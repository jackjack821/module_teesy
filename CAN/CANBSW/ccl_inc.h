/**************************** .FILE_HEADER_BEGIN *****************************

*-----------------------------------------------------------------------------
  .REVISION_LIST  (Will be filled by PVCS)
   Archive: $Log:

  Rev 1.0    WangYang
  Creation.

****************************** .FILE_HEADER_END ******************************/
#ifndef NM_CALLBACK_H
#define	NM_CALLBACK_H

#include "General.h"

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
                                        /* General definitions and datatypes */

/* Foreign headerfiles */


/* Own headerfiles */



/**************************** .BLOCK_COMMENT_BEGIN ***************************
* EXPORT INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define helpful macros for easy data access and for a comfortable function
*   use, if necessary
* - define all global define-constants of your module
* - define all global type definitions of your module
* - declare all system global ROM-constants
* - declare all system global variables of your module
***************************** .BLOCK_COMMENT_END *****************************/


void Ccl_Nm_EnableTxPath( uint8 a );

void ApplCbdWrpStateChange( uint8 a, uint8 b , uint8 c );

void ApplRepeatMsgInd( uint8 a );




#endif

