
/*******************************************************************************
| Module Name: KEY capture and debouncing  
| File Name: KEY.c
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
| 2016.8.3         0100      Li jiaye         module template update. 
| 
| 
****************************** .FILE_HEADER_END *********************************/
#define KEY                         /* name of the module                */

/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */	
#include "ALG.h"


/* Own headerfiles */
#include "KEY_Cfg.h"
#include "KEY_Type.h"
#include "KEY_Private.h"
#include "KEY_Interface.h"
#include "KEY.h"   
#include "Rte_IoHwPortWrite.h"     

static int KEY_u16TestCnt=0;
KEY_tstCalcSt KEY_stCalcSt[KeyNum];
KEY_tstMainOut KEY_stMainOut;


void KEY_vCalcProccess(KEY_tstCalcSt *CalcInOut, KEY_tstCalcOut *ResultInOut);
void KEY_vKeyPriorityCalc(KEY_tstPriorityCalcIn *Input, KEY_tstPriorityCalcOut *Output);


/***********************************************************************************
 Function      : void KEY_vReset (void)                                     
 Description   : Reset container function of KEY                   
 Takes         : Nothing
 Return Value  : Nothing                                                     
************************************************************************************/
void KEY_vReset (void)
{
}


/***********************************************************************************
 Function      : void KEY_vInit(void)                                       
 Description   : initialize function of KEY                    
 Takes         : Nothing
 Return Value  : Nothing                                                
************************************************************************************/
void KEY_vInit (void)
{	
    int i;
    for(i=0u;i<KeyNum;i++)
    {
        KEY_stCalcSt[i].enKeyCurrStatus=KEY_enReleased;
    }
    KEY_vClrForceFlagByteAction();
    KEY_vKeyClearPhyKeyFalg();
}


/***********************************************************************************
 Function      : void KEY_vDeinit(void)                                     
 Description   : De-init function of KEY              
 Takes         : Nothing
 Return Value  : Nothing                                                                                                
************************************************************************************/
void KEY_vDeinit (void)
{
    KEY_vClrForceFlagByteAction();
}

/***********************************************************************************
 Function      : void KEY_vActive(void)                              
 Description   : Acive function of KEY 
 Takes         : Nothing
 Return Value  : Nothing                                                                                          
************************************************************************************/
void KEY_vActive(void)
{

}


/*****************************************************************************
 Function      : KEY_vMain()	                                       
 Description   : Main container function of KEY
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void KEY_vMain (void)
{
    int i=0u;
    int u8ForceKeyPressValue;

	KEY_u16TestCnt ++;

	if(KEY_u16TestCnt >=2)
	{
		KEY_u16TestCnt = 0;
		//MCU_u16PinWrite(MCU_mPinID_P8_6, 1);
	}
	else
	{
		//MCU_u16PinWrite(MCU_mPinID_P8_6, 0);
	}
	
    KEY_tenValueSts enForceKeyPressSts;
    KEY_tstCalcOut KEY_stCalcOut;
    KEY_tstPriorityCalcIn KEY_stPriorityCalcIn;
    KEY_tstPriorityCalcOut KEY_stPriorityCalcOut;  
    KEY_stCalcOut.u32KeyActionTable=0u;
    KEY_stCalcOut.u32KeyOperationTable=0u;
    KEY_stCalcOut.u32KeyBlockTable=0u;    
    for(i=0u;i<KeyNum;i++)
    {
        enForceKeyPressSts=KEY_vForceKeyPressImport(i,&u8ForceKeyPressValue);
        if(enForceKeyPressSts==KEY_nValid)
        {
             KEY_stCalcSt[i].enKeyCurrStatus=(KEY_tenKeyAction)u8ForceKeyPressValue;/*Force key press*/
        }
        else
        {
            KEY_stProperty[i].fpKeyGetStatus((int *)&KEY_stCalcSt[i].enKeyCurrStatus);
        }
        KEY_vPtsKeyPressImport(i,KEY_stCalcSt[i].enKeyCurrStatus);
        KEY_stCalcSt[i].u8KeyId=i;
        KEY_vCalcProccess(&KEY_stCalcSt[i],&KEY_stCalcOut);
    }
    /*Key priority handle*/
    KEY_stPriorityCalcIn.u32KeyActionTable=KEY_stCalcOut.u32KeyActionTable;
    KEY_stPriorityCalcIn.u32KeyOperationTable=KEY_stCalcOut.u32KeyOperationTable;
    KEY_stPriorityCalcIn.u32KeyBlockTable=KEY_stCalcOut.u32KeyBlockTable;
    KEY_vKeyPriorityCalc(&KEY_stPriorityCalcIn, &KEY_stPriorityCalcOut);
    KEY_stMainOut.u32ActionTable=KEY_stPriorityCalcOut.u32KeyActionTable;
    KEY_stMainOut.u32OperationTable=KEY_stCalcOut.u32KeyOperationTable;
    KEY_stMainOut.u32BlockTable=KEY_stCalcOut.u32KeyBlockTable;
    KEY_vMainExportAction();
    Key_u32ForceSensorADProcess();
    
}
/*****************************************************************************
 Function      : KEY_vCalcProccess()	                                       
 Description   : Calculated the pressed KEY
 Takes         : 
 Return Value  :                                                       
*****************************************************************************/
void KEY_vCalcProccess(KEY_tstCalcSt *CalcInOut, KEY_tstCalcOut *ResultInOut)
{
    if(CalcInOut->enKeyCurrStatus==KEY_enReleased)
    {
		CalcInOut->u8KeyPressingTime=0u;
		CalcInOut->u8KeyLongPressTime=0u;
		CalcInOut->u8KeyValib=False;
		CalcInOut->enKeyActionStatus=KEY_enReleased;
        CalcInOut->u16KeyBlockTmr=0u;
        ResultInOut->u32KeyBlockTable&=~((int)1<<CalcInOut->u8KeyId);
        ResultInOut->u32KeyOperationTable&=~((int)1<<CalcInOut->u8KeyId);

        if((CalcInOut->u8KeyReleaseActionPressTime>=KEY_stProperty[CalcInOut->u8KeyId].u8DebouncingTime)&&\
            (CalcInOut->u8KeyReleaseActionPressTime < KEY_stProperty[CalcInOut->u8KeyId].u8RepeatActivateTime))
        {
            if(KEY_stProperty[CalcInOut->u8KeyId].enKeyType== KEY_enReleaseAction)
            {
                CalcInOut->u8KeyValib=1;   
            }
        }
        CalcInOut->u8KeyReleaseActionPressTime=0u;
    }
    else
    {
        if(CalcInOut->enKeyActionStatus== KEY_enReleased)
        {
            if(CalcInOut->u8KeyPressingTime<0xFF)
            {
                CalcInOut->u8KeyPressingTime++;
            }
            if(CalcInOut->u8KeyPressingTime >= KEY_stProperty[CalcInOut->u8KeyId].u8DebouncingTime)
            {
            	CalcInOut->enKeyActionStatus=KEY_enPressed;
            	CalcInOut->u8KeyPressingTime=KEY_stProperty[CalcInOut->u8KeyId].u8DebouncingTime;
                CalcInOut->u8KeyReleaseActionPressTime=CalcInOut->u8KeyPressingTime;
            }
    	}
        else if(CalcInOut->enKeyActionStatus== KEY_enPressed)
        {
    		if(KEY_stProperty[CalcInOut->u8KeyId].enKeyType== KEY_enContinue)
    		{
                if(CalcInOut->u8KeyLongPressTime==0)
                {
                    CalcInOut->u8KeyValib=1;
                    CalcInOut->u8KeyLongPressTime++;
                }
    			else if(CalcInOut->u8KeyLongPressTime>=KEY_stProperty[CalcInOut->u8KeyId].u8RepeatActivateTime)/*Long pressed action =0.4second*/
    			{
    				if(CalcInOut->u8KeyPressingTime >= KEY_stProperty[CalcInOut->u8KeyId].u8RepeatActionTime)
    				{
    					CalcInOut->u8KeyPressingTime=0;
                        if(CalcInOut->u16KeyBlockTmr<KEY_stProperty[CalcInOut->u8KeyId].u16BlockTimeCfg)
                        {
    					    CalcInOut->u8KeyValib++;
                        }
    				}
    				else
    				{
    					CalcInOut->u8KeyPressingTime++;
    				}
    			}
    			else
    			{
    				CalcInOut->u8KeyLongPressTime++;
    				CalcInOut->u8KeyPressingTime++;
    			}
    		}
    		else if(KEY_stProperty[CalcInOut->u8KeyId].enKeyType== KEY_enOnece)
    		{
    			/*niose filter for key*/
    			if(CalcInOut->u8KeyPressingTime<= KEY_stProperty[CalcInOut->u8KeyId].u8DebouncingTime)
    			{
    				CalcInOut->u8KeyPressingTime++;
    				if(CalcInOut->u8KeyPressingTime >= KEY_stProperty[CalcInOut->u8KeyId].u8DebouncingTime)
    				{
    					CalcInOut->u8KeyValib=1;
    				}
    			}
                CalcInOut->u8KeyReleaseActionPressTime=0u;
    		}
            else if(KEY_stProperty[CalcInOut->u8KeyId].enKeyType== KEY_enReleaseAction)
            {
                if(CalcInOut->u8KeyReleaseActionPressTime<0xFF)
                {
                    CalcInOut->u8KeyReleaseActionPressTime++;
                }
            }
        }
        
        ResultInOut->u32KeyOperationTable|=(int)1<<CalcInOut->u8KeyId;
        if(CalcInOut->u16KeyBlockTmr<KEY_stProperty[CalcInOut->u8KeyId].u16BlockTimeCfg)
        {
            CalcInOut->u16KeyBlockTmr++;            
        }
        else
        {
            ResultInOut->u32KeyBlockTable|=(int)1<<CalcInOut->u8KeyId;
        }
    }

	if(CalcInOut->u8KeyValib>0u)
	{
		CalcInOut->u8KeyValib--;
		ResultInOut->u32KeyActionTable|=(int)1<<CalcInOut->u8KeyId;
	}
    else
    {
        ResultInOut->u32KeyActionTable&=~((int)1<<CalcInOut->u8KeyId);
    }
}
/*****************************************************************************
 Function      : KEY_vKeyPriorityCalc()	                                       
 Description   : Calculated the KEY priority
 Takes         : 
 Return Value  :                                                       
*****************************************************************************/
void KEY_vKeyPriorityCalc(KEY_tstPriorityCalcIn *Input, KEY_tstPriorityCalcOut *Output)
{
    int i,j;

    Output->u32KeyActionTable=Input->u32KeyActionTable;
    for(i=0u;i<KeyNum;i++)
    {
        if((Input->u32KeyActionTable&((int)1<<i))>0)/*check the action key*/            
        {
            for(j=0u;j<KeyNum;j++)
            {
                if(((Input->u32KeyOperationTable&((int)1<<j))>0)&&((Input->u32KeyBlockTable&((int)1<<j))==0u))
                {
                    if((KEY_stProperty[i].u8PriorityGroup)==(KEY_stProperty[j].u8PriorityGroup))/*in the same group*/
                    {
                        if((KEY_stProperty[i].u8PriorityLevel)>(KEY_stProperty[j].u8PriorityLevel))
                        {
                            Output->u32KeyActionTable&=~((int)1<<i);
                        }
                    }                    
                }
            }
        }
    }
}

/*******************************************************************************
*Function : KEY_tenValueSts KEY_enGetMainOutputExport(KEY_tstMainOut *value)
*Description : export motor struct
*takes : Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
KEY_tenValueSts KEY_enGetMainOutputExport(KEY_tstMainOut *value)
{
    KEY_tenValueSts enReturn=KEY_nValid;
    memcpy(value, &KEY_stMainOut, sizeof(KEY_tstMainOut));
    return enReturn;
}


