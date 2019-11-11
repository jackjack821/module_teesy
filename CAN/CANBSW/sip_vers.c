/*---------------------------------------------------------------------------- 
 * License information:
 *   -    Serialnumber:       CBD1500751
 *   - Date of license:       2016-01-29
  ----------------------------------------------------------------------------
 * Software is licensed for:
 * Desay SV Automotive Co., Ltd.
 * Package: CBD Geely SLP1
 * Micro: R7F7010233AFP
 * Compiler: Green Hills 6.1.4
  ---------------------------------------------------------------------------*/
/*  --------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  --------------------------------------------------------------------------
 *
 *  Description:  
 *  1) Check that all currently compiled files in the system have the correct 
 *     versions according to the delivered software integration package (SIP).
 *  2) Provide the SIP version as ROM constants for e.g. diagnostic purposes.
 *
 *  Usage hints:
 *    If a compiler error occurs within this file, a wrong version
 *    for the notified module has been detected. 
 *    Please check, if
 *    a) The module is part of your project and the include path is 
 *       set correct (if not, the compiler may assume 0 for the 
 *       version number comparison)
 *    b) The used module may have an incorrect version for this
 *       project. Proof carefully, if a newer (or older) version
 *       of the notified component is already available on your site
 *       and an erroneous version mixup had occurred. See the required
 *       module's main and bugfix version above of the error message.
 *    c) This may be the wrong SIP version check file for the project.
 *       Proof carefully, if the file has been exchanged together with
 *       the latest change of a component (e.g. an bugfix delivery), 
 *       too.
 *    In case none of the above mention points is true, please contact 
 *    your Vector's contact person for further help.
 *
 *  Background information:
 *    Each Vector software component checks its own header
 *    and code files for version consistency. With this, a version  
 *    mixup within each component could be detected during compilation.
 *    To detect the mixup of different components in a project, too,
 *    this version check file has been introduced.
  ---------------------------------------------------------------------------*/


#include "v_inc.h"

#if defined (VGEN_ENABLE_IL_VECTOR)
# include "il_inc.h"
#endif
#if defined (VGEN_ENABLE_LIN_TP)
# include "dtl_inc.h"
#endif
/* Include sequence: include nmh.h before nmh_can.h is included */
#if defined (VGEN_ENABLE_NMHIGH)
# include "nmh.h"
#endif
#if defined (VGEN_ENABLE_TPJ1939_ASRBAM)
# include "J1939Tp_Types.h"
#endif

#if defined (VGEN_ENABLE_LIN_TP)
# if defined ( DTL_PROCESSING_COOKED )
#  define TPLIN_COOCKEDMASTECU_VERSION                       TPLIN_COOCKEDSLAVECU_VERSION
#  define TPLIN_COOCKEDMASTECU_RELEASE_VERSION               TPLIN_COOCKEDSLAVECU_RELEASE_VERSION
# endif

# if defined ( DTL_PROCESSING_RAW )
#  define TPLIN_RAWMASTECU_VERSION                           TPLIN_COOCKEDSLAVECU_VERSION
#  define TPLIN_RAWMASTECU_RELEASE_VERSION                   TPLIN_COOCKEDSLAVECU_RELEASE_VERSION
# endif
#endif

/*----------------------------------------------------------------------------
  DrvCan_Rh850RscanHll
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_CAN_DRV)
# include "can_def.h"
#endif

/*----------------------------------------------------------------------------
  Nm_AsrNmCan
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_NM_ASR_CAN)
# include "CanNm.h"
#endif

/*----------------------------------------------------------------------------
  Nm_AsrNmIf
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_NM_ASR_IF)
# include "Nm.h"
#endif

/*----------------------------------------------------------------------------
  VStdLib_Rh850
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_VSTDLIB)
# include "vstdlib.h"
#endif


/*----------------------------------------------------------------------------
  DrvCan_Rh850RscanHll
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_CAN_DRV)
# if (DRVCAN_SH2RSCANHLL_VERSION != 0x0315)
#  error "DrvCan_Rh850RscanHll: Wrong main/sub version (DRVCAN_SH2RSCANHLL_VERSION) detected for this SIP delivery!"
# endif
# if (DRVCAN_SH2RSCANHLL_RELEASE_VERSION != 0x00)
#  error "DrvCan_Rh850RscanHll: Wrong release version (DRVCAN_SH2RSCANHLL_RELEASE_VERSION) detected for this SIP delivery!"
# endif
#endif

/*----------------------------------------------------------------------------
  Nm_AsrNmCan
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_NM_ASR_CAN)
# if (NM_ASRNMCAN_VERSION != 0x0424)
#  error "Nm_AsrNmCan: Wrong main/sub version (NM_ASRNMCAN_VERSION) detected for this SIP delivery!"
# endif
# if (NM_ASRNMCAN_RELEASE_VERSION != 0x00)
#  error "Nm_AsrNmCan: Wrong release version (NM_ASRNMCAN_RELEASE_VERSION) detected for this SIP delivery!"
# endif
#endif

/*----------------------------------------------------------------------------
  Nm_AsrNmIf
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_NM_ASR_IF)
# if (NM_ASRNMIF_VERSION != 0x0225)
#  error "Nm_AsrNmIf: Wrong main/sub version (NM_ASRNMIF_VERSION) detected for this SIP delivery!"
# endif
# if (NM_ASRNMIF_RELEASE_VERSION != 0x00)
#  error "Nm_AsrNmIf: Wrong release version (NM_ASRNMIF_RELEASE_VERSION) detected for this SIP delivery!"
# endif
#endif

/*----------------------------------------------------------------------------
  VStdLib_Rh850
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_VSTDLIB)
# if (VSTDLIB_RH850_VERSION != 0x0104)
#  error "VStdLib_Rh850: Wrong main/sub version (VSTDLIB_RH850_VERSION) detected for this SIP delivery!"
# endif
# if (VSTDLIB_RH850_RELEASE_VERSION != 0x00)
#  error "VStdLib_Rh850: Wrong release version (VSTDLIB_RH850_RELEASE_VERSION) detected for this SIP delivery!"
# endif
#endif


/*----------------------------------------------------------------------------
  Store SIP version in ROM constants
  ---------------------------------------------------------------------------*/
/* ROM CATEGORY 4 START*/
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kSipMainVersion   = (vuint8)(VGEN_DELIVERY_VERSION_BYTE_0);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kSipSubVersion    = (vuint8)(VGEN_DELIVERY_VERSION_BYTE_1);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kSipBugFixVersion = (vuint8)(VGEN_DELIVERY_VERSION_BYTE_2);
/* ROM CATEGORY 4 END*/

