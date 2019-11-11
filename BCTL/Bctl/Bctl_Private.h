/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [Bctl, Blower control  ]
*-----------------------------------------------------------------------------
  .FILE   [ Bctl_Private.h                                                         ]
*-----------------------------------------------------------------------------

 Version 			Date        		Author              Change                      
 -----------------------------------------------------------------------------
 Rev 01.00.01  2014/04/13     OuyangBihuan       	    	The first version              

*****************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef BCTL_PRIVATE_H
#define BCTL_PRIVATE_H


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

#define BCTL_u8AirdDisInfo()        (AIRD_u8GetValue(AIRD_nu8Display))
#define BCTL_u8AcccDisInfo()        (1u)
#define BCTL_u8IgnEnableSig()       (1u)
#define BCTL_u8IstpEngStatus()      (0u)
#define BCTL_u8MmiSetTempDr()       (MMI_u8GetValue(MMI_nu8SetTempDr))
#define BCTL_u8MmiSetTempPs()       (MMI_u8GetValue(MMI_nu8SetTempPs))
#define BCTL_u8GetMmiBlwEvent()     (0u)
#define BCTL_u8GetMmiMode()		    (MMI_u8GetValue(MMI_nu8BlwModeControl))
#define BCTL_u8GetMmiCtrl()         (MMI_u8GetValue(MMI_nu8BlwControl))
#define BCTL_u8GetPowHighVolt()	    ((uint8)POW_u16GetValue(POW_nu16AppHighVoltage))
#define BCTL_u8GetPowLowVolt()	    ((uint8)POW_u16GetValue(POW_nu16AppLowVoltage))
#define BCTL_u16GetRfaDisInfo()		(RFA_u8GetValue(RFA_nu8Display))
#define BCTL_u16GetOatValue()		(OAT_u16GetValue(OAT_nu16Value))
#define BCTL_u16GetCcsSetTempAvg()	(CCS_u16GetValue(CCS_nu16SetTempAvg))
#define BCTL_u16GetCcsSetTempDr()   (CCS_u16GetValue(CCS_nu16SetTempDr))
#define BCTL_u16GetCcsSetTempPs()	(CCS_u16GetValue(CCS_nu16SetTempPs))
#define BCTL_u16GetCcsBlowoutTempAvg()	    (CCS_u16GetValue(CCS_nu16BlowoutTempAvg))
#define BCTL_u16GetCcsBlowoutTempDr()	    (CCS_u16GetValue(CCS_nu16BlowoutTempDr))
#define BCTL_u16GetCcsBlowoutTempPs()	    (CCS_u16GetValue(CCS_nu16BlowoutTempPs))
#define BCTL_u16GetCcsSiDr()            (CCS_u16GetValue(CCS_nu16TempDiffDr))
#define BCTL_u16GetCcsSiPs()            (CCS_u16GetValue(CCS_nu16TempDiffPs))
#define BCTL_u16GetEvaValue()           (EVAP_u16GetValue(EVAP_nu16AcValue))
#define BCTL_u16GetHctValue()           (HCT_u16GetValue(HCT_nu16Value))
#define BCTL_u16GetSunValueDr()           (SUN_u16GetValue(SUN_nu16ValueDr))
#define BCTL_u16GetSunValuePs()           (SUN_u16GetValue(SUN_nu16ValuePs))
#define BCTL_u16GetVelValue()           (VEL_u16GetValue(VEL_nu16Velocity))

/*************************Extern Module Interface End****************************/

/**************************Internal Module Interface*******************************/
#define BCTL_nLimitTempMin  (5000U)  /*0 DegreeC*/
#define BCTL_nLimitTempMax  (5880U) /*88 DegreeC*/
#define RangeCheck(input,minvalue,maxvalue)	((input)<(minvalue)?(minvalue):(input)>(maxvalue)?(maxvalue):(input))
#define BCTL_vCalMax(a,b)               ((a)>(b)?(a):(b))
#define BCTL_vCalMin(a,b)               ((a)>(b)?(b):(a))

/*************************Internal Module Interface End****************************/


/***************************No Config Parameter********************************/
/*here will define the macro which not to be changed for ever*/
#define BCTL_nUseForDebug           False

/*************************No Config Parameter End******************************/

#define BCTL_nMAX_AC_CONTROL    (1)
#define BCTL_nAUTO_BLOWER_CONTROL (1)
#define BCTL_nUseCCP    (1)
#define BCTL_nUseRTE    (1)

#define BCTL_nSunSensorNum (2)
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef BCTL_PRIVATE_H*/

/*****************************************************************************
* EOF: Mac.h
******************************************************************************/

