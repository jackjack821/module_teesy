/*******************************************************************************
| Module Name: Ion Control
| File Name: Ion_Private.h
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2015 Huizhou Desay SV Automotive Co., Ltd.    All rights reserved.
|
| This software is copyright protected and proprietary to Desay SV Automotive Co., Ltd.
| Desay SV Automotive Co., Ltd grants to you only those rights as set out in the
| license conditions. All other rights remain with Desay SV Automotive Co., Ltd.
|
| REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
|-------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Name                                  Company
| ---------------------     ---------------------------------------
| Yang Shengli                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-02-25  1.00        Yang Shengli      First implementation
********************************************************************************/

#ifndef ION_PRIVATE_H
#define ION_PRIVATE_H

#include "Ccp.h"
#include "Ccp_cfg.h"

/*****************************************************************************
*Macro define
******************************************************************************/
#define ION_nSwVersion					(0xA1u)

#define ION_u8SwVersion					ION_au8Array[ION_nu8SwVersion]
#define ION_u8PM25StsReq				ION_au8Array[ION_nu8PM25StsReq]
#define ION_u8IONStsReq					ION_au8Array[ION_nu8IONStsReq]
#define ION_u8PM25Sts						ION_au8Array[ION_nu8PM25Sts]
#define ION_u8PM25ErrSts				ION_au8Array[ION_nu8PM25ErrSts]
#define ION_u8IONErrSts					ION_au8Array[ION_nu8IONErrSts]
#define ION_u8IONIZEState				ION_au8Array[ION_nu8IONIZEState]
#define ION_u8AirOutQLevel				ION_au8Array[ION_nu8AirOutQLevel]
#define ION_u8AirInQLevel				ION_au8Array[ION_nu8AirInQLevel]
#define ION_u8ErrorCode1				ION_au8Array[ION_nu8ErrorCode1]
#define ION_u8ErrorCode2				ION_au8Array[ION_nu8ErrorCode2]
#define ION_u8SleepFlag					ION_au8Array[ION_nu8SleepFlag]
#define ION_u8TboxRequest				ION_au8Array[ION_nu8TboxRequest]
#define ION_u8PM25Exceed				ION_au8Array[ION_nu8PM25Exceed]
#define ION_u8PM25PopupReq				ION_au8Array[ION_nu8PM25PopupReq]
#define ION_u8AirInQuality            ION_au8Array[ION_nu8AirInQuality]
#define ION_u16PM25OutDen			ION_au16Array[ION_nu16PM25OutDen]
#define ION_u16PM25InDen				ION_au16Array[ION_nu16PM25InDen]
#define ION_u16ErrorCode				ION_au16Array[ION_nu16ErrorCode]
#define ION_u8PM25EnableCheckLostDtc	ION_au8Array[ION_nu8PM25EnableCheckLostDtc]

#define IonReqMax (2)
#define IonReqMin (0)
#define IonStsMax (1)
#define IonStsMin (0)
#define IonErrStsMax (3)
#define IonErrStsMin (0)
#define IonDigMax (1023)
#define IonDigMin (600)
#define Pm25InDenMax (999)
#define Pm25InDenMin (0)
#define Pm25OutDenMax (999)
#define Pm25OutDenMin (0)
#define PmAirInQLevelMax (5)
#define PmAirInQLevelMin (0)
#define PmAirOutQLevelMax (5)
#define PmAirOutQLevelMin (0)
#define Pm25StsMax (3) /*160811*/
#define Pm25StsMin (0)
#define Pm25ErrStsMax (3)
#define Pm25ErrStsMin (0)
#define EngineRunning (3)
#define IonAutoRunTime (300)
#define Pm25UpdateTime (600)
#define IonReqIonizerOffPoint (50)
#define IonReqOpenIonizerOnPoint (75)
#define PM25_nTboxMaxReqTime                (1200U) /*120 sec*/
#define PM25_nPm25NoteLostWaitTime            (50U)  /*- 5 seconds-*/

#define PM25_nAirBadQaulity  (75) /*75 ug/m3*/
#define PM25_nAirGoodQaulity  (50) /*50 ug/m3*/

#define PM25_nAirBadTime  (100) /*10 sec*/
#define PM25_nAirGoodTime  (80) /*10-8 = 2sec*/
#define IonDelayRunTime (50) /*5 sec after bad airexceed*/

#define ION_PM25DenDefault  (0xFFF)

#define PM25_Pm25Inside_LittleBadLevel	        150
#define PM25_Pm25Inside_VeryBadLevel	        200

/*Get value from other modules*/
#define ION_u8GetPowLowValue()	POW_u16GetValue(POW_nu16AppLowVoltage)
#define ION_u8GetPowHighValue()	POW_u16GetValue(POW_nu16AppHighVoltage)
#define ION_u8GetAirCleanerReq()	CANAPP_u16GetValue(CANAPP_nu16TBOX_Inquire_PM25)
//#define ION_u8GetIONSts()			LINAPP_u16GetValue(LIN_nu16IONSts) // Rte_IRead_Ion_vMain_Ion_LinAppIonSts_u8State()
//#define ION_u8GetIONErrSts()		LINAPP_u16GetValue(LIN_nu16IONErrSts) //Rte_IRead_Ion_vMain_Ion_LinAppIonErrSts_u8State()
#define ION_u16GetPM25InDen()	LINAPP_u16GetValue(LIN_nu16L_PM25_InDen) //Rte_IRead_Ion_vMain_Ion_LinAppPM25InDen_u16LinAppPM25Den()
#define ION_u16GetPM25OutDen()	LINAPP_u16GetValue(LIN_nu16L_PM25_OutDen) //Rte_IRead_Ion_vMain_Ion_LinAppPM25OutDen_u16LinAppPM25Den()
#define ION_u8GetPM25ErrSts()	LINAPP_u16GetValue(LIN_nu16L_PM25_ErrSts) //Rte_IRead_Ion_vMain_Ion_LinAppPM25ErrSts_u8State()
#define ION_u8GetPM25Sts()		LINAPP_u16GetValue(LIN_nu16L_PM25_Sts) //Rte_IRead_Ion_vMain_Ion_LinAppPM25Sts_u8State() /*ITP103,160802*/
#define ION_u8GetAirInQLevel()	LINAPP_u16GetValue(LIN_nu16L_PM25_AirInQLevel) //Rte_IRead_Ion_vMain_Ion_LinAppAirInQLevel_u8IonAirQLevel()
#define ION_u8GetAirOutQLevel()	LINAPP_u16GetValue(LIN_nu16L_PM25_AirOutQLevel) //Rte_IRead_Ion_vMain_Ion_LinAppAirOutQLevel_u8IonAirQLevel()
#define ION_u8GetMmiIonCtrl()		MMI_u8GetValue(MMI_nu8IonCtrl)
#define ION_u8GetMmiIonMode()	MMI_u8GetValue(MMI_nu8IonMode)
#define ION_u16Get1000MsFlag()   FRAME_u16GetValue(SYS_nu16Flag1000MS_BG) //Rte_IRead_Ion_vMain_Ion_SysFlag1000msBG_u16Flag()
#define ION_u8GetION_DIG(value)	Rte_Call_IoHwAd_IoHwAd_ReadAd_IonDiag_Read(value)
/*Control PM2.5 power*/
#define ION_vWritePm25PinLevel(level) Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_IonPM25Ctrl_Write(level);
#define ION_vWriteIonModePinLevel(level) Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_IonMode_Write(level);
#define ION_vWriteCleanModePinLevel(level) Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_CleanMode_Write(level);

#define ION_nUseIonCfg                  (DIAG_u8GetValue(DIAG_nu8IONMount))
#define ION_nUsePm25Cfg                (DIAG_u8GetValue(DIAG_nu8PM25Mount))
#define PM25_FirstPopupCycle	        50 /*5s*/
#define PM25_PopupKeepTime	        3 /*300ms*/
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef ION_PRIVATE_H */
/*****************************************************************************
* EOF: Ion_Private.h
******************************************************************************/
