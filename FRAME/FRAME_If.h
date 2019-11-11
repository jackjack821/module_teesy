/*******************************************************************************
| Module Name: Task config
| File Name: Frame_If.h
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
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver        	Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 
|2015.10.17  V1.10      Li, Ning		   :add Interface of debug function
********************************************************************************/
#ifndef FRAME_IF_H
#define FRAME_IF_H

#ifndef Frame_c
  #define frame_ext extern
#else
  #define frame_ext
#endif



#include "FRAME_Type.h"
#include "frame_cfg.h"
#include "mcu_cfg.h"


#if (FRAME_AppSleep==1)
frame_ext uint8 FRAME_vGetAspSleepStatus(void);
#endif

#if (FRAME_BusSleep==1)
frame_ext uint8 FRAME_vGetBusSleepStatus(void);
#endif

/*import*/
frame_ext uint16 FRAME_vImpIDIgnStaticOn(void);
frame_ext uint16 FRAME_vImpIDIgnStable(void);
frame_ext uint16 FRAME_vImpIDIgnIgn2IoStauts(void);
frame_ext uint16 FRAME_vImpIDHalIgn2IoStauts(void);

/*export*/
frame_ext  uint16 FRAME_vExpIDSysBackground1s(void);
frame_ext  uint16 FRAME_vExpIDSysForeground1s(void);
frame_ext  uint16 FRAME_vExpIDAll(void);
frame_ext uint16 FRAME_u16GetValue(SYS_ten16VarNumber valueID);
frame_ext  uint16 FRAME_u16Array[SYS_nu16Max];

/*other*/
frame_ext  uint16 FRAME_vIfOpenRouser(void);
frame_ext  uint16 FRAME_vIfCloseRouser(void);

#if (DebugOS_MonitorTaskTimer==1)
frame_ext   uint16 FRAME_vHalTaskTimeStart_DebugTimer(void);
frame_ext   uint16 FRAME_vHalTaskTimeStop_DebugTimer(void);
//frame_ext   uint16 FRAME_vHalTimerRegiste_DebugTimer();
#endif
//frame_ext   uint16 FRAME_vHalTimerRegiste_SysTimer(void);

 frame_ext  uint16 FRAME_vHalStopMode(void);
 frame_ext  uint16 FRAME_vHalDi(void);
 frame_ext  uint16 FRAME_vHalEi(void);
 frame_ext uint16 FRAME_vHalIgnMain(void);
 frame_ext uint16 FRAME_vHalPowMain(void);
 frame_ext uint16 FRAME_vHalIgnReset(void);
 frame_ext uint16 FRAME_vHalPowReset(void);
 frame_ext uint16 FRAME_vHalIgnInit(void);
 frame_ext uint16 FRAME_vHalPowInit(void);
 frame_ext   uint16 FRAME_vHalSwWdtReset(void);
 frame_ext   uint16 FRAME_vHWdogClr( void);
 frame_ext  uint16 FRAME_vRteProto_Update( void);
 frame_ext   uint16 FRAME_vFinalSleepCheck(void);
 frame_ext   void SYS_vPeripheralInit(void);

 #if (FRAME_HwSBCUsed==1)
  frame_ext uint16 FRAME_vDoSBCSleepCmd(void);
 #endif

 frame_ext   void SYS_vWakeUpContainer(void);
#endif
void MCU_vCycleWakeUp(int WakeUpEnable);


