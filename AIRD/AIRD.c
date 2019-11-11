
/*******************************************************************************
| Module Name: Air distribution control interface
| File Name: AIRD.c
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
| Li Jiaye                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2016.5.17         A0      Li jiaye         module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/
#define AIRD                         /* name of the module                */

/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */	
#include "ALG.h"

/* Own headerfiles */
#include "Aird_Cfg.h"
#include "AIRD_Type.h"
#include "AIRD_Private.h"
#include "AIRD_Interface.h"
#include "AIRD.h"      

/*Define location variable */
Aird_tstMainIn Aird_stMainIn;
Aird_tstMainOut Aird_stMainOut;

Aird_tstColdStartCondiction Aird_stColdStartCondiction;
Aird_tstPurgeAirIn Aird_stPurgeAirIn;
Aird_tstPurgeAirOut Aird_stPurgeAirOut;
uint8 AIRD_u8InitCounter;

/*Position in AUTO mode corresponding to the display*/
const uint8 AIRD_au8Pos2DispTbl[]=
{
    AIRD_nMmiAirDisFace,
    AIRD_nMmiAirDisBilevel,
    AIRD_nMmiAirDisBilevel,
    AIRD_nMmiAirDisBilevel,
    AIRD_nMmiAirDisFloor,
    AIRD_nMmiAirDisMixed,	
    AIRD_nMmAirDisScreen
};

/*The aird display corresponding to the position*/
const uint8 AIRD_au8ManualPosionTbl[]=
{
	AIRD_nAutoFace,
	AIRD_nAutoBilevel2,
	AIRD_nAutoFloor,
	AIRD_nAutoMixed,
	AIRD_nAutoScreen
};


/*Define location function*/
static uint8 AIRD_u8LookupAirdState\
(const uint16 *pu16_down, const uint16 *pu16_up, uint16 u16Input, uint8 u8LastState, uint8 u8Size);
void Aird_vManualCalc (AIRD_tenMMIControlSts enMmiControl,Aird_tstMainOut *Output);
void Aird_vAutoCalc (Aird_tstAutoCalcIn *Input,Aird_tstMainOut *Output);
void Aird_vJudgeColdStartCondiction (Aird_tstAutoCalcIn *Input,Aird_tstColdStartCondiction *Output);
void Aird_vAutoPurgeAirCalc (Aird_tstPurgeAirIn *Input,Aird_tstPurgeAirOut *Output);
void Aird_vInitCounterCalc(uint8 *InOutValue);
void AIRD_vInputErrorCodeHandle(uint16 *ErrorCode, uint8 ErrorMaskNum,AIRD_tenValueSts InputSts);

/***********************************************************************************
 Function      : void AIRD_vReset (void)                                     
 Description   : Reset container function of AIRD                   
 Takes         : Nothing
 Return Value  : Nothing                                                     
************************************************************************************/
void AIRD_vReset (void)
{
    Aird_stMainOut.enAirdDisplay=0xFF;
    Aird_stMainOut.enAutoControlsts=0xFF;
    Aird_stMainOut.u16SetPosition=0xFFFF;
    Aird_stMainOut.u16ErrorCode=0xFFFFu;
}


/***********************************************************************************
 Function      : void AIRD_vInit(void)                                       
 Description   : initialize function of AIRD                    
 Takes         : Nothing
 Return Value  : Nothing                                                
************************************************************************************/
void AIRD_vInit (void)
{	
    AIRD_vReset();/*YSL add,20170318*/
    
	Aird_stColdStartCondiction.boWinterFlag=True;/*init to Winter*/
    Aird_stColdStartCondiction.u8BlowoutTempFlag=True;
    Aird_stColdStartCondiction.u8HctWaterFlag=True;
    Aird_stColdStartCondiction.u8OatFlag=True;
    Aird_stPurgeAirOut.u8PurgeAirFlag=True;
    Aird_stPurgeAirOut.u16PurgeAirTmr=100u;/*10second*/
    Aird_stPurgeAirIn.u16PurgeAirTmr=100u;/*10second*/
    AIRD_u8InitCounter=0u;
    Aird_stMainOut.u16ErrorCode=0u;/*Clr all ErrorCode*/
    AIRD_vClrForceFlagByteAction();
}


/***********************************************************************************
 Function      : void AIRD_vDeinit(void)                                     
 Description   : De-init function of AIRD              
 Takes         : Nothing
 Return Value  : Nothing                                                                                                
************************************************************************************/
void AIRD_vDeinit (void)
{
    AIRD_vClrForceFlagByteAction();
}

/***********************************************************************************
 Function      : void AIRD_vActive(void)                              
 Description   : Acive function of AIRD 
 Takes         : Nothing
 Return Value  : Nothing                                                                                          
************************************************************************************/
void AIRD_vActive(void)
{

}


/*****************************************************************************
 Function      : AIRD_vMain()	                                       
 Description   : Main container function of AIRD
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void AIRD_vMain (void)
{
    Aird_tstAutoCalcIn Aird_stAutoCalcIn;
    AIRD_tenValueSts enPowInputErrorFlag=AIRD_nInvalid;
    AIRD_tenValueSts enMmiInputErrorFlag=AIRD_nInvalid;
    AIRD_tenValueSts enOatInputErrorFlag=AIRD_nInvalid;
    AIRD_tenValueSts enCcsInputErrorFlag=AIRD_nInvalid;
    AIRD_tenValueSts enHctInputErrorFlag=AIRD_nInvalid;
    
    enPowInputErrorFlag=AIRD_enPowFailureImport(&Aird_stMainIn.u8PowFailure);
    AIRD_vInputErrorCodeHandle(&Aird_stMainOut.u16ErrorCode,Aird_nPowModule,enPowInputErrorFlag);
    enMmiInputErrorFlag|=AIRD_enMMIModeImport(&Aird_stMainIn.enMmiAirdMode);
    enMmiInputErrorFlag|=AIRD_enMMIControlImport(&Aird_stMainIn.enMmiAirdControl);
    AIRD_vInputErrorCodeHandle(&Aird_stMainOut.u16ErrorCode,Aird_nMmiModule,enMmiInputErrorFlag);
    if((enPowInputErrorFlag==AIRD_nInvalid)||(enMmiInputErrorFlag==AIRD_nInvalid))
    {
    }
    else
    {
        if(Aird_stMainIn.u8PowFailure==False)
        {
            switch(Aird_stMainIn.enMmiAirdMode)
            {
                case AIRD_nMmiAirdModeOff:
                case AIRD_nMmiAirdModeDef:
                case AIRD_nMmiAirdModeManual:
                case AIRD_nMmiAirdModeMaxAc:
                    Aird_stPurgeAirIn.u16PurgeAirTmr=0;
                    Aird_vManualCalc(Aird_stMainIn.enMmiAirdControl,&Aird_stMainOut);
                    break;
                case AIRD_nMmiAirdModeAuto:          
                    
                    Aird_stPurgeAirIn.u16PurgeAirTmr=Aird_stPurgeAirOut.u16PurgeAirTmr;
                    enOatInputErrorFlag=AIRD_enOATValueImport(&Aird_stPurgeAirIn.u16OatValue);
                    if(enOatInputErrorFlag!=AIRD_nInvalid)
                    {
                        Aird_vAutoPurgeAirCalc(&Aird_stPurgeAirIn,&Aird_stPurgeAirOut);
                    }
                    
                    Aird_stAutoCalcIn.enAutoControlsts=Aird_stMainOut.enAutoControlsts;
                    enCcsInputErrorFlag=AIRD_enCcsBloutTempImport(&Aird_stAutoCalcIn.u16CcsBloutTemp);
                    AIRD_vInputErrorCodeHandle(&Aird_stMainOut.u16ErrorCode,Aird_nCcsModule,enCcsInputErrorFlag);
                    enOatInputErrorFlag=AIRD_enOATValueImport(&Aird_stAutoCalcIn.u16OATValue);
                    AIRD_vInputErrorCodeHandle(&Aird_stMainOut.u16ErrorCode,Aird_nOatModule,enOatInputErrorFlag);
                    enHctInputErrorFlag=AIRD_enHctValueImport(&Aird_stAutoCalcIn.u16HctValue);
                    AIRD_vInputErrorCodeHandle(&Aird_stMainOut.u16ErrorCode,Aird_nHctModule,enHctInputErrorFlag);
                    Aird_stAutoCalcIn.u8PurgeAirFlag=Aird_stPurgeAirOut.u8PurgeAirFlag;
                    if((enCcsInputErrorFlag!=AIRD_nInvalid)&&\
                        (enHctInputErrorFlag!=AIRD_nInvalid)&&\
                        (enOatInputErrorFlag!=AIRD_nInvalid))
                    {
                        Aird_vAutoCalc(&Aird_stAutoCalcIn,&Aird_stMainOut);
                    }
                    break;
                default:
                    break;
                    
            }
        }
        else
        {
            
        }
    }
    Aird_vInitCounterCalc(&AIRD_u8InitCounter);
    AIRD_vOutputUpdate();
}
/*****************************************************************************
 Function      : AIRD_vMain()	                                       
 Description   : Main container function of AIRD
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void Aird_vManualCalc (AIRD_tenMMIControlSts enMmiControl,Aird_tstMainOut *Output)
{
    if(enMmiControl>AIRD_nMmAirDisScreen)
    {
        enMmiControl=AIRD_nMmAirDisScreen;
    }
    Output->u16SetPosition=AIRD_au16Group1AirdManuPosition_Tbl[enMmiControl];
    Output->enAirdDisplay=enMmiControl;
    Output->enAutoControlsts=(AIRD_tenMMIAutoControlSts)AIRD_au8ManualPosionTbl[enMmiControl];
}

/*****************************************************************************
 Function      : Aird_vAutoPurgeAirCalc()	                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void Aird_vAutoPurgeAirCalc (Aird_tstPurgeAirIn *Input,Aird_tstPurgeAirOut *Output)
{
    
    if(Input->u16PurgeAirTmr>0u)
    {
        Output->u16PurgeAirTmr=(Input->u16PurgeAirTmr)-1;
        if(Input->u16OatValue>=25*10+400u)
        {
            Output->u8PurgeAirFlag=True;
        }
        else if(Input->u16OatValue<20*10+400u)
        {
            Output->u8PurgeAirFlag=False;
            Output->u16PurgeAirTmr=0;
        }
       
    }
    else
    {
       Output->u8PurgeAirFlag=False; 
       Output->u16PurgeAirTmr=0;
    }
    
}
/*****************************************************************************
 Function      : Aird_vAutoCalc()	                                       
 Description   : Auto calculation container function of AIRD
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void Aird_vAutoCalc (Aird_tstAutoCalcIn *Input,Aird_tstMainOut *Output)
{
    uint16 *pu16_1 = NULL;
    uint16 *pu16_2 = NULL;
    uint8 u8ColdStartControl;
    //uint8 u8PurgeAirFlag;
    
    Aird_vJudgeColdStartCondiction(Input,&Aird_stColdStartCondiction);
    
    if((Aird_stColdStartCondiction.u8HctWaterFlag==True)&&\
        (Aird_stColdStartCondiction.u8BlowoutTempFlag==True)&&\
        (Aird_stColdStartCondiction.u8OatFlag==True))/*Cold Start*/
    {
        u8ColdStartControl=AIRD_nAutoScreen-(Input->enAutoControlsts);
        if(u8ColdStartControl > AIRD_nHeatercoreTempTbl_Len)  /*by zsc,avoid overflow,150811*/
  		{
  			u8ColdStartControl = AIRD_nHeatercoreTempTbl_Len;
  		}	
		pu16_1 = (uint16*)&AIRD_au16Group1HeatercoreTempDown[0];
		pu16_2 = (uint16*)&AIRD_au16Group1HeatercoreTempUp[0];
		u8ColdStartControl = AIRD_u8LookupAirdState(pu16_1, pu16_2, Input->u16HctValue,\
			                        u8ColdStartControl, AIRD_nHeatercoreTempTbl_Len); /*Calculate the air distribution state*/
		Output->enAutoControlsts = AIRD_nAutoScreen - (AIRD_tenMMIAutoControlSts)u8ColdStartControl; /*change to screen, mix, floor*/
    }
    else
    {
        if(Input->u8PurgeAirFlag==False)
        {
            if((uint8)(Input->enAutoControlsts)> AIRD_nBlowoutTempTbl_Len)  /*by zsc,avoid overflow,150811*/
            {
            	Input->enAutoControlsts = (AIRD_tenMMIAutoControlSts)AIRD_nBlowoutTempTbl_Len;
            }
            pu16_1 = (uint16*)&AIRD_au16Group1BlowoutTempDown_Tbl[0];
            pu16_2 = (uint16*)&AIRD_au16Group1BlowoutTempUp_Tbl[0];
            Output->enAutoControlsts = (AIRD_tenMMIAutoControlSts)AIRD_u8LookupAirdState(pu16_1, pu16_2, Input->u16CcsBloutTemp,\
                                    Input->enAutoControlsts, AIRD_nBlowoutTempTbl_Len); 
        }
        else
        {
           Output->enAutoControlsts=AIRD_nAutoFloor;
        }
    }
    
    if(Aird_stColdStartCondiction.boWinterFlag==False)
    {
        Output->u16SetPosition=AIRD_au16Group1AirdSummerPosition_Tbl[Output->enAutoControlsts];
    }
    else
    {
        Output->u16SetPosition=AIRD_au16Group1AirdWinterPosition_Tbl[Output->enAutoControlsts];
    }
    
    Output->enAirdDisplay=(AIRD_tenMMIControlSts)AIRD_au8Pos2DispTbl[Output->enAutoControlsts];
}
/*****************************************************************************
 Function      : void Aird_vInitCounterCalc(uint8 *InOutValue)                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void Aird_vInitCounterCalc(uint8 *InOutValue)
{
    if(*InOutValue<10)/*1000ms*/
    {
        (*InOutValue)++;
    }
}
/*****************************************************************************
 Function      : Aird_vJudgeColdStartCondiction()	                                       
 Description   : judge the cold start condiction
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void Aird_vJudgeColdStartCondiction (Aird_tstAutoCalcIn *Input,Aird_tstColdStartCondiction *Output)
{
    /*judge the season*/
	if((Input->u16OATValue)<=(10*10+400))
	{
		Output->boWinterFlag = True;
        Output->u8OatFlag=True;
	}
	else if((Input->u16OATValue)>=(15*10+400))
	{
		Output->boWinterFlag = False; 
        Output->u8OatFlag=False;
	}
    /*judge cold start HCT value*/
	if((Input->u16HctValue)<=(45*10+400))
	{
        Output->u8HctWaterFlag=True;
	}
	else if((Input->u16HctValue)>=(50*10+400))
	{
        Output->u8HctWaterFlag=False;
	}
    /*judge cold start Blowout Temp value*/
	if((Input->u16CcsBloutTemp)<=(Input->u16HctValue))
	{
        Output->u8BlowoutTempFlag=False;
	}
	else if((Input->u16CcsBloutTemp)>=(Input->u16HctValue+5*10))
	{
        Output->u8BlowoutTempFlag=True;
	}
}
/*****************************************************************************
 * Function         : AIRD_u8LookupAirdState()	                                       
 * Description     : Calculate the air distribution state depend on the input temperature.
 * Takes            : Nothing
 * Return Value  : Aird mode                                                      
*****************************************************************************/
static uint8 AIRD_u8LookupAirdState\
(const uint16 pu16_down[], const uint16 pu16_up[], uint16 u16Input, uint8 u8LastState, uint8 u8Size)	
{
	uint8 u8i;
	uint8 u8NewValue;

	//u8NewValue = u8LastState>u8Size ? u8Size : u8LastState; /*avoid the u8lastState is out of range*/
	if(u8LastState > u8Size)  /*avoid over flow, by zsc,150811*/
    {       
        u8LastState = u8Size-1;
    }
    u8NewValue = u8LastState;
	for(u8i = u8LastState; u8i > 0; u8i--)
	{
		if(u16Input <= pu16_down[u8i-1])
		{
			u8NewValue = u8i-1;
		}
		else
		{
			break;
		}
	}
	
	for (u8i = u8LastState; u8i < u8Size; u8i++)
	{                                   
		if(u16Input >= pu16_up[u8i])
		{                             
		 	u8NewValue = u8i+1;
		}
		else
		{
			break;
		}
	}
	
	return u8NewValue;
}

/*******************************************************************************
*Function : void AIRD_vInputErrorCodeHandle(uint16 *ErrorCode, uint8 ErrorMaskNum,AIRD_tenValueSts InputSts)
*Description : Set or Clr the ErrorCode
*takes :  Motor index
*return: Nothing
*/
void AIRD_vInputErrorCodeHandle(uint16 *ErrorCode, uint8 ErrorMaskNum,AIRD_tenValueSts InputSts)
{
    if(InputSts==AIRD_nValid)
    {
       (*ErrorCode)&=(~((uint16)1u<<ErrorMaskNum)); 
    }
    else
    {
        (*ErrorCode)|=((uint16)1u<<ErrorMaskNum);
    }
}
/*******************************************************************************
*Function : AIRD_tenValueSts AIRD_enGetStMainOutExport(Aird_tstMainOut *value)
*Description : export the target position
*takes :  Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
AIRD_tenValueSts AIRD_enGetStMainOutExport(Aird_tstMainOut *value)
{
    AIRD_tenValueSts enReturn=AIRD_nValid;
    if(Aird_stMainOut.u16SetPosition==0xFFFF)
    {
        enReturn=AIRD_nInvalid;
    }
    memcpy(value, &Aird_stMainOut, sizeof(Aird_tstMainOut));
    return enReturn;
}

/*******************************************************************************
*Function : void AIRD_enSetStMainOutExport(Aird_tstMainOut *value)
*Description : export the target position
*takes :  Motor index
*return: 
*/
void AIRD_enSetStMainOutExport(Aird_tstMainOut *value)
{
    Aird_stMainOut.u16SetPosition = value->u16SetPosition;
    Aird_stMainOut.enAirdDisplay = value->enAirdDisplay;
}
/*******************************************************************************
*Function : AIRD_tenValueSts AIRD_enGetU8InitCounterExport(uint8 *value)
*Description : export the Init counter position
*takes :  Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
AIRD_tenValueSts AIRD_enGetU8InitCounterExport(uint8 *value)
{
    AIRD_tenValueSts enReturn=AIRD_nValid;
    *value=AIRD_u8InitCounter;
    return enReturn;
}

/*****************************************************************************
 Function      : AIRD_u8GetValue                                              *
 Description   : The extern model get the uint8 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*****************************************************************************/
uint16 AIRD_u16GetValue( AIRD_tenu16VarNumber enIndex )
{
    uint16 u16ReturnValue=0;
    switch(enIndex)
    {
        case AIRD_nu16SetPos:
            u16ReturnValue=Aird_stMainOut.u16SetPosition;
            break;
        case AIRD_nu16ErrCode:
            u16ReturnValue=Aird_stMainOut.u16ErrorCode;
            break;
        case AIRD_nu16SWVersion:
            u16ReturnValue=AIRD_SwVersion;
            break;
        default:
            break;
    }
    return u16ReturnValue;
}

/*****************************************************************************
 Function      : AIRD_u8GetValue                                              *
 Description   : The extern model get the uint8 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*****************************************************************************/
uint8 AIRD_u8GetValue( AIRD_tenu8VarNumber enIndex )
{
    uint8 u8ReturnValue=0;
    switch(enIndex)
    {
        case AIRD_nu8Valid:
            u8ReturnValue=True;
            break;
        case AIRD_nu8Display:
            u8ReturnValue=(uint8)Aird_stMainOut.enAirdDisplay;
            break;
        case AIRD_nu8AirdAutoControl:
            u8ReturnValue=(uint8)Aird_stMainOut.enAutoControlsts;
            break;
        default:
            break;
    }
    return u8ReturnValue;

}



