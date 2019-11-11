/*******************************************************************************
| Module Name: Calculate the mixed air motor position according to blowout temp 
| File Name: MAC.c
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
| Sui Yanchun                        Desay SV Automotive Co., Ltd
| Zhang Shuncong                     Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2013-04-09  1.00        Sui Yanchun       First implementation
| 2015/07/14  2.00        Zhang Shuncong    Add CW and CCW,RTE define
| 2015-09-06  3.00        Zhang Shuncong    Add mix air curve according to hct temp
********************************************************************************/
#define MAC                          /* Name of the Module                */
//#define MAC_UseRTE
/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
#ifdef MAC_UseRTE
#include "ALG.h"
#include "Rte_Mac.h"
#include "BCTL.H"
#else
#include "ALG.h"                 /* algorithms */
#include "CCS.H"
#include "aird.h"
//#include "MMI.H"
#include "hct.h"
#include "Oat.h"
#include "bctl.h"
#include "EED.h"
#include "CCP.H"
#include "EVAP.H"
#endif

/* Own headerfiles */
#include "Mac.h" 
#include "Mac_Private.h" 
#include "Mac_Cfg.h" 
#include "Mac_Type.h"

/*Define location variable */
static uint8 MAC_au8Array[MAC_nu8Max];				/*The 8bit value for other modules*/
static uint16 MAC_au16Array[MAC_nu16Max];			/*The 16bit value for other modules*/
static MAC_tstPosition MAC_stPosition[SYC_ZONES];	/*The Mixed Air position information*/

static uint16 MAC_u16EvapValue;						/*For save the Evap Value*/
static uint16 MAC_u16HctValue;						/*For save the Hct Value*/
static uint16 MAC_u16BlowerTarget;					/*For save the Blower target Value*/
static uint16 MAC_u16CcsBlwoutTemp[SYC_ZONES];		/*For save the target blowout temp*/
static uint8 MAC_u8AirdAutoControl;					/*For save the index of aird position*/
static uint8 MAC_u8FilterInitFlag;					/*The Mixed air position filter init flag*/

#ifdef MAC_EvapTempFilter
static uint8  MAC_u8EvapFilterInit; /*evap filter init flag*/
static uint8  MAC_u8TimeCnt; /*evap filter init flag*/
static uint16  MAC_u16EvapValueHys;
static uint16  MAC_u16EvapValueFilter;
static uint32 MAC_u32EvapFilterPre;	/*add evap filter,150929*/
#endif
/*Mixed Air Door Position Linear*/

static const uint16 *const MAC_au16MixedAirDoorPosInFanLX[SYC_ZONES][MAC_nAirdPosMax]=
{
	{
		MAC_au16Group1DrScaleInFaceFanLowX_Tbl,
		MAC_au16Group1DrScaleInBilvl1FanLowX_Tbl,
		MAC_au16Group1DrScaleInBilvl2FanLowX_Tbl,
		MAC_au16Group1DrScaleInBilvl3FanLowX_Tbl,
		MAC_au16Group1DrScaleInFootFanLowX_Tbl,
		MAC_au16Group1DrScaleInMixed_Tbl,
		MAC_au16Group1DrScaleInScreen_Tbl
	}
	#if(SYC_ZONES >= 2)
	,
	{
		MAC_au16Group1PsScaleInFaceFanLowX_Tbl,
		MAC_au16Group1PsScaleInBilvl1FanLowX_Tbl,
		MAC_au16Group1PsScaleInBilvl2FanLowX_Tbl,
		MAC_au16Group1PsScaleInBilvl3FanLowX_Tbl,
		MAC_au16Group1PsScaleInFootFanLowX_Tbl,
		MAC_au16Group1PsScaleInMixed_Tbl,
		MAC_au16Group1PsScaleInScreen_Tbl
	}
	#endif
}; /*Low Blower speed*/

static const uint16 *const MAC_au16MixedAirDoorPosInFanMX[SYC_ZONES][MAC_nAirdPosMax]=
{
	{
		MAC_au16Group1DrScaleInFaceFanMidX_Tbl,
		MAC_au16Group1DrScaleInBilvl1FanMidX_Tbl,
		MAC_au16Group1DrScaleInBilvl2FanMidX_Tbl,
		MAC_au16Group1DrScaleInBilvl3FanMidX_Tbl,
		MAC_au16Group1DrScaleInFootFanMidX_Tbl,
		MAC_au16Group1DrScaleInMixed_Tbl,
		MAC_au16Group1DrScaleInScreen_Tbl
	}
	#if(SYC_ZONES >= 2)
	,
	{
		MAC_au16Group1PsScaleInFaceFanMidX_Tbl,
		MAC_au16Group1PsScaleInBilvl1FanMidX_Tbl,
		MAC_au16Group1PsScaleInBilvl2FanMidX_Tbl,
		MAC_au16Group1PsScaleInBilvl3FanMidX_Tbl,
		MAC_au16Group1PsScaleInFootFanMidX_Tbl,
		MAC_au16Group1PsScaleInMixed_Tbl,
		MAC_au16Group1PsScaleInScreen_Tbl
	}
	#endif
};	/*Middle Blower speed*/

static const uint16 *const MAC_au16MixedAirDoorPosInFanHX[SYC_ZONES][MAC_nAirdPosMax]=
{
	{
		MAC_au16Group1DrScaleInFaceFanHighX_Tbl,
		MAC_au16Group1DrScaleInBilvl1FanHighX_Tbl,
		MAC_au16Group1DrScaleInBilvl2FanHighX_Tbl,
		MAC_au16Group1DrScaleInBilvl3FanHighX_Tbl,
		MAC_au16Group1DrScaleInFootFanHighX_Tbl,
		MAC_au16Group1DrScaleInMixed_Tbl,
		MAC_au16Group1DrScaleInScreen_Tbl
	}
	#if(SYC_ZONES >= 2)
	,
	{
		MAC_au16Group1PsScaleInFaceFanHighX_Tbl,
		MAC_au16Group1PsScaleInBilvl1FanHighX_Tbl,
		MAC_au16Group1PsScaleInBilvl2FanHighX_Tbl,
		MAC_au16Group1PsScaleInBilvl3FanHighX_Tbl,
		MAC_au16Group1PsScaleInFootFanHighX_Tbl,
		MAC_au16Group1PsScaleInMixed_Tbl,
		MAC_au16Group1PsScaleInScreen_Tbl
	}
	#endif
};	/*High Blower speed*/


static const uint16 *const MAC_au16MixAirDoorPositionY[SYC_ZONES]=
{
	MAC_au16Group1DrMixAirDoorPositionY
	#if(SYC_ZONES >= 2)
	,
	MAC_au16Group1PsMixAirDoorPositionY
	#endif
};	/*Mixed Air Position*/

/* These are the states of the CCS decoding state machine */
static enum MAC_enStates
{
  MAC_nStateCalcA = 0,
  MAC_nStateCalcB,
  MAC_nStateCalcC,
  MAC_nStateCalcD,
  //CCS_nStateCalcE,
  MAC_nStateMax
} MAC_enState;

/*Ccp control*/
typedef enum
{
	MAC_nSetMixMotorPositonDr,
	MAC_nSetMacBlowoutTempDr,
	MAC_nSetMixMotorPositonPs,
	MAC_nSetMacBlowoutTempPs,
	MAC_nCcpForceMax
}CcpControl_MAC;
static uint8 MAC_u8CcpForceFlag=0;
static uint16 MAC_u16CcpControlData[MAC_nCcpForceMax];
#define MAC_GetCcpForceBit(index)	((MAC_u8CcpForceFlag>>index)&0x01)
#define MAC_SetCcpForceBit(index)	(MAC_u8CcpForceFlag=MAC_u8CcpForceFlag|(0x01<<index))
#define MAC_ClrCcpForceBit(index)	(MAC_u8CcpForceFlag=MAC_u8CcpForceFlag&(~(0x01<<index)))
#define MAC_ClrCcpForceByte(void)	(MAC_u8CcpForceFlag=0)
//static void Mac_vCcpInputForce(void);
static void Mac_vCcpOutputForce(void);

/*Define location function */
static uint8 MAC_u8InputValidProcess(void);
static void MAC_vInputValueProcess(void);	
static void MAC_vCalculateMixedAirScale(void);
static void MAC_vCalculateDoorPosition(void);
static void MAC_vPerformDamping(void);
#ifdef MAC_UseRTE
static void MAC_vOutputValue(void);
#endif
#ifdef MAC_EvapTempFilter
static uint16 MAC_u16EvapTempDamping (uint16 u16EvapTemp);
#endif
static void MAC_vCheckRange(void);
/***********************************************************************************
 Function      : void MAC_vReset(void)                              
 Description   : Reset container function of MAC                  
 Takes         : Nothing
 Return Value  : Nothing                                                     
************************************************************************************/
void MAC_vReset (void)
{
	uint8 u8i=0u;
    MAC_u8SwVersion = MAC_nSwVersion;
	
	for(u8i=0u; u8i<SYC_ZONES; u8i++)
	{
		MAC_u16MixedAirPos(u8i) =MAC_au16Group1DrMixAirDoorPositionY[9];
	}
}

/***********************************************************************************
 Function      : void MAC_vInit(void)                                  
 Description   : initialize function of MAC                
 Takes         : Nothing
 Return Value  : Nothing                                                
************************************************************************************/
void MAC_vInit (void)
{
	uint8 u8i=0u;
	
	MAC_u8Valid = False;	
	MAC_u16EvapValue = MAC_nDefaultEvapValue;	/*0 degree*/
	MAC_u16HctValue = MAC_nDefaultHctValue;  	/*80 degree*/
	MAC_u16BlowerTarget = MAC_nDefaultBlowerTarget;
	MAC_u8AirdAutoControl = MAC_nAirdPosBilevel2;  /*Bilevel2*/

	for(u8i=0u; u8i<SYC_ZONES; u8i++)
	{
		MAC_u16CcsBlwoutTemp[u8i] = MAC_nDefaultBlwoutTemp;   /*30 degree*/
	}
	memset((uint8 *)&MAC_stPosition[0], 0, sizeof(MAC_stPosition));  /*Clear MAC_stPositon Buffer*/

	MAC_u8FilterInitFlag = False;
	MAC_u16MixedAirPosDr=0xFFFFu;/*YSL modify, 20170318*/
	MAC_ClrCcpForceByte();

	MAC_enState = MAC_nStateCalcA;    	 /* initialise to the beginning       */

#ifdef MAC_EvapTempFilter
    MAC_u8EvapFilterInit = False; /*150929*/
	MAC_u16EvapValueHys = False;
	MAC_u16EvapValueFilter = False;
	MAC_u8TimeCnt = False;
#endif
}

/***********************************************************************************
 Function      : void MAC_vDeinit (void)                                  
 Description   : De-init function of MAC             
 Takes         : Nothing
 Return Value  : Nothing                                                                                          
************************************************************************************/
void MAC_vDeinit (void)
{
	MAC_u8Valid = False;	
}


/***********************************************************************************
 Function      : void ,MAC_vActive (void)                                  
 Description   : Acive function of MAC          
 Takes         : Nothing
 Return Value  : Nothing                                                                                          
************************************************************************************/
void MAC_vActive(void)
{

}

/*****************************************************************************
 Function      : MAC_vMain (void)                                    
 Description   : Main container function of MAC
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void MAC_vMain(void)
{
	if (MAC_u8InputValidProcess() == True)
	{
	 	switch (MAC_enState)
    	{
        	case MAC_nStateCalcA:
				MAC_vInputValueProcess();			/*Process the input value from other modules*/
				MAC_vCalculateMixedAirScale();		/*Calculate the Mixed Air Scale*/
				MAC_enState = MAC_nStateCalcB;
				break;
			case MAC_nStateCalcB:
				MAC_vCalculateDoorPosition();		/*Calculates the mixed air door position*/
				MAC_enState = MAC_nStateCalcC;
				break;
			case MAC_nStateCalcC:
				MAC_vPerformDamping();				/*Perform damping for the mixed air door position*/
				MAC_enState = MAC_nStateCalcA;
				MAC_u8Valid = True;
				break;
			default:
    			MAC_enState = MAC_nStateCalcA; /*re-operation from A*/
    			break;
        }
	}
	else
	{
		/*Nothing do do*/
	}
	Mac_vCcpOutputForce();
    
    MAC_vCheckRange();
    
	#ifdef MAC_UseRTE
	MAC_vOutputValue();						/*Output value to RTE*/
	#endif
}


/*****************************************************************************
 Function      : MAC_u8InputValidProcess                                            
 Description   : Process the input value which are from other modules   
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static uint8 MAC_u8InputValidProcess(void)
{
	uint8 u8ValidFlg = True;
	uint8 u8CcsValid = False;
	uint8 u8HctValid = False;
	uint8 u8EvapValid = False;
	
	u8CcsValid = MAC_u8GetCcsValue_Valid;
	u8HctValid = MAC_u8GetHctValue_Valid;
	u8EvapValid = MAC_u8GetEvapValue_Valid;
	
	if((u8CcsValid == True)&&(u8HctValid == True)&&(u8EvapValid == True))
	{
		u8ValidFlg = True;	
	}
	else
	{
		u8ValidFlg = False;	
	}
	
    return u8ValidFlg;
}


/*****************************************************************************
 Function      : MAC_vInputValueProcess                                          
 Description   : Process the input value which are from other modules   
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void MAC_vInputValueProcess(void)
{
	uint8 u8i = False;
	uint8 u8InputError = False;
	uint16 u16EvapValue = MAC_nDefaultEvapValue;
	uint16 u16HctValue = MAC_nDefaultHctValue;
	uint16 u16BlowerTarget = MAC_nDefaultBlowerTarget;
	uint16 u8AirdAutoControl = MAC_nAirdPosBilevel2;
#if(SYC_ZONES >= 2)
	uint16 u16CcsBlwoutTemp[SYC_ZONES] = {MAC_nDefaultBlwoutTemp,MAC_nDefaultBlwoutTemp};
#else
	uint16 u16CcsBlwoutTemp[SYC_ZONES] = {MAC_nDefaultBlwoutTemp};
#endif

	u16EvapValue = MAC_u16GetEvapValue_EvapMacValue;
	u16HctValue = MAC_u16GetHctValue_HctTemp;
	u16BlowerTarget = MAC_u16GetBctlValue_BlowerTarget;
	u8AirdAutoControl = MAC_u8GetAirdValue_AutoControl;
	u16CcsBlwoutTemp[0] = MAC_u16GetCcsValue_BlowoutTempDr;
	
#if(SYC_ZONES >= 2)
	u16CcsBlwoutTemp[1] = MAC_u16GetCcsValue_BlowoutTempPs;/*SX5*/
#endif

	uint16 *pu16_1 = NULL;
	

	/*Input1:--------EvapValue process--------------*/
	if(u16EvapValue > MAC_nMaxTemp)
	{
		u8InputError = True;			
	}
	else
	{
		MAC_u16EvapValue = u16EvapValue;
	}

	/*Process Evap Hysteresis */
	#ifdef MAC_EvapTempFilter
    MAC_u16EvapTempHys = MAC_u16EvapTempDamping(MAC_u16EvapValue);
	#else
	MAC_u16EvapTempHys = MAC_u16EvapValue;
    #endif
	
	/*Input2:--------HctValue process--------------*/
	if(u16HctValue > MAC_nMaxTemp)
	{
		u8InputError = True;			
	}
	else
	{
		MAC_u16HctValue = u16HctValue;	
	}
	/*Process Hct Hysteresis */	
	pu16_1= &(MAC_u16HctTempHys);
   	ALG_vHysteresis_16(pu16_1, MAC_u16HctValue, MAC_u16Group1HctHysteresis);


	/*Input3:--------Blower speed process--------------*/
	if(u16BlowerTarget > MAC_nMaxBlowerTarget)
	{
		u8InputError = True;			
	}
	else
	{
		MAC_u16BlowerTarget = u16BlowerTarget;
	}

	/*Process Bctl Hysteresis */
	pu16_1= &(MAC_u16BlowSpeedHys);
   	ALG_vHysteresis_16(pu16_1, MAC_u16BlowerTarget, MAC_u16Group1BlowerHysteresis);
	
	/*Input4:--------Air distribution process--------------*/
	if(u8AirdAutoControl > MAC_nAirdPosScreen)
	{
		u8InputError = True;			
	}
	else
	{
		MAC_u8AirdAutoControl = u8AirdAutoControl;
	}

	/*Input5:--------CCS_BlowoutTemp process--------------*/
	for(u8i=0u; u8i<SYC_ZONES; u8i++)
	{
		if(u16CcsBlwoutTemp[u8i] > MAC_nMaxTemp)
		{
			u8InputError = True;
		}
		else
		{
			MAC_u16CcsBlwoutTemp[u8i] = u16CcsBlwoutTemp[u8i];	
		}
	}

	/*Error code process*/
	if (u8InputError == True)
	{
		BIT_SET(MAC_u16ErrorCode,MAC_nBitInputValueErr);
	}
	else
	{
		BIT_CLEAR(MAC_u16ErrorCode,MAC_nBitInputValueErr);
	}
}


/*****************************************************************************
 Function      : MAC_vCalculateMixedAirScale                                        
 Description   : Calculate the Mixed Air Scale according to the target 
                 temperature and the evaporator Temp and heater core signal 
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void MAC_vCalculateMixedAirScale(void)
{
	uint8 u8i = 0;
	uint32 u32TempRel = 0;
	uint16 u16HctEvapDiff = 0;

	for(u8i=0; u8i<SYC_ZONES; u8i++)
	{
		if(MAC_u16CcsBlwoutTemp[u8i]>=MAC_u16HctTempHys)
		{/*The Target blowout temp is equal or more than hct*/
			
			MAC_u16BlowoutTemp(u8i) = MAC_u16HctTempHys;
			MAC_stPosition[u8i].u16Nominal = MAC_nMaxNominal;
		}
		else if(MAC_u16CcsBlwoutTemp[u8i]<=MAC_u16EvapTempHys)
		{/*The Target blowout temp is equal or less than Tevap*/
			
			MAC_u16BlowoutTemp(u8i) = MAC_u16EvapTempHys;
			MAC_stPosition[u8i].u16Nominal = 0;
		}
		else
		{
			/*Calculate the diff bet Hct and Evap*/
			u16HctEvapDiff = MAC_u16HctTempHys - MAC_u16EvapTempHys;
			
			#ifdef MAC_LimitHctEvapDiff
			MAC_RangeCheck(u16HctEvapDiff,MAC_u16Group1HctEvapMinDiff,0xFFFF);/*limit min diff,160203*/
			#endif

			/*Calculate the Scale*/
			u32TempRel = MAC_nMaxNominal * (uint32) (MAC_u16CcsBlwoutTemp[u8i] - MAC_u16EvapTempHys);
			u32TempRel = u32TempRel /u16HctEvapDiff;
			MAC_stPosition[u8i].u16Nominal = (uint16)u32TempRel;	
			
			MAC_u16BlowoutTemp(u8i) = MAC_u16CcsBlwoutTemp[u8i];	/*Calculate the actual blowout temp*/
		}

		MAC_u16FlapRatio(u8i) = MAC_stPosition[u8i].u16Nominal;/*SX5*/
	}

	/*Calculate the average actual blowout temp*/
	#if (SYC_ZONES == 2)
	MAC_u16BlowoutTempAvg = (MAC_u16BlowoutTempDr*MAC_nDrvSideFactor\
					 			+ MAC_u16BlowoutTempPs*(16-MAC_nDrvSideFactor))>>4; 
	MAC_u16FlapRatioAvg = (MAC_u16FlapRatioDr*MAC_nDrvSideFactor\
					 			+ MAC_u16FlapRatioPs*(16-MAC_nDrvSideFactor))>>4; /*SX5*/
	#else
	MAC_u16BlowoutTempAvg = MAC_u16BlowoutTempDr;
	#endif
			
}


/*****************************************************************************
 Function      : MAC_vCalculateDoorPosition                                        
 Description   : calculates the mixed air door position according to the mixed
 				 air scale in different Fan and different air distribution
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void MAC_vCalculateDoorPosition(void)
{
	uint8 u8i = 0;
	uint16 *pu16_1 = NULL;
    uint16 *pu16_2 = NULL;
    uint16 au16MixedAirPos[3] = {0, 0, 0};

	for(u8i=0; u8i<SYC_ZONES; u8i++)
	{
		/* Caculate the position curve during low speed mode */
		pu16_1 = (uint16 *) MAC_au16MixedAirDoorPosInFanLX[u8i][MAC_u8AirdAutoControl];
		pu16_2 = (uint16 *) MAC_au16MixAirDoorPositionY[u8i];
		au16MixedAirPos[0] = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,MAC_stPosition[u8i].u16Nominal,
	                                                       					   MAC_nDrMixAirDoorPositionY_Len);

		/* Caculate the position curve during mid speed mode */
	    pu16_1 = (uint16 *) MAC_au16MixedAirDoorPosInFanMX[u8i][MAC_u8AirdAutoControl];
		au16MixedAirPos[1] = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,MAC_stPosition[u8i].u16Nominal,
									 										   MAC_nDrMixAirDoorPositionY_Len);

		/* Caculate the position curve during high speed mode */
		pu16_1 = (uint16 *) MAC_au16MixedAirDoorPosInFanHX[u8i][MAC_u8AirdAutoControl];
		au16MixedAirPos[2] = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,MAC_stPosition[u8i].u16Nominal,
									 										   MAC_nDrMixAirDoorPositionY_Len);

		/* Select the suitable curve according to the blower speed. */
		pu16_1 = (uint16 *)&MAC_au16Group1BlowerSelect_Tbl[0];
		pu16_2 = (uint16 *)au16MixedAirPos;
		MAC_stPosition[u8i].u16Raw = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,MAC_u16BlowSpeedHys,3);
	}

}


/*****************************************************************************
 Function      : MAC_vPerformDamping                                          
 Description   : Perform the damping for the mixed air door position
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void MAC_vPerformDamping(void)
{
	uint8 u8i = 0;
	uint16 *pu16_1;
	uint32 *pu32_1;

	for(u8i=0; u8i<SYC_ZONES; u8i++)
	{
		if(MAC_u8FilterInitFlag == False)
		{/*Filters not yet initialized*/

			MAC_stPosition[u8i].u16Value = MAC_stPosition[u8i].u16Raw;
			MAC_stPosition[u8i].u32PT2_Save[0] = (((uint32)MAC_stPosition[u8i].u16Raw) << 16) + 0x8000U;
			MAC_stPosition[u8i].u32PT2_Save[1] = MAC_stPosition[u8i].u32PT2_Save[0];

			MAC_u8FilterInitFlag = True;
		}
		else
		{
			pu32_1 = &(MAC_stPosition[u8i].u32PT2_Save[0]);
			MAC_stPosition[u8i].u16Value = ALG_u16SecondOrderFilter(pu32_1,MAC_stPosition[u8i].u16Raw,MAC_nPt2K);
		}

		/* Hysteresis */
		pu16_1 = &(MAC_stPosition[u8i].u16Hyst);
		ALG_vHysteresis_16(pu16_1,MAC_stPosition[u8i].u16Value,MAC_u16Group1MacPosiHysteresis);

	#ifdef MAC_StopInOffMode
		/*Mac motor will not move under OFF*/
        if (MAC_u16BlowerTarget == False)
        {
            //MAC_u16MixedAirPos(u8i) = MAC_u16PtaMotorFb[u8i];   /*stop motor driving when blower off*/
        }
		else
		{
			MAC_u16MixedAirPos(u8i) = MAC_stPosition[u8i].u16Hyst;
		}
	#else
		MAC_u16MixedAirPos(u8i) = MAC_stPosition[u8i].u16Hyst;
    #endif
	}
}


/*****************************************************************************
 Function      : Mac_vCcpInputForce                                 
 Description   : force Input value
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void Mac_vCcpOutputForce(void)
{	
	if(MAC_GetCcpForceBit(MAC_nSetMixMotorPositonDr))
	{
		MAC_u16MixedAirPosDr=MAC_u16CcpControlData[MAC_nSetMixMotorPositonDr];
	}
	else
	{
	}
	if(MAC_GetCcpForceBit(MAC_nSetMacBlowoutTempDr))
	{
		MAC_u16BlowoutTempDr=MAC_u16CcpControlData[MAC_nSetMacBlowoutTempDr];
	}
	else
	{
	}

	if(MAC_GetCcpForceBit(MAC_nSetMixMotorPositonPs))
	{
        //MAC_u16MixedAirPosDr=MAC_u16CcpControlData[MAC_nSetMixMotorPositonPs];
		MAC_u16MixedAirPosPs=MAC_u16CcpControlData[MAC_nSetMixMotorPositonPs];/*Modify by LT,20160713*/
	}
	else
	{
	}
	if(MAC_GetCcpForceBit(MAC_nSetMacBlowoutTempPs))
	{
        //MAC_u16BlowoutTempDr=MAC_u16CcpControlData[MAC_nSetMacBlowoutTempPs];
		MAC_u16BlowoutTempPs=MAC_u16CcpControlData[MAC_nSetMacBlowoutTempPs];/*Modify by LT,20160713*/
	}
	else
	{
	}
}


#ifdef MAC_EvapTempFilter
/* ===========================================================================
* Function   : void MAC_vEvapTempDamping (void)
* Description: This function performs the evap temp
* Takes      : Nothing
* Returns    : Nothing
*/
static uint16 MAC_u16EvapTempDamping (uint16 u16EvapTemp)
{
	uint8 u8DampK=False;
	uint16 *pu16_1;
	uint32 *pu32_1;
    
	/* Now we have the intended set value, which is to be filtered. */
	if (MAC_u8EvapFilterInit == False)
	{
		MAC_u8EvapFilterInit = True;
		MAC_u32EvapFilterPre = (uint32)u16EvapTemp << 16;
        MAC_u16EvapValueHys = u16EvapTemp;
		MAC_u16EvapValueFilter = u16EvapTemp;
	}
	else
	{
		/*-5 ~ 12deg, filter slow*/
		if ((MAC_u16EvapValueFilter >= MAC_nEvapFilterTempLo) \
			&& (u16EvapTemp >= MAC_nEvapFilterTempLo)\
			&& (MAC_u16EvapValueFilter <= MAC_nEvapFilterTempHi)\
			&& (u16EvapTemp <= MAC_nEvapFilterTempHi))
		{
			u8DampK = MAC_nEvapFilterSlow;
		}
		else
		{
			u8DampK = MAC_nEvapFilterFast;
		}
	    
	    /*Added filter for Evap, count every 1s */
		if(MAC_u8TimeCnt < 10)
		{
			MAC_u8TimeCnt++;
		}
		else
		{
			MAC_u8TimeCnt=0;
			pu32_1 = &MAC_u32EvapFilterPre;
			MAC_u16EvapValueFilter = ALG_u16FirstOrderFilter (pu32_1,u16EvapTemp, u8DampK);
		}

	    /*Hysteresis, 2.0deg*/
		pu16_1 = &MAC_u16EvapValueHys;
		ALG_vHysteresis_16(pu16_1,MAC_u16EvapValueFilter,MAC_u16Group1EvapHysteresis);
	}
    return MAC_u16EvapValueHys;
}
#endif

//#ifndef MAC_UseRTE
/*****************************************************************************
 Function      : HCT_u8GetValue                                              *
 Description   : The extern model get the uint8 type variable value from this*
				     model,                                                      *
                 get position only.                                          *
 Return Value  : uint8 value                                                 *
*****************************************************************************/
uint8 MAC_u8GetValue( MAC_tenu8VarNumber enIndex )
{
	if ( enIndex < MAC_nu8Max )
	{
		return MAC_au8Array[enIndex];
	}
	else
	{
		return MAC_au8Array[MAC_nu8Max-1];
	}
}

/*****************************************************************************
 Function      : MAC_u16GetValue
 Description   : The extern model get the uint16 type variable value from this model
 Return Value  : uint16 value
*****************************************************************************/
uint16 MAC_u16GetValue( MAC_tenu16VarNumber enIndex )
{
	if ( enIndex < MAC_nu16Max )
	{
		return MAC_au16Array[enIndex];
	}
	else
	{
		return MAC_au16Array[MAC_nu16Max-1];
	}
}
//#endif


/*****************************************************************************
 Function      : Mac_u8ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType MAC_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord)
{
	uint8 u8Result=RTE_E_OK;
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				MAC_ClrCcpForceByte();
				break;
			case 1:
            case 0xA1:/*modify by LT,20160713*/
				MAC_SetCcpForceBit(MAC_nSetMixMotorPositonDr);
				MAC_u16CcpControlData[MAC_nSetMixMotorPositonDr]=CcpControlWord.CcpContronData;
				break;
			case 2:
            case 0xA2:/*modify by LT,20160713*/
				MAC_ClrCcpForceBit(MAC_nSetMixMotorPositonDr);
				MAC_u16CcpControlData[MAC_nSetMixMotorPositonDr]=0;
				break;
			case 3:
				MAC_SetCcpForceBit(MAC_nSetMacBlowoutTempDr);
				MAC_u16CcpControlData[MAC_nSetMacBlowoutTempDr]=CcpControlWord.CcpContronData;
				break;
			case 4:
				MAC_ClrCcpForceBit(MAC_nSetMacBlowoutTempDr);
				MAC_u16CcpControlData[MAC_nSetMacBlowoutTempDr]=0;
				break;
			case 5:
            case 0xA3:/*modify by LT,20160713*/
				MAC_SetCcpForceBit(MAC_nSetMixMotorPositonPs);
				MAC_u16CcpControlData[MAC_nSetMixMotorPositonPs]=CcpControlWord.CcpContronData;
				break;
			case 6:
            case 0xA4:/*modify by LT,20160713*/
				MAC_ClrCcpForceBit(MAC_nSetMixMotorPositonPs);
				MAC_u16CcpControlData[MAC_nSetMixMotorPositonPs]=0;
				break;
			case 7:
				MAC_SetCcpForceBit(MAC_nSetMacBlowoutTempPs);
				MAC_u16CcpControlData[MAC_nSetMacBlowoutTempPs]=CcpControlWord.CcpContronData;
				break;
			case 8:
				MAC_ClrCcpForceBit(MAC_nSetMacBlowoutTempPs);
				MAC_u16CcpControlData[MAC_nSetMacBlowoutTempPs]=0;
				break;
			default:
                u8Result= RTE_E_INVALID;
				break;
		}
	}
	else
	{
		MAC_ClrCcpForceByte();
	}
        return u8Result;
}


#ifdef MAC_UseRTE
/*****************************************************************************
 Function      : MAC_vOutputValue                                    
 Description   : Output the value to RTE 
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void MAC_vOutputValue(void)
{
	Rte_IWrite_Mac_vReset_MacSwVersion_u8Version(MAC_u8SwVersion);
	Rte_IWrite_Mac_vMain_MacValid_u8Flag(MAC_u8Valid);
	
	Rte_IWrite_Mac_vMain_MacErrorCode_u16BitMap(MAC_u16ErrorCode);
	
	Rte_IWrite_Mac_vMain_MacMixedAirPosDr_u16MotorPos(MAC_u16MixedAirPosDr);
	Rte_IWrite_Mac_vMain_MacMixedAirPosPs_u16MotorPos(MAC_u16MixedAirPosPs);

	Rte_IWrite_Mac_vMain_MacMixedAirMinPosDr_u16MotorPos(MAC_au16Group1DrMixAirDoorPositionY[0]);
	Rte_IWrite_Mac_vMain_MacMixedAirMaxPosDr_u16MotorPos(MAC_au16Group1DrMixAirDoorPositionY[MAC_nDrMixAirDoorPositionY_Len-1]);

	Rte_IWrite_Mac_vMain_MacMixedAirMinPosPs_u16MotorPos(MAC_au16Group1PsMixAirDoorPositionY[0]);
	Rte_IWrite_Mac_vMain_MacMixedAirMaxPosPs_u16MotorPos(MAC_au16Group1PsMixAirDoorPositionY[MAC_nPsMixAirDoorPositionY_Len-1]);

	Rte_IWrite_Mac_vMain_MacFlapRatioDr_u16Percent(MAC_u16FlapRatioDr);
	Rte_IWrite_Mac_vMain_MacFlapRatioPs_u16Percent(MAC_u16FlapRatioPs);
	Rte_IWrite_Mac_vMain_MacFlapRatioAvg_u16Percent(MAC_u16FlapRatioAvg);

	Rte_IWrite_Mac_vMain_MacBlowoutTempDr_u16Temp(MAC_u16BlowoutTempDr);
	Rte_IWrite_Mac_vMain_MacBlowoutTempPs_u16Temp(MAC_u16BlowoutTempPs);
	Rte_IWrite_Mac_vMain_MacBlowoutTempAvg_u16Temp(MAC_u16BlowoutTempAvg);
	
	Rte_IWrite_Mac_vMain_MacBlwSpeedHys_u16BlwSpd(MAC_u16BlowSpeedHys);
	Rte_IWrite_Mac_vMain_MacEvapTempHys_u16Temp(MAC_u16EvapTempHys);
	Rte_IWrite_Mac_vMain_MacHctHys_u16Temp(MAC_u16HctTempHys);
}

#endif

/*****************************************************************************
 Function      : MAC_vCheckRange
 Description   : void
 Return Value  : void
*****************************************************************************/
static void MAC_vCheckRange(void)
{
	uint8 u8i = 0;

	for(u8i=0; u8i<SYC_ZONES; u8i++)
	{
        if(MAC_u16MixedAirPos(u8i) < MAC_au16Group1MacLimitPosY_Tbl[0])
        {
		    MAC_u16MixedAirPos(u8i) = MAC_au16Group1MacLimitPosY_Tbl[0];
        }
        else if(MAC_u16MixedAirPos(u8i) > MAC_au16Group1MacLimitPosY_Tbl[1])
        {
            MAC_u16MixedAirPos(u8i) = MAC_au16Group1MacLimitPosY_Tbl[1];
        }
	}
}

/*****************************************************************************
* EOF:Mac.c
******************************************************************************/


