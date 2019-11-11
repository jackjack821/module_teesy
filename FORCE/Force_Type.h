/*******************************************************************************
| Module Name: KEY capture and debouncing Private
| File Name: KEY_Private.h
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
|  Liu Longxi                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2019.4.15         0100      Liu Longxi        module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/


#ifndef FORCE_Type_H
#define FORCE_Type_H
#include "General.h"
#define Force_KeyNum   12
#define Force_PosFollowSpeed   100
#define Force_PosFollowStep   1
#define Force_NegFollowSpeed   100
#define Force_NegFollowStep   1
#define Force_SensorThresholdMax   200
#define Force_SensorThresholdMin   3
#define Force_InitialTimes   30/**300ms**/     




void Force_Threshold_set_L1(uint32 parameter);
void Force_Threshold_set_L2(uint32 parameter);
void Force_Threshold_set_L3(uint32 parameter);
void Force_Threshold_set_L4(uint32 parameter);
void Force_Threshold_set_L5(uint32 parameter);
void Force_Threshold_set_L6(uint32 parameter);
void Force_Threshold_set_L7(uint32 parameter);
void Force_Threshold_set_L8(uint32 parameter);
void Force_Threshold_set_L9(uint32 parameter);



/*****************************************************************************
*Enum define
******************************************************************************/
typedef enum 
{
	Force_nu16RawAd = 0,
	Force_nu16RefAd,
	Force_nu16Max
}Force_tu16enVarNumber;

 typedef enum
 {
	KEY_nu8Pad1 = 0,
	KEY_nu8Pad2,
	KEY_nu8Pad3,
	KEY_nu8Pad4,
	KEY_nu8Pad5,	
	KEY_nu8Pad6,
	KEY_nu8Pad7,
	KEY_nu8Pad8,
	KEY_nu8Pad9,
	KEY_nu8Pad10,
	KEY_nu8Pad11,
	KEY_nu8Pad12,
	KEY_nu8PadMax
 }KEY_tenu8PadVarNum;

typedef enum
{
	Sensor_enPrePress,
	Sensor_enLightPressed,
	Sensor_enHeavyPressed,
	Sensor_enReleased
}Force_tenForceSensorStatus;

/*****************************************************************************
*Struct define
******************************************************************************/

typedef struct 
{
    uint8   u8KeyId;
    Force_tenForceSensorStatus 	enSensorCurrStatus;
    uint16 		u16Sensorthreshold;
    uint8 		u8SensorValib;
}FORCE_tstSensorCfg;


#endif

