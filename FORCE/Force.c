
/*******************************************************************************
| Module Name: KEY capture and debouncing  
| File Name: KEY.c
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
|2019.4.15         0100      Liu Longxi        module template update. 
| sss
| 
****************************** .FILE_HEADER_END *********************************/
#define Force                         /* name of the module                */

/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */	
#include "ALG.h"
#include "debug.h"

/* Own headerfiles */

#include "Force.h"      
#include "Force_Type.h"
#include "Rte_internal.h"
static uint8  ForceSensor_au8Array[Force_KeyNum];
uint16 Force_u16ForceSensorADValue;
static uint16 u16ForceSeneorADValue;
static int16 i16ForceSeneorADReferenceValue;
static  int16 i16ForceSeneorADDetalValue;
static uint16 u16FollowTimer;
static uint16 u16InitialCount;
static uint16 Force_au16Array[Force_nu16Max];
  static  void Demo_Vtest(void);
//extern uint8 Force_key_Threshold;
extern uint8 u8ForceKeyPressed;
extern    uint8 TOUCHKEY_u8TouchInfBuff_L[15];    //如果坐标没有报点说明这是稳态值
  uint16 u16Force_Value_Hold=20;
  extern  uint8 u8button_value;   //触摸片的按键值
 uint8  u8Button_Status_Flag=0;
/***********************************************************************************
 Function      : void KEY_vReset (void)                                     
 Description   : Reset container function of KEY                   
 Takes         : Nothing
 Return Value  : Nothing                                                     
************************************************************************************/
void Force_vReset (void)
{
	uint8 j;
	u16InitialCount=0;
	u16ForceSeneorADValue=0;
	i16ForceSeneorADReferenceValue=0;
	i16ForceSeneorADDetalValue=0;
	Force_u16ForceSensorADValue=0;
	u16FollowTimer=0;
	for(j=0;j<12;j++)
	{		
	ForceSensor_au8Array[j]=0;

	}
}


/***********************************************************************************
 Function      : void KEY_vInit(void)                                       
 Description   : initialize function of KEY                    
 Takes         : Nothing
 Return Value  : Nothing                                                
************************************************************************************/
void Force_vInit (void)
{	
 
}


/***********************************************************************************
 Function      : void KEY_vDeinit(void)                                     
 Description   : De-init function of KEY              
 Takes         : Nothing
 Return Value  : Nothing                                                                                                
************************************************************************************/
void Force_vDeinit (void)
{
  
}

/***********************************************************************************
 Function      : void KEY_vActive(void)                              
 Description   : Acive function of KEY 
 Takes         : Nothing
 Return Value  : Nothing                                                                                          
************************************************************************************/
void Force_vActive(void)
{

}
static void Demo_Vtest(void)
{

if ((u8button_value==1)&&(u8ForceKeyPressed==1))
{
CANDebug_MCU[1][0](0);
CANDebug_MCU[1][2](0);
CANDebug_MCU[5][0](2);
CANDebug_MCU[5][0](3);
CANDebug_MCU[5][0](5);
CANDebug_MCU[5][0](6);
}
if ((u8button_value==4)&&(u8ForceKeyPressed==1))
{
CANDebug_MCU[1][0](80);
CANDebug_MCU[1][2](80);
CANDebug_MCU[5][1](2);
CANDebug_MCU[5][1](3);
CANDebug_MCU[5][1](5);
CANDebug_MCU[5][1](6);
}

}


/*****************************************************************************
 Function      : KEY_vMain()	                                       
 Description   : Main container function of KEY
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void Force_vMain (void)
{
    
   uint8 j=0;
   uint16 u16SensorDetectionAD;
   
   u16SensorDetectionAD =Force_u16ForceSensorADProcess();  //压力值
   
if((TOUCHKEY_u8TouchInfBuff_L[15]&TOUCHKEY_u8TouchInfBuff_L[17])==0xff)
{  
  u16Force_Value_Hold =u16SensorDetectionAD;   //实际的压力值 稳态值
}
//u8button_value


	if (u16SensorDetectionAD>=(Sensor_stCfg[u8button_value].u16Sensorthreshold+u16Force_Value_Hold))
      	{
      	u8ForceKeyPressed=1;
	ForceSensor_au8Array[u8button_value]=1;    //每一个按键的状态
	
      	}
	  if (u16SensorDetectionAD<(Sensor_stCfg[u8button_value].u16Sensorthreshold+u16Force_Value_Hold-15))
	 {
        u8ForceKeyPressed=0;
	 ForceSensor_au8Array[u8button_value]=0;
		
	  }
	
if((TOUCHKEY_u8TouchInfBuff_L[14]==1)&&(u8ForceKeyPressed==1))
	    {
	     u8Button_Status_Flag=1;
	    }
	if(u8ForceKeyPressed==0)
	    {
	    u8Button_Status_Flag=0;
		}



     Demo_Vtest();
#if 0	  
   Force_au16Array[Force_nu16RawAd] = u16SensorDetectionAD;
   Force_au16Array[Force_nu16RefAd] = (uint16)i16ForceSeneorADReferenceValue;
	if(u16InitialCount>Force_InitialTimes)
	{
	  	 u16InitialCount=(Force_InitialTimes+1);
		
		 i16ForceSeneorADDetalValue=(u16SensorDetectionAD-i16ForceSeneorADReferenceValue);
		 if(i16ForceSeneorADDetalValue>=Force_SensorThresholdMin)
		 {
			  for(j=0;j<Force_KeyNum;j++)
			   {
				   if(i16ForceSeneorADDetalValue>Sensor_stCfg[j].u16Sensorthreshold)
				   {
					ForceSensor_au8Array[j]=1;    //每一个按键的状态
				   }
				   else
				   {
	                          ForceSensor_au8Array[j]=0;
				   }
			   }
		 }
		 else
		 {
		 	  for(j=0;j<Force_KeyNum;j++)
			   {
				  
	                    ForceSensor_au8Array[j]=0;
			   }
		 	
		 	if(i16ForceSeneorADDetalValue>0)/*****positive follow****/
		 	{
					u16FollowTimer++;
				 	if(u16FollowTimer>Force_PosFollowSpeed)
				 	{
						u16FollowTimer=0;
						i16ForceSeneorADReferenceValue=(i16ForceSeneorADReferenceValue+Force_PosFollowStep);
						
					}
					else
					{
						i16ForceSeneorADReferenceValue=i16ForceSeneorADReferenceValue;
					}
			}
			else if(i16ForceSeneorADDetalValue==0)
			{
				i16ForceSeneorADReferenceValue=i16ForceSeneorADReferenceValue;
			}
			else if(i16ForceSeneorADDetalValue<0)/*****negetive follow****/
			{
					u16FollowTimer++;
				 	if(u16FollowTimer>Force_NegFollowSpeed)
				 	{
						u16FollowTimer=0;
						i16ForceSeneorADReferenceValue=(i16ForceSeneorADReferenceValue-Force_NegFollowStep);
						
					}
					else
					{
						i16ForceSeneorADReferenceValue=i16ForceSeneorADReferenceValue;
					}
			}
			else
			{

			}
		 
			
		 }
		
	}
	else
	{
		u16InitialCount++;
		i16ForceSeneorADReferenceValue=u16SensorDetectionAD;/****initial calibration*****/
	}
  
  #endif
  
}

/*============================================================================
*Function : uint32 Key_u32ForceADProcess(void)
*Description : max 32 keys
*takes : nothing
*return: nothing wuyijun
*/
uint16 Force_u16ForceSensorADProcess(void)
{
	uint16 u16ForceSensorADValue;
	uint16 Value;
	Rte_Call_IoHwAd_IoHwAd_ReadAd_FORCE_Read(&u16ForceSeneorADValue);
	u16ForceSensorADValue=u16ForceSeneorADValue;
	//统一压力1024
	TOUCHKEY_u8TouchInfBuff_L[22]=u16ForceSensorADValue;
       return u16ForceSensorADValue;
	
}

/*************************************************************************************************** 
  Function   : ForceSensor_u8GetValue      
   
  Description: supply variable for other modules.
                            
  Arguments  : None
  
  Returns    : variable other module want to get.
***************************************************************************************************/
uint8 ForceSensor_u8GetValue(KEY_tenu8PadVarNum Num)
{
    	uint8 u8ReturnValue;
	if(Num<Force_KeyNum)
	{
        	u8ReturnValue = ForceSensor_au8Array[Num];
	}
	else
	{
        	u8ReturnValue = ForceSensor_au8Array[Force_KeyNum-1];
	}
    	return u8ReturnValue;
}

uint16 Force_u16GetValue( Force_tu16enVarNumber enIndex )
{
    uint16 u16ReturnValue;
	if ( enIndex < Force_nu16Max )
	{
		u16ReturnValue = Force_au16Array[enIndex];
	}
	else
	{
		u16ReturnValue = Force_au16Array[Force_nu16Max-1];
	}
    return u16ReturnValue;
}



