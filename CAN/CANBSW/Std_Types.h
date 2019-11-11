/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2007 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Std_Types.h
 *    Component:  -
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Provision of Standard Types
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
 *  Heike Honert                  visht         Vector Informatik
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2007-08-01  Jk                    Initial creation
 *  03.00.00  2007-10-10  Jk                    Changes for AUTOSAR 3.0
 *  03.00.01  2007-11-20  Jk                    Version defines for CFG management added
 *  03.01.00  2008-03-05  Jk                    Include order changed
 *  03.02.00  2008-03-18  Jk                    Version defines changed to specification version
 *  03.03.00  2008-06-03  Jk                    changed ModuleId Type in Std_VersionInfoType from uint8 to uint16
 *  03.03.01  2009-11-11  visht                 ESCAN00038201: Support the Standard Type E_PENDING
 *********************************************************************************************************************/

#ifndef STD_TYPES_H
# define STD_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

# include "Platform_Types.h"
# include "Compiler.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : CommonAsr__Common CQComponent : Impl_StdTypes */
# define COMMONASR__COMMON_IMPL_STDTYPES_VERSION 0x0303
# define COMMONASR__COMMON_IMPL_STDTYPES_RELEASE_VERSION 0x01

/* AUTOSAR Software Specification Version Information */
/* AUTOSAR Document version 1.2.0 part of release 3.0.0 */
# define STD_TYPES_AR_MAJOR_VERSION       (1u)
# define STD_TYPES_AR_MINOR_VERSION       (2u)
# define STD_TYPES_AR_PATCH_VERSION       (0u)

/* Component Version Information */
# define STD_TYPES_SW_MAJOR_VERSION       (3u)
# define STD_TYPES_SW_MINOR_VERSION       (3u)
# define STD_TYPES_SW_PATCH_VERSION       (1u) 

# define STD_HIGH     1u /* Physical state 5V or 3.3V */
# define STD_LOW      0u /* Physical state 0V */

# define STD_ACTIVE   1u /* Logical state active */
# define STD_IDLE     0u /* Logical state idle */

# define STD_ON       1u
# define STD_OFF      0u

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* This typedef has been added for OSEK compliance */
# ifndef STATUSTYPEDEFINED
#  define STATUSTYPEDEFINED
#  define E_OK      0u
typedef unsigned char StatusType; /* OSEK compliance */
# endif

# define E_NOT_OK  1u

#  define E_PENDING 2u

typedef uint8 Std_ReturnType;

typedef struct
{
   uint16 vendorID;
   uint16 moduleID;
   uint8  instanceID;
   uint8  sw_major_version;
   uint8  sw_minor_version;
   uint8  sw_patch_version;
} Std_VersionInfoType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
typedef unsigned char 		UINT8;
typedef signed  char 		INT8;
typedef unsigned short		UINT16;/* = unsigned short*/
typedef signed short			INT16;
typedef unsigned long 		UINT32;
typedef signed long		INT32;

/*for application module*/
//typedef UINT8 		uint8;
typedef INT8 		int8;
//typedef UINT16		uint16;
typedef INT16		int16;
//typedef UINT32 		uint32;
typedef	INT32		int32;
typedef UINT8 		Bool;
typedef void			(*vpFun)(void);
typedef void 			(*tFuncPtr)(void);
typedef void 	(*vpFun_u8)(uint8 u8data);
typedef void 	(*vpFun_u16)(uint16 u16data);
typedef void 	(*vpFun_u32_u8)(uint32 u32data,uint8 u8data);
typedef void 	(*vpFunDumy)();
typedef UINT16 (*u16Fun)(void);
typedef UINT16		word;
typedef UINT32 		dword;
typedef UINT8 		byte;

#ifndef NULL
#define NULL	0//((void* )0)
#endif
#define True     	1                      /* Boolean value for True  */
#define False   	 0                      /* Boolean value for False */
#define Yes     	 1                      /* Boolean value for True  */
#define No       	0                      /* Boolean value for False */
#define On      	 1                      /* Boolean value for True  */
#define Off     	 0                      /* Boolean value for False */
#define Ok       	1                      /* Boolean value for True  */
#define NotOk    	0                      /* Boolean value for False */
#define Valid    	1                      /* Boolean value for True  */
#define NotValid   0                      /* Boolean value for False */
#define High		True					/* -CS- 2003/09/25 */
#define Low		False					/* -CS- 2003/09/25 */
#define Start 	True
#define End   	False
#define true		True
#define false		False

#define SYC_ZONES 2 
#if  1//HW_Architecture!= FUJITSU_MB96670 && HW_Architecture!= FUJITSU_MB96690
#define SHRT_MIN        	(-32767-1)      	/* Minimum ("signed") "short" value */
#define USHRT_MAX        	0xFFFF        		/* Maximum "unsigned" "short" value */
#define INT_MAX          	2147483647
#define INT_MIN         	(-2147483647-1)
#define UINT_MAX         	0xFFFFFFFFU
#define LONG_MAX         	2147483647     	/* Maximum ("signed") "long" value */
#define LONG_MIN        	(-2147483647-1) 	/* Minimum ("signed") "long" value */
#define ULONG_MAX        	0xFFFFFFFFU    	/* Maximum "unsigned" "long" value */
#define SCHAR_MIN       	(-128)          		/* Minimum "signed" "char" value */
#define CHAR_MAX         	255
#endif
#define CHAR_BIT         	8              		/* Number of bits in any "char" */
#define CHAR_MIN         	0
#define SCHAR_MAX        	127           		/* Maximum "signed" "char" value */
#define UCHAR_MAX        	255            		/* Maximum "unsigned" "char" value */
#define SHRT_MAX         	32767          		/* Maximum ("signed") "short" value */

#define BYTE_MAX   UCHAR_MAX            /* Maximum Byte value  */
#define WORD_MAX   USHRT_MAX            /* Maximum Word value  */
#define DWORD_MAX  ULONG_MAX            /* Maximum Dword value */
#define UINT8_MAX  UCHAR_MAX            /* Maximum Byte value  */
#define UINT16_MAX USHRT_MAX            /* Maximum Word value  */
#define UINT32_MAX ULONG_MAX            /* Maximum Dword value */

#define UINT8_MIN  CHAR_MIN            /* Minimum Byte value  */
#define INT8_MIN   SCHAR_MIN            /* Minimum Int8 value  */
#define INT8_MAX   SCHAR_MAX            /* Maximum Int8 vlaue  */
#define INT16_MIN  SHRT_MIN             /* Minimum Int16 value */
#define INT16_MAX  SHRT_MAX             /* Maximum Int16 value */
#define INT32_MIN  LONG_MIN             /* Minimum Int32 value */
#define INT32_MAX  LONG_MAX             /* Maximum Imt32 value */

#define MAX(a,b)	((a)>(b) ? (a) : (b))
#define MIN(a,b)	((a)<(b) ? (a) : (b))
#define ABS(a)	((a)>(0) ? (a) :(-(a)))
//#define abs(a)	ABS(a)

#define CheckRange(min,value,max)	 ((value)<(min) ? (min) : ((value) > (max) ?(max) : (value)))

#define BIT_CLEAR(para,bit)	(para &=~(1<<(bit)))
#define BIT_SET(para,bit)		(para |=(1<<(bit)))

typedef enum 
{
	ERR_NON,
	ERR_PARA_RANGE,/*parameter out of range etc.*/
	ERR_SOURCE_USING,
}ERR;

/*Jiaye define type*/
//typedef uint8 Std_ReturnType;
#pragma pack(1)
typedef struct
{
	uint8 CcpCommandFlag;
	uint8 CcpCommand;
	uint16 CcpContronData;
}tstCcpContronType;
#pragma pack()

typedef struct
{
   const tFuncPtr vfpAction;  	

}ThreadAction;

typedef struct
{
	uint8 ID;  	
	vpFun pFun;
}stOS_IRQ;

typedef union tBitField                 /* Bitfield data type with 16 bits */
{
   struct
   {                                    /* Single Bits */
      byte _0 : 1;                      /* Bit 00 */
      byte _1 : 1;                      /* Bit 01 */
      byte _2 : 1;                      /* Bit 02 */
      byte _3 : 1;                      /* Bit 03 */
      byte _4 : 1;                      /* Bit 04 */
      byte _5 : 1;                      /* Bit 05 */
      byte _6 : 1;                      /* Bit 06 */
      byte _7 : 1;                      /* Bit 07 */
      byte _8 : 1;                      /* Bit 08 */
      byte _9 : 1;                      /* Bit 09 */
      byte _10: 1;                      /* Bit 10 */
      byte _11: 1;                      /* Bit 11 */
      byte _12: 1;                      /* Bit 12 */
      byte _13: 1;                      /* Bit 13 */
      byte _14: 1;                      /* Bit 14 */
      byte _15: 1;                      /* Bit 15 */
   } F;                                 /* Flag access identifier */
   struct
   {                                    /* Byte Groups */
      byte _0;                          /* Bits 0 to 7 */
      byte _1;                          /* Bits 8 to 15 */
   } B;                                 /* Byte access identifier */
   word W;                              /* Word access identifier */
} tBitField;

typedef union tWordRec                  /* Word data type with single */
{                                       /*  accessable bytes */
   struct
   {                                    /* Bytes */
      byte _0;                          /* Low  byte */
      byte _1;                          /* High byte */
   } B;                                 /* Byte access identifier */
   word W;                              /* Word access identifier */
} tWordRec;

typedef union tDwordRec                 /* Dword data type with single */
{                                       /*  accessable words and bytes */
   struct
   {                                    /* Bytes */
      byte _0;                          /* Low  byte of the low  word */
      byte _1;                          /* High byte of the low  word */
      byte _2;                          /* Low  byte of the high word */
      byte _3;                          /* High byte of the high word */
   } B;                                 /* Byte access identifier */
   struct
   {                                    /* Words */
      word _0;                          /* Low  word */
      word _1;                          /* High word */
   } W;                                 /* Word access identifier */
   dword D;                             /* Dword access identifier */
} tDwordRec;

typedef union tunBitField               /* Bitfield data type with 16 bits */
{
   struct
   {                                    /* Single Bits */
      word _0 : 1;                      /* Bit 00 */
      word _1 : 1;                      /* Bit 01 */
      word _2 : 1;                      /* Bit 02 */
      word _3 : 1;                      /* Bit 03 */
      word _4 : 1;                      /* Bit 04 */
      word _5 : 1;                      /* Bit 05 */
      word _6 : 1;                      /* Bit 06 */
      word _7 : 1;                      /* Bit 07 */
      word _8 : 1;                      /* Bit 08 */
      word _9 : 1;                      /* Bit 09 */
      word _10: 1;                      /* Bit 10 */
      word _11: 1;                      /* Bit 11 */
      word _12: 1;                      /* Bit 12 */
      word _13: 1;                      /* Bit 13 */
      word _14: 1;                      /* Bit 14 */
      word _15: 1;                      /* Bit 15 */
   } F;                                 /* Flag access identifier */
   struct
   {                                    /* Byte Groups */
      byte _0;                          /* Bits 0 to 7 */
      byte _1;                          /* Bits 8 to 15 */
   } B;                                 /* Byte access identifier */
   word W;                              /* Word access identifier */
} tunBitField;

typedef union tunWordRec                /* Word data type with single */
{                                       /*  accessable bytes */
   struct
   {                                    /* Bytes */
      byte _0;                          /* Low  byte */
      byte _1;                          /* High byte */
   } B;                                 /* Byte access identifier */
   word W;                              /* Word access identifier */
} tunWordRec;

typedef union tunDwordRec               /* Dword data type with single */
{                                       /*  accessable words and bytes */
   struct
   {                                        /* Bytes */
      byte _0;                          /* Low  byte of the low  word */
      byte _1;                          /* High byte of the low  word */
      byte _2;                          /* Low  byte of the high word */
      byte _3;                          /* High byte of the high word */
   } B;                                   /* Byte access identifier */
   struct
   {                                    /* Words */
      word _0;                          /* Low  word */
      word _1;                          /* High word */
   } W;                                 /* Word access identifier */
   dword D;                             /* Dword access identifier */
} tunDwordRec;

typedef void (*tpvFuncPtr)(void);      /* Type definition for function      */

typedef unsigned int bitw;   /* Basistyp fuer Bit-Variablen bis zu 16 Bit*/

/* BIN_BYTE: Converts the binary Expression into a numeric constant *
*  ---------------------------------------------------------------- *
*  Same as BinByte but without then type cast, so BIN_BYTE can also be *
*  used in preprocessor expressions                                    */

#define BIN_BYTE(i) ((0x80&(0x0##i##l>>21))|(0x40&(0x0##i##l>>18))\
   |(0x20&(0x0##i##l>>15))|(0x10&(0x0##i##l>>12))|(0x08&(0x0##i##l>>9))\
   |(0x04&(0x0##i##l>>6))|(0x02&(0x0##i##l>>3))|(0x01&0x0##i##l))

/* TypeConv: convert data types */
#define TypeConv( Typ, VarName) (*((Typ *)&(VarName)))

#define BinByte(i) ((byte)((0x80&(0x0##i##l>>21))|(0x40&(0x0##i##l>>18))\
   |(0x20&(0x0##i##l>>15))|(0x10&(0x0##i##l>>12))|(0x08&(0x0##i##l>>9))\
   |(0x04&(0x0##i##l>>6))|(0x02&(0x0##i##l>>3))|(0x01&0x0##i##l)))
   

union BitByte
{
   struct
   {
      uint8 _0 : 1;
      uint8 _1 : 1;
      uint8 _2 : 1;
      uint8 _3 : 1;
      uint8 _4 : 1;
      uint8 _5 : 1;
      uint8 _6 : 1;
      uint8 _7 : 1;
   } f;
   uint8 b;
};
typedef union BitByte tunBitByte;

union BitReg
   {
   struct
      {
      uint16 _0 : 1;
      uint16 _1 : 1;
      uint16 _2 : 1;
      uint16 _3 : 1;
      uint16 _4 : 1;
      uint16 _5 : 1;
      uint16 _6 : 1;
      uint16 _7 : 1;
      uint16 _8 : 1;
      uint16 _9 : 1;
      uint16 _10: 1;
      uint16 _11: 1;
      uint16 _12: 1;
      uint16 _13: 1;
      uint16 _14: 1;
      uint16 _15: 1;
      } f;
   struct
      {
      uint8 _0;
      uint8 _1;
      } b;
   uint16 w;
   };
   
typedef union BitReg UnBitReg;
union ScrReg
   {
   struct
      {
      uint8 _0;
      uint8 _1;
      uint8 _2;
      uint8 _3;
      } b;
   struct
      {
      uint16  _0;
      uint16  _1;
      } w;
  struct
      {
      uint16 _0 : 1;
      uint16 _1 : 1;
      uint16 _2 : 1;
      uint16 _3 : 1;
      uint16 _4 : 1;
      uint16 _5 : 1;
      uint16 _6 : 1;
      uint16 _7 : 1;
      uint16 _8 : 1;
      uint16 _9 : 1;
      uint16 _10: 1;
      uint16 _11: 1;
      uint16 _12: 1;
      uint16 _13: 1;
      uint16 _14: 1;
      uint16 _15: 1;
      uint16 _16 : 1;
      uint16 _17 : 1;
      uint16 _18 : 1;
      uint16 _19 : 1;
      uint16 _20 : 1;
      uint16 _21 : 1;
      uint16 _22 : 1;
      uint16 _23 : 1;
      uint16 _24 : 1;
      uint16 _25 : 1;
      uint16 _26: 1;
      uint16 _27: 1;
      uint16 _28: 1;
      uint16 _29: 1;
      uint16 _30: 1;
      uint16 _31: 1;
      } f;
   uint32 l;
   };
typedef  union ScrReg UnScrReg;

union	ByteWord
{
   struct
   {
	      uint8 _0;
	      uint8 _1;
	      uint8 _2;
	      uint8 _3;
	      uint8 _4;
	      uint8 _5;
	      uint8 _6;
	      uint8 _7;
	      uint8 _8;
	      uint8 _9;
	      uint8 _10;
	      uint8 _11;
	      uint8 _12;
	      uint8 _13;
	      uint8 _14;
	      uint8 _15;
	      uint8 _16;
	      uint8 _17;
	      uint8 _18;
	      uint8 _19;
	      uint8 _20;
	      uint8 _21;
	      uint8 _22;
	      uint8 _23;
	      uint8 _24;
	      uint8 _25;
	      uint8 _26;
	      uint8 _27;
	      uint8 _28;
	      uint8 _29;
	      uint8 _30;
	      uint8 _31;
   } b;
   
  struct
      {
	      uint16 _0;
	      uint16 _1;
	      uint16 _2;
	      uint16 _3;
	      uint16 _4;
	      uint16 _5;
	      uint16 _6;
	      uint16 _7;
	      uint16 _8;
	      uint16 _9;
	      uint16 _10;
	      uint16 _11;
	      uint16 _12;
	      uint16 _13;
	      uint16 _14;
	      uint16 _15;
      } w;

   struct
      {
             uint32 _0;
	      uint32 _1;
	      uint32 _2;
	      uint32 _3;
	      uint32 _4;
	      uint32 _5;
	      uint32 _6;
	      uint32 _7;
	     
      } l;	
  
};
typedef union ByteWord tunByteWord;

typedef 	struct
	{
		uint8 bit0:1;
		uint8 bit1:1;
		uint8 bit2:1;
		uint8 bit3:1;
		uint8 bit4:1;
		uint8 bit5:1;
		uint8 bit6:1;
		uint8 bit7:1;
}stBYTE;

typedef	struct
{
	uint8 bit0:1;
	uint8 bit1:1;
	uint8 bit2:1;
	uint8 bit3:1;
	uint8 bit4:1;
	uint8 bit5:1;
	uint8 bit6:1;
	uint8 bit7:1;
	uint8 bit8:1;
	uint8 bit9:1;
	uint8 bit10:1;
	uint8 bit11:1;
	uint8 bit12:1;
	uint8 bit13:1;
	uint8 bit14:1;
	uint8 bit15:1;
}stWORD;

#define DET_vErrReport(a)
#endif  /* STD_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
