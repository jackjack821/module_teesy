/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [BCTLDRV_Type, Type define for blower control  ]
*-----------------------------------------------------------------------------
  .FILE   [ BCTLDRV_Type.h                                                         ]
*-----------------------------------------------------------------------------

 Version Date        		Author                       Change                      
 -----------------------------------------------------------------------------
 Rev 01.00.01  2014/04/13     OuyangBihuan       	    	The first version               

*****************************************************************************/

#ifndef BCTLDRV_TYPE_H
#define BCTLDRV_TYPE_H

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/

/* System-headerfiles */
/*#include "General.h"*/
/* Please put the headerfiles which related to system here! */

/* Foreign headerfiles */

/* Please put the headerfiles which related to foreign here! */


/* Own headerfiles */
#include "BCTLDRV_PRIVATE.H"

/*****************************************************************************
* DEFINE DATA TYPE INTERNAL
*
* In this section
* - define all the private data types of this module.
******************************************************************************/

#if(BCTLDRV_nHW_RELAY_CTRL !=0U)    
typedef enum         
{
    BCTLDRV_u8InputBlwRelay	=	0U,
    BCTLDRV_nNumOfU8Inputs
}BCTLDRV_tenu8InputChannels;
#endif

typedef enum         
{
    BCTLDRV_u16InputBlwVolt	=	0U,
#if(BCTLDRV_nWITH_FEED_BACK!=0U)            
    BCTLDRV_u16InputPtaBlwFb,
#endif    
    BCTLDRV_nNumOfU16Inputs
}BCTLDRV_tenu16InputChannels;

 typedef enum
 {
    BCTLDRV_nInvalid=0u,
    BCTLDRV_nValid,
    BCTLDRV_nDefault,
    BCTLDRV_nLastValue
 }BCTLDRV_tenValueSts;

#if ((BCTLDRV_nWITH_FEED_BACK != 0U)&&(BCTLDRV_nUSE_ERR_DET != 0U)) 
typedef struct 
{
   uint8 biRealtime;
   uint8 biHappen;
   uint8 biComfirm;
   uint8 biOutputEn;
   uint8 u8RetryCounter;
   uint8 u8OutputTimer;
} BCTLDRV_tstErrStates;
#endif

typedef struct
{
    BCTLDRV_tenValueSts Sts;
    uint8 Val;
} BCTLDRV_tstU8InOutType;

typedef struct
{
    BCTLDRV_tenValueSts Sts;
    uint16 Val;
} BCTLDRV_tstU16InOutType;

typedef struct         
{
#if(BCTLDRV_nHW_RELAY_CTRL !=0U)    
    BCTLDRV_tstU8InOutType InBlwRelay;
#endif
    BCTLDRV_tstU16InOutType InBlwVolt;
#if(BCTLDRV_nWITH_FEED_BACK!=0U)    
    BCTLDRV_tstU16InOutType InPtaBlwFb;
#endif
}BCTLDRV_tstMainIn;


typedef struct         
{
    BCTLDRV_tstU16InOutType BlwPwmDuty;
    BCTLDRV_tstU16InOutType ErrSts;
#if(BCTLDRV_nWITH_FEED_BACK!=0U)  
    BCTLDRV_tstU16InOutType FbVolt;
#endif
}BCTLDRV_tstMainOut;

typedef BCTLDRV_tstMainOut BCTLDRV_tstMainBankOut;

typedef struct         
{
    BCTLDRV_tstU8InOutType InMmiBlwCtrl;
}BCTLDRV_tstCalDefTrgVolIn;

typedef struct         
{
    BCTLDRV_tstU16InOutType CcsTrgVol;
    BCTLDRV_tstU16InOutType TrgVol;    
    
}BCTLDRV_tstCalDefTrgVolOut;

typedef struct         
{
    BCTLDRV_tstU8InOutType InMmiBlwCtrl;
}BCTLDRV_tstCalManualTrgVolIn;

typedef struct         
{
    BCTLDRV_tstU16InOutType CcsTrgVol;
    BCTLDRV_tstU16InOutType TrgVol;    
    
}BCTLDRV_tstCalManualTrgVolOut;

typedef struct         
{
    const uint16 n16MinVal;            /*- Min value for this input. -*/
    const uint16 n16MaxVal;            /*- Max value for this input. -*/
    const uint16 n16Default;           /*- Default value for this input. -*/
    const uint8  n8ErrWaitTime;       /*- If the time is reached, nDefault would be used.-*/
    uint16 u16Last;
    uint8  u8ErrCounter;

}BCTLDRV_tstU16InputAttributes;

typedef struct
{
    BCTLDRV_tstU16InputAttributes *pstU16Attr;
    uint16 u16Input;
}BCTLDRV_tstU16InAttrType;


typedef struct         
{
    const uint8 n8MinVal;            /*- Min value for this input. -*/
    const uint8 n8MaxVal;            /*- Max value for this input. -*/
    const uint8 n8Default;           /*- Default value for this input. -*/
    const uint8  n8ErrWaitTime;       /*- If the time is reached, nDefault would be used.-*/
    uint8 u8Last;
    uint8 u8ErrCounter;

}BCTLDRV_tstU8InputAttributes;

typedef struct
{
    BCTLDRV_tstU8InputAttributes *pstU8Attr;
    uint8 u8Input;
}BCTLDRV_tstU8InAttrType;
/*
 typedef struct
{
    uint8   CcpCommandFlag;
    uint8   CcpCommand;
    uint16  CcpContronData;
}tstCcpContronType;
*/
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef BCTLDRV_TYPE_H */
/*****************************************************************************
* EOF: Mac_Type.h
******************************************************************************/

