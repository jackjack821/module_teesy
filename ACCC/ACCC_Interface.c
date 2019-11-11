/*******************************************************************************
| Module Name: Air Condition Compressor Control
| File Name: ACCC_Interface.c
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
| Li Jiaye                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2016.4.19     A0      Wu Jiaming         For base code creating
| 
| 
********************************************************************************/


/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define ACCC_Interface                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
#include "POW.h"
#include "Bctl.h"
#include "Mmi.h"
//#include "Ict.h"
#include "Evap.h"
#include "Oat.h"
#include "Ccs.h"
#include "BctlDrv.h"
/* Own headerfiles */
#include "ACCC_Type.h"
#include "ACCC_interface.h"
#include "ACCC_Cfg.h"
#include "ACCC_Private.h"

static uint16 Accc_CcpForceFlag=0u;
static uint16 Accc_CcpControlData[Acc_nCcpForceMax];

/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/

#ifdef ACCC_WithoutRTE

#endif


Std_ReturnType ACCC_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord)
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
				AccClrCcpForceByte();
				break;
			case 1:
				AccSetCcpForceBit(Acc_nSetAcReq);
				Accc_CcpControlData[Acc_nSetAcReq]=CcpControlWord.CcpContronData;
				break;
			case 2:
				AccClrCcpForceBit(Acc_nSetAcReq);
				Accc_CcpControlData[Acc_nSetAcReq]=0;
				break;
			case 3:
				AccSetCcpForceBit(Acc_nSetAcTargetSpeed);
				Accc_CcpControlData[Acc_nSetAcTargetSpeed]=CcpControlWord.CcpContronData;
				break;
			case 4:
				AccClrCcpForceBit(Acc_nSetAcTargetSpeed);
				Accc_CcpControlData[Acc_nSetAcTargetSpeed]=0;
				break;
			case 5:
				AccSetCcpForceBit(Acc_nSetAcTargetEvap);
				Accc_CcpControlData[Acc_nSetAcTargetEvap]=CcpControlWord.CcpContronData;
				break;
			case 6:
				AccClrCcpForceBit(Acc_nSetAcTargetEvap);
				Accc_CcpControlData[Acc_nSetAcTargetEvap]=0;
				break;
			case 7:
				AccSetCcpForceBit(Acc_nSetAcHighFanSpd);
				Accc_CcpControlData[Acc_nSetAcHighFanSpd]=CcpControlWord.CcpContronData;
				break;
			case 8:
				AccClrCcpForceBit(Acc_nSetAcHighFanSpd);
				Accc_CcpControlData[Acc_nSetAcHighFanSpd]=0;
				break;
			case 9:
				AccSetCcpForceBit(Acc_nSetAcHiLoPress);
				Accc_CcpControlData[Acc_nSetAcHiLoPress]=CcpControlWord.CcpContronData*1000;
				break;
			case 10:
				AccClrCcpForceBit(Acc_nSetAcHiLoPress);
				Accc_CcpControlData[Acc_nSetAcHiLoPress]=0;
				break;
			case 11:
				AccSetCcpForceBit(Acc_nSetAcMidPress);
				Accc_CcpControlData[Acc_nSetAcMidPress]=CcpControlWord.CcpContronData*1000;
				break;
			case 12:
				AccClrCcpForceBit(Acc_nSetAcMidPress);
				Accc_CcpControlData[Acc_nSetAcMidPress]=0;
				break;
			case 13:
				AccSetCcpForceBit(Acc_nSetKp);
				Accc_CcpControlData[Acc_nSetKp]=CcpControlWord.CcpContronData;
				break;
			case 14:
				AccClrCcpForceBit(Acc_nSetKp);
				Accc_CcpControlData[Acc_nSetKp]=0;
				break;
			case 15:
				AccSetCcpForceBit(Acc_nSetKi);
				Accc_CcpControlData[Acc_nSetKi]=CcpControlWord.CcpContronData;
				break;
			case 16:
				AccClrCcpForceBit(Acc_nSetKi);
				Accc_CcpControlData[Acc_nSetKi]=0;
				break;
			case 0x81:
				AccSetCcpForceBit(Acc_nSetAcReq);
				Accc_CcpControlData[Acc_nSetAcReq]=CcpControlWord.CcpContronData;
				break;
			case 0xA1:
				AccSetCcpForceBit(Acc_nSetAcReq);
				Accc_CcpControlData[Acc_nSetAcReq]=CcpControlWord.CcpContronData;
				AccSetCcpForceBit(Acc_nSetAcTargetSpeed);
				Accc_CcpControlData[Acc_nSetAcTargetSpeed]=Accc_CcpControlData[Acc_nSetAcReq]*2000/*default compressor */;
				break;
			case 0xA2:
				AccClrCcpForceBit(Acc_nSetAcReq);
				Accc_CcpControlData[Acc_nSetAcReq]=0;
				AccClrCcpForceBit(Acc_nSetAcTargetSpeed);
				Accc_CcpControlData[Acc_nSetAcTargetSpeed]=0;
				break;
			case 0xA3:
				AccSetCcpForceBit(Acc_nSetAcTargetSpeed);
				Accc_CcpControlData[Acc_nSetAcTargetSpeed]=CcpControlWord.CcpContronData;
				AccSetCcpForceBit(Acc_nSetAcReq);
				Accc_CcpControlData[Acc_nSetAcReq]=Accc_CcpControlData[Acc_nSetAcTargetSpeed]>0?1:0;
                break;
			case 0xA4:
				AccClrCcpForceBit(Acc_nSetAcReq);
				Accc_CcpControlData[Acc_nSetAcReq]=0;
				AccClrCcpForceBit(Acc_nSetAcTargetSpeed);
				Accc_CcpControlData[Acc_nSetAcTargetSpeed]=0;
				break;
			default:
                return RTE_E_INVALID;
				break;
		}
	}
	else
	{
		AccClrCcpForceByte();
	}
    return RTE_E_OK;
}

uint16 ACCC_u16GetCcpCtrlValue(uint8 enIndex)
{
	if ( enIndex < Acc_nCcpForceMax )
	{
		return Accc_CcpControlData[enIndex];
	}
	else
	{
		return Accc_CcpControlData[Acc_nCcpForceMax-1];
	}
}

uint16 ACCC_u16GetCcpCtrlFlag(uint8 enIndex)
{
	if ( enIndex < Acc_nCcpForceMax )
	{
		return AccGetCcpForceBit(enIndex);
	}
	else
	{
		return 0u;
	}
}
/*****************************************************************************
 Function      : ACCC_vCcpInputForce                                 
 Description   : force Input value
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
void ACCC_vCcpInputForce(void)
{	
	
}
/*****************************************************************************
 Function      : ACCC_vCcpOutputForce                                 
 Description   : force Output value
 Takes         : NothOutg
 Return Value  : None                                                *
*****************************************************************************/
void ACCC_vCcpOutputForce(void)
{	

}


void ACCC_vPutRteValueInit(void)
{

}

void ACCC_vPutRteValueDeInit(void)
{

}
/*============================================================================
*Function : void ACCC_vPutRteValue(void)
*Description : 
*takes : nothing
*return: nothing
*/
void ACCC_vPutRteValue(void)
{
	ACCC_vCcpOutputForce();
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enAdValidFlagImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enAdValidFlagImport(uint8 *value)
{
    *value=ACCC_u8GetPowAdValid;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enLowVoltageFlagImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enLowVoltageFlagImport(uint8 *value)
{
    *value=ACCC_u8GetPowBattLowVoltage;
    return ACCC_nValid;
}
/*============================================================================
*Function : ACCC_tenValueSts ACCC_enHighVoltageFlagImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enHighVoltageFlagImport(uint8 *value)
{
    *value=ACCC_u8GetPowBattHighVoltage;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enMmiAcCtrlImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enMmiAcCtrlImport(uint8 *value)
{
    *value=ACCC_u8GetMmiAcCtrl;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enMmiAcCtrlImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enMmiAcModeImport(uint8 *value)
{
    *value=ACCC_u8GetMmiAcMode;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enMmiSetTempLeftImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enMmiSetTempLeftImport(uint8 *value)
{
    *value=ACCC_u8GetMmiSetTempLeft;
    return ACCC_nValid;
}

#if(SYC_ZONES == 2)
/*============================================================================
*Function : ACCC_tenValueSts ACCC_enMmiSetTempRightImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enMmiSetTempRightImport(uint8 *value)
{
    *value=ACCC_u8GetMmiSetTempRight;
    return ACCC_nValid;
}
#endif

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enMmiBctlCtrlImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enMmiBctlCtrlImport(uint8 *value)
{
    *value=ACCC_u8GetMmiBctlCtrl;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enCcsBlowoutDrImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enCcsBlowoutDrImport(uint16 *value)
{
    *value=ACCC_u16GetCcsBlowoutDr;
    return ACCC_nValid;
}

#if(SYC_ZONES == 2)
/*============================================================================
*Function : ACCC_tenValueSts ACCC_enCcsBlowoutPsImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enCcsBlowoutPsImport(uint16 *value)
{
    *value=ACCC_u16GetCcsBlowoutPs;
    return ACCC_nValid;
}
#endif

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enEvapAcValueImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enEvapAcValueImport(uint16 *value)
{
    *value=ACCC_u16GetEvapAcValue;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enOatValueImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enOatValueImport(uint16 *value)
{
    *value=ACCC_u16GetOatValue;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enIctValueImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enIctValueImport(uint16 *value)
{
    *value=ACCC_u16GetIctValue;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enBattCoolantInTempImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enBattCoolantInTempImport(uint16 *value)
{
    *value=ACCC_u16GetBattCoolantInTemp;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enBattCoolantInTargetTempImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enBattCoolantInTargetTempImport(uint16 *value)
{
    *value=ACCC_u16GetBattCoolantInTargetTemp;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enBattCoolingModeImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enBattCoolingModeImport(uint16 *value)
{
    *value=ACCC_u16GetBattCoolingMode;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enBattThermalMagReqImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enBattThermalMagReqImport(uint16 *value)
{
    *value=ACCC_u16GetBattThermalMagReq;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enBattThreeWayValveRatioImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enBattThreeWayValveRatioImport(uint16 *value)
{
    *value=ACCC_u16GetBattThreeWayValveRatio;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enEcPowerLimitImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enEcPowerLimitImport(uint16 *value)
{
    *value=ACCC_u16GetEcPowerLimitValue;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enEcActualSpdImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enEcActualSpdImport(uint16 *value)
{
    *value=ACCC_u16GetEcActualSpd;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enRfaDispImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enRfaDispImport(uint8 *value)
{
    *value=ACCC_u8GetRfaDisp;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enBlowerTargetImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enBlowerTargetImport(uint16 *value)
{
    *value=ACCC_u16GetBlowerTarget;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enBlowerErrorImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enBlowerErrorImport(uint16 *value)
{
    *value=ACCC_u16GetBlowerError;
    return ACCC_nValid;
}
/*============================================================================
*Function : ACCC_tenValueSts ACCC_enEngineSpeedImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enEngineSpeedImport(uint16 *value)
{
    *value=ACCC_u16GetEngineSpeed;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enVehicleSpeedImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enVehicleSpeedImport(uint16 *value)
{
    *value=ACCC_u16GetVehicleSpeed;
    return ACCC_nValid;
}

#if(ACCC_nWITH_PRESSURE_SENSOR == True)
/*============================================================================
*Function : ACCC_tenValueSts ACCC_enPressureValueImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enPressureValueImport(uint16 *value)
{
    *value=ACCC_u16GetPressureValue;
    return ACCC_nValid;
}

#endif
#if (ACCC_nWITH_PRESSURE_SWITCH == True)
/*============================================================================
*Function : ACCC_tenValueSts ACCC_enPressureHiLoSwitchValueImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enPressureHiLoSwitchValueImport(uint16 *value)
{
    *value=ACCC_u16GetPressureHiLoSwitchValue;
    return ACCC_nValid;
}
#endif

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enVdcActualCurrImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enVdcActualCurrImport(uint16 *value)
{
    *value=ACCC_u16GetVdcActualCurr;
    return ACCC_nValid;
}

/*============================================================================
*Function : ACCC_tenValueSts ACCC_enCcsTempDiffDrImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ACCC_tenValueSts ACCC_enCcsTempDiffDrImport(uint16 *value)
{
    *value=ACCC_u16GetCcsTempDiffDr;
    return ACCC_nValid;
}

/*****************************************************************************
* EOF: ACCC_Interface.c
*****************************************************************************/
