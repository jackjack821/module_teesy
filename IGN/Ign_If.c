/*******************************************************************************
| Module Name: KL15 manage model
| File Name: ign_if.c
|
|-------------------------------------------------------------------------------
|				C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2015 Huizhou Desay SV Automotive Co., Ltd.	  All rights reserved.
|
| This software is copyright protected and proprietary to Desay SV Automotive Co., Ltd.
| Desay SV Automotive Co., Ltd grants to you only those rights as set out in the
| license conditions. All other rights remain with Desay SV Automotive Co., Ltd.
|
| REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
|-------------------------------------------------------------------------------
|				A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Name									Company
| --------------------- 	---------------------------------------
| Sui Yanchun						 Desay SV Automotive Co., Ltd
| Du Zejia							   Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|				R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date			   Ver			Author				 Description
| ----------  -------  -------------  -------------------------------------------------
| 
|2014/07/28 	Rev 01.00.00	  LN				 The first version	 
********************************************************************************/

/*****************************************************************************
* FILE DECLARATIGN
*****************************************************************************/
#ifndef IGN_IF
#define IGN_IF                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "Mcu_cfg.h"
/* Please put the headerfiles which related to system here! */

/* Own headerfiles */
#include "IGN_if.h" 
#include "IGN_cfg.h" 
#include "IGN_pte.h" 
#include "IGN.h" 

/* Foreign headerfiles */
#include "Rte_Internal.h"

//#include "canapp.h"


/* Please put the headerfiles which related to own here! */


/*****************************************************************************
* MODULE GLOBAL CONFIGURATIGN CONSTANTS
*
* In this sectIGN define
* - constants and macros to configure your module. These constants are unknown for other 
*   modules
*****************************************************************************/




/******************************************************************************************************
******************************************import functon definition*****************************************
*******************************************************************************************************/

/*****************************************************************************
 Function      : IGN_vImpIDHwIgn2IoStatus                                             *
 Description   :get ign2 io status from hw                        *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
/*#if (IGN_Ign2_Used==1)
 uint16 IGN_vImpIDHwIgn2IoStatus(void)
{
	uint16 u16retvalue;
	#if (IGN_RteUsed ==1)
		u16retvalue=HAL_PinRead(IGN_nIGN2Port,IGN_nIGN2Pin);
	#else
		u16retvalue=HAL_PinRead(IGN_nIGN2Port,IGN_nIGN2Pin);
	#endif
	
	return(u16retvalue);
}
#endif*/

/*****************************************************************************
 Function      : IGN_vImpIDHwIgn1IoStatus                                             *
 Description   :get ign1 io status from hw                        *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
/*#if (IGN_Ign1_Used==1)
 uint16 IGN_vImpIDHwIgn1IoStatus(void)
{
	uint16 u16retvalue;
	#if (IGN_RteUsed ==1)
		//u16retvalue=Rte_IRead_Ign_vMain_SysGetIgn1Status();
	#else
		u16retvalue=HAL_PinRead(IGN_nIGN1Port,IGN_nIGN1Pin);
	#endif
	
	return(u16retvalue);
}
#endif*/

/*****************************************************************************
 Function      : IGN_vImpIDRemoteIoStatus                                             *
 Description   :get remote io status from hw                        *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
/*#if (IGN_Ign1_Used==1)
 uint16 IGN_vImpIDRemoteIoStatus(void)
{
	uint16 u16retvalue;
	#if (IGN_RteUsed ==1)
		//u16retvalue=Rte_IRead_Ign_vMain_SysGetIgn1Status();
	#else
		u16retvalue=HAL_PinRead(IGN_nRemoteIoPort,IGN_nRemoteIoPin);
	#endif
	
	return(u16retvalue);
}
#endif*/

/*****************************************************************************
 Function      : IGN_vImpIDAppCrankStatus                                             *
 Description   :get crank status from bus                        *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
#if (IGN_CrankFromBus==1)

 uint16 IGN_vImpIDAppCrankStatus(void)
{
	uint16 u16retvalue;

	#if (IGN_RteUsed ==1)
		//u16retvalue=Rte_IRead_Ign_vMain_SysGetAppCrankStatus();
	#else
		//u16retvalue=CANAPP_u8GetValue(CANAPP_nu8CrankingStatus);
	#endif

    u16retvalue=0;
	
	return(u16retvalue);
}
#endif



/*****************************************************************************
 Function      : IGN_vImpIDAppKeyPos                                             *
 Description   :get key status from bus                        *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
#if (IGN_KeyPosFromBus==1)
 uint16 IGN_vImpIDAppKeyPos(void)
{
    uint16 u16retvalue;
#if (IGN_RteUsed ==1)
    //u16retvalue=Rte_IRead_Ign_vMain_SysGetAppKeyPos();
#else
    u16retvalue= CANAPP_u16GetValue(CanApp_nu16ZAS_Kl_15);
#endif
    if(u16retvalue != 1u)
    {
        u16retvalue = K15_Off;
    }
    else
    {
        u16retvalue = K15_Igon_Running;
    }
    return(u16retvalue);
}
#endif


/*****************************************************************************
 Function      : IGN_vImpIDAppRemoteIo_Status                                             *
 Description   :get remote io status from bus                        *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
#if (IGN_RemoteUsed == 1)
 uint16 IGN_vImpIDAppRemoteIo_Status(void)
{
	uint16 u16retvalue;
	#if (IGN_RteUsed ==1)
		//u16retvalue=Rte_IRead_Ign_vMain_SysGetAppRemoteIo_Status();
	#else
		//u16retvalue=CAPP_u8GetValue(CAPP_RemoteIo_Status);
	#endif
	
	return(u16retvalue);
}
#endif

/******************************************************************************************************
******************************************export functon definition*****************************************
*******************************************************************************************************/


/*****************************************************************************
 Function      : IGN_vExpIDIgnKeyPos                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 IGN_vExpIDIgnKeyPos(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	
	#if (IGN_KeyPosFromBus==1)
		#if(IGN_RteUsed ==1)
			//Rte_IWrite_Ign_vMain_IgnPutKeyPos(IGN_u16Array[IGN_nu16KeyPos]);
		#else
		/*getvalue*/
		#endif
	#endif

	u16retvalue =1;
	return(u16retvalue);
}

/*****************************************************************************
 Function      : IGN_vExpIDIgnOff2OnFlag                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 IGN_vExpIDIgnOff2OnFlag(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	
	#if(IGN_RteUsed ==1)
		//Rte_IWrite_Ign_vMain_IgnOff2OnFlag(IGN_u16Array[IGN_nu16Off2OnFlag]);
	#else
	/*getvalue*/
	#endif

	u16retvalue =1;
	return(u16retvalue);
}

/*****************************************************************************
 Function      : IGN_vExpIDIgnOn2OffFlag                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 IGN_vExpIDIgnOn2OffFlag(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	
	#if(IGN_RteUsed ==1)
		
	#else
	/*getvalue*/
	#endif

	u16retvalue =1;
	return(u16retvalue);
	
}

/*****************************************************************************
 Function      : IGN_vExpIDIgnOff2OnFlag2                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 IGN_vExpIDIgnOff2OnFlag2(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	
	#if(IGN_RteUsed ==1)
		//Rte_IWrite_Ign_vMain_IgnOff2OnFlag(IGN_u16Array[IGN_nu16Off2OnFlag]);
	#else
	/*getvalue*/
	#endif

	u16retvalue =1;
	return(u16retvalue);
}

/*****************************************************************************
 Function      : IGN_vExpIDIgnOn2OffFlag2                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 IGN_vExpIDIgnOn2OffFlag2(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	
	#if(IGN_RteUsed ==1)
		
	#else
	/*getvalue*/
	#endif

	u16retvalue =1;
	return(u16retvalue);
	
}

/*****************************************************************************
 Function      : IGN_vExpIDIgnOff2OnOrLeaveCrankDelayFlag                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 IGN_vExpIDIgnOff2OnOrLeaveCrankDelayFlag(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	
	#if (IGN_CrankFromBus==1)
		#if(IGN_RteUsed ==1)
			//Rte_IWrite_Ign_vMain_IgnPutOff2OnOrLeaveCrankDelayFlag(IGN_u16Array[IGN_nu16Off2OnOrLeaveCrankDelayFlag]);
		#else
		/*getvalue*/
		#endif
	#endif

	u16retvalue =1;
	return(u16retvalue);
}


/*****************************************************************************
 Function      : IGN_vExpIDIgnIGN2IoStatus                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
 uint16  IGN_vExpIDIgnIGN2IoStatus(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	
	#if (IGN_Ign2_Used==1)
	// hardware ign2
		/*use get getvalue not used rte*/
		
	#else
	/*bus: update by output function*/
	/*IGN_u16Array[IGN_nu16IGN2IoStatus]=1;
	IGN_u16Array[IGN_nu16IgnStable]=1;
	IGN_u16Array[IGN_nu16IgnStaticOn]=1;*/
	#endif

	u16retvalue =1;
	return(u16retvalue);
}

/*****************************************************************************
 Function      : IGN_vExpIDIgnIGN2FB                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
 uint16  IGN_vExpIDIgnIGN2FB(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	
	#if (IGN_Ign2_Used==1)
	// hardware ign2
		/*use get getvalue not used rte*/
		
	#else
	/*bus: update by output function*/
	/*IGN_u16Array[IGN_nu16IGN2IoStatus]=1;
	IGN_u16Array[IGN_nu16IgnStable]=1;
	IGN_u16Array[IGN_nu16IgnStaticOn]=1;*/
	#endif

	u16retvalue =1;
	return(u16retvalue);
}

/*****************************************************************************
 Function      : IGN_vExpIDIgnStable                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 IGN_vExpIDIgnStable(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	
	#if(IGN_RteUsed ==1)
		
	#else
	/*getvalue*/
	#endif

	u16retvalue =1;
	return(u16retvalue);
	
}

/*****************************************************************************
 Function      : IGN_vExpIDIgnStaticOn                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 IGN_vExpIDIgnStaticOn(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	
	#if(IGN_RteUsed ==1)
		
	#else
	/*getvalue*/
	#endif

	u16retvalue =1;
	return(u16retvalue);
	
}

/*****************************************************************************
 Function      : IGN_vExpIDIgnSwVersion                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 IGN_vExpIDIgnSwVersion(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	
	#if(IGN_RteUsed ==1)
		
	#else
	/*getvalue*/
	#endif

	u16retvalue =1;
	return(u16retvalue);
	
}

/*****************************************************************************
 Function      : IGN_vExpIDIgnErrorCode                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
static uint16 IGN_vExpIDIgnErrorCode(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	
	#if(IGN_RteUsed ==1)
		
	#else
	/*getvalue*/
	#endif

	u16retvalue =1;
	return(u16retvalue);
	
}

/*****************************************************************************
 Function      : IGN_vExpIDIgnRemoteIoStatus                                             *
 Description   :update the output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
 uint16 IGN_vExpIDIgnRemoteIoStatus(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	
	#if (IGN_RemoteUsed==1)
		#if(IGN_RteUsed ==1)
			//Rte_IWrite_Ign_vMain_IgnPutRemoteIoStatus(IGN_u16Array[IGN_nu16RemoteIoStatus]);
		#else
		/*getvalue*/
		#endif
	#endif
	
	u16retvalue =1;
	return(u16retvalue);
}

/*****************************************************************************
 Function      : IGN_vExpIDAll                                             *
 Description   :update the ALL output  internal data                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
 uint16 IGN_vExpIDAll(void)
{
	uint16 u16retvalue;
	u16retvalue = 0U;
	IGN_vExpIDIgnKeyPos();
	IGN_vExpIDIgnOff2OnFlag();
	IGN_vExpIDIgnOn2OffFlag();
	IGN_vExpIDIgnOff2OnFlag2();
	IGN_vExpIDIgnOn2OffFlag2();
	IGN_vExpIDIgnOff2OnOrLeaveCrankDelayFlag();
	IGN_vExpIDIgnIGN2IoStatus();
	IGN_vExpIDIgnIGN2FB();
	IGN_vExpIDIgnStable();
	IGN_vExpIDIgnStaticOn();
	IGN_vExpIDIgnSwVersion();
	IGN_vExpIDIgnErrorCode();
	IGN_vExpIDIgnRemoteIoStatus();

	u16retvalue = 1U;
	return(u16retvalue);
	
	
}

/* ===========================================================================
* Function   : uint16 IGN_u16GetValue(IGN_tenu16VarNum Num)
* Description: supply variable for other modules.
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/

uint16 IGN_u16GetValue(IGN_tenu16VarNum Num)
{
	uint16 u16Ret=0U;
	
	if(Num<IGN_nu16Max)
	{
		u16Ret=(IGN_u16Array[Num]);
	}
	else
	{
		return(IGN_u16Array[IGN_nu16Max-1]);
	}
	
	return u16Ret;
}

#endif

/******************************************************************************************************
******************************************other functon definition*****************************************
*******************************************************************************************************/


/*****************************************************************************
 Function      : IGN_vSetIDK15Config                                             *
 Description   :config k15 io                          *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
 uint16 IGN_vSetIDK15Config(void)
{
	uint16 u16retvalue;
	u16retvalue = 0;
	/*check if k15 be config by call hal function */
	/*#error "io not config"*/
	return(u16retvalue);
}

#if (IGN_Ign2_Used == 1)
/*****************************************************************************
 Function      : IGN_vGetHwIgn2State                                             *
 Description   :get ign2 io status                       *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
 uint16 IGN_vGetHwIgn2State(void)
{
	uint16 u16retvalue;
	uint16 u16temp;
			
	//MCU_u16PinRead((MUC_enPinID)IGN_nIGN2PortPin,&u8temp);
	Rte_Call_IoHwPortRead_IoHwReadPort_Digital_IgnPort_ReadPort_IgnPort_Read(&u16temp);
	u16retvalue=u16temp;
	
	return(u16retvalue);
}
#endif

#if (IGN_Ign1_Used == 1)
/*****************************************************************************
 Function      : IGN_vGetHwIgn1State                                             *
 Description   :get ign1 io status                        *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
 uint16 IGN_vGetHwIgn1State(void)
{
	uint16 u16retvalue;
	uint8 u8temp;
			
	MCU_u16PinRead((MUC_enPinID)IGN_nIGN1PortPin,&u8temp);		
	u16retvalue=(uint16)u8temp;
	
	return(u16retvalue);
}
#endif

#if (IGN_RemoteUsed==1)
/*****************************************************************************
 Function      : IGN_vGetRemoteIoState                                             *
 Description   :get remote io status                      *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
 uint16 IGN_vGetRemoteIoState(void)
{
	uint16 u16retvalue;
	uint16 u16retvalue;
	uint8 u8temp;
			
	MCU_u16PinRead((MUC_enPinID)IGN_nRemoteIoPortPin,&u8temp);		
	u16retvalue=(uint16)u8temp;
	
	return(u16retvalue);
}
#endif

#if ((IGN_IgnBus_Used==1)||(IGN_KeyPosFromBus==1))
/*****************************************************************************
 Function      : IGN_vGetIgnBusIoState                                             *
 Description   :get ign  io status from bus                      *
 Takes         : None                                              *
 Return Value  : None                                                        *
 Note: 	
*****************************************************************************/
 uint16 IGN_vGetIgnBusIoState(void)
{
	uint16 u16retvalue;
	#if (IGN_IgnBus_Used==1)
		if((CANAPP_u16GetValue(CanApp_nu16ZAS_Kl_15)==1u))
		{
			u16retvalue =1;
		}
		else
		{
			u16retvalue =0;
		}			
	#else
		if(CAPP_u8GetValue(CAPP_ignition_Status)==1)
		{
			u16retvalue =1;
		}
		else
		{
			u16retvalue =0;
		}		    
	#endif

		//u16retvalue=1;
	
	return(u16retvalue);
}
#endif

#if (IGN_CrankFromBus==1)
/*****************************************************************************
 Function      : SYIGN_vCheckCrankBus                                        *
 Description   : crank state check by can bus                             *
 Takes         : None                                                        *
 Return Value  : None                                                        *
*****************************************************************************/
 uint16 IGN_vIFCheckCrankBus(uint8 u8BusCrankStatus)
{	 
	uint8 u8BusCrankValue;	
	uint16 u16ReturnValue;

	u8BusCrankValue = u8BusCrankStatus;
		
	
	if(u8BusCrankValue > Crank_on)
	{
		u16ReturnValue = Crank_off;
	}
	else
	{
		u16ReturnValue	= u8BusCrankValue;
	}

	return(u16ReturnValue);

	
}
#endif

#if (IGN_KeyPosFromBus==1)

/*****************************************************************************
 Function      : IGN_vIFKeyJudge                                        *
 Description   : Ignition state judge.                                       *
Takes         : None                                                        *
 Return Value  : None                                                        *
*****************************************************************************/
 uint16 IGN_vIFKeyJudge(uint8 u8BusKeyPos)
{
	uint16 u16ReturnValue;
	/*read key pos*/
	IGN_u8BusKeyPos = u8BusKeyPos;
	
	switch (IGN_u8BusKeyPos )
	{
		case K15_Unknow:
			 u16ReturnValue=Sys_Off ;
			break;
			
		case K15_Off:
			u16ReturnValue=Sys_Off ;
			break;

		case K15_Acc:
			u16ReturnValue=Sys_Acc ;
			break;		

		case K15_IgOn_Ready:
		case K15_Igon_Running:
			u16ReturnValue=Sys_IgnOn;
			break;

		case K15_Start_Crank:
			if(IGN_biIgnitionBusCrankResult == Crank_off)
			{
				u16ReturnValue=Sys_IdleStart;
			}
			else
			{
				u16ReturnValue=Sys_Crank;
			}
			break;

		case K15_NeverRec:
			u16ReturnValue=Sys_Off ;
			IGN_SetNeverRecK15Msg;
			break;

		case K15_LostNode:
			u16ReturnValue=Sys_Off ;
			IGN_SetLostK15Msg;
			break;

		case K15_Notapplicable:
			
			u16ReturnValue=Sys_Off;
			break;

		case K15_IgAbnormal6:
		case K15_IgAbnormal7:
		case K15_IgAbnormal9:
		case K15_IgAbnormala:
		case K15_IgAbnormalb:
		case K15_IgAbnormalc:
		case K15_IgAbnormald:
		case K15_IgAbnormale:
			u16ReturnValue=Sys_Off;
			IGN_SetAbnormalValue;
			break;	
			

		default:
			u16ReturnValue=Sys_Off;
			break;
	}

	return(u16ReturnValue);

}

/*****************************************************************************
 Function      : IGN_vIFBusLostDet                                        *
 Description   : Ignition error process come from the bus  *
Takes         : None                                                        *
 Return Value  : 1=err,0=no err                                                        *
*****************************************************************************/
 uint16 IGN_vIFBusLostDet(void)
{
	uint16 u16ReturnValue;
	if((IGN_u8BusKeyPos==K15_LostNode)||(IGN_u8BusKeyPos==K15_NeverRec))
	{
		u16ReturnValue=1;
	}
	else
	{
		u16ReturnValue=0;
	}
	return(u16ReturnValue);
}

/*****************************************************************************
 Function      : IGN_vIFBusErrPro                                        *
 Description   : Ignition error process come from the bus  *
Takes         : None                                                        *
 Return Value  : 1=err,0=no err                                                            *
*****************************************************************************/
 uint16 IGN_vIFBusErrPro(uint8 u8BusKeyPos)
{
	uint16 u16ReturnValue;
	/*read key pos*/
	IGN_u8BusKeyPos = u8BusKeyPos;
	
	/*------------clr error code------------*/
	if(IGN_u8BusKeyPos!=K15_NeverRec)
	{
		IGN_ClrNeverRecK15Msg;
	}

	if(IGN_u8BusKeyPos!=K15_LostNode)
	{
		IGN_ClrLostK15Msg;
	}

	if((IGN_u8BusKeyPos!=K15_IgAbnormal6)&&(IGN_u8BusKeyPos!=K15_IgAbnormal7)&&(IGN_u8BusKeyPos!=K15_IgAbnormal9)\
		&&(IGN_u8BusKeyPos!=K15_IgAbnormala)&&(IGN_u8BusKeyPos!=K15_IgAbnormalb)&&(IGN_u8BusKeyPos!=K15_IgAbnormalc)\
		&&(IGN_u8BusKeyPos!=K15_IgAbnormald)&&(IGN_u8BusKeyPos!=K15_IgAbnormale))
	{
		IGN_ClrAbnormalValue;
	}

	/* lost bus then use hardware line */
	u16ReturnValue=IGN_vIFBusLostDet();
	
	return(u16ReturnValue);
	
}

#endif

#if (IGN_CheckIgnLostUsed ==1)
/* =======================================================
* Function   	: uint16 IGN_vK15LostDet(void)
* Description	: check the hardware k15  per 10ms 
* Takes      	: Nothing
* Returns    	: Nothing
*/
 uint16 IGN_vIFK15IOLostDet(uint8 u8BusKeyPos)
{
	uint16 u16returnvalue;
	/*read key pos*/
	IGN_u8BusKeyPos = u8BusKeyPos;
	
	if((IGN_u8BusKeyPos==K15_IgOn_Ready)||(IGN_u8BusKeyPos==K15_Igon_Running))
	{	/*lost k15*/
		u16returnvalue=1;
	
	}
	else
	{
		u16returnvalue=0;
	}
}
#endif

#if (IGN_Ign2Fb_Used==1)
/* =======================================================
* Function   	: uint16 IGN_vIFK15FBDet(void)
* Description	: check the hardware k15  voltage 
* Takes      	: Nothing
* Returns    	: Nothing
*/
 uint16 IGN_vIFK15FBDet(void)
{
	uint16 u16returnvalue;
	/*read k15 feedback*/
	u16returnvalue = HAL_u16AdcGet(IGN_nRawIGN2Fb);
	
	u16returnvalue=IGN_SupplyVot_10Times(u16returnvalue);
	
	return(u16returnvalue);
	
}
#endif



/*****************************************************************************
* EOF: IGN_IF.c
*****************************************************************************/

