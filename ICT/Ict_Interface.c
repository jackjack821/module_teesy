/*******************************************************************************
| Module Name: Calculate in car temperature value(Interface)
| File Name: Ict_interface.c
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
| Ouyang Bihuan                      Desay SV Automotive Co., Ltd
| Li Jiaye                           Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2015-7-2    Rev 1.1   Ouyang Bihuan       Create the module base on ICT of GAC A28.
| 2016-09-27  0100        Li Jiaye          interface updated
********************************************************************************/


/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define ICT_Interface                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
#include "ALG.h"
#include "NAT.h"
#include "OAT.h"
#include "CCS.h"
#include "AIRD.h"
#include "MMI.h"
#include "CCS.h"
/* Own headerfiles */
#include "ICT_Cfg.h"
#include "ICT_Type.h"
#include "ICT_Private.h"
#include "ICT.h"      
#include "ICT_interface.h"

/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/

static uint8 Ict_CcpForceFlag=0;
static uint16 Ict_CcpControlData[Ict_nCcpForceMax];
#define IctGetCcpForceBit(index)	((Ict_CcpForceFlag>>index)&0x01)
#define IctSetCcpForceBit(index)	(Ict_CcpForceFlag=Ict_CcpForceFlag|(0x01<<index))
#define IctClrCcpForceBit(index)	(Ict_CcpForceFlag=Ict_CcpForceFlag&(~(0x01<<index)))
#define IctClrCcpForceByte(void)	(Ict_CcpForceFlag=0)

/*****************************************************************************
 Function      : Ict_vCcpControl                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType ICT_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord)
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
				IctClrCcpForceByte();
				break;
			case 1:
				IctSetCcpForceBit(Ict_nReplaceIctValue);
				Ict_CcpControlData[Ict_nReplaceIctValue]=CcpControlWord.CcpContronData;
				break;
			case 2:
				IctClrCcpForceBit(Ict_nReplaceIctValue);
				Ict_CcpControlData[Ict_nReplaceIctValue]=0;
				break;
			default:
                return RTE_E_INVALID;

		
		}
	}
	else
	{
		IctClrCcpForceByte();
	}
    return RTE_E_OK;
}
/*============================================================================
*Function : void ICT_vClrForceFlagByteAction(void)
*Description : 
*takes : nothing
*return: nothing
*/
void ICT_vClrForceFlagByteAction(void)
{
    IctClrCcpForceByte();
}
/*============================================================================
*Function : ICT_tenValueSts ICT_enMmiSetTempImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ICT_tenValueSts ICT_enMmiSetTempImport(uint8 *value)
{
    ICT_tenValueSts enRet=ICT_nValid;
    *value =MMI_u8GetValue(MMI_nu8SetTempDr);    
    return enRet;
}
/*============================================================================
*Function : ICT_tenValueSts ICT_enSonserRawValueImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ICT_tenValueSts ICT_enSonserRawValueImport(uint16 *value)
{
    ICT_tenValueSts enRet=ICT_nValid;
#ifdef _USE_NATS_
    *value = NAT_u16GetValue(NAT_nu16Value);
#else
    Rte_Call_Ict_ReadAd_SensorValue_Read(value);    
#endif
    return enRet;
}

/*============================================================================
*Function : ICT_tenValueSts ICT_enOatValidImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ICT_tenValueSts ICT_enOatValidImport(uint8 *value)
{
    ICT_tenValueSts enRet=ICT_nValid;
    *value= (uint8)OAT_u16GetValue(OAT_nu16Valid);
    return enRet;
}
/*============================================================================
*Function : ICT_tenValueSts ICT_enOatValueImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ICT_tenValueSts ICT_enOatValueImport(uint16 *value)
{
    ICT_tenValueSts enRet=ICT_nValid;
    *value=OAT_u16GetValue(OAT_nu16Value);   
    return enRet;
}

/*============================================================================
*Function : ICT_tenValueSts ICT_enAirdValidImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ICT_tenValueSts ICT_enAirdValidImport(uint8 *value)
{
    ICT_tenValueSts enRet=ICT_nValid;
    *value=1u;    
    return enRet;
}
/*============================================================================
*Function : ICT_tenValueSts ICT_enAirdPosValueImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ICT_tenValueSts ICT_enAirdPosValueImport(uint16 *value)
{
    ICT_tenValueSts enRet=ICT_nValid;
    *value=AIRD_u16GetValue(AIRD_nu16SetPos);    
    return enRet;
}
/*============================================================================
*Function : ICT_tenValueSts ICT_enCcsSetTempImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ICT_tenValueSts ICT_enCcsSetTempImport(uint16 *value)
{
    ICT_tenValueSts enRet=ICT_nValid;
    *value=CCS_u16GetValue(CCS_nu16SetTempAvg);   
    return enRet;
}
/*============================================================================
*Function : ICT_tenValueSts ICT_enCcsValidImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ICT_tenValueSts ICT_enCcsValidImport(uint8 *value)
{
    ICT_tenValueSts enRet=ICT_nValid;
    *value=CCS_u8GetValue(CCS_nu8Valid);    
    return enRet;
}
/*============================================================================
*Function : ICT_tenValueSts ICT_enPowValidImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ICT_tenValueSts ICT_enPowValidImport(uint8 *value)
{
    ICT_tenValueSts enRet=ICT_nValid;
    *value=True;    
    return enRet;
}

/*============================================================================
*Function : void ICT_vMainExportAction(void)
*Description : Export local calculated value
*takes : nothing
*return: nothing
*/
void ICT_vMainExportAction(void)
{
    ICT_tstMainOut stMainOut;
    ICT_enGetMainOutputExport(&stMainOut);
	if(IctGetCcpForceBit(Ict_nReplaceIctValue))
	{
		stMainOut.u16IctValue=Ict_CcpControlData[Ict_nReplaceIctValue];
		stMainOut.u16UndampedValue=Ict_CcpControlData[Ict_nReplaceIctValue];
	}
	else
	{
	}
#if 0
    Rte_IWrite_Ict_vMain_IctSensorAdValue_u16AdValue(stMainOut.u16SensorAdValue);
    Rte_IWrite_Ict_vMain_IctSensorRawValue_u16Temp(stMainOut.u16SensorValue);
    Rte_IWrite_Ict_vMain_IctDynMax_u16TempOffset(stMainOut.u16DynMax);
    Rte_IWrite_Ict_vMain_IctDynOffset_u16TempOffset(stMainOut.u16DynOffset);
    //Rte_IWrite_Ict_vMain_IctLinearLimitValue_u16Temp(ICT_u16LinearLimitValue);
    Rte_IWrite_Ict_vMain_IctMaxDiff_u16TempDiff(stMainOut.u16MaxDiff);
    Rte_IWrite_Ict_vMain_IctStaticOffset_u16TempOffset(stMainOut.u16StaticOffset);
    Rte_IWrite_Ict_vMain_IctUndampedValue_u16Temp(stMainOut.u16UndampedValue);
    Rte_IWrite_Ict_vMain_IctValue_u16Temp(stMainOut.u16IctValue);

    Rte_IWrite_Ict_vMain_IctValid_u8Flag(stMainOut.u8ModuleValid);
    Rte_IWrite_Ict_vMain_IctErrorCode_u16BitMap((uint8)stMainOut.u16ErrorCode);
#endif
}


/*****************************************************************************
 Function      : ICT_u8GetValue                                              *
 Description   : The extern model get the uint8 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*****************************************************************************/
uint8 ICT_u8GetValue( ICT_tenu8VarNum Num )
{
    uint8 u8ReturnValue=0u;
    ICT_tstMainOut stMainOut;
    ICT_enGetMainOutputExport(&stMainOut);    
    switch(Num)
    {
        case ICT_nu8Valid:
            u8ReturnValue=stMainOut.u8ModuleValid;
        break;
        default:
        break;
    }
    return u8ReturnValue;
}

/*****************************************************************************
 Function      : ICT_u16GetValue                                              *
 Description   : The extern model get the uint8 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*****************************************************************************/
uint16 ICT_u16GetValue( ICT_tenu16VarNum Num )
{
    uint16 u16ReturnValue=0u;
    ICT_tstMainOut stMainOut;
    ICT_enGetMainOutputExport(&stMainOut); 
	if(IctGetCcpForceBit(Ict_nReplaceIctValue))
	{
		stMainOut.u16IctValue=Ict_CcpControlData[Ict_nReplaceIctValue];
		stMainOut.u16UndampedValue=Ict_CcpControlData[Ict_nReplaceIctValue];
	}
	else
	{
	}
    switch(Num )
    {
        case ICT_nu16Value:
            u16ReturnValue=stMainOut.u16IctValue;
        break;
        case ICT_nu16SensorAdValue:
            u16ReturnValue=stMainOut.u16SensorAdValue;
        break;
        case ICT_nu16SensorValue:
            u16ReturnValue=stMainOut.u16SensorValue;
        break;
        case ICT_nu16UndampedValue:
            u16ReturnValue=stMainOut.u16UndampedValue;
        break;
        case ICT_nu16DynOffset:
            u16ReturnValue=stMainOut.u16DynOffset;
        break;
        case ICT_nu16DynMax:
            u16ReturnValue=stMainOut.u16DynMax;
        break;
        case ICT_nu16MaxDiff:
            u16ReturnValue=stMainOut.u16MaxDiff;
        break;
        case ICT_nu16StaticOffset:
            u16ReturnValue=stMainOut.u16StaticOffset;
        break;
        case ICT_nu16SwVersion:
            u16ReturnValue=ICT_SwVersion;
        break;
        case ICT_nu16ErrorState:
            u16ReturnValue=stMainOut.u16ErrorCode;
        break;
        default:
        break;
    }
    return u16ReturnValue;

}




/*****************************************************************************
* EOF: ICT_interface.c
*****************************************************************************/
