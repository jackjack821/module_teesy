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
#ifndef OS_FRAME_Type_H
#define OS_FRAME_Type_H


#include "General.h"


typedef struct SYS_stForceSort
{
	uint8 Sys_en5vOutPutFlag:1;
	uint8 Sys_en5vOutPutValue:1;
	uint8 Sys_enSensorSupplyFlag:1;
	uint8 Sys_enSensorSupplyValue:1;
		
}tstSYS_ForceSort;

/* extern function */



typedef enum{		
		OS_nu16NotUsed=0,
		OS_nu16StatisticStart,
		OS_nu16StatisticEnd	
	}OS_tenu16MaxLoadNum;


typedef enum
{
	SYS_nu16Flag1000MS_BG=0,
	SYS_nu16Flag1000MS_FG,
	SYS_nu16FlagFGrun,
	SYS_nu16FlagBGrun,
	SYS_nu16Info,
	SYS_nu16SwVersion,
	SYS_nu16ErrorCode,

	#if(DebugOS_MonitorTaskTimer==True)	
	SYS_nu16ForeOnTaskDtcOut,
	SYS_n16BackOnTaskDtcOut,
	#endif
	
	#if (DebugOS_MaxLoadRate==True)
	SYS_nu16ForeMaxLoadOut,
	SYS_n16FBMaxLoadOut,
	#endif
	SYS_nu16ResetStatus,	// 0=reset finish 1=reset going

	
	
	#if (DebugOS_SwInitTime==True)
	OS_nu16SwInitTimeOut,
	#endif
	
	SYS_nu16Max
}SYS_ten16VarNumber;

typedef  struct {

	uint16 FRAME_u16Flag1000MS_BG;
	uint16 FRAME_u16Flag1000MS_FG;
	uint16 FRAME_u16FlagFGrun;
	uint16 FRAME_u16FlagBGrun;
	uint16 FRAME_u16Info;
	uint16 FRAME_u16ForegroudTick;
	uint16 FRAME_u16BackgroudTick;
	uint16 FRAME_u16TaskRunningTime;
	uint16 FRAME_u16TaskRunEnable;
	uint16 FRAME_u16ForegroundRunEnable;
	uint16 FRAME_u16BackgroundRunEnable;

	#if(DebugOS_MonitorTaskTimer==True)	
	uint16 FRAME_u16ForeOnTaskDtcOut;
	uint16 FRAME_u16BackOnTaskDtcOut;
	#endif
	
	#if (DebugOS_MaxLoadRate==True)
	uint16 FRAME_u16ForeMaxLoadOut;
	uint16 FRAME_u16FBMaxLoadOut;
	#endif

	
	#if (DebugOS_SwInitTime)
	uint16 OS_u16SwInitTimeOut;
	#endif	
	
}SYS_FRAME;

typedef enum
{
	SYS_enMode_PwrOn,				/*system mode only when power on*/
	SYS_enMode_NotStable,			/*system mode only when IG debounding*/
	SYS_enMode_Active,				/*system mode in Active*/
	SYS_enMode_On,					/*system mode in On*/
	SYS_enMode_Standby,			/*system mode in Standby*/
	SYS_enMode_OnBoardDebug		/*system mode in OBD, only for TPS test*/
}SYS_enMODE;





#endif


