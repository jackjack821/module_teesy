/* -----------------------------------------------------------------------------
  Filename:    dtl_cfg.h
  Description: Toolversion: 00.00.00.01.40.05.50.00.00.00
               
               Serial Number: CBD1400550
               Customer Info: Desay SV Automotive Co., Ltd.
                              Package: LIN_SLP2 - CBD LIN 2.0 license
                              Micro: PD78F1828A
                              Compiler: IAR 4.71.1.50113
               
               
               Generator Fwk   : GENy 
               Generator Module: TpLin
               
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

#if !defined(__DTL_CFG_H__)
#define __DTL_CFG_H__

/* -----------------------------------------------------------------------------
    &&&~ General Configuration Settings
 ----------------------------------------------------------------------------- */

#define DTL_LINDLL_VERSION                   0x0205u
#define DTL_LINDLL_RELEASE_VERSION           0x01u
#define DTL_ECUTYPE_SLAVE
#define DTL_APISTYLE_VECTOR
#define DTL_APITYPE_SINGLE
#define DTL_PROCESSING_COOKED
#define DTL_ENABLE_RESP_PENDING
#define DTL_DISABLE_ALL_NAD
#define DTL_ENABLE_DEBUG
#define DTL_DISABLE_SECONDARY_NAD
#define DTL_DISABLE_TX_SINGLE_FRAME_ONLY
#define DTL_DISABLE_RX_SINGLE_FRAME_ONLY
#define DTL_DISABLE_RCR_RP_SUPPORT



/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 258965458
      #error "The magic number of the generated file <D:\uidq0188\Desktop\New folder\dtl_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 258965458
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __DTL_CFG_H__ */
