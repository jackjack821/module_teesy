/* PRQA S 0288 EOF *//* MD_DTL_LIN_3.1 */
/**************************************************************************************************/
/** @file    dtl_api.h  
*   @brief   General include file for the application to access the LIN diagnostic transport
*            layer services   
* 
*            This file must be used by the application to access all DTL services.
*            The application must not use the file dtl_inc.h, which is reserved to be used
*            by the DTL itself. 
*
*****************************************************************************************************/
/****************************************************************************************************/
/** @page     dtl_api_h_header Header information of dtl_api.h
********************************************************************************************
*   @par      copyright
*   @verbatim
*
*   Copyright (c) 2012 Vector Informatik GmbH          All rights reserved.
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
*   Initials  Name                    Company   
*   Wr        Hans Waaser             Vector Informatik GmbH
*   Ap        Andreas Pick            Vector Informatik GmbH
*
*   @endverbatim
*****************************************************************************************************
*   @par          Revision History   
*   @verbatim
*
*    Date         Ver       Author   Description
*    2004-08-30   1.00.00   Wr       First implementation
*    2005-01-07   1.01.00   Wr       Improved comments
*    2012-12-13   1.02.00   Ap       ESCAN00063602: Support mixed MSR and CBD configurations in LinTp component
*
*   \endverbatim
*****************************************************************************************************/

#if !defined(__DTL_API_H__)
#define __DTL_API_H__

#include "v_inc.h"             /* Include container for controller specific header files */

#include "dtl_cfg.h"          /* Configuration of the features and APIs of the DTL */
#include "dtl_par_i.h"        /* Configuration specific parameters and access to parameters provided */   
#include "dtl_lin.h"          /* API function header of the DTL */

#endif

