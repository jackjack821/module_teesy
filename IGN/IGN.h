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
#ifndef IGN_H
#define IGN_H

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


#include "IGN_If.h"  

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
//ext uint8 IGN_u8KL15State;
//ext uint8 IGN_u8SleepCnt;




/*****************************************************************************
* EXPORT INTERFACE FUNCTIGN PROTOTYPES
*
* In this sectIGN declare
* - all system global functIGN prototypes of your module. This is a copy of the functIGN 
*   definitIGNs without the header template.
******************************************************************************/




 ign_ext void IGN_vWakeUp(void);
 ign_ext void IGN_vReset(void);
 ign_ext void IGN_vMain(void);
 ign_ext  void IGN_ifIgn2ExternInterrupt(void);
 ign_ext void IGN_ifRemoteExternInterrupt(void);

/*-----------------unused --------------------*/
 ign_ext void IGN_vInit(void);
 ign_ext void IGN_vDeinit(void);

#if (IGN_KeyPosFromBus==1)
ign_ext uint8 IGN_u8BusKeyPos;
#endif

#if (IGN_CrankFromBus==1)
//uint8 uRTCrankBus;
ign_ext  uint8 IGN_biIgnitionBusCrankResult;
#endif

 ign_ext uint16 IGN_u16InternalDataErrorCode;	/*maybe record error in IF */

/*****************************************************************************
* End of check if informatIGNs are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
* EOF: IGN.h
******************************************************************************/


