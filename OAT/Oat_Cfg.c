/**************************************************************************************/
/*------------------------------------------------------------------------------------
              Automatically Generated File,do not edit this file manually!
-------------------------------------------------------------------------------------*/
/** Generated On : 2017/10/27 11:44:26                                      */
/**           By : uidp4501                                      */
/**        Using : OAT.xml                         */
/**         From : D:\HVACProject\Geely\FE-5DB&7DA\ProjectCode\01_APP\OAT                             */
/**               (D = )                                                    */
/**************************************************************************************/

/**************************************************************************************
 Module Name : OAT
 File Name : OAT_Cfg.c
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
#define OAT_CFG

/*Header file */
#include "OAT_Cfg.h"

/***************************************************************************************
*MODULE GLOBAL CONFIGURATION CONSTANTS
* In this section define
* - constants and macros to configure your module. These constants are unknown for other
*   modules
***************************************************************************************/



const OAT_tstRomLayout OAT_stRomLayout = {
	{  /*----------------------- Group1 ---------------------------------------*/
		{  /* ModuleInfo */
			{ 0x15eU,0x1f4U,0x28aU,0x320U },				/* au16OatDiffHctToUpdate_X */
			{ 0x258U,0x1f4U,0x190U,0x12cU },				/* au16OatDiffHctToUpdate_Y */
			{ 0x15eU,0x1f4U,0x28aU,0x320U },				/* au16OatLimitHctToUpdate_X */
			{ 0x258U,0x2bcU,0x320U,0x384U },				/* au16OatLimitHctToUpdate_Y */
			{ 0x37U,0x68U,0xbcU,0xfaU,0x14bU,0x1adU,0x21cU,0x290U,0x2fbU,0x379U },				/* au16OatSensorAmbient_X */
			{ 0x4b0U,0x3e8U,0x320U,0x2bcU,0x258U,0x1f4U,0x190U,0x12cU,0xc8U,0x32U },				/* au16OatSensorAmbient_Y */
			{ 0x50U,0xcbU,0x163U,0x1c8U,0x239U,0x2aaU,0x311U,0x364U,0x3a1U,0x3d8U },				/* au16OatAqsPtaAmbient_X */
			{ 0x4b0U,0x3e8U,0x320U,0x2bcU,0x258U,0x1f4U,0x190U,0x12cU,0xc8U,0x32U },				/* au16OatAqsPtaAmbient_Y */
		},
		0x85U,				 /* u8AddChkSum */
		0xf3U,				 /* u8XorChkSum */
	},
};




/**********************************End Of File*****************************************
*************************OAT_CFG_C ****************************
***************************************************************************************/
