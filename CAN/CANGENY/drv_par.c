/* -----------------------------------------------------------------------------
  Filename:    drv_par.c
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

#include "v_inc.h"
#include "can_inc.h"

#include "drv_par.h"
/* -----------------------------------------------------------------------------
    &&&~ Message Buffers
 ----------------------------------------------------------------------------- */

/* RAM CATEGORY 2 START */
/* PRQA  S 0759 QAC_Can_0759 */ /* MD_Can_0759 */
V_MEMRAM0 V_MEMRAM1 _c_AC_ReqSts_buf V_MEMRAM2 AC_ReqSts;
V_MEMRAM0 V_MEMRAM1 _c_NWM_AC_buf V_MEMRAM2 NWM_AC;
V_MEMRAM0 V_MEMRAM1 _c_AC_DiagReq_buf V_MEMRAM2 AC_DiagReq;
V_MEMRAM0 V_MEMRAM1 _c_Func_DiagReq_buf V_MEMRAM2 Func_DiagReq;
V_MEMRAM0 V_MEMRAM1 _c_AC_DiagResp_buf V_MEMRAM2 AC_DiagResp;
V_MEMRAM0 V_MEMRAM1 _c_CCP_Calibration_Read_buf V_MEMRAM2 CCP_Calibration_Read;
V_MEMRAM0 V_MEMRAM1 _c_CCP_Calibration_Write_buf V_MEMRAM2 CCP_Calibration_Write;
V_MEMRAM0 V_MEMRAM1 _c_TBOX_RemCon_buf V_MEMRAM2 TBOX_RemCon;
V_MEMRAM0 V_MEMRAM1 _c_PEPS_Message_Sts_buf V_MEMRAM2 PEPS_Message_Sts;
V_MEMRAM0 V_MEMRAM1 _c_MMI_AC_Command_buf V_MEMRAM2 MMI_AC_Command;
V_MEMRAM0 V_MEMRAM1 _c_AC_Status_Info_buf V_MEMRAM2 AC_Status_Info;
V_MEMRAM0 V_MEMRAM1 _c_EMS_EngineRPM_buf V_MEMRAM2 EMS_EngineRPM;
V_MEMRAM0 V_MEMRAM1 _c_EMS_EngineDriverInfo_buf V_MEMRAM2 EMS_EngineDriverInfo;
V_MEMRAM0 V_MEMRAM1 _c_ESC_Status_buf V_MEMRAM2 ESC_Status;
V_MEMRAM0 V_MEMRAM1 _c_IPK_TotalOdometer_buf V_MEMRAM2 IPK_TotalOdometer;
V_MEMRAM0 V_MEMRAM1 _c_AC_LIN2CANData_buf V_MEMRAM2 AC_LIN2CANData;
V_MEMRAM0 V_MEMRAM1 _c_AC_LIN2CANCom_buf V_MEMRAM2 AC_LIN2CANCom;
V_MEMRAM0 V_MEMRAM1 _c_MMI_HVSM_Command_buf V_MEMRAM2 MMI_HVSM_Command;
V_MEMRAM0 V_MEMRAM1 _c_EMS_EngineStatus_buf V_MEMRAM2 EMS_EngineStatus;
/* PRQA  L:QAC_Can_0759 */

/* RAM CATEGORY 2 END */





/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 286121459
      #error "The magic number of the generated file <D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\CanGenerateCode\drv_par.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\CanGenerateCode\drv_par.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

