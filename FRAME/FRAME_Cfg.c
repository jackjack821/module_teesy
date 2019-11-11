/*******************************************************************************
| Module Name: Task config
| File Name: os_framecfg.c
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

|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver        	Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 
|
|2016.4.14      a2.2             Li Ning		the first version for integration

********************************************************************************/

#ifndef OS_Framecfg
#define OS_Framecfg

/* System-headerfiles */

#include "FRAME.h"
#include "FRAME_cfg.h"
#include "Debug.h"

#include "pow.h"
#include "ign.h"
#include "SBC.h"
#include "canccl.h"
#include "LINCCL.h"
#include "EED.h"
#include "Appdesc.h"
#include "CCP.h"
#include "NCV77x9.h"
#include "Accc.h"
#include "Dcm.h"
#include "Aird.h"
#include "Bctl.h"
#include "BctlDrv.h"
#include "Key.h"
#include "Knob.h"
#include "Dim.h"
#include "Lcd.h"
#include "Hct.h"
#include "Oat.h"
#include "Vel.h"
#include "Sun.h"
#include "Evap.h"
#include "Rfa.h"
#include "Vkey.h"
//#include "Nat.h"
//#include "Ict.h"
#include "Ccs.h"
#include "Cts_export.h"
#include "Mac.h"
#include "Mmi.h"
#include "Rdc.h"
#include "Shc.h"
#include "Vel.h"
#include "Istp.h"
#include "Ion.h"
#include "TouchKey.h"
#include "Force.h"
#if (FRAME_RteUsed==1)
#include "Rte.h"
#include "Rte_Sys.h"
#endif

/* Foreign headerfiles */
//#include "sbc.h"


/*------------------------task schedule------------------------------*/

/* wdg for task*/
#if(Frame_TaskWdgCfg==1)
const FRAME_AppWdgCfgType Frame_auAllTaskWdg[Frame_nTaskMax]=
{
	/*task1 10ms, task2 100ms, task3 reserve*/
	/*   task  id			MaxTime,		MaxCounter    if reset			functionL1	funL2: Maxtime count 1 per 10ms*/
  	{Frame_nTask1, 		4,			1,			1, 			NULL ,		NULL},
  	{Frame_nTask2, 		70,			1,			1, 			NULL,		NULL  },	  	
  	{Frame_nTask3, 		800,			2,			1, 			NULL,		NULL  },	  	
};


#endif

/*-----------foreground task list of schedule Active--------------*/
 const ThreadAction FRAME_axForegroundActiveThread[]={
	{ &FRAME_vFrameForegroundTick1s },
       /*here add app and bus main function	*/       
//	{ &TpTask},                   
 //   { &DescTask},           
  //  { &LCD_vActive},            
    { &MMI_vActive},
	{ &FRAME_vFRAME_ForegroundReset }	
};

/*----------- foreground task list of schedule On--------------*/
const ThreadAction FRAME_axForegroundOnThread[]={
	#if (DebugOS_MaxLoadRate==1)
	{ &OS_vMaxLoadStatisticStart},
	#endif
	{ &FRAME_vFrameForegroundTick1s },
	/*-------don't modify the above code-----*/
	/* add app and bus main function below	*/
	{ &IGN_vMain},
	//{ &TpTask},
	//{ &DescTask},
     //   { &DCM_vMain},
    //{ &NCV77x9_vMain},
    //{ &KNOB_vMain},
    { &DIM_vMain},
    { &MMI_vMain},	
    { &TOUCHKEY_vMain},
    { &KEY_vMain},	
    { &Force_vMain},  /*GET TEST,190419*/
  //  { &LCD_vMainCom0},
 //   { &LCD_vMainCom1},
 //   { &LCD_vMainCom2},
 //   { &LCD_vMainCom3},
    //{ &LCD_vMain},
      { &Debug_vMain},
#if(CarConfiguration == High_End)
    //{ &SHC_vMain},
#endif
    //{ &RDC_vMain},
    { &CCP_vMain},
  //  { &DTC_vMain},
  	{ &FRAME_vFRAME_ForegroundReset }
};


/*----------- background task list of schedule Active--------------*/
const ThreadAction FRAME_axBackgroundActiveThread[]={
	{&FRAME_vFrameBackgroundTick1s },		
	/*here add app and bus main function	*/
	{&EED_vMain},
   // {&OAT_vActive},
    //{&VEL_vActive},
    //{&SUN_vActive},
   // {&EVAP_vActive},
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
   // {&ION_vActive},
#endif
 //   {&DIAG_vActive},
	{&FRAME_vFRAME_BackgroundReset },
};

/*-----------backgroud task list of schedule On--------------*/
const ThreadAction FRAME_axBackgroundOnThread[]={
	{ &FRAME_vFrameBackgroundTick1s },	
	/* add app and bus main function below	*/
	{ &EED_vMain},
    //{ &CCS_vMain},
    //{ &ACCC_vMain},
   // { &AIRD_vMain},
   // { &HCT_vMain},
   // { &OAT_vMain},
   // { &VEL_vMain},
   // { &SUN_vMain},
   // { &EVAP_vMain},
   // { &RFA_vMain},
	//{ &CTS_v100msTask0},
	//{ &CTS_v100msTask1},
	//{ &CTS_v100msTask2},
    //{ &NAT_vMain},
    //{ &ICT_vMain},
    { &MAC_vMain},
    //{ &BCTL_vMain},
    //{ &BCTLDRV_vMain},
    //{ &ISTP_vMain},
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
    //{ &AQS_vMain},
    //{ &ION_vMain},
#endif                                                      
    { &DIAG_vMain},
	/*-------don't modify the below code-----*/                                    
	/*task reset*/                                                          
	#if (DebugOS_MaxLoadRate==1)                   
	{ &OS_vMaxLoadStatisticEnd},                     
	#endif
	{ &FRAME_vFRAME_BackgroundReset }	
	
};



/*-----------1ms task expended time must be less than 100us--------------*/
void FRAME_v1msTaskSchedule(void)
{
	/****1ms task below here******/
    CANCCL_vTickCntCallBack();
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
    LINCCL_vTickCntCallBack();
#endif
    //KNOB_v1msProcess();
	//Force_u16ForceSensorADProcess();
	DCM_vMain();
	
}


/*------------------------------------------
	1.always run task no matter k15 on or off
	2.run before all the app task 
	3.run per 10ms
	4.be care the perform time of task
--------------------------------------------*/
void FRAME_vExtAlwaysTaskSchedule(void)
{
	/****always task below here******/
    SBC_vMain();
	SBC_WDFeedDog();
}



/*-----------------------------app and bus --------------------------------*/

/*****************************************************************************
 Function      : FRAME_vFrameResetApp                                             *
 Description   : os main loop reset for app and bus       .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vMainLoop for app and bus
*****************************************************************************/
void FRAME_vFrameResetExt (void)
{
    CANCCL_vReset();
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
    LINCCL_vReset();
#endif
    SBC_vReset();
	EED_vReset();
    //ACCC_vReset();
//	DIAG_vReset();
 //   DCM_vReset();
  //  AIRD_vReset();
    KEY_vReset();
    KNOB_vReset();
    DIM_vReset();
   LCD_vReset();
   // HCT_vReset();
   // OAT_vReset();
    //VEL_vReset();
    //SUN_vReset();
   // EVAP_vReset();
   // RFA_vReset();
    VKEY_vReset();
	//BCTL_vReset();
	//BCTLDRV_vReset();
    //ICT_vReset();
    //CCS_vReset();
    CCP_vReset();
    //CTS_vReset();
    //NAT_vReset();
    MAC_vReset();
    MMI_vReset();
//    DTC_vReset();
    //RDC_vReset();
#if(CarConfiguration == High_End)
    //SHC_vReset();
#endif
    //ISTP_vReset();
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
    //AQS_vReset();
    //ION_vReset();
#endif
    //NCV77x9_vReset();
 DCM_vReset();
 Force_vReset();
}


/*****************************************************************************
 Function      : FRAME_vFrameWakeUpApp                                             *
 Description   : action when system wake up from standb state   for app and bus     .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vFrameStandbyActive for app and bus
*****************************************************************************/
void FRAME_vFrameWakeUpExt (void)
{
	
}



/*****************************************************************************
 Function      : FRAME_vFrameActiveOnApp                                            *
 Description   : action when system state change from active to On   for app and bus                          *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vCONActionActiveOn for app and bus
*****************************************************************************/
void FRAME_vFrameActiveOnExt (void)
{
    //MCU_vCycleWakeUp(0);
 //   DIAG_vInit();
    DCM_vInit();
    CCP_vInit();
 //   DTC_vInit();
    //ACCC_vInit();
    //AIRD_vInit();
    KEY_vInit();
    KNOB_vInit();
    DIM_vInit();
    LCD_vInit();
    //HCT_vInit();
    //OAT_vInit();
    //VEL_vInit();
   // SUN_vInit();
    //EVAP_vInit();
    //RFA_vInit();
    VKEY_vInit();
    //ICT_vInit();
    //CCS_vInit();
    //CTS_vInit();
    //NAT_vInit();
    MAC_vInit();
    MMI_vInit();
	//BCTL_vInit();
	//BCTLDRV_vInit();
   // RDC_vInit();
#if(CarConfiguration == High_End)
    //SHC_vInit();
#endif
    //ISTP_vInit();
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
    //AQS_vInit();
    //ION_vInit();
#endif
    //NCV77x9_vInit();
}



/*****************************************************************************
 Function      : FRAME_vFrameOnActiveApp                                             *
 Description   : action when system state change from On to Active for app and bus      .                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vCONActionOnActive for app and bus
*****************************************************************************/
void FRAME_vFrameOnActiveExt (void)
{	
	CCP_vDeinit();
 //   DTC_vDeinit();  
//	DIAG_vDeinit();
    DCM_vDeinit();
    //ACCC_vDeinit();
    //AIRD_vDeinit();
    KEY_vDeinit();
    KNOB_vDeinit();
    DIM_vDeinit();
  //  LCD_vDeinit();
    //OAT_vDeinit();
    //HCT_vDeinit();
    //VEL_vDeinit();
    //SUN_vDeinit();
    //EVAP_vDeinit();
    //RFA_vDeinit();
    VKEY_vDeinit();
    //ICT_vDeinit();
    //CCS_vDeinit();
    //CTS_vDeinit();
    //NAT_vDeinit();
    MAC_vDeinit();
    MMI_vDeinit();
	//BCTL_vDeinit();
	//BCTLDRV_vDeinit();
    //NCV77x9_vDeinit();
    //RDC_vDeinit();
#if(CarConfiguration == High_End)
	//SHC_vDeinit();
#endif
    //ISTP_vDeinit();
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
    //AQS_vDeinit();
    //ION_vDeinit();
#endif
    //MCU_vCycleWakeUp(CTS_boGetActiveFlag());
    
}



/*****************************************************************************
 Function      : FRAME_vFrameStandbyActiveApp                                             *
 Description   : action when system state change from Standby to Active for app and bus                *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by OS_vSysCONActionStandbyActiveApp
*****************************************************************************/
void FRAME_vFrameStandbyActiveExt(void)
{
    //CANCCL_vReset();
    //CANCCL_vStandbyActive();
	SBC_vReset();
}



/*****************************************************************************
 Function      : FRAME_vFrameActiveStandbyCfgIoApp                                             *
 Description   : action when system state change from Active to Standby for app and bus      .       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by OS_vSysCONActionActiveStandbyApp
*****************************************************************************/
void FRAME_vFrameActiveStandbyCfgIOExt(void)
{

}



/*****************************************************************************
 Function      : FRAME_vFrameActiveStandbyApp                                             *
 Description   : action when system state change from Active to Standby for app and bus      .              *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vCONActionActiveStandby for app and bus
*****************************************************************************/
void FRAME_vFrameActiveStandbyExt(void)
{
       
	FRAME_vFrameActiveStandbyCfgIOExt();

    MCU_vStandbyCtrl_CleanAllWakeUpFactor();
	//if(CTS_boGetActiveFlag()==True)
	//{
		//MCU_vCycleWakeUp(1);
	//}
	//SBC_vStandby();
}



void FRAME_vFrameUnusedPinCfg(void)
{

		
		
}



#if (FRAME_RteUsed== 1)
	/*for complier pass*/
	/*Std_ReturnType Rte_AcccProto_AcccForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_AirdProto_AirdForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_Bctl1Proto_BctlForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_Bctl2Proto_BctlDrvForceControl(uint32 ForceIoControlWord) 
	{return(1);}


	Std_ReturnType Rte_CcsProto_CcsForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_CtsProto_CtsForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DcmProto_DcmForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DimProto_DimForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DiagProto_ClearAllDtc(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DiagProto_DtcForceIoControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DiagProto_GetExtendData(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DiagProto_GetMaskFaultDtcList(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DiagProto_GetMaskFaultDtcNum(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DiagProto_GetSnapShotData(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DiagProto_GetSupportDtcList(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DtcProto_ClearAllDtc(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DtcProto_DtcForceIoControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DtcProto_GetExtendData(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DtcProto_GetMaskFaultDtcList(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DtcProto_GetMaskFaultDtcNum(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DtcProto_GetSnapShotData(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DtcProto_GetSupportDtcList(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_EvapProto_EvapForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_HctProto_HctForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_IctProto_IctForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_IonProto_IonForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_Istp_IstpForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_KeyProto_KeyForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_MacProto_MacForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_MmiProto_MmiForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_Ncv77x9_Ncv77x9ForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_OatProto_OatForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_RevProto_RevForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_RfaProto_RfaForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_SunProto_SunForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_VelProto_VelForceControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Eed_u8ReadGroupData(EedData portDefArg1, EedData * EedData, EedDataLen EedDataLen)
	{return(1);}

	Std_ReturnType Eed_u8WriteGroupData(EedData portDefArg1, EedData * EedData, EedDataLen EepDataLen)
	{return(1);}
	
	Std_ReturnType Rte_RdcProto_RdcForceControl(UInt32 ForceIoControlWord)
	{return(1);}
	
	Std_ReturnType Rte_AqsProto_AqsForceControl(uint32 ForceIoControlWord) 
	{return(1);}*/

	Std_ReturnType Rte_DtcProto_ForceIoControl(UInt32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DtcProto_ClearAllDtc(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DtcProto_DtcForceIoControl(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DtcProto_GetExtendData(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DtcProto_GetMaskFaultDtcList(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DtcProto_GetMaskFaultDtcNum(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DtcProto_GetSnapShotData(uint32 ForceIoControlWord) 
	{return(1);}

	Std_ReturnType Rte_DtcProto_GetSupportDtcList(uint32 ForceIoControlWord) 
	{return(1);}



   
	

#endif

/*****************************don't modify below**************************************/

/*****************************************************************************
 Function      : FRAME_axGetForegroundActiveThread                                             *
 Description   : reculate the lenth of oregroundActiveThread       .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vMainLoop
*****************************************************************************/

uint8 FRAME_axGetForegroundActiveThread(void)
{
	uint8 u8lenth;
	u8lenth=sizeof(FRAME_axForegroundActiveThread)/sizeof(ThreadAction);
       return u8lenth;
}

/*****************************************************************************
 Function      : FRAME_axGetForegroundOnThread                                             *
 Description   : reculate the lenth of oregroundOnThread       .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vMainLoop
*****************************************************************************/

uint8 FRAME_axGetForegroundOnThread(void)
{
	uint8 u8lenth;
	u8lenth=sizeof(FRAME_axForegroundOnThread)/sizeof(ThreadAction);	
       return u8lenth;
}



/*****************************************************************************
 Function      : FRAME_axGetBackgroundActiveThread                                             *
 Description   : reculate the lenth of BackgroundActiveThread       .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vMainLoop
*****************************************************************************/

uint8 FRAME_axGetBackgroundActiveThread(void)
{
       return sizeof(FRAME_axBackgroundActiveThread)/sizeof(ThreadAction);
}

/*****************************************************************************
 Function      : FRAME_axGetBackgroundOnThread                                             *
 Description   : reculate the lenth of BackgroundOnThread       .                                       *
                                                             *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function be call by FRAME_vMainLoop
*****************************************************************************/

uint8 FRAME_axGetBackgroundOnThread(void)
{
	uint8 u8lenth;
	u8lenth=sizeof(FRAME_axBackgroundOnThread)/sizeof(ThreadAction);
	return u8lenth;
}






#if (DebugOS_MonitorTaskTimer==1)	
/*------------------parameter definition-----------------------------*/
/*uint8 ForeTaskNum;
uint8 BackTaskNum;
ForeTaskNum=sizeof(FRAME_axForegroundOnThread)/sizeof(ThreadAction);
BackTaskNum=FRAME_axGetBackgroundOnThread();*/

/*below counter increase one time per 100us*/
uint16 FRAME_u16TaskTimeReg ;
uint16 FRAME_u16ForeOnTaskTimeNow[sizeof(FRAME_axForegroundOnThread)/sizeof(ThreadAction)] ;		/*use to calculate the mcu load*/
uint16 FRAME_u16BackOnTaskTimeNow[sizeof(FRAME_axBackgroundOnThread)/sizeof(ThreadAction)] ;
uint16 FRAME_u16ForeOnMaxTaskTimeRec[sizeof(FRAME_axForegroundOnThread)/sizeof(ThreadAction)] ;	
uint16 FRAME_u16BackOnMaxTaskTimeRec[sizeof(FRAME_axBackgroundOnThread)/sizeof(ThreadAction)] ;
uint16 FRAME_u16ForeOnTaskDtc[sizeof(FRAME_axForegroundOnThread)/sizeof(ThreadAction)] ;
uint16 FRAME_u16BackOnTaskDtc[sizeof(FRAME_axBackgroundOnThread)/sizeof(ThreadAction)] ;
	




/*----------------function prototype declaration-----------------*/
void FRAME_vForeOnTaskTimeStart(void);
void FRAME_vForeOnTaskTimeEnd(uint8 TaskNum);
void FRAME_vBackOnTaskTimeStart(void);
void FRAME_vBackOnTaskTimeEnd(uint8 TaskNum);
void FRAME_vTaskTimeTick(void);		// for isr service function     




/*****************************************************************************
 Function      : FRAME_vForeTaskTime                                             *
 Description   :clear timer when the task start    .                                       *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function must be call when the tast start. 
*****************************************************************************/
void FRAME_vForeOnTaskTimeStart(void)
{	
	
	FRAME_u16TaskTimeReg=0x0000U;
	FRAME_vHalTaskTimeStart_DebugTimer();
}

/*****************************************************************************
 Function      : FRAME_vForeTaskTimeEnd                                             *
 Description   :record the max running timer    .                                       *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function must be call when the tast end 
*****************************************************************************/
void FRAME_vForeOnTaskTimeEnd(uint8 TaskNum)
{
	/*stop the timer*/
	FRAME_vHalTaskTimeStop_DebugTimer();
	/*record the current running time*/
	FRAME_u16ForeOnTaskTimeNow[TaskNum]=FRAME_u16TaskTimeReg;

	/*record the max running time*/
	if(FRAME_u16TaskTimeReg>FRAME_u16ForeOnMaxTaskTimeRec[TaskNum])
	{
		FRAME_u16ForeOnMaxTaskTimeRec[TaskNum]=FRAME_u16TaskTimeReg;
		
	}
	
	/*record the flag of timeout*/
	if(FRAME_u16TaskTimeReg > ForeTaskTimeOutCfg)
	{
		FRAME_u16ForeOnTaskDtc[TaskNum] = 1;
	}

	/*cleart counter*/
	FRAME_u16TaskTimeReg = 0x0000U;

	/*----------------max load stastic-------------*/
	#if (DebugOS_MaxLoadRate==1)
	{
		OS_u16MaxForeLoadCounterTemp += FRAME_u16ForeOnTaskTimeNow[TaskNum];
	}
	#endif
}

/*****************************************************************************
 Function      : FRAME_vBackTaskTimeStart                                             *
 Description   :clear timer when the task start    .                                       *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function must be call when the tast start. 
*****************************************************************************/
void FRAME_vBackOnTaskTimeStart(void)
{	
	FRAME_u16TaskTimeReg=0x0000U;
	FRAME_vHalTaskTimeStart_DebugTimer();
}

/*****************************************************************************
 Function      : FRAME_vBackTaskTimeEnd                                             *
 Description   :record the max running timer    .                                       *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function must be call when the tast end 
*****************************************************************************/
void FRAME_vBackOnTaskTimeEnd(uint8 TaskNum)
{
	/*stop the timer*/
	FRAME_vHalTaskTimeStop_DebugTimer();
	/*record the current running time*/
	FRAME_u16BackOnTaskTimeNow[TaskNum]=FRAME_u16TaskTimeReg;

	/*record the max running time*/
	if(FRAME_u16TaskTimeReg>FRAME_u16BackOnMaxTaskTimeRec[TaskNum])
	{
		FRAME_u16BackOnMaxTaskTimeRec[TaskNum]=FRAME_u16TaskTimeReg;
	}
	
	/*record the flag of timeout*/
	if(FRAME_u16TaskTimeReg > BackTaskTimeOutCfg)
	{
		FRAME_u16BackOnTaskDtc[TaskNum] = 1;
	}

	/*cleart counter*/
	FRAME_u16TaskTimeReg = 0x0000U;

	/*----------------max load stastic-------------*/
	#if (DebugOS_MaxLoadRate==1)
	{
		OS_u16MaxBackLoadCounterTemp += FRAME_u16BackOnTaskTimeNow[TaskNum];
	}
	#endif
}

/*****************************************************************************
 Function      : FRAME_vTaskTimeTick                                             *
 Description   :process the system base time                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by interrupt of timer 15
*****************************************************************************/
void FRAME_vTaskTimeTick(void)
{
	/* max timeout process */
	/*if(FRAME_u16TaskTimeReg >= TaskTimeOutErrCfg)  
	{
		uint8 TempNum;
		for(TempNum=0;TempNum<ForeTaskNum;TempNum++)
		{
			FRAME_u16ForeOnTaskDtc[TempNum]=1;
		}

		for(TempNum=0;TempNum<BackTaskNum;TempNum++)
		{
			FRAME_u16BackOnTaskDtc[TempNum]=1;
		}
	}
	else*/
	{
		 /*---------------------------100us base ----------------------------*/
		 FRAME_u16TaskTimeReg++;	 
		 TestECircle();
	
	}        
}


#endif


/*****************************************************************************
 Function      : FRAME_u8TaskWdgDet                                 
 Description   : detect running time of all task
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
void FRAME_vTaskWdgDet(void)
{
	
	#if (Frame_TaskWdgCfg==1)	
		uint8 i=0;	
		for(; i<Frame_nTaskMax;i++)
		{
			if(Frame_RunningTick[i]<Frame_auAllTaskWdg[i].u16MaxTick)
			{
				Frame_RunningTick[i]++;
			}
			else
			{
				/*clear tick*/
				Frame_RunningTick[i]=0;

				
				if(Frame_OverflowTick[i]<Frame_auAllTaskWdg[i].u8OverflowCounter)
				{
					Frame_OverflowTick[i]++;
				}

				/*overflow process*/
				if(Frame_auAllTaskWdg[i].u8ResetMCU==True)
				{
					//Level1
					if(Frame_OverflowTick[i]==OverflowL1)
					{
						if(Frame_auAllTaskWdg[i].vfunTaskWdgprocL1!=NULL)
						{
							Frame_auAllTaskWdg[i].vfunTaskWdgprocL1();
						}					
					}

					//Level2
					if(Frame_OverflowTick[i]==OverflowL2)
					{
						if(Frame_auAllTaskWdg[i].vfunTaskWdgprocL2!=NULL)
						{
							Frame_auAllTaskWdg[i].vfunTaskWdgprocL2();
						}					
					}
					
				}
				else
				{
					//do noting
				}
			}
				
		}
		  
	#endif
	
}


#endif
/*****************************************************************************
* EOF:
******************************************************************************/










