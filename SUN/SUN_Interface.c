/*******************************************************************************
| Module Name: Interface for calculation the Blowout and Temp offset according to the solar
| File Name: SUN_Interface.c
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
| ----------  -------  -------------  ------------------------------------------
| 2013-04-09  1.00        Sui Yanchun       First implementation
| 2015-08-05  2.00        Zhang Shuncong    Add RTE ,Copyright and cfg
| 2016-09-22  0100        Li Jiaye          updated module interface
********************************************************************************/


/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define SUN_Interface                     /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
#include "ALG.h"
#include "RTE_internal.h"
#include "oat.h"

/* Own headerfiles */
#include "SUN_Cfg.h"
#include "SUN_Type.h"
#include "SUN_Private.h"
#include "SUN.h"      
#include "SUN_interface.h"

/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/
static uint8 SUN_CcpForceFlag=0;
static uint16 SUN_CcpControlData[SUN_nCcpForceMax];
#define SUN_GetCcpForceBit(index)	((SUN_CcpForceFlag>>index)&0x01)
#define SUN_SetCcpForceBit(index)	(SUN_CcpForceFlag=SUN_CcpForceFlag|(0x01<<index))
#define SUN_ClrCcpForceBit(index)	(SUN_CcpForceFlag=SUN_CcpForceFlag&(~(0x01<<index)))
#define SUN_ClrCcpForceByte(void)	(SUN_CcpForceFlag=0)

/*****************************************************************************
 Function      : Sun_ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType SUN_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
{
    tstSunCcpContronType CcpControlWord;        
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
    
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				SUN_ClrCcpForceByte();
				break;
			case 1:
				SUN_SetCcpForceBit(SUN_nSetSunLoad);
				SUN_CcpControlData[SUN_nSetSunLoad]=CcpControlWord.CcpContronData;
				break;
			case 2:
				SUN_ClrCcpForceBit(SUN_nSetSunLoad);
				SUN_CcpControlData[SUN_nSetSunLoad]=0;
				break;
			case 3:
				SUN_SetCcpForceBit(SUN_nSetSunSensorFbAd);
				SUN_CcpControlData[SUN_nSetSunSensorFbAd]=CcpControlWord.CcpContronData;
				break;
			case 4:
				SUN_ClrCcpForceBit(SUN_nSetSunSensorFbAd);
				SUN_CcpControlData[SUN_nSetSunSensorFbAd]=0;
				break;
			default:
                return 1;//SUN_ClrCcpForceByte();

		}
	}
	else
	{
		SUN_ClrCcpForceByte();
	}
        return 0;
}

/*============================================================================
*Function : void SUN_vClrForceFlagByteAction(void)
*Description : 
*takes : nothing
*return: nothing
*/
void SUN_vClrForceFlagByteAction(void)
{
    SUN_ClrCcpForceByte();
}

/*============================================================================
*Function : SUN_tenValueSts SUN_enSolarRawValueDrvImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
SUN_tenValueSts SUN_enSolarRawValueDrvImport(uint16 *value)
{
    SUN_tenValueSts enRet=SUN_nValid;
    if(SUN_GetCcpForceBit(SUN_nSetSunLoad))
	{
		*value = SUN_CcpControlData[SUN_nSetSunLoad];
        
	}
    else
    {
        Rte_Call_IoHwAd_IoHwAd_ReadAd_DriverSolarSensor_Read(value);
        if(*value>=0xFFFE)
        {
            *value=SUN_nDefaultValue;
            enRet=SUN_nDefault;
        }
    }    
    return enRet;
}

/*============================================================================
*Function : SUN_tenValueSts SUN_enSolarRawValuePsImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
SUN_tenValueSts SUN_enSolarRawValuePsImport(uint16 *value)
{
    SUN_tenValueSts enRet=SUN_nValid;
    if(SUN_GetCcpForceBit(SUN_nSetSunLoad))
	{
		*value = SUN_CcpControlData[SUN_nSetSunLoad];
        
	}
    else
    {
        Rte_Call_IoHwAd_IoHwAd_ReadAd_PassengerSolarSensor_Read(value);
        if(*value>=0xFFFE)
        {
            *value=SUN_nDefaultValue;
            enRet=SUN_nDefault;
        }
    }    
    return enRet;
}


/*============================================================================
*Function : SUN_tenValueSts SUN_enOATValidImport(uint8 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
SUN_tenValueSts SUN_enOATValidImport(uint8 *value)
{
    SUN_tenValueSts enRet=SUN_nValid;
    *value =True;  
    return enRet;
}
/*============================================================================
*Function : SUN_tenValueSts SUN_enOATValueImport(uint16 *value)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
SUN_tenValueSts SUN_enOATValueImport(uint16 *value)
{
    SUN_tenValueSts enRet=SUN_nValid;
    *value =OAT_u16GetValue(OAT_nu16Value); 
    if(*value>=0xFFFE)
    {
        *value=550;
    }
    return enRet;
}
/*============================================================================
*Function : void SUN_vMainExportAction(void)
*Description : Export local calculated value
*takes : nothing
*return: nothing
*/
void SUN_vMainExportAction(void)
{
    Sun_tstMainOut stMainOut;
    SUN_enGetMainOutputExport(&stMainOut);
}



/*****************************************************************************
* EOF: SUN_interface.c
*****************************************************************************/
