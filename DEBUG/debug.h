/*******************************************************************************
| Module Name: Debug capture and debouncing  
| File Name: Debug.h
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
|  Liu Longxi                         Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2019.7.12         0100      wuyijun       module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/

#ifndef Debug_H
#define Debug_H

/* System-headerfiles */
#include "General.h"
#include "Debug_Type.h"
#include "Rte_internal.h"
#include "DIM.h"
#include "DCM.h"
#include "force_type.h"
/* we need headerfiles */
#include "IIC.h"
#include "IIC_Cfg.h" 
#include "Can_par.h" 



void Debug_vInit (void);
void Debug_Do_Nothing(uint32 parameter);
void Debug_Touch_data_L(void);
void Debug_Touch_data_R(void);
void Debug_vRecive_data(void);

void press_key_status_control_enable(uint32 parameter );
void press_key_status_control_close(uint32 parameter);

 void Debug_vMain (void);
static uint8 mcu_option_max[8]={4,4,4,4,4,4};

static void (*CANDebug_MCU[6][5]) (uint32 parameter) = {
{ Debug_Do_Nothing, Debug_Do_Nothing ,Debug_Do_Nothing  , Debug_Do_Nothing },   //do nothing

	
{ L1_Duty_light,L2_Duty_light  , L3_Duty_light ,L4_Duty_light  },     //MCU _light
	
{ DCM_motor_duty_set,MotorGSID_duty_set ,DCM_MotorVibrateCycle_set  , DCM_MCU_u8motortime_set },  //MCU_motor

{ Force_Threshold_set_L1, Force_Threshold_set_L2 , Force_Threshold_set_L3 , Force_Threshold_set_L4, Force_Threshold_set_L5 },             //MCU_press_debug
{ Force_Threshold_set_L6, Force_Threshold_set_L7 , Force_Threshold_set_L8 , Force_Threshold_set_L9, Debug_Do_Nothing },             //MCU_press_debug


{ press_key_status_control_close, press_key_status_control_enable , Debug_Do_Nothing , Debug_Do_Nothing },             //个别按键关闭/激活

};

struct Canoe_IC_Debug
{
      	uint8 ic_choice;       //  1  MCU       2touch_L        3touch_R
	uint8 debug_cmd;       //
	uint8 debug_option;
	uint32 debug_parameter;	
}Canoe_IC_Debug;





#endif                                

