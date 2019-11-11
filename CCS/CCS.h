
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

#ifndef CCS_H
#define CCS_H

#include "CCS_Cfg.h"             
#include "CCS_Type.h" 

/*define the temperature range*/
#define CCS_TempDiff_IMAX				(int16)640
#define CCS_TempDiff_IMIN				(int16)(-640)

#define CCS_TempDiff_UMAX				(uint16)(640*2)
#define CCS_TempDiff_UMIN				(uint16)(0)

#define CCS_Temp_MAX					(uint16)((120+40)*10)
#define CCS_Temp_MIN					(uint16)((-40+40)*10)

#define CCS_Temp_IMAX				(int16)400
#define CCS_Temp_IMIN				(int16)(-400)

/*this is for uint16 type variables*/
typedef enum CCS_enu16VarNumbers
{
	CCS_nu16ErrorCode = 0,			/*module error code*/

	CCS_nu16SetTempAvg,				/*The average target of setting temperature*/
	CCS_nu16SetTempDr,				/*The target of setting temperature of  the driver side*/
	CCS_nu16SetTempPs,				/*The target of setting temperature of  the passenger side*/

	CCS_nu16TempDiffAvg,			/*The average difference between target setting temperature and the corrected incar temperature.*/
	CCS_nu16TempDiffDr,	/*5*/		/*5 --The difference between setting temperature of driver side and the corrected incar temperature.*/
	CCS_nu16TempDiffPs,				/*The difference between setting temperature of driver side and the corrected incar temperature.*/

	CCS_nu16OatSetTempDiffDr,
	CCS_nu16OatSetTempDiffPs,
	
	CCS_nu16OatSetTempOffsetDr,
	CCS_nu16OatSetTempOffsetPs, /*10*/

	CCS_nu16OatBlwoutTempOffsetDr,
	CCS_nu16OatBlwoutTempOffsetPs,
	
	CCS_nu16SunBlwoutTempOffsetDr,
	CCS_nu16SunBlwoutTempOffsetPs,

	CCS_nu16SiBlwoutTempOffsetDr,/*15*/
	CCS_nu16SiBlwoutTempOffsetPs,

	CCS_nu16TsetBlwoutTempOffsetDr,
	CCS_nu16TsetBlwoutTempOffsetPs,

	CCS_nu16VelBlwoutTempOffset,
	
	CCS_nu16BlowoutTempDr,	/*20*/	/*20,The final target blowout temperature of driver side*/
	CCS_nu16BlowoutTempPs,			/*The final target blowout temperature of passenger side*/
	CCS_nu16BlowoutTempAvg,			/*The final average target blowout temperature*/

	CCS_nu16UnDampedBlwoutTempDr,	/*The undamped target blowout temperature of Driver side*/
	CCS_nu16UnDampedBlwoutTempPs,	/*The undamped target blowout temperature of passenger side*/
	CCS_nu16Max
}CCS_tenu16VarNumber;

/*this is for uint8 type variables*/
typedef enum CCS_enu8VarNumbers
{
	CCS_nu8SwVersion = 0,			/*The module SW version*/
	CCS_nu8Valid,					/*The valid flag of output.*/
	CCS_nu8SetTempValid,					/*only for cts,The valid flag of settemp,161220.*/
	CCS_nu8Max
}CCS_tenu8VarNumber;
  

#ifndef CCS_UseRTE
void CCS_vReset (void);      /* Reset Container*/
void CCS_vInit (void);    	/* StandbyActive Container */
void CCS_vDeinit (void);  	/* ActiveStandby Container */
void CCS_vMain (void);   	 /* On Container */
void CCS_vActive(void);		/*Active Container */
#endif
uint8 CCS_u8GetValue( CCS_tenu8VarNumber enIndex );
uint16 CCS_u16GetValue( CCS_tenu16VarNumber enIndex );
Std_ReturnType CCS_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);

  
#endif       

