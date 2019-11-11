/* -----------------------------------------------------------------------------
  Filename:    Nm_Cfg.c
  Description: Toolversion: 01.00.22.01.50.07.51.00.00.00
               
               Serial Number: CBD1500751
               Customer Info: Desay SV Automotive Co., Ltd.
                              Package: CBD Geely SLP1
                              Micro: R7F7010233AFP
                              Compiler: Green Hills 6.1.4
               
               
               Generator Fwk   : GENy 
               Generator Module: Nm
               
               Configuration   : D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\XXX_CAN_20180517.gny
               
               ECU: 
                       TargetSystem: Hw_Rh850Cpu
                       Compiler:     GreenHills
                       Derivates:    F1L
               
               Channel "Channel0":
                       Databasefile: D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\FE-5DB&7DA CAN Communication Matrix V1.61_Release LIN2CAN_AC.dbc
                       Bussystem:    CAN
                       Manufacturer: Geely
                       Node:         AC

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2015 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#include "Nm_Cfg.h"
#include "ccl_inc.h"
#include "Nm_Cbk.h"
/* LT Options */

/* Callbacks to Upper Layer function mapping */
#define NM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/***********************************************************************************************************************
*  Nm_StateChangeNotification
**********************************************************************************************************************/
/*! \brief      Notification that the NM state has changed
*  \param[in]  nmPreviousState                   Former state of the Nm state machine
*  \param[in]  nmCurrentState                    Current state of the Nm state machine
*  \context    Function could be called from task level only
*  \note       Called by CanNmMainFunction, FrNmMainFunction, NmTask
**********************************************************************************************************************/
FUNC( void, NM_CODE ) Nm_StateChangeNotification( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONST( Nm_StateType, AUTOMATIC ) nmPreviousState, CONST( Nm_StateType, AUTOMATIC ) nmCurrentState )
{
#if defined ( NM_STATE_REPORT_ENABLED ) || \
  ( (( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || defined ( NM_GW_EXT_ENABLED )) && \
  defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) )
# if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
  VAR( NetworkHandleType, AUTOMATIC ) channel = Nm_SystemToNmChannelInd[nmChannelHandle];
# endif
#endif

#if defined ( NM_STATE_REPORT_ENABLED )
  {
    uint8 nmStateSignal = (uint8)0u;
    if( nmCurrentState == NM_STATE_REPEAT_MESSAGE )
    {
      /* Bus Sleep / Prepare Bus Sleep -> Repeat Message */
      if( nmPreviousState < NM_STATE_READY_SLEEP )
      {
        nmStateSignal = (uint8)nmPreviousState;
      }
# if ( NM_NODE_DETECTION_ENABLED == STD_ON )
      /* Ready Sleep -> Repeat Message */
      else if( nmPreviousState == NM_STATE_READY_SLEEP )
      {
        nmStateSignal = NM_RM_RS;
      }
      /* Normal Operation -> Repeat Message */
      else if( nmPreviousState == NM_STATE_NORMAL_OPERATION )
      {
        nmStateSignal = NM_RM_NO;
      }
# endif
      else
      {
# if ( NM_BUSNM_FRNM_ENABLED == STD_ON )
        /* Synchronize -> Repeat Message */
        nmStateSignal = NM_RM_BSM;
# endif
      }
    }
# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
    else
    {
      if( nmCurrentState == NM_STATE_NORMAL_OPERATION )
      {
        /* Repeat Message -> Normal Operation */
        if( nmPreviousState == NM_STATE_REPEAT_MESSAGE )
        {
          nmStateSignal = NM_NO_RM;
        }
        /* Ready Sleep -> Normal Operation */
        else
        {
          nmStateSignal = NM_NO_RS;
        }
      }
    }
# endif    /* Write Signal depending on channel (HIS Optimization) */
#  if defined ( NM_STATE_REPORT_ENABLED_0 )
    if( NM_CHANNEL_IDX == 0 )
    {
      (void)NM_STATE_REPORT_SIGNAL_0;
    }
#  endif
  }
#endif

#if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#  if defined ( NM_ENABLE_MULTIPLE_NM_USAGE )
  if( Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_NMFIATC ) /* PRQA S 3689 */ /* MD_NmIf_3689 */
#  endif
  {
    /* PRQA S 3689 1 */ /* MD_NmIf_3689 */
    if( (Nm_PbConfigPtr->Nm_PbChannelConfigPtr)[NM_CHANNEL_IDX] != NM_COORD_SEL )
    {
      if ( (nmCurrentState == NM_STATE_READY_SLEEP) || (nmCurrentState == NM_STATE_NORMAL_OPERATION) )
      {
        if ( (nmPreviousState != NM_STATE_READY_SLEEP ) && (nmPreviousState != NM_STATE_NORMAL_OPERATION ) )
        {
          Nm_AbortSleep_BusNm[0] = 1u;
        }
      }
    }
  }
# endif
#endif

#if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || defined ( NM_GW_EXT_ENABLED )
# if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
  if( (Nm_LChannelConfiguration[NM_CHANNEL_IDX].NM_BUS_TYPE == NM_BUSNM_CANOSEKNM) && (nmPreviousState == NM_STATE_BUS_SLEEP) ) /* PRQA S 3689 */ /* MD_NmIf_3689 */
  {
    if( Nm_NotifyNetworkStart[NM_CHANNEL_IDX] == NM_NOTIFYSTARTSLEEP ) /* PRQA S 3689 */ /* MD_NmIf_3689 */
    {
      Nm_NotifyNetworkStart[NM_CHANNEL_IDX] = NM_SUPPRESSNOTIFYSTART; /* PRQA S 3689 */ /* MD_NmIf_3689 */

#  if defined ( UL_Nm_StateChangeNotification )
      UL_Nm_StateChangeNotification( nmChannelHandle, nmPreviousState, nmCurrentState );
#  endif
    }
  }
  else
# endif
#endif
  {
#if defined ( UL_Nm_StateChangeNotification )
    UL_Nm_StateChangeNotification( nmChannelHandle, nmPreviousState, nmCurrentState );
#endif
  }

#if defined ( UL_Nm_StateChangeNotification )
#else
# if ( NM_USE_DUMMY_STATEMENT == STD_ON )
#  if defined ( NM_STATE_REPORT_ENABLED ) || \
  ( (( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || defined ( NM_GW_EXT_ENABLED )) && \
  defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) )
#  else
  /* PRQA S 3112 1 */ /* MD_NmIf_3112 */
  (void)nmChannelHandle;
#  endif
  /* PRQA S 3112 2 */ /* MD_NmIf_3112 */
  (void)nmPreviousState;
  (void)nmCurrentState;
# endif
#endif

}
/***********************************************************************************************************************
 *  Nm_RepeatMessageIndication
 **********************************************************************************************************************/
/*! \brief      Indication that the Repeat Message Bit was set
 *  \context    Function could be called from task level only
 *  \note       Called by CanNmMainFunction, FrNmMainFunction
 **********************************************************************************************************************/
FUNC( void, NM_CODE ) Nm_RepeatMessageIndication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
#if defined ( UL_Nm_RepeatMessageIndication )
  UL_Nm_RepeatMessageIndication( nmChannelHandle );
#else
# if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* PRQA S 3112 1 */ /* MD_NmIf_3112 */
  (void)nmChannelHandle;
# endif
#endif
}
/***********************************************************************************************************************
 *  Nm_TxTimeoutException
 **********************************************************************************************************************/
/*! \brief      Notification that the NM message has timed out
 *  \context    Function could be called from task level only
 *  \note       Called by CanNmMainFunction, FrNmMainFunction
 **********************************************************************************************************************/
FUNC( void, NM_CODE ) Nm_TxTimeoutException( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
#if defined ( UL_Nm_TxTimeoutException )
  UL_Nm_TxTimeoutException( nmChannelHandle );
#else
# if ( NM_USE_DUMMY_STATEMENT == STD_ON )
  /* PRQA S 3112 1 */ /* MD_NmIf_3112 */
  (void)nmChannelHandle;
# endif
#endif
}

#define NM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"



#define NM_START_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

CONST(Nm_LChannelConfigType, NM_CONST) Nm_LChannelConfiguration[NM_NUMBER_OF_NM_CHANNELS] = 
{
  
  {
    NM_BUSNM_CANNM, 
    0u
  }
};
#define NM_STOP_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"


#define NM_START_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

CONST(Nm_LConfigType, NM_CONST) Nm_LConfiguration = 
{
  1u /* NM_NUMBER_OF_CHANNELS */, 
  1u /* NM_NUMBER_OF_SYSTEM_CHANNELS */
};
#define NM_STOP_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"



#define NM_START_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

CONST(Nm_ConfigType, NM_CONST) Nm_Configuration0 = 
{
  0xBABEu /* NM_MAGIC_NUMBER */
};
#define NM_STOP_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"



/* --------------------- Module Data Prototypes --------------------- */
#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
#else

/* ----------- Local 8 Bit Data definitions without initialization need ----------- */
#define NM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || defined ( NM_GW_EXT_ENABLED )
#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
VAR( uint8, NM_VAR_NOINIT ) Nm_NotifyNetworkStart[NM_NUMBER_OF_NM_CHANNELS];
#  endif
VAR( uint8, NM_VAR_NOINIT ) Nm_NetworkStarted[NM_NUMBER_OF_NM_CHANNELS];
# endif

# if defined ( NM_GW_EXT_ENABLED )
VAR( uint8, NM_VAR_NOINIT ) Nm_RemoteSleepFilter[NM_NUMBER_OF_NM_CHANNELS];
VAR( uint8, NM_VAR_NOINIT ) Nm_RemoteWakeupFilter[NM_NUMBER_OF_NM_CHANNELS];
VAR( uint8, NM_VAR_NOINIT ) Nm_NetworkRequested[NM_NUMBER_OF_NM_CHANNELS];
VAR( uint8, NM_VAR_NOINIT ) Nm_WakeupDetected[NM_NUMBER_OF_NM_CHANNELS];
# endif

# if defined ( NM_ENABLE_COORD_SYNC_SUPPORT ) || ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
VAR( uint8, NM_VAR_NOINIT ) Nm_AbortSleep_BusNm[1];
#  else
#   if defined ( NM_GW_EXT_ENABLED )
VAR( uint8, NM_VAR_NOINIT ) Nm_AbortSleep_BusNm[NM_NUMBER_OF_NM_CHANNELS];
#   endif
#  endif
# endif

#define NM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if defined ( NM_ONM_STATE_CHANGE_IND )
/* ----------- Local Data definitions with unspecified size without initialization need ----------- */
#define NM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

VAR( Nm_StateType, NM_VAR_NOINIT ) Nm_OnmState[NM_NUMBER_OF_NM_CHANNELS];
VAR( Nm_StateType, NM_VAR_NOINIT ) Nm_OnmNetworkRequested[NM_NUMBER_OF_NM_CHANNELS];

#define NM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif /* defined ( NM_ONM_STATE_CHANGE_IND ) */

# if defined ( NM_GW_EXT_ENABLED ) || defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
/* ----------- Local 8 Bit Data definitions with frequent access without initialization need ----------- */
#define NM_START_SEC_VAR_FAST_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  if defined ( NM_GW_EXT_ENABLED )
VAR( uint8, NM_VAR_NOINIT_FAST ) Nm_PartEcuActiveChannels[NM_NUMBER_OF_NM_CHANNELS];
#   if ( NM_BUSNM_CANNM_ENABLED == STD_ON )
VAR( uint8, NM_VAR_NOINIT_FAST ) Nm_PartEcuReqChannels[NM_NUMBER_OF_NM_CHANNELS];
#   endif
#  endif

#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
VAR( uint8, NM_VAR_NOINIT_FAST ) Nm_CoordActiveInd[NM_NUMBER_OF_NM_CHANNELS];
VAR( uint8, NM_VAR_NOINIT_FAST ) Nm_CoordSleepInd[NM_NUMBER_OF_NM_CHANNELS];
#  endif

#define NM_STOP_SEC_VAR_FAST_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif

/* ----------- Local 16 Bit Data definitions with frequent access without initialization need ----------- */
#define NM_START_SEC_VAR_FAST_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if defined ( NM_GW_EXT_ENABLED )
VAR( Nm_TimerCounterType, NM_VAR_NOINIT_FAST ) Nm_ChannelActiveTimer[NM_NUMBER_OF_NM_CHANNELS];
# endif

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || \
  ( defined (NM_GW_EXT_ENABLED) && defined (NM_ENABLE_CHANNELTYPE_CANOSEKNM) )
VAR( Nm_TimerCounterType, NM_VAR_NOINIT_FAST ) Nm_DelayTimer[NM_NUMBER_OF_NM_CHANNELS];
#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
VAR( Nm_TimerCounterType, NM_VAR_NOINIT_FAST ) Nm_DelayTimer_OsekNm[NM_NUMBER_OF_NM_CHANNELS];
#  endif
# endif

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
VAR( Nm_TimerCounterType, NM_VAR_NOINIT_FAST) Nm_CoordTimeoutTimer[NM_NUMBER_OF_NM_CHANNELS];
#  endif
# endif

#define NM_STOP_SEC_VAR_FAST_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/* ----------- Local Data definitions with unspecified size frequent access without initialization need ----------- */
#define NM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

VAR( Nm_NetworkCoordType, NM_VAR_NOINIT_FAST ) Nm_NetworkRequested;
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
VAR( boolean, NM_VAR_NOINIT_FAST ) Nm_CoordChannel[NM_NUMBER_OF_NM_CHANNELS];
#  endif

/* Pointer to (Postbuild) Channel Configuration */
P2CONST( Nm_ConfigType, NM_VAR_NOINIT_FAST, NM_CONST ) Nm_PbConfigPtr;

#define NM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif

#endif /* else NM_MACRO_LAYER_OPT_ENABLED */


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 286121459
      #error "The magic number of the generated file <D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\CanGenerateCode\Nm_Cfg.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\CanGenerateCode\Nm_Cfg.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

