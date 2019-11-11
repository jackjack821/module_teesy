/*******************************************************************************
| Module Name: simulation IIC  model
| File Name: S_SPI.h
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
|2014/10/28 Rev 01.00.00     Tan Fumin			The first version  
|2016/01/26 Rev 02.00.00   Tan Fumin				update to be standard for SVN basic code
********************************************************************************/
#ifndef S_SPI_H
#define S_SPI_H

#include "./s_spi_type.h"
#include "./s_spi_cfg.h"

#if S_SPI_CHANNEL_NUMBER>=1

void SPI_vDrvInit_CH1(void);
void SPI_vDrvDeInit_CH1(void);
uint16 SPI_u16TransferData_CH1(void *pOutDataHead, void *pRecDataHead,uint16 u16DataLen);
uint16 SPI_u16SlaveSelect_CH1(uint8 u8SlaveID,uint8 u8ChipSelect_OnOff);

#endif


#if S_SPI_CHANNEL_NUMBER>=2

void SPI_vDrvInit_CH2(void);
void SPI_vDrvDeInit_CH2(void);
uint16 SPI_u16TransferData_CH2(void *pOutDataHead, void *pRecDataHead,uint16 u16DataLen);
uint16 SPI_u16SlaveSelect_CH2(uint8 u8SlaveID,uint8 u8ChipSelect_OnOff);

#endif













#endif


