/*******************************************************************************
| Module Name: CAN CCL
| File Name: CANCCL.c
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
| Liu Fuguang                           Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-07-19  1.00        Liu Fuguang          First implementation

********************************************************************************/
#define CANCCL_C                          /* Name of the Module                */
/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
#include "general.h"
/* Foreign headerfiles */
#include "CANAPP.h"
#include "CANNMAPP.h"
/* Own headerfiles */
#include "CANCCL.h"
#include "CANCCL_cfg.h"
/* Define static variable */
static uint16 CANCCL_u16Array[CANCCL_nu16Max];
static uint16 CANCCL_u16TimeBase_10ms;
static uint16 CANCCL_u16CANRun10msEnable;
/*****************************************************************************
* Function   :  CANCCL_u16GetValue
* Description: Called in anywhere
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
uint16 CANCCL_u16GetValue(CANCCL_tenu16VarNumber enIndex)
{
	if(enIndex < CANCCL_nu16Max)
	{
		return (CANCCL_u16Array[enIndex]);
	}
	else
	{
		return (CANCCL_u16Array[CANCCL_nu16Max-1]);
	}
}
/*****************************************************************************
* Function   : void CANNM_vReset (void)
* Description: Called OS Reset container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void CANCCL_vReset(void)
{
	CANNMAPP_vReset();
	CANCCL_u16Array[CANCCL_nu16EnableSleep] = False;
	CANCCL_u16TimeBase_10ms = 9;
    CANCCL_u16CANRun10msEnable=CANCCL_enResetFlag;
}

/*****************************************************************************
* Function   : void CANCCL_vTask_10ms (void)
* Description: Called in CANCCL Module Reset container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void CANCCL_vTask_10ms(void)
{
    CANNMAPP_vMain_10ms();
	CANAPP_vMain_10ms();
	if((CANNMAPP_u16GetValue(CAMNMAPP_nu16CanSleep) == True)&&\
		(CANNMAPP_u16GetValue(CANNMAPP_u16BusIdle)==True))
	{
		CANCCL_u16Array[CANCCL_nu16EnableSleep] = True;
	}
	else
	{
		CANCCL_u16Array[CANCCL_nu16EnableSleep] = False;
	}
}
/*****************************************************************************
* Function   : void CANCCL_vMain (void)
* Description: Called in OS 1ms Container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void CANCCL_vMain(void)
{
	if((CANCCL_u16CANRun10msEnable == CANCCL_enRunEnable)||\
        (CANCCL_u16CANRun10msEnable == CANCCL_enResetFlag))
	{
		CANCCL_vTask_10ms();
        if(CANCCL_u16CANRun10msEnable == CANCCL_enResetFlag)
        {
            CANCCL_u16TimeBase_10ms=0;
        }
        CANCCL_u16CANRun10msEnable = CANCCL_enRunDisable;
	}
}
/*****************************************************************************
* Function   : void CANCCL_vClrEnableSleepFlg (void)
* Description: Called in CANCCL Module Reset container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void CANCCL_vClrEnableSleepFlg(void)
{
	CANCCL_u16Array[CANCCL_nu16EnableSleep] = False;
}

void CANCCL_vTickCntCallBack(void)
{
    if(CANCCL_u16CANRun10msEnable == CANCCL_enResetFlag)
    {
        CANCCL_u16TimeBase_10ms=0;
    }
    else
    {
    	if(CANCCL_u16TimeBase_10ms < 9)
    	{
    		CANCCL_u16TimeBase_10ms++;
    	}
        else
        {
            CANCCL_u16CANRun10msEnable=CANCCL_enRunEnable;
            CANCCL_u16TimeBase_10ms=0;
        }
    }
}


