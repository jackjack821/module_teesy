/* -----------------------------------------------------------------------------
  Filename:    lin_cfg.h
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

#if !defined(__LIN_CFG_H__)
#define __LIN_CFG_H__

/* General Configuration settings */
#define DRIVER_LINDLL_VERSION                0x0230u
#define DRIVER_LINDLL_RELEASE_VERSION        0x02u
#define LIN_PROTOCOLVERSION_VALUE            0x21U
#define LIN_PROTOCOLVERSION_21
#define LIN_ECUTYPE_SLAVE
#define LIN_APISTYLE_VECTOR
#define LIN_APITYPE_SINGLE
/* Used features */
#define LIN_ENABLE_SLAVE_CONFIGURATION
#define LIN_ENABLE_ASSIGN_NAD_COMMAND
#define LIN_ENABLE_DATA_DUMP_BY_APPL
#define LIN_ENABLE_READ_BY_ID_BY_APPL
#define LIN_DISABLE_READ_BY_ID_MESSAGE_IDS
#define LIN_DISABLE_COND_CHANGE_NAD_COMMAND
#define LIN_ENABLE_DEBUG
#define LIN_ENABLE_CONFIGURABLE_PID
#define LIN_ENABLE_INIT_PID_FROM_LDF
#define LIN_DISABLE_INIT_PID_FROM_NCF
#define LIN_DISABLE_CONFIGURABLE_INAD
#define LIN_ENABLE_SLAVE_CONFIG_OPT_RESP
#define LIN_ENABLE_SC_WILDCARDS
#define LIN_ENABLE_CONFIGURATION_API
#define LIN_DISABLE_USER_SLAVE_CONFIG_0
#define LIN_DISABLE_USER_SLAVE_CONFIG_1
#define LIN_DISABLE_USER_SLAVE_CONFIG_2
#define LIN_DISABLE_USER_SLAVE_CONFIG_3
#define LIN_DISABLE_DIAG_RESPONSE_AFTER_ERROR
#define LIN_DISABLE_SLEEP_COMMAND_REPETITION
#define LIN_ENABLE_T_NODE_CONFIG_SERVICE
#define LIN_DISABLE_USER_SLAVE_CONFIG
/* Configured frame types */
#define LIN_ENABLE_UNC_RX_FRAMES
#define LIN_ENABLE_UNC_TX_FRAMES
#define LIN_DISABLE_ET_RX_FRAMES
#define LIN_DISABLE_ET_TX_FRAMES
#define LIN_ENABLE_DIAG_FRAMES
#define LIN_DISABLE_UNC_NO_FRAMES
#define LIN_DISABLE_SPOR_SLOTS
#define LIN_DISABLE_CMD_SLOTS
/* notification handling */
#define LIN_ENABLE_MSG_CONFIRMATION_FLAG
#define LIN_ENABLE_MSG_INDICATION_FLAG
#define LIN_DISABLE_INTMSG_INDICATION_FLAG
#define LIN_DISABLE_SIG_CONFIRMATION_FLAG
#define LIN_DISABLE_SIG_INDICATION_FLAG
#define LIN_DISABLE_SIG_CONFIRMATION_FCT
#define LIN_DISABLE_SIG_INDICATION_FCT
#define LIN_DISABLE_MSG_PRETRANSMIT_FCT
#define LIN_DISABLE_MSG_CONFIRMATION_FCT
#define LIN_DISABLE_MSG_INDICATION_FCT
#define LIN_DISABLE_MSG_PRECOPY_FCT
#define LIN_ENABLE_DIAGMSG_CONFIRMATION_FLAG
#define LIN_ENABLE_DIAGMSG_INDICATION_FLAG
#define LIN_DISABLE_DIAGMSG_PRETRANSMIT_FCT
#define LIN_DISABLE_DIAGMSG_CONFIRMATION_FCT
#define LIN_DISABLE_DIAGMSG_INDICATION_FCT
#define LIN_DISABLE_DIAGMSG_PRECOPY_FCT
/* Default values for Signals */
#define LIN_ENABLE_INIT_TX_DEFAULT_DATA
#define LIN_ENABLE_START_TX_DEFAULT_DATA
#define LIN_ENABLE_STOP_TX_DEFAULT_DATA
#define LIN_ENABLE_INIT_RX_DEFAULT_DATA
#define LIN_ENABLE_START_RX_DEFAULT_DATA
#define LIN_ENABLE_STOP_RX_DEFAULT_DATA
#define LIN_ENABLE_STATUSBIT_SIGNAL
/* Timeout observation */
//#define LIN_ENABLE_T_HEADER_MAX
#define LIN_ENABLE_T_FRAME_MAX
#define LIN_ENABLE_T_WAKEUP
#define LIN_ENABLE_T_BUS_IDLE
/* optimizations */
#define LIN_DISABLE_INTCTRL_BY_APPL
#define LIN_ENABLE_MSG_PRETRANSMIT_FCT  /*update key info,161119*/
#define LIN_DISABLE_MSGRESPONSE_FCT
#define LIN_DISABLE_SYNCHBREAK_NOTIFICATION
#define LIN_ENABLE_LINSTART_WAKEUP_INTERNAL
#define LIN_ENABLE_LINSTART_WAKEUP_EXTERNAL
#define LIN_DISABLE_BAUDRATE_INFORMATION
#define LIN_DISABLE_HEADER_NOTIFICATION
#define LIN_DISABLE_RX_BUFFER_OPT
#define LIN_FASTTIMER_CONTEXT_IRQ
#define LIN_ENABLE_FASTRAM_VARIABLES
/* Error observation */
#define LIN_ENABLE_HEADER_MONITORING
#define LIN_ENABLE_NO_BUS_ACTIVITY
#define LIN_ENABLE_NO_BUS_WAKEUP
#define LIN_ENABLE_PHYSICAL_BUS_ERROR
#define LIN_ENABLE_NO_RESPONSE_ERROR
#define LIN_ENABLE_BIT_ERROR
#define LIN_DISABLE_SYNCH_FIELD_ERROR
#define LIN_ENABLE_FORMAT_ERROR
#define LIN_ENABLE_CHECKSUM_ERROR
#define LIN_ENABLE_LOST_PRIORITIZATION_ERROR
#define LIN_ENABLE_NO_HEADER_ERROR
/* Uses of diagnostic frames */
#define LIN_ENABLE_DIAGFRAME_BY_APPL
#define LIN_ENABLE_DIAG_TRANSP_LAYER
#define LIN_DISABLE_TARGETED_RESET_COMMAND
#define LIN_DISABLE_VARIANT_ID_BY_APPL
#define LIN_DISABLE_SUPPLIER_ID_BY_APPL
#define LIN_DISABLE_MULTI_ECU_CONFIG
#define identity                             0
#define LIN_GOTOSLEEPBIT_SET_AFTERTRANSMISSION
#define LIN_DISABLE_ASSIGN_NAD_VIA_SNPD_COMMAND
#define LIN_DISABLE_SAVE_CONFIGURATION_COMMAND
#define LIN_ENABLE_ASSIGN_FRM_ID_RANGE_COMMAND
#define LIN_DISABLE_ASSIGN_FRM_ID_COMMAND
#define LIN_ENABLE_SIGNAL_ACCESS_PROTECTION
#define LIN_DISABLE_COMPATIBILITY_MODE
#define LIN_DISABLE_RESP_ERR_BIT_CONFIG
#define LIN_DISABLE_FULL_NAD_RANGE


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 258965458
      #error "The magic number of the generated file <D:\uidq0188\Desktop\New folder\lin_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 258965458
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __LIN_CFG_H__ */
