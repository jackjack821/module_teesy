
/*******************************************************************************
| Module Name: Recirculation Fresh Air control 
| File Name: RFA.h
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
| Luo Xindian                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2016.6.26         A0      Luo Xindian         module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/

#ifndef RFA_H
#define RFA_H

/* System-headerfiles */
#include "General.h"

/* Own headerfiles */
#include "RFA_Cfg.h"
#include "RFA_Type.h"

#ifndef RFA_UseRTE
void RFA_vReset(void);      /* Reset Container */
void RFA_vInit(void);         /* StandbyActive Container */
void RFA_vDeinit(void);      /* ActiveStandby Container */
void RFA_vMain(void);       /* On Container */
void RFA_vActive(void);     /* Active Container */

uint8 RFA_u8GetValue( RFA_tenu8VarNumber enIndex );

uint16 RFA_u16GetValue( RFA_tenu16VarNumber enIndex );
#endif
uint8 RFA_ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);

uint16 RFA_vGetForceRfaControlFlag(CcpControl_Rfa Index);
#endif                                

