/*******************************************************************************
| Module Name: Lcd Control
| File Name: Lcd_Private.h
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
| 2016-02-27  1.00        Yang Shengli      First implementation
| 2016-03-15  2.00        Yang Shengli      update LCD code
********************************************************************************/

#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H
#include "General.h"
/*****************************************************************************
* EXPORT INTERFACE DEFINITLCDS AND DECLARATLCDS
*
* In this sectLCD
* - define all type definitLCDs of your module.
******************************************************************************/
/*****************************************************************************/
/*
*						COM  SEG
#define LCDICON_PointR	0x00  01
*/
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
#define LCDICON_PointL  0x0107
#define LCDICON_PointR	0x0300
#define LCDICON_PointOat	0xFFFF
#define LCDICON_OutTemp		0xFFFF
#define LCDICON_CelL		0x0104
#define LCDICON_CelR    	0x0218
#define LCDICON_Minus    	0xFFFF
#define LCDICON_Bar1	0x0113
#define LCDICON_Bar2     	0x0112
#define LCDICON_Bar3     	0x0111
#define LCDICON_Bar4     	0x0110
#define LCDICON_Bar5     	0x011c
#define LCDICON_Bar6     	0x011d
#define LCDICON_Bar7     	0x011e
#define LCDICON_Fan     	0x011f
#define LCDICON_Man     	0x010a
#define LCDICON_Face     	0x0109
#define LCDICON_Floor     	0x010c
#define LCDICON_Econ     	0xFFFF
#define LCDICON_Auto     	0xFFFF
#define LCDICON_Ac     	0xFFFF
#define LCDICON_Flower	0xFFFF
#define LCDICON_Car     0xFFFF
#define LCDICON_Rec     0xFFFF
#define LCDICON_Fre     0xFFFF
#define LCDICON_FDef    0x0108
#define LCDICON_Aqs     0xFFFF
#define LCDICON_Ion     0x0114
#define LCDICON_Stick   0x0114
#define LCDICON_leaf1   0x010b
#define LCDICON_leaf2   0x0117
#define LCDICON_leaf3   0x021b
#define LCDICON_leaf4   0x0116
#define LCDICON_leaf5   0x0115

#define LCDICON_1A	0x0000
#define LCDICON_1B	0x0008
#define LCDICON_1C	0X0009
#define LCDICON_1D	0X000a
#define LCDICON_1E	0X000f
#define LCDICON_1F	0X000e
#define LCDICON_1G	0x000d
#define LCDICON_1H	0x0003
#define LCDICON_1I	0x0001
#define LCDICON_1J    0x0002
#define LCDICON_1K   0x0005
#define LCDICON_1L	0x0004
#define LCDICON_1M	0x0007
#define LCDICON_1N	0x0006
#define LCDICON_1O	0x00f2
#define LCDICON_1P	0x000b
#define LCDICON_1Q	0x000c  //number position
//#define LCDICON_a18	
//#define LCDICON_a19	
//#define LCDICON_a20	
//#define LCDICON_a21	
//#define LCDICON_a22	
//#define LCDICON_a23	
//#define LCDICON_a24	
//#define LCDICON_a25	

#define LCDICON_2A	0x0010
#define LCDICON_2B	0x0018
#define LCDICON_2C	0X0019
#define LCDICON_2D	0X001a
#define LCDICON_2E	0X001b
#define LCDICON_2F	0X001f
#define LCDICON_2G	0x001d
#define LCDICON_2H	0x0013
#define LCDICON_2I	0x001e
#define LCDICON_2J    0x0012
#define LCDICON_2K   0x0011
#define LCDICON_2L	0x0014
#define LCDICON_2M	0x0017
#define LCDICON_2N	0x0016
#define LCDICON_2O	0x0105
#define LCDICON_2P	0x0106
#define LCDICON_2Q	0x001c

#define LCDICON_3A	0x0204
#define LCDICON_3B	0x020c
#define LCDICON_3C	0x020d
#define LCDICON_3D	0x020e
#define LCDICON_3E	0x0203
#define LCDICON_3F	0x0202
#define LCDICON_3G	0x0201
#define LCDICON_3H	0x0207
#define LCDICON_3I	0x0205
#define LCDICON_3J	0x0206
#define LCDICON_3K	0x0119
#define LCDICON_3L	0x0118
#define LCDICON_3M	0x011b
#define LCDICON_3N	0x011a
#define LCDICON_3O	0x0209
#define LCDICON_3P	0x0210
#define LCDICON_3Q	0x0200

#define LCDICON_4A	0x0214
#define LCDICON_4B	0x021c
#define LCDICON_4C	0x021d
#define LCDICON_4D	0x021e
#define LCDICON_4E	0x021f
#define LCDICON_4F	0x0213
#define LCDICON_4G	0x0211
#define LCDICON_4H	0x0217
#define LCDICON_4I	0x0212
#define LCDICON_4J	0x0216
#define LCDICON_4K	0x0215
#define LCDICON_4L	0x0208
#define LCDICON_4M	0x020b
#define LCDICON_4N	0x020a
#define LCDICON_4O	0x0219
#define LCDICON_4P	0x021a
#define LCDICON_4Q	0x0210

#define LCDICON_5A	0x0100
#define LCDICON_5B   0x0101
#define LCDICON_5C	0x010d
#define LCDICON_5D	0x010e
#define LCDICON_5E   0x0102
#define LCDICON_5F	0xFFFF	
#define LCDICON_5G	0xFFFF
#define LCDICON_5H	0xFFFF
#define LCDICON_5I	0xFFFF
#define LCDICON_5J	0xFFFF
#define LCDICON_5K	0xFFFF
#define LCDICON_5L	0xFFFF
#define LCDICON_5M	0xFFFF
#define LCDICON_5N	0xFFFF
#define LCDICON_5O	0xFFFF
#define LCDICON_5P	0xFFFF
#define LCDICON_5Q	0xFFFF

#define LCDICON_6A	0x0304
#define LCDICON_6B   0x0305
#define LCDICON_6C	0x0301
#define LCDICON_6D	0x0302
#define LCDICON_6E   0x0306
#define LCDICON_6F	0xFFFF
#define LCDICON_6G	0xFFFF
#define LCDICON_6H	0xFFFF
#define LCDICON_6I	0xFFFF
#define LCDICON_6J	0xFFFF
#define LCDICON_6K	0xFFFF
#define LCDICON_6L	0xFFFF
#define LCDICON_6M	0xFFFF
#define LCDICON_6N	0xFFFF
#define LCDICON_6O	0xFFFF
#define LCDICON_6P	0xFFFF
#define LCDICON_6Q	0xFFFF
#else
#define LCDICON_PointL  0x0107
#define LCDICON_PointR	0x0300
#define LCDICON_PointOat	0xFFFF
#define LCDICON_OutTemp		0xFFFF
#define LCDICON_CelL		0x0104
#define LCDICON_CelR    	0x0218
#define LCDICON_Minus    	0xFFFF
#define LCDICON_Bar1	0x0113
#define LCDICON_Bar2     	0x0112
#define LCDICON_Bar3     	0x0111
#define LCDICON_Bar4     	0x0110
#define LCDICON_Bar5     	0x011c
#define LCDICON_Bar6     	0x011d
#define LCDICON_Bar7     	0x011e
#define LCDICON_Fan     	0x011f
#define LCDICON_Man     	0x010a
#define LCDICON_Face     	0x0109
#define LCDICON_Floor     	0x010c
#define LCDICON_Econ     	0xFFFF
#define LCDICON_Auto     	0xFFFF
#define LCDICON_Ac     	0xFFFF
#define LCDICON_Flower	0xFFFF
#define LCDICON_Car     0x0116
#define LCDICON_Rec     0x0115
#define LCDICON_Fre     0x0114
#define LCDICON_FDef    0x0108
#define LCDICON_Aqs     0xFFFF
#define LCDICON_Ion     0x0114
#define LCDICON_Stick   0x0114
#define LCDICON_leaf1   0x010b
#define LCDICON_leaf2   0x0117
#define LCDICON_leaf3   0x021b
#define LCDICON_leaf4   0x0116
#define LCDICON_leaf5   0x0115

#define LCDICON_1A	0x0000
#define LCDICON_1B	0x0008
#define LCDICON_1C	0X0009
#define LCDICON_1D	0X000a
#define LCDICON_1E	0X000f
#define LCDICON_1F	0X000e
#define LCDICON_1G	0x000d
#define LCDICON_1H	0x0003
#define LCDICON_1I	0x0001
#define LCDICON_1J    0x0002
#define LCDICON_1K   0x0005
#define LCDICON_1L	0x0004
#define LCDICON_1M	0x0007
#define LCDICON_1N	0x0006
#define LCDICON_1O	0x00f2
#define LCDICON_1P	0x000b
#define LCDICON_1Q	0x000c  //number position
//#define LCDICON_a18	
//#define LCDICON_a19	
//#define LCDICON_a20	
//#define LCDICON_a21	
//#define LCDICON_a22	
//#define LCDICON_a23	
//#define LCDICON_a24	
//#define LCDICON_a25	

#define LCDICON_2A	0x0010
#define LCDICON_2B	0x0018
#define LCDICON_2C	0X0019
#define LCDICON_2D	0X001a
#define LCDICON_2E	0X001b
#define LCDICON_2F	0X001f
#define LCDICON_2G	0x001d
#define LCDICON_2H	0x0013
#define LCDICON_2I	0x001e
#define LCDICON_2J    0x0012
#define LCDICON_2K   0x0011
#define LCDICON_2L	0x0014
#define LCDICON_2M	0x0017
#define LCDICON_2N	0x0016
#define LCDICON_2O	0x0105
#define LCDICON_2P	0x0106
#define LCDICON_2Q	0x001c

#define LCDICON_3A	0x0204
#define LCDICON_3B	0x020c
#define LCDICON_3C	0x020d
#define LCDICON_3D	0x020e
#define LCDICON_3E	0x0203
#define LCDICON_3F	0x0202
#define LCDICON_3G	0x0201
#define LCDICON_3H	0x0207
#define LCDICON_3I	0x0205
#define LCDICON_3J	0x0206
#define LCDICON_3K	0x0119
#define LCDICON_3L	0x0118
#define LCDICON_3M	0x011b
#define LCDICON_3N	0x011a
#define LCDICON_3O	0x0209
#define LCDICON_3P	0x0210
#define LCDICON_3Q	0x0200

#define LCDICON_4A	0x0214
#define LCDICON_4B	0x021c
#define LCDICON_4C	0x021d
#define LCDICON_4D	0x021e
#define LCDICON_4E	0x021f
#define LCDICON_4F	0x0213
#define LCDICON_4G	0x0211
#define LCDICON_4H	0x0217
#define LCDICON_4I	0x0212
#define LCDICON_4J	0x0216
#define LCDICON_4K	0x0215
#define LCDICON_4L	0x0208
#define LCDICON_4M	0x020b
#define LCDICON_4N	0x020a
#define LCDICON_4O	0x0219
#define LCDICON_4P	0x021a
#define LCDICON_4Q	0x0210

#define LCDICON_5A	0x0100
#define LCDICON_5B   0x0101
#define LCDICON_5C	0x010d
#define LCDICON_5D	0x010e
#define LCDICON_5E   0x0102
#define LCDICON_5F	0xFFFF	
#define LCDICON_5G	0xFFFF
#define LCDICON_5H	0xFFFF
#define LCDICON_5I	0xFFFF
#define LCDICON_5J	0xFFFF
#define LCDICON_5K	0xFFFF
#define LCDICON_5L	0xFFFF
#define LCDICON_5M	0xFFFF
#define LCDICON_5N	0xFFFF
#define LCDICON_5O	0xFFFF
#define LCDICON_5P	0xFFFF
#define LCDICON_5Q	0xFFFF

#define LCDICON_6A	0x0304
#define LCDICON_6B   0x0305
#define LCDICON_6C	0x0301
#define LCDICON_6D	0x0302
#define LCDICON_6E   0x0306
#define LCDICON_6F	0xFFFF
#define LCDICON_6G	0xFFFF
#define LCDICON_6H	0xFFFF
#define LCDICON_6I	0xFFFF
#define LCDICON_6J	0xFFFF
#define LCDICON_6K	0xFFFF
#define LCDICON_6L	0xFFFF
#define LCDICON_6M	0xFFFF
#define LCDICON_6N	0xFFFF
#define LCDICON_6O	0xFFFF
#define LCDICON_6P	0xFFFF
#define LCDICON_6Q	0xFFFF
#endif


#define LCDNumber	(6U)//(4U)
#define LCDSegment    (32U)
/*****************************************************************************/
//#define USE_INTIIC

#define LcdDriveIC		(1U)	/*the flag of using lcd drive IC*/
#define PCA85162		1U
#define PCA8561			2U
#define FUJITSU			3U
/*****************************************************************************
*Macro define
******************************************************************************/
/*****************************************************************************
*PCA85162
******************************************************************************/
#define   LCD_nAddr85162                          (112)    /*LCD driver addresses for 85162*/
#define   LCD_nModeOn                             (200)    /*LCD display On*/
#define   LCD_nModeOff                            (192/*208*/)    /*LCD display Off*/
#define   LCD_nLoadDataPoint                      (128)    /*Data point*/
#define   LCD_nDeviceSelect                       (224)    /*Device Select*/
#define   LCD_nBankSelect                         (249)    /*Bank Select*/
#define   LCD_nBlinkCtrl                          (112/*240*/)    /*Blink Setting*/
/*****************************************************************************
*PCA8561
******************************************************************************/
#define   LCD_nAddr8561                           (112)    /*LCD driver addresses for 8561*/
#define   LCD_nDataPoint                          (0)    /*RAM point*/
#define   LCD_nSwReset                            (0)    /*Software Reset*/
#define   LCD_nDeviceCtrl                         (12)    /*Device control*/
#define   LCD_nDispCtrl1On                        (1)    /*LCD display On*/
#define   LCD_nDispCtrl1Off                       (0)    /*LCD display Off*/
#define   LCD_nDispCtrl2                          (1)    /*LCD display control2*/
#define   LCD_nPowerOnWaitTime                    (100)    /*Power On delay display*/
/************************FUJITSU LCD Control register define***************************/
#if(LcdDriveIC == FUJITSU)

#define VRAM_START_ADDR		0x062a
#define VRAM_END_ADDR		0x0646
#define VRAM_SIZE			VRAM_END_ADDR-VRAM_START_ADDR

#define LCDER_START_ADDR 	0x061c
#define LCDER_END_ADDR		0x0623
#define LCDER_SIZE			LCDER_END_ADDR-LCDER_START_ADDR

#define SETSEG(seg)		*(unsigned char*)(LCDER_START_ADDR+((seg)>>3))|=1<<(seg&7)

static const uint8 LCD_u8UseSeg[]={

	LCD_nSEG0,
	LCD_nSEG1,
	LCD_nSEG2,
	LCD_nSEG3,
	LCD_nSEG4,
	LCD_nSEG5,
	LCD_nSEG6,
	LCD_nSEG7
};
#endif
/************************Define Segment and COM 0f LCD Display RAM ******************************/
#define MCU_COM(a)  a
#define MCU_SEG(a) 	a

/*LCD COM ID  	MCU COM ID*/
#define LCD_nCOM0 	MCU_COM(0)
#define LCD_nCOM1 	MCU_COM(1)
#define LCD_nCOM2 	MCU_COM(2)
#define LCD_nCOM3 	MCU_COM(3)

/*LCD SEG ID  	MCU SEG ID*/
#define LCD_nSEG0	MCU_SEG(0) /*PCB=SEG_0*/
#define LCD_nSEG1	MCU_SEG(1)/*PCB=SEG_1*/
#define LCD_nSEG2	MCU_SEG(2)/*PCB=SEG_2*/
#define LCD_nSEG3	MCU_SEG(3)/*PCB=SEG_3*/
#define LCD_nSEG4	MCU_SEG(4)/*PCB=SEG_4*/
#define LCD_nSEG5	MCU_SEG(7)/*PCB=SEG_7*/
#define LCD_nSEG6	MCU_SEG(11)/*PCB=SEG_11*/
#define LCD_nSEG7	MCU_SEG(12)/*PCB=SEG_12*/

#define LCD_nSwVersion					(0xA0u)

#define LCD_u8SwVersion					LCD_au8Array[LCD_nu8SwVersion]
#define LCD_u16ErrorCode				LCD_au16Array[LCD_nu16ErrorCode]

#define LCD_PowerOnWaitTime	(2)
#define LCD_nInputErrMaskCanAPP          (0x0001U)
#define LCD_nInputErrMaskIgn           (0x0002U)
#define LCD_nInputErrMaskPow		(0x0004)
#define LCD_nInputErrMaskMmi		(0x0008)
#define LCD_nInputErrMaskOat		(0x0010)
#define LCD_nInputErrMaskIct		(0x0020)

#define LCD_nInputBctlLevelMax      (0x07U)
#define LCD_nInputBctlLevelMin      (0x00U)
#define LCD_nInputAirdMax           (0x04U)
#define LCD_nInputAirdMin           (0x00U)

#define LCD_nu8DefaultOutPutValue		(0xFF)
#define LCD_nu16DefaultOutPutValue		(0xFFFF)

#define LCD_u8MaxFTemp					(84)
#define LCD_u8MinFTemp					(60)
#define LCD_u8MaxCTemp					(64)
#define LCD_u8MinCTemp					(34)

#ifdef USE_TEMP500
#define LCD_u16TempDiff					(5000)
#define LCD_u16MinTempExt				(4600)/*-40*10 + 5000*/
#define LCD_u16MaxTempExt				(5600)/*60*10 + 5000*/
#define LCD_u16MinTempIn				(4600)/*-40*10 + 5000*/
#define LCD_u16MaxTempIn				(5995)/*99.5*10 + 5000*/
#else
#define LCD_u16TempDiff					(396)
#define LCD_u16MinTempExt				(0)/*-40*10 + 400*/
#define LCD_u16MaxTempExt				(1050)/*65*10 + 400*/
#define LCD_u16MinTempIn				(0)/*-40*10 + 400*/
#define LCD_u16MaxTempIn				(1395)/*99.5*10 + 400*/
#endif
/*Get value from other modules*/
#ifdef USE_RTE
#define LCD_u8GetHighVoltage		POW_u8GetValue(POW_nu8BattHighVoltage)//Rte_IRead_Lcd_vMain_Lcd_PowBattHighVoltage_u8Flag()
#define LCD_u8GetLowVoltage			POW_u8GetValue(POW_nu8BattLowVoltage)//Rte_IRead_Lcd_vMain_Lcd_PowBattLowVoltage_u8Flag()
#define LCD_u8GetMmiSetTempDr      	MMI_u8GetValue(MMI_nu8SetTempDr)//Rte_IRead_Lcd_vMain_Lcd_MmiSetTempDr_u8Set()
#define LCD_u8GetMmiBctl      MMI_u8GetValue(MMI_nu8BlwControl)//Rte_IRead_Lcd_vMain_Lcd_MmiBlwControl_u8Set()
#define LCD_u8GetMmiAird      MMI_u8GetValue(MMI_nu8AirdControl)//Rte_IRead_Lcd_vMain_Lcd_MmiAirdControl_u8Set()
#define LCD_u16GetMmiDisplayInfo1      MMI_u16GetValue(MMI_nu16LcdDispInfo1)//Rte_IRead_Lcd_vMain_Lcd_MmiLcdDispInfo1_u16BitMap()
#define LCD_u16GetMmiDisplayInfo2      MMI_u16GetValue(MMI_nu16LcdDispInfo2)//Rte_IRead_Lcd_vMain_Lcd_MmiLcdDispInfo2_u16BitMap()
#define LCD_u8GetSys1000MSFlag SYS_u8GetValue(SYS_nFlag1000MS_FG)	
#define LCD_u8GetHctValidFlag HCT_u16GetValue(HCT_nu16Valid)
#define LCD_u8GetIonExpectedMode MMI_u8GetValue(MMI_nu8IonCtrl)
#define LCD_u16GetOatValidFlag OAT_u16GetValue(OAT_nu16Valid)
#define LCD_u8GetIonFilterMaterialNeedReplace MMI_u8GetValue(MMI_nIonNeedReplaceFilter)//Filter Material need to be changed.
#else
#define LCD_u8GetHighVoltage			((uint8)POW_u16GetValue(POW_nu16AppLowVoltage))
#define LCD_u8GetLowVoltage			((uint8)POW_u16GetValue(POW_nu16AppHighVoltage))
#define LCD_u8GetMmiSetTempDr      MMI_u8GetValue(MMI_nu8SetTempDr)
#define LCD_u8GetMmiSetTempPs      MMI_u8GetValue(MMI_nu8SetTempPs)
#define LCD_u8GetMmiBctl      MMI_u8GetValue(MMI_nu8BlwControl)
#define LCD_u8GetMmiAird      MMI_u8GetValue(MMI_nu8AirdControl)
#define LCD_u16GetMmiDisplayInfo1      MMI_u16GetValue(MMI_nu16LcdDispInfo1)
#define LCD_u16GetMmiDisplayInfo2      MMI_u16GetValue(MMI_nu16LcdDispInfo2)
#define LCD_u8GetSys1000MSFlag ((uint8)FRAME_u16GetValue(SYS_nu16Flag1000MS_FG))		
#define LCD_u8GetHctValidFlag HCT_u16GetValue(HCT_nu16Valid)
#define LCD_u8GetIonExpectedMode MMI_u8GetValue(MMI_nu8IonCtrl)//MI_u8GetValue(MMI_nu8IonCtrl)
#define LCD_u16GetOatValidFlag OAT_u16GetValue(OAT_nu16Valid)//OAT_u16GetValue(OAT_nu16Valid);
//#define LCD_u8GetIonFilterMaterialNeedReplace MMI_u8GetValue(MMI_nIonNeedReplaceFilter)/*Interface need to be fixed*///MMI_u8GetValue(MMI_nIonNeedReplaceFilter);//Filter Material need to be changed.
#endif

#define LCD_CcpControlEnable 0
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef LCD_PRIVATE_H */
/*****************************************************************************
* EOF: Lcd_Private.h
******************************************************************************/
