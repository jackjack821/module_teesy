/***************************************************************************************************
                                     KNOB PROCESS                                                                            
 
  .File Name  : KNOB_Private.h

  .Description: This file is used to define the statement of extern function.

  --------------------------------------------------------------------------------------------------
    Version     Date            Author              Change
    
  --------------------------------------------------------------------------------------------------
    Rev 1.0     2014-11-09      Xu Xianglin         - module template update.
    Rev 2.0     2015-02-05      Xu xianglin	        - inquiry mode.
    Rev 3.0     2015-03-10      Xu xianglin		    - inquiry mode optimization.
***************************************************************************************************/
#ifndef KNOB_PRIVATE_H
#define KNOB_PRIVATE_H


#define KNOB_SwVersion					(0x0101)

/***************************************************************************************************
                                        MACRO DEFINITION
***************************************************************************************************/

#define KNOB_sbiLowVoltage			0U  
#define KNOB_sbiHighVoltage			0U	

/*************************Internal Module Interface End****************************/


#define KNOB_nKnob1Id                                          KNOB_nTempId
#define KNOB_nKnob2Id                                          KNOB_nBlowerId

#define KNOB_nu8Knob1Direction                                 KNOB_nu8TempOperated
#define KNOB_nu8Knob2Direction                                 KNOB_nu8BlowerOperated

#define KNOB_nu8Knob1PlusCounter                               KNOB_nu8TempPlusCounter
#define KNOB_nu8Knob1MinusCounter                              KNOB_nu8TempMinusCounter

#define KNOB_nu8Knob2PlusCounter                               KNOB_nu8BlowerPlusCounter
#define KNOB_nu8Knob2MinusCounter                              KNOB_nu8BlowerMinusCounter

#define KNOB_nu8Knob1PtsPlusCounter                            KNOB_nu8PtsTempPlusCounter
#define KNOB_nu8Knob1PtsMinusCounter                           KNOB_nu8PtsTempMinusCounter

#define KNOB_nu8Knob2PtsPlusCounter                            KNOB_nu8PtsBlowerPlusCounter
#define KNOB_nu8Knob2PtsMinusCounter                           KNOB_nu8PtsBlowerMinusCounter

#ifndef KNOB_RTE
#define Std_ReturnType uint8
#define RTE_E_INVALID (0U)
#define RTE_E_OK (1U)
#define UInt32 uint32
#endif

#endif                    
