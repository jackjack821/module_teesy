/**************************** .FILE_HEADER_BEGIN *****************************
 .FILE; [ CANNMAPP1c1.c]
 .Author; [ Liu Fuguang]
 .Date; 2016/12/30
 .Update Time; 11:43:29
 .Gen File Name: SX11P_LIN_V1.0_2016-12-29.xlsx
****************************** .FILE_HEADER_END ******************************/
#define CANNMAPP                          /* Name of the Module                */
/* HEADER-FILES (Only those that are needed in this file) */
#include "General.h"
/* Foreign headerfiles */
#include "desc.h"
#include "appdesc.h"
#include "IGN.H"
#include "POW.H"
#include "SBC.H"
//#include "VTM.H"
/* Own headerfiles */
#include "CanNm.h"
#include "NmCbdWrp.h"     
#include "CANapp.h"
#include "CANNMAPP.H"
#include "CANNMAPP_cfg.H"

/* internal variable...*/

/**Local Varibles Definition *******************************************/
typedef enum
{
	CANNMAPP_nWakeUp_Local = 0,
	CANNMAPP_nWakeUp_Bus	
}CANNMAPP_tenWakeUpReason;
enum
{
	NmUserData_nClearWakeSource = 0,
	NmUserData_nWakeByK15,
	NmUserData_nWakeByBus
};

static uint16 CANNMAPP_au16Array[CANNMAPP_nu16Max];

static uint16 CANNMAPP_u16WakeUpReason;
static CANNMAPP_tstNmUserData CANNMAPP_stNmUserData;
static uint16 u16BusIdleTimer=0;
#define CANNMAPP_WakeUpReasonSet(Index)		(CANNMAPP_u16WakeUpReason |= (0x0001 << Index))
#define CANNMAPP_WakeUpReasonClr(Index)		(CANNMAPP_u16WakeUpReason &= (~(0x0001 << Index)))
#define CANNMAPP_WakeUpReasonGet(Index)		((CANNMAPP_u16WakeUpReason>>Index) & 0x0001)
#define CANNMAPP_AllWakeUpReasonClr()		(CANNMAPP_u16WakeUpReason = 0x0000)

#define CANNMAPP_MsgDlcErrSet(Index)		(CANNMAPP_au16Array[CANNMAPP_u16MsgDlcErr] |= (0x0001 << Index))
#define CANNMAPP_MsgDlcErrClr(Index)		(CANNMAPP_au16Array[CANNMAPP_u16MsgDlcErr] &= (~(0x0001 << Index)))
#define CANNMAPP_MsgValidSet(Index)		    (CANNMAPP_au16Array[CANNMAPP_u16MsgValid] |= (0x0001 << Index))
#define CANNMAPP_MsgValidClr(Index)		    (CANNMAPP_au16Array[CANNMAPP_u16MsgValid] &= (~(0x0001 << Index)))
/**Local Functions Declear ************************************************************/

/****************************************************************/
/**                                                 ***********************************/
/**  UserData Setting Functions           ***********************************/
/**                                                 ***********************************/
/****************************************************************/
static void CANNMAPP_vSetUserData_WakeSource(uint8 u8WakeUpSource);
static void CANNMAPP_vSetUserData_ClrWakeSource(void);
static void CANNMAPP_vSetUserData_StayWakeReason(void);
static void CANNMAPP_vSetUserData_NetState(void);
static void CANNMAPP_vUpdateUserData(void);
void CANNM_vBusIdleCheck(void);
/****************************************************************/
/**                                                 ***********************************/
/**  Init Function  Functions                **********************************/
/**                                                 ***********************************/
/****************************************************************/
static void CANNMAPP_vHardwareInit(void);
static void CANNMAPP_vPoweronInit(void);

/****************************************************************/
/**                                                 ***********************************/
/**  Other Setting Functions                **********************************/
/**                                                 ***********************************/
/****************************************************************/
static void CANNMAPP_vEnableExInterrupt(void);
static void CANNMAPP_vGetState(void);
static void CANNMAPP_vLocalWakeUpDetect(void);

static void CANNMAPP_vLocalNMRequst(void);
static void CANNMAPP_vGotoSleepMode(void);
static void CANNMAPP_vNetWorkMode(void);

extern void CANCCL_vClrEnableSleepFlg(void);

void CANNM_vMsgDlcCheck(CanRxInfoStructPtr rxStruct);
/*****************************************************************************
* Function   : void CANNMAPP_vHardwareInit (void)
* Description: Lin hardware configuration
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void CANNMAPP_vHardwareInit(void)
{
      /* set fCAN:Main Osc -> CAN */
      	PROTCMD1=0xa5;
      	CKSC_ICANOSCD_CTL=0x01;
      	CKSC_ICANOSCD_CTL=~0x01;
      	CKSC_ICANOSCD_CTL=0x01;
	while (PROTS1 ==0x01);
	//#if 0
	/* Set CAN0TX as P0_0 and CAN0RX as P0_1 */
	/* Set CAN0TX as P0_4 and CAN0RX as P0_5 for GET demo,190423 */
    	PMC0 |= 0x0030; /* Alternative Functions */                                                 
    	PFC0 |= (0x0000); /* Alternative 2 */                                                     
    	PM0 &= ~(1<<4);    /* P0_0 CANTX     Output */                                              
    	PM0 |= 1<<5;  /* P0_1 CANRX     Input */
	P0 |= 0x0030; /* set Tx/Rx port high level*/
//#endif
}
/*****************************************************************************
* Function   : void CANNMAPP_vPoweronInit (void)
* Description: 
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void CANNMAPP_vPoweronInit(void)
{
	CANNMAPP_vHardwareInit();
	__DI();
	CanInitPowerOn();/*CAN Driver Init*/
	CanNm_InitMemory();/*Nm function Memory Init*/
	CanNm_Init(0);	/* Nm Function Init*/
	CbdWrpInit(0);   /*Wrapper Init*/
	TpInitPowerOn(); /*Tp Init*/
	DescInitPowerOn(0); /* Diag Init*/
	__EI();
	CANNMAPP_au16Array[CAMNMAPP_nu16CanSleep] = False;
    CANNMAPP_au16Array[CANNMAPP_u16MsgDlcErr] = False;
    CANNMAPP_au16Array[CANNMAPP_u16MsgValid] = False;
	u16BusIdleTimer=300;
    CANNMAPP_stNmUserData.StayWakeByDiag = False;
	CANAPP_vReset();
}
/*****************************************************************************
* Function   : void CANNMAPP_vInit (void)
* Description: 
* Call	     : Local
* Returns   : Nothing
******************************************************************************/


#if CANNMAPP_McuStopModeUse == Yes	
/*****************************************************************************
* Function   : void CANNMAPP_vWakeFromSTOPmodeSetting (void)
* Description: Set the CAN Interrupt as Externel Interrupt, so the MCU will be able to wake up
			from STOP mode by BUS activity.
* Call	     : Local
******************************************************************************/
static void CANNMAPP_vWakeFromSTOPmodeSetting(void)
{
	#if 0
	FCLA0CTL0_INTPL = 0x02; /* INTP0 Interrupt is generated on falling edge */
	MKP0 = 0; /*INTP0 Enble*/
   	WUFMSK0 &=~(1<<5); /*Allow MCU be wake up by INTP_0 from STOP mode*/
	#endif

//	WUFMSK_ISO0 &=~(1<<2); /*Allow MCU be wake up by INTRCANGRECC from STOP mode*/
//	WUFMSK_ISO0 &=~(1<<2); /*Allow MCU be wake up by INTRCANGRECC from STOP mode*/
	
}

/*****************************************************************************
* Function   : void CANNMAPP_vWakeFromSTOPmodeInterrupt (void)
* Description: CAN Interrupt service Function.
* Call	     : Local
******************************************************************************/
#pragma ghs interrupt	
void CANNMAPP_vWakeFromSTOPmodeInterrupt(void)
{
	//WUFC0  &=~(1<<5);
	//CANNMAPP_WakeUpReasonSet(CANNMAPP_nWakeUp_Bus);
	//CANCCL_vClrEnableSleepFlg();
}
#endif
static void CANNMAPP_vEnableExInterrupt(void)
{
   // MKP0 = 0;
   // FCLA0CTL0_INTPL = 0x02;
  //WUFMSK0 &=~(1<<5); /*INTP_2 for CAN2*/   
}
/*****************************************************************************
* Function   : void CANNMAPP_vReset (void)
* Description: Called in LINCCL Module Reset container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void CANNMAPP_vReset(void)
{
	CANNMAPP_vPoweronInit();
	CANCCL_vClrEnableSleepFlg();
	CANNMAPP_au16Array[CANNMAPP_u16BusIdle]=False;
    CANNMAPP_au16Array[CANNMAPP_u16MsgDlcErr]=False;
    CANNMAPP_au16Array[CANNMAPP_u16MsgValid]=False;
}
/*****************************************************************************
* Function   : void CANNMAPP_vMain_10ms (void)
* Description: Called in LINCCL Module 10ms container. 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
void CANNMAPP_vMain_10ms(void)
{    
    if((CANNMAPP_u16VolLo==False)&&(CANNMAPP_u16VolHi==False))
    {
        CanSetActive();
    }
    else
    {
        CanSetPassive();
    }
    CANNMAPP_vGetState();
    CANNMAPP_vLocalWakeUpDetect();
    CANNM_vBusIdleCheck();
    if((CANNMAPP_au16Array[CANNMAPP_nu16NmMode]==NM_MODE_BUS_SLEEP)||\
        (CANNMAPP_au16Array[CANNMAPP_nu16NmMode]==NM_MODE_PREPARE_BUS_SLEEP))
    {
        CANAPP_vClearSendMsgTmr();
        if(CANNMAPP_WakeUpReasonGet(CANNMAPP_nWakeUp_Local) == True)            
        {
            CANNMAPP_vSetUserData_WakeSource(NmUserData_nWakeByK15);
            CANNMAPP_vLocalNMRequst();
        }
        else
        {
            CANNMAPP_vSetUserData_WakeSource(NmUserData_nWakeByBus);
            CANNMAPP_vGotoSleepMode();
        }
    }
    else
    {/*NetWork Mode*/
        CANNMAPP_vNetWorkMode();
    }
	CbdWrpTask(0);
	CanNm_MainFunction_0();
	CanTask();
}
/*****************************************************************************
* Function   : void CANNMAPP_vLocalNMRequst (void)
* Description: Use For requst NM.
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void CANNMAPP_vLocalNMRequst(void)
{
    uint8 u8ReturnValue;
    if(CANNMAPP_au16Array[CAMNMAPP_nu16CanSleep] == True)
    {/*Can has sleep aready with no wakeup source*/
        CANNMAPP_vPoweronInit();
    }
    if(CANNMAPP_au16Array[CAMNMAPP_nu16CanSleep] == False)
    {
        CANNMAPP_vSetUserData_StayWakeReason();	
        u8ReturnValue = CanNm_NetworkRequest(0);
        if(u8ReturnValue== NM_E_OK )/*Wake up Network Management OK */
        {
            CANAPP_vReset();
        } 
    }
}
/*****************************************************************************
* Function   : void CANNMAPP_vGotoSleepMode(void)
* Description: Use For setting for SleepMode.
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void CANNMAPP_vGotoSleepMode(void)
{
	if(CANNMAPP_au16Array[CANNMAPP_nu16NmMode]==NM_MODE_BUS_SLEEP)
	{
		if(CANNMAPP_au16Array[CAMNMAPP_nu16CanSleep] == False)
		{
			__DI();
			if(CanSleep() == kCanOk)
			{
				CANNMAPP_au16Array[CAMNMAPP_nu16CanSleep]  = True;
                CANNMAPP_au16Array[CANNMAPP_u16MsgDlcErr] = False;
                CANNMAPP_au16Array[CANNMAPP_u16MsgValid] = False;
				CANNMAPP_vEnableExInterrupt();
			}
			__EI();
		}
		else
		{
		}
	}
	
}
/*****************************************************************************
* Function   : void CANNMAPP_vNetWorkMode(void)
* Description: Use For NetWork calculation.
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void CANNMAPP_vNetWorkMode(void)
{/*NetWork Mode*/
    if((CANNMAPP_WakeUpReasonGet(CANNMAPP_nWakeUp_Local) == True)&&\
        (CANNMAPP_stNmUserData.StayWakeByK15 == False)&&\
        (CANNMAPP_au16Array[CANNMAPP_nu16NmCurrState]!=NM_STATE_NORMAL_OPERATION))
    {/*Change to normal Operation State*/
        if(CanNm_NetworkRequest(0) == NM_E_OK)
    	{
    		/*change to normal*/
    	}            
    }
    else if(CANNMAPP_au16Array[CANNMAPP_nu16NmCurrState]==NM_STATE_READY_SLEEP)
    {
        if(CANNMAPP_stNmUserData.StayWakeByDiag== True)
        {
            if(CanNm_NetworkRequest(0) == NM_E_OK)
        	{
        		/*change to normal*/
        	}  
        }
    }
    CANNMAPP_vSetUserData_StayWakeReason();	/**UserData Setting : Stay WakeUpReason*********/	
    if((CANNMAPP_stNmUserData.StayWakeByK15 == False)&&\
        (CANNMAPP_stNmUserData.StayWakeByDiag== False))
    {
    	if(CanNm_NetworkRelease(0) == NM_E_OK)
    	{
    		//CANNMAPP_enNmState = CANNMAPP_nNOStoRSS;
    	}
    }
    CANNMAPP_au16Array[CAMNMAPP_nu16CanSleep] = False;
}
/*****************************************************************************
* Function   : void CANNMAPP_u16GetValue (void)
* Description: 
* Call	     : Global
* Returns   : Nothing
******************************************************************************/
uint16 CANNMAPP_u16GetValue(CANNMAPP_tenu16VarNum enIndex)
{
	if(enIndex < CANNMAPP_nu16Max)
	{
		return (CANNMAPP_au16Array[enIndex]);
	}
	else
	{
		return (CANNMAPP_au16Array[CANNMAPP_nu16Max-1]);
	}
}


/*****************************************************************************
* Function   : void CANNMAPP_vClearBusoffError (void)
* Description: Called by DIAG to Clear Busoff  Error Flag
* Call	     : DIAG
* Returns   : Nothing
******************************************************************************/
void CANNMAPP_vClearBusoffError(void)
{
 	CANNMAPP_au16Array[CANNMAPP_nu16BusOffStart] = False;
	CANNMAPP_au16Array[CANNMAPP_nu16BusOffConf] = False;
}
/*****************************************************************************
* Function   : void CANNMAPP_vClearStayWakeByDiag (void)
* Description: 
* Call	     : DIAG init
* Returns   : Nothing
******************************************************************************/
void CANNMAPP_vClearStayWakeByDiag(void)
{
	CANNMAPP_stNmUserData.StayWakeByDiag=0;
}
/*****************************************************************************
* Function   : void CANNMAPP_vSetWakeupReasonByDiag (void)
* Description: Called by DIAG to Clear Busoff  Error Flag
* Call	     : DIAG
* Returns   : Nothing
******************************************************************************/
void CANNMAPP_vSetWakeupReasonByDiag(void)
{
    CANNMAPP_stNmUserData.StayWakeByDiag = True;

}
/*****************************************************************************
* Function   : void CANNMAPP_vClrWakeupReasonByDiag (void)
* Description: Called by DIAG to Clear Busoff  Error Flag
* Call	     : DIAG
* Returns   : Nothing
******************************************************************************/
void CANNMAPP_vClrWakeupReasonByDiag(void)
{
    CANNMAPP_stNmUserData.StayWakeByDiag = False;
}

/*****************************************************************************
* Function   : void CANNMAPP_vSetUserData_WakeSource (void)
* Description: Use For Setting the UserData of Wake Up Source.
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void CANNMAPP_vSetUserData_WakeSource(uint8 u8WakeUpSource)
{	
    //if(CANNMAPP_stNmUserData.WakeSource == NmUserData_nClearWakeSource)
    {
        if(NmUserData_nWakeByK15==u8WakeUpSource)
        {
            CANNMAPP_stNmUserData.WakeSource = NmUserData_nWakeByK15;
        }
        else
        {
            CANNMAPP_stNmUserData.WakeSource = NmUserData_nWakeByBus;
        }
        
    }
    CANNMAPP_vUpdateUserData();
}
/*****************************************************************************
* Function   : static void CANNMAPP_vSetUserData_ClrWakeSource(void)
* Description: Use For clear the UserData of Wake Up Source.
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void CANNMAPP_vSetUserData_ClrWakeSource(void)
{	
    CANNMAPP_stNmUserData.WakeSource = NmUserData_nClearWakeSource;
    CANNMAPP_vUpdateUserData();
}
/*****************************************************************************
* Function   : void CANNMAPP_vSetUserData_StayWakeReason (void)
* Description: Use For Setting the UserData of Stay Wake Up Reason.
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void CANNMAPP_vSetUserData_StayWakeReason(void)
{
	if(CANNMAPP_WakeUpReasonGet(CANNMAPP_nWakeUp_Local) == False)
	{
		CANNMAPP_stNmUserData.StayWakeByK15 = False;
	}	
	else
	{
		CANNMAPP_stNmUserData.StayWakeByK15 = True;
	}
    CANNMAPP_vUpdateUserData();    
}
/*****************************************************************************
* Function   : void CANNMAPP_vSetUserData_NetState (void)
* Description: Use For Setting the UserData of NetState
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void CANNMAPP_vSetUserData_NetState(void)
{
	if(CANNMAPP_au16Array[CANNMAPP_nu16NmCurrState] == NM_STATE_REPEAT_MESSAGE)
	{
		CANNMAPP_stNmUserData.NetWorkState = 0;/*RMS State*/
	}
	else
	{
		CANNMAPP_stNmUserData.NetWorkState = 1;/*Other State*/
	}
    CANNMAPP_vUpdateUserData();    
}
/*****************************************************************************
* Function   : void CANNMAPP_vSetUserData_NetState (void)
* Description: Use For Setting the UserData of NetState
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void CANNMAPP_vUpdateUserData(void)
{
	CanNm_SetUserData(0,&CANNMAPP_stNmUserData);
}
/*****************************************************************************
* Function   : void CANNMAPP_vLocalWakeUpDetect (void)
* Description: Dectect Local Wake up action
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void CANNMAPP_vLocalWakeUpDetect(void)
{
    uint8 u8Temp = False;

    CANNMAPP_u16LocalWakeUp(&u8Temp);

	u8Temp = True; /*for GET test, always true,190426*/
    if(u8Temp == True)
	//if((CANNMAPP_u16LocalWakeUp == True)||(VTM_u8GetValue(VTM_un8SlpDisable)==True))
	{
		CANNMAPP_WakeUpReasonSet(CANNMAPP_nWakeUp_Local);
        //CANNMAPP_vSetUserData_WakeSource(NmUserData_nWakeByK15);
	}
	else
	{
		CANNMAPP_WakeUpReasonClr(CANNMAPP_nWakeUp_Local);		
	}
}
/*****************************************************************************
* Function   : void CANNMAPP_vLocalWakeUpDetect (void)
* Description: Dectect Local Wake up action
* Call	     : Local
* Returns   : Nothing
******************************************************************************/
static void CANNMAPP_vGetState(void)
{
	Nm_StateType  NmState=0;
	Nm_ModeType  NmMode=0;	
	if(CanNm_GetState(0,&NmState,&NmMode) == NM_E_OK)
	{
		CANNMAPP_au16Array[CANNMAPP_nu16NmMode] = NmMode;
		CANNMAPP_au16Array[CANNMAPP_nu16NmCurrState] = NmState;
	}
}
void CANNM_vBusIdleCheck(void)
{
	if(u16BusIdleTimer >  0)
	{
		u16BusIdleTimer --;
		CANNMAPP_au16Array[CANNMAPP_u16BusIdle]=False;
	}
	else
	{
		CANNMAPP_au16Array[CANNMAPP_u16BusIdle]=True;
	}
}

void CANNM_vBusIdleCheck_ISR(void)
{
	u16BusIdleTimer = 300;
	CANNMAPP_au16Array[CAMNMAPP_nu16CanSleep]=False;
}

void CANNM_vMsgDlcCheck(CanRxInfoStructPtr rxStruct)
{
    uint8 u8MsgDlc = 0u;
    uint16 u16CANMsgID = 0u;
    //uint16 HandleWord=0;
    
    u16CANMsgID = (uint16)*(rxStruct->pChipMsgObj);
    //HandleWord=(uint16)(rxStruct->Handle);
    u8MsgDlc = ((vuint8)((*((rxStruct)->pChipMsgObj+0x01) >> 28) & kCanDlcLogMask));
    switch(u16CANMsgID)
    {
          case 0x85: /* ID: 0x00000085, Handle: 3, EMS_EngineRPM [BC] */ 
            if(u8MsgDlc < 8u)
            {
                if(u8MsgDlc < CanRxDataLen[3])
                {
                    CANNMAPP_MsgValidClr(CANNMAPP_nEmsRPM);
                }
                else
                {
                    CANNMAPP_MsgValidSet(CANNMAPP_nEmsRPM);
                }
                CANNMAPP_MsgDlcErrSet(CANNMAPP_nEmsRPM);
            }
            else
            {
                CANNMAPP_MsgDlcErrClr(CANNMAPP_nEmsRPM);
                CANNMAPP_MsgValidSet(CANNMAPP_nEmsRPM);
            }
            break;
          case 0x3F1: /* ID: 0x000003f1, Handle: 4, IPK_TotalOdometer [FC] */
            if(u8MsgDlc < 8u)
            {
                if(u8MsgDlc < CanRxDataLen[4])
                {
                    CANNMAPP_MsgValidClr(CANNMAPP_nIpk);
                }
                else
                {
                    CANNMAPP_MsgValidSet(CANNMAPP_nIpk);
                }
                CANNMAPP_MsgDlcErrSet(CANNMAPP_nIpk);
            }
            else
            {
                CANNMAPP_MsgDlcErrClr(CANNMAPP_nIpk);
                CANNMAPP_MsgValidSet(CANNMAPP_nIpk);
            }
            break;
          case 0x2A5: /* ID: 0x000002a5, Handle: 5, MMI_AC_Command [FC] */
            if(u8MsgDlc < 8u)
            {
                if(u8MsgDlc < CanRxDataLen[5])
                {
                    CANNMAPP_MsgValidClr(CANNMAPP_nMmiAc);
                }
                else
                {
                    CANNMAPP_MsgValidSet(CANNMAPP_nMmiAc);
                }
                CANNMAPP_MsgDlcErrSet(CANNMAPP_nMmiAc);
            }
            else
            {
                CANNMAPP_MsgDlcErrClr(CANNMAPP_nMmiAc);
                CANNMAPP_MsgValidSet(CANNMAPP_nMmiAc);
            }
            break;
          case 0x2A3: /* ID: 0x000002a3, Handle: 6, MMI_HVSM_Command [FC] */
            if(u8MsgDlc < 8u)
            {
                if(u8MsgDlc < CanRxDataLen[6])
                {
                    CANNMAPP_MsgValidClr(CANNMAPP_nMmiHvsm);
                }
                else
                {
                    CANNMAPP_MsgValidSet(CANNMAPP_nMmiHvsm);
                }
                CANNMAPP_MsgDlcErrSet(CANNMAPP_nMmiHvsm);
            }
            else
            {
                CANNMAPP_MsgDlcErrClr(CANNMAPP_nMmiHvsm);
                CANNMAPP_MsgValidSet(CANNMAPP_nMmiHvsm);
            }
            break;
          case 0x292: /* ID: 0x00000292, Handle: 7, TBOX_RemCon [FC] */
            if(u8MsgDlc < 8u)
            {
                if(u8MsgDlc < CanRxDataLen[7])
                {
                    CANNMAPP_MsgValidClr(CANNMAPP_nTbox);
                }
                else
                {
                    CANNMAPP_MsgValidSet(CANNMAPP_nTbox);
                }
                CANNMAPP_MsgDlcErrSet(CANNMAPP_nTbox);
            }
            else
            {
                CANNMAPP_MsgDlcErrClr(CANNMAPP_nTbox);
                CANNMAPP_MsgValidSet(CANNMAPP_nTbox);
            }
            break;
          case 0x288: /* ID: 0x00000288, Handle: 8, EMS_EngineDriverInfo [FC] */
            if(u8MsgDlc < 8u)
            {
                if(u8MsgDlc < CanRxDataLen[8])
                {
                    CANNMAPP_MsgValidClr(CANNMAPP_nEmsDrv);
                }
                else
                {
                    CANNMAPP_MsgValidSet(CANNMAPP_nEmsDrv);
                }
                CANNMAPP_MsgDlcErrSet(CANNMAPP_nEmsDrv);
            }
            else
            {
                CANNMAPP_MsgDlcErrClr(CANNMAPP_nEmsDrv);
                CANNMAPP_MsgValidSet(CANNMAPP_nEmsDrv);
            }
            break;
          case 0x1E2: /* ID: 0x000001e2, Handle: 9, PEPS_Message_Sts [FC] */
            if(u8MsgDlc < 8u)
            {
                if(u8MsgDlc < CanRxDataLen[9])
                {
                    CANNMAPP_MsgValidClr(CANNMAPP_nPeps);
                }
                else
                {
                    CANNMAPP_MsgValidSet(CANNMAPP_nPeps);
                }
                CANNMAPP_MsgDlcErrSet(CANNMAPP_nPeps);
            }
            else
            {
                CANNMAPP_MsgDlcErrClr(CANNMAPP_nPeps);
                CANNMAPP_MsgValidSet(CANNMAPP_nPeps);
            }
            break;
          case 0x125: /* ID: 0x00000125, Handle: 10, ESC_Status [FC] */
            if(u8MsgDlc < 8u)
            {
                if(u8MsgDlc < CanRxDataLen[10])
                {
                    CANNMAPP_MsgValidClr(CANNMAPP_nEsc);
                }
                else
                {
                    CANNMAPP_MsgValidSet(CANNMAPP_nEsc);
                }
                CANNMAPP_MsgDlcErrSet(CANNMAPP_nEsc);
            }
            else
            {
                CANNMAPP_MsgDlcErrClr(CANNMAPP_nEsc);
                CANNMAPP_MsgValidSet(CANNMAPP_nEsc);
            }
            break;
          case 0x86: /* ID: 0x00000086, Handle: 11, EMS_EngineStatus [FC] */
            if(u8MsgDlc < 8u)
            {
                if(u8MsgDlc < CanRxDataLen[11])
                {
                    CANNMAPP_MsgValidClr(CANNMAPP_nEmsEng);
                }
                else
                {
                    CANNMAPP_MsgValidSet(CANNMAPP_nEmsEng);
                }
                CANNMAPP_MsgDlcErrSet(CANNMAPP_nEmsEng);
            }
            else
            {
                CANNMAPP_MsgDlcErrClr(CANNMAPP_nEmsEng);
                CANNMAPP_MsgValidSet(CANNMAPP_nEmsEng);
            }
            break;
          default:
            break;
    }
}

/****************************************************************/
/**                                                 **********************************/
/**    VECTOR CALLBACK FUNCTIONS    **********************************/
/**                                             on Using    ****************************/
/***************************************************************/

/*****************************************************************************
* Function   : void ApplCbdWrpNetworkStartIndication (void)
* Description: Notification that a NM message has been received within Bus-Sleep Mode.
* Call	     : call back
* Returns   : Nothing
******************************************************************************/
void ApplCbdWrpNetworkStartIndication( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
	if(CANNMAPP_au16Array[CAMNMAPP_nu16CanSleep]  == True)
	{
		CanWakeUp();
	}
	CANNMAPP_vSetUserData_WakeSource(NmUserData_nWakeByBus);/**UserData Setting: WakeUpSource********************/   
    CanNm_PassiveStartUp(0);
	CANAPP_vReset();
}
/*****************************************************************************
* Function   : void ApplCbdWrpBusOffChangeFastToSlow (void)
* Description: When NmState changed, this function will be call, and feedback the PrevNmState
			and Current NmState.
* Call	     : call back
* Returns   : Nothing
******************************************************************************/
void ApplCbdWrpStateChange(uint8 channel,uint8 prevState,uint8 currState ) 
{
	CANNMAPP_au16Array[CANNMAPP_nu16NmPrevState] = prevState;
	CANNMAPP_au16Array[CANNMAPP_nu16NmCurrState] = currState;
	CANNMAPP_vSetUserData_NetState();/**UserData Setting : NetWorkState***********/	
}
/*****************************************************************************
* Function   : void ApplCbdWrpBusOffStart (void)
* Description: Notification that a BusOff has occurred.Indicates the start of the BusOff recovery.
* Call	     : call back
* Returns   : Nothing
******************************************************************************/
void ApplCbdWrpBusOffStart( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
	CANNMAPP_au16Array[CANNMAPP_nu16BusOffStart] = True;
}
/*****************************************************************************
* Function   : void ApplCbdWrpBusOffEnd (void)
* Description: Notification of the end of the BusOff recovery.
* Call	     : call back
* Returns   : Nothing
******************************************************************************/
void ApplCbdWrpBusOffEnd( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
	//CanTransmit(CANNMAPP_BusoffRecoverSendMsgHandle);
}
/*****************************************************************************
* Function   : void ApplCbdWrpBusOffChangeFastToSlow (void)
* Description: 
* Call	     : call back
* Returns   : Nothing
******************************************************************************/
void ApplCbdWrpBusOffChangeFastToSlow( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
	CANNMAPP_au16Array[CANNMAPP_nu16BusOffConf] = True;	
}
/*****************************************************************************
* Function   : void ApplCanTxConfirmation (void)
* Description: when Message sent to BUS successfully, this function will be called.
* Call	     : call back
* Returns   : Nothing
******************************************************************************/
C_CALLBACK_1 void C_CALLBACK_2 ApplCanTxConfirmation(CanTxInfoStructPtr txStruct)
{
	CANNMAPP_au16Array[CANNMAPP_nu16BusOffStart] = False;
	CANNMAPP_au16Array[CANNMAPP_nu16BusOffConf] = False;	
}

C_CALLBACK_1 void C_CALLBACK_2 ApplCanWakeUp(CAN_CHANNEL_CANTYPE_ONLY)
{	
	CANNMAPP_vPoweronInit();
	CANCCL_vClrEnableSleepFlg();
}
/****************************************************************/
/**                                                 **********************************/
/**    VECTOR CALLBACK FUNCTIONS    **********************************/
/**                                             Not Use    ****************************/
/***************************************************************/

/*****************************************************************************
* Function   : void ApplCbdWrpNetStart (void)
* Description: Network start notification.
* Call	     : call back
* Returns   : Nothing
******************************************************************************/
void ApplCbdWrpNetStart( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
}
/*****************************************************************************
* Function   : void ApplCbdWrpNetStop (void)
* Description: Network stop notification.
* Call	     : call back
* Returns   : Nothing
******************************************************************************/
void ApplCbdWrpNetStop( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
}
/*****************************************************************************
* Function   : void ApplCbdWrpBusSleep (void)
* Description: Bus-Sleep notification.
* Call	     : call back
* Returns   : Nothing
******************************************************************************/
void ApplCbdWrpBusSleep( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
    //CANNMAPP_au16Array[CAMNMAPP_nu16CanSleep]  = True;
}
/*****************************************************************************
* Function   : void ApplCbdWrpEnableCom (void)
* Description: Notification about start of communication.
* Call	     : call back
* Returns   : Nothing
******************************************************************************/
void ApplCbdWrpEnableCom( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
}
/*****************************************************************************
* Function   : void ApplCbdWrpDisableCom (void)
* Description: Notification about stop of communication.
* Call	     : call back
* Returns   : Nothing
******************************************************************************/
void ApplCbdWrpDisableCom( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
}
/*****************************************************************************
* Function   : void ApplCbdWrpRestartIndication (void)
* Description: Notification that the NM Coordinator needs to restart this channel.
* Call	     : call back
* Returns   : Nothing
******************************************************************************/
void ApplCbdWrpRestartIndication( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
}
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanMsgReceived(CanRxInfoStructPtr rxStruct)
{
	uint16 HandleWord=0;
	uint8 biNMRxEnable =DIAG_u8GetValue(DIAG_nu8NmRxDisable)==True?0:1;
	uint8 biAppRxEnable =DIAG_u8GetValue(DIAG_nu8AppRxDisable)==True?0:1;
	uint16 u16CANMsgID=0;
	HandleWord=(uint16)(rxStruct->Handle);	
	u16CANMsgID=(uint16)*(rxStruct->pChipMsgObj);

    CANNM_vMsgDlcCheck(rxStruct);/*check dlc err,add by Yang Shengli 20180606*/
    
	if((u16CANMsgID>C_RANGE0_ACC_CODE)&&(u16CANMsgID<(C_RANGE0_ACC_CODE+C_RANGE0_ACC_MASK)))
	{
		return biNMRxEnable&kCanCopyData;   
	}
	else
	{
		if((u16CANMsgID&0x700)==0x700)
		{
			return kCanCopyData;	
		}
		else
		{
			return biAppRxEnable&kCanCopyData;		/*app message??*/
		}
		
	}
}
C_CALLBACK_1 void C_CALLBACK_2 ApplCanOffline( CAN_CHANNEL_CANTYPE_ONLY )
{
}
C_CALLBACK_1 void C_CALLBACK_2 ApplCanOnline( CAN_CHANNEL_CANTYPE_ONLY )
{
}
C_CALLBACK_1 void C_CALLBACK_2 ApplCanFatalError(CAN_CHANNEL_CANTYPE_FIRST vuint8 errorNumber)
{
	uint8 u8ErrorNum;
	u8ErrorNum = errorNumber;
}
void ApplRepeatMsgInd( uint8 a )
{
}
void Ccl_Nm_EnableTxPath( uint8 a )
{
}
/* CODE CATEGORY 2 START */
C_CALLBACK_1 void     C_CALLBACK_2 ApplCanTimerStart(CAN_CHANNEL_CANTYPE_FIRST vuint8 source)
{
}
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanTimerLoop (CAN_CHANNEL_CANTYPE_FIRST vuint8 source)
{
}
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
C_CALLBACK_1 void     C_CALLBACK_2 ApplCanTimerEnd  (CAN_CHANNEL_CANTYPE_FIRST vuint8 source)
{
}
/* CODE CATEGORY 2 END */
/*****************************************************************************
* EOF:
******************************************************************************/
