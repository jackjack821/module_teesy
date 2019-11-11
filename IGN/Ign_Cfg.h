/*******************************************************************************
| Module Name: KL15 manage model
| File Name: ign_cfg.h
|
|-------------------------------------------------------------------------------
|				C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2015 Huizhou Desay SV Automotive Co., Ltd.	  All rights reserved.
|
| This software is copyright protected and proprietary to Desay SV Automotive Co., Ltd.
| Desay SV Automotive Co., Ltd grants to you only those rights as set out in the
| license conditions. All other rights remain with Desay SV Automotive Co., Ltd.
|
| REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
|-------------------------------------------------------------------------------
|				A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Name									Company
| --------------------- 	---------------------------------------
| Sui Yanchun						 Desay SV Automotive Co., Ltd
| Du Zejia							   Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|				R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date			   Ver			Author				 Description
| ----------  -------  -------------  -------------------------------------------------
| 
|2014/07/28 	Rev 01.00.00	  LN				 The first version	 
********************************************************************************/

/*****************************************************************************
* FILE DECLARATIGN
******************************************************************************/
#ifndef IGN_CFG_H
#define IGN_CFG_H
/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */
#include "General.h"
/* Own headerfiles */

/*****************************************************************************
* MACROS
*
* In this sectIGN declare
* - all macros used in the configuratIGN head file and C file.
******************************************************************************/


/*****************************************************************************
* MODULE CONFIGURATIGN DEFINITIGNS 
*
* In this sectIGN declare
* - all module configuratIGN defines which should be generated.
* - all type definitIGNs of your module  which should be generated.
******************************************************************************/



/*---------------------- macro switch definition--------------------------- */

/* if use crank signal from  bus*/
#define IGN_CrankFromBus	0

/*if use keypos signal from bus*/
#define IGN_KeyPosFromBus 	0

/*if use ign from bus*/
#define  IGN_IgnBus_Used		0

/*if use ign1*/
#define  IGN_Ign1_Used		0

/*if use ign2*/
#define  IGN_Ign2_Used		1		/*defaultly use ign2 as k15*/

/*if use ign2 feedback*/
#define  IGN_Ign2Fb_Used	0

/*if use rte*/
#define IGN_RteUsed			0

/*if use remote signal for wake up mcu*/
#define IGN_RemoteUsed		0

/*if use ign lost function.it need use ign signal by hw and bus */
#define IGN_CheckIgnLostUsed			0







/*------------------Ignition pin------------*/

#if (IGN_Ign2_Used == 1)
#define IGN_nIGN2PortPin		True //0x0006		/*defaultly use ign2 as k15*/


/*--configuration of the k15 feedback detection --*/
#define IGN_Volt_R1_Ign	100U				/*K*/
#define IGN_Volt_Rdiv_to_AD_Ign 	33UL	/*K*/
#define IGN_DiodeVolt	0.5                 /*Vol*/ /*change by ln matched the real shematic*/

#define IGN_Numerator_Part		(5*10*(IGN_Volt_R1_Ign+IGN_Volt_Rdiv_to_AD_Ign))
#define IGN_10TimeDiodeVolt		(IGN_DiodeVolt*10)
#define IGN_SupplyVot_10Times(vol)			(((((uint32)(vol))*IGN_Numerator_Part/IGN_Volt_Rdiv_to_AD_Ign)>>10)+IGN_10TimeDiodeVolt)	/*(volad*5*(R1+RAD)/(1023*RAD)+DiodeVol)*10*/

#endif

#if(IGN_Ign2Fb_Used==1)

#define IGN_nRawIGN2Fb MCU_mADCID_ADCA0I4

#endif

#if (IGN_Ign1_Used == 1)
#define IGN_nIGN1PortPin		0x0007
//#define IGN_nIGN1Pin		3

#define IGN_nRawIGN1Fb MCU_mADCID_ADCA0I6

#endif

#if (IGN_RemoteUsed==1)
#define IGN_nRemoteIoPortPin		0x0000	
#define IGN_nRemoteIoFb 		MCU_mADCID_ADCA0I5
#endif



/*----------- Stability parameter -----------*/

/*IGN_u8NotStableTimeCfg>IGN_u8DebounceOffTimeCfg>IGN_u8DebounceOnTimeCfg*/

#define IGN_u8NotStableTimeCfg 			25	/*status2: filter time when k15 line change=200ms */  

#define IGN_u8DebounceOnTimeCfg		20     /* debounce time when kl15 on=200ms = micro interrupt test require 100ms*/

#define IGN_u8DebounceOffTimeCfg		22     /* debounce time when kl15 off =120ms*/  

#define IGN_u8ClientOn2OffCfg			20    /* first:off to on time. must bigger than IGN_u8DebounceOffTimeCfg  */

#define IGN_u8ClientOff2OnCfg			70    /* first:off to on time request by client default value. must bigger than IGN_u8DebounceOnTimeCfg */

#define IGN_u8ClientOn2OffCfg2			0    /* second:off to on time. must bigger than IGN_u8DebounceOffTimeCfg  */

#define IGN_u8ClientOff2OnCfg2			0    /*second: off to on time request by client default value. must bigger than IGN_u8DebounceOnTimeCfg */




/*------------hardware k15 lost time configuration------------*/
#define IGN_LostK15IOTimeCfg			0x0258		/*delay time for lost K15 IO when k15 from bus is on ,counter = 6s*/





/*****************************************************************************
* MODULE CONFIGURATIGN DECLARATIGNS 
*
* In this sectIGN declare
* - module variable declaratIGNs for the variable in the cfg.c file, which will be used in module 
     functIGNs.
******************************************************************************/


/*****************************************************************************
* End of check if informatIGNs are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: IGN_Cfg.h
******************************************************************************/
