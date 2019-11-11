/*******************************************************************************
| Module Name: KEY capture and debouncing  
| File Name: KEY.h
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
| Date          Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2016.8.3      0100      Li jiaye         module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/

#ifndef KEY_H
#define KEY_H

/* System-headerfiles */
#include "General.h"

/* Own headerfiles */


void KEY_vReset(void);      /* Reset Container */
void KEY_vInit(void);         /* StandbyActive Container */
void KEY_vDeinit(void);      /* ActiveStandby Container */
void KEY_vMain(void);       /* On Container */
void KEY_vActive(void);     /* Active Container */
uint16 KEY_u16PressedKey(void);
uint32 KEY_u32PressedKey(void);
uint16 KEY_u16PressedKeyForPts(void);
uint32 KEY_u32KeyStatusIsPress(void);

#endif                                
