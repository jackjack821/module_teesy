/* PRQA S 0288 EOF *//* MD_DTL_LIN_3.1 */
/**************************************************************************************************/
/** @file    dtl_inc.h  
*   @brief   include file used by the file dtl_lin.c
*
*            This file must not be used by the application.
*            The application must use the file dtl_api.h to access the API provided
*            to the application
*****************************************************************************************************/
/****************************************************************************************************/
/** @page     dtl_inc_h_header Header information of dtl_inc.h
*****************************************************************************************************
*   @par        copyright
*   @verbatim
* 
*   Copyright (c) 2012 Vector Informatik GmbH          All rights reserved.
*
*   This software is copyright protected and proprietary to Vector Informatik GmbH. 
*   Vector Informatik GmbH grants to you only those rights as set out in the 
*   license conditions. All other rights remain with Vector Informatik GmbH.
*
*   @endverbatim
*****************************************************************************************************
*   @par      Authors
*   @verbatim
*
*        Initials  Name                    Company   
*        Wr        Hans Waaser             Vector Informatik GmbH
*        Ap        Andreas Pick            Vector Informatik GmbH
*   @endverbatim
*****************************************************************************************************
*  @par          Revision History   
*  @verbatim
*
*  Date        Ver        Author   Description
*  2004-07-19  1.00.00    Wr       First implementation
*  2005-01-07  1.01.00    Wr       Improved comments
*  2006-02-16  1.02.00    Ap       Change include order
*  2012-12-13  1.03.00    Ap       ESCAN00063602: Support mixed MSR and CBD configurations in LinTp component
*
*  \endverbatim
*****************************************************************************************************/



#if !defined(__DTL_INC_H__)
#define __DTL_INC_H__

#include "v_inc.h"             /* Include container for controller specific header files */

#include "sio_cfg.h"           /* Configuration of features provided by sio_drv.h */
#include "sio_drv.h"           /* API and callback functions provided by sio_drv.c */

#if defined VGEN_ENABLE_LIN_CBD_MSR_MIXED_CONFIG
# include "lin_cfg_cbd.h"      /* Configuration of the features and APIs of the LIN driver */
#else
# include "lin_cfg.h"           /* Configuration of the API provided in lin_drv_tp.h */
#endif
#include "lin_drv_tp.h"        /* API and callback functions provided by the lin driver */
#include "lin_par_i.h"         /* Access to internal parameters provided by the LIN driver */

#include "dtl_cfg.h"           /* Configuration of the features and APIs of the DTL */
#include "dtl_par_i.h"         /* Configuration specific parameters and access to parameters provided */
#include "dtl_lin.h"           /* API function header of the DTL */


#endif


