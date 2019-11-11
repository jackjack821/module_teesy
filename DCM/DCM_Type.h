/*******************************************************************************
| Module Name: directed current motor
| File Name: DCM_Type.h
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
| Li Jiaye                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2014.7.17         A0      Li jiaye         module template update. 
| 2014.8.21         A1      Li jiaye         module code updated after coding reviewed.
| 2015.3.29	        A2      Li Jiaye	     add DCM property config
| 2016.2.17         A3      Li Jiaye         module upgraded
| 2016.4.19         A4      Li Jiaye         For base code creating
| 
| 
********************************************************************************/

#ifndef DCM_TYPE_H
#define DCM_TYPE_H

/*****************************************************************************
* EXPORT INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define all type definitions of your module.
******************************************************************************/

/* enum type.
   ---------------------------------------------------------- */
 typedef enum 
{
	DCM_nMixDrMotor=0, /*The Left mix air motor target position*/
	DCM_nAirdMotor, /*The air distribution motor target position*/
	DCM_nRFAMotor, /*The recirculation motor target position*/
#if (SYC_ZONES==2)
	DCM_nMixPsMotor,/*The right mix air motor target position*/
#endif
	DCM_nPort,/*number of all motors	*/
	DCM_nMax
}DCM_tenMotorNumber;

 typedef enum
 {
    DCM_nInvalid=0u,
    DCM_nValid,
    DCM_nDefault,
    DCM_nLastValid
 }DCM_tenValueSts;
 
 typedef enum 
{
	DCM_nu16Max
}DCM_nu16VarNumber;

 typedef enum
 {
 	nSPIReadNoError=0,
 	nSPIReadError
 }DCM_tenSPIRead;

 typedef enum
 {
 	nOpenLoad=0,
 	nOverCurrent,
 	nOverTemp
 }DCM_tenSPIErrType;

 typedef enum DCM_enDirectionState
{
	nDirectionStop = 0,
	nDirectionCW,
	nDirectionCCW,
	nDirectionRestCW,
	nDirectionRestCCW,	
	nDirectionErr
} DCM_tenDirectionState;
 
 typedef enum DCM_enBlockState
{
	nBlockNotDetect = 0,
	nBlockPrevious,
	nBlockConfirm,
	nBlockErr
} DCM_tenBlockState;

 typedef enum 
{
	nOpenLoadNotDetect = 0,
	nOpenLoadPrevious,
	nOpenLoadConfirm,
	nOpenLoadErr
} DCM_tenOpenLoadState;

 typedef enum 
{
	nOverCurrentNotDetect = 0,
	nOverCurrentPrevious,
	nOverCurrentConfirm,
	nOverCurrentErr
} DCM_tenOverCurrentState;

 typedef enum 
{
	nOverTempNotDetect = 0,
	nOverTempPrevious,
	nOverTempConfirm,
	nOverTempErr
} DCM_tenOverTempState;


 typedef enum DCM_enPortState
{
	nNoError = 0,
	nActiveCW,
	nActiveCCW,
	nStopped
} DCM_tenPortState;/*
*  Description: These values are used to describe the state of a motor port,
*                 whether is be the required movement, the last movement, or
*                 the error state.
*               This enum is typedef'd so it can be the return type of
*                 DCM_enDecideOperatingDirection(u8Port).
*/
 typedef enum DCM_enCorrectFBState
{
	nCorrectSuccess = 0,
	nCorrectCW,
	nCorrectCCW,
	nCorrectStop
} DCM_tenCorretFBState;
 
/* struct type.
   ---------------------------------------------------------- */
 typedef struct 
{
   DCM_tenPortState enRequired; /* The required movement.              */
   DCM_tenPortState enPrevious; /* The previous movement.              */
   DCM_tenPortState enError; /* The movement that had an error.     */
   uint8 bi2OkToSleep; /* Zero if port is active.             */
   DCM_tenDirectionState		enDirectionState;
   DCM_tenDirectionState		enDirectionPrevious;
   uint16 u16ActiveTime_Tmr;           /*
*  Description: These timers are used to time how long a port tried to achieve
*                 the target position before timing out in an error condition.
*  Values     : 0 -> DCM_u8MaximumActiveTime.
*/
}DCM_tstState;
typedef struct DCM_stBlockErr
{
	uint8 stBlockPreDringCounter;
	DCM_tenBlockState stBlockStatus;
	uint8 stDetectTimer;
	uint16 stBlockPreTimer;
	uint16 stBlockPTAFBSave;
	uint8 stPTAFBSaveDelay;
        uint32 u32BlockRetryTmr;
}DCM_tstBlockErrStatus;

typedef struct 
{
	uint8 u8OpenLoadPreDringCounter;
	DCM_tenOpenLoadState stOpenLoadStatus;
	uint8 u8OpenLoadPreTimer;
}DCM_tstOpenLoadErrStatus;
typedef struct 
{
	uint8 u8OverCurrentPreDringCounter;
	DCM_tenOverCurrentState stOverCurrentStatus;
	uint8 u8OverCurrentPreTimer;
}DCM_tstOverCurrentErrStatus;
typedef struct 
{
	uint8 u8OverTempPreDringCounter;
	DCM_tenOverTempState stOverTempStatus;
	uint8 u8OverTempPreTimer;
}DCM_tstOverTempErrStatus;

typedef enum
{
	WithFeedback=0,
	WithoutFeedback
}DCM_tenFBSt;

typedef uint8 (*tfpDriverPinSts) (void);
typedef void (*tfpDriverSetPinSts) (DCM_tstState u8Dire);
typedef uint16 (*tfpTargetPosition) (void);
typedef uint8 (*tfpCurrentPosition) (uint16 *Value);

typedef struct
{
    DCM_tenFBSt 	nFeedback;
    const uint16 	u16Maxposition;
    const uint16 	u16Minposition;
    const int16	i16Startvalue;
    const int16	i16Stopvalue;
    const uint16	u16DrivingActionTm;
    /*Error*/
    const uint8 u8MinADChange;
    const uint8	u8BlockPreviousDrvCount;
    const uint8	u8OpenloadPreviousDrvCount;
    const uint8	u8OverCurrentPreviousDrvCount;
    const uint8	u8OverTempPreviousDrvCount;
    const uint16 u16Threshold;
    const uint16 u16MovingSpeed;
    /*Input*/
    const tfpTargetPosition fpTargetPosition;
    const tfpCurrentPosition fpCurrentPosition;

}DCM_tstMotorProperty;

#define DCM_vDefMotor(name,nMotorFBSt,u16Maxposition,u16Minposition,i16Startvalue,i16Stopvalue,u16DrivingActionTm,\
	u8MinADChange,u8BlockPreviousDrvCount,fpTargetPosition,fpCurrentPosition,u16ThresholdValue,u16MovingSpdValue)\
{\
	(nMotorFBSt),\
	(u16Maxposition),\
	(u16Minposition),\
	(i16Startvalue),\
	(i16Stopvalue),\
	(u16DrivingActionTm),\
	(u8MinADChange),\
	(u8BlockPreviousDrvCount),\
	(8u),\
	(8u),\
	(2u),\
	(u16ThresholdValue),\
	(u16MovingSpdValue),\
	(fpTargetPosition),\
	(fpCurrentPosition)\
}
#ifdef PINDRIVER
typedef struct
{
    const tfpDriverSetPinSts fpSetPinSts;
}DCM_tstMotorPinSts;
#define DCM_vDefMotorPIN(name,fpSetPinStsDef)   {fpSetPinStsDef}
#endif
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                
/*****************************************************************************
* EOF: DCM_Type.h
******************************************************************************/
