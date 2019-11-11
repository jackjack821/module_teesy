/*******************************************************************************
| Module Name: Recirculation Fresh Air control interface
| File Name: RFA_Interface.c
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
| Li Jiaye                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2016.7.1          A0      Luo Xindian        First created for base code.  
| 
| 
********************************************************************************/


/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define RFA_Interface                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
//#include "Rte_rfa.h"
#include "ALG.h"
#include "POW.h"
#include "OAT.h"
#include "MMI.h"
#include "CCS.h"
#include "FRAME_IF.h"
#include "AQS.h"
#include "ION.h"

/* Own headerfiles */
#include "RFA_Cfg.h"
#include "RFA_Type.h"
#include "RFA_Private.h"
#include "RFA.h"      
#include "RFA_interface.h"

/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/


RFA_tenValueSts RFA_enU16InputValueCalc(RFA_tstU16InputAttributes *Input, uint16 *Output);
RFA_tenValueSts RFA_enU8InputValueCalc(RFA_tstU8InputAttributes *Input, uint8 *Output);

/*============================================================================
*Function : RFA_tenValueSts RFA_enPowFailureImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
RFA_tenValueSts RFA_enPowFailureImport(uint8 *value)
{
    RFA_tenValueSts enRet;
    RFA_tstU8InputAttributes RFA_stU8InputAttributes;
    static uint8 u8LastOutput;

	#if(RFA_nUseRTE == True)
    RFA_stU8InputAttributes.u8InputValue=Rte_IRead_Aird_vMain_AirdGetBattHighVoltage_BattHighVoltage()|\
        Rte_IRead_Aird_vMain_AirdGetBattLowVoltage_BattLowVoltage();
	#else
    RFA_stU8InputAttributes.u8InputValue=POW_u16GetValue(POW_nu16AppLowVoltage)|\
        POW_u16GetValue(POW_nu16AppHighVoltage);
	#endif
	
    RFA_enGetU8InitCounterExport(&RFA_stU8InputAttributes.u8ErrCounter);
    RFA_stU8InputAttributes.u8LastInput=&u8LastOutput;
    RFA_stU8InputAttributes.u8Default=0u;
    RFA_stU8InputAttributes.u8MinVal=0u;
    RFA_stU8InputAttributes.u8MaxVal=1u;
    RFA_stU8InputAttributes.u8ErrWaitTime=5u;/*500ms*/

    enRet=RFA_enU8InputValueCalc(&RFA_stU8InputAttributes,value);
    return enRet;
}

/*============================================================================
*Function :RFA_tenValueSts RFA_enMMIModeImport(RFA_tenMMIModeSts *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
RFA_tenValueSts RFA_enMMIModeImport(RFA_tenRecircModeStates *value)
{    
    RFA_tenValueSts enRet;
    RFA_tstU8InputAttributes RFA_stU8InputAttributes;
    static uint8 u8LastOutput;
	
    #if(RFA_nUseRTE == True)
    RFA_stU8InputAttributes.u8InputValue=Rte_IRead_Rfa_vMain_RfaGetMmiRfaMode_MmiRfaMode();

	#else
    RFA_stU8InputAttributes.u8InputValue=MMI_u8GetValue(MMI_nu8RecirMode);
	#endif
	
    RFA_enGetU8InitCounterExport(&RFA_stU8InputAttributes.u8ErrCounter);
    RFA_stU8InputAttributes.u8LastInput=&u8LastOutput;
    RFA_stU8InputAttributes.u8Default=(uint8)RFA_nMmiRfaModeOff;
    RFA_stU8InputAttributes.u8MinVal=(uint8)RFA_nMmiRfaModeManual;
    RFA_stU8InputAttributes.u8MaxVal=(uint8)RFA_nMmiRfaModeMaxAc;
    RFA_stU8InputAttributes.u8ErrWaitTime=5u;/*500ms*/

    enRet=RFA_enU8InputValueCalc(&RFA_stU8InputAttributes,value);
    return enRet;
}
/*============================================================================
*Function : RFA_tenValueSts RFA_enMMIControlImport(RFA_tenRecircStates *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
RFA_tenValueSts RFA_enMMIControlImport(RFA_tenRecircStates *value)
{
    RFA_tenValueSts enRet;
    RFA_tstU8InputAttributes RFA_stU8InputAttributes;
    static uint8 u8LastOutput;
    #if(RFA_nUseRTE == True)
    RFA_stU8InputAttributes.u8InputValue=Rte_IRead_Rfa_vMain_RfaGetMmiRfaControl_MmiRfaControl();
	#else
    RFA_stU8InputAttributes.u8InputValue=MMI_u8GetValue(MMI_nu8RecirControl);
	#endif
	
    RFA_enGetU8InitCounterExport(&RFA_stU8InputAttributes.u8ErrCounter);
    RFA_stU8InputAttributes.u8LastInput=&u8LastOutput;
    RFA_stU8InputAttributes.u8Default=(uint8)RFA_nRecircFresh;
    RFA_stU8InputAttributes.u8MinVal=(uint8)RFA_nRecircFresh;
    RFA_stU8InputAttributes.u8MaxVal=(uint8)RFA_nRecircle;
    RFA_stU8InputAttributes.u8ErrWaitTime=5u;/*500ms*/

    enRet=RFA_enU8InputValueCalc(&RFA_stU8InputAttributes,value);

    return enRet;
}

#if (RFA_biSystemState == True)
/*============================================================================
*Function : RFA_tenValueSts RFA_enCcsBloutTempImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
RFA_tenValueSts RFA_enCcsBloutTempImport(uint16 *value)
{
    RFA_tenValueSts enRet;
    RFA_tstU16InputAttributes RFA_stU16InputAttributes;
    static uint16 u16LastOutput;
	#if(RFA_nUseRTE == True)
    RFA_stU16InputAttributes.u16InputValue=Rte_IRead_Aird_vMain_AirdGetCcsBlowoutTempDr_CcsBlowoutTempDr();
	#else
    #if(SYC_ZONES == 2)
	RFA_stU16InputAttributes.u16InputValue=MIN(CCS_u16GetValue(CCS_nu16BlowoutTempDr),CCS_u16GetValue(CCS_nu16BlowoutTempPs));
    #else
    RFA_stU16InputAttributes.u16InputValue=CCS_u16GetValue(CCS_nu16BlowoutTempDr);
    #endif
	#endif
	
    RFA_enGetU8InitCounterExport(&RFA_stU16InputAttributes.u8ErrCounter);
    RFA_stU16InputAttributes.u16LastInput=&u16LastOutput;
    RFA_stU16InputAttributes.u16Default=700u;/*30degree*/
    RFA_stU16InputAttributes.u16MinVal=0u;/*-40degree*/
    RFA_stU16InputAttributes.u16MaxVal=1600u;/*120degree*/
    RFA_stU16InputAttributes.u8ErrWaitTime=5u;/*500ms*/
    
    enRet=RFA_enU16InputValueCalc(&RFA_stU16InputAttributes,value);

    return enRet;
}


/*============================================================================
*Function : RFA_tenValueSts RFA_enOATValueImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
RFA_tenValueSts RFA_enOATValueImport(uint16 *value)
{
    RFA_tenValueSts enRet;
    RFA_tstU16InputAttributes RFA_stU16InputAttributes;
    static uint16 u16LastOutput;
	#if(RFA_nUseRTE == True)
    RFA_stU16InputAttributes.u16InputValue=Rte_IRead_Aird_vMain_AirdGetOatValue_OatValue();
	#else
    RFA_stU16InputAttributes.u16InputValue=OAT_u16GetValue(OAT_nu16Value);
	#endif
	
    RFA_enGetU8InitCounterExport(&RFA_stU16InputAttributes.u8ErrCounter);
    RFA_stU16InputAttributes.u16LastInput=&u16LastOutput;
    RFA_stU16InputAttributes.u16Default=600u;/*20degree*/
    RFA_stU16InputAttributes.u16MinVal=0u;/*-40degree*/
    RFA_stU16InputAttributes.u16MaxVal=1600u;/*120degree*/
    RFA_stU16InputAttributes.u8ErrWaitTime=5u;/*500ms*/
    
    enRet=RFA_enU16InputValueCalc(&RFA_stU16InputAttributes,value);
    return enRet;
}

/*============================================================================
*Function : RFA_tenValueSts RFA_enSys1000msValueImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
RFA_tenValueSts RFA_enSys1000msValueImport(uint8 *value)
{
    RFA_tenValueSts enRet;
    RFA_tstU8InputAttributes RFA_stU8InputAttributes;
    static uint8 u8LastOutput;
	#if(RFA_nUseRTE == True)
    RFA_stU8InputAttributes.u8InputValue=Rte_IRead_Aird_vMain_AirdGetOatValue_OatValue();
	#else
    RFA_stU8InputAttributes.u8InputValue=(uint8)FRAME_u16GetValue(SYS_nu16Flag1000MS_BG);
	#endif
	
    RFA_enGetU8InitCounterExport(&RFA_stU8InputAttributes.u8ErrCounter);
    RFA_stU8InputAttributes.u8LastInput=&u8LastOutput;
    RFA_stU8InputAttributes.u8Default=0u;/*0*/
    RFA_stU8InputAttributes.u8MinVal=0u;/*0*/
    RFA_stU8InputAttributes.u8MaxVal=1u;/*1*/
    RFA_stU8InputAttributes.u8ErrWaitTime=5u;/*500ms*/
    
    enRet=RFA_enU8InputValueCalc(&RFA_stU8InputAttributes,value);
    return enRet;
}
#endif

#if(RFA_biAQS_Cfg == True)
/*============================================================================
*Function : RFA_tenValueSts RFA_enAqsReqValueImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
RFA_tenValueSts RFA_enAqsReqValueImport(uint8 *value)
{
    RFA_tenValueSts enRet;
    RFA_tstU8InputAttributes RFA_stU8InputAttributes;
    static uint8 u8LastOutput;
	#if(RFA_nUseRTE == True)
    RFA_stU8InputAttributes.u8InputValue=Rte_IRead_Aird_vMain_AirdGetHctValue_AqsTemp();
	#else
    RFA_stU8InputAttributes.u8InputValue=MMI_u8GetValue(MMI_nu8AqsRequest);
	#endif
	
    RFA_enGetU8InitCounterExport(&RFA_stU8InputAttributes.u8ErrCounter);
    RFA_stU8InputAttributes.u8LastInput=&u8LastOutput;
    RFA_stU8InputAttributes.u8Default=0u;/*Off*/
    RFA_stU8InputAttributes.u8MinVal=0u;/*Off*/
    RFA_stU8InputAttributes.u8MaxVal=1;/*On*/
    RFA_stU8InputAttributes.u8ErrWaitTime=5u;/*500ms*/
    
    enRet=RFA_enU8InputValueCalc(&RFA_stU8InputAttributes,value);
    return enRet;
}

/*============================================================================
*Function : RFA_tenValueSts RFA_enAqsStateValueImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
RFA_tenValueSts RFA_enAqsStateValueImport(uint8 *value)
{
    RFA_tenValueSts enRet;
    RFA_tstU8InputAttributes RFA_stU8InputAttributes;
    static uint8 u8LastOutput;
	#if(RFA_nUseRTE == True)
    RFA_stU8InputAttributes.u8InputValue=Rte_IRead_Aird_vMain_AirdGetHctValue_AqsTemp();
	#else
    RFA_stU8InputAttributes.u8InputValue=AQS_u8GetValue(AQS_nu8State);
	#endif
	
    RFA_enGetU8InitCounterExport(&RFA_stU8InputAttributes.u8ErrCounter);
    RFA_stU8InputAttributes.u8LastInput=&u8LastOutput;
    RFA_stU8InputAttributes.u8Default=0;/*not abd air*/
    RFA_stU8InputAttributes.u8MinVal=0u;
    RFA_stU8InputAttributes.u8MaxVal=1;/*bad air*/
    RFA_stU8InputAttributes.u8ErrWaitTime=5u;/*500ms*/
    
    enRet=RFA_enU8InputValueCalc(&RFA_stU8InputAttributes,value);
    return enRet;
}
#endif

#if(RFA_nPM25Cfg == True)
/*============================================================================
*Function : RFA_tenValueSts RFA_enPM25InSideValueImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
RFA_tenValueSts RFA_enPM25InSideValueImport(uint16 *value)
{
    RFA_tenValueSts enRet;
    RFA_tstU16InputAttributes RFA_stU16InputAttributes;
    static uint16 u16LastOutput;
	#if(RFA_nUseRTE == True)
    RFA_stU16InputAttributes.u16InputValue=Rte_IRead_Aird_vMain_AirdGetHctValue_AqsTemp();
	#else
    RFA_stU16InputAttributes.u16InputValue=ION_u16GetValue(ION_nu16PM25InDen);
	#endif
	
    RFA_enGetU8InitCounterExport(&RFA_stU16InputAttributes.u8ErrCounter);
    RFA_stU16InputAttributes.u16LastInput=&u16LastOutput;
    RFA_stU16InputAttributes.u16Default=0;/*not abd air*/
    RFA_stU16InputAttributes.u16MinVal=0u;
    RFA_stU16InputAttributes.u16MaxVal=1;/*bad air*/
    RFA_stU16InputAttributes.u8ErrWaitTime=5u;/*500ms*/
    
    enRet=RFA_enU16InputValueCalc(&RFA_stU16InputAttributes,value);
    return enRet;
}

/*============================================================================
*Function : RFA_tenValueSts RFA_enPM25OutSideValueImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
RFA_tenValueSts RFA_enPM25OutSideValueImport(uint16 *value)
{
    RFA_tenValueSts enRet;
    RFA_tstU16InputAttributes RFA_stU16InputAttributes;
    static uint16 u16LastOutput;
	#if(RFA_nUseRTE == True)
    RFA_stU16InputAttributes.u16InputValue=Rte_IRead_Aird_vMain_AirdGetHctValue_AqsTemp();
	#else
    RFA_stU16InputAttributes.u16InputValue=ION_u16GetValue(ION_nu16PM25OutDen);
	#endif
	
    RFA_enGetU8InitCounterExport(&RFA_stU16InputAttributes.u8ErrCounter);
    RFA_stU16InputAttributes.u16LastInput=&u16LastOutput;
    RFA_stU16InputAttributes.u16Default=0;/*not bad air*/
    RFA_stU16InputAttributes.u16MinVal=0u;
    RFA_stU16InputAttributes.u16MaxVal=1;/*bad air*/
    RFA_stU16InputAttributes.u8ErrWaitTime=5u;/*500ms*/
    
    enRet=RFA_enU16InputValueCalc(&RFA_stU16InputAttributes,value);
    return enRet;
}
#endif

#if(RFA_biStartStop_Cfg == True)

#endif

#if(RFA_nUseRTE == True)
/*============================================================================
*Function : void RFA_vOutputUpdate(void)
*Description : Local value after caculation need to transmit to RTE
*takes : nothing
*return: Nothing
*/
void RFA_vOutputUpdate(void)
{
    RFA_tenValueSts enValueSts;
    RFA_tstMainOut stMainOut;
    enValueSts=RFA_enGetStMainOutExport(&stMainOut);

    Rte_IWrite_Aird_vMain_AirdPutAirdSetPos_AirdSetPos(stMainOut.u16SetPosition);
    Rte_IWrite_Aird_vMain_AirdPutAirdDisplay_AirdDisplay(stMainOut.enAirdDisplay);
    Rte_IWrite_Aird_vMain_AirdPutAutoControl_AirdAutoControl(stMainOut.enAutoControlsts);
    Rte_IWrite_Aird_vMain_AirdPutAirdValid_AirdValid(True);
}
#endif
/*============================================================================
*Function : RFA_tenValueSts RFA_enU16InputValueCalc(RFA_tstU16InputAttributes *Input, uint16 *Output)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
RFA_tenValueSts RFA_enU16InputValueCalc(RFA_tstU16InputAttributes *Input, uint16 *Output)
{
    RFA_tenValueSts enRet;
    if(Input->u16InputValue==0xFFFF)
    {
        if(Input->u8ErrCounter<Input->u8ErrWaitTime)
        {
            enRet=RFA_nInvalid;
        }
        else
        {
           enRet=RFA_nDefault;
           *Output=Input->u16Default;
        }
    }
    else
    {
        if((Input->u16InputValue<Input->u16MinVal)||(Input->u16InputValue>Input->u16MaxVal))
        {
          *Output=*(Input->u16LastInput);
          enRet=RFA_nLastValue;
        }
        else
        {
          *Output=Input->u16InputValue;
          enRet=RFA_nValid;
        }
    }
    *(Input->u16LastInput)=*Output;
    return enRet;
}

/*============================================================================
*Function : RFA_tenValueSts RFA_enU8InputValueCalc(RFA_tstU8InputAttributes *Input, uint8 *Output)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
RFA_tenValueSts RFA_enU8InputValueCalc(RFA_tstU8InputAttributes *Input, uint8 *Output)
{
    RFA_tenValueSts enRet;
    if(Input->u8InputValue==0xFF)
    {
        if(Input->u8ErrCounter<Input->u8ErrWaitTime)
        {
            enRet=RFA_nInvalid;
        }
        else
        {
           enRet=RFA_nDefault;
           *Output=Input->u8Default;
        }
    }
    else
    {
        if((Input->u8InputValue<Input->u8MinVal)||(Input->u8InputValue>Input->u8MaxVal))
        {
          *Output=*(Input->u8LastInput);
          enRet=RFA_nLastValue;
        }
        else
        {
          *Output=Input->u8InputValue;
          enRet=RFA_nValid;
        }
    }
    *(Input->u8LastInput)=*Output;
    return enRet;
}

/*****************************************************************************
* EOF: DCM_Cfg.c
*****************************************************************************/
