/*******************************************************************************
| Module Name: KNOB capture and debouncing interface
| File Name: KNOB_interface.h
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
#ifndef KNOB_Interface_H
#define KNOB_Interface_H


#include "KNOB_Type.h"
#include "KNOB_cfg.h"
#ifdef KNOB_RTE
#include "RTE_Knob.h"
#endif




extern KNOB_tstProperty Knob_stProperty[KnobNum];
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
void KNOB_vClrForceFlagByteAction(void);
//KNOB_tenValueSts KNOB_vForceKNOBPressImport(uint8 IndexInput, uint8 *Output);
void KNOB_vMainExportAction(void);
//KNOB_tenValueSts KNOB_enGetMainOutputExport(KNOB_tstMainOut *value);
KNOB_tenValueSts KNOB_enGetMainOutputExport(uint8 index, KNOB_tstMainOut *value);
KNOB_tenValueSts KNOB_enTempPINAImport(uint8 *value);
KNOB_tenValueSts KNOB_enTempPINBImport(uint8 *value);
KNOB_tenValueSts KNOB_enBlowerPINAImport(uint8 *value);
KNOB_tenValueSts KNOB_enBlowerPINBImport(uint8 *value);
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: Knob_Interface.h
******************************************************************************/

