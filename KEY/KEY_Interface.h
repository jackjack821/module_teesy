/*******************************************************************************
| Module Name: KEY capture and debouncing interface
| File Name: KEY_interface.h
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
| 2016.8.3         0100      Li jiaye         module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef KEY_Interface_H
#define KEY_Interface_H



#include "KEY_Private.h"
#include "KEY_type.h"

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
void KEY_vClrForceFlagByteAction(void);
KEY_tenValueSts KEY_vForceKeyPressImport(uint8 IndexInput, uint8 *Output);
KEY_tenValueSts KEY_vPtsKeyPressImport(uint8 IndexInput, KEY_tenKeyAction 	enKeyCurrStatus);
void KEY_vMainExportAction(void);
KEY_tenValueSts KEY_enGetMainOutputExport(KEY_tstMainOut *value);
Std_ReturnType KEY_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);

KEY_tenValueSts KEY_vKey1Import(uint16 *value);
KEY_tenValueSts KEY_vKey2Import(uint16 *value);
KEY_tenValueSts KEY_vKey3Import(uint16 *value);
KEY_tenValueSts KEY_vKey4Import(uint16 *value);
KEY_tenValueSts KEY_vKey5Import(uint16 *value);
KEY_tenValueSts KEY_vKey6Import(uint16 *value);
KEY_tenValueSts KEY_vKey7Import(uint16 *value);
KEY_tenValueSts KEY_vKey8Import(uint16 *value);
KEY_tenValueSts KEY_vKey9Import(uint16 *value);
KEY_tenValueSts KEY_vKeyForce1Import(uint16 *value);
KEY_tenValueSts KEY_vKeyForce2Import(uint16 *value);
KEY_tenValueSts KEY_vKeyForce3Import(uint16 *value);
KEY_tenValueSts KEY_vKeyForce4Import(uint16 *value);
KEY_tenValueSts KEY_vKeyForce5Import(uint16 *value);
KEY_tenValueSts KEY_vKeyForce6Import(uint16 *value);
KEY_tenValueSts KEY_vKeyForce7Import(uint16 *value);
KEY_tenValueSts KEY_vKeyForce8Import(uint16 *value);
KEY_tenValueSts KEY_vKeyForce9Import(uint16 *value);
void KEY_vKeyClearPhyKeyFalg(void);
uint32 KEY_vKeyGetPhyKeyPressAction(void);
uint32 Key_u32ForceSensorADProcess(void);
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: DCM_Cfg.h
******************************************************************************/

