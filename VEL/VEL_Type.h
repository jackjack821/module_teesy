/*******************************************************************************
| Module Name: Calculate the Blowout and Temp offset according to the velocity
| File Name: VEL_Type.h
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
#ifndef VEL_TYPE_H
#define VEL_TYPE_H


/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */


/*****************************************************************************
* DEFINE DATA TYPE INTERNAL
*
* In this section
* - define all the private data types of this module.
******************************************************************************/


/*Define filter type*/
typedef enum VEL_enFilter
{
    VEL_nFilterFast = 0,
    VEL_nFilterSlow,
    VEL_nFilterMid, /*for Oatvalue, rise is slow, fall is fast*/
    VEL_nFilterMax
}VEL_tenFilter;

typedef struct
{
	uint8 CcpCommandFlag;
	uint8 CcpCommand;
	uint16 CcpContronData;
}tstVelCcpContronType;

/*Ccp control*/
typedef enum
{
	VEL_nSetVelValue,
	VEL_nCcpForceMax
}CcpControl_Vel;


/******************************************************
*
*function interface type define
*
**/
 typedef enum
 {
    VEL_nInvalid=0u,
    VEL_nValid,
    VEL_nDefault,
    VEL_nLastValue
 }VEL_tenValueSts;

typedef struct
{
    uint8  u8VelocityInvalidFlag;/*1:velocity invalid;0:velocity valid*/
    uint16 u16VeIocityValue;/*1bit:km/h*/ 
}Vel_tstInputValueProcessIn;
typedef struct
{
    uint16 u16VeIocityValue;/*1bit:km/h*/ 
}Vel_tstInputValueProcessOut;

typedef struct
{
   uint16 u16VeIocityValue;/*1bit:km/h*/  
}Vel_tstDampingIn;
typedef struct
{
   uint16 u16Velocity;/*1bit:km/h*/  
   uint16 u16RfaVelValue;/*1bit:km/h*/  
   uint16 u16OatVelValue;/*1bit:km/h*/  
}Vel_tstDampingOut;

typedef struct
{
    uint16 u16OatValue;
    uint16 u16Velocity;
}Vel_tstCalOatTempOffsetIn;

typedef struct
{
    uint16 u16OatValue;
    uint16 u16Velocity;
}Vel_tstCalOatBlowerOffsetIn;

typedef struct
{
    uint8  u8ModuleValid;
    uint16 u16Velocity;/*1bit:km/h*/  
    uint16 u16RfaVelValue;/*1bit:km/h*/  
    uint16 u16OatVelValue;/*1bit:km/h*/  
    uint16 u16TempOffset;
    uint16 u16BlowerOffset;
    uint16 u16ErrorCode;
}Vel_tstMainOut;


#endif                                  /* ifndef ACCC_TYPE_H*/

/*******************************************************************************
* EOF: VEL_Type.h
*******************************************************************************/

