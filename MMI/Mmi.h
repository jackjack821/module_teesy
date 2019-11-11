/*******************************************************************************
| Module Name: Mmi, Man machine interface
| File Name: Mmi.h
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
| Yang Tingyu                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2016-03-08  A1        Yang Tingyu         First implementation
| 

  ,-~~-.___. 
 / |  ' 	\ 
(  )		0 
 \_/-, ,----' 
	====		   // 
   /  \-'~;    /~~~(O)
  /  __/~|	 /		 |
=(	_____| (_________|

********************************************************************************/

/******************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef MMI_H
#define MMI_H
	

/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
#include "General.h"
/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */
#include "Rte_Type.h"
/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */
#include "Mmi_Type.h"


/*****************************************************************************
* EXPORT INTERFACE VARIABLE DEFINITIONS 
*
* In this section define
* - all variables will be accessed by other module.
******************************************************************************/


/*****************************************************************************
* EXPORT INTERFACE FUNCTION PROTOTYPES
*
* In this section declare
* - all system global function prototypes of your module. This is a copy of the function 
*   definitions without the header template.
******************************************************************************/

 void MMI_vReset(void);        /* Reset Container                   */
 void MMI_vInit (void);        /* StandbyActive Container           */
 void MMI_vDeinit(void);        /* ActiveStandby Container           */
 void MMI_vMain(void);        /* On Container                      */
  void MMI_vActive(void);        /* Active Container                      */
 uint8 MMI_u8GetValue(MMI_tenu8VarNum enIndex );
 uint16 MMI_u16GetValue(MMI_tenu16VarNum enIndex );
 void MMI_vDoDisplayMain(void);
 void MMI_vClrLeftShcKeyState(void);
 void MMI_vClrRightShcKeyState(void);
Std_ReturnType MMI_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord);
 void MMI_vTurnOnByPm25Exceed(void);
 void MMI_vTurnOffByIonFinish(void);

 void MMI_u16ClearKnobOrKeyOperationFlag( void );
 uint16 MMI_u16GetKnobOrKeyOperationFlag( void );
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef MMI_H*/

