/*******************************************************************************
| Module Name: Dimmer Control
| File Name: Dim_interface.c
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
#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#include "Rte_internal.h"
/*input interface*/
DIM_tenValueSts DIM_enPowerStatusImport(uint8 *value);
DIM_tenValueSts DIM_enMmiLedInfo1Import(uint16 *value);
DIM_tenValueSts DIM_enMmiLedInfo2Import(uint16 *value);
DIM_tenValueSts DIM_enLuminanceModeImport(uint8 *value);
DIM_tenValueSts DIM_enBacklightLuminanceImport(uint16 *value);
DIM_tenValueSts DIM_enBacklightStatusImport(uint8 *value);
DIM_tenValueSts DIM_enBacklightLuminanceValidImport(uint8 *value);

/*Output interface*/
DIM_tenValueSts DIM_enIndicatorInfoPinExport(uint8 *index,uint8 *value,uint8 *Cfg);
DIM_tenValueSts DIM_enSymbolBacklightPwmDutyExport(DIM_tstState *value);
DIM_tenValueSts DIM_enLcdBacklightPwmDutyExport(DIM_tstState *value);
DIM_tenValueSts DIM_enIndicatorPwmDutyExport(DIM_tstState *value);
void DIM_vOutputUpdate(void);
Std_ReturnType DIM_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord);

#endif
