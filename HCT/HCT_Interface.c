/***************************************************************************************************
                                           HCT INTERFACE
                                           
  .File Name  : HCT_Interface.h
  
  .Description: This file is the interface of HCT.

  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-07-13  Lv Haoguang   - Creat this module.
***************************************************************************************************/

#define BCTL_Interface


/***************************************************************************************************
                                            HEADER FILES                                            
***************************************************************************************************/

/* System header files */
#include "General.h"
//#include "Rte_Hct.h"
/* Foreign header file */
#include "Canapp.h"

/* Own header files */
#include "HCT_Interface.h"
#include "HCT_Type.h"
#include "HCT.h"
#include "Hct_Private.h" 

static uint16 HCT_u16CanValueErrorCnt = 0u;
static HCT_tenValueSts enRetValue = HCT_nInvalid;

HCT_tenValueSts HCT_enImportRawTemp(uint16 *value)
{
    uint32 u32Dummy;
	if(HCT_u16IgnOnDelayFinish == False)
	{
		enRetValue = HCT_nInvalid;
		*value = HCT_u16DefaultValue;
	}
	else
	{
        if(HCT_u16QualityFlag == HCT_u16QualityValid)
        {
			u32Dummy = HCT_u16RawTempFromCan;
            if(u32Dummy < HCT_u16MaxValue)
            {
                /*PhsicalValue = HCT_u16RawTempFromCan * 0.75 - 36.8 **
    			**InternelValue = PhsicalValue*10 +400               */
                u32Dummy = ((HCT_u16RawTempFromCan*15>>1)+32);
                enRetValue = HCT_nValid;
                *value = (uint16)u32Dummy;
                HCT_u16CanValueErrorCnt = 0;
            }
            else if(HCT_u16CanValueErrorCnt >= HCT_u16ValueErrorTime)
            {
                enRetValue = HCT_nDefault;
                *value = HCT_u16DefaultValue;
            }
            else
            {/*Keep the last value*/
                HCT_u16CanValueErrorCnt++;
            }
        }
        else
        {
            if(HCT_u16CanValueErrorCnt >= HCT_u16ValueErrorTime)
            {
                enRetValue = HCT_nDefault;
                *value = HCT_u16DefaultValue;
            }
            else
            {/*Keep the last value*/
                HCT_u16CanValueErrorCnt++;
            }
        }
    #if 0
		if(HCT_u16QualityFlag == HCT_u16QualityInValid)
		{
			enRetValue = HCT_nDefault;
			*value = HCT_u16DefaultValue;
		}
		else
		{
			enRetValue = HCT_nValid;
			/*PhsicalValue = HCT_u16RawTempFromCan * 0.75 - 36.8 **
			**InternelValue = PhsicalValue*10 +400               */
			u32Dummy = ((HCT_u16RawTempFromCan*15>>1)+32);
			if(u32Dummy >= 65535)
			{
				*value = 65535;
			}
			else
			{
				*value = (uint16)u32Dummy;
			}
		}
    #endif
	}
    return enRetValue;
}

HCT_tenValueSts HCT_enImportOatTemp(uint16 *value)
{
    HCT_tenValueSts enRetValue;
	if(HCT_u16IgnOnDelayFinish == False)
	{
		enRetValue = HCT_nInvalid;
		*value = HCT_u16DefaultOatValue;
	}
	else
	{
		if(HCT_u16OatValid == False)
		{
			enRetValue = HCT_nDefault;
			*value = HCT_u16DefaultOatValue;
		}
		else
		{
			enRetValue = HCT_nValid;
			*value = HCT_u16OatValue;
		}
	}
	return enRetValue;
}

void HCT_enInitValue(void)
{
    HCT_u16CanValueErrorCnt = 0u;
    enRetValue = HCT_nInvalid;
}

void HCT_enExportAll(void)
{
    //Rte_IWrite_Hct_vMain_HctValue_u16Temp(HCT_u16GetValue(HCT_nu16Value));
    //Rte_IWrite_Hct_vMain_HctValid_u8Flag(HCT_u16GetValue(HCT_nu16Valid));
    //Rte_IWrite_Hct_vMain_HctValueForBus_u16Temp(HCT_u16GetValue(HCT_nu16ErrorCode));
    //Rte_IWrite_Hct_vMain_HctSwVersion_u8Version(HCT_u16GetValue(HCT_nu16SwVer));
}


