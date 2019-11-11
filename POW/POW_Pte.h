/*******************************************************************************
| Module Name: Power manage model
| File Name: pow.h
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
| Du Zejia                             Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver        	Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 
|2014/08/01 Rev 01.00.00      Syc       			 The first version  
********************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef POW_Pte_H
#define POW_Pte_H


/*internal data macro definition*/
#define get_bPowInternalDataAppHighVoltage()      		(POW_u16InternalDataAppHighVoltage)
#define clr_bPowInternalDataAppHighVoltage()        		(POW_u16InternalDataAppHighVoltage=0U)
#define set_bPowInternalDataAppHighVoltage(val)         (POW_u16InternalDataAppHighVoltage=(val))

#define get_bPowInternalDataAppLowVoltage()      		(POW_u16InternalDataAppLowVoltage)
#define clr_bPowInternalDataAppLowVoltage()        		(POW_u16InternalDataAppLowVoltage=0U)
#define set_bPowInternalDataAppLowVoltage(val)         (POW_u16InternalDataAppLowVoltage=(val))

#define get_bPowInternalDataComHighVoltage()      		(POW_u16InternalDataComHighVoltage)
#define clr_bPowInternalDataComHighVoltage()        	(POW_u16InternalDataComHighVoltage=0U)
#define set_bPowInternalDataComHighVoltage(val)         (POW_u16InternalDataComHighVoltage=(val))

#define get_bPowInternalDataComLowVoltage()      		(POW_u16InternalDataComLowVoltage)
#define clr_bPowInternalDataComLowVoltage()        		(POW_u16InternalDataComLowVoltage=0U)
#define set_bPowInternalDataComLowVoltage(val)         (POW_u16InternalDataComLowVoltage=(val))

#define get_bPowInternalDataDiagHighVoltage()      		(POW_u16InternalDataDiagHighVoltage)
#define clr_bPowInternalDataDiagHighVoltage()        	(POW_u16InternalDataDiagHighVoltage=0U)
#define set_bPowInternalDataDiagHighVoltage(val)         (POW_u16InternalDataDiagHighVoltage=(val))

#define get_bPowInternalDataDiagLowVoltage()      		(POW_u16InternalDataDiagLowVoltage)
#define clr_bPowInternalDataDiagLowVoltage()        		(POW_u16InternalDataDiagLowVoltage=0U)
#define set_bPowInternalDataDiagLowVoltage(val)         (POW_u16InternalDataDiagLowVoltage=(val))

#if(Ref4_CheckVoltage==1)
#define get_bPowInternalDataRef4HighVoltage()      		(POW_u16InternalDataRef4HighVoltage)
#define clr_bPowInternalDataRef4HighVoltage()        	(POW_u16InternalDataRef4HighVoltage=0U)
#define set_bPowInternalDataRef4HighVoltage(val)         (POW_u16InternalDataRef4HighVoltage=(val))

#define get_bPowInternalDataRef4LowVoltage()      		(POW_u16InternalDataRef4LowVoltage)
#define clr_bPowInternalDataRef4LowVoltage()        		(POW_u16InternalDataRef4LowVoltage=0U)
#define set_bPowInternalDataRef4LowVoltage(val)         (POW_u16InternalDataRef4LowVoltage=(val))
#endif

#define get_bPowInternalDataAdValid()      				(POW_u16InternalDataAdValid)
#define clr_bPowInternalDataAdValid()        			(POW_u16InternalDataAdValid=0U)
#define set_bPowInternalDataAdValid(val)         		(POW_u16InternalDataAdValid=(val))


#define get_bPowInternalDataRawK30VoltFb()  			(POW_u16IDHalK30Fb)

#define get_bPowInternalDataResultK30VoltFb()      		(POW_u16InternalDataK30VoltFb)
#define clr_bPowInternalDataResultK30VoltFb()        	(POW_u16InternalDataK30VoltFb=0U)
#define set_bPowInternalDataResultK30VoltFb(val)         (POW_u16InternalDataK30VoltFb=(val))


#define get_bPowInternalDataRawIGN2VoltFb() 			(POW_u16IDHalIgn2Fb)

#define get_bPowInternalDataResultIGN2VoltFb()      	(POW_u16InternalDataIGN2VoltFb)
#define clr_bPowInternalDataResultIGN2VoltFb()        	(POW_u16InternalDataIGN2VoltFb=0U)
#define set_bPowInternalDataResultIGN2VoltFb(val)         (POW_u16InternalDataIGN2VoltFb=(val))

#define get_bPowInternalDataSwVersion()      			(POW_u16InternalDataSwVersion)
#define clr_bPowInternalDataSwVersion()        			(POW_u16InternalDataSwVersion=0U)
#define set_bPowInternalDataSwVersion(val)         		(POW_u16InternalDataSwVersion=(val))

#define get_bPowInternalDataErrorCode()      			(POW_u16InternalDataErrorCode)
#define clr_bPowInternalDataErrorCode(val)        		(POW_u16InternalDataErrorCode&=(val))
#define set_bPowInternalDataErrorCode(val)         		(POW_u16InternalDataErrorCode|=(val))

#define POW_Set5vShortGnd		do{set_bPowInternalDataErrorCode(0x0001);}while(0) 
#define POW_Clr5vShortGnd		do{clr_bPowInternalDataErrorCode(0xfffe);}while(0) 

#define get_bPowInternalData5vOutputStable()      		(POW_u16InternalData5vOutputStable)
#define clr_bPowInternalData5vOutputStable()        		(POW_u16InternalData5vOutputStable=0U)
#define set_bPowInternalData5vOutputStable(val)         	(POW_u16InternalData5vOutputStable=(val))

#define get_bPowInternalData5vOutputFb()      			(POW_u16InternalData5vOutputFb)
#define clr_bPowInternalData5vOutputFb()        			(POW_u16InternalData5vOutputFb=0U)
#define set_bPowInternalData5vOutputFb(val)         		(POW_u16InternalData5vOutputFb=(val))





/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef POW_H */

/*****************************************************************************
* EOF: Pow.h
******************************************************************************/

