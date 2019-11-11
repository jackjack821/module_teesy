/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE: TLE9262  Driver used on 32bit MCU RH850L by SPI 
*-----------------------------------------------------------------------------
  .FILE:TLE9262.c   
*-----------------------------------------------------------------------------

 Date        Author                       Change
 -----------------------------------------------------------------------------
2018.04.13  ZhengJianshi		   :create this module

*****************************************************************************/
#ifndef SBC_If
#define SBC_If

/* System-headerfiles */

/* Own headerfiles */
#include "SBC_if.h"
#include "SBC_Private.h"


/* Foreign headerfiles */
#include "Mcu_cfg.h"
//#include "IGN1.h"
#if (FRAME_RteUsed==1)
//#include "Rte.h"
//#include "Rte_Sys.h"
#endif
#include "Rte.h"
//#include "Rte_Sys.h"
#include "desc.h"
#include "appdesc.h"
typedef enum
{
    SBC_nIONREQDigital = 0U,
    SBC_nCcpForceMax
}CcpControl_SBC;
static uint16 SBC_CcpForceFlag;
static uint16 SBC_CcpControlData[SBC_nCcpForceMax];

#define SBCGetCcpForceBit(index)	((uint8)(SBC_CcpForceFlag>>(index))&0x01u)
#define SBCSetCcpForceBit(index)	(SBC_CcpForceFlag=((uint16)SBC_CcpForceFlag|(uint16)(((uint16)0x01u<<(index)))))
#define SBCClrCcpForceBit(index)	(SBC_CcpForceFlag=((uint16)SBC_CcpForceFlag&(uint16)(~(uint16)((uint16)0x01u<<(index)))))
#define SBCClrCcpForceByte(void)	(SBC_CcpForceFlag=0u)

/*****************************************************************************
 Function      : SBC_ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType SBC_u8ForceIoControl_Write (/*IN*/uint32 ForceIoControlWord)
{
    uint8 u8ReturnValue=RTE_E_OK;
	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				SBCClrCcpForceByte(void);
				break;
                    case 117:
				SBCSetCcpForceBit(SBC_nIONREQDigital);
				SBC_CcpControlData[SBC_nIONREQDigital]=CcpControlWord.CcpContronData;
				break;
                    case 118:
				SBCClrCcpForceBit(SBC_nIONREQDigital);
				SBC_CcpControlData[SBC_nIONREQDigital]=0;
				break;
			default:
		        u8ReturnValue=RTE_E_INVALID;
                break;
		}
	}
	else
	{
		SBCClrCcpForceByte(void);
	}
        return u8ReturnValue;
}

/******************************************************************************/
/*
*Function Name :

* Description   :
* Date          :	2018.04.13	
*/
/******************************************************************************/
 uint8 TLE9262Drv_vGetHS1_ConfigStatus(void)
{
	uint8 u8retvalue;
	u8retvalue=0;
	
	if(u8retvalue==1)
	{
		return SBCdrv_tenHS_ConfigurationModeType_ON;
	}
	else
	{
		return SBCdrv_tenHS_ConfigurationModeType_OFF;
	}
}




/******************************************************************************/
/*
*Function Name :

* Description   :
* Date          :	2018.04.13	
*/
/******************************************************************************/
 uint8 TLE9262Drv_vGetHS2_ConfigStatus(void)
{
	//uint8 u8retvalue;
	uint8 u8ReadValue,U8AppHighVolt,U8AppLowVolt;
	//u8retvalue=0;

	//Rte_Call_Sys_Sys_Sys_ReadPIMU8Value_Read(PIM_U8_SeatHeatLvL,&u8ReadValue);
       // Rte_Call_MICS_MICS_ReadIsmU8Value_Read(ISM_U8_AppHighVolt,&U8AppHighVolt);
        //Rte_Call_MICS_MICS_ReadIsmU8Value_Read(ISM_U8_AppLowVolt,&U8AppLowVolt);
        if((DIAG_u8GetValue(DIAG_nu8IONMount)==0)||(U8AppHighVolt==1)||(U8AppLowVolt==1))
        {
            u8ReadValue =0;
        }
        /*BLWRelay_3Digital*/
        if(SBCGetCcpForceBit(SBC_nIONREQDigital)==True)
        {
             u8ReadValue = ((uint8)SBC_CcpControlData[SBC_nIONREQDigital]);
        }
	if(u8ReadValue&0x01)
	{
		//return SBCdrv_tenHS_ConfigurationModeType_ON;
	}
	else
	{
		//return SBCdrv_tenHS_ConfigurationModeType_OFF;
	}
	return SBCdrv_tenHS_ConfigurationModeType_ON; /*GE-T*/
}

/******************************************************************************/
/*
*Function Name :

* Description   :
* Date          :	2018.04.13	
*/
/******************************************************************************/
 uint8 TLE9262Drv_vGetHS3_ConfigStatus(void)
{
	uint8 u8retvalue;
	u8retvalue=0;


	
	if(u8retvalue==1)
	{
		return SBCdrv_tenHS_ConfigurationModeType_ON;
	}
	else
	{
		return SBCdrv_tenHS_ConfigurationModeType_OFF;
	}
}


/******************************************************************************/
/*
*Function Name :

* Description   :
* Date          :	2018.04.13	
*/
/******************************************************************************/
 uint8 TLE9262Drv_vGetHS4_ConfigStatus(void)
{
	uint8 u8retvalue;
	u8retvalue=0;

	if(u8retvalue==1)
	{
		return SBCdrv_tenHS_ConfigurationModeType_ON;
	}
	else
	{
		return SBCdrv_tenHS_ConfigurationModeType_OFF;
	}
}	
/******************************************************************************/
/*
*Function Name :

* Description   :
* Date          :	2018.04.13	
*/
/******************************************************************************/
 uint16 SBC_vImpIDIgnStatic(void)
{
	uint16 u16retvalue;
	
	u16retvalue=0;
	
	
	return(u16retvalue);
}
/******************************************************************************/
/*
*Function Name :

* Description   :
* Date          :	2018.04.13	
*/
/******************************************************************************/
 uint8 SBC_vGetSysStatus(void)
{
	uint8 u8retvalue;
	
	u8retvalue=0;
    return u8retvalue;
	
}

#endif
