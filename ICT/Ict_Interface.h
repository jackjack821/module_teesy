/*******************************************************************************
| Module Name: Calculate in car temperature value(Interface)
| File Name: Ict_interface.h
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
| Ouyang Bihuan                      Desay SV Automotive Co., Ltd
| Li Jiaye                           Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2015-7-2    Rev 1.1   Ouyang Bihuan       Create the module base on ICT of GAC A28.
| 2016-09-27  0100        Li Jiaye          interface updated
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef ICT_Interface_H
#define ICT_Interface_H

/* System-headerfiles */
#include "Rte_internal.h"
/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Own headerfiles */
#include "ICT_Private.h"
#include "ICT_type.h"

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
ICT_tenValueSts ICT_enMmiSetTempImport(uint8 *value);
ICT_tenValueSts ICT_enSonserRawValueImport(uint16 *value);
ICT_tenValueSts ICT_enOatValidImport(uint8 *value);
ICT_tenValueSts ICT_enAirdValidImport(uint8 *value);
ICT_tenValueSts ICT_enOatValueImport(uint16 *value);
ICT_tenValueSts ICT_enAirdPosValueImport(uint16 *value);
ICT_tenValueSts ICT_enCcsSetTempImport(uint16 *value);
ICT_tenValueSts ICT_enCcsValidImport(uint8 *value);
ICT_tenValueSts ICT_enPowValidImport(uint8 *value);
void ICT_vClrForceFlagByteAction(void);
ICT_tenValueSts ICT_enGetMainOutputExport(ICT_tstMainOut *value);
void ICT_vMainExportAction(void);
Std_ReturnType ICT_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord);
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: ICT_interface.h
******************************************************************************/

