/**************************************************************************************/
/*------------------------------------------------------------------------------------
              Automatically Generated File,do not edit this file manually!
-------------------------------------------------------------------------------------*/
/** Generated On : 2018-5-30  15:54:05                                      */
/**           By : uidp4501                                                 */
/**        Using : Aqs_Cfg_1.1.xls                                          */
/**         From : D:\HVACProject\Geely\FE-5DB&7DA\ProjectCode\01_APP\AQS   */
/**               (D = )                                                    */
/**************************************************************************************/
 
/******************************************************************************
Module Name : AQS
File Name : AQS_Cfg.h
-------------------------------------------------------------------------------
               C O P Y R I G H T
-------------------------------------------------------------------------------
 Copyright (c) 2015 Huizhou Desay SV Automotive Co., Ltd.   All rights reserved.

 This software is copyright protected and proprietary to Desay SV Automotive Co., Ltd.
 Desay SV Automotive Co., Ltd grants to you only those rights as set out in the
 license conditions. All other rights remain with Desay SV Automotive Co., Ltd.

 REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
 -------------------------------------------------------------------------------
               A U T H O R   I D E N T I T Y
 -------------------------------------------------------------------------------
  Name                                                   Company
  ---------------------          ---------------------------------------
 uidp4501                         Desay SV Automotive Co., Ltd
  ---------------------          ---------------------------------------
******************************************************************************/
 
/* Module Define  */
#ifndef AQS_CFG_H
#define AQS_CFG_H

/* System-headerfiles */
#include "General.h"


/******************************************************************************
* MACROS and STRUCT
*
* In this section declare
* - all macros and structs used in the configuration head file and C file.
******************************************************************************/

#define  AQS_nAqsRecSwitchPointTbl_Len    (4U)
#define  AQS_nAqsFreshSwitchPointTbl_Len    (4U)

/*************************** Define Structures Arrary length ************************/

typedef struct AQS_stDimInfo
{
   uint8    u8VariableConst;
   uint8    u8ChipType;
   uint8    u8AirFilterTime;
   uint8    u8FpDataFill1;
   uint16   au16AqsRecSwitchPoint_X [ AQS_nAqsRecSwitchPointTbl_Len ];
   uint16   au16AqsRecSwitchPoint_Y [ AQS_nAqsRecSwitchPointTbl_Len ];
   uint16   au16AqsFreshSwitchPoint_X [ AQS_nAqsFreshSwitchPointTbl_Len ];
   uint16   au16AqsFreshSwitchPoint_Y [ AQS_nAqsFreshSwitchPointTbl_Len ];
   uint8    u8FpDataFill2;
   uint8    u8FpDataFill3;
} AQS_tstDimInfo;

/*************************** Group Structures ************************/
typedef struct AQS_stGroup1
{
   AQS_tstDimInfo  stDimInfo;
   uint8  u8AddChkSum;
   uint8  u8XorChkSum;
} AQS_tstGroup1;

/********************** LAYOUT STRUCTURE ****************************/

typedef struct 
{
   AQS_tstGroup1  stGroup1;
} AQS_tstRomLayout;

extern  const AQS_tstRomLayout AQS_stRomLayout;

/********************* VARIABLE ACCESS MACROS ***************************/
#define   AQS_u8Group1VariableConst               (AQS_stRomLayout.stGroup1.stDimInfo.u8VariableConst)
#define   AQS_u8Group1ChipType                    (AQS_stRomLayout.stGroup1.stDimInfo.u8ChipType)
#define   AQS_u8Group1AirFilterTime               (AQS_stRomLayout.stGroup1.stDimInfo.u8AirFilterTime)
#define   AQS_u8Group1FpDataFill1                 (AQS_stRomLayout.stGroup1.stDimInfo.u8FpDataFill1)
#define   AQS_au16Group1AqsRecSwitchPoint_X          (AQS_stRomLayout.stGroup1.stDimInfo.au16AqsRecSwitchPoint_X)
#define   AQS_au16Group1AqsRecSwitchPoint_Y          (AQS_stRomLayout.stGroup1.stDimInfo.au16AqsRecSwitchPoint_Y)
#define   AQS_au16Group1AqsFreshSwitchPoint_X          (AQS_stRomLayout.stGroup1.stDimInfo.au16AqsFreshSwitchPoint_X)
#define   AQS_au16Group1AqsFreshSwitchPoint_Y          (AQS_stRomLayout.stGroup1.stDimInfo.au16AqsFreshSwitchPoint_Y)
#define   AQS_u8Group1FpDataFill2                 (AQS_stRomLayout.stGroup1.stDimInfo.u8FpDataFill2)
#define   AQS_u8Group1FpDataFill3                 (AQS_stRomLayout.stGroup1.stDimInfo.u8FpDataFill3)
/******************************** END *************************************/
 /*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
*AQS_Cfg.h
******************************************************************************/
