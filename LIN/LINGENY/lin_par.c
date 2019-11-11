/* -----------------------------------------------------------------------------
  Filename:    lin_par.c
  Description: Toolversion: 00.00.00.01.40.05.50.00.00.00
               
               Serial Number: CBD1400550
               Customer Info: Desay SV Automotive Co., Ltd.
                              Package: LIN_SLP2 - CBD LIN 2.0 license
                              Micro: PD78F1828A
                              Compiler: IAR 4.71.1.50113
               
               
               Generator Fwk   : GENy 
               Generator Module: DrvLin__base
               
               Configuration   : D:\uidq0188\Desktop\New folder\GE12_LIN(Slave).gny
               
               ECU: 
                       TargetSystem: Hw_78k0rCpu
                       Compiler:     IAR
                       Derivates:    Fx3
               
               Channel "Channel1":
                       Databasefile: D:\HVACproject\GEELY\GE12\ÎÄµµ\LIN ±ä¸ü\20170705\GE12_LIN_V1.31_20170625\GE12_LIN_V1.31_20170624.ldf
                       Bussystem:    LIN
                       Node:         FCP

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2014 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#include "v_inc.h"
#include "lin_cfg.h"
#include "drv_par.h"
#include "lin_par_i.h"
#include "lin_par.h"
#include "sio_cfg.h"
#include "sio_drv.h"
/* -----------------------------------------------------------------------------
    &&&~ MISRA definitions
 ----------------------------------------------------------------------------- */

/* PRQA S 759 EOF *//* MD_CBD_18.4 */
/* PRQA S 3453 EOF *//* MD_CBD_19.7 */


/* -----------------------------------------------------------------------------
    &&&~ Configurable NAD
 ----------------------------------------------------------------------------- */

V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 bLinConfiguredNAD;


/* -----------------------------------------------------------------------------
    &&&~ Response max times for each data length in tics of LinfastTimerTask()
 ----------------------------------------------------------------------------- */

#if defined(LIN_ENABLE_T_FRAME_MAX)
V_MEMROM0 V_MEMROM1 tLinFpTimerType V_MEMROM2 cabFpResponseMaxTimes[9] = { 2, 3, 4, 5, 6, 7, 7, 8, 9 };

#endif



/* -----------------------------------------------------------------------------
    &&&~ List of Ids for all messages
 ----------------------------------------------------------------------------- */

V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 cabLinSlaveProtectedIdTbl[kLinNumberOfConfigurablePIDs];
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cabLinSlaveProtectedIdInitTbl[kLinNumberOfConfigurablePIDs] = 
{
  0xC1 /* ID: 0x01, Handle: 0, Name: AC_1 */, 
  0x11 /* ID: 0x11, Handle: 1, Name: FCP_1 */, 
  0x03 /* ID: 0x03, Handle: 2, Name: FCP_2 */
};
V_MEMROM0 V_MEMROM1 tMessageInfoType V_MEMROM2 cabLinRxTxMsgInfo[kLinNumberOfMsgInfoObjects] = 
{
  { kChecksumEnhanced, 0, kMessageDirectionRx, 8 } /* ID: 0x01, Handle: 0, Name: AC_1 */, 
  { kChecksumEnhanced, 0, kMessageDirectionTx, 8 } /* ID: 0x11, Handle: 1, Name: FCP_1 */, 
  { kChecksumEnhanced, 0, kMessageDirectionTx, 8 } /* ID: 0x03, Handle: 2, Name: FCP_2 */, 
  { kChecksumClassic, 0, kMessageDirectionRx, 8 } /* ID: 0x3c, Handle: 3, Name: MasterReq */, 
  { kChecksumClassic, 0, kMessageDirectionTx, 8 } /* ID: 0x3d, Handle: 4, Name: SlaveResp */
};




/* -----------------------------------------------------------------------------
    &&&~ Tables for send and receive messages
 ----------------------------------------------------------------------------- */

V_MEMROM0 V_MEMROM1 tLinMsgDataPtrType V_MEMROM2 capbLinRxTxMsgDataPtr[kLinNumberOfRxTxObjects] = 
{
  (tLinMsgDataPtrType) AC_1._c /* ID: 0x01, Handle: 0, Name: AC_1 */, 
  (tLinMsgDataPtrType) FCP_1._c /* ID: 0x11, Handle: 1, Name: FCP_1 */, 
  (tLinMsgDataPtrType) FCP_2._c /* ID: 0x03, Handle: 2, Name: FCP_2 */
};



/* -----------------------------------------------------------------------------
    &&&~ Precopy Functions of Rx Messages
 ----------------------------------------------------------------------------- */

#if defined(LIN_ENABLE_MSG_PRECOPY_FCT) || defined(LIN_ENABLE_DIAGMSG_PRECOPY_FCT)
#endif

#ifdef LIN_ENABLE_MSG_PRECOPY_FCT
V_MEMROM0 V_MEMROM1 tApplLinMsgPrecopyFct V_MEMROM2 capfLinRxApplMsgPrecopyFctTbl[kLinNumberOfRxObjects] = 
{
  V_NULL /* ID: 0x01, Handle: 0, Name: AC_1 */
};

#endif

#ifdef LIN_ENABLE_DIAGMSG_PRECOPY_FCT
V_MEMROM0 V_MEMROM1 tApplLinMsgPrecopyFct V_MEMROM2 capfLinRxDiagMsgPrecopyFctTbl[kLinNumberOfDiagRxObjects] = 
{
  V_NULL /* ID: 0x3c, Handle: 3, Name: MasterReq */
};

#endif



/* -----------------------------------------------------------------------------
    &&&~ Pretransmit Functions of Tx messages
 ----------------------------------------------------------------------------- */

#if defined(LIN_ENABLE_MSG_PRETRANSMIT_FCT) || defined(LIN_ENABLE_DIAGMSG_PRETRANSMIT_FCT)
#endif

#ifdef LIN_ENABLE_MSG_PRETRANSMIT_FCT
V_MEMROM0 V_MEMROM1 tApplLinMsgPretransmitFct V_MEMROM2 capfLinTxApplMsgPretransmitFctTbl[kLinNumberOfTxObjects] = 
{
  Panel_info_FCP_1 /* ID: 0x11, Handle: 1, Name: FCP_1 */, 
  Panel_info_FCP_2 /* ID: 0x03, Handle: 2, Name: FCP_2 */
};

#endif

#ifdef LIN_ENABLE_DIAGMSG_PRETRANSMIT_FCT
V_MEMROM0 V_MEMROM1 tApplLinMsgPretransmitFct V_MEMROM2 capfLinTxDiagMsgPretransmitFctTbl[kLinNumberOfDiagTxObjects] = 
{
  V_NULL /* ID: 0x3d, Handle: 4, Name: SlaveResp */
};

#endif



/* -----------------------------------------------------------------------------
    &&&~ Indication Flags of Rx messages
 ----------------------------------------------------------------------------- */

#if defined(LIN_ENABLE_MSG_INDICATION_FLAG) || defined(LIN_ENABLE_DIAGMSG_INDICATION_FLAG)
V_MEMRAM0 V_MEMRAM1_NEAR tLinMsgIndicationBits V_MEMRAM2_NEAR uLinMsgIndicationFlags;

#endif

#if defined(LIN_ENABLE_MSG_INDICATION_FLAG) || defined(LIN_ENABLE_DIAGMSG_INDICATION_FLAG) || defined(LIN_ENABLE_INTMSG_INDICATION_FLAG)
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cabLinMsgIndicationOffset[kLinNumberOfRxObjects+kLinNumberOfDiagRxObjects] = 
{
  0 /* ID: 0x01, Handle: 0, Name: AC_1 */, 
  0 /* ID: 0x3c, Handle: 3, Name: MasterReq */
};


V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cabLinMsgIndicationMask[kLinNumberOfRxObjects+kLinNumberOfDiagRxObjects] = 
{
  0x01 /* ID: 0x01, Handle: 0, Name: AC_1 */, 
  0x02 /* ID: 0x3c, Handle: 3, Name: MasterReq */
};


#endif



/* -----------------------------------------------------------------------------
    &&&~ Confirmation Flags of Tx messages
 ----------------------------------------------------------------------------- */

#if defined(LIN_ENABLE_MSG_CONFIRMATION_FLAG) || defined(LIN_ENABLE_DIAGMSG_CONFIRMATION_FLAG)
V_MEMRAM0 V_MEMRAM1_NEAR tLinMsgConfirmationBits V_MEMRAM2_NEAR uLinMsgConfirmationFlags;

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cabLinMsgConfirmationOffset[kLinNumberOfTxObjects+kLinNumberOfDiagTxObjects] = 
{
  0 /* ID: 0x11, Handle: 1, Name: FCP_1 */, 
  0 /* ID: 0x03, Handle: 2, Name: FCP_2 */, 
  0 /* ID: 0x3d, Handle: 4, Name: SlaveResp */
};


V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 cabLinMsgConfirmationMask[kLinNumberOfTxObjects+kLinNumberOfDiagTxObjects] = 
{
  0x01 /* ID: 0x11, Handle: 1, Name: FCP_1 */, 
  0x02 /* ID: 0x03, Handle: 2, Name: FCP_2 */, 
  0x04 /* ID: 0x3d, Handle: 4, Name: SlaveResp */
};


#endif



/* -----------------------------------------------------------------------------
    &&&~ Indication Functions of Rx messages
 ----------------------------------------------------------------------------- */

#if defined(LIN_ENABLE_MSG_INDICATION_FCT) || defined(LIN_ENABLE_DIAGMSG_INDICATION_FCT)
#endif

#ifdef LIN_ENABLE_MSG_INDICATION_FCT
V_MEMROM0 V_MEMROM1 tApplLinMsgIndicationFct V_MEMROM2 capfLinRxApplMsgIndicationFctTbl[kLinNumberOfRxObjects] = 
{
  V_NULL /* ID: 0x01, Handle: 0, Name: AC_1 */
};

#endif

#ifdef LIN_ENABLE_DIAGMSG_INDICATION_FCT
V_MEMROM0 V_MEMROM1 tApplLinMsgIndicationFct V_MEMROM2 capfLinRxDiagMsgIndicationFctTbl[kLinNumberOfDiagRxObjects] = 
{
  V_NULL /* ID: 0x3c, Handle: 3, Name: MasterReq */
};

#endif



/* -----------------------------------------------------------------------------
    &&&~ Confirmation Functions of Tx messages
 ----------------------------------------------------------------------------- */

#if defined(LIN_ENABLE_MSG_CONFIRMATION_FCT) || defined(LIN_ENABLE_DIAGMSG_CONFIRMATION_FCT)
#endif

#ifdef LIN_ENABLE_MSG_CONFIRMATION_FCT
V_MEMROM0 V_MEMROM1 tApplLinMsgConfirmationFct V_MEMROM2 capfLinTxApplMsgConfirmationFctTbl[kLinNumberOfTxObjects] = 
{
  V_NULL /* ID: 0x11, Handle: 1, Name: FCP_1 */, 
  V_NULL /* ID: 0x03, Handle: 2, Name: FCP_2 */
};

#endif

#ifdef LIN_ENABLE_DIAGMSG_CONFIRMATION_FCT
V_MEMROM0 V_MEMROM1 tApplLinMsgConfirmationFct V_MEMROM2 capfLinTxDiagMsgConfirmationFctTbl[kLinNumberOfDiagTxObjects] = 
{
  V_NULL /* ID: 0x3d, Handle: 4, Name: SlaveResp */
};

#endif



/* -----------------------------------------------------------------------------
    &&&~ Default values for Frames
 ----------------------------------------------------------------------------- */

#if defined(LIN_ENABLE_INIT_TX_DEFAULT_DATA) || defined(LIN_ENABLE_START_TX_DEFAULT_DATA) || defined(LIN_ENABLE_STOP_TX_DEFAULT_DATA) || defined(LIN_ENABLE_INIT_RX_DEFAULT_DATA) || defined(LIN_ENABLE_START_RX_DEFAULT_DATA) || defined(LIN_ENABLE_STOP_RX_DEFAULT_DATA)
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 LinMsgDefault_AC_1[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00 };

V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 LinMsgDefault_FCP_1[8] = { 0x00, 0x00, 0x00, 0x02, 0x38, 0xF0, 0xFF, 0xFF };

V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 LinMsgDefault_FCP_2[8] = { 0x14, 0x50, 0x40, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF };

#endif

#if defined(LIN_ENABLE_INIT_TX_DEFAULT_DATA) || defined(LIN_ENABLE_START_TX_DEFAULT_DATA) || defined(LIN_ENABLE_STOP_TX_DEFAULT_DATA) || defined(LIN_ENABLE_INIT_RX_DEFAULT_DATA) || defined(LIN_ENABLE_START_RX_DEFAULT_DATA) || defined(LIN_ENABLE_STOP_RX_DEFAULT_DATA)
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3* V_MEMROM1 V_MEMROM2 capbLinRxTxDefaultDataPtrTbl[kLinNumberOfRxTxObjects] = 
{
  LinMsgDefault_AC_1 /* ID: 0x01, Handle: 0, Name: AC_1 */, 
  LinMsgDefault_FCP_1 /* ID: 0x11, Handle: 1, Name: FCP_1 */, 
  LinMsgDefault_FCP_2 /* ID: 0x03, Handle: 2, Name: FCP_2 */
};

#endif



/* -----------------------------------------------------------------------------
    &&&~ Pointer to Diagnostic Message Buffers
 ----------------------------------------------------------------------------- */

V_MEMROM0 V_MEMROM1 tLinMsgDataPtrType V_MEMROM2 pbLinMasterReqMsgDataPtr = (tLinMsgDataPtrType) MasterReq._c;

V_MEMROM0 V_MEMROM1 tLinMsgDataPtrType V_MEMROM2 pbLinSlaveRespMsgDataPtr = (tLinMsgDataPtrType) SlaveResp._c;



/* -----------------------------------------------------------------------------
    &&&~ ConfigurablePID Handle Table
 ----------------------------------------------------------------------------- */

V_MEMROM0 V_MEMROM1 tLinFrameHandleType V_MEMROM2 cabConfigurablePIDHandleTbl[kLinNumberOfConfigurablePIDs] = 
{
  1 /* ID: 0x11, Handle: 1, Name: FCP_1 */, 
  2 /* ID: 0x03, Handle: 2, Name: FCP_2 */, 
  0 /* ID: 0x01, Handle: 0, Name: AC_1 */
};



/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 258965458
      #error "The magic number of the generated file <D:\uidq0188\Desktop\New folder\lin_par.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <D:\uidq0188\Desktop\New folder\lin_par.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

