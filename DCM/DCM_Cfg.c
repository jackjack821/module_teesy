/*******************************************************************************
| Module Name: directed current motor
| File Name: DCM_Cfg.c
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
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2014.7.17         A0      Li jiaye         module template update. 
| 2014.8.21         A1      Li jiaye         module code updated after coding reviewed.
| 2015.3.29	        A2      Li Jiaye	     add DCM property config
| 2016.2.17         A3      Li Jiaye         module upgraded
| 2016.4.19         A4      Li Jiaye         For base code creating
| 
| 
********************************************************************************/


/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define DCM_Cfg                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
//#include "Mac.h"
//#include "Aird.h"

/* Own headerfiles */
#include "DCM_Type.h"
#include "DCM_Cfg.h"
#include "DCM_Interface.h"

/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/
DCM_tstMotorProperty DCM_stMotorProperty[MotorNum]=
{/*name,feedbackConfig, Maxposition, Minposition, Startvalue, Stopvalue, DrivingActionTmr, MinADChange, BlockPreviousDrvCount,
    SetTargetposition,GetCurrentposition,DirectionThresholdValue,MovingSpeed*/
    DCM_vDefMotor(MixDrMotor,WithFeedback,1000u,50u,8,4,1600u,8u,8u,DCM_GetMacTargetPos,DCM_GetMacCurrentPos,500u,50u),       
    DCM_vDefMotor(AirdMotor,WithFeedback,1000u,50u,16,8,1600u,8u,8u,DCM_GetAirdTargetPos,DCM_GetAirdCurrentPos,500u,50u),
    DCM_vDefMotor(RFAMotor,WithFeedback,1000u,50u,16,8,1200u,8u,8u,DCM_GetRfaTargetPos,DCM_GetRfaCurrentPos,500u,50u),       
#if(SYC_ZONES == 2)
    DCM_vDefMotor(MixPsMotor,WithFeedback,1000u,50u,8,4,1600u,8u,8u,DCM_GetMacPsTargetPos,DCM_GetMacPsCurrentPos,500u,50u)
#endif
};
#ifdef PINDRIVER
DCM_tstMotorPinSts DCM_astMotorSetPIN[MotorNum]=
{
    DCM_vDefMotorPIN(MixDr,DCM_enSetMotor0PINExport),
    DCM_vDefMotorPIN(Aird,DCM_enSetMotor0PINExport),
    DCM_vDefMotorPIN(Rfa,DCM_enSetMotor0PINExport)
};
#endif
/*****************************************************************************
* EOF: DCM_Cfg.c
*****************************************************************************/
