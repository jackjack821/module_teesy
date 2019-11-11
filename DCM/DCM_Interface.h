/*******************************************************************************
| Module Name: directed current motor
| File Name: DCM_Interface.h
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
| 2014.7.17         A0      Li jiaye         module template update. 
| 2014.8.21         A1      Li jiaye         module code updated after coding reviewed.
| 2015.3.29	        A2      Li Jiaye	     add DCM property config
| 2016.2.17         A3      Li Jiaye         module upgraded
| 2016.4.19         A4      Li Jiaye         For base code creating
| 
| 
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef DCM_Interface_H
#define DCM_Interface_H

#include "DCM_Private.h"
#define DCM_sbiLowVoltage  0u
#define DCM_sbiHighVoltage  0u

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
#ifdef DCM_WithoutRTE
uint8 DCM_u16MixMotorDrFB_Read(uint16 * value);
uint8 DCM_u16AirdMotorFB_Read(uint16 * value);
uint8 DCM_u16RfaMotorFB_Read(uint16 * value);
#endif

void DCM_vPutRteValue(void);
#ifdef PINDRIVER
void DCM_vActuatorOperation(void);
DCM_tenValueSts DCM_enSetMotor0PINExport(DCM_tstState *value);
#endif

/*Called function*/
void DCM_vClrForceByteFlag(void);
uint16 Mac_u16GetTargetPosDr(void);

uint16 Aird_u16GetTargetPos(void);

uint16 Rfa_u16GetTargetPos(void);

uint16 Mac_u16GetTargetPosPs(void);



/*input interface*/
DCM_tenValueSts DCM_enLowVoltageFlagImport(uint8 *value);
DCM_tenValueSts DCM_enHighVoltageFlagImport(uint8 *value);
DCM_tenValueSts DCM_enAdValidFlagImport(uint8 *value);
DCM_tenValueSts DCM_enTargetPositionImport(uint8 index,uint16 *value);
DCM_tenValueSts DCM_enCurrentPositionImport(uint8 index,uint16 *value);

/*output interface*/
DCM_tenValueSts DCM_enGetU16TargetPositionExport(uint8 index,uint16 *value);
DCM_tenValueSts DCM_enGetU16CurrentPositionExport(uint8 index,uint16 *value);
DCM_tenValueSts DCM_enGetU16CurrentRawPositionExport(uint8 index,uint16 *value);
DCM_tenValueSts DCM_enGetEnMotorDiretionExport(uint8 index,DCM_tenPortState *value);
DCM_tenValueSts DCM_enGetU8ErrorCodeExport(uint8 index,uint8 *value);
DCM_tenValueSts DCM_enGetStMotorStatusExport(uint8 index,DCM_tstState *value);
DCM_tenValueSts DCM_enGetStMotorBlockStatusExport(uint8 index,DCM_tstBlockErrStatus *value);

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: DCM_Cfg.h
******************************************************************************/

