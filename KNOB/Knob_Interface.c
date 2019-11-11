/*******************************************************************************
| Module Name: KNOB capture and debouncing interface
| File Name: KNOB_interface.c
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
| 2016.8.3         0100      Li jiaye         module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/


/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define KNOB_Interface                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
//#include "Rte_KNOB.h"
#include "ALG.h"

/* Own headerfiles */
#include "KNOB_Cfg.h"
#include "KNOB_Type.h"
#include "KNOB_Private.h"
#include "KNOB.h"      
#include "KNOB_interface.h"

/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/
/*****************************************************************************/
static uint8 KNOB_CcpForceFlag = 0U;
#define KNOB_GetCcpForceBit(index)	((KNOB_CcpForceFlag>>index)&0x01)
#define KNOB_SetCcpForceBit(index)	(KNOB_CcpForceFlag=KNOB_CcpForceFlag|(0x01<<index))
#define KNOB_ClrCcpForceBit(index)	(KNOB_CcpForceFlag=KNOB_CcpForceFlag&(~(0x01<<index)))
#define KNOB_ClrCcpForceByte(void)	(KNOB_CcpForceFlag=0)

static KNOB_tstPtsOutput stPtsOutput[KnobNum];
static void KNOB_u8ClearKnobValueForPts(void);
/*************************************************************************************************** 
  Function   : KNOB_vCcpControl_Write      
   
  Description: Ccp control function for other module.
                            
  Arguments  : None
  
  Returns    : Nothing.
***************************************************************************************************/
Std_ReturnType KNOB_vCcpControl_Write(uint32 ForceIoControlWord)
{
    KNOB_tstCcpControlInput stCcpCtr;
    stCcpCtr.u8Flag = (uint8)(ForceIoControlWord>>24);
    stCcpCtr.u8Command = (uint8)(ForceIoControlWord>>16);
    stCcpCtr.u16ControlValue = (uint16)ForceIoControlWord;

    if(stCcpCtr.u8Flag == True)
    {
        switch(stCcpCtr.u8Command)
        {
            case 0x81U:
                KNOB_SetCcpForceBit(KNOB_nRecordCounter);
                KNOB_u8ClearKnobValueForPts();
                break;
            case 0x82U:
                KNOB_ClrCcpForceBit(KNOB_nRecordCounter);
                KNOB_u8ClearKnobValueForPts();
                break;
            default: return RTE_E_INVALID;
        }
    }
    else
    {
        KNOB_ClrCcpForceByte();
        KNOB_u8ClearKnobValueForPts();
    }
    return RTE_E_OK;
}



/*============================================================================
*Function : void KNOB_vClrForceFlagByteAction(void)
*Description : 
*takes : nothing
*return: nothing
*/
void KNOB_vClrForceFlagByteAction(void)
{
    KNOB_ClrCcpForceByte();
}
/*============================================================================
*Function : void KNOB_vMainExportAction(void)
*Description : Export local calculated value
*takes : nothing
*return: nothing
*/
void KNOB_vMainExportAction(void)
{
    uint8 i;
    KNOB_tstMainOut stMainOut[KnobNum];
    for(i=0;i<KnobNum;i++)
    {
        KNOB_enGetMainOutputExport(i,&stMainOut[i]);
        if(KNOB_GetCcpForceBit(KNOB_nRecordCounter)==True)
        {           
            stPtsOutput[i].u16MinusCounter+=stMainOut[i].u8MinusCounter;
            stPtsOutput[i].u16PlusCounter+=stMainOut[i].u8PlusCounter;
            if(stPtsOutput[i].u16MinusCounter>30u)
            {
                stPtsOutput[i].u16MinusCounter=30u;
            }
            if(stPtsOutput[i].u16PlusCounter>30u)
            {
                stPtsOutput[i].u16PlusCounter=30u;
            }
        }
        else
        {
            stPtsOutput[i].u16MinusCounter=0u;
            stPtsOutput[i].u16PlusCounter=0u;
        }
    }
    
    /*RTE interface*/
}

/*============================================================================
*Function : KNOB_enTempPINAImport
*Description : Import PIN status
*takes : nothing
*return: nothing
*/
KNOB_tenValueSts KNOB_enTempPINAImport(uint8 *value)
{
    KNOB_tenValueSts enRet=KNOB_nInvalid;

    return  enRet;
}
/*============================================================================
*Function : KNOB_enTempPINBImport
*Description : Import PIN status
*takes : nothing
*return: nothing
*/
KNOB_tenValueSts KNOB_enTempPINBImport(uint8 *value)
{
    KNOB_tenValueSts enRet=KNOB_nInvalid;

    return  enRet;
}
/*============================================================================
*Function : KNOB_enBlowerPINAImport
*Description : Import PIN status
*takes : nothing
*return: nothing
*/
KNOB_tenValueSts KNOB_enBlowerPINAImport(uint8 *value)
{
    KNOB_tenValueSts enRet=KNOB_nInvalid;

    return  enRet;
}
/*============================================================================
*Function : KNOB_enBlowerPINBImport
*Description : Import PIN status
*takes : nothing
*return: nothing
*/
KNOB_tenValueSts KNOB_enBlowerPINBImport(uint8 *value)
{
    KNOB_tenValueSts enRet=KNOB_nInvalid;

    return  enRet;
}


uint8 KNOB_u8GetvalueForPts(Knob_tenu8Output index)
{
    uint8 u8Return=0;
    
    switch(index)
    {
        case Knob_enTempLPlusCounter:
            u8Return=(uint8)stPtsOutput[0].u16PlusCounter;
        break;
        case Knob_enTempRPlusCounter:
            u8Return=(uint8)stPtsOutput[1].u16PlusCounter;
        break;
        case Knob_enTempLMinusCounter:
            u8Return=(uint8)stPtsOutput[0].u16MinusCounter;
        break;
        case Knob_enTempRMinusCounter:
            u8Return=(uint8)stPtsOutput[1].u16MinusCounter;
        break;
        default:
            break;
    }
    return u8Return;
}

static void KNOB_u8ClearKnobValueForPts(void)
{
    uint8 i;
    
    for(i=0;i<KnobNum;i++)
    {
        stPtsOutput[i].u16MinusCounter=0u;
        stPtsOutput[i].u16PlusCounter=0u;
    }
}
/*****************************************************************************
* EOF: KEY_interface.c
*****************************************************************************/
