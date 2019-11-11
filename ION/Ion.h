/*******************************************************************************
| Module Name: Ion Control
| File Name: Ion.h
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
| Yang Shengli                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-02-25  1.00        Yang Shengli      First implementation
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef ION_H
#define ION_H


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

#include "Ion_Cfg.h"                 /* Configuration head file */
#include "Ion_Type.h"                 /* General definitions and datatypes */


/*****************************************************************************
*EXPORT INTERFACE FUNCTION DEFINE
******************************************************************************/
extern void ION_vReset(void);               /* called from reset comtainer      */
extern void ION_vInit( void);
extern void ION_vDeinit( void);
extern void ION_vActive(void);              /* active container (100mS)         */
extern void ION_vMain(void);                /* on container (100mS)             */
extern uint8 ION_u8GetValue( ION_tu8enVarNumber enIndex );
extern uint16 ION_u16GetValue( ION_tu16enVarNumber enIndex );
extern void  ION_vObdMain(void);
Std_ReturnType ION_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);
void  ION_vClearErrorCode(void);  
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: ION.h
******************************************************************************/
