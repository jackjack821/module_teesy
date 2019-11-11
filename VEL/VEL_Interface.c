/*******************************************************************************
| Module Name: Calculate the Blowout and Temp offset according to the VELocity
| File Name: VEL_interface.c
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
| Sui Yanchun                        Desay SV Automotive Co., Ltd
| Zhang Shuncong                     Desay SV Automotive Co., Ltd
| Li Jiaye                           Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2013-04-09  1.00        Sui Yanchun       First implementation
| 2015-08-06  2.00        Zhang Shuncong    Add RTE ,Copyright and cfg
| 2016-09-21  0100        Li Jiaye          interface updated
********************************************************************************/


/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define VEL_Interface                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
#include "ALG.h"
#include "CANAPP.h"
#include "OAT.h"

/* Own headerfiles */
#include "VEL_Cfg.h"
#include "VEL_Type.h"
#include "VEL_Private.h"
#include "VEL.h"      
#include "VEL_interface.h"

/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/

static uint8 VEL_CcpForceFlag=0;
static uint16 VEL_CcpControlData[VEL_nCcpForceMax];
/**************************Internal Module Interface*******************************/

#define VEL_GetCcpForceBit(index)	((VEL_CcpForceFlag>>index)&0x01)
#define VEL_SetCcpForceBit(index)	(VEL_CcpForceFlag=VEL_CcpForceFlag|(0x01<<index))
#define VEL_ClrCcpForceBit(index)	(VEL_CcpForceFlag=VEL_CcpForceFlag&(~(0x01<<index)))
#define VEL_ClrCcpForceByte(void)	(VEL_CcpForceFlag=0)


/*****************************************************************************
 Function      : Vel_ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType VEL_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
{
    tstVelCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
    
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				VEL_ClrCcpForceByte();
				break;
			case 1:
				VEL_SetCcpForceBit(VEL_nSetVelValue);
				VEL_CcpControlData[VEL_nSetVelValue]=CcpControlWord.CcpContronData;
				break;
			case 2:
				VEL_ClrCcpForceBit(VEL_nSetVelValue);
				VEL_CcpControlData[VEL_nSetVelValue]=0;
				break;
			default:
				return 1;//VEL_ClrCcpForceByte();
				
		}
	}
	else
	{
		VEL_ClrCcpForceByte();
	}
	return 0;
}
/*============================================================================
*Function : void VEL_vClrForceFlagByteAction(void)
*Description : 
*takes : nothing
*return: nothing
*/
void VEL_vClrForceFlagByteAction(void)
{
    VEL_ClrCcpForceByte();
}

/*============================================================================
*Function : VEL_tenValueSts VEL_enVeIocityValueImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
VEL_tenValueSts VEL_enVeIocityValueImport(uint16 *value)
{
    VEL_tenValueSts enRet=VEL_nValid;
    uint32 u32VelCalc;
    
	if(VEL_GetCcpForceBit(VEL_nSetVelValue))/*CCP Force*/
	{
		*value=VEL_CcpControlData[VEL_nSetVelValue];
		if(*value>VEL_nMaxValue)
		{
			*value=VEL_nMaxValue;
		}
	}
	else
	{
		if(CANAPP_u16GetValue(CANAPP_nu16ESC_VehicleSpeed)<0xFFFE)
		{
			u32VelCalc = CANAPP_u16GetValue(CANAPP_nu16ESC_VehicleSpeed);
			*value=(uint16) ((u32VelCalc*144/10)>>8);/*0.05625km per bit(KC-2)*/;
		}
		else
		{
			*value=0;
		}
	}
    return enRet;
}

/*============================================================================
*Function : VEL_tenValueSts VEL_enVeIocityInvalidImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
VEL_tenValueSts VEL_enVeIocityInvalidImport(uint8 *value)
{
    uint16 u16Invalid;
    
    VEL_tenValueSts enRet=VEL_nValid;

    u16Invalid = CANAPP_u16GetValue(CANAPP_nu16ESC_VehicleSpeedInvalid);
    if(u16Invalid == False)
    {
        enRet = VEL_nValid;
        *value=VEL_nValid;
    }
    else
    {
        enRet = VEL_nInvalid;
        *value=VEL_nInvalid;
    }
    return enRet;
}

/*============================================================================
*Function : VEL_tenValueSts VEL_enOatValidImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
VEL_tenValueSts VEL_enOatValidImport(uint8 *value)
{
    VEL_tenValueSts enRet=VEL_nValid;
    *value=OAT_u16GetValue(OAT_nu16Valid);
    return enRet;
}

/*============================================================================
*Function : VEL_tenValueSts VEL_enOatValueImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
VEL_tenValueSts VEL_enOatValueImport(uint16 *value)
{
    VEL_tenValueSts enRet=VEL_nValid;
    *value=OAT_u16GetValue(OAT_nu16Value);
    return enRet;
}
/*============================================================================
*Function : void VEL_vMainExportAction(void)
*Description : Export local calculated value
*takes : nothing
*return: nothing
*/
void VEL_vMainExportAction(void)
{
    Vel_tstMainOut stMainOut;
    VEL_enGetMainOutputExport(&stMainOut);
    
    /*Rte_IWrite_Vel_vReset_VelSwVersion_u8Version(VEL_u8SwVersion);
    Rte_IWrite_Vel_vMain_VelValid_u8Flag(stMainOut.u8ModuleValid);
    Rte_IWrite_Vel_vMain_VelVelocity_u16Speed(stMainOut.u16Velocity);        
    Rte_IWrite_Vel_vMain_VelRfaValue_u16Speed(stMainOut.u16RfaVelValue);
    Rte_IWrite_Vel_vMain_VelForOatValue_u16Speed(stMainOut.u16OatVelValue); 
    Rte_IWrite_Vel_vMain_VelBlowerOffset_u16BlwSpdOffset(stMainOut.u16BlowerOffset); 
    Rte_IWrite_Vel_vMain_VelTempOffset_u16TempOffset(stMainOut.u16TempOffset);
    Rte_IWrite_Vel_vMain_VelErrorCode_u16BitMap(stMainOut.u16ErrorCode);*/
}



/*****************************************************************************
* EOF: KEY_interface.c
*****************************************************************************/
