/*******************************************************************************
| Module Name: Calculate the Blowout and Temp offset according to the solar
| File Name: SUN.c
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
| Li Jiaye                           Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2013-04-09  1.00        Sui Yanchun       First implementation
| 2015-08-05  2.00        Zhang Shuncong    Add RTE ,Copyright and cfg
| 2016-09-22  0100        Li Jiaye          updated module interface
********************************************************************************/

#define SUN                        /* name of the module                */
/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/

/* System-headerfiles */
#include "General.h"


/* Foreign headerfiles */

#include "ALG.h" 

/* Own headerfiles */
#include "SUN_Cfg.h" 
#include "SUN.h" 
#include "SUN_Private.h" 
#include "SUN_interface.h"
#include "SUN_Type.h"

/*Local variable definition*/
static Bool     SUN_biNeedFilterInit;          /* decide  the linear fliter initial when reset*/
static Bool     SUN_biSysTick1s;                 /* Timer conter tick every second */
static uint8    SUN_u8SysTimeConter;        /* Sys Time conter, increase every 100ms*/


Sun_tstMainOut Sun_stMainOut;

/*Local function definition*/
static void SUN_vPerformDamping(Sun_tstDampingIn *Input,Sun_tstDampingOut *Output);
static void SUN_vInputValueProcess(Sun_tstInputValueProcessIn *Input,Sun_tstInputValueProcessOut *Output);
static uint16 SUN_u16ValueLinearFilter(uint16 u16RawValue, uint16 u16PreValue, uint8 u8FilterType);
static uint16 SUN_u16OffsetLinearFilter(uint16 u16RawValue, uint16 u16PreValue,uint8 u8Step);
void SUN_u16CalOatBlowerOffset (Sun_tstCalOatBlowerOffsetIn *Input,uint16 *Output);		
void SUN_u16CalOatTempOffset (Sun_tstCalOatTempOffsetIn *Input, uint16 *Output);	

#if(SUN_nSensorNum== 2)
static uint16 SUN_u16MaxTempAB(uint16 u16TempA,uint16 u16TempB);
#endif





/* ===========================================================================
* Function   : void SUN_vReset (void)
* Description: This is the reset function for the SUN module.
* Takes      : None
* Returns    : None
*/
  void SUN_vReset(void)
{
    Sun_stMainOut.u16RawSolarValueDr= SUN_nDefaultValue;
    Sun_stMainOut.u16RawSolarValuePs= SUN_nDefaultValue;
    Sun_stMainOut.u8ModuleValid= False;
    Sun_stMainOut.u16SolarValueDr= SUN_nDefaultValue;
    Sun_stMainOut.u16SolarValuePs= SUN_nDefaultValue;
    Sun_stMainOut.u16SolarValueFilter= SUN_nDefaultValue;
    Sun_stMainOut.u16TempOffsetDr= SUN_nDefaultTempOffset;
    Sun_stMainOut.u16TempOffsetPs= SUN_nDefaultTempOffset; 	
    Sun_stMainOut.u16BlowerOffset= SUN_nDefaultBlowerOffset;	

    SUN_biSysTick1s=False;              
    SUN_u8SysTimeConter=0;  
    SUN_biNeedFilterInit = True;  /*filter init*/

}

/* ===========================================================================
* Function   : void SUN_vInit (void)
* Description: This is the initialisation function for the SUN module.
* Takes      : None
* Returns    : None
*/
  void SUN_vInit(void)
{
	SUN_vReset ();
	SUN_vClrForceFlagByteAction();
}

/*****************************************************************************
 AUTHOR:		 : Li Jiaye											  *
 DATE: 		 : 2015/07/22										  *
 Function      : Sun_vActive                                                   *
 Description   : 
 Return Value  : None                                                        *
*****************************************************************************/
void SUN_vActive(void)
{
    /*nothing to do*/
}

/* ===========================================================================
* Function   : void SUN_vMain (void)
* Description: Main container function of SUN
* Takes      : None
* Returns    : None
*/

void SUN_vMain(void)
{
    uint8   u8i = 0;
    Bool biOatValid = True;
    uint16   u16SunMaxVal = 0;
    uint16   au16TempOffset[SUN_nSensorNum];
    uint16   au16BlwrOffset[SUN_nSensorNum];

    Sun_tstInputValueProcessIn Sun_stInputValueProcessIn;
    Sun_tstInputValueProcessOut Sun_stInputValueProcessOut;

    Sun_tstDampingIn Sun_stDampingIn;
    Sun_tstDampingOut Sun_stDampingOut;

    Sun_tstCalOatTempOffsetIn Sun_stCalOatTempOffsetIn;

    Sun_tstCalOatBlowerOffsetIn Sun_stCalOatBlowerOffsetIn;

    /*In the process of integration,open up the following*/
    #if (SUN_OpenInterfaces_Cfg == Yes)
    SUN_enOATValidImport(&biOatValid);
    #endif

     /* Prepare the system 1s flag, add by ZRM */           
    SUN_u8SysTimeConter++;  
    if(SUN_u8SysTimeConter<SUN_nSysTimeCont1s)
    {
        SUN_biSysTick1s=False;          
    }
    else
    {
        SUN_u8SysTimeConter=0;
        SUN_biSysTick1s=True;
    }
    

    if (biOatValid == True)
    {
        Sun_stInputValueProcessIn.u8SolarRawValueDrSts=\
            SUN_enSolarRawValueDrvImport(&Sun_stInputValueProcessIn.u16SolarRawValueDr);
        Sun_stMainOut.u16RawSolarValueDrAD=Sun_stInputValueProcessIn.u16SolarRawValueDr;        
        #if (SUN_nSensorNum >1 ) 
        Sun_stInputValueProcessIn.u8SolarRawValuePsSts=\
            SUN_enSolarRawValuePsImport(&Sun_stInputValueProcessIn.u16SolarRawValuePs);
        Sun_stMainOut.u16RawSolarValuePsAD=Sun_stInputValueProcessIn.u16SolarRawValuePs;
        #endif
        SUN_vInputValueProcess(&Sun_stInputValueProcessIn,&Sun_stInputValueProcessOut);

        Sun_stMainOut.u16RawSolarValueDr=Sun_stInputValueProcessOut.u16SolarRawValueDr;
        Sun_stMainOut.u16RawSolarValuePs=Sun_stInputValueProcessOut.u16SolarRawValuePs;
        Sun_stDampingIn.u16SolarRawValueDr=Sun_stInputValueProcessOut.u16SolarRawValueDr;
        Sun_stDampingIn.u16SolarRawValuePs=Sun_stInputValueProcessOut.u16SolarRawValuePs;
        SUN_vPerformDamping(&Sun_stDampingIn,&Sun_stDampingOut);

        Sun_stMainOut.u16SolarValueDr=Sun_stDampingOut.u16SolarValueDr;
        Sun_stMainOut.u16SolarValuePs=Sun_stDampingOut.u16SolarValuePs;
        Sun_stMainOut.u16SolarValueFilter=Sun_stDampingOut.u16FilterSolar;

        if (SUN_biSysTick1s == True)
        {      
            #if(SUN_nSensorNum== 2)
            u16SunMaxVal = SUN_u16MaxTempAB(Sun_stDampingOut.u16SolarValueDr,Sun_stDampingOut.u16SolarValuePs);    
            #else
            u16SunMaxVal=Sun_stDampingOut.u16SolarValueDr;
            #endif

            for ( u8i=0;u8i<SUN_nSensorNum;u8i++ )
            {				
                #if ( SUN_nUseMaxSolar == False )
                /* Calculate Blowout Temperature Offset both left and right */
                SUN_enOATValueImport(&Sun_stCalOatTempOffsetIn.u16OATvalue);
                Sun_stCalOatTempOffsetIn.u16SolarValueDr=Sun_stDampingOut.u16SolarValueDr;
                Sun_stCalOatTempOffsetIn.u16SolarValuePs=Sun_stDampingOut.u16SolarValuePs;
                Sun_stCalOatTempOffsetIn.u8Zone=u8i;
                SUN_u16CalOatTempOffset(&Sun_stCalOatTempOffsetIn,&au16TempOffset[u8i]);
                #else
                /* Calculate Blowout Temperature,only the max,look up the left solar table */
                SUN_enOATValueImport(&Sun_stCalOatTempOffsetIn.u16OATvalue);
                Sun_stCalOatTempOffsetIn.u16SolarValueDr=u16SunMaxVal;
                Sun_stCalOatTempOffsetIn.u16SolarValuePs=u16SunMaxVal;
                Sun_stCalOatTempOffsetIn.u8Zone=u8i;
                SUN_u16CalOatTempOffset(&Sun_stCalOatTempOffsetIn,&au16TempOffset[u8i]);
                #endif
                
                /* Calculate Blower Offset */
                SUN_enOATValueImport(&Sun_stCalOatBlowerOffsetIn.u16OATvalue);
                Sun_stCalOatBlowerOffsetIn.u16SolarValue=u16SunMaxVal;
                SUN_u16CalOatBlowerOffset(&Sun_stCalOatBlowerOffsetIn,&au16BlwrOffset[u8i]);

                /* To prevent over- / underflow, the offset values are limited  */
                SUN_RangeCheck(au16TempOffset[u8i], SUN_nMinTempOffset, SUN_nMaxTempOffset);
                SUN_RangeCheck(au16BlwrOffset[u8i], SUN_nMinBlowerOffset, SUN_nMaxBlowerOffset);

            }	
            Sun_stMainOut.u16TempOffsetDr=SUN_u16OffsetLinearFilter(au16TempOffset[SUN_nZonesLeft],Sun_stMainOut.u16TempOffsetDr,SUN_u8OffsetStep);
            #if(SUN_nSensorNum== 2)
            Sun_stMainOut.u16TempOffsetPs=SUN_u16OffsetLinearFilter(au16TempOffset[SUN_nZonesRight],Sun_stMainOut.u16TempOffsetPs,SUN_u8OffsetStep);
            #endif
            /* Perform a simple damping, limit the change speed to   1 step / sec */
            
            Sun_stMainOut.u16BlowerOffset= SUN_u16OffsetLinearFilter(au16BlwrOffset[SUN_nZonesLeft],Sun_stMainOut.u16BlowerOffset,SUN_u8OffsetStep);
        }
        else
        {
            /*nothing to do*/
        } 
        Sun_stMainOut.u8ModuleValid = True;
    }
    else
    {
        Sun_stMainOut.u8ModuleValid = False;
    }
    SUN_vMainExportAction();
}
/* ===========================================================================
* Function   : void SUN_vDeinit (void)
* Description: This is On the ignition->off transition function for the SUN module.
* Takes      : None
* Returns    : None
*/
  void SUN_vDeinit (void)
{
	/*Nothing to do*/
}


/* ===========================================================================
* Function   :  void SUN_u16CalOatBlowerOffset (Sun_tstCalOatBlowerOffsetIn *Input,uint16 *Output)		
* Description:  Calculate Blower Offset
* Takes      :   u16InputValue - the input solar indensity value
* Returns   :   The 16-bit output of Blower Offset
*/
void SUN_u16CalOatBlowerOffset (Sun_tstCalOatBlowerOffsetIn *Input,uint16 *Output)	
{
	uint16 *pu16_1 = NULL;
	uint16 *pu16_2 = NULL;
	uint16 u16BlowerSpeedOffset   = 0;
	uint16 au16Offsets[2];
	
	if(Input->u16OATvalue<=SUN_au16Group3BlowerOffsetAmbientTbl[0])
	{	/* Select the first curve for searching the value.*/
		pu16_1 = (uint16 *)SUN_au16Group3BlowerOffsetTbl_X;
		pu16_2 = (uint16 *)SUN_au16Group3BlowerOffsetTbl_Y0;
		u16BlowerSpeedOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValue,SUN_nBlowerOffsetTbl_Len);
	}
	else if (Input->u16OATvalue<=SUN_au16Group3BlowerOffsetAmbientTbl[1])
	{	/* Select the first & second curves for generating the value, then search it for the value.*/
		pu16_1 = (uint16 *)SUN_au16Group3BlowerOffsetTbl_X;
		pu16_2 = (uint16 *)SUN_au16Group3BlowerOffsetTbl_Y0;
		au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,Input->u16SolarValue,SUN_nBlowerOffsetTbl_Len);

		pu16_2 = (uint16 *)SUN_au16Group3BlowerOffsetTbl_Y1;
		au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValue,SUN_nBlowerOffsetTbl_Len);
		pu16_1 = (uint16 *)SUN_au16Group3BlowerOffsetAmbientTbl;
		pu16_2 = (uint16 *)au16Offsets;
		u16BlowerSpeedOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16OATvalue, 2);		
	}
	
	else if (Input->u16OATvalue<=SUN_au16Group3BlowerOffsetAmbientTbl[2])
	{	/* Select the second & third curves for generating the value, then search it for the value.*/
		pu16_1 = (uint16 *)SUN_au16Group3BlowerOffsetTbl_X;
		pu16_2 = (uint16 *)SUN_au16Group3BlowerOffsetTbl_Y1;
		au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValue,SUN_nBlowerOffsetTbl_Len);

		pu16_2 = (uint16 *)SUN_au16Group3BlowerOffsetTbl_Y2;
		au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValue,SUN_nBlowerOffsetTbl_Len);
		pu16_1 = (uint16 *)SUN_au16Group3BlowerOffsetAmbientTbl+1;
		pu16_2 = (uint16 *)au16Offsets;
		u16BlowerSpeedOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16OATvalue, 2);		
	}
	else if (Input->u16OATvalue<SUN_au16Group3BlowerOffsetAmbientTbl[3])
	{	/* Select the third & fourth curves for generating the value, then search it for the value.*/
		pu16_1 = (uint16 *)SUN_au16Group3BlowerOffsetTbl_X;
		pu16_2 = (uint16 *)SUN_au16Group3BlowerOffsetTbl_Y2;
		au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValue,SUN_nBlowerOffsetTbl_Len);

		pu16_2 = (uint16 *)SUN_au16Group3BlowerOffsetTbl_Y3;
		au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValue,SUN_nBlowerOffsetTbl_Len);
		pu16_1 = (uint16 *)SUN_au16Group3BlowerOffsetAmbientTbl+2;
		pu16_2 = (uint16 *)au16Offsets;
		u16BlowerSpeedOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16OATvalue, 2);		
	}	
	else
	{	/* Select the last curve for searching the value.*/
		pu16_1 = (uint16 *)SUN_au16Group3BlowerOffsetTbl_X;
		pu16_2 = (uint16 *)SUN_au16Group3BlowerOffsetTbl_Y3;
		u16BlowerSpeedOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValue,SUN_nBlowerOffsetTbl_Len);
	}
	*Output=u16BlowerSpeedOffset;

}

/* ===========================================================================
* Function   :  void SUN_u16CalOatTempOffset (Sun_tstCalOatTempOffsetIn *Input, uint16 *Output)	
* Description:  Calculate Blowout Temperature Offset
* Takes      :   u16InputValue - the input solar indensity value
* Returns   :   The 16-bit output of Blowout Temperature Offset
*/
void SUN_u16CalOatTempOffset (Sun_tstCalOatTempOffsetIn *Input, uint16 *Output)
{
	uint16 *pu16_1 = NULL;
	uint16 *pu16_2 = NULL;
	uint16 u16TempOffset = 640;	
	uint16 au16Offsets[2];

	if (Input->u8Zone == ((uint8)SUN_nZonesLeft))
	{
		if(Input->u16OATvalue<=SUN_au16Group2TempOffsetAmbientTbl[0])
		{	/* Select the first curve for searching the value.*/
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetTbl_X;
			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y0;
			u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValueDr,SUN_nTempOffsetTbl_Len);
		}
		else if (Input->u16OATvalue<=SUN_au16Group2TempOffsetAmbientTbl[1])
		{	/* Select the first & second curves for generating the value, then search it for the value.*/
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetTbl_X;
			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y0;
			au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValueDr,SUN_nTempOffsetTbl_Len);

			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y1;
			au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValueDr,SUN_nTempOffsetTbl_Len);
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetAmbientTbl;
			pu16_2 = &au16Offsets[0];
			u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16OATvalue, 2);		
		}
		
		else if (Input->u16OATvalue<=SUN_au16Group2TempOffsetAmbientTbl[2])
		{	/* Select the second & third curves for generating the value, then search it for the value.*/
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetTbl_X;
			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y1;
			au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValueDr,SUN_nTempOffsetTbl_Len);

			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y2;
			au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValueDr,SUN_nTempOffsetTbl_Len);
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetAmbientTbl+1;
			pu16_2 = (uint16 *)au16Offsets;
			u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16OATvalue, 2);		
		}
		else if (Input->u16OATvalue<SUN_au16Group2TempOffsetAmbientTbl[3])
		{	/* Select the third & fourth curves for generating the value, then search it for the value.*/
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetTbl_X;
			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y2;
			au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValueDr,SUN_nTempOffsetTbl_Len);

			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y3;
			au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValueDr,SUN_nTempOffsetTbl_Len);
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetAmbientTbl+2;
			pu16_2 = (uint16 *)au16Offsets;
			u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16OATvalue, 2);		
		}	

		else
		{	/* Select the last curve for searching the value.*/
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetTbl_X;
			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y3;
			u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValueDr,SUN_nTempOffsetTbl_Len);
		}
	}
#if ( SUN_nUseMaxSolar == False )
    else if(Input->u8Zone == ((uint8)SUN_nZonesRight))
    {
		if(Input->u16OATvalue<=SUN_au16Group2TempOffsetAmbientTbl[0])
		{	/* Select the first curve for searching the value.*/
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetTbl_X;
			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y0;
			u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValuePs,SUN_nTempOffsetTbl_Len);
		}
		else if (Input->u16OATvalue<=SUN_au16Group2TempOffsetAmbientTbl[1])
		{	/* Select the first & second curves for generating the value, then search it for the value.*/
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetTbl_X;
			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y0;
			au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValuePs,SUN_nTempOffsetTbl_Len);

			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y1;
			au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValuePs,SUN_nTempOffsetTbl_Len);
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetAmbientTbl;
			pu16_2 = &au16Offsets[0];
			u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16OATvalue, 2);		
		}
		
		else if (Input->u16OATvalue<=SUN_au16Group2TempOffsetAmbientTbl[2])
		{	/* Select the second & third curves for generating the value, then search it for the value.*/
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetTbl_X;
			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y1;
			au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValuePs,SUN_nTempOffsetTbl_Len);

			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y2;
			au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValuePs,SUN_nTempOffsetTbl_Len);
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetAmbientTbl+1;
			pu16_2 = (uint16 *)au16Offsets;
			u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16OATvalue, 2);		
		}
		else if (Input->u16OATvalue<SUN_au16Group2TempOffsetAmbientTbl[3])
		{	/* Select the third & fourth curves for generating the value, then search it for the value.*/
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetTbl_X;
			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y2;
			au16Offsets[0] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValuePs,SUN_nTempOffsetTbl_Len);

			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y3;
			au16Offsets[1] = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValuePs,SUN_nTempOffsetTbl_Len);
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetAmbientTbl+2;
			pu16_2 = (uint16 *)au16Offsets;
			u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16OATvalue, 2);		
		}	

		else
		{	/* Select the last curve for searching the value.*/
			pu16_1 = (uint16 *)SUN_au16Group2TempOffsetTbl_X;
			pu16_2 = (uint16 *)SUN_au16Group2TempOffsetTbl_Y3;
			u16TempOffset = ALG_u16CurveLookup_16_16_Limit (pu16_1,pu16_2,Input->u16SolarValuePs,SUN_nTempOffsetTbl_Len);
		}
	}
    else
    {
    	u16TempOffset = 0;
    }
#endif
    *Output=u16TempOffset;

}

/* ===========================================================================
* Function   :  static uint16 SUN_u16ValueLinearFilter(uint16 u16RawValue, uint16 u16PreValue, uint8 u8FilterType)	
* Description:  This function impliments a second order low pass filter   */
/*              with guaranteed no loss of resolution. 
* Takes      :  u16SunRawValue - Raw solar indensity from sensor
                u16PtrAddr -  old Sun Value
* Returns   :   The 16-bit output of the filter
*/
 static uint16 SUN_u16ValueLinearFilter(uint16 u16RawValue, uint16 u16PreValue, uint8 u8FilterType)
{
	uint8 u8IncreSpeed=SUN_u8SlowIncrement;
	uint8 u8DecreSpeed=SUN_u8SlowDecrement;

	if (u8FilterType == SUN_nFilterFast)
	{

		/*Is fast filter type*/
		u8IncreSpeed=SUN_u8FastIncrement;
		u8DecreSpeed=SUN_u8FastDecrement;
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
* Function   :  static uint16 SUN_u16OffsetLinearFilter(uint16 u16RawValue, uint16 u16PreValue,uint8 u8Step)	
* Description:  This function impliments a second order low pass filter   */
/*              with guaranteed no loss of resolution. 
* Takes      :  u16RawValue - Raw solar indensity from sensor
                u16PtrAddr -  old Sun Value
                u8Step - step
* Returns   :   The 16-bit output of the filter
*/
static uint16 SUN_u16OffsetLinearFilter(uint16 u16RawValue, uint16 u16PreValue,uint8 u8Step)
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

/*****************************************************************************
 Function      : SUN_vInputValueProcess
 Description   : Read AD port(raw value) and convert vol to W/m2,
 Return Value  : void
*****************************************************************************/
static void SUN_vInputValueProcess(Sun_tstInputValueProcessIn *Input,Sun_tstInputValueProcessOut *Output)
{   
    uint16 *pu16_1=NULL,*pu16_2=NULL;
    uint16 u16SensorRawValueLeft,u16SensorRawValueRight;
    
    Sun_stMainOut.u16ErrorCode=0u;    /* Clear current error code */


    if(Input->u16SolarRawValueDr>SUN_SensorShortToPowAD)
    {
        Sun_stMainOut.u16ErrorCode|=0x0001;
    }
    else
    {
        Sun_stMainOut.u16ErrorCode&=(~0x0001);
    }
    if(Input->u16SolarRawValueDr<SUN_SensorShortToGndAD)
    {
        Sun_stMainOut.u16ErrorCode|=0x0002;
    }
    else
    {
        Sun_stMainOut.u16ErrorCode&=(~0x0001);
    }
    #ifdef CANSensor
    if(Input->u8SolarRawValueDrSts==SUN_nDefault)
    {
        Sun_stMainOut.u16ErrorCode|=0x0001;
    }
    u16SensorRawValueLeft=Input->u16SolarRawValueDr;
    #else    
    pu16_1 = (uint16 *)SUN_au16Group1SunSensorValueX;
    pu16_2 = (uint16 *)SUN_au16Group1SunSensorValueY;
    u16SensorRawValueLeft = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,Input->u16SolarRawValueDr,SUN_nSunSensorValue_Len);
    #endif
    SUN_RangeCheck(u16SensorRawValueLeft, SUN_nMinValue, SUN_nMaxValue);


    #if (SUN_nSensorNum >1 ) 
    if(Input->u16SolarRawValuePs>SUN_SensorShortToPowAD)
    {
        Sun_stMainOut.u16ErrorCode|=0x0004;
    }
    else
    {
        Sun_stMainOut.u16ErrorCode&=(~0x0004);
    }
    if(Input->u16SolarRawValuePs<SUN_SensorShortToGndAD)
    {
        Sun_stMainOut.u16ErrorCode|=0x0008;
    }
    else
    {
        Sun_stMainOut.u16ErrorCode&=(~0x0008);
    }
    #ifdef CANSensor
    u16SensorRawValueRight=Input->u16SolarRawValuePs;
    #else
    pu16_1 = (uint16 *)SUN_au16Group1SunSensorValueX;
    pu16_2 = (uint16 *)SUN_au16Group1SunSensorValueY;
    u16SensorRawValueRight = ALG_u16CurveLookup_16_16_Limit(pu16_1,pu16_2,Input->u16SolarRawValuePs,SUN_nSunSensorValue_Len);
    #endif
    SUN_RangeCheck(u16SensorRawValueRight, SUN_nMinValue, SUN_nMaxValue);
    #endif
    Output->u16SolarRawValueDr=u16SensorRawValueLeft;
    Output->u16SolarRawValuePs=u16SensorRawValueRight;
}





#if(SUN_nSensorNum== 2)
/*****************************************************************************
 Function      : SUN_u16MaxTempAB
 Description   : cal the max value between A and B
 Return Value  : uint16
*****************************************************************************/
static uint16 SUN_u16MaxTempAB(uint16 u16TempA,uint16 u16TempB)
{
    uint16 u16RetValue=0;

	#if (SUN_nSensorNum >1 )
	u16RetValue = MAX(u16TempA,u16TempB); /*max value*/
	#else
	u16RetValue = u16TempA;
	#endif   

    return u16RetValue;
}
#endif

/*******************************************************************************
  Function   : SUN_vPerformDamping                                                                                                                                                                                                                                     
                           
  Description: This function is used to damp the sunload value.
  
  Arguments  : None
  
  Returns    : None 
*******************************************************************************/
static void SUN_vPerformDamping(Sun_tstDampingIn *Input,Sun_tstDampingOut *Output)
{
    uint16   u16SunFilterVal = 0;
    static uint16 u16ValueDr,u16ValuePs,u16FilterSolar;
    
  #if(SYC_ZONES == 2)
    u16SunFilterVal = SUN_u16MaxTempAB(Input->u16SolarRawValueDr,Input->u16SolarRawValuePs);
  #else
    u16SunFilterVal=Input->u16SolarRawValueDr;
  #endif
   
    if(SUN_biNeedFilterInit == True)
	{
	    SUN_biNeedFilterInit = False;
        
		u16ValueDr = Input->u16SolarRawValueDr;
        
        #if (SUN_nSensorNum >1 )               
        u16ValuePs = Input->u16SolarRawValuePs;  
        #else
        u16ValuePs = u16ValueDr; 
        #endif
     
		u16FilterSolar = u16SunFilterVal;	
	}
	else
	{	
		if (SUN_biSysTick1s == True)
		{
			u16FilterSolar = SUN_u16ValueLinearFilter(u16SunFilterVal,u16FilterSolar,SUN_nFilterSlow);

            u16ValueDr = SUN_u16ValueLinearFilter(Input->u16SolarRawValueDr,u16ValueDr,SUN_nFilterFast);

            #if (SUN_nSensorNum >1 )               
            u16ValuePs = SUN_u16ValueLinearFilter(Input->u16SolarRawValuePs,u16ValuePs,SUN_nFilterFast);  
            #else
            u16ValuePs = u16ValueDr; 
            #endif

            /* To prevent over- / underflow, the values are limited  */
	        SUN_RangeCheck(u16FilterSolar, SUN_nMinValue, SUN_nMaxValue);
            SUN_RangeCheck(u16ValueDr, SUN_nMinValue, SUN_nMaxValue);
            SUN_RangeCheck(u16ValuePs, SUN_nMinValue, SUN_nMaxValue);
        }
        else
        {
            /*nothing to do*/
        }
    }
    Output->u16FilterSolar=u16FilterSolar;
    Output->u16SolarValueDr=u16ValueDr;
    Output->u16SolarValuePs=u16ValuePs;
}



/*****************************************************************************
 Function      : SUN_u16GetValue
 Description   : The extern model get the uint16 type variable value from this model
 Return Value  : uint16 value
*****************************************************************************/
uint16 SUN_u16GetValue( SUN_tenu16VarNumber enIndex )
{
    uint16 u16Return=0;
    switch(enIndex)
    {
        case SUN_nu16SwVersion:
            u16Return=SUN_SwVersion;
            break;
        case SUN_nu16ADRawValueLeft:
            u16Return=Sun_stMainOut.u16RawSolarValueDrAD;
            break;
        case SUN_nu16ADRawValueRight:
            u16Return=Sun_stMainOut.u16RawSolarValuePsAD;
            break;
        case SUN_nu16SensorRawValueLeft:
            u16Return=Sun_stMainOut.u16RawSolarValueDr;
            break;
        case SUN_nu16SensorRawValueRight:
            u16Return=Sun_stMainOut.u16RawSolarValuePs;
            break;
        case SUN_nu16ValueDr:
            u16Return=Sun_stMainOut.u16SolarValueDr;
            break;
        case SUN_nu16ValuePs:
            u16Return=Sun_stMainOut.u16SolarValuePs;
            break;
        case SUN_nu16FilterSolar:
            u16Return=Sun_stMainOut.u16SolarValueFilter;
            break;
        case SUN_nu16TempOffsetDr:
            u16Return=Sun_stMainOut.u16TempOffsetDr;
            break;
        case SUN_nu16TempOffsetPs:
            u16Return=Sun_stMainOut.u16TempOffsetPs;
            break;
        case SUN_nu16BlowerOffset:
            u16Return=Sun_stMainOut.u16BlowerOffset;
            break;
        case SUN_nu16ErrCode:
            u16Return=Sun_stMainOut.u16ErrorCode;
            break;
        default:
            break;
    }
    return u16Return;
}

/*****************************************************************************
 Function      : SUN_u8GetValue
 Description   : The extern model get the uint16 type variable value from this model
 Return Value  : uint8 value
*****************************************************************************/
uint8 SUN_u8GetValue( SUN_tenu8VarNumber enIndex )
{
    uint8 u8Return=0;
    switch(enIndex)
    {
        case SUN_nu8Valid:
            u8Return=Sun_stMainOut.u8ModuleValid;
            break;
        default:
            break;
    }
    return u8Return;
}

/*******************************************************************************
*Function : SUN_tenValueSts SUN_enGetMainOutputExport(SUN_tstMainOut *value)
*Description : export motor struct
*takes : Motor index
*return: 0:invalid  1:valid 2:default   3:last valid
*/
SUN_tenValueSts SUN_enGetMainOutputExport(Sun_tstMainOut *value)
{
    SUN_tenValueSts enReturn=SUN_nValid;
    memcpy(value, &Sun_stMainOut, sizeof(Sun_tstMainOut));
    return enReturn;
}


/*****************************************************************************
* EOF:SUN.c
******************************************************************************/


