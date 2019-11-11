/*********************************************************************************************************************/
/*!
 * \file
 * \par      copyright
 * \verbatim
 *  Copyright (c) 2006-2016 by Vector Informatik GmbH. All rights reserved.
 * 
 *  This software is copyright protected and proprietary to Vector Informatik GmbH.
 *  Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *  All other rights remain with Vector Informatik GmbH.
 * \endverbatim
 */
/*  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ComM_Nm.h
 *      Project:  CANbedded Wrapper for AUTOSAR Network Management
 *       Module:  Nm_AsrNmCanWrapperExt
 *    Generator:  -
 *
 *  Description:  Callback header of ComM callback functions
 *                AUTOSAR Release 3
 *                This interface is required by AUTOSAR NM
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Frank Triem                   Tri           Vector Informatik GmbH
 *  Markus Drescher               vismdr        Vector Informatik GmbH
 *  Oliver Hornung                visoh         Vector Informatik GmbH
 *  Markus Schuster               vissrk        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  1.00.00   2006-02-23  Tri     ESCAN00015285 Creation of component
 *  1.01.00   2006-03-10  Tri     ESCAN00015634 Compiler error due to undeclared identifier
 *  1.02.00   2006-04-26  Tri     ESCAN00015863 Type and interrupt lock service compatibility
 *                                ESCAN00016176 CanResetBusXXX interrupted by CAN-Interrupt
 *  2.00.00   2007-06-22  visoh   ESCAN00021192 Adaptation to AUTOSAR NM 2.1
 *                                ESCAN00022964 No changes
 *  2.01.00   2008-01-08  visoh   ESCAN00023947 No changes
 *  3.00.00   2008-03-03  visoh   ESCAN00025876 Adaptation to AUTOSAR NM 3.0
 *  3.01.00   2008-06-18  visoh   ESCAN00027671 No changes
 *  3.01.01   2008-07-01  visoh   ESCAN00028006 No changes
 *  3.01.02   2008-11-17  visoh   ESCAN00031367 No changes
 *  3.02.00   2009-04-07  visoh   ESCAN00031814 Version numbers adapted
 *                                ESCAN00034467 No changes
 *  3.03.00   2010-03-23  visoh   ESCAN00041477 Improvements (MISRA compliance)
 *                                ESCAN00041480 No changes in this file
 *  3.03.01   2010-06-18  visoh   ESCAN00042648 No changes in this file
 *  3.04.00   2011-03-02  visoh   ESCAN00042517 No changes in this file
 *                                ESCAN00042447 No changes in this file
 *  3.05.00   2014-05-03  vissrk  ESCAN00057295 No changes in this file
 *                                ESCAN00074080 No changes in this file
 *  3.06.00   2016-01-15  vismdr  ESCAN00074222 No changes in this file
 *                                ESCAN00074225 No changes in this file
 *                                ESCAN00087040 No changes in this file
 *                                ESCAN00087577 No changes in this file
 *********************************************************************************************************************/

#ifndef COMM_CBK_HEADER
# define COMM_CBK_HEADER

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* BCD coded version defines for necessary header file */
# define NM_ASRNMCANWRAPPEREXT_COMM_NM_VERSION          0x0306u
# define NM_ASRNMCANWRAPPEREXT_COMM_NM_RELEASE_VERSION  0x00u

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/*-------------------- ComM services called by Generic NM --------------------*/

/* Notification that the network management has entered Network Mode */
extern void ComM_Nm_NetworkMode( const NetworkHandleType nmChannelHandle );

/* Notification that the network management has entered Prepare Bus-Sleep Mode */
extern void ComM_Nm_PrepareBusSleepMode( const NetworkHandleType nmChannelHandle );

/* Notification that the network management has entered Bus-Sleep Mode */
extern void ComM_Nm_BusSleepMode( const NetworkHandleType nmChannelHandle );

/* Indication that some nodes in the network have entered the Network Mode */
extern void ComM_Nm_NetworkStartIndication( const NetworkHandleType nmChannelHandle );

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/* Indication that some nodes in the network have entered the Network Mode */
extern void ComM_Nm_RestartIndication( const NetworkHandleType nmChannelHandle );
# endif

# if defined ( NM_LIMP_HOME_INDICATION )
extern void ComM_Nm_LimpHomeIndication( const NetworkHandleType nmChannelHandle );
extern void ComM_Nm_LimpHomeCancelation( const NetworkHandleType nmChannelHandle );
# endif

#endif /* COMM_CBK_HEADER */

/**********************************************************************************************************************
 *  END OF FILE: ComM_Nm.h
 *********************************************************************************************************************/
