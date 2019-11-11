/*******************************************************************************
| Module Name: Seat Heat Control
| File Name: SHC.c
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
| Luo Xindian                             Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 1/23/2016    1.0  Luo Xindian		  this module for new seat heating modules development
|9/1/2016	1.1	 Luo Xindian		change for FE-5A7A
********************************************************************************/

#define SHC                       /* name of the module                */


/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* system-headerfiles */
#include "General.h"

/* foreign headerfiles */
#include "MMI.h"
#include "Rte_internal.h"
/* own headerfiles */
#include "SHC.h"
#include "SHC_Cfg.h"
#include "SHC_Private.h" 
#include "SHC_Type.h"


/**************************** .BLOCK_COMMENT_BEGIN ***************************
* GLOBAL DEFINITIONS
*
* In this section define
* - all global ROM-constants of your module
* - all global variables of your module
***************************** .BLOCK_COMMENT_END *****************************/



/**************************** .BLOCK_COMMENT_BEGIN ***************************
* FILE LOCAL DEFINITIONS
*
* In this section define
* - all file local macros
* - all file local define-constants
* - all file local type definitions
* - all file local ROM-constants
* - all file local variables
***************************** .BLOCK_COMMENT_END *****************************/
/* internal static variable definition */
static SHC_tstInputLists SHC_stInputLists;
static uint8 SHC_au8Array[SHC_nMax];
static uint8 SHC_au8RFeedBackCnt;
static uint8 SHC_au8LFeedBackCnt;

static void SHC_vInputValueProcess(void);
static void SHC_vSeatHeatReq(void);
static void SHC_vSeatHeatDisp(void);
static void SHC_vSeatHeatReqOutPut(void);

#if (SHC_nUseCcp == True)
static uint8     SHC_CcpForceFlag = 0U;
static uint16    SHC_CcpControlData[SHC_nCcpForceMax] = {0U,0U};

static void SHC_vCcpOutputForce(void);
#endif

#if(SHC_nUseRte == True)
static void SHC_vUpdatedRte(void);
#endif
/*****************************************************************************
 Function      : SHC_vReset                                                  *
 Description   : Initialises the seat heat module
                 Initialises the SHC modle                            *
 Return Value  : None                                                        *
*****************************************************************************/
void SHC_vReset( void)
{
	SHC_u8Valid=0;
	SHC_u8SwVersion=0xA0;
	
	SHC_u8ErrorCode=0;
	SHC_u8LastStateDr=0;
	SHC_u8LastStatePs=0;
	SHC_u8DisplayDr=SHC_nHeatSeatOff;
	SHC_u8DisplayPs=SHC_nHeatSeatOff;
	SHC_u8LeftSeatHeatCtrlTimer =0;
	SHC_u8RightSeatHeatCtrlTimer=0;

    SHC_au8RFeedBackCnt = 0u;
    SHC_au8LFeedBackCnt = 0u;

    Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_SHCL_Write(0u);
    Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_SHCR_Write(0u);
}


/*****************************************************************************
 Function      : SHC_vDeinit                                          *
 Description   : de-init the system when KL15 Off 			                     *
 Return Value  : None                                                        *
*****************************************************************************/
void SHC_vDeinit( void)
{
	SHC_u8Valid=0;
	SHC_u8ErrorCode=0;
	SHC_u8LastStateDr=0;
	SHC_u8LastStatePs=0;
	SHC_u8DisplayDr=SHC_nHeatSeatOff;
	SHC_u8DisplayPs=SHC_nHeatSeatOff;
	SHC_u8LeftSeatHeatCtrlTimer =0;
	SHC_u8RightSeatHeatCtrlTimer=0;

    SHCClrCcpForceByte();
}

/*****************************************************************************
 Function      : SHC_vInit                                          *
 Description   : Initialise the seat heat module       *
 Return Value  : None                                                        *
*****************************************************************************/
void SHC_vInit( void)
{	
	SHC_u8Valid=0;
	SHC_u8ErrorCode=0;
	SHC_u8LastStateDr=0;
	SHC_u8LastStatePs=0;
	SHC_u8DisplayDr=SHC_nHeatSeatOff;
	SHC_u8DisplayPs=SHC_nHeatSeatOff;
	SHC_u8LeftSeatHeatCtrlTimer =0;
	SHC_u8RightSeatHeatCtrlTimer=0;

    SHC_au8RFeedBackCnt = 0u;
    SHC_au8LFeedBackCnt = 0u;
}

/*****************************************************************************
 Function      : SHC_vActive                                                 *
 Description   : seat heat function when kl15 off , for save     *
 			   seat heat state or stop output,clear the timer.    		    *
 Return Value  : None                                                         *
*****************************************************************************/
void SHC_vActive(void)
{
      
}

/*****************************************************************************
 Function      : SHC_vSeatHeatReq                                                   *
 Description   : In the On state, this the send the HMI seat heat request signal function. *
 NOTE:  													*
 Return Value  : None                                                        *
*****************************************************************************/
static void SHC_vSeatHeatReq(void)
{
	/**********Left***********/
	if(SHC_u8LastStateDr==True)
	{
		if(SHC_u8LeftSeatHeatCtrlTimer>18)
		{
			SHC_u8LastStateDr = False;
			SHC_u8LeftSeatHeatCtrlTimer = 0;
            MMI_vClrLeftShcKeyState();
            //Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_SHCL_Write(0u);
		}
		else
		{
			SHC_u8LeftSeatHeatCtrlTimer++;
		}		
	}
	else
	{
		if(SHC_stInputLists.u8SeatHeatStateL == True)
		{
			SHC_u8LastStateDr=On;
            //Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_SHCL_Write(1u);
		}
		else
		{
			/*do nothing*/
		}
	}

	/**********Right***********/
	if(SHC_u8LastStatePs==True)
	{
		if(SHC_u8RightSeatHeatCtrlTimer>18)
		{
			SHC_u8LastStatePs= False;
			SHC_u8RightSeatHeatCtrlTimer = 0;
            MMI_vClrRightShcKeyState();
            //Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_SHCR_Write(0u);
		}
		else
		{
			SHC_u8RightSeatHeatCtrlTimer++;
		}
	}
	else
	{
		if(SHC_stInputLists.u8SeatHeatStateR== True)
		{
			SHC_u8LastStatePs=True;
            //Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_SHCR_Write(1u);
		}
		else
		{
			/*do nothing*/
		}
	}
}

/*****************************************************************************
 Function      : SHC_vSeatHeatDisp                                                   *
 Description   : In the On state, this the send the HMI seat heat Display signal function. *
 NOTE:  													*
 Return Value  : None                                                        *
*****************************************************************************/
static void SHC_vSeatHeatDisp(void)
{
#if 1
/*******************Left Seat*****************/
	if(SHC_stInputLists.u16SeatHeatFeedbackL>306)//over 1.5v,204,1V
	{
        if(SHC_au8LFeedBackCnt < 8u)/*80ms*/
        {
            SHC_au8LFeedBackCnt++;
        }
        else
        {
            SHC_au8LFeedBackCnt = 8u;
            SHC_u8DisplayDr = True;
        }
	}
	else if(SHC_stInputLists.u16SeatHeatFeedbackL<40)//lower than 0.2v
	{
        SHC_au8LFeedBackCnt = 0u;
        SHC_u8DisplayDr = False;
	}
	else
	{
		/*do nothing*/
	}

/*******************Left Seat*****************/
	if(SHC_stInputLists.u16SeatHeatFeedbackR>306)//over 1.5v
	{
        if(SHC_au8RFeedBackCnt < 8u)/*80ms*/
        {
            SHC_au8RFeedBackCnt++;
        }
        else
        {
            SHC_au8RFeedBackCnt = 8u;
            SHC_u8DisplayPs = True;
        }
	}
	else if(SHC_stInputLists.u16SeatHeatFeedbackR<40)//lower than 0.2v
	{
        SHC_au8RFeedBackCnt = 0u;
        SHC_u8DisplayPs = False;
	}
	else
	{
		/*do nothing*/
	}
#else
/*******************Left Seat*****************/
	if(SHC_stInputLists.u16SeatHeatFeedbackL>204)//over 1v
	{
        SHC_u8DisplayDr = True;
	}
	else if(SHC_stInputLists.u16SeatHeatFeedbackL<40)//lower than 0.2v
	{
        SHC_u8DisplayDr = False;
	}
	else
	{
		/*do nothing*/
	}

/*******************Left Seat*****************/
	if(SHC_stInputLists.u16SeatHeatFeedbackR>204)//over 1.0v
	{
        SHC_u8DisplayPs = True;
	}
	else if(SHC_stInputLists.u16SeatHeatFeedbackR<40)//lower than 0.2v
	{
        SHC_u8DisplayPs = False;
	}
	else
	{
		/*do nothing*/
	}
#endif
}
/*****************************************************************************
 Function      : SHC_vMain                                                   *
 Description   : In the On state, this the seat heat main function . *
 NOTE:  													*
 Return Value  : None                                                        *
*****************************************************************************/
void SHC_vMain(void)
{
	SHC_vInputValueProcess();
	
	if((SHC_stInputLists.u8LowVoltage==True) || (SHC_stInputLists.u8HighVoltage==True))
	{/* over low or high voltage*/
		SHC_u8DisplayDr=SHC_nHeatSeatOff;
		SHC_u8DisplayPs=SHC_nHeatSeatOff;
	}
	else
	{
		/* request seat heating signal*/
		SHC_vSeatHeatReq();
		/* heating level and display*/
		SHC_vSeatHeatDisp();
	}

	#if (SHC_nUseCcp == True)
        SHC_vCcpOutputForce();
	#endif
	    SHC_vSeatHeatReqOutPut();
	#if(SHC_nUseRte == True)
	SHC_vUpdatedRte();
	#endif
	
}

/*****************************************************************************
 Function      : SHC_vInputValueProcess                                                   *
 Description   : In the On state, this the seat heat  input function . *
 NOTE:  													*
 Return Value  : None                                                        *
*****************************************************************************/
static void SHC_vInputValueProcess(void)
{
    uint16 u16SeatHeatFeedbackL;
    uint16 u16SeatHeatFeedbackR;

    Rte_Call_IoHwAd_IoHwAd_ReadAd_LeftSeatFbValue_Read(&u16SeatHeatFeedbackL);
    Rte_Call_IoHwAd_IoHwAd_ReadAd_RightSeatFbValue_Read(&u16SeatHeatFeedbackR);
	SHC_stInputLists.u8SeatHeatStateL=(MMI_u8GetValue(MMI_nu8SHL) | MMI_u8GetValue(MMI_nu8SHLFromeBus)); 
	SHC_stInputLists.u8SeatHeatStateR=(MMI_u8GetValue(MMI_nu8SHR) | MMI_u8GetValue(MMI_nu8SHRFromeBus));
	SHC_stInputLists.u16SeatHeatFeedbackL = u16SeatHeatFeedbackL;
	SHC_stInputLists.u16SeatHeatFeedbackR = u16SeatHeatFeedbackR;
}
/*****************************************************************************
 Function      : SHC_vUpdatedRte                                                   *
 Description   : In the On state, this the seat heat RTE interface function . *
 NOTE:  													*
 Return Value  : None                                                        *
*****************************************************************************/
#if(SHC_nUseRte == True)
static void SHC_vUpdatedRte(void)
{
	Rte_IWrite_Shc_vMain_ShcPutSwVersion_Version(SHC_u8SwVersion);
	Rte_IWrite_Shc_vMain_ShcPutDispInfo_ShcDispDr(SHC_u8DisplayDr);
	Rte_IWrite_Shc_vMain_ShcPutDispInfo_ShcDispPs(SHC_u8DisplayPs);
	Rte_IWrite_Shc_vMain_ShcPutErrorCode_u16ErrorCode(SHC_u8ErrorCode);
}
#endif

#if (SHC_nUseCcp == True)
/*************************************************************************************************** 
  Function   : SHC_vCcpOutputForce      
   
  Description: force output value.
                            
  Arguments  : None
  
  Returns    : Nothing.
***************************************************************************************************/
static void SHC_vCcpOutputForce(void)
{	
    uint8 u8SHCReq=0;
    
	if(SHCGetCcpForceBit(SHC_nSetRequestDr))
	{
        u8SHCReq = (uint8)(SHC_CcpControlData[SHC_nSetRequestDr]&0x0001);
        if(u8SHCReq == 1u)
        {
            SHC_u8LastStateDr = 0u;
        }
        else
        {
            SHC_u8LastStateDr = 1u;
        }
        //Rte_Call_ShcWritePort_SheatCtrlDr_Write(u8SHCReq);	
	}
	else
	{
        
	}
	if(SHCGetCcpForceBit(SHC_nSetRequestPs))
	{
        u8SHCReq = (uint8)(SHC_CcpControlData[SHC_nSetRequestPs]&0x0001);
        if(u8SHCReq == 1u)
        {
            SHC_u8LastStatePs = 0u;
        }
        else
        {
            SHC_u8LastStatePs = 1u;
        }
        //Rte_Call_ShcWritePort_SheatCtrlPs_Write(u8SHCReq);
	}
	else
	{
        
	}
    
}
#endif

/***************************************************************************************************
  Function   : SHC_u8ForceIoControl_Write

  Description: For PTS model

  Arguments  : None.

  Returns    : None.
***************************************************************************************************/
Std_ReturnType SHC_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
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
				SHCClrCcpForceByte();
				break;
            case 0xA2:
                SHCClrCcpForceBit(SHC_nSetRequestDr);
                break;   
            case 0xA4:
                SHCClrCcpForceBit(SHC_nSetRequestPs); 
                break;
            case 0x81:
            case 0xA1:
                SHCSetCcpForceBit(SHC_nSetRequestDr);
                SHC_CcpControlData[SHC_nSetRequestDr]=(uint8)(CcpControlWord.CcpContronData&0x0001);
                break;
            case 0x82:
            case 0xA3:
                SHCSetCcpForceBit(SHC_nSetRequestPs);
                SHC_CcpControlData[SHC_nSetRequestPs]=(uint8)(CcpControlWord.CcpContronData&0x0001);               
				break;
			default:
                return RTE_E_INVALID;
		}
	}
	else
	{
		SHCClrCcpForceByte();
	}
    return RTE_E_OK;
}

uint8 SHC_u8GetValue(SHC_tenu8VarNum enIndex)
{
    uint8 u8ReturnValue;
    
    if(enIndex < SHC_nMax)
    {
        u8ReturnValue = SHC_au8Array[enIndex];
    }
    else
    {
        u8ReturnValue = SHC_au8Array[SHC_nMax - 1u];
    }
    return u8ReturnValue;
}

static void SHC_vSeatHeatReqOutPut(void)
{
    if(SHC_u8LastStateDr == True)
    {
        Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_SHCL_Write(1u);
    }
    else
    {
        Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_SHCL_Write(0u);
    }

    if(SHC_u8LastStatePs == True)
    {
        Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_SHCR_Write(1u);
    }
    else
    {
        Rte_Call_IoHwPortWrite_IoHwWritePort_WritePort_SHCR_Write(0u);
    }
}
/****************************************************************************/
/* EOF */
