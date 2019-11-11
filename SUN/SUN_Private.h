/*******************************************************************************
| Module Name: Calculate the Blowout and Temp offset according to the solar
| File Name: SUN_Private.h
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
| Sui Yanchun                        Desay SV Automotive Co., Ltd
| Zhang Shuncong                     Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2013-04-09  1.00        Sui Yanchun       First implementation
| 2015-08-05  2.00        Zhang Shuncong    Add RTE ,Copyright and cfg
********************************************************************************/

#ifndef SUN_PRIVATE_H
#define SUN_PRIVATE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */

/* Foreign headerfiles */

#include "OAT.h"

/* Own headerfiles */
#include "SUN_Cfg.h" 


/*****************************************************************************
* EXPORT INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define helpful macros for easy data access and for a comfortable function use, if 
*   necessary.
* - define all macros for accessing the external module interfaces variables
* - define all macros which not need to be configed and changed for this module 
******************************************************************************/
#define SUN_SwVersion					(0x0101)


/**************************Internal Module Interface*******************************/




/**************************Extern Module Interface Without RTE Start*****************************/
#define SUN_u8GetOatValue_OAT_nu8Valid   	OAT_u16GetValue(OAT_nu16Valid)
#define SUN_u8GetSysValue_SYS_nFlag1s       SYS_u8GetValue(SYS_nFlag1000MS_BG)

#define SUN_u16GetOatValue_OAT_nu16OatValue OAT_u16GetValue(OAT_nu16Value)

//#define SUN_u32GetCcpValue_CCP_nu32CtrWord  False
/**************************Extern Module Interface Without RTE End*****************************/


/**************************Internal Module Parameter*******************************/
#define SUN_u8FastDecrement		(uint8)SUN_nFastFallSpeed	
#define SUN_u8FastIncrement     (uint8)SUN_nFastRiseSpeed     

#define SUN_u8SlowDecrement		(uint8)SUN_nSlowFallSpeed	
#define SUN_u8SlowIncrement     (uint8)SUN_nSlowRiseSpeed 

#define SUN_u8OffsetStep		(uint8)(2U)

#define SUN_nCanValueErrorFromOn   (0xFFFF)
#define SUN_nCanValueMax   (0x00FE)

#define SUN_nMaxValue   	                    (uint16)(1600U)    /* 1600 w*/
#define SUN_nMinValue                           (uint16)(0U)    /* 0 w*/

#define SUN_nMaxTempOffset   	                (uint16)(64*10+640)    /* 64 deg*/
#define SUN_nMinTempOffset                      (uint16)(0U)    /* -64 deg*/

#define SUN_nMaxBlowerOffset   	                (uint16)(10*100+1000)    /*10V*/
#define SUN_nMinBlowerOffset                    (uint16)(0U)    /* -10V*/

#define SUN_RangeCheck(input,minvalue,maxvalue)	\
	if((input)>=(maxvalue))\
		(input)=(maxvalue);\
	else if((input)<=(minvalue))\
		(input)=(minvalue)

#define SUN_nSysTimeCont1s                           (10u)              /* 100ms*10=1s*/
#define SUN_nDefaultTempOffset			(uint16)(640u)    /*0 deg*/
#define SUN_nDefaultBlowerOffset		(uint16)(1000u)	/*0 V*/
#define SUN_nDefaultValue               (uint16)(0U)    /* 0 w*/
#define SUN_SensorShortToPowAD		    (uint16)(1000U) /*4.90V*/
#define SUN_SensorShortToGndAD		    (uint16)(20U) /*0.1V*/
#define SUN_nSensorDefaultAdValue        (0x0398U)   /* 0 w */
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif         
/*****************************************************************************
* EOF: SUN_Private.h
******************************************************************************/

