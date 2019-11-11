/***************************************************************************************************
                                       RDC PROCESS
  .File Name: RDC_Type.h
  
  .Description: Thie file is used to define the special type.

  --------------------------------------------------------------------------------------------------
  Version     Date            Author            Change

  --------------------------------------------------------------------------------------------------
  Rev 1.0     2014/11/27      Xu Xianglin     	The first version            
***************************************************************************************************/

#ifndef RDC_TYPE_H
#define RDC_TYPE_H


/*The following is the result value of sensors and motor feedback*/
typedef enum 
{
	RDC_nu8Request = 0,
	RDC_nu8Display,
	RDC_nu8Feedback,
	RDC_nu8IceDisplayFlag,
	RDC_nu8ErrorCode, 
	RDC_nu8SwVersion,  
	RDC_nu8Max                    
}RDC_tenu8VarNumber;


typedef enum
{
    RDC_nFeedbackUnstable,
    RDC_nErrorMax    
}RDC_tenu8ErrorType;

typedef struct
{
    uint8 u8Flag;
    uint8 u8Command;
    uint8 u16ControlValueHigh;  
    uint8 u16ControlValueLow;    
}RDC_tstCcpControlInput;


typedef enum
{
	RDC_nDiagSetRdcRequest,
    RDC_nPtsSetRdcRequest,
	RDC_nCcpForceMax
}CcpControl_Rdc;
#endif                              
/***************************************************************************************************
* EOF: Rdc_Type.h
***************************************************************************************************/
