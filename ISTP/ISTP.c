/*******************************************************************************
| Module Name: start stop Function module(Idle engine stop )
| File Name: ISTP.c
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2015 Huizhou Desay SV Automotive Co., Ltd.    All rights reserved.
|
| This software is copyright protected and proprietary to Desay SV Automotive Co., Ltd.
| Desay SV Automotive Co., Ltd grants to you only those rights as set out in the
| license conditions. All other rights remain with Desay SV Automotive Co., Ltd.
|
| REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
|-------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Name                                  Company
| ---------------------     ---------------------------------------
| Luo Xindian                             Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2015-10-15    1.0  Luo Xindian		 frist created,for general start stop function 
| 2016-2-18      1.1  Luo Xindian		Modified for KC-2
********************************************************************************/


#ifndef ISTP1C1
#define ISTP1C1
#endif

/* system-headerfiles */
#include "General.h"           
/* General type definitions */

/* foreign headerfiles */
#include "ALG.h"
#include "MMI.h"
#include "OAT.h"
#include "ACCC.h"
#include "CANAPP.h"
#include "CCS.h"
#include "MAC.h"
#include "POW.h"

/* own headerfiles */
#include "ISTP.h"
#include "ISTP_cfg.h"
#include "ISTP_Private.h"
#include "ISTP_Type.h"
#include "appdesc1c1.h"
#define ISTP1C1			/* Name of the Module */

// function description in this module
static void ISTP_vHeatCoolMode( void );
static void ISTP_vErrorManage(void);
static void ISTP_vOffStategy(void);
static void ISTP_vProhibitCondition(void);
static void ISTP_vCoolMode(void);
static void ISTP_vHeatMode(void);
static void ISTP_vBlowerLimit(void);
static void ISTP_vComfortCal(void);
static void ISTP_vEngineMode(void);
static void ISTP_vUpdateEngineReq(void);
static void ISTP_vTimerCount(void);
static void ISTP_vUpdateRteData(void);

static ISTP_tenPriorityLevel ISTP_u8Priority; // the i-stop priority level

static uint8 ISTP_u8StatesDefaultMode;
static uint8 ISTP_u8StatesHeatMode;
static uint8 ISTP_u8StatesCoolMode;
static ISTP_tenModeControl ISTP_enModeControl;
static uint8 ISTP_u8IgOff2OnSelect;

static uint8 ISTP_au8Array[ISTP_nu8Max];
static uint8 ISTP_au16Array[ISTP_nu16Max];

/*****************************************************************************
 Function      : ISTP_vInit                                                	  *
 Description   : Initialises the i-stop module 				*
                					                       			    *
 Return Value  : None                                                        *
*****************************************************************************/
 void ISTP_vInit( void)
{
	ISTP_enModeControl = ISTP_nDefault;
	
	ISTP_au8Array[ISTP_nenStStInfo] = ISTP_nReqStop;
	ISTP_au8Array[ISTP_nu8Valid]=0;
	ISTP_au8Array[ISTP_nu8Version]=ISTP_nSwVersion;
	ISTP_au8Array[ISTP_nenRestartCause]=0;
	ISTP_au8Array[ISTP_nu8ErrorStatus]=0;
	ISTP_au8Array[ISTP_nu8ISState]=ISTP_nReady;
	ISTP_au8Array[ISTP_nu8Allowance]=ISTP_nReqStop;
	ISTP_au8Array[ISTP_nu8StartReq]=0;

	ISTP_au16Array[ISTP_nu16IsTimer]=0;
	ISTP_au16Array[ISTP_nu16IrTimer]=0;
	ISTP_au16Array[ISTP_nu16ErrorCode]=0;
	
	#if (ISTP_nUseRTE == True)
	ISTP_vUpdateRteData();
	#endif
	
	ISTP_u8Priority =ISTP_nLevel0;
	
	ISTP_u8StatesDefaultMode = 0xffU;
	ISTP_u8StatesCoolMode = 0xffU;
	ISTP_u8StatesHeatMode = 0xffU;

	ISTP_u8IgOff2OnSelect=0u;
	
}


/*****************************************************************************
 Function		: ISTP_vReset                                                  						  *
 Description	: Initialises the i-stop module 										  *
                                       														  *
 Return Value	: None                                                        							  *
*****************************************************************************/
void ISTP_vReset( void)
{
	ISTP_enModeControl = ISTP_nDefault; 
	ISTP_au8Array[ISTP_nenStStInfo] = ISTP_nReqStop;
	ISTP_u8Priority = ISTP_nLevel0;
	ISTP_u8IgOff2OnSelect=0u;
}


/*****************************************************************************
 Function      : ISTP_vDeinit                                                 *
 Description   : Initialises the i-stop module*
                                            *
 Return Value  : None                                                        *
*****************************************************************************/
  void ISTP_vDeinit( void)
{
	ISTP_au8Array[ISTP_nenStStInfo] =ISTP_nReqStop;
}


  void ISTP_vActive( void)
{

}

  
Std_ReturnType ISTP_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord)
{

    return 1u;
}
/*****************************************************************************
 Function      : ISTP_vHeatCoolMode                                                 *
 Description   : calculate the mode currently,  there will be three mode *
                                    heat mode and cool mode and defalut        *
 Return Value  : None                                                        *
*****************************************************************************/
static void  ISTP_vHeatCoolMode( void )
{	
	uint16 u16OatValue=0;

	#if(ISTP_OpenInterfaces_Cfg == True)
	u16OatValue=OAT_u16GetValue(OAT_nu16Value);
	#endif
		
	if(u16OatValue < ISTP_u16HeatModeOat) // OAT <15deg heat mode 
	{
		ISTP_enModeControl = ISTP_nHeatMode;
	}
	else if(u16OatValue > ISTP_u16CoolModeOat) // OAT >25deg cool mode 
	{
		ISTP_enModeControl = ISTP_nCoolMode;
	}
	else
	{	// 15~25deg default mode
		if(ISTP_enModeControl ==ISTP_nHeatMode)
		{
			if(u16OatValue > ISTP_u16DefaultModeOatL)
			{
				ISTP_enModeControl = ISTP_nDefault;
			}
		}
		else if(ISTP_enModeControl ==ISTP_nCoolMode)
		{
			if(u16OatValue < ISTP_u16DefaultModeOatH)
			{
				ISTP_enModeControl = ISTP_nDefault;
			}
		}
		else
		{
			ISTP_enModeControl = ISTP_nDefault;
		}
	}
}	
		

/*****************************************************************************
 Function      : ISTP_vErrorManage                                                 *
 Description   : if the voltage is over low or high, it will allow the engine stop,		*
                       if oat and feet sensor is error ,it will set the i-stop error  ,                 *
                        if not it, it will go the next priority  								*
 Return Value  : None                                                        *
*****************************************************************************/
static void ISTP_vErrorManage(void)
{
	uint8 biLowVoltage  =0;
	uint8 biHighVoltage =0;

	#if(ISTP_OpenInterfaces_Cfg == True)
	biLowVoltage=(uint8)POW_u16GetValue(POW_nu16AppLowVoltage);
	biHighVoltage =(uint8)POW_u16GetValue(POW_nu16AppHighVoltage);
	#endif
	if((biLowVoltage == True) || (biHighVoltage == True))
	{	/* When battery voltage is more than 16V or less than 9V,system allows engine stop*/
		ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nReqStop;
		ISTP_u8Priority = ISTP_nMax;
		ISTP_au8Array[ISTP_nu8ErrorStatus] = 3;
	}
	else
	{	/* then it will go to the next Priority*/
		ISTP_u8Priority = ISTP_nLevel1;
		//ISTP_enStStInfo = ISTP_nKeepState;
	}

}


/*****************************************************************************
 Function      :    ISTP_vOffStategy                                                 *
 Description   :  this module will get the AC node information that required in the 	*
                        i-stop ,like the OFF mode  *
 Return Value  : None                                                        *
*****************************************************************************/
static void ISTP_vOffStategy(void)
{
	uint8 u8ModeCtrl=0;
	
	#if(ISTP_OpenInterfaces_Cfg == True)
	u8ModeCtrl=MMI_u8GetValue(MMI_nu8SysState);
	#endif
	
	if( u8ModeCtrl == ISTP_u8ModeOff ) 
	{	 /* it allows engine stop when in the OFF mode*/
		ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nReqStop;
		ISTP_u8Priority = ISTP_nMax;
		ISTP_au8Array[ISTP_nu8ErrorStatus] = 4;
	}
	else
	{
		ISTP_u8Priority = ISTP_nLevel2;
	}
}

/*****************************************************************************
 Function      :    ISTP_vProhibitCondition                                                 *
 Description   :  this module will get the AC node information that required in the 	*
                        i-stop ,like the defrost mode, set temp, Max AC etc  *
 Return Value  : None                                                        *
*****************************************************************************/
static void ISTP_vProhibitCondition(void)
{
	uint8 u8ModeCtrl=0;
	uint8 u8SetTempDr=0;
	uint8 u8SetTempPs=0;
	uint8 u8ComDisplay=0;
	
	#if(ISTP_OpenInterfaces_Cfg == True)
	u8ModeCtrl=MMI_u8GetValue(MMI_nu8SysState);
    #if(SYC_ZONES >= 2)
	u8SetTempDr=MMI_u8GetValue(MMI_nu8SetTempDr);
	u8SetTempPs=MMI_u8GetValue(MMI_nu8SetTempPs);
    #else
    u8SetTempDr=MMI_u8GetValue(MMI_nu8SetTempDr);
    u8SetTempPs=u8SetTempDr;
    #endif
	u8ComDisplay =ACCC_u8GetValue(ACCC_nu8AcDisplay);
	#endif
	
	if(u8ModeCtrl == ISTP_u8Defrost ) // if(ISTP_enDefrostCtrl == MMI_nDefrostOn ) 
	{	 /* it not allow engine stop when in the Manual Defrost*/
		ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nRestart;
		ISTP_u8Priority = ISTP_nMax;
		ISTP_au8Array[ISTP_nu8ErrorStatus] = 5;
		ISTP_au8Array[ISTP_nenRestartCause] = ISTP_nDefrostCause;
	}
	else if((u8SetTempDr ==0xff) ||(u8SetTempPs ==0xff))
	{/* Set Temp Hi*/
		ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nRestart;
		ISTP_u8Priority = ISTP_nMax;
		ISTP_au8Array[ISTP_nu8ErrorStatus] = 6;
		ISTP_au8Array[ISTP_nenRestartCause]  = ISTP_nHiCause;
	}
	else if(((u8SetTempDr ==0) ||(u8SetTempPs ==0))&& ( u8ComDisplay != ISTP_nCompressorOff)) 
	{	 /* it not allow engine stop when set temp LO and A/C on*/
		ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nRestart;
		ISTP_u8Priority = ISTP_nMax;
		ISTP_au8Array[ISTP_nu8ErrorStatus] = 7;
		ISTP_au8Array[ISTP_nenRestartCause]  = ISTP_nLoCause;
	}
	#if(ISTP_nMaxAC ==True)
	else if(u8ModeCtrl == ISTP_u8MaxAC)
	{/* Max A/C On, not allow engine stop*/
		ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nRestart;
		ISTP_u8Priority = ISTP_nMax;
		ISTP_au8Array[ISTP_nu8ErrorStatus] = 8;
		ISTP_au8Array[ISTP_nenRestartCause]  = ISTP_nOthers;
	}
	#endif
	else
	{
		/* then it will go to the next Priority*/
		ISTP_u8Priority = ISTP_nLevel3;
	}
}

/*****************************************************************************
 Function      : ISTP_vCoolMode                                                 *
 Description   : cool Mode Strategy, it will calculate the climate state 		 *
                                            *
 Return Value  : None                                                        *
*****************************************************************************/
static void ISTP_vCoolMode(void)
{
	uint8 u8ACState=0;
	uint16 u16BlowoutTarget=0;
	uint16 u16ActualBlowout=0;
	int16 i16BlowoutDiff=0;
	uint16 u16CcsTempDiff=0;

	#if(ISTP_OpenInterfaces_Cfg == True)
	u8ACState =ACCC_u8GetValue(ACCC_nu8AcDisplay);
    #if(SYC_ZONES >= 2)
	u16BlowoutTarget= MIN(CCS_u16GetValue(CCS_nu16BlowoutTempDr), CCS_u16GetValue(CCS_nu16BlowoutTempPs));
	u16ActualBlowout =MIN(MAC_u16GetValue(MAC_nu16BlowoutTempDr), MAC_u16GetValue(MAC_nu16BlowoutTempDr));
    #else
	u16BlowoutTarget= CCS_u16GetValue(CCS_nu16BlowoutTempDr);
	u16ActualBlowout =MAC_u16GetValue(MAC_nu16BlowoutTempDr);
    #endif
    #if(SYC_ZONES >= 2)
	u16CcsTempDiff=MIN(CCS_u16GetValue(CCS_nu16TempDiffDr),CCS_u16GetValue(CCS_nu16TempDiffPs));
    #else
    CCS_u16GetValue(CCS_nu16TempDiffDr);
    #endif
	#endif
	
	i16BlowoutDiff= u16BlowoutTarget-u16ActualBlowout;
	
	if(u8ACState !=ISTP_nCompressorOff )
	{	/* A/C ON*/
		if(i16BlowoutDiff <ISTP_i8CcsBlowOutLimitL)
		{/* Target blowout ©\ Actual Blowout < ©\12 ¡æ*/
			ISTP_u8StatesCoolMode=0x01u;
			ISTP_au8Array[ISTP_nenRestartCause]=ISTP_nBlowOutCause;
		}
		else if(i16BlowoutDiff >ISTP_i8CcsBlowOutLimitH)
		{/*Target blowout ©\ Actual Blowout > ©\8¡æ */
			ISTP_u8StatesCoolMode&=0xfe;
		}

		// temp difference condition
		if(u16CcsTempDiff < ISTP_u8CoolTempDiffL)
		{	// SI < - TBD deg,not allow engine stop
			ISTP_u8StatesCoolMode |= 0x02U;
			ISTP_au8Array[ISTP_nenRestartCause]  = ISTP_nInCarTempCause;
		} 
		else if ( u16CcsTempDiff> ISTP_u8CoolTempDiffH)
		{	//SI > -TBD deg, allow engine stop
			ISTP_u8StatesCoolMode &= 0xfdU;
		}

	}
	else
	{/* A/C Off , allow engine stop*/
		ISTP_u8StatesCoolMode = 0;
	}

	ISTP_u8StatesCoolMode &= 0x03U;

	ISTP_au8Array[ISTP_nu8ErrorStatus] = 0x20U+ISTP_u8StatesCoolMode;
	
	if(ISTP_u8StatesCoolMode == 0)
	{	/*if all of those condition is satify, it will allow engine stop*/
		//ISTP_u8Priority = ISTP_nMax;
		ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nReqStop;
	} 
	else
	{
		ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nRestart;
	}
}

/*****************************************************************************
 Function      : ISTP_vHeatMode                                                 *
 Description   : heat Mode Strategy it will calculate the climate state *
                                            *
 Return Value  : None                                                        *
*****************************************************************************/
static void ISTP_vHeatMode(void)
{
	uint16 u16BlowoutTarget=0;
	uint16 u16ActualBlowout=0;
	uint16 u16CcsTempDiff=0;
	uint16 i16BlowoutDiff=0;
	uint16 u16CoolantTemp=0;

	#if(ISTP_OpenInterfaces_Cfg == True)
	#if (ISTP_nUseRTE == True)
    #if(SYC_ZONES >= 2)
	u16BlowoutTarget= MAX(CCS_u16GetValue(CCS_nu16BlowoutTempDr), CCS_u16GetValue(CCS_nu16BlowoutTempPs));
	u16ActualBlowout =MAX(MAC_u16GetValue(MAC_nu16BlowoutTempDr), MAC_u16GetValue(MAC_nu16BlowoutTempDr));
    #else
	u16BlowoutTarget= CCS_u16GetValue(CCS_nu16BlowoutTempDr);
	u16ActualBlowout =MAC_u16GetValue(MAC_nu16BlowoutTempDr);
    #endif
    #if(SYC_ZONES >= 2)
	u16CcsTempDiff=MAX(CCS_u16GetValue(CCS_nu16TempDiffDr),CCS_u16GetValue(CCS_nu16TempDiffPs));
    #else
    CCS_u16GetValue(CCS_nu16TempDiffDr);
    #endif
	u16CoolantTemp=HCT_u16GetValue(HCT_nu16Value);
	#endif
	#endif
	
	i16BlowoutDiff= u16BlowoutTarget-u16ActualBlowout;
	
	if(i16BlowoutDiff > ISTP_i8HeatTBlowoutH)
	{/* Target blowout ©\ Actual Blowout > 12 ¡æ*/
		ISTP_u8StatesHeatMode |=0x01U;
		ISTP_au8Array[ISTP_nenRestartCause]  = ISTP_nBlowOutCause;
	}
	else if(i16BlowoutDiff < ISTP_i8HeatTBlowoutL)
	{/*Target blowout ©\ Actual Blowout < 8¡æ */
		ISTP_u8StatesHeatMode &= 0xfeU;
	}

	// temp difference condition
	if(u16CcsTempDiff > ISTP_i8HeatTempDiffH)
	{	// SI < - TBD deg,not allow engine stop
		ISTP_u8StatesHeatMode |= 0x02U;
		ISTP_au8Array[ISTP_nenRestartCause]  = ISTP_nInCarTempCause;
	} 
	else if ( u16CcsTempDiff< ISTP_i8HeatTempDiffL)
	{	//SI > -TBD deg, allow engine stop
		ISTP_u8StatesHeatMode &= 0xfdU;
	}
			
	// Coolant Temp  condition
	if(u16CoolantTemp < ISTP_u8CoolantTempL)
	{  //Coolant Temp<40 ¡æ, not allow engine stop
		ISTP_u8StatesHeatMode |=0x04U;
		ISTP_au8Array[ISTP_nenRestartCause]  = ISTP_nOthers;
	}
	else if(u16CoolantTemp > ISTP_u8CoolantTempH)
	{	//Coolant Temp>55¡æ, allow engine stop
		ISTP_u8StatesHeatMode &= 0xfbU;
	}

	ISTP_u8StatesHeatMode &= 0x07U;

	ISTP_au8Array[ISTP_nu8ErrorStatus] = 0x10U+ISTP_u8StatesHeatMode;

	if(ISTP_u8StatesHeatMode == 0)
	{	/*if all of those condition is satify, it will allow engine stop*/
		//ISTP_u8Priority = ISTP_nMax;
		ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nReqStop;
	} 
	else
	{
		ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nRestart;
	}
}
			


/*****************************************************************************
 Function      : ISTP_vDefaultMode                                                 *
 Description   : the i-stop module*
                       calculation whether engine can stop  when in the default mode                 *
 Return Value  : None                                                        *
*****************************************************************************/
static void ISTP_vDefaultMode(void)
{
	int16 i16CcsTempDiff=0;

	#if(ISTP_OpenInterfaces_Cfg == True)
    #if(SYC_ZONES >= 2)
	i16CcsTempDiff=MIN(abs(CCS_u16GetValue(CCS_nu16TempDiffDr)-640),abs(CCS_u16GetValue(CCS_nu16TempDiffPs)-640));
    #else
    i16CcsTempDiff=CCS_u16GetValue(CCS_nu16TempDiffDr)-640;
    #endif
	#endif
	
	if(i16CcsTempDiff < 0)
	{	// | i16CcsTempDiff |
		i16CcsTempDiff = -i16CcsTempDiff;
	}
	
	if(i16CcsTempDiff > ISTP_u8DefaultTempDiffH)
	{	// SI > |TBD| deg, not allow engine stop
		ISTP_u8StatesDefaultMode |= 0x01U;
		ISTP_au8Array[ISTP_nenRestartCause]  = ISTP_nInCarTempCause;
	} 
	else if ( i16CcsTempDiff < ISTP_u8DefaultTempDiffL)
	{	// SI < |TBD| deg,allow engine stop
		ISTP_u8StatesDefaultMode &= 0xfeU;
	}
	
	ISTP_u8StatesDefaultMode &= 0x01U;
	
	ISTP_au8Array[ISTP_nu8ErrorStatus] = (0x40U+ISTP_u8StatesDefaultMode);

	if(ISTP_u8StatesDefaultMode == 0)
	{	/*if all of those condition is satify, it will allow engine stop*/
		//ISTP_u8Priority = ISTP_nMax;
		ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nReqStop;
	} 
	else
	{ 	/*if one of those condition is not satify, it will not allow engine stop*/
		//ISTP_u8Priority = ISTP_nMax;
		ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nRestart;
	}
	
}


/*****************************************************************************
 Function      : ISTP_vBlowerLimit                                                 *
 Description   : the i-stop module*
                       Limit the blower speed when in the i-stop mode                       *
 Return Value  : None                                                        *
*****************************************************************************/
static void ISTP_vBlowerLimit(void)
{
	uint8 u8BlowerLevel=0;

	#if(ISTP_OpenInterfaces_Cfg == True)
	#if (ISTP_nUseRTE == True)
	u8BlowerLevel=MMI_u8GetValue(MMI_nu8BlwControl);
	#endif
	#endif
	
	if(u8BlowerLevel >= ISTP_u8BowerHi)
	{/* blower level >5bar*/
		ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nRestart;
		ISTP_u8Priority = ISTP_nMax;
		ISTP_au8Array[ISTP_nu8ErrorStatus] = 8;
		ISTP_au8Array[ISTP_nenRestartCause] = ISTP_nBlowerLvl;
	}
	else if(u8BlowerLevel <= ISTP_u8BowerLo)
	{ /*blower level <4bar*/
		ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nReqStop;
		ISTP_u8Priority = ISTP_nLevel4;
	}
	else
	{
		if(ISTP_u8IgOff2OnSelect == False)
		{
			ISTP_au8Array[ISTP_nenStStInfo]  = ISTP_nReqStop;
			ISTP_u8Priority = ISTP_nLevel4;
		}
		
		if(ISTP_au8Array[ISTP_nenStStInfo]  == ISTP_nRestart)
		{
			ISTP_u8Priority = ISTP_nMax;
		}
		else
		{
			ISTP_u8Priority = ISTP_nLevel4;
		}
	}
	
}

/*****************************************************************************
 Function      : ISTP_vComfortCal                                                 *
 Description   : the i-stop module*
                       calculation the confortatble whether engine can stop                   *
 Return Value  : None                                                        *
*****************************************************************************/
static void ISTP_vComfortCal(void)
{
	if(ISTP_enModeControl == ISTP_nCoolMode) // cool mode
	{
		ISTP_vCoolMode();
	}
	else if(ISTP_enModeControl == ISTP_nHeatMode ) //heat mode
	{
		ISTP_vHeatMode();
	}
	else // Default mode
	{
		ISTP_vDefaultMode();
	}
	ISTP_u8Priority = ISTP_nMax;
}

/*****************************************************************************
 Function      : ISTP_vEngineMode                                                 *
 Description   : the i-stop engine mode *
                                            *
 Return Value  : None                                                        *
*****************************************************************************/
static void ISTP_vEngineMode(void)
{
	uint8 u8SSMStatus=0;

	#if(ISTP_OpenInterfaces_Cfg == True)
	#if (ISTP_nUseRTE == True)
	u8SSMStatus=CANAPP_u16GetValue(CANAPP_nu16EMS_SSMStatus);
	#endif
	#endif
/*
	if(u8SSMStatus == ISTP_Stopped)
	{ 
		ISTP_au8Array[ISTP_nu8ISState]=ISTP_nEngineStop;
	}
	else if(u8SSMStatus == ISTP_Operation)
	{
		ISTP_au8Array[ISTP_nu8ISState]=ISTP_nEngineRunning;
	}
	else
	{
		ISTP_au8Array[ISTP_nu8ISState]=ISTP_nOthers;
	}
	*/
    if((u8SSMStatus == ISTP_Stopped)||(u8SSMStatus == ISTP_AutoStopping))
	{ 				
		ISTP_au8Array[ISTP_nu8ISState]=ISTP_nEngineStop;
	}
	/*
	else if(u8SSMStatus == ISTP_Operation)
	{
		ISTP_au8Array[ISTP_nu8ISState]=ISTP_nEngineRunning;
	}*/
	else
	{
		ISTP_au8Array[ISTP_nu8ISState]=ISTP_nEngineRunning;
		//ISTP_au8Array[ISTP_nu8ISState]=ISTP_nOthers;
	}
}


/*****************************************************************************
 Function      : ISTP_vUpdateEngineReq                                                 *
 Description   : the i-stop module*
                                            *
 Return Value  : None                                                        *
*****************************************************************************/
static void ISTP_vUpdateEngineReq(void)
{
    /*
	if(ISTP_au8Array[ISTP_nu8ISState] == ISTP_nEngineRunning)
	{
		ISTP_au8Array[ISTP_nu8Allowance] =ISTP_au8Array[ISTP_nenStStInfo] ;

		ISTP_au8Array[ISTP_nu8StartReq] =0x00 ;
		
	}
	else if(ISTP_au8Array[ISTP_nu8ISState] == ISTP_nEngineStop)
	{
		ISTP_au8Array[ISTP_nu8Allowance] =ISTP_au8Array[ISTP_nenStStInfo] ;
		ISTP_au8Array[ISTP_nu8StartReq] =ISTP_au8Array[ISTP_nenStStInfo] ;
	}
	else
	{
		ISTP_au8Array[ISTP_nu8Allowance] =0;
		ISTP_au8Array[ISTP_nu8StartReq] =0;
	}
	*/
	ISTP_au8Array[ISTP_nu8Allowance] =ISTP_au8Array[ISTP_nenStStInfo] ;/*WII NOT DETECT ISTP SIGNAL,170428*/
	//ISTP_au8Array[ISTP_nu8StartReq] =ISTP_au8Array[ISTP_nenStStInfo] ;

	if( (ISTP_au8Array[ISTP_nu8ISState]==ISTP_nEngineStop)&&(ISTP_au8Array[ISTP_nu8Allowance]>0))/*not allow,170717*/
	{
		ISTP_au8Array[ISTP_nu8StartReq]  = ISTP_nRestart;
	}
	else
	{
		ISTP_au8Array[ISTP_nu8StartReq]  = ISTP_nReqStop;
	}
	ISTP_u8Priority = ISTP_nLevel0;

}

/*****************************************************************************
 Function      : ISTP_vTimerCount                                                 *
 Description   : the i-stop module*
                                            *
 Return Value  : None                                                        *
*****************************************************************************/
static void ISTP_vTimerCount(void)
{
	if(ISTP_au8Array[ISTP_nu8ISState] ==ISTP_nEngineStop)
	{
		if(ISTP_au16Array[ISTP_nu16IsTimer] <0xffff)
		{
			ISTP_au16Array[ISTP_nu16IsTimer]++;
		}
		ISTP_au16Array[ISTP_nu16IrTimer]=0;
	}
	else
	{
		ISTP_au16Array[ISTP_nu16IsTimer]=0;
		if(ISTP_au16Array[ISTP_nu16IrTimer] <255)
		{
			ISTP_au16Array[ISTP_nu16IrTimer]++;
		}
	}
}
#if (ISTP_nUseRTE == True)
/* ===========================================================================
* Function   : void ISTP_vUpdateRteData (void)
* Description: update RTE data container function of ISTP
* Takes      : None
* Returns    : None
*/
static void ISTP_vUpdateRteData(void)
{
	Rte_IWrite_Istp_vMain_IstpISState_u8State(ISTP_au8Array[ISTP_nu8ISState]);
	Rte_IWrite_Istp_vMain_IstpIsAllowanoe_u8State(ISTP_au8Array[ISTP_nu8Allowance]);
	Rte_IWrite_Istp_vMain_IstpIsStateReq_u8State(ISTP_au8Array[ISTP_nu8StartReq]);
	Rte_IWrite_Istp_vMain_IstpValid_u8Flag(ISTP_au8Array[ISTP_nu8StartReq]);
	Rte_IWrite_Istp_vMain_IstpISTime_u16Time(ISTP_au16Array[ISTP_nu16IsTimer]);
	Rte_IWrite_Istp_vMain_IstpIRTime_u16Time(ISTP_au16Array[ISTP_nu16IrTimer]);
	Rte_IWrite_Istp_vMain_IstpErrorCode_u16BitMap(ISTP_au16Array[ISTP_nu16ErrorCode]);
}
#endif
/*****************************************************************************
 Function      : ISTP_vMain                                                   *
 Description   : In the On state, The i-stop is .                         *
               	calculatate the th state whether the engine can stop according 		 *
               	the AC conditions  *
 NOTE: This part of the main code is normally called from the 100mS container*
 Return Value  : None                                                        *
*****************************************************************************/

void ISTP_vMain (void)
{
    uint8 u8FunctionCfg[4] = {0xFF,0xFF,0xFF,0xFF};
    
    ISTP_u8GetFuctionCfg(u8FunctionCfg);

    if((u8FunctionCfg[2]&0x03) == 0x02)
    {/*ISTP cofig*/
        
        /*Byte2,bit0&1,
          00: not used
          01: none
          10: have
          other:reserved
         */
    	ISTP_vHeatCoolMode(); 	// calculate the heat or cool mode
    	
    	ISTP_vEngineMode();
    	
    	ISTP_vTimerCount();
    	
    	switch(ISTP_u8Priority)
    	{
    		case ISTP_nLevel0:
    			ISTP_vErrorManage();
    			break;					
    		case ISTP_nLevel1:
    			ISTP_vOffStategy();
    			break;
    		case ISTP_nLevel2:
    			ISTP_vProhibitCondition();
    			break;
    		case ISTP_nLevel3:
    			ISTP_vBlowerLimit();
    			break;
    		case ISTP_nLevel4:
    			ISTP_vComfortCal();
    			break;
    		case ISTP_nMax:
    			ISTP_vUpdateEngineReq();
    			break;
    		default :
    			ISTP_u8Priority = ISTP_nLevel0;
    			break;
    	}	
    }
    else
    {
    	ISTP_au8Array[ISTP_nenStStInfo] = ISTP_nReqStop;
    	ISTP_au8Array[ISTP_nu8Valid]=0;
    	ISTP_au8Array[ISTP_nenRestartCause]=0;
    	ISTP_au8Array[ISTP_nu8ErrorStatus]=0;
    	ISTP_au8Array[ISTP_nu8ISState]=ISTP_nReady;
    	ISTP_au8Array[ISTP_nu8Allowance]=ISTP_nReqStop;
    	ISTP_au8Array[ISTP_nu8StartReq]=0;

    	ISTP_au16Array[ISTP_nu16IsTimer]=0;
    	ISTP_au16Array[ISTP_nu16IrTimer]=0;
    	ISTP_au16Array[ISTP_nu16ErrorCode]=0;
    }
	#if (ISTP_nUseRTE == True)
	ISTP_vUpdateRteData();
	#endif
}

/*****************************************************************************
 Function      : ISTP_u8GetValue                                              *
 Description   : The extern model get the uint8 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*****************************************************************************/
uint8 ISTP_u8GetValue( ISTP_tenu8VarNumber enIndex )
{
	if ( enIndex < ISTP_nu8Max )
	{
		return ISTP_au8Array[enIndex];
	}
	else
	{
		return ISTP_au8Array[ISTP_nu8Max-1];
	}
}

/*****************************************************************************
 Function      : ISTP_u16GetValue                                              *
 Description   : The extern model get the uint16 type variable value from this*
				 model                                                       *
 Return Value  : uint16 value                                                 *
*****************************************************************************/
uint16 ISTP_u16GetValue( ISTP_tenu16VarNumber enIndex )
{
	if ( enIndex < ISTP_nu16Max )
	{
		return ISTP_au16Array[enIndex];
	}
	else
	{
		return ISTP_au16Array[ISTP_nu16Max-1];
	}
}
/*   EOF */



