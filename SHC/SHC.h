/*******************************************************************************
| Module Name: Seat Heat Control
| File Name: SHC.c
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
| 10/21/2014    1.0  Luo Xindian		  this module for new seat heating modules development
********************************************************************************/

#ifndef SHC_H
#define SHC_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* system-headerfiles*/
#include "General.h"
#include "SHC_type.h"

/* foreign headerfiles*/


/* Own headerfiles */

/**************************** .BLOCK_COMMENT_BEGIN ***************************
* EXPORT INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define helpful macros for easy data access and for a comfortable function
*   use, if necessary
* - define all global define-constants of your module
* - define all global type definitions of your module
* - declare all system global ROM-constants
* - declare all system global variables of your module
***************************** .BLOCK_COMMENT_END *****************************/



/**************************** .BLOCK_COMMENT_BEGIN ***************************
* EXPORT INTERFACE FUNCTION PROTOTYPES
*
* In this section declare
* - all system global function prototypes of your module. This is a copy of
*   the function definitions without the header template.
***************************** .BLOCK_COMMENT_END *****************************/
/* Initialisation */
 extern  void SHC_vReset(void);               /* called from reset comtainer      */

/* State Transitions */
 extern  void SHC_vDeinit(void);       /* called from ActiveStandby        */
 extern  void SHC_vInit( void);      /* called from StandbyActive        */

/* State Containers */
 extern  void SHC_vActive(void);              /* active container (100mS)         */

 extern void SHC_vGetPwmOuputFb1ms(void);/* get PWM output feedback each 1ms*/
 extern  void SHC_vMain(void);                /* on container (100mS)             */

 extern uint8 SHC_u8GetValue(SHC_tenu8VarNum enIndex);
 extern Std_ReturnType SHC_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);

#endif 

/*****************************************************************************
* EOF: 
*****************************************************************************/

