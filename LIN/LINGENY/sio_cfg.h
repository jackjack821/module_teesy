/* -----------------------------------------------------------------------------
  Filename:    sio_cfg.h
  Description: Toolversion: 00.00.00.01.40.05.50.00.00.00
               
               Serial Number: CBD1400550
               Customer Info: Desay SV Automotive Co., Ltd.
                              Package: LIN_SLP2 - CBD LIN 2.0 license
                              Micro: PD78F1828A
                              Compiler: IAR 4.71.1.50113
               
               
               Generator Fwk   : GENy 
               Generator Module: DrvLin__baseSci
               
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

#if !defined(__SIO_CFG_H__)
#define __SIO_CFG_H__

/* Version defines */
#define DRVLIN__BASESCIDLL_VERSION           0x0210u
#define DRVLIN__BASESCIDLL_RELEASE_VERSION   0x03u


/* Hardware dependent configuration */
#define SIO_APITYPE_SINGLE
#define SIO_LL_APISTYLE_MESSAGE
#define SIO_LL_APITYPE_HEADER_IND
#define SIO_LL_DISABLE_BAUDRATE_INFORMATION
#define SIO_ECUTYPE_SLAVE
#define SIO_DISABLE_OSEK_OS
#define SIO_PROTOCOLVERSION_VALUE            0x21
#define SIO_DISABLE_CLOCK_DEV_INDICATION
#define SIO_LL_DISABLE_COMPATIBILITY_MODE
#define SIO_INTERFACE_SCICTRL
#define SIO_ENABLE_SIO_UART0
#define SIO_DISABLE_SIO_UART1
#define SIO_DISABLE_NO_ISR_FUNCTION
#define SIO_DISABLE_BAUDRATE_DETECT
#define kSioNumberOfChannels                 1
#define SIO_ENABLE_BAUDRATE_SYNC


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 258965458
      #error "The magic number of the generated file <D:\uidq0188\Desktop\New folder\sio_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 258965458
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __SIO_CFG_H__ */
