/*******************************************************************************
| Project Name: DiagLIN
|    File Name: LINdiag.c
|
|  Description: UDS (ISO-14229) conform diagnostic layer implementation.
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2014 Vector Informatik GmbH                 All rights reserved.
|
| This software is copyright protected and proprietary to Vector Informatik GmbH.
| Vector Informatik GmbH grants to you only those rights as set out in the
| license conditions. All other rights remain with Vector Informatik GmbH.
|
| REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
|-------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ---------------------------------------
| Sa           Mishel Shishmanyan        Vector Informatik GmbH
| Ap           Andreas Pick              Vector Informatik GmbH
| Svh          Sven Hesselmann           Vector Informatik GmbH
| Bmo          Bastian Molkenthin        Vector Informatik GmbH
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date        Ver      Author  Description
| ----------  -------  ------  -------------------------------------------------
| 2004-07-09  1.00.00  Sa      First implementation
| 2007-05-16  1.01.00  Ap      ESCAN00020779: Support for new LIN Tp interface
|                              ESCAN00020780: Compile warning due to implicit cast to smaller type
| 2008-04-07  1.02.00  Svh     ESCAN00025886: Support Rx Single Frame Only of TpLin
| 2008-06-30  1.03.00  Ap      ESCAN00027967: Report tester present command to application
| 2009-01-30  1.04.00  Ap      ESCAN00032693: Session control enabled
| 2011-08-22  1.05.00  Sa      ESCAN00052746: TesterPresent service not fully UDS compliant
| 2012-11-08  1.06.00  Ap      ESCAN00062456: Service active timeout observation
| 2013-03-04  1.06.01  Ap      ESCAN00065558: Compatibility to LinTp
| 2013-11-27  1.06.02  Ap      ESCAN00072256: Access to suppress positive response bit
| 2013-12-16  1.07.00  Bmo     ESCAN00071108: Response pending frames support enabled
|                              ESCAN00072484: Access to NAD of diagnostic request
| 2014-01-13  1.07.01  Bmo     ESCAN00072939: Abort diagnostic response after failed response pending transmission
********************************************************************************/

/*----------------------------
Include section
----------------------------*/
#include "lin_api.h"
#include "dtl_api.h"
#include "LinDiag.h"

/*----------------------------
Version check
----------------------------*/
#if ( (DIAGLIN_SLAVECU_VERSION          != 0x0107u) || \
      (DIAGLIN_SLAVECU_RELEASE_VERSION  != 0x01u)    )
# error "Source-Header files versions are inconsistent!"
#endif

#if ( TPLIN_VERSION < 0x0129u )
# error "LinDiag is not working with this version of TpLin. Please use newer version of TpLin."
#endif

/*----------------------------
Constants
----------------------------*/
/* All requests have their NADs and the functional one is the 0x7E value */
#define kLinDiagNADFunctional                              kDtlAdrTypeLogical

#if defined (kLinDiagRespPendingLength)
#else
# define kLinDiagRespPendingLength                         0x03u
#endif

/*----------------------------
Typedefs
----------------------------*/
#if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT)
# if (kLinDiagS1Ticks > 255)
typedef vuint16 tLinDiagT1Timer;
# else
typedef vuint8  tLinDiagT1Timer;
# endif
#endif

#if defined (LINDIAG_ENABLE_REQUEST_ACTIVE_TIMEOUT)
# if (kLinDiagRequestActiveTicks > 255)
typedef vuint16 tLinDiagRequestActiveTimer;
# else
typedef vuint8  tLinDiagRequestActiveTimer;
# endif
#endif

#if defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)
# if (kLinDiagP2ExtTicks > 255)
typedef vuint16 tLinDiagT2Timer;
# else
typedef vuint8  tLinDiagT2Timer;
# endif
#endif

typedef struct
{
  vbittype   rxInd                 :1;
  vbittype   bufferLocked          :1;
  vbittype   doSendResponse        :1;
  vbittype   doSendPosResponse     :1;
#if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT)
  vbittype   isSessionNonDefault   :1;
#endif
#if defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)
  vbittype   txReady               :1;
  vbittype   isRcrRpResponse       :1;
#endif
} tLinDiagState;

/*----------------------------
Global RAM variables
----------------------------*/
/* Global diagnostic buffer for the request/response messages. */
V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 pbLinDiagBuffer[kLinDiagDataBufferLength];
/* Global variable for the message length (request/response). */
V_MEMRAM0 V_MEMRAM1 vuint16 V_MEMRAM2 g_linDiagDataLength;

#if defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)
V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 pbLinDiagRcrRpBuffer[6];
#endif

/*----------------------------
Internal RAM variables
----------------------------*/
#if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT)
/* Internal "TesterPresent" monitor */
V_MEMRAM0 static V_MEMRAM1 tLinDiagT1Timer V_MEMRAM2 g_linDiagT1Timer;
#endif

#if defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)
/* Internal "ResponsePending" monitor */
V_MEMRAM0 static V_MEMRAM1 tLinDiagT2Timer V_MEMRAM2 g_linDiagT2Timer;
#endif

/* LINdiag state machine */
V_MEMRAM0 static V_MEMRAM1 tLinDiagState V_MEMRAM2 g_linDiagState;

#if defined (LINDIAG_ENABLE_REQUEST_ACTIVE_TIMEOUT)
/* Service active timer */
V_MEMRAM0 static V_MEMRAM1 tLinDiagRequestActiveTimer V_MEMRAM2 g_linDiagRequestActiveTimer;
#endif

/* NAD of current diagnostic connection */
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 g_linDiagCurrentNAD;


/*----------------------------
Global ROM variables
----------------------------*/
/* Version information */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kLinDiagMainVersion   = (vuint8) ((DIAGLIN_SLAVECU_VERSION & 0xFF00u) >>8);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kLinDiagSubVersion    = (vuint8) (DIAGLIN_SLAVECU_VERSION & 0x00FFu);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kLinDiagBugFixVersion = (vuint8) (DIAGLIN_SLAVECU_RELEASE_VERSION);

/*----------------------------
Internal ROM variables
----------------------------*/

/*----------------------------
Function prototypes
----------------------------*/
static void ResponsePreTransmit(void);

/*----------------------------
Macro functions
----------------------------*/


/*----------------------------
Implementation
----------------------------*/
/*******************************************************************************
* NAME:              LinDiagInit
* PARAMETERS:        none
* RETURNS:           none
* DESCRIPTION:       Initilizes the component.
*******************************************************************************/
void LinDiagInit(void)
{
  g_linDiagState.rxInd                = 0;
  g_linDiagState.bufferLocked         = 0;
  g_linDiagState.doSendPosResponse    = 1;
#if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT)
  g_linDiagState.isSessionNonDefault  = 0;
  g_linDiagT1Timer                    = 0;
#endif

#if defined (LINDIAG_ENABLE_REQUEST_ACTIVE_TIMEOUT)
  g_linDiagRequestActiveTimer         = 0;
#endif

#if defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)
  g_linDiagState.isRcrRpResponse      = 0;
  g_linDiagState.txReady              = 0;
  pbLinDiagRcrRpBuffer[0]             = 0x7Fu;
  pbLinDiagRcrRpBuffer[2]             = 0x78u;
  pbLinDiagRcrRpBuffer[3]             = 0xFFu;
  pbLinDiagRcrRpBuffer[4]             = 0xFFu;
  pbLinDiagRcrRpBuffer[5]             = 0xFFu;
  g_linDiagT2Timer                    = 0;
#endif

  g_linDiagCurrentNAD                 = 0x00u;
}

/*******************************************************************************
* NAME:              LinDiagTask
* PARAMETERS:        none
* RETURNS:           none
* DESCRIPTION:       Manages the component timers and service dispatcher.
*******************************************************************************/
void LinDiagTask(void)
{
#if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT) || \
    defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)     || \
    defined (LINDIAG_ENABLE_REQUEST_ACTIVE_TIMEOUT)
  if(g_linDiagState.bufferLocked != 0)
#endif
  {
    if(g_linDiagState.rxInd != 0)
    { /* service pending */
#if defined (LINDIAG_ENABLE_MULTIPLE_SERVICE_CALL)
      /* g_linDiagState.rxInd not cleared until complete processing of service */
#else
      g_linDiagState.rxInd = 0;
#endif
      /* Dispatch the service */
      switch(pbLinDiagBuffer[0])
      {
           /*Always executable Sids*/
#if defined (LINDIAG_ENABLE_SERVICE_10H)
        case 0x10u:
            /* This service has a sub-function - check the parameter and prepare
             * the sub-function for the application dispatching
             */
            LinDiagPreProcessSubFunction();
            //ApplLinDiagSessionControl();
            break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_11H)
        case 0x11u:
            /* This service has a sub-function - check the parameter and prepare
             * the sub-function for the application dispatching
             */
            LinDiagPreProcessSubFunction();
            //ApplLinDiagEcuReset();
            break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_14H)
        case 0x14u:
            //ApplLinDiagClearDiagInfo();
            break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_19H)
        case 0x19u:
            /* This service has a sub-function - check the parameter and prepare
             * the sub-function for the application dispatching
             */
            LinDiagPreProcessSubFunction();
            //ApplLinDiagReadDtcInfo();
            break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_22H)
        case 0x22u:
           // ApplLinDiagReadDataById();
            break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_23H)
        case 0x23u:
           // ApplLinDiagReadDataByAddress();
            break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_24H)
        case 0x24u:
            //ApplLinDiagReadScalingDataById();
            break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_2EH)
        case 0x2Eu:
            //ApplLinDiagWriteDataById();
            break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_31H)
        case 0x31u:
            /* This service has a sub-function - check the parameter and prepare
             * the sub-function for the application dispatching
             */
            LinDiagPreProcessSubFunction();
           // ApplLinDiagRoutineControl();
            break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_3DH)
        case 0x3Du:
            //ApplLinDiagWriteMemoryByAddress();
            break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_3EH)
        case 0x3Eu:
            /* Set the proper response behavior */
            LinDiagPreProcessSubFunction();
            /* First check minimum length (UDS validation flow) ... */
            if(g_linDiagDataLength >= 1)
            {
              /* ... now check the sub-function ... */
              if(pbLinDiagBuffer[1] == 0x00u)
              {
                /* ... now check concrete (SF specific) length (UDS validation flow) */
                if(g_linDiagDataLength == 1)
                {
                  //ApplLinDiagTesterPresent();
                  /* Echoes the sub-function */
                  g_linDiagDataLength = 1;
                  LinDiagSendPosResponse();
                }
                else
                {
                  LinDiagSendNegResponse(kLinDiagNrcInvalidFormat);
                }
              }
              else
              {
                LinDiagSendNegResponse(kLinDiagNrcInvalidSubFunction);
              }
            }
            else
            {
              LinDiagSendNegResponse(kLinDiagNrcInvalidFormat);
            }
            break;
#endif

#if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT)
        default:
          {
            if(g_linDiagState.isSessionNonDefault != 0)
            {
              switch(pbLinDiagBuffer[0])
              {
#endif
                /* All non-default session SIDs */
#if defined (LINDIAG_ENABLE_SERVICE_27H)
                case 0x27u:
                  /* This service has a sub-function - check the parameter and prepare
                   * the sub-function for the application dispatching
                   */
                  LinDiagPreProcessSubFunction();
                  //ApplLinDiagSecurityAccess();
                  break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_28H)
                case 0x28u:
                  /* This service has a sub-function - check the parameter and prepare
                   * the sub-function for the application dispatching
                   */
                  LinDiagPreProcessSubFunction();
                  //ApplLinDiagCommControl();
                  break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_2FH)
                case 0x2Fu:
                  //ApplLinDiagIoControlById();
                  break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_34H)
                case 0x34u:
                  ApplLinDiagRequestDownload();
                  break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_35H)
                case 0x35u:
                  ApplLinDiagRequestUpload();
                  break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_36H)
                case 0x36u:
                  ApplLinDiagTransferData();
                  break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_37H)
                case 0x37u:
                  ApplLinDiagTransferExit();
                  break;
#endif
    /*****************************/
#if defined (LINDIAG_ENABLE_SERVICE_85H)
                case 0x85u:
                  /* This service has a sub-function - check the parameter and prepare
                   * the sub-function for the application dispatching
                   */
                  LinDiagPreProcessSubFunction();
                  ApplLinDiagControlDtcSetting();
                  break;
#endif
                default:
#if defined (LINDIAG_ENABLE_USER_SERVICE_SUPPORT)
                  /* Call the user service */
                  //ApplLinDiagUserService();
#else
                  LinDiagSendNegResponse(kLinDiagNrcServiceNotSupported);
#endif
#if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT)
              }
            }
            else
            {
              switch(pbLinDiagBuffer[0])
              {
                /* All non-default session SIDs */
# if defined (LINDIAG_ENABLE_SERVICE_27H)
                case 0x27u:
# endif
# if defined (LINDIAG_ENABLE_SERVICE_28H)
                case 0x28u:
# endif
# if defined (LINDIAG_ENABLE_SERVICE_2FH)
                case 0x2Fu:
# endif
# if defined (LINDIAG_ENABLE_SERVICE_34H)
                case 0x34u:
# endif
# if defined (LINDIAG_ENABLE_SERVICE_35H)
                case 0x35u:
# endif
# if defined (LINDIAG_ENABLE_SERVICE_36H)
                case 0x36u:
# endif
# if defined (LINDIAG_ENABLE_SERVICE_37H)
                case 0x37u:
# endif
# if defined (LINDIAG_ENABLE_SERVICE_85H)
                case 0x85u:
# endif
                  LinDiagSendNegResponse(kLinDiagNrcServiceNotSuppInActiveMode);
                  break;
                default:
# if defined (LINDIAG_ENABLE_USER_SERVICE_SUPPORT)
                  /* Call the user service */
                 // ApplLinDiagUserService();
# else
                  LinDiagSendNegResponse(kLinDiagNrcServiceNotSupported);
# endif
              }
            }
          }
#endif
      }
    }/* End of indication dependent code */
#if defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)
    /* It can be collision between RCR-RP and final response poll until free slot found */
    if(g_linDiagState.txReady != 0)
    { /* actual response was triggered */
      if(g_linDiagState.isRcrRpResponse == 0)
      { /* no response pending frame currently transmitted, send response */
        g_linDiagState.txReady = 0;
        (void)DtlTxSendMessage(g_linDiagDataLength);
      }
    }

    /* RCR-RP monitoring */
    if(g_linDiagT2Timer != 0)
    {
      g_linDiagT2Timer--;
      if(g_linDiagT2Timer == 0)
      {
        /* Send this special response via extra API */
        g_linDiagT2Timer = kLinDiagP2ExtTicks;
        g_linDiagState.isRcrRpResponse = 1;
        /* Send response pending frame, SID was already copied */
        if (DtlTxSendRcrRpMessage(kLinDiagRespPendingLength) == kDtlTxState_REJECTED)
        { /* dtl is not ready (previous RP frame could be still ongoing), retry in next cycle */
          g_linDiagT2Timer = 1;
        }
      }
    }
#endif

#if defined (LINDIAG_ENABLE_REQUEST_ACTIVE_TIMEOUT)
    if (g_linDiagRequestActiveTimer != 0)
    {
      g_linDiagRequestActiveTimer--;
      if (g_linDiagRequestActiveTimer == 0)
      { /* timeout on pending service request by diagnostic application - reject service */
        /* inform application on timeout */
        ApplLinDiagServiceActiveTimeout();
        LinDiagSendNoResponse();/* finalize without response - do all designated jobs after a service processing is finished */
      }
    }
#endif
  }
#if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT)
  else
  {
    /* Timeout monitoring only during non-default session */
    if(g_linDiagState.isSessionNonDefault != 0)
    {
      if(g_linDiagT1Timer != 0)
      {
        g_linDiagT1Timer--;
        if(g_linDiagT1Timer == 0)
        {
          /* Time is up - reset the state */
          LinDiagSetSessionDefault();
          /* Notify the application */
# if defined (LINDIAG_ENABLE_ON_S1_TIMEOUT_NOTIFICATION)
          ApplLinDiagOnS1Timeout();
# endif
        }
      }
    }
  }
#endif
}

/*******************************************************************************
* NAME:              LinDiagPreProcessSubFunction
* PARAMETERS:        none
* RETURNS:           none
* DESCRIPTION:       Central sub-function preprocessing.
*******************************************************************************/
void LinDiagPreProcessSubFunction(void)
{
  /* Check Suppress Positive Response Message Indication Bit (SPRMIB) */
  if((pbLinDiagBuffer[1] & 0x80u) != 0)
  { /* Flag is set - clear the pos response flag */
    g_linDiagState.doSendPosResponse = (vuint8)(0x00u);
    /* Mask out the Suppress Positive Response Message Indication Bit (SPRMIB) */
    pbLinDiagBuffer[1] &= 0x7Fu;
  }
}

/*******************************************************************************
* NAME:              LinDiagSendPosResponse
* PARAMETERS:        none
* RETURNS:           none
* DESCRIPTION:       Composes and sends positive response.
*******************************************************************************/
void LinDiagSendPosResponse(void)
{
  if(g_linDiagState.doSendPosResponse == 0)
  {
    /* If positive response with SPRMIB set must be sent - don't send it */
    LinDiagSendNoResponse();
  }
  else
  {
    /* Compose response header */
    pbLinDiagBuffer[0] += 0x40u;
    /* Add SID length */
    g_linDiagDataLength++;
    /* Finalize the request process */
    ResponsePreTransmit();
  }
}

/*******************************************************************************
* NAME:              LinDiagSendNegResponse
* PARAMETERS:
*                    - nrc: The negative response code.
* RETURNS:           none
* DESCRIPTION:       Composes and sends negative response with error code <nrc>.
*******************************************************************************/
void LinDiagSendNegResponse(vuint8 nrc)
{
  pbLinDiagBuffer[1] = pbLinDiagBuffer[0];
  pbLinDiagBuffer[0] = 0x7Fu;
  pbLinDiagBuffer[2] = nrc;
  /* NR are 3 Byte */
  g_linDiagDataLength = 3;
  /* Finalize the request process */
  ResponsePreTransmit();
}

/*******************************************************************************
* NAME:              LinDiagSendNoResponse
* PARAMETERS:        none
* RETURNS:           none
* DESCRIPTION:       Finalizes the request processing without response.
*******************************************************************************/
void LinDiagSendNoResponse(void)
{
  /* No response to be sent */
  g_linDiagState.doSendResponse = 0;
  /* Finalize the request process */
  ResponsePreTransmit();
}

/*******************************************************************************
* NAME:              LinDiagSetRequestPending
* PARAMETERS:        none
* RETURNS:           none
* DESCRIPTION:       Allows response transmission without receiving a request
*                    (FBL use case where a positive response is transmitted after reset).
*                    It is up to the application to guarantee that a response may be
*                    transmitted.
*******************************************************************************/
void LinDiagSetRequestPending(void)
{
  LinSetDiagnosticTxUser(kDdDiagFrmUser_LinTp_S);
  g_linDiagState.doSendResponse = 0x01u;
}


#if defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)
/*******************************************************************************
* NAME:              LinDiagSendResponsePending
* PARAMETERS:        none
* RETURNS:           none
* DESCRIPTION:       Triggers the cyclic transmission of response pending frames.
*                    Must be finalized by a call to LinDiagSend<X>Response.
*******************************************************************************/
void LinDiagSendResponsePending(void)
{
# if defined (LINDIAG_ENABLE_MULTIPLE_SERVICE_CALL)
  g_linDiagState.rxInd = 0;
# endif
# if defined (LINDIAG_ENABLE_REQUEST_ACTIVE_TIMEOUT)
  g_linDiagRequestActiveTimer   = 0;
# endif
  /* Functional request have no response on LIN */
  if(g_linDiagState.doSendResponse != 0)
  {
    /* Copy the SID */
    pbLinDiagRcrRpBuffer[1] = pbLinDiagBuffer[0];
# if defined (LINDIAG_ENABLE_RP_IMMEDIATE_TX)
    g_linDiagState.isRcrRpResponse = 1;
    /* transmit first RP frame directly without waiting for P2 timeout */
    (void)DtlTxSendRcrRpMessage(kLinDiagRespPendingLength);
    /* skip P2 timeout, set directly P2* */
    g_linDiagT2Timer = kLinDiagP2ExtTicks;
# else
    /* Activate RCR-RP P2 timeout */
    g_linDiagT2Timer = kLinDiagP2Ticks;
# endif
    /* Restore the pos response flag because a response pending frame is requested */
    g_linDiagState.doSendPosResponse = 1;
  }
  else
  {
    /* Tp confirmation with success */
    g_linDiagT2Timer = 0;
    (void)ApplDtlTxConfirmation(kDtlTxResult_COMPLETED);
  }
}
#endif


#if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT)
/*******************************************************************************
* NAME:              LinDiagSetSessionNonDefault
* PARAMETERS:        none
* RETURNS:           none
* DESCRIPTION:       Sets active session to extended.
*******************************************************************************/
void LinDiagSetSessionNonDefault(void)
{
  g_linDiagState.isSessionNonDefault = 1;
}
#endif

#if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT)
/*******************************************************************************
* NAME:              LinDiagSetSessionDefault
* PARAMETERS:        none
* RETURNS:           none
* DESCRIPTION:       Sets active session to default.
*******************************************************************************/
void LinDiagSetSessionDefault(void)
{
  g_linDiagState.isSessionNonDefault = 0;
}
#endif

#if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT)
/*******************************************************************************
* NAME:              LinDiagIsSessionNonDefault
* PARAMETERS:        none
* RETURNS:           none
* DESCRIPTION:       Gets the active session type.
*                    Returns 1 for extended, 0 for default session.
*******************************************************************************/
vuint8 LinDiagIsSessionNonDefault(void)
{
  return (vuint8)g_linDiagState.isSessionNonDefault;
}
#endif

/*******************************************************************************
* NAME:              LinDiagCheckSPRMIB
* PARAMETERS:        none
* RETURNS:           0 - Suppress Positive Response Message Indication Bit not set
*                        a response is expected
*                    1 - Suppress Positive Response Message Indication Bit is set
*                        no response is expected
* DESCRIPTION:       This function returns the status of the Suppress Positive 
*                    Response Message Indication Bit.
*******************************************************************************/
vuint8 LinDiagCheckSPRMIB(void)
{
  vuint8 tmpRet;

  /* check if the Suppress Positive Response Message Indication Bit is set */
  if (g_linDiagState.doSendPosResponse == 0)
  { /* SPRMIB flag is set - a response is not expected */
    tmpRet = 1;
  }
  else
  { /* flag is not set - a response is expected */
    tmpRet = 0;
  }
  /* return the pos response flag */
  return  tmpRet;
}

/*******************************************************************************
* NAME:              LinDiagGetCurrentNAD
* PARAMETERS:        none
* RETURNS:           NAD of received frame
* DESCRIPTION:       This function returns the NAD of the currently processed
*                    request.
*******************************************************************************/
vuint8 LinDiagGetCurrentNAD(void)
{
  return g_linDiagCurrentNAD;
}

/*******************************************************************************
* NAME:              ApplDtlRxStartIndication
* PARAMETERS:
*                    bLength: Length of diag request which is currently received
*                    bAddressInfo: NAD of received frame
* RETURNS:           kDtlStart_Ignore    The message is ignored.
*                    kDtlStart_RxCopy    The message is received and copied.
*                    kDtlStart_RxNoCopy  The message is received but not copied.
* DESCRIPTION:       Checks if the request shall be accepted.
*******************************************************************************/
vuint8 ApplDtlRxStartIndication(vuint8 bAddressInfo, vuint16 bLength)
{
  vuint8 bReturn;
  bReturn = kDtlStart_Ignore;
#if defined ( DTL_ENABLE_RX_SINGLE_FRAME_ONLY )
  /* if only RX Single Frames are supported, any length with more than 6 bytes must be ignored */
  if ((g_linDiagState.bufferLocked == 0) && (bLength <= 6))
#else
  if(g_linDiagState.bufferLocked == 0)
#endif
  {
    /* Cache the request total length */
    g_linDiagDataLength = bLength;
    /* Set the addressing type */
    if (bAddressInfo == kLinDiagNADFunctional)
    {
      g_linDiagState.doSendResponse = 0x00u;
    }
    else
    {
      g_linDiagState.doSendResponse = 0x01u;
    }
    /* save NAD of request */
    g_linDiagCurrentNAD = bAddressInfo;

    if(bLength <= kLinDiagDataBufferLength)
    { /* appropriate request length for configured buffer */
      /* lock the buffer */
      g_linDiagState.bufferLocked = 1;
      /* Set return type message accepted */
      bReturn = kDtlStart_RxCopy;
    }
#if defined (LINDIAG_ENABLE_NEG_RES_ON_BUFF_OVERRUN)
    else
    {
      /* Lock the buffer */
      g_linDiagState.bufferLocked = 1;
      /* Set return type to buffer too small */
      bReturn = kDtlStart_RxNoCopy;
    }
#endif
  }
  return bReturn;
}

/*******************************************************************************
* NAME:              ApplDtlRxMsgIndication
* PARAMETERS:
*                    bResult: The result of the reception (0x00 - ok, 0x01 - failed).
* RETURNS:           none
* DESCRIPTION:       Event for complete request reception.
*******************************************************************************/
void ApplDtlRxMsgIndication(vuint8 bResult)
{
  vuint8 bLockStatus;
  /* by default unlock the buffer */
  bLockStatus = 0;
#if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT)
  /* Prepare for new requests - even for fault indication the timer will be reset */
  g_linDiagT1Timer = kLinDiagS1Ticks;
#endif
#if defined (LINDIAG_DISABLE_NR_ON_RES_SID)
  /* If SID in range [0x00, 0x3F]U[0x80, 0xBF] accept it, otherwise ignore the request */
  if((pbLinDiagBuffer[0] & 0x40u) == 0)
#endif
  {
    if(bResult == kDtlRxResult_COMPLETED)
    {
#if defined (LINDIAG_ENABLE_NEG_RES_ON_BUFF_OVERRUN)
      /* The reqLength is still the total one */
      if(g_linDiagDataLength > kLinDiagDataBufferLength)
      {
        /* Send NR invalid format (length) */
        LinDiagSendNegResponse(kLinDiagNrcInvalidFormat);
      }
      else
#endif
      {
        /* Exclude the SID byte from the total length */
        g_linDiagDataLength--;
#if defined (LINDIAG_ENABLE_REQUEST_ACTIVE_TIMEOUT)
        /* Activate request active timeout */
        g_linDiagRequestActiveTimer = kLinDiagRequestActiveTicks;
#endif
        /* By default positive responses will be sent */
        g_linDiagState.doSendPosResponse = 1;
        /* Notify that there is a new request */
        g_linDiagState.rxInd = 1;
      }
      /* Everything ok keep buffer locked */
      bLockStatus = 1;
    }
  }
  /* Assign new buffer lock status */
  g_linDiagState.bufferLocked = bLockStatus;
}

/*******************************************************************************
* NAME:              ApplDtlTxConfirmation
* PARAMETERS:
*                    bResult: The result of the transmission (0x00 - ok, 0x01 - failed).
* RETURNS:           none
* DESCRIPTION:       Event for complete response transmission.
*******************************************************************************/
vuint8 ApplDtlTxConfirmation(vuint8 bResult)
{
  vuint8 bReturn;
  bReturn = kDtlTxResult_COMPLETED;

#if defined ( LINDIAG_ENABLE_RCR_RP_CONFIRMATION ) || defined ( LINDIAG_ENABLE_TX_CONFIRMATION )
# if defined ( LINDIAG_ENABLE_RCR_RP_CONFIRMATION )
  if(g_linDiagState.isRcrRpResponse != 0)
  { /* indicate confirmation of transmitted response pending frame to application */ 
    ApplLinDiagRespPendingTxConfirmation( bResult );
  }
  else
# endif
  {
# if defined ( LINDIAG_ENABLE_TX_CONFIRMATION )
    /* indicate confirmation of transmitted response to application */
    ApplLinDiagTxConfirmation( bResult );
# endif
  }
#else
# if defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)
# else
#  if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  /* Currently not used */
  bResult = bResult;
#  endif
# endif
#endif

#if defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)
  /* Only the final response can unlock the buffer */
  if(g_linDiagState.isRcrRpResponse != 0)
  {
    g_linDiagState.isRcrRpResponse = 0;
    if ( bResult == 0)
    { /* expect further response pending frame or final response */
      bReturn = kDtlTxTransmPending;
    }
    else
    { /* transmission of response failed, abort connection */
      g_linDiagState.doSendResponse = 0;
      g_linDiagState.bufferLocked = 0;
      g_linDiagCurrentNAD = 0x00u;
      /* bReturn has already correct value */
    }
  }
  else
#endif
  {
#if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT)
    /* Allow decrementation */
    g_linDiagT1Timer = kLinDiagS1Ticks;
#endif
    g_linDiagState.bufferLocked = 0;
    g_linDiagCurrentNAD = 0x00u;
  }

  /* Default - no more responses to be awaited */
  return bReturn;
}

/*******************************************************************************
* NAME:              ResponsePreTransmit
* PARAMETERS:        none
* RETURNS:           none
* DESCRIPTION:       Pre response transmission finalization.
*******************************************************************************/
static void ResponsePreTransmit(void)
{
#if defined (LINDIAG_ENABLE_MULTIPLE_SERVICE_CALL)
  g_linDiagState.rxInd = 0;
#endif
#if defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)
  g_linDiagT2Timer = 0;
#endif
#if defined (LINDIAG_ENABLE_REQUEST_ACTIVE_TIMEOUT)
  g_linDiagRequestActiveTimer   = 0;
#endif
  /* Functional request have no response on LIN */
  if(g_linDiagState.doSendResponse != 0)
  {
#if defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)
    if(g_linDiagState.isRcrRpResponse == 0)
    { /* no response pending frame currently transmitted, send response */
      (void)DtlTxSendMessage(g_linDiagDataLength);
    }
    else
    { /* response pending frame active, retry on task level */
      g_linDiagState.txReady = 1;
    }
#else
    (void)DtlTxSendMessage(g_linDiagDataLength);
#endif
  }
  else
  {
    /* Tp confirmation with success */
    (void)ApplDtlTxConfirmation(kDtlTxResult_COMPLETED);
  }
}


/* module specific MISRA deviations:
   MD_LINDIAG_8.8:
     Reason: Also declared in dtl_lin.h to prevent inconsistencies in the layer model (access from dtl and application layer).
     Risk: Compile error due to inconsistencies in declaration
     Prevention: Tested during integration. LinDiag and DTL are always provided together.

   MD_LINDIAG_8.12:
     Reason: Array dimension is project dependent and generated by generation tool.
     Risk: Invalid element access or no compiler optimization.
     Prevention: Tested during integration.

*/
