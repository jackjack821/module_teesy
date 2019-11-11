/*******************************************************************************
| Module Name: simulation IIC  model
| File Name: S_IIC_cfg.h
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
|Tan Fumin                       Desay SV Automotive Co., Ltd
|
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver        	Author               Description
| ----------  -------  -------------  -------------------------------------------------
|2014/10/28  Rev 00.00.00    Tan Fumin				The first version  
| 2015/06/09 Rev 01.00.00   Tan Fumin				update for MISRA C rules
| 2016/01/26 Rev 02.00.00   Tan Fumin				update to be standard for SVN basic code
********************************************************************************/

#include "MCU_CFG.h"	/*for example*/
#include "Rte_internal.h"

#ifndef S_IIC_CFG_H
#define S_IIC_CFG_H

#define S_IIC_CHANNEL_NUMBER	1U

#define S_IIC_DataField_LSB		1U
#define S_IIC_DataField_MSB	2U


#if S_IIC_CHANNEL_NUMBER>=1U

#define S_IIC_CH1_Enable	1U

#define S_IIC_CH1_DataField		(S_IIC_DataField_MSB)/*this value always = MSB*/
#if 0
#define S_IIC_CH1_AckWaitCnt	100U						/*for example*/
#define S_IIC_CH1_DelayCnt		10U						/*for example*/

#define S_IIC_CH1_SetSCLHigh()			(P0|=(1 << 12))//(Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_IicScl_Write(1u))	/*for example*/
#define S_IIC_CH1_SetSCLLow()			(P0&=~(1 << 12))//(Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_IicScl_Write(0u))	/*for example*/
#define S_IIC_CH1_SetSCLOutputMode()	(PM0&=~(1 << 12))//(Rte_Call_IoHwPinCfg_IoHwPinDirectCfg_SetPinDirectCfg_Set(0x000C,0))	/*for example*/

#define S_IIC_CH1_GetSDAValue()	((P0 >> 11)&1)//	(Rte_Call_IoHwPortRead_IoHwReadPort_Digital_IicSdaPort_ReadPort_IicSdaPort_Read(Value))		/*for example*/
#define S_IIC_CH1_SetSDAHigh()		(P0|=(1 << 11))//	(Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_IicSda_Write(1u))	/*for example*/
#define S_IIC_CH1_SetSDALow()		(P0&=~(1 << 11))//	(Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_IicSda_Write(0u))	/*for example*/
#define S_IIC_CH1_SetSDAInputMode()	(PM0|=(1 << 11))//(Rte_Call_IoHwPinCfg_IoHwPinDirectCfg_SetPinDirectCfg_Set(0x000B,1))	/*for example*/
#define S_IIC_CH1_SetSDAOutputMode()	(PM0&=~(1 << 11))//(Rte_Call_IoHwPinCfg_IoHwPinDirectCfg_SetPinDirectCfg_Set(0x000B,0))	/*for example*/

/*======do not edit below this line =======*/
/*Not Edit*/
/*Not Edit*/#define S_IIC_CH1_WaitAck()	do{uint16 u16WaitAckCnt=S_IIC_CH1_AckWaitCnt;S_IIC_CH1_SetSDAInputMode();\
/*Not Edit*/							while((u16WaitAckCnt !=0u)&& S_IIC_CH1_GetSDAValue()!=0){u16WaitAckCnt--;}\
/*Not Edit*/							}while(0)
#else
#define S_IIC_CH1_AckWaitCnt	 100U						/*for example*/
#define S_IIC_CH1_DelayCnt		10U						/*for example*/

#define S_IIC_CH1_SetSCLHigh()			(Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_IicScl_Write(1u))	/*for example*/
#define S_IIC_CH1_SetSCLLow()			(Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_IicScl_Write(0u))	/*for example*/
#define S_IIC_CH1_SetSCLOutputMode()	(Rte_Call_IoHwPinCfg_IoHwPinDirectCfg_SetPinDirectCfg_Set(0x0a03,0))	/*for example*/

#define S_IIC_CH1_GetSDAValue(Value)	    (Rte_Call_IoHwPortRead_IoHwReadPort_Digital_IicSdaPort_ReadPort_IicSdaPort_Read(Value))		/*for example*/
#define S_IIC_CH1_SetSDAHigh()		(Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_IicSda_Write(1u))	/*for example*/
#define S_IIC_CH1_SetSDALow()		(Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_IicSda_Write(0u))	/*for example*/
#define S_IIC_CH1_SetSDAInputMode()	(Rte_Call_IoHwPinCfg_IoHwPinDirectCfg_SetPinDirectCfg_Set(0x0a02,1))	/*for example*/
#define S_IIC_CH1_SetSDAOutputMode()	(Rte_Call_IoHwPinCfg_IoHwPinDirectCfg_SetPinDirectCfg_Set(0x0a02,0))	/*for example*/

/*======do not edit below this line =======*/
/*Not Edit*/
/*Not Edit*/#define S_IIC_CH1_WaitAck()	do{uint16 u16WaitAckCnt=S_IIC_CH1_AckWaitCnt;uint16 Value;S_IIC_CH1_SetSDAInputMode();\
                                           S_IIC_CH1_GetSDAValue(&Value);\
/*Not Edit*/							while((u16WaitAckCnt !=0u) && (Value !=0U)){u16WaitAckCnt--;}\
/*Not Edit*/							}while(0)
/*Not Edit*/
#endif
/*Not Edit*/#define S_IIC_CH1_ClkDelay()	do{uint16 u16Wait=S_IIC_CH1_DelayCnt;while(u16Wait !=0u){u16Wait--;}}while(0)
/*Not Edit*/
/*Not Edit*/#define S_IIC_CH1_Init()	do{	S_IIC_CH1_SetSCLLow();/*set output Low level for ready SDA to output*/\
/*Not Edit*/							S_IIC_CH1_SetSCLOutputMode();/*set Sck input first to avoid Pin level change*/\
/*Not Edit*/							S_IIC_CH1_SetSDAHigh();/*output SDA high level*/\
/*Not Edit*/							S_IIC_CH1_SetSDAOutputMode();\
/*Not Edit*/							S_IIC_CH1_SetSCLHigh(); /*output SCK high level*/\
/*Not Edit*/						}while(0)
/*Not Edit*/						
/*Not Edit*/#define S_IIC_CH1_SetReady()	do{S_IIC_CH1_Init();IIC_u8CH1_Satus=(uint8)IIC_enReady;}while(0)
/*Not Edit*/#define S_IIC_CH1_Exit()			do{S_IIC_CH1_Init();IIC_u8CH1_Satus=(uint8)IIC_enReady;}while(0)
/*Not Edit*/
/*======do not edit above this line =======*/

#endif






#endif
