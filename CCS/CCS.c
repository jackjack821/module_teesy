

/*******************************************************************************
| Module Name: Calculate the target blowout temp ,target set temo and SI
| File Name: CCS.c
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
| 2016-02-01  A3          Zhang Shuncong    add RTE interface
********************************************************************************/

#define CCS                         /* Name of the Module                */
//#define CCS_UseRTE
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
#ifdef CCS_UseRTE
#include "ALG.h"
#include "Rte_Ccs.h"
#else
#include "ALG.h"
#include "AIRD.h"
#include "MMi.h"
//#include "ICT.h"
#include "OAT.h"
#include "SUN.h"
#include "BCTL.h"
#include "VEL.h"

#endif
/* Own headerfiles */
#include "CCS.h"
#include "Ccs_Cfg.h"
#include "CCS_Private.h"
#include "CCS_Type.h"

#ifdef CCS_UseCtsInput
#include "CTS_Export.h"
#endif
/*Define location variable */
static uint8 CCS_au8Array[CCS_nu8Max];
static uint16 CCS_au16Array[CCS_nu16Max];

static uint8 CCS_u8MmiSetTemp[SYC_ZONES];		/*For saving Setting Temperature value from MMI*/
static uint16 CCS_u16BlwCcsTarget;				/*For saving u16BlwCcsTarget value from BCTL*/
static uint16 CCS_u16OatValue;					/*For saving u16OatValue value from OAT*/
static uint16 CCS_u16IctValue[CCS_IctSensorNum];					/*For saving u16IctValue value from ICT*/


static uint16 CCS_u16OatNewValue;				/*for oat filter*/
static uint32 CCS_u32BlwoutTempPre[SYC_ZONES];	/*save the last blowoutTemp*/
static uint8 CCS_u8FilterInit;
static uint8 CCS_u8TimeCounter;
static uint8 CCS_u8MmiSetTempPre[SYC_ZONES];	/*save the last SettingTemp*/

static uint8 CCS_u8IctValid[SYC_ZONES];
static uint8 CCS_u8BlowoutTempValid[SYC_ZONES];
static const uint16 *const CCS_au16SiBlowTempGainZ_Tbl[] = 
{
	CCS_au16Group1SiBlowTempGainY1_Tbl,
	CCS_au16Group1SiBlowTempGainY2_Tbl,
	CCS_au16Group1SiBlowTempGainY3_Tbl,
	CCS_au16Group1SiBlowTempGainY4_Tbl
}; /*the Z axis */

static const uint16 *const CCS_au16OatBlowTempOffsetZ_Tbl[] = 
{
	CCS_au16Group1OatBlowTempOffsetY1_Tbl,
	CCS_au16Group1OatBlowTempOffsetY2_Tbl,
	CCS_au16Group1OatBlowTempOffsetY3_Tbl,
	CCS_au16Group1OatBlowTempOffsetY4_Tbl
}; /*the Z axis */


#if (SYC_ZONES >= 2)
static const uint16 *const CCS_au16DrTsetBlowTempGainZ_Tbl[] = 
{
	CCS_au16Group1DrTsetBlowTempGainY1_Tbl,
	CCS_au16Group1DrTsetBlowTempGainY2_Tbl,
	CCS_au16Group1DrTsetBlowTempGainY3_Tbl,
	CCS_au16Group1DrTsetBlowTempGainY4_Tbl
}; /*the Z axis */

static const uint16 *const CCS_au16PsTsetBlowTempGainZ_Tbl[] = 
{
	CCS_au16Group1PsTsetBlowTempGainY1_Tbl,
	CCS_au16Group1PsTsetBlowTempGainY2_Tbl,
	CCS_au16Group1PsTsetBlowTempGainY3_Tbl,
	CCS_au16Group1PsTsetBlowTempGainY4_Tbl
}; /*the Z axis */
#endif

/* These are the states of the CCS decoding state machine */
static enum CCS_enStates
{
  CCS_nStateCalcA = 0,
  CCS_nStateCalcB,
  CCS_nStateCalcC,
  CCS_nStateCalcD,
  //CCS_nStateCalcE,
  CCS_nStateMax
} CCS_enState;

/*Ccp control*/
typedef enum
{
	CCS_nSetCcsBlwoutTempDr,
	CCS_nSetCcsBlwoutTempPs,
	CCS_nSetCcsSetTempDr,
	CCS_nSetCcsSetTempPs,
	CCS_nCcpForceMax
}CcpControl_CCS;
static uint8 CCS_u8CcpForceFlag=0;
static uint16 CCS_u16CcpControlData[CCS_nCcpForceMax];
#define CCS_GetCcpForceBit(index)	((CCS_u8CcpForceFlag>>index)&0x01)
#define CCS_SetCcpForceBit(index)	(CCS_u8CcpForceFlag=CCS_u8CcpForceFlag|(0x01<<index))
#define CCS_ClrCcpForceBit(index)	(CCS_u8CcpForceFlag=CCS_u8CcpForceFlag&(~(0x01<<index)))
#define CCS_ClrCcpForceByte(void)	(CCS_u8CcpForceFlag=0)
//static void Ccs_vCcpInputForce(void);
static void CCS_vCcpBlowerTempOutputForce(void);
static void CCS_vCcpSetTempOutputForce(void);

/*Define location function */
static uint8 CCS_u8InputValidProcess(void);
static void CCS_vInputValueProcess(void);
static void CCS_vCorrectSetTemp(void);		
static void CCS_vCalculateSi(void);		
static void CCS_vPControlOffset(void);			
static void CCS_vPreControlOffset(void);
static void CCS_vSplitZoneTemp(void);
static void CCS_vCalculateBlowoutTemp(void);	
#ifdef CCS_UseCtsInput
static void CCS_vUseCtsBlowoutTemp(void);
#endif
uint16 CCS_u16ALG3DLookupTable\
(uint16 pu16_X[], uint16 pu16_Y[], uint16 *pu16_Z[], uint16 InputX, uint16 InputY, const uint8 X_Len, const uint8 Y_Len);

static uint16 CCS_u16Convert2InternalTempUnit (uint8 u8InputTemp);
#ifdef CCS_UseRTE
static void CCS_vOutputValue(void);
#endif

/***********************************************************************************
 Function      : void CCS_vReset(void)                              
 Description   : Reset container function of CCS                   
 Takes         : Nothing
 Return Value  : Nothing                                                     
************************************************************************************/
void CCS_vReset (void)
{
	CCS_u8SwVersion = CCS_nSwVersion;		/*SW version*/
}


/***********************************************************************************
 Function      : void CCS_vInit(void)                                  
 Description   : initialize function of CCS                 
 Takes         : Nothing
 Return Value  : Nothing                                                
************************************************************************************/
void CCS_vInit (void)
{
	uint8 u8i = 0;

	CCS_u8Valid = False;
	CCS_u8SetTempValid = False;
	CCS_u16BlwCcsTarget = CCS_nDefaultBlwCcsTarget;
	CCS_u16OatValue = CCS_nDefaultOatValue;				/*20 degree*/
	CCS_u16OatNewValue = CCS_nDefaultOatValue;				/*20 degree*/
	//CCS_u16IctValue = CCS_nDefaultIctValue;				/*22 degree*/
	for(u8i=0; u8i<CCS_IctSensorNum; u8i++)
	{
		CCS_u16IctValue[u8i] = CCS_nDefaultIctValue;
	}
	for(u8i=0; u8i<SYC_ZONES; u8i++)
	{
		CCS_u8MmiSetTemp[u8i] = CCS_nDefaultMmiSetTemp;				/*22 degree*/
		CCS_u32BlwoutTempPre[u8i] = 0;
		CCS_u8MmiSetTempPre[u8i] = 0xf0;
	}

	CCS_u8FilterInit = False;
	CCS_u8TimeCounter = 0;
	CCS_ClrCcpForceByte();
	CCS_enState = CCS_nStateCalcA;    	 /* initialise to the beginning       */

}


/***********************************************************************************
 Function      : void CCS_vDeinit (void)                                  
 Description   : De-init function of CCS              
 Takes         : Nothing
 Return Value  : Nothing                                                                                          
************************************************************************************/
void CCS_vDeinit (void)
{
	CCS_u8Valid = False;/*161220*/
	CCS_u8SetTempValid = False;
	CCS_ClrCcpForceByte();
}


/*****************************************************************************
 Function: 		void CCS_vActive( void)                                      
 Description: 	Acive function of CCS
 Takes: 		Nothing
 Return Value: 	Nothing                                                    
*****************************************************************************/
void CCS_vActive(void)
{

}


/*****************************************************************************
 Function      : CCS_vMain (void)                                    
 Description   : Main container function of CCS
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void CCS_vMain (void)
{
	if(CCS_u8InputValidProcess() == True) /*The ambient temp and Incar temp are valid*/
	{		
        switch (CCS_enState)
    	{
        	case CCS_nStateCalcA:
				CCS_vInputValueProcess();		/*Process the values from other modules*/
				CCS_vCorrectSetTemp();			/*Calculate the correct setting temperature.*/
                CCS_vCcpSetTempOutputForce();
				CCS_vCalculateSi();		/*Calculate the system index.*/
				CCS_enState = CCS_nStateCalcB;

				#ifdef CCS_UseCtsInput
				CCS_vUseCtsBlowoutTemp();
                #if (SYC_ZONES >= 2)
				if ((CCS_u8BlowoutTempValid[0] == True)&&(CCS_u8IctValid[0]==True)\
                    &&(CCS_u8BlowoutTempValid[1] == True)&&(CCS_u8IctValid[1]==True)) /*161220*/
                #else
                if((CCS_u8BlowoutTempValid[0] == True)&&(CCS_u8IctValid[0]==True))
                #endif
				{
					CCS_u8Valid = True;/*0xA3,160804*/
				}
				CCS_enState = CCS_nStateCalcA;
				#endif
				CCS_vCcpBlowerTempOutputForce();
				break;
			case CCS_nStateCalcB:
				#ifdef CCS_UseCtsInput
				CCS_enState = CCS_nStateCalcA;
				#else
				CCS_vPControlOffset();			/*Calculate the P-control blowout temperature offset.*/
				CCS_vPreControlOffset();		/*Calculate the Pre-control blowout temperature offset.*/
				CCS_enState = CCS_nStateCalcC;
				#endif
				break;
			case CCS_nStateCalcC:
				#ifdef CCS_UseCtsInput
				CCS_enState = CCS_nStateCalcA;
				#else
				CCS_vSplitZoneTemp();
				CCS_vCalculateBlowoutTemp();	/*Calculate the final blowout temperature.*/
				#endif
				CCS_enState = CCS_nStateCalcA;
				CCS_u8Valid = True;
				CCS_u8SetTempValid = True;
				break;
			default:
    			CCS_enState = CCS_nStateCalcA; /*re-operation from A*/
    			break;
        }
	}
	else
	{
		/*Nothing do to */
	}
	
	//CCS_vCcpOutputForce();
	
	#ifdef CCS_UseRTE
	CCS_vOutputValue();					/*Output value to RTE*/
	#endif
}

/*****************************************************************************
 Function      : CCS_u8InputValidProcess                                            
 Description   : Process the input value which are from other modules   
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static uint8 CCS_u8InputValidProcess(void)
{
	uint8 u8ValidFlg = True; 
	uint8 u8IctValid = False;
	uint8 u8OatValid = False;
	//uint16 u16IctValue[CCS_IctSensorNum];
	/*Get values from other modules*/
	u8OatValid = CCS_u8GetOatValue_Valid;
	u8IctValid = CCS_u8GetIctValue_Valid;
	#ifdef CCS_UseCtsInput
	u8IctValid = True; /*170114*/
	#endif
	if((u8OatValid == True)&&(u8IctValid == True))
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
 Function      : CCS_vInputValueProcess                                          
 Description   : Process the input value which are from other modules   
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void CCS_vInputValueProcess(void)
{
	uint8 u8i = False;
	uint8 u8SunValid = False;
	uint8 u8VelValid = False;
	uint8 u8InputError = False;
	uint16 u16BlwCcsTarget = CCS_nDefaultBlwCcsTarget;
	uint16 u16VelTempOffset = CCS_nDefaultTempOffset;
	uint16 u16OatValue = CCS_nDefaultOatValue;
	uint16 u16IctValue[CCS_IctSensorNum];
	
#if(SYC_ZONES >= 2)
	uint8 u8MmiSetTemp[SYC_ZONES] = {CCS_nDefaultMmiSetTemp,CCS_nDefaultMmiSetTemp};
	uint16 u16SunTempOffset[SYC_ZONES] = {CCS_nDefaultTempOffset,CCS_nDefaultTempOffset};
#else
	uint8 u8MmiSetTemp[SYC_ZONES] = {CCS_nDefaultMmiSetTemp};
	uint16 u16SunTempOffset[SYC_ZONES] = {CCS_nDefaultTempOffset};
#endif


	uint16 *pu16_1 = NULL;

	u8SunValid = CCS_u8GetSunValue_Valid;
	u8VelValid = CCS_u8GetVelValue_Valid;

	u16BlwCcsTarget = CCS_u16GetBctlValue_BlowerTarget;
	u16VelTempOffset = CCS_u16GetVelValue_TempOffset;
	u16OatValue = CCS_u16GetOatValue_OatValue;
	//u16IctValue = CCS_u16GetIctValue_IctValue;
#ifdef CCS_UseCtsInput
	CCS_u8IctValid[0] = CTS_enGetHeadZoneTempLExport(&u16IctValue[0]);
	#if (CCS_IctSensorNum >1)
	CCS_u8IctValid[1] = CTS_enGetHeadZoneTempRExport(&u16IctValue[1]);
	#endif
#else
	u16IctValue[0] = CCS_u16GetIctValue_IctValue;
	#if (CCS_IctSensorNum >1)
	u16IctValue[1] = CCS_u16GetIctValue_IctValue;
	#endif
#endif
	u8MmiSetTemp[0] = CCS_u8GetMmiValue_SetTempDr;
	
	u16SunTempOffset[0] = CCS_u16GetSunValue_TempOffsetDr;/*SX5*/
#if(SYC_ZONES >= 2)
	u8MmiSetTemp[1] = CCS_u8GetMmiValue_SetTempPs;
	u16SunTempOffset[1] = CCS_u16GetSunValue_TempOffsetPs;/*FE-3Z*/
#endif

	/*ICT_Value process*/
	if(u16IctValue[0] > CCS_Temp_UMAX)
	{
		u8InputError = True;		
	}
	else
	{
		CCS_u16IctValue[0] = u16IctValue[0];	
	}

#if (CCS_IctSensorNum >1)
	if(u16IctValue[1] > CCS_Temp_UMAX)
	{
		u8InputError = True;		
	}
	else
	{
		CCS_u16IctValue[1] = u16IctValue[1];	
	}
#endif

	/*OAT_Value process*/
	if(u16OatValue > CCS_Temp_UMAX)
	{
		u8InputError = True;		
	}
	else
	{
		CCS_u16OatValue = u16OatValue;	
	}
	/*Process Oat Hysteresis */
	pu16_1 = &CCS_u16OatNewValue;
	ALG_vHysteresis_16 (pu16_1,CCS_u16OatValue,CCS_u16Group1OatHysteresis);


	/*BlwCcsTarget process*/
	if(u16BlwCcsTarget > CCS_BlwCcsTargetMax)
	{
		u8InputError = True;		
	}
	else
	{
		CCS_u16BlwCcsTarget = u16BlwCcsTarget;	
	}

	/*VelTempOffset process*/
	if (u8VelValid == True)
	{
		if(u16VelTempOffset > CCS_TempDiff_UMAX)
		{
			u8InputError = True;		
		}
		else
		{
			CCS_u16VelBlwoutTempOffset = u16VelTempOffset;	
		}
	}
	else
	{
		CCS_u16VelBlwoutTempOffset = CCS_nDefaultTempOffset;
	}

	for(u8i=0u; u8i<SYC_ZONES; u8i++)
	{
		/*SunTempOffset process*/
		if (u8SunValid == True)
		{
			if(u16SunTempOffset[u8i] > CCS_TempDiff_UMAX)
			{
				u8InputError = True;	
			}
			else
			{
				CCS_u16SunBlwoutTempOffset(u8i) = u16SunTempOffset[u8i];	
			}
		}
		else
		{
			CCS_u16SunBlwoutTempOffset(u8i) = CCS_nDefaultTempOffset;
		}
		/*MmiSetTemp process*/
		if(((u8MmiSetTemp[u8i] > 0)&&(u8MmiSetTemp[u8i] < CCS_nMmiSetTempMin))
		||((u8MmiSetTemp[u8i] > CCS_nMmiSetTempMax)&&(u8MmiSetTemp[u8i] < 255)))
		{
			u8InputError = True;		
		}
		else
		{
			CCS_u8MmiSetTemp[u8i] = u8MmiSetTemp[u8i];
		}
	}

	/*Error code process*/
	if (u8InputError == True)
	{
		BIT_SET(CCS_u16ErrorCode,CCS_nBitInputValueErr);
	}
	else
	{
		BIT_CLEAR(CCS_u16ErrorCode,CCS_nBitInputValueErr);
	}
}

/*****************************************************************************
 Function      : void CCS_vCorrectSetTemp(void)                                       
 Description   : Calculate the correct setting temperature. 
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void CCS_vCorrectSetTemp(void)
{
	uint8 u8i = False;
	uint16 *pu16_1 = NULL;
	uint16 *pu16_2 = NULL;
	uint16 u16OatSetTempCorr = CCS_TempDiff_IMAX;
	uint16 u16SetTemp[SYC_ZONES];
	int16 i16SetTemp  = 0;

	/*Oat->Set Temp correct*/
	pu16_1 = (uint16 *)CCS_au16Group1OatSetTempOffsetX_Tbl;
	pu16_2 = (uint16 *)CCS_au16Group1OatSetTempOffsetY_Tbl;
	u16OatSetTempCorr = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,\
											CCS_u16OatNewValue,CCS_nOatSetTempOffset_Tbl_Len);

#ifdef CCS_UseDefOffset
	/*Defrost mode->Set Temp correct*/
	if(CCS_u8MmiModeStates == CCS_nMmiModeDef)
	{
		pu16_1 = (uint16 *)CCS_au16Group1DefTempOffsetX_Tbl;
		pu16_2 = (uint16 *)CCS_au16Group1DefTempOffsetY_Tbl;
		u16DefOffset = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,\
											CCS_u16OatNewValue,CCS_nDefTempOffsetTbl_Len);
	}
	else
	{
		u16DefOffset = CCS_TempDiff_IMAX;
	}
#endif	
	for(u8i=0; u8i<SYC_ZONES; u8i++)
	{
		if(CCS_u8MmiSetTemp[u8i]==0)
		{
			CCS_u16SetTemp(u8i)=CCS_Temp_UMIN;		/*If Setting Temp is Low, Correct Setting Temp is -40 degree*/
		}
		else if(CCS_u8MmiSetTemp[u8i]==255)
		{	
			CCS_u16SetTemp(u8i)=CCS_Temp_UMAX;		/*If Setting Temp is High, Correct Setting Temp is 120 degree*/
		}
		else
		{
			/*STEP1:change MMI set temp into internal format*/
			u16SetTemp[u8i] = CCS_u16Convert2InternalTempUnit (CCS_u8MmiSetTemp[u8i]);

			/*STEP2:limit ccs_settemp*/
			pu16_1 = (uint16 *)CCS_au16Group1MmiToCcsSetTempX_Tbl;
			pu16_2 = (uint16 *)CCS_au16Group1MmiToCcsSetTempY_Tbl;
			u16SetTemp[u8i] = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,\
											u16SetTemp[u8i],CCS_nMmiToCcsSetTemp_Tbl_Len);
			
			/*STEP3:Calculate the final correct setting temp*/
			i16SetTemp = (int16)u16SetTemp[u8i] + (int16)u16OatSetTempCorr - CCS_TempDiff_IMAX;
			CCS_RangeCheck(i16SetTemp,CCS_Temp_MIN,CCS_Temp_MAX);
			CCS_u16SetTemp(u8i)= (uint16)i16SetTemp;
		}
		CCS_u16OatSetTempOffset(u8i) = u16OatSetTempCorr;
	}
	
	/*Calculate the average correct setting temp*/
	#if (SYC_ZONES >= 2)
	CCS_u16SetTempAvg = (CCS_u16SetTempDr*CCS_nDrvSideFactor\
						+ CCS_u16SetTempPs*(16-CCS_nDrvSideFactor))>>4; 
	#else
		CCS_u16SetTempAvg = CCS_u16SetTempDr; 
	#endif
	CCS_u8SetTempValid = True;
}

/*****************************************************************************
 Function      : void CCS_vCalculateSi(void)                                    
 Description   : Calculate the system index. 
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void CCS_vCalculateSi(void)
{
	uint8 u8i = False;
	int16 i16Tempdiff = 0;

	for(u8i=0; u8i<SYC_ZONES; u8i++)
	{
		#if (CCS_IctSensorNum >1)
		i16Tempdiff = CCS_TempDiff_IMAX + CCS_u16SetTemp(u8i) - CCS_u16IctValue[u8i];/*Calculate the diff between CCS_SetTemp and ICT*/
		#else
		i16Tempdiff = CCS_TempDiff_IMAX + CCS_u16SetTemp(u8i) - CCS_u16IctValue[0];
		#endif
		/*The limit for Tempdiff*/
		CCS_RangeCheck(i16Tempdiff,CCS_TempDiff_UMIN,CCS_TempDiff_UMAX);
		CCS_u16TempDiff(u8i) = (uint16)i16Tempdiff;
	}
	
	/*Calculate the average Temp diff value*/
	#if (SYC_ZONES >= 2)
	CCS_u16TempDiffAvg = (CCS_u16TempDiffDr*CCS_nDrvSideFactor\
						+ CCS_u16TempDiffPs*(16-CCS_nDrvSideFactor))>>4; 
	#else
	CCS_u16TempDiffAvg = CCS_u16TempDiffDr;
	#endif
}


/*****************************************************************************
 Function      : void CCS_vPControlOffset(void)                                   
 Description   : Calculate the P-control blowout temperature offset 
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void CCS_vPControlOffset(void)
{
	uint8 u8i = False;
	uint8 u8Factor = False;
	uint16 *pu16_x = NULL;
	uint16 *pu16_y = NULL;
	uint16 **pu16_z = NULL;
	
	int16 i16PCtrTempOffset = 0;

	for(u8i=0; u8i<SYC_ZONES; u8i++)
	{
		/*STEP1:Calculate the factor in face mode*/
		pu16_x = (uint16 *)CCS_au16Group1BlowTempOatX_Tbl;
		pu16_y = (uint16 *)CCS_au16Group1SiBlowTempGainX_Tbl;
		pu16_z = (uint16 **)CCS_au16SiBlowTempGainZ_Tbl;
		u8Factor = (uint8)CCS_u16ALG3DLookupTable(pu16_x,pu16_y,pu16_z,CCS_u16OatNewValue,\
			CCS_u16TempDiff(u8i),CCS_nBlowTempOatX_Tbl_Len,CCS_nSiBlowTempGain_Tbl_Len);
		
		/*STEP2:Calculate the P-Control offset*/
		i16PCtrTempOffset = CCS_u16TempDiff(u8i) - CCS_TempDiff_IMAX;
		i16PCtrTempOffset = i16PCtrTempOffset*u8Factor + CCS_TempDiff_IMAX;
		//i16PCtrTempOffset = (int16)((u16Factor*CCS_i16TempDiff[u8i])>>4);

		/*STEP3:The limit for P control offset*/
		CCS_RangeCheck(i16PCtrTempOffset, CCS_TempDiff_UMIN, CCS_TempDiff_UMAX);
		CCS_u16SiBlwoutTempOffset(u8i) = (uint16)i16PCtrTempOffset;
	}
}


/*****************************************************************************
 Function      : void CCS_vPreControlOffset(void)                                  
 Description   : Calculate the Pre-control blowout temperature offset
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void CCS_vPreControlOffset(void)
{
	uint8 u8i = False;
	uint16 *pu16_x = NULL;
	uint16 *pu16_y = NULL;
	uint16 **pu16_z = NULL;
	int16 i16Tempdiff = 0;

	for(u8i=0; u8i<SYC_ZONES; u8i++)
	{
		/*STEP1:Calculate the diff of oat and ccs settemp*/
		i16Tempdiff = CCS_TempDiff_IMAX + CCS_u16OatNewValue - CCS_u16SetTemp(u8i);
		CCS_RangeCheck(i16Tempdiff,CCS_TempDiff_UMIN,CCS_TempDiff_UMAX);
		CCS_u16OatSetTempDiff(u8i) = (uint16)i16Tempdiff;

		/*STEP2:Calculate offset*/
		pu16_x = (uint16 *)CCS_au16Group1OatBlowTempSpeedX_Tbl;
		pu16_y = (uint16 *)CCS_au16Group1OatBlowTempOffsetX_Tbl;
		pu16_z = (uint16 **)CCS_au16OatBlowTempOffsetZ_Tbl;
		CCS_u16OatBlwoutTempOffset(u8i) = CCS_u16ALG3DLookupTable(pu16_x,pu16_y,pu16_z,CCS_u16BlwCcsTarget,\
			CCS_u16OatSetTempDiff(u8i),CCS_nOatBlowTempSpeedX_Tbl_Len,CCS_nOatBlowTempOffset_Tbl_Len);
	}
}


/*****************************************************************************
 Function      : CCS_vSplitZoneTemp                                 
 Description   : force output value
 Takes         : Nothing
 Return Value  : void                                                *
*****************************************************************************/
static void CCS_vSplitZoneTemp(void)
{	
#if (SYC_ZONES >= 2)
	uint16 *pu16_x = NULL;
	uint16 *pu16_y = NULL;
	uint16 **pu16_z = NULL;

	uint8 u8Factor=False;
	uint8 u8i = False;
	int16 i16MmiTempDiff = False;
	int16 i16TempOffset=0;
	uint16 u16SetTempDiff = False;
	uint16 u16MmiSetTemp[SYC_ZONES];
	
	/*Mustlimit LO/HI */
	for(u8i=0u; u8i<SYC_ZONES; u8i++)
	{
		u16MmiSetTemp[u8i] = CCS_u8MmiSetTemp[u8i];  
		CCS_RangeCheck(u16MmiSetTemp[u8i], CCS_nMmiSetTempMin, CCS_nMmiSetTempMax);
		u16MmiSetTemp[u8i] = u16MmiSetTemp[u8i]*5; /*change MMI to CCS revolution*/
	}
	
	/*STEP1: cal driver side*/
	i16MmiTempDiff = CCS_TempDiff_IMAX+u16MmiSetTemp[0] - u16MmiSetTemp[1];
	i16MmiTempDiff = (int16)u16MmiSetTemp[0] - (int16)u16MmiSetTemp[1];
	CCS_RangeCheck(i16MmiTempDiff, CCS_TempDiff_UMIN, CCS_TempDiff_UMAX);
	u16SetTempDiff = (uint16)i16MmiTempDiff;
	
	/*STEP2:Calculate offset*/
	pu16_x = (uint16 *)CCS_au16Group1BlowTempOatX_Tbl;
	pu16_y = (uint16 *)CCS_au16Group1DrTsetBlowTempGainX_Tbl;
	pu16_z = (uint16 **)CCS_au16DrTsetBlowTempGainZ_Tbl;
	u8Factor = (uint8)CCS_u16ALG3DLookupTable(pu16_x,pu16_y,pu16_z,CCS_u16OatNewValue,\
		u16SetTempDiff,CCS_nBlowTempOatX_Tbl_Len,CCS_nDrTsetBlowTempGain_Tbl_Len);
	
	i16MmiTempDiff = (int16)u16MmiSetTemp[0] - (int16)u16MmiSetTemp[1];
	i16TempOffset = i16MmiTempDiff*u8Factor + CCS_TempDiff_IMAX;
	
	CCS_RangeCheck(i16TempOffset, CCS_TempDiff_UMIN, CCS_TempDiff_UMAX);
	CCS_u16TsetBlwoutTempOffsetDr = (uint16)i16TempOffset;


	/*STEP3: cal passenger side*/
	pu16_x = (uint16 *)CCS_au16Group1BlowTempOatX_Tbl;
	pu16_y = (uint16 *)CCS_au16Group1PsTsetBlowTempGainX_Tbl;
	pu16_z = (uint16 **)CCS_au16PsTsetBlowTempGainZ_Tbl;
	u8Factor = (uint8)CCS_u16ALG3DLookupTable(pu16_x,pu16_y,pu16_z,CCS_u16OatNewValue,\
		u16SetTempDiff,CCS_nBlowTempOatX_Tbl_Len,CCS_nPsTsetBlowTempGain_Tbl_Len);
	
	i16MmiTempDiff = (int16)u16MmiSetTemp[1] - (int16)u16MmiSetTemp[0];
	i16TempOffset = i16MmiTempDiff*u8Factor + CCS_TempDiff_IMAX;
	
	CCS_RangeCheck(i16TempOffset, CCS_TempDiff_UMIN, CCS_TempDiff_UMAX);
	CCS_u16TsetBlwoutTempOffsetPs = (uint16)i16TempOffset;
	
#else
	CCS_u16TsetBlwoutTempOffsetDr = CCS_nDefaultTempOffset;
	CCS_u16TsetBlwoutTempOffsetPs = CCS_nDefaultTempOffset;
#endif
	
}


/*****************************************************************************
 Function      : void CCS_vCalculateBlowoutTemp(void)                                  
 Description   : Calculate the final blowout temperature. 
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
void CCS_vCalculateBlowoutTemp(void)
{
	uint8 u8i = False;	
	int16 i16BlowoutTemp = 0;
	uint32 *pu32_1 = NULL;

	if(CCS_u8FilterInit == False)
	{
		/*Within 3s after IG Off to On, the BlowoutTemp needn't filter*/
		if(CCS_u8TimeCounter<30)
		{
			CCS_u8TimeCounter ++;
		}
		else
		{
			CCS_u8FilterInit = True;
		}
	}

	for(u8i=0; u8i<SYC_ZONES; u8i++)
	{
		if (CCS_u8MmiSetTemp[u8i] == 0)
		{
			CCS_u16UnDampedBlwoutTemp(u8i) = CCS_Temp_MIN;
		}
		else if (CCS_u8MmiSetTemp[u8i] == 0xFF)
		{
			CCS_u16UnDampedBlwoutTemp(u8i) = CCS_Temp_MAX;
		}
		else
		{
			i16BlowoutTemp = False;
			
			/* STEP 1 --Aquire CCS_SetTemp */
			i16BlowoutTemp += (int16)CCS_u16SetTemp(u8i) ;

			/* STEP 2 --Aquire OAT-Tset Diff offset */
			i16BlowoutTemp += (int16)CCS_u16OatBlwoutTempOffset(u8i) - CCS_TempDiff_IMAX;

			/* STEP 3 --Aquire SI(P) offset */
			i16BlowoutTemp += (int16)CCS_u16SiBlwoutTempOffset(u8i) - CCS_TempDiff_IMAX;

			/* STEP 4 --Aquire Solar offset. */
			i16BlowoutTemp += (int16)CCS_u16SunBlwoutTempOffset(u8i) - CCS_TempDiff_IMAX;

			/* STEP 5 --Aquire velocity offset. */
			i16BlowoutTemp += (int16)CCS_u16VelBlwoutTempOffset - CCS_TempDiff_IMAX;

			/* STEP 6 --Aquire Mmi setTemp diff offset. */
			i16BlowoutTemp += (int16)CCS_u16TsetBlwoutTempOffset(u8i) - CCS_TempDiff_IMAX;

			/* STEP 7 --The limit for Blowout Temp*/
			CCS_RangeCheck(i16BlowoutTemp,CCS_Temp_UMIN,CCS_Temp_UMAX);

			/*The limit for Blowout Temp*/
			CCS_u16UnDampedBlwoutTemp(u8i) = i16BlowoutTemp;
		}

		/*Blowout Temperature Filter process*/
		if((CCS_u8FilterInit == False)||(CCS_u8MmiSetTemp[u8i]!=CCS_u8MmiSetTempPre[u8i]))
		{/*update the blowoutTemp value directly*/

			CCS_u16BlwoutTemp(u8i) = CCS_u16UnDampedBlwoutTemp(u8i);
			CCS_u32BlwoutTempPre[u8i] = (uint32)CCS_u16UnDampedBlwoutTemp(u8i)<<16;
		}	
		else
		{
			pu32_1 = &CCS_u32BlwoutTempPre[u8i];
			CCS_u16BlwoutTemp(u8i) = ALG_u16FirstOrderFilter (pu32_1,CCS_u16UnDampedBlwoutTemp(u8i),\
																		    CCS_nu8BlowoutTempFilterK);
		}

		CCS_u8MmiSetTempPre[u8i] = CCS_u8MmiSetTemp[u8i];	/*Save the last Setting Temp*/

	}

	/*Calculate the average blowout temp*/
	#if (SYC_ZONES >= 2)
	CCS_u16BlwoutTempAvg = (CCS_u16BlwoutTempDr*CCS_nDrvSideFactor\
					 + CCS_u16BlwoutTempPs*(16-CCS_nDrvSideFactor))>>4; 
	#else
	CCS_u16BlwoutTempAvg = CCS_u16BlwoutTempDr;
	#endif
}


/* ===========================================================================
* Function   : uint16 ALG_u163DLookupTable\
(uint16 pu16_X[], uint16 pu16_Y[], uint16 *pu16_Z1[], uint16 InputX, uint16 InputY, const uint8 X_Len, const uint8 Y_Len)
* Description: This function impliments an 16-bit curve lookup for 3D.
 Takes       : Nothing
* Returns    : Z axis output value;
*/
uint16 CCS_u16ALG3DLookupTable\
(uint16 pu16_X[], uint16 pu16_Y[], uint16 *pu16_Z[], uint16 InputX, uint16 InputY, const uint8 X_Len, const uint8 Y_Len)
{
	uint8 u8i = False;
	uint16 *pu16_1 = NULL;
	uint16 *pu16_2 = NULL;
	uint16 u16Result = False;
	uint16 au16Offsets[2]={0,0};

	if(InputX<=pu16_X[0])
	{/*before the first point*/
		
		pu16_1 = (uint16 *)pu16_Y;
		pu16_2 = (uint16 *)pu16_Z[0];
		u16Result = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,InputY,Y_Len);
	}
	else if(InputX>=pu16_X[X_Len-1])
	{/*pass the last point*/
		
		pu16_1 = (uint16 *)pu16_Y;
		pu16_2 = (uint16 *)pu16_Z[X_Len-1];
		u16Result = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,InputY,Y_Len);
	}
	else
	{/*the normal range*/
		
		for(u8i=1;u8i<X_Len;u8i++)
		{
			if(InputX<=pu16_X[u8i])
			{
				pu16_1 = (uint16 *)pu16_Y;
				pu16_2 = (uint16 *)pu16_Z[u8i-1];
				au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,InputY,Y_Len);

				pu16_2 = (uint16 *)pu16_Z[u8i];
				au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,InputY,Y_Len);

				pu16_1 = (uint16 *)&pu16_X[u8i-1];
				pu16_2 = au16Offsets;
				u16Result = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,InputX,2);
				
				break;
			}
		}
	}

	return u16Result;
}

/*****************************************************************************
 Function      : CCS_u16Convert2InternalTempUnit                                 
 Description   : force output value
 Takes         : Nothing
 Return Value  : uint16                                                *
*****************************************************************************/
static uint16 CCS_u16Convert2InternalTempUnit (uint8 u8InputTemp)
{
	/* convert input temperature (from MMI) into the internally used  *
	* unit (Celsius) and resolution (0.1 degrees). Input can be      *
	* Celsius or Fahrenheit. Both are in 1 degrees resolution.       *
	* casting to int16 is not critical due to the range of values    */
	uint16 u16Temp=False;

	u16Temp = (uint16)u8InputTemp*5 + 400;

	if (u16Temp > CCS_Temp_MAX)
	{
		u16Temp = CCS_Temp_MAX;
	}

	return u16Temp;
}

#ifdef CCS_UseCtsInput
/*****************************************************************************
 Function      : void CCS_vCalculateBlowoutTemp(void)                                  
 Description   : Calculate the final blowout temperature. 
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void CCS_vUseCtsBlowoutTemp(void)
{
	uint8 u8i = False;	
	uint16 u16CtsBlwoutTemp[SYC_ZONES];

	//u16CtsBlwoutTemp[0] = CCS_u16GetCts_BlowoutTempDr*5; /*change to 0.1 per,160930*/
	CCS_u8BlowoutTempValid[0] = CTS_enGetTgtBlowTempLExport(&u16CtsBlwoutTemp[0]);
	
#if(SYC_ZONES >= 2)
	//u16CtsBlwoutTemp[1] = CCS_u16GetCts_BlowoutTempPs*5;
	CCS_u8BlowoutTempValid[1] = CTS_enGetTgtBlowTempRExport(&u16CtsBlwoutTemp[1]);
#endif

	for(u8i=0; u8i<SYC_ZONES; u8i++)
	{
		CCS_u16UnDampedBlwoutTemp(u8i) = u16CtsBlwoutTemp[u8i];

		CCS_u16BlwoutTemp(u8i) = CCS_u16UnDampedBlwoutTemp(u8i);

	}

	/*Calculate the average blowout temp*/
	#if (SYC_ZONES >= 2)
	CCS_u16BlwoutTempAvg = (CCS_u16BlwoutTempDr*CCS_nDrvSideFactor\
					 + CCS_u16BlwoutTempPs*(16-CCS_nDrvSideFactor))>>4; 
	#else
	CCS_u16BlwoutTempAvg = CCS_u16BlwoutTempDr;
	#endif
}
#endif

/*****************************************************************************
 Function      : CCS_vCcpBlowerTempOutputForce                                 
 Description   : force output value
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void CCS_vCcpBlowerTempOutputForce(void)
{
	if(CCS_GetCcpForceBit(CCS_nSetCcsBlwoutTempDr))
	{
		CCS_u16BlwoutTempDr=CCS_u16CcpControlData[CCS_nSetCcsBlwoutTempDr];
        CCS_u16BlwoutTempPs=CCS_u16CcpControlData[CCS_nSetCcsBlwoutTempDr];
	}
	else
	{
	}

	//if(CCS_GetCcpForceBit(CCS_nSetCcsBlwoutTempPs))
	//{
		//CCS_u16BlwoutTempPs=CCS_u16CcpControlData[CCS_nSetCcsBlwoutTempPs];
	//}
	//else
	//{
	//}

	/*Calculate the average blowout temp*/
	#if (SYC_ZONES >= 2)
	CCS_u16BlwoutTempAvg = (CCS_u16BlwoutTempDr*CCS_nDrvSideFactor\
					 + CCS_u16BlwoutTempPs*(16-CCS_nDrvSideFactor))>>4; 
	#else
	CCS_u16BlwoutTempAvg = CCS_u16BlwoutTempDr;
	#endif
}

/*****************************************************************************
 Function      : CCS_vCcpSetTempOutputForce                                 
 Description   : force output value
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void CCS_vCcpSetTempOutputForce(void)
{
    if(CCS_GetCcpForceBit(CCS_nSetCcsSetTempDr))
	{
		CCS_u16SetTempDr=CCS_u16CcpControlData[CCS_nSetCcsSetTempDr];
        
    	#if (SYC_ZONES >= 2)
    	CCS_u16SetTempAvg = (CCS_u16SetTempDr*CCS_nDrvSideFactor\
    						+ CCS_u16SetTempPs*(16-CCS_nDrvSideFactor))>>4; 
    	#else
    		CCS_u16SetTempAvg = CCS_u16SetTempDr; 
    	#endif
	}
	else
	{
	}
}
//#ifndef CCS_UseRTE
/*****************************************************************************
Function      : CCS_u8GetValue                                              *
Description   : The extern model get the uint8 type variable value from this*
			 model                                                       *
Return Value  : uint8 value                                                 *
*****************************************************************************/
uint8 CCS_u8GetValue( CCS_tenu8VarNumber enIndex )
{
   	if ( enIndex < CCS_nu8Max )
	{
		return CCS_au8Array[enIndex];
	}
	else
	{
		return CCS_au8Array[CCS_nu8Max-1];
	}

}


/*****************************************************************************
 Function      : CCS_u16GetValue                                              *
 Description   : The extern model get the uint8 type variable value from this*
				 model                                                       *
 Return Value  : uint16 value                                                 *
*****************************************************************************/
uint16 CCS_u16GetValue( CCS_tenu16VarNumber enIndex )
{
   	if ( enIndex < CCS_nu16Max )
	{
		return CCS_au16Array[enIndex];
	}
	else
	{
		return CCS_au16Array[CCS_nu16Max-1];
	}
}


/*****************************************************************************
 Function      : CCS_u8ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType CCS_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
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
				CCS_ClrCcpForceByte();
				break;
			case 1:
				CCS_SetCcpForceBit(CCS_nSetCcsBlwoutTempDr);
				CCS_u16CcpControlData[CCS_nSetCcsBlwoutTempDr]=CcpControlWord.CcpContronData;
				break;
			case 2:
				CCS_ClrCcpForceBit(CCS_nSetCcsBlwoutTempDr);
				CCS_u16CcpControlData[CCS_nSetCcsBlwoutTempDr]=0;
				break;
			case 3:
				CCS_SetCcpForceBit(CCS_nSetCcsBlwoutTempPs);
				CCS_u16CcpControlData[CCS_nSetCcsBlwoutTempPs]=CcpControlWord.CcpContronData;
				break;
			case 4:
				CCS_ClrCcpForceBit(CCS_nSetCcsBlwoutTempPs);
				CCS_u16CcpControlData[CCS_nSetCcsBlwoutTempPs]=0;
				break;
			case 5:
				CCS_SetCcpForceBit(CCS_nSetCcsSetTempDr);
				CCS_u16CcpControlData[CCS_nSetCcsSetTempDr]=CcpControlWord.CcpContronData;
				break;
			case 6:
				CCS_ClrCcpForceBit(CCS_nSetCcsSetTempDr);
				CCS_u16CcpControlData[CCS_nSetCcsSetTempDr]=0;
				break;
			default:
				u8Result = RTE_E_INVALID;
				break;
		}
	}
	else
	{
		CCS_ClrCcpForceByte();
	}
        return u8Result;
}

#ifdef CCS_UseRTE
/*****************************************************************************
 Function      : CCS_vOutputValue                                    
 Description   : Output the value to RTE 
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void CCS_vOutputValue(void)
{
	Rte_IWrite_Ccs_vMain_CcsValid_u8Flag(CCS_u8Valid);
	Rte_IWrite_Ccs_vReset_CcsSwVersion_u8Version(CCS_u8SwVersion);
		
	Rte_IWrite_Ccs_vMain_CcsErrorCode_u16BitMap(CCS_u16ErrorCode);
	
	Rte_IWrite_Ccs_vMain_CcsSetTempAvg_u16Temp(CCS_u16SetTempAvg);
	Rte_IWrite_Ccs_vMain_CcsSetTempDr_u16Temp(CCS_u16SetTempDr);
	Rte_IWrite_Ccs_vMain_CcsSetTempPs_u16Temp(CCS_u16SetTempPs);

	Rte_IWrite_Ccs_vMain_CcsTempDiffAvg_u16TempDiff(CCS_u16TempDiffAvg);
	Rte_IWrite_Ccs_vMain_CcsTempDiffDr_u16TempDiff(CCS_u16TempDiffDr);
	Rte_IWrite_Ccs_vMain_CcsTempDiffPs_u16TempDiff(CCS_u16TempDiffPs);
	
	Rte_IWrite_Ccs_vMain_CcsOatSetTempOffsetDr_u16TempOffset(CCS_u16OatSetTempOffsetDr);
	Rte_IWrite_Ccs_vMain_CcsOatSetTempOffsetPs_u16TempOffset(CCS_u16OatSetTempOffsetPs);

	Rte_IWrite_Ccs_vMain_CcsOatBlwoutTempOffsetDr_u16TempOffset(CCS_u16OatBlwoutTempOffsetDr);
	Rte_IWrite_Ccs_vMain_CcsOatBlwoutTempOffsetPs_u16TempOffset(CCS_u16OatBlwoutTempOffsetPs);

	Rte_IWrite_Ccs_vMain_CcsSiBlwoutTempOffsetDr_u16TempOffset(CCS_u16SiBlwoutTempOffsetDr);
	Rte_IWrite_Ccs_vMain_CcsSiBlwoutTempOffsetPs_u16TempOffset(CCS_u16SiBlwoutTempOffsetPs);

	Rte_IWrite_Ccs_vMain_CcsTsetBlwoutTempOffsetDr_u16TempOffset(CCS_u16TsetBlwoutTempOffsetDr);
	Rte_IWrite_Ccs_vMain_CcsTsetBlwoutTempOffsetPs_u16TempOffset(CCS_u16TsetBlwoutTempOffsetPs);

	Rte_IWrite_Ccs_vMain_CcsSunBlwoutTempOffsetDr_u16TempOffset(CCS_u16SunBlwoutTempOffsetDr);
	Rte_IWrite_Ccs_vMain_CcsSunBlwoutTempOffsetPs_u16TempOffset(CCS_u16SunBlwoutTempOffsetPs);
	
	Rte_IWrite_Ccs_vMain_CcsVelBlwoutTempOffset_u16TempOffset(CCS_u16VelBlwoutTempOffset);

	Rte_IWrite_Ccs_vMain_CcsBlowoutTempAvg_u16Temp(CCS_u16BlwoutTempAvg);	
	Rte_IWrite_Ccs_vMain_CcsBlowoutTempDr_u16Temp(CCS_u16BlwoutTempDr);
	Rte_IWrite_Ccs_vMain_CcsBlowoutTempPs_u16Temp(CCS_u16BlwoutTempPs);
	
}

#endif


/*****************************************************************************
* EOF:
******************************************************************************/

