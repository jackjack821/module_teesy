/* -----------------------------------------------------------------------------
  Filename:    drv_par_1.c
  Description: Toolversion: 00.00.00.01.40.05.50.00.00.00
               
               Serial Number: CBD1400550
               Customer Info: Desay SV Automotive Co., Ltd.
                              Package: LIN_SLP2 - CBD LIN 2.0 license
                              Micro: PD78F1828A
                              Compiler: IAR 4.71.1.50113
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyDriverBase
               
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
#include "drv_par.h"
/* -----------------------------------------------------------------------------
    &&&~ Message Buffers
 ----------------------------------------------------------------------------- */

/* RAM CATEGORY 2 START */
/* PRQA  S 0759 QAC_Can_0759 */ /* MD_Can_0759 */
V_MEMRAM0 V_MEMRAM1 _c_AC_1_buf V_MEMRAM2 AC_1;
V_MEMRAM0 V_MEMRAM1 _c_FCP_1_buf V_MEMRAM2 FCP_1;
V_MEMRAM0 V_MEMRAM1 _c_FCP_2_buf V_MEMRAM2 FCP_2;
V_MEMRAM0 V_MEMRAM1 _c_MasterReq_buf V_MEMRAM2 MasterReq;
V_MEMRAM0 V_MEMRAM1 _c_SlaveResp_buf V_MEMRAM2 SlaveResp;
/* PRQA  L:QAC_Can_0759 */

/* RAM CATEGORY 2 END */





/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 258965458
      #error "The magic number of the generated file <D:\uidq0188\Desktop\New folder\drv_par_1.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <D:\uidq0188\Desktop\New folder\drv_par_1.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

