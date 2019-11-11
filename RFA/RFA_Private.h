/*******************************************************************************
| Module Name: Recirculation Fresh Air Private definition
| File Name: RFA_Private.h
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
| Luo Xindian                             Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2015-10-15    1.0  Luo Xindian		 frist created 
| 2016-2-18      1.1  Luo Xindian		Modified for KC-2
| 2016-7-1      1.2   Luo Xindian		Modifed for base code
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef RFA_PRIVATE_H
#define RFA_PRIVATE_H


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

/**************************Extern Module Interface*******************************/

/*************************Extern Module Interface End****************************/

/***************************No Config Parameter********************************/
//here will define the macro which not to be changed for ever
#define RFA_nUseForDebug				False

#define RFA_OpenInterfaces_Cfg   (Yes)  /* Yes is to open Getvalue and GetBuffer interfaces*/

#if(RFA_biIsMotorFBValid == True)
#define RFA_u8BreathPos	RFA_u8RecPosPercent75//RFA_u8FreshPos//700		// fill the exprerience value and it need not set to full fresh position,void to siwth between recirc and fresh
#else
#define RFA_u8BreathPos	RFA_u8FreshPos
#endif

#if (RFA_biSystemState == False)
#define RFA_u16FreshPosition				(0)
#define RFA_u16RecircPosition				(1000)
#endif

#if (RFA_biAQS_Cfg == True)
#define AQS_u8AirBad 				(2)
#define AQS_u8Initing 				(0)
#define RFA_u8FreReqDelay		10 /*sencond*/	
#endif

#define RFA_i16PM25DiffLo		(-10)
#define RFA_i16PM25DiffHi		(10)

#define RFA_nBreathEnableAmbientTemp (700)
/*************************No Config Parameter End******************************/
#if(RFA_nUseCCP ==True)

#define RfaGetCcpForceBit(index)	((RFA_CcpForceFlag>>index)&0x01u)
#define RfaSetCcpForceBit(index)	(RFA_CcpForceFlag=RFA_CcpForceFlag|(0x01u<<index))
#define RfaClrCcpForceBit(index)	(RFA_CcpForceFlag=RFA_CcpForceFlag&(~(0x01u<<index)))
#define RfaClrCcpForceByte()	    (RFA_CcpForceFlag=0u)

#endif

#define RFA_nSwVersion				(0x0000)
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef RFA_PRIVATE_H*/

/*****************************************************************************
* EOF: RFA.h
******************************************************************************/
