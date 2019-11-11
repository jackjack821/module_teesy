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
����CAN���߹ر�*/
uint8 DTC_u8BusOffDtcStsImport(void);
/*1 - Invalid Data Received From PEPS
PEPS CANͨѶ����*/
uint8 DTC_u8ErrPEPSDtcStsImport(void);
/*2 - Invalid Data Received From EMS
EMS CANͨѶ����*/
uint8 DTC_u8ErrEMSDtcStsImport(void);
/*3 - Invalid Data Received From ESC
ESC CANͨѶ����*/
uint8 DTC_u8ErrESCDtcStsImport(void);
/*4 - Invalid Data Received From IPK
IPK CANͨѶ����*/
uint8 DTC_u8ErrIPKDtcStsImport(void);
/*5 - Invalid Data Received From MMI
MMI CANͨѶ����*/
uint8 DTC_u8ErrMMIDtcStsImport(void);
/*6 - Invalid Data Received From TBOX
TBOX CANͨѶ����*/
uint8 DTC_u8ErrTBOXDtcStsImport(void);
/*7 - Lost Communication with EMS
��EMSͨ�Ŷ�ʧ*/
uint8 DTC_u8LostEMSDtcStsImport(void);
/*8 - Lost Communication with the ESC
��ESCͨ�Ŷ�ʧ*/
uint8 DTC_u8LostESCDtcStsImport(void);
/*9 - Lost Communication with IPK
��IPKͨ�Ŷ�ʧ*/
uint8 DTC_u8LostIPKDtcStsImport(void);
/*10 - Lost Communication  with MMI
��MMIͨ�Ŷ�ʧ*/
uint8 DTC_u8LostMMIDtcStsImport(void);
/*11 - Lost Communication with TBOX
��TBOXͨ�Ŷ�ʧ*/
uint8 DTC_u8LostTBOXDtcStsImport(void);
/*12 - Lost Communication with the PEPS
��PEPSͨ�Ŷ�ʧ*/
uint8 DTC_u8LostPEPSDtcStsImport(void);
/*13 - Control Module Input Power Low
����ģ�������ѹ��*/
uint8 DTC_u8PowLowDtcStsImport(void);
/*14 - Control Module Input Power High
����ģ�������ѹ��*/
uint8 DTC_u8PowHighDtcStsImport(void);
/*15 - blower voltage feedback is too much differ to target 
�ķ����ѹ������Ŀ��ֵ����*/
uint8 DTC_u8BlowerErrDtcStsImport(void);
/*16 - Driver Temperature door motor short cut to ground
��ʻԱ���¶ȵ��ڵ���Եض�·*/
uint8 DTC_u8Mix1GndDtcStsImport(void);
/*17 - Driver Temperature door motor short cut to power or open load
��ʻԱ���¶ȵ��ڵ���Ե�Դ��·��·*/
uint8 DTC_u8Mix1BatDtcStsImport(void);
/*18 - Driver Temperature door motor stuck
��ʻԱ���¶ȵ��ڵ����ת*/
uint8 DTC_u8Mix1BlockDtcStsImport(void);
/*19 - Passenger Temperature door motor short cut to ground
���ݲ��¶ȵ��ڵ���Եض�·*/
uint8 DTC_u8Mix2GndDtcStsImport(void);
/*20 - Passenger Temperature door motor short cut to power or open load
���ݲ��¶ȵ��ڵ���Ե�Դ��·��·*/
uint8 DTC_u8Mix2BatDtcStsImport(void);
/*21 - Passenger Temperature door motor stuck
����ʻԱ���¶ȵ��ڵ����ת*/
uint8 DTC_u8Mix2BlockDtcStsImport(void);
/*22 - Air distribution motor short cut to ground
����ģʽ���ڵ���Եض�·*/
uint8 DTC_u8AirdGndDtcStsImport(void);
/*23 - Air distribution motor short cut to power or open load
����ģʽ���ڵ���Ե�Դ��·��·*/
uint8 DTC_u8AirdBatDtcStsImport(void);
/*24 - Air distribution motor stuck
����ģʽ���ڵ����ת*/
uint8 DTC_u8AirdBlockDtcStsImport(void);
/*25 - Recirculation moto motor short cut to ground
ѭ�����ŵ���Եض�·*/
uint8 DTC_u8RfaGndDtcStsImport(void);
/*26 - Recirculation motor short cut to power or open load
ѭ�����ŵ���Ե�Դ��·��·*/
uint8 DTC_u8RfaBatDtcStsImport(void);
/*27 - Recirculation motor stuck
ѭ�����ŵ�������ת*/
uint8 DTC_u8RfaBlockDtcStsImport(void);
/*28 - Evaporator temperatrue sensor short cut to ground
�������¶ȴ������Եض�·*/
uint8 DTC_u8EvapGndDtcStsImport(void);
/*29 - Evaporator temperatrue sensor short cut to power or open load
�������¶ȴ������Ե�Դ��·��·*/
uint8 DTC_u8EvapBatDtcStsImport(void);
/*30 - Outside temperatrue sensor short cut to ground
�����¶ȴ������Եض�·*/
uint8 DTC_u8OatGndDtcStsImport(void);
/*31 - Outside temperatrue sensor short cut to power or open load
�����¶ȴ������Ե�Դ��·��·*/
uint8 DTC_u8OatBatDtcStsImport(void);
/*32 - Driver Sunload sensor is short to GND
���ݲ����⴫���� ��·���� */
uint8 DTC_u8SunDrGndDtcStsImport(void);
/*33 - Driver Sunload sensor short to power or open load
���ݲ����⴫�����Ե�Դ��·��·*/
uint8 DTC_u8SunDrBatDtcStsImport(void);
/*34 - Lost Communication with PM2.5
��PM2.5 ͨѶ��ʧ*/
uint8 DTC_u8LostPM25DtcStsImport(void);
/*35 - PM2.5 Hardware errror
PM2.5 Ӳ������*/
uint8 DTC_u8PM25HWErrDtcStsImport(void);
/*36 - AQS Hardware errror
AQS Ӳ������*/
uint8 DTC_u8AQSHWErrDtcStsImport(void);

uint8 DTC_u8K15StsImport(void);
#endif

/*****************************************************************************
* EOF: DTC_interface.h
******************************************************************************/

