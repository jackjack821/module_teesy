/*******************************************************************************
| Module Name: Task frame schedule model
| File Name: os_frame1c1.h
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
| Sui Yanchun                        Desay SV Automotive Co., Ltd
| Du Zejia                             Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver        	Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 
|2015.10.17  V1.10      Li, Ning		   :add cfg of debug function
********************************************************************************/
#ifndef FRAME_H
#define FRAME_H

#ifndef Frame_c
  #define fram_ext extern
#else
  #define fram_ext
#endif

#include "FRAME_If.h"





fram_ext void FRAME_vFrameForegroundTick1s(void);
fram_ext void FRAME_vFrameBackgroundTick1s(void);
fram_ext void FRAME_vFRAME_ForegroundReset(void);
fram_ext void FRAME_vFRAME_BackgroundReset(void);
fram_ext Std_ReturnType SYS_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);
#if (DebugPinTest==1)
fram_ext void TestECircle(void);
#endif





#endif


