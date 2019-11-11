/*******************************************************************************
| Module Name: Mmi, Man machine interface
| File Name: Mmi.c
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



#define MMI_DEVELOPMENT_DEBUG 1U
//#define MMI_UseRTE
//#if(CarConfiguration == High_End)
#define Virtual_Key
//#endif
#define Used_Knob
/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define MMI                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */
/* Please put the headerfiles which related to foreign here! */

#include "Ccp.h"
#include "Ccp_cfg.h"


#include "Key.h"
#include "POW.h"

#include "KNOB.h"
#include "SHC.h"
#include "RDC.h"
#include "Vkey.h"
#include "Pow.h"
#include "Bctl.h"
#include "Aird.h"
#include "Rfa.h"
#include "Accc.h"
/* Own headerfiles */
/* Please put the headerfiles which related to own here! */
#include "Mmi.h" 
#include "Mmi_Type.h"
#include "Mmi_Private.h" 
//#include "Mmi_Cfg.h" 
#include "KEY_Interface.h"




/*****************************************************************************
* GLOBAL DEFINITIONS
*
* In this section define
* - all global ROM-CONSTants of your module
* - all global variables of your module
*****************************************************************************/

/* example1: Global ROM-constants
   ----------------------------------------------------- */

/* example2: Global Variables
   ----------------------------------------------------- */
/******Define Struct for LCD display*************************************/


/* example1: Local Macros
   ----------------------------------------------------- */

/* example2: Local Define-constants
   ----------------------------------------------------- */


/* example3: Local ROM-constants
   ----------------------------------------------------- */


/* example4: Local Type Definition
   ----------------------------------------------------- */

static MMI_tstState MMI_tstAccc;
static MMI_tstState MMI_tstBctl;
static MMI_tstState MMI_tstAird;
static MMI_tstState MMI_tstRfa;
static MMI_tstState MMI_tstIon;
static MMI_tstState MMI_tstAqs;


//MMI_tstMmiStateSave1 MMI_tstMmiStSave;
MMI_tstStStore MMI_tstStateStore;
MMI_tstStatusSave MMI_Save; /*FROM fe-3z,BY ZSC,160524*/
/* example5: Local Variables
   ----------------------------------------------------- */
uint8 MMI_au8Array[MMI_nu8Max]; 
uint16 MMI_au16Array[MMI_nu16Max]; 
uint8 MMI_boNeedSaveData;
uint8 MMI_u8StateSaveTiming;
//static uint8 MMI_u8RearDefCtrl;
uint8 MMI_u8CurrentSysState;
uint8 MMI_u8OperationAfterTurnOn=False; /*flag that key operation after ION turn on */
static uint8 MMI_u8TurnOnByPm25=False; 
static uint8 MMI_u8Pm25PopupKeepTime =0;
uint16 MMI_u16KnobOrKeyOperationFlag;
/* ***********DEFINE RESPONSE FUNCTIONS OF MMI MODULE************************ */
/* ***Add Event functions in this block                           *** */ 
#ifdef Used_RearPanel
static void MMI_vTriggerEventNotUsed(void);
#endif
//static void MMI_vTriggerEventWatchDogTest(void);
static void MMI_vTriggerEventOff(void);
static void MMI_vTriggerEventAuto(void);

static void MMI_vTriggerEventDefrost(void);
static void MMI_vTriggerEventMaxAc(void);
static void MMI_vTriggerEventBlwInc(void);
static void MMI_vTriggerEventBlwDec(void);
static void MMI_vTriggerEventAc(void);
static void MMI_vTriggerEventModeL(void);
static void MMI_vTriggerEventModeR(void);
static void MMI_vTriggerEventShl(void);
static void MMI_vTriggerEventShr(void);
static void MMI_vTriggerEventRecAndFre(void);
static void MMI_vTriggerEventTempDrInc(void);
static void MMI_vTriggerEventTempDrDec(void);
static void MMI_vTriggerEventRearDefrost(void);
static void MMI_vTriggerEventIon(void);

#if (SYC_ZONES >= 2)
static void MMI_vTriggerEventTempPsInc(void);
static void MMI_vTriggerEventTempPsDec(void);
static void MMI_vTriggerEventDual(void);
static void MMI_vTriggerEventOnOff(void); /*on- off button*/
static void MMI_vTriggerEventAqs(void);
static void MMI_vTriggerEventRearMode(void);
static void MMI_vTriggerEventMode(void);
static MMI_tenAirdCtrl MMI_nActAirdSwitchRear(void);
static void MMI_vActSetTempRightInc(void);
static void MMI_vActSetTempRightDec(void);
static void MMI_vActSetTempDual(void);
static void MMI_vTriggerEventPM25(void);
#endif


#ifdef Virtual_Key
static void MMI_vTriggerEventMmiSetTempDr(void);   
static void MMI_vTriggerEventMmiSetTempPs(void);
static void MMI_vTriggerEventMmiPM25PopupActive(void);	   		
static void MMI_vTriggerEventMmiFan(void);		
static void MMI_vTriggerEventMmiAird(void);		
static void MMI_vTriggerEventTboxAirCleanerReq(void);
static void MMI_vTriggerEventTboxAirConditionerReq(void); 
static void MMI_vTriggerEventTboxTempReq(void);  
static void MMI_vTriggerEventMmiPM25PopupOperationSts(void);
static void MMI_vTriggerEventMmiDrvHeat(void);
static void MMI_vTriggerEventMmiPassHeat(void);
#endif

#ifdef Used_RearPanel
static void MMI_vTriggerEventRearBlwInc(void);	
static void MMI_vTriggerEventRearBlwDec(void);		
static void MMI_vTriggerEventTempRearUp(void);			  
static void MMI_vTriggerEventTempRearDn(void);			  
#endif

/* ***********EVENT_FUNCTIONS_END***************************************** */ 

/* ***Add Action functions in this block                           *** */ 

static void MMI_vReadMemData(void);
static void MMI_vResetDefaultValue(void);
static void MMI_vActBctlSpdIncLimit(void);
static void MMI_vActBctlSpdDecLimit(void);
static MMI_tenAcCtrl MMI_nActAcSwitch(void);
static MMI_tenAirdCtrl MMI_nActAirdSwitchR(void);
static MMI_tenAirdCtrl MMI_nActAirdSwitchL(void);
static MMI_tenRfaCtrl MMI_nActOffRfaSwitch(void);
static MMI_tenRfaCtrl MMI_nActRfaAqsSwitch(void);
static MMI_tenRfaCtrl MMI_nActRfaSwitch(void);
static void MMI_vActSetTempLeftInc(void);
static void MMI_vActSetTempLeftDec(void);

static void MMI_vActBctlEnterDef(void);
static void MMI_vActBctlEnterMaxAc(void);
static void MMI_vActAirdEnterDef(void);
static void MMI_vActAirdEnterMaxAc(void);
static void MMI_vActAcccEnterDef(void);
static void MMI_vActAcccEnterMaxAc(void);
static void MMI_vActRfaEnterDef(void);
static void MMI_vActRfaEnterMaxAc(void);
static void MMI_vActAcccAqsEnterDef(void);
static void MMI_vActAqsEnterMaxAc(void);
static void MMI_vChange2ManuFromDefManuOrMaxAcManu(void);
static void MMI_vActChange2Off(void);
static void MMI_vActEnterDefrost(void);
static void MMI_vActEnterMaxAc(void);

static void MMI_vActVkeyBlwCtrl(void);
static MMI_tenAirdCtrl MMI_nActVkeyAirdCtrl(void);

/* ***********ACTION_FUNCTIONS_END***************************************** */ 


/* ***********DEFINE LOCAL FUNCTIONS OF MMI MODULE*************************** */
static void MMI_vKeyMain(void);/*deal the key press */
static void MMI_vVKeyMain (void);
static void MMI_vKonbMain(void);

static void MMI_vPutValueInterFace(void);
static void MMI_vPutValue2Rte(void);

//static void MMI_vUpdateAllStatesByBuffer(void);
static void MMI_vUpdateSaveBuffer(void);

static void MMI_vAllHistoryStateStore(void);
//static void MMI_vAllHistoryStateStoreToDef(void);
static void MMI_vSysHistoryStateStore(void);
static void MMI_vSetTempHistoryStateStore(void);
static void MMI_vBctlHistoryStateStore(void);
static void MMI_vAcccHistoryStateStore(void);
static void MMI_vAirdHistoryStateStore(void);
static void MMI_vRfaHistoryStateStore(void);
static void MMI_vAqsHistoryStateStore(void);
static void MMI_vIonHistoryStateStore(void);
/******************************************************************************/
static void MMI_vAllHistoryStateRestore(void);
static void MMI_vAllHistoryStateRestoreAfterReset(void);
//static void MMI_vAllHistoryStateRestoreToDef(void);
static void MMI_vSysHistoryStateRestore(void);
static void MMI_vBctlHistoryStateRestore(void);
static void MMI_vAirdHistoryStateRestore(void);
static void MMI_vAcccHistoryStateRestore(void);
static void MMI_vRfaHistoryStateRestore(void);
static void MMI_vAqsHistoryStateRestore(void);
static void MMI_vIonHistoryStateRestore(void);
//static void MMI_vGetModuleAutoState(void);
//static uint8 MMI_u8BusKeyStateValid(uint16 u16KeySt); /*by zsc,160521*/
static void MMI_vWriteMemData(void);
static MMI_tenRfaCtrl MMI_vChangeAqsState(uint8 u8Rfa);
static void MMI_vTriggerEventIonLongPress(void);
static void MMI_vSysStoreStateChangeToManual(void);
static void MMI_vVehicleConfig(void);
/******************************************************************************/


/* ***********LOCAL_FUNCTIONS_END******************************************** */ 

/* ***********RESPONSE FUNCTIONS TABLE*************************************** */ 
/* *** Will be updated this table according to project                    *** */ 

#if(SYC_ZONES == 1)

const MMI_tstKeyAction MMI_axActionTableSingleZone [MMI_nMaxKeys] =
{
	&MMI_vTriggerEventAuto    	 ,
	&MMI_vTriggerEventAc	   		 ,
	&MMI_vTriggerEventRecAndFre,
	&MMI_vTriggerEventDefrost      ,
	&MMI_vTriggerEventModeL	     ,
	&MMI_vTriggerEventModeR 	 ,
	&MMI_vTriggerEventShl 	 ,
	&MMI_vTriggerEventShr ,
	&MMI_vTriggerEventMaxAc,
	&MMI_vTriggerEventRearDefrost  ,
	&MMI_vTriggerEventOff 	 ,
	&MMI_vTriggerEventIon,		
	&MMI_vTriggerEventIonLongPress		
};
#elif(SYC_ZONES == 2)
const MMI_tstKeyAction MMI_axActionTableDualZone [MMI_nMaxKeys] =
{
	&MMI_vTriggerEventShr     	,
	&MMI_vTriggerEventShl	   		,
	&MMI_vTriggerEventOff		,
	&MMI_vTriggerEventRecAndFre		,
	&MMI_vTriggerEventDefrost   	 ,
	&MMI_vTriggerEventRearDefrost	   		,
	&MMI_vTriggerEventMode			,
	&MMI_vTriggerEventBlwDec			,
	&MMI_vTriggerEventAuto			,
	&MMI_vTriggerEventAc      	,
	&MMI_vTriggerEventIon    			,
	&MMI_vTriggerEventBlwInc			,
	&MMI_vTriggerEventDual			,
	&MMI_vTriggerEventMaxAc			,
	&MMI_vTriggerEventAqs			,
	&MMI_vTriggerEventPM25			,
};

#endif

#ifdef Used_Knob

const MMI_tstKeyAction MMI_axActionTableKnobDualZone[MMI_nKnobNumber] =
{
	&MMI_vTriggerEventTempDrInc			  ,
	&MMI_vTriggerEventTempDrDec			  ,
	&MMI_vTriggerEventTempPsInc                ,
	&MMI_vTriggerEventTempPsDec
};

#endif

#ifdef Virtual_Key
const MMI_tstKeyAction MMI_axVkeyActionTableSingleZone [MMI_u8VKkeyMax] =
{
	&MMI_vTriggerEventMmiSetTempDr    		,    //FL SET TEMP
	&MMI_vTriggerEventMmiSetTempPs          ,
	&MMI_vTriggerEventMmiFan		,   //BCTL SPEED
	&MMI_vTriggerEventMmiAird		,   //MODE
	&MMI_vTriggerEventMmiPM25PopupOperationSts ,
	&MMI_vTriggerEventMmiDrvHeat    ,
	&MMI_vTriggerEventMmiPassHeat   ,
	&MMI_vTriggerEventMmiPM25PopupActive   ,
	&MMI_vTriggerEventTboxAirCleanerReq		,   //MODE
	&MMI_vTriggerEventTboxTempReq ,
	&MMI_vTriggerEventTboxAirConditionerReq 
};
#endif


#ifdef Used_RearPanel

const MMI_tstKeyAction MMI_axActionTableRearCtrl [10U] =
{
	&MMI_vTriggerEventNotUsed   	    	,
	&MMI_vTriggerEventMaxAc			,
	&MMI_vTriggerEventAc    			,
	&MMI_vTriggerEventMode	    		,
	&MMI_vTriggerEventIon				,
	&MMI_vTriggerEventRearBlwInc		,
	&MMI_vTriggerEventRearBlwDec		,
	&MMI_vTriggerEventTempRearUp			  ,
	&MMI_vTriggerEventTempRearDn			  ,	
	#if RearLocK_Enable
	&MMI_vTriggerEventAuto,	
	#else
	&MMI_vTriggerEventNotUsed,
	#endif
};
#endif

/* ***********TABLE_END****************************************************** */ 

/* ===========================================================================
* Function   : void MMI_vReset (void)
* Description: Reset function for MMI
*              Initialises all variables to safe state
*              Called on Battery->On
* Takes      : Nothing
* Returns    : Nothing
*/
void MMI_vReset (void)
{	
	
	MMI_u8SwVersion = MMI_SW_VERSION;
	MMI_u16ErrorCode = MMI_NoError;
	MMI_vReadMemData();
    MMI_u8ShlCtrl = 0u;
    MMI_u8ShrCtrl = 0u;
    MMI_u8ShlFromeBusCtrl = 0u;
    MMI_u8ShrFromeBusCtrl = 0u;
    MMI_u8RearDefCtrl = 0u;

    MMI_u8Pm25Enable = True;
    MMI_u8Pm25PopActive = False;
	//MMI_vAllHistoryStateStore();/*delete by zsc,160523*/
	
}


static void MMI_vReadMemData(void)
{
	uint8 u8Return =0;
	//u8Return = Rte_Call_Mmi_ReadEep_HmiState_EedRead(&MMI_tstStateStore,sizeof(MMI_tstStateStore));
    u8Return = Rte_Call_IoHwEep_IoHwEedProto_ReadEep_MmiState_EedRead((uint8*)&MMI_Save,sizeof(MMI_Save));
	//MMI_u8SwVersion = u8Return;
    if(u8Return==0/*Read No Error*/)
    {
		MMI_vAllHistoryStateRestoreAfterReset();/*by zsc,160523*/
    }
    else/*Read Error*/
    {
		MMI_vResetDefaultValue();		
    }
	//MMI_vAllHistoryStateStore(); 160719
}


static void MMI_vWriteMemData(void)
{
	uint8 u8Return =0;
	//u8Return = Rte_Call_Mmi_WriteEep_HmiState_EedWrite(&MMI_tstStateStore,sizeof(MMI_tstStateStore));
    u8Return = Rte_Call_IoHwEep_IoHwEedProto_WriteEep_MmiState_EedWrite((uint8*)&MMI_Save,sizeof(MMI_Save));
	if(u8Return==0/*Read No Error*/) /*160523*/
 	{
		MMI_boNeedSaveData = False;
 	}
}


static void MMI_vResetDefaultValue(void)
{
	MMI_u8SysState = MMI_nSysStateAuto;
	
	MMI_tstBctl.u8State = MMI_nBctlStateAuto;
	MMI_tstBctl.u8Ctrl = MMI_nBctlSpeed5;
	
	MMI_tstAird.u8State = MMI_nAirdStateAuto;
	MMI_tstAird.u8Ctrl = MMI_nAirdFace;
	
	MMI_tstAccc.u8State = MMI_nAcStateAuto;
	MMI_tstAccc.u8Ctrl = MMI_nAcOff;
	
	MMI_tstRfa.u8State = MMI_nRfaStateAuto;
	MMI_tstRfa.u8Ctrl = MMI_nRfaFresh;

	MMI_au8Array[MMI_nu8IonMode] = MMI_nIonStateOff;
	MMI_au8Array[MMI_nu8IonCtrl] = MMI_nIonStandby;

	//MMI_au8Array[MMI_nu8AqsRequest]     = MMI_nAQSOn;
    MMI_tstAqs.u8Ctrl     = MMI_nAQSOn;
    MMI_tstAqs.u8State = MMI_nAqsStateAuto;
	
	MMI_u8DualCtrl = MMI_nDualOff;
	
	MMI_u8SetTempDr = MMI_u8SetTempInitValue;	
	MMI_u8SetTempPs = MMI_u8SetTempInitValue;
	

}


/* ===========================================================================
* Function   : void MMI_vDeInit (void)
* Description: Deinit function of MMI
			   Called at ignition off (On -> Active)
* Takes      : Nothing
* Returns    : Nothing
*/
void MMI_vDeinit (void)
{
	MMI_u16ErrorCode = MMI_NoError;

	/* ***********Save data in EEPROM**************************************** */ 
	if(MMI_boNeedSaveData == True)
	{
		MMI_vUpdateSaveBuffer();
		MMI_u8StateSaveTiming=0;
		MMI_vWriteMemData(); 
	}
}


/* ===========================================================================
* Function   : void MMI_vInit (void)
* Description: Initialisation function of MMI
*              Called at ignition on (ActionActiveOn)
*              Makes sure all of the data and setpoints are valid.
* Takes      : Nothing
* Returns    : Nothing
*/
void MMI_vInit (void)
{
	MMI_u16ErrorCode = MMI_NoError;
	MMI_boNeedSaveData = False;
	MMI_u8StateSaveTiming=0;
    MMI_u8ShlCtrl = 0u;
    MMI_u8ShrCtrl = 0u;
    MMI_u8ShlFromeBusCtrl = 0u;
    MMI_u8ShrFromeBusCtrl = 0u;
    MMI_u8RearDefCtrl = 0u;
    MMI_u8Pm25PopupOperationSts = True;
	MMI_u8Pm25Enable = True;
	MMI_u8Pm25PopActive = False;
    MMI_u8OperationAfterTurnOn=False;
	MMI_au8Array[MMI_nu8IonMode] = MMI_nIonStateOff;
	MMI_au8Array[MMI_nu8IonCtrl] = MMI_nIonStandby;
    MMI_u8TurnOnByPm25=False;
    MMI_u16KnobOrKeyOperationFlag = 0u;
    MMI_u8Pm25PopupKeepTime = 0;
}

/* ===========================================================================
* Function   : void MMI_vInit (void)
* Description: Initialisation function of MMI
*              Called at ignition on (ActionActiveOn)
*              Makes sure all of the data and setpoints are valid.
* Takes      : Nothing
* Returns    : Nothing
*/
void MMI_vActive(void)
{
	MMI_u16ErrorCode = MMI_NoError;
	MMI_boNeedSaveData = False;
	MMI_u8StateSaveTiming=0;
}
/* ===========================================================================
* Function   : void MMI_vMain (void)
* Description: Main container function of MMI
* Takes      : Nothing
* Returns    : Nothing
*/
 void MMI_vMain (void)
{
	uint8 sbiLowVoltage = 0;
	uint8 sbiHighVoltage = 0;

	sbiLowVoltage = MMI_u8GetPowLowVolFlag;
	sbiHighVoltage = MMI_u8GetPowHighVolFlag;
	
	if(( sbiLowVoltage	== False)&&( sbiHighVoltage == False) )
	{
		/* ***********konb process*************************************************/
		#ifdef Used_Knob
		MMI_vKonbMain();
		#endif
		/* ***********key process**************************************************/		
		MMI_vKeyMain();
    #ifdef Virtual_Key
		/* ***********Vkey process**************************************************/		
		MMI_vVKeyMain();
    #endif
		//MMI_vGetModuleAutoState();	/*ITP47,add by zsc, close at 160504*/
		MMI_vDoDisplayMain();/*ITP50,add by zsc*/
		
		MMI_vPutValueInterFace();

        MMI_vVehicleConfig();
        
		/*CR  MMI feedback the popupactive time*/
		if (MMI_u8Pm25PopupKeepTime > 0)
		{
			MMI_u8Pm25PopupKeepTime--;
		}
		else
		{
			MMI_u8Pm25PopActive = False;
		}
		/* ***********Save data in EEPROM**************************************** */ 
		if(MMI_boNeedSaveData == True)
		{
			MMI_vUpdateSaveBuffer();
			MMI_u8StateSaveTiming++;
			if(MMI_u8StateSaveTiming >= MMI_SaveDelayTime) /*add save time,byzsc,160523*/
			{
				MMI_u8StateSaveTiming=0;
				MMI_vWriteMemData(); 
			}
		}
	}
	MMI_vPutValue2Rte();


}


/* ===========================================================================
* Function   : void MMI_vDoDisplayMain (void)
* Description: Processing the display info
* Takes      : Nothing
* Returns    : Nothing
*/
void MMI_vDoDisplayMain(void)
{
	uint8 u8BctlDispInfo = 0U;
	uint8 u8AirdDispInfo = 0U;
	uint8 u8RearDefrost = 0U;
	uint8 u8AcDispInfo = 0U;
	uint8 u8RfaDispInfo = 0U;
    //uint8 u8IonNeedReplaceFilter = 0U;
       uint8 u8SeatHeatDispInfoDr = 0U;
	uint8 u8SeatHeatDispInfoPs = 0U;
	
	u8RfaDispInfo = MMI_u8GetRfaDisplayInfo;
	u8BctlDispInfo = MMI_u8GetBctlDisplayInfo;
	u8AirdDispInfo = MMI_u8GetAirdDisplayInfo;
	u8RearDefrost = MMI_u8GetRdcValue();
	//u8RearDefrost = (uint8)CANAPP_u16GetValue(CANAPP_nu16BCM_DefrosterSts);
	u8AcDispInfo = MMI_u8GetAcccDisplayInfo;//ACCC_u8GetValue(ACCC_nu8AcDisplay);//MMI_u8AcccDisplayInfo ;
	//u8IonNeedReplaceFilter = MMI_u8GetIonFilterState();
	u8SeatHeatDispInfoDr = MMI_u8GetShcLDisplayInfo();
	u8SeatHeatDispInfoPs = MMI_u8GetShcRDisplayInfo();
	/***** Get the auto running control from app modules calculated results****/
	if(MMI_tstBctl.u8State == MMI_nBctlStateAuto)
	{
		MMI_tstBctl.u8Ctrl= u8BctlDispInfo;
	}

	if(MMI_tstAird.u8State == MMI_nAirdStateAuto)
	{
		MMI_tstAird.u8Ctrl = u8AirdDispInfo;
	}

	if(MMI_tstAccc.u8State == MMI_nAcStateAuto)
	{
		MMI_tstAccc.u8Ctrl = u8AcDispInfo;
	}

	if(MMI_tstRfa.u8State == MMI_nRfaStateAuto)
	{
		MMI_tstRfa.u8Ctrl = u8RfaDispInfo;
	}
	
	//MMI_u8RearDefCtrl = u8RearDefrost;*/

	/***** Processing the LCD diaplay & Indicators logic*******************************/
	MMI_nDispInfoClearAll();
	MMI_nIndicatorInfoClearAll();

	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_nBackLightFlag(FALSE);
			MMI_nDispOffFlag(True);
			MMI_nDispAutoSymbol(BLANK);
			MMI_nAutoIndicator(BLANK);
			MMI_nDispTempFlag(FALSE);
			MMI_nDispDefSymbol(BLANK);
			MMI_nDefIndicator(BLANK);
			MMI_nDispMaxAcSymbol(BLANK);
			MMI_nMaxAcIndicator(BLANK);
			break;
		case MMI_nSysStateManual:
			MMI_nBackLightFlag(True);
			MMI_nDispOffFlag(FALSE);
			MMI_nDispAutoSymbol(BLANK);
			MMI_nAutoIndicator(BLANK);
			MMI_nDispTempFlag(TRUE);
			MMI_nDispDefSymbol(BLANK);
			MMI_nDefIndicator(BLANK);
			MMI_nDispMaxAcSymbol(BLANK);
			MMI_nMaxAcIndicator(BLANK);
			break;
		case MMI_nSysStateAuto:
			MMI_nBackLightFlag(True);
			MMI_nDispOffFlag(FALSE);
			MMI_nDispAutoSymbol(DISPLAY);
			MMI_nAutoIndicator(DISPLAY);
			MMI_nDispTempFlag(TRUE);
			MMI_nDispDefSymbol(BLANK);
			MMI_nDefIndicator(BLANK);
			MMI_nDispMaxAcSymbol(BLANK);
			MMI_nMaxAcIndicator(BLANK);
			break;
		case MMI_nSysStateDefrost:
			MMI_nBackLightFlag(True);
			MMI_nDispOffFlag(FALSE);
			MMI_nDispAutoSymbol(BLANK);
			MMI_nAutoIndicator(BLANK);
			MMI_nDispDefSymbol(DISPLAY);
			MMI_nDefIndicator(DISPLAY);
			MMI_nDispTempFlag(TRUE);
			MMI_nDispMaxAcSymbol(BLANK);
			MMI_nMaxAcIndicator(BLANK);
			break;
		case MMI_nSysStateMaxAc:
			MMI_nBackLightFlag(True);
			MMI_nDispOffFlag(FALSE);
			MMI_nDispAutoSymbol(BLANK);
			MMI_nAutoIndicator(BLANK);
			MMI_nDispTempFlag(TRUE);
			MMI_nDispDefSymbol(BLANK);
			MMI_nDefIndicator(BLANK);
			MMI_nDispMaxAcSymbol(DISPLAY);
			MMI_nMaxAcIndicator(DISPLAY);
			break;
		default :
			break;
	}

	if(MMI_tstBctl.u8State == MMI_nBctlStateOff)
	{
		MMI_nDispBctlFlag(FALSE);
	}
	else
	{
		MMI_nDispBctlFlag(TRUE);
	}

	if(MMI_tstAird.u8State == MMI_nAirdStateOff)
	{
		MMI_nDispAirdFlag(FALSE);
	}
	else
	{
		MMI_nDispAirdFlag(TRUE);
	}

	if(MMI_u8SysState == MMI_nSysStateOff)
	{
		MMI_nDispRecFlag(FALSE);
	}
	else
	{
		MMI_nDispRecFlag(TRUE);
	}
    
	if(MMI_u8DualCtrl == MMI_nDualOn)
	{
		MMI_nDispDualSymbol(DISPLAY);
		MMI_nDualIndicator(DISPLAY);
	}
	else
	{
		MMI_nDispDualSymbol(BLANK);
		MMI_nDualIndicator(BLANK);
	}

	switch(MMI_tstAccc.u8Ctrl)
	{
		case MMI_nAcOff:
			MMI_nDispAcSymbol(BLANK);
			MMI_nDispEconSymbol(BLANK);
			MMI_nAcIndicator(BLANK);
			break;
		case MMI_nAcOn:
			MMI_nDispAcSymbol(DISPLAY);
			MMI_nDispEconSymbol(BLANK);
			MMI_nAcIndicator(DISPLAY);
			break;
		case MMI_nAcEcon:
			MMI_nDispAcSymbol(DISPLAY);
			MMI_nDispEconSymbol(DISPLAY);
			MMI_nAcIndicator(DISPLAY);
			break;
		default :
			MMI_nDispAcSymbol(BLANK);
			MMI_nDispEconSymbol(BLANK);
			MMI_nAcIndicator(BLANK);
			break;			
	}

	switch(MMI_tstRfa.u8Ctrl)
	{
		case MMI_nRfaFresh:
			MMI_nDispFreshSymbol(DISPLAY);
			MMI_nDispRecSymbol(BLANK);
			MMI_nFreshIndicator(DISPLAY);
			MMI_nRecIndicator(BLANK);
			break;
		case MMI_nRfaRecirc:
			MMI_nDispFreshSymbol(BLANK);
			MMI_nDispRecSymbol(DISPLAY);
			MMI_nFreshIndicator(BLANK);
			MMI_nRecIndicator(DISPLAY);
			break;
		default:
			MMI_nDispFreshSymbol(BLANK);
			MMI_nDispRecSymbol(BLANK);
			MMI_nFreshIndicator(BLANK);
			MMI_nRecIndicator(BLANK);
			break;	
	}

    if(MMI_u8AqsState == MMI_nAQSOn)
    {
        MMI_nDispAqsSymbol(DISPLAY);
    }
    else
    {
        MMI_nDispAqsSymbol(BLANK);
    }
	//#if 0
	if(u8RearDefrost == MMI_nRearDefOn)
	{
		MMI_nDispRearDefSymbol(DISPLAY);
		MMI_nRearDefIndicator(DISPLAY);
	}
	else
	{
		MMI_nDispRearDefSymbol(BLANK);
		MMI_nRearDefIndicator(BLANK);
	}
	//#endif

    //if(u8IonNeedReplaceFilter == True)
    //{/*Filter need to replace*/
        //MMI_u8IonNeedReplaceFilter = True;
    //}
    //else
    //{
        //MMI_u8IonNeedReplaceFilter = False;
    //}

    if(MMI_u8IonCtrl != MMI_nIonStandby)
    {
        MMI_nIonIndicator(DISPLAY);
    }
    else
    {
        MMI_nIonIndicator(BLANK);
    }
    
    if(u8RearDefrost == True)
    {
        MMI_nRearDefIndicator(DISPLAY);
    }
    else
    {
        MMI_nRearDefIndicator(BLANK);
    }

    if(u8SeatHeatDispInfoPs == True)
    {
        MMI_nShcRIndicator(DISPLAY);
    }
    else
    {
        MMI_nShcRIndicator(BLANK);
    }
    if(u8SeatHeatDispInfoDr == True)
    {
        MMI_nShcLIndicator(DISPLAY);
    }
    else
    {
        MMI_nShcLIndicator(BLANK);
    }
	MMI_u16LcdDispInfo1 = (uint16)MMI_nLcdInfo1;
	MMI_u16LcdDispInfo2 = (uint16)MMI_nLcdInfo2;
	
	MMI_u16IndiInfo1 = (uint16)MMI_nIndiInfo1;
    MMI_u16IndiInfo2 = (uint16)MMI_nIndiInfo2;

}


/* ===========================================================================
* Function   : void MMI_vKeyMain (void)
* Description: Processing the KEY trigger event
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vKeyMain(void)
{
	tFuncPtr vfpTheAction = (tFuncPtr)NULL ;/*Pointer to the action function.*/
	uint16 u16KeyPressed=0;
    uint16 u16PhyKeyPressFlag=0;
	
	u16KeyPressed = MMI_u16GetKeyKeyPressed;
    u16PhyKeyPressFlag = (uint16)KEY_vKeyGetPhyKeyPressAction();

	for(uint16 i=0U;i<MMI_nMaxKeys;i++)
	{
		if(u16KeyPressed&(1<<i))
		{
			MMI_boNeedSaveData = True;
			MMI_u8StateSaveTiming=0;
            MMI_u8OperationAfterTurnOn = True;
			if(i != (2)) /*not off press*/
			{
				MMI_u8TurnOnByPm25 = False;/*180426*/
			}
			#if (SYC_ZONES == 1)
			vfpTheAction = MMI_axActionTableSingleZone[i];
			#else
			vfpTheAction = MMI_axActionTableDualZone[i];
			#endif			
			vfpTheAction();
		}
	}
    
    if(u16KeyPressed & u16PhyKeyPressFlag)
    {
        MMI_u16KnobOrKeyOperationFlag |= 2u;
        KEY_vKeyClearPhyKeyFalg();
    }
    else
    {
        MMI_u16KnobOrKeyOperationFlag &= ~2u;
    }
}


/* ===========================================================================
* Function   : void MMI_vKonbMain (void)
* Description: Processing the Knob trigger event
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vKonbMain(void)
{
    uint16 u16KnobOperation = 0u;
#ifdef Used_Knob	
	tFuncPtr vfpTheAction = (tFuncPtr)NULL ;/*Pointer to the action function.*/
	uint8 u8KnobStatus = 0;

/*******left temperature knob***************************************************/	
	u8KnobStatus = (uint8)MMI_u8GetKnobValue(Knob_enTempLRotaryOperate);
	if (( u8KnobStatus != KNOB_nNoRot) &&  ( u8KnobStatus < KNOB_nNumber ))
	{	
		MMI_boNeedSaveData = True;
        MMI_u8OperationAfterTurnOn = True;
        u16KnobOperation = True;
		vfpTheAction =(tFuncPtr) MMI_axActionTableKnobDualZone[u8KnobStatus-1];
		vfpTheAction();
	}
/*******Blower knob**************************************************/
	u8KnobStatus = (uint8)MMI_u8GetKnobValue(Knob_enTempRRotaryOperate);
	if (( u8KnobStatus != KNOB_nNoRot) && ( u8KnobStatus < KNOB_nNumber ))
	{
		MMI_boNeedSaveData = True;
        MMI_u8OperationAfterTurnOn = True;
        u16KnobOperation = True;
		vfpTheAction = (tFuncPtr)MMI_axActionTableKnobDualZone[u8KnobStatus-1+2];
		vfpTheAction();
	}

    if(u16KnobOperation)
    {
        MMI_u16KnobOrKeyOperationFlag |= 1u;
    }
    else
    {
        MMI_u16KnobOrKeyOperationFlag &= ~1u;
    }
#endif
}

#ifdef Virtual_Key
/* ===========================================================================
* Function   : MMI_vVKeyMain
* Description: Main container function of MMI
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vVKeyMain (void)
{
	tFuncPtr vfpTheAction = (tFuncPtr)NULL ;/*Pointer to the action function.*/
	uint16 u16VKeyPressed;

	u16VKeyPressed = MMI_u16GetVkeyPressed;
	for(uint16 i=0U;i<MMI_u8VKkeyMax;i++)
	{
		if(u16VKeyPressed&(1<<i))
		{
			 MMI_boNeedSaveData = True;
			 MMI_u8StateSaveTiming=0;
         	       MMI_u8OperationAfterTurnOn = True;
                    MMI_u8TurnOnByPm25 =False;/*180426*/
			vfpTheAction = MMI_axVkeyActionTableSingleZone[i];
			vfpTheAction();
		}
	}
}
#endif

static void MMI_vPutValueInterFace(void)
{
	//MMI_au8Array[MMI_nu8IonState] = enIonState;
	//MMI_au8Array[MMI_nu8IonCtrl] = enIonCtrl;
	/***MMI Bctl output*/
	if((MMI_tstBctl.u8State==MMI_nBctlStateDefManu)
		||(MMI_tstBctl.u8State==MMI_nBctlStateMaxAcManu))
	{
		MMI_u8BctlState= MMI_nBctlStateManual;
	}
	else
	{
		MMI_u8BctlState = MMI_tstBctl.u8State;
	}
	
	MMI_u8BctlCtrl= MMI_tstBctl.u8Ctrl;
	
	/***MMI Aird output*/
	MMI_u8AirdState = MMI_tstAird.u8State;
	MMI_u8AirdCtrl = MMI_tstAird.u8Ctrl;
	
	/***MMI Accc output*/
	if((MMI_tstAccc.u8State ==MMI_nAcStateDefManu)
		||(MMI_tstAccc.u8State==MMI_nAcStateMaxAcManu))
	{
		MMI_u8AcState = MMI_nAcStateManual;
	}
	else
	{
		MMI_u8AcState = MMI_tstAccc.u8State;
	}
	MMI_u8AcCtrl = MMI_tstAccc.u8Ctrl;
	
	/***MMI Rfa output*/
	if((MMI_tstRfa.u8State == MMI_nRfaStateDefManu)
		||(MMI_tstRfa.u8State == MMI_nRfaStateMaxAcManu))
	{
		MMI_u8RfaState = MMI_nRfaStateManual;
	}
	else
	{
		MMI_u8RfaState = MMI_tstRfa.u8State;
	}
	MMI_u8RfaCtrl = MMI_tstRfa.u8Ctrl;
    MMI_u8AqsState = MMI_tstAqs.u8Ctrl;

}


static void MMI_vPutValue2Rte(void)
{
#if 0
	MMI_u8Put2RteSysState(MMI_u8SysState);
	MMI_u8Put2RteSetTempPs(MMI_u8SetTempPs);
	MMI_u8Put2RteSetTempDr(MMI_u8SetTempDr);
	MMI_u8Put2RteBctlState(MMI_u8BctlState);
	MMI_u8Put2RteBctlCtrl(MMI_u8BctlCtrl);
	MMI_u8Put2RteAirdState(MMI_u8AirdState);
	MMI_u8Put2RteAirdCtrl(MMI_u8AirdCtrl);
	MMI_u8Put2RteAcState(MMI_u8AcState);
	MMI_u8Put2RteAcCtrl(MMI_u8AcCtrl);
	MMI_u8Put2RteRfaState(MMI_u8RfaState);
	MMI_u8Put2RteRfaCtrl(MMI_u8RfaCtrl);
	MMI_u8Put2RteDualCtrl(MMI_u8DualCtrl);
    MMI_u8Put2RteIonMode(MMI_u8IonState);
    MMI_u8Put2RteIonCtrl(MMI_u8IonCtrl);
    MMI_u8Put2RteAqsCtrl(MMI_u8AqsState);
    MMI_u16Put2RteLed1Info(MMI_u16IndiInfo1);
    MMI_u16Put2RteLed2Info(MMI_u16IndiInfo2);
#endif
}

/*
static void MMI_vUpdateAllStatesByBuffer(void)
{

}
*/

static void MMI_vUpdateSaveBuffer(void)
{
	//memcpy(&MMI_Save.MMI_u8SaveAC.MMI_stCurrentStatus.mode, &MMI_tstAccc, 2);

	/*ACCC*/
	MMI_Save.MMI_u8SaveAC.MMI_stCurrentStatus.mode = MMI_tstAccc.u8State;
	MMI_Save.MMI_u8SaveAC.MMI_stCurrentStatus.controlsts = MMI_tstAccc.u8Ctrl;
	MMI_Save.MMI_u8SaveAC.MMI_stOFFpreStatus.mode = MMI_tstStateStore.nAcccState;
	MMI_Save.MMI_u8SaveAC.MMI_stOFFpreStatus.controlsts = MMI_tstStateStore.nAcccCtrl;
	/*AIRD*/
	MMI_Save.MMI_u8SaveAird.MMI_stCurrentStatus.mode = MMI_tstAird.u8State;
	MMI_Save.MMI_u8SaveAird.MMI_stCurrentStatus.controlsts = MMI_tstAird.u8Ctrl;
	MMI_Save.MMI_u8SaveAird.MMI_stOFFpreStatus.mode = MMI_tstStateStore.nAirdState;
	MMI_Save.MMI_u8SaveAird.MMI_stOFFpreStatus.controlsts = MMI_tstStateStore.nAirdCtrl;
	/*BCTL*/
	MMI_Save.MMI_u8SaveBCTL.MMI_stCurrentStatus.mode = MMI_tstBctl.u8State;
	MMI_Save.MMI_u8SaveBCTL.MMI_stCurrentStatus.controlsts = MMI_tstBctl.u8Ctrl;
	MMI_Save.MMI_u8SaveBCTL.MMI_stOFFpreStatus.mode = MMI_tstStateStore.nBctlState;
	MMI_Save.MMI_u8SaveBCTL.MMI_stOFFpreStatus.controlsts = MMI_tstStateStore.nBctlSpd;
	/*RFA*/
	MMI_Save.MMI_u8SaveRFA.MMI_stCurrentStatus.mode = MMI_tstRfa.u8State;
	MMI_Save.MMI_u8SaveRFA.MMI_stCurrentStatus.controlsts = MMI_tstRfa.u8Ctrl;
	MMI_Save.MMI_u8SaveRFA.MMI_stOFFpreStatus.mode = MMI_tstStateStore.nRfaState;
	MMI_Save.MMI_u8SaveRFA.MMI_stOFFpreStatus.controlsts = MMI_tstStateStore.nRfaCtrl;
	/*sys mode*/
	MMI_Save.MMI_u8SaveMode.MMI_stCurrentStatus.mode = MMI_u8SysState;
	MMI_Save.MMI_u8SaveMode.MMI_stCurrentStatus.controlsts = MMI_u8SysState;
	MMI_Save.MMI_u8SaveMode.MMI_stOFFpreStatus.mode = MMI_tstStateStore.nSystemState;
	MMI_Save.MMI_u8SaveMode.MMI_stOFFpreStatus.controlsts = MMI_tstStateStore.nSystemState;

	/*ION*/
	MMI_Save.MMI_u8SaveION.MMI_stCurrentStatus.mode = MMI_au8Array[MMI_nu8IonMode];
	MMI_Save.MMI_u8SaveION.MMI_stCurrentStatus.controlsts = MMI_au8Array[MMI_nu8IonCtrl];
	MMI_Save.MMI_u8SaveION.MMI_stOFFpreStatus.mode = MMI_au8Array[MMI_nu8IonMode];
	MMI_Save.MMI_u8SaveION.MMI_stOFFpreStatus.controlsts = MMI_au8Array[MMI_nu8IonCtrl];
	
	/*Dual*/
	MMI_Save.MMI_u8SaveDual.CurrentStatus = MMI_u8DualCtrl; //MMI_u8SysState;160814
	MMI_Save.MMI_u8SaveDual.OFFpreStatus = MMI_tstStateStore.nDualCtrl;//nSystemState; 160814
	//MMI_Save.MMI_u8SaveDual.DEFpreStatus = MMI_tstStateStore.nSystemState;

	/*Set Temp*/
	MMI_Save.MMI_u8SaveSetTempDr.CurrentStatus = MMI_u8SetTempDr;
	MMI_Save.MMI_u8SaveSetTempDr.OFFpreStatus = MMI_tstStateStore.nSetTempL;

	MMI_Save.MMI_u8SaveSetTempPs.CurrentStatus = MMI_u8SetTempPs;
	MMI_Save.MMI_u8SaveSetTempPs.OFFpreStatus = MMI_tstStateStore.nSetTempR;
	//MMI_Save.MMI_u8SaveDual.DEFpreStatus = MMI_tstStateStore.nSystemState;

    /*Aqs*/
	/*RFA*/
	MMI_Save.MMI_u8SaveAqs.MMI_stCurrentStatus.mode = MMI_tstAqs.u8State;
	MMI_Save.MMI_u8SaveAqs.MMI_stCurrentStatus.controlsts = MMI_tstAqs.u8Ctrl;
	MMI_Save.MMI_u8SaveAqs.MMI_stOFFpreStatus.mode = MMI_tstStateStore.nAqsState;
	MMI_Save.MMI_u8SaveAqs.MMI_stOFFpreStatus.controlsts = MMI_tstStateStore.nAqsCtrl;
}


static void MMI_vAllHistoryStateStore(void)
{
	MMI_vSysHistoryStateStore();
	MMI_vBctlHistoryStateStore();
	MMI_vAirdHistoryStateStore();
	MMI_vAcccHistoryStateStore();
	MMI_vRfaHistoryStateStore();
    MMI_vAqsHistoryStateStore();
    MMI_vIonHistoryStateStore();
}

static void MMI_vSysHistoryStateStore(void)
{ 
	MMI_tstStateStore.nSystemState = MMI_u8SysState;
	MMI_tstStateStore.nDualCtrl = MMI_u8DualCtrl;
	MMI_tstStateStore.nSetTempL = MMI_u8SetTempDr;
	MMI_tstStateStore.nSetTempR = MMI_u8SetTempPs;

}

static void MMI_vSetTempHistoryStateStore(void)
{ 
	MMI_tstStateStore.nSetTempL = MMI_u8SetTempDr;
	MMI_tstStateStore.nSetTempR = MMI_u8SetTempPs;

}
static void MMI_vBctlHistoryStateStore(void)
{
	if((MMI_tstBctl.u8State != MMI_nBctlStateDefrost)&&(MMI_tstBctl.u8State != MMI_nBctlStateMaxAc))
	{/*Do not store states in def or maxAc, because they are special state*/
		MMI_tstStateStore.nBctlState=MMI_tstBctl.u8State;
		MMI_tstStateStore.nBctlSpd=MMI_tstBctl.u8Ctrl;
	}
}

static void MMI_vAirdHistoryStateStore(void)
{
	if((MMI_tstAird.u8State!=MMI_nAirdStateDefrost)&&(MMI_tstAird.u8State!=MMI_nAirdStateMaxAc))
	{/*Do not store states in def or maxAc, because they are special state*/
		MMI_tstStateStore.nAirdState=MMI_tstAird.u8State;
		MMI_tstStateStore.nAirdCtrl=MMI_tstAird.u8Ctrl;
	}
}

static void MMI_vAcccHistoryStateStore(void)
{
	if((MMI_tstAccc.u8State!=MMI_nAcStateDefrost)&&(MMI_tstAccc.u8State!=MMI_nAcStateMaxAc))
	{/*Do not store states in def or maxAc, because they are special state*/
		MMI_tstStateStore.nAcccState=MMI_tstAccc.u8State;
		MMI_tstStateStore.nAcccCtrl=MMI_tstAccc.u8Ctrl;
	}
}

static void MMI_vRfaHistoryStateStore(void)
{
	if((MMI_tstRfa.u8State!=MMI_nRfaStateDefrost)&&(MMI_tstRfa.u8State!=MMI_nRfaStateMaxAc))
	{/*Do not store states in def or maxAc, because they are special state*/
		MMI_tstStateStore.nRfaState=MMI_tstRfa.u8State;
		MMI_tstStateStore.nRfaCtrl=MMI_tstRfa.u8Ctrl;
	}
}

static void MMI_vAqsHistoryStateStore(void)
{
	if((MMI_tstAqs.u8State!=MMI_nAqsStateDefrost)&&(MMI_tstAqs.u8State!=MMI_nAqsStateMaxAc))
	{/*Do not store states in def or maxAc, because they are special state*/
		MMI_tstStateStore.nAqsState=MMI_tstAqs.u8State;
		MMI_tstStateStore.nAqsCtrl=MMI_tstAqs.u8Ctrl;
	}
}

static void MMI_vIonHistoryStateStore(void)
{
	if((MMI_tstIon.u8State!=MMI_nIonStateDefrost)&&(MMI_tstIon.u8State!=MMI_nIonStateMaxAc))
	{/*Do not store states in def or maxAc, because they are special state*/
		MMI_tstStateStore.nIonState=MMI_tstIon.u8State;
		MMI_tstStateStore.nIonCtrl=MMI_tstIon.u8Ctrl;
	}
}
/******************************************************************************/ 
static void MMI_vAllHistoryStateRestore(void)
{
	if((MMI_u8SysState==MMI_nSysStateDefrost)
		||(MMI_u8SysState==MMI_nSysStateMaxAc)
		||(MMI_u8SysState==MMI_nSysStateOff)
		)
	{
		MMI_vSysHistoryStateRestore();
		MMI_vBctlHistoryStateRestore();
		MMI_vAirdHistoryStateRestore();
		MMI_vAcccHistoryStateRestore();
		MMI_vRfaHistoryStateRestore();
        MMI_vAqsHistoryStateRestore();
        MMI_vIonHistoryStateRestore();
	}
}



/******************************************************************************/ 
static void MMI_vAllHistoryStateRestoreAfterReset(void)
{
	/*ACCC*/
	MMI_tstAccc.u8State = MMI_Save.MMI_u8SaveAC.MMI_stCurrentStatus.mode;
	MMI_tstAccc.u8Ctrl = MMI_Save.MMI_u8SaveAC.MMI_stCurrentStatus.controlsts;
	MMI_tstStateStore.nAcccState = MMI_Save.MMI_u8SaveAC.MMI_stOFFpreStatus.mode;
	MMI_tstStateStore.nAcccCtrl = MMI_Save.MMI_u8SaveAC.MMI_stOFFpreStatus.controlsts;
	/*AIRD*/
	MMI_tstAird.u8State = MMI_Save.MMI_u8SaveAird.MMI_stCurrentStatus.mode;
	MMI_tstAird.u8Ctrl = MMI_Save.MMI_u8SaveAird.MMI_stCurrentStatus.controlsts;
	MMI_tstStateStore.nAirdState = MMI_Save.MMI_u8SaveAird.MMI_stOFFpreStatus.mode;
	MMI_tstStateStore.nAirdCtrl = MMI_Save.MMI_u8SaveAird.MMI_stOFFpreStatus.controlsts;
	/*BCTL*/
	MMI_tstBctl.u8State = MMI_Save.MMI_u8SaveBCTL.MMI_stCurrentStatus.mode;
	MMI_tstBctl.u8Ctrl = MMI_Save.MMI_u8SaveBCTL.MMI_stCurrentStatus.controlsts;
	MMI_tstStateStore.nBctlState = MMI_Save.MMI_u8SaveBCTL.MMI_stOFFpreStatus.mode;
	MMI_tstStateStore.nBctlSpd = MMI_Save.MMI_u8SaveBCTL.MMI_stOFFpreStatus.controlsts;
	/*RFA*/
	MMI_tstRfa.u8State = MMI_Save.MMI_u8SaveRFA.MMI_stCurrentStatus.mode;
	MMI_tstRfa.u8Ctrl = MMI_Save.MMI_u8SaveRFA.MMI_stCurrentStatus.controlsts;
	MMI_tstStateStore.nRfaState = MMI_Save.MMI_u8SaveRFA.MMI_stOFFpreStatus.mode;
	MMI_tstStateStore.nRfaCtrl = MMI_Save.MMI_u8SaveRFA.MMI_stOFFpreStatus.controlsts;
	/*sys mode*/
	MMI_u8SysState = MMI_Save.MMI_u8SaveMode.MMI_stCurrentStatus.mode;
	//MMI_u8SysState = MMI_Save.MMI_u8SaveMode.MMI_stCurrentStatus.controlsts;
	MMI_tstStateStore.nSystemState = MMI_Save.MMI_u8SaveMode.MMI_stOFFpreStatus.mode;
	//MMI_Save.MMI_u8SaveMode.MMI_stOFFpreStatus.controlsts = MMI_tstStateStore.nSystemState;

	/*ION*/
	MMI_au8Array[MMI_nu8IonMode] = MMI_Save.MMI_u8SaveION.MMI_stCurrentStatus.mode;
	MMI_au8Array[MMI_nu8IonCtrl] = MMI_Save.MMI_u8SaveION.MMI_stCurrentStatus.controlsts;
	
	MMI_tstStateStore.nIonState = MMI_Save.MMI_u8SaveION.MMI_stOFFpreStatus.mode; /*160814*/
	MMI_tstStateStore.nIonCtrl = MMI_Save.MMI_u8SaveION.MMI_stOFFpreStatus.controlsts;
	//MMI_Save.MMI_u8SaveION.MMI_stOFFpreStatus.mode = MMI_au8Array[MMI_nu8IonMode];
	//MMI_Save.MMI_u8SaveION.MMI_stOFFpreStatus.controlsts = MMI_au8Array[MMI_nu8IonCtrl];
	
	/*Dual*/
	//MMI_u8SysState = MMI_Save.MMI_u8SaveDual.CurrentStatus; 160719
	MMI_u8DualCtrl = MMI_Save.MMI_u8SaveDual.CurrentStatus&0x01;/*add & 01, 160814*/
	//MMI_tstStateStore.nSystemState = MMI_Save.MMI_u8SaveDual.OFFpreStatus;160719
	MMI_tstStateStore.nDualCtrl = MMI_Save.MMI_u8SaveDual.OFFpreStatus&0x01;/*add & 01, 160814*/
	//MMI_Save.MMI_u8SaveDual.DEFpreStatus = MMI_tstStateStore.nSystemState;

	/*AQS*/
	//MMI_u8AqsState = MMI_Save.MMI_u8SaveAqs;
    //MMI_tstAqs.u8Ctrl = MMI_Save.MMI_u8SaveAqs;
    //MMI_tstAqs.u8State = MMI_Save.MMI_u8SaveAqs;
	MMI_tstAqs.u8State = MMI_Save.MMI_u8SaveAqs.MMI_stCurrentStatus.mode;
	MMI_tstAqs.u8Ctrl = MMI_Save.MMI_u8SaveAqs.MMI_stCurrentStatus.controlsts;
	MMI_tstStateStore.nAqsState = MMI_Save.MMI_u8SaveAqs.MMI_stOFFpreStatus.mode;
	MMI_tstStateStore.nAqsCtrl = MMI_Save.MMI_u8SaveAqs.MMI_stOFFpreStatus.controlsts;
    
	/*Set Temp*/
	MMI_u8SetTempDr = MMI_Save.MMI_u8SaveSetTempDr.CurrentStatus;
	MMI_tstStateStore.nSetTempL = MMI_Save.MMI_u8SaveSetTempDr.OFFpreStatus;

	MMI_u8SetTempPs = MMI_Save.MMI_u8SaveSetTempPs.CurrentStatus;
	MMI_tstStateStore.nSetTempR = MMI_Save.MMI_u8SaveSetTempPs.OFFpreStatus;
}

static void MMI_vSysHistoryStateRestore(void)
{
	MMI_u8SysState = MMI_tstStateStore.nSystemState;
	MMI_u8DualCtrl = MMI_tstStateStore.nDualCtrl;
	MMI_u8SetTempDr = MMI_tstStateStore.nSetTempL;
	//MMI_u8SetTempDr = MMI_tstStateStore.nSetTempR;/*ITP45, Dr to Ps,160430*/
	MMI_u8SetTempPs = MMI_tstStateStore.nSetTempR;

    MMI_vAqsHistoryStateRestore();
}

static void MMI_vBctlHistoryStateRestore(void)
{
	MMI_tstBctl.u8State = MMI_tstStateStore.nBctlState;
	MMI_tstBctl.u8Ctrl = MMI_tstStateStore.nBctlSpd;
}

static void MMI_vAirdHistoryStateRestore(void)
{
	MMI_tstAird.u8State = MMI_tstStateStore.nAirdState;
	MMI_tstAird.u8Ctrl = MMI_tstStateStore.nAirdCtrl;
}

static void MMI_vAcccHistoryStateRestore(void)
{
	MMI_tstAccc.u8State = MMI_tstStateStore.nAcccState;
	MMI_tstAccc.u8Ctrl = MMI_tstStateStore.nAcccCtrl;
}

static void MMI_vRfaHistoryStateRestore(void)
{
	MMI_tstRfa.u8State = MMI_tstStateStore.nRfaState;
	MMI_tstRfa.u8Ctrl = MMI_tstStateStore.nRfaCtrl;
}

static void MMI_vAqsHistoryStateRestore(void)
{
	MMI_tstAqs.u8State = MMI_tstStateStore.nAqsState;
	MMI_tstAqs.u8Ctrl = MMI_tstStateStore.nAqsCtrl;
}

static void MMI_vSysStoreStateChangeToManual(void)
{
	MMI_tstStateStore.nSystemState = MMI_nSysStateManual;
}

static void MMI_vIonHistoryStateRestore(void)
{
	MMI_tstIon.u8State = MMI_tstStateStore.nIonState;
	MMI_tstIon.u8Ctrl = MMI_tstStateStore.nIonCtrl;
}
/* ===========================================================================
**********Add The Actions function Here *************************************
============================================================================*/

static void MMI_vActBctlEnterDef(void)
{
#if 0
    if(MMI_u8CurrentSysState == MMI_nSysStateOff)
    {
	    MMI_tstBctl.u8Ctrl = MMI_nBctlSpeed7;
    }
    else
    {
        /*No change*/
    }
#else
    if((MMI_tstBctl.u8Ctrl < 5) || (MMI_u8CurrentSysState == MMI_nSysStateOff))
    {
        MMI_tstBctl.u8Ctrl = MMI_nBctlSpeed5;
    }
    else
    {
        /*No change*/
    }
#endif
}

static void MMI_vActBctlEnterMaxAc(void)
{
	MMI_tstBctl.u8Ctrl = MMI_nBctlSpeed7;
}

static void MMI_vActAirdEnterDef(void)
{
	MMI_tstAird.u8Ctrl = MMI_nAirdScreen;
}

static void MMI_vActAirdEnterMaxAc(void)
{
	MMI_tstAird.u8Ctrl = MMI_nAirdFace;
}

static void MMI_vActAcccEnterDef(void)
{
	MMI_tstAccc.u8Ctrl = MMI_nAcOn;
}

static void MMI_vActAcccEnterMaxAc(void)
{
	MMI_tstAccc.u8Ctrl = MMI_nAcOn;
}

static void MMI_vActRfaEnterDef(void)
{
	MMI_tstRfa.u8Ctrl = MMI_nRfaFresh;
}

static void MMI_vActRfaEnterMaxAc(void)
{
	MMI_tstRfa.u8Ctrl = MMI_nRfaRecirc;
}

static void MMI_vActAcccAqsEnterDef(void)
{
    //MMI_au8Array[MMI_nu8AqsRequest] = MMI_nAQSOff;
    MMI_tstAqs.u8Ctrl = MMI_nAQSOff;
}

static void MMI_vActAqsEnterMaxAc(void)
{
    //MMI_au8Array[MMI_nu8AqsRequest] = MMI_nAQSOff;
    MMI_tstAqs.u8Ctrl = MMI_nAQSOff;
}

static void MMI_vActBctlSpdIncLimit(void)
{
	if(MMI_tstBctl.u8Ctrl >= MMI_nBctlSpeed7)
	{
		MMI_tstBctl.u8Ctrl = MMI_nBctlSpeed7;
	}
	else
	{
        MMI_tstBctl.u8Ctrl ++;
	}
}

static void MMI_vActBctlSpdDecLimit(void)
{
	if(MMI_tstBctl.u8Ctrl <= MMI_nBctlSpeed1)
	{
		MMI_tstBctl.u8Ctrl = MMI_nBctlSpeed1;
	}
	else
	{
        MMI_tstBctl.u8Ctrl --;
	}
}

static MMI_tenAcCtrl MMI_nActAcSwitch(void)
{	
	MMI_tenAcCtrl enReturnAc;
	switch(MMI_tstAccc.u8Ctrl)
	{
		case MMI_nAcOff:
			enReturnAc = MMI_nAcOn;
			break;
		
		case MMI_nAcOn:
			enReturnAc = MMI_nAcOff;
			break;
		default :
			enReturnAc = MMI_nAcOff;
			break;			
	}
	return enReturnAc;
}

static MMI_tenAirdCtrl MMI_nActAirdSwitchR(void)
{
	MMI_tenAirdCtrl enReturnAird;
	switch(MMI_tstAird.u8Ctrl)
	{
		case MMI_nAirdFace:
			enReturnAird = MMI_nAirdBilevel;
			break;
		case MMI_nAirdBilevel:
			enReturnAird = MMI_nAirdFloor;
			break;
		case MMI_nAirdFloor:
			enReturnAird = MMI_nAirdMixed;
			break;
		case MMI_nAirdMixed:
			enReturnAird = MMI_nAirdScreen;
			break;
		case MMI_nAirdScreen:
			enReturnAird = MMI_nAirdFace;
			break;
		default :
			enReturnAird = MMI_nAirdFace;
			break;
	}
	return enReturnAird;
}

static MMI_tenAirdCtrl MMI_nActAirdSwitchL(void)
{
	MMI_tenAirdCtrl enReturnAird;
	switch(MMI_tstAird.u8Ctrl)
	{
		case MMI_nAirdFace:
			enReturnAird = MMI_nAirdScreen;
			break;
		case MMI_nAirdScreen:
			enReturnAird = MMI_nAirdMixed;
			break;
		case MMI_nAirdMixed:
			enReturnAird = MMI_nAirdFloor;
			break;
		case MMI_nAirdFloor:
			enReturnAird = MMI_nAirdBilevel;
			break;
		case MMI_nAirdBilevel:
			enReturnAird = MMI_nAirdFace;
			break;
		default :
			enReturnAird = MMI_nAirdFace;
			break;
	}
	return enReturnAird;
}

static MMI_tenAirdCtrl MMI_nActVkeyAirdCtrl(void)
{
	uint8 u8VkeyMode = MMI_u8GetVkeyMode;
	MMI_tenAirdCtrl enReturnAird;
	if(u8VkeyMode >= MMI_nAirdScreen)
	{
		enReturnAird = MMI_nAirdScreen;
	}
	else
	{
		enReturnAird = (MMI_tenAirdCtrl)u8VkeyMode;

	}
	return enReturnAird;
}

static MMI_tenRfaCtrl MMI_nActOffRfaSwitch(void)
{
	MMI_tenRfaCtrl enReturnRfa;
	switch(MMI_tstRfa.u8Ctrl)
	{
		case MMI_nRfaFresh:
			enReturnRfa = MMI_nRfaRecirc;
			break;
		case MMI_nRfaRecirc:
			enReturnRfa = MMI_nRfaFresh;
			break;
		default:
			enReturnRfa = MMI_nRfaFresh;
			break;
	}
	return enReturnRfa;

}

static MMI_tenRfaCtrl MMI_nActRfaAqsSwitch(void)
{
	MMI_tenRfaCtrl enReturnRfa;
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
    if(MMI_u8SysState != MMI_nSysStateOff)
    {
	    enReturnRfa = MMI_vChangeAqsState(MMI_tstRfa.u8Ctrl);/*160812*/
    }
    else
    {
    	switch(MMI_tstRfa.u8Ctrl)
    	{
    		case MMI_nRfaFresh:
    			enReturnRfa = MMI_nRfaRecirc;
    			break;
    		case MMI_nRfaRecirc:
    			enReturnRfa = MMI_nRfaFresh;
    			break;
    		default:
    			enReturnRfa = MMI_nRfaFresh;
    			break;
    	}
    }
#else
	switch(MMI_tstRfa.u8Ctrl)
	{
		case MMI_nRfaFresh:
			enReturnRfa = MMI_nRfaRecirc;
			break;
		case MMI_nRfaRecirc:
			enReturnRfa = MMI_nRfaFresh;
			break;
		default:
			enReturnRfa = MMI_nRfaFresh;
			break;
	}
#endif

    return enReturnRfa;
}

static MMI_tenRfaCtrl MMI_nActRfaSwitch(void)
{
	MMI_tenRfaCtrl enReturnRfa;
	switch(MMI_tstRfa.u8Ctrl)
	{
		case MMI_nRfaFresh:
			enReturnRfa = MMI_nRfaRecirc;
			break;
		case MMI_nRfaRecirc:
			enReturnRfa = MMI_nRfaFresh;
			break;
		default:
			enReturnRfa = MMI_nRfaFresh;
			break;
	}
    return enReturnRfa;
}
static void MMI_vActSetTempLeftInc(void)
{
	if (MMI_u8SetTempDr <= MMI_nu8TempMaxVal)
	{
		//MMI_u8SetTempDr += MMI_nTempStep;
		MMI_u8SetTempDr += 1;//LINAPP_u16GetValue(LIN_nu16RCPSetTempUp_L);/*KC-2HB,160517*/
	}
	
	if (MMI_u8SetTempDr < MMI_nu8TempMinVal)
	{
		MMI_u8SetTempDr = MMI_nu8TempMinVal;
	}
	else if (MMI_u8SetTempDr > MMI_nu8TempMaxVal)
	{
		MMI_u8SetTempDr = MMI_nu8SetTempHigh;
	}
	else
	{
		/*In normal range*/
	}

	if(MMI_u8DualCtrl == MMI_nDualOff)
	{
		MMI_u8SetTempPs = MMI_u8SetTempDr;
	}

}

static void MMI_vActSetTempLeftDec(void)
{
	if (MMI_u8SetTempDr >= MMI_nu8TempMinVal)
	{
		//MMI_u8SetTempDr -= MMI_nTempStep;
		//if (MMI_u8SetTempDr > LINAPP_u16GetValue(LIN_nu16RCPSetTempDown_L))
		//{
			MMI_u8SetTempDr -= 1;//LINAPP_u16GetValue(LIN_nu16RCPSetTempDown_L);/*KC-2HB,160517*/
		//}
		//else
		//{
			//MMI_u8SetTempDr =MMI_nu8TempMinVal-1;
		//}
	}
	
	if (MMI_u8SetTempDr > MMI_nu8TempMaxVal)
	{
		MMI_u8SetTempDr = MMI_nu8TempMaxVal;
	}
	else if (MMI_u8SetTempDr < MMI_nu8TempMinVal)
	{
		MMI_u8SetTempDr = MMI_nu8SetTempLow;
	}
	else
	{
		/*In normal range*/
	}
	
	if(MMI_u8DualCtrl == MMI_nDualOff)
	{
		MMI_u8SetTempPs = MMI_u8SetTempDr;
	}

}


/* ===========================================================================
* Function   : void MMI_vActChange2Off(void)
* Description: Action, change state to Off
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vActChange2Off(void)
{
	/***System & others state transfer****/ 
	MMI_u8SysState = MMI_nSysStateOff;
	MMI_u8DualCtrl= MMI_nDualOff;
	
	/***BCTL state transfer & Action****/ 
	MMI_tstBctl.u8State = MMI_nBctlStateOff;
	MMI_tstBctl.u8Ctrl = MMI_nBctlOff;
	
	/***AIRD state transfer & Action****/
	MMI_tstAird.u8State = MMI_nAirdStateOff;
	/*enAirdCtrl no atcion. Keep current Ctrl in Off state*/ 
	
	/***ACCC state transfer & Action****/ 
	MMI_tstAccc.u8State = MMI_nAcStateOff;
	MMI_tstAccc.u8Ctrl = MMI_nAcOff;
	
	/***RFA state transfer & Action****/ 
	MMI_tstRfa.u8State = MMI_nRfaStateOff;
    //MMI_tstRfa.u8Ctrl = MMI_nRfaRecirc;
	/*enRfaCtrl no atcion. Keep current Ctrl in Off state*/

	/***Aqs state transfer & Action****/ 
	MMI_tstAqs.u8State = MMI_nAqsStateOff;
	MMI_tstAqs.u8Ctrl = MMI_nAQSOff;
	//MMI_biAtcOffFlag = False;

	/***ION state transfer & Action****/ 
	MMI_au8Array[MMI_nu8IonMode] = MMI_nIonStateOff;
	MMI_au8Array[MMI_nu8IonCtrl] = MMI_nIonStandby;
}


static void MMI_vActEnterDefrost(void)
{
	/***System & others state transfer****/ 
	MMI_u8SysState = MMI_nSysStateDefrost;
	/*enDualCtrl no action*/
	
	/***BCTL state transfer & Action****/ 
	MMI_tstBctl.u8State = MMI_nBctlStateDefrost;
	MMI_vActBctlEnterDef();
	
	/***AIRD state transfer & Action****/
	MMI_tstAird.u8State = MMI_nAirdStateDefrost;
	MMI_vActAirdEnterDef(); 
	
	/***ACCC state transfer & Action****/ 
	MMI_tstAccc.u8State = MMI_nAcStateDefrost;
	MMI_vActAcccEnterDef();
	
	/***RFA state transfer & Action****/ 
	MMI_tstRfa.u8State = MMI_nRfaStateDefrost;
	MMI_vActRfaEnterDef();

	/*close aqs,160812*/
    MMI_tstAqs.u8State = MMI_nAqsStateDefrost;
	MMI_vActAcccAqsEnterDef();
}


static void MMI_vActEnterMaxAc(void)
{
	/***System & others state transfer****/ 
	MMI_u8SysState = MMI_nSysStateMaxAc;
	MMI_u8SetTempDr = 0;
	MMI_u8SetTempPs= 0;
	/*enDualCtrl no action*/

	/***BCTL state transfer & Action****/ 
	MMI_tstBctl.u8State = MMI_nBctlStateMaxAc;
	MMI_vActBctlEnterMaxAc();

	/***AIRD state transfer & Action****/
	MMI_tstAird.u8State = MMI_nAirdStateMaxAc;
	MMI_vActAirdEnterMaxAc(); 

	/***ACCC state transfer & Action****/ 
	MMI_tstAccc.u8State = MMI_nAcStateMaxAc;
	MMI_vActAcccEnterMaxAc();

	/***RFA state transfer & Action****/ 
	MMI_tstRfa.u8State = MMI_nRfaStateMaxAc;
	MMI_vActRfaEnterMaxAc();

	/*close aqs,160812*/
	//MMI_au8Array[MMI_nu8AqsRequest]=MMI_nAQSOff;
	MMI_tstAqs.u8State = MMI_nAqsStateMaxAc;
	MMI_vActAqsEnterMaxAc();
	
}


/* ===========================================================================
* Function   : void MMI_vChange2ManuFromDefManuOrMaxAcManu(void)
* Description: Changed to Manual st while has been operated in def or MaxAc state
* Takes      : Nothing
* Returns    : Nothing
*/

static void MMI_vChange2ManuFromDefManuOrMaxAcManu(void)
{
	if((MMI_tstBctl.u8State==MMI_nBctlStateDefManu)
		||(MMI_tstBctl.u8State==MMI_nBctlStateMaxAcManu))
	{
		MMI_tstBctl.u8State = MMI_nBctlStateManual;
	}
	
	if((MMI_tstAccc.u8State==MMI_nAcStateDefManu)
		||(MMI_tstAccc.u8State==MMI_nAcStateMaxAcManu))
	{
		MMI_tstAccc.u8State = MMI_nAcStateManual;
	}
	
	if((MMI_tstRfa.u8State==MMI_nRfaStateDefManu)
		||(MMI_tstRfa.u8State==MMI_nRfaStateMaxAcManu))
	{
		MMI_tstRfa.u8State = MMI_nRfaStateManual;
	}

}




static void MMI_vActVkeyBlwCtrl(void)
{
	uint8 u8VkeyBlwSpd = MMI_u8GetVkeyBlwSpd;
	if(u8VkeyBlwSpd >= MMI_nBctlSpeed7)
	{
		MMI_tstBctl.u8Ctrl = MMI_nBctlSpeed7;
	}
	else
	{
		MMI_tstBctl.u8Ctrl = u8VkeyBlwSpd;
	}

}

/* ===========================================================================
* Function   : static void MMI_vTriggerEventShl(void)
* Description: Function used for unused buttons in action tables
* Takes      : Nothing
* Returns    : Nothing
*/
 static void MMI_vTriggerEventShl(void)
{
	/* Function used for unused buttons in action tables */ 
    if(MMI_u8ShlCtrl == MMI_nSeatHeatLeftOff)
    {
        MMI_u8ShlCtrl = MMI_nSeatHeatLeft1;
    }
    else
    {
        MMI_u8ShlCtrl = MMI_nSeatHeatLeftOff;
    }
}

/* ===========================================================================
* Function   : static void MMI_vTriggerEventShr(void)
* Description: Function used for unused buttons in action tables
* Takes      : Nothing
* Returns    : Nothing
*/
 static void MMI_vTriggerEventShr(void)
{
	/* Function used for unused buttons in action tables */ 
    if(MMI_u8ShrCtrl == MMI_nSeatHeatRightOff)
    {
        MMI_u8ShrCtrl = MMI_nSeatHeatRight1;
    }
    else
    {
        MMI_u8ShrCtrl = MMI_nSeatHeatRightOff;
    }
}





/* ===========================================================================
**********Add The state transfer function Here *******************************
============================================================================*/

/* ===========================================================================
* Function   : static void MMI__vTakeAction_NotUsed(void)
* Description: Function used for unused buttons in action tables
* Takes      : Nothing
* Returns    : Nothing
*/
#ifdef Used_RearPanel
static void MMI_vTriggerEventNotUsed(void)
{
	/* Function used for unused buttons in action tables */ 
}
#endif
/* ===========================================================================
* Function   : static void MMI__vTakeAction_WatchDogTest(void)
* Description: Function used for test the watch dog function.
* Takes      : Nothing
* Returns    : Nothing
*/
//static void MMI_vTriggerEventWatchDogTest(void)
//{
	//while(True)
	//{
	/*dead loop.*/
	//}
//}


/* ===========================================================================
* Function   : static void MMI_vTriggerEventOff(void)
* Description: Event trigger Function. OFF event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventOff(void)
{
	if(MMI_u8SysState == MMI_nSysStateOff)
	{/***Exit Off State****/ 
		//MMI_vAllHistoryStateRestore(); /*ITP42,do not to repeat same action, BY ZSC,160430*/
		/*Changed to Manual st while has been operated in def or MaxAc state*/
		//MMI_vChange2ManuFromDefManuOrMaxAcManu();/*do not to repeat same action, BY ZSC,160430*/
	}
	else
	{/***Enter Off State****/ 
        if(MMI_u8TurnOnByPm25==True)
		{
			MMI_u8Pm25PopupOperationSts = False; /*press off,180402*/
		}
		/***Restore the history state from Def or MaxAc */
		MMI_vAllHistoryStateRestore();
		/*Changed to Manual st while has been operated in def or MaxAc state*/
		MMI_vChange2ManuFromDefManuOrMaxAcManu();
	
		/***History store before transfer to Off*/ 
		MMI_vAllHistoryStateStore();
		/***Chenge to Off state*/
		MMI_vActChange2Off();
	}

}

/* ===========================================================================
* Function   : static void MMI_vTriggerEventAuto(void)
* Description: Event trigger Function. AUTO event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventAuto(void)
{
	/***Enter****/
	/***Restore the history state from Off,Def or MaxAc */
	MMI_vAllHistoryStateRestore();
	/***History store*/ 
	MMI_vAllHistoryStateStore();
	/***System & others state transfer****/ 
	MMI_u8SysState = MMI_nSysStateAuto;
	/*enDualCtrl no action*/

	/***BCTL state transfer & Action****/ 
	MMI_tstBctl.u8State = MMI_nBctlStateAuto;
	/*enBctlCtrl no action*/
	
	/***AIRD state transfer & Action****/
	MMI_tstAird.u8State = MMI_nAirdStateAuto;
	/*enAirdCtrl no atcion*/ 
	
	/***ACCC state transfer & Action****/ 
	MMI_tstAccc.u8State = MMI_nAcStateAuto;
	/*enAcccCtrl no action*/

	/***RFA state transfer & Action****/ 
	MMI_tstRfa.u8State = MMI_nRfaStateAuto;
	/*enRfaCtrl no atcion*/
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
	/***ION state transfer & Action****/
	if (MMI_nUseIonCfg == False)
	{
		MMI_au8Array[MMI_nu8IonCtrl] =MMI_nIonStandby;
		MMI_au8Array[MMI_nu8IonMode] = MMI_nIonStateOff;
	}
    else
    {
    	MMI_au8Array[MMI_nu8IonMode] = MMI_nIonStateAuto;/*by zsc,160509*/
    	MMI_au8Array[MMI_nu8IonCtrl] = MMI_nIonIonMode;
    }
	
	/***AQS state transfer & Action****/
	//MMI_au8Array[MMI_nu8AqsRequest]     =MMI_nAQSOn;/*by zsc,160512*/
	MMI_tstStateStore.nAqsState = MMI_nAqsStateAuto;
	MMI_tstAqs.u8Ctrl = MMI_nAQSOn;
#endif
}


/* ===========================================================================
* Function   : static void MMI_vTriggerEventDefrost(void)
* Description: Event trigger Function. DEF event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventDefrost(void)
{
	if(MMI_u8SysState != MMI_nSysStateDefrost)
	{/***Enter****/ 
        MMI_u8CurrentSysState = MMI_u8SysState;
		/***Restore the history state from Off,Def or MaxAc */
		MMI_vAllHistoryStateRestore();
		/***History store*/ 
		MMI_vAllHistoryStateStore();

		MMI_vActEnterDefrost();
	}
	else
	{/*Exit Defrost*/
        MMI_vSetTempHistoryStateStore();/*Added By Sunny Young*/
		MMI_vBctlHistoryStateStore();
		MMI_vAirdHistoryStateStore();
		MMI_vAcccHistoryStateStore();
		MMI_vRfaHistoryStateStore();
        MMI_vAqsHistoryStateStore();
		MMI_vAllHistoryStateRestore();
		MMI_vChange2ManuFromDefManuOrMaxAcManu();
		
	}
}


/* ===========================================================================
* Function   : static void MMI_vTriggerEventMaxAc(void)
* Description: Event trigger Function. MaxAc event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventMaxAc(void)
{
	if(MMI_u8SysState != MMI_nSysStateMaxAc)
	{
		/***Enter****/ 
		MMI_vAllHistoryStateRestore();
		/***History store*/ 
		MMI_vAllHistoryStateStore();
	
		MMI_vActEnterMaxAc();
	}
	else
	{
		MMI_vBctlHistoryStateStore();
		MMI_vAirdHistoryStateStore();
		MMI_vAcccHistoryStateStore();
		MMI_vRfaHistoryStateStore();
		MMI_vAllHistoryStateRestore();
		
		MMI_vChange2ManuFromDefManuOrMaxAcManu();
	}

}


/* ===========================================================================
* Function   : static void MMI_vTriggerEventBlowerInc(void)
* Description: Event trigger Function. Blower + event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventBlwInc(void)
{
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_vSysHistoryStateRestore();
			MMI_u8SysState = MMI_nSysStateManual;
			break;
		case MMI_nSysStateAuto:
			MMI_u8SysState = MMI_nSysStateManual;
			break;
        case MMI_nSysStateDefrost:
        case MMI_nSysStateMaxAc:
            {
		        /*else states change to Manual*/ 
                MMI_vSysStoreStateChangeToManual();
            }
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			MMI_tstBctl.u8State= MMI_nBctlStateManual;
			MMI_tstBctl.u8Ctrl = MMI_nBctlSpeed1;
			break;
		case MMI_nBctlStateAuto:
		case MMI_nBctlStateManual:
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			MMI_vActBctlSpdIncLimit();
			break;
		case MMI_nBctlStateDefrost:
		case MMI_nBctlStateDefManu:		
			MMI_tstBctl.u8State = MMI_nBctlStateDefManu;
			MMI_vActBctlSpdIncLimit();
			break;
		case MMI_nBctlStateMaxAc:
		case MMI_nBctlStateMaxAcManu:
			MMI_tstBctl.u8State = MMI_nBctlStateMaxAcManu;
			MMI_vActBctlSpdIncLimit();
			break;
		default :
			break;
			
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			MMI_vAirdHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{
		case MMI_nAcStateOff:
			MMI_vAcccHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_vRfaHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}

    MMI_vBctlHistoryStateStore();/*add by Yang Shengli,2017-03-11*/
}


/* ===========================================================================
* Function   : static void MMI_vTriggerEventBlwDec(void)
* Description: Event trigger Function. Blower - event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventBlwDec(void)
{
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_vSysHistoryStateRestore();
			MMI_u8SysState = MMI_nSysStateManual;
			break;
		case MMI_nSysStateAuto:
			MMI_u8SysState = MMI_nSysStateManual;
			break;
        case MMI_nSysStateDefrost:
        case MMI_nSysStateMaxAc:
            {
		        /*else states change to Manual*/ 
                MMI_vSysStoreStateChangeToManual();
            }
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			MMI_tstBctl.u8Ctrl = MMI_nBctlSpeed1;
			break;
		case MMI_nBctlStateAuto:
		case MMI_nBctlStateManual:
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			MMI_vActBctlSpdDecLimit();
			break;
		case MMI_nBctlStateDefrost:
		case MMI_nBctlStateDefManu: 	
			MMI_tstBctl.u8State = MMI_nBctlStateDefManu;
			MMI_vActBctlSpdDecLimit();
			break;
		case MMI_nBctlStateMaxAc:
		case MMI_nBctlStateMaxAcManu:
			MMI_tstBctl.u8State = MMI_nBctlStateMaxAcManu;
			MMI_vActBctlSpdDecLimit();
			break;
		default :
			break;
			
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			MMI_vAirdHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{
		case MMI_nAcStateOff:
			MMI_vAcccHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_vRfaHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}

    MMI_vBctlHistoryStateStore();/*add by Yang Shengli,2017-03-11*/
}


/* ===========================================================================
* Function   : static void MMI_vTriggerEventAc(void)
* Description: Event trigger Function. A/C event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventAc(void)
{
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_vSysHistoryStateRestore();
			break;
		case MMI_nSysStateMaxAc:
			//MMI_vSysHistoryStateRestore();/*SYS states do not change,160523*/
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			MMI_vBctlHistoryStateRestore();
			break;
		case MMI_nBctlStateAuto:
		case MMI_nBctlStateManual:
		case MMI_nBctlStateDefrost:
		case MMI_nBctlStateDefManu: 
			/*states do not change*/
			break;
		case MMI_nBctlStateMaxAc:
			//MMI_vBctlHistoryStateRestore();/*states do not change,160523*/
			break;			
		case MMI_nBctlStateMaxAcManu:
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		default :
			break;
			
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			MMI_vAirdHistoryStateRestore();
			break;
		case MMI_nAirdStateMaxAc:
			//MMI_vAirdHistoryStateRestore();/*states do not change,160523*/
			break;				
		/*else states do not change*/ 
		default :
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{
		case MMI_nAcStateOff:
			MMI_tstAccc.u8State = MMI_nAcStateManual;
			MMI_tstAccc.u8Ctrl= MMI_nAcOn;
			break;
		case MMI_nAcStateAuto:
			MMI_tstAccc.u8State = MMI_nAcStateManual;
			MMI_tstAccc.u8Ctrl = MMI_nActAcSwitch();
			break;
		case MMI_nAcStateManual:
			MMI_tstAccc.u8State = MMI_nAcStateManual;
			MMI_tstAccc.u8Ctrl = MMI_nActAcSwitch();
			break;
		case MMI_nAcStateDefrost:
			MMI_tstAccc.u8State = MMI_nAcStateDefManu;
			MMI_tstAccc.u8Ctrl = MMI_nActAcSwitch();
			break;
		case MMI_nAcStateDefManu: 	
			MMI_tstAccc.u8State = MMI_nAcStateDefManu;
			MMI_tstAccc.u8Ctrl = MMI_nActAcSwitch();
			break;
		case MMI_nAcStateMaxAc:
			//MMI_vAcccHistoryStateRestore();
			MMI_tstAccc.u8State = MMI_nAcStateDefManu;/*states do not change,160523*/
			MMI_tstAccc.u8Ctrl = MMI_nActAcSwitch();
			break;			
		case MMI_nAcStateMaxAcManu:
			break;						
		default :
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateMaxAc:
			//MMI_vRfaHistoryStateRestore();/*states do not change,160523*/
			break;			
		case MMI_nRfaStateMaxAcManu:
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;						
		/*else states do not change*/ 
		default :
			break;
	}

    MMI_vAcccHistoryStateStore();
}

/* ===========================================================================
* Function   : static void MMI_vTriggerEventModeL(void)
* Description: Event trigger Function. MODE event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventModeL(void)
{
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			//MMI_vSysHistoryStateRestore();/*states do not change,160523*/
			break;
		case MMI_nSysStateAuto:
			MMI_u8SysState = MMI_nSysStateManual;
			break;			
        case MMI_nSysStateDefrost:
        case MMI_nSysStateMaxAc:
            {
                MMI_vSysStoreStateChangeToManual();
                MMI_vSysHistoryStateRestore();
            }
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			//MMI_vBctlHistoryStateRestore();/*states do not change,160523*/
			break;
		case MMI_nBctlStateAuto:/*No Change*/ 
			break;
		case MMI_nBctlStateManual:/*No Change*/ 
			break;
		case MMI_nBctlStateDefrost:
			MMI_vBctlHistoryStateRestore();
			break;
		case MMI_nBctlStateDefManu: /*Exit Def and change to Manual*/	 	
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		case MMI_nBctlStateMaxAc:
			MMI_vBctlHistoryStateRestore();
			break;			
		case MMI_nBctlStateMaxAcManu: /*Exit MaxAc and change to Manual*/	
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		default :
			break;
			
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			//MMI_vAirdHistoryStateRestore();/*states do not change,160523*/
			//MMI_tstAird.u8State = MMI_nAirdStateManual;/*Removed by Yang Shengli,10160919*/
			//MMI_tstAird.u8Ctrl = MMI_nActAirdSwitchL();/*Removed by Yang Shengli,10160919*/
			break;
		case MMI_nAirdStateAuto:
			MMI_tstAird.u8State = MMI_nAirdStateManual;
			MMI_tstAird.u8Ctrl= MMI_nActAirdSwitchL();
			break;
		case MMI_nAirdStateManual:
			MMI_tstAird.u8State = MMI_nAirdStateManual;
			MMI_tstAird.u8Ctrl = MMI_nActAirdSwitchL();
			break;
		case MMI_nAirdStateDefrost:
			MMI_vAirdHistoryStateRestore();
            MMI_tstAird.u8State = MMI_nAirdStateManual;/*add by Yang Shengli,2017-03-11*/
			break;				
		case MMI_nAirdStateMaxAc:
			MMI_vAirdHistoryStateRestore();
            MMI_tstAird.u8State = MMI_nAirdStateManual;/*add by Yang Shengli,2017-03-11*/
			break;				
		/*else states do not change*/ 
		default :
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{	/*Off, MaxAc, Def shall be restroe*/
		case MMI_nAcStateOff:
			/*states do not change,160523*/
			break;
		case MMI_nAcStateMaxAc:
		case MMI_nAcStateDefrost:
			MMI_vAcccHistoryStateRestore();
			break;
		case MMI_nAcStateDefManu: /*Exit Def and change to Manual*/	
			MMI_tstAccc.u8State = MMI_nAcStateManual;
			break;
		case MMI_nAcStateAuto:/*No Change*/ 
			break;
		case MMI_nAcStateManual:/*No Change*/ 
			break;						
		default :
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			//MMI_vRfaHistoryStateRestore();/*states do not change,160523*/
			break;
		case MMI_nRfaStateAuto:/*No Change*/
			break;
		case MMI_nRfaStateManual:/*No Change*/
			break;
		case MMI_nRfaStateDefrost:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateDefManu:/*Exit Def and change to Manual*/
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;
		case MMI_nRfaStateMaxAc:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateMaxAcManu:
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;	
		default :
			break;
	}

}

/* ===========================================================================
* Function   : static void MMI_vTriggerEventModeR(void)
* Description: Event trigger Function. MODE event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventModeR(void)
{
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			//MMI_vSysHistoryStateRestore();/*states do not change,160523*/
			break;
		case MMI_nSysStateAuto:
			MMI_u8SysState = MMI_nSysStateManual;
			break;
        case MMI_nSysStateDefrost:
        case MMI_nSysStateMaxAc:
            {
                MMI_vSysStoreStateChangeToManual();
                MMI_vSysHistoryStateRestore();
            }
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			//MMI_vBctlHistoryStateRestore();/*states do not change,160523*/
			break;
		case MMI_nBctlStateAuto:/*No Change*/ 
			break;
		case MMI_nBctlStateManual:/*No Change*/ 
			break;
		case MMI_nBctlStateDefrost:
			MMI_vBctlHistoryStateRestore();
			break;
		case MMI_nBctlStateDefManu: /*Exit Def and change to Manual*/	 	
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		case MMI_nBctlStateMaxAc:
			MMI_vBctlHistoryStateRestore();
			break;			
		case MMI_nBctlStateMaxAcManu: /*Exit MaxAc and change to Manual*/	
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		default :
			break;
			
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			//MMI_vAirdHistoryStateRestore();/*states do not change,160523*/
			//MMI_tstAird.u8State = MMI_nAirdStateManual;/*Removed by Yang Shengli,10160919*/
			//MMI_tstAird.u8Ctrl = MMI_nActAirdSwitchL();/*Removed by Yang Shengli,10160919*/
			break;
		case MMI_nAirdStateAuto:
			MMI_tstAird.u8State = MMI_nAirdStateManual;
			MMI_tstAird.u8Ctrl= MMI_nActAirdSwitchR();
			break;
		case MMI_nAirdStateManual:
			MMI_tstAird.u8State = MMI_nAirdStateManual;
			MMI_tstAird.u8Ctrl = MMI_nActAirdSwitchR();
			break;
		case MMI_nAirdStateDefrost:
			MMI_vAirdHistoryStateRestore();
            MMI_tstAird.u8State = MMI_nAirdStateManual;/*add by Yang Shengli,2017-03-11*/
			break;				
		case MMI_nAirdStateMaxAc:
			MMI_vAirdHistoryStateRestore();
            MMI_tstAird.u8State = MMI_nAirdStateManual;/*add by Yang Shengli,2017-03-11*/
			break;				
		/*else states do not change*/ 
		default :
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{	/*Off, MaxAc, Def shall be restroe*/
		case MMI_nAcStateOff:
			/*states do not change,160523*/
			break;
		case MMI_nAcStateMaxAc:
		case MMI_nAcStateDefrost:
			MMI_vAcccHistoryStateRestore();
			break;
		case MMI_nAcStateDefManu: /*Exit Def and change to Manual*/	
			MMI_tstAccc.u8State = MMI_nAcStateManual;
			break;
		case MMI_nAcStateAuto:/*No Change*/ 
			break;
		case MMI_nAcStateManual:/*No Change*/ 
			break;						
		default :
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			//MMI_vRfaHistoryStateRestore();/*states do not change,160523*/
			break;
		case MMI_nRfaStateAuto:/*No Change*/
			break;
		case MMI_nRfaStateManual:/*No Change*/
			break;
		case MMI_nRfaStateDefrost:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateDefManu:/*Exit Def and change to Manual*/
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;
		case MMI_nRfaStateMaxAc:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateMaxAcManu:
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;	
		default :
			break;
	}

}

/* ===========================================================================
* Function   : static void MMI_vTriggerEventRecAndFre(void)
* Description: Event trigger Function. R/F event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventRecAndFre(void)
{
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
            //MMI_au8Array[MMI_nu8AqsRequest] = MMI_nAQSOff;
            MMI_tstAqs.u8Ctrl = MMI_nAQSOff;
			MMI_tstRfa.u8Ctrl = MMI_nActOffRfaSwitch();
			break;
		case MMI_nRfaStateAuto:
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			//MMI_tstRfa.u8Ctrl = MMI_nActRfaAqsSwitch();
			MMI_tstRfa.u8Ctrl = MMI_nActRfaSwitch();
			break;
		case MMI_nRfaStateManual:
            /*
        #if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
            if((MMI_tstAqs.u8Ctrl == Off) && (MMI_tstRfa.u8Ctrl == MMI_nRfaRecirc))
            {
                MMI_tstRfa.u8State = MMI_nRfaStateManual;
                if(MMI_u8SysState == MMI_nSysStateOff)
                {
                    MMI_tstRfa.u8Ctrl = MMI_nActRfaAqsSwitch();
                }
                else
                {
                    MMI_vChangeAqsState(MMI_tstRfa.u8Ctrl);
                }
            }
            else
        #endif
            {
                MMI_tstRfa.u8State = MMI_nRfaStateManual;
    			MMI_tstRfa.u8Ctrl = MMI_nActRfaAqsSwitch();
            }
            */
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			//MMI_tstRfa.u8Ctrl = MMI_nActRfaAqsSwitch();
			MMI_tstRfa.u8Ctrl = MMI_nActRfaSwitch();
			break;
		case MMI_nRfaStateDefrost:
            MMI_tstAqs.u8State = MMI_nAqsStateDefManu;/*add by Yang Shengli,2017-03-11*/
            //MMI_tstAqs.u8Ctrl = MMI_nAQSOff;/*add by Yang Shengli,2017-03-11*/
			MMI_tstRfa.u8State = MMI_nRfaStateDefManu;
			//MMI_tstRfa.u8Ctrl = MMI_nActRfaAqsSwitch();
			MMI_tstRfa.u8Ctrl = MMI_nActRfaSwitch();
			break;
		case MMI_nRfaStateDefManu:
			MMI_tstRfa.u8State = MMI_nRfaStateDefManu;
			//MMI_tstRfa.u8Ctrl = MMI_nActRfaAqsSwitch();
			MMI_tstRfa.u8Ctrl = MMI_nActRfaSwitch();
			break;
		case MMI_nRfaStateMaxAc:
            MMI_tstAqs.u8State = MMI_nAqsStateMaxAcManu;/*add by Yang Shengli,2017-03-11*/
            //MMI_tstAqs.u8Ctrl = MMI_nAQSOff;/*add by Yang Shengli,2017-03-11*/
			MMI_tstRfa.u8State = MMI_nRfaStateMaxAcManu;
			//MMI_tstRfa.u8Ctrl = MMI_nActRfaAqsSwitch();
			MMI_tstRfa.u8Ctrl = MMI_nActRfaSwitch();
			break;
		case MMI_nRfaStateMaxAcManu:
			MMI_tstRfa.u8State = MMI_nRfaStateMaxAcManu;
			//MMI_tstRfa.u8Ctrl = MMI_nActRfaAqsSwitch();
			MMI_tstRfa.u8Ctrl = MMI_nActRfaSwitch();
			break;	
		default :
			break;
	}
    MMI_vAqsHistoryStateStore();/*add by Yang Shengli,2017-03-11*/
    MMI_vRfaHistoryStateStore();/*add by Yang Shengli,2017-03-11*/
}


/* ===========================================================================
* Function   : static void MMI_vTriggerEventTempDrInc(void)
* Description: Event trigger Function. SetTemp Dr side + event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventTempDrInc(void)
{
    MMI_tenSysState enSysState;

    enSysState = (MMI_tenSysState)MMI_u8SysState;
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_vSysHistoryStateRestore();
			break;
		case MMI_nSysStateMaxAc:
			MMI_vSysHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			MMI_vBctlHistoryStateRestore();
			break;
		case MMI_nBctlStateMaxAcManu: /*Exit MaxAc to Manual*/
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		case MMI_nBctlStateMaxAc:/*Exit MaxAc and restore*/
			MMI_vBctlHistoryStateRestore();
			break;			
		 
		default :/*else states do not change*/
			break;	
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			MMI_vAirdHistoryStateRestore();
			break;
		case MMI_nAirdStateMaxAc:/*Exit MaxAc and restore*/
			MMI_vAirdHistoryStateRestore();
			break;				
		 
		default :/*else states do not change*/
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{
		case MMI_nAcStateOff:
			MMI_vAcccHistoryStateRestore();
			break;
		case MMI_nAcStateMaxAc:
			MMI_vAcccHistoryStateRestore();
			break;	
			
		default :/*else states do not change*/ 
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateMaxAcManu:
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;	
		case MMI_nRfaStateMaxAc:
			MMI_vRfaHistoryStateRestore();
			break;
		default :/*else states do not change*/
			break;
	}

    if((enSysState != MMI_nSysStateOff) && (enSysState != MMI_nSysStateMaxAc))
    {
	    MMI_vActSetTempLeftInc();
        MMI_vSetTempHistoryStateStore();/*add by Yang Shengli,2017-03-11*/
    }
    else
    {
        /*Just wake up*/
    }

}


/* ===========================================================================
* Function   : static void MMI_vTriggerEventTempDrDec(void)
* Description: Event trigger Function. SetTemp Dr side - event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventTempDrDec(void)
{
    MMI_tenSysState enSysState;

    enSysState = (MMI_tenSysState)MMI_u8SysState;
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_vSysHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			MMI_vBctlHistoryStateRestore();
			break;
		 
		default :/*else states do not change*/
			break;	
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			MMI_vAirdHistoryStateRestore();
			break;
		 
		default :/*else states do not change*/
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{
		case MMI_nAcStateOff:
			MMI_vAcccHistoryStateRestore();
			break;
			
		default :/*else states do not change*/ 
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_vRfaHistoryStateRestore();
			break;
		default :/*else states do not change*/
			break;
	}

    if((enSysState != MMI_nSysStateOff) && (enSysState != MMI_nSysStateMaxAc))
    {
	    MMI_vActSetTempLeftDec();
        MMI_vSetTempHistoryStateStore();/*add by Yang Shengli,2017-03-11*/
    }
    else
    {
        /*Just wake up*/
    }
}

#if (SYC_ZONES == 2)
/* ===========================================================================
* Function   : static void MMI_vTriggerEventOnOff(void)
* Description: Event trigger Function. OFF event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventOnOff(void)
{
	if(MMI_u8SysState == MMI_nSysStateOff)
	{/***Exit Off State****/ 
		MMI_vAllHistoryStateRestore(); 
		/*Changed to Manual st while has been operated in def or MaxAc state*/
		MMI_vChange2ManuFromDefManuOrMaxAcManu();
	}
	else
	{/***Enter Off State****/ 
		/***Restore the history state from Def or MaxAc */
		MMI_vAllHistoryStateRestore();
		/*Changed to Manual st while has been operated in def or MaxAc state*/
		MMI_vChange2ManuFromDefManuOrMaxAcManu();
	
		/***History store before transfer to Off*/ 
		MMI_vAllHistoryStateStore();
		/***Chenge to Off state*/
		MMI_vActChange2Off();
	}

}

/* ===========================================================================
* Function   : static void MMI_vTriggerEventTempPsInc(void)
* Description: Event trigger Function. SetTemp Ps side + event 
* Takes      : Nothing
* Returns    : Nothing
*/

static void MMI_vTriggerEventTempPsInc(void)
{
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_vSysHistoryStateRestore();
			break;
		case MMI_nSysStateMaxAc:
			MMI_vSysHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			MMI_vBctlHistoryStateRestore();
			break;
		case MMI_nBctlStateMaxAcManu: /*Exit MaxAc to Manual*/
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		case MMI_nBctlStateMaxAc:/*Exit MaxAc and restore*/
			MMI_vBctlHistoryStateRestore();
			break;			
		 
		default :/*else states do not change*/
			break;	
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			MMI_vAirdHistoryStateRestore();
			break;
		case MMI_nAirdStateMaxAc:/*Exit MaxAc and restore*/
			MMI_vAirdHistoryStateRestore();
			break;				
		 
		default :/*else states do not change*/
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{
		case MMI_nAcStateOff:
			MMI_vAcccHistoryStateRestore();
			break;
		case MMI_nAcStateMaxAc:
			MMI_vAcccHistoryStateRestore();
			break;	
			
		default :/*else states do not change*/ 
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateMaxAcManu:
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;	
		case MMI_nRfaStateMaxAc:
			MMI_vRfaHistoryStateRestore();
			break;
		default :/*else states do not change*/
			break;
	}

	MMI_vActSetTempRightInc();

}


/* ===========================================================================
* Function   : static void MMI_vTriggerEventTempPsDec(void)
* Description: Event trigger Function. SetTemp Ps side - event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventTempPsDec(void)
{
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_vSysHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			MMI_vBctlHistoryStateRestore();
			break;
		 
		default :/*else states do not change*/
			break;	
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			MMI_vAirdHistoryStateRestore();
			break;
		 
		default :/*else states do not change*/
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{
		case MMI_nAcStateOff:
			MMI_vAcccHistoryStateRestore();
			break;
			
		default :/*else states do not change*/ 
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_vRfaHistoryStateRestore();
			break;
		default :/*else states do not change*/
			break;
	}

	MMI_vActSetTempRightDec();

}


/* ===========================================================================
* Function   : static void MMI_vTriggerEventDaul(void)
* Description: Event trigger Function. DUAL event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventDual(void)
{
	MMI_vActSetTempDual();
}

static void MMI_vTriggerEventAqs(void)
{
    if(MMI_tstAqs.u8Ctrl==MMI_nAQSOn)
	{
        //MMI_au8Array[MMI_nu8RecirMode]      = MMI_nRfaStateManual;
		//MMI_au8Array[MMI_nu8RecirControl]   =MMI_u8GetRfaValue(RFA_nu8Display);
		MMI_tstAqs.u8Ctrl     =MMI_nAQSOff;
        MMI_tstRfa.u8State = MMI_nRfaStateManual;
	}
	else //if(MMI_au8Array[MMI_nu8RecirControl]==MMI_nRecircFresh)
	{
		MMI_tstAqs.u8Ctrl     =MMI_nAQSOn;
		//MMI_au8Array[MMI_nu8RecirMode]      = MMI_nRfaStateAuto;
        MMI_tstRfa.u8State = MMI_nRfaStateAuto;
	}


	if (MMI_au8Array[MMI_nu8ModeControl] != (uint8)MMI_nAirdStateError)
	{ /* Just change intake mode to manual control  and update intake saved data, don't change other status*/
		//MMI_tstStatusSaveDef.nDefRecMode = MMI_au8Array[MMI_nu8RecirMode];
		//MMI_tstStatusSaveDef.nDefRecControl = MMI_au8Array[MMI_nu8RecirControl];
		//MMI_tstStatusSave.nRecMode = MMI_au8Array[MMI_nu8RecirMode];
		//MMI_tstStatusSave.nRecControl = MMI_au8Array[MMI_nu8RecirControl];

	}
	else
	{
		MMI_au8Array[MMI_nError] = True; /* Error */
	}

	//tan fumin
	//MMI_u8AqsBackUp=MMI_au8Array[MMI_nu8AqsRequest];
}


static void MMI_vTriggerEventPM25(void)
{
	MMI_u8Pm25Enable ^= True;
	if (MMI_u8Pm25Enable == True) /*PM25 Power off->on,180402*/
	{
		MMI_u8Pm25PopupOperationSts = True;
	}
	MMI_u8TurnOnByPm25 = False; /*debug:when turn on by pm25, then power off, after that will not popup*/
}
/* ===========================================================================
* Function   : static void MMI_vTriggerEventRearMode(void)
* Description: Event trigger Function. MODE event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventRearMode(void)
{
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_vSysHistoryStateRestore();
			break;
		case MMI_nSysStateAuto:
			MMI_u8SysState = MMI_nSysStateManual;
			break;
		case MMI_nSysStateMaxAc:
			MMI_vSysHistoryStateRestore();
			break;
		case MMI_nSysStateDefrost:
			MMI_vSysHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			MMI_vBctlHistoryStateRestore();
			break;
		case MMI_nBctlStateAuto:/*No Change*/ 
			break;
		case MMI_nBctlStateManual:/*No Change*/ 
			break;
		case MMI_nBctlStateDefrost:
			MMI_vBctlHistoryStateRestore();
			break;
		case MMI_nBctlStateDefManu: /*Exit Def and change to Manual*/	 	
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		case MMI_nBctlStateMaxAc:
			MMI_vBctlHistoryStateRestore();
			break;			
		case MMI_nBctlStateMaxAcManu: /*Exit MaxAc and change to Manual*/	
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		default :
			break;
			
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			MMI_vAirdHistoryStateRestore();
			break;
		case MMI_nAirdStateAuto:
			MMI_tstAird.u8State = MMI_nAirdStateManual;
			MMI_tstAird.u8Ctrl= MMI_nActAirdSwitchRear();
			break;
		case MMI_nAirdStateManual:
			MMI_tstAird.u8State = MMI_nAirdStateManual;
			MMI_tstAird.u8Ctrl = MMI_nActAirdSwitchRear();
			break;
		case MMI_nAirdStateDefrost:
			MMI_vAirdHistoryStateRestore();
			break;				
		case MMI_nAirdStateMaxAc:
			MMI_vAirdHistoryStateRestore();
			break;				
		/*else states do not change*/ 
		default :
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{	/*Off, MaxAc, Def shall be restroe*/
		case MMI_nAcStateOff:
		case MMI_nAcStateMaxAc:
		case MMI_nAcStateDefrost:
			MMI_vAcccHistoryStateRestore();
			break;
		case MMI_nAcStateDefManu: /*Exit Def and change to Manual*/	
			MMI_tstAccc.u8State = MMI_nAcStateManual;
			break;
		case MMI_nAcStateAuto:/*No Change*/ 
			break;
		case MMI_nAcStateManual:/*No Change*/ 
			break;						
		default :
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateAuto:/*No Change*/
			break;
		case MMI_nRfaStateManual:/*No Change*/
			break;
		case MMI_nRfaStateDefrost:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateDefManu:/*Exit Def and change to Manual*/
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;
		case MMI_nRfaStateMaxAc:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateMaxAcManu:
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;	
		default :
			break;
	}

}

/* ===========================================================================
* Function   : static void MMI_vTriggerEventMode(void)
* Description: Event trigger Function. MODE event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventMode(void)
{
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			//MMI_vSysHistoryStateRestore();/*states do not change,160523*/
			break;
		case MMI_nSysStateAuto:
			MMI_u8SysState = MMI_nSysStateManual;
			break;
		case MMI_nSysStateMaxAc:
			MMI_vSysHistoryStateRestore();
			break;
		case MMI_nSysStateDefrost:
			MMI_vSysHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			//MMI_vBctlHistoryStateRestore();/*states do not change,160523*/
			break;
		case MMI_nBctlStateAuto:/*No Change*/ 
			break;
		case MMI_nBctlStateManual:/*No Change*/ 
			break;
		case MMI_nBctlStateDefrost:
			MMI_vBctlHistoryStateRestore();
			break;
		case MMI_nBctlStateDefManu: /*Exit Def and change to Manual*/	 	
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		case MMI_nBctlStateMaxAc:
			MMI_vBctlHistoryStateRestore();
			break;			
		case MMI_nBctlStateMaxAcManu: /*Exit MaxAc and change to Manual*/	
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		default :
			break;
			
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			//MMI_vAirdHistoryStateRestore();/*states do not change,160523*/
			//MMI_tstAird.u8State = MMI_nAirdStateManual;
			//MMI_tstAird.u8Ctrl = MMI_nActAirdSwitchR();
			break;
		case MMI_nAirdStateAuto:
			MMI_tstAird.u8State = MMI_nAirdStateManual;
			MMI_tstAird.u8Ctrl= MMI_nActAirdSwitchR();
			break;
		case MMI_nAirdStateManual:
			MMI_tstAird.u8State = MMI_nAirdStateManual;
			MMI_tstAird.u8Ctrl = MMI_nActAirdSwitchR();
			break;
		case MMI_nAirdStateDefrost:
			MMI_vAirdHistoryStateRestore();
			break;				
		case MMI_nAirdStateMaxAc:
			MMI_vAirdHistoryStateRestore();
			break;				
		/*else states do not change*/ 
		default :
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{	/*Off, MaxAc, Def shall be restroe*/
		case MMI_nAcStateOff:
			/*states do not change,160523*/
			break;
		case MMI_nAcStateMaxAc:
		case MMI_nAcStateDefrost:
			MMI_vAcccHistoryStateRestore();
			break;
		case MMI_nAcStateDefManu: /*Exit Def and change to Manual*/	
			MMI_tstAccc.u8State = MMI_nAcStateManual;
			break;
		case MMI_nAcStateAuto:/*No Change*/ 
			break;
		case MMI_nAcStateManual:/*No Change*/ 
			break;						
		default :
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			//MMI_vRfaHistoryStateRestore();/*states do not change,160523*/
			break;
		case MMI_nRfaStateAuto:/*No Change*/
			break;
		case MMI_nRfaStateManual:/*No Change*/
			break;
		case MMI_nRfaStateDefrost:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateDefManu:/*Exit Def and change to Manual*/
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;
		case MMI_nRfaStateMaxAc:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateMaxAcManu:
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;	
		default :
			break;
	}

}

static MMI_tenAirdCtrl MMI_nActAirdSwitchRear(void)
{
	MMI_tenAirdCtrl enReturnAird;
	switch(MMI_tstAird.u8Ctrl)
	{
		case MMI_nAirdFace:
			enReturnAird = MMI_nAirdBilevel;
			break;
		case MMI_nAirdBilevel:
			enReturnAird = MMI_nAirdFloor;
			break;
		case MMI_nAirdFloor:
			enReturnAird = MMI_nAirdFace;//MMI_nAirdMixed;/*rear mode only 3 posi,160521*/
			break;
		case MMI_nAirdMixed:
			enReturnAird = MMI_nAirdFace;
			break;
		default :
			enReturnAird = MMI_nAirdFace;
			break;
	}
	return enReturnAird;
}

static void MMI_vActSetTempRightInc(void)
{
	if (MMI_u8SetTempPs <= MMI_nu8TempMaxVal)
	{
		MMI_u8SetTempPs += MMI_nTempStep;
	}
	
	if (MMI_u8SetTempPs < MMI_nu8TempMinVal)
	{
		MMI_u8SetTempPs = MMI_nu8TempMinVal;
	}
	else if (MMI_u8SetTempPs > MMI_nu8TempMaxVal)
	{
		MMI_u8SetTempPs = MMI_nu8SetTempHigh;
	}
	else
	{
		/*In normal range*/
	}
	
	MMI_u8DualCtrl = MMI_nDualOn;

}

static void MMI_vActSetTempRightDec(void)
{
	if (MMI_u8SetTempPs >= MMI_nu8TempMinVal)
	{
		MMI_u8SetTempPs -= MMI_nTempStep;
	}
	
	if (MMI_u8SetTempPs > MMI_nu8TempMaxVal)
	{
		MMI_u8SetTempPs = MMI_nu8TempMaxVal;
	}
	else if (MMI_u8SetTempPs < MMI_nu8TempMinVal)
	{
		MMI_u8SetTempPs = MMI_nu8SetTempLow;
	}
	else
	{
		/*In normal range*/
	}

	MMI_u8DualCtrl = MMI_nDualOn;
	
}

static void MMI_vActSetTempDual(void)
{
	if (MMI_u8SysState != MMI_nSysStateOff) /*no active under OFF,by zsc,160509*/
	{
		if (MMI_u8DualCtrl>1) /*error detect,160814*/
		{
			MMI_u8DualCtrl =0;
		}
		MMI_u8DualCtrl ^= True;
		
		if (MMI_u8DualCtrl == False)
		{
			MMI_u8SetTempPs = MMI_u8SetTempDr;
		}
		MMI_tstStateStore.nDualCtrl = MMI_u8DualCtrl;
		MMI_tstStateStore.nSetTempL = MMI_u8SetTempDr;
		MMI_tstStateStore.nSetTempR = MMI_u8SetTempPs;

        //MMI_vSysHistoryStateStore();
	}
	else
	{
	}
}
#endif

static void MMI_vTriggerEventIonLongPress(void)
{
    MMI_au8Array[MMI_nu8IonCtrl] = MMI_nIonStandby;
    MMI_au8Array[MMI_nu8IonMode] = MMI_nIonStateManual;
}
static void MMI_vTriggerEventIon(void)
{

    uint8 u8IonRunningStatus = MMI_au8Array[MMI_nu8IonCtrl];
    //uint8 u8IonRunningStatus = ION_u8GetValue(ION_nu8IONStsReq);/*170514*/
	if (MMI_nUseIonCfg == False)
	{
		MMI_au8Array[MMI_nu8IonCtrl] =MMI_nIonStandby;
		MMI_au8Array[MMI_nu8IonMode] = MMI_nIonStateOff;
		return;
	}	
    
    if(MMI_u8SysState== MMI_nSysStateOff)
	{
    	/***Restore the history state from Off,Def or MaxAc */
    	MMI_vAllHistoryStateRestore();

        MMI_au8Array[MMI_nu8IonCtrl] = MMI_nIonIonMode;
        MMI_au8Array[MMI_nu8IonMode] = MMI_nIonStateManual;
        
    	/***History store*/ 
    	MMI_vAllHistoryStateStore();
		return;
	}
    
	switch (u8IonRunningStatus)
	{
		case MMI_nIonStandby :
			MMI_au8Array[MMI_nu8IonCtrl] = MMI_nIonIonMode;
			break;
		//case MMI_nIonMute :
			//MMI_au8Array[MMI_nu8IonCtrl] = MMI_nIonAuto;
			//break;
		case MMI_nIonIonMode:
			MMI_au8Array[MMI_nu8IonCtrl] = MMI_nIonStandby;
            break;
		//case MMI_nIonHigh:
			//MMI_au8Array[MMI_nu8IonCtrl] = MMI_nIonStandby;
			//break;
		default :
			MMI_au8Array[MMI_nu8IonCtrl] = MMI_nIonStandby;
			break;					
	}

	MMI_au8Array[MMI_nu8IonMode] = MMI_nIonStateManual;
}

/* ===========================================================================
* Function   : static void MMI_vTriggerEventRearDefrost(void)
* Description: Event trigger Function. Rear-Def event 
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vTriggerEventRearDefrost(void)
{
	MMI_u8RearDefCtrl ^= True;
}


#ifdef Virtual_Key
static void MMI_vTriggerEventMmiSetTempDr(void)
{
	uint8 u8VkeySetTempDr = MMI_u8GetVkeySetTempLeft;
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_vSysHistoryStateRestore();
			break;
		case MMI_nSysStateMaxAc:
			MMI_vSysHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			MMI_vBctlHistoryStateRestore();
			break;
		case MMI_nBctlStateMaxAcManu: /*Exit MaxAc to Manual*/
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		case MMI_nBctlStateMaxAc:/*Exit MaxAc and restore*/
			MMI_vBctlHistoryStateRestore();
			break;			
		 
		default :/*else states do not change*/
			break;	
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			MMI_vAirdHistoryStateRestore();
			break;
		case MMI_nAirdStateMaxAc:/*Exit MaxAc and restore*/
			MMI_vAirdHistoryStateRestore();
			break;				
		 
		default :/*else states do not change*/
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{
		case MMI_nAcStateOff:
			MMI_vAcccHistoryStateRestore();
			break;
		case MMI_nAcStateMaxAc:
			MMI_vAcccHistoryStateRestore();
			break;	
			
		default :/*else states do not change*/ 
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateMaxAcManu:
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;	
		case MMI_nRfaStateMaxAc:
			MMI_vRfaHistoryStateRestore();
			break;
		default :/*else states do not change*/
			break;
	}

	if (u8VkeySetTempDr >=0x1e)// MMI_nu8TempMaxVal)
	{
		MMI_u8SetTempDr = 0xff;//MMI_nu8TempMaxVal;
	}
	else if(u8VkeySetTempDr <= 0)//MMI_nu8TempMinVal)
	{
		MMI_u8SetTempDr = 0;//MMI_nu8TempMinVal;
	}
	else
	{
		MMI_u8SetTempDr = u8VkeySetTempDr+34;//u8VkeySetTempDr;
	}
	
	if(MMI_u8DualCtrl == MMI_nDualOff)
	{
		MMI_u8SetTempPs = MMI_u8SetTempDr;
	}
    MMI_vSetTempHistoryStateStore();/*add by Yang Shengli,2017-03-11*/
}

static void MMI_vTriggerEventMmiSetTempPs(void)
{
	uint8 u8VkeySetTempPs = MMI_u8GetVkeySetTempRight;
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_vSysHistoryStateRestore();
			break;
		case MMI_nSysStateMaxAc:
			MMI_vSysHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			MMI_vBctlHistoryStateRestore();
			break;
		case MMI_nBctlStateMaxAcManu: /*Exit MaxAc to Manual*/
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		case MMI_nBctlStateMaxAc:/*Exit MaxAc and restore*/
			MMI_vBctlHistoryStateRestore();
			break;			
		 
		default :/*else states do not change*/
			break;	
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			MMI_vAirdHistoryStateRestore();
			break;
		case MMI_nAirdStateMaxAc:/*Exit MaxAc and restore*/
			MMI_vAirdHistoryStateRestore();
			break;				
		 
		default :/*else states do not change*/
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{
		case MMI_nAcStateOff:
			MMI_vAcccHistoryStateRestore();
			break;
		case MMI_nAcStateMaxAc:
			MMI_vAcccHistoryStateRestore();
			break;	
			
		default :/*else states do not change*/ 
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateMaxAcManu:
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;	
		case MMI_nRfaStateMaxAc:
			MMI_vRfaHistoryStateRestore();
			break;
		default :/*else states do not change*/
			break;
	}

	if (u8VkeySetTempPs >=0x1e)// MMI_nu8TempMaxVal)
	{
		MMI_u8SetTempPs = 0xff;//MMI_nu8TempMaxVal;
	}
	else if(u8VkeySetTempPs <= 0)//MMI_nu8TempMinVal)
	{
		MMI_u8SetTempPs = 0;//MMI_nu8TempMinVal;
	}
	else
	{
		MMI_u8SetTempPs = u8VkeySetTempPs+34;//u8VkeySetTempDr;
	}

    MMI_u8DualCtrl = MMI_nDualOn;

    MMI_vSetTempHistoryStateStore();/*add by Yang Shengli,2017-03-11*/
}

static void MMI_vTriggerEventMmiPM25PopupActive(void)
{
    uint8 u8Pm25PopupActive = 0u;
    u8Pm25PopupActive = MMI_u8GetVkeyPm25PopupActive;
    if(u8Pm25PopupActive == 1u)
    {
    	MMI_u8Pm25PopActive = True;
    	MMI_u8Pm25PopupKeepTime = MMI_Pm25KeepTime; /*keep 200ms*/
    }
    else
    {
    }
}
static void MMI_vTriggerEventMmiFan(void)
{
	uint8 u8VkeyBlwSpd = MMI_u8GetVkeyBlwSpd;
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_vSysHistoryStateRestore();
			MMI_u8SysState = MMI_nSysStateManual;
			break;
		case MMI_nSysStateAuto:
			MMI_u8SysState = MMI_nSysStateManual;
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			MMI_tstBctl.u8State= MMI_nBctlStateManual;
			MMI_tstBctl.u8Ctrl = u8VkeyBlwSpd;
			break;
		case MMI_nBctlStateAuto:
		case MMI_nBctlStateManual:
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			MMI_vActVkeyBlwCtrl();
			break;
		case MMI_nBctlStateDefrost:
		case MMI_nBctlStateDefManu:		
			MMI_tstBctl.u8State = MMI_nBctlStateDefManu;
			MMI_vActVkeyBlwCtrl();
			break;
		case MMI_nBctlStateMaxAc:
		case MMI_nBctlStateMaxAcManu:
			MMI_tstBctl.u8State = MMI_nBctlStateMaxAcManu;
			MMI_vActVkeyBlwCtrl();
			break;
		default :
			break;
			
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			MMI_vAirdHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{
		case MMI_nAcStateOff:
			MMI_vAcccHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_vRfaHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}

    MMI_vBctlHistoryStateStore();/*add by Yang Shengli,2017-03-11*/
	
}

static void MMI_vTriggerEventMmiAird(void)
{
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			//MMI_vSysHistoryStateRestore();/*states do not change,160523*/
			break;
		case MMI_nSysStateAuto:
			MMI_u8SysState = MMI_nSysStateManual;
			break;
		case MMI_nSysStateMaxAc:
			MMI_vSysHistoryStateRestore();
			break;
		case MMI_nSysStateDefrost:
			MMI_vSysHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			//MMI_vBctlHistoryStateRestore();/*states do not change,160523*/
			break;
		case MMI_nBctlStateAuto:/*No Change*/ 
			break;
		case MMI_nBctlStateManual:/*No Change*/ 
			break;
		case MMI_nBctlStateDefrost:
			MMI_vBctlHistoryStateRestore();
			break;
		case MMI_nBctlStateDefManu: /*Exit Def and change to Manual*/		
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		case MMI_nBctlStateMaxAc:
			MMI_vBctlHistoryStateRestore();
			break;			
		case MMI_nBctlStateMaxAcManu: /*Exit MaxAc and change to Manual*/	
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		default :
			break;
			
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			//MMI_vAirdHistoryStateRestore();/*states do not change,160523*/
			//MMI_tstAird.u8State = MMI_nAirdStateManual;
			//MMI_tstAird.u8Ctrl= MMI_nActVkeyAirdCtrl();
			break;
		case MMI_nAirdStateAuto:
			MMI_tstAird.u8State = MMI_nAirdStateManual;
			MMI_tstAird.u8Ctrl= MMI_nActVkeyAirdCtrl();
			break;
		case MMI_nAirdStateManual:
			MMI_tstAird.u8State = MMI_nAirdStateManual;
			MMI_tstAird.u8Ctrl = MMI_nActVkeyAirdCtrl();
			break;
		case MMI_nAirdStateDefrost:
			MMI_vAirdHistoryStateRestore();
            MMI_tstAird.u8State = MMI_nAirdStateManual;/*add by Yang Shengli,2017-03-11*/
			break;				
		case MMI_nAirdStateMaxAc:
			MMI_vAirdHistoryStateRestore();
            MMI_tstAird.u8State = MMI_nAirdStateManual;/*add by Yang Shengli,2017-03-11*/
			break;				
		/*else states do not change*/ 
		default :
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{	/*Off, MaxAc, Def shall be restroe*/
		case MMI_nAcStateOff:
			/*states do not change,160523*/
			break;
		case MMI_nAcStateMaxAc:
		case MMI_nAcStateDefrost:
			MMI_vAcccHistoryStateRestore();
			break;
		case MMI_nAcStateDefManu: /*Exit Def and change to Manual*/ 
			MMI_tstAccc.u8State = MMI_nAcStateManual;
			break;
		case MMI_nAcStateAuto:/*No Change*/ 
			break;
		case MMI_nAcStateManual:/*No Change*/ 
			break;						
		default :
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			//MMI_vRfaHistoryStateRestore();/*states do not change,160523*/
			
			break;
		case MMI_nRfaStateAuto:/*No Change*/
			break;
		case MMI_nRfaStateManual:/*No Change*/
			break;
		case MMI_nRfaStateDefrost:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateDefManu:/*Exit Def and change to Manual*/
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;
		case MMI_nRfaStateMaxAc:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateMaxAcManu:
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;	
		default :
			break;
	}

}

static void MMI_vTriggerEventTboxAirCleanerReq(void)
{
	uint8 u8IonRunningStatus = 0;
	u8IonRunningStatus = MMI_au8Array[MMI_nu8IonCtrl];
    uint8 u8VkeyAirCleanerReq = MMI_u8GetVkeyTboxAirCleanerReq;

    if(MMI_u8SysState== MMI_nSysStateOff)
	{
        if(u8VkeyAirCleanerReq == 0x02)
        {
        	/***Restore the history state from Off,Def or MaxAc */
        	MMI_vAllHistoryStateRestore();

            MMI_au8Array[MMI_nu8IonCtrl] = MMI_nIonIonMode;
            MMI_au8Array[MMI_nu8IonMode] = MMI_nIonStateManual;
            
        	/***History store*/ 
        	MMI_vAllHistoryStateStore();
        }
		return;
	}

    if(u8VkeyAirCleanerReq == 0x02)
    {
        MMI_au8Array[MMI_nu8IonCtrl] = MMI_nIonIonMode;
        MMI_au8Array[MMI_nu8IonMode] = MMI_nIonStateManual;
    }
    else if(u8VkeyAirCleanerReq == 0x01)
    {
        MMI_au8Array[MMI_nu8IonCtrl] = MMI_nIonStandby;
        MMI_au8Array[MMI_nu8IonMode] = MMI_nIonStateManual;
    }
    else
    {
    }
}
static void MMI_vTriggerEventTboxTempReq(void)
{
	uint8 u8VkeySetTemp = MMI_u8GetVkeyTboxSetTemp;
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_vSysHistoryStateRestore();
			break;
		case MMI_nSysStateMaxAc:
			MMI_vSysHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			MMI_vBctlHistoryStateRestore();
			break;
		case MMI_nBctlStateMaxAcManu: /*Exit MaxAc to Manual*/
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			break;
		case MMI_nBctlStateMaxAc:/*Exit MaxAc and restore*/
			MMI_vBctlHistoryStateRestore();
			break;			
		 
		default :/*else states do not change*/
			break;	
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			MMI_vAirdHistoryStateRestore();
			break;
		case MMI_nAirdStateMaxAc:/*Exit MaxAc and restore*/
			MMI_vAirdHistoryStateRestore();
			break;				
		 
		default :/*else states do not change*/
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{
		case MMI_nAcStateOff:
			MMI_vAcccHistoryStateRestore();
			break;
		case MMI_nAcStateMaxAc:
			MMI_vAcccHistoryStateRestore();
			break;	
			
		default :/*else states do not change*/ 
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_vRfaHistoryStateRestore();
			break;
		case MMI_nRfaStateMaxAcManu:
			MMI_tstRfa.u8State = MMI_nRfaStateManual;
			break;	
		case MMI_nRfaStateMaxAc:
			MMI_vRfaHistoryStateRestore();
			break;
		default :/*else states do not change*/
			break;
	}

	if (u8VkeySetTemp >=0x1e)// MMI_nu8TempMaxVal)
	{
		MMI_u8SetTempDr = 0xff;//MMI_nu8TempMaxVal;
	}
	else if(u8VkeySetTemp <= 0)//MMI_nu8TempMinVal)
	{
		MMI_u8SetTempDr = 0;//MMI_nu8TempMinVal;
	}
	else
	{
		MMI_u8SetTempDr = u8VkeySetTemp+34;//u8VkeySetTempDr;
	}
	
    MMI_u8SetTempPs = MMI_u8SetTempDr;
    MMI_u8DualCtrl = MMI_nDualOff;
    MMI_vSetTempHistoryStateStore();/*add by Yang Shengli,2017-03-11*/
}
static void MMI_vTriggerEventTboxAirConditionerReq(void)
{
    uint8 u8VkeyAirConditionerReq = MMI_u8GetVkeyTboxAirConditionerReq;

    //if(MMI_u8SysState == MMI_nSysStateOff)
    if(u8VkeyAirConditionerReq == 0x02)
	{/***Exit Off State****/ 
		MMI_vAllHistoryStateRestore(); 
		/*Changed to Manual st while has been operated in def or MaxAc state*/
		MMI_vChange2ManuFromDefManuOrMaxAcManu();
	}
	else if(u8VkeyAirConditionerReq == 0x01)
	{/***Enter Off State****/ 
		/***Restore the history state from Def or MaxAc */
		MMI_vAllHistoryStateRestore();
		/*Changed to Manual st while has been operated in def or MaxAc state*/
		MMI_vChange2ManuFromDefManuOrMaxAcManu();
	
		/***History store before transfer to Off*/ 
		MMI_vAllHistoryStateStore();
		/***Chenge to Off state*/
		MMI_vActChange2Off();
	}
    else
    {
    }
}

/* ===========================================================================
* Function   : static void MMI_vTriggerEventMmiDrvHeat(void)
* Description: Function used for unused buttons in action tables
* Takes      : Nothing
* Returns    : Nothing
*/
 static void MMI_vTriggerEventMmiDrvHeat(void)
{
    uint8 u8VkeyShcLStateFromeBus = MMI_u8GetVkeyShcLState;
    uint8 u8VkeyShcLStateFromeShc = MMI_u8GetShcLDisplayInfo();

    if(((u8VkeyShcLStateFromeBus == 0u) && u8VkeyShcLStateFromeShc == 1u) \
        || ((u8VkeyShcLStateFromeBus == 1u) && u8VkeyShcLStateFromeShc == 0u))
    {
        MMI_u8ShlFromeBusCtrl = MMI_nSeatHeatLeft1;
    }
    else
    {
    }
}

/* ===========================================================================
* Function   : static void MMI_vTriggerEventMmiPassHeat(void)
* Description: Function used for unused buttons in action tables
* Takes      : Nothing
* Returns    : Nothing
*/
 static void MMI_vTriggerEventMmiPassHeat(void)
{
    uint8 u8VkeyShcRStateFromeBus = MMI_u8GetVkeyShcRState;
    uint8 u8VkeyShcRStateFromeShc = MMI_u8GetShcRDisplayInfo();

    if(((u8VkeyShcRStateFromeBus == 0u) && u8VkeyShcRStateFromeShc == 1u)\
        || ((u8VkeyShcRStateFromeBus == 1u) && u8VkeyShcRStateFromeShc == 0u))
    {
        MMI_u8ShrFromeBusCtrl = MMI_nSeatHeatRight1;
    }
    else
    {
    }
}

/* ===========================================================================
* Function   : static void MMI_vTriggerEventMmiPM25PopupOperationSts(void)
* Description: Function used for unused buttons in action tables
* Takes      : Nothing
* Returns    : Nothing
*/
 static void MMI_vTriggerEventMmiPM25PopupOperationSts(void)
{
    uint8 u8Pm25Switch = 0u;
    u8Pm25Switch = MMI_u8GetVkeyPm25PopupOperationSts;

    if(u8Pm25Switch == 1u)
    {
        MMI_u8Pm25PopupOperationSts = False;
    }
    else
    {
    }
}
#endif


#ifdef Used_RearPanel
static void MMI_vTriggerEventRearBlwInc(void)
{
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_vSysHistoryStateRestore();
			MMI_u8SysState = MMI_nSysStateManual;
			break;
		case MMI_nSysStateAuto:
			MMI_u8SysState = MMI_nSysStateManual;
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			MMI_tstBctl.u8State= MMI_nBctlStateManual;
			MMI_tstBctl.u8Ctrl = MMI_nBctlSpeed1;
			break;
		case MMI_nBctlStateAuto:
		case MMI_nBctlStateManual:
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			MMI_vActBctlSpdIncLimit();
			break;
		case MMI_nBctlStateDefrost:
		case MMI_nBctlStateDefManu: 	
			MMI_tstBctl.u8State = MMI_nBctlStateDefManu;
			MMI_vActBctlSpdIncLimit();
			break;
		case MMI_nBctlStateMaxAc:
		case MMI_nBctlStateMaxAcManu:
			MMI_tstBctl.u8State = MMI_nBctlStateMaxAcManu;
			MMI_vActBctlSpdIncLimit();
			break;
		default :
			break;
			
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			MMI_vAirdHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{
		case MMI_nAcStateOff:
			MMI_vAcccHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_vRfaHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
}



static void MMI_vTriggerEventRearBlwDec(void)
{
	/***System state transfer & Action****/ 
	switch(MMI_u8SysState)
	{
		case MMI_nSysStateOff:
			MMI_vSysHistoryStateRestore();
			MMI_u8SysState = MMI_nSysStateManual;
			break;
		case MMI_nSysStateAuto:
			MMI_u8SysState = MMI_nSysStateManual;
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***BCTL state transfer & Action****/ 
	switch(MMI_tstBctl.u8State)
	{
		case MMI_nBctlStateOff:
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			MMI_tstBctl.u8Ctrl = MMI_nBctlSpeed1;
			break;
		case MMI_nBctlStateAuto:
		case MMI_nBctlStateManual:
			MMI_tstBctl.u8State = MMI_nBctlStateManual;
			MMI_vActBctlSpdDecLimit();
			break;
		case MMI_nBctlStateDefrost:
		case MMI_nBctlStateDefManu: 	
			MMI_tstBctl.u8State = MMI_nBctlStateDefManu;
			MMI_vActBctlSpdDecLimit();
			break;
		case MMI_nBctlStateMaxAc:
		case MMI_nBctlStateMaxAcManu:
			MMI_tstBctl.u8State = MMI_nBctlStateMaxAcManu;
			MMI_vActBctlSpdDecLimit();
			break;
		default :
			break;
			
	}
	/***AIRD state transfer & Action****/
	switch(MMI_tstAird.u8State)
	{
		case MMI_nAirdStateOff:
			MMI_vAirdHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***ACCC state transfer & Action****/ 
	switch(MMI_tstAccc.u8State)
	{
		case MMI_nAcStateOff:
			MMI_vAcccHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
	/***RFA state transfer & Action****/ 
	switch(MMI_tstRfa.u8State)
	{
		case MMI_nRfaStateOff:
			MMI_vRfaHistoryStateRestore();
			break;
		/*else states do not change*/ 
		default :
			break;
	}
}



static void MMI_vTriggerEventTempRearUp(void)
{

}


static void MMI_vTriggerEventTempRearDn(void)
{

}
#endif


void MMI_vClrLeftShcKeyState(void)
{
	MMI_u8ShlCtrl = False;
    MMI_u8ShlFromeBusCtrl = False;
}

void MMI_vClrRightShcKeyState(void)
{
	MMI_u8ShrCtrl = False;
    MMI_u8ShrFromeBusCtrl = False;
}

uint8 MMI_u8GetValue( MMI_tenu8VarNum Num )
{
	if ( Num < MMI_nu8Max )
	{
		return MMI_au8Array[Num];
	}
	else
	{
		return MMI_au8Array[MMI_nu8Max-1];
	}

}

uint16 MMI_u16GetValue( MMI_tenu16VarNum Num )
{
	if ( Num < MMI_nu16Max )
	{
		return MMI_au16Array[Num];
	}
	else
	{
		return MMI_au16Array[MMI_nu16Max-1];
	}
}



Std_ReturnType MMI_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord)
{
	uint8 u8Result=RTE_E_OK;
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0x81:
			case 0xA1:
				MMI_vResetDefaultValue();		
				MMI_vAllHistoryStateStore();
				MMI_vUpdateSaveBuffer();
				MMI_vWriteMemData(); 
				break;
			default:
                u8Result= RTE_E_INVALID;
				break;
		}
	}
	else
	{
		
	}
        return u8Result;
}

static MMI_tenRfaCtrl MMI_vChangeAqsState(uint8 u8Rfa)
{
    uint8 u8ReturnValue;
    
	if(MMI_tstAqs.u8Ctrl==MMI_nAQSOn)
	{
		MMI_tstAqs.u8Ctrl=MMI_nAQSOff;
        if(u8Rfa == MMI_nRfaRecirc)
        {
            u8ReturnValue = MMI_nRfaFresh;
        }
        else
        {
            u8ReturnValue = u8Rfa;
        }
	}
	else if(u8Rfa == MMI_nRfaRecirc)
	{
		MMI_tstAqs.u8Ctrl=MMI_nAQSOn;
        MMI_tstRfa.u8State = MMI_nRfaStateAuto;
        u8ReturnValue = u8Rfa;
        //u8ReturnValue = MMI_nRfaFresh;
	}
	else
	{
		u8ReturnValue = MMI_nRfaRecirc;
	}

    return (MMI_tenRfaCtrl)u8ReturnValue;
}

 void MMI_vTurnOnByPm25Exceed(void)
 {
 	MMI_vTriggerEventAuto();
	MMI_u8OperationAfterTurnOn = False;
 }

  void MMI_vTurnOffByIonFinish(void)
 {
 	if (MMI_u8OperationAfterTurnOn == False)
 	{
 		MMI_vTriggerEventOff();
 	}
 }
static void MMI_vTakeActionPm25PoupOperationSts(void)
{
	MMI_u8Pm25PopupOperationSts = False;
}

/* ===========================================================================
* Function   : static void MMI_vOFFToON(void)
* Description: Used to turn on controller from off state.
* Takes      : Nothing
* Returns    : Nothing
*/
static void MMI_vOFFToON(void)
{
#if 0
	if(MMI_Mode.MMI_stCurrentStatus.mode==MMI_nSysStateOff)
	{
		MMI_Mode.MMI_stCurrentStatus.mode=MMI_Mode.MMI_stOFFpreStatus.mode;
	}
	if(MMI_Aird.MMI_stCurrentStatus.mode==MMI_nAirdStateOff)
	{
		MMI_Aird.MMI_stCurrentStatus.mode=MMI_Aird.MMI_stOFFpreStatus.mode;
		MMI_Aird.MMI_stCurrentStatus.controlsts=MMI_Aird.MMI_stOFFpreStatus.controlsts;
	}
	if(MMI_RFA.MMI_stCurrentStatus.mode==MMI_nRfaStateOff)
	{
		MMI_RFA.MMI_stCurrentStatus.mode=MMI_RFA.MMI_stOFFpreStatus.mode;
		MMI_RFA.MMI_stCurrentStatus.controlsts=MMI_RFA.MMI_stOFFpreStatus.controlsts;
	}
	if(MMI_AC.MMI_stCurrentStatus.mode==MMI_nAcStateOff)
	{
		MMI_AC.MMI_stCurrentStatus.mode=MMI_AC.MMI_stOFFpreStatus.mode;
		MMI_AC.MMI_stCurrentStatus.controlsts=MMI_AC.MMI_stOFFpreStatus.controlsts;
	}
	/*
	if(MMI_ION.MMI_stCurrentStatus.mode==MMI_nIonStateOff)
	{
		MMI_ION.MMI_stCurrentStatus.mode=MMI_ION.MMI_stOFFpreStatus.mode;
		MMI_ION.MMI_stCurrentStatus.controlsts=MMI_ION.MMI_stOFFpreStatus.controlsts;
	}
	*/
	if(MMI_BCTL.MMI_stCurrentStatus.mode==MMI_nBctlStateOff)
	{
		MMI_BCTL.MMI_stCurrentStatus.mode=MMI_BCTL.MMI_stOFFpreStatus.mode;
		MMI_BCTL.MMI_stCurrentStatus.controlsts=MMI_BCTL.MMI_stOFFpreStatus.controlsts;
		if((MMI_BCTL.MMI_stCurrentStatus.mode==MMI_nBctlStateOff)||(MMI_BCTL.MMI_stCurrentStatus.controlsts==MMI_nBctlOff))
		{
			MMI_Mode.MMI_stCurrentStatus.mode=MMI_nSysStateManual;
			MMI_BCTL.MMI_stCurrentStatus.mode=MMI_nBctlStateManual;
			MMI_BCTL.MMI_stCurrentStatus.controlsts=MMI_nBctlSpeed1;
		}
	}
#endif
}

void MMI_u16ClearKnobOrKeyOperationFlag( void )
{
    MMI_u16KnobOrKeyOperationFlag = 0u;
}

uint16 MMI_u16GetKnobOrKeyOperationFlag( void )
{
    return MMI_u16KnobOrKeyOperationFlag;
}

static void MMI_vVehicleConfig(void)
{
	if (MMI_nUseAqsCfg == False)
	{
		MMI_au8Array[MMI_nu8AqsRequest] =MMI_nAQSOff;
	}	

	//if (MMI_nUseRcpCfg == False)
	//{
		//MMI_au8Array[MMI_nRearLock] =False;
	//}	

	if (MMI_nUseIonCfg == False)
	{
		MMI_au8Array[MMI_nu8IonCtrl] =MMI_nIonStandby;
		MMI_au8Array[MMI_nu8IonMode] = MMI_nIonStateOff;
	}
}

/*****************************************************************************
* EOF:
*****************************************************************************/


