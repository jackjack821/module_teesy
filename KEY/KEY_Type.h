/*******************************************************************************
| Module Name: KEY capture and debouncing Private
| File Name: KEY_Private.h
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
| 2016.8.3         0100      Li jiaye         module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/


#ifndef KEY_Type_H
#define KEY_Type_H


/*****************************************************************************
*Enum define
******************************************************************************/
typedef enum
{
    KEY_enOnece=0,
    KEY_enContinue,
    KEY_enReleaseAction
}KEY_tenKeyType;

typedef enum
{
	KEY_enPressed,
	KEY_enReleased
}KEY_tenKeyAction;


/*****************************************************************************
*Struct define
******************************************************************************/

typedef uint8 (*tfpKeyStatus) (uint16 *Value);

typedef struct
{
    const KEY_tenKeyType enKeyType;
    const uint8   u8DebouncingTime;
    const uint8   u8RepeatActivateTime;
    const uint8   u8RepeatActionTime;
    const uint8   u8PriorityGroup;
    const uint8   u8PriorityLevel;
    const uint16  u16BlockTimeCfg;
    const tfpKeyStatus fpKeyGetStatus;
}KEY_tstProperty;

#define KeyDefine(KeyName, KeyType, DebounceTime, RepeatActivateTime, RepeatActionTime,PriorityGroup,PriorityLevel,BlockTimeCfg,KeyGetStatus)    \
{(KeyType), (DebounceTime), (RepeatActivateTime), (RepeatActionTime),(PriorityGroup),(PriorityLevel),(100*(BlockTimeCfg)),(KeyGetStatus)}


typedef struct 
{
    uint8   u8KeyId;
    KEY_tenKeyAction 	enKeyCurrStatus;
    KEY_tenKeyAction	enKeyActionStatus;
    uint8 		u8KeyPressingTime;
    uint8 		u8KeyLongPressTime;
    uint8       u8KeyReleaseActionPressTime;
    uint16      u16KeyBlockTmr;
    uint8 		u8KeyValib;
}KEY_tstCalcSt;

typedef struct 
{
    uint32   u32KeyActionTable;
    uint32   u32KeyOperationTable;
    uint32   u32KeyBlockTable;
}KEY_tstCalcOut;

typedef struct
{
    uint32   u32KeyActionTable;
    uint32   u32KeyOperationTable;
    uint32   u32KeyBlockTable;
}KEY_tstPriorityCalcIn;

typedef struct
{
    uint32 u32KeyActionTable;
}KEY_tstPriorityCalcOut;

typedef struct
{
    uint32   u32ActionTable;
    uint32   u32OperationTable;
    uint32   u32BlockTable;
}KEY_tstMainOut;

 typedef enum
 {
    KEY_nInvalid=0u,
    KEY_nValid,
    KEY_nDefault,
    KEY_nLastValid
 }KEY_tenValueSts;
 
 
#endif

