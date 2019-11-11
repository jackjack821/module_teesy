/* -----------------------------------------------------------------------------
  Filename:    nmcbdwrp_cfg.h
  Description: Toolversion: 01.00.22.01.50.07.51.00.00.00
               
               Serial Number: CBD1500751
               Customer Info: Desay SV Automotive Co., Ltd.
                              Package: CBD Geely SLP1
                              Micro: R7F7010233AFP
                              Compiler: Green Hills 6.1.4
               
               
               Generator Fwk   : GENy 
               Generator Module: Nm_AsrNmCANbeddedWrapper
               
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

#if !defined(__NMCBDWRP_CFG_H__)
#define __NMCBDWRP_CFG_H__

/* Version */
#define NM_ASRNMCANWRAPPEREXTDLL_VERSION     0x0327u
#define NM_ASRNMCANWRAPPEREXTDLL_RELEASE_VERSION 0x00u
/* Instance properties */
#define kCbdWrpNumberOfChannels              1
#define kCbdWrpNumberOfCanChannels           1
/* Module options */
#define CBDWRP_DISABLE_ASR_ERROR_REPORT
#define CBDWRP_DISABLE_ASSERTIONS
#define CBDWRP_ENABLE_EARLY_BUSOFF_REINIT
#define CBDWRP_DISABLE_ASRNM_BUSOFF_SUPPORT
#define CBDWRP_DISABLE_TESTDEBUG
#define CBDWRP_ENABLE_RESET_BUSOFF_THRESHOLD_COUNTER_ON_ANY_TX_CONFIRMATION
#define CBDWRP_ENABLE_FASTBUSOFFRECOVERY_CHANGE_CALLBACK
/* Channel specific parameters */
#define kCbdWrpBusOffRecoveryTime            100
#define kCbdWrpBusOffRecoveryTimeFast        10
#define kCbdWrpBusOffThreshold               10
#define kCbdWrpCycleTime                     10
/* --------------------- Configuration Data Prototypes --------------------- */
#if defined ( CBDWRP_ADAPTATION_LAYER )
#else
# if ( kCbdWrpNumberOfChannels > 1u )
/* BusOff recovery time parameters. */
extern V_MEMROM0 V_MEMROM1 vuint16 V_MEMROM2 CbdWrpBusOffRecoveryTime[kCbdWrpNumberOfChannels];
extern V_MEMROM0 V_MEMROM1 vuint16 V_MEMROM2 CbdWrpBusOffRecoveryTimeFast[kCbdWrpNumberOfChannels];
extern V_MEMROM0 V_MEMROM1 vuint8  V_MEMROM2 CbdWrpBusOffThreshold[kCbdWrpNumberOfChannels];
extern V_MEMROM0 V_MEMROM1 vuint8  V_MEMROM2 CbdWrpCycleTime[kCbdWrpNumberOfChannels];
# endif
#endif

#if ( kCbdWrpNumberOfChannels != kCbdWrpNumberOfCanChannels )
/* CAN to local NM channel */
extern V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanNm_CanToNmChannelInd[kCbdWrpNumberOfCanChannels];
# if defined ( CBDWRP_ADAPTATION_LAYER )
# else
/* Local NM to CAN channel */
extern V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanNm_NmToCanChannelInd[kCbdWrpNumberOfChannels];
# endif
#endif

#if defined ( NM_ASRNMCANWRAPPEREXT_SOURCE ) || defined ( __NMCBDWRP_PAR_C__ )
/* --------------------- Module Data Prototypes --------------------- */
# if defined ( CBDWRP_ADAPTATION_LAYER )
# else
/* BusOff recovery timer. */
extern V_MEMRAM0 V_MEMRAM1 vuint16 V_MEMRAM2 cbdWrpBusOffRecTimer[kCbdWrpNumberOfChannels];
extern V_MEMRAM0 V_MEMRAM1 vuint8  V_MEMRAM2 cbdWrpBusOffThresholdCounter[kCbdWrpNumberOfChannels];

#  if defined ( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
/* Indication Flag that the CAN Driver is in BusOff state */
extern V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 cbdWrpDrvCanIsBusOff[kCbdWrpNumberOfChannels];
#  endif
# endif
#endif

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 286121459
      #error "The magic number of the generated file <D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\CanGenerateCode\nmcbdwrp_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 286121459
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __NMCBDWRP_CFG_H__ */
