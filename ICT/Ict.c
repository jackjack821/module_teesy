/*******************************************************************************
| Module Name: Calculate in car temperature value
| File Name: ICT.c
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
| Ouyang Bihuan                      Desay SV Automotive Co., Ltd
| Li Jiaye                           Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2015-7-2    Rev 1.1   Ouyang Bihuan       Create the module base on ICT of GAC A28.
| 2016-09-27  0100        Li Jiaye          interface updated
********************************************************************************/

#define ICT                    /* Name of the Module                */

/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
//#include "Rte_Ict.h "
#include "Alg.h "

/* Own headerfiles */
#include "Ict_Cfg.h" 
#include "Ict.h" 
#include "Ict_Private.h" 
#include "Ict_Type.h"
#include "Ict_interface.h"

static uint8 ICT_u8IGONInitNeedFlag;
static uint8 ICT_u8ResetInitNeedFlag;
static uint8 ICT_u8SetTempChangeInitNeedFlag;

static ICT_tstMainOut ICT_stMainOut;
static uint32 ICT_u32SensorValueDamping;


 static uint8 ICT_u8StaticTimeBase;
 static uint8 ICT_u8DynamicOffsetCircleTiming;
 static uint8 ICT_u8LastMMISetTemp;/*jiaye at hainan*/
 //static uint8 ICT_au8Array[ICT_nu8Max];
 //static uint16 ICT_au16Array[ICT_nu16Max];

 static uint32 ICT_u32Filter;
// static uint32 ICT_u32DynMaxFilter;
 static int16 ICT_i16OatStaticOffset;
 //static int16 ICT_i16TempOffset;
 static uint32 ICT_u32TempDamping;

 //static uint32 ICT_u32IctDampBuffer;
 //static Bool ICT_boIctDampBufferInit;
 static uint8 ICT_u81000MsCounter;
 
 /***************************************/

static void ICT_vDamping (ICT_tstDampingIn *Input,ICT_tstDampingOut *Output);
//static int16 ICT_i16CalStaticOffset(uint8 u8OatValid, uint8 u8AirdValid, uint16 u16Ambient, uint16 u16AirdPos );
static void ICT_vCalDynamicOffset(ICT_tstCalDynamicOffsetIn *Input,ICT_tstCalDynamicOffsetOut *Output);
void ICT_vCalSensorValue(ICT_tstCalSensorValueIn *Input,ICT_tstCalSensorValueOut *Output );
void ICT_vCalc1000MsFlag(ICT_tstCalc1000MsFlagIn *Input,ICT_tstCalc1000MsFlagOut *Output);



void ICT_vCalSensorValue(ICT_tstCalSensorValueIn *Input,ICT_tstCalSensorValueOut *Output )
{
#ifdef _USE_NATS_
    Output->u16SensorValue = Input->u16SensorRawValue;

    if(Input->u8InitNeedFlag==True)
    {
        ICT_u32SensorValueDamping=Output->u16SensorValue<<16u;
    }
    
    Output->u16SensorValue=ALG_u16FirstOrderFilter (&ICT_u32SensorValueDamping,Output->u16SensorValue, 1U);
#else
    if(Input->u16SensorRawValue< 20)
    {
        ICT_stMainOut.u16ErrorCode|= ICT_nSensorSgErrorMask;
        ICT_stMainOut.u16ErrorCode&= ~ICT_nSensorSpErrorMask;
        Output->u16SensorValue=(uint16)ICT_nSensorDefault;
    }
    else if(Input->u16SensorRawValue > 1000)
    {
        ICT_stMainOut.u16ErrorCode |= ICT_nSensorSpErrorMask;
        ICT_stMainOut.u16ErrorCode &= ~ICT_nSensorSgErrorMask;
        Output->u16SensorValue=(uint16)ICT_nSensorDefault;
    }        
    else
    {
        ICT_stMainOut.u16ErrorCode &= ~ICT_nSensorSgErrorMask;
        ICT_stMainOut.u16ErrorCode &= ~ICT_nSensorSpErrorMask;
        Output->u16SensorValue=(ALG_u16CurveLookup_16_16_Limit((uint16 *)ICT_au16GroupIct1SensorValueX, (uint16 *)ICT_au16GroupIct1SensorValueY, Input->u16SensorRawValue, ICT_nSensorValue_Len));  
    }
    if(Input->u8InitNeedFlag==True)
    {
        ICT_u32SensorValueDamping=Output->u16SensorValue<<16u;
    }
    Output->u16SensorValue=ALG_u16FirstOrderFilter (&ICT_u32SensorValueDamping,Output->u16SensorValue, 4U);
#endif
    
}

void ICT_vCalStaticOffset(ICT_tstCalStaticOffsetIn *Input,ICT_tstCalStaticOffsetOut *Output )
{
    uint16 u16OatStaticOffstLookup[ICT_nAmbientTbl_Len];
    uint16 u16LookupResult;
    int16 i16OatStaticOffset;

    if((Input->u8OatValid==True)&&(Input->u8AirdValid==True))
    {
    	/* Select according to the Aird Position */
    	u16OatStaticOffstLookup[0]= (ALG_u16CurveLookup_16_16_Limit ((uint16 *)ICT_au16GroupIct2StaticOffsetTbl_X,(uint16 *)ICT_au16GroupIct2StaticOffsetTbl_Y0,Input->u16AirdPos,ICT_nStaticOffsetTbl_Len));

    	/* Select according to the Aird Position */
    	u16OatStaticOffstLookup[1]= (ALG_u16CurveLookup_16_16_Limit ((uint16 *)ICT_au16GroupIct2StaticOffsetTbl_X,(uint16 *)ICT_au16GroupIct2StaticOffsetTbl_Y1,Input->u16AirdPos,ICT_nStaticOffsetTbl_Len));

    	/* Select according to the Aird Position */
    	u16OatStaticOffstLookup[2]= (ALG_u16CurveLookup_16_16_Limit ((uint16 *)ICT_au16GroupIct2StaticOffsetTbl_X,(uint16 *)ICT_au16GroupIct2StaticOffsetTbl_Y2,Input->u16AirdPos,ICT_nStaticOffsetTbl_Len));

    	/* Select according to the Aird Position */
    	u16OatStaticOffstLookup[3]= (ALG_u16CurveLookup_16_16_Limit ((uint16 *)ICT_au16GroupIct2StaticOffsetTbl_X,(uint16 *)ICT_au16GroupIct2StaticOffsetTbl_Y3,Input->u16AirdPos,ICT_nStaticOffsetTbl_Len));

    	u16LookupResult = (ALG_u16CurveLookup_16_16_Limit ((uint16 *)ICT_au16GroupIct2StaticOffsetAmbientTbl,u16OatStaticOffstLookup,Input->u16AmbientValue,ICT_nAmbientTbl_Len));

        if(u16LookupResult > 1280)
        {
            u16LookupResult = 1280;
        }
        ICT_stMainOut.u16ErrorCode &= ~ICT_nStaticOffsetInputErrorMask;
    /*===========================================================================================*/	 
    	
    	i16OatStaticOffset = u16LookupResult - 640;
    }
    else
    {
        ICT_stMainOut.u16ErrorCode |= ICT_nStaticOffsetInputErrorMask;
        i16OatStaticOffset = 0;
    }
    Output->i16StaticOffset=i16OatStaticOffset;	
}

static void ICT_vCalDynamicOffset(ICT_tstCalDynamicOffsetIn *Input,ICT_tstCalDynamicOffsetOut *Output)
{
	uint32 *pu32_1;

	int32 i16TempDiff =0;
	uint16 u16Factor =0u;
    uint16 u16DynOffsetInit=ICT_nDynOffsetZeroPoint;
    uint16 u16MaxDiff,u16DynMax;
    
	/* Determine the curve used for temperature shift compensation
	   according to the outside ambient temperature. */
	if ((Input->u8CcsValid== True)&&(Input->u8OatValid==True))
	{
        /*- Update every ICT_nDynamicOffsetTimeCircle seconds. -*/
		if(ICT_u8DynamicOffsetCircleTiming >= ICT_nDynamicOffsetTimeCircle)   
		{
			ICT_u8DynamicOffsetCircleTiming = 0;

            ICT_stMainOut.u16ErrorCode &= ~ICT_nDynamicOffsetInputErrorMask;
            
            /*Compute the max difference temperature at different ambient.*/
            u16MaxDiff =  ALG_u16CurveLookup_16_16_Limit 
                                ((uint16*)ICT_au16GroupIct2DynamicMaxTbl_X,(uint16*)ICT_au16GroupIct2DynamicMaxTbl_Y,Input->u16OatValue,ICT_nDynamicMaxTbl_Len);
            
			u16Factor =  ALG_u16CurveLookup_16_16_Limit 
                                ((uint16*)ICT_au16GroupIct2DynamicFactorTbl_X,(uint16*)ICT_au16GroupIct2DynamicFactorTbl_Y,Input->u16OatValue,ICT_nDynamicFactorTbl_Len);
            
			i16TempDiff = (((int32)(Input->u16CcsSetTemp) - (int32)(Input->i16IctStaticValue))*(int32)u16Factor)/(int32)ICT_nDynamicFactorRes;


			if(i16TempDiff <= -(int16)u16MaxDiff)
			{
				u16DynMax  = ICT_nDynOffsetZeroPoint-u16MaxDiff;
			}
			else if(i16TempDiff >= (int16)u16MaxDiff)
			{
				u16DynMax  = ICT_nDynOffsetZeroPoint+u16MaxDiff;
			}
			else
			{
				u16DynMax  = (uint16)(i16TempDiff+ICT_nDynOffsetZeroPoint);
			}
            if(Input->u8InitNeedFlag==True)
            {
                u16DynOffsetInit = (uint16)((i16TempDiff*(int32)u16Factor)/(int32)ICT_nDynamicFactorRes)+ICT_nDynOffsetZeroPoint;
                ICT_u32Filter =((uint32)u16DynOffsetInit<<16);
            }
			pu32_1 = &ICT_u32Filter;
			Output->u16DynOffset= ALG_u16FirstOrderFilter(pu32_1,u16DynMax , 4);
			Output->i16DynOffset= (int16)((int16)Output->u16DynOffset-ICT_nDynOffsetZeroPoint);
            Output->u16MaxDiff=u16MaxDiff;
            Output->u16DynMax=u16DynMax;

		}
		else
		{
			ICT_u8DynamicOffsetCircleTiming++;
		}

	}
	else
	{
		Output->i16DynOffset=0;
        Output->u16DynOffset=0u;
	}
 
}


/* ===========================================================================
* Function   : void ICT_vStartup (void)
* Description: Startup function of ICT
* Takes      : Nothing
* Returns    : Nothing
*/
void ICT_vStartup (void)
{
	ICT_stMainOut.u16IctValue= 22*10+400;
	ICT_stMainOut.u16UndampedValue=22*10+400;
    ICT_u8ResetInitNeedFlag=True;
}


/* ===========================================================================
* Function   : void ICT_vReset (void)
* Description: Reset function of ICT
* Takes      : Nothing
* Returns    : Nothing
*/
 void ICT_vReset (void)
{
    ICT_u8ResetInitNeedFlag=True;
    ICT_stMainOut.u8ModuleValid=False;
    
	ICT_stMainOut.u16MaxDiff= 8*10;
	ICT_stMainOut.u16DynOffset= ICT_nDynOffsetZeroPoint;  //2012.2.11
	ICT_stMainOut.u16DynMax= ICT_nDynOffsetZeroPoint;

	//ICT_i16TempOffset = 0;
	ICT_u32Filter =((uint32)ICT_nDynOffsetZeroPoint<<16);  //2012.2.11
	//ICT_u32DynMaxFilter = ((uint32)ICT_nDynOffsetZeroPoint<<16);
    ICT_i16OatStaticOffset = 0;
}

/* ===========================================================================
* Function   : void ICT_vInit (void)
* Description: Init function of ICT
*              Called in Active->On container.
               Calls ICT_vReset also.
* Takes      : Nothing
* Returns    : Nothing
*/
 void ICT_vInit (void)
{
    ICT_u8IGONInitNeedFlag=True;
	//ICT_boIctDampBufferInit = True;
    ICT_stMainOut.u16SensorValue= ICT_nSensorDefault;

    ICT_stMainOut.u16ErrorCode = 0U;
    ICT_vClrForceFlagByteAction();
}
/* ===========================================================================
* Function   : void ICT_vDeinit (void)
* Description: De-init function of ICT
*              Called in On->Active container.
               Calls ICT_vReset also.
* Takes      : Nothing
* Returns    : Nothing
*/
 void ICT_vDeinit (void)
{
	if ( ICT_stMainOut.u8ModuleValid == True )
	{
		ICT_u8StaticTimeBase = 0;
	}
}

/*****************************************************************************
 AUTHOR:	   : Li Jiaye											  *
 DATE: 		   : 2015/07/22										  *
 Function      : Ict_vActive                                                *
 Description   : 
 Return Value  : None                                                        *
*****************************************************************************/
void ICT_vActive(void)
{
}

/* ===========================================================================
* Function   : void ICT_vCalc1000MsFlag(ICT_tstCalc1000MsFlagIn *Input,ICT_tstCalc1000MsFlagOut *Output)
* Description: calculate the 1second flag
* Takes      : InitNeedFlag
* Returns    : 1second flag
*/
void ICT_vCalc1000MsFlag(ICT_tstCalc1000MsFlagIn *Input,ICT_tstCalc1000MsFlagOut *Output)
{
    ICT_u81000MsCounter++;
    if(Input->u8InitNeedFlag==True)
    {
       ICT_u81000MsCounter=10u; 
    }
    Output->u81000MsFlag=False;
    if(ICT_u81000MsCounter>=10u)
    {
        ICT_u81000MsCounter=0u;
        Output->u81000MsFlag=True;
    }
}
/* ===========================================================================
* Function   : void ICT_vMain (void)
* Description: The main container function for ICT module.
*              This function is usually called every 100mS in On state.
* Takes      : Nothing
* Returns    : Nothing
*/
void ICT_vMain (void)
{
	Bool sbiSysTick1s =0;
	int16 i16Temp =0;
   	int16 i16OatStaticOffst = 0;
	uint8 u8MMISetTemp;
    uint8 u8PowValid;

    ICT_tstCalc1000MsFlagIn ICT_stCalc1000MsFlagIn;
    ICT_tstCalc1000MsFlagOut ICT_stCalc1000MsFlagOut;

    ICT_tstCalSensorValueIn ICT_stCalSensorValueIn;
    ICT_tstCalSensorValueOut ICT_stCalSensorValueOut;

    ICT_tstCalStaticOffsetIn ICT_stCalStaticOffsetIn;
    ICT_tstCalStaticOffsetOut ICT_stCalStaticOffsetOut;

    ICT_tstCalDynamicOffsetIn ICT_stCalDynamicOffsetIn;
    ICT_tstCalDynamicOffsetOut ICT_stCalDynamicOffsetOut;

    ICT_tstDampingIn ICT_stDampingIn;
    ICT_tstDampingOut ICT_stDampingOut;
	
    /*- Rest ICT DynOffset when MMI setTemp is changed. -*/
    ICT_enMmiSetTempImport(&u8MMISetTemp);
    
    if(ICT_u8LastMMISetTemp!=u8MMISetTemp)
    {
        ICT_u8LastMMISetTemp=u8MMISetTemp;
        ICT_u8SetTempChangeInitNeedFlag=True;
        ICT_u8DynamicOffsetCircleTiming = ICT_nDynamicOffsetTimeCircle; /*enable ICT calculation updates one time; jiaye at hainan*/
    }
    else
    {
    }
    ICT_enPowValidImport(&u8PowValid);
	if (u8PowValid== True)
    {	
        ICT_enSonserRawValueImport(&ICT_stCalSensorValueIn.u16SensorRawValue);	
        ICT_stCalSensorValueIn.u8InitNeedFlag=ICT_u8IGONInitNeedFlag;
        ICT_vCalSensorValue(&ICT_stCalSensorValueIn,&ICT_stCalSensorValueOut);        
        ICT_stMainOut.u16SensorValue=ICT_stCalSensorValueOut.u16SensorValue;
        ICT_stMainOut.u16SensorAdValue=ICT_stCalSensorValueIn.u16SensorRawValue;
        
    	
        if ( ICT_u8IGONInitNeedFlag == True )
        {
            ICT_stMainOut.u16UndampedValue= ICT_stMainOut.u16SensorValue;
            ICT_stMainOut.u16IctValue= ICT_stMainOut.u16SensorValue;
            ICT_stMainOut.u8ModuleValid = True;
            ICT_u8DynamicOffsetCircleTiming = ICT_nDynamicOffsetTimeCircle; /*enable ICT calculation updates one time; jiaye at hainan*/
            ICT_u8StaticTimeBase = ICT_nStaticTimeBasePar; /*enable ICT calculation updates one time; by zsc,141107*/
        }
        ICT_stCalc1000MsFlagIn.u8InitNeedFlag=ICT_u8IGONInitNeedFlag|ICT_u8SetTempChangeInitNeedFlag;
    	ICT_vCalc1000MsFlag(&ICT_stCalc1000MsFlagIn,&ICT_stCalc1000MsFlagOut);
        sbiSysTick1s=ICT_stCalc1000MsFlagOut.u81000MsFlag;
        if (sbiSysTick1s == True)
        {
            /*- Update the static offset every ICT_nStaticTimeBasePar seconds.-*/
        	if ( ICT_u8StaticTimeBase >= ICT_nStaticTimeBasePar )  
        	{
                ICT_u8StaticTimeBase = 0;

                ICT_enOatValidImport(&ICT_stCalStaticOffsetIn.u8OatValid);
                ICT_enAirdValidImport(&ICT_stCalStaticOffsetIn.u8AirdValid);
                ICT_enOatValueImport(&ICT_stCalStaticOffsetIn.u16AmbientValue);
                ICT_enAirdPosValueImport(&ICT_stCalStaticOffsetIn.u16AirdPos);
                ICT_vCalStaticOffset(&ICT_stCalStaticOffsetIn,&ICT_stCalStaticOffsetOut);
                i16OatStaticOffst =ICT_stCalStaticOffsetOut.i16StaticOffset;

                if(ICT_u8IGONInitNeedFlag == True)
                {/* Initial the static offset at once -*/
                    ICT_i16OatStaticOffset = i16OatStaticOffst;
                }
                else
                {			
                    if((ICT_i16OatStaticOffset + (int16)ICT_nOatStaticOffsetStep) < i16OatStaticOffst) 
                    {
                        ICT_i16OatStaticOffset += (int16)ICT_nOatStaticOffsetStep;
                    }
                    else if((ICT_i16OatStaticOffset-(int16)ICT_nOatStaticOffsetStep) > i16OatStaticOffst )
                    {
                        ICT_i16OatStaticOffset -= (int16)ICT_nOatStaticOffsetStep;
                    }
                    else
                    {
                        ICT_i16OatStaticOffset = i16OatStaticOffst;
                    }
                }			
        	}
            else
            {
                ICT_u8StaticTimeBase++;
            }
            /*u16InCarTemp is the original value of ICT sensor, and added the OATstaticOffset*/ 
            i16Temp = (int16)ICT_stMainOut.u16SensorValue+ICT_i16OatStaticOffset;
            ICT_stMainOut.u16StaticOffset= ICT_i16OatStaticOffset +640;
        	
            if ( i16Temp < (int16)0 )
            {
                i16Temp = (int16)0;
            }
            else
            {

            }
            ICT_stCalDynamicOffsetIn.i16IctStaticValue=i16Temp;
            ICT_stCalDynamicOffsetIn.u8InitNeedFlag=ICT_u8IGONInitNeedFlag|ICT_u8SetTempChangeInitNeedFlag;
            ICT_enCcsValidImport(&ICT_stCalDynamicOffsetIn.u8CcsValid);
            ICT_enCcsSetTempImport(&ICT_stCalDynamicOffsetIn.u16CcsSetTemp);
            ICT_enOatValidImport(&ICT_stCalDynamicOffsetIn.u8OatValid);            
            ICT_enOatValueImport(&ICT_stCalDynamicOffsetIn.u16OatValue);

            ICT_stCalDynamicOffsetOut.i16DynOffset=ICT_stMainOut.i16DynOffset;
            ICT_stCalDynamicOffsetOut.u16DynMax=ICT_stMainOut.u16DynMax;
            ICT_stCalDynamicOffsetOut.u16MaxDiff=ICT_stMainOut.u16MaxDiff;
            ICT_stCalDynamicOffsetOut.u16DynOffset=ICT_stMainOut.u16DynOffset;
            ICT_vCalDynamicOffset(&ICT_stCalDynamicOffsetIn,&ICT_stCalDynamicOffsetOut);
            ICT_stMainOut.i16DynOffset=ICT_stCalDynamicOffsetOut.i16DynOffset;
            ICT_stMainOut.u16DynMax=ICT_stCalDynamicOffsetOut.u16DynMax;
            ICT_stMainOut.u16MaxDiff=ICT_stCalDynamicOffsetOut.u16MaxDiff;
            ICT_stMainOut.u16DynOffset=ICT_stCalDynamicOffsetOut.u16DynOffset;

            
            i16Temp += (int16)ICT_stMainOut.i16DynOffset; 

            if (i16Temp <= 0)
            {
                i16Temp = 0;
            }
            else if (i16Temp >= 1600)
            {
                i16Temp = 1600;
            }
            ICT_stMainOut.u16UndampedValue=(uint16)i16Temp;

            ICT_enCcsSetTempImport(&ICT_stDampingIn.u16CcsSetTemp);
            ICT_stDampingIn.u16UnDampingIctValue=ICT_stMainOut.u16UndampedValue;
            ICT_stDampingIn.u8ResetNeedFlag=ICT_u8ResetInitNeedFlag|ICT_u8SetTempChangeInitNeedFlag;
            ICT_vDamping (&ICT_stDampingIn,&ICT_stDampingOut);
            ICT_stMainOut.u16IctValue=ICT_stDampingOut.u16IctValue;
            ICT_u8ResetInitNeedFlag=False;
            ICT_u8IGONInitNeedFlag=False;
            ICT_u8SetTempChangeInitNeedFlag=False;
        }

    }
    else
    {

    }
    ICT_vMainExportAction();
}

/* ===========================================================================
* Function   : static void ICT_vDamping (ICT_tstDampingIn *Input,ICT_tstDampingOut *Output);
* Description: The Damping function, used for damping ict value
* Takes      : Nothing
* Returns    : Nothing
*/
 static void ICT_vDamping (ICT_tstDampingIn *Input,ICT_tstDampingOut *Output)
{
    uint16 u16LastIctValue;
    
	//uint32 u32UndampedValue;
	//uint32 u32Error;
	
	uint16 u16SystemIndex =0;
	uint16 u16DampingK =0;

    if(Input->u8ResetNeedFlag==True)
    {
       ICT_u32TempDamping= (uint32)Input->u16UnDampingIctValue<<16u;
       u16DampingK=0u;
    }
    else
    {
        u16LastIctValue=ICT_u32TempDamping>>16u;
    	
    	if (u16LastIctValue >=Input->u16CcsSetTemp)
    	{
    		u16SystemIndex =u16LastIctValue-(Input->u16CcsSetTemp);
    	}
    	else
    	{
    		u16SystemIndex = Input->u16CcsSetTemp - u16LastIctValue;
    	}
        
		u16DampingK = ALG_u16CurveLookup_16_16_Limit 
                ((uint16*)ICT_au16GroupIct2DampingFactorX,(uint16*)ICT_au16GroupIct2DampingFactorY,u16SystemIndex, ICT_nDampingFactor_len);

        if(u16DampingK>8U)
        {
            u16DampingK = 8U;
        }
    }
    Output->u16IctValue= ALG_u16FirstOrderFilter (&ICT_u32TempDamping,Input->u16UnDampingIctValue, (uint8)u16DampingK);
    

}

/*******************************************************************************
*Function : ICT_tenValueSts ICT_enGetMainOutputExport(ICT_tstMainOut *value)
*Description : export motor struct
*takes : Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
ICT_tenValueSts ICT_enGetMainOutputExport(ICT_tstMainOut *value)
{
    ICT_tenValueSts enReturn=ICT_nValid;
    memcpy(value, &ICT_stMainOut, sizeof(ICT_tstMainOut));
    return enReturn;
}


/*****************************************************************************
* EOF:
******************************************************************************/


