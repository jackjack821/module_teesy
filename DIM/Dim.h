/*******************************************************************************
| Module Name: Dimmer Control
| File Name: Dim.h
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
| 2016-05-18  1.00        Yang Shengli      First implementation
| 2016-06-18  2.00        Yang Shengli      module upgraded
********************************************************************************/
#ifndef DIM_H
#define DIM_H


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

#include "DIM_Cfg.h"                 /* Configuration head file */
#include "DIM_Type.h"                 /* General definitions and datatypes */


/*****************************************************************************
*EXPORT INTERFACE FUNCTION DEFINE
******************************************************************************/
extern void DIM_vReset(void);               /* called from reset comtainer      */
extern void DIM_vInit(void);
extern void DIM_vDeinit(void);
extern void DIM_vActive(void);              /* active container (100mS)         */
extern void DIM_vMain(void);                /* on container (100mS)             */
DIM_tenValueSts DIM_enGetU8InitCounterExport(uint8 *value);
extern uint16 DIM_u16GetValue(DIM_tu16enVarNumber enIndex );
extern DIM_tenValueSts DIM_enU8InputValueCalc(DIM_tstU8InputAttributes *Input, uint8 *Output);
extern void DIM_vILLInputPwmDetect(uint16 *DutyValue);
extern void Callback_MCU_ISR_TAUD0_12(void);
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
extern void L1_Duty_light(uint32 parameter);
extern void L2_Duty_light(uint32 parameter);
extern void L3_Duty_light(uint32 parameter);
extern void L4_Duty_light(uint32 parameter);


#endif                                  /* ifndef */

/*****************************************************************************
* EOF: DIM.h
******************************************************************************/

