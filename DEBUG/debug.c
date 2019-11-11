
/*******************************************************************************
| Module Name: Debug capture and debouncing  
| File Name: Debug.c
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
|   Liu Longxi                         Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
|2019.7.15         0100      wuyijun        module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/
#define Debug                         /* name of the module                */

/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */	



/* Own headerfiles */

#include "Debug.h"      
#include "Debug_Type.h"
#include "Rte_internal.h"

static uint8 TOUCHKEY_u8Debug[31]=0;
uint8  control_key_status_parameter=30;
extern uint8 u8button_value;
extern uint8 control_button_debug[10];
extern  uint8 u8ForceKeyPressed;
/***********************************************************************************
 Function      : void Debug_vReset (void)                                     
 Description   : Reset container function of Debug                   
 Takes         : Nothing
 Return Value  : Nothing                                                     
************************************************************************************/
void Debug_vReset (void)
{

}


/***********************************************************************************
 Function      : void Debug_vInit(void)                                       
 Description   : initialize function of Debug                    
 Takes         : Nothing
 Return Value  : Nothing                                                
************************************************************************************/
void Debug_vInit (void)
{	
 
}


/***********************************************************************************
 Function      : void Debug_vDeinit(void)                                     
 Description   : De-init function of Debug              
 Takes         : Nothing
 Return Value  : Nothing                                                                                                
************************************************************************************/
void Debug_vDeinit (void)
{
  
}

/***********************************************************************************
 Function      : void Debug_vActive(void)                              
 Description   : Acive function of Debug 
 Takes         : Nothing
 Return Value  : Nothing                                                                                          
************************************************************************************/
void Debug_vRecive_data(void)
{
//just test wuyijun
Canoe_IC_Debug.ic_choice=Canoe_IC_Debug_ic_choice;
Canoe_IC_Debug.debug_cmd=Canoe_IC_Debug_debug_cmd;
Canoe_IC_Debug.debug_option=Canoe_IC_Debug_debug_option;
Canoe_IC_Debug.debug_parameter=Canoe_IC_Debug_debug_parameter;

   //·ÀÖ¹Òç³ö
if (Canoe_IC_Debug.debug_cmd>6)  
	Canoe_IC_Debug.debug_cmd=0;

if (Canoe_IC_Debug.debug_option>6)
 Canoe_IC_Debug.debug_option=0;

}
void Debug_Touch_data_L(void)
{

TOUCHKEY_u8Debug[28]=Canoe_IC_Debug.debug_cmd;
TOUCHKEY_u8Debug[29]=Canoe_IC_Debug.debug_option;
TOUCHKEY_u8Debug[30]=Canoe_IC_Debug.debug_parameter;

Siic_SetSlaveAddress(Siic_Chn_0, 0x08);
Siic_u8SendBlock(Siic_Chn_0,0x00,30,&TOUCHKEY_u8Debug);
}
void Debug_Touch_data_R(void)
{

TOUCHKEY_u8Debug[28]=Canoe_IC_Debug.debug_cmd;
TOUCHKEY_u8Debug[29]=Canoe_IC_Debug.debug_option;
TOUCHKEY_u8Debug[30]=Canoe_IC_Debug.debug_parameter;
Siic_SetSlaveAddress(Siic_Chn_0, 0x09);
Siic_u8SendBlock(Siic_Chn_0,0x00,31,&TOUCHKEY_u8Debug);
}
/*============================================================================
*Function :  °´¼ü×´Ì¬¿ØÖÆ
*Description : max 32 Debugs
*takes : nothing
*return: nothing
*/

void press_key_status_control_enable(uint32 parameter )
{
if(parameter>10)
	parameter=9;
control_button_debug[parameter]=parameter;
}
void press_key_status_control_close(uint32 parameter)
{
if(parameter>10)
	parameter=9;
control_button_debug[parameter]=51;


}

/*****************************************************************************
 Function      : Debug_vMain()	                                       
 Description   : Main container function of Debug
 Takes         : Nothing
 Return Value  : Nothing
 //test wuyijun

Siic_SetSlaveAddress(Siic_Chn_0, 0x09);
Siic_u8SendBlock(Siic_Chn_0,0x00,31,&test);
*****************************************************************************/
void Debug_vMain (void)
{


Debug_vRecive_data();


switch(Canoe_IC_Debug.ic_choice)
	{
case 1:                               //MCU
CANDebug_MCU[Canoe_IC_Debug.debug_cmd][Canoe_IC_Debug.debug_option](Canoe_IC_Debug.debug_parameter); 
	break;
case 2:                              //touch_L
   Debug_Touch_data_L();
        break;
case 3:                            //touch_R
      Debug_Touch_data_R();
        break;
default:
	Debug_vInit;
	

     }


  
}



/*============================================================================
*Function : uint32 Debug_u32DebugADProcess(void)
*Description : max 32 Debugs
*takes : nothing
*return: nothing
*/
uint16 Debug_u16DebugSensorADProcess(void)
{

}

/*************************************************************************************************** 
  Function   : DebugSensor_u8GetValue      
   
  Description: supply variable for other modules.
                            
  Arguments  : None
  
  Returns    : variable other module want to get.
***************************************************************************************************/


uint16 Debug_u16GetValue( void )
{
   
}

void Debug_Do_Nothing(uint32 parameter)
{
    
}


