/**************************** .FILE_HEADER_BEGIN *****************************
 .FILE; [ LINAPP1c1.c]
 .Author; [ Chen Yudong]
 .Date; 2017/10/12
 .Update Time; 13:37:47
 .**************   Change History ********************************************* 
 .V2.0 (Release Date:2017-4-3)
 .1.Creation
 .V2.1 (Release Date:2017-4-6)
 .1.Add u32GetValue Interface in LINAPP.C.
 .2.Add u32GetValue Interface in LINAPP.h.
 .V2.2 (Release Date:2017-4-8)
 .1.Add vClearMessCnt Interface in LINAPP.C.
 .***************************************************************************** 
 .Gen File Name: Geely GE12_LIN_V1.31_20170624.xlsx
****************************** .FILE_HEADER_END ******************************/

#ifndef LINAPP_H
#define LINAPP_H
#ifndef LINAPP
#define ext extern
#else
#define ext
#endif

typedef enum
{/* All receive signals...*/
     /* Signals from PM25_1...*/
     LIN_nu16L_PM25_InDen=0,
     LIN_nu16L_PM25_OutDen,
     LIN_nu16L_PM25_AirInQLevel,
     LIN_nu16L_PM25_AirOutQLevel,
     LIN_nu16L_PM25_Sts,
     LIN_nu16L_PM25_ErrSts,
     LIN_nu16L_PM25_MsgRollingCount,
     LIN_nu16PM25_1_LIN_Response_Error,
     /*  Error code... */
     LINAPP_nu16Max
} LIN_tenu16VarNum;

typedef enum
{
     LINAPP_nu32ErrorCode = 0,
      LINAPP_nu32Msg1stRecSucFlg,/*When Receive Message successfully, flag will set 1*/
     LINAPP_nu32Max
} LIN_tenu32VarNum;

typedef enum
{/* All frame Definition*/
     LINAPP_nPM25_1=0,
     LINAPP_nMsgMax
} LINAPP_tenbiRecevMsgNum;



/* Main export function...*/
ext void LINAPP_vReset(void);
ext void LINAPP_vMain_10ms(void);
ext void LINAPP_vClrValue(LIN_tenu16VarNum enIndex);

ext uint16 LINAPP_u16GetValue(LIN_tenu16VarNum enIndex);
ext uint32 LINAPP_u32GetValue(LIN_tenu32VarNum enIndex);
ext uint16 LINAPP_vClearMessCnt(void);
/* End of the file...*/
#undef ext
#endif


