
/*******************************************************************************
| Module Name: Recirculation Fresh Air control 
| File Name: RFA.c
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
| Luo Xindian                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  ------------------------------------------
| 2016.6.26         A0      Luo Xindian         module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/
#define RFA                         /* name of the module                */

/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */	
#include "Alg.h"
#include "OAT.h"
#include "CCS.h"
/* Own headerfiles */
#include "RFA_Cfg.h"
#include "RFA_Type.h"
#include "RFA_Private.h"
#include "RFA_Interface.h"
#include "RFA.h"      

/*Define location variable */
static RFA_tstMainIn RFA_stMainIn;
static RFA_tstMainOut RFA_stMainOut;
static uint8 RFA_u8InitCounter;
static uint8 	RFA_au8Array[RFA_nu8Max];
static uint16 	RFA_au16Array[RFA_nu16Max];
/*Define location function*/
#if(RFA_biSystemState== True)
void RFA_vAutoCalc(void);
static void RFA_vActualPercent(RFA_tstMainIn *Input,RFA_tstMainOut *Output);

#endif

#if (RFA_nBreathPosCfg ==True)
static void RFA_vRecircBreathTime(RFA_tstMainIn *Input,RFA_tstMainOut *Output);
#endif

#if(RFA_nLoAmbientTempCfg == True)
/*Low ambient temp limit*/
static void RFA_vLowAmbientLimit(RFA_tstMainIn *Input,RFA_tstMainOut *Output);
#endif

#if(RFA_biAQS_Cfg ==True)
/* AQS */
static uint16 RFA_u16AqsRequstRecTime;
static RFA_tenAqsReqState RFA_u8AqsReqState;

static void RFA_u8AqsRequest (RFA_tstMainIn *Input,RFA_tstMainOut *Output);
#endif

#if(RFA_nPM25Cfg ==True)
/* PM25 */
static void RFA_vPM25Request (RFA_tstMainIn *Input,RFA_tstMainOut *Output);
#endif

#if (RFA_biStartStop_Cfg == True)
static void RFA_vStartStopRecCtrl(RFA_tstMainIn *Input,RFA_tstMainOut *Output);
#endif

#if(RFA_nAmbientTempCfg == True)
static void RFA_vOatLimitCondition(RFA_tstMainIn *Input,RFA_tstMainOut *Output);
#endif

#if  ( RFA_nBloTempSwitchpoint_Cfg == True )
void RFA_vBloTempRecircleRatioCal(RFA_tstMainIn *Input,RFA_tstMainOut *Output);
#endif

void RFA_vManualCalc (RFA_tenRecircStates enMmiControl,RFA_tstMainOut *Output);
void RFA_vInputErrorCodeHandle(uint16 *ErrorCode, uint8 ErrorMaskNum,RFA_tenValueSts InputSts);
void RFA_vInitCounterCalc(uint8 *InOutValue);
static void RFA_vRfaSetPosition(RFA_tstMainOut *Output);

#if( RFA_nUseCCP == True)
static uint8 RFA_CcpForceFlag=0;
static uint16 RFA_CcpControlData[Rfa_nCcpForceMax];

/*****************************************************************************
 Function      : RFA_ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
uint8 RFA_ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
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
				RfaClrCcpForceByte();
				break;
			case 1:
				RfaSetCcpForceBit(Rfa_nSetRfaPosition);
				RFA_CcpControlData[Rfa_nSetRfaPosition]=CcpControlWord.CcpContronData;
				break;
			case 2:
				RfaClrCcpForceBit(Rfa_nSetRfaPosition);
				RFA_CcpControlData[Rfa_nSetRfaPosition]=0;
				break;
			case 3:
				break;
			case 4:
				break;
                
			case 0xA1:
				RfaSetCcpForceBit(Rfa_nSetRfaReirecTime);
				RFA_CcpControlData[Rfa_nSetRfaReirecTime]=CcpControlWord.CcpContronData;
				break;
			case 0xA2:
				RfaClrCcpForceBit(Rfa_nSetRfaReirecTime);
				RFA_CcpControlData[Rfa_nSetRfaReirecTime]=0;
				break;
            case 0xA3:
				RfaSetCcpForceBit(Rfa_nSetRfaSetPercent);
				RFA_CcpControlData[Rfa_nSetRfaSetPercent]=CcpControlWord.CcpContronData;
				break;
            case 0xA4:
				RfaClrCcpForceBit(Rfa_nSetRfaSetPercent);
				RFA_CcpControlData[Rfa_nSetRfaSetPercent]=0;
				break;
			default:
                return 0;
		}
	}
	else
	{
		RfaClrCcpForceByte();
	}
        return 1;
}


/*****************************************************************************
 Function      : Rfa_vCcpInputForce                                 
 Description   : force Input value
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void Rfa_vCcpInputForce(void)
{	
	
	if(RfaGetCcpForceBit(Rfa_nSetRfaReirecTime))
	{
		//RFA_stMainOut.u16RecirTime=RFA_CcpControlData[Rfa_nSetRfaReirecTime];
	}
	else
	{
	}
}
/*****************************************************************************
 Function      : Rfa_vCcpOutputForce                                 
 Description   : force output value
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
static void Rfa_vCcpOutputForce(void)
{	
	if(RfaGetCcpForceBit(Rfa_nSetRfaPosition))
	{
		//RFA_u16SetPos=RFA_CcpControlData[Rfa_nSetRfaPosition];
	}
	else
	{
	}
}

#endif

/***********************************************************************************
 Function      : void RFA_vReset (void)                                     
 Description   : Reset container function of RFA                   
 Takes         : Nothing
 Return Value  : Nothing                                                     
************************************************************************************/
void RFA_vReset (void)
{
    RFA_stMainOut.enRfaDisplay=0xFF;
	RFA_stMainOut.u16SetPercent=0xFFFF;
    RFA_stMainOut.u16SetPosition=0xFFFF;
	RFA_stMainOut.u16Version=0xFFFF;
    RFA_stMainOut.u16ErrorCode=0xFFFFu;
}


/***********************************************************************************
 Function      : void RFA_vInit(void)                                       
 Description   : initialize function of RFA                    
 Takes         : Nothing
 Return Value  : Nothing                                                
************************************************************************************/
void RFA_vInit (void)
{	
    RFA_u8InitCounter=0u;
	RFA_stMainOut.u16Version=RFA_nSwVersion;
    RFA_stMainOut.u16ErrorCode=0u;/*Clr all ErrorCode*/
    RFA_au8Array[RFA_nu8Valid] = False;
}


/***********************************************************************************
 Function      : void RFA_vDeinit(void)                                     
 Description   : De-init function of RFA              
 Takes         : Nothing
 Return Value  : Nothing                                                                                                
************************************************************************************/
void RFA_vDeinit (void)
{
	
}

/***********************************************************************************
 Function      : void RFA_vActive(void)                              
 Description   : Acive function of RFA 
 Takes         : Nothing
 Return Value  : Nothing                                                                                          
************************************************************************************/
void RFA_vActive(void)
{

}


/*****************************************************************************
 Function      : RFA_vMain()	                                       
 Description   : Main container function of RFA
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void RFA_vMain (void)
{
    RFA_tenValueSts enPowInputErrorFlag=RFA_nInvalid;
    RFA_tenValueSts enMmiInputErrorFlag=RFA_nInvalid;
	#if(RFA_biSystemState== True)
    RFA_tenValueSts enOatInputErrorFlag=RFA_nInvalid;
    RFA_tenValueSts enCcsInputErrorFlag=RFA_nInvalid;
	RFA_tenValueSts enSys1000msInputErrorFlag=RFA_nInvalid;
	#endif
    
    enPowInputErrorFlag=RFA_enPowFailureImport(&RFA_stMainIn.u8PowFailure);
    RFA_vInputErrorCodeHandle(&RFA_stMainOut.u16ErrorCode,RFA_nPowModule,enPowInputErrorFlag);
    enMmiInputErrorFlag|=RFA_enMMIModeImport(&RFA_stMainIn.enMmiRfaMode);
    enMmiInputErrorFlag|=RFA_enMMIControlImport(&RFA_stMainIn.enMmiRfaControl);
    RFA_vInputErrorCodeHandle(&RFA_stMainOut.u16ErrorCode,RFA_nMmiModule,enMmiInputErrorFlag);
    if((enPowInputErrorFlag==RFA_nInvalid)||(enMmiInputErrorFlag==RFA_nInvalid))
    {
		RFA_stMainOut.u16Priority=0;
        #if(RFA_biAQS_Cfg ==True)
		RFA_u16AqsRequstRecTime=0;
        #endif
		RFA_stMainOut.u16RecirTime=0;
    }
    else
    {
        if(RFA_stMainIn.u8PowFailure==False)
        {
            switch(RFA_stMainIn.enMmiRfaMode)
            {
                case RFA_nMmiRfaModeOff:
                case RFA_nMmiRfaModeDef:
                case RFA_nMmiRfaModeManual:
                case RFA_nMmiRfaModeMaxAc: 
                    RFA_vManualCalc(RFA_stMainIn.enMmiRfaControl,&RFA_stMainOut);
                    break;
                case RFA_nMmiRfaModeAuto:          
                    #if(RFA_biSystemState== True)
					enSys1000msInputErrorFlag=RFA_enSys1000msValueImport(&RFA_stMainIn.u8Sys1000ms);
                    enCcsInputErrorFlag=RFA_enCcsBloutTempImport(&RFA_stMainIn.u16CcsBloutTemp);
                    RFA_vInputErrorCodeHandle(&RFA_stMainOut.u16ErrorCode,RFA_nCcsModule,enCcsInputErrorFlag);
                    enOatInputErrorFlag=RFA_enOATValueImport(&RFA_stMainIn.u16OATValue);
                    RFA_vInputErrorCodeHandle(&RFA_stMainOut.u16ErrorCode,RFA_nOatModule,enOatInputErrorFlag);
                    if((enCcsInputErrorFlag!=RFA_nInvalid)&&\
                        (enOatInputErrorFlag!=RFA_nInvalid))
                    {
                        RFA_vAutoCalc();
                    }
					
					#endif
                    break;
                default:
                    RFA_vManualCalc(RFA_stMainIn.enMmiRfaControl,&RFA_stMainOut);
                    break;
                    
            }
        }
        else
        {
            
        }
    }
	RFA_vInitCounterCalc(&RFA_u8InitCounter);

    if(RfaGetCcpForceBit(Rfa_nSetRfaSetPercent))
	{
		RFA_stMainOut.u16SetPercent=RFA_CcpControlData[Rfa_nSetRfaSetPercent];
	}

	/* set RFA motor position*/
	RFA_vRfaSetPosition(&RFA_stMainOut);

	if(RfaGetCcpForceBit(Rfa_nSetRfaReirecTime))
	{
		RFA_stMainOut.u16RecirTime=RFA_CcpControlData[Rfa_nSetRfaReirecTime];

	}
    
    RFA_au16Array[RFA_nu16SetPos] = RFA_stMainOut.u16SetPosition;
    RFA_au16Array[RFA_nu16RecircTime] = RFA_stMainOut.u16RecirTime;
    RFA_au16Array[RFA_nu16ErrorCode] = RFA_stMainOut.u16ErrorCode;
    RFA_au16Array[RFA_nu16Priority] = RFA_stMainOut.u16Priority;
    
    RFA_au8Array[RFA_nu8Valid] = True;
    RFA_au8Array[RFA_nu8Display] = RFA_stMainOut.enRfaDisplay;
    RFA_au8Array[RFA_nu8SetPercent] = (uint8)RFA_stMainOut.u16SetPercent;
    RFA_au8Array[RFA_nu8AutoPercent] = (uint8)RFA_stMainOut.u16AutoPercent;
    
	#if(RFA_nUseRTE ==True)
	/* RTE Updated*/
    RFA_vOutputUpdate();
	#endif
}
/*****************************************************************************
 Function      : RFA_vManualCalc()	                                       
 Description   : Manual calculation container function of RFA
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void RFA_vManualCalc (RFA_tenRecircStates enMmiControl,RFA_tstMainOut *Output)
{
	if(enMmiControl == RFA_nRecircFresh)
	{
		Output->u16SetPercent=RFA_u8FreshPos;
	}
	else
	{
		Output->u16SetPercent=RFA_u8RecPos;
	}

	RFA_stMainOut.u16Priority=0;
    #if(RFA_biAQS_Cfg ==True)
    RFA_u16AqsRequstRecTime=RFA_u16AqsRecTime;/*debug: Auto Rec(Air bad)->AQS off->Air Good->AQS On, RFA should be Fresh.180208*/
    #endif
	RFA_stMainOut.u16RecirTime=0;
}
#if(RFA_biSystemState== True)
/*****************************************************************************
 Function      : void RFA_vAutoCalc (RFA_tstAutoCalcIn *Input,RFA_tstMainOut *Output)	                                       
 Description   : Auto calculation container function of RFA
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void RFA_vAutoCalc (void)
{
	#if(RFA_nBreathPosCfg ==True)
	RFA_vRecircBreathTime(&RFA_stMainIn,&RFA_stMainOut);
	#endif/*end -- #if(RFA_u8BreathPosCfg ==True)*/
	
	#if(RFA_nLoAmbientTempCfg == True)
	/*Low ambient temp limit*/
	RFA_vLowAmbientLimit(&RFA_stMainIn,&RFA_stMainOut);
	#endif
    
#if((CarConfiguration == High_End) || (CarConfiguration == Mid_End))
	#if(RFA_biAQS_Cfg ==True)
	/* with AQS function */
	 RFA_u8AqsRequest(&RFA_stMainIn,&RFA_stMainOut);
	#endif/*end--#if(RFA_biAQS_Cfg ==True)*/

	#if(RFA_nPM25Cfg ==True)
	/* with PM2.5 function */
	RFA_vPM25Request(&RFA_stMainIn,&RFA_stMainOut);
	#endif
#endif

	#if (RFA_biStartStop_Cfg == True)
	/* with start stop function */
	RFA_vStartStopRecCtrl(&RFA_stMainIn,&RFA_stMainOut);
	#endif/*end--#if (RFA_biStartStop_Cfg == True)*/
	
    #if(RFA_nAmbientTempCfg == True)
	RFA_vOatLimitCondition(&RFA_stMainIn,&RFA_stMainOut);
	#endif
		
	#if(RFA_nBloTempSwitchpoint_Cfg == True )
    RFA_vBloTempRecircleRatioCal(&RFA_stMainIn,&RFA_stMainOut);
	#endif

	RFA_vActualPercent(&RFA_stMainIn,&RFA_stMainOut);
}


/* ===========================================================================
* Function   	: void RFA_vActualPercent (RFA_tstAutoCalcIn *Input,RFA_tstMainOut *Output)
* Description	: The recirculation action in Stop of  Start/Stop .
* Takes      	: Nothing
* Returns    	: Nothing
*/
static void RFA_vActualPercent(RFA_tstMainIn *Input,RFA_tstMainOut *Output)
{
	uint8 u8i=0;
	uint16 u16Priority=0;

	for(u8i=0;u8i<RFA_nPriorityMax;u8i++)
	{
		u16Priority = Output->u16Priority &(1<<u8i);
		
		switch(u16Priority)
		{
			case 0x01:
				#if(RFA_nBreathPosCfg ==True)
				Output->u16SetPercent = RFA_u8FreshPos;
				u8i=RFA_nPriorityMax;
				#endif 
				break;
			case 0x02:
				#if(RFA_nLoAmbientTempCfg == True)
				Output->u16SetPercent = RFA_u8FreshPos;
				u8i=RFA_nPriorityMax;
				#endif
				break;
			case 0x04:
				#if(RFA_biAQS_Cfg == True)
				Output->u16SetPercent =RFA_u8RecPos;
				u8i=RFA_nPriorityMax;
				#endif
				break;
			case 0x08:
				#if(RFA_nPM25Cfg == True)
				Output->u16SetPercent =RFA_u8RecPos;
				u8i=RFA_nPriorityMax;
				#endif
				break;
			case 0x10:
				#if(RFA_nIstpCfg == True)
				Output->u16SetPercent =RFA_u8RecPos;
				u8i=RFA_nPriorityMax;
				#endif
				break;
			case 0x20:
				#if(RFA_nAmbientTempCfg == True)
				Output->u16SetPercent =RFA_u8FreshPos;
				u8i=RFA_nPriorityMax;
				#endif
				break;
			case 0x40:
				Output->u16SetPercent = Output->u16AutoPercent;
				u8i=RFA_nPriorityMax;
				break;
			default:
				Output->u16SetPercent = RFA_u8FreshPos;
				break;
		}
	}
}

#endif


#if (RFA_nBreathPosCfg ==True)
/* ===========================================================================
* Function   	: void RFA_vRecircBreathTime (RFA_tstMainIn *Input,RFA_tstMainOut *Output)
* Description	: The recirculation time count .
* Takes      	: Nothing
* Returns    	: Nothing
*/
static void RFA_vRecircBreathTime(RFA_tstMainIn *Input,RFA_tstMainOut *Output)
{
	//Rfa_vCcpInputForce();

	if ( Input->u8Sys1000ms == True )
	{		
		Output->u16RecirTime++;
	}

    if(Input->u16OATValue < RFA_nBreathEnableAmbientTemp)
    {
    	//if(Output->u16SetPercent > RFA_u8RecPosPercent90)
    	if(Output->u16SetPercent >= RFA_u8RecPosPercent75)
    	{	/* recirc state*/
    		if ( Output->u16RecirTime < RFA_u16RecirTime )
    		{	/* timer < 20min*/
    			Output->u16Priority &= ~((1<<RFA_nBreath)&0xff);/* allow recirc*/
    		}
    		else //if ( RFA_u16RecircTime < (RFA_u16RecirTime+RFA_u16FreshTime) )
    		{	/* timer >15min , timer <2min*/
    			Output->u16Priority |= (1<<RFA_nBreath);/* switch to Fresh*/
    		}
    	}
    	else
    	{	/* fresh state*/
    		if ( Output->u16RecirTime >= RFA_u16RecirTime )
    		{
    			if ( Output->u16RecirTime > (RFA_u16RecirTime+RFA_u16FreshTime))
    			{
    				Output->u16Priority &= ~((1<<RFA_nBreath)&0xff);
    				Output->u16RecirTime=0;
    			}
    		}
    		else
    		{
    			Output->u16Priority &= ~((1<<RFA_nBreath)&0xff);
    			Output->u16RecirTime=0;
    		}		
    	}
    }
    else
    {/*Ambient Temp more than 30 degree not allowed switch to Fresh*/
		Output->u16Priority &= ~((1<<RFA_nBreath)&0xff);
		Output->u16RecirTime=0;
    }
}
#endif/*end -- #if(RFA_u8BreathPosCfg ==True)*/

#if(RFA_nLoAmbientTempCfg == True)
/*****************************************************************************
 Function      : void RFA_vLowAmbientLimit (RFA_tstAutoCalcIn *Input,RFA_tstMainOut *Output)	                                       
 Description   : Auto calculation container function of RFA
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
static void RFA_vLowAmbientLimit(RFA_tstMainIn *Input,RFA_tstMainOut *Output)
{	
	if(Input->u16OATValue <= RFA_u16LowAmbientLimitLo)
	{
		Output->u16Priority |= (1<<RFA_nAmbientTAllow);
	}
	else if(Input->u16OATValue >= RFA_u16LowAmbientLimitHi)
	{
		Output->u16Priority &= ~((1<<RFA_nAmbientTAllow)&0xff);
	}
	else
	{
		/*do nothing*/
	}
}
#endif

#if(RFA_biAQS_Cfg ==True)
/* ===========================================================================
* Function   : void RFA_u8AqsRequest (void)
* Description: This is the AQS function for the RFA module.
* Takes      : None
* Returns    : None
*/
static void RFA_u8AqsRequest (RFA_tstMainIn *Input,RFA_tstMainOut *Output)
{
	RFA_tenValueSts enAqsReqInputErrorFlag=RFA_nInvalid;
	RFA_tenValueSts enAqsStateInputErrorFlag=RFA_nInvalid;

	 enAqsReqInputErrorFlag=RFA_enAqsReqValueImport(&Input->u8MmiAqsRequest);
	 RFA_vInputErrorCodeHandle(&Output->u16ErrorCode,RFA_nAqsModule,enAqsReqInputErrorFlag);

	 enAqsStateInputErrorFlag=RFA_enAqsStateValueImport(&Input->u8AqsState);
	 RFA_vInputErrorCodeHandle(&Output->u16ErrorCode,RFA_nAqsModule,enAqsStateInputErrorFlag);

	 if((enAqsReqInputErrorFlag !=RFA_nInvalid) && (enAqsStateInputErrorFlag !=RFA_nInvalid))
	 {
		switch(RFA_u8AqsReqState)
		{
			case RFA_nAqsReqFresh:
				Output->u16Priority &= ~((1<<RFA_nAQS)&0xff);
				if(Input->u8MmiAqsRequest ==On)
				{
					/*outside air condition*/
					if (  Input->u8AqsState == AQS_u8AirBad )
					{
						RFA_u8AqsReqState = RFA_nAqsReqRecir;
					}
					else if(  Input->u8AqsState == AQS_u8Initing)
					{
						RFA_u8AqsReqState=RFA_nAqsReqFresh;
					}
					else  
					{
						RFA_u8AqsReqState=RFA_nAqsReqFresh;
					}
				}
				else
				{
					/*request the min positon*/
					RFA_u8AqsReqState=RFA_nAqsReqFresh;
				}
				RFA_u16AqsRequstRecTime =0;
				break;
			case RFA_nAqsReqRecir:
				Output->u16Priority |= (1<<RFA_nAQS);

				if(Input->u8MmiAqsRequest ==On)
				{
					if(RFA_u16AqsRequstRecTime >= RFA_u16AqsRecTime)
					{
						RFA_u16AqsRequstRecTime=0;
						if (  Input->u8AqsState == AQS_u8AirBad )
						{
							RFA_u8AqsReqState = RFA_nAqsReqRecir;
						}
						else
						{
							RFA_u8AqsReqState=RFA_nAqsReqFresh;
                            Output->u16Priority &= ~((1<<RFA_nAQS)&0xff);
						}
					}
				}
				else
				{
					RFA_u8AqsReqState=RFA_nAqsReqFresh;
				}

				if(Input->u8Sys1000ms == True)
				{
					RFA_u16AqsRequstRecTime++;
				}
				break;
			default:
				RFA_u8AqsReqState=RFA_nAqsReqFresh;
				break;
		}
	 }
	
}
#endif /*#if(RFA_biAQS_Cfg ==True)*/


#if(RFA_nPM25Cfg ==True)
/* ===========================================================================
* Function   : void RFA_vPM25Request (void)
* Description: This is the PM2.5 function for the RFA module.
* Takes      : None
* Returns    : None
*/
static void RFA_vPM25Request (RFA_tstMainIn *Input,RFA_tstMainOut *Output)
{
	int16 i16PM25Diff=0;

	RFA_tenValueSts enPM25InputErrorFlag=RFA_nInvalid;

	enPM25InputErrorFlag |=RFA_enPM25InSideValueImport(&Input->u16PM25InCarDen);
	RFA_vInputErrorCodeHandle(&Output->u16ErrorCode,RFA_nPM25Module,enPM25InputErrorFlag);

	enPM25InputErrorFlag |=RFA_enPM25OutSideValueImport(&Input->u16PM25OutSideDen);
	RFA_vInputErrorCodeHandle(&Output->u16ErrorCode,RFA_nPM25Module,enPM25InputErrorFlag);


	if(enPM25InputErrorFlag !=RFA_nInvalid)
	{
		i16PM25Diff = (int16)Input->u16PM25InCarDen - (int16)Input->u16PM25OutSideDen;

		if(i16PM25Diff > RFA_i16PM25DiffHi)
		{
			Output->u16Priority &= ~((1<<RFA_nPM25)&0xff);
		}
		else if(i16PM25Diff < RFA_i16PM25DiffLo)
		{
			Output->u16Priority |= (1<<RFA_nPM25);
		}
		else
		{
			/*do nothing*/
		}
	}
}

#endif


#if (RFA_biStartStop_Cfg == True)
/* ===========================================================================
* Function   	: void RFA_vStartStopRecCtrl (void)
* Description	: The recirculation action in Stop of  Start/Stop .
* Takes      	: Nothing
* Returns    	: Nothing
*/
static void RFA_vStartStopRecCtrl(RFA_tstMainIn *Input,RFA_tstMainOut *Output)
{
	
}
#endif/*end --#if (RFA_biStartStop_Cfg == True*/

#if(RFA_nAmbientTempCfg == True)
/*****************************************************************************
 Function      : void RFA_vOatLimitCondition (RFA_tstAutoCalcIn *Input,RFA_tstMainOut *Output)	                                       
 Description   : Auto calculation container function of RFA
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
static void RFA_vOatLimitCondition(RFA_tstMainIn *Input,RFA_tstMainOut *Output)
{
	if(Input->u16OATValue <= RFA_u16OatLimitLo)
	{
		Output->u16Priority |= (1<<RFA_nAmbientTForbid);
	}
	else if(Input->u16OATValue >= RFA_u16OatLimitHi)
	{
		Output->u16Priority &= ~((1<<RFA_nAmbientTForbid)&0xff);
	}
	else
	{
		/*do nothing*/
	}
}
#endif

/* ===========================================================================
* Function   	: void RFA_vBloTempRecircleRatioCal (void)
* Description	: The recirculation ratio according to blowout temperature .
* Takes      	:  calculate the RFA percent according to blowout temperature.
* Returns    	: Nothing
*/
#if  ( RFA_nBloTempSwitchpoint_Cfg == True )
void RFA_vBloTempRecircleRatioCal(RFA_tstMainIn *Input,RFA_tstMainOut *Output)
{
	Output->u16Priority  |= (1<<RFA_nBlowoutT);
	
	if ( Input->u16CcsBloutTemp <= RFA_u16BlwOutSwitchPiont0 ) 
	{
		Output->u16AutoPercent = RFA_u8RecPos;
	}
	else if ( Input->u16CcsBloutTemp  >= RFA_u16BlwOutSwitchPiont3 )
	{
		Output->u16AutoPercent = RFA_u8FreshPos;
	}
	else
	{
		#if (RFA_biIsMotorFBValid == True)
		/* the RFA will cal 75% position, so the motor with feedback */
		if ( Output->u16AutoPercent == RFA_u8FreshPos )
		{
			if ( Input->u16CcsBloutTemp <= RFA_u16BlwOutSwitchPiont2 )
			{
				Output->u16AutoPercent = RFA_u8RecPosPercent75;
			}
		}
		else if ( Output->u16AutoPercent == RFA_u8RecPos )
		{
			if ( Input->u16CcsBloutTemp >= RFA_u16BlwOutSwitchPiont1 )
			{
				Output->u16AutoPercent = RFA_u8RecPosPercent75;
			}
		} 
		#endif
	}
}
#endif

/*****************************************************************************
 Function      : void RFA_vInitCounterCalc(uint8 *InOutValue)                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void RFA_vInitCounterCalc(uint8 *InOutValue)
{
    if(*InOutValue<10)/*1000ms*/
    {
        (*InOutValue)++;
    }
}

/*******************************************************************************
*Function : void RFA_vInputErrorCodeHandle(uint16 *ErrorCode, uint8 ErrorMaskNum,RFA_tenValueSts InputSts)
*Description : Set or Clr the ErrorCode
*takes :  Motor index
*return: Nothing
*/
void RFA_vInputErrorCodeHandle(uint16 *ErrorCode, uint8 ErrorMaskNum,RFA_tenValueSts InputSts)
{
    if(InputSts==RFA_nValid)
    {
       (*ErrorCode)&=(~((uint16)1u<<ErrorMaskNum)); 
    }
    else
    {
        (*ErrorCode)|=((uint16)1u<<ErrorMaskNum);
    }
}


/*******************************************************************************
*Function : RFA_tenValueSts RFA_enGetStMainOutExport(RFA_tstMainOut *value)
*Description : export the target position
*takes :  Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
RFA_tenValueSts RFA_enGetStMainOutExport(RFA_tstMainOut *value)
{
    RFA_tenValueSts enReturn=RFA_nValid;
    if(RFA_stMainOut.u16SetPosition==0xFFFF)
    {
        enReturn=RFA_nInvalid;
    }
    memcpy(value, &RFA_stMainOut, sizeof(RFA_tstMainOut));
    return enReturn;
}
/*******************************************************************************
*Function : RFA_tenValueSts RFA_enGetU8InitCounterExport(uint8 *value)
*Description : export the Init counter position
*takes :  Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
RFA_tenValueSts RFA_enGetU8InitCounterExport(uint8 *value)
{
    RFA_tenValueSts enReturn=RFA_nValid;
    *value=RFA_u8InitCounter;
    return enReturn;
}

/* ===========================================================================
* Function   : void RFA_vRfaSetPosition (RFA_tstMainOut *Output)
* Description: Main container function of RFA
* Takes      : None
* Returns    : None
*/
static void RFA_vRfaSetPosition(RFA_tstMainOut *Output)
{
	uint16 *pu16_1 = (uint16 *)&RFA_au16GroupRfaPositionX[0];
	uint16 *pu16_2 = (uint16 *)&RFA_au16GroupRfaPositionY[0];
	Output->u16SetPosition= ALG_u16CurveLookup_16_16_Limit(pu16_1, pu16_2,
							Output->u16SetPercent, RFA_nRfaPositionLen);

	// set position limit 
	if(Output->u16SetPosition < RFA_au16GroupReciroLimitPosition[1])
	{
		Output->u16SetPosition = RFA_au16GroupReciroLimitPosition[1];
	}
	else if(Output->u16SetPosition > RFA_au16GroupReciroLimitPosition[0])
	{
		Output->u16SetPosition = RFA_au16GroupReciroLimitPosition[0];
	}
	else
	{
		// do nothing
	}
        
    if(RfaGetCcpForceBit(Rfa_nSetRfaPosition))
	{
		Output->u16SetPosition=RFA_CcpControlData[Rfa_nSetRfaPosition];
	}
    
	//display info---->will not update when control by diag 
	if(Output->u16SetPercent >= RFA_u8RecPosPercent75)
	{
		Output->enRfaDisplay = RFA_nRecircle;
	}
	else
	{
		Output->enRfaDisplay = RFA_nRecircFresh;
	}

}

/*****************************************************************************
 Function      : RFA_u8GetValue                                              *
 Description   : The extern model get the uint8 type variable value from this*
				 model                                                       *
 Return Value  : uint8 value                                                 *
*****************************************************************************/
uint8 RFA_u8GetValue( RFA_tenu8VarNumber enIndex )
{
	if ( enIndex < RFA_nu8Max )
	{
		return RFA_au8Array[enIndex];
	}
	else
	{
		return RFA_au8Array[RFA_nu8Max-1];
	}
}


/*****************************************************************************
 Function      : RFA_u16GetValue                                              
 Description   : The extern model get the uint16 type variable value from this model                                                       
 Return Value  : uint16 value                                                 
*****************************************************************************/
uint16 RFA_u16GetValue( RFA_tenu16VarNumber enIndex )
{
	if ( enIndex < RFA_nu16Max )
	{
		return RFA_au16Array[enIndex];
	}
	else
	{
		return RFA_au16Array[RFA_nu16Max-1];
	}
}

/*******************************************************************************
*Function : static void RFA_vGetForceBctlControlFlag(CcpControl_Rfa Index)
*Description : export the target position
*takes :  Motor index
*return: none
*/
uint16 RFA_vGetForceRfaControlFlag(CcpControl_Rfa Index)
{
    uint16 u16ReturnValue;
    
    if(Index < Rfa_nCcpForceMax)
    {
        u16ReturnValue = RfaGetCcpForceBit(Index);
    }
    else
    {
        u16ReturnValue = 0u;
    }

    return u16ReturnValue;
}
/*****************************************************************************
* EOF: RFA
******************************************************************************/
