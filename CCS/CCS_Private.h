
/*******************************************************************************
| Module Name: Calculate the target blowout temp ,target set temo and SI
| File Name: CCS.c
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
#ifndef CCS_PRIVATE_H
#define CCS_PRIVATE_H

#include "CCS_Type.h"

/*****************************************************************************
*Macro define
******************************************************************************/
#define CCS_u8SwVersion					CCS_au8Array[CCS_nu8SwVersion]
#define CCS_u8Valid						CCS_au8Array[CCS_nu8Valid]
#define CCS_u8SetTempValid				CCS_au8Array[CCS_nu8SetTempValid]

#define CCS_u16ErrorCode				CCS_au16Array[CCS_nu16ErrorCode]
#define CCS_u16SetTempAvg				CCS_au16Array[CCS_nu16SetTempAvg] 
#define CCS_u16SetTemp(Num)				CCS_au16Array[CCS_nu16SetTempDr+(Num)]
#define CCS_u16SetTempDr				CCS_au16Array[CCS_nu16SetTempDr]
#define CCS_u16SetTempPs				CCS_au16Array[CCS_nu16SetTempPs]

#define CCS_u16TempDiffAvg				CCS_au16Array[CCS_nu16TempDiffAvg]
#define CCS_u16TempDiff(Num)			CCS_au16Array[CCS_nu16TempDiffDr+(Num)]
#define CCS_u16TempDiffDr				CCS_au16Array[CCS_nu16TempDiffDr]
#define CCS_u16TempDiffPs				CCS_au16Array[CCS_nu16TempDiffPs]

#define CCS_u16BlwoutTempAvg			CCS_au16Array[CCS_nu16BlowoutTempAvg]
#define CCS_u16BlwoutTemp(Num)			CCS_au16Array[CCS_nu16BlowoutTempDr+(Num)]
#define CCS_u16BlwoutTempDr				CCS_au16Array[CCS_nu16BlowoutTempDr]
#define CCS_u16BlwoutTempPs				CCS_au16Array[CCS_nu16BlowoutTempPs]

#define CCS_u16UnDampedBlwoutTemp(Num)	CCS_au16Array[CCS_nu16UnDampedBlwoutTempDr+(Num)]
#define CCS_u16UnDampedBlwoutTempDr		CCS_au16Array[CCS_nu16UnDampedBlwoutTempDr]
#define CCS_u16UnDampedBlwoutTempPs		CCS_au16Array[CCS_nu16UnDampedBlwoutTempPs]

#define CCS_u16OatSetTempDiff(Num)		CCS_au16Array[CCS_nu16OatSetTempDiffDr+(Num)]
#define CCS_u16OatSetTempDiffDr			CCS_au16Array[CCS_nu16OatSetTempDiffDr]
#define CCS_u16OatSetTempDiffPs			CCS_au16Array[CCS_nu16OatSetTempDiffPs]

#define CCS_u16OatSetTempOffset(Num)	CCS_au16Array[CCS_nu16OatSetTempOffsetDr+(Num)]
#define CCS_u16OatSetTempOffsetDr		CCS_au16Array[CCS_nu16OatSetTempOffsetDr]
#define CCS_u16OatSetTempOffsetPs		CCS_au16Array[CCS_nu16OatSetTempOffsetPs]

#define CCS_u16OatBlwoutTempOffset(Num)	CCS_au16Array[CCS_nu16OatBlwoutTempOffsetDr+(Num)]
#define CCS_u16OatBlwoutTempOffsetDr	CCS_au16Array[CCS_nu16OatBlwoutTempOffsetDr]
#define CCS_u16OatBlwoutTempOffsetPs	CCS_au16Array[CCS_nu16OatBlwoutTempOffsetPs]

#define CCS_u16SiBlwoutTempOffset(Num)	CCS_au16Array[CCS_nu16SiBlwoutTempOffsetDr+(Num)]
#define CCS_u16SiBlwoutTempOffsetDr		CCS_au16Array[CCS_nu16SiBlwoutTempOffsetDr]
#define CCS_u16SiBlwoutTempOffsetPs		CCS_au16Array[CCS_nu16SiBlwoutTempOffsetPs]

#define CCS_u16TsetBlwoutTempOffset(Num)CCS_au16Array[CCS_nu16TsetBlwoutTempOffsetDr+(Num)]
#define CCS_u16TsetBlwoutTempOffsetDr	CCS_au16Array[CCS_nu16TsetBlwoutTempOffsetDr]
#define CCS_u16TsetBlwoutTempOffsetPs	CCS_au16Array[CCS_nu16TsetBlwoutTempOffsetPs]

#define CCS_u16SunBlwoutTempOffset(Num) CCS_au16Array[CCS_nu16SunBlwoutTempOffsetDr+(Num)]
#define CCS_u16SunBlwoutTempOffsetDr	CCS_au16Array[CCS_nu16SunBlwoutTempOffsetDr]
#define CCS_u16SunBlwoutTempOffsetPs	CCS_au16Array[CCS_nu16SunBlwoutTempOffsetPs]

#define CCS_u16VelBlwoutTempOffset		CCS_au16Array[CCS_nu16VelBlwoutTempOffset]

#if 0
#define CCS_u16SetTempForIct(Num)		CCS_au16Array[CCS_nu16SetTempForIctDr+(Num)]
#define CCS_u16SetTempForIctDr			CCS_au16Array[CCS_nu16SetTempForIctDr]
#define CCS_u16SetTempForIctPs			CCS_au16Array[CCS_nu16SetTempForIctPs]
#define CCS_u16PCtrTempOffset(Num)		CCS_au16Array[CCS_nu16PCtrTempOffsetDr+(Num)]
#define CCS_u16PCtrTempOffsetDr			CCS_au16Array[CCS_nu16PCtrTempOffsetDr] 
#define CCS_u16PCtrTempOffsetPs			CCS_au16Array[CCS_nu16PCtrTempOffsetPs]
#define CCS_u16OatOffset				CCS_au16Array[CCS_nu16OatOffset]
#define CCS_u16SetTempDiffOffset(Num)	CCS_au16Array[CCS_nu16SetTempDiffOffsetDr+(Num)]
#define CCS_u16SetTempDiffOffsetDr		CCS_au16Array[CCS_nu16SetTempDiffOffsetDr] 
#define CCS_u16SetTempDiffOffsetPs		CCS_au16Array[CCS_nu16SetTempDiffOffsetPs]
#define CCS_u16PreCtrTempOffset(Num)	CCS_au16Array[CCS_nu16PreCtrTempOffsetDr+(Num)]
#define CCS_u16PreCtrTempOffsetDr		CCS_au16Array[CCS_nu16PreCtrTempOffsetDr]
#define CCS_u16PreCtrTempOffsetPs		CCS_au16Array[CCS_nu16PreCtrTempOffsetPs]
#endif
/*******************************Parameter define**************************************/
#if 0
#define CCS_TempDiff_IMAX				(640)
#define CCS_TempDiff_IMIN				(-640)

#define CCS_TempDiff_UMAX				(1280u)	/*640*2*/
#define CCS_TempDiff_UMIN				(0u)

#define CCS_Temp_IMAX					(1200)	/*120*10*/
#define CCS_Temp_IMIN					(-400)	/*-40*10*/
#endif
#define CCS_Temp_UMAX					(1600u)	/*(120+40)*10*/
#define CCS_Temp_iMAX					(1600u)	/*(120+40)*10*/
#define CCS_Temp_UMIN					(0)

#define CCS_nMmiSetTempMin				(16*2) /*16deg*/
#define CCS_nMmiSetTempMax				(32*2) /*32deg*/
#define	CCS_BlwCcsTargetMax				(1600u) /*1600*/


#define CCS_nSwVersion					(0xAAu)  /*160829,161025, AA-161220*/

#define CCS_nDefaultBlwCcsTarget		(400u) 	/*0deg*/
#define CCS_nDefaultTempOffset			(640u)	/*0*10+640*/
#define CCS_nDefaultOatValue			(600u)	/*20*10+400*/
#define CCS_nDefaultIctValue			(620u)	/*22*10+400*/
#define CCS_nDefaultMmiSetTemp			(44u)	/*22*2*/
//#define CCS_nDefaultSunTempOffset		(640u)	/*0*10+640*/
#define CCS_nu8BlowoutTempFilterK       (6U)

#define CCS_nDrvSideFactor	(uint8)(0.5*16)

#define CCS_RangeCheck(input,minvalue,maxvalue)	\
	if((input)>=(maxvalue))\
		(input)=(maxvalue);\
	else if((input)<=(minvalue))\
		(input)=(minvalue)
		
/*********************************End************************************/

#ifdef CCS_UseRTE
/**************************Extern Module Interface Use RTE Start*****************************/

//#define CCS_u8GetMmiValue_ModeCtrl     Rte_IRead_Ccs_vMain_CcsGetMmi_MmiMode_MmiModeControl()
#define CCS_u8GetMmiValue_SetTempDr    Rte_IRead_Ccs_vMain_Ccs_MmiSetTempDr_u8Set()
#if SYC_ZONES >= 2U
#define CCS_u8GetMmiValue_SetTempPs    Rte_IRead_Ccs_vMain_Ccs_MmiSetTempPs_u8Set()
#endif


#define CCS_u8GetIctValue_Valid    	   Rte_IRead_Ccs_vMain_Ccs_IctValid_u8Flag()
#define CCS_u16GetIctValue_IctValue    Rte_IRead_Ccs_vMain_Ccs_IctValue_u16Temp()

#define CCS_u8GetOatValue_Valid    	   Rte_IRead_Ccs_vMain_Ccs_OatValid_u8Flag()
#define CCS_u16GetOatValue_OatValue    Rte_IRead_Ccs_vMain_Ccs_OatValue_u16Temp()

//#define CCS_u8GetAirdValue_AutoControl   Rte_IRead_Ccs_vMain_CcsGetAridAutoControl_AirdAutoControl()

#define CCS_u16GetBctlValue_BlowerTarget Rte_IRead_Ccs_vMain_Ccs_BctlBlwCcsTarget_u16BlwSpd()


#define CCS_u8GetVelValue_Valid  		 Rte_IRead_Ccs_vMain_Ccs_VelValid_u8Flag()
#define CCS_u16GetVelValue_TempOffset    Rte_IRead_Ccs_vMain_Ccs_VelTempOffset_u16TempOffset()

#define CCS_u8GetSunValue_Valid 	     Rte_IRead_Ccs_vMain_Ccs_SunValid_u8Flag()
#define CCS_u16GetSunValue_TempOffsetDr  Rte_IRead_Ccs_vMain_Ccs_SunTempOffsetDr_u16TempOffset()
#define CCS_u16GetSunValue_TempOffsetPs  Rte_IRead_Ccs_vMain_Ccs_SunTempOffsetPs_u16TempOffset()
/**************************Extern Module Interface Use RTE End*****************************/
#else
/**************************Extern Module Interface Without RTE Start*****************************/

//#define CCS_u8GetMmiValue_ModeCtrl     MMI_u8GetValue(MMI_nu8ModeControl)
#define CCS_u8GetMmiValue_SetTempDr    MMI_u8GetValue(MMI_nu8SetTempDr)
#if SYC_ZONES >= 2U
#define CCS_u8GetMmiValue_SetTempPs    MMI_u8GetValue(MMI_nu8SetTempPs)
#endif


#define CCS_u8GetIctValue_Valid    	   1//ICT_u8GetValue(ICT_nu8Valid)
#define CCS_u16GetIctValue_IctValue    600u//ICT_u16GetValue(ICT_nu16Value)

#define CCS_u8GetOatValue_Valid    	   (uint8)OAT_u16GetValue(OAT_nu16Valid)
#define CCS_u16GetOatValue_OatValue    OAT_u16GetValue(OAT_nu16Value)

//#define CCS_u8GetAirdValue_AutoControl   AIRD_u8GetValue(AIRD_nu8AutoStepInfo)

#define CCS_u16GetBctlValue_BlowerTarget BCTL_u16GetValue(BCTL_nu16CcsTrgVlt)

#define CCS_u8GetVelValue_Valid    	   	 VEL_u8GetValue(VEL_nu8Valid)
#define CCS_u16GetVelValue_TempOffset    VEL_u16GetValue(VEL_nu16TempOffset)

#define CCS_u8GetSunValue_Valid    	   	 SUN_u8GetValue(SUN_nu8Valid)
#define CCS_u16GetSunValue_TempOffsetDr  SUN_u16GetValue(SUN_nu16TempOffsetDr)
#define CCS_u16GetSunValue_TempOffsetPs  SUN_u16GetValue(SUN_nu16TempOffsetPs)

/**************************Extern Module Interface Without RTE End*****************************/

#endif

#endif                          


