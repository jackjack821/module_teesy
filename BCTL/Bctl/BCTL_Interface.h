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
| 2016.7.1          A0        Luo Xindian         First created for base code. 
| 
| 
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef BCTL_Interface_H
#define BCTL_Interface_H



#include "BCTL_Private.h"


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
BCTL_tenValueSts BCTL_enAirdDisInfoImport(uint8 *value);
BCTL_tenValueSts BCTL_enAcccDisInfoImport(uint8 *value);
BCTL_tenValueSts BCTL_enIgnEnableSigImport(uint8 *value);
BCTL_tenValueSts BCTL_enIsStatusImport(uint8 *value);
BCTL_tenValueSts BCTL_enMmiSetTempDrImport(uint8 *value);
BCTL_tenValueSts BCTL_enMmiSetTempPsImport(uint8 *value);
BCTL_tenValueSts BCTL_enMmiBlwEventImport(uint8 *value);
BCTL_tenValueSts BCTL_enMmiBlwModeImport(uint8 *value);
BCTL_tenValueSts BCTL_enMmiBlwCtrlImport(uint8 *value);
BCTL_tenValueSts BCTL_enPowFailureImport(uint8 *value);
BCTL_tenValueSts BCTL_enRfaDisInfoImport(uint8 *value);

BCTL_tenValueSts BCTL_enCcsSetTempDrImport(uint16 *value);
BCTL_tenValueSts BCTL_enCcsSetTempPsImport(uint16 *value);
BCTL_tenValueSts BCTL_enCcsBlowoutAvgImport(uint16 *value);
BCTL_tenValueSts BCTL_enCcsSiDrImport(uint16 *value);
BCTL_tenValueSts BCTL_enCcsSiPsImport(uint16 *value);
BCTL_tenValueSts BCTL_enEvapVarImport(uint16 *value);
BCTL_tenValueSts BCTL_enHctVarImport(uint16 *value);
BCTL_tenValueSts BCTL_enOatValImport(uint16 *value);
BCTL_tenValueSts BCTL_enIncomingHeatImport(uint16 *value);
BCTL_tenValueSts BCTL_enSunVarImport(uint16 *value);
BCTL_tenValueSts BCTL_enVelVarImport(uint16 *value);

BCTL_tenValueSts BCTL_enGetStMainOutExport(BCTL_tstMainOut *value);

void BCTL_vOutputUpdate(void);
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: DCM_Cfg.h
******************************************************************************/

