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
#ifndef IGN_IF_H
#define IGN_IF_H

#ifndef IGN_C
  #define ign_ext extern
#else
  #define ign_ext
#endif

#include "general.h"

#include "IGN_Type.h"

#include "IGN_cfg.h"

#include "ign_pte.h"

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

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

/*import*/
 ign_ext uint16 IGN_vImpIDAppCrankStatus(void);

ign_ext  uint16 IGN_vImpIDAppKeyPos(void);

 ign_ext uint16 IGN_vImpIDAppRemoteIo_Status(void);

 

/*export*/
 ign_ext  uint16  IGN_vExpIDIgnIGN2IoStatus(void);
 ign_ext uint16 IGN_vExpIDIgnRemoteIoStatus(void);
 ign_ext uint16   IGN_vExpIDAll(void);
 ign_ext uint16 IGN_u16GetValue(IGN_tenu16VarNum Num); 
 
 ign_ext  uint16 IGN_u16Array[IGN_nu16Max];

 /*other*/
  ign_ext uint16 IGN_vSetIDK15Config(void);

#if (IGN_Ign2_Used == 1)
 	ign_ext   uint16 IGN_vGetHwIgn2State(void);
 	ign_ext uint16 IGN_vIFK15FBDet(void);
#endif

#if (IGN_Ign1_Used == 1)
 	ign_ext   uint16 IGN_vGetHwIgn1State(void);
#endif

#if (IGN_RemoteUsed==1)
	 ign_ext   uint16 IGN_vGetRemoteIoState(void);
#endif

#if ((IGN_IgnBus_Used==1)||(IGN_KeyPosFromBus==1))
	 ign_ext    uint16 IGN_vGetIgnBusIoState(void);
#endif

#if (IGN_CrankFromBus==1)
	 ign_ext 	uint16 IGN_vIFCheckCrankBus(uint8 u8BusCrankStatus);
 #endif

#if (IGN_KeyPosFromBus==1)
 	ign_ext  uint16 IGN_vIFKeyJudge(uint8 u8BusKeyPos);
 	ign_ext  uint16 IGN_vIFBusErrPro(uint8 u8BusKeyPos);
	ign_ext  uint16 IGN_vIFBusLostDet(void);
#endif

#if (IGN_CheckIgnLostUsed ==1)
	ign_ext  uint16 IGN_vIFK15IOLostDet(void);
#endif

/*****************************************************************************
* End of check if informatIGNs are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: IGN_If.h
******************************************************************************/
