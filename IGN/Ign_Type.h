/*******************************************************************************
| Module Name: KL15 manage model
| File Name: ign_type.h
|
|-------------------------------------------------------------------------------
|				C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2015 Huizhou Desay SV Automotive Co., Ltd.	  All rights reserved.
|
| This software is copyright protected and proprietary to Desay SV Automotive Co., Ltd.
| Desay SV Automotive Co., Ltd grants to you only those rights as set out in the
| license conditions. All other rights remain with Desay SV Automotive Co., Ltd.
|
| REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
|-------------------------------------------------------------------------------
|				A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Name									Company
| --------------------- 	---------------------------------------
| Sui Yanchun						 Desay SV Automotive Co., Ltd
| Du Zejia							   Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|				R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date			   Ver			Author				 Description
| ----------  -------  -------------  -------------------------------------------------
| 
|2014/07/28 	Rev 01.00.00	  LN				 The first version	 
********************************************************************************/

#ifndef IGN_TYPE_H
#define IGN_TYPE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */




/*****************************************************************************
* EXPORT INTERFACE DEFINITIGNS AND DECLARATIGNS
*
* In this sectIGN
* - define all type definitIGNs of your module.
******************************************************************************/

/*define the Num. of variable that will be used by other modules.*/

typedef enum{	
		
		IGN_nu16KeyPos=0,		
		IGN_nu16Off2OnFlag,
		IGN_nu16On2OffFlag,
		IGN_nu16Off2OnFlag2,
		IGN_nu16On2OffFlag2,
		IGN_nu16Off2OnOrLeaveCrankDelayFlag,
		IGN_nu16IGN2IoStatus,		// ign2
		IGN_nu16IGN2Fb,		
		IGN_nu16IGN1IoStatus,		// ign1
		IGN_nu16IGN1Fb,
		IGN_nu16IgnStable,
		IGN_nu16IgnStaticOn,			
		IGN_nu16SwVersion,
		IGN_nu16ErrorCode,		
		IGN_nu16RemoteIoStatus,		
		IGN_nu16Max
	}IGN_tenu16VarNum;





/*****************************************************************************
* End of check if informatIGNs are already included
******************************************************************************/
#endif                                  /* ifndef IGN_TYPE_H */
/*****************************************************************************
* EOF: IGN_Type.h
******************************************************************************/

