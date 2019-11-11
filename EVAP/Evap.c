/*******************************************************************************
| Module Name: start stop Function module(Idle engine stop )
| File Name: EVAP.c
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
| 2016-2-18     1.1  Luo Xindian		Modified for KC-2
| 2016-4-15		1.2	 Luo Xindian		adapt to all the project after configured
********************************************************************************/
#define 	EVAP1C1

/* System-headerfiles */
#include "General.h"
#include "Rte_internal.h"
#include "Frame_if.h"
#include "Pow.h"

/* Foreign headerfiles*/
#include "ALG.h"
/*--own headfile--*/
#include "EVAP.H"
#include "Evap_Cfg.h"
#include "Evap_Private.h" 
#include "Evap_Type.h"

/*Filter for AC mode*/
static uint32 EVAP_u32ACValueOld;
static uint8 EVAP_biFilterInit;

static uint8 EVAP_au8Array[EVAP_nu8Max];
static uint16 EVAP_au16Array[EVAP_nu16Max];

static tstEVAPFilterConstantType EVAP_stFilterParam;
static tstEVAPFilterVariableType  EVAP_stFilterVar;

static void EVAP_vFilterInit(void);
static void EVAP_vRawValueHandle(uint16 InputValue);
static void EVAP_vTempFilter(void);

static uint8 EVAP_u8SensorFilter(const tstEVAPFilterConstantType SensorPar[], tstEVAPFilterVariableType SensorVar[]);

#if(EVAP_nMacEvapOffsetCfg ==True)
static uint16 EVAP_u16SensorTempOffset(void);
static uint16 Evap_u8OatTempOffset (uint16 u16InputBlowerSpd,uint16 u16OATvalue);
static uint16 Evap_u8IctTempOffset (uint16 u16InputBlowerSpd,uint16 u16ICTvalue);
#endif

#if (EVAP_nDynOffsCfg == True)
/*Filter for Filter old value*/
static uint16 EVAP_u16PtaValueOld;

static uint16 EVAP_u16CalEvapDiffTempOffset (const uint16 u16InputDiff);		
#endif

#if (EVAP_nMacEvapTempCfg == True)
/*Filter for MAC mode*/
static uint32 EVAP_u32MacValueOld;
//static uint8 EVAP_u8FilterCounter;

void EVAP_vSlowTemp(uint16 u16EvapTemp);
#endif

/* CCP HANDLE*/
#if (EVAP_nUseCCP == True)
static uint8 EVAP_u8CcpForceFlag=0;
static uint16 EVAP_au16CcpControlData[EVAP_nCcpForceMax];

static void EVAP_vCcpInputForce(void);
static void EVAP_vCcpOutputForce(void);

/*****************************************************************************
 Function      : Evap_ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType EVAP_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
{
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0x00:
				EVAP_vClrCcpForceByte();
				break;
			case 0x01:/* enforce control the RFA position */
				EVAP_vSetCcpForceBit(EVAP_nSetSensorAD);
				EVAP_au16CcpControlData[EVAP_nSetSensorAD]=CcpControlWord.CcpContronData;
				break;
			case 0x02:/* cancel the position enforce control*/
				EVAP_vClrCcpForceBit(EVAP_nSetSensorAD);
				EVAP_au16CcpControlData[EVAP_nSetSensorAD]=0;
				break;
			case 0x03:/*  enforce the recir time*/
				EVAP_vSetCcpForceBit(EVAP_nSetSensorTemp);
				EVAP_au16CcpControlData[EVAP_nSetSensorTemp]=CcpControlWord.CcpContronData;
 				break;
			case 0x04:/*  cancel enforce the recir time*/
				EVAP_vClrCcpForceBit(EVAP_nSetSensorTemp);
				EVAP_au16CcpControlData[EVAP_nSetSensorTemp]=0;
				break;
			default:
                return RTE_E_INVALID;
				//break;
		}
	}
	else
	{
		EVAP_vClrCcpForceByte();
	}
        return RTE_E_OK;
}

/*****************************************************************************
 Function      : EVAP_vCcpInputForce                                 
 Description   : force Input value
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void EVAP_vCcpInputForce(void)
{	
	if(EVAP_vGetCcpForceBit(EVAP_nSetSensorAD)== True)
	{
		EVAP_u16SensorAdValue =EVAP_au16CcpControlData[EVAP_nSetSensorAD];
	}
	else
	{
	}
}

/*****************************************************************************
 Function      : Evap_vCcpOutputForce                                 
 Description   : force output value
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void EVAP_vCcpOutputForce(void)
{	
	if(EVAP_vGetCcpForceBit(EVAP_nSetSensorTemp))
	{
		EVAP_u16FastEvapTemp=EVAP_au16CcpControlData[EVAP_nSetSensorTemp];

		#if (EVAP_nMacEvapTempCfg == True)
		EVAP_u16MacValue=EVAP_au16CcpControlData[EVAP_nSetSensorTemp];
		#endif
	}
	else
	{
	}
}

#endif

/* ===========================================================================
* Function   : void EVAP_vReset (void)
* Description: Reset function of the heater core temperature model.
* Takes      : Nothing
* Returns    : Nothing
*/
void EVAP_vReset (void)
{
	uint8 u8i=0U;
	EVAP_biFilterInit	=False;

	#if (EVAP_nDynOffsCfg == True)
	EVAP_u16PtaValueOld = 0;
	#endif
	
	#if (EVAP_nMacEvapTempCfg == True)
	EVAP_u32MacValueOld=0;
	//EVAP_u8FilterCounter=0;
	#endif

	EVAP_u32ACValueOld=0U;

	for (u8i=0U; u8i<EVAP_nu8Max; u8i++ )
	{
		EVAP_au8Array[u8i] = 0;
	}
	for ( u8i=0U; u8i<EVAP_nu16Max; u8i++ )
	{
		EVAP_au16Array[u8i] = 0;
	}

	EVAP_stFilterParam.au16Raw = (uint16 *)&EVAP_au16GroupEvapTemp_X[0];
	EVAP_stFilterParam.au16Result = (uint16 *)&EVAP_au16GroupEvapTemp_Y[0];
	EVAP_stFilterParam.u16MaxLimitValue = EVAP_nMaxLimitValue;
	EVAP_stFilterParam.u16MinLimitValue = EVAP_nMinLimitValue;
	EVAP_stFilterParam.u16SensorDefaultValue = EVAP_nSensorDefaultValue;
	EVAP_stFilterParam.u8ErrorCountTimeout = EVAP_nErrorCountTimeout;
	EVAP_stFilterParam.u8FilterParameter = EVAP_nFilterParameter;
	EVAP_stFilterParam.u8Length = EVAP_nEvapTempTbl_Len;

	EVAP_stFilterVar.u32InterimValue=0u;
	EVAP_stFilterVar.u16SensorValue =400u;
	EVAP_stFilterVar.u8ErrorCountL =0u;
	EVAP_stFilterVar.u8ErrorCountH =0u;
	EVAP_stFilterVar.u8SensorErrorFlag=0u;
	EVAP_stFilterVar.u8InitFlag = biColdBoot;
	
	EVAP_u8SwVersion = EVAP_nSwVersion;/*According to the header define*/

	#if( EVAP_nUseRTE == True)
	Rte_IWrite_Evap_vReset_EvapSwVersion_u8Version(EVAP_u8SwVersion);
	
	Rte_IWrite_Evap_vMain_EvapAcValue_u16Temp(0);
	Rte_IWrite_Evap_vMain_EvapValid_u8Flag(0);
	Rte_IWrite_Evap_vMain_EvapMacValue_u16Temp(0);
	#endif

	#if (EVAP_nUseCCP == True)
	EVAP_vClrCcpForceByte();
	#endif
}

/* ===========================================================================
* Function   : void EVAP_vInit (void)
* Description: Init function of the heater core temperature model. This
*              function is called in the transition from the active to the ON
*              state.
* Takes      : Nothing
* Returns    : Nothing
*/
void EVAP_vInit (void)
{
	EVAP_vReset ();
}

/* ===========================================================================
* Function   : void EVAP_vDeinit (void)
* Description: This is On the ignition->off transition function for the EVAP module.
* Takes      : None
* Returns    : None
*/
  void EVAP_vDeinit (void)
{
	/*Nothing to do*/
}

static uint8 EVAP_u8SensorFilter(const tstEVAPFilterConstantType *SensorPar, tstEVAPFilterVariableType *SensorVar)
{
	uint16 u16SensorAD;
	uint16 u16CurrentSensorValue = 400u;/*0 degree*/
	uint8 u8ErrorType=0U;

	u16SensorAD = SensorVar[0].u16SensorAD;
	if ( (u16SensorAD < SensorPar[0].u16MinLimitValue) )
	{
		if ( SensorVar[0].u8ErrorCountL < 0xFFU )
		{
			SensorVar[0].u8ErrorCountL++;
		}

		if ( SensorVar[0].u8ErrorCountL > SensorPar[0].u8ErrorCountTimeout )
		{
			SensorVar[0].u8SensorErrorFlag = True;
			SensorVar[0].u16SensorValue = SensorPar[0].u16SensorDefaultValue;
			u8ErrorType = 1U;
		}

		SensorVar[0].u8ErrorCountH = 0U;
		
	}
	else if(u16SensorAD > SensorPar[0].u16MaxLimitValue)
	{
		if ( SensorVar[0].u8ErrorCountH < 0xFFU )
		{
			SensorVar[0].u8ErrorCountH++;
		}

		if ( SensorVar[0].u8ErrorCountH > SensorPar[0].u8ErrorCountTimeout )
		{
			SensorVar[0].u8SensorErrorFlag = True;
			SensorVar[0].u16SensorValue = SensorPar[0].u16SensorDefaultValue;
			u8ErrorType = (1U<<1U);
		}
		
		SensorVar[0].u8ErrorCountL = 0U;
	}
	else
	{
		SensorVar[0].u8ErrorCountL = 0U;
		SensorVar[0].u8ErrorCountH = 0U;
		
		u16CurrentSensorValue = ALG_u16CurveLookup_16_16_Limit( (uint16 *)SensorPar[0].au16Raw, (uint16 *)SensorPar[0].au16Result, u16SensorAD, SensorPar[0].u8Length );

		if ( (SensorVar[0].u8SensorErrorFlag) || (SensorVar[0].u8InitFlag == ColdBoot) )
		{
			SensorVar[0].u8SensorErrorFlag = False;
			SensorVar[0].u8InitFlag = biHotBoot;
			SensorVar[0].u16SensorValue = u16CurrentSensorValue;
			SensorVar[0].u32InterimValue = (uint32)u16CurrentSensorValue<<16;
		}
		else
		{
			SensorVar[0].u16SensorValue = ALG_u16FirstOrderFilter(&(SensorVar[0].u32InterimValue), u16CurrentSensorValue, 
																SensorPar[0].u8FilterParameter); 
		}
																
	}
    EVAP_u16RawValue = u16CurrentSensorValue;
	return(u8ErrorType);
}

/* ===========================================================================
* Function   : void  EVAP_vRawValueHandle(uint16)
* Description: This is On the ignition->off transition function for the EVAP module.
* Takes      : None
* Returns    : None
*/
static void  EVAP_vRawValueHandle(uint16 InputValue)
{
	uint8 u8Ret;

	EVAP_stFilterVar.u16SensorAD =  InputValue;

	u8Ret = EVAP_u8SensorFilter(&EVAP_stFilterParam,&EVAP_stFilterVar);

    EVAP_u16ErrorCode &=(~0x0003);
	EVAP_u16ErrorCode |=(u8Ret&0x03);
	EVAP_u16ResultTemp =EVAP_stFilterVar.u16SensorValue;
	EVAP_u8SensorFailsafe=EVAP_stFilterVar.u8SensorErrorFlag;

	if(EVAP_stFilterVar.u8SensorErrorFlag ==True)
	{
		EVAP_stFilterVar.u8InitFlag = biColdBoot;
	}
}


/* ===========================================================================
* Function   : void EVAP_vFilterInit(void)
* Description: This is On the ignition->off transition function for the EVAP module.
* Takes      : None
* Returns    : None
*/
static void EVAP_vFilterInit(void)
{
	EVAP_biFilterInit = True;

	#if (EVAP_nMacEvapTempCfg == True)
	EVAP_u16MacValue = EVAP_u16ResultTemp;	
	EVAP_u32MacValueOld = (uint32)EVAP_u16ResultTemp << 16;
	#endif
	
	EVAP_u16FastEvapTemp = EVAP_u16ResultTemp;	
	EVAP_u32ACValueOld = (uint32)EVAP_u16ResultTemp << 16;	

	#if (EVAP_nDynOffsCfg == True)
	EVAP_u16PtaValueOld = EVAP_u16ResultTemp;
	#endif
}


/* ===========================================================================
* Function   : void EVAP_vTempFilter(void)
* Description: This is On the ignition->off transition function for the EVAP module.
* Takes      : None
* Returns    : None
*/
static void EVAP_vTempFilter(void)
{
	uint8 sbiSysTick1s =True;
	uint16 u16EvapTemp;
	
	uint32 *pu32_1 = NULL;

	#if (EVAP_OpenInterfaces_Cfg == True)
	sbiSysTick1s =  EVAP_u8GetSysValue();
	#endif

	if(EVAP_u8SensorFailsafe ==True)
	{
		EVAP_u16FastEvapTemp =EVAP_u16ResultTemp;

		#if (EVAP_nMacEvapTempCfg == True)
		EVAP_u16MacValue = EVAP_u16ResultTemp;
		#endif
		
		EVAP_biFilterInit =False;
	}
	else
	{
		if ( EVAP_biFilterInit == False )
		{	/* filter  first init pra*/
			EVAP_vFilterInit();
		}
		else
		{
			if( sbiSysTick1s == True )
			{
				pu32_1 = &EVAP_u32ACValueOld;
				u16EvapTemp = ALG_u16FirstOrderFilter (pu32_1, EVAP_u16ResultTemp, EVAP_u8FilterK);

				#if (EVAP_nMacEvapTempCfg == True)
				/* mac slow evap temp calculation*/
				EVAP_vSlowTemp(u16EvapTemp);
				#endif

				#if (EVAP_nDynOffsCfg == True)
				/* evap dyn offset cal*/
				EVAP_vDynOffsCal(u16EvapTemp);
				#else
				EVAP_u16FastEvapTemp  =u16EvapTemp;
				#endif
								
			}
		}
	}
}

#if (EVAP_nDynOffsCfg == True)
/* ===========================================================================
* Function   :    static uint16 EVAP_u16CalEvapDiffTempOffset (const uint16 u16InputValue)	
* Description:  Calculate Blower Offset
* Takes      :   u16InputSunload - the input solar indensity value
* Returns   :   The 16-bit output of Blower Offset 
*/
static uint16 EVAP_u16CalEvapDiffTempOffset (const uint16 u16InputDiff)
{
	uint16 *pu16_1 = NULL;
	uint16 *pu16_2 = NULL;
	uint16 u16TempDiffOffset   = 0;
	
	pu16_1 = (uint16 *)EVAP_au16EvaDynOffsX_Tbl;
	pu16_2 = (uint16 *)EVAP_au16EvaDynOffsY_Tbl;
	u16TempDiffOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,u16InputDiff,EVAP_nEvaDynOffsTblLen);

	return u16TempDiffOffset;

}
#endif

#if (EVAP_nMacEvapTempCfg == True)
/* ===========================================================================
* Function   : void EVAP_vSlowTemp(uint8 f)
* Description: Main function of the evaporator temperature model. This
*              function is called in the cyclic background task in the ON
*              state.
* Takes      : Nothing
* Returns    : Nothing
*/
void EVAP_vSlowTemp(uint16 u16EvapTemp)
{
	uint32 *pu32_1 = NULL;
	
	pu32_1 = &EVAP_u32MacValueOld;
	
	#if(EVAP_nMacEvapOffsetCfg==True)
	uint16 u16SlowTemp=0;
	uint16 u16EvaOffsetTemp=EVAP_u16DadaOffset;
	u16SlowTemp = ALG_u16FirstOrderFilter (pu32_1, u16EvapTemp, EVAP_u8FilterKMac);	
    if(True==Rte_IRead_Evap_vMain_Evap_AcccActualRequest_u8State())
     {
    	u16EvaOffsetTemp = EVAP_u16SensorTempOffset();
     }
     else
     {
        u16EvaOffsetTemp=EVAP_u16DadaOffset;
     }
	EVAP_u16MacValue = u16SlowTemp+u16EvaOffsetTemp-EVAP_u16DadaOffset;
	#else
	EVAP_u16MacValue = ALG_u16FirstOrderFilter (pu32_1, u16EvapTemp, EVAP_u8FilterKMac);	
	#endif
	
	
}
#endif

#if (EVAP_nDynOffsCfg == True)
/* ===========================================================================
* Function   : void EVAP_vDynOffsCal(uint8 f)
* Description: Main function of the evaporator temperature model. This
*              function is called in the cyclic background task in the ON
*              state.
* Takes      : Nothing
* Returns    : Nothing
*/
void EVAP_vDynOffsCal(uint16 u16EvapTemp)
{
	int16 i16EvapTempDiff = 0;

	/*to calculate the current -old value,to look up a offset curve, 130508 */
	i16EvapTempDiff = (int16)u16EvapTemp  - (int16)EVAP_u16PtaValueOld + EVAP_u16DadaOffset;
	
	// check the value limit
	if ( i16EvapTempDiff <= Evap_TempDiff_UMIN )
	{
		i16EvapTempDiff = Evap_TempDiff_UMIN;
	}
	else if ( i16EvapTempDiff >= Evap_TempDiff_UMAX )
	{
		i16EvapTempDiff = Evap_TempDiff_UMAX;
	}
	else
	{
	    //none
	}
	
	EVAP_u16DynOffset = EVAP_u16CalEvapDiffTempOffset((uint16)i16EvapTempDiff);
	
	i16EvapTempDiff = (int16)u16EvapTemp + (int16)EVAP_u16DynOffset - EVAP_u16DadaOffset;
	// check the value limit
	if ( i16EvapTempDiff <= Evap_Temp_MIN )
	{
		i16EvapTempDiff = Evap_Temp_MIN;
	}
	else if ( i16EvapTempDiff >= Evap_Temp_MAX )
	{
		i16EvapTempDiff = Evap_Temp_MAX;
	}
	else
	{
	    //none
	}
	
	EVAP_u16FastEvapTemp  = (uint16)i16EvapTempDiff;/*add by zsc,130508 to avoid the eva sensor not sensity*/
	EVAP_u16PtaValueOld = u16EvapTemp;
	
}
#endif

#if(EVAP_nMacEvapOffsetCfg ==True)
/* ===========================================================================
* Function   : static uint16 EVAP_u16SensorTempOffset (void)
* Description: 
*              EVAP Temp offset
*              
* Takes      : Nothing
* Returns    : Nothing
*/
static uint16 EVAP_u16SensorTempOffset(void)
{
	uint16 u16TempOffset=0;
	uint8 u8RecirState=0;
	uint16 u16InletTemp=0;
	uint16 u16BctlValue=0;

	u16BctlValue = Rte_IRead_Evap_vMain_Evap_BctlBlwTarget_u16BlwSpd();
	u8RecirState =Rte_IRead_Evap_vMain_Evap_RfaDisplay_u8DispInfo();
		
	if(u8RecirState == 0)
	{	/* use the OAT value when in the fresh mode*/
		u16InletTemp =Rte_IRead_Evap_vMain_Evap_OatValue_u16Temp();
		 u16TempOffset = Evap_u8OatTempOffset(u16BctlValue,u16InletTemp);
	}
	else
	{	/* use the ICT value when in the recirculation mode*/
		u16InletTemp =Rte_IRead_Evap_vMain_Evap_IctValue_u16Temp();
		u16TempOffset =Evap_u8IctTempOffset(u16BctlValue,u16InletTemp);
	}
	
	return(u16TempOffset);
}

/* ===========================================================================
* Function   : static uint16 Evap_u8OatTempOffset (uint16 u16InputBlowerSpd,uint16 u16OATvalue)
* Description: 
*              EVAP Temp offset
*              
* Takes      : Nothing
* Returns    : Nothing
*/
static uint16 Evap_u8OatTempOffset (uint16 u16InputBlowerSpd,uint16 u16OATvalue)		
{
	uint16 u16TempOatOffset = 0;	
	uint16 au16Offsets[EVAP_nBctlLevelXTbl_Len];
	
	uint16 *pu16_1=NULL;
	uint16 *pu16_2=NULL;

	/* Select the first curve for searching the value.*/
	pu16_1 = (uint16 *)&EVAP_au16GroupEVAPOATOffsetX_Tbl[0];
	pu16_2 = (uint16 *)&EVAP_au16GroupEVAPOATOffsetY_Tbl[0];
	au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,u16OATvalue,EVAP_nOATOffsetXTbl_Len);
	/* Select the second curves for searching the value.*/
	pu16_2 = (uint16 *)&EVAP_au16GroupEVAPOATOffsetY1_Tbl[0];
	au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,u16OATvalue,EVAP_nOATOffsetXTbl_Len);
	/* Select the third curves for searching the value.*/
	pu16_2 = (uint16 *)&EVAP_au16GroupEVAPOATOffsetY2_Tbl[0];
	au16Offsets[2] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,u16OATvalue,EVAP_nOATOffsetXTbl_Len);
	
	pu16_1 = (uint16 *)&EVAP_au16GroupEVAPBctlLevelX_Tbl[0];
	pu16_2 = (uint16 *)&au16Offsets[0];
	
	u16TempOatOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,u16InputBlowerSpd, EVAP_nBctlLevelXTbl_Len);		
	

	return(u16TempOatOffset);

}


/* ===========================================================================
* Function   : static uint16 Evap_u8IctTempOffset (uint16 u16InputBlowerSpd,uint16 u16OATvalue)
* Description: 
*              EVAP Temp offset
*              
* Takes      : Nothing
* Returns    : Nothing
*/
static uint16 Evap_u8IctTempOffset (uint16 u16InputBlowerSpd,uint16 u16ICTvalue)		
{
	uint16 u16TempIctOffset = 0;	
	uint16 au16Offsets[EVAP_nBctlLevelXTbl_Len];
	
	uint16 *pu16_1=NULL;
	uint16 *pu16_2=NULL;

	/* Select the first curve for searching the value.*/
	pu16_1 = (uint16 *)&EVAP_au16GroupEVAPICTOffsetX_Tbl[0];
	pu16_2 = (uint16 *)&EVAP_au16GroupEVAPICTOffsetY_Tbl[0];
	au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,u16ICTvalue,EVAP_nICTOffsetXTbl_Len);
	/* Select the second curves for searching the value.*/
	pu16_2 = (uint16 *)&EVAP_au16GroupEVAPICTOffsetY1_Tbl[0];
	au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,u16ICTvalue,EVAP_nICTOffsetXTbl_Len);
	/* Select the third curves for searching the value.*/
	pu16_2 = (uint16 *)&EVAP_au16GroupEVAPICTOffsetY2_Tbl[0];
	au16Offsets[2] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,u16ICTvalue,EVAP_nICTOffsetXTbl_Len);
	
	pu16_1 = (uint16 *)&EVAP_au16GroupEVAPBctlLevelX_Tbl[0];
	pu16_2 = (uint16 *)&au16Offsets[0];
	
	u16TempIctOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,u16InputBlowerSpd, EVAP_nBctlLevelXTbl_Len);		
	

	return(u16TempIctOffset);

}

#endif

#if( EVAP_nUseRTE == True)
/* ===========================================================================
* Function   : void EVAP_vUpdateRteData (void)
* Description: 
*              update the RTE data
*              
* Takes      : Nothing
* Returns    : Nothing
*/
void EVAP_vUpdateRteData(void)
{
	Rte_IWrite_Evap_vMain_EvapAcValue_u16Temp(EVAP_u16FastEvapTemp);
	Rte_IWrite_Evap_vMain_EvapSensorRawValue_u16Temp(EVAP_u16ResultTemp);
	Rte_IWrite_Evap_vMain_EvapValid_u8Flag(EVAP_u8Valid);
    Rte_IWrite_Evap_vMain_EvapErrorCode_u16BitMap(EVAP_u16ErrorCode);
	
	#if(EVAP_nMacEvapTempCfg == True)
	Rte_IWrite_Evap_vMain_EvapMacValue_u16Temp(EVAP_u16MacValue);
	#endif
}
#endif

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/07/22										  *
 Function      : Evap_vActive                                                   *
 Description   : 
 Return Value  : None                                                        *
*****************************************************************************/
void EVAP_vActive(void)
{
}

/* ===========================================================================
* Function   : void EVAP_vMain (void)
* Description: Main function of the evaporator temperature model. This
*              function is called in the cyclic background task in the ON
*              state.
* Takes      : Nothing
* Returns    : Nothing
*/
void EVAP_vMain (void)
{	
	uint16 u16PTAValid =False;
	uint16 u16LowVoltage=0;
	uint16 u16HighVoltage=0;

	#if (EVAP_OpenInterfaces_Cfg == Yes)
	#if( EVAP_nUseRTE == True)
	/* RTE Interface*/
	Rte_Call_Evap_ReadAd_SensorValue_Read(&EVAP_u16SensorAdValue);
	Rte_IWrite_Evap_vMain_EvapSensorAdValue_u16AdValue(EVAP_u16SensorAdValue);

	biPTAValid =1;// Rte_IRead_Evap_vMain_Evap_PowAdValid_u16Flag();
	boHighVoltage = Rte_IRead_Evap_vMain_Evap_PowBattHighVoltage_u16Flag();
	boLowVoltage = Rte_IRead_Evap_vMain_Evap_PowBattLowVoltage_u16Flag();
	#else
	/* normal get value*/
	Rte_Call_IoHwAd_IoHwAd_ReadAd_EvapSensorValue_Read(&EVAP_u16SensorAdValue);

	u16PTAValid =1;// Rte_IRead_Evap_vMain_Evap_PowAdValid_u16Flag();
	u16HighVoltage = POW_u16GetValue(POW_nu16AppHighVoltage);
	u16LowVoltage = POW_u16GetValue(POW_nu16AppLowVoltage);
	#endif	 
	#endif
	
	if( (u16PTAValid== False)|| (u16LowVoltage == True) || (u16HighVoltage == True))
	{
		EVAP_biFilterInit = False;
        EVAP_u16ErrorCode &= ~(0x30u);
        if(u16LowVoltage == True)
        {
            EVAP_u16ErrorCode |= 0x10u;
        }
        else if(u16LowVoltage == True)
        {
            EVAP_u16ErrorCode |= 0x20u;
        }
	}
	else
	{	/* Evap handle*/

        EVAP_u16ErrorCode &= ~(0x30u);
		#if (EVAP_nUseCCP == True)
		EVAP_vCcpInputForce();
		#endif
		
		EVAP_vRawValueHandle(EVAP_u16SensorAdValue);

		EVAP_vTempFilter();
		
		EVAP_u8Valid = True;
	}

	#if (EVAP_nUseCCP == True)
	EVAP_vCcpOutputForce();
	#endif

	#if( EVAP_nUseRTE == True)
	EVAP_vUpdateRteData();	
	#endif
}

/*****************************************************************************
 Function      : EVAP_u16GetValue                                              
 Description   : The extern model get the uint16 type variable value from this model                                                       
 Return Value  : uint16 value                                                 
*****************************************************************************/
uint16 EVAP_u16GetValue( EVAP_tenu16VarNumber enIndex )
{
	if ( enIndex < EVAP_nu16Max )
	{
		return EVAP_au16Array[enIndex];
	}
	else
	{
		return EVAP_au16Array[EVAP_nu16Max-1];
	}
}

/*****************************************************************************
 Function      : EVAP_u8GetValue                                             
 Description   : The extern model get the uint16 type variable value from this model                                                      
 Return Value  : uint8 value                                                 
*****************************************************************************/
uint8 EVAP_u8GetValue( EVAP_tenu8VarNumber enIndex )
{
	if ( enIndex < EVAP_nu8Max )
	{
		return EVAP_au8Array[enIndex];
	}
	else
	{
		return EVAP_au8Array[EVAP_nu8Max-1];
	}
}

/*****************************************************************************
* EOF: EVAP
******************************************************************************/
