/*******************************************************************************************/
/*===================== COPYRIGHT (C) HUIZHOU DESAY SV AUOTMOTIVE 2018 ====================*/
/*******************************************************************************************
* C Source     : SIIC.c
*
* Description  : Source file for IIC module which belongs to App Layer.
*
* Environment  : autosar 4.x SC1, Renesas RH850, Greenhills Multi 6.1.6
*
* Created_by   : R2S Platform team, BIC R&D
*
* Template name: SIIC_Cfg.c
*
*    Rev 1.1.0   xx-xx-xx,  hxr
*    Initial revision.
*
********************************************************************************************/

/*******************************************************************************************
* FILE DECLARATION
********************************************************************************************/
#define SIIC_C              /* Name of the Module */

/*******************************************************************************************
* HEADER-FILES (Only those that are needed in this file)
********************************************************************************************/

/* System-headerfiles */
//#include "r_typedefs.h"           /* General definitions and datatypes */
//#include "_RH850.h"

//#include "HAL_Gpio.h"

/* Own headerfiles */
//
#include "IIC.h"
#include "IIC_Cfg.h"           /* Inclusion the head file of this module */
//#include "MCU_CFG.h"
static uint8 InternalStart(Siic_Chn ChannelID, uint8 wr);
static void InternalStop(Siic_Chn ChannelID);
/*******************************************************************************************
* CONFIG SERVICE
*
* In this section list
* - all interrupt service routine in your module.
********************************************************************************************/

void Siic_Init(Siic_Chn ChannelID)
{

	SiicDevConfig[ChannelID].Status = SIIC_NotReady;
	//if(SIIC_DEV_PIN_NOUSED != (*SiicChnConfig[ChannelID].SiicDevice).WcPin)
	//{
		//Scii_Dio_SetHigh((*SiicChnConfig[ChannelID].SiicDevice).WcPin);
	//}
}

static void Delay(void)
{
	/* delay 2us */
	uint16 u8Wait = 10;
	while(u8Wait != 0u)
	{
		u8Wait--;
	}
}

/*
** ===================================================================
**     Method      :  GetAck
**
**     Description :
**         The method reads ACK from the bus.
** ===================================================================
*/
static uint8 GetAck(Siic_Chn ChannelID)
{
	uint16 timeout;
	uint8 value = 0;

	Scii_Dio_SetInput((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);/* SDA HIGH */
	Scii_Dio_SetInput((*SiicChnConfig[ChannelID].SiicDevice).SclPin); /* CLOCK HIGH PULSE */
	Delay();
	timeout = 65535;

	do
	{
		value = Scii_Dio_GetVal((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
		timeout--;
	}
	while((value == 0) && (timeout != 0));

	value = Scii_Dio_GetVal((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);

	return value;
}

/*
** ===================================================================
**     Method      :  SetAck
**
**     Description :
**         The method sends ACK to the bus.
** ===================================================================
*/
static void SetAck(Siic_Chn ChannelID, uint8 Ack)
{
	uint16 timeout;
	uint8 value = 0;

	if (Ack)
	{
		/* MASTER NOACKNOWLEDGE - SDA HIGH */
		Scii_Dio_SetInput((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);
	}
	else
	{
		Scii_Dio_SetOutput((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);
		/* MASTER ACKNOWLEDGE - SDA LOW */
		Scii_Dio_SetLow((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);
	}
	/* HIGH CLOCK PULSE */
	Scii_Dio_SetInput((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
	Delay();
	timeout = 65535;
	do
	{
		timeout--;
		value = Scii_Dio_GetVal((*SiicChnConfig[ChannelID].SiicDevice).SclPin/*,&value*/);
	}
	while((value == 0) && (timeout != 0));
	Scii_Dio_SetOutput((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
	/* LOW CLOCK PULSE */
	Scii_Dio_SetLow((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
	Delay();
	/* ACKNOWLEDGE END - SDA HIGH  */
	Scii_Dio_SetInput((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);
}


static uint8 Write(Siic_Chn ChannelID, uint8 Data, uint8 opr)
{
	uint8 i, Shift, value = 0;
	uint16 timeout;

	// 1, WRITE ONE uint8
	Shift = 128;
	for (i = 8; i != 0; i--)
	{
		if(Data & Shift)
		{
			Scii_Dio_SetInput((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);
		}
		else
		{
			Scii_Dio_SetOutput((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);
			Scii_Dio_SetLow((*SiicChnConfig[ChannelID].SiicDevice).SdaPin); /* SDA LOW */
		}
		Shift >>= 1;
		Scii_Dio_SetInput((*SiicChnConfig[ChannelID].SiicDevice).SclPin); /* CLOCK HIGH PULSE */
		Delay();
		timeout = 65535;
		do
		{
			value = Scii_Dio_GetVal((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
			timeout--;
		}
		while((value == GPIO_LO) && (timeout != 0));
		Scii_Dio_SetOutput((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
		Scii_Dio_SetLow((*SiicChnConfig[ChannelID].SiicDevice).SclPin); /* CLOCK LOW PULSE */
		Delay();
	}

	// 2, CHECK ACK
	if(DATA_WRITE == opr)
	{
		if (GetAck(ChannelID))
		{
			/* WRONG ACKNOWLEDGE */
			Scii_Dio_SetOutput((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
			Scii_Dio_SetLow((*SiicChnConfig[ChannelID].SiicDevice).SclPin);  /* CLOCK LOW PULSE */
			InternalStop(ChannelID);
			return False;
		}
		else/* ACKNOWLEDGE HAPPENS */
		{
			Scii_Dio_SetOutput((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
			Scii_Dio_SetLow((*SiicChnConfig[ChannelID].SiicDevice).SclPin);/* CLOCK LOW PULSE */
			Delay();
		}
	}
	return True;

}

/*
** ===================================================================
**     Method      :  Read
**
**     Description :
**         The method reads one uint8 of data from the bus.
** ===================================================================
*/
static uint8 Read(Siic_Chn ChannelID)
{
	uint8 Shift;
	uint8 i, value = 0;
	uint16 timeout;

	Shift = 0;
	/* SDA INPUT MODE */
	Scii_Dio_SetInput((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);
	for (i = 8; i != 0; i--)
	{
		/* CLOCK HIGH PULSE */
		Scii_Dio_SetInput((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
		Delay();
		timeout = 65535;
		do
		{
			value = Scii_Dio_GetVal((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
			timeout--;
		}
		while((value == 0) && (timeout != 0));  /* WAIT FOR CLOCK HIGH PULSE */

		Shift <<= 1;
		value = Scii_Dio_GetVal((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);
		if(value)
		{
			Shift++;
		}
		Scii_Dio_SetOutput((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
		/* CLOCK LOW PULSE */
		Scii_Dio_SetLow((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
		Delay();
	}

	return Shift;
}

/*
** ===================================================================
**     Method      :  InternalStart
**
**     Description :
**         The method generates the start condition on the bus.
** ===================================================================
*/
////////////////////////////////////////////////////////////////////////////////
static uint8 InternalStart(Siic_Chn ChannelID, uint8 wr)
////////////////////////////////////////////////////////////////////////////////
{
	uint8 Acknowledge, SlaveAddr;
	uint16 Trial;

	if(SIIC_DEV_PIN_NOUSED != (*SiicChnConfig[ChannelID].SiicDevice).WcPin)
	{
		Scii_Dio_SetLow((*SiicChnConfig[ChannelID].SiicDevice).WcPin);
	}

	Trial = TRIALS;
	do
	{
		/* SDA HIGH  - START SETUP */
		Scii_Dio_SetInput((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);
		/* CLOCK HIGH PULSE */
		Scii_Dio_SetInput((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
		Delay();                       /* CLOCK HIGH PULSE + BUS FREE TIME */
		Scii_Dio_SetOutput((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);
		/* START CONDITION */
		Scii_Dio_SetLow((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);
		Delay();                       /* START HOLD TIME */
		Scii_Dio_SetOutput((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
		/* CLOCK LOW PULSE */
		Scii_Dio_SetLow((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
		Delay();
		SlaveAddr = SiicChnConfig[ChannelID].SlaveAddress;
		(void)Write(ChannelID, (SlaveAddr + wr), SLAVE_SELECT);

		Acknowledge = GetAck(ChannelID);
		--Trial;
	}
	while (Trial && Acknowledge);

	if (Acknowledge)
	{
		Scii_Dio_SetOutput((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
		/* CLOCK LOW PULSE */
		Scii_Dio_SetLow((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
		InternalStop(ChannelID);
		return False;
	}
	else
	{
		Scii_Dio_SetOutput((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
		/* CLOCK LOW PULSE */
		Scii_Dio_SetLow((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
		Delay();
	}
	return True;
}

/*
** ===================================================================
**     Method      :  InternalStop
**
**     Description :
**         The method generates the Stop condition on the bus.
** ===================================================================
*/
////////////////////////////////////////////////////////////////////////////////
static void InternalStop(Siic_Chn ChannelID)
{
	Scii_Dio_SetOutput((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);
	/* STOP SETUP */
	Scii_Dio_SetLow((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);
	/* CLOCK HIGH PULSE + STOP SETUP TIME */
	Scii_Dio_SetInput((*SiicChnConfig[ChannelID].SiicDevice).SclPin);
	Delay();
	/* STOP CONDITION */
	Scii_Dio_SetInput((*SiicChnConfig[ChannelID].SiicDevice).SdaPin);

	if(SIIC_DEV_PIN_NOUSED != (*SiicChnConfig[ChannelID].SiicDevice).WcPin)
	{
		Scii_Dio_SetHigh((*SiicChnConfig[ChannelID].SiicDevice).WcPin);
	}
}


uint8 Siic_u8SendChar(Siic_Chn ChannelID, uint8 u8Address, uint8 DataByte)
{
	uint8 returnVar = False;

	if(SIIC_Busy == SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status)
		return False;

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Busy;
	// BUS START CONDITION
	returnVar = InternalStart(ChannelID, WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	returnVar = Write(ChannelID, u8Address, DATA_WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	// ONE uint8 WRITE
	returnVar = Write(ChannelID, DataByte, DATA_WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	// BUS STOP CONDITION
	InternalStop(ChannelID);

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Ready;

	return True;
}

uint8 Siic_u8ReceiveChar(Siic_Chn ChannelID, uint8 u8Address, uint8* pDataByte)
{
	//!!!! default perform random read !!!!//

	uint8 returnVar = True;

	if(SIIC_Busy == SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status)
		return False;

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Busy;

	// BUS START CONDITION
	returnVar = InternalStart(ChannelID, WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	returnVar = Write(ChannelID, u8Address, DATA_WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	// BUS START CONDITION AGAIN
	returnVar = InternalStart(ChannelID, READ);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	// PERFORM READ
	*pDataByte = Read(ChannelID);
	// READ END
	SetAck(ChannelID, (uint8)NOACK);

	// BUS STOP CONDITION
	InternalStop(ChannelID);

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Ready;

	return True;
}


uint8 Siic_u8SendBlock(Siic_Chn ChannelID, uint8 u8Address, uint16 u16NumOfBytes, uint8* pDataByte)
{
	uint8 returnVar = False;
	uint16 i;

	if(SIIC_Busy == SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status)
		return False;

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Busy;
	// BUS START CONDITION
	returnVar = InternalStart(ChannelID, WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	returnVar = Write(ChannelID, u8Address, DATA_WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	for(i = 0; i < u16NumOfBytes; i++)
	{
		if(False == Write(ChannelID, *((uint8 *)pDataByte + i), DATA_WRITE))
		{
			SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
			return False;
		}
	}

	// BUS STOP CONDITION
	InternalStop(ChannelID);

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Ready;

	return True;
}

uint8 Siic_u8ReceiveBlock(Siic_Chn ChannelID, uint8 u8Address, uint16 u16NumOfBytes, uint8* pDataByte)
{
	//!!!! default perform random read !!!!//
	uint16 i;
	uint8 returnVar = True;

	if(SIIC_Busy == SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status)
		return False;

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Busy;
	// BUS START CONDITION
	returnVar = InternalStart(ChannelID, WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	returnVar = Write(ChannelID, u8Address, DATA_WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	// BUS START CONDITION AGAIN
	returnVar = InternalStart(ChannelID, READ);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	// PERFORM READ

	for(i = 0; i < u16NumOfBytes; i++)
	{
		*((uint8 *)pDataByte + i) = Read(ChannelID);

		// READ END??
		if (i == (u16NumOfBytes - 1))
		{
			SetAck(ChannelID, NOACK);
		}
		else
		{
			SetAck(ChannelID, ACK);
		}
	}

	// BUS STOP CONDITION
	InternalStop(ChannelID);

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Ready;

	return True;
}


uint8 Siic_u16SendChar(Siic_Chn ChannelID, uint16 u16Address, uint8 DataByte)
{
	uint8 returnVar = False;

	if(SIIC_Busy == SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status)
		return False;

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Busy;
	// BUS START CONDITION
	returnVar = InternalStart(ChannelID, WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	returnVar = Write(ChannelID, (uint8)(u16Address >> 8), DATA_WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	returnVar = Write(ChannelID, (uint8)u16Address, DATA_WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	// ONE uint8 WRITE
	returnVar = Write(ChannelID, DataByte, DATA_WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	// BUS STOP CONDITION
	InternalStop(ChannelID);

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Ready;

	return True;
}


uint8 Siic_u16ReceiveChar(Siic_Chn ChannelID, uint16 u16Address, uint8* pDataByte)
{
	//!!!! default perform random read !!!!//

	uint8 returnVar = True;

	if(SIIC_Busy == SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status)
		return False;

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Busy;
	// BUS START CONDITION
	returnVar = InternalStart(ChannelID, WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	returnVar = Write(ChannelID, (uint8)(u16Address >> 8), DATA_WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	returnVar = Write(ChannelID, (uint8)u16Address, DATA_WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	// BUS START CONDITION AGAIN
	returnVar = InternalStart(ChannelID, READ);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	// PERFORM READ
	*pDataByte = Read(ChannelID);
	// READ END
	SetAck(ChannelID, (uint8)NOACK);

	// BUS STOP CONDITION
	InternalStop(ChannelID);

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Ready;

	return True;
}

uint8 Siic_u16SendBlock(Siic_Chn ChannelID, uint16 u16Address, uint16 u16NumOfBytes, uint8* pDataByte)
{
	uint8 returnVar = False;
	uint16 i;

	if(SIIC_Busy == SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status)
		return False;

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Busy;
	// BUS START CONDITION
	returnVar = InternalStart(ChannelID, WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	returnVar = Write(ChannelID, (uint8)(u16Address >> 8), DATA_WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	returnVar = Write(ChannelID, (uint8)u16Address, DATA_WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	for(i = 0; i < u16NumOfBytes; i++)
	{
		if(False == Write(ChannelID, *((uint8 *)pDataByte + i), DATA_WRITE))
		{
			SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
			return False;
		}
	}

	// BUS STOP CONDITION
	InternalStop(ChannelID);

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Ready;

	return True;
}

uint8 Siic_u16ReceiveBlock(Siic_Chn ChannelID, uint16 u16Address, uint16 u16NumOfBytes, uint8* pDataByte)
{
	//!!!! default perform random read !!!!//
	uint16 i;
	uint8 returnVar = True;

	if(SIIC_Busy == SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status)
		return False;

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Busy;
	// BUS START CONDITION
	returnVar = InternalStart(ChannelID, WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	returnVar = Write(ChannelID, (uint8)(u16Address >> 8), DATA_WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	returnVar = Write(ChannelID, (uint8)u16Address, DATA_WRITE);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}


	// BUS START CONDITION AGAIN
	returnVar = InternalStart(ChannelID, READ);
	if(False == returnVar)
	{
		SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Error;
		return False;
	}

	// PERFORM READ

	for(i = 0; i < u16NumOfBytes; i++)
	{
		*((uint8 *)pDataByte + i) = Read(ChannelID);

		// READ END??
		if (i == (u16NumOfBytes - 1))
		{
			SetAck(ChannelID, NOACK);
		}
		else
		{
			SetAck(ChannelID, ACK);
		}
	}

	// BUS STOP CONDITION
	InternalStop(ChannelID);

	SiicDevConfig[(*SiicChnConfig[ChannelID].SiicDevice).DevId].Status = SIIC_Ready;

	return True;
}

void Siic_SetSlaveAddress(Siic_Chn ChannelID, uint8 u8Address)
{
	uint8 retAddress;

	retAddress = u8Address << 1;

	SiicChnConfig[ChannelID].SlaveAddress = retAddress;
}

uint8 Siic_GetSlaveAddress(Siic_Chn ChannelID, uint8 u8Address)
{
	uint8 retAddress;

	retAddress = SiicChnConfig[ChannelID].SlaveAddress >> 1;

	return retAddress;
}

uint16 HALGPIO_Value_Get(uint16 gpio)
{
	uint8 gpio_value;

	MCU_u16PinRead(gpio, &gpio_value);

	return gpio_value;
}

/*******************************************************************************************
* EOF: IIC_Cfg.c
********************************************************************************************/
