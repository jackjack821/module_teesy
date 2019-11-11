
/*******************************************************************************
| Module Name: Calculate the ambient temperature
| File Name: OAT_Type.h
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2016 Huizhou Desay SV Automotive Co., Ltd.    All rights reserved.
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
| Zou Riming                     Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-06-21   0100      Zou Riming          First Create  
| 2016-09-22   0200      Zou Riming          Delet condition 2 of cold start 
| 
********************************************************************************/

#ifndef OAT_TPYE_H
#define OAT_TPYE_H


/*****************************************************************************
* Define the enum to present the variable for extern model call.
******************************************************************************/

/*this is for uint16 type variables*/
typedef enum OAT_enu16VarNumbers
{
    OAT_nu16SwVersion=0,
    OAT_nu16Valid,                          /* indicate OAT value can be use or not*/
    OAT_nu16Display,                      /*Use for LCD display*/
    OAT_nu16EedOatValue ,            /*for ccp,add by zsc,140219 */
    OAT_nu16EedHctValue ,            /*for ccp,add by zsc,140219 */
    OAT_nu16SensorAdRawValue,    /*Sensor Ad Raw Value from HAL module */
    OAT_nu16BusRawValue,            /*Bus Raw Value from CAN module or LIN module */
    OAT_nu16PhyRawValue,            /* OAT physical raw value */
    OAT_nu16Value,                       /*Slow change value*/
    OAT_nu16ValueHys,                 /*Hysteresis for CCS/BCTL/SUN/VEL/ICT/RFA offset*/
    OAT_nu16DiagInfo,                  /*Use for debug infor, indicate which condition to init */
    OAT_nu16ErrorCode,               /* error code */
    OAT_nu16Max
}OAT_tenu16VarNumber;


/*define the bus quality flag*/
typedef enum OAT_enQuaFlag
{
    OAT_nFaulty = 0,
    OAT_nNoDataExists = 1,
    OAT_nNotWithinSpec = 2,
    OAT_nOK = 3,
}OAT_tenQuaFlag;

 typedef enum
 {
    OAT_nInvalid=0u,
    OAT_nValid,
    OAT_nDefault,
    OAT_nLastValue,
    OAT_nShortToGnd,
    OAT_nShortToPow
 }OAT_tenValueSts;

typedef struct
{
    OAT_tenValueSts State;
    uint8 Value;
}OAT_tstU8Group;

typedef struct
{
    OAT_tenValueSts enState;
    uint16 u16Value;
}OAT_tstU16Group;
 
/*Ccp control*/
typedef enum OAT_enCcpControlType
{
    OAT_nSetOatValue,
    OAT_nSetOatSensorFbAd,
    OAT_nCcpForceMax,
}OAT_tenCcpControlType;

typedef struct OAT_stCcpControl
{
    uint16 CcpCommandFlag;
    uint16 CcpCommand;
    uint16 CcpControlData;
}OAT_tstCcpControl;

/* input value Error */
typedef enum
{
    OAT_nBitSensorShortToGnd=0u,
    OAT_nBitSensorShortToPow,
    OAT_nBitIgnModuleError,
    OAT_nBitSysModuleError,
    OAT_nBitPowModuleError,
    OAT_nBitHalModuleError,
    OAT_nBitBusModuleError,  
    OAT_nBitHctModuleError,  
    OAT_nBitVelModuleError, 
} OAT_tenErrorMask;

typedef struct         
{
    uint16 u16InputValue;
    uint16 *u16LastInput;
    uint16 u16MinVal;            /*- Min value for this input. -*/
    uint16 u16MaxVal;            /*- Max value for this input. -*/
    uint16 u16Default;           /*- Default value for this input. -*/
    uint8  u8ErrWaitTime;       /*- If the time is reached, nDefault would be used.-*/
    uint8  u8ErrCounter;
}OAT_tstU16InputAttributes;

typedef struct         
{
    uint8 u8InputValue;
    uint8 *u8LastInput;
    uint8 u8MinVal;            /*- Min value for this input. -*/
    uint8 u8MaxVal;            /*- Max value for this input. -*/
    uint8 u8Default;           /*- Default value for this input. -*/
    uint8  u8ErrWaitTime;       /*- If the time is reached, nDefault would be used.-*/
    uint8  u8ErrCounter;
}OAT_tstU8InputAttributes;



#endif  

/*****************************************************************************
* EOF: OAT_Type.h
******************************************************************************/

