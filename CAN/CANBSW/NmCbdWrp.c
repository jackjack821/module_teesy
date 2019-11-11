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
 *         File:  NmCbdWrp.c
 *      Project:  CANbedded Wrapper for AUTOSAR Network Management
 *       Module:  Nm_AsrNmCanWrapperExt
 *    Generator:  -
 *
 *  Description:  Implementation of CANbedded Wrapper for AUTOSAR Network Management
 *                AUTOSAR Release 3
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Frank  Triem                  Tri           Vector Informatik GmbH
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
 *                                ESCAN00022964 Support Rx during BusOff as soon as possible
 *  2.01.00   2008-01-08  visoh   ESCAN00023947 Extension for a pure adaptation layer
 *  3.00.00   2008-03-03  visoh   ESCAN00025876 Adaptation to AUTOSAR NM 3.0
 *  3.01.00   2008-06-18  visoh   ESCAN00027671 Adapted global interrupt handling
 *  3.01.01   2008-07-01  visoh   ESCAN00028006 No changes
 *  3.01.02   2008-11-17  visoh   ESCAN00031367 Adapted interrupt handling
 *  3.02.00   2009-04-07  visoh   ESCAN00031814 Additional error check
 *                                ESCAN00034467 Adaptation to changes in AUTOSAR NM
 *  3.03.00   2010-03-23  visoh   ESCAN00041477 Added fast-slow BusOff handling; reworked NM BusOff Support;
 *                                              Improvements (Optimizations / MISRA compliance / Assertion handling)
 *                                ESCAN00041480 Added QNX support
 *  3.03.01   2010-06-18  visoh   ESCAN00042648 Removed CanResetBusSleep during initialization
 *  3.04.00   2011-03-02  visoh   ESCAN00042517 Adapted implementation to design; improvements
 *                                ESCAN00042447 Adapted CAN interrupt handling
 *  3.05.00   2014-05-03  vissrk  ESCAN00057295 Support CanNm version 4.18.00 and above
 *                                ESCAN00074080 No changes in this file
 *  3.06.00   2016-01-15  vismdr  ESCAN00074222 Adapted definition of CBDWRP_ENABLE_USE_PDUINFOTYPE macro
 *                                ESCAN00074225 Adapted definition of CBDWRP_ENABLE_USE_PDUINFOTYPE macro
 *                                ESCAN00087040 Added CbdWrpCanTxConfirmation function definition
 *                                ESCAN00087577 Call ApplCbdWrpBusOffChangeFastToSlow() when BusOff Threshold Counter
 *                                              is decremented to 0
 *********************************************************************************************************************/

#define NM_ASRNMCANWRAPPEREXT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "NmCbdWrp.h"                                                      /* Include interface of CANbedded Wrapper */
#include "can_inc.h"                                                       /* Include CAN Driver Include Header File */
#include "can_par.h"                                                     /* Include CAN Driver Parameter Header File */
#include "CanIf.h"                                                                           /* Include CanIf header */
#include "CanNm_Cbk.h"                                                              /* Include CanNm Callback header */
#include "Can_def.h"                                                                        /* Include CanDrv header */

#if defined( CBDWRP_ENABLE_ASR_ERROR_REPORT )
#else
# if ( CANNM_DEV_ERROR_DETECT  == STD_ON ) || ( NM_DEV_ERROR_DETECT  == STD_ON )
#  include "Det.h"                                                                       /* Include interface of DET */
# endif
#endif

#if defined ( CBDWRP_ADAPTATION_LAYER )
#else
# include "Nm.h"                                                                              /* Include NmIf Header */
# include "ComM_Nm.h"                                                                /* Include ComM callback header */
#endif

#define kCanDriverBusoff        0x01U             /* CAN driver is in recovery phase after bus off */
/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Compare Header File Version */
#if( NM_ASRNMCANWRAPPEREXT_VERSION != 0x0306u )
# error "The included header NmCbdWrp.h is incompatible with the NmCbdWrp.c version."
#endif
#if( NM_ASRNMCANWRAPPEREXT_RELEASE_VERSION != 0x00u )
# error "The included header NmCbdWrp.h is incompatible with the NmCbdWrp.c version."
#endif

#if defined ( CBDWRP_ADAPTATION_LAYER )
#else
# if( NM_ASRNMCANWRAPPEREXT_COMM_NM_VERSION != 0x0306u )
#  error "The included header ComM_Nm.h is incompatible with the NmCbdWrp.c version."
# endif
# if( NM_ASRNMCANWRAPPEREXT_COMM_NM_RELEASE_VERSION != 0x00u )
#  error "The included header ComM_Nm.h is incompatible with the NmCbdWrp.c version."
# endif
#endif

#if( NM_ASRNMCANWRAPPEREXT_CANIF_VERSION != 0x0306u )
# error "The included header CanIf.h is incompatible with the NmCbdWrp.c version."
#endif
#if( NM_ASRNMCANWRAPPEREXT_CANIF_RELEASE_VERSION != 0x00u )
# error "The included header CanIf.h is incompatible with the NmCbdWrp.c version."
#endif

#if defined( CBDWRP_ENABLE_ASR_ERROR_REPORT )
#else
# if ( CANNM_DEV_ERROR_DETECT  == STD_ON ) || ( NM_DEV_ERROR_DETECT  == STD_ON )
#  if( NM_ASRNMCANWRAPPEREXT_DET_VERSION != 0x0306u )
#   error "The included header Det.h is incompatible with the NmCbdWrp.c version."
#  endif
#  if( NM_ASRNMCANWRAPPEREXT_DET_RELEASE_VERSION != 0x00u )
#   error "The included header Det.h is incompatible with the NmCbdWrp.c version."
#  endif
# endif
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
/* Definitions for channel mapping */
#if( kCbdWrpNumberOfChannels > 1u )
# define CBDWRP_LOCAL_CHANNEL_IDX             (localChannel)
# define CBDWRP_LOCAL_CHANNEL_IDX_IND         (CanNm_SystemToNmChannelInd[nmChannelHandle])
#else
# define CBDWRP_LOCAL_CHANNEL_IDX             ((NetworkHandleType)0u)
# define CBDWRP_LOCAL_CHANNEL_IDX_IND         ((NetworkHandleType)0u)
#endif

/* Definitions for Appl channel indirection */
#if( kCbdWrpNumberOfChannels == 1u )
# define CBDWRP_CHANNEL_APPLTYPE_IND_ONLY
# define CBDWRP_CHANNEL_APPLTYPE_IND_FIRST
#else
# define CBDWRP_CHANNEL_APPLTYPE_IND_ONLY     ((NetworkHandleType)CanNm_LChannelConfig[CBDWRP_LOCAL_CHANNEL_IDX].CANNM_CHANNEL_ID)
# define CBDWRP_CHANNEL_APPLTYPE_IND_FIRST    ((NetworkHandleType)CanNm_LChannelConfig[CBDWRP_LOCAL_CHANNEL_IDX].CANNM_CHANNEL_ID),
#endif

/* Channel handle for HIS CAN-Driver functions */
#if defined( C_SINGLE_RECEIVE_CHANNEL )
# define CBDWRP_CHANNEL_CANPARA_ONLY
# define CBDWRP_CHANNEL_CANPARA_IND_ONLY
#else
# if( kCbdWrpNumberOfChannels == kCbdWrpNumberOfCanChannels )
#  define CBDWRP_CHANNEL_CANPARA_ONLY         CBDWRP_LOCAL_CHANNEL_IDX
#  define CBDWRP_CHANNEL_CANPARA_IND_ONLY     CBDWRP_LOCAL_CHANNEL_IDX_IND
# else
#  define CBDWRP_CHANNEL_CANPARA_ONLY         (CanNm_NmToCanChannelInd[CBDWRP_LOCAL_CHANNEL_IDX])
#  define CBDWRP_CHANNEL_CANPARA_IND_ONLY     (CanNm_NmToCanChannelInd[CBDWRP_LOCAL_CHANNEL_IDX_IND])
# endif
#endif

/* Parameter for BusOff recovery timer */
#if( kCbdWrpNumberOfChannels > 1u )
# define CBDWRP_BUS_OFF_RECOVERY_TIME_FAST    (CbdWrpBusOffRecoveryTimeFast[CBDWRP_LOCAL_CHANNEL_IDX])
# define CBDWRP_BUS_OFF_RECOVERY_TIME_SLOW    (CbdWrpBusOffRecoveryTime[CBDWRP_LOCAL_CHANNEL_IDX])
# define CBDWRP_BUS_OFF_THRESHOLD             (CbdWrpBusOffThreshold[CBDWRP_LOCAL_CHANNEL_IDX])
#else
# define CBDWRP_BUS_OFF_RECOVERY_TIME_FAST    (kCbdWrpBusOffRecoveryTimeFast)
# define CBDWRP_BUS_OFF_RECOVERY_TIME_SLOW    (kCbdWrpBusOffRecoveryTime)
# define CBDWRP_BUS_OFF_THRESHOLD             (kCbdWrpBusOffThreshold)
#endif

/* ESCAN00074222, ESCAN00074225 */
#if defined ( NM_ASRNMCAN_VERSION )
# if ( NM_ASRNMCAN_VERSION >= 0x0418u )
#  define CBDWRP_ENABLE_USE_PDUINFOTYPE
# endif
#endif

#if defined ( CANNM_USE_PDUINFOTYPE )
# if ( CANNM_USE_PDUINFOTYPE == STD_ON )
#  if defined ( CBDWRP_ENABLE_USE_PDUINFOTYPE )
#  else
#   define CBDWRP_ENABLE_USE_PDUINFOTYPE
#  endif
# endif
#endif

/* Parameters for the initialization of the CAN-Bus via CanInit */
#define CbdWrpGetCanInitPara()                ((CanInitHandle)(0u))

/* Calculate timer-off value (vuint16).*/
#define CbdWrpTimerOff                        ((vuint16)0u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/* Version of component */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kCbdWrpMainVersion    = (vuint8)(NM_ASRNMCANWRAPPEREXT_VERSION >> 8u);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kCbdWrpSubVersion     = (vuint8)(NM_ASRNMCANWRAPPEREXT_VERSION  & 0x00FFu);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kCbdWrpReleaseVersion = (vuint8)(NM_ASRNMCANWRAPPEREXT_RELEASE_VERSION);

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#if defined CBDWRP_ADAPTATION_LAYER
#else
/*******************************************************************************
** Function:    CbdWrpInit
**
** Purpose:     Initialization of CANbedded Wrapper.
**
**  Called by:  Application
**
**  Context:    Task level.
**              Reentrant with different channel handles.
**
**  Parameter:  nmChannelHandle : System channel handle 
**
**  Returncode: -
*******************************************************************************/
void CbdWrpInit( NetworkHandleType nmChannelHandle )
{
# if( kCbdWrpNumberOfChannels > 1u )
  /* If there are multiple NM instances the local channel handle is required */
  NetworkHandleType localChannel = CanNm_SystemToNmChannelInd[nmChannelHandle];
# endif
# if defined( CBDWRP_ENABLE_ASSERTIONS )
  if( (nmChannelHandle >= CANNM_NUMBER_OF_SYS_CHANNELS)
#  if( kCbdWrpNumberOfChannels < CANNM_NUMBER_OF_SYS_CHANNELS )
#   if( kCbdWrpNumberOfChannels > 1u )
    || (localChannel == 0xFFu)
#   else
    || (CanNm_SystemToNmChannelInd[nmChannelHandle] == 0xFFu)
#   endif
#  endif
    )
  {
    ApplCbdWrpFatalError( CBDWRP_CHANNEL_APPLPARA_FIRST  kCbdWrpModuleIdCbdWrp, kCbdWrpInvalidSysChannel );
  }
  else
# endif

  {
    /* Init BusOff variables */
    cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX] = CbdWrpTimerOff;
    cbdWrpBusOffThresholdCounter[CBDWRP_LOCAL_CHANNEL_IDX] = CBDWRP_BUS_OFF_THRESHOLD;

# if defined( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
    /* Init BusOff flag */
    cbdWrpDrvCanIsBusOff[CBDWRP_LOCAL_CHANNEL_IDX] = 0u;
# endif

    /* Set the CAN-Driver offline */
    CanOffline( CBDWRP_CHANNEL_CANPARA_ONLY );

    /* Application callback function. The application has to call CanSleep */
    ApplCbdWrpBusSleep( CBDWRP_CHANNEL_APPLPARA_ONLY );
  }

# if defined( CBDWRP_ENABLE_ASSERTIONS ) || ( kCbdWrpNumberOfChannels > 1u )
# else
#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  /* PRQA S 3112 1 */ /* MD_NmCbdWrp_3112 */
  (void)nmChannelHandle;
#  endif
# endif
}

/*******************************************************************************
** Function:    CbdWrpTask
**
** Purpose:     Main function of CANbedded Wrapper
**              BusOff Handling
**              IL has to be released within the application callback if sending
**              of application messages has to be restarted after BusOff.
**
**  Called by:  Application
**
**  Context:    Task level only.
**              Not reentrant.
**
**  Parameter:  nmChannelHandle : System channel handle 
**
**  Returncode: -
*******************************************************************************/
void CbdWrpTask( NetworkHandleType nmChannelHandle )
{
  vuint16 busOffTimer;
  Nm_ModeType nmMode;
  Nm_StateType nmState = NM_STATE_UNINIT;

# if( kCbdWrpNumberOfChannels > 1u )
  /* If there are multiple NM instances the local channel handle is required */
  NetworkHandleType localChannel = CanNm_SystemToNmChannelInd[nmChannelHandle];
# endif
# if defined( CBDWRP_ENABLE_ASSERTIONS )
  if( (nmChannelHandle >= CANNM_NUMBER_OF_SYS_CHANNELS)
#  if( kCbdWrpNumberOfChannels < CANNM_NUMBER_OF_SYS_CHANNELS )
#   if( kCbdWrpNumberOfChannels > 1u )
    || (localChannel == 0xFFu)
#   else
    || (CanNm_SystemToNmChannelInd[nmChannelHandle] == 0xFFu)
#   endif
#  endif
    )
  {
    ApplCbdWrpFatalError( CBDWRP_CHANNEL_APPLPARA_FIRST  kCbdWrpModuleIdCbdWrp, kCbdWrpInvalidSysChannel );
  }
  else
# endif

  {

    CanGlobalInterruptDisable();
    /* Read value consistently */
    busOffTimer = cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX];
    CanGlobalInterruptRestore();

    /* BusOff recovery handling */
    if( busOffTimer != CbdWrpTimerOff )
    {

      /* Ongoing BusOff recovery */
      cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX]--;

      /* End of BusOff recovery? */
      if( 
# if defined( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
        /* Restore Rx Path as soon as possible... */
        (cbdWrpDrvCanIsBusOff[CBDWRP_LOCAL_CHANNEL_IDX] != 0u) && /* PRQA S 3415 */ /* MD_NmCbdWrp_3415 */
# endif
        ( (cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX] == 0u)
# if defined( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
        || (CanGetDriverStatus(CBDWRP_CHANNEL_CANPARA_ONLY) != 0x01U)
# endif
        ) )
      {

# if defined( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
        cbdWrpDrvCanIsBusOff[CBDWRP_LOCAL_CHANNEL_IDX] = 0u;
# endif

        CanGlobalInterruptDisable();
        /* Finish the CAN-Driver BusOff handling */
# if defined( C_SINGLE_RECEIVE_CHANNEL )
        CanResetBusOffEnd( CbdWrpGetCanInitPara() );
# else
        CanResetBusOffEnd( CBDWRP_CHANNEL_CANPARA_ONLY, CbdWrpGetCanInitPara() );
# endif
        CanGlobalInterruptRestore();

# if defined( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
      }
      if( cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX] == 0u )
      {
# endif

        /* Activate Tx Path only if NM is in Network Mode */
        (void)Nm_GetState( nmChannelHandle, &nmState, &nmMode );
        if( nmState > NM_STATE_PREPARE_BUS_SLEEP )
        {
          /* Switch the transmit path on again */
          CanOnline( CBDWRP_CHANNEL_CANPARA_ONLY );
        }

        /* Notify the application about end of BusOff recovery */
        ApplCbdWrpBusOffEnd( CBDWRP_CHANNEL_APPLPARA_ONLY );

      }  /* ( cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX] == 0u ) */

    }  /* ( cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX] != CbdWrpTimerOff ) */
  }
}  /* End of CbdWrpTask */ /* PRQA S 4700 */ /* MD_NmCbdWrp_4700 */

/*******************************************************************************
** Function:    CbdWrpBusOff
**
** Purpose:     Notification about a CAN BusOff.
**              Start BusOff handling.
**              IL has to be set to wait within the application callback due to
**              sending of application messages is not allowed during BusOff.
**
**  Called by:  HIS CAN-Driver
**
**  Context:    Task or interrupt level.
**              Reentrant with different channel handles.
**
**  Parameter:  channel : CAN channel handle
**
**  Returncode: -
*******************************************************************************/
void CbdWrpBusOff( CAN_CHANNEL_CANTYPE_ONLY )
{

# if( kCbdWrpNumberOfChannels > 1u )
#  if( kCbdWrpNumberOfChannels == kCbdWrpNumberOfCanChannels )
  /* Local channel handle */
  NetworkHandleType localChannel = (NetworkHandleType)channel;
#  else
  /* Local channel handle */
  NetworkHandleType localChannel = (NetworkHandleType)CanNm_CanToNmChannelInd[channel];
#  endif
# endif
# if defined( CBDWRP_ENABLE_ASSERTIONS ) && defined( C_MULTIPLE_RECEIVE_CHANNEL )
  if( (channel >= kCbdWrpNumberOfCanChannels)
#  if( kCbdWrpNumberOfChannels < kCbdWrpNumberOfCanChannels )
#   if( kCbdWrpNumberOfChannels > 1u )
    || (localChannel == 0xFFu)
#   else
    || (CanNm_CanToNmChannelInd[channel] == 0xFFu)
#   endif
#  endif
    )
  {
#  if ( kCbdWrpNumberOfChannels == 1u )
    ApplCbdWrpFatalError( kCbdWrpModuleIdCbdWrp, kCbdWrpInvalidCanChannel );
#  else
    ApplCbdWrpFatalError( (NetworkHandleType)channel, kCbdWrpModuleIdCbdWrp, kCbdWrpInvalidCanChannel );
#  endif
  }
  else
# endif

  {

    /* Perform handling only if no BusOff recovery is ongoing */
    if( cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX] == CbdWrpTimerOff )
    {

      /* Switch the transmit path off */
      CanOffline( CAN_CHANNEL_CANPARA_ONLY );

      /* and clear the transmit queue */
      CanGlobalInterruptDisable();
# if defined( C_SINGLE_RECEIVE_CHANNEL )
      CanResetBusOffStart( CbdWrpGetCanInitPara() );
# else
      CanResetBusOffStart( CAN_CHANNEL_CANPARA_ONLY, CbdWrpGetCanInitPara() );
# endif
      CanGlobalInterruptRestore();

      /* application callback function */
      ApplCbdWrpBusOffStart( CBDWRP_CHANNEL_APPLTYPE_IND_ONLY );

      /* Start of BusOff recovery algorithm */
      if( cbdWrpBusOffThresholdCounter[CBDWRP_LOCAL_CHANNEL_IDX] > 0u )
      {
        cbdWrpBusOffThresholdCounter[CBDWRP_LOCAL_CHANNEL_IDX]--;
        /* Fast BusOff recovery */
        cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX] = CBDWRP_BUS_OFF_RECOVERY_TIME_FAST;

# if defined ( CBDWRP_ENABLE_FASTBUSOFFRECOVERY_CHANGE_CALLBACK )
        if (cbdWrpBusOffThresholdCounter[CBDWRP_LOCAL_CHANNEL_IDX] == 0u) /* ESCAN00087577 */
        {
          ApplCbdWrpBusOffChangeFastToSlow( CBDWRP_CHANNEL_APPLTYPE_IND_ONLY );
        }
# endif
      }
      else
      {
        /* Slow BusOff recovery */
        cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX] = CBDWRP_BUS_OFF_RECOVERY_TIME_SLOW;
      }

# if defined( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
      /* Set BusOff Flag */
      cbdWrpDrvCanIsBusOff[CBDWRP_LOCAL_CHANNEL_IDX] = 1u;
# endif

    }  /* cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX] == CbdWrpTimerOff */
# if defined( CBDWRP_ENABLE_ASSERTIONS )
    else
    {
      /* A BusOff must not occur during the BusOff recovery time, since the CAN-Driver is offline */
      ApplCbdWrpFatalError( CBDWRP_CHANNEL_APPLTYPE_IND_FIRST  kCbdWrpModuleIdCbdWrp, kCbdWrpBusOffInRecovery );
    }
# endif

  }
}

/*******************************************************************************
** Function:    ComM_Nm_BusSleepMode
**
** Purpose:     Notifies the application, that network management 
**              has entered sleep state.
**
**  Called by:  NM Interface
**
**  Context:    Task level only.
**              Reentrant with different channel handles.
**
**  Parameter:  nmChannelHandle : System channel handle 
**
**  Returncode: -
*******************************************************************************/
void ComM_Nm_BusSleepMode( const NetworkHandleType nmChannelHandle )
{
# if( kCbdWrpNumberOfChannels > 1u )
  /* If there are multiple NM instances the local channel handle is required */
  NetworkHandleType localChannel = CanNm_SystemToNmChannelInd[nmChannelHandle];
# endif

  /* Pending BusOff recovery? */
  if( cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX] != CbdWrpTimerOff )
  {

    /* Stop ongoing BusOff recovery to avoid start of communication in Bus-Sleep Mode */
# if defined( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
    if( cbdWrpDrvCanIsBusOff[CBDWRP_LOCAL_CHANNEL_IDX] != 0u )
# endif
    {
# if defined( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
      cbdWrpDrvCanIsBusOff[CBDWRP_LOCAL_CHANNEL_IDX] = 0u;
# endif

      CanGlobalInterruptDisable();
# if defined( C_SINGLE_RECEIVE_CHANNEL )
      CanResetBusOffEnd( CbdWrpGetCanInitPara() );
# else
      CanResetBusOffEnd( CBDWRP_CHANNEL_CANPARA_ONLY, CbdWrpGetCanInitPara() );
# endif
      CanGlobalInterruptRestore();
    }

    cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX] = CbdWrpTimerOff;

    /* Notify application about stop of BusOff recovery */
    ApplCbdWrpBusOffEnd( CBDWRP_CHANNEL_APPLPARA_ONLY );
  }

  /* Clear the transmit queue and all hardware transmit objects prior to entering sleep mode */
  CanGlobalInterruptDisable();
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CanResetBusSleep( CbdWrpGetCanInitPara() );
# else
  CanResetBusSleep( CBDWRP_CHANNEL_CANPARA_ONLY, CbdWrpGetCanInitPara() );
# endif
  CanGlobalInterruptRestore();

  /* Application callback function. The application has to call CanSleep */
  ApplCbdWrpBusSleep( CBDWRP_CHANNEL_APPLPARA_ONLY );

# if( kCbdWrpNumberOfChannels == 1u )
#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  /* PRQA S 3112 1 */ /* MD_NmCbdWrp_3112 */
  (void)nmChannelHandle;
#  endif
# endif
}

/*******************************************************************************
** Function:    ComM_Nm_NetworkMode
**
** Purpose:     Notifies the application, that network management has entered network mode.
**              IL has to be started within the application callback
**              in order to send application messages.
**
**  Called by:  NM Interface
**
**  Context:    Task level only.
**              Reentrant with different channel handles.
**
**  Parameter:  nmChannelHandle : System channel handle 
**
**  Returncode: -
*******************************************************************************/
void ComM_Nm_NetworkMode( const NetworkHandleType nmChannelHandle )
{
  /* Switch the transmit path on */
  CanOnline( CBDWRP_CHANNEL_CANPARA_IND_ONLY );

  /* application callback function */
  ApplCbdWrpNetStart( CBDWRP_CHANNEL_APPLPARA_ONLY );

  /* application callback function */
  ApplCbdWrpEnableCom( CBDWRP_CHANNEL_APPLPARA_ONLY );

# if( kCbdWrpNumberOfChannels == 1u )
#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  /* PRQA S 3112 1 */ /* MD_NmCbdWrp_3112 */
  (void)nmChannelHandle;
#  endif
# endif
}

/*******************************************************************************
** Function:    ComM_Nm_PrepareBusSleepMode
**
** Purpose:     Notifies the application, that network management has left network mode.
**              IL has to be stopped within the application callback
**              in order to stop sending application messages.
**
**  Called by:  NM Interface
**
**  Context:    Task level only.
**              Reentrant with different channel handles.
**
**  Parameter:  nmChannelHandle : System channel handle 
**
**  Returncode: -
*******************************************************************************/
void ComM_Nm_PrepareBusSleepMode( const NetworkHandleType nmChannelHandle )
{
  /* application callback function */
  ApplCbdWrpDisableCom( CBDWRP_CHANNEL_APPLPARA_ONLY );

  /* application callback function */
  ApplCbdWrpNetStop( CBDWRP_CHANNEL_APPLPARA_ONLY );

  /* Switch the transmit path off */
  CanOffline( CBDWRP_CHANNEL_CANPARA_IND_ONLY );

# if( kCbdWrpNumberOfChannels == 1u )
#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  /* PRQA S 3112 1 */ /* MD_NmCbdWrp_3112 */
  (void)nmChannelHandle;
#  endif
# endif
}

/*******************************************************************************
** Function:    ComM_Nm_NetworkStartIndication
**
** Purpose:     Indication that some nodes in the network have entered the Network Mode.
**
**  Called by:  NM Interface
**
**  Context:    Task level only.
**              Reentrant with different channel handles.
**
**  Parameter:  nmChannelHandle : System channel handle 
**
**  Returncode: -
*******************************************************************************/
void ComM_Nm_NetworkStartIndication( const NetworkHandleType nmChannelHandle )
{
  /* application callback function */
  ApplCbdWrpNetworkStartIndication( CBDWRP_CHANNEL_APPLPARA_ONLY );

# if( kCbdWrpNumberOfChannels == 1u )
#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  /* PRQA S 3112 1 */ /* MD_NmCbdWrp_3112 */
  (void)nmChannelHandle;
#  endif
# endif
}

# if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/*******************************************************************************
** Function:    ComM_Nm_RestartIndication
**
** Purpose:     Indication that some nodes in the network have already entered
**              bus sleep but need to be restarted.
**
**  Called by:  NM Interface
**
**  Context:    Task level only.
**              Reentrant with different channel handles.
**
**  Parameter:  nmChannelHandle : System channel handle 
**
**  Returncode: -
*******************************************************************************/
void ComM_Nm_RestartIndication( const NetworkHandleType nmChannelHandle )
{
  /* application callback function */
  ApplCbdWrpRestartIndication( CBDWRP_CHANNEL_APPLPARA_ONLY );

# if( kCbdWrpNumberOfChannels == 1u )
#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  /* PRQA S 3112 1 */ /* MD_NmCbdWrp_3112 */
  (void)nmChannelHandle;
#  endif
# endif
}
# endif

#endif /* CBDWRP_ADAPTATION_LAYER */

#if defined( CBDWRP_ENABLE_ASR_ERROR_REPORT )
#else
# if ( ( NM_DEV_ERROR_DETECT == STD_ON ) || ( CANNM_DEV_ERROR_DETECT == STD_ON ) )
/*******************************************************************************
** Function:    Det_ReportError
**
** Purpose:     Service for reporting of development errors.
**
**  Called by:  CanNm
**
**  Context:    Task or interrupt level.
**              Reentrant
**
**  Parameter:  ModuleId : Module ID of calling module
**              ApiId    : ID of API service in which error is detected
**              ErrorId  : ID of detected development error
**
**  Returncode: -
*******************************************************************************/
void Det_ReportError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId )
{
  /* DET services are routed to application */
#  if( kCbdWrpNumberOfChannels == 1u )
  ApplCbdWrpFatalError( (vuint8)ModuleId, ErrorId );
#  else
  ApplCbdWrpFatalError( (NetworkHandleType)InstanceId, (vuint8)ModuleId, ErrorId );
#  endif

#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  /* PRQA S 3112 1 */ /* MD_NmCbdWrp_3112 */
  (void)ApiId;
#   if( kCbdWrpNumberOfChannels == 1u )
  /* PRQA S 3112 1 */ /* MD_NmCbdWrp_3112 */
  (void)InstanceId;
#   endif
#  endif
}
# endif
#endif

#if( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
/*******************************************************************************
** Function:    CanIf_Transmit
**
** Purpose:     Service for transmitting a NM message.
**
**  Called by:  CanNm
**
**  Context:    Task level only.
**              Not reentrant
**
**  Parameter:  CanTxPduId : PDU handle of NM message
**              PduInfoPtr : Pointer to message data
**
**  Returncode: E_OK
**              E_NOT_OK
*******************************************************************************/
Std_ReturnType CanIf_Transmit(PduIdType CanTxPduId, const PduInfoType *PduInfoPtr)
{
  vuint8 databyte;
  Std_ReturnType retVal = E_NOT_OK;

# if defined( CBDWRP_ENABLE_ASSERTIONS )
  /* Check for valid PDU ID */
  if( CanTxPduId >= kCanNumberOfTxObjects )
  {
#  if( kCbdWrpNumberOfChannels == 1u )
    ApplCbdWrpFatalError( kCbdWrpModuleIdCbdWrp, kCbdWrpInvalidTxHandle );
#  else
    ApplCbdWrpFatalError( (NetworkHandleType)CanTxPduId, kCbdWrpModuleIdCbdWrp, kCbdWrpInvalidTxHandle );
#  endif
  }
  /* ESCAN00031814: Check for valid DLC */
  else if( CanGetTxDlc(CanTxPduId) < PduInfoPtr->SduLength )
  {
#  if( kCbdWrpNumberOfChannels == 1u )
    ApplCbdWrpFatalError( kCbdWrpModuleIdCbdWrp, kCbdWrpInvalidTxDlc );
#  else
    ApplCbdWrpFatalError( (NetworkHandleType)CanTxPduId, kCbdWrpModuleIdCbdWrp, kCbdWrpInvalidTxDlc );
#  endif
  }
  else
# endif
  {

# if defined ( CBDWRP_ENABLE_ASRNM_BUSOFF_SUPPORT )
#  if( kCbdWrpNumberOfChannels < kCbdWrpNumberOfCanChannels )
    if( cbdWrpBusOffRecTimer[CanNm_CanToNmChannelInd[CanTxMsgHandleToChannel[CanTxPduId]]] != CbdWrpTimerOff )
#  else
#   if ( kCbdWrpNumberOfCanChannels == 1u )
    if( cbdWrpBusOffRecTimer[0u] != CbdWrpTimerOff )
#   else
    if( cbdWrpBusOffRecTimer[CanTxMsgHandleToChannel[CanTxPduId]] != CbdWrpTimerOff )
#   endif
#  endif
    {
#  if( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
      CanNm_TxConfirmation( CanTxPduId );
#  endif
    }
    else
# endif

    {
      /* Lock Global interrupts to ensure data consistency */
      CanGlobalInterruptDisable();
      /* Copy user data to transmit buffer */
      for (databyte=0u; databyte<PduInfoPtr->SduLength; databyte++)
      {
        CanGetTxDataPtr(CanTxPduId)[databyte] = (vuint8)((PduInfoPtr->SduDataPtr)[databyte]);
      }
      CanGlobalInterruptRestore();

      /* Transmit a NM message */
      if( CanTransmit( (CanTransmitHandle)CanTxPduId ) == kCanTxOk )
      {
        retVal = E_OK;
      }
    }
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function:    CanNm_NmMsgPrecopy
**
** Purpose:     Notification of the reception of a NM message.
**              The NM message range has to be configured in the generation tool.
**
**  Called by:  Data link layer
**
**  Context:    Task or Interrupt level.
**
**  Parameter:  Handle of CAN-object is either a pointer to the data buffer or
**              a handle to the receive object.
**
**  Returncode: kCanCopyData:   Indicates the copy of data to global data buffer.
**              kCanNoCopyData: Finish the action in the data link layer.
*******************************************************************************/
/* PRQA S 3673 1 */ /* MD_NmCbdWrp_3673 */
vuint8 CanNm_NmMsgPrecopy( CanRxInfoStructPtr rxStruct )
{

#if defined( CBDWRP_ENABLE_ASSERTIONS )
  if( (rxStruct->Channel >= kCbdWrpNumberOfCanChannels)
# if( kCbdWrpNumberOfChannels != kCbdWrpNumberOfCanChannels )
    || (CanNm_CanToNmChannelInd[ (rxStruct->Channel) ] == 0xFFu)
# endif
    )
  {
#  if( kCbdWrpNumberOfChannels == 1u )
    ApplCbdWrpFatalError( kCbdWrpModuleIdCbdWrp, kCbdWrpInvalidCanChannel );
#  else
    ApplCbdWrpFatalError( (NetworkHandleType)rxStruct->Channel, kCbdWrpModuleIdCbdWrp, kCbdWrpInvalidCanChannel );
#  endif
  }
  else
#endif

  {
#if defined ( CBDWRP_ENABLE_USE_PDUINFOTYPE )
    PduInfoType pduInfo;
    pduInfo.SduDataPtr = (SduDataPtrType)rxStruct->pChipData;
    pduInfo.SduLength = (PduLengthType)CanRxActualDLC(rxStruct);
#endif
    /* Forward to CanNm */
#if( kCbdWrpNumberOfChannels != kCbdWrpNumberOfCanChannels )
# if defined ( CBDWRP_ENABLE_USE_PDUINFOTYPE )
    CanNm_RxIndication( (PduIdType)(CanNm_CanToNmChannelInd[ (rxStruct->Channel) ]), (P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ))&pduInfo );
# else
    CanNm_RxIndication( (PduIdType)(CanNm_CanToNmChannelInd[ (rxStruct->Channel) ]), (uint8*)(rxStruct->pChipData) );
# endif
#else
# if defined ( CBDWRP_ENABLE_USE_PDUINFOTYPE )
    CanNm_RxIndication( (PduIdType)rxStruct->Channel, (P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ))&pduInfo );
# else
    CanNm_RxIndication( (PduIdType)rxStruct->Channel, (uint8*)(rxStruct->pChipData) );
# endif
#endif
  }

  return kCanNoCopyData;
}

/*******************************************************************************
** Function:    CanNm_NmMsgConfirmation
**
** Purpose:     Notification of the successful transmission of a NM message.
**              The confirmation function has to be configured in the generation tool.
**
**  Called by:  Data link layer
**
**  Context:    Task or Interrupt level.
**
**  Parameter:  Handle of the transmitted message.
**
**  Returncode: -
*******************************************************************************/
void CanNm_NmMsgConfirmation( CanTransmitHandle txObject )
{
#if defined ( CBDWRP_ADAPTATION_LAYER ) && \
  ( ( CANNM_PASSIVE_MODE_ENABLED == STD_ON ) || ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_ON ) )
#else

# if defined( CBDWRP_ENABLE_ASSERTIONS )
  if( (txObject >= kCanNumberOfTxObjects)
#  if( kCbdWrpNumberOfChannels < kCbdWrpNumberOfCanChannels )
    || (CanNm_CanToNmChannelInd[CanTxMsgHandleToChannel[txObject]] == 0xFFu)
#  endif
    )
  {
#  if( kCbdWrpNumberOfChannels == 1u )
    ApplCbdWrpFatalError( kCbdWrpModuleIdCbdWrp, kCbdWrpInvalidTxHandle );
#  else
    ApplCbdWrpFatalError( (NetworkHandleType)txObject, kCbdWrpModuleIdCbdWrp, kCbdWrpInvalidTxHandle );
#  endif
  }
  else
# endif

#endif

  {
#if defined ( CBDWRP_ADAPTATION_LAYER ) || \
    defined ( CBDWRP_ENABLE_RESET_BUSOFF_THRESHOLD_COUNTER_ON_ANY_TX_CONFIRMATION )
    /* ESCAN00087040 */
#else
# if( kCbdWrpNumberOfChannels < kCbdWrpNumberOfCanChannels )
    vuint8 localChannel = CanNm_CanToNmChannelInd[CanTxMsgHandleToChannel[txObject]];
# else
#  if ( kCbdWrpNumberOfCanChannels == 1u )
    vuint8 localChannel = 0x00u;
#  else
    CanChannelHandle localChannel = CanTxMsgHandleToChannel[txObject];
#  endif
# endif

    /* Reset BusOff Threshold */
    cbdWrpBusOffThresholdCounter[localChannel] = CBDWRP_BUS_OFF_THRESHOLD;
#endif

#if( ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF ) )
    /* Forward to CanNm */
    CanNm_TxConfirmation( (PduIdType)txObject );
#endif
  }

#if ( defined ( CBDWRP_ADAPTATION_LAYER ) || ( kCbdWrpNumberOfCanChannels == 1u ) ) && \
  ( ( CANNM_PASSIVE_MODE_ENABLED == STD_ON ) || ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_ON ) )
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  /* PRQA S 3112 1 */ /* MD_NmCbdWrp_3112 */
  (void)txObject;
# endif
#endif

}

#if defined(CBDWRP_ENABLE_RESET_BUSOFF_THRESHOLD_COUNTER_ON_ANY_TX_CONFIRMATION)
/*******************************************************************************
** Function:    CbdWrpCanTxConfirmation
**
** Purpose:     Notification of the successful transmission of any message.
**              The confirmation function has to be configured in the generation tool.
**
**  Called by:  Data link layer
**
**  Context:    Task or Interrupt level.
**
**  Parameter:  Handle of the transmitted message.
**
**  Returncode: -
*******************************************************************************/
/* PRQA S 3673 1 */ /* MD_NmCbdWrp_3673 */
C_CALLBACK_1 void C_CALLBACK_2 CbdWrpCanTxConfirmation(CanTxInfoStructPtr txStruct)
{ /* ESCAN00087040 */
	static vuint8 u8SendHandle1,u8SendHandle2,u8SendHandle3;

	//if(txStruct.Handle==CanTxNWM_AC) {u8SendHandle1=1;}
	//if(txStruct.Handle==CanTxAC_Status_Info) {u8SendHandle2=1;}
	//if(txStruct.Handle==CanTxAC_ReqSts) {u8SendHandle3=1;}


# if defined( CBDWRP_ENABLE_ASSERTIONS )
  if (txStruct == V_NULL)
  {
#  if( kCbdWrpNumberOfChannels == 1u )
    ApplCbdWrpFatalError( kCbdWrpModuleIdCbdWrp, kCbdWrpNullPointerPassed );
#  else
    ApplCbdWrpFatalError( 0u, kCbdWrpModuleIdCbdWrp, kCbdWrpNullPointerPassed );
#  endif
  }
  else if( (txStruct->Channel >= kCbdWrpNumberOfCanChannels)
#  if( kCbdWrpNumberOfChannels < kCbdWrpNumberOfCanChannels )
    || (CanNm_CanToNmChannelInd[txStruct->Channel] == 0xFFu)
#  endif
    )
  {
#  if( kCbdWrpNumberOfChannels == 1u )
    ApplCbdWrpFatalError( kCbdWrpModuleIdCbdWrp, kCbdWrpInvalidTxHandle );
#  else
    ApplCbdWrpFatalError( (NetworkHandleType)txStruct->Channel, kCbdWrpModuleIdCbdWrp, kCbdWrpInvalidTxHandle );
#  endif
  }
  else
# endif
  {
# if( kCbdWrpNumberOfChannels < kCbdWrpNumberOfCanChannels )
    vuint8 localChannel = CanNm_CanToNmChannelInd[txStruct->Channel];
# else
#  if ( kCbdWrpNumberOfCanChannels == 1u )
    vuint8 localChannel = 0x00u;
#  else
    CanChannelHandle localChannel = txStruct->Channel;
#  endif
# endif

    /* Reset BusOff Threshold */
#if 0
	if(u8SendHandle1&&u8SendHandle2**u8SendHandle3)
	{
		cbdWrpBusOffThresholdCounter[localChannel] = CBDWRP_BUS_OFF_THRESHOLD;
	}
#endif
    cbdWrpBusOffThresholdCounter[localChannel] = CBDWRP_BUS_OFF_THRESHOLD;
  }
# if defined( CBDWRP_ENABLE_ASSERTIONS ) || ( kCbdWrpNumberOfChannels < kCbdWrpNumberOfCanChannels ) || ( kCbdWrpNumberOfCanChannels != 1u )
# else
#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  /* PRQA S 3112 1 */ /* MD_NmCbdWrp_3112 */
  (void)txStruct;
#  endif
# endif
}
#endif

#if defined( CBDWRP_ENABLE_GET_CONTEXT ) || \
  (defined( VGEN_ENABLE_MDWRAP ) && defined( VQNX_ENABLE_CONTEXT_SWITCH ))
/*******************************************************************************
** Function:    CbdWrpGetModuleContext
**
** Purpose:     Get the current CANbedded Wrapper module context,
**              i.e. all internal variables
**
**  Called by:  Application
**
**  Context:    Task level only
**
**  Parameter:  pContext: Pointer where the module context shall be copied to
**
**  Returncode: -
*******************************************************************************/
void CbdWrpGetModuleContext( tCbdWrpModuleContextStructPtr pContext )
{
# if defined CBDWRP_ADAPTATION_LAYER
# else
#  if ( kCbdWrpNumberOfChannels > 1u )
  vuint8 localChannel;
#  endif
# endif

  /* Save Magic Number */
  pContext->cbdWrpMagicNumber = (((vuint32)NM_ASRNMCANWRAPPEREXT_VERSION)<<8u)+NM_ASRNMCANWRAPPEREXT_RELEASE_VERSION;

  /* Save context */
# if defined CBDWRP_ADAPTATION_LAYER
# else
#  if ( kCbdWrpNumberOfChannels > 1u )
  for( localChannel=0u; localChannel<kCbdWrpNumberOfChannels; localChannel++ )
#  endif
  {
    pContext->cbdWrpBusOffTimer[CBDWRP_LOCAL_CHANNEL_IDX] = cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX];
    pContext->cbdWrpBusOffTCounter[CBDWRP_LOCAL_CHANNEL_IDX] = cbdWrpBusOffThresholdCounter[CBDWRP_LOCAL_CHANNEL_IDX];
#  if defined( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
    pContext->cbdWrpBusOffFlag[CBDWRP_LOCAL_CHANNEL_IDX] = cbdWrpDrvCanIsBusOff[CBDWRP_LOCAL_CHANNEL_IDX];
#  endif
  }
# endif
}
#endif

#if defined( CBDWRP_ENABLE_SET_CONTEXT ) || \
  (defined( VGEN_ENABLE_QWRAP ) && defined( VQNX_ENABLE_CONTEXT_SWITCH ))
/*******************************************************************************
** Function:    CbdWrpSetModuleContext
**
** Purpose:     Initialize the NM module with the given context,
**              i.e. set all internal variables
**
**  Called by:  Application
**
**  Context:    Task level only
**
**  Parameter:  pContext: Pointer where the module context shall be copied from
**
**  Returncode: 0:  Magic number check failed, context not set
**              1:  Context set successfully
*******************************************************************************/
/* PRQA S 3673 1 */ /* MD_NmCbdWrp_3673 */
vuint8 CbdWrpSetModuleContext( tCbdWrpModuleContextStructPtr pContext )
{
# if defined CBDWRP_ADAPTATION_LAYER
# else
#  if ( kCbdWrpNumberOfChannels > 1u )
  vuint8 localChannel;
#  endif
# endif
  vuint8 retVal = 0u;

  /* Check Magic Number */
  if( pContext->cbdWrpMagicNumber == ((((vuint32)NM_ASRNMCANWRAPPEREXT_VERSION)<<8u)+NM_ASRNMCANWRAPPEREXT_RELEASE_VERSION) )
  {
    retVal = 1u;

    /* Set context */
# if defined CBDWRP_ADAPTATION_LAYER
# else
#  if ( kCbdWrpNumberOfChannels > 1u )
    for( localChannel=0u; localChannel<kCbdWrpNumberOfChannels; localChannel++ )
#  endif
    {
      cbdWrpBusOffRecTimer[CBDWRP_LOCAL_CHANNEL_IDX] = pContext->cbdWrpBusOffTimer[CBDWRP_LOCAL_CHANNEL_IDX];
      cbdWrpBusOffThresholdCounter[CBDWRP_LOCAL_CHANNEL_IDX] = 
        pContext->cbdWrpBusOffTCounter[CBDWRP_LOCAL_CHANNEL_IDX];
#  if defined( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
      cbdWrpDrvCanIsBusOff[CBDWRP_LOCAL_CHANNEL_IDX] = pContext->cbdWrpBusOffFlag[CBDWRP_LOCAL_CHANNEL_IDX];
#  endif
    }
# endif
  }

  return retVal;
}
#endif

/**********************************************************************************************************************
 *  Consistency checks
 *********************************************************************************************************************/

/* Check configuration of CANbedded Wrapper */
#if( CANNM_NUMBER_OF_CANNM_CHANNELS != kCbdWrpNumberOfChannels )
# error "CANbedded Wrapper error: Number of CANbedded Wrapper channels must be equal to the number of CAN NM channels!"
#endif

/* Check configuration of CAN Interface / CAN-Driver */
#if defined( C_SINGLE_RECEIVE_BUFFER ) || defined( C_MULTIPLE_RECEIVE_BUFFER )
# error "CANbedded Wrapper error: Single or Multiple receive buffer usage is not supported!"
#endif
#if defined( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
# if defined( C_ENABLE_DRIVER_STATUS )
# else
#  error "CANbedded Wrapper error: Feature 'CBDWRP_ENABLE_EARLY_BUSOFF_REINIT' requires a DrvCan that supports \
  'C_ENABLE_DRIVER_STATUS'!"
# endif
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL ) && ( kCbdWrpNumberOfChannels > 1u )
# error: "CANbedded Wrapper error: Number of CANbedded Wrapper Channels cannot be greater 1 if \
  C_SINGLE_RECEIVE_CHANNEL is defined (only one CAN Channel available!)!"
#endif

/* Check configuration of AUTOSAR NM modules */
#if( NM_BUSNM_CANNM_ENABLED == STD_OFF )
# error "CANbedded Wrapper error: CAN NM is required!"
#endif
#if( CANNM_NUMBER_OF_CANNM_CHANNELS > NM_NUMBER_OF_NM_CHANNELS )
# error "CANbedded Wrapper error: Number of NM channels cannot be smaller then the number of CAN NM channels!"
#endif

/* Check configuration parameters for the initialization of the CAN-Bus via CanInit */
#if defined( kCanNumberOfInitObjects )
# if( kCanNumberOfInitObjects > kCbdWrpNumberOfCanChannels )
#  error "CANbedded Wrapper error: Only one CAN-Driver initialization object per CAN channel is supported!"
# endif
#endif

/* Check configuration settings for 'Reset BusOff Threshold Counter on any TxConfirmation */ /* ESCAN00087040 */
#if defined(CBDWRP_ENABLE_RESET_BUSOFF_THRESHOLD_COUNTER_ON_ANY_TX_CONFIRMATION)
# if defined(C_ENABLE_CAN_TX_CONF_FCT)
# else
#  error "CANbedded Wrapper error: Common Confirmation needs to be enabled for 'Reset BusOff Threshold Counter on any TxConfirmation'!"
# endif

# if defined(CBDWRP_ADAPTATION_LAYER)
#  error "CANbedded Wrapper error: CANbedded Adaption Layer needs to be disabled for 'Reset BusOff Threshold Counter on any TxConfirmation'!"
# endif
#endif

/**********************************************************************************************************************
 *  ORGANI checks
 *********************************************************************************************************************/

/* module specific MISRA deviations:
 MD_NmCbdWrp_3112:
      Reason:     Dummy statement to avoid compiler warnings.
      Risk:       There is no risk as such statements have no effect on the code.
      Prevention: Code review ensures that there is no effect on the code.
 MD_NmCbdWrp_3415:
      Reason:     Function is called within if statement checking multiple expressions.
      Risk:       Function can contain side effects which may or may not occur depending on the values of the other
                  expressions.
      Prevention: Code review ensures that the called function does not contain side effects.
 MD_NmCbdWrp_3673:
      Reason:     Common sense for Vector CANbedded components.
                  Note that declaring API parameter to const could lead to warnings or problems for some compilers.
      Risk:       Parameter is not defined as const and could be modified within this function.
      Prevention: Code review ensures that the parameter is not modified.
 MD_NmCbdWrp_4700:
      Reason:     This rule is for information purpose only.
      Risk:       No risk, as only information.
      Prevention: N/A
*/

/**********************************************************************************************************************
 *  END OF FILE: NmCbdWrp.c
 *********************************************************************************************************************/
