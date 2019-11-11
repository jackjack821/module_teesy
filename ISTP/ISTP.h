/*******************************************************************************
| Module Name: start stop Function module(Idle engine stop )
| File Name: ISTP1c1.c
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
| Luo Xindian                             Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2015-10-15    1.0  Luo Xindian		 frist created,for general start stop function 
| 2016-2-18      1.1  Luo Xindian		Modified for KC-2
********************************************************************************/

#ifndef ISTP1C1_H
#define ISTP1C1_H
/*
#ifndef ISTP1C1
  #define ext extern
#else
  #define ext
#endif
*/
#include "General.h"
#include "ISTP_Cfg.h"

#include "ISTP_Type.h"

void ISTP_vReset(void);               /* called from reset comtainer      */
void ISTP_vInit( void);
void ISTP_vDeinit( void);
void ISTP_vMain(void);                /* on container (100mS)             */

uint8 ISTP_u8GetValue( ISTP_tenu8VarNumber enIndex );

uint16 ISTP_u16GetValue( ISTP_tenu16VarNumber enIndex );

//#undef ext

#endif                     

