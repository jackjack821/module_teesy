/*******************************************************************************
| Module Name: start stop Function module(Idle engine stop )
| File Name: EVAP_Type.h
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
| 2015-10-15    1.0  Luo Xindian		 frist created,for general start stop function 
| 2016-2-18      1.1  Luo Xindian		Modified for KC-2
********************************************************************************/

#ifndef EVAP_TYPE_H
#define EVAP_TYPE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */
#include "General.h"
#include "EVAP_Cfg.h"
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

/*this is for uint16 type variables*/
typedef enum EVAP_enu16VarNumbers
{
	EVAP_nu16SensorAdValue=0, /*sensor ad value*/
	EVAP_nu16ResultTemp,/* Raw evap temp*/
	EVAP_nu16AcValue,/*use for AC control*/
	#if (EVAP_nMacEvapTempCfg == True)
	EVAP_nu16MacValue,/*used for MAC*/
	#endif
	#if (EVAP_nDynOffsCfg ==True)
	EVAP_nu16DynOffset,    /*dyn offset for fast real evap temperature*/
	#endif
	EVAP_nu16ErrorCode,
	EVAP_nu16RawValue,
	EVAP_nu16Max                     
}EVAP_tenu16VarNumber;

/*this is for uint8 type variables*/
typedef enum EVAP_enu8VarNumbers
{   
	EVAP_nu8Valid=0,
	EVAP_nu8SwVersion,
	EVAP_nu8SensorFailsafe,
	EVAP_nu8Max                     
}EVAP_tenu8VarNumber;
/*this is for uint8 type variables*/


typedef enum Evap_enSensorStates
{
	Evap_nNormal = 0,
	Evap_nOpenCircuit,
	Evap_nShortCircuit,
	Evap_nError
} Evap_tenSensorStates;

/* Indicate need to init the sensor parameter */
typedef enum 
{
	biColdBoot = 0, /* Need to init the sensor parameter */
	biHotBoot
}tenEVAPSensorState;

/* The SensorFilter Parameters: all the datas are constant  */
typedef struct
{
	uint16 *au16Raw; /* The Sensor Constant Table X */
     	uint16 *au16Result; /* The Sensor Constant Table Y */
    	uint16 u16MinLimitValue; /* The Min limit value of the valid range*/
     	uint16 u16MaxLimitValue; /* The Max limit value of the valid range */
     	uint16 u16SensorDefaultValue; /* Will be used when AD over the valid range  */
     	uint8 u8ErrorCountTimeout; /* For using to declare a sensor is faulty  */ 
     	uint8 u8FilterParameter; /* The filter level:0-7  */
     	uint8 u8Length; /* The length of the Sensor Constant Table  */
}tstEVAPFilterConstantType;

/* The SensorFilter Parameters: all the datas will be changed  */
typedef struct
{
	uint32 u32InterimValue;/* For store the higher-resulution values for first order filters */
 	uint16 u16SensorAD;/* The sensor AD value */
 	uint16 u16SensorValue;/* The filter sensor value for use  */
 	uint8 u8ErrorCountL;/* For using to count the time of sensor error  */ 
	uint8 u8ErrorCountH;
 	uint8 u8SensorErrorFlag;/* Indicate the sensor is in error state  */
 	tenEVAPSensorState u8InitFlag;/* Is used to init the SensorValue  */
}tstEVAPFilterVariableType;

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef RFA_TYPE_H */
/*****************************************************************************
* EOF: RFA_Type.h
******************************************************************************/

