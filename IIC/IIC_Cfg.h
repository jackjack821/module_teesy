/*******************************************************************************************/
/*===================== COPYRIGHT (C) HUIZHOU DESAY SV AUOTMOTIVE 2016 ====================*/ 
/*******************************************************************************************
* C Source     : SIIC_Cfg.h
*
* Description  : Header file for IIC module which belongs to App Layer.
*
* Environment  : autosar 4.x SC1, Renesas RH850, Greenhills Multi 6.1.6
*
* Created_by   : R2S Platform team, BIC R&D 
*
* Template name: SIIC_Cfg.h
*
*    Rev 1.1.0   Apr 10 2018,  hxr                                     
*    Initial revision.
*
********************************************************************************************/

/*******************************************************************************************
* FILE DECLARATION
********************************************************************************************/
#ifndef IIC_CFG_H /* To avoid double inclusion */ 
#define IIC_CFG_H
//#include "r_dev_api.h"
#include "MCU_CFG.h"
//#include "IIC.h"
//#include "F1L.h"
/*******************************************************************************************
* LOCAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants and macros to configure your register. These constants are only belong to  
* this module.  
********************************************************************************************/
#ifndef ACK
#define ACK             0
#endif

#ifndef NOACK
#define NOACK           1
#endif

#ifndef WRITE
#define WRITE           0
#endif

#ifndef READ
#define READ            1
#endif

#ifndef SLAVE_SELECT
#define SLAVE_SELECT    0
#endif

#ifndef DATA_WRITE
#define DATA_WRITE      1
#endif

// start condition ack retries [wait internal write cycle completed]
#define TRIALS          2000

#ifndef GPIO_OUT
#define GPIO_OUT  (0u)
#endif
#ifndef GPIO_IN
#define GPIO_IN  (1u)
#endif

#ifndef GPIO_HI
#define GPIO_HI (1u)
#endif
#ifndef GPIO_LO
#define GPIO_LO  (0u)
#endif

#define SLAVE_ADDRESS_NOINIT 0
#define SIIC_DEV_PIN_NOUSED 0xFFFF


#define Scii_Dio_SetInput(Pin)      MCU_u16PinDirectCfg(Pin,GPIO_IN)
#define Scii_Dio_SetOutput(Pin)    MCU_u16PinDirectCfg(Pin,GPIO_OUT)
#define Scii_Dio_SetHigh(Pin)       MCU_u16PinWrite(Pin,GPIO_HI)
#define Scii_Dio_SetLow(Pin)       MCU_u16PinWrite(Pin,GPIO_LO)
#define Scii_Dio_GetVal(Pin)        HALGPIO_Value_Get(Pin)

typedef enum
{
	SIIC_NotReady=0u,
	SIIC_Ready,
	SIIC_Busy,
	SIIC_Error,
}SiicStatusTyp;


/*device*/
typedef enum
{
	Siic_Dev_0,
//	Siic_Dev_1,
	Siic_Dev_1,
	Siic_Dev_Max
}Siic_Dev;

/*channel*/
typedef enum
{
	Siic_Chn_0,//lp8860
//	Siic_Chn_1,//eeprom
	Siic_Chn_1,//eeprom
	Siic_Chn_Max
}Siic_Chn;

typedef struct SiicDev
{
	const Siic_Dev DevId;
	const MUC_enPinID SclPin; 
	const MUC_enPinID SdaPin; 
	const MUC_enPinID WcPin; /*eeprom */
	SiicStatusTyp Status;
}SiicDevConfig_t; 

/* Write Control (WC). 
This  input  signal  is  useful
for  protecting  the entire contents of  the  memory
from  inadvertent  write  operations.  Write  opera-
tions are disabled to the entire memory array when
Write Control (WC) is driven High. When uncon-
nected,  the  signal  is  internally  read  as  VIL,  and
Write operations are allowed.
When Write Control (WC) is driven High, Device
Select  and  Address  bytes  are  acknowledged,
Data bytes are not acknowledged.
*/

typedef struct SiicChn
{
	const struct SiicDev *SiicDevice;
	uint8 SlaveAddress;
}SiicChnConfig_t; 


/* Configure Register instance, it will not be appear in actual coding */
extern struct SiicDev SiicDevConfig[Siic_Dev_Max];
extern /*const*/ SiicChnConfig_t SiicChnConfig[Siic_Chn_Max];

/*Declare all system global variables of your module.*/



/*******************************************************************************************
* EXTENAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants and macros to configure your export interface. These constants are public for 
*   other modules
********************************************************************************************/


/*******************************************************************************************
* End of check if informations are already included
********************************************************************************************/
#endif /* ifndef SIIC_CFG_H */

/*******************************************************************************************
* EOF: SIIC_Cfg.h
********************************************************************************************/
