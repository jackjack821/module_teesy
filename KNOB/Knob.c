/***************************************************************************************************
                                     KNOB PROCESS                                                                            
 
  .File Name  : KNOB.c

  .Description: This file is used to process the knob.

  --------------------------------------------------------------------------------------------------
    Version     Date            Author              Change
    
  --------------------------------------------------------------------------------------------------
    Rev 1.0     2014-11-09      Xu Xianglin         - module template update.
    Rev 2.0     2015-02-05      Xu xianglin	        - inquiry mode.
    Rev 3.0     2015-03-10      Xu xianglin		    - inquiry mode optimization.
    Rev 0100    2015-09-06      Li Jiaye            - changed the interface.
***************************************************************************************************/

#define KNOB_C				                                /* Name of the Module                 */
/***************************************************************************************************
                                            HEADER FILES                                          
***************************************************************************************************/

/* System-headerfiles */
#include "General.h"  
/* Foreign headerfiles */

/* Own headerfiles */
#include "Knob_Type.h" 
#include "Knob.h"                                           /* Export interface (Own interface)   */
#include "Knob_Private.h"
#include "Knob_Interface.h"

#if (KNOBType==KNOB_TWO_LINE_FULL_PHASE)|| (KNOBType==KNOB_TWO_LINE_HALF_PHASE) || (KNOBType==KNOB_THREE_LINE)||\
    (KNOBType==KNOB_DETECTOR)
#else
 #error "You should define one kind of encoders at least."
#endif
/***************************************************************************************************
                                      LOCAL VARIABLES
***************************************************************************************************/

static uint16 KNOB_u16Timer[KnobNum];/*Timer of knob status*/
static KNOB_tenPinStatus KNOB_enLastReadPin[KnobNum];/*Last Pin status*/
static KNOB_tenPinStatus KNOB_enPhase0[KnobNum];/*Detection phase 0*/
static KNOB_tenPinStatus KNOB_enPhase1[KnobNum];/*Detection phase 1*/
static KNOB_tenPinStatus KNOB_enPhase2[KnobNum];/*Detection phase 2*/
#if (KNOBType==KNOB_TWO_LINE_FULL_PHASE)
static KNOB_tenPinStatus KNOB_enPhase3[KnobNum];/*Detection phase 3*/
static KNOB_tenPinStatus KNOB_enPhase4[KnobNum];/*Detection phase 4*/
#endif
static Bool KNOB_boSignalValid[KnobNum];/*Signal valid flag*/
static Bool KNOB_boInitFlag;/*Initial flag of knob module*/
static uint8 KNOB_u8PlusCount[KnobNum];/*The knob counter of plus counter.*/
static uint8 KNOB_u8MinusCount[KnobNum];/*The knob counter of minus counter.*/
/*static uint8 KNOB_u8PtsPlusCount[KnobNum];*//*The knob counter of plus counter for PTS.*/
static uint8 KNOB_u8PtsMinusCount[KnobNum];/*The knob counter of minus counter for PTS.*/
/*static uint8 KNOB_au8Array[KnobNum];*/
static uint8 KNOB_u8ObdInitFlag;
static KNOB_tstMainOut KNOB_stMainOut[KnobNum];

/***************************************************************************************************
                                  LOCAL FUNCTION PROTOTYPE
***************************************************************************************************/
static void KNOB_vUpdateInterface(void);
static void Knob_vGetSignal(uint8 enID);
static KNOB_tenPinStatus Knob_vReadEncoder(uint8 enID);
static void KNOB_vJudgeDirection(uint8 enID);
/*static void KNOB_vCcpOutputForPts(void);*/

/*************************************************************************************************** 
  Function   : KNOB_vReset      
   
  Description: Reset container function of Knob.
                            
  Arguments  : None
  
  Returns    : None 
 **************************************************************************************************/
 
void KNOB_vReset(void)	                        
{
	uint8 u8Ctr;

	KNOB_boInitFlag = False;	
    KNOB_u8ObdInitFlag = False;
    
	for(u8Ctr=0U; u8Ctr<KnobNum; u8Ctr++)
	{
       #if (KNOBType==KNOB_TWO_LINE_HALF_PHASE) ||(KNOBType==KNOB_DETECTOR)
		KNOB_enLastReadPin[u8Ctr]=KNOB_nLowHigh;
		KNOB_enPhase0[u8Ctr]=KNOB_nLowHigh;
		KNOB_enPhase1[u8Ctr]=KNOB_nLowHigh;
		KNOB_enPhase2[u8Ctr]=KNOB_nLowHigh;
       #elif (KNOBType==KNOB_TWO_LINE_FULL_PHASE)
		KNOB_enLastReadPin[u8Ctr]=KNOB_nLowHigh;
		KNOB_enPhase0[u8Ctr]=KNOB_nLowHigh;
		KNOB_enPhase1[u8Ctr]=KNOB_nLowHigh;
		KNOB_enPhase2[u8Ctr]=KNOB_nLowHigh;
        KNOB_enPhase3[u8Ctr]=KNOB_nLowHigh;
        KNOB_enPhase4[u8Ctr]=KNOB_nLowHigh;
       #elif (KNOBType==KNOB_THREE_LINE)
		KNOB_enLastReadPin[u8Ctr]=KNOB_nHighHighHigh;
		KNOB_enPhase0[u8Ctr]=KNOB_nHighHighHigh;
		KNOB_enPhase1[u8Ctr]=KNOB_nHighHighHigh;
		KNOB_enPhase2[u8Ctr]=KNOB_nHighHighHigh;
       #endif
       
        KNOB_boSignalValid[u8Ctr]=False;
        KNOB_u16Timer[u8Ctr]=0U;
        KNOB_u8PlusCount[u8Ctr]=0U;
        KNOB_u8MinusCount[u8Ctr]=0U;
	}	
    
    KNOB_vClrForceFlagByteAction();
}



/***************************************************************************************************
  Function   	: void KNOB_vInit (void)
  
  Description	: Init function of Knob ,Called in Active->On container and through other local 
                  functions.
              	              	
  Arguments     : None
  
  Returns    	: None
***************************************************************************************************/
void KNOB_vInit(void)		/* StandbyActive Container */
{
	KNOB_vReset();
}



/***************************************************************************************************
  Function   	: void KNOB_vDeinit (void)

  Description	: Init function of Knob,Called in Active->On container and through other local 
                  functions.

  Arguments     : None

  Returns    	: None
***************************************************************************************************/
void KNOB_vDeinit(void)	/* ActiveStandby Container */
{
	KNOB_vReset();
}

#if 0
/*************************************************************************************************** 
  Function   : KNOB_vCcpOutputForPts     
   
  Description: force output value.
                            
  Arguments  : None
  
  Returns    : Nothing.
***************************************************************************************************/
static void KNOB_vCcpOutputForPts(void)
{	
	if(KNOB_GetCcpForceBit(KNOB_nRecordCounter))
	{
        if(KNOB_u8ObdInitFlag == False)
        {
            KNOB_u8ObdInitFlag = True;
            KNOB_au8Array[KNOB_nu8Knob2PtsPlusCounter] = 0U;
            KNOB_au8Array[KNOB_nu8Knob2PtsMinusCounter] = 0U;
            KNOB_au8Array[KNOB_nu8Knob1PtsPlusCounter] = 0U;
            KNOB_au8Array[KNOB_nu8Knob1PtsMinusCounter] = 0U;

            KNOB_u8PtsPlusCount[KNOB_nKnob2Id] = 0U;
            KNOB_u8PtsMinusCount[KNOB_nKnob2Id] = 0U;
            KNOB_u8PtsPlusCount[KNOB_nKnob1Id] = 0U;
            KNOB_u8PtsMinusCount[KNOB_nKnob1Id] = 0U;
         }
         
        KNOB_au8Array[KNOB_nu8Knob2PtsPlusCounter] += KNOB_u8PtsPlusCount[KNOB_nKnob2Id];
        if(KNOB_au8Array[KNOB_nu8Knob2PtsPlusCounter]>200U)
        {
            KNOB_au8Array[KNOB_nu8Knob2PtsPlusCounter]=200U;
        }
        
        KNOB_au8Array[KNOB_nu8Knob2PtsMinusCounter] += KNOB_u8PtsMinusCount[KNOB_nKnob2Id];
        if(KNOB_au8Array[KNOB_nu8Knob2PtsMinusCounter]>200U)
        {
            KNOB_au8Array[KNOB_nu8Knob2PtsMinusCounter]=200U;
        }
        
        KNOB_au8Array[KNOB_nu8Knob1PtsPlusCounter] += KNOB_u8PtsPlusCount[KNOB_nKnob1Id];
        if(KNOB_au8Array[KNOB_nu8Knob1PtsPlusCounter]>200U)
        {
            KNOB_au8Array[KNOB_nu8Knob1PtsPlusCounter]=200U;
        }
        
        KNOB_au8Array[KNOB_nu8Knob1PtsMinusCounter] += KNOB_u8PtsMinusCount[KNOB_nKnob1Id];
        if(KNOB_au8Array[KNOB_nu8Knob1PtsMinusCounter]>200U)
        {
            KNOB_au8Array[KNOB_nu8Knob1PtsMinusCounter]=200U;
        }
	}
	else
	{
        KNOB_u8ObdInitFlag = False;
        KNOB_au8Array[KNOB_nu8Knob2PtsPlusCounter] = 0U;
        KNOB_au8Array[KNOB_nu8Knob2PtsMinusCounter] = 0U;
        KNOB_au8Array[KNOB_nu8Knob1PtsPlusCounter] = 0U;
        KNOB_au8Array[KNOB_nu8Knob1PtsMinusCounter] = 0U;

        KNOB_u8PtsPlusCount[KNOB_nKnob2Id] = 0U;
        KNOB_u8PtsMinusCount[KNOB_nKnob2Id] = 0U;
        KNOB_u8PtsPlusCount[KNOB_nKnob1Id] = 0U;
        KNOB_u8PtsMinusCount[KNOB_nKnob1Id] = 0U;
	}
}

#endif
/***************************************************************************************************
  Function   	: void KNOB_vMain (void)

  Description	: Main container function of Knob,call this function in 100ms container.

  Arguments     : None

  Returns    	: None
***************************************************************************************************/
void KNOB_vMain(void)
{  
	if((KNOB_sbiLowVoltage == True)||(KNOB_sbiHighVoltage == True))
   	{
   		KNOB_vReset();
   	}
	else
	{
		KNOB_boInitFlag = True;	
        /*KNOB_vCcpOutputForPts();*/
        KNOB_vUpdateInterface();
	}

    KNOB_vMainExportAction();
   #ifdef KNOB_RTE
    KNOB_vUpdateRteOutput();
   #endif
} 


/***************************************************************************************************
  Function     : void Knob_v1msGetSignal(void)
  
  Description : To detect the two phase signal from encoder.
  Call this function every 1ms cycle.
  
  Arguments    : Nothing
  
  Returns      : Nothing

		   CW:
		       ------		   ------		  
		   A:	     |		  |	     |		  
					 |________|      |________ 

				  11->01-> 00-> 10->  11 
		   B:	   ------		   ------		  
			    	     |		  |	     |		  
						 |________|      |________ 


		   CCW:


		   A:      ------		   ------		  
			    	     |		  |	      |		  
						 |________|       |________ 
				  11->10-> 00-> 01->11   		
		        ------		    ------	  
		   B:	      |		   |	   |		  
					  |________|       |________ 
			
***************************************************************************************************/

void KNOB_v1msProcess(void)
{ 
    uint8 u8Ctr;
    
    if(KNOB_boInitFlag == True)
    {
        for(u8Ctr=0U; u8Ctr<KnobNum; u8Ctr++)
        {
            Knob_vGetSignal(u8Ctr);
            KNOB_vJudgeDirection(u8Ctr);
        }
    }
}


/***************************************************************************************************
  Function   	: void Knob_vGetSignal(uint8 enID)

  Description	: Get signal from IO and filtering. Since there will be two-phase signal input to 
                  MCU, the status of signal will be one of LowLow¡¢LowHigh¡¢HighLow and HighHigh.

  Arguments     : Called every 1ms cycle.

  Returns    	: None
***************************************************************************************************/
static void Knob_vGetSignal(uint8 enID)
{
    KNOB_tenPinStatus enReadPin;Bool boCheckKnobEvent = True;

    enReadPin = Knob_vReadEncoder(enID);
    
    KNOB_boSignalValid[enID]=False; 
    if(enReadPin== KNOB_enLastReadPin[enID])
    { 
        if(KNOB_u16Timer[enID]<Knob_stProperty[enID].u16MaxTransitionTime)
        {
            KNOB_u16Timer[enID]++;
        }
/*------------------------------------------------------------------------------------------------*/
       #if (KNOBType==KNOB_TWO_LINE_HALF_PHASE)||(KNOBType==KNOB_DETECTOR)
        else if((enReadPin==KNOB_nLowHigh)||(enReadPin==KNOB_nHighLow))
        {
            KNOB_enPhase2[enID]= KNOB_nLowLow;     /*to avoid stay in transition position for long*/
            boCheckKnobEvent = False;
        } 
/*------------------------------------------------------------------------------------------------*/
       #elif(KNOBType==KNOB_TWO_LINE_FULL_PHASE)
        #if defined KNOB_TWO_LINE_FULL_PHASE_HIGH_START  
        else if((enReadPin==KNOB_nLowHigh)||(enReadPin==KNOB_nHighLow)||(enReadPin==KNOB_nLowLow))
        {
            KNOB_enPhase4[enID]= KNOB_nHighHigh;     /*to avoid stay in transition position for long*/
            boCheckKnobEvent = False;
        } 
        #elif defined KNOB_TWO_LINE_FULL_PHASE_LOW_START
        else if((enReadPin==KNOB_nLowHigh)||(enReadPin==KNOB_nHighLow)||(enReadPin==KNOB_nHighHigh))
        {
            KNOB_enPhase4[enID]= KNOB_nLowLow;     /*to avoid stay in transition position for long*/
            boCheckKnobEvent = False;
        }
        #else
            #error "You should define one of KNOB_TWO_LINE_FULL_PHASE_LOW_START and KNOB_TWO_LINE_FULL_PHASE_HIGH_START at lease."
        #endif
/*------------------------------------------------------------------------------------------------*/
       #elif (KNOBType==KNOB_THREE_LINE)
        else if(enReadPin==KNOB_nHighHighHigh)
        {
            KNOB_enPhase2[enID]= KNOB_nLowLowLow;     /*to avoid stay in transition position for long*/
            boCheckKnobEvent = False;
        }  
       #endif
/*------------------------------------------------------------------------------------------------*/
        else{}
    }
    else
    {
        KNOB_u16Timer[enID] = 1U;
        KNOB_enLastReadPin[enID] = enReadPin;
    }
    if(boCheckKnobEvent)
    {
       #if (KNOBType==KNOB_TWO_LINE_HALF_PHASE) ||(KNOBType==KNOB_THREE_LINE)||(KNOBType==KNOB_DETECTOR)
        if((KNOB_u16Timer[enID] >= Knob_stProperty[enID].u16FilterTime)&&(enReadPin!=KNOB_enPhase2[enID]))
       #elif(KNOBType==KNOB_TWO_LINE_FULL_PHASE)
        if((KNOB_u16Timer[enID] >= Knob_stProperty[enID].u16FilterTime)&&(enReadPin!=KNOB_enPhase4[enID]))
       #endif
        {
            KNOB_enPhase0[enID] = KNOB_enPhase1[enID];
            KNOB_enPhase1[enID] = KNOB_enPhase2[enID];
           #if (KNOBType==KNOB_TWO_LINE_HALF_PHASE)||(KNOBType==KNOB_THREE_LINE)||(KNOBType==KNOB_DETECTOR)
            KNOB_enPhase2[enID] = enReadPin;  
           #elif(KNOBType==KNOB_TWO_LINE_FULL_PHASE)
            KNOB_enPhase2[enID] = KNOB_enPhase3[enID];  
            KNOB_enPhase3[enID] = KNOB_enPhase4[enID];
            KNOB_enPhase4[enID] = enReadPin;  
           #endif         
            KNOB_boSignalValid[enID]=True;
        }
    }
}


/***************************************************************************************************
  Function   	: void Knob_vReadEncoder(uint8 enID)

  Description	: Get signal from encoder through IO port.

  Arguments     : Called every 1ms cycle.

  Returns    	: None
***************************************************************************************************/
static KNOB_tenPinStatus Knob_vReadEncoder(uint8 enID)
{
    KNOB_tenPinStatus enReadPin;uint16 u8Buffer1, u8Buffer2;
    
    Knob_stProperty[enID].fpKnobGetStatusA(&u8Buffer1);
    Knob_stProperty[enID].fpKnobGetStatusB(&u8Buffer2);
    
   #if (KNOBType==KNOB_TWO_LINE_HALF_PHASE) || (KNOBType==KNOB_TWO_LINE_FULL_PHASE)||(KNOBType==KNOB_DETECTOR)
    u8Buffer1 = (uint8)(((uint32)u8Buffer1<<1U)|(uint32)u8Buffer2);
   #elif (KNOBType==KNOB_THREE_LINE)
    KNOB_tenPinStatus u8Buffer3;
    Knob_stProperty[enID].fpKnobGetStatusC(&u8Buffer3);
    u8Buffer1 = (uint8)(((uint32)u8Buffer1<<2U)|((uint32)u8Buffer2<<1U)|((uint32)u8Buffer3))&0x07;
   #endif
    
    switch(u8Buffer1)
    {
       #if (KNOBType==KNOB_TWO_LINE_HALF_PHASE)|| (KNOBType==KNOB_TWO_LINE_FULL_PHASE)||(KNOBType==KNOB_DETECTOR)
        case 0x00: enReadPin = KNOB_nLowLow;break;
        case 0x01: enReadPin = KNOB_nLowHigh;break;
        case 0x02: enReadPin = KNOB_nHighLow;break;
        case 0x03: enReadPin = KNOB_nHighHigh;break;
       #elif (KNOBType==KNOB_THREE_LINE)
        case 0x03: enReadPin = KNOB_nLowHighHigh;break;/*011*/
        case 0x05: enReadPin = KNOB_nHighLowHigh;break;/*101*/
        case 0x06: enReadPin = KNOB_nHighHighLow;break;/*110*/
        case 0x07: enReadPin = KNOB_nHighHighHigh;break;/*111*/
       #endif
        default: break;
    }
    return enReadPin;
}


/***************************************************************************************************
  Function   	: void KNOB_vJudgeDirection(uint8 enID)

  Description	: Judge direction according to the phase0 phase1 and phase2.

  Arguments     : Called every 1ms cycle.

  Returns    	: None
***************************************************************************************************/
static void KNOB_vJudgeDirection(uint8 enID)
{
  #if(KNOBType==KNOB_TWO_LINE_HALF_PHASE)  
   if(KNOB_boSignalValid[enID] == True)
   {
       if(KNOB_enPhase0[enID] == KNOB_nLowLow)
        {
            if(KNOB_enPhase1[enID] == KNOB_nLowHigh)
            {
                if(KNOB_enPhase2[enID] == KNOB_nHighHigh)
                {
                    KNOB_u8MinusCount[enID]++;
                    KNOB_u8PlusCount[enID]=0U;                
                }
            }
            else if(KNOB_enPhase1[enID] == KNOB_nHighLow)
            {
                if(KNOB_enPhase2[enID] == KNOB_nHighHigh)
                {
                    KNOB_u8PlusCount[enID]++;
                    KNOB_u8MinusCount[enID]=0U;
                }
            }
            else{}
        }
        else if(KNOB_enPhase0[enID] == KNOB_nHighHigh)
        {
            if(KNOB_enPhase1[enID] == KNOB_nLowHigh)
            {
                if(KNOB_enPhase2[enID] == KNOB_nLowLow)
                {
                    KNOB_u8PlusCount[enID]++;
                    KNOB_u8MinusCount[enID]=0U;
                }
            }
            else if(KNOB_enPhase1[enID] == KNOB_nHighLow)
            {
                if(KNOB_enPhase2[enID] == KNOB_nLowLow)
                {
                    KNOB_u8MinusCount[enID]++;
                    KNOB_u8PlusCount[enID]=0U;
                }
            }
            else{}
        }
        else{}
    }
/*------------------------------------------------------------------------------------------------*/   
  #elif (KNOBType==KNOB_TWO_LINE_FULL_PHASE)
   if(KNOB_boSignalValid[enID] == True)
   {
       /*#ifdef KNOB_TWO_LINE_FULL_PHASE_LOW_START
        if((KNOB_enPhase0[enID] == KNOB_nLowLow)&&(KNOB_enPhase1[enID] == KNOB_nHighLow)&&\
           (KNOB_enPhase2[enID] == KNOB_nHighHigh)&&(KNOB_enPhase3[enID] == KNOB_nLowHigh)&&\
           (KNOB_enPhase4[enID] == KNOB_nLowLow))
        {
            KNOB_u8MinusCount[enID]++;
            KNOB_u8PlusCount[enID]=0U;            
        }
        else if((KNOB_enPhase0[enID] == KNOB_nLowLow)&&(KNOB_enPhase1[enID] == KNOB_nLowHigh)&&\
           (KNOB_enPhase2[enID] == KNOB_nHighHigh)&&(KNOB_enPhase3[enID] == KNOB_nHighLow)&&\
           (KNOB_enPhase4[enID] == KNOB_nLowLow))
        {
            KNOB_u8MinusCount[enID]=0U;
            KNOB_u8PlusCount[enID]++;            
        }
       #elif defined KNOB_TWO_LINE_FULL_PHASE_HIGH_START
       */
        if((KNOB_enPhase0[enID] == KNOB_nHighHigh)&&(KNOB_enPhase1[enID] == KNOB_nLowHigh)&&\
           (KNOB_enPhase2[enID] == KNOB_nLowLow)&&(KNOB_enPhase3[enID] == KNOB_nHighLow)&&\
           (KNOB_enPhase4[enID] == KNOB_nHighHigh))
        {
            KNOB_u8MinusCount[enID]++;
            KNOB_u8PlusCount[enID]=0U;            
        }
        else if((KNOB_enPhase0[enID] == KNOB_nHighHigh)&&(KNOB_enPhase1[enID] == KNOB_nHighLow)&&\
           (KNOB_enPhase2[enID] == KNOB_nLowLow)&&(KNOB_enPhase3[enID] == KNOB_nLowHigh)&&\
           (KNOB_enPhase4[enID] == KNOB_nHighHigh))
        {
            KNOB_u8MinusCount[enID]=0U;
            KNOB_u8PlusCount[enID]++;            
        }
        /*
       #else
        #error "You should define one of KNOB_TWO_LINE_FULL_PHASE_LOW_START and KNOB_TWO_LINE_FULL_PHASE_HIGH_START at lease."
       #endif
       */
   }

/*------------------------------------------------------------------------------------------------*/     
  #elif (KNOBType==KNOB_THREE_LINE)
   if(KNOB_boSignalValid[enID] == True)
   {
        if(KNOB_enPhase0[enID] == KNOB_nHighHighLow)
        {
            if(KNOB_enPhase1[enID] == KNOB_nHighHighHigh)
            {
                if(KNOB_enPhase2[enID] == KNOB_nHighLowHigh)/*110->101*/
                {
                    KNOB_u8MinusCount[enID]=0U;
                    KNOB_u8PlusCount[enID]++;                
                }
                else if(KNOB_enPhase2[enID] == KNOB_nLowHighHigh)/*110->011*/
                {
                    KNOB_u8MinusCount[enID]++;
                    KNOB_u8PlusCount[enID]=0U;                
                }                
            }
        }
        else if(KNOB_enPhase0[enID] == KNOB_nHighLowHigh)
        {
            if(KNOB_enPhase1[enID] == KNOB_nHighHighHigh)
            {
                if(KNOB_enPhase2[enID] == KNOB_nLowHighHigh)/*101->011*/
                {
                    KNOB_u8MinusCount[enID]=0U;
                    KNOB_u8PlusCount[enID]++; 
                }
                else if(KNOB_enPhase2[enID] == KNOB_nHighHighLow)/*101->110*/
                {
                    KNOB_u8MinusCount[enID]++;
                    KNOB_u8PlusCount[enID]=0U;               
                }
            }
        }
        else if(KNOB_enPhase0[enID] == KNOB_nLowHighHigh)
        {
            if(KNOB_enPhase1[enID] == KNOB_nHighHighHigh)
            {
                if(KNOB_enPhase2[enID] == KNOB_nHighHighLow)/*011->110*/
                {
                    KNOB_u8MinusCount[enID]=0U;
                    KNOB_u8PlusCount[enID]++; 
                }
                else if(KNOB_enPhase2[enID] == KNOB_nHighLowHigh)/*011->101*/
                {
                    KNOB_u8MinusCount[enID]++;
                    KNOB_u8PlusCount[enID]=0U;               
                }
            }
        }
    }
/*------------------------------------------------------------------------------------------------*/     
  #elif (KNOBType==KNOB_DETECTOR)
   if(KNOB_boSignalValid[enID] == True)
   {
        if(KNOB_enPhase0[enID] == KNOB_nHighHigh)
        {
            if(KNOB_enPhase1[enID] == KNOB_nLowHigh)
            {
                if(KNOB_enPhase2[enID] == KNOB_nHighHigh)
                {
                    KNOB_u8PlusCount[enID]++;
                    KNOB_u8MinusCount[enID]=0U;
                }
            }
            else if(KNOB_enPhase1[enID] == KNOB_nHighLow)
            {
                if(KNOB_enPhase2[enID] == KNOB_nHighHigh)
                {
                    KNOB_u8MinusCount[enID]++;
                    KNOB_u8PlusCount[enID]=0U;
                }
            }
            else{}
        }
    }
  #endif
/*
  KNOB_u8PtsPlusCount[enID] = KNOB_u8PlusCount[enID];
  KNOB_u8PtsMinusCount[enID] = KNOB_u8PlusCount[enID];
  */
}


/***************************************************************************************************
  Function     : void KNOB_vUpdateInterface(void)

  Description  : Update the rotary direction and direction counter.

  Takes        : None
  
  *Returns     : None
***************************************************************************************************/
static void KNOB_vUpdateInterface(void)
{
    uint8 i;
    for(i=0;i<KnobNum;i++)
    {
        KNOB_stMainOut[i].u8PlusCounter=KNOB_u8PlusCount[i];
        KNOB_stMainOut[i].u8MinusCounter=KNOB_u8MinusCount[i];
        if(KNOB_u8PlusCount[i]>0u)
        {
            KNOB_stMainOut[i].enRotaryOperate=KNOB_nRotaryUp;
        }
        else if(KNOB_u8MinusCount[i]>0u)
        {
            KNOB_stMainOut[i].enRotaryOperate=KNOB_nRotaryDn;
        }
        else
        {
            KNOB_stMainOut[i].enRotaryOperate=KNOB_nNoRot;
        }
        KNOB_u8PlusCount[i]=0u;
        KNOB_u8MinusCount[i]=0u;
    }

}


/*******************************************************************************
*Function : KNOB_tenValueSts KNOB_enGetMainOutputExport(uint8 index,KNOB_tstMainOut *value)
*Description : export motor struct
*takes : Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
KNOB_tenValueSts KNOB_enGetMainOutputExport(uint8 index, KNOB_tstMainOut *value)
{
    KNOB_tenValueSts enReturn=KNOB_nValid;
    memcpy(value, &KNOB_stMainOut[index], sizeof(KNOB_tstMainOut));
    return enReturn;
}


/***************************************************************************************************
  Function     : uint8 KNOB_u8GetValue(KNOB_tenVarNum Num)

  Description  : For other module to get the rotary direction for other.

  Takes        : None

  Returns      : None
***************************************************************************************************/
uint8 KNOB_u8Getvalue(Knob_tenu8Output index)
{
	uint8 u8returnValue=0;
	switch(index)
	{
		case Knob_enTempLRotaryOperate:
			u8returnValue=KNOB_stMainOut[0].enRotaryOperate;
			break;
		case Knob_enTempRRotaryOperate:
			u8returnValue=KNOB_stMainOut[1].enRotaryOperate;
			break;
		case Knob_enTempLPlusCounter:
			u8returnValue=KNOB_stMainOut[0].u8PlusCounter;
			break;
		case Knob_enTempRPlusCounter:
			u8returnValue=KNOB_stMainOut[1].u8PlusCounter;
			break;
		case Knob_enTempLMinusCounter:
			u8returnValue=KNOB_stMainOut[0].u8MinusCounter;
			break;
		case Knob_enTempRMinusCounter:
			u8returnValue=KNOB_stMainOut[1].u8MinusCounter;
			break;
		default:
			break;
		
	}
	return u8returnValue;
}
