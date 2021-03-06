/* -----------------------------------------------------------------------------
  Filename:    nmcbdwrp_par.c
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

#define __NMCBDWRP_PAR_C__
/* Includes */
#include "v_cfg.h"
#include "v_def.h"
#include "nmcbdwrp_cfg.h"
/* Channel specific parameters */
/* Channel indirection */
/* --------------------- Module Data Prototypes --------------------- */
#if defined CBDWRP_ADAPTATION_LAYER
#else
/* BusOff recovery timer. */
V_MEMRAM0 V_MEMRAM1 vuint16 V_MEMRAM2 cbdWrpBusOffRecTimer[kCbdWrpNumberOfChannels];
V_MEMRAM0 V_MEMRAM1 vuint8  V_MEMRAM2 cbdWrpBusOffThresholdCounter[kCbdWrpNumberOfChannels];

# if defined ( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
/* Indication Flag that the CAN Driver is in BusOff state */
V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 cbdWrpDrvCanIsBusOff[kCbdWrpNumberOfChannels];
# endif
#endif

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 286121459
      #error "The magic number of the generated file <D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\CanGenerateCode\nmcbdwrp_par.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\CanGenerateCode\nmcbdwrp_par.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

