/*******************************************************************************
| Module Name: Air distribution control interface
| File Name: AIRD_Interface.c
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
| 2016.5.17         A0      Li jiaye         module template update. 
| 
| 
********************************************************************************/


/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define AIRD_Interface                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"
#include "POW.h"
/* Foreign headerfiles */
#include "ALG.h"
#include "MMI.h"
#include "OAT.h"
#include "CCS.h"
#include "HCT.h"

/* Own headerfiles */
#include "Aird_Cfg.h"
#include "AIRD_Type.h"
#include "AIRD_Private.h"
#include "AIRD.h"      
#include "AIRD_interface.h"

/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/


static uint8 Aird_CcpForceFlag=0;
static uint16 Aird_CcpControlData[Aird_nCcpForceMax];
#define AirdGetCcpForceBit(index)	((Aird_CcpForceFlag>>index)&0x01u)
#define AirdSetCcpForceBit(index)	(Aird_CcpForceFlag=Aird_CcpForceFlag|(0x01u<<index))
#define AirdClrCcpForceBit(index)	(Aird_CcpForceFlag=Aird_CcpForceFlag&(~(0x01u<<index)))
#define AirdClrCcpForceByte()	    (Aird_CcpForceFlag=0u)

AIRD_tenValueSts AIRD_enU16InputValueCalc(AIRD_tstU16InputAttributes *Input, uint16 *Output);
AIRD_tenValueSts AIRD_enU8InputValueCalc(AIRD_tstU8InputAttributes *Input, uint8 *Output);


/*****************************************************************************
 Function      : AIRD_u8ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType AIRD_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord)
{
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				AirdClrCcpForceByte();
				break;
			case 1:
				AirdSetCcpForceBit(Aird_nSetPosition);
				Aird_CcpControlData[Aird_nSetPosition]=CcpControlWord.CcpContronData;
				break;
			case 2:
				AirdClrCcpForceBit(Aird_nSetPosition);
				Aird_CcpControlData[Aird_nSetPosition]=0;
				break;
			case 3:
				break;
			case 4:
				break;
                
			case 0xA1:
				AirdSetCcpForceBit(Aird_nSetPosition);
				Aird_CcpControlData[Aird_nSetPosition]=CcpControlWord.CcpContronData;
				break;
			case 0xA2:
				AirdClrCcpForceBit(Aird_nSetPosition);
				Aird_CcpControlData[Aird_nSetPosition]=0;
				break;
			case 0xA3:
				AirdSetCcpForceBit(Aird_nSetPosition);
                if(CcpControlWord.CcpContronData < AIRD_nAirdManuPositionTbl_Len)
                {
                    Aird_CcpControlData[Aird_nSetPosition] = AIRD_au16Group1AirdManuPosition_Tbl[CcpControlWord.CcpContronData];
                }
                else
                {
				    Aird_CcpControlData[Aird_nSetPosition]=CcpControlWord.CcpContronData;
                }
				break;
			case 0xA4:
				AirdClrCcpForceBit(Aird_nSetPosition);
				Aird_CcpControlData[Aird_nSetPosition]=0;
				break;
			default:
                return RTE_E_INVALID;
		}
	}
	else
	{
		AirdClrCcpForceByte();
	}
        return RTE_E_OK;
}


/*============================================================================
*Function : void AIRD_vClrForceFlagByteAction(void)
*Description : 
*takes : nothing
*return: nothing
*/
void AIRD_vClrForceFlagByteAction(void)
{
    AirdClrCcpForceByte();
}

/*============================================================================
*Function : AIRD_tenValueSts AIRD_enPowFailureImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
AIRD_tenValueSts AIRD_enPowFailureImport(uint8 *value)
{
    AIRD_tenValueSts enRet;
    AIRD_tstU8InputAttributes AIRD_stU8InputAttributes;
    static uint8 u8LastOutput=0u;
    
    AIRD_stU8InputAttributes.u8InputValue=AIRD_boPowerCheck();
    AIRD_enGetU8InitCounterExport(&AIRD_stU8InputAttributes.u8ErrCounter);
    AIRD_stU8InputAttributes.u8LastInput=&u8LastOutput;
    AIRD_stU8InputAttributes.u8Default=0u;
    AIRD_stU8InputAttributes.u8MinVal=0u;
    AIRD_stU8InputAttributes.u8MaxVal=1u;
    AIRD_stU8InputAttributes.u8ErrWaitTime=5u;/*500ms*/

    enRet=AIRD_enU8InputValueCalc(&AIRD_stU8InputAttributes,value);
    return enRet;
}

/*============================================================================
*Function : AIRD_tenValueSts AIRD_enMMIModeImport(AIRD_tenMMIModeSts *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
AIRD_tenValueSts AIRD_enMMIModeImport(AIRD_tenMMIModeSts *value)
{    
    AIRD_tenValueSts enRet;
    AIRD_tstU8InputAttributes AIRD_stU8InputAttributes;
    static uint8 u8LastOutput=(uint8)AIRD_nMmiAirdModeManual;
    uint8 u8Temp=(uint8)*value;

    
    AIRD_stU8InputAttributes.u8InputValue=AIRD_u8GetMmiModeValue();//Rte_IRead_Aird_vMain_Aird_MmiAirdMode_u8Set();
    AIRD_enGetU8InitCounterExport(&AIRD_stU8InputAttributes.u8ErrCounter);
    AIRD_stU8InputAttributes.u8LastInput=&u8LastOutput;
    AIRD_stU8InputAttributes.u8Default=(uint8)AIRD_nMmiAirdModeManual;
    AIRD_stU8InputAttributes.u8MinVal=(uint8)AIRD_nMmiAirdModeOff;
    AIRD_stU8InputAttributes.u8MaxVal=(uint8)AIRD_nMmiAirdModeMaxAc;
    AIRD_stU8InputAttributes.u8ErrWaitTime=5u;/*500ms*/

    enRet=AIRD_enU8InputValueCalc(&AIRD_stU8InputAttributes,&u8Temp);
    *value=(AIRD_tenMMIModeSts)u8Temp;
    return enRet;
}
/*============================================================================
*Function : AIRD_tenValueSts AIRD_enMMIControlImport(AIRD_tenMMIControlSts *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
AIRD_tenValueSts AIRD_enMMIControlImport(AIRD_tenMMIControlSts *value)
{
    AIRD_tenValueSts enRet;
    AIRD_tstU8InputAttributes AIRD_stU8InputAttributes;
    static uint8 u8LastOutput=(uint8)AIRD_nMmiAirDisBilevel;
    uint8 u8Temp=(uint8)*value;
    
    AIRD_stU8InputAttributes.u8InputValue=AIRD_u8GetMmiCtrlValue();//Rte_IRead_Aird_vMain_Aird_MmiAirdControl_u8Set();
    AIRD_enGetU8InitCounterExport(&AIRD_stU8InputAttributes.u8ErrCounter);
    AIRD_stU8InputAttributes.u8LastInput=&u8LastOutput;
    AIRD_stU8InputAttributes.u8Default=(uint8)AIRD_nMmiAirDisBilevel;
    AIRD_stU8InputAttributes.u8MinVal=(uint8)AIRD_nMmiAirDisFace;
    AIRD_stU8InputAttributes.u8MaxVal=(uint8)AIRD_nMmAirDisScreen;
    AIRD_stU8InputAttributes.u8ErrWaitTime=5u;/*500ms*/

    enRet=AIRD_enU8InputValueCalc(&AIRD_stU8InputAttributes,&u8Temp);
    *value=(AIRD_tenMMIControlSts)u8Temp;
    return enRet;
}

/*============================================================================
*Function : AIRD_tenValueSts AIRD_enCcsBloutTempImport(AIRD_tenMMIControlSts *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
AIRD_tenValueSts AIRD_enCcsBloutTempImport(uint16 *value)
{
    AIRD_tenValueSts enRet;
    AIRD_tstU16InputAttributes AIRD_stU16InputAttributes;
    static uint16 u16LastOutput=700u;

    AIRD_stU16InputAttributes.u16InputValue=AIRD_u16GetCcsValue();//Rte_IRead_Aird_vMain_Aird_CcsBlowoutTempAvg_u16Temp();
    AIRD_enGetU8InitCounterExport(&AIRD_stU16InputAttributes.u8ErrCounter);
    AIRD_stU16InputAttributes.u16LastInput=&u16LastOutput;
    AIRD_stU16InputAttributes.u16Default=700u;/*30degree*/
    AIRD_stU16InputAttributes.u16MinVal=0u;
    AIRD_stU16InputAttributes.u16MaxVal=1600u;/*120degree*/
    AIRD_stU16InputAttributes.u8ErrWaitTime=5u;/*500ms*/
    
    enRet=AIRD_enU16InputValueCalc(&AIRD_stU16InputAttributes,value);

    return enRet;
}

/*============================================================================
*Function : AIRD_tenValueSts AIRD_enOATValueImport(AIRD_tenMMIControlSts *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
AIRD_tenValueSts AIRD_enOATValueImport(uint16 *value)
{
    AIRD_tenValueSts enRet;
    AIRD_tstU16InputAttributes AIRD_stU16InputAttributes;
    static uint16 u16LastOutput=600u;

    AIRD_stU16InputAttributes.u16InputValue=AIRD_u16GetOatValue();//Rte_IRead_Aird_vMain_Aird_OatValue_u16Temp();
    AIRD_enGetU8InitCounterExport(&AIRD_stU16InputAttributes.u8ErrCounter);
    AIRD_stU16InputAttributes.u16LastInput=&u16LastOutput;
    AIRD_stU16InputAttributes.u16Default=600u;/*20degree*/
    AIRD_stU16InputAttributes.u16MinVal=0u;
    AIRD_stU16InputAttributes.u16MaxVal=1600u;/*120degree*/
    AIRD_stU16InputAttributes.u8ErrWaitTime=5u;/*500ms*/
    
    enRet=AIRD_enU16InputValueCalc(&AIRD_stU16InputAttributes,value);
    return enRet;
}

/*============================================================================
*Function : AIRD_tenValueSts AIRD_enHctValueImport(AIRD_tenMMIControlSts *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
AIRD_tenValueSts AIRD_enHctValueImport(uint16 *value)
{
    AIRD_tenValueSts enRet;
    AIRD_tstU16InputAttributes AIRD_stU16InputAttributes;
    static uint16 u16LastOutput=1200u;

    AIRD_stU16InputAttributes.u16InputValue=AIRD_u16GetHctValue();//Rte_IRead_Aird_vMain_Aird_HctValue_u16Temp();
    AIRD_enGetU8InitCounterExport(&AIRD_stU16InputAttributes.u8ErrCounter);
    AIRD_stU16InputAttributes.u16LastInput=&u16LastOutput;
    AIRD_stU16InputAttributes.u16Default=1200u;/*80degree*/
    AIRD_stU16InputAttributes.u16MinVal=0u;
    AIRD_stU16InputAttributes.u16MaxVal=1600u;/*120degree*/
    AIRD_stU16InputAttributes.u8ErrWaitTime=5u;/*500ms*/
    
    enRet=AIRD_enU16InputValueCalc(&AIRD_stU16InputAttributes,value);
    return enRet;
}

/*============================================================================
*Function : void AIRD_vOutputUpdate(void)
*Description : 
*takes : nothing
*return: Nothing
*/
void AIRD_vOutputUpdate(void)
{
    AIRD_tenValueSts enValueSts;
    Aird_tstMainOut stMainOut;
    enValueSts=AIRD_enGetStMainOutExport(&stMainOut);

    if(AirdGetCcpForceBit(Aird_nSetPosition))
	{
		stMainOut.u16SetPosition=Aird_CcpControlData[Aird_nSetPosition];
		stMainOut.enAirdDisplay=(AIRD_tenMMIControlSts)ALG_u16GetClosestEntry((uint16 *)AIRD_au16Group1AirdManuPosition_Tbl, AIRD_nAirdManuPositionTbl_Len, stMainOut.u16SetPosition);

        AIRD_enSetStMainOutExport(&stMainOut);
	}
#if 0
    Rte_IWrite_Aird_vMain_AirdSetPos_u16MotorPos(stMainOut.u16SetPosition);
    Rte_IWrite_Aird_vMain_AirdDisplay_u8DispInfo(stMainOut.enAirdDisplay);
    Rte_IWrite_Aird_vMain_AirdAutoControl_u8Set(stMainOut.enAutoControlsts);
    Rte_IWrite_Aird_vMain_AirdValid_u8Flag(True);
#endif
}
/*============================================================================
*Function : AIRD_tenValueSts AIRD_enU16InputValueCalc(AIRD_tstInputAttributes *Input, uint16 *Output)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
AIRD_tenValueSts AIRD_enU16InputValueCalc(AIRD_tstU16InputAttributes *Input, uint16 *Output)
{
    AIRD_tenValueSts enRet;
    if(Input->u16InputValue==0xFFFF)
    {
        if(Input->u8ErrCounter<Input->u8ErrWaitTime)
        {
            enRet=AIRD_nInvalid;
        }
        else
        {
           enRet=AIRD_nDefault;
           *Output=Input->u16Default;
        }
    }
    else
    {
        if((Input->u16InputValue<Input->u16MinVal)||(Input->u16InputValue>Input->u16MaxVal))
        {
          *Output=*(Input->u16LastInput);
          enRet=AIRD_nLastValue;
        }
        else
        {
          *Output=Input->u16InputValue;
          enRet=AIRD_nValid;
        }
    }
    *(Input->u16LastInput)=*Output;
    return enRet;
}

/*============================================================================
*Function : AIRD_tenValueSts AIRD_enU8InputValueCalc(AIRD_tstInputAttributes *Input, uint8 *Output)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
AIRD_tenValueSts AIRD_enU8InputValueCalc(AIRD_tstU8InputAttributes *Input, uint8 *Output)
{
    AIRD_tenValueSts enRet;
    if(Input->u8InputValue==0xFF)
    {
        if(Input->u8ErrCounter<Input->u8ErrWaitTime)
        {
            enRet=AIRD_nInvalid;
        }
        else
        {
           enRet=AIRD_nDefault;
           *Output=Input->u8Default;
        }
    }
    else
    {
        if((Input->u8InputValue<Input->u8MinVal)||(Input->u8InputValue>Input->u8MaxVal))
        {
          *Output=*(Input->u8LastInput);
          enRet=AIRD_nLastValue;
        }
        else
        {
          *Output=Input->u8InputValue;
          enRet=AIRD_nValid;
        }
    }
    *(Input->u8LastInput)=*Output;
    return enRet;
}

/*****************************************************************************
* EOF: AIRD_interface.c
*****************************************************************************/
