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
         File:  sio_drv.c
    Component:  SIO Driver
       Module:  DrvLin_78k0rSci
    Generator:  DrvLin_78k0rSci

  Description:  Implementation of SIO Driver for 78K0R Fx3 using UARTF.
**********************************************************************************************************************/

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "v_cfg.h"
#include "v_def.h"
#include "Sio_drv.h"
/* define const */

/************************************************************************************************/
/* Register defines                                                                             */
/************************************************************************************************/
/*==================================================================================*/
/* Bitmasks for LIN_LCUC (LIN control register)                                     */
/*==================================================================================*/
#define LIN_LCUC_REQUEST_RESET            ((vuint8)0x00u)              /* 0 = request reset, 1 = reset request inactive */
#define LIN_LCUC_MODE_WAKEUP              ((vuint8)0x01u)              /* Wakeup mode */
#define LIN_LCUC_MODE_NORMAL              ((vuint8)0x03u)              /* Normal communication mode */

/*==================================================================================*/
/* Bitmasks for LIN_LMST (LIN mode status register)                                 */
/*==================================================================================*/
#define LIN_LMST_RESET_STATE_MASK         ((vuint8)0x01u)              /* Reset status bit: 0 = reset state, 1 = not in reset state */
#define LIN_LMST_WAKEUP_MODE_MASK         ((vuint8)0x02u)              /* Mode bit: 0 = wakeup mode, 1 = normal mode */
#define LIN_LMST_OPERATION_MODE_MASK      ((vuint8)0x03u)              /* Mode bit: 0 = wakeup mode, 1 = normal mode */

#define LIN_LMST_RESET_STATE              ((vuint8)0x00u)              /* Reset status bit: 0 = reset state, 1 = not in reset state */
#define LIN_LMST_WAKEUP_MODE              ((vuint8)0x01u)              /* Mode bit: 0 = wakeup mode, 1 = normal mode */
#define LIN_LMST_OPERATION_MODE           ((vuint8)0x03u)              /* Mode bit: 0 = wakeup mode, 1 = normal mode */

/*==================================================================================*/
/* Bitmasks for LIN_ICR  (Interrupt Control Register)                               */
/*==================================================================================*/
#define LIN_ICR_MK_SET_MASK               ((vuint8)0x80u)              /* Mask to set the MK bit of the ICR */
#define LIN_ICR_MK_CLR_MASK               ((vuint8)0x7Fu)              /* Mask to clear the MK bit of the ICR */
#define LIN_ICR_TB_SET_MASK               ((vuint8)0x40u)              /* Mask to set the TB bit of the ICR */
#define LIN_ICR_TB_CLR_MASK               ((vuint8)0xBFu)              /* Mask to clear the TB bit of the ICR */
#define LIN_ICR_RF_CLR_MASK		      ((vuint8)0xEFu)		/* Mask to clear the RF bit of ICR */

/* Data struct for RLIN Controller  */
typedef volatile struct tLinModule
{
  vuint8         	LIN_Reserved1;          /* 0x0000: Reserved */
  vuint8         	LIN_LWBR;               /* 0x0001: LIN Wake-up baud rate selector register - set only in LIN reset mode */
  vuint16		LIN_LBRP01;		/* 0x0002 - 0x0003: LIN Baud Rate Prescaler 01 Register */
  vuint8         	LIN_LSTC;               /* 0x0004: LIN self test control register - set only in LIN reset mode */
  vuint8         	LIN_Reserved2;          /* 0x0005: Reserved */
  vuint8         	LIN_Reserved3;          /* 0x0006: Reserved */
  vuint8         	LIN_Reserved4;          /* 0x0007: Reserved */
  vuint8         	LIN_LMD;                /* 0x0008: LIN / UART mode register - set only in LIN reset mode */
  vuint8         	LIN_LBFC;               /* 0x0009: LIN break field configuration register - set only in LIN reset mode */
  vuint8         	LIN_LSC;                /* 0x000A: LIN / UART space configuration register - set only in LIN reset mode */
  vuint8         	LIN_LWUP;               /* 0x000B: LIN Wake-up configuration register - set only in LIN reset mode */
  vuint8         	LIN_LIE;                /* 0x000C: LIN interrupt enable register - set only in LIN reset mode */
  vuint8         	LIN_LEDE;               /* 0x000D: LIN / UART error detection enable register */
  vuint8         	LIN_LCUC;               /* 0x000E: LIN / UART control register */
  vuint8         	LIN_Reserved5;          /* 0x000F: Reserved */
  vuint8         	LIN_LTRC;               /* 0x0010: LIN / UART transmission control register */
  vuint8         	LIN_LMST;               /* 0x0011: LIN / UART mode status register */
  vuint8         	LIN_LST;                /* 0x0012: LIN / UART Status register */
  vuint8          	LIN_LEST;               /* 0x0013: LIN / UART error status register */
  vuint8          	LIN_LDFC;               /* 0x0014: LIN / UART data field configuration register */
  vuint8          	LIN_LIDB;               /* 0x0015: LIN / UART identifier buffer register */
  vuint8          	LIN_LCBR;               /* 0x0016: LIN checksum buffer register */
  vuint8          	LIN_LUDB0;              /* 0x0017: UART data buffer 0 register */
  vuint8         	LIN_LDBR1;               /* 0x0018: LIN / UART data buffer 1 register */
  vuint8         	LIN_LDBR2;               /* 0x0019: LIN / UART data buffer 2 register */
  vuint8         	LIN_LDBR3;               /* 0x001A: LIN / UART data buffer 3 register */
  vuint8         	LIN_LDBR4;               /* 0x001B: LIN / UART data buffer 4 register */
  vuint8         	LIN_LDBR5;               /* 0x001C: LIN / UART data buffer 5 register */
  vuint8         	LIN_LDBR6;               /* 0x001D: LIN / UART data buffer 6 register */
  vuint8         	LIN_LDBR7;               /* 0x001E: LIN / UART data buffer 7 register */
  vuint8         	LIN_LDBR8;               /* 0x001F: LIN / UART data buffer 8 register */
} tsLinModule;

/* Defines for internal states */
/*      Lin_OnUninit                          ((Lin_StateType)0x00u) */
#define Lin_OnWake                            ((Lin_StateType)0x01u)
#define Lin_OnSleep                           ((Lin_StateType)0x02u)
#define Lin_OnRx                              ((Lin_StateType)0x03u)
#define Lin_OnS2S                             ((Lin_StateType)0x04u)
#define Lin_OnTx                              ((Lin_StateType)0x06u)
#define Lin_OnTxWakeup                        ((Lin_StateType)0x08u)
/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
typedef V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2  Lin_StateType;
typedef volatile struct Lin_INTRegStructTag {
  volatile vuint8 lowerICR;               /* lower byte of the ICR register  */
  volatile vuint8 upperICR;               /* upper byte of the ICR register */
} Lin_INTRegStruct;

typedef volatile struct Lin_INTRegGrpStructTag {
  Lin_INTRegStruct RLINIntTx;
  Lin_INTRegStruct RLINIntRx;
  Lin_INTRegStruct RLINIntErr;
} Lin_INTRegGrpStruct;

#define Lin_ChannelDataBufferSize             (0x08u)

/* Struct to store the channel specific data */
typedef struct Lin_ChannelDataTypeTag
{
  Lin_StateType Lin_State;
  vuint8 Lin_CurrentID;
  vuint8 Lin_DataBuffer[Lin_ChannelDataBufferSize];
}Lin_ChannelDataType;

/* Interrupt register masks for polling mode */
#define kMask_LIN_RF                         	0x10u
#define kMask_LIN_CLR_RF                 	0xEFu

#define check_IrqRxFlag()                   (Lin_ICRPtrTmp->RLINIntRx.upperICR  & kMask_LIN_RF)
#define check_IrqTxFlag()                   (Lin_ICRPtrTmp->RLINIntTx.upperICR  & kMask_LIN_RF)
#define check_IrqErrFlag()                  (Lin_ICRPtrTmp->RLINIntErr.upperICR & kMask_LIN_RF)

#define clr_IrqRxFlag()                     (Lin_ICRPtrTmp->RLINIntRx.upperICR  &= (vuint8)kMask_LIN_CLR_RF)
#define clr_IrqTxFlag()                     (Lin_ICRPtrTmp->RLINIntTx.upperICR  &= (vuint8)kMask_LIN_CLR_RF)
#define clr_IrqErrFlag()                    (Lin_ICRPtrTmp->RLINIntErr.upperICR &= (vuint8)kMask_LIN_CLR_RF)

V_MEMRAM0 static V_MEMRAM1 Lin_ChannelDataType V_MEMRAM2 Lin_ChannelData;
static tsLinModule*  Lin_RLINModulePtrTmp;
static Lin_INTRegGrpStruct*  Lin_ICRPtrTmp;
static Lin_ChannelDataType*  Lin_ChannelDataPtrTmp;
V_MEMRAM0 static V_MEMRAM1 vuint8  V_MEMRAM2 bLinLowInterruptDisableCounter;

vuint8 LinErrCounter=0;

/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
static void LinLowSetNormalMode(tsLinModule* Lin_RLINModulePtrTmp);
static void LinLowSetWakeMode(tsLinModule* Lin_RLINModulePtrTmp);
/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/
/**********************************************************************************************************************
  FUNCTION: LinLowSetNormalMode
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: Lin_RLINModuleStruct    Lin_RLINModulePtrTmp    Pointer to channel register
  Output: void                    -                       -
  Return: void                    -                       -
-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: SIO Driver
  Precondition: None.

  Set the LIN interface to state LIN operation mode to perform frame prcoessing.
**********************************************************************************************************************/
static void LinLowSetNormalMode(tsLinModule* Lin_RLINModulePtrTmp)
{
  	Lin_RLINModulePtrTmp->LIN_LCUC      = LIN_LCUC_REQUEST_RESET;
  	while( ((Lin_RLINModulePtrTmp->LIN_LMST & LIN_LMST_RESET_STATE_MASK) != LIN_LMST_RESET_STATE)  )
  	{
    		;
  	}
  	/* LIN reset mode entered */

  	Lin_RLINModulePtrTmp->LIN_LCUC                = LIN_LCUC_MODE_NORMAL;
  	/* wait until LIN module has left reset state */
  	while( ((Lin_RLINModulePtrTmp->LIN_LMST & LIN_LMST_OPERATION_MODE_MASK) != LIN_LMST_OPERATION_MODE)  )
  	{
    		;
  	}
  	/* LIN normal mode entered */
}

/**********************************************************************************************************************
  FUNCTION: LinLowSetWakeMode
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: Lin_RLINModuleStruct    Lin_RLINModulePtrTmp    Pointer to channel register
  Output: void                    -                       -
  Return: void                    -                       -
-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: SIO Driver
  Precondition: None.

  Set the LIN interface to state LIN wake-up mode to receive or transmit wakeup frames.
**********************************************************************************************************************/
static void LinLowSetWakeMode(tsLinModule* Lin_RLINModulePtrTmp)
{
  	Lin_RLINModulePtrTmp->LIN_LCUC      = LIN_LCUC_REQUEST_RESET;
  	while( ((Lin_RLINModulePtrTmp->LIN_LMST & LIN_LMST_RESET_STATE_MASK) != LIN_LMST_RESET_STATE)  )
  	{
    		;
  	}
  	/* LIN reset mode entered */

  	Lin_RLINModulePtrTmp->LIN_LCUC      = LIN_LCUC_MODE_WAKEUP;
  	/* wait until LIN module has entered wake up mode */
  	while( ((Lin_RLINModulePtrTmp->LIN_LMST & LIN_LMST_OPERATION_MODE_MASK) != LIN_LMST_WAKEUP_MODE) )
  	{
    		;
  	}
  	/* LIN wake up mode entered */
}
/**********************************************************************************************************************
  FUNCTION: l_ifc_rx
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: void                    -                       -
  Output: void                    -                       -
  Return: void                    -                       -
-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------  -------------------------------------------------------
     Called by: System interrupt handler
  Precondition: SIO Driver has been initialized

  Handles the occurring interrupts
**********************************************************************************************************************/
#pragma ghs interrupt 
void l_ifc_rx(void)
{
	vuint8 Lin_RLINFlagsTmp;
  	vuint8 Lin_RLINErrFlagsTmp;
  	/* read status register */
	/* read status flags */
	Lin_RLINFlagsTmp = Lin_RLINModulePtrTmp->LIN_LST;
    	Lin_RLINErrFlagsTmp = Lin_RLINModulePtrTmp->LIN_LEST;
	/* clear interrupt request flag */
	clr_IrqRxFlag();
    	/* clear flags */
	Lin_RLINModulePtrTmp->LIN_LST = 0x00;
	Lin_RLINModulePtrTmp->LIN_LEST = 0x00;
       if ( (Lin_ChannelDataPtrTmp->Lin_State == Lin_OnSleep) || (Lin_ChannelDataPtrTmp->Lin_State == Lin_OnTxWakeup))
	{
		LinLowSetNormalMode(Lin_RLINModulePtrTmp);
		Lin_ChannelDataPtrTmp->Lin_State      = Lin_OnWake;
        	/* inform protocol driver */
        	ApplLinLowWakeUpIndication(SIO_CHANNEL_PARA_ONLY);
		//Lin_RLINModulePtrTmp->LIN_LIDB = 0x00;
		//Lin_RLINModulePtrTmp->LIN_LDFC = 0x00; 
		/* Header reception/wake-up transmission/reception is started */
		Lin_RLINModulePtrTmp->LIN_LTRC = 0x01;
	}
      else
      {
        	if ( (Lin_RLINFlagsTmp & 0x80) != 0)
	      	{
	          	/* header detection */
			Lin_ChannelDataPtrTmp->Lin_CurrentID = Lin_RLINModulePtrTmp->LIN_LIDB;
	          	(void)ApplLinLowHeaderIndication(SIO_CHANNEL_PARA_FIRST Lin_ChannelDataPtrTmp->Lin_CurrentID);
	      	}
        	else
        	{
          		if ( (( Lin_RLINFlagsTmp & 0x02 ) != (vuint8)0x00u) && (Lin_ChannelDataPtrTmp->Lin_State == Lin_OnRx))
          		{
          			/* Response successfully received */
          			Lin_ChannelDataPtrTmp->Lin_DataBuffer[0]   = (vuint8)Lin_RLINModulePtrTmp->LIN_LDBR1;
        			Lin_ChannelDataPtrTmp->Lin_DataBuffer[1]   = (vuint8)Lin_RLINModulePtrTmp->LIN_LDBR2;
        			Lin_ChannelDataPtrTmp->Lin_DataBuffer[2]   = (vuint8)Lin_RLINModulePtrTmp->LIN_LDBR3;
        			Lin_ChannelDataPtrTmp->Lin_DataBuffer[3]   = (vuint8)Lin_RLINModulePtrTmp->LIN_LDBR4;
        			Lin_ChannelDataPtrTmp->Lin_DataBuffer[4]   = (vuint8)Lin_RLINModulePtrTmp->LIN_LDBR5;
        			Lin_ChannelDataPtrTmp->Lin_DataBuffer[5]   = (vuint8)Lin_RLINModulePtrTmp->LIN_LDBR6;
        			Lin_ChannelDataPtrTmp->Lin_DataBuffer[6]   = (vuint8)Lin_RLINModulePtrTmp->LIN_LDBR7;
        			Lin_ChannelDataPtrTmp->Lin_DataBuffer[7]   = (vuint8)Lin_RLINModulePtrTmp->LIN_LDBR8;
				/* assign dummy ID */
        			Lin_ChannelDataPtrTmp->Lin_CurrentID             = 0xFFu;
				Lin_ChannelDataPtrTmp->Lin_State                 = Lin_OnWake;
				/* notify application */
        			(void)ApplLinLowRxMsgIndication(SIO_CHANNEL_PARA_FIRST (vuint8)(Lin_ChannelDataPtrTmp->Lin_CurrentID), Lin_ChannelDataPtrTmp->Lin_DataBuffer);			
          		}
			//Lin_RLINModulePtrTmp->LIN_LIDB = 0x00;
			//Lin_RLINModulePtrTmp->LIN_LDFC = 0x00; 
			/* Header reception/wake-up transmission/reception is started */
			Lin_RLINModulePtrTmp->LIN_LTRC = 0x01;
        	}
      	}
} /* End of l_ifc_rx() */

/**********************************************************************************************************************
  FUNCTION: l_ifc_tx
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: void                    -                       -
  Output: void                    -                       -
  Return: void                    -                       -
-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------  -------------------------------------------------------
     Called by: System interrupt handler
  Precondition: SIO Driver has been initialized

  Handles the occurring interrupts
**********************************************************************************************************************/
#pragma ghs interrupt 
void l_ifc_tx(void)
{
	vuint8 Lin_RLINFlagsTmp;
  	vuint8 Lin_RLINErrFlagsTmp;
  	/* read status register */
	/* read status flags */
    	Lin_RLINFlagsTmp = Lin_RLINModulePtrTmp->LIN_LST;
    	Lin_RLINErrFlagsTmp = Lin_RLINModulePtrTmp->LIN_LEST;
	/* clear interrupt request flag */
	clr_IrqTxFlag();
    	/* clear flags */
	Lin_RLINModulePtrTmp->LIN_LST = 0x00;
	Lin_RLINModulePtrTmp->LIN_LEST = 0x00;
    	if ( (Lin_ChannelDataPtrTmp->Lin_State == Lin_OnSleep) || (Lin_ChannelDataPtrTmp->Lin_State == Lin_OnTxWakeup))
	{
		LinLowSetNormalMode(Lin_RLINModulePtrTmp);
		Lin_ChannelDataPtrTmp->Lin_State      = Lin_OnWake;
        	/* inform protocol driver */
        	ApplLinLowWakeUpIndication(SIO_CHANNEL_PARA_ONLY);
	}
	else
	{
      		if ((( Lin_RLINFlagsTmp & 0x01 ) != (vuint8)0x00u) && (Lin_ChannelDataPtrTmp->Lin_State == Lin_OnTx))
	      	{ /* TX message successfull transmitted */
	      		/* assign dummy ID */
        		Lin_ChannelDataPtrTmp->Lin_CurrentID             = 0xFFu;
	        	Lin_ChannelDataPtrTmp->Lin_State                 = Lin_OnWake;		
	        	(void)ApplLinLowTxMsgIndication(SIO_CHANNEL_PARA_FIRST (vuint8)(Lin_ChannelDataPtrTmp->Lin_CurrentID),Lin_ChannelDataPtrTmp->Lin_DataBuffer);
	      	}
	}
	//Lin_RLINModulePtrTmp->LIN_LIDB = 0x00;
	//Lin_RLINModulePtrTmp->LIN_LDFC = 0x00; 
	/* Header reception/wake-up transmission/reception is started */
	Lin_RLINModulePtrTmp->LIN_LTRC = 0x01;
} /* End of l_ifc_tx() */

/**********************************************************************************************************************
  FUNCTION: l_ifc_err
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: void                    -                       -
  Output: void                    -                       -
  Return: void                    -                       -
-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------  -------------------------------------------------------
     Called by: System interrupt handler
  Precondition: SIO Driver has been initialized

  Handles the occurring interrupts
**********************************************************************************************************************/
#pragma ghs interrupt 
void l_ifc_err(void)
{
	vuint8 Lin_RLINFlagsTmp;
  	vuint8 Lin_RLINErrFlagsTmp;
	
  	/* read status register */
	Lin_RLINFlagsTmp = Lin_RLINModulePtrTmp->LIN_LST;
    	Lin_RLINErrFlagsTmp = Lin_RLINModulePtrTmp->LIN_LEST;

	/* clear interrupt request flag */
	clr_IrqErrFlag();
    	/* clear all status flags by writing one to it */
    	Lin_RLINModulePtrTmp->LIN_LST = 0x00;
	Lin_RLINModulePtrTmp->LIN_LEST = 0x00;
	if ( (Lin_ChannelDataPtrTmp->Lin_State == Lin_OnSleep) || (Lin_ChannelDataPtrTmp->Lin_State == Lin_OnTxWakeup))
	{
		LinLowSetNormalMode(Lin_RLINModulePtrTmp);
		Lin_ChannelDataPtrTmp->Lin_State      = Lin_OnWake;
        	/* inform protocol driver */
        	ApplLinLowWakeUpIndication(SIO_CHANNEL_PARA_ONLY);
		//Lin_RLINModulePtrTmp->LIN_LIDB = 0x00;
		//Lin_RLINModulePtrTmp->LIN_LDFC = 0x00; 
		/* Header reception/wake-up transmission/reception is started */
		Lin_RLINModulePtrTmp->LIN_LTRC = 0x01;
	}
    	else
    	{
      		if ( ( Lin_RLINFlagsTmp & 0x08 ) != (vuint8)0x00u )
		{
			if ( (Lin_RLINErrFlagsTmp & 0x40) != 0)
		      	{
		        	ApplLinLowErrorIndication(SIO_CHANNEL_PARA_FIRST kLinLowIdParityError, (vuint8)(Lin_ChannelDataPtrTmp->Lin_CurrentID));
		      	}
			else if ( ( Lin_RLINErrFlagsTmp & 0x20 ) != (vuint8)0x00u)
		      	{
		        	ApplLinLowErrorIndication(SIO_CHANNEL_PARA_FIRST kLinLowChecksumError, (vuint8)(Lin_ChannelDataPtrTmp->Lin_CurrentID));
		      	}
			else if ( ( Lin_RLINErrFlagsTmp & 0x08 ) != (vuint8)0x00u)
		      	{
		      		ApplLinLowErrorIndication(SIO_CHANNEL_PARA_FIRST kLinLowFrameError, (vuint8)(Lin_ChannelDataPtrTmp->Lin_CurrentID));
		      	}
	  		else if ( ( Lin_RLINErrFlagsTmp & 0x04 ) != (vuint8)0x00u )
		      	{/* timeout */
		        	if ( ( Lin_RLINFlagsTmp & 0x40 ) == (vuint8)0x00u )
		        	{ /* no response byte received */
		          		ApplLinLowErrorIndication(SIO_CHANNEL_PARA_FIRST kLinLowNoResponseTimeout, (vuint8)(Lin_ChannelDataPtrTmp->Lin_CurrentID));
		        	}
	        		else
	        		{ /* response partly received */
	          			ApplLinLowErrorIndication(SIO_CHANNEL_PARA_FIRST kLinLowIncompResponseTimeout, (vuint8)(Lin_ChannelDataPtrTmp->Lin_CurrentID));
	        		}
		      	}
	  		else if ( ( Lin_RLINErrFlagsTmp & 0x01 ) != (vuint8)0x00 )
		      	{
		      		ApplLinLowErrorIndication(SIO_CHANNEL_PARA_FIRST kLinLowMonitoringError, (vuint8)(Lin_ChannelDataPtrTmp->Lin_CurrentID));
		      	}  		  		
	  		else
		      	{
		        	/* nothing to be done here for LIN */
		      	}
		}
		Lin_ChannelDataPtrTmp->Lin_State = Lin_OnWake;
		//Lin_RLINModulePtrTmp->LIN_LIDB = 0x00;
		//Lin_RLINModulePtrTmp->LIN_LDFC = 0x00; 
		/* Header reception/wake-up transmission/reception is started */
		Lin_RLINModulePtrTmp->LIN_LTRC = 0x01;
		
	}
} /* End of l_ifc_err() */


/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  FUNCTION: LinLowInitPowerOn
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: void                    -                       -
  Output: void                    -                       -
  Return: void                    -                       -
-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: LIN Driver
  Precondition: -

  Initialize the LIN interface.
  Channel unspecific initialization
**********************************************************************************************************************/
void LinLowInitPowerOn(void)
{
  /* no channel independent initialization required */

} /* End of LinLowInitPowerOn() */

/**********************************************************************************************************************
  FUNCTION: LinLowInit
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: SioChannelHandle        siochannel              Channel parameter (only applicable for indexed channel)
  Output: void                    -                       -
  Return: void                    -                       -
-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: LIN Driver
  Precondition: LinLowInitPowerOn called before

  Initialize the LIN interface.
  Channel specific initialization
**********************************************************************************************************************/
void LinLowInit(SIO_CHANNEL_TYPE_ONLY)
{
	bLinLowInterruptDisableCounter = 0;
	Lin_ICRPtrTmp = (Lin_INTRegGrpStruct*)(0xFFFF9034u);
	Lin_RLINModulePtrTmp = (tsLinModule*)(0xFFCF0000u);
	Lin_ChannelDataPtrTmp = &Lin_ChannelData;
	/* Initialize channel data */
  	/* Channel is set to sleep mode after initialization */
  	Lin_ChannelDataPtrTmp->Lin_State = Lin_OnSleep;
	/* init current ID */
	Lin_ChannelDataPtrTmp->Lin_CurrentID = 0xFF;
  	/* currently only byte access behaves correctly */
  	Lin_ChannelDataPtrTmp->Lin_DataBuffer[0x00u]  = 0x00u;
  	Lin_ChannelDataPtrTmp->Lin_DataBuffer[0x01u]  = 0x00u;
  	Lin_ChannelDataPtrTmp->Lin_DataBuffer[0x02u]  = 0x00u;
  	Lin_ChannelDataPtrTmp->Lin_DataBuffer[0x03u]  = 0x00u;
  	Lin_ChannelDataPtrTmp->Lin_DataBuffer[0x04u]  = 0x00u;
  	Lin_ChannelDataPtrTmp->Lin_DataBuffer[0x05u]  = 0x00u;
  	Lin_ChannelDataPtrTmp->Lin_DataBuffer[0x06u]  = 0x00u;
  	Lin_ChannelDataPtrTmp->Lin_DataBuffer[0x07u]  = 0x00u;
	Lin_RLINModulePtrTmp->LIN_LCUC = LIN_LCUC_REQUEST_RESET;           /* initialize RLIN UART  */
  	/* wait until LIN module is in reset state */
  	while( ((Lin_RLINModulePtrTmp->LIN_LMST & LIN_LMST_RESET_STATE_MASK) != LIN_LMST_RESET_STATE))
  	{
    		;
  	}
  	/* set baudrate 19200 */
	Lin_RLINModulePtrTmp->LIN_LWBR = 0x00; /* 16 sample */
    	Lin_RLINModulePtrTmp->LIN_LBRP01 = 0x33;  	
    	/* Sets noise filter ON/OFF */
	/* RLIN3n transmission interrupt, RLIN3n successful reception interrupt, and RLIN3n reception status interrupt are used. */
	/* LIN Slave mode with fixed Baud rate */
    	Lin_RLINModulePtrTmp->LIN_LMD = 0x13;
	/* Sets frame configuration parameters  */
	/* A break (low-level) is detected in 9.5 or 10 Tbits */
  	Lin_RLINModulePtrTmp->LIN_LBFC = (vuint8)(0x00);
	/* configure header-response space to 2TBit and inter-byte space to 1 TBit */
  	Lin_RLINModulePtrTmp->LIN_LSC = 0x12;
	/* configure wakeup tx length to 10bits */
  	Lin_RLINModulePtrTmp->LIN_LWUP = 0x90;
  	/* enable interrupts */
  	Lin_RLINModulePtrTmp->LIN_LIE = 0x0F;
  	/* enable error detection */
  	Lin_RLINModulePtrTmp->LIN_LEDE = 0x4D;

	/* set wakeup mode - only possible if wake up/frame transmission has not been triggered before (FTS bit is not set) */
  	/* this is guaranteed by the protocol driver */
  	Lin_RLINModulePtrTmp->LIN_LCUC = LIN_LCUC_MODE_WAKEUP;
  	/* wait until LIN module has left reset state */
  	while( ((Lin_RLINModulePtrTmp->LIN_LMST & LIN_LMST_OPERATION_MODE_MASK) != LIN_LMST_WAKEUP_MODE) )
  	{
    		;
  	}
	/* use interrupt vector table index  */
	Lin_ICRPtrTmp->RLINIntTx.lowerICR |= LIN_ICR_TB_SET_MASK;
  	Lin_ICRPtrTmp->RLINIntRx.lowerICR |= LIN_ICR_TB_SET_MASK; 	
  	Lin_ICRPtrTmp->RLINIntErr.lowerICR |= LIN_ICR_TB_SET_MASK;
	/* clear interrupt request flag */
	clr_IrqTxFlag();
	clr_IrqRxFlag();
	clr_IrqErrFlag();
	/* enable interrupt servicing (Mkn=0!) */
	Lin_ICRPtrTmp->RLINIntTx.lowerICR &= LIN_ICR_MK_CLR_MASK;
  	Lin_ICRPtrTmp->RLINIntRx.lowerICR &= LIN_ICR_MK_CLR_MASK;
  	Lin_ICRPtrTmp->RLINIntErr.lowerICR &= LIN_ICR_MK_CLR_MASK;
	
	//Lin_RLINModulePtrTmp->LIN_LDFC = 0x00; 
	/* Header reception/wake-up transmission/reception is started */
	//Lin_RLINModulePtrTmp->LIN_LTRC = 0x01;
} /* End of LinLowInit() */


/**********************************************************************************************************************
  FUNCTION: LinLowSendWakeUpFrame
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: SioChannelHandle        siochannel              Channel parameter (only applicable for indexed channel)
  Output: void                    -                       -
  Return: void                    -                       -
-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: LIN Driver
  Precondition: LinLowInit called before
                SIO Driver must be in sleep state

  Send wakeup signal.
**********************************************************************************************************************/
void LinLowSendWakeUpFrame(SIO_CHANNEL_TYPE_ONLY)
{
	if (( Lin_ChannelDataPtrTmp->Lin_State == Lin_OnSleep ) || ( Lin_ChannelDataPtrTmp->Lin_State == Lin_OnTxWakeup ))
  	{
    		/* already LIN wake up mode entered but FTS bit is already set for wake up reception */
    		/* a wake up frame can now only be triggered if LIN reset mode is entered again before to clear FTS bit */
    		LinLowSetWakeMode(Lin_RLINModulePtrTmp);
    		/* set direction to tx */
    		Lin_RLINModulePtrTmp->LIN_LDFC = 0x10;
    		/* Waiting for confirmation of the wakeup */
    		Lin_ChannelDataPtrTmp->Lin_State = Lin_OnTxWakeup;
		/* trigger wakeup transmission */
    		Lin_RLINModulePtrTmp->LIN_LTRC = 0x01;
  	}/* End of Lin_ChannelDataPtrTmp->Lin_State == Lin_OnSleep */
  	else
  	{
    		/* LinLowSendWakeUpFrame was called when LIN channel was not in Sleep State */
  	}
} /* End of LinLowSendWakeUpFrame() */


/**********************************************************************************************************************
  FUNCTION: LinLowSendMessageFrame
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: SioChannelHandle        siochannel              Channel parameter (only applicable for indexed channel)
          vuint8                  bProtectedId            LIN PID
          vuint8                  dir                     Tx / Rx / No frame (kLinLowTxMsg, kLinLowRxMsg, kLinLowNoMsg)
          vuint8                  dlc                     Data Length Code
          vuint8                  checksumtype            Checksum (kLinLowCsClassic, kLinLowCsEnhanced)
          vuint8 *                pbData                  Pointer to data buffer
  Output: void                    -                       -
  Return: vuint8                  -                       0x00: Message started; 0x01: Hardware busy, no message started
-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: LIN Driver
  Precondition: LinLowInit called before

  Send a LIN message (rx or tx)
**********************************************************************************************************************/
vuint8 LinLowSendMessageFrame(SIO_CHANNEL_TYPE_FIRST vuint8 identifier, vuint8 dir, vuint8 dlc, vuint8 checksumtype, vuint8* pbData)
{
	vuint8  Lin_FrameCsModelTmp;
	 /* clear status flags */
    	Lin_RLINModulePtrTmp->LIN_LST  = 0x00;
    	Lin_RLINModulePtrTmp->LIN_LEST = 0x00;
  	/* configure data length */
  	if(checksumtype == kLinLowCsEnhanced)
  	{
    		Lin_FrameCsModelTmp = 0x20;
  	}
  	else
  	{
  		Lin_FrameCsModelTmp = 0x00;
  	}
  	if (dir == kLinLowTxMsg)
  	{
  		/* LIN data field configuration */
  		Lin_RLINModulePtrTmp->LIN_LDFC = (vuint8)(Lin_FrameCsModelTmp | 0x10 | (0x0F & dlc));
    		/* copy data to transmit buffer */
      		Lin_RLINModulePtrTmp-> LIN_LDBR1 = pbData[0x00u];
      		Lin_RLINModulePtrTmp-> LIN_LDBR2 = pbData[0x01u];
      		Lin_RLINModulePtrTmp-> LIN_LDBR3 = pbData[0x02u];
      		Lin_RLINModulePtrTmp-> LIN_LDBR4 = pbData[0x03u];
      		Lin_RLINModulePtrTmp-> LIN_LDBR5 = pbData[0x04u];
      		Lin_RLINModulePtrTmp-> LIN_LDBR6 = pbData[0x05u];
      		Lin_RLINModulePtrTmp-> LIN_LDBR7 = pbData[0x06u];
      		Lin_RLINModulePtrTmp-> LIN_LDBR8 = pbData[0x07u];
		Lin_ChannelDataPtrTmp->Lin_State = Lin_OnTx;
		/* Response transmission/reception is started. */
    		Lin_RLINModulePtrTmp->LIN_LTRC = 0x02;
  	}
  	else if (dir == kLinLowRxMsg)
  	{
  		/* LIN data field configuration */
  		Lin_RLINModulePtrTmp->LIN_LDFC = (vuint8)(Lin_FrameCsModelTmp | 0x00 | (0x0F & dlc));
    		/* receive response */
		Lin_RLINModulePtrTmp-> LIN_LDBR1 = 0x5A; /* pattern to identify if bytes of the response are received or not */
		Lin_RLINModulePtrTmp-> LIN_LDBR2 = 0x5A; /* pattern to identify if bytes of the response are received or not */
    		Lin_ChannelDataPtrTmp->Lin_State = Lin_OnRx;
		Lin_RLINModulePtrTmp->LIN_LTRC = 0x02; /* Response reception is started  */
  	}
  	else
  	{
  		//Lin_RLINModulePtrTmp->LIN_LDFC = 0x00;
  		/* Ignore response and wait for next synch break */
  		Lin_ChannelDataPtrTmp->Lin_State = Lin_OnWake;
		Lin_RLINModulePtrTmp->LIN_LTRC |= 0x40;
  	}
  	return 0x00u;  /* Message transmission always successful */
} /* End of LinLowSendMessageFrame() */


/**********************************************************************************************************************
  FUNCTION: LinLowRespTimeoutFunc
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: SioChannelHandle        siochannel              Channel parameter (only applicable for indexed channel)
  Output: void                    -                       -
  Return: vuint8                  kFpTimerNoResponse      No response byte was transmitted/received
        : vuint8                  kFpTimerIncResponse     Incomplete Response
-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: LIN Driver
  Precondition: SIO Driver has been initialized

  When a response timeout is detected by the protocol driver this function returns if the response
  was incomplete or if no response was transmitted/received
**********************************************************************************************************************/
vuint8 LinLowRespTimeoutFunc(SIO_CHANNEL_TYPE_ONLY)
{
  	vuint8 tmpReturn;
  	tmpReturn = kFpTimerNoResponse;
  	if ((Lin_ChannelDataPtrTmp->Lin_State == Lin_OnTx) || ((Lin_ChannelDataPtrTmp->Lin_State == Lin_OnRx) && ((Lin_RLINModulePtrTmp-> LIN_LDBR1) == 0x5A)))
  	{ /* no transmit error interrupt obtained or no byte received */
    		tmpReturn = kFpTimerNoResponse;
  	}
  	else
  	{
    		tmpReturn = kFpTimerIncResponse;
  	}
  	Lin_ChannelDataPtrTmp->Lin_State = Lin_OnWake;
	//Lin_RLINModulePtrTmp->LIN_LDFC = 0x00;
	/* set communication bit to enable wakeup frame reception */
  	Lin_RLINModulePtrTmp->LIN_LTRC = 0x01;
  	return tmpReturn;
}

/**********************************************************************************************************************
  FUNCTION: SioSetMuteMode
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: SioChannelHandle        siochannel              Channel parameter (only applicable for indexed channel)
  Output: void                    -                       -
  Return: void                    -                       -
-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: LIN Driver
  Precondition: SIO Driver has been initialized

  Sets the LIN interface to ignore all none synch break events
**********************************************************************************************************************/
void SioSetMuteMode(SIO_CHANNEL_TYPE_ONLY)
{
	if (Lin_ChannelDataPtrTmp->Lin_State == Lin_OnSleep)
  	{ /* external wake up detected - set back to normal mode */
    		LinLowSetNormalMode(Lin_RLINModulePtrTmp);
    		/* NOTE: the check for failed wakeup frame transmission does not work. A disturbance on the LIN line during WP transmission is not
    		recognized by HW. But actually this behavior is supported when disturbing directly on the TX line. */
    		Lin_ChannelDataPtrTmp->Lin_State = Lin_OnWake;
		//Lin_RLINModulePtrTmp->LIN_LDFC = 0x00;
		/* set communication bit to enable wakeup frame reception */
  		Lin_RLINModulePtrTmp->LIN_LTRC = 0x01;
  	}
} /* End of SioSetMuteMode() */

/**********************************************************************************************************************
  FUNCTION: SioResetMuteMode
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: SioChannelHandle        siochannel              Channel parameter (only applicable for indexed channel)
  Output: void                    -                       -
  Return: void                    -                       -
-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: LIN Driver
  Precondition: SIO Driver has been initialized

  Sets the LIN interface to detect a wakeup frame
**********************************************************************************************************************/
void SioResetMuteMode(SIO_CHANNEL_TYPE_ONLY)
{
	LinLowSetWakeMode(Lin_RLINModulePtrTmp);
  	/* Sleep mode frame was just transmitted */
  	Lin_ChannelDataPtrTmp->Lin_State = Lin_OnSleep;
	/* set direction to RX */
  	Lin_RLINModulePtrTmp->LIN_LDFC = 0x00;/*Jiaye enable 20180116*/
	/* set communication bit to enable wakeup frame reception */
  	Lin_RLINModulePtrTmp->LIN_LTRC = 0x01;
} /* End of SioResetMuteMode() */

/**********************************************************************************************************************
  FUNCTION: SioInterruptDisable
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: SioChannelHandle        siochannel              Channel parameter (only applicable for indexed channel)
  Output: void                    -                       -
  Return: void                    -                       -
-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: LIN Driver
  Precondition: SIO Driver has been initialized

  Disables the channel specific LIN interrupt
**********************************************************************************************************************/
void SioInterruptDisable(SIO_CHANNEL_TYPE_ONLY)
{
	VStdSuspendAllInterrupts();
	bLinLowInterruptDisableCounter++;
	Lin_ICRPtrTmp ->RLINIntRx.lowerICR |= LIN_ICR_MK_SET_MASK;
  	Lin_ICRPtrTmp ->RLINIntTx.lowerICR |= LIN_ICR_MK_SET_MASK;
  	Lin_ICRPtrTmp ->RLINIntErr.lowerICR |= LIN_ICR_MK_SET_MASK;
	VStdResumeAllInterrupts();
} /* End of SioInterruptDisable() */

/**********************************************************************************************************************
  FUNCTION: SioInterruptRestore
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: SioChannelHandle        siochannel              Channel parameter (only applicable for indexed channel)
  Output: void                    -                       -
  Return: void                    -                       -
-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: LIN Driver
  Precondition: SIO Driver has been initialized

  Restores the channel specific LIN interrupt
**********************************************************************************************************************/
void SioInterruptRestore(SIO_CHANNEL_TYPE_ONLY)
{
  	VStdSuspendAllInterrupts();
  	if ( bLinLowInterruptDisableCounter > ((vuint8)0x00u) )
  	{
    		/* decrement counter when it has been incremented before */
    		bLinLowInterruptDisableCounter--;
  	}
  	if ( bLinLowInterruptDisableCounter == ((vuint8)0x00u) )
  	{
    		/* If interrupt counter reached zero restore interrupt */
    		Lin_ICRPtrTmp ->RLINIntRx.lowerICR &= LIN_ICR_MK_CLR_MASK;
    		Lin_ICRPtrTmp ->RLINIntTx.lowerICR &= LIN_ICR_MK_CLR_MASK;
    		Lin_ICRPtrTmp ->RLINIntErr.lowerICR &= LIN_ICR_MK_CLR_MASK;
  	}
  	VStdResumeAllInterrupts();
} /* End of SioInterruptRestore() */

/**********************************************************************************************************************
  END OF FILE: sio_drv.c
**********************************************************************************************************************/

