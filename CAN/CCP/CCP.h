/*******************************************************************************
| Module Name: Climate Calibration Processing Module. 
| File Name: CCP.c
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
| Zhong bin                       Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date            Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
 13/8/2012        V1.1            Zhong Bin           Creation.
 16/12/2015       V1.2            Lin Tao             First release for J72L  

*****************************************************************************/

#ifndef CCP_H
#define CCP_H

#ifndef CCP_C
  #define ext extern
#else
  #define ext
#endif

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* system-headerfiles*/
#include "General.h"

/* foreign headerfiles*/


/* Own headerfiles */
#include "Ccp_def.h"        

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
/* the extern variable */

/** EXPORT INTERFACE FUNCTION PROTOTYPES                                    */
ext uint8 CCP_u8GetValue(CCP_tenu8VarNumber enIndex);
ext Bool CCP_boGetValue(CCP_tenbiVarNumber enIndex);

/* Reset container */
ext void CCP_vReset(void);              
/* State Containers */
ext void CCP_vMain(void);                /* on container (10mS) */
ext void CCP_vInit( void);			 /* called from ActiveOn */
ext void CCP_vDeinit( void);		/* called from ActiveStandby */

uint16 CCP_u16GetAdValue(uint8 u8Index);
/* Interrupt Service Routines */


/** End of check if informations are already included                       */
#undef ext
#endif                                                   /* ifndef CCP_H */

