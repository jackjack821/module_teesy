/*******************************************************************************
| Module Name: Calculate the ambient temperature
| File Name: OAT.c
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2016 Huizhou Desay SV Automotive Co., Ltd.    All rights reserved.
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
|  Zou Riming                      Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-07-11   0100        Zou Riming          fist time create
| 2016-09-22   0200        Zou Riming          Delet condition 2 of cold start 
| 
********************************************************************************/

#define OAT                        /* Name of the Module */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */

/* Foreign headerfiles */
  
/* Own headerfiles */
#include "OAT_Private.h"
/*Define location variable */
static uint16 OAT_au16Array[OAT_nu16Max];   /* OAT module output data uint16 arrary */
static uint16 OAT_u16EedData[4];
static uint8 OAT_u8NeedFilterInit;   /* decide whether the fliter value had been initial when reset in main*/
static uint8 OAT_u8NeedGetEepInit;   /* decide whether the fliter value need initial according eed data when reset in main*/
static uint8 OAT_u8NeedGetStartOnHct ;   /* decide whether Hct has init,:*/
static OAT_tstU16Group OAT_stStartOnHctValue;   /* HCT value from ACTIVE to ON*/
static OAT_tenValueSts OAT_enPhyRawValueState; /*  to indicate the physical raw value state */
static uint32 OAT_u32ValueOld;/*This is a copy of the outside Ambient temperature stored at a higher resolution  */
static uint8 OAT_u8UpdateTimeCount;/*This is for counting the updatetime  */
static uint8 OAT_u8InitCounter; /* time counter from ign on*/
static uint8 OAT_u8EnableWriteToEep;/*This is for decide to updata OAT and HCT to Eeprom  */
static uint16 OAT_u16IgnDelayTimer;

/*Define location function*/
static void OAT_vAllOutputInit(void);
static void OAT_vReadMemData(void);

static void OAT_vWriteMemData(void);
static void OAT_vGetEepInitProcess(OAT_tstU16Group *pstHctValue,OAT_tstU16Group *pstPhyRawValue);
static void OAT_vGetCurrentInitProcess(OAT_tstU16Group *pstPhyRawValue);
static void OAT_vRecordInitHctValue(void);
static void OAT_vCalculateRawValue(void);
#if (OAT_FromSensor==True)
static void OAT_vCalculateRawValueFromSensor(OAT_tstU16Group *pstSensorAdRawValue,OAT_tstU16Group *pstPhyRawValue);
#else
static void OAT_vCalculateRawValueFromBus(OAT_tstU16Group *pstBusRawValue,OAT_tstU16Group *pstPhyRawValue);
#endif
static void OAT_vValueFilterProcess(void);
static void OAT_vPerformDamping(OAT_tstU16Group *pstPhyRawValue);
static void OAT_vCcpOutputForceProcess(void);
static void OAT_vCalculateDisplayValue(void);
static void OAT_vInitCounterCalc(uint8 *InOutValue);
static uint16 OAT_u16RangeCheck(uint16 u16Input,uint16 u16MinValue,uint16 u16MaxValue);
static uint16 OAT_u16ValueLinearFilter(const uint16 u16OatRawValue,uint32 *u32PtrAddr);
static void OAT_vOutputValueToRte(void);


/* =========================================================================
* Function   : void OAT_vReset (void)
* Description: This is the reset function for the OAT module.
* Takes      : None

*/                                                                                  
void OAT_vReset(void)
{  
    OAT_vInit();
}


/* =========================================================================
* Function   : void OAT_vInit (void)
* Description: initialise  data when entering ON mode
* Takes      : None
* Returns    : None
*/                                                                        
void OAT_vInit(void)
{
    OAT_vAllOutputInit();
    OAT_u8NeedFilterInit = True; 	
    OAT_u8InitCounter=0;
    OAT_u8EnableWriteToEep = False;
    OAT_stStartOnHctValue.enState=OAT_nInvalid;
    OAT_stStartOnHctValue.u16Value=OAT_nDefaultHctValue;
    OAT_u8NeedGetStartOnHct= True;
    OAT_u8UpdateTimeCount = 0;
     OAT_vReadMemData();
    #if (OAT_UseNewCCP==True)
    OAT_ClrCcpForceByte();
    #endif
	OAT_u16IgnDelayTimer = 0;
}


/* =========================================================================
* Function   : void OAT_vDeinit (void)
* Description: This is On the ignition->off transition function for the OAT module.
* Takes      : None
* Returns    : None
*/                                                                       
void OAT_vDeinit(void)
{
    if ( OAT_u8EnableWriteToEep == True )/*by zsc,141121*/
    {
        OAT_u8EnableWriteToEep = False;
        OAT_vWriteMemData();
    }
    OAT_u16Valid = False;
}

/* =========================================================================
* Function   : void OAT_vActive (void)
* Description: Active container function of OAT
* Takes      : None
* Returns    : None
*/                                                                       
void OAT_vActive (void)              /* Active Container (background) */
{
	OAT_u16Display = OAT_u16EedOatValue/5;
	OAT_u16ErrorCode&=(~((uint16)1u<<OAT_nBitHalModuleError)); 
}

/* =========================================================================
* Function   : void OAT_vMain (void)
* Description: Main container function of OAT
* Takes      : Nothing
* Returns    : Nothing
*/
void OAT_vMain (void)
{
    OAT_tstU16Group stIgnDelay;

	if(OAT_u16IgnDelayTimer<5)
	{
		OAT_u16IgnDelayTimer++;
		stIgnDelay.enState=OAT_nInvalid;
		stIgnDelay.u16Value= False;
	}
	else
	{
		stIgnDelay.enState=OAT_nValid;
		stIgnDelay.u16Value= True;
	    //stIgnDelay.enState=OAT_u16IgnDelayFlagImport(&stIgnDelay.u16Value);
	    if((stIgnDelay.enState==OAT_nValid)&&(stIgnDelay.u16Value== True))   /* wait until IGN delay finished  */
	    {
	        OAT_vRecordInitHctValue();            /*Record the HCT value first time from active to on */
	        OAT_vCalculateRawValue();            /*Calculate out the phy Raw Value*/
	        OAT_vValueFilterProcess();             /* Physical value linear filter and hysteresis process */
	        OAT_vCcpOutputForceProcess();     /*CCP module froce Control value process*/
	        OAT_vCalculateDisplayValue();        /*Calculate out the display Value*/
	    }
	    else
	    {
	        /*Nothing to do*/
	    }
	    
	    OAT_enGetErrorCode(&OAT_u16ErrorCode);   /*Get the error code of inputs from other module*/
	    OAT_vInitCounterCalc(&OAT_u8InitCounter);    /* time counter inc per main cycle*/
	}
    
}

 
/* =========================================================================
* Function   : void OAT_vRecordInitHctValue (void)
* Description: Record Init Hct Value when first ign on
* Takes      : Nothing
* Returns    : Nothing
*/
static void OAT_vRecordInitHctValue(void)
{
    uint8 u8InitCounter;
    OAT_tstU16Group stHctValue;
    
    if(OAT_u8NeedGetStartOnHct == True)
    {
        u8InitCounter=OAT_u8InitCounter;
        stHctValue.enState=OAT_u16HctValueImport(&stHctValue.u16Value);
        if(u8InitCounter<OAT_nMaxInitTime)
        {
            if(stHctValue.enState==OAT_nValid)
            {
                OAT_u8NeedGetStartOnHct = False;
                OAT_stStartOnHctValue.enState=OAT_nValid;
                OAT_stStartOnHctValue.u16Value= stHctValue.u16Value;
            }
        }
        else
        {
            OAT_u8NeedGetStartOnHct = False;
            OAT_stStartOnHctValue.enState=OAT_nInvalid;
            OAT_stStartOnHctValue.u16Value=OAT_nDefaultHctValue ;
        }
    }
}


/* =========================================================================
* Function   : void OAT_vCalculateRawValue (void)
* Description: Calculate out the phy Raw Value
* Takes      : Nothing
* Returns    : Nothing
*/
static void OAT_vCalculateRawValue(void)
{
    static OAT_tstU16Group stPhyRawValue;

    #if (OAT_FromSensor==True)
    OAT_tstU16Group stSensorAdRawValue;
    stSensorAdRawValue.enState=OAT_u16SensorAdRawValueImport(&stSensorAdRawValue.u16Value);
    OAT_vCalculateRawValueFromSensor(&stSensorAdRawValue,&stPhyRawValue);/* OAT raw value from sensor  */
    if(stSensorAdRawValue.enState != OAT_nInvalid)
    {
        OAT_u16SensorAdRawValue=stSensorAdRawValue.u16Value;
    }

    #else
    OAT_tstU16Group stBusRawValue;
    stBusRawValue.enState = OAT_u16BusRawValueImport(&stBusRawValue.u16Value);
    OAT_vCalculateRawValueFromBus(&stBusRawValue,&stPhyRawValue);/* OAT raw value from bus  */
    if(stBusRawValue.enState != OAT_nInvalid)
    {
        OAT_u16BusRawValue=stBusRawValue.u16Value;
    }

    #endif
    
    if(stPhyRawValue.enState== OAT_nValid)
    {
        OAT_u8EnableWriteToEep=True;/* data valid, can be write to eeprom  */
    }
    if(stPhyRawValue.enState!=OAT_nInvalid)
    {
        OAT_u16PhyRawValue=stPhyRawValue.u16Value;
    }
    OAT_enPhyRawValueState=stPhyRawValue.enState;
}


#if (OAT_FromSensor==True)
/*****************************************************************************
 Function      : OAT_vCalculateRawValueFromSensor                                            
 Description   : Calculate OAT_u16RawValue according to Sensor Ad Raw Value
 Takes         : Nothing
 Return Value  : None                                    
*****************************************************************************/
static void OAT_vCalculateRawValueFromSensor(OAT_tstU16Group *pstSensorAdRawValue,OAT_tstU16Group *pstPhyRawValue)
{
    uint16 *pu16_1 = NULL;;
    uint16 *pu16_2 = NULL;
    uint16 u16OatValue=0;
    uint8 u8InitCounter=0;
    static uint8 u8ErrorCounter=0;
    OAT_tstU16Group stPowAdValid;
    
    u16OatValue=OAT_u16Value;
    u8InitCounter=OAT_u8InitCounter;
    stPowAdValid.enState=OAT_u16PowAdValidFlagImport(&stPowAdValid.u16Value);
    
    if((stPowAdValid.enState==OAT_nValid)&&\
       (stPowAdValid.u16Value==True)&&\
       (pstSensorAdRawValue->enState==OAT_nValid)) 
    {
        u8ErrorCounter=0;
        pstPhyRawValue->enState=OAT_nValid;

        #if(OAT_PtaUseGeneralSensor==True)
        pu16_1 = (uint16 *)OAT_au16Group1OatSensorAmbient_X;
        pu16_2 = (uint16 *)OAT_au16Group1OatSensorAmbient_Y;
        #else
        pu16_1 = (uint16 *)OAT_au16Group1OatAqsPtaAmbient_X;
        pu16_2 = (uint16 *)OAT_au16Group1OatAqsPtaAmbient_Y;
        #endif
        
        pstPhyRawValue->u16Value= ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,pstSensorAdRawValue->u16Value,OAT_nOatSensorAmbient_Len);  
        pstPhyRawValue->u16Value=OAT_u16RangeCheck(pstPhyRawValue->u16Value,OAT_nMinTemp,OAT_nMaxTemp);
    }
    else
    {
        if(u8InitCounter<OAT_nMaxErrorDelay)
        {
            pstPhyRawValue->enState=OAT_nInvalid;
            pstPhyRawValue->u16Value=OAT_nDefaultValue;
        }
        else
        {      
            if(u16OatValue==OAT_nu16InitOutPutValue)
            {
                pstPhyRawValue->enState=OAT_nDefault;
                pstPhyRawValue->u16Value=OAT_nDefaultValue;
            }
            else
            {
                u8ErrorCounter++;
                if(u8ErrorCounter>=OAT_nMaxErrorDelay)
                {
                    u8ErrorCounter=OAT_nMaxErrorDelay;
                    #if (OAT_MidErrorUseDefault==True)
                    pstPhyRawValue->enState=OAT_nDefault;
                    pstPhyRawValue->u16Value=OAT_nDefaultValue;
                    #else
                    pstPhyRawValue->enState=OAT_nLastValue;
                    #endif
                }
            }
        }
    }
}
#endif


#if (OAT_FromSensor==False)
/*****************************************************************************
 Function      : OAT_vCalculateRawValueFromBus                                            
 Description   : Calculate OAT_u16RawValue according to Bus Raw Value
 Takes         : Nothing
 Return Value  : None                                    
*****************************************************************************/
static void OAT_vCalculateRawValueFromBus(OAT_tstU16Group *pstBusRawValue,OAT_tstU16Group *pstPhyRawValue)
{
    uint16 u16OatValue;
    uint8 u8InitCounter=0;
    OAT_tstU16Group stComPowFailureFlag;
    OAT_tstU16Group stBusQualityFlag;

    u16OatValue=OAT_u16Value;
    u8InitCounter=OAT_u8InitCounter;
    stComPowFailureFlag.enState=OAT_u16ComPowVoltageFailureImport(&stComPowFailureFlag.u16Value);
    stBusQualityFlag.enState = OAT_u16BusQualityFlagImport(&stBusQualityFlag.u16Value);

    if((stComPowFailureFlag.enState==OAT_nValid)&&(stComPowFailureFlag.u16Value==False)&&\
        (stBusQualityFlag.enState ==OAT_nValid )&&(stBusQualityFlag.u16Value==OAT_nOK)&&\
        (pstBusRawValue->enState==OAT_nValid))
    {
        pstPhyRawValue->enState = OAT_nValid;
        pstPhyRawValue->u16Value=((pstBusRawValue->u16Value)+(OAT_nTempValueOffset-OAT_nBusValueOffset)*\
        OAT_nBusValueFactor)*OAT_nTempValueFactor/OAT_nBusValueFactor;
        pstPhyRawValue->u16Value=OAT_u16RangeCheck(pstPhyRawValue->u16Value,OAT_nMinTemp,OAT_nMaxTemp);
    }
    else
    {
        if(u8InitCounter<OAT_nMaxErrorDelay)
        {
            pstPhyRawValue->enState=OAT_nInvalid;
        }
        else
        {      
            if(u16OatValue==OAT_nu16InitOutPutValue)
            {
                pstPhyRawValue->enState=OAT_nDefault;
                pstPhyRawValue->u16Value=OAT_nDefaultValue;
            }
            else
            {
                pstPhyRawValue->enState=OAT_nLastValue;
            }
        }
    }
}
#endif


/*****************************************************************************
 Function      : OAT_vValueFilterProcess                                            
 Description   : Physical value linear filter and hysteresis process
 Takes         : Nothing
 Return Value  : None                                    
*****************************************************************************/
static void OAT_vValueFilterProcess(void)
{
    uint8 u8InitCounter=0;
    OAT_tstU16Group stHctValue;
    OAT_tstU16Group stPhyRawValue;

    u8InitCounter=OAT_u8InitCounter;
    stPhyRawValue.u16Value=OAT_u16PhyRawValue;
    stPhyRawValue.enState=OAT_enPhyRawValueState;

    if(stPhyRawValue.enState==OAT_nInvalid)
    {
        return;
    }

    if (OAT_u8NeedGetEepInit == True) 
    {
        stHctValue.enState=OAT_u16HctValueImport(&stHctValue.u16Value);
        if((stHctValue.enState==OAT_nValid)&&(stPhyRawValue.enState==OAT_nValid))
        {
            OAT_u8NeedGetEepInit=False;
            OAT_u8NeedFilterInit =False;
            OAT_vGetEepInitProcess(&stHctValue,&stPhyRawValue);/* choose OAT init value according EEP data*/
            OAT_u16Valid = True;
        }
        else if(u8InitCounter>=OAT_nMaxErrorDelay)
        {
            OAT_u8NeedGetEepInit=False;
        }
    }
    else if(OAT_u8NeedFilterInit ==True)
    {
        if(stPhyRawValue.enState==OAT_nValid)
        {
            OAT_u8NeedFilterInit = False;
        }
        OAT_vGetCurrentInitProcess(&stPhyRawValue);/* choose current input as OAT init value  */
        OAT_u16Valid = True;
    }
    else
    {
        OAT_vPerformDamping(&stPhyRawValue);/* Filter and Hysteresis process of OAT_u16Value */
    }

}


/*****************************************************************************
 Function      : OAT_vGetEepInitProcess                                            
 Description   : Determine that which value will be used as init OAT_u16Value
 Takes         : Nothing
 Return Value  : None                                    
*****************************************************************************/
/*Determine that which value will be used as outside temperature. .*/
static void OAT_vGetEepInitProcess(OAT_tstU16Group *pstHctValue,OAT_tstU16Group *pstPhyRawValue)
{
    uint16 *pu16_1;
    uint16 *pu16_2;
    uint16 u16CompareHctValue;
    uint16 u16HctEedAndCurrentDiff;

    OAT_u16DiagInfo=False;
    if(pstHctValue->u16Value<= OAT_u16HctForColdStartLimit )	/*Cold Start*/
    {
        /**********************Condition 1 **************************/
        if(pstPhyRawValue->u16Value>= pstHctValue->u16Value)
        {
            BIT_SET(OAT_u16DiagInfo,0);/*for diag*/
        }
    }

    /**********************Condition 3 **************************/
    if( pstPhyRawValue->u16Value<= OAT_u16EedOatValue)
    {    
        BIT_SET(OAT_u16DiagInfo,2);/*for diag*/
    }
    else
    {
        /**********************Condition 4 **************************/
        if( OAT_u16EedHctValue>pstHctValue->u16Value )
        {
            pu16_1 = (uint16 *)OAT_au16Group1OatDiffHctToUpdate_X;
            pu16_2 = (uint16 *)OAT_au16Group1OatDiffHctToUpdate_Y;
            u16CompareHctValue= ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2, pstPhyRawValue->u16Value,OAT_nOatDiffHctToUpdate_Len);		
            u16HctEedAndCurrentDiff = OAT_u16EedHctValue - pstHctValue->u16Value;
            if(u16HctEedAndCurrentDiff>= u16CompareHctValue)
            {
                BIT_SET(OAT_u16DiagInfo,3);/*for diag*/
            }
        }
        else
        {
            /**********************Condition 5 151022**************************/
            pu16_1 = (uint16 *)OAT_au16Group1OatLimitHctToUpdate_X;
            pu16_2 = (uint16 *)OAT_au16Group1OatLimitHctToUpdate_Y;
            u16CompareHctValue=ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,pstPhyRawValue->u16Value,OAT_nOatLimitHctToUpdate_Len);
            if(pstHctValue->u16Value<=u16CompareHctValue)
            {
                BIT_SET(OAT_u16DiagInfo,4);/*for diag*/
            }
        }
    }

    if(OAT_u16DiagInfo!=False)
    {
        #if (OAT_InitValUseCurVal==True)
        OAT_u16Value=pstPhyRawValue->u16Value;
        #else
        OAT_u16Value= MIN(pstPhyRawValue->u16Value,pstHctValue->u16Value);
        #endif
    }
    else
    {
        /**********************Except above condition **************************/
        BIT_SET(OAT_u16DiagInfo,5);/*for diag*/
        OAT_u16Value = OAT_u16EedOatValue;      
    }
    OAT_u32ValueOld = ((uint32)OAT_au16Array[OAT_nu16Value] << OAT_nChangePrarameter);
    OAT_u16ValueHys=OAT_u16Value;
}


/*****************************************************************************
 Function      : OAT_vGetCurrentInitProcess                                            
 Description   : Determine that current sensor raw value will be used as init OAT_u16Value
 Takes         : Nothing
 Return Value  : None                                    
*****************************************************************************/
static void OAT_vGetCurrentInitProcess(OAT_tstU16Group *pstPhyRawValue)
{
    OAT_u16DiagInfo= 0;/*for diag*/
    OAT_u16Value= pstPhyRawValue->u16Value;
    OAT_u32ValueOld = ((uint32)OAT_u16Value<< OAT_nChangePrarameter);
    OAT_u16ValueHys=OAT_u16Value;
}


/*****************************************************************************
 Function      : OAT_vPerformDamping                                            
 Description   : Filter and Hysteresis process of OAT_u16Value
 Takes         : Nothing
 Return Value  : None                                    
*****************************************************************************/
static void OAT_vPerformDamping(OAT_tstU16Group *pstPhyRawValue)
{
    uint16 *pu16_1=NULL;     
    OAT_tstU16Group stSysFlag1000MS;

    stSysFlag1000MS.enState = OAT_u16Sys1000msFlagImport(&stSysFlag1000MS.u16Value);
    
    if(( stSysFlag1000MS.enState==OAT_nValid)&&(stSysFlag1000MS.u16Value==True))
    {
        OAT_u8UpdateTimeCount++;
        if (OAT_u8UpdateTimeCount >= OAT_nUpdateTime)
        {
        	OAT_u8UpdateTimeCount=0;
        	OAT_u16Value = OAT_u16ValueLinearFilter(pstPhyRawValue->u16Value,&OAT_u32ValueOld);
        	pu16_1 = &OAT_u16ValueHys;/*by zsc,141121*/
        	ALG_vHysteresis_16(pu16_1, OAT_u16Value, OAT_nHysteresis);
        }
    }
}


/* ===========================================================================
* Function   :  static uint16 OAT_u16ValueLinearFilter(uint16 u16OatRawValue, uint16 *u16PtrAddr)	
* Description:  This function impliments a second order low pass filter   */
/*                  with guaranteed no loss of resolution. 
* Takes      :  u16OatRawValue - Raw ambient temperature value from sensor
                     u16PtrAddr -  old oat Value
* Returns   :   The 16-bit output of the filter
*/                           
static uint16 OAT_u16ValueLinearFilter(const uint16 u16OatRawValue,uint32 *u32PtrAddr)
{
       OAT_tstU16Group stVechileSpeed;
       uint32 u32CurrentInput = 0;

       stVechileSpeed.enState=OAT_u16VechileSpeedValueImport(&stVechileSpeed.u16Value);

	u32CurrentInput = ((uint32)u16OatRawValue << OAT_nChangePrarameter);
    
	if(u32CurrentInput > (*u32PtrAddr))
	{
		if ((stVechileSpeed.enState == OAT_nInvalid)||(stVechileSpeed.u16Value <= OAT_nVelSwitchFreeze)) /*0~ 10 km/h*/
		{
			if(u32CurrentInput > ((*u32PtrAddr) + OAT_u16FreezeRiseSpeed))
			{
				(*u32PtrAddr) += OAT_u16FreezeRiseSpeed;
			}
			else
			{
				(*u32PtrAddr) = u32CurrentInput;
			}	
		}
		else if(stVechileSpeed.u16Value <= OAT_nVelSwitch)/*10~ 40 km/h*/
		{
			if(u32CurrentInput > ((*u32PtrAddr) + OAT_u16SlowRiseSpeed))
			{
				(*u32PtrAddr) += OAT_u16SlowRiseSpeed;
			}
			else
			{
				(*u32PtrAddr) = u32CurrentInput;
			}
		}
		else /*40~  km/h or more*/
		{
			if(u32CurrentInput > ((*u32PtrAddr) + OAT_u16FastRiseSpeed))
			{
				(*u32PtrAddr) += OAT_u16FastRiseSpeed;
			}
			else
			{
				(*u32PtrAddr) = u32CurrentInput;
			}
		}
	}
	else if(u32CurrentInput < (*u32PtrAddr))
	{
		if( (*u32PtrAddr) > (u32CurrentInput + OAT_u16ConstFallSpeed))
		{
			/*- Higher changing speed when incresing. -*/
			(*u32PtrAddr) -= OAT_u16ConstFallSpeed;
		}
		else
		{
			(*u32PtrAddr) = u32CurrentInput;
		}
	}
	else
	{
		/*- Nothing to do.-*/
	}
	/* Convert from high resolution history to low resolution return value   */
	return (uint16)(*u32PtrAddr >> OAT_nChangePrarameter);
}


/*****************************************************************************
 Function      : OAT_vCcpOutputForceProcess                                            
 Description   : CCP module froce Control value process
 Takes         : Nothing
 Return Value  : None                                    
*****************************************************************************/
static void OAT_vCcpOutputForceProcess(void)
{
    #if (OAT_UseNewCCP==True)
    OAT_vCcpOutputForce(&OAT_u16Value);
    OAT_vCcpOutputForce(&OAT_u16ValueHys);
    #endif
}


/*****************************************************************************
 Function      : OAT_vCalculateDisplayValue                                            
 Description   : OAT_vCcpOutputForceProcess
 Takes         : Nothing
 Return Value  : None                                    
*****************************************************************************/
static void OAT_vCalculateDisplayValue(void)
{
    //static uint16 u16LastValue=OAT_nu16InitOutPutValue;
    if(OAT_u16Value!=OAT_nu16InitOutPutValue)
    {
        OAT_u16Display=OAT_u16Value/5;
        if(OAT_u16Display > 0xFF)
        {
            OAT_u16Display = 0xFF;
        }
    }
    //u16LastValue=OAT_u16Value;
}


/* ===========================================================================
* Function   :  static void OAT_vReadMemData(void)	
* Description:  read save data into data flash when ignition OFF->ON 
* Takes      :  None
* Returns    :  None
*/ 
static void OAT_vReadMemData(void)
{
    OAT_ReadEedGroupData((uint8 *)&OAT_u16EedData,4);
    OAT_u16EedOatValue= OAT_u16EedOatData;
    OAT_u16EedHctValue= OAT_u16EedHctData;

    if ((OAT_u16EedHctValue> OAT_nMaxTemp)\
    || (OAT_u16EedOatValue> OAT_nMaxTemp)\
    || (OAT_u16EedOatValue== OAT_nMinTemp)\
    || (OAT_u16EedHctValue== OAT_nMinTemp))
    {
        OAT_u8NeedGetEepInit = False;
    }
    else
    {
        OAT_u8NeedGetEepInit = True;
    }
}


/* ========================================
* Function   :  static void OAT_vWriteMemData(void)	
* Description:  save data into data flash when ignition ON->OFF 
* Takes      :  None
* Returns    :  None
==========================================*/ 
static void OAT_vWriteMemData(void)
{
    OAT_tstU16Group stHctValue;
    stHctValue.enState=OAT_u16HctValueImport(&stHctValue.u16Value);

    if((stHctValue.enState==OAT_nInvalid)&&(OAT_stStartOnHctValue.enState==OAT_nInvalid))
    {
        return;
    }

    if (stHctValue.u16Value > OAT_stStartOnHctValue.u16Value)
    {
        if ( (stHctValue.u16Value-OAT_stStartOnHctValue.u16Value) >= OAT_u16HctKeyOnOffDiffThres )	/*Emgine has ever run? 141227*/
        {
            OAT_u16EedHctValue= stHctValue.u16Value;
        }
        else
        {
            OAT_u16EedHctValue=MAX(stHctValue.u16Value,OAT_u16EedHctValue);
        }
    }
    else
    {
        OAT_u16EedHctValue=MAX(stHctValue.u16Value,OAT_u16EedHctValue);
    }
    OAT_u16EedOatValue= OAT_u16Value;
        
    /*- Write states to EEPRom RAM buffers. -*/ 
    OAT_u16EedOatData=OAT_u16EedOatValue;		
    OAT_u16EedHctData=OAT_u16EedHctValue;

    OAT_WriteEedGroupData((uint8 *)&OAT_u16EedData,4);
}


/*****************************************************************************
 Function      :  OAT_vAllOutputInit                                          
 Description   : All Output Variables Init
 Takes         : Nothing
 Return Value  : None                                    
*****************************************************************************/
static void OAT_vAllOutputInit( void)
{
    OAT_u16SwVersion = OAT_nSwVersion;
    OAT_u16Valid = False;
    //OAT_u16Display = OAT_nu16InitOutPutValue; 
    OAT_u16EedOatValue = OAT_nu16InitOutPutValue;
    OAT_u16EedHctValue = OAT_nu16InitOutPutValue;
    OAT_u16SensorAdRawValue = OAT_nu16InitOutPutValue;
    OAT_u16BusRawValue = OAT_nu16InitOutPutValue;
    OAT_u16PhyRawValue = OAT_nu16InitOutPutValue;
    OAT_u16Value = OAT_nu16InitOutPutValue;	
    OAT_u16ValueHys = OAT_nu16InitOutPutValue;
    OAT_u16DiagInfo = OAT_nu16InitOutPutValue;
    OAT_u16ErrorCode|=((uint16)1u<<OAT_nBitHalModuleError);
}


/*****************************************************************************
 Function      : void OAT_vInitCounterCalc(uint8 *InOutValue)                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
static void OAT_vInitCounterCalc(uint8 *InOutValue)
{
    if(*InOutValue<=OAT_nMaxInitTime)
    {
        (*InOutValue)++;
    }
}


/*******************************************************************************
*Function : OAT_tenValueSts OAT_enGetU8InitCounterExport(uint8 *value)
*Description : export the Init counter position
*takes :  Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
OAT_tenValueSts OAT_enGetU8InitCounterExport(uint8 *value)
{
    OAT_tenValueSts enReturn=OAT_nValid;
    *value=OAT_u8InitCounter;
    return enReturn;
}


/*****************************************************************************
 Function      : OAT_u16RangeCheck                                            
 Description   : limit the input value between min and max   
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static uint16 OAT_u16RangeCheck(uint16 u16Input,uint16 u16MinValue,uint16 u16MaxValue)
{
    uint16 u16RetValue=0U;
    if (u16Input <= u16MinValue)
    {
        u16RetValue = u16MinValue;
    }
    else if (u16Input >= u16MaxValue)
    {
        u16RetValue = u16MaxValue;  
    }
    else
    {
        u16RetValue = u16Input;
    }
    return u16RetValue;
}


/*****************************************************************************
 Function      : OAT_u16GetValue                                              *
 Description   : The extern model get the uint16 type variable value from this*
				 model                                                       *
 Return Value  : uint16 value                                                 *
*****************************************************************************/
uint16 OAT_u16GetValue( OAT_tenu16VarNumber enIndex )
{
    uint16 u16ReturnValue=0U;
    
	if ( enIndex < OAT_nu16Max )
	{
		u16ReturnValue = OAT_au16Array[enIndex];
	}
	else
	{
		u16ReturnValue = OAT_au16Array[OAT_nu16Max-1U];
	}
    
    return u16ReturnValue;
}


/*****************************************************************************
* EOF:OAT.c
******************************************************************************/


