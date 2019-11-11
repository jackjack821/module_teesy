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
| 2016/04/11  A3        Wu Jiaming		    Compatibility for fuel vehicle
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define ACCC                          /* Name of the Module                */

#define ACCC_DEVELOPMENT_DEBUG 0U /*1:Enter development mode;0:Quit development mode*/
/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */
#include "General.h"

#include "ALG.h"

/* Please put the headerfiles which related to foreign here! */

/* Own headerfiles */
#include "ACCC_Type.h"
#include "ACCC.h" 
#include "ACCC_Cfg.h" 
#include "ACCC_interface.h"
#include "ACCC_Private.h" 


/* Please put the headerfiles which related to own here! */


/*****************************************************************************
* GLOBAL DEFINITIONS
*
* In this section define
* - all global ROM-CONSTants of your module
* - all global variables of your module
*****************************************************************************/

//2the varables used for debug

#if (ACCC_DEVELOPMENT_DEBUG)

#endif

/* example1: Global ROM-constants
   ----------------------------------------------------- */

/* example2: Global Variables
   ----------------------------------------------------- */

/* example1: Local Define-constants
   ----------------------------------------------------- */

/* example2: Local ROM-constants
   ----------------------------------------------------- */


/* example3: Local Variables
   ----------------------------------------------------- */
static uint8 ACCC_au8Array[ACCC_nu8Max];
static uint16 ACCC_au16Array[ACCC_nu16Max];
static uint16 ACCC_u16WaitTimer;
static uint32 ACCC_au3216Array[ACCC_nu32Max];

#if((ACCC_nAcType == ACC_u8VariableDisplacAc) || (ACCC_nAcType == ACC_u8ElectricAc))
static uint16 ACCC_u16TargetEvapGradientTimer = 0;
static uint16 ACCC_u16PidParaOatHys = 0;
static Bool ACCC_boTargetEvapInit = True;
static uint8 ACCC_u8DynEvapInit;
static uint16 ACCC_u16DynEvap;
static uint16 ACCC_u16DynEvapTimer;
static uint16 ACCC_u16LastEvap;
static uint16 ACCC_u16CoolingCapacityPITimer;
static ACCC_stPidType ACCC_tstCoolingCapacityPID;

#if ACCC_nWITH_EVAP_DELAY_OFFAC
static uint16 ACCC_u16EvapDelayAcOffTimer;
static Bool ACCC_boEvapDelayAcOffFlag;
#endif
#endif

#if(ACCC_nAcType == ACC_u8VariableDisplacAc)	
static uint16 ACCC_u16PwmPIDTimer;
static ACCC_stPidType ACCC_tstVdcPwmPID;
#if(ACCC_nUSE_SHORT_GND_PROHIBITION == True)
static uint16  ACCC_u16VdcShortToGndRepeatCnt;
static uint16  ACCC_u16VdcShortToGndConfirmTimer;
static uint16  ACCC_u16VdcShortToGndRestoreTimer;
static Bool ACCC_boExitShortToGndFlap;
#endif 
#endif 
#if(ACCC_nAcType == ACC_u8ElectricAc) 	

#if(ACCC_nWITH_BATT_MANAGE == True)
static ACCC_tenEcCoolingMode ACCC_enEcCoolingMode = ACCC_nAcOffMode; 
static uint8 ACCC_u8ChillerVOffDelayTimer = 0;
static uint16 ACCC_u16BattCoolKiTimer = 0;
static ACCC_stPidType ACCC_tstCoolingCapacityPidForBatt = 0;  
#endif
#endif

#if(ACCC_nWITH_COOLING_VALVE == True)
static uint8 ACCC_u8TXVOffDelayTimer = 0;
#endif


/*************************/

/*****************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
*
* In this section declare
* - all file local function prototypes needed for your module.
*****************************************************************************/
static void ACCC_vAcRequestOutput(void);
static void ACCC_vInitVariable(void);
static void ACCC_vMmiRequest(void);
static void ACCC_vAcDisplay(void);

static void ACCC_vRequestCondition(void);
static void ACCC_vLimitCondition(void);
static void ACCC_vEvapCondition(void);
static void ACCC_vPowSupplyCondition(void);
static void ACCC_vBlwSpeedCondition(void);


uint8 ACCC_u8Int16ToUint8(int16 i16Input, int16 i16ZeroPoint);
uint16 ACCC_u16Int16ToUint16(int16 i16Input, int16 i16ZeroPoint);
int8 ACCC_i8Int16ToInt8(int16 i16Input);
uint8 ACCC_u8Uint32ToUint8(uint32 u32Input);
uint8 ACCC_u8Uint16ToUint8(uint16 u16Input);
int16 ACCC_i16Int32ToInt16(int32 i32Input);
uint16 ACCC_u16Int32ToUint16(int32 i32Input, int32 i32ZeroPoint);
uint16 ACCC_u16Uint32ToUint16(uint32 u32Input);
static uint16 Alg_u16_3DLookup_16_16_16_Limit( uint16 InputX, uint16 InputY,uint8 SizeX,uint8 SizeY,const uint16* TableX, const uint16* TableY,const uint16* TableZ);

#if(ACCC_nUSE_OAT_PROHIBITION == True)
static void ACCC_vOatCondition(void);
#endif
#if(ACCC_nUSE_MESSAGE_PROHIBITION == True)
static void ACCC_vMessageCondition(void);
#endif

#if(ACCC_nUSE_INTERVAL_OFF_PROHIBITION == True)
static void ACCC_vIntervalOffCondition(void);
#endif

#if(ACCC_nUSE_ENGINE_PROHIBITION == True)
static void ACCC_vEngSpeedCondition(void);
#endif

#if((ACCC_nWITH_PRESSURE_SENSOR==True)||(ACCC_nWITH_PRESSURE_SWITCH==True))
static void ACCC_vPressureCondition(void);
#endif

#if(ACCC_nUSE_ISTP_PROHIBITION == True)
static void ACCC_vIstpStateCondition(void);
#endif

#if((ACCC_nAcType == ACC_u8VariableDisplacAc) || (ACCC_nAcType == ACC_u8ElectricAc))
static void ACCC_vCoolingCapacityPidInit(void);
static void ACCC_vControlCoolingCapacity(void);
static void ACCC_vCoolingCapacityMapToPhysics(void);
static void ACCC_vPhysicsMapToOutput(void);
static void ACCC_vAcEvapTargetTempCal(void);
static void ACCC_vCoolingSystemControl(void);
static uint16 ACCC_u16PidCalculate (int16 i16Error, ACCC_stPidType *pp);
static void ACCC_vCalPIParaAndFeedward(uint16 u16EvapValue, int16 i16EvapError);
#if(ACCC_nHCU_LIMIT_EC_SPEED == True)
static uint16 ACCC_u16HcuLimitEcPowerAndSpeed(uint16 u16TargePhysics);
#endif
#endif

#if(ACCC_nAcType == ACC_u8VariableDisplacAc)	
static void ACCC_vControlAcDisplace(void);
static void ACCC_vVdcEvapCooling(void);
static void ACCC_vVdcDisplaceLimit(void);

#if(ACCC_nUSE_SHORT_GND_PROHIBITION == True)
static void ACCC_vShortToGndCondition(void);
#endif
#if(ACCC_nWITH_TORQUE_OUTPUT == True)
static void ACCC_vCalculateTorque(void);
static uint8 ACCC_vTorqueLookup(uint16 Pressure, uint16 EngineSpd);
#endif
#endif 

#if(ACCC_nAcType == ACC_u8ElectricAc) 	
#if(ACCC_nHCU_LIMIT_EC_SPEED == True)
static void ACCC_vPowerLimitCondition(void);
#endif
static void ACCC_vSpeedToOutput(void);

#if(ACCC_nWITH_AC_DIAG_SIGNAL == True)
static void ACCC_vDiagnosticSignalCondition(void);
#endif
#if(ACCC_nWITH_BATT_MANAGE == True)
static void ACCC_vBattCoolPIDInit(void); 
static uint16 ACCC_vCalBattCoolKiParameter(void);
static void ACCC_vChillerValveCtrl(void);
static void ACCC_vBattRequest(void);
static void ACCC_u16EcBattCoolingSpdCal(void);
static void ACCC_vCalcCoolingCapacityOnlyBattery(void);
#endif
#if(ACCC_nWITH_COOLING_VALVE == True)
static void ACCC_vCoolingValveCtrl(void);
#endif
#endif

/*****************************************************************************
* FILE GLOBAL FUNCTION DEFINITIONS
*
* In this section definition
* - all file Global function definitions needed for your module.
* - all tasks
*****************************************************************************/
/* ===========================================================================
* Function   : void ACCC_vReset (void)
* Description: Reset container function of ACCC
* Takes      : Nothing
* Returns    : Nothing
*/
 void ACCC_vReset (void)
{
	ACCC_SW_VERSION = SW_VERSION;
	
	ACCC_vInitVariable();
}

/* ===========================================================================
* Function   : void ACCC_vInit (void)
* Description: Init function of ACCC
*              Called in Active->On container and through other local functions
* Takes      : Nothing
* Returns    : Nothing
*/
void ACCC_vInit(void)
{
	ACCC_vInitVariable();
}

/* ===========================================================================
* Function   : void ACCC_vDeinit (void)
* Description: De-init function of ACCC
*              Called in On->Active container
* Takes      : Nothing
* Returns    : Nothing
*/
 void ACCC_vDeinit (void)
{
	ACCC_vInitVariable();
}

/* ===========================================================================
* Function   : void Accc_vActive (void)
* Description: Active container function of ACCC
* Takes      : Nothing
* Returns    : Nothing
*/
void ACCC_vActive(void)
{

}

/* ===========================================================================
* Function   : void ACCC_vMain (void)
* Description: Main container function of ACCC
* Takes      : Nothing
* Returns    : Nothing
*/
void ACCC_vMain (void)
{
	if(ACCC_u16WaitTimer)
	{
		ACCC_u16WaitTimer--;
		return;
	}	
	ACCC_vLimitCondition();

#if((ACCC_nAcType == ACC_u8VariableDisplacAc) || (ACCC_nAcType == ACC_u8ElectricAc))
	ACCC_vAcEvapTargetTempCal();
	ACCC_vCoolingSystemControl();
#endif

	/*****AC display************************************************/ 
	ACCC_vAcDisplay();

	/*****The compressor request************************************/ 
	ACCC_vAcRequestOutput();

	ACCC_vPutRteValue();
}

static void ACCC_vInitVariable(void)
{
	ACCC_u8AcActualReq = ACCC_nAcReqOff;
	ACCC_u8AcDisplayInfo = ACCC_nAcDisplayOff;
	ACCC_u8AcOperation = ACCC_nAcReqOff;
	/*Init Off & Error Code*/
	ACCC_AC_ERROR_CODE =ACCC_nNo_Error;
	ACCC_AC_OFF_CODE =ACCC_nNo_Error;
	ACCC_u16WaitTimer = ACCC_u16WaitTime; 	
	
	//for(uint8 u8Index=0; u8Index<Off_nAllCodeNumber; u8Index++)
	//{
		//Set16BitValue(ACCC_AC_OFF_CODE, u8Index);
	//}

	ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nEvapTDisable);
	ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nRequestOff);
    ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nBlwFault);
    ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nBatHiOrLowVol);	
	
#if(ACCC_nUSE_OAT_PROHIBITION == True)
	Set16BitValue(ACCC_AC_OFF_CODE, Off_nOatDisable); 		
#endif

#if(ACCC_nUSE_ENGINE_PROHIBITION == True)
	ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nEngHighSpd);
	ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nEngLowSpd);
#endif

#if(ACCC_nWITH_PRESSURE_SENSOR==True)
	ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nPressureLow);
	ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nPressureHigh);
#endif
#if (ACCC_nWITH_PRESSURE_SWITCH == True)
	ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nPreOutRange);
#endif

#if((ACCC_nAcType == ACC_u8VariableDisplacAc) || (ACCC_nAcType == ACC_u8ElectricAc))
	ACCC_vCoolingCapacityPidInit();
	ACCC_u16EvapTargetTemp = ACCC_au16TargetEvapByBlowout_Y[0];
	ACCC_u16TargeCoolingCapacity = 0U;
	ACCC_u16TargePhysics = 0U;
	ACCC_u16CoolingCapacityPITimer = 0;
	ACCC_u16TargetEvapGradientTimer = 0U;
	ACCC_u16PidParaOatHys = 0U;
	ACCC_boTargetEvapInit = True;	
#if ACCC_nWITH_EVAP_DELAY_OFFAC
	ACCC_u16EvapDelayAcOffTimer = 0U;
	ACCC_boEvapDelayAcOffFlag = False;
#endif
#endif

#if(ACCC_nAcType == ACC_u8VariableDisplacAc)
	ACCC_u16PwmPIDTimer = 0;
	ACCC_u16VdcPwmOutput = 0;
#if(ACCC_nWITH_TORQUE_OUTPUT == True)
	ACCC_u8TorqueOutput = 0;
#endif

#endif

#if(ACCC_nAcType == ACC_u8ElectricAc) 	
	ACCC_u8EcTargetSpeedForCAN = 0U;
	ACCC_u16EcSpeedToOutput = 0U;
#if(ACCC_nOUTPUT_SPEED_TO_POWER)
	ACCC_u8EcTargetPowerForCAN = 0U;
#endif

#if(ACCC_nHCU_LIMIT_EC_SPEED == True)
	ACCC_u16HcuLimitEcPower = 0U;
	ACCC_u16HcuLimitEcSpd = 0U;
#endif
	

#if(ACCC_nWITH_BATT_MANAGE == True)
	ACCC_vBattCoolPIDInit();
	/*Init HW Pin*/
	ACCC_u8ChillerValveReq = Off;
	ACCC_ChillerValveOutput(Pin_Off);
	ACCC_u8BattCoolingReq = ACCC_nAcReqOff;
	ACCC_u8ChillerVOffDelayTimer = 0U;
	ACCC_u16BattCoolKiTimer = ACCC_u16EcSpeedForBattKiTime;
	ACCC_enEcCoolingMode = ACCC_nAcOffMode;
#endif
#endif

#if(ACCC_nWITH_COOLING_VALVE == True)
	ACCC_u8TXVOffDelayTimer = 0U;
	ACCC_u8AcValveReq = Off;
	ACCC_AcValvePinOutput(Pin_Off);
#endif

}

/* ===========================================================================
* Function   : ACCC_vMmiRequest(void)
* Description: A/C request process
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vMmiRequest(void)
{
	uint8 u8MmiAcMode;
	ACCC_enMmiAcCtrlImport(&ACCC_u8AcOperation);
	ACCC_enMmiAcModeImport(&u8MmiAcMode);
	#if(ACCC_nUSE_HI_PROHIBITION == True)
	uint8 u8MmiSetTempL;
	ACCC_enMmiSetTempLeftImport(&u8MmiSetTempL);
	#if(SYC_ZONES == 2)
	uint8 u8MmiSetTempR;
	ACCC_enMmiSetTempRightImport(&u8MmiSetTempR);
	#endif
	#endif
	
	#if(ACCC_nUSE_SI_PROHIBITION == True)
	uint16 u16CcsTempDiffDr;
	ACCC_enCcsTempDiffDrImport(&u16CcsTempDiffDr);
	#endif
	
	if(u8MmiAcMode == ACCC_nMmiAcModeAuto)
	{/*AUTO state, A/C always On*/
	#if(ACCC_nUSE_HI_PROHIBITION == True)
		#if(SYC_ZONES == 2)
		if((u8MmiSetTempL == ACCC_nMmiSetTempHi) && (u8MmiSetTempR == ACCC_nMmiSetTempHi))
		#endif
		#if(SYC_ZONES == 1)
		if(u8MmiSetTempL == ACCC_nMmiSetTempHi)
		#endif
		{/*SetTemp Hi, shut down A/C for energy saving*/
			ACCC_u8AcOperation = ACCC_nAcReqOff;
		}
		else
	#endif
		{
		#if(ACCC_nUSE_SI_PROHIBITION == True)
			if ( u16CcsTempDiffDr < ACCC_u16SiEnable )
			{
				ACCC_u8AcOperation = ACCC_nAcReqOn;
			}
			else if ( u16CcsTempDiffDr > ACCC_u16SiDisable )
			{
				ACCC_u8AcOperation = ACCC_nAcReqOff;
			}
			else
			{
			}
		#else
			ACCC_u8AcOperation = ACCC_nAcReqOn;
		#endif
		}
	}
}


/* ===========================================================================
* Function   : ACCC_vAcRequestOutput(void)
* Description: A/C request process
* Takes      : Nothing
* Returns    : AC request: u8ReturnAcReq
*/
static void ACCC_vAcRequestOutput (void)
{
	if(ACCC_AC_OFF_CODE == ACCC_nNo_Error)
	{
		ACCC_u8AcActualReq = ACCC_nAcReqOn;
	}
	else
	{
		ACCC_u8AcActualReq = ACCC_nAcReqOff;
	}

    if(ACCC_u16GetCcpCtrlFlag(Acc_nSetAcReq))
    {
        ACCC_u8AcActualReq = (uint8)ACCC_u16GetCcpCtrlValue(Acc_nSetAcReq);
    }
}


/* ===========================================================================
* Function   : void ACCC_vAcDisplay(void)
* Description: Processing the A/C display info
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vAcDisplay(void)
{	
	uint8 u8MmiAcMode;
	ACCC_enMmiAcModeImport(&u8MmiAcMode);
	
	if(ACCC_u8AcOperation == ACCC_nAcReqOn)
	{
		#if ACCC_nTTOFF_WHILE_OATLOW
		if((u8MmiAcMode == ACCC_nMmiAcModeAuto)\
			&&(Check16BitValid(ACCC_AC_OFF_CODE, Off_nOatDisable)==True))
		{/*A/C TT turn off while OAT disable*/
			ACCC_u8AcDisplayInfo = ACCC_nAcDisplayOff;
		}
		else
		{
			ACCC_u8AcDisplayInfo = ACCC_nAcDisplayOn;
		}
		#else
		ACCC_u8AcDisplayInfo = ACCC_nAcDisplayOn;
		#endif
	}
	else
	{
		ACCC_u8AcDisplayInfo = ACCC_nAcDisplayOff;
	}
			
}



/* ===========================================================================
* Function   : void ACCC_vLimitCondition(void)
* Description: Checking the compressor limit conditions, if all of conditions 
			   premit compressor ON, output compressor request is ON and calculate
			   parameters.
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vLimitCondition(void)
{
	ACCC_vRequestCondition();
	
	ACCC_vPowSupplyCondition();
	
	ACCC_vEvapCondition();

	ACCC_vBlwSpeedCondition();

#if(ACCC_nUSE_OAT_PROHIBITION == True)
	ACCC_vOatCondition();
#endif
	
#if(ACCC_nUSE_ENGINE_PROHIBITION == True)
	ACCC_vEngSpeedCondition();
#endif

#if(ACCC_nUSE_MESSAGE_PROHIBITION == True)
	ACCC_vMessageCondition();
#endif

#if(ACCC_nUSE_INTERVAL_OFF_PROHIBITION == True)
	ACCC_vIntervalOffCondition();
#endif

#if((ACCC_nWITH_PRESSURE_SENSOR==True)||(ACCC_nWITH_PRESSURE_SWITCH==True))
	ACCC_vPressureCondition();
#endif
	
#if(ACCC_nUSE_ISTP_PROHIBITION == True)
	ACCC_vIstpStateCondition();
#endif

#if(ACCC_nAcType == ACC_u8VariableDisplacAc)	
#if(ACCC_nUSE_SHORT_GND_PROHIBITION == True)
	ACCC_vShortToGndCondition();
#endif
#endif

#if(ACCC_nAcType == ACC_u8ElectricAc)	
#if(ACCC_nHCU_LIMIT_EC_SPEED == True)
	ACCC_vPowerLimitCondition();
#endif

#if(ACCC_nWITH_AC_DIAG_SIGNAL == True)
	ACCC_vDiagnosticSignalCondition();
#endif
#endif
}

static void ACCC_vRequestCondition(void)
{
	ACCC_vMmiRequest();
#if(ACCC_nWITH_BATT_MANAGE == True)&&(ACCC_nAcType == ACC_u8ElectricAc)
	ACCC_vBattRequest();  
	if((ACCC_u8AcOperation == ACCC_nAcReqOn)||(ACCC_u8BattCoolingReq = ACCC_nAcReqOn))
#else
	if(ACCC_u8AcOperation == ACCC_nAcReqOn)
#endif
	{
		ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nRequestOff); 	
	}
	else
	{
		ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nRequestOff); 	
	}
}

/* ===========================================================================
* Function   : void ACCC_vEvapCondition(void)
* Description: evap. limit condition of A/C request
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vEvapCondition(void)
{
	uint16 u16EvapValue = 0;
#if ACCC_nWITH_ECON_MODE
	uint8 u8MmiAcMode;
#endif
#if (!ACCC_DEVELOPMENT_DEBUG)
	ACCC_enEvapAcValueImport(&u16EvapValue);
#endif
		
#if ACCC_nWITH_ECON_MODE
	ACCC_enMmiAcCtrlImport(&ACCC_u8AcOperation);
	ACCC_enMmiAcModeImport(&u8MmiAcMode);
	if((ACCC_u8AcOperation == ACCC_nAcReqOffEcon) && (u8MmiAcMode == ACCC_nMmiAcModeManu))//change MODEManual to ACModeManual
   {
	/* ----ECON MODE ---- */
	if( u16EvapValue <= ACCC_u16EvapTempDisableEcon )
	{
		Set16BitValue(ACCC_AC_OFF_CODE, Off_nEvapTDisable);			
	}
	else if( u16EvapValue >= ACCC_u16EvapTempEnableEcon )
	{
		Clear16BitValue(ACCC_AC_OFF_CODE, Off_nEvapTDisable); 
	}
 	else
	{
	/* If we are in the hysteresis band, no changes are made. */
	}
   }
   else
#endif
	{
#if ACCC_nWITH_EVAP_DELAY_OFFAC && (ACCC_nAcType == ACC_u8VariableDisplacAc) || (ACCC_nAcType == ACC_u8ElectricAc)
		if(u16EvapValue <= ACCC_u16EvapTempDisable)
		{	
			ACCC_boEvapDelayAcOffFlag = True;
			if(u16EvapValue <= ACCC_u16EvapTempFreezingTemp )
			{
				Set16BitValue(ACCC_AC_OFF_CODE, Off_nEvapTDisable);			
			}
		}
		else if(u16EvapValue >= ACCC_u16EvapTempEnable)
		{
			Clear16BitValue(ACCC_AC_OFF_CODE, Off_nEvapTDisable); 
			ACCC_u16EvapDelayAcOffTimer = 0;
			ACCC_boEvapDelayAcOffFlag = False;
		}
		else
		{
			/*Hysteresis range, do nothing*/
		}

		if(ACCC_boEvapDelayAcOffFlag == True)
		{
			if(ACCC_u16EvapDelayAcOffTimer > ACCC_u16EvapDelayAcOffTime)
			{
				Set16BitValue(ACCC_AC_OFF_CODE, Off_nEvapTDisable);			
			}
			else
			{
				ACCC_u16EvapDelayAcOffTimer ++;
			}
		}
#else
		if(u16EvapValue <= ACCC_u16EvapTempDisable)
		{	 
			Set16BitValue(ACCC_AC_OFF_CODE, Off_nEvapTDisable);			
		}
		else if(u16EvapValue >= ACCC_u16EvapTempEnable)
		{
			Clear16BitValue(ACCC_AC_OFF_CODE, Off_nEvapTDisable); 
		}
		else
		{
			/*Hysteresis range, do nothing*/
		}
#endif
	}	
}

static void ACCC_vPowSupplyCondition(void)
{
	uint8 boLowVoltage;
	uint8 boHighVoltage;
	ACCC_enLowVoltageFlagImport(&boLowVoltage);
	ACCC_enHighVoltageFlagImport(&boHighVoltage);
	if((boLowVoltage==True)||(boHighVoltage==True))
	{
		ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nBatHiOrLowVol);	
	}
	else
	{
		ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nBatHiOrLowVol); 	
	}
}
		
/* ===========================================================================
* Function   : void ACCC_vBlwSpeedCondition(void)
* Description: Blower voltage limit condition of A/C request
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vBlwSpeedCondition(void)
{
	uint16 u16BlwTarget = 0;
    uint16 u16BlwDrvErr = 0;

#if (!ACCC_DEVELOPMENT_DEBUG)	
	ACCC_enBlowerTargetImport(&u16BlwTarget);
    ACCC_enBlowerErrorImport(&u16BlwDrvErr);
#endif	
	/***Checking Blwoer protect limited ***************************************/ 
	if((u16BlwTarget <= 0u) || (u16BlwDrvErr != 0u))/*modify by Yang Shengli,Bctl error occur,20170518*/
	{
		ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nBlwFault);			
	}
	else //if(u16BlwTarget >= (ACCC_nu8BlwTargetVol + ACCC_nu8BlwTargetVolHys))
	{
		ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nBlwFault);			
	}
}


#if(ACCC_nUSE_OAT_PROHIBITION == True)
/* ===========================================================================
* Function   : void ACCC_vOatCondition(void)
* Description: OAT limit condition of A/C request
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vOatCondition(void)
{
	uint16 u16OatValue = 0;

#if (!ACCC_DEVELOPMENT_DEBUG)
	ACCC_enOatValueImport(&u16OatValue);
#endif
	if(u16OatValue <= ACCC_u16AmbTempDisable)
	{
		ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nOatDisable);			
	}
	else if(u16OatValue >= ACCC_u16AmbTempEnable)
	{
		ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nOatDisable);			
	}
	else
	{/*Hysteresis range, do nothing*/}

}
#endif	

/* ===========================================================================
* Function   : void ACCC_vEngSpeedCondition(void)
* Description: Engine speed limit condition of A/C request
* Takes      : Nothing
* Returns    : Nothing
*/
#if(ACCC_nUSE_ENGINE_PROHIBITION == True)
static void ACCC_vEngSpeedCondition(void)
{
	uint16 u16EngnieSpeed = 0;
	uint16 u16VehSpeed = 0;
	ACCC_enEngineSpeedImport(&u16EngnieSpeed);
	ACCC_enVehicleSpeedImport(&u16VehSpeed);
	
	/***Checking engine speed**************************************************/ 
	if (u16VehSpeed <= ACCC_u16VehLowSpd)
	{
		if (u16EngnieSpeed >= (ACCC_u16EngLowSpd + ACCC_u16EngLowSpdHyst))
		{/*Engine is not low speed, detect high speed*/ 
			ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nEngLowSpd);
			if (u16EngnieSpeed >= ACCC_u16EngHighSpd)
			{/*Engine high speed*/ 
				ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nEngHighSpd);
			}
			else if(u16EngnieSpeed <= (ACCC_u16EngHighSpd - ACCC_u16EngHighSpdHyst))
			{
				ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nEngHighSpd);
			}
			else
			{/*Hysteresis range, do nothing*/}
		}
		else if(u16EngnieSpeed <= ACCC_u16EngLowSpd)
		{
			ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nEngLowSpd);
			ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nEngHighSpd);
		}
		else
		{/*Hysteresis range, do nothing*/
			ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nEngHighSpd);
		}
	}
	else
	{
		ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nEngLowSpd);
		ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nEngHighSpd);
	}
}
#endif


/* ===========================================================================
* Function   : void ACCC_vEngSpeedCondition(void)
* Description: Discharge pressure limit condition of A/C request
* Takes      : Nothing
* Returns    : Nothing
*/
#if((ACCC_nWITH_PRESSURE_SENSOR==True)||(ACCC_nWITH_PRESSURE_SWITCH==True))
static void ACCC_vPressureCondition(void)
{
#if(ACCC_nWITH_PRESSURE_SENSOR == True)
	uint16 u16PressureValue;
	
	ACCC_enPressureValueImport(&u16PressureValue);
	
	if (u16PressureValue <= ACCC_u16HighPressureValue-ACCC_u16HighPressureHys)
	{/*Not High pressure, detect low pressure*/
		ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nPressureHigh);
		if (u16PressureValue < ACCC_u16LowPressureValue)
		{/*Low pressure*/ 
			ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nPressureLow);
		}
		else if(u16PressureValue >= (ACCC_u16LowPressureValue+ACCC_u16LowPressureHys))
		{
			ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nPressureLow);
		}
		else
		{/*Hysteresis range, do nothing*/}
	}
	else if(u16PressureValue > ACCC_u16HighPressureValue)
	{
		ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nPressureHigh);
		ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nPressureLow);
	}
	else
	{/*Hysteresis range, do nothing*/ 
		ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nPressureLow);
	}
	
#endif
#if (ACCC_nWITH_PRESSURE_SWITCH == True)
	uint16 u16HiLoPreSwitchValue = 0;
	
    #if (!ACCC_DEVELOPMENT_DEBUG)
	ACCC_enPressureHiLoSwitchValueImport(&u16HiLoPreSwitchValue);
    #endif
	if(u16HiLoPreSwitchValue <= ACCC_u16PreHiOrLowValue)
	{
		ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nPreOutRange);
	}
	else
	{
		ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nPreOutRange);	
	}
#endif
}
#endif

#if(ACCC_nUSE_ISTP_PROHIBITION == True)
/* ===========================================================================
* Function   : void ACCC_vMessageCondition(void)
* Description: Blower voltage limit condition of A/C request
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vIstpStateCondition(void)
{
	if(ACCC_stInputList.u8CanEngSt == ACCC_IsEngineStopping) 
	{/*If the I-Stop state is $6: ISS engine stopping and $7: ISS engine stopped, the A/C request is prohibited.*/ 
		ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nIstpDisable);			
	}
	else
	{
		ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nIstpDisable);			
	}
}
#endif

#if(ACCC_nUSE_MESSAGE_PROHIBITION == True)
/* ===========================================================================
* Function   : void ACCC_vMessageCondition(void)
* Description: Blower voltage limit condition of A/C request
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vMessageCondition(void)
{

}
#endif

#if(ACCC_nUSE_INTERVAL_OFF_PROHIBITION == True)
/* ===========================================================================
* Function   : void ACCC_vIntervalOffCondition(void)
* Description: Blower voltage limit condition of A/C request
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vIntervalOffCondition(void)
{
		if ( ACCC_u16ACPSpdFB == 0 )
		{
			if ( ACCC_u8OnIntervalTime > ACCC_u8TimeInterval )//now the compress is off, so begin to count the time
			{
				ACCC_u8OnIntervalTime = 0;
			}
			
			if ( ACCC_u8OnIntervalTime < ACCC_u8TimeInterval )
			{
				ACCC_u8OnIntervalTime++;
			}
		}
		else
		{
			ACCC_u8OnIntervalTime = ACCC_u8TimeInterval+1;
		}

		//for the compress off time is less than 10seconds and now can't to on
		if ( ACCC_u8OnIntervalTime < ACCC_u8TimeInterval)
		{
			ACCC_u16ACPSpeedSet = 0;
		}
}
#endif

#if((ACCC_nAcType == ACC_u8VariableDisplacAc) || (ACCC_nAcType == ACC_u8ElectricAc))
static void ACCC_vCoolingCapacityPidInit(void)
{
	/***************************************************************************************
	* FUNCTION LOCAL DEFINITIONS
	*
	* In this section define
	* - all function local type definitions
	* - all function local ROM-CONSTants
	* - all function local variables (auto and STATIC)
	****************************************************************************************/
	
	/***************************************************************************************
	* FUNCTION CODE
	****************************************************************************************/

	ACCC_tstCoolingCapacityPID.LastError = 0;     			//Error[-1]
	ACCC_tstCoolingCapacityPID.PrevError = 0;     			//Error[-2] 
	ACCC_tstCoolingCapacityPID.SumError = 0;			//Sums of Errors
	ACCC_tstCoolingCapacityPID.UpperDiffLimit = ACCC_i16EvapTempDiffMax;
	ACCC_tstCoolingCapacityPID.LowerDiffLimit = ACCC_i16EvapTempDiffMin;
	ACCC_tstCoolingCapacityPID.UpperLimit = ACCC_au16CoolingCapacityMax;
	ACCC_tstCoolingCapacityPID.LowerLimit = ACCC_au16CoolingCapacityMin;
	ACCC_tstCoolingCapacityPID.OutputLimitUsed = True;
	ACCC_tstCoolingCapacityPID.UpperSumErrorLimit = (int32)((int32)ACCC_au16CoolingCapacityMax * (int32)ACCC_u16KiBaseConst);
	ACCC_tstCoolingCapacityPID.LowerSumErrorLimit = -(int32)((int32)ACCC_au16CoolingCapacityMax * (int32)ACCC_u16KiBaseConst);
	ACCC_u16CoolingCapacityPITimer = ACCC_u16CoolingCapacityPidCalcTime;
}

/********************* Temperature PID****************************/
uint16 ACCC_u16PidCalculate (int16 i16Error, ACCC_stPidType *pp)
 {
	int16 Error = i16Error;
	int16 dError = 0;
	int32 i32PidOutput = 0;

	if(NULL == pp)
	{
		return (int16)i32PidOutput;
	}
	
	/****limit input: error*/
	if(Error > pp->UpperDiffLimit)
		Error = pp->UpperDiffLimit;

	if(Error < pp->LowerDiffLimit)
		Error = pp->LowerDiffLimit;
		
	/****Caculate parameter*/	
	/****Accumulating intergrator*/
	pp->SumError += (int32)(Error) * (int32)(pp->Ki); 

	/****current derivative */
	dError = pp->LastError - pp->PrevError; 		
	pp->PrevError = pp->LastError;
	pp->LastError = Error;

	/*limit sum error*/
	if(pp->SumError > pp->UpperSumErrorLimit) 
	{
		pp->SumError = pp->UpperSumErrorLimit;
	}
	else if(pp->SumError < pp->LowerSumErrorLimit) 
	{
		pp->SumError = pp->LowerSumErrorLimit;
	}
	else
	{

	}		
	/*calculate P part*/
	i32PidOutput = ((int32)(pp->Kp) * (int32)Error)/ACCC_u16KpBaseConst+ (uint16)(pp->FeedForward);      				

	/*calculate I part*/
	i32PidOutput += (int32)(pp->SumError)/ACCC_u16KiBaseConst;

	/*calculate D part*/
	i32PidOutput += ((int32)(pp->Kd) * (int32)dError)*ACCC_u16KdBaseConst;

	/*output and limit*/		
	if(pp->OutputLimitUsed == True)
	{
		if(i32PidOutput > pp->UpperLimit)
		{
			i32PidOutput = pp->UpperLimit;
			if(Error > 0)
			{
				pp->SumError -= (int32)(Error) * (int32)(pp->Ki);
			}
		}
		if(i32PidOutput < pp->LowerLimit)
		{
			i32PidOutput = pp->LowerLimit;	
			if(Error < 0)
			{
				pp->SumError -= (int32)(Error) * (int32)(pp->Ki);
			}
		}
	}

	return (uint16)i32PidOutput; 
}

static void ACCC_vCoolingSystemControl(void)
{
	ACCC_vControlCoolingCapacity();
	ACCC_vCoolingCapacityMapToPhysics();
	ACCC_vPhysicsMapToOutput();
	
#if(ACCC_nAcType == ACC_u8VariableDisplacAc) 	
	
#if(ACCC_nWITH_TORQUE_OUTPUT == True)
	ACCC_vCalculateTorque();
#endif

#endif 

#if(ACCC_nAcType == ACC_u8ElectricAc) 	

#if(ACCC_nWITH_COOLING_VALVE == True) 	
	ACCC_vCoolingValveCtrl();
#endif

#if(ACCC_nWITH_BATT_MANAGE == True)
	ACCC_vChillerValveCtrl();
#endif

#endif
}
static void ACCC_vCoolingCapacityMapToPhysics(void)
{
	uint16 *pu16_1=NULL;	
	uint16 *pu16_2=NULL;	
	uint16  u16TargePhysics = 0;
	
	if(ACCC_u16TargeCoolingCapacity > 0)
	{
		pu16_1 = (uint16 *)ACCC_au16CoolingCapacityToPhysics_X;		
		pu16_2 = (uint16 *)ACCC_au16CoolingCapacityToPhysics_Y;
		u16TargePhysics = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,
							ACCC_u16TargeCoolingCapacity,ACCC_nCoolingCapacityToPhysics_Len);
	}
	else
	{
		u16TargePhysics = 0;
	}
	#if(ACCC_nHCU_LIMIT_EC_SPEED == True)
	u16TargePhysics = ACCC_u16HcuLimitEcPowerAndSpeed(u16TargePhysics);
       #endif
	ACCC_VALUE_GRADIENT(u16TargePhysics, ACCC_u16TargePhysics, ACCC_u16TargePhysicsIncGradient,ACCC_u16TargePhysicsDecGradient);
}

static void ACCC_vPhysicsMapToOutput(void)
{
#if(ACCC_nAcType == ACC_u8VariableDisplacAc) 	
	ACCC_vCurrToPwm();

#elif(ACCC_nAcType == ACC_u8ElectricAc) 	
	ACCC_vSpeedToOutput();
#endif
}

static void ACCC_vControlCoolingCapacity(void)
{
  	uint16 u16EvapValue=0U;
	int32 i32Tempdiff = 0;
	int16 i16TempDiff=0;
	
	if(ACCC_AC_OFF_CODE == ACCC_nNo_Error)
	{
		if(ACCC_u8AcOperation == ACCC_nAcReqOn)
		{
			ACCC_enEvapAcValueImport(&u16EvapValue);
			i32Tempdiff = ((int32)u16EvapValue - (int32)ACCC_u16EvapTargetTemp);
			i16TempDiff = ACCC_i16Int32ToInt16(i32Tempdiff);/*Limit overflow*/
			
			ACCC_vCalPIParaAndFeedward(u16EvapValue, i16TempDiff);

			if(ACCC_u16CoolingCapacityPITimer >= ACCC_u16CoolingCapacityPidCalcTime)
			{
				ACCC_u16CoolingCapacityPITimer = 0;
				
				ACCC_u16TargeCoolingCapacity = ACCC_u16PidCalculate(i16TempDiff, &ACCC_tstCoolingCapacityPID);
			}
			else
			{
				ACCC_u16CoolingCapacityPITimer++;
			}
		}
		#if(ACCC_nWITH_BATT_MANAGE == True)
		else if(ACCC_u8BattCoolingReq == ACCC_nAcReqOn)
		{
			ACCC_vCalcCoolingCapacityOnlyBattery();
		}
	    	#endif 
	}
	else
	{
		ACCC_tstCoolingCapacityPID.SumError = 0;
		ACCC_u16TargeCoolingCapacity = 0;
		#if(ACCC_nWITH_BATT_MANAGE == True)
		ACCC_u16BattCoolKiTimer = ACCC_u16EcSpeedForBattKiTime;
		ACCC_tstCoolingCapacityPidForBatt.SumError = 0;
	    	#endif 
	}
}

/* ===========================================================================
* Function   : void ACCC_vAcEvapTargetTempCal(void)
* Description: Calculate the Evap. target temperature for A/C ctrl
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vAcEvapTargetTempCal(void)
{
	/***************************************************************************************
	* FUNCTION LOCAL DEFINITIONS
	*
	* In this section define
	* - all function local type definitions
	* - all function local ROM-CONSTants
	* - all function local variables (auto and STATIC)
	****************************************************************************************/
	uint16 u16TargetEvapTempByBlowout;
	uint16 u16TargetEvapTempByOatOffset;
	uint16 u16TargetEvapTemp;
	#if(ACCC_nATCorETC == ATC_u8ATC)
	uint16 u16BlowoutTempL=0U;
#if SYC_ZONES >=2
	uint16 u16BlowoutTempR=0U;
#endif
	#endif
	uint16 u16BlwTarget;
	uint16 u16MinBlowoutT=0U;
	uint8 u8MmiAcMode=0U;
	uint16 u16OatValue=0U;
	uint8 u8RecirState=0;
	uint16 *pu16_1=NULL;	
	uint16 *pu16_2=NULL;	
#if(ACCC_nWITH_BATT_MANAGE == True)&&(ACCC_nAcType == ACC_u8ElectricAc) 	
	uint16 u16BattCoolantInTarget = 0U;
	uint16 u16BattCoolingMode = 0U;
#endif
	
	/***************************************************************************************
	* FUNCTION CODE
	****************************************************************************************/
	ACCC_enMmiAcModeImport(&u8MmiAcMode);

	if(u8MmiAcMode == ACCC_nMmiAcModeDef)
	{
		ACCC_u16EvapTargetTemp = ACCC_u16TargetEvapByDef;
		return;
	}
	
	ACCC_enOatValueImport(&u16OatValue);
	ACCC_enRfaDispImport(&u8RecirState);
	
	#if(ACCC_nATCorETC == ATC_u8ATC)
	ACCC_enCcsBlowoutDrImport(&u16BlowoutTempL);
	u16MinBlowoutT = u16BlowoutTempL;
	
	#if SYC_ZONES>=2
	ACCC_enCcsBlowoutPsImport(&u16BlowoutTempR);
	u16MinBlowoutT = ACCC_MIN_VALUE(u16BlowoutTempL,u16BlowoutTempR);
	#endif
	#elif(ACCC_nATCorETC == ATC_u8ETC)
	u16MinBlowoutT = Knob_MacPosition;
	#endif
	pu16_1 = (uint16*)&ACCC_au16TargetEvapByBlowout_X[0];
	pu16_2 = (uint16*)&ACCC_au16TargetEvapByBlowout_Y[0];
	u16TargetEvapTempByBlowout = ALG_u16CurveLookup_16_16_Limit(pu16_1, pu16_2, u16MinBlowoutT,\
											ACCC_nTargetEvapByBlowoutTbl_Len); 

	if(u8RecirState == 0)//fresh
	{
		u16TargetEvapTempByOatOffset = u16OatValue - ACCC_u16TargetEvapByOatOffsetFresh;
	}
	else //recir
	{
		u16TargetEvapTempByOatOffset = u16OatValue - ACCC_u16TargetEvapByOatOffsetRec;
	}
	if(u16TargetEvapTempByOatOffset < ACCC_au16TargetEvapByBlowout_Y[0])
	{
		u16TargetEvapTempByOatOffset = ACCC_au16TargetEvapByBlowout_Y[0];
	}
	u16TargetEvapTemp = ACCC_MIN_VALUE(u16TargetEvapTempByBlowout, u16TargetEvapTempByOatOffset);

#if(ACCC_nWITH_BATT_MANAGE == True)&&(ACCC_nAcType == ACC_u8ElectricAc) 	

	ACCC_enBattCoolantInTargetTempImport(&u16BattCoolantInTarget);
	ACCC_enBattCoolingModeImport(&u16BattCoolingMode);
	/****Used min value of evap and water in target temp. for target temp. if battery cooling req is true****/ 
	if(ACCC_u8BattCoolingReq == ACCC_nAcReqOn)
	{	/*ACCC_u16ThermoOffset shall be calibration*/ 
		if(u16BattCoolantInTarget < ACCC_u16TargetEvapByThermoOffset)
		{/*Limit Overflow*/
			u16BattCoolantInTarget = ACCC_u16TargetEvapByThermoOffset;
		}
		u16BattCoolantInTarget = u16BattCoolantInTarget - ACCC_u16TargetEvapByThermoOffset;
		
		if(u16BattCoolantInTarget < ACCC_au16TargetEvapByBlowout_Y[0])
		{
			u16BattCoolantInTarget = ACCC_au16TargetEvapByBlowout_Y[0];
		}
		u16TargetEvapTemp = ACCC_MIN_VALUE(u16TargetEvapTemp, u16BattCoolantInTarget);
	}
#endif
#if (!ACCC_DEVELOPMENT_DEBUG)	
	ACCC_enBlowerTargetImport(&u16BlwTarget);
#endif	
	/***Checking Blwoer protect limited ***************************************/ 
	if(u16BlwTarget <= 0)
	{
		ACCC_boTargetEvapInit = True;	
	}
	if(ACCC_boTargetEvapInit == True)
	{
		ACCC_boTargetEvapInit = False;
		ACCC_u16EvapTargetTemp = u16TargetEvapTemp;
		return; 
	}
	if(ACCC_u16EvapTargetTemp < u16TargetEvapTemp)
	{
		if(ACCC_u16TargetEvapGradientTimer >= ACCC_u16TargetEvapGradientTime*10)
		{
			ACCC_u16TargetEvapGradientTimer = 0;
			
			ACCC_u16EvapTargetTemp += ACCC_u16TargetEvapGradientTemp;
		
			if(ACCC_u16EvapTargetTemp > ACCC_au16TargetEvapByBlowout_Y[ACCC_nTargetEvapByBlowoutTbl_Len-1])
			{
				ACCC_u16EvapTargetTemp = ACCC_au16TargetEvapByBlowout_Y[ACCC_nTargetEvapByBlowoutTbl_Len-1];
			}					
		}				
		ACCC_u16TargetEvapGradientTimer++;
	}
	else
	{
		ACCC_u16EvapTargetTemp = u16TargetEvapTemp;
		ACCC_u16TargetEvapGradientTimer = 0;
	}
	ACCC_vCcpInputForce();
}
/* ===========================================================================*/
/* Function   : void ACCC_vCalPIParaAndFeedward(void)
* Description: PID control parameters calculating for A/C speed
* Takes      : Nothing
* Returns    : Nothing
*/
/* ===========================================================================*/
static void ACCC_vCalPIParaAndFeedward(uint16 u16EvapValue, int16 i16EvapError)
{
	int32 i32Err;
	uint16 u16Ki;
	uint16 u16Kp;
	//uint16 u16PreCtl;

	uint16 *pu16_1=NULL;
	uint8 u8BlowerLvl;
	
	uint8 u8RecirState=0;
	uint16 u16InletTemp=0;

	ACCC_enRfaDispImport(&u8RecirState);
	ACCC_enMmiBctlCtrlImport(&u8BlowerLvl);/* ;YTY 2015/4/24 */
		
	if(u8RecirState == 0)
	{	/* use the OAT value when in the fresh mode*/
		ACCC_enOatValueImport(&u16InletTemp);
	}
	else
	{	/* use the ICT value when in the recirculation mode*/
		ACCC_enIctValueImport(&u16InletTemp);
	}	
	
	/*OAT shall be have a hysteresis value */ 
	pu16_1 = &ACCC_u16PidParaOatHys;
	ALG_vHysteresis_16(pu16_1,u16InletTemp, ACCC_u16InletTempHysForPidPara);

	if (ACCC_u16DynEvapTimer >= ACCC_u16CalcDynEvapTime)
	{
		ACCC_u16DynEvapTimer = 0;

		if  (ACCC_u8DynEvapInit == False)
		{
			ACCC_u8DynEvapInit = True;
			ACCC_u16LastEvap = u16EvapValue;
		}

		i32Err = (int32)u16EvapValue - (int32)ACCC_u16LastEvap + 640;

		if (i32Err > USHRT_MAX)
		{
			ACCC_u16DynEvap = USHRT_MAX;
		}
		else if (i32Err < 0)
		{
			ACCC_u16DynEvap = 0;
		}
		else
		{
			ACCC_u16DynEvap = (uint16)i32Err;
		}

		ACCC_u16LastEvap = u16EvapValue;	
	}
	else
	{
		ACCC_u16DynEvapTimer++;
	}
	
	if(u8BlowerLvl <= 1)
	{	/* Select the first curve for searching the value.*/
		u16Ki = Alg_u16_3DLookup_16_16_16_Limit(ACCC_u16DynEvap,  i16EvapError, \
			ACCC_nKiTable_Len, ACCC_nKiTable_Len, \
			ACCC_au16KiDynEvap_X, ACCC_au16KiEvapErr_Y, \
			&ACCC_au16Ki_Z1[0][0]);
		
		if (u16Ki > CHAR_MAX)
		{
			ACCC_tstCoolingCapacityPID.Ki = CHAR_MAX;
		}
		else
		{
			ACCC_tstCoolingCapacityPID.Ki = (uint8)u16Ki; 
		}

		u16Kp = Alg_u16_3DLookup_16_16_16_Limit(u16InletTemp,  i16EvapError, \
			ACCC_nKpTable_Len, ACCC_nKpTable_Len,  \
			ACCC_au16KpInletTemp_X, ACCC_au16KpEvapErr_Y, \
			&ACCC_au16Kp_Z1[0][0]);
		
		if (u16Kp > CHAR_MAX)
		{
			ACCC_tstCoolingCapacityPID.Kp = CHAR_MAX;
		}
		else
		{
			ACCC_tstCoolingCapacityPID.Kp = (uint8)u16Kp; 
		}

		ACCC_tstCoolingCapacityPID.FeedForward = Alg_u16_3DLookup_16_16_16_Limit(u16InletTemp,  ACCC_u16EvapTargetTemp, \
			ACCC_nKfTable_Len, ACCC_nKfTable_Len,  \
			ACCC_au16KfInletTemp_X, ACCC_au16KfTargetEvap_Y, \
			&ACCC_au16Kf_Z1[0][0]);


	}
	else if(u8BlowerLvl <= 3)
	{	/* Select the first & second curves for generating the value, then search it for the value.*/
		u16Ki = Alg_u16_3DLookup_16_16_16_Limit(ACCC_u16DynEvap,  i16EvapError, \
			ACCC_nKiTable_Len, ACCC_nKiTable_Len, \
			ACCC_au16KiDynEvap_X, ACCC_au16KiEvapErr_Y, \
			&ACCC_au16Ki_Z2[0][0]);
		
		if (u16Ki > CHAR_MAX)
		{
			ACCC_tstCoolingCapacityPID.Ki = CHAR_MAX;
		}
		else
		{
			ACCC_tstCoolingCapacityPID.Ki = (uint8)u16Ki; 
		}

		u16Kp = Alg_u16_3DLookup_16_16_16_Limit(u16InletTemp,  i16EvapError, \
			ACCC_nKpTable_Len, ACCC_nKpTable_Len,  \
			ACCC_au16KpInletTemp_X, ACCC_au16KpEvapErr_Y, \
			&ACCC_au16Kp_Z2[0][0]);
		
		if (u16Kp > CHAR_MAX)
		{
			ACCC_tstCoolingCapacityPID.Kp = CHAR_MAX;
		}
		else
		{
			ACCC_tstCoolingCapacityPID.Kp = (uint8)u16Kp; 
		}

		ACCC_tstCoolingCapacityPID.FeedForward = Alg_u16_3DLookup_16_16_16_Limit(u16InletTemp,  ACCC_u16EvapTargetTemp, \
			ACCC_nKfTable_Len, ACCC_nKfTable_Len,  \
			ACCC_au16KfInletTemp_X, ACCC_au16KfTargetEvap_Y, \
			&ACCC_au16Kf_Z2[0][0]);
	}
	else if (u8BlowerLvl <= 5)
	{	/* Select the second & third curves for generating the value, then search it for the value.*/
		u16Ki = Alg_u16_3DLookup_16_16_16_Limit(ACCC_u16DynEvap,  i16EvapError, \
			ACCC_nKiTable_Len, ACCC_nKiTable_Len, \
			ACCC_au16KiDynEvap_X, ACCC_au16KiEvapErr_Y, \
			&ACCC_au16Ki_Z3[0][0]);
		
		if (u16Ki > CHAR_MAX)
		{
			ACCC_tstCoolingCapacityPID.Ki = CHAR_MAX;
		}
		else
		{
			ACCC_tstCoolingCapacityPID.Ki = (uint8)u16Ki; 
		}

		u16Kp = Alg_u16_3DLookup_16_16_16_Limit(u16InletTemp,  i16EvapError, \
			ACCC_nKpTable_Len, ACCC_nKpTable_Len,  \
			ACCC_au16KpInletTemp_X, ACCC_au16KpEvapErr_Y, \
			&ACCC_au16Kp_Z3[0][0]);
		
		if (u16Kp > CHAR_MAX)
		{
			ACCC_tstCoolingCapacityPID.Kp = CHAR_MAX;
		}
		else
		{
			ACCC_tstCoolingCapacityPID.Kp = (uint8)u16Kp; 
		}

		ACCC_tstCoolingCapacityPID.FeedForward = Alg_u16_3DLookup_16_16_16_Limit(u16InletTemp,  ACCC_u16EvapTargetTemp, \
			ACCC_nKfTable_Len, ACCC_nKfTable_Len,  \
			ACCC_au16KfInletTemp_X, ACCC_au16KfTargetEvap_Y, \
			&ACCC_au16Kf_Z3[0][0]);

	}
	else 
	{	/* Select the last curve for searching the value.*/
		u16Ki = Alg_u16_3DLookup_16_16_16_Limit(ACCC_u16DynEvap,  i16EvapError, \
			ACCC_nKiTable_Len, ACCC_nKiTable_Len, \
			ACCC_au16KiDynEvap_X, ACCC_au16KiEvapErr_Y, \
			&ACCC_au16Ki_Z3[0][0]);
		
		if (u16Ki > CHAR_MAX)
		{
			ACCC_tstCoolingCapacityPID.Ki = CHAR_MAX;
		}
		else
		{
			ACCC_tstCoolingCapacityPID.Ki = (uint8)u16Ki; 
		}

		u16Kp = Alg_u16_3DLookup_16_16_16_Limit(u16InletTemp,  i16EvapError, \
			ACCC_nKpTable_Len, ACCC_nKpTable_Len,  \
			ACCC_au16KpInletTemp_X, ACCC_au16KpEvapErr_Y, \
			&ACCC_au16Kp_Z3[0][0]);
		
		if (u16Kp > CHAR_MAX)
		{
			ACCC_tstCoolingCapacityPID.Kp = CHAR_MAX;
		}
		else
		{
			ACCC_tstCoolingCapacityPID.Kp = (uint8)u16Kp; 
		}

		ACCC_tstCoolingCapacityPID.FeedForward = Alg_u16_3DLookup_16_16_16_Limit(u16InletTemp,  ACCC_u16EvapTargetTemp, \
			ACCC_nKfTable_Len, ACCC_nKfTable_Len,  \
			ACCC_au16KfInletTemp_X, ACCC_au16KfTargetEvap_Y, \
			&ACCC_au16Kf_Z3[0][0]);

	}

	ACCC_vCcpOutputForce();
}

#if(ACCC_nHCU_LIMIT_EC_SPEED == True)
/* ===========================================================================
* Function   : void ACCC_u16HcuLimitEcPowerAndSpeed(uint16 EvapTemp)
* Description: Calculate the E-Compressor speed limit value
* Takes      : Nothing
* Returns    : Nothing
*/
static uint16 ACCC_u16HcuLimitEcPowerAndSpeed(uint16 u16TargePhysics)
{
	uint16 *pu16_1=NULL;	
	uint16 *pu16_2=NULL;
	uint16 u16EcPowerLimitValue = 0u;
	uint16 u16ReturnValue;
	
#if (!ACCC_DEVELOPMENT_DEBUG)
	ACCC_enEcPowerLimitImport(&u16EcPowerLimitValue);
	ACCC_u16HcuLimitEcPower = u16EcPowerLimitValue; /*the max consume power of compressor.Uint: W*/ 
	u16EcPowerLimitValue = u16EcPowerLimitValue *100U; /*0.1Kw*100=100w*/ 
#endif

	pu16_1 = (uint16*)&ACCC_u16HcuLimitEcSpd_X[0];
	pu16_2 = (uint16*)&ACCC_u16HcuLimitEcSpd_Y[0];
	ACCC_u16HcuLimitEcSpd = ALG_u16CurveLookup_16_16_Limit(pu16_1, pu16_2, u16EcPowerLimitValue,\
											ACCC_nEcPowerLimitSpd_Len); 
	
	u16ReturnValue = ACCC_MIN_VALUE(u16TargePhysics,ACCC_u16HcuLimitEcSpd);

	return u16ReturnValue;
}
#endif

#endif

#if(ACCC_nAcType == ACC_u8VariableDisplacAc)	
static void ACCC_vVdcPwmPidInit(void)
{
	/***************************************************************************************
	* FUNCTION LOCAL DEFINITIONS
	*
	* In this section define
	* - all function local type definitions
	* - all function local ROM-CONSTants
	* - all function local variables (auto and STATIC)
	****************************************************************************************/
	
	/***************************************************************************************
	* FUNCTION CODE
	****************************************************************************************/
	
	ACCC_tstVdcPwmPID.Kp = ACCC_u16VdcPwmPidKp;          			//Proportional Const 
	ACCC_tstVdcPwmPID.Ki = ACCC_u16VdcPwmPidKi;          			//Integral Const
	ACCC_tstVdcPwmPID.Kd = ACCC_u16VdcPwmPidKd;          			//Derivative Const
	ACCC_tstVdcPwmPID.LastError = 0;     			//Error[-1]
	ACCC_tstVdcPwmPID.PrevError = 0;     			//Error[-2] 
	ACCC_tstVdcPwmPID.SumError = (int32)((int32)ACCC_u16VdcMinPwm * (int32)ACCC_u16VdcPwmPidKiBaseConst);			//Sums of Errors
	ACCC_tstVdcPwmPID.UpperDiffLimit = ACCC_i16VdcCurrDiffMax;
	ACCC_tstVdcPwmPID.LowerDiffLimit = ACCC_i16VdcCurrDiffMin;
	ACCC_tstVdcPwmPID.UpperLimit = ACCC_u16VdcMaxPwm;
	ACCC_tstVdcPwmPID.LowerLimit = ACCC_u16VdcMinPwm;
	ACCC_tstVdcPwmPID.OutputLimitUsed = True;
	ACCC_tstVdcPwmPID.UpperSumErrorLimit = (int32)((int32)ACCC_u16VdcMaxPwm * (int32)ACCC_u16VdcPwmPidKiBaseConst);
	ACCC_tstVdcPwmPID.LowerSumErrorLimit = -(int32)((int32)ACCC_u16VdcMaxPwm * (int32)ACCC_u16VdcPwmPidKiBaseConst);
	ACCC_u16PwmPIDTimer = ACCC_u16VdcPwmPidCalcTime;
}

static void ACCC_vCurrToPwm(void)
{
	int32 i32CurrentDiff=0;
	int16 i16CurrentDiff=0;

	if(ACCC_u16TargePhysics > 0)
	{
		if(ACCC_u16PwmPIDTimer >= ACCC_u16VdcPwmPidCalcTime)
		{
			ACCC_u16PwmPIDTimer = 0;
			
			i32CurrentDiff = ((int32)ACCC_u16TargePhysics - (int32)ACCC_u16GetVdcActualCurr); 
			i16CurrentDiff = ACCC_i16Int32ToInt16(i32CurrentDiff);/*Limit overflow*/

			if(abs(i16CurrentDiff) < 5)//unit: mA//change for increase AC's current accuracy
			{
				i16CurrentDiff = 0;
			} 		

			/* Event though Ac having error status, we should still calculate PID. */
			ACCC_u16VdcPwmOutput = ACCC_u16PidCalculate(i16CurrentDiff, &ACCC_tstVdcPwmPID);

			ACCC_VALUE_LIMIT(ACCC_u16VdcPwmOutput,ACCC_u16VdcMaxPwm ,ACCC_u16VdcMinPwm );	
		}
		else
		{
			ACCC_u16PwmPIDTimer++;
		}
	}
	else
	{
		ACCC_tstVdcPwmPID.SumError = 0;
		ACCC_u16VdcPwmOutput = 0;
		ACCC_u16PwmPIDTimer = 0;
	}
}

#if(ACCC_nUSE_SHORT_GND_PROHIBITION == True)
/* ===========================================================================
* Function   : void ACCC_vBlwSpeedCondition(void)
* Description: Blower voltage limit condition of A/C request
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vShortToGndCondition(void)
{
	if(ACCC_u16VdcPwmOutput > 0)
	{
		if(ACCC_u16GetShortToGndDetectPin == 0)//对地短路
		{
			if(ACCC_u16VdcShortToGndConfirmTimer < ACCC_u16VdcShortToGndConfirmTime)
			{
				ACCC_u16VdcShortToGndConfirmTimer++;
			}
			else//连续地对地对地短路
			{
				ACCC_u16VdcShortToGndRestoreTimer = 0;
				
				if(ACCC_boExitShortToGndFlap == True)
				{
					ACCC_boExitShortToGndFlap = False;
					
					if(ACCC_u16VdcShortToGndRepeatCnt < ACCC_u16VdcShortToGndRepeat)
					{
						ACCC_u16VdcShortToGndRepeatCnt++;
					}
				}
				Set16BitValue(ACCC_AC_OFF_CODE, Off_nShortToGnd);			
			}
		}
		else
		{			
			ACCC_boExitShortToGndFlap = True;
			
			Clear16BitValue(ACCC_AC_OFF_CODE, Off_nShortToGnd);			
		}
	}
	else
	{
		ACCC_u16VdcShortToGndConfirmTimer= 0;

		if(ACCC_u16VdcShortToGndRestoreTimer<ACCC_u16VdcShortToGndRestoreTime)
		{
			ACCC_u16VdcShortToGndRestoreTimer++;
		}
		else
		{
			Clear16BitValue(ACCC_AC_OFF_CODE, Off_nShortToGnd);			
			ACCC_boExitShortToGndFlap = True;
		}	
	}

	if(ACCC_u16VdcShortToGndRepeatCnt == ACCC_u16VdcShortToGndRepeat)
	{
		Set16BitValue(ACCC_AC_OFF_CODE, Off_nShortToGnd);			
	}
}
#endif

#if(ACCC_nWITH_TORQUE_OUTPUT == True)
static void ACCC_vCalculateTorque(void)
{
	/***************************************************************************************
	* FUNCTION LOCAL DEFINITIONS
	*
	* In this section define
	* - all function local type definitions
	* - all function local ROM-CONSTants
	* - all function local variables (auto and STATIC)
	****************************************************************************************/
	uint16 u16PressureValue;
	uint16 u16EngineSpeed;
	
	/***************************************************************************************
	* FUNCTION CODE
	****************************************************************************************/
	/* Is having error status of AC? */
	if(ACCC_AC_OFF_CODE != ACCC_nNo_Error)
	{
		ACCC_u8TorqueOutput = 0;
	}
	else
	{
		ACCC_enPressureValueImport(&u16PressureValue);
		ACCC_enEngineSpeedImport(&u16EngineSpeed);
		ACCC_u8TorqueOutput = Alg_u16_3DLookup_16_16_16_Limit(u16PressureValue,u16EngineSpeed,
			ACCC_nTorquePressure_XLen,ACCC_nTorqueEngineSpd_YLen,ACCC_au16TorquePressure_X,
			ACCC_au16TorqueEngineSpd_Y,ACCC_au16Torque_Z,);
	}
}

#endif

#endif 
#if(ACCC_nAcType == ACC_u8ElectricAc) 	


/* ===========================================================================
* Function   : void ACCC_vSpeedToPowerReq
* Description: E-Compressor comsumed power calculation 
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vSpeedToOutput(void)
{
	
	uint16 *pu16_1=NULL;	
	uint16 *pu16_2=NULL;

	if(ACCC_u16TargePhysics > 0)
	{
		/*Used the PID output target to calculate the compressor consume request*/ 
		pu16_1 = (uint16*)&ACCC_u16EcSpeedToOutput_X[0];
		pu16_2 = (uint16*)&ACCC_u16EcSpeedToOutput_X[0];
		ACCC_u16EcSpeedToOutput = ALG_u16CurveLookup_16_16_Limit(pu16_1, pu16_2, ACCC_u16TargePhysics,\
												ACCC_nEcPowerReq_Len); 
		#if(ACCC_nOUTPUT_SPEED_TO_POWER)
		ACCC_u16EcSpeedToOutput += ACCC_u16PowerReqOffset;

		if (ACCC_u16EcSpeedToOutput > ACCC_u16EcSpeedToOutput_X[ACCC_nEcPowerReq_Len-1])
		{
			ACCC_u16EcSpeedToOutput = ACCC_u16EcSpeedToOutput_X[ACCC_nEcPowerReq_Len-1];
		}
		#endif	
	}
	else
	{
		ACCC_u16EcSpeedToOutput = 0;
	}
	#if(ACCC_nOUTPUT_SPEED_TO_POWER)
	ACCC_u8EcTargetPowerForCAN = ACCC_u16EcSpeedToOutput/ACCC_u16EcPowerToCANFactor;
	#endif	
	ACCC_u8EcTargetSpeedForCAN = ACCC_u16TargePhysics/ACCC_u16EcSpeedToCANFactor;
}

#if(ACCC_nHCU_LIMIT_EC_SPEED == True)

static void ACCC_vPowerLimitCondition(void)
{
	uint16 u16EcPowerLimitValue = 0u;
	
#if (!ACCC_DEVELOPMENT_DEBUG)
	ACCC_enEcPowerLimitImport(&u16EcPowerLimitValue);
	u16EcPowerLimitValue = u16EcPowerLimitValue *100U; /*0.1Kw*100=100w*/ 
#endif

	if(u16EcPowerLimitValue < ACCC_u16PowerLimitDisable)
	{
		ACCC_SetOffCode(ACCC_AC_OFF_CODE, Off_nPowerLimit);			
	}
	else
	{
		ACCC_ClearOffCode(ACCC_AC_OFF_CODE, Off_nPowerLimit);			
	}
}
#endif

#if(ACCC_nWITH_AC_DIAG_SIGNAL == True)
static void ACCC_vDiagnosticSignalCondition(void)
{

}
#endif

#if(ACCC_nWITH_BATT_MANAGE == True)

/* ===========================================================================*/
/* Function   : void ACCC_vBattCoolPIDInit(void)
* Description: PID control parameter initialization of Chiller control
* Takes      : Nothing
* Returns    : Nothing
*/
/* ===========================================================================*/
static void ACCC_vBattCoolPIDInit(void)
{
	ACCC_tstCoolingCapacityPidForBatt.Kp = 0U;          			//Proportional Const 
	ACCC_tstCoolingCapacityPidForBatt.Ki = 1000U;          			//Integral Const
	ACCC_tstCoolingCapacityPidForBatt.Kd = 0U;          			//Derivative Const
	ACCC_tstCoolingCapacityPidForBatt.LastError = 0;     			//Error[-1]
	ACCC_tstCoolingCapacityPidForBatt.PrevError = 0;     			//Error[-2] 
	ACCC_tstCoolingCapacityPidForBatt.SumError = (int32)((int32)ACCC_u16BattMinCoolingCapacity * ACCC_u16KiBaseConst);			//Sums of Errors
	ACCC_tstCoolingCapacityPidForBatt.UpperDiffLimit = ACCC_i16EvapTempDiffMax;
	ACCC_tstCoolingCapacityPidForBatt.LowerDiffLimit = ACCC_i16EvapTempDiffMin;
	ACCC_tstCoolingCapacityPidForBatt.UpperLimit = ACCC_u16BattMaxCoolingCapacity;
	ACCC_tstCoolingCapacityPidForBatt.LowerLimit = ACCC_u16BattMinCoolingCapacity;
	ACCC_tstCoolingCapacityPidForBatt.OutputLimitUsed = True;
	ACCC_tstCoolingCapacityPidForBatt.UpperSumErrorLimit = (int32)ACCC_u16BattMaxCoolingCapacity * ACCC_u16KiBaseConst;
	ACCC_tstCoolingCapacityPidForBatt.LowerSumErrorLimit = -(int32)ACCC_u16BattMaxCoolingCapacity * ACCC_u16KiBaseConst;
}

/* ===========================================================================*/
/* Function   : void ACCC_vCalPidParameter2(void)
* Description: PID control KD parameters calculating for A/C speed
* Takes      : u16Error, u16OatValue
* Returns    : Nothing
*/
/* ===========================================================================*/
static uint16 ACCC_vCalBattCoolKiParameter(void)
{
	uint16 *pu16_1=NULL;
	uint16 *pu16_2=NULL;
	uint16 u16OatValue = 0U;
	uint16 u16Return = 0U;
	
	ACCC_enOatValueImport(&u16OatValue); 
	
	/*OAT shall be have a hysteresis value */ 
	pu16_1 = &ACCC_u16PidParaOatHys;
	ALG_vHysteresis_16(pu16_1,u16OatValue, ACCC_u16InletTempHysForPidPara);

	/*Ki */ 
	pu16_1 = (uint16*)&ACCC_au16BattCoolKi_X[0];
	pu16_2 = (uint16*)&ACCC_au16BattCoolKi_Y[0];				
	u16Return = ALG_u16CurveLookup_16_16_Limit(pu16_1, pu16_2,\
		                    ACCC_u16PidParaOatHys, ACCC_nBattCoolKi_Len);
	return u16Return;
}

static void ACCC_vCalcCoolingCapacityOnlyBattery(void)
{
	uint16 *pu16_1=NULL;	
	uint16 *pu16_2=NULL;
	uint16 u16BtmThreeWayValveRatio=0U;
	uint16 u16BattCoolantInTarget=0U;
	uint16 u16BattCoolantInTemp=0U;
	uint16 u16OatValue=0U;
	uint16 u16EcBasedSpd=0U;
	
	int16 i16PidOutput=0;
	int16 i16TempDiff=0;
	int32 i32Tempdiff = 0;
	int32 i32PidOutput=0;

	ACCC_enBattCoolantInTargetTempImport(&u16BattCoolantInTarget);
	ACCC_enBattCoolantInTempImport(&u16BattCoolantInTemp);
	ACCC_enOatValueImport(&u16OatValue);
	ACCC_enBattThreeWayValveRatioImport(&u16BtmThreeWayValveRatio);

	/****Only battery cooling. Calculate the EC speed based on PID2****/ 	
	if(ACCC_enEcCoolingMode != ACCC_nBattCoolingMode)
	{/*Re-Init PID output*/
		ACCC_enEcCoolingMode = ACCC_nBattCoolingMode; /*Only battery cooling*/
		if(ACCC_u16TargeCoolingCapacity >=ACCC_u16BattMaxCoolingCapacity)
		{
			ACCC_u16TargeCoolingCapacity = ACCC_u16BattMaxCoolingCapacity;
		}
		ACCC_tstCoolingCapacityPidForBatt.SumError = (int32)((int32)ACCC_u16TargePhysics * ACCC_u16KiBaseConst);		
	}

	if(u16BtmThreeWayValveRatio <= ACCC_u16ThreeWayValveRatioLvl1)
	{
		if((ACCC_u16BattCoolKiTimer++) >= ACCC_u16EcSpeedForBattKiTime)
		{
			ACCC_u16BattCoolKiTimer=0U;
			ACCC_tstCoolingCapacityPidForBatt.Ki = ACCC_vCalBattCoolKiParameter();
			/*i16TempDiff = Feedback - Target*/
			i32Tempdiff = ((int32)u16BattCoolantInTemp - (int32)u16BattCoolantInTarget); 
			i16TempDiff = ACCC_i16Int32ToInt16(i32Tempdiff);/*Limit overflow*/
		        if(ABS(i16TempDiff) <= ACCC_u16BattTempDiffTol)
		        {
		            i16TempDiff = 0;
		        }
			
			/*Calculate based speed by OAT*/
			pu16_1 = (uint16*)&ACCC_au16EcBattBasedSpdByOat_X[0];
			pu16_2 = (uint16*)&ACCC_au16EcBattBasedSpdByOat_Y[0];
			u16EcBasedSpd = ALG_u16CurveLookup_16_16_Limit(pu16_1, pu16_2,\
									u16OatValue,ACCC_nEcBattBasedSpdByOat_Len); 
			
			/****Added I part*/
			/****limit input: error*/
			if(i16TempDiff > ACCC_tstCoolingCapacityPidForBatt.UpperDiffLimit)
			{
				i16TempDiff = ACCC_tstCoolingCapacityPidForBatt.UpperDiffLimit;
	              }
			
			if(i16TempDiff < ACCC_tstCoolingCapacityPidForBatt.LowerDiffLimit)
			{
				i16TempDiff = ACCC_tstCoolingCapacityPidForBatt.LowerDiffLimit;
	              }
            			
			/****Accumulating intergrator*/
			ACCC_tstCoolingCapacityPidForBatt.SumError += (int32)(i16TempDiff) * (int32)(ACCC_tstCoolingCapacityPidForBatt.Ki); 
			/*limit sum error*/
			if(ACCC_tstCoolingCapacityPidForBatt.SumError > ACCC_tstCoolingCapacityPidForBatt.UpperSumErrorLimit) 
			{
				ACCC_tstCoolingCapacityPidForBatt.SumError = ACCC_tstCoolingCapacityPidForBatt.UpperSumErrorLimit;
			}
			else if(ACCC_tstCoolingCapacityPidForBatt.SumError < ACCC_tstCoolingCapacityPidForBatt.LowerSumErrorLimit) 
			{
				ACCC_tstCoolingCapacityPidForBatt.SumError = ACCC_tstCoolingCapacityPidForBatt.LowerSumErrorLimit;
			}
			else
			{
			
			}		
			/*Based speed + I part*/
			i32PidOutput = (int32)u16EcBasedSpd + ((int32)(ACCC_tstCoolingCapacityPidForBatt.SumError)/ACCC_u16KiBaseConst);
			/*output and limit*/		
			if(ACCC_tstCoolingCapacityPidForBatt.OutputLimitUsed == True)
			{
				if(i32PidOutput > ACCC_tstCoolingCapacityPidForBatt.UpperLimit)
				{
					i32PidOutput = ACCC_tstCoolingCapacityPidForBatt.UpperLimit;
					if(i16TempDiff > 0)
					{
						ACCC_tstCoolingCapacityPidForBatt.SumError -= (int32)(i16TempDiff) * (int32)(ACCC_tstCoolingCapacityPidForBatt.Ki);
					}
				}
				if(i32PidOutput < ACCC_tstCoolingCapacityPidForBatt.LowerLimit)
				{
					i32PidOutput = ACCC_tstCoolingCapacityPidForBatt.LowerLimit; 
					if(i16TempDiff < 0)
					{
						ACCC_tstCoolingCapacityPidForBatt.SumError -= (int32)(i16TempDiff) * (int32)(ACCC_tstCoolingCapacityPidForBatt.Ki);
					}
				}
			}
			
			i16PidOutput = (int16)i32PidOutput;
			if (i16PidOutput < (int16)CHAR_MIN)
			{
				ACCC_u16TargeCoolingCapacity = 0U;
			}
			else 
			{
				ACCC_u16TargeCoolingCapacity = (uint16)i16PidOutput;
			}
		}
	}
	else if(u16BtmThreeWayValveRatio >= ACCC_u16ThreeWayValveRatioLvl2)
	{
		if((ACCC_u16BattCoolKiTimer++) >= ACCC_u16EcSpeedForBattKiTime)
		{
			ACCC_u16BattCoolKiTimer=0U;
			if(u16BattCoolantInTemp < u16BattCoolantInTarget + 100U)
			{
				ACCC_u16TargeCoolingCapacity -= ACCC_u16SpdDecRateInLvl2;
			}
			if(ACCC_u16TargeCoolingCapacity < ACCC_u16BattMinCoolingCapacity)
			{
				ACCC_u16TargeCoolingCapacity = ACCC_u16BattMinCoolingCapacity;
			}
		}
	}
	else
	{
	    /*Keep current speed*/
	}
	ACCC_VALUE_LIMIT(ACCC_u16TargeCoolingCapacity, ACCC_u16BattMaxCoolingCapacity, ACCC_u16BattMinCoolingCapacity);
}

/* ===========================================================================
* Function   : void ACCC_vChillerValveCtrl(void)
* Description: 
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vChillerValveCtrl(void)
{
	uint16 u16EcActualSpd;
	 ACCC_enEcActualSpdImport(&u16EcActualSpd);
	 
	if(ACCC_u8BattCoolingReq == ACCC_nAcReqOff)
	{
		ACCC_u8ChillerValveReq = Off;
		
		if(ACCC_u8AcValveReq == Off)
		{
			if(u16EcActualSpd == 0U)
			{
				if(ACCC_u8ChillerVOffDelayTimer >= ACCC_u16TXVOffDelayTimeConfig)
				{
					ACCC_u8ChillerVOffDelayTimer = 0U;
					ACCC_u8ChillerValveReq = Off;
					/****HW Output****/ 
					ACCC_ChillerValveOutput(Pin_Off);
				}
				else
				{
					ACCC_u8ChillerVOffDelayTimer++;
				}
			}
		}
		else
		{
			ACCC_u8ChillerValveReq = Off;
			/****HW Output****/ 
			ACCC_ChillerValveOutput(Pin_Off);
			ACCC_u8ChillerVOffDelayTimer = 0U;
		}
	}	
	else
	{
		ACCC_u8ChillerValveReq = On;
		
		ACCC_u8ChillerVOffDelayTimer = 0U;
		
		ACCC_ChillerValveOutput(Pin_On);
	}
}


/* ===========================================================================
* Function   : void ACCC_vBattRequest(void)
* Description: Driver battery cooling control 
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vBattRequest(void)
{
	uint16 u16BattCoolantInTarget;
	uint16 u16BattCoolingMode; 
	uint16 u16BattCoolantInTemp;
	uint16 u16BtmThermalMagReq;

	ACCC_enBattCoolantInTargetTempImport(&u16BattCoolantInTarget);
	ACCC_enBattCoolingModeImport(&u16BattCoolingMode);
	ACCC_enBattCoolantInTempImport(&u16BattCoolantInTemp);
	ACCC_enBattThermalMagReqImport(&u16BtmThermalMagReq);
	
	if(u16BattCoolantInTarget < ACCC_u16CoolantInOffAcOffset)
	{/*Limit overflow*/
		u16BattCoolantInTarget = ACCC_u16CoolantInOffAcOffset;
	}

	if(u16BtmThermalMagReq == ACCC_BtmThermalCoolingReq)
	{/****BTM Cooling request***/
		if(u16BattCoolingMode == ACCC_nAcForceCoolingMode)
		{	
			if(u16BattCoolantInTemp <= u16BattCoolantInTarget - ACCC_u16CoolantInOffAcOffset)
			{/*Coolant in water temperature < Target, shall be shut down A/C */ 
				ACCC_u8BattCoolingReq = ACCC_nAcReqOff;
			}
			else if(u16BattCoolantInTemp >= u16BattCoolantInTarget - ACCC_u16CoolantInOnAcOffset)
			{
				ACCC_u8BattCoolingReq = ACCC_nAcReqOn;
			}
		}
		else
		{/*natural wind cooling mode. no need to force AC cooling*/ 		
			ACCC_u8BattCoolingReq = ACCC_nAcReqOff; 
		}
	}
	else
	{
		ACCC_u8BattCoolingReq = ACCC_nAcReqOff; 
	}
}
#endif

#if(ACCC_nWITH_COOLING_VALVE == True)
/* ===========================================================================
* Function   : void ACCC_vCoolingValveCtrl(void)
* Description: the Evap. pipeline valve control
* Takes      : Nothing
* Returns    : Nothing
*/
static void ACCC_vCoolingValveCtrl(void)
{
	uint16 u16EcActualSpd;
	ACCC_enEcActualSpdImport(&u16EcActualSpd);

	if(ACCC_u8AcOperation == ACCC_nAcReqOn)
	{
		ACCC_u8AcValveReq = On;
		/****HW Output****/ 
		ACCC_AcValvePinOutput(Pin_On);
		ACCC_u8TXVOffDelayTimer = 0;
	}
	else
	{ 
#if(ACCC_nWITH_BATT_MANAGE == True)
		if(ACCC_u8ChillerValveReq == Off)
		{
#endif
			if(u16EcActualSpd == 0U)
			{
				if(ACCC_u8TXVOffDelayTimer >= ACCC_u16TXVOffDelayTimeConfig)
				{
					ACCC_u8TXVOffDelayTimer = 0;
					ACCC_u8AcValveReq = Off;
					/****HW Output****/ 
					ACCC_AcValvePinOutput(Pin_Off);
				}
				else
				{
					ACCC_u8TXVOffDelayTimer++;
				}
			}
			else
			{
				ACCC_u8AcValveReq = On;
				/****HW Output****/ 
				ACCC_AcValvePinOutput(Pin_On);
				ACCC_u8TXVOffDelayTimer = 0;
			}				
#if(ACCC_nWITH_BATT_MANAGE == True)
		}
		else
		{/*Only battery coooling, shut down evap cooling valve*/
			ACCC_u8AcValveReq = Off;
			/****HW Output****/ 
			ACCC_AcValvePinOutput(Pin_Off);	
			ACCC_u8TXVOffDelayTimer = 0;
		}
#endif
	}
}
#endif
#endif

/*****************************************************************************
 Function      : ACCC_u8GetValue                                              *
 Description   : The extern model get the uint8 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*****************************************************************************/
uint8 ACCC_u8GetValue( ACCC_tenu8VarNumber enIndex )
{
	if ( enIndex < ACCC_nu8Max )
	{
		return ACCC_au8Array[enIndex];
	}
	else
	{
		return ACCC_au8Array[ACCC_nu8Max-1];
	}
}

/*****************************************************************************
 Function      : ACCC_u16GetValue                                              *
 Description   : The extern model get the uint16 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*****************************************************************************/
uint16 ACCC_u16GetValue( ACCC_tenu16VarNumber enIndex )
{
	if ( enIndex < ACCC_nu16Max )
	{
		return ACCC_au16Array[enIndex];
	}
	else
	{
		return ACCC_au16Array[ACCC_nu16Max-1];
	}
}

/*****************************************************************************
 Function      : ACCC_vObdMain                                              *
 Description   : For PTS*
     model                                                       *
 Return Value  : Nothing*
*****************************************************************************/
void ACCC_vObdMain(void)
{
#ifdef CCP_CTRL
	uint16 u16CcpValue;
	u16CcpValue=ACCC_u8GetCcpValue_CCP_nu16ObdAcCtrl;

	 if(CCP_ObdNotData!=u16CcpValue)
	 {
	  	/* Control the AC Relay Output by OBD */
		ACCC_ReqOutput(CCP_u16CtrlValue(u16CcpValue)&1);
	 }
#endif
}

static uint16 Alg_u16_3DLookup_16_16_16_Limit( uint16 InputX, uint16 InputY,uint8 SizeX,uint8 SizeY,const uint16* TableX, const uint16* TableY,const uint16* TableZ)
{
	uint16 ReturnValue;
	uint16 TempTable[2];
	uint16 *pu16_1=NULL;	
	uint16 *pu16_2=NULL;

	if(InputY <= TableY[0])
	{	
		pu16_1 = (uint16*)TableX;
		pu16_2 = (uint16*)TableZ;
		
		/* Select the first curve for searching the value.*/
		ReturnValue = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,InputX, SizeX);
		
		return(ReturnValue);
	}

	else
	{
	  	uint8 u8Index;
		for(u8Index=1;u8Index<SizeY;u8Index++)
		{
			if (InputY < TableY[u8Index])
			{	
				pu16_1 = (uint16*)TableX;
				pu16_2 = (uint16*)(TableZ + (u8Index-1)*SizeX);
				/* Select the first & second curves for generating the value, then search it for the value.*/
				TempTable[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,InputX,	SizeX);

				pu16_1 = (uint16*)TableX;
				pu16_2 = (uint16*)(TableZ + u8Index*SizeX);
				TempTable[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,InputX,	SizeX);

				pu16_1 = (uint16*)&TableY[u8Index-1];
				pu16_2 = (uint16*)&TempTable[0];
				ReturnValue = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,InputY, 2);	
				
				return(ReturnValue);		
			}
		}
		
		pu16_1 = (uint16*)TableX;
		pu16_2 = (uint16*)(TableZ + (SizeY - 1) * SizeX);
		/* Select the last curve for searching the value.*/
		ReturnValue = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,InputX, SizeX);
		
		return(ReturnValue);
		
	}
}

/*************************************************************************************************** 
  Function   : ATCS_u8Int16ToUint8                         
                       
  Description: This function is used to convert the signed 16-bit value into unsigned 8-bit value.
                                                                           
  Arguments  : i16Input     - is the signed 16-bit value input.
               i16ZeroPoint - is the zero point after the conversion. For example,if the 
                              i16ZeroPoint is -128, after the conversion we use 0 to represent the 
                              value -128 before the conversion.
               
  Returns    : unsigned 8-bit value output  
***************************************************************************************************/

uint8 ACCC_u8Int16ToUint8(int16 i16Input, int16 i16ZeroPoint)
{
    uint8 u8Return;
    int16 i16Return;

    if (i16Input < i16ZeroPoint)
    {
        u8Return = (uint8)CHAR_MIN;
    }
    else if (i16Input > (i16ZeroPoint+UCHAR_MAX))
    {
        u8Return = (uint8)UCHAR_MAX;
    }
    else
    {
        i16Return = i16Input - i16ZeroPoint;
        u8Return = (uint8)i16Return;
    }

    return u8Return;
}

/*************************************************************************************************** 
  Function   : ATCS_u16Int16ToUint16                         
                       
  Description: This function is used to convert the signed 16-bit value into unsigned 16-bit value.
                                                                           
  Arguments  : i16Input     - is the signed 16-bit value input.
               i16ZeroPoint - is the zero point after the conversion. For example, if the 
                              i16ZeroPoint is -128, after the conversion we use 0 to represent the 
                              value -128 before the conversion.
               
  Returns    : unsigned 16-bit value output  
***************************************************************************************************/

uint16 ACCC_u16Int16ToUint16(int16 i16Input, int16 i16ZeroPoint)
{
    uint16 u16Return;
    int16 i16Return;

    if (i16Input < i16ZeroPoint)
    {
        u16Return = 0U;
    }
    else if (i16Input > (i16ZeroPoint+(int16)USHRT_MAX))
    {
        u16Return = (uint16)USHRT_MAX;
    }
    else
    {
        i16Return = i16Input - i16ZeroPoint;
        u16Return = (uint16)i16Return;
    }

    return u16Return;
}

/*************************************************************************************************** 
  Function   : ATCS_u16Int32ToUint16                         
                       
  Description: This function is used to convert the signed 32-bit value into unsigned 16-bit value.
                                                                           
  Arguments  : i32Input     - is the signed 32-bit value input.
               i32ZeroPoint - is the zero point after the conversion. For example, if the 
                              i32ZeroPoint is -128, after the conversion we use 0 to represent the 
                              value -128 before the conversion.
               
  Returns    : unsigned 16-bit value output  
***************************************************************************************************/

uint16 ACCC_u16Int32ToUint16(int32 i32Input, int32 i32ZeroPoint)
{
    uint16 u16Return;
    int32 i32Return;

    if (i32Input < i32ZeroPoint)
    {
        u16Return = 0U;
    }
    else if (i32Input > (i32ZeroPoint+(int32)USHRT_MAX))
    {
        u16Return = (uint16)USHRT_MAX;
    }
    else
    {
        i32Return = i32Input - i32ZeroPoint;
        u16Return = (uint16)i32Return;
    }

    return u16Return;
}

/*************************************************************************************************** 
  Function   : ATCS_u16Uint32ToUint16                         
                       
  Description: This function is used to convert the unsigned 16-bit value into unsigned 16-bit 
               value.
                                                                           
  Arguments  : u32Input     - is the unsigned 32-bit value input.
               
  Returns    : unsigned 16-bit value output  
***************************************************************************************************/

uint16 ACCC_u16Uint32ToUint16(uint32 u32Input)
{
    uint16 u16Return;

    if (u32Input > USHRT_MAX)
    {
        u16Return = USHRT_MAX;
    }
    else
    {
        u16Return = (uint16)u32Input;
    }

    return u16Return;
}

/*************************************************************************************************** 
  Function   : ATCS_i8Int16ToInt8                         
                       
  Description: This function is used to convert the signed 16-bit value into signed 8-bit value.
                                                                           
  Arguments  : i16Input     - is the signed 16-bit value input.
               
  Returns    : signed 8-bit value output  
***************************************************************************************************/

int8 ACCC_i8Int16ToInt8(int16 i16Input)
{
    int8 i8Return;

    if (i16Input < SCHAR_MIN)
    {
        i8Return = SCHAR_MIN;
    }
    else if (i16Input > SCHAR_MAX)
    {
        i8Return = SCHAR_MAX;
    }
    else
    {
        i8Return = (int8)i16Input;
    }

    return i8Return;
}

/*************************************************************************************************** 
  Function   : ATCS_i16Int32ToInt16                         
                       
  Description: This function is used to convert the signed 32-bit value into signed 16-bit value.
                                                                          
  Arguments  : i32Input     - is the signed 32-bit value input.
               
  Returns    : signed 16-bit value output  
***************************************************************************************************/

int16 ACCC_i16Int32ToInt16(int32 i32Input)
{
    int16 i16Return;

    if (i32Input < SHRT_MIN)
    {
        i16Return = SHRT_MIN;
    }
    else if (i32Input > SHRT_MAX)
    {
        i16Return = SHRT_MAX;
    }
    else
    {
        i16Return = (int16)i32Input;
    }

    return i16Return;
}

/*************************************************************************************************** 
  Function   : ATCS_u8Uint32ToUint8                         
                       
  Description: This function is used to convert the unsigned 16-bit value into unsigned 8-bit value.
                                                                           
  Arguments  : u32Input     - is the unsigned 32-bit value input.
               
  Returns    : unsigned 8-bit value output  
***************************************************************************************************/

uint8 ACCC_u8Uint32ToUint8(uint32 u32Input)
{
    uint8 u8Return;

    if (u32Input > (uint32)UCHAR_MAX)
    {
        u8Return = (uint8)UCHAR_MAX;
    }
    else
    {
        u8Return = (uint8)u32Input;
    }

    return u8Return;
}

/*************************************************************************************************** 
  Function   : ATCS_u8Uint16ToUint8                         
                       
  Description: This function is used to convert the unsigned 16-bit value into unsigned 8-bit value.
                                                                           
  Arguments  : u16Input     - is the unsigned 16-bit value input.
               
  Returns    : unsigned 8-bit value output  
***************************************************************************************************/

uint8 ACCC_u8Uint16ToUint8(uint16 u16Input)
{
    uint8 u8Return;

    if (u16Input > (uint16)UCHAR_MAX)
    {
        u8Return = (uint8)UCHAR_MAX;
    }
    else
    {
        u8Return = (uint8)u16Input;
    }

    return u8Return;
}

/*****************************************************************************
* EOF: Accc.c
*****************************************************************************/
