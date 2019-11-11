/*******************************************************************************
| Module Name: Calculate the mixed air motor position according to blowout temp 
| File Name: MAC_Private.h
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
| 2015/07/14  2.00        Zhang Shuncong    Add CW and CCW,RTE define
| 2015-09-06  3.00        Zhang Shuncong    Add mix air curve according to hct temp
********************************************************************************/
#ifndef MAC_PRIVATE_H
#define MAC_PRIVATE_H

//#define MAC_UseCW

/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */


/*****************************************************************************
* EXPORT INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define helpful macros for easy data access and for a comfortable function use, if 
*   necessary.
* - define all macros for accessing the external module interfaces variables
* - define all macros which not need to be configed and changed for this module 
******************************************************************************/
#define MAC_u8SwVersion					MAC_au8Array[MAC_nu8SwVersion]
#define MAC_u8Valid						MAC_au8Array[MAC_nu8Valid]

#define MAC_u16ErrorCode				MAC_au16Array[MAC_nu16ErrorCode]
#define MAC_u16BlowoutTempDr			MAC_au16Array[MAC_nu16BlowoutTempDr]
#define MAC_u16BlowoutTempPs			MAC_au16Array[MAC_nu16BlowoutTempPs]
#define MAC_u16BlowoutTemp(Num)			MAC_au16Array[MAC_nu16BlowoutTempDr+(Num)]
#define MAC_u16BlowoutTempAvg			MAC_au16Array[MAC_nu16BlowoutTempAvg]
#define MAC_u16MixedAirPosDr			MAC_au16Array[MAC_nu16MixedAirPosDr]
#define MAC_u16MixedAirPosPs			MAC_au16Array[MAC_nu16MixedAirPosPs]
#define MAC_u16MixedAirPos(Num)			MAC_au16Array[MAC_nu16MixedAirPosDr+(Num)]

#define MAC_u16FlapRatioAvg			       MAC_au16Array[MAC_nu16FlapRatioAvg]
#define MAC_u16FlapRatioDr			       MAC_au16Array[MAC_nu16FlapRatioDr]
#define MAC_u16FlapRatioPs				MAC_au16Array[MAC_nu16FlapRatioPs]
#define MAC_u16FlapRatio(Num)			MAC_au16Array[MAC_nu16FlapRatioDr+(Num)]

#define MAC_u16BlowSpeedHys			 MAC_au16Array[MAC_nu16BlowSpeedHys]
#define MAC_u16EvapTempHys		       MAC_au16Array[MAC_nu16EvapTempHys]
#define MAC_u16HctTempHys					MAC_au16Array[MAC_nu16HctHys]

/***************************Parameter********************************/
#define MAC_nSwVersion					(0xA2u)
#define MAC_nMaxTemp					(1600u) /*120*10+400*/
#define MAC_nDefaultEvapValue			(400u) 	/*0*10+400*/
#define MAC_nDefaultHctValue			(1200u) /*80*10+400*/
#define MAC_nDefaultBlwoutTemp			(700u)	/*30*10+400*/
#define MAC_nDefaultBlowerTarget		(0u) 	/*120*10+400*/
#define MAC_nMaxBlowerTarget			(1600u) 	
#define MAC_nPt2K						(0u)
#define MAC_nMaxNominal					(1000u)
#define MAC_nDrvSideFactor				(uint8)(0.5*16)

#define MAC_nEvapFilterFast    			(2U)
#define MAC_nEvapFilterSlow    			(6U)
#define MAC_nEvapFilterTempLo  			(uint16)(350U) /*-5deg, -5*10+400*/
#define MAC_nEvapFilterTempHi  			(uint16)(12*10+400) /*12deg, 12*10+400*/
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/

#define MAC_RangeCheck(input,minvalue,maxvalue)	\
	if((input)>=(maxvalue))\
		(input)=(maxvalue);\
	else if((input)<=(minvalue))\
		(input)=(minvalue)

	
#ifdef MAC_UseRTE

/**************************Extern Module Interface Use RTE Start*****************************/


/**************************Extern Module Interface Use RTE End*****************************/

#else

/**************************Extern Module Interface Without RTE Start*****************************/
#define MAC_u8GetCcsValue_Valid   	CCS_u8GetValue(CCS_nu8Valid)
#define MAC_u8GetHctValue_Valid   	(uint8)HCT_u16GetValue(HCT_nu16Valid)
#define MAC_u8GetEvapValue_Valid   	EVAP_u8GetValue(EVAP_nu8Valid)

#define MAC_u8GetAirdValue_AutoControl  AIRD_u8GetValue(AIRD_nu8AirdAutoControl)

#define MAC_u16GetEvapValue_EvapMacValue   EVAP_u16GetValue(EVAP_nu16MacValue)
#define MAC_u16GetHctValue_HctTemp   	   HCT_u16GetValue(HCT_nu16Value)
#define MAC_u16GetBctlValue_BlowerTarget   BCTL_u16GetValue(BCTL_nu16TrgVlt)

#define MAC_u16GetCcsValue_BlowoutTempDr    CCS_u16GetValue(CCS_nu16BlowoutTempDr)
#define MAC_u16GetCcsValue_BlowoutTempPs    CCS_u16GetValue(CCS_nu16BlowoutTempPs)

#define MAC_u16GetPtaValue_ResultMacFbDr    PTA_u16GetValue(PTA_nResultMacMotorFbDr)
#define MAC_u16GetPtaValue_ResultMacFbPs    PTA_u16GetValue(PTA_nResultMacMotorFbPs)

/**************************Extern Module Interface Without RTE End*****************************/

#endif


#endif                                  /* ifndef MAC_PRIVATE_H*/

/*****************************************************************************
* EOF: MAC_Private.h
******************************************************************************/

