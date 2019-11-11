/*******************************************************************************
| Module Name: KEY capture and debouncing  
| File Name: KEY_CFG.c
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
|   Liu Longxi                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2019.4.15         0100      Liu Longxi        module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/

/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/

#define Force_CFG

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/

#include "Force_Type.h"
#include "Force.h"
#include "CCP_CFG.h"
#include "touchkey.h"
/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants and macros to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/
//wuyijun
//uint8 Force_key_Threshold=0; 
uint8 u8ForceKeyPressed;
  
  
void Force_Threshold_set_L1(uint32 parameter) //压力的阈值设置
{
Sensor_stCfg[1].u16Sensorthreshold=parameter;     

}
void Force_Threshold_set_L2(uint32 parameter) //压力的阈值设置
{
Sensor_stCfg[2].u16Sensorthreshold=parameter;     

}
void Force_Threshold_set_L3(uint32 parameter) //压力的阈值设置
{
Sensor_stCfg[3].u16Sensorthreshold=parameter;     

}
void Force_Threshold_set_L4(uint32 parameter) //压力的阈值设置
{
Sensor_stCfg[4].u16Sensorthreshold=parameter;     

}
void Force_Threshold_set_L5(uint32 parameter) //压力的阈值设置
{
Sensor_stCfg[5].u16Sensorthreshold=parameter;     

}
void Force_Threshold_set_L6(uint32 parameter) //压力的阈值设置
{
Sensor_stCfg[6].u16Sensorthreshold=parameter;     

}
void Force_Threshold_set_L7(uint32 parameter) //压力的阈值设置
{
Sensor_stCfg[7].u16Sensorthreshold=parameter;     

}
void Force_Threshold_set_L8(uint32 parameter) //压力的阈值设置
{
Sensor_stCfg[8].u16Sensorthreshold=parameter;     

}
void Force_Threshold_set_L9(uint32 parameter) //压力的阈值设置
{
Sensor_stCfg[9].u16Sensorthreshold=parameter;     

}

FORCE_tstSensorCfg Sensor_stCfg[Force_KeyNum]=
{\
  
  	/*KeyID,   SensorCurrStatus,   Sensorthreshold,    SensorValib,  */ \
  	{KEY_nu8Pad12,  Sensor_enPrePress, 20000,False},\
	{KEY_nu8Pad1,  Sensor_enPrePress, 28,False},\
	{KEY_nu8Pad2, Sensor_enPrePress, 28,False},\
	{KEY_nu8Pad3, Sensor_enPrePress, 28,False},\
	{KEY_nu8Pad4,  Sensor_enPrePress, 28,False},\
	{KEY_nu8Pad5,  Sensor_enPrePress,28,False},\
	{KEY_nu8Pad6,  Sensor_enPrePress, 28,False},\
	{KEY_nu8Pad7,  Sensor_enPrePress, 17,False},\
	{KEY_nu8Pad8, Sensor_enPrePress, 17,False},\
	{KEY_nu8Pad9, Sensor_enPrePress, 17,False},\
	{KEY_nu8Pad10,  Sensor_enPrePress, 28,False},\
	{KEY_nu8Pad11,  Sensor_enPrePress, 1111,False},\
	
};






