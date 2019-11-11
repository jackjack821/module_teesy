/*******************************************************************************
| Module Name: KL15 manage model
| File Name: ign.h
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
|2014/07/28		Rev 01.00.00      LN      			 The first version   
********************************************************************************/

/*****************************************************************************
* FILE DECLARATIGN
******************************************************************************/
#ifndef IGN_Pte_H
#define IGN_Pte_H

#ifndef IGN_C
  #define ign_ext extern
#else
  #define ign_ext
#endif

/*****************************************************************************
* LOCATIGN-DEFINES -only when the locatIGN assignment is needed.
******************************************************************************/


/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */
#include "IGN_Cfg.h"                 /* ConfiguratIGN head file */


/*****************************************************************************
* EXPORT INTERFACE DEFINITIGNS AND DECLARATIGNS
*
* In this sectIGN
* - define helpful macros for easy data access and for a comfortable functIGN use, if 
*   necessary.
* - define all global define-constants of your module.
* - define all module external interface functIGNs and defines
* - declare all system global ROM-constants.
* - declare all system global variables of your module.
* - adapt external symbols to internally used names if necessary. 
******************************************************************************/

#define IGN_SetLostK15IO		do{set_bIgnInternalDataErrorCode(0x0001);}while(0) 
#define IGN_ClrLostK15IO		do{clr_bIgnInternalDataErrorCode(0xfffe);}while(0) 

#define IGN_SetNeverRecK15Msg	do{set_bIgnInternalDataErrorCode(0x0002);}while(0) 
#define IGN_ClrNeverRecK15Msg	do{clr_bIgnInternalDataErrorCode(0xfffd);}while(0) 

#define IGN_SetLostK15Msg		do{set_bIgnInternalDataErrorCode(0x0004);}while(0) 
#define IGN_ClrLostK15Msg		do{clr_bIgnInternalDataErrorCode(0xfffb);}while(0) 

#define IGN_SetAbnormalValue		do{set_bIgnInternalDataErrorCode(0x0008);}while(0) 
#define IGN_ClrAbnormalValue		do{clr_bIgnInternalDataErrorCode(0xfff7);}while(0) 

/*input data macro definition*/



/* internal data macro definition*/
#if (IGN_KeyPosFromBus==1)
#define get_bIgnInternalKeyPos()      						(IGN_u16InternalKeyPos)
#define clr_bIgnInternalKeyPos()        						(IGN_u16InternalKeyPos=0U)
#define set_bIgnInternalKeyPos(val)         					(IGN_u16InternalKeyPos=(val))
#endif

#define get_bIgnInternalDataOff2OnFlag()      				(IGN_u16InternalDataOff2OnFlag)
#define clr_bIgnInternalDataOff2OnFlag()        				(IGN_u16InternalDataOff2OnFlag=0U)
#define set_bIgnInternalDataOff2OnFlag(val)         			(IGN_u16InternalDataOff2OnFlag=(val))

#define get_bIgnInternalDataOn2OffFlag()      				(IGN_u16InternalDataOn2OffFlag)
#define clr_bIgnInternalDataOn2OffFlag()        				(IGN_u16InternalDataOn2OffFlag=0U)
#define set_bIgnInternalDataOn2OffFlag(val)         			(IGN_u16InternalDataOn2OffFlag=(val))

#define get_bIgnInternalDataOff2OnFlag2()      				(IGN_u16InternalDataOff2OnFlag2)
#define clr_bIgnInternalDataOff2OnFlag2()        			(IGN_u16InternalDataOff2OnFlag2=0U)
#define set_bIgnInternalDataOff2OnFlag2(val)         			(IGN_u16InternalDataOff2OnFlag2=(val))

#define get_bIgnInternalDataOn2OffFlag2()      				(IGN_u16InternalDataOn2OffFlag2)
#define clr_bIgnInternalDataOn2OffFlag2()        			(IGN_u16InternalDataOn2OffFlag2=0U)
#define set_bIgnInternalDataOn2OffFlag2(val)         			(IGN_u16InternalDataOn2OffFlag2=(val))

#if (IGN_CrankFromBus==1)
#define get_bIgnInternalDataOff2OnOrLeaveCrankDelayFlag()      			(IGN_u16InternalDataOff2OnOrLeaveCrankDelayFlag)
#define clr_bIgnInternalDataOff2OnOrLeaveCrankDelayFlag()        			(IGN_u16InternalDataOff2OnOrLeaveCrankDelayFlag=0U)
#define set_bIgnInternalDataOff2OnOrLeaveCrankDelayFlag(val)         		(IGN_u16InternalDataOff2OnOrLeaveCrankDelayFlag=(val))
#endif


#define get_bIgnInternalDataSysIgnStatus()      			(IGN_u16InternalDataSysIgnStatus)
#define clr_bIgnInternalDataSysIgnStatus()        			(IGN_u16InternalDataSysIgnStatus=0U)
#define set_bIgnInternalDataSysIgnStatus(val)         		(IGN_u16InternalDataSysIgnStatus=(val))

/*use for ign2 and ign from bus*/
#define get_bIgnInternalDataIGN2IoStatus()      			(IGN_u16InternalDataIGN2IoStatus)
#define clr_bIgnInternalDataIGN2IoStatus()        			(IGN_u16InternalDataIGN2IoStatus=0U)
#define set_bIgnInternalDataIGN2IoStatus(val)         		(IGN_u16InternalDataIGN2IoStatus=(val))

#if (IGN_Ign2_Used == 1)
#define get_bIgnInternalDataIGN2Fb()      					(IGN_u16InternalDataIGN2Fb)
#define clr_bIgnInternalDataIGN2Fb()         				(IGN_u16InternalDataIGN2Fb=0U)
#define set_bIgnInternalDataIGN2Fb(val)         				(IGN_u16InternalDataIGN2Fb=(val))
#endif

#if (IGN_Ign1_Used == 1)
#define get_bIgnInternalDataIGN1IoStatus()      			(IGN_u16InternalDataIGN1IoStatus)
#define clr_bIgnInternalDataIGN1IoStatus(val)         		(IGN_u16InternalDataIGN1IoStatus=0U)
#define set_bIgnInternalDataIGN1IoStatus(val)         		(IGN_u16InternalDataIGN1IoStatus=(val))

#define get_bIgnInternalDataIGN1Fb()      					(IGN_u16InternalDataIGN1Fb)
#define clr_bIgnInternalDataIGN1Fb()         				(IGN_u16InternalDataIGN1Fb=0U)
#define set_bIgnInternalDataIGN1Fb(val)         				(IGN_u16InternalDataIGN1Fb=(val))
#endif

#define get_bIgnInternalDataIgnStable()      				(IGN_u16InternalDataIgnStable)
#define clr_bIgnInternalDataIgnStable()        				(IGN_u16InternalDataIgnStable=0U)
#define set_bIgnInternalDataIgnStable(val)         			(IGN_u16InternalDataIgnStable=(val))

#define get_bIgnInternalDataIgnStaticOn()      				(IGN_u16InternalDataIgnStaticOn)
#define clr_bIgnInternalDataIgnStaticOn()        				(IGN_u16InternalDataIgnStaticOn=0U)
#define set_bIgnInternalDataIgnStaticOn(val)         			(IGN_u16InternalDataIgnStaticOn=(val))

#define get_bIgnInternalDataSwVersion()      				(IGN_u16InternalDataSwVersion)
#define set_bIgnInternalDataSwVersion(val)         			(IGN_u16InternalDataSwVersion=(val))

#define get_bIgnInternalDataErrorCode()      				(IGN_u16InternalDataErrorCode)
#define clr_bIgnInternalDataErrorCode(val)        			(IGN_u16InternalDataErrorCode&=(val))
#define set_bIgnInternalDataErrorCode(val)         			(IGN_u16InternalDataErrorCode|=(val))

#if (IGN_RemoteUsed== 1)
#define get_bIgnInternalDataRemoteIoStatus()      			(IGN_u16InternalDataRemoteIoStatus)
#define clr_bIgnInternalDataRemoteIoStatus(val)         		(IGN_u16InternalDataRemoteIoStatus=0U)
#define set_bIgnInternalDataRemoteIoStatus(val)         		(IGN_u16InternalDataRemoteIoStatus=(val))
#endif

#if (IGN_KeyPosFromBus ==1 )
/*k15 status from can bus*/
#define K15_Unknow			0x00
#define K15_Off				0x01
#define K15_Acc				0x02
#define K15_Notapplicable	0x03
#define K15_IgOn_Ready		0x04
#define K15_Igon_Running	0x05
#define K15_IgAbnormal6		0x06
#define K15_IgAbnormal7		0x07
#define K15_Start_Crank		0x08
#define K15_IgAbnormal9		0x09
#define K15_IgAbnormala		0x0a
#define K15_IgAbnormalb		0x0b
#define K15_IgAbnormalc		0x0c
#define K15_IgAbnormald		0x0d
#define K15_IgAbnormale		0x0e
#define K15_Invalid			0x0f
#define K15_NeverRec		0xfe
#define K15_LostNode		0xff
#endif

/*key status be processed */
#define Sys_Unknow		0x00
#define Sys_Off			0x01
#define Sys_Acc			0x02
#define Sys_IgnOn		0x03
#define Sys_Crank		0x04
#define Sys_IdleStart		0x05
#define Sys_Err			0x06
/* crank status from can bus */
#define Crank_off		0x00
#define Crank_on			0x01



/*ign_ext  void IGN_vCheckCrankBus(void);
ign_ext  void IGN_vKeyJudge(void);
ign_ext  void IGN_vBusErrPro(void);*/

/*****************************************************************************
* End of check if informatIGNs are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: IGN.h
******************************************************************************/


