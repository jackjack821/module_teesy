/*******************************************************************************
| Module Name: Lcd Control
| File Name: Lcd.c
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
| Yang Shengli                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-02-27  1.00        Yang Shengli      First implementation
| 2016-03-15  2.00        Yang Shengli      update LCD code
********************************************************************************/
#define LCD                        /* name of the module                */
//#define USE_RTE

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/

/* system-headerfiles */
#include "General.h"
/* foreign headerfiles */
#include "ALG.h"
#include "Frame_if.h"
//#ifdef USE_RTE
//#include "Rte_Lcd.h"
//#else
#include "POW.h"
#include "IGN.h"
#include "MMI.h"
#include "HCT.h"
#include "OAT.h"
//#endif
/* own headerfiles */
#include "Lcd.h"
#include "Lcd_Cfg.h"
#include "Lcd_Private.h"
#include "Lcd_Type.h"
//#define USE_INTIIC
#ifndef USE_INTIIC
#include "s_iic.h"
#endif
#include "iic.h"
/*Local variable definition*/
static uint8 LCD_au8Array[LCD_nu8Max];
static uint16 LCD_au16Array[LCD_nu16Max];
static uint8 LCD_u8IgOffToOnDisplayWait;
static uint16 LCD_u16FilterErrorDisplay;
static LCD_tstMapBuffer LCD_stMapBuffer;	/*Mapping buffers of LCD display RAM*/
static uint16 LCD_u16NeedToSwitchOffLcd;
static uint16 LCD_au16Array[LCD_nu16Max]; 
#if LCD_CcpControlEnable
/*Ccp control*/
typedef enum
{
    LCD_nLcdDisplayFlag = 0,
    LCD_nLcdDisplayMode,
	Lcd_nCcpForceMax
}CcpControl_Lcd;
static uint8 Lcd_CcpForceFlag=0;
static uint16 Lcd_CcpControlData[Lcd_nCcpForceMax];
#define LcdGetCcpForceBit(index)	((Lcd_CcpForceFlag>>index)&0x01)
#define LcdSetCcpForceBit(index)	(Lcd_CcpForceFlag=Lcd_CcpForceFlag|(0x01<<index))
#define LcdClrCcpForceBit(index)	(Lcd_CcpForceFlag=Lcd_CcpForceFlag&(~(0x01<<index)))
#define LcdClrCcpForceByte(void)	(Lcd_CcpForceFlag=0)
//static void LCD_vCcpInputForce(void);
static void LCD_vCcpOutputForce(void);
#endif

static void LCD_vInputValueProcess(void);
static void LCD_vUpdateDisplayInfo(void);
static void LCD_vSwitch(uint8 u8Status);
static void LCD_vUpdateBlowerInfo(void);
static void LCD_vUpdateAirdInfo(void);
static void LCD_vUpdateCTempInfo(uint8 Temp,uint8 TempPs);
static void LCD_vUpdateFTempInfo(uint8 Temp);
static void LCD_vShowHiTemp(LCD_enu8HiStatus ZoneStatus);
//static void LCD_vUpdateDiagInfo(void);
static void LCD_vUpdateTempInfo(void);
static void LCD_vUpdateIonInfo(void);
static void LCD_bar(uint8 level);
static void LCD_icon(uint16 u16Icon, uint8 on);
static void LCD_char(uint8 chr, uint8 pos);
static void LCD_minus(uint8 chr, uint8 pos);
static void LCD_u8CheckInputRange(uint8 Max,uint8 Min,uint8 Input,uint8 Num,uint8 Mask);


/*****************************************************************************										  *
 Function      : LCD_vReset                                                  *
 Description   : Initialises the iic*
                                             *
 Return Value  : None                                                        *
*****************************************************************************/
void LCD_vReset(void)
{
    //IIC_vDrvInit_CH1();
}

/*****************************************************************************										  *
 Function      : LCD_vInit                                                  *
 Description   : Module change from Active to ON*
                 .                            *
 Return Value  : None                                                        *
*****************************************************************************/
void LCD_vInit(void)
{
   //IIC_vDrvInit_CH1();
   	Siic_Init(Siic_Chn_0);
	Siic_SetSlaveAddress(Siic_Chn_0, 0x08);
}

/*****************************************************************************										  *
 Function      : LCD_vDeinit                                                  *
 Description   : Module change from ON to Active*
                 .                            *
 Return Value  : None                                                        *
*****************************************************************************/
void LCD_vDeinit(void)
{
	
}

/*****************************************************************************										  *
 Function      : LCD_vActive                                                  *
 Description   : The active function of LCD module*
                                             *
 Return Value  : None                                                        *
*****************************************************************************/
void LCD_vActive(void)
{
   
}
#ifdef USE_INTIIC
uint16 CB_Send,CB_Receive,CB_err;
void LCD_MasterSendEndCallback(void)
{
	CB_Send++;
	//MCU_u16IIC_MasterStopCondition(MCU_mSerial_ID_IIC20);
}

void LCD_MasterReceiveEndCallback(void)
{
	CB_Receive++;
	//MCU_u16IIC_MasterStopCondition(MCU_mSerial_ID_IIC20);
}

void LCD_IicErr(uint8 Index)
{
	CB_err=Index;
}
#endif

/*****************************************************************************										  *
 Function      : LCD_vMainCommand                                                   *
 Description   : In the On state, the Backlight is .                         *
               Control the LCD display. *
 NOTE: This part of the main code is normally called from the 10mS container*
 Return Value  : None                                                        *
*****************************************************************************/
void LCD_vMainCommand(void)
{
		uint8 u8BattHighVoltage;
		uint8 u8BattLowVoltage;
		uint8 u8i,u8RecArray[10];
		uint8 u8Array[1]={0};
		u8Array[0]=0x48;
		uint8 u8EnterOperationMode[1]={0x88};
		/*LCD_stMapBuffer.u8DriverAddr =0x48;//(( 0x24<<1)|1);
		LCD_stMapBuffer.u8Cmd1 = 0x00;	
		LCD_stMapBuffer.u8Cmd2 = 0x00;
		LCD_stMapBuffer.u8Cmd3 = 0x00;
		LCD_stMapBuffer.u8Cmd4 = 0x00;
		LCD_stMapBuffer.u8Cmd5 = 0x00;	
		IIC_vStartCondition_CH1();
		IIC_u16SendData_CH1(&u8Array,1);
		IIC_u16SendData_CH1(0x48,1);
		IIC_u16RecData_CH1(&u8RecArray, 1);
		IIC_vStopCondition_CH1();*/
		//Siic_u8SendBlock(Siic_Chn_0,0x00,1,&u8EnterOperationMode); /*by zsc*/
	//	Siic_u8ReceiveBlock(Siic_Chn_0,0x1B,10,&u8RecArray);/****read touch data*****/
	   
    
}

/*****************************************************************************										  *
 Function      : LCD_vMainCom0                                                   *
 Description   : In the On state, the Backlight is .                         *
               Control the LCD display. *
 NOTE: This part of the main code is normally called from the 10mS container*
 Return Value  : None                                                        *
*****************************************************************************/
void LCD_vMainCom0(void)
{
	
}

/*****************************************************************************										  *
 Function      : LCD_vMainCom1                                                   *
 Description   : In the On state, the Backlight is .                         *
               Control the LCD display. *
 NOTE: This part of the main code is normally called from the 10mS container*
 Return Value  : None                                                        *
*****************************************************************************/
void LCD_vMainCom1(void)
{
	
}

/*****************************************************************************										  *
 Function      : LCD_vMainCom2                                                   *
 Description   : In the On state, the Backlight is .                         *
               Control the LCD display. *
 NOTE: This part of the main code is normally called from the 10mS container*
 Return Value  : None                                                        *
*****************************************************************************/
void LCD_vMainCom2(void)
{
	
}

/*****************************************************************************										  *
 Function      : LCD_vMainCom3                                                   *
 Description   : In the On state, the Backlight is .                         *
               Control the LCD display. *
 NOTE: This part of the main code is normally called from the 10mS container*
 Return Value  : None                                                        *
*****************************************************************************/
void LCD_vMainCom3(void)
{
	
}
/***************************************************
 * Function:     LCD_vUpdateBlowerInfo(void)
 * Description:  Update the current display information.
 * Input:		 None
 * Return:	     None	
***************************************************/
static void LCD_vUpdateBlowerInfo(void)
{
	
}
/***************************************************
 * Function:     LCD_vUpdateAirdInfo(void)
 * Description:  Update the current display information.
 * Input:		 None
 * Return:	     None	
***************************************************/
static void LCD_vUpdateAirdInfo(void)
{
	

	
}
/***************************************************
 * Function:     LCD_vShowHiTemp(void)
 * Description:  If temp exceed the limit.
 * Input:		 None
 * Return:	     None	
***************************************************/
static void LCD_vShowHiTemp(LCD_enu8HiStatus ZoneStatus)
{
	
	

}
/***************************************************
 * Function:     LCD_vShowLoTemp(void)
 * Description:  If temp below the Limit.
 * Input:		 None
 * Return:	     None	
***************************************************/
static void LCD_vShowLoTemp(LCD_nu8LowStatus ZoneStatus)
{
	

}


/***************************************************
 * Function:     LCD_vUpdateCTempInfo(void)
 * Description:  Update the current display information.
 * Input:		 None
 * Return:	     None	
***************************************************/
static void LCD_vUpdateCTempInfo(uint8 Temp,uint8 TempPs)
{
	
}
/***************************************************
 * Function:     LCD_vUpdateFTempInfo(void)
 * Description:  Update the current display information.
 * Input:		 None
 * Return:	     None	
***************************************************/
static void LCD_vUpdateFTempInfo(uint8 Temp)
{
	
}
/***************************************************
 * Function:     LCD_vUpdateTempInfo(void)
 * Description:  Update the current display information.
 * Input:		 None
 * Return:	     None	
***************************************************/
static void LCD_vUpdateTempInfo(void)
{
	
	
}
/*****************************************************************************
 Function      : OAT_u16GetValue                                              *
 Description   : The extern model get the uint16 type variable value from this*
				 model                                                       *
 Return Value  : uint16 value                                                 *
*****************************************************************************/
uint16 LCD_vu16TouchInfGetValue( LCD_tenu16VarNumber enIndex )
{
    uint16 u16ReturnValue=0U;
    
	if ( enIndex < OAT_nu16Max )
	{
		u16ReturnValue = LCD_au16Array[enIndex];
	}
	else
	{
		u16ReturnValue = LCD_au16Array[LCD_nu16Max-1U];
	}
    
    return u16ReturnValue;
}	
/*****************************************************************************										  *
 Function      : LCD_vMain                                                   *
 Description   : In the On state, the Backlight is .                         *
               Control the LCD display. *
 NOTE: This part of the main code is normally called from the 100mS container*
 Return Value  : None                                                        *
*****************************************************************************/


