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
#ifndef BCTLDRV_PRIVATE_H
#define BCTLDRV_PRIVATE_H


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
/***************************No Config Parameter********************************/
/*Here will define the macro which not to be changed for ever******************/
#define   BCTLDRV_nUseRTE                   (1U)
#define   BCTLDRV_nUseForDebug				(0U)
#define   BCTLDRV_nUseCCP                   (1U)
/*************************No Config Parameter End******************************/

/**************************Extern Module Interface*******************************/
#define    BCTLDRV_u8GetBlwCanRelay()         (1U)/*-Test Value. Please fill with input.-*/
#define    BCTLDRV_u16GetBctlVolt()           (BCTL_u16GetValue(BCTL_nu16TrgVlt))/*-Test Value. Please fill with input.-*/
#define    BCTLDRV_u16HalGetBlowerFb(Value)        (Rte_Call_IoHwAd_IoHwAd_ReadAd_BctlDrvBlowerFb_Read(Value))
#define    BCTLDRV_u16SetPwmDuty(Value)        Rte_Call_IoHwPwm_IoHwPwm_SetPwmDuty_BctlDrvBlowerOutput_Set(Value)
/*************************Extern Module Interface End****************************/

/*****************************************************************************
* INTERNAL INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define helpful macros for easy data access and for a comfortable function use, if 
*   necessary.
* - define all macros for accessing the internal module interfaces variables
* - define all macros which not need to be configed and changed for this module 
******************************************************************************/

/**************************Internal Module Interface*******************************/
#define BCTLDRV_nDrvErrMask             (0x0001U)    /**/
#define BCTLDRV_nFbErrMask              (0x0002U)    /**/
#define BCTLDRV_nInputErrMaskCan        (0x0004U)
#define BCTLDRV_nInputErrMaskBctl       (0x0008U)
#define BCTLDRV_nInputErrMaskHal        (0x0010U)
#define BCTLDRV_nInputErrMask           (0xFFE3U)

#define   BCTLDRV_nDrvErrorRecoverTime  (50U)    /**/
#define   BCTLDRV_nDrvErrorRecordTime   (50U)    /**/
#define   BCTLDRV_nRetryLimit           (8U)    /**/
#define   BCTLDRV_nPwmDutyLimitMin      (69U)    /**/
#define   BCTLDRV_nPwmDutyLimitMax      (990U)    /**/
#define   BCTLDRV_nFbFilterFactor       (2U)    /**/
#define   BCTLDRV_nPwmFrequence         (2000U)    /**/
/****************************************************************
Blower Hareware config
****************************************************************/
#define BCTL_PPG_ID				        HAL_BlowerPpgID
#define BCTL_OutPutFrequency	        BCTLDRV_nPwmFrequence		
#define BCTL_OutPutDuty(duty)	        HAL_vPPGSetHZ(BCTL_PPG_ID, BCTL_OutPutFrequency,(duty))
#define BCTL_RelayCtrlOnOffCfg(OnOff)	HAL_PinWrite(PORT_ID_4, PIN_ID_5, (OnOff))

/****************************************************************
Blower Software config
****************************************************************/


/*************************Internal Module Interface End****************************/

/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef BCTLDRV_PRIVATE_H*/

/*****************************************************************************
* EOF: Mac.h
******************************************************************************/

