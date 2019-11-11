/* -----------------------------------------------------------------------------
  Filename:    can_par.h
  Description: Toolversion: 01.00.22.01.50.07.51.00.00.00
               
               Serial Number: CBD1500751
               Customer Info: Desay SV Automotive Co., Ltd.
                              Package: CBD Geely SLP1
                              Micro: R7F7010233AFP
                              Compiler: Green Hills 6.1.4
               
               
               Generator Fwk   : GENy 
               Generator Module: DrvCan__base
               
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

#if !defined(__CAN_PAR_H__)
#define __CAN_PAR_H__

#include "can_cfg.h"
#include "v_inc.h"
#include "drv_par.h"

/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of callback functions
 ----------------------------------------------------------------------------- */

#if defined(C_MULTIPLE_RECEIVE_CHANNEL) || defined(C_SINGLE_RECEIVE_CHANNEL)
#endif

/* CODE CATEGORY 1 START */
extern vuint8 TpFuncPrecopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 TpPrecopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */


/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of confirmation functions
 ----------------------------------------------------------------------------- */

/* CODE CATEGORY 1 START */
extern void TpDrvConfirmation(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void CanNm_NmMsgConfirmation(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */



/* -----------------------------------------------------------------------------
    &&&~ Multiple Callback Functions
 ----------------------------------------------------------------------------- */

/* CODE CATEGORY 1 START */
extern C_CALLBACK_1 void C_CALLBACK_2 ApplCanTxConfirmation(CanTxInfoStructPtr txStruct);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
extern C_CALLBACK_1 void C_CALLBACK_2 CbdWrpCanTxConfirmation(CanTxInfoStructPtr txStruct);
/* CODE CATEGORY 1 END */


/* -----------------------------------------------------------------------------
    &&&~ Extern declarations Hw specififc
 ----------------------------------------------------------------------------- */

/* ROM CATEGORY 4 START */
V_MEMROM0 extern  V_MEMROM1 vuint8 V_MEMROM2 CanRxFifoDepth_0[1];
/* ROM CATEGORY 4 END */

/* ROM CATEGORY 4 START */
V_MEMROM0 extern  V_MEMROM1 tCanFilterRulesBc V_MEMROM2 CanFilterRulesBc_0[2];
/* ROM CATEGORY 4 END */





/* -----------------------------------------------------------------------------
    &&&~ Handles of send objects
 ----------------------------------------------------------------------------- */

#define CanTxAC_DiagResp                     0
#define CanTxAC_LIN2CANData                  1
#define CanTxCCP_Calibration_Read            2
#define CanTxAC_LIN2CANCom                   3
#define CanTxNWM_AC                          4
#define CanTxAC_Status_Info                  5
#define CanTxAC_ReqSts                       6


/* -----------------------------------------------------------------------------
    &&&~ Access to confirmation flags
 ----------------------------------------------------------------------------- */

#define AC_LIN2CANData_conf_b                (CanConfirmationFlags.w[0].b0)
#define CanWriteSyncAC_LIN2CANData_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  AC_LIN2CANData_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define CCP_Calibration_Read_conf_b          (CanConfirmationFlags.w[0].b1)
#define CanWriteSyncCCP_Calibration_Read_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  CCP_Calibration_Read_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define AC_LIN2CANCom_conf_b                 (CanConfirmationFlags.w[0].b2)
#define CanWriteSyncAC_LIN2CANCom_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  AC_LIN2CANCom_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define AC_Status_Info_conf_b                (CanConfirmationFlags.w[0].b3)
#define CanWriteSyncAC_Status_Info_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  AC_Status_Info_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define AC_ReqSts_conf_b                     (CanConfirmationFlags.w[0].b4)
#define CanWriteSyncAC_ReqSts_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  AC_ReqSts_conf_b = (x); \
  CanEndFlagWriteSync(); \
}


/* -----------------------------------------------------------------------------
    &&&~ Handles of receive objects
 ----------------------------------------------------------------------------- */

#define CanRxFunc_DiagReq                    0
#define CanRxAC_DiagReq                      1
#define CanRxCCP_Calibration_Write           2
#define CanRxEMS_EngineRPM                   3
#define CanRxIPK_TotalOdometer               4
#define CanRxMMI_AC_Command                  5
#define CanRxMMI_HVSM_Command                6
#define CanRxTBOX_RemCon                     7
#define CanRxEMS_EngineDriverInfo            8
#define CanRxPEPS_Message_Sts                9
#define CanRxESC_Status                      10
#define CanRxEMS_EngineStatus                11


/* -----------------------------------------------------------------------------
    &&&~ Access to indication flags
 ----------------------------------------------------------------------------- */

#define CCP_Calibration_Write_ind_b          (CanIndicationFlags.w[0].b0)
#define CanWriteSyncCCP_Calibration_Write_ind_b(x) \
{ \
  CanStartFlagWriteSync(); \
  CCP_Calibration_Write_ind_b = (x); \
  CanEndFlagWriteSync(); \
}
#define EMS_EngineRPM_ind_b                  (CanIndicationFlags.w[0].b1)
#define CanWriteSyncEMS_EngineRPM_ind_b(x) \
{ \
  CanStartFlagWriteSync(); \
  EMS_EngineRPM_ind_b = (x); \
  CanEndFlagWriteSync(); \
}
#define IPK_TotalOdometer_ind_b              (CanIndicationFlags.w[0].b2)
#define CanWriteSyncIPK_TotalOdometer_ind_b(x) \
{ \
  CanStartFlagWriteSync(); \
  IPK_TotalOdometer_ind_b = (x); \
  CanEndFlagWriteSync(); \
}
#define MMI_AC_Command_ind_b                 (CanIndicationFlags.w[0].b3)
#define CanWriteSyncMMI_AC_Command_ind_b(x) \
{ \
  CanStartFlagWriteSync(); \
  MMI_AC_Command_ind_b = (x); \
  CanEndFlagWriteSync(); \
}
#define MMI_HVSM_Command_ind_b               (CanIndicationFlags.w[0].b4)
#define CanWriteSyncMMI_HVSM_Command_ind_b(x) \
{ \
  CanStartFlagWriteSync(); \
  MMI_HVSM_Command_ind_b = (x); \
  CanEndFlagWriteSync(); \
}
#define TBOX_RemCon_ind_b                    (CanIndicationFlags.w[0].b5)
#define CanWriteSyncTBOX_RemCon_ind_b(x) \
{ \
  CanStartFlagWriteSync(); \
  TBOX_RemCon_ind_b = (x); \
  CanEndFlagWriteSync(); \
}
#define EMS_EngineDriverInfo_ind_b           (CanIndicationFlags.w[0].b6)
#define CanWriteSyncEMS_EngineDriverInfo_ind_b(x) \
{ \
  CanStartFlagWriteSync(); \
  EMS_EngineDriverInfo_ind_b = (x); \
  CanEndFlagWriteSync(); \
}
#define PEPS_Message_Sts_ind_b               (CanIndicationFlags.w[0].b7)
#define CanWriteSyncPEPS_Message_Sts_ind_b(x) \
{ \
  CanStartFlagWriteSync(); \
  PEPS_Message_Sts_ind_b = (x); \
  CanEndFlagWriteSync(); \
}
#define ESC_Status_ind_b                     (CanIndicationFlags.w[0].b10)
#define CanWriteSyncESC_Status_ind_b(x) \
{ \
  CanStartFlagWriteSync(); \
  ESC_Status_ind_b = (x); \
  CanEndFlagWriteSync(); \
}
#define EMS_EngineStatus_ind_b               (CanIndicationFlags.w[0].b11)
#define CanWriteSyncEMS_EngineStatus_ind_b(x) \
{ \
  CanStartFlagWriteSync(); \
  EMS_EngineStatus_ind_b = (x); \
  CanEndFlagWriteSync(); \
}


/* -----------------------------------------------------------------------------
    &&&~ Access to signals
 ----------------------------------------------------------------------------- */

#define b_AC_DiagResp_Byte0_c                (AC_DiagResp.AC_DiagResp.AC_DiagResp_Byte0)
#define b_AC_DiagResp_Byte1_c                (AC_DiagResp.AC_DiagResp.AC_DiagResp_Byte1)
#define b_AC_DiagResp_Byte2_c                (AC_DiagResp.AC_DiagResp.AC_DiagResp_Byte2)
#define b_AC_DiagResp_Byte3_c                (AC_DiagResp.AC_DiagResp.AC_DiagResp_Byte3)
#define b_AC_DiagResp_Byte4_c                (AC_DiagResp.AC_DiagResp.AC_DiagResp_Byte4)
#define b_AC_DiagResp_Byte5_c                (AC_DiagResp.AC_DiagResp.AC_DiagResp_Byte5)
#define b_AC_DiagResp_Byte6_c                (AC_DiagResp.AC_DiagResp.AC_DiagResp_Byte6)
#define b_AC_DiagResp_Byte7_c                (AC_DiagResp.AC_DiagResp.AC_DiagResp_Byte7)
#define b_ForLinData0_c                      (AC_LIN2CANData.AC_LIN2CANData.ForLinData0)
#define b_ForLinData1_c                      (AC_LIN2CANData.AC_LIN2CANData.ForLinData1)
#define b_ForLinData2_c                      (AC_LIN2CANData.AC_LIN2CANData.ForLinData2)
#define b_ForLinData3_c                      (AC_LIN2CANData.AC_LIN2CANData.ForLinData3)
#define b_ForLinData4_c                      (AC_LIN2CANData.AC_LIN2CANData.ForLinData4)
#define b_ForLinData5_c                      (AC_LIN2CANData.AC_LIN2CANData.ForLinData5)
#define b_ForLinData6_c                      (AC_LIN2CANData.AC_LIN2CANData.ForLinData6)
#define b_ForLinData7_c                      (AC_LIN2CANData.AC_LIN2CANData.ForLinData7)
#define b_AC_CCP_Read_Byte0_c                (CCP_Calibration_Read.CCP_Calibration_Read.AC_CCP_Read_Byte0)
#define b_AC_CCP_Read_Byte1_c                (CCP_Calibration_Read.CCP_Calibration_Read.AC_CCP_Read_Byte1)
#define b_AC_CCP_Read_Byte2_c                (CCP_Calibration_Read.CCP_Calibration_Read.AC_CCP_Read_Byte2)
#define b_AC_CCP_Read_Byte3_c                (CCP_Calibration_Read.CCP_Calibration_Read.AC_CCP_Read_Byte3)
#define b_AC_CCP_Read_Byte4_c                (CCP_Calibration_Read.CCP_Calibration_Read.AC_CCP_Read_Byte4)
#define b_AC_CCP_Read_Byte5_c                (CCP_Calibration_Read.CCP_Calibration_Read.AC_CCP_Read_Byte5)
#define b_AC_CCP_Read_Byte6_c                (CCP_Calibration_Read.CCP_Calibration_Read.AC_CCP_Read_Byte6)
#define b_AC_CCP_Read_Byte7_c                (CCP_Calibration_Read.CCP_Calibration_Read.AC_CCP_Read_Byte7)
#define b_ForLinComman0_c                    (AC_LIN2CANCom.AC_LIN2CANCom.ForLinComman0)
#define b_ForLinComman1_c                    (AC_LIN2CANCom.AC_LIN2CANCom.ForLinComman1)
#define b_ForLinComman2_c                    (AC_LIN2CANCom.AC_LIN2CANCom.ForLinComman2)
#define b_ForLinComman3_c                    (AC_LIN2CANCom.AC_LIN2CANCom.ForLinComman3)
#define b_ForLinComman4_c                    (AC_LIN2CANCom.AC_LIN2CANCom.ForLinComman4)
#define b_ForLinComman5_c                    (AC_LIN2CANCom.AC_LIN2CANCom.ForLinComman5)
#define b_ForLinComman6_c                    (AC_LIN2CANCom.AC_LIN2CANCom.ForLinComman6)
#define b_ForLinComman7_c                    (AC_LIN2CANCom.AC_LIN2CANCom.ForLinComman7)
#define b_AC_AutoState_b                     (AC_Status_Info.AC_Status_Info.AC_AutoState)
#define b_AC_DisplayRequest_b                (AC_Status_Info.AC_Status_Info.AC_DisplayRequest)
#define b_AC_MaxAcState_b                    (AC_Status_Info.AC_Status_Info.AC_MaxAcState)
#define b_AC_FrontDefrostState_b             (AC_Status_Info.AC_Status_Info.AC_FrontDefrostState)
#define b_AC_IntakeAirState_b                (AC_Status_Info.AC_Status_Info.AC_IntakeAirState)
#define b_AC_AqsState_b                      (AC_Status_Info.AC_Status_Info.AC_AqsState)
#define b_AC_BlowerLevel_b                   (AC_Status_Info.AC_Status_Info.AC_BlowerLevel)
#define b_AC_DualState_b                     (AC_Status_Info.AC_Status_Info.AC_DualState)
#define b_AC_IONIZERState_b                  (AC_Status_Info.AC_Status_Info.AC_IONIZERState)
#define b_AC_AirDistributionMode_b           (AC_Status_Info.AC_Status_Info.AC_AirDistributionMode)
#define b_AC_OnState_b                       (AC_Status_Info.AC_Status_Info.AC_OnState)
#define b_AC_LeftSetTemperature_b            (AC_Status_Info.AC_Status_Info.AC_LeftSetTemperature)
#define b_AC_AirCleanState_b                 (AC_Status_Info.AC_Status_Info.AC_AirCleanState)
#define b_AC_RightSetTemperature_b           (AC_Status_Info.AC_Status_Info.AC_RightSetTemperature)
#define b_AC_RemoteControlSt_b               (AC_Status_Info.AC_Status_Info.AC_RemoteControlSt)
#define b_AC_DrvHeatSts_b                    (AC_Status_Info.AC_Status_Info.AC_DrvHeatSts)
#define b_AC_PassHeatingSts_b                (AC_Status_Info.AC_Status_Info.AC_PassHeatingSts)
#define b_AC_ACCompReq_b                     (AC_ReqSts.AC_ReqSts.AC_ACCompReq)
#define b_AC_AmbientTemperatureInvalid_b     (AC_ReqSts.AC_ReqSts.AC_AmbientTemperatureInvalid)
#define b_AC_SSM_Allowance_b                 (AC_ReqSts.AC_ReqSts.AC_SSM_Allowance)
#define b_AC_SSM_StartReq_b                  (AC_ReqSts.AC_ReqSts.AC_SSM_StartReq)
#define b_AC_ACCompReqInvalid_b              (AC_ReqSts.AC_ReqSts.AC_ACCompReqInvalid)
#define b_AC_FanStatus_b                     (AC_ReqSts.AC_ReqSts.AC_FanStatus)
#define b_AC_InsideTemperatureInvalid_b      (AC_ReqSts.AC_ReqSts.AC_InsideTemperatureInvalid)
#define b_AC_AmbientTemperature_c            (AC_ReqSts.AC_ReqSts.AC_AmbientTemperature)
#define b_AC_PM25InDen_0_b                   (AC_ReqSts.AC_ReqSts.AC_PM25InDen_0)
#define b_AC_PM25InDen_1_b                   (AC_ReqSts.AC_ReqSts.AC_PM25InDen_1)
#define b_AC_PM25InDen_b(c) \
{ \
  b_AC_PM25InDen_0_b = (vuint8) (((vuint16) (c)) & 0x0F); \
  b_AC_PM25InDen_1_b = (vuint8) ((((vuint16) (c)) & 0x0FF0) >> 4); \
}
#define b_AC_PM25OutDen_0_b                  (AC_ReqSts.AC_ReqSts.AC_PM25OutDen_0)
#define b_AC_PM25OutDen_1_b                  (AC_ReqSts.AC_ReqSts.AC_PM25OutDen_1)
#define b_AC_PM25OutDen_b(c) \
{ \
  b_AC_PM25OutDen_0_b = (vuint8) (((vuint16) (c)) & 0xFF); \
  b_AC_PM25OutDen_1_b = (vuint8) ((((vuint16) (c)) & 0x0F00) >> 8); \
}
#define b_AC_AirInQLevel_b                   (AC_ReqSts.AC_ReqSts.AC_AirInQLevel)
#define b_AC_AirOutQLevel_b                  (AC_ReqSts.AC_ReqSts.AC_AirOutQLevel)
#define b_AC_PM25Sts_b                       (AC_ReqSts.AC_ReqSts.AC_PM25Sts)
#define b_AC_InsideTemperature_c             (AC_ReqSts.AC_ReqSts.AC_InsideTemperature)
#define b_AC_PM25PopupReq_b                  (AC_ReqSts.AC_ReqSts.AC_PM25PopupReq)
#define b_Func_DiagReq_Byte0_c               (Func_DiagReq.Func_DiagReq.Func_DiagReq_Byte0)
#define b_Func_DiagReq_Byte1_c               (Func_DiagReq.Func_DiagReq.Func_DiagReq_Byte1)
#define b_Func_DiagReq_Byte2_c               (Func_DiagReq.Func_DiagReq.Func_DiagReq_Byte2)
#define b_Func_DiagReq_Byte3_c               (Func_DiagReq.Func_DiagReq.Func_DiagReq_Byte3)
#define b_Func_DiagReq_Byte4_c               (Func_DiagReq.Func_DiagReq.Func_DiagReq_Byte4)
#define b_Func_DiagReq_Byte5_c               (Func_DiagReq.Func_DiagReq.Func_DiagReq_Byte5)
#define b_Func_DiagReq_Byte6_c               (Func_DiagReq.Func_DiagReq.Func_DiagReq_Byte6)
#define b_Func_DiagReq_Byte7_c               (Func_DiagReq.Func_DiagReq.Func_DiagReq_Byte7)
#define b_AC_DiagReq_Byte0_c                 (AC_DiagReq.AC_DiagReq.AC_DiagReq_Byte0)
#define b_AC_DiagReq_Byte1_c                 (AC_DiagReq.AC_DiagReq.AC_DiagReq_Byte1)
#define b_AC_DiagReq_Byte2_c                 (AC_DiagReq.AC_DiagReq.AC_DiagReq_Byte2)
#define b_AC_DiagReq_Byte3_c                 (AC_DiagReq.AC_DiagReq.AC_DiagReq_Byte3)
#define b_AC_DiagReq_Byte4_c                 (AC_DiagReq.AC_DiagReq.AC_DiagReq_Byte4)
#define b_AC_DiagReq_Byte5_c                 (AC_DiagReq.AC_DiagReq.AC_DiagReq_Byte5)
#define b_AC_DiagReq_Byte6_c                 (AC_DiagReq.AC_DiagReq.AC_DiagReq_Byte6)
#define b_AC_DiagReq_Byte7_c                 (AC_DiagReq.AC_DiagReq.AC_DiagReq_Byte7)
#define b_AC_CCP_Write_Byte0_c               (CCP_Calibration_Write.CCP_Calibration_Write.AC_CCP_Write_Byte0)
#define b_AC_CCP_Write_Byte1_c               (CCP_Calibration_Write.CCP_Calibration_Write.AC_CCP_Write_Byte1)
#define b_AC_CCP_Write_Byte2_c               (CCP_Calibration_Write.CCP_Calibration_Write.AC_CCP_Write_Byte2)
#define b_AC_CCP_Write_Byte3_c               (CCP_Calibration_Write.CCP_Calibration_Write.AC_CCP_Write_Byte3)
#define b_AC_CCP_Write_Byte4_c               (CCP_Calibration_Write.CCP_Calibration_Write.AC_CCP_Write_Byte4)
#define b_AC_CCP_Write_Byte5_c               (CCP_Calibration_Write.CCP_Calibration_Write.AC_CCP_Write_Byte5)
#define b_AC_CCP_Write_Byte6_c               (CCP_Calibration_Write.CCP_Calibration_Write.AC_CCP_Write_Byte6)
#define b_AC_CCP_Write_Byte7_c               (CCP_Calibration_Write.CCP_Calibration_Write.AC_CCP_Write_Byte7)
#define b_EMS_EngineSpeedRPM_0_b             (EMS_EngineRPM.EMS_EngineRPM.EMS_EngineSpeedRPM_0)
#define b_EMS_EngineSpeedRPM_1_b             (EMS_EngineRPM.EMS_EngineRPM.EMS_EngineSpeedRPM_1)
#define b_EMS_EngineSpeedRPM_b               ((vuint16) (((vuint16) b_EMS_EngineSpeedRPM_0_b) | (((vuint16) b_EMS_EngineSpeedRPM_1_b) << 8)))
#define b_EMS_SSMStatus_b                    (EMS_EngineRPM.EMS_EngineRPM.EMS_SSMStatus)
#define b_EMS_EngineSpeedRPMInvalid_b        (EMS_EngineRPM.EMS_EngineRPM.EMS_EngineSpeedRPMInvalid)
#define b_EMS_EngStatus_b                    (EMS_EngineRPM.EMS_EngineRPM.EMS_EngStatus)
#define b_IPK_IPKTotalOdometer_0_b           (IPK_TotalOdometer.IPK_TotalOdometer.IPK_IPKTotalOdometer_0)
#define b_IPK_IPKTotalOdometer_1_b           (IPK_TotalOdometer.IPK_TotalOdometer.IPK_IPKTotalOdometer_1)
#define b_IPK_IPKTotalOdometer_2_b           (IPK_TotalOdometer.IPK_TotalOdometer.IPK_IPKTotalOdometer_2)
#define b_IPK_IPKTotalOdometer_b             ((vuint32) (((vuint32) b_IPK_IPKTotalOdometer_0_b) | ((((vuint32) b_IPK_IPKTotalOdometer_1_b) << 8) | (((vuint32) b_IPK_IPKTotalOdometer_2_b) << 16))))
#define b_MMI_AutoKey_b                      (MMI_AC_Command.MMI_AC_Command.MMI_AutoKey)
#define b_MMI_FrontDefrostKey_b              (MMI_AC_Command.MMI_AC_Command.MMI_FrontDefrostKey)
#define b_MMI_FreshReciKey_b                 (MMI_AC_Command.MMI_AC_Command.MMI_FreshReciKey)
#define b_MMI_AqsKey_b                       (MMI_AC_Command.MMI_AC_Command.MMI_AqsKey)
#define b_MMI_AcKey_b                        (MMI_AC_Command.MMI_AC_Command.MMI_AcKey)
#define b_MMI_BlowerFanLevel_b               (MMI_AC_Command.MMI_AC_Command.MMI_BlowerFanLevel)
#define b_MMI_DualKey_b                      (MMI_AC_Command.MMI_AC_Command.MMI_DualKey)
#define b_MMI_PM25Key_b                      (MMI_AC_Command.MMI_AC_Command.MMI_PM25Key)
#define b_MMI_IONIZERKey_b                   (MMI_AC_Command.MMI_AC_Command.MMI_IONIZERKey)
#define b_MMI_AirDistributionModeReq_b       (MMI_AC_Command.MMI_AC_Command.MMI_AirDistributionModeReq)
#define b_MMI_PM25PopupActive_b              (MMI_AC_Command.MMI_AC_Command.MMI_PM25PopupActive)
#define b_MMI_AirConditionerPowerKey_b       (MMI_AC_Command.MMI_AC_Command.MMI_AirConditionerPowerKey)
#define b_MMI_LeftSetTemp_b                  (MMI_AC_Command.MMI_AC_Command.MMI_LeftSetTemp)
#define b_MMI_RightSetTemp_b                 (MMI_AC_Command.MMI_AC_Command.MMI_RightSetTemp)
#define b_MMI_PM25PopupOperationSts_b        (MMI_AC_Command.MMI_AC_Command.MMI_PM25PopupOperationSts)
#define b_MMI_DrvHeatReq_b                   (MMI_HVSM_Command.MMI_HVSM_Command.MMI_DrvHeatReq)
#define b_MMI_PassHeatReq_b                  (MMI_HVSM_Command.MMI_HVSM_Command.MMI_PassHeatReq)
#define b_TBOX_Inquire_PM25_b                (TBOX_RemCon.TBOX_RemCon.TBOX_Inquire_PM25)
#define b_TBOX_AirCleanerReq_b               (TBOX_RemCon.TBOX_RemCon.TBOX_AirCleanerReq)
#define b_TBOX_TempReq_b                     (TBOX_RemCon.TBOX_RemCon.TBOX_TempReq)
#define b_TBOX_AirConditionerReq_b           (TBOX_RemCon.TBOX_RemCon.TBOX_AirConditionerReq)
#define b_EMS_EngineCoolantTemp_c            (EMS_EngineDriverInfo.EMS_EngineDriverInfo.EMS_EngineCoolantTemp)
#define b_EMS_EngineCoolantTempInvalid_b     (EMS_EngineDriverInfo.EMS_EngineDriverInfo.EMS_EngineCoolantTempInvalid)
#define b_PEPS_PowerModeValidity_b           (PEPS_Message_Sts.PEPS_Message_Sts.PEPS_PowerModeValidity)
#define b_PEPS_PowerMode_b                   (PEPS_Message_Sts.PEPS_Message_Sts.PEPS_PowerMode)
#define b_PEPS_RemoteControlSt_b             (PEPS_Message_Sts.PEPS_Message_Sts.PEPS_RemoteControlSt)
#define b_ESC_VehicleSpeed_0_b               (ESC_Status.ESC_Status.ESC_VehicleSpeed_0)
#define b_ESC_VehicleSpeed_1_b               (ESC_Status.ESC_Status.ESC_VehicleSpeed_1)
#define b_ESC_VehicleSpeed_b                 ((vuint16) (((vuint16) b_ESC_VehicleSpeed_0_b) | (((vuint16) b_ESC_VehicleSpeed_1_b) << 5)))
#define b_ESC_VehicleSpeedInvalid_b          (ESC_Status.ESC_Status.ESC_VehicleSpeedInvalid)
#define b_EMS_ACStatus_b                     (EMS_EngineStatus.EMS_EngineStatus.EMS_ACStatus)

//wuyijun we usedmesg

#define  Canoe_IC_Debug_ic_choice                   (EMS_EngineStatus.EMS_EngineStatus.unused0)                     //  1  MCU       2touch_L        3touch_R
#define Canoe_IC_Debug_debug_cmd                     (EMS_EngineStatus.EMS_EngineStatus.unused1)                //CMD
#define Canoe_IC_Debug_debug_option                     (EMS_EngineStatus.EMS_EngineStatus.unused2)             //option
#define Canoe_IC_Debug_debug_parameter                     (EMS_EngineStatus.EMS_EngineStatus.unused3)     //parameter




/* -----------------------------------------------------------------------------
    &&&~ Access to data bytes of Rx messages
 ----------------------------------------------------------------------------- */

/* ID: 0x000007df, Handle: 0, Func_DiagReq [BC] */
#define c1_Func_DiagReq_c                    (Func_DiagReq._c[0])
#define c2_Func_DiagReq_c                    (Func_DiagReq._c[1])
#define c3_Func_DiagReq_c                    (Func_DiagReq._c[2])
#define c4_Func_DiagReq_c                    (Func_DiagReq._c[3])
#define c5_Func_DiagReq_c                    (Func_DiagReq._c[4])
#define c6_Func_DiagReq_c                    (Func_DiagReq._c[5])
#define c7_Func_DiagReq_c                    (Func_DiagReq._c[6])
#define c8_Func_DiagReq_c                    (Func_DiagReq._c[7])

/* ID: 0x000007c6, Handle: 1, AC_DiagReq [BC] */
#define c1_AC_DiagReq_c                      (AC_DiagReq._c[0])
#define c2_AC_DiagReq_c                      (AC_DiagReq._c[1])
#define c3_AC_DiagReq_c                      (AC_DiagReq._c[2])
#define c4_AC_DiagReq_c                      (AC_DiagReq._c[3])
#define c5_AC_DiagReq_c                      (AC_DiagReq._c[4])
#define c6_AC_DiagReq_c                      (AC_DiagReq._c[5])
#define c7_AC_DiagReq_c                      (AC_DiagReq._c[6])
#define c8_AC_DiagReq_c                      (AC_DiagReq._c[7])

/* ID: 0x000006b1, Handle: 2, CCP_Calibration_Write [BC] */
#define c1_CCP_Calibration_Write_c           (CCP_Calibration_Write._c[0])
#define c2_CCP_Calibration_Write_c           (CCP_Calibration_Write._c[1])
#define c3_CCP_Calibration_Write_c           (CCP_Calibration_Write._c[2])
#define c4_CCP_Calibration_Write_c           (CCP_Calibration_Write._c[3])
#define c5_CCP_Calibration_Write_c           (CCP_Calibration_Write._c[4])
#define c6_CCP_Calibration_Write_c           (CCP_Calibration_Write._c[5])
#define c7_CCP_Calibration_Write_c           (CCP_Calibration_Write._c[6])
#define c8_CCP_Calibration_Write_c           (CCP_Calibration_Write._c[7])

/* ID: 0x00000085, Handle: 3, EMS_EngineRPM [BC] */
#define c1_EMS_EngineRPM_c                   (EMS_EngineRPM._c[0])
#define c2_EMS_EngineRPM_c                   (EMS_EngineRPM._c[1])
#define c3_EMS_EngineRPM_c                   (EMS_EngineRPM._c[2])
#define c4_EMS_EngineRPM_c                   (EMS_EngineRPM._c[3])
#define c5_EMS_EngineRPM_c                   (EMS_EngineRPM._c[4])
#define c6_EMS_EngineRPM_c                   (EMS_EngineRPM._c[5])

/* ID: 0x000003f1, Handle: 4, IPK_TotalOdometer [FC] */
#define c1_IPK_TotalOdometer_c               (IPK_TotalOdometer._c[0])
#define c2_IPK_TotalOdometer_c               (IPK_TotalOdometer._c[1])
#define c3_IPK_TotalOdometer_c               (IPK_TotalOdometer._c[2])

/* ID: 0x000002a5, Handle: 5, MMI_AC_Command [FC] */
#define c1_MMI_AC_Command_c                  (MMI_AC_Command._c[0])
#define c2_MMI_AC_Command_c                  (MMI_AC_Command._c[1])
#define c3_MMI_AC_Command_c                  (MMI_AC_Command._c[2])
#define c4_MMI_AC_Command_c                  (MMI_AC_Command._c[3])
#define c5_MMI_AC_Command_c                  (MMI_AC_Command._c[4])
#define c6_MMI_AC_Command_c                  (MMI_AC_Command._c[5])

/* ID: 0x000002a3, Handle: 6, MMI_HVSM_Command [FC] */
#define c1_MMI_HVSM_Command_c                (MMI_HVSM_Command._c[0])

/* ID: 0x00000292, Handle: 7, TBOX_RemCon [FC] */
#define c1_TBOX_RemCon_c                     (TBOX_RemCon._c[0])
#define c2_TBOX_RemCon_c                     (TBOX_RemCon._c[1])
#define c3_TBOX_RemCon_c                     (TBOX_RemCon._c[2])
#define c4_TBOX_RemCon_c                     (TBOX_RemCon._c[3])

/* ID: 0x00000288, Handle: 8, EMS_EngineDriverInfo [FC] */
#define c1_EMS_EngineDriverInfo_c            (EMS_EngineDriverInfo._c[0])
#define c2_EMS_EngineDriverInfo_c            (EMS_EngineDriverInfo._c[1])

/* ID: 0x000001e2, Handle: 9, PEPS_Message_Sts [FC] */
#define c1_PEPS_Message_Sts_c                (PEPS_Message_Sts._c[0])

/* ID: 0x00000125, Handle: 10, ESC_Status [FC] */
#define c1_ESC_Status_c                      (ESC_Status._c[0])
#define c2_ESC_Status_c                      (ESC_Status._c[1])
#define c3_ESC_Status_c                      (ESC_Status._c[2])

/* ID: 0x00000086, Handle: 11, EMS_EngineStatus [FC] */
#define c1_EMS_EngineStatus_c                (EMS_EngineStatus._c[0])
#define c2_EMS_EngineStatus_c                (EMS_EngineStatus._c[1])
#define c3_EMS_EngineStatus_c                (EMS_EngineStatus._c[2])
#define c4_EMS_EngineStatus_c                (EMS_EngineStatus._c[3])
#define c5_EMS_EngineStatus_c                (EMS_EngineStatus._c[4])
#define c6_EMS_EngineStatus_c                (EMS_EngineStatus._c[5])
#define c7_EMS_EngineStatus_c                (EMS_EngineStatus._c[6])



/* -----------------------------------------------------------------------------
    &&&~ Access to data bytes of Tx messages
 ----------------------------------------------------------------------------- */

/* ID: 0x000007ce, Handle: 0, AC_DiagResp [BC] */
#define c1_AC_DiagResp_c                     (AC_DiagResp._c[0])
#define c2_AC_DiagResp_c                     (AC_DiagResp._c[1])
#define c3_AC_DiagResp_c                     (AC_DiagResp._c[2])
#define c4_AC_DiagResp_c                     (AC_DiagResp._c[3])
#define c5_AC_DiagResp_c                     (AC_DiagResp._c[4])
#define c6_AC_DiagResp_c                     (AC_DiagResp._c[5])
#define c7_AC_DiagResp_c                     (AC_DiagResp._c[6])
#define c8_AC_DiagResp_c                     (AC_DiagResp._c[7])

/* ID: 0x000006b3, Handle: 1, AC_LIN2CANData [BC] */
#define c1_AC_LIN2CANData_c                  (AC_LIN2CANData._c[0])
#define c2_AC_LIN2CANData_c                  (AC_LIN2CANData._c[1])
#define c3_AC_LIN2CANData_c                  (AC_LIN2CANData._c[2])
#define c4_AC_LIN2CANData_c                  (AC_LIN2CANData._c[3])
#define c5_AC_LIN2CANData_c                  (AC_LIN2CANData._c[4])
#define c6_AC_LIN2CANData_c                  (AC_LIN2CANData._c[5])
#define c7_AC_LIN2CANData_c                  (AC_LIN2CANData._c[6])
#define c8_AC_LIN2CANData_c                  (AC_LIN2CANData._c[7])

/* ID: 0x000006b2, Handle: 2, CCP_Calibration_Read [BC] */
#define c1_CCP_Calibration_Read_c            (CCP_Calibration_Read._c[0])
#define c2_CCP_Calibration_Read_c            (CCP_Calibration_Read._c[1])
#define c3_CCP_Calibration_Read_c            (CCP_Calibration_Read._c[2])
#define c4_CCP_Calibration_Read_c            (CCP_Calibration_Read._c[3])
#define c5_CCP_Calibration_Read_c            (CCP_Calibration_Read._c[4])
#define c6_CCP_Calibration_Read_c            (CCP_Calibration_Read._c[5])
#define c7_CCP_Calibration_Read_c            (CCP_Calibration_Read._c[6])
#define c8_CCP_Calibration_Read_c            (CCP_Calibration_Read._c[7])

/* ID: 0x000006b0, Handle: 3, AC_LIN2CANCom [BC] */
#define c1_AC_LIN2CANCom_c                   (AC_LIN2CANCom._c[0])
#define c2_AC_LIN2CANCom_c                   (AC_LIN2CANCom._c[1])
#define c3_AC_LIN2CANCom_c                   (AC_LIN2CANCom._c[2])
#define c4_AC_LIN2CANCom_c                   (AC_LIN2CANCom._c[3])
#define c5_AC_LIN2CANCom_c                   (AC_LIN2CANCom._c[4])
#define c6_AC_LIN2CANCom_c                   (AC_LIN2CANCom._c[5])
#define c7_AC_LIN2CANCom_c                   (AC_LIN2CANCom._c[6])
#define c8_AC_LIN2CANCom_c                   (AC_LIN2CANCom._c[7])

/* ID: 0x00000406, Handle: 4, NWM_AC [BC] */
#define c1_NWM_AC_c                          (NWM_AC._c[0])
#define c2_NWM_AC_c                          (NWM_AC._c[1])
#define c3_NWM_AC_c                          (NWM_AC._c[2])
#define c4_NWM_AC_c                          (NWM_AC._c[3])
#define c5_NWM_AC_c                          (NWM_AC._c[4])
#define c6_NWM_AC_c                          (NWM_AC._c[5])
#define c7_NWM_AC_c                          (NWM_AC._c[6])
#define c8_NWM_AC_c                          (NWM_AC._c[7])

/* ID: 0x000002f2, Handle: 5, AC_Status_Info [FC] */
#define c1_AC_Status_Info_c                  (AC_Status_Info._c[0])
#define c2_AC_Status_Info_c                  (AC_Status_Info._c[1])
#define c3_AC_Status_Info_c                  (AC_Status_Info._c[2])
#define c4_AC_Status_Info_c                  (AC_Status_Info._c[3])
#define c5_AC_Status_Info_c                  (AC_Status_Info._c[4])
#define c6_AC_Status_Info_c                  (AC_Status_Info._c[5])
#define c7_AC_Status_Info_c                  (AC_Status_Info._c[6])
#define c8_AC_Status_Info_c                  (AC_Status_Info._c[7])

/* ID: 0x000002f1, Handle: 6, AC_ReqSts [FC] */
#define c1_AC_ReqSts_c                       (AC_ReqSts._c[0])
#define c2_AC_ReqSts_c                       (AC_ReqSts._c[1])
#define c3_AC_ReqSts_c                       (AC_ReqSts._c[2])
#define c4_AC_ReqSts_c                       (AC_ReqSts._c[3])
#define c5_AC_ReqSts_c                       (AC_ReqSts._c[4])
#define c6_AC_ReqSts_c                       (AC_ReqSts._c[5])
#define c7_AC_ReqSts_c                       (AC_ReqSts._c[6])
#define c8_AC_ReqSts_c                       (AC_ReqSts._c[7])



/* -----------------------------------------------------------------------------
    &&&~ RDS Access
 ----------------------------------------------------------------------------- */

#define b_CAN_AC_ACCompReq_b                 (RDS193.AC_ReqSts.AC_ACCompReq)
#define b_CAN_AC_AmbientTemperatureInvalid_b (RDS193.AC_ReqSts.AC_AmbientTemperatureInvalid)
#define b_CAN_AC_SSM_Allowance_b             (RDS193.AC_ReqSts.AC_SSM_Allowance)
#define b_CAN_AC_SSM_StartReq_b              (RDS193.AC_ReqSts.AC_SSM_StartReq)
#define b_CAN_AC_ACCompReqInvalid_b          (RDS193.AC_ReqSts.AC_ACCompReqInvalid)
#define b_CAN_AC_FanStatus_b                 (RDS193.AC_ReqSts.AC_FanStatus)
#define b_CAN_AC_InsideTemperatureInvalid_b  (RDS193.AC_ReqSts.AC_InsideTemperatureInvalid)
#define b_CAN_AC_AmbientTemperature_c        (RDS193.AC_ReqSts.AC_AmbientTemperature)
#define b_CAN_AC_PM25InDen_0_b               (RDS193.AC_ReqSts.AC_PM25InDen_0)
#define b_CAN_AC_PM25InDen_1_b               (RDS193.AC_ReqSts.AC_PM25InDen_1)
#define b_CAN_AC_PM25InDen_b(c) \
{ \
  b_CAN_AC_PM25InDen_0_b = (vuint8) (((vuint16) (c)) & 0x0F); \
  b_CAN_AC_PM25InDen_1_b = (vuint8) ((((vuint16) (c)) & 0x0FF0) >> 4); \
}
#define b_CAN_AC_PM25OutDen_0_b              (RDS193.AC_ReqSts.AC_PM25OutDen_0)
#define b_CAN_AC_PM25OutDen_1_b              (RDS193.AC_ReqSts.AC_PM25OutDen_1)
#define b_CAN_AC_PM25OutDen_b(c) \
{ \
  b_CAN_AC_PM25OutDen_0_b = (vuint8) (((vuint16) (c)) & 0xFF); \
  b_CAN_AC_PM25OutDen_1_b = (vuint8) ((((vuint16) (c)) & 0x0F00) >> 8); \
}
#define b_CAN_AC_AirInQLevel_b               (RDS193.AC_ReqSts.AC_AirInQLevel)
#define b_CAN_AC_AirOutQLevel_b              (RDS193.AC_ReqSts.AC_AirOutQLevel)
#define b_CAN_AC_PM25Sts_b                   (RDS193.AC_ReqSts.AC_PM25Sts)
#define b_CAN_AC_InsideTemperature_c         (RDS193.AC_ReqSts.AC_InsideTemperature)
#define b_CAN_AC_PM25PopupReq_b              (RDS193.AC_ReqSts.AC_PM25PopupReq)

typedef struct _c_AC_ReqSts_RDS_msgTypeTag
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
} _c_AC_ReqSts_RDS_msgType;

#define b_CAN_AC_AutoState_b                 (RDS194.AC_Status_Info.AC_AutoState)
#define b_CAN_AC_DisplayRequest_b            (RDS194.AC_Status_Info.AC_DisplayRequest)
#define b_CAN_AC_MaxAcState_b                (RDS194.AC_Status_Info.AC_MaxAcState)
#define b_CAN_AC_FrontDefrostState_b         (RDS194.AC_Status_Info.AC_FrontDefrostState)
#define b_CAN_AC_IntakeAirState_b            (RDS194.AC_Status_Info.AC_IntakeAirState)
#define b_CAN_AC_AqsState_b                  (RDS194.AC_Status_Info.AC_AqsState)
#define b_CAN_AC_BlowerLevel_b               (RDS194.AC_Status_Info.AC_BlowerLevel)
#define b_CAN_AC_DualState_b                 (RDS194.AC_Status_Info.AC_DualState)
#define b_CAN_AC_IONIZERState_b              (RDS194.AC_Status_Info.AC_IONIZERState)
#define b_CAN_AC_AirDistributionMode_b       (RDS194.AC_Status_Info.AC_AirDistributionMode)
#define b_CAN_AC_OnState_b                   (RDS194.AC_Status_Info.AC_OnState)
#define b_CAN_AC_LeftSetTemperature_b        (RDS194.AC_Status_Info.AC_LeftSetTemperature)
#define b_CAN_AC_AirCleanState_b             (RDS194.AC_Status_Info.AC_AirCleanState)
#define b_CAN_AC_RightSetTemperature_b       (RDS194.AC_Status_Info.AC_RightSetTemperature)
#define b_CAN_AC_RemoteControlSt_b           (RDS194.AC_Status_Info.AC_RemoteControlSt)
#define b_CAN_AC_DrvHeatSts_b                (RDS194.AC_Status_Info.AC_DrvHeatSts)
#define b_CAN_AC_PassHeatingSts_b            (RDS194.AC_Status_Info.AC_PassHeatingSts)

typedef struct _c_AC_Status_Info_RDS_msgTypeTag
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
} _c_AC_Status_Info_RDS_msgType;

#define b_CAN_IPK_IPKTotalOdometer_0_b       (RDS0.IPK_TotalOdometer.IPK_IPKTotalOdometer_0)
#define b_CAN_IPK_IPKTotalOdometer_1_b       (RDS0.IPK_TotalOdometer.IPK_IPKTotalOdometer_1)
#define b_CAN_IPK_IPKTotalOdometer_2_b       (RDS0.IPK_TotalOdometer.IPK_IPKTotalOdometer_2)
#define b_CAN_IPK_IPKTotalOdometer_b         ((vuint32) (((vuint32) b_CAN_IPK_IPKTotalOdometer_0_b) | ((((vuint32) b_CAN_IPK_IPKTotalOdometer_1_b) << 8) | (((vuint32) b_CAN_IPK_IPKTotalOdometer_2_b) << 16))))

typedef struct _c_IPK_TotalOdometer_RDS_msgTypeTag
{
  vbittype IPK_IPKTotalOdometer_2 : 8;
  vbittype IPK_IPKTotalOdometer_1 : 8;
  vbittype IPK_IPKTotalOdometer_0 : 8;
} _c_IPK_TotalOdometer_RDS_msgType;

#define b_CAN_MMI_AutoKey_b                  (RDS1.MMI_AC_Command.MMI_AutoKey)
#define b_CAN_MMI_FrontDefrostKey_b          (RDS1.MMI_AC_Command.MMI_FrontDefrostKey)
#define b_CAN_MMI_FreshReciKey_b             (RDS1.MMI_AC_Command.MMI_FreshReciKey)
#define b_CAN_MMI_AqsKey_b                   (RDS1.MMI_AC_Command.MMI_AqsKey)
#define b_CAN_MMI_AcKey_b                    (RDS1.MMI_AC_Command.MMI_AcKey)
#define b_CAN_MMI_BlowerFanLevel_b           (RDS1.MMI_AC_Command.MMI_BlowerFanLevel)
#define b_CAN_MMI_DualKey_b                  (RDS1.MMI_AC_Command.MMI_DualKey)
#define b_CAN_MMI_PM25Key_b                  (RDS1.MMI_AC_Command.MMI_PM25Key)
#define b_CAN_MMI_IONIZERKey_b               (RDS1.MMI_AC_Command.MMI_IONIZERKey)
#define b_CAN_MMI_AirDistributionModeReq_b   (RDS1.MMI_AC_Command.MMI_AirDistributionModeReq)
#define b_CAN_MMI_PM25PopupActive_b          (RDS1.MMI_AC_Command.MMI_PM25PopupActive)
#define b_CAN_MMI_AirConditionerPowerKey_b   (RDS1.MMI_AC_Command.MMI_AirConditionerPowerKey)
#define b_CAN_MMI_LeftSetTemp_b              (RDS1.MMI_AC_Command.MMI_LeftSetTemp)
#define b_CAN_MMI_RightSetTemp_b             (RDS1.MMI_AC_Command.MMI_RightSetTemp)
#define b_CAN_MMI_PM25PopupOperationSts_b    (RDS1.MMI_AC_Command.MMI_PM25PopupOperationSts)

typedef struct _c_MMI_AC_Command_RDS_msgTypeTag
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
} _c_MMI_AC_Command_RDS_msgType;

#define b_CAN_MMI_DrvHeatReq_b               (RDS2.MMI_HVSM_Command.MMI_DrvHeatReq)
#define b_CAN_MMI_PassHeatReq_b              (RDS2.MMI_HVSM_Command.MMI_PassHeatReq)

typedef struct _c_MMI_HVSM_Command_RDS_msgTypeTag
{
  vbittype MMI_DrvHeatReq : 3;
  vbittype unused0 : 2;
  vbittype MMI_PassHeatReq : 3;
} _c_MMI_HVSM_Command_RDS_msgType;

#define b_CAN_TBOX_Inquire_PM25_b            (RDS3.TBOX_RemCon.TBOX_Inquire_PM25)
#define b_CAN_TBOX_AirCleanerReq_b           (RDS3.TBOX_RemCon.TBOX_AirCleanerReq)
#define b_CAN_TBOX_TempReq_b                 (RDS3.TBOX_RemCon.TBOX_TempReq)
#define b_CAN_TBOX_AirConditionerReq_b       (RDS3.TBOX_RemCon.TBOX_AirConditionerReq)

typedef struct _c_TBOX_RemCon_RDS_msgTypeTag
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
} _c_TBOX_RemCon_RDS_msgType;

#define b_CAN_EMS_EngineCoolantTemp_c        (RDS4.EMS_EngineDriverInfo.EMS_EngineCoolantTemp)
#define b_CAN_EMS_EngineCoolantTempInvalid_b (RDS4.EMS_EngineDriverInfo.EMS_EngineCoolantTempInvalid)

typedef struct _c_EMS_EngineDriverInfo_RDS_msgTypeTag
{
  vbittype EMS_EngineCoolantTemp : 8;
  vbittype EMS_EngineCoolantTempInvalid : 1;
  vbittype unused0 : 7;
} _c_EMS_EngineDriverInfo_RDS_msgType;

#define b_CAN_PEPS_PowerModeValidity_b       (RDS5.PEPS_Message_Sts.PEPS_PowerModeValidity)
#define b_CAN_PEPS_PowerMode_b               (RDS5.PEPS_Message_Sts.PEPS_PowerMode)
#define b_CAN_PEPS_RemoteControlSt_b         (RDS5.PEPS_Message_Sts.PEPS_RemoteControlSt)

typedef struct _c_PEPS_Message_Sts_RDS_msgTypeTag
{
  vbittype PEPS_PowerModeValidity : 2;
  vbittype PEPS_PowerMode : 3;
  vbittype unused0 : 2;
  vbittype PEPS_RemoteControlSt : 1;
} _c_PEPS_Message_Sts_RDS_msgType;

#define b_CAN_ESC_VehicleSpeed_0_b           (RDS6.ESC_Status.ESC_VehicleSpeed_0)
#define b_CAN_ESC_VehicleSpeed_1_b           (RDS6.ESC_Status.ESC_VehicleSpeed_1)
#define b_CAN_ESC_VehicleSpeed_b             ((vuint16) (((vuint16) b_CAN_ESC_VehicleSpeed_0_b) | (((vuint16) b_CAN_ESC_VehicleSpeed_1_b) << 5)))
#define b_CAN_ESC_VehicleSpeedInvalid_b      (RDS6.ESC_Status.ESC_VehicleSpeedInvalid)

typedef struct _c_ESC_Status_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype ESC_VehicleSpeed_1 : 8;
  vbittype unused1 : 2;
  vbittype ESC_VehicleSpeedInvalid : 1;
  vbittype ESC_VehicleSpeed_0 : 5;
} _c_ESC_Status_RDS_msgType;

#define b_CAN_EMS_ACStatus_b                 (RDS7.EMS_EngineStatus.EMS_ACStatus)

typedef struct _c_EMS_EngineStatus_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype EMS_ACStatus : 1;
  vbittype unused6 : 7;
} _c_EMS_EngineStatus_RDS_msgType;

#define b_CAN_AC_DiagReq_Byte0_c             (RDSBasic.AC_DiagReq.AC_DiagReq_Byte0)
#define b_CAN_AC_DiagReq_Byte1_c             (RDSBasic.AC_DiagReq.AC_DiagReq_Byte1)
#define b_CAN_AC_DiagReq_Byte2_c             (RDSBasic.AC_DiagReq.AC_DiagReq_Byte2)
#define b_CAN_AC_DiagReq_Byte3_c             (RDSBasic.AC_DiagReq.AC_DiagReq_Byte3)
#define b_CAN_AC_DiagReq_Byte4_c             (RDSBasic.AC_DiagReq.AC_DiagReq_Byte4)
#define b_CAN_AC_DiagReq_Byte5_c             (RDSBasic.AC_DiagReq.AC_DiagReq_Byte5)
#define b_CAN_AC_DiagReq_Byte6_c             (RDSBasic.AC_DiagReq.AC_DiagReq_Byte6)
#define b_CAN_AC_DiagReq_Byte7_c             (RDSBasic.AC_DiagReq.AC_DiagReq_Byte7)

typedef struct _c_AC_DiagReq_RDS_msgTypeTag
{
  vbittype AC_DiagReq_Byte0 : 8;
  vbittype AC_DiagReq_Byte1 : 8;
  vbittype AC_DiagReq_Byte2 : 8;
  vbittype AC_DiagReq_Byte3 : 8;
  vbittype AC_DiagReq_Byte4 : 8;
  vbittype AC_DiagReq_Byte5 : 8;
  vbittype AC_DiagReq_Byte6 : 8;
  vbittype AC_DiagReq_Byte7 : 8;
} _c_AC_DiagReq_RDS_msgType;

#define b_CAN_Func_DiagReq_Byte0_c           (RDSBasic.Func_DiagReq.Func_DiagReq_Byte0)
#define b_CAN_Func_DiagReq_Byte1_c           (RDSBasic.Func_DiagReq.Func_DiagReq_Byte1)
#define b_CAN_Func_DiagReq_Byte2_c           (RDSBasic.Func_DiagReq.Func_DiagReq_Byte2)
#define b_CAN_Func_DiagReq_Byte3_c           (RDSBasic.Func_DiagReq.Func_DiagReq_Byte3)
#define b_CAN_Func_DiagReq_Byte4_c           (RDSBasic.Func_DiagReq.Func_DiagReq_Byte4)
#define b_CAN_Func_DiagReq_Byte5_c           (RDSBasic.Func_DiagReq.Func_DiagReq_Byte5)
#define b_CAN_Func_DiagReq_Byte6_c           (RDSBasic.Func_DiagReq.Func_DiagReq_Byte6)
#define b_CAN_Func_DiagReq_Byte7_c           (RDSBasic.Func_DiagReq.Func_DiagReq_Byte7)

typedef struct _c_Func_DiagReq_RDS_msgTypeTag
{
  vbittype Func_DiagReq_Byte0 : 8;
  vbittype Func_DiagReq_Byte1 : 8;
  vbittype Func_DiagReq_Byte2 : 8;
  vbittype Func_DiagReq_Byte3 : 8;
  vbittype Func_DiagReq_Byte4 : 8;
  vbittype Func_DiagReq_Byte5 : 8;
  vbittype Func_DiagReq_Byte6 : 8;
  vbittype Func_DiagReq_Byte7 : 8;
} _c_Func_DiagReq_RDS_msgType;

typedef union _c_RDS_Tx_bufTag
{
  vuint8 _c[8];
} _c_RDS_Tx_buf;
typedef union _c_RDS193_bufTag
{
  vuint8 _c[8];
  _c_AC_ReqSts_RDS_msgType AC_ReqSts;
} _c_RDS193_buf;
typedef union _c_RDS194_bufTag
{
  vuint8 _c[8];
  _c_AC_Status_Info_RDS_msgType AC_Status_Info;
} _c_RDS194_buf;
typedef union _c_RDS0_bufTag
{
  vuint8 _c[3];
  _c_IPK_TotalOdometer_RDS_msgType IPK_TotalOdometer;
} _c_RDS0_buf;
typedef union _c_RDS1_bufTag
{
  vuint8 _c[6];
  _c_MMI_AC_Command_RDS_msgType MMI_AC_Command;
} _c_RDS1_buf;
typedef union _c_RDS2_bufTag
{
  vuint8 _c[1];
  _c_MMI_HVSM_Command_RDS_msgType MMI_HVSM_Command;
} _c_RDS2_buf;
typedef union _c_RDS3_bufTag
{
  vuint8 _c[4];
  _c_TBOX_RemCon_RDS_msgType TBOX_RemCon;
} _c_RDS3_buf;
typedef union _c_RDS4_bufTag
{
  vuint8 _c[2];
  _c_EMS_EngineDriverInfo_RDS_msgType EMS_EngineDriverInfo;
} _c_RDS4_buf;
typedef union _c_RDS5_bufTag
{
  vuint8 _c[1];
  _c_PEPS_Message_Sts_RDS_msgType PEPS_Message_Sts;
} _c_RDS5_buf;
typedef union _c_RDS6_bufTag
{
  vuint8 _c[3];
  _c_ESC_Status_RDS_msgType ESC_Status;
} _c_RDS6_buf;
typedef union _c_RDS7_bufTag
{
  vuint8 _c[7];
  _c_EMS_EngineStatus_RDS_msgType EMS_EngineStatus;
} _c_RDS7_buf;
typedef union _c_RDSBasic_bufTag
{
  vuint8 _c[8];
  _c_AC_DiagReq_RDS_msgType AC_DiagReq;
  _c_Func_DiagReq_RDS_msgType Func_DiagReq;
} _c_RDSBasic_buf;


#define RDSTx                                ((* ((_c_RDS_Tx_buf MEMORY_NORMAL *)(0xffd00000 + 0x608 + 0xa00))))
#define RDS193                               ((* ((_c_RDS193_buf MEMORY_NORMAL *)(0xffd00000 + 0x608 + 0xa10))))
#define RDS194                               ((* ((_c_RDS194_buf MEMORY_NORMAL *)(0xffd00000 + 0x608 + 0xa20))))
#define RDS0                                 ((* ((_c_RDS0_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS1                                 ((* ((_c_RDS1_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS2                                 ((* ((_c_RDS2_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS3                                 ((* ((_c_RDS3_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS4                                 ((* ((_c_RDS4_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS5                                 ((* ((_c_RDS5_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS6                                 ((* ((_c_RDS6_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS7                                 ((* ((_c_RDS7_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDSBasic                             ((* ((_c_RDSBasic_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))



#define C_TX_NORMAL_HW_OBJ                   192
#define C_TX_NORMAL_HW_CHANNEL               0
#define CanTxAC_ReqSts_HW_OBJ                193
#define CanTxAC_ReqSts_HW_CHANNEL            0
#define CanTxAC_Status_Info_HW_OBJ           194
#define CanTxAC_Status_Info_HW_CHANNEL       0
#define CanRxIPK_TotalOdometer_HW_OBJ        0
#define CanRxIPK_TotalOdometer_HW_CHANNEL    0
#define CanRxMMI_AC_Command_HW_OBJ           1
#define CanRxMMI_AC_Command_HW_CHANNEL       0
#define CanRxMMI_HVSM_Command_HW_OBJ         2
#define CanRxMMI_HVSM_Command_HW_CHANNEL     0
#define CanRxTBOX_RemCon_HW_OBJ              3
#define CanRxTBOX_RemCon_HW_CHANNEL          0
#define CanRxEMS_EngineDriverInfo_HW_OBJ     4
#define CanRxEMS_EngineDriverInfo_HW_CHANNEL 0
#define CanRxPEPS_Message_Sts_HW_OBJ         5
#define CanRxPEPS_Message_Sts_HW_CHANNEL     0
#define CanRxESC_Status_HW_OBJ               6
#define CanRxESC_Status_HW_CHANNEL           0
#define CanRxEMS_EngineStatus_HW_OBJ         7
#define CanRxEMS_EngineStatus_HW_CHANNEL     0
#define C_BASIC0_HW_OBJ                      128
#define C_BASIC0_HW_CHANNEL                  0




/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 286121459
      #error "The magic number of the generated file <D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\CanGenerateCode\can_par.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 286121459
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __CAN_PAR_H__ */
