/*******************************************************************************************/
/*===================== COPYRIGHT (C) HUIZHOU DESAY SV AUOTMOTIVE 2016 ====================*/
/*******************************************************************************************
* C Source     : SIIC.h
*
* Description  : Header file for IIC module which belongs to App Layer.
*
* Environment  : autosar 4.x SC1, Renesas RH850, Greenhills Multi 6.1.6
*
* Created_by   : R2S Platform team, BIC R&D
*
* Template name: SIIC.h
*
*    Rev 1.1.0   Apr 10 2018,  hxr
*    Initial revision.
*
********************************************************************************************/

/*******************************************************************************************
* FILE DECLARATION
********************************************************************************************/
#ifndef IIC_H /* To avoid double inclusion */
#define IIC_H
//#include "r_dev_api.h"
#include "General.h"
//#include "BSP_Cfg.h"
#include "IIC_Cfg.h"
/*******************************************************************************************
* LOCAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants and macros to configure your register. These constants are only belong to
* this module.
********************************************************************************************/
/* Configure Register instance, it will not be appear in actual coding */


/*Declare all system global variables of your module.*/



/*******************************************************************************************
* EXTENAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants and macros to configure your export interface. These constants are public for
*   other modules
********************************************************************************************/
extern void Siic_Init(Siic_Chn ChannelID);
/*uint8*/

extern uint8 Siic_u8SendChar(Siic_Chn ChannelID, uint8 u8Address, uint8 DataByte);

extern uint8 Siic_u8ReceiveChar(Siic_Chn ChannelID, uint8 u8Address, uint8* pDataByte);

extern uint8 Siic_u8SendBlock(Siic_Chn ChannelID, uint8 u8Address, uint16 u16NumOfBytes, uint8* pDataByte);

extern uint8 Siic_u8ReceiveBlock(Siic_Chn ChannelID, uint8 u8Address, uint16 u16NumOfBytes, uint8* pDataByte);

/*uint16*/
extern uint8 Siic_u16SendChar(Siic_Chn ChannelID, uint16 u8Address, uint8 DataByte);

extern uint8 Siic_u16ReceiveChar(Siic_Chn ChannelID, uint16 u8Address, uint8* pDataByte);

extern uint8 Siic_u16SendBlock(Siic_Chn ChannelID, uint16 u16Address, uint16 u16NumOfBytes, uint8* pDataByte);

extern uint8 Siic_u16ReceiveBlock(Siic_Chn ChannelID, uint16 u16Address, uint16 u16NumOfBytes, uint8* pDataByte);

extern void Siic_SetSlaveAddress(Siic_Chn ChannelID, uint8 u8Address);
extern uint16 HALGPIO_Value_Get(uint16 gpio);

/*******************************************************************************************
* End of check if informations are already included
********************************************************************************************/
#endif /* ifndef SIIC_H */

/*******************************************************************************************
* EOF: SIIC_Cfg.h
********************************************************************************************/

