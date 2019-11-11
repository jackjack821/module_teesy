/* -----------------------------------------------------------------------------
  Filename:    v_par.h
  Description: Toolversion: 01.00.22.01.50.07.51.00.00.00
               
               Serial Number: CBD1500751
               Customer Info: Desay SV Automotive Co., Ltd.
                              Package: CBD Geely SLP1
                              Micro: R7F7010233AFP
                              Compiler: Green Hills 6.1.4
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyVcfgNameDecorator
               
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

#if !defined(__V_PAR_H__)
#define __V_PAR_H__

/* -----------------------------------------------------------------------------
    &&&~ BaseEnv_PHF_Includes
 ----------------------------------------------------------------------------- */

#include "v_cfg.h"
#include "v_def.h"


/* -----------------------------------------------------------------------------
    &&&~ GENy Version Information
 ----------------------------------------------------------------------------- */

#define VGEN_DELIVERY_VERSION_BYTE_0         0x01
#define VGEN_DELIVERY_VERSION_BYTE_1         0x00
#define VGEN_DELIVERY_VERSION_BYTE_2         0x22
#define VGEN_DELIVERY_VERSION_BYTE_3         0x01
#define VGEN_DELIVERY_VERSION_BYTE_4         0x50
#define VGEN_DELIVERY_VERSION_BYTE_5         0x07
#define VGEN_DELIVERY_VERSION_BYTE_6         0x51
#define VGEN_DELIVERY_VERSION_BYTE_7         0x00
#define VGEN_DELIVERY_VERSION_BYTE_8         0x00
#define VGEN_DELIVERY_VERSION_BYTE_9         0x00
#define kGENyVersionNumberOfBytes            10
/* ROM CATEGORY 4 START */
V_MEMROM0 extern  V_MEMROM1 vuint8 V_MEMROM2 kGENyVersion[kGENyVersionNumberOfBytes];
/* ROM CATEGORY 4 END */




/* disable magic number check for support of multiple projects */
#ifndef SKIP_MAGIC_NUMBER
#define SKIP_MAGIC_NUMBER
#endif


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 286121459
      #error "The magic number of the generated file <D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\CanGenerateCode\v_par.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 286121459
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __V_PAR_H__ */
