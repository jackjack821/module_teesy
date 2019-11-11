/***************************************************************************************************
                                        HCT PROCESS
  .File Name : HCT.c
  
  .Description : This file is used to work out a valid heatcore temperature.

----------------------------------------------------------------------------------------------------

  Version       Date          Author         Change

----------------------------------------------------------------------------------------------------
  0x0100        2016/8/23     Lv Haoguang    Create BaseCode.
***************************************************************************************************/
#define HCT_C
#define HCT_RTE
/***************************************************************************************************
                                        HEADER FILES
***************************************************************************************************/                                        
/* System-headerfiles */
#include "General.h"
#include "Rte_internal.h"
/* Foreign headerfiles */	
#include "ALG.h"

/* Own headerfiles */
#include "Hct_Type.h"
#include "Hct_Cfg.h"
#include "Hct.h" 
#include "Hct_Private.h" 
#include "Hct_Interface.h" 


/***For Normal Car*************************************************************/
HCT_tstCalcFilterFactorIn HCT_stCalcFilterFactorIn;
HCT_tstCalcFilterFactorOut HCT_stCalcFilterFactorOut;
HCT_tstFilterProcessIn HCT_stFilterProcessIn;
HCT_tstFilterProcessOut HCT_stFilterProcessOut;
/***Variables*************************************************************/
static uint16 HCT_u161SecFlg;
static uint16 HCT_u161SecTimer;
static uint16 HCT_u16FilterProcessInit;
static uint32 HCT_u32ValuePre;
HCT_tenValueSts HCT_enRawStateForHct;
HCT_tenValueSts HCT_enRawStateForOat;
static uint16 HCT_au16Array[HCT_nu16Max];
/***Functions*************************************************************/
static void HCT_vCalcFilterFactor(HCT_tstCalcFilterFactorIn *Input,HCT_tstCalcFilterFactorOut *Output);
static void HCT_vFilterProcess(HCT_tstFilterProcessIn *Input,HCT_tstFilterProcessOut *Output);
static void HCT_v1SecTimer(void);
static void HCT_vErrorCodeProcess(void);
static void HCT_vModuleInput(void);
static void HCT_vModuleOutput(void);
/*****************************************************************************
 Function      : HCT_vReset()	                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void HCT_vReset(void)
{
	HCT_au16Array[HCT_nu16SwVer] = 0x0202;

	HCT_u161SecTimer=0;
	HCT_u161SecFlg = True;

	HCT_au16Array[HCT_nu16Valid] = False;
	HCT_au16Array[HCT_nu16Value] = HCT_u16DefaultValue;
	HCT_u32ValuePre = HCT_u16DefaultValue;
	HCT_u16FilterProcessInit = True;
	HCT_au16Array[HCT_nu16ErrorCode]=0x00;
    HCT_stFilterProcessIn.u16HctValueRaw = HCT_u16DefaultValue;
    HCT_enInitValue();
}
/*****************************************************************************
 Function      : HCT_vInit()	                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void HCT_vInit(void)
{
	HCT_vReset();
}

/*****************************************************************************
 Function      : HCT_vActive()	                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void HCT_vActive(void)
{

}

/*****************************************************************************
 Function      : HCT_vDeinit()	                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void HCT_vDeinit (void)
{
	HCT_vReset();
}
/*****************************************************************************
 Function      : HCT_vMain()	                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
void HCT_vMain(void)
{
	HCT_vModuleInput();
	/***************************************************/
	if((HCT_enRawStateForHct != HCT_nInvalid)&&(HCT_enRawStateForOat != HCT_nInvalid))/*when HCT Raw Value and Oat Input are OK*/
	{
		HCT_vCalcFilterFactor(&HCT_stCalcFilterFactorIn,&HCT_stCalcFilterFactorOut);
		HCT_stFilterProcessIn.u16FilterFactor = HCT_stCalcFilterFactorOut.u16FilterFactor;
		HCT_vFilterProcess(&HCT_stFilterProcessIn,&HCT_stFilterProcessOut);
		/********************/
		HCT_vErrorCodeProcess();
		/********************/
		HCT_vModuleOutput();
	}
	HCT_v1SecTimer();
}
/*****************************************************************************
 Function      : HCT_vCalcFilterFactor()	                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/ 
static void HCT_vCalcFilterFactor(HCT_tstCalcFilterFactorIn *Input,HCT_tstCalcFilterFactorOut *Output)
{
	uint16 *pu16_1 = NULL;
    uint16 *pu16_2 = NULL;
	pu16_1 = (uint16*)&HCT_u16FilterFactor_X[0];
    pu16_2 = (uint16*)&HCT_u16FilterFactor_Y[0];
    Output->u16FilterFactor = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,Input->u16OatValue,6U);
}
/*****************************************************************************
 Function      : HCT_vFilterProcess()	                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/ 
static void HCT_vFilterProcess(HCT_tstFilterProcessIn *Input,HCT_tstFilterProcessOut *Output)
{
	uint32 *pu32_1 = NULL;
	if(HCT_u16FilterProcessInit == True)
	{
		HCT_u16FilterProcessInit = False;
		HCT_u32ValuePre = (uint32)Input->u16HctValueRaw <<16;
	}
	if (HCT_u161SecFlg == True)
	{
		pu32_1 = &HCT_u32ValuePre;
		Output->u16HctValue = ALG_u16FirstOrderFilter(pu32_1,Input->u16HctValueRaw,Input->u16FilterFactor);
	}
}
/*****************************************************************************
 Function      : HCT_v1SecTimer()	                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/ 
static void HCT_v1SecTimer(void)
{
	if(HCT_u161SecTimer>=10)
	{
		HCT_u161SecTimer = 0;
		HCT_u161SecFlg = True;
	}
	else
	{
		HCT_u161SecTimer++;
		HCT_u161SecFlg = False;
	}
}
/*****************************************************************************
 Function      : HCT_vErrorCodeProcess()	                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/ 
static void HCT_vErrorCodeProcess(void)
{
/*Judge by HCT_enRawStateForHct*/
	if(HCT_enRawStateForHct == HCT_nInvalid)
	{
		HCT_vSetBit(HCT_au16Array[HCT_nu16ErrorCode],0);
	}
	else if(HCT_enRawStateForHct == HCT_nDefault)
	{
		HCT_vSetBit(HCT_au16Array[HCT_nu16ErrorCode],1);
	}
	else if(HCT_enRawStateForHct == HCT_nValid)
	{
		HCT_vClrBit(HCT_au16Array[HCT_nu16ErrorCode],0);	
		HCT_vClrBit(HCT_au16Array[HCT_nu16ErrorCode],1);
	}
/*Judge by HCT_enRawStateForOat*/	
	if(HCT_enRawStateForOat == HCT_nInvalid)
	{
		HCT_vSetBit(HCT_au16Array[HCT_nu16ErrorCode],2);
	}
	else if(HCT_enRawStateForOat == HCT_nDefault)
	{
		HCT_vSetBit(HCT_au16Array[HCT_nu16ErrorCode],3);
	}
	else if(HCT_enRawStateForOat == HCT_nValid)
	{
		HCT_vClrBit(HCT_au16Array[HCT_nu16ErrorCode],2);	
		HCT_vClrBit(HCT_au16Array[HCT_nu16ErrorCode],3);
	}
}
/*****************************************************************************
 Function      : HCT_vModuleInput()	                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/ 
static void HCT_vModuleInput(void)
{
	/*Module Input**************************************/
	HCT_enRawStateForHct = HCT_enImportRawTemp(&HCT_stFilterProcessIn.u16HctValueRaw);
	HCT_enRawStateForOat = HCT_enImportOatTemp(&HCT_stCalcFilterFactorIn.u16OatValue);
}
/*****************************************************************************
 Function      : HCT_vModuleOutput()	                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/ 
static void HCT_vModuleOutput(void)
{
	HCT_au16Array[HCT_nu16Value]=HCT_stFilterProcessOut.u16HctValue;
	HCT_au16Array[HCT_nu16Valid]=True;
	HCT_au16Array[HCT_nu16ErrorCode]=HCT_au16Array[HCT_nu16ErrorCode];
	HCT_au16Array[HCT_nu16SwVer] = HCT_au16Array[HCT_nu16SwVer];
	/*Export if RTE is equipped!*/
	HCT_enExportAll();
}
/*****************************************************************************
 Function      : HCT_u16GetValue()	                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/ 
uint16 HCT_u16GetValue(HCT_tenu16VarNumber enIndex)
{
	if(enIndex < HCT_nu16Max)
	{
		return HCT_au16Array[enIndex];
	}
	else
	{
		return HCT_au16Array[HCT_nu16Max-1];
	}
}

/*****************************************************************************
 Function      : HCT_u8ForceIoControl_Write                                 
 Description   : Ccp control function
 Takes         : Nothing
 Return Value  : None                                                *
*****************************************************************************/
Std_ReturnType HCT_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord)
{
    return 1u;
}

