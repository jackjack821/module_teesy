/*******************************************************************************
| Module Name: Air distribution control interface
| File Name: AIRD_Interface.h
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
| 2016.5.17         A0      Li jiaye         module template update. 
| 
| 
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef AIRD_Interface_H
#define AIRD_Interface_H



#include "AIRD_Private.h"


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
AIRD_tenValueSts AIRD_enMMIModeImport(AIRD_tenMMIModeSts *value);
AIRD_tenValueSts AIRD_enMMIControlImport(AIRD_tenMMIControlSts *value);
AIRD_tenValueSts AIRD_enPowFailureImport(uint8 *value);
AIRD_tenValueSts AIRD_enCcsBloutTempImport(uint16 *value);
AIRD_tenValueSts AIRD_enOATValueImport(uint16 *value);
AIRD_tenValueSts AIRD_enHctValueImport(uint16 *value);

AIRD_tenValueSts AIRD_enGetStMainOutExport(Aird_tstMainOut *value);
void AIRD_enSetStMainOutExport(Aird_tstMainOut *value);
AIRD_tenValueSts AIRD_enGetU8InitCounterExport(uint8 *value);

void AIRD_vClrForceFlagByteAction(void);

void AIRD_vOutputUpdate(void);


/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: DCM_Cfg.h
******************************************************************************/

