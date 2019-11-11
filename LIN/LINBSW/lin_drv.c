/* PRQA S 0715 EOF *//* MD_LIN_DRV_1.1 */
/* PRQA S 0288 EOF *//* MD_LIN_DRV_3.1 */
/* PRQA S 3109 EOF *//* MD_CBD_14.3 */
/* PRQA S 3412 EOF *//* MD_CBD_19.4 */
/* PRQA S 3458 EOF *//* MD_CBD_19.4 */
/* PRQA S 3460 EOF *//* MD_CBD_19.4 */
/* PRQA S 3453 EOF *//* MD_CBD_19.7 */
/*******************************************************************************************/
/** @file    lin_drv.c
*   @brief   Implementation of the LIN protocol driver kernel
*
*            This file contains the Vector LIN driver implementation 2.x which supports a
*            LIN driver corresponding to LIN specification 1.2, 1.3, 2.0, 2.1 or 2.2
*
********************************************************************************************/

/*******************************************************************************************/
/** @page     lin_drv_c_header Header information of lin_drv.c
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
*   @par      Revision History
*   @verbatim
*   Date        Ver     Author Description
*   2004-04-16  2.0     Wr     Rework of the implementation for LIN 2.0 support
*   2004-07-17  2.1     Wr     Added Slave Functionality
*                              Added callback API function for Sleep wakeup control
*                              ESCAN00009018: Delay index of LinScheduleTask
*   2004-08-28  2.2     Wr     ESCAN00009395: Added buffer protection
*                              Adapted dignostic dispatcher for DTL Master
*                              ESCAN00009394: Sleep mode frame data from lin_par.c
*   2004-09-08  2.3     Wr     ESCAN00009714: Cast for sleep mode frame pointer assignment
*                              ESCAN00009416: Call to Frame processor timeout timer
*                              ESCAN00009715: Initialize bus idle timer
*                              ESCAN00009716: Trigger of bus idle timer in Fp Error
*                              ESCAN00009717: Stop schedule table handling after no wakeup conf or after bus idle
*                              ESCAN00009719: One common state for Wakeup frame notification
*                              ESCAN00009720: Increment tx index after requesting wakeup handling
*                              ESCAN00009721: Remove duplicated if condition in ApplFpHeaderIndication.
*                              ESCAN00009722: Optimization for Single frame detection
*                              ESCAN00009723: Return value of ApplLinDtlPrecopyFct
*                              ESCAN00009707: Macro for bFpConnectionState
*   2004-11-04  2.4     Wr     ESCAN00010115: Add support for SIO_LL_APITYPE_SBF_IND
*                              ESCAN00010001: MasterReq frame and SlaveResp header is always send if Diag Frames by Application is deactivated
*                              ESCAN00010020: Handling of undefined error StatusBit in LDF or NCF file
*                              ESCAN00010418: Add 'Init PID from LDF'
*   2004-12-01  2.5     Svh    ESCAN00010414: Add Runtime Measurement
*                       Wr     ESCAN00010457: No Confirmation Handling of SlaveResponse Frame is done
*   2004-12-08  2.6     Svh    ESCAN00010515: SlaveResp Response to a MasterReq may be transmitted after a following MasterReq
*   2004-12-29  2.7     Wr     ESCAN00010674: Mute mode after frame response is not set
*                              ESCAN00010724: Header notification callback function
*                              ESCAN00010750: Modified handling of ApplSioErrorNotification()
*                              ESCAN00010751: Reset mute mode after no wakeup timeout for SCI LIN
*   2005-01-17  2.8     Svh    ESCAN00010764: Collision in Event Triggered Frame is reported as Error to the application
*                              ESCAN00010771: Response_Error (which is transmitted to LIN master) is not set and reset correctly
*                              ESCAN00010816: Rework of Error Handling concerning Collision and Bus Disturbance during Response Handling
*                              ESCAN00010817: Error during Response might not have been reported to the Application
*                       Wr     ESCAN00010814: Ignore SetScheduleTable() when stop request is pending
*                              ESCAN00010824: Parameters of frame processor callback functions are wrong
*   2005-02-03  2.9     Svh    ESCAN00010937: Add user defined single frame diagnostic services
*                              ESCAN00010992: Optimization of Code Size and Runtine
*   2005-04-26  2.10    Svh    ESCAN00011175: Compiler Flags an Error due to an Assignment Mismatch
*                       Wr     ESCAN00011579: Add multi channel to LIN Driver
*                              ESCAN00011592: Corresponding unconditional frame to an event triggered may not be found
*                              ESCAN00011593: LIN Master sends an header after receiving bus traffic that is detected as a synch break
*                              ESCAN00011573: Driver Sends Incorrect Data in Slave Command and Go-to-sleep-command Frames
*                              ESCAN00012042: Error notification for bus idle detection always active
*   2005-05-17  2.11    Svh    ESCAN00012279: Bus Idle observation is not working correctly if controller has message api
*   2005-06-10  2.12    Svh    ESCAN00012491: Add new options to LIN driver
*   2005-07-06  2.13    Svh    ESCAN00012697: Support of no unconditional rx or tx frames
*                              ESCAN00012696: Wrong message handle might be given in ApplLinProtocolError
*   2005-09-09  2.14    Svh    ESCAN00013457: Add CANoeEmu specific code
*                              ESCAN00013484: Further reduction of runtime
*   2005-10-25  2.15    Svh    ESCAN00013687: Add multi channel interface between LIN driver and DTL
*                              ESCAN00013694: Reduce code size by using one function for different configuration API functions
*                              ESCAN00013879: Reception handling of an Event Triggered Frame with unknown Protected Id in first byte of response is not correct
*                              ESCAN00014023: Extend LIN driver dll check to test frame work 1.04 or frame work 1.03 dll version
*                              ESCAN00014053: Remove return value of function ApplLinDtlRxError()
*   2005-11-09  2.16    Svh    ESCAN00014232: After reception of a segmented diagnostic request the node configuration is not working
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
*   2007-01-16  2.33    Ap     ESCAN00018839: LIN 2.1 support: Master
*                                             * NotificationTask handling now replaced by LinScheduleTask()
*                                             * AssignIDRange command
*                                             * Return value of ld_is_ready (LIN API)
*                                             * EventTriggeredFrame collision resolution handling
*                                             * Messages are copied to send buffer when the frame header is transmitted
*                                             * Frames are copied to frame buffer on schedule task after succ. reception
*                                             * Return type of l_ifc_init adapted
*                                             * Status word of l_ifc_read_status extended by Event triggered frame collision and Bus activity bit
*                                             * ld_handle_all_config()/LinCfg_handle_all_config() redesign
*                                             * ld_read_by_id_callout() added for serial number and user defined ID in read by ID service
*                                             LIN 2.1 support: Slave
*                                             * NotificationTask handling now performed in IRQ context
*                                             * Support for assign frame ID range command
*                                             * New API functions ld_read_configuration and ld_set_configuration
*                                             * Services SaveConfiguration 0xB6 and AssignFrameIdRange 0xB7 supported
*                                             * AssignFrameId service 0xB1 obsolete for LIN 2.1 slaves
*                                             * Read by identifier valid ID range adapted to new specification
*                                             * Status reporting extended by bus activity and save configuration bit
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
*   @endverbatim
********************************************************************************************/

/* Include headers of sio driver, configuration and own header. */

#include "lin_inc.h"


/*******************************************************************************************
* Version Check
********************************************************************************************/
#if ( DRVLIN__CORE_VERSION != 0x0283u )
 #error "LIN_DRV.C and LIN_DRV.H used in different versions, please check driver version!"
#endif

#if ( DRVLIN__CORE_RELEASE_VERSION != 0x02u )
 #error "LIN_DRV.C and LIN_DRV.H used in different versions, please check release version!"
#endif

#if ( LIN_DRIVER_OS_VERSION != 0x0205u )
 #error "LIN_DRV_OS.H used in a wrong version, please check header version!"
#endif

#if ( LIN_DRIVER_OS_RELEASE_VERSION != 0x00u )
 #error "LIN_DRV_OS.H used in a wrong version, please check header release version!"
#endif

#if defined ( LIN_ENABLE_DIAG_TRANSP_LAYER )
 #if ( LIN_DRIVER_TP_VERSION != 0x0208u )
  #error "LIN_DRV_TP.H used in a wrong version, please check header version!"
 #endif

 #if ( LIN_DRIVER_TP_RELEASE_VERSION != 0x00u )
  #error "LIN_DRV_TP.H used in a wrong version, please check header release version!"
 #endif
#endif

 #if ( DRIVER_LINDLL_VERSION >= 0x0200u )
  #if ( DRIVER_LINDLL_VERSION < 0x0212u )
   #error "LIN Driver DLL is not working with this version of LIN Driver. Please use newer LIN Driver DLL Version!"
  #endif
 #else
  #if ( DRIVER_LINDLL_VERSION < 0x0105u )
   #error "LIN Driver DLL is not working with this version of LIN Driver. Please use newer LIN Driver DLL Version!"
  #endif
 #endif

/*******************************************************************************************/
/* Global constants with LIN driver main and subversion                                    */
/*******************************************************************************************/
/* ROM CATEGORY 4 START*/
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kLinDrvMainVersion    = (vuint8)( (DRVLIN__CORE_VERSION & 0xFF00u) >> 8);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kLinDrvSubVersion     = (vuint8)( (DRVLIN__CORE_VERSION & 0x00FFu) );
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kLinDrvReleaseVersion = (vuint8)(  DRVLIN__CORE_RELEASE_VERSION  );
/* ROM CATEGORY 4 END*/

/*******************************************************************************************/
/** Configuration Check                                                                    */
/*******************************************************************************************/

/* checks for valid static configuration of SIO driver *************************************/
 #if !defined ( SIO_LL_APISTYLE_MESSAGE )
  #error "LIN driver can only be used with SIO driver supporting Message API. Check sio_cfg.h. "
 #endif

 #if ( (kLinLowRxMsg != kMessageDirectionRx) || \
       (kLinLowTxMsg != kMessageDirectionTx) ||  \
       (kLinLowNoMsg != kMessageDirectionIgnore) )
  #error "Different message direction coding in lin drv and sio drv. Check sio_drv.h. "
 #endif

 #if ( (kLinLowCsClassic != kChecksumClassic) || \
       (kLinLowCsEnhanced != kChecksumEnhanced) )
  #error "Different message direction coding in lin drv and sio drv. Check sio_drv.h. "
 #endif


#if defined ( LIN_ECUTYPE_SLAVE )
 #if defined ( SIO_ENABLE_BAUDRATE_DETECT )
  #if ! defined ( SIO_LL_ENABLE_BAUDRATE_INFORMATION )
   #if defined ( LIN_ENABLE_T_HEADER_MAX ) || defined ( LIN_ENABLE_T_FRAME_MAX )
    #error "Timeout observation of message must be disabled when using baudrate detection. Check lin_cfg.h."
   #endif
  #endif
 #endif
 #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
  #if defined ( LIN_ENABLE_ET_TX_FRAMES ) || defined ( LIN_ENABLE_ET_RX_FRAMES )
   #error "Event triggered frames are not supported for multiple ecu."
  #endif
  #if defined ( LIN_ENABLE_READ_BY_ID_MESSAGE_IDS )
   #error "Multiple ecu not supported together with read by message ids."
  #endif
 #else
  #if defined ( LIN_ENABLE_STATUSBIT_SIGNAL )
    #if !( defined (kLinStatusBitFrameHandle) && defined (kLinStatusBitOffset) && defined (kLinStatusBitMask))
     #error "Status bit signal (response_error) not defined. Check ldf/ncf file and lin_par_i.h."
    #endif
  #endif
 #endif
 #if defined ( SIO_LL_APISTYLE_MESSAGE )
  #if defined ( SIO_LL_APITYPE_HEADER_IND )
   #if defined ( LIN_ENABLE_T_HEADER_MAX )
    #error "Header timeout observation not possible in software for slave nodes when using a header indication interface."
   #endif
  #endif
 #endif
#endif

#if defined ( LIN_ENABLE_T_BUS_IDLE_MODE )
 #if defined ( LIN_ENABLE_T_BUS_IDLE ) || defined ( SIO_LL_ENABLE_T_BUS_IDLE_BY_HARDWARE )
  #if defined ( SIO_LL_ENABLE_T_BUS_IDLE_MODE )
  #else
   #error "The bus idle timeout mode interface has to be supported by the SIO driver to use this API."
  #endif
 #else
  #error "Bus idle timeout observation in driver or hardware has to be enabled if the mode API is requested."
 #endif
#endif

 #if defined ( LIN_ENABLE_ET_RX_FRAMES ) && defined ( LIN_ECUTYPE_SLAVE )
  #error "Event triggered frames are only subscribed by the master node."
 #endif


#if defined ( LIN_ENABLE_BAUDRATE_INFORMATION )
 #if ! defined ( LIN_ECUTYPE_SLAVE )
  #error "Baudrate Information only applicable for LIN Slaves!"
 #endif
 #if ! defined ( SIO_LL_ENABLE_BAUDRATE_INFORMATION )
  #error "Baudrate Information only applicable if supported by SIO Driver!"
 #endif
 #if ! defined ( SIO_ENABLE_BAUDRATE_DETECT )
  #error "Baudrate Information only applicable if baudrate detection is enabled in SIO Driver!"
 #endif
#endif

#if defined ( LIN_ENABLE_SLEEP_COMMAND_REPETITION )
 #if ! defined ( LIN_ECUTYPE_SLAVE )
  #error "Sleep mode frame repetition only supported in slave node."
 #endif
#endif

#if defined ( LIN_ECUTYPE_SLAVE )
#endif
/*******************************************************************************************/
/*******************************************************************************************/
/*        Handling of systems with single channel and multiple channel interface
 *
 *        To reduce the number of conditional code and to increase the readability of the
 *        code, most variable access is implemented as get, set, increment and decrement
 *        function macro. Function calls to internal or external APIs are implemented with a
 *        configurable channel parameter or type.
 *******************************************************************************************/
/*******************************************************************************************/

 /* Channel parameters or types for internal function declarations or calls */
 #define LIN_I_CHANNEL_PARA_FIRST
 #define LIN_I_CHANNEL_PARA_ONLY
 #define LIN_I_CHANNEL_TYPE_FIRST
 #define LIN_I_CHANNEL_TYPE_ONLY            void


 #if defined ( LIN_ECUTYPE_SLAVE )
  #define LIN_I_SL_CHANNEL_PARA_FIRST
  #define LIN_I_CA_SL_CHANNEL_PARA_ONLY     0
 #endif

 #define linchannel                         0

#if defined ( LIN_APISTYLE_LIN )
/* Last protected ID is passed as parameter to the message handler */
 #define LIN_I_PROTECTED_ID_TYPE            vuint8 bProtectedId,
 #define LIN_I_PROTECTED_ID_PARA            getbFpCurrentProtectedId(linchannel),
#else
 #define LIN_I_PROTECTED_ID_TYPE
 #define LIN_I_PROTECTED_ID_PARA
#endif

/*******************************************************************************************/
/*******************************************************************************************/
/**  memory qualifier defines for mapping variables to FastRAM or NormalRAM               **/
/*******************************************************************************************/
/*******************************************************************************************/

#if defined ( LIN_ENABLE_FASTRAM_VARIABLES )

 /* Map switchable variables to near memory */
 #define LIN_V_MEMRAM1    V_MEMRAM1_NEAR
 #define LIN_V_MEMRAM2    V_MEMRAM2_NEAR

#else

 /* Map switchable variables to normal memory */
 #define LIN_V_MEMRAM1    V_MEMRAM1
 #define LIN_V_MEMRAM2    V_MEMRAM2

#endif


/*******************************************************************************************/
/*******************************************************************************************/
/**  Variables, Functions and defines used by the Error handling                          **/
/*******************************************************************************************/
/*******************************************************************************************/

#if defined ( LIN_ENABLE_DEBUG )
 /* For development reasons it is possible to enable the internal debug                    */
 /* mechanism of SIO / LIN driver and handle all fatal errors by a user                    */
 /* defined callback function. So malfunctions could be detected not                       */
 /* only while compile time but also while runtime.                                        */

  /* condition depends on runtime */
  #define LinAssertDynamic(c,p,e)           if(!(p)){ApplLinFatalError(e);}
  /* condition is always true */
  #define LinAssertStatic(c,e)              ApplLinFatalError(e)

/* Variables used to check the correct integration */

/* RAM CATEGORY 2 START*/
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 bInitCheck;
/* RAM CATEGORY 2 END*/

 #define kInitPattern ((vuint8) 0x53u)

#else
 /*lint -e750*/
 /* disable PC-lint info 750: "local macro 'XXX' not referenced" */

 #define LinAssertDynamic(c,p,e)
 #define LinAssertStatic(c,e)

 /* enable PC-lint info 750: "local macro 'XXX' not referenced" */
 /*lint +e750*/
#endif /* LIN_ENABLE_DEBUG */

/*******************************************************************************************/
/*******************************************************************************************/
/**  GROUP:  Network management                                                           **/
/*******************************************************************************************/
/*******************************************************************************************/
/** @defgroup grpNetManagement LIN network management
 *  @brief    Handles the transitions between sleep mode and awake mode (only Vector API)
 *
 *            This group handles the transition of the local state of a LIN node corresponding
 *            to the activities of the network. This contains
 *            - Transmission of wakeup frames
 *            - Evaluation of sleep mode frames
 *            - Monitoring of the wakeup and wakeup repetition
 *            - Notification of the application about transition to sleep or wakeup
 *            - Notification of the application in case of errors
 *
 *   @par     Wakeup handling
 *            When a wakeup frame is transmitted, the read back is expected. After the read back,
 *            the bus is supposed to be in the state awake. For a slave node, this must be
 *            confirmed by the reception of a Header (at least a valid synch pattern)
 *   @{ start group
 *******************************************************************************************/

#if defined ( LIN_APISTYLE_VECTOR )

/** @brief Current State of the Network management
 *
 *         Contains the current state of the NM. This value represents the nodes view of the
 *         network state
 */
/* RAM CATEGORY 1 START*/
V_MEMRAM0 static LIN_V_MEMRAM1 vuint8 LIN_V_MEMRAM2 bNmNetworkState;
/* RAM CATEGORY 1 END*/

  #define get_bNmNetworkState(c)            (bNmNetworkState)
  #define set_bNmNetworkState(c,val)        (bNmNetworkState = (val))


 #define kNmBusSleep                        ((vuint8) 0x00u)
 #define kNmWaitForWakeupFrmConf            ((vuint8) 0x01u)
 #define kNmAwakeWaitforWakeupConf          ((vuint8) 0x02u)
 #define kNmBusAwake                        ((vuint8) 0x03u)
 #define kNmWaitForSleepFrmConf             ((vuint8) 0x04u)


/*******************************************************************************************/
/*  Wakeup observation timeout timer                                                       */
/*******************************************************************************************/
/* Timer is implemented to be triggered from an ISR. To decouple the timer from main task  */
/* activities, an action request value must be used to change the timer state.            */
/* The init value of the timer is provided in lin_par_i.h                                  */

 #if defined ( LIN_ENABLE_LINSTART_WAKEUP_INTERNAL )


/* RAM CATEGORY 2 START*/
V_MEMRAM0 static LIN_V_MEMRAM1 vuint8             LIN_V_MEMRAM2 bNmWupTimerState;
/* RAM CATEGORY 2 END*/
   #define get_bNmWupTimerState(c)            (bNmWupTimerState)
   #define set_bNmWupTimerState(c, val)       (bNmWupTimerState = (val))

   #if !defined (SIO_LL_ENABLE_T_NO_WAKEUP_BY_HARDWARE)
/* RAM CATEGORY 2 START*/
V_MEMRAM0 static LIN_V_MEMRAM1 tLinNmWupTimerType LIN_V_MEMRAM2 bNmWupTimerValue;
V_MEMRAM0 static V_MEMRAM1     tLinNmWupTimerType V_MEMRAM2     bNmWupTimerNewValue;
/* RAM CATEGORY 2 END*/

    #define StartNmWupTimer(c)                 (bNmWupTimerNewValue = get_kNmWupTimerStartValue(c)); \
                                               (bNmWupTimerState = kNmWupTimerStart)
    #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
     #define StartNmWupTimer13(c)              (bNmWupTimerNewValue = get_kNmWupTimerStartValue13(c)); \
                                               (bNmWupTimerState = kNmWupTimerStart)
    #endif

    #define CancelNmWupTimer(c)                (bNmWupTimerState = kNmWupTimerCancel)
    #define get_bNmWupTimerValue(c)            (bNmWupTimerValue)
    #define set_bNmWupTimerValue(c, val)       (bNmWupTimerValue = (val))

    #define get_bNmWupTimerNewValue(c)         (bNmWupTimerNewValue)
    #define set_bNmWupTimerNewValue(c, val)    (bNmWupTimerNewValue = (val))
   #else
    /* Wakeup timer and observation provided by hardware. Wakeup repetition must be done by LIN driver */
    #define StartNmWupTimer(c)                 (bNmWupTimerState = kNmWupTimerActive_1); \
                                               SioSetMuteMode()
    #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
     #define StartNmWupTimer13(c)              (bNmWupTimerState = kNmWupTimerActive_1); \
                                               SioSetMuteMode()
    #endif
    #define get_bNmWupTimerValue(c)
    #define set_bNmWupTimerValue(c, val)
    #define CancelNmWupTimer(c)

    #define get_bNmWupTimerNewValue(c)
    #define set_bNmWupTimerNewValue(c, val)

   #endif /* !SIO_LL_ENABLE_T_NO_WAKEUP_BY_HARDWARE */


  #define kNmWupTimerIdle                    ((vuint8) 0x00u)
  #define kNmWupTimerStart                   ((vuint8) 0x01u)
 /* The following defines must have values of this values                   */
 /* kNmWupTimerActive_3 = kNmWupTimerActive_2 + 1 = kNmWupTimerActive_1 + 2 */
  #define kNmWupTimerActive_1                ((vuint8) 0x11u)
  #define kNmWupTimerActive_2                ((vuint8) 0x12u)
  #define kNmWupTimerActive_3                ((vuint8) 0x13u)
  #define kNmWupTimerCancel                  ((vuint8) 0x0Fu)

 #else /* LIN_ENABLE_LINSTART_WAKEUP_INTERNAL */

  #define StartNmWupTimer(c)
  #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
   #define StartNmWupTimer13(c)
  #endif

  #define CancelNmWupTimer(c)
  #define get_bNmWupTimerValue(c)
  #define set_bNmWupTimerValue(c, val)

  #define get_bNmWupTimerNewValue(c)
  #define set_bNmWupTimerNewValue(c, val)

  #define get_bNmWupTimerState(c)
  #define set_bNmWupTimerState(c, val)

 #endif /* LIN_ENABLE_LINSTART_WAKEUP_INTERNAL */

/*******************************************************************************************/
/*  No Wakeup notification delay timer                                                     */
/*******************************************************************************************/
 #if defined ( LIN_ENABLE_LINSTART_WAKEUP_INTERNAL ) && defined ( LIN_ENABLE_T_WAKEUP )
/* RAM CATEGORY 2 START*/
V_MEMRAM0 static LIN_V_MEMRAM1 tLinNmNoWupDelayTimerType LIN_V_MEMRAM2 bNmNoWupDelayTimerValue;
/* RAM CATEGORY 2 END*/

   #define Start_bNmNoWupDelayTimer(c)        (bNmNoWupDelayTimerValue = get_kNmNoWupDelayValue(c))
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
    #define Start_bNmNoWupDelayTimer13(c)     (bNmNoWupDelayTimerValue = get_kNmNoWupDelayValue13(c))
   #endif
   #define Cancel_bNmNoWupDelayTimer(c)       (bNmNoWupDelayTimerValue = 0)
   #define get_bNmNoWupDelayTimerValue(c)     (bNmNoWupDelayTimerValue)
   #define dec_bNmNoWupDelayTimerValue(c)     (bNmNoWupDelayTimerValue--)


 #else /* LIN_ENABLE_LINSTART_WAKEUP_INTERNAL && LIN_ENABLE_T_WAKEUP */

  #define Start_bNmNoWupDelayTimer(c)
  #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
   #define Start_bNmNoWupDelayTimer13(c)
  #endif
  #define Cancel_bNmNoWupDelayTimer(c)
  #define get_bNmNoWupDelayTimerValue(c)
  #define dec_bNmNoWupDelayTimerValue(c)

 #endif /* LIN_ENABLE_LINSTART_WAKEUP_INTERNAL && LIN_ENABLE_T_WAKEUP */

/*******************************************************************************************/
/*  Bus Idle timeout timer                                                                 */
/*******************************************************************************************/
 #if defined ( LIN_ENABLE_T_BUS_IDLE )
/* RAM CATEGORY 1 START*/
V_MEMRAM0 static LIN_V_MEMRAM1 tLinNmBusIdleTimerType LIN_V_MEMRAM2 bNmBusIdleTimerValue;
/* RAM CATEGORY 1 END*/

   #define SetNmBusIdleTimerStart(c)          (bNmBusIdleTimerValue = get_kNmBusIdleTimeoutValue(c))
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
    #define SetNmBusIdleTimerStart13(c)       (bNmBusIdleTimerValue = get_kNmBusIdleTimeoutValue13(c))
   #endif

   #define CancelNmBusIdleTimer(c)            (bNmBusIdleTimerValue = 0)
   #define get_NmBusIdleTimerValue(c)         (bNmBusIdleTimerValue)
   #define dec_NmBusIdleTimerValue(c)         (bNmBusIdleTimerValue--)


 #else /* LIN_ENABLE_T_BUS_IDLE */

  #if defined (SIO_LL_ENABLE_T_BUS_IDLE_BY_HARDWARE)
    #define SetNmBusIdleTimerStart(c)          SioSetMuteMode()
    #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
     #define SetNmBusIdleTimerStart13(c)       SioSetMuteMode()
    #endif
    #define CancelNmBusIdleTimer(c)            SioResetMuteMode()
  #else
   #define SetNmBusIdleTimerStart(c)
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
    #define SetNmBusIdleTimerStart13(c)
   #endif

   #define CancelNmBusIdleTimer(c)
   #define get_NmBusIdleTimerValue(c)
   #define dec_NmBusIdleTimerValue(c)
  #endif


 #endif /* LIN_ENABLE_T_BUS_IDLE */

 #if defined ( LIN_ENABLE_T_BUS_IDLE_MODE )
  #if defined ( SIO_LL_ENABLE_T_BUS_IDLE_BY_HARDWARE )
   #define set_bNmBusIdleTimerMode(c, val)
  #else
V_MEMRAM0 static LIN_V_MEMRAM1 vuint8 LIN_V_MEMRAM2 bNmBusIdleTimerMode;
    #define get_bNmBusIdleTimerMode(c)         (bNmBusIdleTimerMode)
    #define set_bNmBusIdleTimerMode(c, val)    (bNmBusIdleTimerMode = (val) )
  #endif
 #endif

/*******************************************************************************************/
/*  Sleep Mode Frame Repetition                                                            */
/*******************************************************************************************/
 #if defined ( LIN_ENABLE_SLPMODEFRM_REP )
  /* LIN master sleep mode frame repetion declarations */
  #if ! defined ( kNmSleepModeFrameRepNumber )
   #define kNmSleepModeFrameRepNumber           ((vuint8)0x04u)
  #endif
  #define kNmSleepModeFrameRepReWakeup          ((vuint8)0xFFu)

/* RAM CATEGORY 2 START*/
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 bLinSleepModeFrmRepCnt;
/* RAM CATEGORY 2 END*/
   #define get_bLinSleepModeFrmRepCnt(c)        (bLinSleepModeFrmRepCnt)
   #define set_bLinSleepModeFrmRepCnt(c, val)   (bLinSleepModeFrmRepCnt = (val))
 #endif

#else /* LIN_APISTYLE_VECTOR */
 #define SetNmBusIdleTimerStart(c)
 #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
  #define SetNmBusIdleTimerStart13(c)
 #endif
#endif

/*******************************************************************************************/
/*  Node configuration service timeout timer                                               */
/*******************************************************************************************/
#if defined ( LIN_ENABLE_T_NODE_CONFIG_SERVICE )
V_MEMRAM0 static LIN_V_MEMRAM1 vuint16 LIN_V_MEMRAM2 wNasTimerValue;

  #define dec_NasTimerValue(c)         (wNasTimerValue--)
  #define get_NasTimerValue(c)         (wNasTimerValue)
  #define set_NasTimerValue(c, val)    (wNasTimerValue = (val) )
#endif


#if defined ( LIN_ENABLE_SLEEP_COMMAND_REPETITION )
  /* LIN slave sleep mode frame repetion declarations */
/* RAM CATEGORY 2 START*/
V_MEMRAM0 static V_MEMRAM1 vuint16 V_MEMRAM2 wNmSleepDelayTimerValue;
V_MEMRAM0 static V_MEMRAM1 vuint8  V_MEMRAM2 bNmSleepCommandCounter;
/* RAM CATEGORY 2 END*/
 #define get_wNmSleepDelayTimerValue(c)          (wNmSleepDelayTimerValue)
 #define set_wNmSleepDelayTimerValue(c, val)     (wNmSleepDelayTimerValue = (val))
 #define dec_wNmSleepDelayTimerValue(c)          (wNmSleepDelayTimerValue--)

 #define get_bNmSleepCommandCounter(c)           (bNmSleepCommandCounter)
 #define set_bNmSleepCommandCounter(c, val)      (bNmSleepCommandCounter = (val))
 #define inc_bNmSleepCommandCounter(c)           (bNmSleepCommandCounter++)
#endif

/* @} end of grpNetManagement*/



/*******************************************************************************************/
/*******************************************************************************************/
/**  GROUP: LIN Message handler                                                         ****/
/*******************************************************************************************/
/*******************************************************************************************/
/** @defgroup grpMsgHandler  LIN Message handler
*
*   @brief    Performs the indication and confirmation handling of messages and the Wakeup signal
*
*             In the message handler, all high level handling of the wakeup frame, frame header
*             and frame response is performed.
*
*   @{
********************************************************************************************/

#if (defined ( LIN_ENABLE_ET_TX_FRAMES ) || defined ( LIN_ENABLE_ET_RX_FRAMES ))
 #define LIN_ENABLE_ET_FRAMES
#endif

#if defined ( LIN_ECUTYPE_SLAVE) && defined ( LIN_ENABLE_ET_TX_FRAMES )
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 bLinETFStoreFlag;
  #define get_bLinETFStoreFlag(c)        (bLinETFStoreFlag)
  #define set_bLinETFStoreFlag(c, val)   (bLinETFStoreFlag = (val))
#endif
typedef struct{
  vuint8 pbLinMsgBuffer[8];
  tLinFrameHandleType FrmHandle;
}tlocalMsgBufferType;

/** @brief local message buffer

           Message buffer which holds the currently received or transmitted data
           Managed by the Message handler and accessed by the frame processor
           Format:             |D0|D1|D2|D3|D4|D5|D6|D7|MsgHandle|
*/


/* RAM CATEGORY 1 START*/
V_MEMRAM0 static V_MEMRAM1 tlocalMsgBufferType V_MEMRAM2 pbMhMsgBuffer;
/* RAM CATEGORY 1 END*/

  /* Access macro to set/get the handle in the schedule task. */
 #define set_pbMhMsgBuffer_FrmHandle(c, val)    (pbMhMsgBuffer.FrmHandle = (val))
 #define get_pbMhMsgBuffer_FrmHandle(c)         (pbMhMsgBuffer.FrmHandle)
  /* Access macro to get the frame buffer pointer. */
 #define get_pbMhMsgBuffer_BufferPointer(c)     (pbMhMsgBuffer.pbLinMsgBuffer)



#if defined ( LIN_APISTYLE_LIN )

 #if ! defined ( LIN_GOTOSLEEPBIT_SET_AFTERCALL )         && \
     ! defined ( LIN_GOTOSLEEPBIT_SET_AFTERTRANSMISSION ) && \
     ! defined ( LIN_GOTOSLEEPBIT_SET_NEVER )
  /* If LIN_GOTOSLEEPBIT_SET_ is not defined set for compatibility to older generation tool version */
  #define LIN_GOTOSLEEPBIT_SET_AFTERTRANSMISSION
 #endif

/* Status info word corresponding to LIN spec */
/* RAM CATEGORY 1 START*/
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 bLinStatusInfo_LastPid;
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 bLinStatusInfo_Flags;
/* RAM CATEGORY 1 END*/

  #define set_bLinStatusInfo_LastPid(c, val)     (bLinStatusInfo_LastPid = (val))
  #define get_bLinStatusInfo_LastPid(c)          (bLinStatusInfo_LastPid)

  #define set_bLinStatusInfo_Flags(c, val)       (bLinStatusInfo_Flags = (val))
  #define get_bLinStatusInfo_Flags(c)            (bLinStatusInfo_Flags)


#endif /* LIN_APISTYLE_LIN */

#if defined ( LIN_ECUTYPE_SLAVE )

 #define kLinInvalidProtectedId                  ((vuint8) 0x40u)
 #if defined ( kLinInvalidHandle )
 #else
  #define kLinInvalidHandle                      ((tLinFrameHandleType) 0xFFFFu)
 #endif

 #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
  #define get_LinNumberOfConfigurablePIDs(c)     (cabNumberOfConfigurablePIDs[V_ACTIVE_IDENTITY_LOG])
  #define get_ConfigurablePIDHandleTbl(c)        (cabConfigurablePIDHandleTbl[V_ACTIVE_IDENTITY_LOG])
  #if defined ( LIN_ENABLE_CONFIGURABLE_PID )
   #define get_LinSlaveProtectedIdTbl(c)         (cabLinSlaveProtectedIdTbl)
  #else
   #define get_LinSlaveProtectedIdTbl(c)         (cabLinSlaveProtectedIdTbl[V_ACTIVE_IDENTITY_LOG])
  #endif
 #else
   #define get_LinNumberOfConfigurablePIDs(c)    (kLinNumberOfConfigurablePIDs)
   #define get_LinSlaveProtectedIdTbl(c)         (cabLinSlaveProtectedIdTbl)
   #define get_ConfigurablePIDHandleTbl(c)       (cabConfigurablePIDHandleTbl)
 #endif

 #if defined ( LIN_ENABLE_STATUSBIT_SIGNAL )
  #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
   #if defined ( LIN_ENABLE_RESP_ERR_IN_N_FRAMES )
    #define get_LinStatusBitFrameHandle(c, h)    (cabLinStatusBitFrameHandle[V_ACTIVE_IDENTITY_LOG][(h)])
    #define get_LinStatusBitOffset(c, h)         (cabLinStatusBitOffset[V_ACTIVE_IDENTITY_LOG][(h)])
    #define get_LinStatusBitMask(c, h)           (cabLinStatusBitMask[V_ACTIVE_IDENTITY_LOG][(h)])
   #else
    #if defined ( LIN_ENABLE_RESP_ERR_BIT_CONFIG )
V_MEMRAM0 static V_MEMRAM1 tLinFrameHandleType   V_MEMRAM2 bLinStatusBitFrameHandleRam;
V_MEMRAM0 static V_MEMRAM1 vuint8                V_MEMRAM2 bLinStatusBitOffsetRam;
V_MEMRAM0 static V_MEMRAM1 vuint8                V_MEMRAM2 bLinStatusBitMaskRam;

     #define get_LinStatusBitFrameHandle(c)      (bLinStatusBitFrameHandleRam)
     #define get_LinStatusBitOffset(c)           (bLinStatusBitOffsetRam)
     #define get_LinStatusBitMask(c)             (bLinStatusBitMaskRam)

     #define set_LinStatusBitFrameHandle(c,val)  (bLinStatusBitFrameHandleRam = (val))
     #define set_LinStatusBitOffset(c,val)       (bLinStatusBitOffsetRam = (val))
     #define set_LinStatusBitMask(c,val)         (bLinStatusBitMaskRam = (val))

     #define get_LinStatusBitFrameHandleRom(c)   (cabLinStatusBitFrameHandle[V_ACTIVE_IDENTITY_LOG])
     #define get_LinStatusBitOffsetRom(c)        (cabLinStatusBitOffset[V_ACTIVE_IDENTITY_LOG])
     #define get_LinStatusBitMaskRom(c)          (cabLinStatusBitMask[V_ACTIVE_IDENTITY_LOG])
    #else
     #define get_LinStatusBitFrameHandle(c)      (cabLinStatusBitFrameHandle[V_ACTIVE_IDENTITY_LOG])
     #define get_LinStatusBitOffset(c)           (cabLinStatusBitOffset[V_ACTIVE_IDENTITY_LOG])
     #define get_LinStatusBitMask(c)             (cabLinStatusBitMask[V_ACTIVE_IDENTITY_LOG])
    #endif
   #endif
  #else
    #if defined ( LIN_ENABLE_RESP_ERR_IN_N_FRAMES )
     #define get_LinStatusBitFrameHandle(c, h)   (cabLinStatusBitFrameHandle[(h)])
     #define get_LinStatusBitOffset(c, h)        (cabLinStatusBitOffset[(h)])
     #define get_LinStatusBitMask(c, h)          (cabLinStatusBitMask[(h)])
    #else
     #if defined ( LIN_ENABLE_RESP_ERR_BIT_CONFIG )
V_MEMRAM0 static V_MEMRAM1 tLinFrameHandleType   V_MEMRAM2 bLinStatusBitFrameHandleRam;
V_MEMRAM0 static V_MEMRAM1 vuint8                V_MEMRAM2 bLinStatusBitOffsetRam;
V_MEMRAM0 static V_MEMRAM1 vuint8                V_MEMRAM2 bLinStatusBitMaskRam;

      #define get_LinStatusBitFrameHandle(c)     (bLinStatusBitFrameHandleRam)
      #define get_LinStatusBitOffset(c)          (bLinStatusBitOffsetRam)
      #define get_LinStatusBitMask(c)            (bLinStatusBitMaskRam)

      #define set_LinStatusBitFrameHandle(c,val) (bLinStatusBitFrameHandleRam = (val))
      #define set_LinStatusBitOffset(c,val)      (bLinStatusBitOffsetRam = (val))
      #define set_LinStatusBitMask(c,val)        (bLinStatusBitMaskRam = (val))

      #define get_LinStatusBitFrameHandleRom(c)  (kLinStatusBitFrameHandle)
      #define get_LinStatusBitOffsetRom(c)       (kLinStatusBitOffset)
      #define get_LinStatusBitMaskRom(c)         (kLinStatusBitMask)
     #else
      #define get_LinStatusBitFrameHandle(c)     (kLinStatusBitFrameHandle)
      #define get_LinStatusBitOffset(c)          (kLinStatusBitOffset)
      #define get_LinStatusBitMask(c)            (kLinStatusBitMask)
     #endif
    #endif
  #endif
 #endif

#endif /* LIN_ECUTYPE_SLAVE */


/** @} end of grpMsgHandler*/

#if defined ( LIN_ECUTYPE_SLAVE )
/*******************************************************************************************/
/*******************************************************************************************/
/**  GROUP: LIN slave configuration                                                       **/
/*******************************************************************************************/
/*******************************************************************************************/
/** @defgroup grpSlaveCfg LIN Slave Configuration
 *
 *  @brief    Handles the slave configuration requests
 *
 *            The slave configuration implements the mandatory and optional slave
 *            configuration services
 *
 *   @{ start group
 *******************************************************************************************/
 #if defined ( LIN_ENABLE_SLAVE_CONFIGURATION )

  #define kScReqNotHandled                  ((vuint8)0x00u)
  #define kScReqHandled                     ((vuint8)0x01u)
  #define kScReqIgnored                     ((vuint8)0x02u)

/** @brief Message buffer to store the slave configuration response
 *  @note  The response frame is provided by the slave configuration of directly by the
 *         application
 */
V_MEMRAM0 static LIN_V_MEMRAM1 vuint8 LIN_V_MEMRAM2 bScResponseBuffer[8];
   #define set_bScResponseBuffer(c, i, val) (bScResponseBuffer[i] = (val))
   #define get_bScResponseBuffer(c, i)      (bScResponseBuffer[i])

  #define kScNADWildcard                    ((vuint8)0x7Fu)
  #define kScFunctionalNode                 ((vuint8)0x7Eu)

  #if defined ( LIN_ENABLE_SC_WILDCARDS )
   #define kScSupIdWildcard                 ((vuint16)0x7FFFu)
   #define kScSupIdMSBWildcard              ((vuint8)0x7Fu)
   #define kScSupIdLSBWildcard              ((vuint8)0xFFu)

   #define kScFuncIdWildcard                ((vuint16)0xFFFFu)
   #define kScFuncIdMSBWildcard             ((vuint8)0xFFu)
   #define kScFuncIdLSBWildcard             ((vuint8)0xFFu)
  #endif

  #define kScNRError_SNS                    ((vuint8)0x11u) /* service not supported      */
  #define kScNRError_SFNS                   ((vuint8)0x12u) /* sub function not supported */
  #define kScNRError_CNC                    ((vuint8)0x22u) /* conditions not correct     */

  #if defined ( LIN_ENABLE_USER_SLAVE_CONFIG )
   #define kUserSlaveConfigurationReserve   ((vuint8)0x80u)

V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 cabUserSlaveConfigSID[kNumberOfUserSlaveConfig] =
{
   #if ( kNumberOfUserSlaveConfig > 0 )
  kUserSlaveConfigSID_0
   #endif
   #if ( kNumberOfUserSlaveConfig > 1 )
  ,kUserSlaveConfigSID_1
   #endif
   #if ( kNumberOfUserSlaveConfig > 2 )
  ,kUserSlaveConfigSID_2
   #endif
   #if ( kNumberOfUserSlaveConfig > 3 )
  ,kUserSlaveConfigSID_3
   #endif
   #if ( kNumberOfUserSlaveConfig > 4 )
  ,kUserSlaveConfigSID_4
   #endif
   #if ( kNumberOfUserSlaveConfig > 5 )
  ,kUserSlaveConfigSID_5
   #endif
   #if ( kNumberOfUserSlaveConfig > 6 )
  ,kUserSlaveConfigSID_6
   #endif
   #if ( kNumberOfUserSlaveConfig > 7 )
  ,kUserSlaveConfigSID_7
   #endif
   #if ( kNumberOfUserSlaveConfig > 8 )
  ,kUserSlaveConfigSID_8
   #endif
   #if ( kNumberOfUserSlaveConfig > 9 )
  ,kUserSlaveConfigSID_9
   #endif
};
  #endif /* LIN_ENABLE_USER_SLAVE_CONFIG */

 #endif /* LIN_ENABLE_SLAVE_CONFIGURATION */

 #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
  #define get_LinSlaveProtectedIdInitTblPtr(c)       (cabLinSlaveProtectedIdInitTbl[V_ACTIVE_IDENTITY_LOG])
  #if defined (LIN_ENABLE_MESSAGE_ID_BY_APPL)
   #define get_LinSlaveMessageIdTbl(c, idObject)     (cabLinSlaveMessageIdTblRam[idObject])
  #else
   #define get_LinSlaveMessageIdTbl(c, idObject)     (cabLinSlaveMessageIdTbl[V_ACTIVE_IDENTITY_LOG][(idObject)])
  #endif
   #if defined (LIN_ENABLE_SUPPLIER_ID_BY_APPL)
    #define get_LinSupplierId(c)                     (wLinSupplierId)
   #else
    #define get_LinSupplierId(c)                     (cawLinSupplierId[V_ACTIVE_IDENTITY_LOG])
   #endif
  #define get_LinFunctionId(c)                       (cawLinFunctionId[V_ACTIVE_IDENTITY_LOG])
  #if defined (LIN_ENABLE_VARIANT_ID_BY_APPL)
   #define get_LinVariantId(c)                       (kLinVariantId)
  #else
   #define get_LinVariantId(c)                       (cabLinVariantId[V_ACTIVE_IDENTITY_LOG])
  #endif
 #else
   #define get_LinSlaveProtectedIdInitTblPtr(c)      (cabLinSlaveProtectedIdInitTbl)
   #if defined (LIN_ENABLE_MESSAGE_ID_BY_APPL)
    #define get_LinSlaveMessageIdTbl(c, idObject)    (cabLinSlaveMessageIdTblRam[idObject])
   #else
    #define get_LinSlaveMessageIdTbl(c, idObject)    (cabLinSlaveMessageIdTbl[idObject])
   #endif
   #if defined (LIN_ENABLE_SUPPLIER_ID_BY_APPL)
    #define get_LinSupplierId(c)                     (wLinSupplierId)
   #else
    #define get_LinSupplierId(c)                     (kLinSupplierId)
   #endif
   #define get_LinFunctionId(c)                      (kLinFunctionId)
   #define get_LinVariantId(c)                       (kLinVariantId)
 #endif

/** @} end of grpSlaveCfg*/

 #if defined (LIN_ENABLE_MESSAGE_ID_BY_APPL)
V_MEMRAM0        V_MEMRAM1 vuint16          V_MEMRAM2 cabLinSlaveMessageIdTblRam[kLinNumberOfIdObjects];
 #endif
 #if defined (LIN_ENABLE_SUPPLIER_ID_BY_APPL)
V_MEMRAM0        V_MEMRAM1 vuint16          V_MEMRAM2 wLinSupplierId;
 #endif


 #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
/* RAM CATEGORY 1 START*/
V_MEMRAM0 static V_MEMRAM1 vuint8           V_MEMRAM2 bCurrentProtocolVersion;
V_MEMRAM0        V_MEMRAM1 tMessageInfoType V_MEMRAM2 cabLinRxTxMsgInfoRam[kLinNumberOfMsgInfoObjects];
   #define get_bCurrentProtocolVersion(c)             (bCurrentProtocolVersion)
   #define set_bCurrentProtocolVersion(c,val)         (bCurrentProtocolVersion = (val))
   #define get_cabLinRxTxMsgInfoRam(c)                (cabLinRxTxMsgInfoRam)
/* RAM CATEGORY 1 END*/
 #endif

#endif /* LIN_ECUTYPE_SLAVE */


/*******************************************************************************************/
/*******************************************************************************************/
/**  GROUP: LIN Diagnostic dispatcher                                                     **/
/*******************************************************************************************/
/*******************************************************************************************/
/** @defgroup grpDiagDisp LIN Diagnostic dispatcher
*
*   @brief    Handles the transmission and reception of diagnostic messages and controls the
*             header transmission (MASTER ) and the slave response transmission.
*
*   @{ start group
********************************************************************************************/
#if defined ( LIN_ENABLE_DIAG_FRAMES )
 #if defined ( LIN_ECUTYPE_SLAVE )

  #if defined ( LIN_ENABLE_DIAG_FRAMES )
   #if defined ( LIN_ENABLE_DIAG_TRANSP_LAYER )
V_MEMRAM0 static V_MEMRAM1     vuint8 V_MEMRAM2      bDdDispatcherRxState;
     #define get_bDdDispatcherRxState(c)             (bDdDispatcherRxState)
     #define set_bDdDispatcherRxState(c, v)          (bDdDispatcherRxState = (v))
   #endif
V_MEMRAM0 static LIN_V_MEMRAM1 vuint8 LIN_V_MEMRAM2  bDdDispatcherTxState;
    #define get_bDdDispatcherTxState(c)             (bDdDispatcherTxState)
    #define set_bDdDispatcherTxState(c, v)          (bDdDispatcherTxState = (v))
  #endif
 #endif /* LIN_ECUTYPE_SLAVE */
#endif /* LIN_ENABLE_DIAG_FRAMES */

/** @} end of grpDiagDisp*/



/*****************************************************************************************/
/*****************************************************************************************/
/**  GROUP: Frame Processor                                                             **/
/*****************************************************************************************/
/*****************************************************************************************/
/** @defgroup grpFrmProcessor  LIN Frame processor

    @brief Transmission and reception of frame header, frame response and wakeup signal

           The frame processor implements the state machine for the transmission and
           reception of LIN frames and the reception and transmission of the wakeup signal.
           Beside a check of the monitored bytes, the timeout observation is also part of
           the frame processor.

           The frame processor is implemented in the functions
             ApplSioByteIndication()
             ApplSioErrnrNotification()
             LinFastTimerTask()

    @par   Variables, Functions and defines used by the Frame Processor
    @{    */
/*****************************************************************************************/


/** @brief Pointer of frame processor to message data
 *
 *         Pointer used by the frame processor to read or write data. Data buffer is
 *         located in the message handler
 */
/* RAM CATEGORY 1 START*/
V_MEMRAM0 static LIN_V_MEMRAM1 vuint8 * LIN_V_MEMRAM2 pbFpMsgBuf;
/* RAM CATEGORY 1 END*/

 #define get_pbFpMsgBuf(c)                  (pbFpMsgBuf)
 #define set_pbFpMsgBuf(c,val)              (pbFpMsgBuf = (val))

 #define get_pbFpMsgBufValue(c)             (*pbFpMsgBuf)
 #define set_pbFpMsgBufValue(c,val)         (*pbFpMsgBuf = (val))



/** @brief Local copy of the current protected ID
 *
 *         The protected ID is used for the checksum calculation and for the response
 *         notification
 */
 #define setbFpCurrentProtectedId(c, bProtectedId)   (bFpCurrentProtectedId = (bProtectedId))
 #define getbFpCurrentProtectedId(c)                 (bFpCurrentProtectedId )

/* RAM CATEGORY 1 START*/
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 bFpCurrentProtectedId;
/* RAM CATEGORY 1 END*/

#if defined ( LIN_APISTYLE_LIN ) && ( LIN_PROTOCOLVERSION_VALUE <= 0x20u )
  #define set_bFpConnectionState(c, bState) (bFpConnectionState = (bState))
  #define get_bFpConnectionState(c)         (bFpConnectionState)

/* RAM CATEGORY 1 START*/
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 bFpConnectionState;
/* RAM CATEGORY 1 END*/

 #define kIfcDisconnected                   ((vuint8) 0x00u)
 #define kIfcConnected                      ((vuint8) 0x01u)
#endif /* LIN_APISTYLE_LIN */

#if defined ( LIN_ENABLE_T_HEADER_MAX ) || defined ( LIN_ENABLE_T_FRAME_MAX )
/*******************************************************************************************/
/*  Frame processor timeout timer                                                          */
/*******************************************************************************************/
/* Timer is implemented to be triggered from an ISR. To decouple the timer from main task  */
/* activities, an action request value must be used.                                       */

/* RAM CATEGORY 2 START*/
V_MEMRAM0 static V_MEMRAM1     tLinFpTimerType  V_MEMRAM2     bFpTimerValue;
V_MEMRAM0 static LIN_V_MEMRAM1 vuint8           LIN_V_MEMRAM2 bFpTimerState;
V_MEMRAM0 static V_MEMRAM1     tLinFpTimerType  V_MEMRAM2     bFpTimerNewValue;
/* RAM CATEGORY 2 END*/

  #if defined ( SIO_ENABLE_BAUDRATE_DETECT )
   #define SetFpTimerStartHeaderObs(c)      (bFpTimerNewValue = get_HeaderTimeoutValue((c), bLinCurrentBaudrate)); (bFpTimerState = kFpTimerStartHeaderObs)
   #define SetFpTimerIncResponseObs(c, val) (bFpTimerNewValue = (val)); (bFpTimerState = kFpTimerIncResponseObs)
  #else
   #define SetFpTimerStartHeaderObs(c)      (bFpTimerNewValue = get_HeaderTimeoutValue(c)); (bFpTimerState = kFpTimerStartHeaderObs)
   #define SetFpTimerIncResponseObs(c, val) (bFpTimerNewValue = (val)); (bFpTimerState = kFpTimerIncResponseObs)
  #endif
  #define CancelFpTimer(c)                  (bFpTimerState = kFpTimerCancel)

  #define set_bFpTimerValue(c, val)         (bFpTimerValue = (val))
  #define get_bFpTimerValue(c)              (bFpTimerValue)

  #define set_bFpTimerState(c, val)         (bFpTimerState = (val))
  #define get_bFpTimerState(c)              (bFpTimerState)

  #define set_bFpTimerNewValue(c, val)      (bFpTimerNewValue = (val))
  #define get_bFpTimerNewValue(c)           (bFpTimerNewValue)


 #define kFpTimerIdle                       ((vuint8) 0x00u)
 #define kFpTimerStartHeaderObs             ((vuint8) 0x11u)
 #define kFpTimerIncResponseObs             ((vuint8) 0x23u)
 #define kFpTimerHeaderMode                 ((vuint8) 0x10u)
 #define kFpTimerResponseMode               ((vuint8) 0x20u)
 #define kFpTimerCancel                     ((vuint8) 0x0Fu)

#else /* LIN_ENABLE_T_HEADER_MAX || LIN_ENABLE_T_FRAME_MAX */

 #define SetFpTimerStartHeaderObs(c)
 #define SetFpTimerIncResponseObs(c, val)
 #define CancelFpTimer(c)
 #define get_bFpTimerValue(c)

#endif /* LIN_ENABLE_T_HEADER_MAX || LIN_ENABLE_T_FRAME_MAX */

#if defined ( LIN_ECUTYPE_SLAVE )
 #if defined ( SIO_LL_ENABLE_BAUDRATE_INFORMATION )
  #if defined ( SIO_ENABLE_BAUDRATE_DETECT )
   #if defined ( LIN_ENABLE_T_HEADER_MAX ) || \
       defined ( LIN_ENABLE_T_FRAME_MAX )  || \
       defined ( LIN_ENABLE_BAUDRATE_INFORMATION )
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 bLinCurrentBaudrate;
    #define LIN_CUR_BAUDRATE    (bLinCurrentBaudrate)
   #endif
  #endif
 #else
  #define   LIN_CUR_BAUDRATE    0
 #endif
#endif

/*******************************************************************************************/
/*  Error types detected by the frame processor                                            */
/*******************************************************************************************/

#if defined ( LIN_ECUTYPE_SLAVE )
 #define kFpError_HeaderRxSynchField        ((vuint8) 0x03u)
#endif

#define kFpError_HeaderTimeout              ((vuint8) 0x05u)
#if defined ( LIN_ECUTYPE_SLAVE )
 #define kFpError_HeaderRxFormat            ((vuint8) 0x07u)
#endif
/* Id parity error is not indicated, because it cannot be distinguished from unknown id */
#define kFpError_RespTxMonitoring           ((vuint8) 0x11u)
#define kFpError_RespTxFormat               ((vuint8) 0x12u)
#define kFpError_RespRxFormat               ((vuint8) 0x13u)
#define kFpError_RespRxChecksum             ((vuint8) 0x14u)
#define kFpError_RespOmittedTimeout         ((vuint8) 0x15u)
#define kFpError_RespIncompTimeout          ((vuint8) 0x16u)

/** @} end of grpFrmProcessor */

#if defined ( LIN_ECUTYPE_SLAVE )
#endif



/*******************************************************************************************/
/*   function prototypes of internal used functions                                        */
/*******************************************************************************************/



#if defined ( LIN_ECUTYPE_SLAVE )
 #if defined ( LIN_ENABLE_SLAVE_CONFIGURATION )
  #if defined ( LIN_ENABLE_USER_SLAVE_CONFIG )
static void LinScUserSlaveConfigHandleSetting(LIN_I_CHANNEL_TYPE_FIRST vuint8 bUserSlaveConfServiceNr, vuint8 bRespType, vuint8 bLength);
  #endif /* LIN_ENABLE_USER_SLAVE_CONFIG */

static vuint8 ScMasterReqPrecopyFct_CheckSuppIDFuncID(LIN_I_CHANNEL_TYPE_FIRST const vuint8* const pbDataPtr);
static void ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_TYPE_FIRST vuint8 bServiceID, vuint8 bErrorCode);
static vuint8 ScMasterReqPrecopyFct(LIN_I_CHANNEL_TYPE_FIRST const vuint8* const pbMsgDataPtr);

 #endif /* LIN_ENABLE_SLAVE_CONFIGURATION */
#endif /* LIN_ECUTYPE_SLAVE */


#if defined ( LIN_ENABLE_LINSTART_WAKEUP_INTERNAL )
 #if defined ( LIN_APISTYLE_VECTOR )
/* CODE CATEGORY 3 START*/
static void FpSendWakeup(LIN_I_CHANNEL_TYPE_ONLY);
/* CODE CATEGORY 3 END*/
 #endif
#endif

#if defined ( LIN_APISTYLE_VECTOR )
 #if defined ( LIN_ECUTYPE_SLAVE )
static void LinDoSleepModeHandling(LIN_I_CHANNEL_TYPE_ONLY);
static void LinDoWakeupHandling(LIN_I_CHANNEL_TYPE_ONLY);
 #endif
#endif
#if defined ( LIN_ENABLE_T_BUS_IDLE ) || defined ( SIO_LL_BUS_IDLE_IND ) || defined (SIO_LL_ENABLE_T_BUS_IDLE_BY_HARDWARE)
static void LinDoBusIdleHandling(LIN_I_CHANNEL_TYPE_ONLY);
#endif


/* CODE CATEGORY 1 START*/
static void FpConfigureResponse(LIN_I_CHANNEL_TYPE_FIRST tMessageInfoType vMessageInfo);
/* CODE CATEGORY 1 END*/

#if (defined ( LIN_APISTYLE_LIN ) || defined ( LIN_ENABLE_T_HEADER_MAX ) || defined ( LIN_ENABLE_T_FRAME_MAX ) || \
      ( defined ( LIN_APISTYLE_VECTOR ) &&  defined ( LIN_ENABLE_LINSTART_WAKEUP_EXTERNAL )))
/* CODE CATEGORY 1 START*/
static void FpSetMuteMode(LIN_I_CHANNEL_TYPE_ONLY);
/* CODE CATEGORY 1 END*/
#endif

/* CODE CATEGORY 2 START*/
static void FpResetMuteMode(LIN_I_CHANNEL_TYPE_ONLY);
/* CODE CATEGORY 2 END*/

/* CODE CATEGORY 1 START*/
static void ApplFpWakeupIndication(LIN_I_CHANNEL_TYPE_ONLY);
/* CODE CATEGORY 1 END*/


/* CODE CATEGORY 1 START*/
static void ApplFpHeaderIndication(LIN_I_CHANNEL_TYPE_FIRST vuint8 bProtectedId);
/* CODE CATEGORY 1 END*/

/* CODE CATEGORY 1 START*/
static void ApplFpResponseNotification(LIN_I_CHANNEL_TYPE_FIRST LIN_I_PROTECTED_ID_TYPE vuint8 bMsgDirection);
/* CODE CATEGORY 1 END*/

/* CODE CATEGORY 1 START*/
static void ApplFpErrorNotification(LIN_I_CHANNEL_TYPE_FIRST LIN_I_PROTECTED_ID_TYPE vuint8 bError);
/* CODE CATEGORY 1 END*/

#if defined ( LIN_APISTYLE_VECTOR )
 #if defined ( LIN_ENABLE_INIT_RX_DEFAULT_DATA )   || \
     defined ( LIN_ENABLE_START_RX_DEFAULT_DATA )  || \
     defined ( LIN_ENABLE_STOP_RX_DEFAULT_DATA )
/* CODE CATEGORY 2 START*/
static void LinSetRxDefaultValues(LIN_I_CHANNEL_TYPE_ONLY);
/* CODE CATEGORY 2 END*/
 #endif
 #if defined ( LIN_ENABLE_INIT_TX_DEFAULT_DATA )   || \
     defined ( LIN_ENABLE_START_TX_DEFAULT_DATA )  || \
     defined ( LIN_ENABLE_STOP_TX_DEFAULT_DATA )
/* CODE CATEGORY 2 START*/
static void LinSetTxDefaultValues(LIN_I_CHANNEL_TYPE_ONLY);
/* CODE CATEGORY 2 END*/
 #endif
#endif /* LIN_APISTYLE_VECTOR */

/*******************************************************************************************/
/*    Implementation of external Functions                                                 */
/*                                                                                         */
/*******************************************************************************************/

/*******************************************************************************************/
/*    API FUNCTION:  LinInitPowerOn() / l_sys_init()                                       */
/*******************************************************************************************/
/*    Documentation see lin_drv_os.h                                                       */
/*******************************************************************************************/
/* CODE CATEGORY 4 START*/
#if defined ( LIN_APISTYLE_LIN )
vuint8 l_sys_init(void)
#else
vuint8 LinInitPowerOn(void)
#endif
{

#if defined ( LIN_ENABLE_DEBUG )
  /* Check global interrupt to be disabled */

  /* Set init pattern which is checked by the API Functions to ensure initialized system */
  bInitCheck = kInitPattern;
#endif

#if defined ( SIO_LL_APISTYLE_MESSAGE )
  LinLowInitPowerOn();
#endif

#if defined ( LIN_APISTYLE_VECTOR )


  /* Initialize channel/interface specific variables */
  LinInit(LIN_I_CHANNEL_PARA_ONLY);


#else
  /* l_ifc_init must be called by the application */
#endif

  return(0);      /* Init is always accepted, ESCAN00016326 */
}
/* CODE CATEGORY 4 END*/

/*******************************************************************************************/
/*    FUNCTION:  LinInit() / l_ifc_init()                                                  */
/*******************************************************************************************/
/*    Documentation see lin_drv_os.h                                                       */
/*******************************************************************************************/
/* CODE CATEGORY 4 START*/
#if defined ( LIN_APISTYLE_LIN )
 #if ( LIN_PROTOCOLVERSION_VALUE <= 0x20u )
void   l_ifc_init(LIN_I_CHANNEL_TYPE_ONLY)  /* PRQA S 1330 *//* MD_LIN_DRV_16.4_B */
 #else
l_bool l_ifc_init(LIN_I_CHANNEL_TYPE_ONLY)  /* PRQA S 1330 *//* MD_LIN_DRV_16.4_B */
 #endif
#else
void LinInit(LIN_I_CHANNEL_TYPE_ONLY)
#endif
{
#if !defined ( LIN_APISTYLE_VECTOR )             || \
    !defined ( LIN_ENABLE_INIT_RX_DEFAULT_DATA ) || \
    !defined ( LIN_ENABLE_INIT_TX_DEFAULT_DATA ) || \
     defined ( LIN_ENABLE_COMPATIBILITY_MODE )
  tLinFrameHandleLoopType vLoopCount;
#endif
#if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
  tMessageInfoType        tmpMessageInfoObject;
#endif


  LinAssertDynamic(linchannel, (bInitCheck == kInitPattern) , kLinErrorNoLinInitPowerOn);


#if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
  if ( (get_bCurrentProtocolVersion(linchannel) != kLinProtocolCompatibility_13) &&
       (get_bCurrentProtocolVersion(linchannel) != kLinProtocolCompatibility_20) &&
       (get_bCurrentProtocolVersion(linchannel) != kLinProtocolCompatibility_21) &&
       (get_bCurrentProtocolVersion(linchannel) != kLinProtocolCompatibility_22) &&
       (get_bCurrentProtocolVersion(linchannel) != kLinProtocolCompatibility_J2602) )
  {
 #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
    /* set current protocol version to LIN2.1 */
    set_bCurrentProtocolVersion(linchannel, 0x21u);
 #else
    /* set current protocol version to LIN2.0 */
    set_bCurrentProtocolVersion(linchannel, 0x20u);
 #endif
  }
#endif


#if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
 #if defined ( SIO_LL_ENABLE_COMPATIBILITY_MODE )
  /* indicate active LIN protocol version to low level driver */
  SioSetProtocolVersion(LIN_I_CHANNEL_PARA_FIRST get_bCurrentProtocolVersion(linchannel));
 #endif
#endif


/*******************************************************************************************/
/*    initialize NmStateHandler                                                            */
/*******************************************************************************************/
#if defined ( LIN_APISTYLE_VECTOR )
  set_bNmNetworkState(linchannel, kNmBusSleep);
  set_bNmWupTimerValue(linchannel, 0);
  Cancel_bNmNoWupDelayTimer(linchannel);
 #if defined ( LIN_ENABLE_T_BUS_IDLE )
  CancelNmBusIdleTimer(linchannel);
 #else
  /* if bus idle in hardware is supported FpResetMuteMode will cleare the hardware timer */
 #endif
 #if defined ( LIN_ENABLE_T_BUS_IDLE_MODE )
  set_bNmBusIdleTimerMode(linchannel, kLinBusIdleActive);
 #endif
#endif

#if defined ( LIN_ENABLE_T_NODE_CONFIG_SERVICE )
  set_NasTimerValue(linchannel, 0x00u);
#endif

#if defined ( LIN_ENABLE_SLEEP_COMMAND_REPETITION )
  set_wNmSleepDelayTimerValue(linchannel, 0);
  set_bNmSleepCommandCounter(linchannel, 0);
#endif


#if defined ( LIN_ECUTYPE_SLAVE )
 #if defined ( LIN_ENABLE_DIAG_FRAMES )
  #if defined ( LIN_ENABLE_DIAG_TRANSP_LAYER )
  set_bDdDispatcherRxState(linchannel, kDdDiagFrmUser_SlaveConfig); /* set to highest priority */
  #endif
  set_bDdDispatcherTxState(linchannel, kDdDiagFrmUser_SlaveConfig); /* set to highest priority */
 #endif
 #if defined ( LIN_ENABLE_SLAVE_CONFIGURATION )
  set_bScResponseBuffer(linchannel, 0, 0x00u);                      /* clear pending node configuration request */
 #endif
 #if defined ( LIN_ENABLE_ASSIGN_NAD_COMMAND )
  setbLinConfiguredNAD(linchannel, getbLinInitialNAD(linchannel));
 #endif
#endif /* LIN_ECUTYPE_SLAVE */

/** \par  Message handler ******************************************************************
 *    initialize Message handler                                                           *
 *******************************************************************************************/
#if defined ( LIN_APISTYLE_LIN )
  /* initialize the bytes of the status word */
  set_bLinStatusInfo_LastPid(linchannel, 0);
  set_bLinStatusInfo_Flags(linchannel, 0);
#endif

  set_pbMhMsgBuffer_FrmHandle(linchannel, 0);
#if defined ( LIN_ECUTYPE_SLAVE )
 #if defined ( LIN_ENABLE_CONFIGURABLE_PID )
  #if defined ( LIN_ENABLE_INIT_PID_FROM_LDF ) || defined ( LIN_ENABLE_INIT_PID_FROM_NCF )
   #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
  VStdMemCpyRomToRam(get_LinSlaveProtectedIdTbl(linchannel), get_LinSlaveProtectedIdInitTblPtr(linchannel), get_LinNumberOfIdObjects(linchannel));
   #else
  VStdMemCpyRomToRam(get_LinSlaveProtectedIdTbl(linchannel), get_LinSlaveProtectedIdInitTblPtr(linchannel), get_LinNumberOfConfigurablePIDs(linchannel));
   #endif
  #else
   #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
  VStdMemFarSet(get_LinSlaveProtectedIdTbl(linchannel), kLinInvalidProtectedId, get_LinNumberOfIdObjects(linchannel));
   #else
  VStdMemFarSet(get_LinSlaveProtectedIdTbl(linchannel), kLinInvalidProtectedId, get_LinNumberOfConfigurablePIDs(linchannel));
   #endif
  #endif
 #endif
#endif /* LIN_ECUTYPE_SLAVE */

#if defined ( LIN_APISTYLE_VECTOR ) && defined ( LIN_ENABLE_INIT_RX_DEFAULT_DATA )
  /* Initialize message buffers of Rx messages to default values */
  LinSetRxDefaultValues(LIN_I_CHANNEL_PARA_ONLY);
#else /* LIN_APISTYLE_VECTOR && LIN_ENABLE_INIT_RX_DEFAULT_DATA */
 #if ( kLinNumberOfRxObjects > 0 )
  /* Initialize message buffers of Rx messages */
  for ( vLoopCount = (tLinFrameHandleLoopType)get_LinRxMsgBaseIndex(linchannel); vLoopCount < (tLinFrameHandleLoopType)(get_LinRxMsgBaseIndex(linchannel)+get_LinNumberOfChRxObjects(linchannel)); vLoopCount++ )
  {
  #if defined ( LIN_ENABLE_INIT_RX_DEFAULT_DATA )
    /* Initialize message buffers of Rx messages to default values */
    if ( get_LinRxTxMsgDataPtr(linchannel)[vLoopCount] != (tLinMsgDataPtrType)0)
    {
      VStdMemCpyRomToRam(get_LinRxTxMsgDataPtr(linchannel)[vLoopCount], get_LinRxTxDefaultDataPtrTbl(linchannel)[vLoopCount], get_kLinRxBufferLength(linchannel, vLoopCount));
    }
  #else
    /* Initialize message buffers of Rx messages to zero */
    if ( get_LinRxTxMsgDataPtr(linchannel)[vLoopCount] != (tLinMsgDataPtrType)0 )
    {
      VStdMemFarClr((void*)get_LinRxTxMsgDataPtr(linchannel)[vLoopCount],(vuint16)get_kLinRxBufferLength(linchannel ,vLoopCount));
    }
  #endif
  }
 #endif /* kLinNumberOfRxObjects > 0 */
#endif /* LIN_APISTYLE_VECTOR && LIN_ENABLE_INIT_RX_DEFAULT_DATA */

#if defined ( LIN_APISTYLE_VECTOR ) && defined ( LIN_ENABLE_INIT_TX_DEFAULT_DATA )
  /* Initialize message buffers of Tx messages to default values */
  LinSetTxDefaultValues(LIN_I_CHANNEL_PARA_ONLY);
#else /* LIN_APISTYLE_VECTOR && LIN_ENABLE_INIT_TX_DEFAULT_DATA */
 #if ( kLinNumberOfTxObjects > 0 )
  for ( vLoopCount = (tLinFrameHandleLoopType)get_LinTxMsgBaseIndex(linchannel); vLoopCount < (tLinFrameHandleLoopType)(get_LinTxMsgBaseIndex(linchannel)+get_LinNumberOfChTxObjects(linchannel)); vLoopCount++ )
  {
  #if defined ( LIN_ENABLE_INIT_TX_DEFAULT_DATA )
    /* Initialize message buffers of Tx messages to default values */
    if ( get_LinRxTxMsgDataPtr(linchannel)[vLoopCount] != (tLinMsgDataPtrType)0 )
    {
      VStdMemCpyRomToRam(get_LinRxTxMsgDataPtr(linchannel)[vLoopCount], get_LinRxTxDefaultDataPtrTbl(linchannel)[vLoopCount], get_LinRxTxMsgInfo(linchannel)[vLoopCount].MsgDataLength);
    }
  #else
    /* Initialize message buffers of Tx messages to zero */
    if ( get_LinRxTxMsgDataPtr(linchannel)[vLoopCount] != (tLinMsgDataPtrType)0 )
    {
      VStdMemFarClr((void*)get_LinRxTxMsgDataPtr(linchannel)[vLoopCount],(vuint16)get_LinRxTxMsgInfo(linchannel)[vLoopCount].MsgDataLength);
    }
  #endif
  }
 #endif /* kLinNumberOfTxObjects > 0 */
#endif /* LIN_APISTYLE_VECTOR && LIN_ENABLE_INIT_TX_DEFAULT_DATA */

#if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
  /* copy message info table to RAM image */
  if (get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_13)
  {
    for ( vLoopCount = (tLinFrameHandleLoopType)0; vLoopCount < (tLinFrameHandleLoopType)(get_LinNumberOfMsgInfoObjects(linchannel)); vLoopCount++ )
    { /* all frames are using classic checksum - set the checksum type to classic */
      tmpMessageInfoObject = get_LinRxTxMsgInfo(linchannel)[vLoopCount];
      tmpMessageInfoObject.MsgChecksumType = kChecksumClassic;
      get_cabLinRxTxMsgInfoRam(linchannel)[vLoopCount] = tmpMessageInfoObject;
    }
  }
  else
  {
    VStdMemCpyRomToRam(get_cabLinRxTxMsgInfoRam(linchannel), get_LinRxTxMsgInfo(linchannel), get_LinNumberOfMsgInfoObjects(linchannel)*sizeof(tMessageInfoType));
  }
#endif
#if defined ( LIN_ENABLE_FRAME_CFG_API )
  /* copy message info table to RAM image */
  VStdMemCpyRomToRam(cabLinRxTxMsgInfoRam, cabLinRxTxMsgInfo, get_LinNumberOfMsgInfoObjects(linchannel)*sizeof(tMessageInfoType));
  /* copy PID table to RAM image */
  VStdMemCpyRomToRam(cabLinMsgIdFieldTblRam, cabLinMsgIdFieldTbl, kLinNumberOfObjects);
#endif

#if defined ( LIN_ENABLE_RESP_ERR_BIT_CONFIG )
  /* Init response_error bit configuration from LDF settings */
  set_LinStatusBitFrameHandle(linchannel, get_LinStatusBitFrameHandleRom(linchannel) );
  set_LinStatusBitOffset(linchannel, get_LinStatusBitOffsetRom(linchannel));
  set_LinStatusBitMask(linchannel, get_LinStatusBitMaskRom(linchannel));
#endif


  /* Initialize unions of confirmation flags and indication flags */
#if defined ( LIN_ENABLE_MSG_CONFIRMATION_FLAG ) || defined ( LIN_ENABLE_DIAGMSG_CONFIRMATION_FLAG )
  VStdMemFarClr(((void*)&get_LinMsgConfirmationFlags(linchannel)),((vuint16)(get_LinNumberOfConfFlags(linchannel) + 7)/8));
#endif

#if defined ( LIN_ENABLE_MSG_INDICATION_FLAG ) || defined ( LIN_ENABLE_DIAGMSG_INDICATION_FLAG )
  VStdMemFarClr(((void*)&get_LinMsgIndicationFlags(linchannel)),((vuint16)(get_LinNumberOfIndFlags(linchannel) + 7)/8));
#endif

#if defined ( LIN_ECUTYPE_SLAVE )
 #if defined ( LIN_ENABLE_ET_TX_FRAMES )
 /* Initialize event triggered frame update flags */
  VStdMemFarClr((void*)&get_LinETFUpdateFlags(linchannel),(vuint16)(get_LinNumberOfEtTxObjects(linchannel) + 7)/8);
 #endif
#endif



/** \par Frame processor *******************************************************************
 *    initialize Frame processor                                                           *
 *******************************************************************************************/

#if defined ( SIO_LL_APISTYLE_MESSAGE )
/* init Frame processor timer */
 #if defined ( LIN_ENABLE_T_HEADER_MAX ) || defined ( LIN_ENABLE_T_FRAME_MAX )
  set_bFpTimerNewValue(linchannel, 0);
  set_bFpTimerState(linchannel, kFpTimerIdle);
  set_bFpTimerValue(linchannel, 0);
 #endif
#endif

#if defined ( LIN_ECUTYPE_SLAVE )
 #if defined ( SIO_LL_ENABLE_BAUDRATE_INFORMATION )
  #if defined ( SIO_ENABLE_BAUDRATE_DETECT )
   #if defined ( LIN_ENABLE_T_HEADER_MAX ) || \
       defined ( LIN_ENABLE_T_FRAME_MAX )  || \
       defined ( LIN_ENABLE_BAUDRATE_INFORMATION )
  bLinCurrentBaudrate       = 0;
   #endif
   #if defined ( LIN_ENABLE_BAUDRATE_INFORMATION )
  /* Inform application about current baud rate */
  ApplLinBaudrateInformation ( LIN_I_CHANNEL_PARA_FIRST 0 );
   #endif
  #endif
 #endif
#endif

#if defined ( LIN_APISTYLE_LIN ) && ( LIN_PROTOCOLVERSION_VALUE <= 0x20u )
  set_bFpConnectionState(linchannel, kIfcDisconnected);
#endif

#if defined ( LIN_ECUTYPE_SLAVE )
#endif

#if defined ( LIN_ECUTYPE_SLAVE )
 #if defined ( LIN_ENABLE_ET_TX_FRAMES )
  set_bLinETFStoreFlag(linchannel, 0x00u);
 #endif
#endif

/** \par SIO driver ************************************************************************/
/*    initialize SIO Driver                                                                */
/*******************************************************************************************/
#if defined ( SIO_LL_APISTYLE_MESSAGE )
  LinLowInit(LIN_I_CHANNEL_PARA_ONLY);
#endif
  /* Set Initial State of Frame processor to be able to receive Wakeup Frames */
  FpResetMuteMode(LIN_I_CHANNEL_PARA_ONLY);
#if defined ( LIN_APISTYLE_LIN )
 #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
  return 0; /* successful initialization */
 #endif
#endif
}
/* CODE CATEGORY 4 END*/

#if defined ( LIN_ECUTYPE_SLAVE )
#endif /* LIN_ECUTYPE_SLAVE */

/*******************************************************************************************/
/*******************************************************************************************/
/**  GROUP:  Network management                                                           **/
/*******************************************************************************************/
/*******************************************************************************************/

#if defined ( LIN_APISTYLE_VECTOR )
/*******************************************************************************************/
/*    FUNCTION:  LinStart                                                                  */
/*******************************************************************************************/
/*    Documentation see lin_drv.h                                                          */
/*******************************************************************************************/
 #if defined ( LIN_ENABLE_LINSTART_WAKEUP_INTERNAL ) || defined ( LIN_ENABLE_LINSTART_WAKEUP_EXTERNAL )
/* CODE CATEGORY 3 START*/
vuint8 LinStart(LIN_I_CHANNEL_TYPE_FIRST vuint8 bWakeUpReason)
{
  vuint8 bRc;

  /* Disable UART interrupts */
  LinStartTaskSync(LIN_I_CHANNEL_PARA_ONLY);

  LinAssertDynamic(linchannel, (bInitCheck == kInitPattern) , kLinErrorNoLinInitPowerOn);
  #if defined ( LIN_ENABLE_LINSTART_WAKEUP_INTERNAL ) && defined ( LIN_ENABLE_LINSTART_WAKEUP_EXTERNAL )
  LinAssertDynamic(linchannel, ((bWakeUpReason == kLinWakeUpInternal) || \
                                (bWakeUpReason == kLinWakeUpExternal)), kLinErrorWakeUpReason);
  #elif defined ( LIN_ENABLE_LINSTART_WAKEUP_INTERNAL )
  LinAssertDynamic(linchannel, (bWakeUpReason == kLinWakeUpInternal), kLinErrorWakeUpReason);
  #elif defined ( LIN_ENABLE_LINSTART_WAKEUP_EXTERNAL )
  LinAssertDynamic(linchannel, (bWakeUpReason == kLinWakeUpExternal), kLinErrorWakeUpReason);
  #endif

  bRc = 1; /* start communication rejected! (=> state is ACTIVE) as default, is overwritten if state is sleep */

  /* Start request only accepted in communication state SLEEP */
  if ( get_bNmNetworkState(linchannel) == kNmBusSleep )
  {

  #if defined ( LIN_ENABLE_LINSTART_WAKEUP_INTERNAL )
    if ( bWakeUpReason == kLinWakeUpInternal )
    {
      /* Start Wakeup observation */
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
      if (get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_13)
      {
        StartNmWupTimer13(linchannel);
      }
      else
   #endif
      {
        StartNmWupTimer(linchannel);
      }
      /* Send wakeup frame */
      set_bNmNetworkState(linchannel, kNmWaitForWakeupFrmConf);
      FpSendWakeup(LIN_I_CHANNEL_PARA_ONLY);
    }
    else
  #endif
    {
  #if defined ( LIN_ENABLE_LINSTART_WAKEUP_EXTERNAL )
      /* external Wakeup signal received outside of the driver */
      /* Bus state is awake, but waiting for the confirmation by header reception */
      FpSetMuteMode(LIN_I_CHANNEL_PARA_ONLY);

   #if defined ( LIN_ECUTYPE_SLAVE )
      LinDoWakeupHandling(LIN_I_CHANNEL_PARA_ONLY);
   #endif
      /* Start timeout observation after external wakup - bus idle observation used here due to other node issuing WU frame */
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
      if (get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_13)
      {
        SetNmBusIdleTimerStart13(linchannel);
      }
      else
   #endif
      {
        SetNmBusIdleTimerStart(linchannel);
      }
  #endif
    }

    bRc = 0; /* start communication accepted! (=> state is SLEEP) */
  }
  #if defined ( LIN_ENABLE_SLPMODEFRM_REP )
  else if ( get_bLinSleepModeFrmRepCnt(linchannel) != 0 )
  {
    /* currently on sleep mode frame repetition */
    /* stop repetition and send wakeup frame instead */
    if ( bWakeUpReason == kLinWakeUpInternal )
    {
      set_bLinSleepModeFrmRepCnt(linchannel, kNmSleepModeFrameRepReWakeup);
    }
  }
  #endif


  /* restore UART (TIMER, ...) interrupts */
  LinEndTaskSync(LIN_I_CHANNEL_PARA_ONLY);

  return(bRc); /* start communication accepted or rejected */
}
/* CODE CATEGORY 3 END*/
 #endif /* LIN_ENABLE_LINSTART_WAKEUP_INTERNAL || LIN_ENABLE_LINSTART_WAKEUP_EXTERNAL */

/*******************************************************************************************/
/*    FUNCTION:  LinSlowTimerTask                                                          */
/*******************************************************************************************/
/** @brief   Cyclic task used to implement the no wakeup indication and bus idle observation


 *  @return  void
    @pre     must be called from task level
    @note    The call cycle of the function determines the accuracy of the timeout observation
********************************************************************************************/
/* CODE CATEGORY 2 START*/
void LinSlowTimerTask(LIN_I_CHANNEL_TYPE_ONLY)
{
  /* Disable UART interrupts */
  LinStartTaskSync(LIN_I_CHANNEL_PARA_ONLY);

  LinAssertDynamic(linchannel, (bInitCheck == kInitPattern) , kLinErrorNoLinInitPowerOn);

 #if defined ( SIO_ENABLE_SIO_SLOW_POLLING_BY_DRV )
  /* supplementary task interface for low level driver */
  LinLowSlowPolling(LIN_I_CHANNEL_PARA_ONLY);
 #endif

  /* observes the bus idle timeout and notifies the application after T wup. */

 #if defined ( LIN_ENABLE_LINSTART_WAKEUP_INTERNAL )
  #if defined ( LIN_ENABLE_T_WAKEUP )
  if ( get_bNmNoWupDelayTimerValue(linchannel) != 0 )
  {
    dec_bNmNoWupDelayTimerValue(linchannel);
    if ( get_bNmNoWupDelayTimerValue(linchannel) == 0 )
    {
      /* Timer expired*/
      if ( get_bNmNetworkState(linchannel) == kNmWaitForWakeupFrmConf )
      {
        /* No wakeup frame confirmation after previous transmission */
        set_bNmNetworkState(linchannel, kNmBusSleep);
   #if defined ( LIN_ENABLE_PHYSICAL_BUS_ERROR )
        ApplLinProtocolError(LIN_I_CHANNEL_PARA_FIRST kLinPhysicalBusError, kMsgHandleDummy);
   #endif
      }
      else if ( get_bNmNetworkState(linchannel) == kNmAwakeWaitforWakeupConf )
      {
   #if defined ( LIN_ECUTYPE_SLAVE )
    #if defined ( LIN_ENABLE_NO_BUS_WAKEUP )
        ApplLinProtocolError(LIN_I_CHANNEL_PARA_FIRST kLinNoBusWakeUp, kMsgHandleDummy);
    #endif
        /* Sleep mode handling */
        LinDoSleepModeHandling(LIN_I_CHANNEL_PARA_ONLY);
   #endif
      }
      else
      {
        /* unexpected state, ignore the event. */
      }
    }
  }
  #endif /* LIN_ENABLE_T_WAKEUP */
 #endif /* LIN_ENABLE_LINSTART_WAKEUP_INTERNAL */

 #if defined ( LIN_ENABLE_T_BUS_IDLE )
  #if defined ( LIN_ENABLE_T_BUS_IDLE_MODE )
  if ( get_bNmBusIdleTimerMode(linchannel) == kLinBusIdleActive )
  #endif
  {
    if ( get_NmBusIdleTimerValue(linchannel) != 0 )
    {
      dec_NmBusIdleTimerValue(linchannel);
      if ( get_NmBusIdleTimerValue(linchannel) == 0 )
      {
        /* bus idle timer expired */
        LinDoBusIdleHandling(LIN_I_CHANNEL_PARA_ONLY);
      }
    }
  }
 #endif /* LIN_ENABLE_T_BUS_IDLE */
  /* restore UART (TIMER, ...) interrupts */
  LinEndTaskSync(LIN_I_CHANNEL_PARA_ONLY);
}
/* CODE CATEGORY 2 END*/

#else /* LIN_APISTYLE_VECTOR */
/*******************************************************************************************/
/*    API FUNCTION:  l_ifc_read_status                                                     */
/*******************************************************************************************/
/*    Documentation see lin_drv.h                                                          */
/********************************************************************************************/
/* CODE CATEGORY 2 START*/
vuint16 l_ifc_read_status(LIN_I_CHANNEL_TYPE_ONLY)  /* PRQA S 1330 *//* MD_LIN_DRV_16.4_B */
{
  vuint16 wReturnValue;


  /* Disable UART interrupts */
  LinStartTaskSync(LIN_I_CHANNEL_PARA_ONLY);
  /* Returns the current content of the status word and clears the status word afterwards */
  wReturnValue            = (vuint16)( ( (vuint16) get_bLinStatusInfo_LastPid(linchannel) << 8) | get_bLinStatusInfo_Flags(linchannel) );
  set_bLinStatusInfo_LastPid(linchannel, 0);
  set_bLinStatusInfo_Flags(linchannel, 0);
  /* restore UART (TIMER, ...) interrupts */
  LinEndTaskSync(LIN_I_CHANNEL_PARA_ONLY);

  return(wReturnValue);
}
/* CODE CATEGORY 2 END*/

#endif /* LIN_APISTYLE_LIN */



#if defined ( LIN_APISTYLE_VECTOR )
 #if defined ( LIN_ENABLE_T_BUS_IDLE_MODE )
/* CODE CATEGORY 2 START*/
void LinSetBusIdleTimerMode(LIN_I_CHANNEL_TYPE_FIRST vuint8 bMode)
{
   #if defined ( SIO_LL_ENABLE_T_BUS_IDLE_MODE )
  /* bus idle observation implemented in hardware - forward requested mode to SIO driver */
  SioSetBusIdleTimerMode(LIN_I_CHANNEL_PARA_FIRST bMode);
   #else
  set_bNmBusIdleTimerMode(linchannel, bMode);
   #endif
}
/* CODE CATEGORY 2 END*/
 #endif
#endif



#if defined ( LIN_ECUTYPE_SLAVE )

 #if defined ( LIN_ENABLE_DIAG_FRAMES )
/*******************************************************************************************/
/*******************************************************************************************/
/**  GROUP: LIN Diagnostic dispatcher                                                     **/
/*******************************************************************************************/
/*******************************************************************************************/

/* See lin_drv.h for documentation of this function */
void LinSetDiagnosticTxUser(LIN_I_CHANNEL_TYPE_FIRST vuint8 bDiagUser)
{
  set_bDdDispatcherTxState(linchannel, bDiagUser);
}
 #endif

 #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
/*******************************************************************************************/
/*******************************************************************************************/
/**  GROUP: LIN slave protocol compatibility                                              **/
/*******************************************************************************************/
/*******************************************************************************************/
void LinSetProtocolCompatibility(LIN_I_CHANNEL_TYPE_FIRST vuint8 bProtocolVersion)
{
  if ((bProtocolVersion == 0x13u) || (bProtocolVersion == 0x20u) ||
      (bProtocolVersion == 0x21u) || (bProtocolVersion == 0x22u) ||
      (bProtocolVersion == kLinProtocolCompatibility_J2602))
  { /* only valid protocol versions are accepted */
    set_bCurrentProtocolVersion(linchannel, bProtocolVersion);
  }
}
 #endif

 #if defined ( LIN_ENABLE_RESP_ERR_BIT_CONFIG )
/*******************************************************************************************/
/*******************************************************************************************/
/**  GROUP: LIN slave response_error definition                                           **/
/*******************************************************************************************/
/*******************************************************************************************/
void LinSetResponseErrorBit(LIN_I_CHANNEL_TYPE_FIRST tLinFrameHandleType vMsgHandle, vuint8 bByte, vuint8 bBitMask)
{
  set_LinStatusBitFrameHandle(linchannel, vMsgHandle);
  set_LinStatusBitOffset(linchannel, bByte);
  set_LinStatusBitMask(linchannel, bBitMask);
}
 #endif

 #if defined ( LIN_ENABLE_STATUSBIT_SIGNAL )
  #if defined ( LIN_ENABLE_STATUSBIT_SIGNAL_CHECK )
/*******************************************************************************************/
/*******************************************************************************************/
/**  GROUP: LIN slave response_error check                                                **/
/*******************************************************************************************/
/*******************************************************************************************/
vuint8 LinCheckResponseErrorBit(LIN_I_CHANNEL_TYPE_ONLY)
{
  vuint8 bRespErr;
  bRespErr = 0;

   #if defined ( LIN_ENABLE_J2602_STATUS_SIGNAL )
  bRespErr = get_bJ2602TxStatusCurrentNext(linchannel);
   #else
    #if defined ( LIN_ENABLE_RESP_ERR_IN_N_FRAMES )
  if ((get_LinRxTxMsgDataPtr(linchannel)[get_LinStatusBitFrameHandle(linchannel, 0)][get_LinStatusBitOffset(linchannel, 0)] & get_LinStatusBitMask(linchannel, 0)) != 0)
    #else
  if ((get_LinRxTxMsgDataPtr(linchannel)[get_LinStatusBitFrameHandle(linchannel)]   [get_LinStatusBitOffset(linchannel)] &    get_LinStatusBitMask(linchannel)) != 0 )
    #endif
  {
    bRespErr = 1;
  }
   #endif
  return bRespErr;
}
  #endif
 #endif

 #if defined ( LIN_ENABLE_CONFIGURABLE_PID )
/*******************************************************************************************/
/*******************************************************************************************/
/**  GROUP: LIN slave configuration                                                       **/
/*******************************************************************************************/
/*******************************************************************************************/

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
 *            LDF/NCF configurable_frames section.
 *            In case of multiple ECU length is one NAD plus sum of configurable PIDs over all identities
 *
 *   @param_i iii       channel number
 *
 *   @param   pldata    pointer to application data area
 *   @param   length    pointer to the length of provided data area
 *
 *
 *   @return  LD_READ_OK If the service was successful
 *   @return  LD_LENGTH_TOO_SHORT If configuration size is greater than length (no valid configuration).
 *
 *   @context Function must be called from task context. Calling from interrupt context is not allowed.
 *
 *   @pre     Driver is initialized and in sleep mode.
 *
 *******************************************************************************************/
   #if defined ( LIN_APISTYLE_VECTOR )
vuint8 LinReadConfiguration(LIN_I_CHANNEL_TYPE_FIRST vuint8* const pldata, vuint8* const length)
   #else
l_u8 ld_read_configuration(LIN_I_CHANNEL_TYPE_FIRST l_u8* const pldata, l_u8* const length)
   #endif
{
  vuint8 vRetValue;
   #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
  vuint8 bIndex;
   #endif

  vRetValue = LD_LENGTH_TOO_SHORT;

   #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
  if (*length >= (vuint8)(get_LinNumberOfIdObjects(linchannel) + 1))
   #else
  if (*length >= (vuint8)(get_LinNumberOfConfigurablePIDs(linchannel) + 1))
   #endif
  {
    LinStartTaskSync(LIN_I_CA_SL_CHANNEL_PARA_ONLY);
   #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
    *length = (vuint8)(get_LinNumberOfIdObjects(linchannel) + 1); /* set length of structure */
   #else
    *length = (vuint8)(get_LinNumberOfConfigurablePIDs(linchannel) + 1); /* set length of structure */
   #endif
    /* first byte of data structure is initial/configured NAD */
    pldata[0] = getbLinConfiguredNAD(linchannel);

   #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
    for (bIndex = 0; bIndex < get_LinNumberOfConfigurablePIDs(linchannel); bIndex++)
    { /* copy PID list to cabLinSlaveProtectedIdTbl in order according to LDF configurable_frames section */
      pldata[(vuint8)(bIndex+1)] = get_LinSlaveProtectedIdTbl(linchannel)[get_ConfigurablePIDHandleTbl(linchannel)[bIndex]];
    }
   #else
    #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
    VStdMemCpyRamToRam(&pldata[1], get_LinSlaveProtectedIdTbl(linchannel), get_LinNumberOfIdObjects(linchannel));
    #else
    VStdMemCpyRamToRam(&pldata[1], get_LinSlaveProtectedIdTbl(linchannel), get_LinNumberOfConfigurablePIDs(linchannel));
    #endif
   #endif
    LinEndTaskSync(LIN_I_CA_SL_CHANNEL_PARA_ONLY);
    vRetValue = LD_READ_OK;
  }

  return vRetValue;
}

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
 *            same as the frame list in the LDF/NCF configurable_frames section.
 *            In case of multiple ECU length is one NAD plus sum of configurable PIDs over all identities
 *
 *
 *   @param_i iii       channel number
 *
 *   @param   pldata    pointer to application data area
 *   @param   length    length of provided data area
 *
 *   @return  LD_SET_OK If the service was successful
 *   @return  LD_LENGTH_NOT_CORRECT required size is not equal to the given size
 *   @return  LD_DATA_ERROR The set of configuration could notbe made.
 *
 *   @context Function must be called from task context. Calling from interrupt context is not allowed.
 *
 *   @pre     This function should be called after LinInitPowerOn().
 *
 *******************************************************************************************/
   #if defined ( LIN_APISTYLE_VECTOR )
vuint8 LinSetConfiguration(LIN_I_CHANNEL_TYPE_FIRST const vuint8* const pldata, vuint8 length)
   #else
l_u8 ld_set_configuration (LIN_I_CHANNEL_TYPE_FIRST const l_u8* const pldata, l_u8 length)
   #endif
{
  vuint8 vRetValue;
   #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
  vuint8 bIndex;
   #endif

  vRetValue = LD_LENGTH_NOT_CORRECT;

   #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
  if (length == (vuint8)(get_LinNumberOfIdObjects(linchannel) + 1))
   #else
  if (length == (vuint8)(get_LinNumberOfConfigurablePIDs(linchannel) + 1))
   #endif
  {
   #if !defined ( LIN_ENABLE_ASSIGN_NAD_COMMAND )
    if (pldata[0] != getbLinConfiguredNAD(linchannel))
    { /* stored configuration does not match lin driver configuration of NAD */
      vRetValue = LD_DATA_ERROR;
    }
    else
   #endif
    {
      LinStartTaskSync(LIN_I_CA_SL_CHANNEL_PARA_ONLY);
   #if defined ( LIN_ENABLE_ASSIGN_NAD_COMMAND )
      setbLinConfiguredNAD(linchannel, pldata[0]); /* set configured NAD */
   #endif
   #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
      for (bIndex = 0; bIndex < get_LinNumberOfConfigurablePIDs(linchannel); bIndex++)
      { /* copy PID list to cabLinSlaveProtectedIdTbl in order according to LDF configurable_frames section */
        get_LinSlaveProtectedIdTbl(linchannel)[get_ConfigurablePIDHandleTbl(linchannel)[bIndex]] = pldata[(vuint8)(bIndex+1)];
      }
   #else
    #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
      VStdMemCpyRamToRam(get_LinSlaveProtectedIdTbl(linchannel), (void *)&pldata[1], get_LinNumberOfIdObjects(linchannel)); /* store PID list */
    #else
      VStdMemCpyRamToRam(get_LinSlaveProtectedIdTbl(linchannel), (void *)&pldata[1], get_LinNumberOfConfigurablePIDs(linchannel)); /* store PID list */
    #endif
   #endif
      LinEndTaskSync(LIN_I_CA_SL_CHANNEL_PARA_ONLY);
      vRetValue = LD_SET_OK;
    }
  }
  return vRetValue;
}
  #endif
 #endif


 #if defined ( LIN_ENABLE_SLAVE_CONFIGURATION )
  #if defined ( LIN_ENABLE_USER_SLAVE_CONFIG )
/*******************************************************************************************/
/*    FUNCTION:  LinScUserSlaveConfigHandleSetting                                         */
/*******************************************************************************************/
/**
 *   @brief   Function handles setting of the user specific diagnostic answer
 *
 *            The function is either called from ScMasterReqPrecopyFct (UART interrupt context)
 *            or from LinScSetRespUserSlaveConfig (task context with disabled UART interrupt).
 *            Before calling the function the access to the slave configuration answer must be
 *            checked.
 *            The function sets the Slave Response answer that is transmitted, depending on
 *            the parameters bRespType (positive, negative, no or pending answer) and bLength
 *            to set the length of a positive answer.
 *            If a positive answer with data has to be send, the data bytes have to be set before
 *            calling this function.
 *            If a negative answer has to be send, the error code has to be set before
 *            calling this function.
 *
 *   @param   bRespType     Type of answer (positive, negative, no or pending), s. ApplLinScUserSlaveConfig_x
 *   @param   bLength       Only needed if positive answer is selected with bRespType. Defines
 *                          the length of valid data.
 *
 *   @return  None
 *
 *   @note    Call context is UART Interrupt or task level with disabled UART Interrupt
 *
 *******************************************************************************************/
static void LinScUserSlaveConfigHandleSetting(LIN_I_CHANNEL_TYPE_FIRST vuint8 bUserSlaveConfServiceNr, vuint8 bRespType, vuint8 bLength)
{
  if ( bRespType == kLinSc_SendUserSpecConfig )
  {
    /* Send positive response */
    set_bScResponseBuffer(linchannel, 2, (vuint8)(cabUserSlaveConfigSID[bUserSlaveConfServiceNr] | 0x40u));  /* RSID, positive response */
    set_bScResponseBuffer(linchannel, 1, (vuint8)(bLength + 1));         /* PCI, length according to return value */
    set_bScResponseBuffer(linchannel, 0, getbLinConfiguredNAD(linchannel));        /* NAD */
    /* further data bytes are set by application */
  }
  else if ( bRespType == kLinSc_WaitForUserSpecConfig )
  {
    set_bScResponseBuffer(linchannel, 0, (vuint8)(kUserSlaveConfigurationReserve + bUserSlaveConfServiceNr));
  }
  else if ( bRespType == kLinSc_NoUserSpecConfig )
  {
    /* No response shall be send */
    set_bScResponseBuffer(linchannel, 0, 0x00u);                          /* no answer shall be transmitted to that request */
  }
  else
  {
    /* send negative response   */
    /* Error Code is set by application */
    set_bScResponseBuffer(linchannel, 3, cabUserSlaveConfigSID[bUserSlaveConfServiceNr]); /* SID */
    set_bScResponseBuffer(linchannel, 2, kRSID_NegativeResp);                             /* RSID, negative response */
    set_bScResponseBuffer(linchannel, 1, 0x03u);                                          /* PCI, length 3 */
    set_bScResponseBuffer(linchannel, 0, getbLinConfiguredNAD(linchannel));               /* NAD */
  }
}

/*******************************************************************************************/
/*    FUNCTION:  LinScSetRespUserSlaveConfig                                             */
/*******************************************************************************************/
/*    Documentation see lin_drv.h                                                          */
/*******************************************************************************************/
vuint8 LinScSetRespUserSlaveConfig(LIN_I_CHANNEL_TYPE_FIRST vuint8 bUserSlaveConfServiceNr, vuint8 bRespType, vuint8 bLength)
{
  vuint8 vRetValue;

  LinStartTaskSync(LIN_I_CA_SL_CHANNEL_PARA_ONLY);

  /* Check for right Error code */
  LinAssertDynamic(LIN_I_CA_SL_CHANNEL_PARA_ONLY, (bLength <= 5) , kLinErrorScInvalidLength);
  LinAssertDynamic(LIN_I_CA_SL_CHANNEL_PARA_ONLY, ( (bRespType == kLinSc_SendUserSpecConfig) || (bRespType == kLinSc_WaitForUserSpecConfig) || \
                                 (bRespType == kLinSc_NoUserSpecConfig)   || (bRespType == kLinSc_WrongUserSpecConfig) ) , kLinErrorScInvalidParam);

  vRetValue = 1;

  /* Check if request can be handled */
  if ( (get_bDdDispatcherTxState(linchannel) == kDdDiagFrmUser_SlaveConfig) && (get_bScResponseBuffer(linchannel, 0) == (kUserSlaveConfigurationReserve+bUserSlaveConfServiceNr)) )
  {
    vRetValue = 0;

    LinScUserSlaveConfigHandleSetting(LIN_I_CHANNEL_PARA_FIRST bUserSlaveConfServiceNr, bRespType, bLength);

   #if defined ( LIN_ENABLE_T_NODE_CONFIG_SERVICE )
    if ( bRespType == kLinSc_NoUserSpecConfig )
    {
      set_NasTimerValue(linchannel, 0x00u);
    }
   #endif
  }

  LinEndTaskSync(LIN_I_CA_SL_CHANNEL_PARA_ONLY);

  return(vRetValue);
}
  #endif /* LIN_ENABLE_USER_SLAVE_CONFIG */

/*******************************************************************************************/
/*    FUNCTION:  ScMasterReqPrecopyFct_CheckSuppIDFuncID                                   */
/*******************************************************************************************/
/**
 *   @brief   Check if Supplier ID and Function ID match
 *
 *            Function checks if the supplier identification and the function identification
 *            are correct.
 *            The pointer pbDataPtr must pointer to the LSB of the supplier ID. Following bytes
 *            are MSB supplier ID, LSB and MSB function id.
 *
 *   @param   pbDataPtr  Pointer to the first data byte to check the values
 *
 *   @return  1: Supplier ID and Function ID Match
 *            0: Supplier ID and Function ID do not Match
 *
 *   @note    Call context is UART Interrupt from function ScMasterReqPrecopyFct
 *
 *******************************************************************************************/
static vuint8 ScMasterReqPrecopyFct_CheckSuppIDFuncID(LIN_I_CHANNEL_TYPE_FIRST const vuint8 * const pbDataPtr)
{
  vuint8  bRetValue;
  #if defined ( C_CPUTYPE_32BIT ) || defined ( C_CPUTYPE_16BIT )
  vuint16 wSuppID;
  vuint16 wFuncID;
  #endif

  bRetValue = 0;

  #if defined ( LIN_ENABLE_SC_WILDCARDS )
   #if defined ( C_CPUTYPE_32BIT ) || defined ( C_CPUTYPE_16BIT )
  wSuppID = ((vuint16)pbDataPtr[1] << 8) | pbDataPtr[0];
  wFuncID = ((vuint16)pbDataPtr[3] << 8) | pbDataPtr[2];
  if ( ( ( wSuppID == get_LinSupplierId(linchannel) )   ||
         ( wSuppID == kScSupIdWildcard ) )    &&
       ( ( wFuncID == get_LinFunctionId(linchannel) )   ||
         ( wFuncID == kScFuncIdWildcard ) ) )
   #else
  if ( ( ( ( pbDataPtr[1] == (vuint8) ((get_LinSupplierId(linchannel) & 0xFF00u)>> 8) )  && ( pbDataPtr[0] == (vuint8) (get_LinSupplierId(linchannel) & 0x00FFu) ) ) ||  \
         ( ( pbDataPtr[1] == (vuint8) ((kScSupIdWildcard & 0xFF00u) >> 8) )    && ( pbDataPtr[0] == (vuint8) (kScSupIdWildcard & 0x00FFu) ) ) )  &&  \
       ( ( ( pbDataPtr[3] == (vuint8) ((get_LinFunctionId(linchannel) & 0xFF00u) >> 8) ) && ( pbDataPtr[2] == (vuint8) (get_LinFunctionId(linchannel) & 0x00FFu) ) ) ||  \
         ( ( pbDataPtr[3] == (vuint8) ((kScFuncIdWildcard & 0xFF00u) >> 8) )   && ( pbDataPtr[2] == (vuint8) (kScFuncIdWildcard & 0x00FFu) ) ) ) )
   #endif
  #else
   #if defined ( C_CPUTYPE_32BIT ) || defined ( C_CPUTYPE_16BIT )
  wSuppID = ((vuint16)pbDataPtr[1] << 8) | pbDataPtr[0];
  wFuncID = ((vuint16)pbDataPtr[3] << 8) | pbDataPtr[2];
  if ( ( ( wSuppID == get_LinSupplierId(linchannel) )   &&
         ( wFuncID == get_LinFunctionId(linchannel) ) ) )
   #else
  if ( ( ( pbDataPtr[1] == (vuint8) ((get_LinSupplierId(linchannel) & 0xFF00u) >> 8) )   && ( pbDataPtr[0] == (vuint8) (get_LinSupplierId(linchannel) & 0x00FFu) ) ) &&  \
       ( ( pbDataPtr[3] == (vuint8) ((get_LinFunctionId(linchannel) & 0xFF00u) >> 8) )   && ( pbDataPtr[2] == (vuint8) (get_LinFunctionId(linchannel) & 0x00FFu) ) ) )
   #endif
  #endif
  {
    bRetValue = 1;
  }

  return(bRetValue);
}

/*******************************************************************************************/
/*    FUNCTION:  ScMasterReqPrecopyFct_ConfigNegResp                                       */
/*******************************************************************************************/
/**
 *   @brief   Configure negative response to node configuration request
 *
 *            Function set the negative response of a node configuration request.
 *            The service identifier and error code are given be parameters.
 *
 *   @param   bServiceID  The service identifier is written to byte 3 of the negative response
 *            bErrorCode  The error code is written to byte 4 of the negative response
 *
 *   @return  None
 *
 *   @note    Call context is UART Interrupt from function ScMasterReqPrecopyFct
 *
 *******************************************************************************************/
static void ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_TYPE_FIRST vuint8 bServiceID, vuint8 bErrorCode)
{
  /* send negative response   */
  set_bScResponseBuffer(linchannel, 4, bErrorCode);              /* ErrorCode, Service not supported */
  set_bScResponseBuffer(linchannel, 3, bServiceID);              /* SID */
  set_bScResponseBuffer(linchannel, 2, kRSID_NegativeResp);      /* RSID, negative response */
  set_bScResponseBuffer(linchannel, 1, 0x03u);                   /* PCI, length 3 */
  set_bScResponseBuffer(linchannel, 0, getbLinConfiguredNAD(linchannel));  /* NAD */
}

/*******************************************************************************************/
/*    FUNCTION:  ScMasterReqPrecopyFct                                                     */
/*******************************************************************************************/
/**
 *   @brief   Precopy function of a Master Request frame
 *
 *            The function is called by the message handler, when a Master Request frame is
 *            received and slave configuration is active. The function handles the request,
 *            when the address information matches, a single frame is received and the
 *            service is in the range 0xB0 - 0xB4/0xB7. Mandatory services are always handled.
 *            the handling of optional services is done by the function when enabled or
 *            forwarded to the application.
 *            Services in the range of 0xB0 - 0xB4/0xB7 with a not matching address information
 *            are indicated to the diagnostic dispatcher to be handled. No response will be
 *            provided in this case.
 *
 *   @param   pbMsgDataPtr  Pointer to the data of the Master Requet frame
 *
 *   @return  HandlingState Informs the Diagnostic dispatcher whether the frame is handled
 *            by the slave configuration or not.
 *
 *   @note    Call context is UART Interrupt
 *
 *******************************************************************************************/
static vuint8 ScMasterReqPrecopyFct(LIN_I_CHANNEL_TYPE_FIRST const vuint8* const pbMsgDataPtr)
{
  #if ( LIN_PROTOCOLVERSION_VALUE <= 0x20u ) || defined ( LIN_ENABLE_COMPATIBILITY_MODE ) || defined ( LIN_ENABLE_ASSIGN_ID_BY_APPL )
  vuint16 wTmpMessageId;
  #endif
  vuint8  bRetValue;
  vuint8  bTmpByte;
  tLinFrameHandleLoopType vLoopCount;
  vuint8  bTmpLength;

  #if defined ( LIN_ENABLE_USER_SLAVE_CONFIG )
  vuint8  bCount;
  #endif
  #if ( LIN_PROTOCOLVERSION_VALUE <= 0x20u ) || defined ( LIN_ENABLE_COMPATIBILITY_MODE ) || defined ( LIN_ENABLE_ASSIGN_ID_BY_APPL )
   #if defined ( LIN_ENABLE_SC_WILDCARDS )
    #if defined ( C_CPUTYPE_32BIT ) || defined ( C_CPUTYPE_16BIT )
  vuint16 wSuppID;
    #endif
   #endif
  #endif

  #if ( defined ( LIN_ENABLE_COND_CHANGE_NAD_COMMAND ) && defined ( LIN_ENABLE_ASSIGN_NAD_COMMAND ) )
  vuint8  bTmpScipConditionCheck;
  #endif


  #if defined ( LIN_ENABLE_FULL_NAD_RANGE )
  if ( (pbMsgDataPtr[1] >= 0x01u) && (pbMsgDataPtr[1] <= 0x06u) )
  #else
  if ( (pbMsgDataPtr[0]<0x80u) && (pbMsgDataPtr[1] >= 0x01u) && (pbMsgDataPtr[1] <= 0x06u) )
  #endif
  {

  #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
    if ((get_bCurrentProtocolVersion(linchannel) >= kLinProtocolCompatibility_21) && (get_bScResponseBuffer(linchannel, 0) != 0) && (pbMsgDataPtr[0] == 0x7Eu))
   #else
    if ((get_bScResponseBuffer(linchannel, 0) != 0) && ( pbMsgDataPtr[0] == 0x7Eu ))
   #endif
    { /* functional request while physical response is pending */
      /* ignore request and keep response - kScReqIgnored but rejected later as only own NAD and wildcard are supported */
      bRetValue = kScReqIgnored;    /* presetting is that the frame is handled by the slave configuration */
    }
    else
  #endif
    {
      /* Single frame with valid diagnostic address received */
      bRetValue = kScReqHandled;   /* presetting is that the frame is handled by the slave configuration */
      set_bScResponseBuffer(linchannel, 0, 0x00u);         /* Using the first byte of the response data as response enable flag */
                                                           /* presetting that the succeeding slave response is not transmitted. */
      set_bScResponseBuffer(linchannel, 1, 0x01u);         /* PCI, length 1, presetting to most common length */
      set_bScResponseBuffer(linchannel, 2, (vuint8)(pbMsgDataPtr[2] + 0x40u)); /* RSID, presetting to default RSID */

      /* Set bytes of response buffer to value "unused" */
      set_bScResponseBuffer(linchannel, 3, 0xFFu);
      set_bScResponseBuffer(linchannel, 4, 0xFFu);
      set_bScResponseBuffer(linchannel, 5, 0xFFu);
      set_bScResponseBuffer(linchannel, 6, 0xFFu);
      set_bScResponseBuffer(linchannel, 7, 0xFFu);
  #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
      if ( (pbMsgDataPtr[2] >= 0xB0u) && (pbMsgDataPtr[2] <= 0xB7u) )
  #else
      /* #elif ( LIN_PROTOCOLVERSION_VALUE <= 0x20u ) */
      if ( (pbMsgDataPtr[2] >= 0xB0u) && (pbMsgDataPtr[2] <= 0xB4u) )
  #endif
      {
  #if defined ( LIN_ENABLE_ASSIGN_NAD_COMMAND )
        if ( pbMsgDataPtr[2] == kSID_AssignNAD )
        { /* received NAD must match initial NAD value */
          bTmpByte  = getbLinInitialNAD(linchannel);
        }
        else
  #endif
        { /* received NAD must match configured NAD value */
          bTmpByte  = getbLinConfiguredNAD(linchannel);
        }

  #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
        if ( ((get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_J2602) && ( pbMsgDataPtr[2] == kSID_J2602TargetedReset )) ||
    #if defined ( LIN_ENABLE_J2602_B6_B7 )
             ((get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_J2602) && ( pbMsgDataPtr[2] == kSID_SaveConfiguration )) ||
    #endif
             ((get_bCurrentProtocolVersion(linchannel) >= kLinProtocolCompatibility_21) && ( pbMsgDataPtr[2] == kSID_SaveConfiguration )) )
   #else
        if ( pbMsgDataPtr[2] == kSID_SaveConfiguration )
   #endif
        {
          bTmpLength  = 0x01u;
        }
        else
        {
          bTmpLength  = 0x06u;
        }
  #else
        bTmpLength  = 0x06u;
  #endif

        if ( (pbMsgDataPtr[1] == bTmpLength) && ( (pbMsgDataPtr[0] == bTmpByte) || (pbMsgDataPtr[0] == kScNADWildcard) ) )
        {
          switch (pbMsgDataPtr[2])
          {
            /* valid node configuration request which adresses this node - check specific service */
            case kSID_AssignNAD:
              /* 0xB0 Assign NAD request (optional) */
              /* This slave is addressed by NAD*/
              /* Check now matching supplier ID and Function ID */

              bTmpByte = ScMasterReqPrecopyFct_CheckSuppIDFuncID(LIN_I_CHANNEL_PARA_FIRST &pbMsgDataPtr[3]);

              if ( bTmpByte != 0 )
              {
  #if defined ( LIN_ENABLE_ASSIGN_NAD_COMMAND )
   #if defined ( LIN_ENABLE_ASSIGN_NAD_COMMAND_DYN )
                bTmpByte = ApplLinScDynAssignNAD( LIN_I_CHANNEL_PARA_FIRST pbMsgDataPtr);
                if (kLinSc_Reject_ASSING_NAD_COMMAND == bTmpByte)
                {
                  /* send negative response, service not supported */
                  ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_PARA_FIRST kSID_AssignNAD, kScNRError_SNS);
                }
                else if (kLinSc_Ignore_ASSING_NAD_COMMAND == bTmpByte)
                {
                  /* negative response suppressed */
                }
                else
   #endif
                {
                  /* Assign NAD, the range of the configured NAD is not verified. */
                  setbLinConfiguredNAD(linchannel, pbMsgDataPtr[7]);
   #if defined ( LIN_ENABLE_SLAVE_CONFIG_OPT_RESP )
                  /* Send positive response */
                  set_bScResponseBuffer(linchannel, 0, getbLinInitialNAD(linchannel));   /* INAD */
   #endif
                }
  #else /* LIN_ENABLE_ASSIGN_NAD_COMMAND */
   #if defined ( LIN_ENABLE_SLAVE_CONFIG_OPT_RESP )
                /*
                  ScMasterReqPrecopyFct_ConfigNegResp used getbLinConfiguredNAD() in response,
                  but this is identical to getbLinInitialNAD() if Assign NAD is not supported.
                */
                /* send negative response, service not supported */
                ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_PARA_FIRST kSID_AssignNAD, kScNRError_SNS);
   #endif
  #endif /* LIN_ENABLE_ASSIGN_NAD_COMMAND */
              }
              else
              {
                /* Wrong Supplier id or function id. A response should not be send */
                /* Frame filtered out, but not handled */
              }
            break;
            case kSID_AssignFrameId:
  #if ( LIN_PROTOCOLVERSION_VALUE <= 0x20u )
              /* 0xB1 Assign frame ID request (mandatory) */
              /* Format NAD|PCI|SID|SUP_LSB|SUP_MSB|MSG_LSB|MSG_MSB|PID  */
              /* Check matching supplier id */
   #if defined ( LIN_ENABLE_SC_WILDCARDS )
    #if defined ( C_CPUTYPE_32BIT ) || defined ( C_CPUTYPE_16BIT )
              wSuppID =   (vuint16) pbMsgDataPtr[3];
              wSuppID |=  (vuint16) pbMsgDataPtr[4] << 8;

              if ( ( wSuppID == get_LinSupplierId(linchannel) )   ||
                   ( wSuppID == kScSupIdWildcard ) )
    #else
              if ( ( ( pbMsgDataPtr[4] == (vuint8) ((get_LinSupplierId(linchannel) & 0xFF00u) >> 8) ) && ( pbMsgDataPtr[3] == (vuint8) (get_LinSupplierId(linchannel) & 0x00FFu) ) ) || \
                   ( ( pbMsgDataPtr[4] == (vuint8) ((kScSupIdWildcard & 0xFF00u) >> 8) )    && ( pbMsgDataPtr[3] == (vuint8) (kScSupIdWildcard & 0x00FFu) ) ) )
    #endif
   #else
              if ( ( pbMsgDataPtr[4] == (vuint8) ((get_LinSupplierId(linchannel) & 0xFF00u) >> 8) )   && ( pbMsgDataPtr[3] == (vuint8) (get_LinSupplierId(linchannel) & 0x00FFu) ) )
   #endif
              {
                /* Supplier ID matches. The PID value is not verified. PID == 0x40u sets the PID to invalid */
                wTmpMessageId =   (vuint16) pbMsgDataPtr[5];
                wTmpMessageId |=  (vuint16) pbMsgDataPtr[6] << 8;

   #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
                if (wTmpMessageId == 0xFFFFu)
                {
                  /* Message ID 0xFFFFu not allowed for MultiEcu */
    #if defined ( LIN_ENABLE_SLAVE_CONFIG_OPT_RESP )
                  /* send negative response, sub function not supported */
                  ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_PARA_FIRST kSID_AssignFrameId, kScNRError_SFNS);
    #endif
                }
                else
   #endif /* LIN_ENABLE_MULTI_ECU_CONFIG */
                {
                  /* Search message id in message list */
   #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
                  for ( vLoopCount = 0; vLoopCount < get_LinNumberOfIdObjects(linchannel); vLoopCount++ )
   #else
                  for ( vLoopCount = 0; vLoopCount < get_LinNumberOfConfigurablePIDs(linchannel); vLoopCount++ )
   #endif
                  {
                    if ( get_LinSlaveMessageIdTbl(linchannel, vLoopCount) == wTmpMessageId )
                    {
                      /* Message ID found. Set requested protected ID */
   #if defined ( LIN_ENABLE_CONFIGURABLE_PID )
                      get_LinSlaveProtectedIdTbl(linchannel)[vLoopCount] = pbMsgDataPtr[7];
   #endif
   #if defined ( LIN_ENABLE_SLAVE_CONFIG_OPT_RESP )
                      /* Send positive response */
                      set_bScResponseBuffer(linchannel, 0, getbLinConfiguredNAD(linchannel));  /* NAD */
   #endif
                      break; /* PRQA S 3333 *//* MD_LIN_DRV_14.6 */
                    }
                    else
                    {
    #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
                      if ( vLoopCount == (get_LinNumberOfIdObjects(linchannel) - 1) )
    #else
                      if ( vLoopCount == (get_LinNumberOfConfigurablePIDs(linchannel) - 1) )
    #endif
                      {
                        /* Message ID not found in message list. */
   #if defined ( LIN_ENABLE_SLAVE_CONFIG_OPT_RESP )
                        /* send negative response, sub function not supported */
                        ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_PARA_FIRST kSID_AssignFrameId, kScNRError_SFNS);
   #endif
                      }
                    }
                  }
                }
              }
              else
              {
                /* Wrong Supplier id. A response should not be send */
                /* Frame filtered out, but not handled */
              }
  #else
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE ) || defined ( LIN_ENABLE_ASSIGN_ID_BY_APPL )
    #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
              if (( get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_20 ) ||
                  ( get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_J2602) )
    #endif
              {
                /* Assign frame ID request (mandatory) */
                /* Format NAD|PCI|SID|SUP_LSB|SUP_MSB|MSG_LSB|MSG_MSB|PID  */
                /* Check matching supplier id */
    #if defined ( LIN_ENABLE_SC_WILDCARDS )
     #if defined ( C_CPUTYPE_32BIT ) || defined ( C_CPUTYPE_16BIT )
                wSuppID =   (vuint16) pbMsgDataPtr[3];
                wSuppID |=  (vuint16) pbMsgDataPtr[4] << 8;

                if ( ( wSuppID == get_LinSupplierId(linchannel) )   ||
                  ( wSuppID == kScSupIdWildcard ) )
     #else
                if ( ( ( pbMsgDataPtr[4] == (vuint8) ((get_LinSupplierId(linchannel) & 0xFF00u) >> 8) ) && ( pbMsgDataPtr[3] == (vuint8) (get_LinSupplierId(linchannel) & 0x00FFu) ) ) || \
                     ( ( pbMsgDataPtr[4] == (vuint8) ((kScSupIdWildcard & 0xFF00u) >> 8) )    && ( pbMsgDataPtr[3] == (vuint8) (kScSupIdWildcard & 0x00FFu) ) ) )
     #endif
    #else
                if ( ( pbMsgDataPtr[4] == (vuint8) ((get_LinSupplierId(linchannel) & 0xFF00u) >> 8) )   && ( pbMsgDataPtr[3] == (vuint8) (get_LinSupplierId(linchannel) & 0x00FFu) ) )
    #endif
                {
                  /* Supplier ID matches. The PID value is not verified. PID == 0x40u sets the PID to invalid */
                  wTmpMessageId =   (vuint16) pbMsgDataPtr[5];
                  wTmpMessageId |=  (vuint16) pbMsgDataPtr[6] << 8;

                  bTmpByte = ApplLinScAssignId(LIN_I_CHANNEL_PARA_FIRST wTmpMessageId, pbMsgDataPtr[7]);
                  if ( bTmpByte != kLinSc_AssignIdSendNegativeResponse )
                  { /* only positive or negative response accepted - response send if optional slave response is enabled */
    #if defined ( LIN_ENABLE_SLAVE_CONFIG_OPT_RESP )
                    /* Send positive response */
                    set_bScResponseBuffer(linchannel, 0, getbLinConfiguredNAD(linchannel));  /* NAD */
    #endif
                  }
                  else
                  {
                    /* Negative response will be send */
    #if defined ( LIN_ENABLE_SLAVE_CONFIG_OPT_RESP )
                    /* send negative response, sub function not supported */
                    ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_PARA_FIRST kSID_AssignFrameId, kScNRError_SFNS);
    #endif
                  }
                }
                else
                {
                  /* Wrong Supplier id. A response should not be send */
                  /* Frame filtered out, but not handled */
                }
              }
   #else
              /* send negative response - service not supported any more */
              ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_PARA_FIRST kSID_AssignFrameId, kScNRError_SNS);
   #endif
  #endif
            break;
            case kSID_ReadById:
              /* 0xB2 Read by Identifier request (mandatory for ID 0) */
              /* Check matching supplier id and function id */

              bTmpByte = ScMasterReqPrecopyFct_CheckSuppIDFuncID(LIN_I_CHANNEL_PARA_FIRST &pbMsgDataPtr[4]);
              if ( bTmpByte != 0 )
              { /* supplier id and function id match */
                /* Check on RDBI: ID==0 */
                if ( pbMsgDataPtr[3] == 0 )
                { /* Read product identification is requested */

                  /* Send positive response */

                  /*lint -e778*/
                  /* disable PC-lint info 778: "Constant expression evaluates to 0 in operation  '&'" */
                  /*lint -e572*/
                  /* disable PC-lint warning 572: "Excessive shift value (precission 0 shifted right by 8)" */
                  /* RSID has already been set */
                  /* usage of macros to obtain supplier and function id because wildcards may be used in request data */
                  set_bScResponseBuffer(linchannel, 7, (vuint8) (get_LinVariantId(linchannel)));                     /* Variant */
                  set_bScResponseBuffer(linchannel, 6, (vuint8) ((get_LinFunctionId(linchannel) & 0xFF00u) >> 8));   /* Function Id MSM */
                  set_bScResponseBuffer(linchannel, 5, (vuint8) (get_LinFunctionId(linchannel) & 0x00FFu));          /* Function Id LSM */
                  set_bScResponseBuffer(linchannel, 4, (vuint8) ((get_LinSupplierId(linchannel) & 0xFF00u) >> 8));   /* Supplier Id MSM */
                  set_bScResponseBuffer(linchannel, 3, (vuint8) (get_LinSupplierId(linchannel) & 0x00FFu));          /* Supplier Id LSM */
                  set_bScResponseBuffer(linchannel, 1, 0x06u);                                                       /* PCI, length 6 */
                  set_bScResponseBuffer(linchannel, 0, getbLinConfiguredNAD(linchannel));                            /* NAD */
                  /*lint +e572*/
                  /* enable PC-lint warning 572: "Excessive shift value (precission 0 shifted right by 8)" */
                  /*lint +e778*/
                  /* enable PC-lint info 778: "Constant expression evaluates to 0 in operation  '&'" */
                }

  #if defined ( LIN_ENABLE_READ_BY_ID_BY_APPL )
                /* Check on RDBI: ID==1 */
                else if ( pbMsgDataPtr[3] == 1 )
                { /* get Serial Nr is requested */
   #if defined ( LIN_APISTYLE_VECTOR )
                  bTmpByte = ApplLinScGetSerialNumber(LIN_I_CHANNEL_PARA_FIRST (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
                  if ( bTmpByte == kLinSc_SendSerialNr )
   #else
                  bTmpByte = ld_read_by_id_callout (LIN_I_CA_SL_CHANNEL_PARA_ONLY, 1, (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
                  if ( bTmpByte == LD_POSITIVE_RESPONSE )
   #endif
                  { /* Send positive response */
                    set_bScResponseBuffer(linchannel, 1, 0x05u);                             /* PCI, length 5 */
                    set_bScResponseBuffer(linchannel, 0, getbLinConfiguredNAD(linchannel));  /* NAD */
                    /* RSID has already been set */
                    /* The other data must be provided by the application */
                  }
   #if defined ( LIN_APISTYLE_LIN )
                  else if ( bTmpByte == LD_NO_RESPONSE )
                  {
                    bTmpByte = 0; /* No response will be send */
                  }
   #endif
                  else
                  {
   #if defined ( LIN_APISTYLE_LIN )
                    bTmpByte = 1; /* Negative response will be send */
   #else
                    /* Negative response will be send */
   #endif
                  }
                }
  #endif

  #if defined ( LIN_ENABLE_READ_BY_ID_MESSAGE_IDS )
                /* Check on RDBI: ID==[16, 31] */
                else if (( pbMsgDataPtr[3] > 15 ) && ( pbMsgDataPtr[3] < 32 ))
                {
                  /* Identifier is message information. Information is always provided */
                  if ( pbMsgDataPtr[3] < (get_LinNumberOfConfigurablePIDs(linchannel)+16) )
                  {
                    bTmpByte             = (vuint8)(pbMsgDataPtr[3]-16);
                    set_bScResponseBuffer(linchannel, 5, (get_LinSlaveProtectedIdTbl(linchannel)[bTmpByte]));                        /* Protected ID   */
                    set_bScResponseBuffer(linchannel, 4, (vuint8)((get_LinSlaveMessageIdTbl(linchannel, bTmpByte) & 0xFF00u) >> 8)); /* Message Id MSB */
                    set_bScResponseBuffer(linchannel, 3, (vuint8)(get_LinSlaveMessageIdTbl(linchannel, bTmpByte) & 0x00FFu));        /* Message Id LSB */
                    /* RSID has already been set */
                    set_bScResponseBuffer(linchannel, 1, 0x04u);                             /* PCI, length 4 */
                    /* Send positive response */
                    set_bScResponseBuffer(linchannel, 0, getbLinConfiguredNAD(linchannel));  /* NAD */
                  }
                  else
                  {
                    /* Requested ID out of message index range. Return sub function not supported */
                  }
                }
  #endif

  #if defined ( LIN_ENABLE_READ_BY_ID_BY_APPL )
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
                /* Check on RDBI: ID==[16, 63] LIN 2.0 */
                /* Check on RDBI: ID==[32, 63] LIN 2.1 */
                else if ( ((get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_20)    && ( pbMsgDataPtr[3] > 15 ) && ( pbMsgDataPtr[3] < 64 )) ||
                          ((get_bCurrentProtocolVersion(linchannel) >= kLinProtocolCompatibility_21)    && ( pbMsgDataPtr[3] > 31 ) && ( pbMsgDataPtr[3] < 64 ))  )
   #else
                  /* Check on RDBI: ID==[32, 63] */
                else if ( ( pbMsgDataPtr[3] > 31 ) && ( pbMsgDataPtr[3] < 64 ) )
   #endif
                {
                  /* User defined identifier is requested. Request application for handling */
                  /* Using here bTmpByte to store the return value temporarily */
   #if defined ( LIN_APISTYLE_VECTOR )
                  bTmpByte = ApplLinScGetUserDefinedId(LIN_I_CHANNEL_PARA_FIRST pbMsgDataPtr[3], (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
   #else
                  bTmpByte = ld_read_by_id_callout (LIN_I_CA_SL_CHANNEL_PARA_ONLY, pbMsgDataPtr[3], (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
   #endif
                  LinAssertDynamic(LIN_I_CA_SL_CHANNEL_PARA_ONLY, (bTmpByte <= 6) , kLinErrorScInvalidLength);

   #if defined ( LIN_APISTYLE_VECTOR )
                  if ( bTmpByte != kLinSc_SendNegativeResponse )
   #else
                  if ( bTmpByte != LD_NEGATIVE_RESPONSE )
   #endif
                  { /* (response length != 0) or status not LD_NEGATIVE_RESPONSE */
   #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
    #if defined ( LIN_APISTYLE_VECTOR )
                    if ( bTmpByte == kLinSc_NoResponse )
    #else
                    if ( bTmpByte == LD_NO_RESPONSE )
    #endif
                    {
                      bTmpByte = 0; /* No response will be send */
                    }
                    else
   #endif
                    {
                      /* Send positive response */
                      set_bScResponseBuffer(linchannel, 1, (vuint8)((bTmpByte + 1) & 0x0Fu));  /* PCI, user defined return value length (1-6bytes) */
                      set_bScResponseBuffer(linchannel, 0, getbLinConfiguredNAD(linchannel));  /* NAD */
                      /* RSID has already been set */
                      /* The other data must be provided by the application */
                    }
                  }
                  else
                  {
                    bTmpByte = 1; /* Negative response will be send */
                  }
                }
  #endif
                else
                {
                  /* Replied with negative response */
                }

                /* Check if negative or no response should be send */
                if ( get_bScResponseBuffer(linchannel, 0) == 0 )
                { /* check if a negative or no response should be send */
                  if (bTmpByte != 0) /* PRQA S 3355, 3358 *//* MD_LIN_DRV_13.7 */
                  {
                    /* Send negative response, sub function not supported */
                    ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_PARA_FIRST kSID_ReadById, kScNRError_SFNS);
                  }
                }
              }
              else
              {
                /* Wrong Supplier id or function id. */
  #if defined ( LIN_DISABLE_RDBI_NR_SUP_MISMATCH ) || defined ( LIN_ENABLE_COMPATIBILITY_MODE ) || ( LIN_PROTOCOLVERSION_VALUE == 0x20u )
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE ) && ( !defined ( LIN_DISABLE_RDBI_NR_SUP_MISMATCH ))
                if ( get_bCurrentProtocolVersion(linchannel) >= kLinProtocolCompatibility_21 )
                {
                  /* Send negative response, sub function not supported */
                  ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_PARA_FIRST kSID_ReadById, kScNRError_SFNS);
                }
                else
   #endif
                {
                  /* legacy setting for missmatch - no negative response reported */
                }
  #else
                /* Send negative response, sub function not supported */
                ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_PARA_FIRST kSID_ReadById, kScNRError_SFNS);
  #endif
              }
            break;
            case kSID_CondChangeNAD:
              /* 0xB3 Conditional change NAD request (optional) */
  #if ( defined ( LIN_ENABLE_COND_CHANGE_NAD_COMMAND ) && defined ( LIN_ENABLE_ASSIGN_NAD_COMMAND ) )
              bTmpScipConditionCheck = 0;
              if ( pbMsgDataPtr[3] == 0 )
              {
                /* Identifier references the product identification */
                switch (pbMsgDataPtr[4])
                {
                  case 1:
                    /* Condition is applied to Supplier Id lSB */
                    bTmpByte = (vuint8)(get_LinSupplierId(linchannel) & 0x00FFu);
                  break;
                  case 2:
                    /* Condition is applied to Supplier Id MSB */
                    /*lint -e778*/
                    /* disable PC-lint info 778: "Constant expression evaluates to 0 in operation  '&'" */
                    /*lint -e572*/
                    /* disable PC-lint warning 572: "Excessive shift value (precission 0 shifted right by 8)" */
                    bTmpByte = (vuint8)((get_LinSupplierId(linchannel) & 0xFF00u) >> 8);
                    /*lint +e572*/
                    /* enable PC-lint warning 572: "Excessive shift value (precission 0 shifted right by 8)" */
                    /*lint +e778*/
                    /* enable PC-lint info 778: "Constant expression evaluates to 0 in operation  '&'" */
                  break;
                  case 3:
                    /* Condition is applied to Function Id lSB */
                    bTmpByte = (vuint8)(get_LinFunctionId(linchannel) & 0x00FFu);
                  break;
                  case 4:
                    /* Condition is applied to Function Id MSB */
                    /*lint -e778*/
                    /* disable PC-lint info 778: "Constant expression evaluates to 0 in operation  '&'" */
                    /*lint -e572*/
                    /* disable PC-lint warning 572: "Excessive shift value (precission 0 shifted right by 8)" */
                    bTmpByte = (vuint8)((get_LinFunctionId(linchannel) & 0xFF00u) >> 8);
                    /*lint +e572*/
                    /* enable PC-lint warning 572: "Excessive shift value (precission 0 shifted right by 8)" */
                    /*lint +e778*/
                    /* enable PC-lint info 778: "Constant expression evaluates to 0 in operation  '&'" */
                  break;
                  case 5:
                    /* Condition is applied to Variant Id */
                    bTmpByte = get_LinVariantId(linchannel);
                  break;
                  default:
                    bTmpScipConditionCheck = 1;
                  /*lint -e527*/
                  /* disable PC-lint warning 527: "unreachable" */
                  break;
                  /* enable PC-lint info 527: "unreachable" */
                  /*lint +e527*/
                }
              }
   #if defined ( LIN_ENABLE_READ_BY_ID_BY_APPL )
              else if ( pbMsgDataPtr[3] == 1 )                                /* ID 1 */
              { /* Identifier references the serial number */
                if ((pbMsgDataPtr[4] > 0) && (pbMsgDataPtr[4] < 5))
                { /* query byte in valid range of 1 to 4 */
    #if defined ( LIN_APISTYLE_VECTOR )
                  bTmpByte = ApplLinScGetSerialNumber(LIN_I_CHANNEL_PARA_FIRST (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
                  if ( bTmpByte == kLinSc_SendSerialNr )
    #else
                  bTmpByte = ld_read_by_id_callout (LIN_I_CA_SL_CHANNEL_PARA_ONLY, 1, (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
                  if ( bTmpByte == LD_POSITIVE_RESPONSE )
    #endif
                  { /* serial number is valid and can be used for calculation */
                    /* read requested byte into bTmpByte - byte value starts with 1 so read from byte 3 to 6 */
                    bTmpByte = get_bScResponseBuffer(linchannel, (vuint8)(2+pbMsgDataPtr[4]));
                    /* clear now the response buffer again */
                    set_bScResponseBuffer(linchannel, 3, 0xFFu);  /* stuffing byte */
                    set_bScResponseBuffer(linchannel, 4, 0xFFu);  /* stuffing byte */
                    set_bScResponseBuffer(linchannel, 5, 0xFFu);  /* stuffing byte */
                    set_bScResponseBuffer(linchannel, 6, 0xFFu);  /* stuffing byte */
                  }
                  else
                  { /* serial number is optional and was not provided by application */
                    bTmpScipConditionCheck = 1;
                  }
                }
                else
                { /* invalid access to 4 bytes serial number */
                  bTmpScipConditionCheck = 1;
                }
              }
   #endif

   #if ( LIN_PROTOCOLVERSION_VALUE <= 0x20u )
              else if ( pbMsgDataPtr[3] < 16 )
              {
                /* Id is out of supported range. Sub function not supported */
                /* Conditional change NAD based on serial number is not supported */
                bTmpScipConditionCheck = 1;
              }
              else if (pbMsgDataPtr[3] < 32 )
              {
    #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
                /* message IDs not supported to prevent additional mapping table from message id index to handle */
    #else
                if ( pbMsgDataPtr[3] < (vuint8)(get_LinNumberOfConfigurablePIDs(linchannel) + 16) )
                {
                  /* Requested ID is in the range of available messages */
                  /* get the referenced byte */
                  bTmpByte     = (vuint8)(pbMsgDataPtr[3]-16);

                  switch (pbMsgDataPtr[4])
                  {
                    case 1:
                      /* Condition is applied to Message Id LSB*/
                      bTmpByte = (vuint8)(get_LinSlaveMessageIdTbl(linchannel, bTmpByte) & 0x00FFu);
                    break;
                    case 2:
                      /* Condition is applied to Message Id MSB*/
                      bTmpByte = (vuint8)((get_LinSlaveMessageIdTbl(linchannel, bTmpByte) & 0xFF00u) >> 8);
                    break;
                    case 3:
                      /* Condition is applied to protected id*/
                      bTmpByte = get_LinSlaveProtectedIdTbl(linchannel)[bTmpByte];
                    break;
                    default:
                      /* Referenced byte out of range */
                      bTmpScipConditionCheck = 1;
                    /*lint -e527*/
                    /* disable PC-lint warning 527: "unreachable" */
                    break;
                    /* enable PC-lint info 527: "unreachable" */
                    /*lint +e527*/
                  }
                }
                else
    #endif
                {
                  bTmpScipConditionCheck = 1;
                }
              }
   #endif
              else
              {
                /* Id is out of supported range. sub function not supported */
                /* Conditional change NAD based on serial number is not supported */
                bTmpScipConditionCheck = 1;
              }
              if ( bTmpScipConditionCheck == 0 )
              {
                /* Calculate the condition result */
                bTmpByte ^= pbMsgDataPtr[6];       /* Do a bitwise XOR with Invert */
                bTmpByte &= pbMsgDataPtr[5];       /* Do a bitwise AND with Mask */

                /* If the final result is zero, then change the NAD */
                if ( bTmpByte == 0 )
                {
   #if defined ( LIN_ENABLE_SLAVE_CONFIG_OPT_RESP )
                  /* Send positive response */
                  set_bScResponseBuffer(linchannel, 0, getbLinConfiguredNAD(linchannel));  /* NAD */
   #endif
                  /* Change the NAD after providing the response so that the response NAD corresponds */
                  /* with the request NAD   */
                  setbLinConfiguredNAD(linchannel, pbMsgDataPtr[7]);
                }
                else
                {
                  /* negative response not used for this service to avoid collisions */
                }
              }
  #else /* LIN_ENABLE_COND_CHANGE_NAD_COMMAND && LIN_ENABLE_ASSIGN_NAD_COMMAND */
              /* negative response not used for this service */
  #endif /* LIN_ENABLE_COND_CHANGE_NAD_COMMAND && LIN_ENABLE_ASSIGN_NAD_COMMAND */
          break;
          case kSID_DataDump:
            /* 0xB4 Data dump request (optional) */
  #if defined ( LIN_ENABLE_DATA_DUMP_BY_APPL )
              bTmpByte = ApplLinScDataDump(LIN_I_CHANNEL_PARA_FIRST &pbMsgDataPtr[3], (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));

              if ( bTmpByte == kLinSc_SendDataDump )
              {
                /* Send positive response */
                set_bScResponseBuffer(linchannel, 1, 0x06u);                   /* PCI, length 6 */
                set_bScResponseBuffer(linchannel, 0, getbLinConfiguredNAD(linchannel));  /* NAD */
                /* other data bytes are provided by the application */
              }
              else
  #endif
              {
  #if defined ( LIN_ENABLE_SLAVE_CONFIG_OPT_RESP )
                /* send negative response   */
                ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_PARA_FIRST kSID_DataDump, kScNRError_SNS);
  #endif
              }
            break;
  #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u ) 
          case 0xB5:
   #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
    #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
              if ( get_bCurrentProtocolVersion(linchannel) >= kLinProtocolCompatibility_21 )
    #endif
              { /* kSID_AssignNADviaSNPD: Assign NAD via SNPD */
    #if defined ( LIN_ENABLE_ASSIGN_NAD_VIA_SNPD_COMMAND )
                ApplLinScAssignNADviaSNPD(LIN_I_CHANNEL_PARA_FIRST &pbMsgDataPtr[0]);
                /* The response to a SNPD command depends on the method applied later - no response is transmitted here */
    #endif
              }
   #endif
            break;
  #endif
  #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
          case kSID_SaveConfiguration:
   #if defined ( LIN_ENABLE_SAVE_CONFIGURATION_COMMAND )
            /* 0xB6 Save configuration - always a positive response is provided after successful reception of this command */
    #if defined ( LIN_APISTYLE_VECTOR )
            ApplLinScSaveConfiguration(LIN_I_CHANNEL_PARA_ONLY); /* inform application to safe current configuration */
    #else
            set_bLinStatusInfo_Flags(LIN_I_CA_SL_CHANNEL_PARA_ONLY, (vuint8)(get_bLinStatusInfo_Flags(LIN_I_CA_SL_CHANNEL_PARA_ONLY) | kLinStatus_SaveConfig));
    #endif
            /* Send positive response */
            set_bScResponseBuffer(linchannel, 0, getbLinConfiguredNAD(linchannel));  /* NAD */
            /* other data bytes already set to 0xFF */
   #else
            ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_PARA_FIRST kSID_SaveConfiguration, kScNRError_SNS);
   #endif
            break;
          case kSID_AssignFrameIdRange:
            /* 0xB7 Assign frame identifier range */
   #if defined ( LIN_ENABLE_CONFIGURABLE_PID ) && (kLinNumberOfConfigurablePIDs >= 0x00u)
            for ( vLoopCount = 0; vLoopCount < 4; vLoopCount++ )
            { /* check the four provided PIDs */
              if ( pbMsgDataPtr[(vuint8)(7-vLoopCount)] != 0xFFu )
              { /* PID is not of type dont care */
                if ( (vuint8)((pbMsgDataPtr[3] + 3) - vLoopCount) >= get_LinNumberOfConfigurablePIDs(linchannel) )
                { /* PID assign offset out of configurable frame range - reject command */
                  break; /* quit loop */
                }
                else
                { /* change current PID value */
                  if ( pbMsgDataPtr[(vuint8)(7-vLoopCount)] == 0x00u )
                  { /* set current PID to unassign value */
                    get_LinSlaveProtectedIdTbl(linchannel)[get_ConfigurablePIDHandleTbl(linchannel)[(vuint8)((pbMsgDataPtr[3] + 3) - vLoopCount)]] = kLinInvalidProtectedId;
                  }
                  else
                  { /* set current PID to transmitted PID */
                    get_LinSlaveProtectedIdTbl(linchannel)[get_ConfigurablePIDHandleTbl(linchannel)[(vuint8)((pbMsgDataPtr[3] + 3) - vLoopCount)]] = pbMsgDataPtr[(vuint8)(7-vLoopCount)];
                  }
                }
              }
            }
            if (vLoopCount < 4)
            { /* invalid command - reject it */
              /* send negative response */
              ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_PARA_FIRST kSID_AssignFrameIdRange, kScNRError_SNS);
            }
            else
            { /* assign PIDs */
              /* Send positive response */
              set_bScResponseBuffer(linchannel, 0, getbLinConfiguredNAD(linchannel));    /* NAD */
              /* other data bytes already set to 0xFF */
            }
            break;
   #else
            /* send negative response */
            ScMasterReqPrecopyFct_ConfigNegResp(LIN_I_CHANNEL_PARA_FIRST kSID_AssignFrameIdRange, kScNRError_SNS);
            break;
   #endif
  #endif /* LIN_PROTOCOLVERSION_VALUE >= 0x21u */
          default:
              /* Frame is no slave configuration request can not be because of check before */
            break;
          }
        }
        else
        {
          /* node configuration service with invalid length or a different slave node is addressed - pending response already cleared */
        }
      }
      else
      {
  #if defined ( LIN_ENABLE_USER_SLAVE_CONFIG )
        /* check if SID is known */
        switch (pbMsgDataPtr[2])
        {
   #if ( kNumberOfUserSlaveConfig > 0 )
          case kUserSlaveConfigSID_0:
   #endif
   #if ( kNumberOfUserSlaveConfig > 1 )
          case kUserSlaveConfigSID_1:
   #endif
   #if ( kNumberOfUserSlaveConfig > 2 )
          case kUserSlaveConfigSID_2:
   #endif
   #if ( kNumberOfUserSlaveConfig > 3 )
          case kUserSlaveConfigSID_3:
   #endif
   #if ( kNumberOfUserSlaveConfig > 4 )
          case kUserSlaveConfigSID_4:
   #endif
   #if ( kNumberOfUserSlaveConfig > 5 )
          case kUserSlaveConfigSID_5:
   #endif
   #if ( kNumberOfUserSlaveConfig > 6 )
          case kUserSlaveConfigSID_6:
   #endif
   #if ( kNumberOfUserSlaveConfig > 7 )
          case kUserSlaveConfigSID_7:
   #endif
   #if ( kNumberOfUserSlaveConfig > 8 )
          case kUserSlaveConfigSID_8:
   #endif
   #if ( kNumberOfUserSlaveConfig > 9 )
          case kUserSlaveConfigSID_9:
   #endif
            /* User slave configuration request */
            bCount  = pbMsgDataPtr[1]; /* read PCI - check on data length [1 - 6] already done */

   #if defined ( LIN_ENABLE_FULL_NAD_RANGE )
   #else
            if ( (pbMsgDataPtr[0] == getbLinConfiguredNAD(linchannel)) || (pbMsgDataPtr[0] == kScNADWildcard) )
   #endif
            {
              /* This slave is addressed with correct length */

              bCount--; /* calculate diagnostic payload length */

              switch (pbMsgDataPtr[2])
              {
   #if ( kNumberOfUserSlaveConfig > 0 )
                case kUserSlaveConfigSID_0:
                  bTmpByte = ApplLinScUserSlaveConfig_0(LIN_I_CHANNEL_PARA_FIRST &bCount, &pbMsgDataPtr[0], (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
                  LinScUserSlaveConfigHandleSetting(LIN_I_CHANNEL_PARA_FIRST 0, bTmpByte, bCount);
                  break;
   #endif
   #if ( kNumberOfUserSlaveConfig > 1 )
                case kUserSlaveConfigSID_1:
                  bTmpByte = ApplLinScUserSlaveConfig_1(LIN_I_CHANNEL_PARA_FIRST &bCount, &pbMsgDataPtr[0], (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
                  LinScUserSlaveConfigHandleSetting(LIN_I_CHANNEL_PARA_FIRST 1, bTmpByte, bCount);
                  break;
   #endif
   #if ( kNumberOfUserSlaveConfig > 2 )
                case kUserSlaveConfigSID_2:
                  bTmpByte = ApplLinScUserSlaveConfig_2(LIN_I_CHANNEL_PARA_FIRST &bCount, &pbMsgDataPtr[0], (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
                  LinScUserSlaveConfigHandleSetting(LIN_I_CHANNEL_PARA_FIRST 2, bTmpByte, bCount);
                  break;
   #endif
   #if ( kNumberOfUserSlaveConfig > 3 )
                case kUserSlaveConfigSID_3:
                  bTmpByte = ApplLinScUserSlaveConfig_3(LIN_I_CHANNEL_PARA_FIRST &bCount, &pbMsgDataPtr[0], (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
                  LinScUserSlaveConfigHandleSetting(LIN_I_CHANNEL_PARA_FIRST 3, bTmpByte, bCount);
                  break;
   #endif
   #if ( kNumberOfUserSlaveConfig > 4 )
                case kUserSlaveConfigSID_4:
                  bTmpByte = ApplLinScUserSlaveConfig_4(LIN_I_CHANNEL_PARA_FIRST &bCount, &pbMsgDataPtr[0], (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
                  LinScUserSlaveConfigHandleSetting(LIN_I_CHANNEL_PARA_FIRST 4, bTmpByte, bCount);
                  break;
   #endif
   #if ( kNumberOfUserSlaveConfig > 5 )
                case kUserSlaveConfigSID_5:
                  bTmpByte = ApplLinScUserSlaveConfig_5(LIN_I_CHANNEL_PARA_FIRST &bCount, &pbMsgDataPtr[0], (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
                  LinScUserSlaveConfigHandleSetting(LIN_I_CHANNEL_PARA_FIRST 5, bTmpByte, bCount);
                  break;
   #endif
   #if ( kNumberOfUserSlaveConfig > 6 )
                case kUserSlaveConfigSID_6:
                  bTmpByte = ApplLinScUserSlaveConfig_6(LIN_I_CHANNEL_PARA_FIRST &bCount, &pbMsgDataPtr[0], (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
                  LinScUserSlaveConfigHandleSetting(LIN_I_CHANNEL_PARA_FIRST 6, bTmpByte, bCount);
                  break;
   #endif
   #if ( kNumberOfUserSlaveConfig > 7 )
                case kUserSlaveConfigSID_7:
                  bTmpByte = ApplLinScUserSlaveConfig_7(LIN_I_CHANNEL_PARA_FIRST &bCount, &pbMsgDataPtr[0], (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
                  LinScUserSlaveConfigHandleSetting(LIN_I_CHANNEL_PARA_FIRST 7, bTmpByte, bCount);
                  break;
   #endif
   #if ( kNumberOfUserSlaveConfig > 8 )
                case kUserSlaveConfigSID_8:
                  bTmpByte = ApplLinScUserSlaveConfig_8(LIN_I_CHANNEL_PARA_FIRST &bCount, &pbMsgDataPtr[0], (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
                  LinScUserSlaveConfigHandleSetting(LIN_I_CHANNEL_PARA_FIRST 8, bTmpByte, bCount);
                  break;
   #endif
   #if ( kNumberOfUserSlaveConfig > 9 )
                case kUserSlaveConfigSID_9:
                  bTmpByte = ApplLinScUserSlaveConfig_9(LIN_I_CHANNEL_PARA_FIRST &bCount, &pbMsgDataPtr[0], (vuint8*) &(get_bScResponseBuffer(linchannel, 3)));
                  LinScUserSlaveConfigHandleSetting(LIN_I_CHANNEL_PARA_FIRST 9, bTmpByte, bCount);
                  break;
   #endif
                default:
   #if defined ( LIN_ENABLE_DEBUG )
                  /* set variable to avoid compiler warning */
                  bTmpByte = kLinSc_WaitForUserSpecConfig;
   #endif
                  /* This default will never be reached because of switch above */
                  break;
              }

              LinAssertDynamic(LIN_I_CA_SL_CHANNEL_PARA_ONLY, (bCount <= 5) , kLinErrorScInvalidLength);
              LinAssertDynamic(LIN_I_CA_SL_CHANNEL_PARA_ONLY, ( (bTmpByte == kLinSc_SendUserSpecConfig) \
                || (bTmpByte == kLinSc_WaitForUserSpecConfig) || (bTmpByte == kLinSc_NoUserSpecConfig)  \
                || (bTmpByte == kLinSc_WrongUserSpecConfig) ) , kLinErrorScInvalidParam);
            }
   #if !defined ( LIN_ENABLE_FULL_NAD_RANGE )
            else
            {
              /* Other slave node addressed - frame filtered out, pending response already cleared */
            }
   #endif
          break;
          default:
            /* Frame is no slave configuration request */
            bRetValue = kScReqNotHandled;   /* frame not handled by Configuration API */
          break;
        }
  #else /* LIN_ENABLE_USER_SLAVE_CONFIG */
        /* Slave Configuration API not supported by setup */
        bRetValue = kScReqNotHandled;
  #endif /* LIN_ENABLE_USER_SLAVE_CONFIG */
      }
    }
  }
  else
  {
    /* No matching NAD range or frame type is not single frame. Frame not handled */
  #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
    if ((get_bCurrentProtocolVersion(linchannel) >= kLinProtocolCompatibility_21) && (get_bScResponseBuffer(linchannel, 0) != 0) && (pbMsgDataPtr[0] == 0x7Eu))
   #else
    if ((get_bScResponseBuffer(linchannel, 0) != 0) && ( pbMsgDataPtr[0] == 0x7Eu ))
   #endif
    { /* invalid functional request while physical response is pending - ignore current frame and continue with physical response transmission */
      bRetValue = kScReqIgnored;
    }
    else
  #endif
    {
      bRetValue = kScReqNotHandled;
    }
  }

 #if defined ( LIN_ENABLE_T_NODE_CONFIG_SERVICE )
  if ( get_bScResponseBuffer(linchannel, 0) != 0x00u )
  { /* Node configuration service response pending - start N_As timeout observation */
    set_NasTimerValue(linchannel, get_NasTimerInitValue(linchannel) );
  }
 #endif

  return(bRetValue);
} /* PRQA S 6030 *//* MD_LIN_METRIC_STCYC *//* PRQA S 6010 *//* MD_LIN_METRIC_STPTH *//* PRQA S 6080 *//* MD_LIN_METRIC_STMIF */ /* PRQA S 6050 *//* MD_LIN_METRIC_STCAL */
 #endif /* LIN_ENABLE_SLAVE_CONFIGURATION */
#endif /* LIN_ECUTYPE_SLAVE */


/*******************************************************************************************/
/*******************************************************************************************/
/**  GROUP: LIN Message handler                                                         ****/
/*******************************************************************************************/
/*******************************************************************************************/


#if defined ( LIN_APISTYLE_VECTOR )
 #if defined ( LIN_ENABLE_INIT_RX_DEFAULT_DATA )   || \
     defined ( LIN_ENABLE_START_RX_DEFAULT_DATA )  || \
     defined ( LIN_ENABLE_STOP_RX_DEFAULT_DATA )
/*******************************************************************************************/
/*    FUNCTION:  LinSetRxDefaultValues                                                     */
/*******************************************************************************************/
/**
 *   @brief   Set Default values of all Rx messages
 *
 *            This function copies the default data to all received messages.
 *
 *   @param   none
 *
 *   @return  none
 *
 *   @note    Function called during initialization, wakeup and sleep if option is enabled.
 *
 *******************************************************************************************/
/* CODE CATEGORY 2 START*/
static void LinSetRxDefaultValues(LIN_I_CHANNEL_TYPE_ONLY)
{
  #if ( kLinNumberOfRxObjects > 0 )

  tLinFrameHandleLoopType vLoopCount;

  for ( vLoopCount = (tLinFrameHandleLoopType)get_LinRxMsgBaseIndex(linchannel); vLoopCount < ((tLinFrameHandleLoopType)(get_LinRxMsgBaseIndex(linchannel)+get_LinNumberOfChRxObjects(linchannel))); vLoopCount++ )
  {
    /* Initialize message buffers of Rx messages to default values */
    if ( get_LinRxTxMsgDataPtr(linchannel)[vLoopCount] != (tLinMsgDataPtrType)0 )
    {
      VStdMemCpyRomToRam(get_LinRxTxMsgDataPtr(linchannel)[vLoopCount], get_LinRxTxDefaultDataPtrTbl(linchannel)[vLoopCount], get_kLinRxBufferLength(linchannel, vLoopCount));
    }
  }
  #endif
}
/* CODE CATEGORY 2 END*/
 #endif

 #if defined ( LIN_ENABLE_INIT_TX_DEFAULT_DATA )   || \
     defined ( LIN_ENABLE_START_TX_DEFAULT_DATA )  || \
     defined ( LIN_ENABLE_STOP_TX_DEFAULT_DATA )
/*******************************************************************************************/
/*    FUNCTION:  LinSetTxDefaultValues                                                     */
/*******************************************************************************************/
/**
 *   @brief   Set Default values of all Tx messages
 *
 *            This function copies the default data to all transmitted messages.
 *
 *   @param   none
 *
 *   @return  none
 *
 *   @note    Function called during initialization, wakeup and sleep if option is enabled.
 *
 *******************************************************************************************/
/* CODE CATEGORY 2 START*/
static void LinSetTxDefaultValues(LIN_I_CHANNEL_TYPE_ONLY)
{
  #if ( kLinNumberOfTxObjects > 0 )

  tLinFrameHandleLoopType vLoopCount;

  for ( vLoopCount = (tLinFrameHandleLoopType)get_LinTxMsgBaseIndex(linchannel); vLoopCount < ((tLinFrameHandleLoopType)(get_LinTxMsgBaseIndex(linchannel)+get_LinNumberOfChTxObjects(linchannel))); vLoopCount++ )
  {
    /* Initialize message buffers of Tx messages to default values */
    if ( get_LinRxTxMsgDataPtr(linchannel)[vLoopCount] != (tLinMsgDataPtrType)0 )
    {
      VStdMemCpyRomToRam(get_LinRxTxMsgDataPtr(linchannel)[vLoopCount], (get_LinRxTxDefaultDataPtrTbl(linchannel)[vLoopCount]), get_LinRxTxMsgInfo(linchannel)[vLoopCount].MsgDataLength);
    }
  }
  #endif
}
/* CODE CATEGORY 2 END*/
 #endif

 #if defined ( LIN_ECUTYPE_SLAVE )
/*******************************************************************************************/
/*    FUNCTION:  LinDoSleepModeHandling                                                    */
/*******************************************************************************************/
/**
 *   @brief   If a sleep condition has been detected the driver is performing state transitions
 *
 *   @param   none
 *
 *   @return  none
 *
 *   @note    Function called during transition to sleep mode.
 *
 *******************************************************************************************/
static void LinDoSleepModeHandling(LIN_I_CHANNEL_TYPE_ONLY)
{
  set_bNmNetworkState(linchannel, kNmBusSleep);
  #if defined ( LIN_ENABLE_T_BUS_IDLE )
  /* Cancel Bus idle observation */
  CancelNmBusIdleTimer(linchannel);
  #endif
  /* Inform Application */
  ApplLinBusSleep(LIN_I_CHANNEL_PARA_ONLY);

  #if defined ( LIN_ENABLE_STOP_RX_DEFAULT_DATA )
  LinSetRxDefaultValues(LIN_I_CHANNEL_PARA_ONLY);
  #endif
  #if defined ( LIN_ENABLE_STOP_TX_DEFAULT_DATA )
  LinSetTxDefaultValues(LIN_I_CHANNEL_PARA_ONLY);
  #endif

  /* Enable frame processor to receive Wakeup frames */
  FpResetMuteMode(LIN_I_CHANNEL_PARA_ONLY);
}

/*******************************************************************************************/
/*    FUNCTION:  LinDoWakeupHandling                                                       */
/*******************************************************************************************/
/**
 *   @brief   If a wake up has been detected the driver is performing state transitions
 *
 *   @param   none
 *
 *   @return  none
 *
 *   @note    Function called during transition to wake state.
 *
 *******************************************************************************************/
static void LinDoWakeupHandling(LIN_I_CHANNEL_TYPE_ONLY)
{
  #if defined ( LIN_ENABLE_LINSTART_WAKEUP_INTERNAL )
  if ( (get_bNmNetworkState(linchannel) == kNmBusSleep) || \
       (get_bNmNetworkState(linchannel) == kNmWaitForWakeupFrmConf) )
  #else
  if ( get_bNmNetworkState(linchannel) == kNmBusSleep )
  #endif
  { /* Set NmState */
    set_bNmNetworkState(linchannel, kNmAwakeWaitforWakeupConf);
    /* Handling of wakeup signal indication/confirmation */

  #if defined ( LIN_ENABLE_START_RX_DEFAULT_DATA )
    LinSetRxDefaultValues (LIN_I_CHANNEL_PARA_ONLY);
  #endif
  #if defined ( LIN_ENABLE_START_TX_DEFAULT_DATA )
    LinSetTxDefaultValues (LIN_I_CHANNEL_PARA_ONLY);
  #endif

    /* Inform application about wakeup event */
    ApplLinWakeUp(LIN_I_CHANNEL_PARA_ONLY);
  }
}
 #endif /* LIN_ECUTYPE_SLAVE */

#endif /* LIN_APISTYLE_VECTOR */

#if defined ( LIN_ENABLE_T_BUS_IDLE ) || defined ( SIO_LL_BUS_IDLE_IND ) || defined (SIO_LL_ENABLE_T_BUS_IDLE_BY_HARDWARE)
/*******************************************************************************************/
/*    FUNCTION:  LinDoBusIdleHandling                                                       */
/*******************************************************************************************/
/**
 *   @brief   If a bus idle condition is detected the driver is performing state transitions 
 *            and notifying the application accordingly
 *
 *   @param   none
 *
 *   @return  none
 *
 *   @note    Function called during transition to wake state.
 *
 *******************************************************************************************/
static void LinDoBusIdleHandling(LIN_I_CHANNEL_TYPE_ONLY)
{
  
 #if defined ( LIN_ECUTYPE_SLAVE )
  /* Signalize error to application. No bus transitions observed */
  #if defined ( LIN_APISTYLE_VECTOR )
   #if defined ( LIN_ENABLE_NO_BUS_ACTIVITY )
  ApplLinProtocolError(LIN_I_CHANNEL_PARA_FIRST kLinNoBusActivity, kMsgHandleDummy);
   #endif
  /* Sleep mode handling */
  LinDoSleepModeHandling(LIN_I_CHANNEL_PARA_ONLY);
  #else
  /* When bus idle is detected by the hardware we have to inform the application accordingly - not appropriate status bit defined in the status word */
  ApplLinProtocolError(LIN_I_CHANNEL_PARA_FIRST kLinNoBusActivity, kMsgHandleDummy);
  #endif
 #endif
}
#endif

/*******************************************************************************************/
/*    FUNCTION:  ApplFpWakeupIndication                                                    */
/*******************************************************************************************/
/** @brief  Indication of a wakeup request by the frame processor
*
 *          The callback function is called by the frame processor, when the current
 *          state is "waiting for wakeup frame indication" or "waiting for wakeup frame
 *          confirmation" and a wakeup signal is received.
 *
 *  @param_i channel The interface/channel which detected the wakeup signal
 *  @return void     No return value
 *
 *  @note   Call context is UART Interrupt
 *******************************************************************************************/
/* CODE CATEGORY 1 START*/
static void ApplFpWakeupIndication(LIN_I_CHANNEL_TYPE_ONLY)
{
#if defined ( LIN_APISTYLE_LIN )
  #if defined ( LIN_ECUTYPE_SLAVE )
   #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
  set_bLinStatusInfo_Flags(linchannel, (vuint8)(get_bLinStatusInfo_Flags(linchannel) | kLinStatus_BusActivity));
   #endif
  #endif
  ApplLinWakeupRequest(LIN_I_CHANNEL_PARA_ONLY);

#else /* LIN_APISTYLE_LIN */

 #if defined ( LIN_ECUTYPE_SLAVE )
  /*******************************************************************************************/
  /* Handling of Wakeup frame                                   */
  /*******************************************************************************************/
  LinDoWakeupHandling(LIN_I_CHANNEL_PARA_ONLY);
 #endif /* LIN_ECUTYPE_SLAVE */
#endif /* LIN_APISTYLE_LIN */
}
/* CODE CATEGORY 1 END*/

/*******************************************************************************************/
/*    FUNCTION:  ApplFpHeaderIndication                                                    */
/*******************************************************************************************/
/** @brief  Indication of the end of a header transmission or reception
*
*           The callback function is called by the frame processor, when a header has
*           been successfully transmitted (master) or successfully received (slave).
*           The type of message assigned to the header is checked here and the response
*           is configured corresponding to the message type.
*
*   @param  bProtectedId   The protected identifier of the header
*   @return void           No return value
*
*   @note   Call context is UART Interrupt
********************************************************************************************/

/* CODE CATEGORY 1 START*/
static void ApplFpHeaderIndication(LIN_I_CHANNEL_TYPE_FIRST vuint8 bProtectedId)
{
#if defined ( LIN_ECUTYPE_SLAVE )
  tLinFrameHandleLoopType bLoopcount;
 #if defined ( LIN_ENABLE_ET_TX_FRAMES )
  tLinFrameHandleType     bTmpIndex;
 #endif
 #if defined ( LIN_ENABLE_MSGRESPONSE_FCT ) || defined ( LIN_ENABLE_DIAGFRAME_BY_APPL ) || defined ( LIN_ENABLE_DIAG_TRANSP_LAYER ) || defined ( LIN_ENABLE_XCPONLIN )
  vuint8                  retvalue;
 #endif
#endif

  tLinFrameHandleType tempCurFrameHandle;
  tMessageInfoType    tempMessageInfo = {0,0,kMessageDirectionIgnore,0};


#if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  bProtectedId = bProtectedId;  /* Avoid compiler warning */
#endif

#if defined ( LIN_ECUTYPE_SLAVE )
  if ( bProtectedId == 0x3Cu )
  {
    /* Handling of master request frame */
    /* Save handle in local message buffer for indication handling */
    tempCurFrameHandle  = get_MasterReqHandle(linchannel);
  }
 #if defined ( LIN_ENABLE_DIAG_FRAMES )
  #if defined (SIO_LL_ID_FORMAT_RAW)
  else if ( bProtectedId == 0x3Du )
  #else
  else if ( bProtectedId == 0x7Du )
  #endif
  {
    /* Handling of Slave Response Frame */
    /* Save handle in local message buffer for indication handling */
    tempCurFrameHandle  = get_SlaveRespHandle(linchannel);
  }
 #endif
  else
  {
    /* Set handle to invalid handle */
    tempCurFrameHandle  = kLinInvalidHandle;
    if ( bProtectedId != kLinInvalidProtectedId )
    {
      /* Check whether the protected ID is in the ID list */
      /* Protected ID must be different to kLinInvalidProtectedId. Is an invalid ID and used as invalid flag. */
      /* Search is performed back wards, to first check the tx messages. */
 #if ( kLinNumberOfConfigurablePIDs > 1 )
  #if defined ( LIN_ENABLE_MULTI_ECU_CONFIG )
      bLoopcount  = get_LinNumberOfIdObjects(linchannel);
  #else
      bLoopcount  = get_LinNumberOfConfigurablePIDs(linchannel);
  #endif
      while ( bLoopcount > 0 )
      {
        bLoopcount--;
  #if defined (SIO_LL_ID_FORMAT_RAW)
        /* check for matching ID and that the current RAM value is not the kLinInvalidProtectedId */
        if (   ( (0x3Fu & get_LinSlaveProtectedIdTbl(linchannel)[bLoopcount]) == bProtectedId )
            && ( (get_LinSlaveProtectedIdTbl(linchannel)[bLoopcount]) != kLinInvalidProtectedId ) )
  #else
        if ( get_LinSlaveProtectedIdTbl(linchannel)[bLoopcount] == bProtectedId )
  #endif
        {
          /* ID is processed by the node. The index is the current handle */
          tempCurFrameHandle  = (tLinFrameHandleType)bLoopcount;
          break;
        }
      }
 #elif ( kLinNumberOfConfigurablePIDs == 1 )
  #if defined (SIO_LL_ID_FORMAT_RAW)
      /* check for matching ID and that the current RAM value is not the kLinInvalidProtectedId */
      if (   ( (0x3Fu & get_LinSlaveProtectedIdTbl(linchannel)[0]) == bProtectedId )
          && ( (get_LinSlaveProtectedIdTbl(linchannel)[0]) != kLinInvalidProtectedId ) )
  #else
      if ( get_LinSlaveProtectedIdTbl(linchannel)[0] == bProtectedId )
  #endif
      {
          tempCurFrameHandle  = 0;
      }
 #endif
    }
    else
    {
      /* no search performed, because kLinInvalidProtectedId is used as invalid Protected id */
    }
  }

 #if defined (SIO_LL_ID_FORMAT_RAW)
  /* paritiy error must be detected by low level driver */
 #else
 #endif

  /* store tempCurFrameHandle into global variable */
  set_pbMhMsgBuffer_FrmHandle(linchannel, tempCurFrameHandle);

 #if defined ( LIN_ENABLE_HEADER_NOTIFICATION )
  /* When enabled, the reception of an identifier field can be notified to the application */
  #if defined ( kLinHeaderNotificationHandle )
  if ( tempCurFrameHandle == kLinHeaderNotificationHandle )
  #endif
  {
    /* notification is called only for the specified handle */
    ApplLinHeaderDetection(LIN_I_SL_CHANNEL_PARA_FIRST tempCurFrameHandle);
  }
 #endif
  /* Handling of header corresponding to the saved slot handle */

#endif /* LIN_ECUTYPE_SLAVE */


#if defined ( LIN_ECUTYPE_SLAVE )
  if ( tempCurFrameHandle == kLinInvalidHandle )
  {
    /* unknown protected ID. Ignore the response. */
  }
  else
  {
    /* Get message info (id, direction and checksum type) and save it */
 #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
    tempMessageInfo = get_cabLinRxTxMsgInfoRam(linchannel)[tempCurFrameHandle];
 #else
    tempMessageInfo = get_LinRxTxMsgInfo(linchannel)[tempCurFrameHandle];
 #endif
    /*******************************************************************************************/
    /*  Handling of Rx messages and Tx messages                                                */
    /*******************************************************************************************/
    if ( tempCurFrameHandle < get_LinNumberOfRxTxObjects(linchannel) )
    {
      if ( tempMessageInfo.MsgDirection == kMessageDirectionTx )
      {
 #if defined ( LIN_ENABLE_XCPONLIN )
        /* ESCAN00016382 */
        if ( tempCurFrameHandle == LinGetXcpTransmitHandle(LIN_I_CHANNEL_PARA_ONLY) )
        {
          /* Forward to XcpOnLin component if frame response of Xcp Response shall be send */
          retvalue = ApplLinXcpResponseFct(LIN_I_CHANNEL_PARA_ONLY);
        }
        else
 #endif
        {
 #if defined ( LIN_ENABLE_MSGRESPONSE_FCT )
          /* Inform application about received header, it has to decide if message response shall be send */
          retvalue = ApplLinFrameResponseFct(LIN_I_CHANNEL_PARA_FIRST tempCurFrameHandle);
 #else
  #if defined ( LIN_ENABLE_XCPONLIN )
          retvalue = kLinFrameRespConfirm;
  #endif
 #endif
        }

 #if defined ( LIN_ENABLE_MSGRESPONSE_FCT ) || defined ( LIN_ENABLE_XCPONLIN )
        if ( retvalue == kLinFrameRespReject )
        {
          /* ignore response */
          tempMessageInfo.MsgDirection  = kMessageDirectionIgnore;
        }
        else
 #endif
        {
 #if defined ( LIN_ENABLE_ET_TX_FRAMES )
          /* Get index of the handle within the event triggered Tx objects */
          bTmpIndex = (tLinFrameHandleType)(tempCurFrameHandle-(get_LinNumberOfRxObjects(linchannel) + get_LinNumberOfEtRxObjects(linchannel)));

          if ( bTmpIndex < get_LinNumberOfEtTxObjects(linchannel))
          {
            /* Handling of clearing the event triggered frame pending flag moved to Header indication */

            /* Store Currently worked on Byte */
  #if ( kLinNumberOfEtTxObjects <= 8 )
            /* if only 1 - 8 flags are available offset is always 0 */
            set_bLinETFStoreFlag(linchannel, (get_LinETFUpdateFlags(linchannel))._c[0]);
            /* Clear Flag */
            (get_LinETFUpdateFlags(linchannel))._c[0] &= (vuint8)~get_LinETFUpdateFlagMask(linchannel)[bTmpIndex];
  #else
            set_bLinETFStoreFlag(linchannel, (get_LinETFUpdateFlags(linchannel))._c[get_LinETFUpdateFlagOffset(linchannel)[bTmpIndex]]);
            /* Clear Flag */
            (get_LinETFUpdateFlags(linchannel))._c[get_LinETFUpdateFlagOffset(linchannel)[bTmpIndex]] &= (vuint8)~get_LinETFUpdateFlagMask(linchannel)[bTmpIndex];
  #endif
          }
 #endif
          /* Event triggered frames are no tx messages of the master */

          /*lint -e661*/
          /* Disable PC-lint warning 661: "Possible creation of out-of-bounds pointer" */
          /*lint -e662*/
          /* Disable PC-lint warning 662: "Possible access of out-of-bounds pointer" */
          /*
          Warning are shown by PC-lint if event triggered frames are used, a problem does not occur because
          the values that would lead to an error are filtered out be the tx message check above.
          */
 #if defined ( LIN_ENABLE_MSG_PRETRANSMIT_FCT )
  #if defined ( V_ENABLE_USE_DUMMY_FUNCTIONS )
          /* Dummy function used when no user defined pretransmit function is used. No check required */
  #else
          /*lint -e611*/
          /* Disable PC-lint warning 611: "Suspicious cast" */
          /* Cast of null pointer used to avoid compiler warning */
          if ( (tApplLinMsgPretransmitFct)V_NULL != get_LinTxApplMsgPretransmitFctTbl(linchannel)[tempCurFrameHandle - get_LinNumberOfRxObjects(linchannel)] )
            /* Enable PC-lint warning 611: "Suspicious cast" */
            /*lint +e611*/
  #endif
          {
            /* Call pretransmit function */
            if ( (get_LinTxApplMsgPretransmitFctTbl(linchannel)[tempCurFrameHandle - get_LinNumberOfRxObjects(linchannel)]) \
              (LIN_I_CHANNEL_PARA_FIRST get_pbMhMsgBuffer_BufferPointer(linchannel)) == kLinNoCopyData_i )
            {
              goto LABEL_SKIP_PRETRANSMIT_HANDLING; /* Sorry, but this way allows to avoid double code */ /* PRQA S 2001 *//* MD_LIN_DRV_14.4 */
            }
          }
 #endif /* LIN_ENABLE_MSG_PRETRANSMIT_FCT */
 #if defined ( LIN_ENABLE_UNC_TX_FRAMES )
          if ( get_LinRxTxMsgDataPtr(linchannel)[tempCurFrameHandle] != (tLinMsgDataPtrType)0 )
          {
            /* copy n data bytes from the message buffer to the local message buffer */
            VStdMemCpyRamToRam(get_pbMhMsgBuffer_BufferPointer(linchannel), get_LinRxTxMsgDataPtr(linchannel)[tempCurFrameHandle], tempMessageInfo.MsgDataLength);
          }
 #endif
          /* Enable PC-lint warning 662: "Possible access of out-of-bounds pointer" */
          /*lint +e662*/
          /* Enable PC-lint warning 661: "Possible creation of out-of-bounds pointer" */
          /*lint +e661*/
 #if defined ( LIN_ENABLE_ET_TX_FRAMES )
          if ( bTmpIndex < get_LinNumberOfEtTxObjects(linchannel))
          {
            /* protected id of the assigned frame must be rewritten */
            get_pbMhMsgBuffer_BufferPointer(linchannel)[0] = get_LinSlaveProtectedIdTbl(linchannel)[(tLinFrameHandleType)(bTmpIndex + get_LinNumberOfRxObjects(linchannel))];
          }
 #endif
 #if defined ( LIN_ENABLE_MSG_PRETRANSMIT_FCT )
LABEL_SKIP_PRETRANSMIT_HANDLING:;
 #endif

        /* Call response configuration of Frame processor */
        }
      }
    }

    /*******************************************************************************************/
    /*  Handling of event triggered frames                                                     */
    /*******************************************************************************************/
 #if defined ( LIN_ENABLE_ET_TX_FRAMES )
    else if ( tempCurFrameHandle < get_LinNumberOfIdObjects(linchannel) )
    {
      if ( tempMessageInfo.MsgDirection == kMessageDirectionTx )
      {
  #if defined ( LIN_ENABLE_MSGRESPONSE_FCT )
        retvalue = ApplLinFrameResponseFct(LIN_I_CHANNEL_PARA_FIRST tempCurFrameHandle);

        if ( retvalue == kLinFrameRespReject )
        {
          /* reject response */
          tempMessageInfo.MsgDirection  = kMessageDirectionIgnore;
        }
        else
  #endif
        {
          /* Get index of the handle within the event triggered Tx objects */
          bTmpIndex = (tLinFrameHandleType)(tempCurFrameHandle-(get_LinNumberOfRxTxObjects(linchannel) + get_LinNumberOfEtRxObjects(linchannel)));
          /* Handling of header of an event triggered frame. Check assigned frame for new data */
  #if ( kLinNumberOfEtTxObjects <= 8 )
            /* if only 1 - 8 flags are available offset is always 0 */
          if ( ((get_LinETFUpdateFlags(linchannel))._c[0] & get_LinETFUpdateFlagMask(linchannel)[bTmpIndex]) != 0 )
  #else
          if ( ((get_LinETFUpdateFlags(linchannel))._c[get_LinETFUpdateFlagOffset(linchannel)[bTmpIndex]] & get_LinETFUpdateFlagMask(linchannel)[bTmpIndex]) != 0 )
  #endif
          {
            /* Transmission of assigned frame is pending */
            /* pretransmit function is not called */

            /* Store currently worked on byte */
  #if ( kLinNumberOfEtTxObjects <= 8 )
            /* if only 1 - 8 flags are available offset is always 0 */

            set_bLinETFStoreFlag(linchannel, (get_LinETFUpdateFlags(linchannel))._c[0]);
            /* Clear Flag */
            (get_LinETFUpdateFlags(linchannel))._c[0]  &= (vuint8)~get_LinETFUpdateFlagMask(linchannel)[bTmpIndex];
  #else
            set_bLinETFStoreFlag(linchannel, (get_LinETFUpdateFlags(linchannel))._c[get_LinETFUpdateFlagOffset(linchannel)[bTmpIndex]]);
            /* Clear Flag */
            (get_LinETFUpdateFlags(linchannel))._c[get_LinETFUpdateFlagOffset(linchannel)[bTmpIndex]] &= (vuint8)~get_LinETFUpdateFlagMask(linchannel)[bTmpIndex];
  #endif

  #if defined ( LIN_ENABLE_UNC_TX_FRAMES )
            if ( get_LinRxTxMsgDataPtr(linchannel)[(tLinFrameHandleType)(bTmpIndex + get_LinNumberOfRxObjects(linchannel))] != (tLinMsgDataPtrType)0 )
            {
              /* copy n data bytes from the message buffer to the local message buffer */
              VStdMemCpyRamToRam(get_pbMhMsgBuffer_BufferPointer(linchannel), get_LinRxTxMsgDataPtr(linchannel)[(tLinFrameHandleType)(bTmpIndex + get_LinNumberOfRxObjects(linchannel))], tempMessageInfo.MsgDataLength);
            }
  #endif
            /* protected id of the assigned frame must be rewritten */
            get_pbMhMsgBuffer_BufferPointer(linchannel)[0] = get_LinSlaveProtectedIdTbl(linchannel)[(tLinFrameHandleType)(bTmpIndex + get_LinNumberOfRxObjects(linchannel))];

            /* Handle of event triggered frame is kept until checksum confirmation. */
          }
          else
          {
            /* Assigned frame has no new data. Ignore frame */
            tempMessageInfo.MsgDirection = kMessageDirectionIgnore;
          }
        }
      }
    }
 #endif /* LIN_ENABLE_ET_TX_FRAMES */

 #if defined ( LIN_ENABLE_DIAG_FRAMES )
    /*****************************************************************************************/
    /*  Handling of diagnostic frames                                                        */
    /*****************************************************************************************/
    else if ( tempCurFrameHandle < get_LinNumberOfMsgInfoObjects(linchannel) ) /* PRQA S 3355, 3358 *//* MD_LIN_DRV_13.7 */
    {
      if ( tempMessageInfo.MsgDirection == kMessageDirectionTx )
      {
        /* Transmission of SlaveResp frame */
        switch (get_bDdDispatcherTxState(linchannel))
        {
  #if defined ( LIN_ENABLE_DIAGFRAME_BY_APPL )
        case (vuint16)kDdDiagFrmUser_None:
          retvalue  = ApplLinConfirmDiagFrameResp(LIN_I_CHANNEL_PARA_ONLY);
          if ( retvalue == kLinFrameRespConfirm )
          {
            /* call Pretransmit function */
   #if defined ( LIN_ENABLE_DIAGMSG_PRETRANSMIT_FCT )
            /* Test if function is available not needed, if LIN_ENABLE_DIAGMSG_INDICATION_FCT set then function in slave available */
            /* Call pretransmit function */
            if ( (get_LinTxDiagMsgPretransmitFctTbl(linchannel)[0])
              (LIN_I_CHANNEL_PARA_FIRST get_pbMhMsgBuffer_BufferPointer(linchannel)) == kLinNoCopyData_i )
            {
              goto LABEL_SKIP_DIAG_PRETRANSMIT_HANDLING; /* Sorry, but this way allows to avoid double code */ /* PRQA S 2001 *//* MD_LIN_DRV_14.4 */
            }
   #endif /* LIN_ENABLE_MSG_PRETRANSMIT_FCT */
            if ( get_pbLinSlaveRespMsgDataPtr(linchannel) != (tLinMsgDataPtrType)0 )
            {
              /* copy 8 data bytes from the message buffer to the local message buffer */
              VStdMemCpyRamToRam(get_pbMhMsgBuffer_BufferPointer(linchannel), get_pbLinSlaveRespMsgDataPtr(linchannel), 8);
            }

   #if defined ( LIN_ENABLE_DIAGMSG_PRETRANSMIT_FCT )
LABEL_SKIP_DIAG_PRETRANSMIT_HANDLING:;
   #endif
          }
          else
          {
            /* Ignore frame response */
            tempMessageInfo.MsgDirection = kMessageDirectionIgnore;
          }
          break;
  #endif /* LIN_ENABLE_DIAGFRAME_BY_APPL */

  #if defined ( LIN_ENABLE_SLAVE_CONFIGURATION )
        case (vuint16)kDdDiagFrmUser_SlaveConfig:
          if ( get_bScResponseBuffer(linchannel, 0) != 0x00u )
          {
   #if defined ( LIN_ENABLE_USER_SLAVE_CONFIG )
            if ( get_bScResponseBuffer(linchannel, 0) >= kUserSlaveConfigurationReserve )
            {
              /* Ignore frame response, but keep bDdDispatcherTxState for pending answer */
              tempMessageInfo.MsgDirection  = kMessageDirectionIgnore;
            }
            else
   #endif
            {
              /* Response has been set by slave configuration. Perform pretransmit handling  */
              VStdMemCpyRamToRam(get_pbMhMsgBuffer_BufferPointer(linchannel), (vuint8*) &get_bScResponseBuffer(linchannel, 0), 8);

              /* DiagFrmUser SlaveConfig will be cleared in ApplFpResponseNotification */
            }
          }
          else
          {
            /* Ignore frame response */
            tempMessageInfo.MsgDirection  = kMessageDirectionIgnore;
          }
          break;
  #endif

  #if defined ( LIN_ENABLE_DIAG_TRANSP_LAYER )
        case (vuint16)kDdDiagFrmUser_LinTp_S:
          /* Request transport layer, whether a response should be send */
          retvalue  = ApplLinDtlConfirmDiagFrameResp(LIN_I_CHANNEL_PARA_ONLY);
          if ( retvalue == kLinTpFrameRespConfirm )
          { /* Handle frame */
            ApplLinDtlPretransmitFct(LIN_I_CHANNEL_PARA_FIRST get_pbMhMsgBuffer_BufferPointer(linchannel));
          }
          else
          {
            /* Ignore frame response */
            tempMessageInfo.MsgDirection = kMessageDirectionIgnore;
          }
          break;
  #endif
        default:
          /* Unexpected state of vDdDispatcherState_User */
          /* Ignore frame response */
          tempMessageInfo.MsgDirection = kMessageDirectionIgnore;
          break;
        }
      }
    }
 #endif /* LIN_ENABLE_DIAG_FRAMES */
    else
    { /* PRQA S 3201 *//* MD_LIN_DRV_14.1 */
    }
  }

  /* Request response handling for the current frame */
  FpConfigureResponse(LIN_I_CHANNEL_PARA_FIRST tempMessageInfo);
#endif /* LIN_ECUTYPE_SLAVE */


#if defined ( LIN_APISTYLE_VECTOR )
 #if defined ( SIO_LL_APISTYLE_MESSAGE ) && defined ( SIO_LL_APITYPE_MESSAGE_IND )
  /* ApplFpHeaderIndication called directly in FpSendHeader to perform pretransmit handling */
  /* The call is no confirmation of a bus activity. */
 #else
  if ( get_bNmNetworkState(linchannel) == kNmAwakeWaitforWakeupConf )
  {
    /* Waiting for a wakeup confirmation by the reception of a synch pattern */
    CancelNmWupTimer(linchannel);
    Cancel_bNmNoWupDelayTimer(linchannel);

    set_bNmNetworkState(linchannel,kNmBusAwake);
  }
 #endif
#endif
}  /* PRQA S 6030 *//* MD_LIN_METRIC_STCYC */ /* PRQA S 6010 *//* MD_LIN_METRIC_STPTH */ /* PRQA S 6080 *//* MD_LIN_METRIC_STMIF */
/* CODE CATEGORY 1 END*/

/*******************************************************************************************/
/*    FUNCTION:  ApplFpResponseNotification                                                */
/*******************************************************************************************/
/**
 *   @brief   Handling of a successfully received or transmitted message
 *
 *            The callback function is called by the frame processor, when a response has
 *            been successfully transmitted or successfully received.
 *            For receive messages, a precopy handling is performed.
 *
 *
 *   @param_i channel The interface/channel which received or transmitted the response
 *
 *   @param   bMsgDirection The direction of the message (Tx or Rx)
 *
 *   @return  No return value
 *
 *   @note    Call context is UART Interrupt
 *
 *******************************************************************************************/

/* CODE CATEGORY 1 START*/
static void ApplFpResponseNotification(LIN_I_CHANNEL_TYPE_FIRST LIN_I_PROTECTED_ID_TYPE vuint8 bMsgDirection)
{
  vuint8*             pbTmpCurMsgPointer;
  tLinFrameHandleType tempCurFrameHandle;

#if defined ( LIN_ECUTYPE_SLAVE ) && defined ( LIN_ENABLE_DIAG_FRAMES )
 #if defined ( LIN_ENABLE_DIAG_TRANSP_LAYER ) || \
     defined ( LIN_ENABLE_SLAVE_CONFIGURATION )
  vuint8              bTmpDiagFrmHandled;
 #endif
#endif
#if defined ( LIN_ECUTYPE_SLAVE )
 #if defined ( LIN_ENABLE_RESP_ERR_IN_N_FRAMES )
  vuint8              bTmpIndex;
 #endif
 #if defined ( LIN_ENABLE_SLEEP_COMMAND_REPETITION )
  vuint8              bSleepCommandIndication;

  bSleepCommandIndication = 0;
 #endif
#endif


#if defined ( SIO_LL_APISTYLE_MESSAGE ) && defined ( SIO_LL_APITYPE_MESSAGE_IND )
 #if defined ( LIN_APISTYLE_VECTOR )
  if ( get_bNmNetworkState(linchannel) == kNmAwakeWaitforWakeupConf )
  {
    /* Waiting for a wakeup confirmation by the reception of a synch pattern */
    CancelNmWupTimer(linchannel);
    Cancel_bNmNoWupDelayTimer(linchannel);
    set_bNmNetworkState(linchannel,kNmBusAwake);
  }
 #endif
#endif

  /* local pointer is used because for LIN Master the pointer depends on the channel */
  pbTmpCurMsgPointer  = get_pbMhMsgBuffer_BufferPointer(linchannel);
  tempCurFrameHandle  = get_pbMhMsgBuffer_FrmHandle(linchannel);

#if defined ( LIN_APISTYLE_LIN )
  /* Set last protected Id, successful transfer and if necessary, overrun */
  set_bLinStatusInfo_LastPid(linchannel, bProtectedId);
  if ( (get_bLinStatusInfo_Flags(linchannel) & (kLinStatus_RxTxSuccess | kLinStatus_ResponseError)) != 0 )
  {
    /* Successful transfer of Error in response already set. Overrun condition */
    set_bLinStatusInfo_Flags(linchannel, (vuint8)(get_bLinStatusInfo_Flags(linchannel) | kLinStatus_Overrun));
  }
  #if defined ( LIN_ECUTYPE_SLAVE ) && ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
  set_bLinStatusInfo_Flags(linchannel, (vuint8)(get_bLinStatusInfo_Flags(linchannel) | kLinStatus_RxTxSuccess | kLinStatus_BusActivity));
  #else
  set_bLinStatusInfo_Flags(linchannel, (vuint8)(get_bLinStatusInfo_Flags(linchannel) | kLinStatus_RxTxSuccess));
  #endif
#endif


/*******************************************************************************************/
/*   Handling of all Rx Messages                                                           */
/*******************************************************************************************/
  if ( bMsgDirection == kMessageDirectionRx )
  {
    /* Indication of a receive (Rx) message received */

    if ( tempCurFrameHandle < get_LinNumberOfIdObjects(linchannel) )
    {
      /* Message is Unconditional frame or Event triggered frame (Master) */
#if ( kLinNumberOfIdObjects > 0 )
/*******************************************************************************************/

      /* perform now precopy handling */
 #if defined ( LIN_ENABLE_MSG_PRECOPY_FCT )

      /*lint -e661*/
      /* Disable PC-lint warning 661: "Possible creation of out-of-bounds pointer" */
      /*lint -e662*/
      /* Disable PC-lint warning 662: "Possible access of out-of-bounds pointer" */
      /*
         Warning are shown by PC-lint if event triggered frames are used, a problem does not occur because
         the values that would lead to an error is set to new values during handling of event triggered frame.
         If no new value is found during handling of event triggered frame, this code is skipped with 'goto'.
      */

  #if defined ( V_ENABLE_USE_DUMMY_FUNCTIONS )
      /* Dummy function used when no user defined precopy function is used. no check required */
  #else
      /*lint -e611*/
      /* Disable PC-lint warning 611: "Suspicious cast" */
      /* Cast of null pointer used to avoid compiler warning */
      if ( (tApplLinMsgPrecopyFct) V_NULL != get_LinRxApplMsgPrecopyFctTbl(linchannel)[tempCurFrameHandle] )
      /* Enable PC-lint warning 611: "Suspicious cast" */
      /*lint +e611*/
  #endif
      {
        /* Call precopy function for slave task */
        if ( (get_LinRxApplMsgPrecopyFctTbl(linchannel)[tempCurFrameHandle])(LIN_I_CHANNEL_PARA_FIRST pbTmpCurMsgPointer)
              == kLinNoCopyData_i )
        {
          goto LABEL_SKIP_INDICATION_HANDLING; /* Sorry, but this way allows to avoid double code */ /* PRQA S 2001 *//* MD_LIN_DRV_14.4 */
        }
      }
      /* Enable PC-lint warning 662: "Possible access of out-of-bounds pointer" */
      /*lint +e662*/
      /* Enable PC-lint warning 661: "Possible creation of out-of-bounds pointer" */
      /*lint +e661*/
 #endif /* LIN_ENABLE_MSG_PRECOPY_FCT */

      /* Request indication handling when not skipped by return value "kLinNoCopyData" */
 #if defined ( LIN_ECUTYPE_SLAVE )
/*******************************************************************************************/
/* Indication handling of unconditional Rx messages                                        */
/*******************************************************************************************/
  #if ( kLinNumberOfRxObjects > 0 )
      /* copy message data to message buffer */
      if ( get_LinRxTxMsgDataPtr(linchannel)[tempCurFrameHandle] != (tLinMsgDataPtrType)0 )
      {
        VStdMemCpyRamToRam( get_LinRxTxMsgDataPtr(linchannel)[tempCurFrameHandle],
                            pbTmpCurMsgPointer,
                            (vuint16)get_kLinRxBufferLength(linchannel, tempCurFrameHandle));
      }
   #if defined ( LIN_ENABLE_MSG_INDICATION_FLAG )
      /* set indication flag for received unconditional frame */

    #if ( (kLinNumberOfRxObjects+kLinNumberOfDiagRxObjects) <= 8 )
      /* if only 1 - 8 flags are available offset is always 0 */
      get_LinMsgIndicationFlags(linchannel)._c[0] |=
                                get_LinMsgIndicationMask(linchannel)[tempCurFrameHandle];
    #else
      get_LinMsgIndicationFlags(linchannel)._c[get_LinMsgIndicationOffset(linchannel)[tempCurFrameHandle]] |=
                                get_LinMsgIndicationMask(linchannel)[tempCurFrameHandle];
    #endif

   #endif

   #if defined ( LIN_ENABLE_MSG_INDICATION_FCT )
    #if defined ( V_ENABLE_USE_DUMMY_FUNCTIONS )
      /* Dummy function used when no user defined precopy function is used. no check required */
    #else
      /*lint -e611*/
      /* Disable PC-lint warning 611: "Suspicious cast" */
      /* Cast of null pointer used to avoid compiler warning */
      if ( (tApplLinMsgIndicationFct) V_NULL != get_LinRxApplMsgIndicationFctTbl(linchannel)[tempCurFrameHandle] )
      /* Enable PC-lint warning 611: "Suspicious cast" */
      /*lint +e611*/
    #endif
      {
        /* call indication function and pass receive message handle to the application */
        (get_LinRxApplMsgIndicationFctTbl(linchannel)[tempCurFrameHandle])
                                       (LIN_I_CHANNEL_PARA_FIRST tempCurFrameHandle);
      }
   #endif
  #endif /* ( kLinNumberOfRxObjects > 0 ) */
 #endif /* LIN_ECUTYPE_SLAVE */
 #if defined ( LIN_ENABLE_MSG_PRECOPY_FCT ) || defined ( LIN_ENABLE_ET_RX_FRAMES )
      LABEL_SKIP_INDICATION_HANDLING:;
 #endif
#endif /* kLinNumberOfIdObjects > 0 */
    }
/*******************************************************************************************/
/*   handling of diagnostic Rx frame                                                       */
/*******************************************************************************************/
    else if ( tempCurFrameHandle < get_LinNumberOfMsgInfoObjects(linchannel) )
    {
#if defined ( LIN_ECUTYPE_SLAVE )
      /* Received MasterReq frame in slave node  */
      if ( pbTmpCurMsgPointer[0] == 0 )
      {
        /* Sleep mode frame received. */
 #if defined ( LIN_ENABLE_SLEEP_COMMAND_REPETITION )
        bSleepCommandIndication = 1;
        inc_bNmSleepCommandCounter(linchannel);
        if (get_bNmSleepCommandCounter(linchannel) < 3)
        {
          /* indicate sleep command to application to allow goto-sleep state indication */
          ApplLinPreBusSleep(LIN_I_CHANNEL_PARA_FIRST get_bNmSleepCommandCounter(linchannel));
          set_wNmSleepDelayTimerValue(linchannel, get_kNmSleepTimeoutValue(linchannel));
        }
 #else
  #if defined ( LIN_APISTYLE_VECTOR )
        LinDoSleepModeHandling(LIN_I_CHANNEL_PARA_ONLY);
        /* reset mute mode performed in LinDoSleepModeHandling() */
  #else
        set_bLinStatusInfo_Flags(linchannel, (vuint8)(get_bLinStatusInfo_Flags(linchannel) | kLinStatus_GotoSleep));
        /* Enable frame processor to receive Wakeup frames */
        FpResetMuteMode(LIN_I_CHANNEL_PARA_ONLY);
  #endif
  #if defined ( LIN_ENABLE_DIAG_FRAMES )
        /* bDdDispatcherTx/RxState is reset when sleep mode frame is received */
        set_bDdDispatcherTxState(linchannel, kDdDiagFrmUser_SlaveConfig); /* set to highest priority */
   #if defined ( LIN_ENABLE_DIAG_TRANSP_LAYER )
        set_bDdDispatcherRxState(linchannel, kDdDiagFrmUser_SlaveConfig); /* set to highest priority */
   #endif
  #endif
 #endif
      }
 #if defined ( LIN_ENABLE_DIAG_FRAMES )
      else
      {
        /* Diagnostic MasterReq frame received. Pass data to all implemented Diagnostic servers */
        /* when currently no Receiver is activated. */

  #if defined ( LIN_ENABLE_DIAGMSG_INDICATION_FLAG )
        /* set indication flag for received MasterReq frame */

   #if ( (kLinNumberOfRxObjects+kLinNumberOfDiagRxObjects) <= 8 )
        /* if only 1 - 8 flags are available offset is always 0 */
        get_LinMsgIndicationFlags(linchannel)._c[0] |=
          get_LinMsgIndicationMask(linchannel)[get_MasterReqHandle(linchannel) - (get_LinNumberOfTxObjects(linchannel) + get_LinNumberOfEtObjects(linchannel))];
   #else
        get_LinMsgIndicationFlags(linchannel)._c[get_LinMsgIndicationOffset(linchannel)[get_MasterReqHandle(linchannel) - (get_LinNumberOfTxObjects(linchannel) + get_LinNumberOfEtObjects(linchannel))]] |=
          get_LinMsgIndicationMask(linchannel)[get_MasterReqHandle(linchannel) - (get_LinNumberOfTxObjects(linchannel) + get_LinNumberOfEtObjects(linchannel))];
   #endif

  #endif

  #if defined ( LIN_ENABLE_DIAG_TRANSP_LAYER )    || \
      defined ( LIN_ENABLE_SLAVE_CONFIGURATION )
        bTmpDiagFrmHandled = 0;
  #endif
  #if defined ( LIN_ENABLE_SLAVE_CONFIGURATION )
        /* Request Slave configuration for handling */
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
        if ((get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_13) ||
            ((get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_20)    && ((pbTmpCurMsgPointer[2]>= 0xB5u) && (pbTmpCurMsgPointer[2]<= 0xB7u))) )
        {
          bTmpDiagFrmHandled = kScReqNotHandled;
        }
        else
   #endif
        {
          bTmpDiagFrmHandled = ScMasterReqPrecopyFct(LIN_I_CHANNEL_PARA_FIRST pbTmpCurMsgPointer);
        }
        /* Slave configuration handles only single frame. */
        if ( bTmpDiagFrmHandled == kScReqHandled )
        { /* frame subscribed by node configuration API */
   #if defined ( LIN_ENABLE_DIAG_TRANSP_LAYER )
          if (get_bDdDispatcherRxState(linchannel) == kDdDiagFrmUser_LinTp_S)
          { /* inform active TP about more priorized configuration command reception */
            ApplLinDtlError(LIN_I_CHANNEL_PARA_ONLY);
          }
          set_bDdDispatcherRxState(linchannel, kDdDiagFrmUser_SlaveConfig); /* set to highest priority */
   #endif
   #if defined ( LIN_ENABLE_DIAGFRAME_BY_APPL ) && defined ( LIN_ENABLE_LOST_PRIORITIZATION_ERROR )
          if (get_bDdDispatcherTxState(linchannel) == kDdDiagFrmUser_None )
          { /* inform application of lost priorization - only relevant in running application session */
            ApplLinProtocolError( LIN_I_CHANNEL_PARA_FIRST  kLinLostPriorization, get_MasterReqHandle(linchannel));
          }
   #endif
          /* optional confirm to received request handled by node configuration API */
          set_bDdDispatcherTxState(linchannel, kDdDiagFrmUser_SlaveConfig);
        }
   #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
        else if ( bTmpDiagFrmHandled == kScReqIgnored )
        {
          /* other layer are not informed - keep current dispatcher states */
        }
   #endif
        else
  #endif /* LIN_ENABLE_SLAVE_CONFIGURATION */
        {
  #if defined ( LIN_ENABLE_DIAG_TRANSP_LAYER )
          /* Request Transport layer for handling */
          bTmpDiagFrmHandled = ApplLinDtlPrecopyFct(LIN_I_CHANNEL_PARA_FIRST pbTmpCurMsgPointer);
   #if defined ( LIN_ENABLE_DIAGFRAME_BY_APPL ) && defined ( LIN_ENABLE_LOST_PRIORITIZATION_ERROR )
          if (( bTmpDiagFrmHandled != kDtlRxFrameNotHandled ) && ( get_bDdDispatcherRxState(linchannel) == kDdDiagFrmUser_None ))
          { /* inform application of lost priorization - only relevant in running application session */
            ApplLinProtocolError( LIN_I_CHANNEL_PARA_FIRST  kLinLostPriorization, get_MasterReqHandle(linchannel));
          }
   #endif
          if ( bTmpDiagFrmHandled == kDtlRxExpectNextFrame )
          { /* continue reception of request - leave Tx state to most priore state */
            set_bDdDispatcherRxState(linchannel, kDdDiagFrmUser_LinTp_S);
            set_bDdDispatcherTxState(linchannel, kDdDiagFrmUser_SlaveConfig);
          }
          else if ( bTmpDiagFrmHandled == kDtlRxCompleteEnableTx )
          { /* request accepted prepare for response */
            set_bDdDispatcherRxState(linchannel, kDdDiagFrmUser_SlaveConfig); /* set back to highest priority */
            set_bDdDispatcherTxState(linchannel, kDdDiagFrmUser_LinTp_S);
          }
          else if ( bTmpDiagFrmHandled == kDtlRxCompleteNoTx )
          { /* request accepted no response */
            set_bDdDispatcherRxState(linchannel, kDdDiagFrmUser_SlaveConfig); /* set back to highest priority */
            set_bDdDispatcherTxState(linchannel, kDdDiagFrmUser_SlaveConfig); /* set to highest priority */
          }
          else  /* kDtlRxFrameNotHandled */
  #endif /* LIN_ENABLE_DIAG_TRANSP_LAYER */
          {
  #if defined ( LIN_ENABLE_DIAGFRAME_BY_APPL )
            /* Request Application for handling            */
            /* Perform precopy handling of SlaveResp frame */
   #if defined ( LIN_ENABLE_DIAGMSG_PRECOPY_FCT )
            /*lint -e661*/
            /* Disable PC-lint warning 661: "Possible creation of out-of-bounds pointer" */
            /*lint -e662*/
            /* Disable PC-lint warning 662: "Possible access of out-of-bounds pointer" */
            /*
            Warning are shown by PC-lint if diagnostic frames are used, a problem does not occur because
            the values that would lead to an error is filtered out by only handling rx messages.
            */

            /* Test if function is available not needed, if LIN_ENABLE_DIAGMSG_INDICATION_FCT set then function in slave available */
            /* Call precopy function  */
            if ( (get_LinRxDiagMsgPrecopyFctTbl(linchannel)[get_MasterReqHandle(linchannel) - get_LinNumberOfIdObjects(linchannel)])(LIN_I_CHANNEL_PARA_FIRST pbTmpCurMsgPointer)
                  != kLinNoCopyData_i )
            /* Enable PC-lint warning 662: "Possible access of out-of-bounds pointer" */
            /*lint +e662*/
            /* Enable PC-lint warning 661: "Possible creation of out-of-bounds pointer" */
            /*lint +e661*/
   #endif /* LIN_ENABLE_DIAGMSG_PRECOPY_FCT */
            {
              /* Rx message is Master Request Frame */
              /*******************************************************************************************/
              /* Indication handling of MasterRequest                                                    */
              /*******************************************************************************************/
              if ( get_pbLinMasterReqMsgDataPtr(linchannel) != (tLinMsgDataPtrType)0 )
              {
                /* copy message data to message buffer */
                VStdMemCpyRamToRam((void*)get_pbLinMasterReqMsgDataPtr(linchannel), (void*)pbTmpCurMsgPointer, 8);
              }

   #if defined ( LIN_ENABLE_DIAGMSG_INDICATION_FCT )
              /* Test if function is available not needed, if LIN_ENABLE_DIAGMSG_INDICATION_FCT set then function in slave available */
              /* call indication function and pass receive message handle to the application */
              get_LinRxDiagMsgIndicationFctTbl(linchannel)(LIN_I_CHANNEL_PARA_FIRST tempCurFrameHandle);
   #endif
            }
  #endif /* LIN_ENABLE_DIAGFRAME_BY_APPL */
  #if defined ( LIN_ENABLE_DIAG_TRANSP_LAYER )
            /* reqest passed to application */
            set_bDdDispatcherRxState(linchannel, kDdDiagFrmUser_None);
  #endif
            set_bDdDispatcherTxState(linchannel, kDdDiagFrmUser_None);
          } /* else Tp */
        } /* else Configuration API */
      }
 #endif /* LIN_ENABLE_DIAG_FRAMES */
#endif /* LIN_ECUTYPE_SLAVE */
    }
    else
    {
      /* other handles are either checked in the tx messages or not handled here */
    }
  }
  else /* bMsgDirection == kMessageDirectionRx */
  {
/*******************************************************************************************/
/*   Handling of all Tx Messages                                                           */
/*******************************************************************************************/
#if defined ( LIN_ECUTYPE_SLAVE )
    if ( tempCurFrameHandle < get_LinNumberOfIdObjects(linchannel) )
    {
      /* Tx frames or ET frames */

      /* Implement posttransmit function */

 #if defined ( LIN_ENABLE_STATUSBIT_SIGNAL )
  #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
      if ((get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_20) || (get_bCurrentProtocolVersion(linchannel) >= kLinProtocolCompatibility_21))
  #endif
      {
        /* response_error shall be cleared after transmission of frame with response_error bit. */
  #if defined ( LIN_ENABLE_RESP_ERR_IN_N_FRAMES )
        /* check first if current frame contains response_error bit */
        if (get_LinRxTxMsgInfo(linchannel)[tempCurFrameHandle].MsgRespErr == 1)
        {
          /* check with one tx frame if response_error flags are set and have to be cleared */
          if ((get_LinRxTxMsgDataPtr(linchannel)[get_LinStatusBitFrameHandle(linchannel, 0)][get_LinStatusBitOffset(linchannel, 0)] & get_LinStatusBitMask(linchannel, 0)) != 0)
          { /* flag set - clear flag in all affected frames */
            for (bTmpIndex = 0; bTmpIndex < kNumberOfRespErrFrames; bTmpIndex++)
            {
              /* Clear the error flag */
              get_LinRxTxMsgDataPtr(linchannel)[get_LinStatusBitFrameHandle(linchannel, bTmpIndex)][get_LinStatusBitOffset(linchannel, bTmpIndex)] &= (vuint8)((~get_LinStatusBitMask(linchannel, bTmpIndex)) & 0xFFU);
            }
          }
        }
  #else
        if ( tempCurFrameHandle == get_LinStatusBitFrameHandle(linchannel) )
        {
          /* Clear the error flag */
          get_LinRxTxMsgDataPtr(linchannel)[get_LinStatusBitFrameHandle(linchannel)][get_LinStatusBitOffset(linchannel)] &= (vuint8)((~get_LinStatusBitMask(linchannel)) & 0xFFU);
        }
  #endif
      }
 #endif


 #if defined ( LIN_ENABLE_ET_TX_FRAMES )
      /* Special handling for Event triggered Frame.    */
      /* Frame transmit with no error. Clear the transmission request flag.    */
      if ( tempCurFrameHandle >= get_LinNumberOfRxTxObjects(linchannel) )
      {
        /* Confirmation of Event triggered frame. Set handle to handle of assigned frame */
        tempCurFrameHandle  = (vuint8)((tempCurFrameHandle - (get_LinNumberOfRxTxObjects(linchannel) + get_LinNumberOfEtRxObjects(linchannel))) + get_LinNumberOfRxObjects(linchannel));
        /* set_pbMhMsgBuffer_FrmHandle(linchannel, tempCurFrameHandle);  Storing not needed because handle not needed after this function */
      }
 #endif

/*******************************************************************************************/
/* Confirmation handling of unconditional Tx messages                                      */
/*******************************************************************************************/
 #if defined ( LIN_ENABLE_MSG_CONFIRMATION_FLAG )
      /* set confirmation flag for transmitted unconditional frame */
  #if ( (kLinNumberOfTxObjects+kLinNumberOfDiagTxObjects) <= 8 )
      /* if only 1 - 8 flags are available offset is always 0 */
      get_LinMsgConfirmationFlags(linchannel)._c[0] |=
                                get_LinMsgConfirmationMask(linchannel)[tempCurFrameHandle-get_LinNumberOfRxObjects(linchannel)];
  #else
      get_LinMsgConfirmationFlags(linchannel)._c[get_LinMsgConfirmationOffset(linchannel)[tempCurFrameHandle-get_LinNumberOfRxObjects(linchannel)]] |=
                                get_LinMsgConfirmationMask(linchannel)[tempCurFrameHandle-get_LinNumberOfRxObjects(linchannel)];
  #endif
 #endif

 #if defined ( LIN_ENABLE_MSG_CONFIRMATION_FCT )
  #if defined ( V_ENABLE_USE_DUMMY_FUNCTIONS )
      /* Dummy function used when no user defined precopy function is used. no check required */
  #else
      /*lint -e611*/
      /* Disable PC-lint warning 611: "Suspicious cast" */
      /* Cast of null pointer used to avoid compiler warning */
      if ( (tApplLinMsgConfirmationFct) V_NULL != get_LinTxApplMsgConfirmationFctTbl(linchannel)[tempCurFrameHandle-get_LinNumberOfRxObjects(linchannel)] )
      /* Enable PC-lint warning 611: "Suspicious cast" */
      /*lint +e611*/
  #endif
      {
        /* call indication function and pass receive message handle to the application */
        (get_LinTxApplMsgConfirmationFctTbl(linchannel)[tempCurFrameHandle-get_LinNumberOfRxObjects(linchannel)])
                                          (LIN_I_CHANNEL_PARA_FIRST tempCurFrameHandle);
      }
 #endif /* LIN_ENABLE_MSG_CONFIRMATION_FCT */
    }
    else
    {
      /* Handling of transmitted SlaveResp frame  */
 #if defined ( LIN_ENABLE_DIAG_FRAMES )

  #if defined ( LIN_ENABLE_DIAGMSG_CONFIRMATION_FLAG )
      /* set confirmation flag for transmitted SlaveResp frame */
   #if ( (kLinNumberOfTxObjects+kLinNumberOfDiagTxObjects) <= 8 )
      /* if only 1 - 8 flags are available offset is always 0 */
      get_LinMsgConfirmationFlags(linchannel)._c[0] |=
        get_LinMsgConfirmationMask(linchannel)[get_SlaveRespHandle(linchannel) - ( get_LinNumberOfRxObjects(linchannel) + get_LinNumberOfEtObjects(linchannel) + get_LinNumberOfDiagRxObjects(linchannel) )];
   #else
      get_LinMsgConfirmationFlags(linchannel)._c[get_LinMsgConfirmationOffset(linchannel)[get_SlaveRespHandle(linchannel) - ( get_LinNumberOfRxObjects(linchannel) + get_LinNumberOfEtObjects(linchannel) + get_LinNumberOfDiagRxObjects(linchannel) )]] |=
        get_LinMsgConfirmationMask(linchannel)[get_SlaveRespHandle(linchannel) - ( get_LinNumberOfRxObjects(linchannel) + get_LinNumberOfEtObjects(linchannel) + get_LinNumberOfDiagRxObjects(linchannel) )];
   #endif
  #endif
  #if defined ( LIN_ENABLE_DIAGFRAME_BY_APPL )
      if ( get_bDdDispatcherTxState(linchannel) == kDdDiagFrmUser_None )
      {
   #if defined ( LIN_ENABLE_DIAGMSG_CONFIRMATION_FCT )
        /* Test if function is available not needed, if LIN_ENABLE_DIAGMSG_INDICATION_FCT set then function in slave available */
        /* call indication function and pass receive message handle to the application */
        get_LinTxDiagMsgConfirmationFctTbl(linchannel)(LIN_I_CHANNEL_PARA_FIRST get_SlaveRespHandle(linchannel));
   #endif
      }
  #endif

  #if defined ( LIN_ENABLE_SLAVE_CONFIGURATION )
      /* Confirmation handling and error handling is not performed. */
      if ( get_bDdDispatcherTxState(linchannel) == kDdDiagFrmUser_SlaveConfig )
      { /* positive response transmitted */
        /* clear pending response */
          set_bScResponseBuffer(linchannel, 0, 0);
   #if defined ( LIN_ENABLE_T_NODE_CONFIG_SERVICE )
          set_NasTimerValue(linchannel, 0x00u);
   #endif
      }
  #endif
  #if defined ( LIN_ENABLE_DIAG_TRANSP_LAYER )
      if ( get_bDdDispatcherTxState(linchannel) == kDdDiagFrmUser_LinTp_S )
      {
        /* Successful transmission of the SlaveResp frame */
        bTmpDiagFrmHandled = ApplLinDtlTxConfirmation(LIN_I_CHANNEL_PARA_ONLY);
        if ( bTmpDiagFrmHandled == kDtlTxCompleteNoRx )
        {
          set_bDdDispatcherTxState(linchannel, kDdDiagFrmUser_SlaveConfig);
        }
      }
  #endif
 #endif /* LIN_ENABLE_DIAG_FRAMES */
    }
#endif /* LIN_ECUTYPE_SLAVE */
  }
#if defined ( LIN_ENABLE_SLEEP_COMMAND_REPETITION )
  if (get_wNmSleepDelayTimerValue(linchannel) > 0)
  { /* sleep command previously received - check if current frame is not sleep command */
    if (bSleepCommandIndication == 0)
    { /* normal frame received - stop sleep transition */
      set_wNmSleepDelayTimerValue(linchannel, 0);
      set_bNmSleepCommandCounter(linchannel, 0);
      /* Inform application about wakeup event */
 #if defined ( LIN_APISTYLE_LIN )
  #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u )
      set_bLinStatusInfo_Flags(linchannel, (vuint8)(get_bLinStatusInfo_Flags(linchannel) | kLinStatus_BusActivity));
  #endif
      ApplLinWakeupRequest(LIN_I_CHANNEL_PARA_ONLY);
 #else /* LIN_APISTYLE_LIN */
      ApplLinWakeUp(LIN_I_CHANNEL_PARA_ONLY);
 #endif /* LIN_APISTYLE_LIN */
    }
  }
#endif
} /* PRQA S 6030 *//* MD_LIN_METRIC_STCYC */ /* PRQA S 6080 *//* MD_LIN_METRIC_STMIF */ /* PRQA S 6050 *//* MD_LIN_METRIC_STCAL */
/* CODE CATEGORY 1 END*/

/*******************************************************************************************/
/*    FUNCTION:  ApplFpErrorNotification                                                   */
/*******************************************************************************************/
/**
 *   @brief   Handling of all protocol errors detected by the frame processor
 *
 *            The callback function is called by the frame processor, when a protocol error
 *            has been detected. Dependent on the message type, the error is indicated to the
 *            application or not.
 *
 *   @param_i channel The interface/channel which received or transmitted the response
 *
 *   @param   bError Error code of the detected error
 *
 *   @return  No return value
 *
 *   @note    Call context is UART Interrupt or task level
 *
 *******************************************************************************************/
/* CODE CATEGORY 1 START*/
static void ApplFpErrorNotification(LIN_I_CHANNEL_TYPE_FIRST LIN_I_PROTECTED_ID_TYPE vuint8 bError)
{
  tLinFrameHandleType tempCurFrameHandle;
#if defined ( LIN_ECUTYPE_SLAVE )
 #if defined ( LIN_ENABLE_RESP_ERR_IN_N_FRAMES )
  vuint8 bTmpIndex;
 #endif
#endif

#if defined ( LIN_ECUTYPE_SLAVE )
#endif

  if ( (bError & 0xF0u) != 0 )
  { /* Handling of errors in response (Rx or Tx) */
#if defined ( LIN_ECUTYPE_SLAVE )
    {
      tempCurFrameHandle  = get_pbMhMsgBuffer_FrmHandle(linchannel);
    }
#endif

#if defined ( LIN_ENABLE_ET_RX_FRAMES ) || defined ( LIN_ENABLE_ET_TX_FRAMES )
    if ( (tempCurFrameHandle >= get_LinNumberOfRxTxObjects(linchannel)) &&
         (tempCurFrameHandle < get_LinNumberOfIdObjects(linchannel)) )
    {
      /* Special handling for event triggered frames */
 #if defined ( LIN_ECUTYPE_SLAVE )
  #if defined ( LIN_ENABLE_ET_TX_FRAMES )
      /* Handling of clearing the event triggered frame pending flag moved to Header indication */
      /* Reset flag of assigned frame */
   #if ( kLinNumberOfEtTxObjects <= 8 )
      /* if only 1 - 8 flags are available offset is always 0 */
      (get_LinETFUpdateFlags(linchannel))._c[0] |= get_bLinETFStoreFlag(linchannel);
   #else
      (get_LinETFUpdateFlags(linchannel))._c[get_LinETFUpdateFlagOffset(linchannel)[tempCurFrameHandle-get_LinNumberOfRxTxObjects(linchannel)]] |= get_bLinETFStoreFlag(linchannel);
   #endif
  #endif
 #endif
    }
    else
#endif
    {
#if defined ( LIN_ECUTYPE_SLAVE ) && defined ( LIN_ENABLE_ET_TX_FRAMES )
      if ( (tempCurFrameHandle >= get_LinNumberOfRxObjects(linchannel)) &&
           (tempCurFrameHandle < (get_LinNumberOfRxObjects(linchannel) + get_LinNumberOfEtTxObjects(linchannel))) )
      {
        /* Handling of clearing the event triggered frame pending flag moved to Header indication */
        /* Reset flag of assigned frame */
 #if ( kLinNumberOfEtTxObjects <= 8 )
      /* if only 1 - 8 flags are available offset is always 0 */
        (get_LinETFUpdateFlags(linchannel))._c[0] |= get_bLinETFStoreFlag(linchannel);
 #else
        (get_LinETFUpdateFlags(linchannel))._c[get_LinETFUpdateFlagOffset(linchannel)[tempCurFrameHandle-get_LinNumberOfRxObjects(linchannel)]] |= get_bLinETFStoreFlag(linchannel);
 #endif
      }
#endif
#if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u ) || defined ( LIN_ENABLE_RE_SUPP_ON_NO_RESPONSE )
       /* in case of LIN >= 2.1 or if LIN_ENABLE_RE_SUPP_ON_NO_RESPONSE no response_error bit is set when no response is received on unconditional frame header */
 #if defined ( LIN_APISTYLE_LIN ) || defined ( LIN_ECUTYPE_SLAVE )
  #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
      if ( ( bError != kFpError_RespOmittedTimeout )  ||  (get_bCurrentProtocolVersion(linchannel) <= kLinProtocolCompatibility_20) )
  #else
      if ( bError != kFpError_RespOmittedTimeout )
  #endif
 #endif
#endif
      {
#if defined ( LIN_APISTYLE_LIN )
        /* Set last protected id, error in transfer and if necessary, overrun */
        set_bLinStatusInfo_LastPid(linchannel, bProtectedId);
        if ( (get_bLinStatusInfo_Flags(linchannel) & (kLinStatus_RxTxSuccess | kLinStatus_ResponseError)) != 0 )
        {
          /* Successful transfer of error in response already set. Overrun condition */
          set_bLinStatusInfo_Flags(linchannel, (vuint8)(get_bLinStatusInfo_Flags(linchannel) | kLinStatus_Overrun));
        }
 #if ( LIN_PROTOCOLVERSION_VALUE >= 0x21u ) 
  #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
        if ((get_bCurrentProtocolVersion(linchannel) >= kLinProtocolCompatibility_21) || (get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_J2602))
  #endif
        {
          set_bLinStatusInfo_Flags(linchannel, (vuint8)(get_bLinStatusInfo_Flags(linchannel) | kLinStatus_ResponseError | kLinStatus_BusActivity));
        }
  #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
        else
        {
          set_bLinStatusInfo_Flags(linchannel, (vuint8)(get_bLinStatusInfo_Flags(linchannel) | kLinStatus_ResponseError));
        }
  #endif
 #else
        set_bLinStatusInfo_Flags(linchannel, (vuint8)(get_bLinStatusInfo_Flags(linchannel) | kLinStatus_ResponseError));
 #endif
#endif
#if defined ( LIN_ECUTYPE_SLAVE )
 #if defined ( LIN_ENABLE_STATUSBIT_SIGNAL )
      /* response_error shall be set whenever a frame received by the node or a frame      */
      /* transmitted by the node contains an error in the response field.                  */

      /* Set the error flag */
  #if defined ( LIN_ENABLE_RESP_ERR_IN_N_FRAMES )
        /* set response_error in all affected frames */
        for (bTmpIndex = 0; bTmpIndex < kNumberOfRespErrFrames; bTmpIndex++)
        {
          get_LinRxTxMsgDataPtr(linchannel)[get_LinStatusBitFrameHandle(linchannel, bTmpIndex)][get_LinStatusBitOffset(linchannel, bTmpIndex)] |= get_LinStatusBitMask(linchannel, bTmpIndex);
        }
  #else
        get_LinRxTxMsgDataPtr(linchannel)[get_LinStatusBitFrameHandle(linchannel)][get_LinStatusBitOffset(linchannel)] |= get_LinStatusBitMask(linchannel);
  #endif
 #endif
#endif
      }

#if defined ( LIN_ENABLE_DIAG_FRAMES )
 #if defined ( LIN_ECUTYPE_SLAVE )
      if ( tempCurFrameHandle == get_MasterReqHandle(linchannel) )
      { /* error in MasterReq response - pending responses must be canceled */
  #if defined ( LIN_ENABLE_SLAVE_CONFIGURATION )
        /* Error handling is not performed. */
   #if defined ( LIN_ENABLE_DIAG_RESPONSE_AFTER_ERROR ) || ( LIN_PROTOCOLVERSION_VALUE >= 0x22u )
        /* Introduced with Errata sheet 1.4 the slave node shall proceed with a diagnosic request even
           when a new MasterReq frame with error in response has been received */
   #else
        if ( get_bDdDispatcherTxState(linchannel) == kDdDiagFrmUser_SlaveConfig )
        { /* clear pending response */
          set_bScResponseBuffer(linchannel, 0, 0);
    #if defined ( LIN_ENABLE_T_NODE_CONFIG_SERVICE )
          set_NasTimerValue(linchannel, 0x00u);
    #endif
        }
   #endif
  #endif
  #if defined ( LIN_ENABLE_DIAG_RESPONSE_AFTER_ERROR ) || ( LIN_PROTOCOLVERSION_VALUE >= 0x22u )
        /* Introduced with Errata sheet 1.4 the slave node shall proceed with a diagnosic request even
           when a new MasterReq frame with error in response has been received */
        /* keep in current state */
  #else
   #if defined ( LIN_ENABLE_DIAG_TRANSP_LAYER )
        if (( get_bDdDispatcherTxState(linchannel) == kDdDiagFrmUser_LinTp_S ) || ( get_bDdDispatcherRxState(linchannel) == kDdDiagFrmUser_LinTp_S ))
        {
          set_bDdDispatcherRxState(linchannel, kDdDiagFrmUser_SlaveConfig); /* set to highest priority */
          /* Inform transport layer about error */
          ApplLinDtlError(LIN_I_CHANNEL_PARA_ONLY);
        }
        else
        {
          /* application will be informed with protocol errors */
        }
   #endif /* LIN_ENABLE_DIAG_TRANSP_LAYER */
        /* pending application diagnostic session is also rejected - FramingError or ChecksumError is reported in this case */
        set_bDdDispatcherTxState(linchannel, kDdDiagFrmUser_SlaveConfig);
  #endif
      }
      if ( tempCurFrameHandle == get_SlaveRespHandle( linchannel) )
      {
  #if defined ( LIN_ENABLE_DIAG_TRANSP_LAYER )
        if ( get_bDdDispatcherTxState(linchannel) == kDdDiagFrmUser_LinTp_S )
        {
          set_bDdDispatcherRxState(linchannel, kDdDiagFrmUser_SlaveConfig); /* set to highest priority */
          ApplLinDtlError(LIN_I_CHANNEL_PARA_ONLY);
        }
  #endif
  #if defined ( LIN_ENABLE_SLAVE_CONFIGURATION )
        if ( get_bDdDispatcherTxState(linchannel) == kDdDiagFrmUser_SlaveConfig )
        {
          /* clear pending response */
          set_bScResponseBuffer(linchannel, 0, 0);
   #if defined ( LIN_ENABLE_T_NODE_CONFIG_SERVICE )
          set_NasTimerValue(linchannel, 0x00u);
   #endif
        }
  #endif
      }
 #endif /* LIN_ECUTYPE_SLAVE */

#endif /* LIN_ENABLE_DIAG_FRAMES */
      switch (bError)
      {
#if defined ( LIN_ENABLE_BIT_ERROR )
        case (vuint16) kFpError_RespTxMonitoring:
        case (vuint16) kFpError_RespTxFormat:
          ApplLinProtocolError( LIN_I_CHANNEL_PARA_FIRST  kLinBitError, tempCurFrameHandle);
        break;
#endif

#if defined ( LIN_ENABLE_FORMAT_ERROR )
        case (vuint16) kFpError_RespRxFormat:
          ApplLinProtocolError( LIN_I_CHANNEL_PARA_FIRST  kLinFormatError, tempCurFrameHandle);
        break;
#endif

#if defined ( LIN_ENABLE_CHECKSUM_ERROR )
        case (vuint16) kFpError_RespRxChecksum:
          ApplLinProtocolError( LIN_I_CHANNEL_PARA_FIRST  kLinChecksumError, tempCurFrameHandle);
        break;
#endif

#if defined ( LIN_ENABLE_NO_RESPONSE_ERROR )
        case (vuint16) kFpError_RespIncompTimeout:
          ApplLinProtocolError( LIN_I_CHANNEL_PARA_FIRST  kLinErrInResponse, tempCurFrameHandle);
        break;
        case (vuint16) kFpError_RespOmittedTimeout:
          ApplLinProtocolError( LIN_I_CHANNEL_PARA_FIRST  kLinNoResponse, tempCurFrameHandle);
        break;
#endif
        default:
          /* Unknown error is not handled */
        break;
      }
    }
  }
  else
  {
    /* Handling of errors in header */
    switch (bError)
    {

#if defined ( LIN_ECUTYPE_SLAVE )
 #if defined ( LIN_ENABLE_SYNCH_FIELD_ERROR )
      case (vuint16)kFpError_HeaderRxSynchField:
        ApplLinProtocolError( LIN_I_CHANNEL_PARA_FIRST  kLinSynchFieldError, kMsgHandleDummy);
      break;
 #endif
#endif

#if defined ( LIN_ENABLE_NO_HEADER_ERROR )
      case (vuint16) kFpError_HeaderTimeout:
 #if defined ( LIN_ECUTYPE_SLAVE )
      case (vuint16) kFpError_HeaderRxFormat:
 #endif
        ApplLinProtocolError( LIN_I_CHANNEL_PARA_FIRST  kLinNoHeader, kMsgHandleDummy);
      break;
#endif
      default:
        /* Unknown error is not handled */
      break;
    }
  } /* PRQA S 6030 *//* MD_LIN_METRIC_STCYC */ /* PRQA S 6010 *//* MD_LIN_METRIC_STPTH */
  /* no header indication when waiting for the Identifier is handled as a Bus activity */
} /* PRQA S 6030 *//* MD_LIN_METRIC_STCYC */ /* PRQA S 6010 *//* MD_LIN_METRIC_STPTH */
/* CODE CATEGORY 1 END*/

/*******************************************************************************************/
/*    FUNCTION:  LinFastTimerTask                                                          */
/*******************************************************************************************/
/*    Documentation see lin_drv_os.h                                                       */
/*******************************************************************************************/
/* CODE CATEGORY 2 START*/
void LinFastTimerTask(LIN_I_CHANNEL_TYPE_ONLY)
{
#if defined ( LIN_ENABLE_T_HEADER_MAX ) || defined ( LIN_ENABLE_T_FRAME_MAX )
 #if defined ( SIO_LL_APISTYLE_MESSAGE )
  vuint8 bTimeoutCause;
 #endif
#endif
  /* observes the message timeouts and the wakeup repetition. */

  /* Disable UART interrupts */
  LinStartTaskSync(LIN_I_CHANNEL_PARA_ONLY);

#if defined ( SIO_ENABLE_MUTE_MODE_POLLING )
  /* Generic call for polling function */
  /* This controller needs a high level to set the mute mode, so it is perioricly called */
  SioMuteModePolling(LIN_I_CHANNEL_PARA_ONLY);
#endif

#if defined ( SIO_ENABLE_SIO_POLLING_BY_DRV )
  /* This controller needs a polling function that is periodically called */
  LinLowPolling(LIN_I_CHANNEL_PARA_ONLY);
#endif

#if defined ( LIN_ENABLE_T_HEADER_MAX ) || defined ( LIN_ENABLE_T_FRAME_MAX )
/*******************************************************************************************/
/*    Header max and Frame max timeout observation                                         */
/*******************************************************************************************/
  /* Change action for the timer has been requested   */
  switch ( get_bFpTimerState(linchannel) )
  {
    case (vuint16)kFpTimerStartHeaderObs:
      /* Start header observation */
      set_bFpTimerValue(linchannel, get_bFpTimerNewValue(linchannel));
      set_bFpTimerState(linchannel, kFpTimerHeaderMode);
    break;

    case (vuint16)kFpTimerIncResponseObs:
      /* Start response observation and use remaining header time*/
      set_bFpTimerValue(linchannel, (vuint8)(get_bFpTimerValue(linchannel) + get_bFpTimerNewValue(linchannel)));
      set_bFpTimerState(linchannel, kFpTimerResponseMode);
    break;

    case (vuint16)kFpTimerCancel:
      set_bFpTimerValue(linchannel, 0);
      set_bFpTimerState(linchannel, kFpTimerIdle);
    break;

    default:
      /* nothing to do here */
    break;
  }

/*******************************************************************************************/
  if ( get_bFpTimerValue(linchannel) != 0 )    /* to be verified whether cases must be distinguished. */
  {
    set_bFpTimerValue(linchannel, (vuint8)(get_bFpTimerValue(linchannel) - 1));
    if ( ! (get_bFpTimerValue(linchannel)) )
    {
      /* Timer expired  */
 #if ( defined ( SIO_LL_APISTYLE_MESSAGE ) && defined ( SIO_LL_APITYPE_HEADER_IND ) )
      if ( get_bFpTimerState(linchannel) == kFpTimerHeaderMode )
      { /* Header timeout */
        {
          ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_HeaderTimeout);
        }
      }
      else if ( get_bFpTimerState(linchannel) == kFpTimerResponseMode )
 #else
      if ( get_bFpTimerState(linchannel) == kFpTimerResponseMode )
 #endif
      { /* Response timeout */
 #if defined ( SIO_LL_APISTYLE_MESSAGE )
  #if defined ( SIO_LL_APITYPE_MESSAGE_IND )
        bTimeoutCause = LinLowFrmTimeoutFunc(LIN_I_CHANNEL_PARA_ONLY);
        if ( kFpTimerNoHeader == bTimeoutCause )
        { /* No header byte transmitted/received */
          ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_HeaderOmittedTimeout);
        }
        else if ( kFpTimerIncHeader == bTimeoutCause )
        { /* Header incomplete received/transmitted */
          ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_HeaderTimeout);
        }
   #if defined (SIO_EXTENDED_FRM_TIMEOUT_HANDLING)
        else if ( kFpTxMonitoringError == bTimeoutCause )
        { /* no interrupt generated in case of monitoring error - report now */
          ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_RespTxMonitoring);
        }
   #endif
        else if ( kFpTimerNoResponse == bTimeoutCause  )
  #else
        /* Message API with header indication */
        bTimeoutCause = LinLowRespTimeoutFunc(LIN_I_CHANNEL_PARA_ONLY);
        if ( kFpTimerNoResponse == bTimeoutCause )
  #endif
 #else
        /* Byte API */
        if ( (get_bFpRemainingBytes(linchannel) & kFpNoReceptionFlag) != 0 )
 #endif
        {
          /* No Response Timeout */
          ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_RespOmittedTimeout);
        }
        else
        { /* Incomplete Response Timeout */
          ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_RespIncompTimeout);
        }
      }
      else
      {
        /* Misra needs ending else in if - else if */
      }
      set_bFpTimerState(linchannel, kFpTimerIdle);
      FpSetMuteMode(LIN_I_CHANNEL_PARA_ONLY);
    }
  }

#endif /* LIN_ENABLE_T_HEADER_MAX || LIN_ENABLE_T_FRAME_MAX */

#if defined ( LIN_APISTYLE_VECTOR )

 #if defined ( LIN_ENABLE_LINSTART_WAKEUP_INTERNAL )
  #if !defined ( SIO_LL_ENABLE_T_NO_WAKEUP_BY_HARDWARE )
/*******************************************************************************************/
/*    No wakeup timeout observation                                                        */
/*******************************************************************************************/
  /* Change action for the timer has been requested   */
  switch ( get_bNmWupTimerState(linchannel) )
  {
    case (vuint16)kNmWupTimerStart:
      /* Start Wakeup observation */
      set_bNmWupTimerValue(linchannel, get_bNmWupTimerNewValue(linchannel) );
      set_bNmWupTimerState(linchannel, kNmWupTimerActive_1);
    break;

    case (vuint16)kNmWupTimerCancel:
      set_bNmWupTimerValue(linchannel, 0);
      set_bNmWupTimerState(linchannel, kNmWupTimerIdle);
    break;

    default:
      /* nothing to do here */
    break;
  }
/*******************************************************************************************/
  if ( get_bNmWupTimerValue(linchannel) != 0 )
  {
    set_bNmWupTimerValue(linchannel, (vuint8)(get_bNmWupTimerValue(linchannel) - 1));
    if ( ! (get_bNmWupTimerValue(linchannel)) )
    {
      /* Timer expired  */
      switch ( get_bNmWupTimerState(linchannel) )
      {
        case (vuint16)kNmWupTimerActive_1:
        case (vuint16)kNmWupTimerActive_2:
          /* Timeout after first Wakeup frame  */
          set_bNmWupTimerState(linchannel, (vuint8)(get_bNmWupTimerState(linchannel) + 1));
          /* Restart timer */
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
          if (get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_13)
          {
            set_bNmWupTimerValue(linchannel, get_kNmWupTimerStartValue13(linchannel));
          }
          else
   #endif
          {
            set_bNmWupTimerValue(linchannel, get_kNmWupTimerStartValue(linchannel));
          }
          /* Repeat transmission of Wakeup frame */
          FpResetMuteMode(LIN_I_CHANNEL_PARA_ONLY);
          FpSendWakeup(LIN_I_CHANNEL_PARA_ONLY);
        break;

        case (vuint16)kNmWupTimerActive_3:
          /* Timeout after third Wakeup frame  */
          set_bNmWupTimerState(linchannel, kNmWupTimerIdle);
          /* Start notification delay timer */
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
          if (get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_13)
          {
            Start_bNmNoWupDelayTimer13(linchannel);
          }
          else
   #endif
          {
            Start_bNmNoWupDelayTimer(linchannel);
          }
          /* Wait for external wake */
          FpResetMuteMode(LIN_I_CHANNEL_PARA_ONLY);
        break;

        default:
          /* nothing to do here */
        break;
      }
    }
  }
  #endif /* ! SIO_LL_ENABLE_T_NO_WAKEUP_BY_HARDWARE */
 #endif /* LIN_ENABLE_LINSTART_WAKEUP_INTERNAL */
#endif /* LIN_APISTYLE_VECTOR */

#if defined ( LIN_ENABLE_T_NODE_CONFIG_SERVICE )
/*******************************************************************************************/
/*    Node configuration service timeout observation                                       */
/*******************************************************************************************/
  if ( get_bScResponseBuffer(linchannel, 0) != 0x00u )
  { /* Node configuration service response pending - check for N_As timeout */
    if ( get_NasTimerValue(linchannel) != 0 )
    {
      dec_NasTimerValue(linchannel);
      if ( get_NasTimerValue(linchannel) == 0 )
      { /* Timer expired - clear pending response */
        set_bScResponseBuffer(linchannel, 0, 0x00u);
        /* Notification to application layer not necessary */
      }
    }
  }
#endif

#if defined ( LIN_ENABLE_SLEEP_COMMAND_REPETITION )

  if (get_wNmSleepDelayTimerValue(linchannel) > 0)
  {
    dec_wNmSleepDelayTimerValue(linchannel);
    if (get_wNmSleepDelayTimerValue(linchannel) == 0)
    { /* timeout reached - goto sleep now */
      set_bNmSleepCommandCounter(linchannel, 0);

 #if defined ( LIN_APISTYLE_VECTOR )
      LinDoSleepModeHandling(LIN_I_CHANNEL_PARA_ONLY);
      /* reset mute mode performed in LinDoSleepModeHandling() */
 #else
      set_bLinStatusInfo_Flags(linchannel, (vuint8)(get_bLinStatusInfo_Flags(linchannel) | kLinStatus_GotoSleep));
      /* Enable frame processor to receive Wakeup frames */
      FpResetMuteMode(LIN_I_CHANNEL_PARA_ONLY);
 #endif
 #if defined ( LIN_ENABLE_DIAG_FRAMES )
      /* bDdDispatcherTx/RxState is reset when sleep mode frame is received */
      set_bDdDispatcherTxState(linchannel, kDdDiagFrmUser_SlaveConfig); /* set to highest priority */
  #if defined ( LIN_ENABLE_DIAG_TRANSP_LAYER )
      set_bDdDispatcherRxState(linchannel, kDdDiagFrmUser_SlaveConfig); /* set to highest priority */
  #endif
 #endif
    }
  }
#endif
  /* restore UART (TIMER, ...) interrupts */
  LinEndTaskSync(LIN_I_CHANNEL_PARA_ONLY);
} /* PRQA S 6030 *//* MD_LIN_METRIC_STCYC */ /* PRQA S 6010 *//* MD_LIN_METRIC_STPTH */ /* PRQA S 6050 *//* MD_LIN_METRIC_STCAL */ /* PRQA S 6080 *//* MD_LIN_METRIC_STMIF */
/* CODE CATEGORY 2 END*/

/*******************************************************************************************/
/*******************************************************************************************/
/*    GROUP: Frame processor                                                              **/
/*******************************************************************************************/
/*******************************************************************************************/
/** @addtogroup grpFrmProcessor
 *  @par Functions implemented by the Frame processor (RxTx handler)
 *  @{
 */

#if defined ( LIN_APISTYLE_LIN )
 #if ( LIN_PROTOCOLVERSION_VALUE <= 0x20u )
/*******************************************************************************************/
/*    FUNCTION:  l_ifc_connect                                                             */
/*******************************************************************************************/
/*    Documentation see lin_drv.h                                                          */
/*******************************************************************************************/
/* CODE CATEGORY 4 START*/
l_bool l_ifc_connect(LIN_I_CHANNEL_TYPE_ONLY) /* PRQA S 1330 *//* MD_LIN_DRV_16.4_B */
{
  set_bFpConnectionState(linchannel, kIfcConnected);
  return(0);
}
/* CODE CATEGORY 4 END*/

/*******************************************************************************************/
/*    FUNCTION:  l_ifc_disconnect                                                          */
/*******************************************************************************************/
/*    Documentation see lin_drv.h                                                          */
/*******************************************************************************************/
/* CODE CATEGORY 4 START*/
l_bool l_ifc_disconnect(LIN_I_CHANNEL_TYPE_ONLY) /* PRQA S 1330 *//* MD_LIN_DRV_16.4_B */
{
  set_bFpConnectionState(linchannel, kIfcDisconnected);
  return(0);
}
/* CODE CATEGORY 4 END*/
 #endif
/*******************************************************************************************/
/*    API FUNCTION:  LinSetOperationalMode                                                 */
/*******************************************************************************************/
/*    Documentation see lin_drv.h                                                          */
/*******************************************************************************************/
/* CODE CATEGORY 4 START*/
void LinSetOperationalMode(LIN_I_CHANNEL_TYPE_ONLY) /* PRQA S 1330 *//* MD_LIN_DRV_16.4_B */
{
  FpSetMuteMode(LIN_I_CHANNEL_PARA_ONLY);
}
/* CODE CATEGORY 4 END*/

/*******************************************************************************************/
/*    API FUNCTION:  LinSetStandByMode                                                     */
/*******************************************************************************************/
/*    Documentation see lin_drv.h                                                          */
/*******************************************************************************************/
/* CODE CATEGORY 4 START*/
void LinSetStandByMode(LIN_I_CHANNEL_TYPE_ONLY) /* PRQA S 1330 *//* MD_LIN_DRV_16.4_B */
{
  FpResetMuteMode(LIN_I_CHANNEL_PARA_ONLY);
}
/* CODE CATEGORY 4 END*/

#endif /* LIN_APISTYLE_LIN */

#if ( defined ( LIN_APISTYLE_LIN ) || defined ( LIN_ENABLE_T_HEADER_MAX ) || defined ( LIN_ENABLE_T_FRAME_MAX ) || \
     ( defined ( LIN_APISTYLE_VECTOR ) &&  defined ( LIN_ENABLE_LINSTART_WAKEUP_EXTERNAL )))
/******************************************************************************************/
/*    FUNCTION:  FpSetMuteMode                                                            */
/******************************************************************************************/
/**
 *   @brief   Sets the frame processor and the SIO interface to mute mode
 *
 *            The internal function sets the frame processor and the SIO interface to
 *            mute mode. in this mode, only the synch break field is handled. Byte
 *            indications are ignored.
 *
 *   @param_i channel The interface/channel which is used
 *
 *   @param   none.
 *
 *   @return  No return value
 *
 *******************************************************************************************/
/* CODE CATEGORY 1 START*/
static void FpSetMuteMode(LIN_I_CHANNEL_TYPE_ONLY)
{
  SioSetMuteMode(LIN_I_CHANNEL_PARA_ONLY);
}
/* CODE CATEGORY 1 END*/
#endif
/*******************************************************************************************/
/*    FUNCTION:  FpResetMuteMode                                                           */
/*******************************************************************************************/
/**
 *   @brief   Clears the mute mode of the frame processor and the SIO interface
 *
 *            The internal function clears the mute mode of the frame processor and the
 *            SIO interface to be able to receive a wakeup signal
 *
 *   @param_i channel The interface/channel which is used
 *
 *   @param   none.
 *
 *   @return  No return value
 *
 *******************************************************************************************/
/* CODE CATEGORY 2 START*/
static void FpResetMuteMode(LIN_I_CHANNEL_TYPE_ONLY)
{
  SioResetMuteMode(LIN_I_CHANNEL_PARA_ONLY);
}
/* CODE CATEGORY 2 END*/

/*******************************************************************************************/
/*    FUNCTION:  FpSendWakeup                                                              */
/*******************************************************************************************/
/*    Documentation see lin_drv.h                                                          */
/*******************************************************************************************/
/* CODE CATEGORY 3 START*/
#if defined ( LIN_APISTYLE_LIN )
void l_ifc_wake_up(LIN_I_CHANNEL_TYPE_ONLY)  /* PRQA S 1330 *//* MD_LIN_DRV_16.4_B */
#elif defined ( LIN_ENABLE_LINSTART_WAKEUP_INTERNAL )
static void FpSendWakeup(LIN_I_CHANNEL_TYPE_ONLY)
#endif
#if defined ( LIN_APISTYLE_LIN ) || defined ( LIN_ENABLE_LINSTART_WAKEUP_INTERNAL )
{
 #if defined ( LIN_APISTYLE_LIN ) && ( LIN_PROTOCOLVERSION_VALUE <= 0x20u )
  if ( get_bFpConnectionState(linchannel) != 0 )
 #endif
  {
 #if defined ( SIO_LL_APISTYLE_MESSAGE )
    LinLowSendWakeUpFrame(LIN_I_CHANNEL_PARA_ONLY);
  #if defined (SIO_LL_NO_WUP_FRAME_CONFIRMATION)
    /* Waiting now for header transmission/reception */
    FpSetMuteMode(LIN_I_CHANNEL_PARA_ONLY);
    /* Hardware is not able to confirm transmitted wakeup frame. Call confirmation from here */
    ApplFpWakeupIndication(LIN_I_CHANNEL_PARA_ONLY);
  #endif
 #endif
  }
}
#endif
/* CODE CATEGORY 3 END*/


/******************************************************************************************/
/*    FUNCTION:  FpConfigureResponse                                                      */
/******************************************************************************************/
/**
 *   @brief   Sets the mode of the frame response
 *
 *            Dependent on the frame, the direction (Rx, Tx or ignore), the checksum model
 *            and the data length is set.
 *
 *   @param_i channel The interface/channel which is used
 *
 *   @param   vMessageInfo Contains the message direction, the data length and the checksum type.
 *
 *   @return  No return value
 *
 *******************************************************************************************/
/* CODE CATEGORY 1 START*/
static void FpConfigureResponse(LIN_I_CHANNEL_TYPE_FIRST tMessageInfoType vMessageInfo)
{
#if defined ( SIO_LL_APISTYLE_MESSAGE )
 #if defined ( LIN_ENABLE_DEBUG ) || defined ( LIN_ENABLE_T_HEADER_MAX ) || defined ( LIN_ENABLE_T_FRAME_MAX )
  vuint8 bRetSendMsg;
 #endif
#endif
  set_pbFpMsgBuf(linchannel, get_pbMhMsgBuffer_BufferPointer(linchannel));   /* Set the local pointer to internal buffer */

#if defined ( SIO_LL_APISTYLE_MESSAGE )
    /* Request the message transmission */
 #if defined ( LIN_ENABLE_DEBUG )
  bRetSendMsg = LinLowSendMessageFrame(LIN_I_CHANNEL_PARA_FIRST getbFpCurrentProtectedId(linchannel), vMessageInfo.MsgDirection, \
                         vMessageInfo.MsgDataLength, vMessageInfo.MsgChecksumType, get_pbFpMsgBuf(linchannel));

  LinAssertDynamic(linchannel, !bRetSendMsg,  kLinErrorMessageOverrun);
 #else
  #if defined ( LIN_ENABLE_T_HEADER_MAX ) || defined ( LIN_ENABLE_T_FRAME_MAX )
  bRetSendMsg = LinLowSendMessageFrame(LIN_I_CHANNEL_PARA_FIRST getbFpCurrentProtectedId(linchannel), vMessageInfo.MsgDirection, \
                         vMessageInfo.MsgDataLength, vMessageInfo.MsgChecksumType, get_pbFpMsgBuf(linchannel));
  #else
  (void)        LinLowSendMessageFrame(LIN_I_CHANNEL_PARA_FIRST getbFpCurrentProtectedId(linchannel), vMessageInfo.MsgDirection, \
                         vMessageInfo.MsgDataLength, vMessageInfo.MsgChecksumType, get_pbFpMsgBuf(linchannel));
  #endif
 #endif

 #if defined ( LIN_ENABLE_T_HEADER_MAX ) || defined ( LIN_ENABLE_T_FRAME_MAX )
  if (( vMessageInfo.MsgDirection == kMessageDirectionIgnore ) || (bRetSendMsg != 0))
  {
    CancelFpTimer(linchannel);
  }
  else
  {
  #if defined ( SIO_LL_APITYPE_HEADER_IND )
    /* Start Response Timeout observation */
    SetFpTimerIncResponseObs(linchannel, get_ResponseTimeoutValue(linchannel, vMessageInfo.MsgDataLength));
  #else
    /* Start Frame Timeout observation */
    SetFpTimerIncResponseObs(linchannel, get_HeaderTimeoutValue(linchannel) + get_ResponseTimeoutValue(linchannel, vMessageInfo.MsgDataLength));
  #endif
  }
 #endif
#endif /* SIO_LL_APISTYLE_MESSAGE */
}
/* CODE CATEGORY 1 END*/



#if defined ( LIN_ECUTYPE_SLAVE )
 #if defined ( SIO_LL_ENABLE_BAUDRATE_INFORMATION )
  #if defined ( SIO_ENABLE_BAUDRATE_DETECT )
/*******************************************************************************************/
/*    CALLBACK FUNCTION:  ApplSioBaudrateInformation                                       */
/*******************************************************************************************/
/**
 *   @brief   Indication of a detected baud rate
 *
 *            The callback function is called by the SIO driver detection of a valid baud
 *            rate. The given baud rate is an index to the currently detected baud rate.
 *
 *   @param_i channel The interface/channel which received the byte
 *
 *   @param   bBaudrate  The baud rate detected
 *
 *   @return  No return value
 *
 *******************************************************************************************/
/* CODE CATEGORY 1 START*/
void ApplSioBaudrateInformation ( LIN_I_CHANNEL_TYPE_FIRST vuint8 bBaudrate ) /* PRQA S 1330 *//* MD_LIN_DRV_16.4_A */
{
   #if defined ( LIN_ENABLE_BAUDRATE_INFORMATION )
  if ( bLinCurrentBaudrate != bBaudrate )
  {
    ApplLinBaudrateInformation ( LIN_I_CHANNEL_PARA_FIRST bBaudrate );
  }
   #endif
   #if defined ( LIN_ENABLE_T_HEADER_MAX ) || \
       defined ( LIN_ENABLE_T_FRAME_MAX )  || \
       defined ( LIN_ENABLE_BAUDRATE_INFORMATION )
  bLinCurrentBaudrate = bBaudrate;
   #endif /* LIN_ENABLE_T_HEADER_MAX || LIN_ENABLE_T_FRAME_MAX */
}
/* CODE CATEGORY 1 END*/
  #endif /* SIO_ENABLE_BAUDRATE_DETECT */
 #endif /* SIO_LL_ENABLE_BAUDRATE_INFORMATION */
#endif /* LIN_ECUTYPE_SLAVE */

#if defined ( SIO_LL_APISTYLE_MESSAGE )
/*******************************************************************************************/
/*    CALLBACK FUNCTION:  ApplLinLowWakeUpIndication                                       */
/*******************************************************************************************/
/* CODE CATEGORY 1 START*/
void  ApplLinLowWakeUpIndication(LIN_I_CHANNEL_TYPE_ONLY) /* PRQA S 1330 *//* MD_LIN_DRV_16.4_A */
{

 #if defined ( LIN_APISTYLE_LIN ) && ( LIN_PROTOCOLVERSION_VALUE <= 0x20u )
  if ( get_bFpConnectionState(linchannel) != 0 )
 #endif
  {
    /* reset bus idle timer with any LIN interrupt */
 #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
    if (get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_13)
    {
      SetNmBusIdleTimerStart13(linchannel);
    }
    else
 #endif
    {
      SetNmBusIdleTimerStart(linchannel);
    }
    ApplFpWakeupIndication(LIN_I_CHANNEL_PARA_ONLY);
  }
}
/* CODE CATEGORY 1 END*/

 #if defined ( SIO_LL_APITYPE_HEADER_IND )
/*******************************************************************************************/
/*    CALLBACK FUNCTION:  ApplLinLowHeaderIndication                                       */
/*******************************************************************************************/
/* CODE CATEGORY 1 START*/
vuint8 ApplLinLowHeaderIndication(LIN_I_CHANNEL_TYPE_FIRST vuint8 bProtectedId) /* PRQA S 1330 *//* MD_LIN_DRV_16.4_A */
{
  /* reset bus idle timer with any LIN interrupt */
  #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
  if (get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_13)
  {
    SetNmBusIdleTimerStart13(linchannel);
  }
  else
  #endif
  {
    SetNmBusIdleTimerStart(linchannel);
  }

  #if defined ( LIN_ECUTYPE_SLAVE )
  /* Save local copy of current protected id */
  setbFpCurrentProtectedId(linchannel, bProtectedId); /* may generate warning in some configurations (LIN1.3, VectorAPI,..) */  /* PRQA S 3218 *//* MD_LIN_DRV_8.7 */
  #endif

  /* SIO driver API SIO_LL_APITYPE_HEADER_IND is used. Header is indicated, by the SIO driver. */
  ApplFpHeaderIndication(LIN_I_CHANNEL_PARA_FIRST bProtectedId);
  return(0);
}
/* CODE CATEGORY 1 END*/

 #endif

 #if defined ( SIO_LL_APITYPE_CLEAR_BUS_IDLE )
/*******************************************************************************************/
/*    CALLBACK FUNCTION:  ApplLinLowClearBusIdle                                           */
/*******************************************************************************************/
/* CODE CATEGORY 1 START*/
void ApplLinLowClearBusIdle(LIN_I_CHANNEL_TYPE_ONLY) /* PRQA S 1330 *//* MD_LIN_DRV_16.4_A */
{
  /* Confirmation/indication of transmitted/received Synch break field */
  #if defined ( LIN_APISTYLE_LIN ) && ( LIN_PROTOCOLVERSION_VALUE <= 0x20u )
  if ( get_bFpConnectionState(linchannel) != 0 )
  #endif
  {
  /* reset bus idle timer with any LIN interrupt */
  #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
    if (get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_13)
    {
      SetNmBusIdleTimerStart13(linchannel);
    }
    else
  #endif
    {
      SetNmBusIdleTimerStart(linchannel);
    }
  }
}
/* CODE CATEGORY 1 END*/

 #endif

/*******************************************************************************************/
/*    CALLBACK FUNCTION:  ApplLinLowRxMsgIndication                                        */
/*******************************************************************************************/
/* CODE CATEGORY 1 START*/
vuint8 ApplLinLowRxMsgIndication(LIN_I_CHANNEL_TYPE_FIRST vuint8 identifier, vuint8* pbData) /* PRQA S 1330 *//* MD_LIN_DRV_16.4_A */
{
 #if defined ( LIN_ECUTYPE_SLAVE ) && defined ( SIO_LL_APITYPE_MESSAGE_IND )
  tLinFrameHandleType tempCurFrameHandle;
  tLinFrameHandleType bLoopcount;
 #endif

 #if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
 identifier=identifier;
 #endif

 #if defined ( LIN_APISTYLE_LIN ) && ( LIN_PROTOCOLVERSION_VALUE <= 0x20u )
  if ( get_bFpConnectionState(linchannel) != 0 )
 #endif
  {
    /* reset bus idle timer with any LIN interrupt */
 #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
    if (get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_13)
    {
      SetNmBusIdleTimerStart13(linchannel);
    }
    else
 #endif
    {
      SetNmBusIdleTimerStart(linchannel);
    }

    /* Cancel frame timeout observation */
    CancelFpTimer(linchannel);

 #if defined ( LIN_ECUTYPE_SLAVE ) && defined ( SIO_LL_APITYPE_MESSAGE_IND )
    set_pbFpMsgBuf(linchannel, get_pbMhMsgBuffer_BufferPointer(linchannel));

    if ( identifier == 0x3Cu )
    {
      /* Handling of master request frame */
      /* Save handle in local message buffer for indication handling */
      tempCurFrameHandle  = get_MasterReqHandle(linchannel);
    }
  #if defined ( LIN_ENABLE_DIAG_FRAMES )
    else if ( identifier == 0x3Du )
    {
      /* Handling of Slave Response Frame */
      /* Save handle in local message buffer for indication handling */
      tempCurFrameHandle  = get_SlaveRespHandle(linchannel);
    }
  #endif
    else
    {
      /* Set handle to invalid handle */
      tempCurFrameHandle  = kLinInvalidHandle;
      if ( identifier != kLinInvalidProtectedId )
      {
        /* Check whether the protected ID is in the ID list */
        /* Protected ID must be different to kLinInvalidProtectedId. Is an invalid ID and used as invalid flag. */
        for ( bLoopcount = 0; bLoopcount < kLinNumberOfConfigurablePIDs; bLoopcount++ )
        {
          if ( ( cabLinSlaveProtectedIdTbl[bLoopcount] != kLinInvalidProtectedId ) &&
               ( (cabLinSlaveProtectedIdTbl[bLoopcount]&0x3Fu) == identifier ) )
          {
            /* ID is processed by the node. The index is the current handle */
            tempCurFrameHandle  = bLoopcount;
            break;
          }
        }
      }
      else
      {
        /* no search performed, because kLinInvalidProtectedId is used as invalid Protected id */
      }
    }

    /* store tempCurFrameHandle into global variable */
    set_pbMhMsgBuffer_FrmHandle(linchannel, tempCurFrameHandle);
 #endif

    /* copy received data to LIN driver message buffer */
    VStdMemCpyRamToRam(get_pbFpMsgBuf(linchannel), pbData, 8);

    ApplFpResponseNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kMessageDirectionRx);
  }
  return(0);
}
/* CODE CATEGORY 1 END*/

/*******************************************************************************************/
/*    CALLBACK FUNCTION:  ApplLinLowRxMsgIndication                                        */
/*******************************************************************************************/
/* CODE CATEGORY 1 START*/
vuint8 ApplLinLowTxMsgIndication(LIN_I_CHANNEL_TYPE_FIRST vuint8 identifier, vuint8* pbData) /* PRQA S 1330 *//* MD_LIN_DRV_16.4_A */
{
 #if defined ( LIN_ECUTYPE_SLAVE ) && defined ( SIO_LL_APITYPE_MESSAGE_IND )
  tLinFrameHandleType tempCurFrameHandle;
  tLinFrameHandleType bLoopcount;
 #endif
 #if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
 pbData=pbData;
 identifier=identifier;
 #endif
 #if defined ( LIN_APISTYLE_LIN ) && ( LIN_PROTOCOLVERSION_VALUE <= 0x20u )
  if ( get_bFpConnectionState(linchannel) != 0 )
 #endif
  {
    /* reset bus idle timer with any LIN interrupt */
 #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
    if (get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_13)
    {
      SetNmBusIdleTimerStart13(linchannel);
    }
    else
 #endif
    {
      SetNmBusIdleTimerStart(linchannel);
    }

    /* Cancel frame timeout observation */
    CancelFpTimer(linchannel);
 #if defined ( LIN_ECUTYPE_SLAVE ) && defined ( SIO_LL_APITYPE_MESSAGE_IND )
    if ( identifier == 0x3Cu )
    {
      /* Handling of master request frame */
      /* Save handle in local message buffer for indication handling */
      tempCurFrameHandle  = get_MasterReqHandle(linchannel);
    }
  #if defined ( LIN_ENABLE_DIAG_FRAMES )
    else if ( identifier == 0x3Du )
    {
      /* Handling of Slave Response Frame */
      /* Save handle in local message buffer for indication handling */
      tempCurFrameHandle  = get_SlaveRespHandle(linchannel);
    }
  #endif
    else
    {
      /* Set handle to invalid handle */
      tempCurFrameHandle  = kLinInvalidHandle;
      if ( identifier != kLinInvalidProtectedId )
      {
        /* Check whether the protected ID is in the ID list */
        /* Protected ID must be different to kLinInvalidProtectedId. Is an invalid ID and used as invalid flag. */
        for ( bLoopcount = 0; bLoopcount < kLinNumberOfConfigurablePIDs; bLoopcount++ )
        {
          if ( ( cabLinSlaveProtectedIdTbl[bLoopcount] != kLinInvalidProtectedId ) &&
               ( (cabLinSlaveProtectedIdTbl[bLoopcount]&0x3Fu) == identifier ) )
          {
            /* ID is processed by the node. The index is the current handle */
            tempCurFrameHandle  = bLoopcount;
            break;
          }
        }
      }
      else
      {
        /* no search performed, because kLinInvalidProtectedId is used as invalid Protected id */
      }
    }

    /* store tempCurFrameHandle into global variable */
    set_pbMhMsgBuffer_FrmHandle(linchannel, tempCurFrameHandle);
 #endif

    ApplFpResponseNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kMessageDirectionTx);
  }

  return(0);
}
/* CODE CATEGORY 1 END*/

/*******************************************************************************************/
/*    CALLBACK FUNCTION:  ApplLinLowErrorIndication                                        */
/*******************************************************************************************/
/* CODE CATEGORY 1 START*/
#if defined ( SIO_LL_EXTENDED_ERROR_INDICATION )
void ApplLinLowErrorIndication(LIN_I_CHANNEL_TYPE_FIRST vuint8 error, vuint8 bProtectedId, vuint8 bBusIdleTimer) /* PRQA S 1330 *//* MD_LIN_DRV_16.4_A */
#else
void ApplLinLowErrorIndication(LIN_I_CHANNEL_TYPE_FIRST vuint8 error, vuint8 bProtectedId) /* PRQA S 1330 *//* MD_LIN_DRV_16.4_A */
#endif
{
 #if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  bProtectedId = bProtectedId;
 #endif
 #if defined ( LIN_APISTYLE_LIN ) && ( LIN_PROTOCOLVERSION_VALUE <= 0x20u )
  if ( get_bFpConnectionState(linchannel) != 0 )
 #endif
  {
 #if defined ( V_CPU_MAC710X )                     || \
     defined ( V_CPU_MPC55XX )
  #if defined ( SIO_LL_EXTENDED_ERROR_INDICATION )
    if ( bBusIdleTimer != SIO_ALLOW_BUS_IDLE_TIMEOUT )
  #else
    if ( error != kLinLowSynchError )
  #endif
 #endif
    {
      /* reset bus idle timer with any LIN interrupt */
 #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
      if (get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_13)
      {
        SetNmBusIdleTimerStart13(linchannel);
      }
      else
 #endif
      {
        SetNmBusIdleTimerStart(linchannel);
      }
    }
    /* Cancel frame timeout observation */
    CancelFpTimer(linchannel);

    /* Mapping SIO driver error codes to LIN driver Error codes */
    switch (error)
    {
      case (vuint16)kLinLowHeaderTimeout:
        ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_HeaderTimeout);
      break;

      case (vuint16)kLinLowSynchError:
 #if defined ( LIN_ECUTYPE_SLAVE )
        /* monitoring error */
        ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_HeaderRxSynchField);
 #endif
      break;

      case (vuint16)kLinLowIdParityError:
 #if defined ( LIN_ECUTYPE_SLAVE )
 #endif
      break;

      case (vuint16)kLinLowNoResponseTimeout:
        ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_RespOmittedTimeout);
      break;

      case (vuint16)kLinLowIncompResponseTimeout:
        ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_RespIncompTimeout);
      break;

      case (vuint16)kLinLowChecksumError:
        ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_RespRxChecksum);
      break;

      case (vuint16)kLinLowMonitoringError:
        ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_RespTxMonitoring);
      break;

      case (vuint16)kLinLowFrameError:
        ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_RespRxFormat);
      break;

 #if defined (SIO_LL_ENABLE_T_BUS_IDLE_BY_HARDWARE)
      case (vuint16)kLinLowBusIdle:
        /* bus idle detected by LIN hardware */
        LinDoBusIdleHandling(LIN_I_CHANNEL_PARA_ONLY);
      break;

  #if defined (SIO_LL_ENABLE_T_NO_WAKEUP_BY_HARDWARE)
      case kLinLowNobusWakeUp:
        /* Wakeup timeout observation and timer provided by hardware */
        switch ( get_bNmWupTimerState(linchannel) )
        {
          case (vuint16)kNmWupTimerActive_1:
          case (vuint16)kNmWupTimerActive_2:
            /* Timeout after first Wakeup frame  */
            set_bNmWupTimerState(linchannel, (vuint8)(get_bNmWupTimerState(linchannel) + 1));
            /* Repeat transmission of Wakeup frame */
            FpResetMuteMode(LIN_I_CHANNEL_PARA_ONLY);
            FpSendWakeup(LIN_I_CHANNEL_PARA_ONLY);
          break;

          case (vuint16)kNmWupTimerActive_3:
            /* No wakeup after transmission of three wakeup frames. Stay in sleep mode and inform application after delay */
            set_bNmWupTimerState(linchannel, kNmWupTimerIdle);
            FpResetMuteMode(LIN_I_CHANNEL_PARA_ONLY);
            /* Start notification delay timer */
   #if defined ( LIN_ENABLE_COMPATIBILITY_MODE )
            if (get_bCurrentProtocolVersion(linchannel) == kLinProtocolCompatibility_13)
            {
              Start_bNmNoWupDelayTimer13(linchannel);
            }
            else
   #endif
            {
              Start_bNmNoWupDelayTimer(linchannel);
            }
          break;
          default:
            /* nothing to do here */
          break;
        }
  #endif /* LIN_ENABLE_NO_WAKEUP_TIMER */

      break; /* PRQA S 3201 *//* MD_LIN_DRV_14.1 */
 #endif /* SIO_LL_ENABLE_T_BUS_IDLE_BY_HARDWARE */

 #if defined ( kLinLowHeaderMonitoringError )
      /* use error only if reported / defined by SIO Driver */
      case (vuint16)kLinLowHeaderMonitoringError:
        ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_HeaderTxMonitoring);
      break;
 #endif

 #if defined ( kLinLowHeaderRxFormat )
      /* use error only if reported / defined by SIO Driver */
      case (vuint16)kLinLowHeaderRxFormat:
        ApplFpErrorNotification(LIN_I_CHANNEL_PARA_FIRST LIN_I_PROTECTED_ID_PARA kFpError_HeaderRxFormat);
      break;
 #endif

      default:
        /* Error is not passed to application. Do nothing here  */
      break;
    }
  }
} /* PRQA S 6030 *//* MD_LIN_METRIC_STCYC */
/* CODE CATEGORY 1 END*/
#endif /* SIO_LL_APISTYLE_MESSAGE */


/* @} end of grpFrmProcessor */

/* module specific MISRA deviations:
  MD_LIN_DRV_1.1:
     Reason: Runtime and code efficient implementation of message handles force high nesting.
     Risk: High nesting depth is hard to review and error prone.
     Prevention: Specific test cases which reach the inner code and also code inspection.

  MD_LIN_DRV_1.2
     Reason: NullScheduleTable is defined as NULL Pointer. Code is protected with different variable.
     Risk: Dereferencing to a NULL pointer may have undefined behaviour.
     Prevention: Code inspection and test with different schedule tables in the component test.

  MD_LIN_DRV_3.1:
     Reason: @ necessary as character to support Doxygen documentation.
     Risk: None. All known compiler support @ in comments.
     Prevention: N/A

  MD_LIN_DRV_5.1:
     Reason: Externally defined function name with more than 31 characters.
     Risk: A compiler may incorrectly assign/call function with similar names.
     Prevention: Code is only for measurement of timing and filtered out for deliveries.

  MD_LIN_DRV_6.4:
     Reason: Type of bitfields is specified by compiler vendor.
     Risk: Invalid access to bitfield and unpredictible behaviour in pepending code.
     Prevention: Any compiler microcontroller combination has to be verified in the component test.

  MD_LIN_DRV_8.7
     Reason: Depending on the specific configuration the variable is only used in one function.
     Risk: Unnecessary usage of RAM.
     Prevention: N/A

  MD_LIN_DRV_11.5:
     Reason: Usage of lib copy function uses cast without const qualifier. Type of pointer is given by LIN standard.
     Risk: Incorrect implementation of copy routine may change pointer.
     Prevention: Component test has to check the correct behaviour of the lib copy routine.

  MD_LIN_DRV_13.7:
     Reason: Expression always true in some configurations.
     Risk: None. If this is the case the compiler will remove dead code.
     Prevention: Code inspection and test of the different variants in the component test.

  MD_LIN_DRV_14.1:
     Reason: Expression always true in some configurations.
     Risk: None. If this is the case the compiler will remove dead code.
     Prevention: Code inspection and test of the different variants in the component test.

  MD_LIN_DRV_14.4:
     Reason: Preprocessor check together with runtime checks would require doubled code segments. Removing gotos
     would cause a high risk of new issues.
     Risk: Code maintenance is difficult and error prone.
     Prevention: Code inspection and test cases for the different variants.

  MD_LIN_DRV_16.4_A:
     Reason: Low level driver uses a separate namespace (sio) for parameters
     Risk: None.
     Prevention: N/A

  MD_LIN_DRV_16.4_B:
     Reason: Vector and LIN API implemented together but using different parameter names
     which prevent identical names for both cases.
     Risk: None.
     Prevention: N/A

  MD_LIN_DRV_17.4:
     Reason: Usage of array index would indicate that the first element of the array is accessed only.
     However the array is processed element by element.
     Risk: Access to unintended element.
     Prevention: Code inspection and test cases.

  MD_LIN_DRV_19.1:
     Reason: FBL memory mapping requires inclusion of MemMap.h several times.
     Risk: MemMap.h is provided by the integrator, hence many risks may occur, caused by wrong implementation of this file.
     Prevention: Code inspection of MemMap.h by the FBL integrator.

  MD_LIN_DRV_19.10:
     Reason: Usage of braces would before index access would be syntactical incorrect.
     Risk: As no expressions are used for this parameters but only variables there is no dedicated risk.
     Prevention: Test of the macros in the component test.

  MD_LIN_DRV_19.13:
     Reason: Prevention of double definition of signal access macros with two similar APIs
     Risk: If the API cannot be used due to K&R compiler type an alternative API is provided without # character
     Prevention: Additional API provided without # character usage.

  MD_LIN_METRIC_STCYC:
     Reason: No separation of functionality into sub-functions due to higher voted requirements for minimized stack and runtime usage.
     Risk: Understandability and testability might become too complex.
     Prevention: Design and code review + clearly structured and commented code.

  MD_LIN_METRIC_STPTH:
     Reason: No separation of functionality into sub-functions due to higher voted requirements for minimized stack and runtime usage.
     Risk: Understandability and testability might become too complex.
     Prevention: Design and code review + clearly structured and commented code.

  MD_LIN_METRIC_STCAL:
     Reason: Software structure defined by XXX standard. Standard compliance is voted higher than metric threshold.
     Risk: Understandability and testability might become too complex due to fan-out to many functions.
     Prevention: Design and code review + clearly structured and commented code.

  MD_LIN_METRIC_STMIF:
     Reason: Function handles specific task in the overall component behavior; task has different scenarios
     to cover depending on local conditions - this results in deep nesting of control structures.
     Due to there is more common than different code, higher nesting level is accepted to keep code footprint small.
     Risk: Code is difficult to maintain
     Prevention: Design and code review + clearly structured and commented code.


*/



/* End of lin_drv.c  */

