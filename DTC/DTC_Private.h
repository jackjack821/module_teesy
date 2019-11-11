
/*******************************************************************************
| Module Name: DTC process(prcess dianostic code) 
| File Name: DTC_Private.h
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
| Sui Yanchun                        Desay SV Automotive Co., Ltd
| Lin Tao                     Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2014-11-24  1.00        Sui Yanchun       update the DTC module 
| 2015-12-56  2.00        Lin Tao           update for the MISRA C

********************************************************************************/



#ifndef DTC_PRIVATE_H
#define  DTC_PRIVATE_H

#include "General.h"
//#include "ACCC.h" 
//#include  "Hct.h"   
//#include "Btm.h" 
//#include "LinApp.H" 
//#include "LinApp_cfg.H" 
#include "desc.H" 
#include "AppDesc.h"

typedef uint32 DTC_DataType;
typedef uint8  DTC_IDX_TYPE;

#define DTC_nSysType                (32U)   /*define the MUC Type, 8bit,16bit,32bit*/

/*define the error code from the App module*/
#define DTC_nDcmShortBatCode            (0x01U)/*Interface OK*/
#define DTC_nDcmShortGndCode            (0x02U)/*Interface OK*/
#define DTC_nDcmBlockCode               (0x04U)/*Interface OK*/

#define DTC_nBctlErrCode               (0x01U)

#define DTC_nSensorShortGndCode         (0x01U)/*Interface OK*/
#define DTC_nSensorShortBatCode         (0x02U)	/*Interface OK*/

#define DTC_nCanBusOffCode             (0x0001U)	

#define DTC_nPEPSMissErrCode           (0x0001U)//(0x0002U)    /*ID:0x1E2*/
#define DTC_nBCMMissErrCode            (0x0004U)//(0x0008U)	/*ID:0x1F0*/
#define DTC_nESCMissErrCode            (0x0010U)//(0x0020U)	/*ID:0x125*/
#define DTC_nMMIMissErrCode            (0x0020U)//(0x0040U)	/*ID:0x2A5*/
#define DTC_nIPKMissErrCode            (0x0040U)//(0x0080U)	/*ID:0x3F1*/
#define DTC_nTBOXMissErrCode           (0x0080U)//(0x0100U)	/*ID:0x292*/
#define DTC_nEMSMissErrCode            (0x0100U)//(0x0200U)	/*ID:0x288*/

/*KC-2 HB New CAN node*/
#define DTC_nIPUMissErrCode            (0x1000U)	/*ID:0x360*/
#define DTC_nBMSHMissErrCode           (0x0800U)    /*ID:0x3D0*/	
#define DTC_nOBCMissErrCode            (0x0400U)	/*ID:0x220*/	
#define DTC_nVCUMissErrCode            (0x4000U)	/*ID:0x162*/	



#define DTC_nIONMissErrCode             (0x0001U<<LINAPP_nION_1)/*ION*/
#define DTC_nPM25MissErrCode            (0x0001U<<LINAPP_nPM25_1)/*PM25*/
#define DTC_nRCPMissErrCode             (0x0001U<<LINAPP_nION_1)/*RCP*/


/*KC-2 HB New LIN node*/
#define DTC_nPTCMissErrCode            (0x0060U)/*PTC1,PTC2*/	
#define DTC_nACCMMissErrCode           (0x0180U)/*ACCM1,ACCM2*/	
#define DTC_nLinVCUMissErrCode         (0x0018U)/*VCU1,VCU2*/	
#define DTC_nWV1MissErrCode            (0x0200U)/*WV1*/
#define DTC_nWV2MissErrCode            (0x0400U)/*WV2*/
#define DTC_nWV3MissErrCode            (0x0800U)/*WV3*/

/*KC-2 HB Pump Error code*/
#define DTC_nPumpDryRunErrcode           (0x0001U)
#define DTC_nPumpStallErrcode            (0x0002U)
#define DTC_nPumpOverTempErrcode         (0x0004U)
#define DTC_nPumpVoltageErrcode          (0x0008U)


#define DTC_nIONHWErrCode               (0x03)
#define DTC_nPM25ErrCode                (0x03)


//#define DTC_nPTCHWErrCode                (0x01FFFC)//bit2~bit16 (0x03)
#define DTC_nPTCHWErrCode                (0x03FFFC)//bit2~bit17 (0x03)
//#define DTC_nACCMHWErrCode                (0x03FFFF)//bit0~bit17 (0x03)
#define DTC_nACCMHWErrCode                (0x0FFFFF)//bit0~bit19 (0x03)


#define DTC_nSignalErrCode              (0x04U)
#define DTC_nOutPutPowErrCode           (0x02U)





#if 0


#define DTC_u8GetIONMountCfg             1
#define DTC_u8GetPM25MountCfg            DIAG_u8GetValue(DIAG_nu8PM25Mount)
#define DTC_u8GetRCPMountCfg             DIAG_u8GetValue(DIAG_nu8RCPMount)
#define DTC_u8GetAQSMountCfg             DIAG_u8GetValue(DIAG_nu8AQSMount)

#define DTC_ReadCanNetworkCfg(ReadCfg)  DIAG_NetWorkCf(ReadCfg)
#define DTC_u16GetCANAppErrCode         CANAPP_u16GetValue(CANAPP_nu16ComErrorFlage) //Rte_IRead_Dtc_vMain_Dtc_CanAppErrorCode_u16BitMap()
#define DTC_u16GetLinAppErrCode         LINAPP_u16GetValue(LIN_nu16LINErrorCode) //Rte_IRead_Dtc_vMain_Dtc_LinAppErrorCode_u16BitMap()
#define DTC_u16GetAQSErrCode            AQS_u8GetValue(AQS_nu8ErrorCode)//Rte_IRead_Dtc_vMain_Dtc_AqsErrorCode_u16BitMap
#define DTC_u16GetPM25HWErrCode         ION_u8GetValue(ION_nu8ErrorCode1)//Rte_IRead_Dtc_vMain_Dtc_IonErrorCode_u16BitMap
#define DTC_u16GetIONHWErrCode          ION_u8GetValue(ION_nu8ErrorCode2)//Rte_IRead_Dtc_vMain_Dtc_IonErrorCode_u16BitMap


#define DTC_u16GetInCarErrCode      ICT_u16GetValue(ICT_nu16ErrorState)
#define DTC_u16GetEvapErrCode       EVAP_u8GetValue(EVAP_nu8ErrorCode)//Rte_IRead_Dtc_vMain_Dtc_EvapErrorCode_u16BitMap()
#define DTC_u16GetOatErrCode        OAT_u16GetValue(OAT_nu16ErrorCode)//Rte_IRead_Dtc_vMain_Dtc_OatErrorCode_u16BitMap()
#define DTC_u16GetPowErrCode        Rte_IRead_Dtc_vMain_Dtc_PowErrorCode_u16BitMap()
#define DTC_u8GetDcmMixDrErrCode   (Rte_IRead_Dtc_vMain_Dtc_DcmErrorCode_u32DcmErrorCode()&0x000000FFU)
#define DTC_u8GetDcmMixPsErrCode   ((Rte_IRead_Dtc_vMain_Dtc_DcmErrorCode_u32DcmErrorCode()&0x0000FF00U)>>8)
#define DTC_u8GetDcmAirdErrCode    ((Rte_IRead_Dtc_vMain_Dtc_DcmErrorCode_u32DcmErrorCode()&0x00FF0000U)>>16)
#define DTC_u8GetDcmRfaErrCode     ((Rte_IRead_Dtc_vMain_Dtc_DcmErrorCode_u32DcmErrorCode()&0xFF000000U)>>24)
#define DTC_u16GetBlowerErrCode     BCTLDRV_u16GetValue(BCTLDRV_nu16Error)// Rte_IRead_Dtc_vMain_Dtc_BctlDrvErrorCode_u16BitMap()


#define DTC_boGetPOWDiagHigh         POW_u8GetValue(POW_nu8DiagHighVoltage)//Rte_IRead_Dtc_vMain_Dtc_PowDiagHighVoltage_u8Flag()
#define DTC_boGetPOWDiagLow          POW_u8GetValue(POW_nu8DiagLowVoltage)//Rte_IRead_Dtc_vMain_Dtc_PowDiagLowVoltage_u8Flag()
#define DTC_u16GetBatteryVol         POW_u8GetValue(POW_nu8BattVoltage)//Rte_IRead_Dtc_vMain_Dtc_PowBattVoltage_u16AdValue()
#define DTC_u16GetCANAppVelSpeed     CANAPP_u16GetValue(CANAPP_nu16VehicleSpeed)
#define DTC_u32GetCANAppOdometer     CANAPP_u32GetValue(CANAPP_nu32TotalOdometer)
#define DTC_u8GetCANCoolantTemp      CANAPP_u8GetValue(CANAPP_nu8EngWaterTemp)
#define DTC_u8GetDiagCanRxStatus     DIAG_u8GetValue(DIAG_nu8AppRxDisable)

#endif

#define DTC_u8GetIONMountCfg           DIAG_u8GetValue(DIAG_nu8IONMount)//Rte_IRead_Dtc_vMain_Dtc_DiagIonMount_u8Flag()
#define DTC_u8GetPM25MountCfg          DIAG_u8GetValue(DIAG_nu8PM25Mount)//  Rte_IRead_Dtc_vMain_Dtc_DiagPM25Mount_u8Flag()/*Interface OK,20160713*/
#define DTC_u8GetRCPMountCfg           DIAG_u8GetValue(DIAG_nu8RCPMount)//   Rte_IRead_Dtc_vMain_Dtc_DiagRCPMount_u8Flag()/*Interface OK,20160713*/
#define DTC_u8GetAQSMountCfg           DIAG_u8GetValue(DIAG_nu8AQSMount)//  Rte_IRead_Dtc_vMain_Dtc_DiagAQSMount_u8Flag()/*Interface OK,20160713*/


#define DTC_ReadCanNetworkCfg(ReadCfg)  DIAG_NetWorkCf(ReadCfg) //Rte_Call_Dtc_DiagNetWorkCfg_NetWorkCfg(ReadCfg)/*Interface OK,20160713*/


#define DTC_u16GetCANBusOffConfirm     CANNMAPP_u16GetValue(CANNMAPP_nu16BusOffConf)// CANNM_u8GetValue(CANNM_nu8BusOffConf)
#define DTC_u16GetCANBusOffStart       CANNMAPP_u16GetValue(CANNMAPP_nu16BusOffStart)// CANNM_u8GetValue(CANNM_nu8BusOffStart)

#define DTC_u32GetCANAppErrCode         CANAPP_u32GetValue(CANAPP_nu32ErrorCode)//Rte_IRead_Dtc_vMain_Dtc_CanAppErrorCode_u16BitMap()/*Interface OK,20160713*/
#define DTC_u32GetCANAppDlcErrCode         CANAPP_u32GetValue(CANAPP_nu32MsgDlcErr)
#define DTC_u32GetLinAppErrCode         LINAPP_u32GetValue(LINAPP_nu32ErrorCode)//Rte_IRead_Dtc_vMain_Dtc_LinAppErrorCode_u16BitMap()/*Interface not OK,20160713*/
#define DTC_u16GetAQSErrCode            ((uint16)AQS_u8GetValue(AQS_nu8ErrorCode))//Rte_IRead_Dtc_vMain_Dtc_AqsErrorCode_u16BitMap()/*Interface OK,but module not so correct,20160713*/
#define DTC_u16GetPM25HWErrCode         LINAPP_u16GetValue(LIN_nu16L_PM25_ErrSts)//(Rte_IRead_Dtc_vMain_Dtc_IonErrorCode_u16BitMap()&0x00FF)/*pay attention to this,may error value*/
#define DTC_u16GetIONHWErrCode          (0u)//((ION_u16GetValue(ION_nu16ErrorCode)&&0x00FF)>>8)//((Rte_IRead_Dtc_vMain_Dtc_IonErrorCode_u16BitMap()&0xFF00)>>8)/*pay attention to this,may error value*/
#define DTC_u16GetPressureErrCode       (0u)//(PSV_u16GetValue(PSV_nu16ErrorCode))
#define DTC_u32GetPtcHwErrorState       (0u)//(HCT_u32GetValue(HCT_nu32ErrorCode))
#define DTC_u32GetAcccHwErrorState      (0u)//(ACCC_u32GetValue(ACCC_nu32ErrorCode))

#define DTC_u16GetInCarErrCode          (0u)//(ICT_u16GetValue(ICT_nu16ErrorState))// Rte_IRead_Dtc_vMain_Dtc_IctErrorCode_u16BitMap()/*Interface OK,20160713*/
#define DTC_u16GetEvapErrCode           (EVAP_u16GetValue(EVAP_nu16ErrorCode))//Rte_IRead_Dtc_vMain_Dtc_EvapErrorCode_u16BitMap()/*Interface OK,20160713*/
#define DTC_u16GetOatErrCode            (OAT_u16GetValue(OAT_nu16ErrorCode))// Rte_IRead_Dtc_vMain_Dtc_OatErrorCode_u16BitMap()/*Interface OK,20160713*/
//#define DTC_u16GetPowErrCode            (POW_u8GetValue(OAT_nu16ErrorCode))//Rte_IRead_Dtc_vMain_Dtc_PowErrorCode_u16BitMap()/*no use*/
#define DTC_u8GetDcmMixDrErrCode        (DCM_u8GetValue(DCM_nu8MixDrErrorCode))//(Rte_IRead_Dtc_vMain_Dtc_DcmErrorCode_u32DcmErrorCode()&0x000000FFU)/*Interface OK,20160713*/
#define DTC_u8GetDcmAirdErrCode         (DCM_u8GetValue(DCM_nu8AirdErrorCode))//((Rte_IRead_Dtc_vMain_Dtc_DcmErrorCode_u32DcmErrorCode()&0x0000FF00U)>>8)/*Interface OK,20160713*/
#define DTC_u8GetDcmRfaErrCode          (DCM_u8GetValue(DCM_nu8RfaErrorCode))//((Rte_IRead_Dtc_vMain_Dtc_DcmErrorCode_u32DcmErrorCode()&0x00FF0000U)>>16)/*Interface OK,20160713*/
#define DTC_u8GetDcmMixPsErrCode        (DCM_u8GetValue(DCM_nu8MixPsErrorCode))//((Rte_IRead_Dtc_vMain_Dtc_DcmErrorCode_u32DcmErrorCode()&0xFF000000U)>>24)/*Interface OK,20160713*/
#define DTC_u16GetSunErrCode            (SUN_u16GetValue(SUN_nu16ErrCode))
#define DTC_u16GetBlowerErrCode         (BCTLDRV_u16GetValue(BCTLDRV_nu16Error))//Rte_IRead_Dtc_vMain_Dtc_BctlDrvErrorCode_u16BitMap()/*Interface OK,20160713*/


#define DTC_boGetPOWDiagHigh            (POW_u16GetValue(POW_nu16DiagHighVoltage))// Rte_IRead_Dtc_vMain_Dtc_PowDiagHighVoltage_u16Flag()/*Interface not OK,20160713*/
#define DTC_boGetPOWDiagLow             (POW_u16GetValue(POW_nu16DiagLowVoltage))//Rte_IRead_Dtc_vMain_Dtc_PowDiagLowVoltage_u16Flag()/*Interface not OK,20160713*/
#define DTC_u16GetBatteryVol            (POW_u16GetValue(POW_nu16ResultK30VoltFb))//Rte_IRead_Dtc_vMain_Dtc_PowK30ResultVoltFb_u16ResultVoltage()/*Interface not OK,20160713*/
#define DTC_u16GetCANAppVelSpeed        (CANAPP_u16GetValue(CANAPP_nu16ESC_VehicleSpeed))//Rte_IRead_Dtc_vMain_Dtc_CanVehSpd_u16Speed()/*Interface not OK,20160714*/
#define DTC_u32GetCANAppOdometer        (CANAPP_u32GetValue(CANAPP_nu32IPK_IPKTotalOdometer))//Rte_IRead_Dtc_vMain_Dtc_CanTotalOdometer_u32CanAppTotalOdometer()/*Interface OK,moudule not ok,20160713*/
#define DTC_u8GetCANCoolantTemp         (CANAPP_u16GetValue(CANAPP_nu16EMS_EngineCoolantTemp))//Rte_IRead_Dtc_vMain_Dtc_CanEngWaterTemp_u8Temp()/*Interface not OK,20160714*/
#define DTC_u8GetDiagCanRxStatus        (DIAG_u8GetValue(DIAG_nu8AppRxDisable))//Rte_IRead_Dtc_vMain_Dtc_DiagCommunicatonEnable_u8Flag()/*Interface OK,20160713*/
#define DTC_u8GetEngStatus              CANAPP_u16GetValue(CANAPP_nu16EMS_EngStatus)

#define DTC_vClearCANMessCnt            CANAPP_vClearMsgMissError
#define DTC_vClearBusoffCnt             CANNMAPP_vClearBusoffError
#define DTC_vClearLINMessCnt            LINAPP_vClearMessCnt


#define HIGH(x)						(uint8)((x)>>16U)
#define MIDDLE(x)					(uint8)((x)>>8U)
#define LOW(x)						(uint8)(x)

#define GetErrCodeValue(x)			(1ul<<(x))

#define BitValue(x,y)					(((x)>>(y))&0x01U)/*x is varible , y is number of witch bit(from 0 -> 7)*/
#define DTCStatusBit(a,b)				(BitValue(DTC_DATA[(a)].Status_Byte,(b)))
#define DTCStatusClrBit(a,b)			(DTC_DATA[(a)].Status_Byte &=(uint8)(~(1UL << (b))))
#define DTCStatusSetBit(a,b)			(DTC_DATA[(a)].Status_Byte |=(uint8)(1UL << (b)))
#define DtcStateDetect(a,b)				( ((a)==(b)) ? True: False)
#define DTCStatusCheckBitSet(a,b)		((DTC_DATA[(a)].Status_Byte&((uint8)(1UL << (b))))>0U)
#define DTCStatusCheckBitClr(a,b)		((DTC_DATA[(a)].Status_Byte&((uint8)(1UL << (b))))==0U)
									


//#define DTC_nSWVerSion                  (0xA2U)/*20160806*//*Release Warning,161024*/
#define STATUS_BYTE						(uint8)(0x00U)


#define MaskState							(0x7FU) /*For internal mask use, supported bit0~bit6*/
#define DTC_nAvailableMark					(0x09U) /*bit3,bit0 */


#define	DTC_nu8CrankDisableTimer			 (0x03U)  /*three seconds after crank*/
#define	DTC_nu16PowerFailDisTimer		     (50U)//(100U)  /*after powerfailure,500ms,20160914*/
#define DTC_nu16IGDelayTimer                 (300U)/*3S*/
#define DTC_nu16IGDelayForPOW                (200U)/*2S*/

#define DTC_nHighLowVolCfgTimer              (50U)/*500mS*/  
#define DTC_nBusOffResumTime                 (100U)/*1S*/

#define DTC_Stored_Group 					EED_nu8GroupDTC


#define DTC_TEST_PASSED			(0x00U)
#define DTC_TEST_FAILED			(0x01U)

#define DTC_MIN_NUMBER_TO_STORE	(32U)/* 160806,too many data will refect the init speed,should pay attention to the EEPROM*/
#define DTC_AGING_CRITERIA		(99U)//(40U)/*Modify by LT,20160806*/


//#define DTC_n10msDtcEnd	        (10U)
//#define DTC_nDtcNumberDiv	    (20U)

#define DTC_UpdateSnapAtFirstConfrim

#define DTC_SortType            (DTC_SortPriority)

#endif          

