/*******************************************************************************
| Module Name: CAN CCL
| File Name: LINCCL.c
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
#define LINCCL_C                          /* Name of the Module                */
/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
//#include "iodefine.h"
#include "general.h"
/* Foreign headerfiles */
#include "v_inc.h"
#include "LINAPP.h"
#include "LINNM.h"
/* Own headerfiles */
#include "LINCCL.h"
#include "LINCCL_cfg.h"
/* Define static variable */
static uint16 LINCCL_u16Array[LINCCL_nu16Max];
static uint16 LINCCL_u16TimeBase_10ms;
static uint16 LINCCL_u16TimeBase_20ms;
static uint16 LINCCL_u16LINRun1msEnable;
static uint16 LINCCL_u16LINRun10msEnable;
static uint16 LINCCL_u16LINRun20msEnable;
/*****************************************************************************
* Function   :  LINCCL_u16GetValue
* Description: Called in anywhere
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
uint16 LINCCL_u16GetValue(LINCCL_tenu16VarNumber enIndex)
{
	if(enIndex < LINCCL_nu16Max)
	{
		return (LINCCL_u16Array[enIndex]);
	}
	else
	{
		return (LINCCL_u16Array[LINCCL_nu16Max-1]);
	}
}
/*****************************************************************************
* Function   : void LINNM_vReset (void)
* Description: Called OS Reset container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void LINCCL_vReset(void)
{
	LINNM_vReset();
	LINAPP_vReset();
	LINCCL_u16Array[LINCCL_nu16EnableSleep] = False;
	LINCCL_u16TimeBase_10ms = 0;
	LINCCL_u16TimeBase_20ms = 0;
    LINCCL_u16LINRun1msEnable=True;
    LINCCL_u16LINRun10msEnable=True;
    LINCCL_u16LINRun20msEnable=True;
}

/*****************************************************************************
* Function   : void LINCCL_vTask_10ms (void)
* Description: Called in LINCCL Module Reset container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void LINCCL_vTask_10ms(void)
{
    LINNM_vMain_10ms();
    LINAPP_vMain_10ms();
	if(LINNM_u16GetValue(LINNM_nu16NmState)==LINNM_nSleep)
	{
		LINCCL_u16Array[LINCCL_nu16EnableSleep] = True;
	}
}
/*****************************************************************************
* Function   : void LINCCL_vTask_20ms (void)
* Description: Called in LINCCL Module Reset container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void LINCCL_vTask_20ms(void)
{
	LINNM_vMain_20ms();
}
/*****************************************************************************
* Function   : void LINCCL_vTask_1ms (void)
* Description: Called in LINCCL Module Reset container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void LINCCL_vTask_1ms(void)
{
	LINNM_vMain_1ms();
}
/*****************************************************************************
* Function   : void LINCCL_vMain (void)
* Description: Called in OS 1ms Container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void LINCCL_vMain(void)
{
    if(LINCCL_u16LINRun1msEnable==True)
    {
    	LINNM_vMain_1ms();
        LINCCL_u16LINRun1msEnable=False;
    }
    if(LINCCL_u16LINRun10msEnable==True)
    {
        LINCCL_vTask_10ms();
        LINCCL_u16LINRun10msEnable=False;
    }
    if(LINCCL_u16LINRun20msEnable==True)
    {
        LINCCL_vTask_20ms();
        LINCCL_u16LINRun20msEnable=False;
    }

}
/*****************************************************************************
* Function   : void LINCCL_vTask_1ms (void)
* Description: Called in LINCCL Module Reset container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void LINCCL_vClrEnableSleepFlg(void)
{
	LINCCL_u16Array[LINCCL_nu16EnableSleep] = False;
}

void LINCCL_vTickCntCallBack(void)
{
	/*1ms*/
	LINCCL_u16LINRun1msEnable=True;
	/*10ms*/
	if(LINCCL_u16TimeBase_10ms < 9)
	{
		LINCCL_u16TimeBase_10ms++;
	}
	else
	{
        LINCCL_u16LINRun10msEnable=True;
        LINCCL_u16TimeBase_10ms=0;
	}
	/*20ms*/
	if(LINCCL_u16TimeBase_20ms < 19)
	{
		LINCCL_u16TimeBase_20ms++;
	}
	else
	{
        LINCCL_u16LINRun20msEnable=True;
        LINCCL_u16TimeBase_20ms=0;
	}
}


