/**************************** .FILE_HEADER_BEGIN *****************************
 .FILE; [ CANAPP.h]
 .Author; [ Liu Fuguang]
 .Date; 2018-5-17
 .Update Time; 15:50:30
 .Gen File Name: Geely GE12_V1.3.11_CAN.xlsx
 .**************   Change History ********************************************* 
 .V2.0 (Release Date:2017-4-17)
 .1.Creation
 .V2.1 (Release Date:2017-4-18)
 .1.Add static uint16 CANAPP_u16SendMsgTimer_20ms
 .2.Add static uint16 CANAPP_u16SendMsgTimer_40ms
 .3.Add static uint16 CANAPP_u16SendMsgTimer_500ms
 .V2.2 (Release Date:2017-4-22)
 .1.Update *Update Content Of Send Message* Module 
 .***************************************************************************** 
****************************** .FILE_HEADER_END ******************************/

#ifndef CANAPP_H
#define CANAPP_H

#ifndef CANAPP_C
    #define ext extern
#else
    #define ext
#endif

/* Define CAN uint16 receive signals enum...*/
typedef enum CANAPP_enu16VarNumber
{
        /* Signals from message PEPS_Message_Sts...*/
        CANAPP_nu16PEPS_PowerModeValidity = 0,
        CANAPP_nu16PEPS_PowerMode,
        CANAPP_nu16PEPS_RemoteControlSt,
        /* Signals from message EMS_EngineRPM...*/
        CANAPP_nu16EMS_EngineSpeedRPM,
        CANAPP_nu16EMS_SSMStatus,
        CANAPP_nu16EMS_EngineSpeedRPMInvalid,
        CANAPP_nu16EMS_EngStatus,
        /* Signals from message EMS_EngineDriverInfo...*/
        CANAPP_nu16EMS_EngineCoolantTemp,
        CANAPP_nu16EMS_EngineCoolantTempInvalid,
        /* Signals from message EMS_EngineStatus...*/
        CANAPP_nu16EMS_ACStatus,
        /* Signals from message ESC_Status...*/
        CANAPP_nu16ESC_VehicleSpeed,
        CANAPP_nu16ESC_VehicleSpeedInvalid,
        /* Signals from message MMI_HVSM_Command...*/
        CANAPP_nu16MMI_DrvHeatReq,
        CANAPP_nu16MMI_PassHeatReq,
        /* Signals from message MMI_AC_Command...*/
        CANAPP_nu16MMI_AutoKey,
        CANAPP_nu16MMI_FrontDefrostKey,
        CANAPP_nu16MMI_FreshReciKey,
        CANAPP_nu16MMI_AqsKey,
        CANAPP_nu16MMI_AcKey,
        CANAPP_nu16MMI_BlowerFanLevel,
        CANAPP_nu16MMI_DualKey,
        CANAPP_nu16MMI_PM25Key,
        CANAPP_nu16MMI_IONIZERKey,
        CANAPP_nu16MMI_AirDistributionModeReq,
        CANAPP_nu16MMI_PM25PopupActive,
        CANAPP_nu16MMI_AirConditionerPowerKey,
        CANAPP_nu16MMI_LeftSetTemp,
        CANAPP_nu16MMI_RightSetTemp,
        CANAPP_nu16MMI_PM25PopupOperationSts,
        /* Signals from message TBOX_RemCon...*/
        CANAPP_nu16TBOX_Inquire_PM25,
        CANAPP_nu16TBOX_AirCleanerReq,
        CANAPP_nu16TBOX_TempReq,
        CANAPP_nu16TBOX_AirConditionerReq,
        CANAPP_nu16Max
}CANAPP_tenu16VarNumber;

/* Define CAN uint32 receive signals enum...*/
typedef enum CANAPP_enu32VarNumber
{
        /* Signals from message IPK_TotalOdometer...*/
        CANAPP_nu32IPK_IPKTotalOdometer,
        CANAPP_nu32ErrorCode,
        CANAPP_nu32MsgNeverRecFlg,
        CANAPP_nu32MsgDlcErr,
        CANAPP_nu32Max
}CANAPP_tenu32VarNumber;

/* Define all messages identifier enum number...*/
enum
{
        CANAPP_nbiPEPS_Message_Sts_0x1E2,
        CANAPP_nbiEMS_EngineRPM_0x85,
        CANAPP_nbiEMS_EngineDriverInfo_0x288,
        CANAPP_nbiEMS_EngineStatus_0x86,
        CANAPP_nbiESC_Status_0x125,
        CANAPP_nbiMMI_HVSM_Command_0x2A3,
        CANAPP_nbiMMI_AC_Command_0x2A5,
        CANAPP_nbiIPK_TotalOdometer_0x3F1,
        CANAPP_nbiTBOX_RemCon_0x292,
        CANAPP_nbiNumberRevMesg
};
/* Const code area...*/

enum
{
  //CANNMAPP_nDiagFun = 0/* ID: 0x000007df, Handle: 0, Func_DiagReq [BC] */, 
  //CANNMAPP_nDiagReq /* ID: 0x000007c6, Handle: 1, AC_DiagReq [BC] */, 
  //CANNMAPP_nCalibration /* ID: 0x000006b1, Handle: 2, CCP_Calibration_Write [BC] */, 
  CANAPP_nEmsRPM /* ID: 0x00000085, Handle: 3, EMS_EngineRPM [BC] */, 
  CANAPP_nIpk /* ID: 0x000003f1, Handle: 4, IPK_TotalOdometer [FC] */, 
  CANAPP_nMmiAc /* ID: 0x000002a5, Handle: 5, MMI_AC_Command [FC] */, 
  CANAPP_nMmiHvsm /* ID: 0x000002a3, Handle: 6, MMI_HVSM_Command [FC] */, 
  CANAPP_nTbox /* ID: 0x00000292, Handle: 7, TBOX_RemCon [FC] */, 
  CANAPP_nEmsDrv /* ID: 0x00000288, Handle: 8, EMS_EngineDriverInfo [FC] */, 
  CANAPP_nPeps /* ID: 0x000001e2, Handle: 9, PEPS_Message_Sts [FC] */, 
  CANAPP_nEsc /* ID: 0x00000125, Handle: 10, ESC_Status [FC] */, 
  CANAPP_nEmsEng /* ID: 0x00000086, Handle: 11, EMS_EngineStatus [FC] */,
  CANAPP_nMax
};
ext void CANAPP_vReset(void);
ext void CANAPP_vMain_10ms(void);
ext void CANAPP_vClearMsgMissError(void);
ext void CANAPP_vClearSendMsgTmr(void);
/* Interface for supporting data to other modules */
ext uint16 CANAPP_u16GetValue(CANAPP_tenu16VarNumber enIndex);
ext uint32 CANAPP_u32GetValue(CANAPP_tenu32VarNumber enIndex);
ext void CANAPP_vSendMsg_AC_LIN2CANData_0x6B3(uint8 Data_0,uint8 Data_1,\
	uint8 Data_2,uint8 Data_3,uint8 Data_4,uint8 Data_5,uint8 Data_6,uint8 Data_7);
ext void CANAPP_vSendMsg_AC_LIN2CANCom_0x6B0(uint8 Data_0,uint8 Data_1,\
	uint8 Data_2,uint8 Data_3,uint8 Data_4,uint8 Data_5,uint8 Data_6,uint8 Data_7);
#undef ext
#endif



