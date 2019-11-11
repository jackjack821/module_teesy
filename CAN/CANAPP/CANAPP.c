/**************************** .FILE_HEADER_BEGIN *****************************
 .FILE; [ CANAPP.c]
 .Author; [ Liu Fuguang]
 .Date; 2018-5-17
 .Update Time; 15:50:30
 .Gen File Name: Geely GE12_V1.3.11_CAN.xlsx
 .**************   Change History ********************************************* 
 .V2.0 (Release Date:2017-4-17)
 .1.Creation
 .V2.1 (Release Date:2017-4-18)
 .1.Add static uint16 CANAPP_u16SendMsgTimer_20ms
 .2.Add static uint16 CANAPP_u16SendMsgTimer_40ms
 .3.Add static uint16 CANAPP_u16SendMsgTimer_500ms
 .V2.2 (Release Date:2017-4-22)
 .1.Update *Update Content Of Send Message* Module 
 .V2.3 (Release Date:2017-6-21)
 .1.Update the CANAPP_vReset£¨£©º¯Êý 
 .***************************************************************************** 
****************************** .FILE_HEADER_END ******************************/

#define CANAPP_C                          /* Name of the Module                */

/*****************************************************************************
** HEADER-FILES (Only those that are needed in this file) **
*****************************************************************************/

/* System headerfiles */
#include "general.h"
//#include "iodefine.h"

/* Foreign headerfiles */
#include "v_inc.h"
#include "Ccp_cfg.h"
#include "CanNmApp.h"
#include "Accc.h"
#include "Mmi.h"
#include "Oat.h"
//#include "Ict.h"
#include "Rfa.h"
#include "Bctl.h"
#include "Aird.h"
#include "Shc.h"
#include "AQS.h"
#include "ISTP.h"
#include "Ion.h"

/* Own headerfiles */
#include "CANAPP.H"
#include "CANAPP_cfg.H"

/**Local Varibles Definition *******************************************/
static uint16 CANAPP_u16SendMsgTimer_20ms;
static uint16 CANAPP_u16SendMsgTimer_40ms;
static uint16 CANAPP_u16SendMsgTimer_50ms;
static uint16 CANAPP_u16SendMsgTimer_100ms;
static uint16 CANAPP_u16SendMsgTimer_200ms;
static uint16 CANAPP_u16SendMsgTimer_400ms;
static uint16 CANAPP_u16SendMsgTimer_500ms;
static uint16 CANAPP_u16SendMsgTimer_1000ms;
static uint16 CANAPP_au16Array[CANAPP_nu16Max];
static uint32 CANAPP_au32Array[CANAPP_nu32Max];
static uint16 CANAPP_au16MsgMissCnt[CANAPP_nbiNumberRevMesg];
static uint16 CANAPP_u16SendKeyPressCnt;
static uint16 CANAPP_u16DlcrrorCounterArray[CANAPP_nMax];

#define CANAPP_ErrCodeSet(Index)    (CANAPP_au32Array[CANAPP_nu32ErrorCode] |= (0x00000001 << Index))
#define CANAPP_ErrCodeClr(Index)        (CANAPP_au32Array[CANAPP_nu32ErrorCode] &= (~(0x00000001 << Index)))
#define CANAPP_ErrCodeGet(Index)    ((CANAPP_au32Array[CANAPP_nu32ErrorCode]>>Index) & 0x00000001)
#define CANAPP_AllErrCodeClr()      (CANAPP_au32Array[CANAPP_nu32ErrorCode] = 0U)
#define CANAPP_MsgNeverRecFlgSet(Index) (CANAPP_au32Array[CANAPP_nu32MsgNeverRecFlg] |= (0x00000001 << Index))
#define CANAPP_MsgNeverRecFlgClr(Index)     (CANAPP_au32Array[CANAPP_nu32MsgNeverRecFlg] &= (~(0x00000001 << Index)))
#define CANAPP_MsgNeverRecFlgGet(Index) ((CANAPP_au32Array[CANAPP_nu32MsgNeverRecFlg]>>Index) & 0x00000001)
#define CANAPP_AllMsgNeverRecFlgClr()       (CANAPP_au32Array[CANAPP_nu32MsgNeverRecFlg] = 0U)
#define CANAPP_DlcErrCodeSet(Index)    (CANAPP_au32Array[CANAPP_nu32MsgDlcErr] |= (0x00000001 << Index))
#define CANAPP_DlcErrCodeClr(Index)        (CANAPP_au32Array[CANAPP_nu32MsgDlcErr] &= (~(0x00000001 << Index)))
#define CANAPP_DlcErrCodeGet(Index)    ((CANAPP_au32Array[CANAPP_nu32MsgDlcErr]>>Index) & 0x00000001)
#define CANAPP_AllDlcErrCodeClr()      (CANAPP_au32Array[CANAPP_nu32MsgDlcErr] = 0U)
#define CANAPP_MsgMissTimeout_PEPS_Message_Sts_0x1E2_MAX                25/*PEPS_Message_Sts25*10 = Timeout time...*/
#define CANAPP_MsgMissTimeout_EMS_EngineRPM_0x85_MAX                25/*EMS_EngineRPM25*10 = Timeout time...*/
#define CANAPP_MsgMissTimeout_EMS_EngineDriverInfo_0x288_MAX                50/*EMS_EngineDriverInfo50*10 = Timeout time...*/
#define CANAPP_MsgMissTimeout_EMS_EngineStatus_0x86_MAX                25/*EMS_EngineStatus25*10 = Timeout time...*/
#define CANAPP_MsgMissTimeout_ESC_Status_0x125_MAX                25/*ESC_Status25*10 = Timeout time...*/
#define CANAPP_MsgMissTimeout_MMI_HVSM_Command_0x2A3_MAX                50/*MMI_HVSM_Command50*10 = Timeout time...*/
#define CANAPP_MsgMissTimeout_MMI_AC_Command_0x2A5_MAX                50/*MMI_AC_Command50*10 = Timeout time...*/
#define CANAPP_MsgMissTimeout_IPK_TotalOdometer_0x3F1_MAX                500/*IPK_TotalOdometer500*10 = Timeout time...*/
#define CANAPP_MsgMissTimeout_TBOX_RemCon_0x292_MAX                50/*TBOX_RemCon50*10 = Timeout time...*/

/**Local Functions Declear ************************************************************/
/****************************************************************/
/**                                                 ***********************************/
/**  Update Content Of Send Message  ***********************************/
/**                                                 ***********************************/
/****************************************************************/
void CANAPP_vSendMsgUpdate_AC_ReqSts_0x2F1(void);
void CANAPP_vSendMsgUpdate_AC_Status_Info_0x2F2(void);

/****************************************************************/
/**                                                 ***********************************/
/**            Send Message                  ***********************************/
/**                                                 ***********************************/
/****************************************************************/
void CANAPP_vSendMsg_AC_ReqSts_0x2F1(void);
void CANAPP_vSendMsg_AC_Status_Info_0x2F2(void);

void CANAPP_vSendMsg_10ms(void);
void CANAPP_vSendMsg_20ms(void);
void CANAPP_vSendMsg_40ms(void);
void CANAPP_vSendMsg_50ms(void);
void CANAPP_vSendMsg_100ms(void);
void CANAPP_vSendMsg_200ms(void);
void CANAPP_vSendMsg_400ms(void);
void CANAPP_vSendMsg_500ms(void);
void CANAPP_vSendMsg_1000ms(void);

/****************************************************************/
/**                                                 ***********************************/
/**            Receive Message              ***********************************/
/**                                                 ***********************************/
/****************************************************************/
void CANAPP_vReceiveMsg(void);
void CANAPP_vReceiveMsg_PEPS_Message_Sts_0x1E2(void);
void CANAPP_vReceiveMsg_EMS_EngineRPM_0x85(void);
void CANAPP_vReceiveMsg_EMS_EngineDriverInfo_0x288(void);
void CANAPP_vReceiveMsg_EMS_EngineStatus_0x86(void);
void CANAPP_vReceiveMsg_ESC_Status_0x125(void);
void CANAPP_vReceiveMsg_MMI_HVSM_Command_0x2A3(void);
void CANAPP_vReceiveMsg_MMI_AC_Command_0x2A5(void);
void CANAPP_vReceiveMsg_IPK_TotalOdometer_0x3F1(void);
void CANAPP_vReceiveMsg_TBOX_RemCon_0x292(void);

/**Local Functions Definition ************************************************************/
/****************************************************************/
/**                                                 ***********************************/
/**  Update Content Of Send Message  ***********************************/
/**                                                 ***********************************/
/****************************************************************/
void CANAPP_vSendMsgUpdate(void)
{
    if((MMI_u16GetKnobOrKeyOperationFlag() > 0) && CANAPP_u16SendKeyPressCnt <= 0u)
    {
        CANAPP_u16SendKeyPressCnt = 3u;
    }
    
    CANAPP_vSendMsgUpdate_AC_ReqSts_0x2F1();
    CANAPP_vSendMsgUpdate_AC_Status_Info_0x2F2();
}
void CANAPP_vSendMsgUpdate_AC_ReqSts_0x2F1(void)
{
    uint16 u16VictValue = 0u;

    b_AC_ACCompReq_b = ACCC_u8GetValue(ACCC_nu8AcActualRequest); 
    b_AC_AmbientTemperatureInvalid_b = (OAT_u16GetValue(OAT_nu16ErrorCode)&3)>0? 1:0;
    b_AC_SSM_Allowance_b = ISTP_u8GetValue(ISTP_nu8Allowance);
    b_AC_SSM_StartReq_b = ISTP_u8GetValue(ISTP_nu8StartReq);
	if(MMI_u8GetValue(MMI_nu8BlwControl)!=0)
	{
 		b_AC_FanStatus_b = 1;     
	}
	else
	{
		b_AC_FanStatus_b = 0; 
	}
    if((VICT_u16GetValidState(VICT_nu16HeadZoneTempL) == 1u)\
        && (VICT_u16GetValidState(VICT_nu16HeadZoneTempR) == 1u))
    {
        u16VictValue = (VICT_u16GetValue(VICT_nu16HeadZoneTempL) + VICT_u16GetValue(VICT_nu16HeadZoneTempL))/10;
        if(u16VictValue > 0xc8)
        {
            b_AC_InsideTemperature_c = 0xc8;
        }
        else
        {
            b_AC_InsideTemperature_c = (uint8)u16VictValue;
        }
        
	    b_AC_InsideTemperatureInvalid_b = 0u;
    }
    else
    {
        b_AC_InsideTemperature_c = 0x78u;
        b_AC_InsideTemperatureInvalid_b = 1u;
    }
	if(OAT_u16GetValue(OAT_nu16Display)>0xc8)
	{
		b_AC_AmbientTemperature_c = 0xc8;   
	}
	else
	{
		b_AC_AmbientTemperature_c=OAT_u16GetValue(OAT_nu16Display);
	}
	b_AC_PM25InDen_b(ION_u16GetValue(ION_nu16PM25InDen)) ;
	b_AC_PM25OutDen_b(ION_u16GetValue(ION_nu16PM25OutDen));
	b_AC_AirInQLevel_b  =  ION_u8GetValue(ION_nu8AirInQLevel) ; 
	b_AC_AirOutQLevel_b =  ION_u8GetValue(ION_nu8AirOutQLevel);     
	b_AC_PM25Sts_b=  CANAPP_au16Array[CANAPP_nu16EMS_EngStatus];//ION_u8GetValue(ION_nu8PM25Sts);  GET TEST
    
    //b_AC_PM25PopupReq_b = ION_u8GetValue(ION_nu8PM25Exceed);/*TBD*/
    b_AC_PM25PopupReq_b = ION_u8GetValue(ION_nu8PM25PopupReq); /*V1.92*/
}
void CANAPP_vSendMsgUpdate_AC_Status_Info_0x2F2(void)
{
	uint8 u8MMI_SetTempDr=MMI_u8GetValue(MMI_nu8SetTempDr);
    uint8 u8MMI_SetTempPs=MMI_u8GetValue(MMI_nu8SetTempPs);
	uint8 u8MMI_Mode=MMI_u8GetValue(MMI_nu8SysState);

    if(MMI_u8GetValue(MMI_nu8BlwModeControl)==MMI_nBctlStateOff)
    {
        b_AC_AutoState_b=0;
    }
    else
    {
        b_AC_AutoState_b = (MMI_u8GetValue(MMI_nu8SysState)==MMI_nSysStateAuto?1:0);
    }
    if(CANAPP_u16SendKeyPressCnt > 0u)
    {
        b_AC_DisplayRequest_b = 1;/*TBD*/
    }
    else
    {
        b_AC_DisplayRequest_b = 0;/*TBD*/
    }
    if(MMI_u8GetValue(MMI_nu8SysState) == MMI_nSysStateMaxAc)
    {
        b_AC_MaxAcState_b = 1u;
    }
    else
    {
        b_AC_MaxAcState_b = 0u;
    }
    b_AC_FrontDefrostState_b = MMI_u8GetValue(MMI_nu8SysState)==MMI_nSysStateDefrost?1:0;
    b_AC_IntakeAirState_b  = MMI_u8GetValue(MMI_nu8RecirControl); 
    b_AC_AqsState_b = (MMI_u8GetValue(MMI_nu8RecirMode)==MMI_nRfaStateAuto?1:0);
    b_AC_BlowerLevel_b =  MMI_u8GetValue(MMI_nu8BlwControl);
    b_AC_DualState_b = MMI_u8GetValue(MMI_nu8DualControl);
    if((MMI_u8GetValue(MMI_nu8IonCtrl) == MMI_nIonIonMode) && (ION_u8GetValue(ION_nu8IONErrSts) == 1))
    {
        b_AC_IONIZERState_b = 3;
    }
    else if((MMI_u8GetValue(MMI_nu8IonCtrl) == MMI_nIonIonMode) && (ION_u8GetValue(ION_nu8IONErrSts) == 0))
    {
        b_AC_IONIZERState_b = 1;
    }
    else
    {
        b_AC_IONIZERState_b = 0;
    }
    b_AC_AirDistributionMode_b  = MMI_u8GetValue(MMI_nu8AirdControl);
    b_AC_OnState_b = (MMI_u8GetValue(MMI_nu8BlwModeControl)==MMI_nBctlStateOff?0:1);
	if(0==u8MMI_SetTempDr)
	{
		b_AC_LeftSetTemperature_b = 0;	
	}
	else if(0xff==u8MMI_SetTempDr)
	{
		b_AC_LeftSetTemperature_b = 0x1e;	
	}
	else 
	{
		b_AC_LeftSetTemperature_b = (u8MMI_SetTempDr -34);
	}
    b_AC_AirCleanState_b = MMI_u8GetValue(MMI_nu8IonCtrl);/*TBD*/
	if(0==u8MMI_SetTempPs)
	{
		b_AC_RightSetTemperature_b = 0;	
	}
	else if(0xff==u8MMI_SetTempPs)
	{
		b_AC_RightSetTemperature_b = 0x1e;	
	}
	else 
	{
		b_AC_RightSetTemperature_b = (u8MMI_SetTempPs -34);
	}
	if( CANAPP_au16Array[CANAPP_nu16PEPS_RemoteControlSt] >= U16_MISS_VALUE) /*add ig on,170730*/
	{
		b_AC_RemoteControlSt_b =False;
	}
	else
	{
		b_AC_RemoteControlSt_b = b_PEPS_RemoteControlSt_b;/*BUG:signal 1->0->1 when IG ON, direct from can,1*/
	}/*TBD*/
	b_AC_DrvHeatSts_b = SHC_u8GetValue(SHC_nu8DisplayDr);
	b_AC_PassHeatingSts_b = SHC_u8GetValue(SHC_nu8DisplayPs);
}

/****************************************************************/
/**                                                 ***********************************/
/**            Send Message                  ***********************************/
/**                                                 ***********************************/
/****************************************************************/
void CANAPP_vSendMsg_AC_ReqSts_0x2F1(void)
{/* Message tranmit with every 100ms...*/
        if(AC_ReqSts_conf_b == True)
        {
                CanWriteSyncAC_ReqSts_conf_b(0);
        }
        CanTransmit(CanTxAC_ReqSts);
}

void CANAPP_vSendMsg_AC_Status_Info_0x2F2(void)
{/* Message tranmit with every 100ms...*/

        if(CANAPP_u16SendKeyPressCnt > 0u)
        {
            CANAPP_u16SendKeyPressCnt--;
        }
        else
        {
            MMI_u16ClearKnobOrKeyOperationFlag();
        }
        
        if(AC_Status_Info_conf_b == True)
        {
            CanWriteSyncAC_Status_Info_conf_b(0);
        }
        CanTransmit(CanTxAC_Status_Info);
}
/*****************************************************************************
* Function   : void CANAPP_vClearSendMsgTmr (void)
* Description: this function used for clrean the message send timer
* Returns   : Nothing
******************************************************************************/
void CANAPP_vClearSendMsgTmr(void)
{
	CANAPP_u16SendMsgTimer_20ms = 0;
	CANAPP_u16SendMsgTimer_40ms = 0;
	CANAPP_u16SendMsgTimer_50ms = 0;
	CANAPP_u16SendMsgTimer_100ms = 0;
	CANAPP_u16SendMsgTimer_200ms = 0;
	CANAPP_u16SendMsgTimer_400ms = 0;
	CANAPP_u16SendMsgTimer_500ms = 0;
	CANAPP_u16SendMsgTimer_1000ms = 0;

    CANAPP_u16SendKeyPressCnt = 0u;
}
void CANAPP_vSendMsg_10ms(void)
{

}
void CANAPP_vSendMsg_20ms(void)
{
        if(CANAPP_u16SendMsgTimer_20ms < 1)
        {
                CANAPP_u16SendMsgTimer_20ms++;
        }
        else
        {
                CANAPP_u16SendMsgTimer_20ms = 0;
        }
        switch(CANAPP_u16SendMsgTimer_20ms)
        {
                case 0:
                        break;
                case 1:
                        break;
                case 2:
                        break;
                default:
                        break;
        }
}
void CANAPP_vSendMsg_40ms(void)
{
        if(CANAPP_u16SendMsgTimer_40ms < 3)
        {
                CANAPP_u16SendMsgTimer_40ms++;
        }
        else
        {
                CANAPP_u16SendMsgTimer_40ms = 0;
        }
        switch(CANAPP_u16SendMsgTimer_40ms)
        {
                case 0:
                        break;
                case 1:
                        break;
                case 2:
                        break;
                default:
                        break;
        }
}
void CANAPP_vSendMsg_50ms(void)
{
        if(CANAPP_u16SendMsgTimer_50ms < 4)
        {
                CANAPP_u16SendMsgTimer_50ms++;
        }
        else
        {
                CANAPP_u16SendMsgTimer_50ms = 0;
        }
        switch(CANAPP_u16SendMsgTimer_50ms)
        {
                case 0:
                        break;
                case 1:
                        break;
                case 2:
                        break;
                default:
                        break;
        }
}
void CANAPP_vSendMsg_100ms(void)
{
        switch(CANAPP_u16SendMsgTimer_100ms)
        {
                case 0:
                    CANAPP_vSendMsg_AC_ReqSts_0x2F1();
                        break;
                case 1:
                    CANAPP_vSendMsg_AC_Status_Info_0x2F2();
                        break;
                case 2:
                        break;
                default:
                        break;
        }
        if(CANAPP_u16SendMsgTimer_100ms < 9)
        {
                CANAPP_u16SendMsgTimer_100ms++;
        }
        else
        {
                CANAPP_u16SendMsgTimer_100ms = 0;
        }
}
void CANAPP_vSendMsg_200ms(void)
{
        if(CANAPP_u16SendMsgTimer_200ms < 19)
        {
                CANAPP_u16SendMsgTimer_200ms++;
        }
        else
        {
                CANAPP_u16SendMsgTimer_200ms = 0;
        }
        switch(CANAPP_u16SendMsgTimer_200ms)
        {
                case 0:
                        break;
                case 1:
                        break;
                case 2:
                        break;
                default:
                        break;
        }
}
void CANAPP_vSendMsg_400ms(void)
{
        if(CANAPP_u16SendMsgTimer_400ms < 39)
        {
                CANAPP_u16SendMsgTimer_400ms++;
        }
        else
        {
                CANAPP_u16SendMsgTimer_400ms = 0;
        }
        switch(CANAPP_u16SendMsgTimer_400ms)
        {
                case 0:
                        break;
                case 1:
                        break;
                case 2:
                        break;
                default:
                        break;
        }
}
void CANAPP_vSendMsg_500ms(void)
{
        if(CANAPP_u16SendMsgTimer_500ms < 49)
        {
                CANAPP_u16SendMsgTimer_500ms++;
        }
        else
        {
                CANAPP_u16SendMsgTimer_500ms = 0;
        }
        switch(CANAPP_u16SendMsgTimer_500ms)
        {
                case 0:
                        break;
                case 1:
                        break;
                case 2:
                        break;
                default:
                        break;
        }
}
void CANAPP_vSendMsg_1000ms(void)
{
        if(CANAPP_u16SendMsgTimer_1000ms > 99)
        {
                CANAPP_u16SendMsgTimer_1000ms = 0;
        }
        else
        {
                CANAPP_u16SendMsgTimer_1000ms++;
        }
        switch(CANAPP_u16SendMsgTimer_1000ms)
        {
                case 0:
                        break;
                case 1:
                        break;
                case 2:
                        break;
                default:
                        break;
        }
}

/****************************************************************/
/**                                                 ***********************************/
/**            Receive Message              ***********************************/
/**                                                 ***********************************/
/****************************************************************/
void CANAPP_vReceiveMsg(void)
{
        CANAPP_vReceiveMsg_PEPS_Message_Sts_0x1E2();
        CANAPP_vReceiveMsg_EMS_EngineRPM_0x85();
        CANAPP_vReceiveMsg_EMS_EngineDriverInfo_0x288();
        CANAPP_vReceiveMsg_EMS_EngineStatus_0x86();
        CANAPP_vReceiveMsg_ESC_Status_0x125();
        CANAPP_vReceiveMsg_MMI_HVSM_Command_0x2A3();
        CANAPP_vReceiveMsg_MMI_AC_Command_0x2A5();
        CANAPP_vReceiveMsg_IPK_TotalOdometer_0x3F1();
        CANAPP_vReceiveMsg_TBOX_RemCon_0x292();
}
void CANAPP_vReceiveMsg_PEPS_Message_Sts_0x1E2(void)
{/* Message received with every 20ms...*/
        uint16 u16DlcErrCode = 0u;
        uint16 u16DataValid = 0u;
        
        if(PEPS_Message_Sts_ind_b == True)
        {
                u16DlcErrCode = CANNMAPP_u16GetValue(CANNMAPP_u16MsgDlcErr);
                u16DataValid = CANNMAPP_u16GetValue(CANNMAPP_u16MsgValid);
                PEPS_Message_Sts_ind_b = 0x00;
                CANAPP_ErrCodeClr(CANAPP_nbiPEPS_Message_Sts_0x1E2);
                CANAPP_au16MsgMissCnt[CANAPP_nbiPEPS_Message_Sts_0x1E2] = 0;

                if((u16DataValid&(1<<CANAPP_nPeps))>0)
                {
                    CANAPP_MsgNeverRecFlgSet(CANAPP_nbiPEPS_Message_Sts_0x1E2);
                    CANAPP_au16Array[CANAPP_nu16PEPS_PowerModeValidity] = b_PEPS_PowerModeValidity_b;
                    CANAPP_au16Array[CANAPP_nu16PEPS_PowerMode] = b_PEPS_PowerMode_b;
                    CANAPP_au16Array[CANAPP_nu16PEPS_RemoteControlSt] = b_PEPS_RemoteControlSt_b;
                }

                /*Check DLC err*/
                if((u16DlcErrCode&(1<<CANAPP_nPeps))>0)
                {
                    if(CANAPP_u16DlcrrorCounterArray[CANAPP_nPeps] < 10)
                    {
                        CANAPP_u16DlcrrorCounterArray[CANAPP_nPeps]++;
                    }
                    else
                    {
                        CANAPP_DlcErrCodeSet(CANAPP_nPeps);
                    }
                }
                else
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nPeps);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nPeps] = 0u;
                }
        }
        else
        {
                if(CANNMAPP_BusOffStart == True)
                {
                        CANAPP_ErrCodeClr(CANAPP_nbiPEPS_Message_Sts_0x1E2);
                        CANAPP_au16MsgMissCnt[CANAPP_nbiPEPS_Message_Sts_0x1E2] = 0;
                }
                else
                {
                if(CANAPP_au16MsgMissCnt[CANAPP_nbiPEPS_Message_Sts_0x1E2] >= CANAPP_MsgMissTimeout_PEPS_Message_Sts_0x1E2_MAX)
                {
                        if(CANAPP_MsgNeverRecFlgGet(CANAPP_nbiPEPS_Message_Sts_0x1E2) == True)
                        {
                                CANAPP_au16Array[CANAPP_nu16PEPS_PowerModeValidity] = U16_MISS_VALUE;
                                CANAPP_au16Array[CANAPP_nu16PEPS_PowerMode] = U16_MISS_VALUE;
                                CANAPP_au16Array[CANAPP_nu16PEPS_RemoteControlSt] = U16_MISS_VALUE;
                        }
                        CANAPP_ErrCodeSet(CANAPP_nbiPEPS_Message_Sts_0x1E2);
                }
                else
                {
                        CANAPP_au16MsgMissCnt[CANAPP_nbiPEPS_Message_Sts_0x1E2]++;
                }
                }
                
                if(CANAPP_au16MsgMissCnt[CANAPP_nbiPEPS_Message_Sts_0x1E2] >= 2)
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nPeps);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nPeps] = 0u;
                }
        }
}

void CANAPP_vReceiveMsg_EMS_EngineRPM_0x85(void)
{/* Message received with every 10ms...*/
        uint16 u16DlcErrCode = 0u;
        uint16 u16DataValid = 0u;
        
        if(EMS_EngineRPM_ind_b == True)
        {
                u16DlcErrCode = CANNMAPP_u16GetValue(CANNMAPP_u16MsgDlcErr);
                u16DataValid = CANNMAPP_u16GetValue(CANNMAPP_u16MsgValid);
                EMS_EngineRPM_ind_b = 0x00;
                CANAPP_ErrCodeClr(CANAPP_nbiEMS_EngineRPM_0x85);
                CANAPP_au16MsgMissCnt[CANAPP_nbiEMS_EngineRPM_0x85] = 0;

                if((u16DataValid&(1<<CANAPP_nEmsRPM))>0)
                {
                    CANAPP_MsgNeverRecFlgSet(CANAPP_nbiEMS_EngineRPM_0x85);
                    CANAPP_au16Array[CANAPP_nu16EMS_EngineSpeedRPM] = b_EMS_EngineSpeedRPM_b;
                    CANAPP_au16Array[CANAPP_nu16EMS_SSMStatus] = b_EMS_SSMStatus_b;
                    CANAPP_au16Array[CANAPP_nu16EMS_EngineSpeedRPMInvalid] = b_EMS_EngineSpeedRPMInvalid_b;
                    CANAPP_au16Array[CANAPP_nu16EMS_EngStatus] = b_EMS_EngStatus_b;
                }

                /*Check DLC err*/
                if((u16DlcErrCode&(1<<CANAPP_nEmsRPM))>0)
                {
                    if(CANAPP_u16DlcrrorCounterArray[CANAPP_nEmsRPM] < 10)
                    {
                        CANAPP_u16DlcrrorCounterArray[CANAPP_nEmsRPM]++;
                    }
                    else
                    {
                        CANAPP_DlcErrCodeSet(CANAPP_nEmsRPM);
                    }
                }
                else
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nEmsRPM);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nEmsRPM] = 0u;
                }
        }
        else
        {
                if(CANNMAPP_BusOffStart == True)
                {
                        CANAPP_ErrCodeClr(CANAPP_nbiEMS_EngineRPM_0x85);
                        CANAPP_au16MsgMissCnt[CANAPP_nbiEMS_EngineRPM_0x85] = 0;
                }
                else
                {
                if(CANAPP_au16MsgMissCnt[CANAPP_nbiEMS_EngineRPM_0x85] >= CANAPP_MsgMissTimeout_EMS_EngineRPM_0x85_MAX)
                {
                        if(CANAPP_MsgNeverRecFlgGet(CANAPP_nbiEMS_EngineRPM_0x85) == True)
                        {
                                CANAPP_au16Array[CANAPP_nu16EMS_EngineSpeedRPM] = U16_MISS_VALUE;
                                CANAPP_au16Array[CANAPP_nu16EMS_SSMStatus] = U16_MISS_VALUE;
                                CANAPP_au16Array[CANAPP_nu16EMS_EngineSpeedRPMInvalid] = U16_MISS_VALUE;
                                CANAPP_au16Array[CANAPP_nu16EMS_EngStatus] = U16_MISS_VALUE;
                        }
                        CANAPP_ErrCodeSet(CANAPP_nbiEMS_EngineRPM_0x85);
                }
                else
                {
                        CANAPP_au16MsgMissCnt[CANAPP_nbiEMS_EngineRPM_0x85]++;
                }
                }
                CANAPP_DlcErrCodeClr(CANAPP_nEmsRPM);
                CANAPP_u16DlcrrorCounterArray[CANAPP_nEmsRPM] = 0u;
        }
}

void CANAPP_vReceiveMsg_EMS_EngineDriverInfo_0x288(void)
{/* Message received with every 100ms...*/
        uint16 u16DlcErrCode = 0u;
        uint16 u16DataValid = 0u;
        
        if(EMS_EngineDriverInfo_ind_b == True)
        {
                u16DlcErrCode = CANNMAPP_u16GetValue(CANNMAPP_u16MsgDlcErr);
                u16DataValid = CANNMAPP_u16GetValue(CANNMAPP_u16MsgValid);
                EMS_EngineDriverInfo_ind_b = 0x00;
                CANAPP_ErrCodeClr(CANAPP_nbiEMS_EngineDriverInfo_0x288);
                CANAPP_au16MsgMissCnt[CANAPP_nbiEMS_EngineDriverInfo_0x288] = 0;

                if((u16DataValid&(1<<CANAPP_nEmsDrv))>0)
                {
                    CANAPP_MsgNeverRecFlgSet(CANAPP_nbiEMS_EngineDriverInfo_0x288);
                    CANAPP_au16Array[CANAPP_nu16EMS_EngineCoolantTemp] = b_EMS_EngineCoolantTemp_c;
                    CANAPP_au16Array[CANAPP_nu16EMS_EngineCoolantTempInvalid] = b_EMS_EngineCoolantTempInvalid_b;
                }

                /*Check DLC err*/
                if((u16DlcErrCode&(1<<CANAPP_nEmsDrv))>0)
                {
                    if(CANAPP_u16DlcrrorCounterArray[CANAPP_nEmsDrv] < 10)
                    {
                        CANAPP_u16DlcrrorCounterArray[CANAPP_nEmsDrv]++;
                    }
                    else
                    {
                        CANAPP_DlcErrCodeSet(CANAPP_nEmsDrv);
                    }
                }
                else
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nEmsDrv);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nEmsDrv] = 0u;
                }
        }
        else
        {
                if(CANNMAPP_BusOffStart == True)
                {
                        CANAPP_ErrCodeClr(CANAPP_nbiEMS_EngineDriverInfo_0x288);
                        CANAPP_au16MsgMissCnt[CANAPP_nbiEMS_EngineDriverInfo_0x288] = 0;
                }
                else
                {
                    if(CANAPP_au16MsgMissCnt[CANAPP_nbiEMS_EngineDriverInfo_0x288] >= CANAPP_MsgMissTimeout_EMS_EngineDriverInfo_0x288_MAX)
                    {
                            if(CANAPP_MsgNeverRecFlgGet(CANAPP_nbiEMS_EngineDriverInfo_0x288) == True)
                            {
                                    CANAPP_au16Array[CANAPP_nu16EMS_EngineCoolantTemp] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16EMS_EngineCoolantTempInvalid] = U16_MISS_VALUE;
                            }
                            CANAPP_ErrCodeSet(CANAPP_nbiEMS_EngineDriverInfo_0x288);
                    }
                    else
                    {
                            CANAPP_au16MsgMissCnt[CANAPP_nbiEMS_EngineDriverInfo_0x288]++;
                    }
                }

                if(CANAPP_au16MsgMissCnt[CANAPP_nbiEMS_EngineDriverInfo_0x288] >= 10)
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nEmsDrv);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nEmsDrv] = 0u;
                }
        }
}

void CANAPP_vReceiveMsg_EMS_EngineStatus_0x86(void)
{/* Message received with every 10ms...*/
        uint16 u16DlcErrCode = 0u;
        uint16 u16DataValid = 0u;
        
        if(EMS_EngineStatus_ind_b == True)
        {
                u16DlcErrCode = CANNMAPP_u16GetValue(CANNMAPP_u16MsgDlcErr);
                u16DataValid = CANNMAPP_u16GetValue(CANNMAPP_u16MsgValid);
                EMS_EngineStatus_ind_b = 0x00;
                CANAPP_ErrCodeClr(CANAPP_nbiEMS_EngineStatus_0x86);
                CANAPP_au16MsgMissCnt[CANAPP_nbiEMS_EngineStatus_0x86] = 0;

                if((u16DataValid&(1<<CANAPP_nEmsEng))>0)
                {
                    CANAPP_MsgNeverRecFlgSet(CANAPP_nbiEMS_EngineStatus_0x86);
                    CANAPP_au16Array[CANAPP_nu16EMS_ACStatus] = b_EMS_ACStatus_b;
                }

                /*Check DLC err*/
                if((u16DlcErrCode&(1<<CANAPP_nEmsEng))>0)
                {
                    if(CANAPP_u16DlcrrorCounterArray[CANAPP_nEmsEng] < 10)
                    {
                        CANAPP_u16DlcrrorCounterArray[CANAPP_nEmsEng]++;
                    }
                    else
                    {
                        CANAPP_DlcErrCodeSet(CANAPP_nEmsEng);
                    }
                }
                else
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nEmsEng);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nEmsEng] = 0u;
                }
        }
        else
        {
                if(CANNMAPP_BusOffStart == True)
                {
                        CANAPP_ErrCodeClr(CANAPP_nbiEMS_EngineStatus_0x86);
                        CANAPP_au16MsgMissCnt[CANAPP_nbiEMS_EngineStatus_0x86] = 0;
                }
                else
                {
                if(CANAPP_au16MsgMissCnt[CANAPP_nbiEMS_EngineStatus_0x86] >= CANAPP_MsgMissTimeout_EMS_EngineStatus_0x86_MAX)
                {
                        if(CANAPP_MsgNeverRecFlgGet(CANAPP_nbiEMS_EngineStatus_0x86) == True)
                        {
                                CANAPP_au16Array[CANAPP_nu16EMS_ACStatus] = U16_MISS_VALUE;
                        }
                        CANAPP_ErrCodeSet(CANAPP_nbiEMS_EngineStatus_0x86);
                }
                else
                {
                        CANAPP_au16MsgMissCnt[CANAPP_nbiEMS_EngineStatus_0x86]++;
                }
                }
                CANAPP_DlcErrCodeClr(CANAPP_nEmsEng);
                CANAPP_u16DlcrrorCounterArray[CANAPP_nEmsEng] = 0u;
        }
}

void CANAPP_vReceiveMsg_ESC_Status_0x125(void)
{/* Message received with every 20ms...*/
        uint16 u16DlcErrCode = 0u;
        uint16 u16DataValid = 0u;
        
        if(ESC_Status_ind_b == True)
        {
                u16DlcErrCode = CANNMAPP_u16GetValue(CANNMAPP_u16MsgDlcErr);
                u16DataValid = CANNMAPP_u16GetValue(CANNMAPP_u16MsgValid);
                ESC_Status_ind_b = 0x00;
                CANAPP_ErrCodeClr(CANAPP_nbiESC_Status_0x125);
                CANAPP_au16MsgMissCnt[CANAPP_nbiESC_Status_0x125] = 0;

                if((u16DataValid&(1<<CANAPP_nEsc))>0)
                {
                    CANAPP_MsgNeverRecFlgSet(CANAPP_nbiESC_Status_0x125);
                    CANAPP_au16Array[CANAPP_nu16ESC_VehicleSpeed] = b_ESC_VehicleSpeed_b;
                    CANAPP_au16Array[CANAPP_nu16ESC_VehicleSpeedInvalid] = b_ESC_VehicleSpeedInvalid_b;
                }

                /*Check DLC err*/
                if((u16DlcErrCode&(1<<CANAPP_nEsc))>0)
                {
                    if(CANAPP_u16DlcrrorCounterArray[CANAPP_nEsc] < 10)
                    {
                        CANAPP_u16DlcrrorCounterArray[CANAPP_nEsc]++;
                    }
                    else
                    {
                        CANAPP_DlcErrCodeSet(CANAPP_nEsc);
                    }
                }
                else
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nEsc);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nEsc] = 0u;
                }
        }
        else
        {
                if(CANNMAPP_BusOffStart == True)
                {
                        CANAPP_ErrCodeClr(CANAPP_nbiESC_Status_0x125);
                        CANAPP_au16MsgMissCnt[CANAPP_nbiESC_Status_0x125] = 0;
                }
                else
                {
                if(CANAPP_au16MsgMissCnt[CANAPP_nbiESC_Status_0x125] >= CANAPP_MsgMissTimeout_ESC_Status_0x125_MAX)
                {
                        if(CANAPP_MsgNeverRecFlgGet(CANAPP_nbiESC_Status_0x125) == True)
                        {
                                CANAPP_au16Array[CANAPP_nu16ESC_VehicleSpeed] = U16_MISS_VALUE;
                                CANAPP_au16Array[CANAPP_nu16ESC_VehicleSpeedInvalid] = U16_MISS_VALUE;
                        }
                        CANAPP_ErrCodeSet(CANAPP_nbiESC_Status_0x125);
                }
                else
                {
                        CANAPP_au16MsgMissCnt[CANAPP_nbiESC_Status_0x125]++;
                }
                }

                if(CANAPP_au16MsgMissCnt[CANAPP_nbiESC_Status_0x125] >= 2)
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nEsc);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nEsc] = 0u;
                }
        }
}

void CANAPP_vReceiveMsg_MMI_HVSM_Command_0x2A3(void)
{/* Message received with every 100ms...*/
        uint16 u16DlcErrCode = 0u;
        uint16 u16DataValid = 0u;
        
        if(MMI_HVSM_Command_ind_b == True)
        {
                u16DlcErrCode = CANNMAPP_u16GetValue(CANNMAPP_u16MsgDlcErr);
                u16DataValid = CANNMAPP_u16GetValue(CANNMAPP_u16MsgValid);
                MMI_HVSM_Command_ind_b = 0x00;
                CANAPP_ErrCodeClr(CANAPP_nbiMMI_HVSM_Command_0x2A3);
                CANAPP_au16MsgMissCnt[CANAPP_nbiMMI_HVSM_Command_0x2A3] = 0;

                if((u16DataValid&(1<<CANAPP_nMmiHvsm))>0)
                {
                    CANAPP_MsgNeverRecFlgSet(CANAPP_nbiMMI_HVSM_Command_0x2A3);
                    CANAPP_au16Array[CANAPP_nu16MMI_DrvHeatReq] = b_MMI_DrvHeatReq_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_PassHeatReq] = b_MMI_PassHeatReq_b;
                }

                /*Check DLC err*/
                if((u16DlcErrCode&(1<<CANAPP_nMmiHvsm))>0)
                {
                    if(CANAPP_u16DlcrrorCounterArray[CANAPP_nMmiHvsm] < 10)
                    {
                        CANAPP_u16DlcrrorCounterArray[CANAPP_nMmiHvsm]++;
                    }
                    else
                    {
                        CANAPP_DlcErrCodeSet(CANAPP_nMmiHvsm);
                    }
                }
                else
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nMmiHvsm);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nMmiHvsm] = 0u;
                }
        }
        else
        {
                if(CANNMAPP_BusOffStart == True)
                {
                        CANAPP_ErrCodeClr(CANAPP_nbiMMI_HVSM_Command_0x2A3);
                        CANAPP_au16MsgMissCnt[CANAPP_nbiMMI_HVSM_Command_0x2A3] = 0;
                }
                else
                {
                if(CANAPP_au16MsgMissCnt[CANAPP_nbiMMI_HVSM_Command_0x2A3] >= CANAPP_MsgMissTimeout_MMI_HVSM_Command_0x2A3_MAX)
                {
                        if(CANAPP_MsgNeverRecFlgGet(CANAPP_nbiMMI_HVSM_Command_0x2A3) == True)
                        {
                                CANAPP_au16Array[CANAPP_nu16MMI_DrvHeatReq] = U16_MISS_VALUE;
                                CANAPP_au16Array[CANAPP_nu16MMI_PassHeatReq] = U16_MISS_VALUE;
                        }
                        CANAPP_ErrCodeSet(CANAPP_nbiMMI_HVSM_Command_0x2A3);
                }
                else
                {
                        CANAPP_au16MsgMissCnt[CANAPP_nbiMMI_HVSM_Command_0x2A3]++;
                }
                }

                if(CANAPP_au16MsgMissCnt[CANAPP_nbiMMI_HVSM_Command_0x2A3] >= 10)
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nMmiHvsm);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nMmiHvsm] = 0u;
                }
        }
}

void CANAPP_vReceiveMsg_MMI_AC_Command_0x2A5(void)
{/* Message received with every 100ms...*/
        uint16 u16DlcErrCode = 0u;
        uint16 u16DataValid = 0u;
        
        if(MMI_AC_Command_ind_b == True)
        {
                u16DlcErrCode = CANNMAPP_u16GetValue(CANNMAPP_u16MsgDlcErr);
                u16DataValid = CANNMAPP_u16GetValue(CANNMAPP_u16MsgValid);
                MMI_AC_Command_ind_b = 0x00;
                CANAPP_ErrCodeClr(CANAPP_nbiMMI_AC_Command_0x2A5);
                CANAPP_au16MsgMissCnt[CANAPP_nbiMMI_AC_Command_0x2A5] = 0;

                if((u16DataValid&(1<<CANAPP_nMmiAc))>0)
                {
                    CANAPP_MsgNeverRecFlgSet(CANAPP_nbiMMI_AC_Command_0x2A5);
                    CANAPP_au16Array[CANAPP_nu16MMI_AutoKey] = b_MMI_AutoKey_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_FrontDefrostKey] = b_MMI_FrontDefrostKey_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_FreshReciKey] = b_MMI_FreshReciKey_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_AqsKey] = b_MMI_AqsKey_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_AcKey] = b_MMI_AcKey_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_BlowerFanLevel] = b_MMI_BlowerFanLevel_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_DualKey] = b_MMI_DualKey_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_PM25Key] = b_MMI_PM25Key_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_IONIZERKey] = b_MMI_IONIZERKey_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_AirDistributionModeReq] = b_MMI_AirDistributionModeReq_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_PM25PopupActive] = b_MMI_PM25PopupActive_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_AirConditionerPowerKey] = b_MMI_AirConditionerPowerKey_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_LeftSetTemp] = b_MMI_LeftSetTemp_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_RightSetTemp] = b_MMI_RightSetTemp_b;
                    CANAPP_au16Array[CANAPP_nu16MMI_PM25PopupOperationSts] = b_MMI_PM25PopupOperationSts_b;
                }

                /*Check DLC err*/
                if((u16DlcErrCode&(1<<CANAPP_nMmiAc))>0)
                {
                    if(CANAPP_u16DlcrrorCounterArray[CANAPP_nMmiAc] < 10)
                    {
                        CANAPP_u16DlcrrorCounterArray[CANAPP_nMmiAc]++;
                    }
                    else
                    {
                        CANAPP_DlcErrCodeSet(CANAPP_nMmiAc);
                    }
                }
                else
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nMmiAc);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nMmiAc] = 0u;
                }
        }
        else
        {
                if(CANNMAPP_BusOffStart == True)
                {
                        CANAPP_ErrCodeClr(CANAPP_nbiMMI_AC_Command_0x2A5);
                        CANAPP_au16MsgMissCnt[CANAPP_nbiMMI_AC_Command_0x2A5] = 0;
                }
                else
                {
                    if(CANAPP_au16MsgMissCnt[CANAPP_nbiMMI_AC_Command_0x2A5] >= CANAPP_MsgMissTimeout_MMI_AC_Command_0x2A5_MAX)
                    {
                            if(CANAPP_MsgNeverRecFlgGet(CANAPP_nbiMMI_AC_Command_0x2A5) == True)
                            {
                                    CANAPP_au16Array[CANAPP_nu16MMI_AutoKey] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16MMI_FrontDefrostKey] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16MMI_FreshReciKey] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16MMI_AqsKey] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16MMI_AcKey] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16MMI_BlowerFanLevel] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16MMI_DualKey] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16MMI_PM25Key] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16MMI_IONIZERKey] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16MMI_AirDistributionModeReq] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16MMI_PM25PopupActive] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16MMI_AirConditionerPowerKey] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16MMI_LeftSetTemp] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16MMI_RightSetTemp] = U16_MISS_VALUE;
                                    CANAPP_au16Array[CANAPP_nu16MMI_PM25PopupOperationSts] = U16_MISS_VALUE;
                            }
                            CANAPP_ErrCodeSet(CANAPP_nbiMMI_AC_Command_0x2A5);
                    }
                    else
                    {
                            CANAPP_au16MsgMissCnt[CANAPP_nbiMMI_AC_Command_0x2A5]++;
                    }
                }
                
                if(CANAPP_au16MsgMissCnt[CANAPP_nbiMMI_AC_Command_0x2A5] >= 10)
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nMmiAc);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nMmiAc] = 0u;
                }
        }
}

void CANAPP_vReceiveMsg_IPK_TotalOdometer_0x3F1(void)
{/* Message received with every 1000ms...*/
        uint16 u16DlcErrCode = 0u;
        uint16 u16DataValid = 0u;
        
        if(IPK_TotalOdometer_ind_b == True)
        {
                u16DlcErrCode = CANNMAPP_u16GetValue(CANNMAPP_u16MsgDlcErr);
                u16DataValid = CANNMAPP_u16GetValue(CANNMAPP_u16MsgValid);
                IPK_TotalOdometer_ind_b = 0x00;
                CANAPP_ErrCodeClr(CANAPP_nbiIPK_TotalOdometer_0x3F1);
                CANAPP_au16MsgMissCnt[CANAPP_nbiIPK_TotalOdometer_0x3F1] = 0;

                if((u16DataValid&(1<<CANAPP_nIpk))>0)
                {
                    CANAPP_MsgNeverRecFlgSet(CANAPP_nbiIPK_TotalOdometer_0x3F1);
                    CANAPP_au32Array[CANAPP_nu32IPK_IPKTotalOdometer] = b_IPK_IPKTotalOdometer_b;
                }

                /*Check DLC err*/
                if((u16DlcErrCode&(1<<CANAPP_nIpk))>0)
                {
                    if(CANAPP_u16DlcrrorCounterArray[CANAPP_nIpk] < 10)
                    {
                        CANAPP_u16DlcrrorCounterArray[CANAPP_nIpk]++;
                    }
                    else
                    {
                        CANAPP_DlcErrCodeSet(CANAPP_nIpk);
                    }
                }
                else
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nIpk);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nIpk] = 0u;
                }
        }
        else
        {
                if(CANNMAPP_BusOffStart == True)
                {
                        CANAPP_ErrCodeClr(CANAPP_nbiIPK_TotalOdometer_0x3F1);
                        CANAPP_au16MsgMissCnt[CANAPP_nbiIPK_TotalOdometer_0x3F1] = 0;
                }
                else
                {
                if(CANAPP_au16MsgMissCnt[CANAPP_nbiIPK_TotalOdometer_0x3F1] >= CANAPP_MsgMissTimeout_IPK_TotalOdometer_0x3F1_MAX)
                {
                        if(CANAPP_MsgNeverRecFlgGet(CANAPP_nbiIPK_TotalOdometer_0x3F1) == True)
                        {
                                CANAPP_au32Array[CANAPP_nu32IPK_IPKTotalOdometer] = U32_MISS_VALUE;
                        }
                        CANAPP_ErrCodeSet(CANAPP_nbiIPK_TotalOdometer_0x3F1);
                }
                else
                {
                        CANAPP_au16MsgMissCnt[CANAPP_nbiIPK_TotalOdometer_0x3F1]++;
                }
                }

                if(CANAPP_au16MsgMissCnt[CANAPP_nbiIPK_TotalOdometer_0x3F1] >= 100)
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nIpk);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nIpk] = 0u;
                }
        }
}

void CANAPP_vReceiveMsg_TBOX_RemCon_0x292(void)
{/* Message received with every 100ms...*/
        uint16 u16DlcErrCode = 0u;
        uint16 u16DataValid = 0u;
        
        if(TBOX_RemCon_ind_b == True)
        {
                u16DlcErrCode = CANNMAPP_u16GetValue(CANNMAPP_u16MsgDlcErr);
                u16DataValid = CANNMAPP_u16GetValue(CANNMAPP_u16MsgValid);
                TBOX_RemCon_ind_b = 0x00;
                CANAPP_ErrCodeClr(CANAPP_nbiTBOX_RemCon_0x292);
                CANAPP_au16MsgMissCnt[CANAPP_nbiTBOX_RemCon_0x292] = 0;

                if((u16DataValid&(1<<CANAPP_nTbox))>0)
                {
                    CANAPP_MsgNeverRecFlgSet(CANAPP_nbiTBOX_RemCon_0x292);
                    CANAPP_au16Array[CANAPP_nu16TBOX_Inquire_PM25] = b_TBOX_Inquire_PM25_b;
                    CANAPP_au16Array[CANAPP_nu16TBOX_AirCleanerReq] = b_TBOX_AirCleanerReq_b;
                    CANAPP_au16Array[CANAPP_nu16TBOX_TempReq] = b_TBOX_TempReq_b;
                    CANAPP_au16Array[CANAPP_nu16TBOX_AirConditionerReq] = b_TBOX_AirConditionerReq_b;
                }

                /*Check DLC err*/
                if((u16DlcErrCode&(1<<CANAPP_nTbox))>0)
                {
                    if(CANAPP_u16DlcrrorCounterArray[CANAPP_nTbox] < 10)
                    {
                        CANAPP_u16DlcrrorCounterArray[CANAPP_nTbox]++;
                    }
                    else
                    {
                        CANAPP_DlcErrCodeSet(CANAPP_nTbox);
                    }
                }
                else
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nTbox);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nTbox] = 0u;
                }
        }
        else
        {
                if(CANNMAPP_BusOffStart == True)
                {
                        CANAPP_ErrCodeClr(CANAPP_nbiTBOX_RemCon_0x292);
                        CANAPP_au16MsgMissCnt[CANAPP_nbiTBOX_RemCon_0x292] = 0;
                }
                else
                {
                if(CANAPP_au16MsgMissCnt[CANAPP_nbiTBOX_RemCon_0x292] >= CANAPP_MsgMissTimeout_TBOX_RemCon_0x292_MAX)
                {
                        if(CANAPP_MsgNeverRecFlgGet(CANAPP_nbiTBOX_RemCon_0x292) == True)
                        {
                                CANAPP_au16Array[CANAPP_nu16TBOX_Inquire_PM25] = U16_MISS_VALUE;
                                CANAPP_au16Array[CANAPP_nu16TBOX_AirCleanerReq] = U16_MISS_VALUE;
                                CANAPP_au16Array[CANAPP_nu16TBOX_TempReq] = U16_MISS_VALUE;
                                CANAPP_au16Array[CANAPP_nu16TBOX_AirConditionerReq] = U16_MISS_VALUE;
                        }
                        CANAPP_ErrCodeSet(CANAPP_nbiTBOX_RemCon_0x292);
                }
                else
                {
                        CANAPP_au16MsgMissCnt[CANAPP_nbiTBOX_RemCon_0x292]++;
                }
                }

                if(CANAPP_au16MsgMissCnt[CANAPP_nbiTBOX_RemCon_0x292] >= 10)
                {
                    CANAPP_DlcErrCodeClr(CANAPP_nTbox);
                    CANAPP_u16DlcrrorCounterArray[CANAPP_nTbox] = 0u;
                }
        }
}


/* Const code area...*/
/*****************************************************************************
* Function   : void CANAPP_vReset (void)
* Description: this function will be call in CANCCL Reset
* Returns   : Nothing
******************************************************************************/
void CANAPP_vReset(void)
{
	/*Reset  Send Message Cycle Timer */
	CANAPP_u16SendMsgTimer_20ms = 0;
	CANAPP_u16SendMsgTimer_40ms = 0;
	CANAPP_u16SendMsgTimer_50ms = 0;
	CANAPP_u16SendMsgTimer_100ms = 0;
	CANAPP_u16SendMsgTimer_200ms = 0;
	CANAPP_u16SendMsgTimer_400ms = 0;
	CANAPP_u16SendMsgTimer_500ms = 0;
	CANAPP_u16SendMsgTimer_1000ms = 0;
	/*Clear Message Never Receive Flag and Reset the CAN signals*/
	for(uint8 u16_i = 0x00; u16_i < CANAPP_nu16Max; u16_i++)
	{
		CANAPP_au16Array[u16_i] = U16_INIT_VALUE;
	}	
	CANAPP_AllMsgNeverRecFlgClr();
	/*Clear Message Miss Error Code and Error Counter */
	for(uint16 u16_i = 0x00; u16_i < CANAPP_nbiNumberRevMesg; u16_i++)
	{
		CANAPP_au16MsgMissCnt[u16_i] = 0;
	}
	for(uint16 u16_i = 0x00; u16_i < CANAPP_nMax; u16_i++)
	{
		CANAPP_u16DlcrrorCounterArray[u16_i] = 0;
	}
	CANAPP_AllErrCodeClr();	
    CANAPP_AllDlcErrCodeClr();
}
/*****************************************************************************
* Function   : void CANAPP_vMain (void)
* Description: this function will be call every 10ms
* Returns   : Nothing
******************************************************************************/
void CANAPP_vMain_10ms(void)
{
	/*Update content of Send Messages*/
	CANAPP_vSendMsgUpdate();
	/*Send Message To CAN BUS*/
	CANAPP_vSendMsg_10ms();
	CANAPP_vSendMsg_20ms();
	CANAPP_vSendMsg_40ms();
	CANAPP_vSendMsg_50ms();
	CANAPP_vSendMsg_100ms();
	CANAPP_vSendMsg_200ms();
	CANAPP_vSendMsg_400ms();
	CANAPP_vSendMsg_500ms();
	CANAPP_vSendMsg_1000ms();
	/*Receive Message From CAN BUS*/
	CANAPP_vReceiveMsg();
}
/*****************************************************************************
* Function   : uint16 CANAPP_u16GetValue (CANAPP_tenu16VarNumber enIndex)
* Description: you can use this function to get any singles you want from the CANAPP
* Returns   : Nothing
******************************************************************************/
uint16 CANAPP_u16GetValue(CANAPP_tenu16VarNumber enIndex)
{
	if(enIndex < CANAPP_nu16Max)
	{
		return (CANAPP_au16Array[enIndex]);
	}
	else
	{
		return (CANAPP_au16Array[CANAPP_nu16Max-1]);
	}
}
/*****************************************************************************
* Function   : uint32 CANAPP_u32GetValue (CANAPP_u32GetValue enIndex)
* Description: you can use this function to get any singles you want from the CANAPP
* Returns   : Nothing
******************************************************************************/
uint32 CANAPP_u32GetValue(CANAPP_tenu32VarNumber enIndex)
{
	if(enIndex < CANAPP_nu32Max)
	{
		return (CANAPP_au32Array[enIndex]);
	}
	else
	{
		return (CANAPP_au32Array[CANAPP_nu32Max-1]);
	}
}
void CANAPP_vClearMsgMissError(void)
{
	CANAPP_AllErrCodeClr();
    CANAPP_AllDlcErrCodeClr();
	for(uint8 u8_i = 0x00; u8_i < CANAPP_nbiNumberRevMesg; u8_i++)
	{
		CANAPP_au16MsgMissCnt[u8_i] = 0x00;
	}
	for(uint16 u16_i = 0x00; u16_i < CANAPP_nMax; u16_i++)
	{
		CANAPP_u16DlcrrorCounterArray[u16_i] = 0;
	}
}

void CANAPP_vSendMsg_AC_LIN2CANData_0x6B3(uint8 Data_0,uint8 Data_1,\
	uint8 Data_2,uint8 Data_3,uint8 Data_4,uint8 Data_5,uint8 Data_6,uint8 Data_7)
{/* Message tranmit with every 50ms...*/
        if(AC_LIN2CANData_conf_b == True)
        {
                CanWriteSyncAC_LIN2CANData_conf_b(0);
                b_ForLinData0_c=Data_0;
                b_ForLinData1_c=Data_1;
                b_ForLinData2_c=Data_2;
                b_ForLinData3_c=Data_3;
                b_ForLinData4_c=Data_4;
                b_ForLinData5_c=Data_5;
                b_ForLinData6_c=Data_6;
                b_ForLinData7_c=Data_7;
        }
        CanTransmit(CanTxAC_LIN2CANData);
}
void CANAPP_vSendMsg_AC_LIN2CANCom_0x6B0(uint8 Data_0,uint8 Data_1,\
	uint8 Data_2,uint8 Data_3,uint8 Data_4,uint8 Data_5,uint8 Data_6,uint8 Data_7)
{/* Message tranmit with every 50ms...*/
        if(AC_LIN2CANCom_conf_b == True)
        {
		        CanWriteSyncAC_LIN2CANCom_conf_b(0);
                b_ForLinComman0_c=Data_0;
                b_ForLinComman1_c=Data_1;
                b_ForLinComman2_c=Data_2;
                b_ForLinComman3_c=Data_3;
                b_ForLinComman4_c=Data_4;
                b_ForLinComman5_c=Data_5;
                b_ForLinComman6_c=Data_6;
                b_ForLinComman7_c=Data_7;
        }
        CanTransmit(CanTxAC_LIN2CANCom);
}


