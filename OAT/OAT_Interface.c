/*******************************************************************************
| Module Name: Calculate the ambient temperature
| File Name: OAT_Interface.c
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2016 Huizhou Desay SV Automotive Co., Ltd.    All rights reserved.
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
| Zou Riming                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2016-06-21   0100      Zou Riming          First Create 
| 2016-09-22   0200      Zou Riming          Delet condition 2 of cold start 
| 
********************************************************************************/


/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define OAT_Interface                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */



/* Foreign headerfiles */
#include "VEL.h"
/* Own headerfiles */
#include "OAT_Private.h"

/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/

static uint16 OAT_u16InputErrorCode=0u;
#if (OAT_UseNewCCP==True)
static uint16 OAT_CcpForceFlag=0;
static uint16 OAT_CcpControlData[OAT_nCcpForceMax];
#define OAT_GetCcpForceBit(index)	((OAT_CcpForceFlag>>(index))&0x01)
#define OAT_SetCcpForceBit(index)	(OAT_CcpForceFlag=OAT_CcpForceFlag|(0x01<<(index)))
#define OAT_ClrCcpForceBit(index)	(OAT_CcpForceFlag=OAT_CcpForceFlag&(~(0x01<<(index))))
#endif

static void OAT_vInputErrorCodeHandle(uint16 *ErrorCode, uint8 ErrorMaskNum,OAT_tenValueSts InputSts);
//static OAT_tenValueSts OAT_enU8InputValueCalc(OAT_tstU8InputAttributes *Input, uint8 *Output);
static OAT_tenValueSts OAT_enU16InputValueCalc(OAT_tstU16InputAttributes *Input, uint16 *Output);


#if (OAT_UseNewCCP==True)
/*****************************************************************************
 Function      : OAT_ClrCcpForceByte                              
 Description   : Ccp control function
 Takes         : None
 Return Value  : None                                                *
*****************************************************************************/
void OAT_ClrCcpForceByte(void)
{
    OAT_CcpForceFlag=0;
}


/*****************************************************************************
 Function      : OAT_vCcpContro                              
 Description   : Ccp control function
 Takes         : uint32
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType OAT_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
{
	uint8 u8Result=0;
	OAT_tstCcpControl CcpControlWord;
	CcpControlWord.CcpControlData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
             switch(CcpControlWord.CcpCommand)
		{
			case 0:
				OAT_ClrCcpForceByte();
				break;
			case 1:
				OAT_SetCcpForceBit(OAT_nSetOatSensorFbAd);
				OAT_CcpControlData[OAT_nSetOatSensorFbAd]=CcpControlWord.CcpControlData;
				break;
			case 2:
				OAT_ClrCcpForceBit(OAT_nSetOatSensorFbAd);
				OAT_CcpControlData[OAT_nSetOatSensorFbAd]=False;
				break;
                	case 3:
				OAT_SetCcpForceBit(OAT_nSetOatValue);
				OAT_CcpControlData[OAT_nSetOatValue]=CcpControlWord.CcpControlData;
				break;
			case 4:
				OAT_ClrCcpForceBit(OAT_nSetOatValue);
				OAT_CcpControlData[OAT_nSetOatValue]=False;
				break;
			default:
				u8Result = 0;
				break;
		}
	}
	else
	{
		OAT_ClrCcpForceByte();
	}
	return u8Result;
}



/*****************************************************************************
 Function      : OAT_vCcpOutputForce                                 
 Description   : force output value
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
void OAT_vCcpOutputForce(uint16*Value)
{
    if(OAT_GetCcpForceBit(OAT_nSetOatValue))
    {
       *Value= OAT_CcpControlData[OAT_nSetOatValue];
    }
}

#endif


/*============================================================================
*Function : OAT_u16IgnDelayFlagImport(uint16*Value)
*Description : 
*takes : nothing
*return: uint16;    0:no error, others:error
*/
OAT_tenValueSts OAT_u16IgnDelayFlagImport(uint16*Value)
{
    OAT_tenValueSts enRet;
    OAT_tstU16InputAttributes OAT_stU16InputAttributes;
    static uint16 u16LastOutput=0u;

    OAT_stU16InputAttributes.u16InputValue=OAT_u16GetIgnDelayFlag();
    OAT_enGetU8InitCounterExport(&OAT_stU16InputAttributes.u8ErrCounter);
    OAT_stU16InputAttributes.u16LastInput=&u16LastOutput;
    OAT_stU16InputAttributes.u16Default=1u;
    OAT_stU16InputAttributes.u16MinVal=0u;
    OAT_stU16InputAttributes.u16MaxVal=1u;
    OAT_stU16InputAttributes.u8ErrWaitTime=OAT_nMaxErrorDelay;/*500ms*/
    
    enRet=OAT_enU16InputValueCalc(&OAT_stU16InputAttributes,Value);
    OAT_vInputErrorCodeHandle(&OAT_u16InputErrorCode,OAT_nBitIgnModuleError,enRet);

    return enRet;

}


/*============================================================================
*Function : OAT_u16Sys1000msFlagImport(uint16*Value)
*Description : 
*takes : nothing
*return: uint16;    0:no error, others:error
*/
OAT_tenValueSts OAT_u16Sys1000msFlagImport(uint16*Value)
{
    OAT_tenValueSts enRet;
    OAT_tstU16InputAttributes OAT_stU16InputAttributes;
    static uint16 u16LastOutput=0u;

    OAT_stU16InputAttributes.u16InputValue=OAT_u16GetSysValue_SYS_nFlag1000MS_BG();
    OAT_enGetU8InitCounterExport(&OAT_stU16InputAttributes.u8ErrCounter);
    OAT_stU16InputAttributes.u16LastInput=&u16LastOutput;
    OAT_stU16InputAttributes.u16Default=0u;
    OAT_stU16InputAttributes.u16MinVal=0u;
    OAT_stU16InputAttributes.u16MaxVal=1u;
    OAT_stU16InputAttributes.u8ErrWaitTime=OAT_nMaxErrorDelay;/*500ms*/
    
    enRet=OAT_enU16InputValueCalc(&OAT_stU16InputAttributes,Value);
    OAT_vInputErrorCodeHandle(&OAT_u16InputErrorCode,OAT_nBitSysModuleError,enRet);

    return enRet;

}


/*============================================================================
*Function : OAT_u16ComPowVoltageValidImport(uint16*Value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
#if(OAT_FromSensor==False)
OAT_tenValueSts OAT_u16ComPowVoltageFailureImport(uint16*Value)
{
    OAT_tenValueSts enRet;
    OAT_tstU16InputAttributes OAT_stU16InputAttributes;
    static uint16 u16LastOutput=1u;

    OAT_stU16InputAttributes.u16InputValue=\
        (OAT_u16GetPowValue_POW_nu16ComLowVoltage()|\
        OAT_u16GetPowValue_POW_nu16ComHighVoltage());
    OAT_enGetU8InitCounterExport(&OAT_stU16InputAttributes.u8ErrCounter);
    OAT_stU16InputAttributes.u16LastInput=&u16LastOutput;
    OAT_stU16InputAttributes.u16Default=1u;
    OAT_stU16InputAttributes.u16MinVal=0u;
    OAT_stU16InputAttributes.u16MaxVal=1u;\
    OAT_stU16InputAttributes.u8ErrWaitTime=OAT_nMaxErrorDelay;/*500ms*/
    
    enRet=OAT_enU16InputValueCalc(&OAT_stU16InputAttributes,Value);
    OAT_vInputErrorCodeHandle(&OAT_u16InputErrorCode,OAT_nBitPowModuleError,enRet);

    return enRet;

}
#endif

/*============================================================================
*Function : OAT_u16BusQualityFlagImport(uint16*Value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
#if(OAT_FromSensor==False)
OAT_tenValueSts OAT_u16BusQualityFlagImport(uint16*Value)
{
    OAT_tenValueSts enRet;
    OAT_tstU16InputAttributes OAT_stU16InputAttributes;
    static uint16 u16LastOutput=0u;

    OAT_stU16InputAttributes.u16InputValue=OAT_u16GetCanValue_CANAPP_nu16OatQuaFlag();
    OAT_enGetU8InitCounterExport(&OAT_stU16InputAttributes.u8ErrCounter);
    OAT_stU16InputAttributes.u16LastInput=&u16LastOutput;
    OAT_stU16InputAttributes.u16Default=3u;
    OAT_stU16InputAttributes.u16MinVal=0u;
    OAT_stU16InputAttributes.u16MaxVal=3u;
    OAT_stU16InputAttributes.u8ErrWaitTime=OAT_nMaxErrorDelay;/*500ms*/
    
    enRet=OAT_enU16InputValueCalc(&OAT_stU16InputAttributes,Value);
    OAT_vInputErrorCodeHandle(&OAT_u16InputErrorCode,OAT_nBitBusModuleError,enRet);

    return enRet;

}
#endif

/*============================================================================
*Function : OAT_u16BusRawValueImport(uint16*Value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
#if(OAT_FromSensor==False)
OAT_tenValueSts OAT_u16BusRawValueImport(uint16*Value)
{
    OAT_tenValueSts enRet;
    OAT_tstU16InputAttributes OAT_stU16InputAttributes;
    static uint16 u16LastOutput=OAT_nDefaultBusValue;

    OAT_stU16InputAttributes.u16InputValue=OAT_u16GetCanValue_CANAPP_nu16OatValue();
    OAT_enGetU8InitCounterExport(&OAT_stU16InputAttributes.u8ErrCounter);
    OAT_stU16InputAttributes.u16LastInput=&u16LastOutput;
    OAT_stU16InputAttributes.u16Default=OAT_nDefaultBusValue;
    OAT_stU16InputAttributes.u16MinVal=0u;
    OAT_stU16InputAttributes.u16MaxVal=0x3FF;
    OAT_stU16InputAttributes.u8ErrWaitTime=OAT_nMaxErrorDelay;/*500ms*/

    enRet=OAT_enU16InputValueCalc(&OAT_stU16InputAttributes,Value);
    OAT_vInputErrorCodeHandle(&OAT_u16InputErrorCode,OAT_nBitBusModuleError,enRet);

    return enRet;

}
#endif


/*============================================================================
*Function : OAT_u16PowAdValidFlagImport(uint16*Value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
#if(OAT_FromSensor==True)
OAT_tenValueSts OAT_u16PowAdValidFlagImport(uint16*Value)
{
    OAT_tenValueSts enRet;
    OAT_tstU16InputAttributes OAT_stU16InputAttributes;
    static uint16 u16LastOutput=0u;
    
    OAT_stU16InputAttributes.u16InputValue=OAT_u16GetPowValue_POW_nu16AdValid();
    OAT_enGetU8InitCounterExport(&OAT_stU16InputAttributes.u8ErrCounter);
    OAT_stU16InputAttributes.u16LastInput=&u16LastOutput;
    OAT_stU16InputAttributes.u16Default=0u;
    OAT_stU16InputAttributes.u16MinVal=0u;
    OAT_stU16InputAttributes.u16MaxVal=1u;
    OAT_stU16InputAttributes.u8ErrWaitTime=OAT_nMaxErrorDelay;/*500ms*/
    
    enRet=OAT_enU16InputValueCalc(&OAT_stU16InputAttributes,Value);
    OAT_vInputErrorCodeHandle(&OAT_u16InputErrorCode,OAT_nBitPowModuleError,enRet);

    return enRet;

}
#endif


/*============================================================================
*Function : OAT_u16SensorAdRawValueImport(uint16*Value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
#if(OAT_FromSensor==True)
OAT_tenValueSts OAT_u16SensorAdRawValueImport(uint16*Value)
{
    OAT_tenValueSts enRet;
    OAT_tstU16InputAttributes OAT_stU16InputAttributes;
    static uint16 u16LastOutput=1023u;

    OAT_u16GetHalValue_HAL_nu16OatAdValue(&OAT_stU16InputAttributes.u16InputValue);
    OAT_enGetU8InitCounterExport(&OAT_stU16InputAttributes.u8ErrCounter);
    OAT_stU16InputAttributes.u16LastInput=&u16LastOutput;
    OAT_stU16InputAttributes.u16Default=1023u;
    OAT_stU16InputAttributes.u16MinVal=0u;
    OAT_stU16InputAttributes.u16MaxVal=1023u;
    OAT_stU16InputAttributes.u8ErrWaitTime=OAT_nMaxErrorDelay;/*500ms*/
    
    enRet=OAT_enU16InputValueCalc(&OAT_stU16InputAttributes,Value);
    if(enRet==OAT_nInvalid)
    {
        OAT_vInputErrorCodeHandle(&OAT_u16InputErrorCode,OAT_nBitHalModuleError,enRet);
    }
    else
    {
        if(*Value>OAT_nValueShortToPow)   /*open or short to battery*/
        {
            enRet=OAT_nShortToPow;
            OAT_vInputErrorCodeHandle(&OAT_u16InputErrorCode,OAT_nBitSensorShortToPow,enRet);
        }
        else if(*Value<OAT_nValueShortToGnd)   /*short to ground*/
        {
            enRet=OAT_nShortToGnd;
            OAT_vInputErrorCodeHandle(&OAT_u16InputErrorCode,OAT_nBitSensorShortToGnd,enRet);
        }
        else
        {
            OAT_vInputErrorCodeHandle(&OAT_u16InputErrorCode,OAT_nBitSensorShortToPow,OAT_nValid);
            OAT_vInputErrorCodeHandle(&OAT_u16InputErrorCode,OAT_nBitSensorShortToGnd,OAT_nValid);
            OAT_vInputErrorCodeHandle(&OAT_u16InputErrorCode,OAT_nBitHalModuleError,enRet);
        }
    }
    
    return enRet;

}
#endif


/*============================================================================
*Function : OAT_u16VechileSpeedValueImport(uint16*Value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
OAT_tenValueSts OAT_u16VechileSpeedValueImport(uint16*Value)
{
    OAT_tenValueSts enRet;
    OAT_tstU16InputAttributes OAT_stU16InputAttributes;
    static uint16 u16LastOutput=0u;

    OAT_stU16InputAttributes.u16InputValue=OAT_u16GetVelValue_VEL_nu16ValueForOat();
    OAT_enGetU8InitCounterExport(&OAT_stU16InputAttributes.u8ErrCounter);
    OAT_stU16InputAttributes.u16LastInput=&u16LastOutput;
    OAT_stU16InputAttributes.u16Default=0u;
    OAT_stU16InputAttributes.u16MinVal=0u;
    OAT_stU16InputAttributes.u16MaxVal=655u;
    OAT_stU16InputAttributes.u8ErrWaitTime=OAT_nMaxErrorDelay;/*500ms*/
    
    enRet=OAT_enU16InputValueCalc(&OAT_stU16InputAttributes,Value);
    OAT_vInputErrorCodeHandle(&OAT_u16InputErrorCode,OAT_nBitVelModuleError,enRet);

    return enRet;

}


/*============================================================================
*Function : OAT_u16HctValueImport(uint16*Value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
OAT_tenValueSts OAT_u16HctValueImport(uint16*Value)
{
    OAT_tenValueSts enRet;
    OAT_tstU16InputAttributes OAT_stU16InputAttributes;
    static uint16 u16LastOutput=OAT_nTemp(50);/*50degree*/

    OAT_stU16InputAttributes.u16InputValue=OAT_u16GetHctValue_HCT_nu16ValueForOat();
    OAT_enGetU8InitCounterExport(&OAT_stU16InputAttributes.u8ErrCounter);
    OAT_stU16InputAttributes.u16LastInput=&u16LastOutput;
    OAT_stU16InputAttributes.u16Default=OAT_nTemp(50);/*50degree*/
    OAT_stU16InputAttributes.u16MinVal=0u;
    OAT_stU16InputAttributes.u16MaxVal=OAT_nTemp(120);/*120degree*/
    OAT_stU16InputAttributes.u8ErrWaitTime=OAT_nMaxErrorDelay;/*500ms*/
    
    enRet=OAT_enU16InputValueCalc(&OAT_stU16InputAttributes,Value);
    OAT_vInputErrorCodeHandle(&OAT_u16InputErrorCode,OAT_nBitHctModuleError,enRet);

    return enRet;

}


/* =========================================================================
* Function   : void OAT_enGetErrorCode (void)
* Description: error code output interface
* Takes      : uint16 *ErrorCode
* Returns    : Nothing
*/
OAT_tenValueSts OAT_enGetErrorCode(uint16 *ErrorCode)
{
    *ErrorCode=OAT_u16InputErrorCode;
    return OAT_nValid;
}


#if 0
/*============================================================================
*Function : OAT_tenValueSts OAT_enU8InputValueCalc(OAT_tstInputAttributes *Input, uint8 *Output)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
static OAT_tenValueSts OAT_enU8InputValueCalc(OAT_tstU8InputAttributes *Input, uint8 *Output)
{
    OAT_tenValueSts enRet;
    if(Input->u8InputValue==0xFF)
    {
        if(Input->u8ErrCounter<Input->u8ErrWaitTime)
        {
            enRet=OAT_nInvalid;
        }
        else
        {
           enRet=OAT_nDefault;
           *Output=Input->u8Default;
        }
    }
    else
    {
        if((Input->u8InputValue<Input->u8MinVal)||(Input->u8InputValue>Input->u8MaxVal))
        {
          *Output=*(Input->u8LastInput);
          enRet=OAT_nLastValue;
        }
        else
        {
          *Output=Input->u8InputValue;
          enRet=OAT_nValid;
        }
    }
    *(Input->u8LastInput)=*Output;
    return enRet;
}
#endif

/*============================================================================
*Function : OAT_tenValueSts OAT_enU16InputValueCalc(OAT_tstInputAttributes *Input, uint16 *Output)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
static OAT_tenValueSts OAT_enU16InputValueCalc(OAT_tstU16InputAttributes *Input, uint16 *Output)
{
    OAT_tenValueSts enRet;
    if(Input->u16InputValue==0xFFFF)
    {
        if(Input->u8ErrCounter<Input->u8ErrWaitTime)
        {
            enRet=OAT_nInvalid;
        }
        else
        {
           enRet=OAT_nDefault;
           *Output=Input->u16Default;
        }
    }
    else
    {
        if((Input->u16InputValue<Input->u16MinVal)||(Input->u16InputValue>Input->u16MaxVal))
        {
          *Output=*(Input->u16LastInput);
          enRet=OAT_nLastValue;
        }
        else
        {
          *Output=Input->u16InputValue;
          enRet=OAT_nValid;
        }
    }
    *(Input->u16LastInput)=*Output;
    return enRet;
}


/*******************************************************************************
*Function : void OAT_vInputErrorCodeHandle(uint16 *ErrorCode, uint8 ErrorMaskNum,OAT_tenValueSts InputSts)
*Description : Set or Clr the ErrorCode
*takes :  Motor index
*return: Nothing
*/
void OAT_vInputErrorCodeHandle(uint16 *ErrorCode, uint8 ErrorMaskNum,OAT_tenValueSts InputSts)
{
    if(InputSts==OAT_nValid)
    {
       (*ErrorCode)&=(~((uint16)1u<<ErrorMaskNum)); 
    }
    else
    {
        (*ErrorCode)|=((uint16)1u<<ErrorMaskNum);
    }
}



/*****************************************************************************
* EOF: OAT_Interface.c
*****************************************************************************/
