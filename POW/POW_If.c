/*******************************************************************************
| Module Name: Power manage model
| File Name: pow_if.c
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
| Du Zejia                             Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver        	Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 
|2015/08/10 Rev 01.10.00      Li Ning       			 The second version  
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define POW_If                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "Mcu_cfg.h"
/* Please put the headerfiles which related to system here! */

/* Own head file */
#include "Pow_if.h"
#include "Pow_Cfg.h"
#include "Mcu_Cfg.h"
/* Foreign headerfiles */
#include "Rte_Internal.h"
#include "ign.h"

/* Own headerfiles */



/******************************************************************************************************
******************************************import functon definition*****************************************
*******************************************************************************************************/

/*****************************************************************************
 Function      : POW_vImpIDIgnStaticOn                                             *
 Description   :get staticOn                        *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by FRAME_vFRAMEAlways
*****************************************************************************/
 uint16 POW_vImpIDIgnStaticOn(void)
{
	uint16 u16retvalue;
	#if (POW_RteUsed ==1)
		u16retvalue=Rte_IRead_Pow_vMain_PowGetIgnStaticOn_IgnFlag();
	#else
		u16retvalue=IGN_u16GetValue(IGN_nu16IgnStaticOn);
	#endif
	
	return(u16retvalue);
}

/*****************************************************************************
 Function      : POW_vImpIDIgnStable                                             *
 Description   :get staticOn                        *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by FRAME_vFRAMEAlways
*****************************************************************************/
 uint16 POW_vImpIDIgnStable(void)
{
	uint16 u16retvalue;
	#if (POW_RteUsed ==1)
		u16retvalue=Rte_IRead_Pow_vMain_PowGetIgnStable_IgnFlag();
	#else
		u16retvalue=IGN_u16GetValue(IGN_nu16IgnStable);
	#endif
	
	return(u16retvalue);
}

/*****************************************************************************
 Function      : POW_vImpIDGetAnalogValue5VOutputFb                                             *
 Description   :get staticOn                        *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by FRAME_vFRAMEAlways
*****************************************************************************/
 uint16 POW_vImpIDGetAnalogValue5VOutputFb(void)
{
	uint16 u16retvalue;
	uint16 u16temp;	
	
	#if (POW_RteUsed ==1)
		Rte_Call_PowGetAnalogValue5V_Read(&u16temp);		
	#else
		#if (POW_5vOutputFbUsed==1)
			//MCU_u16ADCgetResault((MCU_enAdcaID)POW_nRaw5vOutputFb,&u16temp);
			Rte_Call_IoHwAd_IoHwAd_ReadAd_Pow5Voltage_Read(&u16temp);
		#else
			u16temp=0;
		#endif

	#endif

	u16retvalue=u16temp;
	
	return(u16retvalue);
}

/*****************************************************************************
 Function      : POW_vImpIDGetAnalogValueBatFb                                             *
 Description   :get staticOn                        *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by FRAME_vFRAMEAlways
*****************************************************************************/
 uint16 POW_vImpIDGetAnalogValueBatFb(void)
{
	uint16 u16retvalue;
	uint16 u16temp;	
	#if (POW_RteUsed ==1)
		Rte_Call_IoHwAd_IoHwAb_Analog_K30Fb_AnalogRead(&u16temp);
		
	#else		
		//MCU_u16ADCgetResault((MCU_enAdcaID)POW_nRawKL30VtgFb,&u16temp);
		Rte_Call_IoHwAd_IoHwAd_ReadAd_PowBattVoltage_Read(&u16temp);
	#endif

	u16retvalue=u16temp;
	
	return(u16retvalue);
}

/*****************************************************************************
 Function      : POW_vImpIDGetAnalogValueIgn2Fb                                             *
 Description   :get staticOn                        *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by FRAME_vFRAMEAlways
*****************************************************************************/
 uint16 POW_vImpIDGetAnalogValueIgn2Fb(void)
{
	uint16 u16retvalue;
	uint16 u16temp;
	#if (POW_RteUsed ==1)
		Rte_Call_PowGetAnalogValueK15_Read(&u16temp);
	
	#else
		#if (POW_Ign2FbUsed==1)
			MCU_u16ADCgetResault((MCU_enAdcaID)POW_nRawIGN2VtgFb,&u16temp);			
		#else
			u16temp=0;
		#endif
	#endif

	u16retvalue=u16temp;
	
	return(u16retvalue);
}

/*****************************************************************************
 Function      : POW_vImpIDGet5vSensorSupplyFb                                             *
 Description   :get staticOn                        *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	this function  be call by FRAME_vFRAMEAlways
*****************************************************************************/
 uint16 POW_vImpIDGet5vSensorSupplyFb(void)
{
	
	uint16 u16retvalue;
	uint16 u16temp;
	
	#if (POW_SensorSupplyFbUsed ==1)
		#if (POW_RteUsed ==1)
			
			Rte_Call_PowGetAnalogValueSensorSupply_Read(&u16temp);
			
		#else
			MCU_u16ADCgetResault((MCU_enAdcaID)POW_nRaw5vSensorSupplyFb,&u16temp);	
			
		#endif
	#else
		u16temp = 0;		
	#endif

	u16retvalue=u16temp;
	
	return(u16retvalue);
}



/******************************************************************************************************
******************************************export functon definition*****************************************
*******************************************************************************************************/


/*****************************************************************************
 Function      : POW_vExpIDBattLowVoltage                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpIDBattLowVoltage(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	#if (FRAME_RteUsed ==1)			
		Rte_IWrite_Pow_vMain_PowPutBattLowVoltage_BattLowVoltage(POW_u16Array[POW_nu16AppLowVoltage]);
	#else
		/*getvalue:read data by getvalue function with no rte layer*/
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_vExpIDBattHighVoltage                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpIDBattHighVoltage(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	#if (FRAME_RteUsed ==1)			
		Rte_IWrite_Pow_vMain_PowPutBattHighVoltage_BattHighVoltage(POW_u16Array[POW_nu16AppHighVoltage]);	
	#else
		/*getvalue:read data by getvalue function with no rte layer*/
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_vExpIDComLowVoltage                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpIDComLowVoltage(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	#if (FRAME_RteUsed ==1)			
		Rte_IWrite_Pow_vMain_PowPutComLowVoltage_PowComLowVoltage(POW_u16Array[POW_nu16ComLowVoltage]);	
	#else
		/*getvalue:read data by getvalue function with no rte layer*/
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_vExpIDComHighVoltage                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpIDComHighVoltage(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	#if (FRAME_RteUsed ==1)			
		Rte_IWrite_Pow_vMain_PowPutComHighVoltage_PowComHighVoltage(POW_u16Array[POW_nu16ComHighVoltage]);	
	#else
		/*getvalue:read data by getvalue function with no rte layer*/
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_vExpIDDiagLowVoltage                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpIDDiagLowVoltage(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	#if (FRAME_RteUsed ==1)			
		Rte_IWrite_Pow_vMain_PowPutDiagLowVoltage_PowDiagLowVoltage(POW_u16Array[POW_nu16DiagLowVoltage]);	
	#else
		/*getvalue:read data by getvalue function with no rte layer*/
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_vExpIDDiagHighVoltage                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpIDDiagHighVoltage(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	#if (FRAME_RteUsed ==1)			
		Rte_IWrite_Pow_vMain_PowPutDiagHighVoltage_PowDiagHighVoltage(POW_u16Array[POW_nu16DiagHighVoltage]);	
	#else
		/*getvalue:read data by getvalue function with no rte layer*/
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_vExpIDRef4LowVoltage                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpIDRef4LowVoltage(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	#if (FRAME_RteUsed ==1)	
		#if (Ref4_CheckVoltage==1)
			Rte_IWrite_Pow_vMain_PowPutRef4LowVoltage_PowRef4LowVoltage(POW_u16Array[POW_nu16Ref4LowVoltage]);	
		#endif
	#else
		/*getvalue:read data by getvalue function with no rte layer*/
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_vExpIDRef4HighVoltage                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpIDRef4HighVoltage(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	#if (FRAME_RteUsed ==1)	
		#if (Ref4_CheckVoltage==1)
			Rte_IWrite_Pow_vMain_PowPutRef4HighVoltage_PowRef4HighVoltage(POW_u16Array[POW_nu16Ref4HighVoltage]);
		#endif
	#else
		/*getvalue:read data by getvalue function with no rte layer*/
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_vExpIDAdValid                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpIDAdValid(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	#if (FRAME_RteUsed ==1)			
		Rte_IWrite_Pow_vMain_PowPutAdValid_PowValid(POW_u16Array[POW_nu16AdValid]);	
	#else
		/*getvalue:read data by getvalue function with no rte layer*/
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_vExpIDKl30FbAdValue                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpIDKl30FbAdValue(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	#if (FRAME_RteUsed ==1)	
		Rte_IWrite_Pow_vMain_PowPutKl30FbAdValue_PowVtgFbAdValue(POW_u16Array[POW_nu16RawK30VoltFb]);
		Rte_IWrite_Pow_vMain_PowPutKl30FbAdValue_PowVtgFbAdValue(POW_u16Array[POW_nu16ResultK30VoltFb]);
	#else
		/*getvalue:read data by getvalue function with no rte layer*/
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_vExpIDKl15FbAdValue                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpIDKl15FbAdValue(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	#if (FRAME_RteUsed ==1)		
		Rte_IWrite_Pow_vMain_PowPutKl15FbAdValue_PowVtgFbAdValue(POW_u16Array[POW_nu16RawIGN2VoltFb]);
		Rte_IWrite_Pow_vMain_PowPutKl15FbAdValue_PowVtgFbAdValue(POW_u16Array[POW_nu16ResultIGN2VoltFb]);
	#else
		/*getvalue:read data by getvalue function with no rte layer*/
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_vExpIDSwVersion                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpIDSwVersion(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	#if (FRAME_RteUsed ==1)			
		Rte_IWrite_Pow_vMain_PowPutVersion_Version(POW_u16Array[POW_nu16SwVersion]);
	#else
		/*getvalue:read data by getvalue function with no rte layer*/
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_vExpIDErrorCode                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpIDErrorCode(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	#if (FRAME_RteUsed ==1)			
		Rte_IWrite_Pow_vMain_PowPutErrorCode_u16ErrorCode(POW_u16Array[POW_nu16ErrorCode]);
	#else
		/*getvalue:read data by getvalue function with no rte layer*/
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_vExpID5vOutputStable                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpID5vOutputStable(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	#if (POW_5vOutputStableUsed==1)
		#if (FRAME_RteUsed ==1)			
			Rte_IWrite_Pow_vMain_PowPut5vOutputStable_Pow5vOutputStable(POW_u16Array[POW_nu165vOutputStable]);
		#else
			/*getvalue:read data by getvalue function with no rte layer*/
		#endif
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}

/*****************************************************************************
 Function      : POW_vExpID5vOutputStable                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 POW_vExpID5vFbAdValue(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;

	#if (FRAME_RteUsed ==1)			
		Rte_IWrite_Pow_vMain_PowPut5vFbAdValue_Pow5vFbAdValue(POW_u16Array[POW_nu16Raw5vOutputFb]);
		Rte_IWrite_Pow_vMain_PowPut5vFbAdValue_Pow5vFbAdValue(POW_u16Array[POW_nu16Result5vOutputFb]);
	#else
		/*getvalue:read data by getvalue function with no rte layer*/
	#endif

	u16retvalue = 1;
	return (u16retvalue);
}


/*****************************************************************************
 Function      : POW_vExpIDAll                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
 uint16 POW_vExpIDAll(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	
	POW_vExpIDBattLowVoltage();
	POW_vExpIDBattHighVoltage();
	POW_vExpIDComLowVoltage();
	POW_vExpIDComHighVoltage();
	POW_vExpIDDiagLowVoltage();
	POW_vExpIDDiagHighVoltage();
	POW_vExpIDAdValid();
	POW_vExpIDKl30FbAdValue();
	POW_vExpIDKl15FbAdValue();
	POW_vExpIDSwVersion();
	POW_vExpIDErrorCode();
	POW_vExpID5vOutputStable();
	POW_vExpID5vFbAdValue();	

	u16retvalue = 1;
	return (u16retvalue);
}

/* ===========================================================================
* Function   : uint16 POW_u16GetValue(POW_tenu16VarNum Num)
* Description: supply variable for other modules.
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/


uint16 POW_u16GetValue(POW_tenu16VarNum Num)
{
	uint16 u16Ret=0U;
	
	if(Num<POW_nu16Max)
	{
		u16Ret= (POW_u16Array[Num]);
	}
	else
	{
		 u16Ret=(POW_u16Array[POW_nu16Max-1U]);
	}
	
	return u16Ret;
}


/******************************************************************************************************
******************************************other functon definition*****************************************
*******************************************************************************************************/
/* ===========================================================================
* Function   : uint16 POW_vMcuSupplyEnable(void)
* Description: mcu supply.
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/

uint16 POW_vMcuSupplyEnable( void)
{
	uint16 u16Ret=0U;
	#if (POW_VccCutOffUsed==1)
	
		#if (FRAME_RteUsed ==1)
			Rte_Call_Pow_PowProto_PowMcuSupplyEnable_Write( POW_McuSupply_OnLevel);
		#else
			MCU_u16PinWrite((MUC_enPinID)POW_McuSupply_PortPin,POW_McuSupply_OnLevel);	
			
		#endif
	#endif

	u16Ret=1;
	return u16Ret;
}


/* ===========================================================================
* Function   : uint16 POW_vMcuSupplyEnable(void)
* Description: mcu supply.
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/


uint16 POW_vMcuSupplyDisable( void)
{
	uint16 u16Ret=0U;

	#if (POW_VccCutOffUsed==1)
		#if (FRAME_RteUsed ==1)
			Rte_Call_Pow_PowProto_PowMcuSupplyDisable_Write( POW_McuSupply_OffLevel);
		#else
			MCU_u16PinWrite((MUC_enPinID)POW_McuSupply_PortPin,POW_McuSupply_OffLevel);	
			
		#endif

	#endif
	u16Ret=1;
	return u16Ret;
}


/* ===========================================================================
* Function   : uint16 POW_vSensorSupplyEnable(void)
* Description: sensor supply
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/

uint16 POW_vSensorSupplyEnable( void)
{
	uint16 u16Ret=0U;

	#if (POW_SensorSupplyCtrlUsed==1)
		#if (FRAME_RteUsed ==1)
			Rte_Call_PowPutSensorSupply_Write( POW_SensorSupply_OnLevel);
		#else
			//MCU_u16PinWrite((MUC_enPinID)POW_SensorSupply_PortPin,POW_SensorSupply_OnLevel);
			Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_PowSensorSupply_Write(POW_SensorSupply_OnLevel);
		#endif
	#endif

	u16Ret=1;
	return u16Ret;
}

/* ===========================================================================
* Function   : uint16 POW_vSensorSupplyDisable(void)
* Description: sensor supply
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/

uint16 POW_vSensorSupplyDisable( void)
{
	uint16 u16Ret=0U;

	#if (POW_SensorSupplyCtrlUsed==1)
		#if (FRAME_RteUsed ==1)
			Rte_Call_PowPutSensorSupply_Write( POW_SensorSupply_OffLevel);
		#else
			//MCU_u16PinWrite((MUC_enPinID)POW_SensorSupply_PortPin,POW_SensorSupply_OffLevel);
			Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_PowSensorSupply_Write(POW_SensorSupply_OffLevel);
		#endif
	#endif

	u16Ret=1;
	return u16Ret;
}

/* ===========================================================================
* Function   : uint16 POW_v5vOutputEnable(void)
* Description: 5v output
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/

uint16 POW_v5vOutputEnable( void)
{
	uint16 u16Ret=0U;
	#if (POW_5vOutPutCtrlUsed==1)
	
		#if (FRAME_RteUsed ==1)
			Rte_Call_PowPut5vOutputPin_Write( POW_5vOutput_OnLevel);
		#else
			//MCU_u16PinWrite((MUC_enPinID)POW_5vOutput_PortPin,POW_5vOutput_OnLevel);
			Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_Pow5VOutput_Write(POW_5vOutput_OnLevel);
		#endif
	#endif

	u16Ret=1;
	return u16Ret;
}

/* ===========================================================================
* Function   : uint16 POW_v5vOutputDisable(void)
* Description: 5v output
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/

uint16 POW_v5vOutputDisable( void)
{
	uint16 u16Ret=0U;
	#if (POW_5vOutPutCtrlUsed==1)
		#if (FRAME_RteUsed ==1)
			Rte_Call_PowPut5vOutputPin_Write( POW_5vOutput_OffLevel);
		#else
			//MCU_u16PinWrite((MUC_enPinID)POW_5vOutput_PortPin,POW_5vOutput_OffLevel);
			Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_Pow5VOutput_Write(POW_5vOutput_OffLevel);
		#endif
	#endif

	u16Ret=1;
	return u16Ret;
}

/* ===========================================================================
* Function   : uint16 POW_v5vAmpOutputEnable(void)
* Description: 5v output
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/

uint16 POW_v5vAmpOutputEnable( void)
{
	uint16 u16Ret=0U;
	#if (POW_5vOutPutCtrlUsed==1)
	
		#if (FRAME_RteUsed ==1)
			Rte_Call_PowPut5vOutputPin_Write( POW_5vOutput_OnLevel);
		#else
			//MCU_u16PinWrite((MUC_enPinID)POW_5vOutput_PortPin,POW_5vOutput_OnLevel);
			Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_Pow5VAmpOutput_Write(1u);
		#endif
	#endif

	u16Ret=1;
	return u16Ret;
}

/* ===========================================================================
* Function   : uint16 POW_v5vAmpOutputDisable(void)
* Description: 5v output
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/

uint16 POW_v5vAmpOutputDisable( void)
{
	uint16 u16Ret=0U;
	#if (POW_5vOutPutCtrlUsed==1)
		#if (FRAME_RteUsed ==1)
			Rte_Call_PowPut5vOutputPin_Write( POW_5vOutput_OffLevel);
		#else
			//MCU_u16PinWrite((MUC_enPinID)POW_5vOutput_PortPin,POW_5vOutput_OffLevel);
			Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_Pow5VAmpOutput_Write(0u);
		#endif
	#endif

	u16Ret=1;
	return u16Ret;
}


/* ===========================================================================
* Function   :  void POW_vSupplyReset(void)
* Description: reset all the supply  power.
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/
 void POW_vSupplyReset(void)
{   
	#if (POW_VccCutOffUsed ==1)
		POW_vMcuSupplyEnable();
	#endif

    POW_v5vAmpOutputEnable();
	POW_v5vOutputDisable();	
	POW_vSensorSupplyEnable();
	MCU_u16PinWrite((MUC_enPinID)MCU_mPinID_P8_5,True);/***touch rest pin set high level***/
	
}

/* ===========================================================================
* Function   :  void POW_vSupplyWakeup(void)
* Description: wake up all the   supply power.
* Input      : 
* Returns    : 
*/
 void POW_vSupplyWakeup(void)
{   
	POW_vSupplyReset();
	
}

/* ===========================================================================
* Function   :  void POW_vSupplyOff(void)
* Description:  all the supply  power off.
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/
 void POW_vSupplyOff(void)
{   
    POW_v5vAmpOutputDisable();
	POW_v5vOutputDisable();	
	POW_vSensorSupplyDisable();
	#if (POW_VccCutOffUsed ==1)
		POW_vMcuSupplyDisable();
	#endif
	
}





/*****************************************************************************
* EOF: Pow_If.c
*****************************************************************************/
