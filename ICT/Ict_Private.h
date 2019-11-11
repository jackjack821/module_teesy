/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [Ict_Private, Private define for module ICT  ]
*-----------------------------------------------------------------------------
  .FILE   [ Ict_Private.h                                                         ]
*-----------------------------------------------------------------------------

 Version Date        		Author                       Change                      
 -----------------------------------------------------------------------------
 Rev 01.00.01  2014/04/13     OuyangBihuan       	    	The first version               

*****************************************************************************/

#ifndef ICT_PRIVATE_H
#define ICT_PRIVATE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */
/*#include "General.h"*/
/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */

#define ICT_SwVersion					(0x0100)

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
#if 0
#define ICT_u8GetPowValid()             1
#define ICT_u8GetSys1000Ms()			SYS_u8GetValue(SYS_nFlag1000MS_BG) //160811 Rte_IRead_Ict_vMain_Ict_SysFlag1000msBG_u8Flag()

#define ICT_u8GetCcsValid()			    Rte_IRead_Ict_vMain_Ict_CcsValid_u8Flag()
#define ICT_u16GetCcsSetTemp()			Rte_IRead_Ict_vMain_Ict_CcsSetTempDr_u16Temp()
#define ICT_u16GetCcsTempDiff()			CCS_u16GetValue(CCS_nu16TempDiffDr)//060811 CCS_u16GetValue(Num)

#define ICT_u8GetAirdValid()			1//AIRD_u8GetValue(Num)
#define ICT_u16GetAirdSetPos()		    Rte_IRead_Ict_vMain_Ict_AirdSetPos_u16MotorPos()

#define ICT_u8GetOatValid()			    Rte_IRead_Ict_vMain_Ict_OatValid_u8Flag()
#define ICT_u16GetOatValue()		    Rte_IRead_Ict_vMain_Ict_OatValue_u16Temp()

//#define ICT_u8GetRfaValid()			    1//RFA_u8GetValue(Num)
//#define ICT_u16GetSunRfaValue()			0//SUN_u16GetValue(Num)
#endif


/*************************Extern Module Interface End****************************/



/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#undef ICT_PRIVATE_H
#endif         
/*****************************************************************************
* EOF: Ict_Private.h
******************************************************************************/

