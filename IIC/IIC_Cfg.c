/*******************************************************************************************/
/*===================== COPYRIGHT (C) HUIZHOU DESAY SV AUOTMOTIVE 2018 ====================*/ 
/*******************************************************************************************
* C Source     : SIIC_Cfg.c
*
* Description  : Source file for IIC module which belongs to App Layer.
*
* Environment  : autosar 4.x SC1, Renesas RH850, Greenhills Multi 6.1.6
*
* Created_by   : R2S Platform team, BIC R&D 
*
* Template name: SIIC_Cfg.c
*
*    Rev 1.1.0   xx-xx-xx,  hxr                                   
*    Initial revision.
*
********************************************************************************************/

/*******************************************************************************************
* FILE DECLARATION
********************************************************************************************/
#define IIC_CFG_C 				/* Name of the Module */

/*******************************************************************************************
* HEADER-FILES (Only those that are needed in this file)
********************************************************************************************/

/* System-headerfiles */
//#include "r_typedefs.h" 			/* General definitions and datatypes */


/* Own headerfiles */
#include "IIC_Cfg.h" 			/* Inclusion the head file of this module */


/*******************************************************************************************
* CONFIG SERVICE
*
* In this section list
* - all interrupt service routine in your module.
********************************************************************************************/
/*################################################
	############################################
	
			SIIC module configeration
			
	############################################	
################################################*/
/*device config*/
struct SiicDev SiicDevConfig[Siic_Dev_Max] = 
{
	{Siic_Dev_0, MCU_mPinID_P10_3,MCU_mPinID_P10_2,SIIC_DEV_PIN_NOUSED,SIIC_NotReady},//dev0
//	{Siic_Dev_1, MCU_mPinID_P0_12,MCU_mPinID_P0_11,MCU_mPinID_P0_13, SIIC_NotReady},//dev1
//	{Siic_Dev_1, MCU_mPinID_P10_10,MCU_mPinID_P10_11,SIIC_DEV_PIN_NOUSED, SIIC_NotReady},//dev1
};

/*channel config */
/*const */struct SiicChn SiicChnConfig[Siic_Chn_Max] = 
{
	{&SiicDevConfig[Siic_Dev_0], SLAVE_ADDRESS_NOINIT}, //chn0
//	{&SiicDevConfig[Siic_Dev_1], SLAVE_ADDRESS_NOINIT}, //chn1
//	{&SiicDevConfig[Siic_Dev_1], SLAVE_ADDRESS_NOINIT}, //chn1
};


/*******************************************************************************************
* EOF: IIC_Cfg.c
********************************************************************************************/

