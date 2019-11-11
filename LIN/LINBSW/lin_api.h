/*******************************************************************************************/
/** @file    lin_api.h
*   @brief   General include file for the application to access the LIN driver services
*
*            This file must be used by the application to access all LIN driver services.
*            The application must not use the file lin_inc.h, which is reserved to be used
*            by the LIN driver itself.
*
********************************************************************************************/

/*******************************************************************************************/
/** @page     lin_api_h_header Header information of lin_api.h
********************************************************************************************
    @par      copyright
    @verbatim

    Copyright (c) 2000 - 2010 Vector Informatik GmbH          All rights reserved.

    This software is copyright protected and proprietary to Vector Informatik GmbH.
    Vector Informatik GmbH grants to you only those rights as set out in the
    license conditions. All other rights remain with Vector Informatik GmbH.

    @endverbatim
********************************************************************************************
*   @par      Authors
*   @verbatim
*
*        Initials  Name                    Company
*        Wr        Hans Waaser             Vector Informatik GmbH
*        Fki       Friedrich Kiesel        Vector Informatik GmbH
*   @endverbatim
********************************************************************************************
*  @par          Revision History
*  @verbatim
*
*      Date        Ver    Author   Description
*      2004-04-16  2.0    Wr       Rework of the implementation for LIN 2.0 support
*      2004-08-30  2.1    Wr       Changed copyright text
*      2010-05-06  2.2    Fki      ESCAN00042785: Support mixed AUTOSAR - Canbedded configurations
*
*  \endverbatim
********************************************************************************************/

#if !defined(__LIN_API_H__)
 #define __LIN_API_H__

 #include "v_inc.h"             /* Include container for controller specific header files */

 #include "drv_par.h"           /* Signal oriented access to the message buffers provided in drv.par.c */

 #include "sio_cfg.h"           /* Access th the SIO Driver API relevant for the application */
 #include "sio_drv.h"

 #if defined VGEN_ENABLE_LIN_CBD_MSR_MIXED_CONFIG
  #include "lin_cfg_cbd.h"      /* Configuration of the features and APIs of the LIN driver */
 #else
  #include "lin_cfg.h"          /* Configuration of the features and APIs of the LIN driver */
 #endif

 #include "lin_par_i.h"         /* Configuration specific macros and prototypes for internal use*/
 #include "lin_par.h"           /* Configuration specific macros and prototypes to be used by the application */

 #include "lin_drv.h"           /* Functions, callbacks and variables provided by the LIN driver */
 #include "lin_drv_os.h"        /* API functions of the LIN driver for initialization and cyclic tasks */

#endif

