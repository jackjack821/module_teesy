
/*******************************************************************************
| Module Name: DTC process(prcess dianostic code) 
| File Name: DTC.c
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
| Sui Yanchun                 Desay SV Automotive Co., Ltd
| Lin Tao                     Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2014-11-24  1.00        Sui Yanchun       update the DTC module 
| 2015-12-16  2.00        Lin Tao           update for the MISRA C
| 2015-12-27  3.00        Lin Tao           Add the interface for the Diag service $19
********************************************************************************/

#define Dtc1c1                          /* Name of the Module                */


#include "Ccp.h"
#include "Ccp_cfg.h"
#include "CANApp.h"
//#include "BCTLDrv.h"
#include "Desc.h"
#include "Appdesc.h"

#include "General.h"
#include "LinApp.h" /*no RTE*/
#include "CANApp.h"
#include "CANNMApp.h"
#include "Rte.H"
#include "Rte_Internal.h"
/* Own headerfiles */
#include "DTC.h"
#include "DTC_Cfg.h"
#include "DTC_Type.h"
#include "DTC_Private.h"
#include "Ccp.h"
#include "Ccp_cfg.h"
#include "Dtc_interface.h"

static void DiagDTCSingleFailure(DTC_IDX_TYPE Idx, uint8 TestResult);
static void DiagDTCMultiFailure(DTC_IDX_TYPE Idx, uint8 TestResult);
static void DiagDTCRecordTestResult(DTC_IDX_TYPE Idx, uint8 TestResult);
static void DiagDeleteStoredDTC(DTC_IDX_TYPE Idx);
static void DiagUpdateStoredDTC(uint8 u8Pos,DTC_IDX_TYPE Idx);
static void DiagAssembleNewDTC(DTC_IDX_TYPE Idx);
 
static uint8 DTC_u8WriteAllDTCToEeprom(void);
static void DTC_vINCFault_Freq(DTC_IDX_TYPE Idx);
//static void DTC_vDECFault_Freq(DTC_IDX_TYPE Idx);
static void DTC_vINCFault_Count(DTC_IDX_TYPE Number);
static void DTC_vDECFault_Count(DTC_IDX_TYPE Number);
static void DTC_vSaveCurrentDtc(DTC_IDX_TYPE id);
static void DTC_vReadAllDTCFromEeprom(void);

static void DTC_vFailedAction(DTC_IDX_TYPE Idx);
static void DTC_vPassedAction(DTC_IDX_TYPE Idx);

static void DTC_vStoreNewDTC( uint8 u8Index,DTC_IDX_TYPE Idx);
static void DTC_vSortStore(DTC_IDX_TYPE Idx);
#if (DTC_SortType==DTC_SortPriority)
static void DTC_vActiveSort(uint8 u8LowestPrio);
static uint8 DTC_vPrioritySort(void);
#endif
static uint8 DTC_vCheckVehicleCfg(void);
void DTC_vGetErrorBit(uint8 u8Num,uint8 u8value);




static uint8 DTC_Logging_Status = False ;/* Control by Diagnosis command: program session and dtcsetting be unalbe this bit*/
static uint8 DTCFunctionEnabled = False;/* internal control , eg : power on off. acitive to standby be unable this bit*/
static uint8 DTC_biPowUnderVoltage = False;
static uint8 DTC_biPowOverVoltage = False;
static uint8 StoreDTCHaveChanged = False ;
static uint8 DTC_u8LoopCnt = 0;
static uint8 DTC_u8IgnStaticOn=False;/*160102*/
    
static uint16  DTC_u16IGTimer = 0U;
static uint16 DTC_u16PowFailureDisableTimer = 0U;

static uint16 DTC_u16ErrorCode;
static uint32 DTC_u32ArrageBuf[DTC_END/DTC_nSysType+1U]; /*The buffer for arrange the DTC error*/
static uint8 DTC_au8Array[DTC_nu8Max];
static uint16 DTC_au16Array[DTC_nu16Max];
static uint8 DTC_au8NetWorkNodeCfg[DTC_nu8VechileCfgMax];
/*UnScrReg u8DtcreArrange*/
static uint8 DTC_u8K15StsTmr=5;

DTC_DATA_TYPE DTC_DATA[DTC_END] ;
DTC_EEP_STORE STORE_DTC[DTC_MIN_NUMBER_TO_STORE];
const DTC_EEP_STORE DefaultEEPStoreData = {DTC_END, STATUS_BYTE , {0U,0U},{0U,0U,0U,0U},0U};


/***************************************************************************************************
* Function   : void Dtc_vMain(void)
* Description: dtc process
* Takes      : Nothing
* Returns    : Nothing
***************************************************************************************************/
void DTC_vMain10ms(void)
{
    uint8 u8DtcNumber = 0U;
	DTC_u8IgnStaticOn = IGN_u16GetValue(IGN_nu16IgnStaticOn);//(IGN_u16GetValue(IGN_nBitIgnState)>>2)&0x01;	/*add &0x01 by zsc,151219*/
    DTC_biPowOverVoltage = DTC_boGetPOWDiagHigh;
    DTC_biPowUnderVoltage = DTC_boGetPOWDiagLow;
     
    if(DTC_u16IGTimer<1000U)
    {
    	DTC_u16IGTimer++;  /*the time after IG ON*/
    }
		
	/*DTC resumed time from battery failure */
	if(DTC_u16PowFailureDisableTimer>0U)
	{
		DTC_u16PowFailureDisableTimer--;
	}

	if((DTC_biPowUnderVoltage)||(DTC_biPowOverVoltage))/*LT modify,20160721*/
	{
		DTC_u16PowFailureDisableTimer=DTC_nu16PowerFailDisTimer;
	}

		/*allowed to do DTC operations*/
	if ((DTC_Logging_Status == True) && (DTCFunctionEnabled == True)&&(DTC_u8IgnStaticOn == True))/*detect can error under IG is ON,160102*/
	{	 
		 for(u8DtcNumber=0;u8DtcNumber<DTC_END;u8DtcNumber++)
        {
            if(DTC_u16PowFailureDisableTimer == 0U)
            {
                if(DTC_stPropertyTable[u8DtcNumber].CallSequence== DTC_nCallForeGround)
                {
                    DTC_vGetErrorBit(u8DtcNumber,DTC_stPropertyTable[u8DtcNumber].fpDtcGetFailureStatus());
                }
            }
            else
            {
                DTC_vClearBusoffCnt();
                DTC_vClearCANMessCnt();
                if(DTC_stPropertyTable[u8DtcNumber].CallSequence == DTC_nCallForeGround)
                {
                    DTC_vGetErrorBit(u8DtcNumber,0);
                }				
            }		

            if(DTC_stPropertyTable[u8DtcNumber].CallSequence == DTC_nCallPowFailureDtc)
            {
                if(DTC_u16IGTimer >=DTC_nu16IGDelayForPOW)
                {
                    DTC_vGetErrorBit(u8DtcNumber,DTC_stPropertyTable[u8DtcNumber].fpDtcGetFailureStatus());
                }
                else
                {
                    DTC_vGetErrorBit(u8DtcNumber,0);
                }
            }
        }        
	}
	else
	{
	    memset(&DTC_u32ArrageBuf[0],0,sizeof(DTC_u32ArrageBuf));
	}  
	/****************************** process full error ******************************************/

	/*allowed to do DTC operations*/
	if ((DTC_Logging_Status == True) && (DTCFunctionEnabled == True))
     //   &&(DTC_u16IGTimer>=DTC_nu16IGDelayTimer)) 
	{	
    	/* only process ATC related dtc and can communication dtc*/      		
    	for(u8DtcNumber=0U;u8DtcNumber<DTC_END;u8DtcNumber++)
    	{	
    		if((DTC_stPropertyTable[u8DtcNumber].CallSequence == DTC_nCallForeGround)||\
    			(DTC_stPropertyTable[u8DtcNumber].CallSequence == DTC_nCallPowFailureDtc))
    		{            	    
    			if(((DTC_u32ArrageBuf[u8DtcNumber/DTC_nSysType]>>(u8DtcNumber%DTC_nSysType))&0x01U)!=0U)
    			{
    				DiagDTCRecordTestResult(u8DtcNumber,DTC_TEST_FAILED);
    			}
    			else
    			{
    				DiagDTCRecordTestResult(u8DtcNumber,DTC_TEST_PASSED);
    			}
    		}
    	}   
    }
    else
    {
        /*do nothing*/
    }
    DTC_vCheckVehicleCfg(); 
    if(DTC_u8K15StsImport()==True)
    {   	
    DTC_u8K15StsTmr=5;
    }
    else
    {
        if(DTC_u8K15StsTmr>0)
        {
            DTC_u8K15StsTmr--;
        }
    }
    if(DTC_u8K15StsTmr==0)
    {
        for(u8DtcNumber=0U;u8DtcNumber<DTC_END;u8DtcNumber++)
        {
            DTCStatusClrBit(u8DtcNumber,0); 
        }
    }
}

/***************************************************************************************************
* Function   : void Dtc_vMain1(void)
* Description: dtc process
* Takes      : Nothing
* Returns    : Nothing
***************************************************************************************************/
 void DTC_vMain1(void)
{	
	uint8 u8DtcNumber;
	/*allowed to do DTC operations*/
	if ((DTC_Logging_Status == True) && (DTCFunctionEnabled == True)&&\
		(DTC_u16IGTimer >=DTC_nu16IGDelayTimer )&&(DTC_u8IgnStaticOn == True)) 
	{
		for(u8DtcNumber=0;u8DtcNumber<DTC_END;u8DtcNumber++)
		{
			if(DTC_u16PowFailureDisableTimer == 0U)
			{
				if((DTC_stPropertyTable[u8DtcNumber].CallSequence != DTC_nCallForeGround)&&\
					(DTC_stPropertyTable[u8DtcNumber].CallSequence != DTC_nCallPowFailureDtc))
				{
					DTC_vGetErrorBit(u8DtcNumber,DTC_stPropertyTable[u8DtcNumber].fpDtcGetFailureStatus());
				}
			}
			else
			{
				if((DTC_stPropertyTable[u8DtcNumber].CallSequence != DTC_nCallForeGround)&&\
					(DTC_stPropertyTable[u8DtcNumber].CallSequence != DTC_nCallPowFailureDtc))
				{
					DTC_vGetErrorBit(u8DtcNumber,0);
				}
			}
		}
	}
	else
	{
		for(u8DtcNumber=0;u8DtcNumber<DTC_END;u8DtcNumber++)
		{
			if((DTC_stPropertyTable[u8DtcNumber].CallSequence != DTC_nCallForeGround)&&\
				(DTC_stPropertyTable[u8DtcNumber].CallSequence != DTC_nCallPowFailureDtc))
			{
				DTC_vGetErrorBit(u8DtcNumber,0);
			}
		}
	}
	
     DTC_au8Array[DTC_nu8Valid]=True;
		
}


/***************************************************************************************************
* Function   : void Dtc_vMain2 (void)
* Description: dtc process
* Takes      : Nothing
* Returns    : Nothing
***************************************************************************************************/
 void DTC_vMain2 (void)
{	
	uint8 u8DtcNumber = 0U;

	/****************************** process full error ******************************************/

	/*allowed to do DTC operations*/
	if ((DTC_Logging_Status == True) && (DTCFunctionEnabled == True)
        &&(DTC_u16IGTimer>=DTC_nu16IGDelayTimer)&&(DTC_u8IgnStaticOn == True)) 
	{	

    	/* only process ATC related dtc and can communication dtc*/      		
    	for(u8DtcNumber=0;u8DtcNumber<DTC_END;u8DtcNumber++)
    	{	
            if(DTC_stPropertyTable[u8DtcNumber].CallSequence == DTC_nCallBackGround1)
            {
        		if(((DTC_u32ArrageBuf[u8DtcNumber/DTC_nSysType]>>(u8DtcNumber%DTC_nSysType))&0x01U)!=0U)
        		{
        			DiagDTCRecordTestResult(u8DtcNumber,DTC_TEST_FAILED);
        		}
        		else
        		{
        			DiagDTCRecordTestResult(u8DtcNumber,DTC_TEST_PASSED);
        		}
            }
    	} 
              
   }
   else
   {
        /*do nothing*/
   }

	
	

}


/***************************************************************************************************
* Function   : void Dtc_vMainbank (void)
* Description: dtc process
* Takes      : Nothing
* Returns    : Nothing
***************************************************************************************************/
void DTC_vMain3(void)
{	
	uint8 u8DtcNumber = 0U;

	/****************************** process full error ******************************************/
	/*allowed to do DTC operations*/
	if ((DTC_Logging_Status == True) && (DTCFunctionEnabled == True)
    &&(DTC_u16IGTimer>=DTC_nu16IGDelayTimer)&&(DTC_u8IgnStaticOn == True)) 
	{
    	/*only process ad port and not busoff and lost bcm*/
    	for(u8DtcNumber=0;u8DtcNumber<DTC_END;u8DtcNumber++)
    	{	
            if(DTC_stPropertyTable[u8DtcNumber].CallSequence == DTC_nCallBackGround2)
            {
        		if(((DTC_u32ArrageBuf[u8DtcNumber/DTC_nSysType]>>(u8DtcNumber%DTC_nSysType))&0x01U) != 0U)
        		{
        			DiagDTCRecordTestResult(u8DtcNumber,DTC_TEST_FAILED);
        		}
        		else
        		{
        			DiagDTCRecordTestResult(u8DtcNumber,DTC_TEST_PASSED);
        		}
            }
    	}
 
   }
   else
   {
        /*do nothing*/
   }

		
}

/*****************************************************************************************************************
* FUNCTION      : DiagDTCRecordTestResult
* DESCRIPTION   : Called by outsiders to log DTC.
					
* PARAMETERS    : unsigned char CurrentIdx
* RETURN        : void
*****************************************************************************************************************/
static  void DiagDTCRecordTestResult(DTC_IDX_TYPE Idx, uint8 TestResult)
{
	if ((DTC_Logging_Status == True) && (DTCFunctionEnabled == True))	/*allowed to do DTC operations*/
	{
		if((DTC_stPropertyTable[Idx].Fault_THRPass == (DEFAULT_THR_Init+SIGNAL_FAULT_THR))&&\
            (DTC_stPropertyTable[Idx].Fault_THRFail == (DEFAULT_THR_Init+SIGNAL_FAULT_THR)))
		{
			DiagDTCSingleFailure(Idx , TestResult );
		}
		else
		{
			DiagDTCMultiFailure(Idx , TestResult );
		}
	}
}




/*****************************************************************************************************************
* FUNCTION      : DTC_vFailedAction
* DESCRIPTION   : Called when the error have failed, means that the Fault Counter> Fail Threshold
					
* PARAMETERS    : unsigned char CurrentIdx
* RETURN        : void
*****************************************************************************************************************/
static void DTC_vFailedAction(DTC_IDX_TYPE Idx)
{
    uint8 u8Battery = 0U,u8CoolantTemp;
    uint16 u16VelSpeed = 0U;
    uint32 u32Odometer=0U;
    
    u8Battery = DTC_u16GetBatteryVol;
    u16VelSpeed = DTC_u16GetCANAppVelSpeed;
    u32Odometer = DTC_u32GetCANAppOdometer;
    u8CoolantTemp = DTC_u8GetCANCoolantTemp;
    
     /*Now can confirm the DTC, and save the snapshot*/
	if(DTCStatusCheckBitClr(Idx,3))
	{

		/*u16Battery from Rte_IRead_Dtc_vMain_DtcGetPowBattVoltage_BattVolt()*//*external interface*/
        /*u16VelSpeed from Rte_IRead_Dtc_vMain_DtcGetVelocityValue_Velocity()*//*external interface*/		
        /*Here save the snapshot*/
		DTC_DATA[Idx].Snapshot_Data.VelSpeed =u16VelSpeed;
		DTC_DATA[Idx].Snapshot_Data.SysBattery = u8Battery; 
        DTC_DATA[Idx].Snapshot_Data.CoolantTemp = u8CoolantTemp; 
        DTC_DATA[Idx].Snapshot_Data.u32FirstOdometer = u32Odometer; 
	}
       
    if(DTCStatusCheckBitClr(Idx,1))
	{
        DTC_vINCFault_Freq(Idx);
        
        DTC_DATA[Idx].Snapshot_Data.u32LastOdometer = u32Odometer; 

	    if(DTC_DATA[Idx].Extended_Data.MonitorCycleCnt < 255U) 
        {
            DTC_DATA[Idx].Extended_Data.MonitorCycleCnt++;
        }
	}
    /*Set bit0: testFailed*/
    DTCStatusSetBit(Idx, 0);
	/*Set bit1:  test failure this operation cycle*/
	DTCStatusSetBit(Idx, 1);
	/*Set bit2: pendingDTC*/
	DTCStatusSetBit(Idx, 2);
	/*Set bit3:confirmDTC*/
	DTCStatusSetBit(Idx, 3);
	/*Set bit5: testFaildSinceLastClear*/
	DTCStatusSetBit(Idx, 5);   
	/*Clr bit4: testNotCompletedSinceLastClear*/
	DTCStatusClrBit(Idx, 4); 
       /*Clr bit6: testNotCompletedThisOperationCycle*/
	DTCStatusClrBit(Idx, 6);           
	/*clear the self heal counter*/
	DTC_DATA[Idx].Extended_Data.AgeingCnt = 0U;	
    /*no sure about this value,20150819,LT*/
	DTC_DATA[Idx].DTC_Aged = 1U;
    
    DTC_vSaveCurrentDtc(Idx);
}

/*****************************************************************************************************************
* FUNCTION      : DTC_vPassedAction
* DESCRIPTION   : Called when the error have Passed, means that the Fault Counter< PassThreshold
				
* PARAMETERS    : unsigned char CurrentIdx
* RETURN        : void
*****************************************************************************************************************/
static void DTC_vPassedAction(DTC_IDX_TYPE Idx)
{
    /*Clr bit6: testNotCompletedThisOperationCycle*/
    DTCStatusClrBit(Idx,6);
    /*Clr bit4: testNotCompletedSinceLastClear*/
    DTCStatusClrBit(Idx,4);   
    /*bit0 test failure, not necessary*/
    DTCStatusClrBit(Idx, 0);
}




/*****************************************************************************************************************
 * FunctionName:	DiagDTCSinalFailure
 * Description:	Record the signal Failure DTC , there is not Pending DTC state.
 				If fault one time , It will go to Fault Detected state
					
* PARAMETERS    : unsigned char Idx
* RETURN        : void
*****************************************************************************************************************/

static  void DiagDTCSingleFailure(DTC_IDX_TYPE Idx, uint8 TestResult)
{

	if (TestResult == DTC_TEST_FAILED)	/*test failed for this round*/
	{	
             /* Clear the bit7*/
        	DTC_DATA[Idx].Status_Byte &=MaskState;
        	DTC_vINCFault_Count(Idx);
            DTC_vFailedAction(Idx);
	}
	else /* (TestResult == DTC_TEST_PASSED)*/
	{
        	/* Clear the bit7*/
        	DTC_DATA[Idx].Status_Byte &=MaskState;
        	DTC_vDECFault_Count(Idx);
		    DTC_vPassedAction(Idx);
	}
		
}

/*****************************************************************************************************************
* FunctionName:	DiagDTCMultiFailure
* Description:	Record the multi- Failure DTC , there is Pending DTC state.
 				If fault one time , It will go to Pending DTC  state
					
* PARAMETERS    : unsigned char Idx
* RETURN        : void
*****************************************************************************************************************/

static  void DiagDTCMultiFailure(DTC_IDX_TYPE Idx, uint8 TestResult)
{

    
	if (TestResult == DTC_TEST_FAILED)	/*test failed for this round*/
	{
		 /* Clear the bit7*/
		DTC_DATA[Idx].Status_Byte &=MaskState;
		
	    DTC_vINCFault_Count(Idx);
	    	
		if(DTC_DATA[Idx].Extended_Data.Fault_Count >= DTC_stPropertyTable[Idx].Fault_THRFail)
		{	
            DTC_vFailedAction(Idx);
		}
		else
		{	
			 /*Do nothing*/
		}	
			
	}
	else /*(TestResult == DTC_TEST_PASSED)*/
	{
		 /* Clear the bit7*/
		DTC_DATA[Idx].Status_Byte &=MaskState;

		DTC_vDECFault_Count(Idx);
	
        if(DTC_DATA[Idx].Extended_Data.Fault_Count <= DTC_stPropertyTable[Idx].Fault_THRPass)
        {
                DTC_vPassedAction(Idx);			
        }
        else
        {
            /*Do nothing*/
        }
		
	}

		
}

/***************************************************************************************************
* FUNCTION      : DTC_vINCFault_Freq
* DESCRIPTION   : increase the frequency of the DTC
				
* PARAMETERS    : the index of the DTC
* RETURN        : void
***************************************************************************************************/
static void DTC_vINCFault_Freq(DTC_IDX_TYPE Idx)
{
    /*increase the Fault Frequrece , if it is 0xFF , just hold 0xFF*/
	if(DTC_DATA[Idx].Extended_Data.Fault_Frequency < 0xFFU)
	{
        DTC_DATA[(Idx)].Extended_Data.Fault_Frequency ++;  
	}
}

#if 0
/***************************************************************************************************
* FUNCTION      : DTC_vDECFault_Freq
* DESCRIPTION   : decrease the frequency of the DTC
				
* PARAMETERS    : the index of the DTC
* RETURN        : void
***************************************************************************************************/
static void DTC_vDECFault_Freq(DTC_IDX_TYPE Idx)
{
    /*Decrease the Fault Frequrece , if it is 0x00 , just hold 0x00*/  
    if(DTC_DATA[(Idx)].Extended_Data.Fault_Frequency > 0x00U)
    {
        DTC_DATA[(Idx)].Extended_Data.Fault_Frequency --;
    }
}
#endif
/***************************************************************************************************
* FUNCTION      : Dtc_vINCFault_Count
* DESCRIPTION   : increase the fault counter of the DTC when detect error
				
* PARAMETERS    : the index of the DTC
* RETURN        :
***************************************************************************************************/
static  void DTC_vINCFault_Count(DTC_IDX_TYPE Number)
{
    uint16 u16FaultCnt = 0U;
	if(DTCStatusCheckBitSet(Number,6))/*to make sure the time of test completed this operation cycle = Fault_Count*/
	{
        
	}

    /*when detect the error,the fault count should be bigger than init state fault*/
    if(DTC_DATA[Number].Extended_Data.Fault_Count< DEFAULT_THR_Init)
    {
        DTC_DATA[Number].Extended_Data.Fault_Count = DEFAULT_THR_Init;
    }
    
    u16FaultCnt = (uint16)DTC_DATA[Number].Extended_Data.Fault_Count+(uint16)DTC_stPropertyTable[Number].Fault_INC;
        
	if(u16FaultCnt > DTC_stPropertyTable[Number].Fault_THRFail)
	{
		DTC_DATA[Number].Extended_Data.Fault_Count = DTC_stPropertyTable[Number].Fault_THRFail;
	}
	else
	{
	    DTC_DATA[Number].Extended_Data.Fault_Count = (uint8)u16FaultCnt;
	}

    
}

/***************************************************************************************************
* FUNCTION      : Dtc_vINCFault_Count
* DESCRIPTION   : decrease the fault counter of the DTC when detect no error
				
* PARAMETERS    : the index of the DTC
* RETURN        :
***************************************************************************************************/
static  void DTC_vDECFault_Count(DTC_IDX_TYPE Number)
{
	if((DTCStatusCheckBitSet(Number,6))||(DTCStatusCheckBitSet(Number,4)))
		/*to make sure the time of test completed this operation cycle = Fault_Count*/
	{
        #if 0
		if(DTC_200MsFlag==True)
		{
			return;
		}
        #endif
	}
    
	if(DTC_DATA[Number].Extended_Data.Fault_Count>= DTC_stPropertyTable[Number].Fault_DEC)
	{		
		DTC_DATA[Number].Extended_Data.Fault_Count -= DTC_stPropertyTable[Number].Fault_DEC;
	}
    else
    {
        DTC_DATA[Number].Extended_Data.Fault_Count = 0;
    }

    if(DTC_DATA[Number].Extended_Data.Fault_Count< DTC_stPropertyTable[Number].Fault_THRPass)
	{
		DTC_DATA[Number].Extended_Data.Fault_Count = DTC_stPropertyTable[Number].Fault_THRPass;
	}
}


/*****************************************************************************************************************
 * FunctionName:	DiagDeleteStoredDTC
 * Description:	Update DetectedDTCFull[] store new extended data of current logging DTC
				to memory which will written to EEPROM to perserve current DTC info.
 * Input:	   		DTC_IDX_TYPE Idx		
 * Return:		None
*****************************************************************************************************************/

static  void DiagDeleteStoredDTC(DTC_IDX_TYPE Idx)
{
	uint8 i=0U;
	uint8 j=0U;

	/*check if CurrentIdx is stored fully:*/
	for (i = 0U; i < DTC_MIN_NUMBER_TO_STORE; i ++)
	{
		if (STORE_DTC[i].DTCIndex == Idx)	/*found!*/
		{	
			for(j=i;j<DTC_MIN_NUMBER_TO_STORE-1U;j++)
			{
				memcpy(&STORE_DTC[j], &STORE_DTC[j + 1U], sizeof(DTC_EEP_STORE) );
			}

			memcpy(&STORE_DTC[DTC_MIN_NUMBER_TO_STORE-1U], &DefaultEEPStoreData, sizeof(DTC_EEP_STORE) );			
			StoreDTCHaveChanged = True;
		}
	}
}

/*****************************************************************************************************************
 * FunctionName:	DiagUpdateStoredDTC
 * Description:	Update DetectedDTCFull[] store new extended data of current logging DTC
					to memory which will written to EEPROM to perserve current DTC info.
 * Input:	   		DTC_IDX_TYPE Idx		
 * Return:		None
*****************************************************************************************************************/

static void DiagUpdateStoredDTC(uint8 u8Pos,DTC_IDX_TYPE Idx)
{

	if (STORE_DTC[u8Pos].DTCIndex == Idx)	/*found*/
	{			
		STORE_DTC[u8Pos].Status_Byte = DTC_DATA[Idx].Status_Byte;
		STORE_DTC[u8Pos].Extended_Data = DTC_DATA[Idx].Extended_Data;
		STORE_DTC[u8Pos].Aged_Check = DTC_DATA[Idx].DTC_Aged;
		
        if(DTC_DATA[Idx].Status_Byte==0x00U)
        {
            STORE_DTC[u8Pos].DTCIndex =DTC_END;
        }				
		StoreDTCHaveChanged = True;
	}

}



#if (DTC_SortType==DTC_SortPriority)
/*****************************************************************************************************************
**FUNCTION      :  static  void DTC_vPrioritySort(void)
**  DESCRIPTION   :  	to memory which will written to EEPROM to perserve current DTC info.					
**  PARAMETERS    :
**  RETURN        : void
*****************************************************************************************************************/

 static  uint8  DTC_vPrioritySort(void)
{
    uint8 i=0U,j=0U,DTC_isChanged=0U;
    uint8 u8PriorityA = 1U,u8PriorityB = 1U,u8PrioLowLevel = 1U;

    DTC_EEP_STORE       AssembleDTCStore;

       /*Bubble sort, from small to big,find the Priority*/
	for(j=DTC_MIN_NUMBER_TO_STORE-1U;j>0U;j--)
	{
		DTC_isChanged=False;
		for(i=0U;i<j;i++)
		{
            u8PriorityA= DTC_stPropertyTable[STORE_DTC[i+1U].DTCIndex].DTC_Priority;
            u8PriorityB = DTC_stPropertyTable[STORE_DTC[i].DTCIndex].DTC_Priority;

            if(u8PriorityA<u8PriorityB)
            {
                /*Exchange the  result, A<--->B*/
                AssembleDTCStore=STORE_DTC[i+1U];
                STORE_DTC[i+1U]=STORE_DTC[i];
                STORE_DTC[i]=AssembleDTCStore;
                DTC_isChanged=True;
            }
		}
		/*if no order changed, sort finish*/
		if(DTC_isChanged==False)
		{
			break;
		}
	}
    u8PrioLowLevel =  DTC_stPropertyTable[STORE_DTC[DTC_MIN_NUMBER_TO_STORE-1U].DTCIndex].DTC_Priority;

    return u8PrioLowLevel;
}
#endif 
/***************************************************************************************************
**FUNCTION      :  static  void DTC_vCheckVehicleCfg(void)
**  DESCRIPTION   : check the vehicle confi 					
**  PARAMETERS    :
**  RETURN        : void
***************************************************************************************************/
static uint8 DTC_vCheckVehicleCfg(void)
{
    uint8 u8CanNetworkCfg[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    
    
    DTC_ReadCanNetworkCfg(&u8CanNetworkCfg[0]);

	DTC_au8NetWorkNodeCfg[DTC_nu8EMSNodeCfg] = True;
	DTC_au8NetWorkNodeCfg[DTC_nu8IPKNodeCfg] = True;
	DTC_au8NetWorkNodeCfg[DTC_nu8BCMNodeCfg] = True;
	DTC_au8NetWorkNodeCfg[DTC_nu8ESCNodeCfg] = True;
	DTC_au8NetWorkNodeCfg[DTC_nu8PEPSNodeCfg] = True;
	//DTC_au8NetWorkNodeCfg[DTC_nu8MMINodeCfg] = True;
	if((u8CanNetworkCfg[1]&0x08)==0x08)/*Byte1, bit 3*/
    {
        DTC_au8NetWorkNodeCfg[DTC_nu8MMINodeCfg] = True;
    }
    else
    {
        DTC_au8NetWorkNodeCfg[DTC_nu8MMINodeCfg] = False;
    }
	DTC_au8NetWorkNodeCfg[DTC_nu8IPUNodeCfg] = True;
	DTC_au8NetWorkNodeCfg[DTC_nu8BMSHNodeCfg] = True;
	DTC_au8NetWorkNodeCfg[DTC_nu8VCUNodeCfg] = True;
	DTC_au8NetWorkNodeCfg[DTC_nu8OBCNodeCfg] = True;
        
    //DTC_au8NetWorkNodeCfg[DTC_nu8TBOXNodeCfg] = True;  /*Standard ECU for the HB*/

    if((u8CanNetworkCfg[1]&0x40)==0x40)/*Byte1, bit 6*/
    {
        DTC_au8NetWorkNodeCfg[DTC_nu8TBOXNodeCfg] = True;
    }
    else
    {
        DTC_au8NetWorkNodeCfg[DTC_nu8TBOXNodeCfg] = False;
    }         
    
    DTC_au8NetWorkNodeCfg[DTC_nu8PM25NodeCfg] = DTC_u8GetPM25MountCfg;
    DTC_au8NetWorkNodeCfg[DTC_nu8IONNodeCfg] = DTC_u8GetIONMountCfg;
    DTC_au8NetWorkNodeCfg[DTC_nu8RCPNodeCfg] = DTC_u8GetRCPMountCfg;
    DTC_au8NetWorkNodeCfg[DTC_nu8AQSSensorCfg] = DTC_u8GetAQSMountCfg;
   
    return 0;/*Release Warning,161024*/  
    
}

#if (DTC_SortType==DTC_SortPriority)
/***************************************************************************************************
**FUNCTION      :  static  void DTC_vActiveSort(void)
**  DESCRIPTION   :  	sort the active state  only  for the lowest Priority of the current dtc, 					
**  PARAMETERS    :
**  RETURN        : void
***************************************************************************************************/
static void DTC_vActiveSort(uint8 u8LowestPrio)
{
    uint8 u8Idx,u8i,u8j,u8DTCAState,u8DTCBState,u8Pos;
    DTC_EEP_STORE AssembleDTCStore;

       /*find the start position which is the begain of the lowest priority*/
       for(u8j = 0U; u8j <DTC_MIN_NUMBER_TO_STORE;u8j++ )
       {
           u8Idx = STORE_DTC[u8j].DTCIndex;
           
           if(DTC_stPropertyTable[u8Idx].DTC_Priority==u8LowestPrio)
           {
                  u8Pos = u8j;
                  break;
           }
           else
           {
                /*do nothing*/
              
           }
       }
       
        for(u8j=(DTC_MIN_NUMBER_TO_STORE-1U);u8j>u8Pos;u8j--)
        {
            for(u8i=u8Pos;u8i<u8j;u8i++)
            {
                u8Idx=STORE_DTC[u8i].DTCIndex;
                if((DTCStatusCheckBitClr(u8Idx,6))&&(DTCStatusCheckBitClr(u8Idx,0)))
                {
                    u8DTCAState = False; /*Not Active state*/
                }
                else
                {
                    u8DTCAState = True; /*Active state*/
                }   

                u8Idx=STORE_DTC[u8i+1U].DTCIndex;           
                if((DTCStatusCheckBitClr(u8Idx,6))&&(DTCStatusCheckBitClr(u8Idx,0)))
                {
                    u8DTCBState = False; /*Not Active state*/
                }
                else
                {
                    u8DTCBState = True; /*Active state*/
                }   

                if((u8DTCAState==False)&&(u8DTCBState==True))
                {
                    /*Exchange the position, move the not active dtc back*/
                    AssembleDTCStore=STORE_DTC[u8i+1U];
                    STORE_DTC[u8i+1U]=STORE_DTC[u8i];
                    STORE_DTC[u8i]=AssembleDTCStore;                   
                }
            }
        }

#if 0    
   static DTC_EEP_STORE DTCSort[DTC_MIN_NUMBER_TO_STORE];
    
   /*find the start position which is the begain of the lowest priority*/
   for(u8j = 0; u8j <DTC_MIN_NUMBER_TO_STORE;u8j++ )
   {
       u8Idx = STORE_DTC[u8j].DTCIndex;
       
       if(DTC_Code_Table[u8Idx].Priority==u8LowestPrio)
       {
              u8Pos = u8j;
              u8LowPrioPos = u8Pos;
              break;
       }
       else
       {
            /*do nothing*/
          
       }
   }

   /*sort the actived dtc,u8Pos is the start position*/        
    for(u8j=u8Pos;u8j<DTC_MIN_NUMBER_TO_STORE;u8j++)
    {    

         u8Idx = STORE_DTC[u8j].DTCIndex;        
         /*check if the DTC is active,if it's active,copy to the DTCSort buffer*/
         if((DTC_DATA[u8Idx].Status_Byte&0x80) == 0x80)
         {
                DTCSort[u8Pos]=STORE_DTC[u8j];
                u8Pos++;
         }
    }

    /*sort the not actived dtc,u8Pos is the start position*/        
    for(u8j=u8Pos;u8j<DTC_MIN_NUMBER_TO_STORE;u8j++)
    {    
         u8Idx = STORE_DTC[u8j].DTCIndex;        
         /*check if the DTC is noactive,if it's not active,copy to the DTCSort buffer*/
         if((DTC_DATA[u8Idx].Status_Byte&0x80) != 0x80)
         {
                DTCSort[u8Pos]=STORE_DTC[u8j];
                u8Pos++;
         }
    }

    /*Copy the sort result to the Store DTC*/
    for(u8j=u8LowPrioPos;u8j<DTC_MIN_NUMBER_TO_STORE;u8j++)
    {
        STORE_DTC[u8j] = DTCSort[u8j];
    }
#endif 

}

#endif
/***************************************************************************************************
**  FUNCTION      : void DTC_vStoreNewDTC(void)
**  DESCRIPTION   : 				
**  PARAMETERS    :
**  RETURN        : void
***************************************************************************************************/
static void DTC_vStoreNewDTC( uint8 u8Index,DTC_IDX_TYPE Idx)
{    
	if((STORE_DTC[u8Index].DTCIndex!=Idx)||\
		(STORE_DTC[u8Index].Aged_Check!=DTC_DATA[Idx].DTC_Aged)||\
		(STORE_DTC[u8Index].Status_Byte != DTC_DATA[Idx].Status_Byte))
	{
		StoreDTCHaveChanged = True;
	}
        STORE_DTC[u8Index].DTCIndex = Idx;	
        STORE_DTC[u8Index].Aged_Check=DTC_DATA[Idx].DTC_Aged;
        STORE_DTC[u8Index].Status_Byte = DTC_DATA[Idx].Status_Byte;
        STORE_DTC[u8Index].Snapshot_Data = DTC_DATA[Idx].Snapshot_Data;
        STORE_DTC[u8Index].Extended_Data=DTC_DATA[Idx].Extended_Data;        
}
/*****************************************************************************************************************
** FUNCTION      : DTC_vSortStore
** DESCRIPTION   :  Store the DTC accroding to the sort result
				
** PARAMETERS    : DTC_IDX_TYPE Idx
** RETURN        : void
*****************************************************************************************************************/
static void DTC_vSortStore(DTC_IDX_TYPE Idx)
{
       
#if (DTC_SortType==DTC_SortFIFO)
    uint8   temp = 0U;
    for(temp = 0U; temp <(DTC_MIN_NUMBER_TO_STORE - 1U);temp++)
    {
        memcpy(&STORE_DTC[temp], &STORE_DTC[temp + 1U], sizeof(DTC_EEP_STORE));
    }
    DTC_vStoreNewDTC(DTC_MIN_NUMBER_TO_STORE - 1U,Idx);
#else
    uint8   PrioLastLevel = 1U,NewDTCPrio = 1U,u8IdxID = 0U; 
    /*sort accroding to the Priority*/
    PrioLastLevel = DTC_vPrioritySort();	
    
    NewDTCPrio = DTC_stPropertyTable[Idx].DTC_Priority;
    
    if(NewDTCPrio<PrioLastLevel) /*need to save*/
    {
            /*need to save,just sort the for  lowest level dtc*/
            DTC_vActiveSort(PrioLastLevel);
            /*then store the current DTC to last slot:   */
            DTC_vStoreNewDTC(DTC_MIN_NUMBER_TO_STORE - 1U,Idx);
            
    }
    else if(NewDTCPrio==PrioLastLevel)
    {
            DTC_vActiveSort(PrioLastLevel);
           
            u8IdxID = STORE_DTC[DTC_MIN_NUMBER_TO_STORE-1U].DTCIndex;
             /*check if there is any dtc is not active*/
            if((DTCStatusCheckBitClr(u8IdxID,6))&&(DTCStatusCheckBitClr(u8IdxID,0)))
            {
                /*then store the current DTC to last slot:   */
                DTC_vStoreNewDTC(DTC_MIN_NUMBER_TO_STORE - 1U,Idx);
            }
            else
            {
                /*Do nothing*/
            }
           
    }
    else
    {
           /*no need to save,just ignore the dtc*/
    }
#endif

}
/*****************************************************************************************************************
** FUNCTION      : DiagAssembleNewDTC
** DESCRIPTION   :  Modify DetectedDTCFull[] store snapshot and extended data of current logging DTC
		to memory which will written to EEPROM to perserve current DTC info.
				
** PARAMETERS    : DTC_IDX_TYPE Idx
** RETURN        : void
*****************************************************************************************************************/
static  void DiagAssembleNewDTC(DTC_IDX_TYPE Idx)
{
	uint8	temp = 0U;


        /*Find the position to save the dtc, smaller the index is, the dtc confrim earlier */
	while ((STORE_DTC[temp].DTCIndex != Idx)&&(STORE_DTC[temp].DTCIndex<DTC_END))
	{
		 temp ++;
            
		if (temp == DTC_MIN_NUMBER_TO_STORE)	/*have no vaccant slot*/
		{
			break;
		}
	}

        /*has vaccant slot,can save the dtc directly or the dtc have existed*/
	if (temp < DTC_MIN_NUMBER_TO_STORE)
	{	
            /*need to update the DTCstatus information, status information may be used for the sort*/
            DTC_vStoreNewDTC(temp,Idx);
	}
	else	 /*The DTC Space have full, and need to sort*/
	{	
            DTC_vSortStore( Idx);		
	}

	
}

/**************************************************************************************************
 * FunctionName:	DTC_vActive
 * Description:	run at system active
 * Task:			
 * Input:	   	void
 * Return:		void
*************************************************************************************************/
void DTC_vActive(void)
{
    
}
/**************************************************************************************************
 * FunctionName:	DTC_vDeInit
 * Description:	run at Ignition off
 * Task:			Back up mask state
 * Input:	   		void
 * Return:		void
*************************************************************************************************/
void DTC_vDeinit(void)
{
    uint8 u8i = 0U;
    uint8 u8Idx = 0U;
       
	for(u8i = 0U ; u8i < DTC_MIN_NUMBER_TO_STORE ; u8i++) 
	{
        u8Idx = STORE_DTC[u8i].DTCIndex;
        if(u8Idx<DTC_END)
        {
            /*Check whether  the dtc has no error in this ignition cycle */
    		if((DTCStatusCheckBitClr(u8Idx,0))&&(DTCStatusCheckBitClr(u8Idx,1)))
    		{
                if(DTC_DATA[u8Idx].Extended_Data.AgeingCnt<DTC_AGING_CRITERIA)
            	{		
            		DTC_DATA[u8Idx].Extended_Data.AgeingCnt++;						
            	}
                        /*clear pending failed */
    			DTCStatusClrBit(u8Idx,2); 
    		}
                /*Update the dtc status infor */
            DiagUpdateStoredDTC(u8i,u8Idx);
        }
	}
       
	DTC_u8WriteAllDTCToEeprom();
}

/*****************************************************************************************************************
 * FunctionName:	DTC_Reset
 * Description:	Reset DTC when reset mcu
 * Input:	   		unsigned char type
 * type:			DTC_CMD_CLEAR : Clear DTC via diagnosis command
 				DTC_AGEING_CLEAR : clear DTC via ageing mechanism
 * Return:		None
*****************************************************************************************************************/
void DTC_vReset(void)
{	

	DTC_Logging_Status = True;		/*Control by Diagnosis command*/
	DTCFunctionEnabled = True;		/* internal control , eg : power on off.*/

	/*init the DTC_DATA table.*/
	memset(&DTC_DATA[0], 0, sizeof(DTC_DATA) );
	
	/*Read DTC information from EEPROM only when each battery is on*/
	DTC_vReadAllDTCFromEeprom();

	/*must after the read eeprom , then init the data.*/
	DTC_vStandbyActive();

    DTC_au8Array[DTC_nu8SwVersion]=DTC_nSWVerSion;


}


/*****************************************************************************************************************
 * FunctionName:	DTC_vInit
 * Description:	active to on state
 * Task:			1> init the DTC except eeprom CRC Error, EEProm communication error.
 					ms CAN / Volcano init error . can config error.
 * Input:	   		void
 * Return:		void
*****************************************************************************************************************/
 void DTC_vInit(void)
{

    uint8 i = 0U;

	DTC_Logging_Status = True;		/*Control by Diagnosis command*/
	DTCFunctionEnabled = True;		/* internal control , eg : power on off.*/
	DTC_u16IGTimer=0U;
	DTC_u16PowFailureDisableTimer=0U;
    DTC_u8LoopCnt = 0;
	
	for(i = 0U ; i < DTC_END ; i ++) 
	{
   
		if((DTC_DATA[i].DTC_Aged==1U)&&(DTC_DATA[i].Extended_Data.AgeingCnt>=DTC_AGING_CRITERIA))
		{
            /*clear the confort bit and clear it from EEPROM*/
            DTCStatusClrBit(i,2);/*clear pending dtc*/
            DTCStatusClrBit(i,3);/*clear confirm dtc*/
            DTC_DATA[i].Extended_Data=(DTC_EXTENDED_DATA){0U,0U,0U,0U};
            DTC_DATA[i].DTC_Aged=0U;
            DiagDeleteStoredDTC(i);
            /*DTC_vSaveCurrentDtc*/
		}
        
		DTCStatusClrBit(i,0); /*clear test failed */
		DTCStatusClrBit(i,1); /*clear test failed this operation cycle*/		
		DTCStatusSetBit(i,6); /*set test not completed this operation cycle*/		

		DTC_DATA[i].Extended_Data.Fault_Count=DEFAULT_THR_Init;
	}

     DTC_au8Array[DTC_nu8Valid]=False;


}





static void DTC_vSaveCurrentDtc(DTC_IDX_TYPE id)
{
	DiagAssembleNewDTC(id);		
}

/*****************************************************************************************************************
 * FunctionName:	DTC_vStandbyActive
 * Description:	1> Handle when power on
 				2> init the DTC of  eeprom CRC Error, EEProm communication error.
 					ms CAN / Volcano init error . can config error.
 * Input:	   		void
 * Return:		void
*****************************************************************************************************************/
 void DTC_vStandbyActive(void)
{
	DTCFunctionEnabled = True;	
	StoreDTCHaveChanged = False;
}

/*****************************************************************************************************************
 * FunctionName:	DTC_vActiveStandby
 * Description:	Handle when power off
 * Input:	   		void
 * Return:		void
*****************************************************************************************************************/
 void DTC_vActiveStandby(void)
{	
	/*when power off , disable the DTC detected*/
	DTCFunctionEnabled = False;
	DTC_vDeinit();
}

/*****************************************************************************************************************
* FUNCTION      : DiagClearAllDtcToEeprom
* DESCRIPTION   : clear all DTC PerClasses into EEPROM to perserve current DTC info.
* Caution : 	Do not always store DTC into eeprom because it need much time.
			if 100 ms call this function more than 2~5 time , ATC will die
PARAMETERS    : void
RETURN        : void
*****************************************************************************************************************/
Std_ReturnType DTC_u8ClearAllDtc(void)
{
    uint8  retVal = 0U;
	uint8  index = 0U;

	for(index=0U;index<DTC_MIN_NUMBER_TO_STORE;index++)
	{
		memcpy(&STORE_DTC[index], &DefaultEEPStoreData, sizeof(DTC_EEP_STORE) );
	}
    
	memset(&DTC_DATA[0], 0, sizeof(DTC_DATA) );

	for(index=0U;index<DTC_END;index++)
	{
    	DTC_DATA[index].Extended_Data.Fault_Count=DEFAULT_THR_Init;
	    DTCStatusSetBit(index,4); /*set test not completed since last clear*/
        DTCStatusClrBit(index,5); /*clr test failed since last clear*/
	}
    
	StoreDTCHaveChanged=True;
       /*retVal = 0 is OK*/
       retVal = DTC_u8WriteAllDTCToEeprom();
	return retVal;	
}



/*****************************************************************************************************************
 * FUNCTION      : DTC_vWriteAllDTCToEeprom
 * DESCRIPTION   : Write all DTC PerClasses into EEPROM to perserve current DTC info.
 * Caution : 	Do not always store DTC into eeprom because it need much time.
			if 100 ms call this function more than 2~5 time , ATC will die
 * PARAMETERS    : void
 * RETURN        : void
****************************************************************************************************************/

static  uint8 DTC_u8WriteAllDTCToEeprom(void)
{
	uint8 u8Result =0U;
	uint16 u16Addr=0x0002;
	/*only when there is any DTC change should store the DTC*/
	if(StoreDTCHaveChanged == True)
	{										
		/*external interface*/
		u8Result=Rte_Call_IoHwEep_IoHwEedProto_WriteEep_DtcData_EedWrite((uint8 *)&STORE_DTC[0],sizeof(STORE_DTC));
		StoreDTCHaveChanged=False;
	}

	if(u8Result == 1U) /*no successful*/
	{
		DTC_au16Array[DTC_nu16ErrorCode]|= 0x0001U;
	}
	else
	{
		DTC_au16Array[DTC_nu16ErrorCode] &= 0xFFFEU;
	}
	return u8Result;
	
}

/*****************************************************************************************************************
FUNCTION      : DTC_vReadAllDTCFromEeprom
DESCRIPTION   : Read all DTC PerClasses from EEPROM to perserve current DTC info.
					when read out all the data of DTC , need calculate the check sum. and compare with
					the checksum in eeprom. if the check sum error . use the default value.				
PARAMETERS    : void
RETURN       	 : sucess : bit0 is checksum error (0:error , 1: ok)
			 bit1 is communication error (0: error , 1 :ok)
*****************************************************************************************************************/
static void DTC_vReadAllDTCFromEeprom(void)
{
	uint8 sucess = 0U;
	uint8 index=0U,DtcMapIdx=0U;
	
	/*external interface*/
	sucess = Rte_Call_IoHwEep_IoHwEedProto_ReadEep_DtcData_EedRead((uint8 *)&STORE_DTC[0],sizeof(STORE_DTC));
	
	if(sucess == 0U)/*sucess */
	{			
		/*update the DTC_DATA as same as STORE_DTC*/
		for(index = 0U ; index < DTC_MIN_NUMBER_TO_STORE ; index++)
		{				
			DtcMapIdx=STORE_DTC[index].DTCIndex;
			if(DtcMapIdx<DTC_END)
			{
				DTC_DATA[DtcMapIdx].Status_Byte=STORE_DTC[index].Status_Byte;
                		DTC_DATA[DtcMapIdx].Snapshot_Data=STORE_DTC[index].Snapshot_Data;
				DTC_DATA[DtcMapIdx].Extended_Data=STORE_DTC[index].Extended_Data;
				DTC_DATA[DtcMapIdx].DTC_Aged=STORE_DTC[index].Aged_Check;
			}
		}		
	}
	else
	{
		for (index = 0U; index < DTC_MIN_NUMBER_TO_STORE; index++)
		{
			memcpy(&STORE_DTC[index], &DefaultEEPStoreData, sizeof(DTC_EEP_STORE) );
		}
	}

}

Std_ReturnType DTC_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
{

	tstCcpContronType CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				DTC_Logging_Status = True;
				break;
			case 0x01:
	              case 0xA1:
				DTC_Logging_Status = (uint8)(CcpControlWord.CcpContronData&0x0001);
				break;           
				case 0x02:
		       case 0xA2:
				DTC_Logging_Status = True;
				break;
			case 0x81:
				DTC_Logging_Status = False;
				DTC_u8ClearAllDtc();
				break;
			default:
				break;
		}
	}
	else
	{
		DTC_Logging_Status = True;
	}

	return 0;
}


void DTC_vMain(void)
{    
    if(DTC_u8LoopCnt<9)
    {
        DTC_u8LoopCnt++;
    }
    else
    {
        DTC_u8LoopCnt = 0;
        DTC_vMain1();
        DTC_vMain2();
        DTC_vMain3();    
    }
    DTC_vMain10ms();
	DTC_u8WriteAllDTCToEeprom();
}
/*****************************************************************************
 Function      : DTC_u8GetValue                                              *
 Description   : The extern model get the uint8 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*****************************************************************************/
uint8 DTC_u8GetValue( DTC_tenu8VarNumber enIndex )
{
    uint8 u8ReturnValue = 0U;
    
	if ( enIndex < DTC_nu8Max )
	{
	 	u8ReturnValue = DTC_au8Array[enIndex];
	}
	else
	{
		u8ReturnValue = 0xFFU;
	}
    return u8ReturnValue;
}

/*****************************************************************************
 Function      : DTC_u8GetValue                                              *
 Description   : The extern model get the uint8 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*****************************************************************************/
uint16 DTC_u16GetValue( DTC_tenu16VarNumber enIndex )
{
    uint16 u16ReturnValue = 0U;
    
	if ( enIndex < DTC_nu16Max )
	{
	 	u16ReturnValue = DTC_au16Array[enIndex];
	}
	else
	{
		u16ReturnValue = 0xFFFFU;
	}
    return u16ReturnValue;
}

/*****************************************************************************
 Function      : DTC_u8GetNetWorkCfgValue                                              *
 Description   : The extern model get the uint8 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*****************************************************************************/
uint8 DTC_u8GetNetWorkCfgValue(DTC_tenu8VarVechileCfg enIndex )
{
    uint8 u8ReturnValue = 0U;
    
	if ( enIndex < DTC_nu8VechileCfgMax )
	{
	 	u8ReturnValue = DTC_au8NetWorkNodeCfg[enIndex];
	}
	else
	{
		u8ReturnValue = 0xFFU;
	}
    return u8ReturnValue;
}
/*****************************************************************************
 Function      : DTC_u8GetValue2                                              *
 Description   : The extern model get the uint8 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*****************************************************************************/
Std_ReturnType DTC_u8ReadStatusByte(/*INOUT*/UInt8 * Status, /*INOUT*/UInt8 * Index)
{
    	uint8 u8DTCStatus = 0U;
   	uint8 retVal = RTE_E_OK,u8i=0;
    
    	u8i = Index[0];
    
	if ( u8i < DTC_END )
	{
	 	u8DTCStatus = DTC_DATA[u8i].Status_Byte;
        retVal = RTE_E_OK;
	}
	else
	{
		u8DTCStatus = 0x00U;
        retVal = RTE_E_INVALID;
	}
    
    Status[0] = u8DTCStatus;
    
    return RTE_E_OK;
}
/*****************************************************************************
 Function      : DTC_u8GetDTCNumber  ---- $19 01                             *
 Description   : The extern model get the uint8 type variables value from    *
				 this model                                                  *
 Return Value  : void                                                        *
*****************************************************************************/
Std_ReturnType DTC_u8ReadMaskFaultDtcNum(/*INOUT*/UInt8 * Req, /*INOUT*/UInt8 * Res, /*OUT*/UInt8 * Num)
{

    uint8 i=0U,u8AvailabilityMask=0U;
    uint16 u16DtcNum=0U;

    u8AvailabilityMask = Req[0];
    u8AvailabilityMask&=DTC_nAvailableMark;

    for(i = 0x00U; i < DTC_END; i++)
    {
        if((u8AvailabilityMask & DTC_DATA[i].Status_Byte) != 0U)
        {
            u16DtcNum++;
        }
    }
    Res[0] = DTC_nAvailableMark;
    Res[1] = 0x00U;/*0:ISO15031-6DTCFormat*/
    Res[2] = (uint8)(u16DtcNum>>8U);
    Res[3] = (uint8)u16DtcNum;
    Num[0] = 0x04U;

   return RTE_E_OK;

}


/*****************************************************************************
 Function      : DTC_ReadMaskFaultDtcList ---$19 02                           *
 Description   : The extern model get the uint8 type variables value from     *
				 this model                                                   *
 Return Value  : void                                                         *
*****************************************************************************/
Std_ReturnType DTC_u8ReadMaskFaultDtcList(/*INOUT*/UInt8 * Req, /*INOUT*/UInt8 * Res, /*OUT*/UInt8 * Num)
{
         uint8 i = 0U,u8Maskbit=0U;
         uint16 u16i=0U;
    
    u8Maskbit = Req[i];
    u8Maskbit&= DTC_nAvailableMark;

    Num[0]=0x01U;
    Res[u16i]= DTC_nAvailableMark;
    u16i++;
    
         for(i = 0U; i < DTC_END; i++)
         {
                   if((u8Maskbit & DTC_DATA[i].Status_Byte) != 0U)
                   {
                            Res[u16i] = DTC_stPropertyTable[i].DTC_Code.DTCMSB;
                            u16i++;
                            Res[u16i] = DTC_stPropertyTable[i].DTC_Code.DTCLSB;
                            u16i++;
                            Res[u16i] = DTC_stPropertyTable[i].DTC_Code.DTC_Failure_Type;
                            u16i++;
                            Res[u16i] = (DTC_DATA[i].Status_Byte & DTC_nAvailableMark);
                            u16i++;
                            Num[0]+=0x04U;
                   }
         }

         return RTE_E_OK;

}

/*****************************************************************************
 Function      : DTC_u8ReadOutSnapShot --$ 19 04                             *
 Description   : output the Snapshot record data                             *
 Return Value  : uint8                                                       *
*****************************************************************************/
Std_ReturnType DTC_u8ReadSnapShotData(/*INOUT*/UInt8 * Req, /*INOUT*/UInt8 * Res, /*OUT*/UInt8 * Num)
{
	uint8 i=0U,maskbit=DTC_nAvailableMark,BeginNum = 0U;
	uint8 boFindResult=False;
	uint8 retVal = RTE_E_OK;

	/*Calc the beginning DTCNum*/
	for(i = 0U; i < DTC_END; i++)
	{
        /*Find the same DTC Num*/
		if((Req[0]== DTC_stPropertyTable[i].DTC_Code.DTCMSB)&&(Req[1]== DTC_stPropertyTable[i].DTC_Code.DTCLSB)\
			&&(Req[2]== DTC_stPropertyTable[i].DTC_Code.DTC_Failure_Type))
		{
			BeginNum=i;
			boFindResult=True;
            break;
		}
	}
    
    
    /*output data arrange*/
    /*0x01: Report DTCSnapshotRecordNumber = 0x01 ,0xFF: Report all the DTCSnapshotRecordNumber */
	if((boFindResult==True)&&((Req[3]==0xFFU)||(Req[3]==DTC_SnapshotNumTbl[0])))    
	{		
        Res[0]  = DTC_stPropertyTable[BeginNum].DTC_Code.DTCMSB;
        Res[1]  = DTC_stPropertyTable[BeginNum].DTC_Code.DTCLSB;
        Res[2]  = DTC_stPropertyTable[BeginNum].DTC_Code.DTC_Failure_Type;
        Res[3]  = ((DTC_DATA[BeginNum].Status_Byte)&maskbit);	
        Res[4]  = DTC_SnapshotNumTbl[0];	/*Record Num*/
        Res[5]  = 0x06U;	/*DTCSnapshotRecordNumberOfIdentifiers,there are 6 in this project */
        Res[6] = (uint8)(DTC_SnapshotDIDTbl[0][0]>>8U);	/*DID MSB */
        Res[7] = (uint8)(DTC_SnapshotDIDTbl[0][0]&0x00FFU);	/*DID LSB*/
        Res[8] = DTC_DATA[BeginNum].Snapshot_Data.SysBattery;
        Res[9] = (uint8)(DTC_SnapshotDIDTbl[0][1]>>8U);	/*DID MSB */
        Res[10] = (uint8)(DTC_SnapshotDIDTbl[0][1]&0x00FFU);	/*DID LSB*/
        Res[11] = (DTC_DATA[BeginNum].Snapshot_Data.VelSpeed>>8U);
        Res[12] = (uint8)(DTC_DATA[BeginNum].Snapshot_Data.VelSpeed);
        Res[13] = (uint8)(DTC_SnapshotDIDTbl[0][2]>>8U);	/*DID MSB */
        Res[14] = (uint8)(DTC_SnapshotDIDTbl[0][2]&0x00FFU);	/*DID LSB*/
        Res[15] = (uint8)(DTC_DATA[BeginNum].Extended_Data.Fault_Frequency);
        Res[16] = (uint8)(DTC_SnapshotDIDTbl[0][3]>>8U);	/*DID MSB */
        Res[17] = (uint8)(DTC_SnapshotDIDTbl[0][3]&0x00FFU);	/*DID LSB*/
        Res[18] = (uint8)(DTC_DATA[BeginNum].Snapshot_Data.u32FirstOdometer>>16U);
        Res[19] = (uint8)(DTC_DATA[BeginNum].Snapshot_Data.u32FirstOdometer>>8U);
        Res[20] = (uint8)(DTC_DATA[BeginNum].Snapshot_Data.u32FirstOdometer);
        Res[21] = (uint8)(DTC_SnapshotDIDTbl[0][4]>>8U);	/*DID MSB */
        Res[22] = (uint8)(DTC_SnapshotDIDTbl[0][4]&0x00FFU);	/*DID LSB*/
        Res[23] = (uint8)(DTC_DATA[BeginNum].Snapshot_Data.u32LastOdometer>>16U);
        Res[24] = (uint8)(DTC_DATA[BeginNum].Snapshot_Data.u32LastOdometer>>8U);
        Res[25] = (uint8)(DTC_DATA[BeginNum].Snapshot_Data.u32LastOdometer);
        Res[26] = (uint8)(DTC_SnapshotDIDTbl[0][5]>>8U);	/*DID MSB */
        Res[27] = (uint8)(DTC_SnapshotDIDTbl[0][5]&0x00FFU);	/*DID LSB*/
        Res[28] = (uint8)(DTC_DATA[BeginNum].Snapshot_Data.CoolantTemp);
        Num[0] = 29U;
        retVal = RTE_E_OK;
	}
	else
	{
		retVal = RTE_E_INVALID;
        Num[0] = 0U;
	}
	return retVal;
	
}


/*****************************************************************************
 Function      : DTC_u8ReadOutExtenddata            $ 19 06                            
 Description   : out put the extend record data                                                 
 Return Value  : uint8                                                        
*****************************************************************************/
Std_ReturnType DTC_u8ReadExtendData(/*INOUT*/UInt8 * Req, /*INOUT*/UInt8 * Res, /*OUT*/UInt8 * Num)
{
	uint8 i=0U,maskbit=DTC_nAvailableMark;
	uint8 BeginNum=0U,boFindResult=False,RecordNum=0U;
	uint8 retVal = RTE_E_OK;
	/*Calc the beginning DTCNum*/
	for(i = 0U; i < DTC_END; i++)
	{
              /*find the match DTC num*/
		if((Req[0]== DTC_stPropertyTable[i ].DTC_Code.DTCMSB)&&(Req[1]== DTC_stPropertyTable[i].DTC_Code.DTCLSB)\
			&&(Req[2]== DTC_stPropertyTable[i].DTC_Code.DTC_Failure_Type))
		{
			BeginNum=i;
			i=DTC_END;
			boFindResult=True;
		}
	}
	
	RecordNum= Req[3];
	Res[0] = DTC_stPropertyTable[BeginNum].DTC_Code.DTCMSB;
	Res[1] = DTC_stPropertyTable[BeginNum ].DTC_Code.DTCLSB;
	Res[2] = DTC_stPropertyTable[BeginNum ].DTC_Code.DTC_Failure_Type;
	Res[3] = ((DTC_DATA[BeginNum].Status_Byte)&maskbit);

	if((RecordNum==0xFFU)&&(boFindResult==True))
	{			
		Res[4] = DTC_ExtendedRecordNumTbl[0];	/*Record Num*/
		Res[5] = DTC_DATA[BeginNum].Extended_Data.MonitorCycleCnt;
		Res[6] = DTC_ExtendedRecordNumTbl[1];
		Res[7] = (uint8)((int16)((int16)DTC_DATA[BeginNum].Extended_Data.Fault_Count-128)); /*For mazada*/
		Num[0] = 8U;
		retVal = RTE_E_OK;
	}
	else if((DTC_ExtendedRecordNumTbl[0]== RecordNum)&&(boFindResult==True))
	{
		Res[4] = DTC_ExtendedRecordNumTbl[0];	/*Record Num*/
		Res[5] = DTC_DATA[BeginNum].Extended_Data.MonitorCycleCnt;
		Num[0] = 6U;
		retVal = RTE_E_OK;
	}
	else if((DTC_ExtendedRecordNumTbl[1]== RecordNum)&&(boFindResult==True))
	{
		Res[4] = DTC_ExtendedRecordNumTbl[1];
		Res[5] = (uint8)((int16)((int16)DTC_DATA[BeginNum].Extended_Data.Fault_Count-128)); /*For mazada*/
		Num[0] = 6U;
		retVal = RTE_E_OK;
	}
	else
	{
		retVal = RTE_E_INVALID;
	}
	return retVal;
}
/*****************************************************************************
 Function      : DTC_u8ReadOutDTCList  -$19 0A                                   *
 Description   : The extern model get the uint8 type variables value from     *
				 this model                                                   *
 Return Value  : uint8                                                         *
*****************************************************************************/
Std_ReturnType DTC_u8ReadSupportDtcList(/*INOUT*/UInt8 * Req, /*INOUT*/UInt8 * Res, /*OUT*/UInt16 * Num)
{
         uint8 i = 0U;
         uint16 u16i=0U;

         Num[0] = 0x01U;
         Res[0] = DTC_nAvailableMark;
         u16i++;           
         for(i = 0U; i < DTC_END; i++)
         {
                   Res[u16i] = DTC_stPropertyTable[i].DTC_Code.DTCMSB;
                   u16i++;
                   Res[u16i] = DTC_stPropertyTable[i].DTC_Code.DTCLSB;
                   u16i++;
                   Res[u16i] = DTC_stPropertyTable[i].DTC_Code.DTC_Failure_Type;
                   u16i++;
                   Res[u16i] = ((DTC_DATA[i].Status_Byte)&DTC_nAvailableMark);
                   u16i++;
                   Num[0]+=0x04U;
         }

         return RTE_E_OK;

}

uint16 DTC_u16GetIgOnDelayTmr(void)
{
	return DTC_u16IGTimer;
}
void DTC_vGetErrorBit(uint8 u8Num,uint8 u8value)
{
	if(u8value==1)
	{
		DTC_u32ArrageBuf[u8Num/DTC_nSysType]|= (DTC_DataType)(1UL<<(u8Num%DTC_nSysType));
	}
	else
	{
		DTC_u32ArrageBuf[u8Num/DTC_nSysType] &= (DTC_DataType)(~(1UL<<(u8Num%DTC_nSysType)));
	}
}



