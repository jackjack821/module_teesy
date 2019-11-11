/*******************************************************************************
| Module Name: simulation IIC  model
| File Name: S_SPI_Cfg.c
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

#include "s_spi_cfg.h"


#if S_SPI_CHANNEL_NUMBER>=1
/*****************************************************************************
 Function  : SPI_vSlaveSelect												 
 Description   :select a slave channle for communication control
 
 In Parameter: 
 			u8SlaveID: slave index in CH1 SPI channel
 			u8ChipSelect: slave chip select level, CSx = High or Low
 			
Return Value:
 			NULL
 			
 NOTE: 		
			this function will implement by user to control CS pin or other things
			
*****************************************************************************/
uint16 SPI_u16SlaveSelect_CH1(uint8 u8SlaveID,uint8 u8ChipSelect_OnOff)
{
	//HAL_PinConfig(8,1, HAL_mPinOutput);
	//HAL_PinWrite(8,1,u8ChipSelect_OnOff);
    Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_SbcCs_Write((DigitalLevel)u8ChipSelect_OnOff);
    return 1u;
}

#endif


#if S_SPI_CHANNEL_NUMBER>=2
/*****************************************************************************
 Function  : SPI_vSlaveSelect												 
 Description   :select a slave channle for communication control
 
 In Parameter: 
 			u8SlaveID: slave index in CH1 SPI channel
 			u8ChipSelect: slave chip select level, CSx = High or Low
 			
Return Value:
 			NULL
 			
 NOTE: 		
			this function will implement by user to control CS pin or other things
			
*****************************************************************************/
uint16 SPI_u16SlaveSelect_CH2(uint8 u8SlaveID,uint8 u8ChipSelect_OnOff)
{

	//HAL_PinConfig(8,9, HAL_mPinOutput);
	//HAL_PinWrite(8,9,u8ChipSelect_OnOff);
	Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_NcvCs_Write((DigitalLevel)u8ChipSelect_OnOff);
    return 1u;
}

#endif

