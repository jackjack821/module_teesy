/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

/* STARTSINGLE_OF_MULTIPLE */

#ifndef  CAN_HL_H
# define  CAN_HL_H

/* ***************************************************************************
|
| Project Name: DrvCan_Rh850RscanHll
|    File Name: can_def.h
|
|  Description: Application interface of the CAN driver
|               Declaration of functions, variables and constants
|
|               Target systems: see module file
|               Compiler:       see module file
|
|************************************************************************** */

/* ***************************************************************************
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 1996-2015 by Vector Informatik GmbH.      All rights reserved.
|
| This software is copyright protected and proprietary 
| to Vector Informatik GmbH. Vector Informatik GmbH 
| grants to you only those rights as set out in the 
| license conditions. All other rights remain with 
| Vector Informatik GmbH.
|
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| Tkr          Torsten Kercher           Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Version   Author  Description
| ----------  --------  ------  ----------------------------------------------
| 2011-03-03   2.00.00   Tkr    - ESCAN00049511: Initial release for SH2 platform with GHS compiler and ASR
| 2011-03-28   2.00.01   Tkr    - ESCAN00049632: Review reworks
| 2011-05-02   2.01.00   Tkr    - ESCAN00050300: Full support of RSCAN
| 2011-11-09   2.02.00   Tkr    - ESCAN00055178: Support API functions 'Can_ClearTxFifo' and 'Can_GetTxFifoPendings'
|                               - ESCAN00055179: Move CAN interrupt locking from CAN cell to interrupt controller
|                               - ESCAN00055180: AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
|                               - ESCAN00055181: Wait for completion of CAN RAM initialization before accessing hardware
| 2011-12-13   2.02.01   Tkr    - ESCAN00055551: Remove PB section pragmas in 'Can_MemMap.inc' file
| 2012-07-02   3.00.00   Tkr    - ESCAN00061608: Rename CAN cell and driver
|                               - ESCAN00061610: Support RH850 platform with GHS compiler
|                               - ESCAN00061611: Rework initialization sequence
|                               - ESCAN00058834: BusOff event is not detected and notified
|                               - ESCAN00060435: API function 'Can_ClearTxFifo' has no effect
| 2012-10-09   3.01.00   Tkr    - ESCAN00062467: Support CBD
|                               - ESCAN00062468: Support SH2 platform with Renesas (HEW) compiler
| 2013-01-15   3.02.00   Tkr    - ESCAN00064272: Support GenTool 'DaVinci Configurator'
|                               - ESCAN00064273: Support features 'TxFifo' and 'SpecialBusOff' for RH850 platform
|                               - ESCAN00064036: Use 32bit access to copy data from and to HW mailboxes
| 2013-02-12   3.03.00   Tkr    - ESCAN00065625: Support RL78 platform with Renesas compiler
|                               - ESCAN00065626: Support configuration of nested interrupts for RH850 and RL78 platforms
|                               - ESCAN00065718: Support optimization if only one physical channel is used
| 2013-04-15   3.03.01   Tkr    - ESCAN00066703: Review reworks
|                               - ESCAN00067169: Unexpected Tx confirmation call
| 2013-05-21   3.04.00   Tkr    - ESCAN00067472: Support HighEnd features for CBD
| 2013-07-01   3.05.00   Tkr    - ESCAN00068478: Support RL78 platform with IAR compiler
| 2013-08-07   3.05.01   Tkr    - ESCAN00069688: Adapt internal platform specific feature switches
|                               - ESCAN00069942: Review reworks
| 2013-08-19   3.06.00   Tkr    - ESCAN00069923: Support RH850 platform with DiabData compiler
| 2013-09-25   3.07.00   Tkr    - ESCAN00070178: Full support of sleep/wakeup functionality for RH850 platform
|                               - ESCAN00070963: Rework mode transitions
|                               - ESCAN00070964: Rework BusOff recovery behavior
| 2013-10-28   3.08.00   Tkr    - ESCAN00071497: AR4-328: Predefined Runtime Measurement Points
|                               - ESCAN00071662: Support usage of 'Peripheral Interrupt API' (Microsar OS) for RH850 platform
| 2014-01-15   3.09.00   Tkr    - ESCAN00073117: General code reworks
|                               - ESCAN00073369: Compiler warning: Conversion may lose significant digits
| 2014-03-18   3.10.00   Tkr    - ESCAN00074760: Support extended CAN RAM check
|                               - ESCAN00074761: Support RSCAN RAM test
| 2014-04-29   3.10.01   Tkr    - ESCAN00075301: Adapt default value of nested interrupt configuration
| 2014-05-06   3.11.00   Tkr    - ESCAN00075610: Support RH850 platform with IAR compiler
| 2014-06-02   3.12.00   Tkr    - ESCAN00077418: Support RH850 platform with Renesas compiler
|                               - ESCAN00077419: Add MISRA justifications in source code for CBD
|                               - ESCAN00077420: Support application callouts when accessing interrupt control registers for RH850 platform
|                               - ESCAN00077427: Compliance to RH850 usage notes regarding synchronization of subsequent instructions
|                               - ESCAN00077428: Rework mode transitions
|                               - ESCAN00077431: Illegal access by extended CAN RAM check
|                               - ESCAN00077432: General code reworks
| 2014-08-13   3.12.01   Tkr    - ESCAN00077732: Compiler error: Identifier 'canPhysChannel' is undefined
| 2014-10-24   3.13.00   Tkr    - ESCAN00079341: Support Rscan-FD IP-Core
|                               - ESCAN00079342: Support usage of MICROSAR OS 'Peripheral Access API' for RH850 platform
|                               - ESCAN00079343: Support callback function 'ApplCanWakeupOccurred'
|                               - ESCAN00079344: General code reworks
|                               - ESCAN00078598: Compiler warning: Possible use of 'CanLL_TxTmpBuf' before definition
| 2014-12-03   3.13.01   Tkr    - ESCAN00079720: Compiler error: Unresolved symbols _Rtm_Stop_ and _Rtm_Start_
| 2014-12-08   3.14.00   Tkr    - ESCAN00080058: Support gateway bus mirroring
| 2015-05-26   3.15.00   Tkr    - ESCAN00083194: Support multi-channel RL78 derivatives
|                               - ESCAN00082515: Optimize 'Channel Error Flag' register access
|                               - ESCAN00082290: Undefined ECU behavior
|                               - ESCAN00082632: FullCAN message is not received
|************************************************************************** */
/* ***************************************************************************
|
|    ************    Version and change information of      **********        
|    ************    high level part only                   **********        
|
|    Please find the version number of the whole module in the previous 
|    File header.
|
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------
| Ht           Heike Honert              Vector Informatik GmbH
| Pl           Georg Pfluegel            Vector Informatik GmbH
| Vg           Frank Voorburg            Vector CANtech, Inc.
| An           Ahmad Nasser              Vector CANtech, Inc.
| Ml           Patrick Markl             Vector Informatik GmbH
| Seu          Eugen Stripling           Vector Informatik GmbH
| Uce          Cengiz Uenver             Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------ -----------------------------------------------------
| ---------  ---  ------ -- --------------------------------------------------
| 24-Jan-01  0.02      Ht     - derived from C16x V3.3
| 18-Apr-01  1.00      Pl     - adaption for ARM7 TDMI
| 26-Apr-01  1.01      Ht     - adaption to LI 1.2
|                             - changed from code doupling to indexed
| 19-Jun-01            Ht     - define of CanSetActive/Passive changed
| 31-Oct-01  1.02      Ht     - support hash search
|                      Vg     - adaption for PowerPC
| 07-Nov-01  1.03      Ht     - remove some comments
| 12-Nov-01  1.04      Fz     - no changes
| 02-Jan-02  1.05      Ht     - ESCAN00002009: support of polling mode improved
| 12-Feb-02  1.06      Pl     - ESCAN00002279: - now it is possible to use only the error-task without the tx-task
|                                              - support of the makro  REENTRANT
|                                              - support of the makro C_HL_ENABLE_RX_INFO_STRUCT_PTR
|                                              - For better performance for the T89C51C there is a switch-case
|                                                instruction for direct call of the PreTransmitfunction
|                                              - insert Prototyp for CanErrorTask
| 18-Mai-02  1.07       Ht    - support Hash search with FullCAN controller
|                             - ESCAN00002707: Reception could went wrong if IL and Hash Search
|                             - ESCAN00002893: adaption to LI 1.3
| 29-Mai-02  1.08       Ht    - ESCAN00003028: Transmission could fail in Polling mode
|                             - ESCAN00003082: call Can_LL_TxEnd() in CanMsgTransmit()
|                             - ESCAN00003083: Hash search with extended ID
|                             - ESCAN00003084: Support C_COMP_METROWERKS_PPC
|                             - ESCAN00002164: Temporary vaiable "i" not defined in function CanBasicCanMsgReceived
|                             - ESCAN00003085: support C_HL_ENABLE_IDTYPE_IN_ID
| 25-Jun     1.08.01    Vg    - Declared localInterruptOldFlag in CanRxTask()
|                             - Corrected call to CanWakeUp for multichannel
| 11-Jul-02  1.08.02    Ht    - ESCAN00003203: Hash Search routine does not work will with extended IDs
|                             - ESCAN00003205: Support of ranges could went wrong on some platforms
| 08-Aug-02  1.08.03    Ht    - ESCAN00003447: Transmission without databuffer and pretransmit-function 
| 08-Aug-02  1.08.04    An      no changes
| 09-Sep-02  1.09       Ht    - ESCAN00003837: code optimication with KernelBuilder 
| 2002-12-12 1.10       Ht    -                support Dummy functions for indirect function call 
| 2003-02-04 1.11       Ht    -                optimization for polling mode
|                       Fz    - ESCAN00004600: Flags changed for V850 aFCAN only
| 2003-03-19 1.12       Ht    - ESCAN00005153: Wrong number of Indication bytes for V850 aFCAN only
|                             - ESCAN00005152: optimization of CanInit() in case of Direct Tx Objects
|                             - ESCAN00005143: CompilerWarning about function prototype 
|                                              CanHL_ReceivedRxHandle() and CanHL_IndRxHandle
|                             - ESCAN00005130: Wrong result of Heash Search on second or higher channel               
| 2003-05-12 1.13       Ht    - ESCAN00005624: support CantxMsgDestroyed for multichannel system
|                             - ESCAN00005209: Support confirmation and indication flags for EasyCAN4
|                             - ESCAN00004721: Change data type of Handle in CanRxInfoStruct
| 2003-06-18 1.20       Ht    - ESCAN00005908: support features of RI1.4
|                             - Support FJ16LX-Workaround for multichannel system
|                             - ESCAN00005671: Dynamic ID in extended ID system could fail
|                             - ESCAN00005863: Notification about cancelation failes in case of CanTxMsgDestroyed
| 2003-06-30 1.21       Ht   - ESCAN00006117: Common Confirmation Function: Write access to wrong memory location
|                            - ESCAN00006008: CanCanInterruptDisable in case of polling
|                            - ESCAN00006118: Optimization for Mixed ID and ID type in Own Register or ID type in ID Register
|                            - ESCAN00006063: Undesirable hardware dependency for 
|                                             CAN_HL (CanLL_RxBasicTxIdReceived)
| 2003-09-10 1.22       Ht   - ESCAN00006853: Support V_MEMROM0
|                            - ESCAN00006854: suppress some Compiler warnings
|                            - ESCAN00006856: support CanTask if only Wakeup in polling mode
|                            - ESCAN00006857: variable newDLC not defined in case of Variable DataLen
| 2003-10-14 1.23       Ht   - ESCAN00006858: support BrsTime for internal runtime measurement
|                            - ESCAN00006860: support Conditional Msg Receive
|                            - ESCAN00006865: support "Cancel in HW" with CanTask
|                            - ESCAN00006866: support Direct Tx Objects
|                            - ESCAN00007109: support new memory qualifier for const data and pointer to const
| 2004-01-05 1.24       Ml   - ESCAN00007206: no changes
|                       Ml   - ESCAN00007254: several changes
| 2004-02-06 1.25       Ml   - ESCAN00007281: no changes
|                       Ml   - removed compiler warnings
| 2004-02-21 1.26       Ml   - ESCAN00007670: CAN RAM check
|                       Ml   - ESCAN00007671: no changes
|                       Ml   - ESCAN00007764: no changes
|                       Ml   - ESCAN00007681: no changes
|                       Ml   - ESCAN00007272: no changes
|                       Ml   - ESCAN00008064: encapsulated CanRxHashId in case of array dimension == 0
| 2004-04-16 1.27       Ml   - ESCAN00008204: Optimized CanRxActualId for different ID modes
|                       Ml   - ESCAN00008160: encapsulated functions declared by tool in case of multichannel
|                       Ml   - ESCAN00008266: changed name of parameter of function CanTxGetActHandle
|                       Fz   - ESCAN00008272: Compiler error due to missing array canPollingTaskActive
| 2004-05-10 1.28       Fz   - ESCAN00008328: Compiler error if cancel in hardware is active
|                            - ESCAN00008363: Hole closed when TX in interrupt and cancel in HW is used
|                            - ESCAN00008365: Switch C_ENABLE_APPLCANPREWAKEUP_FCT added
|                            - ESCAN00008391: Wrong parameter macro used in call of 
|                                             CanLL_WakeUpHandling
| 2004-05-24 1.29       Ht   - ESCAN00008441: Interrupt not restored in case of internal error if TX Polling is used
| 2004-09-21 1.30       Ht   - ESCAN00008824: check of reference implementation version added
|                            - ESCAN00008825: No call of ApplCanMsgCancelNotification during CanInit()
|                            - ESCAN00008826: Support asssertions for "Conditional Message Received"  
|                       Ml   - ESCAN00008752: Added function qualifier macros
|                       Ht   - ESCAN00008823: compiler error due to array size 0
|                            - ESCAN00008977: label without instructions
|                            - ESCAN00009485: Message via Normal Tx Object will not be sent  
|                            - ESCAN00009497: support of CommonCAN and RX queue added
| 2004-09-28 1.31       Ht   - ESCAN00009703: unresolved functions CAN_POLLING_IRQ_DISABLE/RESTORE()
| 2004-11-25 1.32       Ht   - move fix for ESCAN00007671 to CAN-LL of DrvCan_MpcToucanHll
|                            - ESCAN00010350: Dynamic Tx messages are send always with Std. ID
|                            - ESCAN00010388: ApplCanMsgConfirmed will only be called if realy transmitted
|                       Ml   - ESCAN00009931: The HardwareLoopCheck should have a channelparameter in multichannel systems.
|                            - ESCAN00010093: lint warning: function type inconsistent "CanCheckMemory"
|                        Ht  - ESCAN00010811: remove Misra and compiler warnings
|                            - ESCAN00010812: support Multi ECU
|                            - ESCAN00010526: CAN interrupts will be disabled accidently
|                            - ESCAN00010584: ECU may crash or behave strange with Rx queue active
| 2005-01-20 1.33       Ht   - ESCAN00010877: ApplCanMsgTransmitConf() is called erronemous
| 2005-03-03 1.34       Ht   - ESCAN00011139: Improvement/Correction of C_ENABLE_MULTI_ECU_CONFIG
|                            - ESCAN00011511: avoid PC-Lint warnings
|                            - ESCAN00011512: copy DLC in case of variable Rx Datalen
|                            - ESCAN00010847: warning due to missing brakets in can_par.c at CanChannelObject
| 2005-05-23 1.35       Ht   - ESCAN00012445: compiler error "V_MEMROMO undefined"in case of multi ECU
|                            - ESCAN00012350: Compiler Error "Illegal token channel"
| 2005-07-06 1.36       Ht   - ESCAN00012153: Compile Error: missing declaration of variable i
|                            - ESCAN00012460: Confirmation of LowLevel message will run into assertion (C_ENABLE_MULTI_ECU_PHYS enabled)
|                            - support Testpoints for CanTestKit
| 2005-07-14 1.37       Ht   - ESCAN00012892: compile error due to missing logTxObjHandle
|                            - ESCAN00012998: Compile Error: missing declaration of txHandle in CanInit()
|                            - support Testpoints for CanTestKit for FullCAN controller
| 2005-10-05 1.38       Ht   - ESCAN00013597: Linker error: Undefined symbol 'CanHL_IndRxHandle'
| 2005-11-10 1.39.00    Ht   - ESCAN00014331: Compile error due to missing 'else' in function CanTransmit
| 2005-04-26 2.00.00    Ht   - ESCAN00016698: support RI1.5
|                            - ESCAN00014770: Cosmic compiler reports truncating assignement
|                            - ESCAN00016191: Compiler warning about unused variable in CanTxTask
| 2007-01-23 2.01.00    Ht   - ESCAN00017279: Usage of SingleGlobalInterruptDisable lead to assertion in OSEK
|                            - ESCAN00017148: Compile error in higher layer due to missing declaration of CanTxMsgHandleToChannel
| 2007-03-14 2.02.00   Ht    - ESCAN00019825: error directives added and misra changes
|                            - ESCAN00019827: adaption to never version of VStdLib.
|                            - ESCAN00019619: V_CALLBACK_1 and V_CALLBACK_2 not defined
|                            - ESCAN00019953: Handling of FullCAN reception in interrupt instead of polling or vice versa.
|                            - ESCAN00019958: CanDynTxObjSetId() or CanDynTxObjSetExtId() will run into assertion
| 2007-03-26 2.03.00  Ht     - ESCAN00019988: Compile warnings in can_drv.c
|                            - ESCAN00018831: polling mode: function prototype without function implemenation (CanRxFullCANTask + CanRxBasicCANTask)
| 2007-04-20 2.04.00  dH     - ESCAN00020299: user assertion fired irregularly due to unknown parameter (in case of CommonCAN)
| 2007-05-02 2.05.00  Ht     - ESCAN00021069: Handling of canStatus improved, usage of preprocessor defines unified
|                            - ESCAN00021070: support relocation of HW objects in case of Multiple configuration
|                            - ESCAN00021166: Compiler Warnings: canHwChannel & canReturnCode not used in CanGetStatus
|                            - ESCAN00021223: CanCanInterruptDisabled called during Sleepmode in CanWakeupTask
|                            - ESCAN00022048: Parameter of ApplCancorruptMailbox is hardware channel instead of logical channel - Error directive added
| 2007-11-12 2.06.00  Ht     - ESCAN00023188: support CAN Controller specific polling sequence for BasicCAN objects
|                            - ESCAN00023208: Compile issue about undefined variable kCanTxQueuePadBits in the CAN driver in Bit based Tx queue
| 2008-10-20 2.07.00  Ht     - ESCAN00023010: support disabled mailboxes in case of extended RAM check
|                            - ESCAN00025706: provide C_SUPPORTS_MULTI_ECU_PHYS
|                            - ESCAN00026120: compiler warnings found on DrvCan_V85xAfcanHll RI 1.5     ##Ht: reviewed 2008-09-03
|                            - ESCAN00026322: ApplCanMsgNotMatched not called in special configuration
|                            - ESCAN00026413: Add possibility to reject remote frames received by FullCAN message objects
|                            - ESCAN00028758: CAN HL must support QNX
|                            - ESCAN00029788: CommonCAN for Driver which support only one Tx object improved (CanInit()).
|                            - ESCAN00029889: Compiler warning about uninitialized variable canHwChannel in CanCanInterruptDisable/Restore()
|                            - ESCAN00029891: Compiler warning: variable "rxHandle" was set but never used
|                            - ESCAN00029929: Support Extended ID Masking for Tx Fullcan messages 
|                            - ESCAN00030371: Improvements (assertions, misra)
|                            - ESCAN00027931: Wrong check of "queueBitPos" size
| 2009-04-08 2.08.00  Ht     - ESCAN00034492: no automatic remove of CanCanInterruptDisable/Restore
|                            - ESCAN00031816: CANRANGExIDTYPE can be removed and direct expression used
|                            - ESCAN00032027: CanMsgTransmit shall support tCanMsgTransmitStruct pointer accesses to far RAM
|                            - ESCAN00034488: Postfix for unsigned const in perprocessor directives are not supported by all Compiler (ARM-Compiler 1.2)
| 2009-06-04 2.08.01  Ht     - ESCAN00035426: Compiler warning about truncation in CanGetStatus removed
| 2009-10-21 2.09.00  Ht     - ESCAN00036258: Compiler warning about "CanHL_ReceivedRxHandle" was declared but never referenced
|                            - ESCAN00038642: Support reentrant functions for compiler with own keyword
|                            - ESCAN00038645: support new switch C_ENABLE_UPDATE_BASE_ADDRESS
| 2010-02-01 2.10.00  Ht     - ESCAN00036260: Support configuartion without static Tx messages and only one channel (remove compiler warning)
|                            - ESCAN00040478: Handle update of virtual CanBaseAdress in accordance to QNX documentation
|                            - ESCAN00039235: Compiler Warning: Narrowing or Signed-to-Unsigned type conversion
| 2010-07-22 2.11.00  Ht     - ESCAN00044221: support Retransmit functionality for FBL
|                            - ESCAN00044222: internal changes: improve readability and
|                                             change CAN_CAN_INTERRUPT_... macros to avoid preprocessor errors for some compiler
|                            - ESCAN00044174: TxBitQueue only - compiler warning occurs about: condition is always true
| 2010-10-22 2.12.00  Ht - ESCAN00046326: support  C_COMP_KEIL_XC800 and  C_COMP_TI_TMS320
| 2011-05-17 2.13.00  Ht - ESCAN00048965: Add assertion check txMsgStruct for NULL-Pointer value in CanMsgTransmit() API
|                        - ESCAN00050948: support retransmit macro if kCanHwTxStartIndex != 0.
| 2012-04-23 2.14.00  Ht - ESCAN00053779: Linker error: CanBaseAddressRequest() and CanBaseAddressActivate() are not available
|                        - ESCAN00056617: remove brackets in macro CanInterruptDisable/Restore()
|                        - ESCAN00058520: support CommonCAN in combination with RAM check
|                        - ESCAN00058521: support C_COMP_KEIL_SLC8051_CCAN
|                        - ESCAN00058522: some  message will be not be received via BasicCAN if index search and multichannel are active
|                        - ESCAN00058104: compiler warning occurs about: comparison between signed and unsigned
| 2012-04-23 2.14.01  Ht - ESCAN00058636: some BasicCAN messages will not be received with linear search
| 2012-05-11 2.15.00  Seu - ESCAN00058891: Add switch C_HL_ENABLE_PRETRANSMIT_SWITCH_COMMENT
| 2012-07-02 2.15.01  Ht  - ESCAN00058586: Compiler warning: comparison is always true due to limited range of data type
|                         - ESCAN00059562: Compile error: Size of array CanRxMsgIndirection is zero if index search and no Rx FullCANs are used
|                         - ESCAN00059736: Compiler warning: pointless comparison of unsigned integer with zero
| 2012-10-30 2.15.02  Ht  - ESCAN00061829: Compiler error:  about(CAN_HL_HW_RX_BASIC/FULL_STARTINDEX(canHwChannel) == 0)
|                         - ESCAN00057831: Compiler warning: "canCanInterruptOldStatus" was declared but never referenced
|                         - ESCAN00057832: Compiler warning: "canCanInterruptCounter" was set but never referenced
|                         - ESCAN00062667: Verify Identity during CanOnline and Misra improvement
| 2013-05-27 2.16.00  Ht  - ESCAN00067627: support more than 255 HW objects
| 2014-04-08 2.17.00  Ht  - ESCAN00074874: internal change: support possibility to reject transmit request before request in HW has to be set
| 2014-07-22 2.18.00  Uce - ESCAN00076820: added Misra deviation comments
|                     Ht  - ESCAN00076413: remove compiler warning - comparison is always true due to limited range of data type
|
|    ************    Version and change information of      **********        
|    ************    high level part only                   **********        
|
|    Please find the version number of the whole module in the previous 
|    File header.
|
|************************************************************************** */

/* PRQA S 0857 QAC_Can_0857 */ /* MD_Can_0857 */
/* PRQA S 0828 QAC_Can_0828 */ /* MD_Can_0828 */
/* PRQA S 3453 QAC_Can_3453 */ /* MD_Can_3453 */
/* PRQA S 0850 QAC_Can_0850 */ /* MD_Can_0850 */

/* *********************************************************************** */
/* Version                  (abcd: Main version ab Sub Version cd )        */
/* *********************************************************************** */
/* ##V_CFG_MANAGEMENT ##CQProject : DrvCan_Sh2RscanHll CQComponent : Implementation */
#define DRVCAN_SH2RSCANHLL_VERSION         0x0315u
#define DRVCAN_SH2RSCANHLL_RELEASE_VERSION 0x00u

/* ##V_CFG_MANAGEMENT ##CQProject : DrvCan__coreHll CQComponent : Implementation */
# define DRVCAN__COREHLL_VERSION                 0x0218
# define DRVCAN__COREHLL_RELEASE_VERSION         0x00
#define DRVCAN__HLLTXQUEUEBIT_VERSION 0x0106
#define DRVCAN__HLLTXQUEUEBIT_RELEASE_VERSION 0x05

/* *********************************************************************** */
/* Include                                                                 */
/* *********************************************************************** */

# include "v_def.h"

/* *********************************************************************** */
/* Defines                                                                 */
/* *********************************************************************** */

/* *********************************************************************** */
/* Default switches                                                        */
/* Automatic define settings, depending on user configuration in can_cfg.h */
/* *********************************************************************** */
# if defined( C_ENABLE_MULTICHANNEL_API )
#  define C_MULTIPLE_RECEIVE_CHANNEL
#  define MULTIPLE_RECEIVE_CHANNEL
# else
#  define C_SINGLE_RECEIVE_CHANNEL
# endif

# if ( kCanNumberOfTxObjects > 0 )
#  if !(defined( C_ENABLE_CAN_TRANSMIT ) || defined( C_DISABLE_CAN_TRANSMIT ))
#   define C_ENABLE_CAN_TRANSMIT
#  endif
# endif

# if !(defined( C_ENABLE_OFFLINE ) || defined( C_DISABLE_OFFLINE ))
#  define C_ENABLE_OFFLINE
# endif

# if !(defined( C_ENABLE_STOP ) || defined( C_DISABLE_STOP ))
#  define C_ENABLE_STOP
# endif

# if !(defined( C_ENABLE_CAN_CAN_INTERRUPT_CONTROL ) || defined( C_DISABLE_CAN_CAN_INTERRUPT_CONTROL ))
#  define C_ENABLE_CAN_CAN_INTERRUPT_CONTROL
# endif

# if !(defined( C_ENABLE_CAN_CANCEL_TRANSMIT ) || defined( C_DISABLE_CAN_CANCEL_TRANSMIT ))
#  if defined( C_ENABLE_CAN_TRANSMIT )
#   define C_ENABLE_CAN_CANCEL_TRANSMIT
#  endif
# endif

# if !defined( kCanNumberOfHwChannels )
/* compatibility for older tool versions */
#  define kCanNumberOfHwChannels                 kCanNumberOfChannels
# endif

# if !(defined( C_ENABLE_HW_OBJ_EXCEED_255_DRV ) || defined( C_DISABLE_HW_OBJ_EXCEED_255_DRV ))
#  define C_ENABLE_HW_OBJ_EXCEED_255_DRV
# endif

#define C_HL_ENABLE_OVERRUN_IN_STATUS

#define C_HL_DISABLE_HW_RANGES_FILTER

#define C_HL_ENABLE_IDTYPE_IN_ID

#if defined (C_HL_ENABLE_IDTYPE_IN_ID)
/* Specify the ID tables which contain the ID type */
# define C_LL_RX_IDTYPE_TABLE      CanRxId0
# define C_LL_TX_IDTYPE_TABLE      CanTxId0
#endif

#define C_HL_DISABLE_DUMMY_FCT_CALL

#define C_HL_DISABLE_TX_MSG_DESTROYED

#define C_HL_DISABLE_CANCEL_IN_HW_TASK

# define C_HL_DISABLE_HW_EXIT_TRANSMIT

#define C_HL_ENABLE_LAST_INIT_OBJ

# if defined(C_ENABLE_SLEEP_WAKEUP) && defined(C_ENABLE_BUSWAKEUP_SUPPORT)
#  if !defined(C_ENABLE_EXTERNAL_WAKEUP_SUPPRESSION)
#   define C_ENABLE_LL_WAKEUP_SUPPORT
#  endif
# endif
# if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
#  if defined(C_ENABLE_WAKEUP_POLLING)
#   define C_ENABLE_LL_WAKEUP_POLLING
#  endif
# else
#  define C_ENABLE_LL_WAKEUP_POLLING
# endif

#if ((  defined( C_ENABLE_CAN_CAN_INTERRUPT_CONTROL ) && !defined( C_ENABLE_OSEK_CAN_INTCTRL )) && \
     (( defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING ))    || \
      ( defined( C_ENABLE_RX_FULLCAN_OBJECTS )  && !defined( C_ENABLE_RX_FULLCAN_POLLING  ))    || \
       !defined( C_ENABLE_TX_POLLING )         || \
        defined( C_ENABLE_INDIVIDUAL_POLLING ) || \
       !defined( C_ENABLE_ERROR_POLLING )      || \
       !defined( C_ENABLE_LL_WAKEUP_POLLING )  )  )
# define C_HL_ENABLE_CAN_IRQ_DISABLE
#else
# define C_HL_DISABLE_CAN_IRQ_DISABLE
#endif

#define C_HL_DISABLE_ADJUST_RXHANDLE

#define C_HL_DISABLE_REJECT_UNWANTED_IDTYPE

#define C_HL_DISABLE_REJECT_REMOTE_FRAME

#define C_HL_DISABLE_REJECT_REMOTE_FRAME_FULLCAN

#define C_HL_DISABLE_COPROCESSOR_SUPPORT

#if !(defined (C_ENABLE_DRIVER_STATUS) || defined (C_DISABLE_DRIVER_STATUS))
# define C_ENABLE_DRIVER_STATUS
#endif

#define C_HL_DISABLE_RETRANSMIT_FCT

#define C_HL_ENABLE_RETRANSMIT_CONF_ISR

#define C_HL_DISABLE_AVOID_REENTRANT_APPLCANCANCELNOTIFICATION

#define C_ENABLE_TX_ACTUAL_MACROS

#define CAN_HL_HW_LAYOUT_TXBASIC_FIRST

# define CAN_CAST_ADDR(val) (val)

# if defined( C_ENABLE_TX_POLLING )
#  if !(defined( C_ENABLE_ERROR_POLLING )  || defined( C_DISABLE_ERROR_POLLING ))
#   define C_ENABLE_ERROR_POLLING 
#  endif
# endif

# if !(defined( C_ENABLE_TASK_RECURSION_CHECK ) || defined( C_DISABLE_TASK_RECURSION_CHECK ))
#  define C_ENABLE_TASK_RECURSION_CHECK
# endif

# if defined( C_ENABLE_MULTI_ECU_PHYS )
#  define C_SUPPORTS_MULTI_ECU_PHYS
# endif

/* *********************************************************************** */
/* return values                                                           */
/* *********************************************************************** */

/* generel return values */
# define kCanFailed                              ((vuint8)0x00)
# define kCanOk                                  ((vuint8)0x01)
# define kCanNotSupported                        ((vuint8)0x02)

# define kCanFalse                               ((vuint8)0x00)
# define kCanTrue                                ((vuint8)0x01)

/* return values for precopy-routines */
# define kCanNoCopyData                          ((vuint8)0x00)
# define kCanCopyData                            ((vuint8)0x01)

/* Bitmask of return value of CanGetStatus() */
# define kCanTxOff                               ((vuint8)0x00)
# define kCanStatusInit                          ((vuint8)0x00)
# define kCanTxOn                                ((vuint8)0x01)
# define kCanTxNotOn                             ((vuint8)0xFE)              /* internal use only */
# define kCanHwIsStop                            ((vuint8)0x02)
# define kCanHwIsInit                            ((vuint8)0x04)
# define kCanHwIsInconsistent                    ((vuint8)0x08)              /* used of for common CAN */
# define kCanHwIsWarning                         ((vuint8)0x10)
# define kCanHwIsPassive                         ((vuint8)0x20)
# define kCanHwIsBusOff                          ((vuint8)0x40)
# define kCanHwIsSleep                           ((vuint8)0x80)

/* CanTransmit return values ----------------------------------------------- */
# define kCanTxFailed                            kCanFailed      /* Tx path switched off or no sending possible */
# define kCanTxOk                                kCanOk          /* msg transmitted or in queue                 */
# define kCanTxPartOffline                       ((vuint8)0x02)  /* Tx path switched part off or           */
# define kCanCommunicationDisabled               ((vuint8)0x03)  /* if application has disabled com after memory check */

# if defined( C_DRV_INTERNAL )
#  define kCanTxNotify                           ((vuint8)0x05)  /* internal returncode only - not used for the API */
# endif

/* CanGetDynTxObj return values ----------------------------------------------- */
# define kCanNoTxDynObjAvailable                 ((CanTransmitHandle)0xFFFFFFFFU)

/* CanReleaseDynTxObj return values ------------------------------------------- */
# define kCanDynReleased                         ((vuint8)0x00)
# define kCanDynNotReleased                      ((vuint8)0x01)

/* results of CAN RAM check */
# define kCanRamCheckFailed                      ((vuint8)0x00)
# define kCanRamCheckOk                          ((vuint8)0x01)
# define kCanDisableCommunication                ((vuint8)0x00)
# define kCanEnableCommunication                 ((vuint8)0x01)

/* return values of CanRxActualIdType */
#define kCanIdTypeStd           (0x00000000UL)
#define kCanIdTypeExt           (0x80000000UL)
#define kCanStdIdMask           (0x000007FFUL)
#define kCanExtIdMask           (0x1FFFFFFFUL)
#define kCanDlcLogMask          (0x0FU)

/* return values of CanGetDriverStatus */
#define kCanDriverBusoff        0x01U             /* CAN driver is in recovery phase after bus off */
#define kCanDriverBusoffInit    0x02U             /* Driver finished recovery and needs to be initialized */
#define kCanDriverNormal        0x03U             /* Driver completed recovery and is in normal mode */

/* used for stop transition */
#define kCanStopFailed          kCanFailed
#define kCanStopOk              kCanOk
#define kCanStopIdle            kCanNotSupported

/* *********************************************************************** */
/* parameter values                                                        */
/* *********************************************************************** */
/* parameters for partial offline */
# define kCanTxPartInit                          ((vuint8)0x00)

/* paramater for assertions */
# define kCanAllChannels                         ((CanChannelHandle)0xFFU)
/* used for generated tables */
# define kCanChannelNotUsed                      ((CanChannelHandle)0xFFU)

/* canRxHandle does not contain a certain message handle or entry in table is not used */
# define kCanRxHandleNotUsed                     ((CanReceiveHandle)  0xFFFFFFFFU)
# define kCanTxHandleNotUsed                     ((CanTransmitHandle) 0xFFFFFFFFU)

# if defined( C_DRV_INTERNAL )
#  define kCanRxHandleRange0                     ((CanReceiveHandle)  0xFFFFFFF0U)
#  define kCanRxHandleRange1                     ((CanReceiveHandle)  0xFFFFFFF1U)
#  define kCanRxHandleRange2                     ((CanReceiveHandle)  0xFFFFFFF2U)
#  define kCanRxHandleRange3                     ((CanReceiveHandle)  0xFFFFFFF3U)

/* entries for generated table CanHwMsgTransmitIndex[], CanHwTxNormalIndex[] - unused in case of CommonCan */
/* table entry does not contain a HW object assignment */
#  if defined ( C_ENABLE_HW_OBJ_EXCEED_255_DRV ) &&\
      defined ( C_ENABLE_HW_OBJ_EXCEED_255_CFG )
#   define kCanObjectHandleNotUsed                ((CanObjectHandle)0xFFFFFFFFU)
#  else
#   define kCanObjectHandleNotUsed                ((CanObjectHandle)0xFFU)
#  endif

# endif

/* status of transmit objects */
# define kCanBufferFree                         ((CanTransmitHandle)0xFFFFFFFFU)   /* mark a transmit object is free */
# define kCanBufferCancel                       ((CanTransmitHandle)0xFFFFFFFEU)   /* mark a transmit object as canceled */
# define kCanBufferMsgDestroyed                 ((CanTransmitHandle)0xFFFFFFFDU)   /* mark a transmit object as destroyed */
# define kCanBufferMsgTransmit                  ((CanTransmitHandle)0xFFFFFFFCU)   /* mark a transmit object as used by CanMsgTransmit */
# define kCanBufferRetransmit                   ((CanTransmitHandle)0xFFFFFFFBU)   /* mark a transmit object as used by CanRetransmit */
/* valid transmit message handle:   0x0 to kCanNumberOfTxObjects   */

/* parameter for ApplCanTimerStart(), -End(), -Loop() */
#define kCanLoopRamInit                0x00U
#define kCanLoopInit                   0x01U
#define kCanLoopBusOffRecovery         0x02U
#define kCanLoopEnterResetMode         0x03U
#define kCanLoopEnterOperationMode     0x04U
#define kCanLoopEnterSleepMode         0x05U
#define kCanLoopEnterWakeupMode        0x06U
#define kCanLoopRxFcProcess            0x07U

/* *********************************************************************** */
/* macros                                                                  */
/* *********************************************************************** */

# if defined( C_SINGLE_RECEIVE_CHANNEL ) 
#  define CAN_CHANNEL_CANTYPE_ONLY               void                                 /* PRQA S 3460 */ /* MD_Can_3460 */
#  define CAN_CHANNEL_CANTYPE_FIRST
#  define CAN_CHANNEL_CANTYPE_LOCAL         
#  define CAN_CHANNEL_CANPARA_ONLY
#  define CAN_CHANNEL_CANPARA_FIRST
#  define CAN_HW_CHANNEL_CANTYPE_ONLY            void                                 /* PRQA S 3460 */ /* MD_Can_3460 */
#  define CAN_HW_CHANNEL_CANTYPE_FIRST
#  define CAN_HW_CHANNEL_CANTYPE_LOCAL
#  define CAN_HW_CHANNEL_CANPARA_ONLY
#  define CAN_HW_CHANNEL_CANPARA_FIRST
# else
#  define CAN_CHANNEL_CANTYPE_ONLY               CanChannelHandle channel
#  define CAN_CHANNEL_CANTYPE_FIRST              CanChannelHandle channel,
#  define CAN_CHANNEL_CANTYPE_LOCAL              CanChannelHandle channel;             /* PRQA S 3412 */ /* MD_Can_3412 */
#  define CAN_CHANNEL_CANPARA_ONLY               channel
#  define CAN_CHANNEL_CANPARA_FIRST              channel,
#  define CAN_HW_CHANNEL_CANTYPE_ONLY            CanChannelHandle canHwChannel
#  define CAN_HW_CHANNEL_CANTYPE_FIRST           CanChannelHandle canHwChannel,
#  define CAN_HW_CHANNEL_CANTYPE_LOCAL           CanChannelHandle canHwChannel;        /* PRQA S 3412 */ /* MD_Can_3412 */
#  define CAN_HW_CHANNEL_CANPARA_ONLY            canHwChannel
#  define CAN_HW_CHANNEL_CANPARA_FIRST           canHwChannel,
# endif

# if defined( C_DRV_INTERNAL )
/* macros to fill struct elements RangeMask and RangeCode of type tCanChannelObject - used by generation tool only */
#  if (kCanNumberOfUsedCanRxIdTables == 1)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 2)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i), MK_RX_RANGE_MASK_IDSTD1(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i), MK_RX_RANGE_CODE_IDSTD1(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 3)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i), MK_RX_RANGE_MASK_IDSTD1(i), MK_RX_RANGE_MASK_IDSTD2(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i), MK_RX_RANGE_CODE_IDSTD1(i), MK_RX_RANGE_CODE_IDSTD2(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 4)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i), MK_RX_RANGE_MASK_IDSTD1(i), MK_RX_RANGE_MASK_IDSTD2(i), MK_RX_RANGE_MASK_IDSTD3(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i), MK_RX_RANGE_CODE_IDSTD1(i), MK_RX_RANGE_CODE_IDSTD2(i), MK_RX_RANGE_CODE_IDSTD3(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 5)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i), MK_RX_RANGE_MASK_IDSTD1(i), MK_RX_RANGE_MASK_IDSTD2(i), MK_RX_RANGE_MASK_IDSTD3(i), MK_RX_RANGE_MASK_IDSTD4(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i), MK_RX_RANGE_CODE_IDSTD1(i), MK_RX_RANGE_CODE_IDSTD2(i), MK_RX_RANGE_CODE_IDSTD3(i), MK_RX_RANGE_CODE_IDSTD4(i)}
#  endif

#  if (kCanNumberOfUsedCanRxIdTables == 1)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 2)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i), MK_RX_RANGE_MASK_IDEXT1(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i), MK_RX_RANGE_CODE_IDEXT1(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 3)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i), MK_RX_RANGE_MASK_IDEXT1(i), MK_RX_RANGE_MASK_IDEXT2(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i), MK_RX_RANGE_CODE_IDEXT1(i), MK_RX_RANGE_CODE_IDEXT2(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 4)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i), MK_RX_RANGE_MASK_IDEXT1(i), MK_RX_RANGE_MASK_IDEXT2(i), MK_RX_RANGE_MASK_IDEXT3(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i), MK_RX_RANGE_CODE_IDEXT1(i), MK_RX_RANGE_CODE_IDEXT2(i), MK_RX_RANGE_CODE_IDEXT3(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 5)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i), MK_RX_RANGE_MASK_IDEXT1(i), MK_RX_RANGE_MASK_IDEXT2(i), MK_RX_RANGE_MASK_IDEXT3(i), MK_RX_RANGE_MASK_IDEXT4(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i), MK_RX_RANGE_CODE_IDEXT1(i), MK_RX_RANGE_CODE_IDEXT2(i), MK_RX_RANGE_CODE_IDEXT3(i), MK_RX_RANGE_CODE_IDEXT4(i)}
#  endif
# endif

/* calculate size of cond/ind-flags */
#  define kCanNumberOfConfBytes                  ((kCanNumberOfConfFlags + 7)/8)
# define kCanNumberOfConfWords                   ((kCanNumberOfConfFlags + 15)/16)
# define kCanNumberOfConfDWords                  ((kCanNumberOfConfFlags + 31)/32)
#  define kCanNumberOfIndBytes                   ((kCanNumberOfIndFlags + 7)/8)
# define kCanNumberOfIndWords                    ((kCanNumberOfIndFlags + 15)/16)
# define kCanNumberOfIndDWords                   ((kCanNumberOfIndFlags + 31)/32)

/* Macros for CAN message access within ApplCanMsgReceived() or PreCopy() function */

# if defined( C_ENABLE_EXTENDED_ID )
#  if defined( C_ENABLE_MIXED_ID )
#   define CanRxActualId(rxStruct)               ((CanRxActualIdType(rxStruct) == kCanIdTypeExt) ?      \
                                                 CanRxActualExtId(rxStruct) : ((vuint32)CanRxActualStdId(rxStruct)))         /* returns vuint32 */
#  else
#   define CanRxActualId(rxStruct)               (CanRxActualExtId(rxStruct))                                                /* returns vuint32 */
#  endif
# else
#  define CanRxActualId(rxStruct)                (CanRxActualStdId(rxStruct))                                                /* returns vuint16 */
# endif

/* Macros for CAN Status */
# define CanHwIsOk(state)                        (((state) & (kCanHwIsWarning |     \
                                                    kCanHwIsPassive |     \
                                                    kCanHwIsBusOff) )    ? 0 : 1)
# define CanHwIsWarning(state)                   (((state) & kCanHwIsWarning)      ? 1 : 0)
# define CanHwIsPassive(state)                   (((state) & kCanHwIsPassive)      ? 1 : 0)
# define CanHwIsBusOff(state)                    (((state) & kCanHwIsBusOff)       ? 1 : 0)
# define CanHwIsWakeup(state)                    (((state) & kCanHwIsSleep)        ? 0 : 1)
# define CanHwIsSleep(state)                     (((state) & kCanHwIsSleep)        ? 1 : 0)
# define CanHwIsStop(state)                      (((state) & kCanHwIsStop)         ? 1 : 0)
# define CanHwIsStart(state)                     (((state) & kCanHwIsStop)         ? 0 : 1)
# define CanIsOnline(state)                      (((state) & kCanTxOn)             ? 1 : 0)
# define CanIsOffline(state)                     (((state) & kCanTxOn)             ? 0 : 1)
# define CanHwIsInconsistent(state)              (((state) & kCanHwIsInconsistent) ? 1 : 0)

#  if defined( C_DRV_INTERNAL )
#   define CanGetTxId0(i)                        (CanTxId0[i])
#   define CanGetTxId1(i)                        (CanTxId1[i])
#   define CanGetTxId2(i)                        (CanTxId2[i])
#   define CanGetTxId3(i)                        (CanTxId3[i])
#   define CanGetTxId4(i)                        (CanTxId4[i])
#   if defined( C_ENABLE_EXTENDED_ID )
#    if defined( C_ENABLE_MIXED_ID )
#     if defined( C_HL_ENABLE_IDTYPE_IN_ID )
#      define CanGetTxIdType(i)                  (C_LL_TX_IDTYPE_TABLE[i] & kCanIdTypeExt)
#     else
#       define CanGetTxIdType(i)                 (CanTxIdType[i] & kCanIdTypeExt)
#     endif
#    else
#     define CanGetTxIdType(i)                   (kCanIdTypeExt)
#    endif
#   else
#    define CanGetTxIdType(i)                    (kCanIdTypeStd)
#   endif
#  endif /* C_DRV_INTERNAL */

#  define CanGetTxDlc(i)                         (CanTxDLC[i])
#  define CanGetTxDataPtr(i)                     (CanTxDataPtr[i])
#  define CanGetConfirmationOffset(i)            (CanConfirmationOffset[i])
#  define CanGetConfirmationMask(i)              (CanConfirmationMask[i])
#   define CanGetTxHwObj(i)                      (CanTxHwObj[i])
#  define CanGetTxSendMask(i)                    (CanTxSendMask[i])
#  define CanGetApplPreTransmitPtr(i)            (CanTxApplPreTransmitPtr[i])
#  define CanGetApplConfirmationPtr(i)           (CanTxApplConfirmationPtr[i])
#  define CanGetChannelOfTxObj(i)                (CanTxMsgHandleToChannel[i])

#  if defined( C_DRV_INTERNAL )
#   define CanGetRxId0(i)                        (CanRxId0[i])
#   define CanGetRxId1(i)                        (CanRxId1[i])
#   define CanGetRxId2(i)                        (CanRxId2[i])
#   define CanGetRxId3(i)                        (CanRxId3[i])
#   define CanGetRxId4(i)                        (CanRxId4[i])
#   if defined( C_ENABLE_EXTENDED_ID )
#    if defined( C_ENABLE_MIXED_ID )
#     if defined( C_HL_ENABLE_IDTYPE_IN_ID )
#      define CanGetRxIdType(i)                  (C_LL_RX_IDTYPE_TABLE[i] & kCanIdTypeExt)
#     else
#      define CanGetRxIdType(i)                  (CanRxIdType[i] & kCanIdTypeExt)
#     endif
#    else
#     define CanGetRxIdType(i)                   (kCanIdTypeExt)
#    endif
#   else
#    define CanGetRxIdType(i)                    (kCanIdTypeStd)
#   endif
#  endif /* C_DRV_INTERNAL */

#  define CanGetRxDataLen(i)                     (CanRxDataLen[i])
#  define CanGetRxMinDataLen(i)                  (CanRxMinDataLen[i])
#  define CanGetRxDataPtr(i)                     (CanRxDataPtr[i])
#  define CanGetIndicationOffset(i)              (CanIndicationOffset[i])
#  define CanGetIndicationMask(i)                (CanIndicationMask[i])
#  define CanGetApplPrecopyPtr(i)                (CanRxApplPrecopyPtr[i])
#  define CanGetApplIndicationPtr(i)             (CanRxApplIndicationPtr[i])

# if defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_DYN_TX_OBJECTS )  && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
  /* set confirmation active for CanReleaseDynTxObj() */
#  if defined( C_SINGLE_RECEIVE_CHANNEL ) 
#   define CanConfirmStart(txHandle)             {confirmHandle[0] = (txHandle);}                 /* PRQA S 3458 */ /* MD_Can_3458 */
#   define CanConfirmEnd()                       {confirmHandle[0] = kCanTxHandleNotUsed;}        /* PRQA S 3458 */ /* MD_Can_3458 */
#  else
#   define CanConfirmStart(channel, txHandle)    {confirmHandle[channel] = (txHandle);}           /* PRQA S 3458 */ /* MD_Can_3458 */
#   define CanConfirmEnd(channel)                {confirmHandle[channel] = kCanTxHandleNotUsed;}  /* PRQA S 3458 */ /* MD_Can_3458 */
#  endif
# endif

# if defined( C_ENABLE_PART_OFFLINE )
#  if defined( C_SINGLE_RECEIVE_CHANNEL ) 
#   define CanPartOffline(sendGroup)             (CanSetPartOffline( sendGroup))
#   define CanPartOnline(sendGroup)              (CanSetPartOnline( (vuint8)~(vuint8)(sendGroup)) )
#  else
#   define CanPartOffline(channel, sendGroup)    (CanSetPartOffline((channel), (sendGroup)))
#   define CanPartOnline(channel,  sendGroup)    (CanSetPartOnline((channel), (vuint8)~(vuint8)(sendGroup)) )
#  endif
# else
#  if defined( C_SINGLE_RECEIVE_CHANNEL ) 
#   define CanPartOffline(sendGroup)
#   define CanPartOnline(sendGroup)
#  else
#   define CanPartOffline(channel, sendGroup)
#   define CanPartOnline(channel, sendGroup)
#  endif
# endif

/* provide interface for interrupt disable and restore functions */
# define CanGlobalInterruptDisable               VStdSuspendAllInterrupts
# define CanGlobalInterruptRestore               VStdResumeAllInterrupts

# if ( C_SECURITY_LEVEL == 0 )
#  define CanDeclareGlobalInterruptOldStatus
#  define CanPutGlobalInterruptOldStatus(x)
#  define CanGetGlobalInterruptOldStatus(x)
#  define CanNestedGlobalInterruptDisable()
#  define CanNestedGlobalInterruptRestore()
# else  /* C_SECURITY_LEVEL == 0 */
#  define CanDeclareGlobalInterruptOldStatus     VStdDeclareGlobalInterruptOldStatus
#  define CanPutGlobalInterruptOldStatus(x)      VStdPutGlobalInterruptOldStatus(x)
#  define CanGetGlobalInterruptOldStatus(x)      VStdGetGlobalInterruptOldStatus(x)
#  if (VSTDLIB__COREHLL_VERSION  <  0x0216 )
#   define CanNestedGlobalInterruptDisable()      VStdNestedGlobalInterruptDisable()
#   define CanNestedGlobalInterruptRestore()      VStdNestedGlobalInterruptRestore()
#  else
#   define CanNestedGlobalInterruptDisable()      VStdGlobalInterruptDisable()
#   define CanNestedGlobalInterruptRestore()      VStdGlobalInterruptRestore()
#  endif
# endif /* C_SECURITY_LEVEL == 0 */

/* provide support for multiple callbacks */
#if !defined( APPL_CAN_GENERIC_PRECOPY )
# define APPL_CAN_GENERIC_PRECOPY                          ApplCanGenericPrecopy
#endif
#if !defined( APPL_CAN_TX_CONFIRMATION )
# define APPL_CAN_TX_CONFIRMATION                          ApplCanTxConfirmation
#endif
#if !defined( APPL_CAN_MSGTRANSMITCONF )
# define APPL_CAN_MSGTRANSMITCONF                          ApplCanMsgTransmitConf
#endif
#if !defined( APPL_CAN_MSGTRANSMITINIT )
# define APPL_CAN_MSGTRANSMITINIT                          ApplCanMsgTransmitInit
#endif
#if !defined( APPL_CAN_ONLINE )
# define APPL_CAN_ONLINE                                   ApplCanOnline
#endif
#if !defined( APPL_CAN_OFFLINE )
# define APPL_CAN_OFFLINE                                  ApplCanOffline
#endif
#if !defined( APPL_CAN_MSGRECEIVED )
# define APPL_CAN_MSGRECEIVED                              ApplCanMsgReceived
#endif
#if !defined( APPL_CAN_CANCELNOTIFICATION )
# define APPL_CAN_CANCELNOTIFICATION                       ApplCanCancelNotification
#endif
#if !defined( APPL_CAN_MSGCANCELNOTIFICATION )
# define APPL_CAN_MSGCANCELNOTIFICATION                    ApplCanMsgCancelNotification
#endif

#if defined( C_CPUTYPE_32BIT )
# define kCanTxQueueSize      ((kCanTxQueueBytes + 3) >> 2)
#endif

#if defined(MISRA_CHECK)
#endif

#if defined(C_ENABLE_SINGLE_PHYS_CHANNEL_OPTIMIZATION)
# define C_SINGLE_PHYS_CHANNEL
# define mCanLogToPhys(ch)           kCanLogToPhys
# define mCanTxBufOffset(ch)         kCanTxBufOffset
#else
# define C_MULTIPLE_PHYS_CHANNEL
# define mCanLogToPhys(ch)           CanLogToPhys[ch]
# define mCanTxBufOffset(ch)         CanTxBufOffset[ch]
#endif

#if defined( C_ENABLE_VARIABLE_DLC )
#define CanLL_DlcMask                0x00U
#endif

/* macros to set DLC and ID in rx-,tx-structures */
#define MK_RX_RANGE_MASK_IDSTD0(id)  (MK_STDID0(id))
#define MK_RX_RANGE_CODE_IDSTD0(id)  (MK_STDID0(id))
#define MK_RX_RANGE_MASK_IDEXT0(id)  (MK_EXTID0(id) & ~kCanIdTypeExt)
#define MK_RX_RANGE_CODE_IDEXT0(id)  (MK_EXTID0(id))

#define MK_STDID0(id)                ((id) & kCanStdIdMask)
#define MK_EXTID0(id)                (((id) & kCanExtIdMask) | kCanIdTypeExt)

#define C_RX_DIR                     0x00U
#define C_TX_DIR                     0x00U

#define MK_TX_DLC(dlc)               ((vuint8)((dlc) & kCanDlcLogMask))
#define MK_TX_DLC_EXT(dlc)           ((vuint8)((dlc) & kCanDlcLogMask))

/* extract  DLC from register format to logical format - return code has to be vuint8 */
#define XT_TX_DLC(dlc_raw)           ((vuint8)(dlc_raw))

#if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CanResetBusOffStart(a)
#   define CanResetBusOffEnd(a)      (CanInit(a))
#   define CanResetBusSleep(a)       (CanInit(a))
#else
#   define CanResetBusOffStart(ch, a)
#   define CanResetBusOffEnd(ch, a)  (CanInit((ch), (a)))
#  define CanResetBusSleep(ch, a)    (CanInit((ch), (a)))
#endif

#define CanRxActualIdRaw0(rxStruct)         ((tCanRxId0)(*((rxStruct)->pChipMsgObj)))
/* Macros for CAN message access within ApplCanMsgReceived() or PreCopy() function */
#if defined( C_ENABLE_EXTENDED_ID )
# define CanRxActualIdExtHi(rxStruct)       ((vuint8)((*((rxStruct)->pChipMsgObj) >> 24) & 0x1FU))                                   /* return code has to be vuint8     */
# define CanRxActualIdExtMidHi(rxStruct)    ((vuint8) (*((rxStruct)->pChipMsgObj) >> 16))                                            /* return code has to be vuint8     */
# define CanRxActualIdExtMidLo(rxStruct)    ((vuint8) (*((rxStruct)->pChipMsgObj) >> 8))                                             /* return code has to be vuint8     */
# define CanRxActualIdExtLo(rxStruct)       ((vuint8) (*((rxStruct)->pChipMsgObj)))                                                  /* return code has to be vuint8     */
#endif
#define CanRxActualIdType(rxStruct)         ((tCanIdType)(*((rxStruct)->pChipMsgObj) & kCanIdTypeExt))                               /* return code has to be tCanIdType */
#define CanRxActualExtId(rxStruct)          ((vuint32)(*((rxStruct)->pChipMsgObj) & kCanExtIdMask))                                  /* return code has to be vuint32    */
#define CanRxActualStdId(rxStruct)          ((vuint16)(*((rxStruct)->pChipMsgObj) & kCanStdIdMask))                                  /* return code has to be vuint16    */
#define CanRxActualData(rxStruct,i)         ((vuint8) (*((rxStruct)->pChipData+(i))))                                                /* return code has to be vuint8     */
# define CanRxActualDLC(rxStruct)           ((vuint8)((*((rxStruct)->pChipMsgObj+0x01) >> 28) & kCanDlcLogMask))                     /* return code has to be vuint8     */

/* Macros for CAN message access within GenericConfirmation() function */
#define CanTxActualIdType(txConfStruct)     CanRxActualIdType(txConfStruct)
#define CanTxActualExtId(txConfStruct)      CanRxActualExtId(txConfStruct)
#define CanTxActualStdId(txConfStruct)      CanRxActualStdId(txConfStruct)
#define CanTxActualData(txConfStruct,i)     CanRxActualData(txConfStruct,i)
# define CanTxActualDLC(txConfStruct)       CanRxActualDLC(txConfStruct)

# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define CanRxActualErrorCounter()         ((vuint8)(*((V_DEF_P2SFR_CAN(V_NONE, vuint8, AUTOMATIC)) CAN_CAST_ADDR((kCanBaseAdr + 0x0AU) + (mCanLogToPhys(0) << 4)))))
#  define CanTxActualErrorCounter()         ((vuint8)(*((V_DEF_P2SFR_CAN(V_NONE, vuint8, AUTOMATIC)) CAN_CAST_ADDR((kCanBaseAdr + 0x0BU) + (mCanLogToPhys(0) << 4)))))
# else
#  define CanRxActualErrorCounter(channel)  ((vuint8)(*((V_DEF_P2SFR_CAN(V_NONE, vuint8, AUTOMATIC)) CAN_CAST_ADDR((kCanBaseAdr + 0x0AU) + (mCanLogToPhys(channel) << 4)))))
#  define CanTxActualErrorCounter(channel)  ((vuint8)(*((V_DEF_P2SFR_CAN(V_NONE, vuint8, AUTOMATIC)) CAN_CAST_ADDR((kCanBaseAdr + 0x0BU) + (mCanLogToPhys(channel) << 4)))))
# endif

/* Macros for CAN message access within PreTransmit() function */
#if defined( C_ENABLE_EXTENDED_ID )
# define CanTxWriteActExtId(txStruct,id)    { *((CanChipMsgPtr32) CAN_CAST_ADDR((txStruct).pChipMsgObj)) = MK_EXTID0(id); }                     /* PRQA S 3458 */ /* MD_Can_3458 */
#endif
# define CanTxWriteActId(txStruct,id)       { *((CanChipMsgPtr32) CAN_CAST_ADDR((txStruct).pChipMsgObj)) = MK_STDID0(id); }                     /* PRQA S 3458 */ /* MD_Can_3458 */
# define CanTxWriteActDLC(txStruct,dlc)     { *((CanChipMsgPtr32) CAN_CAST_ADDR((txStruct).pChipMsgObj+0x01)) = ((dlc) << 28); }                /* PRQA S 3458 */ /* MD_Can_3458 */

/* Macros to fill variables of the type tCanMsgTransmitStruct */
#define CanMsgTransmitSetStdId(pCanMsgTransmitStruct, id)               { (pCanMsgTransmitStruct)->IdRaw0 = MK_STDID0(id); }                    /* PRQA S 3458 */ /* MD_Can_3458 */
#define CanMsgTransmitSetExtId(pCanMsgTransmitStruct, id)               { (pCanMsgTransmitStruct)->IdRaw0 = MK_EXTID0(id); }                    /* PRQA S 3458 */ /* MD_Can_3458 */
# define CanMsgTransmitSetDlc(pCanMsgTransmitStruct, dlc)               { (pCanMsgTransmitStruct)->DlcRaw = (vuint32)((vuint32)(dlc) << 28); }  /* PRQA S 3458 */ /* MD_Can_3458 */
#define CanMsgTransmitSetData(pCanMsgTransmitStruct, dataByte, msgData) { (pCanMsgTransmitStruct)->DataFld[dataByte] = (msgData); }             /* PRQA S 3458 */ /* MD_Can_3458 */

/* macros for buffer access */
#define StartRxReadSync()          (VStdSuspendAllInterrupts())
#define EndRxReadSync()            (VStdResumeAllInterrupts())

#define StartRxWriteSync()         (VStdSuspendAllInterrupts())
#define EndRxWriteSync()           (VStdResumeAllInterrupts())

#define StartTxReadSync()
#define EndTxReadSync()

#define StartTxWriteSync()         (VStdSuspendAllInterrupts())
#define EndTxWriteSync()           (VStdResumeAllInterrupts())

#define StartRxWriteCANSync()
#define EndRxWriteCANSync()

#define StartRxReadCANSync()
#define EndRxReadCANSync()

#define StartRxFullCANReadSync(Obj)
#define EndRxFullCANReadSync(Obj)

#define StartRxFullCANWriteSync(obj)
#define EndRxFullCANWriteSync(obj)

/* macros for flag access */
#define CanStartFlagWriteSync()    (VStdSuspendAllInterrupts())
#define CanEndFlagWriteSync()      (VStdResumeAllInterrupts())

/* *********************************************************************** */
/* error codes                                                             */
/* *********************************************************************** */
/* error numbers for User Assertions 0x00-0x1f - hardware independed */
# define kErrorTxDlcTooLarge                     ((vuint8)0x01)
# define kErrorTxHdlTooLarge                     ((vuint8)0x02)
# define kErrorIntRestoreTooOften                ((vuint8)0x03)
# define kErrorIntDisableTooOften                ((vuint8)0x04)
# define kErrorChannelHdlTooLarge                ((vuint8)0x05)
# define kErrorInitObjectHdlTooLarge             ((vuint8)0x06)
# define kErrorTxHwHdlTooLarge                   ((vuint8)0x07)
# define kErrorHwObjNotInPolling                 ((vuint8)0x08)
# define kErrorHwHdlTooSmall                     ((vuint8)0x09)
# define kErrorHwHdlTooLarge                     ((vuint8)0x0A)

# define kErrorAccessedInvalidDynObj             ((vuint8)0x0B)
# define kErrorAccessedStatObjAsDyn              ((vuint8)0x0C)
# define kErrorDynObjReleased                    ((vuint8)0x0D)

# define kErrorPollingTaskRecursion              ((vuint8)0x0E)
# define kErrorDisabledChannel                   ((vuint8)0x0F)
# define kErrorDisabledTxMessage                 ((vuint8)0x10)
# define kErrorDisabledCanInt                    ((vuint8)0x11)

# define kErrorCanSleep                          ((vuint8)0x12)
# define kErrorCanOnline                         ((vuint8)0x13)
# define kErrorCanStop                           ((vuint8)0x14)
# define kErrorWrongMask                         ((vuint8)0x15)
# define kErrorWrongId                           ((vuint8)0x16)
# define kErrorNullPointerParameter              ((vuint8)0x17)
# define kErrorTxFifoNotConfigured               ((vuint8)0x20)

/* error numbers for Gentool Assertions 0x40-0x5f */
# define kErrorTxROMDLCTooLarge                  ((vuint8)0x40)
# define kErrorWrongHwTxObjHandle                ((vuint8)0x41)
# define kErrorHwToLogTxObjCalculation           ((vuint8)0x42)

# define kErrorGenCheck                          ((vuint8)0x60)

/* error numbers for Hardware Assertions 0x80-0x9f */
# define kErrorTxBufferBusy                      ((vuint8)0x80)

/* error numbers for Internal Assertions 0xc0-0xdf */
# define kErrorTxHandleWrong                     ((vuint8)0xC0)
# define kErrorInternalTxHdlTooLarge             ((vuint8)0xC1)
# define kErrorRxHandleWrong                     ((vuint8)0xC2)        
# define kErrorTxObjHandleWrong                  ((vuint8)0xC3)
# define kErrorReleasedUnusedDynObj              ((vuint8)0xC4)
# define kErrorTxQueueTooManyHandle              ((vuint8)0xC5)
# define kErrorInternalChannelHdlTooLarge        ((vuint8)0xC6)
# define kErrorInternalDisabledChannel           ((vuint8)0xC7)
# define kErrorInternalDisabledTxMessage         ((vuint8)0xC8)

/* *********************************************************************** */
/* DummyFunction                                                           */
/* *********************************************************************** */
# if defined( C_DRV_INTERNAL )
#  define CAN_RECEIVE_FCT_DUMMY                  ApplCanRxStructPtrDummy
#  define CAN_RANGE_FCT_DUMMY                    ApplCanRxStructPtrDummy
#  define CAN_BUSOFF_FCT_DUMMY                   ApplCanChannelDummy
#   define CAN_INDICATION_FCT_DUMMY              V_NULL
#   define CAN_PRECOPY_FCT_DUMMY                 V_NULL
#   define CAN_CONFIRMATION_FCT_DUMMY            V_NULL
#   define CAN_PRETRANSMIT_FCT_DUMMY             V_NULL
# endif

# if defined( C_NO_COMPATIBILITY )
# else
/* *********************************************************************** */
/* compatibility defines                                                   */
/* *********************************************************************** */

#  define CAN_TX_DLC(i)                          (CanGetTxDlc(i))
#  define CAN_TX_DATA_PTR(i)                     (CanGetTxDataPtr(i))
#  define CAN_CONFIRMATION_OFFSET(i)             (CanGetConfirmationOffset(i))
#  define CAN_CONFIRMATION_MASK(i)               (CanGetConfirmationMask(i))

#  define CAN_RX_DATA_LEN(i)                     (CanGetRxDataLen(i))
#  define CAN_RX_DATA_PTR(i)                     (CanGetRxDataPtr(i))
#  define CAN_INDICATION_OFFSET(i)               (CanGetIndicationOffset(i))
#  define CAN_INDICATION_MASK(i)                 (CanGetIndicationMask(i))

#  define CanInterruptDisable()                  VStdSuspendAllInterrupts()
#  define CanInterruptRestore()                  VStdResumeAllInterrupts()

#  define ApplCanReceiveDummy0                   ApplCanRxStructPtrDummy
#  define ApplCanReceiveDummy1                   ApplCanChannelDummy

#  define CanGetTxDirectMsg                      (CanGetTxHwObj)

#  define canRxDlcRam                            (canVariableRxDataLen)

#  define CAN_START_INDEX_INIT_OBJ(i)            (CanInitObjectStartIndex[i])
#  define CAN_START_INDEX_TX_OBJ(i)              (CanTxStartIndex[i])
#  define CAN_START_INDEX_RX_OBJ(i)              (CanRxStartIndex[i])

#  if !defined( VGEN_GENY )
#   if defined( C_ENABLE_RANGE_EXTENDED_ID )
#    define MK_RX_RANGE_MASK0(id)                (MK_RX_RANGE_MASK_IDEXT0(id))
#    define MK_RX_RANGE_MASK1(id)                (MK_RX_RANGE_MASK_IDEXT1(id))
#    define MK_RX_RANGE_MASK2(id)                (MK_RX_RANGE_MASK_IDEXT2(id))
#    define MK_RX_RANGE_MASK3(id)                (MK_RX_RANGE_MASK_IDEXT3(id))
#    define MK_RX_RANGE_MASK4(id)                (MK_RX_RANGE_MASK_IDEXT4(id))

#    define MK_RX_RANGE_CODE0(id)                (MK_RX_RANGE_CODE_IDEXT0(id))
#    define MK_RX_RANGE_CODE1(id)                (MK_RX_RANGE_CODE_IDEXT1(id))
#    define MK_RX_RANGE_CODE2(id)                (MK_RX_RANGE_CODE_IDEXT2(id))
#    define MK_RX_RANGE_CODE3(id)                (MK_RX_RANGE_CODE_IDEXT3(id))
#    define MK_RX_RANGE_CODE4(id)                (MK_RX_RANGE_CODE_IDEXT4(id))
#   else
#    define MK_RX_RANGE_MASK0(id)                (MK_RX_RANGE_MASK_IDSTD0(id))
#    define MK_RX_RANGE_MASK1(id)                (MK_RX_RANGE_MASK_IDSTD1(id))
#    define MK_RX_RANGE_MASK2(id)                (MK_RX_RANGE_MASK_IDSTD2(id))
#    define MK_RX_RANGE_MASK3(id)                (MK_RX_RANGE_MASK_IDSTD3(id))
#    define MK_RX_RANGE_MASK4(id)                (MK_RX_RANGE_MASK_IDSTD4(id))

#    define MK_RX_RANGE_CODE0(id)                (MK_RX_RANGE_CODE_IDSTD0(id))
#    define MK_RX_RANGE_CODE1(id)                (MK_RX_RANGE_CODE_IDSTD1(id))
#    define MK_RX_RANGE_CODE2(id)                (MK_RX_RANGE_CODE_IDSTD2(id))
#    define MK_RX_RANGE_CODE3(id)                (MK_RX_RANGE_CODE_IDSTD3(id))
#    define MK_RX_RANGE_CODE4(id)                (MK_RX_RANGE_CODE_IDSTD4(id))
#   endif
#  endif

/* *********************************************************************** */
/* end of compatibility defines                                            */
/* *********************************************************************** */
# endif /* C_NO_COMPATIBILITY */

/* *********************************************************************** */
/* Memory qualifier                                                        */
/* *********************************************************************** */
/* memory qualifier for the CAN controller registers */
#define MEMORY_CAN

/* *********************************************************************** */
/* data types                                                              */
/* *********************************************************************** */

/* declare data type for the queue */
#if defined( C_CPUTYPE_32BIT )
typedef vuint32 tCanQueueElementType;
#endif

#if !defined( tCanTxQueuePadBits )
# define tCanTxQueuePadBits vuint8
#endif

/* data types for driver function parameters */
typedef vuint8            CanInitHandle;
typedef vuint8            CanChannelHandle;
typedef vuint16           CanObjectHandle;

typedef vuint16           CanTransmitHandle;
typedef vuint16           CanReceiveHandle;

/* define datatype of local signed variables for message handles */
typedef vsintx CanSignedTxHandle;

typedef vsintx CanSignedRxHandle;

V_DEF_P2SFR_CAN_TYPE(volatile, vuint8)  CanChipDataPtr;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint32) CanChipMsgPtr;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint16) CanChipMsgPtr16;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint32) CanChipMsgPtr32;

typedef vuint32          tCanTxId0;
typedef vuint32          tCanIdType;
typedef vuint32          tCanRxId0;

/* stucture of the CAN message object used by CanMsgTransmit() and RxQueue */
typedef struct
{
  tCanTxId0     IdRaw0;
  vuint32       DlcRaw;
  vuint8        DataFld[8];
} tCanMsgTransmitStruct;

V_DEF_P2VAR_TYPE(V_NONE, tCanMsgTransmitStruct, VAR_NOINIT) CanMsgTransmitStructPtrType;

# if defined( C_ENABLE_EXTENDED_ID )
typedef struct tCanFilterRulesBcTag
{
  vuint32 Code;
  vuint32 Mask;
} tCanFilterRulesBc;
# else
typedef struct tCanFilterRulesBcTag
{
  vuint16 Code;
  vuint16 Mask;
} tCanFilterRulesBc;
# endif

V_DEF_P2CONST_TYPE(V_NONE, vuint8, VAR_NOINIT) CanRxFifoDepth_TabPtrType;
V_DEF_P2CONST_TYPE(V_NONE, tCanFilterRulesBc, VAR_NOINIT) CanFilterRulesBc_TabPtrType;

typedef struct tCanChannelDataTag
{
  CanRxFifoDepth_TabPtrType CanRxFifoDepth;
  CanFilterRulesBc_TabPtrType CanFilterRulesBc;
# if defined(V_CPU_RH850)
  vuint32 CanIntcChTxBaseAdr;
  vuint32 CanIntcChErrorBaseAdr;
#  if defined(C_ENABLE_SLEEP_WAKEUP) && defined(C_ENABLE_BUSWAKEUP_SUPPORT)
  vuint32 CanIntcChWakeupBaseAdr;
#  endif
# endif
  vuint32 CanRxFcMask[kCanNumberOfSharedReg16];
  vuint16 CanTxIntMask;
  vuint16 CanFilterRulesStartIndex;
  vuint8 CanFilterRulesTotalCount;
  vuint8 CanFilterRulesBcCount;
  vuint8 CanRxBcMask;
  vuint8 CanRxBcMsgProcessCount;
  vuint8 CanRxBcStartIndex;
  vuint8 CanRxBcStopIndex;
# if defined(V_CPU_RH850)
  vuint8 CanIntPrio;
# endif
} tCanChannelData;

# if defined( C_ENABLE_CAN_CAN_INTERRUPT_CONTROL ) && !defined( C_ENABLE_OSEK_CAN_INTCTRL )
#  if ((defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING )) || \
       (defined( C_ENABLE_RX_FULLCAN_OBJECTS )  && !defined( C_ENABLE_RX_FULLCAN_POLLING  )) || \
       !defined( C_ENABLE_TX_POLLING )         || \
        defined( C_ENABLE_INDIVIDUAL_POLLING ) || \
       !defined( C_ENABLE_ERROR_POLLING )      || \
       !defined( C_ENABLE_LL_WAKEUP_POLLING ))
#   define C_ENABLE_LL_CAN_INTCTRL
#  endif
#  if defined( C_ENABLE_LL_WAKEUP_SUPPORT )
#   define C_ENABLE_LL_CAN_WAKEUP_INTCTRL
#  endif
# else
#  if ((defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING )) || \
       (defined( C_ENABLE_RX_FULLCAN_OBJECTS )  && !defined( C_ENABLE_RX_FULLCAN_POLLING  )) || \
       !defined( C_ENABLE_TX_POLLING )         || \
        defined( C_ENABLE_INDIVIDUAL_POLLING ) || \
       !defined( C_ENABLE_ERROR_POLLING )      || \
       !defined( C_ENABLE_LL_WAKEUP_POLLING ))
#   define C_ENABLE_LL_CAN_INTCB
#  endif
#  if defined( C_ENABLE_LL_WAKEUP_SUPPORT )
#   define C_ENABLE_LL_CAN_WAKEUP_INTCB
#  endif
# endif

typedef struct 
{
  CanChipDataPtr     pChipData;
  CanTransmitHandle  Handle;
/* CPU-specific part */
  CanChipMsgPtr      pChipMsgObj;
} tCanTxInfoStruct;

/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
typedef struct 
{
  CanChannelHandle   Channel;
  CanTransmitHandle  Handle;
/* CPU-specific part */
# if defined( C_ENABLE_CAN_TX_CONF_MSG_ACCESS )
  CanChipMsgPtr      pChipMsgObj;
  CanChipDataPtr     pChipData;
# endif
} tCanTxConfInfoStruct;

typedef struct 
{
  CanChannelHandle  Channel;
  CanChipMsgPtr     pChipMsgObj;
  CanChipDataPtr    pChipData;
  CanReceiveHandle  Handle;
/* CPU-specific part */
} tCanRxInfoStruct;

typedef tCanRxInfoStruct          *CanRxInfoStructPtr;
typedef tCanTxInfoStruct          CanTxInfoStruct;
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
typedef tCanTxConfInfoStruct      *CanTxInfoStructPtr;

/* types of application functions called by driver --------------------------- */
typedef C_CALLBACK_1 vuint8   (C_CALLBACK_2 *ApplCanMsgRcvFct)    (CanRxInfoStructPtr rxStruct);
typedef C_CALLBACK_1 vuint8   (C_CALLBACK_2 *ApplRangeFct)        (CanRxInfoStructPtr rxStruct);
typedef C_CALLBACK_1 vuint8   (C_CALLBACK_2 *ApplPrecopyFct)      (CanRxInfoStructPtr rxStruct);
typedef C_CALLBACK_1 void     (C_CALLBACK_2 *ApplIndicationFct)   (CanReceiveHandle rxObject);
typedef C_CALLBACK_1 void     (C_CALLBACK_2 *ApplConfirmationFct) (CanTransmitHandle txObject);
typedef C_CALLBACK_1 vuint8   (C_CALLBACK_2 *ApplPreTransmitFct)  (CanTxInfoStruct txStruct);
typedef C_CALLBACK_1 void     (C_CALLBACK_2 *ApplChannelFct)      (CAN_CHANNEL_CANTYPE_ONLY);

typedef struct
{
  tCanRxId0           Id0;
# if (kCanNumberOfUsedCanRxIdTables > 1)
  tCanRxId1           Id1;
# endif
# if (kCanNumberOfUsedCanRxIdTables > 2)
  tCanRxId2           Id2;
# endif     
# if (kCanNumberOfUsedCanRxIdTables > 3)
  tCanRxId3           Id3;
# endif
# if (kCanNumberOfUsedCanRxIdTables > 4)
  tCanRxId4           Id4;
# endif
} tCanStructRxIdType;

# if defined( C_DRV_INTERNAL )
typedef struct
{
  ApplChannelFct      ApplCanWakeUpFct; 
  ApplCanMsgRcvFct    ApplCanMsgReceivedFct;
  ApplRangeFct        ApplCanRangeFct[4];
  ApplChannelFct      ApplCanBusOffFct;
  ApplConfirmationFct ApplCanCancelNotificationFct;
  ApplChannelFct      ApplCanMsgTransmitCancelNotifyFct;
  tCanStructRxIdType  RangeMask[4];
  tCanStructRxIdType  RangeCode[4];
  vuint16             RangeActiveFlag;
  tCanIdType          RangeIdType[4];
} tCanChannelObject;
# endif

/* datatypes for indication and confirmation flags */
# if defined( C_ENABLE_CONFIRMATION_FLAG )
union CanConfirmationBits                                 
{    /* PRQA S 0750 */ /* MD_Can_0750 */
  vuint8         _c[kCanNumberOfConfBytes];
#  if defined( V_CPUTYPE_BITARRAY_32BIT )
#   if kCanNumberOfConfFlags > 16
  struct _c_bits32 w[kCanNumberOfConfDWords];
#   elif kCanNumberOfConfFlags > 8
  struct _c_bits16 w[kCanNumberOfConfWords];
#   else
  struct _c_bits8  w[1];
#   endif
#  else
#   if kCanNumberOfConfFlags > 8
  struct _c_bits16 w[kCanNumberOfConfWords];
#   else
  struct _c_bits8  w[1];
#   endif
#  endif
}; 
# endif

# if defined( C_ENABLE_INDICATION_FLAG )
union CanIndicationBits                                  
{    /* PRQA S 0750 */ /* MD_Can_0750 */
  vuint8         _c[kCanNumberOfIndBytes];
#  if defined( V_CPUTYPE_BITARRAY_32BIT )
#   if kCanNumberOfIndFlags > 16
  struct _c_bits32 w[kCanNumberOfIndDWords];
#   elif kCanNumberOfIndFlags > 8
  struct _c_bits16 w[kCanNumberOfIndWords];
#   else
  struct _c_bits8  w[1];
#   endif
#  else
#   if kCanNumberOfIndFlags > 8
  struct _c_bits16 w[kCanNumberOfIndWords];
#   else
  struct _c_bits8 w[1];
#   endif
#  endif
};
# endif

# if defined( C_ENABLE_RX_QUEUE )
/* struct for receive-Queue. Should correspond to t_MsgObject */
typedef struct
{
  CanReceiveHandle      Handle;
  CanChannelHandle      Channel;
  tCanMsgTransmitStruct CanChipMsgObj;
}
tCanRxQueueObject;

/* the queue */
typedef struct 
{
  tCanRxQueueObject canRxQueueBuf[kCanRxQueueSize];  /* buffer for msg and handle */  
  volatile vuintx   canRxQueueWriteIndex;            /* index in canRxQueueBuf */
  volatile vuintx   canRxQueueReadIndex;             /* index in canRxQueueBuf */
  volatile vuintx   canRxQueueCount;                 /* count of messages in canRxQueueBuf  */   
}
tCanRxQueue;
# endif

/* *********************************************************************** */
/* External Declarations                                                   */
/* *********************************************************************** */

/*  CAN driver version */
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kCanMainVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kCanSubVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kCanBugFixVersion;
/* ROM CATEGORY 4 END */

# if defined( C_ENABLE_PRECOPY_FCT )
/* RAM CATEGORY 1 START */
extern volatile CanReceiveHandle canRxHandle[kCanNumberOfChannels];
/* RAM CATEGORY 1 END */
# endif

# if defined( C_ENABLE_CONFIRMATION_FLAG )
/* RAM CATEGORY 1 START */
V_MEMRAM0 extern volatile V_MEMRAM1_NEAR union CanConfirmationBits V_MEMRAM2_NEAR CanConfirmationFlags;              /* PRQA S 0759 */ /* MD_Can_0750 */
/* RAM CATEGORY 1 END */
# endif

# if defined( C_ENABLE_INDICATION_FLAG )
/* RAM CATEGORY 1 START */
V_MEMRAM0 extern volatile V_MEMRAM1_NEAR union CanIndicationBits   V_MEMRAM2_NEAR CanIndicationFlags;                /* PRQA S 0759 */ /* MD_Can_0750 */
/* RAM CATEGORY 1 END */
# endif

# if defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_DYN_TX_OBJECTS )  && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
/* RAM CATEGORY 3 START */
extern CanTransmitHandle          confirmHandle[kCanNumberOfChannels];
/* RAM CATEGORY 3 END */
# endif

/* ##RI1.4 - 3.31: Dynamic Receive DLC */
# if defined( C_ENABLE_VARIABLE_RX_DATALEN )
#  if ( kCanNumberOfRxObjects > 0 )
/* RAM CATEGORY 1 START */
extern volatile vuint8 canVariableRxDataLen[kCanNumberOfRxObjects];
/* RAM CATEGORY 1 END */
#  endif
# endif

/* RAM CATEGORY 1 START */
extern CanChipDataPtr canRDSRxPtr[kCanNumberOfChannels];
/* RAM CATEGORY 1 END */

/* *********************************************************************** */
/* Data structures filled with data by parameter generating tool           */
/* *********************************************************************** */

# if defined( C_DRV_INTERNAL )
/* structures for init and common objects ----------------------- */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#  else
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 tCanChannelObject   V_MEMROM2 CanChannelObject[kCanNumberOfChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 vuint8              V_MEMROM2 CanInitObjectStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 4 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanTransmitHandle   V_MEMROM2 CanTxDynRomStartIndex[kCanNumberOfChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanTransmitHandle   V_MEMROM2 CanTxDynRamStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle    V_MEMROM2 CanRxBasicStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle    V_MEMROM2 CanRxFullStartIndex[kCanNumberOfHwChannels+1];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanLogHwTxStartIndex[kCanNumberOfHwChannels+1];
/* ROM CATEGORY 2 END */

/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwTxStartIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 2 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwRxFullStartIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwRxBasicStartIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwUnusedStartIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 4 END */
/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwTxStopIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 2 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwRxFullStopIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwRxBasicStopIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwUnusedStopIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 4 END */

/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwMsgTransmitIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwTxNormalIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 vsintx              V_MEMROM2 CanTxOffsetHwToLog[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */

#  endif  /* C_SINGLE_RECEIVE_CHANNEL */

#  if defined( C_ENABLE_INDIVIDUAL_POLLING )
/* ROM CATEGORY 1 START */
/* define first index to array CanHwObjIndivPolling[][] */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2     CanHwObjIndivPolling[1][kCanNumberOfHwObjIndivPolling];
/* ROM CATEGORY 1 END */
#  endif

# endif /* C_DRV_INTERNAL */

# if defined( C_SINGLE_RECEIVE_CHANNEL )
# else
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanTransmitHandle   V_MEMROM2 CanTxStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 1 END */ 
/* ROM CATEGORY 2 START */ 
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle    V_MEMROM2 CanRxStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 2 END */
# endif

/* ROM generated */

# if ( kCanNumberOfTxObjects > 0 )
#   if defined( C_DRV_INTERNAL )
/* structures for transmit objects ----------------------- */
/* ROM CATEGORY 1 START */ 
V_MEMROM0 extern V_MEMROM1 tCanTxId0 V_MEMROM2       CanTxId0[kCanNumberOfTxObjects];  
#    if (kCanNumberOfUsedCanTxIdTables > 1)
V_MEMROM0 extern V_MEMROM1 tCanTxId1 V_MEMROM2       CanTxId1[kCanNumberOfTxObjects];  
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 2)
V_MEMROM0 extern V_MEMROM1 tCanTxId2 V_MEMROM2       CanTxId2[kCanNumberOfTxObjects];  
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 3)
V_MEMROM0 extern V_MEMROM1 tCanTxId3 V_MEMROM2       CanTxId3[kCanNumberOfTxObjects];  
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 4)
V_MEMROM0 extern V_MEMROM1 tCanTxId4 V_MEMROM2       CanTxId4[kCanNumberOfTxObjects];  
#    endif

#    if defined( C_ENABLE_MIXED_ID )
#    endif
/* ROM CATEGORY 1 END */
#   endif /* C_DRV_INTERNAL */

/* ROM CATEGORY 2 START */
#   if defined( C_ENABLE_PART_OFFLINE )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2          CanTxSendMask[kCanNumberOfTxObjects];
#   endif
/* ROM CATEGORY 2 END */

/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2          CanTxDLC[kCanNumberOfTxObjects];
V_MEMROM0 extern V_MEMROM1 TxDataPtr V_MEMROM2       CanTxDataPtr[kCanNumberOfTxObjects];

#   if defined( C_ENABLE_CONFIRMATION_FLAG )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2          CanConfirmationOffset[kCanNumberOfTxObjects];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2          CanConfirmationMask[kCanNumberOfTxObjects];
#   endif
#   if defined( C_ENABLE_CONFIRMATION_FCT )
V_MEMROM0 extern V_MEMROM1 ApplConfirmationFct V_MEMROM2 CanTxApplConfirmationPtr[kCanNumberOfTxObjects];
#   endif
#   if defined( C_ENABLE_PRETRANSMIT_FCT )
V_MEMROM0 extern V_MEMROM1 ApplPreTransmitFct  V_MEMROM2 CanTxApplPreTransmitPtr[kCanNumberOfTxObjects];
#   endif
/* ROM CATEGORY 1 END */

#   if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
/* ROM CATEGORY 2 START */
#     if defined ( C_ENABLE_HW_OBJ_EXCEED_255_DRV ) &&\
         defined ( C_ENABLE_HW_OBJ_EXCEED_255_CFG )
V_MEMROM0 extern V_MEMROM1 CanObjectHandle V_MEMROM2 CanTxHwObj[kCanNumberOfTxObjects];
#     else
V_MEMROM0 extern V_MEMROM1 vuint8          V_MEMROM2 CanTxHwObj[kCanNumberOfTxObjects];
#     endif
/* ROM CATEGORY 2 END */
#   endif

#   if defined( C_SINGLE_RECEIVE_CHANNEL )
#   else
#    if ( kCanNumberOfTxObjects > 0 )
/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanChannelHandle    V_MEMROM2 CanTxMsgHandleToChannel[kCanNumberOfTxObjects];
/* ROM CATEGORY 2 END */
#    endif
#   endif /* C_SINGLE_RECEIVE_CHANNEL */ 

#   if defined( C_ENABLE_MULTI_ECU_PHYS )
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 tVIdentityMsk V_MEMROM2      CanTxIdentityAssignment[kCanNumberOfTxObjects];
/* ROM CATEGORY 4 END */
#   endif

#  if defined( C_ENABLE_TRANSMIT_QUEUE )
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
/* ROM CATEGORY 1 START */
/* pad bits added before the current channel position */
V_MEMROM0 extern  V_MEMROM1 tCanTxQueuePadBits V_MEMROM2 CanTxQueuePadBits[kCanNumberOfChannels];

/* start / stop indices for the element search */
V_MEMROM0 extern V_MEMROM1 CanSignedTxHandle V_MEMROM2 CanTxQueueStartIndex[kCanNumberOfChannels + 1];
/* ROM CATEGORY 1 END */
#endif
#  endif

# endif /* ( kCanNumberOfTxObjects > 0 ) */

/* structures for basic and full can receive objects ----------------------- */

# if ( kCanNumberOfRxObjects > 0 )
#  if defined( C_DRV_INTERNAL )
/* ROM CATEGORY 1 START */
#   if defined( C_SEARCH_HASH ) ||\
      defined( C_SEARCH_INDEX )
#    if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
V_MEMROM0 extern V_MEMROM1 tCanRxId0 V_MEMROM2       CanRxId0[kCanNumberOfRxFullCANObjects];  
#     if (kCanNumberOfUsedCanRxIdTables > 1)
V_MEMROM0 extern V_MEMROM1 tCanRxId1 V_MEMROM2       CanRxId1[kCanNumberOfRxFullCANObjects];  
#     endif
#     if (kCanNumberOfUsedCanRxIdTables > 2)
V_MEMROM0 extern V_MEMROM1 tCanRxId2 V_MEMROM2       CanRxId2[kCanNumberOfRxFullCANObjects];  
#     endif
#     if (kCanNumberOfUsedCanRxIdTables > 3)
V_MEMROM0 extern V_MEMROM1 tCanRxId3 V_MEMROM2       CanRxId3[kCanNumberOfRxFullCANObjects];  
#     endif
#     if (kCanNumberOfUsedCanRxIdTables > 4)
V_MEMROM0 extern V_MEMROM1 tCanRxId4 V_MEMROM2       CanRxId4[kCanNumberOfRxFullCANObjects];  
#     endif

#     if defined( C_ENABLE_MIXED_ID )
#      if defined( C_HL_ENABLE_IDTYPE_IN_ID )
#      else
V_MEMROM0 extern V_MEMROM1 tCanIdType V_MEMROM2      CanRxIdType[kCanNumberOfRxFullCANObjects];
#      endif
#     endif
#    endif /* C_ENABLE_RX_FULLCAN_OBJECTS */
#   else   /* C_SEARCH_HASH */
V_MEMROM0 extern V_MEMROM1 tCanRxId0 V_MEMROM2       CanRxId0[kCanNumberOfRxObjects];  
#    if (kCanNumberOfUsedCanRxIdTables > 1)
V_MEMROM0 extern V_MEMROM1 tCanRxId1 V_MEMROM2       CanRxId1[kCanNumberOfRxObjects];  
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 2)
V_MEMROM0 extern V_MEMROM1 tCanRxId2 V_MEMROM2       CanRxId2[kCanNumberOfRxObjects];  
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 3)
V_MEMROM0 extern V_MEMROM1 tCanRxId3 V_MEMROM2       CanRxId3[kCanNumberOfRxObjects];  
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 4)
V_MEMROM0 extern V_MEMROM1 tCanRxId4 V_MEMROM2       CanRxId4[kCanNumberOfRxObjects];  
#    endif

#    if defined( C_ENABLE_MIXED_ID )
#     if defined( C_HL_ENABLE_IDTYPE_IN_ID )
#     else
V_MEMROM0 extern V_MEMROM1 tCanIdType V_MEMROM2      CanRxIdType[kCanNumberOfRxObjects];
#     endif
#    endif
#   endif  /* C_SEARCH_HASH */

#   if defined( C_SEARCH_HASH )
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxMsgIndirection[kHashSearchListCount + kHashSearchListCountEx + kCanNumberOfRxFullCANObjects];
#   else
#    if defined( C_SEARCH_INDEX )
 /*  Size of array CanRxMsgIndirection is zero if index search and no Rx FullCANs are used; ESCAN00059562 */
#     if defined (C_ENABLE_RX_FULLCAN_OBJECTS)
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxMsgIndirection[kCanNumberOfRxFullCANObjects];
#     endif
#    else
#     if defined( C_ENABLE_RX_MSG_INDIRECTION )
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxMsgIndirection[kCanNumberOfRxObjects];
#     endif
#    endif
#   endif

#   if defined( C_SEARCH_HASH )
#    if defined( C_ENABLE_EXTENDED_ID )
#     if( kHashSearchListCountEx > 0)
V_MEMROM0 extern V_MEMROM1 vuint32 V_MEMROM2              CanRxHashIdEx[kHashSearchListCountEx];
#     endif /* (kHashSearchListCountEx > 0) */
#     if defined( C_ENABLE_MIXED_ID )
#      if( kHashSearchListCount > 0)
V_MEMROM0 extern V_MEMROM1 vuint16 V_MEMROM2              CanRxHashId[kHashSearchListCount];
#      endif
#     endif
#    else
#     if( kHashSearchListCount > 0)
V_MEMROM0 extern V_MEMROM1 vuint16 V_MEMROM2              CanRxHashId[kHashSearchListCount];
#     endif 
#    endif
#   endif

#   if defined( C_SEARCH_INDEX )
#    if defined( C_SINGLE_RECEIVE_CHANNEL )
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxIndexTbl[2048];
#    else
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxIndexTbl[kCanNumberOfChannels][2048];
#    endif
#   endif
#   if defined( C_ENABLE_MULTI_ECU_PHYS )
V_MEMROM0 extern V_MEMROM1 tVIdentityMsk V_MEMROM2           CanRxIdentityAssignment[kCanNumberOfRxObjects];
#   endif

#   if defined( C_ENABLE_RX_QUEUE_RANGE )
#    if defined( C_ENABLE_RANGE_0 )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanRxQueueRange0[kCanNumberOfChannels];
#    endif
#    if defined( C_ENABLE_RANGE_1 )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanRxQueueRange1[kCanNumberOfChannels];
#    endif
#    if defined( C_ENABLE_RANGE_2 )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanRxQueueRange2[kCanNumberOfChannels];
#    endif
#    if defined( C_ENABLE_RANGE_3 )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanRxQueueRange3[kCanNumberOfChannels];
#    endif
#   endif
/* ROM CATEGORY 1 END */

/* ROM CATEGORY 4 START */
#   if defined( C_ENABLE_MULTIPLE_BASICCAN ) && \
       defined( C_ENABLE_GEN_CHECK )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanNumberOfBasicCAN[kCanNumberOfChannels];
#   endif
/* ROM CATEGORY 4 END */

#  endif /* C_DRV_INTERNAL */

/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 vuint8               V_MEMROM2 CanRxDataLen[kCanNumberOfRxObjects];
#   if defined( C_ENABLE_DLC_CHECK_MIN_DATALEN )
V_MEMROM0 extern V_MEMROM1 vuint8               V_MEMROM2 CanRxMinDataLen[kCanNumberOfRxObjects];
#   endif
V_MEMROM0 extern V_MEMROM1 RxDataPtr            V_MEMROM2 CanRxDataPtr[kCanNumberOfRxObjects];

#   if defined( C_ENABLE_PRECOPY_FCT )
V_MEMROM0 extern V_MEMROM1 ApplPrecopyFct       V_MEMROM2 CanRxApplPrecopyPtr[kCanNumberOfRxObjects];
#   endif
#   if defined( C_ENABLE_INDICATION_FLAG )
V_MEMROM0 extern V_MEMROM1 vuint8               V_MEMROM2 CanIndicationOffset[kCanNumberOfRxObjects];
V_MEMROM0 extern V_MEMROM1 vuint8               V_MEMROM2 CanIndicationMask[kCanNumberOfRxObjects];
#   endif
#   if defined( C_ENABLE_INDICATION_FCT )
V_MEMROM0 extern V_MEMROM1 ApplIndicationFct    V_MEMROM2 CanRxApplIndicationPtr[kCanNumberOfRxObjects];
#   endif
/* ROM CATEGORY 1 END */
# endif /* ( kCanNumberOfRxObjects > 0 ) */

/* ROM CATEGORY 1 START */
#if defined(C_MULTIPLE_PHYS_CHANNEL)
V_DEF_CONST(extern, vuint8, CONST) CanLogToPhys[kCanNumberOfHwChannels];
V_DEF_CONST(extern, CanObjectHandle, CONST) CanTxBufOffset[kCanNumberOfHwChannels];
#endif
V_DEF_CONST(extern, tCanChannelData, CONST) CanChannelData[kCanNumberOfHwChannels];
# if ((defined(V_CPU_RH850) && defined(C_MULTIPLE_RECEIVE_CHANNEL)))
V_DEF_CONST(extern, vuint8, CONST) CanFifoToLogChannel[kVNumberOfIdentities][kCanNumberOfRxFifos];
# endif
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 4 START */
V_DEF_CONST(extern, vuint32, CONST) CanInitBCFG[kCanNumberOfInitObjects];
/* ROM CATEGORY 4 END */

/* *********************************************************************** */
/* Callback functions                                                      */
/* *********************************************************************** */

# if defined( C_ENABLE_INTCTRL_ADD_CAN_FCT )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanAddCanInterruptRestore(CanChannelHandle channel) C_API_3;
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanAddCanInterruptDisable(CanChannelHandle channel) C_API_3;
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_HARDWARE_CHECK ) || \
    defined( C_ENABLE_USER_CHECK )     || \
    defined( C_ENABLE_GEN_CHECK )      || \
    defined( C_ENABLE_INTERNAL_CHECK ) 
/* CODE CATEGORY 4 START */ 
C_CALLBACK_1 void C_CALLBACK_2 ApplCanFatalError(CAN_CHANNEL_CANTYPE_FIRST vuint8 errorNumber) C_API_3;
/* CODE CATEGORY 4 END */
# endif

# if defined( C_SINGLE_RECEIVE_CHANNEL )
/* these two functions are declared by the tool in case of multichannel */
/* CODE CATEGORY 4 START */ 
C_CALLBACK_1 void C_CALLBACK_2 ApplCanBusOff(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */ 
C_CALLBACK_1 void C_CALLBACK_2 ApplCanWakeUp(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif
# if defined( C_ENABLE_APPLCANPREWAKEUP_FCT )
/* CODE CATEGORY 4 START */ 
C_CALLBACK_1 void C_CALLBACK_2 ApplCanPreWakeUp(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif
# if defined( C_ENABLE_OVERRUN )
/* CODE CATEGORY 4 START */ 
C_CALLBACK_1 void C_CALLBACK_2 ApplCanOverrun ( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif

/* Range precopy/ generic precopy functions ****************************** */
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  if defined( C_ENABLE_RANGE_0 )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRange0Precopy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_RANGE_1 )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRange1Precopy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_RANGE_2 )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRange2Precopy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_RANGE_3 )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRange3Precopy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
#  endif
# endif

# if defined( C_ENABLE_COND_RECEIVE_FCT )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanMsgCondReceived  ( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_CAN_RAM_CHECK )
#  if defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanCorruptMailbox(CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle hwObjHandle);
/* CODE CATEGORY 4 END */
#  endif  /* defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX ) */
/* CODE CATEGORY 4 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanMemCheckFailed(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif  /* defined ( C_ENABLE_CAN_RAM_CHECK ) */

# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  if defined( C_ENABLE_RECEIVE_FCT )
/* in case of multiple CAN channels this function is declared by the tool */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 APPL_CAN_MSGRECEIVED(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */
#  endif
# endif

/* ##RI1.4 - 2.7: Callbackfunction-DLC-Check */
# if defined( C_ENABLE_DLC_FAILED_FCT )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanMsgDlcFailed( CanRxInfoStructPtr rxStruct ); 
/* CODE CATEGORY 4 END */ 
# endif  /* C_ENABLE_DLC_FAILED_FCT */

# if defined( C_ENABLE_GENERIC_PRECOPY )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 APPL_CAN_GENERIC_PRECOPY( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_NOT_MATCHED_FCT )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanMsgNotMatched( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_CAN_TX_CONF_FCT )
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_TX_CONFIRMATION(CanTxInfoStructPtr txStruct);
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_TX_OBSERVE )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanTxObjStart( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObject );
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanTxObjConfirmed( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObject );
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanInit( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObjectFirstUsed, CanObjectHandle txHwObjectFirstUnused);
/* CODE CATEGORY 4 END */
# endif

# if defined( C_ENABLE_HW_LOOP_TIMER )
/* CODE CATEGORY 2 START */
C_CALLBACK_1 void     C_CALLBACK_2 ApplCanTimerStart(CAN_CHANNEL_CANTYPE_FIRST vuint8 source);
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanTimerLoop (CAN_CHANNEL_CANTYPE_FIRST vuint8 source);
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
C_CALLBACK_1 void     C_CALLBACK_2 ApplCanTimerEnd  (CAN_CHANNEL_CANTYPE_FIRST vuint8 source);
/* CODE CATEGORY 2 END */
# endif

# if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_MSGTRANSMITCONF(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_MSGTRANSMITINIT(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif

# if defined( C_SINGLE_RECEIVE_CHANNEL )
/* in case of multichannel these two functions are declared by the tool */
#  if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
/* CODE CATEGORY 3 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_CANCELNOTIFICATION( CanTransmitHandle txHandle );
/* CODE CATEGORY 3 END */
#  endif
#  if defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
/* CODE CATEGORY 3 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_MSGCANCELNOTIFICATION( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
#  endif
# endif

# if defined( C_ENABLE_RX_QUEUE )
#  if defined( C_ENABLE_APPLCANPRERXQUEUE )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanPreRxQueue( CanRxInfoStructPtr pCanRxInfoStruct );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_RXQUEUE_OVERRUN_NOTIFY )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanRxQueueOverrun( void );
/* CODE CATEGORY 4 END */
#  endif
# endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
/* CODE CATEGORY 3 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanChannelDummy( CanChannelHandle channel );
/* CODE CATEGORY 3 END */
# endif
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) 
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanTxHandleDummy( CanTransmitHandle txHandle );
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRxStructPtrDummy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
# endif
# if defined( C_ENABLE_ONLINE_OFFLINE_CALLBACK_FCT )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_OFFLINE( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_ONLINE( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif

# if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) &&\
     defined (C_ENABLE_OSEK_CAN_INTCTRL)
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 OsCanCanInterruptDisable( CAN_HW_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 OsCanCanInterruptRestore( CAN_HW_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 1 END */
# endif

#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
# if defined(C_ENABLE_LL_CAN_INTCB) || defined(C_ENABLE_LL_CAN_WAKEUP_INTCB)
/* CODE CATEGORY 4 START */
V_DEF_FUNC_CBK(extern, void, APPL_CODE) ApplCanWakeupInterruptEnable(vuint8 Controller);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
V_DEF_FUNC_CBK(extern, void, APPL_CODE) ApplCanWakeupInterruptDisable(vuint8 Controller);
/* CODE CATEGORY 4 END */
# endif
# if defined(C_ENABLE_WAKEUP_POLLING) && defined(C_ENABLE_LL_CAN_WAKEUP_INTCB)
/* CODE CATEGORY 4 START */
V_DEF_FUNC_CBK(extern, vuint8, APPL_CODE) ApplCanWakeupOccurred(vuint8 Controller);
/* CODE CATEGORY 4 END */
# endif
#endif

#if defined(V_CPU_RH850) && defined(C_ENABLE_INTC_ACCESS_BY_APPL)
/* CODE CATEGORY 1 START */
V_DEF_FUNC_CBK(extern, void, APPL_CODE) ApplCanWriteIcr8(vuint32 Address, vuint8 Value);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
V_DEF_FUNC_CBK(extern, vuint8, APPL_CODE) ApplCanReadIcr8(vuint32 Address);
/* CODE CATEGORY 1 END */
#endif

#if defined(V_CPU_RH850) && defined(C_ENABLE_ECC_CALLOUT)
/* CODE CATEGORY 4 START */
V_DEF_FUNC_CBK(extern, void, APPL_CODE) ApplCanEccConfiguration(void);
/* CODE CATEGORY 4 END */
#endif

#if defined(C_ENABLE_CAN_HW_RAM_CHECK)
/* CODE CATEGORY 4 START */
V_DEF_FUNC_CBK(extern, vuint8, APPL_CODE) ApplCanGlobalMemCheckFailed(void);
/* CODE CATEGORY 4 END */
#endif

/* *********************************************************************** */
/* function prototypes                                                     */
/* *********************************************************************** */

/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanInitPowerOn( void );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanInit( CAN_CHANNEL_CANTYPE_FIRST CanInitHandle initObject );
/* CODE CATEGORY 4 END */

# if defined( C_ENABLE_CAN_TRANSMIT )
/* CODE CATEGORY 2 START */
C_API_1 vuint8 C_API_2 CanTransmit(CanTransmitHandle txHandle) C_API_3;
/* CODE CATEGORY 2 END */
#  if defined( C_ENABLE_VARIABLE_DLC )
/* CODE CATEGORY 2 START */
C_API_1 vuint8 C_API_2 CanTransmitVarDLC( CanTransmitHandle txHandle, vuint8 dlc) C_API_3;
/* CODE CATEGORY 2 END */
#  endif
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanCancelTransmit( CanTransmitHandle txHandle );
/* CODE CATEGORY 3 END */
# endif

# if defined( C_ENABLE_MSG_TRANSMIT )
/* CODE CATEGORY 2 START */

# if defined ( V_ENABLE_USED_GLOBAL_VAR )
/* txMsgStruct is located in far memory */
C_API_1 vuint8 C_API_2 CanMsgTransmit( CAN_CHANNEL_CANTYPE_FIRST V_MEMRAM1_FAR tCanMsgTransmitStruct V_MEMRAM2_FAR V_MEMRAM3_FAR *txMsgStruct );
# else
C_API_1 vuint8 C_API_2 CanMsgTransmit( CAN_CHANNEL_CANTYPE_FIRST tCanMsgTransmitStruct *txMsgStruct);
# endif

/* CODE CATEGORY 2 END */
#  if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanCancelMsgTransmit( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
#  endif
# endif

# if defined( C_ENABLE_OFFLINE )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanOnline( CAN_CHANNEL_CANTYPE_ONLY );           /* switch CanStatus to On */
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanOffline( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 4 END */
# endif

# if defined( C_ENABLE_PART_OFFLINE )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPartOffline( CAN_CHANNEL_CANTYPE_FIRST vuint8 sendGroup);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPartOnline( CAN_CHANNEL_CANTYPE_FIRST vuint8 invSendGroup);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanGetPartMode( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif

/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanGetStatus( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 3 END */

/* CanSleep functions */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanSleep( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanWakeUp( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */

# if defined( C_ENABLE_ECU_SWITCH_PASS )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetActive(  CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPassive( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# else
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
#   define    CanSetActive( channel )            /* remove calls to setActive/Passive */
#   define    CanSetPassive( channel )
#  else
#   define    CanSetActive( )                    /* remove calls to setActive/Passive */
#   define    CanSetPassive( )
#  endif
# endif

# if defined( C_ENABLE_STOP )
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanStart( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanStop( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif

# if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL)
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 CanCanInterruptDisable( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 CanCanInterruptRestore( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_TX_POLLING ) || \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  || \
    defined( C_ENABLE_RX_BASICCAN_POLLING ) || \
    defined( C_ENABLE_ERROR_POLLING ) || \
    defined( C_ENABLE_WAKEUP_POLLING ) 
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTask(void);
/* CODE CATEGORY 2 END */
# endif
# if defined( C_ENABLE_TX_POLLING ) 
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTxTask( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 2 END */
# endif
# if defined( C_ENABLE_TX_POLLING ) && \
     defined( C_ENABLE_INDIVIDUAL_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTxObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle);
/* CODE CATEGORY 2 END */
# endif
# if defined( C_ENABLE_ERROR_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanErrorTask( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 2 END */
# endif
# if defined( C_ENABLE_SLEEP_WAKEUP )
#  if defined( C_ENABLE_WAKEUP_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanWakeUpTask(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
#  endif
# endif
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) && \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxFullCANTask(CAN_CHANNEL_CANTYPE_ONLY) C_API_3;
/* CODE CATEGORY 2 END */
#  if defined( C_ENABLE_INDIVIDUAL_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxFullCANObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);
/* CODE CATEGORY 2 END */
#  endif
# endif
#if defined( C_ENABLE_RX_BASICCAN_POLLING ) && \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxBasicCANTask(CAN_CHANNEL_CANTYPE_ONLY) C_API_3;
/* CODE CATEGORY 2 END */
#  if defined( C_ENABLE_INDIVIDUAL_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxBasicCANObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);
/* CODE CATEGORY 2 END */
#  endif
# endif

# if defined( C_ENABLE_DYN_TX_OBJECTS )
/* CODE CATEGORY 3 START */
C_API_1 CanTransmitHandle C_API_2 CanGetDynTxObj(CanTransmitHandle txHandle ) C_API_3;
/* CODE CATEGORY 3 END */
/* CODE CATEGORY 3 START */
C_API_1 vuint8          C_API_2 CanReleaseDynTxObj(CanTransmitHandle txHandle) C_API_3;
/* CODE CATEGORY 3 END */

#  if defined( C_ENABLE_DYN_TX_ID )
#   if !defined( C_ENABLE_EXTENDED_ID ) ||\
     defined( C_ENABLE_MIXED_ID )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetId(CanTransmitHandle txHandle, vuint16 id) C_API_3;
/* CODE CATEGORY 2 END */
#   endif
#   if defined( C_ENABLE_EXTENDED_ID )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetExtId(CanTransmitHandle txHandle, vuint16 idExtHi, vuint16 idExtLo) C_API_3;
/* CODE CATEGORY 2 END */
#   endif
#  endif
#  if defined( C_ENABLE_DYN_TX_DLC )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetDlc(CanTransmitHandle txHandle, vuint8 dlc) C_API_3;
/* CODE CATEGORY 2 END */
#  endif
#  if defined( C_ENABLE_DYN_TX_DATAPTR )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetDataPtr(CanTransmitHandle txHandle, void* pData) C_API_3;
/* CODE CATEGORY 2 END */
#  endif

# endif /* defined( C_ENABLE_DYN_TX_OBJECTS ) */

# if defined( C_ENABLE_TX_MASK_EXT_ID )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtHi( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtMidHi( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtMidLo( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtLo( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask );
/* CODE CATEGORY 4 END */
# endif

# if defined( C_ENABLE_TX_OBSERVE )
/* CODE CATEGORY 3 START */
C_API_1 CanTransmitHandle C_API_2 CanTxGetActHandle( CanObjectHandle logicalTxHdl ) C_API_3;
/* CODE CATEGORY 3 END */
# endif

# if defined( C_ENABLE_COND_RECEIVE_FCT )
/* CODE CATEGORY 3 START */
C_API_1 void     C_API_2 CanSetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
/* CODE CATEGORY 3 START */
C_API_1 void     C_API_2 CanResetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanGetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
# endif

# if defined( C_ENABLE_RX_QUEUE )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanDeleteRxQueue(void);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanHandleRxMsg(void);
/* CODE CATEGORY 2 END */
# endif

/* Additional API for QNX */

# if defined ( C_ENABLE_MEMCOPY_SUPPORT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanCopyToCan(CanChipDataPtr dst, V_DEF_P2VAR_PARA(V_NONE, void, AUTOMATIC, APPL_VAR) src, vuint8 len) C_API_3;
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanCopyFromCan(V_DEF_P2VAR_PARA(V_NONE, void, AUTOMATIC, APPL_VAR) dst, CanChipDataPtr src, vuint8 len);
/* CODE CATEGORY 1 END */
# endif
# if defined ( C_ENABLE_DRIVER_STATUS )
/* CODE CATEGORY 4 START */
V_DEF_FUNC_API(V_NONE, vuint8, CODE) CanGetDriverStatus(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif

#if defined(MISRA_CHECK)
#  pragma PRQA_MACRO_MESSAGES_OFF "CanLL_DI", 1006                         /* MD_Can_1006_LL */
#  pragma PRQA_MACRO_MESSAGES_OFF "CanLL_EI", 1006                         /* MD_Can_1006_LL */
#  pragma PRQA_MACRO_MESSAGES_OFF "CanLL_SYNCP", 1006                      /* MD_Can_1006_LL */
#endif

# if defined(C_ENABLE_NESTED_INTERRUPTS) || defined(C_DISABLE_NESTED_INTERRUPTS)
#  if defined(C_ENABLE_NESTED_INTERRUPTS) && defined(C_DISABLE_NESTED_INTERRUPTS)
#   error "Configuration of nested interrupts is ambiguous!"
#  endif
#   if defined(C_ENABLE_NESTED_INTERRUPTS)
#    if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2)
#     error "Nesting of category 2 CAN interrupts must not be enabled by the driver!"
#    endif
#    if defined(C_ENABLE_ISRVOID)
#     error "Nesting of void-void CAN interrupts must not be enabled by the driver!"
#    endif
#   endif
# else
#  if (defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2)) || defined(C_ENABLE_ISRVOID)
#    define C_DISABLE_NESTED_INTERRUPTS
#  else
#   if defined(C_COMP_GHS_RH850_RSCAN)      
#    define C_ENABLE_NESTED_INTERRUPTS
#   else
#    define C_DISABLE_NESTED_INTERRUPTS
#   endif
#  endif
# endif /* C_ENABLE_NESTED_INTERRUPTS || C_DISABLE_NESTED_INTERRUPTS */

# if !defined(C_ENABLE_NESTED_INTERRUPTS)   || \
      defined(C_COMP_GHS_RH850_RSCAN)       
#  define CanLL_DI()
#  define CanLL_EI()
# else
#  define CanLL_DI()         __asm(" di")
#  define CanLL_EI()         __asm(" ei")
# endif

#if defined(V_CPU_RH850)
# if defined(C_COMP_GHS_RH850_RSCAN) 
#  define CanLL_SYNCP()      __asm(" syncp")
# endif
#endif

#if defined(C_ENABLE_ISRVOID)
# define C_ISR_KEYWORD       V_NONE
#else
# if defined(C_COMP_GHS_RH850_RSCAN)        
#  define C_ISR_KEYWORD      V_NONE
# endif
#endif /* C_ENABLE_ISRVOID */

/* Possibility to disable the prototypes of interrupt service routines in the driver configuration header file. */
#if !(defined( C_ENABLE_ISR_PROTOTYPE) || defined( C_DISABLE_ISR_PROTOTYPE ))
# define C_ENABLE_ISR_PROTOTYPE
#endif

#if defined (C_ENABLE_ISR_PROTOTYPE)
# if defined(C_ENABLE_OSEK_OS)&&\
     defined(C_ENABLE_OSEK_OS_INTCAT2)
/* ISR prototypes must be provided by OS header file */
# else

#  if ((defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING )) || \
       (defined( C_ENABLE_RX_FULLCAN_OBJECTS )  && !defined( C_ENABLE_RX_FULLCAN_POLLING  )) || \
       !defined( C_ENABLE_TX_POLLING )         || \
        defined( C_ENABLE_INDIVIDUAL_POLLING ) || \
       !defined( C_ENABLE_ERROR_POLLING )      || \
       !defined( C_ENABLE_LL_WAKEUP_POLLING ))        /* ISR necessary; no pure polling configuration */

#   if defined( kCanPhysToLogChannelIndex_0 )

/* ! Tx Polling */
#    if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_0(void);
#    endif /* C_ENABLE_TX_POLLING */

#    if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* ! Wakeup Polling */
#     if defined(C_ENABLE_WAKEUP_POLLING)
#     else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_0(void);
#     endif /* C_ENABLE_WAKEUP_POLLING */
#    endif

/* ! Error Polling */
#    if defined(C_ENABLE_ERROR_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_0(void);
#    endif /* C_ENABLE_ERROR_POLLING */

#   endif  /* kCanPhysToLogChannelIndex_0 */
#   if defined( kCanPhysToLogChannelIndex_1 )

/* ! Tx Polling */
#    if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_1(void);
#    endif /* C_ENABLE_TX_POLLING */

#    if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* ! Wakeup Polling */
#     if defined(C_ENABLE_WAKEUP_POLLING)
#     else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_1(void);
#     endif /* C_ENABLE_WAKEUP_POLLING */
#    endif

/* ! Error Polling */
#    if defined(C_ENABLE_ERROR_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_1(void);
#    endif /* C_ENABLE_ERROR_POLLING */

#   endif  /* kCanPhysToLogChannelIndex_1 */
#   if defined( kCanPhysToLogChannelIndex_2 )

/* ! Tx Polling */
#    if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_2(void);
#    endif /* C_ENABLE_TX_POLLING */

#    if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* ! Wakeup Polling */
#     if defined(C_ENABLE_WAKEUP_POLLING)
#     else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_2(void);
#     endif /* C_ENABLE_WAKEUP_POLLING */
#    endif

/* ! Error Polling */
#    if defined(C_ENABLE_ERROR_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_2(void);
#    endif /* C_ENABLE_ERROR_POLLING */

#   endif  /* kCanPhysToLogChannelIndex_2 */
#   if defined( kCanPhysToLogChannelIndex_3 )

/* ! Tx Polling */
#    if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_3(void);
#    endif /* C_ENABLE_TX_POLLING */

#    if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* ! Wakeup Polling */
#     if defined(C_ENABLE_WAKEUP_POLLING)
#     else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_3(void);
#     endif /* C_ENABLE_WAKEUP_POLLING */
#    endif

/* ! Error Polling */
#    if defined(C_ENABLE_ERROR_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_3(void);
#    endif /* C_ENABLE_ERROR_POLLING */

#   endif  /* kCanPhysToLogChannelIndex_3 */
#   if defined( kCanPhysToLogChannelIndex_4 )

/* ! Tx Polling */
#    if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_4(void);
#    endif /* C_ENABLE_TX_POLLING */

#    if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* ! Wakeup Polling */
#     if defined(C_ENABLE_WAKEUP_POLLING)
#     else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_4(void);
#     endif /* C_ENABLE_WAKEUP_POLLING */
#    endif

/* ! Error Polling */
#    if defined(C_ENABLE_ERROR_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_4(void);
#    endif /* C_ENABLE_ERROR_POLLING */

#   endif  /* kCanPhysToLogChannelIndex_4 */
#   if defined( kCanPhysToLogChannelIndex_5 )

/* ! Tx Polling */
#    if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_5(void);
#    endif /* C_ENABLE_TX_POLLING */

#    if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* ! Wakeup Polling */
#     if defined(C_ENABLE_WAKEUP_POLLING)
#     else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_5(void);
#     endif /* C_ENABLE_WAKEUP_POLLING */
#    endif

/* ! Error Polling */
#    if defined(C_ENABLE_ERROR_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_5(void);
#    endif /* C_ENABLE_ERROR_POLLING */

#   endif  /* kCanPhysToLogChannelIndex_5 */
#   if defined( kCanPhysToLogChannelIndex_6 )

/* ! Tx Polling */
#    if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_6(void);
#    endif /* C_ENABLE_TX_POLLING */

#    if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* ! Wakeup Polling */
#     if defined(C_ENABLE_WAKEUP_POLLING)
#     else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_6(void);
#     endif /* C_ENABLE_WAKEUP_POLLING */
#    endif

/* ! Error Polling */
#    if defined(C_ENABLE_ERROR_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_6(void);
#    endif /* C_ENABLE_ERROR_POLLING */

#   endif  /* kCanPhysToLogChannelIndex_6 */
#   if defined( kCanPhysToLogChannelIndex_7 )

/* ! Tx Polling */
#    if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_7(void);
#    endif /* C_ENABLE_TX_POLLING */

#    if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* ! Wakeup Polling */
#     if defined(C_ENABLE_WAKEUP_POLLING)
#     else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_7(void);
#     endif /* C_ENABLE_WAKEUP_POLLING */
#    endif

/* ! Error Polling */
#    if defined(C_ENABLE_ERROR_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_7(void);
#    endif /* C_ENABLE_ERROR_POLLING */

#   endif  /* kCanPhysToLogChannelIndex_7 */

#   if defined(C_ENABLE_RX_BASICCAN_OBJECTS) 
/* ! Error Polling */
#    if defined(C_ENABLE_ERROR_POLLING)
#    else
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrGlobalStatus(void);
#    endif /* C_ENABLE_ERROR_POLLING */
#   endif  /* C_ENABLE_RX_BASICCAN_OBJECTS */

#   if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/* ! Rx BasicCAN Polling */
#    if defined(C_ENABLE_RX_BASICCAN_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
#    else
#      if defined(kCanFifoToLogChannelIndex_0) || defined(kCanFifoToLogChannelIndex_1) || \
          defined(kCanFifoToLogChannelIndex_2) || defined(kCanFifoToLogChannelIndex_3) || \
          defined(kCanFifoToLogChannelIndex_4) || defined(kCanFifoToLogChannelIndex_5) || \
          defined(kCanFifoToLogChannelIndex_6) || defined(kCanFifoToLogChannelIndex_7)
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrRxFifo(void);
#      endif
#    endif /* C_ENABLE_RX_BASICCAN_POLLING */ 
#   endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#  endif /* no pure polling configuration */
# endif /* C_ENABLE_OSEK_OS && C_ENABLE_OSEK_OS_INTCAT2 */
#endif /* C_ENABLE_ISR_PROTOTYPE */

/* PRQA  L:QAC_Can_0857 */
/* PRQA  L:QAC_Can_0828 */
/* PRQA  L:QAC_Can_3453 */
/* PRQA  L:QAC_Can_0850 */

#endif /* CAN_DEF_H */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

