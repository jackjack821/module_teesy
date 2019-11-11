/* -----------------------------------------------------------------------------
  Filename:    lin_par.h
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

#if !defined(__LIN_PAR_H__)
#define __LIN_PAR_H__

/* -----------------------------------------------------------------------------
    &&&~ MISRA definitions
 ----------------------------------------------------------------------------- */

/* PRQA S 3458 EOF *//* MD_CBD_19.4 */


/* -----------------------------------------------------------------------------
    &&&~ Timeout handling
 ----------------------------------------------------------------------------- */

#define kLinFastTimeoutTaskCycle             1000
#define kLinSlowTimeoutTaskCycle             20
#define kLinTimeBaseHighRes                  10000


/* -----------------------------------------------------------------------------
    &&&~ Message Callback functions
 ----------------------------------------------------------------------------- */

/* return values used by precopy and pretransmit functions */
#define kLinNoCopyData                       0x00U
#define kLinCopyData                         0x01U


/* -----------------------------------------------------------------------------
    &&&~ Access to confirmation flags
 ----------------------------------------------------------------------------- */

#define FCP_1_conf_b                         (uLinMsgConfirmationFlags.w[0].b0)
#define l_flg_tst_FCP_1()                    (FCP_1_conf_b != 0)
#define l_flg_clr_FCP_1()                    (FCP_1_conf_b = 0)
#define FCP_2_conf_b                         (uLinMsgConfirmationFlags.w[0].b1)
#define l_flg_tst_FCP_2()                    (FCP_2_conf_b != 0)
#define l_flg_clr_FCP_2()                    (FCP_2_conf_b = 0)
#define SlaveResp_conf_b                     (uLinMsgConfirmationFlags.w[0].b2)
#define l_flg_tst_SlaveResp()                (SlaveResp_conf_b != 0)
#define l_flg_clr_SlaveResp()                (SlaveResp_conf_b = 0)


/* -----------------------------------------------------------------------------
    &&&~ Access to indication flags
 ----------------------------------------------------------------------------- */

#define AC_1_ind_b                           (uLinMsgIndicationFlags.w[0].b0)
#define l_flg_tst_AC_1()                     (AC_1_ind_b != 0)
#define l_flg_clr_AC_1()                     (AC_1_ind_b = 0)
#define MasterReq_ind_b                      (uLinMsgIndicationFlags.w[0].b1)
#define l_flg_tst_MasterReq()                (MasterReq_ind_b != 0)
#define l_flg_clr_MasterReq()                (MasterReq_ind_b = 0)


/* -----------------------------------------------------------------------------
    &&&~ Macro Access to signals
 ----------------------------------------------------------------------------- */

#define _s_L_AC_LeftSetTemperature           (AC_1.AC_1.L_AC_LeftSetTemperature)
#define _s_L_AC_RightSetTemperature          (AC_1.AC_1.L_AC_RightSetTemperature)
#define _s_L_AC_AmbientTemperature           (AC_1.AC_1.L_AC_AmbientTemperature)
#define _s_L_AC_BlowerLevel                  (AC_1.AC_1.L_AC_BlowerLevel)
#define _s_L_AC_IntakeAirState               (AC_1.AC_1.L_AC_IntakeAirState)
#define _s_L_AC_AirDistributionMode          (AC_1.AC_1.L_AC_AirDistributionMode)
#define _s_L_AC_AqsState                     (AC_1.AC_1.L_AC_AqsState)
#define _s_L_AC_DefrostState                 (AC_1.AC_1.L_AC_DefrostState)
#define _s_L_AC_AutoState                    (AC_1.AC_1.L_AC_AutoState)
#define _s_L_AC_ACCompReq                    (AC_1.AC_1.L_AC_ACCompReq)
#define _s_L_AC_OnState                      (AC_1.AC_1.L_AC_OnState)
#define _s_L_AC_DUALstatus                   (AC_1.AC_1.L_AC_DUALstatus)
#define _s_L_AC_MaxACrequset                 (AC_1.AC_1.L_AC_MaxACrequset)
#define _s_L_AC_SeatHeat_L                   (AC_1.AC_1.L_AC_SeatHeat_L)
#define _s_L_AC_Control_Lock_Req             (AC_1.AC_1.L_AC_Control_Lock_Req)
#define _s_L_AC_SeatHeat_R                   (AC_1.AC_1.L_AC_SeatHeat_R)
#define _s_L_AC_SeatHeatLevel_R              (AC_1.AC_1.L_AC_SeatHeatLevel_R)
#define _s_L_AC_RearDefReq                   (AC_1.AC_1.L_AC_RearDefReq)
#define _s_L_AC_RearDefActualReq             (AC_1.AC_1.L_AC_RearDefActualReq)
#define _s_L_AC_EconMode                     (AC_1.AC_1.L_AC_EconMode)
#define _s_L_AC_IONRunstatus                 (AC_1.AC_1.L_AC_IONRunstatus)
#define _s_L_AC_OffMode                      (AC_1.AC_1.L_AC_OffMode)
#define _s_L_AC_InCarAirCondition            (AC_1.AC_1.L_AC_InCarAirCondition)
#define _s_L_AC_System_1S                    (AC_1.AC_1.L_AC_System_1S)
#define _s_L_AC_PowerFail                    (AC_1.AC_1.L_AC_PowerFail)
#define _s_L_AC_IONdetectEnable              (AC_1.AC_1.L_AC_IONdetectEnable)
#define _s_L_FCP_LeftTempUp                  (FCP_1.FCP_1.L_FCP_LeftTempUp)
#define _s_L_FCP_LeftTempDown                (FCP_1.FCP_1.L_FCP_LeftTempDown)
#define _s_L_FCP_RightTempUp                 (FCP_1.FCP_1.L_FCP_RightTempUp)
#define _s_L_FCP_RightTempDown               (FCP_1.FCP_1.L_FCP_RightTempDown)
#define _s_L_FCP_Blowup                      (FCP_1.FCP_1.L_FCP_Blowup)
#define _s_L_FCP_BlowDown                    (FCP_1.FCP_1.L_FCP_BlowDown)
#define _s_L_FCP_Heatreq                     (FCP_1.FCP_1.L_FCP_Heatreq)
#define _s_L_FCP_ModeDown                    (FCP_1.FCP_1.L_FCP_ModeDown)
#define _s_L_FCP_ModeUp                      (FCP_1.FCP_1.L_FCP_ModeUp)
#define _s_L_FCP_AUTOreq                     (FCP_1.FCP_1.L_FCP_AUTOreq)
#define _s_L_FCP_Acreq                       (FCP_1.FCP_1.L_FCP_Acreq)
#define _s_L_FCP_DualReq                     (FCP_1.FCP_1.L_FCP_DualReq)
#define _s_L_FCP_MaxAcReq                    (FCP_1.FCP_1.L_FCP_MaxAcReq)
//#define _s_L_FCP_DefrostReq                  (FCP_1.FCP_1.L_FCP_DefrostReq)
//#define _s_L_FCP_RearDefReq                  (FCP_1.FCP_1.L_FCP_RearDefReq)
//#define _s_L_FCP_CycleReq                    (FCP_1.FCP_1.L_FCP_CycleReq)
//#define _s_L_FCP_LeftSeatHeatReq             (FCP_1.FCP_1.L_FCP_LeftSeatHeatReq)
//#define _s_L_FCP_RightSeatHeatReq            (FCP_1.FCP_1.L_FCP_RightSeatHeatReq)
//#define _s_L_FCP_EconReq                     (FCP_1.FCP_1.L_FCP_EconReq)
//#define _s_L_FCP_IONreq                      (FCP_1.FCP_1.L_FCP_IONreq)
//#define _s_L_FCP_OffModereq                  (FCP_1.FCP_1.L_FCP_OffModereq)
#define _s_L_FCP_NoUsed4                 (FCP_1.FCP_1.unused4)
#define _s_L_FCP_NoUsed3                 (FCP_1.FCP_1.unused3)
#define _s_L_FCP_NoUsed2                 (FCP_1.FCP_1.unused2)
#define _s_L_FCP_NoUsed1                 (FCP_1.FCP_1.unused1)
#define _s_FCP_NatsIrAd_0                    (FCP_2.FCP_2.FCP_NatsIrAd_0)
#define _s_FCP_NatsIrAd_1                    (FCP_2.FCP_2.FCP_NatsIrAd_1)
#define _s_FCP_NatsTempAd_0                  (FCP_2.FCP_2.FCP_NatsTempAd_0)
#define _s_FCP_NatsTempAd_1                  (FCP_2.FCP_2.FCP_NatsTempAd_1)
#define _s_FCP_NatsPcbTempAd_0               (FCP_2.FCP_2.FCP_NatsPcbTempAd_0)
#define _s_FCP_NatsPcbTempAd_1               (FCP_2.FCP_2.FCP_NatsPcbTempAd_1)
#define _s_MasterReqB0                       (MasterReq.MasterReq.MasterReqB0)
#define _s_MasterReqB1                       (MasterReq.MasterReq.MasterReqB1)
#define _s_MasterReqB2                       (MasterReq.MasterReq.MasterReqB2)
#define _s_MasterReqB3                       (MasterReq.MasterReq.MasterReqB3)
#define _s_MasterReqB4                       (MasterReq.MasterReq.MasterReqB4)
#define _s_MasterReqB5                       (MasterReq.MasterReq.MasterReqB5)
#define _s_MasterReqB6                       (MasterReq.MasterReq.MasterReqB6)
#define _s_MasterReqB7                       (MasterReq.MasterReq.MasterReqB7)
#define _s_SlaveRespB0                       (SlaveResp.SlaveResp.SlaveRespB0)
#define _s_SlaveRespB1                       (SlaveResp.SlaveResp.SlaveRespB1)
#define _s_SlaveRespB2                       (SlaveResp.SlaveResp.SlaveRespB2)
#define _s_SlaveRespB3                       (SlaveResp.SlaveResp.SlaveRespB3)
#define _s_SlaveRespB4                       (SlaveResp.SlaveResp.SlaveRespB4)
#define _s_SlaveRespB5                       (SlaveResp.SlaveResp.SlaveRespB5)
#define _s_SlaveRespB6                       (SlaveResp.SlaveResp.SlaveRespB6)
#define _s_SlaveRespB7                       (SlaveResp.SlaveResp.SlaveRespB7)


/* -----------------------------------------------------------------------------
    &&&~ Access to signals
 ----------------------------------------------------------------------------- */

#define l_u8_rd_L_AC_LeftSetTemperature()    _s_L_AC_LeftSetTemperature
#define l_u8_wr_L_AC_LeftSetTemperature(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_LeftSetTemperature = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_L_AC_RightSetTemperature()   _s_L_AC_RightSetTemperature
#define l_u8_wr_L_AC_RightSetTemperature(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_RightSetTemperature = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_L_AC_AmbientTemperature()    _s_L_AC_AmbientTemperature
#define l_u8_wr_L_AC_AmbientTemperature(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_AmbientTemperature = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_L_AC_BlowerLevel()           _s_L_AC_BlowerLevel
#define l_u8_wr_L_AC_BlowerLevel(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_BlowerLevel = ((vuint8) (((vuint8) (a)) & 0x0F)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_L_AC_IntakeAirState()        _s_L_AC_IntakeAirState
#define l_u8_wr_L_AC_IntakeAirState(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_IntakeAirState = ((vuint8) (((vuint8) (a)) & 0x0F)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_L_AC_AirDistributionMode()   _s_L_AC_AirDistributionMode
#define l_u8_wr_L_AC_AirDistributionMode(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_AirDistributionMode = ((vuint8) (((vuint8) (a)) & 0x0F)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_AqsState()            _s_L_AC_AqsState
#define l_bool_wr_L_AC_AqsState(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_AqsState = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_DefrostState()        _s_L_AC_DefrostState
#define l_bool_wr_L_AC_DefrostState(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_DefrostState = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_AutoState()           _s_L_AC_AutoState
#define l_bool_wr_L_AC_AutoState(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_AutoState = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_ACCompReq()           _s_L_AC_ACCompReq
#define l_bool_wr_L_AC_ACCompReq(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_ACCompReq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_OnState()             _s_L_AC_OnState
#define l_bool_wr_L_AC_OnState(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_OnState = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_DUALstatus()          _s_L_AC_DUALstatus
#define l_bool_wr_L_AC_DUALstatus(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_DUALstatus = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_MaxACrequset()        _s_L_AC_MaxACrequset
#define l_bool_wr_L_AC_MaxACrequset(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_MaxACrequset = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_SeatHeat_L()          _s_L_AC_SeatHeat_L
#define l_bool_wr_L_AC_SeatHeat_L(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_SeatHeat_L = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_L_AC_Control_Lock_Req()      _s_L_AC_Control_Lock_Req
#define l_u8_wr_L_AC_Control_Lock_Req(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_Control_Lock_Req = ((vuint8) (((vuint8) (a)) & 0x03)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_SeatHeat_R()          _s_L_AC_SeatHeat_R
#define l_bool_wr_L_AC_SeatHeat_R(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_SeatHeat_R = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_L_AC_SeatHeatLevel_R()       _s_L_AC_SeatHeatLevel_R
#define l_u8_wr_L_AC_SeatHeatLevel_R(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_SeatHeatLevel_R = ((vuint8) (((vuint8) (a)) & 0x0F)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_RearDefReq()          _s_L_AC_RearDefReq
#define l_bool_wr_L_AC_RearDefReq(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_RearDefReq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_RearDefActualReq()    _s_L_AC_RearDefActualReq
#define l_bool_wr_L_AC_RearDefActualReq(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_RearDefActualReq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_EconMode()            _s_L_AC_EconMode
#define l_bool_wr_L_AC_EconMode(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_EconMode = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_L_AC_IONRunstatus()          _s_L_AC_IONRunstatus
#define l_u8_wr_L_AC_IONRunstatus(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_IONRunstatus = ((vuint8) (((vuint8) (a)) & 0x03)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_OffMode()             _s_L_AC_OffMode
#define l_bool_wr_L_AC_OffMode(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_OffMode = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_L_AC_InCarAirCondition()     _s_L_AC_InCarAirCondition
#define l_u8_wr_L_AC_InCarAirCondition(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_InCarAirCondition = ((vuint8) (((vuint8) (a)) & 0x03)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_System_1S()           _s_L_AC_System_1S
#define l_bool_wr_L_AC_System_1S(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_System_1S = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_PowerFail()           _s_L_AC_PowerFail
#define l_bool_wr_L_AC_PowerFail(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_PowerFail = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_bool_rd_L_AC_IONdetectEnable()     _s_L_AC_IONdetectEnable
#define l_bool_wr_L_AC_IONdetectEnable(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_L_AC_IONdetectEnable = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_L_FCP_LeftTempUp()           _s_L_FCP_LeftTempUp
#define l_u8_wr_L_FCP_LeftTempUp(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_LeftTempUp = ((vuint8) (((vuint8) (a)) & 0x0F)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_u8_rd_L_FCP_LeftTempDown()         _s_L_FCP_LeftTempDown
#define l_u8_wr_L_FCP_LeftTempDown(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_LeftTempDown = ((vuint8) (((vuint8) (a)) & 0x0F)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_u8_rd_L_FCP_RightTempUp()          _s_L_FCP_RightTempUp
#define l_u8_wr_L_FCP_RightTempUp(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_RightTempUp = ((vuint8) (((vuint8) (a)) & 0x0F)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_u8_rd_L_FCP_RightTempDown()        _s_L_FCP_RightTempDown
#define l_u8_wr_L_FCP_RightTempDown(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_RightTempDown = ((vuint8) (((vuint8) (a)) & 0x0F)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_u8_rd_L_FCP_Blowup()               _s_L_FCP_Blowup
#define l_u8_wr_L_FCP_Blowup(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_Blowup = ((vuint8) (((vuint8) (a)) & 0x0F)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_u8_rd_L_FCP_BlowDown()             _s_L_FCP_BlowDown
#define l_u8_wr_L_FCP_BlowDown(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_BlowDown = ((vuint8) (((vuint8) (a)) & 0x0F)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_Heatreq()            _s_L_FCP_Heatreq
#define l_bool_wr_L_FCP_Heatreq(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_Heatreq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_ModeDown()           _s_L_FCP_ModeDown
#define l_bool_wr_L_FCP_ModeDown(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_ModeDown = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_ModeUp()             _s_L_FCP_ModeUp
#define l_bool_wr_L_FCP_ModeUp(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_ModeUp = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_AUTOreq()            _s_L_FCP_AUTOreq
#define l_bool_wr_L_FCP_AUTOreq(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_AUTOreq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_Acreq()              _s_L_FCP_Acreq
#define l_bool_wr_L_FCP_Acreq(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_Acreq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_DualReq()            _s_L_FCP_DualReq
#define l_bool_wr_L_FCP_DualReq(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_DualReq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_MaxAcReq()           _s_L_FCP_MaxAcReq
#define l_bool_wr_L_FCP_MaxAcReq(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_MaxAcReq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_DefrostReq()         _s_L_FCP_DefrostReq
#define l_bool_wr_L_FCP_DefrostReq(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_DefrostReq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_RearDefReq()         _s_L_FCP_RearDefReq
#define l_bool_wr_L_FCP_RearDefReq(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_RearDefReq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_CycleReq()           _s_L_FCP_CycleReq
#define l_bool_wr_L_FCP_CycleReq(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_CycleReq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_LeftSeatHeatReq()    _s_L_FCP_LeftSeatHeatReq
#define l_bool_wr_L_FCP_LeftSeatHeatReq(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_LeftSeatHeatReq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_RightSeatHeatReq()   _s_L_FCP_RightSeatHeatReq
#define l_bool_wr_L_FCP_RightSeatHeatReq(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_RightSeatHeatReq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_EconReq()            _s_L_FCP_EconReq
#define l_bool_wr_L_FCP_EconReq(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_EconReq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_IONreq()             _s_L_FCP_IONreq
#define l_bool_wr_L_FCP_IONreq(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_IONreq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_bool_rd_L_FCP_OffModereq()         _s_L_FCP_OffModereq
#define l_bool_wr_L_FCP_OffModereq(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_L_FCP_OffModereq = ((vuint8) (((vuint8) (a)) & 0x01)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_u16_rd_FCP_NatsIrAd()              ((vuint16) (((vuint16) (_s_FCP_NatsIrAd_1) << 8) | ((vuint16) (_s_FCP_NatsIrAd_0))))
#define l_u16_wr_FCP_NatsIrAd(a) \
{ \
  { \
    LinStartTxSignalWriteSync(); \
    _s_FCP_NatsIrAd_0 = ((vuint8) (((vuint16) (a)) & 0xFF)); \
    _s_FCP_NatsIrAd_1 = ((vuint8) ((((vuint16) (a)) & 0x0300) >> 8)); \
    LinEndTxSignalWriteSync(); \
  } \
}
#define l_u16_rd_FCP_NatsTempAd()            ((vuint16) (((vuint16) (_s_FCP_NatsTempAd_1) << 6) | ((vuint16) (_s_FCP_NatsTempAd_0))))
#define l_u16_wr_FCP_NatsTempAd(a) \
{ \
  { \
    LinStartTxSignalWriteSync(); \
    _s_FCP_NatsTempAd_0 = ((vuint8) (((vuint16) (a)) & 0x3F)); \
    _s_FCP_NatsTempAd_1 = ((vuint8) ((((vuint16) (a)) & 0x03C0) >> 6)); \
    LinEndTxSignalWriteSync(); \
  } \
}
#define l_u16_rd_FCP_NatsPcbTempAd()         ((vuint16) (((vuint16) (_s_FCP_NatsPcbTempAd_1) << 4) | ((vuint16) (_s_FCP_NatsPcbTempAd_0))))
#define l_u16_wr_FCP_NatsPcbTempAd(a) \
{ \
  { \
    LinStartTxSignalWriteSync(); \
    _s_FCP_NatsPcbTempAd_0 = ((vuint8) (((vuint16) (a)) & 0x0F)); \
    _s_FCP_NatsPcbTempAd_1 = ((vuint8) ((((vuint16) (a)) & 0x03F0) >> 4)); \
    LinEndTxSignalWriteSync(); \
  } \
}
#define l_u8_rd_MasterReqB0()                _s_MasterReqB0
#define l_u8_wr_MasterReqB0(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_MasterReqB0 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_MasterReqB1()                _s_MasterReqB1
#define l_u8_wr_MasterReqB1(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_MasterReqB1 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_MasterReqB2()                _s_MasterReqB2
#define l_u8_wr_MasterReqB2(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_MasterReqB2 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_MasterReqB3()                _s_MasterReqB3
#define l_u8_wr_MasterReqB3(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_MasterReqB3 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_MasterReqB4()                _s_MasterReqB4
#define l_u8_wr_MasterReqB4(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_MasterReqB4 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_MasterReqB5()                _s_MasterReqB5
#define l_u8_wr_MasterReqB5(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_MasterReqB5 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_MasterReqB6()                _s_MasterReqB6
#define l_u8_wr_MasterReqB6(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_MasterReqB6 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_MasterReqB7()                _s_MasterReqB7
#define l_u8_wr_MasterReqB7(a) \
{ \
  LinStartRxBitSignalReadSync(); \
  _s_MasterReqB7 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndRxBitSignalReadSync(); \
}
#define l_u8_rd_SlaveRespB0()                _s_SlaveRespB0
#define l_u8_wr_SlaveRespB0(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_SlaveRespB0 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_u8_rd_SlaveRespB1()                _s_SlaveRespB1
#define l_u8_wr_SlaveRespB1(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_SlaveRespB1 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_u8_rd_SlaveRespB2()                _s_SlaveRespB2
#define l_u8_wr_SlaveRespB2(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_SlaveRespB2 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_u8_rd_SlaveRespB3()                _s_SlaveRespB3
#define l_u8_wr_SlaveRespB3(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_SlaveRespB3 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_u8_rd_SlaveRespB4()                _s_SlaveRespB4
#define l_u8_wr_SlaveRespB4(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_SlaveRespB4 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_u8_rd_SlaveRespB5()                _s_SlaveRespB5
#define l_u8_wr_SlaveRespB5(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_SlaveRespB5 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_u8_rd_SlaveRespB6()                _s_SlaveRespB6
#define l_u8_wr_SlaveRespB6(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_SlaveRespB6 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndTxBitSignalReadSync(); \
}
#define l_u8_rd_SlaveRespB7()                _s_SlaveRespB7
#define l_u8_wr_SlaveRespB7(a) \
{ \
  LinStartTxBitSignalReadSync(); \
  _s_SlaveRespB7 = ((vuint8) (((vuint8) (a)) & 0xFF)); \
  LinEndTxBitSignalReadSync(); \
}


/* -----------------------------------------------------------------------------
    &&&~ Access to data bytes of Rx messages
 ----------------------------------------------------------------------------- */

/* ID: 0x01, Handle: 0, Name: AC_1 */
#define c1_AC_1_c                            (AC_1._c[0])
#define c2_AC_1_c                            (AC_1._c[1])
#define c3_AC_1_c                            (AC_1._c[2])
#define c4_AC_1_c                            (AC_1._c[3])
#define c5_AC_1_c                            (AC_1._c[4])
#define c6_AC_1_c                            (AC_1._c[5])
#define c7_AC_1_c                            (AC_1._c[6])
#define c8_AC_1_c                            (AC_1._c[7])



/* -----------------------------------------------------------------------------
    &&&~ Access to data bytes of Tx messages
 ----------------------------------------------------------------------------- */

/* ID: 0x11, Handle: 1, Name: FCP_1 */
#define c1_FCP_1_c                           (FCP_1._c[0])
#define c2_FCP_1_c                           (FCP_1._c[1])
#define c3_FCP_1_c                           (FCP_1._c[2])
#define c4_FCP_1_c                           (FCP_1._c[3])
#define c5_FCP_1_c                           (FCP_1._c[4])
#define c6_FCP_1_c                           (FCP_1._c[5])
#define c7_FCP_1_c                           (FCP_1._c[6])
#define c8_FCP_1_c                           (FCP_1._c[7])

/* ID: 0x03, Handle: 2, Name: FCP_2 */
#define c1_FCP_2_c                           (FCP_2._c[0])
#define c2_FCP_2_c                           (FCP_2._c[1])
#define c3_FCP_2_c                           (FCP_2._c[2])
#define c4_FCP_2_c                           (FCP_2._c[3])
#define c5_FCP_2_c                           (FCP_2._c[4])
#define c6_FCP_2_c                           (FCP_2._c[5])
#define c7_FCP_2_c                           (FCP_2._c[6])
#define c8_FCP_2_c                           (FCP_2._c[7])



/* -----------------------------------------------------------------------------
    &&&~ Prototypes of Precopy Functions
 ----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
    &&&~ Prototypes of Indication Functions
 ----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
    &&&~ Prototypes of Confirmation Functions
 ----------------------------------------------------------------------------- */
extern vuint8 Panel_info_FCP_1(vuint8* txBuffer);
extern vuint8 Panel_info_FCP_2 (vuint8* txBuffer);


/* -----------------------------------------------------------------------------
    &&&~ Prototypes of Pretransmit Functions
 ----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
    &&&~ Message Handles
 ----------------------------------------------------------------------------- */

#define LinRxAC_1                            0
#define LinTxFCP_1                           1
#define LinTxFCP_2                           2
#define LinRxMasterReq                       3
#define LinTxSlaveResp                       4


/* -----------------------------------------------------------------------------
    &&&~ Declaration of objects provided by lin_par.c
 ----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
    &&&~ Name defines for LIN channel
 ----------------------------------------------------------------------------- */

#ifndef Channel1
#define Channel1                             0
#endif




/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 258965458
      #error "The magic number of the generated file <D:\uidq0188\Desktop\New folder\lin_par.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 258965458
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __LIN_PAR_H__ */
