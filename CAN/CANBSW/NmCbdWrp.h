/*********************************************************************************************************************/
/*!
 * \file
 * \par      copyright
 * \verbatim
 *  Copyright (c) 2006-2016 by Vector Informatik GmbH. All rights reserved.
 * 
 *  This software is copyright protected and proprietary to Vector Informatik GmbH.
 *  Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *  All other rights remain with Vector Informatik GmbH.
 * \endverbatim
 */
/*  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  NmCbdWrp.h
 *      Project:  CANbedded Wrapper for AUTOSAR Network Management
 *       Module:  Nm_AsrNmCanWrapperExt
 *    Generator:  -
 *
 *  Description:  Header of CANbedded Wrapper for AUTOSAR Network Management
 *                AUTOSAR Release 3
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Frank Triem                   Tri           Vector Informatik GmbH
 *  Markus Drescher               vismdr        Vector Informatik GmbH
 *  Oliver Hornung                visoh         Vector Informatik GmbH
 *  Markus Schuster               vissrk        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  1.00.00   2006-02-23  Tri     ESCAN00015285 Creation of component
 *  1.01.00   2006-03-10  Tri     ESCAN00015634 Compiler error due to undeclared identifier
 *  1.02.00   2006-04-26  Tri     ESCAN00015863 Type and interrupt lock service compatibility
 *                                ESCAN00016176 CanResetBusXXX interrupted by CAN-Interrupt
 *  2.00.00   2007-06-22  visoh   ESCAN00021192 Adaptation to AUTOSAR NM 2.1
 *                                ESCAN00022964 No changes
 *  2.01.00   2008-01-08  visoh   ESCAN00023947 Extension for a pure adaptation layer
 *  3.00.00   2008-03-03  visoh   ESCAN00025876 Adaptation to AUTOSAR NM 3.0
 *  3.01.00   2008-06-18  visoh   ESCAN00027671 No changes
 *  3.01.01   2008-07-01  visoh   ESCAN00028006 No changes
 *  3.01.02   2008-11-17  visoh   ESCAN00031367 No changes
 *  3.02.00   2009-04-07  visoh   ESCAN00031814 No changes
 *                                ESCAN00034467 Adaptation to changes in AUTOSAR NM
 *  3.03.00   2010-03-23  visoh   ESCAN00041477 Added fast-slow BusOff handling; reworked NM BusOff Support;
 *                                              Improvements (Optimizations / MISRA compliance / Assertion handling)
 *                                ESCAN00041480 Added QNX support
 *  3.03.01   2010-06-18  visoh   ESCAN00042648 No changes in this file
 *  3.04.00   2011-03-02  visoh   ESCAN00042517 Improvements
 *                                ESCAN00042447 No changes in this file
 *  3.05.00   2014-05-03  vissrk  ESCAN00057295 Support CanNm version 4.18.00 and above
 *                                ESCAN00074080 No changes in this file
 *  3.06.00   2016-01-15  vismdr  ESCAN00074222 No changes in this file
 *                                ESCAN00074225 No changes in this file
 *                                ESCAN00087040 Added error code kCbdWrpNullPointerPassed
 *                                ESCAN00087577 Added ApplCbdWrpBusOffChangeFastToSlow() function declaration
 *********************************************************************************************************************/

#ifndef NM_ASRNMCANWRAPPEREXT_HEADER
# define NM_ASRNMCANWRAPPEREXT_HEADER

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "v_cfg.h"                                                           /* Include Vector configuration header */
# include "v_def.h"                                                          /* Include Vector type defintion header */
# include "nmcbdwrp_cfg.h"                                         /* Include CANbedded Wrapper configuration header */
# include "CanNm_Cfg.h"                                                        /* Include CanNm configuration header */
# include "CanNm.h"                                                                          /* Include CanNm header */
# if defined ( VGEN_ENABLE_NM_OSEK_D ) && !defined ( VGEN_ENABLE_IF_ASRIFCAN )
#  include "NmIf_Cfg.h"                                                        /* Include NM Interface Configuration */
# else
/* coding -v99 */ /* static check does not care about configuration and header for OSEK NM is named nm_cfg.h */
#  include "Nm_Cfg.h"                                                          /* Include NM Interface Configuration */
/* coding +v99 */
# endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : NM_ASRNMCANWRAPPEREXT CQComponent : Implementation */
/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
# define NM_ASRNMCANWRAPPEREXT_VERSION            0x0306u
# define NM_ASRNMCANWRAPPEREXT_RELEASE_VERSION    0x00u

/* Channel handle for application callback functions */
# if ( kCbdWrpNumberOfChannels == 1u )
/* PRQA S 3460 1 */ /* MD_CBD_19.4 */
#  define CBDWRP_CHANNEL_APPLTYPE_ONLY    void
#  define CBDWRP_CHANNEL_APPLTYPE_FIRST
#  define CBDWRP_CHANNEL_APPLPARA_ONLY
#  define CBDWRP_CHANNEL_APPLPARA_FIRST
# else
#  define CBDWRP_CHANNEL_APPLTYPE_ONLY    const NetworkHandleType nmChannelHandle
#  define CBDWRP_CHANNEL_APPLTYPE_FIRST   const NetworkHandleType nmChannelHandle,
#  define CBDWRP_CHANNEL_APPLPARA_ONLY    nmChannelHandle
#  define CBDWRP_CHANNEL_APPLPARA_FIRST   nmChannelHandle,
# endif

# if defined ( CBDWRP_ENABLE_ASSERTIONS )
/* Error codes of assertions */
#  define kCbdWrpInvalidCanChannel        0x01u
#  define kCbdWrpInvalidSysChannel        0x02u
#  define kCbdWrpBusOffInRecovery         0x10u
#  define kCbdWrpInvalidTxHandle          0x20u
#  define kCbdWrpInvalidTxDlc             0x21u
#  define kCbdWrpNullPointerPassed        0x22u
# endif

/* Module Ids */
# define kCbdWrpModuleIdNm                0x1Eu
# define kCbdWrpModuleIdCanNm             0x1Fu
# define kCbdWrpModuleIdCbdWrp            0x20u

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if defined( CBDWRP_ENABLE_GET_CONTEXT ) || defined( CBDWRP_ENABLE_SET_CONTEXT ) || \
  ((defined( VGEN_ENABLE_MDWRAP ) || defined( VGEN_ENABLE_QWRAP )) && defined( VQNX_ENABLE_CONTEXT_SWITCH ))
/*--- QNX support ---------------------------------------------------------*/
/* Type that contains all internal variables */
typedef struct
{
# if defined CBDWRP_ADAPTATION_LAYER
# else
  vuint16 cbdWrpBusOffTimer[kCbdWrpNumberOfChannels];
  vuint8  cbdWrpBusOffTCounter[kCbdWrpNumberOfChannels];
#  if defined( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
  vuint8  cbdWrpBusOffFlag[kCbdWrpNumberOfChannels];
#  endif
# endif
  vuint32 cbdWrpMagicNumber;
} tCbdWrpModuleContextStruct;

typedef tCbdWrpModuleContextStruct* tCbdWrpModuleContextStructPtr;
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/* Exported version of component */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kCbdWrpMainVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kCbdWrpSubVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kCbdWrpReleaseVersion;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/*--------- CANbedded Wrapper services called by CCL / Application -----------*/
# if defined CBDWRP_ADAPTATION_LAYER
# else
/* Initialization of CANbedded Wrapper */
extern void CbdWrpInit( NetworkHandleType nmChannelHandle );
/* Cyclic task of CANbedded Wrapper */
extern void CbdWrpTask( NetworkHandleType nmChannelHandle );
# endif

# if defined( CBDWRP_ENABLE_GET_CONTEXT ) || \
  (defined( VGEN_ENABLE_MDWRAP ) && defined( VQNX_ENABLE_CONTEXT_SWITCH ))
extern void CbdWrpGetModuleContext( tCbdWrpModuleContextStructPtr pContext );
# endif

# if defined( CBDWRP_ENABLE_SET_CONTEXT ) || \
  (defined( VGEN_ENABLE_QWRAP ) && defined( VQNX_ENABLE_CONTEXT_SWITCH ))
extern vuint8 CbdWrpSetModuleContext( tCbdWrpModuleContextStructPtr pContext );
# endif

/*----------- CANbedded Wrapper services called by CAN-Driver ------------*/
/* 
 * The prototypes of the CAN Driver callback services implemented by the 
 * CANbedded Wrapper are defined by the CAN Driver.
 */

/*----------- CANbedded Wrapper services called by AUTOSAR NM ----------------*/
/* 
 * The prototypes of the ASR NM callback services implemented by the 
 * by the CANbedded Wrapper can be found in ComM_Nm.h.
 */

/*---- application (CCL) callback services called by CANbedded Wrapper -------*/
# if defined CBDWRP_ADAPTATION_LAYER
# else
/* Callback functions, to notify about mode changes of Network Management */
extern void ApplCbdWrpBusSleep( CBDWRP_CHANNEL_APPLTYPE_ONLY );
extern void ApplCbdWrpNetStart( CBDWRP_CHANNEL_APPLTYPE_ONLY );
extern void ApplCbdWrpNetStop( CBDWRP_CHANNEL_APPLTYPE_ONLY );
/* Callback functions, to notify about start and stop of communication */
extern void ApplCbdWrpEnableCom( CBDWRP_CHANNEL_APPLTYPE_ONLY );
extern void ApplCbdWrpDisableCom( CBDWRP_CHANNEL_APPLTYPE_ONLY );
/* Callback functions, to notify about start of network */
extern void ApplCbdWrpNetworkStartIndication( CBDWRP_CHANNEL_APPLTYPE_ONLY );
# if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
extern void ApplCbdWrpRestartIndication( CBDWRP_CHANNEL_APPLTYPE_ONLY );
# endif
/* Callback functions, to notify about start and end of BusOff recovery */
extern void ApplCbdWrpBusOffStart( CBDWRP_CHANNEL_APPLTYPE_ONLY );
extern void ApplCbdWrpBusOffEnd( CBDWRP_CHANNEL_APPLTYPE_ONLY );
#  if defined ( CBDWRP_ENABLE_FASTBUSOFFRECOVERY_CHANGE_CALLBACK )
/* ESCAN00087577 */
extern void ApplCbdWrpBusOffChangeFastToSlow( CBDWRP_CHANNEL_APPLTYPE_ONLY );
#  endif

# endif /* CBDWRP_ADAPTATION_LAYER */

# if defined ( CBDWRP_ENABLE_ASSERTIONS ) || \
  ( (!defined ( CBDWRP_ENABLE_ASR_ERROR_REPORT ) ) && \
  ( ( NM_DEV_ERROR_DETECT == STD_ON ) || ( CANNM_DEV_ERROR_DETECT == STD_ON ) ) )
/* Callback function to report development errors */
extern void ApplCbdWrpFatalError( CBDWRP_CHANNEL_APPLTYPE_FIRST 
                                V_MEMROM1 vuint8 V_MEMROM2 moduleId, V_MEMROM1 vuint8 V_MEMROM2 errorCode );
# endif

#endif /* NM_ASRNMCANWRAPPEREXT_HEADER */

/**********************************************************************************************************************
 *  END OF FILE: NmCbdWrp.h
 *********************************************************************************************************************/
