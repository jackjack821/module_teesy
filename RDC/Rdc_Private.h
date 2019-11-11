/***************************************************************************************************
                                       RDC PROCESS
  .File Name: RDC_Type.h
  
  .Description: Thie file is used to define the special type.

  --------------------------------------------------------------------------------------------------
  Version     Date            Author            Change

  --------------------------------------------------------------------------------------------------
  Rev 1.0     2014/11/27      Xu Xianglin     	The first version            
***************************************************************************************************/
#ifndef RDC_PRIVATE_H
#define RDC_PRIVATE_H
#ifndef RDC_nTBD                                 
#define RDC_nTBD     (0U)
#endif
/***************************************************************************************************
                                        HEADER FILES
***************************************************************************************************/ 
/* System-headerfiles */

/* Foreign headerfiles */

/* Own headerfiles */

/***************************************************************************************************
                                        EXTERNAL INTERFACE
***************************************************************************************************/
#define RDC_u8GetMmiStatus()		 MMI_u8GetValue(MMI_nRearDefrost)
#define RDC_u8GetHighPowValue()	     POW_u16GetValue(POW_nu16AppHighVoltage)
#define RDC_u8GetLowPowValue()	     POW_u16GetValue(POW_nu16AppLowVoltage)
#define RDC_u16GetSignal(x)          Rte_Call_IoHwAd_IoHwAd_ReadAd_Rdc_Read(x)
#define RDC_u8GetBcmRearDefFeedback() 0x00u//CANAPP_u16GetValue(CANAPP_nu16BCM_DefrosterSts)

/***************************************************************************************************
                                        MACRO DEFINITION
***************************************************************************************************/
#define RDC_u8SwVersion                                   RDC_au8Array[RDC_nu8SwVersion]
#define RDC_u8Display                                     RDC_au8Array[RDC_nu8Display]
#define RDC_u8ErrCode                                     RDC_au8Array[RDC_nu8ErrorCode]
#define RDC_u8Request                                     RDC_au8Array[RDC_nu8Request]
#define RDC_u8Feedback                                    RDC_au8Array[RDC_nu8Feedback]
#define RDC_u8IceDisplayFlag                             RDC_au8Array[RDC_nu8IceDisplayFlag]

#define RDC_nVersion                                    (0xA1)
#define RdfrostFeedBackChannel                          (4U)
#define REQUSET_NOT_ACTIVE                               (0U)
#define REQUSET_ACTIVE                                   (1U)                                
#define REQ_PULSE_WIDE                                   (20U) /*10*20ms Output signal wideth.*/
#define WAIT_MMI_TIME                                    (3U) /*Wait time when module initialization.*/

#define UPDATE_DISPLAY_DELAY                             (10U) /*Apply to update display when press key.*/
#define UPDATE_DISPLAY_CYCLE                             (10U) /*Apply to update display when no key press.*/
#define DISPLAY_MIN_ON_TIME                              (3U) /*Apply to feedback signal valid detection.*/

#define FEEDBACK_DETECT_CYCLE                            (100U) /*Applay to detect error.*/
#define FEEDBACK_MIN_ERR_TIME                            (10U) /*Feedback signal error time parameter*/
#define FEEDBACK_MAX_ERR_TIME                            (90U) /*Feedback signal error time parameter*/

#define FUNCTION_MAX_TIME                                (90000U)/*function duration.*/

#define RDC_ErrorCodeSet(index)   (RDC_u8ErrCode|=((uint32)1U<<(index)))
#define RDC_ErrorCodeClr(index)   (RDC_u8ErrCode&=~((uint32)1U<<(index)))

#define RdcGetCcpForceBit(index)	((RDC_CcpForceFlag>>index)&0x01)
#define RdcSetCcpForceBit(index)	(RDC_CcpForceFlag=RDC_CcpForceFlag|(0x01<<index))
#define RdcClrCcpForceBit(index)	(RDC_CcpForceFlag=RDC_CcpForceFlag&(~(0x01<<index)))
#define RdcClrCcpForceByte(void)	(RDC_CcpForceFlag=0)

//#ifndef RDC_RTE
//#define Std_ReturnType uint8
//#define RTE_E_INVALID (0U)
//#define RTE_E_OK (1U)
//#define UInt32 uint32
//#endif
#endif                           
/**************************************************************************************************
* EOF: Rdc_Private.h
***************************************************************************************************/
