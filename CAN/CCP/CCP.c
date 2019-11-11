/*******************************************************************************
| Module Name: Climate Calibration Processing Module. 
| File Name: CCP.c
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
| Zhong bin                       Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date            Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
 13/8/2012        V1.0(0xA0)           Zhong Bin           Creation.
 16/12/2015       V1.1(0xA1)           Lin Tao             First release for J72L  
 12/12/2015       V1.2(0xA2)           Lin Tao             Change the Calibration test frame as SW-Test request  
 24/8/2016       V1.3(0xA2)            Lin Tao             
 1.Add the CCP_vReadInf from 0 to 0x7F
 2.update the PTS
|-------------------------------------------------------------------------------
|               ISSUE  List 
|-------------------------------------------------------------------------------
1.EEXT intreface--EEP_u8WriteDataWait
*****************************************************************************/

#define CCP_C                         /* name of the module                */


/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* system-headerfiles */
#include "general.h"
//#include "Hal.h"
//#include "FLS_Drv.h"
//#include "KEY.h"
/* foreign headerfiles */
#include "Rte.h"
#include "Can_inc.h"
#include "Can_par.h"
//#include "REV.h"
//#include "PSV.h" 


#include "SUN_interface.h"
#include "CCS.h"
#include "CTS_stddef.h"
#include "CTS_import.h"
#include "OAT_interface.h"
#include "KEY_interface.h"
//#include "ICT_interface.h"
#include "HCT_interface.h"
#include "vel_interface.h"
/* own headerfiles */
#include "Ccp.h"
#include "Ccp_cfg.h"

static uint8 CCP_au8Array[CCP_nu8Max];
/* Define the bit variables */
static uint8 CCP_u8BitArray[CCP_nbiByteMax];
static tunBitByte CCP_unLocalFlage;
const uint8 u8Passwords[PASSWORDNUM] = {'D','E','S','A','Y','S','V'};

#if(CarConfiguration == High_End)
const char  CCP_ModelName[5] = {'F','C',0x22,0x79,0x41};
#elif(CarConfiguration == Mid_End)
const char  CCP_ModelName[5] = {'F','C',0x22,0x69,0x41};
#elif(CarConfiguration == Low_End)
const char  CCP_ModelName[5] = {'F','C',0x22,0x59,0x41};
#else
const char  CCP_ModelName[5] = {'F','C',0x22,0x87,0x41};
#endif
  
/* define the static variables */
static uint8 CCP_u8CidSequence;
static CCP_tenModeType CCP_enWorkingMode;
/* Define access eeprom static variable */
static CCP_tenEepAccessType CCP_u8EepAccessType;
static CCP_tenFrameType CCP_u8FrameType;
static uint16 CCP_u16EepAddress;
static uint16 CCP_u16EepDataLength;
static uint16 CCP_u16EepDataPtr;
static CCP_tstGlobals CCP_stGlobals;
static CCP_tenAckType CCP_u8AckType;
static uint8 CCP_u8TimeCounter;
/* Define access eeprom static variable end */
/*- Tx data, data to be sent. -*/
static tstCcpdata *CCP_stDataPtr;
/* Rx command.*/
static tstCcpdata *CCP_tstCmdPtr;
static CCP_tenCaliTxType CCP_tstCaliTxType;
static CCP_tenDelayResCmd   CCP_tstResDelayCmd;
static uint8   CCP_u8ResDelayTime = 0;





static void CCP_vCalibrationTask(void);
/* Define the static function this module */
static void CCP_vSessionMode(void);
static void CCP_vExitCcp(void);
static void CCP_vReadByCommonID (void);
static void CCP_vReadMemoryByAddress (void);
static void CCP_vSafeAccess (void);
static void CCP_vIOControlByLocalID (void);
static void CCP_vWriteMemoryByAddress (void);
static void CCP_vReadCalibrationFrame(void);
static void CCP_vNegativeResphone(uint8 u8ErrorCode);
/* Define eeprom access function */
static void CCP_vClrGlobalBuff (uint8 u8RW);
static void CCP_vReadEepromAccess(void);
static void CCP_vStartTxFrameHandling(void);
static void CCP_vMidTxFrameHandling(void);
static void CCP_vEndTxFrameHandling(void);
static void CCP_vWriteEepromAccess(void);
static void CCP_vStartRxFrameHandling(void);
static void CCP_vMidRxFrameHandling(void);
static void CCP_vEndRxFrameHandling(void);
static uint8 CCP_vCalChecksum(uint8 u8RW);
static uint32 CCP_u32KeyBitChange(uint32 InValue,uint32 OutValue,uint32 InPos,uint32 OutPos);


/* Define clear ccp function content */
static void CCP_ClearAllFunction(void);/*Release Warning,161024*/
/* Define CCP control function */
static void CCP_vIoControl_10(void);
static void CCP_vIoControl_11(void);
static void CCP_vIoControl_12(void);
static void CCP_vIoControl_13(void);
static void CCP_vIoControl_14(void);
static void CCP_vIoControl_15(void);
static void CCP_vIoControl_16(void);
static void CCP_vIoControl_17(void);
static void CCP_vIoControl_18(void);
static void CCP_vIoControl_19(void);
static void CCP_vIoControl_1A(void);
static void CCP_vIoControl_1B(void);
static void CCP_vIoControl_1C(void);
static void CCP_vIoControl_1D(void);
static void CCP_vIoControl_1E(void);
static void CCP_vIoControl_1F(void);
static void CCP_vIoControl_20(void);
static void CCP_vIoControl_21(void);
static void CCP_vIoControl_22(void);
static void CCP_vIoControl_23(void);
static void CCP_vIoControl_24(void);
static void CCP_vIoControl_25(void);
static void CCP_vIoControl_26(void);
static void CCP_vIoControl_27(void);
static void CCP_vIoControl_28(void);
static void CCP_vIoControl_29(void);
static void CCP_vIoControl_2A(void);
static void CCP_vIoControl_2B(void);
static void CCP_vIoControl_2C(void);
static void CCP_vIoControl_2D(void);
static void CCP_vIoControl_2E(void);
static void CCP_vIoControl_2F(void);
static void CCP_vIoControl_30(void);
static void CCP_vIoControl_31(void);
static void CCP_vIoControl_32(void);
static void CCP_vIoControl_33(void);
static void CCP_vIoControl_34(void);
static void CCP_vIoControl_35(void);
static void CCP_vIoControl_36(void);
static void CCP_vIoControl_37(void);
static void CCP_vIoControl_38(void);
static void CCP_vIoControl_39(void);
static void CCP_vIoControl_3A(void);
static void CCP_vIoControl_3B(void);
static void CCP_vIoControl_3C(void);
static void CCP_vIoControl_3D(void);
static void CCP_vIoControl_3E(void);
static void CCP_vIoControl_3F(void);
static void CCP_vIoControl_40(void);
static void CCP_vIoControl_41(void);
static void CCP_vIoControl_42(void);
static void CCP_vIoControl_43(void);
static void CCP_vIoControl_44(void);
static void CCP_vIoControl_45(void);
static void CCP_vIoControl_46(void);
static void CCP_vIoControl_47(void);
static void CCP_vIoControl_48(void);
static void CCP_vIoControl_49(void);
static void CCP_vIoControl_4A(void);
static void CCP_vIoControl_4B(void);
static void CCP_vIoControl_4C(void);
static void CCP_vIoControl_4D(void);
static void CCP_vIoControl_4E(void);
static void CCP_vIoControl_4F(void);
static void CCP_vIoControl_50(void);
static void CCP_vIoControl_51(void);
static void CCP_vIoControl_52(void);
static void CCP_vIoControl_53(void);
static void CCP_vIoControl_54(void);
static void CCP_vIoControl_55(void);
static void CCP_vIoControl_56(void);
static void CCP_vIoControl_57(void);
static void CCP_vIoControl_58(void);
static void CCP_vIoControl_59(void);
static void CCP_vIoControl_5A(void);
static void CCP_vIoControl_5B(void);
static void CCP_vIoControl_5C(void);
static void CCP_vIoControl_5D(void);
static void CCP_vIoControl_5E(void);
static void CCP_vIoControl_5F(void);
static void CCP_vIoControl_60(void);
static void CCP_vIoControl_61(void);
static void CCP_vIoControl_62(void);
static void CCP_vIoControl_63(void);
/* Define PTS control function */
static void CCP_vPtsControl_21(void);
static void CCP_vPtsControl_22(void);
static void CCP_vPtsControl_23(void);
static void CCP_vPtsControl_24(void);
static void CCP_vPtsControl_25(void);
static void CCP_vPtsControl_26(void);
static void CCP_vPtsControl_27(void);
static void CCP_vPtsControl_28(void);
static void CCP_vPtsControl_29(void);
static void CCP_vPtsControl_2A(void);
static void CCP_vPtsControl_2B(void);
static void CCP_vPtsControl_2C(void);
static void CCP_vPtsControl_2D(void);
static void CCP_vPtsControl_2E(void);
static void CCP_vPtsControl_2F(void);
/* Define PTS Read function */
static void CCP_vPtsReadInf_01(void);
static void CCP_vPtsReadInf_02(void);
static void CCP_vPtsReadInf_03(void);
static void CCP_vPtsReadInf_04(void);
static void CCP_vPtsReadInf_05(void);
static void CCP_vPtsReadInf_06(void);
static void CCP_vPtsReadInf_07(void);
static void CCP_vPtsReadInf_08(void);
static void CCP_vPtsReadInf_09(void);
static void CCP_vPtsReadInf_0A(void);
static void CCP_vPtsReadInf_0B(void);
static void CCP_vPtsReadInf_0C(void);
static void CCP_vPtsReadInf_0D(void);
static void CCP_vPtsReadInf_0E(void);
static void CCP_vPtsReadInf_0F(void);
static void CCP_vPtsReadModelName(void);
static void CCP_vPtsReadSerialNum(void);
static void CCP_vPtsReadFactoryNum(void);
static void CCP_vPtsReadDate(void);
static void CCP_vPtsReadProductionLine(void);
static void CCP_vPtsReadSerialByDay(void);
static void CCP_vPtsReadInternalHWVer(void);
static void CCP_vPtsReadExternalHWVer(void);
static void CCP_vPtsWriteModelName(void);
static void CCP_vPtsWriteSerialNum(void);
static void CCP_vPtsWriteFactoryNum(void);
static void CCP_vPtsWriteDate(void);
static void CCP_vPtsWriteProductionLine(void);
static void CCP_vPtsWriteSerialByDay(void);
static void CCP_vPtsWriteInternalHWVer(void);
static void CCP_vPtsWriteExternalHWVer(void);


/* climate calibration process function */
static void CCP_vReadInf_00(void);
static void CCP_vReadInf_01(void);
static void CCP_vReadInf_02(void);
static void CCP_vReadInf_03(void);
static void CCP_vReadInf_04(void);
static void CCP_vReadInf_05(void);
static void CCP_vReadInf_06(void);
static void CCP_vReadInf_07(void);
static void CCP_vReadInf_08(void);
static void CCP_vReadInf_09(void);
static void CCP_vReadInf_0A(void);
static void CCP_vReadInf_0B(void);
static void CCP_vReadInf_0C(void);
static void CCP_vReadInf_0D(void);
static void CCP_vReadInf_0E(void);
static void CCP_vReadInf_0F(void);
static void CCP_vReadInf_10(void);
static void CCP_vReadInf_11(void);
static void CCP_vReadInf_12(void);
static void CCP_vReadInf_13(void);
static void CCP_vReadInf_14(void);
static void CCP_vReadInf_15(void);
static void CCP_vReadInf_16(void);
static void CCP_vReadInf_17(void);
static void CCP_vReadInf_18(void);
static void CCP_vReadInf_19(void);
static void CCP_vReadInf_1A(void);
static void CCP_vReadInf_1B(void);
static void CCP_vReadInf_1C(void);
static void CCP_vReadInf_1D(void);
static void CCP_vReadInf_1E(void);
static void CCP_vReadInf_1F(void);
static void CCP_vReadInf_20(void);
static void CCP_vReadInf_21(void);
static void CCP_vReadInf_22(void);
static void CCP_vReadInf_23(void);
static void CCP_vReadInf_24(void);
static void CCP_vReadInf_25(void);
static void CCP_vReadInf_26(void);
static void CCP_vReadInf_27(void);
static void CCP_vReadInf_28(void);
static void CCP_vReadInf_29(void);
static void CCP_vReadInf_2A(void);
static void CCP_vReadInf_2B(void);
static void CCP_vReadInf_2C(void);
static void CCP_vReadInf_2D(void);
static void CCP_vReadInf_2E(void);
static void CCP_vReadInf_2F(void);
static void CCP_vReadInf_30(void);
static void CCP_vReadInf_31(void);
static void CCP_vReadInf_32(void);
static void CCP_vReadInf_33(void);
static void CCP_vReadInf_34(void);
static void CCP_vReadInf_35(void);
static void CCP_vReadInf_36(void);
static void CCP_vReadInf_37(void);
static void CCP_vReadInf_38(void);
static void CCP_vReadInf_39(void);
static void CCP_vReadInf_3A(void);
static void CCP_vReadInf_3B(void);
static void CCP_vReadInf_3C(void);
static void CCP_vReadInf_3D(void);
static void CCP_vReadInf_3E(void);
static void CCP_vReadInf_3F(void);
static void CCP_vReadInf_40(void);
static void CCP_vReadInf_41(void);
static void CCP_vReadInf_42(void);
static void CCP_vReadInf_43(void);
static void CCP_vReadInf_44(void);
static void CCP_vReadInf_45(void);
static void CCP_vReadInf_46(void);
static void CCP_vReadInf_47(void);
static void CCP_vReadInf_48(void);
static void CCP_vReadInf_49(void);
static void CCP_vReadInf_4A(void);
static void CCP_vReadInf_4B(void);
static void CCP_vReadInf_4C(void);
static void CCP_vReadInf_4D(void);
static void CCP_vReadInf_4E(void);
static void CCP_vReadInf_4F(void);
static void CCP_vReadInf_50(void);
static void CCP_vReadInf_51(void);
static void CCP_vReadInf_52(void);
static void CCP_vReadInf_53(void);
static void CCP_vReadInf_54(void);
static void CCP_vReadInf_55(void);
static void CCP_vReadInf_56(void);
static void CCP_vReadInf_57(void);
static void CCP_vReadInf_58(void);
static void CCP_vReadInf_59(void);
static void CCP_vReadInf_5A(void);
static void CCP_vReadInf_5B(void);
static void CCP_vReadInf_5C(void);
static void CCP_vReadInf_5D(void);
static void CCP_vReadInf_5E(void);
static void CCP_vReadInf_5F(void);
static void CCP_vReadInf_60(void);
static void CCP_vReadInf_61(void);
static void CCP_vReadInf_62(void);
static void CCP_vReadInf_63(void);
static void CCP_vReadInf_64(void);
static void CCP_vReadInf_65(void);
static void CCP_vReadInf_66(void);
static void CCP_vReadInf_67(void);
static void CCP_vReadInf_68(void);
static void CCP_vReadInf_69(void);
static void CCP_vReadInf_6A(void);
static void CCP_vReadInf_6B(void);
static void CCP_vReadInf_6C(void);
static void CCP_vReadInf_6D(void);
static void CCP_vReadInf_6E(void);
static void CCP_vReadInf_6F(void);
static void CCP_vReadInf_70(void);
static void CCP_vReadInf_71(void);
static void CCP_vReadInf_72(void);
static void CCP_vReadInf_73(void);
static void CCP_vReadInf_74(void);
static void CCP_vReadInf_75(void);
static void CCP_vReadInf_76(void);
static void CCP_vReadInf_77(void);
static void CCP_vReadInf_78(void);
static void CCP_vReadInf_79(void);
static void CCP_vReadInf_7A(void);
static void CCP_vReadInf_7B(void);
static void CCP_vReadInf_7C(void);
static void CCP_vReadInf_7D(void);
static void CCP_vReadInf_7E(void);
static void CCP_vReadInf_7F(void);
static void CCP_vReadInf_80(void);
static void CCP_vReadInf_81(void);
static void CCP_vReadInf_82(void);
static void CCP_vReadInf_83(void);
static void CCP_vReadInf_84(void);
static void CCP_vReadInf_85(void);
static void CCP_vReadInf_86(void);
static void CCP_vReadInf_87(void);
static void CCP_vReadInf_88(void);
static void CCP_vReadInf_89(void);
static void CCP_vReadInf_8A(void);
static void CCP_vReadInf_8B(void);
static void CCP_vReadInf_8C(void);
static void CCP_vReadInf_8D(void);
static void CCP_vReadInf_8E(void);
static void CCP_vReadInf_8F(void);
static void CCP_vReadInf_90(void);
static void CCP_vReadInf_91(void);
static void CCP_vReadInf_92(void);
static void CCP_vReadInf_93(void);
static void CCP_vReadInf_94(void);
static void CCP_vReadInf_95(void);
static void CCP_vReadInf_96(void);
static void CCP_vReadInf_97(void);
static void CCP_vReadInf_98(void);
static void CCP_vReadInf_99(void);
static void CCP_vReadInf_9A(void);
static void CCP_vReadInf_9B(void);
static void CCP_vReadInf_9C(void);
static void CCP_vReadInf_9D(void);
static void CCP_vReadInf_9E(void);
static void CCP_vReadInf_9F(void);
static void CCP_vReadInf_A0(void);
static void CCP_vReadInf_A1(void);
static void CCP_vReadInf_A2(void);
static void CCP_vReadInf_A3(void);
static void CCP_vReadInf_A4(void);
static void CCP_vReadInf_A5(void);
static void CCP_vReadInf_A6(void);
static void CCP_vReadInf_A7(void);
static void CCP_vReadInf_A8(void);
static void CCP_vReadInf_A9(void);
static void CCP_vReadInf_AA(void);
static void CCP_vReadInf_AB(void);
static void CCP_vReadInf_AC(void);
static void CCP_vReadInf_AD(void);
static void CCP_vReadInf_AE(void);
static void CCP_vReadInf_AF(void);
static void CCP_vReadInf_B0(void);
static void CCP_vReadInf_B1(void);
static void CCP_vReadInf_B2(void);
static void CCP_vReadInf_B3(void);
static void CCP_vReadInf_B4(void);
static void CCP_vReadInf_B5(void);
static void CCP_vReadInf_B6(void);
static void CCP_vReadInf_B7(void);
static void CCP_vReadInf_B8(void);
static void CCP_vReadInf_B9(void);
static void CCP_vReadInf_BA(void);
static void CCP_vReadInf_BB(void);
static void CCP_vReadInf_BC(void);
static void CCP_vReadInf_BD(void);
static void CCP_vReadInf_BE(void);
static void CCP_vReadInf_BF(void);
static void CCP_vReadInf_C0(void);
static void CCP_vReadInf_C1(void);
static void CCP_vReadInf_C2(void);
static void CCP_vReadInf_C3(void);
static void CCP_vReadInf_C4(void);
static void CCP_vReadInf_C5(void);
static void CCP_vReadInf_C6(void);
static void CCP_vReadInf_C7(void);
static void CCP_vReadInf_C8(void);
static void CCP_vReadInf_C9(void);
static void CCP_vReadInf_CA(void);
static void CCP_vReadInf_CB(void);
static void CCP_vReadInf_CC(void);
static void CCP_vReadInf_CD(void);
static void CCP_vReadInf_CE(void);
static void CCP_vReadInf_CF(void);
static void CCP_vReadInf_D0(void);
static void CCP_vReadInf_D1(void);
static void CCP_vReadInf_D2(void);
static void CCP_vReadInf_D3(void);
static void CCP_vReadInf_D4(void);
static void CCP_vReadInf_D5(void);
static void CCP_vReadInf_D6(void);
static void CCP_vReadInf_D7(void);
static void CCP_vReadInf_D8(void);
static void CCP_vReadInf_D9(void);
static void CCP_vReadInf_DA(void);
static void CCP_vReadInf_DB(void);
static void CCP_vReadInf_DC(void);
static void CCP_vReadInf_DD(void);
static void CCP_vReadInf_DE(void);
static void CCP_vReadInf_DF(void);
static void CCP_vReadInf_E0(void);
static void CCP_vReadInf_E1(void);
static void CCP_vReadInf_E2(void);
static void CCP_vReadInf_E3(void);
static void CCP_vReadInf_E4(void);
static void CCP_vReadInf_E5(void);
static void CCP_vReadInf_E6(void);
static void CCP_vReadInf_E7(void);
static void CCP_vReadInf_E8(void);
static void CCP_vReadInf_E9(void);
static void CCP_vReadInf_EA(void);
static void CCP_vReadInf_EB(void);
static void CCP_vReadInf_EC(void);
static void CCP_vReadInf_ED(void);
static void CCP_vReadInf_EE(void);
static void CCP_vReadInf_EF(void);
static void CCP_vReadInf_F0(void);
static void CCP_vReadInf_F1(void);
static void CCP_vReadInf_F2(void);
static void CCP_vReadInf_F3(void);
static void CCP_vReadInf_F4(void);
static void CCP_vReadInf_F5(void);
static void CCP_vReadInf_F6(void);
static void CCP_vReadInf_F7(void);
static void CCP_vReadInf_F8(void);
static void CCP_vReadInf_F9(void);
static void CCP_vReadInf_FA(void);
static void CCP_vReadInf_FB(void);
static void CCP_vReadInf_FC(void);
static void CCP_vReadInf_FD(void);
static void CCP_vReadInf_FE(void);


static const CCP_tpfCidService CCP_pfCIDServices[CCP_RCID_NUM] =
{
	{&CCP_vReadInf_00,True},
	{&CCP_vReadInf_01,True},
	{&CCP_vReadInf_02,True},
	{&CCP_vReadInf_03,True},
	{&CCP_vReadInf_04,True},
	{&CCP_vReadInf_05,True},
	{&CCP_vReadInf_06,False},
	{&CCP_vReadInf_07,False},
	{&CCP_vReadInf_08,False},
	{&CCP_vReadInf_09,False},
	{&CCP_vReadInf_0A,False},
	{&CCP_vReadInf_0B,False},
	{&CCP_vReadInf_0C,False},
	{&CCP_vReadInf_0D,False},
	{&CCP_vReadInf_0E,False},
	{&CCP_vReadInf_0F,False},
	{&CCP_vReadInf_10,False},
	{&CCP_vReadInf_11,False},
	{&CCP_vReadInf_12,False},
	{&CCP_vReadInf_13,False},
	{&CCP_vReadInf_14,False},
	{&CCP_vReadInf_15,False},
	{&CCP_vReadInf_16,False},
	{&CCP_vReadInf_17,False},
	{&CCP_vReadInf_18,False},
	{&CCP_vReadInf_19,False},
	{&CCP_vReadInf_1A,False},
	{&CCP_vReadInf_1B,False},
	{&CCP_vReadInf_1C,False},
	{&CCP_vReadInf_1D,False},
	{&CCP_vReadInf_1E,False},
	{&CCP_vReadInf_1F,False},
	{&CCP_vReadInf_20,False},
	{&CCP_vReadInf_21,False},
	{&CCP_vReadInf_22,False},
	{&CCP_vReadInf_23,False},
	{&CCP_vReadInf_24,False},
	{&CCP_vReadInf_25,False},
	{&CCP_vReadInf_26,False},
	{&CCP_vReadInf_27,False},
	{&CCP_vReadInf_28,False},
	{&CCP_vReadInf_29,False},
	{&CCP_vReadInf_2A,False},
	{&CCP_vReadInf_2B,False},
	{&CCP_vReadInf_2C,False},
	{&CCP_vReadInf_2D,False},
	{&CCP_vReadInf_2E,False},
	{&CCP_vReadInf_2F,False},
	{&CCP_vReadInf_30,False},
	{&CCP_vReadInf_31,False},
	{&CCP_vReadInf_32,False},
	{&CCP_vReadInf_33,False},
	{&CCP_vReadInf_34,False},
	{&CCP_vReadInf_35,False},
	{&CCP_vReadInf_36,False},
	{&CCP_vReadInf_37,False},
	{&CCP_vReadInf_38,False},
	{&CCP_vReadInf_39,False},
	{&CCP_vReadInf_3A,False},
	{&CCP_vReadInf_3B,False},
	{&CCP_vReadInf_3C,False},
	{&CCP_vReadInf_3D,False},
	{&CCP_vReadInf_3E,False},
	{&CCP_vReadInf_3F,False},
	{&CCP_vReadInf_40,False},
	{&CCP_vReadInf_41,False},
	{&CCP_vReadInf_42,False},
	{&CCP_vReadInf_43,False},
	{&CCP_vReadInf_44,False},
	{&CCP_vReadInf_45,False},
	{&CCP_vReadInf_46,False},
	{&CCP_vReadInf_47,False},
	{&CCP_vReadInf_48,False},
	{&CCP_vReadInf_49,False},
	{&CCP_vReadInf_4A,False},
	{&CCP_vReadInf_4B,False},
	{&CCP_vReadInf_4C,False},
	{&CCP_vReadInf_4D,False},
	{&CCP_vReadInf_4E,False},
	{&CCP_vReadInf_4F,False},
	{&CCP_vReadInf_50,False},
    {&CCP_vReadInf_51,False},
    {&CCP_vReadInf_52,False},
    {&CCP_vReadInf_53,False},
    {&CCP_vReadInf_54,False},
    {&CCP_vReadInf_55,False},
    {&CCP_vReadInf_56,False},
    {&CCP_vReadInf_57,False},
    {&CCP_vReadInf_58,False},
    {&CCP_vReadInf_59,False},
    {&CCP_vReadInf_5A,False},
    {&CCP_vReadInf_5B,False},
    {&CCP_vReadInf_5C,False},
    {&CCP_vReadInf_5D,False},
    {&CCP_vReadInf_5E,False},
    {&CCP_vReadInf_5F,False},
    {&CCP_vReadInf_60,False},
    {&CCP_vReadInf_61,False},
    {&CCP_vReadInf_62,False},
    {&CCP_vReadInf_63,False},
    {&CCP_vReadInf_64,False},
    {&CCP_vReadInf_65,False},
    {&CCP_vReadInf_66,False},
    {&CCP_vReadInf_67,False},
    {&CCP_vReadInf_68,False},
    {&CCP_vReadInf_69,False},
    {&CCP_vReadInf_6A,False},
    {&CCP_vReadInf_6B,False},
    {&CCP_vReadInf_6C,False},
    {&CCP_vReadInf_6D,False},
    {&CCP_vReadInf_6E,False},
    {&CCP_vReadInf_6F,False},
    {&CCP_vReadInf_70,False},
    {&CCP_vReadInf_71,False},
    {&CCP_vReadInf_72,False},
    {&CCP_vReadInf_73,False},
    {&CCP_vReadInf_74,False},
    {&CCP_vReadInf_75,False},
    {&CCP_vReadInf_76,False},
    {&CCP_vReadInf_77,False},
    {&CCP_vReadInf_78,False},
    {&CCP_vReadInf_79,False},
    {&CCP_vReadInf_7A,False},
    {&CCP_vReadInf_7B,False},
    {&CCP_vReadInf_7C,False},
    {&CCP_vReadInf_7D,False},
    {&CCP_vReadInf_7E,False},
    {&CCP_vReadInf_7F,False},
	{&CCP_vReadInf_80,False},
	{&CCP_vReadInf_81,False},
	{&CCP_vReadInf_82,False},
	{&CCP_vReadInf_83,False},
	{&CCP_vReadInf_84,False},
	{&CCP_vReadInf_85,False},
	{&CCP_vReadInf_86,False},
	{&CCP_vReadInf_87,False},
	{&CCP_vReadInf_88,False},
	{&CCP_vReadInf_89,False},
	{&CCP_vReadInf_8A,False},
	{&CCP_vReadInf_8B,False},
	{&CCP_vReadInf_8C,False},
	{&CCP_vReadInf_8D,False},
	{&CCP_vReadInf_8E,False},
	{&CCP_vReadInf_8F,False},
	{&CCP_vReadInf_90,False},
	{&CCP_vReadInf_91,False},
	{&CCP_vReadInf_92,False},
	{&CCP_vReadInf_93,False},
	{&CCP_vReadInf_94,False},
	{&CCP_vReadInf_95,False},
	{&CCP_vReadInf_96,False},
	{&CCP_vReadInf_97,False},
	{&CCP_vReadInf_98,False},
	{&CCP_vReadInf_99,False},
	{&CCP_vReadInf_9A,False},
	{&CCP_vReadInf_9B,False},
	{&CCP_vReadInf_9C,False},
	{&CCP_vReadInf_9D,False},
	{&CCP_vReadInf_9E,False},
	{&CCP_vReadInf_9F,False},
	{&CCP_vReadInf_A0,False},
	{&CCP_vReadInf_A1,False},
	{&CCP_vReadInf_A2,False},
	{&CCP_vReadInf_A3,False},
	{&CCP_vReadInf_A4,False},
	{&CCP_vReadInf_A5,False},
	{&CCP_vReadInf_A6,False},
	{&CCP_vReadInf_A7,False},
	{&CCP_vReadInf_A8,False},
	{&CCP_vReadInf_A9,False},
	{&CCP_vReadInf_AA,False},
	{&CCP_vReadInf_AB,False},
	{&CCP_vReadInf_AC,False},
	{&CCP_vReadInf_AD,False},
	{&CCP_vReadInf_AE,False},
	{&CCP_vReadInf_AF,False},
	{&CCP_vReadInf_B0,False},
	{&CCP_vReadInf_B1,False},
	{&CCP_vReadInf_B2,False},
	{&CCP_vReadInf_B3,False},
	{&CCP_vReadInf_B4,False},
	{&CCP_vReadInf_B5,False},
	{&CCP_vReadInf_B6,False},
	{&CCP_vReadInf_B7,False},
	{&CCP_vReadInf_B8,False},
	{&CCP_vReadInf_B9,False},
	{&CCP_vReadInf_BA,False},
	{&CCP_vReadInf_BB,False},
	{&CCP_vReadInf_BC,False},
	{&CCP_vReadInf_BD,False},
	{&CCP_vReadInf_BE,False},
	{&CCP_vReadInf_BF,False},
	{&CCP_vReadInf_C0,False},
	{&CCP_vReadInf_C1,False},
	{&CCP_vReadInf_C2,False},
	{&CCP_vReadInf_C3,False},
	{&CCP_vReadInf_C4,False},
	{&CCP_vReadInf_C5,False},
	{&CCP_vReadInf_C6,False},
	{&CCP_vReadInf_C7,False},
	{&CCP_vReadInf_C8,False},
	{&CCP_vReadInf_C9,False},
	{&CCP_vReadInf_CA,False},
	{&CCP_vReadInf_CB,False},
	{&CCP_vReadInf_CC,False},
	{&CCP_vReadInf_CD,False},
	{&CCP_vReadInf_CE,False},
	{&CCP_vReadInf_CF,False},
	{&CCP_vReadInf_D0,False},
    {&CCP_vReadInf_D1,False},
    {&CCP_vReadInf_D2,False},
    {&CCP_vReadInf_D3,False},
    {&CCP_vReadInf_D4,False},
    {&CCP_vReadInf_D5,False},
    {&CCP_vReadInf_D6,False},
    {&CCP_vReadInf_D7,False},
    {&CCP_vReadInf_D8,False},
    {&CCP_vReadInf_D9,False},
    {&CCP_vReadInf_DA,False},
    {&CCP_vReadInf_DB,False},
    {&CCP_vReadInf_DC,False},
    {&CCP_vReadInf_DD,False},
    {&CCP_vReadInf_DE,False},
    {&CCP_vReadInf_DF,False},
    {&CCP_vReadInf_E0,False},
    {&CCP_vReadInf_E1,False},
    {&CCP_vReadInf_E2,False},
    {&CCP_vReadInf_E3,False},
    {&CCP_vReadInf_E4,False},
    {&CCP_vReadInf_E5,False},
    {&CCP_vReadInf_E6,False},
    {&CCP_vReadInf_E7,False},
    {&CCP_vReadInf_E8,False},
    {&CCP_vReadInf_E9,False},
    {&CCP_vReadInf_EA,False},
    {&CCP_vReadInf_EB,False},
    {&CCP_vReadInf_EC,False},
    {&CCP_vReadInf_ED,False},
    {&CCP_vReadInf_EE,False},
    {&CCP_vReadInf_EF,False},
    {&CCP_vReadInf_F0,False},
    {&CCP_vReadInf_F1,False},
    {&CCP_vReadInf_F2,False},
    {&CCP_vReadInf_F3,False},
    {&CCP_vReadInf_F4,False},
    {&CCP_vReadInf_F5,False},
    {&CCP_vReadInf_F6,False},
    {&CCP_vReadInf_F7,False},
    {&CCP_vReadInf_F8,False},
    {&CCP_vReadInf_F9,True},
    {&CCP_vReadInf_FA,True},
    {&CCP_vReadInf_FB,True},
    {&CCP_vReadInf_FC,True},
    {&CCP_vReadInf_FD,True},
    {&CCP_vReadInf_FE,True},

};

static const CCP_tpfService Ccp_pfIoControlTable [CCP_IO_CONTROL_NUM] =
{
	&CCP_vIoControl_10,
	&CCP_vIoControl_11,
	&CCP_vIoControl_12,
	&CCP_vIoControl_13,
	&CCP_vIoControl_14,
	&CCP_vIoControl_15,
	&CCP_vIoControl_16,
	&CCP_vIoControl_17,
	&CCP_vIoControl_18,
	&CCP_vIoControl_19,
	&CCP_vIoControl_1A,
	&CCP_vIoControl_1B,
	&CCP_vIoControl_1C,
	&CCP_vIoControl_1D,
	&CCP_vIoControl_1E,
	&CCP_vIoControl_1F,
	&CCP_vIoControl_20,
	&CCP_vIoControl_21,
	&CCP_vIoControl_22,
	&CCP_vIoControl_23,
	&CCP_vIoControl_24,
	&CCP_vIoControl_25,
	&CCP_vIoControl_26,
	&CCP_vIoControl_27,
	&CCP_vIoControl_28,
	&CCP_vIoControl_29,
	&CCP_vIoControl_2A,
	&CCP_vIoControl_2B,
	&CCP_vIoControl_2C,
	&CCP_vIoControl_2D,
	&CCP_vIoControl_2E,
	&CCP_vIoControl_2F,
	&CCP_vIoControl_30,
	&CCP_vIoControl_31,
	&CCP_vIoControl_32,
	&CCP_vIoControl_33,
	&CCP_vIoControl_34,
	&CCP_vIoControl_35,
	&CCP_vIoControl_36,
	&CCP_vIoControl_37,
	&CCP_vIoControl_38,
	&CCP_vIoControl_39,
	&CCP_vIoControl_3A,
	&CCP_vIoControl_3B,
	&CCP_vIoControl_3C,
	&CCP_vIoControl_3D,
	&CCP_vIoControl_3E,
	&CCP_vIoControl_3F,
	&CCP_vIoControl_40,
	&CCP_vIoControl_41,
	&CCP_vIoControl_42,
	&CCP_vIoControl_43,
	&CCP_vIoControl_44,
	&CCP_vIoControl_45,
	&CCP_vIoControl_46,
	&CCP_vIoControl_47,
	&CCP_vIoControl_48,
	&CCP_vIoControl_49,
	&CCP_vIoControl_4A,
	&CCP_vIoControl_4B,
	&CCP_vIoControl_4C,
	&CCP_vIoControl_4D,
	&CCP_vIoControl_4E,
	&CCP_vIoControl_4F,
	&CCP_vIoControl_50,
	&CCP_vIoControl_51,
	&CCP_vIoControl_52,
	&CCP_vIoControl_53,
	&CCP_vIoControl_54,
	&CCP_vIoControl_55,	
	&CCP_vIoControl_56,
	&CCP_vIoControl_57,
	&CCP_vIoControl_58,
	&CCP_vIoControl_59,
	&CCP_vIoControl_5A,
	&CCP_vIoControl_5B,
	&CCP_vIoControl_5C,
	&CCP_vIoControl_5D,
	&CCP_vIoControl_5E,
	&CCP_vIoControl_5F,
	&CCP_vIoControl_60,
	&CCP_vIoControl_61,
	&CCP_vIoControl_62,
	&CCP_vIoControl_63
};

static const CCP_tpfService Ccp_pfPtsControlTable [CCP_PTS_CONTROL_NUM] =
{
	&CCP_vPtsControl_21,
	&CCP_vPtsControl_22,
	&CCP_vPtsControl_23,
	&CCP_vPtsControl_24,
	&CCP_vPtsControl_25,
	&CCP_vPtsControl_26,
	&CCP_vPtsControl_27,
	&CCP_vPtsControl_28,
	&CCP_vPtsControl_29,
	&CCP_vPtsControl_2A,
	&CCP_vPtsControl_2B,
	&CCP_vPtsControl_2C,
	&CCP_vPtsControl_2D,
	&CCP_vPtsControl_2E,
	&CCP_vPtsControl_2F
};

static const CCP_tpfService Ccp_pfPtsReadInfTable [CCP_PTS_READINF_NUM] =
{
	&CCP_vPtsReadInf_01,
	&CCP_vPtsReadInf_02,
	&CCP_vPtsReadInf_03,
	&CCP_vPtsReadInf_04,
	&CCP_vPtsReadInf_05,
	&CCP_vPtsReadInf_06,
	&CCP_vPtsReadInf_07,
	&CCP_vPtsReadInf_08,
	&CCP_vPtsReadInf_09,
	&CCP_vPtsReadInf_0A,
	&CCP_vPtsReadInf_0B,
	&CCP_vPtsReadInf_0C,
	&CCP_vPtsReadInf_0D,
	&CCP_vPtsReadInf_0E,
	&CCP_vPtsReadInf_0F
};
	
static const CCP_tstMapTable CCP_stMapTable[CCP_MAP_TABLE_SIZE] =
{
	{ 0x10, CCP_vSessionMode},
	{ 0x20, CCP_vExitCcp},
	{ 0x22, CCP_vReadByCommonID },
	{ 0x23, CCP_vReadMemoryByAddress },
	{ 0x27, CCP_vSafeAccess },
	{ 0x30, CCP_vIOControlByLocalID },
	{ 0x3D, CCP_vWriteMemoryByAddress },
    { 0x3F, CCP_vReadCalibrationFrame }
};


/* Eeprom access function , all the functions must not be update */
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vClrGlobalBuff                                              *
 Description   :   Clear global variable buffers     *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vClrGlobalBuff (uint8 u8RW)
{
	uint8 u8TempCnt;
	if(u8RW == CCP_nClrWriteGlbBuff)
	{
		CCP_stGlobals.WriteInfo.u8FrameType = CCP_nNullFrame;
		CCP_stGlobals.WriteInfo.u16DataLen = 0x00;
		CCP_stGlobals.WriteInfo.u16Address = 0x0000;
		CCP_stGlobals.WriteInfo.u8DataType = CCP_nData;
		CCP_stGlobals.WriteInfo.u8CheckSum = 0x00;
		for(u8TempCnt=0; u8TempCnt < sizeof(CCP_stGlobals.WriteInfo.u8Data); u8TempCnt++)
		{
			CCP_stGlobals.WriteInfo.u8Data[u8TempCnt] = 0;
		}
	}
	else if(u8RW == CCP_nClrReadGlbBuff)
	{
		CCP_stGlobals.ReadInfo.u8FrameType = CCP_nNullFrame;
		CCP_stGlobals.ReadInfo.u16DataLen = 0x00;
		CCP_stGlobals.ReadInfo.u16Address = 0x0000;
		CCP_stGlobals.ReadInfo.u8DataType = CCP_nData;
		CCP_stGlobals.ReadInfo.u8CheckSum = 0x00;
		for(u8TempCnt=0; u8TempCnt < sizeof(CCP_stGlobals.ReadInfo.u8Data); u8TempCnt++)
		{
			CCP_stGlobals.ReadInfo.u8Data[u8TempCnt] = 0;
		}
	}
	else
	{
		//no action
	}
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vReadEepromAccess                                              *
 Description   :   Read eeprom     *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadEepromAccess(void)
{
    if(CCP_EepromInd_b == True)
	{
        CCP_EepromInd_b = False;
        
        //CCP_u8FrameType = CCP_stCmdPtr.u8CmdID;
        switch(CCP_stCmdPtr.u8CmdID)
        {
            case CCP_nStartFrame:
            CCP_vStartTxFrameHandling();
            /*CCP_u8FrameType = CCP_nMidFrame;*/
            break;
            case CCP_nMidFrame:
            CCP_vMidTxFrameHandling();
            /*CCP_u8FrameType = CCP_nEndFrame;*/
            break;
            case CCP_nEndFrame:
            CCP_vEndTxFrameHandling();
            /*CCP_u8FrameType = CCP_nStartFrame;*/
            break;
            default:
            break;
        }
    }
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vStartTxFrameHandling                                              *
 Description   :   handling transmitted start frame     *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vStartTxFrameHandling(void)
{
    //uint8 u8EEPErr = 0xFF;
     uint8 u8Ret=0;
     uint32 u32ReadAddr = 0U; 
	if((CCP_stCmdPtr.u8Data4==CCP_nFieldEnd)&&(CCP_stCmdPtr.u8Data5==0xFF))//if(CCP_u16EepDataPtr >= CCP_u16EepDataLength)
	{
		CCP_stDatastrct.u8CmdID = CCP_nStartFrame;
		CCP_stDatastrct.u8Data1 = 0x00;
		CCP_stDatastrct.u8Data2 = 0x00;
		CCP_stDatastrct.u8Data3 = 0x00;
		CCP_stDatastrct.u8Data4 = CCP_nFieldEnd;
		CCP_stDatastrct.u8Data5 = 0xFF;
		CCP_stDatastrct.u8Data6 = NO_USE;
		CCP_stDatastrct.u8Data7 = NO_USE;
		CCP_biEepromAccess = False; /* Eeprom access finished */
		CCP_u8EepAccessType = CCP_nRWNullAction;
		CCP_biServiceActive = True;
		CCP_SetBit(CCP_nbiServiceActive);
	}
	else
	{
		CCP_stGlobals.ReadInfo.u8FrameType = CCP_nStartFrame; /* start frame */
		if((CCP_u16EepDataLength - CCP_u16EepDataPtr)>=16)
		{	
			CCP_stGlobals.ReadInfo.u16DataLen = 0x10;
		}
		else
		{
			CCP_stGlobals.ReadInfo.u16DataLen = CCP_u16EepDataLength - CCP_u16EepDataPtr;
		}
		CCP_stGlobals.ReadInfo.u16Address = (CCP_u16EepDataPtr / 0x10) * 0x10;
		CCP_stGlobals.ReadInfo.u16Address += CCP_u16EepAddress;
		CCP_stGlobals.ReadInfo.u8DataType = CCP_nData; /* Data type */
		CCP_u16EepDataPtr += CCP_stGlobals.ReadInfo.u16DataLen;
		if(CCP_u8EepAccessType == CCP_nReadRamByID)
		{
			/* Read RAM */
			memcpy(CCP_stGlobals.ReadInfo.u8Data,(char *)(CCP_stGlobals.ReadInfo.u16Address),(uint8)(CCP_stGlobals.ReadInfo.u16DataLen));
		}
		else
		{
			/* Read Eeprom */            
            #ifdef CcpDataFlashUse           
            if((CCP_enWorkingMode == CCP_nObdMode)&&(CCP_stGlobals.ReadInfo.u16Address>=CcpGetEEPPTSStartAddr))
            {
                u32ReadAddr = CCP_stGlobals.ReadInfo.u16Address-CcpGetEEPPTSStartAddr;
        	    u32ReadAddr |= CcpPTSDataFalshStart;
                u8Ret=CCP_ReadEEPData(u32ReadAddr,&CCP_stGlobals.ReadInfo.u8Data[0],CCP_stGlobals.ReadInfo.u16DataLen);
            }
            else if((CCP_enWorkingMode == CCP_nCalibrationMode))
            {
                u32ReadAddr = CCP_stGlobals.ReadInfo.u16Address;
        	    u32ReadAddr |= CcpCaliDataFlashStart;
                u8Ret=CCP_ReadEEPData(u32ReadAddr,&CCP_stGlobals.ReadInfo.u8Data[0],CCP_stGlobals.ReadInfo.u16DataLen);               
            }
            else
            {
                 CCP_u8EepAccessType = CCP_nRWNullAction;
            }
            
            #else
            CCP_stGlobals.ReadInfo.u16Address = CCP_stGlobals.ReadInfo.u16Address;     
            u8Ret=CCP_ReadEEPData(CCP_stGlobals.ReadInfo.u16Address,&CCP_stGlobals.ReadInfo.u8Data[0],CCP_stGlobals.ReadInfo.u16DataLen);
            #endif

            if(u8Ret != 0)/*not successful*/
            {
               CCP_u8EepAccessType = CCP_nRWNullAction;
            }
 
		}
        
		/* transmit the data to the send buffer */
		CCP_stDatastrct.u8CmdID = CCP_stGlobals.ReadInfo.u8FrameType;
		CCP_stDatastrct.u8Data1 = (uint8)CCP_stGlobals.ReadInfo.u16DataLen;	
		CCP_stDatastrct.u8Data2 = (uint8)((CCP_stGlobals.ReadInfo.u16Address & 0xFF00) >> 8);	
		CCP_stDatastrct.u8Data3 = (uint8)(CCP_stGlobals.ReadInfo.u16Address & 0x00FF);	
		CCP_stDatastrct.u8Data4 = CCP_stGlobals.ReadInfo.u8DataType;	
		CCP_stDatastrct.u8Data5 = CCP_stGlobals.ReadInfo.u8Data[0];
		CCP_stDatastrct.u8Data6 = CCP_stGlobals.ReadInfo.u8Data[1];
		CCP_stDatastrct.u8Data7 = CCP_stGlobals.ReadInfo.u8Data[2];
		CCP_biServiceActive = True;
		CCP_SetBit(CCP_nbiServiceActive);
	}
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vMidTxFrameHandling                                              *
 Description   :   handling transmitted middle frame     *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vMidTxFrameHandling(void)
{
	CCP_stGlobals.ReadInfo.u8FrameType = CCP_nMidFrame; /* middle frame */
	/* transmit the data to the send buffer */
	CCP_stDatastrct.u8CmdID = CCP_stGlobals.ReadInfo.u8FrameType;
	CCP_stDatastrct.u8Data1 = CCP_stGlobals.ReadInfo.u8Data[3];
	CCP_stDatastrct.u8Data2 = CCP_stGlobals.ReadInfo.u8Data[4];
	CCP_stDatastrct.u8Data3 = CCP_stGlobals.ReadInfo.u8Data[5];
	CCP_stDatastrct.u8Data4 = CCP_stGlobals.ReadInfo.u8Data[6];
	CCP_stDatastrct.u8Data5 = CCP_stGlobals.ReadInfo.u8Data[7];
	CCP_stDatastrct.u8Data6 = CCP_stGlobals.ReadInfo.u8Data[8];
	CCP_stDatastrct.u8Data7 = CCP_stGlobals.ReadInfo.u8Data[9];
	CCP_biServiceActive = True;
	CCP_SetBit(CCP_nbiServiceActive);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vEndTxFrameHandling                                              *
 Description   :   handling transmitted end frame     *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vEndTxFrameHandling(void)
{
	CCP_stGlobals.ReadInfo.u8FrameType = CCP_nEndFrame; /* end frame */

	/* calculate checksum */
	CCP_stGlobals.ReadInfo.u8CheckSum = CCP_vCalChecksum(CCP_nCalReadCheckSum);
	/* transmit the data to the send buffer */
	CCP_stDatastrct.u8CmdID = CCP_stGlobals.ReadInfo.u8FrameType;
	CCP_stDatastrct.u8Data1 = CCP_stGlobals.ReadInfo.u8Data[10];
	CCP_stDatastrct.u8Data2 = CCP_stGlobals.ReadInfo.u8Data[11];
	CCP_stDatastrct.u8Data3 = CCP_stGlobals.ReadInfo.u8Data[12];
	CCP_stDatastrct.u8Data4 = CCP_stGlobals.ReadInfo.u8Data[13];
	CCP_stDatastrct.u8Data5 = CCP_stGlobals.ReadInfo.u8Data[14];
	CCP_stDatastrct.u8Data6 = CCP_stGlobals.ReadInfo.u8Data[15];
	CCP_stDatastrct.u8Data7 = CCP_stGlobals.ReadInfo.u8CheckSum;
	CCP_biServiceActive = True;
	CCP_SetBit(CCP_nbiServiceActive);
	/* clr the global buffer before load the new data */
	CCP_vClrGlobalBuff(CCP_nClrReadGlbBuff);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vWriteEepromAccess                                              *
 Description   :   Write eeprom     *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vWriteEepromAccess(void)
{
	if(CCP_EepromInd_b == True)
	{
		CCP_EepromInd_b = False;
		switch(CCP_stCmdPtr.u8CmdID)
		{
			case CCP_nStartFrame:
				/* clear the global buffer before load the new data */
				CCP_vClrGlobalBuff(CCP_nClrWriteGlbBuff);					
				CCP_vStartRxFrameHandling();
				break;		
			case CCP_nMidFrame:
				CCP_vMidRxFrameHandling();
				break;			
			case CCP_nEndFrame:
				CCP_vEndRxFrameHandling();
				break;	
			default:
				CCP_u8AckType = CCP_nFormatErr;
				break;
		}
		if(CCP_au8Array[CCP_nu8WriteEeprom] == 0x00)
		{
			CCP_biServiceActive = True;
			CCP_SetBit(CCP_nbiServiceActive); /* Enable transmit writing eeprom resphone after write action */
		}
		if(CCP_u8AckType == CCP_nSuccessful)
		{
			/* Positive resphone */
			CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID | 0x40;
			CCP_stDatastrct.u8Data1 = CCP_u8AckType;
			CCP_stDatastrct.u8Data2 = NO_USE;
			CCP_stDatastrct.u8Data3 = NO_USE;
			CCP_stDatastrct.u8Data4 = NO_USE;
			CCP_stDatastrct.u8Data5 = NO_USE;
			CCP_stDatastrct.u8Data6 = NO_USE;
			CCP_stDatastrct.u8Data7 = NO_USE;
		}
		else
		{
			/* Negative resphone */
			CCP_vNegativeResphone((uint8)CCP_u8AckType);
			CCP_biEepromAccess = False; /* Exit Eeprom access */
		}
	}
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vStartRxFrameHandling                                              *
 Description   :   Receive the first frame data     *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vStartRxFrameHandling(void)
{
	CCP_u8AckType = CCP_nSuccessful; /* Receive is successful */
	if(CCP_stCmdPtr.u8Data4 == CCP_nFieldEnd) /* Interal format Hex file the end frame is 0x01 */
	{
		CCP_biEepromAccess = False; /* Eeprom access finished */
		CCP_u8EepAccessType = CCP_nRWNullAction;
	}
	else
	{
		/* data length */
		CCP_stGlobals.WriteInfo.u16DataLen = CCP_stCmdPtr.u8Data1;
		/* data address */
		CCP_stGlobals.WriteInfo.u16Address = ((uint16)(CCP_stCmdPtr.u8Data2)  << 8 ) + CCP_stCmdPtr.u8Data3;
		/* data type */
		CCP_stGlobals.WriteInfo.u8DataType = CCP_stCmdPtr.u8Data4;
		/* data */
		CCP_stGlobals.WriteInfo.u8Data[0] = CCP_stCmdPtr.u8Data5;
		CCP_stGlobals.WriteInfo.u8Data[1] = CCP_stCmdPtr.u8Data6;
		CCP_stGlobals.WriteInfo.u8Data[2] = CCP_stCmdPtr.u8Data7;
	}
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vMidRxFrameHandling                                              *
 Description   :   Receive the middle frame data     *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vMidRxFrameHandling(void)
{
	/* data */
	CCP_stGlobals.WriteInfo.u8Data[3] = CCP_stCmdPtr.u8Data1;
	CCP_stGlobals.WriteInfo.u8Data[4] = CCP_stCmdPtr.u8Data2;
	CCP_stGlobals.WriteInfo.u8Data[5] = CCP_stCmdPtr.u8Data3;
	CCP_stGlobals.WriteInfo.u8Data[6] = CCP_stCmdPtr.u8Data4;
	CCP_stGlobals.WriteInfo.u8Data[7] = CCP_stCmdPtr.u8Data5;
	CCP_stGlobals.WriteInfo.u8Data[8] = CCP_stCmdPtr.u8Data6;
	CCP_stGlobals.WriteInfo.u8Data[9] = CCP_stCmdPtr.u8Data7;
	CCP_u8AckType = CCP_nSuccessful; /* Receive is successful */
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vEndRxFrameHandling                                              *
 Description   :   Receive the end frame data     *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vEndRxFrameHandling(void)
{
	uint8 u8Ret = 0xFF;
	uint32 TempAddress;
	/* data */
	CCP_stGlobals.WriteInfo.u8Data[10] = CCP_stCmdPtr.u8Data1;
	CCP_stGlobals.WriteInfo.u8Data[11] = CCP_stCmdPtr.u8Data2;
	CCP_stGlobals.WriteInfo.u8Data[12] = CCP_stCmdPtr.u8Data3;
	CCP_stGlobals.WriteInfo.u8Data[13] = CCP_stCmdPtr.u8Data4;
	CCP_stGlobals.WriteInfo.u8Data[14] = CCP_stCmdPtr.u8Data5;
	CCP_stGlobals.WriteInfo.u8Data[15] = CCP_stCmdPtr.u8Data6;
	/* check sum */
	CCP_stGlobals.WriteInfo.u8CheckSum = CCP_stCmdPtr.u8Data7;
	if(CCP_vCalChecksum(CCP_nCalWriteCheckSum) == CCP_stGlobals.WriteInfo.u8CheckSum)
	{
		if((CCP_u8EepAccessType == CCP_nWriteEepByID) ||(CCP_u8EepAccessType == CCP_nWriteWholeEep)) 
		{
			CCP_au8Array[CCP_nu8WriteEeprom] = CCP_WRITE_EEPROM;
			CCP_u8TimeCounter = 0x00;

            if((CCP_enWorkingMode == CCP_nObdMode)&&(CCP_stGlobals.WriteInfo.u16Address>=CcpGetEEPPTSStartAddr))
            {
                #ifdef CcpDataFlashUse
                    TempAddress = CCP_stGlobals.WriteInfo.u16Address-CcpGetEEPPTSStartAddr;
    			    TempAddress |= CcpPTSDataFalshStart;
                #else
                    TempAddress = CCP_stGlobals.WriteInfo.u16Address;
                #endif
                u8Ret = CCP_WriteEEPData(TempAddress,&CCP_stGlobals.WriteInfo.u8Data[0],CCP_stGlobals.WriteInfo.u16DataLen);

            }
            else if(CCP_enWorkingMode == CCP_nCalibrationMode)
            {              
                #ifdef CcpDataFlashUse
                    TempAddress = CCP_stGlobals.WriteInfo.u16Address;
    			    TempAddress |= CcpCaliDataFlashStart;
                #else
                    TempAddress = CCP_stGlobals.WriteInfo.u16Address;
                #endif
                     u8Ret = CCP_WriteEEPData(TempAddress,&CCP_stGlobals.WriteInfo.u8Data[0],CCP_stGlobals.WriteInfo.u16DataLen);
            }
            else
            {
                CCP_u8AckType = CCP_nFormatErr;
            }

           #if 0 /*Test for dataflash*/
			if(u8Ret == CCP_nbRC_OK)
			{
				CCP_u8AckType = CCP_nSuccessful;
			}
			else if(u8Ret == CCP_nbRC_BUSY)
			{
				CCP_u8AckType = CCP_nTimeOutErr;
			}
			else
			{
				CCP_u8AckType = CCP_nFormatErr;
			}
           #endif
		}
		else
		{
			CCP_u8AckType = CCP_nSuccessful;
			memcpy((char *)(CCP_stGlobals.WriteInfo.u16Address),CCP_stGlobals.WriteInfo.u8Data,CCP_stGlobals.WriteInfo.u16DataLen);
		}
	}
	else
	{
		CCP_u8AckType = CCP_nCheckSumErr;
	}
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vCalChecksum                                              *
 Description   :   calculate check sum     *
 Return Value  : None                                                        *
*****************************************************************************/
static uint8 CCP_vCalChecksum(uint8 u8RW)
{
	uint16 u16tempCRC = 0;
	uint8  u8tempCRC = 0;
	uint8 u8LoopCnt;
	if(u8RW == CCP_nCalWriteCheckSum)
	{
		/* calculate the checksum for receiving the data from pc */
		u16tempCRC += (uint8)(CCP_stGlobals.WriteInfo.u16DataLen);
		u16tempCRC += (uint8)((CCP_stGlobals.WriteInfo.u16Address & 0xFF00)>> 8);
		u16tempCRC += (uint8)(CCP_stGlobals.WriteInfo.u16Address & 0x00FF);
		u16tempCRC += CCP_stGlobals.WriteInfo.u8DataType;
		for(u8LoopCnt=0; u8LoopCnt < (uint8)(CCP_stGlobals.WriteInfo.u16DataLen); u8LoopCnt++)
		{
			u16tempCRC += CCP_stGlobals.WriteInfo.u8Data[u8LoopCnt];
		}
	}
	else if(u8RW == CCP_nCalReadCheckSum)
	{
		/* to calculate the checksum for transmitting the data to pc */
		u16tempCRC += (uint8)(CCP_stGlobals.ReadInfo.u16DataLen);
		u16tempCRC += (uint8)((CCP_stGlobals.ReadInfo.u16Address & 0xFF00)>> 8);
		u16tempCRC += (uint8)(CCP_stGlobals.ReadInfo.u16Address & 0x00FF);
		u16tempCRC += CCP_stGlobals.ReadInfo.u8DataType;
		for(u8LoopCnt=0; u8LoopCnt < (uint8)(CCP_stGlobals.ReadInfo.u16DataLen); u8LoopCnt++)
		{
			u16tempCRC += CCP_stGlobals.ReadInfo.u8Data[u8LoopCnt];
		}
	}
	else
	{
		/* no action */
	}
	u16tempCRC %= 0x100;
	u16tempCRC =~ u16tempCRC;
	u16tempCRC += 1;
	u8tempCRC = (uint8)(u16tempCRC);
	return (u8tempCRC);
}
/* Eeprom access function end */
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/14											  *
 Function      : CCP_u8GetValue                                              *
 Description   :   rutern the status of climate calibration message transmit switch     *
 Return Value  : CCP_au8Array                                                        *
*****************************************************************************/
uint8 CCP_u8GetValue(CCP_tenu8VarNumber enIndex)
{
	if(enIndex < CCP_nu8Max)
	{
		return(CCP_au8Array[enIndex]);
	}
	else
	{
		return(CCP_au8Array[CCP_nu8Max-1]);
	}
}

static uint32 CCP_u32KeyBitChange(uint32 InValue,uint32 OutValue,uint32 InPos,uint32 OutPos)
{
    InPos = (uint32)(1u<<InPos);
    if((InValue&InPos)==InPos)
    {
        OutValue |= (uint32)(1u<<OutPos);
    }
    else
    {
        OutValue &= (uint32)(~(1u<<OutPos));
    }

    return OutValue;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/10/18										  *
 Function      : CCP_boGetValue                                              *
 Description   :   rutern the value of bit valiable     *
 Return Value  : Ture/False                                                        *
*****************************************************************************/
Bool CCP_boGetValue(CCP_tenbiVarNumber enIndex)
{
	if(enIndex < CCP_nbiMax)
	{
		return(CCP_GetBitValue(enIndex) == 0x01);
	}
	else
	{
		return(CCP_GetBitValue((CCP_nbiMax - 1)) == 0x01);
	}
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_90                                              *
 Description   : Read information ID 90                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_00(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray00_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray00_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray00_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray00_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray00_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray00_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray00_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_01                                              *
 Description   : Read information ID 01                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_01(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray01_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray01_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray01_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray01_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray01_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray01_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray01_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_02                                              *
 Description   : Read information ID 02                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_02(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray02_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray02_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray02_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray02_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray02_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray02_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray02_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_03                                              *
 Description   : Read information ID 03                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_03(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray03_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray03_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray03_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray03_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray03_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray03_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray03_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_04                                              *
 Description   : Read information ID 04                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_04(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray04_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray04_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray04_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray04_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray04_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray04_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray04_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_05                                              *
 Description   : Read information ID 05                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_05(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray05_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray05_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray05_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray05_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray05_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray05_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray05_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_06                                              *
 Description   : Read information ID 06                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_06(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray06_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray06_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray06_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray06_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray06_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray06_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray06_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin						  *
 DATE: 		 : 2015/6/29							  *
 Function      : CCP_vReadInf_07                                       *
 Description   : Read information ID 07                            	  *
 Return Value  : None                                                       *
*****************************************************************************/
static void CCP_vReadInf_07(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray07_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray07_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray07_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray07_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray07_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray07_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray07_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_08                                              *
 Description   : Read information ID 08                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_08(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray08_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray08_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray08_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray08_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray08_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray08_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray08_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_09                                              *
 Description   : Read information ID 09                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_09(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray09_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray09_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray09_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray09_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray09_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray09_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray09_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_0A                                              *
 Description   : Read information ID 0A                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_0A(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray0A_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray0A_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray0A_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray0A_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray0A_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray0A_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray0A_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_0B                                              *
 Description   : Read information ID 0B                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_0B(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray0B_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray0B_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray0B_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray0B_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray0B_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray0B_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray0B_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_0C                                              *
 Description   : Read information ID 0C                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_0C(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray0C_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray0C_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray0C_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray0C_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray0C_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray0C_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray0C_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_0D                                              *
 Description   : Read information ID 0D                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_0D(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray0D_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray0D_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray0D_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray0D_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray0D_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray0D_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray0D_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_0E                                              *
 Description   : Read information ID 0E                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_0E(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray0E_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray0E_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray0E_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray0E_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray0E_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray0E_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray0E_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_0F                                              *
 Description   : Read information ID 0F                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_0F(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray0F_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray0F_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray0F_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray0F_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray0F_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray0F_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray0F_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_10                                              *
 Description   : Read information ID 10                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_10(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray10_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray10_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray10_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray10_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray10_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray10_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray10_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_11                                              *
 Description   : Read information ID 11                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_11(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray11_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray11_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray11_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray11_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray11_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray11_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray11_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_12                                              *
 Description   : Read information ID 12                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_12(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray12_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray12_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray12_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray12_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray12_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray12_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray12_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_13                                              *
 Description   : Read information ID 13                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_13(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray13_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray13_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray13_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray13_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray13_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray13_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray13_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_14                                              *
 Description   : Read information ID 14                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_14(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray14_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray14_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray14_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray14_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray14_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray14_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray14_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_15                                              *
 Description   : Read information ID 15                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_15(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray15_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray15_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray15_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray15_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray15_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray15_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray15_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_16                                              *
 Description   : Read information ID 16                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_16(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray16_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray16_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray16_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray16_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray16_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray16_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray16_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_17                                              *
 Description   : Read information ID 17                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_17(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray17_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray17_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray17_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray17_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray17_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray17_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray17_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_18                                              *
 Description   : Read information ID 18                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_18(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray18_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray18_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray18_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray18_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray18_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray18_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray18_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_19                                              *
 Description   : Read information ID 19                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_19(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray19_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray19_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray19_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray19_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray19_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray19_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray19_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_1A                                              *
 Description   : Read information ID 1A                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_1A(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray1A_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray1A_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray1A_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray1A_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray1A_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray1A_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray1A_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_1B                                              *
 Description   : Read information ID 1B                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_1B(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray1B_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray1B_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray1B_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray1B_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray1B_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray1B_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray1B_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_1C                                              *
 Description   : Read information ID 1C                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_1C(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray1C_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray1C_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray1C_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray1C_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray1C_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray1C_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray1C_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_1D                                              *
 Description   : Read information ID 1D                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_1D(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray1D_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray1D_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray1D_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray1D_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray1D_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray1D_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray1D_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_1E                                              *
 Description   : Read information ID 1E                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_1E(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray1E_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray1E_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray1E_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray1E_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray1E_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray1E_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray1E_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_1F                                              *
 Description   : Read information ID 1F                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_1F(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray1F_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray1F_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray1F_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray1F_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray1F_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray1F_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray1F_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_20                                              *
 Description   : Read information ID 20                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_20(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray20_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray20_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray20_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray20_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray20_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray20_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray20_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_21                                              *
 Description   : Read information ID 21                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_21(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray21_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray21_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray21_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray21_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray21_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray21_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray21_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_22                                              *
 Description   : Read information ID 22                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_22(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray22_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray22_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray22_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray22_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray22_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray22_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray22_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_23                                              *
 Description   : Read information ID 23                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_23(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray23_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray23_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray23_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray23_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray23_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray23_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray23_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_24                                              *
 Description   : Read information ID 24                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_24(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray24_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray24_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray24_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray24_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray24_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray24_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray24_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2025/6/29											  *
 Function      : CCP_vReadInf_25                                              *
 Description   : Read information ID 25                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_25(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray25_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray25_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray25_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray25_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray25_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray25_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray25_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_26                                              *
 Description   : Read information ID 26                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_26(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray26_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray26_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray26_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray26_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray26_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray26_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray26_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_27                                              *
 Description   : Read information ID 27                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_27(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray27_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray27_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray27_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray27_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray27_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray27_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray27_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_28                                              *
 Description   : Read information ID 28                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_28(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray28_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray28_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray28_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray28_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray28_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray28_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray28_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_29                                              *
 Description   : Read information ID 29                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_29(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray29_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray29_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray29_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray29_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray29_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray29_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray29_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_2A                                              *
 Description   : Read information ID 2A                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_2A(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray2A_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray2A_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray2A_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray2A_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray2A_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray2A_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray2A_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_2B                                              *
 Description   : Read information ID 2B                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_2B(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray2B_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray2B_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray2B_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray2B_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray2B_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray2B_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray2B_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_2C                                              *
 Description   : Read information ID 2C                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_2C(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray2C_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray2C_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray2C_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray2C_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray2C_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray2C_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray2C_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_2D                                              *
 Description   : Read information ID 2D                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_2D(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray2D_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray2D_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray2D_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray2D_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray2D_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray2D_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray2D_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_2E                                              *
 Description   : Read information ID 2E                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_2E(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray2E_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray2E_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray2E_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray2E_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray2E_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray2E_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray2E_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_2F                                              *
 Description   : Read information ID 2F                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_2F(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray2F_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray2F_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray2F_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray2F_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray2F_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray2F_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray2F_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_30                                              *
 Description   : Read information ID 30                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_30(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray30_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray30_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray30_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray30_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray30_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray30_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray30_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_31                                              *
 Description   : Read information ID 31                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_31(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray31_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray31_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray31_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray31_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray31_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray31_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray31_Byte7;
}


/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_32                                              *
 Description   : Read information ID 32                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_32(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray32_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray32_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray32_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray32_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray32_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray32_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray32_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_33                                              *
 Description   : Read information ID 33                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_33(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray33_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray33_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray33_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray33_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray33_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray33_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray33_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_34                                              *
 Description   : Read information ID 34                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_34(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray34_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray34_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray34_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray34_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray34_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray34_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray34_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_35                                              *
 Description   : Read information ID 35                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_35(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray35_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray35_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray35_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray35_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray35_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray35_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray35_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_36                                              *
 Description   : Read information ID 36                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_36(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray36_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray36_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray36_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray36_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray36_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray36_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray36_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_37                                              *
 Description   : Read information ID 37                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_37(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray37_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray37_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray37_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray37_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray37_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray37_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray37_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_38                                              *
 Description   : Read information ID 38                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_38(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray38_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray38_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray38_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray38_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray38_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray38_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray38_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_39                                              *
 Description   : Read information ID 39                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_39(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray39_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray39_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray39_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray39_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray39_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray39_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray39_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_3A                                              *
 Description   : Read information ID 3A                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_3A(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray3A_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray3A_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray3A_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray3A_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray3A_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray3A_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray3A_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_3B                                              *
 Description   : Read information ID 3B                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_3B(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray3B_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray3B_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray3B_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray3B_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray3B_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray3B_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray3B_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_3C                                              *
 Description   : Read information ID 3C                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_3C(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray3C_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray3C_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray3C_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray3C_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray3C_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray3C_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray3C_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_3D                                              *
 Description   : Read information ID 3D                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_3D(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray3D_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray3D_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray3D_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray3D_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray3D_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray3D_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray3D_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_3E                                              *
 Description   : Read information ID 3E                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_3E(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray3E_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray3E_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray3E_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray3E_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray3E_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray3E_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray3E_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_3F                                              *
 Description   : Read information ID 3F                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_3F(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray3F_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray3F_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray3F_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray3F_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray3F_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray3F_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray3F_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_40                                              *
 Description   : Read information ID 40                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_40(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray40_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray40_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray40_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray40_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray40_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray40_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray40_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_41                                              *
 Description   : Read information ID 41                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_41(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray41_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray41_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray41_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray41_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray41_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray41_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray41_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_42                                              *
 Description   : Read information ID 42                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_42(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray42_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray42_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray42_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray42_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray42_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray42_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray42_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_43                                              *
 Description   : Read information ID 43                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_43(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray43_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray43_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray43_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray43_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray43_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray43_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray43_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_44                                              *
 Description   : Read information ID 44                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_44(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray44_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray44_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray44_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray44_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray44_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray44_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray44_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_45                                              *
 Description   : Read information ID 45                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_45(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray45_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray45_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray45_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray45_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray45_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray45_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray45_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_46                                              *
 Description   : Read information ID 46                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_46(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray46_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray46_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray46_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray46_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray46_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray46_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray46_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_47                                              *
 Description   : Read information ID 47                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_47(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray47_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray47_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray47_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray47_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray47_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray47_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray47_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_48                                              *
 Description   : Read information ID 48                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_48(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray48_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray48_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray48_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray48_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray48_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray48_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray48_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_49                                              *
 Description   : Read information ID 49                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_49(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray49_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray49_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray49_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray49_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray49_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray49_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray49_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_4A                                              *
 Description   : Read information ID 4A                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_4A(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray4A_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray4A_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray4A_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray4A_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray4A_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray4A_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray4A_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_4B                                              *
 Description   : Read information ID 4B                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_4B(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray4B_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray4B_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray4B_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray4B_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray4B_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray4B_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray4B_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_4C                                              *
 Description   : Read information ID 4C                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_4C(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray4C_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray4C_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray4C_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray4C_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray4C_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray4C_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray4C_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_4D                                              *
 Description   : Read information ID 4D                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_4D(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray4D_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray4D_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray4D_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray4D_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray4D_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray4D_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray4D_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_4E                                              *
 Description   : Read information ID 4E                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_4E(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray4E_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray4E_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray4E_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray4E_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray4E_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray4E_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray4E_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_4F                                              *
 Description   : Read information ID 4F                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_4F(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray4F_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray4F_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray4F_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray4F_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray4F_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray4F_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray4F_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_50                                              *
 Description   : Read information ID 50                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_50(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray50_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray50_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray50_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray50_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray50_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray50_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray50_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_51                                              *
 Description   : Read information ID 51                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_51(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray51_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray51_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray51_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray51_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray51_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray51_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray51_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_52                                              *
 Description   : Read information ID 52                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_52(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray52_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray52_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray52_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray52_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray52_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray52_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray52_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_53                                              *
 Description   : Read information ID 53                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_53(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray53_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray53_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray53_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray53_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray53_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray53_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray53_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_54                                              *
 Description   : Read information ID 54                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_54(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray54_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray54_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray54_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray54_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray54_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray54_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray54_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_55                                              *
 Description   : Read information ID 55                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_55(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray55_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray55_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray55_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray55_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray55_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray55_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray55_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_56                                              *
 Description   : Read information ID 56                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_56(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray56_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray56_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray56_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray56_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray56_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray56_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray56_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_57                                              *
 Description   : Read information ID 57                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_57(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray57_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray57_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray57_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray57_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray57_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray57_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray57_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_58                                              *
 Description   : Read information ID 58                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_58(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray58_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray58_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray58_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray58_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray58_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray58_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray58_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_59                                              *
 Description   : Read information ID 59                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_59(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray59_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray59_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray59_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray59_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray59_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray59_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray59_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_5A                                              *
 Description   : Read information ID 5A                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_5A(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray5A_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray5A_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray5A_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray5A_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray5A_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray5A_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray5A_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_5B                                              *
 Description   : Read information ID 5B                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_5B(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray5B_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray5B_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray5B_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray5B_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray5B_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray5B_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray5B_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_5C                                              *
 Description   : Read information ID 5C                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_5C(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray5C_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray5C_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray5C_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray5C_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray5C_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray5C_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray5C_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_5D                                              *
 Description   : Read information ID 5D                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_5D(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray5D_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray5D_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray5D_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray5D_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray5D_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray5D_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray5D_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_5E                                              *
 Description   : Read information ID 5E                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_5E(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray5E_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray5E_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray5E_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray5E_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray5E_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray5E_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray5E_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_5F                                              *
 Description   : Read information ID 5F                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_5F(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray5F_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray5F_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray5F_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray5F_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray5F_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray5F_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray5F_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_60                                              *
 Description   : Read information ID 60                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_60(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray60_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray60_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray60_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray60_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray60_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray60_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray60_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_61                                              *
 Description   : Read information ID 61                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_61(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray61_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray61_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray61_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray61_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray61_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray61_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray61_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_62                                              *
 Description   : Read information ID 62                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_62(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray62_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray62_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray62_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray62_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray62_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray62_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray62_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_63                                              *
 Description   : Read information ID 63                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_63(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray63_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray63_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray63_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray63_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray63_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray63_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray63_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_64                                              *
 Description   : Read information ID 64                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_64(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray64_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray64_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray64_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray64_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray64_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray64_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray64_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_65                                              *
 Description   : Read information ID 65                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_65(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray65_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray65_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray65_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray65_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray65_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray65_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray65_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_66                                              *
 Description   : Read information ID 66                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_66(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray66_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray66_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray66_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray66_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray66_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray66_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray66_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_67                                              *
 Description   : Read information ID 67                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_67(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray67_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray67_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray67_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray67_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray67_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray67_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray67_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_68                                              *
 Description   : Read information ID 68                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_68(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray68_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray68_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray68_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray68_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray68_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray68_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray68_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_69                                              *
 Description   : Read information ID 69                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_69(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray69_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray69_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray69_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray69_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray69_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray69_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray69_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_6A                                              *
 Description   : Read information ID 6A                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_6A(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray6A_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray6A_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray6A_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray6A_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray6A_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray6A_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray6A_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_6B                                              *
 Description   : Read information ID 6B                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_6B(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray6B_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray6B_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray6B_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray6B_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray6B_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray6B_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray6B_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_6C                                              *
 Description   : Read information ID 6C                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_6C(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray6C_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray6C_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray6C_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray6C_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray6C_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray6C_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray6C_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_6D                                              *
 Description   : Read information ID 6D                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_6D(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray6D_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray6D_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray6D_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray6D_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray6D_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray6D_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray6D_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_6E                                              *
 Description   : Read information ID 6E                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_6E(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray6E_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray6E_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray6E_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray6E_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray6E_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray6E_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray6E_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_6F                                              *
 Description   : Read information ID 6F                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_6F(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray6F_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray6F_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray6F_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray6F_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray6F_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray6F_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray6F_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_70                                              *
 Description   : Read information ID 70                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_70(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray70_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray70_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray70_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray70_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray70_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray70_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray70_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_71                                              *
 Description   : Read information ID 71                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_71(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray71_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray71_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray71_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray71_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray71_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray71_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray71_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_72                                              *
 Description   : Read information ID 72                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_72(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray72_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray72_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray72_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray72_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray72_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray72_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray72_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_73                                              *
 Description   : Read information ID 73                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_73(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray73_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray73_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray73_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray73_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray73_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray73_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray73_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_74                                              *
 Description   : Read information ID 74                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_74(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray74_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray74_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray74_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray74_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray74_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray74_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray74_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_75                                              *
 Description   : Read information ID 75                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_75(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray75_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray75_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray75_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray75_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray75_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray75_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray75_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_76                                              *
 Description   : Read information ID 76                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_76(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray76_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray76_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray76_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray76_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray76_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray76_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray76_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_77                                              *
 Description   : Read information ID 77                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_77(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray77_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray77_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray77_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray77_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray77_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray77_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray77_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_78                                              *
 Description   : Read information ID 78                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_78(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray78_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray78_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray78_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray78_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray78_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray78_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray78_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_79                                              *
 Description   : Read information ID 79                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_79(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray79_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray79_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray79_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray79_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray79_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray79_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray79_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_7A                                              *
 Description   : Read information ID 7A                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_7A(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray7A_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray7A_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray7A_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray7A_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray7A_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray7A_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray7A_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_7B                                              *
 Description   : Read information ID 7B                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_7B(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray7B_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray7B_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray7B_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray7B_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray7B_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray7B_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray7B_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_7C                                              *
 Description   : Read information ID 7C                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_7C(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray7C_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray7C_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray7C_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray7C_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray7C_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray7C_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray7C_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_7D                                              *
 Description   : Read information ID 7D                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_7D(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray7D_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray7D_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray7D_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray7D_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray7D_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray7D_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray7D_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_7E                                              *
 Description   : Read information ID 7E                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_7E(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray7E_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray7E_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray7E_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray7E_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray7E_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray7E_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray7E_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_7F                                              *
 Description   : Read information ID 7F                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_7F(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray7F_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray7F_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray7F_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray7F_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray7F_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray7F_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray7F_Byte7;
}


/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_80                                              *
 Description   : Read information ID 80                          							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_80(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray80_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray80_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray80_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray80_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray80_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray80_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray80_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_81                                              *
 Description   : Read information ID 81                          							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_81(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray81_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray81_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray81_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray81_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray81_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray81_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray81_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_82                                              *
 Description   : Read information ID 82                        							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_82(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray82_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray82_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray82_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray82_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray82_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray82_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray82_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_83                                              *
 Description   : Read information ID 83                       							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_83(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray83_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray83_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray83_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray83_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray83_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray83_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray83_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_84                                              *
 Description   : Read information ID 84                          							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_84(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray84_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray84_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray84_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray84_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray84_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray84_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray84_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_85                                              *
 Description   : Read information ID 85                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_85(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray85_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray85_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray85_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray85_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray85_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray85_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray85_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_86                                              *
 Description   : Read information ID 86                          							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_86(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray86_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray86_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray86_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray86_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray86_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray86_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray86_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_87                                              *
 Description   : Read information ID 87                          							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_87(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray87_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray87_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray87_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray87_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray87_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray87_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray87_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_88                                              *
 Description   : Read information ID 88                          							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_88(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray88_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray88_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray88_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray88_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray88_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray88_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray88_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_89                                              *
 Description   : Read information ID 89                        							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_89(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray89_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray89_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray89_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray89_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray89_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray89_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray89_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_8A                                              *
 Description   : Read information ID 8A                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_8A(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray8A_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray8A_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray8A_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray8A_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray8A_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray8A_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray8A_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_8B                                              *
 Description   : Read information ID 8B                          							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_8B(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray8B_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray8B_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray8B_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray8B_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray8B_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray8B_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray8B_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_8C                                              *
 Description   : Read information ID 8C                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_8C(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray8C_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray8C_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray8C_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray8C_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray8C_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray8C_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray8C_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_8D                                              *
 Description   : Read information ID 8D                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_8D(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray8D_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray8D_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray8D_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray8D_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray8D_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray8D_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray8D_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_8E                                              *
 Description   : Read information ID 8E                        							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_8E(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray8E_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray8E_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray8E_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray8E_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray8E_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray8E_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray8E_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_8F                                              *
 Description   : Read information ID 8F                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_8F(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray8F_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray8F_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray8F_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray8F_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray8F_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray8F_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray8F_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_90                                              *
 Description   : Read information ID 90                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_90(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray90_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray90_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray90_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray90_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray90_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray90_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray90_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_91                                              *
 Description   : Read information ID 91                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_91(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray91_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray91_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray91_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray91_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray91_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray91_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray91_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_92                                              *
 Description   : Read information ID 92                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_92(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray92_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray92_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray92_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray92_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray92_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray92_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray92_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_93                                              *
 Description   : Read information ID 93                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_93(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray93_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray93_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray93_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray93_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray93_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray93_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray93_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_94                                              *
 Description   : Read information ID 94                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_94(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray94_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray94_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray94_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray94_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray94_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray94_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray94_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_95                                              *
 Description   : Read information ID 95                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_95(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray95_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray95_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray95_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray95_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray95_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray95_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray95_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_96                                              *
 Description   : Read information ID 96                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_96(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray96_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray96_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray96_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray96_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray96_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray96_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray96_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_97                                              *
 Description   : Read information ID 97                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_97(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray97_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray97_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray97_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray97_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray97_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray97_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray97_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_98                                              *
 Description   : Read information ID 98                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_98(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray98_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray98_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray98_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray98_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray98_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray98_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray98_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_99                                              *
 Description   : Read information ID 99                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_99(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray99_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray99_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray99_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray99_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray99_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray99_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray99_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_9A                                              *
 Description   : Read information ID 9A                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_9A(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray9A_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray9A_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray9A_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray9A_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray9A_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray9A_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray9A_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_9B                                              *
 Description   : Read information ID 9B                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_9B(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray9B_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray9B_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray9B_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray9B_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray9B_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray9B_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray9B_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_9C                                              *
 Description   : Read information ID 9C                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_9C(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray9C_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray9C_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray9C_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray9C_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray9C_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray9C_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray9C_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_9D                                              *
 Description   : Read information ID 9D                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_9D(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray9D_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray9D_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray9D_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray9D_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray9D_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray9D_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray9D_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_9E                                              *
 Description   : Read information ID 9E                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_9E(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray9E_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray9E_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray9E_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray9E_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray9E_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray9E_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray9E_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_9F                                              *
 Description   : Read information ID 9F                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_9F(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArray9F_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArray9F_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArray9F_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArray9F_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArray9F_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArray9F_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArray9F_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_A0                                              *
 Description   : Read information ID A0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_A0(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayA0_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayA0_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayA0_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayA0_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayA0_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayA0_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayA0_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_A1                                              *
 Description   : Read information ID A1                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_A1(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayA1_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayA1_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayA1_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayA1_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayA1_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayA1_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayA1_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_A2                                              *
 Description   : Read information ID A2                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_A2(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayA2_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayA2_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayA2_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayA2_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayA2_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayA2_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayA2_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_A3                                              *
 Description   : Read information ID A3                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_A3(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayA3_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayA3_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayA3_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayA3_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayA3_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayA3_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayA3_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_A4                                              *
 Description   : Read information ID A4                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_A4(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayA4_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayA4_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayA4_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayA4_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayA4_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayA4_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayA4_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_A5                                              *
 Description   : Read information ID A5                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_A5(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayA5_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayA5_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayA5_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayA5_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayA5_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayA5_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayA5_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_A6                                              *
 Description   : Read information ID A6                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_A6(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayA6_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayA6_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayA6_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayA6_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayA6_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayA6_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayA6_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_A7                                              *
 Description   : Read information ID A7                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_A7(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayA7_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayA7_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayA7_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayA7_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayA7_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayA7_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayA7_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_A8                                              *
 Description   : Read information ID A8                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_A8(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayA8_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayA8_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayA8_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayA8_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayA8_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayA8_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayA8_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_A9                                              *
 Description   : Read information ID A9                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_A9(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayA9_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayA9_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayA9_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayA9_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayA9_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayA9_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayA9_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_AA                                              *
 Description   : Read information ID AA                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_AA(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayAA_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayAA_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayAA_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayAA_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayAA_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayAA_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayAA_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_AB                                              *
 Description   : Read information ID AB                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_AB(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayAB_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayAB_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayAB_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayAB_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayAB_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayAB_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayAB_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_AC                                              *
 Description   : Read information ID AC                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_AC(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayAC_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayAC_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayAC_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayAC_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayAC_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayAC_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayAC_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_AD                                              *
 Description   : Read information ID AD                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_AD(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayAD_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayAD_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayAD_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayAD_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayAD_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayAD_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayAD_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_AE                                              *
 Description   : Read information ID AE                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_AE(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayAE_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayAE_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayAE_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayAE_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayAE_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayAE_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayAE_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/29											  *
 Function      : CCP_vReadInf_AF                                              *
 Description   : Read information ID AF                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_AF(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayAF_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayAF_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayAF_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayAF_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayAF_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayAF_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayAF_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_B0                                              *
 Description   : Read information ID B0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_B0(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayB0_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayB0_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayB0_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayB0_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayB0_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayB0_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayB0_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_B1                                              *
 Description   : Read information ID B1                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_B1(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayB1_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayB1_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayB1_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayB1_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayB1_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayB1_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayB1_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_B2                                              *
 Description   : Read information ID B2                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_B2(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayB2_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayB2_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayB2_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayB2_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayB2_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayB2_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayB2_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_B3                                              *
 Description   : Read information ID B3                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_B3(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayB3_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayB3_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayB3_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayB3_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayB3_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayB3_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayB3_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_B4                                              *
 Description   : Read information ID B4                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_B4(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayB4_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayB4_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayB4_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayB4_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayB4_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayB4_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayB4_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_B5                                              *
 Description   : Read information ID B5                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_B5(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayB5_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayB5_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayB5_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayB5_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayB5_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayB5_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayB5_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_B6                                              *
 Description   : Read information ID B6                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_B6(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayB6_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayB6_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayB6_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayB6_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayB6_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayB6_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayB6_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_B7                                              *
 Description   : Read information ID B7                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_B7(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayB7_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayB7_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayB7_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayB7_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayB7_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayB7_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayB7_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_B8                                              *
 Description   : Read information ID B8                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_B8(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayB8_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayB8_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayB8_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayB8_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayB8_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayB8_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayB8_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_B9                                              *
 Description   : Read information ID B9                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_B9(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayB9_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayB9_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayB9_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayB9_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayB9_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayB9_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayB9_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_BA                                              *
 Description   : Read information ID BA                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_BA(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayBA_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayBA_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayBA_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayBA_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayBA_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayBA_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayBA_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_BB                                              *
 Description   : Read information ID BB                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_BB(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayBB_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayBB_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayBB_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayBB_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayBB_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayBB_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayBB_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_BC                                              *
 Description   : Read information ID BC                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_BC(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayBC_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayBC_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayBC_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayBC_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayBC_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayBC_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayBC_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_BD                                              *
 Description   : Read information ID BD                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_BD(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayBD_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayBD_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayBD_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayBD_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayBD_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayBD_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayBD_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_BE                                              *
 Description   : Read information ID BE                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_BE(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayBE_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayBE_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayBE_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayBE_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayBE_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayBE_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayBE_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_BF                                              *
 Description   : Read information ID BF                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_BF(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayBF_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayBF_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayBF_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayBF_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayBF_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayBF_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayBF_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_C0                                              *
 Description   : Read information ID C0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_C0(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayC0_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayC0_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayC0_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayC0_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayC0_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayC0_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayC0_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_C1                                              *
 Description   : Read information ID C1                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_C1(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayC1_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayC1_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayC1_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayC1_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayC1_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayC1_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayC1_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_C2                                              *
 Description   : Read information ID C2                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_C2(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayC2_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayC2_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayC2_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayC2_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayC2_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayC2_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayC2_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_C3                                              *
 Description   : Read information ID C3                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_C3(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayC3_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayC3_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayC3_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayC3_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayC3_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayC3_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayC3_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_C4                                              *
 Description   : Read information ID C4                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_C4(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayC4_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayC4_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayC4_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayC4_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayC4_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayC4_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayC4_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_C5                                              *
 Description   : Read information ID C5                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_C5(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayC5_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayC5_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayC5_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayC5_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayC5_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayC5_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayC5_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_C6                                              *
 Description   : Read information ID C6                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_C6(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayC6_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayC6_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayC6_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayC6_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayC6_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayC6_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayC6_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_C7                                              *
 Description   : Read information ID C7                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_C7(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayC7_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayC7_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayC7_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayC7_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayC7_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayC7_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayC7_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_C8                                              *
 Description   : Read information ID C8                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_C8(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayC8_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayC8_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayC8_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayC8_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayC8_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayC8_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayC8_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_C9                                              *
 Description   : Read information ID C9                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_C9(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayC9_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayC9_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayC9_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayC9_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayC9_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayC9_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayC9_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_CA                                              *
 Description   : Read information ID CA                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_CA(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayCA_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayCA_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayCA_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayCA_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayCA_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayCA_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayCA_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_CB                                              *
 Description   : Read information ID CB                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_CB(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayCB_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayCB_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayCB_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayCB_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayCB_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayCB_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayCB_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_CC                                              *
 Description   : Read information ID CC                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_CC(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayCC_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayCC_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayCC_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayCC_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayCC_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayCC_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayCC_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_CD                                              *
 Description   : Read information ID CD                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_CD(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayCD_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayCD_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayCD_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayCD_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayCD_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayCD_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayCD_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_CE                                              *
 Description   : Read information ID CE                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_CE(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayCE_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayCE_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayCE_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayCE_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayCE_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayCE_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayCE_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_CF                                              *
 Description   : Read information ID CF                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_CF(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayCF_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayCF_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayCF_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayCF_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayCF_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayCF_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayCF_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_D0(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayD0_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayD0_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayD0_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayD0_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayD0_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayD0_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayD0_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_D1(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayD1_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayD1_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayD1_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayD1_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayD1_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayD1_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayD1_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_D2(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayD2_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayD2_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayD2_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayD2_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayD2_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayD2_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayD2_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_D3(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayD3_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayD3_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayD3_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayD3_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayD3_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayD3_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayD3_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_D4(void)
{
	//uint8 u8ModuleName[5]={0,0,0,0,0};/*Release Warning,161024*/
	//VER_vReadOutModuleName(MODULE_NAME,&u8ModuleName[0]);
	CCP_stDatastrct.u8Data1 = CCP_ModelName[0];
	CCP_stDatastrct.u8Data2 = CCP_ModelName[1];
	CCP_stDatastrct.u8Data3 = CCP_ModelName[2];
	CCP_stDatastrct.u8Data4 = CCP_ModelName[3];
	CCP_stDatastrct.u8Data5 = CCP_ModelName[4];
	CCP_stDatastrct.u8Data6 = 0;
	CCP_stDatastrct.u8Data7 = 0;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_D5(void)
{
    //VER_vReadOutSWVersion(SW_VERSION_INTERNAL,&u8SWVersion[0]); 
	CCP_stDatastrct.u8Data1 = (uint8)(SW_VERSION_INTERNAL>>8u);
	CCP_stDatastrct.u8Data2 = (uint8)(SW_VERSION_INTERNAL&0xFF);
	CCP_stDatastrct.u8Data3 = (uint8)((SW_VERSION_DATE>>16u)&0xFF);
	CCP_stDatastrct.u8Data4 = (uint8)((SW_VERSION_DATE>>8u)&0xFF);
	CCP_stDatastrct.u8Data5 = (uint8)(SW_VERSION_DATE&0xFF);;
	CCP_stDatastrct.u8Data6 = NO_USE;
	CCP_stDatastrct.u8Data7 = NO_USE;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_D6(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayD6_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayD6_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayD6_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayD6_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayD6_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayD6_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayD6_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_D7(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayD7_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayD7_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayD7_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayD7_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayD7_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayD7_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayD7_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_D8(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayD8_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayD8_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayD8_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayD8_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayD8_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayD8_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayD8_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_D9(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayD9_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayD9_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayD9_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayD9_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayD9_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayD9_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayD9_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_DA(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayDA_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayDA_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayDA_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayDA_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayDA_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayDA_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayDA_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_DB(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayDB_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayDB_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayDB_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayDB_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayDB_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayDB_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayDB_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_DC(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayDC_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayDC_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayDC_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayDC_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayDC_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayDC_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayDC_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_DD(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayDD_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayDD_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayDD_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayDD_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayDD_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayDD_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayDD_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_DE(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayDE_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayDE_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayDE_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayDE_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayDE_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayDE_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayDE_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_DF(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayDF_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayDF_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayDF_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayDF_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayDF_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayDF_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayDF_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_E0(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayE0_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayE0_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayE0_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayE0_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayE0_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayE0_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayE0_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_E1(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayE1_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayE1_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayE1_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayE1_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayE1_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayE1_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayE1_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_E2(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayE2_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayE2_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayE2_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayE2_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayE2_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayE2_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayE2_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_E3(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayE3_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayE3_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayE3_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayE3_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayE3_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayE3_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayE3_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_E4(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayE4_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayE4_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayE4_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayE4_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayE4_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayE4_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayE4_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_E5(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayE5_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayE5_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayE5_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayE5_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayE5_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayE5_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayE5_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_E6(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayE6_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayE6_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayE6_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayE6_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayE6_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayE6_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayE6_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_E7(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayE7_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayE7_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayE7_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayE7_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayE7_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayE7_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayE7_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_E8(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayE8_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayE8_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayE8_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayE8_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayE8_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayE8_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayE8_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_E9(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayE9_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayE9_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayE9_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayE9_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayE9_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayE9_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayE9_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_EA(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayEA_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayEA_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayEA_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayEA_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayEA_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayEA_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayEA_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_EB(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayEB_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayEB_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayEB_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayEB_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayEB_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayEB_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayEB_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_EC(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayEC_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayEC_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayEC_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayEC_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayEC_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayEC_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayEC_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_EC                                              *
 Description   : Read information ID EC                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_ED(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayED_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayED_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayED_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayED_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayED_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayED_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayED_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_EE(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayEE_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayEE_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayEE_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayEE_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayEE_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayEE_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayEE_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_EF(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayEF_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayEF_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayEF_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayEF_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayEF_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayEF_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayEF_Byte7;
}


/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_F0(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayF0_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayF0_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayF0_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayF0_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayF0_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayF0_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayF0_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_F1(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayF1_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayF1_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayF1_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayF1_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayF1_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayF1_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayF1_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_F2(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayF2_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayF2_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayF2_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayF2_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayF2_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayF2_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayF2_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_F3(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayF3_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayF3_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayF3_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayF3_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayF3_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayF3_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayF3_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_F4(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayF4_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayF4_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayF4_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayF4_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayF4_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayF4_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayF4_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_F5(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayF5_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayF5_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayF5_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayF5_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayF5_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayF5_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayF5_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_F6(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayF6_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayF6_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayF6_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayF6_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayF6_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayF6_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayF6_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_F7(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayF7_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayF7_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayF7_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayF7_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayF7_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayF7_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayF7_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_F8(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayF8_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayF8_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayF8_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayF8_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayF8_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayF8_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayF8_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_F9(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayF9_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayF9_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayF9_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayF9_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayF9_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayF9_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayF9_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_FA(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayFA_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayFA_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayFA_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayFA_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayFA_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayFA_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayFA_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_FB(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayFB_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayFB_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayFB_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayFB_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayFB_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayFB_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayFB_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_FC(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayFC_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayFC_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayFC_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayFC_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayFC_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayFC_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayFC_Byte7;
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_FD(void)
{
	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayFD_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayFD_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayFD_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayFD_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayFD_Byte5;
	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayFD_Byte6;
	CCP_stDatastrct.u8Data7 = CCP_u8DataArrayFD_Byte7;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vReadInf_D0                                              *
 Description   : Read information ID D0                         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadInf_FE(void)
{


	CCP_stDatastrct.u8Data1 = CCP_u8DataArrayFE_Byte1;
	CCP_stDatastrct.u8Data2 = CCP_u8DataArrayFE_Byte2;
	CCP_stDatastrct.u8Data3 = CCP_u8DataArrayFE_Byte3;
	CCP_stDatastrct.u8Data4 = CCP_u8DataArrayFE_Byte4;
	CCP_stDatastrct.u8Data5 = CCP_u8DataArrayFE_Byte5;
 	CCP_stDatastrct.u8Data6 = CCP_u8DataArrayFE_Byte6;
       CCP_stDatastrct.u8Data7 = CCP_u8DataArrayFE_Byte7;	
	
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_10                                              *
 Description   : Control Aqs status                           							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_10(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_11                                              *
 Description   : Control Aqs voltage                           							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_11(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_12                                             *
 Description   : Control Airdistribution set position                           							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_12(void)
{	
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	AIRD_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_13                                              *
 Description   : Control compressor actual request                           							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_13(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_14                                              *
 Description   : Control blower voltage compensation in CCS module                           							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_14(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
     BCTL_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_15                                              *
 Description   : Control blower target                          							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_15(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=3;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=4;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
    BCTL_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_16                                              *
 Description   : Control blower feed back voltage                        							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_16(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=5;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=6;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;

	BCTL_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_17                                              *
 Description   : Control rear blowerout temperature in CCS module                     							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_17(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_18                                              *
 Description   : Control driver blowerout temperature in CCS module                     							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_18(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;	
    CCS_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_19                                              *
 Description   : Control passenger blowerout temperature in CCS module                     							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_19(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=3;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=4;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;	
    CCS_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_1A                                              *
 Description   : Control air mix driver motor feed back voltage                     							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_1A(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	DCM_u8ForceIoControl_Write(Ccp_ControlData);
   }

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_1B                                              *
 Description   : Control air mix passenger motor feed back voltage                     							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_1B(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_1C                                              *
 Description   : Control rear air mix motor feed back voltage                     							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_1C(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_1D                                              *
 Description   : Control airdistribution motor feed back voltage                     							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_1D(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=3;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=4;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	DCM_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_1E                                              *
 Description   : Control fresh and recircution motor feed back voltage                     							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_1E(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_1F                                              *
 Description   : Control evaporator sensor voltage                     							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_1F(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
   EVAP_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_20                                              *
 Description   : Control evaporator sensor temperature                     							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_20(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=3;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=4;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	EVAP_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_21                                              *
 Description   : Control heat core temperature                     							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_21(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
    HCT_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_22                                              *
 Description   : Control ION small dirty                     							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_22(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_23                                              *
 Description   : Control ION bigl dirty                     							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_23(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_24                                              *
 Description   : Control ION time                    							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_24(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_25                                              *
 Description   : Control in car temperature                    							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_25(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//ICT_u8ForceIoControl_Write(Ccp_ControlData);	
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_26                                              *
 Description   : Control in car temperature sensor voltage                 							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_26(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_27                                              *
 Description   : Control key pressed                 							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_27(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	KEY_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_28                                              *
 Description   : Control knob action                 							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_28(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_29                                              *
 Description   : Control air mix driver position                 							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_29(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	MAC_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_2A                                              *
 Description   : Control air mix passenger position                 							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_2A(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=5;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=6;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	MAC_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_2B                                              *
 Description   : Control driver blower out temperature in MAC module                							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_2B(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=3;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=4;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	MAC_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_2C                                              *
 Description   : Control passenger blower out temperature in MAC module                							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_2C(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=7;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=8;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	MAC_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_2D                                              *
 Description   : Control rear blower out temperature in MAC module                							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_2D(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_2E                                              *
 Description   : Control ambient temperature                							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_2E(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=3;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=4;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	OAT_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_2F                                              *
 Description   : Control ambient temperature sensor voltage               							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_2F(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	OAT_u8ForceIoControl_Write(Ccp_ControlData);
	
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_30                                              *
 Description   : Control 5v voltage               							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_30(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_31                                              *
 Description   : Control KL30 voltage               							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_31(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=3;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=4;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//POW_ForceIoControl_Write(Ccp_ControlData);
    //CCP_au32Array[CCP_nu32CidPow] = Ccp_ControlData;
	POW_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_32                                              *
 Description   : Control KL15 voltage               							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_32(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_33                                              *
 Description   : Control intake position               							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_33(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
    RFA_ForceIoControl_Write(Ccp_ControlData);
	
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_34                                              *
 Description   : Control fresh and recirculation time               							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_34(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=3;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=4;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
    RFA_ForceIoControl_Write(Ccp_ControlData);

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_35                                              *
 Description   : Control rear defrost run time               							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_35(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
    //CCP_au32Array[CCP_nu32CidRdc] = Ccp_ControlData;

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_36                                              *
 Description   : Control rear defrost status               							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_36(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=3;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=4;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
   // CCP_au32Array[CCP_nu32CidRdc] = Ccp_ControlData;

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_37                                              *
 Description   : Control engine speed               							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_37(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_38                                              *
 Description   : Control driver sun sensor value               							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_38(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
    //CCP_au32Array[CCP_nu32CidSun] = Ccp_ControlData;
	SUN_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_39                                              *
 Description   : Control passenger sun sensor value               							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_39(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=3;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=4;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
    //CCP_au32Array[CCP_nu32CidSun] = Ccp_ControlData;
    SUN_u8ForceIoControl_Write(Ccp_ControlData);
	
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_3A                                              *
 Description   : Control driver sensor voltage           							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_3A(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_3B                                              *
 Description   : Control passenger voltage         							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_3B(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vIoControl_3C                                              *
 Description   : Control vehicle speed						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_3C(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//Vel_ForceIoControl_Write(Ccp_ControlData);
    //CCP_au32Array[CCP_nu32CidVel] = Ccp_ControlData;
	VEL_u8ForceIoControl_Write(Ccp_ControlData);
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_3D                                              *
 Description   : Acc Requirest						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_3D(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
    ACCC_u8ForceIoControl_Write(Ccp_ControlData); /*ACCC*/
	
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_3E                                              *
 Description   : Acc compresser target speed					  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_3E(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=3;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=4;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
    	//ACCC_vCcpControl(Ccp_ControlData);
	//ACCC_u8ForceIoControl_Write(Ccp_ControlData); /*ACCC*/
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_3F                                              *
 Description   : Acc ouput Evap Target Tempt						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_3F(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	MAC_u8ForceIoControl_Write(Ccp_ControlData);/*Dr*/

	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=5;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=6;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data5;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data6;
	MAC_u8ForceIoControl_Write(Ccp_ControlData);/*Ps*/
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_40                                              *
 Description   : 					  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_40(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=11;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=12;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//CCP_au32Array[CCP_nu32CidHct] = Ccp_ControlData;
	HCT_u8ForceIoControl_Write(Ccp_ControlData);
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_41                                              *
 Description   : Acc High fan speed req					  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_41(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=7;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=8;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
    	//ACCC_vCcpControl(Ccp_ControlData);
	//ACCC_u8ForceIoControl_Write(Ccp_ControlData); /*ACCC*/
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_42                                              *
 Description   : 	Ac press hilo				  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_42(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=9;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=10;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
    	//ACCC_vCcpControl(Ccp_ControlData);
	//ACCC_u8ForceIoControl_Write(Ccp_ControlData); /*ACCC*/	
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_43                                              *
 Description   : 		Ac press mid			  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_43(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=11;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=12;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
    //ACCC_vCcpControl(Ccp_ControlData);
	//ACCC_u8ForceIoControl_Write(Ccp_ControlData); /*ACCC*/
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_44                                              *
 Description   : 					  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_44(void)
{
	
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_45                                              *
 Description   : 					  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_45(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=5;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=6;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
    //CCP_au32Array[CCP_nu32CidHct] = Ccp_ControlData;
	HCT_u8ForceIoControl_Write(Ccp_ControlData); 
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_46                                              *
 Description   : 					  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_46(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=7;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=8;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//CCP_au32Array[CCP_nu32CidHct] = Ccp_ControlData;
	//HCT_u8ForceIoControl_Write(Ccp_ControlData);
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_47                                              *
 Description   : 					  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_47(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=9;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=10;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//CCP_au32Array[CCP_nu32CidHct] = Ccp_ControlData;
	//HCT_u8ForceIoControl_Write(Ccp_ControlData);
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_48                                              *
 Description   : 	Kp control for Accc				  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_48(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=13;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=14;
			break;
		default:
			
			break;		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//ACCC_vCcpControl(Ccp_ControlData);
	//ACCC_u8ForceIoControl_Write(Ccp_ControlData);
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_49                                              *
 Description   : 	Ki control for Accc				  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_49(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=15;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=16;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//ACCC_vCcpControl(Ccp_ControlData);
	//ACCC_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_4A                                              *
 Description   : Battery pack temperature heat/refrigeration Req control					  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_4A(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=7;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=8;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//VTM_u8ForceIoControl_Write(Ccp_ControlData);
	//Rte_Call_CcpWriteBptForceData_ForceIoControlData(Ccp_ControlData);	
    
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_4B                                           *
 Description   :				  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_4B(void)
{
    	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=2;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=0;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//Btm_u8ForceIoControl_Write(Ccp_ControlData);
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=21;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=22;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//VTM_u8ForceIoControl_Write(Ccp_ControlData);

}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_4C                                           *
 Description   :				  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_4C(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=3;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=0;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//Btm_u8ForceIoControl_Write(Ccp_ControlData);

	//Rte_Call_CcpWriteBptForceData_ForceIoControlData(Ccp_ControlData);	
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_4D                                          *
 Description   :				  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_4D(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=4;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=0;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//Btm_u8ForceIoControl_Write(Ccp_ControlData);
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=23;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=24;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//VTM_u8ForceIoControl_Write(Ccp_ControlData);
}
/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_4F                                           *
 Description   :				  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_4E(void)
{
    	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=5;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=0;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//Btm_u8ForceIoControl_Write(Ccp_ControlData);
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=25;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=26;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//VTM_u8ForceIoControl_Write(Ccp_ControlData);

}

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_4E                                           *
 Description   :				  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_4F(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=13;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=14;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//CCP_au32Array[CCP_nu32CidHct] = Ccp_ControlData;
	//HCT_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_4E                                           *
 Description   :				  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_50(void)
{
    	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=6;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=0;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//Btm_u8ForceIoControl_Write(Ccp_ControlData);
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=9;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=10;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//VTM_u8ForceIoControl_Write(Ccp_ControlData);

}

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_4E                                           *
 Description   :				  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_51(void)
{
    	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=7;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=0;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//Btm_u8ForceIoControl_Write(Ccp_ControlData);
	//Rte_Call_CcpWriteBptForceData_ForceIoControlData(Ccp_ControlData);	

}

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_4E                                           *
 Description   :				  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_52(void)
{
    	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=8;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=0;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//Btm_u8ForceIoControl_Write(Ccp_ControlData);
	//Rte_Call_CcpWriteBptForceData_ForceIoControlData(Ccp_ControlData);	

}

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_4E                                           *
 Description   :				  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_53(void)
{
    	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=9;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=0;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//Btm_u8ForceIoControl_Write(Ccp_ControlData);
	//Rte_Call_CcpWriteBptForceData_ForceIoControlData(Ccp_ControlData);	

}

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_4E                                           *
 Description   :				  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_54(void)
{
    	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=10;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=0;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//Btm_u8ForceIoControl_Write(Ccp_ControlData);
	//Rte_Call_CcpWriteBptForceData_ForceIoControlData(Ccp_ControlData);	

}

/*****************************************************************************
 AUTHOR:		 : Lin Tao												  *
 DATE: 		 : 2016/3/14											      *
 Function      : CCP_vIoControl_55                                        *
 Description   : Error code for OAT					                      *
 Return Value  : None                                                     *
*****************************************************************************/
static void CCP_vIoControl_55(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=11;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=0;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//Btm_u8ForceIoControl_Write(Ccp_ControlData);
}
/*****************************************************************************
 AUTHOR:		 : Lin Tao												  *
 DATE: 		 : 2016/3/14											      *
 Function      : CCP_vIoControl_56                                        *
 Description   : ThTemp for ISTP					                      *
 Return Value  : None                                                     *
*****************************************************************************/
static void CCP_vIoControl_56(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=12;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=0;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//Btm_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Lin Tao												  *
 DATE: 		 : 2016/3/14											      *
 Function      : CCP_vIoControl_57                                        *
 Description   : FpAtcPSteam					                                      *
 Return Value  : None                                                     *
*****************************************************************************/
static void CCP_vIoControl_57(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=13;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=0;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//Btm_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Lin Tao												  *
 DATE: 		 : 2016/3/14											      *
 Function      : CCP_vIoControl_58                                        *
 Description   : FpAtcFlgFogCtrl					                      *
 Return Value  : None                                                     *
*****************************************************************************/
static void CCP_vIoControl_58(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=15;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=16;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	//VTM_u8ForceIoControl_Write(Ccp_ControlData);

}
/*****************************************************************************
 AUTHOR:		 : Lin Tao												  *
 DATE: 		 : 2016/3/14											      *
 Function      : CCP_vIoControl_59                                        *
 Description   : CCP_nu16CidFpAtcTFlgFog					              *
 Return Value  : None                                                     *
*****************************************************************************/
static void CCP_vIoControl_59(void)
{

}
/*****************************************************************************
 AUTHOR:		 : Lin Tao												  *
 DATE: 		 : 2016/3/14											      *
 Function      : CCP_vIoControl_59                                        *
 Description   : CCP_nu16CidFpAtcTFlgFog					              *
 Return Value  : None                                                     *
*****************************************************************************/
static void CCP_vIoControl_5A(void)
{
}
/*****************************************************************************
 AUTHOR:		 : Lin Tao												  *
 DATE: 		 : 2016/3/14											      *
 Function      : CCP_vIoControl_59                                        *
 Description   : CCP_nu16CidFpAtcTFlgFog					              *
 Return Value  : None                                                     *
*****************************************************************************/
static void CCP_vIoControl_5B(void)
{
}
/*****************************************************************************
 AUTHOR:		 : Lin Tao												  *
 DATE: 		 : 2016/3/14											      *
 Function      : CCP_vIoControl_59                                        *
 Description   : CCP_nu16CidFpAtcTFlgFog					              *
 Return Value  : None                                                     *
*****************************************************************************/
static void CCP_vIoControl_5C(void)
{
}
/*****************************************************************************
 AUTHOR:		 : Lin Tao												  *
 DATE: 		 : 2016/3/14											      *
 Function      : CCP_vIoControl_59                                        *
 Description   : CCP_nu16CidFpAtcTFlgFog					              *
 Return Value  : None                                                     *
*****************************************************************************/
static void CCP_vIoControl_5D(void)
{
}
/*****************************************************************************
 AUTHOR:		 : Lin Tao												  *
 DATE: 		 : 2016/3/14											      *
 Function      : CCP_vIoControl_59                                        *
 Description   : CCP_nu16CidFpAtcTFlgFog					              *
 Return Value  : None                                                     *
*****************************************************************************/
static void CCP_vIoControl_5E(void)
{
}
/*****************************************************************************
 AUTHOR:		 : Lin Tao												  *
 DATE: 		 : 2016/3/14											      *
 Function      : CCP_vIoControl_59                                        *
 Description   : CCP_nu16CidFpAtcTFlgFog					              *
 Return Value  : None                                                     *
*****************************************************************************/
static void CCP_vIoControl_5F(void)
{
}

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_4A                                              *
 Description   : 					  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_60(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=1;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=2;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	CTS_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_4A                                              *
 Description   : 					  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_61(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=3;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=4;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	CTS_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_62                                              *
 Description   : 					  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_62(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=5;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=6;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	CTS_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/7/20											  *
 Function      : CCP_vIoControl_63                                              *
 Description   : 					  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vIoControl_63(void)
{
	uint32 Ccp_ControlData;
	Ccp_ControlData=1;
	Ccp_ControlData<<=8;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case CCP_ADJUST_CONTROL:
			Ccp_ControlData|=7;
			break;
		case CCP_NORMAL_CONTROL:
			Ccp_ControlData|=8;
			break;
		default:
			
			break;
		
	}
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data3;
	Ccp_ControlData<<=8;
	Ccp_ControlData|=CCP_stCmdPtr.u8Data4;
	CTS_u8ForceIoControl_Write(Ccp_ControlData);
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_21                                              *
 Description   : PTS Digital Port Control						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_21(void)
{
	uint32 Ccp_ControlData=0u;

	switch(CCP_stCmdPtr.u8Data2) /*Control sub Type*/
	{
        case 1:/*AC digital*/
			Ccp_ControlData = CCP_nu32AcccActualReqPTSForce;		
			Ccp_ControlData |= (CCP_stCmdPtr.u8Data3&0x01u);
            CCP_WriteAcccForceData(Ccp_ControlData);
            break;
		case 2:/*5v Output*/	
			Ccp_ControlData = CCP_nu32Pow5vOutPutPTSForce;		
			Ccp_ControlData |= (CCP_stCmdPtr.u8Data3&0x01u);	
			CCP_WritePowForceData(Ccp_ControlData);
			break;	
		case 3:/*sensor supply*/
			Ccp_ControlData = CCP_nu32PowSenSupplyPTSForce;
			Ccp_ControlData|= (CCP_stCmdPtr.u8Data3&0x01u);
			CCP_WritePowForceData(Ccp_ControlData);
			break;	
        case 4:
			Ccp_ControlData=CCP_nu32RdcPTSCtr;/*Rear defrost control*/
			Ccp_ControlData|=CCP_stCmdPtr.u8Data3;	
			CCP_WriteRdcForceData(Ccp_ControlData);
			break;
        /*User define*/ 
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
		case 6:/*PM25 Clean mode port*/
			Ccp_ControlData = CCP_nu32IONPM25CleanModePTSForce;
			Ccp_ControlData|= (CCP_stCmdPtr.u8Data3&0x01u);
			CCP_WriteIonForceData(Ccp_ControlData);
			break;	
		case 7:/*PM25 Ion mode port*/
			Ccp_ControlData = CCP_nu32IONPM25IonModePTSForce;
			Ccp_ControlData|= (CCP_stCmdPtr.u8Data3&0x01u);
			CCP_WriteIonForceData(Ccp_ControlData);
			break;
#endif
#if(CarConfiguration == High_End)
		case 8:
			Ccp_ControlData=CCP_nu32ShcLPTSCtr;/*Seat Heating Left*/
			Ccp_ControlData|=CCP_stCmdPtr.u8Data3;	
			CCP_WriteShcForceData(Ccp_ControlData);
			break;

		case 9:
			Ccp_ControlData=CCP_nu32ShcRPTSCtr;/*Seat Heating Right*/		
			Ccp_ControlData|=CCP_stCmdPtr.u8Data3;	
			CCP_WriteShcForceData(Ccp_ControlData);	
			break;
#endif
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
		case 10:/*PM25 Power*/
			Ccp_ControlData = CCP_nu32IONPM25OutPutPTSForce;
			Ccp_ControlData|= (CCP_stCmdPtr.u8Data3&0x01u);
			CCP_WriteIonForceData(Ccp_ControlData);
			break;
			break;
#endif
		case 0xFF:/*all the channel*/
			if(CCP_stCmdPtr.u8Data3==0xFFu)
			{
				CCP_WritePowForceData(0u);	
				CCP_WriteAcccForceData(0u);
                CCP_WriteRdcForceData(0u);
				CCP_WriteIonForceData(0u);/*161112*/
                CCP_WriteShcForceData(0u);
				//CCP_WriteDimForceData(0u);
			}
			else if((CCP_stCmdPtr.u8Data3==0x00u)||(CCP_stCmdPtr.u8Data3==0x01u))
			{
    			Ccp_ControlData = CCP_nu8AcccActualReqPTSForce;		
    			Ccp_ControlData |= CCP_stCmdPtr.u8Data3;
                CCP_WriteAcccForceData(Ccp_ControlData);

				Ccp_ControlData = CCP_nu32Pow5vOutPutPTSForce;		
    			Ccp_ControlData |= CCP_stCmdPtr.u8Data3;	
    			CCP_WritePowForceData(Ccp_ControlData);
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
				Ccp_ControlData = CCP_nu32IONPM25OutPutPTSForce;
				Ccp_ControlData|= CCP_stCmdPtr.u8Data3;
				CCP_WriteIonForceData(Ccp_ControlData);

    			Ccp_ControlData = CCP_nu32IONPM25CleanModePTSForce;
    			Ccp_ControlData|= (CCP_stCmdPtr.u8Data3&0x01u);
    			CCP_WriteIonForceData(Ccp_ControlData);

    			Ccp_ControlData = CCP_nu32IONPM25IonModePTSForce;
    			Ccp_ControlData|= (CCP_stCmdPtr.u8Data3&0x01u);
    			CCP_WriteIonForceData(Ccp_ControlData);
#endif
#if(CarConfiguration == High_End)
    			Ccp_ControlData=CCP_nu32ShcLPTSCtr;/*Seat Heating Left*/
    			Ccp_ControlData|=CCP_stCmdPtr.u8Data3;	
    			CCP_WriteShcForceData(Ccp_ControlData);

    			Ccp_ControlData=CCP_nu32ShcRPTSCtr;/*Seat Heating Right*/		
    			Ccp_ControlData|=CCP_stCmdPtr.u8Data3;	
    			CCP_WriteShcForceData(Ccp_ControlData);	
#endif
    			Ccp_ControlData=CCP_nu32RdcPTSCtr;/*Rear defrost control*/
    			Ccp_ControlData|=CCP_stCmdPtr.u8Data3;	
    			CCP_WriteRdcForceData(Ccp_ControlData);

				Ccp_ControlData = CCP_nu32PowSenSupplyPTSForce;
    			Ccp_ControlData|= CCP_stCmdPtr.u8Data3;
    			CCP_WritePowForceData(Ccp_ControlData);
			}
            else
            {
                /*Do noting*/
            }
		break;
		default:
        break;
		
	}
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_22                                              *
 Description   : PTS LCD control						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_22(void)
{
	uint32 Ccp_ControlData;
    
    /*should turn on the Lcd PWM first*/
	Ccp_ControlData = CCP_nu32LcdPWMPTSForce;/*Control the Symbol PWM*/
	Ccp_ControlData|= 100;	/*PWM=100%*/
	CCP_WriteDimForceData(Ccp_ControlData);  
    
	switch(CCP_stCmdPtr.u8Data2)
	{
		case 0:/*All Segments OFF*/
			Ccp_ControlData = CCP_nu32LcdTestPTSCtr;
			Ccp_ControlData|= CCP_nu8LcdAllOffCtr;	
			break;        
		case 1:/*All Segments on*/
			Ccp_ControlData = CCP_nu32LcdTestPTSCtr;
			Ccp_ControlData|= CCP_nu8LcdAllOnCtr;		
			break;
		case 2:/*LCD Odd Segment ON, LCD Even Segment OFF*/
			Ccp_ControlData = CCP_nu32LcdTestPTSCtr;
			Ccp_ControlData|= CCP_nu8LcdOddSegOnCtr;	
			break;
		case 3:/*LCD Odd Segment OFF, LCD Even Segment ON*/
			Ccp_ControlData = CCP_nu32LcdTestPTSCtr;
			Ccp_ControlData|= CCP_nu8LcdEvenSegOnCtr;	
			break;
		case 4:/*COM1&COM3 ON COM2&COM4 OFF*/
			Ccp_ControlData = CCP_nu32LcdTestPTSCtr;
			Ccp_ControlData|= CCP_nu8LcdOddComOnCtr;	
			break;
		case 5:/*COM1&COM3 Off COM2&COM4 On*/
			Ccp_ControlData = CCP_nu32LcdTestPTSCtr;
			Ccp_ControlData|= CCP_nu8LcdEvenComOnCtr;		
			break;
    	case 6:/*COM1 ON,Com2,COM3 COM4 OFF*/
    		Ccp_ControlData = CCP_nu32LcdTestPTSCtr;
    		Ccp_ControlData|= CCP_nu8LcdOnlyCom1OnCtr;	
		    break;  
    	case 7:/*COM2 ON,Com1,COM3 COM4 OFF*/
    		Ccp_ControlData = CCP_nu32LcdTestPTSCtr;
    		Ccp_ControlData|= CCP_nu8LcdOnlyCom2OnCtr;		
		    break;     
    	case 8:/*COM3 ON,Com1,COM2 COM4 OFF*/
    		Ccp_ControlData = CCP_nu32LcdTestPTSCtr;
    		Ccp_ControlData|= CCP_nu8LcdOnlyCom3OnCtr;		
		    break;  
    	case 9:/*COM4 ON,Com1,COM2 COM3 OFF*/
    		Ccp_ControlData = CCP_nu32LcdTestPTSCtr;
    		Ccp_ControlData|= CCP_nu8LcdOnlyCom4OnCtr;	
            break;
		default:			
		break;
		
	}
    CCP_WriteLcdForceData(Ccp_ControlData);
    
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_23                                              *
 Description   : PTS LED control						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_23(void)
{
	uint32 Ccp_ControlData;
    uint16 u16LedData;

    /*Set the LED PWM to default value*/
	Ccp_ControlData = CCP_nu32LedPWMPTSForce;	
	Ccp_ControlData|= 100;	/*Set PWM to 100%*/
	CCP_WriteDimForceData(Ccp_ControlData);	
    
	switch(CCP_stCmdPtr.u8Data2)/*Control sub type*/
	{
		case 1:
            /*Group 1 Led*/
			Ccp_ControlData =CCP_nu32LedGroup1PTSForce;/*LED control*/	
            u16LedData = ((uint16)CCP_stCmdPtr.u8Data3<<8u)|CCP_stCmdPtr.u8Data4;
			Ccp_ControlData|= u16LedData;			
			CCP_WriteDimForceData(Ccp_ControlData);
            /*Group 2 Led*/
			Ccp_ControlData =CCP_nu32LedGroup2PTSForce;/*LED control*/	
            u16LedData = ((uint16)CCP_stCmdPtr.u8Data5<<8u)|CCP_stCmdPtr.u8Data6;
			Ccp_ControlData|= u16LedData;			
			CCP_WriteDimForceData(Ccp_ControlData);            
			break;
		default:			
		break;
		
	}
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_24                                              *
 Description   : PTS DIM control						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_24(void)
{
	uint32 Ccp_ControlData;

	switch(CCP_stCmdPtr.u8Data2)/*Control sub type*/
	{
		case 1:/*LED PWM*/	
			Ccp_ControlData = CCP_nu32LedPWMPTSForce;	/*Control the Led1 PWM*/
			Ccp_ControlData|= CCP_stCmdPtr.u8Data3;	
			CCP_WriteDimForceData(Ccp_ControlData);	
			break;
        case 2:/*LCD PWM*/
			Ccp_ControlData = CCP_nu32LcdPWMPTSForce;	/*Control the Lcd PWM*/
			Ccp_ControlData|= CCP_stCmdPtr.u8Data3;	
			CCP_WriteDimForceData(Ccp_ControlData);	            
		case 3:/*symbol backlight*/
            #if 0
			Ccp_ControlData =0x01830100U;	/*Control the symbol1 PWM*/
			Ccp_ControlData|=CCP_stCmdPtr.u8Data3;	
			Ccp_ControlData =0x01830200U;	/*Control the symbol2 PWM*/
			Ccp_ControlData|=CCP_stCmdPtr.u8Data4;	
			Ccp_ControlData =0x01830400U;	/*Control the symbol3 PWM*/
			Ccp_ControlData|=CCP_stCmdPtr.u8Data5;	
            #endif
			Ccp_ControlData = CCP_nu32SymbolPWMPTSForce;/*Control the Symbol PWM*/
			Ccp_ControlData|= CCP_stCmdPtr.u8Data3;	
			CCP_WriteDimForceData(Ccp_ControlData);
			break;
		default:
			
			break;
	}      
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_25                                              *
 Description   : PTS Blower Control						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_25(void)
{
	uint32 Ccp_ControlData;
    
	Ccp_ControlData = CCP_nu32BctlSpdPTSForce;/*Blower control*/
	Ccp_ControlData |=(uint16)CCP_stCmdPtr.u8Data2;	
    CCP_WriteBctlForceData(Ccp_ControlData);

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_26                                              *
 Description   : PTS Motor Control						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_26(void)
{
	uint32 Ccp_ControlData;

	switch(CCP_stCmdPtr.u8Data2)
	{
		case 1:/*DC Motor*/
			Ccp_ControlData = CCP_nu32DcmMixAirDrPTSForce;/*Mixed Flap*/			
			Ccp_ControlData |= (CCP_stCmdPtr.u8Data3&0x03u);
            CCP_WriteDcmForceData(Ccp_ControlData);
			Ccp_ControlData = CCP_nu32DcmMixAirPsPTSForce;/*Mixed Flap*/			
			Ccp_ControlData |= (CCP_stCmdPtr.u8Data4&0x03u);
            CCP_WriteDcmForceData(Ccp_ControlData);
			Ccp_ControlData = CCP_nu32DcmAirdPTSForce;/*Aird Flap*/			
			Ccp_ControlData |= (CCP_stCmdPtr.u8Data5&0x03u);
            CCP_WriteDcmForceData(Ccp_ControlData); 
 			Ccp_ControlData = CCP_nu32DcmRfaPTSForce;/*Rfa Flap*/			
			Ccp_ControlData |= (CCP_stCmdPtr.u8Data6&0x03u);
            CCP_WriteDcmForceData(Ccp_ControlData);  
 			Ccp_ControlData = CCP_nu32DcmDefPTSForce;/*DEF Flap*/			
			Ccp_ControlData |= (CCP_stCmdPtr.u8Data7&0x03u);
            CCP_WriteDcmForceData(Ccp_ControlData);            
			break;
		case 2:/*step Motor*/
			break;
        case 3:
            if((CCP_stCmdPtr.u8Data3 == 0x00u) && (CCP_stCmdPtr.u8Data4 == 0x00u)\
                && (CCP_stCmdPtr.u8Data5 == 0x00u) && (CCP_stCmdPtr.u8Data6 == 0x00u))
            {
    			Ccp_ControlData = CCP_nu32DcmAllPTSForce;/*All low*/			
    			Ccp_ControlData |= (CCP_stCmdPtr.u8Data3&0x00u);
                CCP_WriteDcmForceData(Ccp_ControlData);
            }
            else if((CCP_stCmdPtr.u8Data3 == 0x05u) && (CCP_stCmdPtr.u8Data4 == 0x05u)\
                && (CCP_stCmdPtr.u8Data5 == 0x05u) && (CCP_stCmdPtr.u8Data6 == 0x05u))
            {
    			Ccp_ControlData = CCP_nu32DcmAllPTSForce;/*Odd high*/			
    			Ccp_ControlData |= (CCP_stCmdPtr.u8Data3&0x05u);
                CCP_WriteDcmForceData(Ccp_ControlData);
            }
            else if((CCP_stCmdPtr.u8Data3 == 0x0Au) && (CCP_stCmdPtr.u8Data4 == 0x0Au)\
                && (CCP_stCmdPtr.u8Data5 == 0x0Au) && (CCP_stCmdPtr.u8Data6 == 0x0Au))
            {
    			Ccp_ControlData = CCP_nu32DcmAllPTSForce;/*Even high*/			
    			Ccp_ControlData |= (CCP_stCmdPtr.u8Data3&0x0Au);
                CCP_WriteDcmForceData(Ccp_ControlData);
            }
            else if((CCP_stCmdPtr.u8Data3 == 0xFFu) && (CCP_stCmdPtr.u8Data4 == 0xFFu)\
                && (CCP_stCmdPtr.u8Data5 == 0xFFu) && (CCP_stCmdPtr.u8Data6 == 0xFFu))
            {
    			Ccp_ControlData = CCP_nu32DcmAllPTSForce;/*All high*/			
    			Ccp_ControlData |= (CCP_stCmdPtr.u8Data3&0xFFu);
                CCP_WriteDcmForceData(Ccp_ControlData);
            }
            break;
		default:			
	    break;
	} 	
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_27                                              *
 Description   : PTS Quiescent Current Measurement						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_27(void)
{
	CCP_WriteSysForceData(CCP_nu32SysQuiescentPTSCtr);/*Quiescent Current For PTS*/ 
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_28                                             *
 Description   : PTS Seat heat Control						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_28(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_29                                             *
 Description   : PTS PWM Control						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_29(void)
{
	uint32 Ccp_ControlData=0u;
    switch(CCP_stCmdPtr.u8Data2)/*Sub Type*/
    {
       case 1:/*Control the ambient temp PWM ouput*/       
       break;
       case 2:/*Control the Compressor PWM ouput*/
       break;
       case 3:/*Control the PTC PWM ouput*/
       break;
       case 4:/*Control the pressure PWM ouput*/
       break;       
       case 5:/*Battary cool bump PWM ouput --> BTM */
			Ccp_ControlData = CCP_nu32BtmBattBumpPTSForce;	
			if (CCP_stCmdPtr.u8Data3 <= 100) /*pwm */
			{
				Ccp_ControlData |= CCP_stCmdPtr.u8Data3;
			}
			else
			{
				Ccp_ControlData |= 50; /*pwm = 50%*/
			}
	        //Btm_u8ForceIoControl_Write(Ccp_ControlData);
		   	break;
       case 6:/*Motor/Obc cool bump PWM ouput --> BTM */
			Ccp_ControlData = CCP_nu32BtmMotorBumpPTSForce;		
			if (CCP_stCmdPtr.u8Data3 <= 100) /*pwm */
			{
				Ccp_ControlData |= CCP_stCmdPtr.u8Data3;
			}
			else
			{
				Ccp_ControlData |= 50; /*pwm = 50%*/
			}
	        //Btm_u8ForceIoControl_Write(Ccp_ControlData);
	        break;
       case 7:/*Ptc bump PWM ouput --> HCT */
			Ccp_ControlData = CCP_nu32HctPtcBumpPTSForce;		
			if (CCP_stCmdPtr.u8Data3 <= 100) /*pwm */
			{
				Ccp_ControlData |= CCP_stCmdPtr.u8Data3;
			}
			else
			{
				Ccp_ControlData |= 50; /*pwm = 50%*/
			}
	        //HCT_u8ForceIoControl_Write(Ccp_ControlData);
			break;
	   case 0xFF:/*all the channel*/
			if(CCP_stCmdPtr.u8Data3==0xFFu)
			{
				//Btm_u8ForceIoControl_Write(0u);	
				//HCT_u8ForceIoControl_Write(0u);
			}
			else if(CCP_stCmdPtr.u8Data3 <= 100) /*pwm */
			{
				Ccp_ControlData = CCP_nu32BtmBattBumpPTSForce;		
				Ccp_ControlData |= CCP_stCmdPtr.u8Data3;
		        //Btm_u8ForceIoControl_Write(Ccp_ControlData);

				Ccp_ControlData = CCP_nu32BtmMotorBumpPTSForce;		
				Ccp_ControlData |= CCP_stCmdPtr.u8Data3;
		        //Btm_u8ForceIoControl_Write(Ccp_ControlData);

				Ccp_ControlData = CCP_nu32HctPtcBumpPTSForce;		
				Ccp_ControlData |= CCP_stCmdPtr.u8Data3;
		        //HCT_u8ForceIoControl_Write(Ccp_ControlData);  

			}
            else
            {
                /*Do noting*/
            }
		break;
       default:
       break;

    }
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_2A                                             *
 Description   : PTS Product information Config						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_2A(void)
{
    switch(CCP_stCmdPtr.u8Data2)/*Sub Type*/
    {
        case 1:/*Write the model Name*/
            CCP_vPtsWriteModelName();            
        break;
        case 2:/*Write the serial Name*/
            CCP_vPtsWriteSerialNum();           
        break;
        case 3:/*Write the Factory Number*/
            CCP_vPtsWriteFactoryNum();
        break;
        case 4:/*Write the Date*/
            CCP_vPtsWriteDate();
        break;
        case 5:/*Write the Production Line*/
            CCP_vPtsWriteProductionLine();
        break;
        case 6:/*Write the serial Number by Day*/
            CCP_vPtsWriteSerialByDay();
        break;
        case 7:/*Write the Internal Hardware Version*/
            CCP_vPtsWriteInternalHWVer();
        break;
        case 8:/*Write the Internal Hardware Version*/
            CCP_vPtsWriteExternalHWVer();
        break;
        default:
        break;      
    }
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_2B                                             *
 Description   : PTS Reserve1						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_2B(void)
{
    uint8 u8EepTestData[16],u8Ret,u8i;

	switch(CCP_stCmdPtr.u8Data2)/*COntrol sub type*/
	{
		case 0x01:           
        for(u8i = 0; u8i<16U;u8i++)
        {
            u8EepTestData[u8i] = CcpPTSEEPSelfTestData;
        }   
        
        u8Ret = CCP_WriteEEPData(CcpGetEEPSelfTestAddr,&u8EepTestData[0],16);          
        break;
		default:			
		break;
	} 
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_2C                                             *
 Description   : PTS Knob test						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_2C(void)
{
    switch(CCP_stCmdPtr.u8Data2)/*Sub Type*/
    {
        case 1:/*Knob start Test*/
            CCP_WriteKnobForceData(CCP_nu32KnobStartTestPTSForce);           
        break;
        case 0xFF:/*Write the serial Name*/
            CCP_WriteKnobForceData(CCP_nu32KnobStopTestPTSForce);  
        break;
        default:
        break;      
    }
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_2D                                             *
 Description   : PTS Clear the DTC						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_2D(void)
{
	uint32 Ccp_ControlData;

	switch(CCP_stCmdPtr.u8Data2)
	{
		case 1:/*MMI information set to default*/
			Ccp_ControlData = CCP_nu32MMIResetPTSCtr;		
			CCP_WriteMmiForceData(Ccp_ControlData);
			break;
		case 2:/*Clear DTC information*/
			Ccp_ControlData = CCP_nu32DTClearPTSCtr;		
			CCP_WriteMmiForceData(Ccp_ControlData);
            CCP_tstResDelayCmd = CCP_nDTCCmdDelayRes;
            CCP_u8ResDelayTime = CcpPTSResDelayForDTC;
            CCP_biServiceActive = False;
            CCP_ClearBit(CCP_nbiServiceActive);            
			break;   		
		default:
			
			break;
	} 	
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_2E                                             *
 Description   : PTS Reserve2						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_2E(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsControl_2F                                             *
 Description   : PTS Reserve3						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsControl_2F(void)
{

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_01                                             *
 Description   : PTS Read Software version						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_01(void)
{
		
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;

    switch(CCP_stDatastrct.u8Data2)
    {
        case 0x01:/*Internal SW version*/
        	CCP_stDatastrct.u8Data3 = (uint8)(CCP_SWVER_INTERNAL>>8u);
            CCP_stDatastrct.u8Data4 = (uint8)CCP_SWVER_INTERNAL;
        	CCP_stDatastrct.u8Data5 = (uint8)(CCP_SWVER_DATE>>16u);
        	CCP_stDatastrct.u8Data6 = (uint8)(CCP_SWVER_DATE>>8u);
        	CCP_stDatastrct.u8Data7 = (uint8)CCP_SWVER_DATE;    
            break;
        default: /*External SW version*/
        	CCP_stDatastrct.u8Data3 = NO_USE;
        	CCP_stDatastrct.u8Data4 = NO_USE;
        	CCP_stDatastrct.u8Data5 = NO_USE;
        	CCP_stDatastrct.u8Data6 = NO_USE;
        	CCP_stDatastrct.u8Data7 = NO_USE;    
            break;            
    }

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_02                                             *
 Description   : PTS Read Hardware version						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_02(void)
{
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
    
    switch(CCP_stDatastrct.u8Data2)
    {
        case 0x01: 
        	CCP_stDatastrct.u8Data3 = NO_USE;
            CCP_stDatastrct.u8Data4 = NO_USE;
        	CCP_stDatastrct.u8Data5 = NO_USE;
        	CCP_stDatastrct.u8Data6 = NO_USE;
        	CCP_stDatastrct.u8Data7 = NO_USE;    
            break;

        default:
        	CCP_stDatastrct.u8Data3 = NO_USE;
        	CCP_stDatastrct.u8Data4 = NO_USE;
        	CCP_stDatastrct.u8Data5 = NO_USE;
        	CCP_stDatastrct.u8Data6 = NO_USE;
        	CCP_stDatastrct.u8Data7 = NO_USE;    
            break;            
    }
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_03                                             *
 Description   : PTS Read diagtal port and Key						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_03(void)
{
    uint8 u8PortValue = 0;
    uint32 u32KeyOutValue = 0u,u32KeyInputValue=0;
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
    
	switch(CCP_stCmdPtr.u8Data2)/*Control Sub Type*/
	{
        case 1:/*Read the Key Value*/
        CCP_WriteKeyForceData(CCP_nu32KeyStartTestPTSForce);
        u32KeyOutValue = 0u;
        u32KeyInputValue = CCP_GetKeyValue1;
        u32KeyOutValue = CCP_u32KeyBitChange(u32KeyInputValue,u32KeyOutValue,2u,0u);
        u32KeyOutValue = CCP_u32KeyBitChange(u32KeyInputValue,u32KeyOutValue,4u,1u);
        u32KeyOutValue = CCP_u32KeyBitChange(u32KeyInputValue,u32KeyOutValue,8u,2u);
        u32KeyOutValue = CCP_u32KeyBitChange(u32KeyInputValue,u32KeyOutValue,13u,3u);
        u32KeyOutValue = CCP_u32KeyBitChange(u32KeyInputValue,u32KeyOutValue,6u,4u);
        u32KeyOutValue = CCP_u32KeyBitChange(u32KeyInputValue,u32KeyOutValue,12u,5u);
        u32KeyOutValue = CCP_u32KeyBitChange(u32KeyInputValue,u32KeyOutValue,9u,6u);
        u32KeyOutValue = CCP_u32KeyBitChange(u32KeyInputValue,u32KeyOutValue,3u,7u);
        u32KeyOutValue = CCP_u32KeyBitChange(u32KeyInputValue,u32KeyOutValue,5u,9u);
        u32KeyOutValue = CCP_u32KeyBitChange(u32KeyInputValue,u32KeyOutValue,11u,10u);
        u32KeyOutValue = CCP_u32KeyBitChange(u32KeyInputValue,u32KeyOutValue,7u,11u);
        u32KeyOutValue = CCP_u32KeyBitChange(u32KeyInputValue,u32KeyOutValue,10u,26u);
        u32KeyOutValue = CCP_u32KeyBitChange(u32KeyInputValue,u32KeyOutValue,1u,27u);
        u32KeyOutValue = CCP_u32KeyBitChange(u32KeyInputValue,u32KeyOutValue,0u,28u);
        CCP_stDatastrct.u8Data3 = (uint8)u32KeyOutValue;
        CCP_stDatastrct.u8Data4 = (uint8)(u32KeyOutValue >> 8);
        CCP_stDatastrct.u8Data5 = (uint8)(u32KeyOutValue >> 16);
        CCP_stDatastrct.u8Data6 = (uint8)(u32KeyOutValue >> 24);
        //CCP_KeyShift(u32KeyInValue,u32KeyOutValue);

        CCP_stDatastrct.u8Data7 = NO_USE; 
        break;
        case 2: /*Read the digtial port*/
        u8PortValue |= CCP_GetDigtalPort0;
        u8PortValue |= (CCP_GetDigtalPort1<<1u);
        u8PortValue |= (CCP_GetDigtalPort2<<2u);
        u8PortValue |= (CCP_GetDigtalPort3<<3u);
        u8PortValue |= (CCP_GetDigtalPort4<<4u);
        u8PortValue |= (CCP_GetDigtalPort5<<5u);
        u8PortValue |= (CCP_GetDigtalPort6<<6u);
        u8PortValue |= (CCP_GetDigtalPort7<<7u);        
        CCP_stDatastrct.u8Data3 = u8PortValue;  
        u8PortValue |= CCP_GetDigtalPort8;
        u8PortValue |= (CCP_GetDigtalPort9<<1u);
        u8PortValue |= (CCP_GetDigtalPort10<<2u);
        u8PortValue |= (CCP_GetDigtalPort11<<3u);
        u8PortValue |= (CCP_GetDigtalPort12<<4u);
        u8PortValue |= (CCP_GetDigtalPort13<<5u);
        u8PortValue |= (CCP_GetDigtalPort14<<6u);
        u8PortValue |= (CCP_GetDigtalPort15<<7u);        
        CCP_stDatastrct.u8Data4 = NO_USE;
        CCP_stDatastrct.u8Data5 = NO_USE;
        CCP_stDatastrct.u8Data6 = NO_USE;
        CCP_stDatastrct.u8Data7 = NO_USE;
        break;   
        default:
        break;
	}
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_04                                             *
 Description   : PTS Read knob	counter					  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_04(void)
{
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_GetKnob1ValueCW;
	CCP_stDatastrct.u8Data3 = CCP_GetKnob1ValueCCW;
	CCP_stDatastrct.u8Data4 = CCP_GetKnob2ValueCW;
	CCP_stDatastrct.u8Data5 = CCP_GetKnob2ValueCCW;
	CCP_stDatastrct.u8Data6 = CCP_GetKnob3ValueCW;
	CCP_stDatastrct.u8Data7 = CCP_GetKnob3ValueCCW;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_05                                             *
 Description   : PTS Read AD						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_05(void)
{
    uint32 Ccp_ControlData;
    /*Turn on the 5V and sensor supply*/  
	Ccp_ControlData = CCP_nu32Pow5vOutPutPTSForce|0x01u;		
	CCP_WritePowForceData(Ccp_ControlData);
	Ccp_ControlData = CCP_nu32PowSenSupplyPTSForce|0x01u;
	CCP_WritePowForceData(Ccp_ControlData);
   
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
	switch(CCP_stCmdPtr.u8Data2)
	{
		case 1:
			CCP_stDatastrct.u8Data3 = CCP_GetBatteryAD;
			CCP_stDatastrct.u8Data4 = CCP_GetMixAirDrFbAD;
			CCP_stDatastrct.u8Data5 = CCP_GetMixAirPsFbAD;
			CCP_stDatastrct.u8Data6 = CCP_GetAirdFbAD;
			CCP_stDatastrct.u8Data7 = CCP_GetRfaFbAD;
			break;
		case 2:
			CCP_stDatastrct.u8Data3 = CCP_GetEvapSensorAd;
			CCP_stDatastrct.u8Data4 = CCP_GetSolarSensorDrAd;
			CCP_stDatastrct.u8Data5 = CCP_GetSolarSensorPsAd;
			CCP_stDatastrct.u8Data6 = CCP_GetOatTempSensorAd;
			CCP_stDatastrct.u8Data7 = CCP_GetIctTempSensorAd;
			break;
		case 3:
			CCP_stDatastrct.u8Data3 = CCP_GetHctTempSensorAd;
			CCP_stDatastrct.u8Data4 = CCP_GetAQSSensorAd;
			CCP_stDatastrct.u8Data5 = CCP_GetPressureSensorAd;
			CCP_stDatastrct.u8Data6 = CCP_GetIG1FbAd;
			CCP_stDatastrct.u8Data7 = CCP_GetIG2FbAd;
			break;
		case 4:
			CCP_stDatastrct.u8Data3 = CCP_GetBlowerFbAd;
			CCP_stDatastrct.u8Data4 = CCP_Get5VFbAd;
			CCP_stDatastrct.u8Data5 = CCP_GetRearDefFbAd;
			CCP_stDatastrct.u8Data6 = CCP_GetSeatHeatDrFbAd;
			CCP_stDatastrct.u8Data7 = CCP_GetSeatHeatPsFbAd;
			break;
        case 5:
			CCP_stDatastrct.u8Data3 = CCP_GetDimmingDetAd;
			CCP_stDatastrct.u8Data4 = CCP_GetFaceBlwSensorDrAd;
			CCP_stDatastrct.u8Data5 = CCP_GetFaceBlwSensorPsAd;
			CCP_stDatastrct.u8Data6 = CCP_GetFootBlwSensorDrAd;
			CCP_stDatastrct.u8Data7 = CCP_GetFootBlwSensorPsAd;            
		case 6:
			CCP_stDatastrct.u8Data3 = CCP_GetNATSFaceTempSensorAd;
			CCP_stDatastrct.u8Data4 = CCP_GetNATSPCBTempSensorAd;
			CCP_stDatastrct.u8Data5 = CCP_GetNATSIRTempSensorAd;
			CCP_stDatastrct.u8Data6 = CCP_GetUserDefine1;
			CCP_stDatastrct.u8Data7 = CCP_GetUserDefine2;
			break;	
		case 7:
			CCP_stDatastrct.u8Data3 = CCP_GetIonDiagnosis;
			CCP_stDatastrct.u8Data4 = CCP_GetUserDefine4;
			CCP_stDatastrct.u8Data5 = CCP_GetUserDefine5;
			CCP_stDatastrct.u8Data6 = CCP_GetUserDefine6;
			CCP_stDatastrct.u8Data7 = CCP_GetUserDefine7;
            break;
       case 8:
			CCP_stDatastrct.u8Data3 = CCP_GetUserDefine8;
			CCP_stDatastrct.u8Data4 = CCP_GetUserDefine9;
			CCP_stDatastrct.u8Data5 = CCP_GetUserDefine10;
			CCP_stDatastrct.u8Data6 = CCP_GetUserDefine11;
			CCP_stDatastrct.u8Data7 = CCP_GetUserDefine12;        
			break;            
		default:
			break;
	}
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_06                                             *
 Description   : PTS Read PWM/Frequence						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_06(void)
{
    uint8 u8ExternalPWM = 0;
    uint16 u16ExternalFreq = 0;
    
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
	switch(CCP_stCmdPtr.u8Data2)/*Sub Type*/
	{
        case 1:
        u8ExternalPWM = CCP_GetOatTmpInputPWM ;
        u16ExternalFreq = CCP_GetOatTmpInputFreq;
        break;
        case 2:
        u8ExternalPWM = CCP_GetAccInputPWM ;
        u16ExternalFreq = CCP_GetAccInputFreq;            
        break;
        case 3:
        u8ExternalPWM = CCP_GetPTCInputPWM ;
        u16ExternalFreq = CCP_GetPTCInputFreq;                
        break;
        case 4:
        u8ExternalPWM = CCP_GetPressureInputPWM ;
        u16ExternalFreq = CCP_GetPressureInputFreq;             
        break;
        case 5:
        u8ExternalPWM = CCP_GetDimInputPWM ;
        u16ExternalFreq = CCP_GetDimInputFreq; 
        break;
        case 6:
        u8ExternalPWM = CCP_GetHCTInputPWM ;
        u16ExternalFreq = CCP_GetHCTInputFreq; 
        break;  
        case 7:        
        u8ExternalPWM = CCP_GetVelInputPWM ;
        u16ExternalFreq = CCP_GetVelInputFreq; 
        break;
        case 8:        
        u8ExternalPWM = CCP_GetAqsInputPWM ;
        u16ExternalFreq = CCP_GetVelInputFreq; 
        break;
        default:           
        break;
       
	}
	CCP_stDatastrct.u8Data3 = u8ExternalPWM;
	CCP_stDatastrct.u8Data4 = (u16ExternalFreq>>8u);
	CCP_stDatastrct.u8Data5 = (uint8)(u16ExternalFreq);
	CCP_stDatastrct.u8Data6 = NO_USE;
	CCP_stDatastrct.u8Data7 = NO_USE;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_07                                             *
 Description   : PTS Read NAT information						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_07(void)
{
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
    
	switch(CCP_stCmdPtr.u8Data2)/*Sub Type*/
	{ 
        case 1:
    	CCP_stDatastrct.u8Data3 = CCP_GetNATSSurfaceTemp;
    	CCP_stDatastrct.u8Data4 = CCP_GetNATSPcbTemp;
    	CCP_stDatastrct.u8Data5 = CCP_GetNATSAbsTemp;
    	CCP_stDatastrct.u8Data6 = NO_USE;
    	CCP_stDatastrct.u8Data7 = NO_USE;
        break;
        default:
        break;
	}
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_08                                             *
 Description   : PTS Read Production Information(PartNumber,ModelName etc)						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_08(void)
{
    

    switch(CCP_stCmdPtr.u8Data2)/*Sub Type*/
    {
        case 1:/*Read the model Name*/
            CCP_vPtsReadModelName();            
        break;
        case 2:/*Read the serial Name*/
            CCP_vPtsReadSerialNum();           
        break;
        case 3:/*Read the Factory Number*/
            CCP_vPtsReadFactoryNum();
        break;
        case 4:/*Read the Date*/
            CCP_vPtsReadDate();
        break;
        case 5:/*Read the Production Line*/
            CCP_vPtsReadProductionLine();
        break;
        case 6:/*Read the serial Number by Day*/
            CCP_vPtsReadSerialByDay();
        break;
        case 7:/*Read the Internal Hardware Version*/
            CCP_vPtsReadInternalHWVer();
        break;
        case 8:/*Read the Internal Hardware Version*/
            CCP_vPtsReadExternalHWVer();
        break;
        default:
        break;      
    }

}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_09                                             *
 Description   : PTS Read UART						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_09(void)
{
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
	CCP_stDatastrct.u8Data3 = NO_USE;
	CCP_stDatastrct.u8Data4 = NO_USE;
	CCP_stDatastrct.u8Data5 = NO_USE;
	CCP_stDatastrct.u8Data6 = NO_USE;
	CCP_stDatastrct.u8Data7 = NO_USE;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_0A                                             *
 Description   : PTS Read Reserve1						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_0A(void)
{
    uint8 u8EepTestData[16],u8Ret,u8CheckResult,u8i;
        
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
	CCP_stDatastrct.u8Data3 = NO_USE;
	CCP_stDatastrct.u8Data4 = NO_USE;
	CCP_stDatastrct.u8Data5 = NO_USE;
	CCP_stDatastrct.u8Data6 = NO_USE;
	CCP_stDatastrct.u8Data7 = NO_USE;
    
    switch(CCP_stDatastrct.u8Data2) /*Control sub type*/
    {        
        case 0x01:
        for(u8i = 0; u8i < 16U; u8i++)
        {
            u8EepTestData[u8i] = 0x00;
        }
        u8Ret = CCP_ReadEEPData(CcpGetEEPSelfTestAddr,&u8EepTestData[0],16U);
        u8CheckResult = True; 
        
        /*Check the EEP */
        for(u8i = 0; u8i < 16U; u8i++)
        {
            if(u8EepTestData[u8i]!=CcpPTSEEPSelfTestData)
            {
                u8CheckResult = False;
                break;
            }
        }
        
        if((u8Ret == 0U)&&(u8CheckResult==True))
        {
            CCP_stDatastrct.u8Data3 = 0x01;/*OK*/
        }
        else
        {
            CCP_stDatastrct.u8Data3 = 0x02;/*Not OK*/
        }

        /*Clear the EEP*/
        for(u8i = 0; u8i < 16U; u8i++)
        {
            u8EepTestData[u8i] = 0xFFU;
        }        
        u8Ret = CCP_WriteEEPData(CcpGetEEPSelfTestAddr,&u8EepTestData[0],16U);
        break;
        default:            
        break;
    }
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_0B                                             *
 Description   : PTS Read Reserve2						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_0B(void)
{
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
	CCP_stDatastrct.u8Data3 = NO_USE;
	CCP_stDatastrct.u8Data4 = NO_USE;
	CCP_stDatastrct.u8Data5 = NO_USE;
	CCP_stDatastrct.u8Data6 = NO_USE;
	CCP_stDatastrct.u8Data7 = NO_USE;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_0C                                             *
 Description   : PTS Read Reserve3						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_0C(void)
{
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
	CCP_stDatastrct.u8Data3 = NO_USE;
	CCP_stDatastrct.u8Data4 = NO_USE;
	CCP_stDatastrct.u8Data5 = NO_USE;
	CCP_stDatastrct.u8Data6 = NO_USE;
	CCP_stDatastrct.u8Data7 = NO_USE;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_0D                                             *
 Description   : PTS Read Reserve4						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_0D(void)
{
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
	CCP_stDatastrct.u8Data3 = NO_USE;
	CCP_stDatastrct.u8Data4 = NO_USE;
	CCP_stDatastrct.u8Data5 = NO_USE;
	CCP_stDatastrct.u8Data6 = NO_USE;
	CCP_stDatastrct.u8Data7 = NO_USE;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_0E                                             *
 Description   : PTS Read Reserve5						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_0E(void)
{
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
	CCP_stDatastrct.u8Data3 = NO_USE;
	CCP_stDatastrct.u8Data4 = NO_USE;
	CCP_stDatastrct.u8Data5 = NO_USE;
	CCP_stDatastrct.u8Data6 = NO_USE;
	CCP_stDatastrct.u8Data7 = NO_USE;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/7/7											  *
 Function      : CCP_vPtsReadInf_0F                                             *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInf_0F(void)
{
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
	CCP_stDatastrct.u8Data3 = NO_USE;
	CCP_stDatastrct.u8Data4 = NO_USE;
	CCP_stDatastrct.u8Data5 = NO_USE;
	CCP_stDatastrct.u8Data6 = NO_USE;
	CCP_stDatastrct.u8Data7 = NO_USE;
}


/*****************************************************************************
 AUTHOR:     : Lin Tao											  *
 DATE: 		 :   2016/7/7											  *
 Function      : CCP_vPtsDelayRes                                             *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsDelayRes(void)
{
    uint8 u8Result;

    if(CCP_u8ResDelayTime!=0U)
    {
        CCP_u8ResDelayTime--;
        CCP_biServiceActive = False;
        CCP_ClearBit(CCP_nbiServiceActive);
    }
    else
    {
        
        switch(CCP_tstResDelayCmd)
        {
            case CCP_nDTCCmdDelayRes:
            u8Result = 1;//CCP_DTCChecking();  
            if(u8Result == False)/*error*/
            {
                CCP_stDatastrct.u8CmdID = 0x7FU;
                CCP_stDatastrct.u8Data1 = 0x30U;/**/
                CCP_stDatastrct.u8Data2 = 0x2DU;/**/
                CCP_stDatastrct.u8Data3 = 0x02U;
                CCP_stDatastrct.u8Data4 = NO_USE;
                CCP_stDatastrct.u8Data5 = NO_USE;
                CCP_stDatastrct.u8Data6 = NO_USE;
                CCP_stDatastrct.u8Data7 = NO_USE;
            }
            else
            {
                CCP_stDatastrct.u8CmdID = 0x70U;
                CCP_stDatastrct.u8Data1 = 0x2DU;
                CCP_stDatastrct.u8Data2 = 0x02U;
                CCP_stDatastrct.u8Data3 = NO_USE;
                CCP_stDatastrct.u8Data4 = NO_USE;
                CCP_stDatastrct.u8Data5 = NO_USE;
                CCP_stDatastrct.u8Data6 = NO_USE;
                CCP_stDatastrct.u8Data7 = NO_USE;
            }
            break;
            default:
            CCP_stDatastrct.u8CmdID = NO_USE;
            CCP_stDatastrct.u8Data1 = NO_USE;
            CCP_stDatastrct.u8Data2 = NO_USE;
            CCP_stDatastrct.u8Data3 = NO_USE;
            CCP_stDatastrct.u8Data4 = NO_USE;
            CCP_stDatastrct.u8Data5 = NO_USE;
            CCP_stDatastrct.u8Data6 = NO_USE;
            CCP_stDatastrct.u8Data7 = NO_USE;    
            break;            
   
        }
        CCP_biServiceActive = True;
        CCP_SetBit(CCP_nbiServiceActive); 
        CCP_tstResDelayCmd = CCP_nResNullDelay;
    }

}




/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadSerialNum                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadModelName(void)
{

#if 0    
    uint8 u8Ret,au8Buffer[16];
    
    u8Ret = CCP_ReadEEPData(CCP_nu8SerialNumAddr,&au8Buffer[0],CCP_nu8SerialLen);

	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2; 
    
    if(u8Ret == 0u)/*successful*/
    {
        /*Data save is ASCII, and PTS is BCD, ASCII-->BCD*/
    	CCP_stDatastrct.u8Data3 = ((au8Buffer[0]-'0')<<4u)|((au8Buffer[1]-'0')&0x0F);
    	CCP_stDatastrct.u8Data4 = ((au8Buffer[2]-'0')<<4u)|((au8Buffer[3]-'0')&0x0F);
    	CCP_stDatastrct.u8Data5 = ((au8Buffer[4]-'0')<<4u)|((au8Buffer[5]-'0')&0x0F);
    	CCP_stDatastrct.u8Data6 = ((au8Buffer[6]-'0')<<4u)|((au8Buffer[7]-'0')&0x0F);
    	CCP_stDatastrct.u8Data7 = ((au8Buffer[8]-'0')<<4u)|((au8Buffer[9]-'0')&0x0F);                
    }
    else
    {
    	CCP_stDatastrct.u8Data3 = 0xFFu;
    	CCP_stDatastrct.u8Data4 = 0xFFu;
    	CCP_stDatastrct.u8Data5 = 0xFFu;
    	CCP_stDatastrct.u8Data6 = 0xFFu;
    	CCP_stDatastrct.u8Data7 = 0xFFu; 
    }
#endif

	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
	CCP_stDatastrct.u8Data3 = CCP_ModelName[0];
	CCP_stDatastrct.u8Data4 = CCP_ModelName[1];
	CCP_stDatastrct.u8Data5 = CCP_ModelName[2];
	CCP_stDatastrct.u8Data6 = CCP_ModelName[3];
	CCP_stDatastrct.u8Data7 = CCP_ModelName[4]; 
}

/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadSerialNum                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadSerialNum(void)
{
#if 0
    uint8 u8Ret,au8Buffer[16],u8i;
	memset(au8Buffer,0,sizeof(au8Buffer));/*Release Warning,161024*/
#ifdef WriteLogDataUseDiretAddr    
    u8Ret = CCP_WriteEEPData(CCP_nu8SerialNumAddr,&au8Buffer[0],CCP_nu8SerialLen);
#else    
    u8Ret = CCP_ReadLogicDataGroup(CCP_LogicDataID,(uint8*)&Diag_stLayout,sizeof(Diag_stLayout)-2U);

    for(u8i =0;u8i<10;u8i++)
    {
        au8Buffer[u8i] = CCP_nu8SerialNumBuffer[u8i];
    }

#endif

	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2; 
    
    if(u8Ret == 0u)/*successful*/
    {
        /*Data save is ASCII, and PTS is BCD, ASCII-->BCD*/
    	CCP_stDatastrct.u8Data3 = ((au8Buffer[0]-'0')<<4u)|((au8Buffer[1]-'0')&0x0F);
    	CCP_stDatastrct.u8Data4 = ((au8Buffer[2]-'0')<<4u)|((au8Buffer[3]-'0')&0x0F);
    	CCP_stDatastrct.u8Data5 = ((au8Buffer[4]-'0')<<4u)|((au8Buffer[5]-'0')&0x0F);
    	CCP_stDatastrct.u8Data6 = ((au8Buffer[6]-'0')<<4u)|((au8Buffer[7]-'0')&0x0F);
    	CCP_stDatastrct.u8Data7 = ((au8Buffer[8]-'0')<<4u)|((au8Buffer[9]-'0')&0x0F);                
    }
    else
    {
    	CCP_stDatastrct.u8Data3 = 0xFFu;
    	CCP_stDatastrct.u8Data4 = 0xFFu;
    	CCP_stDatastrct.u8Data5 = 0xFFu;
    	CCP_stDatastrct.u8Data6 = 0xFFu;
    	CCP_stDatastrct.u8Data7 = 0xFFu; 
    }    
#endif

    CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
    CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
    CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2; 
    CCP_stDatastrct.u8Data3 = 0xFFu;
    CCP_stDatastrct.u8Data4 = 0xFFu;
    CCP_stDatastrct.u8Data5 = 0xFFu;
    CCP_stDatastrct.u8Data6 = 0xFFu;
    CCP_stDatastrct.u8Data7 = 0xFFu;     
}


/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadSerialNum                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadFactoryNum(void)
{
    uint8 u8Ret,au8Buffer[16];
    memset(au8Buffer,0,sizeof(au8Buffer));/*Release Warning,161024*/
    u8Ret = 1;//CCP_ReadEEPData(CCP_nu8FactoryNumAddr,&au8Buffer[0],CCP_nu8FactoryNumLen);
    
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2; 
    
    if(u8Ret == 0u)/*successful*/
    {
    	CCP_stDatastrct.u8Data3 = au8Buffer[0];/*ASCII*/
    	CCP_stDatastrct.u8Data4 = au8Buffer[1];/*ASCII*/
    	CCP_stDatastrct.u8Data5 = au8Buffer[2];/*ASCII*/
    	CCP_stDatastrct.u8Data6 = au8Buffer[3];/*ASCII*/
    	CCP_stDatastrct.u8Data7 = au8Buffer[4];/*ASCII*/                
    }
    else
    {      
    	CCP_stDatastrct.u8Data3 = 0xFFu;
    	CCP_stDatastrct.u8Data4 = 0xFFu;
    	CCP_stDatastrct.u8Data5 = 0xFFu;
    	CCP_stDatastrct.u8Data6 = 0xFFu;
    	CCP_stDatastrct.u8Data7 = 0xFFu; 
    }     
}

/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadSerialNum                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadDate(void)
{
    uint8 u8Ret,au8Buffer[16],u8i;
    
#ifdef WriteLogDataUseDiretAddr        
    u8Ret = CCP_ReadEEPData(CCP_nu8DateAddr,&au8Buffer[0],CCP_nu8DateLen);
#else    
    u8Ret = CCP_ReadLogicDataGroup(CCP_LogicDataID,(uint8*)&Diag_stLayout,sizeof(Diag_stLayout)-2U);

    for(u8i =0;u8i<3;u8i++)
    {
        au8Buffer[u8i] = CCP_nu8DateBuffer[u8i+1];/*The first date is centery*/
    }

#endif
    
    CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
    CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
    CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
    
    if(u8Ret == 0u)/*successful*/
    {
    	CCP_stDatastrct.u8Data3 = au8Buffer[0];/*Year,BCD*/
    	CCP_stDatastrct.u8Data4 = au8Buffer[1];/*Month,BCD*/
    	CCP_stDatastrct.u8Data5 = au8Buffer[2];/*Day,BCD*/
    	CCP_stDatastrct.u8Data6 = NO_USE;/*BCD*/
    	CCP_stDatastrct.u8Data7 = NO_USE;/*BCD*/                
    }
    else
    {        
    	CCP_stDatastrct.u8Data3 = 0xFFu;
    	CCP_stDatastrct.u8Data4 = 0xFFu;
    	CCP_stDatastrct.u8Data5 = 0xFFu;
    	CCP_stDatastrct.u8Data6 = 0xFFu;
    	CCP_stDatastrct.u8Data7 = 0xFFu; 
    }        
}


/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadProductionLine                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadProductionLine(void)
{
    uint8 u8Ret,au8Buffer[16];
    memset(au8Buffer,0,sizeof(au8Buffer));/*Release Warning,161024*/
    u8Ret = 1;//CCP_ReadEEPData(CCP_nu8ProductLineAddr,&au8Buffer[0],CCP_nu8ProductLineLen);

	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
    
    if(u8Ret == 0u)/*successful*/
    {
    	CCP_stDatastrct.u8Data3 = au8Buffer[0];/*ASCII*/
    	CCP_stDatastrct.u8Data4 = au8Buffer[1];/*ASCII*/
    	CCP_stDatastrct.u8Data5 = au8Buffer[2];/*ASCII*/
    	CCP_stDatastrct.u8Data6 = au8Buffer[2];/*ASCII*/
    	CCP_stDatastrct.u8Data7 = au8Buffer[2];/*ASCII*/                
    }
    else
    {       
    	CCP_stDatastrct.u8Data3 = 0xFFu;
    	CCP_stDatastrct.u8Data4 = 0xFFu;
    	CCP_stDatastrct.u8Data5 = 0xFFu;
    	CCP_stDatastrct.u8Data6 = 0xFFu;
    	CCP_stDatastrct.u8Data7 = 0xFFu; 
    }      
}

/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadInternalHWVer                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadSerialByDay(void)
{
    uint8 u8Ret,au8Buffer[16];
    memset(au8Buffer,0,sizeof(au8Buffer));/*Release Warning,161024*/

    u8Ret = CCP_WriteLogicDataGroup(CCP_LogicDataID, (uint8*)&Diag_stLayout,sizeof(Diag_stLayout)-2U); 

    /*CCP_nu8SerialNumBuffer[0] use for other*/
    au8Buffer[0] = CCP_nu8SerialNumBuffer[1];
    au8Buffer[1] = CCP_nu8SerialNumBuffer[2];
    au8Buffer[2] = CCP_nu8SerialNumBuffer[3];
    au8Buffer[3] = CCP_nu8SerialNumBuffer[4];
   
	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
    
    if(u8Ret == 0u)/*successful*/
    {
    	CCP_stDatastrct.u8Data3 = au8Buffer[0];
    	CCP_stDatastrct.u8Data4 = au8Buffer[1];
    	CCP_stDatastrct.u8Data5 = au8Buffer[2];
    	CCP_stDatastrct.u8Data6 = au8Buffer[3];
    	CCP_stDatastrct.u8Data7 = NO_USE;             
    }
    else
    {       
    	CCP_stDatastrct.u8Data3 = 0xFFu;
    	CCP_stDatastrct.u8Data4 = 0xFFu;
    	CCP_stDatastrct.u8Data5 = 0xFFu;
    	CCP_stDatastrct.u8Data6 = 0xFFu;
    	CCP_stDatastrct.u8Data7 = 0xFFu; 
    }     
}


/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadSerialByDay                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadInternalHWVer(void)
{
    uint8 u8Ret,au8Buffer[16];
#if 0
#ifdef WriteLogDataUseDiretAddr     
    u8Ret = CCP_ReadEEPData(CCP_nu8InterHWVerAddr,&au8Buffer[0],CCP_nu8InterHWVerLen);
#else
    u8Ret = CCP_ReadLogicDataGroup(CCP_LogicDataID,&Diag_stLayout,sizeof(Diag_stLayout)-2U);
    au8Buffer[0] = CCP_nu8InterHWVerBuffer[0];

#endif
#endif

	u8Ret = CCP_ReadEEPData(CCP_nu8InterHWVerAddr,&au8Buffer[0],CCP_nu8InterHWVerLen);

	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
    
    if(u8Ret == 0u)/*successful*/
    {
    	CCP_stDatastrct.u8Data3 = au8Buffer[0];/*Hex*/
    	CCP_stDatastrct.u8Data4 = NO_USE;
    	CCP_stDatastrct.u8Data5 = NO_USE;
    	CCP_stDatastrct.u8Data6 = NO_USE;
    	CCP_stDatastrct.u8Data7 = NO_USE;            
    }
    else
    {       
    	CCP_stDatastrct.u8Data3 = 0xFFu;
    	CCP_stDatastrct.u8Data4 = 0xFFu;
    	CCP_stDatastrct.u8Data5 = 0xFFu;
    	CCP_stDatastrct.u8Data6 = 0xFFu;
    	CCP_stDatastrct.u8Data7 = 0xFFu; 
    }     
}

/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadExternalHWVer                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsReadExternalHWVer(void)
{
    uint8 u8Ret,au8Buffer[16];
    memset(au8Buffer,0,sizeof(au8Buffer));/*Release Warning,161024*/
    u8Ret = 1;//CCP_ReadEEPData(CCP_nu8ExterHWVerAddr,&au8Buffer[0],CCP_nu8ExterHWVerLen);

	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
    
    if(u8Ret == 0u)/*successful*/
    {
    	CCP_stDatastrct.u8Data3 = au8Buffer[0];/*ASCII*/
    	CCP_stDatastrct.u8Data4 = au8Buffer[1];
    	CCP_stDatastrct.u8Data5 = au8Buffer[2];
    	CCP_stDatastrct.u8Data6 = au8Buffer[3];
    	CCP_stDatastrct.u8Data7 = au8Buffer[4];            
    }
    else
    {       
    	CCP_stDatastrct.u8Data3 = 0xFFu;
    	CCP_stDatastrct.u8Data4 = 0xFFu;
    	CCP_stDatastrct.u8Data5 = 0xFFu;
    	CCP_stDatastrct.u8Data6 = 0xFFu;
    	CCP_stDatastrct.u8Data7 = 0xFFu; 
    } 

    
}


/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsWriteModelName                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsWriteModelName(void)
{


}

/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadSerialNum                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsWriteSerialNum(void)
{
    #if 0
    uint8 u8Ret,au8Buffer[16],u8i;

    au8Buffer[0]= ((CCP_stCmdPtr.u8Data3>>4u)&0x0Fu)+'0';
    au8Buffer[1]= (CCP_stCmdPtr.u8Data3&0x0Fu)+'0';
    au8Buffer[2]= ((CCP_stCmdPtr.u8Data4>>4u)&0x0Fu)+'0';
    au8Buffer[3]= (CCP_stCmdPtr.u8Data4&0x0Fu)+'0';
    au8Buffer[4]= ((CCP_stCmdPtr.u8Data5>>4u)&0x0Fu)+'0';
    au8Buffer[5]= (CCP_stCmdPtr.u8Data5&0x0Fu)+'0';
    au8Buffer[6]= ((CCP_stCmdPtr.u8Data6>>4u)&0x0Fu)+'0';
    au8Buffer[7]= (CCP_stCmdPtr.u8Data6&0x0Fu)+'0';    
    au8Buffer[8]= ((CCP_stCmdPtr.u8Data7>>4u)&0x0Fu)+'0';
    au8Buffer[9]= (CCP_stCmdPtr.u8Data7&0x0Fu)+'0';   

#ifdef WriteLogDataUseDiretAddr    
    u8Ret = CCP_WriteEEPData(CCP_nu8SerialNumAddr,&au8Buffer[0],CCP_nu8SerialLen);
#else
    memcpy(CCP_nu8SerialNumBuffer,&au8Buffer[0],10);

    for(u8i = 10; u8i < CCP_nu8SerialLen;u8i++)
    {
        CCP_nu8SerialNumBuffer[u8i] = 0x20u;
    }
    /*not include the check sum*/
    u8Ret = CCP_WriteLogicDataGroup(CCP_LogicDataID, (uint8*)&Diag_stLayout,sizeof(Diag_stLayout)-2U); 
#endif

  
    if(u8Ret == 0u)/*successful*/
    {
        /*return the original data from the request*/             
    }
    else
    {
        CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
        CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
        CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;         
        CCP_stDatastrct.u8Data3 = 0xFFu;
        CCP_stDatastrct.u8Data4 = 0xFFu;
        CCP_stDatastrct.u8Data5 = 0xFFu;
        CCP_stDatastrct.u8Data6 = 0xFFu;
        CCP_stDatastrct.u8Data7 = 0xFFu; 
    } 
    #endif

    CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
    CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
    CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;         
    CCP_stDatastrct.u8Data3 = 0xFFu;
    CCP_stDatastrct.u8Data4 = 0xFFu;
    CCP_stDatastrct.u8Data5 = 0xFFu;
    CCP_stDatastrct.u8Data6 = 0xFFu;
    CCP_stDatastrct.u8Data7 = 0xFFu; 
}


/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadSerialNum                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsWriteFactoryNum(void)
{
    uint8 u8Ret,au8Buffer[16];
    
    au8Buffer[0]= CCP_stCmdPtr.u8Data3;
    au8Buffer[1]= CCP_stCmdPtr.u8Data4;
    au8Buffer[2]= CCP_stCmdPtr.u8Data5;
    au8Buffer[3]= CCP_stCmdPtr.u8Data6;
    au8Buffer[4]= CCP_stCmdPtr.u8Data7;
   
    u8Ret = 1;//CCP_WriteEEPData(CCP_nu8FactoryNumAddr,&au8Buffer[0],CCP_nu8FactoryNumLen);
    
    if(u8Ret == 0u)/*successful*/
    {
        /*return the original data from the request*/                 
    }
    else
    {      
        CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
        CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
        CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;         
        CCP_stDatastrct.u8Data3 = 0xFFu;
        CCP_stDatastrct.u8Data4 = 0xFFu;
        CCP_stDatastrct.u8Data5 = 0xFFu;
        CCP_stDatastrct.u8Data6 = 0xFFu;
        CCP_stDatastrct.u8Data7 = 0xFFu; 
    }     
}

/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadSerialNum                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsWriteDate(void)
{
    uint8 u8Ret,au8Buffer[16],u8i;

    /*check accroing to the customer request*/
    au8Buffer[0]= CCP_stCmdPtr.u8Data3;/*Year*/
    au8Buffer[1]= CCP_stCmdPtr.u8Data4;/*month*/
    au8Buffer[2]= CCP_stCmdPtr.u8Data5;/*Day*/   
    
#ifdef WriteLogDataUseDiretAddr      
    u8Ret = CCP_WriteEEPData(CCP_nu8DateAddr,&au8Buffer[0],CCP_nu8DateLen);
#else 

   CCP_nu8DateBuffer[0] = 0x20u;
   CCP_nu8DateBuffer[1] = au8Buffer[0];
   CCP_nu8DateBuffer[2] = au8Buffer[1];
   CCP_nu8DateBuffer[3] = au8Buffer[2];
   /*not include the check sum*/
   u8Ret = CCP_WriteLogicDataGroup(CCP_LogicDataID, (uint8*)&Diag_stLayout,sizeof(Diag_stLayout)-2U); 
#endif
    
    CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
    CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
    CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
    
    if(u8Ret == 0u)/*successful*/
    {
        /*return the original data from the request*/                
    }
    else
    {        
        CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
        CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
        CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;         
        CCP_stDatastrct.u8Data3 = 0xFFu;
        CCP_stDatastrct.u8Data4 = 0xFFu;
        CCP_stDatastrct.u8Data5 = 0xFFu;
        CCP_stDatastrct.u8Data6 = 0xFFu;
        CCP_stDatastrct.u8Data7 = 0xFFu; 
    }        
}

/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadProductionLine                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsWriteProductionLine(void)
{
    uint8 u8Ret,au8Buffer[16];

    au8Buffer[0]= CCP_stCmdPtr.u8Data3;/*Gnerally will be ASCII*/
    au8Buffer[1]= CCP_stCmdPtr.u8Data4;
    au8Buffer[2]= CCP_stCmdPtr.u8Data5;
    au8Buffer[3]= CCP_stCmdPtr.u8Data6;   
    
    u8Ret = 1;//CCP_WriteEEPData(CCP_nu8ProductLineAddr,&au8Buffer[0],CCP_nu8ProductLineLen);
    
    CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
    CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
    CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
    
    if(u8Ret == 0u)/*successful*/
    {
        /*return the original data from the request*/                
    }
    else
    {        
        CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
        CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
        CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;         
        CCP_stDatastrct.u8Data3 = 0xFFu;
        CCP_stDatastrct.u8Data4 = 0xFFu;
        CCP_stDatastrct.u8Data5 = 0xFFu;
        CCP_stDatastrct.u8Data6 = 0xFFu;
        CCP_stDatastrct.u8Data7 = 0xFFu; 
    }        
}
/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadInternalHWVer                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsWriteSerialByDay(void)
{
    uint8 u8Ret,au8Buffer[16];

    au8Buffer[0]= CCP_stCmdPtr.u8Data3;/*Gnerally will be ASCII*/
    au8Buffer[1]= CCP_stCmdPtr.u8Data4;
    au8Buffer[2]= CCP_stCmdPtr.u8Data5;
    au8Buffer[3]= CCP_stCmdPtr.u8Data6;  
   

   /*Write the Serial productline,byte19*/
   CCP_nu8SerialNumBuffer[0] = 0x30U;/*default value*/   
   /*Write the SerialNum by day,byte20~byte23*/
   CCP_nu8SerialNumBuffer[1] = au8Buffer[0];
   CCP_nu8SerialNumBuffer[2] = au8Buffer[1];
   CCP_nu8SerialNumBuffer[3] = au8Buffer[2];
   CCP_nu8SerialNumBuffer[4] = au8Buffer[3];
    
   /*not include the check sum*/  
   u8Ret = CCP_WriteLogicDataGroup(CCP_LogicDataID, (uint8*)&Diag_stLayout,sizeof(Diag_stLayout)-2U); 

	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
    
    if(u8Ret == 0u)/*successful*/
    {
        /*return the original data from the request*/              
    }
    else
    {       
        CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
        CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
        CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;         
        CCP_stDatastrct.u8Data3 = 0xFFu;
        CCP_stDatastrct.u8Data4 = 0xFFu;
        CCP_stDatastrct.u8Data5 = 0xFFu;
        CCP_stDatastrct.u8Data6 = 0xFFu;
        CCP_stDatastrct.u8Data7 = 0xFFu;  
    }     
}


/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadSerialByDay                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsWriteInternalHWVer(void)
{
    uint8 u8Ret,au8Buffer[16],u8i;
    
    au8Buffer[0]= CCP_stCmdPtr.u8Data3; 

#if 0
#ifdef WriteLogDataUseDiretAddr     
    u8Ret = CCP_WriteEEPData(CCP_nu8InterHWVerAddr,&au8Buffer[0],CCP_nu8InterHWVerLen);
#else

   CCP_nu8InterHWVerBuffer[0] = au8Buffer[0];   
   for(u8i = 1u; u8i < CCP_nu8InterHWVerLen ;u8i++)
   {
        CCP_nu8InterHWVerBuffer[u8i] = 0x20u;
   }
   /*not include the check sum*/
   u8Ret = CCP_WriteLogicDataGroup(CCP_LogicDataID, &Diag_stLayout,sizeof(Diag_stLayout)-2U);   
#endif
#endif
   u8Ret = CCP_WriteEEPData(CCP_nu8InterHWVerAddr,&au8Buffer[0],CCP_nu8InterHWVerLen);


	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
    
    if(u8Ret == 0u)/*successful*/
    {
        /*return the original data from the request*/             
    }
    else
    {       
        CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
        CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
        CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;         
        CCP_stDatastrct.u8Data3 = 0xFFu;
        CCP_stDatastrct.u8Data4 = 0xFFu;
        CCP_stDatastrct.u8Data5 = 0xFFu;
        CCP_stDatastrct.u8Data6 = 0xFFu;
        CCP_stDatastrct.u8Data7 = 0xFFu; 
    }     
}

/*****************************************************************************
 AUTHOR:		 : Lin Tao											  *
 DATE: 		    : 2016/8/22											  *
 Function      : CCP_vPtsReadExternalHWVer                                           *
 Description   : PTS Read Reserve6						  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vPtsWriteExternalHWVer(void)
{
    uint8 u8Ret,au8Buffer[16];
    
    au8Buffer[0]= CCP_stCmdPtr.u8Data3;/*Gnerally will be ASCII*/
    au8Buffer[1]= CCP_stCmdPtr.u8Data4;
    au8Buffer[2]= CCP_stCmdPtr.u8Data5;
    au8Buffer[3]= CCP_stCmdPtr.u8Data6;  
    au8Buffer[4]= CCP_stCmdPtr.u8Data7;  
    
    u8Ret = 1;//CCP_WriteEEPData(CCP_nu8ExterHWVerAddr,&au8Buffer[0],CCP_nu8ExterHWVerLen);

	CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
	CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
    
    if(u8Ret == 0u)/*successful*/
    {
        /*return the original data from the request*/            
    }
    else
    {       
        CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40u;
        CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
        CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;         
        CCP_stDatastrct.u8Data3 = 0xFFu;
        CCP_stDatastrct.u8Data4 = 0xFFu;
        CCP_stDatastrct.u8Data5 = 0xFFu;
        CCP_stDatastrct.u8Data6 = 0xFFu;
        CCP_stDatastrct.u8Data7 = 0xFFu; 
    } 

    
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/5/4											  *
 Function      : CCP_vSessionMode                                              *
 Description   : Entry the relative mode                           							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vSessionMode(void)
{
	CCP_tenModeType enSubId;
	if(CCP_biSecurityChk == True)
	{
		/*- Get the subID */
		enSubId = (CCP_tenModeType)(CCP_stCmdPtr.u8Data1);
		if((enSubId >= CCP_nMaxMode) || (enSubId < CCP_nDefaultMode))
		{
			CCP_vNegativeResphone(KWP_ERR_SUB_SERVICE_NOT_SUPPORT);
		}
		else
		{
			if(enSubId == CCP_nDefaultMode)
			{
				/* Clear all mandatory control variable */
				CCP_ClearAllFunction();
				CCP_enWorkingMode = CCP_nDefaultMode;
			}
			else if(enSubId == CCP_nCalibrationMode)
			{
				if(CCP_enWorkingMode != CCP_nCalibrationMode)
				{
					/* Clear all mandatory control variable */
					CCP_ClearAllFunction();
					CCP_enWorkingMode = CCP_nCalibrationMode;
				}

                if(CCP_stCmdPtr.u8Data2 == 0x00)/*Tx Calibration message by period*/
                {
                    CCP_tstCaliTxType = CCP_nTxCaliByPeroid;
                }
                else/*Tx Calibration message by period*/
                {
                    CCP_tstCaliTxType = CCP_nTxCaliByCommand;
                }
			}
			else if(enSubId == CCP_nObdMode)
			{
				if(CCP_enWorkingMode != CCP_nObdMode)
				{
					/* Clear all mandatory control variable */
					CCP_ClearAllFunction();
					CCP_enWorkingMode = CCP_nObdMode;
				}
			}
			else
			{
				
			}
			/* positive respone */
			CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
			CCP_stDatastrct.u8Data1 = enSubId;
			CCP_stDatastrct.u8Data2 = NO_USE;
			CCP_stDatastrct.u8Data3 = NO_USE;
			CCP_stDatastrct.u8Data4 = NO_USE;
			CCP_stDatastrct.u8Data5 = NO_USE;
			CCP_stDatastrct.u8Data6 = NO_USE;
			CCP_stDatastrct.u8Data7 = NO_USE;
		}
	}
	else
	{
		CCP_biServiceActive = False;
		CCP_ClearBit(CCP_nbiServiceActive); /* No resphone */
	}
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_ClearAllFunction                                              *
 Description   : clear all ccp mandatory control variable                            							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_ClearAllFunction(void)
{
    CCP_WriteKnobForceData(0u);    
    CCP_WriteDcmForceData(0u);     
    CCP_WriteLcdForceData(0u);     
    CCP_WriteDimForceData(0u);    
    CCP_WriteBctlForceData(0u);   
    //CCP_WriteSysForceData(Value);     
    CCP_WriteAcccForceData(0u);    
    CCP_WritePowForceData(0u);     
   // CCP_WriteRdcForceData(0u);     
    CCP_WriteMmiForceData(0u);     
    CCP_WriteAirdForceData(0u);    
    CCP_WriteMacForceData(0u);    
    CCP_WriteDtcForceData(0u);    
    CCP_WriteShcForceData(0u);     
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2015/6/30											  *
 Function      : CCP_vExitCcp                                              *
 Description   : Exit CCP                            							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vExitCcp(void)
{
	if(CCP_biSecurityChk == True)
	{
		CCP_biSecurityChk = False;
		CCP_ClearBit(CCP_nbiSecurityChk); 
		CCP_biEepromAccess = False;
		CCP_u8CidSequence = CCP_nTimingCircle;
		CCP_au8Array[CCP_nu8WriteEeprom] = 0x00;
		/* EEPROM access initialization */
		CCP_u8EepAccessType = CCP_nRWNullAction;
		CCP_u8FrameType = CCP_nNullFrame;
		CCP_u16EepDataPtr = 0x0000;
		CCP_u16EepAddress = 0x0000;
		CCP_u16EepDataLength = 0x0000;
		CCP_u8TimeCounter = 0x00;
		CCP_u8AckType = CCP_nNullAction;
		CCP_enWorkingMode = CCP_nDefaultMode;
		/* clear the blobal buffer*/
		CCP_vClrGlobalBuff(CCP_nClrWriteGlbBuff);
		CCP_vClrGlobalBuff(CCP_nClrReadGlbBuff);

		/* Clear all CCP function */
		CCP_ClearAllFunction();
		/* positive respone */
		CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
		CCP_stDatastrct.u8Data1 = NO_USE;
		CCP_stDatastrct.u8Data2 = NO_USE;
		CCP_stDatastrct.u8Data3 = NO_USE;
		CCP_stDatastrct.u8Data4 = NO_USE;
		CCP_stDatastrct.u8Data5 = NO_USE;
		CCP_stDatastrct.u8Data6 = NO_USE;
		CCP_stDatastrct.u8Data7 = NO_USE;	
	}
	else
	{
		CCP_biServiceActive = False;
		CCP_ClearBit(CCP_nbiServiceActive); /* No resphone */
	}
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vReadMemoryByAddress                                              *
 Description   : Read eeprom                           							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vReadMemoryByAddress (void)
{
	uint16 u16EepromSize = 0x0000;
	if((CCP_biSecurityChk == True) && (CCP_enWorkingMode != CCP_nDefaultMode))
	{
		CCP_biEepromAccess = True; /* start access eeprom at the next 10ms */
		CCP_vClrGlobalBuff(CCP_nClrReadGlbBuff); /* clear the blobal buffer */
		CCP_u16EepDataPtr = 0x0000;
		CCP_u8EepAccessType = (CCP_tenEepAccessType)(CCP_stCmdPtr.u8Data1);
		if(CCP_u8EepAccessType == CCP_nReadWholeEep)
		{
			CCP_u8FrameType = CCP_nStartFrame;
			CCP_u16EepAddress = 0x0000;
			CCP_u16EepDataLength = CCP_EEPROM_TABLE_LENGTH;
			u16EepromSize = CCP_u16EepDataLength;
			CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
			CCP_stDatastrct.u8Data1 = CCP_u8EepAccessType; /* Frame type */
			CCP_stDatastrct.u8Data2 = 0x00; /* Eeprom start address high byte */
			CCP_stDatastrct.u8Data3 = 0x00; /* Eeprom start address low byte */
			CCP_stDatastrct.u8Data4 = (uint8)((u16EepromSize & 0xFF00) >> 8); /* Eeprom table length high byte */
			CCP_stDatastrct.u8Data5 = (uint8)(u16EepromSize & 0x00FF); /* Eeprom table length low byte */
			CCP_stDatastrct.u8Data6 = NO_USE;
			CCP_stDatastrct.u8Data7 = NO_USE;
		}
		else if((CCP_u8EepAccessType == CCP_nReadEepByID)||(CCP_u8EepAccessType == CCP_nReadRamByID))
		{
			CCP_u8FrameType = CCP_nStartFrame;
			CCP_u16EepAddress = ((uint16)(CCP_stCmdPtr.u8Data2) << 8) | (CCP_stCmdPtr.u8Data3);
			CCP_u16EepDataLength = (((uint16)(CCP_stCmdPtr.u8Data4)) << 8) | (CCP_stCmdPtr.u8Data5);
			u16EepromSize = CCP_u16EepDataLength;
			if(((CCP_u16EepAddress % 0x02) == 0x00) && ((CCP_u16EepDataLength % 0x02) == 0x00))
			{
				CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
				CCP_stDatastrct.u8Data1 = CCP_u8EepAccessType;
				CCP_stDatastrct.u8Data2 = (uint8)((CCP_u16EepAddress & 0xFF00) >> 8);
				CCP_stDatastrct.u8Data3 = (uint8)(CCP_u16EepAddress & 0x00FF);
				CCP_stDatastrct.u8Data4 = (uint8)((u16EepromSize & 0xFF00) >> 8);
				CCP_stDatastrct.u8Data5 = (uint8)(u16EepromSize & 0x00FF);
				CCP_stDatastrct.u8Data6 = NO_USE;
				CCP_stDatastrct.u8Data7 = NO_USE;
			}
			else
			{
				/* Negative resphone */
				CCP_u8EepAccessType = CCP_nRWNullAction;
				CCP_u8FrameType = CCP_nNullFrame;
				CCP_u16EepAddress = 0x0000;
				CCP_u16EepDataLength = 0x0000;
				CCP_biEepromAccess = False;
				CCP_vNegativeResphone(KWP_ERR_CONDITION_NOT_CRRECT);
			}
		}
		else
		{
			/* Negative resphone */
			CCP_u8EepAccessType = CCP_nRWNullAction;
			CCP_u8FrameType = CCP_nNullFrame;
			CCP_u16EepAddress = 0x0000;
			CCP_u16EepDataLength = 0x0000;
			CCP_biEepromAccess = False;
			CCP_vNegativeResphone(KWP_ERR_SERVICE_NOT_SUPPORTED);
		}
	}
	else
	{
		CCP_biServiceActive = False;
		CCP_ClearBit(CCP_nbiServiceActive); /* No resphone */
	}
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vWriteMemoryByAddress                                              *
 Description   : Write eeprom                           							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vWriteMemoryByAddress (void)
{
	uint16 u16TempAddress,u16TempLength;
	uint32 u32TempAddress;
	if((CCP_biSecurityChk == True) && (CCP_enWorkingMode != CCP_nDefaultMode))
	{
		CCP_biEepromAccess = True; /* start access eeprom at the next 10ms */
		CCP_vClrGlobalBuff(CCP_nClrReadGlbBuff); /* clear the blobal buffer */
		CCP_u16EepDataPtr = 0x0000;
		CCP_u8EepAccessType = (CCP_tenEepAccessType)(CCP_stCmdPtr.u8Data1);
		if((CCP_u8EepAccessType == CCP_nWriteWholeEep) || (CCP_u8EepAccessType == CCP_nWriteEepByID)\
			|| (CCP_u8EepAccessType == CCP_nWriteRamByID))
		{         
			u16TempAddress = (((uint16)CCP_stCmdPtr.u8Data2) << 8) | (CCP_stCmdPtr.u8Data3);
			u16TempLength = ((((uint16)CCP_stCmdPtr.u8Data4)) << 8) | (CCP_stCmdPtr.u8Data5);

            if(CCP_enWorkingMode == CCP_nObdMode)
            {                
                /*Check the addr*/
                if((u16TempAddress>=CcpGetEEPPTSStartAddr)&&((u16TempAddress+u16TempLength)<=(CcpGetEEPPTSStartAddr+CcpGetEEPPTSMaxSize)))/*160812*/
                {
                    #ifdef CcpDataFlashUse
                     u16TempAddress = u16TempAddress-CcpGetEEPPTSStartAddr;
                    #endif

                }
                else
                {
                    /* Negative resphone */
    				CCP_u8EepAccessType = CCP_nRWNullAction;
    				CCP_u8FrameType = CCP_nNullFrame;
    				CCP_u16EepAddress = 0x0000;
    				CCP_u16EepDataLength = 0x0000;
    				CCP_biEepromAccess = False;
    				CCP_vNegativeResphone(KWP_ERR_CONDITION_NOT_CRRECT);
                }
            }
            else if(CCP_enWorkingMode == CCP_nCalibrationMode)
            {
                /*need to update accroding to th data falsh*/
            }
            
         	if(((u16TempAddress % 0x02) == 0x00) && ((u16TempLength % 0x02) == 0x00))
			{
				CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
				CCP_stDatastrct.u8Data1 = CCP_u8EepAccessType;
				CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
				CCP_stDatastrct.u8Data3 = CCP_stCmdPtr.u8Data3;
				CCP_stDatastrct.u8Data4 = CCP_stCmdPtr.u8Data4;
				CCP_stDatastrct.u8Data5 = CCP_stCmdPtr.u8Data5;
				CCP_stDatastrct.u8Data6 = NO_USE;
				CCP_stDatastrct.u8Data7 = NO_USE;
			}
			else
			{
				/* Negative resphone */
				CCP_u8EepAccessType = CCP_nRWNullAction;
				CCP_u8FrameType = CCP_nNullFrame;
				CCP_u16EepAddress = 0x0000;
				CCP_u16EepDataLength = 0x0000;
				CCP_biEepromAccess = False;
				CCP_vNegativeResphone(KWP_ERR_CONDITION_NOT_CRRECT);
			}
		}
		else
		{
			/* Negative resphone */
			CCP_u8EepAccessType = CCP_nRWNullAction;
			CCP_u8FrameType = CCP_nNullFrame;
			CCP_u16EepAddress = 0x0000;
			CCP_u16EepDataLength = 0x0000;
			CCP_biEepromAccess = False;
			CCP_vNegativeResphone(KWP_ERR_SERVICE_NOT_SUPPORTED);
		}
		CCP_EepromInd_b = False;
	}
	else
	{
		CCP_biServiceActive = False;
		CCP_ClearBit(CCP_nbiServiceActive); /* No resphone */
	}
}

/*****************************************************************************
 AUTHOR: Lin Tao										  *
 DATE: 2015/12/24										  *
 Function      : CCP_vReadCalibrationFrame                                             
 Description   : Send the Calibration frame by command                           							  *
 Return Value  : None                                     *
*****************************************************************************/
static void CCP_vReadCalibrationFrame(void)
{
    uint8 u8CidSequence = 0;
	/* whether there is other diagnosics service active? */ 
	if((CCP_enWorkingMode == CCP_nCalibrationMode)&&(CCP_tstCaliTxType==CCP_nTxCaliByCommand))
	{
        u8CidSequence = (uint8)(CCP_stCmdPtr.u8Data1-CCP_CALIBRATION_START_ID);     
		/* There is no other diagnosics service, so to fill the clamite calibration information to Tx buffers */
        if((u8CidSequence < CCP_RCID_NUM)&&(CCP_pfCIDServices[u8CidSequence].boTxCfg==True))
        {
    		(CCP_pfCIDServices[u8CidSequence].vfpCidAction)();
    		CCP_stDatastrct.u8CmdID = CCP_CALIBRATION_START_ID + u8CidSequence;
    		CCP_biServiceActive = True;
    		CCP_SetBit(CCP_nbiServiceActive);	
        }
        else
        {
            CCP_vNegativeResphone(KWP_ERR_SUB_SERVICE_NOT_SUPPORT);
        }
	} 
    else
    {
        CCP_biServiceActive = False;
		CCP_ClearBit(CCP_nbiServiceActive); /* No resphone */
    }

}


/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vReadByCommonID                                            
 Description   : Read information by common ID                           							  *
 Return Value  : None                                                        *
*****************************************************************************/
void CCP_vReadByCommonID (void)
{
	uint8 u8CommonId;
	if((CCP_biSecurityChk == True) && (CCP_enWorkingMode != CCP_nDefaultMode))
	{

		if(CCP_enWorkingMode == CCP_nCalibrationMode)
		{

			CCP_biServiceActive = False;
			CCP_ClearBit(CCP_nbiServiceActive); /* No resphone */
		}
		else if(CCP_enWorkingMode == CCP_nObdMode)
		{
			/*- Get Command Number. -*/
			u8CommonId = CCP_stCmdPtr.u8Data1;
			if((u8CommonId >= CCP_PTS_READINF_START) && (u8CommonId < (CCP_PTS_READINF_START + CCP_PTS_READINF_NUM)))
			{
				u8CommonId -= CCP_PTS_READINF_START;
				(Ccp_pfPtsReadInfTable[u8CommonId]) ();
			}
			else
			{
				CCP_vNegativeResphone(KWP_ERR_SUB_SERVICE_NOT_SUPPORT);
			}
		}
		else
		{
			CCP_biServiceActive = False;
			CCP_ClearBit(CCP_nbiServiceActive); /* No resphone */
		}
	}
	else
	{
		CCP_biServiceActive = False;
		CCP_ClearBit(CCP_nbiServiceActive); /* No resphone */
	}	
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vIOControlByLocalID                                              *
 Description   : ATC control by local ID                           							  *
 Return Value  : None                                                        *
*****************************************************************************/
void CCP_vIOControlByLocalID (void)
{
	uint8 u8IoControlNumber,u8IoControlType;
	if(CCP_biSecurityChk == True)
	{

		if(CCP_enWorkingMode == CCP_nCalibrationMode)
		{

			u8IoControlNumber = CCP_stCmdPtr.u8Data1;
			if((u8IoControlNumber >= CCP_IO_CONTROL_START) && (u8IoControlNumber < (CCP_IO_CONTROL_START + CCP_IO_CONTROL_NUM)))
			{		
				u8IoControlNumber -= CCP_IO_CONTROL_START;
				u8IoControlType = CCP_stCmdPtr.u8Data2;
				if((u8IoControlType == CCP_ADJUST_CONTROL)||(u8IoControlType == CCP_NORMAL_CONTROL))
				{
					(Ccp_pfIoControlTable[u8IoControlNumber]) ();
					CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
					CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
					CCP_stDatastrct.u8Data2 = NO_USE;
					CCP_stDatastrct.u8Data3 = NO_USE;
					CCP_stDatastrct.u8Data4 = NO_USE;
					CCP_stDatastrct.u8Data5 = NO_USE;
					CCP_stDatastrct.u8Data6 = NO_USE;
					CCP_stDatastrct.u8Data7 = NO_USE;
				}
				else
				{
					CCP_vNegativeResphone(KWP_ERR_REQUEST_OUT_OF_RANGE);
				}
			}
			else
			{
				CCP_vNegativeResphone(KWP_ERR_SUB_SERVICE_NOT_SUPPORT);
			}
		}
		else if(CCP_enWorkingMode == CCP_nObdMode)
		{
			u8IoControlNumber = CCP_stCmdPtr.u8Data1;
			if((u8IoControlNumber >= CCP_PTS_CONTROL_START) && (u8IoControlNumber < (CCP_PTS_CONTROL_START + CCP_PTS_CONTROL_NUM)))
			{
				u8IoControlNumber -= CCP_PTS_CONTROL_START;
				u8IoControlType = CCP_stCmdPtr.u8Data2;	
                /*modify by LT, then the function table can change the response value,20160525*/
				CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID|0x40;
				CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8Data1;
				CCP_stDatastrct.u8Data2 = CCP_stCmdPtr.u8Data2;
				CCP_stDatastrct.u8Data3 = CCP_stCmdPtr.u8Data3;
				CCP_stDatastrct.u8Data4 = CCP_stCmdPtr.u8Data4;
				CCP_stDatastrct.u8Data5 = CCP_stCmdPtr.u8Data5;
				CCP_stDatastrct.u8Data6 = CCP_stCmdPtr.u8Data6;
				CCP_stDatastrct.u8Data7 = CCP_stCmdPtr.u8Data7;		                
				(Ccp_pfPtsControlTable[u8IoControlNumber]) ();	
			}
			else
			{
				CCP_vNegativeResphone(KWP_ERR_SUB_SERVICE_NOT_SUPPORT);
			}
		}
		else
		{
			CCP_biServiceActive = False;
			CCP_ClearBit(CCP_nbiServiceActive); /* No resphone */
		}
	}
	else
	{
		CCP_biServiceActive = False;
		CCP_ClearBit(CCP_nbiServiceActive); /* No resphone */
	}
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vSafeAccess                                              *
 Description   : Security access                           							  *
 Return Value  : None                                                        *
*****************************************************************************/
static void CCP_vSafeAccess (void)
{
	uint8 i;
	if(CCP_biSecurityChk == False)
	{
		for(i = 0; i < PASSWORDNUM; i++)
		{
			if(*(&(CCP_stCmdPtr.u8Data1) + i) != u8Passwords[i])
			{
				i = PASSWORDNUM;
			}
		}
		if(i == PASSWORDNUM)
		{
			/* positive respone, the passwords is right */
			CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
			CCP_stDatastrct.u8Data1 = u8Passwords[0];
			CCP_stDatastrct.u8Data2 = u8Passwords[1];
			CCP_stDatastrct.u8Data3 = u8Passwords[2];
			CCP_stDatastrct.u8Data4 = u8Passwords[3];
			CCP_stDatastrct.u8Data5 = u8Passwords[4];
			CCP_stDatastrct.u8Data6 = u8Passwords[5];
			CCP_stDatastrct.u8Data7 = u8Passwords[6];
			CCP_biSecurityChk = True; /* the password is right */
			CCP_SetBit(CCP_nbiSecurityChk);
		}
		else
		{
			CCP_biSecurityChk = False;
			CCP_ClearBit(CCP_nbiSecurityChk);
			/* negative respone, the passwords is error */
			CCP_vNegativeResphone(KWP_ERR_INVALID_KEY);
		}		
	}
	else
	{
        #if 0
		CCP_biServiceActive = False;
		CCP_ClearBit(CCP_nbiServiceActive); /* No resphone */
        #endif
    	/* positive respone, the passwords is right */
		CCP_stDatastrct.u8CmdID = CCP_stCmdPtr.u8CmdID  | 0x40;
		CCP_stDatastrct.u8Data1 = u8Passwords[0];
		CCP_stDatastrct.u8Data2 = u8Passwords[1];
		CCP_stDatastrct.u8Data3 = u8Passwords[2];
		CCP_stDatastrct.u8Data4 = u8Passwords[3];
		CCP_stDatastrct.u8Data5 = u8Passwords[4];
		CCP_stDatastrct.u8Data6 = u8Passwords[5];
		CCP_stDatastrct.u8Data7 = u8Passwords[6];
		CCP_biSecurityChk = True; /* the password is right */
		CCP_SetBit(CCP_nbiSecurityChk);
	}
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/16											  *
 Function      : CCP_vNegativeResphone                                          		  *
 Description   :  Negative resphone                         							  *
 Return Value  : None                                             		  *
*****************************************************************************/
static void CCP_vNegativeResphone(uint8 u8ErrorCode)
{
	CCP_stDatastrct.u8CmdID = KWP_NEGATIVE_SID;
	CCP_stDatastrct.u8Data1 = CCP_stCmdPtr.u8CmdID; /* service ID */
	CCP_stDatastrct.u8Data2 = u8ErrorCode; /* Negative code */
	CCP_stDatastrct.u8Data3 = NO_USE;
	CCP_stDatastrct.u8Data4 = NO_USE;
	CCP_stDatastrct.u8Data5 = NO_USE;
	CCP_stDatastrct.u8Data6 = NO_USE;
	CCP_stDatastrct.u8Data7 = NO_USE;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/13											  *
 Function      : Ccp_vReset                                          		  *
 Description   :                           							  *
 Return Value  : None                                             		  *
*****************************************************************************/
void CCP_vReset( void)
{
	CCP_biServiceActive = False;
	CCP_ClearBit(CCP_nbiServiceActive); /* Disable transmit response message */
	CCP_biSecurityChk = False;
	CCP_ClearBit(CCP_nbiSecurityChk); 
	CCP_biEepromAccess = False;
	CCP_u8CidSequence = CCP_nTimingCircle;
	CCP_au8Array[CCP_nu8WriteEeprom] = 0x00;
	/* EEPROM access initialization */
	CCP_u8EepAccessType = CCP_nRWNullAction;
	CCP_u8FrameType = CCP_nNullFrame;
	CCP_u16EepDataPtr = 0x0000;
	CCP_u16EepAddress = 0x0000;
	CCP_u16EepDataLength = 0x0000;
	CCP_u8TimeCounter = 0x00;
	CCP_u8AckType = CCP_nNullAction;
	CCP_enWorkingMode = CCP_nDefaultMode;
	/* Clear all mandatory control variable */
	CCP_ClearAllFunction();
	/* clear the blobal buffer */
	CCP_vClrGlobalBuff(CCP_nClrWriteGlbBuff);
	CCP_vClrGlobalBuff(CCP_nClrReadGlbBuff);
    CCP_tstResDelayCmd = CCP_nResNullDelay;
    CCP_u8ResDelayTime = 0;
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/13											  *
 Function      : Ccp_vInit                                                	  *
 Description   :                            							  *
 Return Value  : None                                                        *
*****************************************************************************/
void CCP_vInit( void)
{
	CCP_vReset();
}

/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/13											  *
 Function      : Ccp_vDeinit                                                 *
 Description   :                           *
 Return Value  : None                                                        *
*****************************************************************************/
void CCP_vDeinit( void)
{
	CCP_vReset();
}
/*****************************************************************************
 AUTHOR:		 : ***											  *
 DATE: 		 : 2017/7/13											  *
 Function      : 	Ccp_ClearRteData                                                 *
 Description   :                           *
 Return Value  : None                                                        *
*****************************************************************************/
void CCP_ClearRteData( void)
{
	//Rte_Call_CcpWriteKeyForceData_ForceIoControlData(0);
}

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/07/22										  *
 Function      : Ccp_vActive                                                   *
 Description   : 
 Return Value  : None                                                        *
*****************************************************************************/
void CCP_vActive(void)
{
}

static void CCP_vCalibrationTask(void)
{
	if(CCP_biServiceActive == True)
	{
        
		if(CCP_Calibration_Read_conf_b==True)
		{
			CCP_Calibration_Read_conf_b = False;
		}
        
		/*--------		send the message with calibration data		---------*/
		CanTransmit(CanTxCCP_Calibration_Read);
	}
	else
	{
		/* Stop transmiting climate calibration information */
	}
}
/*****************************************************************************
 AUTHOR:		 : Zhong Bin											  *
 DATE: 		 : 2012/8/13											  *
 Function      : Ccp_vMain                                                   *
 Description   : Climate Calibration main function
 NOTE: This part of the main code is normally called from the 10mS container*
 Return Value  : None                                                        *
*****************************************************************************/
void CCP_vMain(void)
{

	uint8 i;
	/*- Point to the begaining of command message and data buffers. -*/
	CCP_tstCmdPtr = (tstCcpdata *)&CCP_stCanRxMessage;
	CCP_stDataPtr = (tstCcpdata *)&CCP_stCanTxMessage;
	CCP_biServiceActive = False;
	CCP_ClearBit(CCP_nbiServiceActive);
	if(CCP_biEepromAccess == False)
	{
		memset (CCP_stDataPtr, 0, 8); /* Clear transmit data buffer */
		CCP_ClearRteData(); /* Clear Key control action */
		 /* Control bytes for the associated sub-functions. */
        if(CCP_tstResDelayCmd == CCP_nResNullDelay)
        {
	   	for (i = 0; i < CCP_MAP_TABLE_SIZE; i++)
	   	{
   			if (CCP_stCmdPtr.u8CmdID == CCP_stMapTable[i].u8SID)
   			{
   				CCP_biServiceActive = True;
				CCP_SetBit(CCP_nbiServiceActive);
   				(*(CCP_stMapTable[i].pfService)) ();
   				i = CCP_MAP_TABLE_SIZE;
				/*- Clean Command Receiver Buffers. -*/
				memset (CCP_tstCmdPtr, 0, 8);
   			}
	   	}
        }
        else
        {
            CCP_vPtsDelayRes();            
        }
		if(CCP_enWorkingMode == CCP_nCalibrationMode)
		{
			/*--------		to load calibration data sequence		--------*/			
			if(CCP_u8CidSequence >= CCP_RCID_NUM)
			{
				CCP_u8CidSequence = 0; /* It is out of range climate calibration sequence */
			}
			else
			{
				/* whether there is other diagnosics service active? */ 
				if((CCP_biServiceActive == False)&&(CCP_tstCaliTxType==CCP_nTxCaliByPeroid))
				{                    
                    for(i=CCP_u8CidSequence;i<CCP_RCID_NUM;i++)
                    {
                        if(CCP_pfCIDServices[CCP_u8CidSequence].boTxCfg!=True)
                        {
                            CCP_u8CidSequence++;
                        }
                        else
                        {
                            break;
                        }
                    }
					/* There is no other diagnosics service, so to fill the clamite calibration information to Tx buffers */
                    if(CCP_u8CidSequence<CCP_RCID_NUM)
                    {
                        (CCP_pfCIDServices[CCP_u8CidSequence].vfpCidAction)();
    					CCP_stDatastrct.u8CmdID = CCP_CALIBRATION_START_ID + CCP_u8CidSequence;
    					CCP_biServiceActive = True;
    					CCP_SetBit(CCP_nbiServiceActive);
                        		CCP_u8CidSequence++;
                    }
                    else
                    {
                        CCP_u8CidSequence = 0;
                    }

				}
			}
		}
	}
	else
	{
		/*- Reset data buffers. -*/
		if(CCP_au8Array[CCP_nu8WriteEeprom] == 0x00)
		{
			memset (CCP_stDataPtr, 0, 8);
		}
		else
		{
			/* know it is in write eeprom */
			if(CCP_u8TimeCounter == 0x0A) /* 100ms */
			{
				/* write eeprom is successful */
				CCP_u8TimeCounter = 0x00;
				CCP_au8Array[CCP_nu8WriteEeprom] = 0x00;
				CCP_biServiceActive = True;
				CCP_SetBit(CCP_nbiServiceActive); /* Enable transmit writing eeprom resphone after write action */
			}
			else
			{
				/* wait 100ms to confirm write eeprom is successful */
				CCP_u8TimeCounter++;
			}
		}
		/* Eeprom down load */
		switch(CCP_u8EepAccessType)
		{
			case CCP_nReadRamByID:	/* read RAM by ID */
			case CCP_nReadEepByID:	/* read EEPROM by ID */
			case CCP_nReadWholeEep:	/* read whole EEPROM */
				CCP_vReadEepromAccess();
				break;
			case CCP_nWriteRamByID:	/* write RAM by ID */
			case CCP_nWriteEepByID:	/* write EEPROM by ID */
			case CCP_nWriteWholeEep:	/* write whole EEPROM */
				CCP_vWriteEepromAccess();
				break;
			default:
				CCP_biEepromAccess = False; /* Exit eeprom access */
				break;
		}
	}
	//Rte_IWrite_Ccp_vMain_CcpPutSessionInfo_CcpSessionInfo(CCP_enWorkingMode);
	 CCP_vCalibrationTask();
	 		//HAL_PinWrite(0,3,0);

}

uint16 CCP_u16GetAdValue(uint8 u8Index)
{
    uint16 u16ReturnValue = 0u;
    switch(u8Index)
    {
        case 0:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_LeftSeatFbValue_Read(&u16ReturnValue);
            break;
        case 1:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_RightSeatFbValue_Read(&u16ReturnValue);
            break;
        case 2:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_BctlDrvBlowerFb_Read(&u16ReturnValue);
            break;
        case 3:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_IncarTemp_Read(&u16ReturnValue);
            break;
        case 4:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_DcmRfaMotorFB_Read(&u16ReturnValue);
            break;
        case 5:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_IncarSun_Read(&u16ReturnValue);
            break;
        case 6:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_EvapSensorValue_Read(&u16ReturnValue);
            break;
        case 7:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_DriverSolarSensor_Read(&u16ReturnValue);
            break;
        case 8:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_PassengerSolarSensor_Read(&u16ReturnValue);
            break;
        case 9:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_OatSensorValue_Read(&u16ReturnValue);
            break;
        case 10:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_DcmAirdMotorFB_Read(&u16ReturnValue);
            break;
        case 11:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_DcmMixMotorDrFB_Read(&u16ReturnValue);
            break;
        case 12:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_Pow5Voltage_Read(&u16ReturnValue);
            break;
        case 13:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_PowBattVoltage_Read(&u16ReturnValue);
            break;
        case 14:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_PcbNtcValue_Read(&u16ReturnValue);
            break;
        case 15:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_DcmMixMotorPsFB_Read(&u16ReturnValue);
            break;
        case 16:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_IonDiag_Read(&u16ReturnValue);
            break;
        case 17:
            Rte_Call_IoHwAd_IoHwAd_ReadAd_Rdc_Read(&u16ReturnValue);
            break;
        default:
            break;
    }

    return u16ReturnValue;
}
/* ===========================================================================*/
