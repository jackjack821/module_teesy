/***************************************************************************************************
                                        Touch KEY PROCESS
  .File Name: TouchKey.c
  
  .Description: Thie file is used to process touch key events.

  --------------------------------------------------------------------------------------------------
  Version     Date            Author            Change

  --------------------------------------------------------------------------------------------------
  Rev 1.0     2017/11/06      Zhong Bin     	The first version      
  Rev 2.0     2018/11/22      Liu Longxi     	 version 2.0
***************************************************************************************************/    
#define TOUCHKEY_C                                   /*Name of the file*/

/***************************************************************************************************
                                        HEADER FILES
***************************************************************************************************/                                       

/* System-headerfiles */


/* Foreign headerfiles */


/* Own headerfiles */
#include "TouchKey.h"
#include "TouchKey_Cfg.h"
#include "TouchKey_Private.h"
#include "TouchKey_Type.h"
#include "TouchKey_Interface.h"
#include "General.h"
#include "IIC.h"
#include "IIC_Cfg.h" 
//#include "HAL_Gpio.h" 
#include "KEY_Interface.h"
#include "KEY.h" 
#include "Knob_Type.h" 
#include "Knob.h"   

#include "FRAME.h"

#include "Force.h" 
#include "Ccp_cfg.h"
#include "Debug.h"

/***************************************************************************************************
                                        LOCAL VARIABLES
***************************************************************************************************/
static uint32  TOUCHKEY_au32Array[TouchKeyNum];
static uint16  TOUCHKEY_au16Array[TOUCHKEY_nu16Max];
static uint8  TOUCHKEY_au8MainPageMode[MainPageNum];
static TOUCHKEY_tenMenuMode TouchKey_MianMenu_Mode=TOUCHKEY_nCCMode;

static TOUCHKEY_stPageAttribute TOUCHKEY_stMainPageManage[TOUCHKEY_nMAINPAGE_Max] = TOUCHKEY_nMainPageAttribute;
static TOUCHKEY_stPageAttribute TOUCHKEY_stSeatModePageManage[TOUCHKEY_nSeatModePAGE_Max] = TOUCHKEY_nSeatModePageAttribute;
static TOUCHKEY_stPageAttribute TOUCHKEY_stDriveModePageManage[TOUCHKEY_nDriveModePAGE_Max] = TOUCHKEY_nDriveModePageAttribute;

static TOUCHKEY_stPageAttribute TOUCHKEY_stCCModePageManage[TOUCHKEY_nu32CCModeMax] = TOUCHKEY_nCCModePageAttribute;


static TOUCHKEY_stPageAttribute TOUCHKEY_stBodyModePageManage[TOUCHKEY_nBodyModePAGE_Max] = TOUCHKEY_nBodyModePageAttribute;

static uint16 Touch_u16TestCnt=0;
static uint16 u16DelayTimeCounter = 0;
static uint16 u16_XPos = 0,u16_YPos = 0;
static uint8 TOUCHKEY_u8TouchInfBuff[TouchIicDataLen]=0;
static uint8 TOUCHKEY_u8TouchInfBuff_R[30]=0;
       uint8 TOUCHKEY_u8TouchInfBuff_L[30]=0;
extern boolean control_key_status;
extern uint8 control_key_status_parameter;
extern  uint8 u8ForceKeyPressed;
		uint8  u8button_value=0;
		uint8 u8Gsid_flag=0;
		uint8 control_button_debug[10]={0,1,2,3,4,5,6,7,8,9};
static uint8 u8WaitFlag=0;
static uint8 uRH850_8InterruptFlag=0;
TOUCHKEY_tenMoveDirection ActionMode;

/******************************
add by wuyijunm
flag : L or R
function:   
Provide starting data
*********************************/
static boolean turn=true;
static uint8 u8old=0;
static uint8 u8new=0;
  uint8 TOUCHKEY_u8DataArrayFE_Byte6;
/***************************************************************************************************
                                    LOCAL FUNCTION PROTOTYTE
***************************************************************************************************/
static void  TOUCHKEY_vGetMainPageMode(TOUCHKEY_stPageAttribute *PageManage,uint8 PageID);
static void TOUCHKEY_vGetDriveModeKeyState (TOUCHKEY_stPageAttribute *PageManage,uint8 KeyNum);
static void TOUCHKEY_vGetBodyModeKeyState (TOUCHKEY_stPageAttribute *PageManage,uint8 KeyNum);
static void TOUCHKEY_vGetCCModeKeyState (TOUCHKEY_stPageAttribute *PageManage,uint8 KeyNum);
static void TOUCHKEY_vGetSeatModeKeyState (TOUCHKEY_stPageAttribute *PageManage,uint8 KeyNum);

static void TOUCHKEY_vTouchInformationProcess(void);
static void TOUCHKEY_vTouchComunicationEngine(void);
static void TOUCHKEY_vSinglePointTouchSignalProcess(void);
static void TOUCHKEY_vMultiPointTouchSignalProcess(uint8 TouchNum);

static void TOUCHKEY_vUpdateOutputVariable(TOUCHKEY_stPageAttribute *PageManage,uint8 KeyNum,uint8 PageID);
static void TOUCHKEY_vClearOutput(void);
static void TouchKey_vGetMenuMode(void);

/*************************************************************************************************** 
  Function   : TOUCHKEY_vReset      
   
  Description: The reset routine for the Touch key module.
                            
  Arguments  : None
  
  Returns    : Nothing.
***************************************************************************************************/
 void TOUCHKEY_vReset (void)
 {
   	//	TOUCHKEY_au32Array[TOUCHKEY_nu32AcPage] = 0U;      /* Init output variable  */nCCMode_Button_R_1
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_1] = 0U;  
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_2] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_3] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_4] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_5] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_6] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_7] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_8] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_9] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_10]= 0U;
        TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_1] = 0U;  
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_2] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_3] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_4] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_5] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_6] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_7] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_8] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_9] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_10]= 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nu32MainCCPage] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nu32MainBodyPage] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nu32MainSeatPage] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nu32MainDrivePage] = 0U;
		TOUCHKEY_au8MainPageMode[MainPageNum]=0U;
 }

/*************************************************************************************************** 
  Function   : TOUCHKEY_vInit      
   
  Description: The Initialisation routine for the key module.
                            
  Arguments  : None
  
  Returns    : None.
***************************************************************************************************/
void TOUCHKEY_vInit (void)
{
    	TOUCHKEY_vReset(); 
}


/*************************************************************************************************** 
  Function   : TOUCHKEY_vDeinit      
   
  Description: The de-initialisation routine for the key module.
                            
  Arguments  : None
  
  Returns    : None.
***************************************************************************************************/
void TOUCHKEY_vDeinit (void)
{
    	TOUCHKEY_vReset();
}

/*************************************************************************************************** 
  Function   : TOUCHKEY_vMain      
   
  Description: The main function of this module.
                            
  Arguments  : None
  
  Returns    : None.
***************************************************************************************************/
void TOUCHKEY_vMain (void)
{   uint8 u8value;

	if((TOUCHKEY_sbiLowVoltage == True)||(TOUCHKEY_sbiHighVoltage == True))
	{
		TOUCHKEY_vReset(); 
	}
	else
	{		
		MCU_u16PinRead((MUC_enPinID)MCU_mPinID_P8_5,&u8value);
		
		if(u8value==1)   /***confirm touch rest pin is high**/
		{
		   	//TOUCHKEY_vTouchComunicationEngine();

			/****run interrupt service function******/
			
			/****run interrupt service function******/
			if((uRH850_8InterruptFlag==0))
			{

			 #if (TouchType==SinglePointTouch)
			 
		       TOUCHKEY_vSinglePointTouchSignalProcess();
			 
		       #elif(TouchType==MultiPointTouch)
			   
		       TOUCHKEY_vMultiPointTouchSignalProcess(TouchNumbers);
			   
		       #endif
				
			}
			else
			{
				/*****do Nothing*****/
			}
		}
		else
		{
			/*****do Nothing*****/
		}		

	}
	  	
}

/*************************************************************************************************** 
  Function   : TOUCHKEY_vGetCCModeKeyState      
   
  Description: The function is used for getting CCMode raw position from touch.
                            
  Arguments  : None
  
  Returns    : None.
***************************************************************************************************/
static void TOUCHKEY_vGetCCModeKeyState (TOUCHKEY_stPageAttribute *PageManage,uint8 KeyNum)
{
	uint8 u8_i;
	uint8 u8button_value_R;

 	/*************************************************************************************************** 
  Function   : define L or R     
   
  Description: set u8_i and key 
                            
  Arguments  : 2019-6-10
  
  Returns    : None.
***************************************************************************************************/
	
if(turn==true)
	{
		u8_i=0;
	    KeyNum=9;
		u16_XPos=Get16BitValue(TOUCHKEY_u8TouchInfBuff_L[15], TOUCHKEY_u8TouchInfBuff_L[16]);
	      u16_YPos=Get16BitValue(TOUCHKEY_u8TouchInfBuff_L[17], TOUCHKEY_u8TouchInfBuff_L[18]);
		  	 
		if((TOUCHKEY_u8TouchInfBuff_L[24]>=0xb0)&&(TOUCHKEY_u8TouchInfBuff_L[24]<=0xba))
			u8Gsid_flag=1;
		else
			u8Gsid_flag=0;
if(TOUCHKEY_u8TouchInfBuff_L[14]==1)
	{	
		for(u8_i ; u8_i < KeyNum; u8_i++)
		{	
			if((u16_XPos >= PageManage[u8_i].x_PosMin)&&(u16_XPos <=  PageManage[u8_i].x_PosMax))
			{
				if((u16_YPos >=PageManage[u8_i].y_PosMin)&&(u16_YPos <= PageManage[u8_i].y_PosMax))
				{
					TOUCHKEY_au32Array[u8_i]=TOUCHKEY_nPress;	
					
					u8button_value=u8_i+1;
					
						if(u8button_value !=control_button_debug[u8button_value])					
					          {  u8button_value=0;}					
					 	TOUCHKEY_u8TouchInfBuff_L[28]=u8button_value;                                     
							
				}
				else
				{
					TOUCHKEY_au32Array[u8_i] = TOUCHKEY_nRelease;				
					
				}
			}
			else
			{
				TOUCHKEY_au32Array[u8_i] = TOUCHKEY_nRelease;
				
			}
		}
	}
	else
	{
		u16_XPos=0;
		u16_YPos=0;
		TOUCHKEY_u8TouchInfBuff_L[28]=0; 
		u8button_value=0;
		u8ForceKeyPressed=0;

		for(u8_i ; u8_i < KeyNum; u8_i++)
		{
			TOUCHKEY_au32Array[u8_i]=TOUCHKEY_nRelease;			
			TOUCHKEY_u8TouchInfBuff_L[28]=0;				
		}		
	}
		
		  
	}
else{
	    u8_i=9;
	   KeyNum=20;
	   	u16_XPos=Get16BitValue(TOUCHKEY_u8TouchInfBuff_R[15], TOUCHKEY_u8TouchInfBuff_R[16]);
	      u16_YPos=Get16BitValue(TOUCHKEY_u8TouchInfBuff_R[17], TOUCHKEY_u8TouchInfBuff_R[18]);
		  if(TOUCHKEY_u8TouchInfBuff_R[14]==1)
	{	
		for(u8_i ; u8_i < KeyNum; u8_i++)
		{	
			if((u16_XPos >= PageManage[u8_i].x_PosMin)&&(u16_XPos <=  PageManage[u8_i].x_PosMax))
			{
				if((u16_YPos >=PageManage[u8_i].y_PosMin)&&(u16_YPos <= PageManage[u8_i].y_PosMax))
				{
					TOUCHKEY_au32Array[u8_i]=TOUCHKEY_nPress;	
					
					u8button_value_R=u8_i+1;				
									
					 	TOUCHKEY_u8TouchInfBuff_R[28]=u8button_value_R;                                            
									
				}
				else
				{
					TOUCHKEY_au32Array[u8_i] = TOUCHKEY_nRelease;				
					
				}
			}
			else
			{
				TOUCHKEY_au32Array[u8_i] = TOUCHKEY_nRelease;
				
			}
		}
	}
	else
	{
		u16_XPos=0;
		u16_YPos=0;
	TOUCHKEY_u8TouchInfBuff_R[28]=0;
	     u8button_value_R=0;   
		for(u8_i ; u8_i < KeyNum; u8_i++)
		{
			TOUCHKEY_au32Array[u8_i]=TOUCHKEY_nRelease;
			
			TOUCHKEY_u8TouchInfBuff_R[28]=0;
				
		}
		
	}

	}
	
	
		
	}

	/*******************
      add by wuyijun
      app 

	*********/
	 
	//TOUCHKEY_u8TouchInfBuff_L[22]=CCP_u8GetLowByte(Force_u16GetValue(Force_nu16RawAd));
	//TOUCHKEY_u8TouchInfBuff_L[23]=CCP_u8GetHighByte(Force_u16GetValue(Force_nu16RawAd);
	
	



/*************************************************************************************************** 
  Function   : TOUCHKEY_vGetDriveModeKeyState      
   
  Description: The function is used for getting DriveMode raw position from touch.
                            
  Arguments  : None
  
  Returns    : None.
***************************************************************************************************/
static void TOUCHKEY_vGetDriveModeKeyState (TOUCHKEY_stPageAttribute *PageManage,uint8 KeyNum)
{
	uint8 u8_i;
	uint32 u32temp=0;
	u16_XPos=Get16BitValue(TOUCHKEY_u8TouchInfBuff[1], TOUCHKEY_u8TouchInfBuff[2]);
	u32temp = Get16BitValue(TOUCHKEY_u8TouchInfBuff[3], TOUCHKEY_u8TouchInfBuff[4])	;
	u16_YPos=(uint16)(u32temp*67/100);
	
	if(TOUCHKEY_u8TouchInfBuff[0]==1)
	{
		for(u8_i =48; u8_i < (KeyNum+48); u8_i++)
		{
			if((u16_XPos > PageManage[u8_i-48].x_PosMin)&&(u16_XPos <=  PageManage[u8_i-48].x_PosMax))
			{
				if((u16_YPos > PageManage[u8_i-48].y_PosMin)&&(u16_YPos <= PageManage[u8_i-48].y_PosMax))
				{
					TOUCHKEY_au32Array[u8_i]=TOUCHKEY_nPress;
				}
				else
				{
					TOUCHKEY_au32Array[u8_i] = TOUCHKEY_nRelease;
				}
			}
			else
			{
				TOUCHKEY_au32Array[u8_i] = TOUCHKEY_nRelease;
			}
		}
	}
	else
	{
		u16_XPos=0;
		u16_YPos=0;
		for(u8_i =48; u8_i < (KeyNum+48); u8_i++)
		{
			TOUCHKEY_au32Array[u8_i]=TOUCHKEY_nRelease;
		}
		
	}
	
}


/*************************************************************************************************** 
  Function   : TOUCHKEY_vGetSeatModeKeyState      
   
  Description: The function is used for getting SeatMode raw position from touch.
                            
  Arguments  : None
  
  Returns    : None.
***************************************************************************************************/
static void TOUCHKEY_vGetSeatModeKeyState (TOUCHKEY_stPageAttribute *PageManage,uint8 KeyNum)
{
	uint8 u8_i;
	uint32 u32temp=0;
	u16_XPos=Get16BitValue(TOUCHKEY_u8TouchInfBuff[1], TOUCHKEY_u8TouchInfBuff[2]);
	//u16_YPos=Get16BitValue(TOUCHKEY_u8TouchInfBuff[3], TOUCHKEY_u8TouchInfBuff[4])*0.67;/*do not use point value,190427*/
	u32temp = Get16BitValue(TOUCHKEY_u8TouchInfBuff[3], TOUCHKEY_u8TouchInfBuff[4])	;
	u16_YPos=(uint16)(u32temp*67/100);
	
	if(TOUCHKEY_u8TouchInfBuff[0]==1)
	{
		for(u8_i =16; u8_i < (KeyNum+16); u8_i++)
		{
			if((u16_XPos > PageManage[u8_i].x_PosMin)&&(u16_XPos <=  PageManage[u8_i].x_PosMax))
			{
				if((u16_YPos > PageManage[u8_i].y_PosMin)&&(u16_YPos <= PageManage[u8_i].y_PosMax))
				{
					TOUCHKEY_au32Array[u8_i]=TOUCHKEY_nPress;
				}
				else
				{
					TOUCHKEY_au32Array[u8_i] = TOUCHKEY_nRelease;
				}
			}
			else
			{
				TOUCHKEY_au32Array[u8_i] = TOUCHKEY_nRelease;
			}
		}
	}
	else
	{
		u16_XPos=0;
		u16_YPos=0;
		for(u8_i =16; u8_i < (KeyNum+16); u8_i++)
		{
			TOUCHKEY_au32Array[u8_i]=TOUCHKEY_nRelease;
		}
		
	}
	
}


/*************************************************************************************************** 
  Function   : TOUCHKEY_vGetCCModeKeyState      
   
  Description: The function is used for getting SeatMode raw position from touch.
                            
  Arguments  : None
  
  Returns    : None.
***************************************************************************************************/
static void TOUCHKEY_vGetBodyModeKeyState (TOUCHKEY_stPageAttribute *PageManage,uint8 KeyNum)
{
	
	uint8 u8_i;
	uint32 u32temp=0;
	u16_XPos=Get16BitValue(TOUCHKEY_u8TouchInfBuff[1], TOUCHKEY_u8TouchInfBuff[2]);
	//u16_YPos=Get16BitValue(TOUCHKEY_u8TouchInfBuff[3], TOUCHKEY_u8TouchInfBuff[4])*0.67;
	u32temp = Get16BitValue(TOUCHKEY_u8TouchInfBuff[3], TOUCHKEY_u8TouchInfBuff[4])	;/*do not use point value,190427*/
	u16_YPos=(uint16)(u32temp*67/100);
	if(TOUCHKEY_u8TouchInfBuff[0]==1)
	{
		for(u8_i =32; u8_i < (KeyNum+32); u8_i++)
		{
			if((u16_XPos > PageManage[u8_i-32].x_PosMin)&&(u16_XPos <=  PageManage[u8_i-32].x_PosMax))
			{
				if((u16_YPos > PageManage[u8_i-32].y_PosMin)&&(u16_YPos <= PageManage[u8_i-32].y_PosMax))
				{
					TOUCHKEY_au32Array[u8_i]=TOUCHKEY_nPress;
				}
				else
				{
					TOUCHKEY_au32Array[u8_i] = TOUCHKEY_nRelease;
				}
			}
			else
			{
				TOUCHKEY_au32Array[u8_i] = TOUCHKEY_nRelease;
			}
		}
	}
	else
	{
		u16_XPos=0;
		u16_YPos=0;
		for(u8_i =32; u8_i < (KeyNum+32); u8_i++)
		{
			TOUCHKEY_au32Array[u8_i]=TOUCHKEY_nRelease;
		}
		
	}
	
}



/*************************************************************************************************** 
  Function   : TOUCHKEY_vGetMainPageMode      
   
  Description: The function is used for get the main page mode .
                            
  Arguments  : None
  
  Returns    : The key number used for index the response function in MMI.
***************************************************************************************************/
static void  TOUCHKEY_vGetMainPageMode(TOUCHKEY_stPageAttribute *PageManage,uint8 PageID)
{

	uint8 u8_i;
	uint32 u32temp=0;
	u16_XPos=Get16BitValue(TOUCHKEY_u8TouchInfBuff[1], TOUCHKEY_u8TouchInfBuff[2]);
	//u16_YPos=Get16BitValue(TOUCHKEY_u8TouchInfBuff[3], TOUCHKEY_u8TouchInfBuff[4])*0.67;
	u32temp = Get16BitValue(TOUCHKEY_u8TouchInfBuff[3], TOUCHKEY_u8TouchInfBuff[4])	;/*do not use point value,190427*/
	u16_YPos=(uint16)(u32temp*67/100);
	
	if(TOUCHKEY_u8TouchInfBuff[0]==1)
	{
		for(u8_i =64; u8_i < (PageID+64); u8_i++)
		{
			if((u16_XPos > PageManage[u8_i-64].x_PosMin)&&(u16_XPos <=  PageManage[u8_i-64].x_PosMax))
			{
				if((u16_YPos > PageManage[u8_i-64].y_PosMin)&&(u16_YPos <= PageManage[u8_i-64].y_PosMax))
				{
					TOUCHKEY_au32Array[u8_i]=TOUCHKEY_nPress;
					TOUCHKEY_au8MainPageMode[u8_i-64]=1;
					
				}
				else
				{
					TOUCHKEY_au32Array[u8_i] = TOUCHKEY_nRelease;
					TOUCHKEY_au8MainPageMode[u8_i-64]=0;
				}
			}
			else
			{
				TOUCHKEY_au32Array[u8_i] = TOUCHKEY_nRelease;
				TOUCHKEY_au8MainPageMode[u8_i-64]=0;
			}
		}
	}
	else
	{
		u16_XPos=0;
		u16_YPos=0;
		for(u8_i =64; u8_i < (PageID+64); u8_i++)
		{
			TOUCHKEY_au32Array[u8_i]=TOUCHKEY_nRelease;
		}
		
	}

  
}

/*************************************************************************************************** 
  Function   : TOUCHKEY_vSinglePointTouchActionProcess      
   
  Description: The function is used for detecting Single touch key signal.
                            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/
static void TOUCHKEY_vSinglePointTouchSignalProcess(void)
{
/****************************************
function :read  right touch data
add by wuyijun
date 2019-5 -21
 Description: 10ms receive data
 
*************************************/

 

if(turn==true)
{	
       turn=false;
	Siic_SetSlaveAddress(Siic_Chn_0, 0x09);
	Siic_u8ReceiveBlock(Siic_Chn_0,0x00,29,&TOUCHKEY_u8TouchInfBuff);   
	Siic_u8ReceiveBlock(Siic_Chn_0,0x00,29,&TOUCHKEY_u8TouchInfBuff_R);   		
}
else
{
	turn=true;
	Siic_SetSlaveAddress(Siic_Chn_0, 0x08);	
	
	Siic_u8ReceiveBlock(Siic_Chn_0,0x00,29,&TOUCHKEY_u8TouchInfBuff);   
	Siic_u8ReceiveBlock(Siic_Chn_0,0x00,29,&TOUCHKEY_u8TouchInfBuff_L);   
	
}
/****read touch data  lin read data*****/
 u8new =CCP_u8DataArrayFE_Byte6;
 TOUCHKEY_u8DataArrayFE_Byte6=   ((CCP_u8DataArrayFE_Byte6) | (u8old));
 u8old=u8new;

 
/*TOUCHKEY_vGetMainPageMode(TOUCHKEY_stMainPageManage,TOUCHKEY_nMAINPAGE_Max);*/
	TOUCHKEY_vTouchInformationProcess();

}

/*************************************************************************************************** 
  Function   : TOUCHKEY_vMultiPointTouchActionProcess      
   
  Description: The function is used for detecting Multi touch key signal.
                            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/
static void TOUCHKEY_vMultiPointTouchSignalProcess(uint8 TouchNum)
{
	static uint8 u16GetMultiTouchData=0;

	/****************************************
	function :read  right touch data
	add by wuyijun
	date 2019-5 -21
	 Description: 10ms receive data
	 
	*************************************/
if(turn==true)
{	
     turn=false;
	Siic_SetSlaveAddress(Siic_Chn_0, 0x09);  
	u16GetMultiTouchData=10*TouchNum;
	Siic_u8ReceiveBlock(Siic_Chn_0,0x1B,u16GetMultiTouchData,&TOUCHKEY_u8TouchInfBuff);
	Siic_u8ReceiveBlock(Siic_Chn_0,0x00,30,&TOUCHKEY_u8TouchInfBuff_L);   	
}
else
{
	turn=true;
	Siic_SetSlaveAddress(Siic_Chn_0, 0x08);
	u16GetMultiTouchData=10*TouchNum;
	Siic_u8ReceiveBlock(Siic_Chn_0,0x1B,u16GetMultiTouchData,&TOUCHKEY_u8TouchInfBuff);
	Siic_u8ReceiveBlock(Siic_Chn_0,0x00,30,&TOUCHKEY_u8TouchInfBuff_L);   
}	
	
	/****read touch data*****/

 u8new =CCP_u8DataArrayFE_Byte6;
 TOUCHKEY_u8DataArrayFE_Byte6=   ((CCP_u8DataArrayFE_Byte6) | (u8old));
 u8old=u8new;
	/*****do Nothing*****/
}

/*************************************************************************************************** 
  Function   : TOUCHKEY_vTouchInformationProcess      
   
  Description: The function is used for detecting the key from pressed to released.
                            
  Arguments  : None
  
  Returns    : None X and Y and status
***************************************************************************************************/
static void TOUCHKEY_vTouchInformationProcess(void)
{
		TOUCHKEY_tenMenuMode TOUCHKEY_MenuMode=TOUCHKEY_nCCMode;
		static TOUCHKEY_tenMenuMode TOUCHKEY_MenuModeLast=TOUCHKEY_nCCMode;
		TOUCHKEY_MenuMode=0;//Knob_vGetMenuMode();
		
		if(TOUCHKEY_MenuMode==TOUCHKEY_nMaxMode)
		{
			TOUCHKEY_MenuMode=TOUCHKEY_MenuModeLast;

		}
	if(TOUCHKEY_MenuMode==TOUCHKEY_nCCMode)
	{
		TOUCHKEY_vGetCCModeKeyState(TOUCHKEY_stCCModePageManage,TOUCHKEY_nu32CCModeMax);
	}
	else if(TOUCHKEY_MenuMode==TOUCHKEY_nSeatMode)
	{
		TOUCHKEY_vGetSeatModeKeyState(TOUCHKEY_stSeatModePageManage,TOUCHKEY_nSeatModePAGE_Max);
		
	}
	else if(TOUCHKEY_MenuMode==TOUCHKEY_nBodyMode)
	{
		TOUCHKEY_vGetBodyModeKeyState(TOUCHKEY_stBodyModePageManage,TOUCHKEY_nBodyModePAGE_Max);
		
	}
	else if(TOUCHKEY_MenuMode==TOUCHKEY_nDriveMode)
	{
		TOUCHKEY_vGetDriveModeKeyState(TOUCHKEY_stDriveModePageManage,TOUCHKEY_nDriveModePAGE_Max);
		
	}
	else
	{
		
	}
	TOUCHKEY_au16Array[TOUCHKEY_nu16IicX_Value]=Get16BitValue(TOUCHKEY_u8TouchInfBuff[15], TOUCHKEY_u8TouchInfBuff[16]);
	TOUCHKEY_au16Array[TOUCHKEY_nu16IicY_Value]=Get16BitValue(TOUCHKEY_u8TouchInfBuff[17], TOUCHKEY_u8TouchInfBuff[18]);
	
	//Button_u8key();

	TOUCHKEY_MenuModeLast=TOUCHKEY_MenuMode; 
} 

/*************************************************************************************************** 
  Function   : TOUCHKEY_vTouchComunicationEngine      
   
  Description: The function is used for processing the comunication TP(SPI/IIC) engine between 
  the touch MCU  and the main MCU
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/
static void TOUCHKEY_vTouchComunicationEngine(void)
{
	uint8 u8EnterOperationMode[1]={0x88};
	uint8 u8ExitBootLader[8]={0xFF,0x01,0x3b,0x00,0x00,0x4f,0x6d,0x17};

	switch(u8WaitFlag)
	{
		case 0:
			u8WaitFlag=1;
			Siic_u8SendBlock(Siic_Chn_1,0x00,8,&u8ExitBootLader);	/*****exit bootloader mode*****/
			break;
		case 1:
			u8WaitFlag=2;
			Siic_u8SendBlock(Siic_Chn_1,0x00,8,&u8ExitBootLader);	/*****exit bootloader mode*****/
			break;
		case 2:
			u8WaitFlag=3;
			Siic_u8SendBlock(Siic_Chn_1,0x00,1,&u8EnterOperationMode);/*****Enter Operation Mode*****/
			break;
		case 3:
			u8WaitFlag=4;
			Siic_u8SendBlock(Siic_Chn_1,0x00,1,&u8EnterOperationMode);/*****Enter Operation Mode*****/
			break;
		case 4:
			u8WaitFlag=4;
			//TOUCHKEY_vGetCCModeKeyState(TOUCHKEY_stCCModePageManage,TOUCHKEY_nu32CCModeMax);
			break;
		default :
			break;	
	}	
}

/*************************************************************************************************** 
  Function   : TOUCHKEY_vDetectActionP2P      
   
  Description: The function is used for detecting the key from pressed to pressed.
                            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/
static void TOUCHKEY_vDetectActionP2P(TOUCHKEY_stPageAttribute *PageManage,uint8 u8KeyId)
{

}

static void TOUCHKEY_vClearOutput(void)
{
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_1] = 0U;      /* Init output variable  */
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_2] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_3] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_4] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_5] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_6] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_7] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_8] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_9] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_L_10] = 0U;			
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_1] = 0U;  
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_2] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_3] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_4] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_5] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_6] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_7] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_8] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_9] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nCCMode_Button_R_10] = 0U;		
		TOUCHKEY_au32Array[TOUCHKEY_nu32MainCCPage] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nu32MainBodyPage] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nu32MainSeatPage] = 0U;
		TOUCHKEY_au32Array[TOUCHKEY_nu32MainDrivePage] = 0U;

}

/*************************************************************************************************** 
  Function   : TOUCHKEY_vUpdateOutputVariable      
   
  Description: The function is used for Getting the valid key flag.
                            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/
static void TOUCHKEY_vUpdateOutputVariable(TOUCHKEY_stPageAttribute *PageManage,uint8 KeyNum,uint8 PageID)
{
    	
}

/*************************************************************************************************** 
  Function   : TOUCHKEY_u16GetValue      
   
  Description: supply variable for other modules.
                            
  Arguments  : None
  
  Returns    : variable other module want to get.
***************************************************************************************************/
uint32 TOUCHKEY_u32GetValue(TOUCHKEY_tenu32CCModeVarNum Num)
{
    	uint32 u32ReturnValue;
	if(Num<TouchKeyNum)
	{
        	u32ReturnValue = TOUCHKEY_au32Array[Num];
	}
	else
	{
        	u32ReturnValue = TOUCHKEY_au32Array[TouchKeyNum-1];
	}
    	return u32ReturnValue;
}

uint16 TOUCHKEY_u16GetValue(TOUCHKEY_tenu16CCModeVarNum Num)
{
    	uint16 u16ReturnValue;
	if(Num<TOUCHKEY_nu16Max)
	{
        	u16ReturnValue = TOUCHKEY_au16Array[Num];
	}
	else
	{
        	u16ReturnValue = TOUCHKEY_au16Array[TOUCHKEY_nu16Max-1];
	}
    	return u16ReturnValue;
}

/*************************************************************************************************** 
  Function   : Get16BitValue      
   
  Description: supply variable for other modules,Replace the 8-bit data with 16 bits.
                            
  Arguments  : None
  
  Returns    : variable other module want to get.
***************************************************************************************************/
uint16  Get16BitValue(uint8 ucHighByte, uint8 ucLowByte)
{
	uint8 t_ucHighByte = 0, t_ucLowByte = 0;
	uint16 t_uc16BitValue = 0;

	t_ucHighByte = ucHighByte;
	t_ucLowByte = ucLowByte;
#if 1
	t_uc16BitValue = (t_ucLowByte << 8) | t_ucHighByte;

#else
	t_uc16BitValue = (t_ucHighByte << 8) | t_ucLowByte;

#endif
	return(t_uc16BitValue);

}

/***************************************************************************************************
  Function     : Knob_vGetMenuMode()
  Description  : For other module to get the rotary direction for other.

  Takes        : None

  Returns      : None
***************************************************************************************************/
static void TouchKey_vGetMenuMode(void)
{
	/***do nothing****/
	uint32 u32MenuModeKeyPressed=0;
    	uint32 u32PhyKeyPressFlag=0;
	u32MenuModeKeyPressed = 0;                            //TOUCHKEY_u32GetKeyKeyPressed;  
       u32PhyKeyPressFlag = (uint32)KEY_vKeyGetPhyKeyPressAction();
	if((u32MenuModeKeyPressed)&(1<<26))
	{
		TouchKey_MianMenu_Mode=TOUCHKEY_nCCMode;
	}
	else if((u32MenuModeKeyPressed)&(1<<27))                                          
	{               
		TouchKey_MianMenu_Mode=TOUCHKEY_nSeatMode;		       
	}
	else if((u32MenuModeKeyPressed)&(1<<28))
	{
		TouchKey_MianMenu_Mode=TOUCHKEY_nBodyMode;		
	}
	else if((u32MenuModeKeyPressed)&(1<<29))
	{
		TouchKey_MianMenu_Mode=TOUCHKEY_nDriveMode;		
	}
	else
	{
		
	}
}

uint8 TOUCHKEY_u8GetIicValue_R(uint8 u8Num)
{
	uint8 u8RetValue=0;
	
	if(u8Num<TouchIicDataLen)
	{
		u8RetValue = TOUCHKEY_u8TouchInfBuff_R[u8Num];
	}
	else
	{
		u8RetValue = TOUCHKEY_u8TouchInfBuff_R[TouchIicDataLen-1];
	}
	return u8RetValue;
}
uint8 TOUCHKEY_u8GetIicValue_L(uint8 u8Num)
{
	uint8 u8RetValue=0;
	
	if(u8Num<TouchIicDataLen)
	{
		u8RetValue = TOUCHKEY_u8TouchInfBuff_L[u8Num];
	}
	else
	{
		u8RetValue = TOUCHKEY_u8TouchInfBuff_L[TouchIicDataLen-1];
	}
	return u8RetValue;
}



/***************************************************************************************************
  EOF: touch.c
***************************************************************************************************/


