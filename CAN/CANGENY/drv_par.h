/* -----------------------------------------------------------------------------
  Filename:    drv_par.h
  Description: Toolversion: 01.00.22.01.50.07.51.00.00.00
               
               Serial Number: CBD1500751
               Customer Info: Desay SV Automotive Co., Ltd.
                              Package: CBD Geely SLP1
                              Micro: R7F7010233AFP
                              Compiler: Green Hills 6.1.4
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyDriverBase
               
               Configuration   : D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\XXX_CAN_20180517.gny
               
               ECU: 
                       TargetSystem: Hw_Rh850Cpu
                       Compiler:     GreenHills
                       Derivates:    F1L
               
               Channel "Channel0":
                       Databasefile: D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\FE-5DB&7DA CAN Communication Matrix V1.61_Release LIN2CAN_AC.dbc
                       Bussystem:    CAN
                       Manufacturer: Geely
                       Node:         AC

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2015 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#if !defined(__DRV_PAR_H__)
#define __DRV_PAR_H__

/* -----------------------------------------------------------------------------
    &&&~ Signal Structures
 ----------------------------------------------------------------------------- */

typedef struct _c_AC_ReqSts_msgTypeTag
{
  vbittype AC_ACCompReq : 1;
  vbittype AC_AmbientTemperatureInvalid : 1;
  vbittype AC_SSM_Allowance : 1;
  vbittype AC_SSM_StartReq : 1;
  vbittype AC_ACCompReqInvalid : 1;
  vbittype AC_FanStatus : 1;
  vbittype unused0 : 1;
  vbittype AC_InsideTemperatureInvalid : 1;
  vbittype AC_AmbientTemperature : 8;
  vbittype AC_PM25InDen_1 : 8;
  vbittype AC_PM25OutDen_1 : 4;
  vbittype AC_PM25InDen_0 : 4;
  vbittype AC_PM25OutDen_0 : 8;
  vbittype AC_AirInQLevel : 3;
  vbittype AC_AirOutQLevel : 3;
  vbittype AC_PM25Sts : 2;
  vbittype AC_InsideTemperature : 8;
  vbittype unused1 : 4;
  vbittype AC_PM25PopupReq : 2;
  vbittype unused2 : 2;
} _c_AC_ReqSts_msgType;
typedef struct _c_NWM_AC_msgTypeTag
{
  vbittype AC_Address : 8;
  vbittype AC_RMR : 1;
  vbittype unused0 : 3;
  vbittype AC_AWB : 1;
  vbittype unused1 : 3;
  vbittype AC_Wakeup_reasons : 8;
  vbittype AC_NMSts : 1;
  vbittype unused2 : 7;
  vbittype unused3 : 1;
  vbittype AC_Stayawake_reasons_Bit33 : 1;
  vbittype unused4 : 4;
  vbittype AC_Stayawake_reasons_Bit38 : 1;
  vbittype unused5 : 1;
  vbittype unused6 : 8;
  vbittype unused7 : 8;
  vbittype unused8 : 8;
} _c_NWM_AC_msgType;
typedef struct _c_AC_DiagReq_msgTypeTag
{
  vbittype AC_DiagReq_Byte0 : 8;
  vbittype AC_DiagReq_Byte1 : 8;
  vbittype AC_DiagReq_Byte2 : 8;
  vbittype AC_DiagReq_Byte3 : 8;
  vbittype AC_DiagReq_Byte4 : 8;
  vbittype AC_DiagReq_Byte5 : 8;
  vbittype AC_DiagReq_Byte6 : 8;
  vbittype AC_DiagReq_Byte7 : 8;
} _c_AC_DiagReq_msgType;
typedef struct _c_Func_DiagReq_msgTypeTag
{
  vbittype Func_DiagReq_Byte0 : 8;
  vbittype Func_DiagReq_Byte1 : 8;
  vbittype Func_DiagReq_Byte2 : 8;
  vbittype Func_DiagReq_Byte3 : 8;
  vbittype Func_DiagReq_Byte4 : 8;
  vbittype Func_DiagReq_Byte5 : 8;
  vbittype Func_DiagReq_Byte6 : 8;
  vbittype Func_DiagReq_Byte7 : 8;
} _c_Func_DiagReq_msgType;
typedef struct _c_AC_DiagResp_msgTypeTag
{
  vbittype AC_DiagResp_Byte0 : 8;
  vbittype AC_DiagResp_Byte1 : 8;
  vbittype AC_DiagResp_Byte2 : 8;
  vbittype AC_DiagResp_Byte3 : 8;
  vbittype AC_DiagResp_Byte4 : 8;
  vbittype AC_DiagResp_Byte5 : 8;
  vbittype AC_DiagResp_Byte6 : 8;
  vbittype AC_DiagResp_Byte7 : 8;
} _c_AC_DiagResp_msgType;
typedef struct _c_CCP_Calibration_Read_msgTypeTag
{
  vbittype AC_CCP_Read_Byte0 : 8;
  vbittype AC_CCP_Read_Byte1 : 8;
  vbittype AC_CCP_Read_Byte2 : 8;
  vbittype AC_CCP_Read_Byte3 : 8;
  vbittype AC_CCP_Read_Byte4 : 8;
  vbittype AC_CCP_Read_Byte5 : 8;
  vbittype AC_CCP_Read_Byte6 : 8;
  vbittype AC_CCP_Read_Byte7 : 8;
} _c_CCP_Calibration_Read_msgType;
typedef struct _c_CCP_Calibration_Write_msgTypeTag
{
  vbittype AC_CCP_Write_Byte0 : 8;
  vbittype AC_CCP_Write_Byte1 : 8;
  vbittype AC_CCP_Write_Byte2 : 8;
  vbittype AC_CCP_Write_Byte3 : 8;
  vbittype AC_CCP_Write_Byte4 : 8;
  vbittype AC_CCP_Write_Byte5 : 8;
  vbittype AC_CCP_Write_Byte6 : 8;
  vbittype AC_CCP_Write_Byte7 : 8;
} _c_CCP_Calibration_Write_msgType;
typedef struct _c_TBOX_RemCon_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 2;
  vbittype TBOX_Inquire_PM25 : 1;
  vbittype TBOX_AirCleanerReq : 2;
  vbittype unused2 : 3;
  vbittype unused3 : 8;
  vbittype TBOX_TempReq : 5;
  vbittype TBOX_AirConditionerReq : 2;
  vbittype unused4 : 1;
} _c_TBOX_RemCon_msgType;
typedef struct _c_PEPS_Message_Sts_msgTypeTag
{
  vbittype PEPS_PowerModeValidity : 2;
  vbittype PEPS_PowerMode : 3;
  vbittype unused0 : 2;
  vbittype PEPS_RemoteControlSt : 1;
} _c_PEPS_Message_Sts_msgType;
typedef struct _c_MMI_AC_Command_msgTypeTag
{
  vbittype MMI_AutoKey : 1;
  vbittype unused0 : 2;
  vbittype MMI_FrontDefrostKey : 1;
  vbittype unused1 : 1;
  vbittype MMI_FreshReciKey : 1;
  vbittype MMI_AqsKey : 1;
  vbittype MMI_AcKey : 1;
  vbittype MMI_BlowerFanLevel : 4;
  vbittype unused2 : 1;
  vbittype MMI_DualKey : 1;
  vbittype MMI_PM25Key : 1;
  vbittype MMI_IONIZERKey : 1;
  vbittype MMI_AirDistributionModeReq : 3;
  vbittype MMI_PM25PopupActive : 1;
  vbittype MMI_AirConditionerPowerKey : 1;
  vbittype unused3 : 3;
  vbittype MMI_LeftSetTemp : 5;
  vbittype unused4 : 3;
  vbittype MMI_RightSetTemp : 5;
  vbittype unused5 : 3;
  vbittype MMI_PM25PopupOperationSts : 2;
  vbittype unused6 : 6;
} _c_MMI_AC_Command_msgType;
typedef struct _c_AC_Status_Info_msgTypeTag
{
  vbittype AC_AutoState : 1;
  vbittype AC_DisplayRequest : 1;
  vbittype AC_MaxAcState : 1;
  vbittype AC_FrontDefrostState : 1;
  vbittype AC_IntakeAirState : 2;
  vbittype AC_AqsState : 1;
  vbittype unused0 : 1;
  vbittype AC_BlowerLevel : 4;
  vbittype unused1 : 1;
  vbittype AC_DualState : 1;
  vbittype AC_IONIZERState : 2;
  vbittype AC_AirDistributionMode : 3;
  vbittype unused2 : 1;
  vbittype AC_OnState : 1;
  vbittype unused3 : 3;
  vbittype AC_LeftSetTemperature : 5;
  vbittype unused4 : 2;
  vbittype AC_AirCleanState : 1;
  vbittype AC_RightSetTemperature : 5;
  vbittype unused5 : 2;
  vbittype AC_RemoteControlSt : 1;
  vbittype unused6 : 8;
  vbittype AC_DrvHeatSts : 1;
  vbittype AC_PassHeatingSts : 1;
  vbittype unused7 : 6;
  vbittype unused8 : 8;
} _c_AC_Status_Info_msgType;
typedef struct _c_EMS_EngineRPM_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype EMS_EngineSpeedRPM_1 : 8;
  vbittype EMS_EngineSpeedRPM_0 : 8;
  vbittype unused2 : 8;
  vbittype EMS_SSMStatus : 3;
  vbittype unused3 : 1;
  vbittype EMS_EngineSpeedRPMInvalid : 1;
  vbittype EMS_EngStatus : 3;
} _c_EMS_EngineRPM_msgType;
typedef struct _c_EMS_EngineDriverInfo_msgTypeTag
{
  vbittype EMS_EngineCoolantTemp : 8;
  vbittype EMS_EngineCoolantTempInvalid : 1;
  vbittype unused0 : 7;
} _c_EMS_EngineDriverInfo_msgType;
typedef struct _c_ESC_Status_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype ESC_VehicleSpeed_1 : 8;
  vbittype unused1 : 2;
  vbittype ESC_VehicleSpeedInvalid : 1;
  vbittype ESC_VehicleSpeed_0 : 5;
} _c_ESC_Status_msgType;
typedef struct _c_IPK_TotalOdometer_msgTypeTag
{
  vbittype IPK_IPKTotalOdometer_2 : 8;
  vbittype IPK_IPKTotalOdometer_1 : 8;
  vbittype IPK_IPKTotalOdometer_0 : 8;
} _c_IPK_TotalOdometer_msgType;
typedef struct _c_AC_LIN2CANData_msgTypeTag
{
  vbittype ForLinData0 : 8;
  vbittype ForLinData1 : 8;
  vbittype ForLinData2 : 8;
  vbittype ForLinData3 : 8;
  vbittype ForLinData4 : 8;
  vbittype ForLinData5 : 8;
  vbittype ForLinData6 : 8;
  vbittype ForLinData7 : 8;
} _c_AC_LIN2CANData_msgType;
typedef struct _c_AC_LIN2CANCom_msgTypeTag
{
  vbittype ForLinComman0 : 8;
  vbittype ForLinComman1 : 8;
  vbittype ForLinComman2 : 8;
  vbittype ForLinComman3 : 8;
  vbittype ForLinComman4 : 8;
  vbittype ForLinComman5 : 8;
  vbittype ForLinComman6 : 8;
  vbittype ForLinComman7 : 8;
} _c_AC_LIN2CANCom_msgType;
typedef struct _c_MMI_HVSM_Command_msgTypeTag
{
  vbittype MMI_DrvHeatReq : 3;
  vbittype unused0 : 2;
  vbittype MMI_PassHeatReq : 3;
} _c_MMI_HVSM_Command_msgType;
typedef struct _c_EMS_EngineStatus_msgTypeTag  //we used
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype EMS_ACStatus : 1;
  vbittype unused6 : 7;
} _c_EMS_EngineStatus_msgType;


/* -----------------------------------------------------------------------------
    &&&~ Signal value names
 ----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
    &&&~ Message Unions
 ----------------------------------------------------------------------------- */

typedef union _c_AC_ReqSts_bufTag
{
  vuint8 _c[8];
  _c_AC_ReqSts_msgType AC_ReqSts;
} _c_AC_ReqSts_buf;
typedef union _c_NWM_AC_bufTag
{
  vuint8 _c[8];
  _c_NWM_AC_msgType NWM_AC;
} _c_NWM_AC_buf;
typedef union _c_AC_DiagReq_bufTag
{
  vuint8 _c[8];
  _c_AC_DiagReq_msgType AC_DiagReq;
} _c_AC_DiagReq_buf;
typedef union _c_Func_DiagReq_bufTag
{
  vuint8 _c[8];
  _c_Func_DiagReq_msgType Func_DiagReq;
} _c_Func_DiagReq_buf;
typedef union _c_AC_DiagResp_bufTag
{
  vuint8 _c[8];
  _c_AC_DiagResp_msgType AC_DiagResp;
} _c_AC_DiagResp_buf;
typedef union _c_CCP_Calibration_Read_bufTag
{
  vuint8 _c[8];
  _c_CCP_Calibration_Read_msgType CCP_Calibration_Read;
} _c_CCP_Calibration_Read_buf;
typedef union _c_CCP_Calibration_Write_bufTag
{
  vuint8 _c[8];
  _c_CCP_Calibration_Write_msgType CCP_Calibration_Write;
} _c_CCP_Calibration_Write_buf;
typedef union _c_TBOX_RemCon_bufTag
{
  vuint8 _c[4];
  _c_TBOX_RemCon_msgType TBOX_RemCon;
} _c_TBOX_RemCon_buf;
typedef union _c_PEPS_Message_Sts_bufTag
{
  vuint8 _c[1];
  _c_PEPS_Message_Sts_msgType PEPS_Message_Sts;
} _c_PEPS_Message_Sts_buf;
typedef union _c_MMI_AC_Command_bufTag
{
  vuint8 _c[6];
  _c_MMI_AC_Command_msgType MMI_AC_Command;
} _c_MMI_AC_Command_buf;
typedef union _c_AC_Status_Info_bufTag
{
  vuint8 _c[8];
  _c_AC_Status_Info_msgType AC_Status_Info;
} _c_AC_Status_Info_buf;
typedef union _c_EMS_EngineRPM_bufTag
{
  vuint8 _c[6];
  _c_EMS_EngineRPM_msgType EMS_EngineRPM;
} _c_EMS_EngineRPM_buf;
typedef union _c_EMS_EngineDriverInfo_bufTag
{
  vuint8 _c[2];
  _c_EMS_EngineDriverInfo_msgType EMS_EngineDriverInfo;
} _c_EMS_EngineDriverInfo_buf;
typedef union _c_ESC_Status_bufTag
{
  vuint8 _c[3];
  _c_ESC_Status_msgType ESC_Status;
} _c_ESC_Status_buf;
typedef union _c_IPK_TotalOdometer_bufTag
{
  vuint8 _c[3];
  _c_IPK_TotalOdometer_msgType IPK_TotalOdometer;
} _c_IPK_TotalOdometer_buf;
typedef union _c_AC_LIN2CANData_bufTag
{
  vuint8 _c[8];
  _c_AC_LIN2CANData_msgType AC_LIN2CANData;
} _c_AC_LIN2CANData_buf;
typedef union _c_AC_LIN2CANCom_bufTag
{
  vuint8 _c[8];
  _c_AC_LIN2CANCom_msgType AC_LIN2CANCom;
} _c_AC_LIN2CANCom_buf;
typedef union _c_MMI_HVSM_Command_bufTag
{
  vuint8 _c[1];
  _c_MMI_HVSM_Command_msgType MMI_HVSM_Command;
} _c_MMI_HVSM_Command_buf;
typedef union _c_EMS_EngineStatus_bufTag
{
  vuint8 _c[7];
  _c_EMS_EngineStatus_msgType EMS_EngineStatus;
} _c_EMS_EngineStatus_buf;


/* -----------------------------------------------------------------------------
    &&&~ Message Buffers
 ----------------------------------------------------------------------------- */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_AC_ReqSts_buf V_MEMRAM2 AC_ReqSts;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_NWM_AC_buf V_MEMRAM2 NWM_AC;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_AC_DiagReq_buf V_MEMRAM2 AC_DiagReq;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_Func_DiagReq_buf V_MEMRAM2 Func_DiagReq;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_AC_DiagResp_buf V_MEMRAM2 AC_DiagResp;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_CCP_Calibration_Read_buf V_MEMRAM2 CCP_Calibration_Read;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_CCP_Calibration_Write_buf V_MEMRAM2 CCP_Calibration_Write;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TBOX_RemCon_buf V_MEMRAM2 TBOX_RemCon;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_PEPS_Message_Sts_buf V_MEMRAM2 PEPS_Message_Sts;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_MMI_AC_Command_buf V_MEMRAM2 MMI_AC_Command;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_AC_Status_Info_buf V_MEMRAM2 AC_Status_Info;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_EMS_EngineRPM_buf V_MEMRAM2 EMS_EngineRPM;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_EMS_EngineDriverInfo_buf V_MEMRAM2 EMS_EngineDriverInfo;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_ESC_Status_buf V_MEMRAM2 ESC_Status;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_IPK_TotalOdometer_buf V_MEMRAM2 IPK_TotalOdometer;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_AC_LIN2CANData_buf V_MEMRAM2 AC_LIN2CANData;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_AC_LIN2CANCom_buf V_MEMRAM2 AC_LIN2CANCom;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_MMI_HVSM_Command_buf V_MEMRAM2 MMI_HVSM_Command;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_EMS_EngineStatus_buf V_MEMRAM2 EMS_EngineStatus;
/* RAM CATEGORY 2 END */





/* disable magic number check for support of multiple projects */
#ifndef SKIP_MAGIC_NUMBER
#define SKIP_MAGIC_NUMBER
#endif

#include "drv_par_l.h"


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 286121459
      #error "The magic number of the generated file <D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\CanGenerateCode\drv_par.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 286121459
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __DRV_PAR_H__ */
