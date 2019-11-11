/*******************************************************************************
| Module Name: AQS Control
| File Name: Aqs.h
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
#ifndef AQS_H
#define AQS_H


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

#include "AQS_Cfg.h"                 /* Configuration head file */
#include "AQS_Type.h"                 /* General definitions and datatypes */
#include "Rte_Internal.h"

/*****************************************************************************
*EXPORT INTERFACE FUNCTION DEFINE
******************************************************************************/
extern void AQS_vReset(void);               /* called from reset comtainer      */
extern void AQS_vInit( void);
extern void AQS_vDeinit( void);
extern void AQS_vActive(void);              /* active container (100mS)         */
extern void AQS_vMain(void);                /* on container (100mS)             */
extern void AQS_vActiveStandby(void);
extern uint8 AQS_u8GetValue( AQS_tu8enVarNumber enIndex );
extern Std_ReturnType AQS_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord);
extern uint16 AQS_u16GetValue( AQS_tu16enVarNumber enIndex );
extern void Callback_MCU_ISR_TAUJ1_2(void);

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: AQS.h
******************************************************************************/
