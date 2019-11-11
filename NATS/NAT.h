/*******************************************************************************
| Module Name:  Non-Aspirated Temperature
| File Name: NAT.c
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
| 2016-8-17    1.0  Luo Xindian		 frist created,for basic code 
********************************************************************************/

#ifndef NAT1C1_H
#define	NAT1C1_H

#ifndef NAT1C1
  #define ext extern
#else
  #define ext
#endif


/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
//#include <sysbits.h>

/* Foreign headerfiles */
#include "NAT_Type.h"
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

	ext void NAT_vReset(void);		                  /* Reset Container */
	ext void NAT_vInit(void);		          /* StandbyActive Container */
	ext void NAT_vDeinit(void);	             /* ActiveStandby Container */
	ext void NAT_vMain(void);		                     /* On Container */
	ext void NAT_vActive(void);
	
	ext uint8 NAT_u8GetValue( NAT_tenu8VarNumber enIndex );
	ext uint16 NAT_u16GetValue( NAT_tenu16VarNumber enIndex );

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#undef	ext

#endif                                  /* ifndef */


/*****************************************************************************
* EOF:
******************************************************************************/
