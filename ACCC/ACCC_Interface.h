/*******************************************************************************
| Module Name: Air Condition Compressor Control
| File Name: ACCC_Interface.h
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
******************************************************************************/
#ifndef ACCC_Interface_H
#define ACCC_Interface_H

#include "ACCC_Private.h"
#include "Rte_Internal.h"

/*****************************************************************************
* MACROS
*
* Functional macros defined.
******************************************************************************/


/*****************************************************************************
* MACROS
*
* In this section declare
* - all macros used in the configuration file and C file.
******************************************************************************/



/*****************************************************************************
* MODULE CONFIGURATION DEFINITIONS
*
* In this section declare
* - all module configuration defines which should be generated.
******************************************************************************/

/*****************************************************************************
* MODULE CONFIGURATION DECLARATIONS
*
* In this section declare
* - module variable declarations for the variable in the cfg.c file, which will be used in module
     functions.
******************************************************************************/
#ifdef ACCC_WithoutRTE
uint8 ACCC_u16MixMotorDrFB_Read(uint16 * value);
uint8 ACCC_u16AirdMotorFB_Read(uint16 * value);
uint8 ACCC_u16RfaMotorFB_Read(uint16 * value);
#endif

void ACCC_vPutRteValue(void);
void ACCC_vPutRteValueInit(void);
void ACCC_vPutRteValueDeInit(void);
#ifdef PINDRIVER
void ACCC_vActuatorOperation(void);
ACCC_tenValueSts ACCC_enSetMotor0PINExport(ACCC_tstState *value);
#endif

/*Called function*/
void ACCC_vClrForceByteFlag(void);
void ACCC_vCcpInputForce(void);
void ACCC_vCcpOutputForce(void);
Std_ReturnType ACCC_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord);


/*input interface*/
ACCC_tenValueSts ACCC_enLowVoltageFlagImport(uint8 *value);
ACCC_tenValueSts ACCC_enHighVoltageFlagImport(uint8 *value);
ACCC_tenValueSts ACCC_enAdValidFlagImport(uint8 *value);
ACCC_tenValueSts ACCC_enMmiAcCtrlImport(uint8 *value);
ACCC_tenValueSts ACCC_enMmiAcModeImport(uint8 *value);
ACCC_tenValueSts ACCC_enMmiSetTempLeftImport(uint8 *value);
#if(SYC_ZONES == 2)
ACCC_tenValueSts ACCC_enMmiSetTempRightImport(uint8 *value);
#endif
ACCC_tenValueSts ACCC_enMmiBctlCtrlImport(uint8 *value);
ACCC_tenValueSts ACCC_enCcsBlowoutDrImport(uint16 *value);
#if(SYC_ZONES == 2)
ACCC_tenValueSts ACCC_enCcsBlowoutPsImport(uint16 *value);
#endif
ACCC_tenValueSts ACCC_enEvapAcValueImport(uint16 *value);
ACCC_tenValueSts ACCC_enOatValueImport(uint16 *value);
ACCC_tenValueSts ACCC_enBattCoolantInTempImport(uint16 *value);
ACCC_tenValueSts ACCC_enBattCoolantInTargetTempImport(uint16 *value);
ACCC_tenValueSts ACCC_enBattCoolingModeImport(uint16 *value);
ACCC_tenValueSts ACCC_enBattThermalMagReqImport(uint16 *value);
ACCC_tenValueSts ACCC_enBattThreeWayValveRatioImport(uint16 *value);
ACCC_tenValueSts ACCC_enEcPowerLimitImport(uint16 *value);
ACCC_tenValueSts ACCC_enEcActualSpdImport(uint16 *value);
ACCC_tenValueSts ACCC_enRfaDispImport(uint8 *value);
ACCC_tenValueSts ACCC_enBlowerTargetImport(uint16 *value);
ACCC_tenValueSts ACCC_enBlowerErrorImport(uint16 *value);
ACCC_tenValueSts ACCC_enPressureValueImport(uint16 *value);
ACCC_tenValueSts ACCC_enVdcActualCurrImport(uint16 *value);
ACCC_tenValueSts ACCC_enEngineSpeedImport(uint16 *value);
ACCC_tenValueSts ACCC_enVehicleSpeedImport(uint16 *value);
ACCC_tenValueSts ACCC_enCcsTempDiffDrImport(uint16 *value);
ACCC_tenValueSts ACCC_enIctValueImport(uint16 *value);

uint16 ACCC_u16GetCcpCtrlValue(uint8 enIndex);
uint16 ACCC_u16GetCcpCtrlFlag(uint8 enIndex);
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: ACCC_Interface.h
******************************************************************************/

