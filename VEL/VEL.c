/*******************************************************************************
| Module Name: Calculate the Blowout and Temp offset according to the VELocity
| File Name: VEL.c
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
| Sui Yanchun                        Desay SV Automotive Co., Ltd
| Zhang Shuncong                     Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2013-04-09  1.00        Sui Yanchun       First implementation
| 2015-08-06  2.00        Zhang Shuncong    Add RTE ,Copyright and cfg
| 2016-09-21  0100        Li Jiaye          interface updated
********************************************************************************/

#define 	VEL      /* Name of the Module */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/

/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */

#include "ALG.h" 

/* Own headerfiles */
#include "VEL_Cfg.h" 
#include "VEL.h" 
#include "VEL_Private.h" 
#include "VEL_interface.h"
#include "VEL_Type.h"

/*Local variable definition*/
static Bool     VEL_biNeedFilterInit;           /* initial when reset*/
static Bool     VEL_biSysTick1s;                 /* Timer conter tick every second */
static uint8    VEL_u8SysTimeConter;       /* Sys Time conter, increase every 100ms*/
static uint16   VEL_u8SignlInValidCount; /*  speed signal invalid time */
static Vel_tstMainOut Vel_stMainOut;


/*Local function definition*/
static void VEL_vPerformDamping(Vel_tstDampingIn *Input,Vel_tstDampingOut *Output);
static void VEL_vInputValueProcess(Vel_tstInputValueProcessIn *Input, Vel_tstInputValueProcessOut *Output);
static uint16 VEL_u16ValueLinearFilter(uint16 u16RawValue, uint16 u16PreValue, uint8 u8FilterType);
static uint16 VEL_u16OffsetLinearFilter(uint16 u16RawValue, uint16 u16PreValue,uint8 u8Step);
static uint16 VEL_u16CalOatBlowerOffset (Vel_tstCalOatBlowerOffsetIn *Input);	
static uint16 VEL_u16CalOatTempOffset (Vel_tstCalOatTempOffsetIn *Input);


/* ===========================================================================
* Function   : void VEL_vReset (void)
* Description: This is the reset function for the VEL module.
* Takes      : None
* Returns    : None
*/
 void VEL_vReset(void)
{
    Vel_stMainOut.u8ModuleValid= False;

    Vel_stMainOut.u16Velocity = VEL_nDefaultValue;
    Vel_stMainOut.u16RfaVelValue = VEL_nDefaultValue;
    Vel_stMainOut.u16OatVelValue = VEL_nDefaultValue;
    Vel_stMainOut.u16TempOffset= VEL_nDefaultTempOffset;	
    Vel_stMainOut.u16BlowerOffset = VEL_nDefaultBlowerOffset;			

    VEL_biNeedFilterInit = True;
    VEL_u8SignlInValidCount = VEL_nu8SignalInvaidTime;
    VEL_biSysTick1s=False;              
    VEL_u8SysTimeConter=VEL_nSysTimeCont1s-1;  
}

/* ===========================================================================
* Function   : void VEL_vInit (void)
* Description: initialise VELocity data when entering ON mode
* Takes      : None
* Returns    : None
*/
 void VEL_vInit( void)
{
	VEL_vReset();
    VEL_vClrForceFlagByteAction();
}

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/07/22										  *
 Function      : VEL_vActive                                                   *
 Description   : 
 Return Value  : None                                                        *
*****************************************************************************/
void VEL_vActive(void)
{
    /*nothing to do*/
}


/* ===========================================================================
* Function   : void VEL_vMain (void)
* Description: Main container function of VEL
* Takes      : Nothing
* Returns    : Nothing
*/
void VEL_vMain(void)
{
	uint16  u16TempOffset = 0;
	uint16  u16BlwrOffset = 0;
	Bool    biOatValid = True; 

    Vel_tstInputValueProcessIn Vel_stInputValueProcessIn;
    Vel_tstInputValueProcessOut Vel_stInputValueProcessOut;

    Vel_tstDampingIn Vel_stDampingIn;
    Vel_tstDampingOut Vel_stDampingOut;

    Vel_tstCalOatTempOffsetIn Vel_stCalOatTempOffsetIn;
    
    Vel_tstCalOatBlowerOffsetIn Vel_stCalOatBlowerOffsetIn;
	
    /*In the process of integration,open up the following*/
    VEL_enOatValidImport(&biOatValid);
	if (biOatValid == True)
	{
        /* Prepare the system 1s flag, add by ZRM */           
        VEL_u8SysTimeConter++;  
        if(VEL_u8SysTimeConter<VEL_nSysTimeCont1s)
        {
            VEL_biSysTick1s=False;          
        }
        else
        {
            VEL_u8SysTimeConter=0;
            VEL_biSysTick1s=True;
        }
        VEL_enVeIocityInvalidImport(&Vel_stInputValueProcessIn.u8VelocityInvalidFlag);
        VEL_enVeIocityValueImport(&Vel_stInputValueProcessIn.u16VeIocityValue);
	    VEL_vInputValueProcess(&Vel_stInputValueProcessIn,&Vel_stInputValueProcessOut);

        Vel_stDampingIn.u16VeIocityValue=Vel_stInputValueProcessOut.u16VeIocityValue;
	    VEL_vPerformDamping(&Vel_stDampingIn,&Vel_stDampingOut);
        
		if (VEL_biSysTick1s == True)
		{		
			/* Calculate Blowout Temperature Offset */
            Vel_stCalOatTempOffsetIn.u16Velocity=Vel_stDampingOut.u16RfaVelValue;
            VEL_enOatValueImport(&Vel_stCalOatTempOffsetIn.u16OatValue);
			u16TempOffset = VEL_u16CalOatTempOffset(&Vel_stCalOatTempOffsetIn);

			/* Calculate Blower Offset */
            Vel_stCalOatBlowerOffsetIn.u16Velocity=Vel_stDampingOut.u16RfaVelValue;
            VEL_enOatValueImport(&Vel_stCalOatBlowerOffsetIn.u16OatValue);
			u16BlwrOffset = VEL_u16CalOatBlowerOffset(&Vel_stCalOatBlowerOffsetIn);

            /* To prevent over- / underflow, the offset values are limited  */
			VEL_RangeCheck(u16TempOffset, VEL_nMinTempOffset, VEL_nMaxTempOffset);
            VEL_RangeCheck(u16BlwrOffset, VEL_nMinBlowerOffset, VEL_nMaxBlowerOffset);

			/* Perform a simple damping, limit the change speed to 1 step / sec */
            Vel_stMainOut.u16TempOffset = VEL_u16OffsetLinearFilter(u16TempOffset,Vel_stMainOut.u16TempOffset,VEL_u8OffsetStep);				
            Vel_stMainOut.u16BlowerOffset = VEL_u16OffsetLinearFilter(u16BlwrOffset,Vel_stMainOut.u16BlowerOffset,VEL_u8OffsetStep);
		}
        else
        {
            /*nothing to do*/
        }
        Vel_stMainOut.u8ModuleValid = True;
    }
    else
    {
        Vel_stMainOut.u8ModuleValid = False;
    }
    
    Vel_stMainOut.u16OatVelValue=Vel_stDampingOut.u16OatVelValue;
    Vel_stMainOut.u16RfaVelValue=Vel_stDampingOut.u16RfaVelValue;
    Vel_stMainOut.u16Velocity=Vel_stDampingOut.u16Velocity;

    VEL_vMainExportAction();
}

/* ===========================================================================
* Function   : void VEL_vDeinit (void)
* Description: This is On the ignition->off transition function for the VEL module.
* Takes      : None
* Returns    : None
*/
 void VEL_vDeinit( void)
{
	/*Nothing to do*/
}


/*****************************************************************************
 Function      : VEL_vInputValueProcess
 Description   : Read AD port(raw value) and convert vol to W/m2,
 Return Value  : void
*****************************************************************************/
static void VEL_vInputValueProcess(Vel_tstInputValueProcessIn *Input, Vel_tstInputValueProcessOut *Output)
{
	if ((Input->u8VelocityInvalidFlag)== VEL_nValid)  /*0--Invalid and error, 1---valid*/
	{			
		Output->u16VeIocityValue =Input->u16VeIocityValue;
		VEL_u8SignlInValidCount = 0;
	}
	else    
	{
	    /*velocity is invalid , use default value*/
		VEL_u8SignlInValidCount++;
		if ( VEL_u8SignlInValidCount >= VEL_nu8SignalInvaidTime )
		{
			VEL_u8SignlInValidCount = VEL_nu8SignalInvaidTime;
			Output->u16VeIocityValue = VEL_nDefaultValue; 
		}
		else
		{
			/*nothing to do*/
		}
	}
    
    VEL_RangeCheck(Output->u16VeIocityValue, VEL_nMinValue, VEL_nMaxValue);
}



/*******************************************************************************
  Function   : VEL_vPerformDamping                                                                                                                                                                                                                                     
                           
  Description: This function is used to damp the VELload value.
  
  Arguments  : None
  
  Returns    : None 
*******************************************************************************/
static void VEL_vPerformDamping(Vel_tstDampingIn *Input,Vel_tstDampingOut *Output)
{
    static uint16 u16Velocity;
    static uint16 u16RfaVelValue;
    static uint16 u16OatVelValue;

    if(VEL_biNeedFilterInit == True)
	{
	    VEL_biNeedFilterInit = False;
        
		u16Velocity = Input->u16VeIocityValue;
        u16RfaVelValue = Input->u16VeIocityValue;
        u16OatVelValue = Input->u16VeIocityValue;
	}
	else
	{	
		if (VEL_biSysTick1s== True)
		{
			u16Velocity = VEL_u16ValueLinearFilter(Input->u16VeIocityValue,u16Velocity,VEL_nFilterFast);

            u16RfaVelValue = VEL_u16ValueLinearFilter(Input->u16VeIocityValue,u16RfaVelValue,VEL_nFilterSlow);

            u16OatVelValue = VEL_u16ValueLinearFilter(Input->u16VeIocityValue,u16OatVelValue,VEL_nFilterMid);

            /* To prevent over- / underflow, the values are limited  */
	        VEL_RangeCheck(u16Velocity, VEL_nMinValue, VEL_nMaxValue);
            VEL_RangeCheck(u16RfaVelValue, VEL_nMinValue, VEL_nMaxValue);
            VEL_RangeCheck(u16OatVelValue, VEL_nMinValue, VEL_nMaxValue);
        }
        else
        {
            /*nothing to do*/
        }
    }
    Output->u16OatVelValue=u16OatVelValue;
    Output->u16RfaVelValue=u16RfaVelValue;
    Output->u16Velocity=u16Velocity;
}

/* ===========================================================================
* Function   :  static uint16 VEL_u16ValueLinearFilter(uint16 u16VELRawValue, uint16 *u16PtrAddr)	
* Description:  This function impliments a second order low pass filter   */
/*              with guaranteed no loss of resolution. 
* Takes      :  u8VELRawValue - Raw solar indensity from sensor
                u16PtrAddr -  old VEL Value
* Returns   :   The 16-bit output of the filter
*/
static uint16 VEL_u16ValueLinearFilter(uint16 u16RawValue, uint16 u16PreValue, uint8 u8FilterType)
{
	uint8 u8IncreSpeed=VEL_u8SlowIncrement;
	uint8 u8DecreSpeed=VEL_u8SlowDecrement;

	if (u8FilterType == VEL_nFilterFast) /*fast type*/
	{
		/*Is fast filter type*/
		u8IncreSpeed=VEL_u8FastIncrement;
		u8DecreSpeed=VEL_u8FastDecrement;
	}

	if (u8FilterType == VEL_nFilterMid) /*Mid type*/
	{
		/*Is fast filter type*/
		u8IncreSpeed=VEL_u8SlowIncrement;
		u8DecreSpeed=VEL_u8FastDecrement;
	}
	
	if ( u16RawValue > u16PreValue )
	{
		if ( (u16RawValue - u16PreValue) > u8IncreSpeed )
		{
			u16PreValue += u8IncreSpeed;
		}
		else
		{
			u16PreValue = u16RawValue;
		}
	}
	else if ( u16RawValue < u16PreValue )
	{
		if ( (u16PreValue -u16RawValue ) > u8DecreSpeed )
		{
			u16PreValue -= u8DecreSpeed;
		}
		else
		{
			u16PreValue = u16RawValue;
		}
	}

	return u16PreValue;
}



/* ===========================================================================
* Function   :  static uint16 VEL_u16OffsetLinearFilter(uint16 u16RawValue, uint16 u16PreValue,uint8 u8Step)	
* Description:  This function impliments a second order low pass filter   */
/*              with guaranteed no loss of resolution. 
* Takes      :  u16RawValue - Raw solar indensity from sensor
                u16PtrAddr -  old VEL Value
                u8Step - step
* Returns   :   The 16-bit output of the filter
*/
static uint16 VEL_u16OffsetLinearFilter(uint16 u16RawValue, uint16 u16PreValue,uint8 u8Step)
{	
	if ( u16RawValue > u16PreValue )
	{
		if ( (u16RawValue - u16PreValue) > u8Step )
		{
			u16PreValue += u8Step;
		}
		else
		{
			u16PreValue = u16RawValue;
		}
	}
	else if ( u16RawValue < u16PreValue )
	{
		if ( (u16PreValue -u16RawValue ) > u8Step )
		{
			u16PreValue -= u8Step;
		}
		else
		{
			u16PreValue = u16RawValue;
		}
	}

	return u16PreValue;
}


/* ===========================================================================
* Function   :  static uint16 VEL_u8CalVELOatTempOffset (uint16 u16InputValue)	
* Description:  Calculate Blowout Temperature Offset 
* Takes      :  u16InputValue - the input vehicle speed value
* Returns   :   The 16-bit output of Blowout Temperature Offset 
*/
 static uint16 VEL_u16CalOatTempOffset(Vel_tstCalOatTempOffsetIn *Input)		
{
	uint16 *pu16_1 = NULL;
	uint16 *pu16_2 = NULL;
	uint16 u16TempOffset   = 0;	
	uint16 au16Offsets[2];	

	if((Input->u16OatValue)<=VEL_au16Group2TempOffsetAmbientTbl[0])
	{	/* Select the first curve for searching the value.*/
		pu16_1 = (uint16 *)VEL_au16Group2TempOffsetTbl_X;
		pu16_2 = (uint16 *)VEL_au16Group2TempOffsetTbl_Y0;
		u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nTempOffsetTbl_Len);
	}
	else if ((Input->u16OatValue)<=VEL_au16Group2TempOffsetAmbientTbl[1])
	{	/* Select the first & second curves for generating the value, then search it for the value.*/
		pu16_1 = (uint16 *)VEL_au16Group2TempOffsetTbl_X;
		pu16_2 = (uint16 *)VEL_au16Group2TempOffsetTbl_Y0;
		au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nTempOffsetTbl_Len);

		pu16_2 = (uint16 *)VEL_au16Group2TempOffsetTbl_Y1;
		au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nTempOffsetTbl_Len);
		pu16_1 = (uint16 *)VEL_au16Group2TempOffsetAmbientTbl;
		pu16_2 = &au16Offsets[0];
		u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,(Input->u16OatValue), 2);		
	}
	
	else if ((Input->u16OatValue)<=VEL_au16Group2TempOffsetAmbientTbl[2])
	{	/* Select the second & third curves for generating the value, then search it for the value.*/
		pu16_1 = (uint16 *)VEL_au16Group2TempOffsetTbl_X;
		pu16_2 = (uint16 *)VEL_au16Group2TempOffsetTbl_Y1;
		au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nTempOffsetTbl_Len);

		pu16_2 = (uint16 *)VEL_au16Group2TempOffsetTbl_Y2;
		au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nTempOffsetTbl_Len);
		pu16_1 = (uint16 *)VEL_au16Group2TempOffsetAmbientTbl+1;
		pu16_2 = (uint16 *)au16Offsets;
		u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,(Input->u16OatValue), 2);		
	}
	else if ((Input->u16OatValue)<VEL_au16Group2TempOffsetAmbientTbl[3])
	{	/* Select the third & fourth curves for generating the value, then search it for the value.*/
		pu16_1 = (uint16 *)VEL_au16Group2TempOffsetTbl_X;
		pu16_2 = (uint16 *)VEL_au16Group2TempOffsetTbl_Y2;
		au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nTempOffsetTbl_Len);

		pu16_2 = (uint16 *)VEL_au16Group2TempOffsetTbl_Y3;
		au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nTempOffsetTbl_Len);
		pu16_1 = (uint16 *)VEL_au16Group2TempOffsetAmbientTbl+2;
		pu16_2 = (uint16 *)au16Offsets;
		u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,(Input->u16OatValue), 2);		
	}	

	else
	{	/* Select the last curve for searching the value.*/
		pu16_1 = (uint16 *)VEL_au16Group2TempOffsetTbl_X;
		pu16_2 = (uint16 *)VEL_au16Group2TempOffsetTbl_Y3;
		u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nTempOffsetTbl_Len);
	}
	return(u16TempOffset);

}

/* ===========================================================================
* Function   :     static uint16 VEL_u16CalOatBlowerOffset (Vel_tstCalOatBlowerOffsetIn *Input)
* Description:  Calculate Blower Offset
* Takes      :   u16InputValue - the input vehicle speed value
* Returns   :   The 16-bit output of Blower speed Offset 
*/
 static uint16 VEL_u16CalOatBlowerOffset (Vel_tstCalOatBlowerOffsetIn *Input)		
{
	uint16 *pu16_1 = NULL;
	uint16 *pu16_2 = NULL;
	uint16 u16BlowerSpeedOffset   = 0;
	uint16 au16Offsets[2];
	
	if((Input->u16OatValue)<=VEL_au16Group3BlowerOffsetAmbientTbl[0])
	{	/* Select the first curve for searching the value.*/
		pu16_1 = (uint16 *)VEL_au16Group3BlowerOffsetTbl_X;
		pu16_2 = (uint16 *)VEL_au16Group3BlowerOffsetTbl_Y0;
		u16BlowerSpeedOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nBlowerOffsetTbl_Len);
	}
	else if ((Input->u16OatValue)<=VEL_au16Group3BlowerOffsetAmbientTbl[1])
	{	/* Select the first & second curves for generating the value, then search it for the value.*/
		pu16_1 = (uint16 *)VEL_au16Group3BlowerOffsetTbl_X;
		pu16_2 = (uint16 *)VEL_au16Group3BlowerOffsetTbl_Y0;
		au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,Input->u16Velocity,VEL_nBlowerOffsetTbl_Len);

		pu16_2 = (uint16 *)VEL_au16Group3BlowerOffsetTbl_Y1;
		au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nBlowerOffsetTbl_Len);
		pu16_1 = (uint16 *)VEL_au16Group3BlowerOffsetAmbientTbl;
		pu16_2 = (uint16 *)au16Offsets;
		u16BlowerSpeedOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,(Input->u16OatValue), 2);		
	}
	
	else if ((Input->u16OatValue)<=VEL_au16Group3BlowerOffsetAmbientTbl[2])
	{	/* Select the second & third curves for generating the value, then search it for the value.*/
		pu16_1 = (uint16 *)VEL_au16Group3BlowerOffsetTbl_X;
		pu16_2 = (uint16 *)VEL_au16Group3BlowerOffsetTbl_Y1;
		au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nBlowerOffsetTbl_Len);

		pu16_2 = (uint16 *)VEL_au16Group3BlowerOffsetTbl_Y2;
		au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nBlowerOffsetTbl_Len);
		pu16_1 = (uint16 *)VEL_au16Group3BlowerOffsetAmbientTbl+1;
		pu16_2 = (uint16 *)au16Offsets;
		u16BlowerSpeedOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,(Input->u16OatValue), 2);		
	}
	else if ((Input->u16OatValue)<VEL_au16Group3BlowerOffsetAmbientTbl[3])
	{	/* Select the third & fourth curves for generating the value, then search it for the value.*/
		pu16_1 = (uint16 *)VEL_au16Group3BlowerOffsetTbl_X;
		pu16_2 = (uint16 *)VEL_au16Group3BlowerOffsetTbl_Y2;
		au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nBlowerOffsetTbl_Len);

		pu16_2 = (uint16 *)VEL_au16Group3BlowerOffsetTbl_Y3;
		au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nBlowerOffsetTbl_Len);
		pu16_1 = (uint16 *)VEL_au16Group3BlowerOffsetAmbientTbl+2;
		pu16_2 = (uint16 *)au16Offsets;
		u16BlowerSpeedOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,(Input->u16OatValue), 2);		
	}	
	else
	{	/* Select the last curve for searching the value.*/
		pu16_1 = (uint16 *)VEL_au16Group3BlowerOffsetTbl_X;
		pu16_2 = (uint16 *)VEL_au16Group3BlowerOffsetTbl_Y3;
		u16BlowerSpeedOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16Velocity,VEL_nBlowerOffsetTbl_Len);
	}
	
	return u16BlowerSpeedOffset;	

}



//#ifndef VEL_UseRTE
/*****************************************************************************
 Function      : VEL_u16GetValue                                              *
 Description   : The extern model get the uint16 type variable value from this model    
 Return Value  : uint16 value                                                 *
*****************************************************************************/
uint16 VEL_u16GetValue( VEL_tenu16VarNumber enIndex )
{
    uint16 u16Return=0;
    switch(enIndex)
    {
        case VEL_nu16SwVersion:
            u16Return=VEL_SwVersion;
            break;
        case VEL_nu16Velocity:
            u16Return=Vel_stMainOut.u16Velocity;
            break;
        case VEL_nu16RfaValue:
            u16Return=Vel_stMainOut.u16RfaVelValue;
            break;
        case VEL_nu16OatValue:
            u16Return=Vel_stMainOut.u16OatVelValue;
            break;
        case VEL_nu16BlowerOffset:
            u16Return=Vel_stMainOut.u16BlowerOffset;
            break;
        case VEL_nu16TempOffset:
            u16Return=Vel_stMainOut.u16TempOffset;
            break;
        case VEL_nu16ErrCode:
            break;
        default:
            break;
    }
    return u16Return;
}

/*****************************************************************************
 Function      : VEL_u8GetValue                                              
 Description   : The extern model get the uint8 type variable value from this model   
 Return Value  : uint8 value                                                 
*****************************************************************************/
uint8 VEL_u8GetValue( VEL_tenu8VarNumber enIndex )
{    
    uint8 u8Return=0;
    switch(enIndex)
    {
        case VEL_nu8Valid:
            u8Return=Vel_stMainOut.u8ModuleValid;
            break;
        default:
            break;
    }
    return u8Return;
}


/*******************************************************************************
*Function : VEL_tenValueSts VEL_enGetMainOutputExport(VEL_tstMainOut *value)
*Description : export motor struct
*takes : Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
VEL_tenValueSts VEL_enGetMainOutputExport(Vel_tstMainOut *value)
{
    VEL_tenValueSts enReturn=VEL_nValid;
    memcpy(value, &Vel_stMainOut, sizeof(Vel_tstMainOut));
    return enReturn;
}




/*****************************************************************************
* EOF: VEL.c
******************************************************************************/

