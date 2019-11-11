/*******************************************************************************
| Module Name: Calculate the Blowout and Temp offset according to the VELocity
| File Name: VEL_Private.h
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
| 2015-08-06  2.00        Zhang Shuncong    Add RTE ,Copyright and cfg
| 2016-09-21  0100        Li Jiaye          interface updated
********************************************************************************/
#ifndef VEL_PRIVATE_H
#define VEL_PRIVATE_H

/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Own headerfiles */
#include "VEL_Cfg.h" 
/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */


/*******************************************************************************
* EXPORT INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define helpful macros for easy data access and for a comfortable function use, if 
*   necessary.
* - define all macros for accessing the external module interfaces variables
* - define all macros which not need to be configed and changed for this module 
******************************************************************************/

#define VEL_SwVersion					(0x0100)


/***************************No Config Parameter********************************/


/**************************Internal Module Parameter*******************************/
#define VEL_u8FastDecrement		(uint8)VEL_nFastFallSpeed	
#define VEL_u8FastIncrement     (uint8)VEL_nFastRiseSpeed     

#define VEL_u8SlowDecrement		(uint8)VEL_nSlowFallSpeed	
#define VEL_u8SlowIncrement     (uint8)VEL_nSlowRiseSpeed 

#define VEL_u8OffsetStep		(uint8)(2U)

#define VEL_nMaxValue   	                (uint16)(255U)    /* 255 km/h*/
#define VEL_nMinValue                       (uint16)(0U)    /* 0 km/h*/

#define VEL_nMaxTempOffset   	                (uint16)(64*10+640)    /* 64 deg*/
#define VEL_nMinTempOffset                      (uint16)(0U)    /* -64 deg*/

#define VEL_nMaxBlowerOffset   	                (uint16)(10*100+1000)    /*10V*/
#define VEL_nMinBlowerOffset                    (uint16)(0U)    /* -10V*/

#define VEL_RangeCheck(input,minvalue,maxvalue)	\
	if((input)>=(maxvalue))\
		(input)=(maxvalue);\
	else if((input)<=(minvalue))\
		(input)=(minvalue)

#define VEL_nSwVersion					(0x02u)
#define VEL_nSysTimeCont1s                        (10U)               /* 100ms*10=1s*/
#define VEL_nDefaultTempOffset			(uint16)(640u)    /*0 deg*/
#define VEL_nDefaultBlowerOffset		(uint16)(1000u)	/*0 V*/
#define VEL_nDefaultValue               (uint16)(0U)    /* 0 km/h*/

#define VEL_nu8SignalInvaidTime         (uint8)(10U)    /*100ms * 10 = 1s*/
/*******************************************************************************
* End of check if informations are already included
*******************************************************************************/
#endif                                  

/*******************************************************************************
* EOF: VEL_Private.h
*******************************************************************************/


