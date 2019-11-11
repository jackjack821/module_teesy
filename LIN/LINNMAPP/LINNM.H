/**************************** .FILE_HEADER_BEGIN *****************************
 .FILE; [ LINNM.h]
 .Author; [ Liu Fuguang]
 .Date; 2016/12/30
 .Update Time; 11:43:29
 .Gen File Name: SX11P_LIN_V1.0_2016-12-29.xlsx
****************************** .FILE_HEADER_END ******************************/

#ifndef LINNM_H
#define LINNM_H
#ifndef LINNM
#define ext extern
#else
#define ext
#endif

typedef enum
{/* All receive signals...*/
     LINNM_nu16NmState = 0,
     LINNM_nu16CommunicationEnable,
     LINNM_nu16Max
} LINNM_tenu16VarNum;

enum
{
	LINNM_nWake,
	LINNM_nSleep
};
/* Main export function...*/
ext void LINNM_vReset(void);
ext void LINNM_vMain_1ms(void);
ext void LINNM_vMain_10ms(void);
ext void LINNM_vMain_20ms(void);
ext uint16 LINNM_u16GetValue(LINNM_tenu16VarNum enIndex);
ext void LINNM_vDiagReqTx(uint8 u8DiagEnable,uint8 u8TxDataLen,uint8 u8NAD,uint8 * au8TxData);


/* End of the file...*/
#undef ext
#endif


