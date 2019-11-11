/*******************************************************************************
| Module Name: Non-Aspirated Temperature type definition
| File Name: NAT_Type.h
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
| 2016-8-18    1.0  Luo Xindian		 frist created 
********************************************************************************/

#ifndef NAT_TYPE_H
#define NAT_TYPE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */
#include "General.h"
#include "NAT_Cfg.h"
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

/*this is for uint8 type variables*/
typedef enum NAT_enu8VarNumbers
{
	NAT_nu8Valid = 0,
	NAT_nu8Value,
	NAT_nu8SwVersion,
	NAT_nu8Max
}NAT_tenu8VarNumber;

/*this is for uint16 type variables*/
typedef enum NAT_enu16VarNumbers
{
	NAT_nu16Value = 0,
	NAT_nu16ErrorCode,
	NAT_nu16SurfaceTemp,
	NAT_nu16PcbTemp,
	NAT_nu16IRSunLoad,
	NAT_nu16DynOffset,
	NAT_nu16StaOffset,
	NAT_nu16TmlOffset,
	NAT_nu16RayOffset,
	NAT_nu16TempDiff,
	NAT_nu16Max                     
}NAT_tenu16VarNumber;

#if(NAT_nUseCCP ==True)

typedef enum
{
	NAT_nSetSurfaceTemp,
	NAT_nSetPcbTemp,
	NAT_nSetNatValue,
	NAT_nCcpForceMax
}CcpControl_NAT;
#endif

typedef struct NAT_stInputLists        
{
    uint8 u8IgnDelay;
    uint8 u8LowVoltage;
    uint8 u8HighVoltage;	
    uint8 u8Sys1000ms;
    uint16 u16OatValue;
    uint16 u16SurfaceAd;
   uint16 u16PcbAd;
   uint16 u16IrSolarAd;
}NAT_tstInputLists;


/*this is for uint8 type variables*/
/* Indicate need to init the sensor parameter */
typedef enum 
{
	NAT_nColdBoot = 0, /* Need to init the sensor parameter */
	NAT_nHotBoot
}tenNATSensorState;


/* The SensorFilter Parameters: all the datas are constant  */
typedef struct
{
	const uint16 *au16Raw; /* The Sensor Constant Table X */
     	const uint16 *au16Result; /* The Sensor Constant Table Y */
    	uint16 u16MinLimitValue; /* The Min limit value of the valid range*/
     	uint16 u16MaxLimitValue; /* The Max limit value of the valid range */
     	uint16 u16SensorDefaultValue; /* Will be used when AD over the valid range  */
     	uint8 u8ErrorCountTimeout; /* For using to declare a sensor is faulty  */ 
     	uint8 u8FilterParameter; /* The filter level:0-7  */
     	uint8 u8Length; /* The length of the Sensor Constant Table  */
}tstNATFilterConstantType;

/* The SensorFilter Parameters: all the datas will be changed  */
typedef struct
{
	uint32 u32InterimValue;/* For store the higher-resulution values for first order filters */
     	uint16 u16SensorAD;/* The sensor AD value */
     	uint16 u16SensorValue;/* The filter sensor value for use  */
     	uint8 u8ErrorCountL;/* For using to count the time of sensor error  */ 
	uint8 u8ErrorCountH;
     	uint8 u8SensorErrorFlag;/* Indicate the sensor is in error state  */
     	tenNATSensorState u8InitFlag;/* Is used to init the SensorValue  */
}tstNATFilterVariableType;


/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef NAT_TYPE_H */
/*****************************************************************************
* EOF: NAT_Type.h
******************************************************************************/

