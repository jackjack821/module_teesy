/********************************************************************************
| Module Name: DTC process(prcess dianostic code)
| File Name: DTC_Interface.h
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
| .Date; 2018-6-5
| .Update Time; 14:49:42
| .DTCDefineList; D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\DTC\DTCGen\FE-5DB&7DA DTC list_20180605.xlsm
|-------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Name                                  Company
| ---------------------     ---------------------------------------
| Sui Yanchun                        Desay SV Automotive Co., Ltd
| Zhang Shuncong                     Desay SV Automotive Co., Ltd
| Li Jiaye                           Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2014-11-24  1.00        Sui Yanchun       update the DTC module
| 2015-12-56  2.00        Lin Tao           update for the MISRA C
| 2017-07-21  3.00        Li Jiaye          interface update

********************************************************************************/
/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef DTC_Interface_H
#define DTC_Interface_H
/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
#include "General.h" 

/* Foreign headerfiles */
/* Own headerfiles */
#include "DTC_Private.h" 


/*****************************************************************************
* MACROS
*
* Functional macros defined.
******************************************************************************/


/*****************************************************************************
* MACROS
*
* In this section declare
* - all macros used in the configuration file and C file.
******************************************************************************/


/*****************************************************************************
* MODULE CONFIGURATION DEFINITIONS
*
* In this section declare
* - all module configuration defines which should be generated.
******************************************************************************/

/*****************************************************************************
* MODULE CONFIGURATION DECLARATIONS
*
* In this section declare
* - module variable declarations for the variable in the cfg.c file, which will be used in module
     functions.
******************************************************************************/

uint16 DTC_u16GetIgOnDelayTmr(void);
/*0 - Control Module CAN Bus Off
控制CAN总线关闭*/
uint8 DTC_u8BusOffDtcStsImport(void);
/*1 - Invalid Data Received From PEPS
PEPS CAN通讯错误*/
uint8 DTC_u8ErrPEPSDtcStsImport(void);
/*2 - Invalid Data Received From EMS
EMS CAN通讯错误*/
uint8 DTC_u8ErrEMSDtcStsImport(void);
/*3 - Invalid Data Received From ESC
ESC CAN通讯错误*/
uint8 DTC_u8ErrESCDtcStsImport(void);
/*4 - Invalid Data Received From IPK
IPK CAN通讯错误*/
uint8 DTC_u8ErrIPKDtcStsImport(void);
/*5 - Invalid Data Received From MMI
MMI CAN通讯错误*/
uint8 DTC_u8ErrMMIDtcStsImport(void);
/*6 - Invalid Data Received From TBOX
TBOX CAN通讯错误*/
uint8 DTC_u8ErrTBOXDtcStsImport(void);
/*7 - Lost Communication with EMS
与EMS通信丢失*/
uint8 DTC_u8LostEMSDtcStsImport(void);
/*8 - Lost Communication with the ESC
与ESC通信丢失*/
uint8 DTC_u8LostESCDtcStsImport(void);
/*9 - Lost Communication with IPK
与IPK通信丢失*/
uint8 DTC_u8LostIPKDtcStsImport(void);
/*10 - Lost Communication  with MMI
与MMI通信丢失*/
uint8 DTC_u8LostMMIDtcStsImport(void);
/*11 - Lost Communication with TBOX
与TBOX通信丢失*/
uint8 DTC_u8LostTBOXDtcStsImport(void);
/*12 - Lost Communication with the PEPS
与PEPS通信丢失*/
uint8 DTC_u8LostPEPSDtcStsImport(void);
/*13 - Control Module Input Power Low
控制模块输入电压低*/
uint8 DTC_u8PowLowDtcStsImport(void);
/*14 - Control Module Input Power High
控制模块输入电压高*/
uint8 DTC_u8PowHighDtcStsImport(void);
/*15 - blower voltage feedback is too much differ to target 
鼓风机电压反馈与目标值相差大*/
uint8 DTC_u8BlowerErrDtcStsImport(void);
/*16 - Driver Temperature door motor short cut to ground
驾驶员侧温度调节电机对地短路*/
uint8 DTC_u8Mix1GndDtcStsImport(void);
/*17 - Driver Temperature door motor short cut to power or open load
驾驶员侧温度调节电机对电源短路或开路*/
uint8 DTC_u8Mix1BatDtcStsImport(void);
/*18 - Driver Temperature door motor stuck
驾驶员侧温度调节电机堵转*/
uint8 DTC_u8Mix1BlockDtcStsImport(void);
/*19 - Passenger Temperature door motor short cut to ground
副驾侧温度调节电机对地短路*/
uint8 DTC_u8Mix2GndDtcStsImport(void);
/*20 - Passenger Temperature door motor short cut to power or open load
副驾侧温度调节电机对电源短路或开路*/
uint8 DTC_u8Mix2BatDtcStsImport(void);
/*21 - Passenger Temperature door motor stuck
副驾驶员侧温度调节电机堵转*/
uint8 DTC_u8Mix2BlockDtcStsImport(void);
/*22 - Air distribution motor short cut to ground
出风模式调节电机对地短路*/
uint8 DTC_u8AirdGndDtcStsImport(void);
/*23 - Air distribution motor short cut to power or open load
出风模式调节电机对电源短路或开路*/
uint8 DTC_u8AirdBatDtcStsImport(void);
/*24 - Air distribution motor stuck
出风模式调节电机堵转*/
uint8 DTC_u8AirdBlockDtcStsImport(void);
/*25 - Recirculation moto motor short cut to ground
循环风门电机对地短路*/
uint8 DTC_u8RfaGndDtcStsImport(void);
/*26 - Recirculation motor short cut to power or open load
循环风门电机对电源短路或开路*/
uint8 DTC_u8RfaBatDtcStsImport(void);
/*27 - Recirculation motor stuck
循环风门电机电机堵转*/
uint8 DTC_u8RfaBlockDtcStsImport(void);
/*28 - Evaporator temperatrue sensor short cut to ground
蒸发器温度传感器对地短路*/
uint8 DTC_u8EvapGndDtcStsImport(void);
/*29 - Evaporator temperatrue sensor short cut to power or open load
蒸发器温度传感器对电源短路或开路*/
uint8 DTC_u8EvapBatDtcStsImport(void);
/*30 - Outside temperatrue sensor short cut to ground
车外温度传感器对地短路*/
uint8 DTC_u8OatGndDtcStsImport(void);
/*31 - Outside temperatrue sensor short cut to power or open load
车外温度传感器对电源短路或开路*/
uint8 DTC_u8OatBatDtcStsImport(void);
/*32 - Driver Sunload sensor is short to GND
主驾侧阳光传感器 短路到地 */
uint8 DTC_u8SunDrGndDtcStsImport(void);
/*33 - Driver Sunload sensor short to power or open load
主驾侧阳光传感器对电源短路或开路*/
uint8 DTC_u8SunDrBatDtcStsImport(void);
/*34 - Lost Communication with PM2.5
与PM2.5 通讯丢失*/
uint8 DTC_u8LostPM25DtcStsImport(void);
/*35 - PM2.5 Hardware errror
PM2.5 硬件故障*/
uint8 DTC_u8PM25HWErrDtcStsImport(void);
/*36 - AQS Hardware errror
AQS 硬件故障*/
uint8 DTC_u8AQSHWErrDtcStsImport(void);

uint8 DTC_u8K15StsImport(void);
#endif

/*****************************************************************************
* EOF: DTC_interface.h
******************************************************************************/

