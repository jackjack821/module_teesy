/* -----------------------------------------------------------------------------
  Filename:    diag_cfg.h
  Description: Toolversion: 00.00.00.01.40.05.50.00.00.00
               
               Serial Number: CBD1400550
               Customer Info: Desay SV Automotive Co., Ltd.
                              Package: LIN_SLP2 - CBD LIN 2.0 license
                              Micro: PD78F1828A
                              Compiler: IAR 4.71.1.50113
               
               
               Generator Fwk   : GENy 
               Generator Module: DiagLin_SlavEcu
               
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

#if !defined(__DIAG_CFG_H__)
#define __DIAG_CFG_H__

#define kLinDiagDataBufferLength             255
#define LINDIAG_DISABLE_DEBUG_MODE
#define LINDIAG_DISABLE_RCR_RP_SUPPORT
#define LINDIAG_DISABLE_SESSION_MANAGEMENT
#define LINDIAG_DISABLE_ON_S1_TIMEOUT_NOTIFICATION
#define kLinDiagCallCycleTime                10
#define LINDIAG_DISABLE_NR_ON_RES_SID
#define LINDIAG_DISABLE_MULTIPLE_SERVICE_CALL
#define LINDIAG_DISABLE_NEG_RES_ON_BUFF_OVERRUN
#define LINDIAG_ENABLE_USER_SERVICE_SUPPORT
#define LINDIAG_DISABLE_TX_CONFIRMATION
#define LINDIAG_DISABLE_SERVICE_10H
#define LINDIAG_DISABLE_SERVICE_11H
#define LINDIAG_DISABLE_SERVICE_27H
#define LINDIAG_DISABLE_SERVICE_28H
#define LINDIAG_DISABLE_SERVICE_3EH
#define LINDIAG_DISABLE_SERVICE_85H
#define LINDIAG_DISABLE_SERVICE_22H
#define LINDIAG_DISABLE_SERVICE_23H
#define LINDIAG_DISABLE_SERVICE_24H
#define LINDIAG_DISABLE_SERVICE_3DH
#define LINDIAG_DISABLE_SERVICE_2EH
#define LINDIAG_DISABLE_SERVICE_14H
#define LINDIAG_DISABLE_SERVICE_19H
#define LINDIAG_DISABLE_SERVICE_2FH
#define LINDIAG_DISABLE_SERVICE_31H
#define LINDIAG_DISABLE_SERVICE_34H
#define LINDIAG_DISABLE_SERVICE_35H
#define LINDIAG_DISABLE_SERVICE_36H
#define LINDIAG_DISABLE_SERVICE_37H

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 258965458
      #error "The magic number of the generated file <D:\uidq0188\Desktop\New folder\diag_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 258965458
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __DIAG_CFG_H__ */
