/*******************************************************************************
| Module Name: CAN CCL
| File Name: LINCCL.h
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2015 Huizhou Desay SV Automotive Co., Ltd.    All rights reserved.
|
| This software is copyright protected and proprietary to Desay SV Automotive Co., Ltd.
| Desay SV Automotive Co., Ltd grants to you only those rights as set out in the
| license conditions. All other rights remain with Desay SV Automotive Co., Ltd.
|
| REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
|-------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Name                                  Company
| ---------------------     ---------------------------------------
| Liu Fuguang                           Desay SV Automotive Co., Ltd
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver         Author               Description
| ----------  -------  -------------  -------------------------------------------------
| 2016-07-19  1.00        Liu Fuguang          First implementation

********************************************************************************/

#ifndef LINCCL_H
#define LINCCL_H

#ifndef LINCCL_C
  #define ext extern
#else
  #define ext
#endif

/*this is for uint8 type variables*/
typedef enum LINCCL_enu16VarNumber
{
	LINCCL_nu16EnableSleep = 0,
	LINCCL_nu16Max
}LINCCL_tenu16VarNumber;

/**************************** .BLOCK_COMMENT_BEGIN ***************************
* EXPORT INTERFACE FUNCTION PROTOTYPES
*
* In this section declare
* - all system global function prototypes of your module. This is a copy of
*   the function definitions without the header template.
***************************** .BLOCK_COMMENT_END *****************************/

ext void LINCCL_vReset(void);
ext void LINCCL_vMain(void);
ext uint16 LINCCL_u16GetValue(LINCCL_tenu16VarNumber enIndex);
void LINCCL_vTickCntCallBack(void);

#undef ext
#endif
