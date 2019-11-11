/*******************************************************************************
| Module Name: DTC process(prcess dianostic code)
| File Name: DTC_Interface.c
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
| .Date; 2018-6-5
| .Update Time; 14:49:42
| .DTCDefineList; D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\DTC\DTCGen\FE-5DB&7DA DTC list_20180605.xlsm
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
| 2014-11-24  1.00        Sui Yanchun       update the DTC module
| 2015-12-56  2.00        Lin Tao           update for the MISRA C
| 2017-07-21  3.00        Li Jiaye          interface update
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define DTC_Interface                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h" 
#include "General.h" 
#include "LinApp.h"
#include "CanApp.h"
#include "CanNmApp.h"
#include "Pow.h"
#include "BCTLDrv.h"
#include "EVAP.h"
#include "OAT.h"
#include "SUN.h"
#include "ION.h"
#include "Rte_Internal.h"
/* Foreign headerfiles */
/* Own headerfiles */
#include "DTC_Cfg.h" 
#include "DTC_Type.h" 
#include "DTC.h" 
#include "DTC_interface.h" 


/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/
static uint8 DTCInterface_u8BusOffReturnValue=0;
static uint8 DTCInterface_u8BusOffResumTimer=0;

static uint16 DTCInterface_u16HighVolCounter = 0;
static uint16 DTCInterface_u16HighVolRecoveryCnt = DTC_nHighLowVolCfgTimer;
static uint16 DTCInterface_u16LowVolCounter = 0;
static uint16 DTCInterface_u16LowVolRecoveryCnt =DTC_nHighLowVolCfgTimer ;
static uint8  DTCInterface_u8PowHighReturn= 0;
static uint8  DTCInterface_u8PowLowReturn= 0;

/*============================================================================
*Function : uint8 DTC_u8BusOffDtcStsImport(void) 
*Description :0 - Control Module CAN Bus Off
控制CAN总线关闭*
*takes : nothing
*return: BusOff status
*/
uint8 DTC_u8BusOffDtcStsImport(void) 
{
   	uint8 u8CanBusOffConfirm = False,u8CanBusOffStart = False;

	u8CanBusOffStart = DTC_u16GetCANBusOffStart;
	u8CanBusOffConfirm = DTC_u16GetCANBusOffConfirm;

	/*CAN Bus off */
	if(u8CanBusOffStart == True)
	{
	    DTCInterface_u8BusOffResumTimer = DTC_nBusOffResumTime;
	}

	if(DTCInterface_u8BusOffResumTimer!=0U)
	{
	    DTCInterface_u8BusOffResumTimer--;
	}

	if(u8CanBusOffStart == True)
	{       
	    if(u8CanBusOffConfirm == True)
	    {
	        DTCInterface_u8BusOffReturnValue=True;
	    }
	    else
	    {
	       DTCInterface_u8BusOffReturnValue=False;
	    }
	    DTC_vClearCANMessCnt();
	}
	else
	{
	    if((DTCInterface_u8BusOffResumTimer==0U)&&(DTC_u16GetIgOnDelayTmr() >=DTC_nu16IGDelayTimer))
	    {
	       DTCInterface_u8BusOffReturnValue=False;
	    }
	    else
	    {
	        DTC_vClearCANMessCnt();            
	    }
	}
	return DTCInterface_u8BusOffReturnValue;
}


/*============================================================================
*Function : uint8 DTC_u8ErrPEPSDtcStsImport(void) 
*Description :1 - Invalid Data Received From PEPS
PEPS CAN通讯错误*
*takes : nothing
*return: ErrPEPS status
*/
uint8 DTC_u8ErrPEPSDtcStsImport(void) 
{
    //uint32 u32BusErrCode;
	uint32 u32BusDlcErrCode;
    
    //u32BusErrCode = DTC_u32GetCANAppErrCode;
	u32BusDlcErrCode = DTC_u32GetCANAppDlcErrCode;
	if(DTC_u16GetCANBusOffStart==True)
	{
		return False;
	}
	else
	{
		if((u32BusDlcErrCode&(1<<CANAPP_nPeps))>0)
		{
			return True;
		}
		else
		{
			return False;
		}
	}
}


/*============================================================================
*Function : uint8 DTC_u8ErrEMSDtcStsImport(void) 
*Description :2 - Invalid Data Received From EMS
EMS CAN通讯错误*
*takes : nothing
*return: ErrEMS status
*/
uint8 DTC_u8ErrEMSDtcStsImport(void) 
{
    //uint32 u32BusErrCode;
	uint32 u32BusDlcErrCode;
    
    //u32BusErrCode = DTC_u32GetCANAppErrCode;
	u32BusDlcErrCode = DTC_u32GetCANAppDlcErrCode;
	if(DTC_u16GetCANBusOffStart==True)
	{
		return False;
	}
	else
	{
		if(((u32BusDlcErrCode&(1<<CANAPP_nEmsDrv))>0) || ((u32BusDlcErrCode&(1<<CANAPP_nEmsRPM))>0)\
            || ((u32BusDlcErrCode&(1<<CANAPP_nEmsEng))>0))
		{
			return True;
		}
		else
		{
			return False;
		}
	}
}


/*============================================================================
*Function : uint8 DTC_u8ErrESCDtcStsImport(void) 
*Description :3 - Invalid Data Received From ESC
ESC CAN通讯错误*
*takes : nothing
*return: ErrESC status
*/
uint8 DTC_u8ErrESCDtcStsImport(void) 
{
    //uint32 u32BusErrCode;
	uint32 u32BusDlcErrCode;
    
    //u32BusErrCode = DTC_u32GetCANAppErrCode;
	u32BusDlcErrCode = DTC_u32GetCANAppDlcErrCode;
	if(DTC_u16GetCANBusOffStart==True)
	{
		return False;
	}
	else
	{
		if((u32BusDlcErrCode&(1<<CANAPP_nEsc))>0)
		{
			return True;
		}
		else
		{
			return False;
		}
	}
}


/*============================================================================
*Function : uint8 DTC_u8ErrIPKDtcStsImport(void) 
*Description :4 - Invalid Data Received From IPK
IPK CAN通讯错误*
*takes : nothing
*return: ErrIPK status
*/
uint8 DTC_u8ErrIPKDtcStsImport(void) 
{
    //uint32 u32BusErrCode;
	uint32 u32BusDlcErrCode;
    
    //u32BusErrCode = DTC_u32GetCANAppErrCode;
	u32BusDlcErrCode = DTC_u32GetCANAppDlcErrCode;
	if(DTC_u16GetCANBusOffStart==True)
	{
		return False;
	}
	else
	{
		if((u32BusDlcErrCode&(1<<CANAPP_nIpk))>0)
		{
			return True;
		}
		else
		{
			return False;
		}
	}
}


/*============================================================================
*Function : uint8 DTC_u8ErrMMIDtcStsImport(void) 
*Description :5 - Invalid Data Received From MMI
MMI CAN通讯错误*
*takes : nothing
*return: ErrMMI status
*/
uint8 DTC_u8ErrMMIDtcStsImport(void) 
{
    //uint32 u32BusErrCode;
	uint32 u32BusDlcErrCode;
    
    //u32BusErrCode = DTC_u32GetCANAppErrCode;
	u32BusDlcErrCode = DTC_u32GetCANAppDlcErrCode;
	if(DTC_u16GetCANBusOffStart==True)
	{
		return False;
	}
	else
	{
		if(((u32BusDlcErrCode&(1<<CANAPP_nMmiAc))>0) || ((u32BusDlcErrCode&(1<<CANAPP_nMmiHvsm))>0))
		{
			return True;
		}
		else
		{
			return False;
		}
	}
}


/*============================================================================
*Function : uint8 DTC_u8ErrTBOXDtcStsImport(void) 
*Description :6 - Invalid Data Received From TBOX
TBOX CAN通讯错误*
*takes : nothing
*return: ErrTBOX status
*/
uint8 DTC_u8ErrTBOXDtcStsImport(void) 
{
    //uint32 u32BusErrCode;
	uint32 u32BusDlcErrCode;
    
    //u32BusErrCode = DTC_u32GetCANAppErrCode;
	u32BusDlcErrCode = DTC_u32GetCANAppDlcErrCode;
	if(DTC_u16GetCANBusOffStart==True)
	{
		return False;
	}
	else
	{
		if((u32BusDlcErrCode&(1<<CANAPP_nTbox))>0)
		{
			return True;
		}
		else
		{
			return False;
		}
	}
}


/*============================================================================
*Function : uint8 DTC_u8LostEMSDtcStsImport(void) 
*Description :7 - Lost Communication with EMS
与EMS通信丢失*
*takes : nothing
*return: LostEMS status
*/
uint8 DTC_u8LostEMSDtcStsImport(void) 
{
	uint32 u32BusErrCode;
	u32BusErrCode = DTC_u32GetCANAppErrCode;
	if(DTC_u16GetCANBusOffStart==True)
	{
		return False;
	}
	else
	{
		if((u32BusErrCode&((uint32)1<<CANAPP_nbiEMS_EngineRPM_0x85))>0)
		{
			return True;
		}
		else
		{
			return False;
		}
	}
}


/*============================================================================
*Function : uint8 DTC_u8LostESCDtcStsImport(void) 
*Description :8 - Lost Communication with the ESC
与ESC通信丢失*
*takes : nothing
*return: LostESC status
*/
uint8 DTC_u8LostESCDtcStsImport(void) 
{
	uint32 u32BusErrCode;
	u32BusErrCode = DTC_u32GetCANAppErrCode;
	if(DTC_u16GetCANBusOffStart==True)
	{
		return False;
	}
	else
	{
		if((u32BusErrCode&((uint32)1<<CANAPP_nbiESC_Status_0x125))>0)
		{
			return True;
		}
		else
		{
			return False;
		}
	}
}


/*============================================================================
*Function : uint8 DTC_u8LostIPKDtcStsImport(void) 
*Description :9 - Lost Communication with IPK
与IPK通信丢失*
*takes : nothing
*return: LostIPK status
*/
uint8 DTC_u8LostIPKDtcStsImport(void) 
{
	uint32 u32BusErrCode;
	u32BusErrCode = DTC_u32GetCANAppErrCode;
	if(DTC_u16GetCANBusOffStart==True)
	{
		return False;
	}
	else
	{
		if((u32BusErrCode&((uint32)1<<CANAPP_nbiIPK_TotalOdometer_0x3F1))>0)
		{
			return True;
		}
		else
		{
			return False;
		}
	}
}


/*============================================================================
*Function : uint8 DTC_u8LostMMIDtcStsImport(void) 
*Description :10 - Lost Communication  with MMI
与MMI通信丢失*
*takes : nothing
*return: LostMMI status
*/
uint8 DTC_u8LostMMIDtcStsImport(void) 
{
	uint32 u32BusErrCode;
	u32BusErrCode = DTC_u32GetCANAppErrCode;
	if(DTC_u16GetCANBusOffStart==True)
	{
		return False;
	}
	else
	{
		if((u32BusErrCode&((uint32)1<<CANAPP_nbiMMI_AC_Command_0x2A5))>0)
		{
			return True;
		}
		else
		{
			return False;
		}
	}
}


/*============================================================================
*Function : uint8 DTC_u8LostTBOXDtcStsImport(void) 
*Description :11 - Lost Communication with TBOX
与TBOX通信丢失*
*takes : nothing
*return: LostTBOX status
*/
uint8 DTC_u8LostTBOXDtcStsImport(void) 
{
	uint32 u32BusErrCode;
	u32BusErrCode = DTC_u32GetCANAppErrCode;
	if(DTC_u16GetCANBusOffStart==True)
	{
		return False;
	}
	else
	{
		if((u32BusErrCode&((uint32)1<<CANAPP_nbiTBOX_RemCon_0x292))>0)
		{
			return True;
		}
		else
		{
			return False;
		}
	}
}


/*============================================================================
*Function : uint8 DTC_u8LostPEPSDtcStsImport(void) 
*Description :12 - Lost Communication with the PEPS
与PEPS通信丢失*
*takes : nothing
*return: LostPEPS status
*/
uint8 DTC_u8LostPEPSDtcStsImport(void) 
{
	uint32 u32BusErrCode;
	u32BusErrCode = DTC_u32GetCANAppErrCode;
	if(DTC_u16GetCANBusOffStart==True)
	{
		return False;
	}
	else
	{
		if((u32BusErrCode&((uint32)1<<CANAPP_nbiPEPS_Message_Sts_0x1E2))>0)
		{
			return True;
		}
		else
		{
			return False;
		}
	}
}


/*============================================================================
*Function : uint8 DTC_u8PowLowDtcStsImport(void) 
*Description :13 - Control Module Input Power Low
控制模块输入电压低*
*takes : nothing
*return: PowLow status
*/
uint8 DTC_u8PowLowDtcStsImport(void) 
{
	uint8 u8EnagStatus;
	u8EnagStatus = DTC_u8GetEngStatus;
	if(u8EnagStatus != 0x01U)
	{
		if(DTC_boGetPOWDiagLow==True)
		{
			DTCInterface_u16LowVolRecoveryCnt=0;
			if(DTCInterface_u16LowVolCounter<DTC_nHighLowVolCfgTimer)
			{
				DTCInterface_u16LowVolCounter++;
			}			
		}
		else
		{
			DTCInterface_u16LowVolCounter=0;
			if(DTCInterface_u16LowVolRecoveryCnt<DTC_nHighLowVolCfgTimer)
			{
				DTCInterface_u16LowVolRecoveryCnt++;
			}
		}
		if(DTCInterface_u16LowVolCounter==DTC_nHighLowVolCfgTimer)
		{
			DTCInterface_u8PowLowReturn=1;
		}
		if(DTCInterface_u16LowVolRecoveryCnt==DTC_nHighLowVolCfgTimer)
		{
			DTCInterface_u8PowLowReturn=0;
		}
		return DTCInterface_u8PowLowReturn;
	}
	
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8PowHighDtcStsImport(void) 
*Description :14 - Control Module Input Power High
控制模块输入电压高*
*takes : nothing
*return: PowHigh status
*/
uint8 DTC_u8PowHighDtcStsImport(void) 
{
	uint8 u8EnagStatus;
	u8EnagStatus = DTC_u8GetEngStatus;
	if(u8EnagStatus != 0x01U)
	{
		if(DTC_boGetPOWDiagHigh==True)
		{
			DTCInterface_u16HighVolRecoveryCnt=0;
			if(DTCInterface_u16HighVolCounter<DTC_nHighLowVolCfgTimer)
			{
				DTCInterface_u16HighVolCounter++;
			}			
		}
		else
		{
			DTCInterface_u16HighVolCounter=0;
			if(DTCInterface_u16HighVolRecoveryCnt<DTC_nHighLowVolCfgTimer)
			{
				DTCInterface_u16HighVolRecoveryCnt++;
			}
		}
		if(DTCInterface_u16HighVolCounter==DTC_nHighLowVolCfgTimer)
		{
			DTCInterface_u8PowHighReturn=1;
		}
		if(DTCInterface_u16HighVolRecoveryCnt==DTC_nHighLowVolCfgTimer)
		{
			DTCInterface_u8PowHighReturn=0;
		}
		return DTCInterface_u8PowHighReturn;
	}
	
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8BlowerErrDtcStsImport(void) 
*Description :15 - blower voltage feedback is too much differ to target 
鼓风机电压反馈与目标值相差大*
*takes : nothing
*return: BlowerErr status
*/
uint8 DTC_u8BlowerErrDtcStsImport(void) 
{
	uint16 u16BlowerErrCode = DTC_u16GetBlowerErrCode;
	if(u16BlowerErrCode==0x0001)
	{
		return 1;
	}
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8Mix1GndDtcStsImport(void) 
*Description :16 - Driver Temperature door motor short cut to ground
驾驶员侧温度调节电机对地短路*
*takes : nothing
*return: Mix1Gnd status
*/
uint8 DTC_u8Mix1GndDtcStsImport(void) 
{
	if((DTC_u8GetDcmMixDrErrCode & DTC_nDcmShortGndCode)== DTC_nDcmShortGndCode)
	{
		return 1;
	}
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8Mix1BatDtcStsImport(void) 
*Description :17 - Driver Temperature door motor short cut to power or open load
驾驶员侧温度调节电机对电源短路或开路*
*takes : nothing
*return: Mix1Bat status
*/
uint8 DTC_u8Mix1BatDtcStsImport(void) 
{
	if((DTC_u8GetDcmMixDrErrCode & DTC_nDcmShortBatCode)== DTC_nDcmShortBatCode)
	{
		return 1;
	}
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8Mix1BlockDtcStsImport(void) 
*Description :18 - Driver Temperature door motor stuck
驾驶员侧温度调节电机堵转*
*takes : nothing
*return: Mix1Block status
*/
uint8 DTC_u8Mix1BlockDtcStsImport(void) 
{
	if((DTC_u8GetDcmMixDrErrCode & DTC_nDcmBlockCode)== DTC_nDcmBlockCode)
	{
		return 1;
	}
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8Mix2GndDtcStsImport(void) 
*Description :19 - Passenger Temperature door motor short cut to ground
副驾侧温度调节电机对地短路*
*takes : nothing
*return: Mix2Gnd status
*/
uint8 DTC_u8Mix2GndDtcStsImport(void) 
{
	if((DTC_u8GetDcmMixPsErrCode & DTC_nDcmShortGndCode)== DTC_nDcmShortGndCode)
	{
		return 1;
	}
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8Mix2BatDtcStsImport(void) 
*Description :20 - Passenger Temperature door motor short cut to power or open load
副驾侧温度调节电机对电源短路或开路*
*takes : nothing
*return: Mix2Bat status
*/
uint8 DTC_u8Mix2BatDtcStsImport(void) 
{
	if((DTC_u8GetDcmMixPsErrCode & DTC_nDcmShortBatCode)== DTC_nDcmShortBatCode)
	{
		return 1;
	}
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8Mix2BlockDtcStsImport(void) 
*Description :21 - Passenger Temperature door motor stuck
副驾驶员侧温度调节电机堵转*
*takes : nothing
*return: Mix2Block status
*/
uint8 DTC_u8Mix2BlockDtcStsImport(void) 
{
	if((DTC_u8GetDcmMixPsErrCode & DTC_nDcmBlockCode)== DTC_nDcmBlockCode)
	{
		return 1;
	}
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8AirdGndDtcStsImport(void) 
*Description :22 - Air distribution motor short cut to ground
出风模式调节电机对地短路*
*takes : nothing
*return: AirdGnd status
*/
uint8 DTC_u8AirdGndDtcStsImport(void) 
{
	if((DTC_u8GetDcmAirdErrCode & DTC_nDcmShortGndCode)== DTC_nDcmShortGndCode)
	{
		return 1;
	}
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8AirdBatDtcStsImport(void) 
*Description :23 - Air distribution motor short cut to power or open load
出风模式调节电机对电源短路或开路*
*takes : nothing
*return: AirdBat status
*/
uint8 DTC_u8AirdBatDtcStsImport(void) 
{
	if((DTC_u8GetDcmAirdErrCode & DTC_nDcmShortBatCode)== DTC_nDcmShortBatCode)
	{
		return 1;
	}
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8AirdBlockDtcStsImport(void) 
*Description :24 - Air distribution motor stuck
出风模式调节电机堵转*
*takes : nothing
*return: AirdBlock status
*/
uint8 DTC_u8AirdBlockDtcStsImport(void) 
{
	if((DTC_u8GetDcmAirdErrCode & DTC_nDcmBlockCode)== DTC_nDcmBlockCode)
	{
		return 1;
	}
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8RfaGndDtcStsImport(void) 
*Description :25 - Recirculation moto motor short cut to ground
循环风门电机对地短路*
*takes : nothing
*return: RfaGnd status
*/
uint8 DTC_u8RfaGndDtcStsImport(void) 
{
	if((DTC_u8GetDcmRfaErrCode & DTC_nDcmShortGndCode)== DTC_nDcmShortGndCode)
	{
		return 1;
	}
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8RfaBatDtcStsImport(void) 
*Description :26 - Recirculation motor short cut to power or open load
循环风门电机对电源短路或开路*
*takes : nothing
*return: RfaBat status
*/
uint8 DTC_u8RfaBatDtcStsImport(void) 
{
	if((DTC_u8GetDcmRfaErrCode & DTC_nDcmShortBatCode)== DTC_nDcmShortBatCode)
	{
		return 1;
	}
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8RfaBlockDtcStsImport(void) 
*Description :27 - Recirculation motor stuck
循环风门电机电机堵转*
*takes : nothing
*return: RfaBlock status
*/
uint8 DTC_u8RfaBlockDtcStsImport(void) 
{
	if((DTC_u8GetDcmRfaErrCode & DTC_nDcmBlockCode)== DTC_nDcmBlockCode)
	{
		return 1;
	}
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8EvapGndDtcStsImport(void) 
*Description :28 - Evaporator temperatrue sensor short cut to ground
蒸发器温度传感器对地短路*
*takes : nothing
*return: EvapGnd status
*/
uint8 DTC_u8EvapGndDtcStsImport(void) 
{
	if((DTC_u16GetEvapErrCode&DTC_nSensorShortGndCode) == DTC_nSensorShortGndCode)
	{
		return 1;
	}	
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8EvapBatDtcStsImport(void) 
*Description :29 - Evaporator temperatrue sensor short cut to power or open load
蒸发器温度传感器对电源短路或开路*
*takes : nothing
*return: EvapBat status
*/
uint8 DTC_u8EvapBatDtcStsImport(void) 
{
	if((DTC_u16GetEvapErrCode&DTC_nSensorShortBatCode) == DTC_nSensorShortBatCode)
	{
		return 1;
	}	
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8OatGndDtcStsImport(void) 
*Description :30 - Outside temperatrue sensor short cut to ground
车外温度传感器对地短路*
*takes : nothing
*return: OatGnd status
*/
uint8 DTC_u8OatGndDtcStsImport(void) 
{
	if((DTC_u16GetOatErrCode&DTC_nSensorShortGndCode) == DTC_nSensorShortGndCode)
	{
		return 1;
	}	
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8OatBatDtcStsImport(void) 
*Description :31 - Outside temperatrue sensor short cut to power or open load
车外温度传感器对电源短路或开路*
*takes : nothing
*return: OatBat status
*/
uint8 DTC_u8OatBatDtcStsImport(void) 
{
	if((DTC_u16GetOatErrCode&DTC_nSensorShortBatCode) == DTC_nSensorShortBatCode)
	{
		return 1;
	}	
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8SunDrGndDtcStsImport(void) 
*Description :32 - Driver Sunload sensor is short to GND
主驾侧阳光传感器 短路到地 *
*takes : nothing
*return: SunDrGnd status
*/
uint8 DTC_u8SunDrGndDtcStsImport(void) 
{
	if((DTC_u16GetSunErrCode&DTC_nSensorShortGndCode) == DTC_nSensorShortGndCode)
	{
		return 1;
	}	
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8SunDrBatDtcStsImport(void) 
*Description :33 - Driver Sunload sensor short to power or open load
主驾侧阳光传感器对电源短路或开路*
*takes : nothing
*return: SunDrBat status
*/
uint8 DTC_u8SunDrBatDtcStsImport(void) 
{
	if((DTC_u16GetSunErrCode&DTC_nSensorShortBatCode) == DTC_nSensorShortBatCode)
	{
		return 1;
	}	
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8LostPM25DtcStsImport(void) 
*Description :34 - Lost Communication with PM2.5
与PM2.5 通讯丢失*
*takes : nothing
*return: LostPM25 status
*/
//extern uint8 DTC_u8GetNetWorkCfgValue(DTC_tenu8VarVechileCfg enIndex );
uint8 DTC_u8LostPM25DtcStsImport(void) 
{
	if(((DTC_u32GetLinAppErrCode&((uint32)1<<LINAPP_nPM25_1))>0)
		&&(DIAG_u8GetValue(DIAG_nu8AQSMount)==True)
		&&(ION_u8GetValue(ION_nu8PM25StsReq)==True))
	{
		return 1;
	}
  	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8PM25HWErrDtcStsImport(void) 
*Description :35 - PM2.5 Hardware errror
PM2.5 硬件故障*
*takes : nothing
*return: PM25HWErr status
*/
uint8 DTC_u8PM25HWErrDtcStsImport(void) 
{
    if((DIAG_u8GetValue(DIAG_nu8AQSMount)==True) && (ION_u8GetValue(ION_nu8PM25StsReq)==True))
    {
    	if(DTC_u16GetPM25HWErrCode<0xFFFE)
    	{
    		if((DTC_u16GetPM25HWErrCode&DTC_nPM25ErrCode) != 0)
    		{
    			return 1;
    		}
    	}
    }
	return 0;
}


/*============================================================================
*Function : uint8 DTC_u8AQSHWErrDtcStsImport(void) 
*Description :36 - AQS Hardware errror
AQS 硬件故障*
*takes : nothing
*return: AQSHWErr status
*/
uint8 DTC_u8AQSHWErrDtcStsImport(void) 
{
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
	//if(DIAG_u8GetValue(DIAG_nu8AQSMount)==True)
	{
		if(DTC_u16GetAQSErrCode)
		{
			return 1;
		}	
	}
#endif
    return 0;
}

/*============================================================================
*Function : uint8 DTC_u8LostFCPDtcStsImport(void) 
*Description :64 - Lost Communication with FCP
与KL15 状态?
*takes : nothing
*return: LostFCP status
*/
uint8 DTC_u8K15StsImport(void) 
{
	
	uint16 returnvalue;
	Rte_Call_IoHwPortRead_IoHwReadPort_Digital_IgnPort_ReadPort_IgnPort_Read(&returnvalue);	
	return  (uint8)returnvalue;
}


