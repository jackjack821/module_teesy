/*******************************************************************************
| Module Name: evaporator caculation module
| File Name: EVAP.h
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

#ifndef 	EVAP1C1_H_
#define 	EVAP1C1_H_

/* Foreign headerfiles */
#include "General.h"
#include "EVAP_Type.h"

void EVAP_vReset (void);			/* Reset Container */
void EVAP_vInit (void);			/* StandbyActive Container */
void EVAP_vDeinit (void);
void EVAP_vMain (void);			/* On Container */
void EVAP_vActive (void);
uint8 EVAP_u8GetValue( EVAP_tenu8VarNumber enIndex );

uint16 EVAP_u16GetValue( EVAP_tenu16VarNumber enIndex );
void EVAP_vCcpControl(uint32 u32ControlData);

Std_ReturnType EVAP_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);
#endif /*HCS1C1_H_*/

