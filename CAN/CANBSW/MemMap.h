/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2007 - 2012 by Vector Informatik GmbH.                                           All rights reserved.
 *
 *                Please note, that this file contains example configuration used by the 
 *                MICROSAR BSW. This code may influence the behaviour of the MICROSAR BSW
 *                in principle. Therefore, great care must be taken to verify
 *                the correctness of the implementation.
 *
 *                The contents of the originally delivered files are only examples resp. 
 *                implementation proposals. With regard to the fact that these functions
 *                are meant for demonstration purposes only, Vector Informatik's
 *                liability shall be expressly excluded in cases of ordinary negligence, 
 *                to the extent admissible by law or statute.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  _MemMap.h
 *    Component:  -
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  This File is a template for the MemMap.h
 *                This file has to be extended with the memory section defines for all BSW modules
 *                which where used.
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  MISRA VIOLATIONS
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Joachim Kalmbach              Jk            Vector Informatik
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2007-08-01  Jk                    Initial creation
 *  01.01.00  2007-12-14  Jk                    Component spesific defines filtering added
 *  01.01.02  2008-11-04  Jk                    Component spesific defines filtering added
 *  01.01.03  2008-12-17  Ht                    Improve list of components  (Tp_AsrTpCan,Tp_AsrTpFr,DrvMcu,DrvIcu added)
 *  01.01.04  2009-04-27  Ht                    improve list of components  (Cp_XcpOnCanAsr, Il_AsrIpduM, If_VxFblDcm,
 *                                              If_VxFblVpm_Volvo_ab, DrvFls added)
 *  01.01.05  2009-04-24  Msr                   Renamed J1939_AsrBase as TpJ1939_AsrBase
 *  01.01.06  2009-06-03  Ht                    Improve list of components (Adc, Dio, Gpt, Pwm, Spi, Wdg, Fls, Port, Fim)
 *  01.02.00  2009-08-01  Ht                    Improve list of components (Fee_30_Inst2, Can, ...Sub)
 *                                              Support filtering for RTE
 *  01.02.01  2009-08-18  HH                    replaced C++ comment by C comment
 *  01.02.02  2009-09-02  Lo                    add external Flash driver support
 *  01.02.03  2009-09-12  Lo                    add DrvFls_Mcs12xFslftm01ExtVx
 *                        Ht                    Improve list of components (CanTrcv_30_Tja1040dio,
 *                                                Eth, EthTrcv, EthIf, SoAd, TcpIp, EthSM)
 *  01.03.00  2009-10-30  Ht                    support R8: change EthTrcv to EthTrcv_30_Canoeemu
 *                                              support EthTrcv_30_Dp83848
 *                                              change CanTrcv_30_Xdio to CanTrcv_30___Your_Trcv__
 *                                              change CanTrcv_30_Tja1040dio to CanTrcv_30_Tja1041
 *                                              change name FrTrcv to FrTrcv_30_Tja1080dio
 *                        Lo                    add Cp_AsrXcp
 *                        Ht                    add Cp_XcpOnFrAsr
 *  01.03.01  2010-01-13  Ht                    support SysService_AsrCal
 *  01.03.02  2010-02-15  Ht                    support SysService_SswRcs_Daimler, SysService_Tls, Tp_Http, 
 *                                                      SysService_Dns, SysService_Json, DrvTrans_GenericLindioAsr
 *                        Lo                    add Diag_AsrDem for all oems
 *                                              rename internal variables and filtermethods
 *  01.04.00  2010-03-04  Ht                    change name FrTrcv_30_Tja1080dio to FrTrcv_30_Tja1080
 *  01.04.01  2010-03-10  Ht                    support DrvTrans_GenericFrAsr, DrvTrans_As8223FrspiAsr, DrvEep and If_AsrIfEa
 *  01.04.02  2010-04-07  Lo                    change IfFee to real components and add If_AsrIfWdV85xNec01Sub
 *  01.04.03  2010-06-11  Ht                    add CanTrcv_30_Tja1043
 *                        Lo                    add Il_AsrIpduMEbBmwSub
 *  01.04.04  2010-08-24  Ht                    add CanTrcv_30_Tle62512G, DrvEep_XAt25128EAsr, Tp_AsrTpFrEbBmwSub
 *  01.05.00  2010-08-24  Ht                    support R10:
 *                                              change LinTrcv_30_Tle7259dio to LinTrcv_30_Tle7259
 *  01.05.01  2010-10-14  Ht                    add VStdLib, SysService_SswScc, SysService_IpBase, SysService_Crypto
 *  01.05.02  2010-10-20  Ht                    support comments for Package Merge Tool
 *  01.05.03  2010-11-03  Ht                    add SysService_E2eLibTttechSub, SysService_E2ePwTttechSub
 *  01.05.04  2010-11-16  Ht                    add SysService_Exi, DrvTrans_Int6400EthAsr, Cdd_AsrCdd_Fiat, Diag_AsrDem_Fiat
 *  01.05.05  2010-12-17  Ht                    add SysService_AsrSchM, DrvEep_XXStubAsr, DrvIcu_Tms570Tinhet01ExtVx
 *                                                  DrvWd_XTle4278gEAsr, DrvWd_XXStubAsr
 *  01.05.06  2011-02-17  Ht                    add DrvEed, SysService_AsrBswM
 *  01.05.07  2011-03-04  Ht                    add DrvTrans_Tja1055CandioAsr
 *                                              rename CanTrcv_30_Tja1040dio to CanTrcv_30_Tja1040
 *                                              add SysService_XmlEngine
 *  01.05.08  2011-09-20  Ht                    add Monitoring_AsrDlt and Monitoring_GenericMeasurement
 *                                              add DrvFls_XXStubAsr,
 *                                              If_AsrIfFeeV85xNec05Sub, If_AsrIfFeeV85xNec06Sub, If_AsrIfFeeV85xNec07Sub
 *                                              SysService_AsrWdMTttechSub and If_AsrIfWdTttechSub
 *  01.05.09  2011-12-19  Ht                    add If_AsrIfFeeTiSub, Nm_AsrNmDirOsek
 *                                              add Tp_IpV4, Tp_IpV6
 *                                              add Monitoring_RuntimeMeasurement
 *                                              add DrvI2c
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#undef MEM_VENDOR_ID
#undef MEM_AR_MAJOR_VERSION
#undef MEM_AR_MINOR_VERSION
#undef MEM_AR_PATCH_VERSION
#undef MEM_SW_MAJOR_VERSION
#undef MEM_SW_MINOR_VERSION
#undef MEM_SW_PATCH_VERSION

#define MEM_VENDOR_ID        (30u)
#define MEM_AR_MAJOR_VERSION (1u)                      /* part of Autosare release 3.0.1 */
#define MEM_AR_MINOR_VERSION (1u)
#define MEM_AR_PATCH_VERSION (0u)

#define MEM_SW_MAJOR_VERSION (1u)
#define MEM_SW_MINOR_VERSION (5u)
#define MEM_SW_PATCH_VERSION (9u)

#define MEMMAP_ERROR

/* Package Merger: Start Section MemMapModuleList */




/**********************************************************************************************************************
 *  CANNM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef CANNM_START_SEC_CODE
    #undef CANNM_START_SEC_CODE                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CODE                              /* mapped to default code section */
#endif
#ifdef CANNM_STOP_SEC_CODE
    #undef CANNM_STOP_SEC_CODE                          /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CODE                               /* default code stop section */
#endif

#ifdef CANNM_START_SEC_APPL_CODE
    #undef CANNM_START_SEC_APPL_CODE                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CODE                              /* mapped to default code section */
#endif
#ifdef CANNM_STOP_SEC_APPL_CODE
    #undef CANNM_STOP_SEC_APPL_CODE                     /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CODE                               /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef CANNM_START_SEC_CONST_8BIT
    #undef CANNM_START_SEC_CONST_8BIT                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_8BIT                        /* mapped to default const section */
#endif
#ifdef CANNM_STOP_SEC_CONST_8BIT
    #undef CANNM_STOP_SEC_CONST_8BIT                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

#ifdef CANNM_START_SEC_CONST_32BIT
    #undef CANNM_START_SEC_CONST_32BIT                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_32BIT                       /* mapped to default const section */
#endif
#ifdef CANNM_STOP_SEC_CONST_32BIT
    #undef CANNM_STOP_SEC_CONST_32BIT                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

#ifdef CANNM_START_SEC_CONST_UNSPECIFIED
    #undef CANNM_START_SEC_CONST_UNSPECIFIED            /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_UNSPECIFIED                 /* mapped to default const section */
#endif
#ifdef CANNM_STOP_SEC_CONST_UNSPECIFIED
    #undef CANNM_STOP_SEC_CONST_UNSPECIFIED             /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

/* Postbuild CFG CONST sections */

#ifdef CANNM_START_SEC_PBCFG
    #undef CANNM_START_SEC_PBCFG                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_PBCFG                       /* mapped to default postbuild section */
#endif
#ifdef CANNM_STOP_SEC_PBCFG
    #undef CANNM_STOP_SEC_PBCFG                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

#ifdef CANNM_START_SEC_PBCFG_ROOT
    #undef CANNM_START_SEC_PBCFG_ROOT                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_PBCFG                       /* mapped to default postbuild section */
#endif
#ifdef CANNM_STOP_SEC_PBCFG_ROOT
    #undef CANNM_STOP_SEC_PBCFG_ROOT                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#ifdef CANNM_START_SEC_VAR_NOINIT_8BIT
    #undef CANNM_START_SEC_VAR_NOINIT_8BIT              /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_NOINIT_8BIT                   /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_NOINIT_8BIT
    #undef CANNM_STOP_SEC_VAR_NOINIT_8BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

#ifdef CANNM_START_SEC_VAR_NOINIT_UNSPECIFIED
    #undef CANNM_START_SEC_VAR_NOINIT_UNSPECIFIED       /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_NOINIT_UNSPECIFIED            /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #undef CANNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED        /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

/* VAR FAST NOINIT sections */

#ifdef CANNM_START_SEC_VAR_FAST_NOINIT_8BIT
    #undef CANNM_START_SEC_VAR_FAST_NOINIT_8BIT         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_FAST_NOINIT_8BIT              /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_FAST_NOINIT_8BIT
    #undef CANNM_STOP_SEC_VAR_FAST_NOINIT_8BIT          /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

#ifdef CANNM_START_SEC_VAR_FAST_NOINIT_16BIT
    #undef CANNM_START_SEC_VAR_FAST_NOINIT_16BIT        /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_FAST_NOINIT_16BIT             /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_FAST_NOINIT_16BIT
    #undef CANNM_STOP_SEC_VAR_FAST_NOINIT_16BIT         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

#ifdef CANNM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #undef CANNM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED  /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED       /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #undef CANNM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED   /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

/* VAR FAST ZERO INIT sections */

#ifdef CANNM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #undef CANNM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED      /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #undef CANNM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED  /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                                  /* default var stop section */
#endif

/**********************************************************************************************************************
 *  CANNM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  NM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef NM_START_SEC_CODE
# undef NM_START_SEC_CODE                               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                                 /* mapped to default code section */
#endif
#ifdef NM_STOP_SEC_CODE
# undef NM_STOP_SEC_CODE                                /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE                                  /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

#ifdef NM_START_SEC_CONST_8BIT
# undef NM_START_SEC_CONST_8BIT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_8BIT                           /* mapped to default const section */
#endif
#ifdef NM_STOP_SEC_CONST_8BIT
# undef NM_STOP_SEC_CONST_8BIT                          /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                                 /* default const stop section */
#endif

#ifdef NM_START_SEC_CONST_32BIT
# undef NM_START_SEC_CONST_32BIT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_32BIT                          /* mapped to default const section */
#endif
#ifdef NM_STOP_SEC_CONST_32BIT
# undef NM_STOP_SEC_CONST_32BIT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                                 /* default const stop section */
#endif

#ifdef NM_START_SEC_CONST_UNSPECIFIED
# undef NM_START_SEC_CONST_UNSPECIFIED                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED                    /* mapped to default const section */
#endif
#ifdef NM_STOP_SEC_CONST_UNSPECIFIED
# undef NM_STOP_SEC_CONST_UNSPECIFIED                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                                 /* default const stop section */
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#ifdef NM_START_SEC_VAR_NOINIT_8BIT
# undef NM_START_SEC_VAR_NOINIT_8BIT                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_8BIT                      /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_NOINIT_8BIT
# undef NM_STOP_SEC_VAR_NOINIT_8BIT                     /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

#ifdef NM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef NM_START_SEC_VAR_NOINIT_UNSPECIFIED             /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED               /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef NM_STOP_SEC_VAR_NOINIT_UNSPECIFIED              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

/* VAR FAST NOINIT sections */

#ifdef NM_START_SEC_VAR_FAST_NOINIT_8BIT
# undef NM_START_SEC_VAR_FAST_NOINIT_8BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_NOINIT_8BIT                 /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_FAST_NOINIT_8BIT
# undef NM_STOP_SEC_VAR_FAST_NOINIT_8BIT                /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

#ifdef NM_START_SEC_VAR_FAST_NOINIT_16BIT
# undef NM_START_SEC_VAR_FAST_NOINIT_16BIT              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_NOINIT_16BIT                /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_FAST_NOINIT_16BIT
# undef NM_STOP_SEC_VAR_FAST_NOINIT_16BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

#ifdef NM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# undef NM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED          /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# undef NM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

/* VAR FAST ZERO INIT sections */

#ifdef NM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# undef NM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED     /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED       /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# undef NM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED      /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

/**********************************************************************************************************************
 *  NM END
 *********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* VStdLib start MemMap.inc                                                                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------- Code ---------------------------------------------------------------------------*/

#ifdef VSTDLIB_START_SEC_CODE                             /* VStdLib code */
# undef VSTDLIB_START_SEC_CODE                            /* PRQA S 0841 */
# define START_SEC_CODE                                   /* mapped to default code section */
#endif
#ifdef VSTDLIB_STOP_SEC_CODE
# undef VSTDLIB_STOP_SEC_CODE                             /* PRQA S 0841 */
# define STOP_SEC_CODE
#endif

/*---------------------------------- Const --------------------------------------------------------------------------*/

#ifdef VSTDLIB_START_SEC_CONST_UNSPECIFIED               /* VStdLib const */
# undef VSTDLIB_START_SEC_CONST_UNSPECIFIED              /* PRQA S 0841 */
# define START_SEC_CONST_UNSPECIFIED                     /* mapped to default const section */
#endif
#ifdef VSTDLIB_STOP_SEC_CONST_UNSPECIFIED  
# undef VSTDLIB_STOP_SEC_CONST_UNSPECIFIED               /* PRQA S 0841 */
# define STOP_SEC_CONST
#endif

/*---------------------------------- RAM ----------------------------------------------------------------------------*/

#ifdef VSTDLIB_START_SEC_VAR_NOINIT_UNSPECIFIED          /* VStdLib var */
# undef VSTDLIB_START_SEC_VAR_NOINIT_UNSPECIFIED         /* PRQA S 0841 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED                /* mapped to default noinit var section */
#endif
#ifdef VSTDLIB_STOP_SEC_VAR_NOINIT_UNSPECIFIED  
# undef VSTDLIB_STOP_SEC_VAR_NOINIT_UNSPECIFIED          /* PRQA S 0841 */
# define STOP_SEC_VAR 
#endif

/*-------------------------------------------------------------------------------------------------------------------*/
/* VStdLib end MemMap.inc                                                                                            */
/*-------------------------------------------------------------------------------------------------------------------*/



/* Package Merger: Stop Section MemMapModuleList */

/*------------------------------GLOBAL-SECTIONS-----------------------------*/
/* Check code sections */
#if ( (defined CODE_SEC_OPEN)                            && \
     ((defined START_SEC_CODE                          ) || \
      (defined START_SEC_CODE_FAST                     ) || \
      (defined START_SEC_CODE_ISR                      )    \
      ))
    #error "MemMap.h: Close the former code segment before opening a new one."
#endif

/* Check const sections */
#if ( (defined CONST_SEC_OPEN)                           && \
     ((defined START_SEC_CONST_8BIT                    ) || \
      (defined START_SEC_CONST_16BIT                   ) || \
      (defined START_SEC_CONST_32BIT                   ) || \
      (defined START_SEC_CONST_UNSPECIFIED             ) || \
      (defined START_SEC_CONST_FAST_8BIT               ) || \
      (defined START_SEC_CONST_FAST_16BIT              ) || \
      (defined START_SEC_CONST_FAST_32BIT              ) || \
      (defined START_SEC_CONST_FAST_UNSPECIFIED        ) || \
      (defined START_SEC_CONST_PBCFG                   )    \
      ))
    #error "MemMap.h: Close the former const segment before opening a new one."
#endif

/* Check data sections */
#if ( (defined VAR_SEC_OPEN)                             && \
     ((defined START_SEC_VAR_INIT_8BIT                 ) || \
      (defined START_SEC_VAR_INIT_16BIT                ) || \
      (defined START_SEC_VAR_INIT_32BIT                ) || \
      (defined START_SEC_VAR_INIT_UNSPECIFIED          ) || \
      (defined START_SEC_VAR_NOINIT_8BIT               ) || \
      (defined START_SEC_VAR_NOINIT_16BIT              ) || \
      (defined START_SEC_VAR_NOINIT_32BIT              ) || \
      (defined START_SEC_VAR_NOINIT_UNSPECIFIED        ) || \
      (defined START_SEC_VAR_ZERO_INIT_8BIT            ) || \
      (defined START_SEC_VAR_ZERO_INIT_16BIT           ) || \
      (defined START_SEC_VAR_ZERO_INIT_32BIT           ) || \
      (defined START_SEC_VAR_ZERO_INIT_UNSPECIFIED     ) || \
      (defined START_SEC_VAR_FAST_INIT_8BIT            ) || \
      (defined START_SEC_VAR_FAST_INIT_16BIT           ) || \
      (defined START_SEC_VAR_FAST_INIT_32BIT           ) || \
      (defined START_SEC_VAR_FAST_INIT_UNSPECIFIED     ) || \
      (defined START_SEC_VAR_FAST_NOINIT_8BIT          ) || \
      (defined START_SEC_VAR_FAST_NOINIT_16BIT         ) || \
      (defined START_SEC_VAR_FAST_NOINIT_32BIT         ) || \
      (defined START_SEC_VAR_FAST_NOINIT_UNSPECIFIED   ) || \
      (defined START_SEC_VAR_FAST_ZERO_INIT_8BIT       ) || \
      (defined START_SEC_VAR_FAST_ZERO_INIT_16BIT      ) || \
      (defined START_SEC_VAR_FAST_ZERO_INIT_32BIT      ) || \
      (defined START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED)    \
      ))
    #error "MemMap.h: Close the former variable segment before opening a new one."
#endif



/*------------------------------GLOBAL-START-SECTIONS------------------------------*/

/* Code section */
#ifdef START_SEC_CODE                          
    #define CODE_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CODE                          
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_CODE_FAST                     
    #define CODE_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CODE_FAST                     
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_CODE_ISR                      
    #define CODE_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CODE_ISR                      
    #undef MEMMAP_ERROR
#endif




/* Const section */
#ifdef START_SEC_CONST_8BIT                    
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_8BIT                    
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_CONST_16BIT                   
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_16BIT                   
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_CONST_32BIT                   
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_32BIT                   
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_CONST_UNSPECIFIED             
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_UNSPECIFIED             
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_CONST_FAST_8BIT               
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_FAST_8BIT               
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_CONST_FAST_16BIT              
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_FAST_16BIT              
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_CONST_FAST_32BIT              
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_FAST_32BIT              
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_CONST_FAST_UNSPECIFIED        
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_FAST_UNSPECIFIED        
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_CONST_PBCFG                   
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_PBCFG                   
    #undef MEMMAP_ERROR
#endif




/* Var section */
#ifdef START_SEC_VAR_INIT_8BIT                 
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_INIT_8BIT                 
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_INIT_16BIT                
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_INIT_16BIT                
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_INIT_32BIT                
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_INIT_32BIT                
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_INIT_UNSPECIFIED          
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_INIT_UNSPECIFIED          
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_NOINIT_8BIT               
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOINIT_8BIT               
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_NOINIT_16BIT              
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOINIT_16BIT              
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_NOINIT_32BIT              
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOINIT_32BIT              
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_NOINIT_UNSPECIFIED        
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_NOINIT_UNSPECIFIED        
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_ZERO_INIT_8BIT            
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_ZERO_INIT_8BIT            
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_ZERO_INIT_16BIT           
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_ZERO_INIT_16BIT           
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_ZERO_INIT_32BIT           
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_ZERO_INIT_32BIT           
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_ZERO_INIT_UNSPECIFIED     
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_ZERO_INIT_UNSPECIFIED     
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_FAST_INIT_8BIT            
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_INIT_8BIT            
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_FAST_INIT_16BIT           
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_INIT_16BIT           
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_FAST_INIT_32BIT           
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_INIT_32BIT           
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_FAST_INIT_UNSPECIFIED     
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_INIT_UNSPECIFIED     
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_FAST_NOINIT_8BIT          
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_NOINIT_8BIT          
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_FAST_NOINIT_16BIT         
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_NOINIT_16BIT         
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_FAST_NOINIT_32BIT         
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_NOINIT_32BIT         
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_FAST_NOINIT_UNSPECIFIED   
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_NOINIT_UNSPECIFIED   
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_FAST_ZERO_INIT_8BIT       
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_ZERO_INIT_8BIT       
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_FAST_ZERO_INIT_16BIT      
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_ZERO_INIT_16BIT      
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_FAST_ZERO_INIT_32BIT      
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_ZERO_INIT_32BIT      
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #define VAR_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#endif



/*------------------------------GENERAL-STOP-SECTIONS-------------------------------*/

/*default segment for Code*/
#ifdef STOP_SEC_CODE
    #undef CODE_SEC_OPEN
/* Enter here a #pragma command for closing the specified section */
/* This should switch back to the default section */
/*    #pragma */
    #undef STOP_SEC_CODE
    #undef MEMMAP_ERROR
#endif

/*default segment for Constants*/
#ifdef STOP_SEC_CONST
    #undef CONST_SEC_OPEN
/* Enter here a #pragma command for closing the specified section */
/* This should switch back to the default section */
/*    #pragma */
    #undef STOP_SEC_CONST
    #undef MEMMAP_ERROR
#endif

/*default segment for Datas*/
#ifdef STOP_SEC_VAR
    #undef VAR_SEC_OPEN
/* Enter here a #pragma command for closing the specified section */
/* This should switch back to the default section */
/*    #pragma */
    #undef STOP_SEC_VAR
    #undef MEMMAP_ERROR
#endif


#ifdef MEMMAP_ERROR
    #error "MemMap.h, wrong pragma command"
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  END OF FILE: MemMap.h
 *********************************************************************************************************************/
