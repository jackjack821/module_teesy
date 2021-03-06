/**************************************************************************************/
/*------------------------------------------------------------------------------------
              Automatically Generated File,do not edit this file manually!
-------------------------------------------------------------------------------------*/
/** Generated On : 2018-3-5 14:28:19                                      */
/**           By : uidp4501                                      */
/**        Using : CCS_FE-5DB7DA_V1.2.xml                         */
/**         From : D:\HVACProject\Geely\FE-5DB&7DA\ProjectCode\01_APP\CCS                             */
/**               (D = )                                                    */
/**************************************************************************************/

/**************************************************************************************
 Module Name : CCS
 File Name : CCS_Cfg.c
--------------------------------------------------------------------------------------
               C O P Y R I G H T
--------------------------------------------------------------------------------------
 Copyright (c) 2015 Huizhou Desay SV Automotive Co., Ltd.    All rights reserved.

 This software is copyright protected and proprietary to Desay SV Automotive Co., Ltd.
 Desay SV Automotive Co., Ltd grants to you only those rights as set out in the
 license conditions. All other rights remain with Desay SV Automotive Co., Ltd.

 REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
 -------------------------------------------------------------------------------------
               A U T H O R   I D E N T I T Y
 ------------------------------------------------------------------------------------
  Name                                          Company
  -----------------------------          ---------------------------------------
 uidp4501                              Desay SV Automotive Co., Ltd
  -----------------------------          ---------------------------------------
***************************************************************************************/
/*Module Define*/
#define CCS_CFG

/*Header file */
#include "CCS_Cfg.h"

/***************************************************************************************
*MODULE GLOBAL CONFIGURATION CONSTANTS
* In this section define
* - constants and macros to configure your module. These constants are unknown for other
*   modules
***************************************************************************************/



const CCS_tstRomLayout CCS_stRomLayout = {
	{  /*----------------------- Group1 ---------------------------------------*/
		{  /* ModuleInfo */
			0x1U,				/* u8VariableConst */
			0x1U,				/* u8ChipType */
		},
		{  /* ModuleData */
			{ 0x32U,0xfaU,0x190U,0x226U,0x2eeU,0x320U },				/* au16OatSetTempOffsetX_Tbl */
			{ 0x29eU,0x299U,0x292U,0x28aU,0x285U,0x280U },				/* au16OatSetTempOffsetY_Tbl */
			{ 0x0U,0x8cU,0xf0U,0x154U,0x1eaU,0x226U,0x276U,0x2bcU,0x2eeU,0x320U,0x352U,0x384U,0x3e8U },				/* au16OatBlowTempOffsetX_Tbl */
			{ 0x3e8U,0x384U,0x352U,0x320U,0x2eeU,0x2d0U,0x2bcU,0x2a8U,0x280U,0x258U,0x21cU,0x1f4U,0x1e0U },				/* au16OatBlowTempOffsetY1_Tbl */
			{ 0x3e8U,0x3b6U,0x384U,0x334U,0x30cU,0x2f8U,0x2e4U,0x2bcU,0x280U,0x258U,0x230U,0x21cU,0x1f4U },				/* au16OatBlowTempOffsetY2_Tbl */
			{ 0x384U,0x370U,0x35cU,0x320U,0x30cU,0x2f8U,0x2e4U,0x2bcU,0x28aU,0x262U,0x24eU,0x226U,0x208U },				/* au16OatBlowTempOffsetY3_Tbl */
			{ 0x384U,0x35cU,0x320U,0x30cU,0x2e4U,0x2bcU,0x294U,0x26cU,0x258U,0x24eU,0x244U,0x22bU,0x212U },				/* au16OatBlowTempOffsetY4_Tbl */
			{ 0x190U,0x258U,0x320U,0x44cU },				/* au16OatBlowTempSpeedX_Tbl */
			{ 0x262U,0x26cU,0x280U,0x294U,0x29eU },				/* au16SiBlowTempGainX_Tbl */
			{ 0x3U,0x2U,0x0U,0x2U,0x3U },				/* au16SiBlowTempGainY1_Tbl */
			{ 0x3U,0x2U,0x0U,0x2U,0x3U },				/* au16SiBlowTempGainY2_Tbl */
			{ 0x3U,0x2U,0x0U,0x2U,0x3U },				/* au16SiBlowTempGainY3_Tbl */
			{ 0x2U,0x1U,0x0U,0x1U,0x2U },				/* au16SiBlowTempGainY4_Tbl */
			{ 0x12cU,0x1c2U,0x258U,0x2eeU },				/* au16BlowTempOatX_Tbl */
			{ 0x230U,0x244U,0x258U,0x26cU,0x280U,0x294U,0x2a8U,0x2bcU,0x2d0U },				/* au16MmiToCcsSetTempX_Tbl */
			{ 0x212U,0x230U,0x24eU,0x26cU,0x28aU,0x2a8U,0x2c6U,0x2e4U,0x302U },				/* au16MmiToCcsSetTempY_Tbl */
			{ 0x1f4U,0x230U,0x258U,0x280U,0x2a8U,0x2d0U,0x30cU },				/* au16DrTsetBlowTempGainX_Tbl */
			{ 0x0U,0x0U,0x0U,0x0U,0x0U,0x0U,0x0U },				/* au16DrTsetBlowTempGainY1_Tbl */
			{ 0x0U,0x0U,0x0U,0x0U,0x0U,0x0U,0x0U },				/* au16DrTsetBlowTempGainY2_Tbl */
			{ 0x0U,0x0U,0x0U,0x0U,0x0U,0x0U,0x0U },				/* au16DrTsetBlowTempGainY3_Tbl */
			{ 0x0U,0x0U,0x0U,0x0U,0x0U,0x0U,0x0U },				/* au16DrTsetBlowTempGainY4_Tbl */
			{ 0x1f4U,0x230U,0x258U,0x280U,0x2a8U,0x2d0U,0x30cU },				/* au16PsTsetBlowTempGainX_Tbl */
			{ 0x1U,0x1U,0x1U,0x0U,0x1U,0x1U,0x1U },				/* au16PsTsetBlowTempGainY1_Tbl */
			{ 0x1U,0x1U,0x1U,0x0U,0x1U,0x1U,0x1U },				/* au16PsTsetBlowTempGainY2_Tbl */
			{ 0x1U,0x1U,0x1U,0x0U,0x1U,0x1U,0x1U },				/* au16PsTsetBlowTempGainY3_Tbl */
			{ 0x1U,0x1U,0x1U,0x0U,0x1U,0x1U,0x1U },				/* au16PsTsetBlowTempGainY4_Tbl */
		},
		{  /* Macro */
			0x14U,				/* u16OatHysteresis */
			0x1f4U,				/* u16SetTempLowForIct */
			0x320U,				/* u16SetTempHighForIct */
			0x5U,				/* u8BlowoutTempFilterK */
			0x1U,				/* u8SetTempWeightDr */
		},
		0x1eU,				 /* u8AddChkSum */
		0x94U,				 /* u8XorChkSum */
	},
};




/**********************************End Of File*****************************************
*************************CCS_CFG_C ****************************
***************************************************************************************/
