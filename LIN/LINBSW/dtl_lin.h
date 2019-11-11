/* PRQA S 0288 EOF *//* MD_DTL_LIN_3.1 */
/*******************************************************************************************/
/** @file    dtl_lin.h
*   @brief   Export interface of the LIN diagnostic transport layer used by the diagnostic application
*
*            This file provides the API to access the functions provided by the diagnostic
*            transport layer. Dependent on the selection, either the LIN API of the LIN
*            specification or the enhanced Vector API is provided.
*
********************************************************************************************/
/*******************************************************************************************/
/** @page     dtl_lin_h_header Header information of dtl_lin.h
********************************************************************************************
*   @par      copyright
*   @verbatim
*
*   Copyright (c) 2014 Vector Informatik GmbH                  All rights reserved.
*
*   This software is copyright protected and proprietary to Vector Informatik GmbH.
*   Vector Informatik GmbH grants to you only those rights as set out in the
*   license conditions. All other rights remain with Vector Informatik GmbH.
*
*   @endverbatim
********************************************************************************************
*   @par      Authors
*   @verbatim
*
*        Initials  Name                    Company
*        Wr        Hans Waaser             Vector Informatik GmbH
*        Svh       Sven Hesselmann         Vector Informatik GmbH
*        Ap        Andreas Pick            Vector Informatik GmbH
*        Bmo       Bastian Molkenthin      Vector Informatik GmbH
*   @endverbatim
********************************************************************************************
*  @par          Revision History
*  @verbatim
*
*    Date         Ver       Author   Description
*    2004-08-30   1.00      Wr       First implementation
*    2004-09-01   1.01      Wr       Extern declarations for version number
*                                    Added TP raw implementation
*    2004-12-07   1.02      Wr       Adapted API description and some defines of TP raw.
*    2005-01-17   1.03      Wr       No changes here (See dtl_lin.c).
*    2005-08-26   1.04      Svh      ESCAN00013274: Define LD_IN_PROCESS is given instead of LD_IN_PROGRESS
*    2005-09-28   1.05      Svh      ESCAN00014052: Findings of MISRA check and code review have to be included
*    2005-11-09   1.06      Svh      No changes here (See dtl_lin.c).
*    2005-12-13   1.07      Svh      ESCAN00014641: Compiler error because of an unknown define if LIN API of TpLin is used
*    2006-02-14   1.08      Ap       ESCAN00015343: [TpLin_CookedMasterECU] LIN Master multi channel support
*                                    ESCAN00015344: [TpLin_RawMasterECU]    LIN Master multi channel support
*    2007-01-17   1.09      Ap       ESCAN00018979: Support for LIN 2.1 TP raw extensions
*    2007-03-12   1.10      Ap       ESCAN00019772: Support for LIN 2.1 TP cooked extensions
*                                    ESCAN00019891: RAW API: ld_get_raw() or DtlGetRaw() might return invalid data after frame error on SlaveResponse
*    2007-04-19   1.11      Ap       ESCAN00020347: Seperate rx and tx state engine
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
*  \endverbatim
********************************************************************************************/


#ifndef __DTL_LIN_H__
 #define __DTL_LIN_H__

/*******************************************************************************************/
/* Version                  (abcd: Main version ab Sub Version cd )                        */
/*******************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : TpLin CQComponent : Implementation */
 #define TPLIN_VERSION          0x0129u
 #define TPLIN_RELEASE_VERSION  0x05u


/*******************************************************************************************/
/* Global constants with DTL main and subversion                                           */
/*******************************************************************************************/
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kDtlLinMainVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kDtlLinSubVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kDtlLinReleaseVersion;


 #if defined ( DTL_APISTYLE_LIN )
  #if ! defined ( __LIN_DATA_TYPES__ )
   #define __LIN_DATA_TYPES__
/* Mapping of the data types of the LIN API to the internal used types  */
typedef vuint8  l_bool;
typedef vuint8  l_u8;
typedef vuint16 l_u16;
typedef vuint8  l_ifc_handle;
typedef vuint8  l_schedule_handle;
  #endif
 #endif


 #if defined(DTL_ECUTYPE_SLAVE)
V_MEMRAM0 extern V_MEMRAM1 vuint8  V_MEMRAM2 pbLinDiagBuffer[]; /* PRQA S 3684 *//* MD_DTL_LIN_8.12 */
   #if defined (DTL_ENABLE_RCR_RP_SUPPORT)
V_MEMRAM0 extern V_MEMRAM1 vuint8  V_MEMRAM2 pbLinDiagRcrRpBuffer[]; /* PRQA S 3684 *//* MD_DTL_LIN_8.12 */
   #endif
 #endif

/* The parameter documented with @param_i is the optional channel/interface parameter. It is
   only available when an indexed API is used.
   The interface parameter iii is mandatory for the function calls starting with 'ld_'.
*/

 #define kDtlFunctionalNAD                       ((vuint8) 0x7Eu) /* NAD used for functional addressing */
 #define kDtlBroadcastNAD                        ((vuint8) 0x7Fu) /* NAD used for broadcast addressing  */
 #define kDtlAdrTypeLogical                      kDtlFunctionalNAD

/*******************************************************************************************/
/*       COMMON API PART                                                                   */
/*******************************************************************************************/
 #if defined ( DTL_APISTYLE_VECTOR )
/*******************************************************************************************/
/*    API FUNCTION:  DtlInitPowerOn                                                        */
/*******************************************************************************************/
/**
 *   @brief   Initialization of the diagnostic transport layer
 *
 *            Initialization of all transport layer channels. The function must be called
 *            before using any API function.
 *
 *   @return  none
 *
 *   @pre     Function must be called with global interrupts disabled.
 *
 *******************************************************************************************/
extern void DtlInitPowerOn(void);


/*******************************************************************************************/
/*    API FUNCTION:  DtlInit / ld_init                                                     */
/*******************************************************************************************/
/**
 *   @brief   Initialization of one diagnostic transport layer channel
 *
 *            Initialization of all DTL internal variables and states of one channel. The
 *            function is called by LinInitPowerOn() for all channels. It can be called
 *            by the application for the reinitialization of one channel.
 *
 *   @param_i bDtlLinChannel / iii The interface/channel which is initialized
 *
 *   @return  none
 *
 *   @pre     Function must be called with global interrupts disabled.
 *
 *******************************************************************************************/
extern void DtlInit(void);

 #else /* DTL_APISTYLE_VECTOR */
extern void ld_init (l_ifc_handle iii);
 #endif

/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplDtlFatalError                                            */
/*******************************************************************************************/
/**
 *   @brief   Indication of fatal errors detected by the diagnostic transport layer
 *
 *            Callback function for the application called by the DTL after a fatal
 *            error has been detected.
 *            This can be caused by an inconsistent configuration, an inconsistent
 *            internal state or the usage of a function parameter out of the
 *            allowed range. The call of the function must be observed during
 *            development.
 *
 *   @param_i channel The interface/channel which detected the error
 *
 *   @param   error The error code of the detected error
 *
 *   @return  none
 *
 *   @pre     Only called, when debug option is enabled. Function is called from task or interrupt level.
 *
 *******************************************************************************************/
 #if defined ( DTL_ENABLE_DEBUG )
extern void ApplDtlFatalError(vuint8 error);
 #endif

/* Errors signalized by ApplDtlFatalError() when debug mode is enabled */

 #define kDtlErrorNADNotAllowed                  ((vuint8) 0x01u)      /* Indicates NAD = 0 (Sleep frame, not allowed), cooked master only */
 #define kDtlErrorQueueOverrun                   ((vuint8) 0x80u)      /* Queue overrun, increase queue or increment polling rate, raw master only */
 #define kDtlErrorNotInitialized                 ((vuint8) 0x02u)      /* DtlInit has not been called before Calling the API function */
 #define kDtlErrorParamValue                     ((vuint8) 0x10u)      /* Function called with parameter out of range */
 #define kDtlErrorInconsistentState              ((vuint8) 0x20u)      /* Status engine inconsistent                  */
 #define kDtlErrorInvalidReturnValue             ((vuint8) 0x40u)      /* Return value not expected                   */


 #if defined ( DTL_PROCESSING_COOKED )
/*******************************************************************************************/
/*    API FUNCTION:  DtlTimerTask                                                          */
/*******************************************************************************************/
/**
 *   @brief   Provides a base time for the timeout observation
 *
 *            The function provides the base time for the timeout observation of
 *            the separation time. The timeout is observed for the send process
 *            and receive process.
 *
 *   @param_i bDtlLinChannel The interface/channel the task call is relevant for.
 *
 *   @return  none
 *
 *   @pre     Function must be called cyclically from task level with the
 *            configured cycle time.
 *
 *******************************************************************************************/
extern void DtlTimerTask(void);

  #if defined ( DTL_APISTYLE_VECTOR )
/*******************************************************************************************/
/*       VECTOR API                                                                        */
/*******************************************************************************************/
/*******************************************************************************************/
/*    API FUNCTION:  DtlTxSendMessage                                                      */
/*******************************************************************************************/
/**
 *   @brief   Requests the transmission of message data
 *
 *            The function requests the transmission of N byte of data.
 *            The pointer to the data is optional. For slave nodes a fix data buffer
 *            is used.
 *            Dependent on the State of the TP, the request is accepted or not.
 *
 *   @param_i bDtlLinChannel  The interface/channel which is requested
 *   @param   wLength      Number of data bytes to be transmitted
 *   @param   bAddressInfo The address info to be used for transmission
 *   @param   pbMsgData    Pointer to the message data buffer
 *
 *   @return  Acceptance of the transmission request
 *                         kDtlTxState_ACCEPTED  A transmission is currently possible.
 *                         kDtlTxState_REJECTED  A transmission is rejected.
 *
 *   @pre     wLength      must be in the range of 1..4095.
 *
 *   @note    The message data buffer may not be changed as long as
 *            ApplDtlTxConfirmation is not called.
 *
 *******************************************************************************************/
extern vuint8 DtlTxSendMessage(vuint16 wLength);

   #define kDtlTxState_ACCEPTED                  ((vuint8) 0x00u)
   #define kDtlTxState_REJECTED                  ((vuint8) 0x01u)

   #if defined (DTL_ECUTYPE_SLAVE)
    #if defined (DTL_ENABLE_RCR_RP_SUPPORT)
/*******************************************************************************************/
/*    API FUNCTION:  DtlTxSendRcrRpMessage                                                 */
/*******************************************************************************************/
/**
 *   @brief   Requests the transmission of a response pending frame
 *
 *            The function requests the transmission of N byte of data.
 *            The data is accessed from the fixed response pending data buffer
 *            provided by LinDiag layer. This function is only available for slave nodes.
 *            Dependent on the State of the TP, the request is accepted or not.
 *            Not available for indexed slaves.
 *
 *   @param_i bDtlLinChannel  The interface/channel which is requested
 *   @param   bLength      Number of data bytes to be transmitted
 *
 *   @return  Acceptance of the transmission request
 *                         kDtlTxState_ACCEPTED  A transmission is currently possible.
 *                         kDtlTxState_REJECTED  A transmission is rejected.
 *
 *   @pre     bLength      must be in the range of 1..6.
 *
 *   @note    The response pending data buffer may not be changed as long as
 *            ApplDtlTxConfirmation is not called.
 *
 *******************************************************************************************/
extern vuint8 DtlTxSendRcrRpMessage(vuint8 bLength);
    #endif
   #endif

/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplDtlTxConfirmation                                        */
/*******************************************************************************************/
/**
 *   @brief   Confirmation of the Transmission. Indicates also an error in transmission
 *
 *            Callback function for the confirmation of a successful or failed
 *            transmission.
 *
 *   @param_i channel The interface/channel where the confirmation comes from.
 *
 *   @param   bResult The result of the current transmission. Can be either
 *                    kDtlTxResult_COMPLETED  for sucessful transmission or
 *                    kDtlTxResult_FAILED     for failed transmission
 *
 *   @return  Handling instruction for the indicated frame
 *
 *   @pre     No precondition. Function is called from interrupt level.
 *
 *******************************************************************************************/
extern vuint8 ApplDtlTxConfirmation(vuint8 bResult);

 /* Defines for the parameter bResult */
   #define kDtlTxResult_COMPLETED                ((vuint8) 0x00u)
   #define kDtlTxResult_FAILED                   ((vuint8) 0x01u)
   #define kDtlFuncTxResult_COMPLETED            ((vuint8) 0x02u)
   #define kDtlFuncTxResult_FAILED               ((vuint8) 0x03u)

/* Defines for the return value */
    #define kDtlTxTransmComplete                 ((vuint8) 0x00u)
    #define kDtlTxTransmPending                  ((vuint8) 0x01u)

/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplDtlRxStartIndication                                     */
/*******************************************************************************************/
/**
 *   @brief   Indication of the start of a reception (SF or FF)
 *
 *            Callback function for the indication of a new reception.
 *            The application can decide whether the message shall be ignored,
 *            received and copied to the application or just received and not
 *            copied.
 *
 *   @param_i bDtlLinChannel  The interface/channel where the start indication comes from.
 *
 *   @param   bAddressInfo The address info of the received message
 *                         (0x01 - 0x7d for physical addressing 0x7E for functional and 0x7f for broadcast)
 *   @param   bLength      Length of the indicated message.
 *   @param   ppbRxDataPtr Pointer to the transport layer data pointer. This pointer must
 *                         be set when the reception is enabled with kDtlStart_RxCopy.
 *
 *   @return  Handling instruction for the indicated frame. Possible values are
 *                         kDtlStart_Ignore    The message is ignored.
 *                         kDtlStart_RxCopy    The message is received and copied.
 *                         kDtlStart_RxNoCopy  The message is received but not copied.
 *
 *   @pre     No precondition. Function is called from interrupt level.
 *
 *******************************************************************************************/
extern vuint8 ApplDtlRxStartIndication(vuint8 bAddressInfo, vuint16 bLength);

  /* return values */
   #define kDtlStart_Ignore                      ((vuint8) 0x00u)
   #define kDtlStart_RxCopy                      ((vuint8) 0x01u)
   #define kDtlStart_RxNoCopy                    ((vuint8) 0x02u)


/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplDtlRxMsgIndication                                       */
/*******************************************************************************************/
/**
 *   @brief   Indication of the end of a received message
 *
 *            Callback function for the indication of the end of a received
 *            message. The message can be received either successfully or
 *            with an error.
 *
 *   @param_i channel   The interface/channel where the indication comes from.
 *
 *   @param   bResult   The state of the reception.
 *            kDtlRxResult_COMPLETED     Message received without errors.
 *            kDtlRxResult_FAILED        Receive error appeared. Discard data.
 *            kDtlRxResult_REPLACE       A running reception is suspended by a new SF/FF reception
 *
 *   @return  none/bNextState  bNextState configures the succeeding state of the Rx channel.
 *
 *   @pre     No precondition. Function is called from interrupt or task level.
 *
 *******************************************************************************************/
extern void ApplDtlRxMsgIndication(vuint8 bResult);

  /* Values of bResult */
   #define kDtlRxResult_COMPLETED                ((vuint8) 0x00u)
   #define kDtlRxResult_FAILED                   ((vuint8) 0x01u)



   #if defined(DTL_ECUTYPE_SLAVE)
/*******************************************************************************************/
/*    API FUNCTION:  DtlGetCurrentNAD                                                      */
/*******************************************************************************************/
/**
 *   @brief   Requests the current NAD received in a diagnostic MasterReq frame
 *
 *            When a diagnostic frame reception is indicated this function may be used to
 *            obtain the NAD used for the request.
 *            Request are only accepted if the received NAD equals to the configured NAD,
 *            broadcast NAD. If sondondary NAD is enabled the return value also could be
 *            the secondary NAD.
 *
 *   @param   void
 *
 *   @return  Current NAD
 *
 *   @note    If no valid request has been received before a zero is returned for the NAD.
 *
 *******************************************************************************************/
   extern vuint8 DtlGetCurrentNAD(void);

    #if defined (DTL_ENABLE_SECONDARY_NAD)
/*******************************************************************************************/
/*    API FUNCTION:  DtlSetCurrentNAD                                                      */
/*******************************************************************************************/
/**
 *   @brief   Sets the NAD which shall be used for the next response transmission.
 *
 *            By default the NAD received in the last request is used for the response
 *            transmission. Using this API allows to overwrite the used NAD before calling
 *            DtlTxSendMessage().
 *            If a positive/negative response should be transmitted after power on without
 *            receiving another diagnostic request this API must be used to define the
 *            correct NAD (configured or secondary NAD).
 *
 *   @param   bCurrentNAD          Valid NAD in range [0x01 - 0x7D, 0x80 - 0xFF]
 *
 *   @return  void
 *
 *   @note    After the response transmission has triggered the API must not be used until
 *            next request reception.
 *
 *******************************************************************************************/
   extern void   DtlSetCurrentNAD(vuint8 bCurrentNAD);
    #endif
   #endif


  #else /* DTL_APISTYLE_LIN */
/*******************************************************************************************/
/*       LIN API                                                                           */
/*******************************************************************************************/
/*******************************************************************************************/
/*    API FUNCTION:  ld_send_message                                                       */
/*******************************************************************************************/
/**
 *   @brief   Requests the transmission of a message
 *
 *            The call packs the information specified by data and length into
 *            one or multiple diagnostic frames.
 *            The SID shall be the first byte in the data area.
 *            Length must be in the range 1 to 4095 bytes.
 *
 *   @param   iii     The interface/channel which is accessed.
 *   @param   length  The length of the data to be transmitted.
 *   @param   NAD     The address information used in the first data byte.
 *   @param   data    Pointer to the message data buffer.
 *
 *   @return  none
 *
 *   @pre     Availability of the tx channel must be verified by ld_tx_status().
 *
 *   @note    The result of the transmission must be checked by ld_tx_status().
 *
 *******************************************************************************************/
extern void ld_send_message(l_ifc_handle iii, l_u16 length, l_u8 NAD, l_u8* data);


/*******************************************************************************************/
/*    API FUNCTION:  ld_receive_message                                                    */
/*******************************************************************************************/
/**
 *   @brief   Request for the reception of a message
 *
 *            The call prepares the LIN diagnostic module to receive one message
 *            and store it in the buffer pointed to by data. The parameter length
 *            specifies the maximum length allowed. When the reception has
 *            completed, length is changed to the actual length, NAD to the NAD
 *            in the received message.
 *
 *   @param   iii     The interface/channel which is accessed.
 *   @param   length  Pointer to the maximum length information.
 *   @param   NAD     Pointer to the address information.
 *   @param   data    Pointer to the message data buffer.
 *
 *   @return  none
 *
 *   @pre     Availability of the rx channel must be verified by ld_rx_status().
 *
 *   @note    The result of the transmission must be checked by ld_rx_status().
 *
 ****************************************************************************/
extern void ld_receive_message(l_ifc_handle iii, l_u16* length, l_u8* NAD, l_u8* data);


/*******************************************************************************************/
/*    API FUNCTION:  ld_tx_status                                                          */
/*******************************************************************************************/
/**
 *   @brief   Checks the state of the transmit channel
 *
 *            The call returns the status of the last made call to
 *            ld_send_message.
 *
 *   @param   iii     The interface/channel which is accessed.
 *
 *   @return  status  The state of the transmit channel. Possible values are
 *            LD_IN_PROGRESS     The transmission is not yet completed.
 *            LD_COMPLETED       The transmission has completed successfully.
 *                               A new ld_send_message call can be issued.
 *            LD_FAILED          The transmission ended in an error. The data was
 *                               only partially sent.
 *                               A new ld_send_message call can be issued.
 *
 *   @pre     No precondition.
 *
 *   @note    Due to the half duplex implementation ld_tx_status() returns also
 *            LD_IN_PROGRESS when a reception is in process.
 *
 *
 *******************************************************************************************/
extern l_u8 ld_tx_status(l_ifc_handle iii);


/*******************************************************************************************/
/*    API FUNCTION:  ld_rx_status                                                          */
/*******************************************************************************************/
/**
 *   @brief   Checks the state of the receive channel
 *
 *            The call returns the status of the last made call to
 *            ld_receive_message.
 *
 *   @param   iii     The interface/channel which is accessed
 *
 *   @return  status  The state of the receive channel. Possible values are
 *            LD_IN_PROGRESS     The reception is not yet completed.
 *            LD_COMPLETED       The reception has completed successfully and
 *                               all information (length, NAD, data) is available.
 *                               A new ld_receive_message call can be issued.
 *            LD_FAILED          The reception ended in an error. The data was only
 *                               partially received and should not be trusted.
 *                               A new ld_receive_message call can be issued.
 *
 *   @return  none
 *
 *   @pre     No precondition.
 *
 *   @note    Due to the half duplex implementation ld_rx_status() returns also
 *            LD_IN_PROGRESS when a transmission is in process.
 *
 *
 *******************************************************************************************/
extern l_u8 ld_rx_status(l_ifc_handle iii);

/* defines used by ld_tx_status() and ld_rx_status() */
   #define LD_IN_PROGRESS                        ((vuint8) 0x00u)
   #define LD_COMPLETED                          ((vuint8) 0x01u)
   #define LD_FAILED                             ((vuint8) 0x02u)
   #define LD_N_AS_TIMEOUT                       ((vuint8) 0x03u)
   #define LD_N_CR_TIMEOUT                       ((vuint8) 0x04u)
   #define LD_WRONG_SN                           ((vuint8) 0x05u)

  #endif /* DTL_APISTYLE_VECTOR */
 #endif /* DTL_PROCESSING_COOKED */


#endif /* end of dtl_lin.h */

