/*******************************************************************************
| Module Name: Lcd Control
| File Name: Lcd_Type.h
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

#ifndef LCD_TYPE_H
#define LCD_TYPE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */
#include "General.h"
#include "Lcd_Private.h"
/*****************************************************************************
*Data structures define
******************************************************************************/
/*define the Num. of variable that will be used by other modules.*/

/*****************************************************************************
*Struct define
******************************************************************************/
/*define Segment byte struct*/
#if(LcdDriveIC == PCA8561)

typedef struct
{
	uint8 u8DriverAddr;
	uint8 u8Cmd1;
	uint8 u8Cmd2;
	uint8 u8Cmd3;
	uint8 u8Cmd4;
	uint8 u8Cmd5;
	uint8 au8Seg[4][3];  /*4 COM, 3 Segment Byte*/
}LCD_tstMapBuffer;

#else
#define LCD_nMaxDatabyte (4u)
typedef struct
{
#if(LcdDriveIC != FUJITSU)
	uint8 u8DriverAddr;
	uint8 u8Cmd1;
	uint8 u8Cmd2;
	uint8 u8Cmd3;
	uint8 u8Cmd4;
	uint8 u8Cmd5;
    uint8 au8Seg[4][4];  /*4 COM, 4 Segment Byte*/
#else
	uint8 au8Seg[LCD_nMaxDatabyte];
#endif
}LCD_tstMapBuffer;

#endif

typedef enum LCD_enu8VarNumbers
{
	LCD_nu8SwVersion,
	LCD_nu8SetTempDr,
	LCD_nu8SetTempPs,//add by liyang
	LCD_nu8BctlDis,
	LCD_nu8AirdDis,
	LCD_nu8DisplayInfo_00,
	LCD_nu8DisplayInfo_01,
	LCD_nu8DisplayInfo_02,
	LCD_nu8DisplayInfo_03,
	LCD_nu8DisplayInfo_04,
	LCD_nu8DisplayInfo_05,
	LCD_nu8DisplayInfo_06,
	LCD_nu8DisplayInfo_07,
	LCD_nu8DisplayInfo_08,
	LCD_nu8DisplayInfo_09,
	LCD_nu8DisplayInfo_10,
	LCD_nu8DisplayInfo_11,
	LCD_nu8DisplayInfo_12,
	LCD_nu8DisplayInfo_13,
	LCD_nu8DisplayInfo_14,
	LCD_nu8DisplayInfo_15,
	LCD_nu8DisplayInfo_16,
	LCD_nu8DisplayInfo_17,
	LCD_nu8Max
}LCD_tu8enVarNumber;



/*For PTS test select*/
enum
{
	LCD_nObdTurnOffAllSegment = 0,
	LCD_nObdTurnOnAllSegment,
	LCD_nObdTurnOnOddSegment,
	LCD_nObdTurnOnEvenSegment,
	LCD_nObdTurnOnEvenCom,
	LCD_nObdTurnOnOddCom,
	LCD_nObdTurnOnCom0,
	LCD_nObdTurnOnCom1,
	LCD_nObdTurnOnCom2,
	LCD_nObdTurnOnCom3,
};

enum
{
    LCD_nMMIFace = 0,
    LCD_nMMIBilevel,
	LCD_nMMIFloor,
	LCD_nMMIMix,
	LCD_nMMIDefrost,
	LCD_nReserve5_0,
	LCD_nReserve5_1,
	LCD_nReserve5_2,
};
/*define the bit position of LCD state from Mmi*/
enum
{
	LCD_nBitMmiAuto = 0,
	LCD_nBitMmiAc,
	LCD_nBitMmiDual,
	LCD_nBitMmiEcon,
	LCD_nBitMmiFre,
	LCD_nBitMmiRec,
	LCD_nBitMmiRDef,
	LCD_nBitMmiAqs,
	LCD_nBitMmiMaxac,
	LCD_nBitMmiFDef,
	LCD_nBitMmiOff,
	LCD_nBitMmiRearLock,
	LCD_nBitMmiManual,
	LCD_nReserve1_0,
	LCD_nReserve1_1,
	LCD_nReserve1_2
};

enum
{
    LCD_nBitMmiTempLFlag = 0,
    LCD_nBitMmiBlwFlag,
	LCD_nBitMmiAirdLFlag,
	LCD_nBitMmiTempDispMode,/*0:Cesl,1:F*/
	LCD_nBitMmiLcdFlag,
	LCD_nBitMmiRecFlag,
	LCD_nReserve2_1,
	LCD_nReserve2_2,
	LCD_nReserve2_3,
	LCD_nReserve2_4,
	LCD_nReserve2_5,
	LCD_nReserve2_6,
	LCD_nReserve2_7,
	LCD_nReserve2_8,
	LCD_nReserve2_9,
	LCD_nReserve2_10
};

enum
{
	LCD_nBitMmiLedAuto = 0,
	LCD_nBitMmiLedAc,
	LCD_nBitMmiLedDual,
	LCD_nBitMmiLedFre,
	LCD_nBitMmiLedRec,
	LCD_nBitMmiLedRDef,
	LCD_nBitMmiLedMaxac,
	LCD_nBitMmiRecLedFDef,
	LCD_nBitMmiRecLedMixed,
	LCD_nBitMmiRecLedFloor,
	LCD_nBitMmiRecLedFace,
	LCD_nBitMmiRecLedBilevel,
	LCD_nReserve3_0,
	LCD_nReserve3_1,
	LCD_nReserve3_2,
	LCD_nReserve3_3
};

/*define the Num of number Array*/
enum {
	LCD_enNumID_0 = 0,
	LCD_enNumID_1,
	LCD_enNumID_2,
	LCD_enNumID_3,
	LCD_enNumID_4,
	LCD_enNumID_5,
	LCD_enNumID_6,
	LCD_enNumID_7,
	LCD_enNumID_8,
	LCD_enNumID_9,
	LCD_enNumID_H,
	LCD_enNumID_I,
	LCD_enNumID_L,
	LCD_enNumID_O,
	LCD_enNumID_Minus,
	LCD_enNumID_NULL,
	LCD_enNumID_NUM,
};

enum
{/* ION Control */
   LCD_nIonStandby=0,
   //LCD_nIonCleanMode,
   LCD_nIonIonMode,
};

enum
{/* PM25 Status */
   LCD_nPm25Standy=0,
   LCD_nAirGood,
   LCD_nAirBad
};
typedef enum LCD_enu8HiStatus
{/*Zones Stat us */
   LCD_DrvierHi=0,
   LCD_PassengerHi=2,
   LCD_ZonesHi
}LCD_enu8HiStatus;

typedef enum LCD_enu8LowStatus
{/*Zones Status */
    LCD_DrvierLo=0,
   LCD_PassengerLo=2,
   LCD_ZonesLo
}LCD_nu8LowStatus;

typedef enum LCD_enu16VarNumbers
{
	LCD_nu16TouchKey1=0,
	LCD_nu16TouchKey2=0,                         /* indicate OAT value can be use or not*/
	LCD_nu16TouchKey3=0,                    /*Use for LCD display*/
	LCD_nu16TouchKey4=0,            /*for ccp,add by zsc,140219 */
	LCD_nu16TouchKey5=0,           /*for ccp,add by zsc,140219 */
	LCD_nu16TouchKey6=0,    /*Sensor Ad Raw Value from HAL module */
	LCD_nu16TouchKey7=0,           /*Bus Raw Value from CAN module or LIN module */
	LCD_nu16TouchKey8=0,           /* OAT physical raw value */
	LCD_nu16TouchKey9=0,                   /*Slow change value*/
	LCD_nu16TouchKey10=0,               /*Hysteresis for CCS/BCTL/SUN/VEL/ICT/RFA offset*/
	LCD_nu16TouchKey11=0,                 /*Use for debug infor, indicate which condition to init */
	LCD_nu16TouchKey12=0,              /* error code */
	LCD_nu16Max
}LCD_tenu16VarNumber;

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef LCD_TYPE_H */
/*****************************************************************************
* EOF: LCD_Type.h
******************************************************************************/

