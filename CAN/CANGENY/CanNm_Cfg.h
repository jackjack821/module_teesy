/* -----------------------------------------------------------------------------
  Filename:    CanNm_Cfg.h
  Description: Toolversion: 01.00.22.01.50.07.51.00.00.00
               
               Serial Number: CBD1500751
               Customer Info: Desay SV Automotive Co., Ltd.
                              Package: CBD Geely SLP1
                              Micro: R7F7010233AFP
                              Compiler: Green Hills 6.1.4
               
               
               Generator Fwk   : GENy 
               Generator Module: CanNm
               
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

#if !defined(CANNM_CFG_H)
#define CANNM_CFG_H

#include "ComStack_Types.h"
#include "NmStack_Types.h"
#define NM_ASRNMCANDLL_VERSION               0x0327u
#define NM_ASRNMCANDLL_RELEASE_VERSION       0x00u
/* START of Checksum include for
  - CanNmLinktimeCRC */
#define CANNM_NUMBER_OF_CANNM_CHANNELS       1u
#define CANNM_NUMBER_OF_SYS_CHANNELS         1u
#define CANNM_MAX_PDU_LENGTH                 8u
/* END of Checksum include for
  - CanNmLinktimeCRC */

/* Nm instance properties */
/* START of Checksum include for
  - CanNmPrecompileCRC */
#define CANNM_CONFIG_VARIANT                 1u
/* END of Checksum include for
  - CanNmPrecompileCRC */

/* Options */
/* START of Checksum include for
  - CanNmPrecompileCRC */
#define CANNM_BUS_LOAD_REDUCTION_ENABLED STD_OFF
#define CANNM_IMMEDIATE_TXCONF_ENABLED STD_OFF
#define CANNM_USER_DATA_ENABLED STD_ON
#define CANNM_NODE_DETECTION_ENABLED STD_ON
#define CANNM_NODE_ID_ENABLED STD_ON
#define CANNM_PASSIVE_MODE_ENABLED STD_OFF
#define CANNM_VERSION_INFO_API STD_OFF
#define CANNM_DEV_ERROR_DETECT STD_OFF
#define CANNM_DISABLE_TX_ERR_REPORT STD_OFF
#define CANNM_PROD_ERROR_DETECT STD_OFF
#define CANNM_COM_CONTROL_ENABLED STD_OFF
#define CANNM_IMMEDIATE_RESTART_ENABLED STD_OFF
#define CANNM_PDU_RX_INDICATION_ENABLED STD_OFF
#define CANNM_STATE_CHANGE_IND_ENABLED STD_ON
#define CANNM_REMOTE_SLEEP_IND_ENABLED STD_OFF
#define CANNM_BUS_SYNCHRONIZATION_ENABLED STD_OFF
#define CANNM_REPEAT_MSG_IND_ENABLED STD_ON
#define CANNM_COM_USER_DATA_ENABLED STD_OFF
#define CANNM_CAR_WUP_RX_FEATURE_ENABLED STD_OFF
#define CANNM_CAR_WUP_FILTER_FEATURE_ENABLED STD_OFF
#define CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED STD_ON
#define CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED STD_ON
#define CANNM_PN_FEATURE_ENABLED STD_OFF
#define CANNM_PN_ERA_CALC_FEATURE_ENABLED STD_OFF
#define CANNM_PN_EIRA_CALC_FEATURE_ENABLED   STD_OFF
#define CANNM_IMMEDIATE_TRANSMISSION_ON_REPEAT_MSG_REQUEST STD_OFF
#define CANNM_FORWARD_TX_CONFIRMATION STD_OFF
/* END of Checksum include for
  - CanNmPrecompileCRC */

/* Integration */
/* START of Checksum include for
  - CanNmPrecompileCRC */
#define CANNM_USE_DUMMY_STATEMENT STD_ON
#define CANNM_DEM2DET_ENABLED STD_ON
#define CANNM_CANIF_RANGE_CONFIG_DLC_CHECK
/* END of Checksum include for
  - CanNmPrecompileCRC */

/* CRC check */
/* START of Checksum include for
  - CanNmPrecompileCRC */
#define CANNM_CRC_CHECK                      STD_OFF
/* END of Checksum include for
  - CanNmPrecompileCRC */

#define CANNM_PRECOMPILE_CRC                 (uint32) 0xDB86456Eu
#define CANNM_LINKTIME_CRC                   (uint32) 0x1355178Bu
/* CanNm error codes */
#define CANNM_ERROR_CODE_NW_TIMEOUT          Dem_CANNM_E_NETWORK_TIMEOUT
/* PN Filter Masks */
/* AMD Runtime Measurement */
/* START of Checksum include for
  - CanNmPrecompileCRC */
#define CANNM_AMD_RUNTIME_MEASUREMENT STD_OFF
/* END of Checksum include for
  - CanNmPrecompileCRC */

/* Data Types and Structures */
/* --------------------- Data Types and Structures --------------------- */
/* Invalid Channel Handle */
#define CANNM_INVALID_CHANNEL  0xFFu

/* User Data Buffer Needed */
#if defined ( CANNM_ENABLE_COORD_SYNC_SUPPORT ) || ( CANNM_NODE_ID_ENABLED == STD_ON ) \
  || ( CANNM_USER_DATA_ENABLED == STD_ON ) || ( CANNM_COM_USER_DATA_ENABLED == STD_ON ) \
  || ( CANNM_PN_FEATURE_ENABLED == STD_ON ) || ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON )
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
#  define CANNM_TX_USER_DATA_BUFFER_ENABLED
# endif
#endif
#if ( CANNM_NODE_ID_ENABLED == STD_ON ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) \
  || ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
# define CANNM_RX_USER_DATA_BUFFER_ENABLED
#endif

/* PN Calculation */
#if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON ) || ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
# define CANNM_PN_CALC_FEATURE_ENABLED
# define CANNM_PN_CLUSTERS_PER_BYTE 8u
#endif

/* Structures for link-time configuration parameters. */
typedef struct
{
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
  uint16 CANNM_IMMEDIATE_NM_CYCLE_TIME;           /* Fast NM PDU Transmission Time during WUP */
#endif
  uint16 CANNM_TIMEOUT_TIME;                      /* Timeout for the NM messages [ms]. */
  uint16 CANNM_WAIT_BUS_SLEEP_TIME;               /* Timeout for bus calm down phase [ms]. */
  uint16 CANNM_REPEAT_MESSAGE_TIME;               /* Timeout for Repeat Message State [ms]. */
  uint16 CANNM_REMOTE_SLEEP_IND_TIME;             /* Timeout for Remote Sleep Indication [ms]. */
  uint16 CANNM_MSG_CYCLE_TIME;                    /* Period of a NM message [ms]. It determines the
                                                     periodic rate in the periodic transmission mode. */
  uint16 CANNM_MSG_TIMEOUT_TIME;                  /* Transmission Timeout [ms] of NM message. If there is no
                                                     transmission confirmation by the CAN Interface within this
                                                     timeout, the CAN NM module shall give an error notification. */
#if defined ( CANNM_PN_CALC_FEATURE_ENABLED )
  uint16 CANNM_PN_RESET_TIME;                     /* Timeout Time for a request cluster */
#endif
#if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
  PduIdType CANNM_PN_ERA_RX_PDU_ID;               /* I-PDU handle of Com PDU for ERA */
#endif
  uint8  CANNM_CHANNEL_ID;                        /* Channel ID configured for the respective instance of the NM. */
  uint8  CANNM_CHANNEL_ACTIVE;                    /* Determines if the respective NM channel is active or not. */
  uint8  CANNM_BUS_LOAD_REDUCTION_ACTIVE;         /* Determines if bus load reduction for the respective NM channel 
                                                     is active or not. */
  uint8  CANNM_PDU_LENGTH;                        /* Length of the NM PDU */
  uint8  CANNM_PDU_NID_POSITION;                  /* Node ID Position in the PDU */
  uint8  CANNM_PDU_CBV_POSITION;                  /* Control Bit Vector Position in the PDU */
  uint8  CANNM_USER_DATA_LENGTH;                  /* Length of the User Data in the NM PDU */
  uint8  CANNM_MAIN_FUNCTION_PERIOD;              /* Call cycle of CanNm_MainFunction_x for the respective instance. */
#if ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
  uint8  CANNM_CAR_WAKE_UP_BYTE_POSITION;         /* Byte Position of Car WUP Flag in NM PDU */
  uint8  CANNM_CAR_WAKE_UP_BIT_POSITION;          /* Bit Position of Car WUP Flag in NM PDU */
#endif
#if ( CANNM_CAR_WUP_FILTER_FEATURE_ENABLED == STD_ON )
  uint8  CANNM_CAR_WAKE_UP_FILTER_ENABLED;        /* Determines if Car WUP Filter Handling is active or not */
  uint8  CANNM_CAR_WAKE_UP_FILTER_NODE_ID;        /* Car WUP Node Identifier for Filter Handling */
#endif
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
  uint8  CANNM_IMMEDIATE_NM_TRANSMISSIONS;        /* Number of fast NM PDU Transmissions during WUP */
#endif
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON )
  uint8  CANNM_ACTIVE_WAKE_UP_BIT_ENABLED;        /* Determines if Active WUP Bit Handling is active or not */
#endif
#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
  uint8  CANNM_ALL_MESSAGES_KEEP_AWAKE;           /* Determines if all NM PDUs are relevant or not */

  /* Determines whether a call of CanNm_NetworkRequest leads to a transition to Repeat Message from Network Mode */
  uint8  CANNM_PN_HANDLE_MULTIPLE_NETWORK_REQUEST;
#endif
#if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
  uint8  CANNM_PN_ERA_CALC_ENABLED;               /* Determines if PN Cluster Calculation is active or not */
#endif
} CanNm_LChannelConfigType;

typedef struct
{
#if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
  PduIdType CANNM_PN_EIRA_RX_PDU_ID;              /* I-PDU handle of Com PDU for EIRA */
  uint8  CANNM_PN_EIRA_CALC_ENABLED;              /* Determines if PN EIRA Calculation is active or not */
#endif
#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
  uint8  CANNM_PN_INFO_OFFSET;                    /* Cluster Information Offset in NM PDU */
  uint8  CANNM_PN_INFO_LENGTH;                    /* Cluster Information Length in NM PDU */
#endif
  uint8 CANNM_NUMBER_OF_CHANNELS;                 /* Number of CanNm Channels */
  uint8 CANNM_NUMBER_OF_SYSTEM_CHANNELS;          /* Number of System Channels */
} CanNm_LConfigType;

/* Structure for post-build channel configuration parameters. */
typedef struct
{
  uint16 CANNM_MSG_CYCLE_OFFSET;                  /* Time offset [ms] in the periodic transmission node.
                                                     It determines the start delay of the transmission. */
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON )
  uint16 CANNM_MSG_REDUCED_TIME;                  /* Node specific bus cycle time [ms] in the periodic transmission 
                                                     mode with bus load reduction. */
#endif
  PduIdType CANNM_TX_PDU_ID;                      /* L-PDU handle of NM PDUs to be transmitted. */
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
  PduIdType CANNM_TX_USER_DATA_PDU_ID;            /* I-PDU handle of NM user data PDU */
#endif
#if ( CANNM_NODE_ID_ENABLED == STD_ON )
  uint8  CANNM_NODE_ID;                           /* Node Identifier of local node. */
#endif
#if ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
  uint8  CANNM_CAR_WAKE_UP_RX_ENABLED;            /* Determines if Car WUP Rx Handling is active or not */
#endif
#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
  uint8  CANNM_PN_ENABLED;                        /* Determines if Partial Networking is active or not */
#endif
} CanNm_PbChannelConfigType;

typedef P2CONST(CanNm_PbChannelConfigType, CANNM_PBCFG, CANNM_PBCFG ) CanNm_PbChannelConfigPtrType;

/* Structure for (post-build able) CAN NM configuration parameters */
typedef struct
{
#if defined ( CANNM_USE_EXTENDED_ASR_VERSION_CHECK )
  uint32 CanNm_GeneratorVersion;
#endif
#if ( CANNM_CRC_CHECK == STD_ON )
  uint32 CanNm_Cfg_PrecompileCRC;
  uint32 CanNm_Cfg_LinktimeCRC;
#endif
  /* Post-build Channel Configuration */
  CanNm_PbChannelConfigPtrType CanNm_PbChannelConfigPtr;
  uint16 CANNM_MAGIC_NUMBER;                      /* Magic Number for Vector post-build check */
} CanNm_ConfigType;

/* Pdu buffer type */
#if ( CANNM_MAX_PDU_LENGTH > 0 )
typedef uint8 CanNm_MsgDataType[CANNM_MAX_PDU_LENGTH];
#else
typedef uint8 CanNm_MsgDataType[1];
#endif

#if defined ( CANNM_PN_CALC_FEATURE_ENABLED )
typedef uint8 CanNm_PnClusterReqDataType[CANNM_DEF_PN_CLUSTER_INFO_LENGTH];
#endif

/* Type of the timer/counters. */
typedef uint16 CanNm_TimerCounterType;

#if defined( CANNM_ENABLE_GET_CONTEXT ) || defined( CANNM_ENABLE_SET_CONTEXT ) || \
  ((defined( VGEN_ENABLE_MDWRAP ) || defined( VGEN_ENABLE_QWRAP )) && defined( VQNX_ENABLE_CONTEXT_SWITCH ))
/*--- QNX support ---------------------------------------------------------*/
/* Type that contains all internal variables */
typedef struct
{

  CanNm_TimerCounterType TimeoutTimer[CANNM_NUMBER_OF_CANNM_CHANNELS];
  CanNm_TimerCounterType WaitBusSleepTimer[CANNM_NUMBER_OF_CANNM_CHANNELS];
  CanNm_TimerCounterType RepeatMsgTimer[CANNM_NUMBER_OF_CANNM_CHANNELS];

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
  CanNm_TimerCounterType MsgTimer[CANNM_NUMBER_OF_CANNM_CHANNELS];
#  if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
  CanNm_TimerCounterType MsgTimeoutTimer[CANNM_NUMBER_OF_CANNM_CHANNELS];
#  endif
# endif

# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
  CanNm_TimerCounterType PnClusterResetTimer[CANNM_DEF_PN_CLUSTER_INFO_LENGTH][CANNM_PN_CLUSTERS_PER_BYTE];
# endif
# if (CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON)
  CanNm_TimerCounterType PnClusterResetTimerExt[CANNM_NUMBER_OF_CANNM_CHANNELS][CANNM_DEF_PN_CLUSTER_INFO_LENGTH][CANNM_PN_CLUSTERS_PER_BYTE];
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
  CanNm_TimerCounterType RemoteSleepTimer[CANNM_NUMBER_OF_CANNM_CHANNELS];
  uint8 RemoteSleepIndState[CANNM_NUMBER_OF_CANNM_CHANNELS];
# endif

  uint8 NmState[CANNM_NUMBER_OF_CANNM_CHANNELS];
  uint8 NetworkRestartFlag[CANNM_NUMBER_OF_CANNM_CHANNELS];
  uint8 MsgIndicationFlag[CANNM_NUMBER_OF_CANNM_CHANNELS];

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  uint8 CommState[CANNM_NUMBER_OF_CANNM_CHANNELS];
  uint8 MsgConfirmationFlag[CANNM_NUMBER_OF_CANNM_CHANNELS];
# endif

# if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED )
  CanNm_MsgDataType TxMessageData[CANNM_NUMBER_OF_CANNM_CHANNELS];
# endif
# if defined ( CANNM_RX_USER_DATA_BUFFER_ENABLED )
  CanNm_MsgDataType RxMessageData[CANNM_NUMBER_OF_CANNM_CHANNELS];
# endif

# if ( CANNM_USER_DATA_ENABLED == STD_ON ) || ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
  uint8 UserDataPosition[CANNM_NUMBER_OF_CANNM_CHANNELS];
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_NODE_DETECTION_ENABLED == STD_ON )
  uint8 RepeatMsgBitIndFlag[CANNM_NUMBER_OF_CANNM_CHANNELS];
  uint8 RepeatMsgReqFlag[CANNM_NUMBER_OF_CANNM_CHANNELS];
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_COM_CONTROL_ENABLED == STD_ON )
  uint8 TxControlState[CANNM_NUMBER_OF_CANNM_CHANNELS];
  uint8 TxControlStateRequest[CANNM_NUMBER_OF_CANNM_CHANNELS];
# endif

# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
  CanNm_PnClusterReqDataType PnClusterReq;
  CanNm_PnClusterReqDataType PnClusterReqNew;
# endif
# if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
  CanNm_PnClusterReqDataType PnClusterReqExt[CANNM_NUMBER_OF_CANNM_CHANNELS];
  CanNm_PnClusterReqDataType PnClusterReqExtNew[CANNM_NUMBER_OF_CANNM_CHANNELS];
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
  uint8 ImmediateNmMsgCount[CANNM_NUMBER_OF_CANNM_CHANNELS];
# endif

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
#  if defined ( CANNM_DIAG_GW_EXT_ENABLED ) || ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
  uint8 MsgRequest[CANNM_NUMBER_OF_CANNM_CHANNELS];
#  endif
# endif

# if defined ( CANNM_LIMP_HOME_INDICATION )
  uint8 LimpHomeState[CANNM_NUMBER_OF_CANNM_CHANNELS];
# endif

# if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
  uint8 PnMessageFilterEnabled[CANNM_NUMBER_OF_CANNM_CHANNELS];
# endif

  uint32 canNmMagicNumber;
} CanNm_ModuleContextStructType;
#endif

/* --------------------- Configuration Data Prototypes --------------------- */
#if ( CANNM_CRC_CHECK == STD_ON )
#define CANNM_START_SEC_CONST_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONST(uint32, CANNM_CONST) CanNm_LinktimeCRC;

#define CANNM_STOP_SEC_CONST_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
#else

#define CANNM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Channel indirection: System Channel handle to NM channel handle */
extern CONST( NetworkHandleType, CANNM_CONST ) CanNm_SystemToNmChannelInd[CANNM_NUMBER_OF_SYS_CHANNELS];

#define CANNM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif

#define CANNM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if ( CANNM_PROD_ERROR_DETECT == STD_ON ) && ( CANNM_CONFIG_VARIANT > 1 )
# if ( CANNM_DEM2DET_ENABLED == STD_OFF ) || (( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_DISABLE_TX_ERR_REPORT == STD_OFF ))

/* DEM Constant(s) for link-time support */
#  if ( CANNM_DEM2DET_ENABLED == STD_OFF )
extern CONST( Dem_EventIdType, CANNM_CONST ) CanNm_DemInitFailed;
#  endif

#  if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_DISABLE_TX_ERR_REPORT == STD_OFF )
#   if ( CANNM_DEM2DET_ENABLED == STD_OFF )
extern CONST( Dem_EventIdType, CANNM_CONST ) CanNm_DemTxError;
#   endif

extern CONST( Dem_EventIdType, CANNM_CONST ) CanNm_DemNetTimeout;
#  endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_DISABLE_TX_ERR_REPORT == STD_OFF ) */

# endif /* ( CANNM_DEM2DET_ENABLED == STD_OFF ) || (...) */
#endif /* ( CANNM_PROD_ERROR_DETECT == STD_ON ) && ( CANNM_CONFIG_VARIANT > 1 ) */

/* Configuration of CAN Network Management (link-time able part) */
extern CONST( CanNm_LConfigType, CANNM_CONST ) CanNm_LConfiguration;
extern CONST( CanNm_LChannelConfigType, CANNM_CONST) CanNm_LChannelConfig[CANNM_NUMBER_OF_CANNM_CHANNELS];

#define CANNM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* --------------------- Module Data Prototypes --------------------- */

/* (Local) main function of CAN NM. */
#define CANNM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
extern FUNC( void, CANNM_CODE ) CanNm_LocalMainFunction( void );
#else
extern FUNC( void, CANNM_CODE ) CanNm_LocalMainFunction( CONST( NetworkHandleType, AUTOMATIC ) channel );
#endif

#define CANNM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ----------- Local 8 Bit Data definitions without initialization need ----------- */
#define CANNM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Tx NM message data buffer. */
#if defined ( CANNM_TX_USER_DATA_BUFFER_ENABLED )
extern VAR( CanNm_MsgDataType, CANNM_VAR_NOINIT ) CanNm_TxMessageData[CANNM_NUMBER_OF_CANNM_CHANNELS];
#else
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
extern VAR( CanNm_MsgDataType, CANNM_VAR_NOINIT ) CanNm_TxMessageData;
# endif
#endif

#if defined ( CANNM_RX_USER_DATA_BUFFER_ENABLED )
/* Rx NM message data buffer. */
extern VAR( CanNm_MsgDataType, CANNM_VAR_NOINIT ) CanNm_RxMessageData[CANNM_NUMBER_OF_CANNM_CHANNELS];
#endif

#if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
/* Internal and External Cluster Request Buffer */
extern VAR( CanNm_PnClusterReqDataType, CANNM_VAR_NOINIT ) CanNm_PnClusterReq;
extern VAR( CanNm_PnClusterReqDataType, CANNM_VAR_NOINIT ) CanNm_PnClusterReqNew;
#endif
#if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
/* External Cluster Request Buffer */
extern VAR( CanNm_PnClusterReqDataType, CANNM_VAR_NOINIT ) CanNm_PnClusterReqExt[CANNM_NUMBER_OF_CANNM_CHANNELS];
extern VAR( CanNm_PnClusterReqDataType, CANNM_VAR_NOINIT ) CanNm_PnClusterReqExtNew[CANNM_NUMBER_OF_CANNM_CHANNELS];
#endif

#if ( CANNM_USER_DATA_ENABLED == STD_ON ) || ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
/* User Data Position Start Index */
extern VAR( uint8, CANNM_VAR_NOINIT ) CanNm_UserDataPosition[CANNM_NUMBER_OF_CANNM_CHANNELS];
#endif

#if defined ( CANNM_DIAG_GW_EXT_ENABLED ) || ( CANNM_COM_USER_DATA_ENABLED == STD_ON )
extern VAR( uint8, CANNM_VAR_NOINIT ) CanNm_MsgRequest[CANNM_NUMBER_OF_CANNM_CHANNELS];
#endif

#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ----------- Local 8 Bit Data definitions with frequent access without initialization need ----------- */
/* Control States */
#define CANNM_START_SEC_VAR_FAST_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
/* Internal state for the application's need for communication. */
extern VAR( uint8, CANNM_VAR_NOINIT_FAST ) CanNm_CommState[CANNM_NUMBER_OF_CANNM_CHANNELS];
#endif

extern VAR( uint8, CANNM_VAR_NOINIT_FAST ) CanNm_NetworkRestartFlag[CANNM_NUMBER_OF_CANNM_CHANNELS];

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
extern VAR( uint8, CANNM_VAR_NOINIT_FAST ) CanNm_ImmediateNmMsgCount[CANNM_NUMBER_OF_CANNM_CHANNELS];
#endif

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
extern VAR( uint8, CANNM_VAR_NOINIT_FAST ) CanNm_PnEnabled[CANNM_NUMBER_OF_CANNM_CHANNELS];
#endif

#define CANNM_STOP_SEC_VAR_FAST_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */


#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_COM_CONTROL_ENABLED == STD_ON )
#define CANNM_START_SEC_VAR_FAST_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Message transmission control state request. */
extern VAR( uint8, CANNM_VAR_NOINIT_FAST ) CanNm_TxControlStateRequest[CANNM_NUMBER_OF_CANNM_CHANNELS];
/* Message transmission control state. */
extern VAR( uint8, CANNM_VAR_NOINIT_FAST ) CanNm_TxControlState[CANNM_NUMBER_OF_CANNM_CHANNELS];

#define CANNM_STOP_SEC_VAR_FAST_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

/* ----------- Local 16 Bit Data definitions with frequent access without initialization need ----------- */
#define CANNM_START_SEC_VAR_FAST_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Timer for NM Algorithm. */
extern VAR( CanNm_TimerCounterType, CANNM_VAR_NOINIT_FAST ) CanNm_TimeoutTimer[CANNM_NUMBER_OF_CANNM_CHANNELS];

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
extern VAR( CanNm_TimerCounterType, CANNM_VAR_NOINIT_FAST ) CanNm_RemoteSleepTimer[CANNM_NUMBER_OF_CANNM_CHANNELS];
#endif

extern VAR( CanNm_TimerCounterType, CANNM_VAR_NOINIT_FAST ) CanNm_WaitBusSleepTimer[CANNM_NUMBER_OF_CANNM_CHANNELS];
extern VAR( CanNm_TimerCounterType, CANNM_VAR_NOINIT_FAST ) CanNm_RepeatMsgTimer[CANNM_NUMBER_OF_CANNM_CHANNELS];

#if (CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON)
extern VAR( CanNm_TimerCounterType, CANNM_VAR_NOINIT_FAST ) CanNm_PnClusterResetTimer[CANNM_DEF_PN_CLUSTER_INFO_LENGTH][CANNM_PN_CLUSTERS_PER_BYTE];
#endif
#if (CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON)
extern VAR( CanNm_TimerCounterType, CANNM_VAR_NOINIT_FAST ) CanNm_PnClusterResetTimerExt[CANNM_NUMBER_OF_CANNM_CHANNELS][CANNM_DEF_PN_CLUSTER_INFO_LENGTH][CANNM_PN_CLUSTERS_PER_BYTE];
#endif

/* CANNM072: Message Transmission only for nodes that are not passive */
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
/* Timer for NM message transmission. */
extern VAR( CanNm_TimerCounterType, CANNM_VAR_NOINIT_FAST ) CanNm_MsgTimer[CANNM_NUMBER_OF_CANNM_CHANNELS];
/* CANNM071: Immediate Transmission confirmation is configurable */
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
/* CANNM073: Transmission error handling only when not passive and immediate transmission confirmation is not enabled */
extern VAR( CanNm_TimerCounterType, CANNM_VAR_NOINIT_FAST ) CanNm_MsgTimeoutTimer[CANNM_NUMBER_OF_CANNM_CHANNELS];
# endif
#endif

#define CANNM_STOP_SEC_VAR_FAST_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ----------- Local Data definitions with unspecified size without initialization need ----------- */
/* CANNM149: Remote Sleep Indication is configurable */
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
#define CANNM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* State of remote sleep indication. */
extern VAR( boolean, CANNM_VAR_NOINIT ) CanNm_RemoteSleepIndState[CANNM_NUMBER_OF_CANNM_CHANNELS];

#define CANNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

#if defined ( CANNM_LIMP_HOME_INDICATION )
#define CANNM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Limp Home State */
extern VAR( boolean, CANNM_VAR_NOINIT ) CanNm_LimpHomeState[CANNM_NUMBER_OF_CANNM_CHANNELS];

#define CANNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
#define CANNM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Partial Networking: Message Reception Filter is enabled */
extern VAR( boolean, CANNM_VAR_NOINIT ) CanNm_PnMessageFilterEnabled[CANNM_NUMBER_OF_CANNM_CHANNELS];

#define CANNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

/* ----------- Local Data definitions with unspecified size frequent access without initialization need ----------- */
#define CANNM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Control Flags */
extern VAR( boolean, CANNM_VAR_NOINIT_FAST ) CanNm_MsgIndicationFlag[CANNM_NUMBER_OF_CANNM_CHANNELS];
/* CANNM161, CANNM162: Passive Mode is configurable */
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
extern VAR( boolean, CANNM_VAR_NOINIT_FAST ) CanNm_MsgConfirmationFlag[CANNM_NUMBER_OF_CANNM_CHANNELS];
/* CANNM135: Repeat Message Request / Bit is configurable */
# if ( CANNM_NODE_DETECTION_ENABLED == STD_ON )
extern VAR( boolean, CANNM_VAR_NOINIT_FAST ) CanNm_RepeatMsgBitIndFlag[CANNM_NUMBER_OF_CANNM_CHANNELS];
extern VAR( boolean, CANNM_VAR_NOINIT_FAST ) CanNm_RepeatMsgReqFlag[CANNM_NUMBER_OF_CANNM_CHANNELS];
# endif
#endif

#define CANNM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ----------- Local Data definitions with unspecified size frequent access with initialization need ----------- */
#define CANNM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* CANNM089: NM state for each channel */
extern VAR( Nm_StateType, CANNM_VAR_ZERO_INIT_FAST ) CanNm_NmState[CANNM_NUMBER_OF_CANNM_CHANNELS];

#define CANNM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* ----------- Generated Configuration declarations(s) ----------- */
#define CANNM_START_SEC_PBCFG_ROOT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Configuration(s) of CAN Network Management (post-build able part). */
extern CONST( CanNm_ConfigType, CANNM_PBCFG_ROOT ) CanNm_Configuration0;
#define CANNM_STOP_SEC_PBCFG_ROOT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define CANNM_START_SEC_PBCFG
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Channel Configuration(s) of CAN Network Management (post-build able part). */
extern CONST( CanNm_PbChannelConfigType, CANNM_PBCFG ) CanNm_PbChannelConfig0[CANNM_NUMBER_OF_CANNM_CHANNELS];
#define CANNM_STOP_SEC_PBCFG
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* ----------- Generated main function declarations(s) ----------- */
#define CANNM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* START of Checksum include for
  - CanNmLinktimeCRC */
extern FUNC( void, CANNM_CODE ) CanNm_MainFunction_0( void );
/* END of Checksum include for
  - CanNmLinktimeCRC */

#define CANNM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 286121459
      #error "The magic number of the generated file <D:\HVACProject\Geely\FE-5DB&7DA\ProjectTools\CANTools\CanGenerateCode\CanNm_Cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 286121459
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* CANNM_CFG_H */
