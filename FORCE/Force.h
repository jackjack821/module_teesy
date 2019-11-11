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
|  Liu Longxi                         Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2019.4.15         0100      Liu Longxi        module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/

#ifndef Force_H
#define Force_H

/* System-headerfiles */
#include "General.h"
#include "Force_Type.h"
/* Own headerfiles */

extern FORCE_tstSensorCfg Sensor_stCfg[Force_KeyNum];
void Force_vReset(void);      /* Reset Container */
void Force_vInit(void);         /* StandbyActive Container */
void Force_vDeinit(void);      /* ActiveStandby Container */
void Force_vMain(void);       /* On Container */
void Force_vActive(void);     /* Active Container */
uint16 Force_u16PressedKey(void);
uint16 Force_u16PressedKeyForPts(void);
uint8 ForceSensor_u8GetValue(KEY_tenu8PadVarNum Num);
uint16 Force_u16ForceSensorADProcess(void);
uint16 Force_u16GetValue( Force_tu16enVarNumber enIndex );
#endif                                

