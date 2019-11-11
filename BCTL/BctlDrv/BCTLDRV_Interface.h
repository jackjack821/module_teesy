/*******************************************************************************
| Module Name: Recirculation Fresh Air control interface
| File Name: BCTL_Interface.h
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
| 2016.7.1          A0        Ouyang Bihuan         First created for base code. 
| 
| 
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef BCTLDRV_Interface_H
#define BCTLDRV_Interface_H
#include "BCTLDRV_Private.h"


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
#if (BCTLDRV_nHW_RELAY_CTRL != 0U)
BCTLDRV_tenValueSts BCTLDRV_enRelaySigImport(uint8 *value);
#endif


BCTLDRV_tenValueSts BCTLDRV_enBlwVoltImport(uint16 *value);
#if(BCTLDRV_nWITH_FEED_BACK != 0U)
BCTLDRV_tenValueSts BCTLDRV_enPtaBlwVoltImport(uint16 *value);
#endif

void BCTLDRV_vOutputUpdate(void);
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: BCTLDRV_Interface.h
******************************************************************************/

