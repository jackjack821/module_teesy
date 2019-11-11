/*******************************************************************************
| Module Name: Dimmer Control
| File Name: Dim_type.h
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

#ifndef DIM_TYPE_H
#define DIM_TYPE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */
#include "General.h"

/*****************************************************************************
*Data structures define
******************************************************************************/
/*define the Num. of variable that will be used by other modules.*/
typedef enum DIM_enu16VarNumbers
{
	DIM_nu16SwVersion = 0u,
    DIM_nu16ErrorCode,
    DIM_nu16InputPwmDuty,
    DIM_nu16LcdPwmDuty,
    DIM_nu16LumMode,
	DIM_nu16Max
}DIM_tu16enVarNumber;


/*OBD test command*/
enum
{
	DIM_nObdCancelCtrLed = 0u,	    /*Cancel control*/
 	DIM_nObdCtrLed = 0xFFu,   		/*turn on each telltale*/
};

/*Dimmer mode define*/
typedef enum DIM_enModes
{
	DIM_nDayMode = 0u,		/*Day mode PWM*/
	DIM_nNightMode,			/*Night mode PWM*/
}DIM_tenMode;

/*PWM duty ID*/
typedef enum
{
	DIM_nSymbolBacklight = 0u,		/*Control Symbol backlight PWM*/
	DIM_nSymbolBacklightPwmDutyMax,
}DIM_tenBacklightPwmDuty;

typedef enum
{
    DIM_nIndiShcL = 0u,       /*Control indicator*/
    DIM_nIndiShcR,
    DIM_nIndiAc,
    DIM_nIndiFDef,
    DIM_nIndiAuto,
    DIM_nIndiRec,
    DIM_nIndiRDef,
    DIM_nIndiMaxAc,
    DIM_nIndiIon,
    DIM_nIndiDual,
	DIM_nIndicatorPwmDutyMax,
}DIM_tenIndicatorPwmDuty;

typedef enum
{
    DIM_nLcdBacklight = 0u,      /*Control LCD backlight*/
	DIM_nLcdBacklightPwmDutyMax,
}DIM_tenLcdBacklightPwmDuty;
/*define the bit position of LED state from Mmi*/
enum
{
	DIM_nBitMmiAuto = 0u,   /*AUTO Indicator*/
	DIM_nBitMmiAc,          /*AC Indicator*/
	DIM_nBitMmiDual,        /*DUAL Indicator*/
	DIM_nBitMmiFre,         /*FRE Indicator*/
	DIM_nBitMmiRec,         /*REC Indicator*/
	DIM_nBitMmiRdef,        /*RDEF Indicator*/
	DIM_nBitMmiMaxAc,       /*MAXAC Indicator*/
	DIM_nBitMmiFdef,        /*FDEF Indicator*/
	DIM_nBitMmiMixed,       /*MIXED Indicator*/
	DIM_nBitMmiFloor,       /*FLOOR Indicator*/
	DIM_nBitMmiFace,        /*FACE Indicator*/
	DIM_nBitMmiBilevel,     /*BILEVEL Indicator*/
	DIM_nBitMmiRearLock,    /*REARLOCK Indicator*/
	DIM_nBitiIon,
	DIM_nBitReserved1_1,
	DIM_nBitReserved1_2,
}DIM_tenValueIndicateInfo1;

enum
{
	DIM_nBitMmiHSL1 = 0u,   /*Left Heated seat level1 indicator*/
	DIM_nBitMmiHSL2,        /*Left Heated seat level2 indicator*/
	DIM_nBitMmiHSL3,        /*Left Heated seat level3 indicator*/
	DIM_nBitMmiHSR1,        /*Right Heated seat level1 indicator*/
	DIM_nBitMmiHSR2,        /*Right Heated seat level2 indicator*/
	DIM_nBitMmiHSR3,        /*Right Heated seat level3 indicator*/
	DIM_nBitMmiHCL1,        /*Left Cooled seat level1 indicator*/
	DIM_nBitMmiHCL2,        /*Left Cooled seat level2 indicator*/
	DIM_nBitMmiHCL3,        /*Left Cooled seat level3 indicator*/
	DIM_nBitMmiHCR1,        /*Right Cooled seat level1 indicator*/
	DIM_nBitMmiHCR2,        /*Right Cooled seat level2 indicator*/
	DIM_nBitMmiHCR3,        /*Right Cooled seat level3 indicator*/
	DIM_nBitReserved2_0,
	DIM_nBitReserved2_1,
	DIM_nBitReserved2_2,
	DIM_nBitReserved2_3,
}DIM_tenValueIndicateInfo2;

typedef enum
{
    DIM_nInvalid = 0u,
    DIM_nValid,
    DIM_nDefault,
    DIM_nLastValue
}DIM_tenValueSts;

/* input value Error */
typedef enum
{
	DIM_nPowerModule = 0u,
    DIM_nLinAppModule,
	DIM_nModuleMax
}DIM_tenInputMode;

/* struct type.
---------------------------------------------------------- */
typedef struct 
{
    uint16 enPwmDuty; /* The PWM duty.              */
    uint8 enIndex; /* The Index of PWM duty ID.              */
}DIM_tstState;

typedef struct 
{
    uint8 enLightMode;
    uint8 enLuminaceValid;
    uint8 enBacklightStatus;
    uint16 enInputSymbolBacklightPwmDuty[DIM_nSymbolBacklightPwmDutyMax];
    uint16 enInputLcdBacklightPwmDuty[DIM_nLcdBacklightPwmDutyMax];
    uint16 enInputIndicatorPwmDuty[DIM_nIndicatorPwmDutyMax];
    uint16 enIndicatorInfo1; 
    uint16 enIndicatorInfo2;
}DIM_tstInput;

typedef struct         
{
    uint16 u16InputValue;
    uint16 *u16LastInput;
    uint16 u16MinVal;            /*- Min value for this input. -*/
    uint16 u16MaxVal;            /*- Max value for this input. -*/
    uint16 u16Default;           /*- Default value for this input. -*/
    uint8  u8ErrWaitTime;       /*- If the time is reached, nDefault would be used.-*/
    uint8  u8ErrCounter;
}DIM_tstU16InputAttributes;

typedef struct         
{
    uint8 u8InputValue;
    uint8 *u8LastInput;
    uint8 u8MinVal;            /*- Min value for this input. -*/
    uint8 u8MaxVal;            /*- Max value for this input. -*/
    uint8 u8Default;           /*- Default value for this input. -*/
    uint8 u8ErrWaitTime;       /*- If the time is reached, nDefault would be used.-*/
    uint8 u8ErrCounter;
}DIM_tstU8InputAttributes;
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef DIM_TYPE_H */
/*****************************************************************************
* EOF: DIM_Type.h
******************************************************************************/

