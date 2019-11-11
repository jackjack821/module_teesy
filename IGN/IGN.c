/*******************************************************************************
| Module Name: KL15 detection model
| File Name: IGN.C
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
|Li Ning					 Desay SV Automotive Co., Ltd|
|-------------------------------------------------------------------------------
|				R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date			   Ver			Author				 Description
| ----------  -------  -------------  -------------------------------------------------
| 
|2015.9.2       a2.2             Li Ning		the first version for integration

********************************************************************************/
#ifndef IGN_C
#define IGN_C

/* System-headerfiles */


/* Foreign headerfiles */


/* Own headerfiles */


#include "Ign_if.h"
#include "Ign_cfg.h"
#include "Ign.h"

#include "frame.h"


#if (IGN_RemoteUsed==1)
	static uint8 IGN_biRemoteIoStable;
	static uint8 IGN_biRemoteIoStaticOn;
	static uint8 IGN_u8RemoteIoNotStableFlag;	
#endif



/*time parameter for hardware line */
static uint8 IGN_u8DebounceOnTime;
static uint8 IGN_u8DebounceOffTime;
static uint8 IGN_u8NotStableTime;		/* for hardware line */

/*first  delay time*/
static uint8 IGN_u8ClientDebounceOn2OffTime;
static uint8 IGN_u8ClientDebounceOff2OnTime;

/*second delay time if you need*/
static uint8 IGN_u8ClientDebounceOn2OffTime2;
static uint8 IGN_u8ClientDebounceOff2OnTime2;
#if (IGN_CrankFromBus==1)
	static uint8 IGN_u8ClientLeaveCrankBusDelayTime;
#endif

			

/*key position be processed with the logic offered by the client */

/*record keypos value temporarily*/
#if (IGN_KeyPosFromBus==1)
	static uint8 IGN_u8SysKeyPosTemp;	
#endif




/*hardware k15 lost detect */
#if (IGN_CheckIgnLostUsed ==1)
	static uint16 IGN_u16LostK15IOCounter;
#endif


/*interface data buffer definition*/
#if (IGN_CrankFromBus==1)
	static uint8 IGN_u8IDBusCrankState;
#endif

#if (IGN_KeyPosFromBus ==1)
	static uint8 IGN_u8IDBusKeyPos;
#endif

#if (IGN_RemoteUsed ==1)
	static uint8 IGN_u8IDRemoteIoStatus;
#endif

/*interanl data buffer definition*/
#if (IGN_KeyPosFromBus ==1)
	static uint16 IGN_u16InternalKeyPos;
#endif
static uint16 IGN_u16InternalDataOff2OnFlag;
static uint16 IGN_u16InternalDataOn2OffFlag;
static uint16 IGN_u16InternalDataOff2OnFlag2;
static uint16 IGN_u16InternalDataOn2OffFlag2;
#if (IGN_CrankFromBus==1)
	static uint16 IGN_u16InternalDataOff2OnOrLeaveCrankDelayFlag;
#endif

static uint16 IGN_u16InternalDataIGN2IoStatus;	// ign2 and bus
#if (IGN_Ign2Fb_Used == 1)
static uint16 IGN_u16InternalDataIGN2Fb;
#endif
#if (IGN_Ign1_Used == 1)
static uint16 IGN_u16InternalDataIGN1IoStatus;
static uint16 IGN_u16InternalDataIGN1Fb;
#endif
static uint16 IGN_u16InternalDataIgnStable;
static uint16 IGN_u16InternalDataIgnStaticOn;
static uint16 IGN_u16InternalDataSwVersion;
//static uint16 IGN_u16InternalDataErrorCode;
#if (IGN_RemoteUsed ==1)
	static uint16 IGN_u16InternalDataRemoteIoStatus;
#endif
static uint16 IGN_u16InternalDataSysIgnStatus;




static  void IGN_vCheckSysIgnEvent(void);
static   void IGN_vSysDebounce(void);
static void IGN_vDebounceClient(void);
static void IGN_vDebounce(void);
static uint16  IGN_vSysIgnCheck(void);
#if (IGN_CheckIgnLostUsed==1)
static void IGN_vK15IOLostDet(void);
#endif



/* ===========================================================================
* Function   : static uint8 IGN_vHmiDataReset(void)
* Description: this function be call when k30 turn on from off state thant mcu can work normally.
* Input      : none.
* Returns    : none.
*/

static uint8  IGN_vHmiDataReset(void)
{
	uint8 u8retvalue;
	u8retvalue =0U;
	/* set the default output value for uint16 */
	#if (IGN_KeyPosFromBus==1)
		clr_bIgnInternalKeyPos();
	#endif

	clr_bIgnInternalDataOff2OnFlag();

	clr_bIgnInternalDataOn2OffFlag();

	#if (IGN_CrankFromBus==1)
		clr_bIgnInternalDataOff2OnOrLeaveCrankDelayFlag();	
	#endif	

	
	clr_bIgnInternalDataIGN2IoStatus();		// ign2 and bus
	#if (IGN_Ign2Fb_Used==1)
	clr_bIgnInternalDataIGN2Fb();	
	#endif

	#if (IGN_Ign1_Used==1)
	clr_bIgnInternalDataIGN1IoStatus() ;	
	clr_bIgnInternalDataIGN1Fb();	
	#endif

	clr_bIgnInternalDataIgnStable();
	
	clr_bIgnInternalDataIgnStaticOn();

	clr_bIgnInternalDataSysIgnStatus();		/*io of sys ign*/

	#if (IGN_Ign2_Used == 1)
		clr_bIgnInternalDataIGN2IoStatus();		/*io of  ign2 by hardware*/
	#endif

	#if (IGN_RemoteUsed ==1)
	clr_bIgnInternalDataRemoteIoStatus();		/*io of  ign2 by hardware*/
	#endif

	set_bIgnInternalDataSwVersion(0x0400U);	
	
	clr_bIgnInternalDataErrorCode(0x0000U);

	#if (IGN_RemoteUsed==1)
		clr_bIgnInternalDataRemoteIoStatus();
	#endif

	u8retvalue =1U;
	return (u8retvalue);
}



/* ===========================================================================
* Function   : uint8 IGN_vIDInputUpdate()
* Description: update the interface date of input.
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/

static uint8 IGN_vIDInputUpdate(void)
{
	uint8 u8retvalue;	
	u8retvalue = 0U;
	
	#if (IGN_CrankFromBus==1)
	IGN_u8IDBusCrankState	= IGN_vImpIDAppCrankStatus();
	#endif

	#if (IGN_KeyPosFromBus==1)
		IGN_u8IDBusKeyPos		=  IGN_vImpIDAppKeyPos();
	#endif
	
	#if (IGN_RemoteUsed == 1)
		IGN_u8IDRemoteIoStatus	 = IGN_vImpIDAppRemoteIo_Status();
	#endif
	u8retvalue =1U;
	return (u8retvalue);
		
}

/* ===========================================================================
* Function   : uint8 IGN_vIDOutputUpdate()
* Description: update the interface date of output.
* Input      : the variable number which other module want to get.
* Returns    : the varible value which other module want to get.
*/

static uint16 IGN_vIDOutputUpdate(void)
{
	uint16 u16retvalue;
	u16retvalue = 0U;

	/*update output of my module*/
	#if (IGN_KeyPosFromBus==1)
		IGN_u16Array[IGN_nu16KeyPos]	 		=  get_bIgnInternalKeyPos();	
	#endif

	IGN_u16Array[IGN_nu16Off2OnFlag] 			=  get_bIgnInternalDataOff2OnFlag();
	
	IGN_u16Array[IGN_nu16On2OffFlag] 			=  get_bIgnInternalDataOn2OffFlag();

	IGN_u16Array[IGN_nu16Off2OnFlag2] 			=  get_bIgnInternalDataOff2OnFlag2();
	
	IGN_u16Array[IGN_nu16On2OffFlag2] 			=  get_bIgnInternalDataOn2OffFlag2();

	#if (IGN_CrankFromBus==1)
	IGN_u16Array[IGN_nu16Off2OnOrLeaveCrankDelayFlag] 	=  get_bIgnInternalDataOff2OnOrLeaveCrankDelayFlag();	
	#endif	

	#if (IGN_Ign2_Used==1)
	set_bIgnInternalDataIGN2IoStatus(IGN_vGetHwIgn2State());
	IGN_u16Array[IGN_nu16IGN2IoStatus] 		= get_bIgnInternalDataIGN2IoStatus() ;
	#endif

	#if(IGN_Ign2Fb_Used==1)
	IGN_u16Array[IGN_nu16IGN2Fb]			= IGN_vIFK15FBDet();
	#endif
	
	#if (IGN_Ign1_Used==1)
	set_bIgnInternalDataIGN1IoStatus(IGN_vGetHwIgn1State()) ;
	IGN_u16Array[IGN_nu16IGN1IoStatus] 		= get_bIgnInternalDataIGN1IoStatus() ;
	
	set_bIgnInternalDataIGN1Fb( HAL_u16AdcGet(IGN_nRawIGN1Fb));
	IGN_u16Array[IGN_nu16IGN1Fb]			= get_bIgnInternalDataIGN1Fb();  
	#endif
		
	IGN_u16Array[IGN_nu16IgnStable] 			= True;//get_bIgnInternalDataIgnStable(); /*GET ONLY.190419*/
	
	IGN_u16Array[IGN_nu16IgnStaticOn] 		= True;//get_bIgnInternalDataIgnStaticOn(); /*GET ONLY.190419*/

	IGN_u16Array[IGN_nu16SwVersion]			= get_bIgnInternalDataSwVersion();	
	
	IGN_u16Array[IGN_nu16ErrorCode]			= get_bIgnInternalDataErrorCode();

	#if (IGN_RemoteUsed==1)
		IGN_u16Array[IGN_nu16RemoteIoStatus]	= get_bIgnInternalDataRemoteIoStatus();
	#endif

	
	/*update output use by other module*/		
	IGN_vExpIDAll();

	u16retvalue =1U;
	return (u16retvalue);
}



#if (IGN_CheckIgnLostUsed ==1)
/* =======================================================
* Function   	: void IGN_vK15LostDet(void)
* Description	: check the hardware k15  per 10ms 
* Takes      	: Nothing
* Returns    	: Nothing
*/
static void IGN_vK15IOLostDet(void)
{	
	if(IGN_vIFK15IOLostDet( IGN_u8IDBusKeyPos)==1)
	{
		if(get_bIgnInternalDataIGN2IoStatus()==False)
		{
			if(IGN_u16LostK15IOCounter>0)
			{
				IGN_u16LostK15IOCounter--;
			}
			
			if(IGN_u16LostK15IOCounter==0)
			{
				IGN_SetLostK15IO;
			}
		}
		else
		{
			IGN_ClrLostK15IO;
			IGN_u16LostK15IOCounter = 	IGN_LostK15IOTimeCfg;
		}
	}
	else
	{
		IGN_ClrLostK15IO;
		IGN_u16LostK15IOCounter = 	IGN_LostK15IOTimeCfg;
	}
}
#endif


#if (IGN_CrankFromBus==1)
/*****************************************************************************
 Function      : SYIGN_vCheckCrankBus                                        *
 Description   : crank state check by can bus                             *
 Takes         : None                                                        *
 Return Value  : None                                                        *
*****************************************************************************/
 void IGN_vCheckCrankBus(void)
{
	IGN_biIgnitionBusCrankResult=IGN_vIFCheckCrankBus(IGN_u8IDBusCrankState);

}
#endif

#if (IGN_KeyPosFromBus==1)

/*****************************************************************************
 Function      : IGN_vKeyJudge                                        *
 Description   : Ignition state judge.                                       *
Takes         : None                                                        *
 Return Value  : None                                                        *
*****************************************************************************/
 void IGN_vKeyJudge(void)
{
	set_bIgnInternalKeyPos(IGN_vIFKeyJudge(IGN_u8IDBusKeyPos));	

}


/*****************************************************************************
 Function      : IGN_vBusErrPro                                        *
 Description   : Ignition error process come from the bus  *
Takes         : None                                                        *
 Return Value  : None                                                        *
*****************************************************************************/
 void IGN_vBusErrPro(void)
{

	/*check k15 and record err */
	if(IGN_vIFBusErrPro(IGN_u8IDBusKeyPos)==1)
	{
		/*lost bus then use hardware line */
		if((get_bIgnInternalDataIgnStaticOn()==1)&&(get_bIgnInternalDataIgnStable()==1))
		{
			set_bIgnInternalKeyPos(Sys_IgnOn);
		}
	}
	
}

#endif







/*****************************************************************************
 Function      : SYIGN_vCheckIgn2Event                                        *
 Description   : Ignition state check by hardware                             *                                                                          
 Takes         : None                                                        *
 Return Value  : None                                                        *
*****************************************************************************/
static void IGN_vCheckSysIgnEvent(void)
{
	uint8 boPinLevel;			/*use for final ign state*/
	uint8 boIgn2PinLevel;		/*use for  ign2 state by hardware*/
	#if ((IGN_IgnBus_Used==1)||(IGN_KeyPosFromBus==1))
		uint8 boIgn2BusLevel;	/*use for  ign state by bus*/
	#endif

	#if (IGN_RemoteUsed==1)
		uint8 boRemoteIoLevel;	/*use for  remote state*/
	#endif


	/*-------------------------read ign state---------------*/
	/*read ign2 by hardware*/
	#if (IGN_Ign2_Used == 1)
		boIgn2PinLevel=IGN_vGetHwIgn2State();
	#else
		/*avoid for warning*/
		boIgn2PinLevel = 0;
		boIgn2PinLevel = boIgn2PinLevel;
	#endif

	/*read ig2 from bus*/
	#if ((IGN_IgnBus_Used==1)||(IGN_KeyPosFromBus==1))
		
		if(IGN_vGetIgnBusIoState())
		{
			boIgn2BusLevel =1;	
		}
		else
		{
			boIgn2BusLevel =0;
		}
	#endif

	/*read remote io*/
	#if (IGN_RemoteUsed==1)
		boRemoteIoLevel=IGN_vGetRemoteIoState();
	#endif

	/*--------------------judge IGN--------------------*/
	if((0)
	#if(IGN_Ign2_Used==1)
		||(boIgn2PinLevel==1)				/*ign2 by hardware*/
	#endif
	#if ((IGN_IgnBus_Used==1)||(IGN_KeyPosFromBus==1))
		||(boIgn2BusLevel==1)		/*ign2 by bus*/
	#endif
	#if (IGN_RemoteUsed==1)
		||(boRemoteIoLevel==1)	/*remote io by hardware*/
	#endif
	)
	{
		boPinLevel = 1;
	}
	else
	{
		boPinLevel = 0;
	}

	/*-------------------- status update-------------------*/
	/*update ign2 by hardware*/
	if( get_bIgnInternalDataIGN2IoStatus() != boIgn2PinLevel )
	{		
		set_bIgnInternalDataIGN2IoStatus(boIgn2PinLevel);		/*use for ign2 lost */			
		
	}

	/*update ign2 by bus*/
	//not used

	#if (IGN_RemoteUsed==1)
	/*update remote io by hardware*/	
	if( get_bIgnInternalDataRemoteIoStatus() != boRemoteIoLevel )
	{		
		set_bIgnInternalDataRemoteIoStatus(boRemoteIoLevel);		/*use for remote io lost */			
		
	}
	#endif
	
	/*update sys ign status*/
	if( get_bIgnInternalDataSysIgnStatus() != boPinLevel )
	{		
		set_bIgnInternalDataSysIgnStatus(boPinLevel);
		clr_bIgnInternalDataIgnStable();	
		IGN_u8NotStableTime = IGN_u8NotStableTimeCfg;				
		
	}
	
	else
	{
		
	}
      
	
}

/*****************************************************************************
 Function      : SYIGN_ifIgn2ExternInterrupt                                     *
 Description   : Use INTP for detecting the state of Ignition.          *
                      This is an interrupt service function.                      *
 Takes         :    None                                                        *
 Return Value  : None                                                        *
*****************************************************************************/
void IGN_ifIgn2ExternInterrupt(void)
{
	#if (IGN_Ign2_Used == 1)
		uint8 boPinLevel;
		
		boPinLevel=IGN_vGetHwIgn2State();

		if ( get_bIgnInternalDataSysIgnStatus() != boPinLevel )
		{
			set_bIgnInternalDataIGN2IoStatus(boPinLevel);
			set_bIgnInternalDataSysIgnStatus(boPinLevel);
			clr_bIgnInternalDataIgnStable();
			IGN_u8NotStableTime = IGN_u8NotStableTimeCfg;
			/*must update date immediately*/
			#if (IGN_RteUsed ==1)
				IGN_u16Array[IGN_nu16IGN2IoStatus] = get_bIgnInternalDataIGN2IoStatus() ;
				/*not use rte */
				//IGN_vExpIDIgnIGN2IoStatus();/*rte update function */
			#else
				IGN_u16Array[IGN_nu16IGN2IoStatus] = get_bIgnInternalDataIGN2IoStatus() ;
			#endif
			

		}
		
	#endif
}


/*****************************************************************************
 Function      : IGN_ifRemoteExternInterrupt                                     *
 Description   : Use INTP for detecting the state of Ignition.          *
                      This is an interrupt service function.                      *
 Takes         :    None                                                        *
 Return Value  : None                                                        *
*****************************************************************************/
void IGN_ifRemoteExternInterrupt(void)
{
	#if (IGN_RemoteUsed==1)
		uint8 boPinLevel;
		
		asm("DI");
		boPinLevel=IGN_vGetRemoteIoState();

		if ( get_bIgnInternalDataSysIgnStatus() != boPinLevel )
		{
			set_bIgnInternalDataRemoteIoStatus(boPinLevel);
			set_bIgnInternalDataSysIgnStatus(boPinLevel);
			clr_bIgnInternalDataIgnStable();
			IGN_u8NotStableTime = IGN_u8NotStableTimeCfg;
			/*must update date immediately*/
			#if (IGN_RteUsed ==1)
				IGN_u16Array[IGN_nu16RemoteIoStatus] = get_bIgnInternalDataRemoteIoStatus() ;
				IGN_vExpIDIgnRemoteIoStatus();/*rte update function */
			#else
				IGN_u16Array[IGN_nu16RemoteIoStatus] = get_bIgnInternalDataRemoteIoStatus() ;
			#endif
			

		}
		
		asm("EI");

	#endif	
}




/*****************************************************************************
 Function       : IGN_vSysDebounceSys                                       *
 Description   : Ignition stable debounce.                               *
                     Run every 10ms.                                            *
 Takes           : None                                                            *
 Return Value : None                                                            *
*****************************************************************************/

static void IGN_vSysDebounce(void)
{
	/*manage ignition detected by int1 or poll*/
	if ( get_bIgnInternalDataSysIgnStatus() == 1 )			/* io ignition on*/
	{			
		if (IGN_u8DebounceOnTime > (uint8)0)
		{
			--IGN_u8DebounceOnTime;
			IGN_u8DebounceOffTime = IGN_u8DebounceOffTimeCfg;
		}
		else
		{
			set_bIgnInternalDataIgnStaticOn(1);
		}
	}
	
	else										/* ignition off*/
	{
		if (IGN_u8DebounceOffTime > (uint8)0)
		{
			--IGN_u8DebounceOffTime;
			IGN_u8DebounceOnTime = IGN_u8DebounceOnTimeCfg;
		}
		else
		{
			clr_bIgnInternalDataIgnStaticOn();
		}			
	}

	if (IGN_u8NotStableTime > (uint8)0)			/* filter ignition detected by interrupt or ignition reset*/
	{
		--IGN_u8NotStableTime;		/*system state is changing.*/			
	}
	else
	{
		set_bIgnInternalDataIgnStable(1);
	}

				
	
}

/*****************************************************************************
 Function      : IGN_vDebounceExt                                             *
 Description   : Ignition state check for extern module.                                       *
                 Run every 10ms.                                            *
 Takes         : None                                                        *
 Return Value  : None                                                        *
*****************************************************************************/

static void IGN_vDebounceExt(void)
{
	/* ignition on to off*/
	//if(( get_bIgnInternalDataIgnStable() == 1 ) &&(get_bIgnInternalDataIgnStaticOn() == False))
	 if( get_bIgnInternalDataSysIgnStatus() == False )
	{
		if (IGN_u8ClientDebounceOn2OffTime > 0)
		{
			--IGN_u8ClientDebounceOn2OffTime;
			IGN_u8ClientDebounceOff2OnTime = IGN_u8ClientOff2OnCfg;
			clr_bIgnInternalDataOn2OffFlag();
		}
		else
		{
                  
			set_bIgnInternalDataOn2OffFlag(1);
			clr_bIgnInternalDataOff2OnFlag();
		}	
		
	}
	/*ignition off to on*/
	//else if(( get_bIgnInternalDataIgnStable() == 1 ) &&(get_bIgnInternalDataIgnStaticOn() == 1))
	else if( get_bIgnInternalDataSysIgnStatus() == 1 )		 
	{			
		if (IGN_u8ClientDebounceOff2OnTime > 0)
		{
			--IGN_u8ClientDebounceOff2OnTime;
			IGN_u8ClientDebounceOn2OffTime = IGN_u8ClientOn2OffCfg;
			clr_bIgnInternalDataOff2OnFlag();
		}
		else
		{
			set_bIgnInternalDataOff2OnFlag(1);
			clr_bIgnInternalDataOn2OffFlag();
		}
		
	}
	
	else
	{
		// do nothing
	}
	
}

/*****************************************************************************
 Function      : IGN_vDebounceExt2                                             *
 Description   : Ignition state check for extern module.                                       *
                 Run every 10ms.                                            *
 Takes         : None                                                        *
 Return Value  : None                                                        *
*****************************************************************************/

static void IGN_vDebounceExt2(void)
{
	/* ignition on to off*/
	//if(( get_bIgnInternalDataIgnStable() == 1 ) &&(get_bIgnInternalDataIgnStaticOn() == False))
	 if( get_bIgnInternalDataSysIgnStatus() == False )
	{
		if (IGN_u8ClientDebounceOn2OffTime2 > 0)
		{
			--IGN_u8ClientDebounceOn2OffTime2;
			IGN_u8ClientDebounceOff2OnTime2 = IGN_u8ClientOff2OnCfg2;
			clr_bIgnInternalDataOn2OffFlag2();
		}
		else
		{
                  
			set_bIgnInternalDataOn2OffFlag2(1);
			clr_bIgnInternalDataOff2OnFlag2();
		}	
		
	}
	/*ignition off to on*/
	//else if(( get_bIgnInternalDataIgnStable() == 1 ) &&(get_bIgnInternalDataIgnStaticOn() == 1))
	else if( get_bIgnInternalDataSysIgnStatus() == 1 )		 
	{			
		if (IGN_u8ClientDebounceOff2OnTime2 > 0)
		{
			--IGN_u8ClientDebounceOff2OnTime2;
			IGN_u8ClientDebounceOn2OffTime2 = IGN_u8ClientOn2OffCfg2;
			clr_bIgnInternalDataOff2OnFlag2();
		}
		else
		{
			set_bIgnInternalDataOff2OnFlag2(1);
			clr_bIgnInternalDataOn2OffFlag2();
		}
		
	}
	
	else
	{
		// do nothing
	}
	
}


/*****************************************************************************
 Function      : IGN_vClientDebounce                                             *
 Description   : Ignition state check.                                       *
                 Run every 10ms.                                            *
 Takes         : None                                                        *
 Return Value  : None                                                        *
*****************************************************************************/

static void IGN_vDebounceClient(void)
{
	
	#if (IGN_KeyPosFromBus==1)
	
		/* crank delay process */
		if(get_bIgnInternalKeyPos() == Sys_Crank)
		{
			IGN_u8SysKeyPosTemp = get_bIgnInternalKeyPos();
			IGN_u8ClientLeaveCrankBusDelayTime = IGN_u8ClientOff2OnCfg;
			clr_bIgnInternalDataOff2OnOrLeaveCrankDelayFlag();
		}

		if((IGN_u8SysKeyPosTemp == Sys_Crank )&&(get_bIgnInternalKeyPos()!=Sys_Crank))
		{
			if(IGN_u8ClientLeaveCrankBusDelayTime>0)
			{
				IGN_u8ClientLeaveCrankBusDelayTime--;
			}
			else
			{
				IGN_u8SysKeyPosTemp = get_bIgnInternalKeyPos();
				set_bIgnInternalDataOff2OnOrLeaveCrankDelayFlag(1);
			}
		}
		else
		{
			//IGN_u8ClientLeaveCrankBusDelayTime = IGN_u8ClientOff2OnCfg;
			//IGN_u8LeaveCrankBusDelay = False;
		}

		/*lost bus then use hardware k15*/	
		if(IGN_vIFBusLostDet()==1)
		{
			set_bIgnInternalDataOff2OnOrLeaveCrankDelayFlag(get_bIgnInternalDataOff2OnFlag());
		}	
		else
		{
			//do nothing
		}
	
	#else
		/*not use ign_bus,then use hardware k15*/
	#endif

	
}

/*****************************************************************************
 Function      : IGN_vDebounce                                             *
 Description   : Ignition line debouce for os state                                        *
                 Run every 10ms.                                            *
 Takes         : None                                                        *
 Return Value  : None                                                        *
 Note: 	this function be call by os then the some varible can be used by app
*****************************************************************************/

static void IGN_vDebounce(void)
{
	/*sys io debounce*/
	IGN_vSysDebounce();	
		
	/*delay with system k15 line for extern module*/
	IGN_vDebounceExt();
	IGN_vDebounceExt2();

	/*delay with client par for extern module*/
	IGN_vDebounceClient();
	
	
}

/* =======================================================
* Function   	: uint16 IGN_vSysIgnCheck(void)
* Description	: must run one time  per 10ms 
* Takes      	: Nothing
* Returns    	: Nothing
*/
static uint16 IGN_vSysIgnCheck(void)
{	
	uint16 u16temp;
	u16temp =0U;
	/*read sys ign state */
	IGN_vCheckSysIgnEvent();

	#if (IGN_CrankFromBus==1)	
	/*read crank status from can bus*/
	IGN_vCheckCrankBus();
	#endif

	/*read k15 line status from can bus*/
	#if (IGN_KeyPosFromBus==1)
		
		/* accord the bus signal to confirm key postion used by app */
		IGN_vKeyJudge();

		/*k15 received from the bus error process */
		IGN_vBusErrPro();		
	#endif
	

	u16temp = 1U;
	return (u16temp);

	
	
}

/* ===========================================================================
* Function   : void IGN_vReset(void)
* Description:this function be call when k30 turn on from off state thant mcu can work normally.
* Input      : none.
* Returns    : none.
*/
void IGN_vReset(void)
{
	/*  the temporary variable reset*/
	IGN_vHmiDataReset();

	/*set the default value of the debounce counter*/
	IGN_u8DebounceOnTime 	= IGN_u8DebounceOnTimeCfg;
	IGN_u8DebounceOffTime 	= IGN_u8DebounceOffTimeCfg;
	IGN_u8NotStableTime	= IGN_u8NotStableTimeCfg;
	#if (IGN_CheckIgnLostUsed == 1)
		IGN_u16LostK15IOCounter = 	IGN_LostK15IOTimeCfg;
	#endif
	IGN_u8ClientDebounceOff2OnTime = IGN_u8ClientOff2OnCfg;
	IGN_u8ClientDebounceOn2OffTime = IGN_u8ClientOn2OffCfg;

	IGN_u8ClientDebounceOff2OnTime2 = IGN_u8ClientOff2OnCfg2;
	IGN_u8ClientDebounceOn2OffTime2 = IGN_u8ClientOn2OffCfg2;
	
	/* k15 input pin reset in mcu cfg.c*/
	IGN_vSetIDK15Config();

	
	#if (IGN_KeyPosFromBus==1)
	IGN_biIgnitionBusCrankResult	= False;
	IGN_u8BusKeyPos		= 0x00U; 	
	IGN_u8SysKeyPosTemp	=0x00U;
	#endif

	
	
	/*update output data*/
	IGN_vIDOutputUpdate();

}

/* ===========================================================================
* Function   : void IGN_vInit(void)
* Description: this function be call when k15 turn on from off.
* Input      : none.
* Returns    : none.
*/
void IGN_vInit(void)
{
	#if (IGN_CrankFromBus==1)
		clr_bIgnInternalDataOff2OnOrLeaveCrankDelayFlag();
	#endif
	
}	

/* ===========================================================================
* Function   : void IGN_vInit(void)
* Description: this function be call when k15 turn off from on.
* Input      : none.
* Returns    : none.
*/
void IGN_vDeinit(void)
{	

}

/* ===========================================================================
* Function   : void IGN_vWakeUp(void)
* Description: this function be call when the system wake up.
* Input      : none.
* Returns    : none.
*/
void IGN_vWakeUp(void)
{
	
}




/* =======================================================
* Function   	: void IGN_vMain(void)
* Description	: must run one time  per 10ms 
* Takes      	: Nothing
* Returns    	: Nothing
*/
void IGN_vMain(void)
{
	//uint16 u16temp;
	//u16temp = 0U;

	/*update interface data*/
	
	/*update internal data*/
	IGN_vIDInputUpdate();
	
	IGN_vSysIgnCheck();
	
	IGN_vDebounce();
	
	#if (IGN_CheckIgnLostUsed==1)
	IGN_vK15IOLostDet();
	#endif

	IGN_vIDOutputUpdate();
	
	//u16temp = 1U;
	//return (u16temp);
	
}





#endif

/*****************************************************************************
* EOF:
******************************************************************************/

