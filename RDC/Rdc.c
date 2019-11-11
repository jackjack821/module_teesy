/***************************************************************************************************
                                        RDC PROCESS
  .File Name: RDC.c
  
  .Description: Thie file is used to process rear defrost function.

  --------------------------------------------------------------------------------------------------
  Version     Date            Author            Change

  --------------------------------------------------------------------------------------------------
  Rev 1.0     2014/11/27      Xu Xianglin     	The first version  
  Rev 2.0     2014/11/27      Xu Xianglin     	Apply to Geely FE-3Z   
***************************************************************************************************/    

#define RDC_C                                   /*Name of the file*/
/***************************************************************************************************
                                        HEADER FILES
***************************************************************************************************/ 

/* System-headerfiles */
#include "General.h"
/* Foreign headerfiles */
#include "Rte_internal.h"
#include "Pow.h"
#include "Mmi.h"
#include "CANAPP.h"
/* Own headerfiles */
#include "Rdc.h"
#include "Rdc_Private.h"



/***************************************************************************************************
                                        LOCAL VARIABLES
***************************************************************************************************/
static uint8     RDC_au8Array[RDC_nu8Max];
static uint8     RDC_u8MmiStatus = False;/*Last mmi status.*/
static uint8     RDC_u8MmiInitWait = WAIT_MMI_TIME;/*Wait mmi state valid.*/
static uint8     RDC_u8UserRequest = False;/*To indicate whether to activate the output signal.*/

static uint16    RDC_u16ErrorDetectTimer = 0U;
static uint8     RDC_u16ErrorDetectTimerOn = 0U;/*Feedback signal on timer.*/
static uint8     RDC_u8ErrCounter = 0U; /*Apply to record signal unstable error times.*/

static uint8     RDC_u8RequestCount = 0U;
static uint8     RDC_u8ProcessState = REQUSET_NOT_ACTIVE;/*Process state of output signal handling.*/
static uint8     RDC_u8PluseTimer = 0U;/*Record output signal wide.*/

static uint8     RDC_u8StartUpdateTimer=0U;
static uint8     RDC_u8DisplayUpdateTimerOn = 0U;/*Feedback signal on timer.*/
static uint8     RDC_u8DisplayUpdateTimer = 0U;   /*Apply to record feedback signal detect cycle.*/
static uint8     RDC_u8BcmRearDefFeedback;
//static uint8     RDC_u8LastBcmRearDefFeedback;
//static uint8     RDC_u8BcmFeedbackInit;
static uint8    RDC_au8FeedBackCnt;

static uint8     RDC_CcpForceFlag = 0U;
static uint16    RDC_CcpControlData[RDC_nCcpForceMax] = {0U};

/***************************************************************************************************
                                        LOCAL FUNCTION PROTOTYTE
***************************************************************************************************/
static void RDC_vGetInputValue(void);
static void RDC_vCheckInputValue(void);
static void RDC_vUpdateOutputRequest(void);
static void RDC_vUpdateOutputDisplay(void);
static void RDC_vUpdateOutputVariable(void);
static void RDC_vCcpOutputForce(void);
/***************************************************************************************************
  Function    : RDC_vMain

  Description : Main function of Rear Defrost Control model Called in On container every 100 ms.

  Arguments   : None.

  Returns     : None.
***************************************************************************************************/
 void RDC_vMain(void)
{
    uint8 sbiLowVoltage, sbiHighVoltage;
    
	sbiLowVoltage = RDC_u8GetLowPowValue();
	sbiHighVoltage= RDC_u8GetHighPowValue();

    RDC_vGetInputValue();
    RDC_vCheckInputValue();
    if((sbiLowVoltage == True) || (sbiHighVoltage == True))
    {
        RDC_u8Request = False;
        RDC_u8Display = False;
    }
    else
    {
        RDC_vUpdateOutputRequest();
        RDC_vUpdateOutputDisplay(); 
    }
    RDC_vCcpOutputForce();
    RDC_vUpdateOutputVariable();
}


/***************************************************************************************************
  Function    : RDC_vGetInputValue

  Description : Apply to get input signal.

  Arguments   : None.

  Returns     : None.
***************************************************************************************************/
static void RDC_vGetInputValue(void)
{
    uint8 u8MmiStatus;
    uint16 u16RdefrostFeedBackAdValue = False;
    /*---------------------------1.Get User Request---------------------------*/    
    if(RDC_u8MmiInitWait > 0U) 
    {
        RDC_u8MmiInitWait--;
        RDC_u8MmiStatus = RDC_u8GetMmiStatus();
    }
    else
    {   
        /*Added by Yang Shengli,20170711*/
    	if(RdcGetCcpForceBit(RDC_nDiagSetRdcRequest))
    	{
            u8MmiStatus = (uint8)RDC_CcpControlData[RDC_nDiagSetRdcRequest];
    	}
    	else
    	{
            u8MmiStatus = RDC_u8GetMmiStatus();
    	}
            
        if(RDC_u8MmiStatus != u8MmiStatus)
        {
            RDC_u8MmiStatus = u8MmiStatus;
            if(RDC_u8UserRequest == True)
            {
                RDC_u8UserRequest = False;
            }
            else
            {
                RDC_u8UserRequest = True;
            }
        }
    }
    /*---------------------------2.Get Feedback Signal-------------------------*/ 
    RDC_u16GetSignal(&u16RdefrostFeedBackAdValue);
#if 0
    if(u16RdefrostFeedBackAdValue > 716u)/*240*/
    {
        if(RDC_au8FeedBackCnt < 20u)/*200ms*/
        {
            RDC_au8FeedBackCnt++;
        }
        else
        {
            RDC_au8FeedBackCnt = 20u;
            RDC_u8Feedback = True;
        }
    }
    else if(u16RdefrostFeedBackAdValue < 40u)
    {
        if(RDC_au8FeedBackCnt > 5u)
        {
            RDC_au8FeedBackCnt -= 5u;
        }
        else
        {
            RDC_au8FeedBackCnt = 0u;
            RDC_u8Feedback = False;
        }
    }
    else
    {
    }
#else
    if(u16RdefrostFeedBackAdValue > 240u)
    {
        RDC_u8Feedback = True;
    }
    else if(u16RdefrostFeedBackAdValue < 40u)
    {
        RDC_u8Feedback = False;
    }
    else
    {
    }
#endif
    RDC_u8BcmRearDefFeedback = RDC_u8GetBcmRearDefFeedback();
}



/***************************************************************************************************
  Function    : RDC_vCheckInputValue

  Description : Apply to check input signal.

  Arguments   : None.

  Returns     : None.
***************************************************************************************************/
static void RDC_vCheckInputValue(void)
{
    /*---------------------------1.Check Feedback Signal------------------------*/ 
    if(RDC_u16ErrorDetectTimer < FEEDBACK_DETECT_CYCLE)
    {
        RDC_u16ErrorDetectTimer++;
        if(RDC_u8Feedback != False)
        {
            RDC_u16ErrorDetectTimerOn++;
        }
    }
    else
    {
        if((RDC_u16ErrorDetectTimerOn > FEEDBACK_MIN_ERR_TIME)&&\
           (RDC_u16ErrorDetectTimerOn < FEEDBACK_MAX_ERR_TIME))
        {
            if(RDC_u8ErrCounter < 5U)
            {
                RDC_u8ErrCounter++;
            }
            else
            {
                RDC_ErrorCodeSet(RDC_nFeedbackUnstable);
            }
        }
        else
        {
            RDC_u8ErrCounter = 0U;
            RDC_ErrorCodeClr(RDC_nFeedbackUnstable);
        }
        RDC_u16ErrorDetectTimer = 0U;
        RDC_u16ErrorDetectTimerOn = 0U;
    }
}


/***************************************************************************************************
  Function    : RDC_vUpdateOutputRequest

  Description : Apply to Update rear defrost request.

  Arguments   : None.

  Returns     : None.
***************************************************************************************************/
static void RDC_vUpdateOutputRequest(void)
{
    if(RDC_u8UserRequest == True)
    {
        RDC_u8RequestCount++;
        RDC_u8RequestCount %= 2U;
    }
    
    if(RDC_u8ProcessState == REQUSET_NOT_ACTIVE)
    { 
        if(RDC_u8RequestCount > 0U)
        {
            RDC_u8RequestCount = 0U;
            RDC_u8ProcessState = REQUSET_ACTIVE;
        }
    }
    if(RDC_u8ProcessState == REQUSET_ACTIVE)
    {
        if(RDC_u8PluseTimer < REQ_PULSE_WIDE)
        {
            RDC_u8Request = True;
            RDC_u8PluseTimer++;
        }
        else
        {
            RDC_u8Request = False;
            RDC_u8PluseTimer = 0U;
            RDC_u8ProcessState = REQUSET_NOT_ACTIVE;
        }
    }
}



/***************************************************************************************************
  Function    : RDC_vUpdateOutputDisplay

  Description : Apply to Update display request.

  Arguments   : None.

  Returns     : None.
***************************************************************************************************/
static void RDC_vUpdateOutputDisplay(void)
{
   #ifdef RDC_USER_REQUEST_UPDATE_DISPLAY
    if(RDC_u8UserRequest == True)
    {
        if(RDC_u8Display)
        {
            RDC_u8Display = False;
        }
        else
        {
            RDC_u8Display = True;
        }
    }
   #endif
    if(RDC_u8UserRequest == True || RDC_u8ProcessState == REQUSET_ACTIVE)
    {
        RDC_u8StartUpdateTimer = UPDATE_DISPLAY_DELAY;
    }
    else
    {
        if(RDC_u8StartUpdateTimer > 0U)
        {
            RDC_u8StartUpdateTimer--;
        }
        else
        {
            /*Update display according to feedback.*/
            if(RDC_u8DisplayUpdateTimer < UPDATE_DISPLAY_CYCLE)
            {
                RDC_u8DisplayUpdateTimer++;
                if(RDC_u8Feedback != False)
                {
                    RDC_u8DisplayUpdateTimerOn++;
                }
            }
            else
            {
                if(RDC_u8DisplayUpdateTimerOn > DISPLAY_MIN_ON_TIME)
                {
                    RDC_u8Display = True;
                }
                else
                {
                    RDC_u8Display = False;
                }
                
                RDC_u8DisplayUpdateTimer = 0U;
                RDC_u8DisplayUpdateTimerOn = 0U;
            }
        }
    }
    RDC_u8UserRequest = False;

#if 0
    /*For ICE Display*/
    if(RDC_u8BcmFeedbackInit == False)
    {
        if(RDC_u8BcmRearDefFeedback < 2U)/*Signal is normal*/
        {
            RDC_u8BcmFeedbackInit = True;
            RDC_u8LastBcmRearDefFeedback = RDC_u8BcmRearDefFeedback;
        }
    }

    if(RDC_u8BcmRearDefFeedback < 2U)/*Signal is normal*/
    {
        if(RDC_u8BcmRearDefFeedback != RDC_u8LastBcmRearDefFeedback)
        {
            RDC_u8IceDisplayFlag = True;
        }
        else
        {
            RDC_u8IceDisplayFlag = False;
        }
        RDC_u8LastBcmRearDefFeedback = RDC_u8BcmRearDefFeedback;
    }
#endif
}


/***************************************************************************************************
  Function    : RDC_vUpdateOutputVariable

  Description : Apply to Update rte interface or IO value.

  Arguments   : None.

  Returns     : None.
***************************************************************************************************/
static void RDC_vUpdateOutputVariable(void)
{
    
}


/***************************************************************************************************
  Function   : RDC_u8ForceIoControl_Write

  Description: For PTS model

  Arguments  : None.

  Returns    : None.
***************************************************************************************************/
Std_ReturnType RDC_u8ForceIoControl_Write(UInt32 ForceIoControlWord)
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
				RdcClrCcpForceByte();
				break;
            case 0x04:
            case 0x82:
                RdcClrCcpForceBit(RDC_nPtsSetRdcRequest);
                break;
            case 0xA2:
                RdcClrCcpForceBit(RDC_nDiagSetRdcRequest);
                break;    
			case 0x03:
            case 0x81:
                RdcSetCcpForceBit(RDC_nPtsSetRdcRequest);
                RDC_CcpControlData[RDC_nPtsSetRdcRequest]=(uint8)(CcpControlWord.CcpContronData&0x0001);
				break;
            case 0xA1:
                RdcSetCcpForceBit(RDC_nDiagSetRdcRequest);
                RDC_CcpControlData[RDC_nDiagSetRdcRequest]=(uint8)(CcpControlWord.CcpContronData&0x0001);
				break;
			default:
                return RTE_E_INVALID;
		}
	}
	else
	{
		RdcClrCcpForceByte();
	}
    return RTE_E_OK;

}



/*************************************************************************************************** 
  Function   : RDC_vCcpOutputForce      
   
  Description: force output value.
                            
  Arguments  : None
  
  Returns    : Nothing.
***************************************************************************************************/
static void RDC_vCcpOutputForce(void)
{	
	if(RdcGetCcpForceBit(RDC_nPtsSetRdcRequest))
	{
        if(RDC_CcpControlData[RDC_nPtsSetRdcRequest] == 1u)
        {
            RDC_u8Request = 0u;
        }
        else if(RDC_CcpControlData[RDC_nPtsSetRdcRequest] == 0u)
        {
            RDC_u8Request = 1u;
        }
        else
        {
        }
	}
	else
	{
	}
}

/***************************************************************************************************
  Function   : RDC_vReset

  Description: The reset routine for the Rdc module.

  Arguments  : None.

  Returns    : None.
***************************************************************************************************/
 void RDC_vReset(void)
{
     RDC_u8SwVersion = RDC_nVersion;/*2016.06.21*/
     RDC_u8Display = False;
     RDC_u8ErrCode = 0U;
     RDC_u8Request = False;
     RDC_u8IceDisplayFlag = False;
     RDC_u8MmiStatus = False;
     RDC_u8MmiInitWait = WAIT_MMI_TIME;
     RDC_u8UserRequest = False;
     RDC_u8Feedback = False;
     RDC_u16ErrorDetectTimer = 0U;
     RDC_u16ErrorDetectTimerOn = 0U;
     RDC_u8ErrCounter = 0U;
     RDC_u8RequestCount=0U;
     RDC_u8ProcessState = REQUSET_NOT_ACTIVE;
     RDC_u8PluseTimer = 0U;
     RDC_u8StartUpdateTimer=0U;
     RDC_u8DisplayUpdateTimerOn = 0U;
     RDC_u8DisplayUpdateTimer = 0U;
     RDC_CcpForceFlag = 0u;

     RDC_au8FeedBackCnt = 0u;
     //RDC_u8BcmFeedbackInit = False;
     
}



/***************************************************************************************************
  Function   : RDC_vInit

  Description: Init function of rear defrost control model Called in Active->On container.

  Arguments  : None.

  Returns    : None.
***************************************************************************************************/
 void RDC_vInit(void)
{
	RDC_vReset();
}



/***************************************************************************************************
  Function   : RDC_vDeinit

  Description: Deinit function of rear defrost control model Called in Active->On container.

  Arguments  : None.

  Returns    : None.
***************************************************************************************************/
void RDC_vDeinit(void)
{
	RDC_vReset();
}

void RDC_vActive(void)
{
	
}

/***************************************************************************************************
  Function   : RDC_u8GetValue

  Description: The extern model get the uint8 type variable value from this  model

  Arguments  : None.

  Returns    : None.
***************************************************************************************************/
uint8 RDC_u8GetValue( RDC_tenu8VarNumber enIndex )
{
    uint8 u8ReturnValue;
	if ( enIndex < RDC_nu8Max )
	{
        u8ReturnValue = RDC_au8Array[enIndex];
	}
	else
	{
        u8ReturnValue = RDC_au8Array[RDC_nu8Max-1];
	}
    return u8ReturnValue;
}
/***************************************************************************************************
* EOF:
***************************************************************************************************/
