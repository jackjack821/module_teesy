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
#ifndef ACCC_TYPE_H
#define ACCC_TYPE_H


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
#include "ACCC_Cfg.h" 


/*****************************************************************************
* DEFINE DATA TYPE INTERNAL
*
* In this section
* - define all the private data types of this module.
******************************************************************************/
typedef enum ACCC_enu32VarNumbers
{
	ACCC_nu32AcOffCode,      /* Off code record */
    ACCC_nu32Max
}ACCC_tenu32VarNumber;

/*this is for uint16 type variables*/
typedef enum ACCC_enu16VarNumbers
{
	ACCC_nu16AcErrorCode=0,  /* Error code record*/
	ACCC_nu16AcOffCode,      /* Off code record */
#if((ACCC_nAcType == ACC_u8VariableDisplacAc) || (ACCC_nAcType == ACC_u8ElectricAc))
	ACCC_nu16EvapTargetTemp, /* calcualte evap. target temperature*/
	ACCC_nu16TargeCoolingCapacity,
	ACCC_nu16TargePhysics,
#endif
#if(ACCC_nAcType == ACC_u8VariableDisplacAc)	
	ACCC_nu16VdcPwmOutput,
#elif(ACCC_nAcType == ACC_u8ElectricAc) 	
	ACCC_nu16EcSpeedToOutput,
#if(ACCC_nHCU_LIMIT_EC_SPEED == True)
	ACCC_nu16HcuLimitEcSpd,  
	ACCC_nu16HcuLimitEcPower,
#endif
#endif
	ACCC_nu16Max                     
}ACCC_tenu16VarNumber;


/*this is for uint8 type variables*/
typedef enum ACCC_enu8VarNumbers
{   
	ACCC_nu8SwVersion=0,
	ACCC_nu8AcActualRequest,       /* Request to On or Off AC          */
	ACCC_nu8AcDisplay,       /* The display of AC in LCD or Telltale */
	ACCC_nu8MmiAcReq,        /* A/C requset processing from MMI*/ 
#if(ACCC_nWITH_COOLING_VALVE == True)
	ACCC_nu8AcValveReq,      /* Compressor refrigerating pipeline valve request*/ 
	ACCC_nu8AcValvePin,      /* Compressor refrigerating pipeline valve output Pin for RTE*/ 
#endif
#if(ACCC_nAcType == ACC_u8VariableDisplacAc)	
	ACCC_nu8TorqueOutput,
#endif
#if(ACCC_nAcType == ACC_u8ElectricAc) 	
	ACCC_nu8EcTargetSpeedForCAN,  /* calculate E-compressor control speed*/
	#if(ACCC_nOUTPUT_SPEED_TO_POWER)
	ACCC_nu8EcTargetPowerForCAN,  /* calculate E-compressor control speed*/
	#endif
#if(ACCC_nWITH_BATT_MANAGE == True)
	ACCC_nu8BattCoolingReq,  /* Request of battery force cooling by A/C*/
	ACCC_nu8ChillerValveReq, /* battery chiller E-Valve requset*/
	ACCC_nu8ChillerValvePin, /* Chiller E-Valve output Pin for RTE*/
#endif
#endif
	ACCC_nu8Max                   
}ACCC_tenu8VarNumber;


typedef enum ACCC_enu8AcRequest
{
	ACCC_nAcReqOff=0,
	ACCC_nAcReqOn,
#if ACCC_nWITH_ECON_MODE
	ACCC_nAcReqOffEcon,
#endif		
	ACCC_nAcReqError
}ACCC_tenu8AcRequest;


typedef enum ACCC_enu8AcDisplayInfo
{
	ACCC_nAcDisplayOff=0,
	ACCC_nAcDisplayOn,
	ACCC_nAcDisplayEcon,
	ACCC_nAcDisplayError
}ACCC_tenu8AcDisplayInfo;


typedef enum Acc_enOffCodeIDType
{
	Off_nEvapTDisable=0,//0
	Off_nOatDisable,
	Off_nBlwFault,
	Off_nPressureHigh,
	Off_nPressureLow,// 4
	Off_nEngLowSpd,
	Off_nEngHighSpd,
	Off_nEvapSensorFault,
	Off_nOatSensorFault,
	Off_nBatHiOrLowVol,//9
	Off_nAcOff,
	//Off_nSysOff,
	Off_nRequestOff,
	Off_nPreOutRange,//13
	Off_nShortToGnd,
	Off_nPowerLimit,
	Off_nIstpDisable,
	Off_nAllCodeNumber,
}Acc_tenOffCodeIDType;


typedef struct   
{                 
	uint16 Kp;                 /*Proportional Constant, actual p = kp/8*/
	uint16 Ki;           	   /*Integral Constant, actual i = ki/256*/
	uint16 Kd;           	   /*Derivative Constant, actual d = kd*2*/
	
	int16 LastError;     	   /*Error Tn-1*/
	int16 PrevError;     	   /*Error Tn-2*/   
	int32 SumError; 		   /*Sums of Errors*/
	
	int16 UpperDiffLimit;	   /*upper limit of difference*/
	int16 LowerDiffLimit;	   /*lower limit of difference*/
	int32 UpperSumErrorLimit;  /*upper limit of sum error*/
	int32 LowerSumErrorLimit;  /*lower limit of sum error*/	
	
	Bool OutputLimitUsed;	   /*if limit the PID output, set it true. */
	int16 UpperLimit;		   /*Upper limit of PID control*/
	int16 LowerLimit;		   /*Lower limit of PID control*/
	uint16 FeedForward;
} ACCC_stPidType ;

typedef enum  ACCC_enEcCoolingMode
{
    ACCC_nAcOffMode=0,
    ACCC_nEvapCoolingMode,
    ACCC_nBattCoolingMode
}ACCC_tenEcCoolingMode;

/*Ccp control*/
typedef enum
{
	Acc_nSetAcReq,
	Acc_nSetAcTargetSpeed,
	Acc_nSetAcTargetEvap,
	Acc_nSetAcHighFanSpd,
	Acc_nSetAcHiLoPress,
	Acc_nSetAcMidPress,
	Acc_nSetKp,
	Acc_nSetKi,
	Acc_nCcpForceMax
}CcpControl_Acc;

 typedef enum
 {
    ACCC_nInvalid=0u,
    ACCC_nValid,
    ACCC_nDefault,
    ACCC_nLastValid
 }ACCC_tenValueSts;
 

#endif                                  /* ifndef ACCC_TYPE_H*/

/*******************************************************************************
* EOF: ACCC_Type.h
*******************************************************************************/










