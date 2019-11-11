/*******************************************************************************
| Project Name: DiagLIN
|    File Name: LINdiag.h
|
|  Description: UDS (ISO-14229) conform diagnostic layer API declarations.
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2014 Vector Informatik GmbH                 All rights reserved.
|
| This software is copyright protected and proprietary to Vector Informatik GmbH.
| Vector Informatik GmbH grants to you only those rights as set out in the
| license conditions. All other rights remain with Vector Informatik GmbH.
|
| REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
|-------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ---------------------------------------
| Sa           Mishel Shishmanyan        Vector Informatik GmbH
| Ap           Andreas Pick              Vector Informatik GmbH
| Svh          Sven Hesselmann           Vector Informatik GmbH
| Bmo          Bastian Molkenthin        Vector Informatik GmbH
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date        Ver      Author  Description
| ----------  -------  ------  -------------------------------------------------
| 2004-07-09  1.00.00  Sa      First implementation
| 2007-05-16  1.01.00  Ap      ESCAN00020779: Support for new LIN Tp interface
|                              ESCAN00020780: Compile warning due to implicit cast to smaller type
| 2008-04-07  1.02.00  Svh     ESCAN00025886: Support Rx Single Frame Only of TpLin
| 2008-06-30  1.03.00  Ap      ESCAN00027967: Report tester present command to application
| 2009-01-30  1.04.00  Ap      ESCAN00032693: Session control enabled
| 2011-08-22  1.05.00  Sa      ESCAN00052746: TesterPresent service not fully UDS compliant
| 2012-11-08  1.06.00  Ap      ESCAN00062456: Service active timeout observation
| 2013-03-04  1.06.01  Ap      ESCAN00065558: Compatibility to LinTp
| 2013-11-27  1.06.02  Ap      ESCAN00072256: Access to suppress positive response bit
| 2013-12-16  1.07.00  Bmo     ESCAN00071108: Response pending frames support enabled
|                              ESCAN00072484: Access to NAD of diagnostic request
| 2014-01-13  1.07.01  Bmo     ESCAN00072939: Abort diagnostic response after failed response pending transmission
********************************************************************************/
#if !defined (__LINDIAG_H__)
# define __LINDIAG_H__

/*----------------------------
Version check defines
----------------------------*/
/* ##V_CFG_MANAGEMENT ##CQProject : DiagLin_SlavEcu CQComponent : Implementation */
# define DIAGLIN_SLAVECU_VERSION                            0x0107u
# define DIAGLIN_SLAVECU_RELEASE_VERSION                    0x01u

/*----------------------------
Include section
----------------------------*/
# include "diag_cfg.h"
# include "diag_chk.h"


/*----------------------------------------------------------------------------
    Negative response codes
----------------------------------------------------------------------------*/
# define kLinDiagNrcGeneralReject                          ((vuint8)0x10u)
# define kLinDiagNrcServiceNotSupported                    ((vuint8)0x11u)
# define kLinDiagNrcInvalidSubFunction                     ((vuint8)0x12u)
# define kLinDiagNrcInvalidFormat                          ((vuint8)0x13u)
# define kLinDiagNrcBusyRepeatRequest                      ((vuint8)0x21u)
# define kLinDiagNrcConditionsNotCorrect                   ((vuint8)0x22u)
# define kLinDiagNrcRequestSequenceError                   ((vuint8)0x24u)
# define kLinDiagNrcRequestOutOfRange                      ((vuint8)0x31u)
# define kLinDiagNrcAccessDenied                           ((vuint8)0x33u)
# define kLinDiagNrcInvalidKey                             ((vuint8)0x35u)
# define kLinDiagNrcExceedNumOfAttempts                    ((vuint8)0x36u)
# define kLinDiagNrcTimeDelayNotExpired                    ((vuint8)0x37u)
# define kLinDiagNrcUploadDownloadNotAccepted              ((vuint8)0x70u)
# define kLinDiagNrcTransferDataSuspended                  ((vuint8)0x71u)
# define kLinDiagNrcGeneralProgrammingFailure              ((vuint8)0x72u)
# define kLinDiagNrcWrongBlockSequenceCounter              ((vuint8)0x73u)
# define kLinDiagNrcResponsePending                        ((vuint8)0x78u)
# define kLinDiagNrcSubFuncNotSuppInActiveMode             ((vuint8)0x7Eu)
# define kLinDiagNrcServiceNotSuppInActiveMode             ((vuint8)0x7Fu)
# define kLinDiagNrcRpmTooHigh                             ((vuint8)0x81u)
# define kLinDiagNrcRpmTooLow                              ((vuint8)0x82u)
# define kLinDiagNrcEngineIsRunning                        ((vuint8)0x83u)
# define kLinDiagNrcEngineIsNotRunning                     ((vuint8)0x84u)
# define kLinDiagNrcEngineRunTimeTooLow                    ((vuint8)0x85u)
# define kLinDiagNrcTemperatureTooHigh                     ((vuint8)0x86u)
# define kLinDiagNrcTemperatureTooLow                      ((vuint8)0x87u)
# define kLinDiagNrcVehicleSpeedTooHigh                    ((vuint8)0x88u)
# define kLinDiagNrcVehicleSpeedTooLow                     ((vuint8)0x89u)
# define kLinDiagNrcThrottleSpeedTooHigh                   ((vuint8)0x8Au)
# define kLinDiagNrcThrottleSpeedTooLow                    ((vuint8)0x8Bu)
# define kLinDiagNrcTransmissionRangeInNeutral             ((vuint8)0x8Cu)
# define kLinDiagNrcTransmissionRangeInGears               ((vuint8)0x8Du)
# define kLinDiagNrcBrakeSwitchNotClosed                   ((vuint8)0x8Fu)
# define kLinDiagNrcShifterLeverNotInPark                  ((vuint8)0x90u)
# define kLinDiagNrcTorqueConverterClutchLocked            ((vuint8)0x91u)
# define kLinDiagNrcVoltageTooHigh                         ((vuint8)0x92u)
# define kLinDiagNrcVoltageTooLow                          ((vuint8)0x93u)

/*----------------------------
Global RAM variables
----------------------------*/
/* Global buffer for TP and application:
 * - TP reads/writes from position 0,
 * - application reads/writes from position 1
 */
V_MEMRAM0 extern V_MEMRAM1 vuint8 V_MEMRAM2 pbLinDiagBuffer[];  /* PRQA S 3451, 3684 *//* MD_LINDIAG_8.8, MD_LINDIAG_8.12 */
/* Data length (without SID byte) for the application:
 * - TP reads/writes the response/request message length,
 * - application reads/writes the length of the data stream after the SID/RSID
 */
V_MEMRAM0 extern V_MEMRAM1 vuint16 V_MEMRAM2 g_linDiagDataLength;
#if defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)
/* Global buffer for TP used for response pending frame.
 * - By default, application should not access it.
 */
V_MEMRAM0 extern V_MEMRAM1 vuint8 V_MEMRAM2 pbLinDiagRcrRpBuffer[];
#endif

/*----------------------------
Global ROM variables
----------------------------*/
/* Version information */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kLinDiagMainVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kLinDiagSubVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kLinDiagBugFixVersion;

/*----------------------------
Function prototypes
----------------------------*/
/* Application's API */
void LinDiagInit(void);
void LinDiagTask(void);

void LinDiagPreProcessSubFunction(void);
void LinDiagSendPosResponse(void);
void LinDiagSendNegResponse(vuint8 nrc);
void LinDiagSendNoResponse(void);
void LinDiagSetRequestPending(void);
#if defined (LINDIAG_ENABLE_RCR_RP_SUPPORT)
void LinDiagSendResponsePending(void);
#endif

# if defined ( LINDIAG_ENABLE_TX_CONFIRMATION )
/* Confirmation callback, 0x00 - ok, 0x01 - failed */
void ApplLinDiagTxConfirmation(vuint8 bResult );
# endif

# if defined ( LINDIAG_ENABLE_RCR_RP_SUPPORT )
#  if defined ( LINDIAG_ENABLE_RCR_RP_CONFIRMATION )
/* RP confirmation callback, 0x00 - ok, 0x01 - failed */
void ApplLinDiagRespPendingTxConfirmation(vuint8 bResult );
#  endif
#endif

#if defined (LINDIAG_ENABLE_REQUEST_ACTIVE_TIMEOUT)
void ApplLinDiagServiceActiveTimeout(void);
#endif

# if defined (LINDIAG_ENABLE_SESSION_MANAGEMENT)
vuint8 LinDiagIsSessionNonDefault(void);
void   LinDiagSetSessionDefault(void);
void   LinDiagSetSessionNonDefault(void);
# else
/* Always default */
#  define LinDiagIsSessionNonDefault()                     ((vuint8)0x00u)
#  define LinDiagSetSessionDefault()                       /* Not used */
#  define LinDiagSetSessionNonDefault()                    /* Not used */
# endif

/* Check Suppress Positive Response Message Indication Bit */
vuint8   LinDiagCheckSPRMIB(void);
/* Get NAD of current request */
vuint8   LinDiagGetCurrentNAD(void);

/* Application's callbacks */
# if defined (LINDIAG_ENABLE_ON_S1_TIMEOUT_NOTIFICATION)
/* Application notification about the time expiration. */
void ApplLinDiagOnS1Timeout(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_10H)
void ApplLinDiagSessionControl(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_11H)
void ApplLinDiagEcuReset(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_14H)
void ApplLinDiagClearDiagInfo(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_19H)
void ApplLinDiagReadDtcInfo(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_22H)
void ApplLinDiagReadDataById(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_23H)
void ApplLinDiagReadDataByAddress(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_24H)
void ApplLinDiagReadScalingDataById(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_27H)
void ApplLinDiagSecurityAccess(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_28H)
void ApplLinDiagCommControl(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_2EH)
void ApplLinDiagWriteDataById(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_2FH)
void ApplLinDiagIoControlById(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_31H)
void ApplLinDiagRoutineControl(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_34H)
void ApplLinDiagRequestDownload(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_35H)
void ApplLinDiagRequestUpload(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_36H)
void ApplLinDiagTransferData(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_37H)
void ApplLinDiagTransferExit(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_3DH)
void ApplLinDiagWriteMemoryByAddress(void);
# endif

#if defined  (LINDIAG_ENABLE_SERVICE_3EH)
void ApplLinDiagTesterPresent(void);
# endif

# if defined (LINDIAG_ENABLE_SERVICE_85H)
void ApplLinDiagControlDtcSetting(void);
# endif

# if defined (LINDIAG_ENABLE_USER_SERVICE_SUPPORT)
void ApplLinDiagUserService(void);
# endif

#endif /*__LINDIAG_H__*/
