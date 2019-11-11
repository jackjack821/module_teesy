/*******************************************************************************
| Module Name: Dimmer Control
| File Name: Dim_private.h
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
| 2016-05-18  1.00        Yang Shengli      First implementation
| 2016-06-18  2.00        Yang Shengli      module upgraded
********************************************************************************/

#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H

/*****************************************************************************
*Macro define
******************************************************************************/
#define DIM_SwVersion					    (0x0101u)

#define DIM_u16SwVersion					DIM_au16Array[DIM_nu16SwVersion]
#define DIM_u16ErrorCode                    DIM_au16Array[DIM_nu16ErrorCode]
#define DIM_u16InputPwm                     DIM_au16Array[DIM_nu16InputPwmDuty]
#define DIM_u16LcdPwm                       DIM_au16Array[DIM_nu16LcdPwmDuty]
#define DIM_u16LumMode                      DIM_au16Array[DIM_nu16LumMode]
/*Read bit state*/
#define DIM_vReadBit(array,bit)			(array)&(1<<(bit))
#define DIM_vSetBit(array,bit)			(array)|(1<<(bit))
#define DIM_vClrBit(array,bit)			(array)&(~(1<<(bit)))
#define PortNotUse  (0xFFFFu)
/*Get value from other modules*/
#define DIM_u8GetBacklightLuminaceValid()     (0u)//LIN_stMasteData.u8BackLightLuminanceValid  //LINAPP_u8GetValue(LINAPP_nu8BacklightingLuminaceValidity)
#define DIM_u8GetBacklightStatus(value)       (0u)//Rte_Call_IoHwPortRead_IoHwReadPort_Digital_LightMode_ReadPort_LightMode_Read(value)       //LINAPP_u8GetValue(LINAPP_nu8BacklightingStatus)
#define DIM_u8GetBacklightLuminace()          (0u)//LIN_stMasteData.u8BackLightLuminance       //LINAPP_u8GetValue(LINAPP_nu8BacklightingLuminace)

#define DIM_u16GetPowBattLowFlag()           (POW_u16GetValue(POW_nu16AppLowVoltage))
#define DIM_u16GetPowBattHighFlag()          (POW_u16GetValue(POW_nu16AppHighVoltage))
#define DIM_u16GetMmiLedInfo1()             MMI_u16GetValue(MMI_nu16IndicatorInfo1)
#define DIM_u16GetMmiLedInfo2()             MMI_u16GetValue(MMI_nu16IndicatorInfo2)
#define DIM_u8GetLuminaceMode()             (DIM_u16GetValue(DIM_nu16InputPwmDuty))

#define DIM_nMaxDuty        (1000U)
#define DIM_nMinDuty        (0U)
#define DIM_nDeFaultDuty        (1000U)
#define DIM_u8WaitTime		(100U)
/*Pin Write Define*/
#define DIM_vPinWrite(u8Port,u8Pin,value)  ((((uint16)u8Port << 8) | u8Pin), value)//Rte_IoHwWritePort_DigitalPortWrite((((uint16)u8Port << 8) | u8Pin), value)

/*PPG Channel Define*/
#define DIM_LcdBacklightPwmDutySet(value)  Rte_Call_IoHwPwm_IoHwPwm_SetPwmDuty_LcdBacklight_Set(value)
#define DIM_ShcLIndiPwmDutySet(value)  Rte_Call_IoHwPwm_IoHwPwm_SetPwmDuty_LeftSeatTelltales_Set(value)
#define DIM_ShcRIndiPwmDutySet(value)  Rte_Call_IoHwPwm_IoHwPwm_SetPwmDuty_RightSeatTelltales_Set(value)
#define DIM_FDefIndiPwmDutySet(value)  Rte_Call_IoHwPwm_IoHwPwm_SetPwmDuty_DefTelltales_Set(value)
#define DIM_AutoIndiPwmDutySet(value)  Rte_Call_IoHwPwm_IoHwPwm_SetPwmDuty_AutoTelltales_Set(value)
#define DIM_RecIndiPwmDutySet(value)  Rte_Call_IoHwPwm_IoHwPwm_SetPwmDuty_RecTelltales_Set(value)
#define DIM_RDefIndiPwmDutySet(value)  Rte_Call_IoHwPwm_IoHwPwm_SetPwmDuty_RDefTelltales_Set(value)
#define DIM_MaxAcIndiPwmDutySet(value)  Rte_Call_IoHwPwm_IoHwPwm_SetPwmDuty_AcmaxTelltales_Set(value)
#define DIM_IonIndiPwmDutySet(value)  Rte_Call_IoHwPwm_IoHwPwm_SetPwmDuty_IonTelltales_Set(value)
#define DIM_AcIndiPwmDutySet(value)  Rte_Call_IoHwPwm_IoHwPwm_SetPwmDuty_AcTelltales_Set(value)
#define DIM_DualIndiPwmDutySet(value)  Rte_Call_IoHwPwm_IoHwPwm_SetPwmDuty_DualTelltales_Set(value)

#define DIM_ControlGetPwmWidth(OnOff)  MCU_vTAUxRunCtrl(MCU_mTAUD0_12,OnOff)
#define DIM_ReadIllPort(PortValue)      Rte_Call_IoHwPortRead_IoHwReadPort_Digital_IlldetectPort_ReadPort_IlldetectPort_Read(PortValue)
#define DIM_nFilterFactor                 (1U)    /**/
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef LCD_PRIVATE_H */
/*****************************************************************************
* EOF: Dim_Private.h
******************************************************************************/
