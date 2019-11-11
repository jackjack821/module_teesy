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
#ifndef BCTL_H
#define BCTL_H

#ifdef BCTL
#ifndef ext
#define ext 
#endif
#else
#ifndef ext
#define ext extern
#endif
#endif

/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
#include "General.h"
/* Own headerfiles */
#include "Bctl_Type.h"
/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */


/*****************************************************************************
* EXPORT INTERFACE VARIABLE DEFINITIONS 
*
* In this section define
* - all variables will be accessed by other module.
******************************************************************************/

/*this is for uint16 type variables*/
typedef enum BCTL_enu16VarNumbers
{
    BCTL_nu16OatCcsSetTempVolOffsetDr=0,
    BCTL_nu16OatCcsSetTempVolOffsetPs,
    BCTL_nu16SiVolOffsetDr,
    BCTL_nu16SiVolOffsetPs,
    BCTL_nu16SunVolOffset,
    BCTL_nu16VelVolOffset,    
    BCTL_nu16CcsTrgVol,
    BCTL_nu16TrgVol,
    BCTL_nu16WuCdVolLmt,
    BCTL_nu16OatVolLmt,
    BCTL_nu16VolLmt,
    BCTL_nu16CcsTrgVlt,
    BCTL_nu16TrgVlt,
    BCTL_nu16SwVer,
    BCTL_nu16Max                     
}BCTL_tenu16VarNumber;

/*this is for uint8 type variables*/
typedef enum BCTL_enu8VarNumbers
{   
	BCTL_nu8DisplayInfo=0,
	BCTL_nu8Max
}BCTL_tenu8VarNumber;

/*****************************************************************************
* EXPORT INTERFACE FUNCTION PROTOTYPES
*
* In this section declare
* - all system global function prototypes of your module. This is a copy of the function 
*   definitions without the header template.
******************************************************************************/

ext void BCTL_vReset(void);	
ext void BCTL_vInit(void);
ext void BCTL_vDeinit(void);	
ext void BCTL_vActive(void);
ext void BCTL_vMain(void);	
ext void BCTL_vObdMain(void);	
ext uint8 BCTL_u8GetValue( BCTL_tenu8VarNumber enIndex );	
ext uint16 BCTL_u16GetValue(BCTL_tenu16VarNumber enIndex);
uint8 BCTL_u8ForceIoControl_Write(/*IN*/uint32 ForceIoControlWord);
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef BCTL_H*/

/*****************************************************************************
* EOF: Mac.h
******************************************************************************/

