/*******************************************************************************
| Module Name: Calculate the Blowout and Temp offset according to the solar
| File Name: SUN_Type.h
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

#ifndef SUN_TYPE_H
#define SUN_TYPE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */


/* Foreign headerfiles */


/* Own headerfiles */


/*****************************************************************************
* DEFINE DATA TYPE INTERNAL
*
* In this section
* - define all the private data types of this module.
******************************************************************************/

//#define SUN_UseRTE

//#define CANSensor

#define SUN_OpenInterfaces_Cfg   (Yes)  /* Yes is to open Getvalue and GetBuffer interfaces*/

#define SUN_nSensorNum       (2)  /* number of Zones (i.e. Actuators). e.g. 2 is dual zone */

#define SUN_nUseMaxSolar   (True) /* only for dual solar sensor*/


/*Define number of solar sensor*/
typedef enum SUN_enZonesNum
{
    SUN_nZonesLeft = 0,
    SUN_nZonesRight,
    SUN_nZonesMax
}SUN_tenZonesNum;

/*Define filter type*/
typedef enum SUN_enFilter
{
    SUN_nFilterFast = 0,
    SUN_nFilterSlow,
    SUN_nFilterMax
}SUN_tenFilter;

 /*this is for SUN_nu8State variables, 1 bit represents one error*/
typedef enum SUN_enStates
{
	SUN_nOutputInvalid = 0x01,       	 /*data overflow during calculating*/	
	SUN_nGetOatInvalid = 0x02,           /*SUN_biValid is false*/
}SUN_tenState;


typedef struct
{
	uint8 CcpCommandFlag;
	uint8 CcpCommand;
	uint16 CcpContronData;
}tstSunCcpContronType;


/*Ccp control*/
typedef enum
{
	SUN_nSetSunLoad=0,
	SUN_nSetSunSensorFbAd,
	SUN_nCcpForceMax
}CcpControl_Sun;

 typedef enum
 {
    SUN_nInvalid=0u,
    SUN_nValid,
    SUN_nDefault,
    SUN_nLastValue
 }SUN_tenValueSts;


typedef struct
{
    uint8  u8SolarRawValueDrSts;
    uint16 u16SolarRawValueDr;
    uint8 u8SolarRawValuePsSts;
    uint16 u16SolarRawValuePs;
}Sun_tstInputValueProcessIn;
typedef struct
{
    uint16 u16SolarRawValueDr;
    uint16 u16SolarRawValuePs;
}Sun_tstInputValueProcessOut;

typedef struct
{
    uint16 u16SolarRawValueDr;
    uint16 u16SolarRawValuePs;
}Sun_tstDampingIn;
typedef struct
{
    uint16 u16FilterSolar;
    uint16 u16SolarValueDr;
    uint16 u16SolarValuePs;
}Sun_tstDampingOut;

typedef struct
{
    uint8 u8Zone;
    uint16 u16OATvalue;
    uint16 u16SolarValueDr;
    uint16 u16SolarValuePs;
}Sun_tstCalOatTempOffsetIn;

typedef struct
{
    uint16 u16OATvalue;
    uint16 u16SolarValue;
}Sun_tstCalOatBlowerOffsetIn;

typedef struct
{
    uint8 u8ModuleValid;
    uint16 u16RawSolarValueDrAD;
    uint16 u16RawSolarValuePsAD;
    uint16 u16RawSolarValueDr;
    uint16 u16RawSolarValuePs;
    uint16 u16SolarValueDr;
    uint16 u16SolarValuePs;
    uint16 u16SolarValueFilter;
    uint16 u16TempOffsetDr;
    uint16 u16TempOffsetPs;
    uint16 u16BlowerOffset;
    uint16 u16ErrorCode;
}Sun_tstMainOut;
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef SUN_TYPE_H */
/*****************************************************************************
* EOF: SUN_Type.h
******************************************************************************/
