/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [Aird, Mixed air control  ]
*-----------------------------------------------------------------------------
  .FILE   [AIRD_Private.h           ]
*-----------------------------------------------------------------------------

 Version 			Date        		Author              Change                      
 -----------------------------------------------------------------------------
 Rev 01.00.00 	2014/11/25     	duzj      		The first version 
 Rev 0100   	2016/06/22     	Li Jiaye   		update the interface   

*****************************************************************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef AIRD_PRIVATE_H
#define AIRD_PRIVATE_H

#define AIRD_SwVersion					(0x0101)

/*****************************************************************************
*Macro define
******************************************************************************/
								
/*Get the value from other modules*****************************************/
#define AIRD_u8GetMmiModeValue()			(MMI_u8GetValue(MMI_nu8AirdModeControl))
#define AIRD_u8GetMmiCtrlValue()			(MMI_u8GetValue(MMI_nu8AirdControl))
#define AIRD_boPowerCheck() 			((uint8)(POW_u16GetValue(POW_nu16AppLowVoltage)|POW_u16GetValue(POW_nu16AppHighVoltage)))
#define AIRD_u16GetOatValue()		(OAT_u16GetValue(OAT_nu16Value))
#define AIRD_u16GetHctValue()		(HCT_u16GetValue(HCT_nu16Value))
#define AIRD_u16GetCcsValue()		(CCS_u16GetValue(CCS_nu16BlowoutTempAvg))

/*******************************ErrorCode define**************************************/

#define Aird_MMIErrCodeSet(ErrorCode)		do{(ErrorCode)|=0x01u;}while(0)
#define Aird_MMIErrCodeClr(ErrorCode)		do{(ErrorCode)&=(~0x01u);}while(0)
#define Aird_OATErrCodeSet(ErrorCode)		do{(ErrorCode)|=0x02u;}while(0)
#define Aird_OATErrCodeClr(ErrorCode)		do{(ErrorCode)&=(~0x02u);}while(0)
#define Aird_POWErrCodeSet(ErrorCode)		do{(ErrorCode)|=0x04u;}while(0)
#define Aird_POWErrCodeClr(ErrorCode)		do{(ErrorCode)&=(~0x04u);}while(0)
#define Aird_HCTErrCodeSet(ErrorCode)		do{(ErrorCode)|=0x08u;}while(0)
#define Aird_HCTErrCodeClr(ErrorCode)		do{(ErrorCode)&=(~0x08u);}while(0)
#define Aird_CCSErrCodeSet(ErrorCode)		do{(ErrorCode)|=0x10u;}while(0)
#define Aird_CCSErrCodeClr(ErrorCode)		do{(ErrorCode)&=(~0x10u);}while(0)


/*******************************Parameter define**************************************/


#define AIRD_nMaxTempValue				(1600u) /*120*10+400*/
#define AIRD_nDefaultOatValue			(600u)	/*20*10+400*/
#define AIRD_nDefaultEvapValue			(400u) 	/*0*10+400*/
#define AIRD_nDefaultHctValue			(1200u) /*80*10+400*/
#define AIRD_nDefaultBlwoutTemp			(700u)	/*30*10+400*/
#define AIRD_nDelayTime					(300u)  /*30s*/
#define AIRD_nRevStartUp				(255u)
#define Aird_SamplingTm                              (15)/*1.5s*/

#endif                                  /* ifndef AIRD_PRIVATE_H*/

/*****************************************************************************
* EOF: AIRD_Private.h
******************************************************************************/

