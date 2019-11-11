/**************************** .FILE_HEADER_BEGIN *****************************
 .FILE; [ LINAPP1c1.c]
 .Author; [ Chen Yudong]
 .Date; 2017/10/12
 .Update Time; 13:37:47
 .**************   Change History ********************************************* 
 .V2.0 (Release Date:2017-4-3)
 .1.Creation
 .V2.1 (Release Date:2017-4-6)
 .1.Add u32GetValue Interface in LINAPP.C.
 .2.Add u32GetValue Interface in LINAPP.h.
 .V2.2 (Release Date:2017-4-8)
 .1.Add vClearMessCnt Interface in LINAPP.C.
 .***************************************************************************** 
 .Gen File Name: Geely GE12_LIN_V1.31_20170624.xlsx
****************************** .FILE_HEADER_END ******************************/

#ifndef LINAPP_CFG_H
#define LINAPP_CFG_H
#ifndef LINAPP
#define ext extern
#else
#define ext
#endif
#define LIN_u8DefaultNeverSuc  (0xFE)
#define LIN_u8DefaultLeast1stSuc (0xFF)
#define LIN_u16DefaultNeverSuc  (0xFFFE)
#define LIN_u16DefaultLeast1stSuc (0xFFFF)

/* Signals from AC_1...*/
#define LINAPP_Int_L_AC_LeftSetTemperature MMI_u8GetValue(MMI_nu8SetTempDr)
#define LINAPP_Int_L_AC_RightSetTemperature MMI_u8GetValue(MMI_nu8SetTempPs)
#define LINAPP_Int_L_AC_AmbientTemperature OAT_u16GetValue(OAT_nu16Display)
#define LINAPP_Int_L_AC_BlowerLevel MMI_u8GetValue(MMI_nu8BlwControl)
#define LINAPP_Int_L_AC_IntakeAirState ((MMI_u8GetValue(MMI_nu8RecirControl))+0x01)
#define LINAPP_Int_L_AC_AirDistributionMode (MMI_u8GetValue(MMI_nu8AirdControl))
#define LINAPP_Int_L_AC_DefrostState (MMI_u8GetValue(MMI_nu8SysState)==MMI_nSysStateDefrost?1:0)
#define LINAPP_Int_L_AC_AutoState (MMI_u8GetValue(MMI_nu8SysState)==MMI_nSysStateAuto?1:0)
#define LINAPP_Int_L_AC_ACCompReq (ACCC_u8GetValue(ACCC_nu8AcDisplay))
#define LINAPP_Int_L_AC_OnState (ACCC_u8GetValue(ACCC_nu8AcActualRequest))
#define LINAPP_Int_L_AC_MaxACrequset (MMI_u8GetValue(MMI_nu8SysState)==MMI_nSysStateMaxAc?1:0)
#define LINAPP_Int_L_AC_SeatHeat_L (SHC_u8GetValue(SHC_nu8LastStateDr))
#define LINAPP_Int_L_AC_SeatHeatLevel_L (SHC_u8GetValue(SHC_nu8DisplayDr))
#define LINAPP_Int_L_AC_SeatHeat_R (SHC_u8GetValue(SHC_nu8LastStatePs))
#define LINAPP_Int_L_AC_SeatHeatLevel_R (SHC_u8GetValue(SHC_nu8DisplayPs))
#define LINAPP_Int_L_AC_RearDefReq (RDC_u8GetValue(RDC_nu8Request))
#define LINAPP_Int_L_AC_RearDefActualReq (RDC_u8GetValue(RDC_nu8Display))
#define LINAPP_Int_L_AC_EconMode 0
#define LINAPP_Int_L_AC_OffMode (BCTL_u8GetValue(BCTL_nu8DisplayInfo)==MMI_nBctlOff?0:1)
#define LINAPP_Int_L_AC_InCarAirCondition (ION_u8GetValue(ION_nu8AirInQuality))
#define LINAPP_Int_L_AC_System_1S (FRAME_u16GetValue(SYS_nu16Flag1000MS_FG))
#define LINAPP_Int_L_AC_PowerFail ((POW_u16GetValue(POW_nu16AppLowVoltage) == True)||(POW_u16GetValue(POW_nu16AppHighVoltage) == True))

/* Signals from AC_2...*/
#define LINAPP_Int_L_AC_PM25StsReq ION_u8GetValue(ION_nu8PM25StsReq)
#define LINAPP_Int_L_AC_CarSpeed (uint8)VEL_u16GetValue(VEL_nu16Velocity)


#undef ext
#endif

