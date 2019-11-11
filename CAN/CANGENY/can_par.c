/* -----------------------------------------------------------------------------
  Filename:    can_par.c
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

#define C_DRV_INTERNAL
#include "can_inc.h"
#include "can_par.h"
#include "v_inc.h"

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanTxId0 V_MEMROM2 CanTxId0[kCanNumberOfTxObjects] = 
{
  MK_STDID0(0x7CEu) /* ID: 0x000007ce, Handle: 0, AC_DiagResp [BC] */, 
  MK_STDID0(0x6B3u) /* ID: 0x000006b3, Handle: 1, AC_LIN2CANData [BC] */, 
  MK_STDID0(0x6B2u) /* ID: 0x000006b2, Handle: 2, CCP_Calibration_Read [BC] */, 
  MK_STDID0(0x6B0u) /* ID: 0x000006b0, Handle: 3, AC_LIN2CANCom [BC] */, 
  MK_STDID0(0x406u) /* ID: 0x00000406, Handle: 4, NWM_AC [BC] */, 
  MK_STDID0(0x2F2u) /* ID: 0x000002f2, Handle: 5, AC_Status_Info [FC] */, 
  MK_STDID0(0x2F1u) /* ID: 0x000002f1, Handle: 6, AC_ReqSts [FC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanTxDLC[kCanNumberOfTxObjects] = 
{
  MK_TX_DLC(8) /* ID: 0x000007ce, Handle: 0, AC_DiagResp [BC] */, 
  MK_TX_DLC(8) /* ID: 0x000006b3, Handle: 1, AC_LIN2CANData [BC] */, 
  MK_TX_DLC(8) /* ID: 0x000006b2, Handle: 2, CCP_Calibration_Read [BC] */, 
  MK_TX_DLC(8) /* ID: 0x000006b0, Handle: 3, AC_LIN2CANCom [BC] */, 
  MK_TX_DLC(8) /* ID: 0x00000406, Handle: 4, NWM_AC [BC] */, 
  MK_TX_DLC(8) /* ID: 0x000002f2, Handle: 5, AC_Status_Info [FC] */, 
  MK_TX_DLC(8) /* ID: 0x000002f1, Handle: 6, AC_ReqSts [FC] */
};
/* ROM CATEGORY 1 END */


#ifdef C_ENABLE_COPY_TX_DATA
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 TxDataPtr V_MEMROM2 CanTxDataPtr[kCanNumberOfTxObjects] = 
{
  (TxDataPtr) AC_DiagResp._c /* ID: 0x000007ce, Handle: 0, AC_DiagResp [BC] */, 
  (TxDataPtr) AC_LIN2CANData._c /* ID: 0x000006b3, Handle: 1, AC_LIN2CANData [BC] */, 
  (TxDataPtr) CCP_Calibration_Read._c /* ID: 0x000006b2, Handle: 2, CCP_Calibration_Read [BC] */, 
  (TxDataPtr) AC_LIN2CANCom._c /* ID: 0x000006b0, Handle: 3, AC_LIN2CANCom [BC] */, 
  (TxDataPtr) NWM_AC._c /* ID: 0x00000406, Handle: 4, NWM_AC [BC] */, 
  (TxDataPtr) AC_Status_Info._c /* ID: 0x000002f2, Handle: 5, AC_Status_Info [FC] */, 
  (TxDataPtr) AC_ReqSts._c /* ID: 0x000002f1, Handle: 6, AC_ReqSts [FC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PRETRANSMIT_FCT
/* ROM CATEGORY 1 START */
/* PRQA  S 1334 QAC_Can_1334 */ /* MD_Can_1334 */
V_MEMROM0 V_MEMROM1 ApplPreTransmitFct V_MEMROM2 CanTxApplPreTransmitPtr[kCanNumberOfTxObjects] = 
{
  V_NULL /* ID: 0x000007ce, Handle: 0, AC_DiagResp [BC] */, 
  V_NULL /* ID: 0x000006b3, Handle: 1, AC_LIN2CANData [BC] */, 
  V_NULL /* ID: 0x000006b2, Handle: 2, CCP_Calibration_Read [BC] */, 
  V_NULL /* ID: 0x000006b0, Handle: 3, AC_LIN2CANCom [BC] */, 
  V_NULL /* ID: 0x00000406, Handle: 4, NWM_AC [BC] */, 
  V_NULL /* ID: 0x000002f2, Handle: 5, AC_Status_Info [FC] */, 
  V_NULL /* ID: 0x000002f1, Handle: 6, AC_ReqSts [FC] */
};
/* PRQA  L:QAC_Can_1334 */

/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_CONFIRMATION_FCT
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 ApplConfirmationFct V_MEMROM2 CanTxApplConfirmationPtr[kCanNumberOfTxObjects] = 
{
  TpDrvConfirmation /* ID: 0x000007ce, Handle: 0, AC_DiagResp [BC] */, 
  V_NULL /* ID: 0x000006b3, Handle: 1, AC_LIN2CANData [BC] */, 
  V_NULL /* ID: 0x000006b2, Handle: 2, CCP_Calibration_Read [BC] */, 
  V_NULL /* ID: 0x000006b0, Handle: 3, AC_LIN2CANCom [BC] */, 
  CanNm_NmMsgConfirmation /* ID: 0x00000406, Handle: 4, NWM_AC [BC] */, 
  V_NULL /* ID: 0x000002f2, Handle: 5, AC_Status_Info [FC] */, 
  V_NULL /* ID: 0x000002f1, Handle: 6, AC_ReqSts [FC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PART_OFFLINE
/* ROM CATEGORY 2 START */

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanTxSendMask[kCanNumberOfTxObjects] = 
{
  (vuint8) C_SEND_GRP_DIAG /* ID: 0x000007ce, Handle: 0, AC_DiagResp [BC] */, 
  (vuint8) C_SEND_GRP_APPL /* ID: 0x000006b3, Handle: 1, AC_LIN2CANData [BC] */, 
  (vuint8) C_SEND_GRP_APPL /* ID: 0x000006b2, Handle: 2, CCP_Calibration_Read [BC] */, 
  (vuint8) C_SEND_GRP_APPL /* ID: 0x000006b0, Handle: 3, AC_LIN2CANCom [BC] */, 
  (vuint8) C_SEND_GRP_NM /* ID: 0x00000406, Handle: 4, NWM_AC [BC] */, 
  (vuint8) C_SEND_GRP_APPL /* ID: 0x000002f2, Handle: 5, AC_Status_Info [FC] */, 
  (vuint8) C_SEND_GRP_APPL /* ID: 0x000002f1, Handle: 6, AC_ReqSts [FC] */
};

/* ROM CATEGORY 2 END */

#endif


#ifdef C_ENABLE_CONFIRMATION_FLAG
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanConfirmationOffset[kCanNumberOfTxObjects] = 
{
  0 /* ID: 0x000007ce, Handle: 0, AC_DiagResp [BC] */, 
  0 /* ID: 0x000006b3, Handle: 1, AC_LIN2CANData [BC] */, 
  0 /* ID: 0x000006b2, Handle: 2, CCP_Calibration_Read [BC] */, 
  0 /* ID: 0x000006b0, Handle: 3, AC_LIN2CANCom [BC] */, 
  0 /* ID: 0x00000406, Handle: 4, NWM_AC [BC] */, 
  0 /* ID: 0x000002f2, Handle: 5, AC_Status_Info [FC] */, 
  0 /* ID: 0x000002f1, Handle: 6, AC_ReqSts [FC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanConfirmationMask[kCanNumberOfTxObjects] = 
{
  0x00u /* ID: 0x000007ce, Handle: 0, AC_DiagResp [BC] */, 
  0x01u /* ID: 0x000006b3, Handle: 1, AC_LIN2CANData [BC] */, 
  0x02u /* ID: 0x000006b2, Handle: 2, CCP_Calibration_Read [BC] */, 
  0x04u /* ID: 0x000006b0, Handle: 3, AC_LIN2CANCom [BC] */, 
  0x00u /* ID: 0x00000406, Handle: 4, NWM_AC [BC] */, 
  0x08u /* ID: 0x000002f2, Handle: 5, AC_Status_Info [FC] */, 
  0x10u /* ID: 0x000002f1, Handle: 6, AC_ReqSts [FC] */
};
/* ROM CATEGORY 1 END */


#endif




/* Id table depending on search algorithm */
/* Linear search */
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanRxId0 V_MEMROM2 CanRxId0[kCanNumberOfRxObjects] = 
{
  MK_STDID0(0x7DFu) /* ID: 0x000007df, Handle: 0, Func_DiagReq [BC] */, 
  MK_STDID0(0x7C6u) /* ID: 0x000007c6, Handle: 1, AC_DiagReq [BC] */, 
  MK_STDID0(0x6B1u) /* ID: 0x000006b1, Handle: 2, CCP_Calibration_Write [BC] */, 
  MK_STDID0(0x085u) /* ID: 0x00000085, Handle: 3, EMS_EngineRPM [BC] */, 
  MK_STDID0(0x3F1u) /* ID: 0x000003f1, Handle: 4, IPK_TotalOdometer [FC] */, 
  MK_STDID0(0x2A5u) /* ID: 0x000002a5, Handle: 5, MMI_AC_Command [FC] */, 
  MK_STDID0(0x2A3u) /* ID: 0x000002a3, Handle: 6, MMI_HVSM_Command [FC] */, 
  MK_STDID0(0x292u) /* ID: 0x00000292, Handle: 7, TBOX_RemCon [FC] */, 
  MK_STDID0(0x288u) /* ID: 0x00000288, Handle: 8, EMS_EngineDriverInfo [FC] */, 
  MK_STDID0(0x1E2u) /* ID: 0x000001e2, Handle: 9, PEPS_Message_Sts [FC] */, 
  MK_STDID0(0x125u) /* ID: 0x00000125, Handle: 10, ESC_Status [FC] */, 
  MK_STDID0(0x086u) /* ID: 0x00000086, Handle: 11, EMS_EngineStatus [FC] */
};
/* ROM CATEGORY 1 END */



/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanRxDataLen[kCanNumberOfRxObjects] = 
{
  8 /* ID: 0x000007df, Handle: 0, Func_DiagReq [BC] */, 
  8 /* ID: 0x000007c6, Handle: 1, AC_DiagReq [BC] */, 
  8 /* ID: 0x000006b1, Handle: 2, CCP_Calibration_Write [BC] */, 
  6 /* ID: 0x00000085, Handle: 3, EMS_EngineRPM [BC] */, 
  3 /* ID: 0x000003f1, Handle: 4, IPK_TotalOdometer [FC] */, 
  6 /* ID: 0x000002a5, Handle: 5, MMI_AC_Command [FC] */, 
  1 /* ID: 0x000002a3, Handle: 6, MMI_HVSM_Command [FC] */, 
  4 /* ID: 0x00000292, Handle: 7, TBOX_RemCon [FC] */, 
  2 /* ID: 0x00000288, Handle: 8, EMS_EngineDriverInfo [FC] */, 
  1 /* ID: 0x000001e2, Handle: 9, PEPS_Message_Sts [FC] */, 
  3 /* ID: 0x00000125, Handle: 10, ESC_Status [FC] */, 
  7 /* ID: 0x00000086, Handle: 11, EMS_EngineStatus [FC] */
};
/* ROM CATEGORY 1 END */


#ifdef C_ENABLE_COPY_RX_DATA
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 RxDataPtr V_MEMROM2 CanRxDataPtr[kCanNumberOfRxObjects] = 
{
  (RxDataPtr) Func_DiagReq._c /* ID: 0x000007df, Handle: 0, Func_DiagReq [BC] */, 
  (RxDataPtr) AC_DiagReq._c /* ID: 0x000007c6, Handle: 1, AC_DiagReq [BC] */, 
  (RxDataPtr) CCP_Calibration_Write._c /* ID: 0x000006b1, Handle: 2, CCP_Calibration_Write [BC] */, 
  (RxDataPtr) EMS_EngineRPM._c /* ID: 0x00000085, Handle: 3, EMS_EngineRPM [BC] */, 
  (RxDataPtr) IPK_TotalOdometer._c /* ID: 0x000003f1, Handle: 4, IPK_TotalOdometer [FC] */, 
  (RxDataPtr) MMI_AC_Command._c /* ID: 0x000002a5, Handle: 5, MMI_AC_Command [FC] */, 
  (RxDataPtr) MMI_HVSM_Command._c /* ID: 0x000002a3, Handle: 6, MMI_HVSM_Command [FC] */, 
  (RxDataPtr) TBOX_RemCon._c /* ID: 0x00000292, Handle: 7, TBOX_RemCon [FC] */, 
  (RxDataPtr) EMS_EngineDriverInfo._c /* ID: 0x00000288, Handle: 8, EMS_EngineDriverInfo [FC] */, 
  (RxDataPtr) PEPS_Message_Sts._c /* ID: 0x000001e2, Handle: 9, PEPS_Message_Sts [FC] */, 
  (RxDataPtr) ESC_Status._c /* ID: 0x00000125, Handle: 10, ESC_Status [FC] */, 
  (RxDataPtr) EMS_EngineStatus._c /* ID: 0x00000086, Handle: 11, EMS_EngineStatus [FC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PRECOPY_FCT
/* CODE CATEGORY 1 START */
/* CODE CATEGORY 1 END */

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 ApplPrecopyFct V_MEMROM2 CanRxApplPrecopyPtr[kCanNumberOfRxObjects] = 
{
  TpFuncPrecopy /* ID: 0x000007df, Handle: 0, Func_DiagReq [BC] */, 
  TpPrecopy /* ID: 0x000007c6, Handle: 1, AC_DiagReq [BC] */, 
  V_NULL /* ID: 0x000006b1, Handle: 2, CCP_Calibration_Write [BC] */, 
  V_NULL /* ID: 0x00000085, Handle: 3, EMS_EngineRPM [BC] */, 
  V_NULL /* ID: 0x000003f1, Handle: 4, IPK_TotalOdometer [FC] */, 
  V_NULL /* ID: 0x000002a5, Handle: 5, MMI_AC_Command [FC] */, 
  V_NULL /* ID: 0x000002a3, Handle: 6, MMI_HVSM_Command [FC] */, 
  V_NULL /* ID: 0x00000292, Handle: 7, TBOX_RemCon [FC] */, 
  V_NULL /* ID: 0x00000288, Handle: 8, EMS_EngineDriverInfo [FC] */, 
  V_NULL /* ID: 0x000001e2, Handle: 9, PEPS_Message_Sts [FC] */, 
  V_NULL /* ID: 0x00000125, Handle: 10, ESC_Status [FC] */, 
  V_NULL /* ID: 0x00000086, Handle: 11, EMS_EngineStatus [FC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_INDICATION_FCT
/* ROM CATEGORY 1 START */
/* PRQA  S 1334 QAC_Can_1334 */ /* MD_Can_1334 */
V_MEMROM0 V_MEMROM1 ApplIndicationFct V_MEMROM2 CanRxApplIndicationPtr[kCanNumberOfRxObjects] = 
{
  V_NULL /* ID: 0x000007df, Handle: 0, Func_DiagReq [BC] */, 
  V_NULL /* ID: 0x000007c6, Handle: 1, AC_DiagReq [BC] */, 
  V_NULL /* ID: 0x000006b1, Handle: 2, CCP_Calibration_Write [BC] */, 
  V_NULL /* ID: 0x00000085, Handle: 3, EMS_EngineRPM [BC] */, 
  V_NULL /* ID: 0x000003f1, Handle: 4, IPK_TotalOdometer [FC] */, 
  V_NULL /* ID: 0x000002a5, Handle: 5, MMI_AC_Command [FC] */, 
  V_NULL /* ID: 0x000002a3, Handle: 6, MMI_HVSM_Command [FC] */, 
  V_NULL /* ID: 0x00000292, Handle: 7, TBOX_RemCon [FC] */, 
  V_NULL /* ID: 0x00000288, Handle: 8, EMS_EngineDriverInfo [FC] */, 
  V_NULL /* ID: 0x000001e2, Handle: 9, PEPS_Message_Sts [FC] */, 
  V_NULL /* ID: 0x00000125, Handle: 10, ESC_Status [FC] */, 
  V_NULL /* ID: 0x00000086, Handle: 11, EMS_EngineStatus [FC] */
};
/* PRQA  L:QAC_Can_1334 */

/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_INDICATION_FLAG
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanIndicationOffset[kCanNumberOfRxObjects] = 
{
  0 /* ID: 0x000007df, Handle: 0, Func_DiagReq [BC] */, 
  0 /* ID: 0x000007c6, Handle: 1, AC_DiagReq [BC] */, 
  0 /* ID: 0x000006b1, Handle: 2, CCP_Calibration_Write [BC] */, 
  0 /* ID: 0x00000085, Handle: 3, EMS_EngineRPM [BC] */, 
  0 /* ID: 0x000003f1, Handle: 4, IPK_TotalOdometer [FC] */, 
  0 /* ID: 0x000002a5, Handle: 5, MMI_AC_Command [FC] */, 
  0 /* ID: 0x000002a3, Handle: 6, MMI_HVSM_Command [FC] */, 
  0 /* ID: 0x00000292, Handle: 7, TBOX_RemCon [FC] */, 
  0 /* ID: 0x00000288, Handle: 8, EMS_EngineDriverInfo [FC] */, 
  0 /* ID: 0x000001e2, Handle: 9, PEPS_Message_Sts [FC] */, 
  1 /* ID: 0x00000125, Handle: 10, ESC_Status [FC] */, 
  1 /* ID: 0x00000086, Handle: 11, EMS_EngineStatus [FC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanIndicationMask[kCanNumberOfRxObjects] = 
{
  0x00u /* ID: 0x000007df, Handle: 0, Func_DiagReq [BC] */, 
  0x00u /* ID: 0x000007c6, Handle: 1, AC_DiagReq [BC] */, 
  0x01u /* ID: 0x000006b1, Handle: 2, CCP_Calibration_Write [BC] */, 
  0x02u /* ID: 0x00000085, Handle: 3, EMS_EngineRPM [BC] */, 
  0x04u /* ID: 0x000003f1, Handle: 4, IPK_TotalOdometer [FC] */, 
  0x08u /* ID: 0x000002a5, Handle: 5, MMI_AC_Command [FC] */, 
  0x10u /* ID: 0x000002a3, Handle: 6, MMI_HVSM_Command [FC] */, 
  0x20u /* ID: 0x00000292, Handle: 7, TBOX_RemCon [FC] */, 
  0x40u /* ID: 0x00000288, Handle: 8, EMS_EngineDriverInfo [FC] */, 
  0x80u /* ID: 0x000001e2, Handle: 9, PEPS_Message_Sts [FC] */, 
  0x01u /* ID: 0x00000125, Handle: 10, ESC_Status [FC] */, 
  0x02u /* ID: 0x00000086, Handle: 11, EMS_EngineStatus [FC] */
};
/* ROM CATEGORY 1 END */


#endif




/* -----------------------------------------------------------------------------
    &&&~ Init structures
 ----------------------------------------------------------------------------- */

/* ROM CATEGORY 4 START */
/* PRQA S 3408 1 */ /* MD_Can_3408_extLinkage */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanInitObjectStartIndex[2] = 
{
  0, 
  1
};

/* ROM CATEGORY 4 END */

/* ROM CATEGORY 4 START */
V_MEMROM0 V_MEMROM1 tCanFilterRulesBc V_MEMROM2 CanFilterRulesBc_0[2] = 
{
  
  {
    0x0085u, 
    0x07FFu
  }, 
  
  {
    0x0400u, 
    0x0400u
  }
};
V_MEMROM0 V_MEMROM1 vuint32 V_MEMROM2 CanInitBCFG[1] = 
{
  0x022B0001u
};
/* ROM CATEGORY 4 END */



#if defined(C_ENABLE_MULTI_ECU_CONFIG)
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanPhysToLogChannel[kVNumberOfIdentities][kCanNumberOfPhysChannels] = 
{
  
  {
    kCanChannelNotUsed, 
    kCanChannelNotUsed, 
    0
  }
};
/* ROM CATEGORY 1 END */

#endif

#if defined(C_ENABLE_MULTI_ECU_CONFIG)
/* ROM CATEGORY 2 START */

V_MEMROM0 V_MEMROM1 tVIdentityMsk V_MEMROM2 CanChannelIdentityAssignment[kCanNumberOfChannels] = 
{
  0x01u
};

/* ROM CATEGORY 2 END */

#endif

#if defined(C_ENABLE_MULTI_ECU_PHYS)
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tVIdentityMsk V_MEMROM2 CanRxIdentityAssignment[kCanNumberOfRxObjects] = 
{
  0x01u /* ID: 0x000007df, Handle: 0, Func_DiagReq [BC] */, 
  0x01u /* ID: 0x000007c6, Handle: 1, AC_DiagReq [BC] */, 
  0x01u /* ID: 0x000006b1, Handle: 2, CCP_Calibration_Write [BC] */, 
  0x01u /* ID: 0x00000085, Handle: 3, EMS_EngineRPM [BC] */, 
  0x01u /* ID: 0x000003f1, Handle: 4, IPK_TotalOdometer [FC] */, 
  0x01u /* ID: 0x000002a5, Handle: 5, MMI_AC_Command [FC] */, 
  0x01u /* ID: 0x000002a3, Handle: 6, MMI_HVSM_Command [FC] */, 
  0x01u /* ID: 0x00000292, Handle: 7, TBOX_RemCon [FC] */, 
  0x01u /* ID: 0x00000288, Handle: 8, EMS_EngineDriverInfo [FC] */, 
  0x01u /* ID: 0x000001e2, Handle: 9, PEPS_Message_Sts [FC] */, 
  0x01u /* ID: 0x00000125, Handle: 10, ESC_Status [FC] */, 
  0x01u /* ID: 0x00000086, Handle: 11, EMS_EngineStatus [FC] */
};
/* ROM CATEGORY 1 END */

/* ROM CATEGORY 4 START */
V_MEMROM0 V_MEMROM1 tVIdentityMsk V_MEMROM2 CanTxIdentityAssignment[kCanNumberOfTxObjects] = 
{
  0x01u /* ID: 0x000007ce, Handle: 0, AC_DiagResp [BC] */, 
  0x01u /* ID: 0x000006b3, Handle: 1, AC_LIN2CANData [BC] */, 
  0x01u /* ID: 0x000006b2, Handle: 2, CCP_Calibration_Read [BC] */, 
  0x01u /* ID: 0x000006b0, Handle: 3, AC_LIN2CANCom [BC] */, 
  0x01u /* ID: 0x00000406, Handle: 4, NWM_AC [BC] */, 
  0x01u /* ID: 0x000002f2, Handle: 5, AC_Status_Info [FC] */, 
  0x01u /* ID: 0x000002f1, Handle: 6, AC_ReqSts [FC] */
};
/* ROM CATEGORY 4 END */

#endif


/* -----------------------------------------------------------------------------
    &&&~ Multiple Callback Functions
 ----------------------------------------------------------------------------- */

/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 WrapperApplCanTxConfirmation(CanTxInfoStructPtr txStruct)
{
  ApplCanTxConfirmation(txStruct);
  CbdWrpCanTxConfirmation(txStruct);
}


/* CODE CATEGORY 1 END */


#ifdef C_ENABLE_TX_FULLCAN_OBJECTS
/* ROM CATEGORY 2 START */
#ifdef C_ENABLE_HW_OBJ_EXCEED_255_DRV
V_MEMROM0 V_MEMROM1 CanObjectHandle V_MEMROM2 CanTxHwObj[kCanNumberOfTxObjects] = 
{
  0xC0 /* ID: 0x000007ce, Handle: 0, AC_DiagResp [BC] */, 
  0xC0 /* ID: 0x000006b3, Handle: 1, AC_LIN2CANData [BC] */, 
  0xC0 /* ID: 0x000006b2, Handle: 2, CCP_Calibration_Read [BC] */, 
  0xC0 /* ID: 0x000006b0, Handle: 3, AC_LIN2CANCom [BC] */, 
  0xC0 /* ID: 0x00000406, Handle: 4, NWM_AC [BC] */, 
  0xC2 /* ID: 0x000002f2, Handle: 5, AC_Status_Info [FC] */, 
  0xC1 /* ID: 0x000002f1, Handle: 6, AC_ReqSts [FC] */
};
#else
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanTxHwObj[kCanNumberOfTxObjects] = 
{
  0xC0 /* ID: 0x000007ce, Handle: 0, AC_DiagResp [BC] */, 
  0xC0 /* ID: 0x000006b3, Handle: 1, AC_LIN2CANData [BC] */, 
  0xC0 /* ID: 0x000006b2, Handle: 2, CCP_Calibration_Read [BC] */, 
  0xC0 /* ID: 0x000006b0, Handle: 3, AC_LIN2CANCom [BC] */, 
  0xC0 /* ID: 0x00000406, Handle: 4, NWM_AC [BC] */, 
  0xC2 /* ID: 0x000002f2, Handle: 5, AC_Status_Info [FC] */, 
  0xC1 /* ID: 0x000002f1, Handle: 6, AC_ReqSts [FC] */
};
#endif

/* ROM CATEGORY 2 END */

#endif



/* -----------------------------------------------------------------------------
    &&&~ Hw specific
 ----------------------------------------------------------------------------- */

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanChannelData V_MEMROM2 CanChannelData[kCanNumberOfHwChannels] = 
{
  
  {
    CanRxFifoDepth_0 /* CanRxFifoDepth */, 
    CanFilterRulesBc_0 /* CanFilterRulesBc */, 
    0xFFFFA1A6u /* CanIntcChTxBaseAdr */, 
    0xFFFFA1A2u /* CanIntcChErrorBaseAdr */, 
    0xFFFF903Eu /* CanIntcChWakeupBaseAdr */, 
    { 0x0000FFFFu, 0x00000000u } /* CanRxFcMask */, 
    0x007Fu /* CanTxIntMask */, 
    0u /* CanFilterRulesStartIndex */, 
    0x12u /* CanFilterRulesTotalCount */, 
    2u /* CanFilterRulesBcCount */, 
    0x01u /* CanRxBcMask */, 
    0x08u /* CanRxBcMsgProcessCount */, 
    0u /* CanRxBcStartIndex */, 
    1u /* CanRxBcStopIndex */, 
    3u /* CanIntPrio */
  }
};
/* ROM CATEGORY 1 END */

/* ROM CATEGORY 1 START */
/* ROM CATEGORY 1 END */

/* ROM CATEGORY 4 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanRxFifoDepth_0[1] = 
{
  0x01u
};
/* ROM CATEGORY 4 END */





/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 286121459
      #error "The magic number of the generated file <D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\CanGenerateCode\can_par.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\CanGenerateCode\can_par.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

