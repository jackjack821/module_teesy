/*******************************************************************************************/
/** @file    lin_drv_tp.h
*   @brief   Export interface of the LIN driver used by the diagnostic transport layer
*
*            This file provides the API to access the functions and callback functions of the
*            LIN driver to be used by the transport layer.
*
********************************************************************************************/

/*******************************************************************************************/
/** @page     lin_tp_h_header Header information of lin_tp.h
********************************************************************************************
*   @par      copyright
*   @verbatim
*
*   Copyright (c) 2000 - 2012 Vector Informatik GmbH          All rights reserved.
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
*      Date        Ver    Author   Description
*      2004-04-16  2.00   Wr       Rework of the implementation for LIN 2.0 support
*      2004-07-17  2.01   Wr       No changes here (see lin_drv.c)
*      2004-08-27  2.02   Wr       Adapted dignostic dispatcher for DTL Master
*      2005-10-25  2.03   Svh      ESCAN00013687: Add multi channel interface between LIN driver and DTL
*                                  ESCAN00014053: Remove return value of function ApplLinDtlRxError()
*      2007-03-01  2.04   Ap       ESCAN00018979: Support for LIN 2.1 TP raw extensions
*                                  ESCAN00019772: Support for LIN 2.1 TP cooked extensions
*      2008-01-08  2.05   Ap       ESCAN00023918: Memory mapping support added
*      2011-06-14  2.06   Bmo      ESCAN00051600: Compile Error: Incorrect macro LinGetConfiguredNAD
*      2011-10-17  2.07   Ap       ESCAN00053855: Support for Misra annotations in code
*      2012-05-25  2.08   Ap       ESCAN00058689: Slave specific define for indexed implementation
*  \endverbatim
********************************************************************************************/


#ifndef LIN_TP_H
 #define LIN_TP_H


/*******************************************************************************************/
/* Version                  (abcd: Main version ab Sub Version cd )                        */
/*******************************************************************************************/
 #define LIN_DRIVER_TP_VERSION                        0x0208u
 #define LIN_DRIVER_TP_RELEASE_VERSION                0x00u


 #if defined ( LIN_ECUTYPE_SLAVE )
 /* Access macro to configured NAD */
  #define LinGetConfiguredNAD(c)                      getbLinConfiguredNAD(c)
 #endif
/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinDtlPrecopyFct                                         */
/*******************************************************************************************/
/**
 *   @brief  Callback function provides access to the Data of the diagnostic Rx frame
 *
 *           The callback function provides the data of the received diagnostic
 *           frame in the interrupt context. The function must check the data and
 *           decide to handle the frame or not. In case of a segmented reception,
 *           the following frame can be reserved to be handled.
 *
 *   @param_i bLinChannel The interface/channel the task call is relevant for
 *
 *   @param   MessagePtr Pointer to received frame data (8 bytes) starting with NAD in first byte
 *
 *   @return  kDtlRxFrameNotHandled   Frame is not handled by Dtl
 *            kDtlRxExpectNextFrame   Frame is received and expecting more frames
 *            kDtlRxCompleteEnableTx  Frame is received and state is changed to transmission
 *            kDtlRxCompleteNoTx      Frame is received an Tp communication is finished.
 *
 *   @pre     function can be called from task or interrupt context
 *
 *   @note    In case of a timeout the transport layer is responsible to release
 *            the reservation of the receive frame.
 *******************************************************************************************/
/* CODE CATEGORY 1 START*/
extern vuint8 ApplLinDtlPrecopyFct(vuint8* MessagePtr);
/* CODE CATEGORY 1 END*/

/* return value definition */
 #define kDtlRxFrameNotHandled                        ((vuint8)0x00u)
 #define kDtlRxExpectNextFrame                        ((vuint8)0x01u)
 #define kDtlRxCompleteEnableTx                       ((vuint8)0x02u)
 #define kDtlRxCompleteNoTx                           ((vuint8)0x03u)

/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinDtlError                                              */
/*******************************************************************************************/
/**
 *   @brief  Informs the transport layer about a protocol error in a frame
 *
 *           Callback function is called when the frame processor detects a
 *           protocol error in the diagnostic frame.
 *
 *   @param_i bLinChannel The interface/channel the task call is relevant for
 *
 *   @return  void
 *
 *   @pre     function can be called from task or interrupt context
 *
 *   @note
 *******************************************************************************************/
/* CODE CATEGORY 1 START*/
extern void ApplLinDtlError(void);
/* CODE CATEGORY 1 END*/

/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinDtlPretransmitFct                                     */
/*******************************************************************************************/
/**
 *   @brief  Provides acces to the transmit data
 *
 *           Callback function is called when the transmission is enabled.
 *           The data must be provided by the transport layer.
 *
 *   @param_i bLinChannel The interface/channel the task call is relevant for
 *
 *   @param   MessagePtr Pointer to transmit frame data (8 bytes) starting with NAD in first byte
 *
 *   @return  void
 *
 *   @pre     function can be called from task or interrupt context
 *
 *   @note
 *******************************************************************************************/
/* CODE CATEGORY 2 START*/
  extern void ApplLinDtlPretransmitFct(vuint8* MessagePtr);
/* CODE CATEGORY 2 END*/

 #if defined ( LIN_ECUTYPE_SLAVE )
/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinDtlConfirmDiagFrameResp                               */
/*******************************************************************************************/
/**
 *   @brief   Header indication of SlaveResp frame to enable the frame response transmission
 *
 *            Callback function for the application called by the LIN driver
 *            after the header of a SlaveResp frame has been received.
 *            Depending on the return value, the pretransmit handling is executed
 *            and the frame response is transmitted or rejected (no response).
 *
 *   @param_i bLinChannel The interface/channel the task call is relevant for
 *
 *   @return  kLinTpFrameRespConfirm  to confirm the transmission
 *            kLinTpFrameRespReject   to omit the transmission
 *
 *   @pre     No precondition. Function is called from taks level or interrupt
 *
 *******************************************************************************************/
extern vuint8 ApplLinDtlConfirmDiagFrameResp(void);

/* return value definition */
  #define kLinTpFrameRespConfirm                      ((vuint8)0x01u)
  #define kLinTpFrameRespReject                       ((vuint8)0x00u)

 #endif

/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinDtlTxConfirmation                                     */
/*******************************************************************************************/
/**
 *   @brief   Indication of successful transmission of Dtl request
 *
 *            Callback function for the application/Dtl called by the LIN driver
 *            after successful transmission of MasterReq (Master) or SlaveResp (Slave) frame.
 *            Depending on the return value, the transmission continues or response reception is
 *            started Dtl handling is quit without waiting for a response.
 *
 *   @param_i bLinChannel The interface/channel the task call is relevant for
 *
 *   @return  kDtlTxExpectNextFrame  Transmission ongoing (next CF)
 *            kDtlTxCompleteEnableRx Transmission finished and wait for response
 *            kDtlTxCompleteNoRx     Transmission finished and no response expected.
 *
 *   @pre     No precondition. Function is called from taks level or interrupt
 *
 *******************************************************************************************/
/* CODE CATEGORY 2 START*/
extern vuint8 ApplLinDtlTxConfirmation(void);
/* CODE CATEGORY 2 END*/

/* return value definition */
 #define kDtlTxExpectNextFrame                        ((vuint8)0x01u)
 #define kDtlTxCompleteEnableRx                       ((vuint8)0x02u)
 #define kDtlTxCompleteNoRx                           ((vuint8)0x03u)


#endif /* end of lin_tp.h */

