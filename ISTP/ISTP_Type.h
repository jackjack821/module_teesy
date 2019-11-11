/*******************************************************************************
| Module Name: start stop Function module(Idle engine stop )
| File Name: ISTP_Type.h
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

#ifndef ISTP_TYPE_H
#define ISTP_TYPE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */
#include "General.h"
/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */


/*****************************************************************************
* DEFINE DATA TYPE INTERNAL
*
* In this section
* - define all the private data types of this module.
******************************************************************************/


// can msssage CL2_StSt_Info state enum
typedef enum ISTP_enStSt_InfoTag
{
	ISTP_nReqStop=0,	// 0 = request engine stop
	ISTP_nRestart,		// 2 = Restart engine
	ISTP_nSysErr		// 3 =System error
}ISTP_tenStSt_Info;

// ISTP mode heat or cool mode state enum
typedef enum ISTP_enModeControlTag
{
	ISTP_nDefault=0,
	ISTP_nHeatMode,
	ISTP_nCoolMode,
	ISTP_nErrMode
}ISTP_tenModeControl;

// ISTP mode priority  enum
typedef enum ISTP_enPriorityLevelTag
{
	ISTP_nLevel0=0,
	ISTP_nLevel1,
	ISTP_nLevel2,
	ISTP_nLevel3,
	ISTP_nLevel4,
	ISTP_nMax
	
}ISTP_tenPriorityLevel;


typedef enum ISTP_enRestartTag
{
	ISTP_nStop=0,
	ISTP_nHiCause,
	ISTP_nLoCause,
	ISTP_nBlowerLvl,
	ISTP_nDefrostCause,
	ISTP_nBlowOutCause,
	ISTP_nInCarTempCause,
	ISTP_nOthers
}ISTP_tenRestartCause;


typedef enum ISTP_enu8VarNumber
{
	ISTP_nenStStInfo=0,
	ISTP_nu8Valid,
	ISTP_nenRestartCause,
	ISTP_nu8ErrorStatus,
	ISTP_nu8ISState,
	ISTP_nu8Allowance,
	ISTP_nu8StartReq,
	ISTP_nu8Version,
	ISTP_nu8Max                     
}ISTP_tenu8VarNumber;

typedef enum ISTP_enu16VarNumber
{
	ISTP_nu16IsTimer=0,
	ISTP_nu16IrTimer,
	ISTP_nu16ErrorCode,
	ISTP_nu16Max                     
}ISTP_tenu16VarNumber;

typedef enum ISTP_enSSMStatus
{
	ISTP_Reset=0,
	ISTP_Standby,
	ISTP_Stopped,
	ISTP_StarterRestart,
	ISTP_EngineRestart,
	ISTP_Operation,
	ISTP_AutoStopping,
	ISTP_nuSSM8Max                     
}ISTP_tenSSMStatus;

typedef enum ISTP_enISState
{
	ISTP_nEngineStop=0,
	ISTP_nEngineRunning,
	ISTP_nReady,
	ISTP_nu8ISMax                     
}ISTP_tenISState;

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef RFA_TYPE_H */
/*****************************************************************************
* EOF: ISTP_Type.h
******************************************************************************/

