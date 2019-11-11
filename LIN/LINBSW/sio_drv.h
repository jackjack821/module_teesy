/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  Copyright (c) 2014 by Vector Informatik GmbH.                                                    All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
         File:  sio_drv.h
    Component:  SIO Driver
       Module:  DrvLin_78k0rSci
    Generator:  DrvLin_78k0rSci

  Description:  Header file of the SIO Driver for 78K0R Fx3 using UARTF
**********************************************************************************************************************/

#ifndef SIO_DRV_COMPONENT_HEADER
#define SIO_DRV_COMPONENT_HEADER

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/* Defines for indexed and single channel implementation */
#define SIO_CHANNEL_TYPE_ONLY          void
#define SIO_CHANNEL_TYPE_FIRST
#define SIO_CHANNEL_PARA_ONLY
#define SIO_CHANNEL_PARA_FIRST

/*****************************************************************************
 * message informations
 *****************************************************************************/
/* Defines to specify checksum type of a message */
#define kLinLowCsClassic                0x00u
#define kLinLowCsEnhanced               0x01u

/* Defines to specify direction of a message */
#define kLinLowRxMsg                    0x01u
#define kLinLowTxMsg                    0x02u
#define kLinLowNoMsg                    0x03u
#define kLinLowWakeUpMsg                0x04u

/* Defines to specify timeout type if detected by protocol driver */
#define kFpTimerNoHeader                0x00u
#define kFpTimerIncHeader               0x01u
#define kFpTimerNoResponse              0x02u
#define kFpTimerIncResponse             0x03u

/*****************************************************************************
 * error codes
 *****************************************************************************/
/* LIN LowLevel errors signalized by ApplLinLowErrorNotification() */
#define kLinLowHeaderTimeout            ((vuint8)0x10u)
#define kLinLowNoResponseTimeout        ((vuint8)0x11u)
#define kLinLowIncompResponseTimeout    ((vuint8)0x12u)
#define kLinLowSynchError               ((vuint8)0x13u)
#define kLinLowIdParityError            ((vuint8)0x14u)
#define kLinLowChecksumError            ((vuint8)0x15u)
#define kLinLowMonitoringError          ((vuint8)0x16u)
#define kLinLowFrameError               ((vuint8)0x17u)

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
extern void ApplLinLowWakeUpIndication(SIO_CHANNEL_TYPE_ONLY);
extern vuint8 ApplLinLowHeaderIndication(SIO_CHANNEL_TYPE_FIRST vuint8 bProtectedId);
extern vuint8 ApplLinLowRxMsgIndication(SIO_CHANNEL_TYPE_FIRST vuint8 identifier, vuint8* pbData);
extern vuint8 ApplLinLowTxMsgIndication(SIO_CHANNEL_TYPE_FIRST vuint8 identifier, vuint8* pbData);
extern void ApplLinLowErrorIndication(SIO_CHANNEL_TYPE_FIRST vuint8 error, vuint8 identifier);
extern void LinLowInitPowerOn(void);
extern void LinLowInit(SIO_CHANNEL_TYPE_ONLY);
extern void LinLowSendWakeUpFrame(SIO_CHANNEL_TYPE_ONLY);
extern vuint8 LinLowSendMessageFrame(SIO_CHANNEL_TYPE_FIRST vuint8 identifier, vuint8 dir, vuint8 dlc, vuint8 checksumtype, vuint8* pbData);
extern vuint8 LinLowRespTimeoutFunc(SIO_CHANNEL_TYPE_ONLY);
extern void SioSetMuteMode(SIO_CHANNEL_TYPE_ONLY);
extern void SioResetMuteMode(SIO_CHANNEL_TYPE_ONLY);
extern void SioInterruptDisable(SIO_CHANNEL_TYPE_ONLY);
extern void SioInterruptRestore(SIO_CHANNEL_TYPE_ONLY);

/* require_prototypes requires forward declarations even for interrupt routines */
extern void l_ifc_tx(void);
extern void l_ifc_rx(void);
extern void l_ifc_err(void);

#endif  /* SIO_DRV_COMPONENT_HEADER */

/**********************************************************************************************************************
  END OF FILE: sio_drv.h
**********************************************************************************************************************/
