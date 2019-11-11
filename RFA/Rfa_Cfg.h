/**************************************************************************************/
/*------------------------------------------------------------------------------------
              Automatically Generated File,do not edit this file manually!
-------------------------------------------------------------------------------------*/
/** Generated On : 2018-7-7  10:17:29                                       */
/**           By : uidp4501                                                 */
/**        Using : Rfa_Cfg_Template_Release_A11.xls                         */
/**         From : D:\HVACProject\Geely\FE-5DB&7DA\ProjectCode\01_APP\RFA   */
/**               (D = )                                                    */
/**************************************************************************************/
 
/******************************************************************************
Module Name : RFA
File Name : RFA_Cfg.h
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
#ifndef RFA_CFG_H
#define RFA_CFG_H

/* System-headerfiles */
#include "General.h"


/******************************************************************************
* MACROS and STRUCT
*
* In this section declare
* - all macros and structs used in the configuration head file and C file.
******************************************************************************/

#define  RFA_nRfaPositionLen    (3U)
#define  RFA_nRfaPositionLen    (3U)
#define  RFA_nReciroLimitPosition    (2U)
#define  RFA_nRecirConfigurationLen    (6U)
#define  RFA_nSolarRecircOffsetLen    (5U)

/*************************** Define Structures Arrary length ************************/

typedef struct RFA_stRfaInfo
{
   uint8    u8VariableConst;
   uint8    u8ModuleID;
   uint16   u16ModuleLen;
} RFA_tstRfaInfo;

typedef struct RFA_stRfaData
{
   uint16   au16RfaPositionX [ RFA_nRfaPositionLen ];
   uint16   au16RfaPositionY [ RFA_nRfaPositionLen ];
   uint16   au16ReciroLimitPosition [ RFA_nReciroLimitPosition ];
   uint8    au8RecirConfiguration [ RFA_nRecirConfigurationLen ];
   uint16   au16SolarRecircOffsetX [ RFA_nSolarRecircOffsetLen ];
   uint16   au16SolarRecircOffsetY [ RFA_nSolarRecircOffsetLen ];
} RFA_tstRfaData;

/*************************** Group Structures ************************/
typedef struct RFA_stGroup
{
   RFA_tstRfaInfo  stRfaInfo;
   RFA_tstRfaData  stRfaData;
   uint8  u8AddChkSum;
   uint8  u8XorChkSum;
} RFA_tstGroup;

/********************** LAYOUT STRUCTURE ****************************/

typedef struct 
{
   RFA_tstGroup  stGroup;
} RFA_tstRomLayout;

extern  const RFA_tstRomLayout RFA_stRomLayout;

/********************* VARIABLE ACCESS MACROS ***************************/
#define   RFA_u8GroupVariableConst                (RFA_stRomLayout.stGroup.stRfaInfo.u8VariableConst)
#define   RFA_u8GroupModuleID                     (RFA_stRomLayout.stGroup.stRfaInfo.u8ModuleID)
#define   RFA_u16GroupModuleLen                   (RFA_stRomLayout.stGroup.stRfaInfo.u16ModuleLen)
#define   RFA_au16GroupRfaPositionX               (RFA_stRomLayout.stGroup.stRfaData.au16RfaPositionX)
#define   RFA_au16GroupRfaPositionY               (RFA_stRomLayout.stGroup.stRfaData.au16RfaPositionY)
#define   RFA_au16GroupReciroLimitPosition          (RFA_stRomLayout.stGroup.stRfaData.au16ReciroLimitPosition)
#define   RFA_au8GroupRecirConfiguration          (RFA_stRomLayout.stGroup.stRfaData.au8RecirConfiguration)
#define   RFA_au16GroupSolarRecircOffsetX          (RFA_stRomLayout.stGroup.stRfaData.au16SolarRecircOffsetX)
#define   RFA_au16GroupSolarRecircOffsetY          (RFA_stRomLayout.stGroup.stRfaData.au16SolarRecircOffsetY)
#define   RFA_u16TempDiffMAX                      (640U)    /**/
#define   RFA_nFactorRes                          (128U)    /**/
#define   RFA_nBloTempSwitchpoint_Cfg             (1U)    /**/
#define   RFA_nOpenInterfaces_Cfg                 (0U)    /**/
#define   RFA_u16AqsFreTime                       (0U)    /**/
#define   RFA_u16AqsRecTime                       (180U)    /**/
#define   RFA_u16RecirTime                        (1200U)    /**/
#define   RFA_u16FreshTime                        (60U)    /**/
#define   RFA_u16BlwOutSwitchPiont0               (500U)    /**/
#define   RFA_u16BlwOutSwitchPiont1               (520U)    /**/
#define   RFA_u16BlwOutSwitchPiont2               (550U)    /**/
#define   RFA_u16BlwOutSwitchPiont3               (580U)    /**/
#define   RFA_u16OatSwitchPiontOn                 (630U)    /**/
#define   RFA_u16OatSwitchPiontOff                (580U)    /**/
#define   RFA_u16SIRecirc                         (540U)    /**/
#define   RFA_u16SIFresh                          (600U)    /**/
#define   RFA_u16SIRecirc2                        (640U)    /**/
#define   RFA_u16SIFresh2                         (680U)    /**/
#define   RFA_biSystemState                       (1U)    /*0--this project is ETC,1--this project is ATC*/
#define   RFA_biIsSunValid                        (1U)    /*0--no sun sensor, 1--with sun sensor*/
#define   RFA_biIsMotorFBValid                    (1U)    /*0-- without motor feedback, 1-- with motor feedback*/
#define   RFA_biAQS_Cfg                           (1U)    /*AQS--Air Quality System,0--without AQS,1--with AQS*/
#define   RFA_biStartStop_Cfg                     (0U)    /*Disable/Enable start/stop function*/
#define   RFA_biInletSensor_Cfg                   (0U)    /*Without/With inlet air sensor*/
#define   RFA_biMaxAC_Cfg                         (0U)    /*Without/With Max AC*/
#define   RFA_u16AqsOatLimitLo                    (410U)    /**/
#define   RFA_u16AqsOatLimitHi                    (430U)    /**/
#define   RFA_nUseRTE                             (0U)    /**/
#define   RFA_nIstpCfg                            (0U)    /**/
#define   RFA_nBreathPosCfg                       (1U)    /**/
#define   RFA_nUseCCP                             (1U)    /**/
#define   RFA_nPM25Cfg                            (1U)    /**/
#define   RFA_nOatSunSwitchpoint_Cfg              (1U)    /**/
#define   RFA_nAmbientTempCfg                     (1U)    /**/
#define   RFA_u16OatLimitLo                       (600U)    /**/
#define   RFA_u16OatLimitHi                       (650U)    /**/
#define   RFA_nLoAmbientTempCfg                   (1U)    /**/
#define   RFA_u16LowAmbientLimitLo                (410U)    /**/
#define   RFA_u16LowAmbientLimitHi                (430U)    /**/
/******************************** END *************************************/
 /*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef */

/*****************************************************************************
*RFA_Cfg.h
******************************************************************************/