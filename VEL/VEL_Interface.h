/*******************************************************************************
| Module Name: Calculate the Blowout and Temp offset according to the VELocity
| File Name: VEL_interface.c
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
| Li Jiaye                           Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2013-04-09  1.00        Sui Yanchun       First implementation
| 2015-08-06  2.00        Zhang Shuncong    Add RTE ,Copyright and cfg
| 2016-09-21  0100        Li Jiaye          interface updated
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef VEL_Interface_H
#define VEL_Interface_H

/* System-headerfiles */
//#include "Rte_VEL.h"
/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Own headerfiles */
#include "VEL_Private.h"
#include "VEL_type.h"

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
void VEL_vClrForceFlagByteAction(void);
VEL_tenValueSts VEL_enVeIocityInvalidImport(uint8 *value);
VEL_tenValueSts VEL_enVeIocityValueImport(uint16 *value);
VEL_tenValueSts VEL_enOatValidImport(uint8 *value);
VEL_tenValueSts VEL_enOatValueImport(uint16 *value);
VEL_tenValueSts VEL_enGetMainOutputExport(Vel_tstMainOut *value);
void VEL_vMainExportAction(void);
Std_ReturnType VEL_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);


/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: DCM_Cfg.h
******************************************************************************/

