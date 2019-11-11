/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [Bctl, Blower control  ]
*-----------------------------------------------------------------------------
  .FILE   [ Bctl.c                                                         ]
*-----------------------------------------------------------------------------

 Version 			Date        Author                       Change                      
 -----------------------------------------------------------------------------     
 Rev 01.00.01  2014/04/13     OuyangBihuan       	    	The first version                  

*****************************************************************************/

/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/
#define BCTLDRV                          /* Name of the Module                */

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
/* System-headerfiles */
#include "General.h"

/* Foreign headerfiles */
#include "Alg.h "
#include "Bctl.h"
#include "RTE_Internal.h" 
/* Please put the headerfiles which related to foreign here! */

/* Own headerfiles */
#include "BCTLDRV.h" 
#include "BCTLDRV_Private.h" 
#include "BCTLDRV_Type.h"
#include "BCTLDRV_Interface.h"


/* Please put the headerfiles which related to own here! */


/*****************************************************************************
* GLOBAL DEFINITIONS
*
* In this section define
* - all global ROM-CONSTants of your module
* - all global variables of your module
*****************************************************************************/

/* example1: Global ROM-constants
   ----------------------------------------------------- */

/* example2: Global Variables
   ----------------------------------------------------- */

static BCTLDRV_tstMainOut BCTLDRV_stMainOut;

#if (BCTLDRV_nWITH_FEED_BACK != 0U) 
static uint32 BCTLDRV_u32FbFilterBuffer;

#if (BCTLDRV_nUSE_ERR_DET != 0U)
static BCTLDRV_tstErrStates BCTLDRV_stErr; 
#endif

#endif

/*****************************************************************************
* FILE LOCAL DEFINITIONS
*
* In this section define
* - all file local define-CONSTants
* - all file local ROM-CONSTants (STATIC)
* - all file local variables (STATIC)
*****************************************************************************/
/* example1: Local Define-constants
   ----------------------------------------------------- */

/*****************************************************************************
* FILE LOCAL FUNCTION DECLARE
*
* In this section declare
* - all file functions used internal of this module 
*****************************************************************************/
static uint16   BCTLDRV_u16CalPwmDuty(uint16 u16Volt);
#if (BCTLDRV_nWITH_FEED_BACK != 0U)
static uint16 BCTLDRV_u16CalFbVolt(uint16 u16AdRaw);
#endif
#if ((BCTLDRV_nWITH_FEED_BACK != 0U)&&(BCTLDRV_nUSE_ERR_DET != 0U))
static void BCTLDRV_vErrorCheck(uint16 u16PwmDuty, uint16 u16FbDuty, BCTLDRV_tstErrStates *pstErrSts);
static void BCTLDRV_vErrorHandle(BCTLDRV_tstErrStates stErrSts, uint16 *pu16PwmDuty, uint16 *pu16Err);
#endif
#if ((BCTLDRV_nWITH_FEED_BACK != 0U)&&(BCTLDRV_nUSE_ERR_DET != 0U))
static void BCTLDRV_vErrorCheck (uint16 u16PwmDuty, uint16 u16FbDuty, BCTLDRV_tstErrStates *pstErrSts)
{
    /*************************************************************************/
    if(pstErrSts->biComfirm == 1U)
    {
        pstErrSts->biHappen = 1U;
        pstErrSts->biRealtime = 1U;
        pstErrSts->biOutputEn = 0U;
        pstErrSts->u8OutputTimer = 0U;
        pstErrSts->u8RetryCounter = 0U;
    }
    else
    {
        if(pstErrSts->biOutputEn == 0U)
        {
            if(pstErrSts->u8OutputTimer < BCTLDRV_nDrvErrorRecoverTime)
            {
                pstErrSts->u8OutputTimer ++;
            }
            else
            {   
                if(pstErrSts->u8RetryCounter < BCTLDRV_nRetryLimit)   
                {
                    pstErrSts->u8OutputTimer = 0U;
                    pstErrSts->biOutputEn = 1U;

                    pstErrSts->u8RetryCounter++;
                }
                else
                {
                    pstErrSts->biComfirm =1U;
                }
            }
        }
        else
        {
            if((u16PwmDuty >200U/*- Blower is ON , and the voltage is bigger than 3V.-*/)
                &&(u16FbDuty < 166U/*- Blower voltage <2.5V-*/))
            {
                pstErrSts->biRealtime=1U;
                if(pstErrSts->u8OutputTimer < BCTLDRV_nDrvErrorRecordTime)
                {
                    pstErrSts->u8OutputTimer ++;
                }
                else
                {
                    pstErrSts->biHappen = 1U;
                    pstErrSts->biOutputEn = 0U;
                    pstErrSts->u8OutputTimer = 0U;
                }
            }
            else
            {
                pstErrSts->biRealtime=0U;
                pstErrSts->u8OutputTimer = 0U;
                pstErrSts->biHappen = 0U;
                pstErrSts->biOutputEn = 1U; 
                pstErrSts->u8RetryCounter = 0U;
            }
        }
    } 
 
}

static void BCTLDRV_vErrorHandle(BCTLDRV_tstErrStates stErrSts, uint16 *pu16PwmDuty, uint16 *pu16Err)
{
    if(stErrSts.biHappen)
    {
        *pu16Err |= BCTLDRV_nDrvErrMask; 
    }
    else
    {
        *pu16Err &= ~BCTLDRV_nDrvErrMask;
    }

    if(stErrSts.biOutputEn == 0U)
    {
        //*pu16PwmDuty = 0U;
    }
    else
    {

    }
}
#endif 

#if (BCTLDRV_nWITH_FEED_BACK != 0U)
/* ===========================================================================
* Function   : static uint16 BCTLDRV_u16CalFbVolt(uint16 u16AdRaw)
* Description: need to add description
*              
*              
* Takes      : Nothing
* Returns    : Nothing
*/
static uint16 BCTLDRV_u16CalFbVolt(uint16 u16AdRaw)
{
    uint16 u16Ret;
    
    u16Ret = 
        ALG_u16FirstOrderFilter
            (&BCTLDRV_u32FbFilterBuffer,u16AdRaw, BCTLDRV_nFbFilterFactor);  
    
	u16Ret = 
    	ALG_cu16CurveLookup_16_16_Limit
    	    (BCTLDRV_au16RomFbDigital, BCTLDRV_au16RomFbVolt, u16Ret, BCTLDRV_nFbVolt_Len);      

    return(u16Ret);
	
}
#endif
/* ===========================================================================
* Function   : static uint16   BCTLDRV_u16CalPwmDuty(void)
* Description: need to add description
*              
*              
* Takes      : Nothing
* Returns    : Nothing
*/
static uint16   BCTLDRV_u16CalPwmDuty(uint16 u16Volt)
{
    uint16 u16Ret;
    u16Ret = 
           ALG_cu16CurveLookup_16_16_Limit(
                BCTLDRV_au16RomTrgVolt,
                    BCTLDRV_au16RomPwmDuty,
                        u16Volt,
                            BCTLDRV_nVolt2Pwm_Len);
    
    if(u16Ret < BCTLDRV_nPwmDutyLimitMin)
    {
        u16Ret = 0U;
    }
    else if(u16Ret > BCTLDRV_nPwmDutyLimitMax)
    {
        u16Ret = 1000U;
    }
    else
    {

    }
    return(u16Ret);
}

void BCTLDRV_vReset(void)
{
    BCTLDRV_stMainOut.BlwPwmDuty.Sts = BCTLDRV_nInvalid;
    BCTLDRV_stMainOut.ErrSts.Sts= BCTLDRV_nInvalid;
    BCTLDRV_stMainOut.BlwPwmDuty.Val = 0U;
    BCTLDRV_stMainOut.ErrSts.Val = 0U;
#if (BCTLDRV_nWITH_FEED_BACK != 0U)   
    BCTLDRV_u32FbFilterBuffer = 0U;
    BCTLDRV_stMainOut.FbVolt.Sts= BCTLDRV_nInvalid;
    BCTLDRV_stMainOut.FbVolt.Val = 0xFFFFU;
#if (BCTLDRV_nUSE_ERR_DET != 0U)
    BCTLDRV_stErr.biHappen = 0U;
    BCTLDRV_stErr.biRealtime = 0U;
    BCTLDRV_stErr.biOutputEn = 1U;
    BCTLDRV_stErr.biComfirm = 0U;
    BCTLDRV_stErr.u8OutputTimer = 0U;
    BCTLDRV_stErr.u8RetryCounter = 0U;
#endif
#endif
    BCTLDRV_u16SetPwmDuty(0u);
#if(BCTLDRV_nHW_RELAY_CTRL !=0U)
    BCTL_RelayCtrlOnOffCfg(0U);
#endif
}
void BCTLDRV_vInit(void)
{
    BCTLDRV_stMainOut.BlwPwmDuty.Sts = BCTLDRV_nInvalid;
    BCTLDRV_stMainOut.ErrSts.Sts= BCTLDRV_nInvalid;
    BCTLDRV_stMainOut.BlwPwmDuty.Val = 0U;
    BCTLDRV_stMainOut.ErrSts.Val = 0U;
#if (BCTLDRV_nWITH_FEED_BACK != 0U)   
    BCTLDRV_u32FbFilterBuffer = 0U;
    BCTLDRV_stMainOut.FbVolt.Sts= BCTLDRV_nInvalid;
    BCTLDRV_stMainOut.FbVolt.Val = 0xFFFFU;
#if (BCTLDRV_nUSE_ERR_DET != 0U)
    BCTLDRV_stErr.biHappen = 0U;
    BCTLDRV_stErr.biRealtime = 0U;
    BCTLDRV_stErr.biOutputEn = 1U;
    BCTLDRV_stErr.biComfirm = 0U;
    BCTLDRV_stErr.u8OutputTimer = 0U;
    BCTLDRV_stErr.u8RetryCounter = 0U;
#endif
#endif
    BCTLDRV_u16SetPwmDuty(0u);
#if(BCTLDRV_nHW_RELAY_CTRL !=0U)
    BCTL_RelayCtrlOnOffCfg(0U);
#endif
}
void BCTLDRV_vDeinit(void)
{
    BCTLDRV_stMainOut.BlwPwmDuty.Sts = BCTLDRV_nInvalid;
    BCTLDRV_stMainOut.ErrSts.Sts= BCTLDRV_nInvalid;
    BCTLDRV_stMainOut.BlwPwmDuty.Val = 0U;
    BCTLDRV_stMainOut.ErrSts.Val = 0U;
#if (BCTLDRV_nWITH_FEED_BACK != 0U)   
    BCTLDRV_u32FbFilterBuffer = 0U;
    BCTLDRV_stMainOut.FbVolt.Sts= BCTLDRV_nInvalid;
    BCTLDRV_stMainOut.FbVolt.Val = 0xFFFFU;
#if (BCTLDRV_nUSE_ERR_DET != 0U)
    BCTLDRV_stErr.biHappen = 0U;
    BCTLDRV_stErr.biRealtime = 0U;
    BCTLDRV_stErr.biOutputEn = 1U;
    BCTLDRV_stErr.biComfirm = 0U;
    BCTLDRV_stErr.u8OutputTimer = 0U;
    BCTLDRV_stErr.u8RetryCounter = 0U;
#endif
#endif
    BCTLDRV_u16SetPwmDuty(0u);
#if(BCTLDRV_nHW_RELAY_CTRL !=0U)
    BCTL_RelayCtrlOnOffCfg(0U);
#endif
}


void BCTLDRV_vMain(void)
{
    BCTLDRV_tstMainIn stMainIn;  

    stMainIn.InBlwVolt.Sts = BCTLDRV_enBlwVoltImport(&stMainIn.InBlwVolt.Val);
#if (BCTLDRV_nWITH_FEED_BACK != 0U) 
    stMainIn.InPtaBlwFb.Sts = BCTLDRV_enPtaBlwVoltImport(&stMainIn.InPtaBlwFb.Val);
#endif
//#if (BCTLDRV_nWITH_FEED_BACK != 0U) 
    //if((stMainIn.InBlwVolt.Sts == BCTLDRV_nInvalid)||(stMainIn.InPtaBlwFb.Sts == BCTLDRV_nInvalid))
//#else
    if(stMainIn.InBlwVolt.Sts == BCTLDRV_nInvalid)
//#endif        
    {
#if (BCTLDRV_nWITH_FEED_BACK != 0U)
        BCTLDRV_stMainOut.FbVolt.Sts = BCTLDRV_nInvalid;
        BCTLDRV_stMainOut.FbVolt.Val = 0xFFFFU;
#endif    
        BCTLDRV_stMainOut.ErrSts.Sts = BCTLDRV_nInvalid;
        BCTLDRV_stMainOut.ErrSts.Val = 0x0U;
        BCTLDRV_stMainOut.BlwPwmDuty.Sts = BCTLDRV_nInvalid;
        BCTLDRV_stMainOut.BlwPwmDuty.Val = 0U;
        BCTLDRV_u16SetPwmDuty(0u);
#if(BCTLDRV_nHW_RELAY_CTRL != 0U)        
        BCTL_RelayCtrlOnOffCfg(0U);
#endif
    }
    else
    {
        BCTLDRV_stMainOut.BlwPwmDuty.Sts = BCTLDRV_nValid;
        BCTLDRV_stMainOut.BlwPwmDuty.Val = BCTLDRV_u16CalPwmDuty(stMainIn.InBlwVolt.Val);
        
#if (BCTLDRV_nWITH_FEED_BACK != 0U) 
        BCTLDRV_stMainOut.FbVolt.Sts = BCTLDRV_nValid;
        BCTLDRV_stMainOut.FbVolt.Val = BCTLDRV_u16CalFbVolt(stMainIn.InPtaBlwFb.Val);
#if (BCTLDRV_nUSE_ERR_DET != 0U)  
        BCTLDRV_stMainOut.ErrSts.Sts = BCTLDRV_nValid;
        BCTLDRV_vErrorCheck(BCTLDRV_stMainOut.BlwPwmDuty.Val,stMainIn.InPtaBlwFb.Val,&BCTLDRV_stErr);
        BCTLDRV_vErrorHandle(BCTLDRV_stErr,&BCTLDRV_stMainOut.BlwPwmDuty.Val,&BCTLDRV_stMainOut.ErrSts.Val);
#endif        
#endif  
        BCTLDRV_u16SetPwmDuty(BCTLDRV_stMainOut.BlwPwmDuty.Val);
#if(BCTLDRV_nHW_RELAY_CTRL != 0U)     
        stMainIn.InBlwRelay.Sts = BCTLDRV_enRelaySigImport(&stMainIn.InBlwRelay.Val);
        if((stMainIn.InBlwRelay.Sts == BCTLDRV_nInvalid)||(stMainIn.InBlwRelay.Val == 0U))
        {
            BCTL_RelayCtrlOnOffCfg(0U);
        }
        else
        {
            BCTL_RelayCtrlOnOffCfg(1U);
        }
#endif
    }
    BCTLDRV_vOutputUpdate();
}


/*****************************************************************************
* Function      : uint8 BCTLDRV_u8GetValue( BCTLDRV_tenu8VarNumber enIndex )                                            
* Description   : The extern model get the uint8 type variable value from this
*				     model,                                                      
* Takes  :    enIndex   - the index number.                                          
* Returns   : uint8   - the wanted value                                                 
*****************************************************************************/
uint8 BCTLDRV_u8GetValue( BCTLDRV_tenu8VarNumber enIndex )
{
    return(0xA2U);
}

/*****************************************************************************
* Function      : uint16 BCTLDRV_u16GetValue( BCTLDRV_tenu16VarNumber enIndex )                                              
* Description   : The extern model get the uint8 type variable value from this
*				     model,                                                      
* Takes  :    enIndex   - the index number.                                          
* Returns   : uint8   - the wanted value   
*****************************************************************************/
uint16 BCTLDRV_u16GetValue( BCTLDRV_tenu16VarNumber enIndex )
{
    uint16 u16Ret;

    switch(enIndex)
    {
        case BCTLDRV_nu16Error: 
            if(BCTLDRV_stMainOut.ErrSts.Sts == BCTLDRV_nInvalid)
            {
                u16Ret = 0xFFFFU;
            }
            else
            {
                u16Ret = BCTLDRV_stMainOut.ErrSts.Val;
            }
            break;
        case BCTLDRV_nu16PwmDuty: 
            if(BCTLDRV_stMainOut.BlwPwmDuty.Sts == BCTLDRV_nInvalid)
            {
                u16Ret = 0xFFFFU;
            }
            else
            {
                u16Ret = BCTLDRV_stMainOut.BlwPwmDuty.Val;
            }
            break;
        case BCTLDRV_nu16SwVersion: 
            u16Ret = 0x0101U;
            break;   
#if (BCTLDRV_nWITH_FEED_BACK != 0U)
        case BCTLDRV_nu16VoltFeedback: 
            if(BCTLDRV_stMainOut.FbVolt.Sts == BCTLDRV_nInvalid)
            {
                u16Ret = 0xFFFFU;
            }
            else
            {
                u16Ret = BCTLDRV_stMainOut.FbVolt.Val;
            }
            break;
        case BCTLDRV_nu16VoltFeedbackRaw: 
            BCTLDRV_enPtaBlwVoltImport(&u16Ret);
            break;
#endif	
        default:
            u16Ret = 0xFFFFU;
            break;
    }
    return(u16Ret);    
}

void BCTLDRV_vActive(void)
{

}

/*****************************************************************************
* EOF:Mac.c
******************************************************************************/


