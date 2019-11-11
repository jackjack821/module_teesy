/*******************************************************************************
| Module Name: Air Condition Compressor Control
| File Name: Accc.c
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
| Yang Tingyu                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2014/11/25  A1        Yang Tingyu		    The first version	
| 2016/01/11  A2        Yang Tingyu		    Modified for HEV
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef ACCC_H
#define ACCC_H


/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
#include "General.h"
/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */
#include "ACCC_Type.h"


/*****************************************************************************
* EXPORT INTERFACE VARIABLE DEFINITIONS 
*
* In this section define
* - all variables will be accessed by other module.
******************************************************************************/


/*****************************************************************************
* EXPORT INTERFACE FUNCTION PROTOTYPES
*
* In this section declare
* - all system global function prototypes of your module. This is a copy of the function 
*   definitions without the header template.
******************************************************************************/

 void ACCC_vReset  (void);        /* Reset Container                   */
 void ACCC_vInit(void);        /* StandbyActive Container           */
 void ACCC_vDeinit (void);        /* ActiveStandby Container           */
 void ACCC_vMain   (void);        /* On Container                      */
 uint8 ACCC_u8GetValue( ACCC_tenu8VarNumber enIndex );
 uint16 ACCC_u16GetValue(ACCC_tenu16VarNumber enIndex );

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef ACCC_H*/

/*****************************************************************************
* EOF: ACCC.h
******************************************************************************/

