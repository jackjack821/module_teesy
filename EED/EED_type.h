/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [EED                                      ]
*-----------------------------------------------------------------------------
  .FILE   [ EED.c                                                         ]
  .AUTHOR [  Tan Fumin				                                     ]
*-----------------------------------------------------------------------------
 Version Date        		Author                       
Change                      
 -----------------------------------------------------------------------------
 Rev 00.00.00 2014/12/12    Tan Fumin      			 The first version  
 Rev 02       2015/06/01    Zhang Shuncong            add groupID info,update flow                                                  update Telltales process
****************************** .FILE_HEADER_END ******************************/

#ifndef EED_TYPE_H
#define EED_TYPE_H

#define EED_EEPFlowWaitMax		4
#define EED_FlsFlowWaitMax		10

/* Structure
   ========= */
typedef  struct  
{
	const uint8 u8GroupID;         /* group ID    */
    const uint8 u8CheckSumCfg;         /* Need checksum?  */
	const uint16 u16Length;         /* group length   */
	const uint32 u32StartAddr;         /* group start addr */
    const uint32 u32EndAddr;         /* group start addr */

}EED_tstGroup;

#define EED_nRegisterGroupInfo(GroupID,CheckSumCfg,Length,StartAddr,EndAddr) \
{ \
   (GroupID), \
   (CheckSumCfg), \
   (Length), \
   (StartAddr), \
   (EndAddr), \
}

/*define the Num. of variable that will be used by other modules.*/
typedef enum EED_enu8VarNum
{
	EED_nu8ErrorCode=0,
	EED_nu8SwVersion,
	EED_nu8Max
}EED_tenu8VarNum;

#if 0
/*this is for uint8 type variables*/
typedef enum EED_enu8GroupNum
{
	EED_nu8GroupMMI =0,
	EED_nu8GroupOAT,
	EED_nu8GroupDIAG,
	EED_nu8GroupDTC,
	EED_nu8GroupPTS,
	EED_nu8GroupMax                     
}EED_tenu8GroupNum;
#endif
/*this is for uint8 type variables*/
typedef enum EED_enu8SectorNum
{
	EED_nu8SectorSA1 =0,
	EED_nu8SectorSA2,
	EED_nu8SectorSA3,
	EED_nu8SectorSA4,
	EED_nu8SectorMax                     
}EED_tenu8SectorNum;


/*this is for EED_nu8ErrorCode variables, 1 bit represents one error*/
typedef enum EED_enState
{
	EED_nBit0 = 0,  
	EED_nBit1,		
	EED_nBit2, 
	EED_nBit3,  
	EED_nBit4,		
	EED_nBit5, 
	EED_nBit6,		
	EED_nBit7, 
}EED_tenState;

typedef enum EED_Result
{
    EED_ERR_NULL = 0,  /* No error */
    EED_Error,  /* Non-specific error code */
    EED_ErrorAddressAlignment,  /* Address alignment does not match */
    EED_ErrorAccessRights,  /* Wrong mode (e.g. user/system) mode is set */
    EED_ErrorInvalidParameter,  /* Provided parameter is not valid */
    EED_ErrorOperationInProgress,  /* 5 ,A conflicting or requested operation is still in progress*/
    EED_ErrorInvalidMode,  /* Operation not allowed in current mode*/
    EED_ErrorUninitialized,  /* Module (or part of it) was not initialized properly*/
    EED_ErrorBufferFull,  /* Circular buffer can not be written because the buffer is full*/
    EED_ErrorTimeout,   /* A requested operation could not be completed*/
    EED_ErrorInvalidGroupID,   /* 10,Invalid GroupID*/
    EED_ErrorInvalidGroupLen,   /* Invalid group length*/
    EED_ErrorInvalidChecksum,   /* Invalid checksum*/
    EED_ErrorMax
} EED_tenResult;

#if EED_DataFlashType == NEC_32BIT
typedef enum EED_FDL_STATUS_T
{
    EED_FDL_OK  = 0,        /**< Operation terminated successfully */
    EED_FDL_BUSY,        /**< Operation is still ongoing */
    EED_FDL_SUSPENDED,        /**< Flash operation is suspended */
    EED_FDL_ERR_CONFIGURATION,        /**< The FDL configuration (descriptor) was wrong */
    EED_FDL_ERR_PARAMETER,        /**< A parameter of the FDL function call was wrong */
    EED_FDL_ERR_PROTECTION,        /**< Operation blocked due to wrong parameters */
    EED_FDL_ERR_REJECTED,        /**< Flow error, e.g. another operation is still busy */
    EED_FDL_ERR_WRITE,        /**< Flash write error */
    EED_FDL_ERR_ERASE,        /**< Flash erase error */
    EED_FDL_ERR_BLANKCHECK,        /**< Flash blank check error */
    EED_FDL_ERR_COMMAND,       /**< Unknown command */
    EED_FDL_ERR_ECC_SED,       /**< Single bit error detected by ECC*/
    EED_FDL_ERR_ECC_DED,       /**< Double bit error detected by ECC*/
    EED_FDL_ERR_INTERNAL        /**< Library internal error */
} EED_fdl_status_t;
#endif

typedef struct 
{
	uint8 In;
	uint8 Out;
	uint16 DataLen[EED_EEPFlowWaitMax];
	uint16 EraseSize[EED_EEPFlowWaitMax]; /*160702*/
	void *From[EED_EEPFlowWaitMax];
	void *To[EED_EEPFlowWaitMax];
	vpFun CallBack[EED_EEPFlowWaitMax];
}EED_stEEPFLOW;

typedef struct 
{
	uint8 In;
	uint8 Out;
	uint16 DataLen[EED_FlsFlowWaitMax];
	uint16 EraseSize[EED_EEPFlowWaitMax]; /*160702*/
	void *From[EED_FlsFlowWaitMax];
	void *To[EED_FlsFlowWaitMax];
	vpFun CallBack[EED_FlsFlowWaitMax];
}EED_stFLSFLOW;

typedef const struct 
{
   void   *  pvGroupRAMHead;
   void   *  pvGroupROMHead; /*check if need __far*/
   uint16  u16GroupSize;
} EED_tstBlockInfo;

typedef enum
{
	EED_enGroupID_1=0,
	EED_enGroupID_2,
	EED_enGroupID_3,
	EED_enGroupID_4,
	EED_enGroupID_5,
	EED_enGroupID_6,
	EED_enGroupID_7,
	EED_enGroupID_8,
	EED_enGroupID_9,
	EED_enGroupID_10,
	EED_enGroupID_11,
	EED_enGroupID_12,
	EED_enGroupID_13,
	EED_enGroupID_14,
	EED_enGroupID_15,
	EED_enGroupID_16,
	EED_enGroupID_17,
	EED_enGroupID_18,
	EED_enGroupID_19,
	EED_enGroupID_20,
	EED_enGroupID_21,
	EED_enGroupID_22,
	EED_enGroupID_23,
	EED_enGroupID_24,
	EED_enGroupID_25,
	EED_enGroupID_26,
	EED_enGroupID_27,
	EED_enGroupID_28,
	EED_enGroupID_29,
	EED_enGroupID_30,
	EED_enGroupID_31,
	EED_enGroupID_32,
	/*add group index here if neccessary!!*/
	
	EED_enGroupID_ALLEeprom,
	EED_enGroupID_ALLFlash,
	EED_enGroupID_ALLData,
}EED_enGROUP;

#endif

