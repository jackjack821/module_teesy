/*******************************************************************************
| Module Name: Dimmer Control
| File Name: Dim.c
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
| Yang Shengli                        Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-05-18  1.00        Yang Shengli      First implementation
| 2016-06-18  2.00        Yang Shengli      module upgraded
********************************************************************************/

#define DIM                        /* name of the module                */


/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/

/* system-headerfiles */
#include "General.h"
/* foreign headerfiles */
#include "Rte_internal.h"
#include "Alg.h"
/* own headerfiles */
#include "DIM.h"
#include "DIM_Cfg.h"
#include "DIM_Private.h"
#include "DIM_Type.h"
#include "DIM_interface.h"
//#include "_RH850.h"

/*Local variable definition*/
static uint8 DIM_biFilterInit;
static uint8 DIM_u8IndicatorOnWait;
static uint8 DIM_u8InitCounter;
static uint8 DIM_u8ICTMissTmr;
static uint16 DIM_au16Array[DIM_nu16Max];
static uint32 DIM_u32BacklightPwmDutyOld;
static uint32 DIM_u32InputPwmWidth;
static DIM_tstInput DIM_stInput;
/*Local function definition*/
static void DIM_vGetInputValue(void);
static void DIM_vGetSymbolBacklightLuminace(void);
static void DIM_vGetLcdBacklightLuminace(void);
static void DIM_vDetectLumMode(void);
static void DIM_vIndicatorPwmDuty(void);
static void DIM_vProcessIndicator(uint16 indicatorInfo,uint16 indicatorCfg,uint8 group);
static void DIM_vTelltalesLum(uint8 u8Status);
static void DIM_vSetSymbolBacklightPwmDuty(uint8 u8Status);
static void DIM_vSetLcdBacklightPwmDuty(uint8 u8Status);
static void DIM_vSetTelltalePwmDuty(uint8 u8Status);
static void DIM_vInitCounterCalc(uint8 *InOutValue);
DIM_tenValueSts DIM_enU16InputValueCalc(DIM_tstU16InputAttributes *Input, uint16 *Output);
DIM_tenValueSts DIM_enU8InputValueCalc(DIM_tstU8InputAttributes *Input, uint8 *Output);
static void DIM_vInputErrorCodeHandle(uint16 *ErrorCode, uint8 ErrorMaskNum,DIM_tenValueSts InputSts);
static   uint32 L1_light_duty=600;
static   uint32 L2_light_duty=600;
static   uint32 L3_light_duty=600;
static   uint32 L4_light_duty=600;
//#define TestLight
/*****************************************************************************										  *
 Function      : DIM_vReset                                                  *
 Description   : Initialises the stepper motor channels and interrupt sources*
                 Initialises the pwm capture also                            *
 Return Value  : None                                                        *
*****************************************************************************/
void DIM_vReset(void)
{
	DIM_u16SwVersion = DIM_SwVersion;
    
    DIM_u8InitCounter = 0;
    DIM_u32BacklightPwmDutyOld = 0;
    DIM_biFilterInit = False;
    DIM_u8IndicatorOnWait = DIM_u8WaitTime;
    memset(&DIM_stInput,0,sizeof(DIM_stInput));
#ifdef DIM_TelltalesUseIoControl
    DIM_vTelltalesLum(Off);		/*Turn off TT*/
#endif
    DIM_vSetTelltalePwmDuty(Off);	/*Turn off Telltale PWM duty*/
    DIM_vSetSymbolBacklightPwmDuty(Off);	/*Turn off Backlight PWM duty*/
    DIM_vSetLcdBacklightPwmDuty(Off);	/*Turn off LCD Backlight PWM duty*/
}

/*****************************************************************************										  *
 Function      : DIM_vInit                                                	  *
 Description   : Initialises the stepper motor channels and interrupt sources*
                 Initialises the pwm capture also                            *
 Return Value  : None                                                        *
*****************************************************************************/
void DIM_vInit(void)
{
    //DIM_u8InitCounter = 0;
    //DIM_u32BacklightPwmDutyOld = 0;
    //DIM_biFilterInit = False;
    //memset(&DIM_stInput,0,sizeof(DIM_stInput));
    DIM_u8IndicatorOnWait = DIM_u8WaitTime;
    DIM_u32InputPwmWidth = 0u;
#ifdef DIM_TelltalesUseIoControl
    DIM_vTelltalesLum(Off);		/*Turn off TT*/
#endif
    DIM_vSetTelltalePwmDuty(Off);	/*Turn off Telltale PWM duty*/
    DIM_ControlGetPwmWidth(On);
}


/*****************************************************************************										  *
 Function      : DIM_vDeinit                                                 *
 Description   : Initialises the stepper motor channels and interrupt sources*
                 Initialises the pwm capture also                            *
 Return Value  : None                                                        *
*****************************************************************************/
void DIM_vDeinit(void)
{
#ifdef DIM_TelltalesUseIoControl
    DIM_vTelltalesLum(Off);		/*Turn off TT*/
#endif
    DIM_vSetLcdBacklightPwmDuty(Off);	/*Turn off LCD Backlight PWM duty*/
    DIM_vSetTelltalePwmDuty(Off);	/*Turn off Telltale PWM duty*/
    DIM_ControlGetPwmWidth(Off);
}

/*****************************************************************************											  *
 Function      : DIM_vActive                                                 *
 Description   : If the Park input is HIGH when the IGN is OFF the Kernal    *
               is forced into Active state where it performs the tasks to    *
               maintain the illumination.                                    *
               Illumination is switched off during overvoltage\undervoltage. *
 Return Value  : None                                                        *
*****************************************************************************/
void DIM_vActive(void)
{
    DIM_tenValueSts enPowInputErrorFlag = DIM_nInvalid;
	uint8 u8PowerFailStatus = 0U;
	
	/*get Low voltage/ high voltage information by function.*/
	enPowInputErrorFlag = DIM_enPowerStatusImport(&u8PowerFailStatus);
    DIM_vInputErrorCodeHandle(&DIM_au16Array[DIM_nu16ErrorCode],DIM_nPowerModule,enPowInputErrorFlag);

    if(enPowInputErrorFlag == DIM_nInvalid)
    {
        
    }
    else
    {
    	if(u8PowerFailStatus == True)
    	{/*Power fail, shut down all light*/
    		DIM_vSetSymbolBacklightPwmDuty(Off);	/*Turn off Backlight pWM duty*/
    	}
    	else
    	{
            DIM_vGetInputValue();
            DIM_vSetSymbolBacklightPwmDuty(On);
    	}
    }
#ifdef DIM_TelltalesUseIoControl
    DIM_vTelltalesLum(Off);		/*Turn off TT*/
#endif
    DIM_vSetTelltalePwmDuty(Off);	/*Turn off Telltale PWM duty*/
    DIM_vSetLcdBacklightPwmDuty(Off);	/*Turn off lcd Backlight PWM duty*/
}



void L1_Duty_light(uint32 parameter)      // 2  5
{

	if(parameter>0x64u)
		parameter=0x64u;
	L1_light_duty=parameter*10;
	
}
void L2_Duty_light(uint32 parameter)     //7    +  -
{
	if(parameter>0x64u)
		parameter=0x64u;
	L2_light_duty=parameter*10;
	
}
void L3_Duty_light(uint32 parameter)    //  3 6  +  -
{
	if(parameter>0x64u)
		parameter=0x64u;
	L3_light_duty=parameter*10;
	
}
void L4_Duty_light(uint32 parameter)    //  1  4
{
	if(parameter>0x64u)
		parameter=0x64u;
	L4_light_duty=parameter*10;
	
}
/*****************************************************************************										  *
 Function      : DIM_vMain                                                   *
 Description   : In the On state, the Backlight is .                         *
               Illumination is switched off during overvoltage\undervoltage. *
 NOTE: This part of the main code is normally called from the 100mS container*
 Return Value  : None                                                        *
*****************************************************************************/
void DIM_vMain (void)
{
		DIM_tenValueSts enPowInputErrorFlag = DIM_nInvalid;
		uint8 u8PowerFailStatus = 0U;
		MCU_u16PWGASetDuty(8,L1_light_duty);                                    // 2  5
		MCU_u16PWGASetDuty(9,L2_light_duty);                                                //7    +  -
		MCU_u16PWGASetDuty(20,L3_light_duty);                                      //  3 6  +  -
		MCU_u16PWGASetDuty(21,L4_light_duty);             //  1  4
		
		
	#if 0
	/*get Low voltage/ high voltage information by function.*/
	enPowInputErrorFlag = DIM_enPowerStatusImport(&u8PowerFailStatus);
    DIM_vInputErrorCodeHandle(&DIM_au16Array[DIM_nu16ErrorCode],DIM_nPowerModule,enPowInputErrorFlag);

	if(DIM_u8IndicatorOnWait != 0U)
	{
		DIM_u8IndicatorOnWait--;
	}
    else
    {
        if(enPowInputErrorFlag == DIM_nInvalid)
        {
            
        }
        else
        {

			//MCU_u16PWGASetDuty(8,500);
			MCU_u16PWGASetDuty(9,500);
			MCU_u16PWGASetDuty(20,100);
			MCU_u16PWGASetDuty(21,1000);
			
        	if(u8PowerFailStatus == True)
        	{/*Power fail, shut down all light*/
            #ifdef DIM_TelltalesUseIoControl
        		DIM_vTelltalesLum(Off);		/*Turn off TT*/
            #endif
                DIM_vSetTelltalePwmDuty(Off);	/*Turn off Telltale PWM duty*/
        	   DIM_vSetSymbolBacklightPwmDuty(Off);	/*Turn off Backlight pWM duty*/
                DIM_vSetLcdBacklightPwmDuty(Off);	/*Turn off lcd Backlight PWM duty*/
        	}
        	else
        	{
                DIM_vGetInputValue();
            #ifdef DIM_TelltalesUseIoControl
                DIM_vTelltalesLum(On);
            #endif
               // DIM_vSetTelltalePwmDuty(On);	/*Turn on Telltale PWM duty*/
               // DIM_vSetSymbolBacklightPwmDuty(On);   /*Turn on Backlight PWM duty*/
              //  DIM_vSetLcdBacklightPwmDuty(On);	/*Turn on lcd Backlight PWM duty*/
		//	MCU_u16PWGASetDuty(8,500);
		//	MCU_u16PWGASetDuty(9,500);
		//	MCU_u16PWGASetDuty(20,100);
		//	MCU_u16PWGASetDuty(21,1000);
        	}
        }
        DIM_vInitCounterCalc(&DIM_u8InitCounter);
	}
    DIM_vOutputUpdate();
	#endif
}

static void DIM_vGetInputValue(void)
{
    uint16 LedInfo;
    
    if(DIM_nIndicatorCfg1 != 0)
    {
        DIM_enMmiLedInfo1Import(&LedInfo);
        DIM_stInput.enIndicatorInfo1 = LedInfo;
    }
    if(DIM_nIndicatorCfg2 != 0)
    {
        DIM_enMmiLedInfo2Import(&LedInfo);
        DIM_stInput.enIndicatorInfo2 = LedInfo;
    }
    DIM_vDetectLumMode();
    DIM_vGetSymbolBacklightLuminace();
    DIM_vGetLcdBacklightLuminace();
    DIM_vIndicatorPwmDuty();
}
/*****************************************************************************									  										  
 Function:     DIM_vGetSymbolBacklightLuminace                               
 Description:  get luminace duty
 Return Value: None                                                       
*****************************************************************************/
static void DIM_vGetSymbolBacklightLuminace(void)
{
	uint8 u8BackLightingStatus;
    uint8 u8BackLightingLuminanceValidity;
    uint16 u16BackLightingLuminance;
    DIM_tenValueSts enLinAppInputErrorFlag = DIM_nInvalid;
    uint8 u8I;
	
	enLinAppInputErrorFlag |= DIM_enBacklightLuminanceImport(&u16BackLightingLuminance);
    enLinAppInputErrorFlag |= DIM_enBacklightStatusImport(&u8BackLightingStatus);
    enLinAppInputErrorFlag |= DIM_enBacklightLuminanceValidImport(&u8BackLightingLuminanceValidity);
    
    DIM_vInputErrorCodeHandle(&DIM_au16Array[DIM_nu16ErrorCode],DIM_nLinAppModule,enLinAppInputErrorFlag);
	DIM_stInput.enBacklightStatus = u8BackLightingStatus;
    DIM_stInput.enLuminaceValid = u8BackLightingLuminanceValidity;
    
    if(DIM_stInput.enBacklightStatus == Off)
    {
        u16BackLightingLuminance = DIM_nMinDuty;
    }
    else if(DIM_stInput.enLuminaceValid == 1U)
    {
        u16BackLightingLuminance = DIM_nDeFaultDuty;
    }
    else
    {
    }
    
    if(DIM_biFilterInit == False)
    {
        DIM_biFilterInit = True;
        DIM_u32BacklightPwmDutyOld = (uint32)u16BackLightingLuminance << 16U;
    }
    else
    {
        u16BackLightingLuminance = ALG_u16FirstOrderFilter(&DIM_u32BacklightPwmDutyOld,u16BackLightingLuminance,DIM_nFilterFactor);
    }
    
    for(u8I = 0;u8I < DIM_nSymbolBacklightPwmDutyMax;u8I++)
    {
        DIM_stInput.enInputSymbolBacklightPwmDuty[u8I] = u16BackLightingLuminance;
    }
}

/*****************************************************************************									  										  
 Function:     DIM_vGetLcdBacklightLuminace                               
 Description:  get luminace duty
 Return Value: None                                                       
*****************************************************************************/
static void DIM_vGetLcdBacklightLuminace(void)
{
    uint8 u8I;
    static uint16 u16LcdBackLightingLuminance;
#ifdef TestLight
    u16LcdBackLightingLuminance = 1000;
#else
	if(DIM_stInput.enLightMode == DIM_nNightMode)
	{
        u16LcdBackLightingLuminance = DIM_nNightModeDuty_TT;
    }
    else if(DIM_stInput.enLightMode == DIM_nDayMode)
    {
        u16LcdBackLightingLuminance = DIM_nDayModeDuty_TT;
    }
    else
    {
    }
#endif
    
    for(u8I = 0;u8I < DIM_nLcdBacklightPwmDutyMax;u8I++)
    {
        DIM_stInput.enInputLcdBacklightPwmDuty[u8I] = u16LcdBackLightingLuminance;
    }
}
/*****************************************************************************									  										  
 Function:     DIM_vDetectLumMode                               
 Description:  detect ILL Signal state
 Return Value: None                                                       
*****************************************************************************/
static void DIM_vDetectLumMode(void)
{
	uint8 u8State;
	
	DIM_enLuminanceModeImport(&u8State);	/*detect ILL signal state*/
	
	if(u8State == 0U)
	{
		DIM_stInput.enLightMode = DIM_nDayMode;
	}
	else if(u8State == 1U)
	{
		DIM_stInput.enLightMode = DIM_nNightMode;
	}
    else
    {
    }
#ifdef TestLight
    DIM_stInput.enLightMode = DIM_nDayMode;
#endif
    DIM_u16LumMode = DIM_stInput.enLightMode;
}

/*****************************************************************************									  										  
 Function:     DIM_vDetectLumMode                               
 Description:  detect ILL Signal state
 Return Value: None                                                       
*****************************************************************************/
static void DIM_vIndicatorPwmDuty(void)
{
    uint16 u16IndicatorInfo1;
    uint16 u16IndicatorInfo2;
    static uint16 u16IndicatorPwmDuty[DIM_nIndicatorPwmDutyMax] = {0u};
#ifdef TestLight
    u16IndicatorInfo1 = 0xFFFFu;
    u16IndicatorInfo2 = 0xFFFFu;
#else
    u16IndicatorInfo1 = DIM_stInput.enIndicatorInfo1;
    u16IndicatorInfo2 = DIM_stInput.enIndicatorInfo2;
#endif

#ifdef TestLight
    u16IndicatorPwmDuty[DIM_nIndiShcL] = 1000u;
    u16IndicatorPwmDuty[DIM_nIndiShcR] = 1000u;
    u16IndicatorPwmDuty[DIM_nIndiAc] = 1000u;
    u16IndicatorPwmDuty[DIM_nIndiFDef] = 1000u;
    u16IndicatorPwmDuty[DIM_nIndiAuto] = 1000u;
    u16IndicatorPwmDuty[DIM_nIndiRec] = 1000u;
    u16IndicatorPwmDuty[DIM_nIndiRDef] = 1000u;
    u16IndicatorPwmDuty[DIM_nIndiMaxAc] = 1000u;
    u16IndicatorPwmDuty[DIM_nIndiIon] = 1000u;
    u16IndicatorPwmDuty[DIM_nIndiDual] = 1000u;
#else
	if(DIM_stInput.enLightMode == DIM_nNightMode)
	{
        u16IndicatorPwmDuty[DIM_nIndiShcL] = DIM_nNightModeDuty_SHL;
        u16IndicatorPwmDuty[DIM_nIndiShcR] = DIM_nNightModeDuty_SHR;
        u16IndicatorPwmDuty[DIM_nIndiAc] = DIM_nNightModeDuty_AC;
        u16IndicatorPwmDuty[DIM_nIndiFDef] = DIM_nNightModeDuty_FDEF;
        u16IndicatorPwmDuty[DIM_nIndiAuto] = DIM_nNightModeDuty_AUTO;
        u16IndicatorPwmDuty[DIM_nIndiRec] = DIM_nNightModeDuty_REC;
        u16IndicatorPwmDuty[DIM_nIndiRDef] = DIM_nNightModeDuty_RDEF;
        u16IndicatorPwmDuty[DIM_nIndiMaxAc] = DIM_nNightModeDuty_MAXAC;
        u16IndicatorPwmDuty[DIM_nIndiIon] = DIM_nNightModeDuty_ION;
        u16IndicatorPwmDuty[DIM_nIndiDual] = DIM_nNightModeDuty_DUAL;
	}
	else if(DIM_stInput.enLightMode == DIM_nDayMode)
	{
        u16IndicatorPwmDuty[DIM_nIndiShcL] = DIM_nDayModeDuty_SHL;
        u16IndicatorPwmDuty[DIM_nIndiShcR] = DIM_nDayModeDuty_SHR;
        u16IndicatorPwmDuty[DIM_nIndiAc] = DIM_nDayModeDuty_AC;
        u16IndicatorPwmDuty[DIM_nIndiFDef] = DIM_nDayModeDuty_FDEF;
        u16IndicatorPwmDuty[DIM_nIndiAuto] = DIM_nDayModeDuty_AUTO;
        u16IndicatorPwmDuty[DIM_nIndiRec] = DIM_nDayModeDuty_REC;
        u16IndicatorPwmDuty[DIM_nIndiRDef] = DIM_nDayModeDuty_RDEF;
        u16IndicatorPwmDuty[DIM_nIndiMaxAc] = DIM_nDayModeDuty_MAXAC;
        u16IndicatorPwmDuty[DIM_nIndiIon] = DIM_nDayModeDuty_ION;
        u16IndicatorPwmDuty[DIM_nIndiDual] = DIM_nDayModeDuty_DUAL;
	}
    else
    {
        
    }
#endif
    if((u16IndicatorInfo1 >> DIM_nBitMmiAuto) & 0x01u)
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiAuto] = u16IndicatorPwmDuty[DIM_nIndiAuto];
    }
    else
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiAuto] = DIM_nMinDuty;
    }

    if((u16IndicatorInfo1 >> DIM_nBitMmiAc) & 0x01u)
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiAc] = u16IndicatorPwmDuty[DIM_nIndiAc];
    }
    else
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiAc] = DIM_nMinDuty;
    }

    if((u16IndicatorInfo1 >> DIM_nBitMmiRec) & 0x01u)
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiRec] = u16IndicatorPwmDuty[DIM_nIndiRec];
    }
    else
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiRec] = DIM_nMinDuty;
    }

    if((u16IndicatorInfo1 >> DIM_nBitMmiRdef) & 0x01u)
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiRDef] = u16IndicatorPwmDuty[DIM_nIndiRDef];
    }
    else
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiRDef] = DIM_nMinDuty;
    }

    if((u16IndicatorInfo1 >> DIM_nBitMmiMaxAc) & 0x01u)
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiMaxAc] = u16IndicatorPwmDuty[DIM_nIndiMaxAc];
    }
    else
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiMaxAc] = DIM_nMinDuty;
    }

    if((u16IndicatorInfo1 >> DIM_nBitMmiFdef) & 0x01u)
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiFDef] = u16IndicatorPwmDuty[DIM_nIndiFDef];
    }
    else
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiFDef] = DIM_nMinDuty;
    }

    if((u16IndicatorInfo1 >> DIM_nBitiIon) & 0x01u)
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiIon] = u16IndicatorPwmDuty[DIM_nIndiIon];
    }
    else
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiIon] = DIM_nMinDuty;
    }

    if((u16IndicatorInfo2 >> DIM_nBitMmiHSL1) & 0x01u)
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiShcL] = u16IndicatorPwmDuty[DIM_nIndiShcL];
    }
    else
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiShcL] = DIM_nMinDuty;
    }

    if((u16IndicatorInfo2 >> DIM_nBitMmiHSR1) & 0x01u)
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiShcR] = u16IndicatorPwmDuty[DIM_nIndiShcR];
    }
    else
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiShcR] = DIM_nMinDuty;
    }

    if((u16IndicatorInfo1 >> DIM_nBitMmiDual) & 0x01u)
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiDual] = u16IndicatorPwmDuty[DIM_nIndiDual];
    }
    else
    {
        DIM_stInput.enInputIndicatorPwmDuty[DIM_nIndiDual] = DIM_nMinDuty;
    }
}
static void DIM_vProcessIndicator(uint16 indicatorInfo,uint16 indicatorCfg,uint8 group)
{
    uint8 u8I;
    uint8 u8Index;
    uint8 u8Value;
    
    for(u8I = 0u; u8I < 16u;u8I++)
    {
        if(((indicatorCfg >> u8I) & 0x0001u) != 0u)
        {
            if(((indicatorInfo >> u8I) & 0x0001u) != 0u)
            {
                u8Value = 1u;/*Trun on this indicator*/
            }
            else
            {
                u8Value = 0u;/*Trun off this indicator*/
            }
            u8Index = u8I;
            DIM_enIndicatorInfoPinExport(&u8Index,&u8Value,&group);
        }
    }
}

/*****************************************************************************								  										  
 Function:     DIM_vTelltalesLum                              
 Description:  Telltales brightness control
 Return Value: None                                                       
*****************************************************************************/
static void DIM_vTelltalesLum(uint8 u8Status)
{
	uint16 u16IndicatorInfo;

	if(u8Status == On)
	{
        if(DIM_nIndicatorCfg1 != 0u)
        {
            u16IndicatorInfo = DIM_stInput.enIndicatorInfo1;
    		DIM_vProcessIndicator(u16IndicatorInfo,DIM_nIndicatorCfg1,1U);
        }
        
        if(DIM_nIndicatorCfg2 != 0u)
        {
            u16IndicatorInfo = DIM_stInput.enIndicatorInfo2;
    		DIM_vProcessIndicator(u16IndicatorInfo,DIM_nIndicatorCfg2,2U);
        }
	}
	else
	{/*Turn off all telltales*/
        if(DIM_nIndicatorCfg1 != 0u)
        {
            u16IndicatorInfo = 0x0000u;
    		DIM_vProcessIndicator(u16IndicatorInfo,DIM_nIndicatorCfg1,1U);
        }
        
        if(DIM_nIndicatorCfg2 != 0u)
        {
            u16IndicatorInfo = 0x0000u;
    		DIM_vProcessIndicator(u16IndicatorInfo,DIM_nIndicatorCfg2,2U);
        }
	}
}

/*****************************************************************************								  										  
 Function:     DIM_vSetSymbolBacklightPwmDuty                              
 Description:  PWM duty control
 Return Value: None                                                       
*****************************************************************************/
static void DIM_vSetSymbolBacklightPwmDuty(uint8 u8Status)
{
    uint8 u8I;
    DIM_tstState Dim_stState;
    
    if(u8Status == On)
    {
        for(u8I = 0;u8I < DIM_nSymbolBacklightPwmDutyMax;u8I++)
        {
            Dim_stState.enIndex = u8I;
            Dim_stState.enPwmDuty = DIM_stInput.enInputSymbolBacklightPwmDuty[u8I];
    	    DIM_enSymbolBacklightPwmDutyExport(&Dim_stState);
        }
    }
    else
    {
        for(u8I = 0;u8I < DIM_nSymbolBacklightPwmDutyMax;u8I++)
        {
            Dim_stState.enIndex = u8I;
            Dim_stState.enPwmDuty = 0u;
    	    DIM_enSymbolBacklightPwmDutyExport(&Dim_stState);
        }
    }
   
}

/*****************************************************************************								  										  
 Function:     DIM_vSetLcdBacklightPwmDuty                              
 Description:  PWM duty control
 Return Value: None                                                       
*****************************************************************************/
static void DIM_vSetLcdBacklightPwmDuty(uint8 u8Status)
{
    uint8 u8I;
    DIM_tstState Dim_stState;
    
    if(u8Status == On)
    {
        for(u8I = 0;u8I < DIM_nLcdBacklightPwmDutyMax;u8I++)
        {
            Dim_stState.enIndex = u8I;
            Dim_stState.enPwmDuty = DIM_stInput.enInputLcdBacklightPwmDuty[u8I];
    	    DIM_enLcdBacklightPwmDutyExport(&Dim_stState);
        }
    }
    else
    {
        for(u8I = 0;u8I < DIM_nSymbolBacklightPwmDutyMax;u8I++)
        {
            Dim_stState.enIndex = u8I;
            Dim_stState.enPwmDuty = 0u;
    	    DIM_enLcdBacklightPwmDutyExport(&Dim_stState);
        }
    }
    /*For diag service*/
    DIM_u16LcdPwm = Dim_stState.enPwmDuty/10;
}
/*****************************************************************************								  										  
 Function:     DIM_vSetTelltalePwmDuty                              
 Description:  PWM duty control
 Return Value: None                                                       
*****************************************************************************/
static void DIM_vSetTelltalePwmDuty(uint8 u8Status)
{
    uint8 u8I;
    DIM_tstState Dim_stState;
    
    if(u8Status == On)
    {
        for(u8I = 0;u8I < DIM_nIndicatorPwmDutyMax;u8I++)
        {
            Dim_stState.enIndex = u8I;
            Dim_stState.enPwmDuty = DIM_stInput.enInputIndicatorPwmDuty[u8I];
    	    DIM_enIndicatorPwmDutyExport(&Dim_stState);
        }
    }
    else
    {
        for(u8I = 0;u8I < DIM_nIndicatorPwmDutyMax;u8I++)
        {
            Dim_stState.enIndex = u8I;
            Dim_stState.enPwmDuty = 0u;
    	    DIM_enIndicatorPwmDutyExport(&Dim_stState);
        }
    }
   
}
/*******************************************************************************
*Function : void DIM_vInputErrorCodeHandle(uint16 *ErrorCode, uint8 ErrorMaskNum,DIM_tenValueSts InputSts)
*Description : Set or Clr the ErrorCode
*takes :
*return: Nothing
*/
static void DIM_vInputErrorCodeHandle(uint16 *ErrorCode, uint8 ErrorMaskNum,DIM_tenValueSts InputSts)
{
    if(InputSts == DIM_nValid)
    {
       (*ErrorCode) &= (~((uint16)1u << ErrorMaskNum)); 
    }
    else
    {
        (*ErrorCode) |= ((uint16)1u << ErrorMaskNum);
    }
}
/*******************************************************************************
*Function : DIM_tenValueSts DIM_enGetU8InitCounterExport(uint8 *value)
*Description : export the Init counter position
*takes :  Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DIM_tenValueSts DIM_enGetU8InitCounterExport(uint8 *value)
{
    DIM_tenValueSts enReturn = DIM_nValid;
    *value= DIM_u8InitCounter;
    return enReturn;
}
/*****************************************************************************
 Function      : void DIM_vInitCounterCalc(uint8 *InOutValue)                                       
 Description   : 
 Takes         : Nothing
 Return Value  : Nothing                                                      
*****************************************************************************/
static void DIM_vInitCounterCalc(uint8 *InOutValue)
{
    if(*InOutValue < 10)/*100ms*/
    {
        (*InOutValue)++;
    }
}
/*============================================================================
*Function : AIRD_tenValueSts DIM_enU16InputValueCalc(DIM_tstInputAttributes *Input, uint16 *Output)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DIM_tenValueSts DIM_enU16InputValueCalc(DIM_tstU16InputAttributes *Input, uint16 *Output)
{
    DIM_tenValueSts enRet;
    if(Input->u16InputValue == 0xFFFF)
    {
        if(Input->u8ErrCounter < Input->u8ErrWaitTime)
        {
            enRet = DIM_nInvalid;
        }
        else
        {
           enRet = DIM_nDefault;
           *Output = Input->u16Default;
        }
    }
    else
    {
        if((Input->u16InputValue < Input->u16MinVal)||(Input->u16InputValue > Input->u16MaxVal))
        {
          *Output = *(Input->u16LastInput);
          enRet = DIM_nLastValue;
        }
        else
        {
          *Output = Input->u16InputValue;
          enRet = DIM_nValid;
        }
    }
    *(Input->u16LastInput) = *Output;
    return enRet;
}

/*============================================================================
*Function : DIM_tenValueSts DIM_enU8InputValueCalc(DIM_tstInputAttributes *Input, uint8 *Output)
*Description : 
*takes : nothing
*return: 0:invalid  1:valid 2:default   3:last valid
*/
DIM_tenValueSts DIM_enU8InputValueCalc(DIM_tstU8InputAttributes *Input, uint8 *Output)
{
    DIM_tenValueSts enRet;
    if(Input->u8InputValue == 0xFF)
    {
        if(Input->u8ErrCounter < Input->u8ErrWaitTime)
        {
            enRet = DIM_nInvalid;
            
        }
        else
        {
           enRet = DIM_nDefault;
           *Output = Input->u8Default;
        }
    }
    else
    {
        if((Input->u8InputValue < Input->u8MinVal)||(Input->u8InputValue > Input->u8MaxVal))
        {
          *Output = *(Input->u8LastInput);
          enRet = DIM_nLastValue;
        }
        else
        {
          *Output = Input->u8InputValue;
          enRet = DIM_nValid;
        }
    }
    *(Input->u8LastInput) = *Output;
    return enRet;
}
/*****************************************************************************
 Function      : DIM_u16GetValue                                   *
 Description   : The extern model get the uint16 type variables value from     *
				 this model                                                   *
 Return Value  : uint8                                                       *
*****************************************************************************/
uint16 DIM_u16GetValue( DIM_tu16enVarNumber enIndex )
{
    uint16 u16ReturnValue;
    
	if ( enIndex < DIM_nu16Max )
	{
		u16ReturnValue = DIM_au16Array[enIndex];
	}
	else
	{
		u16ReturnValue = DIM_au16Array[DIM_nu16Max-1];
	}
    
    return u16ReturnValue;
}

void DIM_vILLInputPwmDetect(uint16 *DutyValue)
{
    uint16 u16DutyValue = 0u;
    uint16 u16PortValue = 0u;
    
    if(DIM_u8ICTMissTmr < 4u)
    {
        DIM_u8ICTMissTmr++;
        u16DutyValue=(uint16)DIM_u32InputPwmWidth;
    }
    else
    {
        DIM_ReadIllPort(&u16PortValue);
        if(u16PortValue == 0u)
        {
            u16DutyValue= 0u;/*0%*/ 
        }
        else
        {
            u16DutyValue= 1000u;/*100%*/ 
        }
    }
    if(u16DutyValue > 1000u)
    {
        u16DutyValue = 1000u;/*100%*/
    }
    DIM_u16InputPwm = u16DutyValue;
    *DutyValue=u16DutyValue;
}

void Callback_MCU_ISR_TAUD0_12(void)
{
    uint32 u32InputPwmDuty;
    
    u32InputPwmDuty = MCU_u32TAUxGetTime(MCU_mTAUD0_12);

    u32InputPwmDuty = u32InputPwmDuty/10u;/*(DIM_u32InputPwmWidth(us)/10(ms)*1000)*1000,0~1000%*/
    if(u32InputPwmDuty > 1000u)
    {
        DIM_u32InputPwmWidth = 1000u;
    }
    else
    {
        DIM_u32InputPwmWidth = u32InputPwmDuty;
    }

    DIM_u8ICTMissTmr = 0u;
}


