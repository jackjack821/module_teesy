/*******************************************************************************
| Module Name: Task frame schedule model
| File Name: os_frame.c
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
| ----------  -------  -------------  -------------------------------------------------|
|2015.9.2      a2.2             Li Ning		the first version for integration
|2016.3.8	 a2.3 	      Li Ning		update mcu driver
|2016.4.4	 a2.3 	      Li Ning		set  the sleep time 5s
|2016.4.10	 a2.4 	      Li Ning		add ign init function
|2016.4.14	 a2.5 	      Li Ning		modify the FRAME_vMachineStatusSet
********************************************************************************/

#ifndef Frame_c
#define Frame_c
//#include "rte_internal.h" 
/* Own headerfiles */
#include "FRAME.h"
#include "FRAME_Pte.h"


/* Foreign headerfiles */
#include "POW.h"
#include "IGN.h"
#include "canccl.h"
#include "LINCCL.h"
#include "Sbc.h"
//#if (FRAME_FlashDrvUsed==1)
#include "fls_drv.h"
#include "eed.h"
//#endif
#include "Rte_Internal.h"


/*global variable*/
SYS_FRAME SYS_frame;



/*static global variable*/
static uint8  OS__u8Foregrond1sCount = 0U;
static uint8  OS__u8Backgrond1sCount = 0U;

static uint8  Foreground_u8ActiveThreadNumber=0U;
static uint8  Foreground_u8OnThreadNumber=0U;


static uint8  Background_u8ActiveThreadNumber=0U;
static uint8  Background_u8OnThreadNumber=0U;



/* the system status update */
static uint16 FRAME_u16SleepCnt;

static  uint8 OS_SysState;


static uint16 OS_u16ForceSleep;

static uint16 FRAME_u16IDIgnStaticOn;
static uint16 FRAME_u16IDIgnStable;
static uint16 FRAME_u16IDIgnIgn2IoStauts;



void FRAME_vFRAME_Foreground(void);
void FRAME_vFRAME_Background(void);


void FRAME_vFrameReset (void);
void FRAME_vFrameWakeUp (void);
void FRAME_vTick(void);

void FRAME_vMainLoop(void);


uint8 FRAME_u8GetMode(void);
void FRAME_vFRAME_ForegroundTaskActive(void);
void FRAME_vFRAME_ForegroundTaskOn(void);
void FRAME_vFRAME_ForegroundTaskErr(void);
void FRAME_vFRAME_BackgroundTaskActive(void);
void FRAME_vFRAME_BackgroundTaskOn(void);
void FRAME_vFRAME_BackgroundTaskErr(void);

static void FRAME_vWdtHwReset(void);
static void FRAME_vStateProcess(void);
static void FRAME_vMachineStateEmplement(void);

static void FRAME_vCONActionStandby(void);
static void FRAME_vCONActionActive(void);
static void FRAME_vCONActionOn(void);
static void FRAME_vCONActionStandbyActive(void);
static void FRAME_vCONActionActiveStandby(void);
static void FRAME_vCONActionActiveOn(void);
static void FRAME_vCONActionOnActive(void);
static void FRAME_vCONActionStandbyOn(void);
static void FRAME_vCONActionError(void);
static void FRAME_vSysSleepCount(void);
static uint8 FRAME_vReadSysSleepStatus(void);
static uint8 FRAME_vReadHwSleepStatus(void);
static uint8 FRAME_vReadPtsSleepStatus(void);
static uint8 FRAME_vActiveStautsCheck(void);
static uint8 FRAME_vOnStautsCheck(void);
static uint8 FRAME_vStandbyStautsCheck(void);

void FRAME_vFrameActiveStandbyCfgIO(void);

tstSYS_ForceSort FRAME_u8ForceSort;


static uint16 FRAME_u16InternalDataFlag1000MS_BG;
static uint16 FRAME_u16InternalDataFlag1000MS_FG;
//static uint16 FRAME_u16InternalDataFlagFlagFGrun;
//static uint16 FRAME_u16InternalDataFlagFlagBGrun;
static uint16 FRAME_u16InternalDataSysInfo;

static uint16 FRAME_u16InternalDataForegroudTick;



static uint16 FRAME_u16InternalDataBackgroudTick;
static uint16 FRAME_u16InternalDataTaskRunningTime;
static uint16 FRAME_u16InternalDataTaskRunEnable;
static uint16 FRAME_u16InternalDataForegroundRunEnable;
static uint16 FRAME_u16InternalDataBackgroundRunEnable;
static uint16 FRAME_u16InternalDataSwVersion;
static uint16 FRAME_u16InternalDataErrorCode;
#if(DebugOS_MonitorTaskTimer==1)	
static uint16 FRAME_u16InternalDataForeOnTaskDtcOut;
static uint16 FRAME_u16InternalDataBackOnTaskDtcOut;
#endif
#if (DebugOS_MaxLoadRate==1)
static uint16 FRAME_u16InternalDataForeMaxLoadOut;
static uint16 FRAME_u16InternalDataBackOnTaskDtcOut;
#endif
#if (DebugOS_SwInitTime==1)
static uint16 FRAME_u16InternalDataSwInitTimeCounter;
#endif

static uint16 Frame_u16TestCnt=0;

/*****************************************************************************
 Function      : FRAME_vIDInputUpdate                                             *
 Description   :update the input  interface data                         *
 Takes         : None                                                                        *
 Return Value  : None                                                        *
 Note: 	this function  be call by FRAME_vFRAMEAlways
*****************************************************************************/
static uint8 FRAME_vIDInputUpdate(void)
{
	uint8 u8retvalue;
	u8retvalue = 0U;	
	/*main function call all variable before run*/
	FRAME_u16IDIgnStaticOn 			= FRAME_vImpIDIgnStaticOn();
	FRAME_u16IDIgnStable			= FRAME_vImpIDIgnStable();
	FRAME_u16IDIgnIgn2IoStauts 	= FRAME_vImpIDIgnIgn2IoStauts();		/*need use getvalue interface not use rte */ 	

	u8retvalue = 1u;
	return (u8retvalue);
}

/*****************************************************************************
 Function      : FRAME_vIOutputUpdate                                             *
 Description   :update the output  interface data  o                        *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by FRAME_vFRAMEAlways
*****************************************************************************/
static uint16 FRAME_vIDOutputUpdate(void)
{
	uint16 u16retvalue;
	u16retvalue = 0U;

	/*update interface variable*/
	/*1s flag need to update when it be set and clear
	FRAME_u16Array[SYS_nu16Flag1000MS_BG] 	=get_bSysBackground1s();
	FRAME_u16Array[SYS_nu16Flag1000MS_FG] 	= get_bSysForeground1s();
	*/
	FRAME_u16Array[SYS_nu16Info]				= get_bSysInfo();
	FRAME_u16Array[SYS_nu16SwVersion]			= get_bSysSwVersion();
	FRAME_u16Array[SYS_nu16ErrorCode]			= get_bSysErrorCode();
	#if (DebugOS_SwInitTime==1)
		FRAME_u16Array[OS_nu16SwInitTimeOut] 	= get_bSysSwInitCounter();
	#endif
	FRAME_u16Array[SYS_nu16ResetStatus]			= SYS_getSystemBusy();

	/*transmit data*/
	FRAME_vExpIDAll();

	u16retvalue = 1u;
	return (u16retvalue);
}



/* ===========================================================================
* Function   : static uint8 FRAME_vHmiDataReset(void)
* Description: this function be call when k30 turn on from off state thant mcu can work normally.
* Input      : none.
* Returns    : none.
*/

static uint8  FRAME_vHmiDataReset(void)
{
	uint8 u8retvalue;
	u8retvalue =0U;
	
	/* set the default output value for uint16 */
	clr_bSysBackground1s();
	clr_bSysForeground1s();
	clr_bSysInfo();
	set_bSysSwVersion(0x0400U);
	clr_bSysErrorCode();
	#if (DebugOS_SwInitTime==1)
		clr_bSysSwInitCounter();
	#endif
		
	u8retvalue =1U;
	return (u8retvalue);
}
 
/* pin flip for test task running time */
#if (DebugPinTest==1)

void TestECircle(void);

#define testpin MCU_mPinID_JP0_4
static uint8 reverse1;


void TestECircle(void)
{	 
	reverse1++;
	MCU_u16PinWrite(testpin,(reverse1&0x01));
			
}



#endif

#if (DebugOS_SwInitTime==1)
/*count the sw reset timer only use for test running time of  all reset function use for status   pow on */
static uint16 OS_u16SwResetCounter;	
static uint16   OS_u16SwResetFlag;
/*count the sw init timer not include reset time only use for status changed from standby to on*/
	
static uint16   OS_u16SwInitFlag;
void OS_vSwResetTimePro(void);
void OS_vSwInitTimePro(void);
void OS_vSwResetTimeStart(void);
void OS_vSwResetTimeEnd(void);
void OS_vSwInitTimeStart(void);
void OS_vSwInitTimeEnd(void);

 void OS_vSwResetTimePro(void)
{
	if(OS_u16SwResetFlag==1)
	{
		OS_u16SwResetCounter++;
	}
}
void OS_vSwInitTimePro(void)
{
	if(OS_u16SwInitFlag==1)
	{
		inc_bSysSwInitCounter();
	}
}
void OS_vSwResetTimeStart(void)
{
	OS_u16SwResetCounter	=0U;	
	OS_u16SwResetFlag		=1;
	
}
void OS_vSwResetTimeEnd(void)
{
	OS_u16SwResetFlag		=0;
	
}
void OS_vSwInitTimeStart(void)
{
	clr_bSysSwInitCounter();	
	OS_u16SwInitFlag		=1;
	
}
void OS_vSwInitTimeEnd(void)
{
	OS_u16SwInitFlag		=0;
	
}

#endif 



	
#if (DebugOS_MaxLoadRate==1)


/*100ms x 1000 : count per 100us, duty/circle*100=percent of mcu load*/	
#define  OS_n16MaxLoadCircle		1000
#define  OS_n16MaxLoadFactor	10	/*duty/1000*100*/
static uint16 OS_u16MaxForeLoadCounter;	
static  uint16 OS_u16MaxBackLoadCounter;
static uint16 OS_u16MaxFBLoadCounter;	
static uint16 OS_u16MaxForeLoadCounterTemp;	
static uint16 OS_u16MaxBackLoadCounterTemp;
static uint16 OS_u16MaxFBLoadCounterTemp;	
static uint16 OS_u16MaxForeLoadRate;	
static uint16 OS_u16MaxBackLoadRate;
static uint16 OS_u16MaxFBLoadRate;




OS_tenu16MaxLoadNum OS_tenu16MaxLoadState;

static void OS_vMaxLoadStatisticStart(void);
static void OS_vMaxLoadStatisticEnd(void);
static  void OS_vMaxLoadStatisticClear(void);


static void OS_vMaxLoadStatisticStart(void)
{	/*only record on  state*/
	if(FRAME_u8SysState == KeepOn)
	{
		if((OS_tenu16MaxLoadState == OS_nu16StatisticEnd)||(OS_tenu16MaxLoadState ==OS_nu16NotUsed))
	 	{
	 		OS_tenu16MaxLoadState 				= OS_nu16StatisticStart;
			OS_u16MaxForeLoadCounterTemp		= 0x0000U;	
			OS_u16MaxBackLoadCounterTemp		= 0x0000U;
			OS_u16MaxFBLoadCounterTemp		= 0x0000U;
	 	}
	}
	else
	{
		OS_tenu16MaxLoadState 				= OS_nu16NotUsed;
		OS_u16MaxForeLoadCounterTemp		= 0x0000U;	
		OS_u16MaxBackLoadCounterTemp		= 0x0000U;
		OS_u16MaxFBLoadCounterTemp		= 0x0000U;
	}
	
 }

static void OS_vMaxLoadStatisticEnd(void)
{	/*only record on  state*/
	if(FRAME_u8SysState == KeepOn)
	{
		if(OS_tenu16MaxLoadState == OS_nu16StatisticStart)
	 	{
	 		OS_tenu16MaxLoadState	= OS_nu16StatisticEnd;
			/*foreground task max rate*/
			if(OS_u16MaxForeLoadCounterTemp>OS_u16MaxForeLoadCounter)
			{
				OS_u16MaxForeLoadCounter	= OS_u16MaxForeLoadCounterTemp;
				OS_u16MaxForeLoadRate 	= OS_u16MaxForeLoadCounter/OS_n16MaxLoadFactor;
			}

			/*background task max rate*/
			if(OS_u16MaxBackLoadCounterTemp>OS_u16MaxBackLoadCounter)
			{
				OS_u16MaxBackLoadCounter	= OS_u16MaxBackLoadCounterTemp;
				OS_u16MaxBackLoadRate		= OS_u16MaxBackLoadCounter/OS_n16MaxLoadFactor;
			}

			/*fore and back ground task max rate*/
			OS_u16MaxFBLoadCounterTemp = OS_u16MaxForeLoadCounterTemp+OS_u16MaxBackLoadCounterTemp;
			if(OS_u16MaxFBLoadCounterTemp>OS_u16MaxFBLoadCounter)
			{
				OS_u16MaxFBLoadCounter	= OS_u16MaxFBLoadCounterTemp;
				OS_u16MaxFBLoadRate		= OS_u16MaxFBLoadCounter/OS_n16MaxLoadFactor;
			}
			
	 	}
	}
	else
	{
		OS_tenu16MaxLoadState 				= OS_nu16NotUsed;
		OS_u16MaxForeLoadCounterTemp		= 0x0000U;	
		OS_u16MaxBackLoadCounterTemp		= 0x0000U;
		OS_u16MaxFBLoadCounterTemp		= 0x0000U;
	}
		
}

static  void OS_vMaxLoadStatisticClear(void)
 {
	OS_u16MaxForeLoadCounter			= 0x0000U;	
	OS_u16MaxBackLoadCounter			= 0x0000U;
	OS_u16MaxFBLoadCounter			= 0x0000U;
	OS_u16MaxForeLoadCounterTemp		= 0x0000U;	
	OS_u16MaxBackLoadCounterTemp		= 0x0000U;
	OS_u16MaxFBLoadCounterTemp		= 0x0000U;
	OS_tenu16MaxLoadState				= OS_nu16NotUsed;
	OS_u16MaxForeLoadRate				= 0x0000U;	
	OS_u16MaxBackLoadRate				= 0x0000U;
	OS_u16MaxFBLoadRate				= 0x0000U;
	/*avoid warning*/
	OS_u16MaxForeLoadRate				= OS_u16MaxForeLoadRate;	
	OS_u16MaxBackLoadRate				= OS_u16MaxBackLoadRate;
	OS_u16MaxFBLoadRate				= OS_u16MaxFBLoadRate;
	
	
 }


#endif

#if (DebugOs_SwStackPercent==1)
static uint16 OS_u16StackStart;	
static  uint16 OS_u16StackEnd;
static  uint16 OS_u16StackCurrent;
static  uint16 OS_u16StackCurrentMax;
static  uint16 OS_u16StackUseMax;

void FRAME_vFrameStackRec(void);
void FRAME_vFrameStackCal(void);
void FRAME_vFrameStackInit(void);

void FRAME_vFrameStackInit(void)
{
	OS_u16StackStart 		= OS_u16StackStartCfg;
	OS_u16StackEnd   		= OS_u16StackEndCfg;
	OS_u16StackCurrent 		=OS_u16StackEndCfg;
	OS_u16StackCurrentMax 	= OS_u16StackEndCfg;
	OS_u16StackUseMax		= 0x0000U;
}

void FRAME_vFrameStackRec(void)
{
	if(SP < OS_u16StackCurrent)
	{
		OS_u16StackCurrent = sp;
	}
}

/*calculate per 100ms when the system is on state */
void FRAME_vFrameStackCal(void)
{
	if((OS_u16StackCurrent<OS_u16StackStartCfg)||(OS_u16StackCurrent>OS_u16StackEndCfg))
	{
		OS_u16StackUseMax = 0xffffU;	/*overflow*/
	}
	else if(OS_u16StackCurrent < OS_u16StackCurrentMax)
	{
		OS_u16StackCurrentMax = OS_u16StackCurrent;
		OS_u16StackUseMax =100*(OS_u16StackCurrentMax-OS_u16StackStartCfg)/(OS_u16StackEndCfg-OS_u16StackStartCfg);
	}
	else
	{
		
	}	
	
}


#endif





/* counter  the occupy time of task,fore task increase one per 100us and back task increase one per 100us
     and record the max time in the array */



/*****************************************************************************
 Function      : FRAME_vFrameActiveStandbyCfgIo                                             *
 Description   : action when system state change from Active to Standby       .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vCONActionActiveStandby
*****************************************************************************/
void FRAME_vFrameActiveStandbyCfgIO(void)
{
	/*reference the hardware*/

	/*application and bus function add here*/
	FRAME_vFrameActiveStandbyCfgIOExt();
	
	
}

/*****************************************************************************
 Function      : FRAME_vFrameActiveStandbyCfgPowSupply                                             *
 Description   : control pow supply when system state change from Active to Standby       .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vCONActionActiveStandby
*****************************************************************************/
uint8 FRAME_vFrameActiveStandbyCfgPowSupply(void)
{
	/*reference the hardware*/
	uint8 u8retvalue;
	u8retvalue =0U;
	
	POW_vSupplyOff();
	
	u8retvalue =1U;
	return (u8retvalue);
}
  


/*****************************************************************************
 Function      : FRAME_vFrameStandby                                             *
 Description   : action when system is on standby state         .                                       *
                 Run every 10ms.                                            *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vFrameStandbyCfg
*****************************************************************************/
void FRAME_vFrameStandby (void)
{
    uint8 u8PtsSleepStatus = 0u;
	
	FRAME_vHalDi();
	if(FRAME_vFinalSleepCheck()==0)
	{
        u8PtsSleepStatus = FRAME_vReadPtsSleepStatus();
        FRAME_vHalEi();		/*recovery ei*/
        if(u8PtsSleepStatus == 1u)
        {
            //SBC_vNormalStandby();
			if(FRAME_vDoSBCSleepCmd() == 0)
			{
				FRAME_vHalStopMode();
			}
			else
			{
				FRAME_vDoSBCSleepCmd();	
			}
        }
        else
        {
    		/*Enter standby*/
            FRAME_vHalStopMode();
        }
        
	}
	else
	{
		FRAME_vHalEi();	/*this instruction hold interrupt until the next instruction*/		
		#if (FRAME_HwSBCUsed==1)
			if(FRAME_vDoSBCSleepCmd() == 0)
			{
				FRAME_vHalStopMode();
			}
			else
			{
				FRAME_vDoSBCSleepCmd();	
			}
 		#else		
			#if (FRAME_VccCutOffUsed==1)
				/*repeate close pow supply*/
				FRAME_vFrameActiveStandbyCfgPowSupply();
			#else		
				FRAME_vHalStopMode();	
			#endif
		#endif
	
	}
	
}

/*****************************************************************************
 Function      : FRAME_vFrameReset                                             *
 Description   : os main loop reset        .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vMainLoop
*****************************************************************************/
void FRAME_vFrameReset (void)
{
	/* the status is active when the system power on firstly*/
	SYS_biMachineStatusActiveTrue;
	SYS_biMachineStatusChange2ActiveTrue;		/* consistency the state */

	/* reset the  parameter of sleep mode*/
	//OS_boSleepCtrByObd 	= 0;	
    FRAME_u16SleepCnt 					= 0x0000U;
	
	FRAME_vHmiDataReset();
	
	
	/* module reset */		
	FRAME_vHalIgnReset();
	POW_vSupplyReset();		/*supply pow reset*/
	FRAME_vHalPowReset();
	

	/*set system busy*/
	SYS_biSystemBusyTrue;	
	clr_bSysSleepStatus();
	
	/*---------max load statistic reset--------*/	
	#if (DebugOS_MaxLoadRate==1)
	OS_vMaxLoadStatisticClear();	
	#endif

	/*update before all other app module*/
	FRAME_vIDOutputUpdate();

	FRAME_vHalPowMain();
	/*application function add here*/
	FRAME_vFrameResetExt();	
	

}


/*****************************************************************************
 Function      : FRAME_vFrameWakeUp                                             *
 Description   : action when system wake up from standb state       .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vFrameStandbyActive
*****************************************************************************/
void FRAME_vFrameWakeUp (void)
{
	/* the status is active when the system power on firstly*/
	

	/* reset the  parameter of sleep mode*/
    FRAME_u16SleepCnt 			= 0x0000U;
	/* module reset */	
	FRAME_vHalIgnReset();
	POW_vSupplyWakeup();		/*supply pow reset*/
	FRAME_vHalPowReset();	

    FRAME_vHalPowMain();
	clr_bSysSleepStatus();
	
	/*---------max load statistic init--------*/	
	#if (DebugOS_MaxLoadRate==1)
	OS_vMaxLoadStatisticClear();	
	#endif

	/*application function add here*/
	FRAME_vFrameWakeUpExt();
	

}


/*****************************************************************************
 Function      : FRAME_vFrameActiveOn                                             *
 Description   : action when system state change from active to On       .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vCONActionActiveOn
*****************************************************************************/
void FRAME_vFrameActiveOn (void)
{
	FRAME_vFRAME_BackgroundReset();
	FRAME_vFRAME_ForegroundReset();		
	POW_vSensorSupplyEnable();	/* be sure this switch open*/	
	FRAME_vHalPowInit();	
	FRAME_vHalIgnInit();
	Foreground_u8ActiveThreadNumber=0U;
	Foreground_u8OnThreadNumber=0U;
	#if  (DebugOS_SwInitTime==1)
	/*  init time counter*/	
	OS_vSwInitTimeEnd();
	#endif

	/*application function add here*/
	FRAME_vFrameActiveOnExt();
	
	

	
	
}

/*****************************************************************************
 Function      : FRAME_vFrameOnActive                                             *
 Description   : action when system state change from On to Active       .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vCONActionOnActive
*****************************************************************************/
void FRAME_vFrameOnActive (void)
{
	FRAME_vFRAME_BackgroundReset();
	FRAME_vFRAME_ForegroundReset();		
	//POW_vPwrContorl(POW_en5VoutputDisable);	
	Foreground_u8ActiveThreadNumber=0U;
	Foreground_u8OnThreadNumber=0U;

	/*application function add here*/
	FRAME_vFrameOnActiveExt();
	
}




/*****************************************************************************
 Function      : FRAME_vFrameStandbyActive                                             *
 Description   : action when system state change from Standby to Active       .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vCONActionStandbyActive
*****************************************************************************/
void FRAME_vFrameStandbyActive(void)
{
	FRAME_vIfCloseRouser();
	
	#if  (DebugOS_SwInitTime==1)
	/*  init time counter*/	
	OS_vSwInitTimeStart();
	#endif
	
	FRAME_vFrameWakeUp();
	Foreground_u8ActiveThreadNumber=0U;
	Foreground_u8OnThreadNumber=0U;

	/*set system busy*/
	SYS_biSystemBusyTrue;

	/*application function add here*/
	FRAME_vFrameStandbyActiveExt();
	
	
}

/*****************************************************************************
 Function      : FRAME_vFrameActive                                           *
 Description   : action when system state keep Active        .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vCONActionActive
*****************************************************************************/
static void FRAME_vFrameActive(void)
{
	SYS_biSystemBusyFalse;
}

/*****************************************************************************
 Function      : FRAME_vFrameOn                                           *
 Description   : action when system state keep on        .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vCONActionOn
*****************************************************************************/
static void FRAME_vFrameOn(void)
{
	
}



/*****************************************************************************
 Function      : FRAME_vFrameActiveStandby                                             *
 Description   : action when system state change from Active to Standby       .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vCONActionActiveStandby
*****************************************************************************/
void FRAME_vFrameActiveStandby(void)
{	
	Foreground_u8ActiveThreadNumber=0U;
	Foreground_u8OnThreadNumber=0U;
	Background_u8ActiveThreadNumber= 0U;
	Background_u8OnThreadNumber	= 0U;

	/*application function add here*/
	FRAME_vFrameOnActiveExt();				// for case that no k15 is on 
	FRAME_vFrameActiveStandbyCfgIO();

	/*close pow supply*/
	FRAME_vFrameActiveStandbyCfgPowSupply();
	
	/*open rouser*/
	FRAME_vIfOpenRouser();

	FRAME_vFrameActiveStandbyExt();

	
}
	

/*****************************************************************************
 Function      : FRAME_vFRAME_ForegroundReset                                             *
 Description   :reset the 10ms timebass of foreground      .                                       *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function must be call when all foreground task  finish. 
*****************************************************************************/
void FRAME_vFRAME_ForegroundReset(void)
{
	
	/*static uint8 ResetWait*/
	Foreground_u8ActiveThreadNumber=0U;
	Foreground_u8OnThreadNumber=0U;

	/*******wdg timer clear for task1***************/
	Frame_RunningTick[Frame_nTask1]=0;
	Frame_OverflowTick[Frame_nTask1]=0;
	
	
	/*wait for diag respond and reset MCU*/
	if(get_bSysForeground1s()  == 1)
	{
				
		set_bSysForeground1s(0);
		OS__u8Foregrond1sCount=0U;	
		
		/*update 1s flag*/
		FRAME_u16Array[SYS_nu16Flag1000MS_FG] 	= get_bSysForeground1s();
		FRAME_vExpIDSysForeground1s();
		FRAME_vRteProto_Update();
	}
    EED_vWriteFlowCheck();/*160625*/
	set_bSysForegroundRunEnable(False);
	
}

/*****************************************************************************
 Function      : FRAME_vFRAME_BackgroundReset                                             *
 Description   :reset the 10ms timebass of background      .                                       *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function must be call when all background task  finish. 
*****************************************************************************/
void FRAME_vFRAME_BackgroundReset(void)
{
		
		Background_u8ActiveThreadNumber= 0U;
		Background_u8OnThreadNumber	= 0U;	

		/*******wdg timer clear for task1***************/
		Frame_RunningTick[Frame_nTask2]=0;
		Frame_OverflowTick[Frame_nTask2]=0;
		
		if(get_bSysBackground1s() 	== 1)
		{
			set_bSysBackground1s(0);
			OS__u8Backgrond1sCount=0U;	

			/*update 1s flag*/
			FRAME_u16Array[SYS_nu16Flag1000MS_BG] 	=get_bSysBackground1s();
			FRAME_vExpIDSysBackground1s();
			FRAME_vRteProto_Update();
		}

		set_bSysBackgroundRunEnable(False);

		
}


/*****************************************************************************
 Function      : FRAME_vFrameForegroundTick1s                                             *
 Description   :1s counter of foreground      .                                       *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function must be call when all foregroudground task start. 
*****************************************************************************/
void FRAME_vFrameForegroundTick1s(void)
{
	
	
	if( OS__u8Foregrond1sCount<SYS_Foregroud1sCountMax)
	{
		OS__u8Foregrond1sCount++;
	}
	else
	{
		set_bSysForeground1s(1);

		/*update 1s flag*/
		FRAME_u16Array[SYS_nu16Flag1000MS_FG] 	= get_bSysForeground1s();
		FRAME_vExpIDSysForeground1s();
		FRAME_vRteProto_Update();
	}	

	
	
	
	/*EEXT_vCheckReady();*/

	
}

/*****************************************************************************
 Function      : FRAME_vFrameBackgroundTick1s                                             *
 Description   :1s counter of background      .                                       *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function must be call when all backgroudground task start. 
*****************************************************************************/
void FRAME_vFrameBackgroundTick1s(void)
{
	if( OS__u8Backgrond1sCount<SYS_Backgroud1sCountMax)
	{
		OS__u8Backgrond1sCount++;
	}
	else
	{	
		set_bSysBackground1s(1);

		/*update 1s flag*/
		FRAME_u16Array[SYS_nu16Flag1000MS_BG] 	=get_bSysBackground1s();
		FRAME_vExpIDSysBackground1s();
		FRAME_vRteProto_Update();
	}
	
}


/*****************************************************************************
 Function      : FRAME_vFRAME_ForegroundTaskActive                                             *
 Description   :perform the shedule of foreground accord the system state                              *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call per 10ms 
*****************************************************************************/
void FRAME_vFRAME_ForegroundTaskActive(void)
{
	uint8  u8NeedExit=0U,u8Index=0u;
	
	
	while(1U ==1U)
	{
		/*task run!*/
		if(Foreground_u8ActiveThreadNumber<FRAME_axGetForegroundActiveThread())
		{				
			u8Index=Foreground_u8ActiveThreadNumber;
			Foreground_u8ActiveThreadNumber++;
			FRAME_axForegroundActiveThread[u8Index].vfpAction();			

						
			/*task forbid*/			
			if(get_bSysForegroundRunEnable()==False)
			{
				u8NeedExit=1U;	/*if time out only record error the tast must continue to perform*/
			}
			
		}
		else
		{
			u8NeedExit=1U;
			Foreground_u8ActiveThreadNumber=0U;
		}
		
		if(u8NeedExit !=0U)
		{
			break;
		}
	}
	
}


/*****************************************************************************
 Function      : FRAME_vFRAME_ForegroundTaskOn                                                                *
 Description   :perform the shedule of foreground accord the system state                              *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call per 10ms 
*****************************************************************************/
void FRAME_vFRAME_ForegroundTaskOn(void)
{
	uint8 u8NeedExit=0U,u8Index=0u;
	
	while(1U ==1U)
	{
		/*task run!*/			
		if(Foreground_u8OnThreadNumber<FRAME_axGetForegroundOnThread())
		{				
			u8Index=Foreground_u8OnThreadNumber;
			Foreground_u8OnThreadNumber++;

			    #if (DebugOS_MonitorTaskTimer==1)
				FRAME_vForeOnTaskTimeStart();
				FRAME_axForegroundOnThread[u8Index].vfpAction();
				FRAME_vForeOnTaskTimeEnd(u8Index);
			#else
				FRAME_axForegroundOnThread[u8Index].vfpAction();
			#endif	                                                                                
					
			
			/*task forbid */
			//if((OS_TaskRunEnable()==0U) ||(OS_ForegroundRunEnable()==0U)) modify by ln on 20151223
			if(get_bSysForegroundRunEnable()==False)
			{
				u8NeedExit=1U;	/*if time out only record error the tast must continue to perform*/
			}
			
		}
		else
		{
			u8NeedExit=1U;
			Foreground_u8OnThreadNumber=0U;
		}
		
		if(u8NeedExit !=0U)
		{
			break;
		}
	}
	
}

/*****************************************************************************
 Function      : FRAME_vFRAME_ForegroundTaskErr                                             *
 Description   :perform the shedule of foreground accord the system state                              *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call per 10ms 
*****************************************************************************/
void FRAME_vFRAME_ForegroundTaskErr(void)
{	
	/*in wrong condition-----------------*/		
	Foreground_u8OnThreadNumber=0U;
	Foreground_u8ActiveThreadNumber=0U;
	
}
/*****************************************************************************
 Function      : FRAME_vFRAME_Foreground                                             *
 Description   :perform the shedule of foreground accord the system state                              *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call per 10ms 
*****************************************************************************/
void FRAME_vFRAME_Foreground(void)
{

	Frame_u16TestCnt ++;

	if(Frame_u16TestCnt >=2)
	{
		Frame_u16TestCnt = 0;
		//MCU_u16PinWrite(MCU_mPinID_P8_6, 1);
	}
	else
	{
		//MCU_u16PinWrite(MCU_mPinID_P8_6, 0);
	}
		
	/*foreground active*/
	if(((FRAME_u8SysState & (uint8)(1U<<0U)))!=0U)
	{
		FRAME_vFRAME_ForegroundTaskActive();
	}
	/*foreground on*/
	else  if(((FRAME_u8SysState & (uint8)(1U<<1U)))!=0U)
	{
		FRAME_vFRAME_ForegroundTaskOn();
	}
	/*foreground error*/
	else
	{
		FRAME_vFRAME_ForegroundTaskErr();
	}	
	
}


/*****************************************************************************
 Function      : FRAME_vFRAME_BackgroundTaskActive                                             *
 Description   :perform the shedule of background accord the system state                              *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call per 100ms 
*****************************************************************************/

void FRAME_vFRAME_BackgroundTaskActive(void)
{
	uint8 u8NeedExit=0u,u8Index=0u;	
	while(1U ==1U)
	{
		/*task run!*/		
		if(Background_u8ActiveThreadNumber<FRAME_axGetBackgroundActiveThread())
		{
			u8Index=Background_u8ActiveThreadNumber;
			Background_u8ActiveThreadNumber++;
			FRAME_axBackgroundActiveThread[u8Index].vfpAction();
			
			/*time out or task forbid*/
			if((get_bSysTaskRunEnable()==False) || (get_bSysBackgroundRunEnable()==False))
			{
				u8NeedExit=1u;	
			}
		}
		else
		{
			u8NeedExit=1u;
			Background_u8ActiveThreadNumber=0U;
		}
		
		if(u8NeedExit !=0u)
		{
			break;
		}
	}

}


/*****************************************************************************
 Function      : FRAME_vFRAME_BackgroundTaskOn                                             *
 Description   :perform the shedule of background accord the system state                              *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call per 100ms 
*****************************************************************************/

void FRAME_vFRAME_BackgroundTaskOn(void)
{
	uint8 u8NeedExit=0u,u8Index=0u;	
	
	while(1U ==1U)
	{
		/*task run!*/
		if(Background_u8OnThreadNumber<FRAME_axGetBackgroundOnThread())
		{
			u8Index=Background_u8OnThreadNumber;
			Background_u8OnThreadNumber++;
			
			#if (DebugOS_MonitorTaskTimer==1)
				FRAME_vBackOnTaskTimeStart();
				FRAME_axBackgroundOnThread[u8Index].vfpAction();
				FRAME_vBackOnTaskTimeEnd(u8Index);
			#else
				FRAME_axBackgroundOnThread[u8Index].vfpAction();
			#endif
			
			/*time out or task forbid*/
			if((get_bSysTaskRunEnable()==False)|| (get_bSysBackgroundRunEnable()==False))
						
			{
				u8NeedExit=1u;	
			
			}
		}
		else
		{
			u8NeedExit=1u;
			Background_u8OnThreadNumber=0U;
		}
		
		if(u8NeedExit !=0u)
		{
			break;
		}
	}	
}


/*****************************************************************************
 Function      : FRAME_vFRAME_BackgroundTaskErr                                             *
 Description   :perform the shedule of background accord the system state                              *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call per 100ms 
*****************************************************************************/

void FRAME_vFRAME_BackgroundTaskErr(void)
{
	/*in wrong condition-----------------*/
		
	Background_u8ActiveThreadNumber=0U;
	Background_u8OnThreadNumber=0U;
}

/*****************************************************************************
 Function      : FRAME_vFRAME_Background                                             *
 Description   :perform the shedule of background accord the system state                              *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call per 100ms 
*****************************************************************************/

void FRAME_vFRAME_Background(void)
{
	/*background active*/
	if(((FRAME_u8SysState & (uint8)(1U<<0U)))!=0U)
	{
		FRAME_vFRAME_BackgroundTaskActive();
	}
	/*background on*/
	else  if(((FRAME_u8SysState & (uint8)(1U<<1U)))!=0U)
	{
		FRAME_vFRAME_BackgroundTaskOn();
	}
	/*background error*/
	else
	{
		FRAME_vFRAME_BackgroundTaskErr();
	}	
	
}




/*****************************************************************************
 Function      : FRAME_vCONActionStandby                                             *
 Description   :action of standby state                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call when system keep  standby
*****************************************************************************/
static void FRAME_vCONActionStandby(void)
{
	FRAME_vFrameStandby();

}

/*****************************************************************************
 Function      : FRAME_vCONActionActive                                             *
 Description   :action of active state                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call when system keep  active
*****************************************************************************/

static void FRAME_vCONActionActive(void)
{
	FRAME_vFrameActive();	
}

/*****************************************************************************
 Function      : FRAME_vCONActionOn                                             *
 Description   :action of On state                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call when system keep  On
*****************************************************************************/

static void FRAME_vCONActionOn(void)
{
	 FRAME_vFrameOn();
}

/*****************************************************************************
 Function      : FRAME_vCONActionStandbyActive                                             *
 Description   :action of standby change to active                           *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call when system change from standby to active
*****************************************************************************/

static void FRAME_vCONActionStandbyActive(void)
{

	FRAME_vFrameStandbyActive();/*Standby to Active*/
}

/*****************************************************************************
 Function      : FRAME_vCONActionActiveStandby                                             *
 Description   :action of active change to standby                           *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call when system change from active to standby
*****************************************************************************/

static void FRAME_vCONActionActiveStandby(void)
{		
	FRAME_vFrameActiveStandby();/*Active2Standby()	*/
}


/*****************************************************************************
 Function      : FRAME_vCONActionActiveOn                                             *
 Description   :action of Active change to On                           *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call when system change from active to On
*****************************************************************************/

static void FRAME_vCONActionActiveOn(void)
{
	FRAME_vFrameActiveOn();/*Active2On()*/
}


/*****************************************************************************
 Function      : FRAME_vCONActionOnActive                                             *
 Description   :action of On change to Active                           *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call when system change from On to Active
*****************************************************************************/

static void FRAME_vCONActionOnActive(void)
{
	FRAME_vFrameOnActive();/*On2Active()*/
}

/*****************************************************************************
 Function      : FRAME_vCONActionStandbyOn                                             *
 Description   :action of Standby change to On                           *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call when system change from Standby to On
*****************************************************************************/

static void FRAME_vCONActionStandbyOn(void)
{
	FRAME_vCONActionStandbyActive();
	FRAME_vCONActionActiveOn();
}


/*****************************************************************************
 Function      : FRAME_vCONActionError                                             *
 Description   :action of os error                           *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call when system has error
*****************************************************************************/
static void FRAME_vCONActionError(void)
{
	FRAME_u8SysInitState &=(uint8)0x80;
}

/*****************************************************************************
 Function      : FRAME_vReadSysSleepStatus                                             *
 Description   : read sleep status of system     .              *     *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 
*****************************************************************************/
static uint8 FRAME_vReadSysSleepStatus(void)
{
	uint8 u8retvalue;
	u8retvalue=0;
	/*add sleep condition of app below*/
	if((SYS_getSystemBusy() == 0)&&(FRAME_u16SleepCnt >= OS_SleepCountCfg))
	{
		u8retvalue = 1;	/* enable sleep*/
	}
	else
	{
		u8retvalue = 0; /* disable sleep*/
	}
	
	return (u8retvalue);
	
}

/*****************************************************************************
 Function      : FRAME_vReadHwSleepStatus                                             *
 Description   : read sleep status of system     .              *     *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 
*****************************************************************************/
static uint8 FRAME_vReadHwSleepStatus(void)
{
	uint8 u8retvalue;
	u8retvalue=0;
	/*add sleep condition of app below*/
	
	if((FRAME_u16IDIgnStaticOn == 0)&&(FRAME_u16IDIgnStable==1))
	
	{
		u8retvalue = 1;	/* enable sleep*/
	}
	else
	{
		u8retvalue = 0; /* disable sleep*/
	}
	
	return (u8retvalue);
	
}

/*****************************************************************************
 Function      : FRAME_vReadPtsSleepStatus                                             *
 Description   : read sleep status of system     .              *     *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 
*****************************************************************************/
static uint8 FRAME_vReadPtsSleepStatus(void)
{
	uint8 u8retvalue;
	u8retvalue=0;
	/*add sleep condition of app below*/
	if((get_bPtsSleepStatus()==1)&&(SYS_getSystemBusy() == 0))
	{
		u8retvalue = 1;	/* enable sleep*/
	}
	else
	{
		u8retvalue = 0; /* disable sleep*/
	}
	
	return (u8retvalue);
	
}


/*****************************************************************************
 Function      : FRAME_vStandbyStautsCheck                                             *
 Description   :if On status     .              *     *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 
*****************************************************************************/
static uint8 FRAME_vStandbyStautsCheck(void)
{
	uint8 u8retvalue;
	u8retvalue=0;
	/*add sleep condition of app below*/
	if (((FRAME_vReadSysSleepStatus()==1)								/*system sleep condition*/
		&&(FRAME_vReadHwSleepStatus()==1)							      /*hardware sleep condition*/
		
		#if (FRAME_BusSleep==1)	
			&&(FRAME_vGetBusSleepStatus()==1)						/*bus sleep condition*/
		#endif

		//#if (FRAME_AppSleep==1)			
			//&&(FRAME_vGetAspSleepStatus()==1)						/*app sleep condition*/
		//#endif	
		)			
	)
	
	{
		u8retvalue = 1;	/* standby*/
	}
	else
	{
		u8retvalue = 0; /* not standby*/
	}
	
	return (u8retvalue);
	
}

/*****************************************************************************
 Function      : FRAME_vActiveStautsCheck                                             *
 Description   :if active status     .              *     *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 
*****************************************************************************/
static uint8 FRAME_vActiveStautsCheck(void)
{
	uint8 u8retvalue;
	u8retvalue=0;
	/*add sleep condition of app below*/
	 if((SYS_getSystemBusy() == 1) || (FRAME_u16IDIgnStaticOn == 0))			
	{
		u8retvalue = 1;	/* active*/
	}
	else
	{
		u8retvalue = 0; /* not active*/
	}
	
	return (u8retvalue);
	
}

/*****************************************************************************
 Function      : FRAME_vOnStautsCheck                                             *
 Description   :if On status     .              *     *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 
*****************************************************************************/
static uint8 FRAME_vOnStautsCheck(void)
{
	uint8 u8retvalue;
	u8retvalue=0;
	/*add sleep condition of app below*/
		
	if(FRAME_u16IDIgnStaticOn == 1)	
	{
		u8retvalue = 1;	/* on*/
	}
	else
	{
		u8retvalue = 0; /* not on*/
	}
	
	return (u8retvalue);
	
}



/*****************************************************************************
 Function      : FRAME_vSysSleepCount                                             *
 Description   :count for sleep                           *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call always
*****************************************************************************/
static void FRAME_vSysSleepCount(void)
{
	/*sleep count*/
	if (((SYS_getSystemBusy() == 0)
		&&(FRAME_vReadHwSleepStatus()==1)	
	#if (FRAME_BusSleep==1)	
		&&(FRAME_vGetBusSleepStatus()==1)
	#endif
	//#if (FRAME_AppSleep==1)		
		//&&(FRAME_vGetAspSleepStatus()==1)
	//#endif
	#if (FRAME_RemoteSleep==1)		
		&&(FRAME_vGetRemoteSleepStatus()==1)
	#endif	
	)
	
	)
	{
		if(FRAME_u16SleepCnt >=OS_SleepCountCfg)
		{
			FRAME_u16SleepCnt=OS_SleepCountCfg;			 
		}
		else
		{
			FRAME_u16SleepCnt++;
		}
	}
	
	else
	{
		FRAME_u16SleepCnt=0;
	}
}
/* =========================================================
* Function   	: void FRAME_vMachineStatusSet(void)
* Description	: must run one time  when call FRAME_vCONActionAlways
* Takes      	: Nothing
* Returns    	: Nothing
*/
/*-----------------------------system state check----------------------------*/
/*---------x x x x x x x x--------------------------------------------------- */
/*                | | | | | | | |					  	    							            */
/*                | | | | | | | |__last two-bit:00 is standby;01 is active;02 is on;03 is reserve        */
/*                | | | | | | |													                */
/*                | | | | | |___third is  SYS_biScheduleActionActive	      				           */
/*                | | | | |													                    */
/*                | | | | |__fourth is 	SYS_biScheduleActionOn					                    */
/*                | | | |      												                    */
/*                | | | |__1 is change to standby(don't care last state)				                */
/*                | | | 						            								       */
/*                | | |__1 is change to active (don't care last state)				                */
/*                | |     								            					           */
/*                | |__1 is change to on (don't care last state)					                    */
/*                |          								                   				 */
/*                |__system already reset       								                    */
/*-------------------------------------------------------------------------*/
extern uint8 FRAME_axBackgroundThread();
static void FRAME_vMachineStatusSet(void)
{
	
	/* active->standby*/
	FRAME_vSysSleepCount();
	
	/*pts standby*/
	if((FRAME_vReadPtsSleepStatus()==1)&&(FRAME_vReadHwSleepStatus()==1))
	{
	
		/*on2active*/                
		FRAME_vCONActionOnActive();	   			
		SYS_biMachineStatusActiveTrue;         
		SYS_biMachineStatusActionOnFalse;      


		/*active2standby*/ 
		FRAME_vCONActionActiveStandby();				 
		SYS_biMachineStatusActiveFalse; 
		SYS_biMachineStatusActionOnFalse; 


		/*standby*/ 
		SYS_biMachineStatusChange2StandbyTrue; 
		SYS_biMachineStatusChange2ActiveFalse; 
		SYS_biMachineStatusChange2OnFalse; 
		SYS_biMachineStatusActiveFalse; 
		SYS_biMachineStatusActionOnFalse;	 
		FRAME_vCONActionStandby(); 	        /* standby action */	
		
		 
		
	}

	/*standby*/
	else if (FRAME_vStandbyStautsCheck()==1)

	{
		SYS_biMachineStatusChange2StandbyTrue;
		 SYS_biMachineStatusChange2ActiveFalse;
		 SYS_biMachineStatusChange2OnFalse;
	}

	/* active	*/
	else if (FRAME_vActiveStautsCheck() == 1)
	{
		SYS_biMachineStatusChange2StandbyFalse;
		SYS_biMachineStatusChange2ActiveTrue;
		SYS_biMachineStatusChange2OnFalse;
	}

	/* on*/
	
	else if(FRAME_vOnStautsCheck()==1)
	{
		SYS_biMachineStatusChange2StandbyFalse;
		SYS_biMachineStatusChange2ActiveFalse;
		SYS_biMachineStatusChange2OnTrue;
	}

	/*other*/
	else
	{
		FRAME_u16SleepCnt = 0U;		/*avoid to count abnormally*/
	}
   


}



/*****************************************************************************
 Function      : FRAME_vMachineStateEmplement                                             *
 Description   :manage the system state                           *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by OS_vCurrentModeRun
*****************************************************************************/
static void FRAME_vMachineStateEmplement(void)
{	
	switch(FRAME_u8SysState)
	{
		case KeepStandby:			
			SYS_biMachineStatusActiveFalse;
			SYS_biMachineStatusActionOnFalse;	
			FRAME_vCONActionStandby(); 	        /* standby action */	
			
			break;

		case StandbyToActive:
			FRAME_vCONActionStandbyActive();				
			SYS_biMachineStatusActiveTrue;
			SYS_biMachineStatusActionOnFalse;
			break;

		case StandbyToOn:
			FRAME_vCONActionStandbyOn();				
			SYS_biMachineStatusActiveFalse;
			SYS_biMachineStatusActionOnTrue;				
			break;

		case ActiveToStandby:
			FRAME_vCONActionActiveStandby();				
			SYS_biMachineStatusActiveFalse;
			SYS_biMachineStatusActionOnFalse;
			break;

		case KeepActive:
			FRAME_vCONActionActive();				
			SYS_biMachineStatusActiveTrue;
			SYS_biMachineStatusActionOnFalse;			
			break;

		case ActiveToOn:
			FRAME_vCONActionActiveOn();				
			SYS_biMachineStatusActiveFalse;
			SYS_biMachineStatusActionOnTrue;
			break;

		case OnToActive:
			FRAME_vCONActionOnActive();				
			SYS_biMachineStatusActiveTrue;
			SYS_biMachineStatusActionOnFalse;
			break;

		case KeepOn:
			FRAME_vCONActionOn();				
			SYS_biMachineStatusActiveFalse;
			SYS_biMachineStatusActionOnTrue;
			break;

		default:
			FRAME_vCONActionError();  /*system busy*/
			break;	
	}		 

	/* extern module use it  */
	set_bSysInfo(FRAME_u8SysState);
}




/*****************************************************************************
 Function      : FRAME_vStateProcess                                             *
 Description   :check the system state and perform the action of the current state                           *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by FRAME_vFRAMEAlways
*****************************************************************************/
static void FRAME_vStateProcess(void)
{	

	/* this function must be done at first  */
	FRAME_vHalIgnMain();
	

	/*update interface data of RTE*/
	#if (FRAME_RteUsed == 1)
		Rte_SysProto_Sys_vMain();
	#endif

	/*update internal data*/
	FRAME_vIDInputUpdate();
	
	FRAME_vMachineStatusSet();

	FRAME_vMachineStateEmplement();	
	
	/* this function must be done after the system state confirm for switch power supply*/
	FRAME_vHalPowMain();

	/*update internal data*/
	FRAME_vIDOutputUpdate();

	/*update interface data of RTE*/
	#if (FRAME_RteUsed == 1)
		Rte_SysProto_Sys_vMain();
	#endif

	
	
		  
}


/*****************************************************************************
 Function      : FRAME_vWdtHwReset                                             *
 Description   :watch the hardware dog                            *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by FRAME_vFRAMEAlways
*****************************************************************************/
 static void FRAME_vWdtHwReset(void)
{
	FRAME_vHWdogClr();	
}

/*****************************************************************************
 Function      : FRAME_vFRAMEAlways                                             *
 Description   :run this subroutine always                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by FRAME_vMainLoop
*****************************************************************************/
void FRAME_vFRAMEAlways (void)
{
    CANCCL_vMain();
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
    LINCCL_vMain();
#endif

	if(get_bSysTaskRunEnable() !=False)
	{		
		/*10ms function*/
		if(get_bSysForegroundRunEnable() !=False)
		{
            MCU_u16ADCstart();        
            FRAME_vWdtHwReset();
            FRAME_vStateProcess();
            FRAME_vExtAlwaysTaskSchedule();
            FRAME_vFRAME_Foreground();			
		      
		}

		/*100ms function*/
		if((get_bSysBackgroundRunEnable()!=False )&& (get_bSysTaskRunEnable()!=False))
		{		
			FRAME_vFRAME_Background();
		}
	}

}




/*****************************************************************************
 Function      : FRAME_vTick                                             *
 Description   :process the system base time                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by interrupt of timer 14
*****************************************************************************/
void FRAME_vTick(void)
{
	inc_bSysForegroudTick();
	inc_bSysBackgroudTick();    

	#if  (DebugOS_SwInitTime==1)
	/*reset and init time counter*/
	OS_vSwResetTimePro();
	#endif

	#if (DebugOs_SwStackPercent==1)
	FRAME_vFrameStackRec();
	#endif
        
	 /*---------------------------1ms task ----------------------------*/

	/*1ms test*/
	
	
	#if (Frame_TaskWdgCfg==1)
	 	FRAME_vTaskWdgDet();
	#endif
	
        FRAME_v1msTaskSchedule();

	/*-------------------------- 10ms------------------------  */
	if(get_bSysForegroudTick()>=SYS_ForgroundTickCnt)
	{
		/*10ms test*/
		
		
		set_bSysTaskRunEnable(1);
		set_bSysForegroundRunEnable(1);
		clr_bSysForegroudTick();

	
		#if  (DebugOS_SwInitTime==1)
		OS_vSwResetTimePro();
		OS_vSwInitTimePro();
		#endif
		
	}
	
	/*--------------------------- 100ms---------------------------- */
	if(get_bSysBackgroudTick()>=SYS_BackGroundTickCnt)
	{	
		/*100ms test*/
		//TestPin1();
		
		set_bSysBackgroundRunEnable(1);
		clr_bSysBackgroudTick();
	}

	/*-------Task running max time in one frame is 7 ms------------ */	
	if(get_bSysTaskRunEnable()!=0)
	{
		inc_bSysTaskRunningTime();
		if(get_bSysTaskRunningTime()>=SYS_FrameMaxTime )
		{
			set_bSysTaskRunEnable(0);
			
			
			#if (DebugOS_RecordTaskErr==1)
			FRAME_u16InternalDataErrorCode|=OS_TimerOut7ms;
			
			/*if  need record detail of erorr you can use below code*/
			
			/*if(Foreground_u8ActiveThreadNumber>0)
			{
				FRAME_u16InternalDataErrorCode|=OS_ForeActiveTimeout;
			}
			
			if(Foreground_u8OnThreadNumber>0)
			{
				FRAME_u16InternalDataErrorCode|=OS_ForeOnTimeout;
			}

			if(Background_u8ActiveThreadNumber>0)
			{
				FRAME_u16InternalDataErrorCode|=OS_BackActiveTimeout;
			}

			if(Background_u8OnThreadNumber>0)
			{
				FRAME_u16InternalDataErrorCode|=OS_BackOnTimeout;
			}*/
			#endif

		}
	}
	else
	{
		clr_bSysTaskRunningTime();	/*clear timer at the 8th ms*/
	}
}

/*****************************************************************************
 Function      : FRAME_vPeripheralInit                                             *
 Description   :init for periphera                         *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by main function
*****************************************************************************/
void FRAME_vPeripheralInit(void)
{
	
}

//#if (FRAME_RteUsed==1)

void SYS_vActive(void)
{
	
}

 void SYS_vMain(void)
 {
 	
 }
 void SYS_vDeinit(void)
 {
      
 }

 void SYS_vInit(void)
 {
 	
 }
 
void SYS_vInterfaceDataUpdate(void)
{
	
}

//#else

/*getvalue funciton*/

//#endif


/*****************************************************************************
 Function      : FRAME_vMainLoop                                             *
 Description   :main function of os                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by main function
*****************************************************************************/

/*system main loop*/
void SYS_vMainLoop(void)
{		

	//MCU_u16ADCstart();
	/*system tick and debug tick. other module don't occupy these timers */
	/*#if (FRAME_32bitUsed ==1)		
		HAL_vTimerRegiste(HAL_SystemTimerID,1000U,FRAME_vTick);
	#endif*/
	//FRAME_vHalTimerRegiste_SysTimer();
	#if (DebugOS_MonitorTaskTimer==1)	
	/*------------------parameter definition-----------------------------*/
	//ForeTaskNum=FRAME_axGetForegroundOnThread();
	//BackTaskNum=FRAME_axGetBackgroundOnThread();
	#endif


	#if  (DebugOS_SwInitTime==1)
	/*reset and init time counter*/
	OS_vSwResetTimeStart();
	OS_vSwInitTimeStart();
	#endif

	
	//HAL_vAdcRegister();
	
	/*wd free for test*/
	//MCU_u16PinWrite((MUC_enPinID)0x0a0fu,1);
	
	FRAME_vFrameReset();

	#if  (DebugOS_SwInitTime==1)
	OS_vSwResetTimeEnd();
	#endif

	//FRAME_vHalPowMain();
    
	while(1U ==1U)
	{	
		FRAME_vHalSwWdtReset();
		FLS_vCheckReady();
		FRAME_vFRAMEAlways();
	}


}


/*****************************************************************************
 Function      : FRAME_u8ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType SYS_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
{
	uint8 u8Result=0;
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==1)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0x80:
				clr_bSysSleepStatus();
				break;
			case 0x81:
				set_bSysSleepStatus(1);
				break;
			
			default:
                		u8Result= 1;
				break;
		}
	}
	else
	{
		clr_bSysSleepStatus();
	}
        return u8Result;
}


#endif

/*****************************************************************************
* EOF:
******************************************************************************/















