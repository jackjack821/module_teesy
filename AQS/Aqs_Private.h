/*******************************************************************************
| Module Name: AQS Control
| File Name: Aqs_Private.h
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
| 2016-02-25  1.00        Yang Shengli      First implementation
********************************************************************************/

#ifndef AQS_PRIVATE_H
#define AQS_PRIVATE_H

/*****************************************************************************
*Macro define
******************************************************************************/
#define AQS_nSwVersion					(0xA2u)

#define AQS_u8SwVersion					AQS_au8Array[AQS_nu8SwVersion]
#define AQS_u8Valid						AQS_au8Array[AQS_nu8Valid]
#define AQS_u8ErrorCode				AQS_au8Array[AQS_nu8ErrorCode]
#define AQS_u8State					AQS_au8Array[AQS_nu8State]
#define AQS_u8AirBadTime			AQS_au8Array[AQS_nu8AirBadTime]
#define AQS_u16PwmValue              AQS_au16Array[AQS_nu16PwmValue]    /*Modify by LT,20160713*/
#define AQS_u8AirBadPercent			AQS_au8Array[AQS_nu8AirBadPercent]

#define AQS_vSetBit(Value,bit)				(Value |= (1 << bit))
#define AQS_ControlGetAqsSensorPwm(OnOff)   MCU_vTAUxRunCtrl(MCU_mTAUJ1_2,OnOff)
#define AQS_ReadAqsOutsidePort(PortValue)   Rte_Call_IoHwPortRead_IoHwReadPort_Digital_AqsdetectPort_ReadPort_AqsdetectPort_Read(PortValue)
#define AQS_u8GetVelValid()                 VEL_u8GetValue(VEL_nu8Valid)
#define AQS_u16GetVelValue()                VEL_u16GetValue(VEL_nu16RfaValue)

#define AQS_SetCurRecordBad()	(AQS_au8Record[AQS_u8RecordIndex >> 3] |= 1 << (AQS_u8RecordIndex & 7))
#define AQS_SetCurRecordGood()	(AQS_au8Record[AQS_u8RecordIndex >> 3] &= ~(1 << (AQS_u8RecordIndex & 7)))
#define AQS_ClrLastCycRecord()	(AQS_au8Record[AQS_u8RecordIndex >> 3] &= ~(1 << (AQS_u8RecordIndex & 7)))
#define AQS_LastCycRecord()	((AQS_au8Record[AQS_u8RecordIndex >> 3] >> (AQS_u8RecordIndex & 7)) & 1)

#define AQS_FilterTime AQS_u8Group1AirFilterTime
#define AQS_au16VelFreshPercent_X AQS_au16Group1AqsFreshSwitchPoint_X
#define AQS_au16VelFreshPercent_Y AQS_au16Group1AqsFreshSwitchPoint_Y
#define AQS_au16VelFreshPercentLen AQS_nAqsFreshSwitchPointTbl_Len

#define AQS_au16VelRecPercent_X AQS_au16Group1AqsRecSwitchPoint_X
#define AQS_au16VelRecPercent_Y AQS_au16Group1AqsRecSwitchPoint_Y
#define AQS_au16VelRecPercentLen AQS_nAqsRecSwitchPointTbl_Len
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef AQS_PRIVATE_H */
/*****************************************************************************
* EOF: Aqs_Private.h
******************************************************************************/
