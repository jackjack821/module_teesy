/*******************************************************************************
| Module Name: Dimmer Control
| File Name: Dim_interface.c
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
| Yang Shengli                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-05-18  1.00        Yang Shengli      First implementation
| 2016-06-18  2.00        Yang Shengli      module upgraded
********************************************************************************/
#include "Mmi.h" 
//#include "Mmi_Type.h"
//#include "Mmi_Private.h" 
#include "Pow.h"
#include "Rte_internal.h"

#include "DIM.h"
#include "DIM_private.h"
#include "DIM_interface.h"
#include "DIM_type.h"
#include "DIM_cfg.h"
const uint16 DIM_au8Indicator1Pin[] = 
{
	(PortNotUse),   /*AUTO Indicator*/
	(MCU_mPinID_P8_4),          /*AC Indicator*/
	(MCU_mPinID_P10_12),        /*DUAL Indicator*/
	PortNotUse,         /*FRE Indicator*/
	(MCU_mPinID_P8_7),         /*REC Indicator*/
	(PortNotUse),        /*RDEF Indicator*/
	(MCU_mPinID_P11_1),       /*MAXAC Indicator*/
	//(MCU_mPinID_P8_0),        /*FDEF Indicator*/
	PortNotUse,        /*FDEF Indicator*/
	PortNotUse,       /*MIXED Indicator*/
	PortNotUse,       /*FLOOR Indicator*/
	PortNotUse,        /*FACE Indicator*/
	PortNotUse,     /*BILEVEL Indicator*/
	PortNotUse,    /*REARLOCK Indicator*/
	(MCU_mPinID_P8_8),/*ION Indicator*/
	PortNotUse,
	PortNotUse,
};
const uint16 DIM_au8Indicator2Pin[] =
{
    (MCU_mPinID_P11_8),   /*Left Heated seat level1 indicator*/
	PortNotUse,        /*Left Heated seat level2 indicator*/
	PortNotUse,        /*Left Heated seat level3 indicator*/
	//(MCU_mPinID_P10_8),        /*Right Heated seat level1 indicator*/
	PortNotUse,
	PortNotUse,        /*Right Heated seat level2 indicator*/
	PortNotUse,        /*Right Heated seat level3 indicator*/
	PortNotUse,        /*Left Cooled seat level1 indicator*/
	PortNotUse,        /*Left Cooled seat level2 indicator*/
	PortNotUse,        /*Left Cooled seat level3 indicator*/
	PortNotUse,        /*Right Cooled seat level1 indicator*/
	PortNotUse,        /*Right Cooled seat level2 indicator*/
	PortNotUse,        /*Right Cooled seat level3 indicator*/
	PortNotUse,
	PortNotUse,
	PortNotUse,
	PortNotUse,
};
#define DIM_CcpControlEnable (True)
#if DIM_CcpControlEnable
/*Ccp control*/
/**********************************Ccp control*****************************************/
typedef enum
{
    DIM_nLcdPwmDuty=0u,	    /*Lcd PWM duty*/
	DIM_nTelltalesTt,	/*TT Led PWM*/
	DIM_nTelltalesCtrl,
	DIM_nCcpForceMax
}CcpControl_DIM;
//static uint8 DIM_u8CcpForceControlLedFlag=0;
static uint16 DIM_u16CcpForceFlag=0u;
static uint16 DIM_u16CcpForceFlagInfo1=0u;
static uint16 DIM_u16CcpForceFlagInfo2=0u;
static uint16 DIM_u16CcpControlData[DIM_nCcpForceMax];
#define DIMGetCcpForceBit(index)	((uint16)(DIM_u16CcpForceFlag>>(index))&0x01u)
#define DIMSetCcpForceBit(index)	(DIM_u16CcpForceFlag=DIM_u16CcpForceFlag|(0x01u<<(index)))
#define DIMClrCcpForceBit(index)	(DIM_u16CcpForceFlag=DIM_u16CcpForceFlag&(~(0x01u<<(index))))

#define DIMGetCcpForceBit1(index)	((uint16)(DIM_u16CcpForceFlagInfo1>>(index))&0x01u)
#define DIMSetCcpForceBit1(index)	(DIM_u16CcpForceFlagInfo1=DIM_u16CcpForceFlagInfo1|(0x01u<<(index)))
#define DIMClrCcpForceBit1(index)	(DIM_u16CcpForceFlagInfo1=DIM_u16CcpForceFlagInfo1&(~(0x01u<<(index))))

#define DIMGetCcpForceBit2(index)	((uint16)(DIM_u16CcpForceFlagInfo2>>(index))&0x01u)
#define DIMSetCcpForceBit2(index)	(DIM_u16CcpForceFlagInfo2=DIM_u16CcpForceFlagInfo2|(0x01u<<(index)))
#define DIMClrCcpForceBit2(index)	(DIM_u16CcpForceFlagInfo2=DIM_u16CcpForceFlagInfo2&(~(0x01u<<(index))))

#define DIMClrCcpForceByte1(void)	(DIM_u16CcpForceFlagInfo1=0u)
#define DIMClrCcpForceByte2(void)	(DIM_u16CcpForceFlagInfo2=0u)
#define DIMClrCcpForceByte(void)	(DIM_u16CcpForceFlag=0u)
/*************************************************************************************/

/*****************************************************************************
 Function      : DIM_u8ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/

Std_ReturnType DIM_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord)
{
    Std_ReturnType returnValue = RTE_E_OK;
    
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				DIMClrCcpForceByte();
				break;
            case 0x01:
            case 0x82:
            case 0xA1:/*LCD PWM*/
                DIMSetCcpForceBit(DIM_nLcdPwmDuty);
                DIM_u16CcpControlData[DIM_nLcdPwmDuty]=(uint8)CcpControlWord.CcpContronData & 0xFF;
                break;
            case 0x02:
            case 0xA2:/*Cancel LCD PWM*/
                DIMClrCcpForceBit(DIM_nLcdPwmDuty);
                break;
            case 0x03:
            case 0x81:
            case 0xA3:/*LED PWM*/
				DIMSetCcpForceBit(DIM_nTelltalesTt);
				DIM_u16CcpControlData[DIM_nTelltalesTt]=(uint8)CcpControlWord.CcpContronData & 0xFF;
                break;
            case 0x04:
            case 0xA4:/*Cancel all led PWM*/
                DIMClrCcpForceBit(DIM_nTelltalesTt);
                break;
            case 0x05:
			case 0x83:
            case 0xA5:/*Character PWM*/
				break;
            case 0x06:
            case 0xA6:/*Cancel all character*/
                break;
			case 0x84:/*LED Status*/
				if((CcpControlWord.CcpContronData&0x0001U) == 0x0001U )
				{
					DIMSetCcpForceBit1(DIM_nBitMmiAuto);/*Auto TT on*/
				}
				else
				{
					DIMClrCcpForceBit1(DIM_nBitMmiAuto);/*Auto TT off*/
				}
				if((CcpControlWord.CcpContronData&0x0002U) == 0x0002U )
				{
					DIMSetCcpForceBit1(DIM_nBitMmiAc);/*Ac TT on*/
				}
				else
				{
					DIMClrCcpForceBit1(DIM_nBitMmiAc);/*Ac TT off*/
				}
				if((CcpControlWord.CcpContronData&0x0004U) == 0x0004U )
				{
					DIMSetCcpForceBit1(DIM_nBitMmiDual);/*Daul TT on*/
				}
				else
				{
					DIMClrCcpForceBit1(DIM_nBitMmiDual);/*Daul TT off*/
				}
				if((CcpControlWord.CcpContronData&0x0010U) == 0x0010U)
				{
					DIMSetCcpForceBit1(DIM_nBitMmiRec);/*Rec TT on*/
				}
				else
				{
					DIMClrCcpForceBit1(DIM_nBitMmiRec);/*Rec TT off*/	
				}
				if((CcpControlWord.CcpContronData&0x0020U) == 0x0020U)
				{
					DIMSetCcpForceBit1(DIM_nBitMmiRdef);/*Rdef TT on*/
				}
				else
				{
					DIMClrCcpForceBit1(DIM_nBitMmiRdef);/*Rdef TT off*/	
				}
				if((CcpControlWord.CcpContronData&0x0040U) == 0x0040U)
				{
					DIMSetCcpForceBit1(DIM_nBitMmiMaxAc);/*MaxAc TT on*/
				}
				else
				{
					DIMClrCcpForceBit1(DIM_nBitMmiMaxAc);/*MaxAc TT off*/	
				}
				if((CcpControlWord.CcpContronData&0x0080U) == 0x0080U)
				{
					DIMSetCcpForceBit1(DIM_nBitMmiFdef);/*Fdef TT on*/
				}
				else
				{
					DIMClrCcpForceBit1(DIM_nBitMmiFdef);/*Fdef TT off*/	
				}
				if((CcpControlWord.CcpContronData&0x2000U) == 0x2000U)
				{
					DIMSetCcpForceBit1(DIM_nBitiIon);/*Ion TT on*/
				}
				else
				{
					DIMClrCcpForceBit1(DIM_nBitiIon);/*Ion TT off*/	
				}
                DIMSetCcpForceBit(DIM_nTelltalesCtrl);
				break;
            case 0x85:
                if((CcpControlWord.CcpContronData&0x0001U) == 0x0001U )
				{
					DIMSetCcpForceBit2(DIM_nBitMmiHSL1);/*SHL1 TT on*/
				}
				else
				{
					DIMClrCcpForceBit2(DIM_nBitMmiHSL1);/*SHL1 TT off*/
				}
                
				if((CcpControlWord.CcpContronData&0x0008U) == 0x0008U)
				{
					DIMSetCcpForceBit2(DIM_nBitMmiHSR1);/*SHR1 TT on*/
				}
				else
				{
					DIMClrCcpForceBit2(DIM_nBitMmiHSR1);/*SHR1 TT off*/	
				}
                DIMSetCcpForceBit(DIM_nTelltalesCtrl);
                break;
            case 0xA7:
                if((CcpControlWord.CcpContronData&0x0001U) == 0x0001U)
                {
                    DIMSetCcpForceBit1(DIM_nBitMmiRdef);/*Rdef TT on*/
                }
                else
                {
                    DIMClrCcpForceBit1(DIM_nBitMmiRdef);/*Rdef TT off*/	
                }
                DIMSetCcpForceBit(DIM_nTelltalesCtrl);
                DIMSetCcpForceBit(DIM_nTelltalesTt);
                DIM_u16CcpControlData[DIM_nTelltalesTt]=100;
                break;
            case 0xA8:
                DIMClrCcpForceBit(DIM_nTelltalesCtrl);
                DIMClrCcpForceBit(DIM_nTelltalesTt);
                break;
			default:
                returnValue = RTE_E_INVALID;
				break;
		}
	}
	else
	{
		DIMClrCcpForceByte();
	}

    return returnValue;
}
#endif
/*============================================================================
*Function : DIM_tenValueSts DIM_enPowerStatusImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DIM_tenValueSts DIM_enPowerStatusImport(uint8 *value)
{
    DIM_tenValueSts enRet;
    DIM_tstU8InputAttributes DIM_stU8InputAttributes;
    static uint8 u8PowerLastOutput = 0;
    
    DIM_stU8InputAttributes.u8InputValue = DIM_u16GetPowBattLowFlag() | \
        DIM_u16GetPowBattHighFlag();
    DIM_enGetU8InitCounterExport(&DIM_stU8InputAttributes.u8ErrCounter);
    DIM_stU8InputAttributes.u8LastInput = &u8PowerLastOutput;
    DIM_stU8InputAttributes.u8Default = 0u;
    DIM_stU8InputAttributes.u8MinVal = 0u;
    DIM_stU8InputAttributes.u8MaxVal = 1u;
    DIM_stU8InputAttributes.u8ErrWaitTime = 5u;/*500ms*/

    enRet = DIM_enU8InputValueCalc(&DIM_stU8InputAttributes,value);
    return enRet;
}
/*============================================================================
*Function : DIM_tenValueSts DIM_enMmiLedInfo1Import(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DIM_tenValueSts DIM_enMmiLedInfo1Import(uint16 *value)
{
    *value = DIM_u16GetMmiLedInfo1();
    return DIM_nValid;
}
/*============================================================================
*Function : DIM_tenValueSts DIM_enMmiLedInfo2Import(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DIM_tenValueSts DIM_enMmiLedInfo2Import(uint16 *value)
{
    *value = DIM_u16GetMmiLedInfo2();
    return DIM_nValid;
}
/*============================================================================
*Function : DIM_tenValueSts DIM_enLuminanceModeImport(uint8 *value)
*Description 0:DayMode
             1:NightMode
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DIM_tenValueSts DIM_enLuminanceModeImport(uint8 *value)
{
    DIM_tenValueSts enRet;
    uint16 u16LuminaceMode;
    DIM_tstU8InputAttributes DIM_stU8InputAttributes;
    static uint8 u8PowerLastOutput = 0;

    DIM_vILLInputPwmDetect(&u16LuminaceMode);
    if((u16LuminaceMode>50/*5%*/)&&(u16LuminaceMode<950/*95%*/))
    {
        DIM_stU8InputAttributes.u8InputValue = 1;/*Nigh mode*/
    }
    else
    {
        DIM_stU8InputAttributes.u8InputValue = 0;
    }
    DIM_enGetU8InitCounterExport(&DIM_stU8InputAttributes.u8ErrCounter);
    DIM_stU8InputAttributes.u8LastInput = &u8PowerLastOutput;
    DIM_stU8InputAttributes.u8Default = 0u;
    DIM_stU8InputAttributes.u8MinVal = 0u;
    DIM_stU8InputAttributes.u8MaxVal = 1u;
    DIM_stU8InputAttributes.u8ErrWaitTime = 5u;/*500ms*/

    enRet = DIM_enU8InputValueCalc(&DIM_stU8InputAttributes,value);
    return enRet;
}
/*============================================================================
*Function : DIM_tenValueSts DIM_enBacklightLuminanceImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DIM_tenValueSts DIM_enBacklightLuminanceImport(uint16 *value)
{
    uint16 u16Luminance;
    uint8 u8Temp=0;
    DIM_tenValueSts enRet;

    DIM_tstU8InputAttributes DIM_stU8InputAttributes;
    static uint8 u8PowerLastOutput = 0;
    
    DIM_stU8InputAttributes.u8InputValue = DIM_u8GetBacklightLuminace();
    DIM_enGetU8InitCounterExport(&DIM_stU8InputAttributes.u8ErrCounter);
    DIM_stU8InputAttributes.u8LastInput = &u8PowerLastOutput;
    DIM_stU8InputAttributes.u8Default = 0u;
    DIM_stU8InputAttributes.u8MinVal = 0u;
    DIM_stU8InputAttributes.u8MaxVal = 255u;
    DIM_stU8InputAttributes.u8ErrWaitTime = 5u;/*500ms*/
    
    enRet = DIM_enU8InputValueCalc(&DIM_stU8InputAttributes,&u8Temp);
    
    u16Luminance = ((uint16)u8Temp)*100/255*10;
    if(u16Luminance > 1000U)
    {
        u16Luminance = 1000U;
    }
    *value = u16Luminance;
    return enRet;
}
/*============================================================================
*Function : DIM_tenValueSts DIM_enBacklightStatusImport(uint8 *value)
*Description 0:Luminance Off
             1:Luminance On
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DIM_tenValueSts DIM_enBacklightStatusImport(uint8 *value)
{
    DIM_tenValueSts enRet;
    DIM_tstU8InputAttributes DIM_stU8InputAttributes;
    static uint8 u8PowerLastOutput = 0;
    
    DIM_stU8InputAttributes.u8InputValue = DIM_u8GetBacklightStatus();
    DIM_enGetU8InitCounterExport(&DIM_stU8InputAttributes.u8ErrCounter);
    DIM_stU8InputAttributes.u8LastInput = &u8PowerLastOutput;
    DIM_stU8InputAttributes.u8Default = 0u;
    DIM_stU8InputAttributes.u8MinVal = 0u;
    DIM_stU8InputAttributes.u8MaxVal = 1u;
    DIM_stU8InputAttributes.u8ErrWaitTime = 5u;/*500ms*/

    enRet = DIM_enU8InputValueCalc(&DIM_stU8InputAttributes,value);
    return enRet;
}
/*============================================================================
*Function : DIM_tenValueSts DIM_enBacklightLuminanceValidImport(uint8 *value)
*Description 0:Luminance value valid
             1:Luminance value invalid 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DIM_tenValueSts DIM_enBacklightLuminanceValidImport(uint8 *value)
{
    DIM_tenValueSts enRet;
    DIM_tstU8InputAttributes DIM_stU8InputAttributes;
    static uint8 u8PowerLastOutput = 0;
    
    DIM_stU8InputAttributes.u8InputValue = DIM_u8GetBacklightLuminaceValid();
    DIM_enGetU8InitCounterExport(&DIM_stU8InputAttributes.u8ErrCounter);
    DIM_stU8InputAttributes.u8LastInput = &u8PowerLastOutput;
    DIM_stU8InputAttributes.u8Default = 0u;
    DIM_stU8InputAttributes.u8MinVal = 0u;
    DIM_stU8InputAttributes.u8MaxVal = 1u;
    DIM_stU8InputAttributes.u8ErrWaitTime = 5u;/*500ms*/

    enRet = DIM_enU8InputValueCalc(&DIM_stU8InputAttributes,value);
    return enRet;
}
/*============================================================================
*Function : DIM_tenValueSts DIM_enIndicatorInfo1DutyExport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DIM_tenValueSts DIM_enIndicatorInfoPinExport(uint8 *index,uint8 *value,uint8 *group)
{
    uint8 u8Port = 0xFF,u8Pin = 0xFF,u8Value,u8ReturnValue;

    if(*group == 1)
    {
        u8Port = (uint8)(DIM_au8Indicator1Pin[*index] >> 8 & 0xFF);
        u8Pin = (uint8)(DIM_au8Indicator1Pin[*index] & 0xFF);
    }
    else if(*group == 2)
    {
        u8Port = (uint8)(DIM_au8Indicator2Pin[*index] >> 8 & 0xFF);
        u8Pin = (uint8)(DIM_au8Indicator2Pin[*index] & 0xFF);
    }
    else
    {
    }
    
    if((u8Port != 0xFF) && (u8Pin != 0xFF))
    {
        u8Value = *value;
        DIM_vPinWrite(u8Port,u8Pin,u8Value);
        u8ReturnValue = DIM_nValid;
    }
    else
    {
        u8ReturnValue = DIM_nInvalid;
    }
    
    return (DIM_tenValueSts)u8ReturnValue;
}

/*============================================================================
*Function : DIM_tenValueSts DIM_enSymbolBacklightPwmDutyExport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DIM_tenValueSts DIM_enSymbolBacklightPwmDutyExport(DIM_tstState *value)
{
    uint8 u8ReturnValue = DIM_nValid;

    switch(value->enIndex)
    {
        case DIM_nSymbolBacklight:
            //DIM_vPpgSetDuty(DIM_nChannelID_SymbolBacklight,value->enPwmDuty);
            break;
        default:
            u8ReturnValue = DIM_nInvalid;
            break;
    }
    return (DIM_tenValueSts)u8ReturnValue;
}

/*============================================================================
*Function : DIM_tenValueSts DIM_enLcdBacklightPwmDutyExport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DIM_tenValueSts DIM_enLcdBacklightPwmDutyExport(DIM_tstState *value)
{
    uint8 u8ReturnValue = DIM_nValid;
    uint16 u16PwmDuty = 0u; 

    if(DIMGetCcpForceBit(DIM_nLcdPwmDuty))
    {
        u16PwmDuty = DIM_u16CcpControlData[DIM_nLcdPwmDuty] * 10;
    }
    else
    {
        u16PwmDuty = value->enPwmDuty;
    }
    if(u16PwmDuty > 1000u)
    {
        u16PwmDuty = 1000u;
    }
    switch(value->enIndex)
    {
        case DIM_nLcdBacklight:
            DIM_LcdBacklightPwmDutySet(u16PwmDuty);
            break;
        default:
            u8ReturnValue = DIM_nInvalid;
            break;
    }
    return (DIM_tenValueSts)u8ReturnValue;
}
/*============================================================================
*Function : DIM_tenValueSts DIM_enIndicatorPwmDutyExport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DIM_tenValueSts DIM_enIndicatorPwmDutyExport(DIM_tstState *value)
{
    uint8 u8ReturnValue = DIM_nValid;
    uint16 u16InputPwmDuty = 0u;

    if(DIMGetCcpForceBit(DIM_nTelltalesTt))
    {
        u16InputPwmDuty = DIM_u16CcpControlData[DIM_nTelltalesTt] * 10u;
    }
    else
    {
        u16InputPwmDuty = value->enPwmDuty;
    }

    if(u16InputPwmDuty > 1000u)
    {
        u16InputPwmDuty = 1000u;
    }
    
    switch(value->enIndex)
    {
        case DIM_nIndiShcL:
            if(DIMGetCcpForceBit(DIM_nTelltalesCtrl))
            {
                if(DIMGetCcpForceBit2(DIM_nBitMmiHSL1))
                {
                    DIM_ShcLIndiPwmDutySet(u16InputPwmDuty);
                }
                else
                {
                    DIM_ShcLIndiPwmDutySet(0u);
                }
            }
            else
            {
                DIM_ShcLIndiPwmDutySet(u16InputPwmDuty);
            }
            break;
        case DIM_nIndiShcR:
            if(DIMGetCcpForceBit(DIM_nTelltalesCtrl))
            {
                if(DIMGetCcpForceBit2(DIM_nBitMmiHSR1))
                {
                    DIM_ShcRIndiPwmDutySet(u16InputPwmDuty);
                }
                else
                {
                    DIM_ShcRIndiPwmDutySet(0u);
                }
            }
            else
            {
                DIM_ShcRIndiPwmDutySet(u16InputPwmDuty);
            }
            break;
        case DIM_nIndiAc:
            if(DIMGetCcpForceBit(DIM_nTelltalesCtrl))
            {
                if(DIMGetCcpForceBit1(DIM_nBitMmiAc))
                {
                    DIM_AcIndiPwmDutySet(u16InputPwmDuty);
                }
                else
                {
                    DIM_AcIndiPwmDutySet(0u);
                }
            }
            else
            {
                DIM_AcIndiPwmDutySet(u16InputPwmDuty);
            }
            break;
        case DIM_nIndiFDef:
            if(DIMGetCcpForceBit(DIM_nTelltalesCtrl))
            {
                if(DIMGetCcpForceBit1(DIM_nBitMmiFdef))
                {
                    DIM_FDefIndiPwmDutySet(u16InputPwmDuty);
                }
                else
                {
                    DIM_FDefIndiPwmDutySet(0u);
                }
            }
            else
            {
                DIM_FDefIndiPwmDutySet(u16InputPwmDuty);
            }
            break;
        case DIM_nIndiAuto:
            if(DIMGetCcpForceBit(DIM_nTelltalesCtrl))
            {
                if(DIMGetCcpForceBit1(DIM_nBitMmiAuto))
                {
                    DIM_AutoIndiPwmDutySet(u16InputPwmDuty);
                }
                else
                {
                    DIM_AutoIndiPwmDutySet(0u);
                }
            }
            else
            {
                DIM_AutoIndiPwmDutySet(u16InputPwmDuty);
            }
            break;
        case DIM_nIndiRec:
            if(DIMGetCcpForceBit(DIM_nTelltalesCtrl))
            {
                if(DIMGetCcpForceBit1(DIM_nBitMmiRec))
                {
                    DIM_RecIndiPwmDutySet(u16InputPwmDuty);
                }
                else
                {
                    DIM_RecIndiPwmDutySet(0u);
                }
            }
            else
            {
                DIM_RecIndiPwmDutySet(u16InputPwmDuty);
            }
            break;
        case DIM_nIndiRDef:
            if(DIMGetCcpForceBit(DIM_nTelltalesCtrl))
            {
                if(DIMGetCcpForceBit1(DIM_nBitMmiRdef))
                {
                    DIM_RDefIndiPwmDutySet(u16InputPwmDuty);
                }
                else
                {
                    DIM_RDefIndiPwmDutySet(0u);
                }
            }
            else
            {
                DIM_RDefIndiPwmDutySet(u16InputPwmDuty);
            }
            break;
        case DIM_nIndiMaxAc:
            if(DIMGetCcpForceBit(DIM_nTelltalesCtrl))
            {
                if(DIMGetCcpForceBit1(DIM_nBitMmiMaxAc))
                {
                    DIM_MaxAcIndiPwmDutySet(u16InputPwmDuty);
                }
                else
                {
                    DIM_MaxAcIndiPwmDutySet(0u);
                }
            }
            else
            {
                DIM_MaxAcIndiPwmDutySet(u16InputPwmDuty);
            }
            break;
        case DIM_nIndiIon:
            if(DIMGetCcpForceBit(DIM_nTelltalesCtrl))
            {
                if(DIMGetCcpForceBit1(DIM_nBitiIon))
                {
                    DIM_IonIndiPwmDutySet(u16InputPwmDuty);
                }
                else
                {
                    DIM_IonIndiPwmDutySet(0u);
                }
            }
            else
            {
                DIM_IonIndiPwmDutySet(u16InputPwmDuty);
            }
            break;
        case DIM_nIndiDual:
            if(DIMGetCcpForceBit(DIM_nTelltalesCtrl))
            {
                if(DIMGetCcpForceBit1(DIM_nBitMmiDual))
                {
                    DIM_DualIndiPwmDutySet(u16InputPwmDuty);
                }
                else
                {
                    DIM_DualIndiPwmDutySet(0u);
                }
            }
            else
            {
                DIM_DualIndiPwmDutySet(u16InputPwmDuty);
            }
            break;
        default:
            u8ReturnValue = DIM_nInvalid;
            break;
    }
    return (DIM_tenValueSts)u8ReturnValue;
}

/*============================================================================
*Function : void DIM_vOutputUpdate(void)
*Description : 
*takes : nothing
*return: Nothing
*/
void DIM_vOutputUpdate(void)
{
    uint16 u16DimLumMode = DIM_nDayMode;
    
    u16DimLumMode = DIM_u16GetValue(DIM_nu16LumMode);
    if(DIMGetCcpForceBit(DIM_nTelltalesTt))
    {
        //Rte_IWrite_Dim_vMain_DimLED2PWMValue_u16PwmDuty(DIM_u16CcpControlData[DIM_nTelltalesTt]);
    }
    else
    {
        if(u16DimLumMode == DIM_nDayMode)
        {
            //Rte_IWrite_Dim_vMain_DimLED2PWMValue_u16PwmDuty(DIM_nDayModeDuty_TT/10);
        }
        else
        {
            //Rte_IWrite_Dim_vMain_DimLED2PWMValue_u16PwmDuty(DIM_nNightModeDuty_TT/10);
        }
    }

    if(DIMGetCcpForceBit(DIM_nLcdPwmDuty))
    {
        //Rte_IWrite_Dim_vMain_DimLCDPWMValue_u16PwmDuty(DIM_u16CcpControlData[DIM_nLcdPwmDuty]);
        //Rte_IWrite_Dim_vMain_DimLED1PWMValue_u16PwmDuty(DIM_u16CcpControlData[DIM_nLcdPwmDuty]);
    }
    else
    {
        if(u16DimLumMode == DIM_nDayMode)
        {
            //Rte_IWrite_Dim_vMain_DimLCDPWMValue_u16PwmDuty(DIM_nDayModeDuty_TT/10);
            //Rte_IWrite_Dim_vMain_DimLED1PWMValue_u16PwmDuty(DIM_nDayModeDuty_TT/10);
        }
        else
        {
            //Rte_IWrite_Dim_vMain_DimLCDPWMValue_u16PwmDuty(DIM_nNightModeDuty_TT/10);
            //Rte_IWrite_Dim_vMain_DimLED1PWMValue_u16PwmDuty(DIM_nNightModeDuty_TT/10);
        }
    }
}


