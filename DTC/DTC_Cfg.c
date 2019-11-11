/*******************************************************************************
| Module Name: DTC process(prcess dianostic code)
| File Name: DTC_Cfg.c
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
#define DTC_CFG
/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
#include "General.h" 

/* Foreign headerfiles */
/* Own headerfiles */
#include "DTC.h" 
#include "DTC_Cfg.h" 
#include "DTC_Private.h" 
#include "DTC_interface.h" 

const DTC_tstProperty DTC_stPropertyTable[DTC_END]={
/*0 - Control Module CAN Bus Off
����CAN���߹ر�*/
{DTC_nBusOff,     {0xC0,0x73,0x00}, 1 , 1, 127, 129, 4, DTC_nCallForeGround, DTC_u8BusOffDtcStsImport},
/*1 - Invalid Data Received From PEPS
PEPS CANͨѶ����*/
{DTC_nErrPEPS,     {0xC5,0x15,0x81}, 1 , 1, 127, 129, 6, DTC_nCallForeGround, DTC_u8ErrPEPSDtcStsImport},
/*2 - Invalid Data Received From EMS
EMS CANͨѶ����*/
{DTC_nErrEMS,     {0xC4,0x01,0x81}, 1 , 1, 127, 129, 6, DTC_nCallForeGround, DTC_u8ErrEMSDtcStsImport},
/*3 - Invalid Data Received From ESC
ESC CANͨѶ����*/
{DTC_nErrESC,     {0xC4,0x16,0x81}, 1 , 1, 127, 129, 6, DTC_nCallForeGround, DTC_u8ErrESCDtcStsImport},
/*4 - Invalid Data Received From IPK
IPK CANͨѶ����*/
{DTC_nErrIPK,     {0xC4,0x23,0x81}, 1 , 1, 127, 129, 6, DTC_nCallForeGround, DTC_u8ErrIPKDtcStsImport},
/*5 - Invalid Data Received From MMI
MMI CANͨѶ����*/
{DTC_nErrMMI,     {0xC4,0x57,0x81}, 1 , 1, 127, 129, 6, DTC_nCallForeGround, DTC_u8ErrMMIDtcStsImport},
/*6 - Invalid Data Received From TBOX
TBOX CANͨѶ����*/
{DTC_nErrTBOX,     {0xC4,0x99,0x81}, 1 , 1, 127, 129, 6, DTC_nCallForeGround, DTC_u8ErrTBOXDtcStsImport},
/*7 - Lost Communication with EMS
��EMSͨ�Ŷ�ʧ*/
{DTC_nLostEMS,     {0xC1,0x00,0x87}, 1 , 1, 127, 129, 6, DTC_nCallForeGround, DTC_u8LostEMSDtcStsImport},
/*8 - Lost Communication with the ESC
��ESCͨ�Ŷ�ʧ*/
{DTC_nLostESC,     {0xC1,0x22,0x87}, 1 , 1, 127, 129, 6, DTC_nCallForeGround, DTC_u8LostESCDtcStsImport},
/*9 - Lost Communication with IPK
��IPKͨ�Ŷ�ʧ*/
{DTC_nLostIPK,     {0xC1,0x55,0x87}, 1 , 1, 127, 129, 6, DTC_nCallForeGround, DTC_u8LostIPKDtcStsImport},
/*10 - Lost Communication  with MMI
��MMIͨ�Ŷ�ʧ*/
{DTC_nLostMMI,     {0xC1,0x56,0x87}, 1 , 1, 127, 129, 6, DTC_nCallForeGround, DTC_u8LostMMIDtcStsImport},
/*11 - Lost Communication with TBOX
��TBOXͨ�Ŷ�ʧ*/
{DTC_nLostTBOX,     {0xC1,0x98,0x87}, 1 , 1, 127, 129, 6, DTC_nCallForeGround, DTC_u8LostTBOXDtcStsImport},
/*12 - Lost Communication with the PEPS
��PEPSͨ�Ŷ�ʧ*/
{DTC_nLostPEPS,     {0xC2,0x14,0x87}, 1 , 1, 127, 129, 6, DTC_nCallForeGround, DTC_u8LostPEPSDtcStsImport},
/*13 - Control Module Input Power Low
����ģ�������ѹ��*/
{DTC_nPowLow,     {0xF0,0x06,0x16}, 1 , 1, 127, 129, 3, DTC_nCallPowFailureDtc, DTC_u8PowLowDtcStsImport},
/*14 - Control Module Input Power High
����ģ�������ѹ��*/
{DTC_nPowHigh,     {0xF0,0x06,0x17}, 1 , 1, 127, 129, 3, DTC_nCallPowFailureDtc, DTC_u8PowHighDtcStsImport},
/*15 - blower voltage feedback is too much differ to target 
�ķ����ѹ������Ŀ��ֵ����*/
{DTC_nBlowerErr,     {0x91,0x80,0x17}, 1 , 1, 108, 148, 3, DTC_nCallBackGround1, DTC_u8BlowerErrDtcStsImport},
/*16 - Driver Temperature door motor short cut to ground
��ʻԱ���¶ȵ��ڵ���Եض�·*/
{DTC_nMix1Gnd,     {0x91,0x81,0x11}, 1 , 1, 108, 148, 3, DTC_nCallBackGround1, DTC_u8Mix1GndDtcStsImport},
/*17 - Driver Temperature door motor short cut to power or open load
��ʻԱ���¶ȵ��ڵ���Ե�Դ��·��·*/
{DTC_nMix1Bat,     {0x91,0x81,0x15}, 1 , 1, 108, 148, 3, DTC_nCallBackGround1, DTC_u8Mix1BatDtcStsImport},
/*18 - Driver Temperature door motor stuck
��ʻԱ���¶ȵ��ڵ����ת*/
{DTC_nMix1Block,     {0x91,0x81,0x71}, 1 , 1, 127, 129, 3, DTC_nCallBackGround1, DTC_u8Mix1BlockDtcStsImport},
/*19 - Passenger Temperature door motor short cut to ground
���ݲ��¶ȵ��ڵ���Եض�·*/
{DTC_nMix2Gnd,     {0x91,0x82,0x11}, 1 , 1, 108, 148, 3, DTC_nCallBackGround1, DTC_u8Mix2GndDtcStsImport},
/*20 - Passenger Temperature door motor short cut to power or open load
���ݲ��¶ȵ��ڵ���Ե�Դ��·��·*/
{DTC_nMix2Bat,     {0x91,0x82,0x15}, 1 , 1, 108, 148, 3, DTC_nCallBackGround1, DTC_u8Mix2BatDtcStsImport},
/*21 - Passenger Temperature door motor stuck
����ʻԱ���¶ȵ��ڵ����ת*/
{DTC_nMix2Block,     {0x91,0x82,0x71}, 1 , 1, 127, 129, 3, DTC_nCallBackGround1, DTC_u8Mix2BlockDtcStsImport},
/*22 - Air distribution motor short cut to ground
����ģʽ���ڵ���Եض�·*/
{DTC_nAirdGnd,     {0x91,0x83,0x11}, 1 , 1, 108, 148, 3, DTC_nCallBackGround1, DTC_u8AirdGndDtcStsImport},
/*23 - Air distribution motor short cut to power or open load
����ģʽ���ڵ���Ե�Դ��·��·*/
{DTC_nAirdBat,     {0x91,0x83,0x15}, 1 , 1, 108, 148, 3, DTC_nCallBackGround1, DTC_u8AirdBatDtcStsImport},
/*24 - Air distribution motor stuck
����ģʽ���ڵ����ת*/
{DTC_nAirdBlock,     {0x91,0x83,0x71}, 1 , 1, 127, 129, 3, DTC_nCallBackGround1, DTC_u8AirdBlockDtcStsImport},
/*25 - Recirculation moto motor short cut to ground
ѭ�����ŵ���Եض�·*/
{DTC_nRfaGnd,     {0x91,0x84,0x11}, 1 , 1, 108, 148, 3, DTC_nCallBackGround1, DTC_u8RfaGndDtcStsImport},
/*26 - Recirculation motor short cut to power or open load
ѭ�����ŵ���Ե�Դ��·��·*/
{DTC_nRfaBat,     {0x91,0x84,0x15}, 1 , 1, 108, 148, 3, DTC_nCallBackGround1, DTC_u8RfaBatDtcStsImport},
/*27 - Recirculation motor stuck
ѭ�����ŵ�������ת*/
{DTC_nRfaBlock,     {0x91,0x84,0x71}, 1 , 1, 127, 129, 3, DTC_nCallBackGround1, DTC_u8RfaBlockDtcStsImport},
/*28 - Evaporator temperatrue sensor short cut to ground
�������¶ȴ������Եض�·*/
{DTC_nEvapGnd,     {0x91,0x86,0x11}, 1 , 1, 108, 148, 4, DTC_nCallBackGround1, DTC_u8EvapGndDtcStsImport},
/*29 - Evaporator temperatrue sensor short cut to power or open load
�������¶ȴ������Ե�Դ��·��·*/
{DTC_nEvapBat,     {0x91,0x86,0x15}, 1 , 1, 108, 148, 4, DTC_nCallBackGround1, DTC_u8EvapBatDtcStsImport},
/*30 - Outside temperatrue sensor short cut to ground
�����¶ȴ������Եض�·*/
{DTC_nOatGnd,     {0x91,0x87,0x11}, 1 , 1, 108, 148, 4, DTC_nCallBackGround1, DTC_u8OatGndDtcStsImport},
/*31 - Outside temperatrue sensor short cut to power or open load
�����¶ȴ������Ե�Դ��·��·*/
{DTC_nOatBat,     {0x91,0x87,0x15}, 1 , 1, 108, 148, 4, DTC_nCallBackGround1, DTC_u8OatBatDtcStsImport},
/*32 - Driver Sunload sensor is short to GND
���ݲ����⴫���� ��·���� */
{DTC_nSunDrGnd,     {0x91,0x8A,0x11}, 1 , 1, 127, 129, 4, DTC_nCallBackGround1, DTC_u8SunDrGndDtcStsImport},
/*33 - Driver Sunload sensor short to power or open load
���ݲ����⴫�����Ե�Դ��·��·*/
{DTC_nSunDrBat,     {0x91,0x8A,0x15}, 1 , 1, 108, 148, 4, DTC_nCallBackGround1, DTC_u8SunDrBatDtcStsImport},
/*34 - Lost Communication with PM2.5
��PM2.5 ͨѶ��ʧ*/
{DTC_nLostPM25,     {0x91,0x8D,0x00}, 1 , 1, 127, 129, 4, DTC_nCallBackGround1, DTC_u8LostPM25DtcStsImport},
/*35 - PM2.5 Hardware errror
PM2.5 Ӳ������*/
{DTC_nPM25HWErr,     {0x91,0x8D,0x96}, 1 , 1, 108, 148, 4, DTC_nCallBackGround1, DTC_u8PM25HWErrDtcStsImport},
/*36 - AQS Hardware errror
AQS Ӳ������*/
{DTC_nAQSHWErr,     {0x91 ,0x88,0x96}, 1 , 1, 108, 148, 4, DTC_nCallBackGround1, DTC_u8AQSHWErrDtcStsImport},
};

#if (DTC_SnapshotSupported == Yes)
const uint8 DTC_SnapshotNumTbl[1]={0x01U};
const uint16 DTC_SnapshotDIDTbl[1][6]={
    {0xDF00,0xDF01,0xDF02,0xDF03,0xDF04,0x631A}
};

#endif

#if (DTC_ExtendDataSupported == Yes)
const uint8 DTC_ExtendedRecordNumTbl[2]={0x02U,0x10U};
#endif


/*****************************************************************************
* EOF: DTC_cfg.c
******************************************************************************/

