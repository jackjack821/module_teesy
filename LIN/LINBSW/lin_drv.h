/* PRQA S 0288 EOF *//* MD_LIN_DRV_3.1 */
/*******************************************************************************************/
/** @file    lin_drv.h
*   @brief   Export interface of the LIN driver used by the application
*
*            This file provides the API to access the functions provided by the LIN driver
*            Dependent on the selection, either the LIN API of the LIN specification or the
*            enhanced Vector interface is provided
*
********************************************************************************************/

/*******************************************************************************************/
/** @page     lin_drv_h_header Header information of lin_drv.h
********************************************************************************************
*   @par      copyright
*   @verbatim
*
*   Copyright (c) 2000 - 2014 Vector Informatik GmbH          All rights reserved.
*
*   This software is copyright protected and proprietary to Vector Informatik GmbH.
*   Vector Informatik GmbH grants to you only those rights as set out in the
*   license conditions. All other rights remain with Vector Informatik GmbH.
*
*   @endverbatim
********************************************************************************************
*   @par      Authors
*   @verbatim
*     Initials  Name                    Company
*     Wr        Hans Waaser             Vector Informatik GmbH
*     Svh       Sven Hesselmann         Vector Informatik GmbH
*     Ap        Andreas Pick            Vector Informatik GmbH
*     Eta       Edgar Tongoona          Vector Informatik GmbH
*     Fki       Friedrich Kiesel        Vector Informatik GmbH
*     Bmo       Bastian Molkenthin      Vector Informatik GmbH
*   @endverbatim
********************************************************************************************
*  @par          Revision History
*  @verbatim
*
*   Date        Ver     Author Description
*   2004-04-16  2.0     Wr     Rework of the implementation for LIN 2.0 support
*   2004-07-17  2.1     Wr     Added Slave functionality
*   2004-07-17  2.2     Wr     No changes here
*   2004-09-21  2.3     Wr     Extern declaration of version number
*                              Changed internal defines for Version identification
*   2004-11-05  2.4     Wr     No changes here (See lin_drv.c)
*   2004-12-01  2.5     Svh    No changes here (See lin_drv.c)
*   2004-12-08  2.6     Svh    No changes here (See lin_drv.c)
*   2004-12-29  2.7     Wr     ESCAN00010724: Header notification callback function
*   2005-01-17  2.8     Svh    No changes here (See lin_drv.c)
*   2005-02-03  2.9     Svh    ESCAN00010937: Add user defined single frame diagnostic services
*                              ESCAN00010992: Optimization of Code Size and Runtine
*   2005-04-26  2.10    Svh    No changes here (See lin_drv.c)
*   2005-05-17  2.11    Svh    No changes here (See lin_drv.c)
*   2005-06-10  2.12    Svh    ESCAN00012491: Add new options to LIN driver
*   2005-07-06  2.13    Svh    No changes here (See lin_drv.c)
*   2005-09-07  2.14    Svh    No changes here (See lin_drv.c)
*   2005-10-25  2.15    Svh    ESCAN00013694: Reduce code size by using one function for different configuration API functions
*   2005-11-09  2.16    Svh    No changes here (See lin_drv.c)
*   2005-11-17  2.17    Svh    ESCAN00014303: Increase maximum number of user defined diagnostic services to 10 and improve handling
*                              ESCAN00014304: Use typedefs for all counter that could become 16bit values
*                              ESCAN00014312: Add interface for SIO driver with SIO_LL_APISTYLE_MESSAGE and SIO_LL_APITYPE_HEADER_IND
*                              ESCAN00014497: Add Tlcs870 specific code
*                              ESCAN00014538: Response to SlaveResp is transmitted though it should not
*   2006-01-27  2.18    Svh    ESCAN00015099: Implement interface for controller with synch indication
*                              ESCAN00015110: Message timeout observation is not working correctly
*   2006-02-03  2.19    Svh    ESCAN00015128: Add feature MultiEcu to LIN driver
*   2006-02-06  2.20    Ap     ESCAN00015234: Support for extended LinLowSendHeader interface
*   2006-03-02  2.21    Svh    ESCAN00015509: Wrong compiler error directive for LIN slave with LIN protocol version 1.2/3
*   2006-03-15  2.22    Svh    ESCAN00015695: Add 78k0 specific code
*   2006-03-28  2.23    Svh    ESCAN00015848: Adapt code to CodeVisionAVR C Compiler
*                              ESCAN00015849: Adapt 78k0 specific check to be only for LIN UART
*   2006-04-05  2.24    Svh    ESCAN00015936: Bus Idle observation is not working correctly
*   2006-05-12  2.25    Svh    ESCAN00016326: Incorrect return value of LinInitPowerOn() / l_sys_init()
*                              ESCAN00014867: CANbedded internal indication flag
*                              ESCAN00016382: Add ApplLinXcpResponseFct for XcpOnLin handling
*   2006-07-31  2.26    Ap     ESCAN00017146: Bus idle detection support for MAC7100
*   2006-08-02  2.27    Svh    ESCAN00016936: Multiple Identities incorrect handled for LIN 1.x
*                              ESCAN00017076: Wrong return value description in comment of function ApplLinScGetSerialNumber
*                              ESCAN00016676: Add support for J2602 slave status byte
*                              ESCAN00017165: Implement repetition of sleep mode frame
*   2006-08-09  2.28    Svh    ESCAN00017214: Add 78k0 specific code for NEC Compiler
*   2006-09-26  2.29    Svh    ESCAN00017674: Reception of Incorrect Synch Field is not reported as Data Error
*                       Ap     ESCAN00017860: MPC5500: Transition to bus sleep not performed when short to ground or Vbatt for 4 seconds
*   2006-10-10  2.30    Ap     ESCAN00017980: Parameter of type V_NULL  "void *" is incompatible with function parameter of type "vuint8 *"
*   2006-11-08  2.31    Svh    ESCAN00018300: Use bit 5 in status byte for bus activity encoding and application notification
*                              ESCAN00018301: Make Goto Sleep bit configurable when to set it: never, after sleep frame transmission or in l_ifc_goto_sleep
*   2006-11-29  2.32    Ap     ESCAN00018550: Compile error if only InitTx default values or InitRx default values is configured
*                              ESCAN00018565: No interrupt protection for l_ifc_goto_sleep()
*   2007-01-16  2.33    Ap     ESCAN00018839: LIN 2.1 support
*                       Ap     ESCAN00018254: Implement interrupt control by application
*   2007-02-01  2.34    Svh    ESCAN00019346: Add Fj8fx specific code
*                              ESCAN00019347: Use defines instead of values and add 'u' to fixed values
*   2007-02-16  2.35    Svh    ESCAN00019633: If 'Sleep Mode Frame Repetition' is used, LinStart() is accepted directly after LinStop() has been called
*   2007-02-22  2.36    Svh    ESCAN00019716: Pretransmit function not called and data not correct for Sporadic frames
*                              ESCAN00019717: Add call back function for synch break notification
*                              ESCAN00019762: Error reporting to frame processor in case of new synch break detection while on header detection added
*   2007-02-28  2.37    Ap     ESCAN00019784: Cast required for strict compiler warning level
*   2007-03-09  2.38    Ap     ESCAN00019897: Diagnostic interface to ConfigAPI, TpLIN and Appl restructured
*   2007-03-20  2.39    Ap     ESCAN00020020: Compatibility support for SlaveResp suppress in Master by Tp or Application
*                       Ap     ESCAN00020022: Pending configuration API request not indicated by return value of ld_is_ready()
*   2007-04-24  2.40    Svh    ESCAN00020119: J2602 status bits are not reset correctly
*                       Ap     ESCAN00020476: Diagnostic dispatching in slave restructured
*   2007-06-14  2.41    Svh    ESCAN00020639: Schedule table L_NULL_SCHEDULE not necessary to be set before l_ifc_goto_sleep
*                       Ap     ESCAN00021053: Cast required for strict compiler warning level (arithmetic operations)
*                       Ap     ESCAN00021073: Support for dynamic signal value and signal notification flag API
*                       Ap     ESCAN00020919: Wrong PID is given in l_ifc_read_status for errornous messages
*                       Ap     ESCAN00021077: MasterReq and SlaveResp confirmation/indication flag handling not performed for TP and config API
*   2007-07-06  2.42    Ap     ESCAN00021148: Slave Configuration API not accessible from Vector API
*                       Ap     ESCAN00021300: Schedule table change and network state transition not independent
*                       Ap     ESCAN00021314: Declaration of response omitted timeout required for LIN 2.1 Slaves
*   2007-07-16  2.43    Ap     ESCAN00021457: Valid AssignFrameIDRange command quit with negative response and configuration command not accepted
*                       Ap     ESCAN00021458: Wakeup frame indication clears entry parameter of pending schedule table change request
*   2007-07-31  2.44    Ap     ESCAN00021611: Support configuration command AssignFrameIDRange for multiple ECU
*                       Svh    ESCAN00021694: Save Configuration Command can not be enabled
*                              ESCAN00021752: Array index can be below zero for access to MasterReq Confirmation Flag
*   2007-08-13  2.45    Svh    ESCAN00021534: Event Triggered Frame is not transmitted if signal is changed during transmission of event triggered frame response
*   2007-10-12  2.46    Ap     ESCAN00022538: Support for configurations implementing a master and slave node in one ECU
*                       Ap     ESCAN00022593: Undefined element kScRxFrameNotHandled leads to compile error
*                       Ap     ESCAN00022726: Sporadic frame is transmitted without request
*   2007-10-26  2.47    Svh    ESCAN00023006: Reception of framing error in Tx messages is not reported as Byte Field Framing Error but as Data Error
*                              ESCAN00023019: Rx message with no bytes received leads to setting the error in response bit and is reported to application
*                       Ap     ESCAN00022961: Truncating assignment may lead to compile error
*   2007-11-26  2.48    Wr     ESCAN00023187: Timeout observation support for Slc8051
*                       Ap     ESCAN00023141: During noise on LIN bus idle timer expires erroneous and ECU will go to sleep
*   2007-12-19  2.49    Svh    ESCAN00023825: Rx messages with no response cause setting the error in response bit and reporting to application for standard UART
*   2008-01-09  2.50    Ap     ESCAN00023918: Memory mapping support added
*                       Ap     ESCAN00023952: Conditional change NAD command may not answered if match operation fails
*                       Ap     ESCAN00023995: Add Fj16fx specific code
*   2008-02-22  2.51    Ap     ESCAN00024341: Error in LIN master rx frame response not reported to application
*                       Ap     ESCAN00024534: When receiving an external wakeup request bus idle timer not set
*   2008-04-07  2.52    Svh    ESCAN00025741: Optimization of source code to reduce resource consumption
*                              ESCAN00025066: warning: variable "bLinNodeConfigurationStatus" was declared but never used
*                              ESCAN00025820: SioMuteModePolling function required for baudrate detection of R8C
*   2008-04-10  2.53    Svh    ESCAN00026008: Compiler error due to unknown symbol
*                              ESCAN00026009: AssignFrameIdRange is not working
*   2008-04-18  2.54    Svh    ESCAN00026141: MasterReq header is always transmitted
*                              ESCAN00026171: Call back function ApplSioBaudrateInformation for detected baud rate added
*   2008-06-11  2.55    Ap     ESCAN00027523: Header and Response timeout observation for LIN Ctrl interface added
*                       Ap     ESCAN00027529: Compile error setbLinConfiguredNAD() undefined
*   2008-07-01  2.56    Ap     ESCAN00028000: Invalid read access to structure cabLinRxTxMsgInfo[]
*   2008-07-15  2.57    Svh    ESCAN00028434: Add Tms470 specific code
*   2008-08-22  2.58    Svh    ESCAN00029413: Searching of handle not required for header indication handling
*                              ESCAN00028862: Diagnostic service SupplierID and FunctionID check fail
*   2008-09-29  2.59    Svh    ESCAN00030326: New feature 'Baud Rate Information Callback' added
*   2008-10-13  2.60    Ap     ESCAN00030534: Symbol LABEL_SKIP_DIAGHEADER not found during compilation
*                       Ap     ESCAN00030602: Segmented transport layer transmission abort due invalid new request
*                       Ap     ESCAN00030615: A pending response is cleared when error in response of new MasterReq occures
*                       Ap     ESCAN00030630: Add H8SX specific code
*   2008-11-14  2.61    Ap     ESCAN00031038: Add MPC55xx specific code
*                       Ap     ESCAN00031317: Lost prioritization error notification encapsulated
*                       Svh    ESCAN00031321: Compiler warning due to unused parameters and local variables
*                       Svh    ESCAN00031412: Error code kLinNoResponse seperated in kLinNoResponse and kLinErrInResponse
*   2008-12-03  2.62    Ap     ESCAN00031580: SlaveResp frame send without preceding MasterReq frame
*   2009-01-19  2.63    Eta    ESCAN00032162: Add support for M16C5L
*                       Ap     ESCAN00032289: Application access to bDdDispatcherTxState necessary to send positive response after flashing
*                       Ap     ESCAN00032028: Return value definition not according LIN specification
*   2009-09-02  2.64    Ap     ESCAN00034433: Mute mode polling support for SH2 required
*                              ESCAN00035263: Diagnostic functional request will abort pending physical node configuration response
*   2009-09-15  2.65    Ap     ESCAN00037752: Calculation of event triggered frame handle incorrect
*   2009-11-20  2.66    Eta    ESCAN00039315: Idle detection timer not restarted upon receiving a break
*   2010-05-06  2.67    Fki    ESCAN00042785: Support mixed AUTOSAR - Canbedded configurations
*   2010-06-16  2.68    Fki    ESCAN00043452: Add Fj16lx specific code
*                              ESCAN00035058: warning vLoopCount: unreferenced local variable
*   2010-08-26  2.69    Fki    ESCAN00044883: Allow external wakup in 1.5sec pause after third failed wake up transmission
*                       Ap     ESCAN00044888: Add end of schedule table indication
*                       Ap     ESCAN00044411: Add LIN bootloader specific code
*   2010-10-27  2.70    Ap     ESCAN00046433: Support XCP on LIN master nodes
*                       Ap     ESCAN00046434: Application diagnostic services interface changed
*   2011-01-25  2.71    Eta    ESCAN00047816: Support XCP on multi channel LIN master nodes
*                       Ap     ESCAN00048188: Support Assign NAD via SNPD command
*                       Ap     ESCAN00048189: Diagnostic response after new request with failure in frame response
*   2011-02-11  2.72    Ap     ESCAN00046087: Support for multi channel LIN slave node
*                       Ap     ESCAN00048346: Resolved compiler warning "Precision lost"
*   2011-05-26  2.73    Ap     ESCAN00050309: LIN low level driver initialization function not called
*                       Ap     ESCAN00050385: LIN slave protocol compatibility mode
*                       Ap     ESCAN00050939: Three sleep mode frame support
*                       Ap     ESCAN00051061: response_error signal in multiple frames
*   2011-06-08  2.74    Ap     ESCAN00051336: Add a check for frames that are not finished at the end of the schedule slot to the schedule task
*   2011-08-16  2.75    Ap     ESCAN00052326: response_error signal configurable
*                       Ap     ESCAN00051832: Monitoring error is reported as Byte Field Framing Error instead of Data Error
*   2011-09-19  2.76    Ap     ESCAN00053692: Provide API to activate or inactivate the bus idle timeout observation
*   2011-10-20  2.77    Ap     ESCAN00053855: Support for Misra annotations in code
*                       Ap     ESCAN00054026: Support timeout on node configuration service
*                       Ap     ESCAN00054195: ld_set_configuration() / LinSetConfiguration() API uses incorrect PID order
*                       Ap     ESCAN00054243: Support Targeted Reset command handing as node configuration service
*                       Ap     ESCAN00054353: Negative response transmitted on some IDs for ReadById service 0xB2 if no response is expected
*   2012-03-15  2.78.00 Ap     ESCAN00055970: External function declaration of application specific diag services with incorrect signature
*                       Ap     ESCAN00056266: Frame timeout check by scheduler for message interface driver without frame timeout
*                       Ap     ESCAN00056260: Conditional change NAD command with incorrect positive response
*                       Ap     ESCAN00056534: Functional request will interrupt physical node configuration response transmission
*                       Ap     ESCAN00057406: Schedule table active confirmation
*   2012-04-10  2.78.01 Fki    ESCAN00058228: Add Support for extended error reporting in frame timeout function
*   2012-05-09  2.79.00 Ap     ESCAN00058689: Slave specific define for indexed implementation
*                       Ap     ESCAN00058804: Support for multiple sporadic frame slots
*                       Ap     ESCAN00058828: Assignment of PID to frame with currently unassigned PIDs does not work
*                       Ap     ESCAN00058917: Send negative response on RDBI mismatch of supplier or function ID
*                       Ap     ESCAN00058947: Support J2602 in compatibility mode
*   2012-07-26  2.79.01 Ap     ESCAN00059876: Wrong defines used to access PID handles
*                       Ap     ESCAN00060346: Multiple ECU slave PID assignment incorrect
*   2012-11-07  2.79.02 Ap     ESCAN00061922: In J2602 compatibility mode some node configuration services are incorrect
*   2012-11-26  2.80.00 Ap     ESCAN00062606: Supplier ID by application
*                       Ap     ESCAN00062608: Message ID by Application
*   2013-03-15  2.81.00 Ap     ESCAN00064855: Support for AssignFrameIdRange and SaveConfiguration in J2602 compatibility mode
*                       Ap     ESCAN00065552: Support for NAD in full range
*   2013-04-10  2.81.01 Ap     ESCAN00066126: J2602 parity error reported
*                       Ap     ESCAN00066324: Paramater added to ApplLinScTargetedReset to differentiate between targeted and broadcast reset
*   2013-06-25  2.81.02 Ap     ESCAN00066911: Report current protocol version to low level driver in case of compatibility mode
*                       Bmo    ESCAN00068323: Add memory sections for FBL
*   2013-08-21  2.81.03 Ap     ESCAN00069912: Support bus idle timeout mode in hardware
*                       Ap     ESCAN00069916: Diagnostic session abort
*                       Ap     ESCAN00069954: Send no response on RDBI mismatch of supplier or function ID for LIN 2.0 nodes
*   2013-09-23  2.82.00 Ap     ESCAN00070590: Support for dynamic AssignNAD handling
*                       Ap     ESCAN00070588: Wrong handle reported in ApplLinScheduleActiveConfirmation() after EVT-frame collision
*                       Ap     ESCAN00070854: Support for response_error bit according to LIN2.1 in case of no response
*   2014-01-15  2.82.01 Ap     ESCAN00072171: Illegal memory access when entering sleep mode
*   2014-02-06  2.82.02 Ap     ESCAN00073511: No full wake up transition performed if no frame responses are transmitted after wake up
*   2014-02-26  2.82.03 Ap     ESCAN00073950: Compile error in case of bus idle detection by hardware and LIN API
*   2014-05-16  2.82.04 Eta    ESCAN00073954: LIN master only: support header notification and error in header reporting
*                       Ap     ESCAN00075716: Alternative signature for ApplLinLowErrorIndication() created with additional bus inactivity indication added
*   2014-07-07  2.83.00 Ap     ESCAN00076838: Bus idle API extended to allow hardware detection in byte interface and application level reset of timer
*   2014-07-28  2.83.01 Ap     ESCAN00077447: kFpError_HeaderRxSynchField not defined for LIN master
*   2014-09-01  2.83.02 Ap     ESCAN00078198: Compile error in case of bus idle detection and byte interface
*
*  \endverbatim
********************************************************************************************/


#ifndef __LIN_DRV_H__
 #define __LIN_DRV_H__

/*******************************************************************************************/
/* Version                  (abcd: Main version ab Sub Version cd )                        */
/*******************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : DrvLin__core CQComponent : Implementation */
 #define DRVLIN__CORE_VERSION                     0x0283u
 #define DRVLIN__CORE_RELEASE_VERSION             0x02u

/*******************************************************************************************/
/** Version Configuration Check                                                            */
/*******************************************************************************************/
 #if !defined ( LIN_PROTOCOLVERSION_VALUE )
  #if defined ( LIN_PROTOCOLVERSION_22 )
   #define LIN_PROTOCOLVERSION_VALUE       0x22u
  #elif defined ( LIN_PROTOCOLVERSION_21 )
   #define LIN_PROTOCOLVERSION_VALUE       0x21u
  #elif defined ( LIN_PROTOCOLVERSION_20 )
   #define LIN_PROTOCOLVERSION_VALUE       0x20u
  #elif defined ( LIN_PROTOCOLVERSION_13 )
   #define LIN_PROTOCOLVERSION_VALUE       0x13u
  #elif defined ( LIN_PROTOCOLVERSION_12 )
   #define LIN_PROTOCOLVERSION_VALUE       0x12u
  #else
   #error "LIN Protocol version definition missing or not specified correctly."
  #endif
 #else
  #if ( LIN_PROTOCOLVERSION_VALUE == 0x21u )
   #if !defined ( LIN_PROTOCOLVERSION_21 )
    #define LIN_PROTOCOLVERSION_21
   #endif
  #endif
 #endif


/*******************************************************************************************/
/* Global constants with LIN driver main and subversion                                    */
/*******************************************************************************************/
/* ROM CATEGORY 4 START*/
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kLinDrvMainVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kLinDrvSubVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kLinDrvReleaseVersion;
/* ROM CATEGORY 4 END*/


/* LIN protocol errors signalized by ApplLinProtocolError() */
 #define kLinNoHeader                  ((vuint8) 0x01u)
 #define kLinNoResponse                ((vuint8) 0x02u)
 #define kLinErrInResponse             ((vuint8) 0x06u)
 #define kLinSynchFieldError           ((vuint8) 0x05u)    /* Only slave */
 #define kLinChecksumError             ((vuint8) 0x07u)
 #define kLinBitError                  ((vuint8) 0x08u)
 #define kLinFormatError               ((vuint8) 0x09u)
 #define kLinLostPriorization          ((vuint8) 0x0Bu)
 #define kLinErrInHeader               ((vuint8) 0x0Cu)    /* Only for master */
/* Errors only indicated, when API_STYLE_VECTOR is activated */
 #define kLinNoBusWakeUp               ((vuint8) 0x04u)
/* Errors only indicated, when API_STYLE_VECTOR is activated or if specific LIN hardware interface support */
 #define kLinNoBusActivity             ((vuint8) 0x03u)    /* Only slave. Master indicates Physical Bus Error */
 #define kLinPhysicalBusError          ((vuint8) 0x0Au)


/* LIN driver errors signalized by ApplLinFatalError() when debug mode is enabled */
 #define kLinErrorScheduleTableHandle  ((vuint8) 0x01u)
 #define kLinErrorScheduleTableEntry   ((vuint8) 0x02u)
 #define kLinErrorWakeUpReason         ((vuint8) 0x03u)
 #define kLinErrorWakeUpScheduleState  ((vuint8) 0x04u)
 #define kLinErrorSynchField           ((vuint8) 0x05u)
 #define kLinErrorIdentifierField      ((vuint8) 0x06u)
 #define kLinErrorChecksumField        ((vuint8) 0x07u)
 #define kLinErrorWrongMsgHandle       ((vuint8) 0x08u)
 #define kLinErrorWrongEcuHandle       ((vuint8) 0x09u)
 #define kLinErrorTxDataPtr            ((vuint8) 0x0Au)
 #define kLinErrorIllegalDriverState   ((vuint8) 0x0Bu)
 #define kLinErrorFrameDistance        ((vuint8) 0x0Cu)
 #define kLinErrorScheduleTable        ((vuint8) 0x0Du)
 #define kLinErrorGenTxDataLen         ((vuint8) 0x0Eu)
 #define kLinErrorGenPreTxFunc         ((vuint8) 0x0Fu)
 #define kLinErrorGenTxConfFunc        ((vuint8) 0x10u)
 #define kLinErrorGenRxDataLen         ((vuint8) 0x11u)
 #define kLinErrorGenPreRxFunc         ((vuint8) 0x12u)
 #define kLinErrorGenRxIndFunc         ((vuint8) 0x13u)
 #define kLinErrorGenRxId              ((vuint8) 0x14u)
 #define kLinErrorGenRxReservedId3E    ((vuint8) 0x15u)
 #define kLinErrorGenRxReservedId3F    ((vuint8) 0x16u)
 #define kLinErrorWrongDataHandle      ((vuint8) 0x19u)
 #define kLinErrorWrongDataPointer     ((vuint8) 0x1Au)
 #define kLinErrorMsgFrameOverflow     ((vuint8) 0x1Bu)
 #define kLinErrorScheduleTableLength  ((vuint8) 0x1Cu)
 #define kLinErrorMessageOverrun       ((vuint8) 0x1Du)
 #define kLinErrorWrongTxMsgQueue      ((vuint8) 0x1Eu)
 #define kLinErrorWrongRxMsgQueue      ((vuint8) 0x1Fu)

 #define kLinErrorNoScheduleTableSet   ((vuint8) 0x20u)
 #define kLinErrorNoLinInitPowerOn     ((vuint8) 0x21u)
 #define kLinErrorIdentifierReserved   ((vuint8) 0x22u)

 #if defined ( LIN_ENABLE_SLAVE_CONFIGURATION )
  #define kLinErrorScInvalidLength     ((vuint8) 0x60u)
  #define kLinErrorScInvalidParam      ((vuint8) 0x61u)
 #endif



/*******************************************************************************************/
/*       COMMON API PART                                                                   */
/*******************************************************************************************/

/* Mapping of dynamic API to generated static function calls            */
/* sig and flag refer to the signal and flag name string                */
/* this contains channel suffixes in multi channel configurations       */

/* scalar signal access with dynamic API */
/* PRQA S 0342 16 *//* MD_LIN_DRV_19.13 */
 #define l_bool_rd(sig)                    l_bool_rd_ ##sig()
 #define l_u8_rd(sig)                      l_u8_rd_ ##sig()
 #define l_u16_rd(sig)                     l_u16_rd_ ##sig()

 #define l_bool_wr(sig, v)                 l_bool_wr_ ##sig(v)
 #define l_u8_wr(sig, v)                   l_u8_wr_ ##sig(v)
 #define l_u16_wr(sig, v)                  l_u16_wr_ ##sig(v)

/* byte array access with dynamic API */
 #define l_bytes_rd(sig,start,count,sdata)  l_bytes_rd_ ##sig((start),(count),(sdata))
 #define l_bytes_wr(sig,start,count,sdata)  l_bytes_wr_ ##sig((start),(count),(sdata))

/* notification with dynamic API */
 #define l_flg_tst(flag)                   l_flg_tst_ ##flag()
 #define l_flg_clr(flag)                   l_flg_clr_ ##flag()

/* All message and signal related interfaces and callback functions are
   provided by lin_par.h */


 #if defined ( LIN_ENABLE_DYN_SCHEDULE_API )
/*******************************************************************************************/
/* Typedefinition for schedule table passed to dynamic schedule table API                  */
/* vFrameHandle   Reference to frame which can be taken from lin_par.h                     */
/* vFrameDistance Slot delay of frame in multiple of schedule task cycle                   */
/* The first schedule table entry contain the number of scheduled frames in vFrameHandle   */
/* vFrameDistance is not relevant in this case. See lin_par.c for schedule table examples. */
/*******************************************************************************************/
typedef struct tLinDynSchedTblEntryTypeTag
{
  vuint8 vFrameHandle;
  vuint8 vFrameDistance;
} tLinDynSchedTblEntryType;
 #endif


/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinProtocolError                                         */
/*******************************************************************************************/
/**
 *   @brief   (M,S) Indication of protocol errors detected by the LIN driver
 *
 *            Callback function for the application called by the LIN driver
 *            after a LIN protocol error has been detected.
 *
 *   @param_i linchannel The interface/channel which detected the error
 *   @param   error The error code of the detected error
 *   @param   vMsgHandle The handle of the message processed when the error
 *            is detected. When no message can be assigned, kMsgHandleDummy
 *            is used
 *
 *   @return  void none
 *
 *   @context Called by the driver in interrupt or task context
 *
 *   @pre     No precondition. Function is called from task level or interrupt.
 *
 *******************************************************************************************/
/* CODE CATEGORY 1 START*/
extern void ApplLinProtocolError(vuint8 error, tLinFrameHandleType vMsgHandle );
/* CODE CATEGORY 1 END*/

/* Parameter used, when error cannot be assigned to one message*/
 #define kMsgHandleDummy ((vuint8) 0xFFu)


/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinFatalError                                            */
/*******************************************************************************************/
/**
 *   @brief   (M,S) Indication of fatal errors detected by the LIN driver
 *
 *            Callback function for the application called by the LIN driver
 *            after a LIN fatal error has been detected.
 *            This can be caused by an inconsistent configuration, an inconsistent
 *            internal state or the usage of a function parameter out of the
 *            allowed range. The call of the function must be observed during
 *            development
 *
 *   @param_i linchannel The interface/channel which detected the error
 *   @param   error The error code of the detected error
 *
 *   @return  void none
 *
 *   @context Called by the driver in interrupt or task context
 *
 *   @pre     No precondition.
 *
 *******************************************************************************************/
/* CODE CATEGORY 1 START*/
extern void ApplLinFatalError(vuint8 error);
/* CODE CATEGORY 1 END*/

 #if defined ( LIN_ENABLE_SYNCHBREAK_NOTIFICATION )
/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinSynchBreakNotification                                */
/*******************************************************************************************/
/**
 *   @brief   (M, S) Notification of a synch break
 *
 *            The callback function can be configured to be called for each synch break
 *            transmitted or received.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   void none
 *
 *   @return  void none
 *
 *   @context Called by the driver in interrupt context
 *
 *   @pre     No precondition.
 *
 *******************************************************************************************/
/* CODE CATEGORY 1 START*/
extern void ApplLinSynchBreakNotification(void);
/* CODE CATEGORY 1 END*/
 #endif

 #if defined ( LIN_ECUTYPE_SLAVE )
  #if defined ( LIN_ENABLE_HEADER_NOTIFICATION )
/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinHeaderDetection                                       */
/*******************************************************************************************/
/**
 *   @brief   (S) Notification of a received header
 *
 *            The callback function can be configured to be called for each header or only
 *            for one preconfigured header.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   FrameHandle The handle which corresponds to the received header.
 *
 *   @return  void none
 *
 *   @context Called by the driver in interrupt context
 *
 *   @pre     No precondition.
 *
 *******************************************************************************************/
extern void ApplLinHeaderDetection(tLinFrameHandleType FrameHandle);
  #endif
 #endif

 #if defined ( LIN_ECUTYPE_SLAVE )
  #if defined ( SIO_LL_ENABLE_BAUDRATE_INFORMATION )
   #if defined ( SIO_ENABLE_BAUDRATE_DETECT )
    #if defined ( LIN_ENABLE_BAUDRATE_INFORMATION )
/*******************************************************************************************/
/*    CALLBACK FUNCTION:  ApplLinBaudrateInformation                                       */
/*******************************************************************************************/
/**
 *   @brief   (S) Indication of a detected baud rate
 *
 *            The callback function is called by the LIN driver detection of a valid baud
 *            rate. The given baud rate is an index to the currently detected baud rate.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   bBaudrate  The baud rate detected
 *
 *   @return  No return value
 *
 *******************************************************************************************/
/* CODE CATEGORY 1 START*/
extern void ApplLinBaudrateInformation (vuint8 bBaudrate);
    #endif
   #endif
  #endif
 #endif


/* Service IDs used for the Slave Configuration  */
 #define kSID_AssignNAD           ((vuint8) 0xB0u)
 #define kSID_AssignFrameId       ((vuint8) 0xB1u)
 #define kSID_ReadById            ((vuint8) 0xB2u)
 #define kSID_CondChangeNAD       ((vuint8) 0xB3u)
 #define kSID_DataDump            ((vuint8) 0xB4u)
 #define kSID_AssignNADviaSNPD    ((vuint8) 0xB5u)
 #define kSID_J2602TargetedReset  ((vuint8) 0xB5u)
 #define kSID_SaveConfiguration   ((vuint8) 0xB6u)
 #define kSID_AssignFrameIdRange  ((vuint8) 0xB7u)

 #define kRSID_AssignNAD          ((vuint8) 0xF0u)
 #define kRSID_AssignFrameId      ((vuint8) 0xF1u)
 #define kRSID_ReadById           ((vuint8) 0xF2u)
 #define kRSID_CondChangeNAD      ((vuint8) 0xF3u)
 #define kRSID_DataDump           ((vuint8) 0xF4u)
 #define kRSID_AssignNADviaSNPD   ((vuint8) 0xF5u)
 #define kRSID_J2602TargetedReset ((vuint8) 0xF5u)
 #define kRSID_SaveConfiguration  ((vuint8) 0xF6u)
 #define kRSID_AssignFrameIdRange ((vuint8) 0xF7u)

 #define kRSID_NegativeResp       ((vuint8) 0x7Fu)





 #if defined ( LIN_ECUTYPE_SLAVE )
  #define kLinFrameRespConfirm      ((vuint8)  0x01u)
  #define kLinFrameRespReject       ((vuint8)  0x00u)
  #if defined ( LIN_ENABLE_DIAGFRAME_BY_APPL )
/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinConfirmDiagFrameResp                                  */
/*******************************************************************************************/
/**
 *   @brief   (S) Header indication of SlaveResp frame to enable the frame response transmission
 *
 *            Callback function for the application called by the LIN driver
 *            after the header of a SlaveResp frame has been received.
 *            Corresponding to the return value, the pretransmit handling is executed
 *            and the frame response is transmitted
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   void none
 *
 *   @return  kLinFrameRespConfirm  confirm the transmission of the response
 *   @return  kLinFrameRespReject   omit the transmission of the response
 *
 *   @context Called by the driver in interrupt context
 *
 *   @pre     No precondition. Function is called from interrupt level.
 *
 *******************************************************************************************/
extern vuint8 ApplLinConfirmDiagFrameResp(void);

  #endif
  #if defined ( LIN_ENABLE_MSGRESPONSE_FCT )

/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinFrameResponseFct                                      */
/*******************************************************************************************/
/**
 *   @brief   (S) Header indication of a transmit frame to enable the frame response transmission
 *
 *            Callback function for the application called by the LIN driver
 *            after the header of a transmit frame has been received.
 *            Corresponding to the return value, the pretransmit handling is executed
 *            and the frame response is transmitted.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   bLinMsgHandle handle of the Tx frame
 *
 *   @return  kLinFrameRespConfirm  to confirm the transmission
 *   @return  kLinFrameRespReject   to omit the transmission
 *
 *   @context Called by the driver in interrupt context
 *
 *   @pre     No precondition.
 *
 *******************************************************************************************/
extern vuint8 ApplLinFrameResponseFct(tLinFrameHandleType bLinMsgHandle);

  #endif
  #if defined ( LIN_ENABLE_XCPONLIN )

/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinXcpResponseFct                                        */
/*******************************************************************************************/
/**
 *   @brief   (S) Header indication of a the Xcp response transmit frame to enable or
 *            disable the frame response transmission
 *
 *            Callback function for the Cp_XcpOnLin component called by the LIN driver
 *            after the header of the Xcp response transmit frame has been received.
 *            Corresponding to the return value, the pretransmit handling is executed
 *            and the frame response is transmitted or the handling is skipped.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   void none
 *
 *   @return  kLinFrameRespConfirm  to confirm the transmission
 *   @return  kLinFrameRespReject   to omit the transmission
 *
 *   @context Called by the driver in interrupt context
 *
 *   @pre     No precondition.
 *
 *******************************************************************************************/
extern vuint8 ApplLinXcpResponseFct(void);

  #endif



  #if defined ( LIN_ENABLE_SLEEP_COMMAND_REPETITION )
/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinPreBusSleep                                           */
/*******************************************************************************************/
/**
 *   @brief   (S) Notification of a sleep mode frame reception
 *
 *            The transition to sleep mode is performed after the third
 *            reception of a sleep mode frame
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   repetition Number of the sleep command frame received in the sequence of three
 *            sleep commands starting with value one.
 *
 *   @return  void none
 *
 *   @context Function is called by the driver in interrupt context.
 *
 *   @pre     No precondition.
 *
 *******************************************************************************************/
/* CODE CATEGORY 2 START*/
extern void ApplLinPreBusSleep(vuint8 repetition);
/* CODE CATEGORY 2 END*/
  #endif


 #endif /* LIN_ECUTYPE_SLAVE */



 #if defined ( LIN_ECUTYPE_SLAVE )
  #if defined ( LIN_ENABLE_SLAVE_CONFIGURATION )
   #if defined ( LIN_ENABLE_ASSIGN_NAD_COMMAND_DYN )
/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinScDynAssignNAD                                        */
/*******************************************************************************************/
/**
 *   @brief   (S) Request Assign NAD received
 *
 *            THE USAGE MAY AFFECT LIN CONFORMITY
 *
 *            Special purpose callback!
 *            This callback allows to specify on application level and during runtime
 *            if an assign NAD command is accepted and if a reponse is transmitted.
 *
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   pbMsgDataPtr received Assign NAD command starting with first byte: InitialNAD
 *
 *   @return  kLinSc_Confirm_ASSING_NAD_COMMAND  Send a positive response and accept NAD configuration
 *   @return  kLinSc_Reject_ASSING_NAD_COMMAND   Send a negative response and reject NAD configuration
 *   @return  kLinSc_Ignore_ASSING_NAD_COMMAND   Send no response and reject NAD configuration
 *
 *   @context Called by the driver in interrupt context
 *
 *   @pre     No precondition.
 *
 *******************************************************************************************/
vuint8 ApplLinScDynAssignNAD(const vuint8* const pbMsgDataPtr);
    #define kLinSc_Confirm_ASSING_NAD_COMMAND    ((vuint8) 0x00u)
    #define kLinSc_Reject_ASSING_NAD_COMMAND     ((vuint8) 0x01u)
    #define kLinSc_Ignore_ASSING_NAD_COMMAND     ((vuint8) 0x02u)
   #endif


   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE ) || defined ( LIN_ENABLE_ASSIGN_ID_BY_APPL )
/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinScAssignId                                            */
/*******************************************************************************************/
/**
 *   @brief   (S) Request Assign Frame Id received
 *
 *            In case the slave configuration is based on a LIN 2.1 LDF but
 *            the LIN 2.0 AssignId command should also be supported for compatibility
 *            reasons this callback indicates the reception of a AssignId command with
 *            correct NAD and supplier ID. Its up to the application to check the MessageId
 *            (the 16bit MessageIds are user defined as not specified for LIN 2.1 nodes in the LDF).
 *            If the MessageId is correct the PID received and provided in parameter bPID
 *            should be assigned to the table cabLinSlaveProtectedIdTbl[]. See the
 *            documentation for more information on this topic. If the MessageId does not match
 *            quit the routine with kLinSc_AssignIdSendNegativeResponse.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   wMessageId received MessageId in the AssignId command
 *   @param   bPID       received new PID which should be assigned if the MessageId matches
 *
 *   @return  kLinSc_AssignIdSendNegativeResponse  Send a negative response if optional response has been enabled
 *   @return  kLinSc_AssignIdSendPositiveResponse  Send a positive response if optional response has been enabled
 *
 *   @context Called by the driver in interrupt context
 *
 *   @pre     No precondition.
 *
 *******************************************************************************************/
extern vuint8 ApplLinScAssignId(vuint16 wMessageId, vuint8 bPID);
    #define kLinSc_AssignIdSendNegativeResponse    ((vuint8) 0x00u)
    #define kLinSc_AssignIdSendPositiveResponse    ((vuint8) 0x01u)
   #endif

   #if defined ( LIN_ENABLE_READ_BY_ID_BY_APPL )
    #if defined ( LIN_APISTYLE_VECTOR )
/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinScGetSerialNumber                                     */
/*******************************************************************************************/
/**
 *   @brief   (S) Request Read by identifier, identifier "Serial Number" received
 *
 *            The slave configuration has received the service request
 *            Read by Identifier. The received identifier 1 is defined to be
 *            the serial number. When the application wants to provide the serial
 *            number, it returns kLinSc_SendSerialNr. In this case, four bytes must
 *            be written to the received pointer in the format
 *            Serial 0 (LSB), Serial1, Serial2, Serial3 (MSB)
 *            at least before the following slave response frame is received.
 *            When no serial number should be provided, the return value is
 *            kLinSc_NoSerialNr.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   pbSerialNumber pointer to write the serial number
 *
 *   @return  kLinSc_SendSerialNr  Service response will be send
 *   @return  kLinSc_NoSerialNr    Subservice not supported will be send
 *
 *   @context Called by the driver in interrupt context
 *
 *   @pre     No precondition.
 *
 *******************************************************************************************/
extern vuint8 ApplLinScGetSerialNumber(vuint8* pbSerialNumber);
     #define kLinSc_SendSerialNr 0
     #define kLinSc_NoSerialNr   6


/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinScGetUserDefinedId                                    */
/*******************************************************************************************/
/**
 *   @brief   (S) Request Read by identifier, identifier "Userdefined" received
 *
 *            The slave configuration has received the service request
 *            Read by Identifier. The received identifier is in the user defined
 *            range of 32 - 63.
 *            When the application wants to provide response data to the request, it
 *            returns the length of diagnostic data in the range 1 - 5 (user defined length).
 *            In this case, the response data to the requested identifier must be written
 *            to the pointer parameter.
 *            The application must always write 5 bytes, at least before the
 *            following slave response frame header is received. When the returned length
 *            is between 1 and 4, the unused bytes must be set to 0xFF.
 *            When the requested identifier should not be provided, the return value is
 *            kLinSc_SendNegativeResponse or kLinSc_NoResponse.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   IdNumber The number of the requested identifier
 *   @param   pbIdValue Pointer to write the requested identifier
 *
 *   @return  length  Length of the provided diagnostic response data exclusice response SID.
 *
 *   @context Called by the driver in interrupt context
 *
 *   @pre     No precondition.
 *
 *******************************************************************************************/
extern vuint8 ApplLinScGetUserDefinedId(vuint8 IdNumber, vuint8* pbIdValue);
     #define kLinSc_SendNegativeResponse    ((vuint8) 0x00u)
     #define kLinSc_NoResponse              ((vuint8) 0x06u)
     /* legacy define - use actual response length instead which is depending on SID and protocol version */
     #define kLinSc_SendPositiveResponse    ((vuint8) 0x05u)


    #endif /* LIN_APISTYLE_VECTOR */

   #endif /* LIN_ENABLE_READ_BY_ID_BY_APPL */

   #if defined ( LIN_ENABLE_SAVE_CONFIGURATION_COMMAND )
    #if defined ( LIN_APISTYLE_VECTOR )
/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinScSaveConfiguration                                   */
/*******************************************************************************************/
/**
 *   @brief   (S) Notification callback to inform the application to save the current configuration
 *
 *            A positive response is provided in any case due to successful reception of service.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   none
 *
 *   @return  void
 *
 *   @context The function is called from interrupt level.
 *
 *   @pre     none
 *
 *******************************************************************************************/
extern void ApplLinScSaveConfiguration(void);
    #endif
   #endif

   #if defined ( LIN_ENABLE_DATA_DUMP_BY_APPL )
/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinScDataDump                                            */
/*******************************************************************************************/
/**
 *   @brief   (S) Request Data dump received
 *
 *            The slave configuration has received the service request
 *            Data Dump. The request contains always 5 data bytes, which can be
 *            accessed via pbRequestData. When a response should be provided,
 *            the return value must be set to kLinSc_SendDataDump and the
 *            response of 5 data bytes must be written to pbResponseData
 *            at least before the following slave response frame is received.
 *            When a negative response should be provided, the return value is
 *            kLinSc_NoDataDump.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   pbRequestData  pointer to the received data
 *   @param   pbResponseData pointer to the data to be transmitted
 *
 *   @return  kLinSc_SendDataDump  Service response will be send
 *   @return  kLinSc_NoDataDump    Service not supported will be send
 *
 *   @context Called by the driver in interrupt context
 *
 *   @pre     No precondition.
 *
 *   @note    The service should not be used in an operational cluster. It is
 *            intended for initial configuration by the node supplier
 *
 *******************************************************************************************/
extern vuint8 ApplLinScDataDump(const vuint8* const pbRequestData, vuint8* pbResponseData);
    #define kLinSc_SendDataDump             ((vuint8)0x00u)
    #define kLinSc_NoDataDump               ((vuint8)0x01u)

   #endif /* LIN_ENABLE_DATA_DUMP_BY_APPL */




   #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
    #if defined ( LIN_ENABLE_ASSIGN_NAD_VIA_SNPD_COMMAND )
/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinScAssignNADviaSNPD                                    */
/*******************************************************************************************/
/**
 *   @brief   (S) Request Assign NAD via Slave Node Position Detection (SNPD)
 *
 *            The slave has received the service request indication the SNPD sequence.
 *            The request contains always 6 diagnostic data bytes, which can be
 *            accessed via pbRequestData. An optional response is not send here but has to be
 *            triggert in case the NAD assignment in this node was successful.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   pbRequestData  pointer to the received data
 *
 *   @return  void
 *
 *   @context Called by the driver in interrupt context
 *
 *   @pre     No precondition.
 *
 *
 *******************************************************************************************/
extern void ApplLinScAssignNADviaSNPD(const vuint8* const pbRequestData);
    #endif
   #endif


   #if defined ( LIN_ENABLE_USER_SLAVE_CONFIG )
    #define kLinSc_SendUserSpecConfig        0
    #define kLinSc_WaitForUserSpecConfig     1
    #define kLinSc_NoUserSpecConfig          2
    #define kLinSc_WrongUserSpecConfig       3

    #define kLinSc_ResponseData_ErrorCode    1

/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinScUserSlaveConfig_x                                   */
/*******************************************************************************************/
/**
 *   @brief   (S) User specific diagnostic request received
 *
 *            The slave configuration has received a user specific service request.
 *            The request is configured in the generation tool. The received data can
 *            be accessed via pbRequestData and the length of valid data is *pbDataLength.
 *            When a response should be provided, the return value must be set to
 *            kLinSc_SendUserSpecConfig and the response of up to 5 data bytes must be
 *            written to pbResponseData at least before the following slave response
 *            frame is received (best is to write them in this function). The length
 *            of valid response data is set with *pbDataLength.
 *            When the response is not yet available kLinSc_WaitForUserSpecConfig shall be
 *            returned. Then response can be configured with the function LinScSetRespUserSlaveConfig
 *            later (see description of that function). To configure the response data in
 *            this case, the pbResponseData must be store. The data has to be written to
 *            that pointer before calling LinScSetRespUserSlaveConfig.
 *            When a negative response should be provided, the return value has to be
 *            kLinSc_WrongUserSpecConfig. In this case the error code must be written into
 *            pbResponseData[kLinSc_ResponseData_ErrorCode], before leaving the function.
 *            When no answer shall be send the return value must be kLinSc_NoUserSpecConfig.
 *
 *            In previous versions of this implementation the pointer pbRequestData has been
 *            pointing to the payload data following the SID. This has been changed now to allow
 *            the application to access also the NAD which might be functional where no response is transmitted.
 *            pbRequestData now points to the NAD of the received LIN frame.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   pbDataLength                  pointer to the length received, also write length
 *                                          to be transmitted if return value is kLinSc_SendUserSpecConfig
 *   @param   pbRequestData                 pointer to the received frame starting with the NAD, only the first *pbDataLength + 3
 *                                          (incoming value) bytes should be evaluated
 *   @param   pbResponseData                pointer to the data to be transmitted, only the first *pbDataLength
 *                                          (outgoing value) bytes should be written
 *
 *   @return  kLinSc_SendUserSpecConfig     Service response will be send
 *   @return  kLinSc_WaitForUserSpecConfig  Service response pending, waiting for further data
 *   @return  kLinSc_NoUserSpecConfig       No Service response will be send
 *   @return  kLinSc_WrongUserSpecConfig    Service not supported will be send
 *
 *   @context Called by the driver in interrupt context
 *
 *   @pre     Function must be enabled in generation tool.
 *
 *   @note    The service should not be used in an operational cluster. It is
 *            intended for a small diagnostic implementation based in single frame
 *            diagonstics.
 *
 *******************************************************************************************/
    #if ( kNumberOfUserSlaveConfig > 0 )
extern vuint8 ApplLinScUserSlaveConfig_0(vuint8* pbDataLength, const vuint8* const pbRequestData, vuint8* pbResponseData);
    #endif

    #if ( kNumberOfUserSlaveConfig > 1 )
extern vuint8 ApplLinScUserSlaveConfig_1(vuint8* pbDataLength, const vuint8* const pbRequestData, vuint8* pbResponseData);
    #endif

    #if ( kNumberOfUserSlaveConfig > 2 )
extern vuint8 ApplLinScUserSlaveConfig_2(vuint8* pbDataLength, const vuint8* const pbRequestData, vuint8* pbResponseData);
    #endif

    #if ( kNumberOfUserSlaveConfig > 3 )
extern vuint8 ApplLinScUserSlaveConfig_3(vuint8* pbDataLength, const vuint8* const pbRequestData, vuint8* pbResponseData);
    #endif

    #if ( kNumberOfUserSlaveConfig > 4 )
extern vuint8 ApplLinScUserSlaveConfig_4(vuint8* pbDataLength, const vuint8* const pbRequestData, vuint8* pbResponseData);
    #endif

    #if ( kNumberOfUserSlaveConfig > 5 )
extern vuint8 ApplLinScUserSlaveConfig_5(vuint8* pbDataLength, const vuint8* const pbRequestData, vuint8* pbResponseData);
    #endif

    #if ( kNumberOfUserSlaveConfig > 6 )
extern vuint8 ApplLinScUserSlaveConfig_6(vuint8* pbDataLength, const vuint8* const pbRequestData, vuint8* pbResponseData);
    #endif

    #if ( kNumberOfUserSlaveConfig > 7 )
extern vuint8 ApplLinScUserSlaveConfig_7(vuint8* pbDataLength, const vuint8* const pbRequestData, vuint8* pbResponseData);
    #endif

    #if ( kNumberOfUserSlaveConfig > 8 )
extern vuint8 ApplLinScUserSlaveConfig_8(vuint8* pbDataLength, const vuint8* const pbRequestData, vuint8* pbResponseData);
    #endif

    #if ( kNumberOfUserSlaveConfig > 9 )
extern vuint8 ApplLinScUserSlaveConfig_9(vuint8* pbDataLength, const vuint8* const pbRequestData, vuint8* pbResponseData);
    #endif


/*******************************************************************************************/
/*    API FUNCTION:  LinScSetRespUserSlaveConfig                                           */
/*******************************************************************************************/
/**
 *   @brief   (S) Configures the answer of a pending user specific diagnostic request
 *
 *            The function is called from the application.
 *            With this function the answer to a diagnostic request can be configured if
 *            the return value of function ApplLinScUserSlaveConfig_x was set to
 *            kLinSc_WaitForUserSpecConfig.
 *            If a positive response has to be send bRespType must be kLinSc_SendUserSpecConfig.
 *            The data must be written to the pointer pbResponseData, received in
 *            ApplLinScUserSlaveConfig_x before calling this function.
 *            If a negative response has to be send bRespType must be kLinSc_WrongUserSpecConfig.
 *            The error code must be written to pbResponseData[kLinSc_ResponseData_ErrorCode]
 *            before calling this function.
 *            If no answer shall be send bRespType must be kLinSc_NoUserSpecConfig.
 *            Before data is written to pbResponseData (negative or positive answer) this function
 *            can be called with bRespType beeing kLinSc_WaitForUserSpecConfig. This does not change
 *            the actual status. A positive return value indicates that the response can still be
 *            configured.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   bRespType     Type of answer (positive, negative, no or pending), s. ApplLinScUserSlaveConfig_x
 *   @param   bLength       Only needed if positive answer is selected with bRespType. Defines
 *                          the length of valid data.
 *
 *   @return  0 = accepted, 1 = rejected
 *
 *   @context Function must be called from task context. Calling from interrupt context is not allowed.
 *
 *   @pre     Function ApplLinScUserSlaveConfig_x must have been called before and return value
 *            must have been set to kLinSc_WaitForUserSpecConfig.
 *
 *******************************************************************************************/
extern vuint8 LinScSetRespUserSlaveConfig(vuint8 bUserSlaveConfServiceNr, vuint8 bRespType, vuint8 bLength);

   #endif /* LIN_ENABLE_USER_SLAVE_CONFIG */
  #endif /* LIN_ENABLE_SLAVE_CONFIGURATION */


  #if defined ( LIN_ENABLE_DIAG_FRAMES )
/*******************************************************************************************/
/*    API FUNCTION:  LinSetDiagnosticTxUser                                                */
/*******************************************************************************************/
/**
 *   @brief   (S) Configures the current user (instance) of the SlaveResp frame.
 *
 *            Three different users are sharing the diagnostic communication primitives MasterReq
 *            and SlaveResp: Node Configuration Services, LIN Tp and Diag Layer, Application
 *
 *            This function is intended to be used only in case of bootloaders where a SlaveResp
 *            must be replied in the application without preceding MasterReq (which was already
 *            handled by the bootloader before performing a reset operation and enabling the normal
 *            application). Depending on the implementation the SlaveResp might be answered by the
 *            user Application or by the LIN Tp / Diag Layer. The appropriate parameters
 *            kDdDiagFrmUser_None(Application) or kDdDiagFrmUser_LinTp_S may be used as parameters.
 *
 *            This function should only be called once after reset and initialisation LinInitPowerOn()!
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   bDiagUser     Intended user of the next SlaveResp frame
 *
 *   @return  void
 *
 *   @context Function must be called from task context once after LinInitPowerOn() before enabling interrupts.
 *
 *   @pre     LinInitPowerOn()/l_sys_init() was called before and interrupts are disabled on global level.
 *
 *******************************************************************************************/
extern void LinSetDiagnosticTxUser(vuint8 bDiagUser);
  #endif
  #define kDdDiagFrmUser_None               ((vuint8) 0x00u)
  #define kDdDiagFrmUser_SlaveConfig        ((vuint8) 0x02u)
  #define kDdDiagFrmUser_LinTp_S            ((vuint8) 0x03u)


  #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
/*******************************************************************************************/
/*    API FUNCTION:  LinSetProtocolCompatibility                                           */
/*******************************************************************************************/
/**
 *   @brief   (S) Configures the current protocol version of the slave node
 *
 *            Using the compatibility mode allows a LIN 2.1 slave node to act as a LIN 1.3 or
 *            LIN 2.0 node in some aspects like checksum model or usage of node configuration
 *            services. A full LIN compliance to the 1.3 or 2.0 can not be achieved!
 *
 *            This function should only be called once after reset and before LinInitPowerOn()!
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   bProtocolVersion     Protocol version to be active
 *
 *   @return  void
 *
 *   @context Function must be called from task context before LinInitPowerOn() and before enabling interrupts.
 *
 *   @pre     Interrupts are disabled on global level.
 *
 *******************************************************************************************/
extern void LinSetProtocolCompatibility(vuint8 bProtocolVersion);
   #define kLinProtocolCompatibility_13    ((vuint8) 0x13u)
   #define kLinProtocolCompatibility_20    ((vuint8) 0x20u)
   #define kLinProtocolCompatibility_21    ((vuint8) 0x21u)
   #define kLinProtocolCompatibility_22    ((vuint8) 0x22u)
   #define kLinProtocolCompatibility_J2602 ((vuint8) 0xF6u)
  #endif

  #if defined ( LIN_ENABLE_RESP_ERR_BIT_CONFIG )
/*******************************************************************************************/
/*    API FUNCTION:  LinSetResponseErrorBit                                                */
/*******************************************************************************************/
/**
 *   @brief   (S) Configures the response_error bit of the slave node
 *
 *            Using this API the response_error signal can be defined during initialization
 *            after power on reset. By default the response_error bit is set based on the LDF
 *            and this API is not necessary.
 *
 *            This function should only be called once after reset and after LinInitPowerOn()!
 *
 *            Incorrect configuration will avoid conformance test to be passed and may disturb a signal value!
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   vMsgHandle           The handle of the tx message containing the response_error signal
 *   @param   bByte                Byte containing the response_error signal [0-7]
 *   @param   bBitMask             Bit mask where the response_error signal is mapped to [0x01u to 0x80u]
 *
 *   @return  void
 *
 *   @context Function must be called from task context after LinInitPowerOn() and before enabling interrupts.
 *
 *   @pre     Interrupts are disabled on global level.
 *
 *******************************************************************************************/
extern void LinSetResponseErrorBit(tLinFrameHandleType vMsgHandle, vuint8 bByte, vuint8 bBitMask);
  #endif

   #if defined ( LIN_ENABLE_STATUSBIT_SIGNAL )
    #if defined ( LIN_ENABLE_STATUSBIT_SIGNAL_CHECK )
/*******************************************************************************************/
/*    API FUNCTION:  LinCheckResponseErrorBit                                              */
/*******************************************************************************************/
/**
 *   @brief   (S) Check if the response_error bit is currently set/pending
 *
 *            It is up the the LIN driver to set and clear the response_error bit.
 *            This function allows to check if the driver has currently set the bit for
 *            transmission in the next frame. This function is intended to be used in context
 *            of ApplLinProtocolError() to check if the error has forced that the response_error
 *            bit has been set.
 *            In case of J2602 the 3-bit error field is reported in the lower nibble of the
 *            response byte.
 *            The LIN driver will clear the response_error bit as soon as the bit has been
 *            transmitted successfully.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *
 *   @return  value of response_error bit
 *
 *   @context Function must be called from task context in context of ApplLinProtocolError or from
 *            task level.
 *
 *   @pre     Driver is initialized and ApplLinProtocolError is called.
 *
 *******************************************************************************************/
extern vuint8 LinCheckResponseErrorBit(void);
    #endif
   #endif

 #endif /* LIN_ECUTYPE_SLAVE */

 #if defined ( LIN_APISTYLE_VECTOR )
/*******************************************************************************************/
/*       VECTOR API (COVERS THE LIN API)                                                   */
/*******************************************************************************************/

  #if defined ( LIN_ENABLE_LINSTART_WAKEUP_INTERNAL ) || defined ( LIN_ENABLE_LINSTART_WAKEUP_EXTERNAL )

/*******************************************************************************************/
/*    API FUNCTION:  LinStart                                                              */
/*******************************************************************************************/
/**
 *   @brief   (M,S) Requests the start of bus communication
 *
 *            The call of LinStart transmits a wakeup frame, observes the activity
 *            on the bus and informs the application about the wakeup.
 *            For the master node, the schedule table handling is started as soon
 *            as a valid schedule table has been set.
 *            Parameter kLinWakeUpExternal assumes that an external wakeup has been
 *            detected by the application (e.g power on or ext. interrupt))
 *
 *   @param_i linchannel The interface/channel the communication is requested for
 *   @param   bWakeUpReason Internal or external wakeup reason. For external wakeup
 *            reason, no wakeup frame is transmitted
 *
 *   @return  0 = accepted, 1 = rejected
 *
 *   @context Function must be called from task context. Calling from interrupt context is not allowed.
 *
 *   @pre     Driver is initialized and in sleep mode.
 *
 *******************************************************************************************/
/* CODE CATEGORY 3 START*/
  extern vuint8 LinStart (vuint8 bWakeUpReason);
/* CODE CATEGORY 3 END*/

  /* Valid values for bWakeUpReason */
   #define kLinWakeUpInternal         ((vuint8) 0x01u)     /**< Start communication after internal wup reason */
   #define kLinWakeUpExternal         ((vuint8) 0x02u)     /**< Start communication after external wup reason */

  #endif /* LIN_ENABLE_LINSTART_WAKEUP_INTERNAL || LIN_ENABLE_LINSTART_WAKEUP_EXTERNAL */

  #if defined ( LIN_ENABLE_T_BUS_IDLE_MODE )
/*******************************************************************************************/
/*    API FUNCTION:  LinSetBusIdleTimerMode                                                */
/*******************************************************************************************/
/**
 *   @brief   Activate/inactivate bus idle timer observation
 *
 *            Using this API allows to activate or deactivate bus idle timeout observation.
 *            The mode is defined by the application after LIN initialization. By default
 *            the timeout observation is activated.
 *
 *            This function should only be called once after reset and after LinInitPowerOn()!
 *
 *            If the timeout observation is disabled the slave node will not go to sleep mode by its own
 *            if no sleep mode frame is transmitted by the LIN master. Transmitting a wake up frame
 *            is only possible in sleep mode.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   bMode      Provides the active/inactive mode of bus idle timeout observation
 *
 *   @return  void
 *
 *   @context Function must be called from task context after LinInitPowerOn() and before enabling interrupts.
 *
 *   @pre     Bus idle timeout observation is enabled.
 *
 *******************************************************************************************/
/* CODE CATEGORY 2 START*/
extern void LinSetBusIdleTimerMode(vuint8 bMode);
/* CODE CATEGORY 2 END*/
   #define kLinBusIdleInactive       ((vuint8) 0x00u)
   #define kLinBusIdleActive         ((vuint8) 0x01u)
  #endif

/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinWakeUp                                                */
/*******************************************************************************************/
/**
 *   @brief   (M,S) Notification of a transition to wakeup after reception or transmission
 *            of a wakeup frame
 *
 *   @param_i linchannel The interface/channel which is requested
 *   @param   void none
 *
 *   @return  void none
 *
 *   @context Function is called by the driver in task context.
 *
 *   @pre     No precondition.
 *
 *******************************************************************************************/
/* CODE CATEGORY 1 START*/
extern void ApplLinWakeUp(void);
/* CODE CATEGORY 1 END*/

/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinBusSleep                                              */
/*******************************************************************************************/
/**
 *   @brief   (M,S) Notification of a transition to sleep mode
 *
 *            The transition to sleep mode is performed after the transmission
 *            or reception of a sleep mode frame or after a bus idle timeout
 *
 *   @param_i linchannel The interface/channel which is requested
 *   @param   void none
 *
 *   @return  void none
 *
 *   @context Function is called by the driver in task context.
 *
 *   @pre     No precondition.
 *
 *******************************************************************************************/
/* CODE CATEGORY 2 START*/
extern void ApplLinBusSleep(void);
/* CODE CATEGORY 2 END*/



  #if defined ( LIN_ECUTYPE_SLAVE )
   #if defined ( LIN_ENABLE_CONFIGURABLE_PID )
    #if defined ( LIN_ENABLE_CONFIGURATION_API )
/*******************************************************************************************/
/*    API FUNCTION:  LinReadConfiguration                                                 */
/*******************************************************************************************/
/**
 *   @brief   (S) This service copies the current configuration of PIDs in the slave to a
 *            application area.
 *
 *            The call of this API will check the provided parameter length to decide if the
 *            provided data area is appropriate in size and copies in case the configuration
 *            to this buffer. The return value of this function can be LD_READ_OK or
 *            LD_LENGTH_TOO_SHORT if the buffer does not fit. The order of information inside
 *            the data structure is NAD followed by PIDs in order listed in the corresponding
 *            LDF/NCF.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   pldata pointer to application data area
 *   @param   length length of provided data area
 *
 *
 *   @return  LD_READ_OK If the service was successful
 *   @return  LD_LENGTH_TOO_SHORT If configuration size is greater than length (no valid configuration).
 *
 *   @context Function must be called from task context. Calling from interrupt context is not allowed.
 *
 *   @pre     Driver is initialized.
 *
 *******************************************************************************************/
extern vuint8 LinReadConfiguration(vuint8* const pldata, vuint8* const length);
     #define LD_READ_OK             ((vuint8) 0x00u)
     #define LD_LENGTH_TOO_SHORT    ((vuint8) 0x01u)

/*******************************************************************************************/
/*    API FUNCTION:  LinSetConfiguration                                                 */
/*******************************************************************************************/
/**
 *   @brief   (S) This services initializes a configuration in the LIN driver given by the application
 *
 *            The function will configure the NAD and the PIDs according to the configuration
 *            given by data. The intended usage is to restore a saved configuration
 *            or set an initial configuration (e.g. coded by I/O pins).
 *            The caller shall set the size of the data area before calling the function.
 *            The data contains the NAD and the PIDs and occupies one byte each. The structure
 *            of the data is: NAD and then all PIDs for the frames. The order of the PIDs are the
 *            same as the frame list in the LDF/NCF.
 *
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   pldata pointer to application data area
 *   @param   length length of provided data area
 *
 *   @return  LD_SET_OK If the service was successful
 *   @return  LD_LENGTH_NOT_CORRECT required size is not equal to the given size
 *   @return  LD_DATA_ERROR The set of configuration could not be made.
 *
 *   @context Function must be called from task context. Calling from interrupt context is not allowed.
 *
 *   @pre     This function should be called after l_ifc_init.
 *
 *******************************************************************************************/
extern vuint8 LinSetConfiguration(const vuint8* const pldata, vuint8 length);
     #define LD_SET_OK              ((vuint8) 0x00u)
     #define LD_LENGTH_NOT_CORRECT  ((vuint8) 0x01u)
     #define LD_DATA_ERROR          ((vuint8) 0x02u)
    #endif /* LIN_ENABLE_CONFIGURATION_API */
   #endif /* LIN_ENABLE_CONFIGURABLE_PID */
  #endif /* LIN_ECUTYPE_SLAVE */
 #else /* LIN_APISTYLE_LIN */
/*******************************************************************************************/

/*******************************************************************************************/
/*       LIN API (CORRESPONDING TO LIN SPEC)                                               */
/*******************************************************************************************/

  #if !defined ( __LIN_DATA_TYPES__ )
   #define __LIN_DATA_TYPES__
  /* Mapping of the data types of the LIN API to the internal used types  */
  typedef vuint8              l_bool;
  typedef vuint8              l_u8;
  typedef vuint16             l_u16;
  typedef vuint8              l_ifc_handle;
  typedef vuint8              l_schedule_handle;
  #endif

/* The mapping of the static implementation prototypes corresponding to the format         */
/* function_iii() is done in lin_par.h                                                     */

  #if ( LIN_PROTOCOLVERSION_VALUE <= 0x20u )
/*******************************************************************************************/
/*    API FUNCTION:  l_ifc_connect                                                         */
/*******************************************************************************************/
/**
 *   @brief   (M,S) The call to the l_ifc_connect will connect the interface iii to the
 *            LIN cluster and enable the transmission of headers and data to the bus.
 *
 *   @param_i iii The interface/channel which is requested
 *
 *   @return  Zero, if the connect operation was successful and
 *            non-zero if the connect operation failed
 *
 *   @pre     Function must be called from task context. Calling from interrupt context is not allowed.
 *
 *   @note    The call is always accepted
 *
 *******************************************************************************************/
/* CODE CATEGORY 4 START*/
extern l_bool l_ifc_connect(void);
/* CODE CATEGORY 4 END*/
/*******************************************************************************************/
/*    API FUNCTION:  l_ifc_disconnect                                                      */
/*******************************************************************************************/
/**
 *   @brief   (M,S) The call to the l_ifc_disconnect will disconnect the interface iii
 *            from the LIN cluster and thus disable the interaction with the other nodes in the cluster.
 *
 *   @param_i iii The interface/channel which is requested
 *
 *   @return  Zero, if the disconnect operation was successful and
 *            non-zero if the connect operation failed
 *
 *   @pre     Function must be called from task context. Calling from interrupt context is not allowed.
 *
 *   @note    The call is always accepted
 *
 *******************************************************************************************/
/* CODE CATEGORY 4 START*/
extern l_bool l_ifc_disconnect(void);
/* CODE CATEGORY 4 END*/
  #endif /* LIN_PROTOCOLVERSION_VALUE <= 0x20u */

/*******************************************************************************************/
/*    API FUNCTION:  LinSetOperationalMode                                                 */
/*******************************************************************************************/
/**
 *   @brief   (M,S) The call to LinSetOperationalMode sets the frame processor in the
 *            operational state
 *
 *            In the operational state, only synch break fields are expected.
 *            All received bytes are ignored. To be able to receive a wakeup frame
 *            after a bus idle timeout, the frame processor must be set to stand-by
 *            by the application
 *
 *   @param_i iii The interface/channel which is requested
 *
 *   @return  void none
 *
 *   @pre     Function must be called from task context. Calling from interrupt context is not allowed.
 *
 *   @note    The API function is not part of the LIN specification, but required for
 *            the operation.
 *
 *******************************************************************************************/
/* CODE CATEGORY 4 START*/
extern void LinSetOperationalMode(void);
/* CODE CATEGORY 4 END*/
/*******************************************************************************************/
/*    API FUNCTION:  LinSetStandByMode                                                     */
/*******************************************************************************************/
/**
 *   @brief   (M,S) The call to LinSetStandByMode sets the frame processor in the
 *            stand-by state
 *
 *            In the stand-by state a wakeup signal is expected. When a wakeup signal
 *            is detected by the transceiver (e.g. power up or external IRQ), the
 *            state stand-by has been left. In this case, LinSetOperationalMode
 *            must be called.
 *
 *   @param_i iii The interface/channel which is requested
 *
 *   @return  void none
 *
 *   @pre     Function must be called from task context. Calling from interrupt context is not allowed.
 *
 *   @note    The API function is not part of the LIN specification, but required for
 *            the operation.
 *
 *******************************************************************************************/
/* CODE CATEGORY 4 START*/
extern void LinSetStandByMode(void);
/* CODE CATEGORY 4 END*/



/*******************************************************************************************/
/*    API FUNCTION:  l_ifc_wake_up                                                         */
/*******************************************************************************************/
/**
 *   @brief   (M,S) Transmits a wakeup signal via interface iii
 *
 *   @param_i iii The interface/channel which must transmit the wakeup request
 *   @param   void none
 *
 *   @return  void none
 *
 *   @pre     Bus must be in mode sleep
 *
 *   @note    The request is confirmed with ApplLinWakeupRequest
 *
 *******************************************************************************************/
/* CODE CATEGORY 3 START*/
extern void l_ifc_wake_up(void);
/* CODE CATEGORY 3 END*/

/*******************************************************************************************/
/*    API CALLBACK FUNCTION:  ApplLinWakeupRequest                                         */
/*******************************************************************************************/
/**
 *   @brief   (M,S) Indication of a detected wake-up request on the bus
 *
 *            Callback function is called after the reception of any bus activity by the LIN
 *            hardware e.g. UART when the bus is in sleep mode.
 *
 *   @param_i iii The interface/channel which received the wakeup request
 *   @param   void none
 *
 *   @return  void none
 *
 *   @pre     No precondition. Function is called from UART interrupt level.
 *
 *   @note    An API function for the indication of a wakeup request is not defined.
 *
 *******************************************************************************************/
/* CODE CATEGORY 1 START*/
extern void ApplLinWakeupRequest(void);
/* CODE CATEGORY 1 END*/

/*******************************************************************************************/
/*    API FUNCTION:  l_ifc_read_status                                                     */
/*******************************************************************************************/
/**
 *   @brief   (M,S) The call returns a 16 bit status value of interface iii
 *
 *   @param_i iii The interface/channel which must send the sleep command
 *   @param   void none
 *
 *   @return  Status word     Bit0     Error in response
 *                            Bit1     Successful transfer
 *                            Bit2     Overrun
 *                            Bit3     Goto sleep
 *                            Bit8..15 Last frame protected Id
 *
 *   @context Function must be called from task context. Calling from interrupt context is not allowed.
 *
 *   @pre     No precondition.
 *
 *******************************************************************************************/
/* CODE CATEGORY 2 START*/
extern l_u16 l_ifc_read_status(void);
/* CODE CATEGORY 2 END*/

 /* Bit masks of flags of low byte */
  #define kLinStatus_ResponseError    ((vuint8) 0x01u)
  #define kLinStatus_RxTxSuccess      ((vuint8) 0x02u)
  #define kLinStatus_Overrun          ((vuint8) 0x04u)
  #define kLinStatus_GotoSleep        ((vuint8) 0x08u)
  #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u ) 
   #define kLinStatus_BusActivity     ((vuint8) 0x10u)
  #endif
  #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
   #if defined ( LIN_ECUTYPE_SLAVE )
    #define kLinStatus_SaveConfig      ((vuint8) 0x40u)
   #endif
  #endif

  #if defined ( LIN_ECUTYPE_SLAVE )
   #if defined ( LIN_ENABLE_SLAVE_CONFIGURATION )
    #if defined ( LIN_ENABLE_READ_BY_ID_BY_APPL )

/*******************************************************************************************/
/*    API CALLOUT:  ld_read_by_id_callout                                                  */
/*******************************************************************************************/
/**
 *   @brief   (S) Configures response for read_by_identifier request with user-defined identifier
 *
 *   @param   iii      Handle of the requested interface.
 *   @param   id       Identifier corresponding to the mapping used with "read_by_Identifier"
 *   @param   pldata   Pointer to five byte data buffer used for response.
 *
 *   @return  l_u8     Indication if response (positive or negative) should be provided
 *
 *   @context The function must be called from task level.
 *
 *   @pre     Availability of the API must be checked by a previous call of
 *            ld_is_ready()
 *
 *******************************************************************************************/
  extern l_u8 ld_read_by_id_callout (l_ifc_handle iii, l_u8 id, l_u8* pldata);

    /* return values of ld_read_by_id_callout */
    /* values are set as they are to be compatible with return value definition of ApplLinScGetUserDefinedId() */
     #define LD_NEGATIVE_RESPONSE     ((vuint8) 0x00u)
     #define LD_POSITIVE_RESPONSE     ((vuint8) 0x05u)
     #define LD_NO_RESPONSE           ((vuint8) 0x06u)

    #endif
   #endif

   #if defined ( LIN_ENABLE_CONFIGURABLE_PID )
    #if defined ( LIN_ENABLE_CONFIGURATION_API )
/*******************************************************************************************/
/*    API FUNCTION:  ld_read_configuration                                                 */
/*******************************************************************************************/
/**
 *   @brief   (S) This service copies the current configuration of PIDs in the slave to a
 *            application area.
 *
 *            The call of this API will check the provided parameter length to decide if the
 *            provided data area is appropriate in size and copies in case the configuration
 *            to this buffer. The return value of this function can be LD_READ_OK or
 *            LD_LENGTH_TOO_SHORT if the buffer does not fit. The order of information inside
 *            the data structure is NAD followed by PIDs in order listed in the corresponding
 *            LDF/NCF.
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   pldata pointer to application data area
 *   @param   length length of provided data area
 *
 *   @return  LD_READ_OK If the service was successful
 *   @return  LD_LENGTH_TOO_SHORT If configuration size is greater than length (no valid configuration).
 *
 *   @context Function must be called from task context. Calling from interrupt context is not allowed.
 *
 *   @pre     Driver is initialized.
 *
 *******************************************************************************************/
extern l_u8 ld_read_configuration(l_u8* const pldata, l_u8* const length);
     #define LD_READ_OK             ((vuint8) 0x00u)
     #define LD_LENGTH_TOO_SHORT    ((vuint8) 0x01u)

/*******************************************************************************************/
/*    API FUNCTION:  ld_set_configuration                                                 */
/*******************************************************************************************/
/**
 *   @brief   (S) This services initializes a configuration in the LIN driver given by the application
 *
 *            The function will configure the NAD and the PIDs according to the configuration
 *            given by data. The intended usage is to restore a saved configuration
 *            or set an initial configuration (e.g. coded by I/O pins).
 *            The caller shall set the size of the data area before calling the function.
 *            The data contains the NAD and the PIDs and occupies one byte each. The structure
 *            of the data is: NAD and then all PIDs for the frames. The order of the PIDs are the
 *            same as the frame list in the LDF/NCF.
 *
 *
 *   @param_i linchannel The interface/channel the call is relevant for
 *   @param   pldata pointer to application data area
 *   @param   length length of provided data area
 *
 *
 *   @return  LD_SET_OK If the service was successful
 *   @return  LD_LENGTH_NOT_CORRECT required size is not equal to the given size
 *   @return  LD_DATA_ERROR The set of configuration could not be made.
 *
 *   @context Function must be called from task context. Calling from interrupt context is not allowed.
 *
 *   @pre     This function should be called after l_ifc_init.
 *
 *******************************************************************************************/
extern l_u8 ld_set_configuration (const l_u8* const pldata, l_u8 length);
     #define LD_SET_OK              ((vuint8) 0x00u)
     #define LD_LENGTH_NOT_CORRECT  ((vuint8) 0x01u)
     #define LD_DATA_ERROR          ((vuint8) 0x02u)
    #endif /* LIN_ENABLE_CONFIGURATION_API */
   #endif /* LIN_ENABLE_CONFIGURABLE_PID */
  #endif /* LIN_ECUTYPE_SLAVE */

 #endif /* LIN_APISTYLE_LIN */

#endif /* end of lin_drv.h */


