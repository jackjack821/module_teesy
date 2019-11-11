/*******************************************************************************
| Module Name: Task config
| File Name: os_framecfg.h
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
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver        	Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 
|2015.10.17  V1.10      Li, Ning		   :add cfg of debug function
********************************************************************************/
#ifndef FRAME_CFG_H
#define FRAME_CFG_H

#ifndef Frame_c
  #define frame_ext extern
#else
  #define frame_ext
#endif

/* Foreign headerfiles */

#include "General.h"
#include "ign.h"
#include "FRAME_Pte.h"
/* Own headerfiles */



/*---------------------- macro timer definition--------------------------- */
/* only definition for marking*/
//#define SystemTimerID   MCU_mTimerArray_06		/*timer06*/
//#define SystemDebugOSTimerID MCU_mTimerArray_27	/*timer27*/

/*---------------------- macro switch definition--------------------------- */

/* os sleep signal come from bus  */
#define FRAME_BusSleep		1
#define FRAME_CanBusSleep		1
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
#define FRAME_LinBusSleep		1
#else
#define FRAME_LinBusSleep		0
#endif
#define FRAME_KBusSleep		0

/* APP sleep signal */
#define FRAME_AppSleep		1
#define FRAME_CtsSleep		1
#define FRAME_EedSleep		0

/*remote signal from hardware*/
#define FRAME_RemoteSleep	0

/*use hardware ign as sleep*/
#define FRAME_HwIgnUsed	1	

/* pts sleep cmd: please confirm close the k15 line before send the sleep cmd*/
//#define FRAME_PtsSleep		1

/*use rte or not */
#define FRAME_RteUsed		0	

/*if use the hardware ign as wake up reource*/
#define FRAME_RouserIgnUsed		1	

/*if use the remote signal as wake up reource*/
#define FRAME_RouserRemoteUsed	0		

/*if hw watch dog used as hardware*/
#define FRAME_VccCutOffUsed 		0

/*if hw SBC used for close sbc when standby*/
#define FRAME_HwSBCUsed 			1


/*if hw watch dog used*/
#define FRAME_HwWdgUsed 		0




/*-----------------------below use them only on debug mode-------------------*/
/*1=enable 0=disable please use it only on debug mode*/
/*the reset and init time are not use this time just system tick*/

/* monitor the task running timer  base tick is 100us use HAL_DebugOSTimerID */
#define DebugOS_MonitorTaskTimer	0
#if (DebugOS_MonitorTaskTimer==1)
	#define HAL_DebugOSTimerID		MCU_mTAUB0_0	/*be sure this time is not occupied by other function*/
#endif
/*monitor the array:
FRAME_u16ForeOnTaskTimeNow,
FRAME_u16ForeOnMaxTaskTimeRec,
FRAME_u16BackOnTaskTimeNow,
FRAME_u16BackOnMaxTaskTimeRec
*/

#if (DebugOS_MonitorTaskTimer==1)
#define DebugOS_MaxLoadRate			0
/*sw max load rate statistic of On state . the DebugOS_MonitorTaskTimer macro must open 
monitor the array:
OS_u16MaxForeLoadRate
OS_u16MaxBackLoadRate
OS_u16MaxFBLoadRate
*/
#endif


/* record task timer which running than 7ms use HAL_SystemTimerID 
monitor:
FRAME_u16InternalDataErrorCode
*/
#define DebugOS_RecordTaskErr			0

/* pin flip for test task running time */
#define DebugPinTest						1

/*sw initialize time not include startup(hw) base tick is 10ms use HAL_SystemTimerID
monitor:
FRAME_u16InternalDataSwInitTimeCounter
*/
#define DebugOS_SwInitTime				0	

/*monitor the  stack less than 25%,less than 50%,less than 75%,less than 100%*/

//#define DebugOs_SwStackPercent		0

#if (DebugOs_SwStackPercent==1)
#define OS_u16StackStartCfg	0xcdff		/* reference to the xcl */
#define OS_u16StackEndCfg	0xcfff
#endif




#if (FRAME_HwIgnUsed)
/*the default k15 input pin is P06 */
#define FRAME_nIGN2PortPin		True //0x0006
#endif


/*if use the hardware ign as wake up reource*/
#if (FRAME_RouserIgnUsed	==	1)
	#define FRAME_IGN_EXT_ID 	MCU_mEINT_ID_INT2
#endif

/*if use the remote signal as wake up reource*/
#if ( FRAME_RouserRemoteUsed==1)
	#define FRAME_REMOTE_EXT_ID 	
#endif

/*if used hardware watchdog*/
#if (FRAME_HwWdgUsed==1)	
	//4Power_IC watchdog clear control pin(hardware watchdog)
	#define FRAME_HWwatchdog_PortPin		0x0007

#endif

#define Frame_TaskWdgCfg	1

typedef struct _FRAME_AppWdgCfg
{
	uint8 	u8Taskid;	
	uint16     u16MaxTick;
	uint8  	u8OverflowCounter;
	uint8  	u8ResetMCU;
	tFuncPtr 	vfunTaskWdgprocL1;
	tFuncPtr 	vfunTaskWdgprocL2;
}FRAME_AppWdgCfgType;

#if(Frame_TaskWdgCfg==1)
typedef enum
{
	Frame_nTask1,
	Frame_nTask2,
	Frame_nTask3,
	Frame_nTaskMax
}Frame_TaskIdDef;



#define OverflowL1	1	// overflow number
#define OverflowL2	2
uint16 Frame_RunningTick[Frame_nTaskMax];
uint8   Frame_OverflowTick[Frame_nTaskMax];
#endif


frame_ext uint8 FRAME_axGetForegroundOnThread(void);		/*use to calculate the mcu load*/
frame_ext uint8 FRAME_axGetBackgroundOnThread(void) ;

//#define ForeOnTaskNumCfg (ForeOnTaskNum)
//#define BackOnTaskNumCfg (BackOnTaskNum)




/*-----------foreground task list of schedule Active--------------*/

extern const ThreadAction FRAME_axForegroundActiveThread[];

/*----------- foreground task list of schedule On--------------*/
extern const ThreadAction FRAME_axForegroundOnThread[];

/*----------- background task list of schedule Active--------------*/
extern const ThreadAction FRAME_axBackgroundActiveThread[];

/*-----------backgroud task list of schedule On--------------*/
extern const ThreadAction FRAME_axBackgroundOnThread[];

frame_ext uint8 FRAME_axGetForegroundActiveThread(void);

frame_ext uint8 FRAME_axGetForegroundOnThread(void);

frame_ext uint8 FRAME_axGetBackgroundActiveThread(void);

frame_ext uint8 FRAME_axGetBackgroundOnThread(void);


frame_ext void FRAME_vFrameResetExt (void);



frame_ext  void FRAME_vFrameWakeUpExt (void);



frame_ext void FRAME_vFrameActiveOnExt (void);



frame_ext void FRAME_vFrameOnActiveExt (void);



frame_ext void FRAME_vFrameStandbyActiveExt(void);



frame_ext void FRAME_vFrameActiveStandbyCfgIOExt(void);



frame_ext void FRAME_vFrameActiveStandbyExt(void);

frame_ext void FRAME_vFrameUnusedPinCfg(void);

frame_ext void FRAME_v1msTaskSchedule(void);
 
frame_ext void FRAME_vExtAlwaysTaskSchedule(void);

#if (Frame_TaskWdgCfg==1)
frame_ext void FRAME_vTaskWdgDet(void);
#endif

frame_ext void IGN_ifIgn2ExternInterrupt(void);


#if (DebugOS_MonitorTaskTimer==1)	
frame_ext void FRAME_vForeOnTaskTimeStart(void);
frame_ext void FRAME_vForeOnTaskTimeEnd(uint8 TaskNum);
frame_ext void FRAME_vBackOnTaskTimeStart(void);
frame_ext void FRAME_vBackOnTaskTimeEnd(uint8 TaskNum);
frame_ext void FRAME_vTaskTimeTick(void);		// for isr service function     
#endif




#if (FRAME_RteUsed==1)
	/*================================================================*/

	frame_ext void Rte_DiagProto_Diag_vDeinit(void);
	frame_ext void Rte_DiagProto_Diag_vInit(void);
	frame_ext void Rte_DiagProto_Diag_vMain(void);
	frame_ext void Rte_DiagProto_Diag_vReset(void);
	frame_ext void Rte_DiagProto_Diag_vDescAppl(void);

	frame_ext void Rte_DtcProto_Dtc_vDeinit(void);
	frame_ext void Rte_DtcProto_Dtc_vInit(void);
	frame_ext void Rte_DtcProto_Dtc_vMain(void);
	frame_ext void Rte_DtcProto_Dtc_vReset(void);

	frame_ext void Rte_AcccProto_Accc_vDeinit(void);
	frame_ext void Rte_AcccProto_Accc_vInit(void);
	frame_ext void Rte_AcccProto_Accc_vMain(void);
	frame_ext void Rte_AcccProto_Accc_vReset(void);
	frame_ext void Rte_AcccProto_Accc_vActive(void);

	frame_ext void Rte_AirdProto_Aird_vDeinit(void);
	frame_ext void Rte_AirdProto_Aird_vInit(void);
	frame_ext void Rte_AirdProto_Aird_vMain(void);
	frame_ext void Rte_AirdProto_Aird_vReset(void);

	frame_ext void Rte_Bctl1Proto_Bctl_vDeinit(void);
	frame_ext void Rte_Bctl1Proto_Bctl_vInit(void);
	frame_ext void Rte_Bctl1Proto_Bctl_vMain(void);
	frame_ext void Rte_Bctl1Proto_Bctl_vReset(void);

	frame_ext void Rte_Bctl2Proto_BctlDrv_vDeinit(void);
	frame_ext void Rte_Bctl2Proto_BctlDrv_vInit(void);
	frame_ext void Rte_Bctl2Proto_BctlDrv_vMain(void);
	frame_ext void Rte_Bctl2Proto_BctlDrv_vReset(void);

	frame_ext void Rte_EvapProto_Evap_vDeinit(void);
	frame_ext void Rte_EvapProto_Evap_vInit(void);
	frame_ext void Rte_EvapProto_Evap_vMain(void);
	frame_ext void Rte_EvapProto_Evap_vReset(void);

	frame_ext void Rte_HctProto_Hct_vDeinit(void);
	frame_ext void Rte_HctProto_Hct_vInit(void);
	frame_ext void Rte_HctProto_Hct_vMain(void);
	frame_ext void Rte_HctProto_Hct_vReset(void);

	frame_ext void Rte_IctProto_Ict_vDeinit(void);
	frame_ext void Rte_IctProto_Ict_vInit(void);
	frame_ext void Rte_IctProto_Ict_vMain(void);
	frame_ext void Rte_IctProto_Ict_vReset(void);

	frame_ext void Rte_IonProto_Ion_vDeinit(void);
	frame_ext void Rte_IonProto_Ion_vInit(void);
	frame_ext void Rte_IonProto_Ion_vMain(void);
	frame_ext void Rte_IonProto_Ion_vReset(void);

	frame_ext void Rte_KeyProto_Key_vDeinit(void);
	frame_ext void Rte_KeyProto_Key_vInit(void);
	frame_ext void Rte_KeyProto_Key_vMain(void);
	frame_ext void Rte_KeyProto_Key_vReset(void);

	frame_ext void Rte_KnobProto_Knob_vDeinit(void);
	frame_ext void Rte_KnobProto_Knob_vInit(void);
	frame_ext void Rte_KnobProto_Knob_vMain(void);
	frame_ext void Rte_KnobProto_Knob_vReset(void);

	frame_ext void Rte_MacProto_Mac_vDeinit(void);
	frame_ext void Rte_MacProto_Mac_vInit(void);
	frame_ext void Rte_MacProto_Mac_vMain(void);
	frame_ext void Rte_MacProto_Mac_vReset(void);

	frame_ext void Rte_MmiProto_Mmi_vDeinit(void);
	frame_ext void Rte_MmiProto_Mmi_vInit(void);
	frame_ext void Rte_MmiProto_Mmi_vMain(void);
	frame_ext void Rte_MmiProto_Mmi_vReset(void);
	frame_ext void Rte_MmiProto_Mmi_vActive(void);

	frame_ext void Rte_OatProto_Oat_vDeinit(void);
	frame_ext void Rte_OatProto_Oat_vInit(void);
	frame_ext void Rte_OatProto_Oat_vMain(void);
	frame_ext void Rte_OatProto_Oat_vReset(void);

	frame_ext void Rte_PowProto_Pow_vDeinit(void);
	frame_ext void Rte_PowProto_Pow_vInit(void);
	frame_ext void Rte_PowProto_Pow_vMain(void);
	frame_ext void Rte_PowProto_Pow_vReset(void);

	frame_ext void Rte_IgnProto_Ign_vDeinit(void);
	frame_ext void Rte_IgnProto_Ign_vInit(void);
	frame_ext void Rte_IgnProto_Ign_vMain(void);
	frame_ext void Rte_IgnProto_Ign_vReset(void);

	frame_ext void Rte_RdcProto_Rdc_vDeinit(void);
	frame_ext void Rte_RdcProto_Rdc_vInit(void);
	frame_ext void Rte_RdcProto_Rdc_vMain(void);
	frame_ext void Rte_RdcProto_Rdc_vReset(void);

	frame_ext void Rte_RevProto_Rev_vDeinit(void);
	frame_ext void Rte_RevProto_Rev_vInit(void);
	frame_ext void Rte_RevProto_Rev_vMain(void);
	frame_ext void Rte_RevProto_Rev_vReset(void);

	frame_ext void Rte_RfaProto_Rfa_vDeinit(void);
	frame_ext void Rte_RfaProto_Rfa_vInit(void);
	frame_ext void Rte_RfaProto_Rfa_vMain(void);
	frame_ext void Rte_RfaProto_Rfa_vReset(void);

	frame_ext void Rte_SunProto_Sun_vDeinit(void);
	frame_ext void Rte_SunProto_Sun_vInit(void);
	frame_ext void Rte_SunProto_Sun_vMain(void);
	frame_ext void Rte_SunProto_Sun_vReset(void);

	frame_ext void Rte_VelProto_Vel_vDeinit(void);
	frame_ext void Rte_VelProto_Vel_vInit(void);
	frame_ext void Rte_VelProto_Vel_vMain(void);
	frame_ext void Rte_VelProto_Vel_vReset(void);

	frame_ext void Rte_DimProto_Dim_vMain(void);
	frame_ext void Rte_DimProto_Dim_vReset(void);
	frame_ext void Rte_DimProto_Dim_vInit(void);
	frame_ext void Rte_DimProto_Dim_vDeInit(void);

	frame_ext void Rte_CcsProto_Ccs_vMain(void);
	frame_ext void Rte_CcsProto_Ccs_vDeinit(void);
	frame_ext void Rte_CcsProto_Ccs_vReset(void);
	frame_ext void Rte_CcsProto_Ccs_vInit(void);


	frame_ext void Rte_DcmProto_Dcm_vMain(void);
	frame_ext void Rte_DcmProto_Dcm_vReset(void);
	frame_ext void Rte_DcmProto_Dcm_vInit(void);
	frame_ext void Rte_DcmProto_Dcm_vDeInit(void);

	frame_ext void Rte_Ncv77x8Proto_Ncv77x8_vMain(void);
	frame_ext void Rte_Ncv77x8Proto_Ncv77x8_vReset(void);
	frame_ext void Rte_Ncv77x8Proto_Ncv77x8_vInit(void);
	frame_ext void Rte_Ncv77x8Proto_Ncv77x8_vDeinit(void);
	frame_ext void Rte_Ncv77x8Proto_Ncv77x8_vActive(void);

	frame_ext void Rte_Ncv7240Proto_Ncv7240_vMain(void);
	frame_ext void Rte_Ncv7240Proto_Ncv7240_vReset(void);
	frame_ext void Rte_Ncv7240Proto_Ncv7240_vInit(void);
	frame_ext void Rte_Ncv7240Proto_Ncv7240_vDeinit(void);

	frame_ext void Rte_CanAppProto_CanApp_vMain(void);
	frame_ext void Rte_CanAppProto_CanApp_vActive(void);
	frame_ext void Rte_CanAppProto_CanApp_vReset(void);
	frame_ext void Rte_CanAppProto_CanApp_vInit(void);
	frame_ext void Rte_CanAppProto_CanApp_vDeinit(void);

	frame_ext void Rte_LinAppProto_LinApp_vMain(void);
	frame_ext void Rte_LinAppProto_LinApp_vActive(void);
	frame_ext void Rte_LinAppProto_LinApp_vReset(void);
	frame_ext void Rte_LinAppProto_LinApp_vInit(void);
	frame_ext void Rte_LinAppProto_LinApp_vDeinit(void);

	frame_ext void Rte_CcpProto_Ccp_vMain(void); 
	frame_ext void Rte_CcpProto_Ccp_vReset(void); 
	frame_ext void Rte_CcpProto_Ccp_vInit(void); 
	frame_ext void Rte_CcpProto_Ccp_vDeinit(void); 

	frame_ext void Rte_SysProto_Sys_vMain(void);
	frame_ext void Rte_SysProto_Sys_vInit(void);
	frame_ext void Rte_SysProto_Sys_vDeinit(void);
	frame_ext void Rte_SysProto_Sys_vActive(void);

	frame_ext void Rte_BtmProto_Btm_vMain(void);
	frame_ext void Rte_BtmProto_Btm_vInit(void);
	frame_ext void Rte_BtmProto_Btm_vReset(void);
	frame_ext void Rte_BtmProto_Btm_vDeinit(void);
	frame_ext void Rte_BtmProto_Btm_vActive(void);


	frame_ext void Rte_LcdProto_Lcd_vMain(void);
	frame_ext void Rte_LcdProto_Lcd_vReset(void);
	frame_ext void Rte_LcdProto_Lcd_vInit(void);
	frame_ext void Rte_LcdProto_Lcd_vDeinit(void);

	frame_ext void Rte_ShcProto_Shc_vReset(void);
	frame_ext void Rte_ShcProto_Shc_vMain(void);
	frame_ext void Rte_ShcProto_Shc_vInit(void);
	frame_ext void Rte_ShcProto_Shc_vDeinit(void);

	frame_ext void Rte_CtsProto_Cts_vActive(void);
	frame_ext void Rte_CtsProto_Cts_vReset(void);
	frame_ext void Rte_CtsProto_Cts_vInit(void);
	frame_ext void Rte_CtsProto_Cts_vDeinit(void);
	frame_ext void Rte_CtsProto_Cts_vGetRteInput();
	frame_ext void Rte_CtsProto_Cts_vRte100msTask0(void);
	frame_ext void Rte_CtsProto_Cts_vRte100msTask1(void);
	frame_ext void Rte_CtsProto_Cts_vRte100msTask2(void);
	frame_ext void Rte_CtsProto_Cts_vWriteRteOutput();

	frame_ext void Rte_Ncv7240Proto_Ncv7240_vObdMain(void);
	frame_ext void Rte_PowProto_Pow_vObdMain(void);
	frame_ext void Rte_KeyProto_Key_vOBDMain(void);
	frame_ext void Rte_Ncv77x8Proto_Ncv77x8_vOBDMain(void);
	frame_ext void Rte_Bctl2Proto_BctlDrv_vOBDMain(void);
	frame_ext void Rte_DimProto_Dim_vOBDMain(void);
	frame_ext void Rte_LcdProto_Lcd_vOBDMain(void);
	frame_ext void Rte_IoHwPwm_IoHwPwmReset(void);
#endif



#endif





