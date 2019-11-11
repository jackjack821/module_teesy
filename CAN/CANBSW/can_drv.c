/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

/* STARTSINGLE_OF_MULTIPLE */

/* ***************************************************************************
|
| Project Name: DrvCan_Rh850RscanHll
|    File Name: can_drv.c
|
|  Description: Implementation of the CAN driver
|
|               Target systems: RH850 derivatives with RSCAN
|
|               Compiler:       GreenHills
|                               WindRiver Diab
|                               Renesas
|                               IAR
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
|                               - ESCAN00071662: Support usage of MICROSAR OS 'Peripheral Interrupt API' for RH850 platform
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
| --------     ---------------------     -------------------------------------
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
| ---------  ---  ------  ----------------------------------------------------
| 19-Jan-01  0.02  Ht     - derived form C16x V3.3
| 18-Apr-01  1.00  Pl     - derived for ARM7 TDMI
| 02-May-01  1.01  Ht     - adaption to LI1.2
|                         - change from code doupling to indexed
| 31-Oct-01  1.02  Ht     - support hash search
|                  Ht     - optimisation for message access (hardware index)
|                  Vg     - adaption for PowerPC
| 07-Nov-01  1.03  Ht     - remove some comments
|                         - support of basicCAN polling extended
| 12-Dez-01  1.04  Ht     - avoid compiler warnings for KEIL C166
|                         - ESCAN00001881: warning in CanInitPowerOn
|                         - ESCAN00001913: call of CanLL_TxEnd()
|                  Fz     - ESCAN00001914: CanInterruptRestore changed for M32C
| 02-Jan-02  1.05  Ht     - ESCAN00002009: support of polling mode improved
|                         - ESCAN00002010: Prototype of CanHL_TxConfirmation() 
|                                          not available in every case.
| 12-Feb-02  1.06 Pl      - ESCAN00002279: - now it is possible to use only the error-task without the tx-task
|                                          - support of the makro  REENTRANT
|                                          - support of the makro C_HL_ENABLE_RX_INFO_STRUCT_PTR
|                                          - For better performance for the T89C51C there is a switch-case
|                                            instruction for direct call of the PreTransmitfunction
|                                          - add C_ENABLE_RX_BASICCAN_POLLING in CanInitPowerOn
| 18-Mai-02  1.07 Ht      - support Hash search with FullCAN controller
|                         - ESCAN00002707: Reception could went wrong if IL and Hash Search
|                         - ESCAN00002893: adaption to LI 1.3
| 29-Mai-02  1.08 Ht      - ESCAN00003028: Transmission could fail in Polling mode
|                         - ESCAN00003082: call Can_LL_TxEnd() in CanMsgTransmit()
|                         - ESCAN00003083: Hash search with extended ID
|                         - ESCAN00003084: Support C_COMP_METROWERKS_PPC
|                         - ESCAN00002164: Temporary vaiable "i" not defined in function CanBasicCanMsgReceived
|                         - ESCAN00003085: support C_HL_ENABLE_IDTYPE_IN_ID
| 25-Jun     1.08.01 Vg   - Declared localInterruptOldFlag in CanRxTask()
|                         - Corrected call to CanWakeUp for multichannel
| 11-Jul-02  1.08.02 Ht   - ESCAN00003203: Hash Search routine does not work will with extended IDs
|                         - ESCAN00003205: Support of ranges could went wrong on some platforms
| 08-Aug-02  1.08.03 Ht   - ESCAN00003447: Transmission without databuffer and pretransmit-function 
| 08-Aug-02  1.08.04 An   - Added support to Green Hills
| 09-Sep-02  1.09    Ht   - ESCAN00003837: code optimication with KernelBuilder
|                         - ESCAN00004479: change the place oft the functioncall of CanLL_TxCopyMsgTransmit
|                                          in CanMsgTransmit 
| 2002-12-06 1.10    Ht   -                Support consistancy for polling tasks
|                         - ESCAN00004567: Definiton of V_NULL pointer
|                         -                remove include of string.h
|                         -                support Dummy functions for indirect function call 
|                         -                optimization for one single Tx mail box
| 2003-02-04 1.11    Ht   -                optimization for polling mode
| 2003-03-19 1.12    Ht   - ESCAN00005152: optimization of CanInit() in case of Direct Tx Objects
|                         - ESCAN00005143: CompilerWarning about function prototype 
|                                          CanHL_ReceivedRxHandle() and CanHL_IndRxHandle
|                         - ESCAN00005130: Wrong result of Heash Search on second or higher channel               
| 2003-05-12 1.13    Ht   - ESCAN00005624: support CantxMsgDestroyed for multichannel system
|                         - ESCAN00005209: Support confirmation and indication flags for EasyCAN4
|                         - ESCAN00004721: Change data type of Handle in CanRxInfoStruct
| 2003-06-18 1.20   Ht    - ESCAN00005908: support features of RI1.4
|                         - Support FJ16LX-Workaround for multichannel system
|                         - ESCAN00005671: Dynamic Transmit Objects: ID in extended ID frames is wrong
|                         - ESCAN00005863: Notification about cancelation failes in case of CanTxMsgDestroyed
| 2003-06-30 1.21   Ht   - ESCAN00006117: Common Confirmation Function: Write access to wrong memory location
|                        - ESCAN00006008: CanCanInterruptDisable in case of polling
|                        - ESCAN00006118: Optimization for Mixed ID and ID type in Own Register or ID type in ID Register
|                        - ESCAN00006100: transmission with wrong ID in mixed ID mode
|                        - ESCAN00006063: Undesirable hardware dependency for 
|                                         CAN_HL (CanLL_RxBasicTxIdReceived)
| 2003-09-10 1.22   Ht   - ESCAN00006853: Support V_MEMROM0
|                        - ESCAN00006854: suppress some Compiler warnings
|                        - ESCAN00006856: support CanTask if only Wakeup in polling mode
|                        - ESCAN00006857: variable newDLC not defined in case of Variable DataLen
| 2003-10-14 1.23   Ht   - ESCAN00006858: support BrsTime for internal runtime measurement
|                        - ESCAN00006860: support Conditional Msg Receive
|                        - ESCAN00006865: support "Cancel in HW" with CanTask
|                        - ESCAN00006866: support Direct Tx Objects
|                        - ESCAN00007109: support new memory qualifier for const data and pointer to const
| 2004-01-05 1.24   Ml   - ESCAN00007206: resolved preprocessor error for Hitachi compiler
|                   Ml   - ESCAN00007254: several changes
| 2004-02-06 1.25   Ml   - ESCAN00007281: solved compilerwarning
|                   Ml   - removed compiler warnings
| 2004-02-21 1.26   Ml   - ESCAN00007670: CAN RAM check
|                   Ml   - ESCAN00007671: fixed dyn Tx object issue
|                   Ml   - ESCAN00007764: added possibility to adjust Rx handle in LL drv
|                   Ml   - ESCAN00007681: solved compilerwarning in CanHL_IndRxHandle
|                   Ml   - ESCAN00007272: solved queue transmission out of LowLevel object
|                   Ml   - ESCAN00008064: no changes
| 2004-04-16 1.27   Ml   - ESCAN00008204: no changes
|                   Ml   - ESCAN00008160: no changes
|                   Ml   - ESCAN00008266: changed name of parameter of function CanTxGetActHandle
|                   Fz   - ESCAN00008272: Compiler error due to missing array canPollingTaskActive
| 2004-05-10 1.28   Fz   - ESCAN00008328: Compiler error if cancel in hardware is active
|                        - ESCAN00008363: Hole closed when TX in interrupt and cancel in HW is used
|                        - ESCAN00008365: Switch C_ENABLE_APPLCANPREWAKEUP_FCT added
|                        - ESCAN00008391: Wrong parameter macro used in call of 
|                                         CanLL_WakeUpHandling
| 2004-05-24 1.29   Ht   - ESCAN00008441: Interrupt not restored in case of internal error if TX Polling is used
| 2004-09-21 1.30   Ht   - ESCAN00008914: CAN channel may stop transmission for a certain time
|                        - ESCAN00008824: check of reference implementation version added
|                        - ESCAN00008825: No call of ApplCanMsgCancelNotification during CanInit()
|                        - ESCAN00008826: Support asssertions for "Conditional Message Received"  
|                   Ml   - ESCAN00008752: Added function qualifier macros
|                   Ht   - ESCAN00008823: compiler error due to array size 0
|                        - ESCAN00008977: label without instructions
|                        - ESCAN00009485: Message via Normal Tx Object will not be sent  
|                        - ESCAN00009497: support of CommonCAN and RX queue added
|                        - ESCAN00009521: Inconsitancy in total polling mode
| 2004-09-28 1.31   Ht   - ESCAN00009703: unresolved functions CAN_POLLING_IRQ_DISABLE/RESTORE()
| 2004-11-25 1.32   Ht   - move fix for ESCAN00007671 to CAN-LL of DrvCan_MpcToucanHll
|                        - ESCAN00010350: Dynamic Tx messages are send always with Std. ID
|                        - ESCAN00010388: ApplCanMsgConfirmed will only be called if realy transmitted
|                    Ml  - ESCAN00009931: The HardwareLoopCheck should have a channelparameter in multichannel systems.
|                    Ml  - ESCAN00010093: lint warning: function type inconsistent "CanCheckMemory"
|                    Ht  - ESCAN00010811: remove Misra and compiler warnings
|                        - ESCAN00010812: support Multi ECU
|                        - ESCAN00010526: CAN interrupts will be disabled accidently
|                        - ESCAN00010584: ECU may crash or behave strange with Rx queue active
| 2005-01-20 1.33    Ht  - ESCAN00010877: ApplCanMsgTransmitConf() is called erronemous
| 2005-03-03 1.34    Ht  - ESCAN00011139: Improvement/Correction of C_ENABLE_MULTI_ECU_CONFIG
|                        - ESCAN00011511: avoid PC-Lint warnings
|                        - ESCAN00011512: copy DLC in case of variable Rx Datalen
|                        - ESCAN00010847: warning due to missing brakets in can_par.c at CanChannelObject
| 2005-05-23 1.35   Ht   - ESCAN00012445: compiler error "V_MEMROMO undefined"in case of multi ECU
|                        - ESCAN00012350: Compiler Error "Illegal token channel"
| 2005-07-06 1.36   Ht   - ESCAN00012153: Compile Error: missing declaration of variable i
|                        - ESCAN00012460: Confirmation of LowLevel message will run into assertion (C_ENABLE_MULTI_ECU_PHYS enabled)
|                        - support Testpoints for CanTestKit
| 2005-07-14 1.37   Ht   - ESCAN00012892: compile error due to missing logTxObjHandle
|                        - ESCAN00012998: Compile Error: missing declaration of txHandle in CanInit()
|                        - support Testpoints for CanTestKit for FullCAN controller
| 2005-09-21 1.38   Ht   - ESCAN00013597: Linker error: Undefined symbol 'CanHL_IndRxHandle'
| 2005-11-10 1.39.00 Ht  - ESCAN00014331: Compile error due to missing 'else' in function CanTransmit
|
| 2005-04-26 2.00.00  Ht - ESCAN00016698: support RI1.5
|                        - ESCAN00014770: Cosmic compiler reports truncating assignement
|                        - ESCAN00016191: Compiler warning about unused variable in CanTxTask
|
| 2007-01-23 2.01.00  Ht - ESCAN00017279: Usage of SingleGlobalInterruptDisable lead to assertion in OSEK
|                        - ESCAN00017148: Compile error in higher layer due to missing declaration of CanTxMsgHandleToChannel
| 2007-03-14 2.02.00  Ht - ESCAN00019825: error directives added and misra changes
|                        - ESCAN00019827: adaption to never version of VStdLib.
|                        - ESCAN00019619: V_CALLBACK_1 and V_CALLBACK_2 not defined
|                        - ESCAN00019953: Handling of FullCAN reception in interrupt instead of polling or vice versa.
|                        - ESCAN00019958: CanDynTxObjSetId() or CanDynTxObjSetExtId() will run into assertion
| 2007-03-26 2.03.00  Ht - ESCAN00019988: Compile warnings in can_drv.c
|                        - ESCAN00018831: polling mode: function prototype without function implemenation (CanRxFullCANTask + CanRxBasicCANTask)
| 2007-04-20 2.04.00  dH - ESCAN00020299: user assertion fired irregularly due to unknown parameter (in case of CommonCAN)
| 2007-05-02 2.05.00  Ht - ESCAN00021069: Handling of canStatus improved, usage of preprocessor defines unified
|                        - ESCAN00021070: support relocation of HW objects in case of Multiple configuration
|                        - ESCAN00021166: Compiler Warnings: canHwChannel & canReturnCode not used in CanGetStatus
|                        - ESCAN00021223: CanCanInterruptDisabled called during Sleepmode in CanWakeupTask
|                        - ESCAN00022048: Parameter of ApplCancorruptMailbox is hardware channel instead of logical channel - Error directive added
| 2007-11-12 2.06.00  Ht - ESCAN00023188: support CAN Controller specific polling sequence for BasicCAN objects
|                        - ESCAN00023208: Compile issue about undefined variable kCanTxQueuePadBits in the CAN driver in Bit based Tx queue
| 2008-10-20 2.07.00  Ht - ESCAN00023010: support disabled mailboxes in case of extended RAM check
|                        - ESCAN00025706: provide C_SUPPORTS_MULTI_ECU_PHYS
|                        - ESCAN00026120: compiler warnings found on DrvCan_V85xAfcanHll RI 1.5
|                        - ESCAN00026322: ApplCanMsgNotMatched not called in special configuration
|                        - ESCAN00026413: Add possibility to reject remote frames received by FullCAN message objects
|                        - ESCAN00028758: CAN HL must support QNX
|                        - ESCAN00029788: CommonCAN for Driver which support only one Tx object improved (CanInit()).
|                        - ESCAN00029889: Compiler warning about uninitialized variable canHwChannel in CanCanInterruptDisable/Restore()
|                        - ESCAN00029891: Compiler warning: variable "rxHandle" was set but never used
|                        - ESCAN00029929: Support Extended ID Masking for Tx Fullcan messages 
|                        - ESCAN00030371: Improvements (assertions, misra)
|                        - ESCAN00027931: Wrong check of "queueBitPos" size
| 2009-04-08 2.08.00  Ht - ESCAN00034492: no automatic remove of CanCanInterruptDisable/Restore
|                        - ESCAN00031816: CANRANGExIDTYPE can be removed and direct expression used
|                        - ESCAN00032027: CanMsgTransmit shall support tCanMsgTransmitStruct pointer accesses to far RAM
|                        - ESCAN00034488: Postfix for unsigned const in perprocessor directives are not supported by all Compiler (ARM-Compiler 1.2)
| 2009-06-04 2.08.01  Ht - ESCAN00035426: Compiler warning about truncation in CanGetStatus removed
| 2009-10-21 2.09.00  Ht - ESCAN00036258: Compiler warning about "CanHL_ReceivedRxHandle" was declared but never referenced
|                        - ESCAN00038642: Support reentrant functions for compiler with own keyword
|                        - ESCAN00038645: support new switch C_ENABLE_UPDATE_BASE_ADDRESS
| 2010-02-01 2.10.00  Ht - ESCAN00036260: Support configuartion without static Tx messages and only one channel (remove compiler warning)
|                        - ESCAN00040478: Handle update of virtual CanBaseAdress in accordance to QNX documentation
|                        - ESCAN00039235: Compiler Warning: Narrowing or Signed-to-Unsigned type conversion
| 2010-07-22 2.11.00  Ht - ESCAN00044221: support Retransmit functionality for FBL
|                        - ESCAN00044222: internal changes: improve readability and
|                                         change CAN_CAN_INTERRUPT_... macros to avoid preprocessor errors for some compiler
|                        - ESCAN00044174: TxBitQueue only - compiler warning occurs about: condition is always true
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
|************************************************************************* */

#define C_DRV_INTERNAL

/* PRQA S 3453 EOF */ /* MD_Can_3453 */
/* PRQA S 3109 EOF */ /* MD_Can_3109 */
/* PRQA S 2001 EOF */ /* MD_Can_2001 */
/* PRQA S 2006 EOF */ /* MD_Can_2006 */
/* PRQA S 0750 EOF */ /* MD_Can_0750 */
/* PRQA S 0850 EOF */ /* MD_Can_0850 */
/* PRQA S 0715 EOF */ /* MD_Can_0715 */
/* PRQA S 0857 EOF */ /* MD_Can_0857 */ 
/* PRQA S 0828 EOF */ /* MD_Can_0828 */
/* PRQA S 3458 EOF */ /* MD_Can_3458 */
/* PRQA S 3412 EOF */ /* MD_Can_3412 */
/* PRQA S 0488 EOF */ /* MD_Can_17.4 */
/* PRQA S 0489 EOF */ /* MD_Can_17.4 */
/* lint -function(exit, ApplCanFatalError) */

/* *********************************************************************** */
/* Include files                                                           */
/* *********************************************************************** */

#include "can_inc.h"

/* *********************************************************************** */
/* Version check                                                           */
/* *********************************************************************** */
#if (DRVCAN_SH2RSCANHLL_VERSION         != 0x0315u)
# error "Source and header files are inconsistent!"
#endif
#if (DRVCAN_SH2RSCANHLL_RELEASE_VERSION != 0x00u)
# error "Source and header files are inconsistent!"
#endif

#if( C_VERSION_REF_IMPLEMENTATION != 0x150)
# error "Generated Data and CAN driver source file are inconsistent!"
#endif

#if( DRVCAN__COREHLL_VERSION != 0x0218)
# error "Source and Header file are inconsistent!"
#endif
#if( DRVCAN__COREHLL_RELEASE_VERSION != 0x00)
# error "Source and Header file are inconsistent!"
#endif

#if ( ( DRVCAN__HLLTXQUEUEBIT_VERSION != 0x0106) )
# error "TxQueue Source and Header Version inconsistent!"
#endif
#if ( ( DRVCAN__HLLTXQUEUEBIT_RELEASE_VERSION != 0x05) )
# error "TxQueue Source and Header Version inconsistent!"
#endif

#if defined( DRVCAN__HLLTXQUEUEBIT_VERSION )
# if ( ( DRVCAN__HLLTXQUEUEBIT_VERSION != 0x0106) || \
       ( DRVCAN__HLLTXQUEUEBIT_RELEASE_VERSION != 0x05)  )
#  error "TxQueue Version inconsistent!"
# endif

/* defines to satisfy MISRA checker tool */
# define DRVCAN__HLLTXQUEUEBYTE_VERSION 0x0000
# define DRVCAN__HLLTXQUEUEBYTE_RELEASE_VERSION 0x00

#else
# if defined( DRVCAN__HLLTXQUEUEBYTE_VERSION )
#  if ( ( DRVCAN__HLLTXQUEUEBYTE_VERSION != 0x0104) || \
       ( DRVCAN__HLLTXQUEUEBYTE_RELEASE_VERSION != 0x00)  )
#   error "TxQueue Version inconsistent!"
#  endif
# else
#  error "No TxQueue available"
# endif

/* defines to satisfy MISRA checker tool */
# define DRVCAN__HLLTXQUEUEBIT_VERSION 0x0000
# define DRVCAN__HLLTXQUEUEBIT_RELEASE_VERSION 0x00

#endif

/* *********************************************************************** */
/* Defines                                                                 */
/* *********************************************************************** */

/* return values */ 
#define kCanHlFinishRx                                     ((vuint8)0x00)
#define kCanHlContinueRx                                   ((vuint8)0x01)

#define  CANHL_TX_QUEUE_BIT

#if !defined(C_ENABLE_IF_RSCAN) && !defined(C_ENABLE_IF_RSCAN_FD)
# define C_ENABLE_IF_RSCAN
#endif
#if defined(V_CPU_RH850)
# if defined(C_ENABLE_IF_RSCAN) && defined(C_ENABLE_IF_RSCAN_FD)
#  error "Configuration of CAN interface is ambiguous!"
# endif
#endif

#define kCanIntMaskBusoff            0x00000800u /* BO entry */
#define kCanIntMaskCancel            0x00010000u
#if defined(C_ENABLE_IMMEDIATE_BUSOFF_RECOVERY)
# define kCanCrHaltAtBusoff          0x00200000u /* halt mode at bus-off entry (BOM=01) */
#else
# define kCanCrHaltAtBusoff          0x00400000u /* default: halt mode at bus-off end (BOM=10) */
#endif
#define kCanSrMaskBusoff             0x00000010u
#define kCanSrMaskPassive            0x00000008u
#define kCanSrMaskRec                0x00FF0000u
#define kCanSrMaskTec                0xFF000000u
#define kCanEfMaskBusoff             0x0008u     /* BO entry */
#define kCanEfMaskBusoffClear        0x7FF7u

#if defined(C_ENABLE_ALTERNATIVE_CLOCK_SOURCE)
# define kCanGlobCfg                 0x00000010u /* clock source select = 1 */
#else
# define kCanGlobCfg                 0x00000000u /* default: clock source select = 0 */
#endif
#define kCanIntMaskMessageLost       0x00000200u /* RX FIFO overrun */
#define kCanSrMaskRamIst             0x00000008u
#define kCanEfMaskParityError        0x00000008u
#define kCanParityCheckEnable        0x00000001u
#define kCanHwRamTestEnable          0x00000004u
#define kCanHwRamTestDisable         0x00000000u
#define kCanProtectionUnlockData1    0x00007575u
#define kCanProtectionUnlockData2    0x00008A8Au

#define kCanRuleWrite                0x00000100u
#define kCanRuleReceive              0x00000000u
#define kCanRuleUseBuf               0x00008000u
#define kCanRuleStdMustMatch         0xC00007FFu
#define kCanRuleExtMustMatch         0xDFFFFFFFu
#define kCanRuleHeader               0xC0000000u
#define kCanRuleHeaderClrMask        0x1FFFFFFFu
# define kCanRuleIndexMask           0x000Fu
# define kCanRulePageMask            0xFFF0u
# define kCanRulePageShiftVal        4u

#define kCanOne16                    0xFFFFu
#define kCanOne8                     0xFFu
#define kCanOne                      1u
#define kCanZero                     0u
# define kCanRxFifoMask              0x000000FFu
# define kCanDlcMask                 0xF0000000u

#define kCanModeMask                 0xFFFFFFF8u /* incl. STP */
#if defined(C_ENABLE_CONDITIONAL_START_TRANSITION)
# define kCanModeBits                0x00000087u /* includes check for COMST */
#else
# define kCanModeBits                0x00000007u /* default: no check for COMST */
#endif
#define kCanOperationMode            0x00000000u /* global and channel */
#define kCanOperationModeCheck       0x00000080u /* channel only */
#define kCanResetMode                0x00000001u /* global and channel */
#define kCanTestMode                 0x00000002u /* global only */
#define kCanHaltMode                 0x00000002u /* channel only */
#define kCanStopMode                 0x00000005u /* global and channel */

#define kCanCrTxBufReq               0x01u
#define kCanCrTxBufCancel            0x02u
#define kCanSrTxBufMaskPending       0x06u
#define kCanSrTxBufMaskComplete      0x04u
#define kCanSrTxBufMaskCancel        0x02u
#define kCanSrTxBufMaskFree          0x1Fu
#define kCanSrTxBufMaskAReq          0x10u
#define kCanSrTxBufMaskTReq          0x08u

#define kCanCrFifoEnable             0x00000001u
#define kCanCrRxFifoIntEnable        0x00000002u
#define kCanCrTxFifoIntEnable        0x00000004u
#define kCanCrRxFifoSet              0x00001000u /* interrupt every message */ 
#define kCanCrTxFifoSet              0x00011000u /* link to TB0; transmit mode; interrupt every message */
#define kCanSrFifoEmpty              0x00000001u
#define kCanSrFifoFull               0x00000002u
#define kCanSrFifoOverrun            0x00000004u
#define kCanSrRxFifoIntFlag          0x00000008u
#define kCanSrTxFifoIntFlag          0x00000010u
#define kCanSrFifoMsgCount           0x0000FF00u
#define kCanPcrFifoPC                0x000000FFu

/* Layout */
# define kCanMaxPhysChannelsCell     8u
# define kCanMaxRxFifosCell          8u
# define kCanMaxTxFifosCell          3u  /* per channel */
# define kCanMaxRxBufCell            128u
# define kCanMaxTxBufCell            16u /* per channel */
# define kCanNumberOfSharedReg8Cell  2u
# define kCanNumberOfSharedReg16Cell 4u
# define kCanMaxHwObjectsCell        288u
# define kCanMaxRuleAccessCell       16u
# define kCanMaxRamTestAccessCell    64u
# define kCanRegSize                 vuint32
# define kCanTxSize                  vuint16

/* INTC */
#if defined(V_CPU_RH850)
# define kCanIntcIPR                 ((vuint8) 0x0Fu) /* EIPn */
# define kCanIntcEIMK                ((vuint8) 0x80u)
# if defined(C_ENABLE_DIRECT_INTERRUPT_BRANCH)
#  define kCanIntcEITB               ((vuint8) 0x00u)
# else
#  define kCanIntcEITB               ((vuint8) 0x40u)
# endif
# define kCanIntcEIRF                ((vuint8) 0x10u)
# define kCanIntcEIRFNeg             ((vuint8) 0xEFu)
#endif

#if defined(C_ENABLE_CAN_HW_RAM_CHECK)
#  define CanMemCheckValuesRegSize   CanMemCheckValues32bit
#endif

#if defined(C_ENABLE_CAN_HW_RAM_CHECK)
/* 32 byte per block */
# define kCanHwRamCheckByteToBlockShiftVal  5u
# define kCanHwRamCheckByteToBlockMask      0x001Fu
/* 8 blocks per page */
# define kCanHwRamCheckBlocksPerPage        8u
# define kCanHwRamCheckBlockToPageShiftVal  3u
# define kCanHwRamCheckBlockToPageMask      0x0007u

/* get the RAM size in blocks */
# if defined(C_ENABLE_CAN_HW_RAM_CHECK_SIZE)
/* the RAM size has to be > 0, in 16bit range and a multiple of the blocksize */
#  if (C_ENABLE_CAN_HW_RAM_CHECK_SIZE == 0)                                    || \
      (C_ENABLE_CAN_HW_RAM_CHECK_SIZE > kCanOne16)                             || \
      ((C_ENABLE_CAN_HW_RAM_CHECK_SIZE & kCanHwRamCheckByteToBlockMask) != 0)
#   error "C_ENABLE_CAN_HW_RAM_CHECK_SIZE defines an invalid value for the RSCAN RAM test!"
#  endif
#  define kCanHwRamCheckSize         (C_ENABLE_CAN_HW_RAM_CHECK_SIZE >> kCanHwRamCheckByteToBlockShiftVal)
# else
#  if defined(V_CPU_RH850)
#   error "C_ENABLE_CAN_HW_RAM_CHECK_SIZE has to be defined if the RSCAN RAM test is enabled!"
#  endif
# endif

/* get the last necessary test target page and the number of blocks that have to be checked for this page */
# define kCanHwRamCheckPageMax       ((kCanHwRamCheckSize - 1) >> kCanHwRamCheckBlockToPageShiftVal)
# define kCanHwRamCheckBlockMax      (kCanHwRamCheckSize & kCanHwRamCheckBlockToPageMask)
#endif /* C_ENABLE_CAN_HW_RAM_CHECK */

#if defined(MISRA_CHECK)
/* PRQA S 0303 EOF */                                                               /* MD_Can_0303_HWaccess */
#  pragma PRQA_MACRO_MESSAGES_OFF "CanLL_CanInterruptDisable", 1006,3197,3198,3199  /* MD_Can_1006_LL,MD_Can_3199_dummy,MD_Can_3199_dummy,MD_Can_3199_dummy */
#  pragma PRQA_MACRO_MESSAGES_OFF "CanNestedGlobalInterruptDisable", 1006           /* MD_Can_1006_LL */
#  pragma PRQA_MACRO_MESSAGES_OFF "CanNestedGlobalInterruptRestore", 1006           /* MD_Can_1006_LL */
#endif

/* *********************************************************************** */
/* Basic configuration check                                               */
/* *********************************************************************** */
#if ((kCanMaxPhysChannels > kCanMaxPhysChannelsCell) || \
     (kCanMaxRxFifos > kCanMaxRxFifosCell)           || \
     (kCanMaxTxFifos > kCanMaxTxFifosCell)           || \
     (kCanMaxRxBuf > kCanMaxRxBufCell)               || \
     (kCanMaxTxBuf > kCanMaxTxBufCell))
# error "Configuration exceeds RSCAN limitations, check the derivative data!"
#endif

#if ((kCanBaseAdr == 0)                              || \
     (kCanMaxPhysChannels == 0)                      || \
     (kCanRxBufOffset >= kCanRxFifoOffset)           || \
     (kCanRxFifoOffset >= kCanTxBufOffset_0)         || \
     (kCanTxBufOffset_0 >= kCanMaxHwObjects)         || \
     (kCanNumberOfSharedReg16 == 0)                  || \
     (kCanNumberOfSharedReg16 > ((kCanMaxPhysChannels+1)>>1)))
# error "General configuration error!"
#endif

#if defined (C_ENABLE_LL_CAN_INTCTRL)
# if ((kCanIntcRxFifoBaseAdr == 0)                   || \
      (kCanIntcGErrorBaseAdr == 0))
#  error "Interrupt control register address configuration error!"
# endif
#endif

#if defined (C_ENABLE_RX_FULLCAN_OBJECTS)
# if !defined (C_ENABLE_RX_FULLCAN_POLLING)
#  error "Rx FullCANs cannot be processed in interrupt context!"
# endif
#endif

#if !defined (C_ENABLE_DRIVER_STATUS)
# error "C_ENABLE_DRIVER_STATUS has to be defined!"
#endif

#if defined(V_CPU_RH850)
# if defined(C_ENABLE_INTC_ACCESS_BY_APPL)
#  if !defined(C_ENABLE_LL_CAN_INTCTRL) && !defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL)
#   error "C_ENABLE_INTC_ACCESS_BY_* must not be defined if no CAN interrupts are used or the driver has no CAN interrupt control!"
#  endif
# endif
#  define CanAreaGlob    0u
#  define CanAreaCh(ch)  0u
#  define CanAreaWup(ch) 0u
#endif

/* *********************************************************************** */
/* macros                                                                  */
/* *********************************************************************** */

#if !(defined( C_HL_DISABLE_RX_INFO_STRUCT_PTR ) || defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR ))
# define C_HL_ENABLE_RX_INFO_STRUCT_PTR
#endif

#if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
# define CAN_HL_P_RX_INFO_STRUCT(channel)                  (pCanRxInfoStruct)  
# define CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)           (pCanRxInfoStruct->Handle)  
#else
# define CAN_HL_P_RX_INFO_STRUCT(channel)                  (&canRxInfoStruct[channel])
# define CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)           (canRxInfoStruct[channel].Handle)  
#endif 

/* disabled - lint -emacro( (572, 778), C_RANGE_MATCH) */

#if defined( C_SINGLE_RECEIVE_CHANNEL )
# if (kCanNumberOfUsedCanRxIdTables == 1)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  (  ((idRaw0) & (tCanRxId0)~MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  (  ((idRaw0) & (tCanRxId0)~MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 2)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDSTD1(mask)) == MK_RX_RANGE_CODE_IDSTD1(code) ) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDEXT1(mask)) == MK_RX_RANGE_CODE_IDEXT1(code) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 3)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDSTD1(mask)) == MK_RX_RANGE_CODE_IDSTD1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDSTD2(mask)) == MK_RX_RANGE_CODE_IDSTD2(code) ) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDEXT1(mask)) == MK_RX_RANGE_CODE_IDEXT1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDEXT2(mask)) == MK_RX_RANGE_CODE_IDEXT2(code) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 4)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDSTD1(mask)) == MK_RX_RANGE_CODE_IDSTD1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDSTD2(mask)) == MK_RX_RANGE_CODE_IDSTD2(code) ) && \
                    ( ((idRaw3) & (tCanRxId3)~ MK_RX_RANGE_MASK_IDSTD3(mask)) == MK_RX_RANGE_CODE_IDSTD3(code) ) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDEXT1(mask)) == MK_RX_RANGE_CODE_IDEXT1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDEXT2(mask)) == MK_RX_RANGE_CODE_IDEXT2(code) ) && \
                    ( ((idRaw3) & (tCanRxId3)~ MK_RX_RANGE_MASK_IDEXT3(mask)) == MK_RX_RANGE_CODE_IDEXT3(code) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 5)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDSTD1(mask)) == MK_RX_RANGE_CODE_IDSTD1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDSTD2(mask)) == MK_RX_RANGE_CODE_IDSTD2(code) ) && \
                    ( ((idRaw3) & (tCanRxId3)~ MK_RX_RANGE_MASK_IDSTD3(mask)) == MK_RX_RANGE_CODE_IDSTD3(code) ) && \
                    ( ((idRaw4) & (tCanRxId4)~ MK_RX_RANGE_MASK_IDSTD4(mask)) == MK_RX_RANGE_CODE_IDSTD4(code) ) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDEXT1(mask)) == MK_RX_RANGE_CODE_IDEXT1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDEXT2(mask)) == MK_RX_RANGE_CODE_IDEXT2(code) ) && \
                    ( ((idRaw3) & (tCanRxId3)~ MK_RX_RANGE_MASK_IDEXT3(mask)) == MK_RX_RANGE_CODE_IDEXT3(code) ) && \
                    ( ((idRaw4) & (tCanRxId4)~ MK_RX_RANGE_MASK_IDEXT4(mask)) == MK_RX_RANGE_CODE_IDEXT4(code) ) )
# endif
#else     /* C_MULTIPLE_RECEIVE_CHANNEL */

# if (kCanNumberOfUsedCanRxIdTables == 1)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                (  ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 2)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                ( ( ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) ) &&\
                                  ( ((idRaw1) & (tCanRxId1)~((mask).Id1)) == ((code).Id1) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 3)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                ( ( ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) ) &&\
                                  ( ((idRaw1) & (tCanRxId1)~((mask).Id1)) == ((code).Id1) ) &&\
                                  ( ((idRaw2) & (tCanRxId2)~((mask).Id2)) == ((code).Id2) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 4)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                ( ( ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) ) &&\
                                  ( ((idRaw1) & (tCanRxId1)~((mask).Id1)) == ((code).Id1) ) &&\
                                  ( ((idRaw2) & (tCanRxId2)~((mask).Id2)) == ((code).Id2) ) &&\
                                  ( ((idRaw3) & (tCanRxId3)~((mask).Id3)) == ((code).Id3) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 5)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                ( ( ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) ) &&\
                                  ( ((idRaw1) & (tCanRxId1)~((mask).Id1)) == ((code).Id1) ) &&\
                                  ( ((idRaw2) & (tCanRxId2)~((mask).Id2)) == ((code).Id2) ) &&\
                                  ( ((idRaw3) & (tCanRxId3)~((mask).Id3)) == ((code).Id3) ) &&\
                                  ( ((idRaw4) & (tCanRxId4)~((mask).Id4)) == ((code).Id4) ) )
# endif
#endif

#if (kCanNumberOfUsedCanRxIdTables == 1)
# define CAN_RX_IDRAW_PARA                                 idRaw0
#endif
#if (kCanNumberOfUsedCanRxIdTables == 2)
# define CAN_RX_IDRAW_PARA                                 idRaw0, idRaw1
#endif
#if (kCanNumberOfUsedCanRxIdTables == 3)
# define CAN_RX_IDRAW_PARA                                 idRaw0, idRaw1, idRaw2
#endif
#if (kCanNumberOfUsedCanRxIdTables == 4)
# define CAN_RX_IDRAW_PARA                                 idRaw0, idRaw1, idRaw2, idRaw3
#endif
#if (kCanNumberOfUsedCanRxIdTables == 5)
# define CAN_RX_IDRAW_PARA                                 idRaw0, idRaw1, idRaw2, idRaw3, idRaw4
#endif

#if defined( C_SINGLE_RECEIVE_CHANNEL )
# define channel                                           ((CanChannelHandle)0)
# define canHwChannel                                      ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STARTINDEX(channel)             ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STOPINDEX(channel)              ((CanChannelHandle)0)
# define CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel)        (kCanMsgTransmitObj)
# define CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel)           (kCanHwTxNormalIndex)

/* Offset which has to be added to change the hardware Tx handle into a logical handle, which is unique over all channels */
/*        Tx-Hardware-Handle - CAN_HL_HW_TX_STARTINDEX(canHwChannel) + CAN_HL_LOG_HW_TX_STARTINDEX(canHwChannel) */
# define CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)          ((vsintx)0-(vsintx)kCanHwTxStartIndex)
/* ESCAN00062667 */

# define CAN_HL_TX_STARTINDEX(channel)                     ((CanTransmitHandle)0)
# define CAN_HL_TX_STAT_STARTINDEX(channel)                ((CanTransmitHandle)0)
# define CAN_HL_TX_DYN_ROM_STARTINDEX(channel)             (kCanNumberOfTxStatObjects)
# define CAN_HL_TX_DYN_RAM_STARTINDEX(channel)             ((CanTransmitHandle)0)
/* # define CAN_HL_RX_STARTINDEX(channel)                     ((CanReceiveHandle)0) */
/* index to access the ID tables - Basic index only for linear search 
   for hash search this is the start index of the ??? */
# define CAN_HL_RX_BASIC_STARTINDEX(channel)               ((CanReceiveHandle)0)
# if defined( C_SEARCH_HASH ) || \
     defined( C_SEARCH_INDEX )
#  define CAN_HL_RX_FULL_STARTINDEX(canHwChannel)          ((CanReceiveHandle)0)
# else
#  define CAN_HL_RX_FULL_STARTINDEX(canHwChannel)          (kCanNumberOfRxBasicCANObjects)
# endif
# define CAN_HL_INIT_OBJ_STARTINDEX(channel)               ((vuint8)0)
# define CAN_HL_LOG_HW_TX_STARTINDEX(canHwChannel)         ((CanObjectHandle)0)
# define CAN_HL_HW_TX_STARTINDEX(canHwChannel)             ((CanObjectHandle)kCanHwTxStartIndex)
/* ESCAN00076413 */

# define CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel)        (kCanHwRxFullStartIndex)
# define CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel)       (kCanHwRxBasicStartIndex)
# define CAN_HL_HW_UNUSED_STARTINDEX(canHwChannel)         (kCanHwUnusedStartIndex)

# define CAN_HL_TX_STOPINDEX(channel)                      (kCanNumberOfTxObjects)
# define CAN_HL_TX_STAT_STOPINDEX(channel)                 (kCanNumberOfTxStatObjects)
# define CAN_HL_TX_DYN_ROM_STOPINDEX(channel)              (kCanNumberOfTxObjects)
# define CAN_HL_TX_DYN_RAM_STOPINDEX(channel)              (kCanNumberOfTxDynObjects)
/* # define CAN_HL_RX_STOPINDEX(channel)                      (kCanNumberOfRxObjects) */
# define CAN_HL_RX_BASIC_STOPINDEX(channel)                (kCanNumberOfRxBasicCANObjects)
# if defined( C_SEARCH_HASH ) || \
     defined( C_SEARCH_INDEX )
#  define CAN_HL_RX_FULL_STOPINDEX(canHwChannel)           (kCanNumberOfRxFullCANObjects)
# else
#  define CAN_HL_RX_FULL_STOPINDEX(canHwChannel)           (kCanNumberOfRxBasicCANObjects+kCanNumberOfRxFullCANObjects)
# endif
# define CAN_HL_INIT_OBJ_STOPINDEX(channel)                (kCanNumberOfInitObjects)
# define CAN_HL_LOG_HW_TX_STOPINDEX(canHwChannel)          (kCanNumberOfUsedTxCANObjects)
# define CAN_HL_HW_TX_STOPINDEX(canHwChannel)              (kCanHwTxStartIndex     +kCanNumberOfUsedTxCANObjects)
# define CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel)         (kCanHwRxFullStartIndex +kCanNumberOfRxFullCANObjects)
# define CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel)        (kCanHwRxBasicStartIndex+kCanNumberOfUsedRxBasicCANObjects)
# define CAN_HL_HW_UNUSED_STOPINDEX(canHwChannel)          (kCanHwUnusedStartIndex +kCanNumberOfUnusedObjects)

#else
#  define canHwChannel                                     channel   /* brackets are not allowed here due to compiler error with Renesas HEW compiler for SH2 */
#  define CAN_HL_HW_CHANNEL_STARTINDEX(channel)            (channel)
#  define CAN_HL_HW_CHANNEL_STOPINDEX(channel)             (channel)

#  define CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel)       (CanHwMsgTransmitIndex[(canHwChannel)])
#  define CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel)          (CanHwTxNormalIndex[(canHwChannel)])
/* Offset which has to be added to change the hardware Tx handle into a logical handle, which is unique over all channels */
/*        Tx-Hardware-Handle - CAN_HL_HW_TX_STARTINDEX(canHwChannel) + CAN_HL_LOG_HW_TX_STARTINDEX(canHwChannel) */
#  define CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)         (CanTxOffsetHwToLog[(canHwChannel)])

# define CAN_HL_TX_STARTINDEX(channel)                     (CanTxStartIndex[(channel)])
# define CAN_HL_TX_STAT_STARTINDEX(channel)                (CanTxStartIndex[(channel)])
# define CAN_HL_TX_DYN_ROM_STARTINDEX(channel)             (CanTxDynRomStartIndex[(channel)])
# define CAN_HL_TX_DYN_RAM_STARTINDEX(channel)             (CanTxDynRamStartIndex[(channel)])
/* # define CAN_HL_RX_STARTINDEX(channel)                     (CanRxStartIndex[(channel)]) */
/* index to access the ID tables - Basic index only for linear search */
# define CAN_HL_RX_BASIC_STARTINDEX(channel)               (CanRxBasicStartIndex[(channel)])      
# define CAN_HL_RX_FULL_STARTINDEX(canHwChannel)           (CanRxFullStartIndex[(canHwChannel)])
# define CAN_HL_INIT_OBJ_STARTINDEX(channel)               (CanInitObjectStartIndex[(channel)])      
# define CAN_HL_LOG_HW_TX_STARTINDEX(canHwChannel)         (CanLogHwTxStartIndex[(canHwChannel)])
#  define CAN_HL_HW_TX_STARTINDEX(canHwChannel)             (CanHwTxStartIndex[(canHwChannel)])   
#  define CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel)        (CanHwRxFullStartIndex[(canHwChannel)])
#  define CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel)       (CanHwRxBasicStartIndex[(canHwChannel)]) 
#  define CAN_HL_HW_UNUSED_STARTINDEX(canHwChannel)         (CanHwUnusedStartIndex[(canHwChannel)])
                                                           
# define CAN_HL_TX_STOPINDEX(channel)                      (CanTxStartIndex[(channel) + 1]) 
# define CAN_HL_TX_STAT_STOPINDEX(channel)                 (CanTxDynRomStartIndex[(channel)])
# define CAN_HL_TX_DYN_ROM_STOPINDEX(channel)              (CanTxStartIndex[(channel) + 1]) 
# define CAN_HL_TX_DYN_RAM_STOPINDEX(channel)              (CanTxDynRamStartIndex[(channel) + 1])
/* # define CAN_HL_RX_STOPINDEX(channel)                      (CanRxStartIndex[(channel) + 1]) */
/* index to access the ID tables - Basic index only for linear search */
# define CAN_HL_RX_BASIC_STOPINDEX(channel)                (CanRxFullStartIndex[CAN_HL_HW_CHANNEL_STARTINDEX(channel)])
# define CAN_HL_INIT_OBJ_STOPINDEX(channel)                (CanInitObjectStartIndex[(channel) + 1])
# define CAN_HL_LOG_HW_TX_STOPINDEX(canHwChannel)          (CanLogHwTxStartIndex[(canHwChannel) +1])      
#  define CAN_HL_HW_TX_STOPINDEX(canHwChannel)              (CanHwTxStopIndex[(canHwChannel)])
#  define CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel)         (CanHwRxFullStopIndex[(canHwChannel)])
#  define CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel)         (CanHwRxBasicStopIndex[(canHwChannel)])
#  define CAN_HL_HW_UNUSED_STOPINDEX(canHwChannel)         (CanHwUnusedStopIndex[(canHwChannel)])

#endif

#if defined( C_SINGLE_RECEIVE_CHANNEL )

# define CANRANGE0ACCMASK(i)                               C_RANGE0_ACC_MASK
# define CANRANGE0ACCCODE(i)                               C_RANGE0_ACC_CODE
# define CANRANGE1ACCMASK(i)                               C_RANGE1_ACC_MASK
# define CANRANGE1ACCCODE(i)                               C_RANGE1_ACC_CODE
# define CANRANGE2ACCMASK(i)                               C_RANGE2_ACC_MASK
# define CANRANGE2ACCCODE(i)                               C_RANGE2_ACC_CODE
# define CANRANGE3ACCMASK(i)                               C_RANGE3_ACC_MASK
# define CANRANGE3ACCCODE(i)                               C_RANGE3_ACC_CODE

# define APPL_CAN_MSG_RECEIVED( i )                        (APPL_CAN_MSGRECEIVED( i ))

# define APPLCANRANGE0PRECOPY( i )                         (ApplCanRange0Precopy( i ))   
# define APPLCANRANGE1PRECOPY( i )                         (ApplCanRange1Precopy( i ))   
# define APPLCANRANGE2PRECOPY( i )                         (ApplCanRange2Precopy( i ))   
# define APPLCANRANGE3PRECOPY( i )                         (ApplCanRange3Precopy( i ))   

# define APPL_CAN_BUSOFF( i )                              (ApplCanBusOff())
# define APPL_CAN_WAKEUP( i )                              (ApplCanWakeUp())

# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
#  define APPLCANCANCELNOTIFICATION( i, j )                (APPL_CAN_CANCELNOTIFICATION( j ))
# else
#  define APPLCANCANCELNOTIFICATION( i, j )
# endif
# if defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
#  define APPLCANMSGCANCELNOTIFICATION( i )                (APPL_CAN_MSGCANCELNOTIFICATION())
# else
#  define APPLCANMSGCANCELNOTIFICATION( i )
# endif

# define CAN_RX_INDEX_TBL(channel, id)                      (CanRxIndexTbl[id])

#else

# define CANRANGE0ACCMASK(i)                               (CanChannelObject[i].RangeMask[0])
# define CANRANGE0ACCCODE(i)                               (CanChannelObject[i].RangeCode[0])
# define CANRANGE1ACCMASK(i)                               (CanChannelObject[i].RangeMask[1])
# define CANRANGE1ACCCODE(i)                               (CanChannelObject[i].RangeCode[1])
# define CANRANGE2ACCMASK(i)                               (CanChannelObject[i].RangeMask[2])
# define CANRANGE2ACCCODE(i)                               (CanChannelObject[i].RangeCode[2])
# define CANRANGE3ACCMASK(i)                               (CanChannelObject[i].RangeMask[3])
# define CANRANGE3ACCCODE(i)                               (CanChannelObject[i].RangeCode[3])

/* generated id type of the range */
# define CANRANGE0IDTYPE(i)                                (CanChannelObject[i].RangeIdType[0])
# define CANRANGE1IDTYPE(i)                                (CanChannelObject[i].RangeIdType[1])
# define CANRANGE2IDTYPE(i)                                (CanChannelObject[i].RangeIdType[2])
# define CANRANGE3IDTYPE(i)                                (CanChannelObject[i].RangeIdType[3])

# define APPL_CAN_MSG_RECEIVED( i )                        (CanChannelObject[(i)->Channel].ApplCanMsgReceivedFct(i))

# define APPLCANRANGE0PRECOPY( i )                         (CanChannelObject[(i)->Channel].ApplCanRangeFct[0](i))
# define APPLCANRANGE1PRECOPY( i )                         (CanChannelObject[(i)->Channel].ApplCanRangeFct[1](i))   
# define APPLCANRANGE2PRECOPY( i )                         (CanChannelObject[(i)->Channel].ApplCanRangeFct[2](i))   
# define APPLCANRANGE3PRECOPY( i )                         (CanChannelObject[(i)->Channel].ApplCanRangeFct[3](i))   

# define APPL_CAN_BUSOFF( i )                              (CanChannelObject[i].ApplCanBusOffFct(i))
# define APPL_CAN_WAKEUP( i )                              (CanChannelObject[i].ApplCanWakeUpFct(i))

# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
#  define APPLCANCANCELNOTIFICATION( i, j )                (CanChannelObject[i].ApplCanCancelNotificationFct( j ))
# else
#  define APPLCANCANCELNOTIFICATION( i, j )
# endif

# if defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
#  define APPLCANMSGCANCELNOTIFICATION( i )                (CanChannelObject[i].ApplCanMsgTransmitCancelNotifyFct( i ))
# else
#  define APPLCANMSGCANCELNOTIFICATION( i )
# endif

# define CAN_RX_INDEX_TBL(channel, id)                      (CanRxIndexTbl[channel][id])

#endif

#if defined ( C_ENABLE_CAN_CAN_INTERRUPT_CONTROL )
# define CAN_CAN_INTERRUPT_DISABLE(channel)                        (CanCanInterruptDisable(CAN_CHANNEL_CANPARA_ONLY))
# define CAN_CAN_INTERRUPT_RESTORE(channel)                        (CanCanInterruptRestore(CAN_CHANNEL_CANPARA_ONLY))
#else
# define CAN_CAN_INTERRUPT_DISABLE(channel)
# define CAN_CAN_INTERRUPT_RESTORE(channel)
#endif

#if defined( C_ENABLE_INDIVIDUAL_POLLING )
/* define first index to array CanHwObjIndivPolling[][] */
#   define CAN_HWOBJINDIVPOLLING_INDEX0                    (0)
#endif

/* mask for range enable status */
#define kCanRange0                                         ((vuint16)1)
#define kCanRange1                                         ((vuint16)2)
#define kCanRange2                                         ((vuint16)4)
#define kCanRange3                                         ((vuint16)8)

/* Assertions ---------------------------------------------------------------- */
/* lint -function(exit, ApplCanFatalError) */

/* lint -emacro( (506), assertUser) */
#if defined( C_ENABLE_USER_CHECK )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define assertUser(p, c, e)                                if (!(p))   {ApplCanFatalError(e);}
# else
#  define assertUser(p, c, e)                                if (!(p))   {ApplCanFatalError((c), (e));}
# endif
#else
# define assertUser(p, c, e)
#endif

/* lint -emacro( (506), assertGen) */
#if defined( C_ENABLE_GEN_CHECK )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define assertGen(p, c, e)                                 if (!(p))   {ApplCanFatalError(e);}
# else
#  define assertGen(p, c, e)                                 if (!(p))   {ApplCanFatalError((c), (e));}
# endif
#else
# define assertGen(p, c, e)
#endif

/* lint -emacro( (506), assertHardware) */
#if defined( C_ENABLE_HARDWARE_CHECK )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define assertHardware(p, c, e)                            if (!(p))   {ApplCanFatalError(e);}
# else
#  define assertHardware(p, c, e)                            if (!(p))   {ApplCanFatalError((c), (e));}
# endif
#else
# define assertHardware(p, c, e)
#endif

/* lint -emacro( (506), assertInternal) */
#if defined( C_ENABLE_INTERNAL_CHECK )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define assertInternal(p, c, e)                            if (!(p))   {ApplCanFatalError(e);}
# else
#  define assertInternal(p, c, e)                            if (!(p))   {ApplCanFatalError((c), (e));}
# endif
#else
# define assertInternal(p, c, e)
#endif

#if defined( C_ENABLE_TRANSMIT_QUEUE )
#if defined( C_CPUTYPE_32BIT )
# define kCanTxQueueShift     5
#endif

/* mask used to get the flag index from the handle */
# define kCanTxQueueMask      (((vuint8)1 << kCanTxQueueShift) - (vuint8)1)

#if defined( C_SINGLE_RECEIVE_CHANNEL )
# define CAN_HL_TXQUEUE_PADBITS(channel)             ((CanTransmitHandle)0)
# define CAN_HL_TXQUEUE_STARTINDEX(channel)          ((CanSignedTxHandle)0)
# define CAN_HL_TXQUEUE_STOPINDEX(channel)           ((CanSignedTxHandle)kCanTxQueueSize)
#else
# define CAN_HL_TXQUEUE_PADBITS(channel)             ((CanTransmitHandle)CanTxQueuePadBits[(channel)])
# define CAN_HL_TXQUEUE_STARTINDEX(channel)          (CanTxQueueStartIndex[(channel)])
# define CAN_HL_TXQUEUE_STOPINDEX(channel)           (CanTxQueueStartIndex[(channel) + (CanChannelHandle)1])
#endif

#endif

#if defined(C_SINGLE_PHYS_CHANNEL)
# define canPhysChannel        kCanLogToPhys
#endif

/* creates a mask for a single bit within a dword */
#define CanLL_SL32(num) \
  ((vuint32) (((vuint32)0x00000001)<<((vuint8)(num)&0x1F)))

/* creates a mask for a single bit within a word */
#define CanLL_SL16(num) \
  ((vuint16) (((vuint16)0x0001)<<((vuint8)(num)&0x0F)))

/* creates a mask for a single bit within a byte */
#define CanLL_SL8(num) \
  ((vuint8) (((vuint8)0x01)<<((vuint8)(num)&0x07)))

/* creates a mask for a single bit within a shared register */
# define CanLL_SLRS(num) \
  CanLL_SL32(num)

# define CanLL_RsCast kCanRegSize

/* returns the position of a bit in a shared register */
#define CanLL_BitPosition(num) \
  ((num)&0x1F)

/* returns the registerindex of a bit in a shared register */
#define CanLL_BitIndex(num) \
  (((num)>>5)&0x03)

/* returns the registerindex of a bit in a continuous register */
#define CanLL_BitIndex16(num) \
  (((num)>>5)&0x0F)

/* preparation to clear a bit in a shared register */
#define CanLL_ClearBitRS(num) \
  ((CanLL_RsCast) ~CanLL_SLRS(CanLL_BitPosition(num)))

/* preparation to set a bit in a shared register */
#define CanLL_SetBitRS(num) \
  ((CanLL_RsCast) CanLL_SLRS(CanLL_BitPosition(num)))

/* clears multiple bits in a shared register */
#define CanLL_ClearBitMaskRS(mask) \
  ((CanLL_RsCast) ~(mask))

/* returns the registerindex of a channel dependent word in a shared register */
#define CanLL_WordIndex(pch) \
  (((pch)>>1)&0x03) 

/* returns the registerindex of a channel dependent byte in a shared register */
#define CanLL_ByteIndex(pch) \
  (((pch)>>2)&0x01)

/* masks one channel dependent word in a shared register */
# define CanLL_MaskWord(pch) \
   ((((pch)&0x01) == 0) ? ((kCanRegSize)0x0000FFFFu) : ((kCanRegSize)0xFFFF0000u))

/* creates a mask to clear one channel dependent word in a shared register */
#define CanLL_MaskWordClear(pch) \
  ((kCanRegSize) ~CanLL_MaskWord(pch))

/* returns a channel dependent word from a shared register */
# define CanLL_SharedRegToWord(pch,val) \
   ((((pch)&0x01) == 0) ? ((vuint16)(val)) : ((vuint16)((kCanRegSize)(val)>>16)))

/* returns a shared register value based on a channel dependent word */
# define CanLL_WordToSharedReg(pch,val) \
   ((((pch)&0x01) == 0) ? ((kCanRegSize)(val)) : ((kCanRegSize)((kCanRegSize)(val)<<16)))

/* returns a shared register value based on a channel dependent byte */
# define CanLL_FilterListConfig(pch,val) \
  (kCanRegSize)((((kCanRegSize)(val))&0x000000FF)<<(24-(((pch)&0x03)<<3)))

/* creates a mask for a single bit within kCanTxSize */
# define CanLL_SLTS(num) \
  CanLL_SL16(num)

/* preparation to clear a bit in a tx register */
#define CanLL_ClearBitTS(num) \
  ((kCanTxSize) ~CanLL_SLTS(num))

/* preparation to set a bit in a tx register */
#define CanLL_SetBitTS(num) \
  ((kCanTxSize) CanLL_SLTS(num))

/* requests a mode on a logical channel */
#define CanLL_ModeReq_Log(ch,mode) \
  (Can->ChCtrl[mCanLogToPhys(ch)].CR = ((Can->ChCtrl[mCanLogToPhys(ch)].CR & kCanModeMask) | (mode)))

/* checks the mode on a logical channel */
#define CanLL_ModeCheck_Log(ch,mode) \
  ((Can->ChCtrl[mCanLogToPhys(ch)].SR & kCanModeBits) == ((mode) & kCanModeBits))

/* requests a on a physical channel */
#define CanLL_ModeReq_Phys(pch,mode) \
  (Can->ChCtrl[pch].CR = ((Can->ChCtrl[pch].CR & kCanModeMask) | (mode)))

/* checks the mode on a physical channel */
#define CanLL_ModeCheck_Phys(pch,mode) \
  ((Can->ChCtrl[pch].SR & kCanModeBits) == ((mode) & kCanModeBits))

/* requests a global mode */
#define CanLL_GlobalModeReq(mode) \
  (Can->CGCR = ((Can->CGCR & kCanModeMask) | (mode)))

/* checks the global mode (also checks if RAMIST==0) */
#define CanLL_GlobalModeCheck(mode) \
  (Can->CGSR == (mode))

/* get error counters */
#define CanLL_Rec(ch) ((vuint8) ((Can->ChCtrl[mCanLogToPhys(ch)].SR & kCanSrMaskRec) >> 16))
#define CanLL_Tec(ch) ((vuint8) ((Can->ChCtrl[mCanLogToPhys(ch)].SR & kCanSrMaskTec) >> 24))

#if defined (C_ENABLE_LL_CAN_INTCTRL) || defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL)
# if defined (V_CPU_RH850)
/* configures a ICR or status-var to enable the interrupt source */
#   define CanLL_IntcIntEnableLoc(addr,prio) \
  ((addr) = (kCanIntcEITB | (prio)))

/* configures a ICR or status-var to disable the interrupt source */
#   define CanLL_IntcIntDisableLoc(addr) \
  ((addr) |= kCanIntcEIMK)

#  if defined (C_ENABLE_INTC_ACCESS_BY_APPL)

#   define CanLL_IntcIntEnable(area,reg,prio) \
  ApplCanWriteIcr8((vuint32)(&(reg)), (vuint8)(kCanIntcEITB | (prio)))

#   define CanLL_IntcIntDisable(area,reg) \
  ApplCanWriteIcr8((vuint32)(&(reg)), (vuint8)(ApplCanReadIcr8((vuint32)(&(reg))) | kCanIntcEIMK))

#   define CanLL_IntcIntFlag(area,reg) \
  ((ApplCanReadIcr8((vuint32)(&(reg))) & kCanIntcEIRF) == kCanIntcEIRF)

#   define CanLL_IntcIntClear(area,reg) \
  ApplCanWriteIcr8((vuint32)(&(reg)), (vuint8)(ApplCanReadIcr8((vuint32)(&(reg))) & kCanIntcEIRFNeg))

#   define CanLL_IntcIntSave(area,dst,src) \
  ((dst) = ApplCanReadIcr8((vuint32)(&(src))))

#   define CanLL_IntcIntRestore(area,dst,src) \
  ApplCanWriteIcr8((vuint32)(&(dst)), (vuint8)(src))

#  else /* C_ENABLE_INTC_ACCESS_BY_DRIVER */

/* configures a ICR to enable the interrupt source */
#   define CanLL_IntcIntEnable(area,reg,prio) \
  CanLL_IntcIntEnableLoc((reg),(prio))

/* configures a ICR to disable the interrupt source */
#   define CanLL_IntcIntDisable(area,reg) \
  CanLL_IntcIntDisableLoc(reg)

/* is true if the interrupt request flag is set within a ICR */
#   define CanLL_IntcIntFlag(area,reg) \
  (((reg) & kCanIntcEIRF) == kCanIntcEIRF)

/* clears the interrupt request flag within a ICR */
#   define CanLL_IntcIntClear(area,reg) \
  ((reg) &= kCanIntcEIRFNeg)

/* saves interrupt status from a ICR (src) to a status-var (dst) */
#   define CanLL_IntcIntSave(area,dst,src) \
  ((dst) = (src))

/* restores interrupt status from a status-var (src) to a ICR (dst) */
#   define CanLL_IntcIntRestore(area,dst,src) \
  ((dst) = (src))

#  endif /* C_ENABLE_INTC_ACCESS_BY_* */
# endif /* V_CPU_RH850 */
#endif /* C_ENABLE_LL_CAN_INTCTRL || C_ENABLE_LL_CAN_WAKEUP_INTCTRL */

# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define CanRxFcCount(hwch) \
  kCanNumberOfRxFullCANObjects
# else
#  define CanRxFcCount(hwch) \
  (vuint8) (CAN_HL_HW_RX_FULL_STOPINDEX(hwch) - CAN_HL_HW_RX_FULL_STARTINDEX(hwch))
# endif

# define txObjHandleAdjusted txObjHandle
# define hwObjHandleAdjusted hwObjHandle

#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
# if defined(C_ENABLE_WAKEUP_POLLING)
#  if defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL)
#   if defined(V_CPU_RH850)
#    define CanLL_CanWakeupOccurred( CAN_HW_CHANNEL_CANPARA_ONLY )                                                     \
      (CanLL_IntcIntFlag(CanAreaWup(canHwChannel),CanLL_StateCanInterruptWupPtr(canHwChannel)->uWup))
#   endif
#  endif
# else /* C_ENABLE_WAKEUP_POLLING */
#  if defined (C_ENABLE_LL_CAN_INTCTRL)
#   if defined(V_CPU_RH850)
#    define CanLL_CanWakeupInterruptDisable(canHwChannel, localInterruptOldFlagPtr)                                    \
{                                                                                                                      \
  CanLL_DeclareCanInterruptWupPtr                                                                                      \
  CanLL_AssignCanInterruptWupPtr(canHwChannel);                                                                        \
  CanLL_IntcIntDisable(CanAreaWup(canHwChannel),CanIntcChWup->Wup);                                                    \
  CanLL_IntcIntDisableLoc((*(localInterruptOldFlagPtr)).Wup);                                                          \
}
#   endif

#   if defined(V_CPU_RH850)
#    define CanLL_CanWakeupInterruptEnable(canHwChannel, localInterruptOldFlagPtr)                                               \
{                                                                                                                                \
  if (canCanInterruptCounter[canHwChannel] == 0)                                                                                 \
  { CanLL_DeclareCanInterruptWupPtr                                                                                              \
    CanLL_AssignCanInterruptWupPtr(canHwChannel);                                                                                \
    CanLL_IntcIntEnable(CanAreaWup(canHwChannel),CanIntcChWup->Wup,(CanChannelData[canHwChannel].CanIntPrio & kCanIntcIPR)); }   \
  else                                                                                                                           \
  { CanLL_IntcIntEnableLoc((*(localInterruptOldFlagPtr)).Wup,(CanChannelData[canHwChannel].CanIntPrio&kCanIntcIPR)); }           \
}
#   endif
#  endif /* C_ENABLE_LL_CAN_INTCTRL */
# endif /* C_ENABLE_WAKEUP_POLLING */
# if defined (C_ENABLE_LL_CAN_WAKEUP_INTCTRL)
#  if defined(V_CPU_RH850)
#   define CanLL_ClearCanWakeupInterruptFlag(canHwChannel)                                                             \
{                                                                                                                      \
  tCanIntcChWupPtr CanIntcChWup;                                                                                       \
  CanIntcChWup = (tCanIntcChWupPtr)CanChannelData[canHwChannel].CanIntcChWakeupBaseAdr;                                \
  CanLL_IntcIntClear(CanAreaWup(canHwChannel),CanIntcChWup->uWup);                                                     \
}
#  endif
# endif /* C_ENABLE_LL_CAN_WAKEUP_INTCTRL */
#endif /* C_ENABLE_LL_WAKEUP_SUPPORT */

#if defined (V_CPU_RH850)
# if defined( C_ENABLE_INDIVIDUAL_POLLING ) || !defined( C_ENABLE_RX_BASICCAN_POLLING )
#  define CanLL_CanInterruptDisable_RF(canDummy)                                                                       \
{                                                                                                                      \
  CanLL_IntcIntSave(CanAreaGlob,canInterruptOldFlag.RF,CanIntcRxFifo->RF);                                             \
  CanLL_IntcIntDisable(CanAreaGlob,CanIntcRxFifo->RF);                                                                 \
  CanLL_IntcIntSave(CanAreaGlob,(canDummy),CanIntcRxFifo->RF);                                                         \
}
#  define CanLL_CanInterruptRestore_RF()                                                                               \
  CanLL_IntcIntRestore(CanAreaGlob,CanIntcRxFifo->RF,canInterruptOldFlag.RF);

# else
#  define CanLL_CanInterruptDisable_RF(canDummy)
#  define CanLL_CanInterruptRestore_RF()
# endif /* C_ENABLE_INDIVIDUAL_POLLING || !C_ENABLE_RX_BASICCAN_POLLING */

# if !defined(C_ENABLE_ERROR_POLLING)
#  define CanLL_DeclareCanInterruptErrPtr                                                                              \
     tCanIntcChErrPtr CanIntcChErr;
#  define CanLL_AssignCanInterruptErrPtr(canHwChannel)                                                                 \
     CanIntcChErr = (tCanIntcChErrPtr)CanChannelData[canHwChannel].CanIntcChErrorBaseAdr

#  define CanLL_CanInterruptDisable_GErr(canDummy)                                                                     \
{                                                                                                                      \
  CanLL_IntcIntSave(CanAreaGlob,canInterruptOldFlag.GErr,CanIntcGErr->GErr);                                           \
  CanLL_IntcIntDisable(CanAreaGlob,CanIntcGErr->GErr);                                                                 \
  CanLL_IntcIntSave(CanAreaGlob,(canDummy),CanIntcGErr->GErr);                                                         \
}
#  define CanLL_CanInterruptRestore_GErr()                                                                             \
  CanLL_IntcIntRestore(CanAreaGlob,CanIntcGErr->GErr,canInterruptOldFlag.GErr);

#  define CanLL_CanInterruptDisable_Err(ch,localInterruptOldFlagPtr,canDummy)                                          \
{                                                                                                                      \
  CanLL_IntcIntSave(CanAreaCh(ch),(*(localInterruptOldFlagPtr)).Err,CanIntcChErr->Err);                                \
  CanLL_IntcIntDisable(CanAreaCh(ch),CanIntcChErr->Err);                                                               \
  CanLL_IntcIntSave(CanAreaCh(ch),(canDummy),CanIntcChErr->Err);                                                       \
}
#  define CanLL_CanInterruptRestore_Err(ch,localInterruptOldFlag)                                                      \
  CanLL_IntcIntRestore(CanAreaCh(ch),CanIntcChErr->Err,(localInterruptOldFlag).Err);

# else
#  define CanLL_DeclareCanInterruptErrPtr
#  define CanLL_AssignCanInterruptErrPtr(canHwChannel)
#  define CanLL_CanInterruptDisable_GErr(canDummy)
#  define CanLL_CanInterruptRestore_GErr()
#  define CanLL_CanInterruptDisable_Err(ch,localInterruptOldFlagPtr,canDummy)
#  define CanLL_CanInterruptRestore_Err(ch,localInterruptOldFlag)
# endif /* !C_ENABLE_ERROR_POLLING */

# if defined( C_ENABLE_INDIVIDUAL_POLLING ) || !defined( C_ENABLE_TX_POLLING )
#  define CanLL_DeclareCanInterruptTxPtr                                                                               \
     tCanIntcChTxPtr CanIntcChTx;
#  define CanLL_AssignCanInterruptTxPtr(canHwChannel)                                                                  \
     CanIntcChTx = (tCanIntcChTxPtr)CanChannelData[canHwChannel].CanIntcChTxBaseAdr

#  define CanLL_CanInterruptDisable_Tx(ch,localInterruptOldFlagPtr,canDummy)                                           \
{                                                                                                                      \
  CanLL_IntcIntSave(CanAreaCh(ch),(*(localInterruptOldFlagPtr)).Tx,CanIntcChTx->Tx);                                   \
  CanLL_IntcIntDisable(CanAreaCh(ch),CanIntcChTx->Tx);                                                                 \
  CanLL_IntcIntSave(CanAreaCh(ch),(canDummy),CanIntcChTx->Tx);                                                         \
}
#  define CanLL_CanInterruptRestore_Tx(ch,localInterruptOldFlag)                                                       \
  CanLL_IntcIntRestore(CanAreaCh(ch),CanIntcChTx->Tx,(localInterruptOldFlag).Tx);

# else
#  define CanLL_DeclareCanInterruptTxPtr
#  define CanLL_AssignCanInterruptTxPtr(canHwChannel)
#  define CanLL_CanInterruptDisable_Tx(ch,localInterruptOldFlagPtr,canDummy)
#  define CanLL_CanInterruptRestore_Tx(ch,localInterruptOldFlag)
# endif /* C_ENABLE_INDIVIDUAL_POLLING || !C_ENABLE_TX_POLLING */

# if defined( C_ENABLE_LL_WAKEUP_SUPPORT )
#  if defined( C_ENABLE_WAKEUP_POLLING )
#   define CanLL_DeclareCanInterruptWupPtr
#   define CanLL_AssignCanInterruptWupPtr(canHwChannel)
#   define CanLL_StateCanInterruptWupPtr(canHwChannel)                                                                 \
     ((tCanIntcChWupPtr)CanChannelData[canHwChannel].CanIntcChWakeupBaseAdr)

#   define CanLL_CanInterruptDisable_Wup(ch,localInterruptOldFlagPtr,canDummy)
#   define CanLL_CanInterruptRestore_Wup(ch,localInterruptOldFlag)
#  else
#   define CanLL_DeclareCanInterruptWupPtr                                                                             \
     tCanIntcChWupPtr CanIntcChWup;
#   define CanLL_AssignCanInterruptWupPtr(canHwChannel)                                                                \
     CanIntcChWup = (tCanIntcChWupPtr)CanChannelData[canHwChannel].CanIntcChWakeupBaseAdr

#   define CanLL_CanInterruptDisable_Wup(ch,localInterruptOldFlagPtr,canDummy)                                         \
{                                                                                                                      \
  CanLL_IntcIntSave(CanAreaWup(ch),(*(localInterruptOldFlagPtr)).Wup,CanIntcChWup->Wup);                               \
  CanLL_IntcIntDisable(CanAreaWup(ch),CanIntcChWup->Wup);                                                              \
  CanLL_IntcIntSave(CanAreaWup(ch),(canDummy),CanIntcChWup->Wup);                                                      \
}
#   define CanLL_CanInterruptRestore_Wup(ch,localInterruptOldFlag)                                                     \
  CanLL_IntcIntRestore(CanAreaWup(ch),CanIntcChWup->Wup,(localInterruptOldFlag).Wup);

#  endif /* C_ENABLE_WAKEUP_POLLING */
# else
#  define CanLL_DeclareCanInterruptWupPtr
#  define CanLL_AssignCanInterruptWupPtr(canHwChannel)
#  define CanLL_CanInterruptDisable_Wup(ch,localInterruptOldFlagPtr,canDummy)
#  define CanLL_CanInterruptRestore_Wup(ch,localInterruptOldFlag)
# endif /* C_ENABLE_LL_WAKEUP_SUPPORT */
#endif /* V_CPU_RH850 */

#if defined (C_ENABLE_LL_CAN_INTCTRL)
# if defined (V_CPU_RH850)
#  if defined(V_ENABLE_USE_DUMMY_STATEMENT)
#   define CanLL_AssignCanDummy(canDummy) ((canDummy) = (canDummy))
#  else
#   define CanLL_AssignCanDummy(canDummy)
#  endif

#  define CanLL_CanInterruptDisable(canHwChannel, localInterruptOldFlagPtr)                                            \
{                                                                                                                      \
  vuint8 canDummy = 0;                                                                                                 \
  CanLL_DeclareCanInterruptTxPtr                                                                                       \
  CanLL_DeclareCanInterruptErrPtr                                                                                      \
  CanLL_DeclareCanInterruptWupPtr                                                                                      \
  CanLL_AssignCanInterruptTxPtr(canHwChannel);                                                                         \
  CanLL_AssignCanInterruptErrPtr(canHwChannel);                                                                        \
  CanLL_AssignCanInterruptWupPtr(canHwChannel);                                                                        \
  if (canInterruptOldFlag.GErrCnt == kCanZero)                                                                         \
  {                                                                                                                    \
    CanLL_CanInterruptDisable_RF(canDummy);                                                                            \
    CanLL_CanInterruptDisable_GErr(canDummy);                                                                          \
  }                                                                                                                    \
  canInterruptOldFlag.GErrCnt++;                                                                                       \
  CanLL_CanInterruptDisable_Tx(canHwChannel,localInterruptOldFlagPtr,canDummy);                                        \
  CanLL_CanInterruptDisable_Err(canHwChannel,localInterruptOldFlagPtr,canDummy);                                       \
  CanLL_CanInterruptDisable_Wup(canHwChannel,localInterruptOldFlagPtr,canDummy);                                       \
  CanLL_AssignCanDummy(canDummy);                                                                                      \
  CanLL_SYNCP();                                                                                                       \
}
# endif
#else
# define CanLL_CanInterruptDisable(canHwChannel, localInterruptOldFlagPtr)
#endif /* C_ENABLE_LL_CAN_INTCTRL */

#if defined (C_ENABLE_LL_CAN_INTCTRL)
# if defined (V_CPU_RH850)
#  define CanLL_CanInterruptRestore(canHwChannel, localInterruptOldFlag)                                               \
{                                                                                                                      \
  CanLL_DeclareCanInterruptTxPtr                                                                                       \
  CanLL_DeclareCanInterruptErrPtr                                                                                      \
  CanLL_DeclareCanInterruptWupPtr                                                                                      \
  CanLL_AssignCanInterruptTxPtr(canHwChannel);                                                                         \
  CanLL_AssignCanInterruptErrPtr(canHwChannel);                                                                        \
  CanLL_AssignCanInterruptWupPtr(canHwChannel);                                                                        \
  canInterruptOldFlag.GErrCnt--;                                                                                       \
  if(canInterruptOldFlag.GErrCnt == kCanZero)                                                                          \
  {                                                                                                                    \
    CanLL_CanInterruptRestore_RF();                                                                                    \
    CanLL_CanInterruptRestore_GErr();                                                                                  \
  }                                                                                                                    \
  CanLL_CanInterruptRestore_Tx(canHwChannel,localInterruptOldFlag);                                                    \
  CanLL_CanInterruptRestore_Err(canHwChannel,localInterruptOldFlag);                                                   \
  CanLL_CanInterruptRestore_Wup(canHwChannel,localInterruptOldFlag);                                                   \
}
# endif
#else
# define CanLL_CanInterruptRestore(canHwChannel, localInterruptOldFlag)
#endif /* C_ENABLE_LL_CAN_INTCTRL */

#   define CanLL_TxIsHWObjFree( canHwChannel, txObjHandle ) \
  ((Can->ChBS[mCanLogToPhys(canHwChannel)].TBSR[(txObjHandle)-mCanTxBufOffset(canHwChannel)] & (kCanSrTxBufMaskAReq|kCanSrTxBufMaskTReq)) == 0)

#if defined( C_ENABLE_SLEEP_WAKEUP )
# define CanLL_HwIsSleep( CAN_HW_CHANNEL_CANPARA_ONLY ) \
    (CanLL_ModeCheck_Log((canHwChannel),kCanStopMode))
#else
# define CanLL_HwIsSleep( CAN_HW_CHANNEL_CANPARA_ONLY ) \
    (kCanFalse != kCanFalse)
#endif /* C_ENABLE_SLEEP_WAKEUP */

#define CanLL_HwIsStop( CAN_HW_CHANNEL_CANPARA_ONLY ) \
  (CanLL_ModeCheck_Log((canHwChannel),kCanResetMode) || CanLL_ModeCheck_Log((canHwChannel),kCanHaltMode))

#define CanLL_HwIsBusOff( CAN_HW_CHANNEL_CANPARA_ONLY ) \
  ((Can->ChCtrl[mCanLogToPhys(canHwChannel)].SR & kCanSrMaskBusoff) == kCanSrMaskBusoff)

#define CanLL_HwWasBusOff( CAN_HW_CHANNEL_CANPARA_ONLY ) \
  ((Can->ChCtrl[mCanLogToPhys(canHwChannel)].EF & kCanEfMaskBusoff) == kCanEfMaskBusoff)

#if defined( C_ENABLE_EXTENDED_STATUS )
# define CanLL_HwIsPassive( CAN_HW_CHANNEL_CANPARA_ONLY ) \
    ((Can->ChCtrl[mCanLogToPhys(canHwChannel)].SR & kCanSrMaskPassive) == kCanSrMaskPassive)

# define CanLL_HwIsWarning( CAN_HW_CHANNEL_CANPARA_ONLY )                        \
  (((CanLL_Rec(canHwChannel) >= (96u)) && (CanLL_Rec(canHwChannel) < (128u))) || \
   ((CanLL_Tec(canHwChannel) >= (96u)) && (CanLL_Tec(canHwChannel) < (128u))))
#endif /* C_ENABLE_EXTENDED_STATUS */

#if defined(C_ENABLE_HW_LOOP_TIMER) 
# if defined(C_MULTIPLE_RECEIVE_CHANNEL)
#  define CanLL_ApplCanTimerStart(loop)  ApplCanTimerStart(channel, loop)
#  define CanLL_ApplCanTimerEnd(loop)    ApplCanTimerEnd(channel, loop)
#  define CanLL_ApplCanTimerLoop(loop)   ApplCanTimerLoop(channel, loop)
# else
#  define CanLL_ApplCanTimerStart(loop)  ApplCanTimerStart(loop)
#  define CanLL_ApplCanTimerEnd(loop)    ApplCanTimerEnd(loop)
#  define CanLL_ApplCanTimerLoop(loop)   ApplCanTimerLoop(loop)
# endif /* C_MULTIPLE_RECEIVE_CHANNEL */
#else /* C_ENABLE_HW_LOOP_TIMER */
#  define CanLL_ApplCanTimerStart(loop)
#  define CanLL_ApplCanTimerEnd(loop)
#  define CanLL_ApplCanTimerLoop(loop)   1u
#endif /* C_ENABLE_HW_LOOP_TIMER */

#if defined(C_ENABLE_HW_LOOP_TIMER)
#  define CanLL_CanTimerStart(loop)      CanLL_ApplCanTimerStart(loop)
#  define CanLL_CanTimerEnd(loop)        CanLL_ApplCanTimerEnd(loop)
#  define CanLL_CanTimerLoop(loop)       CanLL_ApplCanTimerLoop(loop)

#  define CanLL_CanTimerWait(loop,condition)                     \
{                                                                \
  CanLL_CanTimerStart(loop);                                     \
  while ((condition) && (CanLL_CanTimerLoop(loop) != 0)) { ; }   \
  CanLL_CanTimerEnd(loop);                                       \
}
#else /* C_ENABLE_HW_LOOP_TIMER */
#  define CanLL_CanTimerStart(loop)
#  define CanLL_CanTimerEnd(loop)
#  define CanLL_CanTimerLoop(loop)       1u

#  define CanLL_CanTimerWait(loop,condition)                     \
    while (condition) { ; }
#endif /* C_ENABLE_HW_LOOP_TIMER */

#if defined(C_ENABLE_CANLL_GEN_CHECK)
# define assertGenLL(a, b, c)            if (!(a)) {CanLL_CheckGeneratedDataError();}
#endif

# define CAN_WAKEUP(channel)             (void) CanWakeUp( CAN_CHANNEL_CANPARA_ONLY )

# define CanLL_RtmStart(point)
# define CanLL_RtmStop(point)

/* *********************************************************************** */
/* Defines / data types / structs / unions                                 */
/* *********************************************************************** */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
#endif

typedef union
{ /* PRQA S 0750 */ /* MD_Can_0750 */
  vuint8  bData[8];
  vuint16 wData[4];
  vuint32 iData[2];
} tTmpData;

#if defined(C_ENABLE_LL_CAN_INTCTRL)
# if defined(V_CPU_RH850)
typedef struct
{
  vuint8  RF;
  vuint8  GErr;
  vuint8  GErrCnt;
} tCanLLCanGlobalIntOld;
# endif
#endif

# if defined(C_HL_ENABLE_CAN_IRQ_DISABLE)
#  if defined(V_CPU_RH850)
typedef struct tCanLLCanIntOldTag
{
  vuint8 Err;
  vuint8 Tx;
  vuint8 Wup;
} tCanLLCanIntOld;
#  endif
# endif

# if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS)
typedef struct tTmpMsgObjTag
{
  vuint32 Id;
  vuint32 Dlc;
  union
  { /* PRQA S 0750 */ /* MD_Can_0750 */
    vuint8  bData[8];
    vuint16 wData[4];
    vuint32 iData[2];
  } u;
} tTmpMsgObj;
# endif

/* *********************************************************************** */
/* Constants                                                               */
/* *********************************************************************** */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
/* ROM CATEGORY 1 START */
/* lookup table for setting the flags in the queue */
/* PRQA  S 1281 QAC_Can_1281 */ /* MD_Can_1281 */
V_MEMROM0 static V_MEMROM1 tCanQueueElementType V_MEMROM2 CanShiftLookUp[1 << kCanTxQueueShift] = 
{
#if defined( C_CPUTYPE_32BIT ) 
   (tCanQueueElementType)0x00000001, (tCanQueueElementType)0x00000002, (tCanQueueElementType)0x00000004, (tCanQueueElementType)0x00000008, 
   (tCanQueueElementType)0x00000010, (tCanQueueElementType)0x00000020, (tCanQueueElementType)0x00000040, (tCanQueueElementType)0x00000080
#endif

#if defined( C_CPUTYPE_32BIT ) 
 , (tCanQueueElementType)0x00000100, (tCanQueueElementType)0x00000200, (tCanQueueElementType)0x00000400, (tCanQueueElementType)0x00000800, 
   (tCanQueueElementType)0x00001000, (tCanQueueElementType)0x00002000, (tCanQueueElementType)0x00004000, (tCanQueueElementType)0x00008000
#endif

#if defined( C_CPUTYPE_32BIT )
 , (tCanQueueElementType)0x00010000, (tCanQueueElementType)0x00020000, (tCanQueueElementType)0x00040000, (tCanQueueElementType)0x00080000, 
   (tCanQueueElementType)0x00100000, (tCanQueueElementType)0x00200000, (tCanQueueElementType)0x00400000, (tCanQueueElementType)0x00800000,
   (tCanQueueElementType)0x01000000, (tCanQueueElementType)0x02000000, (tCanQueueElementType)0x04000000, (tCanQueueElementType)0x08000000, 
   (tCanQueueElementType)0x10000000, (tCanQueueElementType)0x20000000, (tCanQueueElementType)0x40000000, (tCanQueueElementType)0x80000000
#endif
};
/* PRQA  L:QAC_Can_1281 */

/* returns the highest pending flag from the lower nibble */
V_MEMROM0 static V_MEMROM1 vsint8 V_MEMROM2 CanGetHighestFlagFromNibble[16] =        /* PRQA S 3218 */ /* MD_Can_3218 */
{    
  (vsint8)-1,                /* (vsint8)0xFF - changed due to misra; cast due to R32C */
  0x00,
  0x01, 0x01,
  0x02, 0x02, 0x02, 0x02,
  0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
};
/* ROM CATEGORY 1 END */
#endif
/* Global constants with CAN driver main and subversion */
/* ROM CATEGORY 4 START */
V_DEF_CONST(V_NONE, vuint8, CONST) kCanMainVersion   = (vuint8)(( DRVCAN_SH2RSCANHLL_VERSION ) >> 8 );  /* lint !e572 !e778 */
V_DEF_CONST(V_NONE, vuint8, CONST) kCanSubVersion    = (vuint8)(( DRVCAN_SH2RSCANHLL_VERSION ) & 0x00FF );
V_DEF_CONST(V_NONE, vuint8, CONST) kCanBugFixVersion = (vuint8)(  DRVCAN_SH2RSCANHLL_RELEASE_VERSION );
/* ROM CATEGORY 4 END */

#if defined(C_ENABLE_CAN_RAM_CHECK) || (defined(C_ENABLE_CAN_HW_RAM_CHECK) )
/* ROM CATEGORY 4 START */
V_DEF_CONST(CAN_STATIC, vuint32, CONST) CanMemCheckValues32bit[3] = /* PRQA S 3218 */ /* MD_Can_3218 */
{
  0xAAAAAAAAUL, 0x55555555UL, 0x00000000UL
};
/* ROM CATEGORY 4 END */
#endif

/* *********************************************************************** */
/* CAN-Hardware Data Definitions                                           */
/* *********************************************************************** */

# define mRuleCode(idx)        Can->Rule[idx].Code
# define mRuleMask(idx)        Can->Rule[idx].Mask
# define mRuleBuf(idx)         Can->Rule[idx].Buf
# define mRuleFifo(idx)        Can->Rule[idx].Fifo
# define mCRAMTR(idx)          Can->CRAMTR[idx]
# define mBufId(idx)           Can->Buf[idx].Id
# define mBufDlc(idx)          Can->Buf[idx].Dlc
# define mBufbData(bidx,didx)  Can->Buf[bidx].u.bData[didx]
# define mBufwData(bidx,didx)  Can->Buf[bidx].u.wData[didx]
# define mBufiData(bidx,didx)  Can->Buf[bidx].u.iData[didx]
# define mTHAR(idx)            Can->THAR[idx]

typedef volatile struct        /* channel control and status */
{
  volatile vuint32      BCFG;                                  /* CmCFG */
  volatile vuint32      CR;                                    /* CmCTR */
  volatile vuint32      SR;                                    /* CmSTS */
  volatile vuint16      EF;                                    /* CmERFLL */
  volatile vuint16      CRC;                                   /* CmERFLH */
} tCanChCtrl;

typedef volatile struct        /* fifo control */
{
  volatile vuint32      TRFCR[kCanMaxTxFifosCell];             /* CFCCk */
} tCanChFC;

typedef volatile struct        /* fifo status */
{
  volatile kCanRegSize  TRFSR[kCanMaxTxFifosCell];             /* CFSTSk */
} tCanChFS;

typedef volatile struct        /* fifo pointer control */
{
  volatile kCanRegSize  TRFPCR[kCanMaxTxFifosCell];            /* CFPCTRk */
} tCanChFPC;

typedef volatile struct        /* buffer control */
{
  volatile vuint8       TBCR[kCanMaxTxBufCell];                /* TMCp */
} tCanChBC;

typedef volatile struct        /* buffer status */
{
  volatile vuint8       TBSR[kCanMaxTxBufCell];                /* TMSTSp */
} tCanChBS;

typedef volatile struct        /* receive rule */
{
  volatile vuint32      Code;     /* A - ID code            */ /* GAFLIDj */ 
  volatile vuint32      Mask;     /* B - ID mask            */ /* GAFLMj  */ 
  volatile vuint32      Buf;      /* C - DLC, label, buffer */ /* GAFLP0j */ 
  volatile vuint32      Fifo;     /* D - fifo               */ /* GAFLP1j */ 
} tCanRule;

typedef volatile struct        /* mailbox */
{
  volatile vuint32      Id;       /* A - ID                 */ /* RMIDq / RFIDx / CFIDk / TMIDp */
  volatile kCanRegSize  Dlc;      /* B - DLC, label, timest.*/ /* RMPTRq / RFPTRx / CFPTRk / TMPTRp */ 
  union { /* PRQA S 0750 */ /* MD_Can_0750 */                  /* RMDF[0/1]q / RFDF[0/1]x / CFDF[0/1]k / TMDF[0/1]p */
    volatile vuint8     bData[8]; /* C,D - data             */
    volatile vuint16    wData[4]; /* C,D - data             */
    volatile vuint32    iData[2]; /* C,D - data             */
  } u;
} tCanMsgObj;

typedef volatile struct
{
  /* control and status */
  tCanChCtrl            ChCtrl[kCanMaxPhysChannelsCell];       /* CmCFG, CmCTR, CmSTS, CmERFL */
  volatile kCanRegSize  Unused01[1];
  volatile vuint32      CGCFG;                                 /* GCFG */
  volatile vuint32      CGCR;                                  /* GCTR */
  volatile kCanRegSize  CGSR;                                  /* GSTS */
  volatile kCanRegSize  CGEF;                                  /* GERFL */
  volatile kCanRegSize  CTS;                                   /* GTSC */
  /* receive rules */
  volatile kCanRegSize  CRECR;                                 /* GAFLECTR */
  volatile kCanRegSize  CRNCFG[kCanNumberOfSharedReg8Cell];    /* GAFLCFG[0/1] */
  /* rx buffers */
  volatile kCanRegSize  CRBNUM;                                /* RMNB */
  volatile kCanRegSize  CRBRCF[kCanNumberOfSharedReg16Cell];   /* RMND[0/1/2/3] */
  /* fifos */
  volatile kCanRegSize  CRFCR[kCanMaxRxFifosCell];             /* RFCCx */
  volatile kCanRegSize  CRFSR[kCanMaxRxFifosCell];             /* RFSTSx */
  volatile kCanRegSize  CRFPCR[kCanMaxRxFifosCell];            /* RFPCTRx */
  tCanChFC              ChFC[kCanMaxPhysChannelsCell];         /* CFCCk */
  tCanChFS              ChFS[kCanMaxPhysChannelsCell];         /* CFSTSk */
  tCanChFPC             ChFPC[kCanMaxPhysChannelsCell];        /* CFPCTRk */
  volatile kCanRegSize  CFESR;                                 /* FESTS */
  volatile kCanRegSize  CFFSR;                                 /* FFSTS */
  volatile kCanRegSize  CFMLSR;                                /* FMSTS */
  volatile kCanRegSize  CRFISR;                                /* RFISTS */
  volatile kCanRegSize  CTRFRISR;                              /* CFRISTS */
  volatile kCanRegSize  CTRFTISR;                              /* CFTISTS */
  /* tx buffers */
  tCanChBC              ChBC[kCanMaxPhysChannelsCell];         /* TMCp */
  tCanChBS              ChBS[kCanMaxPhysChannelsCell];         /* TMSTSp */
  volatile kCanRegSize  CTBTRSR[kCanNumberOfSharedReg16Cell];  /* TMTRSTSy */
  volatile kCanRegSize  CTBARSR[kCanNumberOfSharedReg16Cell];  /* TMTARSTSy */
  volatile kCanRegSize  CTBTCSR[kCanNumberOfSharedReg16Cell];  /* TMTCSTSy */
  volatile kCanRegSize  CTBASR[kCanNumberOfSharedReg16Cell];   /* TMTASTSy */
  volatile kCanRegSize  CTBIER[kCanNumberOfSharedReg16Cell];   /* TMIECy */
  /* tx queue */
  volatile kCanRegSize  TQCR[kCanMaxPhysChannelsCell];         /* TXQCCm */
  volatile kCanRegSize  TQSR[kCanMaxPhysChannelsCell];         /* TXQSTSm */
  volatile kCanRegSize  TQPCR[kCanMaxPhysChannelsCell];        /* TXQPCTRm */
  /* tx history */
  volatile kCanRegSize  THCR[kCanMaxPhysChannelsCell];         /* THLCCm */
  volatile kCanRegSize  THSR[kCanMaxPhysChannelsCell];         /* THLSTSm */
  volatile kCanRegSize  THPCR[kCanMaxPhysChannelsCell];        /* THLPCTRm */
  /* tx interrupt status, global test */
  volatile kCanRegSize  CGTINTSTS[kCanNumberOfSharedReg8Cell]; /* GTINTSTS[0/1] */
  volatile kCanRegSize  CGTCFG;                                /* GTSTCFG */
  volatile kCanRegSize  CGTCR;                                 /* GTSTCTR */
  volatile kCanRegSize  Unused02[3];
  volatile kCanRegSize  CGTPUR;                                /* GLOCKK */
#if defined(C_ENABLE_IF_RSCAN)
  volatile kCanRegSize  Unused03[32];
#endif
#if defined(C_ENABLE_IF_RSCAN_FD)
  volatile kCanRegSize  Unused03[31];
  volatile kCanRegSize  CGRMCFG;                               /* CFDGRMCFG */
#endif
  /* receive rules */
  tCanRule              Rule[kCanMaxRuleAccessCell];           /* GAFLIDj, GAFLMj, GAFLP0j, GAFLP1j */
  /* mailbox access */
  tCanMsgObj            Buf[kCanMaxHwObjectsCell];             /* [RM/RF/CF/TM]ID, [RM/RF/CF/TM]PTR, [RM/RF/CF/TM]DF[0/1] */
  volatile kCanRegSize  THAR[kCanMaxPhysChannelsCell];         /* THLACCm */
  volatile kCanRegSize  Unused04[56];
  /* ram test */
  volatile vuint32      CRAMTR[kCanMaxRamTestAccessCell];      /* RPGACCr */
} tCanCell;

V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanCell) tCanCellPtr;
#define Can ((tCanCellPtr) CAN_CAST_ADDR(kCanBaseAdr))

#if defined (C_ENABLE_LL_CAN_INTCTRL)
# if defined(V_CPU_RH850)
typedef volatile struct
{
  volatile vuint8       Tx;                      /* lower channel Tx ICR     */
  volatile vuint8       uTx;                     /* upper channel Tx ICR     */
} tCanIntcChTxObj;

typedef volatile struct
{
  volatile vuint8       Err;                     /* lower channel error ICR  */
  volatile vuint8       uErr;                    /* upper channel error ICR  */
} tCanIntcChErrObj;

typedef volatile struct
{
  volatile vuint8       RF;                      /* lower receive FIFO ICR   */
  volatile vuint8       uRF;                     /* upper receive FIFO ICR   */
} tCanIntcRxFifoObj;

typedef volatile struct
{
  volatile vuint8       GErr;                    /* lower global error ICR   */
  volatile vuint8       uGErr;                   /* upper global error ICR   */
} tCanIntcGErrObj;
# endif

# if defined(V_CPU_RH850)
V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanIntcChTxObj) tCanIntcChTxPtr;
V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanIntcChErrObj) tCanIntcChErrPtr;
V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanIntcRxFifoObj) tCanIntcRxFifoPtr;
V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanIntcGErrObj) tCanIntcGErrPtr;
#  define CanIntcRxFifo ((tCanIntcRxFifoPtr) CAN_CAST_ADDR(kCanIntcRxFifoBaseAdr))
#  define CanIntcGErr ((tCanIntcGErrPtr) CAN_CAST_ADDR(kCanIntcGErrorBaseAdr))
# endif
#endif /* C_ENABLE_LL_CAN_INTCTRL */

#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
# if defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL) || defined(C_ENABLE_WAKEUP_POLLING)
#  if defined(V_CPU_RH850)
typedef volatile struct
{
  volatile vuint8       Wup;                     /* lower channel wakeup ICR */
  volatile vuint8       uWup;                    /* upper channel wakeup ICR */
} tCanIntcChWupObj;
V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanIntcChWupObj) tCanIntcChWupPtr;
#  endif
# endif
#endif /* C_ENABLE_LL_WAKEUP_SUPPORT */

#if defined(C_ENABLE_CAN_HW_RAM_CHECK)
V_DEF_P2SFR_CAN_TYPE(V_NONE, volatile kCanRegSize) tCanHwRamCheckPtr;
#endif

/* *********************************************************************** */
/* external declarations                                                   */
/* *********************************************************************** */

#if !defined( CANDRV_SET_CODE_TEST_POINT )
# define CANDRV_SET_CODE_TEST_POINT(x)
#else
extern vuint8 tscCTKTestPointState[CTK_MAX_TEST_POINT];       /* PRQA S 3447 */ /* MD_Can_3447 */
#endif

/* *********************************************************************** */
/* global data definitions                                                 */
/* *********************************************************************** */

/* RAM CATEGORY 1 START */
volatile CanReceiveHandle canRxHandle[kCanNumberOfChannels];        /* PRQA S 1514,3408 */ /* MD_Can_3218,MD_Can_3447 */
/* RAM CATEGORY 1 END */

/* RAM CATEGORY 3 START */
#if defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_DYN_TX_OBJECTS )   && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
CanTransmitHandle          confirmHandle[kCanNumberOfChannels];
#endif
/* RAM CATEGORY 3 END */

/* RAM CATEGORY 1 START */
#if defined( C_ENABLE_CONFIRMATION_FLAG )
/* Msg(4:0750) A union type has been used. MISRA Rules 110 - no change */
V_MEMRAM0 volatile V_MEMRAM1_NEAR union CanConfirmationBits V_MEMRAM2_NEAR CanConfirmationFlags;       /* PRQA S 0759 */ /* MD_Can_0750 */
#endif

#if defined( C_ENABLE_INDICATION_FLAG )
/* Msg(4:0750) A union type has been used. MISRA Rules 110 - no change */
V_MEMRAM0 volatile V_MEMRAM1_NEAR union CanIndicationBits   V_MEMRAM2_NEAR CanIndicationFlags;         /* PRQA S 0759 */ /* MD_Can_0750 */
#endif
/* RAM CATEGORY 1 END */

/* RAM CATEGORY 1 START */
#if defined( C_ENABLE_VARIABLE_RX_DATALEN )
/* ##RI1.4 - 3.31: Dynamic Receive DLC */
volatile vuint8 canVariableRxDataLen[kCanNumberOfRxObjects];
#endif
/* RAM CATEGORY 1 END */

/* RAM CATEGORY 1 START */
CanChipDataPtr canRDSRxPtr[kCanNumberOfChannels];                  /* PRQA S 1514 */ /* MD_Can_3218 */
/* RAM CATEGORY 1 END */

/* *********************************************************************** */
/* local data definitions                                                  */
/* *********************************************************************** */

/* support for CAN driver features : */
/* RAM CATEGORY 1 START */
static volatile CanTransmitHandle canHandleCurTxObj[kCanNumberOfUsedTxCANObjects];
/* RAM CATEGORY 1 END */

/* RAM CATEGORY 2 START */
#if defined( C_ENABLE_ECU_SWITCH_PASS )
static vuint8 canPassive[kCanNumberOfChannels];
#endif
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
#if defined( C_ENABLE_CAN_RAM_CHECK )
static vuint8 canComStatus[kCanNumberOfChannels]; /* stores the decision of the App after the last CAN RAM check */
#endif

#if defined( C_ENABLE_DYN_TX_OBJECTS )
static volatile vuint8 canTxDynObjReservedFlag[kCanNumberOfTxDynObjects];

# if defined( C_ENABLE_DYN_TX_ID )
static tCanTxId0 canDynTxId0[kCanNumberOfTxDynObjects];
#  if (kCanNumberOfUsedCanTxIdTables > 1)
static tCanTxId1 canDynTxId1[kCanNumberOfTxDynObjects];
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 2)
static tCanTxId2 canDynTxId2[kCanNumberOfTxDynObjects];
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 3)
static tCanTxId3 canDynTxId3[kCanNumberOfTxDynObjects];
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 4)
static tCanTxId4 canDynTxId4[kCanNumberOfTxDynObjects];
#  endif
#  if defined( C_ENABLE_MIXED_ID )
#   if defined( C_HL_ENABLE_IDTYPE_IN_ID )
#   else
static tCanIdType                 canDynTxIdType[kCanNumberOfTxDynObjects];
#   endif
#  endif
# endif

# if defined( C_ENABLE_DYN_TX_DLC )
static vuint8                   canDynTxDLC[kCanNumberOfTxDynObjects];
# endif
# if defined( C_ENABLE_DYN_TX_DATAPTR )
static TxDataPtr                  canDynTxDataPtr[kCanNumberOfTxDynObjects];
# endif
# if defined( C_ENABLE_CONFIRMATION_FCT )
# endif 
#endif /* C_ENABLED_DYN_TX_OBJECTS */

#if defined( C_ENABLE_TX_MASK_EXT_ID )
static tCanTxId0 canTxMask0[kCanNumberOfChannels];
# if (kCanNumberOfUsedCanTxIdTables > 1)
static tCanTxId1 canTxMask1[kCanNumberOfChannels];
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
static tCanTxId2 canTxMask2[kCanNumberOfChannels];
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
static tCanTxId3 canTxMask3[kCanNumberOfChannels];
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
static tCanTxId4 canTxMask4[kCanNumberOfChannels];
# endif
#endif

#if defined( C_ENABLE_VARIABLE_DLC )
static vuint8 canTxDLC_RAM[kCanNumberOfTxObjects];
#endif

#if defined( C_HL_ENABLE_COPROCESSOR_SUPPORT )
#else
static volatile vuint8 canStatus[kCanNumberOfChannels];

# if defined( C_ENABLE_PART_OFFLINE )
static vuint8 canTxPartOffline[kCanNumberOfChannels];
# endif
#endif
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 1 START */

#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL)
static vsintx          canCanInterruptCounter[kCanNumberOfChannels];        /* lint !e551 */
# if defined( C_HL_ENABLE_CAN_IRQ_DISABLE )
static tCanLLCanIntOld canCanInterruptOldStatus[kCanNumberOfHwChannels];
# endif
#endif
/* RAM CATEGORY 1 END */

#if defined( C_HL_ENABLE_LAST_INIT_OBJ )
/* RAM CATEGORY 4 START */
static CanInitHandle lastInitObject[kCanNumberOfChannels];
/* RAM CATEGORY 4 END */
#endif
#if defined( C_ENABLE_TX_POLLING )          || \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  || \
    defined( C_ENABLE_RX_BASICCAN_POLLING ) || \
    defined( C_ENABLE_ERROR_POLLING )       || \
    defined( C_ENABLE_WAKEUP_POLLING )      
/* RAM CATEGORY 2 START */
static vuint8 canPollingTaskActive[kCanNumberOfChannels];
/* RAM CATEGORY 2 END */
#endif

/* RAM CATEGORY 1 START */
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )  || \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
static tCanRxInfoStruct        canRxInfoStruct[kCanNumberOfChannels];
#endif
#if defined( C_ENABLE_CAN_TX_CONF_FCT )
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
static tCanTxConfInfoStruct    txInfoStructConf[kCanNumberOfChannels];
#endif

#if defined( C_ENABLE_COND_RECEIVE_FCT )
static volatile vuint8 canMsgCondRecState[kCanNumberOfChannels];
#endif

#if defined( C_ENABLE_RX_QUEUE )
static tCanRxQueue canRxQueue;         /* the rx queue (buffer and queue variables) */
#endif
/* RAM CATEGORY 1 END */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
/* RAM CATEGORY 1 START */
static volatile tCanQueueElementType canTxQueueFlags[kCanTxQueueSize];
/* RAM CATEGORY 1 END */
#endif
#if defined(V_CPU_RH850) 
# if defined(C_ENABLE_LL_CAN_INTCTRL)
V_DEF_VAR(CAN_STATIC, tCanLLCanGlobalIntOld, VAR_NOINIT) canInterruptOldFlag;
# endif
#endif
# if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) || defined( C_ENABLE_RX_BASICCAN_OBJECTS )
V_DEF_VAR(CAN_STATIC, tTmpMsgObj, VAR_NOINIT) CanLL_RxTmpBuf[kCanNumberOfHwChannels]; /* PRQA S 3218 */ /* MD_Can_3218 */
# endif
# if defined(C_ENABLE_STOP)
V_DEF_VAR(CAN_STATIC, vuint8, VAR_NOINIT) CanLL_StopTransition[kCanNumberOfChannels];
# endif

/* *********************************************************************** */
/*  local prototypes                                                       */
/* *********************************************************************** */
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )  || \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
# if defined( C_ENABLE_RX_QUEUE )
/* CODE CATEGORY 1 START */
static vuint8 CanHL_ReceivedRxHandleQueue(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 1 END */
# endif
/* CODE CATEGORY 1 START */
# if ( kCanNumberOfRxObjects > 0 )
#  if defined( C_ENABLE_RX_QUEUE )
static vuint8 CanHL_ReceivedRxHandle( CAN_CHANNEL_CANTYPE_FIRST tCanRxInfoStruct *pCanRxInfoStruct );
#  else
static vuint8 CanHL_ReceivedRxHandle( CAN_CHANNEL_CANTYPE_ONLY );
#  endif
# endif /* ( kCanNumberOfRxObjects > 0 ) */ 
/* CODE CATEGORY 1 END */
# if defined( C_ENABLE_INDICATION_FLAG ) || \
     defined( C_ENABLE_INDICATION_FCT )
/* CODE CATEGORY 1 START */
static void CanHL_IndRxHandle( CanReceiveHandle rxHandle );
/* CODE CATEGORY 1 END */
# endif
#endif
#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* CODE CATEGORY 1 START */
static void CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);  
/* CODE CATEGORY 1 END */
#endif
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/* CODE CATEGORY 1 START */
static void CanFullCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);
/* CODE CATEGORY 1 END */
#endif

/* CODE CATEGORY 1 START */
static void CanHL_TxConfirmation(CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle);
/* CODE CATEGORY 1 END */
# if defined( C_ENABLE_CAN_TRANSMIT )
/* CODE CATEGORY 1 START */
static vuint8 CanCopyDataAndStartTransmission(CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle, CanTransmitHandle txHandle)  C_API_3;   /* lint !e14 !e31 */
/* CODE CATEGORY 1 END */
# endif   /* C_ENABLE_CAN_TRANSMIT */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
/* CODE CATEGORY 4 START */
static void CanDelQueuedObj( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 4 END */
# if defined( C_ENABLE_TX_POLLING ) 
/* CODE CATEGORY 2 START */
static void CanHl_RestartTxQueue( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 2 END */
# endif
#endif 

/* CODE CATEGORY 2 START */
static void CanHL_ErrorHandling( CAN_HW_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 2 END */

#if defined( C_ENABLE_VARIABLE_RX_DATALEN )
/* CODE CATEGORY 1 START */
static void CanSetVariableRxDatalen ( CanReceiveHandle rxHandle, vuint8 dataLen );
/* CODE CATEGORY 1 END */
#endif

#if defined(C_ENABLE_SLEEP_WAKEUP)
# if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_WakeUpHandling(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# else
#  define CanLL_WakeUpHandling(channel)
# endif
#endif
#if defined( C_ENABLE_CAN_RAM_CHECK )
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_IsMailboxCorrupt(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle hwObjHandle);
/* CODE CATEGORY 4 END */
#endif
#if defined(C_ENABLE_CAN_HW_RAM_CHECK)
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_IsHwRamCorrupt(void);
/* CODE CATEGORY 4 END */
#endif
#if defined( C_ENABLE_CANLL_GEN_CHECK )
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_CheckGeneratedData(void);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_CheckGeneratedDataError(void);
/* CODE CATEGORY 4 END */
#endif

/* CODE CATEGORY 1 START */
/* ! Tx Polling */
# if defined( C_ENABLE_TX_POLLING ) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanInterruptTx(CAN_HW_CHANNEL_CANTYPE_ONLY);
# endif /* C_ENABLE_TX_POLLING */

# if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* ! Wakeup Polling */
#   if defined(C_ENABLE_WAKEUP_POLLING)
#   else
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanInterruptWakeup(CAN_HW_CHANNEL_CANTYPE_ONLY);
#   endif /* C_ENABLE_WAKEUP_POLLING */
# endif

/* ! Error Polling */
# if defined(C_ENABLE_ERROR_POLLING)
# else
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanInterruptStatus(CAN_HW_CHANNEL_CANTYPE_ONLY);
#  if defined(C_ENABLE_RX_BASICCAN_OBJECTS) 
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanInterruptGlobalStatus(void);
#  endif
# endif /* C_ENABLE_ERROR_POLLING */

/* ! Rx BasicCAN Polling */
# if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
#  if defined(C_ENABLE_RX_BASICCAN_POLLING ) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
#  else
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanInterruptRxFifo(void);
#  endif /* C_ENABLE_RX_BASICCAN_POLLING */
# endif /* C_ENABLE_RX_BASICCAN_OBJECTS */
/* CODE CATEGORY 1 END */

/* *********************************************************************** */
/*  Error Check                                                            */
/* *********************************************************************** */

/* *************** error check for Organi process ************************ */

/* *************** error check for not supported feature  ****************** */

#if defined( C_ENABLE_COMMON_CAN )
# error "Common CAN is not supported with this CAN driver implementation"
#endif

#if defined( C_ENABLE_MULTI_ECU_CONFIG )
# error "Multiple Configuration is not supported with this CAN driver implementation"
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
# error "Extended RAM Check is not supported with this CAN driver implementation"
#endif

#if (VSTDLIB__COREHLL_VERSION  <  0x0213 )
# error "Incompatible version of VStdLib. Core Version 2.13.00 or higher is necessary."
#endif

#if (kCanNumberOfHwChannels > 255)
#  error "Too many CAN channels. This driver can only handle up to 255 channels"
#endif

#if defined( C_SEARCH_HASH )
# if !defined( kHashSearchListCountEx )
#  error "kHashSearchListCountEx not defined"
# endif
# if !defined( kHashSearchMaxStepsEx )
#  error "kHashSearchMaxStepsEx not defined"
# endif
# if !defined( kHashSearchListCount )
#  error "kHashSearchListCount not defined"
# endif
# if !defined( kHashSearchMaxSteps )
#  error "kHashSearchMaxSteps not defined"
# endif
# if ( (kHashSearchMaxStepsEx < 1) ||(kHashSearchMaxStepsEx > 32768) )
#  error "kHashSearchMaxStepsEx has ilegal value"
# endif
# if ( kHashSearchListCountEx > 32768 )
#  error "Hash table for extended ID is too large"
# endif
# if ( (kHashSearchMaxSteps < 1) ||(kHashSearchMaxSteps > 32768) )
#  error "kHashSearchMaxStepsEx has ilegal value"
# endif
# if ( kHashSearchListCount > 32768 )
#  error "Hash table for standard ID is too large"
# endif
# if !defined( C_ENABLE_EXTENDED_ID) && (kHashSearchListCountEx > 0)
#  error "kHashSearchListCountEx has to be 0 in this configuration"
# endif
# if defined( C_ENABLE_EXTENDED_ID) && !defined( C_ENABLE_MIXED_ID) &&(kHashSearchListCount > 0)
#  error "kHashSearchListCount has to be 0 in this configuration"
# endif
#endif

#if defined( C_ENABLE_RX_QUEUE )
# if !defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
#  error "RX-Queue requires C_HL_ENABLE_RX_INFO_STRUCT_PTR"
# endif
#endif

#if defined( C_SEARCH_INDEX ) && defined( C_ENABLE_EXTENDED_ID )
# error "Index search is not possible with extended ID's"
#endif /* defined( C_SEARCH_INDEX ) */

#if defined ( CAN_POLLING_IRQ_DISABLE ) || defined ( CAN_POLLING_IRQ_RESTORE )
# error "Feature has changed - use C_DISABLE_CAN_CAN_INTERRUPT_CONTROL to remove the CAN interrupt disabling"
#endif

# if defined( C_ENABLE_CAN_TX_CONF_MSG_ACCESS ) && defined( C_ENABLE_ECU_SWITCH_PASS )
# error "Access to transmitted message is not supported in combination with passiv mode"
#endif

/* *********************************************************************** */
/*  Functions                                                              */
/* *********************************************************************** */

# if defined( C_ENABLE_MEMCOPY_SUPPORT )
/* **************************************************************************
| NAME:             CanCopyFromCan
| CALLED BY:        Application
| PRECONDITIONS:    none
|
| INPUT PARAMETERS: void *             dst        | pointer to destionation buffer
|                   CanChipDataPtr     src        | pointer to CAN buffer
|                   vuint8             len        | number of bytes to copy
|
| RETURN VALUES:    -
|
| DESCRIPTION:      copy data from CAN receive buffer to RAM.
|
| ATTENTION:        
************************************************************************** */
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanCopyFromCan(V_DEF_P2VAR_PARA(V_NONE, void, AUTOMATIC, APPL_VAR) dst, CanChipDataPtr src, vuint8 len) /* PRQA S 3673 */ /* MD_Can_3673 */
{
  vuint8 canllidx;
  for(canllidx=0; canllidx<len; canllidx++)
  {
    ((V_DEF_P2VAR_PARA(V_NONE, vuint8, AUTOMATIC, APPL_VAR))dst)[canllidx] = src[canllidx];
  }
}
/* CODE CATEGORY 1 END */

/* **************************************************************************
| NAME:             CanCopyToCan
| CALLED BY:        Application
| PRECONDITIONS:    none
|
| INPUT PARAMETERS: void *             src        | pointer to source buffer
|                   CanChipDataPtr     dst        | pointer to CAN buffer
|                   vuint8             len        | number of bytes to copy
|
| RETURN VALUES:    -
|
| DESCRIPTION:      copy data from CAN receive buffer to RAM.
|
| ATTENTION:        
************************************************************************** */
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanCopyToCan(CanChipDataPtr dst, V_DEF_P2VAR_PARA(V_NONE, void, AUTOMATIC, APPL_VAR) src, vuint8 len) C_API_3 /* PRQA S 3673 */ /* MD_Can_3673 */
{
  vuint8 canllidx;
  for(canllidx=0; canllidx<len; canllidx++)
  {
    dst[canllidx] = ((V_DEF_P2VAR_PARA(V_NONE, vuint8, AUTOMATIC, APPL_VAR))src)[canllidx];
  }
}
/* CODE CATEGORY 1 END */
# endif

# if defined ( C_ENABLE_DRIVER_STATUS )
/* **********************************************************************
| NAME:             CanGetDriverStatus
| CALLED BY:        Application
| PRECONDITIONS:    none  
| INPUT PARAMETER:  CanChannelHandle   channel    | 
| RETURN VALUE:     kCanDriverBusoff:     CAN Driver is in state Busoff, 
|                                         Init mode is not reached yet.
|                   kCanDriverBusoffInit: Initmode is reached, CanResetBusoffEnd
|                                         can be processed without delay on entry. 
|                   kCanDriverNormal:     Initmode is already left. CanResetBusoffEnd
|                                         can be processed without delay on entry 
|                                         (if not already performed). 
|
| DESCRIPTION:      The API function provide the current state of the 
|                   bus off recovery. This allows to call CanResetBusOffEnd
|                   more early to be able to receive messages as soon 
|                   as possible after Busoff.
*********************************************************************** */
/* CODE CATEGORY 4 START */
V_DEF_FUNC_API(V_NONE, vuint8, CODE) CanGetDriverStatus(CAN_CHANNEL_CANTYPE_ONLY)
{
  vuint8 retVal;

  if(CanLL_HwIsBusOff(CAN_CHANNEL_CANPARA_ONLY))
  {
    /* the channel is BusOff */
    retVal = kCanDriverBusoff;
  }
  else if(CanLL_HwIsStop(CAN_CHANNEL_CANPARA_ONLY))
  {
    /* BusOff recovery has finished and the channel has transitioned to halt mode */
    retVal = kCanDriverBusoffInit;
  }
  else
  {
    retVal = kCanDriverNormal;
  }

#  if defined(V_ENABLE_USE_DUMMY_STATEMENT)
#   if defined(C_MULTIPLE_RECEIVE_CHANNEL) 
  channel = channel; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
#   endif
#  endif

  return(retVal);
}
/* CODE CATEGORY 4 END */
# endif /* C_ENABLE_DRIVER_STATUS */

#if defined( C_ENABLE_LL_WAKEUP_SUPPORT )
/* **************************************************************************
| NAME:             CanLL_WakeUpHandling
| CALLED BY:        CanWakeUpTask() and WakeUp-ISR
| PRECONDITIONS:    none
|
| INPUT PARAMETERS: CanChannelHandle  channel        | current CAN channel
|                   and parameters which are defined in CanLL_WakeUpTaskLocalParameter
|
| RETURN VALUES:    -
|
| DESCRIPTION:      perform wakeup handling.
|
| ATTENTION:        CanLL_WakeUpHandling has to contain:
|                     ApplCanPreWakeUp(CAN_CHANNEL_CANPARA_ONLY);
|                     CanWakeUp(CAN_CHANNEL_CANPARA_ONLY); / CAN_WAKEUP()  - if hardware does not wake up automatically
|                     APPL_CAN_WAKEUP( channel );
|                   In case of CommonCAN, it might be necessary to call CanWakeUp() / CAN_WAKEUP() even if the hardware
|                   wakes up automatically to make sure all associated HW channels are awaken.
************************************************************************** */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_WakeUpHandling(CAN_CHANNEL_CANTYPE_ONLY)
{
# if defined( C_ENABLE_APPLCANPREWAKEUP_FCT )
  ApplCanPreWakeUp(CAN_CHANNEL_CANPARA_ONLY);
# endif
  CAN_WAKEUP( channel ); /* PRQA S 0277 */ /* MD_Can_0277_negation */
  APPL_CAN_WAKEUP( channel );
}
/* CODE CATEGORY 4 END */
#endif /* C_ENABLE_LL_WAKEUP_SUPPORT */

#if defined(C_ENABLE_CAN_RAM_CHECK)
/* **************************************************************************
| NAME:             CanLL_IsMailboxCorrupt
| CALLED BY:        Hll: CanInit()
| CALLED BY:        Asr: Can_InitController()
| PRECONDITIONS:    none
|
| INPUT PARAMETERS: CanChannelHandle  canHwChannel   | current HW CAN channel
|                   CanObjectHandle   hwObjHandle    | Handle to hardware object
|
| RETURN VALUES:    kCanTrue:  Mailbox is corrupt
|                   kCanFalse: Mailbox is not corrupt  
|
| DESCRIPTION:      performs RAM check for the mailbox at index hwObjHandle
************************************************************************** */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_IsMailboxCorrupt(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle hwObjHandle)
{
  vuint8 idx;
  vuint8 canMailboxCheckFailed;

  /* assume the mailbox is not corrupt */
  canMailboxCheckFailed = kCanFalse;

# if defined(C_ENABLE_CAN_HW_RAM_CHECK)
  /* as C_ENABLE_CAN_HW_RAM_CHECK also checks the mailboxes omit the check here when coming from poweron */
  if ((canStatus[canHwChannel] & kCanHwIsInit) == 0)
  {
    return(canMailboxCheckFailed);
  }
# endif

  /* iterate test patterns */
  for(idx=0; idx<3; idx++)
  {
    /* CiTBpA,CiTBpB,CiTBpC,CiTBpD/TMIDp,TMPTRp,TMDF0p,TMDF1p - omit label data */
    mBufId(hwObjHandleAdjusted)        =  CanMemCheckValues32bit[idx];
    mBufDlc(hwObjHandleAdjusted)       = (CanMemCheckValues32bit[idx] & kCanDlcMask);
    mBufiData(hwObjHandleAdjusted,0)   =  CanMemCheckValues32bit[idx];
    mBufiData(hwObjHandleAdjusted,1)   =  CanMemCheckValues32bit[idx];
    if( (mBufId(hwObjHandleAdjusted)      !=  CanMemCheckValues32bit[idx]                ) ||
        (mBufDlc(hwObjHandleAdjusted)     != (CanMemCheckValues32bit[idx] & kCanDlcMask) ) ||
        (mBufiData(hwObjHandleAdjusted,0) !=  CanMemCheckValues32bit[idx]                ) ||
        (mBufiData(hwObjHandleAdjusted,1) !=  CanMemCheckValues32bit[idx]                )
      )
    {
      canMailboxCheckFailed = kCanTrue; /* the mailbox is corrupt */
    }
  } /* iterate test patterns */

# if defined(V_ENABLE_USE_DUMMY_STATEMENT)
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) 
#   if !defined(C_ENABLE_CAN_HW_RAM_CHECK) 
  canHwChannel = canHwChannel;  /* PRQA S 3199 */ /* MD_Can_3199_dummy */
#   endif
#  endif
# endif

  return(canMailboxCheckFailed);
}
/* CODE CATEGORY 4 END */
#endif /* C_ENABLE_CAN_RAM_CHECK */

#if defined(C_ENABLE_CAN_HW_RAM_CHECK)
/* **************************************************************************
| NAME:             CanLL_IsHwRamCorrupt
| CALLED BY:        Hll: CanInitPowerOn()
| CALLED BY:        Asr: Can_Init()
| PRECONDITIONS:    RSCAN has to be in global reset mode
|
| INPUT PARAMETERS: none
|
| RETURN VALUES:    kCanTrue:  HwRam is corrupt
|                   kCanFalse: HwRam is not corrupt  
|
| DESCRIPTION:      performs internal RSCAN RAM test
************************************************************************** */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_IsHwRamCorrupt(void)
{
  tCanHwRamCheckPtr canHwRamCheckPtr;
  kCanRegSize canHwRamCheckFailed;
# if (kCanHwRamCheckPageMax != 0)
  vuint8 canHwRamCheckPage;
# endif
  vuint8 canHwRamCheckBlock;
  vuint8 idx;
# if defined(C_ENABLE_HW_LOOP_TIMER) && defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CAN_CHANNEL_CANTYPE_LOCAL
  channel = 0;
# endif

  /* assume the RAM is not corrupt */
  canHwRamCheckFailed = kCanZero;

  /* transit to global test mode */
  CanLL_GlobalModeReq(kCanTestMode);
  if (!CanLL_GlobalModeCheck(kCanTestMode))
  {
    if (!CanLL_GlobalModeCheck(kCanTestMode))
    {
      CanLL_CanTimerWait(kCanLoopInit,!CanLL_GlobalModeCheck(kCanTestMode)); /* PRQA S 3415 */ /* MD_Can_3415_LL */
    }
  }

  /* release the protection and enable the RAM test */
  Can->CGTPUR = kCanProtectionUnlockData1;
  Can->CGTPUR = kCanProtectionUnlockData2;
  Can->CGTCR = kCanHwRamTestEnable;
  if ((Can->CGTCR & kCanHwRamTestEnable) != kCanHwRamTestEnable)
  {
    if ((Can->CGTCR & kCanHwRamTestEnable) != kCanHwRamTestEnable)
    {
      CanLL_CanTimerWait(kCanLoopInit,(Can->CGTCR & kCanHwRamTestEnable) != kCanHwRamTestEnable); /* PRQA S 3415 */ /* MD_Can_3415_LL */
    }
  }
  
  /* perform the RAM test */
# if (kCanHwRamCheckPageMax != 0)
  for(canHwRamCheckPage=0; canHwRamCheckPage<=kCanHwRamCheckPageMax; canHwRamCheckPage++)
  {
    Can->CGTCFG = ((kCanRegSize) canHwRamCheckPage) << 16;
# else
    Can->CGTCFG = kCanZero;
# endif

    for(idx=0; idx<3; idx++)
    {
# if (kCanHwRamCheckPageMax != 0)
#  if (kCanHwRamCheckBlockMax != 0)
      if(canHwRamCheckPage == kCanHwRamCheckPageMax)
      {
        canHwRamCheckBlock = kCanHwRamCheckBlockMax;
      } 
      else
#  endif
      {
        canHwRamCheckBlock = kCanHwRamCheckBlocksPerPage;
      }
# else
#  if (kCanHwRamCheckBlockMax != 0)
      canHwRamCheckBlock = kCanHwRamCheckBlockMax;
#  else
      canHwRamCheckBlock = kCanHwRamCheckBlocksPerPage;
#  endif
# endif
      canHwRamCheckPtr = (tCanHwRamCheckPtr)&mCRAMTR(0); /* PRQA S 0310 */ /* MD_Can_0310 */

      do {
        canHwRamCheckPtr[0] = CanMemCheckValuesRegSize[idx];
        canHwRamCheckPtr[1] = CanMemCheckValuesRegSize[idx];
        canHwRamCheckPtr[2] = CanMemCheckValuesRegSize[idx];
        canHwRamCheckPtr[3] = CanMemCheckValuesRegSize[idx];
        canHwRamCheckFailed |= (canHwRamCheckPtr[0] - CanMemCheckValuesRegSize[idx]);
        canHwRamCheckFailed |= (canHwRamCheckPtr[1] - CanMemCheckValuesRegSize[idx]);
        canHwRamCheckFailed |= (canHwRamCheckPtr[2] - CanMemCheckValuesRegSize[idx]);
        canHwRamCheckFailed |= (canHwRamCheckPtr[3] - CanMemCheckValuesRegSize[idx]);
        canHwRamCheckPtr[4] = CanMemCheckValuesRegSize[idx];
        canHwRamCheckPtr[5] = CanMemCheckValuesRegSize[idx];
        canHwRamCheckPtr[6] = CanMemCheckValuesRegSize[idx];
        canHwRamCheckPtr[7] = CanMemCheckValuesRegSize[idx];
        canHwRamCheckFailed |= (canHwRamCheckPtr[4] - CanMemCheckValuesRegSize[idx]);
        canHwRamCheckFailed |= (canHwRamCheckPtr[5] - CanMemCheckValuesRegSize[idx]);
        canHwRamCheckFailed |= (canHwRamCheckPtr[6] - CanMemCheckValuesRegSize[idx]);
        canHwRamCheckFailed |= (canHwRamCheckPtr[7] - CanMemCheckValuesRegSize[idx]);
        canHwRamCheckPtr += 8;
        canHwRamCheckBlock--;
      } while(canHwRamCheckBlock > 0); /* iterate blocks */
    } /* iterate test patterns */

# if (kCanHwRamCheckPageMax != 0)
    /* skip further pages if check already failed */
    if (canHwRamCheckFailed != kCanZero)
    {
      break;
    }
  } /* iterate pages */
# endif

  /* disable the RAM test and transit to global reset mode */
  Can->CGTCR = kCanHwRamTestDisable;
  CanLL_GlobalModeReq(kCanResetMode);
  if (!CanLL_GlobalModeCheck(kCanResetMode))
  {
    if (!CanLL_GlobalModeCheck(kCanResetMode))
    {
      CanLL_CanTimerWait(kCanLoopInit,!CanLL_GlobalModeCheck(kCanResetMode)); /* PRQA S 3415 */ /* MD_Can_3415_LL */
    }
  }

  /* return kCanTrue if corrupt RAM was found */
  if(canHwRamCheckFailed != kCanZero)
  {
    return(kCanTrue);
  }
  else
  {
    return(kCanFalse);
  }
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* CODE CATEGORY 4 END */
#endif /* C_ENABLE_CAN_HW_RAM_CHECK */

#if defined(C_ENABLE_CANLL_GEN_CHECK)
#  include "can_par.h"
# define bufmskdim   ((kCanMaxHwObjects+31)>>5)
# define rulesmskdim ((kCanMaxRules+31)>>5)
/* **************************************************************************
| NAME:             CanLL_CheckGeneratedData()
| CALLED BY:        Hll: CanInitPowerOn()
| CALLED BY:        Asr: Can_Init()
| PRECONDITIONS:    none
|
| INPUT PARAMETERS: none
|
| RETURN VALUES:    none
|
| DESCRIPTION:      checks the HW specific generated data against base
|                   data and performs additional plausibility checks,
|                   issues an assertGenLL() when an error is detected
************************************************************************** */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_CheckGeneratedData(void)
{
  CanObjectHandle hwObjHandle, hwObjHandleInt;
  CAN_CHANNEL_CANTYPE_LOCAL
# if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel;
# endif
  vuint8 identity, tmpmsk8, tmpmsk8ref, physchmsk;
  vuint16 idx, poolbufcnt, rulescnt, rxbccnt, rxfccnt, cnt, cntref, tmpmsk16;
  vuint32 tmpmsk32[kCanNumberOfSharedReg16];
  vuint32 bufmsk[bufmskdim], rulesmsk[rulesmskdim];
#  if (kCanNumberOfTxObjects > 0)
  CanTransmitHandle hwhandle;
  CanObjectHandle logHwObjHandle;
#  endif
  vuint8 fifobufcnt[] = {0,4,8,16,32,48,64,128};

  /* CanObjectHandle has to be 16bit for GenCheck (because entire layout is checked) */
  assertGenLL(sizeof(CanObjectHandle) > 1, kCanChannelNotUsed, kErrorGenCheck);

  identity = 0;
  identity = identity;
  {
    physchmsk = 0;
    for(idx=0;idx<bufmskdim;idx++)
    {
      bufmsk[idx] = 0;
    }
    for(idx=0;idx<rulesmskdim;idx++)
    {
      rulesmsk[idx] = 0;
    }
    rxbccnt = 0;
    rxfccnt = 0;
    poolbufcnt = 0;
    rulescnt = 0;

# if defined(C_MULTIPLE_RECEIVE_CHANNEL)
    /* iterate logical channels */
    for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
    {
      {
# if defined(CAN_ENABLE_SELECTABLE_PB)
        canControllerConfigPtr[channel] = &CAN_CONTROLLER_CONFIG_INIT[channel];
# endif
# if defined(C_MULTIPLE_PHYS_CHANNEL)
        canPhysChannel = mCanLogToPhys(channel);
# endif

        /* physical channel and others */
        assertGenLL(canPhysChannel < kCanMaxPhysChannels, channel, kErrorGenCheck);
        assertGenLL((physchmsk & CanLL_SL8(canPhysChannel)) == kCanZero, channel, kErrorGenCheck);
        physchmsk |= CanLL_SL8(canPhysChannel);
# if defined(V_CPU_RH850)
#  if defined(C_ENABLE_LL_CAN_INTCTRL)
        assertGenLL(CanChannelData[channel].CanIntcChTxBaseAdr != kCanZero, channel, kErrorGenCheck);
        assertGenLL(CanChannelData[channel].CanIntcChErrorBaseAdr != kCanZero, channel, kErrorGenCheck);
#  endif
#  if defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL) || (defined(C_ENABLE_LL_WAKEUP_SUPPORT) && defined(C_ENABLE_WAKEUP_POLLING))
        assertGenLL(CanChannelData[channel].CanIntcChWakeupBaseAdr != kCanZero, channel, kErrorGenCheck);
#  endif
# endif

        /* Rx FullCAN objects */
        cnt = 0;
        for(idx=0;idx<kCanNumberOfSharedReg16;idx++)
        {
          tmpmsk32[idx] = 0;
        }

        for (hwObjHandle=CAN_HL_HW_RX_FULL_STARTINDEX(channel); hwObjHandle<CAN_HL_HW_RX_FULL_STOPINDEX(channel); hwObjHandle++ )
        {
          tmpmsk32[CanLL_BitIndex(hwObjHandle-kCanRxBufOffset)] |= CanLL_SL32(CanLL_BitPosition(hwObjHandle-kCanRxBufOffset));
# if defined(C_ENABLE_INDIVIDUAL_POLLING)
          /* check whether all FullCAN objects are configured to polling */
          assertGenLL(CanHwObjIndivPolling[identity][hwObjHandle] != kCanZero, channel, kErrorGenCheck);
# endif
          assertGenLL((bufmsk[CanLL_BitIndex16(hwObjHandle)] & CanLL_SL32(CanLL_BitPosition(hwObjHandle))) == kCanZero, channel, kErrorGenCheck);
          bufmsk[CanLL_BitIndex16(hwObjHandle)] |= CanLL_SL32(CanLL_BitPosition(hwObjHandle));
          cnt++;
        }

        assertGenLL(cnt == CanRxFcCount(channel), channel, kErrorGenCheck);
        for(idx=0;idx<kCanNumberOfSharedReg16;idx++)
        {
          assertGenLL(tmpmsk32[idx] == CanChannelData[channel].CanRxFcMask[idx], channel, kErrorGenCheck);
        }
        rxfccnt += cnt;
        poolbufcnt += cnt;
        if (cnt != 0)
        {
# if (kCanRxBufOffset != 0)
          assertGenLL(CAN_HL_HW_RX_FULL_STARTINDEX(channel) >= kCanRxBufOffset, channel, kErrorGenCheck);
# endif
          assertGenLL(CAN_HL_HW_RX_FULL_STOPINDEX(channel) >= CAN_HL_HW_RX_FULL_STARTINDEX(channel), channel, kErrorGenCheck);
          assertGenLL(CAN_HL_HW_RX_FULL_STOPINDEX(channel) <= kCanRxFifoOffset, channel, kErrorGenCheck);
          assertGenLL(CAN_HL_HW_RX_FULL_STOPINDEX(channel) <= ((kCanNumberOfSharedReg16*32)+kCanRxBufOffset), channel, kErrorGenCheck);
        }

        /* Rx BasicCAN objects */
        cnt = 0;
        cntref = 0;
        tmpmsk8 = 0;
        tmpmsk8ref = 0;

        for (hwObjHandle=CAN_HL_HW_RX_BASIC_STARTINDEX(channel); hwObjHandle<CAN_HL_HW_RX_BASIC_STOPINDEX(channel); hwObjHandle++ )
        {
          tmpmsk8ref |= CanLL_SL8(hwObjHandle-kCanRxFifoOffset);
          assertGenLL((bufmsk[CanLL_BitIndex16(hwObjHandle)] & CanLL_SL32(CanLL_BitPosition(hwObjHandle))) == kCanZero, channel, kErrorGenCheck);
          bufmsk[CanLL_BitIndex16(hwObjHandle)] |= CanLL_SL32(CanLL_BitPosition(hwObjHandle));
          cntref++;
        }
        for (hwObjHandleInt=CanChannelData[channel].CanRxBcStartIndex; hwObjHandleInt<CanChannelData[channel].CanRxBcStopIndex; hwObjHandleInt++ )
        {
          tmpmsk8 |= CanLL_SL8(hwObjHandleInt);
          poolbufcnt += fifobufcnt[CanChannelData[channel].CanRxFifoDepth[cnt]];
#  if ((defined(V_CPU_RH850) && defined(C_MULTIPLE_RECEIVE_CHANNEL)))
          assertGenLL(CanFifoToLogChannel[identity][hwObjHandleInt] == channel, channel, kErrorGenCheck);
#  endif
          cnt++;
        }

        assertGenLL(cnt == cntref, channel, kErrorGenCheck);
        assertGenLL(tmpmsk8 == tmpmsk8ref, channel, kErrorGenCheck);
        assertGenLL(tmpmsk8 == CanChannelData[channel].CanRxBcMask, channel, kErrorGenCheck);
        rxbccnt += cnt;
        if (cnt != 0)
        {
          assertGenLL(CAN_HL_HW_RX_BASIC_STARTINDEX(channel) >= kCanRxFifoOffset, channel, kErrorGenCheck);
          assertGenLL(CAN_HL_HW_RX_BASIC_STOPINDEX(channel) >= CAN_HL_HW_RX_BASIC_STARTINDEX(channel), channel, kErrorGenCheck);
          assertGenLL(CAN_HL_HW_RX_BASIC_STOPINDEX(channel) <= kCanTxBufOffset_0, channel, kErrorGenCheck);
        }
        assertGenLL(CanChannelData[channel].CanRxBcMsgProcessCount > 1, channel, kErrorGenCheck);

        /* receive rules */
#  define kRxBcFilterCnt (CanChannelData[channel].CanFilterRulesBcCount*cnt)
        assertGenLL((kRxBcFilterCnt + CanRxFcCount(channel)) == CanChannelData[channel].CanFilterRulesTotalCount, channel, kErrorGenCheck);
        assertGenLL(CanChannelData[channel].CanFilterRulesTotalCount <= 128, channel, kErrorGenCheck);
        for (idx=CanChannelData[channel].CanFilterRulesStartIndex; idx<(CanChannelData[channel].CanFilterRulesStartIndex+CanChannelData[channel].CanFilterRulesTotalCount); idx++ )
        {
          assertGenLL(idx<(kCanMaxPhysChannels<<6), channel, kErrorGenCheck);
          assertGenLL((rulesmsk[CanLL_BitIndex16(idx)] & CanLL_SL32(CanLL_BitPosition(idx))) == kCanZero, channel, kErrorGenCheck);
          rulesmsk[CanLL_BitIndex16(idx)] |= CanLL_SL32(CanLL_BitPosition(idx));
        }
        rulescnt += CanChannelData[channel].CanFilterRulesTotalCount;

        if(kRxBcFilterCnt > 0)
        {
# if defined(C_ENABLE_EXTENDED_ID)
          assertGenLL(sizeof(CanChannelData[channel].CanFilterRulesBc[0]) == 8, channel, kErrorGenCheck);
          assertGenLL(CanChannelData[channel].CanFilterRulesBc[0].Mask >= 0x80000000, channel, kErrorGenCheck);
# else
          assertGenLL(sizeof(CanChannelData[channel].CanFilterRulesBc[0]) == 4, channel, kErrorGenCheck);
# endif
#  if (kCanNumberOfChannels > 1)
          if(channel == 1)
          {
            assertGenLL((sizeof(CanFilterRulesBc_1) / sizeof(CanFilterRulesBc_1[0])) == kRxBcFilterCnt, channel, kErrorGenCheck);
          }
          else if(channel == 0)
#  endif
          {
            assertGenLL((sizeof(CanFilterRulesBc_0) / sizeof(CanFilterRulesBc_0[0])) == kRxBcFilterCnt, channel, kErrorGenCheck);
          }
        }

        /* Tx objects */
        assertGenLL(CAN_HL_HW_TX_STARTINDEX(channel) >= kCanTxBufOffset_0, channel, kErrorGenCheck);
        assertGenLL(CAN_HL_HW_TX_STARTINDEX(channel) == mCanTxBufOffset(channel), channel, kErrorGenCheck);
        assertGenLL(CAN_HL_HW_TX_STOPINDEX(channel) >= CAN_HL_HW_TX_STARTINDEX(channel), channel, kErrorGenCheck);
        assertGenLL(CAN_HL_HW_TX_STOPINDEX(channel) <= kCanMaxHwObjects, channel, kErrorGenCheck);
        assertGenLL(CAN_HL_HW_TX_STOPINDEX(channel) <= (mCanTxBufOffset(channel)+kCanMaxTxBuf), channel, kErrorGenCheck);

        tmpmsk16 = 0;
        for (hwObjHandle=CAN_HL_HW_TX_STARTINDEX(channel); hwObjHandle<CAN_HL_HW_TX_STOPINDEX(channel); hwObjHandle++ )
        {
          assertGenLL((bufmsk[CanLL_BitIndex16(hwObjHandle)] & CanLL_SL32(CanLL_BitPosition(hwObjHandle))) == kCanZero, channel, kErrorGenCheck);
          bufmsk[CanLL_BitIndex16(hwObjHandle)] |= CanLL_SL32(CanLL_BitPosition(hwObjHandle));
# if defined(C_ENABLE_INDIVIDUAL_POLLING)
          if (CanHwObjIndivPolling[identity][hwObjHandle] == kCanZero)
          {
            tmpmsk16 |= CanLL_SL16(hwObjHandle-mCanTxBufOffset(channel));
          }
# elif !defined(C_ENABLE_TX_POLLING)
          tmpmsk16 |= CanLL_SL16(hwObjHandle-mCanTxBufOffset(channel));
# endif
        }
        assertGenLL(tmpmsk16 == CanChannelData[channel].CanTxIntMask, channel, kErrorGenCheck);
      } /* if channel is active in identity */
    } /* channel loop */

#  if (kCanNumberOfTxObjects > 0)
    for(hwhandle=0;hwhandle<kCanNumberOfTxObjects;hwhandle++)
    {
#   if defined(C_MULTIPLE_RECEIVE_CHANNEL)
      channel = CanGetChannelOfTxObj(hwhandle);
#   endif
#   if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
      hwObjHandle = CanGetTxHwObj(hwhandle);
#   else
      hwObjHandle = CAN_HL_HW_TX_NORMAL_INDEX(channel);
#   endif
      assertGenLL(channel<kCanNumberOfChannels, channel, kErrorGenCheck);
      assertGenLL(hwObjHandle>=CAN_HL_HW_TX_STARTINDEX(channel), channel, kErrorGenCheck);
      assertGenLL(hwObjHandle<CAN_HL_HW_TX_STOPINDEX(channel), channel, kErrorGenCheck);
      logHwObjHandle = (CanObjectHandle)((vsintx)hwObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(channel));
#   if defined(C_MULTIPLE_RECEIVE_CHANNEL)
      assertGenLL(logHwObjHandle>=CAN_HL_LOG_HW_TX_STARTINDEX(channel), channel, kErrorGenCheck);
#   endif
      assertGenLL(logHwObjHandle<CAN_HL_LOG_HW_TX_STOPINDEX(channel), channel, kErrorGenCheck);
    }
#  endif
    assertGenLL(CAN_HL_HW_TX_NORMAL_INDEX(channel)==CAN_HL_HW_TX_STARTINDEX(channel), channel, kErrorGenCheck);
#  if defined(C_ENABLE_MSG_TRANSMIT)
    assertGenLL(CAN_HL_HW_MSG_TRANSMIT_INDEX(channel)==(CAN_HL_HW_TX_STARTINDEX(channel)+1), channel, kErrorGenCheck);
#  endif
    assertGenLL(channel==(kCanNumberOfChannels-1), kCanChannelNotUsed, kErrorGenCheck);

    assertGenLL(rxbccnt <= kCanMaxRxFifos, kCanChannelNotUsed, kErrorGenCheck);
    assertGenLL(rxfccnt <= kCanMaxRxBuf, kCanChannelNotUsed, kErrorGenCheck);
    assertGenLL(poolbufcnt <= kCanMaxPoolBuf, kCanChannelNotUsed, kErrorGenCheck);
    assertGenLL(rulescnt <= kCanMaxRules, kCanChannelNotUsed, kErrorGenCheck);

    for(hwObjHandle=0;hwObjHandle<kCanMaxHwObjects;hwObjHandle++)
    {
      if(
#  if (kCanRxBufOffset != 0)
         (hwObjHandle>=kCanRxBufOffset) &&
#  endif
         (hwObjHandle<(kCanRxBufOffset+rxfccnt))
        )
      {
        /* check whether Rx FullCAN objects start at the first Rx buffer and are continuous */
        assertGenLL((bufmsk[CanLL_BitIndex16(hwObjHandle)] & CanLL_SL32(CanLL_BitPosition(hwObjHandle))) != 0, kCanChannelNotUsed, kErrorGenCheck)
      }
      else if((hwObjHandle>=kCanRxFifoOffset) && (hwObjHandle<(kCanRxFifoOffset+rxbccnt)))
      {
        /* check whether Rx BasicCAN objects start at the first Rx fifo and are continuous */
        assertGenLL((bufmsk[CanLL_BitIndex16(hwObjHandle)] & CanLL_SL32(CanLL_BitPosition(hwObjHandle))) != 0, kCanChannelNotUsed, kErrorGenCheck)
      }
      else if(hwObjHandle<kCanTxBufOffset_0)
      {
        /* check whether other objects in Rx and common fifo areas are not used */
        assertGenLL((bufmsk[CanLL_BitIndex16(hwObjHandle)] & CanLL_SL32(CanLL_BitPosition(hwObjHandle))) == 0, kCanChannelNotUsed, kErrorGenCheck)
      }

#  if defined(C_ENABLE_INDIVIDUAL_POLLING)
      if((bufmsk[CanLL_BitIndex16(hwObjHandle)] & CanLL_SL32(CanLL_BitPosition(hwObjHandle))) == 0)
      {
        /* check whether unused objects have no polling entries in individual polling table */
        assertGenLL(CanHwObjIndivPolling[identity][hwObjHandle] == kCanZero, kCanChannelNotUsed, kErrorGenCheck);
      }
#  endif
    }

    for(idx=0;idx<kCanMaxRules;idx++)
    {
      if(idx<rulescnt)
      {
        /* check whether rules start at the beginning and are continuous */
        assertGenLL((rulesmsk[CanLL_BitIndex16(idx)] & CanLL_SL32(CanLL_BitPosition(idx))) != 0, kCanChannelNotUsed, kErrorGenCheck)
      }
      else
      {
        /* check whether no further entries exist */
        assertGenLL((rulesmsk[CanLL_BitIndex16(idx)] & CanLL_SL32(CanLL_BitPosition(idx))) == 0, kCanChannelNotUsed, kErrorGenCheck)
      }
    }
  } /* identity loop */
}
/* CODE CATEGORY 4 END */

/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanLL_CheckGeneratedDataError(void)
{
  volatile vuint8 loopvar;
  CanGlobalInterruptDisable();
  loopvar = 0;
  while (loopvar == 0)
  {
    loopvar = loopvar;
  }
}
/* CODE CATEGORY 4 END */
#endif /* C_ENABLE_CANLL_GEN_CHECK */

#if ((defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING )) || \
     (defined( C_ENABLE_RX_FULLCAN_OBJECTS )  && !defined( C_ENABLE_RX_FULLCAN_POLLING  )) || \
     !defined( C_ENABLE_TX_POLLING )         || \
      defined( C_ENABLE_INDIVIDUAL_POLLING ) || \
     !defined( C_ENABLE_ERROR_POLLING )      || \
     !defined( C_ENABLE_LL_WAKEUP_POLLING ))        /* ISR necessary; no pure polling configuration */
/* CODE CATEGORY 1 START */

# if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
#  if defined(C_ENABLE_RX_BASICCAN_POLLING )  && !defined(C_ENABLE_INDIVIDUAL_POLLING)
#  else
/****************************************************************************
| NAME:             CanInterruptRxFifo
| CALLED BY:        CanIsrRxFifo
| PRECONDITIONS:  
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Receive interrupt service function
****************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanInterruptRxFifo(void)
{
  CAN_HW_CHANNEL_CANTYPE_LOCAL
  vuint8 canFifoNum;
  vuint8 localReg;
  vuint8 canCount;
  CanLL_RtmStart(CanInterruptRxFifo);
  CanLL_EI();

  /* work with local copy - any flags set during processing will be handled by interrupt immediately afterwards */
  localReg = (vuint8)(Can->CFESR & kCanRxFifoMask);
  if (localReg != kCanRxFifoMask)
  {
    /* process all RF (all channels) */
    canFifoNum = 0;
    do
    {
      if ((localReg & CanLL_SL8(canFifoNum)) == 0)
      {
#     if defined(C_ENABLE_INDIVIDUAL_POLLING)
        /* additional check is necessary to ensure only objects configured for interrupt are processed here */
        if (CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][canFifoNum+kCanRxFifoOffset] == 0)
#     endif
        {
#     if defined(C_MULTIPLE_RECEIVE_CHANNEL)
          canHwChannel = CanFifoToLogChannel[0][canFifoNum];
#     endif
          canCount = CanChannelData[canHwChannel].CanRxBcMsgProcessCount;
          /* process messages till fifo is empty or configured limit is reached */
          do
          {
            canCount--;
            /* interrupt flag is deleted within CanBasicCanMsgReceived() */
            CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST (CanObjectHandle)(canFifoNum+kCanRxFifoOffset));
          } while(((Can->CRFSR[canFifoNum] & kCanSrFifoEmpty) == 0) && (canCount > 0));
        }
        localReg |= CanLL_SL8(canFifoNum); /* set bit */
      }
      canFifoNum++;
    }  while (localReg != kCanOne8);
  }

  CanLL_DI();
  CanLL_RtmStop(CanInterruptRxFifo);
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#  endif /* C_ENABLE_RX_BASICCAN_POLLING */
# endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
/****************************************************************************
| NAME:             CanInterruptTx
| CALLED BY:        CanIsrTx_x (tx complete)
| PRECONDITIONS:
| INPUT PARAMETERS: CanChannelHandle canHwChannel
| RETURN VALUES:    none
| DESCRIPTION:      Transmit interrupt service function
****************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanInterruptTx(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  vuint8 localObjHandle;
  vuint16 localReg;
#  if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel; 
  canPhysChannel = mCanLogToPhys(canHwChannel);
#  endif
  CanLL_RtmStart(CanInterruptTx);
  CanLL_EI();

    /* work with local copy - any flags set during processing will be handled by interrupt immediately afterwards */
    localReg = CanLL_SharedRegToWord(canPhysChannel,Can->CTBTCSR[CanLL_WordIndex(canPhysChannel)]) & CanChannelData[canHwChannel].CanTxIntMask;
#   if defined(C_ENABLE_CANCEL_IN_HW)
#    if defined(C_ENABLE_INDIVIDUAL_POLLING)
    localReg |= CanLL_SharedRegToWord(canPhysChannel,Can->CTBASR[CanLL_WordIndex(canPhysChannel)]);
#    else
    localReg |= CanLL_SharedRegToWord(canPhysChannel,Can->CTBASR[CanLL_WordIndex(canPhysChannel)]) & CanChannelData[canHwChannel].CanTxIntMask;
#    endif
#   endif

    if (localReg != 0)
    {
      /* jump directly to first nibble != 0 */
      if      ((localReg & 0x000F) != 0) { localObjHandle = 0u; }
      else if ((localReg & 0x00F0) != 0) { localObjHandle = 4u; }
      else if ((localReg & 0x0F00) != 0) { localObjHandle = 8u; }
      else                               { localObjHandle = 12u; }

      do
      {
        if ((localReg & CanLL_SL16(localObjHandle)) != 0)
        {
          CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST (CanObjectHandle)(localObjHandle+mCanTxBufOffset(canHwChannel)));
          localReg &= (localReg-1u); /* clear bit */
        }
        localObjHandle++;
      }  while (localReg != 0);
    }

  CanLL_DI();
  CanLL_RtmStop(CanInterruptTx);
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */
# endif /* C_ENABLE_TX_POLLING */

# if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
#  if defined(C_ENABLE_WAKEUP_POLLING)
#  else
/****************************************************************************
| NAME:             CanInterruptWakeup
| CALLED BY:        CanIsrWakeup_x
| PRECONDITIONS:
| INPUT PARAMETERS: CanChannelHandle canHwChannel
| RETURN VALUES:    none
| DESCRIPTION:      Wakeup interrupt service function
****************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanInterruptWakeup(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  CanLL_RtmStart(CanInterruptWakeup);
  CanLL_EI();

  CanLL_WakeUpHandling(CAN_HW_CHANNEL_CANPARA_ONLY);

  CanLL_DI();
  CanLL_RtmStop(CanInterruptWakeup);
}
#  endif /* C_ENABLE_WAKEUP_POLLING */
# endif

# if defined(C_ENABLE_ERROR_POLLING)
# else
/****************************************************************************
| NAME:             CanInterruptStatus
| CALLED BY:        CanIsrStatus_x
| PRECONDITIONS:
| INPUT PARAMETERS: CanChannelHandle canHwChannel
| RETURN VALUES:    none
| DESCRIPTION:      Status interrupt service function (-> busoffhandling)
****************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanInterruptStatus(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  CanLL_RtmStart(CanInterruptStatus);
  CanLL_EI();

  CanHL_ErrorHandling(CAN_HW_CHANNEL_CANPARA_ONLY);

  CanLL_DI();
  CanLL_RtmStop(CanInterruptStatus);
}

#  if defined(C_ENABLE_RX_BASICCAN_OBJECTS) 
/****************************************************************************
| NAME:             CanInterruptGlobalStatus
| CALLED BY:        CanIsrGlobalStatus
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Global status interrupt service function (-> Rx BasicCAN overrun)
****************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanInterruptGlobalStatus(void)
{
  CAN_HW_CHANNEL_CANTYPE_LOCAL
  CanLL_RtmStart(CanInterruptGlobalStatus);
  CanLL_EI();

#   if defined(C_MULTIPLE_RECEIVE_CHANNEL)
    for (canHwChannel=0; canHwChannel<kCanNumberOfChannels; canHwChannel++)
#   endif
    {
      {
        CanHL_ErrorHandling(CAN_HW_CHANNEL_CANPARA_ONLY);
      }
    }

  CanLL_DI();
  CanLL_RtmStop(CanInterruptGlobalStatus);
}
#  endif /* C_ENABLE_RX_BASICCAN_OBJECTS */
# endif /* C_ENABLE_ERROR_POLLING */

/* CODE CATEGORY 1 END */
#endif /* ISR necessary; no pure polling configuration */

#if ((defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING )) || \
     (defined( C_ENABLE_RX_FULLCAN_OBJECTS )  && !defined( C_ENABLE_RX_FULLCAN_POLLING  )) || \
     !defined( C_ENABLE_TX_POLLING )         || \
      defined( C_ENABLE_INDIVIDUAL_POLLING ) || \
     !defined( C_ENABLE_ERROR_POLLING )      || \
     !defined( C_ENABLE_LL_WAKEUP_POLLING ))        /* ISR necessary; no pure polling configuration */

/* **************************************************************************
| NAME:             CanIsrTx_0
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Transmit interrupt service function for CAN channel _0
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_0 )
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrTx_0Cat)
#    if (osdIsrCanIsrTx_0Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_0 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrTx_0Cat)
#    if (osdIsrCanIsrTx_0Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_0( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptTx(kCanPhysToLogChannelIndex_0);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptTx();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_0) */
/* CODE CATEGORY 1 END */

#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* **************************************************************************
| NAME:             CanIsrWakeup_0
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Wakeup interrupt service function for CAN channel _0
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_0 )
# if defined(C_ENABLE_WAKEUP_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrWakeup_0Cat)
#    if (osdIsrCanIsrWakeup_0Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_0 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrWakeup_0Cat)
#    if (osdIsrCanIsrWakeup_0Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_0( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptWakeup(kCanPhysToLogChannelIndex_0);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptWakeup();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_0) */
/* CODE CATEGORY 1 END */
#endif

/****************************************************************************
| NAME:             CanIsrStatus_0
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Status interrupt service function for CAN channel _0 (busoff)
****************************************************************************/
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_0 )
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrStatus_0Cat)
#    if (osdIsrCanIsrStatus_0Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_0 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrStatus_0Cat)
#    if (osdIsrCanIsrStatus_0Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_0( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptStatus(kCanPhysToLogChannelIndex_0);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptStatus();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_0) */
/* CODE CATEGORY 1 END */

/* **************************************************************************
| NAME:             CanIsrTx_1
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Transmit interrupt service function for CAN channel _1
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_1 )
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrTx_1Cat)
#    if (osdIsrCanIsrTx_1Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_1 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrTx_1Cat)
#    if (osdIsrCanIsrTx_1Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_1( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptTx(kCanPhysToLogChannelIndex_1);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptTx();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_1) */
/* CODE CATEGORY 1 END */

#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* **************************************************************************
| NAME:             CanIsrWakeup_1
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Wakeup interrupt service function for CAN channel _1
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_1 )
# if defined(C_ENABLE_WAKEUP_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrWakeup_1Cat)
#    if (osdIsrCanIsrWakeup_1Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_1 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrWakeup_1Cat)
#    if (osdIsrCanIsrWakeup_1Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_1( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptWakeup(kCanPhysToLogChannelIndex_1);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptWakeup();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_1) */
/* CODE CATEGORY 1 END */
#endif

/****************************************************************************
| NAME:             CanIsrStatus_1
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Status interrupt service function for CAN channel _1 (busoff)
****************************************************************************/
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_1 )
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrStatus_1Cat)
#    if (osdIsrCanIsrStatus_1Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_1 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrStatus_1Cat)
#    if (osdIsrCanIsrStatus_1Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_1( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptStatus(kCanPhysToLogChannelIndex_1);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptStatus();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_1) */
/* CODE CATEGORY 1 END */

/* **************************************************************************
| NAME:             CanIsrTx_2
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Transmit interrupt service function for CAN channel _2
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_2 )
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrTx_2Cat)
#    if (osdIsrCanIsrTx_2Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_2 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrTx_2Cat)
#    if (osdIsrCanIsrTx_2Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_2( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptTx(kCanPhysToLogChannelIndex_2);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptTx();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_2) */
/* CODE CATEGORY 1 END */

#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* **************************************************************************
| NAME:             CanIsrWakeup_2
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Wakeup interrupt service function for CAN channel _2
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_2 )
# if defined(C_ENABLE_WAKEUP_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrWakeup_2Cat)
#    if (osdIsrCanIsrWakeup_2Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_2 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrWakeup_2Cat)
#    if (osdIsrCanIsrWakeup_2Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_2( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptWakeup(kCanPhysToLogChannelIndex_2);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptWakeup();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_2) */
/* CODE CATEGORY 1 END */
#endif

/****************************************************************************
| NAME:             CanIsrStatus_2
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Status interrupt service function for CAN channel _2 (busoff)
****************************************************************************/
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_2 )
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrStatus_2Cat)
#    if (osdIsrCanIsrStatus_2Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_2 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrStatus_2Cat)
#    if (osdIsrCanIsrStatus_2Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_2( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptStatus(kCanPhysToLogChannelIndex_2);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptStatus();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_2) */
/* CODE CATEGORY 1 END */

/* **************************************************************************
| NAME:             CanIsrTx_3
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Transmit interrupt service function for CAN channel _3
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_3 )
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrTx_3Cat)
#    if (osdIsrCanIsrTx_3Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_3 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrTx_3Cat)
#    if (osdIsrCanIsrTx_3Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_3( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptTx(kCanPhysToLogChannelIndex_3);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptTx();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_3) */
/* CODE CATEGORY 1 END */

#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* **************************************************************************
| NAME:             CanIsrWakeup_3
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Wakeup interrupt service function for CAN channel _3
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_3 )
# if defined(C_ENABLE_WAKEUP_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrWakeup_3Cat)
#    if (osdIsrCanIsrWakeup_3Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_3 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrWakeup_3Cat)
#    if (osdIsrCanIsrWakeup_3Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_3( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptWakeup(kCanPhysToLogChannelIndex_3);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptWakeup();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_3) */
/* CODE CATEGORY 1 END */
#endif

/****************************************************************************
| NAME:             CanIsrStatus_3
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Status interrupt service function for CAN channel _3 (busoff)
****************************************************************************/
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_3 )
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrStatus_3Cat)
#    if (osdIsrCanIsrStatus_3Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_3 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrStatus_3Cat)
#    if (osdIsrCanIsrStatus_3Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_3( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptStatus(kCanPhysToLogChannelIndex_3);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptStatus();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_3) */
/* CODE CATEGORY 1 END */

/* **************************************************************************
| NAME:             CanIsrTx_4
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Transmit interrupt service function for CAN channel _4
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_4 )
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrTx_4Cat)
#    if (osdIsrCanIsrTx_4Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_4 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrTx_4Cat)
#    if (osdIsrCanIsrTx_4Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_4( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptTx(kCanPhysToLogChannelIndex_4);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptTx();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_4) */
/* CODE CATEGORY 1 END */

#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* **************************************************************************
| NAME:             CanIsrWakeup_4
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Wakeup interrupt service function for CAN channel _4
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_4 )
# if defined(C_ENABLE_WAKEUP_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrWakeup_4Cat)
#    if (osdIsrCanIsrWakeup_4Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_4 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrWakeup_4Cat)
#    if (osdIsrCanIsrWakeup_4Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_4( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptWakeup(kCanPhysToLogChannelIndex_4);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptWakeup();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_4) */
/* CODE CATEGORY 1 END */
#endif

/****************************************************************************
| NAME:             CanIsrStatus_4
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Status interrupt service function for CAN channel _4 (busoff)
****************************************************************************/
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_4 )
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrStatus_4Cat)
#    if (osdIsrCanIsrStatus_4Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_4 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrStatus_4Cat)
#    if (osdIsrCanIsrStatus_4Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_4( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptStatus(kCanPhysToLogChannelIndex_4);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptStatus();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_4) */
/* CODE CATEGORY 1 END */

/* **************************************************************************
| NAME:             CanIsrTx_5
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Transmit interrupt service function for CAN channel _5
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_5 )
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrTx_5Cat)
#    if (osdIsrCanIsrTx_5Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_5 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrTx_5Cat)
#    if (osdIsrCanIsrTx_5Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_5( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptTx(kCanPhysToLogChannelIndex_5);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptTx();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_5) */
/* CODE CATEGORY 1 END */

#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* **************************************************************************
| NAME:             CanIsrWakeup_5
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Wakeup interrupt service function for CAN channel _5
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_5 )
# if defined(C_ENABLE_WAKEUP_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrWakeup_5Cat)
#    if (osdIsrCanIsrWakeup_5Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_5 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrWakeup_5Cat)
#    if (osdIsrCanIsrWakeup_5Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_5( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptWakeup(kCanPhysToLogChannelIndex_5);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptWakeup();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_5) */
/* CODE CATEGORY 1 END */
#endif

/****************************************************************************
| NAME:             CanIsrStatus_5
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Status interrupt service function for CAN channel _5 (busoff)
****************************************************************************/
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_5 )
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrStatus_5Cat)
#    if (osdIsrCanIsrStatus_5Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_5 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrStatus_5Cat)
#    if (osdIsrCanIsrStatus_5Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_5( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptStatus(kCanPhysToLogChannelIndex_5);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptStatus();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_5) */
/* CODE CATEGORY 1 END */

/* **************************************************************************
| NAME:             CanIsrTx_6
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Transmit interrupt service function for CAN channel _6
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_6 )
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrTx_6Cat)
#    if (osdIsrCanIsrTx_6Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_6 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrTx_6Cat)
#    if (osdIsrCanIsrTx_6Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_6( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptTx(kCanPhysToLogChannelIndex_6);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptTx();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_6) */
/* CODE CATEGORY 1 END */

#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* **************************************************************************
| NAME:             CanIsrWakeup_6
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Wakeup interrupt service function for CAN channel _6
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_6 )
# if defined(C_ENABLE_WAKEUP_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrWakeup_6Cat)
#    if (osdIsrCanIsrWakeup_6Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_6 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrWakeup_6Cat)
#    if (osdIsrCanIsrWakeup_6Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_6( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptWakeup(kCanPhysToLogChannelIndex_6);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptWakeup();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_6) */
/* CODE CATEGORY 1 END */
#endif

/****************************************************************************
| NAME:             CanIsrStatus_6
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Status interrupt service function for CAN channel _6 (busoff)
****************************************************************************/
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_6 )
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrStatus_6Cat)
#    if (osdIsrCanIsrStatus_6Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_6 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrStatus_6Cat)
#    if (osdIsrCanIsrStatus_6Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_6( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptStatus(kCanPhysToLogChannelIndex_6);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptStatus();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_6) */
/* CODE CATEGORY 1 END */

/* **************************************************************************
| NAME:             CanIsrTx_7
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Transmit interrupt service function for CAN channel _7
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_7 )
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrTx_7Cat)
#    if (osdIsrCanIsrTx_7Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_7 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrTx_7Cat)
#    if (osdIsrCanIsrTx_7Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_7( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptTx(kCanPhysToLogChannelIndex_7);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptTx();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_7) */
/* CODE CATEGORY 1 END */

#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* **************************************************************************
| NAME:             CanIsrWakeup_7
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Wakeup interrupt service function for CAN channel _7
************************************************************************** */
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_7 )
# if defined(C_ENABLE_WAKEUP_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrWakeup_7Cat)
#    if (osdIsrCanIsrWakeup_7Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_7 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrWakeup_7Cat)
#    if (osdIsrCanIsrWakeup_7Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_7( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptWakeup(kCanPhysToLogChannelIndex_7);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptWakeup();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_7) */
/* CODE CATEGORY 1 END */
#endif

/****************************************************************************
| NAME:             CanIsrStatus_7
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Status interrupt service function for CAN channel _7 (busoff)
****************************************************************************/
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_7 )
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrStatus_7Cat)
#    if (osdIsrCanIsrStatus_7Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_7 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrStatus_7Cat)
#    if (osdIsrCanIsrStatus_7Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_7( void )
#  endif /* C_ENABLE_OSEK_OS */
{
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  CanInterruptStatus(kCanPhysToLogChannelIndex_7);     /* call Interrupthandling with logical channel */
#  else
  CanInterruptStatus();
#  endif
} /* END OF CanISR */
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_7) */
/* CODE CATEGORY 1 END */

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) 
/* **************************************************************************
| NAME:             CanIsrGlobalStatus
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Global Status interrupt service function (rx fifo overrun)
************************************************************************** */
/* CODE CATEGORY 1 START */
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsrGlobalStatusCat)
#    if (osdIsrCanIsrGlobalStatusCat != 2)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrGlobalStatus )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
      defined (osdIsrCanIsrGlobalStatusCat)
#    if (osdIsrCanIsrGlobalStatusCat != 1)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN)
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#     endif
#    endif
#   endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrGlobalStatus( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanInterruptGlobalStatus();          /* call Interrupthandling */
} /* END OF CanISR */
# endif /* C_ENABLE_ERROR_POLLING */
/* CODE CATEGORY 1 END */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
# if defined(C_ENABLE_RX_BASICCAN_POLLING )  && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else

/* **************************************************************************
| NAME:             CanIsrRxFifo
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Receive interrupt service function for all RxFifos
************************************************************************** */
/* CODE CATEGORY 1 START */
# if defined(kCanFifoToLogChannelIndex_0) || defined(kCanFifoToLogChannelIndex_1) || \
     defined(kCanFifoToLogChannelIndex_2) || defined(kCanFifoToLogChannelIndex_3) || \
     defined(kCanFifoToLogChannelIndex_4) || defined(kCanFifoToLogChannelIndex_5) || \
     defined(kCanFifoToLogChannelIndex_6) || defined(kCanFifoToLogChannelIndex_7)
#   if defined( C_ENABLE_OSEK_OS ) && \
       defined( C_ENABLE_OSEK_OS_INTCAT2 )
#    if defined (osdIsrCanIsrRxFifoCat)
#     if (osdIsrCanIsrRxFifoCat != 2)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
ISR( CanIsrRxFifo )
#   else
#    if defined( C_ENABLE_OSEK_OS ) && \
        defined (osdIsrCanIsrRxFifoCat)
#     if (osdIsrCanIsrRxFifoCat != 1)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#    if !defined(C_ENABLE_ISRVOID)
#     if defined(C_COMP_GHS_RH850_RSCAN)
#      if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_3116_LL */
#      else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_3116_LL */
#      endif
#     endif
#    endif
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrRxFifo( void )
#   endif /* C_ENABLE_OSEK_OS */
{
  CanInterruptRxFifo();
  extern void CANNM_vBusIdleCheck_ISR(void);/*Add by Li Jiaye , 20170414*/
  CANNM_vBusIdleCheck_ISR();/*Add by Jiaye , 20170414*/

} /* END OF CanISR */
#  endif /* kCanFifoToLogChannelIndex_x */
/* CODE CATEGORY 1 END */

# endif /* C_ENABLE_RX_BASICCAN_POLLING */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#endif  /* Not a pure polling configuration */

/* **************************************************************************
| NAME:             CanInit
| CALLED BY:        CanInitPowerOn(), Network management
| PRECONDITIONS:    none
| INPUT PARAMETERS: Handle to initstructure
| RETURN VALUES:    none
| DESCRIPTION:      initialization of chip-hardware
|                   initialization of receive and transmit message objects
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanInit( CAN_CHANNEL_CANTYPE_FIRST CanInitHandle initObject )     /* PRQA S 1505 */ /* MD_CBD_8.10 */
{
#if defined( C_ENABLE_CAN_RAM_CHECK )
  vuint8                 canRamCheckStatus;
#endif
  CanObjectHandle        hwObjHandle;
#if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION ) || \
    defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
  CanTransmitHandle      txHandle;
#endif
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
  CanReceiveHandle       rxHandle;
#endif
  CanObjectHandle        logTxObjHandle;

  vuint32 canTmpReg;
  #if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel;
  #endif
  #if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
  vuint8 canCount;
  #endif

#if defined( C_HL_ENABLE_LAST_INIT_OBJ )  
  lastInitObject[channel] = initObject;
#endif

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
/* Msg(4:3759) Implicit conversion: int to unsigned short. MISRA Rule 43 - no change in RI 1.4 */
  initObject  += CAN_HL_INIT_OBJ_STARTINDEX(channel);
#endif

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif
  assertUser(initObject < kCanNumberOfInitObjects, channel, kErrorInitObjectHdlTooLarge);
  assertUser(initObject < CAN_HL_INIT_OBJ_STOPINDEX(channel), channel, kErrorInitObjectHdlTooLarge);     /* PRQA S 3689 */ /* MD_Can_3689 */

#if defined( C_ENABLE_CAN_RAM_CHECK )
  canRamCheckStatus = kCanRamCheckOk;
#endif

  {

    #if defined(C_MULTIPLE_PHYS_CHANNEL)
    /* get physical channel index */
    canPhysChannel = mCanLogToPhys(canHwChannel); /* PRQA S 3689 */ /* MD_Can_3689 */
    #endif
    
    #if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
    # if !defined(C_ENABLE_WAKEUP_POLLING)
    #  if defined (C_ENABLE_LL_CAN_INTCTRL)
      CanLL_CanWakeupInterruptDisable(canHwChannel, &canCanInterruptOldStatus[canHwChannel]); /* PRQA S 3689 */ /* MD_Can_3689 */
    #  endif
    #  if defined (C_ENABLE_LL_CAN_INTCB)
      /* ApplCanWakeupInterruptDisable has to disable the interrupt */
      ApplCanWakeupInterruptDisable(canHwChannel);
    #  endif
    # endif
    #endif
    
    if((canStatus[canHwChannel] & kCanHwIsInit) != 0) /* PRQA S 3689 */ /* MD_Can_3689 */
    {
      /* wait for completion of busoff recovery */
      if (CanLL_HwIsBusOff(CAN_HW_CHANNEL_CANPARA_ONLY)) /* PRQA S 3689 */ /* MD_Can_3689 */
      {
        CanLL_CanTimerWait(kCanLoopBusOffRecovery,CanLL_HwIsBusOff(CAN_HW_CHANNEL_CANPARA_ONLY)); /* PRQA S 3415,3689 */ /* MD_Can_3415_LL,MD_Can_3689 */
      }
    
      /* switch to reset mode and check if it is reached */
      CanLL_ModeReq_Phys(canPhysChannel,kCanResetMode);
      if (!CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode))
      {
        if (!CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode))
        {
          CanLL_CanTimerWait(kCanLoopEnterResetMode,!CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode)); /* PRQA S 3415 */ /* MD_Can_3415_LL */
    
    # if defined(C_ENABLE_STOP) && defined(C_ENABLE_HW_LOOP_TIMER)
          if (CanLL_StopTransition[channel] != kCanStopIdle) /* PRQA S 3689 */ /* MD_Can_3689 */
          {
            if (!CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode))
            {
              CanLL_StopTransition[channel] = kCanStopFailed; /* PRQA S 3689 */ /* MD_Can_3689 */
            }
          }
    # endif
        }
      }
    }
    
    /* set bustiming */
    Can->ChCtrl[canPhysChannel].BCFG = CanInitBCFG[initObject]; /* PRQA S 3689 */ /* MD_Can_3689 */
    
    /* set busoff return behavior (and current mode bits) */
    canTmpReg = kCanCrHaltAtBusoff | kCanResetMode;
    /* enable busoff interrupt (also used if special busoff behaviour is configured) */
    #if !defined(C_ENABLE_ERROR_POLLING)
    canTmpReg |= kCanIntMaskBusoff;
    #endif
    /* enable cancel interrupt */
    #if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
    #else
    # if defined(C_ENABLE_CANCEL_IN_HW)
    canTmpReg |= kCanIntMaskCancel;
    # endif
    #endif
    Can->ChCtrl[canPhysChannel].CR = canTmpReg;
    
    /* set TB interrupt enable bits */
    Can->CTBIER[CanLL_WordIndex(canPhysChannel)] = 
      ((Can->CTBIER[CanLL_WordIndex(canPhysChannel)] & CanLL_MaskWordClear(canPhysChannel)) |
        CanLL_WordToSharedReg(canPhysChannel,CanChannelData[canHwChannel].CanTxIntMask)); /* PRQA S 3689 */ /* MD_Can_3689 */
    
    /* message status, send & cancel requests for TB objects 
       and error flags were cleared by channel reset above   */
    
    #if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
    /* clear rx full pendings */
    for(canCount=0;canCount<kCanNumberOfSharedReg16;canCount++)
    {
      Can->CRBRCF[canCount] = CanLL_ClearBitMaskRS(CanChannelData[canHwChannel].CanRxFcMask[canCount]); /* PRQA S 3689 */ /* MD_Can_3689 */
    }
    #endif
    
    /* rx basic pendings are cleared below */
    
    /* Init Tx-Objects -------------------------------------------------------- */
    /* init saved Tx handles: */                   
    /* in case of CommonCAN, transmission is always on the frist HW channel of a CommonCAN channel */
    {
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
      assertGen( ((vsintx)CAN_HL_HW_TX_STOPINDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel))              /* PRQA S 3689 */ /* MD_Can_3689 */
                 == (vsintx)CAN_HL_LOG_HW_TX_STOPINDEX(canHwChannel), channel, kErrorHwToLogTxObjCalculation);          /* PRQA S 3689 */ /* MD_Can_3689 */ /* ESCAN00062667 */
      assertGen( ((vsintx)CAN_HL_HW_TX_STARTINDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel))             /* PRQA S 3689 */ /* MD_Can_3689 */
                 == (vsintx)CAN_HL_LOG_HW_TX_STARTINDEX(canHwChannel), channel, kErrorHwToLogTxObjCalculation);         /* PRQA S 3689 */ /* MD_Can_3689 */ /* ESCAN00062667 */
      assertGen( CAN_HL_LOG_HW_TX_STARTINDEX(canHwChannel) <= CAN_HL_LOG_HW_TX_STOPINDEX(canHwChannel), channel, kErrorHwToLogTxObjCalculation);  /* PRQA S 3689 */ /* MD_Can_3689 */
#endif
  
      for (hwObjHandle=CAN_HL_HW_TX_STARTINDEX(canHwChannel); hwObjHandle<CAN_HL_HW_TX_STOPINDEX(canHwChannel); hwObjHandle++ )   /* PRQA S 3689,3355,3357 */ /* MD_Can_3689,MD_Can_13.7,MD_Can_13.7 */  /* lint !e661 */
      {
        logTxObjHandle = (CanObjectHandle)((vsintx)hwObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));  /* PRQA S 3689 */ /* MD_Can_3689 */   /* lint !e661 */

#if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION ) || \
    defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
        if((canStatus[channel] & kCanHwIsInit) == kCanHwIsInit)      /* PRQA S 3689 */ /* MD_Can_3689 */ /* lint !e661 */
        {
          /* inform application, if a pending transmission is canceled */
          txHandle = canHandleCurTxObj[logTxObjHandle];

# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
          if( txHandle < kCanNumberOfTxObjects )
          {
            APPLCANCANCELNOTIFICATION(channel, txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
          }
# endif
# if defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
          if( txHandle == kCanBufferMsgTransmit)
          { 
            APPLCANMSGCANCELNOTIFICATION(channel); /* PRQA S 3689 */ /* MD_Can_3689 */
          } 
# endif
        }
#endif

        canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;                   /* MsgObj is free */

# if defined( C_ENABLE_CAN_RAM_CHECK )
        if(kCanTrue == CanLL_IsMailboxCorrupt(CAN_HW_CHANNEL_CANPARA_FIRST hwObjHandle))
        {
#  if defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX )
          ApplCanCorruptMailbox(CAN_CHANNEL_CANPARA_FIRST hwObjHandle);
#  endif
          canRamCheckStatus = kCanRamCheckFailed;
        }
# endif

      }

    }

    /* init unused msg objects ------------------------------------------------ */
    for (hwObjHandle=CAN_HL_HW_UNUSED_STARTINDEX(canHwChannel); hwObjHandle<CAN_HL_HW_UNUSED_STOPINDEX(canHwChannel); hwObjHandle++ ) /* PRQA S 3689,3355,3357 */ /* MD_Can_3689,MD_Can_13.7,MD_Can_13.7 */ /* lint !e661 !e681 */
    {
      /* nothing to do */
      break; /* PRQA S 0771 */ /* MD_Can_14.6 */
    }

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
    /* init full can receive msg objects: ------------------------------------- */
    for (hwObjHandle=CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel); hwObjHandle<CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel); hwObjHandle++ ) /* PRQA S 3689,3355,3357 */ /* MD_Can_3689,MD_Can_13.7,MD_Can_13.7 */ /* MD_Can_3689 */
    {
      /* brackets to avoid lint info 834 */
      rxHandle = (hwObjHandle-CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel))+CAN_HL_RX_FULL_STARTINDEX(canHwChannel); /* PRQA S 3689 */ /* MD_Can_3689 */

      /* PRQA S 3689 2 */ /* MD_Can_3689 */
      # if defined(V_ENABLE_USE_DUMMY_STATEMENT)
      rxHandle = rxHandle; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
      # endif
      /* nothing to do */
      break; /* PRQA S 0771 */ /* MD_Can_14.6 */
    }
#endif

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
    /* init basic can receive msg object: ------------------------------------- */
    for (hwObjHandle=CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel); hwObjHandle<CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel); hwObjHandle++ ) /* PRQA S 3689,3355,3357 */ /* MD_Can_3689,MD_Can_13.7,MD_Can_13.7 */
    {

      /* the LL driver has to know which ID tpyes have to be received by which object */
      /* disable fifo to clear pendings */
      Can->CRFCR[hwObjHandle-kCanRxFifoOffset] &= ((kCanRegSize) ~kCanCrFifoEnable);
      /* delete fifo interrupt and overrun flags */
      Can->CRFSR[hwObjHandle-kCanRxFifoOffset] &= ((kCanRegSize) ~(kCanSrRxFifoIntFlag | kCanSrFifoOverrun));
      /* re-enable fifo */
      Can->CRFCR[hwObjHandle-kCanRxFifoOffset] |= kCanCrFifoEnable;
    }
#endif
                     
    {
    #if defined(C_ENABLE_STOP)
      /* suppress start transition if called in context of CanStop() */
      if (CanLL_StopTransition[channel] == kCanStopIdle) /* PRQA S 3689 */ /* MD_Can_3689 */
    #endif
      {
        /* switch to operation mode (and wait till it is reached) */
        CanLL_ModeReq_Phys(canPhysChannel,kCanOperationMode);
        CanLL_CanTimerWait(kCanLoopEnterResetMode,!CanLL_ModeCheck_Phys(canPhysChannel,kCanOperationModeCheck)); /* PRQA S 3415 */ /* MD_Can_3415_LL */
      }
    }
  } /* end of loop over all hw channels */

#if defined( C_ENABLE_TX_OBSERVE )
  ApplCanInit( CAN_CHANNEL_CANPARA_FIRST CAN_HL_LOG_HW_TX_STARTINDEX(canHwChannel), CAN_HL_LOG_HW_TX_STOPINDEX(canHwChannel) ); /* PRQA S 3689 */ /* MD_Can_3689 */
#endif
#if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
  APPL_CAN_MSGTRANSMITINIT( CAN_CHANNEL_CANPARA_ONLY );
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK )
  if( canRamCheckStatus == kCanRamCheckFailed)
  {
    /* let the application decide if communication is disabled */
    if (ApplCanMemCheckFailed(CAN_CHANNEL_CANPARA_ONLY) == kCanDisableCommunication)
    {
      canComStatus[channel] = kCanDisableCommunication; /* PRQA S 3689 */ /* MD_Can_3689 */
    }  
  }
#endif

} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */ 
/* END OF CanInit */
/* CODE CATEGORY 4 END */

/* **************************************************************************
| NAME:             CanInitPowerOn
| CALLED BY:        Application
| PRECONDITIONS:    This function must be called by the application before
|                   any other CAN driver function 
|                   Interrupts must be disabled
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Initialization of the CAN chip
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanInitPowerOn( void )
{ 

#if defined( C_ENABLE_VARIABLE_DLC )        || \
      defined( C_ENABLE_DYN_TX_OBJECTS )      || \
      defined( C_ENABLE_INDICATION_FLAG )     || \
      defined( C_ENABLE_CONFIRMATION_FLAG )
  CanTransmitHandle txHandle;
#endif
#if defined( C_ENABLE_VARIABLE_RX_DATALEN )
  CanReceiveHandle rxHandle;
#endif
  CAN_CHANNEL_CANTYPE_LOCAL

  VStdInitPowerOn();

#if defined( C_ENABLE_VARIABLE_DLC )
  for (txHandle = 0; txHandle < kCanNumberOfTxObjects; txHandle++)
  {
    assertGen(XT_TX_DLC(CanGetTxDlc(txHandle))<(vuint8)9, kCanAllChannels, kErrorTxROMDLCTooLarge);
    canTxDLC_RAM[txHandle] = CanGetTxDlc(txHandle);
  }
#endif

#if defined( C_ENABLE_DYN_TX_OBJECTS )
  /*  Reset dynamic transmission object management -------------------------- */
  for (txHandle = 0; txHandle < kCanNumberOfTxDynObjects; txHandle++)
  {
    /*  Reset management information  */
    canTxDynObjReservedFlag[txHandle] = 0;
  }
#endif /* C_ENABLE_DYN_TX_OBJECTS */

#if defined( C_ENABLE_VARIABLE_RX_DATALEN )
  /*  Initialize the array with received dlc -------------------------- */
  for (rxHandle = 0; rxHandle < kCanNumberOfRxObjects; rxHandle++) {
    canVariableRxDataLen[rxHandle] = CanGetRxDataLen(rxHandle);
  }
#endif

#if defined( C_ENABLE_INDICATION_FLAG )
/* txHandle as loop variable is ok here, because the number of indication bytes is not as high as the number of Rx Messages */
  for (txHandle = 0; txHandle < kCanNumberOfIndBytes; txHandle++) {
    CanIndicationFlags._c[txHandle] = 0;
  }
#endif

#if defined( C_ENABLE_CONFIRMATION_FLAG )
  for (txHandle = 0; txHandle < kCanNumberOfConfBytes; txHandle++) {
    CanConfirmationFlags._c[txHandle] = 0;
  }
#endif

#if defined( C_ENABLE_RX_QUEUE )
  CanDeleteRxQueue();
#endif

#if defined( C_ENABLE_TRANSMIT_QUEUE )
#endif

  {
  #if defined(C_MULTIPLE_PHYS_CHANNEL)
    CanChannelHandle canPhysChannel;
  #endif
  #if defined (C_ENABLE_LL_CAN_INTCTRL)  
  # if defined(V_CPU_RH850)
    tCanIntcChTxPtr CanIntcChTx;
    tCanIntcChErrPtr CanIntcChErr;
  #  if !defined(C_ENABLE_ERROR_POLLING) || (defined(V_CPU_RH850) && (defined( C_ENABLE_INDIVIDUAL_POLLING ) || !defined( C_ENABLE_RX_BASICCAN_POLLING )))
    vuint8 canIntPrioTemp;
  #  endif
  #  if defined(C_ENABLE_INDIVIDUAL_POLLING) || !defined(C_ENABLE_TX_POLLING) || !defined(C_ENABLE_RX_BASICCAN_POLLING) || !defined(C_ENABLE_ERROR_POLLING)
    vuint8 canIntPrioCh;
  #  endif
  # endif
  #endif
    vuint8 canFcObjTemp;
  #if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) || defined( C_ENABLE_RX_BASICCAN_OBJECTS )
    CanObjectHandle hwObjHandle;
    vuint8 canFilterRulesIndex;
    vuint8 canFilterRulesPage;
  #endif
  #if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
    vuint8 canLogHwFifoHandle;
    vuint8 canFilterRulesBcIndex;
    vuint8 canFilterRulesBcStartIndex;
    vuint8 canFilterRulesBcStopIndex;
  #endif
  # if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
    CanReceiveHandle localRxHandle;
  # endif
  
  #if defined (C_ENABLE_LL_CAN_INTCTRL)
  # if !defined(C_ENABLE_ERROR_POLLING) || (defined(V_CPU_RH850) && (defined( C_ENABLE_INDIVIDUAL_POLLING ) || !defined( C_ENABLE_RX_BASICCAN_POLLING ))) 
  #  if defined(V_CPU_RH850)
    canIntPrioTemp = kCanZero;                 /* local temp, init with max priority */
  #  endif
  #  if defined(V_CPU_RH850) 
    canInterruptOldFlag.GErrCnt = kCanZero;    /* counter for interrupt disable/restore on shared overflow source */
  #  endif
  # endif
  #endif
    canFcObjTemp = kCanZero;                   /* local temp */
  #if defined(C_ENABLE_HW_LOOP_TIMER) && defined(C_MULTIPLE_RECEIVE_CHANNEL)
    channel = 0;
  #endif
  
  #if defined(C_ENABLE_CANLL_GEN_CHECK)
    CanLL_CheckGeneratedData();
  #endif
    
    /* wait till CAN RAM initialization is complete */
    if ((Can->CGSR & kCanSrMaskRamIst) != 0)
    {
      CanLL_CanTimerWait(kCanLoopRamInit,(Can->CGSR & kCanSrMaskRamIst) != 0); /* PRQA S 3415 */ /* MD_Can_3415_LL */
    }
  
    /* transit to global stop mode in order to stop all channels that may have been active before */
    if (!CanLL_GlobalModeCheck(kCanStopMode))
    {
      CanLL_GlobalModeReq(kCanResetMode);
      if (!CanLL_GlobalModeCheck(kCanResetMode))
      {
        if (!CanLL_GlobalModeCheck(kCanResetMode))
        {
          CanLL_CanTimerWait(kCanLoopInit,!CanLL_GlobalModeCheck(kCanResetMode)); /* PRQA S 3415 */ /* MD_Can_3415_LL */
        }
      }
      CanLL_GlobalModeReq(kCanStopMode);
      if (!CanLL_GlobalModeCheck(kCanStopMode))
      {
        if (!CanLL_GlobalModeCheck(kCanStopMode))
        {
          CanLL_CanTimerWait(kCanLoopInit,!CanLL_GlobalModeCheck(kCanStopMode)); /* PRQA S 3415 */ /* MD_Can_3415_LL */
        }
      }
    }
  
  #if defined(V_CPU_RH850) && defined(C_ENABLE_ECC_CALLOUT)
    /* the RSCAN is currently in global stop mode, invoke callout for ECC configuration */
    ApplCanEccConfiguration();
  #endif /* V_CPU_RH850 && C_ENABLE_ECC_CALLOUT */
  
    /* transit to global reset mode */
    CanLL_GlobalModeReq(kCanResetMode);
    if (!CanLL_GlobalModeCheck(kCanResetMode))
    {
      if (!CanLL_GlobalModeCheck(kCanResetMode))
      {
        CanLL_CanTimerWait(kCanLoopInit,!CanLL_GlobalModeCheck(kCanResetMode)); /* PRQA S 3415 */ /* MD_Can_3415_LL */
      }
    }
  
  #if defined(C_ENABLE_CAN_HW_RAM_CHECK)
    if (CanLL_IsHwRamCorrupt() == kCanTrue)
    {
      /* if the application decides to stop here put the RSCAN back into stop mode and return */
      if (ApplCanGlobalMemCheckFailed() == kCanDisableCommunication)
      {
        CanLL_GlobalModeReq(kCanStopMode);
  #  if defined(C_MULTIPLE_RECEIVE_CHANNEL)
        for (channel=0; channel<kCanNumberOfChannels; channel++)
  #  endif
        {
          canStatus[channel] = kCanStatusInit;
        }
        if (!CanLL_GlobalModeCheck(kCanStopMode))
        {
          if (!CanLL_GlobalModeCheck(kCanStopMode))
          {
            CanLL_CanTimerWait(kCanLoopInit,!CanLL_GlobalModeCheck(kCanStopMode)); /* PRQA S 3415 */ /* MD_Can_3415_LL */
          }
        }
        return;
      }
    }
  #endif /* C_ENABLE_CAN_HW_RAM_CHECK */
  
  #if defined(C_ENABLE_IF_RSCAN_FD)
    /* Select classical CAN mode */
    Can->CGRMCFG = kCanZero;
  #endif
    Can->CGCFG = kCanGlobCfg;
   
  #if defined (C_ENABLE_LL_CAN_INTCTRL)
  # if defined(V_CPU_RH850)
    CanLL_IntcIntDisable(CanAreaGlob,CanIntcGErr->GErr);
  # endif
  # if defined(V_CPU_RH850)
    CanLL_IntcIntDisable(CanAreaGlob,CanIntcRxFifo->RF);
  # endif
  
  # if defined(C_MULTIPLE_RECEIVE_CHANNEL)
    /* iterate logical channels to disable channel specific interrupts, will be re-enabled if necessary */
    for (channel = 0; channel < kCanNumberOfChannels; channel++)
  # endif
    {
  # if defined(V_CPU_RH850)
      CanIntcChTx = (tCanIntcChTxPtr)CanChannelData[channel].CanIntcChTxBaseAdr;
      CanIntcChErr = (tCanIntcChErrPtr)CanChannelData[channel].CanIntcChErrorBaseAdr;
      CanLL_IntcIntDisable(CanAreaCh(channel),CanIntcChErr->Err);
  # endif
  # if defined(V_CPU_RH850)
      CanLL_IntcIntDisable(CanAreaCh(channel),CanIntcChTx->Tx);
  # endif
    }
  #endif /* C_ENABLE_LL_CAN_INTCTRL */
  
    /* clear receive rule settings */
    Can->CRNCFG[0] = kCanZero;
  #if (kCanMaxPhysChannels > 4)
    Can->CRNCFG[1] = kCanZero;
  #endif
  
  #if defined(C_MULTIPLE_RECEIVE_CHANNEL)
    /* iterate logical channels */
    for (channel = 0; channel < kCanNumberOfChannels; channel++)
  #endif
    {
      {
  #if defined(C_MULTIPLE_PHYS_CHANNEL)
        canPhysChannel = mCanLogToPhys(channel);
  #endif
  
        /* set channel reset mode */
        CanLL_ModeReq_Phys(canPhysChannel,kCanResetMode);
        if (!CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode))
        {
          if (!CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode))
          {
            CanLL_CanTimerWait(kCanLoopInit,!CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode)); /* PRQA S 3415 */ /* MD_Can_3415_LL */
          }
        }
  
  #if defined (C_ENABLE_LL_CAN_INTCTRL)
        /* enable channel specific interrupts */
  # if defined(V_CPU_RH850)
  #  if defined(C_ENABLE_INDIVIDUAL_POLLING) || !defined(C_ENABLE_TX_POLLING) || !defined(C_ENABLE_RX_BASICCAN_POLLING) || !defined(C_ENABLE_ERROR_POLLING)
        canIntPrioCh = (CanChannelData[channel].CanIntPrio & kCanIntcIPR);
  #  endif
  #  if !defined(C_ENABLE_ERROR_POLLING)
        CanIntcChErr = (tCanIntcChErrPtr)CanChannelData[channel].CanIntcChErrorBaseAdr;
        CanLL_IntcIntEnable(CanAreaCh(channel),CanIntcChErr->Err,canIntPrioCh);
  #  endif
  #  if !defined(C_ENABLE_ERROR_POLLING) || \
      (defined(V_CPU_RH850) && (defined( C_ENABLE_INDIVIDUAL_POLLING ) || !defined( C_ENABLE_RX_BASICCAN_POLLING )))
  #   if defined(V_CPU_RH850)
        /* lower levels have higher priority - always set lower priority for shared interrupts */
        if(canIntPrioCh > canIntPrioTemp)
  #   endif
        {
          canIntPrioTemp = canIntPrioCh;
        }
  #  endif
  #  if defined( C_ENABLE_INDIVIDUAL_POLLING ) || !defined( C_ENABLE_TX_POLLING )
      CanIntcChTx = (tCanIntcChTxPtr)CanChannelData[channel].CanIntcChTxBaseAdr;
  #   if defined (V_CPU_RH850)
        CanLL_IntcIntEnable(CanAreaCh(channel),CanIntcChTx->Tx,canIntPrioCh);
  #   endif /* V_CPU_RH850 */
  #  endif /* C_ENABLE_INDIVIDUAL_POLLING || !C_ENABLE_TX_POLLING */
  # endif /* V_CPU_SH2 || V_CPU_RH850 */
  #endif /* C_ENABLE_LL_CAN_INTCTRL */
  
        /* rx buffer layout preparation */
  #if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
        canFcObjTemp += CanRxFcCount(channel);
  #endif
  
        /* rule layout */
  #if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) || defined( C_ENABLE_RX_BASICCAN_OBJECTS )
        Can->CRNCFG[CanLL_ByteIndex(canPhysChannel)] |= CanLL_FilterListConfig(canPhysChannel,CanChannelData[channel].CanFilterRulesTotalCount);
  
        /* get fiter index and prepare filter configuration */
        canFilterRulesIndex = (vuint8) (CanChannelData[channel].CanFilterRulesStartIndex & kCanRuleIndexMask);
        canFilterRulesPage = (vuint8) ((CanChannelData[channel].CanFilterRulesStartIndex & kCanRulePageMask) >> kCanRulePageShiftVal);
        Can->CRECR = kCanRuleWrite | canFilterRulesPage;
  #endif
  
        /* init filter rules */
  #if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
        for (hwObjHandle=CAN_HL_HW_RX_FULL_STARTINDEX(channel); hwObjHandle<CAN_HL_HW_RX_FULL_STOPINDEX(channel); hwObjHandle++ )
        {
          localRxHandle = (hwObjHandle-CAN_HL_HW_RX_FULL_STARTINDEX(channel))+CAN_HL_RX_FULL_STARTINDEX(channel);
          if (canFilterRulesIndex == 16)
          {
            canFilterRulesPage++;
            Can->CRECR = kCanRuleWrite | canFilterRulesPage;
            canFilterRulesIndex = 0;
          }
  # if defined( C_ENABLE_EXTENDED_ID )
  #  if defined( C_ENABLE_MIXED_ID )
          if (CanGetRxIdType(localRxHandle) == kCanIdTypeStd)
          {
            mRuleCode(canFilterRulesIndex) = CanGetRxId0(localRxHandle); /* IDE, RTR, RMS are set accordingly by macro */
            mRuleMask(canFilterRulesIndex) = kCanRuleStdMustMatch;
          }
          else
  #  endif
          {
            mRuleCode(canFilterRulesIndex) = CanGetRxId0(localRxHandle); /* IDE, RTR, RMS are set accordingly by macro */
  #  if defined( C_ENABLE_RX_MASK_EXT_ID )
            mRuleMask(canFilterRulesIndex) = (((vuint32)C_MASK_EXT_ID) & kCanRuleHeaderClrMask) | kCanRuleHeader;
  #  else
            mRuleMask(canFilterRulesIndex) = kCanRuleExtMustMatch;
  #  endif
          }
  # else
          {
            mRuleCode(canFilterRulesIndex) = CanGetRxId0(localRxHandle); /* IDE, RTR, RMS are set accordingly by macro */
            mRuleMask(canFilterRulesIndex) = kCanRuleStdMustMatch;
          }
  # endif
          /* store messages in global rx buffers */
          mRuleBuf(canFilterRulesIndex) = kCanRuleUseBuf | (((vuint32)(hwObjHandle - kCanRxBufOffset)) << 8);
          mRuleFifo(canFilterRulesIndex) = kCanZero;
          canFilterRulesIndex++;
        }
  #endif /* C_ENABLE_RX_FULLCAN_OBJECTS */
  
  #if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
        for (hwObjHandle=CAN_HL_HW_RX_BASIC_STARTINDEX(channel); hwObjHandle<CAN_HL_HW_RX_BASIC_STOPINDEX(channel); hwObjHandle++ )
        {
          canLogHwFifoHandle = (vuint8)((hwObjHandle-kCanRxFifoOffset)-CanChannelData[channel].CanRxBcStartIndex);
          /* always set filters from first initobject, others are not generated */
          canFilterRulesBcStartIndex = (vuint8) (canLogHwFifoHandle * CanChannelData[channel].CanFilterRulesBcCount);
          canFilterRulesBcStopIndex = (vuint8) (canFilterRulesBcStartIndex + CanChannelData[channel].CanFilterRulesBcCount);
          for(canFilterRulesBcIndex=canFilterRulesBcStartIndex; canFilterRulesBcIndex<canFilterRulesBcStopIndex; canFilterRulesBcIndex++)
          {
            if (canFilterRulesIndex == 16)
            {
              canFilterRulesPage++;
              Can->CRECR = kCanRuleWrite | canFilterRulesPage;
              canFilterRulesIndex = 0;
            }
            mRuleCode(canFilterRulesIndex) = (vuint32) (CanChannelData[channel].CanFilterRulesBc[canFilterRulesBcIndex].Code);
            mRuleMask(canFilterRulesIndex) = (vuint32) (kCanRuleHeader | CanChannelData[channel].CanFilterRulesBc[canFilterRulesBcIndex].Mask);
            /* store messages in global rx fifos */
            mRuleBuf(canFilterRulesIndex) = kCanZero;
            mRuleFifo(canFilterRulesIndex) = CanLL_SL32(hwObjHandle-kCanRxFifoOffset);
            canFilterRulesIndex++;
          }
  
          Can->CRFCR[hwObjHandle-kCanRxFifoOffset] = (kCanCrRxFifoSet | ((kCanRegSize)((kCanRegSize)CanChannelData[channel].CanRxFifoDepth[canLogHwFifoHandle] << 8)));
  # if defined( C_ENABLE_INDIVIDUAL_POLLING ) || !defined( C_ENABLE_RX_BASICCAN_POLLING )
  #  if defined( C_ENABLE_INDIVIDUAL_POLLING )
          if (CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][hwObjHandle] == 0)
  #  endif
          {  
            Can->CRFCR[hwObjHandle-kCanRxFifoOffset] |= kCanCrRxFifoIntEnable;
          }
  # endif
        }
  #endif /* C_ENABLE_RX_BASICCAN_OBJECTS */
  
      } /* if channel is used in selected identity */
    } /* iterate logical channels */
  
    /* rx buffer layout */
    Can->CRBNUM = canFcObjTemp;
    /* receiving (disable rule write access) */
    Can->CRECR = kCanRuleReceive;
  
  #if defined(V_CPU_RH850) && defined(C_ENABLE_LL_CAN_INTCTRL)
  # if defined( C_ENABLE_INDIVIDUAL_POLLING ) || !defined( C_ENABLE_RX_BASICCAN_POLLING )
    CanLL_IntcIntEnable(CanAreaGlob,CanIntcRxFifo->RF,canIntPrioTemp);
  # endif
  #endif
  
    /* transit to global operating mode and enable/disable global error interrupt */
  #if !defined(C_ENABLE_ERROR_POLLING) && \
     ((defined(C_ENABLE_RX_BASICCAN_OBJECTS) && defined(C_ENABLE_OVERRUN)) )
  # if defined (C_ENABLE_LL_CAN_INTCTRL)
  #  if defined (V_CPU_RH850)
    CanLL_IntcIntEnable(CanAreaGlob,CanIntcGErr->GErr,canIntPrioTemp);
  #  endif
  # endif
    CanLL_GlobalModeReq(kCanOperationMode | kCanIntMaskMessageLost);
  #else
    CanLL_GlobalModeReq(kCanOperationMode);
  #endif
  
  #if defined(C_ENABLE_HW_LOOP_TIMER) && defined(C_MULTIPLE_RECEIVE_CHANNEL)
    channel = 0;
  #endif
    if (!CanLL_GlobalModeCheck(kCanOperationMode))
    {
      if (!CanLL_GlobalModeCheck(kCanOperationMode))
      {
        CanLL_CanTimerWait(kCanLoopInit,!CanLL_GlobalModeCheck(kCanOperationMode)); /* PRQA S 3415 */ /* MD_Can_3415_LL */
      }
    }
  }

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  for (channel=0; channel<kCanNumberOfChannels; channel++)
#endif
  {

#if defined( C_ENABLE_CAN_RAM_CHECK )
    canComStatus[channel] = kCanEnableCommunication;
#endif
   
    canStatus[channel]              = kCanStatusInit;

    # if defined(C_ENABLE_STOP)
    CanLL_StopTransition[channel] = kCanStopIdle;
    # endif

#if defined( C_ENABLE_CAN_TX_CONF_FCT )
    txInfoStructConf[channel].Channel = channel;
#endif
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )  || \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
    canRxInfoStruct[channel].Channel  = channel;
#endif

#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL)
    canCanInterruptCounter[channel] = 0; 
#endif

#if defined( C_ENABLE_TX_POLLING )          || \
      defined( C_ENABLE_RX_FULLCAN_POLLING )  || \
      defined( C_ENABLE_RX_BASICCAN_POLLING ) || \
      defined( C_ENABLE_ERROR_POLLING )       || \
      defined( C_ENABLE_WAKEUP_POLLING )      
    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
#endif

#if defined( C_ENABLE_DYN_TX_OBJECTS )   && \
    defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
  /*  Reset dynamic transmission object management -------------------------- */
    confirmHandle[channel] = kCanBufferFree;
#endif

#if defined( C_ENABLE_TX_MASK_EXT_ID )
    canTxMask0[channel] = 0;
# if (kCanNumberOfUsedCanTxIdTables > 1)
    canTxMask1[channel] = 0;
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
    canTxMask2[channel] = 0;
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
    canTxMask3[channel] = 0;
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
    canTxMask4[channel] = 0;
# endif
#endif

#if defined( C_ENABLE_ECU_SWITCH_PASS )
    canPassive[channel]             = 0;
#endif

#if defined( C_ENABLE_PART_OFFLINE )
    canTxPartOffline[channel]       = kCanTxPartInit;
#endif
#if defined( C_ENABLE_COND_RECEIVE_FCT )
    canMsgCondRecState[channel]     = kCanTrue;
#endif

    canRxHandle[channel] = kCanRxHandleNotUsed;

    {
#if defined( C_ENABLE_TRANSMIT_QUEUE )
  /* clear all Tx queue flags */
      CanDelQueuedObj( CAN_CHANNEL_CANPARA_ONLY );
#endif

      CanInit( CAN_CHANNEL_CANPARA_FIRST 0 );

      /* canStatus is only set to init and online, if CanInit() is called for this channel. */
      canStatus[channel]              |= (kCanHwIsInit | kCanTxOn);
    }

  }

} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
/* END OF CanInitPowerOn */
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
/* **********************************************************************
* NAME:               CanDelQueuedObj
* CALLED BY:          
* PRECONDITIONS:      
* PARAMETER:          notify: if set to 1 for every deleted obj the appl is notified
* RETURN VALUE:       -
* DESCRIPTION:        Resets the bits with are set to 0 in mask
*                     Clearing the Transmit-queue
*********************************************************************** */
/* CODE CATEGORY 4 START */
static void CanDelQueuedObj( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{ 
  CanSignedTxHandle     queueElementIdx;
  #if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
  CanSignedTxHandle     elementBitIdx;
  CanTransmitHandle     txHandle;
  tCanQueueElementType  elem;
  #endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
# endif

  #  if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
  if((canStatus[channel] & kCanHwIsInit) == kCanHwIsInit) /* PRQA S 3689 */ /* MD_Can_3689 */
  {
    CAN_CAN_INTERRUPT_DISABLE(CAN_CHANNEL_CANPARA_ONLY);        /* avoid interruption by CanHL_TxConfirmation */
    for(queueElementIdx = CAN_HL_TXQUEUE_STARTINDEX(channel); queueElementIdx < CAN_HL_TXQUEUE_STOPINDEX(channel); queueElementIdx++) /* PRQA S 3689 */ /* MD_Can_3689 */
    { 
      elem = canTxQueueFlags[queueElementIdx];
      if(elem != (tCanQueueElementType)0) /* is there any flag set in the queue element? */
      {
        /* iterate through all flags and notify application for every scheduled transmission */
        for(elementBitIdx = ((CanSignedTxHandle)1 << kCanTxQueueShift) - (CanSignedTxHandle)1; elementBitIdx >= (CanSignedTxHandle)0; elementBitIdx--)
        { 
          if( ( elem & CanShiftLookUp[elementBitIdx] ) != (tCanQueueElementType)0)
          { 
            txHandle = (CanTransmitHandle)((((CanTransmitHandle)queueElementIdx << kCanTxQueueShift) + (CanTransmitHandle)elementBitIdx) - CAN_HL_TXQUEUE_PADBITS(channel)); /* PRQA S 3689 */ /* MD_Can_3689 */ /* ESCAN00039235 */
            APPLCANCANCELNOTIFICATION(channel, txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
          } 
        } 
        canTxQueueFlags[queueElementIdx] = (tCanQueueElementType)0;
      }
    } 
    CAN_CAN_INTERRUPT_RESTORE(CAN_CHANNEL_CANPARA_ONLY);
  } 
  else
  #  endif
  {
    for(queueElementIdx = CAN_HL_TXQUEUE_STARTINDEX(channel); queueElementIdx < CAN_HL_TXQUEUE_STOPINDEX(channel); queueElementIdx++) /* PRQA S 3689 */ /* MD_Can_3689 */
    { 
      canTxQueueFlags[queueElementIdx] = (tCanQueueElementType)0;
    } 
  }

# if defined( C_HL_ENABLE_COPROCESSOR_SUPPORT )
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* CODE CATEGORY 4 END */
#endif

#if defined( C_ENABLE_CAN_TRANSMIT )
# if defined( C_ENABLE_CAN_CANCEL_TRANSMIT )
/* CODE CATEGORY 3 START */
/* **************************************************************************
| NAME:             CanCancelTransmit
| CALLED BY:        Application
| PRECONDITIONS:    none
| INPUT PARAMETERS: Tx-Msg-Handle
| RETURN VALUES:    none
| DESCRIPTION:      delete on Msg-Object
************************************************************************** */
C_API_1 void C_API_2 CanCancelTransmit( CanTransmitHandle txHandle )
{
  CanDeclareGlobalInterruptOldStatus
  CAN_CHANNEL_CANTYPE_LOCAL 
  CanObjectHandle        logTxObjHandle;
  /* ##RI1.4 - 1.6: CanCancelTransmit and CanCancelMsgTransmit */
#  if defined( C_ENABLE_CANCEL_IN_HW )
  CanObjectHandle        txObjHandle;
#  endif

# if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanSignedTxHandle queueElementIdx; /* index for accessing the tx queue */
  CanSignedTxHandle elementBitIdx;  /* bit index within the tx queue element */
  CanTransmitHandle queueBitPos;  /* physical bitposition of the handle */
# endif

  if (txHandle < kCanNumberOfTxObjects)         /* legal txHandle ? */
  {
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

# if defined( C_ENABLE_MULTI_ECU_PHYS )
    assertUser(((CanTxIdentityAssignment[txHandle] & V_ACTIVE_IDENTITY_MSK) != (tVIdentityMsk)0 ), channel, kErrorDisabledTxMessage);    /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

    CanNestedGlobalInterruptDisable();
# if defined( C_ENABLE_TRANSMIT_QUEUE )
    #if defined( C_ENABLE_INTERNAL_CHECK ) &&\
        defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if (sizeof(queueBitPos) == 1) /* PRQA S 3325 */ /* MD_Can_3201 */
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      assertInternal( ((vuint16)((vuint16)kCanNumberOfTxObjects + (vuint16)CanTxQueuePadBits[kCanNumberOfChannels-1]) <= 256u), kCanAllChannels, kErrorTxQueueTooManyHandle) /*lint !e572 !e506*/
    }
    else
    {
      if (((sizeof(tCanTxQueuePadBits) == 1) && (kCanNumberOfTxObjects > (65536 - 256))) || (sizeof(tCanTxQueuePadBits) > 1)) /* PRQA S 3325 */ /* MD_Can_3201 */
      { /* PRQA S 3201 */ /* MD_Can_3201 */
        assertInternal( ((vuint32)((vuint32)kCanNumberOfTxObjects + (vuint32)CanTxQueuePadBits[kCanNumberOfChannels-1]) <= 65536u), kCanAllChannels, kErrorTxQueueTooManyHandle) /*lint !e572 !e506*/
      }  
    }
    #endif
    queueBitPos  = txHandle + CAN_HL_TXQUEUE_PADBITS(channel);
    queueElementIdx = (CanSignedTxHandle)(queueBitPos >> kCanTxQueueShift); /* get the queue element where to set the flag */
    elementBitIdx  = (CanSignedTxHandle)(queueBitPos & kCanTxQueueMask);   /* get the flag index wihtin the queue element */
    if( (canTxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) != (tCanQueueElementType)0 )
    {
      canTxQueueFlags[queueElementIdx] &= (tCanQueueElementType)~CanShiftLookUp[elementBitIdx]; /* clear flag from the queue */
      APPLCANCANCELNOTIFICATION(channel, txHandle);
    }
# endif

# if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
    logTxObjHandle = (CanObjectHandle)((vsintx)CanGetTxHwObj(txHandle) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));
# else
    logTxObjHandle = (CanObjectHandle)((vsintx)CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));
# endif/* C_ENABLE_TX_FULLCAN_OBJECTS */
    if (canHandleCurTxObj[logTxObjHandle] == txHandle)
    {
      canHandleCurTxObj[logTxObjHandle] = kCanBufferCancel;

      /* ##RI1.4 - 1.6: CanCancelTransmit and CanCancelMsgTransmit */
# if defined( C_ENABLE_CANCEL_IN_HW )
#  if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
      txObjHandle = CanGetTxHwObj(txHandle);
#  else
      txObjHandle = CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel);
#  endif /* C_ENABLE_TX_FULLCAN_OBJECTS */
      Can->ChBC[mCanLogToPhys(canHwChannel)].TBCR[txObjHandle-mCanTxBufOffset(canHwChannel)] |= kCanCrTxBufCancel; /* PRQA S 3689 */ /* MD_Can_3689 */
# endif /* C_ENABLE_CANCEL_IN_HW */
      APPLCANCANCELNOTIFICATION(channel, txHandle);
    }

    CanNestedGlobalInterruptRestore();
  } /* if (txHandle < kCanNumberOfTxObjects) */
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* CODE CATEGORY 3 END */
# endif /* defined( C_ENABLE_CAN_CANCEL_TRANSMIT ) */

#endif /* if defined( C_ENABLE_CAN_TRANSMIT ) */

#if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
/* **************************************************************************
| NAME:             CanCancelMsgTransmit
| CALLED BY:        Application
| PRECONDITIONS:    none
| INPUT PARAMETERS: none or channel
| RETURN VALUES:    none
| DESCRIPTION:      delete on Msg-Object
************************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanCancelMsgTransmit( CAN_CHANNEL_CANTYPE_ONLY )
{
  CanDeclareGlobalInterruptOldStatus
  CanObjectHandle  logTxObjHandle;
# if defined( C_ENABLE_CANCEL_IN_HW )
  CanObjectHandle  txObjHandle;    /* ##RI1.4 - 1.6: CanCancelTransmit and CanCancelMsgTransmit */
# endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  logTxObjHandle = (CanObjectHandle)((vsintx)CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));    /* PRQA S 3689 */ /* MD_Can_3689 */

  CanNestedGlobalInterruptDisable();
  if (canHandleCurTxObj[logTxObjHandle] == kCanBufferMsgTransmit)
  {
    canHandleCurTxObj[logTxObjHandle] = kCanBufferCancel;

    /* ##RI1.4 - 1.6: CanCancelTransmit and CanCancelMsgTransmit */
# if defined( C_ENABLE_CANCEL_IN_HW )
    txObjHandle = CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel); /* PRQA S 3689 */ /* MD_Can_3689 */
    Can->ChBC[mCanLogToPhys(canHwChannel)].TBCR[txObjHandle-mCanTxBufOffset(canHwChannel)] |= kCanCrTxBufCancel; /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
    APPLCANMSGCANCELNOTIFICATION(channel); /* PRQA S 3689 */ /* MD_Can_3689 */
  }
  CanNestedGlobalInterruptRestore();
}
/* CODE CATEGORY 3 END */
#endif

#if defined( C_ENABLE_CAN_TRANSMIT )
# if defined( C_ENABLE_VARIABLE_DLC )
/* CODE CATEGORY 2 START */
/* **************************************************************************
| NAME:             CanTransmitVarDLC
| CALLED BY:        Netmanagement, application
| PRECONDITIONS:    Can driver must be initialized
| INPUT PARAMETERS: Handle to Tx message, DLC of Tx message
| RETURN VALUES:    kCanTxFailed: transmit failed
|                   kCanTxOk    : transmit was succesful
| DESCRIPTION:      If the CAN driver is not ready for send, the application
|                   decide, whether the transmit request is repeated or not.
************************************************************************** */
C_API_1 vuint8 C_API_2 CanTransmitVarDLC(CanTransmitHandle txHandle, vuint8 dlc) C_API_3
{
  assertUser(dlc<(vuint8)9, kCanAllChannels, kErrorTxDlcTooLarge);
  assertUser(txHandle<kCanNumberOfTxObjects, kCanAllChannels, kErrorTxHdlTooLarge);

  canTxDLC_RAM[ txHandle ] = (canTxDLC_RAM[ txHandle ] & CanLL_DlcMask) | MK_TX_DLC(dlc); /* PRQA S 3689 */ /* MD_Can_3689 */

  return CanTransmit( txHandle );
} /* END OF CanTransmitVarDLC */
/* CODE CATEGORY 2 END */
# endif   /* C_ENABLE_VARIABLE_DLC */

/* **************************************************************************
| NAME:             CanTransmit
| CALLED BY:        application
| PRECONDITIONS:    Can driver must be initialized
| INPUT PARAMETERS: Handle of the transmit object to be send
| RETURN VALUES:    kCanTxFailed: transmit failed
|                   kCanTxOk    : transmit was succesful
| DESCRIPTION:      If the CAN driver is not ready for send, the application
|                   decide, whether the transmit request is repeated or not.
************************************************************************** */
/* CODE CATEGORY 2 START */

C_API_1 vuint8 C_API_2 CanTransmit(CanTransmitHandle txHandle) C_API_3   /* lint !e14 !e31 */
{
  CanDeclareGlobalInterruptOldStatus

# if !defined( C_ENABLE_TX_POLLING )          ||\
     !defined( C_ENABLE_TRANSMIT_QUEUE )      ||\
     defined( C_ENABLE_TX_FULLCAN_OBJECTS )   ||\
     defined( C_ENABLE_INDIVIDUAL_POLLING )
  CanObjectHandle      txObjHandle;
  CanObjectHandle      logTxObjHandle;
  vuint8             rc;
# endif   /* ! C_ENABLE_TX_POLLING  || ! C_ENABLE_TRANSMIT_QUEUE || C_ENABLE_TX_FULLCAN_OBJECTS || C_ENABLE_INDIVIDUAL_POLLING */
  CAN_CHANNEL_CANTYPE_LOCAL

# if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanSignedTxHandle queueElementIdx; /* index for accessing the tx queue */
  CanSignedTxHandle elementBitIdx;  /* bit index within the tx queue element */
  CanTransmitHandle queueBitPos;  /* physical bitposition of the handle */
# endif

  assertUser(txHandle<kCanNumberOfTxObjects, kCanAllChannels, kErrorTxHdlTooLarge);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle);    /* PRQA S 3689 */ /* MD_Can_3689 */ /* lint !e661 */
# endif

# if defined( C_ENABLE_MULTI_ECU_PHYS )
  assertUser(((CanTxIdentityAssignment[txHandle] & V_ACTIVE_IDENTITY_MSK) != (tVIdentityMsk)0 ), channel, kErrorDisabledTxMessage);    /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  /* test offline ---------------------------------------------------------- */
  if ( (canStatus[channel] & kCanTxOn) != kCanTxOn )           /* transmit path switched off */
  {
    return kCanTxFailed;
  }

# if defined( C_ENABLE_PART_OFFLINE )
  if ( (canTxPartOffline[channel] & CanTxSendMask[txHandle]) != (vuint8)0)  /* PRQA S 3689 */ /* MD_Can_3689 */ /* lint !e661 */ /* CAN off ? */
  {
    return (kCanTxPartOffline);
  }
# endif

# if defined( C_ENABLE_CAN_RAM_CHECK )
  if(canComStatus[channel] == kCanDisableCommunication) /* PRQA S 3689 */ /* MD_Can_3689 */ 
  {
    return(kCanCommunicationDisabled);
  }
# endif

# if defined( C_ENABLE_SLEEP_WAKEUP )
  assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep);    /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
# endif
  assertUser(!CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanStop);      /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */

  /* passive mode ---------------------------------------------------------- */
# if defined( C_ENABLE_ECU_SWITCH_PASS )
  if ( canPassive[channel] != (vuint8)0)                             /*  set passive ? */
  {
#  if defined( C_ENABLE_CAN_TX_CONF_FCT ) || \
      defined( C_ENABLE_CONFIRMATION_FCT )
    CAN_CAN_INTERRUPT_DISABLE(channel);      /* avoid CAN Rx interruption */
#  endif

#  if defined( C_ENABLE_CAN_TX_CONF_FCT )
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
    txInfoStructConf[channel].Handle  = txHandle;
    APPL_CAN_TX_CONFIRMATION(&txInfoStructConf[channel]);
#  endif

#  if defined( C_ENABLE_CONFIRMATION_FLAG )       /* set transmit ready flag  */
#   if C_SECURITY_LEVEL > 20
    CanNestedGlobalInterruptDisable();
#   endif
    CanConfirmationFlags._c[CanGetConfirmationOffset(txHandle)] |= CanGetConfirmationMask(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */    /* lint !e661 */
#   if C_SECURITY_LEVEL > 20
    CanNestedGlobalInterruptRestore();
#   endif
#  endif

#  if defined( C_ENABLE_CONFIRMATION_FCT )
    {
      if ( CanGetApplConfirmationPtr(txHandle) != V_NULL ) /* PRQA S 3689 */ /* MD_Can_3689 */
      {
         (CanGetApplConfirmationPtr(txHandle))(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */ /* call completion routine  */
      }
    }
#  endif /* C_ENABLE_CONFIRMATION_FCT */

#  if defined( C_ENABLE_CAN_TX_CONF_FCT ) || \
      defined( C_ENABLE_CONFIRMATION_FCT )
    CAN_CAN_INTERRUPT_RESTORE(channel);
#  endif

    return kCanTxOk;
  }
# endif

   /* can transmit enabled ================================================== */

   /* ----------------------------------------------------------------------- */
   /* ---  transmit queue with one objects ---------------------------------- */
   /* ---  transmit using fullcan objects ----------------------------------- */
   /* ----------------------------------------------------------------------- */

#  if !defined( C_ENABLE_TX_POLLING )          ||\
      !defined( C_ENABLE_TRANSMIT_QUEUE )      ||\
      defined( C_ENABLE_TX_FULLCAN_OBJECTS )   ||\
      defined( C_ENABLE_INDIVIDUAL_POLLING )

#   if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
  txObjHandle = CanGetTxHwObj(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */  /* lint !e661 */
#   else
  txObjHandle = CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel);                                          /* msg in object 0 */
#   endif

  logTxObjHandle = (CanObjectHandle)((vsintx)txObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));
#  endif   /* ! C_ENABLE_TX_POLLING  || ! C_ENABLE_TRANSMIT_QUEUE || C_ENABLE_TX_FULLCAN_OBJECTS || C_ENABLE_INDIVIDUAL_POLLING */

  CanNestedGlobalInterruptDisable();
 
  /* test offline after interrupt disable ---------------------------------- */
  if ( (canStatus[channel] & kCanTxOn) != kCanTxOn )                /* transmit path switched off */
  {
    CanNestedGlobalInterruptRestore();
    return kCanTxFailed;
  }
  
# if defined( C_ENABLE_TRANSMIT_QUEUE )
#  if defined( C_ENABLE_TX_FULLCAN_OBJECTS )  ||\
      !defined( C_ENABLE_TX_POLLING )         ||\
      defined( C_ENABLE_INDIVIDUAL_POLLING )
  if (
#   if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
       (txObjHandle == CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel))                                   /* disabled - lint !e774 */
#   endif
#   if defined( C_ENABLE_TX_FULLCAN_OBJECTS )  &&\
       ( !defined( C_ENABLE_TX_POLLING )         ||\
          defined( C_ENABLE_INDIVIDUAL_POLLING ) )
     &&
#   endif

#   if defined( C_ENABLE_TX_POLLING )
#    if defined( C_ENABLE_INDIVIDUAL_POLLING )
       ( ( CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][txObjHandle] != (vuint8)0 )       /* Object is used in polling mode! */
                         || (canHandleCurTxObj[logTxObjHandle] != kCanBufferFree) )    /* MsgObj used?  */
#    else
        /* write always to queue; transmission is started out of TxTask */
#    endif
#   else
       ( canHandleCurTxObj[logTxObjHandle] != kCanBufferFree)    /* MsgObj used?  */
#   endif
     )
#  endif   /*  ( C_ENABLE_TX_FULLCAN_OBJECTS )  || !( C_ENABLE_TX_POLLING ) || ( C_ENABLE_INDIVIDUAL_POLLING ) */

    {
      /* tx object 0 used -> set msg in queue: ----------------------------- */
      queueBitPos  = txHandle + CAN_HL_TXQUEUE_PADBITS(channel);
      queueElementIdx = (CanSignedTxHandle)(queueBitPos >> kCanTxQueueShift); /* get the queue element where to set the flag */
      elementBitIdx  = (CanSignedTxHandle)(queueBitPos & kCanTxQueueMask);   /* get the flag index wihtin the queue element */
      canTxQueueFlags[queueElementIdx] |= CanShiftLookUp[elementBitIdx];
      CanNestedGlobalInterruptRestore();
      return kCanTxOk;                          
  }
# endif  /* C_ENABLE_TRANSMIT_QUEUE */

# if !defined( C_ENABLE_TX_POLLING )          ||\
     !defined( C_ENABLE_TRANSMIT_QUEUE )      ||\
     defined( C_ENABLE_TX_FULLCAN_OBJECTS )   ||\
     defined( C_ENABLE_INDIVIDUAL_POLLING )

#  if defined( C_ENABLE_TRANSMIT_QUEUE )    && \
      ( defined( C_ENABLE_TX_FULLCAN_OBJECTS )  ||\
        !defined( C_ENABLE_TX_POLLING )         ||\
        defined( C_ENABLE_INDIVIDUAL_POLLING )  )
  else
#  endif
  {
  /* check for transmit message object free --------------------------------- */
    if (( canHandleCurTxObj[logTxObjHandle] != kCanBufferFree)    /* MsgObj used?  */
       || ( !CanLL_TxIsHWObjFree( canHwChannel, txObjHandle ) ) /* PRQA S 0303,3355,3356 */ /* MD_Can_0303_HWaccess,MD_Can_13.7,MD_Can_13.7 */

      /* hareware-txObject is not free -------------------------------------- */
       )  /* end of if question */

    {  /* object used */
      /* tx object n used, quit with error */
      CanNestedGlobalInterruptRestore();
      return kCanTxFailed;
    }
  }

  /* Obj, pMsgObject points to is free, transmit msg object: ---------------- */
  canHandleCurTxObj[logTxObjHandle] = txHandle; /* Save hdl of msgObj to be transmitted */
  CanNestedGlobalInterruptRestore();

  rc = CanCopyDataAndStartTransmission( CAN_CHANNEL_CANPARA_FIRST txObjHandle, txHandle);

#  if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
  if ( rc == kCanTxNotify)
  {
    rc = kCanTxFailed;      /* ignore notification if calls of CanCopy.. is performed within CanTransmit */
  }
#  endif

  return(rc);

# else   /* ! C_ENABLE_TX_POLLING  || ! C_ENABLE_TRANSMIT_QUEUE || C_ENABLE_TX_FULLCAN_OBJECTS || C_ENABLE_INDIVIDUAL_POLLING */
# endif   /* ! C_ENABLE_TX_POLLING  || ! C_ENABLE_TRANSMIT_QUEUE || C_ENABLE_TX_FULLCAN_OBJECTS || C_ENABLE_INDIVIDUAL_POLLING */

} /* PRQA S 6010,6030,6050 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL */
/* END OF CanTransmit */
/* CODE CATEGORY 2 END */

/* **************************************************************************
| NAME:             CanCopyDataAndStartTransmission
| CALLED BY:        CanTransmit, CanHl_RestartTxQueue and CanHL_TxConfirmation
| PRECONDITIONS:    - Can driver must be initialized
|                   - canTxCurHandle[logTxObjHandle] must be set
|                   - the hardwareObject (txObjHandle) must be free
| INPUT PARAMETERS: txHandle: Handle of the transmit object to be send
|                   txObjHandle:  Nr of the HardwareObjects to use
| RETURN VALUES:    kCanTxFailed: transmit failed
|                   kCanTxOk    : transmit was succesful
| DESCRIPTION:      If the CAN driver is not ready for send, the application
|                   decide, whether the transmit request is repeated or not.
************************************************************************** */
/* PRQA S 2001 End_CanCopyDataAndStartTransmission */ /* MD_Can_2001 */
/* CODE CATEGORY 1 START */
static vuint8 CanCopyDataAndStartTransmission( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle, CanTransmitHandle txHandle) C_API_3   /* lint !e14 !e31 */
{
   CanDeclareGlobalInterruptOldStatus
   vuint8               rc;
   CanObjectHandle      logTxObjHandle;
#  if defined( C_ENABLE_COPY_TX_DATA )  
   TxDataPtr   CanMemCopySrcPtr;
#  endif
# if defined( C_ENABLE_DYN_TX_OBJECTS )
   CanTransmitHandle    dynTxObj;
# endif /* C_ENABLE_DYN_TX_OBJECTS */
# if defined( C_ENABLE_PRETRANSMIT_FCT )
   CanTxInfoStruct      txStruct;
# endif

   tTmpData CanLL_TxTmpBuf; /* PRQA S 0759 */ /* MD_Can_0759 */

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
   assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
# endif
   assertInternal(txHandle < kCanNumberOfTxObjects, kCanAllChannels, kErrorInternalTxHdlTooLarge);

# if defined( C_ENABLE_DYN_TX_OBJECTS )
#  if ( kCanNumberOfTxStatObjects == 0)
   dynTxObj = txHandle;               /* only dynamic messages are used */
#  else   /* ( kCanNumberOfTxStatObjects == 0) */
   /* dynamic and static messages are in the system */
   if (txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) /* PRQA S 3689 */ /* MD_Can_3689 */
   {
     dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel);    /* PRQA S 3382,0291,3689 */ /* MD_Can_3382,MD_Can_0291,MD_Can_3689 */
   }
   else
   {
     dynTxObj = kCanTxHandleNotUsed;
   }
#  endif /* ( kCanNumberOfTxStatObjects == 0) */
# endif /* C_ENABLE_DYN_TX_OBJECTS */

   assertInternal(txObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel), channel, kErrorTxObjHandleWrong);      /* PRQA S 3689 */ /* MD_Can_3689 */
   logTxObjHandle = (CanObjectHandle)((vsintx)txObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));       /* PRQA S 3689 */ /* MD_Can_3689 */

   assertHardware( CanLL_TxIsHWObjFree( canHwChannel, txObjHandle ), channel, kErrorTxBufferBusy);          /* PRQA S 0303,3689 */ /* MD_Can_0303,MD_Can_3689 */

   /* set id and dlc  -------------------------------------------------------- */
   {
# if defined( C_ENABLE_DYN_TX_DLC ) || \
      defined( C_ENABLE_DYN_TX_ID )
     if (dynTxObj < kCanNumberOfTxDynObjects)
     {           /* set dynamic part of dynamic objects ---------------------- */
#  if defined( C_ENABLE_DYN_TX_ID )
        mBufId(txObjHandleAdjusted) = canDynTxId0[dynTxObj]; /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
 
#  if defined( C_ENABLE_DYN_TX_DLC )
        mBufDlc(txObjHandleAdjusted) = (kCanRegSize)(((kCanRegSize)((canDynTxDLC[dynTxObj])))<<28); /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
     }
     else
     {          /* set part of static objects assocciated the dynamic -------- */
#  if defined( C_ENABLE_DYN_TX_ID )
#   if defined( C_ENABLE_TX_MASK_EXT_ID )
#    if defined( C_ENABLE_MIXED_ID )
        if (CanGetTxIdType(txHandle)==kCanIdTypeStd)
        {
          mBufId(txObjHandleAdjusted) = CanGetTxId0(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
        }
        else
#    endif
        {
          /* mask extened ID */
          mBufId(txObjHandleAdjusted) = (CanGetTxId0(txHandle)|canTxMask0[channel]); /* PRQA S 3689 */ /* MD_Can_3689 */
        }
#   else
        mBufId(txObjHandleAdjusted) = CanGetTxId0(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
#   endif
#  endif

#  if defined( C_ENABLE_DYN_TX_DLC )
#   if defined( C_ENABLE_VARIABLE_DLC )
        /* init DLC, RAM */
        mBufDlc(txObjHandleAdjusted) = (kCanRegSize)(((kCanRegSize)((canTxDLC_RAM[txHandle])))<<28); /* PRQA S 3689 */ /* MD_Can_3689 */
#   else
        /* init DLC, ROM */
        mBufDlc(txObjHandleAdjusted) = (kCanRegSize)(((kCanRegSize)(CanGetTxDlc(txHandle)))<<28); /* PRQA S 3689 */ /* MD_Can_3689 */
#   endif
#  endif
     }
# endif
     /* set static part commen for static and dynamic objects ---------------- */
# if defined( C_ENABLE_DYN_TX_ID )
# else
#  if defined( C_ENABLE_TX_MASK_EXT_ID )
#   if defined( C_ENABLE_MIXED_ID )
     if (CanGetTxIdType(txHandle)==kCanIdTypeStd)
     {
       mBufId(txObjHandleAdjusted) = CanGetTxId0(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
     }
     else
#   endif
     {
       /* mask extened ID */
       mBufId(txObjHandleAdjusted) = (CanGetTxId0(txHandle)|canTxMask0[channel]); /* PRQA S 3689 */ /* MD_Can_3689 */
     }
#  else
     mBufId(txObjHandleAdjusted) = CanGetTxId0(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
# endif
# if defined( C_ENABLE_DYN_TX_DLC )
# else
#  if defined( C_ENABLE_VARIABLE_DLC )
     /* init DLC, RAM */
     mBufDlc(txObjHandleAdjusted) = (kCanRegSize)(((kCanRegSize)((canTxDLC_RAM[txHandle])))<<28); /* PRQA S 3689 */ /* MD_Can_3689 */
#  else
     /* init DLC, ROM */
     mBufDlc(txObjHandleAdjusted) = (kCanRegSize)(((kCanRegSize)(CanGetTxDlc(txHandle)))<<28); /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
# endif

# if defined( C_ENABLE_MIXED_ID )
#  if defined( C_HL_ENABLE_IDTYPE_IN_ID )
#  else
#   if defined( C_ENABLE_DYN_TX_DLC ) || \
       defined( C_ENABLE_DYN_TX_ID )
     if (dynTxObj < kCanNumberOfTxDynObjects)
     {                      /* set dynamic part of dynamic objects */
#    if defined( C_ENABLE_DYN_TX_ID )
#    else
#    endif
     }
#   else
#   endif
#  endif
# endif

   }

 /* call pretransmit function ----------------------------------------------- */
# if defined( C_ENABLE_PRETRANSMIT_FCT )

   /* pointer needed for other modules */
   /* PRQA S 3689 1 */ /* MD_Can_3689 */
   (txStruct.pChipData) = (CanChipDataPtr)&mBufbData(txObjHandleAdjusted,0);
   (txStruct.pChipMsgObj) = (CanChipMsgPtr)&mBufId(txObjHandleAdjusted);
   txStruct.Handle      = txHandle;

   {  
    /* Is there a PreTransmit function ? ------------------------------------- */ 
    if ( CanGetApplPreTransmitPtr(txHandle) != V_NULL )  /* PRQA S 3689 */ /* MD_Can_3689 */  /* if PreTransmit exists */ 
    { 
      if ( (CanGetApplPreTransmitPtr(txHandle)) (txStruct) == kCanNoCopyData)  /* PRQA S 3689 */ /* MD_Can_3689 */ 
      { 
      
        /* Do not copy the data - already done by the PreTransmit-function */  
        /* --- start transmission --- */  
        goto startTransmission; 
      } 
    } 
   }  
# endif /* C_ENABLE_PRETRANSMIT_FCT */

 /* copy data --------------------------------------------------------------- */
# if defined( C_ENABLE_COPY_TX_DATA )  
#  if defined( C_ENABLE_DYN_TX_DATAPTR )  
   if (dynTxObj < kCanNumberOfTxDynObjects)  
   {  
      CanMemCopySrcPtr = canDynTxDataPtr[dynTxObj];  
   }  
   else  
#  endif  
   {  
     CanMemCopySrcPtr = CanGetTxDataPtr(txHandle);  /* PRQA S 3689 */ /* MD_Can_3689 */
   }  
 /* copy via index in MsgObj data field, copy always 8 bytes ----------- */  
   if ( CanMemCopySrcPtr != V_NULL )   /* copy if buffer exists */
   {
#  if C_SECURITY_LEVEL > 10
     CanNestedGlobalInterruptDisable();  
#  endif
     /* PRQA S 3689 3 */ /* MD_Can_3689 */
     CanLL_TxTmpBuf.bData[0] = CanMemCopySrcPtr[0];
     CanLL_TxTmpBuf.bData[1] = CanMemCopySrcPtr[1];
     CanLL_TxTmpBuf.bData[2] = CanMemCopySrcPtr[2];
     CanLL_TxTmpBuf.bData[3] = CanMemCopySrcPtr[3];
     mBufiData(txObjHandleAdjusted,0) = CanLL_TxTmpBuf.iData[0];
     CanLL_TxTmpBuf.bData[4] = CanMemCopySrcPtr[4];
     CanLL_TxTmpBuf.bData[5] = CanMemCopySrcPtr[5];
     CanLL_TxTmpBuf.bData[6] = CanMemCopySrcPtr[6];
     CanLL_TxTmpBuf.bData[7] = CanMemCopySrcPtr[7];
     mBufiData(txObjHandleAdjusted,1) = CanLL_TxTmpBuf.iData[1];

#  if C_SECURITY_LEVEL > 10
     CanNestedGlobalInterruptRestore();  
#  endif
   }
# endif /* ( C_ENABLE_COPY_TX_DATA ) */  

   CANDRV_SET_CODE_TEST_POINT(0x10A);

# if defined( C_ENABLE_PRETRANSMIT_FCT )
/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
startTransmission:
# endif

   /* test offline and handle and start transmission ------------------------ */
   CanNestedGlobalInterruptDisable();  
   /* If CanTransmit was interrupted by a re-initialization or CanOffline */  
   /* no transmitrequest of this action should be started      */  
   if ((canHandleCurTxObj[logTxObjHandle] == txHandle) && ((canStatus[channel] & kCanTxOn) == kCanTxOn)) /* PRQA S 3689 */ /* MD_Can_3689 */
   {  
     {
       /* tx request for TB object */
       Can->ChBC[mCanLogToPhys(canHwChannel)].TBCR[txObjHandle-mCanTxBufOffset(canHwChannel)] |= kCanCrTxBufReq; /* PRQA S 3689 */ /* MD_Can_3689 */
     }
     
     {
# if defined( C_ENABLE_TX_OBSERVE )
       ApplCanTxObjStart( CAN_CHANNEL_CANPARA_FIRST logTxObjHandle );
# endif
       rc = kCanTxOk;                                    
     }  
   }  
   else  
   {  
# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
     if (canHandleCurTxObj[logTxObjHandle] == txHandle) /* PRQA S 3689 */ /* MD_Can_3689 */
     {
       /* only CanOffline was called on higher level */
       rc = kCanTxNotify;
     }
     else
# endif
     {
       rc = kCanTxFailed;   
     }
     assertInternal((canHandleCurTxObj[logTxObjHandle] == txHandle) || (canHandleCurTxObj[logTxObjHandle] == kCanBufferFree), /* PRQA S 3689 */ /* MD_Can_3689 */
                                                                                       channel, kErrorTxHandleWrong);
     canHandleCurTxObj[logTxObjHandle] = kCanBufferFree; /* PRQA S 3689 */ /* MD_Can_3689 */ /* release TxHandle (CanOffline) */
   }  

   CanNestedGlobalInterruptRestore();

   return (rc);   

} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */ 
/* END OF CanCopyDataAndStartTransmission */
/* CODE CATEGORY 1 END */
/* PRQA L:End_CanCopyDataAndStartTransmission */

#endif /* if defined( C_ENABLE_CAN_TRANSMIT ) */

#if defined( C_ENABLE_TX_POLLING ) || \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  || \
    defined( C_ENABLE_RX_BASICCAN_POLLING ) || \
    defined( C_ENABLE_ERROR_POLLING ) || \
    defined( C_ENABLE_WAKEUP_POLLING ) 
/* **************************************************************************
| NAME:             CanTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task, 
|                   - polling error bus off
|                   - polling Tx objects
|                   - polling Rx objects
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTask(void)
{
  CAN_CHANNEL_CANTYPE_LOCAL

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
  {
    {
# if defined( C_ENABLE_ERROR_POLLING )
      CanErrorTask(CAN_CHANNEL_CANPARA_ONLY);
# endif

# if defined( C_ENABLE_SLEEP_WAKEUP )
#  if defined( C_ENABLE_WAKEUP_POLLING )
      CanWakeUpTask(CAN_CHANNEL_CANPARA_ONLY);
#  endif
# endif

# if defined( C_ENABLE_TX_POLLING ) 
      CanTxTask(CAN_CHANNEL_CANPARA_ONLY);
# endif

# if defined( C_ENABLE_RX_FULLCAN_POLLING ) && \
     defined( C_ENABLE_RX_FULLCAN_OBJECTS )
      CanRxFullCANTask(CAN_CHANNEL_CANPARA_ONLY);
# endif

# if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && \
    defined( C_ENABLE_RX_BASICCAN_POLLING )
      CanRxBasicCANTask(CAN_CHANNEL_CANPARA_ONLY);
# endif
    }
  }
}
/* CODE CATEGORY 2 END */
#endif

#if defined( C_ENABLE_ERROR_POLLING )
/* **************************************************************************
| NAME:             CanErrorTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task, 
|                   - polling error status
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanErrorTask( CAN_CHANNEL_CANTYPE_ONLY )
{

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);     /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0) /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

    {
# if defined( C_ENABLE_SLEEP_WAKEUP )
      if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY)) /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
# endif
      {
        CAN_CAN_INTERRUPT_DISABLE(channel);
        CanHL_ErrorHandling(CAN_HW_CHANNEL_CANPARA_ONLY);
        CAN_CAN_INTERRUPT_RESTORE(channel);
      }
    }

    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }
}
/* CODE CATEGORY 2 END */
#endif

#if defined( C_ENABLE_SLEEP_WAKEUP )
# if defined( C_ENABLE_WAKEUP_POLLING )
/* **************************************************************************
| NAME:             CanWakeUpTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task, 
|                   - polling CAN wakeup event
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanWakeUpTask(CAN_CHANNEL_CANTYPE_ONLY)
{
  CanDeclareGlobalInterruptOldStatus

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#  endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);    /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

    #if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
    if (CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY) && /* PRQA S 3415 */ /* MD_Can_3415_LL */
        (
    #  if defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL)  
          CanLL_CanWakeupOccurred(CAN_HW_CHANNEL_CANPARA_ONLY)
    #  endif
    #  if defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL) && defined(C_ENABLE_LL_CAN_WAKEUP_INTCB)
          ||
    #  endif
    #  if defined(C_ENABLE_LL_CAN_WAKEUP_INTCB)
          (ApplCanWakeupOccurred(canHwChannel) == kCanOk)
    #  endif
        )
       )
    #else
    if (kCanFalse != kCanFalse) /* PRQA S 3325 */ /* MD_Can_3201 */
    #endif
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      CANDRV_SET_CODE_TEST_POINT(0x111);
      CanNestedGlobalInterruptDisable();          /* ESCAN00021223 */
      CanLL_WakeUpHandling(CAN_CHANNEL_CANPARA_ONLY);
      CanNestedGlobalInterruptRestore();          /* ESCAN00021223 */
    }
    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }
}
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* C_ENABLE_SLEEP_WAKEUP */

#if defined( C_ENABLE_TX_POLLING ) 
/* **************************************************************************
| NAME:             CanTxTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task, 
|                   - polling Tx objects
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTxTask( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{
  CanObjectHandle      txObjHandle;

  #if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel;
  canPhysChannel = mCanLogToPhys(canHwChannel);
  #endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);    /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

# if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY)) /* PRQA S 0303,3689 */ /* MD_Can_0303_HWaccess,MD_Can_3689 */
# endif
    {
      /* --  polling Tx objects ---------------------------------------- */

# if defined( C_ENABLE_TX_POLLING )
      /* check for global confirmation Pending and may be reset global pending confirmation */
      /* check TB complete and abort status register (also TRF flag if applicable) */
      if(   ((Can->CTBTCSR[CanLL_WordIndex(canPhysChannel)] & CanLL_MaskWord(canPhysChannel)) != 0)
      #if defined(C_ENABLE_CANCEL_IN_HW)
         || ((Can->CTBASR[CanLL_WordIndex(canPhysChannel)] & CanLL_MaskWord(canPhysChannel)) != 0)
      #endif
        )
      {
        for ( txObjHandle = CAN_HL_HW_TX_STARTINDEX(canHwChannel); txObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel); txObjHandle++ ) /* PRQA S 3689 */ /* MD_Can_3689 */
        {
#  if defined( C_ENABLE_INDIVIDUAL_POLLING )
          if ( CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][txObjHandle] != (vuint8)0 )
#  endif
          {
            /* check for dedicated confirmation pending */
            if(   ((Can->ChBS[canPhysChannel].TBSR[txObjHandle-mCanTxBufOffset(canHwChannel)] & kCanSrTxBufMaskPending) != 0) /* PRQA S 3382,3689 */ /* MD_Can_3382_LL,MD_Can_3689 */
              )
            {
              CANDRV_SET_CODE_TEST_POINT(0x110);
              CAN_CAN_INTERRUPT_DISABLE(channel);
              /* do tx confirmation */
              CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST txObjHandle );
              CAN_CAN_INTERRUPT_RESTORE(channel);
            }
          } /* if individual polling & object has to be polled */
        }
      }
# endif /* ( C_ENABLE_TX_POLLING ) */

# if defined( C_ENABLE_TRANSMIT_QUEUE )
      CanHl_RestartTxQueue( CAN_CHANNEL_CANPARA_ONLY );
# endif /*  C_ENABLE_TRANSMIT_QUEUE */

    } /* if ( CanLL_HwIsSleep... ) */

    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }

} /* PRQA S 6080 */ /* MD_MSR_STMIF */ 
/* END OF CanTxTask */
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_TX_POLLING */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
# if defined( C_ENABLE_TX_POLLING ) 
/* **************************************************************************
| NAME:             CanHl_RestartTxQueue
| CALLED BY:        CanTxTask, via CanLL (TxMsgDestroyed)
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      start transmission if queue entry exists and HW is free
************************************************************************** */
/* CODE CATEGORY 2 START */
static void CanHl_RestartTxQueue( CAN_CHANNEL_CANTYPE_ONLY )
{
  CanTransmitHandle    txHandle;
#  if  defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
  vuint8             rc;
#  endif
  CanDeclareGlobalInterruptOldStatus

  CanSignedTxHandle         queueElementIdx;    /* use as signed due to loop */
  CanSignedTxHandle         elementBitIdx;
  tCanQueueElementType             elem;

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
#  endif

  if (canHandleCurTxObj[(vsintx)CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)] == kCanBufferFree) /* PRQA S 3689 */ /* MD_Can_3689 */
  {
    /* PRQA S 3689 2 */ /* MD_Can_3689 */
    for(queueElementIdx = CAN_HL_TXQUEUE_STOPINDEX(channel) - (CanSignedTxHandle)1; 
                             queueElementIdx >= CAN_HL_TXQUEUE_STARTINDEX(channel); queueElementIdx--)
    {
      elem = canTxQueueFlags[queueElementIdx];
      if(elem != (tCanQueueElementType)0) /* is there any flag set in the queue element? */
      {

        /* Transmit Queued Objects */
        /* start the bitsearch */
        #if defined( C_CPUTYPE_32BIT )
        if((elem & (tCanQueueElementType)0xFFFF0000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
        {
          if((elem & (tCanQueueElementType)0xFF000000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
          {
            if((elem & (tCanQueueElementType)0xF0000000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 28] + 28;
            }
            else /* 0x0F000000 */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 24] + 24;
            }
          }
          else
          {
            if((elem & (tCanQueueElementType)0x00F00000) != (tCanQueueElementType)0)
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 20] + 20;
            }
            else /* 0x000F0000 */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 16] + 16;
            }
          }
        }
        else
        #endif
        {
        #if defined( C_CPUTYPE_32BIT ) 
          if((elem & (tCanQueueElementType)0x0000FF00) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
          {
            if((elem & (tCanQueueElementType)0x0000F000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 12] + 12;
            }
            else /* 0x00000F00 */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 8] + 8;
            }
          }
          else
        #endif
          {
            if((elem & (tCanQueueElementType)0x000000F0) != (tCanQueueElementType)0)
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 4] + 4;
            }
            else /* 0x0000000F */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem];
            }
          }
        }
        /* PRQA S 3689 1 */ /* MD_Can_3689 */
        txHandle = (CanTransmitHandle)((((CanTransmitHandle)queueElementIdx << kCanTxQueueShift) + (CanTransmitHandle)elementBitIdx) - CAN_HL_TXQUEUE_PADBITS(channel)); 
        {

            CanNestedGlobalInterruptDisable();
            if (canHandleCurTxObj[(vsintx)CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)] == kCanBufferFree) /* PRQA S 3689 */ /* MD_Can_3689 */
            {
              if ( (canTxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) != (tCanQueueElementType)0 )
              {
                canTxQueueFlags[queueElementIdx] &= (tCanQueueElementType)~CanShiftLookUp[elementBitIdx]; /* clear flag from the queue */
                /* Save hdl of msgObj to be transmitted */
                canHandleCurTxObj[(vsintx)CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)] = txHandle; /* PRQA S 3689 */ /* MD_Can_3689 */
                CanNestedGlobalInterruptRestore();  
#  if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
                rc = CanCopyDataAndStartTransmission(CAN_CHANNEL_CANPARA_FIRST CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel), txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
                if ( rc == kCanTxNotify)
                {
#   if defined ( C_HL_ENABLE_AVOID_REENTRANT_APPLCANCANCELNOTIFICATION )
                  CanNestedGlobalInterruptDisable();
#   endif
                  APPLCANCANCELNOTIFICATION(channel, txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
#   if defined ( C_HL_ENABLE_AVOID_REENTRANT_APPLCANCANCELNOTIFICATION )
                  CanNestedGlobalInterruptRestore();
#   endif
                }
#  else
                (void)CanCopyDataAndStartTransmission(CAN_CHANNEL_CANPARA_FIRST CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel), txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
                return;
              }

            }
            CanNestedGlobalInterruptRestore();
            return;
        }
      }
    }
  }
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */
/* End of CanHl_RestartTxQueue */
/* CODE CATEGORY 2 END */
# endif
#endif /*  C_ENABLE_TRANSMIT_QUEUE */

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) && \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  
/* **************************************************************************
| NAME:             CanRxFullCANTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task, 
|                   - polling Rx FullCAN objects
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxFullCANTask(CAN_CHANNEL_CANTYPE_ONLY) C_API_3
{

  CanObjectHandle     rxObjHandle;        /* keyword register removed 2005-06-29 Ht */

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);    /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

    {
# if defined( C_ENABLE_SLEEP_WAKEUP )
      if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY)) /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
      {
        /* --  polling fullcan Rx objects ---------------------------------------- */

        /* check for global fullCan Rx indication pending and may be reset global */
        /* indication pending */
        if(   ((Can->CRBRCF[0] & (CanLL_RsCast)CanChannelData[canHwChannel].CanRxFcMask[0]) != 0) /* PRQA S 3689 */ /* MD_Can_3689 */
        #if (kCanNumberOfSharedReg16 > 1)
           || ((Can->CRBRCF[1] & (CanLL_RsCast)CanChannelData[canHwChannel].CanRxFcMask[1]) != 0) /* PRQA S 3689 */ /* MD_Can_3689 */
        #endif
        #if (kCanNumberOfSharedReg16 > 2)
           || ((Can->CRBRCF[2] & (CanLL_RsCast)CanChannelData[canHwChannel].CanRxFcMask[2]) != 0) /* PRQA S 3689 */ /* MD_Can_3689 */
        #endif
        #if (kCanNumberOfSharedReg16 > 3)
           || ((Can->CRBRCF[3] & (CanLL_RsCast)CanChannelData[canHwChannel].CanRxFcMask[3]) != 0) /* PRQA S 3689 */ /* MD_Can_3689 */
        #endif
          )
        {
	  extern void CANNM_vBusIdleCheck_ISR(void);/*Add by Li Jiaye , 20170414*/
	  CANNM_vBusIdleCheck_ISR();/*Add by Jiaye , 20170414*/
          for (rxObjHandle=CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel); rxObjHandle<CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel); rxObjHandle++ ) /* PRQA S 3689 */ /* MD_Can_3689 */
          {
# if defined( C_ENABLE_INDIVIDUAL_POLLING )
            if ( CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][rxObjHandle] != (vuint8)0 )
# endif
            {
              /* check for dedicated indication pending */
              if ((Can->CRBRCF[CanLL_BitIndex(rxObjHandle-kCanRxBufOffset)] & CanLL_SLRS(CanLL_BitPosition(rxObjHandle-kCanRxBufOffset))) != 0)
              {
                CANDRV_SET_CODE_TEST_POINT(0x109);
                CAN_CAN_INTERRUPT_DISABLE(channel);
                CanFullCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle);
                CAN_CAN_INTERRUPT_RESTORE(channel);
              }
            }  /* if individual polling & object has to be polled */
          } /* for ( txObjHandle ) */
        } /* if (global pending) */
      } /* if ( CanLL_HwIsSleep ... )  */
    }  /* for (all associated HW channel) */
    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }

} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* END OF CanRxTask */
/* CODE CATEGORY 2 END */
#endif /*  C_ENABLE_RX_FULLCAN_OBJECTS && C_ENABLE_RX_FULLCAN_POLLING */

#if defined( C_ENABLE_RX_BASICCAN_POLLING ) && \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* **************************************************************************
| NAME:             CanRxBasicCANTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task, 
|                   - polling Rx BasicCAN objects
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxBasicCANTask(CAN_CHANNEL_CANTYPE_ONLY) C_API_3
{
  vuint8 canCount;

  CanObjectHandle     rxObjHandle;          /* keyword register removed 2005-06-29 Ht */

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);   /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

# if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY))
# endif
    {

      if (((Can->CFESR & kCanRxFifoMask & CanChannelData[canHwChannel].CanRxBcMask) != CanChannelData[canHwChannel].CanRxBcMask)) /* PRQA S 3689 */ /* MD_Can_3689 */
      {
        for (rxObjHandle=CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel); rxObjHandle<CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel); rxObjHandle++ ) /* PRQA S 3689 */ /* MD_Can_3689 */
        {
# if defined( C_ENABLE_INDIVIDUAL_POLLING )
          if ( CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][rxObjHandle] != (vuint8)0 )
# endif
          {
            /* check for dedicated indication pending */
            canCount = CanChannelData[canHwChannel].CanRxBcMsgProcessCount; /* PRQA S 3689 */ /* MD_Can_3689 */
            /* process messages till fifo is empty or configured limit is reached */
            while(((Can->CRFSR[rxObjHandle-kCanRxFifoOffset] & kCanSrFifoEmpty) == 0) && (canCount > 0)) /* PRQA S 3382 */ /* MD_Can_3382_LL */
            {
              canCount--;
              CANDRV_SET_CODE_TEST_POINT(0x108);

              CAN_CAN_INTERRUPT_DISABLE(channel);
              CanBasicCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle);
              CAN_CAN_INTERRUPT_RESTORE(channel);
            }
          } /* if individual polling & object has to be polled */
        }
      }
    } /* if ( CanLL_HwIsSleep... )  */

    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }

} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* END OF CanRxTask */
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_RX_BASICCAN_POLLING && C_ENABLE_RX_BASICCAN_OBJECTS */

/* **************************************************************************
| NAME:             CanHL_ErrorHandling
| CALLED BY:        CanISR(), CanErrorTask()
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - error interrupt (busoff, error warning, ...)
************************************************************************** */
/* CODE CATEGORY 2 START */
static void CanHL_ErrorHandling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  #if defined( C_HL_ENABLE_OVERRUN_IN_STATUS )
  # if defined( C_ENABLE_OVERRUN )
  vuint8 canFifoHandle;
  # endif
  #endif

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
#endif

  /* check for status register (bus error)-- */
  if(   CanLL_HwWasBusOff(canHwChannel) /* PRQA S 3689 */ /* MD_Can_3689 */
    )
  {
    Can->ChCtrl[mCanLogToPhys(canHwChannel)].EF = kCanEfMaskBusoffClear; /* PRQA S 3689 */ /* MD_Can_3689 */
    /* ==BUS OFF ERROR========================= */
    APPL_CAN_BUSOFF( CAN_CHANNEL_CANPARA_ONLY );     /* PRQA S 3689 */ /* MD_Can_3689 */ /* call application specific function */
  }

#if defined( C_HL_ENABLE_OVERRUN_IN_STATUS )
  /* check for status register (overrun occured)-- */
# if defined( C_ENABLE_OVERRUN )
  /* check if overrun happened on current channel */
  if((Can->CFMLSR & kCanRxFifoMask & CanChannelData[canHwChannel].CanRxBcMask) != 0) /* PRQA S 3689 */ /* MD_Can_3689 */
  {
    /* clear all possible rxfifo overruns on channel */
    for(canFifoHandle=CanChannelData[canHwChannel].CanRxBcStartIndex;canFifoHandle<CanChannelData[canHwChannel].CanRxBcStopIndex;canFifoHandle++) /* PRQA S 3689 */ /* MD_Can_3689 */
    {
      Can->CRFSR[canFifoHandle] &= ((kCanRegSize) ~kCanSrFifoOverrun);
    }
    ApplCanOverrun( CAN_CHANNEL_CANPARA_ONLY );
  }
# endif
#endif

} /* END OF CanHL_ErrorHandling */
/* CODE CATEGORY 2 END */

#if defined( C_ENABLE_INDIVIDUAL_POLLING )
# if defined( C_ENABLE_TX_POLLING )
/* **************************************************************************
| NAME:             CanTxObjTask()
| CALLED BY:        
| PRECONDITIONS:    
| INPUT PARAMETERS: CAN_HW_CHANNEL_CANTYPE_FIRST 
|                   CanObjectHandle txObjHandle
| RETURN VALUES:    none
| DESCRIPTION:      Polling special Object
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTxObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle)      /* PRQA S 1330 */ /* MD_Can_1330 */
{

  #if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel;
  canPhysChannel = mCanLogToPhys(canHwChannel);
  #endif

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#  endif
  assertUser(txObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel), channel, kErrorHwHdlTooLarge); /* PRQA S 3689 */ /* MD_Can_3689 */

/* ESCAN00076413 */
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(txObjHandle >= CAN_HL_HW_TX_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall);   /* PRQA S 3689 */ /* MD_Can_3689 */ /* lint !e568 */
#  else
#   if (kCanHwTxStartIndex != 0)
  assertUser(txObjHandle >= CAN_HL_HW_TX_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall);   /* PRQA S 3689 */ /* MD_Can_3689 */ /* lint !e568 */
#   endif
#  endif

  assertUser(CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][txObjHandle] != (vuint8)0, channel, kErrorHwObjNotInPolling); /* PRQA S 3689 */ /* MD_Can_3689 */
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion); /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0) /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

#  if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY))
#  endif
    {

      /* check for dedicated confirmation pending */
      if(   ((Can->ChBS[canPhysChannel].TBSR[txObjHandle-mCanTxBufOffset(canHwChannel)] & kCanSrTxBufMaskPending) != 0) /* PRQA S 3382,3689 */ /* MD_Can_3382_LL,MD_Can_3689 */
        )
      {
        CAN_CAN_INTERRUPT_DISABLE(channel);
        /* do tx confirmation */
        CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST txObjHandle );
        CAN_CAN_INTERRUPT_RESTORE(channel);
      }

#  if defined( C_ENABLE_TRANSMIT_QUEUE )
      if ( txObjHandle == CAN_HL_HW_TX_NORMAL_INDEX(channel) ) /* PRQA S 3689 */ /* MD_Can_3689 */
      {
        CanHl_RestartTxQueue( CAN_CHANNEL_CANPARA_ONLY );
      }
#  endif /*  C_ENABLE_TRANSMIT_QUEUE */
    }

    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }
} /* PRQA S 6010 */ /* MD_MSR_STPTH */
/* CanTxObjTask */
/* CODE CATEGORY 2 END */
# endif    /* defined( C_ENABLE_INDIVIDUAL_POLLING ) && defined( C_ENABLE_TX_POLLING ) */

# if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) && \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  
/* **************************************************************************
| NAME:             CanRxFullCANObjTask()
| CALLED BY:        
| PRECONDITIONS:    
| INPUT PARAMETERS: CAN_HW_CHANNEL_CANTYPE_FIRST 
|                   CanObjectHandle rxObjHandle
| RETURN VALUES:    none
| DESCRIPTION:      Polling special Object
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxFullCANObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle)      /* PRQA S 1330 */ /* MD_Can_1330 */
{

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#  endif
  assertUser(rxObjHandle < CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel), channel, kErrorHwHdlTooLarge); /* PRQA S 3689 */ /* MD_Can_3689 */
#  if defined( C_SINGLE_RECEIVE_CHANNEL ) 
#   if (CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel) == 0)
  /* avoid compiler warning: comparison is always true ; ESCAN00059736 */
#   else
  assertUser(rxObjHandle >= CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall);  /* lint !e568 */
#   endif
#  else
  assertUser(rxObjHandle >= CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall); /* PRQA S 3689 */ /* MD_Can_3689 */ /* lint !e568 */
#  endif
  assertUser(CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][rxObjHandle] != (vuint8)0, channel, kErrorHwObjNotInPolling);
  assertUser((canPollingTaskActive[channel] == 0), channel, kErrorPollingTaskRecursion); /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0) /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

#  if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY))
#  endif
    {
      /* check for dedicated indication pending */
      if ((Can->CRBRCF[CanLL_BitIndex(rxObjHandle-kCanRxBufOffset)] & CanLL_SLRS(CanLL_BitPosition(rxObjHandle-kCanRxBufOffset))) != 0)
      {
        CANDRV_SET_CODE_TEST_POINT(0x109);
        CAN_CAN_INTERRUPT_DISABLE(channel);
        CanFullCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle);
        CAN_CAN_INTERRUPT_RESTORE(channel);
      }
    }
    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }
} /* PRQA S 6010 */ /* MD_MSR_STPTH */
/* CanRxFullCANObjTask */
/* CODE CATEGORY 2 END */
# endif

# if defined( C_ENABLE_RX_BASICCAN_POLLING ) && \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* **************************************************************************
| NAME:             CanRxBasicCANObjTask()
| CALLED BY:        
| PRECONDITIONS:    
| INPUT PARAMETERS: CAN_HW_CHANNEL_CANTYPE_FIRST 
|                   CanObjectHandle rxObjHandle
| RETURN VALUES:    none
| DESCRIPTION:      Polling special Object
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxBasicCANObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle)        /* PRQA S 1330 */ /* MD_Can_1330 */
{
#  if kCanNumberOfHwObjPerBasicCan > 1
  CanObjectHandle i;
#  endif

  vuint8 canCount;

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#  endif
  assertUser(rxObjHandle < CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel), channel, kErrorHwHdlTooLarge); /* PRQA S 3689 */ /* MD_Can_3689 */
#  if defined( C_SINGLE_RECEIVE_CHANNEL ) 
#   if (CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel) == 0)
  /* avoid compiler warning: comparison is always true ; ESCAN00058586 */
#   else
  assertUser(rxObjHandle >= CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall); /* lint !e568 */
#   endif
#  else
  assertUser(rxObjHandle >= CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall); /* PRQA S 3689 */ /* MD_Can_3689 */ /* lint !e568 */
#  endif
  assertUser(CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][rxObjHandle] != (vuint8)0, channel, kErrorHwObjNotInPolling);
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion); /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canPollingTaskActive[channel] == (vuint8)0) /* PRQA S 3689 */ /* MD_Can_3689 */ /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

#  if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY) )
#  endif
    {

#  if kCanNumberOfHwObjPerBasicCan > 1
      /* loop over all HW objects assigned to one BasicCAN  */
      for (i = 0; i < kCanNumberOfHwObjPerBasicCan; i++)
      {
#  endif
        /* check for dedicated indication pending */
        canCount = CanChannelData[canHwChannel].CanRxBcMsgProcessCount; /* PRQA S 3689 */ /* MD_Can_3689 */
        /* process messages till fifo is empty or configured limit is reached */
        while(((Can->CRFSR[rxObjHandle-kCanRxFifoOffset] & kCanSrFifoEmpty) == 0) && (canCount > 0)) /* PRQA S 3382 */ /* MD_Can_3382_LL */
        {
          canCount--;
          CANDRV_SET_CODE_TEST_POINT(0x109);
          CAN_CAN_INTERRUPT_DISABLE(channel);
          CanBasicCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle);
          CAN_CAN_INTERRUPT_RESTORE(channel);
        }
#  if kCanNumberOfHwObjPerBasicCan > 1
        rxObjHandle++;
      }
#  endif
    }
    canPollingTaskActive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
  }
} /* PRQA S 6010 */ /* MD_MSR_STPTH */
/* CanRxBasicCANObjTask */
/* CODE CATEGORY 2 END */
# endif
#endif /* C_ENABLE_INDIVIDUAL_POLLING */

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* **************************************************************************
| NAME:             CanBasicCanMsgReceived
| CALLED BY:        CanISR()
| PRECONDITIONS:
| INPUT PARAMETERS: internal can chip number
| RETURN VALUES:    none
| DESCRIPTION:      - basic can receive
************************************************************************** */
/* PRQA S 2001 End_CanBasicCanMsgReceived */ /* MD_Can_2001 */
/* CODE CATEGORY 1 START */
static void CanBasicCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle)
{
# if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  tCanRxInfoStruct    *pCanRxInfoStruct;
# endif  
  
# if ( !defined( C_SEARCH_HASH ) && \
       !defined( C_SEARCH_INDEX ) )  ||\
     defined( C_ENABLE_RANGE_0 ) || \
     defined( C_ENABLE_RANGE_1 ) || \
     defined( C_ENABLE_RANGE_2 ) || \
     defined( C_ENABLE_RANGE_3 )
  tCanRxId0 idRaw0;
#  if (kCanNumberOfUsedCanRxIdTables > 1)
  tCanRxId1 idRaw1;
#  endif
#  if (kCanNumberOfUsedCanRxIdTables > 2)
  tCanRxId2 idRaw2;
#  endif
#  if (kCanNumberOfUsedCanRxIdTables > 3)
  tCanRxId3 idRaw3;
#  endif
#  if (kCanNumberOfUsedCanRxIdTables > 4)
  tCanRxId4 idRaw4;
#  endif
# endif

# if defined( C_SEARCH_HASH )
#  if (kCanNumberOfRxBasicCANObjects > 0)
#   if (kHashSearchListCountEx > 0)
  vuint32          idExt;
#    if (kHashSearchListCountEx > 1)
  vuint32          winternExt;        /* prehashvalue         */
#    endif
#   endif
#   if (kHashSearchListCount > 0)
  vuint16          idStd;
#    if (kHashSearchListCount > 1)
  vuint16          winternStd;        /* prehashvalue         */
#    endif
#   endif
#   if (((kHashSearchListCountEx > 1) && (kHashSearchMaxStepsEx > 1)) ||\
        ((kHashSearchListCount > 1)   && (kHashSearchMaxSteps > 1))) 
  vuint16          i_increment;    /* delta for next step  */
  vsint16          count;
#   endif
#  endif  /* kCanNumberOfRxBasicCANObjects > 0 */
# endif

# if defined( C_ENABLE_GENERIC_PRECOPY ) || \
    defined( C_ENABLE_PRECOPY_FCT )     || \
    defined( C_ENABLE_COPY_RX_DATA )    || \
    defined( C_ENABLE_INDICATION_FLAG ) || \
    defined( C_ENABLE_INDICATION_FCT )  || \
    defined( C_ENABLE_DLC_CHECK )       || \
    defined( C_ENABLE_NOT_MATCHED_FCT )
#  if (kCanNumberOfRxBasicCANObjects > 0)

  CanReceiveHandle         rxHandle;

  rxHandle = kCanRxHandleNotUsed; /* PRQA S 3198 */ /* MD_Can_3198 */

#  endif /* kCanNumberOfRxBasicCANObjects > 0 */
# endif

  CANDRV_SET_CODE_TEST_POINT(0x100);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
# endif

  /* delete interrupt flag here at the beginning to ensure detection of new messages */
  Can->CRFSR[rxObjHandle-kCanRxFifoOffset] &= ((kCanRegSize) ~kCanSrRxFifoIntFlag);
  
  /* copy message (ID, DLC, DATA) to temp buffer */
  CanLL_RxTmpBuf[canHwChannel].Id         = mBufId(rxObjHandle);      /* PRQA S 3689 */ /* MD_Can_3689 */
  CanLL_RxTmpBuf[canHwChannel].Dlc        = mBufDlc(rxObjHandle);     /* PRQA S 3689 */ /* MD_Can_3689 */
  CanLL_RxTmpBuf[canHwChannel].u.iData[0] = mBufiData(rxObjHandle,0); /* PRQA S 3689 */ /* MD_Can_3689 */
  CanLL_RxTmpBuf[canHwChannel].u.iData[1] = mBufiData(rxObjHandle,1); /* PRQA S 3689 */ /* MD_Can_3689 */
  
  /* Point to next msg in fifo */
  Can->CRFPCR[rxObjHandle-kCanRxFifoOffset] = kCanPcrFifoPC;

# if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  /* PRQA S 3689 5 */ /* MD_Can_3689 */
  pCanRxInfoStruct =  &canRxInfoStruct[channel]; 
  (pCanRxInfoStruct->pChipMsgObj) = (CanChipMsgPtr)&(CanLL_RxTmpBuf[canHwChannel].Id);
  (pCanRxInfoStruct->pChipData) = (CanChipDataPtr)&(CanLL_RxTmpBuf[canHwChannel].u.bData[0]);
  canRDSRxPtr[channel] = pCanRxInfoStruct->pChipData;
# else
  (canRxInfoStruct[channel].pChipMsgObj) = (CanChipMsgPtr)&(CanLL_RxTmpBuf[canHwChannel].Id);
  (canRxInfoStruct[channel].pChipData) = (CanChipDataPtr)&(CanLL_RxTmpBuf[canHwChannel].u.bData[0]);
  canRDSRxPtr[channel] = canRxInfoStruct[channel].pChipData;
# endif
  CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)      = kCanRxHandleNotUsed;  

# if defined( C_ENABLE_CAN_RAM_CHECK )
  if(canComStatus[channel] == kCanDisableCommunication) /* PRQA S 3689 */ /* MD_Can_3689 */
  {
    goto finishBasicCan; /* PRQA S 3689 */ /* MD_Can_3689 */ /* ignore reception */
  }
# endif

# if defined( C_HL_ENABLE_OVERRUN_IN_STATUS )
# else
#  if defined( C_ENABLE_OVERRUN )
  {
    ApplCanOverrun( CAN_CHANNEL_CANPARA_ONLY );
  }
#  endif
# endif

  /* ************************** reject remote frames  ************************************** */

  /* ************************** reject messages with unallowed ID type ************************************** */

# if defined( C_ENABLE_COND_RECEIVE_FCT )
  /* ************************** conditional message receive function  ************************************** */
  if(canMsgCondRecState[channel]==kCanTrue)
  {
    ApplCanMsgCondReceived( CAN_HL_P_RX_INFO_STRUCT(channel) );
  }
# endif

# if defined( C_ENABLE_RECEIVE_FCT )
  /* ************************** call ApplCanMsgReceived() ************************************************** */
  if (APPL_CAN_MSG_RECEIVED( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
  {
    goto finishBasicCan;
  }
# endif
  
# if ( !defined( C_SEARCH_HASH ) && \
       !defined( C_SEARCH_INDEX ) ) || \
     defined( C_ENABLE_RANGE_0 ) || \
     defined( C_ENABLE_RANGE_1 ) || \
     defined( C_ENABLE_RANGE_2 ) || \
     defined( C_ENABLE_RANGE_3 )
  /* ************************** calculate idRaw for filtering ********************************************** */
#  if defined( C_ENABLE_EXTENDED_ID )
#   if defined( C_ENABLE_MIXED_ID )
  if (CanRxActualIdType(CAN_HL_P_RX_INFO_STRUCT(channel)) == kCanIdTypeExt)
#   endif
  {
#   if defined( C_ENABLE_RX_MASK_EXT_ID )
    idRaw0 = CanRxActualIdRaw0( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID0(C_MASK_EXT_ID); /* PRQA  S 0310 */ /* MD_Can_0310 */
#    if (kCanNumberOfUsedCanRxIdTables > 1)
    idRaw1 = CanRxActualIdRaw1( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID1(C_MASK_EXT_ID);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 2)
    idRaw2 = CanRxActualIdRaw2( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID2(C_MASK_EXT_ID);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 3)
    idRaw3 = CanRxActualIdRaw3( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID3(C_MASK_EXT_ID);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 4)
    idRaw4 = CanRxActualIdRaw4( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID4(C_MASK_EXT_ID);
#    endif
#   else
    idRaw0 = CanRxActualIdRaw0( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID0(0x1FFFFFFF); /* PRQA  S 0310,0311 */ /* MD_Can_0310,MD_Can_0311 */
#    if (kCanNumberOfUsedCanRxIdTables > 1)
    idRaw1 = CanRxActualIdRaw1( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID1(0x1FFFFFFF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 2)
    idRaw2 = CanRxActualIdRaw2( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID2(0x1FFFFFFF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 3)
    idRaw3 = CanRxActualIdRaw3( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID3(0x1FFFFFFF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 4)
    idRaw4 = CanRxActualIdRaw4( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID4(0x1FFFFFFF);
#    endif
#   endif /*  C_ENABLE_RX_MASK_EXT_ID */
  }
#   if defined( C_ENABLE_MIXED_ID )
  else
  {
    idRaw0 = CanRxActualIdRaw0( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID0(0x7FF); /* PRQA  S 0310 */ /* MD_Can_0310 */
#    if (kCanNumberOfUsedCanRxIdTables > 1)
    idRaw1 = CanRxActualIdRaw1( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID1(0x7FF); /* PRQA  S 0310 */ /* MD_Can_0310 */
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 2)
    idRaw2 = CanRxActualIdRaw2( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID2(0x7FF); /* PRQA  S 0310 */ /* MD_Can_0310 */
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 3)
    idRaw3 = CanRxActualIdRaw3( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID3(0x7FF); /* PRQA  S 0310 */ /* MD_Can_0310 */
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 4)
    idRaw4 = CanRxActualIdRaw4( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID4(0x7FF); /* PRQA  S 0310 */ /* MD_Can_0310 */
#    endif
  }
#   endif
#  else /* C_ENABLE_EXTENDED_ID */
  {
    idRaw0 = CanRxActualIdRaw0( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID0(0x7FF); /* PRQA  S 0310 */ /* MD_Can_0310 */
#   if (kCanNumberOfUsedCanRxIdTables > 1)
    idRaw1 = CanRxActualIdRaw1( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID1(0x7FF); /* PRQA  S 0310 */ /* MD_Can_0310 */
#   endif
#   if (kCanNumberOfUsedCanRxIdTables > 2)
    idRaw2 = CanRxActualIdRaw2( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID2(0x7FF); /* PRQA  S 0310 */ /* MD_Can_0310 */
#   endif
#   if (kCanNumberOfUsedCanRxIdTables > 3)
    idRaw3 = CanRxActualIdRaw3( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID3(0x7FF); /* PRQA  S 0310 */ /* MD_Can_0310 */
#   endif
#   if (kCanNumberOfUsedCanRxIdTables > 4)
    idRaw4 = CanRxActualIdRaw4( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID4(0x7FF); /* PRQA  S 0310 */ /* MD_Can_0310 */
#   endif
  }
#  endif /* C_ENABLE_EXTENDED_ID */
# endif /* ( !defined( C_SEARCH_HASH ) && ...  defined( C_ENABLE_RANGE_3 ) */

  /* ***************** Range filtering ****************************************************************** */

  {
#  if defined( C_ENABLE_RANGE_0 )
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if ( (CanChannelObject[channel].RangeActiveFlag & kCanRange0) != (vuint16)0 ) /* PRQA  S 3689 */ /* MD_Can_3689 */
    {
#    if defined( C_ENABLE_MIXED_ID ) && !defined( C_HL_ENABLE_IDTYPE_IN_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CANRANGE0IDTYPE(channel))
#    endif
      {
        if ( C_RANGE_MATCH( CAN_RX_IDRAW_PARA, CANRANGE0ACCMASK(channel), CANRANGE0ACCCODE(channel)) ) /* PRQA  S 3689 */ /* MD_Can_3689 */
#   else    /* C_SINGLE_RECEIVE_CHANNEL) */
    {
#    if (C_RANGE0_IDTYPE == kCanIdTypeStd )
#     if defined( C_ENABLE_MIXED_ID ) && !defined( C_HL_ENABLE_IDTYPE_IN_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeStd)
#     endif
      {
        if ( C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, CANRANGE0ACCMASK(channel), CANRANGE0ACCCODE(channel)) )
#    else  /* C_RANGE_0_IDTYPE == kCanIdTypeExt */
#     if defined( C_ENABLE_MIXED_ID ) && !defined( C_HL_ENABLE_IDTYPE_IN_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeExt)
#     endif
      {
        if ( C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, CANRANGE0ACCMASK(channel), CANRANGE0ACCCODE(channel)) )
#    endif
#   endif
        {
#   if defined( C_ENABLE_RX_QUEUE_RANGE )
          if (CanRxQueueRange0[channel] == kCanTrue) /* PRQA  S 3689 */ /* MD_Can_3689 */
          {
            pCanRxInfoStruct->Handle      = kCanRxHandleRange0;
            (void)CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY );
            goto finishBasicCan;
          }
          else
#   endif  /* C_ENABLE_RX_QUEUE */
          {
            if (APPLCANRANGE0PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
            {
              goto finishBasicCan;
            }
          }
        }
      }
    }
#  endif  /* C_ENABLE_RANGE_0 */

#  if defined( C_ENABLE_RANGE_1 )
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if ( (CanChannelObject[channel].RangeActiveFlag & kCanRange1) != (vuint16)0 ) /* PRQA  S 3689 */ /* MD_Can_3689 */
    {
#    if defined( C_ENABLE_MIXED_ID ) && !defined( C_HL_ENABLE_IDTYPE_IN_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CANRANGE1IDTYPE(channel))
#    endif
      {
        if ( C_RANGE_MATCH( CAN_RX_IDRAW_PARA, CANRANGE1ACCMASK(channel), CANRANGE1ACCCODE(channel)) ) /* PRQA  S 3689 */ /* MD_Can_3689 */
#   else    /* C_SINGLE_RECEIVE_CHANNEL) */
    {
#    if (C_RANGE1_IDTYPE == kCanIdTypeStd )
#     if defined( C_ENABLE_MIXED_ID ) && !defined( C_HL_ENABLE_IDTYPE_IN_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeStd)
#     endif
      {
        if ( C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, CANRANGE1ACCMASK(channel), CANRANGE1ACCCODE(channel)) )
#    else  /* C_RANGE_1_IDTYPE == kCanIdTypeExt */
#     if defined( C_ENABLE_MIXED_ID ) && !defined( C_HL_ENABLE_IDTYPE_IN_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeExt)
#     endif
      {
        if ( C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, CANRANGE1ACCMASK(channel), CANRANGE1ACCCODE(channel)) )
#    endif
#   endif
        {
#   if defined( C_ENABLE_RX_QUEUE_RANGE )
          if (CanRxQueueRange1[channel] == kCanTrue) /* PRQA  S 3689 */ /* MD_Can_3689 */
          {
            pCanRxInfoStruct->Handle      = kCanRxHandleRange1;
            (void)CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY );
            goto finishBasicCan;
          }
          else
#   endif  /* C_ENABLE_RX_QUEUE */
          {
            if (APPLCANRANGE1PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
            {
              goto finishBasicCan;
            }
          }
        }
      }
    }
#  endif  /* C_ENABLE_RANGE_1 */

#  if defined( C_ENABLE_RANGE_2 )
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if ( (CanChannelObject[channel].RangeActiveFlag & kCanRange2) != (vuint16)0 ) /* PRQA  S 3689 */ /* MD_Can_3689 */
    {
#    if defined( C_ENABLE_MIXED_ID ) && !defined( C_HL_ENABLE_IDTYPE_IN_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CANRANGE2IDTYPE(channel))
#    endif
      {
        if ( C_RANGE_MATCH( CAN_RX_IDRAW_PARA, CANRANGE2ACCMASK(channel), CANRANGE2ACCCODE(channel)) ) /* PRQA  S 3689 */ /* MD_Can_3689 */
#   else    /* C_SINGLE_RECEIVE_CHANNEL) */
    {
#    if (C_RANGE2_IDTYPE == kCanIdTypeStd )
#     if defined( C_ENABLE_MIXED_ID ) && !defined( C_HL_ENABLE_IDTYPE_IN_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeStd)
#     endif
      {
        if ( C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, CANRANGE2ACCMASK(channel), CANRANGE2ACCCODE(channel)) )
#    else  /* C_RANGE_2_IDTYPE == kCanIdTypeExt */
#     if defined( C_ENABLE_MIXED_ID ) && !defined( C_HL_ENABLE_IDTYPE_IN_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeExt)
#     endif
      {
        if ( C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, CANRANGE2ACCMASK(channel), CANRANGE2ACCCODE(channel)) )
#    endif
#   endif
        {
#   if defined( C_ENABLE_RX_QUEUE_RANGE )
          if (CanRxQueueRange2[channel] == kCanTrue) /* PRQA  S 3689 */ /* MD_Can_3689 */
          {
            pCanRxInfoStruct->Handle      = kCanRxHandleRange2;
            (void)CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY );
            goto finishBasicCan;
          }
          else
#   endif  /* C_ENABLE_RX_QUEUE */
          {
            if (APPLCANRANGE2PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
            {
              goto finishBasicCan;
            }
          }
        }
      }
    }
#  endif  /* C_ENABLE_RANGE_2 */

#  if defined( C_ENABLE_RANGE_3 )
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if ( (CanChannelObject[channel].RangeActiveFlag & kCanRange3) != (vuint16)0 ) /* PRQA  S 3689 */ /* MD_Can_3689 */
    {
#    if defined( C_ENABLE_MIXED_ID ) && !defined( C_HL_ENABLE_IDTYPE_IN_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CANRANGE3IDTYPE(channel))
#    endif
      {
        if ( C_RANGE_MATCH( CAN_RX_IDRAW_PARA, CANRANGE3ACCMASK(channel), CANRANGE3ACCCODE(channel)) ) /* PRQA  S 3689 */ /* MD_Can_3689 */
#   else    /* C_SINGLE_RECEIVE_CHANNEL) */
    {
#    if (C_RANGE3_IDTYPE == kCanIdTypeStd )
#     if defined( C_ENABLE_MIXED_ID ) && !defined( C_HL_ENABLE_IDTYPE_IN_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeStd)
#     endif
      {
        if ( C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, CANRANGE3ACCMASK(channel), CANRANGE3ACCCODE(channel)) )
#    else  /* C_RANGE_3_IDTYPE == kCanIdTypeExt */
#     if defined( C_ENABLE_MIXED_ID ) && !defined( C_HL_ENABLE_IDTYPE_IN_ID )
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeExt)
#     endif
      {
        if ( C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, CANRANGE3ACCMASK(channel), CANRANGE3ACCCODE(channel)) )
#    endif
#   endif
        {
#   if defined( C_ENABLE_RX_QUEUE_RANGE )
          if (CanRxQueueRange3[channel] == kCanTrue) /* PRQA  S 3689 */ /* MD_Can_3689 */
          {
            pCanRxInfoStruct->Handle      = kCanRxHandleRange3;
            (void)CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY );
            goto finishBasicCan;
          }
          else
#   endif  /* C_ENABLE_RX_QUEUE */
          {
            if (APPLCANRANGE3PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
            {
              goto finishBasicCan;
            }
          }
        }
      }
    }
#  endif  /* C_ENABLE_RANGE_3 */

  }

# if defined( C_ENABLE_GENERIC_PRECOPY ) || \
    defined( C_ENABLE_PRECOPY_FCT )     || \
    defined( C_ENABLE_COPY_RX_DATA )    || \
    defined( C_ENABLE_INDICATION_FLAG ) || \
    defined( C_ENABLE_INDICATION_FCT )  || \
    defined( C_ENABLE_DLC_CHECK )       || \
    defined( C_ENABLE_NOT_MATCHED_FCT )
# if (kCanNumberOfRxBasicCANObjects > 0)

   /* search the received id in ROM table: */

#  if defined( C_SEARCH_LINEAR )
  /* ************* Linear search ********************************************* */
  {
    for (rxHandle = CAN_HL_RX_BASIC_STARTINDEX(channel); rxHandle < CAN_HL_RX_BASIC_STOPINDEX(channel); rxHandle++)
    {
      if( idRaw0 == CanGetRxId0(rxHandle) )
      {
#   if (kCanNumberOfUsedCanRxIdTables > 1)
        if( idRaw1 == CanGetRxId1(rxHandle) )
#   endif
        {
#   if (kCanNumberOfUsedCanRxIdTables > 2)
          if( idRaw2 == CanGetRxId2(rxHandle) )
#   endif
          {
#   if (kCanNumberOfUsedCanRxIdTables > 3)
            if( idRaw3 == CanGetRxId3(rxHandle) )
#   endif
            {
#   if (kCanNumberOfUsedCanRxIdTables > 4)
              if( idRaw4 == CanGetRxId4(rxHandle) )
#   endif
              {
#   if defined( C_ENABLE_MIXED_ID ) 
#    if defined( C_HL_ENABLE_IDTYPE_IN_ID )
#    else
                /* verify ID type, if not already done with the ID raw */
                if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CanGetRxIdType(rxHandle))
#    endif
#   endif
                {
                  /* message found in id table */
                  break;    /* exit loop with index rxHandle */
                }
              }
            }
          }
        }
      }
    }

    if ( rxHandle >= CAN_HL_RX_BASIC_STOPINDEX(channel))     /* no match in linear search detected */
    {
#   if defined( C_ENABLE_NOT_MATCHED_FCT )
      ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#   endif
      goto finishBasicCan;
    }
#   if defined( C_ENABLE_RX_MSG_INDIRECTION )
    else
    {
      rxHandle = CanRxMsgIndirection[rxHandle];       /* indirection for special sort-algoritms */
    }
#   endif
  }
#  endif  /* defined( C_SEARCH_LINEAR ) */

#  if defined( C_SEARCH_HASH )
  /* ************* Hash search ********************************************** */
  {
#   if defined( C_ENABLE_EXTENDED_ID ) 
  /* one or more Extended ID listed */
#    if defined( C_ENABLE_MIXED_ID )
    if((CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) )) == kCanIdTypeExt)
#    endif
#    if (kHashSearchListCountEx > 0)
    {
    /* calculate the logical ID */
#     if defined( C_ENABLE_RX_MASK_EXT_ID )
      idExt          = (CanRxActualId( CAN_HL_P_RX_INFO_STRUCT(channel) ) &  C_MASK_EXT_ID ) | \
                                                                                 ((vuint32)channel << 29);                
#     else
      idExt          = CanRxActualId( CAN_HL_P_RX_INFO_STRUCT(channel) )| ((vuint32)channel << 29); /* PRQA S 0310,3305 */ /* MD_Can_0310,MD_Can_3305_LL */
#     endif

#     if (kHashSearchListCountEx == 1)
      rxHandle       = (CanReceiveHandle)0;
#     else
      winternExt     = idExt + kHashSearchRandomNumberEx;                    
      rxHandle       = (CanReceiveHandle)(winternExt % kHashSearchListCountEx);
#     endif /* (kHashSearchListCountEx == 1) */

#     if ((kHashSearchListCountEx == 1) || (kHashSearchMaxStepsEx == 1))
      if (idExt != CanRxHashIdEx[rxHandle])   
      { 
#      if defined( C_ENABLE_NOT_MATCHED_FCT )
        ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#      endif
        goto finishBasicCan;
      }
#     else /* (kHashSearchListCountEx == 1) || (kHashSearchMaxStepsEx == 1) */

      i_increment = (vuint16)((winternExt % (kHashSearchListCountEx - 1)) + (vuint8)1);          /* ST10-CCAN Keil compiler complains without cast */
      count       = (vsint16)kHashSearchMaxStepsEx - 1;               
  
      while(idExt != CanRxHashIdEx[rxHandle])   
      {
        if(count == (vsint16)0)  
        {
#      if defined( C_ENABLE_NOT_MATCHED_FCT )
          ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#      endif
          goto finishBasicCan;
        }
        count--;
        rxHandle += i_increment;
        if( rxHandle >= (vuint16)kHashSearchListCountEx ) 
        {
          rxHandle -= kHashSearchListCountEx;
        }
      }
#     endif  /* (kHashSearchListCountEx == 1) || (kHashSearchMaxStepsEx == 1) */
      rxHandle = CanRxMsgIndirection[rxHandle+kHashSearchListCount];
    }
#    else /* (kHashSearchListCountEx > 0) */
    {
#     if defined( C_ENABLE_NOT_MATCHED_FCT )
      ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#     endif
      goto finishBasicCan;
    }
#    endif /* (kHashSearchListCountEx > 0) */

#    if defined( C_ENABLE_MIXED_ID )
    else   /* if((CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) )) == kCanIdTypeStd)  */
#    endif
#   endif /* If defined( C_ENABLE_EXTENDED_ID ) */

#   if defined( C_ENABLE_MIXED_ID ) || !defined( C_ENABLE_EXTENDED_ID ) 
#    if (kHashSearchListCount > 0)
    {
      idStd          = ((vuint16)CanRxActualId( CAN_HL_P_RX_INFO_STRUCT(channel) ) | ((vuint16)channel << 11)); /* PRQA S 0310,3305 */ /* MD_Can_0310,MD_Can_3305_LL */   /* calculate the logical ID */

#     if (kHashSearchListCount == 1)
      rxHandle       = (CanReceiveHandle)0;
#     else
      winternStd     = idStd + kHashSearchRandomNumber;
      rxHandle       = (CanReceiveHandle)(winternStd % kHashSearchListCount);
#     endif /* (kHashSearchListCount == 1) */

#     if ((kHashSearchListCount == 1)  || (kHashSearchMaxSteps == 1))
      if (idStd != CanRxHashId[rxHandle])
      {
#      if defined( C_ENABLE_NOT_MATCHED_FCT )
        ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#      endif
        goto finishBasicCan;
      }
#     else /* ((kHashSearchListCount == 1)  || (kHashSearchMaxSteps == 1)) */

      i_increment = (vuint16)((winternStd % (kHashSearchListCount - 1)) + (vuint8)1);
      count       = (vsint16)kHashSearchMaxSteps-1;

    /* type of CanRxHashId table depends on the used type of Id */
      while ( idStd != CanRxHashId[rxHandle])
      {
        if (count == (vsint16)0)
        {
#     if defined( C_ENABLE_NOT_MATCHED_FCT )
          ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#     endif
          goto finishBasicCan;
        }
        count--; 
        rxHandle += i_increment;
        if ( rxHandle >= kHashSearchListCount )
        {
          rxHandle -= kHashSearchListCount;
        }
      }
#     endif /* ((kHashSearchListCount == 1)  || (kHashSearchMaxSteps == 1)) */
      rxHandle = CanRxMsgIndirection[rxHandle];
    }
#    else /* (kHashSearchListCount > 0) */
    {
#     if defined( C_ENABLE_NOT_MATCHED_FCT )
      ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#     endif
      goto finishBasicCan;
    }
#    endif /* (kHashSearchListCount > 0) */
#   endif /* defined( C_ENABLE_MIXED_ID ) || !defined( C_ENABLE_EXTENDED_ID ) */ 
  }
#  endif /* defined( C_SEARCH_HASH ) */

#  if defined( C_SEARCH_INDEX )
  /* ************* index search *********************************************** */
  {
    rxHandle = CAN_RX_INDEX_TBL(channel, (vuint16)(CanRxActualId( CAN_HL_P_RX_INFO_STRUCT(channel)))); /* PRQA S 3689 */ /* MD_Can_3689 */
    if ( rxHandle >= kCanNumberOfRxObjects)     /* no match in index search detected */
    {
#   if defined( C_ENABLE_NOT_MATCHED_FCT )
      ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#   endif
      goto finishBasicCan;
    }
  }
#  endif /* defined( C_SEARCH_INDEX ) */

  /* ************************** handle filtered message ************************************************** */
  {
    assertInternal((rxHandle < kCanNumberOfRxObjects), kCanAllChannels, kErrorRxHandleWrong);  /* PRQA S 3201,3355,3356,3359 */ /* MD_Can_3201,MD_Can_13.7,MD_Can_13.7,MD_Can_13.7 */ /* legal rxHandle ? */

    CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel) = rxHandle;  

#  if defined( C_ENABLE_RX_QUEUE )
    if (CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY ) == kCanHlContinueRx)
#  else
    if (CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_ONLY ) == kCanHlContinueRx)
#  endif
    { 
#  if defined( C_ENABLE_INDICATION_FLAG ) || \
          defined( C_ENABLE_INDICATION_FCT )

      CanHL_IndRxHandle( rxHandle );
      
      ; /* to avoid MISRA warnings */

      return;
#  endif
    }
  }
# else  /* kCanNumberOfRxBasicCANObjects > 0 */
#  if defined( C_ENABLE_NOT_MATCHED_FCT )
  ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#  endif
# endif /* kCanNumberOfRxBasicCANObjects > 0 */

# endif

  goto finishBasicCan;     /* to avoid compiler warning */

/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
finishBasicCan:

  /* make receive buffer free */
  ; /* to avoid MISRA warnings */

  return;    /* to avoid compiler warnings about label without code */

} /* PRQA S 6010,6030,6050 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL */
/* end of BasicCan */
/* CODE CATEGORY 1 END */
/* PRQA L:End_CanBasicCanMsgReceived */
#endif

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/* **************************************************************************
| NAME:             CanFullCanMsgReceived
| CALLED BY:        CanISR()
| PRECONDITIONS:
| INPUT PARAMETERS: internal can chip number
| RETURN VALUES:    none
| DESCRIPTION:      - full can receive
************************************************************************** */
/* PRQA S 2001 End_CanFullCanMsgReceived */ /* MD_Can_2001 */
/* CODE CATEGORY 1 START */
static void CanFullCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle )
{
  CanReceiveHandle   rxHandle; 

# if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  tCanRxInfoStruct    *pCanRxInfoStruct;
# endif  

  #if defined( C_ENABLE_HW_LOOP_TIMER )
  vuint8 canHwLoopRetVal;
  #endif

  CANDRV_SET_CODE_TEST_POINT(0x101);
   
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
# endif

  /* clear complete flag */
  Can->CRBRCF[CanLL_BitIndex(rxObjHandle-kCanRxBufOffset)] = CanLL_ClearBitRS(rxObjHandle-kCanRxBufOffset);
  
  CanLL_RxTmpBuf[canHwChannel].Id         = mBufId(rxObjHandle);      /* PRQA S 3689 */ /* MD_Can_3689 */
  CanLL_RxTmpBuf[canHwChannel].Dlc        = mBufDlc(rxObjHandle);     /* PRQA S 3689 */ /* MD_Can_3689 */
  CanLL_RxTmpBuf[canHwChannel].u.iData[0] = mBufiData(rxObjHandle,0); /* PRQA S 3689 */ /* MD_Can_3689 */
  CanLL_RxTmpBuf[canHwChannel].u.iData[1] = mBufiData(rxObjHandle,1); /* PRQA S 3689 */ /* MD_Can_3689 */
  
  /* Two conditions lead to a situation where the complete flag is set here:
      1) a new message was received while copying data to the temporary SW buffer
      2) the flag could not be cleared in the first place as hw copying to the mailbox was in progress
  
      The process of copying data to the SW buffer is repeated until this flag is 0
      -> copied data is consistent (as flag cannot be cleared when hw copying is still in 
        progress and is set to 1 when the copying of a new message starts (see hw manual)
      -> always the newest data is copied and indicated
  
      Since most overruns will not be detected (only chance is here while accessing the
      buffer), there is no notification of an overrun in this case either. 
  */
  if((Can->CRBRCF[CanLL_BitIndex(rxObjHandle-kCanRxBufOffset)] & CanLL_SLRS(CanLL_BitPosition(rxObjHandle-kCanRxBufOffset))) != 0)
  {
    CanLL_CanTimerStart(kCanLoopRxFcProcess);
    do
    {
      Can->CRBRCF[CanLL_BitIndex(rxObjHandle-kCanRxBufOffset)] = CanLL_ClearBitRS(rxObjHandle-kCanRxBufOffset);
  
      CanLL_RxTmpBuf[canHwChannel].Id         = mBufId(rxObjHandle);      /* PRQA S 3689 */ /* MD_Can_3689 */
      CanLL_RxTmpBuf[canHwChannel].Dlc        = mBufDlc(rxObjHandle);     /* PRQA S 3689 */ /* MD_Can_3689 */
      CanLL_RxTmpBuf[canHwChannel].u.iData[0] = mBufiData(rxObjHandle,0); /* PRQA S 3689 */ /* MD_Can_3689 */
      CanLL_RxTmpBuf[canHwChannel].u.iData[1] = mBufiData(rxObjHandle,1); /* PRQA S 3689 */ /* MD_Can_3689 */
  
  #if defined( C_ENABLE_HW_LOOP_TIMER )
      canHwLoopRetVal = CanLL_CanTimerLoop(kCanLoopRxFcProcess);
    } while((canHwLoopRetVal != 0) && ((Can->CRBRCF[CanLL_BitIndex(rxObjHandle-kCanRxBufOffset)] & CanLL_SLRS(CanLL_BitPosition(rxObjHandle-kCanRxBufOffset))) != 0));
  #else
    } while((Can->CRBRCF[CanLL_BitIndex(rxObjHandle-kCanRxBufOffset)] & CanLL_SLRS(CanLL_BitPosition(rxObjHandle-kCanRxBufOffset))) != 0);
  #endif
    CanLL_CanTimerEnd(kCanLoopRxFcProcess);
  
  #if defined( C_ENABLE_HW_LOOP_TIMER )
    /* do not proceed (no message indication or overrun notification) if data is inconsistent (caused by loop cancellation) */
    if(canHwLoopRetVal == 0)
    { 
      Can->CRBRCF[CanLL_BitIndex(rxObjHandle-kCanRxBufOffset)] = CanLL_ClearBitRS(rxObjHandle-kCanRxBufOffset);
      goto finishRxFullCan;
    }
  #endif
  }

# if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  /* pointer needed for other modules */
  /* PRQA S 3689 5 */ /* MD_Can_3689 */
  pCanRxInfoStruct =  &canRxInfoStruct[channel];
  (pCanRxInfoStruct->pChipMsgObj) = (CanChipMsgPtr)&(CanLL_RxTmpBuf[canHwChannel].Id);
  (pCanRxInfoStruct->pChipData) = (CanChipDataPtr)&(CanLL_RxTmpBuf[canHwChannel].u.bData[0]);
  canRDSRxPtr[channel] = pCanRxInfoStruct->pChipData;
# else
  (canRxInfoStruct[channel].pChipMsgObj) = (CanChipMsgPtr)&(CanLL_RxTmpBuf[canHwChannel].Id);
  (canRxInfoStruct[channel].pChipData) = (CanChipDataPtr)&(CanLL_RxTmpBuf[canHwChannel].u.bData[0]);
  canRDSRxPtr[channel] = canRxInfoStruct[channel].pChipData;
# endif

# if defined( C_ENABLE_CAN_RAM_CHECK )
  if(canComStatus[channel] == kCanDisableCommunication) /* PRQA S 3689 */ /* MD_Can_3689 */ 
  {
    goto finishRxFullCan; /* PRQA S 3689 */ /* MD_Can_3689 */ /* ignore reception */
  }
# endif

# if defined( C_HL_ENABLE_OVERRUN_IN_STATUS )
# else
# endif

# if defined( C_ENABLE_COND_RECEIVE_FCT )
  /* ************************** conditional message receive function  ************************************** */
  if(canMsgCondRecState[channel]==kCanTrue)
  {
    ApplCanMsgCondReceived( CAN_HL_P_RX_INFO_STRUCT(channel) );
  }
# endif

# if defined( C_ENABLE_RECEIVE_FCT )
  /* ************************** call ApplCanMsgReceived() ************************************************** */
  if (APPL_CAN_MSG_RECEIVED( CAN_HL_P_RX_INFO_STRUCT(channel) )==kCanNoCopyData)
  {
     goto finishRxFullCan;
  }
# endif

  /* calculate the message handle to access the generated data for the received message */

  /* brackets to avoid lint info 834 */
  rxHandle = (rxObjHandle - CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel)) /* PRQA S 3689 */ /* MD_Can_3689 */
# if defined( C_SEARCH_HASH )
                         + kHashSearchListCount
                         + kHashSearchListCountEx
# endif
                         + CAN_HL_RX_FULL_STARTINDEX(canHwChannel);

# if defined( C_HL_ENABLE_ADJUST_RXHANDLE )
# endif

# if defined( C_ENABLE_RX_MSG_INDIRECTION ) || \
     defined( C_SEARCH_HASH ) || \
     defined( C_SEARCH_INDEX )
  rxHandle = CanRxMsgIndirection[rxHandle];
# endif

  assertInternal((rxHandle < kCanNumberOfRxObjects), kCanAllChannels, kErrorRxHandleWrong);  /* legal rxHandle ? */

  CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel) = rxHandle;  

# if defined( C_ENABLE_RX_QUEUE )
  if (CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY) == kCanHlContinueRx)
# else
  if (CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_ONLY ) == kCanHlContinueRx)
# endif
  { 
# if defined( C_ENABLE_INDICATION_FLAG ) || \
        defined( C_ENABLE_INDICATION_FCT )

    CanHL_IndRxHandle( rxHandle );

    ; /* to avoid MISRA warnings */

    return;
# endif
  }

  goto finishRxFullCan;     /* to avoid compiler warning */

/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
finishRxFullCan:

  /* make receive buffer free */
  ; /* to avoid MISRA warnings */

  return;    /* to avoid compiler warnings about label without code */
} /* PRQA S 6010,6030,6050 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL */
/* CODE CATEGORY 1 END */
/* PRQA L:End_CanFullCanMsgReceived */

#endif

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )  || \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
# if ( kCanNumberOfRxObjects > 0 )
/* **************************************************************************
| NAME:             CanHL_ReceivedRxHandle
| CALLED BY:        CanBasicCanMsgReceived, CanFullCanMsgReceived
| PRECONDITIONS:
| INPUT PARAMETERS: Handle of received Message to access generated data
| RETURN VALUES:    none
| DESCRIPTION:      DLC-check, Precopy and copy of Data for received message
************************************************************************** */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_RX_QUEUE )
static vuint8 CanHL_ReceivedRxHandle( CAN_CHANNEL_CANTYPE_FIRST tCanRxInfoStruct *pCanRxInfoStruct )
{
#  else
static vuint8 CanHL_ReceivedRxHandle( CAN_CHANNEL_CANTYPE_ONLY )
{
#  endif
#  if !defined( C_ENABLE_RX_QUEUE ) &&\
    defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  tCanRxInfoStruct    *pCanRxInfoStruct;
#  endif

#  if defined( C_ENABLE_COPY_RX_DATA )
#   if C_SECURITY_LEVEL > 20
  CanDeclareGlobalInterruptOldStatus
#   endif
#  endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
# endif

#  if !defined( C_ENABLE_RX_QUEUE ) &&\
    defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  pCanRxInfoStruct =  &canRxInfoStruct[channel]; /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif

#  if defined( C_ENABLE_MULTI_ECU_PHYS )
  if ( (CanRxIdentityAssignment[CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)] & V_ACTIVE_IDENTITY_MSK) == (tVIdentityMsk)0 )
  {
    /* message is not a receive message in the active indentity */
    CANDRV_SET_CODE_TEST_POINT(0x10B);
    return  kCanHlFinishRx;
  }
#  endif

#  if defined( C_ENABLE_DLC_CHECK )  
#   if defined( C_ENABLE_DLC_CHECK_MIN_DATALEN )
  if ( (CanGetRxMinDataLen(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel))) > CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel) ) ) /* PRQA S 0303 */ /* MD_Can_0303_HWaccess */
#   else
  if ( (CanGetRxDataLen(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel))) > CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel) ) )
#   endif
  {
    /* ##RI1.4 - 2.7: Callbackfunction-DLC-Check */
#   if defined( C_ENABLE_DLC_FAILED_FCT )
    ApplCanMsgDlcFailed( CAN_HL_P_RX_INFO_STRUCT(channel) ); 
#   endif  /* C_ENABLE_DLC_FAILED_FCT */
    return  kCanHlFinishRx;
  }
#  endif

#  if defined( C_ENABLE_VARIABLE_RX_DATALEN )
  CanSetVariableRxDatalen (CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel), CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel)));
#  endif

#  if defined( C_ENABLE_GENERIC_PRECOPY )
  if ( APPL_CAN_GENERIC_PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) != kCanCopyData)
  {
    return kCanHlFinishRx;  
  }
#  endif

#  if defined( C_ENABLE_PRECOPY_FCT )
  if ( CanGetApplPrecopyPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)) != V_NULL )    /* precopy routine */
  {
    /* canRxHandle in indexed drivers only for consistancy check in higher layer modules */
    canRxHandle[channel] = CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel); /* PRQA S 3689 */ /* MD_Can_3689 */
    
    if ( CanGetApplPrecopyPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel))( CAN_HL_P_RX_INFO_STRUCT(channel) )==kCanNoCopyData )
    {  /* precopy routine returns kCanNoCopyData:   */
      return  kCanHlFinishRx;
    }                      /* do not copy data check next irpt */
  }
#  endif

#  if defined( C_ENABLE_COPY_RX_DATA )
  /* no precopy or precopy returns kCanCopyData : copy data -- */
  /* copy via index ------------------------------------------- */
  if ( CanGetRxDataPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)) != V_NULL )      /* copy if buffer exists */
  {
    /* copy data --------------------------------------------- */
#   if C_SECURITY_LEVEL > 20
    CanNestedGlobalInterruptDisable();
#   endif
    CANDRV_SET_CODE_TEST_POINT(0x107);
#   if defined( C_ENABLE_COPY_RX_DATA_WITH_DLC )
    if ( CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel)) < CanGetRxDataLen(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)) )
    {
#    if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )    
      {
        vuint8 canllidx;
        for(canllidx=0; canllidx<CanRxActualDLC(CAN_HL_P_RX_INFO_STRUCT(channel)); canllidx++)
        {
          CanGetRxDataPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel))[canllidx] = pCanRxInfoStruct->pChipData[canllidx];
        }
      }
#    else
      {
        vuint8 canllidx;
        for(canllidx=0; canllidx<CanRxActualDLC(CAN_HL_P_RX_INFO_STRUCT(channel)); canllidx++)
        {
          CanGetRxDataPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel))[canllidx] = canRxInfoStruct[channel].pChipData[canllidx];
        }
      }
#    endif 
    }
    else
#   endif   /* C_ENABLE_COPY_RX_DATA_WITH_DLC */
    {
#   if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )    
      {
        vuint8 canllidx;
        for(canllidx=0; canllidx<CanGetRxDataLen(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)); canllidx++)
        {
          CanGetRxDataPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel))[canllidx] = pCanRxInfoStruct->pChipData[canllidx];
        }
      }
#   else
      {
        vuint8 canllidx;
        for(canllidx=0; canllidx<CanGetRxDataLen(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)); canllidx++)
        {
          CanGetRxDataPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel))[canllidx] = canRxInfoStruct[channel].pChipData[canllidx];
        }
      }
#   endif 
    }
#   if C_SECURITY_LEVEL > 20
    CanNestedGlobalInterruptRestore();
#   endif
  }
#  endif /* ( C_ENABLE_COPY_RX_DATA ) */

  CANDRV_SET_CODE_TEST_POINT(0x105);
  return kCanHlContinueRx;
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* end of CanReceivceRxHandle() */
/* CODE CATEGORY 1 END */

#  if defined( C_ENABLE_INDICATION_FLAG ) || \
     defined( C_ENABLE_INDICATION_FCT )
/* **************************************************************************
| NAME:             CanHL_IndRxHandle
| CALLED BY:        CanBasicCanMsgReceived, CanFullCanMsgReceived
| PRECONDITIONS:
| INPUT PARAMETERS: Handle of received Message to access generated data
| RETURN VALUES:    none
| DESCRIPTION:      DLC-check, Precopy and copy of Data for received message
************************************************************************** */
/* CODE CATEGORY 1 START */
static void CanHL_IndRxHandle( CanReceiveHandle rxHandle )
{
#   if defined( C_ENABLE_INDICATION_FLAG )
#    if C_SECURITY_LEVEL > 20
  CanDeclareGlobalInterruptOldStatus
#    endif
#   endif

#   if defined( C_ENABLE_INDICATION_FLAG )
#    if C_SECURITY_LEVEL > 20
  CanNestedGlobalInterruptDisable();
#    endif
  CanIndicationFlags._c[CanGetIndicationOffset(rxHandle)] |= CanGetIndicationMask(rxHandle);
#    if C_SECURITY_LEVEL > 20
  CanNestedGlobalInterruptRestore();
#    endif
#   endif

#   if defined( C_ENABLE_INDICATION_FCT )
  if ( CanGetApplIndicationPtr(rxHandle) != V_NULL )
  {
    CanGetApplIndicationPtr(rxHandle)(rxHandle);  /* call IndicationRoutine */
  }
#   endif
}
/* CODE CATEGORY 1 END */
#  endif /* C_ENABLE_INDICATION_FLAG || C_ENABLE_INDICATION_FCT  */
# endif /* ( kCanNumberOfRxObjects > 0 ) */
#endif

/* **************************************************************************
| NAME:             CanHL_TxConfirmation
| CALLED BY:        CanISR()
| PRECONDITIONS:
| INPUT PARAMETERS: - internal can chip number
|                   - interrupt ID
| RETURN VALUES:    none
| DESCRIPTION:      - full can transmit
************************************************************************** */
/* PRQA S 2001 End_CanHL_TxConfirmation */ /* MD_Can_2001 */
/* CODE CATEGORY 1 START */
static void CanHL_TxConfirmation( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle)
{
  CanObjectHandle       logTxObjHandle;
  CanTransmitHandle     txHandle;

#if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanSignedTxHandle         queueElementIdx;    /* use as signed due to loop */
  CanSignedTxHandle         elementBitIdx;
  tCanQueueElementType             elem;
  CanDeclareGlobalInterruptOldStatus
#else
# if defined( C_ENABLE_CONFIRMATION_FLAG )
#  if C_SECURITY_LEVEL > 20
  CanDeclareGlobalInterruptOldStatus
#  endif
# endif
#endif

#if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION ) && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
  vuint8 rc;
#endif

  #if defined(C_ENABLE_CANCEL_IN_HW)
  vuint8 canPendingTemp;
  #endif
  #if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel;
  canPhysChannel = mCanLogToPhys(canHwChannel);
  #endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
# endif

  logTxObjHandle = (CanObjectHandle)((vsintx)txObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)); /* PRQA S 3689 */ /* MD_Can_3689 */
  txHandle = canHandleCurTxObj[logTxObjHandle];           /* get saved handle */

  {
    #if defined(C_ENABLE_CANCEL_IN_HW)
    canPendingTemp = Can->ChBS[canPhysChannel].TBSR[txObjHandle-mCanTxBufOffset(canHwChannel)]; /* PRQA S 3689 */ /* MD_Can_3689 */
    #endif
    
    {
      /* clear complete or cancel flag and release the object */
      Can->ChBS[canPhysChannel].TBSR[txObjHandle-mCanTxBufOffset(canHwChannel)] &= ((vuint8) ~kCanSrTxBufMaskPending); /* PRQA S 0277,3689 */ /* MD_Can_0277_negation,MD_Can_3689 */
    }

    /* check associated transmit handle */
    if (txHandle == kCanBufferFree)
    {
      assertInternal (0, channel, kErrorTxHandleWrong);          /* lint !e506 !e774 */
      goto finishCanHL_TxConfirmation;
    }  

#if defined( C_ENABLE_TX_OBSERVE ) || \
    defined( C_ENABLE_CAN_TX_CONF_FCT )
# if defined( C_ENABLE_CANCEL_IN_HW )
    if ((canPendingTemp & kCanSrTxBufMaskComplete) != 0)
# endif
    {
# if defined( C_ENABLE_TX_OBSERVE )
      {
        ApplCanTxObjConfirmed( CAN_CHANNEL_CANPARA_FIRST logTxObjHandle );
      }
# endif

# if defined( C_ENABLE_CAN_TX_CONF_FCT )
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
        txInfoStructConf[channel].Handle  = txHandle; /* PRQA S 3689 */ /* MD_Can_3689 */
#  if defined( C_ENABLE_CAN_TX_CONF_MSG_ACCESS )
        /* PRQA S 3689 1 */ /* MD_Can_3689 */
        txInfoStructConf[channel].pChipMsgObj = (CanChipMsgPtr)&mBufId(txObjHandle);
        txInfoStructConf[channel].pChipData = (CanChipDataPtr)&mBufbData(txObjHandle,0);
#  endif
        APPL_CAN_TX_CONFIRMATION(&txInfoStructConf[channel]); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
    }
#endif /* defined( C_ENABLE_TX_OBSERVE ) || defined( C_ENABLE_CAN_TX_CONF_FCT ) */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
# if defined( C_ENABLE_TX_FULLCAN_OBJECTS )  || \
     defined( C_ENABLE_MSG_TRANSMIT )
    if (txObjHandle != CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel)) /* PRQA S 3689 */ /* MD_Can_3689 */
    {
      canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;                 /* free msg object of FullCAN or LowLevel Tx obj. */
    }
# endif
#else
    canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;                   /* free msg object if queue is not used */
#endif

    if (txHandle != kCanBufferCancel)
    {
#if defined( C_ENABLE_MSG_TRANSMIT )
      if (txObjHandle == CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel)) /* PRQA S 3689 */ /* MD_Can_3689 */
      {
# if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
        APPL_CAN_MSGTRANSMITCONF( CAN_CHANNEL_CANPARA_ONLY );
# endif

        goto finishCanHL_TxConfirmation;
      }
#endif

#if defined( C_ENABLE_MULTI_ECU_PHYS )
      assertInternal(((CanTxIdentityAssignment[txHandle] & V_ACTIVE_IDENTITY_MSK) != (tVIdentityMsk)0 ), 
                                                                channel, kErrorInternalDisabledTxMessage);
#endif

#if defined( C_ENABLE_CONFIRMATION_FLAG )       /* set transmit ready flag  */
# if C_SECURITY_LEVEL > 20
      CanNestedGlobalInterruptDisable();
# endif
      CanConfirmationFlags._c[CanGetConfirmationOffset(txHandle)] |= CanGetConfirmationMask(txHandle);
# if C_SECURITY_LEVEL > 20
      CanNestedGlobalInterruptRestore();
# endif
#endif

#if defined( C_ENABLE_CONFIRMATION_FCT )
      {
        if ( CanGetApplConfirmationPtr(txHandle) != V_NULL )
        {
          (CanGetApplConfirmationPtr(txHandle))(txHandle);   /* call completion routine  */
        }
      }
#endif /* C_ENABLE_CONFIRMATION_FCT */

    } /* end if kCanBufferCancel */
  
#if defined( C_ENABLE_TRANSMIT_QUEUE )
# if defined( C_ENABLE_TX_FULLCAN_OBJECTS ) ||\
     defined( C_ENABLE_MSG_TRANSMIT )
    if (txObjHandle == CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel)) /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
    {
      CanNestedGlobalInterruptDisable();                /* ESCAN00008914 */

      /* PRQA S 3689 2 */ /* MD_Can_3689 */
      for(queueElementIdx = CAN_HL_TXQUEUE_STOPINDEX(channel) - (CanSignedTxHandle)1; 
                               queueElementIdx >= CAN_HL_TXQUEUE_STARTINDEX(channel); queueElementIdx--)
      {
        elem = canTxQueueFlags[queueElementIdx];
        if(elem != (tCanQueueElementType)0) /* is there any flag set in the queue element? */
        {

          CanNestedGlobalInterruptRestore();

          /* start the bitsearch */
          #if defined( C_CPUTYPE_32BIT )
          if((elem & (tCanQueueElementType)0xFFFF0000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
          {
            if((elem & (tCanQueueElementType)0xFF000000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
            {
              if((elem & (tCanQueueElementType)0xF0000000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 28] + 28;
              }
              else /* 0x0F000000 */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 24] + 24;
              }
            }
            else
            {
              if((elem & (tCanQueueElementType)0x00F00000) != (tCanQueueElementType)0)
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 20] + 20;
              }
              else /* 0x000F0000 */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 16] + 16;
              }
            }
          }
          else
          #endif
          {
          #if defined( C_CPUTYPE_32BIT ) 
            if((elem & (tCanQueueElementType)0x0000FF00) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
            {
              if((elem & (tCanQueueElementType)0x0000F000) != (tCanQueueElementType)0) /* PRQA S 1281 */ /* MD_Can_1281 */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 12] + 12;
              }
              else /* 0x00000F00 */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 8] + 8;
              }
            }
            else
          #endif
            {
              if((elem & (tCanQueueElementType)0x000000F0) != (tCanQueueElementType)0)
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 4] + 4;
              }
              else /* 0x0000000F */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem];
              }
            }
          }
          /* PRQA S 3689 1 */ /* MD_Can_3689 */
          txHandle = (CanTransmitHandle)((((CanTransmitHandle)queueElementIdx << kCanTxQueueShift) + (CanTransmitHandle)elementBitIdx) - CAN_HL_TXQUEUE_PADBITS(channel)); 
          {

              /* compute the logical message handle */
              CanNestedGlobalInterruptDisable();
 
              if ( (canTxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) != (tCanQueueElementType)0 )
              {
                canTxQueueFlags[queueElementIdx] &= (tCanQueueElementType)~CanShiftLookUp[elementBitIdx]; /* clear flag from the queue */

                CanNestedGlobalInterruptRestore();  
                canHandleCurTxObj[logTxObjHandle] = txHandle; /* Save hdl of msgObj to be transmitted */
# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
                rc = CanCopyDataAndStartTransmission( CAN_CHANNEL_CANPARA_FIRST txObjHandle, txHandle); 
                if ( rc == kCanTxNotify)
                {
#   if defined ( C_HL_ENABLE_AVOID_REENTRANT_APPLCANCANCELNOTIFICATION )
                  CanNestedGlobalInterruptDisable();
#   endif
                  APPLCANCANCELNOTIFICATION(channel, txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
#   if defined ( C_HL_ENABLE_AVOID_REENTRANT_APPLCANCANCELNOTIFICATION )
                  CanNestedGlobalInterruptRestore();
#   endif
                }
# else       /* C_ENABLE_CAN_CANCEL_NOTIFICATION */
                (void)CanCopyDataAndStartTransmission( CAN_CHANNEL_CANPARA_FIRST txObjHandle, txHandle); 
# endif /* C_ENABLE_CAN_CANCEL_NOTIFICATION */

                goto finishCanHL_TxConfirmation;
              }
              /* meanwhile, the queue is empty. E.g. due to CanOffline on higher level */
              canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;  /* free msg object if queue is empty */
              CanNestedGlobalInterruptRestore();  
              goto finishCanHL_TxConfirmation;
            
          }
          /* no entry found in Queue */
# if defined( CANHL_TX_QUEUE_BIT )
# else
          CanNestedGlobalInterruptDisable();                /* lint !e527 ESCAN00008914 */
                                                 /* unreachable in case of Bit-Queue */
# endif                                                 
        }
      }

      canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;  /* free msg object if queue is empty */
      CanNestedGlobalInterruptRestore();                 /* ESCAN00008914 */
    }
#endif
  /* check for next msg object in queue and transmit it */

/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
finishCanHL_TxConfirmation:
    ;

  }
  return;

} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */
/* END OF CanTxInterrupt */
/* CODE CATEGORY 1 END */
/* PRQA L:End_CanHL_TxConfirmation */

#if defined( C_ENABLE_ECU_SWITCH_PASS )
/* **********************************************************************
* NAME:               CanSetActive
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       none
* DESCRIPTION:        Set the CAN driver into active mode
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetActive( CAN_CHANNEL_CANTYPE_ONLY )
{
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

  canPassive[channel] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
} /* END OF CanSetActive */
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanSetPassive
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       none
* DESCRIPTION:        Set the can driver into passive mode
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPassive( CAN_CHANNEL_CANTYPE_ONLY )
{
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

  canPassive[channel] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */
 
# if defined( C_ENABLE_TRANSMIT_QUEUE )
  /* clear all Tx queue flags: */
  CanDelQueuedObj( CAN_CHANNEL_CANPARA_ONLY ); 
# endif
 
} /* END OF CanSetPassive */
/* CODE CATEGORY 4 END */
#endif /* IF defined( C_ENABLE_ECU_SWITCH_PASS ) */

#if defined( C_ENABLE_OFFLINE )
/* **********************************************************************
* NAME:               CanOnline( CanChannelHandle channel )
* CALLED BY:          netmanagement
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       none
* DESCRIPTION:        Switch on transmit path
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanOnline(CAN_CHANNEL_CANTYPE_ONLY)
{
  CanDeclareGlobalInterruptOldStatus

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif
  {

    CanNestedGlobalInterruptDisable();

    canStatus[channel] |= kCanTxOn; /* PRQA S 3689 */ /* MD_Can_3689 */

#   if defined( C_ENABLE_ONLINE_OFFLINE_CALLBACK_FCT )
    APPL_CAN_ONLINE(CAN_CHANNEL_CANPARA_ONLY);
#   endif
    CanNestedGlobalInterruptRestore();
  }

}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanOffline( CanChannelHandle channel )
* CALLED BY:          netmanagement
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       none
* DESCRIPTION:        Switch off transmit path
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanOffline(CAN_CHANNEL_CANTYPE_ONLY) C_API_3
{
  CanDeclareGlobalInterruptOldStatus

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

  CanNestedGlobalInterruptDisable();

  canStatus[channel] &= kCanTxNotOn; /* PRQA S 3689 */ /* MD_Can_3689 */

# if defined( C_ENABLE_ONLINE_OFFLINE_CALLBACK_FCT )
  APPL_CAN_OFFLINE(CAN_CHANNEL_CANPARA_ONLY);
# endif
  CanNestedGlobalInterruptRestore();

# if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanDelQueuedObj( CAN_CHANNEL_CANPARA_ONLY );
# endif

}
/* CODE CATEGORY 4 END */
#endif /* if defined( C_ENABLE_OFFLINE ) */

#if defined( C_ENABLE_PART_OFFLINE )
/* **********************************************************************
* NAME:               CanSetPartOffline
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          (channel), sendGroup
* RETURN VALUE:       none
* DESCRIPTION:        Switch partial off transmit path
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPartOffline(CAN_CHANNEL_CANTYPE_FIRST vuint8 sendGroup)
{
  CanDeclareGlobalInterruptOldStatus

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

  CanNestedGlobalInterruptDisable();
  canTxPartOffline[channel] |= sendGroup;  /* PRQA S 3689 */ /* MD_Can_3689 */ /* set offlinestate and Save for use of CanOnline/CanOffline */
  CanNestedGlobalInterruptRestore();
}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanSetPartOnline
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          (channel), invSendGroup
* RETURN VALUE:       none
* DESCRIPTION:        Switch partial on transmit path
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPartOnline(CAN_CHANNEL_CANTYPE_FIRST vuint8 invSendGroup)
{
  CanDeclareGlobalInterruptOldStatus

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

  CanNestedGlobalInterruptDisable();
  canTxPartOffline[channel] &= invSendGroup; /* PRQA S 3689 */ /* MD_Can_3689 */
  CanNestedGlobalInterruptRestore();
}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanGetPartMode
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       canTxPartOffline
* DESCRIPTION:        return status of partoffline-Mode
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanGetPartMode(CAN_CHANNEL_CANTYPE_ONLY)
{
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

  return canTxPartOffline[channel]; /* PRQA S 3689 */ /* MD_Can_3689 */
}
/* CODE CATEGORY 4 END */
#endif

/* **************************************************************************
| NAME:             CanGetStatus
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none or channel
| RETURN VALUES:    Bit coded status (more than one status can be set):
|                   kCanTxOn
|                   kCanHwIsStop        
|                   kCanHwIsInit        
|                   kCanHwIsInconsistent
|                   kCanHwIsWarning     
|                   kCanHwIsPassive     
|                   kCanHwIsBusOff      
|                   kCanHwIsSleep       
| DESCRIPTION:      returns the status of the transmit path and the CAN hardware.
|                   Only one of the statusbits Sleep, Busoff, Passiv, Warning is set.
|                   Sleep has the highest priority, error warning the lowerst. 
************************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanGetStatus( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{
#if defined( C_ENABLE_EXTENDED_STATUS )
#endif

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif

#if defined( C_ENABLE_EXTENDED_STATUS )

# if defined( C_ENABLE_SLEEP_WAKEUP )
  /* *************************** verify Sleep mode *********************************** */
  if ( CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY)   )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsSleep ) ); } /* PRQA S 0303,3689 */ /* MD_Can_0303_HWaccess,MD_Can_3689 */

# endif

  /* *************************** verify Stop mode *********************************** */
  if ( CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY)    )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsStop ) ); } /* PRQA S 3689 */ /* MD_Can_3689 */

  /* *************************** verify Busoff *********************************** */
  if ( CanLL_HwIsBusOff(CAN_HW_CHANNEL_CANPARA_ONLY)  )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsBusOff ) ); } /* PRQA S 3689 */ /* MD_Can_3689 */

  /* *************************** verify Error Passiv ***************************** */
  {
    if ( CanLL_HwIsPassive(CAN_HW_CHANNEL_CANPARA_ONLY) )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsPassive ) ); } /* PRQA S 3689 */ /* MD_Can_3689 */
  }

  /* *************************** verify Error Warning **************************** */
  {
    if ( CanLL_HwIsWarning(CAN_HW_CHANNEL_CANPARA_ONLY) )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsWarning ) ); } /* PRQA S 3689 */ /* MD_Can_3689 */
  }
#endif
  return ( VUINT8_CAST (canStatus[channel] & kCanTxOn) ); /* PRQA S 3689 */ /* MD_Can_3689 */

} /* END OF CanGetStatus */
/* CODE CATEGORY 3 END */

/* **************************************************************************
| NAME:             CanSleep
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none or channel
| RETURN VALUES:    kCanOk, if CanSleep was successfull
|                   kCanFailed, if function failed
|                   kCanNotSupported, if this function is not supported
| DESCRIPTION:      disable CAN 
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanSleep(CAN_CHANNEL_CANTYPE_ONLY) /* PRQA S 3206 */ /* MD_Can_3206_UnusedParam */
{
#if defined( C_ENABLE_SLEEP_WAKEUP )
  vuint8         canReturnCode;
#endif

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif
#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL)
  assertUser((canCanInterruptCounter[channel] == (vsintx)0), channel, kErrorDisabledCanInt);    /* PRQA S 3689 */ /* MD_Can_3689 */
#endif

#if defined( C_ENABLE_COND_RECEIVE_FCT )
  /* this has to be done, even if SLEEP_WAKEUP is not enabled */
  canMsgCondRecState[channel] = kCanTrue;
#endif

#if defined( C_ENABLE_SLEEP_WAKEUP )

  assertUser((canStatus[channel] & kCanTxOn) != kCanTxOn, channel, kErrorCanOnline);   /* PRQA S 0303,3689 */ /* MD_Can_0303_HWaccess,MD_Can_3689 */

  {
    assertUser(!CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanStop);     /* PRQA S 0303,3689 */ /* MD_Can_0303_HWaccess,MD_Can_3689 */
    {
    #  if defined(C_MULTIPLE_PHYS_CHANNEL)
      CanChannelHandle canPhysChannel; 
      canPhysChannel = mCanLogToPhys(canHwChannel); /* PRQA S 3689 */ /* MD_Can_3689 */
    #  endif
      canReturnCode = kCanFailed;
    
      /* transit to channel reset mode */
      CanLL_ModeReq_Phys(canPhysChannel,kCanResetMode); /* PRQA S 3689 */ /* MD_Can_3689 */
      if (!CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode)) /* PRQA S 3689 */ /* MD_Can_3689 */
      {
        if (!CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode)) /* PRQA S 3689 */ /* MD_Can_3689 */
        {
          CanLL_CanTimerWait(kCanLoopEnterSleepMode,!CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode)); /* PRQA S 3415 */ /* MD_Can_3415_LL */
        }
      }
    
      /* only go on if reset transition was successful */
      if (CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode))
      {
        /* delete rx pendings (others are not possible after channel reset) */
    #  if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS)
        vuint8 canCount;
    #  endif
    #  if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
        /* clear rx full reception flags */
        for(canCount=0;canCount<kCanNumberOfSharedReg16;canCount++)
        {
          Can->CRBRCF[canCount] = CanLL_ClearBitMaskRS(CanChannelData[canHwChannel].CanRxFcMask[canCount]); /* PRQA S 3689 */ /* MD_Can_3689 */
        }
    #  endif
    #  if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
        /* disable rx fifos to clear pendings, clear interrupt and overrun flags and re-enable fifos again */
        for(canCount=CanChannelData[canHwChannel].CanRxBcStartIndex;canCount<CanChannelData[canHwChannel].CanRxBcStopIndex;canCount++) /* PRQA S 3689 */ /* MD_Can_3689 */
        {
          Can->CRFCR[canCount] &= ((kCanRegSize) ~kCanCrFifoEnable);
          Can->CRFSR[canCount] &= ((kCanRegSize) ~(kCanSrRxFifoIntFlag | kCanSrFifoOverrun));
          Can->CRFCR[canCount] |= kCanCrFifoEnable;
        }
    #  endif
    
        /* transit to channel stop mode (deactivate clock) */
        CanLL_ModeReq_Phys(canPhysChannel,kCanStopMode); /* PRQA S 3689 */ /* MD_Can_3689 */
        if (!CanLL_ModeCheck_Phys(canPhysChannel,kCanStopMode)) /* PRQA S 3689 */ /* MD_Can_3689 */
        {
          if (!CanLL_ModeCheck_Phys(canPhysChannel,kCanStopMode)) /* PRQA S 3689 */ /* MD_Can_3689 */
          {
            CanLL_CanTimerWait(kCanLoopEnterSleepMode,!CanLL_ModeCheck_Phys(canPhysChannel,kCanStopMode)); /* PRQA S 3415 */ /* MD_Can_3415_LL */
          }
        }
    
        /* only go on if stop transition was successful */
        if(CanLL_ModeCheck_Phys(canPhysChannel,kCanStopMode))
        {
          canReturnCode = kCanOk;
    #  if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
    #   if defined (C_ENABLE_LL_CAN_WAKEUP_INTCTRL)
          CanLL_ClearCanWakeupInterruptFlag(canHwChannel); /* PRQA S 3689 */ /* MD_Can_3689 */
    #   endif
    #   if !defined (C_ENABLE_WAKEUP_POLLING) && defined (C_ENABLE_LL_CAN_INTCTRL)
          CanLL_CanWakeupInterruptEnable(canHwChannel, &canCanInterruptOldStatus[canHwChannel]); /* PRQA S 3689 */ /* MD_Can_3689 */
    #   endif
    #   if defined (C_ENABLE_LL_CAN_INTCB) || defined (C_ENABLE_LL_CAN_WAKEUP_INTCB)
          /* ApplCanWakeupInterruptEnable always has to clear the IF and then - only in interrupt configurations - enable the interrupt */
          ApplCanWakeupInterruptEnable(canHwChannel);
    #   endif
    #  endif /* C_ENABLE_LL_WAKEUP_SUPPORT */
        }
      }
    }
  }
  return canReturnCode;
#else
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && \
     defined( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
  return kCanNotSupported;
#endif
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* END OF CanSleep */
/* CODE CATEGORY 4 END */

/* **************************************************************************
| NAME:             CanWakeUp
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none or channel
| RETURN VALUES:    kCanOk, if CanWakeUp was successfull
|                   kCanFailed, if function failed
|                   kCanNotSupported, if this function is not supported
| DESCRIPTION:      enable CAN 
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanWakeUp( CAN_CHANNEL_CANTYPE_ONLY ) /* PRQA S 3206 */ /* MD_Can_3206_UnusedParam */
{
#if defined( C_ENABLE_SLEEP_WAKEUP )
  vuint8         canReturnCode;

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#endif
#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL)
  assertUser((canCanInterruptCounter[channel] == (vsintx)0), channel, kErrorDisabledCanInt);    /* PRQA S 3689 */ /* MD_Can_3689 */
#endif

  {
    {
    #  if defined(C_MULTIPLE_PHYS_CHANNEL)
      CanChannelHandle canPhysChannel; 
      canPhysChannel = mCanLogToPhys(canHwChannel); /* PRQA S 3689 */ /* MD_Can_3689 */
    #  endif
      canReturnCode = kCanFailed;
    
      /* transit to channel reset mode (activate clock) */
      CanLL_ModeReq_Phys(canPhysChannel,kCanResetMode); /* PRQA S 3689 */ /* MD_Can_3689 */
      if (!CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode)) /* PRQA S 3689 */ /* MD_Can_3689 */
      {
        if (!CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode)) /* PRQA S 3689 */ /* MD_Can_3689 */
        {
          CanLL_CanTimerWait(kCanLoopEnterWakeupMode,!CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode)); /* PRQA S 3415 */ /* MD_Can_3415_LL */
        }
      }
    
      /* only go on if reset transition was successful */
      if (CanLL_ModeCheck_Phys(canPhysChannel,kCanResetMode))
      {
        /* transit to channel start mode */
        CanLL_ModeReq_Phys(canPhysChannel,kCanOperationMode); /* PRQA S 3689 */ /* MD_Can_3689 */
        CanLL_CanTimerWait(kCanLoopEnterWakeupMode,!CanLL_ModeCheck_Phys(canPhysChannel,kCanOperationModeCheck)); /* PRQA S 3415,3689 */ /* MD_Can_3415_LL,MD_Can_3689 */
    
        /* only go on if start transition was successful */
        if (CanLL_ModeCheck_Phys(canPhysChannel,kCanOperationModeCheck)) /* PRQA S 3689 */ /* MD_Can_3689 */
        {
          canReturnCode = kCanOk;
        }
      }
    #  if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
    
    #   if !defined(C_ENABLE_WAKEUP_POLLING)
    #    if defined (C_ENABLE_LL_CAN_INTCTRL)
      CanLL_CanWakeupInterruptDisable(canHwChannel, &canCanInterruptOldStatus[canHwChannel]); /* PRQA S 3689 */ /* MD_Can_3689 */
    #    endif
    #    if defined (C_ENABLE_LL_CAN_INTCB)
      /* ApplCanWakeupInterruptDisable has to disable the interrupt */
      ApplCanWakeupInterruptDisable(canHwChannel);
    #    endif
    #   endif
    #  endif /* C_ENABLE_LL_WAKEUP_SUPPORT */
    }
  }
  return canReturnCode;
#else
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && \
     defined( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel; /* PRQA S 3199 */ /* MD_Can_3199_dummy */
# endif
  return kCanNotSupported;
#endif /* C_ENABLE_SLEEP_WAKEUP */
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* END OF CanWakeUp */
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_STOP )
/* **************************************************************************
| NAME:             CanStop
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    kCanOk, if success
|                   kCanFailed, if function failed
|                   kCanNotSupported, if this function is not supported
| DESCRIPTION:      stop CAN-controller
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanStop( CAN_CHANNEL_CANTYPE_ONLY )
{
  vuint8         canReturnCode;

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif
  assertUser((canStatus[channel] & kCanTxOn) != kCanTxOn, channel, kErrorCanOnline);   /* PRQA S 3689 */ /* MD_Can_3689 */

  {
# if defined( C_ENABLE_SLEEP_WAKEUP )
    assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep);   /* PRQA S 0303,3689 */ /* MD_Can_0303_HWaccess,MD_Can_3689 */
# endif
    {
    
      /* start transition within CanInit() is suppressed if CanLL_StopTransition[channel] != kCanStopIdle */
      CanLL_StopTransition[channel] = kCanStopOk; /* PRQA S 3689 */ /* MD_Can_3689 */
      CanInit(CAN_CHANNEL_CANPARA_FIRST lastInitObject[channel]); /* PRQA S 3689 */ /* MD_Can_3689 */
      canReturnCode = CanLL_StopTransition[channel]; /* PRQA S 3689 */ /* MD_Can_3689 */
      CanLL_StopTransition[channel] = kCanStopIdle; /* PRQA S 3689 */ /* MD_Can_3689 */
      
    }
  }
  return canReturnCode;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */
/* CODE CATEGORY 4 END */

/* **************************************************************************
| NAME:             CanStart
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    kCanOk, if success
|                   kCanFailed, if function failed
|                   kCanNotSupported, if this function is not supported
| DESCRIPTION:      restart CAN-controller
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanStart( CAN_CHANNEL_CANTYPE_ONLY )
{
  vuint8         canReturnCode;

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  {
    /* transit to channel start mode */
    CanLL_ModeReq_Log(canHwChannel,kCanOperationMode); /* PRQA S 3689 */ /* MD_Can_3689 */
    CanLL_CanTimerWait(kCanLoopEnterOperationMode,!CanLL_ModeCheck_Log(canHwChannel,kCanOperationModeCheck)); /* PRQA S 3415,3689 */ /* MD_Can_3415_LL,MD_Can_3689 */
    
    if (CanLL_ModeCheck_Log(canHwChannel,kCanOperationModeCheck)) /* PRQA S 3689 */ /* MD_Can_3689 */
    {
      canReturnCode = kCanOk;
    }
    else
    {
      canReturnCode = kCanFailed;
    }
  }
  return canReturnCode;
}
/* CODE CATEGORY 4 END */
#endif /* if defined( C_ENABLE_STOP ) */

#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL)
/* **************************************************************************
| NAME:             CanCanInterruptDisable
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      disables CAN interrupts and stores old interrupt status
************************************************************************** */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 CanCanInterruptDisable( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{
# if defined (C_ENABLE_OSEK_CAN_INTCTRL)

  {
    OsCanCanInterruptDisable(CAN_HW_CHANNEL_CANPARA_ONLY);
  }
# else  /* defined (C_ENABLE_OSEK_CAN_INTCTRL) */

  CanDeclareGlobalInterruptOldStatus
#  if defined( C_HL_ENABLE_CAN_IRQ_DISABLE )
#  endif

  /* local variable must reside on stack or registerbank, switched */
  /* in interrupt level                                            */
  /* disable global interrupt                                      */
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#  endif
  assertUser(canCanInterruptCounter[channel]<(vsint8)0x7f, kCanAllChannels, kErrorIntDisableTooOften);    /* PRQA S 3689 */ /* MD_Can_3689 */

  CanNestedGlobalInterruptDisable();
  if (canCanInterruptCounter[channel] == (vsintx)0) /* PRQA S 3689 */ /* MD_Can_3689 */ /* if 0 then save old interrupt status */
  {
#  if defined( C_HL_ENABLE_CAN_IRQ_DISABLE )
    {
#   if defined( C_ENABLE_SLEEP_WAKEUP )
      assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep);     /* PRQA S 0303,3689 */ /* MD_Can_0303_HWaccess,MD_Can_3689 */
#   endif

      CanLL_CanInterruptDisable(canHwChannel, &canCanInterruptOldStatus[canHwChannel]); /* PRQA S 3689 */ /* MD_Can_3689 */
    }
#  endif
#  if defined( C_ENABLE_INTCTRL_ADD_CAN_FCT )
    ApplCanAddCanInterruptDisable(channel);
#  endif
  }
  canCanInterruptCounter[channel]++;     /* PRQA S 3689 */ /* MD_Can_3689 */ /* common for all platforms */

  CanNestedGlobalInterruptRestore();
# endif  /* C_ENABLE_OSEK_CAN_INTCTRL */
} /* PRQA S 6010 */ /* MD_MSR_STPTH */ 
/* END OF CanCanInterruptDisable */
/* CODE CATEGORY 1 END */

/* **************************************************************************
| NAME:             CanCanInterruptRestore
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      restores the old interrupt status of the CAN interrupt if 
|                   canCanInterruptCounter[channel] is zero
************************************************************************** */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 CanCanInterruptRestore( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{
# if defined (C_ENABLE_OSEK_CAN_INTCTRL)

  {
    OsCanCanInterruptRestore(CAN_HW_CHANNEL_CANPARA_ONLY);
  }
# else  /* defined (C_ENABLE_OSEK_CAN_INTCTRL) */

  CanDeclareGlobalInterruptOldStatus
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
#  endif
  assertUser(canCanInterruptCounter[channel]>(vsintx)0, kCanAllChannels, kErrorIntRestoreTooOften);   /* PRQA S 3689 */ /* MD_Can_3689 */

  CanNestedGlobalInterruptDisable();
  /* restore CAN interrupt */
  canCanInterruptCounter[channel]--; /* PRQA S 3689 */ /* MD_Can_3689 */

  if (canCanInterruptCounter[channel] == (vsintx)0)   /* PRQA S 3689 */ /* MD_Can_3689 */ /* restore interrupt if canCanInterruptCounter=0 */
  {
#  if defined( C_HL_ENABLE_CAN_IRQ_DISABLE )    
    {
#   if defined( C_ENABLE_SLEEP_WAKEUP )
      assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep);   /* PRQA S 0303,3689 */ /* MD_Can_0303_HWaccess,MD_Can_3689 */
#   endif

      CanLL_CanInterruptRestore(canHwChannel, canCanInterruptOldStatus[canHwChannel]); /* PRQA S 3689 */ /* MD_Can_3689 */
    }
#  endif

#  if defined( C_ENABLE_INTCTRL_ADD_CAN_FCT )
    ApplCanAddCanInterruptRestore(channel);
#  endif
  }
  CanNestedGlobalInterruptRestore();
# endif  /* defined (C_ENABLE_OSEK_CAN_INTCTRL) */
} /* PRQA S 6010 */ /* MD_MSR_STPTH */
/* END OF CanCanInterruptRestore */
/* CODE CATEGORY 1 END */
#endif /* defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) */

#if defined( C_ENABLE_MSG_TRANSMIT )
/* **********************************************************************
* NAME:               CanMsgTransmit
* CALLED BY:          CanReceivedFunction
* PRECONDITIONS:      Called in Receive Interrupt
* PARAMETER:          Pointer to message buffer data block; This can either be
*                     a RAM structure data block or the receive buffer in the
*                     CAN chip
* RETURN VALUE:       The return value says that a transmit request was successful
*                     or not
* DESCRIPTION:        Transmit functions for gateway issues (with dynamic
*                     messages). If the transmit buffer is not free, the message
*                     is inserted in the FIFO ring buffer.
*********************************************************************** */
/* Msg(4:3673) The object addressed by the pointer "txMsgStruct" is not modified in this function.
   The use of "const" should be considered to indicate that it never changes. MISRA Rule 81 - no change */
/* CODE CATEGORY 2 START */
# if defined ( V_ENABLE_USED_GLOBAL_VAR )
/* txMsgStruct is located in far memory */
C_API_1 vuint8 C_API_2 CanMsgTransmit( CAN_CHANNEL_CANTYPE_FIRST V_MEMRAM1_FAR tCanMsgTransmitStruct V_MEMRAM2_FAR V_MEMRAM3_FAR *txMsgStruct )       /* PRQA S 3673 */ /* MD_Can_3673 */     /* suppress message about const pointer */
{
# else
C_API_1 vuint8 C_API_2 CanMsgTransmit( CAN_CHANNEL_CANTYPE_FIRST tCanMsgTransmitStruct *txMsgStruct )       /* PRQA S 3673 */ /* MD_Can_3673 */     /* suppress message about const pointer */
{
# endif
  CanDeclareGlobalInterruptOldStatus
  vuint8                   rc;
  CanObjectHandle          txObjHandle;
  CanObjectHandle          logTxObjHandle;

  tTmpData CanLL_TxTmpBuf; /* PRQA S 0759 */ /* MD_Can_0759 */

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  assertUser( (txMsgStruct != V_NULL), channel, kErrorNullPointerParameter);

  CanNestedGlobalInterruptDisable();

  /* --- test on CAN transmit switch --- */
  if ( (canStatus[channel] & kCanTxOn) != kCanTxOn ) /* PRQA S 3689 */ /* MD_Can_3689 */                /* transmit path switched off */
  {
    CanNestedGlobalInterruptRestore();
    return kCanTxFailed;
  }

# if defined( C_ENABLE_CAN_RAM_CHECK )
  if(canComStatus[channel] == kCanDisableCommunication) /* PRQA S 3689 */ /* MD_Can_3689 */ 
  {
    CanNestedGlobalInterruptRestore();
    return(kCanCommunicationDisabled);
  }
# endif

# if defined( C_ENABLE_SLEEP_WAKEUP )
  assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep);    /* PRQA S 0303,3689 */ /* MD_Can_0303,MD_Can_3689 */
# endif
  assertUser(!CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanStop);      /* PRQA S 0303,3689 */ /* MD_Can_0303,MD_Can_3689 */
  
  /* --- check on passive state --- */
# if defined( C_ENABLE_ECU_SWITCH_PASS )
  if ( canPassive[channel] != (vuint8)0) /* PRQA S 3689 */ /* MD_Can_3689 */                            /*  set passive ? */
  {
    CanNestedGlobalInterruptRestore();
#  if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
    APPL_CAN_MSGTRANSMITCONF( CAN_CHANNEL_CANPARA_ONLY );
#  endif
    return (kCanTxOk);
  }
# endif /* C_ENABLE_ECU_SWITCH_PASS */

  /* calculate index for canhandleCurTxObj (logical object handle) */
  logTxObjHandle = (CanObjectHandle)((vsintx)CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)); /* PRQA S 3689 */ /* MD_Can_3689 */

  /* check for transmit message object free --------------------------------- */
  /* MsgObj used?  */
  if (( canHandleCurTxObj[logTxObjHandle] != kCanBufferFree ))    
  {
    CanNestedGlobalInterruptRestore();
    return kCanTxFailed;
  }

  /* Obj, pMsgObject points to is free, transmit msg object: ---------------- */
  /* Save hdl of msgObj to be transmitted */
  canHandleCurTxObj[logTxObjHandle] = kCanBufferMsgTransmit;
  CanNestedGlobalInterruptRestore();

  txObjHandle = CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel); /* PRQA S 3689 */ /* MD_Can_3689 */
  assertHardware( CanLL_TxIsHWObjFree(canHwChannel, txObjHandle ), channel, kErrorTxBufferBusy); /* PRQA S 3689 */ /* MD_Can_3689 */

  CanNestedGlobalInterruptDisable();
  /* Copy all data into transmit object */

  /* If CanTransmit was interrupted by a re-initialization or CanOffline */  
  /* no transmitrequest of this action should be started      */  
  if ((canHandleCurTxObj[logTxObjHandle] == kCanBufferMsgTransmit) && 
                                   ( (canStatus[channel] & kCanTxOn) == kCanTxOn ) ) /* PRQA S 3689 */ /* MD_Can_3689 */
  {  
     /* copy ID */
     mBufId(txObjHandle) = txMsgStruct->IdRaw0; /* PRQA S 0505 */ /* MD_Can_0505 */
     
     /* copy DLC */
     mBufDlc(txObjHandle) = (txMsgStruct->DlcRaw) & kCanDlcMask;
     
     /* copy data */
     CanLL_TxTmpBuf.bData[0] = txMsgStruct->DataFld[0];
     CanLL_TxTmpBuf.bData[1] = txMsgStruct->DataFld[1];
     CanLL_TxTmpBuf.bData[2] = txMsgStruct->DataFld[2];
     CanLL_TxTmpBuf.bData[3] = txMsgStruct->DataFld[3];
     mBufiData(txObjHandle,0) = CanLL_TxTmpBuf.iData[0];
     CanLL_TxTmpBuf.bData[4] = txMsgStruct->DataFld[4];
     CanLL_TxTmpBuf.bData[5] = txMsgStruct->DataFld[5];
     CanLL_TxTmpBuf.bData[6] = txMsgStruct->DataFld[6];
     CanLL_TxTmpBuf.bData[7] = txMsgStruct->DataFld[7];
     mBufiData(txObjHandle,1) = CanLL_TxTmpBuf.iData[1];

     Can->ChBC[mCanLogToPhys(canHwChannel)].TBCR[txObjHandle-mCanTxBufOffset(canHwChannel)] |= kCanCrTxBufReq; /* PRQA S 3689 */ /* MD_Can_3689 */
     
     {
# if defined( C_ENABLE_TX_OBSERVE )
       ApplCanTxObjStart( CAN_CHANNEL_CANPARA_FIRST logTxObjHandle );
# endif
   
       rc = kCanTxOk;                                    
     }
  }  
  else  
  {  
    /* release TxHandle (CanOffline) */
    canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;  
    rc = kCanTxFailed;   
  }  

  CanNestedGlobalInterruptRestore();

  return rc;
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* end of CanMsgTransmit() */
/* CODE CATEGORY 2 END */
#endif

#if defined( C_ENABLE_DYN_TX_OBJECTS )
/* **********************************************************************
* NAME:           CanGetDynTxObj
* PARAMETER:      txHandle - Handle of the dynamic object to reserve
* RETURN VALUE:   kCanNoTxDynObjAvailable (0xFF) - 
*                   object not available
*                 0..F0 - 
*                   Handle to dynamic transmission object
* DESCRIPTION:    Function reserves and return a handle to a dynamic 
*                   transmission object
*
*                 To use dynamic transmission, an application must get
*                 a dynamic object from CAN-driver. 
*                 Before transmission, application must set all attributes 
*                 (id, dlc, data, confirmation function/flag, pretransmission
*                 etc. - as configurated). 
*                 Application can use a dynamic object for one or many
*                 transmissions (as it likes) - but finally, it must
*                 release the dynamic object by calling CanReleaseDynTxObj.
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 CanTransmitHandle C_API_2 CanGetDynTxObj(CanTransmitHandle txHandle ) C_API_3
{
  CanTransmitHandle nTxDynObj;
  CanDeclareGlobalInterruptOldStatus
  CAN_CHANNEL_CANTYPE_LOCAL
  
  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* lint !e568 */
# endif

  nTxDynObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel); /* PRQA S 3382, 0291 */ /* MD_Can_3382,MD_Can_0291 */

  CanNestedGlobalInterruptDisable();
  if ( canTxDynObjReservedFlag[nTxDynObj] != (vuint8)0) /* PRQA S 3689 */ /* MD_Can_3689 */
  {
    CanNestedGlobalInterruptRestore();
    return kCanNoTxDynObjAvailable;
  }
  /*  Mark dynamic object as used  */
  canTxDynObjReservedFlag[nTxDynObj] = 1; /* PRQA S 3689 */ /* MD_Can_3689 */

# if defined( C_ENABLE_CONFIRMATION_FLAG )
  CanConfirmationFlags._c[CanGetConfirmationOffset(txHandle)] &=          /* PRQA S 3689 */ /* MD_Can_3689 */
                            (vuint8)(~CanGetConfirmationMask(txHandle));  /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
  CanNestedGlobalInterruptRestore();

  /* Initialize dynamic object */
# if defined( C_ENABLE_DYN_TX_DATAPTR )  
  canDynTxDataPtr[nTxDynObj] = V_NULL;  /* PRQA S 3689 */ /* MD_Can_3689 */
# endif  
  
  return (txHandle);
} /* PRQA S 6010 */ /* MD_MSR_STPTH */
/* CODE CATEGORY 3 END */

/* **********************************************************************
* NAME:           CanReleaseDynTxObj
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
* RETURN VALUE:   --
* DESCRIPTION:    Function releases dynamic transmission object
*                   which was reserved before (calling CanGetDynTxObj)
*                 
*                 After a transmission of one or more messages is finished,
*                 application must free the reserved resource, formally the
*                 dynamic transmission object calling this function.
*
*                 As the number of dynamic transmission object is limited,
*                 application should not keep unused dynamic transmission
*                 objects for a longer time.
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanReleaseDynTxObj(CanTransmitHandle txHandle) C_API_3
{
  CanTransmitHandle dynTxObj;
  CAN_CHANNEL_CANTYPE_LOCAL
# if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanSignedTxHandle queueElementIdx; /* index for accessing the tx queue */
  CanSignedTxHandle elementBitIdx;  /* bit index within the tx queue element */
  CanTransmitHandle queueBitPos;  /* physical bitposition of the handle */
# endif
  
  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);  
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* lint !e568 */
# endif

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel);  /* PRQA S 3382,0291 */ /* MD_Can_3382,MD_Can_0291 */

  assertInternal((canTxDynObjReservedFlag[dynTxObj] != (vuint8)0), channel, kErrorReleasedUnusedDynObj);  /* PRQA S 3689 */ /* MD_Can_3689 */

# if defined( C_ENABLE_TRANSMIT_QUEUE )
  #if defined( C_ENABLE_INTERNAL_CHECK ) &&\
      defined( C_MULTIPLE_RECEIVE_CHANNEL )
  if (sizeof(queueBitPos) == 1) /* PRQA S 3325 */ /* MD_Can_3201 */
  { /* PRQA S 3201 */ /* MD_Can_3201 */
    assertInternal( ((vuint16)((vuint16)kCanNumberOfTxObjects + (vuint16)CanTxQueuePadBits[kCanNumberOfChannels-1]) <= 256u), kCanAllChannels, kErrorTxQueueTooManyHandle) /*lint !e572 !e506*/
  }
  else
  {
    if (((sizeof(tCanTxQueuePadBits) == 1) && (kCanNumberOfTxObjects > (65536 - 256))) || (sizeof(tCanTxQueuePadBits) > 1)) /* PRQA S 3325 */ /* MD_Can_3201 */
    { /* PRQA S 3201 */ /* MD_Can_3201 */
      assertInternal( ((vuint32)((vuint32)kCanNumberOfTxObjects + (vuint32)CanTxQueuePadBits[kCanNumberOfChannels-1]) <= 65536u), kCanAllChannels, kErrorTxQueueTooManyHandle) /*lint !e572 !e506*/
    }  
  }
  #endif
  queueBitPos  = txHandle + CAN_HL_TXQUEUE_PADBITS(channel);
  queueElementIdx = (CanSignedTxHandle)(queueBitPos >> kCanTxQueueShift); /* get the queue element where to set the flag */
  elementBitIdx  = (CanSignedTxHandle)(queueBitPos & kCanTxQueueMask);   /* get the flag index wihtin the queue element */
  if( (canTxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) != (tCanQueueElementType)0 )
  {
  }
  else
# endif
  {
    if (
# if defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
         (confirmHandle[channel] == txHandle) ||       /* confirmation active ? */
# endif
         (canHandleCurTxObj[(vsintx)CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)] != txHandle) )
    {
      /*  Mark dynamic object as not used  */
      canTxDynObjReservedFlag[dynTxObj] = 0; /* PRQA S 3689 */ /* MD_Can_3689 */
      return(kCanDynReleased);
    }
  }
  return(kCanDynNotReleased);
} /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */
/* CODE CATEGORY 3 END */
#endif /* C_ENABLE_DYN_TX_OBJECTS */

#if defined( C_ENABLE_DYN_TX_ID ) 
# if !defined( C_ENABLE_EXTENDED_ID ) ||\
     defined( C_ENABLE_MIXED_ID )
/* **********************************************************************
* NAME:           CanDynTxObjSetId
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
*                 id -
*                   Id (standard-format) to register with dynamic object
* RETURN VALUE:   --
* DESCRIPTION:    Function registers submitted id (standard format)
*                 with dynamic object referenced by handle.
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetId(CanTransmitHandle txHandle, vuint16 id) C_API_3
{
  CanTransmitHandle dynTxObj;

  CAN_CHANNEL_CANTYPE_LOCAL
  
  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* lint !e568 */
# endif
  assertUser(id <= (vuint16)0x7FF, channel, kErrorWrongId);

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel); /* PRQA S 3382,0291 */ /* MD_Can_3382,MD_Can_0291 */

#  if defined( C_ENABLE_MIXED_ID )
#   if defined( C_HL_ENABLE_IDTYPE_IN_ID )
#   else
  canDynTxIdType[dynTxObj]  = kCanIdTypeStd; 
#   endif
#  endif

  canDynTxId0[dynTxObj] = MK_STDID0(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  if (kCanNumberOfUsedCanTxIdTables > 1)
  canDynTxId1[dynTxObj] = MK_STDID1(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 2)
  canDynTxId2[dynTxObj] = MK_STDID2(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 3)
  canDynTxId3[dynTxObj] = MK_STDID3(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 4)
  canDynTxId4[dynTxObj] = MK_STDID4(id);     /* PRQA S 3689 */ /* MD_Can_3689 */
#  endif
}
/* CODE CATEGORY 2 END */
# endif /* !defined( C_ENABLE_EXTENDED_ID ) || defined( C_ENABLE_MIXED_ID ) */
#endif /* C_ENABLE_DYN_TX_ID */

#if defined( C_ENABLE_DYN_TX_ID ) && \
    defined( C_ENABLE_EXTENDED_ID )
/* **********************************************************************
* NAME:           CanDynTxObjSetExtId
* PARAMETER:      hTxObj -  Handle of dynamic transmission object
*                 idExtHi - Id low word (extended-format) to register with
*                                                         dynamic object
*                 idExtLo - Id high word (extended-format) 
* RETURN VALUE:   --
* DESCRIPTION:    Function registers submitted id (standard format)
*                 with dynamic object referenced by handle.
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetExtId(CanTransmitHandle txHandle, vuint16 idExtHi, vuint16 idExtLo) C_API_3
{
  CanTransmitHandle dynTxObj;
  CAN_CHANNEL_CANTYPE_LOCAL
  
  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* lint !e568 */
# endif
  assertUser(idExtHi <= (vuint16)0x1FFF, channel, kErrorWrongId);                                        

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel); /* PRQA S 3382,0291 */ /* MD_Can_3382,MD_Can_0291 */

# if defined( C_ENABLE_MIXED_ID )
#  if defined( C_HL_ENABLE_IDTYPE_IN_ID )
#  else
  canDynTxIdType[dynTxObj] = kCanIdTypeExt; 
#  endif
# endif

  canDynTxId0[dynTxObj]      = MK_EXTID0( ((vuint32)idExtHi<<16) | (vuint32)idExtLo ); /* PRQA S 3689 */ /* MD_Can_3689 */
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canDynTxId1[dynTxObj]      = MK_EXTID1( ((vuint32)idExtHi<<16) | (vuint32)idExtLo );
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canDynTxId2[dynTxObj]      = MK_EXTID2( ((vuint32)idExtHi<<16) | (vuint32)idExtLo );
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canDynTxId3[dynTxObj]      = MK_EXTID3( ((vuint32)idExtHi<<16) | (vuint32)idExtLo );
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canDynTxId4[dynTxObj]      = MK_EXTID4( ((vuint32)idExtHi<<16) | (vuint32)idExtLo );
# endif
}
/* CODE CATEGORY 2 END */
#endif

#if defined( C_ENABLE_DYN_TX_DLC )
/* **********************************************************************
* NAME:           CanDynTxObjSetDlc
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
*                 dlc -
*                   data length code to register with dynamic object
* RETURN VALUE:   --
* DESCRIPTION:    Function registers data length code with 
*                 dynamic object referenced by submitted handle.
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetDlc(CanTransmitHandle txHandle, vuint8 dlc) C_API_3
{
  CanTransmitHandle dynTxObj;
  CAN_CHANNEL_CANTYPE_LOCAL
  
  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
  
  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* lint !e568 */
# endif
  assertUser(dlc<(vuint8)9, channel, kErrorTxDlcTooLarge);
  
  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel); /* PRQA S 3382,0291 */ /* MD_Can_3382,MD_Can_0291 */
  
# if defined( C_ENABLE_EXTENDED_ID )
  canDynTxDLC[dynTxObj] = MK_TX_DLC_EXT(dlc); /* PRQA S 3689 */ /* MD_Can_3689 */
# else
  canDynTxDLC[dynTxObj] = MK_TX_DLC(dlc);     /* PRQA S 3689 */ /* MD_Can_3689 */
# endif
}
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_DYN_TX_DLC */

#if defined( C_ENABLE_DYN_TX_DATAPTR )
/* **********************************************************************
* NAME:           CanDynTxObjSetData
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
*                 pData -
*                   data reference to be stored in data buffer of dynamic object
* RETURN VALUE:   --
* DESCRIPTION:    Functions stores reference to data registered with
*                 dynamic object.
*                 
*                 The number of byte copied is (always) 8. The number of 
*                 relevant (and consequently evaluated) byte is to be 
*                 taken from function CanDynObjGetDLC.
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetDataPtr(CanTransmitHandle txHandle, void* pData) C_API_3
{
  CanTransmitHandle dynTxObj;
  CAN_CHANNEL_CANTYPE_LOCAL
  
  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle); /* PRQA S 3689 */ /* MD_Can_3689 */
# endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* lint !e568 */
# endif

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel);  /* PRQA S 3382,0291 */ /* MD_Can_3382,MD_Can_0291 */

  canDynTxDataPtr[dynTxObj] = pData; /* PRQA S 3689 */ /* MD_Can_3689 */
}
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_DYN_TX_DATAPTR */

#if defined( C_ENABLE_TX_MASK_EXT_ID )
/* **********************************************************************
* NAME:               CanSetTxIdExtHi
* CALLED BY:          
* PRECONDITIONS:      CanInitPower should already been called.
* PARAMETER:          new source address for the 29-bit CAN-ID
* RETURN VALUE:       -
* DESCRIPTION:        Sets the source address in the lower 8 bit of the
*                     29-bit CAN identifier.
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtHi( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask )
{  
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif
  assertUser(mask <= (vuint8)0x1F, channel, kErrorWrongMask);

  canTxMask0[channel] = (canTxMask0[channel] & MK_EXTID0(0x00FFFFFFUL)) | MK_EXTID0((vuint32)mask<<24);
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canTxMask1[channel] = (canTxMask1[channel] & MK_EXTID1(0x00FFFFFFUL)) | MK_EXTID1((vuint32)mask<<24);
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canTxMask2[channel] = (canTxMask2[channel] & MK_EXTID2(0x00FFFFFFUL)) | MK_EXTID2((vuint32)mask<<24);
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canTxMask3[channel] = (canTxMask3[channel] & MK_EXTID3(0x00FFFFFFUL)) | MK_EXTID3((vuint32)mask<<24);
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canTxMask4[channel] = (canTxMask4[channel] & MK_EXTID4(0x00FFFFFFUL)) | MK_EXTID4((vuint32)mask<<24);
# endif
}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanSetTxIdExtMidHi
* CALLED BY:          
* PRECONDITIONS:      CanInitPower should already been called.
* PARAMETER:          new source address for the 29-bit CAN-ID
* RETURN VALUE:       -
* DESCRIPTION:        Sets the source address in the lower 8 bit of the
*                     29-bit CAN identifier.
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtMidHi( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  canTxMask0[channel] = (canTxMask0[channel] & MK_EXTID0(0xFF00FFFFUL)) | MK_EXTID0((vuint32)mask<<16);   /* lint !e572 */
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canTxMask1[channel] = (canTxMask1[channel] & MK_EXTID1(0xFF00FFFFUL)) | MK_EXTID1((vuint32)mask<<16);   /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canTxMask2[channel] = (canTxMask2[channel] & MK_EXTID2(0xFF00FFFFUL)) | MK_EXTID2((vuint32)mask<<16);   /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canTxMask3[channel] = (canTxMask3[channel] & MK_EXTID3(0xFF00FFFFUL)) | MK_EXTID3((vuint32)mask<<16);   /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canTxMask4[channel] = (canTxMask4[channel] & MK_EXTID4(0xFF00FFFFUL)) | MK_EXTID4((vuint32)mask<<16);   /* lint !e572 */
# endif
}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanSetTxIdExtMidLo
* CALLED BY:          
* PRECONDITIONS:      CanInitPower should already been called.
* PARAMETER:          new source address for the 29-bit CAN-ID
* RETURN VALUE:       -
* DESCRIPTION:        Sets the source address in the lower 8 bit of the
*                     29-bit CAN identifier.
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtMidLo( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  canTxMask0[channel] = (canTxMask0[channel] & MK_EXTID0(0xFFFF00FFUL)) | MK_EXTID0((vuint32)mask<<8);    /* lint !e572 */
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canTxMask1[channel] = (canTxMask1[channel] & MK_EXTID1(0xFFFF00FFUL)) | MK_EXTID1((vuint32)mask<<8);    /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canTxMask2[channel] = (canTxMask2[channel] & MK_EXTID2(0xFFFF00FFUL)) | MK_EXTID2((vuint32)mask<<8);    /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canTxMask3[channel] = (canTxMask3[channel] & MK_EXTID3(0xFFFF00FFUL)) | MK_EXTID3((vuint32)mask<<8);    /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canTxMask4[channel] = (canTxMask4[channel] & MK_EXTID4(0xFFFF00FFUL)) | MK_EXTID4((vuint32)mask<<8);    /* lint !e572 */
# endif
}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanSetTxIdExtLo
* CALLED BY:          
* PRECONDITIONS:      CanInitPower should already been called.
* PARAMETER:          new source address for the 29-bit CAN-ID
* RETURN VALUE:       -
* DESCRIPTION:        Sets the source address in the lower 8 bit of the
*                     29-bit CAN identifier.
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtLo( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  canTxMask0[channel] = (canTxMask0[channel] & MK_EXTID0(0xFFFFFF00UL)) | MK_EXTID0((vuint32)mask);     /* lint !e572 */
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canTxMask1[channel] = (canTxMask1[channel] & MK_EXTID1(0xFFFFFF00UL)) | MK_EXTID1((vuint32)mask);     /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canTxMask2[channel] = (canTxMask2[channel] & MK_EXTID2(0xFFFFFF00UL)) | MK_EXTID2((vuint32)mask);     /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canTxMask3[channel] = (canTxMask3[channel] & MK_EXTID3(0xFFFFFF00UL)) | MK_EXTID3((vuint32)mask);     /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canTxMask4[channel] = (canTxMask4[channel] & MK_EXTID4(0xFFFFFF00UL)) | MK_EXTID4((vuint32)mask);    /* lint !e572 */
# endif
}
/* CODE CATEGORY 4 END */
#endif

#if defined( C_ENABLE_TX_OBSERVE )
/* **********************************************************************
* NAME:               CanTxGetActHandle
* CALLED BY:          
* PRECONDITIONS:      
* PARAMETER:          logical hardware object handle
* RETURN VALUE:       handle of the message in the assigned mailbox
* DESCRIPTION:        get transmit handle of the message, which is currently
*                     in the mailbox txHwObject.
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 CanTransmitHandle C_API_2 CanTxGetActHandle( CanObjectHandle logicalTxHdl ) C_API_3
{
  assertUser(logicalTxHdl < kCanNumberOfUsedTxCANObjects, kCanAllChannels, kErrorTxHwHdlTooLarge);

  return (canHandleCurTxObj[logicalTxHdl]);  /* PRQA S 3689 */ /* MD_Can_3689 */     /* lint !e661 */
}
/* CODE CATEGORY 3 END */
#endif

#if defined( C_ENABLE_VARIABLE_RX_DATALEN )
/* **********************************************************************
* NAME:               CanSetVariableRxDatalen
* CALLED BY:          
* PRECONDITIONS:      
* PARAMETER:          rxHandle: Handle of receive Message for which the datalen has
*                               to be changed
*                     dataLen:  new number of bytes, which have to be copied to the 
*                               message buffer.
* RETURN VALUE:       -
* DESCRIPTION:        change the dataLen of a receive message to copy a 
*                     smaller number of bytes than defined in the database.
*                     the dataLen can only be decreased. If the parameter
*                     dataLen is bigger than the statically defined value
*                     the statically defined value will be set.
*********************************************************************** */
/* CODE CATEGORY 1 START */
static void CanSetVariableRxDatalen (CanReceiveHandle rxHandle, vuint8 dataLen)
{
  assertInternal(rxHandle < kCanNumberOfRxObjects, kCanAllChannels, kErrorRxHandleWrong);  /* legal rxHandle ? */
  /* assertion for dataLen not necessary due to runtime check */

  if (dataLen < CanGetRxDataLen(rxHandle))
  {
    canVariableRxDataLen[rxHandle]=dataLen;
  }
  else
  {
    canVariableRxDataLen[rxHandle] = CanGetRxDataLen(rxHandle);
  }
}
/* CODE CATEGORY 1 END */
#endif

#if defined( C_ENABLE_COND_RECEIVE_FCT )
/* **********************************************************************
* NAME:               CanSetMsgReceivedCondition
* CALLED BY:          Application
* PRECONDITIONS:      
* PARAMETER:          -.
* RETURN VALUE:       -
* DESCRIPTION:        The service function CanSetMsgReceivedCondition()
*                     enables the calling of ApplCanMsgCondReceived()
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanSetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((channel < kCanNumberOfChannels), kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  canMsgCondRecState[channel] = kCanTrue;
}
/* CODE CATEGORY 3 END */

/* **********************************************************************
* NAME:               CanResetMsgReceivedCondition
* CALLED BY:          Application
* PRECONDITIONS:      
* PARAMETER:          -
* RETURN VALUE:       -
* DESCRIPTION:        The service function CanResetMsgReceivedCondition()
*                     disables the calling of ApplCanMsgCondReceived()
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanResetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((channel < kCanNumberOfChannels), kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  canMsgCondRecState[channel] = kCanFalse;
}
/* CODE CATEGORY 3 END */

/* **********************************************************************
* NAME:               CanGetMsgReceivedCondition
* CALLED BY:          Application
* PRECONDITIONS:      
* PARAMETER:          -
* RETURN VALUE:       status of Conditional receive function:
*                     kCanTrue : Condition is set -> ApplCanMsgCondReceived 
*                                will be called
*                     kCanFalse: Condition is not set -> ApplCanMsgCondReceived
*                                will not be called
* DESCRIPTION:        The service function CanGetMsgReceivedCondition() 
*                     returns the status of the condition for calling
*                     ApplCanMsgCondReceived()
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanGetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((channel < kCanNumberOfChannels), kCanAllChannels, kErrorChannelHdlTooLarge);
# endif

  return( canMsgCondRecState[channel] );
}
/* CODE CATEGORY 3 END */
#endif

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
/* **********************************************************************
* NAME:           ApplCanChannelDummy
* PARAMETER:      channel
*                 current receive channel
* RETURN VALUE:   ---
* DESCRIPTION:    dummy-function for unused Callback-functions
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 ApplCanChannelDummy( CanChannelHandle channel ) /* PRQA S 3206 */ /* MD_Can_3206 */
{
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;     /* PRQA S 3199 */ /* MD_Can_3199_dummy */ /* to avoid lint warnings */
# endif
}
/* CODE CATEGORY 3 END */
#endif   /* C_MULTIPLE_RECEIVE_CHANNEL */

#if defined( C_MULTIPLE_RECEIVE_CHANNEL ) 
/* **********************************************************************
* NAME:           ApplCanRxStructPtrDummy
* PARAMETER:      rxStruct
*                 pointer of CanRxInfoStruct
* RETURN VALUE:   kCanCopyData 
* DESCRIPTION:    dummy-function for unused Callback-functions
*********************************************************************** */
/* CODE CATEGORY 1 START */
C_API_1 vuint8 C_API_2 ApplCanRxStructPtrDummy( CanRxInfoStructPtr rxStruct ) /* PRQA S 3206 */ /* MD_Can_3206 */
{
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  rxStruct = rxStruct;     /* PRQA S 3199 */ /* MD_Can_3199_dummy */ /* to avoid lint warnings */
# endif
  return kCanCopyData;
}
/* CODE CATEGORY 1 END */

/* **********************************************************************
* NAME:           ApplCanTxHandleDummy
* PARAMETER:      txHandle
*                 transmit handle
* RETURN VALUE:   ---
* DESCRIPTION:    dummy-function for unused Callback-functions
*********************************************************************** */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 ApplCanTxHandleDummy( CanTransmitHandle txHandle ) /* PRQA S 3206 */ /* MD_Can_3206 */
{
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  txHandle = txHandle;     /* PRQA S 3199 */ /* MD_Can_3199_dummy */ /* to avoid lint warnings */
# endif
}
/* CODE CATEGORY 1 END */
#endif   /* C_MULTIPLE_RECEIVE_CHANNEL || C_HL_ENABLE_DUMMY_FCT_CALL */

#if defined( C_ENABLE_RX_QUEUE )
/* **********************************************************************
* NAME:               CanHL_ReceivedRxHandleQueue
* CALLED BY:          CanBasicCanMsgReceived, CanFullCanMsgReceived
* Preconditions:      none
* PARAMETER:          none
* RETURN VALUE:       none
* DESCRIPTION:        Writes receive data into queue or starts further
*                     processing for this message
*********************************************************************** */
/* CODE CATEGORY 1 START */
static vuint8 CanHL_ReceivedRxHandleQueue(CAN_CHANNEL_CANTYPE_ONLY)
{
  CanDeclareGlobalInterruptOldStatus
  tCanRxInfoStruct    *pCanRxInfoStruct;

  CanChipMsgPtr pSrcBuffer;
  CanChipDataPtr pSrcData;
  CanMsgTransmitStructPtrType pDstStruct;
  CanChipDataPtr pDstData;

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);
# endif

  /* Rx Queue is supported with C_HL_ENABLE_RX_INFO_STRUCT_PTR only! */
  pCanRxInfoStruct =  &canRxInfoStruct[channel]; /* PRQA S 3689 */ /* MD_Can_3689 */

  /* if C_ENABLE_APPLCANPRERXQUEUE is not set, a macro ApplCanPreRxQueue has to be provided by the tool */
  /* in case of ranges, ApplCanPreRxQueue has to return kCanCopyData! */
# if defined( C_ENABLE_APPLCANPRERXQUEUE )
  if(ApplCanPreRxQueue(CAN_HL_P_RX_INFO_STRUCT(channel)) == kCanCopyData)
# endif
  {
    /* Disable the interrupts because nested interrupts can take place -
      CAN interrupts of all channels have to be disabled here */
    CanNestedGlobalInterruptDisable();
    if(canRxQueue.canRxQueueCount < kCanRxQueueSize)   /* Queue full ? */
    {
      if (canRxQueue.canRxQueueWriteIndex == (kCanRxQueueSize - 1) )
      {
        canRxQueue.canRxQueueWriteIndex = 0;
      }
      else
      {
        canRxQueue.canRxQueueWriteIndex++;
      }
      canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueWriteIndex].Channel = channel;
      canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueWriteIndex].Handle  = pCanRxInfoStruct->Handle;

      /* initialize pointers */
      pSrcBuffer = pCanRxInfoStruct->pChipMsgObj;
      pSrcData = pCanRxInfoStruct->pChipData;
      pDstStruct = (CanMsgTransmitStructPtrType)&canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueWriteIndex].CanChipMsgObj;
      pDstData = (CanChipDataPtr)&(pDstStruct->DataFld[0]);
      
      /* copy ID */
      pDstStruct->IdRaw0 = pSrcBuffer[0];
      
      /* copy DLC */
      pDstStruct->DlcRaw = (kCanRegSize)(pSrcBuffer[1] & kCanDlcMask);
      
      /* copy data */
      pDstData[0] = pSrcData[0];
      pDstData[1] = pSrcData[1];
      pDstData[2] = pSrcData[2];
      pDstData[3] = pSrcData[3];
      pDstData[4] = pSrcData[4];
      pDstData[5] = pSrcData[5];
      pDstData[6] = pSrcData[6];
      pDstData[7] = pSrcData[7];

      canRxQueue.canRxQueueCount++;
    }
# if defined( C_ENABLE_RXQUEUE_OVERRUN_NOTIFY )
    else
    {
      ApplCanRxQueueOverrun();
    }
# endif
    CanNestedGlobalInterruptRestore();
  } 
# if defined( C_ENABLE_APPLCANPRERXQUEUE )
  else
  {
    /* Call the application call-back functions and set flags */
#  if defined( C_ENABLE_RX_QUEUE_RANGE )
    if (pCanRxInfoStruct->Handle < kCanNumberOfRxObjects )
#  endif
    { 
      return CanHL_ReceivedRxHandle(CAN_CHANNEL_CANPARA_FIRST pCanRxInfoStruct);
    }
  }
# endif
  return kCanHlFinishRx;
}
/* CODE CATEGORY 1 END */

/* **********************************************************************
* NAME:               CanHandleRxMsg
* CALLED BY:          Application
* Preconditions:      none
* PARAMETER:          none
* RETURN VALUE:       none
* DESCRIPTION:        Calls PreCopy and/or Indication, if existent and
*                     set the indication flag
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanHandleRxMsg(void)
{
  CanDeclareGlobalInterruptOldStatus
  CAN_CHANNEL_CANTYPE_LOCAL
  tCanRxInfoStruct        localCanRxInfoStruct;

  while ( canRxQueue.canRxQueueCount != (vuintx)0 )
  {

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    channel = canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueReadIndex].Channel;
# endif

    CAN_CAN_INTERRUPT_DISABLE( channel );

    /* Call the application call-back functions and set flags */
    localCanRxInfoStruct.Handle      = canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueReadIndex].Handle;
    localCanRxInfoStruct.pChipData   = (CanChipDataPtr)&(canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueReadIndex].CanChipMsgObj.DataFld[0]);
    canRDSRxPtr[channel] = localCanRxInfoStruct.pChipData;
    localCanRxInfoStruct.pChipMsgObj = (CanChipMsgPtr) &(canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueReadIndex].CanChipMsgObj); /* PRQA S 0310 */ /* MD_Can_0310 */
    localCanRxInfoStruct.Channel     = channel;

# if defined( C_ENABLE_RX_QUEUE_RANGE )
    switch ( localCanRxInfoStruct.Handle)
    {
#  if defined( C_ENABLE_RANGE_0 )
      case kCanRxHandleRange0: (void)APPLCANRANGE0PRECOPY( &localCanRxInfoStruct ); break;
#  endif
#  if defined( C_ENABLE_RANGE_1 )
      case kCanRxHandleRange1: (void)APPLCANRANGE1PRECOPY( &localCanRxInfoStruct ); break;
#  endif
#  if defined( C_ENABLE_RANGE_2 )
      case kCanRxHandleRange2: (void)APPLCANRANGE2PRECOPY( &localCanRxInfoStruct ); break;
#  endif
#  if defined( C_ENABLE_RANGE_3 )
      case kCanRxHandleRange3: (void)APPLCANRANGE3PRECOPY( &localCanRxInfoStruct ); break;
#  endif
      default:
#  if defined( C_ENABLE_INDICATION_FLAG ) || \
      defined( C_ENABLE_INDICATION_FCT )
             if( CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_FIRST &localCanRxInfoStruct ) == kCanHlContinueRx )
             {
               CanHL_IndRxHandle(localCanRxInfoStruct.Handle);
             }
#  else
             (void) CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_FIRST &localCanRxInfoStruct );
#  endif
             break;
   }
# else
#  if defined( C_ENABLE_INDICATION_FLAG ) || \
      defined( C_ENABLE_INDICATION_FCT )
    if( CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_FIRST &localCanRxInfoStruct ) == kCanHlContinueRx )
    {
      CanHL_IndRxHandle(localCanRxInfoStruct.Handle);
    }
#  else
    (void) CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_FIRST &localCanRxInfoStruct );
#  endif
# endif
    
    CAN_CAN_INTERRUPT_RESTORE( channel );

    CanNestedGlobalInterruptDisable();
    if (canRxQueue.canRxQueueReadIndex == (kCanRxQueueSize - 1) )
    {
      canRxQueue.canRxQueueReadIndex = 0;
    }
    else
    {
      canRxQueue.canRxQueueReadIndex++;
    }
    canRxQueue.canRxQueueCount--;
    CanNestedGlobalInterruptRestore();
  }
  return;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */
/* end of CanHandleRxMsg() */
/* CODE CATEGORY 2 END */

/* **********************************************************************
* NAME:               CanDeleteRxQueue
* CALLED BY:          Application, CAN driver
* Preconditions:      none
* PARAMETER:          none
* RETURN VALUE:       none
* DESCRIPTION:        delete receive queue
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanDeleteRxQueue(void)
{
  CanDeclareGlobalInterruptOldStatus
  
  CanNestedGlobalInterruptDisable();
  canRxQueue.canRxQueueWriteIndex  = (vuintx)0xFFFFFFFF; /* PRQA S 1281 */ /* MD_Can_1281 */
  canRxQueue.canRxQueueReadIndex   = 0;
  canRxQueue.canRxQueueCount       = 0;  
  CanNestedGlobalInterruptRestore();
} /* end of CanDeleteRxQueue() */
/* CODE CATEGORY 4 END */

#endif /* C_ENABLE_RX_QUEUE */

/****************************************************************************/
/*  MISRA deviations                                                        */
/****************************************************************************/
/* Justification for module-specific MISRA deviations:

MD_Can_3436:
Major
  Reason: Compatibility define used here.
  Risk: name conflict.
  Prevention: Code review and compiler check for name conflicts.

MD_Can_3199_dummy:
Redundancy
  Reason: Dummy assignment used to satisfy API parameters that are never used.
  Risk: None.
  Prevention: None.

MD_Can_0715:
Misra Rule 1.1
  Reason: Complex code structure used and not split in modules or functions to make the code compact and efficent.
  Risk: Hard to understand.
  Prevention: Code inspection and multiple configuration aspects used in component test.

MD_Can_0828:
Misra Rule 1.1
  Reason: Nesting of #if statements bigger than 8 depends on configuration aspects.
  Risk: Compiler does not support that.
  Prevention: Used Compilers checked and limitations form ANSI is not relevant.

MD_Can_0857:
Misra Rule 1.1
  Reason: Macros used to make the code compact and efficent.
  Risk: Hard to understand.
  Prevention: Code inspection and multiple configuration aspects used in component test.

MD_Can_0505:
Misra Rule 1.2
  Reason: Assertion prevents dereferencing a NULL pointer
  Risk: Undefined behaviour.
  Prevention: Code inspection.

MD_Can_0277_negation:
Misra Rule 3.1
  Reason: negation of an unsigned value used to mask bits.
  Risk: None.
  Prevention: None.

MD_Can_0277_invalid:
Misra Rule 3.1
  Reason: define a invalid value by use highest value of the given data type.
  Risk: None.
  Prevention: None.

MD_Can_3218:
Misra Rule 8.7
  Reason: The usage of variables depend on configuration aspects and may be used only once, or defined global to improve overview.
  Risk: name conflict.
  Prevention: Compiler optimize and check for name conflicts.

MD_Can_3207:
Misra Rule 8.7
  Reason: The usage of variables depend on configuration aspects and may be used or not once in this particular configuration.
  Risk: unnecessary RAM occupied.
  Prevention: Compiler optimize and check for name conflicts.
  
MD_Can_3408_extLinkage:
Misra Rule 8.8
  Reason: Declaration of generated data is only internal to restrict visibility
  Risk: None.
  Prevention: None.

MD_Can_3447:
Misra Rule 8.8
  Reason: This appears only in internal test configurations.
  Risk: Symbolic conflict for other module.
  Prevention: -
  
MD_Can_3684:
Misra Rule 8.12
  Reason: Arrays declared without size, because size depends on configuration and is unknown here, especially for linktime tables.
  Risk: Data access outside table.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3760_LogToHw:
Misra Rule 10.01
  Reason: Calculating hardware index out of logical need a negative value in calcuation, but result is always positive.
  Risk: Data access out of bounce.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_1281:
Misra Rule 10.6
  Reason: type of casting variable can be configured
  Risk: wrong size of data type could be used
  Prevention: Code inspection.

MD_Can_0303_HWaccess:
Misra Rule 11.3
  Reason: Hardware access need pointer to CAN cell as volatile.
  Risk: Access of unknown memory.
  Prevention: Runtime tests.

MD_Can_0310:
Misra Rule 11.4
  Reason: cast increase performance here.
  Risk: pointer alignment does not fit and wrong memory is accessed.
  Prevention: Code inspection and component test.

MD_Can_0311:
Misra Rule 11.5
  Reason: Const pointer used only for read access. Same macro is used also for none const pointer.
  Risk: None.
  Prevention: None.

MD_Can_0312:
Misra Rule 11.5
  Reason: cast to none volatile pointer is ok here because usage of data is read only here.
  Risk: Upper Layer has to make sure that there is no write access to this data.
  Prevention: Documentation of API.

MD_Can_13.7:
Misra Rule 13.7
  Reason: Result or value is always true or false depend on configuration aspect and used platform specific implementation
  Risk: Incorrect platform specific return will be ignored.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3201:
Misra Rule 14.1
  Reason: Configuration or platform specific dependent unreachable code.
  Risk: Incorrect behavior depend on settings.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_3325:
Misra Rule 14.1
  Reason: This control expression is always true or false depend on configuration aspect and used platform specific implementation.
  Risk: Incorrect behavior depend on settings.
  Prevention: Code inspection and test of the different variants in the component test.
  
MD_Can_3109:
Misra Rule 14.3
  Reason: Empty statements occur multiple times because macros used like functions, and configuration aspects may deactivate complete functionality.
  Risk: Functionality unexpected missing.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_2001:
Misra Rule 14.4
  Reason: 'goto' statement used to optimize code (readability and runtime).
  Risk: Incorrect jump.
  Prevention: Code inspection.

MD_Can_0770:
Misra Rule 14.5
  Reason: 'continue' statement used to optimize code (readability and runtime).
  Risk: Relevant fragments of code not executed.
  Prevention: Code inspection.

MD_Can_14.6:
Misra Rule 14.6
  Reason: multiple break used for optimize code runtime
  Risk: Relevant fragments of code not executed.
  Prevention: Code inspection.

MD_Can_2006:
Misra Rule 14.7
  Reason: Multiple return path used to optimize code (readability and runtime).
  Risk: Return a function too soon.
  Prevention: Code inspection.

MD_Can_1330:
Misra Rule 16.4
  Reason: no impact on functionality, due to different configurations the function paramters can be different
  Risk: traceability could be diffcult 
  Prevention: Code inspection.
  
MD_Can_1334:
Misra Rule 16.4
  Reason: no impact on functionality, due to different configurations the function paramters can be different
  Risk: traceability could be diffcult 
  Prevention: Code inspection.
  
MD_Can_3673:
Misra Rule 16.7
  Reason: no change due to compatibility of the API
  Risk: data could be modified without intention
  Prevention: Code inspection.
  
MD_Can_17.4:
Misra Rule 17.4
  Reason: Pointer arithmetic used multiple times to optimize runtime.
  Risk: Access wrong memory.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_0750:
Misra Rule 18.4
  Reason: Using union type to handel configuration specific data access.
  Risk: Misinterpreted data.
  Prevention: Code inspection.
  
MD_Can_0759:
Misra Rule 18.4
  Reason: Using union type to handle configuration specific data access.
  Risk: Misinterpreted data.
  Prevention: Code inspection.

MD_Can_3412:
Misra Rule 19.4
  Reason: Complex Macros with unrecognised code-fragment used to optimize code runtime.
  Risk: Readability reduced.
  Prevention: Code inspection.

MD_Can_3458:
Misra Rule 19.4
  Reason:Complex Macros with unbraced code statement blocks used to optimize code runtime.
  Risk: Readability reduced.
  Prevention: Code inspection.

MD_Can_3460:
Misra Rule 19.4
  Reason: void used as macro to get configuration specific API.
  Risk: Readability reduced.
  Prevention: Compile test.
  
MD_Can_0841:
Misra Rule 19.6
  Reason:undefine macro for compatibility reasons and re-usage of platform specific code.
  Risk: Meaning of macro is uncertain and may lead to wrong implementation.
  Prevention: Code inspection, compile tests and runtime tests.

MD_Can_3453:
Misra Rule 19.7
  Reason: Complex Macros used to optimize code runtime.
  Risk: Readability reduced.
  Prevention: Code inspection.

MD_Can_0850:
Misra Rule 19.8
  Reason: Macro argument is empty depend on usage of compiler abstraction.
  Risk: None.
  Prevention: Code inspection.

  MD_Can_3410:
Misra Rule 19.10
  Reason: Parameter used in structures that does not allow brackets
  Risk: None atomic parameter lead to compile errors
  Prevention: Used parameter is always atomic depend on usage

MD_Can_0342:
Misra Rule 19.13
  Reason: Glue operator used to abstract AuotSar compiler abstraction
  Risk: Only K&R compiler support glue operator
  Prevention: Compile test show whether compiler accept glue operator

MD_Can_0291:
Misra Rule 21.1
  Reason: "if" query prevents negative arithmetic result
  Risk: index of array could be negative and therefore undefined
  Prevention: Code inspection. 
  
MD_Can_3382:
Misra Rule 21.1
  Reason: "if" query prevents overflow arithmetic result
  Risk: index of array could exceed dimension (due to overflow) and therefore undefined
  Prevention: Code inspection.  
  
MD_Can_3689:
Misra Rule 21.1
  Reason: assertion prevents out of bound indexing
  Risk: undefined behaviour
  Prevention: Code inspection. Index cannot exceed the maximum dimension of the array.
  
MD_Can_1006_LL:
Misra Rule 1.1
  Reason: Compiler specific instructions are used for interrupt control.
  Risk: Portability problems when using another compiler.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_3116_LL:
Misra Rule 3.4
  Reason: Compiler specific pragmas are necessary for correct behaviour.
  Risk: Portability problems when using another compiler.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_3415_LL:
Misra Rule 12.4
  Reason: Runtime optimization by explicitly assigning operand with side effects to the right hand of the && or || operator.
  Risk: Side effects may always be expected.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_3382_LL:
Misra Rule 21.1
  Reason: Values are only used with binary operations.
  Risk: Data may be misinterpreted. 
  Prevention: Code inspection and test of different variants in the component test.

*/

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Rh850RscanHll Erzeugungsgangnummer: 1 */

