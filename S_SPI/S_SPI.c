/*******************************************************************************
| Module Name: simulation IIC  model
| File Name: S_SPI.c
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
|2014/10/28 Rev 01.00.00     Tan Fumin			The first version  
|2016/01/26 Rev 02.00.00   Tan Fumin				update to be standard for SVN basic code
********************************************************************************/
#define S_SPI_DRV  

#include "./s_spi.h"


#if S_SPI_CHANNEL_NUMBER>=1u

#if S_SPI_CH1_DataBuffEnable !=0u
uint8 SPI_u8CH1_DataBuff[S_SPI_CH1_DataBuffSize]={0};/*store data to transfer, to avoid data changed during transfing*/
#endif

uint8 SPI_u8CH1_SpiSatus;

uint16 SPI_u16SlaveSelect_CH1(uint8 u8SlaveID,uint8 u8ChipSelect_OnOff);


/*****************************************************************************
 Function  : SPI_vDrvInit_CH1												 
 Description   :initialization the SPI I/O pin to be ready 
 
 In Parameter: 
 			NULL
 			
Return Value:
 			NULL
 			
 NOTE: 		
 			after execute this function, 
 				SI	=X,		Input
 				SO	=High,	output
 				SCK	=ReadyLevel,	output
*****************************************************************************/
void SPI_vDrvInit_CH1(void)
{
	S_SPI_CH1_SetReady();
}

/*****************************************************************************
 Function  : SPI_vDrvDeInit_CH1												 
 Description   :De-nitialization the SPI I/O pin to be ready 
 
 In Parameter: 
 			NULL
 			
Return Value:
 			NULL
 			
 NOTE: 		
 			after execute this function, 
 				SI	=X,		Input
 				SO	=High,	output
 				SCK	=ReadyLevel,	output
*****************************************************************************/
void SPI_vDrvDeInit_CH1(void)
{
	S_SPI_CH1_Exit();
}


/*****************************************************************************
 Function  : SPI_u16TransferData_CH1												 
 Description   :send data to SPI slave and receive data at the same time
 
 In Parameter: 
 			pOutDataHead: output data head, if receive data from slave, 
 						  filed the buffer to dummy level like 0xFF for High
 						  
 			pRecDataHead: receive data head,
 			
Return Value:
 			NULL
 			
 NOTE: 		
 			after execute this function, 
 				SI	=X,		Input
 				SO	=X,		output
 				SCK	=ReadyLevel,	output
*****************************************************************************/
uint16 SPI_u16TransferData_CH1(void *pOutDataHead, void *pRecDataHead,uint16 u16DataLen)
{
	uint16 u16totallIndex,u16Index;
	#if	S_SPI_CH1_DataUnit == 8u
	uint8 *pData,*pRecData,u8totallLoop,OutData,Mask,RecData;
	#elif S_SPI_CH1_DataUnit == 16u
	uint16 *pData,*pRecData,u8totallLoop,OutData,Mask,RecData;
	#elif S_SPI_CH1_DataUnit == 32u
	uint32 *pData,*pRecData,u8totallLoop,OutData,Mask,RecData;
	#endif
    uint16 u16Level = 0u;

	uint16 u16RetVal=DET_Err_NotErr;
	
	DET_ErrCheck(((pOutDataHead !=NULL) ||(pRecDataHead !=NULL)) , DET_Err_SerialParaInvalib);
	
	/*check driver status*/
	if(SPI_u8CH1_SpiSatus !=SPI_enReady)
	{
		DET_ErrReport(DET_Err_SPINotReady);
	}
	else
	{
			SPI_u8CH1_SpiSatus=SPI_enBusy;
			
			#if S_SPI_CH1_DataBuffEnable!=0u
				/*if send data lenth is too long, only send max bytes!*/
				if(u16DataLen>S_SPI_CH1_DataBuffSize)
				{
					DET_ErrReport(DET_Err_BufferOverLap);
					u16DataLen=S_SPI_CH1_DataBuffSize;
				}
			#endif
			
			#if S_SPI_CH1_DataUnit == 8u
			u8totallLoop=u16DataLen;
			#elif S_SPI_CH1_DataUnit == 16u
			u8totallLoop=(uint8)((u16DataLen+1)>>1u);
			#elif S_SPI_CH1_DataUnit == 32u
			u8totallLoop=(uint8)((u16DataLen+3)>>2u);
			#endif
					
			#if S_SPI_CH1_DataBuffEnable!=0u
				/*set data buffer ready*/
				if(pOutDataHead != NULL)
				{
					pRecData=pOutDataHead;
					pData=(void *)SPI_u8CH1_DataBuff;
					for(u16Index=0u;u16Index<u8totallLoop;u16Index++)
					{
						*pData++=*pRecData++;
					}					
					pData=(void *)SPI_u8CH1_DataBuff;
				}
				else
				{
					pData=NULL;
				}
				
				pRecData=pRecDataHead;
				
			#else
				pData = pOutDataHead;
				pRecData=pRecDataHead;
				
			#endif	
			
			
			/*totall loops*/
			for(u16totallIndex=0u;u16totallIndex<u8totallLoop;u16totallIndex++)
			{
				if(pData !=NULL)
				{
					OutData=*pData++;
				}
				else
				{
					OutData=S_SPI_CH1_SODummyOut;
				}
				
				RecData=0u;
				
				/*uinit loops*/
			#if S_SPI_CH1_DataField == S_SPI_DataField_LSB
				for(Mask=1ul;Mask!=0u;Mask<<=1u)
			#elif S_SPI_CH1_DataField ==S_SPI_DataField_MSB
				for(Mask=1ul<<(S_SPI_CH1_DataUnit-1u);Mask!=0u;Mask>>=1u)
			#endif
				{

		/*########################################################
				S_SPI_CH1_CLKReadyLevel ==0u
		##########################################################*/
		
				#if S_SPI_CH1_CLKReadyLevel ==0u
				
				/*####################
				*******Rasing edge********
				#####################*/		

					/*set ready data for output */
					#if S_SPI_CH1_DataOutEdge == S_SPI_RisingEdge
						/*set output bit ready*/
						if((OutData & Mask)!=0u)
						{
							S_SPI_CH1_SetSoHigh();
						}
						else
						{
							S_SPI_CH1_SetSoLow();
						}
					#endif
				
						/*Raising edge trigger */
						S_SPI_CH1_SetClkHigh();
						/*wait value pin stable*/
						S_SPI_CH1_ClkDelay();
							
					/*Read data in rasing edge */
					#if S_SPI_CH1_DataInEdge == S_SPI_RisingEdge
						/*get input value*/
                        S_SPI_CH1_GetSiValue(&u16Level);
						if(u16Level!=0u)
						{
							RecData |=Mask;
						}
					#endif
				
				/*####################
				*******Failing edge********
				#####################*/		

				/*set ready data for output */
				#if S_SPI_CH1_DataOutEdge != S_SPI_RisingEdge
					/*set output bit ready*/
					if((OutData & Mask)!=0u)
					{
						S_SPI_CH1_SetSoHigh();
					}
					else
					{
						S_SPI_CH1_SetSoLow();
					}
				#endif
									
					/*Failising edge trigger*/
					S_SPI_CH1_SetClkLow();
					/*wait value pin stable*/
					S_SPI_CH1_ClkDelay();
					
				#if S_SPI_CH1_DataInEdge != S_SPI_RisingEdge
					/*get input value*/
                    S_SPI_CH1_GetSiValue(&u16Level);
					if(u16Level!=0u)
					{
						RecData |=Mask;
					}
				#endif
				
		/*########################################################
				S_SPI_CH1_CLKReadyLevel !=0u
		##########################################################*/

			#elif S_SPI_CH1_CLKReadyLevel !=0u
				
				/*####################
				*******Failing edge********
				#####################*/		

					/*set ready data for output */
					#if S_SPI_CH1_DataOutEdge != S_SPI_RisingEdge
						/*set output bit ready*/
						if((OutData & Mask)!=0u)
						{
							S_SPI_CH1_SetSoHigh();
						}
						else
						{
							S_SPI_CH1_SetSoLow();
						}
					#endif
										
						/*Failising edge trigger*/
						S_SPI_CH1_SetClkLow();
						/*wait value pin stable*/
						S_SPI_CH1_ClkDelay();
					
					#if S_SPI_CH1_DataInEdge != S_SPI_RisingEdge
						/*get input value*/
                        S_SPI_CH1_GetSiValue(&u16Level);
						if(u16Level!=0u)
						{			
							RecData |=Mask;
						}
					#endif
				
				/*####################
				*******Rasing edge********
				#####################*/		

					/*set ready data for output */
					#if S_SPI_CH1_DataOutEdge == S_SPI_RisingEdge
						/*set output bit ready*/
						if((OutData & Mask)!=0u)
						{
							S_SPI_CH1_SetSoHigh();
						}
						else
						{
							S_SPI_CH1_SetSoLow();
						}
					#endif
					
						/*Raising edge trigger */
						S_SPI_CH1_SetClkHigh();
						/*wait value pin stable*/
						S_SPI_CH1_ClkDelay();
					
					/*Read data in rasing edge */
					#if S_SPI_CH1_DataInEdge == S_SPI_RisingEdge
						/*get input value*/
                        S_SPI_CH1_GetSiValue(&u16Level);
						if(u16Level!=0u)
						{
							RecData |=Mask;
						}
					#endif
				
				
				#endif/*end of S_SPI_CH1_CLKReadyLevel !=0u*/

			}
			
			if(pRecData !=NULL)
			{
				/*output the receive data to caller*/
				*pRecData++=RecData;
			}

		}	

		/*set driver to ready*/
		SPI_u8CH1_SpiSatus =SPI_enReady;
		
	}
	
	return u16RetVal;
	
}

#endif /*end of S_SPI_CHANNEL_NUMBER>=1u*/

#if S_SPI_CHANNEL_NUMBER>=2u

#if S_SPI_CH2_DataBuffEnable !=0u
uint8 SPI_u8CH2_DataBuff[S_SPI_CH2_DataBuffSize]={0};/*store data to transfer, to avoid data changed during transfing*/
#endif

uint8 SPI_u8CH2_SpiSatus;

uint16 SPI_u16SlaveSelect_CH2(uint8 u8SlaveID,uint8 u8ChipSelect_OnOff);


/*****************************************************************************
 Function  : SPI_vDrvInit_CH2												 
 Description   :initialization the SPI I/O pin to be ready 
 
 In Parameter: 
 			NULL
 			
Return Value:
 			NULL
 			
 NOTE: 		
 			after execute this function, 
 				SI	=X,		Input
 				SO	=High,	output
 				SCK	=ReadyLevel,	output
*****************************************************************************/
void SPI_vDrvInit_CH2(void)
{
	S_SPI_CH2_SetReady();
}

/*****************************************************************************
 Function  : SPI_vDrvDeInit_CH2												 
 Description   :De-nitialization the SPI I/O pin to be ready 
 
 In Parameter: 
 			NULL
 			
Return Value:
 			NULL
 			
 NOTE: 		
 			after execute this function, 
 				SI	=X,		Input
 				SO	=High,	output
 				SCK	=ReadyLevel,	output
*****************************************************************************/
void SPI_vDrvDeInit_CH2(void)
{
	S_SPI_CH2_Exit();
}

/*****************************************************************************
 Function  : SPI_u16TransferData_CH2												 
 Description   :send data to SPI slave and receive data at the same time
 
 In Parameter: 
 			pOutDataHead: output data head, if receive data from slave, 
 						  filed the buffer to dummy level like 0xFF for High
 						  
 			pRecDataHead: receive data head,
 			
Return Value:
 			NULL
 			
 NOTE: 		
 			after execute this function, 
 				SI	=X,		Input
 				SO	=X,		output
 				SCK	=ReadyLevel,	output
*****************************************************************************/
uint16 SPI_u16TransferData_CH2(void *pOutDataHead, void *pRecDataHead,uint16 u16DataLen)
{
	uint8 u8totallIndex;
	#if	S_SPI_CH2_DataUnit == 8u
	uint8 *pData,*pRecData,u8totallLoop,OutData,Mask,RecData;
	#elif S_SPI_CH2_DataUnit == 16u
	uint16 *pData,*pRecData,u8totallLoop,OutData,Mask,RecData;
	#endif
    uint16 u16Level = 0u;
    
	uint16 u16RetVal=DET_Err_NotErr;

	//S_SPI_CH2_SetSoOutPutMode();/*for test*/
	DET_ErrCheck(((pOutDataHead !=NULL) ||(pRecDataHead !=NULL)) , DET_Err_SerialParaInvalib);
	
	/*check driver status*/
	if(SPI_u8CH2_SpiSatus !=SPI_enReady)
	{
		DET_ErrReport(DET_Err_SPINotReady);
	}
	else
	{
			SPI_u8CH2_SpiSatus=SPI_enBusy;
			
			#if S_SPI_CH2_DataBuffEnable!=0u
				/*if send data lenth is too long, only send max bytes!*/
				if(u16DataLen>S_SPI_CH2_DataBuffSize)
				{
					DET_ErrReport(DET_Err_BufferOverLap);
					u16DataLen=S_SPI_CH2_DataBuffSize;
				}
			#endif
			
			#if S_SPI_CH2_DataUnit == 8u
			u8totallLoop=u16DataLen;
			#elif S_SPI_CH2_DataUnit == 16u
			u8totallLoop=(uint8)((u16DataLen+1)>>1u);
			#endif
					
			#if S_SPI_CH2_DataBuffEnable!=0u
				/*set data buffer ready*/
				if(pOutDataHead != NULL)
				{
					pRecData=pOutDataHead;
					pData=(void *)SPI_u8CH2_DataBuff;
					for(u8Index=0u;u8Index<u8totallLoop;u8Index++)
					{
						*pData++=*pRecData++;
					}					
					pData=(void *)SPI_u8CH2_DataBuff;
				}
				else
				{
					pData=NULL;
				}
				
				pRecData=pRecDataHead;
				
			#else
				pData = pOutDataHead;
				pRecData=pRecDataHead;
				
			#endif	
			
			
			/*totall loops*/
			for(u8totallIndex=0u;u8totallIndex<u8totallLoop;u8totallIndex++)
			{
				if(pData !=NULL)
				{
					OutData=*pData++;
				}
				else
				{
					OutData=S_SPI_CH2_SODummyOut;
				}
				
				RecData=0u;
				
				/*uinit loops*/
			#if S_SPI_CH2_DataField == S_SPI_DataField_LSB
				for(Mask=1u;Mask!=0u;Mask<<=1u)
			#elif S_SPI_CH2_DataField ==S_SPI_DataField_MSB
				for(Mask=1u<<(S_SPI_CH2_DataUnit-1u);Mask!=0u;Mask>>=1u)
			#endif
				{

		/*########################################################
				S_SPI_CH2_CLKReadyLevel ==0u
		##########################################################*/
		
				#if S_SPI_CH2_CLKReadyLevel ==0u
				
				/*####################
				*******Rasing edge********
				#####################*/		

					/*set ready data for output */
					#if S_SPI_CH2_DataOutEdge == S_SPI_RisingEdge
						/*set output bit ready*/
						if((OutData & Mask)!=0u)
						{
							S_SPI_CH2_SetSoHigh();
						}
						else
						{
							S_SPI_CH2_SetSoLow();
						}
					#endif
				
						/*Raising edge trigger */
						S_SPI_CH2_SetClkHigh();
						/*wait value pin stable*/
						S_SPI_CH2_ClkDelay();
							
					/*Read data in rasing edge */
					#if S_SPI_CH2_DataInEdge == S_SPI_RisingEdge
						/*get input value*/
						if(S_SPI_CH2_GetSiValue()!=0u)
						{
							RecData |=Mask;
						}
					#endif
				
				/*####################
				*******Failing edge********
				#####################*/		

				/*set ready data for output */
				#if S_SPI_CH2_DataOutEdge != S_SPI_RisingEdge
					/*set output bit ready*/
					if((OutData & Mask)!=0u)
					{
						S_SPI_CH2_SetSoHigh();
					}
					else
					{
						S_SPI_CH2_SetSoLow();
					}
				#endif
									
					/*Failising edge trigger*/
					S_SPI_CH2_SetClkLow();
					/*wait value pin stable*/
					S_SPI_CH2_ClkDelay();
					
				#if S_SPI_CH2_DataInEdge != S_SPI_RisingEdge
					/*get input value*/
                    S_SPI_CH2_GetSiValue(&u16Level);
					if(u16Level!=0u)
					{
						RecData |=Mask;
					}
				#endif
				
		/*########################################################
				S_SPI_CH2_CLKReadyLevel !=0u
		##########################################################*/

			#elif S_SPI_CH2_CLKReadyLevel !=0u
				
				/*####################
				*******Failing edge********
				#####################*/		

					/*set ready data for output */
					#if S_SPI_CH2_DataOutEdge != S_SPI_RisingEdge
						/*set output bit ready*/
						if((OutData & Mask)!=0u)
						{
							S_SPI_CH2_SetSoHigh();
						}
						else
						{
							S_SPI_CH2_SetSoLow();
						}
					#endif
										
						/*Failising edge trigger*/
						S_SPI_CH2_SetClkLow();
						/*wait value pin stable*/
						S_SPI_CH2_ClkDelay();
					
					#if S_SPI_CH2_DataInEdge != S_SPI_RisingEdge
						/*get input value*/
                        S_SPI_CH2_GetSiValue(&u16Level);
    					if(u16Level!=0u)
    					{
    						RecData |=Mask;
    					}
					#endif
				
				/*####################
				*******Rasing edge********
				#####################*/		

					/*set ready data for output */
					#if S_SPI_CH2_DataOutEdge == S_SPI_RisingEdge
						/*set output bit ready*/
						if((OutData & Mask)!=0u)
						{
							S_SPI_CH2_SetSoHigh();
						}
						else
						{
							S_SPI_CH2_SetSoLow();
						}
					#endif
					
						/*Raising edge trigger */
						S_SPI_CH2_SetClkHigh();
						/*wait value pin stable*/
						S_SPI_CH2_ClkDelay();
					
					/*Read data in rasing edge */
					#if S_SPI_CH2_DataInEdge == S_SPI_RisingEdge
						/*get input value*/
                        S_SPI_CH2_GetSiValue(&u16Level);
    					if(u16Level!=0u)
    					{
    						RecData |=Mask;
    					}
					#endif
				
				
				#endif/*end of S_SPI_CH2_CLKReadyLevel !=0u*/

			}
			
			if(pRecData !=NULL)
			{
				/*output the receive data to caller*/
				*pRecData++=RecData;
			}

		}	

		/*set driver to ready*/
		SPI_u8CH2_SpiSatus =SPI_enReady;
		
	}
	
	return u16RetVal;
	
}

#endif /*end of S_SPI_CHANNEL_NUMBER>=1u*/


