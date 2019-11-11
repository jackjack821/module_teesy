/*******************************************************************************
| Module Name: simulation IIC  model
| File Name: S_IIC.c
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2015 Huizhou Desay SV Automotive Co., Ltd.    All rights reserved.
|
| This software is copyright protected and proprietary to Desay SV Automotive Co., Ltd.
| Desay SV Automotive Co., Ltd grants to you only those rights as set out in the
| license conditions. All other rights remain with Desay SV Automotive Co., Ltd.
|
| REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
|-------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Name                                  Company
| ---------------------     ---------------------------------------
|Tan Fumin                       Desay SV Automotive Co., Ltd
|
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver        	Author               Description
| ----------  -------  -------------  -------------------------------------------------
|2014/10/28 Rev 00.00.00     Tan Fumin				The first version  
| 2015/06/09 Rev 01.00.00   Tan Fumin				update for MISRA C rules
| 2016/01/26 Rev 02.00.00   Tan Fumin				update to be standard for SVN basic code
********************************************************************************/

#define S_IIC_DRV  

#include "./S_IIC.h"
#include "det.h"


#if S_IIC_CHANNEL_NUMBER>=1U

void IIC_CH1_SlaveNotAckErrCB(void);
uint8 IIC_u8CH1_Satus=IIC_enBusy;

/*****************************************************************************
 Function  : IIC_vDrvInit_CH1												 
 Description   :initialization the IIC I/O pin to be ready 
 
 In Parameter: 
 			NULL
 			
Return Value:
 			NULL
 			
 NOTE: 		
 			after execute this function, 
 				SDA=High,output
 				SCK=High
*****************************************************************************/
void IIC_vDrvInit_CH1(void)
{
	S_IIC_CH1_SetReady();
}

/*****************************************************************************
 Function  : IIC_vDrvDeInit_CH1												 
 Description   :De-initialization the IIC I/O pin to be ready 
 
 In Parameter: 
 			NULL
 			
Return Value:
 			NULL
 			
 NOTE: 		
 			after execute this function, 
 				SDA=High,output
 				SCK=High
*****************************************************************************/
void IIC_vDrvDeInit_CH1(void)
{
	S_IIC_CH1_Exit();
}

/*****************************************************************************
 Function  : IIC_vStartCondition_CH1												 
 Description   :generate a start-condition for prepare data transfer
 
 In Parameter: 
 			NULL
 			
Return Value:
 			NULL
 			
 NOTE: 		
 			after execute this function, 
 				SDA=Low,output
 				SCK=Low
*****************************************************************************/
void IIC_vStartCondition_CH1(void)
{
	S_IIC_CH1_SetSCLHigh();
	S_IIC_CH1_ClkDelay();
	
	S_IIC_CH1_SetSDAHigh();
	S_IIC_CH1_ClkDelay();
	
	S_IIC_CH1_SetSDALow();
	S_IIC_CH1_ClkDelay();
	
	S_IIC_CH1_SetSCLLow();
	S_IIC_CH1_ClkDelay();
	
}

/*****************************************************************************
 Function  : IIC_vStopCondition_CH1												 
 Description   :generate a stop-condition for prepare data transfer
 
 In Parameter: 
 			NULL
 			
Return Value:
 			NULL
 			
 NOTE: 		
 			after execute this function, 
 				SDA=High,output
 				SCK=High
*****************************************************************************/
void IIC_vStopCondition_CH1(void)
{
	S_IIC_CH1_SetSCLLow();
	S_IIC_CH1_ClkDelay();

	S_IIC_CH1_SetSDALow();
	S_IIC_CH1_ClkDelay();
	
	S_IIC_CH1_SetSCLHigh();
	S_IIC_CH1_ClkDelay();

	S_IIC_CH1_SetSDAHigh();
	S_IIC_CH1_ClkDelay();
}

/*****************************************************************************
 Function  : IIC_u16SendData_CH1												 
 Description   :send data to slave node
 
 In Parameter: 
 			pOutDataHead : output data head
 			u16DataLen : data lenth(in byte)
 			
Return Value:
 			function execute resault
 			
 NOTE: 		
 			after execute this function, 
 				SDA=Low,output
 				SCK=Low
*****************************************************************************/
uint16 IIC_u16SendData_CH1(uint8 pOutDataHead[], uint16 u16DataLen)
{
	uint8 u8totallIndex;
	uint8 OutData,u8i;
	uint8 u8MaskData;
    uint16 u16GetValue;
	
	uint16 u16RetVal=DET_Err_NotErr;

	/*check driver status*/
	if(IIC_u8CH1_Satus !=IIC_enReady)
	{
		DET_ErrReport(DET_Err_IICNotReady);
		u16RetVal =  DET_Err_IICNotReady;
	}
	else
	{
	
		IIC_u8CH1_Satus=IIC_enBusy;		
		
		/*totall loops*/
		for(u8totallIndex=0U;u8totallIndex<u16DataLen;u8totallIndex++)
		{
			OutData=pOutDataHead[u8totallIndex];
            
                #if S_IIC_CH1_DataField == S_IIC_DataField_LSB
                     u8MaskData=1u;
                #elif S_IIC_CH1_DataField ==S_IIC_DataField_MSB
                     u8MaskData=0x80u;
                #endif
			/*uinit loops*/
			for(u8i=0u;u8i<8u;u8i++)
			{			
				/*set output bit ready*/
				if((OutData & u8MaskData) !=0U)
				{
					S_IIC_CH1_SetSDAHigh();
				}
				else
				{
					S_IIC_CH1_SetSDALow();
				}
				
			#if S_IIC_CH1_DataField == S_IIC_DataField_LSB
				u8MaskData<<=1u;
			#elif S_IIC_CH1_DataField ==S_IIC_DataField_MSB
				u8MaskData>>=1u;
			#endif
				/*wait value pin stable*/
				S_IIC_CH1_ClkDelay();
				
				/*rasing edge trigger to ouput SDA value*/
				S_IIC_CH1_SetSCLHigh();
				
				/*wait value pin stable*/
				S_IIC_CH1_ClkDelay();
				
				/*Set SCK to low for next bit output*/
				S_IIC_CH1_SetSCLLow();
				
				/*wait value pin stable*/
				S_IIC_CH1_ClkDelay();
			}
			
			/*small delay to wait Ack*/
			S_IIC_CH1_ClkDelay();
			/*rasing edge trigger to Get SDA ACK value*/
			S_IIC_CH1_SetSCLHigh();


			/*****by liulongxi 20190404******/
			S_IIC_CH1_WaitAck();
			/*****by liulongxi 20190404******/

			

            S_IIC_CH1_GetSDAValue(&u16GetValue);
			//if(S_IIC_CH1_GetSDAValue()!=0U)
			if(u16GetValue != 0)
			{
				u16RetVal=DET_Err_IICSlaveNotAck;
				DET_ErrReport(DET_Err_IICSlaveNotAck);
			}
			
			/*Set SCK to low for next bit output*/
			S_IIC_CH1_SetSCLLow();
			
			/*Set SDA to low for next bit output*/
			S_IIC_CH1_SetSDALow();
			S_IIC_CH1_SetSDAOutputMode();
		}	
		
		IIC_u8CH1_Satus =IIC_enReady;
	}

	if(DET_Err_IICSlaveNotAck==u16RetVal)
	{
		IIC_CH1_SlaveNotAckErrCB();
	}
	
	return u16RetVal;
	
}


/*****************************************************************************
 Function  : IIC_u16RecData_CH1												 
 Description   :receive data from slave node
 
 In Parameter: 
 			pRecDataHead : input data head
 			u16DataLen : data lenth(in byte)
 			
Return Value:
 			function execute resault
 			
 NOTE: 		
 			after execute this function, 
 				SDA=Low,output
 				SCK=Low
*****************************************************************************/
uint16 IIC_u16RecData_CH1(uint8 pRecDataHead[], uint16 u16DataLen)
{
	uint8 u8i,RecData,u8MaskData,u8totallIndex=0U;
    uint16 u16GetValue;
	
	uint16 u16RetVal=DET_Err_NotErr;
		
	/*check driver status*/
	if(IIC_u8CH1_Satus !=IIC_enReady)
	{
		DET_ErrReport(DET_Err_IICNotReady);
		u16RetVal =  DET_Err_IICNotReady;
	}
	else
	{
		IIC_u8CH1_Satus=IIC_enBusy; 	
		
		/*totall loops*/
		for(u8totallIndex=0U;u8totallIndex<u16DataLen;u8totallIndex++)
		{
			RecData=0U;
                     #if S_IIC_CH1_DataField == S_IIC_DataField_LSB
	              u8MaskData=1u;
                     #elif S_IIC_CH1_DataField ==S_IIC_DataField_MSB
	        	       u8MaskData=0x80u;
                    #endif
			/*set input mode for data in*/
			S_IIC_CH1_SetSDAInputMode();
			
			/*uinit loops*/
			for(u8i=0u;u8i<8u;u8i++)
			{			
				/*wait value pin stable*/
				S_IIC_CH1_ClkDelay();
				
				/*rasing edge trigger to get SDA value*/
				S_IIC_CH1_SetSCLHigh();
				
				/*wait value pin stable*/
				S_IIC_CH1_ClkDelay();
				
				/*get SDA bit data*/
                S_IIC_CH1_GetSDAValue(&u16GetValue);
    			//if(S_IIC_CH1_GetSDAValue()!=0U)
    			if(u16GetValue != 0)
				{
					RecData|=u8MaskData;
				}	
				
			#if S_IIC_CH1_DataField == S_IIC_DataField_LSB
				u8MaskData<<=1u;
			#elif S_IIC_CH1_DataField ==S_IIC_DataField_MSB
				u8MaskData>>=1u;
			#endif
				/*Set SCK to low for next bit output*/
				S_IIC_CH1_SetSCLLow();
				
			}
			
				/*small delay to send Ack*/
				S_IIC_CH1_ClkDelay();
				if(u8totallIndex<(uint8)(u16DataLen-1U))
				{
					/*Set SDA to low for next bit input*/
					S_IIC_CH1_SetSDALow();
				}
				else
				{
					/*Set SDA to high for Not Ack if it is last bit input*/
					S_IIC_CH1_SetSDAHigh();
				}
				S_IIC_CH1_SetSDAOutputMode();
				
					
				/*rasing edge trigger to send SDA ACK signal*/
				S_IIC_CH1_SetSCLHigh();
				
				/*update data to app layer*/
				pRecDataHead[u8totallIndex]=RecData;
				
				/*small delay to next byte*/
				S_IIC_CH1_ClkDelay();
				
				/*Set SCK to low for next bit input*/
				S_IIC_CH1_SetSCLLow();
			
		}	
		
		/*Set SDA to low for next bit input*/
		S_IIC_CH1_ClkDelay();
		S_IIC_CH1_SetSDALow();
		
		IIC_u8CH1_Satus =IIC_enReady;
		
	}
	
	return u16RetVal;
}


#endif


