/***************************************************************************************************
                                        VKEY PROCESS
  .File Name: VKEY.c
  
  .Description: Thie file is used to process virtual key events.

  --------------------------------------------------------------------------------------------------
  Version     Date            Author            Change

  --------------------------------------------------------------------------------------------------
  Rev 1.0     2016/02/03      Xu Xianglin     	The first version                                                 
***************************************************************************************************/    

#define VKEY_C                                   /*Name of the file*/
/***************************************************************************************************
                                        HEADER FILES
***************************************************************************************************/                                       

/* System-headerfiles */
#include "General.h"
/* Foreign headerfiles */
//#include  "RTE_Vkey.h"
#include  "Rte_internal.h"
#include  "CANAPP.h"
#include  "POW.h"

/* Own headerfiles */
#include "Vkey_Type.h"
#include "Vkey.h"
#include "Vkey_Private.h"
#include "Vkey_Cfg.h"

/***************************************************************************************************
                                        LOCAL VARIABLES
***************************************************************************************************/

static uint16  VKEY_au16Array[VKEY_nu16Max];
static uint8   VKEY_au8Array[VKEY_nu8Max];
static uint8   VKEY_u8ValidPriority[VKEY_nMaxKeyGroup];
static uint8   VKEY_boIgnitionOnInit = False;	/*ITP48, by zsc, 160430*/
static uint8   VKEY_u8IgDelayTime;/*ITP48, by zsc, 160430*/
static VKEY_stATTRIBUTE VKEY_stManage[VKEY_nMaxKeyNum]= VKEY_nAttribute;	
static uint8 VKEY_CcpForceFlag = 0U;
static uint16 VKEY_CcpControlData[VKey_nCcpForceMax] = {0U};
//static uint8 VKEY_u8Input[VKEY_nMaxKeyNum];
/***************************************************************************************************
                                    LOCAL FUNCTION PROTOTYTE
***************************************************************************************************/
static void VKEY_vGetValidPriority(void);
static void VKEY_vGetVkeyState (void);
static void VKEY_vLimitOutput(void);
static void VKEY_vUpdateOutputVariable(void);
static void VKEY_vCcpOutputForce(void);

/*************************************************************************************************** 
  Function   : VKEY_vCcpControl_Write      
   
  Description: Ccp control function for other module.
                            
  Arguments  : None
  
  Returns    : Nothing.
***************************************************************************************************/
void VKEY_vCcpControl_Write(uint32 ForceIoControlWord)
{
	VKEY_tstCcpControlInput CcpControlWord;
	CcpControlWord.CcpContronData=(uint16)ForceIoControlWord;
	CcpControlWord.CcpCommand=(uint8)(ForceIoControlWord>>16);
	CcpControlWord.CcpCommandFlag=(uint8)(ForceIoControlWord>>24);
	if(CcpControlWord.CcpCommandFlag==True)
	{
		switch(CcpControlWord.CcpCommand)
		{
			case 0:
				VKeyClrCcpForceByte();
				break;
			case 1:
				VKeySetCcpForceBit(VKey_nSetKeyPress);
				VKEY_CcpControlData[VKey_nSetKeyPress]=CcpControlWord.CcpContronData;
				break;
			case 2:
				VKeyClrCcpForceBit(VKey_nSetKeyPress);
				VKEY_CcpControlData[VKey_nSetKeyPress]=0;
				break;
			default:
				break;
		}
	}
	else
	{
		VKeyClrCcpForceByte();
	}

}


/*************************************************************************************************** 
  Function   : VKEY_vCcpOutputForce      
   
  Description: force output value.
                            
  Arguments  : None
  
  Returns    : Nothing.
***************************************************************************************************/
static void VKEY_vCcpOutputForce(void)
{	
	if(VKeyGetCcpForceBit(VKey_nSetKeyPress))
	{
		VKEY_PressedKey|=0x0001<<VKEY_CcpControlData[VKEY_PressedKey];
	}
	else
	{
	}
}


/*************************************************************************************************** 
  Function   : VKEY_vReset      
   
  Description: The reset routine for the VKEY module.
                            
  Arguments  : None
  
  Returns    : Nothing.
***************************************************************************************************/
 void VKEY_vReset (void)
 {
	uint8 u8Ctr;
    VKEY_PressedKey = 0U;      /* Init output variable  */
    VKEY_u8SwVersion = 0xA1U;
    VKEY_boIgnitionOnInit = False;
	VKEY_u8IgDelayTime=0;
    for(u8Ctr=0U;u8Ctr<VKEY_nMaxKeyNum;u8Ctr++)
    {
        VKEY_stManage[u8Ctr].u8CurrStatus = 0xffU;
        VKEY_stManage[u8Ctr].u8LastStatus = 0xffU;        
        VKEY_stManage[u8Ctr].u8PressTimer = 0xffU;
        VKEY_stManage[u8Ctr].boKeyValib = False;
    }
 }


/*************************************************************************************************** 
  Function   : VKEY_vInit      
   
  Description: The Initialisation routine for the VKEY module.
                            
  Arguments  : None
  
  Returns    : None.
***************************************************************************************************/
void VKEY_vInit (void)
{
    VKEY_vReset(); 
}


/*************************************************************************************************** 
  Function   : VKEY_vDeinit      
   
  Description: The de-initialisation routine for the VKEY module.
                            
  Arguments  : None
  
  Returns    : None.
***************************************************************************************************/
void VKEY_vDeinit (void)
{
    VKEY_vReset ();
}


void VKEY_vActive(void)
{
}

/*************************************************************************************************** 
  Function   : VKEY_vMain      
   
  Description: The main function of this module.
                            
  Arguments  : None
  
  Returns    : None.
***************************************************************************************************/
void VKEY_vMain (void)
{
    
	Bool boLowVoltage =0U;
	Bool boHighVoltage =0U;
    
    boLowVoltage = VKEY_u8GetLowPowValue();
    boHighVoltage= VKEY_u8GetHighPowValue();    

	if (VKEY_u8IgDelayTime<=15) /*150ms, by zsc,160524*/
	{
		VKEY_u8IgDelayTime++;
		return;
	}
	if((boLowVoltage == True)||(boHighVoltage == True))
	{
		VKEY_PressedKey = 0U; 
	}
    else
    {
		VKEY_vGetVkeyState();
		VKEY_vGetValidPriority();
		VKEY_vLimitOutput();
		VKEY_vUpdateOutputVariable();
    }
    VKEY_vCcpOutputForce();
}


/*************************************************************************************************** 
  Function   : VKEY_vGetRawVKEYState      
   
  Description: The function is used for getting raw VKEY state from I/O or signal.
                            
  Arguments  : None
  
  Returns    : None.
***************************************************************************************************/
static void VKEY_vGetVkeyState (void)
{
    uint8 u8VKeyId;

    VKEY_stManage[VKEY_nFLeftSetTemp].u8CurrStatus = VKEY_u8GetFLeftSetTemp();
    VKEY_stManage[VKEY_nFRightSetTemp].u8CurrStatus = VKEY_u8GetFRightSetTemp();
    //VKEY_stManage[VKEY_nAutoKey].u8CurrStatus = VKEY_u8GetAutoKey();
    VKEY_stManage[VKEY_nBlowerSpd].u8CurrStatus = VKEY_u8GetBlowerSpd();
    VKEY_stManage[VKEY_nMode].u8CurrStatus = VKEY_u8GetMode();
    //VKEY_stManage[VKEY_nAqsKey].u8CurrStatus = VKEY_u8GetAqsKey();
    //VKEY_stManage[VKEY_nAcKey].u8CurrStatus = VKEY_u8GetAcKey();
    //VKEY_stManage[VKEY_nDefKey].u8CurrStatus = VKEY_u8GetDefKey();
    //VKEY_stManage[VKEY_nRfaKey].u8CurrStatus = VKEY_u8GetRfaKey();
    //VKEY_stManage[VKEY_nOffKey].u8CurrStatus = VKEY_u8GetOffKey();
    //VKEY_stManage[VKEY_nIonKey].u8CurrStatus = VKEY_u8GetIonKey();
    VKEY_stManage[VKEY_nPM25PopupOperationSts].u8CurrStatus = VKEY_u8GetPm25PopupOperationSts();
    VKEY_stManage[VKEY_nDrvHeaReq].u8CurrStatus = VKEY_u8GetDrvHeaReq();
    VKEY_stManage[VKEY_nPassHeaReq].u8CurrStatus = VKEY_u8GetPassHeaReq();

    //VKEY_stManage[VKEY_nDualKey].u8CurrStatus = VKEY_u8GetDualKey();
    //VKEY_stManage[VKEY_nPM25Key].u8CurrStatus = VKEY_u8GetPM25Key();
    VKEY_stManage[VKEY_nPM25PopupActive].u8CurrStatus = VKEY_u8GetPM25PopupActiveKey();
    VKEY_stManage[VKEY_nAirCleanerReq].u8CurrStatus = VKEY_u8GetTboxAirCleanerReq();
    VKEY_stManage[VKEY_nTempReq].u8CurrStatus = VKEY_u8GetTboxTempReq();
    VKEY_stManage[VKEY_nAirConditionerReq].u8CurrStatus = VKEY_u8GetTboxAirConditionerReq();

	/*ITP48, Ig from on to off error,by zsc, 160430*/
	if (VKEY_boIgnitionOnInit == False)	
	{
		VKEY_boIgnitionOnInit=True;
	    for(uint8 u8VKeyId=0U;u8VKeyId<VKEY_nMaxKeyNum;u8VKeyId++)
    	{
	        VKEY_stManage[u8VKeyId].u8LastStatus= VKEY_stManage[u8VKeyId].u8CurrStatus;
    	}
		return;
	}
    VKEY_RawKey = 0U;
    for(u8VKeyId=0U; u8VKeyId<VKEY_nMaxKeyNum; u8VKeyId++)
    {
        if((VKEY_stManage[u8VKeyId].u8CurrStatus >= VKEY_stManage[u8VKeyId].u8MinValidValue)&&\
          (VKEY_stManage[u8VKeyId].u8CurrStatus <= VKEY_stManage[u8VKeyId].u8MaxValidValue))
        {
            if(VKEY_stManage[u8VKeyId].u8CurrStatus != VKEY_stManage[u8VKeyId].u8LastStatus)
            {
                VKEY_stManage[u8VKeyId].u8PressTimer = 1U;
            }
            else
            {            
                if(VKEY_stManage[u8VKeyId].u8PressTimer < 0xffU)
                {
                    VKEY_stManage[u8VKeyId].u8PressTimer++;
                }
            }
        }
        else
        {
            VKEY_stManage[u8VKeyId].u8PressTimer = 0xffU;
        }
        VKEY_stManage[u8VKeyId].u8LastStatus = VKEY_stManage[u8VKeyId].u8CurrStatus;


        if(VKEY_stManage[u8VKeyId].u8PressTimer == VKEY_stManage[u8VKeyId].u8ResponseTime)
        {
            if(((VKEY_stManage[u8VKeyId].u8Attr == 0U) && (VKEY_stManage[u8VKeyId].u8CurrStatus != 0U))\
                || (VKEY_stManage[u8VKeyId].u8Attr == 1U))
            {
                VKEY_stManage[u8VKeyId].boKeyValib = True;
            }
            else
            {
                VKEY_stManage[u8VKeyId].boKeyValib = False;
            }
        }
        else
        {
            VKEY_stManage[u8VKeyId].boKeyValib = False;
        }    
    }
}


/*************************************************************************************************** 
  Function   : VKEY_vGetValidPriority      
   
  Description: The function is used for Get valid u8Priority.
                            
  Arguments  : None
  
  Returns    : None.
***************************************************************************************************/
static void  VKEY_vGetValidPriority(void)
{
    uint8 u8Ctr = 0U, u8GroupTemporary = 0U;
    for(u8Ctr=0U;u8Ctr<VKEY_nMaxKeyGroup;u8Ctr++)
    {
        VKEY_u8ValidPriority[u8Ctr]= 100U;
    }    
    for(u8Ctr=0U;u8Ctr<VKEY_nMaxKeyNum;u8Ctr++)
    {
        if(VKEY_stManage[u8Ctr].boKeyValib == True)
        {
            /*The smaller the variable is ,the higher u8Priority.*/
            if(VKEY_stManage[u8Ctr].u8Group<VKEY_nMaxKeyGroup)
            {
                u8GroupTemporary = VKEY_stManage[u8Ctr].u8Group;
                if(VKEY_stManage[u8Ctr].u8Priority<VKEY_u8ValidPriority[u8GroupTemporary])
                {
                    VKEY_u8ValidPriority[u8GroupTemporary] = VKEY_stManage[u8Ctr].u8Priority;
                }
            }
        }
    }
}



/*************************************************************************************************** 
  Function   : VKEY_vLimitOutput      
   
  Description: The function is used for limit the output VKEY flag with blocked flag,Priority.
                            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/
static void VKEY_vLimitOutput(void)
{   uint8 u8Ctr=0U, u8GroupTemporary=0U;
  	
	for(u8Ctr=0U;u8Ctr<VKEY_nMaxKeyNum;u8Ctr++)
	{
        if(VKEY_stManage[u8Ctr].boKeyValib == True) /*Priority limit*/
        {
            if(VKEY_stManage[u8Ctr].u8Group<VKEY_nMaxKeyGroup)
            {
                u8GroupTemporary = VKEY_stManage[u8Ctr].u8Group;
                if(VKEY_stManage[u8Ctr].u8Priority != VKEY_u8ValidPriority[u8GroupTemporary])
                {
                    VKEY_stManage[u8Ctr].boKeyValib = False;
                }     
            }
            else
            {
                VKEY_stManage[u8Ctr].boKeyValib = False;
            }
 
        }
	}
}



/*************************************************************************************************** 
  Function   : VKEY_vUpdateOutputVariable      
   
  Description: The function is used for Getting the valid VKEY flag.
                            
  Arguments  : None
  
  Returns    : None
***************************************************************************************************/
static void VKEY_vUpdateOutputVariable(void)
{
    uint8 u8Ctr;

    VKEY_PressedKey=0U;
    VKEY_ErrorCode=0U;
	for (u8Ctr=0U; u8Ctr<VKEY_nMaxKeyNum; u8Ctr++)
	{
        if (VKEY_stManage[u8Ctr].boKeyValib == True )
        {
            VKEY_PressedKey |= (uint16)((uint32)1U<<u8Ctr);
            VKEY_stManage[u8Ctr].boKeyValib = False;
            VKEY_au8Array[u8Ctr] = VKEY_stManage[u8Ctr].u8CurrStatus;
        }
	}
  
}


/*************************************************************************************************** 
  Function   : VKEY_u8GetValue      
   
  Description: supply variable for other modules.
                            
  Arguments  : None
  
  Returns    : variable other module want to get.
***************************************************************************************************/
uint8 VKEY_u8GetValue(VKEY_tenu8VarNum Num)
{
    uint8 u8ReturnValue;
	if(Num<VKEY_nu8Max)
	{
        u8ReturnValue = (uint8)VKEY_au8Array[Num];
	}
	else
	{
        u8ReturnValue = (uint8)VKEY_au8Array[VKEY_nu8SwVersion];
	}
    return u8ReturnValue;
}


/*************************************************************************************************** 
  Function   : VKEY_u16GetValue      
   
  Description: supply variable for other modules.
                            
  Arguments  : None
  
  Returns    : variable other module want to get.
***************************************************************************************************/
uint16 VKEY_u16GetValue(VKEY_tenu16VarNum Num)
{
    uint16 u16ReturnValue;
	if(Num<VKEY_nu16Max)
	{
        u16ReturnValue = (uint16)VKEY_au16Array[Num];
	}
	else
	{
        u16ReturnValue = (uint16)VKEY_au16Array[VKEY_nu16PressedKey];
	}
    return u16ReturnValue;
}


Std_ReturnType VKEY_u8ForceIoControl_Write(/*IN*/UInt32 ForceIoControlWord)
{
    return 1u;
}


