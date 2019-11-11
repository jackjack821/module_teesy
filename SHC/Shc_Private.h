/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [Seat Heating Control 													]
*-----------------------------------------------------------------------------
  .FILE   [ SHC_Private.h                                                   ]
*-----------------------------------------------------------------------------

 VersCCP  Date        		Author            Change                      
 -----------------------------------------------------------------------------
 Rev001   10/4/2015         Luo Xindian     	  Create module.                    

*****************************************************************************/

#ifndef SHC_PRIVATE_H
#define  SHC_PRIVATE_H

/*****************************************************************************
*Macro define
******************************************************************************/
/* seat heat request on signal, 1--on, 0 --off*/
#define SHC_u8SeatHeatOn			(1u)
#define SHC_u8SeatHeatOff			(0u)

/* seat heat LED on signal, 0--on, 1--off*/
#define SHC_u8SeatHeatLedOn			(0u)
#define SHC_u8SeatHeatLedOff			(1u)

/*Get value from other modules*/
/* example3: define all module external interface functions and defines
   ----------------------------------------------------- */
#define   SHC_u8Valid 				SHC_au8Array[SHC_nu8Valid]
#define 	SHC_u8SwVersion			SHC_au8Array[SHC_nu8SwVersion]
#define   SHC_u8ErrorCode			SHC_au8Array[SHC_nu8ErrorCode]
#define 	SHC_u8LastStateDr			SHC_au8Array[SHC_nu8LastStateDr]
#define 	SHC_u8LastStatePs			SHC_au8Array[SHC_nu8LastStatePs]
#define 	SHC_u8DisplayDr			SHC_au8Array[SHC_nu8DisplayDr]
#define 	SHC_u8DisplayPs			SHC_au8Array[SHC_nu8DisplayPs]
#define 	SHC_u8LeftSeatHeatCtrlTimer		SHC_au8Array[SHC_nu8LeftSeatHeatCtrlTimer]
#define 	SHC_u8RightSeatHeatCtrlTimer	SHC_au8Array[SHT_nu8RightSeatHeatCtrlTimer]

#define SHCGetCcpForceBit(index)	((SHC_CcpForceFlag>>index)&0x01)
#define SHCSetCcpForceBit(index)	(SHC_CcpForceFlag=SHC_CcpForceFlag|(0x01<<index))
#define SHCClrCcpForceBit(index)	(SHC_CcpForceFlag=SHC_CcpForceFlag&(~(0x01<<index)))
#define SHCClrCcpForceByte(void)	(SHC_CcpForceFlag=0)
/*****************************************************************************
* End of check if informations are already included
******************************************************************************/
#endif                                  /* ifndef SHC_PRIVATE_H */
/*****************************************************************************
* EOF: SHC_Private.h
******************************************************************************/
