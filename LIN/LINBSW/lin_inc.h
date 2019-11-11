/*******************************************************************************************/
/** @file    lin_inc.h
*   @brief   include file used by the file lin_drv.c
*
*            This file must not be used by the application.
*            The application must use the file lin_api.h to access the API provided
*            to the application
********************************************************************************************/

/*******************************************************************************************/
/** @page     lin_inc_h_header Header information of lin_inc.h
********************************************************************************************
*   @par      copyright
*   @verbatim
*
*   Copyright (c) 2000 - 2010 Vector Informatik GmbH          All rights reserved.
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
*        Fki       Friedrich Kiesel        Vector Informatik GmbH
*   @endverbatim
********************************************************************************************
*  @par          Revision History
*  @verbatim
*
*      Date        Ver    Author   Description
*      2004-04-16  2.00   Wr       Rework of the implementation for LIN 2.0 support
*      2004-08-30  2.01   Wr       Changed copyright text
*                                  Added header file for TP API
*      2008-09-25  2.02   Svh      SIO Driver header included before LIN Driver header
*      2010-05-06  2.03   Fki      ESCAN00042785: Support mixed AUTOSAR - Canbedded configurations
*
*  \endverbatim
********************************************************************************************/



#if !defined(__LIN_INC_H__)
#define __LIN_INC_H__

#include "v_inc.h"             /* Include container for controller specific header files */

#include "sio_cfg.h"
#include "sio_par.h"
#include "sio_drv.h"

#if defined VGEN_ENABLE_LIN_CBD_MSR_MIXED_CONFIG
# include "lin_cfg_cbd.h"      /* Configuration of the features and APIs of the LIN driver */
#else
# include "lin_cfg.h"          /* Configuration of the features and APIs of the LIN driver */
#endif

#include "lin_par_i.h"         /* Configuration specific parameters and access to parameters provided */
#include "lin_drv.h"           /* Own header */
#include "lin_drv_os.h"
#if defined (LIN_ENABLE_DIAG_TRANSP_LAYER)
#include "lin_drv_tp.h"
#endif

#endif
