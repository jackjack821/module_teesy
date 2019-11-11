/*******************************************************************************
| Module Name: start stop Function module(Idle engine stop )
| File Name: ISTP_Private.h
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

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef RFA_PRIVATE_H
#define RFA_PRIVATE_H


/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */


/*****************************************************************************
* EXPORT INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define helpful macros for easy data access and for a comfortable function use, if 
*   necessary.
* - define all macros for accessing the external module interfaces variables
* - define all macros which not need to be configed and changed for this module 
******************************************************************************/

/**************************Extern Module Interface*******************************/

/*************************Extern Module Interface End****************************/

/***************************No Config Parameter********************************/
//here will define the macro which not to be changed for ever
#define ISTP_OpenInterfaces_Cfg   (Yes)  /* Yes is to open Getvalue and GetBuffer interfaces*/

#define ISTP_nSwVersion					(0xA2)

#define ISTP_u8CoolTempDiffH			(590)/*-5Cdeg*/
#define ISTP_u8CoolTempDiffL			(560)/*-8Cdeg*/

// heat mode
#define ISTP_i8HeatTBlowoutH		      (120)/*12Cdeg */
#define ISTP_i8HeatTBlowoutL			      (80)/* 8Cdeg*/

#define ISTP_i8HeatTempDiffH			(720)/*8Cdeg*/
#define ISTP_i8HeatTempDiffL				(690)/*5Cdeg*/

#define ISTP_u8CoolantTempH			(950)/*55Cdeg*/
#define ISTP_u8CoolantTempL				(800)/*40Cdeg*/

#define ISTP_u8DefaultTempDiffH			(80)/* 8Cdeg*/
#define ISTP_u8DefaultTempDiffL			(50)/*5Cdeg*/

#define ISTP_u8BowerHi				(5)
#define ISTP_u8BowerLo				(4)

#define ISTP_u16HeatModeOat			(550)/* 15 Cdeg*/
#define ISTP_u16CoolModeOat				(650)/*25 Cdeg*/

#define ISTP_u16DefaultModeOatL			(580)/* 18 Cdeg*/
#define ISTP_u16DefaultModeOatH			(630)/*23 Cdeg*/

#define ISTP_i8CcsBlowOutLimitH			(-80)//  -8 degree
#define ISTP_i8CcsBlowOutLimitL			(-120)//  -12 degree

#define ISTP_nCompressorOff				(0)
#define ISTP_u8ModeOff 					(0)
#define ISTP_u8Defrost					(3)
#define ISTP_u8MaxAC					(4)
/*************************No Config Parameter End******************************/
#define ISTP_u8GetFuctionCfg(u8FunctionCfg)          DIAG_FunctionCf(u8FunctionCfg)

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef RFA_PRIVATE_H*/

/*****************************************************************************
* EOF: ISTP
******************************************************************************/
