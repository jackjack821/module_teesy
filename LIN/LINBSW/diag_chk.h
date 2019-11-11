/*******************************************************************************
| Project Name: DiagLIN
|    File Name: diag_chk.h
|
|  Description: LINdiag configuration consistency checker.
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2014 Vector Informatik GmbH                 All rights reserved.
|
| This software is copyright protected and proprietary to Vector Informatik GmbH.
| Vector Informatik GmbH grants to you only those rights as set out in the
| license conditions. All other rights remain with Vector Informatik GmbH.
|
| REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
|-------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ---------------------------------------
| Sa           Mishel Shishmanyan        Vector Informatik GmbH
| Ap           Andreas Pick              Vector Informatik GmbH
| Svh          Sven Hesselmann           Vector Informatik GmbH
| Bmo          Bastian Molkenthin        Vector Informatik GmbH
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date        Ver      Author  Description
| ----------  -------  ------  -------------------------------------------------
| 2004-07-09  1.00.00  Sa      First implementation
| 2007-05-16  1.01.00  Ap      ESCAN00020779: Support for new LIN Tp interface
|                              ESCAN00020780: Compile warning due to implicit cast to smaller type
| 2008-04-07  1.02.00  Svh     ESCAN00025886: Support Rx Single Frame Only of TpLin
| 2008-06-30  1.03.00  Ap      ESCAN00027967: Report tester present command to application
| 2009-01-30  1.04.00  Ap      ESCAN00032693: Session control enabled
| 2011-08-22  1.05.00  Sa      ESCAN00052746: TesterPresent service not fully UDS compliant
| 2012-11-08  1.06.00  Ap      ESCAN00062456: Service active timeout observation
| 2013-03-04  1.06.01  Ap      ESCAN00065558: Compatibility to LinTp
| 2013-11-27  1.06.02  Ap      ESCAN00072256: Access to suppress positive response bit
| 2013-12-16  1.07.00  Bmo     ESCAN00071108: Response pending frames support enabled
|                              ESCAN00072484: Access to NAD of diagnostic request
| 2014-01-13  1.07.01  Bmo     ESCAN00072939: Abort diagnostic response after failed response pending transmission
********************************************************************************/
#if !defined (__DIAG_CHECK_H__)
# define __DIAG_CHECK_H__

/*----------------------------
Version check
----------------------------*/
# if ((DIAGLIN_SLAVECU_VERSION != 0x0107u) || \
      (DIAGLIN_SLAVECU_RELEASE_VERSION != 0x01u))
#  error "Checker-Header files versions are inconsistent!"
# endif

/*GE-T test code, release error warning*/
#define kLinDiagDataBufferLength             255
#define LINDIAG_DISABLE_DEBUG_MODE
#define LINDIAG_DISABLE_RCR_RP_SUPPORT
#define LINDIAG_DISABLE_SESSION_MANAGEMENT
#define LINDIAG_DISABLE_ON_S1_TIMEOUT_NOTIFICATION
#define kLinDiagCallCycleTime                10
#define LINDIAG_DISABLE_NR_ON_RES_SID
#define LINDIAG_DISABLE_MULTIPLE_SERVICE_CALL
#define LINDIAG_DISABLE_NEG_RES_ON_BUFF_OVERRUN
#define LINDIAG_ENABLE_USER_SERVICE_SUPPORT
#define LINDIAG_DISABLE_TX_CONFIRMATION
#define LINDIAG_ENABLE_SERVICE_10H
#define LINDIAG_ENABLE_SERVICE_11H
#define LINDIAG_ENABLE_SERVICE_27H
#define LINDIAG_ENABLE_SERVICE_28H
#define LINDIAG_ENABLE_SERVICE_3EH
#define LINDIAG_DISABLE_SERVICE_85H
#define LINDIAG_ENABLE_SERVICE_22H
#define LINDIAG_ENABLE_SERVICE_23H
#define LINDIAG_DISABLE_SERVICE_24H
#define LINDIAG_ENABLE_SERVICE_3DH
#define LINDIAG_ENABLE_SERVICE_2EH
#define LINDIAG_DISABLE_SERVICE_14H
#define LINDIAG_DISABLE_SERVICE_19H
#define LINDIAG_ENABLE_SERVICE_2FH
#define LINDIAG_DISABLE_SERVICE_31H
#define LINDIAG_DISABLE_SERVICE_34H
#define LINDIAG_DISABLE_SERVICE_35H
#define LINDIAG_DISABLE_SERVICE_36H
#define LINDIAG_DISABLE_SERVICE_37H

/*----------------------------
Configuration check
----------------------------*/
# if defined (kLinDiagDataBufferLength)
#  if (kLinDiagDataBufferLength == 0)
#   error "Invalid (zero) buffer size!"
#  endif
# else
#  error "Missing buffer size setting!"
# endif

/************************ LINDIAG_XXXABLE_SESSION_MANAGEMENT ***********************/
# if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT)
#  if defined (kLinDiagS1Ticks)
#   if (kLinDiagS1Ticks != 0)
/* Config ok */
#   else
#    error "Invalid (zero) setting for TesterPresent timeout!"
#   endif
#  else
#   error "Missing kLinDiagS1Ticks define!"
#  endif
# else
#  if defined (LINDIAG_DISABLE_SESSION_MANAGEMENT)
/* Config ok */
#  else
#   error "Missing LINDIAG_XXXABLE_SESSION_MANAGEMENT switch!"
#  endif
# endif

/************************ LINDIAG_XXXABLE_RCR_RP_SUPPORT ***********************/
# if defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)
#  if defined (kLinDiagP2Ticks)
#   if (kLinDiagP2Ticks != 0)
/* Config ok */
#   else
#    error "Invalid (zero) setting for P2 time!"
#   endif
#  else
#   error "Missing kLinDiagP2Ticks define!"
#  endif
#  if defined (kLinDiagP2ExtTicks)
#   if (kLinDiagP2ExtTicks >= kLinDiagP2Ticks)
/* Config ok */
#   else
#    error "The P2Ext time must be >= the P2 time!"
#   endif
#  else
#   error "Missing kLinDiagP2ExtTicks define!"
#  endif
# else
#  if defined (LINDIAG_DISABLE_RCR_RP_SUPPORT)
#   if defined (LINDIAG_ENABLE_RCR_RP_CONFIRMATION)
#    error "RP confirmation callback can only be used if RP support is enabled!"
#   else
/* Config ok */
#   endif
/* Config ok */
#  else
#   error "Missing LINDIAG_XXXABLE_RCR_RP_SUPPORT switch!"
#  endif
# endif

/************************ LINDIAG_XXXABLE_NR_ON_RES_SID ***********************/
# if defined (LINDIAG_ENABLE_NR_ON_RES_SID)
/* Config ok */
# else
#  if defined (LINDIAG_DISABLE_NR_ON_RES_SID)
/* Config ok */
#  else
#   error "Missing LINDIAG_XXXABLE_NR_ON_RES_SID switch!"
#  endif
# endif

/************************ LINDIAG_XXXABLE_ON_S1_TIMEOUT_NOTIFICATION ***********************/
# if defined (LINDIAG_ENABLE_ON_S1_TIMEOUT_NOTIFICATION)
/* Config ok */
# else
#  if defined (LINDIAG_DISABLE_ON_S1_TIMEOUT_NOTIFICATION)
/* Config ok */
#  else
#   error "Missing LINDIAG_XXXABLE_ON_S1_TIMEOUT_NOTIFICATION switch!"
#  endif
# endif

/************************ LINDIAG_XXXABLE_MULTIPLE_SERVICE_CALL ***********************/
# if defined (LINDIAG_ENABLE_MULTIPLE_SERVICE_CALL)
/* Config ok */
# else
#  if defined (LINDIAG_DISABLE_MULTIPLE_SERVICE_CALL)
/* Config ok */
#  else
#   error "Missing LINDIAG_XXXABLE_MULTIPLE_SERVICE_CALL switch!"
#  endif
# endif

/************************ LINDIAG_XXXABLE_NEG_RES_ON_BUFF_OVERRUN ***********************/
# if defined (LINDIAG_ENABLE_NEG_RES_ON_BUFF_OVERRUN)
/* Config ok */
# else
#  if defined (LINDIAG_DISABLE_NEG_RES_ON_BUFF_OVERRUN)
/* Config ok */
#  else
#   error "Missing LINDIAG_XXXABLE_NEG_RES_ON_BUFF_OVERRUN switch!"
#  endif
# endif

/************************ LINDIAG_XXXABLE_UNKNOWN_SERVICE_SUPPORT ***********************/
# if defined (LINDIAG_ENABLE_USER_SERVICE_SUPPORT)
/* Config ok */
# else
#  if defined (LINDIAG_DISABLE_USER_SERVICE_SUPPORT)
/* Config ok */
#  else
#   error "Missing LINDIAG_XXXABLE_USER_SERVICE_SUPPORT switch!"
#  endif
# endif

#endif /*__DIAG_CHECK_H__*/
