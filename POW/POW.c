
/*******************************************************************************
| Module Name: Power manage model
| File Name: pow.c
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
| Li Ning                       Desay SV Automotive Co., Ltd

|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver        	Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 
|2015.9.2        a2.2             Li Ning		the first version for integration

********************************************************************************/


/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#ifndef POW_C
#define POW_C                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */





/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */


/* Please put the headerfiles which related to foreign here! */

/* Own headerfiles */

#include "POW_Pte.h"
#include "POW_cfg.h"
#include "POW_If.h"


/* Please put the headerfiles which related to own here! */


/*****************************************************************************
* GLOBAL DEFINITIONS
*
* In this section define
* - all global ROM-CONSTants of your module
* - all global variables of your module
*****************************************************************************/

/* example1: Global ROM-constants
   ----------------------------------------------------- */

/* example2: Global Variables
   ----------------------------------------------------- */


/*****************************************************************************
* FILE LOCAL DEFINITIONS
*
* In this section define
* - all file local macros
* - all file local define-CONSTants
* - all file local ROM-CONSTants (STATIC)
* - all file local type definitions
* - all file local variables (STATIC)
*****************************************************************************/
/* example1: Local Macros
   ----------------------------------------------------- */

/* example2: Local Define-constants
   ----------------------------------------------------- */



/* example3: Local ROM-constants
   ----------------------------------------------------- */


/* example4: Local Type Definition
   ----------------------------------------------------- */



/* example5: Local Variables
   ----------------------------------------------------- */
   

static uint16 POW_u16BattVolt;	/*only use for check low or high voltage*/
//#if (POW_AppRef==POW_Ref_IGN2)||(POW_ComRef==POW_Ref_IGN2)||(POW_DiagRef==POW_Ref_IGN2)||(POW_K30Abnormal ==  1)
static uint16 POW_u16IgnVolt;
//#endif
static uint16 POW_u16AppLeaveLowVoltageTimer;
static uint16 POW_u16AppEnterLowVoltageTimer;
static uint16 POW_u16AppLeaveHighVoltageTimer;
static uint16 POW_u16AppEnterHighVoltageTimer;
static uint16 POW_u16AppEnterHighVolTimerCfgShare;


static uint16 POW_u8IDIgnStaticOn;
static uint16 POW_u8IDIgnStable;
static uint16 POW_u16IDHalRaw5vOutputFb;
static uint16 POW_u16IDHalK30Fb;
//#if (POW_AppRef==POW_Ref_IGN1)||(POW_ComRef==POW_Ref_IGN1)||(POW_DiagRef==POW_Ref_IGN1)
static uint16 POW_u16IDHalIgn1Fb;
//#endif
static uint16 POW_u16IDHalIgn2Fb;
//#if (POW_SensorSupplyFbUsed==1)
	static uint16 POW_u16IDHal5vSensorFb;
//#endif


static uint16 POW_u16InternalDataAppHighVoltage;
static uint16 POW_u16InternalDataAppLowVoltage;
static uint16 POW_u16InternalDataComHighVoltage;
static uint16 POW_u16InternalDataComLowVoltage;
static uint16 POW_u16InternalDataDiagHighVoltage;
static uint16 POW_u16InternalDataDiagLowVoltage;
#if (Ref4_CheckVoltage==1)
static uint16 POW_u16InternalDataRef4HighVoltage;
static uint16 POW_u16InternalDataRef4LowVoltage;
#endif
static uint16 POW_u16InternalDataAdValid;
static uint16 POW_u16InternalDataK30VoltFb;
static uint16 POW_u16InternalDataIGN2VoltFb;
static uint16 POW_u16InternalDataSwVersion;
static uint16 POW_u16InternalDataErrorCode;
static uint16 POW_u16InternalData5vOutputStable;
static uint16 POW_u16InternalData5vOutputFb;










#if (POW_SensorSupplyFbUsed ==1)
static uint8 POW_u8EC5VSensorTime;
#endif
static uint8 POW_u8AdValidTime;
static uint8 POW_u85vStableTime;

#if (Com_CheckVoltage==1)
static uint16 POW_u16CanEnterLowVoltageTimer;/*Can low(inactive) voltage timer*/
static uint16 POW_u16CanLeaveLowVoltageTimer;/*Can low(inactive) voltage timer*/
static uint16 POW_u16CanEnterHighVoltageTimer;/*Can low(inactive) voltage timer*/
static uint16 POW_u16CanLeaveHighVoltageTimer;/*Can low(inactive) voltage timer*/
#endif

#if (Diag_CheckVoltage==1)
static uint16 POW_u16DiagEnterLowVoltageTimer;/*Diag low voltage timer*/
static uint16 POW_u16DiagLeaveLowVoltageTimer;/*Diag low voltage timer*/
static uint16 POW_u16DiagEnterHighVoltageTimer;/*Diag low voltage timer*/
static uint16 POW_u16DiagLeaveHighVoltageTimer;/*Diag low voltage timer*/
#endif

#if (Ref4_CheckVoltage==1)
static uint16 POW_u16Ref4EnterLowVoltageTimer;/*Diag low voltage timer*/
static uint16 POW_u16Ref4LeaveLowVoltageTimer;/*Diag low voltage timer*/
static uint16 POW_u16Ref4EnterHighVoltageTimer;/*Diag low voltage timer*/
static uint16 POW_u16Ref4LeaveHighVoltageTimer;/*Diag low voltage timer*/
#endif

static void POW_vLowHighVoltageCheck (void);
static uint16 POW_vReadBatVoltage(void);
static void POW_vVoltageCheck(void);
static void  POW_v5vOutputCtrl(void);
static void POW_vSensor5vOutputCtrl(void);
static uint16  POW_u16ForceIoControl_Sensor5vFb_Set(uint16 ForceIoControlWord);
static uint16  POW_u16ForceIoControl_Sensor5vFb_Clr(uint16 ForceIoControlWord);
static void POW_vAdValidCheck(void);
static void POW_v5vOutputStableCheck(void);

#if (POW_SensorSupplyFbUsed==1)
static void POW_v5vSensorFbCheck(void);
#endif

tstPOW_ForceSort POW_tstPtsStatus;


#if (POW_AppRef==POW_Ref_K30)
static void POW_vAppLowHighVoltageCheckK30 (void);	
#endif
static void POW_vAppLowHighVoltageCheckK15 (void);
#if (POW_ComRef==POW_Ref_K30)
static void POW_vComLowHighVoltageCheckK30 (void);
#endif
static void POW_vComLowHighVoltageCheckK15 (void);
#if (POW_DiagRef==POW_Ref_K30)
static void POW_vDiagLowHighVoltageCheckK30 (void);
#endif
static void POW_vDiagLowHighVoltageCheckK15 (void);


//#if (POW_K30Abnormal ==  1)
/*static uint16 POW_u16BatShortGndVoltageEnterTime;
static uint16 POW_u16BatShortGndVoltageRecoverTime;*/
static uint8	POW_u8BatAbnormalFlag;
static void POW_vVoltageAbnormalCheck(void);
//#endif



/* ===========================================================================
* Function   : uint8 POW_vIDInputUpdate()
* Description: update the interface date of input.
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/

static uint8 POW_vIDInputUpdate(void)
{
	uint8 u8retvalue;
	u8retvalue =0U;	
	
	POW_u8IDIgnStaticOn		= POW_vImpIDIgnStaticOn();
	POW_u8IDIgnStable			= POW_vImpIDIgnStable();
	POW_u16IDHalRaw5vOutputFb 	= POW_vImpIDGetAnalogValue5VOutputFb();	
	POW_u16IDHalK30Fb			= POW_vImpIDGetAnalogValueBatFb();
	POW_u16IDHalIgn2Fb		= POW_vImpIDGetAnalogValueIgn2Fb();
	
	#if (POW_SensorSupplyFbUsed ==1)	
		POW_u16IDHal5vSensorFb=POW_vImpIDGet5vSensorSupplyFb();
	#else		
	#endif
	

	u8retvalue =1U;
	return (u8retvalue);
}

/* ===========================================================================
* Function   : uint8 POW_vIDOutputUpdate()
* Description: update the interface date of output.
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/

static uint8 POW_vIDOutputUpdate(void)
{
	uint8 u8retvalue;
	u8retvalue = 0U;

	/*update output of my module*/	
	POW_u16Array[POW_nu16AppLowVoltage] 	= get_bPowInternalDataAppLowVoltage();	
	
	POW_u16Array[POW_nu16AppHighVoltage] 	= get_bPowInternalDataAppHighVoltage();
	
	POW_u16Array[POW_nu16ComLowVoltage] 	= get_bPowInternalDataComLowVoltage();
	
	POW_u16Array[POW_nu16ComHighVoltage] 	= get_bPowInternalDataComHighVoltage();	
	
	POW_u16Array[POW_nu16DiagLowVoltage] 	= get_bPowInternalDataDiagLowVoltage();

	POW_u16Array[POW_nu16DiagHighVoltage] 	= get_bPowInternalDataDiagHighVoltage();

	#if (Ref4_CheckVoltage==1)
		POW_u16Array[POW_nu16Ref4LowVoltage] 	= get_bPowInternalDataRef4LowVoltage();

		POW_u16Array[POW_nu16Ref4HighVoltage] 	= get_bPowInternalDataRef4HighVoltage();
	#endif
	
	POW_u16Array[POW_nu16AdValid] 			= get_bPowInternalDataAdValid();	

	POW_u16Array[POW_nu16RawK30VoltFb] 	= 	get_bPowInternalDataRawK30VoltFb();

	POW_u16Array[POW_nu16ResultK30VoltFb] 	= get_bPowInternalDataResultK30VoltFb();

	POW_u16Array[POW_nu16RawIGN2VoltFb] 	= get_bPowInternalDataRawIGN2VoltFb();
	
	POW_u16Array[POW_nu16ResultIGN2VoltFb] 		= get_bPowInternalDataResultIGN2VoltFb() ;

	POW_u16Array[POW_nu16SwVersion] 		= get_bPowInternalDataSwVersion();
	
	POW_u16Array[POW_nu16ErrorCode] 		= get_bPowInternalDataErrorCode();
		
	POW_u16Array[POW_nu165vOutputStable] 	=get_bPowInternalData5vOutputStable();
	
	POW_u16Array[POW_nu16Raw5vOutputFb] 	= get_bPowInternalData5vOutputFb();

	POW_u16Array[POW_nu16Result5vOutputFb]	=	POW_5vOutputToValue(get_bPowInternalData5vOutputFb());
	
	
	/*update */
	POW_vExpIDAll();

	u8retvalue =1U;
	return (u8retvalue);
}


/* ===========================================================================
* Function   : uint16 POW_u16ClrPtsStatus()
* Description: supply variable for other modules.
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/


static uint16 POW_u16ClrPtsStatus(void)
{
	uint16 u16retvalue;
	u16retvalue =0U;
	POW_tstPtsStatus.POW_u16K15VoltageFbValue = 0U;
	POW_tstPtsStatus.POW_u165vOutPutCtrlValue = 0U;
	POW_tstPtsStatus.POW_u165vOutPutFbValue = 0U;
	POW_tstPtsStatus.POW_u16K30VoltageFbValue = 0U;
	POW_tstPtsStatus.POW_u16SensorFbValue = 0U;
	POW_tstPtsStatus.POW_u16SensorSupplyValue = 0U;
	POW_tstPtsStatus.POW_u8K15VoltageFbFlag = 0U;
	POW_tstPtsStatus.POW_u85vOutPutCtrlFlag = 0U;
	POW_tstPtsStatus.POW_u85vOutPutFbFlag = 0U;
	POW_tstPtsStatus.POW_u8K30VoltageFbFlag = 0U;
	POW_tstPtsStatus.POW_u8SensorFbFlag = 0U;
	POW_tstPtsStatus.POW_u8SensorSupplyCtrlFlag = 0U;

	u16retvalue =1U;
	return (u16retvalue);

	
}

/* ===========================================================================
* Function   : void POW_vReset(void)
* Description: this function be call when k30 turn on from off state thant mcu can work normally.
* Input      : none.
* Returns    : none.
*/

static void POW_vHmiDataReset(void)
{
	/* set the default output value for uint16 */
	set_bPowInternalDataSwVersion(0x0300U);	
	clr_bPowInternalDataErrorCode(0x0000U);
	set_bPowInternalDataAppHighVoltage(1);  
	set_bPowInternalDataAppLowVoltage(1);
	set_bPowInternalDataComLowVoltage(1);
	set_bPowInternalDataComHighVoltage(1);
	set_bPowInternalDataDiagLowVoltage(1);
	set_bPowInternalDataDiagHighVoltage(1);
	#if (Ref4_CheckVoltage==1)
		set_bPowInternalDataRef4LowVoltage(1);
		set_bPowInternalDataRef4HighVoltage(1);
	#endif
	clr_bPowInternalDataAdValid();
	clr_bPowInternalData5vOutputStable();
	clr_bPowInternalData5vOutputFb();
	clr_bPowInternalDataResultIGN2VoltFb() ;
}

/* ===========================================================================
* Function   : void POW_vReset(void)
* Description: this function be call when k30 turn on from off state thant mcu can work normally.
* Input      : none.
* Returns    : none.
*/

void POW_vReset(void)
{
	/* used pin reset*/
	//POW_vPinReset();	

	/* register ad function */

	/*clear array data for hmi*/
	POW_vHmiDataReset();
	

	/* set the temporary variable*/
	
	POW_u16BattVolt = 0U;
	#if (POW_AppRef==POW_Ref_IGN2)||(POW_ComRef==POW_Ref_IGN2)||(POW_DiagRef==POW_Ref_IGN2)||(POW_K30Abnormal ==  1)
		POW_u16IgnVolt = 0U;
	#endif

	#if (POW_K30Abnormal ==  1)
	/*POW_u16BatShortGndVoltageEnterTime = 0U;
	POW_u16BatShortGndVoltageRecoverTime= POW_u16BatShortGndVoltageRecoverTimeCfg;*/
	POW_u8BatAbnormalFlag = False;
	#endif

	/*set the counter when the battery voltage enter hi or low voltage*/
	POW_u16AppLeaveLowVoltageTimer = POW_u16AppLeaveLowVoltageTimerCfg;	// quickly response when the system power on 
	POW_u16AppLeaveHighVoltageTimer = POW_u16AppLeaveHighVoltageTimerCfg;
	POW_u16AppEnterLowVoltageTimer = 0U;
	POW_u16AppEnterHighVoltageTimer = 0U;
	POW_u16AppEnterHighVolTimerCfgShare = 0U;
	#if (Com_CheckVoltage==1)
		POW_u16CanLeaveLowVoltageTimer = POW_u16CanLeaveLowVoltageTimerCfg; // quickly response when the system power on 
		POW_u16CanLeaveHighVoltageTimer = POW_u16CanLeaveHighVoltageTimerCfg;
		POW_u16CanEnterLowVoltageTimer = 0U;
		POW_u16CanEnterHighVoltageTimer = 0U;	
	#endif
	
	#if (Diag_CheckVoltage==1)
		POW_u16DiagLeaveLowVoltageTimer = POW_u16DiagLeaveLowVoltageTimerCfg; // quickly response when the system power on 
		POW_u16DiagLeaveHighVoltageTimer = POW_u16DiagLeaveHighVoltageTimerCfg;
		POW_u16DiagEnterLowVoltageTimer = 0U;
		POW_u16DiagEnterHighVoltageTimer = 0U;
	#endif

	#if (Ref4_CheckVoltage==1)
		POW_u16Ref4LeaveLowVoltageTimer 	= POW_u16Ref4LeaveLowVoltageTimerCfg; // quickly response when the system power on 
		POW_u16Ref4LeaveHighVoltageTimer 	= POW_u16Ref4LeaveHighVoltageTimerCfg;
		POW_u16Ref4EnterLowVoltageTimer 	= 0U;
		POW_u16Ref4EnterHighVoltageTimer 	= 0U;
	#endif
      

	/*error code detect cfg*/
	#if (POW_SensorSupplyFbUsed ==1)
	POW_u8EC5VSensorTime=0x00U;
	#endif

	/*ad valid time reset*/
	POW_u8AdValidTime = 0x00U;
	
	/*5v stable time reset*/
	POW_u85vStableTime=0x00u;

	
	/*pts status clear*/
	POW_u16ClrPtsStatus();

	/*update output data*/
	POW_vIDOutputUpdate();

	
	
}


/*-------not used------------*/
void POW_vInit(void)
{
	
}	

/* ===========================================================================
* Function   : void POW_vWakeUp(void)
* Description: this function be call when the system wake up.
* Input      : none.
* Returns    : none.
*/
void POW_vWakeUp(void)
{
	/* the function be call when the system wake up*/
	#if (POW_SensorSupplyFbUsed ==1)
		POW_u8EC5VSensorTime=0x00U;
	#endif
	clr_bPowInternalDataErrorCode(0x0000U);
	POW_u8AdValidTime = 0x00U;
	POW_u85vStableTime = 0x00U;
	clr_bPowInternalDataAdValid();

	/*set the counter when the battery voltage enter hi or low voltage*/
	POW_u16AppLeaveLowVoltageTimer 		= POW_u16AppLeaveLowVoltageTimerCfg;	// quickly response when the system power on 
	POW_u16AppLeaveHighVoltageTimer 		= POW_u16AppLeaveHighVoltageTimerCfg;
	POW_u16AppEnterLowVoltageTimer 		= 0U;
	POW_u16AppEnterHighVoltageTimer 		= 0U;
	POW_u16AppEnterHighVolTimerCfgShare 	= 0U;
	#if (Com_CheckVoltage==1)
		POW_u16CanLeaveLowVoltageTimer 	= POW_u16CanLeaveLowVoltageTimerCfg; // quickly response when the system power on 
		POW_u16CanLeaveHighVoltageTimer 	= POW_u16CanLeaveHighVoltageTimerCfg;
		POW_u16CanEnterLowVoltageTimer 	= 0U;
		POW_u16CanEnterHighVoltageTimer 	= 0U;	
	#endif
	
	#if (Diag_CheckVoltage==1)
		POW_u16DiagLeaveLowVoltageTimer 	= POW_u16DiagLeaveLowVoltageTimerCfg; // quickly response when the system power on 
		POW_u16DiagLeaveHighVoltageTimer 	= POW_u16DiagLeaveHighVoltageTimerCfg;
		POW_u16DiagEnterLowVoltageTimer 	= 0U;
		POW_u16DiagEnterHighVoltageTimer 	= 0U;
	#endif

	#if (Ref4_CheckVoltage==1)
		POW_u16Ref4LeaveLowVoltageTimer 	= POW_u16Ref4LeaveLowVoltageTimerCfg; // quickly response when the system power on 
		POW_u16Ref4LeaveHighVoltageTimer 	= POW_u16Ref4LeaveHighVoltageTimerCfg;
		POW_u16Ref4EnterLowVoltageTimer 	= 0U;
		POW_u16Ref4EnterHighVoltageTimer 	= 0U;
	#endif

	#if (POW_K30Abnormal ==  1)
		/*POW_u16BatShortGndVoltageEnterTime = 0U;
		POW_u16BatShortGndVoltageRecoverTime= POW_u16BatShortGndVoltageRecoverTimeCfg;*/
		POW_u8BatAbnormalFlag = False;
	#endif
	
}


#if (POW_AppRef==POW_Ref_K30)
/* ===========================================================================
* Function   : void POW_vLowHighVoltageCheckK30(void)
* Description: this function check the all high or low voltage for app 
* Input      : none.
* Returns    : none.
*/
static void POW_vAppLowHighVoltageCheckK30 (void)
{
	/*------------------------------------application function voltage----------------------------------*/	
        /*  leave app low volatage  (8.7v) */
	if ( POW_u16BattVolt >= POW_u16AppLowVoltageThreshold )
	{
		/*avoid warning*/
		POW_u16AppLeaveLowVoltageTimer = POW_u16AppLeaveLowVoltageTimer;
		
		#if POW_u16AppLeaveLowVoltageTimerCfg>0U
			if ( POW_u16AppLeaveLowVoltageTimer >= POW_u16AppLeaveLowVoltageTimerCfg )
			{
				clr_bPowInternalDataAppLowVoltage();
				POW_u16AppEnterLowVoltageTimer = 0U;
			}
			else
			{			
				POW_u16AppLeaveLowVoltageTimer++;			
			}
		#else
			clr_bPowInternalDataAppLowVoltage();
			POW_u16AppEnterLowVoltageTimer = 0U;
		#endif
	}

	/* enter app low voltage (8.2v)*/
	else if ( POW_u16BattVolt <= (uint16)(POW_u16AppLowVoltageThreshold-POW_u16AppLowVoltageHystCfg) )
	{
		/*avoid warning*/
		POW_u16AppEnterLowVoltageTimer = POW_u16AppEnterLowVoltageTimer;
		
		#if POW_u16AppEnterLowVoltageTimerCfg>0U
			if ( POW_u16AppEnterLowVoltageTimer >= POW_u16AppEnterLowVoltageTimerCfg )
			{
				set_bPowInternalDataAppLowVoltage(1);
				POW_u16AppLeaveLowVoltageTimer = 0U;
			}
			else
			{
				POW_u16AppEnterLowVoltageTimer++;
			}
		#else
			set_bPowInternalDataAppLowVoltage(1);
			POW_u16AppLeaveLowVoltageTimer = 0U;
		#endif
	}
	
	else
	{
		 /*In the Hysteresis and do nothing*/
	}


	/* config time of app super high voltage (19v) 10ms*/
	if ( POW_u16BattVolt >= POW_u16AppSuperHighVoltageThreshold ) /* 19v 10ms*/
	{
		POW_u16AppEnterHighVolTimerCfgShare = POW_u16AppEnterSuperHighVoltageTimerCfg;
	}
	
	 /*config time of app high voltage 16v ~ 19V 1.2S*/
       else if ( POW_u16BattVolt >= POW_u16AppHighVoltageThreshold)   
       {
             POW_u16AppEnterHighVolTimerCfgShare = POW_u16AppEnterHighVoltageTimerCfg;
       }
	   
	/* you can add other voltage*/
	else
	{
		
	}
    

	/*leave high voltage */
	if ( POW_u16BattVolt <= POW_u16AppHighVoltageThreshold )
	{
		/*avoid warning*/
		POW_u16AppLeaveHighVoltageTimer =POW_u16AppLeaveHighVoltageTimer;
		
		#if POW_u16AppLeaveHighVoltageTimerCfg>0U
	    		if(POW_u16AppLeaveHighVoltageTimer >= POW_u16AppLeaveHighVoltageTimerCfg)
			{
				clr_bPowInternalDataAppHighVoltage();
	             	 	POW_u16AppEnterHighVoltageTimer = 0U;
	    		}
			else
			{
				POW_u16AppLeaveHighVoltageTimer++;
			}
		#else
			 clr_bPowInternalDataAppHighVoltage();
	             	 POW_u16AppEnterHighVoltageTimer = 0U;
		#endif
	}

	/*enter high voltage or super high voltage */
	else if ( POW_u16BattVolt >= (uint16)(POW_u16AppHighVoltageThreshold+POW_u16AppHighVoltageHystCfg) )
	{		
              if(POW_u16AppEnterHighVoltageTimer >= POW_u16AppEnterHighVolTimerCfgShare)
              {
		       set_bPowInternalDataAppHighVoltage(1);
			POW_u16AppLeaveHighVoltageTimer = 0U;
              }
              else
              {
                    POW_u16AppEnterHighVoltageTimer++;
              }
	}
	
       else
       {       
              /*In the Hysteresis and do nothing*/
       }
}
#endif


/* ===========================================================================
* Function   : void POW_vLowHighVoltageCheckK15(void)
* Description: this function check the all high or low voltage for app 
* Input      : none.
* Returns    : none.
*/
static void POW_vAppLowHighVoltageCheckK15 (void)
{
	/*------------------------------------application function voltage----------------------------------*/	
        /*  leave app low volatage  (8.7v) */
	
	if ( POW_u16IgnVolt >= POW_u16AppLowVoltageThresholdIgn )
	{
		/*avoid warning*/
		POW_u16AppLeaveLowVoltageTimer = POW_u16AppLeaveLowVoltageTimer;
		
		#if POW_u16AppLeaveLowVoltageTimerCfg>0U
			if ( POW_u16AppLeaveLowVoltageTimer >= POW_u16AppLeaveLowVoltageTimerCfg )
			{
				clr_bPowInternalDataAppLowVoltage();
				POW_u16AppEnterLowVoltageTimer = 0U;
			}
			else
			{			
				POW_u16AppLeaveLowVoltageTimer++;			
			}
		#else
			clr_bPowInternalDataAppLowVoltage();
			POW_u16AppEnterLowVoltageTimer = 0U;
		#endif
	}

	/* enter app low voltage (8.2v)*/
	else if ( POW_u16IgnVolt <= (uint16)(POW_u16AppLowVoltageThresholdIgn-POW_u16AppLowVoltageIgnHystCfg) )
	{
		/*avoid warning*/
		POW_u16AppEnterLowVoltageTimer = POW_u16AppEnterLowVoltageTimer;
		
		#if POW_u16AppEnterLowVoltageTimerCfg>0U
			if ( POW_u16AppEnterLowVoltageTimer >= POW_u16AppEnterLowVoltageTimerCfg )
			{
				set_bPowInternalDataAppLowVoltage(1);
				POW_u16AppLeaveLowVoltageTimer = 0U;
			}
			else
			{
				POW_u16AppEnterLowVoltageTimer++;
			}
		#else
			set_bPowInternalDataAppLowVoltage(1);
			POW_u16AppLeaveLowVoltageTimer = 0U;
		#endif
	}
	
	else
	{
		 /*In the Hysteresis and do nothing*/
	}


	/* config time of app super high voltage (19v) 10ms*/
	if ( POW_u16IgnVolt >= POW_u16AppSuperHighVoltageThresholdIgn ) /* 19v 10ms*/
	{
		POW_u16AppEnterHighVolTimerCfgShare = POW_u16AppEnterSuperHighVoltageTimerCfg;
	}
	
	 /*config time of app high voltage 16v ~ 19V 1.2S*/
       else if ( POW_u16IgnVolt >= POW_u16AppHighVoltageThresholdIgn)   
       {
             POW_u16AppEnterHighVolTimerCfgShare = POW_u16AppEnterHighVoltageTimerCfg;
       }
	   
	/* you can add other voltage*/
	else
	{
		
	}
    

	/*leave high voltage */
	if ( POW_u16IgnVolt <= POW_u16AppHighVoltageThresholdIgn )
	{
		/*avoid warning*/
		POW_u16AppLeaveHighVoltageTimer =POW_u16AppLeaveHighVoltageTimer;
		
		#if POW_u16AppLeaveHighVoltageTimerCfg>0U
	    		if(POW_u16AppLeaveHighVoltageTimer >= POW_u16AppLeaveHighVoltageTimerCfg)
			{
				clr_bPowInternalDataAppHighVoltage();
	             	 	POW_u16AppEnterHighVoltageTimer = 0U;
	    		}
			else
			{
				POW_u16AppLeaveHighVoltageTimer++;
			}
		#else
			 clr_bPowInternalDataAppHighVoltage();
	             	 POW_u16AppEnterHighVoltageTimer = 0U;
		#endif
	}

	/*enter high voltage or super high voltage */
	else if ( POW_u16IgnVolt >= (uint16)(POW_u16AppHighVoltageThresholdIgn+POW_u16AppHighVoltageIgnHystCfg) )
	{		
              if(POW_u16AppEnterHighVoltageTimer >= POW_u16AppEnterHighVolTimerCfgShare)
              {
		      set_bPowInternalDataAppHighVoltage(1);
			POW_u16AppLeaveHighVoltageTimer = 0U;
              }
              else
              {
                    POW_u16AppEnterHighVoltageTimer++;
              }
	}
	
       else
       {       
              /*In the Hysteresis and do nothing*/
       }
}




#if (POW_ComRef==POW_Ref_K30)

/* ===========================================================================
* Function   : void POW_vComLowHighVoltageCheckK30(void)
* Description: this function check the all high or low voltage for communication  .
* Input      : none.
* Returns    : none.
*/
static void POW_vComLowHighVoltageCheckK30 (void)
{
	/*-----------------------------------communication function voltage--------------------------------------*/	
#if  (Com_CheckVoltage==1)
	/*leave com low voltage (7.6v) */
	if ( POW_u16BattVolt >= POW_u16CanLowVoltageThreshold )
	{
		/*avoid warning*/
		POW_u16CanLeaveLowVoltageTimer = POW_u16CanLeaveLowVoltageTimer;
		
		#if POW_u16CanLeaveLowVoltageTimerCfg >0U
			if ( POW_u16CanLeaveLowVoltageTimer >= POW_u16CanLeaveLowVoltageTimerCfg )
			{
				clr_bPowInternalDataComLowVoltage();
				POW_u16CanEnterLowVoltageTimer = 0U;
			}
			else
			{
				POW_u16CanLeaveLowVoltageTimer++;
			}
		#else
			clr_bPowInternalDataComLowVoltage();
			POW_u16CanEnterLowVoltageTimer = 0U;
		#endif
	}
	
	/* enter com low voltage (6.7v) */
	else if ( POW_u16BattVolt <= (uint16)(POW_u16CanLowVoltageThreshold-POW_u16CanLowVoltageHystCfg) )
	{
		/*avoid warning*/
		POW_u16CanEnterLowVoltageTimer = POW_u16CanEnterLowVoltageTimer;
		
		#if POW_u16CanEnterLowVoltageTimerCfg >0U
			if ( POW_u16CanEnterLowVoltageTimer >= (uint8)POW_u16CanEnterLowVoltageTimerCfg )
			{
				set_bPowInternalDataComLowVoltage(1);
				POW_u16CanLeaveLowVoltageTimer = 0U;
			}
			else
			{
				POW_u16CanEnterLowVoltageTimer++;
			}
		#else
			set_bPowInternalDataComLowVoltage(1);
			POW_u16CanLeaveLowVoltageTimer = 0U;
		#endif
	}
	
	else
	{
		  /*In the Hysteresis and do nothing*/
	}

	/* leave com hi voltage (18v)*/
	if ( POW_u16BattVolt <= POW_u16CanHighVoltageThreshold )
	{
		/*avoid warning*/
		POW_u16CanLeaveHighVoltageTimer = POW_u16CanLeaveHighVoltageTimer;
		
		#if POW_u16CanLeaveHighVoltageTimerCfg >0U
			if ( POW_u16CanLeaveHighVoltageTimer >= (uint8)POW_u16CanLeaveHighVoltageTimerCfg )
			{
				clr_bPowInternalDataComHighVoltage();
				POW_u16CanEnterHighVoltageTimer = 0U;
			}
			else
			{
				POW_u16CanLeaveHighVoltageTimer++;
			}
		#else
			clr_bPowInternalDataComHighVoltage();
			POW_u16CanEnterHighVoltageTimer = 0U;
		#endif
	}
	/* enter com hi voltage (18.5v)*/
	else if ( POW_u16BattVolt >= (uint16)(POW_u16CanHighVoltageThreshold+POW_u16CanHighVoltageHystCfg) )
	{
		/*avoid warning*/
		POW_u16CanEnterHighVoltageTimer = POW_u16CanEnterHighVoltageTimer;
		
		#if POW_u16CanEnterHighVoltageTimerCfg >0U
			if ( POW_u16CanEnterHighVoltageTimer >= (uint8)POW_u16CanEnterHighVoltageTimerCfg )
			{
				set_bPowInternalDataComHighVoltage(1);
				POW_u16CanLeaveHighVoltageTimer =0U;
			}
			else
			{
				POW_u16CanEnterHighVoltageTimer++;
			}
		#else
			set_bPowInternalDataComHighVoltage(1);
			POW_u16CanLeaveHighVoltageTimer =0U;
		#endif
	}
        else
        {
		/*In the Hysteresis and do nothing*/
        }
#endif
}

#endif
/* ===========================================================================
* Function   : void POW_vComLowHighVoltageCheckK15(void)
* Description: this function check the all high or low voltage for communication  .
* Input      : none.
* Returns    : none.
*/
static void POW_vComLowHighVoltageCheckK15 (void)
{
	/*-----------------------------------communication function voltage--------------------------------------*/	
#if  (Com_CheckVoltage==1)
	/*leave com low voltage (7.6v) */
	if ( POW_u16IgnVolt >= POW_u16CanLowVoltageThresholdIgn )
	{
		/*avoid warning*/
		POW_u16CanLeaveLowVoltageTimer = POW_u16CanLeaveLowVoltageTimer;
		
		#if POW_u16CanLeaveLowVoltageTimerCfg >0U
			if ( POW_u16CanLeaveLowVoltageTimer >= POW_u16CanLeaveLowVoltageTimerCfg )
			{
				clr_bPowInternalDataComLowVoltage();
				POW_u16CanEnterLowVoltageTimer = 0U;
			}
			else
			{
				POW_u16CanLeaveLowVoltageTimer++;
			}
		#else
			clr_bPowInternalDataComLowVoltage();
			POW_u16CanEnterLowVoltageTimer = 0U;
		#endif
	}
	
	/* enter com low voltage (6.7v) */
	else if ( POW_u16IgnVolt <= (uint16)(POW_u16CanLowVoltageThresholdIgn-POW_u16CanLowVoltageIgnHystCfg) )
	{
		/*avoid warning*/
		POW_u16CanEnterLowVoltageTimer = POW_u16CanEnterLowVoltageTimer;
		
		#if POW_u16CanEnterLowVoltageTimerCfg >0U
			if ( POW_u16CanEnterLowVoltageTimer >= (uint8)POW_u16CanEnterLowVoltageTimerCfg )
			{
				set_bPowInternalDataComLowVoltage(1);
				POW_u16CanLeaveLowVoltageTimer = 0U;
			}
			else
			{
				POW_u16CanEnterLowVoltageTimer++;
			}
		#else
			set_bPowInternalDataComLowVoltage(1);
			POW_u16CanLeaveLowVoltageTimer = 0U;
		#endif
	}
	
	else
	{
		  /*In the Hysteresis and do nothing*/
	}

	/* leave com hi voltage (18v)*/
	if ( POW_u16IgnVolt <= POW_u16CanHighVoltageThresholdIgn )
	{
		/*avoid warning*/
		POW_u16CanLeaveHighVoltageTimer = POW_u16CanLeaveHighVoltageTimer;
		
		#if POW_u16CanLeaveHighVoltageTimerCfg >0U
			if ( POW_u16CanLeaveHighVoltageTimer >= (uint8)POW_u16CanLeaveHighVoltageTimerCfg )
			{
				clr_bPowInternalDataComHighVoltage();
				POW_u16CanEnterHighVoltageTimer = 0U;
			}
			else
			{
				POW_u16CanLeaveHighVoltageTimer++;
			}
		#else
			clr_bPowInternalDataComHighVoltage();
			POW_u16CanEnterHighVoltageTimer = 0U;
		#endif
	}
	/* enter com hi voltage (18.5v)*/
	else if ( POW_u16IgnVolt >= (uint16)(POW_u16CanHighVoltageThresholdIgn+POW_u16CanHighVoltageIgnHystCfg) )
	{
		/*avoid warning*/
		POW_u16CanEnterHighVoltageTimer = POW_u16CanEnterHighVoltageTimer;
		
		#if POW_u16CanEnterHighVoltageTimerCfg >0U
			if ( POW_u16CanEnterHighVoltageTimer >= (uint8)POW_u16CanEnterHighVoltageTimerCfg )
			{
				set_bPowInternalDataComHighVoltage(1);
				POW_u16CanLeaveHighVoltageTimer =0U;
			}
			else
			{
				POW_u16CanEnterHighVoltageTimer++;
			}
		#else
			set_bPowInternalDataComHighVoltage(1);
			POW_u16CanLeaveHighVoltageTimer =0U;
		#endif
	}
        else
        {
		/*In the Hysteresis and do nothing*/
        }
#endif
}



#if (POW_DiagRef==POW_Ref_K30)
/* ===========================================================================
* Function   : void POW_vDiagLowHighVoltageCheckK30(void)
* Description: this function check the all high or low voltage for diagnostic  .
* Input      : none.
* Returns    : none.
*/
static void POW_vDiagLowHighVoltageCheckK30 (void)
{
	/*---------------------------------diagnostic function voltage-----------------------------------------*/
#if  (Diag_CheckVoltage==1)
	
	/*leave diag low voltage*/
	if ( POW_u16BattVolt >= POW_u16DiagLowVoltageThreshold )
	{
		/*avoid warning*/
		POW_u16DiagLeaveLowVoltageTimer = POW_u16DiagLeaveLowVoltageTimer;
		
		#if POW_u16DiagLeaveLowVoltageTimerCfg>0U
			if(POW_u16DiagLeaveLowVoltageTimer >= POW_u16DiagLeaveLowVoltageTimerCfg )
			{
				clr_bPowInternalDataDiagLowVoltage();
				POW_u16DiagEnterLowVoltageTimer = 0U;
			}
			else
			{
				POW_u16DiagLeaveLowVoltageTimer++;
			}
		#else
			clr_bPowInternalDataDiagLowVoltage();
			POW_u16DiagEnterLowVoltageTimer = 0U;
		#endif
	}
	
	/*enter diag low voltage 9.5v*/
	else if ( POW_u16BattVolt <= (uint16)(POW_u16DiagLowVoltageThreshold-POW_u16DiagLowVoltageHystCfg) )
	{
		/*avoid warning*/
		POW_u16DiagEnterLowVoltageTimer = POW_u16DiagEnterLowVoltageTimer;
		
		#if POW_u16DiagEnterLowVoltageTimerCfg>0U
			if ( POW_u16DiagEnterLowVoltageTimer >= POW_u16DiagEnterLowVoltageTimerCfg )
			{
				set_bPowInternalDataDiagLowVoltage(1);
				POW_u16DiagLeaveLowVoltageTimer = 0U;
			}
			else
			{
				POW_u16DiagEnterLowVoltageTimer++;
			}
		#else
			set_bPowInternalDataDiagLowVoltage(1);
			POW_u16DiagLeaveLowVoltageTimer = 0U;
		#endif
	}
	else
	{
		
	}

	/*leave diag high voltage*/
	if ( POW_u16BattVolt <= POW_u16DiagHighVoltageThreshold )
	{
		/*avoid warning*/
		POW_u16DiagLeaveHighVoltageTimer = POW_u16DiagLeaveHighVoltageTimer;
		
		#if POW_u16DiagLeaveHighVoltageTimerCfg>0U
			if ( POW_u16DiagLeaveHighVoltageTimer >= POW_u16DiagLeaveHighVoltageTimerCfg )
			{
				clr_bPowInternalDataDiagHighVoltage();
				POW_u16DiagEnterHighVoltageTimer=0U;
			}
			else
			{
				POW_u16DiagLeaveHighVoltageTimer++;
			}
		#else
			clr_bPowInternalDataDiagHighVoltage();
			POW_u16DiagEnterHighVoltageTimer=0U;
		#endif
	}

	/*enter diag high voltage*/
	else if ( POW_u16BattVolt >= (uint16)(POW_u16DiagHighVoltageThreshold+POW_u16DiagHighVoltageHystCfg) )
	{
		/*avoid warning*/
		POW_u16DiagEnterHighVoltageTimer = POW_u16DiagEnterHighVoltageTimer;
		
		#if POW_u16DiagEnterHighVoltageTimerCfg>0U
			if(POW_u16DiagEnterHighVoltageTimer>=POW_u16DiagEnterHighVoltageTimerCfg)
			{
				set_bPowInternalDataDiagHighVoltage(1);
				POW_u16DiagLeaveHighVoltageTimer = 0U;
			}
			else
			{
				POW_u16DiagEnterHighVoltageTimer++;
			}
		#else
			set_bPowInternalDataDiagHighVoltage(1);
			POW_u16DiagLeaveHighVoltageTimer = 0U;
		#endif
	}
        else
        {
		
        }
#endif
}

#endif
/* ===========================================================================
* Function   : void POW_vDiagLowHighVoltageCheckK15(void)
* Description: this function check the all high or low voltage for diagnostic  .
* Input      : none.
* Returns    : none.
*/
static void POW_vDiagLowHighVoltageCheckK15 (void)
{
	/*---------------------------------diagnostic function voltage-----------------------------------------*/
#if  (Diag_CheckVoltage==1)
	
	/*leave diag low voltage*/
	if ( POW_u16IgnVolt >= POW_u16DiagLowVoltageThresholdIgn )
	{
		/*avoid warning*/
		POW_u16DiagLeaveLowVoltageTimer = POW_u16DiagLeaveLowVoltageTimer;
		
		#if POW_u16DiagLeaveLowVoltageTimerCfg>0U
			if(POW_u16DiagLeaveLowVoltageTimer >= POW_u16DiagLeaveLowVoltageTimerCfg )
			{
				clr_bPowInternalDataDiagLowVoltage();
				POW_u16DiagEnterLowVoltageTimer = 0U;
			}
			else
			{
				POW_u16DiagLeaveLowVoltageTimer++;
			}
		#else
			clr_bPowInternalDataDiagLowVoltage();
			POW_u16DiagEnterLowVoltageTimer = 0U;
		#endif
	}
	
	/*enter diag low voltage 9.5v*/
	else if ( POW_u16IgnVolt <= (uint16)(POW_u16DiagLowVoltageThresholdIgn-POW_u16DiagLowVoltageIgnHystCfg) )
	{
		/*avoid warning*/
		POW_u16DiagEnterLowVoltageTimer = POW_u16DiagEnterLowVoltageTimer;
		
		#if POW_u16DiagEnterLowVoltageTimerCfg>0U
			if ( POW_u16DiagEnterLowVoltageTimer >= POW_u16DiagEnterLowVoltageTimerCfg )
			{
				set_bPowInternalDataDiagLowVoltage(1);
				POW_u16DiagLeaveLowVoltageTimer = 0U;
			}
			else
			{
				POW_u16DiagEnterLowVoltageTimer++;
			}
		#else
			set_bPowInternalDataDiagLowVoltage(1);
			POW_u16DiagLeaveLowVoltageTimer = 0U;
		#endif
	}
	else
	{
		
	}

	/*leave diag high voltage*/
	if ( POW_u16IgnVolt <= POW_u16DiagHighVoltageThresholdIgn )
	{
		/*avoid warning*/
		POW_u16DiagLeaveHighVoltageTimer = POW_u16DiagLeaveHighVoltageTimer;
		
		#if POW_u16DiagLeaveHighVoltageTimerCfg>0U
			if ( POW_u16DiagLeaveHighVoltageTimer >= POW_u16DiagLeaveHighVoltageTimerCfg )
			{
				clr_bPowInternalDataDiagHighVoltage();
				POW_u16DiagEnterHighVoltageTimer=0U;
			}
			else
			{
				POW_u16DiagLeaveHighVoltageTimer++;
			}
		#else
			clr_bPowInternalDataDiagHighVoltage();
			POW_u16DiagEnterHighVoltageTimer=0U;
		#endif
	}

	/*enter diag high voltage*/
	else if ( POW_u16IgnVolt >= (uint16)(POW_u16DiagHighVoltageThresholdIgn+POW_u16DiagHighVoltageIgnHystCfg) )
	{
		/*avoid warning*/
		POW_u16DiagEnterHighVoltageTimer = POW_u16DiagEnterHighVoltageTimer;
		
		#if POW_u16DiagEnterHighVoltageTimerCfg>0U
			if(POW_u16DiagEnterHighVoltageTimer>=POW_u16DiagEnterHighVoltageTimerCfg)
			{
				set_bPowInternalDataDiagHighVoltage(1);
				POW_u16DiagLeaveHighVoltageTimer = 0U;
			}
			else
			{
				POW_u16DiagEnterHighVoltageTimer++;
			}
		#else
			set_bPowInternalDataDiagHighVoltage(1);
			POW_u16DiagLeaveHighVoltageTimer = 0U;
		#endif
	}
        else
        {
		
        }
#endif
}

#if (POW_Ref4==POW_Ref_K30)
/* ===========================================================================
* Function   : void POW_vRef4LowHighVoltageCheckK30(void)
* Description: this function check the all high or low voltage for ref4  .
* Input      : none.
* Returns    : none.
*/
static void POW_vRef4LowHighVoltageCheckK30 (void)
{
	/*---------------------------------ref4 function voltage-----------------------------------------*/
#if  (Ref4_CheckVoltage==1)
	
	/*leave Ref4 low voltage*/
	if ( POW_u16BattVolt >= POW_u16Ref4LowVoltageThreshold )
	{
		/*avoid warning*/
		POW_u16Ref4LeaveLowVoltageTimer = POW_u16Ref4LeaveLowVoltageTimer;
		
		#if POW_u16Ref4LeaveLowVoltageTimerCfg>0U
			if(POW_u16Ref4LeaveLowVoltageTimer >= POW_u16Ref4LeaveLowVoltageTimerCfg )
			{
				clr_bPowInternalDataRef4LowVoltage();
				POW_u16Ref4EnterLowVoltageTimer = 0U;
			}
			else
			{
				POW_u16Ref4LeaveLowVoltageTimer++;
			}
		#else
			clr_bPowInternalDataRef4LowVoltage();
			POW_u16Ref4EnterLowVoltageTimer = 0U;
		#endif
	}
	
	/*enter Ref4 low voltage 9.5v*/
	else if ( POW_u16BattVolt <= (uint16)(POW_u16Ref4LowVoltageThreshold-POW_u16Ref4LowVoltageHystCfg) )
	{
		/*avoid warning*/
		POW_u16Ref4EnterLowVoltageTimer = POW_u16Ref4EnterLowVoltageTimer;
		
		#if POW_u16Ref4EnterLowVoltageTimerCfg>0U
			if ( POW_u16Ref4EnterLowVoltageTimer >= POW_u16Ref4EnterLowVoltageTimerCfg )
			{
				set_bPowInternalDataRef4LowVoltage(1);
				POW_u16Ref4LeaveLowVoltageTimer = 0U;
			}
			else
			{
				POW_u16Ref4EnterLowVoltageTimer++;
			}
		#else
			set_bPowInternalDataRef4LowVoltage(1);
			POW_u16Ref4LeaveLowVoltageTimer = 0U;
		#endif
	}
	else
	{
		
	}

	/*leave Ref4 high voltage*/
	if ( POW_u16BattVolt <= POW_u16Ref4HighVoltageThreshold )
	{
		/*avoid warning*/
		POW_u16Ref4LeaveHighVoltageTimer = POW_u16Ref4LeaveHighVoltageTimer;
		
		#if POW_u16Ref4LeaveHighVoltageTimerCfg>0U
			if ( POW_u16Ref4LeaveHighVoltageTimer >= POW_u16Ref4LeaveHighVoltageTimerCfg )
			{
				clr_bPowInternalDataRef4HighVoltage();
				POW_u16Ref4EnterHighVoltageTimer=0U;
			}
			else
			{
				POW_u16Ref4LeaveHighVoltageTimer++;
			}
		#else
			clr_bPowInternalDataRef4HighVoltage();
			POW_u16Ref4EnterHighVoltageTimer=0U;
		#endif
	}

	/*enter Ref4 high voltage*/
	else if ( POW_u16BattVolt >= (uint16)(POW_u16Ref4HighVoltageThreshold+POW_u16Ref4HighVoltageHystCfg) )
	{
		/*avoid warning*/
		POW_u16Ref4EnterHighVoltageTimer = POW_u16Ref4EnterHighVoltageTimer;
		
		#if POW_u16Ref4EnterHighVoltageTimerCfg>0U
			if(POW_u16Ref4EnterHighVoltageTimer>=POW_u16Ref4EnterHighVoltageTimerCfg)
			{
				set_bPowInternalDataRef4HighVoltage(1);
				POW_u16Ref4LeaveHighVoltageTimer = 0U;
			}
			else
			{
				POW_u16Ref4EnterHighVoltageTimer++;
			}
		#else
			set_bPowInternalDataRef4HighVoltage(1);
			POW_u16Ref4LeaveHighVoltageTimer = 0U;
		#endif
	}
        else
        {
		
        }
#endif
}

#endif
/* ===========================================================================
* Function   : void POW_vRef4LowHighVoltageCheckK15(void)
* Description: this function check the all high or low voltage for diagnostic  .
* Input      : none.
* Returns    : none.
*/
static void POW_vRef4LowHighVoltageCheckK15 (void)
{
	/*---------------------------------Ref4 function voltage-----------------------------------------*/
#if  (Ref4_CheckVoltage==1)
	
	/*leave Ref4 low voltage*/
	if ( POW_u16IgnVolt >= POW_u16Ref4LowVoltageThresholdIgn )
	{
		/*avoid warning*/
		POW_u16Ref4LeaveLowVoltageTimer = POW_u16Ref4LeaveLowVoltageTimer;
		
		#if POW_u16Ref4LeaveLowVoltageTimerCfg>0U
			if(POW_u16Ref4LeaveLowVoltageTimer >= POW_u16Ref4LeaveLowVoltageTimerCfg )
			{
				clr_bPowInternalDataRef4LowVoltage();
				POW_u16Ref4EnterLowVoltageTimer = 0U;
			}
			else
			{
				POW_u16Ref4LeaveLowVoltageTimer++;
			}
		#else
			clr_bPowInternalDataRef4LowVoltage();
			POW_u16Ref4EnterLowVoltageTimer = 0U;
		#endif
	}
	
	/*enter Ref4 low voltage 9.5v*/
	else if ( POW_u16IgnVolt <= (uint16)(POW_u16Ref4LowVoltageThresholdIgn-POW_u16Ref4LowVoltageIgnHystCfg) )
	{
		/*avoid warning*/
		POW_u16Ref4EnterLowVoltageTimer = POW_u16Ref4EnterLowVoltageTimer;
		
		#if POW_u16Ref4EnterLowVoltageTimerCfg>0U
			if ( POW_u16Ref4EnterLowVoltageTimer >= POW_u16Ref4EnterLowVoltageTimerCfg )
			{
				set_bPowInternalDataRef4LowVoltage(1);
				POW_u16Ref4LeaveLowVoltageTimer = 0U;
			}
			else
			{
				POW_u16Ref4EnterLowVoltageTimer++;
			}
		#else
			set_bPowInternalDataRef4LowVoltage(1);
			POW_u16Ref4LeaveLowVoltageTimer = 0U;
		#endif
	}
	else
	{
		
	}

	/*leave Ref4 high voltage*/
	if ( POW_u16IgnVolt <= POW_u16Ref4HighVoltageThresholdIgn )
	{
		/*avoid warning*/
		POW_u16Ref4LeaveHighVoltageTimer = POW_u16Ref4LeaveHighVoltageTimer;
		
		#if POW_u16Ref4LeaveHighVoltageTimerCfg>0U
			if ( POW_u16Ref4LeaveHighVoltageTimer >= POW_u16Ref4LeaveHighVoltageTimerCfg )
			{
				clr_bPowInternalDataRef4HighVoltage();
				POW_u16Ref4EnterHighVoltageTimer=0U;
			}
			else
			{
				POW_u16Ref4LeaveHighVoltageTimer++;
			}
		#else
			clr_bPowInternalDataRef4HighVoltage();
			POW_u16Ref4EnterHighVoltageTimer=0U;
		#endif
	}

	/*enter Ref4 high voltage*/
	else if ( POW_u16IgnVolt >= (uint16)(POW_u16Ref4HighVoltageThresholdIgn+POW_u16Ref4HighVoltageIgnHystCfg) )
	{
		/*avoid warning*/
		POW_u16Ref4EnterHighVoltageTimer = POW_u16Ref4EnterHighVoltageTimer;
		
		#if POW_u16Ref4EnterHighVoltageTimerCfg>0U
			if(POW_u16Ref4EnterHighVoltageTimer>=POW_u16Ref4EnterHighVoltageTimerCfg)
			{
				set_bPowInternalDataRef4HighVoltage(1);
				POW_u16Ref4LeaveHighVoltageTimer = 0U;
			}
			else
			{
				POW_u16Ref4EnterHighVoltageTimer++;
			}
		#else
			set_bPowInternalDataRef4HighVoltage(1);
			POW_u16Ref4LeaveHighVoltageTimer = 0U;
		#endif
	}
        else
        {
		
        }
#endif
}


/* ===========================================================================
* Function   : void POW_vLowHighVoltageCheck(void)
* Description: this function check the all high or low voltage for app and bus .
* Input      : none.
* Returns    : none.
*/
static void POW_vLowHighVoltageCheck (void)
{	
	#if (POW_AppRef==POW_Ref_K30)
		if (POW_u8BatAbnormalFlag ==False)
		{
			POW_vAppLowHighVoltageCheckK30();
		}
		else
		{
			POW_vAppLowHighVoltageCheckK15();
		}	
	#else
		POW_vAppLowHighVoltageCheckK15();
	#endif
	
	#if (POW_ComRef==POW_Ref_K30)
		if (POW_u8BatAbnormalFlag ==False)
		{
			POW_vComLowHighVoltageCheckK30();
		}
		else
		{
			POW_vComLowHighVoltageCheckK15();
		}
	#else
		{
			POW_vComLowHighVoltageCheckK15();
		}
	#endif
	
	#if (POW_DiagRef==POW_Ref_K30)
		if (POW_u8BatAbnormalFlag ==False)
		{
			POW_vDiagLowHighVoltageCheckK30();
		}
		else
		{
			POW_vDiagLowHighVoltageCheckK15();
		}
	#else
		POW_vDiagLowHighVoltageCheckK15();
	#endif

	#if (POW_Ref4==POW_Ref_K30)
		if (POW_u8BatAbnormalFlag ==False)
		{
			POW_vRef4LowHighVoltageCheckK30();
		}
		else
		{
			POW_vRef4LowHighVoltageCheckK15();
		}
	#else
		POW_vRef4LowHighVoltageCheckK15();
	#endif
}

/* ===========================================================================
* Function   : void POW_vReadBatVoltage(void)
* Description: this function get the battery voltage .
* Input      : none.
* Returns    : none.
*/

static uint16 POW_vReadBatVoltage(void)
{
	uint16 u16temp;
	
	u16temp = POW_u16IDHalK30Fb;
	
	return u16temp;
}

#if (POW_AppRef==POW_Ref_IGN2)||(POW_ComRef==POW_Ref_IGN2)||(POW_DiagRef==POW_Ref_IGN2)||(POW_K30Abnormal ==  1)
/* ===========================================================================
* Function   : void POW_vReadBatVoltage(void)
* Description: this function get the battery voltage .
* Input      : none.
* Returns    : none.
*/

static uint16 POW_vReadIgnVoltage(void)
{
	uint16 u16temp;

	u16temp = POW_u16IDHalIgn2Fb;
	
	return u16temp;
}
#endif

#if (POW_K30Abnormal ==  1)

/* ===========================================================================
* Function   : void POW_vVoltageAbnormalCheck(void)
* Description: if the k30 lost .
* Input      : none.
* Returns    : none.
*/
static void POW_vVoltageAbnormalCheck(void)
{
	/*k30 vs k15*/
	uint32 u32BatVolTemp,u32IgnVolTemp, u32HystCfgTemp;
	u32BatVolTemp=(uint32)POW_u16BattVolt*POW_SupplyVoltK30Coefficient;
	u32IgnVolTemp=(uint32)POW_u16IgnVolt*POW_SupplyVoltIgnCoefficient;
	u32HystCfgTemp = (uint32)POW_u16BatShortGndHystCfg;

	if(u32IgnVolTemp > u32HystCfgTemp)	/*be sure ign -hyst > 0*/
	{
		
		 if(u32BatVolTemp >= u32IgnVolTemp)
		{
			/*k30>=k15*/
			POW_u8BatAbnormalFlag =False;
		}
		else if( u32BatVolTemp< (u32IgnVolTemp-u32HystCfgTemp))
		{
			/*k15-k30>1v then use k15*/
			POW_u8BatAbnormalFlag =1;	
		}
		else
		{
			/*hold current state*/
			
		}
	}
	else
	{
		/*k15 is low then don't use it*/
		POW_u8BatAbnormalFlag =False;
		
	}	
	
	
}
#endif

/* ===========================================================================
* Function   : void POW_vVoltageCheck(void)
* Description: this function get the battery voltage and check high or low .
* Input      : none.
* Returns    : none.
*/
static void POW_vVoltageCheck (void)
{
	
	
	/* pts k30*/
	if(POW_tstPtsStatus.POW_u8K30VoltageFbFlag == 1)
	{				
		POW_u16BattVolt  = POW_tstPtsStatus.POW_u16K30VoltageFbValue;
		#if (POW_AppRef==POW_Ref_IGN2)||(POW_ComRef==POW_Ref_IGN2)||(POW_DiagRef==POW_Ref_IGN2)||(POW_K30Abnormal ==  1)
		POW_u16IgnVolt = POW_u16BattVolt;
		#endif
		
	}
	/*pts k15*/
	else if(POW_tstPtsStatus.POW_u8K15VoltageFbFlag == 1)
	{
		#if (POW_AppRef==POW_Ref_IGN2)||(POW_ComRef==POW_Ref_IGN2)||(POW_DiagRef==POW_Ref_IGN2)||(POW_K30Abnormal ==  1)
			POW_u16IgnVolt = POW_tstPtsStatus.POW_u16K15VoltageFbValue;
		#endif

	}
	/*read voltage from ad normally*/
	else
	{	
		/*read volatge from ad*/
		
		POW_u16BattVolt = POW_vReadBatVoltage();
		
		
		#if (POW_AppRef==POW_Ref_IGN2)||(POW_ComRef==POW_Ref_IGN2)||(POW_DiagRef==POW_Ref_IGN2)||(POW_K30Abnormal ==  1)
			POW_u16IgnVolt = POW_vReadIgnVoltage();				
		#endif
	}

	/* use ign value if bat is abnormal*/
	#if (POW_K30Abnormal ==  1)
	POW_vVoltageAbnormalCheck();
	#endif		
	
	/* check*/
	POW_vLowHighVoltageCheck();

	/* call by external module*/
	#if (POW_AppRef==POW_Ref_K30)	
		set_bPowInternalDataResultK30VoltFb(POW_SupplyVot_10Times(POW_u16BattVolt));
	#else 
		set_bPowInternalDataResultIGN2VoltFb(POW_SupplyVot_10Times(POW_u16IgnVolt));
	
	#endif

	
}


/* ===========================================================================
 Function      : POW_v5vOutputFb                                   *
 Description   : 5v output fb . 				   *
* Input      : none.
* Returns    :none.
*/
static void POW_v5vOutputFbPro(void)
{
	/*record 5v output feedback voltage*/
	if(POW_tstPtsStatus.POW_u85vOutPutFbFlag == 1)
	{
		set_bPowInternalData5vOutputFb(POW_tstPtsStatus.POW_u165vOutPutFbValue);
	}
	else
	{
		set_bPowInternalData5vOutputFb( POW_u16IDHalRaw5vOutputFb);
		
	}
}

/* ===========================================================================
 Function      : POW_v5vOutputCtrl                                    *
 Description   : 5v output check. 				   *
* Input      : none.
* Returns    :none.
*/
static void POW_v5vOutputCtrl(void)
{	
	/*pts control*/
	if(POW_tstPtsStatus.POW_u85vOutPutFbFlag == 1)
	{
		return;
	}

	/* 5v output control when system is  on state*/
	if(( POW_u8IDIgnStaticOn == 1))
	{
		if((get_bPowInternalDataAppHighVoltage()==1)||(get_bPowInternalDataAppLowVoltage() ==1))
		{
			
			POW_v5vOutputDisable();
		}

		else if((get_bPowInternalDataAppHighVoltage()==False)&&(get_bPowInternalDataAppLowVoltage() ==False))
		{
			POW_v5vOutputEnable();
		}

		else
		{
			/*no this case*/
		}
	}
	else
	{
		#if (POW_5VOutputCfgIfIgnOff==1)
		{
			POW_v5vOutputEnable()
		}
		#else
		{
			POW_v5vOutputDisable();
		}
		#endif
	}
}

/* ===========================================================================
 Function      : POW_vSensor5vOutputCtrl                                    *
 Description   : 5v output check. 				   *
* Input      : none.
* Returns    :none.
*/
static void POW_vSensor5vOutputCtrl(void)
{	
	/*pts control*/
	if(POW_tstPtsStatus.POW_u8SensorFbFlag == 1)
	{
		return;
	}

	/* 5v output control when system is  on state*/
	if(( POW_u8IDIgnStaticOn == 1))
	{
		if((get_bPowInternalDataAppHighVoltage()==1)||(get_bPowInternalDataAppLowVoltage() ==1))
		{
			
			POW_vSensorSupplyDisable();
		}

		else if((get_bPowInternalDataAppHighVoltage()==False)&&(get_bPowInternalDataAppLowVoltage() ==False))
		{
			POW_vSensorSupplyEnable();
		}

		else
		{
			/*no this case*/
		}
	}
	else
	{
		POW_vSensorSupplyDisable();
	}
}

#if (POW_SensorSupplyFbUsed ==1)
/* ===========================================================================
* Function      : POW_v5vSensorFbCheck                                             *
* Description   : 5v output check.      						   *
* Input      : none.
* Returns    :none.
*/
static void POW_v5vSensorFbCheck(void)
{
	
	/* 5v sensor feedback detect when k15 is on*/	
	if(( POW_u8IDIgnStaticOn== 1)&&(POW_u8IDIgnStable==1))
	{
		if((get_bPowInternalDataAppHighVoltage()==False)&&(get_bPowInternalDataAppLowVoltage() ==False))
		{
			if(POW_u16IDHal5vSensorFb<=POW_u165vSensorMin)
			{

				if(POW_u8EC5VSensorTime>=POW_u85vSensorLimitTimeCfg)
				{
					POW_Set5vShortGnd;
				}
				else
				{
					POW_u8EC5VSensorTime++;
				}
			}
			else
			{
				POW_u8EC5VSensorTime = 0U;
				POW_Clr5vShortGnd;

			}
		}
		else
		{
			/*do nothing*/
		}
	}
	else
	{
		POW_u8EC5VSensorTime = 0U;
		POW_Clr5vShortGnd;
	}
	
}

#endif

/* ===========================================================================
 Function      : POW_vAdValidCheck                                             *
 Description   : when the system go to on state and delay some tims then set the ad valid other module can use ad 
 			value when this flag set to 1*    
* Input      : none.
* Returns    :none.
*/

static void POW_vAdValidCheck(void)
{	
	if((POW_u8IDIgnStaticOn == 1)&&(POW_u8IDIgnStable==1))
	{
		if((get_bPowInternalDataAppHighVoltage()==False)&&(get_bPowInternalDataAppLowVoltage() ==False))
		{
			if(POW_u8AdValidTime>=POW_u8AdValidTimeCfg)
			{
				set_bPowInternalDataAdValid(1);
			}
			else
			{
				POW_u8AdValidTime++;
				clr_bPowInternalDataAdValid();
			}
		}
		else
		{
			POW_u8AdValidTime = 0x00U;
			clr_bPowInternalDataAdValid();
		}
		
	}
	else
	{
		POW_u8AdValidTime = 0x00U;
		clr_bPowInternalDataAdValid();
	}
	
}

/* ===========================================================================
 Function      : POW_v5vOutputStableCheck                                             *
 Description   : when the system go to on state and detect the 5v output more than 4.5v and keep 200ms then set the 5v output stable flag
 			value when this flag set to 1*    this function must be call after POW_v5vOutputCtrl()
* Input      : none.
* Returns    :none.
*/
static void POW_v5vOutputStableCheck(void)
{	
	if(( POW_u8IDIgnStaticOn == 1)&&(POW_u8IDIgnStable == 1))
	{
		if((get_bPowInternalDataAppHighVoltage()==False)&&(get_bPowInternalDataAppLowVoltage() ==False))
		{
			if(POW_u16IDHalRaw5vOutputFb >POW_u165vStableVolCfg)
			{
				if(POW_u85vStableTime>=POW_u85vStableTimeCfg)
				{
					set_bPowInternalData5vOutputStable(1);
				}
				else
				{
					POW_u85vStableTime++;
					clr_bPowInternalData5vOutputStable();
				}
			}
			else
			{
				POW_u85vStableTime = 0x00U;
				clr_bPowInternalData5vOutputStable();
			}
		}
		else
		{
			POW_u85vStableTime = 0x00U;
			clr_bPowInternalData5vOutputStable();
		}
		
	}
	else
	{
		POW_u85vStableTime = 0x00U;
		clr_bPowInternalData5vOutputStable();
	}

	
	
}






/* ===========================================================================
* Function   : void POW_vMain(void)
* Description: voltage check and 5voutput control and 5v sensor feedback detect and ad valid.
* Input      : none.
* Returns    : none.
*/
void POW_vMain(void)
{
	
	/*update internal data*/
	POW_vIDInputUpdate();
	
	/* battery voltage detect*/
	POW_vVoltageCheck();

	/*5v output feedback process*/
	POW_v5vOutputFbPro();

	/*5v output control*/
	POW_v5vOutputCtrl();

    /*Sensor 5v output control*/
    POW_vSensor5vOutputCtrl();
    
	/*5v sensor supply feedback detect*/
	#if (POW_SensorSupplyFbUsed ==1)
		POW_v5vSensorFbCheck();/*if 5v sensor does not operate on active,you will not call this function here*/
	#endif

	/*ad valid flag detect*/
	POW_vAdValidCheck();

	/*5v output stable flag detect*/
	POW_v5vOutputStableCheck();	

	/*hmi output update*/
	POW_vIDOutputUpdate();	
	
}

void POW_vObdMain(void)
{
        
}

void POW_vActive(void)
{
        
}

void POW_vDeinit(void)
{
        
}


/*****************************************************************************
 Function      : POW_u16ForceIoControl_5vFb_Set                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static uint16  POW_u16ForceIoControl_5vFb_Set(uint16 ForceIoControlWord)
{
	uint16 u16retvalue;
	u16retvalue =0U;
	POW_tstPtsStatus.POW_u85vOutPutFbFlag = 1;
	POW_tstPtsStatus.POW_u165vOutPutFbValue = ForceIoControlWord;

	u16retvalue =1U;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_u16ForceIoControl_5vFb_Set                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static uint16  POW_u16ForceIoControl_5vFb_Clr(void)
{
	uint16 u16retvalue;
	u16retvalue =0U;
	POW_tstPtsStatus.POW_u85vOutPutFbFlag = False;
	POW_tstPtsStatus.POW_u165vOutPutFbValue = 0U;
	u16retvalue =1U;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_u16ForceIoControl_5vFb_Set                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static uint16  POW_u16ForceIoControl_Sensor5vFb_Set(uint16 ForceIoControlWord)
{
	uint16 u16retvalue;
	u16retvalue =0U;
	POW_tstPtsStatus.POW_u8SensorFbFlag = 1;
	POW_tstPtsStatus.POW_u16SensorFbValue = ForceIoControlWord;

	u16retvalue =1U;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_u16ForceIoControl_5vFb_Set                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static uint16  POW_u16ForceIoControl_Sensor5vFb_Clr(uint16 ForceIoControlWord)
{
	uint16 u16retvalue;
	u16retvalue =0U;
	POW_tstPtsStatus.POW_u8SensorFbFlag = False;
	POW_tstPtsStatus.POW_u16SensorFbValue = 0U;
	u16retvalue =1U;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_u16ForceIoControl_K30Fb_Set                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static uint16  POW_u16ForceIoControl_K30Fb_Set(uint16 ForceIoControlWord)
{
	uint16 u16retvalue;
	u16retvalue =0U;
	POW_tstPtsStatus.POW_u8K30VoltageFbFlag = 1;
	POW_tstPtsStatus.POW_u16K30VoltageFbValue = ForceIoControlWord;
	u16retvalue =1U;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_u16ForceIoControl_K30Fb_Clr                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static uint16  POW_u16ForceIoControl_K30Fb_Clr(void)
{
	uint16 u16retvalue;
	u16retvalue =0U;
	POW_tstPtsStatus.POW_u8K30VoltageFbFlag = False;
	POW_tstPtsStatus.POW_u16K30VoltageFbValue = 0U;
	u16retvalue =1U;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_u16ForceIoControl_K15Fb_Set                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static uint16  POW_u16ForceIoControl_K15Fb_Set(uint16 ForceIoControlWord)
{
	uint16 u16retvalue;
	u16retvalue =0U;
	POW_tstPtsStatus.POW_u8K15VoltageFbFlag = 1;
	POW_tstPtsStatus.POW_u16K15VoltageFbValue = ForceIoControlWord;
	u16retvalue =1U;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_u16ForceIoControl_K15Fb_Clr                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static uint16  POW_u16ForceIoControl_K15Fb_Clr(void)
{
	uint16 u16retvalue;
	u16retvalue =0U;
	POW_tstPtsStatus.POW_u8K15VoltageFbFlag = False;
	POW_tstPtsStatus.POW_u16K15VoltageFbValue = 0U;
	u16retvalue =1U;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_u16ForceIoControl_5vOutputCtrl                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static uint16  POW_u16ForceIoControl_5vOutputCtrl(uint16 ForceIoControlWord)
{
	uint16 u16retvalue;
	u16retvalue =0U;
	if(ForceIoControlWord==0x01)
	{		
		POW_tstPtsStatus.POW_u85vOutPutCtrlFlag = 1;
		POW_tstPtsStatus.POW_u165vOutPutCtrlValue = 1U;
		POW_v5vOutputEnable();
	}
	else
	{
		POW_tstPtsStatus.POW_u85vOutPutCtrlFlag = False;
		POW_tstPtsStatus.POW_u165vOutPutCtrlValue = 0U;
		POW_v5vOutputDisable();
	}
	u16retvalue =1U;
	return (u16retvalue);
}

//#if (POW_SensorSupplyFbUsed==1)
/*****************************************************************************
 Function      : POW_u16ForceIoControl_SensorSupplyCtrl                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static uint16  POW_u16ForceIoControl_SensorSupplyCtrl(uint16 ForceIoControlWord)
{
	uint16 u16retvalue;
	u16retvalue =0U;
	if(ForceIoControlWord==0x01)
	{		
		POW_tstPtsStatus.POW_u8SensorSupplyCtrlFlag = 1;
		POW_tstPtsStatus.POW_u16SensorSupplyValue = 1U;
		POW_vSensorSupplyEnable();
	}
	else
	{
		POW_tstPtsStatus.POW_u8SensorSupplyCtrlFlag = False;
		POW_tstPtsStatus.POW_u16SensorSupplyValue = 0U;
		POW_vSensorSupplyDisable();
	}
	u16retvalue =1U;
	return (u16retvalue);
}
//#endif

/*****************************************************************************
 Function      : POW_u8ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType POW_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
{
	uint8 u8Result=0;
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;				/*pts data */
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);			/*pts cmd*/
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);		/*pts switch*/
	if(CcpControlWord.CcpCommandFlag==1)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0x00:
				POW_u16ClrPtsStatus();
				break;
			case 0x01:
				#if (POW_5vOutputFbUsed==1)
					POW_u16ForceIoControl_5vFb_Set(CcpControlWord.CcpContronData);
				#endif
				break;
			case 0x02:
				#if (POW_5vOutputFbUsed==1)
					POW_u16ForceIoControl_5vFb_Clr();
				#endif
				break;
			case 0x03:
				#if (POW_K30FbUsed==1)
					POW_u16ForceIoControl_K30Fb_Set(CcpControlWord.CcpContronData);
				#endif
				break;
			case 0x04:
				#if (POW_K30FbUsed==1)
					POW_u16ForceIoControl_K30Fb_Clr();
				#endif
				break;
			case 0x05:
				#if (POW_Ign2FbUsed==1)
					POW_u16ForceIoControl_K15Fb_Set(CcpControlWord.CcpContronData);
				#endif
				break;
			case 0x06:
				#if (POW_Ign2FbUsed==1)
					POW_u16ForceIoControl_K15Fb_Clr();
				#endif
				break;
			case 0x81:
				#if (POW_5vOutPutCtrlUsed==1)
                    POW_u16ForceIoControl_5vFb_Set(CcpControlWord.CcpContronData);
					POW_u16ForceIoControl_5vOutputCtrl(CcpControlWord.CcpContronData);
				#endif
				break;
			case 0x82:
				//#if (POW_SensorSupplyFbUsed==1)
                POW_u16ForceIoControl_Sensor5vFb_Set(CcpControlWord.CcpContronData);
				POW_u16ForceIoControl_SensorSupplyCtrl(CcpControlWord.CcpContronData);
				//#endif
				break;
			
			default:				
                		u8Result= 1;
				break;
		}
	}
	else
	{
		POW_u16ClrPtsStatus();
	}
        return u8Result;
}



#endif
/*****************************************************************************
* EOF:
******************************************************************************/


