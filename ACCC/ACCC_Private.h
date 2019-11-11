/*******************************************************************************
| Module Name: Air Condition Compressor Control
| File Name: Accc.c
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
| 2014/11/25  A1        Yang Tingyu		    The first version	
| 2016/01/11  A2        Yang Tingyu		    Modified for HEV
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef ACCC_PRIVATE_H
#define ACCC_PRIVATE_H


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


/*******************************************************************************
* EXPORT INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define helpful macros for easy data access and for a comfortable function use, if 
*   necessary.
* - define all macros for accessing the external module interfaces variables
* - define all macros which not need to be configed and changed for this module 
******************************************************************************/
#define SW_VERSION (0xA5U) /* ;YTY 2016/4/6 */ 

/****Macros switch********/ 
/**************************Extern Module Interface*****************************/
#define ACCC_u8GetPowAdValid				(0x7f)//Rte_IRead_Accc_vMain_Accc_PowAdValid_u8Flag()
#define ACCC_u8GetPowBattLowVoltage   	        ((uint8)POW_u16GetValue(POW_nu16AppLowVoltage))
#define ACCC_u8GetPowBattHighVoltage	        ((uint8)POW_u16GetValue(POW_nu16AppHighVoltage))
#define ACCC_u8GetMmiAcCtrl					    MMI_u8GetValue(MMI_nu8ACControl)
#define ACCC_u8GetMmiAcMode					    MMI_u8GetValue(MMI_nu8ACMode)
#define ACCC_u8GetMmiSetTempLeft				MMI_u8GetValue(MMI_nu8SetTempDr)
#if(SYC_ZONES == 2)
#define ACCC_u8GetMmiSetTempRight				MMI_u8GetValue(MMI_nu8SetTempPs)
#endif
#define ACCC_u8GetMmiBctlCtrl					MMI_u8GetValue(MMI_nu8BlwControl)
#define ACCC_u16GetCcsBlowoutDr			        CCS_u16GetValue(CCS_nu16BlowoutTempDr)
#if(SYC_ZONES == 2)
#define ACCC_u16GetCcsBlowoutPs			    CCS_u16GetValue(CCS_nu16BlowoutTempPs)
#endif
#define ACCC_u16GetEvapAcValue				   EVAP_u16GetValue(EVAP_nu16AcValue)
#define ACCC_u16GetOatValue					    OAT_u16GetValue(OAT_nu16Value)
#define ACCC_u16GetIctValue					    600u;//ICT_u16GetValue(ICT_nu16Value)

#define ACCC_u16GetBattCoolantInTemp	        (0x7f)//(Rte_IRead_Accc_vMain_AcccGetBtmWaterInCur_BtmWaterInCurrent())
#define ACCC_u16GetBattCoolantInTargetTemp  (0x7f)// (Rte_IRead_Accc_vMain_AcccGetBtmWaterInTgt_BtmWaterInTarget())
/*ACCC_u16GetBattCoolingMode: 0:Force Cooling; 1:Natural cooling*/
#define ACCC_u16GetBattCoolingMode           (0x7f)//(Rte_IRead_Accc_vMain_AcccGetBtmNaturalRefrigSts_BtmNaturalRefrigSts())		
/*0:NotHeatNotCooling; 1:Heating; 2:Cooling****/
#define ACCC_u16GetBattThermalMagReq             (0x7f)//(Rte_IRead_Accc_vMain_AcccGetBtmTempMagReq_BtmTempManagReq())
#define ACCC_u16GetBattThreeWayValveRatio       (0x7f)// (Rte_IRead_Accc_vMain_AcccGetBtmThreeGateValve_BtmLinThreeValve())

#define ACCC_u16GetEcPowerLimitValue       (0x7f)//  (Rte_IRead_Accc_vMain_AcccGetCanCompressorPowerLimit_CanApp_VcuAcPowerLimt())
//#define ACCC_u16GetEcActualPower             (Rte_IRead_Accc_vMain_AcccGetCanCompressorActualPower_CanApp_AcPowerConsumption())    	
#define ACCC_u16GetEcActualSpd              (0x7f)// (Rte_IRead_Accc_vMain_AcccGetCanCompressorRpm_CanApp_AcCompRPM())
//#define ACCC_u16GetEcState                   (Rte_IRead_Accc_vMain_AcccGetCanCompressorStatus_CanApp_CompStatus())
#define ACCC_u8GetRfaDisp					  (0x7f)//   (Rte_IRead_Accc_vMain_AcccGetRfaDisplay_RfaDisplay())

#if(ACCC_nWITH_PRESSURE_SENSOR == True)
#define ACCC_u16GetPtaPressureFb(value)		(0x7f)//(Rte_Call_Accc_AcccProto_AcccGetAdcResultAcPressHiLo_Read(value))
#endif 
#if (ACCC_nWITH_PRESSURE_SWITCH == True)
#define ACCC_u16GetPressureHiLoSwitchValue	(0x7f)//(Rte_Call_Accc_AcccProto_AcccGetAdcResultAcPressHiLo_Read(value))
#endif

#define ACCC_u16GetBlowerTarget				(BCTL_u16GetValue(BCTL_nu16TrgVol))
#define ACCC_u16GetBlowerError				(BCTLDRV_u16GetValue(BCTLDRV_nu16Error))
#define ACCC_u16GetEngineSpeed				(0x7f)//
#define ACCC_u16GetVehicleSpeed				(0x7f)//
#define ACCC_u16GetPressureValue			(0x7f)//
#define ACCC_u16GetVdcActualCurr			(0x7f)//
#define ACCC_u16GetShortToGndDetectPin		(0x7f)
#define ACCC_u16GetCcsTempDiffDr			(0x7f)

/**************************Output Extern Interface define*****************************/ 
#define ACCC_SW_VERSION    		   (ACCC_au8Array[ACCC_nu8SwVersion])
#define ACCC_u8AcActualReq         (ACCC_au8Array[ACCC_nu8AcActualRequest])
#define ACCC_u8AcOperation         (ACCC_au8Array[ACCC_nu8MmiAcReq])
#define ACCC_u8AcDisplayInfo       (ACCC_au8Array[ACCC_nu8AcDisplay])
#define ACCC_AC_ERROR_CODE         (ACCC_au16Array[ACCC_nu16AcErrorCode])
#define ACCC_AC_OFF_CODE           (ACCC_au16Array[ACCC_nu16AcOffCode])
#if(ACCC_nWITH_COOLING_VALVE == True)
#define ACCC_u8AcValveReq          (ACCC_au8Array[ACCC_nu8AcValveReq])
#define ACCC_u8AcValvePin          (ACCC_au8Array[ACCC_nu8AcValvePin])
#endif

#if((ACCC_nAcType == ACC_u8VariableDisplacAc) || (ACCC_nAcType == ACC_u8ElectricAc))
#define ACCC_u16EvapTargetTemp	(ACCC_au16Array[ACCC_nu16EvapTargetTemp])
#define ACCC_u16TargeCoolingCapacity	(ACCC_au16Array[ACCC_nu16TargeCoolingCapacity])
#define ACCC_u16TargePhysics	(ACCC_au16Array[ACCC_nu16TargePhysics])
#endif
#if(ACCC_nAcType == ACC_u8VariableDisplacAc)	
#define ACCC_u16VdcPwmOutput	(ACCC_au16Array[ACCC_nu16VdcPwmOutput])
#define ACCC_u8TorqueOutput       (ACCC_au8Array[ACCC_nu8AcDisplay])
#elif(ACCC_nAcType == ACC_u8ElectricAc) 	
#define ACCC_u16EcSpeedToOutput       (ACCC_au16Array[ACCC_nu16EcSpeedToOutput])
#define ACCC_u8EcTargetSpeedForCAN		(ACCC_au8Array[ACCC_nu8EcTargetSpeedForCAN])
#if(ACCC_nOUTPUT_SPEED_TO_POWER)
#define ACCC_u8EcTargetPowerForCAN		(ACCC_au8Array[ACCC_nu8EcTargetPowerForCAN])
#endif
#if(ACCC_nHCU_LIMIT_EC_SPEED == True)
#define ACCC_u16HcuLimitEcSpd         (ACCC_au16Array[ACCC_nu16HcuLimitEcSpd])
#define ACCC_u16HcuLimitEcPower     (ACCC_au16Array[ACCC_nu16HcuLimitEcPower])
#endif

#if(ACCC_nWITH_BATT_MANAGE == True)
#define ACCC_u8BattCoolingReq	(ACCC_au8Array[ACCC_nu8BattCoolingReq])
#define ACCC_u8ChillerValveReq	(ACCC_au8Array[ACCC_nu8ChillerValveReq])
#define ACCC_u8ChillerValvePin	(ACCC_au8Array[ACCC_nu8ChillerValvePin])
#endif
#endif

/*****Extern Modules define*****/
#define ACCC_nMmiAcModeOff    0
#define ACCC_nMmiAcModeManu   1
#define ACCC_nMmiAcModeAuto   2   
#define ACCC_nMmiAcModeDef   3   

#define ACCC_nMmiAcOff  MMI_nAcOff
#define ACCC_nMmiAcOn  MMI_nAcOn
#define ACCC_nMmiSetTempHi    255U
#define ACCC_nMmiSetTempLo    0U

#define ACCC_nAcForceCoolingMode    0U 
#define ACCC_BtmThermalCoolingReq   2U 
/*******************************/

/******************/ 





/*******AC HW define***********************************/
/****The Pin interface shall be update for new project*/ 
#define AcReqOutputPinID  04U
#define TXV_EvapPinID    05U
#define TXV_ChillerPinID    06U

#define ACCC_ReqOnHighActive    (1U)
#if ACCC_ReqOnHighActive
#define ACCC_nCompressorOff    (0U)
#define ACCC_nCompressorOn    (1U)
#else
#define ACCC_nCompressorOff    (1U)
#define ACCC_nCompressorOn    (0U)
#endif
#define Pin_Off    (0U)
#define Pin_On    (2U)

/****A/C request output****/ 
#define	ACCC_ReqPinCfg()    /*HAL_PinConfig(AcReqOutputPinID,Off)*/
#define ACCC_ReqPinInit()    /*HAL_PinWrite(AcReqOutputPinID,Off)*/
#define	ACCC_ReqPinDeinit()    /*HAL_PinWrite(AcReqOutputPinID,Off)*/
#define ACCC_ReqOutput(ON_OFF)  /*HAL_PinWrite(AcReqOutputPinID,ON_OFF) */
/****A/C Evap cooliing Valve output****/ 
#define	ACCC_AcValvePinCfg()    /*HAL_PinConfig(TXV_EvapPinID,Off)*/
#define ACCC_AcValvePinOutput(ON_OFF)  ACCC_u8AcValvePin=(ON_OFF)/*HAL_PinWrite(TXV_EvapPinID,ON_OFF) */
/****Battery Chiller Valve output****/ 
#define	ACCC_ChillerValvePinCfg()    /*HAL_PinConfig(TXV_ChillerPinID,Off)*/
#define ACCC_ChillerValveOutput(ON_OFF)  ACCC_u8ChillerValvePin = (ON_OFF)/*HAL_PinWrite(TXV_ChillerPinID,ON_OFF)*/

/***************************No Config Parameter********************************/


/*Private Macro define*/
#define Set16BitValue(Value, Num)    (Value|=((uint16)1<<Num))
#define Clear16BitValue(Value, Num)    (Value &=(~((uint16)1<<Num)))
#define Check16BitValid(Value, Num)    ((((uint16)1<<Num)&(uint16)Value) != 0x0000U)
#define Check16BitInvalid(Value, Num)    ((((uint16)1<<Num)&(uint16)Value) == 0x0000U)

#define ACCC_SetOffCode(Value, Num)    Set16BitValue(Value, Num)
#define ACCC_ClearOffCode(Value, Num)    Clear16BitValue(Value, Num)

#define ACCC_SetErrorCode(Value, Num)    Set16BitValue(Value, Num)
#define ACCC_ClearErrorCode(Value, Num)    Clear16BitValue(Value, Num)

#define ACCC_MIN_VALUE(Value1,Value2)    MIN(Value1,Value2)

#define AccGetCcpForceBit(index)	((Accc_CcpForceFlag>>index)&0x01)
#define AccSetCcpForceBit(index)	(Accc_CcpForceFlag=Accc_CcpForceFlag|(0x01<<index))
#define AccClrCcpForceBit(index)	(Accc_CcpForceFlag=Accc_CcpForceFlag&(~(0x01<<index)))
#define AccClrCcpForceByte(void)	(Accc_CcpForceFlag=0)
/*******************************************************************************/


/**********FUNCTION DEFINE*****************************************************/ 
#define ACCC_VALUE_LIMIT(Data, LimitMax, LimitMin)					\
	if(Data >= LimitMax)				\
	{											\
		Data = LimitMax;				\
	}											\
	else if(Data <= LimitMin)			\
	{											\
		Data = LimitMin;				\
	}											\
	else											\
	{											\
												\
	}											

#define ACCC_VALUE_GRADIENT(TargetData, OutputData,  IncGradient, DecGradient) \
	if((TargetData) > (OutputData))    \
	{    \
		if((TargetData) > ((OutputData) + (IncGradient))) (OutputData) +=  (IncGradient);    \
		else (OutputData) = (TargetData);    \
	}    \
	else \
	{    \
		if((OutputData) > ((TargetData) + (DecGradient))) (OutputData) -=  (DecGradient);    \
		else (OutputData) = (TargetData);    \
	} 
	



/*******************************************************************************
* End of check if informations are already included
*******************************************************************************/
#endif                                  /* ifndef ACCC_PRIVATE_H*/

/*******************************************************************************
* EOF: ACCC.h
*******************************************************************************/


