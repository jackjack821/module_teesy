/* PRQA S 0715 EOF *//* MD_DTL_DRV_1.1 */
/* PRQA S 0288 EOF *//* MD_DTL_LIN_3.1 */
/* PRQA S 3453 EOF *//* MD_DTL_LIN_19.7 */
/*******************************************************************************************/
/** @file    dtl_lin.c
**  @brief   Implementation of the LIN diagnostic transport layer
**
**           This file contains the Vector LIN transport layer implementation
**           corresponding to LIN specification 2.0. Due to the properties and requirements of LIN, the
**           transport layer is implemented as single connection and half duplex.
**
********************************************************************************************/

/*******************************************************************************************/
/** @page     dtl_lin_c_header Header information of dtl_lin.c
********************************************************************************************
*    @par      copyright
*    @verbatim
*
*    Copyright (c) 2014  Vector Informatik GmbH                 All rights reserved.
*
*    This software is copyright protected and proprietary to Vector Informatik GmbH.
*    Vector Informatik GmbH grants to you only those rights as set out in the
*    license conditions. All other rights remain with Vector Informatik GmbH.
*
*    @endverbatim
*********************************************************************************************
*    @par      Authors
*    @verbatim
*      Initials  Name                    Company
*      Wr        Hans Waaser             Vector Informatik GmbH
*      Svh       Sven Hesselmann         Vector Informatik GmbH
*      Ap        Andreas Pick            Vector Informatik GmbH
*      Bmo       Bastian Molkenthin      Vector Informatik GmbH
*    @endverbatim
*********************************************************************************************
*    @par      Revision History
*    @verbatim
*    Date         Ver       Author   Description
*    2004-08-30   1.00      Wr       First implementation
*    2004-09-01   1.01      Wr       ESCAN00009568: Missing if branch
*                                    ESCAN00009569: Maximum sequence number
*                                    ESCAN00009570: Support of all NAD
*                                    ESCAN00009571: Type of bDtlTimeoutTimerValue
*                           Svh      ESCAN00010316: First Frame handling in segmented transmission corrected (Master)
*                                    ESCAN00010318: First Frame handling in segmented transmission corrected (Slave)
*                           Wr       ESCAN00010466: Tp raw implementation added
*    2004-12-07   1.02      Wr       ESCAN00010527: Tp cooked reception aborted or data not copied
*                                    ESCAN00010647: Tp cooked enable reception with ld_receive_message
*                                    ESCAN00010725: Tp raw return value check of DTLGetRaw()
*    2005-01-17   1.03      Wr       ESCAN00010821: Tp raw next state compare value of DtlGetRaw()
*    2005-08-26   1.04      Svh      ESCAN00013006: Evaluation of the PCI type (SF, FF, CF) is not working correctly (TpLin_CookedMastEcu)
*                                    ESCAN00013033: Evaluation of the PCI type (SF, FF, CF) is not working correctly (TpLin_CookedSlavEcu)
*                                    ESCAN00012289: Tx Buffer has size of Rx Buffer
*                                    ESCAN00013244: Reduce code size of TpLin component
*                                    ESCAN00013274: Define LD_IN_PROCESS is given instead of LD_IN_PROGRESS
*                                    ESCAN00013275: TpLin reports an error after successful reception of a single frame
*                                    ESCAN00013284: Use new memory qualifier for all internal variables (TpLin_CookedMastEcu)
*                                    ESCAN00013305: Use new memory qualifier for all internal variables (TpLin_CookedSlavEcu)
*                                    ESCAN00013306: Use new memory qualifier for all internal variables (TpLin_RawMastEcu)
*                                    ESCAN00013326: Received First Frame (FF) is not ignored if length information (LEN) is 0x006 (TpLin_CookedMastEcu)
*                                    ESCAN00013327: Received First Frame (FF) is not ignored if length information (LEN) is 0x006 (TpLin_CookedSlavEcu)
*    2005-09-28   1.05      Svh      ESCAN00013688: Change interface between LIN driver and DTL depending on the number of channels in the LIN driver
*                                    ESCAN00014052: Findings of MISRA check and code review have to be included
*                                    ESCAN00014055: Remove return value of function ApplLinDtlRxError()
*    2005-11-09   1.06      Svh      ESCAN00014234: Timeout observation should also be handled in case of wait for tx confirmation
*    2005-12-13   1.07      Svh      ESCAN00014641: Compiler error because of an unknown define if LIN API of TpLin is used
*    2006-02-14   1.08      Ap       ESCAN00015343: [TpLin_CookedMasterECU] LIN Master multi channel support
*                                    ESCAN00015344: [TpLin_RawMasterECU]    LIN Master multi channel support
*    2007-01-17   1.09      Ap       ESCAN00018979: Support for LIN 2.1 TP raw extensions
*                                                    * LIN API making use of ld_init instead of DtlInit
*                                                    * New/changed return values for ld_raw_tx_status and ld_raw_rx_status
*                                                    * Interleaved functional requests from backbone bus
*    2007-03-12   1.10      Ap       ESCAN00019772: Support for LIN 2.1 TP cooked extensions
*                                    ESCAN00019891: RAW API: ld_get_raw() or DtlGetRaw() might return invalid data after frame error on SlaveResponse
*    2007-04-19   1.11      Ap       ESCAN00020347: Separate rx and tx state engine for cooked TP
*                                    ESCAN00020399: Allow ld_receive_message request for response when still in transmit mode
*                                    ESCAN00020400: Functional request handled in LIN 2.1 slave node
*    2007-06-14   1.12      Ap       ESCAN00020634: LIN API: Call of DtlInitPowerOn() not conform to LIN specification
*                           Ap       ESCAN00020879: Unexpected Consecutive Frame is not ignored
*    2007-06-21   1.13      Ap       ESCAN00021154: ld_raw_tx_status() return value wrong when functional request pending
*    2007-09-24   1.14      Ap       ESCAN00022467: Compile error due to type mismatch when LIN API is used
*    2008-03-01   1.15      Ap       ESCAN00019479: Missing error indication in case of a Rx queue overrun
*                                    ESCAN00024894: Valid diagnostic request not aswered slave node
*    2008-04-02   1.16      Svh      ESCAN00025726: Optimization of source code to reduce resource consumption
*    2008-06-16   1.17      Ap       ESCAN00027550: A multiframe reception abort is not reported to diagnostic component
*    2008-10-27   1.18      Ap       ESCAN00030851: Invalid PCI is not ignored but aborts ongoing transmission
*                                    ESCAN00030911: Return value variable bRetValue may not have been initialized
*    2009-02-24   1.19      Ap       ESCAN00033092: Missing variable declaration leads to compile error
*                                    ESCAN00033363: LIN 2.1 functional addressing with incorrect transmit data
*    2009-06-09   1.20      Ap       ESCAN00034265: Inconsistent transmission status when receiving a response while a transmit request is pending
*                                    ESCAN00035619: SingleFrame or FirstFrame reception during running reception does not start reception with new SF or FF (Master)
*    2009-06-18   1.21      Ap       ESCAN00035838: API extensiion to allow SF/FF notification during running reception
*    2010-01-18   1.22.00   Ap       ESCAN00039014: Functional request quit ongoing physical connection
*    2010-08-27   1.23.00   Ap       ESCAN00043744: SlaveResp frame is always rejected in case LIN driver feature "Enable SlaveResp Header Suppression" is active
*                                    ESCAN00044412: Add LIN bootoader specific code
*                                    ESCAN00043165: Compiler error "wDtlCurrentBufferIndex undefined" if "Tx Single frame only" and "Rx Single frame only" are activated.
*    2010-11-26   1.24.00   Ap       ESCAN00047228: Incorrect pointer definition
*    2011-06-14   1.25.00   Bmo      ESCAN00051600: Compile Error: Incorrect macro LinGetConfiguredNAD
*    2011-08-29   1.26.00   vadhda   ESCAN00048344: Compiler warning "Conversion in argument"
*                                    ESCAN00048345: Compiler warning "Precision lost"
*    2012-12-13   1.27.00   Ap       ESCAN00063602: Support mixed MSR and CBD configurations in LinTp component
*    2013-03-01   1.28.00   Ap       ESCAN00065523: Support for secondary NAD
*    2013-06-25   1.28.01   Bmo      ESCAN00068332: Add memory sections for FBL
*    2013-10-15   1.29.00   Bmo      ESCAN00071109: Add interface to support response pending frames feature of LinDiag
*    2014-01-10   1.29.01   Bmo      ESCAN00072864: Compiler warning: bRetValue may be used before being set
*                                    ESCAN00072868: Compiler error: get_pbLinDiagRcrRpBuffer not defined
*    2014-03-10   1.29.02   Bmo      ESCAN00074173: Slave response not notified if functional request is transmitted between physical request and response
*                                    ESCAN00074176: Adapt confirmation handling of functional requests
*    2014-03-18   1.29.03   Bmo      ESCAN00074356: Unexpected negative physical Tx confirmation if additional functional request cannot not be handled
*    2014-04-25   1.29.04   Ap       ESCAN00075233: Compiler error: dtllinchannel undefined
*    2014-07-07   1.29.05   Ap       ESCAN00076839: Misra correction added
*    @endverbatim
*******************************************************************************************/

#include "dtl_inc.h"

/*******************************************************************************************
* Version Check
********************************************************************************************/
#if( TPLIN_VERSION != 0x0129u )
 #error "DTL_LIN.C and DTL_LIN.H used in different versions, please check driver version!"
#endif
#if( TPLIN_RELEASE_VERSION != 0x05u )
 #error "DTL_LIN.C and DTL_LIN.H used in different versions, please check bugfix version!"
#endif


#if ( LIN_DRIVER_TP_VERSION < 0x0206u )
 #error "LIN driver does not match TP API. Older TP version or later LIN driver required."
#endif

#if ( DTL_LINDLL_VERSION < 0x0202u )
 #error "TPLIN DLL is not working with this version of TPLIN implmentation. Please use newer TPLIN DLL Version!"
#endif


/*******************************************************************************************/
/* Global constants with DTL main and subversion                                           */
/*******************************************************************************************/
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kDtlLinMainVersion    = (vuint8)(( TPLIN_VERSION & 0xFF00U ) >> 8);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kDtlLinSubVersion     = (vuint8)(  TPLIN_VERSION & 0x00FFU );
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kDtlLinReleaseVersion = (vuint8)(  TPLIN_RELEASE_VERSION );


/*******************************************************************************************
* Configuration Check
********************************************************************************************/
 #if defined ( DTL_APISTYLE_LIN )
  #error "LIN API not supported for slave ECU. Check configuration."
 #endif

#if defined (DTL_APISTYLE_LIN)
#elif defined (DTL_APISTYLE_VECTOR)
#else
 #error "DTL API style not selected. Check dtl_cfg.h!"
#endif


#if defined (DTL_ENABLE_RCR_RP_SUPPORT)
# if defined (DTL_APISTYLE_LIN)
#  error "Response pending frames not supported for LIN API style. Check configuration."
# endif
#endif

#if defined ( DTL_ENABLE_DEBUG )
 /* For development reasons it is possible to enable the internal debug                    */
 /* mechanism of the transport layer and handle all fatal errors by a                      */
 /* callback function. So malfunctions could be detected not                               */
 /* only while compile time but also while runtime.                                        */

 /* condition depends on runtime */
  #define DtlAssertDynamic(c,p,e)                if(!(p)){ApplDtlFatalError(e);}  /* PRQA S 3412 *//* MD_DTL_LIN_19.4A */
 /* condition is always true */
  #define DtlAssertStatic(c,e)                   ApplDtlFatalError(e)
 /* Variables used to check the correct integration */

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 bInitCheck;

 #define kInitPattern                            ((vuint8) 0x53u)

#else
 /*lint +e750*/
 /* disable PC-lint info 750: "local macro 'XXX' not referenced" */

 #define DtlAssertDynamic(c,p,e)
 #define DtlAssertStatic(c,e)

 /* enable PC-lint info 750: "local macro 'XXX' not referenced" */
 /*lint -e750*/
#endif /* DTL_ENABLE_DEBUG */

#if defined (DTL_PROCESSING_COOKED)
 #if !defined (kDtlTimerTicsMax)
  #error "maximum value of timer tics not defined. Check dtl_cfg.h!"
 #endif
#endif
/*******************************************************************************************
* Compatibility defines
********************************************************************************************/


 /* single channel defines for interface between DTL and application */
 #define DTL_I_CHANNEL_PARA_FIRST
 #define DTL_I_CHANNEL_PARA_ONLY
 #define DTL_I_CHANNEL_TYPE_FIRST
 #define DTL_I_CHANNEL_TYPE_ONLY                 void /* PRQA S 3460 *//* MD_DTL_LIN_19.4B */

 /* single channel defines for interface between DTL and application, if LIN API has fixed channel parameter */
 #define DTL_I_CA_CHANNEL_PARA_FIRST
 #define DTL_I_CA_CHANNEL_PARA_ONLY
 #define DTL_I_CA_CHANNEL_TYPE_FIRST
 #define DTL_I_CA_CHANNEL_TYPE_ONLY              void /* PRQA S 3460 *//* MD_DTL_LIN_19.4B */

 #if defined (LIN_APITYPE_INDEXED)

  /* single channel defines for interface between LIN driver and DTL */
  /* DTL is single channel, but LIN is indexed channel, so interface between DTL and LIN must be indexed */
  #define DTL_LIN_I_CHANNEL_PARA_FIRST           0,                  /* The DTL is fixed on channel 0 of the LIN driver */
  #define DTL_LIN_I_CHANNEL_PARA_ONLY            0                   /* The DTL is fixed on channel 0 of the LIN driver */
  #define DTL_LIN_I_CHANNEL_TYPE_FIRST           vuint8 dtllinchannel,
  #define DTL_LIN_I_CHANNEL_TYPE_ONLY            vuint8 dtllinchannel

  /* single channel defines for interface between LIN driver and DTL, if LIN API has fixed channel parameter */
  #define DTL_LIN_I_CA_CHANNEL_PARA_FIRST        0,
  #define DTL_LIN_I_CA_CHANNEL_PARA_ONLY         0
  #define DTL_LIN_I_CA_CHANNEL_TYPE_FIRST        vuint8 lincachannel,
  #define DTL_LIN_I_CA_CHANNEL_TYPE_ONLY         vuint8 lincachannel

 #else

  /* single channel defines for interface between LIN driver and DTL */
  #define DTL_LIN_I_CHANNEL_PARA_FIRST
  #define DTL_LIN_I_CHANNEL_PARA_ONLY
  #define DTL_LIN_I_CHANNEL_TYPE_FIRST
  #define DTL_LIN_I_CHANNEL_TYPE_ONLY            void /* PRQA S 3460 *//* MD_DTL_LIN_19.4B */

  /* single channel defines for interface between LIN driver and DTL, if LIN API has fixed channel parameter */
  #define DTL_LIN_I_CA_CHANNEL_PARA_FIRST
  #define DTL_LIN_I_CA_CHANNEL_PARA_ONLY
  #define DTL_LIN_I_CA_CHANNEL_TYPE_FIRST
  #define DTL_LIN_I_CA_CHANNEL_TYPE_ONLY         void /* PRQA S 3460 *//* MD_DTL_LIN_19.4B */

  #if defined ( DTL_APISTYLE_VECTOR )
   #define lincachannel                          0
  #endif

  #define dtllinchannel                          0

 #endif

#define kDtlStateIdle                            ((vuint8) 0x00u)

#if defined (DTL_PROCESSING_COOKED)
/* Current state of the transport layer */
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 bDtlTpTxState;
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 bDtlTpRxState;
  #define get_bDtlTpTxState(c)                      (bDtlTpTxState)
  #define set_bDtlTpTxState(c, val)                 (bDtlTpTxState = (val))
  #define get_bDtlTpRxState(c)                      (bDtlTpRxState)
  #define set_bDtlTpRxState(c, val)                 (bDtlTpRxState = (val))
  #define clr_bDtlTpTxState(c)                      (bDtlTpTxState = kDtlStateIdle)
  #define clr_bDtlTpRxState(c)                      (bDtlTpRxState = kDtlStateIdle)
  #define clr_bDtlTpState(c)                        (bDtlTpTxState = kDtlStateIdle); \
                                                    (bDtlTpRxState = kDtlStateIdle) /* PRQA S 3412 *//* MD_DTL_LIN_19.4B */
 #if ! defined ( DTL_ENABLE_RX_SINGLE_FRAME_ONLY )
  #define kDtlStateRxWaitCF                      ((vuint8) 0x01u)
 #endif
 #define kDtlStateTxWaitStartTransm              ((vuint8) 0x03u)
 #define kDtlStateTxWaitSFConf                   ((vuint8) 0x04u)
 #if ! defined ( DTL_ENABLE_TX_SINGLE_FRAME_ONLY )
  #define kDtlStateTxWaitFFConf                  ((vuint8) 0x05u)
  #define kDtlStateTxWaitCFTransm                ((vuint8) 0x06u)
  #define kDtlStateTxWaitCFConf                  ((vuint8) 0x07u)
 #endif
#endif

#if defined (DTL_PROCESSING_COOKED)
/* Parameters of the current TP connection */
V_MEMRAM0 static V_MEMRAM1 vuint8  V_MEMRAM2  bDtlCurrentAddress;
  #if (! defined ( DTL_ENABLE_TX_SINGLE_FRAME_ONLY )) || (! defined ( DTL_ENABLE_RX_SINGLE_FRAME_ONLY ))
V_MEMRAM0 static V_MEMRAM1 vuint16 V_MEMRAM2  wDtlCurrentBufferIndex;
V_MEMRAM0 static V_MEMRAM1 vuint8  V_MEMRAM2  bDtlNextSequenceNr;
  #endif
V_MEMRAM0 static V_MEMRAM1 vuint16 V_MEMRAM2  wDtlRemainingLength;
  #if defined (DTL_ECUTYPE_SLAVE)
   #if defined (DTL_ENABLE_RCR_RP_SUPPORT)
V_MEMRAM0 static V_MEMRAM1 vuint8  V_MEMRAM2  bDtlResponsePendingFlag;
   #endif
  #endif
  #define get_bDtlRxCopyMode(c)                  (bDtlRxCopyMode)
  #define set_bDtlRxCopyMode(c, val)             (bDtlRxCopyMode = (val))
  #define get_wDtlCurrentBufferIndex(c)          (wDtlCurrentBufferIndex)
  #define set_wDtlCurrentBufferIndex(c, val)     (wDtlCurrentBufferIndex = (val))
  #define get_bDtlCurrentAddress(c)              (bDtlCurrentAddress)
  #define set_bDtlCurrentAddress(c, val)         (bDtlCurrentAddress = (val))
  #define get_bDtlNextSequenceNr(c)              (bDtlNextSequenceNr)
  #define set_bDtlNextSequenceNr(c, val)         (bDtlNextSequenceNr = (val))
  #define get_wDtlRemainingLength(c)             (wDtlRemainingLength)
  #define set_wDtlRemainingLength(c, val)        (wDtlRemainingLength = (val))
  #define get_bDtlGetSecondaryNAD(c)             (bDtlSecondaryNAD)
  #if defined (DTL_ECUTYPE_SLAVE)
   #if defined (DTL_ENABLE_RCR_RP_SUPPORT)
    #define get_bDtlResponsePendingFlag(c)       (bDtlResponsePendingFlag)
    #define set_bDtlResponsePendingFlag(c, val)  (bDtlResponsePendingFlag = (val))
   #endif
  #endif

  #define DTL_VOID_CAST
  /* in slave case, the diag buffers are declared in the header file */
  #define get_pbLinDiagBuffer(c)                 (pbLinDiagBuffer)
  #define set_pbLinDiagBuffer(c, val)            (pbLinDiagBuffer = (val))
  #if defined (DTL_ENABLE_RCR_RP_SUPPORT)
   #define get_pbLinDiagRcrRpBuffer(c)           (pbLinDiagRcrRpBuffer)
  #endif
#endif /* DTL_PROCESSING_COOKED */

#if defined (DTL_PROCESSING_COOKED)
/*******************************************************************************************/
/*  DTL Timeout timer                                                                      */
/*******************************************************************************************/
  #if (kDtlTimerTicsMax > 255)
V_MEMRAM0 static V_MEMRAM1 vuint16 V_MEMRAM2  bDtlTimeoutTimerValue;
  #else
V_MEMRAM0 static V_MEMRAM1 vuint8  V_MEMRAM2  bDtlTimeoutTimerValue;
  #endif

  #define Start_DtlTimeout_RxSTmax(c)            (bDtlTimeoutTimerValue = kDtlRxStMaxTimeout)

  #define Start_DtlTimeout_TxPending(c)          (bDtlTimeoutTimerValue = kDtlTxReqPendingTimeout)
  #define Start_DtlTimeout_TxSTmax(c)            (bDtlTimeoutTimerValue = kDtlTxStMaxTimeout)
  #define Start_DtlTimeout_TxConfirm(c)          (bDtlTimeoutTimerValue = kDtlTxConfirmTimeout)
  #define Cancel_DtlTimeoutTimer(c)              (bDtlTimeoutTimerValue = 0)
  #define get_DtlTimeoutTimerValue(c)            (bDtlTimeoutTimerValue)
  #define dec_DtlTimeoutTimerValue(c)            (bDtlTimeoutTimerValue--)
#endif /* DTL_PROCESSING_COOKED */


/*******************************************************************************************/
/*   function prototypes of internal used functions                                        */
/*******************************************************************************************/


/*******************************************************************************************/
/*******************************************************************************************/
/**    Internal functions of the Dtl                                                      **/
/*******************************************************************************************/
/*******************************************************************************************/

/*******************************************************************************************/
/*******************************************************************************************/
/**    Common API functions                                                               **/
/*******************************************************************************************/
/*******************************************************************************************/

#if defined ( DTL_APISTYLE_VECTOR )
/*******************************************************************************************/
/*    API FUNCTION:  DtlInitPowerOn                                                        */
/*******************************************************************************************/
/* for documentation, see dtl_lin.h                                                        */

void DtlInitPowerOn(void)
{
  #if defined ( DTL_APISTYLE_VECTOR )
  DtlInit(DTL_I_CHANNEL_PARA_ONLY);
  #else
  ld_init(dtllinchannel);
  #endif
 #if defined ( DTL_ENABLE_DEBUG )
  /* Init check */
  bInitCheck = kInitPattern;
 #endif
}
#endif

/*******************************************************************************************/
/*    API FUNCTION:  DtlInit / ld_init                                                     */
/*******************************************************************************************/
/* for documentation, see dtl_lin.h                                                        */

#if defined ( DTL_APISTYLE_VECTOR )
void DtlInit(DTL_I_CHANNEL_TYPE_ONLY)
#else
void ld_init (vuint8 dummy)  /* PRQA S 1330 *//* MD_DTL_LIN_16.4 */
#endif
{
 #if defined (DTL_APISTYLE_LIN)
  #if defined ( DTL_ENABLE_DEBUG )
  /* Init check */
  bInitCheck = kInitPattern;
  #endif
 #endif

#if defined (DTL_PROCESSING_COOKED)
  /* set NAD to invalid value to indicate no previous reception */
  set_bDtlCurrentAddress(dtllinchannel, 0x00u);
  #if defined (DTL_ENABLE_RCR_RP_SUPPORT)
  set_bDtlResponsePendingFlag(dtllinchannel, 0x00u);
  #endif
  clr_bDtlTpState(dtllinchannel);
 #if (! defined ( DTL_ENABLE_TX_SINGLE_FRAME_ONLY )) || (! defined ( DTL_ENABLE_RX_SINGLE_FRAME_ONLY ))
  set_wDtlCurrentBufferIndex(dtllinchannel, 0x00u);
 #endif
  Cancel_DtlTimeoutTimer(dtllinchannel);
#endif

}

#if defined (DTL_PROCESSING_COOKED)
/*******************************************************************************************/
/*    API FUNCTION:  DtlTimerTask                                                          */
/*******************************************************************************************/
/* for documentation, see dtl_lin.h                                                        */

void DtlTimerTask(DTL_I_CHANNEL_TYPE_ONLY)
{
  DtlAssertDynamic(dtllinchannel, (bInitCheck==kInitPattern), kDtlErrorNotInitialized); /* PRQA S 3109 *//* MD_DTL_LIN_14.3 */

  /* Disable UART  interrupts */
  LinStartTaskSync(DTL_LIN_I_CHANNEL_PARA_ONLY);

  /* observation of ST max timeout and Tx pending Timeout */
  if (get_DtlTimeoutTimerValue(dtllinchannel) != 0x00u)
  {
    dec_DtlTimeoutTimerValue(dtllinchannel);
    if (get_DtlTimeoutTimerValue(dtllinchannel) == 0x00u)
    {
      /* Timeout timer expired */
      if (get_bDtlTpTxState(dtllinchannel) > kDtlStateIdle)
      {
        /* TP is in Tx mode, but no corresponding confirmation or error indication function received. */
        clr_bDtlTpTxState(dtllinchannel);
 #if defined (DTL_APISTYLE_VECTOR)
        clr_bDtlTpRxState(dtllinchannel);
        (void)ApplDtlTxConfirmation(DTL_I_CHANNEL_PARA_FIRST kDtlTxResult_FAILED);
 #else
  #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
        set_bLdTxStatus(dtllinchannel, LD_N_AS_TIMEOUT);
  #else
        set_bLdTxStatus(dtllinchannel, LD_FAILED);
  #endif
        if (get_bDtlTpRxState(dtllinchannel) != kDtlStateIdle)
        { /* ld_receive_message pending - set error indication */
          set_bLdRxStatus(dtllinchannel, LD_FAILED);
          clr_bDtlTpRxState(dtllinchannel);
        }
 #endif
      }
      else if (get_bDtlTpRxState(dtllinchannel) > kDtlStateIdle)
      {
        /* Rx timeout. Stop reception and inform diagnostic application. */
        clr_bDtlTpState(dtllinchannel);
 #if defined (DTL_APISTYLE_VECTOR)
        DTL_VOID_CAST ApplDtlRxMsgIndication(DTL_I_CHANNEL_PARA_FIRST kDtlRxResult_FAILED);
 #else
  #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
        set_bLdRxStatus(dtllinchannel, LD_N_CR_TIMEOUT);
  #else
        set_bLdRxStatus(dtllinchannel, LD_FAILED);
  #endif
 #endif
      }
      else
      {
        /* Nothing to do */
      }
    }
  }
  /* restore UART (TIMER, ...) interrupts */
  LinEndTaskSync(DTL_LIN_I_CHANNEL_PARA_ONLY);
}

 #if defined(DTL_ECUTYPE_SLAVE)
/*******************************************************************************************/
/*    API FUNCTION:  DtlGetCurrentNAD                                                      */
/*******************************************************************************************/
vuint8 DtlGetCurrentNAD(void)
{
  /* Return the NAD which is currently requested */
  return get_bDtlCurrentAddress(dtllinchannel);
}

  #if defined (DTL_ENABLE_SECONDARY_NAD)
/*******************************************************************************************/
/*    API FUNCTION:  DtlSetCurrentNAD                                                      */
/*******************************************************************************************/
void   DtlSetCurrentNAD(vuint8 bCurrentNAD)
{
  set_bDtlCurrentAddress(dtllinchannel, bCurrentNAD);
}
  #endif
 #endif


#endif /* DTL_PROCESSING_COOKED */

#if defined (DTL_PROCESSING_COOKED)
/*******************************************************************************************/
/*******************************************************************************************/
/**    Cooked API functions                                                               **/
/*******************************************************************************************/
/*******************************************************************************************/

/*******************************************************************************************/
/** @par  Receive Channel
 *******************************************************************************************/

 #if defined (DTL_APISTYLE_LIN)
/*******************************************************************************************/
/*    API FUNCTION:  ld_rx_status                                                          */
/*******************************************************************************************/
/* for documentation, see dtl_lin.h                                                        */

vuint8 ld_rx_status (vuint8 lincachannel) /* PRQA S 1330 *//* MD_DTL_LIN_16.4 */
{
   #if defined (V_ENABLE_USE_DUMMY_STATEMENT)
  lincachannel = lincachannel; /* avoid compiler warnings */
   #endif
  return get_bLdRxStatus(lincachannel);
}

/*******************************************************************************************/
/*    API FUNCTION:  ld_receive_message                                                    */
/*******************************************************************************************/
/* for documentation, see dtl_lin.h                                                        */

void ld_receive_message (vuint8 lincachannel, vuint16* length, vuint8* NAD, vuint8* data) /* PRQA S 1330 *//* MD_DTL_LIN_16.4 */
{
  DtlAssertDynamic(lincachannel, (bInitCheck==kInitPattern), kDtlErrorNotInitialized); /* PRQA S 3109 *//* MD_DTL_LIN_14.3 */

  /* Request the reception of a message */
  /* Save the pointer to the address information */
  set_pbLocalNAD(lincachannel, NAD);
  /* Save the pointer to the data buffer */
  set_pbLinDiagBuffer(lincachannel, data);

  /* Enable Reception */
  set_bDtlTpRxState(lincachannel, kDtlStateRxWaitStartRecept);
  set_bLdRxStatus(lincachannel, LD_IN_PROGRESS);
  if (get_bDtlTpTxState(lincachannel) == kDtlStateIdle)
  { /* transmission not pending - start timeout observation now */
    Start_DtlTimeout_RxPending(lincachannel);
  }
}
 #endif


/*******************************************************************************************/
/** @par  Transmit Channel
 *
 *******************************************************************************************/
 #if defined (DTL_APISTYLE_LIN)
/*******************************************************************************************/
/*    API FUNCTION:  ld_tx_status                                                          */
/*******************************************************************************************/
/* for documentation, see dtl_lin.h                                                        */

vuint8 ld_tx_status (vuint8 lincachannel) /* PRQA S 1330 *//* MD_DTL_LIN_16.4 */
{
   #if defined (V_ENABLE_USE_DUMMY_STATEMENT)
  lincachannel = lincachannel; /* avoid compiler warnings */
   #endif
  return get_bLdTxStatus(lincachannel);
}
 #endif

/*******************************************************************************************/
/*    API FUNCTION:  ld_send_message / DtlTxSendMessage                                    */
/*******************************************************************************************/
/* for documentation, see dtl_lin.h                                                        */

 #if defined (DTL_APISTYLE_VECTOR)
vuint8 DtlTxSendMessage(vuint16 wLength)
 #else
void ld_send_message (vuint8 lincachannel, vuint16 wLength, vuint8 bAddressInfo, vuint8*  pbMsgData) /* PRQA S 1330 *//* MD_DTL_LIN_16.4 */
 #endif
{
 #if defined (DTL_APISTYLE_VECTOR)
  vuint8 bRetValue;
 #endif

  DtlAssertDynamic(lincachannel, (bInitCheck==kInitPattern), kDtlErrorNotInitialized); /* PRQA S 3109 *//* MD_DTL_LIN_14.3 */
 #if defined ( DTL_ENABLE_TX_SINGLE_FRAME_ONLY )
  DtlAssertDynamic(lincachannel, (wLength<=6), kDtlErrorParamValue); /* PRQA S 3109 *//* MD_DTL_LIN_14.3 */
 #else
  DtlAssertDynamic(lincachannel, (wLength<=4095), kDtlErrorParamValue); /* PRQA S 3109 *//* MD_DTL_LIN_14.3 */
 #endif

  /* Disable UART  interrupts */
  LinStartTaskSync(DTL_LIN_I_CA_CHANNEL_PARA_ONLY);

  if(get_bDtlTpTxState(lincachannel) == kDtlStateIdle)
  {
    /* Handle request */
    set_bDtlTpTxState(lincachannel, kDtlStateTxWaitStartTransm);
    Start_DtlTimeout_TxPending(lincachannel);

    /* Application is responsible to respect maximum length of 4095 */
    /* Application is responsible to respect maximum length of 6 if DTL_ENABLE_TX_SINGLE_FRAME_ONLY is set */
    set_wDtlRemainingLength(lincachannel, wLength);

  #if defined (DTL_ENABLE_SECONDARY_NAD)
    /* use requested NAD or NAD which was set by the applicaton */
  #else
    /* always answer on a request with the node specific NAD - even if request is broadcast */
    set_bDtlCurrentAddress(lincachannel, LinGetConfiguredNAD(lincachannel));
  #endif
 #if defined (DTL_APISTYLE_VECTOR)
    bRetValue           = kDtlTxState_ACCEPTED;
 #else
    set_bLdTxStatus(lincachannel, LD_IN_PROGRESS);
 #endif
  }
 #if defined (DTL_APISTYLE_VECTOR)
  else
  {
    /* DTL currently active, reject transmission request */
    bRetValue             = kDtlTxState_REJECTED;
  }
 #endif
  /* restore UART (TIMER, ...) interrupts */
  LinEndTaskSync(DTL_LIN_I_CA_CHANNEL_PARA_ONLY);

 #if defined (DTL_APISTYLE_VECTOR)
  return bRetValue;
 #endif
}

/*******************************************************************************************/
/*    API FUNCTION:  DtlTxSendRcrRpMessage                                                 */
/*******************************************************************************************/
/* for documentation, see dtl_lin.h                                                        */

 #if defined (DTL_APISTYLE_VECTOR)
  #if defined (DTL_ECUTYPE_SLAVE)
   #if defined (DTL_ENABLE_RCR_RP_SUPPORT)
vuint8 DtlTxSendRcrRpMessage(vuint8 bLength)
{
  vuint8 bRetValue;

  /* Disable UART  interrupts */
  LinStartTaskSync(DTL_LIN_I_CA_CHANNEL_PARA_ONLY);
  /* use DtlTxSendMessage to avoid code duplication, however the interrupts are disabled / restored twice */
  bRetValue = DtlTxSendMessage(bLength);
  if (bRetValue == kDtlTxState_ACCEPTED)
  {
    set_bDtlResponsePendingFlag(lincachannel, 1);
  }
  /* restore UART (TIMER, ...) interrupts */
  LinEndTaskSync(DTL_LIN_I_CA_CHANNEL_PARA_ONLY);

  return bRetValue;
}
   #endif /* DTL_ENABLE_RCR_RP_SUPPORT */
  #endif /* DTL_ECUTYPE_SLAVE */
 #endif /* DTL_APISTYLE_VECTOR */
#endif /* DTL_PROCESSING_COOKED */


/*******************************************************************************************/
/*******************************************************************************************/
/**    Diagnostic dispatcher callback functions                                           **/
/*******************************************************************************************/
/*******************************************************************************************/


#if defined (DTL_ECUTYPE_SLAVE)
/*******************************************************************************************/
/*    CALLBACK FUNCTION:  ApplLinDtlConfirmDiagFrameResp                                   */
/*******************************************************************************************/
/* for documentation, see drv_lin_tp.h                                                     */

vuint8 ApplLinDtlConfirmDiagFrameResp( void )
{ /* confirm transmission of SlaveResp */
  vuint8 bRetValue;

 #if ! defined ( DTL_ENABLE_TX_SINGLE_FRAME_ONLY )
  if( (get_bDtlTpTxState(dtllinchannel) == kDtlStateTxWaitStartTransm) ||
      (get_bDtlTpTxState(dtllinchannel) == kDtlStateTxWaitCFTransm) )
 #else
  if( get_bDtlTpTxState(dtllinchannel) == kDtlStateTxWaitStartTransm )
 #endif
  {
    bRetValue = kLinTpFrameRespConfirm;
  }
  else
  {
    bRetValue = kLinTpFrameRespReject;
  }
  return bRetValue;
}
#endif


/*******************************************************************************************/
/*    CALLBACK FUNCTION:  ApplLinDtlPrecopyFct                                             */
/*******************************************************************************************/
/* for documentation, see drv_lin_tp.h                                                     */

vuint8 ApplLinDtlPrecopyFct(DTL_LIN_I_CHANNEL_TYPE_FIRST vuint8* MessagePtr)
{ /* diag frame received */
#if defined (DTL_PROCESSING_COOKED)
/* Copy mode of the Rx connection */
V_MEMRAM0 static V_MEMRAM1 vuint8  V_MEMRAM2  bDtlRxCopyMode;
#endif
  vuint8 bRetValue;
#if defined (DTL_PROCESSING_COOKED)
  vuint16 wLength;
#endif

#if defined (DTL_PROCESSING_COOKED)
  /* Address, format and sequence check  */

  /* Address check. Sleep frame address is filtered by the driver. */
  /* The format of frames with address >= 0x80 is not defined and can not be handled by the dtl */

 #if defined (DTL_ENABLE_ALL_NAD)
 #else
  #if defined (DTL_ENABLE_SECONDARY_NAD)
  if((MessagePtr[0] < 0x80u) || (MessagePtr[0] == get_bDtlGetSecondaryNAD(dtllinchannel)) )
  #else
  if(MessagePtr[0] < 0x80u)
  #endif
 #endif
  {

 #if defined (DTL_ECUTYPE_SLAVE)
    if( (MessagePtr[0] == LinGetConfiguredNAD(dtllinchannel)) ||
  #if defined (DTL_ENABLE_SECONDARY_NAD)
        (MessagePtr[0] == get_bDtlGetSecondaryNAD(dtllinchannel)) ||
  #endif
        (MessagePtr[0] == kDtlBroadcastNAD) )
 #endif
    {
      /* Frames are handled by the TP */

      /* Check frame type for SF, FF or CF  */
      switch (MessagePtr[1] & 0xF0u)
      {
        case 0x00u:
          /* Single frame received */
          /* check for valid length information*/
          if ( (MessagePtr[1] > 0x00u) &&
               (MessagePtr[1] <= 0x06u) )
          {
 #if ! defined ( DTL_ENABLE_RX_SINGLE_FRAME_ONLY )
            /* Check current TP state */
            if(get_bDtlTpRxState(dtllinchannel) == kDtlStateRxWaitCF)
            {
              /* Indicate error and restart communication */
              Cancel_DtlTimeoutTimer(dtllinchannel);
              ApplDtlRxMsgIndication(DTL_I_CHANNEL_PARA_FIRST kDtlRxResult_FAILED);
              clr_bDtlTpState(dtllinchannel);
            }
 #endif /* ! DTL_ENABLE_RX_SINGLE_FRAME_ONLY */
            if (get_bDtlTpTxState(dtllinchannel) != kDtlStateIdle)
            { /* SF received in Tx mode - stop transmission or response and proceed with request */
              /* Indicate error and restart communication */
              Cancel_DtlTimeoutTimer(dtllinchannel);
              clr_bDtlTpState(dtllinchannel);
              (void)ApplDtlTxConfirmation(DTL_I_CHANNEL_PARA_FIRST kDtlTxResult_FAILED);
            }
            set_bDtlRxCopyMode(dtllinchannel, ApplDtlRxStartIndication(DTL_I_CHANNEL_PARA_FIRST MessagePtr[0], (MessagePtr[1]&0x0Fu))); /* PRQA S 0850 *//* MD_DTL_LIN_19.8 */


            if(( get_bDtlRxCopyMode(dtllinchannel) == kDtlStart_RxCopy ) ||
              ( get_bDtlRxCopyMode(dtllinchannel) == kDtlStart_RxNoCopy ))
            {
  #if defined (DTL_ENABLE_SECONDARY_NAD)
              if (MessagePtr[0] == kDtlBroadcastNAD)
              {
                /* response with node specific NAD by default */
                set_bDtlCurrentAddress(dtllinchannel, LinGetConfiguredNAD(dtllinchannel));
              }
              else
              {
                /* store requested NAD for response transmission (default) */
                set_bDtlCurrentAddress(dtllinchannel, MessagePtr[0]);
              }
  #endif
              /* Receive Request and copy it to data buffer */
              /* For optimization, copy always 6 byte */

              /* For Slave, also in case kDtlStart_RxNoCopy, the first frame is copied
              to be able to use the service identifier.   */
              VStdMemCpyRamToRam(get_pbLinDiagBuffer(dtllinchannel), &(MessagePtr[2]), 6);

              ApplDtlRxMsgIndication(DTL_I_CHANNEL_PARA_FIRST kDtlRxResult_COMPLETED);
              bRetValue = kDtlRxCompleteEnableTx;
            }
            else
            {
              /* Ignore frame and wait for next request*/
              bRetValue = kDtlRxCompleteNoTx;
            }
          }
          else
          {
            /* Single frames (SF) with invalid length information are ignored */
            if (get_bDtlTpRxState(dtllinchannel) != kDtlStateIdle)
            { /* wait for next CF */
              bRetValue = kDtlRxExpectNextFrame;
            }
            else if (get_bDtlTpTxState(dtllinchannel) != kDtlStateIdle)
            { /* wait for next transmission */
              bRetValue = kDtlRxCompleteEnableTx;
            }
            else
            { /* quit processing of invalid SF - no further handling required */
              bRetValue = kDtlRxCompleteNoTx;
            }
          }
        break;
        case 0x10u:
          /* First frame received */
          wLength = (vuint16)(((vuint16)(MessagePtr[1]& 0x0Fu)<<8)|MessagePtr[2]);

          /* check for valid length information, valid length must be greater then 0x06 */
          if( wLength > 0x06u)
          {
            Cancel_DtlTimeoutTimer(dtllinchannel);
 #if ! defined ( DTL_ENABLE_RX_SINGLE_FRAME_ONLY )
            /* Check current TP state */
            if(get_bDtlTpRxState(dtllinchannel) == kDtlStateRxWaitCF)
            {
              /* Indicate error and restart communication */
              Cancel_DtlTimeoutTimer(dtllinchannel);
              ApplDtlRxMsgIndication(DTL_I_CHANNEL_PARA_FIRST kDtlRxResult_FAILED);
              clr_bDtlTpState(dtllinchannel);
            }
 #endif /* ! DTL_ENABLE_RX_SINGLE_FRAME_ONLY */

            if (get_bDtlTpTxState(dtllinchannel) != kDtlStateIdle)
            { /* FF received in Tx mode - stop transmission or response and proceed with request */
              /* Indicate error and restart communication */
              Cancel_DtlTimeoutTimer(dtllinchannel);
              clr_bDtlTpState(dtllinchannel);
              (void)ApplDtlTxConfirmation(DTL_I_CHANNEL_PARA_FIRST kDtlTxResult_FAILED);
            }

            set_bDtlRxCopyMode(dtllinchannel, ApplDtlRxStartIndication(DTL_I_CHANNEL_PARA_FIRST MessagePtr[0], wLength)); /* PRQA S 0850 *//* MD_DTL_LIN_19.8 */

  #if defined ( DTL_ENABLE_RX_SINGLE_FRAME_ONLY )
            /* if only RX Single Frames are supported, any length with more than 6 bytes must be ignored */
            DtlAssertDynamic(lincachannel, kDtlStart_Ignore == get_bDtlRxCopyMode(dtllinchannel), kDtlErrorInvalidReturnValue); /* PRQA S 3109 *//* MD_DTL_LIN_14.3 */
  #else /* ! DTL_ENABLE_RX_SINGLE_FRAME_ONLY */
            if(( get_bDtlRxCopyMode(dtllinchannel) == kDtlStart_RxCopy ) ||
              ( get_bDtlRxCopyMode(dtllinchannel) == kDtlStart_RxNoCopy ))
            {
            /* For Slave, also in case kDtlStart_RxNoCopy, the first frame is copied
              to be able to use the Service identifier.   */

              /* Receive Request and copy it to Data buffer */
              /* For optimization, copy always 5 byte */
              VStdMemCpyRamToRam(get_pbLinDiagBuffer(dtllinchannel), &(MessagePtr[3]), 5);

              /* Start ST timeout observation */
              Start_DtlTimeout_RxSTmax(dtllinchannel);
              /* Set new expected values */
              set_wDtlRemainingLength(dtllinchannel, wLength - 5);
              set_wDtlCurrentBufferIndex(dtllinchannel, 5);
              set_bDtlCurrentAddress(dtllinchannel, MessagePtr[0]);
              set_bDtlNextSequenceNr(dtllinchannel, 1);
              set_bDtlTpRxState(dtllinchannel, kDtlStateRxWaitCF);
              bRetValue               = kDtlRxExpectNextFrame;
            }
            else
  #endif /* ! DTL_ENABLE_RX_SINGLE_FRAME_ONLY */
            {
              /* Ignore Frame and wait for next request*/
              bRetValue = kDtlRxCompleteNoTx;
            }
          }
          else
          {
            /* First frames (FF) with invalid length information are ignored */
            if (get_bDtlTpRxState(dtllinchannel) != kDtlStateIdle)
            { /* wait for next CF */
              bRetValue = kDtlRxExpectNextFrame;
            }
            else if (get_bDtlTpTxState(dtllinchannel) != kDtlStateIdle)
            { /* wait for next transmission */
              bRetValue = kDtlRxCompleteEnableTx;
            }
            else
            { /* quit processing of invalid FF - no further handling required */
              bRetValue = kDtlRxCompleteNoTx;
            }
          }
        break;

 #if ! defined ( DTL_ENABLE_RX_SINGLE_FRAME_ONLY )
        case 0x20u:
          /* Consecutive frame received */
          if(get_bDtlTpRxState(dtllinchannel) == kDtlStateRxWaitCF)
          {
            /* Expecting consecutive frame. Check address information identical to FF */
            if(MessagePtr[0]== get_bDtlCurrentAddress(dtllinchannel))
            {
              if((MessagePtr[1]&0x0Fu) == get_bDtlNextSequenceNr(dtllinchannel))
              {
                /* Expected consecutive frame received.*/
                if(get_wDtlRemainingLength(dtllinchannel) <=(vuint16)6)
                {
                  /* Last message received */
                  if( (get_bDtlRxCopyMode(dtllinchannel) == kDtlStart_RxCopy) )
                  {
                    /* Copy only remaining bytes to message buffer */
                    VStdMemCpyRamToRam(&(get_pbLinDiagBuffer(dtllinchannel)[get_wDtlCurrentBufferIndex(dtllinchannel)]), &(MessagePtr[2]), get_wDtlRemainingLength(dtllinchannel));
                  }
                  set_wDtlRemainingLength(dtllinchannel, 0);
                  /* Cancel ST timeout observation */
                  Cancel_DtlTimeoutTimer(dtllinchannel);

                  bRetValue = kDtlRxCompleteEnableTx;
                  clr_bDtlTpState(dtllinchannel);
   #if defined (DTL_ENABLE_SECONDARY_NAD)
                  if (MessagePtr[0] == kDtlBroadcastNAD)
                  {
                    /* response with node specific NAD by default */
                    set_bDtlCurrentAddress(dtllinchannel, LinGetConfiguredNAD(dtllinchannel));
                  }
   #endif
                  /* Indicate successful reception to diagnostic application */
                  ApplDtlRxMsgIndication(DTL_I_CHANNEL_PARA_FIRST kDtlRxResult_COMPLETED);
                }
                else
                {
                  if( (get_bDtlRxCopyMode(dtllinchannel) == kDtlStart_RxCopy) )
                  {
                    /* copy six data bytes to message buffer */
                    VStdMemCpyRamToRam(&(get_pbLinDiagBuffer(dtllinchannel)[get_wDtlCurrentBufferIndex(dtllinchannel)]), &(MessagePtr[2]), 6);
                  }
                  set_wDtlCurrentBufferIndex(dtllinchannel,(vuint16)(get_wDtlCurrentBufferIndex(dtllinchannel) + 6));

                  set_bDtlNextSequenceNr(dtllinchannel, (vuint8)((get_bDtlNextSequenceNr(dtllinchannel) + 1) & 0x0Fu));
                  set_wDtlRemainingLength(dtllinchannel, (vuint16)(get_wDtlRemainingLength(dtllinchannel) - 6));

                  /* Start ST timeout observation */
                  Start_DtlTimeout_RxSTmax(dtllinchannel);
                  bRetValue = kDtlRxExpectNextFrame;
                }
              }
              else
              {
                /* Wrong sequence number. Indicate Error. */
                Cancel_DtlTimeoutTimer(dtllinchannel);
  #if defined (DTL_APISTYLE_VECTOR)
                DTL_VOID_CAST ApplDtlRxMsgIndication(DTL_I_CHANNEL_PARA_FIRST kDtlRxResult_FAILED);
  #else
   #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
                set_bLdRxStatus(dtllinchannel, LD_WRONG_SN);
   #else
                set_bLdRxStatus(dtllinchannel, LD_FAILED);
   #endif
  #endif
                clr_bDtlTpState(dtllinchannel);

                /* Stop receive mode */
                bRetValue = kDtlRxCompleteNoTx;
              }
            }
            else
            {
              /* Consecutive frame with wrong address information received. Ignore frame */
              bRetValue = kDtlRxCompleteNoTx;
            }
          }
          else
          {
            /* unexpected consecutive frame. Ignore frame */
            if (get_bDtlTpRxState(dtllinchannel) != kDtlStateIdle)
            { /* wait for next CF */
              bRetValue = kDtlRxExpectNextFrame;
            }
            else if (get_bDtlTpTxState(dtllinchannel) != kDtlStateIdle)
            { /* wait for next transmission */
              bRetValue = kDtlRxCompleteEnableTx;
            }
            else
            { /* quit processing of invalid SF - no further handling required */
              bRetValue = kDtlRxCompleteNoTx;
            }
          }
        break;
 #endif /* ! DTL_ENABLE_RX_SINGLE_FRAME_ONLY */
        default:
          /* unknown frame type received. Ignore the frame */
          if (get_bDtlTpRxState(dtllinchannel) != kDtlStateIdle)
          { /* wait for next CF */
            bRetValue = kDtlRxExpectNextFrame;
          }
          else if (get_bDtlTpTxState(dtllinchannel) != kDtlStateIdle)
          { /* wait for next transmission */
            bRetValue = kDtlRxCompleteEnableTx;
          }
          else
          { /* quit processing of invalid SF - no further handling required */
            bRetValue = kDtlRxCompleteNoTx;
          }
        break;
      }
    }
 #if defined (DTL_ECUTYPE_SLAVE)
  #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
    else if ((MessagePtr[0] == kDtlFunctionalNAD) && (MessagePtr[1] > 0x00u) && (MessagePtr[1] <= 0x06u))
    { /* valid functional request received */
      if((get_bDtlTpTxState(dtllinchannel) == kDtlStateIdle) && (get_bDtlTpRxState(dtllinchannel) == kDtlStateIdle))
      { /* handle functional request */
        set_bDtlRxCopyMode(dtllinchannel, ApplDtlRxStartIndication(DTL_I_CHANNEL_PARA_FIRST MessagePtr[0], (MessagePtr[1]&0x0Fu))); /* PRQA S 0850 *//* MD_DTL_LIN_19.8 */

        if(( get_bDtlRxCopyMode(dtllinchannel) == kDtlStart_RxCopy ) ||
          ( get_bDtlRxCopyMode(dtllinchannel) == kDtlStart_RxNoCopy ))
        {
          /* Receive Request and copy it to Data buffer */
          /* For optimization, copy always 6 byte */

          /* For Slave, also in case kDtlStart_RxNoCopy, the first frame is copied
          to be able to use the Service identifier.   */
          VStdMemCpyRamToRam(get_pbLinDiagBuffer(dtllinchannel), &(MessagePtr[2]), 6);

          ApplDtlRxMsgIndication(DTL_I_CHANNEL_PARA_FIRST kDtlRxResult_COMPLETED);
        }
        bRetValue = kDtlRxCompleteNoTx;
      }
      /* Ignore the functional request type */
      else if (get_bDtlTpRxState(dtllinchannel) != kDtlStateIdle)
      { /* wait for next CF */
        bRetValue = kDtlRxExpectNextFrame;
      }
      else /* if (get_bDtlTpTxState(dtllinchannel) != kDtlStateIdle) */
      { /* wait for next transmission */
        bRetValue = kDtlRxCompleteEnableTx;
      }
    }
  #endif
    else
    {
      /* NAD not addressing this node - quit running connection if ongoing */

      if( get_bDtlTpTxState(dtllinchannel) != kDtlStateIdle )
      { /* Cancel transmission and inform application */
        Cancel_DtlTimeoutTimer(dtllinchannel);
        clr_bDtlTpState(dtllinchannel);
        (void)ApplDtlTxConfirmation(DTL_I_CHANNEL_PARA_FIRST kDtlTxResult_FAILED);
      }
      else if(get_bDtlTpRxState(dtllinchannel) != kDtlStateIdle)
      { /* Cancel reception and inform diagnostic Application */
        clr_bDtlTpState(dtllinchannel);
        Cancel_DtlTimeoutTimer(dtllinchannel);
        set_wDtlRemainingLength(dtllinchannel, 0);
  #if (! defined ( DTL_ENABLE_TX_SINGLE_FRAME_ONLY )) || (! defined ( DTL_ENABLE_RX_SINGLE_FRAME_ONLY ))
        set_wDtlCurrentBufferIndex(dtllinchannel, 0);
  #endif
        DTL_VOID_CAST ApplDtlRxMsgIndication(DTL_I_CHANNEL_PARA_FIRST kDtlTxResult_FAILED);
      }
      else
      {
        /* MISRA */
      }
      bRetValue = kDtlRxCompleteNoTx;
    }
 #endif
  }
 #if defined (DTL_ENABLE_ALL_NAD)
 #else
  else
  {
  #if defined (DTL_ECUTYPE_SLAVE)
    /* NAD not addressing this node - quit running connection if ongoing */

    if( get_bDtlTpTxState(dtllinchannel) != kDtlStateIdle )
    { /* Cancel transmission and inform application */
      Cancel_DtlTimeoutTimer(dtllinchannel);
      clr_bDtlTpState(dtllinchannel);
      (void)ApplDtlTxConfirmation(DTL_I_CHANNEL_PARA_FIRST kDtlTxResult_FAILED);
    }
    else if(get_bDtlTpRxState(dtllinchannel) != kDtlStateIdle)
    { /* Cancel reception and inform diagnostic Application */
      clr_bDtlTpState(dtllinchannel);
      Cancel_DtlTimeoutTimer(dtllinchannel);
      set_wDtlRemainingLength(dtllinchannel, 0);
   #if (! defined ( DTL_ENABLE_TX_SINGLE_FRAME_ONLY )) || (! defined ( DTL_ENABLE_RX_SINGLE_FRAME_ONLY ))
      set_wDtlCurrentBufferIndex(dtllinchannel, 0);
   #endif
      DTL_VOID_CAST ApplDtlRxMsgIndication(DTL_I_CHANNEL_PARA_FIRST kDtlTxResult_FAILED);
    }
    else
    {
      /* MISRA */
    }
  #endif
    /* Frame address is >= 0x80. Frame not handled by the DTL. */
    bRetValue = kDtlRxFrameNotHandled;
  }
 #endif

#endif /* DTL_PROCESSING_COOKED */
  return bRetValue;
} /* PRQA S 6030 *//* MD_DTL_METRIC_STCYC *//* PRQA S 6080 *//* MD_DTL_METRIC_STMIF */

/*******************************************************************************************/
/*    CALLBACK FUNCTION:  ApplLinDtlPretransmitFct                                         */
/*******************************************************************************************/
/* for documentation, see drv_lin_tp.h                                                     */

void ApplLinDtlPretransmitFct(DTL_LIN_I_CHANNEL_TYPE_FIRST vuint8* MessagePtr)
{

#if defined (DTL_PROCESSING_COOKED)
  /* Provide segmented transmit data, address information and  protocol information */
  if(get_bDtlTpTxState(dtllinchannel) == kDtlStateTxWaitStartTransm)
  {
    Cancel_DtlTimeoutTimer(dtllinchannel);

    MessagePtr[0] = get_bDtlCurrentAddress(dtllinchannel);

 #if ! defined ( DTL_ENABLE_TX_SINGLE_FRAME_ONLY )
    /* checking not needed if only SF is supported */
    if(get_wDtlRemainingLength(dtllinchannel) <= (vuint16)6)
 #endif
    {
      /* Send single frame */
      MessagePtr[1] = (vuint8) get_wDtlRemainingLength(dtllinchannel);
 #if defined (DTL_ECUTYPE_SLAVE)
  #if defined (DTL_ENABLE_RCR_RP_SUPPORT)
      if (get_bDtlResponsePendingFlag(dtllinchannel) == 1)
      { /* response pending frame requested, use RcrRp diagnostic buffer */
        set_bDtlResponsePendingFlag(dtllinchannel, 0);
        MessagePtr[2] = get_pbLinDiagRcrRpBuffer(dtllinchannel)[0];
        MessagePtr[3] = get_pbLinDiagRcrRpBuffer(dtllinchannel)[1];
        MessagePtr[4] = get_pbLinDiagRcrRpBuffer(dtllinchannel)[2];
        MessagePtr[5] = get_pbLinDiagRcrRpBuffer(dtllinchannel)[3];
        MessagePtr[6] = get_pbLinDiagRcrRpBuffer(dtllinchannel)[4];
        MessagePtr[7] = get_pbLinDiagRcrRpBuffer(dtllinchannel)[5];
      }
      else
  #endif
 #endif
      {
        VStdMemCpyRamToRam(&(MessagePtr[2]), get_pbLinDiagBuffer(dtllinchannel), get_wDtlRemainingLength(dtllinchannel));

        VStdMemFarSet(&(MessagePtr[(vuint8)(2 + get_wDtlRemainingLength(dtllinchannel))]), 0xFFu, (vuint16)(6 - get_wDtlRemainingLength(dtllinchannel)));
      }
      set_bDtlTpTxState(dtllinchannel, kDtlStateTxWaitSFConf);
      set_wDtlRemainingLength(dtllinchannel, 0);
    }
 #if ! defined ( DTL_ENABLE_TX_SINGLE_FRAME_ONLY )
    else
    {
      /* Send first frame */
      MessagePtr[1] = (vuint8) (0x10u | (0x0Fu & (get_wDtlRemainingLength(dtllinchannel) >> 8)));
      MessagePtr[2] = (vuint8) get_wDtlRemainingLength(dtllinchannel);

      VStdMemCpyRamToRam(&(MessagePtr[3]), get_pbLinDiagBuffer(dtllinchannel), 5);

      set_wDtlRemainingLength(dtllinchannel, (vuint16)(get_wDtlRemainingLength(dtllinchannel) - 5));
      set_bDtlNextSequenceNr(dtllinchannel, 1);
      set_wDtlCurrentBufferIndex(dtllinchannel, 5);

      set_bDtlTpTxState(dtllinchannel, kDtlStateTxWaitFFConf);
    }
 #endif /* ! DTL_ENABLE_TX_SINGLE_FRAME_ONLY */
    Start_DtlTimeout_TxConfirm(dtllinchannel);
  }
 #if ! defined ( DTL_ENABLE_TX_SINGLE_FRAME_ONLY )
  else if (get_bDtlTpTxState(dtllinchannel) == kDtlStateTxWaitCFTransm)
  {
    Cancel_DtlTimeoutTimer(dtllinchannel);
    /* Send consecutive frame */
    MessagePtr[0] = get_bDtlCurrentAddress(dtllinchannel);
    MessagePtr[1] = (vuint8)(0x20u | get_bDtlNextSequenceNr(dtllinchannel) );

    if(get_wDtlRemainingLength(dtllinchannel) <= (vuint16)6)
    {

      VStdMemCpyRamToRam(&(MessagePtr[2]), &(get_pbLinDiagBuffer(dtllinchannel)[get_wDtlCurrentBufferIndex(dtllinchannel)]), get_wDtlRemainingLength(dtllinchannel));

      VStdMemFarSet(&(MessagePtr[(vuint8)(2 + get_wDtlRemainingLength(dtllinchannel))]), 0xFFu, (vuint8)(6 - get_wDtlRemainingLength(dtllinchannel)));

      set_wDtlCurrentBufferIndex(dtllinchannel, 0);
      set_wDtlRemainingLength(dtllinchannel, 0);
      set_bDtlTpTxState(dtllinchannel, kDtlStateTxWaitCFConf);
      }
    else
    {
      /* more frames to transmit */
      VStdMemCpyRamToRam(&(MessagePtr[2]), &(get_pbLinDiagBuffer(dtllinchannel)[get_wDtlCurrentBufferIndex(dtllinchannel)]), 6);

      set_wDtlCurrentBufferIndex(dtllinchannel,(get_wDtlCurrentBufferIndex(dtllinchannel) + 6));
      set_wDtlRemainingLength(dtllinchannel, get_wDtlRemainingLength(dtllinchannel) - 6);
      set_bDtlTpTxState(dtllinchannel, kDtlStateTxWaitCFConf);
      set_bDtlNextSequenceNr(dtllinchannel, (vuint8)((get_bDtlNextSequenceNr(dtllinchannel) + 1) & 0x0Fu));
    }
    Start_DtlTimeout_TxConfirm(dtllinchannel);
  }
 #endif /* ! DTL_ENABLE_TX_SINGLE_FRAME_ONLY */
  else
  {
    /* Pretransmit function should not be called in this state. */
    DtlAssertStatic(dtllinchannel,kDtlErrorInconsistentState); /* PRQA S 3109 *//* MD_DTL_LIN_14.3 */
  }
#endif /* DTL_PROCESSING_COOKED */
}

/*******************************************************************************************/
/*    CALLBACK FUNCTION:  ApplLinDtlTxConfirmation                                         */
/*******************************************************************************************/
/* for documentation, see drv_lin_tp.h                                                     */

vuint8 ApplLinDtlTxConfirmation(DTL_LIN_I_CHANNEL_TYPE_ONLY)
{
  vuint8 bRetValue;

#if defined (DTL_PROCESSING_COOKED)
  if( get_bDtlTpTxState(dtllinchannel) == kDtlStateTxWaitSFConf )
  {
    /* transmission Complete */
    clr_bDtlTpTxState(dtllinchannel);
    Cancel_DtlTimeoutTimer(dtllinchannel);
 #if defined (DTL_APISTYLE_VECTOR)
    /* Store result of ApplDtlTxConfirmation temporarily in bRetValue */
    bRetValue = ApplDtlTxConfirmation(DTL_I_CHANNEL_PARA_FIRST kDtlTxResult_COMPLETED);
 #endif
    if(bRetValue == kDtlTxTransmComplete)
    {
      bRetValue = kDtlTxCompleteNoRx;
    }
    else if (bRetValue == kDtlTxTransmPending)
    {
      bRetValue = kDtlTxExpectNextFrame;
    }
    else
    {
      /*unexpected return value */
      DtlAssertStatic(dtllinchannel, kDtlErrorInvalidReturnValue); /* PRQA S 3109 *//* MD_DTL_LIN_14.3 */
    }

  }
 #if ! defined ( DTL_ENABLE_TX_SINGLE_FRAME_ONLY )
  else if (get_bDtlTpTxState(dtllinchannel) == kDtlStateTxWaitFFConf)
  {
    set_bDtlTpTxState(dtllinchannel, kDtlStateTxWaitCFTransm);
    /* Activate ST timeout observation */
    Start_DtlTimeout_TxSTmax(dtllinchannel);
    bRetValue = kDtlTxExpectNextFrame;
  }
  else if (get_bDtlTpTxState(dtllinchannel) == kDtlStateTxWaitCFConf)
  {
    if(get_wDtlRemainingLength(dtllinchannel) != 0)
    {
      set_bDtlTpTxState(dtllinchannel, kDtlStateTxWaitCFTransm);
      /* Activate ST timeout observation */
      Start_DtlTimeout_TxSTmax(dtllinchannel);
      bRetValue = kDtlTxExpectNextFrame;
    }
    else
    {
      /* Transmission complete */
      clr_bDtlTpTxState(dtllinchannel);
      Cancel_DtlTimeoutTimer(dtllinchannel);
  #if defined (DTL_APISTYLE_VECTOR)
      bRetValue = ApplDtlTxConfirmation(DTL_I_CHANNEL_PARA_FIRST kDtlTxResult_COMPLETED);
  #endif
      if(bRetValue == kDtlTxTransmComplete)
      {
        bRetValue = kDtlTxCompleteNoRx;
      }
      else if (bRetValue == kDtlTxTransmPending)
      {
        bRetValue = kDtlTxExpectNextFrame;
      }
      else
      {
        /*unexpected return value */
        DtlAssertStatic(dtllinchannel, kDtlErrorParamValue); /* PRQA S 3109 *//* MD_DTL_LIN_14.3 */
        bRetValue = kDtlTxCompleteNoRx;
      }
    }
  }
 #endif /* ! DTL_ENABLE_TX_SINGLE_FRAME_ONLY */
  else
  {
    /* Unexpected Tx Confirmation set return value to kDtlTxCompleteNoRx */
    bRetValue = kDtlTxCompleteNoRx;
  }
#endif /* DTL_PROCESSING_COOKED */
  return bRetValue;
} /* PRQA S 6080 *//* MD_DTL_METRIC_STMIF */

/*******************************************************************************************/
/*    CALLBACK FUNCTION:  ApplLinDtlTxError                                                */
/*******************************************************************************************/
/* for documentation, see drv_lin_tp.h                                                     */

void ApplLinDtlError(DTL_LIN_I_CHANNEL_TYPE_ONLY)
{ /* Indication of protocol error or lost priority */
#if defined (DTL_PROCESSING_COOKED)
  /* Indication of protocol Error in Tx frame  */
  #if ! defined ( DTL_ENABLE_TX_SINGLE_FRAME_ONLY )
  if( (get_bDtlTpTxState(dtllinchannel) == kDtlStateTxWaitSFConf) ||
      (get_bDtlTpTxState(dtllinchannel) == kDtlStateTxWaitFFConf) ||
      (get_bDtlTpTxState(dtllinchannel) == kDtlStateTxWaitCFConf) )
  #else
  if( get_bDtlTpTxState(dtllinchannel) == kDtlStateTxWaitSFConf )
  #endif
  {
    /* Transmit error. Inform application */
    Cancel_DtlTimeoutTimer(dtllinchannel);
 #if defined (DTL_APISTYLE_VECTOR)
    clr_bDtlTpState(dtllinchannel);
    (void)ApplDtlTxConfirmation(DTL_I_CHANNEL_PARA_FIRST kDtlTxResult_FAILED);
 #else
    set_bLdTxStatus(dtllinchannel, LD_FAILED);
    if (get_bDtlTpRxState(dtllinchannel) != kDtlStateIdle)
    { /* ld_receive_message pending - set error indication */
      set_bLdRxStatus(dtllinchannel, LD_FAILED);
    }
    clr_bDtlTpState(dtllinchannel);
 #endif
  }
 #if ! defined ( DTL_ENABLE_RX_SINGLE_FRAME_ONLY )
  else if(get_bDtlTpRxState(dtllinchannel) == kDtlStateRxWaitCF)
  { /* protocol error in the Rx diagnostic frame */
    /* Cancel reception and inform diagnostic Application */
    clr_bDtlTpState(dtllinchannel);
    set_wDtlRemainingLength(dtllinchannel, 0);
    set_wDtlCurrentBufferIndex(dtllinchannel, 0);
  #if defined (DTL_APISTYLE_VECTOR)
    DTL_VOID_CAST ApplDtlRxMsgIndication(DTL_I_CHANNEL_PARA_FIRST kDtlTxResult_FAILED);
  #else
    set_bLdRxStatus(dtllinchannel, LD_FAILED);
  #endif
  }
  else
  {
    /* MISRA */
  }
 #endif /* ! DTL_ENABLE_RX_SINGLE_FRAME_ONLY */
#endif /* else DTL_PROCESSING_COOKED */
}


/* module specific MISRA deviations:
  MD_DTL_DRV_1.1:
     Reason: Runtime and code efficient implementation of message handles force high nesting.
     Risk: High nesting depth is hard to review and error prone.
     Prevention: Specific test cases which reach the inner code and also code inspection.
  MD_DTL_LIN_3.1:
     Reason: @ necessary as character to support Doxygen documentation.
     Risk: None. All known compiler support @ in comments.
     Prevention: N/A

  MD_DTL_LIN_8.12:
     Reason: Array dimension is project dependent and generated by generation tool.
     Risk: Invalid element access or no compiler optimization.
     Prevention: Tested during integration.

  MD_DTL_LIN_14.3:
     Reason: Line only empty if debugging is disabled.
     Risk: Wrong macro implementations could remain undetected.
     Prevention: Code inspection of the macros and test of different source code variants in component release process.

  MD_DTL_LIN_16.4:
     Reason: Parameter name differ from declaration to simplify implementation with Vector and LIN API.
     Risk: Understandability suffers if the official API is known.
     Prevention: Code inspection of the affected variant.

  MD_DTL_LIN_19.1:
     Reason: FBL memory mapping requires inclusion of MemMap.h several times.
     Risk: MemMap.h is provided by the integrator, hence many risks may occur, caused by wrong implementation of this file.
     Prevention: Code inspection of MemMap.h by the FBL integrator.

  MD_DTL_LIN_19.4A:
     Reason: Debug code with runtime check removed for serial release of code.
     Risk: Incorrect usage of macro.
     Prevention: Code inspection of the macros and test in component release process.

  MD_DTL_LIN_19.4B:
     Reason: Usage of braces forces compile error
     Risk: Incorrect usage of macro.
     Prevention: Code inspection of the macros and test in component release process.

  MD_DTL_LIN_19.7:
     Reason: Function like makro used to distinguish index from single channel system. Efficiency.
     Risk: Resulting code is difficult to understand or may not work as expected.
     Prevention: Code inspection and test of the different variants in the component release process.

  MD_DTL_LIN_19.8:
     Reason: Macro used in single and multi channel configurations.
     Risk: Uncleare usage of macro parameter
     Prevention: Code inspection of the macros and test in component release process.

  MD_DTL_METRIC_STCYC:
     Reason: No separation of functionality into sub-functions due to higher voted requirements for minimized stack and runtime usage.
     Risk: Understandability and testability might become too complex.
     Prevention: Design and code review + clearly structured and commented code.

  MD_DTL_METRIC_STMIF:
     Reason: Function handles specific task in the overall component behavior; task has different scenarios
     to cover depending on local conditions - this results in deep nesting of control structures.
     Due to there is more common than different code, higher nesting level is accepted to keep code footprint small.
     Risk: Code is difficult to maintain
     Prevention: Design and code review + clearly structured and commented code.


*/

/* End of dtl_lin.c  */

