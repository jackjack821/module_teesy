/*******************************************************************************************/
/** @file    lin_drv_os.h
*   @brief   Export interface of the LIN driver used by the "operating system"
*
*            This file provides the API to access the init functions and cyclic task
*            functions provided by the LIN driver.
*            Dependent on the configuration, either the LIN API of the LIN specification
*            or the enhanced Vector API is enabled.
*            The cyclic task LinFastTimerTask() is independent
*            of the selected API.
*
********************************************************************************************/

/*******************************************************************************************/
/** @page     lin_os_h_header Header information of lin_os.h
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
*   @endverbatim
********************************************************************************************
*  @par          Revision History
*  @verbatim
*
*   Date        Ver   Author   Description
*   2004-04-16  2.0   Wr       Rework of the implementation for LIN 2.0 support
*   2004-08-30  2.1   Wr       Layout modifications
*   2004-02-21  2.2   Svh      Parameter in Indexed corrected
*   2007-01-11  2.3   Ap       LIN 2.1 support (NotificationTask removed)
*   2008-01-08  2.4   Ap       ESCAN00023918: Memory mapping support added
*   2012-05-03  2.5   Ap       ESCAN00058689: Slave specific define for indexed implementation
*
*  \endverbatim
********************************************************************************************/


#ifndef __LIN_OS_H__
 #define __LIN_OS_H__


/*******************************************************************************************/
/* Version                  (abcd: Main version ab Sub Version cd )                        */
/*******************************************************************************************/
 #define LIN_DRIVER_OS_VERSION                                        0x0205u
 #define LIN_DRIVER_OS_RELEASE_VERSION                                0x00u

/*******************************************************************************************/
/*       COMMON API PART                                                                   */
/*******************************************************************************************/


/*******************************************************************************************/
/*    API FUNCTION:  LinFastTimerTask                                                      */
/*******************************************************************************************/
/**
 *   @brief   (M,S) Task for the observation of short timeouts
 *
 *             The LinFastTimerTask is used to observe the following timeouts
 *             - Header Max Length
 *             - Frame max length
 *             - Wakeup repetition delay (T tobrk)
 *             - N_As for node configuration service responses
 *
 *
 *   @param_i linchannel The interface/channel the task call is relevant for
 *
 *   @return  void
 *
 *   @context Function can be called from task or interrupt context
 *
 *   @pre     No precondition
 *
 *   @note    The short call cycle required here may be difficult to provide
 *            on task level. So the function is designed to be called also
 *            from interrupt level. However the LinFastTimerTask() call may not interrupt
 *            the LIN interrupt service function.
 ********************************************************************************************/
/* CODE CATEGORY 2 START*/
extern void LinFastTimerTask (void);
/* CODE CATEGORY 2 END*/

 #if defined ( LIN_APISTYLE_VECTOR )
/*******************************************************************************************/
/*       VECTOR API (COVERS THE LIN API)                                                   */
/*******************************************************************************************/


/*******************************************************************************************/
/*    API FUNCTION:  LinInitPowerOn                                                        */
/*******************************************************************************************/
/**
 *   @brief   (M,S) Initialization of the driver core and all channels.
 *
 *            LinInitPowerOn performs the initialization of the driver core,
 *            all channels and the associated hardware.
 *
 *   @return  success True, if call has been accepted and successfully executed.
 *
 *   @context Function must be called from task context
 *
 *   @pre     The global interrupt must be disabled when calling the function.
 *
 *   @note    For a handling of permanent problems, LinInit() may be called.
 *
 *******************************************************************************************/
/* CODE CATEGORY 4 START*/
extern vuint8 LinInitPowerOn (void);
/* CODE CATEGORY 4 END*/

/*******************************************************************************************/
/*    API FUNCTION:  LinInit                                                               */
/*******************************************************************************************/
/**
 *   @brief   (M,S) Initialization of the channel dependent data
 *
 *            LinInit performs the initialization of the channel dependent data
 *            and the associated hardware channel.
 *            The function is called by LinInitPowerOn(). For a handling of permanent
 *            problems, LinInit may be called directly by the application.
 *
 *   @param_i linchannel The interface/channel the task call is relevant for
 *
 *   @return  void
 *
 *   @context Function must be called from task context. Calling from interrupt
 *            context is not allowed.
 *
 *   @pre     Global interrupts must be disabled.
 *
 *******************************************************************************************/
/* CODE CATEGORY 4 START*/
extern void LinInit(void);
/* CODE CATEGORY 4 END*/

/*******************************************************************************************/
/**
 *   @brief   Type of the return value of LinScheduleTask
 *
 *            Dependent on the required information about the LinScheduleTask
 *            action, the return value may provide the index of the next index,
 *            the current index or both indexes.
 *
 *******************************************************************************************/

/*******************************************************************************************/
/*    API FUNCTION:  LinSlowTimerTask                                                      */
/*******************************************************************************************/
/**
 *     @brief   (M,S) Task for the observation of longer timeouts
 *
 *              The LinSlowTimerTask is used to observe the following Timeouts
 *              - No Wakeup indication delay (T t3brk)
 *              - Bus Idle
 *
 *     @param_i linchannel The interface/channel the task call is relevant for
 *
 *     @return  void
 *
 *     @context Function must be called from task context. Calling from interrupt
 *              context is not allowed.
 *
 *     @pre     No precondition.
 *
********************************************************************************************/
/* CODE CATEGORY 2 START*/
extern void LinSlowTimerTask (void);
/* CODE CATEGORY 2 END*/

 #else /*  #if defined (LIN_APISTYLE_LIN) */

/*******************************************************************************************/
/*       LIN API (CORRESPONDING TO LIN SPEC)                                               */
/*******************************************************************************************/

/*******************************************************************************************/
/*    API FUNCTION:  l_sys_init                                                            */
/*******************************************************************************************/
/**
 *    @brief     (M,S) Initialization of the LIN Core  (LIN API)
 *
 *               l_sys_init() initializes the channel independent variables.
 *               the function l_ifc_init must be  called afterwards
 *
 *    @context   Function must be called from task context. Calling from interrupt
 *               context is not allowed.
 *
 *    @pre       global interrupt must be disabled
 *
 *    @param     void
 *
 *    @return    zero if init success, non zero, if init failed
 ********************************************************************************************/
/* CODE CATEGORY 4 START*/
extern l_bool l_sys_init(void);
/* CODE CATEGORY 4 END*/

/*******************************************************************************************/
/*    API FUNCTION:  l_ifc_init                                                            */
/*******************************************************************************************/
/**
 *     @brief     (M,S) Initialization of the interface iii
 *
 *     @param_i   iii the interface/channel which should be initialized
 *
 *     @return    void
 *
 *     @context   Function must be called from task context. Calling from interrupt
 *                context is not allowed.
 *
 *     @pre       global interrupt must be disabled and l_sys_init must be called before
 *
 ********************************************************************************************/
   #if ( LIN_PROTOCOLVERSION_VALUE <= 0x20u )
/* CODE CATEGORY 4 START*/
extern void   l_ifc_init(void);
/* CODE CATEGORY 4 END*/
   #else
/* CODE CATEGORY 4 START*/
extern l_bool l_ifc_init(void);
/* CODE CATEGORY 4 END*/
   #endif


 #endif /* API_STYLE */

#endif /* end of lin_os.h */
