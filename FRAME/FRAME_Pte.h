/*******************************************************************************
| Module Name: Task frame schedule model
| File Name: os_framePte.h
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
|2016.4.26  V1.10      Li, Ning		   :first version
********************************************************************************/
#ifndef OS_FRAME_Pte
#define OS_FRAME_Pte



#include "FRAME_Type.h"



/* the os time parameter configuration */
#define SYS_FrameMaxTime					((uint8)(7))/*7ms*/
#define SYS_ForgroundTickCnt				((uint8)(10))/*10ms*/
#define FRAME_u16TickTimeCnt1000ms			((uint16)(1000))/*1000 ms*/
#define SYS_BackGroundTickCnt				((uint8)(100))/*100ms*/
#define SYS_Foregroud1sCountMax  			((uint8)99)
#define SYS_Backgroud1sCountMax   			((uint8)9)

/* the system status update and the current task run */
/*
#define IGN_u8SetKL15Value(Num)     			do{IGN_u8KL15State = (uint8)(Num);}while(0)
#define IGN_u8SetSleepValue(Num)   			do{IGN_u8SleepCnt = (uint8)(Num);}while(0)
#define IGN_u8SetSleepState(Num)     			do{IGN_boSleepCtrByObd = (uint8)(Num);}while(0)
*/
#define   SYS_biMachineStatusActionOnFalse		do{OS_SysState&=(uint8)0xfd;}while(0)
#define   SYS_biMachineStatusActionOnTrue		do{OS_SysState|=(uint8)0x02;}while(0) 

#define   SYS_biMachineStatusActiveFalse			do{OS_SysState&=(uint8)0xfe;}while(0) 
#define   SYS_biMachineStatusActiveTrue			do{OS_SysState|=(uint8)0x01;}while(0) 


#define	SYS_biMachineStatusChange2StandbyTrue			do{OS_SysState|=(uint8)0x10;}while(0)
#define	SYS_biMachineStatusChange2StandbyFalse		do{OS_SysState&=(uint8)0xEF;}while(0)
#define	SYS_biMachineStatusChange2ActiveTrue			do{OS_SysState|=(uint8)0x20;}while(0)
#define	SYS_biMachineStatusChange2ActiveFalse			do{OS_SysState&=(uint8)0xDF;}while(0)
#define   SYS_biMachineStatusChange2OnTrue				do{OS_SysState|=(uint8)0x40;}while(0)	
#define   SYS_biMachineStatusChange2OnFalse				do{OS_SysState&=(uint8)0xBF;}while(0)	
#define   SYS_biSystemBusyTrue							do{OS_SysState|=(uint8)0x80;}while(0)	
#define   SYS_biSystemBusyFalse							do{OS_SysState&=(uint8)0x7F;}while(0)

	
#define   SYS_getSystemBusy()					(OS_SysState>>7u)




#define FRAME_u8SysInitState						(OS_SysState)
#define FRAME_u8SysState    						(OS_SysState & 0x73U)


/* first high four bit then low four bit*/
#define KeepStandby 							0x10U
#define StandbyToActive 						0x20U
#define StandbyToOn							0x40U
#define ActiveToStandby 						0x11U
#define KeepActive							0x21U
#define ActiveToOn	 						0x41U
#define OnToActive	 						0x22U
#define KeepOn		 						0x42U

#define ForeTaskTimeOutCfg					10U		/*1ms note: the precision is 100us*/
#define BackTaskTimeOutCfg					30U		/*3mss note: the precision is 100us*/
#define TaskTimeOutErrCfg					100U	/*Max time out counter=10ms or 100ms*/

#define OS_SleepCountCfg						0x1f4U	/*sleep counter cfg: default value is 5s*/

#define OS_TimerOut7ms						0x0001
#define OS_ForeActiveTimeout				0x0002
#define OS_ForeOnTimeout					0x0004
#define OS_BackActiveTimeout				0x0008
#define OS_BackOnTimeout					0x0010



/* the os time macro definition */
#define get_bSysBackground1s()            (FRAME_u16InternalDataFlag1000MS_BG)
#define clr_bSysBackground1s()        	  (FRAME_u16InternalDataFlag1000MS_BG = 0U)
#define set_bSysBackground1s(val)        (FRAME_u16InternalDataFlag1000MS_BG = (val))

#define get_bSysForeground1s()            (FRAME_u16InternalDataFlag1000MS_FG)
#define clr_bSysForeground1s()             (FRAME_u16InternalDataFlag1000MS_FG = 0U)
#define set_bSysForeground1s(val)        (FRAME_u16InternalDataFlag1000MS_FG = (val))

#define get_bSysInfo()            			  (FRAME_u16InternalDataSysInfo)
#define clr_bSysInfo()       			  (FRAME_u16InternalDataSysInfo = 0U)
#define set_bSysInfo(val)       			  (FRAME_u16InternalDataSysInfo = (val))

#define get_bSysForegroudTick()            (FRAME_u16InternalDataForegroudTick)
#define clr_bSysForegroudTick()       	  (FRAME_u16InternalDataForegroudTick=0U)
#define inc_bSysForegroudTick()       	  (FRAME_u16InternalDataForegroudTick++)

#define get_bSysBackgroudTick()            (FRAME_u16InternalDataBackgroudTick)
#define clr_bSysBackgroudTick()       	  (FRAME_u16InternalDataBackgroudTick=0U)
#define inc_bSysBackgroudTick()       	  (FRAME_u16InternalDataBackgroudTick++)

#define get_bSysTaskRunningTime()       (FRAME_u16InternalDataTaskRunningTime)
#define clr_bSysTaskRunningTime()        (FRAME_u16InternalDataTaskRunningTime=0U)
#define inc_bSysTaskRunningTime()        (FRAME_u16InternalDataTaskRunningTime++)

#define get_bSysTaskRunEnable()            (FRAME_u16InternalDataTaskRunEnable)
#define set_bSysTaskRunEnable(val)       (FRAME_u16InternalDataTaskRunEnable = (val))

#define get_bSysForegroundRunEnable()            (FRAME_u16InternalDataForegroundRunEnable)
#define set_bSysForegroundRunEnable(val)        (FRAME_u16InternalDataForegroundRunEnable = (val))

#define get_bSysBackgroundRunEnable()            (FRAME_u16InternalDataBackgroundRunEnable)
#define set_bSysBackgroundRunEnable(val)        (FRAME_u16InternalDataBackgroundRunEnable = (val))

#define get_bSysSwVersion()				(FRAME_u16InternalDataSwVersion)
#define set_bSysSwVersion(val)			(FRAME_u16InternalDataSwVersion = (val))

#define get_bSysErrorCode() 				(FRAME_u16InternalDataErrorCode)
#define clr_bSysErrorCode(val) 			(FRAME_u16InternalDataErrorCode = (0U))

#if (DebugOS_SwInitTime==1)
#define get_bSysSwInitCounter()       	(FRAME_u16InternalDataSwInitTimeCounter)
#define clr_bSysSwInitCounter()       	 (FRAME_u16InternalDataSwInitTimeCounter=0U)
#define inc_bSysSwInitCounter()        	(FRAME_u16InternalDataSwInitTimeCounter++)
#endif





#define get_bPtsSleepStatus()               (OS_u16ForceSleep)
#define clr_bSysSleepStatus()        		(OS_u16ForceSleep = 0U)
#define set_bSysSleepStatus(val)         (OS_u16ForceSleep = (val))



uint8 FRAME_vGetMode(void);
void FRAME_vSetMode(SYS_enMODE mode);
void FRAME_vFRAMEAlways (void);
void FRAME_vFRAMEReset (void);

void FRAME_vFrameStandby (void);
void FRAME_vFrameStandbyActive(void);
void FRAME_vFrameActiveStandby(void);
void FRAME_vFrameActiveOn (void);
void FRAME_vFrameOnActive (void);



#endif


