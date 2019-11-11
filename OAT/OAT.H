
/*******************************************************************************
| Module Name: Calculate the ambient temperature
| File Name: OAT.h
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2016 Huizhou Desay SV Automotive Co., Ltd.    All rights reserved.
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
| Zou Riming                    Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-07-11   0100        Zou Riming          fist time create
|
********************************************************************************/

#ifndef OAT_H
#define OAT_H

/* System-headerfiles */

/* Foreign headerfiles */

/* Own headerfiles */
#include "OAT_Type.h"     


void OAT_vReset  (void);             /* Reset container                   */
void OAT_vInit   (void);                 /* Active -> On transition           */
void OAT_vDeinit (void);              /* On -> Active transition           */
void OAT_vMain   (void);               /* On Container (background) */
void OAT_vActive (void);               /* Active Container (background) */

uint16 OAT_u16GetValue( OAT_tenu16VarNumber enIndex );
OAT_tenValueSts OAT_enGetU8InitCounterExport(uint8 *value);

#endif                                  /* ifndef */

/*****************************************************************************
* EOF:OAT.h
******************************************************************************/
