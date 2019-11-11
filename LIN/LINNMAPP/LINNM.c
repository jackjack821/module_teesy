/**************************** .FILE_HEADER_BEGIN *****************************
 .FILE; [ LINNM1c1.c]
 .Author; [ Liu Fuguang]
 .Date; 2016/12/30
 .Update Time; 11:43:29
 .Gen File Name: SX11P_LIN_V1.0_2016-12-29.xlsx
****************************** .FILE_HEADER_END ******************************/
#define LINNM                          /* Name of the Module                */
/* HEADER-FILES (Only those that are needed in this file) */
//#include "Ccp.H" 
#include "Pow.H"
#include "stdio.H"
/* System-headerfiles */
#include "General.H"
#include "Mcu_cfg.h"
//#include "Iodefine.H"
//#include "Desc.h"
//#include "Appdesc.h"
/* Lin Driver headfiles */
#include "lin_api.H"
#include "dtl_api.H"
#include "canapp.H"
/* Own headerfiles */
#include "LINAPP.H"
#include "LINNM.H"
#include "LINNM_cfg.H"
/* internal variable...*/
typedef enum
{
	LINNM_nWakeUp_Bus = 0,
}LINNM_tenWakeUpReason;
typedef enum
{
	LINNM_nSysStandby = 0,
	LINNM_nSysStandbyToOn,
		
	LINNM_nSysOn,
	LINNM_nSysOnToStandby,
}LINNM_tenSysState;

static uint16 LINNM_au16Array[LINNM_nu16Max];
//static uint16 LINNM_u16ScheduleCurrent;
//static uint16 LINNM_u16ScheduleNext;
static uint16 LINNM_u16WakeUpReason;
static LINNM_tenSysState LINNM_enSysState;
//static uint8 LINNM_u8ReadyTxDiagSlaveFrameHeadTimer;
static uint16 LINNM_u16TransceiverSleepControlTmr;

#define LINNM_WakeUpReasonSet(Index)		(LINNM_u16WakeUpReason |= (0x0001 << Index))
#define LINNM_WakeUpReasonClr(Index)		(LINNM_u16WakeUpReason &= (~(0x0001 << Index)))
#define LINNM_WakeUpReasonGet(Index)		((LINNM_u16WakeUpReason>>Index) & 0x0001)
#define LINNM_AllWakeUpReasonClr()			(LINNM_u16WakeUpReason = 0x0000)
/*****LINNM FUNCTIONS**********************************************************************************/
static void LINNM_vStandby(void);
static void LINNM_vStandbyToOn(void);

static void LINNM_vOn(void);
static void LINNM_vOnToStandby(void);

static void LINNM_vClockConf(void);
static void LINNM_vHardwareInit(void);
static void LINNM_vTransceiverControl(uint8 u8On_Off);
/*****************************************************************************
* Function   : void LINNM_u16GetValue (void)
* Description: 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
uint16 LINNM_u16GetValue(LINNM_tenu16VarNum enIndex)
{
	if(enIndex < LINNM_nu16Max)
	{
		return (LINNM_au16Array[enIndex]);
	}
	else
	{
		return (LINNM_au16Array[LINNM_nu16Max-1]);
	}
}
/*****************************************************************************
* Function   : void LINNM_vReset (void)
* Description: Called in LINCCL Module Reset container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void LINNM_vReset(void)
{
	LINNM_enSysState = LINNM_nSysStandbyToOn;
	LINNM_WakeUpReasonSet(LINNM_nWakeUp_Bus);
	LINNM_au16Array[LINNM_nu16NmState] = LINNM_nWake;		
}
/*****************************************************************************
* Function   : void LINNM_vMain_10ms (void)
* Description: Called in LINCCL Module 10ms container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void LINNM_vMain_10ms(void)
{
	switch(LINNM_enSysState)
	{
		case LINNM_nSysStandby:
			LINNM_vStandby();
			break;
		case LINNM_nSysStandbyToOn:
			LINNM_vStandbyToOn();
			break;
		case LINNM_nSysOn:
			LINNM_vOn();
			break;
		case LINNM_nSysOnToStandby:
			LINNM_vOnToStandby();
			break;
		default:
			LINNM_enSysState = LINNM_nSysStandby;
			break;
	}
}
/*****************************************************************************
* Function   : void LINNM_vMain_1ms (void)
* Description: Called in LINCCL Module 1ms container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void LINNM_vMain_1ms(void)
{
    LinFastTimerTask();
	/*****************************************************
	LinFastTimerTask()
	1. must be called with cycle specified in generation tool
	2. If possible the LinFastTimerTask should be called with 1ms, 
	but at least with the cycle time of the time base given in the LDF.
	******************************************************/
}
/*****************************************************************************
* Function   : void LINNM_vMain_20ms (void)
* Description: Called in LINCCL Module 20ms container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void LINNM_vMain_20ms(void)
{
	/***************************************************
	LinSlowTimerTask() : 
	1.must be called with cycle specified in generation tool;
	2.If possible the LinSlowTimerTask should be called with about 20ms,
	   a cycle time of over 100 ms should not be exceeded.
	****************************************************/	
	LinSlowTimerTask();
}
/*****************************************************************************
* Function   : void LINNM_vStandby (void)
* Description: 
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void LINNM_vStandby(void)
{
	if(LINNM_WakeUpReasonGet(LINNM_nWakeUp_Bus) == True)
	{
		LINNM_WakeUpReasonClr(LINNM_nWakeUp_Bus);
		//LINNM_enSysState = LINNM_nSysStandbyToOn;
	}

}
/*****************************************************************************
* Function   : void LINNM_vStandbyToOn (void)
* Description: 
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void LINNM_vStandbyToOn(void)
{
	__DI();
	LINNM_vHardwareInit();
	LinInitPowerOn();
	__EI();
	if(LinStart(kLinWakeUpExternal) == 0)
	{
		LINNM_enSysState = LINNM_nSysOn;
	}
}
/*****************************************************************************
* Function   : void LINNM_vOn (void)
* Description: 
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void LINNM_vOn(void)
{
    #if 0
	if(LINAPP_u8LINCommunicationCondictionFlag()==True)
	{
		LINNM_enSysState = LINNM_nSysOnToStandby;
		LINNM_WakeUpReasonClr(LINNM_nWakeUp_Bus);	
	}
	LINNM_u16TransceiverSleepControlTmr=0;
#endif
	/*Do nothing*/
}
/*****************************************************************************
* Function   : void LINNM_vOnToStandby (void)
* Description: 
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void LINNM_vOnToStandby(void)
{
	LINNM_vTransceiverControl(Off);
	LINNM_au16Array[LINNM_nu16NmState] = LINNM_nSleep;
	LINNM_enSysState = LINNM_nSysStandby;
	LINNM_u16TransceiverSleepControlTmr=0;
}
/*****************************************************************************
* Function   : void LINNM_vClockConf (void)
* Description: configuration of LIN Clock
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void LINNM_vClockConf(void)
{
      	PROTCMD1=0xa5;
      	CKSC_ILINS_CTL=0x02;
      	CKSC_ILINS_CTL=~0x02;
      	CKSC_ILINS_CTL=0x02;
	while (PROTS1 ==0x02);
}
/*****************************************************************************
* Function   : void LINNM_vHardwareInit (void)
* Description: Lin hardware configuration
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void LINNM_vHardwareInit(void)
{
	LINNM_vTransceiverControl(On);
	/*RLIN30RX is P0_3, RLIN30TX is P0_2*/
	LINNM_vClockConf();/*TAN FUMIN set clock source to main_osc, not use CPU clk!!*/
	/*Disable Externel Interrupt *****   TBD    *****/
	MKP10 = 1u;
	FCLA0CTL2_INTPH = 0x00;
	/* LIN0 Pin Configuration */
	LIN0_SET_PFC;
	LIN0_SET_PFCE;
	LIN0_SET_PFCAE;
	LIN0_SET_PMC;
	LIN0_SET_PM;
	//#endif
	LIN0_SET_RX_PU;
	/* Set LIN Interrupt Priorities */
	LIN0_SET_INT_PRIO;
}
/*****************************************************************************
* Function   : void LINNM_vWakeFromSTOPmodeSetting(void)
* Description: As the RH850 MCU Specification,  RLIN Interrupt cannot wake up the MCU when it is STOP.
			So if the project equit the CTS function, the power of MCU will not be cutoff, and MCU will
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void LINNM_vTransceiverControl(uint8 u8On_Off)
{
	//LINNM_u16Transceiver_EN(u8On_Off);
	//LINNM_u16Transceiver_WAKE(Off);
}
/**VECTOR CALLBACK FUNCTIONS**************************************************************************/
void ApplLinBusSleep(void)
{
	LINNM_enSysState = LINNM_nSysOnToStandby;
	LINNM_WakeUpReasonClr(LINNM_nWakeUp_Bus);	
}
void ApplLinProtocolError(vuint8 error, tLinFrameHandleType vMsgHandle )
{
	if((error ==kLinPhysicalBusError)||(error == kLinErrInHeader))
	{
		__DI();
		LINNM_vHardwareInit();
		LinInitPowerOn();
		__EI();
	}
}
void ApplLinFatalError(vuint8 error)
{
}
/*****************************************************************************
			e.g: UART when the bus is in sleep mode.
			Function is called by the driver in interrupt context
* Call	     : call back function from VECTOR
* Returns   : Nothing
******************************************************************************/

extern void LINCCL_vClrEnableSleepFlg(void);
void ApplLinWakeUp(void)
{
	/*re- open at 170615*/
	//if(LINNM_au16Array[LINNM_nu16NmState] == LINNM_nSleep)
		LINNM_enSysState = LINNM_nSysStandbyToOn;
		LINNM_WakeUpReasonSet(LINNM_nWakeUp_Bus);
		LINNM_au16Array[LINNM_nu16NmState] = LINNM_nWake;
		LINCCL_vClrEnableSleepFlg();
}
void ApplDtlFatalError(vuint8 error)
{
}

vuint8 ApplLinScGetSerialNumber(vuint8* pbSerialNumber)
{
}
vuint8 ApplLinScGetUserDefinedId(vuint8 IdNumber, vuint8* pbIdValue)
{
	if (IdNumber == 0x20)
	{
		pbIdValue[0] = 0x03;/* PartNumLSB */
		pbIdValue[1] = 0x93;/* PartNum */
		pbIdValue[2] = 0x8E;/* PartNum */
		pbIdValue[3] = 0x9D;/* PartNumMSB */
		pbIdValue[4] = 0x40;/* EA  //Version A--0,B--1,C--2,D--3......*/
	}
	else
	{
	}
	return kLinSc_SendPositiveResponse;
}

vuint8 ApplLinScDataDump(const vuint8* const pbRequestData, vuint8* pbResponseData)
{
}
vuint8 ApplLinConfirmDiagFrameResp(void)
{
}
#if 0
vuint8 ApplLinDiagSlotIndication(vuint8 bMsgDirection)
{
}

vuint8 ApplDtlTxConfirmation (vuint8 bResult)
{
}
vuint8 ApplDtlRxMsgIndication(vuint8 bResult)
{
}
vuint8 ApplDtlRxStartIndication (vuint8 bAddressInfo, vuint16 bLength, vuint8 ** ppbRxDataPtr)
{
}
#endif
/*****************************************************************************
* EOF:
******************************************************************************/
