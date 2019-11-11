/**************************************************************************************/
/*------------------------------------------------------------------------------------
              Automatically Generated File,do not edit this file manually!
-------------------------------------------------------------------------------------*/
/** Generated On : 2016/4/7  19:24:20                                       */
/**           By : uidp3721                                                 */
/**        Using : ISTP_Cfg_Template_Release_A10.xls                        */
/**         From : D:\HVACProject\Geely\KC-2\ATC\01_Application\02_Sources\01_CC\01_APP\ISTP*/
/**               (D = )                                                    */
/**************************************************************************************/
 
/******************************************************************************
Module Name : ISTP
File Name : ISTP_Cfg.h
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
 uidp3721                         Desay SV Automotive Co., Ltd
  ---------------------          ---------------------------------------
******************************************************************************/
 
/* Module Define  */
#ifndef ISTP_CFG_H
#define ISTP_CFG_H

/* System-headerfiles */
#include "General.h"


/******************************************************************************
* MACROS and STRUCT
*
* In this section declare
* - all macros and structs used in the configuration head file and C file.
******************************************************************************/

#define  ISTP_nOatBoDiffHTbl_Len    (7U)
#define  ISTP_nOatBoDiffCTbl_Len    (7U)
#define  ISTP_nOatBoDiffCTbl_Len    (7U)
#define  ISTP_nOatIRTimerCTbl_Len    (8U)
#define  ISTP_nOatIRTimerHTbl_Len    (8U)
#define  ISTP_nBctlIRTimerFactorTbl_Len    (7U)
#define  ISTP_nBlowerOatLimitTbl_Len    (8U)
#define  ISTP_nSunTempTbl_Len    (4U)
#define  ISTP_nSunTempTbl_Len    (4U)
#define  ISTP_nSunTempOatTbl_Len    (4U)
#define  ISTP_nSunBctlTbl_Len    (4U)
#define  ISTP_nMMISaveData_Len    (2U)
#define  ISTP_nSHCOutPutVoltage_Tbl    (2U)
#define  ISTP_nSHCOutPutCurrent_Tbl    (2U)

/*************************** Define Structures Arrary length ************************/

typedef struct ISTP_stIstpInfo
{
   uint8    u8VariableConst;
   uint8    u8ChipType;
   uint8    u8HeaderFillByte1;
   uint8    u8HeaderFillByte2;
} ISTP_tstIstpInfo;

typedef struct ISTP_stIstpData
{
   uint16   au16OatBoDiffHX_Tbl [ ISTP_nOatBoDiffHTbl_Len ];
   uint16   au16OatBoDiffHY_Tbl [ ISTP_nOatBoDiffHTbl_Len ];
   uint16   au16OatBoDiffCX_Tbl [ ISTP_nOatBoDiffCTbl_Len ];
   uint16   au16OatBoDiffCY_Tbl [ ISTP_nOatBoDiffCTbl_Len ];
   uint16   au16OatIRTimerCX_Tbl [ ISTP_nOatIRTimerCTbl_Len ];
   uint16   au16OatIRTimerCY_Tbl [ ISTP_nOatIRTimerCTbl_Len ];
   uint16   au16OatIRTimerHX_Tbl [ ISTP_nOatIRTimerHTbl_Len ];
   uint16   au16OatIRTimerHY_Tbl [ ISTP_nOatIRTimerHTbl_Len ];
   uint8    au8BctlIRTimerFactorX_Tbl [ ISTP_nBctlIRTimerFactorTbl_Len ];
   uint8    au8BctlIRTimerFactorY_Tbl [ ISTP_nBctlIRTimerFactorTbl_Len ];
   uint16   au16BlowerOatLimitX_Tbl [ ISTP_nBlowerOatLimitTbl_Len ];
   uint16   au16BlowerOatLimitY_Tbl [ ISTP_nBlowerOatLimitTbl_Len ];
   uint16   au16SunTempOffsX_Tbl [ ISTP_nSunTempTbl_Len ];
   uint16   au16SunTempOffsY1_Tbl [ ISTP_nSunTempTbl_Len ];
   uint16   au16SunTempOffsY2_Tbl [ ISTP_nSunTempTbl_Len ];
   uint16   au16SunTempOffsY3_Tbl [ ISTP_nSunTempTbl_Len ];
   uint16   au16SunTempOffsY4_Tbl [ ISTP_nSunTempTbl_Len ];
   uint16   au16SunTempOatX_Tbl [ ISTP_nSunTempOatTbl_Len ];
   uint16   au16SunBctlOffsX_Tbl [ ISTP_nSunBctlTbl_Len ];
   uint16   au16SunBctlOffsY1_Tbl [ ISTP_nSunBctlTbl_Len ];
   uint16   au16SunBctlOffsY2_Tbl [ ISTP_nSunBctlTbl_Len ];
   uint16   au16SunBctlOffsY3_Tbl [ ISTP_nSunBctlTbl_Len ];
   uint16   au16SunBctlOffsY4_Tbl [ ISTP_nSunBctlTbl_Len ];
} ISTP_tstIstpData;

typedef struct ISTP_stModeVarSelect
{
   uint8    u8VariableConst;
   uint8    u8VCFillByte1;
   uint8    u8VCFillByte2;
   uint8    u8VCFillByte3;
} ISTP_tstModeVarSelect;

typedef struct ISTP_stModelVariant
{
   uint8    u8ModelType;
   uint8    u8VWType;
} ISTP_tstModelVariant;

typedef struct ISTP_stMMIVarSelect
{
   uint8    u8VariableConst;
   uint8    u8VCFillByte1;
   uint8    u8VCFillByte2;
   uint8    u8VCFillByte3;
} ISTP_tstMMIVarSelect;

typedef struct ISTP_stMMISaveData
{
   uint8    au8MMISaveData [ ISTP_nMMISaveData_Len ];
} ISTP_tstMMISaveData;

typedef struct ISTP_stSHCVarSelect
{
   uint8    u8VariableConst;
   uint8    u8VCFillByte1;
   uint8    u8VCFillByte2;
   uint8    u8VCFillByte3;
} ISTP_tstSHCVarSelect;

typedef struct ISTP_stSHCCalibration
{
   uint8    au8SHCOutPutVoltage [ ISTP_nSHCOutPutVoltage_Tbl ];
   uint8    au8SHCOutPutCurrent [ ISTP_nSHCOutPutCurrent_Tbl ];
   uint8    u8SHCKParameter;
   uint8    u8FillByte_SHCCalibration;
} ISTP_tstSHCCalibration;

/*************************** Group Structures ************************/
typedef struct ISTP_stGroupISTP
{
   ISTP_tstIstpInfo  stIstpInfo;
   ISTP_tstIstpData  stIstpData;
   uint8  u8AddChkSum;
   uint8  u8XorChkSum;
} ISTP_tstGroupISTP;

typedef struct ISTP_stGroupISTP1
{
   ISTP_tstModeVarSelect  stModeVarSelect;
   ISTP_tstModelVariant  stModelVariant;
   uint8  u8AddChkSum;
   uint8  u8XorChkSum;
} ISTP_tstGroupISTP1;

typedef struct ISTP_stGroupISTP2
{
   ISTP_tstMMIVarSelect  stMMIVarSelect;
   ISTP_tstMMISaveData  stMMISaveData;
   uint8  u8AddChkSum;
   uint8  u8XorChkSum;
} ISTP_tstGroupISTP2;

typedef struct ISTP_stGroupISTP3
{
   ISTP_tstSHCVarSelect  stSHCVarSelect;
   ISTP_tstSHCCalibration  stSHCCalibration;
   uint8  u8AddChkSum;
   uint8  u8XorChkSum;
} ISTP_tstGroupISTP3;

/********************** LAYOUT STRUCTURE ****************************/
typedef struct 
{
   ISTP_tstGroupISTP  stGroupISTP;
   ISTP_tstGroupISTP1  stGroupISTP1;
} ISTP_tstLayout;


typedef struct 
{
   ISTP_tstGroupISTP2  stGroupISTP2;
   ISTP_tstGroupISTP3  stGroupISTP3;
} ISTP_tstRomLayout;

extern ISTP_tstLayout ISTP_stLayout;

extern const ISTP_tstLayout ISTP_stDefaultLayout;

extern  const ISTP_tstRomLayout ISTP_stRomLayout;

/********************* VARIABLE ACCESS MACROS ***************************/
#define   ISTP_u8GroupISTPVariableConst           (ISTP_stLayout.stGroupISTP.stIstpInfo.u8VariableConst)
#define   ISTP_u8GroupISTPChipType                (ISTP_stLayout.stGroupISTP.stIstpInfo.u8ChipType)
#define   ISTP_u8GroupISTPHeaderFillByte1          (ISTP_stLayout.stGroupISTP.stIstpInfo.u8HeaderFillByte1)
#define   ISTP_u8GroupISTPHeaderFillByte2          (ISTP_stLayout.stGroupISTP.stIstpInfo.u8HeaderFillByte2)
#define   ISTP_au16GroupISTPOatBoDiffHX_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16OatBoDiffHX_Tbl)
#define   ISTP_au16GroupISTPOatBoDiffHY_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16OatBoDiffHY_Tbl)
#define   ISTP_au16GroupISTPOatBoDiffCX_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16OatBoDiffCX_Tbl)
#define   ISTP_au16GroupISTPOatBoDiffCY_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16OatBoDiffCY_Tbl)
#define   ISTP_au16GroupISTPOatIRTimerCX_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16OatIRTimerCX_Tbl)
#define   ISTP_au16GroupISTPOatIRTimerCY_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16OatIRTimerCY_Tbl)
#define   ISTP_au16GroupISTPOatIRTimerHX_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16OatIRTimerHX_Tbl)
#define   ISTP_au16GroupISTPOatIRTimerHY_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16OatIRTimerHY_Tbl)
#define   ISTP_au8GroupISTPBctlIRTimerFactorX_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au8BctlIRTimerFactorX_Tbl)
#define   ISTP_au8GroupISTPBctlIRTimerFactorY_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au8BctlIRTimerFactorY_Tbl)
#define   ISTP_au16GroupISTPBlowerOatLimitX_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16BlowerOatLimitX_Tbl)
#define   ISTP_au16GroupISTPBlowerOatLimitY_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16BlowerOatLimitY_Tbl)
#define   ISTP_au16GroupISTPSunTempOffsX_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16SunTempOffsX_Tbl)
#define   ISTP_au16GroupISTPSunTempOffsY1_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16SunTempOffsY1_Tbl)
#define   ISTP_au16GroupISTPSunTempOffsY2_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16SunTempOffsY2_Tbl)
#define   ISTP_au16GroupISTPSunTempOffsY3_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16SunTempOffsY3_Tbl)
#define   ISTP_au16GroupISTPSunTempOffsY4_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16SunTempOffsY4_Tbl)
#define   ISTP_au16GroupISTPSunTempOatX_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16SunTempOatX_Tbl)
#define   ISTP_au16GroupISTPSunBctlOffsX_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16SunBctlOffsX_Tbl)
#define   ISTP_au16GroupISTPSunBctlOffsY1_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16SunBctlOffsY1_Tbl)
#define   ISTP_au16GroupISTPSunBctlOffsY2_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16SunBctlOffsY2_Tbl)
#define   ISTP_au16GroupISTPSunBctlOffsY3_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16SunBctlOffsY3_Tbl)
#define   ISTP_au16GroupISTPSunBctlOffsY4_Tbl          (ISTP_stLayout.stGroupISTP.stIstpData.au16SunBctlOffsY4_Tbl)
#define   ISTP_u8GroupISTP1VariableConst          (ISTP_stLayout.stGroupISTP1.stModeVarSelect.u8VariableConst)
#define   ISTP_u8GroupISTP1VCFillByte1            (ISTP_stLayout.stGroupISTP1.stModeVarSelect.u8VCFillByte1)
#define   ISTP_u8GroupISTP1VCFillByte2            (ISTP_stLayout.stGroupISTP1.stModeVarSelect.u8VCFillByte2)
#define   ISTP_u8GroupISTP1VCFillByte3            (ISTP_stLayout.stGroupISTP1.stModeVarSelect.u8VCFillByte3)
#define   ISTP_u8GroupISTP1ModelType              (ISTP_stLayout.stGroupISTP1.stModelVariant.u8ModelType)
#define   ISTP_u8GroupISTP1VWType                 (ISTP_stLayout.stGroupISTP1.stModelVariant.u8VWType)
#define   ISTP_u8GroupISTP2VariableConst          (ISTP_stRomLayout.stGroupISTP2.stMMIVarSelect.u8VariableConst)
#define   ISTP_u8GroupISTP2VCFillByte1            (ISTP_stRomLayout.stGroupISTP2.stMMIVarSelect.u8VCFillByte1)
#define   ISTP_u8GroupISTP2VCFillByte2            (ISTP_stRomLayout.stGroupISTP2.stMMIVarSelect.u8VCFillByte2)
#define   ISTP_u8GroupISTP2VCFillByte3            (ISTP_stRomLayout.stGroupISTP2.stMMIVarSelect.u8VCFillByte3)
#define   ISTP_au8GroupISTP2MMISaveData           (ISTP_stRomLayout.stGroupISTP2.stMMISaveData.au8MMISaveData)
#define   ISTP_u8GroupISTP3VariableConst          (ISTP_stRomLayout.stGroupISTP3.stSHCVarSelect.u8VariableConst)
#define   ISTP_u8GroupISTP3VCFillByte1            (ISTP_stRomLayout.stGroupISTP3.stSHCVarSelect.u8VCFillByte1)
#define   ISTP_u8GroupISTP3VCFillByte2            (ISTP_stRomLayout.stGroupISTP3.stSHCVarSelect.u8VCFillByte2)
#define   ISTP_u8GroupISTP3VCFillByte3            (ISTP_stRomLayout.stGroupISTP3.stSHCVarSelect.u8VCFillByte3)
#define   ISTP_au8GroupISTP3SHCOutPutVoltage          (ISTP_stRomLayout.stGroupISTP3.stSHCCalibration.au8SHCOutPutVoltage)
#define   ISTP_au8GroupISTP3SHCOutPutCurrent          (ISTP_stRomLayout.stGroupISTP3.stSHCCalibration.au8SHCOutPutCurrent)
#define   ISTP_u8GroupISTP3SHCKParameter          (ISTP_stRomLayout.stGroupISTP3.stSHCCalibration.u8SHCKParameter)
#define   ISTP_u8GroupISTP3FillByte_SHCCalibration          (ISTP_stRomLayout.stGroupISTP3.stSHCCalibration.u8FillByte_SHCCalibration)
#define   ISTP_nCoolantTLimitL                    (840U)    /*Not Allow Stop when coolant temp <*/
#define   ISTP_nCoolantTLimitH                    (950U)    /*Allow Stop when coolant temp >*/
#define   ISTP_nHeatTBlowout                      (460U)    /*Allow  stop when blowout temp<*/
#define   ISTP_nCoolTBlowout                      (340U)    /*Allow  stop when blowout temp<*/
#define   ISTP_nDefaultTBlowoutH                  (500U)    /*Not Allow  stop when blowout temp>*/
#define   ISTP_nDefaultTBlowoutL                  (460U)    /*Allow  stop when blowout temp<*/
#define   ISTP_nWinterFTBlowoutH                  (700U)    /*Not Allow  stop when blowout temp>*/
#define   ISTP_nWinterFTBlowoutL                  (600U)    /*Allow  stop when blowout temp<*/
#define   ISTP_nHeatTempDiffH                     (480U)    /*Allowed stop if SI <=*/
#define   ISTP_nHeatTempDiffL                     (520U)    /*Not allowed stop if SI >=*/
#define   ISTP_nCoolTempDiffH                     (320U)    /*Allowed stop if SI >=*/
#define   ISTP_nCoolTempDiffL                     (240U)    /*Not allowed stop if SI <=*/
#define   ISTP_nDefaultTempDiffH                  (460U)    /*Allowed stop if SI <=*/
#define   ISTP_nDefaultTempDiffL                  (500U)    /*Not allowed stop if SI >=*/
#define   ISTP_nWinterFTempDiffH                  (480U)    /*Allowed stop if SI <=*/
#define   ISTP_nWinterFTempDiffL                  (520U)    /*Not allowed stop if SI >=*/
#define   ISTP_nEvapTempH                         (600U)    /*Not allow stop if EVAP >*/
#define   ISTP_nEvapTempL                         (480U)    /*Allow stop if EVAP <*/
#define   ISTP_nHeatModeOat                       (550U)    /**/
#define   ISTP_nCoolModeOat                       (650U)    /**/
#define   ISTP_nCcsBlowOutLimit                   (450U)    /**/
#define   ISTP_nUseRTE                            (0U)    /**/
#define   ISTP_nUseCCP                            (1U)    /**/
#define   ISTP_nMaxAC							  (0u)
/******************************** END *************************************/
 /*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
*ISTP_Cfg.h
******************************************************************************/