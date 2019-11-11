/* -----------------------------------------------------------------------------
  Filename:    lin_par_i.h
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

#if !defined(__LIN_PAR_I_H__)
#define __LIN_PAR_I_H__

/* -----------------------------------------------------------------------------
    &&&~ MISRA definitions
 ----------------------------------------------------------------------------- */

/* PRQA S 750 EOF *//* MD_CBD_18.4 */
/* PRQA S 759 EOF *//* MD_CBD_18.4 */
/* PRQA S 635 EOF *//* MD_LIN_DRV_6.4 */
/* PRQA S 3453 EOF *//* MD_CBD_19.7 */


/* -----------------------------------------------------------------------------
    &&&~ Type definitions of objects used in lin_par.c
 ----------------------------------------------------------------------------- */

/* general data types */
typedef vuint8 tLinFrameHandleType;
typedef vuintx tLinFrameHandleLoopType;
typedef vuint8 tLinFrameDistanceType;
typedef struct tLinSchedTblEntryTypeTag
{
  tLinFrameHandleType vFrameHandle;
  tLinFrameDistanceType vFrameDistance;
} tLinSchedTblEntryType;
typedef V_MEMROM1 tLinSchedTblEntryType V_MEMROM2 V_MEMROM3*  tLinSchedTblEntryPtrType;
typedef V_MEMROM1 tLinSchedTblEntryPtrType V_MEMROM2 V_MEMROM3*  tLinChannelsSchedTblEntryPtr;
/* Data types used by message buffers */
typedef vuint8* tLinMsgDataPtrType;
typedef struct tMessageInfoTypeTag
{
  vbittype MsgChecksumType : 1;
  vbittype MsgReserved : 1;
  vbittype MsgDirection : 2;
  vbittype MsgDataLength : 4;
} tMessageInfoType;
#define kChecksumClassic                     0
#define kChecksumEnhanced                    1
#define kMessageDirectionRx                  1
#define kMessageDirectionTx                  2
#define kMessageDirectionIgnore              3
#define kLinInvalidHandle                    0xFFU
typedef vuint8 tLinNmWupTimerType;
typedef vuint8 tLinNmNoWupDelayTimerType;
typedef vuint8 tLinNmBusIdleTimerType;
typedef vuint8 tLinFpTimerType;


/* -----------------------------------------------------------------------------
    &&&~ Number of defines
 ----------------------------------------------------------------------------- */

#define kLinNumberOfChannels                 1
#define kLinNumberOfEtTxObjects              0
#define kLinNumberOfSporSlots                0
#define kLinNumberOfUncondSporFrame          0
#define kLinNumberOfRxObjects                1
#define kLinNumberOfDiagRxObjects            1
#define kLinNumberOfTxObjects                2
#define kLinNumberOfIdObjects                (kLinNumberOfRxTxObjects + kLinNumberOfEtObjects)
#define kLinNumberOfRxTxObjects              (kLinNumberOfRxObjects + kLinNumberOfTxObjects)
#define kLinNumberOfEtRxObjects              0
#define kLinNumberOfEtObjects                (kLinNumberOfEtRxObjects + kLinNumberOfEtTxObjects)
#define kLinNumberOfConfigurablePIDs         3
#define kLinNumberOfDiagObjects              2
#define kLinNumberOfDiagTxObjects            1
#define kLinNumberOfMsgInfoObjects           (kLinNumberOfIdObjects + kLinNumberOfDiagObjects)
#define kLinNumberOfNoObjects                0
#define kLinNumberOfObjects                  (kLinNumberOfMsgInfoObjects + kLinNumberOfNoObjects)
#define kLinNumberOfConfigCmd                0
#define kLinNumberOfFrameObjects             (kLinNumberOfObjects + kLinNumberOfConfigCmd)
#define kLinNumberOfSlotHandles              (kLinNumberOfObjects + kLinNumberOfConfigCmd + kLinNumberOfSporSlots)
#define kLinSleepCmdHandle                   kLinNumberOfSlotHandles
#define kLinWakeupHandle                     (kLinNumberOfSlotHandles + 1)
#define getkLinNumberOfChTxObjects(c)        kLinNumberOfTxObjects
#define getkLinNumberOfChRxObjects(c)        kLinNumberOfRxObjects
#define getkLinNumberOfChTxRxNoObjects(c)    kLinNumberOfTxRxNoObjects
#define getkLinNumberOfChEtObjects(c)        kLinNumberOfEtObjects
#define getkLinNumberOfChSporSlots(c)        kLinNumberOfSporSlots
#define getkLinNumberOfChConfigCmd(c)        kLinNumberOfConfigCmd
#define kNmWupTimerStartValue                151
#define kNmNoWupDelayValue                   76
#define kNmBusIdleTimeoutValue               201
#define kLinNumberOfScheduleTables           4
#define kFpWakeupPattern                     0xF0U
#define kLinNumberOfConfFlags                3
#define kLinNumberOfIndFlags                 2
#define kLinNumberOfIntIndFlags              2
#define get_SlaveRespHandle(c)               4
#define get_MasterReqHandle(c)               3
#define kLinNumberOfSigConfFlags             0
#define kLinNumberOfSigIndFlags              0
#define get_LinNumberOfRxObjects(c)          kLinNumberOfRxObjects
#define get_LinNumberOfTxObjects(c)          kLinNumberOfTxObjects
#define get_LinNumberOfRxTxObjects(c)        kLinNumberOfRxTxObjects
#define get_LinNumberOfEtRxObjects(c)        kLinNumberOfEtRxObjects
#define get_LinNumberOfEtTxObjects(c)        kLinNumberOfEtTxObjects
#define get_LinNumberOfEtObjects(c)          kLinNumberOfEtObjects
#define get_LinNumberOfIdObjects(c)          kLinNumberOfIdObjects
#define get_LinNumberOfDiagRxObjects(c)      kLinNumberOfDiagRxObjects
#define get_LinNumberOfMsgInfoObjects(c)     kLinNumberOfMsgInfoObjects
#define get_LinNumberOfChTxObjects(c)        kLinNumberOfTxObjects
#define get_LinNumberOfChRxObjects(c)        kLinNumberOfRxObjects
#define get_LinNumberOfConfFlags(c)          kLinNumberOfConfFlags
#define get_LinNumberOfIndFlags(c)           kLinNumberOfIndFlags
#if defined(LIN_ENABLE_MSG_INDICATION_FLAG) || defined(LIN_ENABLE_DIAGMSG_INDICATION_FLAG)
#define get_LinMsgIndicationFlags(c)         uLinMsgIndicationFlags
#endif

#define get_LinMsgIndicationOffset(c)        cabLinMsgIndicationOffset
#define get_LinMsgIndicationMask(c)          cabLinMsgIndicationMask
#if defined(LIN_ENABLE_MSG_CONFIRMATION_FLAG) || defined(LIN_ENABLE_DIAGMSG_CONFIRMATION_FLAG)
#define get_LinMsgConfirmationFlags(c)       uLinMsgConfirmationFlags
#endif

#define get_LinMsgConfirmationOffset(c)      cabLinMsgConfirmationOffset
#define get_LinMsgConfirmationMask(c)        cabLinMsgConfirmationMask
#define get_LinRxTxMsgInfo(c)                cabLinRxTxMsgInfo
#define get_LinRxTxMsgDataPtr(c)             capbLinRxTxMsgDataPtr
#define get_LinRxTxDefaultDataPtrTbl(c)      capbLinRxTxDefaultDataPtrTbl
#define get_LinETFUpdateFlags(c)             uLinETFUpdateFlags
#define get_LinETFUpdateFlagOffset(c)        cabLinETFUpdateFlagOffset
#define get_LinETFUpdateFlagMask(c)          cabLinETFUpdateFlagMask
#define get_LinRxApplMsgIndicationFctTbl(c)  capfLinRxApplMsgIndicationFctTbl
#define get_LinTxApplMsgConfirmationFctTbl(c) capfLinTxApplMsgConfirmationFctTbl
#define get_LinRxDiagMsgIndicationFctTbl(c)  (capfLinRxDiagMsgIndicationFctTbl[c])
#define get_LinTxDiagMsgConfirmationFctTbl(c) (capfLinTxDiagMsgConfirmationFctTbl[c])
#define get_LinRxDiagMsgPrecopyFctTbl(c)     capfLinRxDiagMsgPrecopyFctTbl
#define get_LinTxApplMsgPretransmitFctTbl(c) capfLinTxApplMsgPretransmitFctTbl
#define get_LinTxDiagMsgPretransmitFctTbl(c) capfLinTxDiagMsgPretransmitFctTbl
#define get_LinRxApplMsgPrecopyFctTbl(c)     capfLinRxApplMsgPrecopyFctTbl
/* Mapping of Synch functions */
#define kLinChannel
#define LinStartTxSignalReadSync()           SioInterruptDisable(kLinChannel)
#define LinEndTxSignalReadSync()             SioInterruptRestore(kLinChannel)
#define LinStartRxSignalReadSync()           SioInterruptDisable(kLinChannel)
#define LinEndRxSignalReadSync()             SioInterruptRestore(kLinChannel)
#define LinStartTxArrayReadSync()            SioInterruptDisable(kLinChannel)
#define LinEndTxArrayReadSync()              SioInterruptRestore(kLinChannel)
#define LinStartRxArrayReadSync()            SioInterruptDisable(kLinChannel)
#define LinEndRxArrayReadSync()              SioInterruptRestore(kLinChannel)
#define LinStartTxSignalWriteSync()          SioInterruptDisable(kLinChannel)
#define LinEndTxSignalWriteSync()            SioInterruptRestore(kLinChannel)
#define LinStartRxSignalWriteSync()          SioInterruptDisable(kLinChannel)
#define LinEndRxSignalWriteSync()            SioInterruptRestore(kLinChannel)
#define LinStartTxArrayWriteSync()           SioInterruptDisable(kLinChannel)
#define LinEndTxArrayWriteSync()             SioInterruptRestore(kLinChannel)
#define LinStartRxArrayWriteSync()           SioInterruptDisable(kLinChannel)
#define LinEndRxArrayWriteSync()             SioInterruptRestore(kLinChannel)
#define LinStartTxBitSignalReadSync()        SioInterruptDisable(kLinChannel)
#define LinEndTxBitSignalReadSync()          SioInterruptRestore(kLinChannel)
#define LinStartRxBitSignalReadSync()        SioInterruptDisable(kLinChannel)
#define LinEndRxBitSignalReadSync()          SioInterruptRestore(kLinChannel)
#define LinStartTaskSync(c)                  SioInterruptDisable(kLinChannel)
#define LinEndTaskSync(c)                    SioInterruptRestore(kLinChannel)
/* return values internally by precopy and pretransmit functions */
#define kLinNoCopyData_i                     0x00U
#define kLinCopyData_i                       0x01U
#define kLinSupplierId                       0x0000U
#define kLinFunctionId                       0x0000U
#define kLinVariantId                        0x00FFU
/* Slave NAD */
#define bLinInitialNAD                       0x4EU
#define getbLinInitialNAD(c)                 bLinInitialNAD
V_MEMRAM0 extern  V_MEMRAM1 vuint8 V_MEMRAM2 bLinConfiguredNAD;
#define getbLinConfiguredNAD(c)              bLinConfiguredNAD
#define setbLinConfiguredNAD(c, val)         (bLinConfiguredNAD = (val))
#define get_kNmWupTimerStartValue(c)         kNmWupTimerStartValue
#define get_kNmNoWupDelayValue(c)            kNmNoWupDelayValue
#define get_kNmBusIdleTimeoutValue(c)        kNmBusIdleTimeoutValue
#define get_kFpWakeupPattern(c)              kFpWakeupPattern
#define get_LinRxMsgBaseIndex(c)             0
#define get_LinTxMsgBaseIndex(c)             1
#define get_LinTxMsgEndIndex(c)              2
#define get_LinRxMsgEndIndex(c)              0
#define get_NasTimerInitValue(c)             0x03E9U


/* -----------------------------------------------------------------------------
    &&&~ Defines for user specific diagnostic services
 ----------------------------------------------------------------------------- */

#define kNumberOfUserSlaveConfig             0


#define kLinStatusBitFrameHandle             0x01U
#define kLinStatusBitOffset                  0x05U
#define kLinStatusBitMask                    0x02U

/* -----------------------------------------------------------------------------
    &&&~ Confirmation and indication handling
 ----------------------------------------------------------------------------- */

#if defined(LIN_ENABLE_MSG_CONFIRMATION_FLAG) || defined(LIN_ENABLE_DIAGMSG_CONFIRMATION_FLAG)
typedef union tLinMsgConfirmationBitsTag
{
  vuint8 _c[1];
  struct _c_bits16 w[1];
} tLinMsgConfirmationBits;
#endif

#if defined(LIN_ENABLE_MSG_INDICATION_FLAG) || defined(LIN_ENABLE_DIAGMSG_INDICATION_FLAG) || defined(LIN_ENABLE_INTMSG_INDICATION_FLAG)
typedef union tLinMsgIndicationBitsTag
{
  vuint8 _c[1];
  struct _c_bits16 w[1];
} tLinMsgIndicationBits;
#endif

typedef vuint8 (* tApplLinMsgPrecopyFct)(vuint8* rxBuffer);
typedef void (* tApplLinMsgIndicationFct)(tLinFrameHandleType vMsgHandle);
typedef vuint8 (* tApplLinMsgPretransmitFct)(vuint8* txBuffer);
typedef void (* tApplLinMsgConfirmationFct)(tLinFrameHandleType vMsgHandle);
#if defined(LIN_ENABLE_MSG_INDICATION_FLAG) || defined(LIN_ENABLE_DIAGMSG_INDICATION_FLAG)
V_MEMRAM0 extern  V_MEMRAM1_NEAR tLinMsgIndicationBits V_MEMRAM2_NEAR uLinMsgIndicationFlags;

#endif

#if defined(LIN_ENABLE_MSG_CONFIRMATION_FLAG) || defined(LIN_ENABLE_DIAGMSG_CONFIRMATION_FLAG)
V_MEMRAM0 extern  V_MEMRAM1_NEAR tLinMsgConfirmationBits V_MEMRAM2_NEAR uLinMsgConfirmationFlags;

#endif



/* -----------------------------------------------------------------------------
    &&&~ Message Timeout Related Objects
 ----------------------------------------------------------------------------- */

#if defined(LIN_ENABLE_T_FRAME_MAX)
V_MEMROM0 extern  V_MEMROM1 tLinFpTimerType V_MEMROM2 cabFpResponseMaxTimes[9];

#endif

#define get_ResponseTimeoutValue(c, dlc)     (cabFpResponseMaxTimes[dlc])
#define get_HeaderTimeoutValue(c)            4


/* -----------------------------------------------------------------------------
    &&&~ Message related Objects
 ----------------------------------------------------------------------------- */

V_MEMRAM0 extern  V_MEMRAM1 vuint8 V_MEMRAM2 cabLinSlaveProtectedIdTbl[kLinNumberOfConfigurablePIDs];
V_MEMROM0 extern  V_MEMROM1 vuint8 V_MEMROM2 cabLinSlaveProtectedIdInitTbl[kLinNumberOfConfigurablePIDs];
/* Message length, checksum type and direction of each message */
V_MEMROM0 extern  V_MEMROM1 tMessageInfoType V_MEMROM2 cabLinRxTxMsgInfo[kLinNumberOfMsgInfoObjects];


/* Rx data length table */
V_MEMROM0 extern  V_MEMROM1 tLinMsgDataPtrType V_MEMROM2 capbLinRxTxMsgDataPtr[kLinNumberOfRxTxObjects];

V_MEMROM0 extern  V_MEMROM1 tLinMsgDataPtrType V_MEMROM2 pbLinSlaveRespMsgDataPtr;

#define get_pbLinSlaveRespMsgDataPtr(c)      pbLinSlaveRespMsgDataPtr
V_MEMROM0 extern  V_MEMROM1 tLinMsgDataPtrType V_MEMROM2 pbLinMasterReqMsgDataPtr;

#define get_pbLinMasterReqMsgDataPtr(c)      pbLinMasterReqMsgDataPtr
#define get_kLinRxBufferLength(c, hndl)      (cabLinRxTxMsgInfo[hndl].MsgDataLength)
/* pointers to default values */
#if defined(LIN_ENABLE_INIT_TX_DEFAULT_DATA) || defined(LIN_ENABLE_START_TX_DEFAULT_DATA) || defined(LIN_ENABLE_STOP_TX_DEFAULT_DATA) || defined(LIN_ENABLE_INIT_RX_DEFAULT_DATA) || defined(LIN_ENABLE_START_RX_DEFAULT_DATA) || defined(LIN_ENABLE_STOP_RX_DEFAULT_DATA)
V_MEMROM0 extern  V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3* V_MEMROM1 V_MEMROM2 capbLinRxTxDefaultDataPtrTbl[kLinNumberOfRxTxObjects];

#endif

#define LinGetRxTxMsgDataPtrFromHdl(a)       (capbLinRxTxMsgDataPtr[(a)])


/* -----------------------------------------------------------------------------
    &&&~ Message indication and confirmation related objects
 ----------------------------------------------------------------------------- */

V_MEMROM0 extern  V_MEMROM1 tApplLinMsgPrecopyFct V_MEMROM2 capfLinRxApplMsgPrecopyFctTbl[kLinNumberOfRxObjects];

V_MEMROM0 extern  V_MEMROM1 tApplLinMsgIndicationFct V_MEMROM2 capfLinRxApplMsgIndicationFctTbl[kLinNumberOfRxObjects];

V_MEMROM0 extern  V_MEMROM1 tApplLinMsgPretransmitFct V_MEMROM2 capfLinTxApplMsgPretransmitFctTbl[kLinNumberOfTxObjects];

V_MEMROM0 extern  V_MEMROM1 tApplLinMsgConfirmationFct V_MEMROM2 capfLinTxApplMsgConfirmationFctTbl[kLinNumberOfTxObjects];

V_MEMROM0 extern  V_MEMROM1 tApplLinMsgPrecopyFct V_MEMROM2 capfLinRxDiagMsgPrecopyFctTbl[kLinNumberOfDiagRxObjects];

V_MEMROM0 extern  V_MEMROM1 tApplLinMsgIndicationFct V_MEMROM2 capfLinRxDiagMsgIndicationFctTbl[kLinNumberOfDiagRxObjects];

V_MEMROM0 extern  V_MEMROM1 tApplLinMsgPretransmitFct V_MEMROM2 capfLinTxDiagMsgPretransmitFctTbl[kLinNumberOfDiagTxObjects];

V_MEMROM0 extern  V_MEMROM1 tApplLinMsgConfirmationFct V_MEMROM2 capfLinTxDiagMsgConfirmationFctTbl[kLinNumberOfDiagTxObjects];

#if defined(LIN_ENABLE_MSG_INDICATION_FLAG) || defined(LIN_ENABLE_DIAGMSG_INDICATION_FLAG) || defined(LIN_ENABLE_INTMSG_INDICATION_FLAG)
V_MEMROM0 extern  V_MEMROM1 vuint8 V_MEMROM2 cabLinMsgIndicationOffset[kLinNumberOfRxObjects+kLinNumberOfDiagRxObjects];

V_MEMROM0 extern  V_MEMROM1 vuint8 V_MEMROM2 cabLinMsgIndicationMask[kLinNumberOfRxObjects+kLinNumberOfDiagRxObjects];

#endif

V_MEMROM0 extern  V_MEMROM1 vuint8 V_MEMROM2 cabLinMsgConfirmationOffset[kLinNumberOfTxObjects+kLinNumberOfDiagTxObjects];

V_MEMROM0 extern  V_MEMROM1 vuint8 V_MEMROM2 cabLinMsgConfirmationMask[kLinNumberOfTxObjects+kLinNumberOfDiagTxObjects];



/* -----------------------------------------------------------------------------
    &&&~ Lin21 Table
 ----------------------------------------------------------------------------- */

V_MEMROM0 extern  V_MEMROM1 tLinFrameHandleType V_MEMROM2 cabConfigurablePIDHandleTbl[kLinNumberOfConfigurablePIDs];



/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 258965458
      #error "The magic number of the generated file <D:\uidq0188\Desktop\New folder\lin_par_i.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 258965458
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __LIN_PAR_I_H__ */
