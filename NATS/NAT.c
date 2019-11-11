/*******************************************************************************
| Module Name:  Non-Aspirated Temperature
| File Name: NAT.c
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
| 2016-8-17    1.0  Luo Xindian		 frist created,for basic code 
********************************************************************************/

#define NAT1C1                    /* Name of the Module                */


/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */

 /* General type definitions */
#include "General.h"

/* Foreign Headerfiles. */
#include "ALG.h"                 /* algorithms */
#include "frame_if.h"
#include "POW.h"
#include "OAT.h"
#include "Rte_internal.h"

/* Own headerfiles */
#include "NAT.h"
#include "NAT_Cfg.h"
#include "NAT_Private.h"
#include "NAT_Type.h"

/*Define Static*/

static uint8 NAT_au8Array[NAT_nu8Max];
static uint16 NAT_au16Array[NAT_nu16Max];
static NAT_tstInputLists	NAT_stInputLists;

static tstNATFilterConstantType NAT_stFilterParamSurf;
static tstNATFilterVariableType  NAT_stFilterVarSurf;

static tstNATFilterConstantType NAT_stFilterParamPcb;
static tstNATFilterVariableType  NAT_stFilterVarPcb;

static uint8 NAT_u8DynTmr;		/*Dynamic Timer*/
static uint8 NAT_biDynTmr;

static uint16 NAT_u16DynOldSurTemp[NAT_n8DynTmr];    /*Old Surface Temperature*/

static uint16 NAT_u16FilterBuffer[2];		/*Filter Buffer.*/ 

/*-Change 10 seconds to 20 seconds.-*/
static uint8 NAT_u8NumOf10Sec;

static uint32 NAT_u32FilterSta;
static uint32 NAT_u32FilterDyn;
static uint32 NAT_u32ValueFilter;

static uint32 NAT_u32ZeroFilter;
static uint16 NAT_u16ZeroOffset;

static uint32 	 NAT_u32FilterIR;
static uint32 	 NAT_u32FilterIROffset;

static uint8	NAT_u8IRFilterTmr;

static uint8 NAT_biFilterActive;

static void NAT_vInitSensorParam(void);
static void NAT_vInputValueProcess(void);
static void NAT_vAd2Temptransform(void);
static uint8 NAT_u8SensorFilter(const tstNATFilterConstantType SensorPar[], tstNATFilterVariableType SensorVar[]);
static void NAT_vTempDiffCalc(void);
static void NAT_vStaticOffsetCalc(void);
static void NAT_vTmlOffsetCalc(void);
static void NAT_vRayRadiationOffset(void);
static void NAT_vDynamicOffsetCalc(void);
static void NAT_vOffsetFilter(void);

#if(NAT_nUseCCP ==True)
/*Ccp control*/

static uint8 NAT_CcpForceFlag;
static uint16 NAT_CcpControlData[NAT_nCcpForceMax];

static void NAT_vCcpInputForce(void);
static void NAT_vCcpOutputForce(void);

/*****************************************************************************
 Function      : NAT_u8ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
uint8 NAT_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
{
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				NatClrCcpForceByte();
				break;
			case 1:
				NatSetCcpForceBit(NAT_nSetSurfaceTemp);
				NAT_CcpControlData[NAT_nSetSurfaceTemp]=CcpControlWord.CcpContronData;
				break;
			case 2:
				NatClrCcpForceBit(NAT_nSetSurfaceTemp);
				NAT_CcpControlData[NAT_nSetSurfaceTemp]=0;
				break;
			case 3:
				NatSetCcpForceBit(NAT_nSetPcbTemp);
				NAT_CcpControlData[NAT_nSetPcbTemp]=CcpControlWord.CcpContronData;
				break;
			case 4:
				NatClrCcpForceBit(NAT_nSetPcbTemp);
				NAT_CcpControlData[NAT_nSetPcbTemp]=0;
				break;
			case 0xA1:
				NatSetCcpForceBit(NAT_nSetNatValue);
				NAT_CcpControlData[NAT_nSetNatValue]=CcpControlWord.CcpContronData;
				break;
			case 0xA2:
				NatClrCcpForceBit(NAT_nSetNatValue);
				NAT_CcpControlData[NAT_nSetNatValue]=0;
				break;
			default:
                	return NotOk;
		}
	}
	else
	{
		NatClrCcpForceByte();
	}
        return Ok;
}

/*****************************************************************************
 Function      : NAT_vCcpInputForce                                 
 Description   : force Input value
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void NAT_vCcpInputForce(void)
{	
	if(NatGetCcpForceBit(NAT_nSetSurfaceTemp))
	{
		NAT_u16SurfaceTemp =NAT_CcpControlData[NAT_nSetSurfaceTemp];
	}
	else
	{
	}

	if(NatGetCcpForceBit(NAT_nSetPcbTemp))
	{
		NAT_u16PcbTemp =NAT_CcpControlData[NAT_nSetPcbTemp];
	}
	else
	{
	}
}
/*****************************************************************************
 Function      : NAT_vCcpOutputForce                                 
 Description   : force output value
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void NAT_vCcpOutputForce(void)
{	
	if(NatGetCcpForceBit(NAT_nSetNatValue))
	{
		NAT_u16Value=NAT_CcpControlData[NAT_nSetNatValue];
	}
	else
	{
	}
}
#endif/*#if(NAT_u8UseCCP ==True)*/

/* ===========================================================================
* Function   : void NAT_vActive (void)
* Description: Active function of NAT
* Takes      : Nothing
* Returns    : Nothing
*/
void NAT_vActive (void)
{
	
}



/* ===========================================================================
* Function   : void NAT_vActive (void)
* Description: Reset function of NAT
* Takes      : Nothing
* Returns    : Nothing
*/
void NAT_vReset(void)
{
	NAT_u8Valid = False;
	NAT_u8Value = 25 * 2 + 80;
	NAT_u16Value = 25 * 10 + 400;
	
	NAT_u8NumOf10Sec =0;
	NAT_u16ZeroOffset = 0;
	 NAT_u32ZeroFilter = NAT_u16ZeroOffset<<8;
	 NAT_u32FilterIR = 0;
	 NAT_u32FilterIROffset= 0;
	NAT_u8IRFilterTmr=0;
	NAT_biFilterActive=0;

	NAT_vInitSensorParam();
}

/* ===========================================================================
* Function   : void NAT_vInit (void)
* Description: Init function of NAT
*              Called in Active->On container.
               Calls NAT_vReset also.
* Takes      : Nothing
* Returns    : Nothing
*/
void NAT_vInit (void)
{
	NAT_u8DynTmr = 0;
	NAT_biDynTmr = False;
	NAT_u16DynOffset = NAT_nOffset;
	NAT_u16StaOffset = NAT_nOffset;
	NAT_u16RayOffset = 0;
	NAT_u16TmlOffset = NAT_nOffset;
	NAT_u32FilterDyn = ((uint32)NAT_nOffset)<<16;
	NAT_u32FilterSta = ((uint32)NAT_nOffset)<<16;

	NAT_u8Valid = False;
	NAT_biFilterActive=0u;

	NAT_vInitSensorParam();
}
/* ===========================================================================
* Function   : void NAT_vDeinit (void)
* Description: De-init function of NAT
*              Called in On->Active container.
               Calls NAT_vReset also.
* Takes      : Nothing
* Returns    : Nothing
*/
void NAT_vDeinit (void)
{

}
/* ===========================================================================
* Function   : void NAT_vMain (void)
* Description: The main container function for NAT module.
*              This function is usually called every 100mS in On state.
* Takes      : Nothing
* Returns    : Nothing
*/
void NAT_vMain (void)
{
	NAT_vInputValueProcess();
	
	if((NAT_stInputLists.u8LowVoltage== True) || (NAT_stInputLists.u8LowVoltage== True))
	{
		/*do nothing*/
	}
	else
	{
		NAT_u8Valid = True;

		/*--------Sensor Transmit---------*/
		NAT_vAd2Temptransform();
		
		/*----PCB - Surface temp different---*/
		NAT_vTempDiffCalc();
		
		/*--------Static Offset-------------*/
		NAT_vStaticOffsetCalc();
		
		/*--------Thermal Offset-----------*/
		NAT_vTmlOffsetCalc();
		
		/*--------Ray Radiation Offset-------*/
		NAT_vRayRadiationOffset();

		/*--------Dynamic Offset-----------*/
		NAT_vDynamicOffsetCalc();

		/*---------Offset Filter------------*/
		NAT_vOffsetFilter();
		
	}	
	/*output to RTE*/
	
}
/* ===========================================================================
* Function   : void NAT_vInitSensorParam (void)
* Description: This is the Init sensor param handle function for the NAT module.
* Takes      : None
* Returns    : None
*/
static void NAT_vInitSensorParam(void)
{
	/*------------Surface temp sensor---------------------------*/
	NAT_stFilterParamSurf.au16Raw = (uint16 *)&NAT_au16GroupSurfTempXTbl[0];
	NAT_stFilterParamSurf.au16Result = (uint16 *)&NAT_au16GroupSurfTempYTbl[0];
	NAT_stFilterParamSurf.u16MaxLimitValue = NAT_nSurfSensorMax;
	NAT_stFilterParamSurf.u16MinLimitValue = NAT_nSurfSensorMin;
	NAT_stFilterParamSurf.u16SensorDefaultValue = NAT_nSurfSensorDefaultValue;
	NAT_stFilterParamSurf.u8ErrorCountTimeout = NAT_nErrorCountTimeout;
	NAT_stFilterParamSurf.u8FilterParameter = NAT_nFilterParameter;
	NAT_stFilterParamSurf.u8Length = NAT_nSurfTempTblLen;

	NAT_stFilterVarSurf.u32InterimValue=0u;
	NAT_stFilterVarSurf.u16SensorValue =NAT_nSurfSensorDefaultValue;
	NAT_stFilterVarSurf.u8ErrorCountL =0u;
	NAT_stFilterVarSurf.u8ErrorCountH =0u;
	NAT_stFilterVarSurf.u8SensorErrorFlag=0u;
	NAT_stFilterVarSurf.u8InitFlag = NAT_nColdBoot;

	/*------------PCB temp sensor---------------------------*/
	NAT_stFilterParamPcb.au16Raw = (uint16 *)&NAT_au16GroupPCBTempXTbl[0];
	NAT_stFilterParamPcb.au16Result = (uint16 *)&NAT_au16GroupPCBTempYTbl[0];
	NAT_stFilterParamPcb.u16MaxLimitValue = NAT_nPcbSensorMax;
	NAT_stFilterParamPcb.u16MinLimitValue = NAT_nPcbSensorMin;
	NAT_stFilterParamPcb.u16SensorDefaultValue = NAT_nPcbSensorDefaultValue;
	NAT_stFilterParamPcb.u8ErrorCountTimeout = NAT_nErrorCountTimeout;
	NAT_stFilterParamPcb.u8FilterParameter = NAT_nFilterParameter;
	NAT_stFilterParamPcb.u8Length = NAT_nPCBTempTblLen;

	NAT_stFilterVarPcb.u32InterimValue=0u;
	NAT_stFilterVarPcb.u16SensorValue =NAT_nPcbSensorDefaultValue;
	NAT_stFilterVarPcb.u8ErrorCountL =0u;
	NAT_stFilterVarPcb.u8ErrorCountH =0u;
	NAT_stFilterVarPcb.u8SensorErrorFlag=0u;
	NAT_stFilterVarPcb.u8InitFlag = NAT_nColdBoot;
}
/* ===========================================================================
* Function   : void NAT_vInputValueProcess (void)
* Description: This is the input variable handle function for the NAT module.
* Takes      : None
* Returns    : None
*/
static void NAT_vInputValueProcess(void)
{
    uint16 u16GetValue;
    
	#if (NAT_OpenInterfaces_Cfg == Yes)
	#if(NAT_nUseRTE ==True)
	
	#else
	NAT_stInputLists.u8HighVoltage = NAT_GetHighVoltage;
	NAT_stInputLists.u8LowVoltage = NAT_GetLowVoltage;
	NAT_stInputLists.u8Sys1000ms =NAT_Get100msFlag;
	NAT_stInputLists.u16OatValue = NAT_GetOatValue;
    
	NAT_GetSurfaceTempAd(&u16GetValue);
    NAT_stInputLists.u16SurfaceAd = u16GetValue;
    
	NAT_GetPCBTempAd(&u16GetValue);
    NAT_stInputLists.u16PcbAd = u16GetValue;
    
	NAT_GetIRAd(&u16GetValue);
    NAT_stInputLists.u16IrSolarAd = u16GetValue;
    
	#endif/*#if(NAT_u8UseRTE ==True)*/
	#endif/*#if (NAT_OpenInterfaces_Cfg == Yes)*/

	#if(NAT_nUseCCP ==True)
	/*CCP Control*/
	NAT_vCcpInputForce();
	#endif
}
/* ===========================================================================
* Function   : void NAT_vAd2Temptransform (void)
* Description: This is the AD transform to temp handle function for the NAT module.
* Takes      : None
* Returns    : None
*/
static void NAT_vAd2Temptransform(void)
{
	uint8 u8Ret=0u;
	
	NAT_u16ErrorCode=0;
	
	/*-------Surface temp sensor-----------------------------*/
	NAT_stFilterVarSurf.u16SensorAD = NAT_stInputLists.u16SurfaceAd;
	u8Ret = NAT_u8SensorFilter(&NAT_stFilterParamSurf,&NAT_stFilterVarSurf);

	NAT_u16ErrorCode |=(u8Ret&0x03);
		
	NAT_u16SurfaceTemp =NAT_stFilterVarSurf.u16SensorValue;

	if(NAT_stFilterVarSurf.u8SensorErrorFlag ==True)
	{
		NAT_stFilterVarSurf.u8InitFlag = NAT_nColdBoot;
	}

	/*-------Pcb temp sensor-----------------------------*/
	NAT_stFilterVarPcb.u16SensorAD = NAT_stInputLists.u16PcbAd;
	u8Ret = NAT_u8SensorFilter(&NAT_stFilterParamPcb,&NAT_stFilterVarPcb);

	NAT_u16ErrorCode |=(u8Ret<<2);
		
	NAT_u16PcbTemp =NAT_stFilterVarPcb.u16SensorValue;

	if(NAT_stFilterVarPcb.u8SensorErrorFlag ==True)
	{
		NAT_stFilterVarPcb.u8InitFlag = NAT_nColdBoot;
	}
}
/* ===========================================================================
* Function   : void NAT_u8SensorFilter (void)
* Description: This is the AD transform to temp and filter handle function for the NAT module.
* Takes      : None
* Returns    : None
*/
static uint8 NAT_u8SensorFilter(const tstNATFilterConstantType SensorPar[], tstNATFilterVariableType SensorVar[])
{
	uint16 u16SensorAD;
	uint16 u16CurrentSensorValue;
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
		}

		SensorVar[0].u8ErrorCountH = 0U;
		u8ErrorType = 1U;
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
		}
		
		SensorVar[0].u8ErrorCountL = 0U;
		u8ErrorType = 2U;
	}
	else
	{
		SensorVar[0].u8ErrorCountL = 0U;
		SensorVar[0].u8ErrorCountH = 0U;
		
		u16CurrentSensorValue = ALG_u16CurveLookup_16_16_Limit( (uint16 *)SensorPar[0].au16Raw, (uint16 *)SensorPar[0].au16Result, u16SensorAD, SensorPar[0].u8Length );

		if ( (SensorVar[0].u8SensorErrorFlag) || (SensorVar[0].u8InitFlag == NAT_nColdBoot) )
		{
			SensorVar[0].u8SensorErrorFlag = False;
			SensorVar[0].u8InitFlag = NAT_nHotBoot;
			SensorVar[0].u16SensorValue = u16CurrentSensorValue;
			SensorVar[0].u32InterimValue = (uint32)u16CurrentSensorValue<<16;
		}
		else
		{
			SensorVar[0].u16SensorValue = ALG_u16FirstOrderFilter(&(SensorVar[0].u32InterimValue), u16CurrentSensorValue, 
																SensorPar[0].u8FilterParameter); 
		}
																
	}

	return(u8ErrorType);
	
}

/* ===========================================================================
* Function   : void NAT_vTempDiffCalc (void)
* Description: This is the PCB and Surface Temperature different handle function for the NAT module.
* Takes      : None
* Returns    : None
*/
static void NAT_vTempDiffCalc(void)
{
	int16 i16TempDiff;
	
	i16TempDiff = NAT_u16PcbTemp - NAT_u16SurfaceTemp;
	
	if ( i16TempDiff < (int16) NAT_nOffsetMin )
	{
		NAT_u16TempDiff = 0;
	}
	else if ( i16TempDiff > (int16) NAT_nOffsetMax)
	{
		NAT_u16TempDiff = ((uint16)UCHAR_MAX)*5;
	}
	else
	{
		NAT_u16TempDiff = (uint16)(i16TempDiff - (int16)NAT_nOffsetMin);
	}
}
/* ===========================================================================
* Function   : void NAT_vStaticOffsetCalc (void)
* Description: This is the static offset calculation function for the NAT module.
* Takes      : None
* Returns    : None
*/
static void NAT_vStaticOffsetCalc(void)
{
	uint16 u16OffsetTemp=0u;
	uint16 *pu16_1 =NULL;
	uint16 *pu16_2 =NULL;
	uint32 *pu32_1 = NULL;
	
	pu16_1 =(uint16 *) &NAT_au16GroupStaticOffsetX[0];
	pu16_2 = (uint16 *)&NAT_au16GroupStaticOffsetY[0];
	u16OffsetTemp = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,NAT_u16TempDiff,NAT_nStaticOffsetTblLen);

	pu32_1 = &NAT_u32FilterSta;
	NAT_u16StaOffset = ALG_u16FirstOrderFilter(pu32_1,u16OffsetTemp, NAT_nDynFilterK);
}
/* ===========================================================================
* Function   : void NAT_vTmlOffsetCalc (void)
* Description: This is the Ambient temp calculation function for the NAT module.
* Takes      : None
* Returns    : None
*/
static void NAT_vTmlOffsetCalc(void)
{
	uint16 u16OffsetTemp=0u;
	uint16 *pu16_1 =NULL;
	uint16 *pu16_2 =NULL;
	
	pu16_1 = (uint16 *)&NAT_au16GroupThermalOffsetX[0];
	pu16_2 = (uint16 *)&NAT_au16GroupThermalOffsetY[0];
	u16OffsetTemp= ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,NAT_stInputLists.u16OatValue,NAT_nThermalOffsetLen);
	
	if(u16OffsetTemp>(NAT_u16TmlOffset+NAT_au8OatOfsStep))
	{
		NAT_u16TmlOffset += NAT_au8OatOfsStep;
	}
	else if((u16OffsetTemp + NAT_au8OatOfsStep) < NAT_u16TmlOffset)
	{
		NAT_u16TmlOffset -=NAT_au8OatOfsStep;
	}
	else
	{
		NAT_u16TmlOffset = u16OffsetTemp;
	}
}
/* ===========================================================================
* Function   : void NAT_vRayRadiationOffset (void)
* Description: This is the IR offset calculation function for the NAT module.
* Takes      : None
* Returns    : None
*/
static void NAT_vRayRadiationOffset(void)
{
	uint8   u8IRFilterK=0u;
	uint8   u8IROFilterK=0u;
	uint16 u16OffsetTemp=0u;
	uint16 *pu16_1 =NULL;
	uint16 *pu16_2 =NULL;
	uint32 *pu32_1 = NULL;
	
	if(NAT_stInputLists.u16IrSolarAd >= NAT_u16IRSunLoad)
	{
		u8IRFilterK= 7u;
	}
	else
	{
		u8IRFilterK=7u;
	}
	
	pu32_1 = (uint32 *)&NAT_u32FilterIR;
	NAT_u16IRSunLoad = ALG_u16FirstOrderFilter(pu32_1,NAT_stInputLists.u16IrSolarAd, u8IRFilterK);
	
	pu16_1 = (uint16 *)&NAT_au16GroupRadOffsetX[0];
	pu16_2 = (uint16 *)&NAT_au16GroupRadOffsetY[0];
	u16OffsetTemp = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,NAT_u16IRSunLoad,NAT_nRadOffsetTblLen);

	if(NAT_u8IRFilterTmr>= 1u)
	{
		NAT_u8IRFilterTmr = 0u;

		if(u16OffsetTemp>=NAT_u16RayOffset)
		{
			u8IROFilterK= 5u;
		}
		else
		{
			u8IROFilterK=5u;//4
		}
		
		pu32_1 = &NAT_u32FilterIROffset;
		NAT_u16RayOffset = ALG_u16FirstOrderFilter(pu32_1,u16OffsetTemp, u8IROFilterK);
	}
	else
	{
		NAT_u8IRFilterTmr++;
	}	
}
/* ===========================================================================
* Function   : void NAT_vDynamicOffsetCalc (void)
* Description: This is the dynamic offset handle function for the NAT module.
* Takes      : None
* Returns    : None
*/
static void NAT_vDynamicOffsetCalc(void)
{
	uint8 i;
	int16 i16TempDiff=0;
	uint16 u16TempDiff=0u;
	uint16 u16OffsetTemp=0u;
	uint16 *pu16_1 =NULL;
	uint16 *pu16_2 =NULL;
	uint32 *pu32_1 = NULL;
	
	if (NAT_stInputLists.u8Sys1000ms == True)
	{
		if(NAT_u8NumOf10Sec >= NAT_nNumOf10Sec)
		{
			NAT_u8NumOf10Sec =0u;
			
			if(NAT_biDynTmr == False)
			{
				for(i=0u;i<NAT_n8DynTmr;i++)
				{

					NAT_u16DynOldSurTemp[i] = NAT_u16SurfaceTemp;
				}
				NAT_biDynTmr = True;
			}
			else
			{
				NAT_u16DynOldSurTemp[NAT_u8DynTmr] = NAT_u16SurfaceTemp;
			}

			NAT_u8DynTmr ++;
			
			if(NAT_u8DynTmr >=NAT_n8DynTmr )
			{
				NAT_u8DynTmr = 0u;
			}
			
			i16TempDiff = (int16)(NAT_u16SurfaceTemp -NAT_u16DynOldSurTemp[NAT_u8DynTmr]);

						
			if ( i16TempDiff < (int16) NAT_nOffsetMin)
			{
				u16TempDiff = 0u;
			}
			else if ( i16TempDiff > (int16) NAT_nOffsetMax)
			{
				u16TempDiff =  UCHAR_MAX*5;
			}
			else
			{
				u16TempDiff = (uint16)(i16TempDiff - (int16)NAT_nOffsetMin);
			}
#if 0
			//Detect if there is someone touching the sensor.
			if(u16TempDiff < NAT_nDynSurfTempBiasMin)//NAT__au16DynOffsetX_Tbl[0])
			{
				NAT_biTouchDn = True;
				//NAT_biTouchUp = False;
			}
			else if(u16TempDiff > NAT_nDynSurfTempBiasMax)//NAT__au16DynOffsetX_Tbl[NAT__nDynOffsetTbl_Len-1])
			{
				//NAT_biTouchDn = False;
				NAT_biTouchUp = True;
			}
			else
			{
				//NAT_biTouchDn = False;
				//NAT_biTouchUp = False;
			}
#endif
						
			pu16_1 =(uint16 *) &NAT_au16GroupDynamicOffsetX[0];
			pu16_2 =(uint16 *) &NAT_au16GroupDynamicOffsetY[0];
			u16OffsetTemp= ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,u16TempDiff,NAT_nDynamicOffsetTblLen);
			
			pu32_1 = (uint32 *)&NAT_u32FilterDyn;
			NAT_u16DynOffset = ALG_u16FirstOrderFilter(pu32_1,u16OffsetTemp, NAT_nDynFilterK);
			
		}
		else
		{
			NAT_u8NumOf10Sec++;
		}
	}
}
/* ===========================================================================
* Function   : void NAT_vOffsetFilter (void)
* Description: This is the  Offset Filter handle function for the NAT module.
* Takes      : None
* Returns    : None
*/
static void NAT_vOffsetFilter(void)
{
	int16 i16TempDiff;
    int16 i16SumOffset=0;
	uint8 u8TempDiff=0u;
	uint16 u16OffsetTemp=0u;
	uint16 *pu16_1 =NULL;
	//uint16 *pu16_2 =NULL;
	uint32 *pu32_1 = NULL;
	
	i16TempDiff= 	(int16)(
					NAT_u16StaOffset + NAT_nOffsetMin
				    + NAT_u16DynOffset + NAT_nOffsetMin
				    + (NAT_u16TmlOffset + NAT_nOffsetMin)
				    - (NAT_u16RayOffset)
				    );

		
	if ( i16TempDiff < (int16) NAT_nOffsetMin )
	{
		u8TempDiff = 0u;
		NAT_u16Value = NAT_u16SurfaceTemp;
	}
	else if ( i16TempDiff > (int16) NAT_nOffsetMax)
	{
		u8TempDiff = (uint8) UCHAR_MAX;
		NAT_u16Value = NAT_u16SurfaceTemp - NAT_nOffsetMin;
	}
	else
	{
		u8TempDiff = (uint8) (i16TempDiff /5 - SCHAR_MIN);
        i16SumOffset = (int16)NAT_u16SurfaceTemp + i16TempDiff;
        if(i16SumOffset < 0)
        {
            i16SumOffset = 0;
        }
        NAT_u16Value = (uint16)i16SumOffset;
		//NAT_u16Value = NAT_u16SurfaceTemp + i16TempDiff ;
	}
	#if 0
	if((NAT_nu8RayRawValue <= NAT_nCoveredDefalut)
	   &&(NAT_biTouchDn == True)
	   &&(NAT_u16Value>660))
	{
		if(NAT_u16Value < NAT_u16SurfaceTemp)
		{
			NAT_u16Value = NAT_u16SurfaceTemp;// + NAT_stOffset.u16STA_Offset + NAT_nOffsetMin;
			u8TempDiff = 128;//NAT_stOffset.u16STA_Offset /5;
		}
		else
		{
			NAT_biTouchDn = False;
		}

	}
	#endif
#if 0
		if((NAT_nu8RayRawValue <= NAT_nCoveredDefalut)
		   &&(NAT_biTouchUp == True)
		   &&(NAT_u16Value>660))
		{
			if(NAT_u16Value > NAT_u16SurfaceTemp)
			{
				NAT_u16Value = NAT_u16SurfaceTemp;// + NAT_stOffset.u16STA_Offset + NAT_nOffsetMin;;
				u8TempDiff = 128;//NAT_stOffset.u16STA_Offset /5;
			}
			else
			{
				NAT_biTouchUp = False;
			}
		}
		//End
#endif				
		if(NAT_u16Value < 360u)
		{
			u16OffsetTemp = 40u;
		}
		else if(NAT_u16Value < 400u)
		{
			u16OffsetTemp = (uint8)(400u -NAT_u16Value);
		}
		else
		{
			u16OffsetTemp = 0u;
		}
		if (NAT_stInputLists.u8Sys1000ms == True)	
		{	
			pu32_1 = (uint32 *)&NAT_u32ZeroFilter;
			NAT_u16ZeroOffset = ALG_u16FirstOrderFilter(pu32_1,u16OffsetTemp, 6);
		}
		NAT_u16Value +=NAT_u16ZeroOffset;
		
		i16TempDiff = (int16)(NAT_u16SurfaceTemp+NAT_u16ZeroOffset)/5 + u8TempDiff + SCHAR_MIN;
		if ( i16TempDiff < (int16) 0 )
		{
			NAT_u8Value = 0;
		}
		else if ( i16TempDiff > (int16) UCHAR_MAX)
		{
			NAT_u8Value = (uint8) UCHAR_MAX;
		}
		else
		{
			NAT_u8Value =  (uint8) (i16TempDiff);
		}
		
		if (NAT_biFilterActive == False)								
		{														
				NAT_biFilterActive = True;								
				NAT_u16FilterBuffer[0] = NAT_u8Value << 8;			
				NAT_u16FilterBuffer[1] = NAT_u16FilterBuffer[0] ;	
				NAT_u32ValueFilter = (uint32)NAT_u16Value << 16;
				
				NAT_u32FilterSta = (uint32)NAT_u16StaOffset<<16;
				NAT_u32FilterDyn = (uint32)NAT_u16DynOffset<<16;
				NAT_u32FilterIROffset = (uint32)NAT_u16RayOffset<<16;
		}															
		else														
		{	
			pu16_1 = NAT_u16FilterBuffer;  //2012.2.8 change it to array 2, and delete '&', because this is the second order filter.
			NAT_u8Value = ALG_u8SecondOrderFilter(pu16_1,NAT_u8Value, 0x55);  //2012.2//(uint8)(ALG_u8FirstOrderFilter (NAT_u8Value, NAT__DampingK));	

			pu32_1 = (uint32 *)&NAT_u32ValueFilter;
			NAT_u16Value = ALG_u16FirstOrderFilter(pu32_1,NAT_u16Value, 4);
		}		
}


/*****************************************************************************
 Function      : NAT_u8GetValue                                              *
 Description   : The extern model get the uint8 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*****************************************************************************/
uint8 NAT_u8GetValue( NAT_tenu8VarNumber enIndex )
{
	if ( enIndex < NAT_nu8Max )
	{
		return NAT_au8Array[enIndex];
	}
	else
	{
		return NAT_au8Array[NAT_nu8Max-1];
	}
}

/*****************************************************************************
 Function      : NAT_u16GetValue                                              
 Description   : The extern model get the uint16 type variable value from this model                                                       
 Return Value  : uint16 value                                                 
*****************************************************************************/
uint16 NAT_u16GetValue( NAT_tenu16VarNumber enIndex )
{
	if ( enIndex < NAT_nu16Max )
	{
		return NAT_au16Array[enIndex];
	}
	else
	{
		return NAT_au16Array[NAT_nu16Max-1];
	}
}

/*****************************************************************************
* EOF:
******************************************************************************/
