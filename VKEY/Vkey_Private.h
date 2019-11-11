/***************************************************************************************************
                                       VKEY PROCESS
  .File Name: VKEY_Private.h
  
  .Description: Thie file is used to include the macro used for Vkey module only.

  --------------------------------------------------------------------------------------------------
  Version     Date            Author            Change

  --------------------------------------------------------------------------------------------------
  Rev 1.0     2015/03/26      Xu Xianglin     	The first version            
***************************************************************************************************/
#ifndef VKEY_PRIVATE_H
#define VKEY_PRIVATE_H

/* System-headerfiles */

/* Foreign headerfiles */

/* Own headerfiles */

/***************************************************************************************************
                                    EXTERNAL MODULE INTERFACE
***************************************************************************************************/
#define VKEY_u8GetLowPowValue()			           (uint8)POW_u16GetValue(POW_nu16AppLowVoltage)
#define VKEY_u8GetHighPowValue()	               (uint8)POW_u16GetValue(POW_nu16AppHighVoltage)

#define VKEY_u8GetFLeftSetTemp()                   (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_LeftSetTemp)                   
#define VKEY_u8GetFRightSetTemp()                  (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_RightSetTemp)
#define VKEY_u8GetMode()                           (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_AirDistributionModeReq)
#define VKEY_u8GetBlowerSpd()                      (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_BlowerFanLevel)
//#define VKEY_u8GetAutoKey()                (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_AutoKey)
//#define VKEY_u8GetAcKey()                  (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_AcKey)
//#define VKEY_u8GetAqsKey()                 (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_AqsKey)
//#define VKEY_u8GetRfaKey()                 (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_FreshReciKey)
//#define VKEY_u8GetOffKey()                 (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_AirConditionerPowerKey)
//#define VKEY_u8GetDefKey()                 (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_FrontDefrostKey)
#define VKEY_u8GetPm25PopupOperationSts()  (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_PM25PopupOperationSts)
//#define VKEY_u8GetIonKey()                 (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_IONIZERKey)
//#define VKEY_u8GetDualKey()                (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_DualKey)
//#define VKEY_u8GetPM25Key()                (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_PM25Key)
#define VKEY_u8GetPM25PopupActiveKey()     (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_PM25PopupActive)

#define VKEY_u8GetTboxAirCleanerReq()                (uint8)CANAPP_u16GetValue(CANAPP_nu16TBOX_AirCleanerReq)
#define VKEY_u8GetTboxTempReq()                (uint8)CANAPP_u16GetValue(CANAPP_nu16TBOX_TempReq)
#define VKEY_u8GetTboxAirConditionerReq()     (uint8)CANAPP_u16GetValue(CANAPP_nu16TBOX_AirConditionerReq)

#define VKEY_u8GetDrvHeaReq()              (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_DrvHeatReq)
#define VKEY_u8GetPassHeaReq()             (uint8)CANAPP_u16GetValue(CANAPP_nu16MMI_PassHeatReq)

/***************************************************************************************************
                                    INTERNAL MODULE INTERFACE
***************************************************************************************************/
/*
typedef struct {
const VKEY_tenID 	enKeyID;
const uint8     	u8MinValidValue;
const uint8     	u8MaxValidValue;
uint8               u8CurrStatus;
uint8               u8LastStatus;
uint8 				u8PressTimer;
const uint8         u8ResponseTime;
uint8               boKeyValib;
const uint8	        u8Group;
const uint8         u8Priority;
const uint8         u8Attr;
}VKEY_stATTRIBUTE;
*/
#define VKEY_nAttribute \
{\
    /*KeyID*/        /*Min*/ /*Max*/ /*PressTimer*/ /*FilterTime*/ /*FirstRespTime*/\
	{VKEY_nFLeftSetTemp,    0x00,	0x1E,   0xffU, 0xffU,   0xffU,   1U, False,0U, 1U ,1U },\
    {VKEY_nFRightSetTemp,   0x00,	0x1E,   0xffU, 0xffU,   0xffU,   1U, False,0U, 1U ,1U },\
	{VKEY_nBlowerSpd,       0x00,   0x08,   0xffU, 0xffU,   0xffU,   1U, False,0U, 1U ,1U },\
	{VKEY_nMode,	        0x00,   0x04,   0xffU, 0xffU,   0xffU,   1U, False,0U, 1U ,1U },\
    {VKEY_nPM25PopupOperationSts,   0x00,   0x03,   0xffU, 0xffU,   0xffU,   1U, False,0U, 1U ,1U },\
    {VKEY_nDrvHeaReq,       0x00,   0x07,   0xffU, 0xffU,   0xffU,   1U, False,0U, 1U ,1U },\
    {VKEY_nPassHeaReq,      0x00,   0x07,   0xffU, 0xffU,   0xffU,   1U, False,0U, 1U ,1U },\
    {VKEY_nPM25PopupActive,          0x00,   0x01,   0xffU, 0xffU,   0xffU,   1U, False,0U, 1U ,1U },\
    {VKEY_nAirCleanerReq,   0x00,   0x03,   0xffU, 0xffU,   0xffU,   1U, False,0U, 1U ,0U },\
    {VKEY_nTempReq,       0x00,   0x1E,   0xffU, 0xffU,   0xffU,   1U, False,0U, 1U ,1U },\
    {VKEY_nAirConditionerReq,      0x00,   0x03,   0xffU, 0xffU,   0xffU,   1U, False,0U, 1U ,1U },\
}


#define VKEY_PressedKey                   VKEY_au16Array[VKEY_nu16PressedKey]
#define VKEY_RawKey                       VKEY_au16Array[VKEY_nu16RawKey]
#define VKEY_ErrorCode                    VKEY_au16Array[VKEY_nu16ErrorCode]

#define VKEY_u8FLeftSetTemp               VKEY_au8Array[VKEY_nu8FLeftSetTemp]
#define VKEY_u8FRightSetTemp              VKEY_au8Array[VKEY_nu8FRightSetTemp]
#define VKEY_u8Mode                       VKEY_au8Array[VKEY_nu8Mode]
#define VKEY_u8BlowerSpd                  VKEY_au8Array[VKEY_nu8BlowerSpd]
#define VKEY_u8SwVersion                  VKEY_au8Array[VKEY_nu8SwVersion]

#define VKeyGetCcpForceBit(index)	((VKEY_CcpForceFlag>>index)&0x01)
#define VKeySetCcpForceBit(index)	(VKEY_CcpForceFlag=VKEY_CcpForceFlag|(0x01<<index))
#define VKeyClrCcpForceBit(index)	(VKEY_CcpForceFlag=VKEY_CcpForceFlag&(~(0x01<<index)))
#define VKeyClrCcpForceByte(void)	(VKEY_CcpForceFlag=0)
#endif                              
/***************************************************************************************************
                                            END
***************************************************************************************************/
