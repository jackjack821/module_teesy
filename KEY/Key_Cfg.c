/*******************************************************************************
| Module Name: KEY capture and debouncing  
| File Name: KEY_CFG.c
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

/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/

#define KEY_CFG

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
#include "KEY_CFG.h"
#include "Key_type.h"
#include "RTE_internal.h"
#include "Key_interface.h"

/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants and macros to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/

KEY_tstProperty KEY_stProperty[KeyNum]=
{
    /*(KeyName, KeyType, DebounceTime, RepeatActivateTime, RepeatActionTime,PriorityGroup,PriorityLevel,KeyGetStatus*/
    KeyDefine(Key1,     KEY_enOnece,3/*20ms*/,20/*200ms*/,20/*200ms*/,0x00,0xFF,10u/*10s*/,KEY_vKey1Import),
    KeyDefine(Key2,     KEY_enOnece,3/*20ms*/,20/*200ms*/,20/*200ms*/,0x01,0xFF,10u/*10s*/,KEY_vKey2Import),
    KeyDefine(Key3, 	KEY_enOnece,3/*20ms*/,20/*200ms*/,20/*200ms*/,0x02,0xFF,10u/*10s*/,KEY_vKey3Import),
    KeyDefine(Key4,     KEY_enOnece,3/*20ms*/,20/*200ms*/,20/*200ms*/,0x03,0xFF,10u/*10s*/,KEY_vKey4Import),
    KeyDefine(Key5,     KEY_enOnece,3/*20ms*/,20/*200ms*/,20/*200ms*/,0x04,0xFF,10u/*10s*/,KEY_vKey5Import),
    KeyDefine(Key6,    KEY_enOnece,3/*20ms*/,20/*200ms*/,20/*200ms*/,0x05,0xFF,10u/*10s*/,KEY_vKey6Import),
    KeyDefine(Key7,    KEY_enOnece,3/*20ms*/,20/*200ms*/,20/*200ms*/,0x06,0xFF,10u/*10s*/,KEY_vKey7Import),
    KeyDefine(Key8,    KEY_enOnece,3/*20ms*/,20/*500ms*/,20/*200ms*/,0x07,0xFF,10u/*10s*/,KEY_vKey8Import),
    KeyDefine(Key9,    KEY_enOnece,3/*20ms*/,20/*200ms*/,20/*200ms*/,0x08,0xFF,10u/*10s*/,KEY_vKey9Import),
    KeyDefine(ForceKey1,     KEY_enContinue,3/*20ms*/,100/*200ms*/,100/*200ms*/,0x09,0xFF,10u/*10s*/,KEY_vKeyForce1Import),
    KeyDefine(ForceKey2,     KEY_enContinue,3/*20ms*/,100/*200ms*/,100/*200ms*/,0x10,0xFF,10u/*10s*/,KEY_vKeyForce2Import),
    KeyDefine(ForceKey3, 	KEY_enContinue,3/*20ms*/,100/*200ms*/,100/*200ms*/,0x20,0xFF,10u/*10s*/,KEY_vKeyForce3Import),
    KeyDefine(ForceKey4,     KEY_enContinue,3/*20ms*/,100/*200ms*/,100/*200ms*/,0x30,0xFF,10u/*10s*/,KEY_vKeyForce4Import),
    KeyDefine(ForceKey5,     KEY_enContinue,3/*20ms*/,100/*200ms*/,100/*200ms*/,0x40,0xFF,10u/*10s*/,KEY_vKeyForce5Import),
    KeyDefine(ForceKey6,    KEY_enContinue,3/*20ms*/,100/*200ms*/,100/*200ms*/,0x50,0xFF,10u/*10s*/,KEY_vKeyForce6Import),
    KeyDefine(ForceKey7,    KEY_enContinue,3/*20ms*/,100/*200ms*/,100/*200ms*/,0x60,0xFF,10u/*10s*/,KEY_vKeyForce7Import),
    KeyDefine(ForceKey8,  	KEY_enContinue,3/*20ms*/,100/*500ms*/,100/*200ms*/,0x70,0xFF,10u/*10s*/,KEY_vKeyForce8Import),
    KeyDefine(ForceKey9,    KEY_enContinue,3/*20ms*/,100/*200ms*/,100/*200ms*/,0x80,0xFF,10u/*10s*/,KEY_vKeyForce9Import),
};






