/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [Bctl, Blower control  ]
*-----------------------------------------------------------------------------
  .FILE   [ Bctl.h                                                         ]
*-----------------------------------------------------------------------------

 Version 			Date        		Author              Change                      
 -----------------------------------------------------------------------------
 Rev 01.00.01  2014/04/13     OuyangBihuan       	    	The first version              

*****************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef BCTLDRV_H
#define BCTLDRV_H

/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */
#include "BCTLDRV_Cfg.h" 
/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */
#define   BCTLDRV_nUSE_ERR_DET              (1U)    /**/
#define   BCTLDRV_nWITH_FEED_BACK           (1U)    /**/
#define   BCTLDRV_nHW_RELAY_CTRL            (0U)    /**/

/*****************************************************************************
* EXPORT INTERFACE VARIABLE DEFINITIONS 
*
* In this section define
* - all variables will be accessed by other module.
******************************************************************************/

/*this is for uint16 type variables*/
typedef enum BCTLDRV_enu16VarNumbers
{
    BCTLDRV_nu16Error=0U,    
    BCTLDRV_nu16PwmDuty,
    BCTLDRV_nu16SwVersion,   
#if (BCTLDRV_nWITH_FEED_BACK != 0U)     
    BCTLDRV_nu16VoltFeedback,
    BCTLDRV_nu16VoltFeedbackRaw,
#endif	
    BCTLDRV_nu16Max                     
}BCTLDRV_tenu16VarNumber;

/*this is for uint8 type variables*/
typedef enum BCTLDRV_enu8VarNumbers
{   
	BCTLDRV_nu8SwVersion=0U,      
	BCTLDRV_nu8Max
}BCTLDRV_tenu8VarNumber;

/*****************************************************************************
* EXPORT INTERFACE FUNCTION PROTOTYPES
*
* In this section declare
* - all system global function prototypes of your module. This is a copy of the function 
*   definitions without the header template.
******************************************************************************/

 void BCTLDRV_vReset(void);	
 void BCTLDRV_vInit(void);
 void BCTLDRV_vDeinit(void);	
 void BCTLDRV_vMain(void);	
 void BCTLDRV_vObdMain(void);	
 uint8 BCTLDRV_u8GetValue( BCTLDRV_tenu8VarNumber enIndex );	
 uint16 BCTLDRV_u16GetValue(BCTLDRV_tenu16VarNumber enIndex);
 void BCTLDRV_vDrvMain(void);	

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef BCTLDRV_H*/

/*****************************************************************************
* EOF: Mac.h
******************************************************************************/

