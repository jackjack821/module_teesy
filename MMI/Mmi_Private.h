/*******************************************************************************
| Module Name: Mmi, Man machine interface
| File Name: Mmi_Private.h
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
| Yang Tingyu                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2016-03-08  A1        Yang Tingyu         First implementation
| 

  ,-~~-.___. 
 / |  ' 	\ 
(  )		0 
 \_/-, ,----' 
	====		   // 
   /  \-'~;    /~~~(O)
  /  __/~|	 /		 |
=(	_____| (_________|

********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef MMI_PRIVATE_H
#define MMI_PRIVATE_H


/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */
#include "Mmi_Type.h"


/*******************************************************************************
* EXPORT INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define helpful macros for easy data access and for a comfortable function use, if 
*   necessary.
* - define all macros for accessing the external module interfaces variables
* - define all macros which not need to be configed and changed for this module 
******************************************************************************/

/**************************Extern Module Interface*****************************/
/* example3: define all module external interface functions and defines
   ----------------------------------------------------- */

/*************************No Config Parameter End******************************/
#define MMI_SW_VERSION (0xA1U)
#define MMI_nu8SaveDelayTime (20U)

#define MMI_nUseAqsCfg                  (DIAG_u8GetValue(DIAG_nu8AQSMount))
#define MMI_nUseIonCfg                  (DIAG_u8GetValue(DIAG_nu8IONMount))
#define MMI_nUsePm25Cfg                  (DIAG_u8GetValue(DIAG_nu8PM25Mount))
//#define MMI_nUseRcpCfg                  (DIAG_u8GetValue(DIAG_nu8RCPMount))
/**************************Extern Module Interface Use RTE Start***************/

/****Read Value from RTE*******************************************************/
#define MMI_u8GetPowHighVolFlag       (POW_u16GetValue(POW_nu16AppHighVoltage))
#define MMI_u8GetPowLowVolFlag        (POW_u16GetValue(POW_nu16AppLowVoltage))
#define MMI_u8GetAirdDisplayInfo      (AIRD_u8GetValue(AIRD_nu8Display))
#define MMI_u8GetBctlDisplayInfo      (BCTL_u8GetValue(BCTL_nu8DisplayInfo))
#define MMI_u8GetRfaDisplayInfo       (RFA_u8GetValue(RFA_nu8Display))
#define MMI_u8GetLinAppRearCtrlInfo   (Rte_IRead_Mmi_vMain_Mmi_LinAppRearCtrlinfo_u8State())
#define MMI_u16GetKeyKeyPressed       (KEY_u16PressedKey())//KEY_u16GetValue(KEY_nu16PressedKey)//(Rte_IRead_Mmi_vMain_Mmi_KeyPressed_u16BitMap())
#define MMI_u8GetVkeySetTempLeft      (VKEY_u8GetValue(VKEY_nu8FLeftSetTemp))
#define MMI_u8GetVkeySetTempRight     (VKEY_u8GetValue(VKEY_nu8FRightSetTemp))
#define MMI_u8GetVkeyShcLState        (VKEY_u8GetValue(VKEY_nu8DrvHeaReq))
#define MMI_u8GetVkeyShcRState        (VKEY_u8GetValue(VKEY_nu8PassHeaReq))
#define MMI_u8GetVkeyRearLock         (Rte_IRead_Mmi_vMain_Mmi_VkeyRearKeyLockSet_u8Set())
#define MMI_u8GetVkeyMode             (VKEY_u8GetValue(VKEY_nu8Mode))
#define MMI_u8GetVkeyBlwSpd           (VKEY_u8GetValue(VKEY_nu8BlowerSpd))
#define MMI_u8GetAcccDisplayInfo      (ACCC_u8GetValue(ACCC_nu8AcDisplay))
#define MMI_u16GetVkeyRawValue        (VKEY_u16GetValue(VKEY_nu16PressedKey))
#define MMI_u16GetVkeyPressed         (VKEY_u16GetValue(VKEY_nu16PressedKey))
#define MMI_u8GetIonFilterState()     0xff;/*Interface need to be fixed*///(ION_u8GetValue(value))
#define MMI_u8GetKnobValue(value)     (KNOB_u8Getvalue(value))
#define MMI_u8GetShcRDisplayInfo()    (SHC_u8GetValue(SHC_nu8DisplayPs))
#define MMI_u8GetShcLDisplayInfo()    (SHC_u8GetValue(SHC_nu8DisplayDr))
#define MMI_u8GetRdcValue()           (RDC_u8GetValue(RDC_nu8Display))
#define MMI_u8GetVkeyPm25PopupOperationSts       (VKEY_u8GetValue(VKEY_nu8PM25PopupOerationSts))
#define MMI_u8GetVkeyPm25PopupActive       (VKEY_u8GetValue(VKEY_nu8PM25PopupActive))
#define MMI_u8GetVkeyTboxSetTemp      (VKEY_u8GetValue(VKEY_nu8TempReq))
#define MMI_u8GetVkeyTboxAirCleanerReq      (VKEY_u8GetValue(VKEY_nu8AirCleanerReq))
#define MMI_u8GetVkeyTboxAirConditionerReq      (VKEY_u8GetValue(VKEY_nu8AirConditionerReq))
/****Write Value to RTE*********************************************************/
#define MMI_u8Put2RteSysState(Value)         (Rte_IWrite_Mmi_vMain_MmiMode_u8Set(Value))
#define MMI_u8Put2RteSetTempPs(Value)        (Rte_IWrite_Mmi_vMain_MmiSetTempPs_u8Set(Value))
#define MMI_u8Put2RteSetTempDr(Value)        (Rte_IWrite_Mmi_vMain_MmiSetTempDr_u8Set(Value))
#define MMI_u8Put2RteBctlState(Value)        (Rte_IWrite_Mmi_vMain_MmiBlwMode_u8Set(Value))
#define MMI_u8Put2RteBctlCtrl(Value)         (Rte_IWrite_Mmi_vMain_MmiBlwControl_u8Set(Value))
#define MMI_u8Put2RteAirdState(Value)        (Rte_IWrite_Mmi_vMain_MmiAirdMode_u8Set(Value))
#define MMI_u8Put2RteAirdCtrl(Value)         (Rte_IWrite_Mmi_vMain_MmiAirdControl_u8Set(Value))
#define MMI_u8Put2RteAcState(Value)          (Rte_IWrite_Mmi_vMain_MmiAcMode_u8Set(Value))
#define MMI_u8Put2RteAcCtrl(Value)           (Rte_IWrite_Mmi_vMain_MmiAcControl_u8Set(Value))
#define MMI_u8Put2RteRfaState(Value)         (Rte_IWrite_Mmi_vMain_MmiRecirMode_u8Set(Value))
#define MMI_u8Put2RteRfaCtrl(Value)          (Rte_IWrite_Mmi_vMain_MmiRecirControl_u8Set(Value))
#define MMI_u8Put2RteRearLock(Value)         (Rte_IWrite_Mmi_vMain_MmiRearLockSt_u8State(Value))
#define MMI_u8Put2RteIonState(Value)         (Rte_IWrite_Mmi_vMain_MmiIonMode_u8Set(Value))
#define MMI_u8Put2RteIonCtrl(Value)          (Rte_IWrite_Mmi_vMain_MmiIonControl_u8Set(Value))
#define MMI_u8Put2RteDualCtrl(Value)         (Rte_IWrite_Mmi_vMain_MmiDualSt_u8State(Value))
#define MMI_u8Put2RteRemoteCtrl(Value)       (Rte_IWrite_Mmi_vMain_MmiRemoteControlSt_u8State(Value))
#define MMI_u8Put2RteAirClean(Value)         (Rte_IWrite_Mmi_vMain_MmiAirCleanSt_u8State(Value))
#define MMI_u8Put2RteErrorCode(Value)        (Rte_IWrite_Mmi_vMain_MmiErrorCode_u16BitMap(Value))
#define MMI_u8Put2RteIonMode(Value)          (Rte_IWrite_Mmi_vMain_MmiIonMode_u8Set(Value))
#define MMI_u8Put2RteAqsCtrl(Value)          (Rte_IWrite_Mmi_vMain_MmiAqsControl_u8Set(Value))
#define MMI_u16Put2RteLed1Info(Value)        (Rte_IWrite_Mmi_vMain_MmiLedIndicatorInfo1_u16BitMap(Value))
#define MMI_u16Put2RteLed2Info(Value)        (Rte_IWrite_Mmi_vMain_MmiLedIndicatorInfo2_u16BitMap(Value))
/**************************Extern Module Interface END*************************/
/*
*/
/**************************EEPROM Input Interface******************************/
#define MMI_nMaxKeys            (16U)//(MMI_u8MaxKeys) add mode key,160508,  add rear mode,160521
#define MMI_u8VKkeyMax          (11U)//(MMI_u8VKeyMaxKeys)
#define MMI_nKnobNumber         (4U)

#define MMI_nu8TempMinVal                       (35U)    /**/
#define MMI_nu8TempMaxVal                       (63U)    /**/
#define MMI_u8SetTempInitValue  (44U)//(MMI_nu8SetTempInitValue)
#define MMI_nu8SetTempLow                       (0U)    /**/
#define MMI_nu8SetTempHigh                      (255U)    /**/
#define MMI_nTempStep                           (1U)    /**/

#define MMI_Pm25KeepTime	(20) /*200ms*/
/**************************EEPROM Input Interface END**************************/
/*
*/
/**************************Module Extern output Interface**********************/
#define MMI_u8SwVersion        (MMI_au8Array[MMI_nu8SwVersion])
#define MMI_u16ErrorCode       (MMI_au16Array[MMI_nu16ErrorCode])
#define MMI_u16LcdDispInfo1    (MMI_au16Array[MMI_nu16LcdDispInfo1])
#define MMI_u16LcdDispInfo2    (MMI_au16Array[MMI_nu16LcdDispInfo2])
#define MMI_u16IndiInfo1       (MMI_au16Array[MMI_nu16IndicatorInfo1])
#define MMI_u16IndiInfo2       (MMI_au16Array[MMI_nu16IndicatorInfo2])

#define MMI_u8SysState         (MMI_au8Array[MMI_nu8SysState])
#define MMI_u8DualCtrl         (MMI_au8Array[MMI_nu8DualControl])
#define MMI_u8SetTempDr        (MMI_au8Array[MMI_nu8SetTempDr])
#define MMI_u8SetTempPs        (MMI_au8Array[MMI_nu8SetTempPs])
#define MMI_u8RearDefCtrl      (MMI_au8Array[MMI_nRearDefrost])

#define MMI_u8BctlCtrl         (MMI_au8Array[MMI_nu8BlwControl])				/* 4 The blower control level of current moment, Level 1 to level 8*/
#define MMI_u8BctlState        (MMI_au8Array[MMI_nu8BlwModeControl])			/* 5 The blower control mode of current moment, Auto/Manual/Off*/
#define MMI_u8AcCtrl           (MMI_au8Array[MMI_nu8ACControl])			/* 6 The compress control state of current moment, AC on or Off*/
#define MMI_u8AcState          (MMI_au8Array[MMI_nu8ACMode])					/* 7 The compress control mode of current moment, Auto/Manual/Off*/
#define MMI_u8AirdCtrl         (MMI_au8Array[MMI_nu8AirdControl]) 			/* 8 The air distribute control state of current moment, Face/face&foot/foot/foot&screen*/
#define MMI_u8AirdState        (MMI_au8Array[MMI_nu8AirdModeControl]) 		/* 9 The air distribute control mode of current moment, Auto/Manual/Off*/
#define MMI_u8RfaCtrl          (MMI_au8Array[MMI_nu8RecirControl])			/* 10 The recirculation control state of current moment, Rec or Fre*/
#define MMI_u8RfaState         (MMI_au8Array[MMI_nu8RecirMode])				/* 11 The recirculation control mode of current moment,, Auto/Manual/Off*/
#define MMI_u8IonMode         (MMI_au8Array[MMI_nu8IonMode])			/* 21 The Ion control mode of current moment, Auto/Manual/Off*/
#define MMI_u8IonCtrl          (MMI_au8Array[MMI_nu8IonCtrl])				/* 22 The Ion control state of current moment,, Mute/Auto/High*/
//#define MMI_u8IonNeedReplaceFilter (MMI_au8Array[MMI_nIonNeedReplaceFilter])				/* 22 The Ion control state of current moment,, Mute/Auto/High*/
#define MMI_u8AqsState         (MMI_au8Array[MMI_nu8AqsRequest])
#define MMI_u8ShlCtrl          (MMI_au8Array[MMI_nu8SHL])
#define MMI_u8ShrCtrl          (MMI_au8Array[MMI_nu8SHR])	
#define MMI_u8ShlFromeBusCtrl          (MMI_au8Array[MMI_nu8SHLFromeBus])
#define MMI_u8ShrFromeBusCtrl          (MMI_au8Array[MMI_nu8SHRFromeBus])
#define MMI_u8Pm25PopupOperationSts        (MMI_au8Array[MMI_nPm25PopupOerationSts])

//#define MMI_u8Pm25Switch        (MMI_au8Array[MMI_nPm25Switch])
#define MMI_u8Pm25Enable        (MMI_au8Array[MMI_nPm25Enable])
#define MMI_u8Pm25PopActive        (MMI_au8Array[MMI_nPm25PopActive])
/**************************Module Extern output Interface END *****************/
/*
*/
/************Define these errors statuses ID of Input. ********************** */	
#define Er_nReserve0        (0x0001U)
#define Er_nReserve1        (0x0002U)
#define Er_nReserve2        (0x0004U)
#define Er_nReserve3        (0x0008U)
#define Er_nReserve4        (0x0010U)
#define Er_nReserve5        (0x0020U)
#define Er_nReserve6        (0x0040U)
#define Er_nReserve7        (0x0080U)
#define Er_nReserve8        (0x0100U)
#define Er_nReserve9        (0x0200U)
#define Er_nReserve10       (0x0400U)
#define Er_nReserve11       (0x0800U)
#define Er_nReserve12       (0x1000U)
#define Er_nReserve13       (0x2000U)
#define Er_nReserve14       (0x4000U)
#define Er_nReserve15       (0x8000U)
/************Define END  **************************************************** */	
/*
*/
/***************************No Config Parameters********************************/
#define MMI_nu8DefaultOutputValue		(0xFFU)
#define MMI_nu16DefaultOutputValue		(0xFFFFU)
#define MMI_NoError                     (0x0000U)
#define MMI_nNotKeyPressed              (0U)







/************************** Display Info **************************************/

#define DISPLAY (1U)
#define BLANK   (0U)

MMI_tstLcdInfo tstLcdInfo;

#define MMI_nDispInfoClearAll() tstLcdInfo.tunLcdInfo1.u16LcdInfo1=0x0000u;\
	                            tstLcdInfo.tunLcdInfo2.u16LcdInfo2=0x0000u
#define MMI_nLcdInfo1           tstLcdInfo.tunLcdInfo1.u16LcdInfo1
#define MMI_nLcdInfo2           tstLcdInfo.tunLcdInfo2.u16LcdInfo2

#define MMI_nDispOffFlag(TRUE_FALSE)         (tstLcdInfo.tunLcdInfo1.tstLcdInfo1.OffFlag=(TRUE_FALSE))
#define MMI_nDispDefSymbol(DISP_BLANK)       (tstLcdInfo.tunLcdInfo1.tstLcdInfo1.DefSymbol=(DISP_BLANK))
#define MMI_nDispMaxAcSymbol(DISP_BLANK)     (tstLcdInfo.tunLcdInfo1.tstLcdInfo1.MaxAcSymbol=(DISP_BLANK))
#define MMI_nDispManualSymbol(DISP_BLANK)    (tstLcdInfo.tunLcdInfo1.tstLcdInfo1.ManualSymbol=(DISP_BLANK))
#define MMI_nDispAutoSymbol(DISP_BLANK)      (tstLcdInfo.tunLcdInfo1.tstLcdInfo1.AutoSymbol=(DISP_BLANK))
#define MMI_nDispAcSymbol(DISP_BLANK)        (tstLcdInfo.tunLcdInfo1.tstLcdInfo1.AcSymbol=(DISP_BLANK))
#define MMI_nDispDualSymbol(DISP_BLANK)      (tstLcdInfo.tunLcdInfo1.tstLcdInfo1.DualSymbol=(DISP_BLANK))
#define MMI_nDispEconSymbol(DISP_BLANK)      (tstLcdInfo.tunLcdInfo1.tstLcdInfo1.EconSymbol=(DISP_BLANK))
#define MMI_nDispFreshSymbol(DISP_BLANK)     (tstLcdInfo.tunLcdInfo1.tstLcdInfo1.FreSymbol=(DISP_BLANK))
#define MMI_nDispRecSymbol(DISP_BLANK)       (tstLcdInfo.tunLcdInfo1.tstLcdInfo1.RecSymbol=(DISP_BLANK))
#define MMI_nDispRearDefSymbol(DISP_BLANK)   (tstLcdInfo.tunLcdInfo1.tstLcdInfo1.RDefSymbol=(DISP_BLANK))
#define MMI_nDispAqsSymbol(DISP_BLANK)       (tstLcdInfo.tunLcdInfo1.tstLcdInfo1.AqsSymbol=(DISP_BLANK))
#define MMI_nDispTempFlag(TRUE_FALSE)        (tstLcdInfo.tunLcdInfo2.tstLcdInfo2.TempFlag=(TRUE_FALSE))
#define MMI_nDispBctlFlag(TRUE_FALSE)        (tstLcdInfo.tunLcdInfo2.tstLcdInfo2.BlwFlag=(TRUE_FALSE))
#define MMI_nDispAirdFlag(TRUE_FALSE)        (tstLcdInfo.tunLcdInfo2.tstLcdInfo2.AirdFlag=(TRUE_FALSE))
#define MMI_nDispRecFlag(TRUE_FALSE)        (tstLcdInfo.tunLcdInfo2.tstLcdInfo2.RecFlag=(TRUE_FALSE))

/***** Indicator display Info*************************/
MMI_tstIndiInfo tstIndiInfo;

#define MMI_nIndicatorInfoClearAll()         tstIndiInfo.nu16IndiInfo1.u16IndiInfo1 = 0x0000u;\
                                              tstIndiInfo.nu16IndiInfo2.u16IndiInfo2 = 0x0000u

#define MMI_nIndiInfo1                       (tstIndiInfo.nu16IndiInfo1.u16IndiInfo1)
#define MMI_nIndiInfo2                       (tstIndiInfo.nu16IndiInfo2.u16IndiInfo2)

#define MMI_nAutoIndicator(DISP_BLANK)       (tstIndiInfo.nu16IndiInfo1.tstIndiInfo1.AutoIndi=(DISP_BLANK))
#define MMI_nAcIndicator(DISP_BLANK)         (tstIndiInfo.nu16IndiInfo1.tstIndiInfo1.AcIndi=(DISP_BLANK))
#define MMI_nDualIndicator(DISP_BLANK)       (tstIndiInfo.nu16IndiInfo1.tstIndiInfo1.DualIndi=(DISP_BLANK))
#define MMI_nFreshIndicator(DISP_BLANK)      (tstIndiInfo.nu16IndiInfo1.tstIndiInfo1.FreshIndi=(DISP_BLANK))
#define MMI_nRecIndicator(DISP_BLANK)        (tstIndiInfo.nu16IndiInfo1.tstIndiInfo1.RecIndi=(DISP_BLANK))
#define MMI_nRearDefIndicator(DISP_BLANK)    (tstIndiInfo.nu16IndiInfo1.tstIndiInfo1.RDefIndi=(DISP_BLANK))
#define MMI_nDefIndicator(DISP_BLANK)        (tstIndiInfo.nu16IndiInfo1.tstIndiInfo1.DefIndi=(DISP_BLANK))
#define MMI_nMaxAcIndicator(DISP_BLANK)      (tstIndiInfo.nu16IndiInfo1.tstIndiInfo1.MaxAcIndi=(DISP_BLANK))
#define MMI_nBackLightFlag(TRUE_FALSE)       (tstIndiInfo.nu16IndiInfo1.tstIndiInfo1.LcdBLFlag=(TRUE_FALSE))
#define MMI_nIonIndicator(DISP_BLANK)       (tstIndiInfo.nu16IndiInfo1.tstIndiInfo1.IonIndi=(DISP_BLANK))

#define MMI_nShcRIndicator(DISP_BLANK)      (tstIndiInfo.nu16IndiInfo2.tstIndiInfo2.Hsr1Indi=(DISP_BLANK))
#define MMI_nShcLIndicator(DISP_BLANK)       (tstIndiInfo.nu16IndiInfo2.tstIndiInfo2.Hsl1Indi=(DISP_BLANK))

/************************** Display Info End **************************************/

#define	MMI_RearBlowerDelayTime			(200)/*2second*/
#define	MMI_SaveDelayTime				(200)/*2second*/
#define MMI_u16BusDefaultNeverSuc  (0xFFFE)
#define MMI_u16BusDefaultLeast1stSuc (0xFFFF)

/*******************************************************************************
* End of check if informations are already included
*******************************************************************************/
#endif                                  /* ifndef MMI_PRIVATE_H*/

/*******************************************************************************
* EOF: Mmi_Private.h
*******************************************************************************/


