/*******************************************************************************
| Module Name: Recirculation Fresh Air control interface
| File Name: RFA_Interface.h
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
#ifndef RFA_Interface_H
#define RFA_Interface_H



#include "RFA_Private.h"


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
RFA_tenValueSts RFA_enMMIModeImport(RFA_tenRecircModeStates *value);
RFA_tenValueSts RFA_enMMIControlImport(RFA_tenRecircStates *value);
RFA_tenValueSts RFA_enPowFailureImport(uint8 *value);
#if(RFA_biSystemState == True)
RFA_tenValueSts RFA_enCcsBloutTempImport(uint16 *value);
RFA_tenValueSts RFA_enOATValueImport(uint16 *value);
RFA_tenValueSts RFA_enSys1000msValueImport(uint8 *value);
#endif

#if(RFA_biAQS_Cfg == True)
RFA_tenValueSts RFA_enAqsReqValueImport(uint8 *value);
RFA_tenValueSts RFA_enAqsStateValueImport(uint8 *value);
#endif

#if(RFA_nPM25Cfg == True)
RFA_tenValueSts RFA_enPM25InSideValueImport(uint16 *value);
RFA_tenValueSts RFA_enPM25OutSideValueImport(uint16 *value);
#endif

RFA_tenValueSts RFA_enGetStMainOutExport(RFA_tstMainOut *value);
RFA_tenValueSts RFA_enGetU8InitCounterExport(uint8 *value);

void RFA_vOutputUpdate(void);


/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: DCM_Cfg.h
******************************************************************************/

