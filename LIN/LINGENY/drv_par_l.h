/* -----------------------------------------------------------------------------
  Filename:    drv_par_1.h
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

#if !defined(__DRV_PAR_1_H__)
#define __DRV_PAR_1_H__

/* -----------------------------------------------------------------------------
    &&&~ Signal Structures
 ----------------------------------------------------------------------------- */

typedef struct _c_AC_1_msgTypeTag
{
  vbittype L_AC_LeftSetTemperature : 8;
  vbittype L_AC_RightSetTemperature : 8;
  vbittype L_AC_AmbientTemperature : 8;
  vbittype L_AC_BlowerLevel : 4;
  vbittype L_AC_IntakeAirState : 4;
  vbittype L_AC_AirDistributionMode : 4;
  vbittype L_AC_AqsState : 1;
  vbittype L_AC_DefrostState : 1;
  vbittype L_AC_AutoState : 1;
  vbittype L_AC_ACCompReq : 1;
  vbittype L_AC_OnState : 1;
  vbittype L_AC_DUALstatus : 1;
  vbittype L_AC_MaxACrequset : 1;
  vbittype L_AC_SeatHeat_L : 1;
  vbittype L_AC_Control_Lock_Req : 2;
  vbittype unused0 : 2;
  vbittype L_AC_SeatHeat_R : 1;
  vbittype L_AC_SeatHeatLevel_R : 4;
  vbittype L_AC_RearDefReq : 1;
  vbittype L_AC_RearDefActualReq : 1;
  vbittype L_AC_EconMode : 1;
  vbittype L_AC_IONRunstatus : 2;
  vbittype L_AC_OffMode : 1;
  vbittype L_AC_InCarAirCondition : 2;
  vbittype L_AC_System_1S : 1;
  vbittype L_AC_PowerFail : 1;
  vbittype L_AC_IONdetectEnable : 1;
} _c_AC_1_msgType;
typedef struct _c_FCP_1_msgTypeTag
{
  vbittype L_FCP_LeftTempUp : 4;
  vbittype L_FCP_LeftTempDown : 4;
  vbittype L_FCP_RightTempUp : 4;
  vbittype L_FCP_RightTempDown : 4;
  vbittype L_FCP_Blowup : 4;
  vbittype L_FCP_BlowDown : 4;
  vbittype L_FCP_Heatreq : 1;
  vbittype unused0 : 1;
  vbittype L_FCP_ModeDown : 1;
  vbittype L_FCP_ModeUp : 1;
  vbittype L_FCP_AUTOreq : 1;
  vbittype L_FCP_Acreq : 1;
  vbittype L_FCP_DualReq : 1;
  vbittype L_FCP_MaxAcReq : 1;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
} _c_FCP_1_msgType;
typedef struct _c_FCP_2_msgTypeTag
{
  vbittype FCP_NatsIrAd_0 : 8;
  vbittype FCP_NatsIrAd_1 : 2;
  vbittype FCP_NatsTempAd_0 : 6;
  vbittype FCP_NatsTempAd_1 : 4;
  vbittype FCP_NatsPcbTempAd_0 : 4;
  vbittype FCP_NatsPcbTempAd_1 : 6;
  vbittype unused0 : 2;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
} _c_FCP_2_msgType;
typedef struct _c_MasterReq_msgTypeTag
{
  vbittype MasterReqB0 : 8;
  vbittype MasterReqB1 : 8;
  vbittype MasterReqB2 : 8;
  vbittype MasterReqB3 : 8;
  vbittype MasterReqB4 : 8;
  vbittype MasterReqB5 : 8;
  vbittype MasterReqB6 : 8;
  vbittype MasterReqB7 : 8;
} _c_MasterReq_msgType;
typedef struct _c_SlaveResp_msgTypeTag
{
  vbittype SlaveRespB0 : 8;
  vbittype SlaveRespB1 : 8;
  vbittype SlaveRespB2 : 8;
  vbittype SlaveRespB3 : 8;
  vbittype SlaveRespB4 : 8;
  vbittype SlaveRespB5 : 8;
  vbittype SlaveRespB6 : 8;
  vbittype SlaveRespB7 : 8;
} _c_SlaveResp_msgType;


/* -----------------------------------------------------------------------------
    &&&~ Signal value names
 ----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
    &&&~ Message Unions
 ----------------------------------------------------------------------------- */

typedef union _c_AC_1_bufTag
{
  vuint8 _c[8];
  _c_AC_1_msgType AC_1;
} _c_AC_1_buf;
typedef union _c_FCP_1_bufTag
{
  vuint8 _c[8];
  _c_FCP_1_msgType FCP_1;
} _c_FCP_1_buf;
typedef union _c_FCP_2_bufTag
{
  vuint8 _c[8];
  _c_FCP_2_msgType FCP_2;
} _c_FCP_2_buf;
typedef union _c_MasterReq_bufTag
{
  vuint8 _c[8];
  _c_MasterReq_msgType MasterReq;
} _c_MasterReq_buf;
typedef union _c_SlaveResp_bufTag
{
  vuint8 _c[8];
  _c_SlaveResp_msgType SlaveResp;
} _c_SlaveResp_buf;


/* -----------------------------------------------------------------------------
    &&&~ Message Buffers
 ----------------------------------------------------------------------------- */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_AC_1_buf V_MEMRAM2 AC_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_FCP_1_buf V_MEMRAM2 FCP_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_FCP_2_buf V_MEMRAM2 FCP_2;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_MasterReq_buf V_MEMRAM2 MasterReq;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_SlaveResp_buf V_MEMRAM2 SlaveResp;
/* RAM CATEGORY 2 END */






/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 258965458
      #error "The magic number of the generated file <D:\uidq0188\Desktop\New folder\drv_par_1.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 258965458
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __DRV_PAR_1_H__ */
