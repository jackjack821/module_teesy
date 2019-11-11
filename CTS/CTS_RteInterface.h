/***************************************************************************************************
                            CLIMATE THERMODYNAMICS SYSTEM RTE INTERFACE                             
                           
  .File Name  : CTS_RetInterface.h
  
  .Description: This file is the climate thermodynamics system interface for RTE.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-03-18  Chen Xiongzhi   - Creat this module.
***************************************************************************************************/

#ifndef CTS_RteInterface_H
#define CTS_RteInterface_H

 
/***************************************************************************************************
                                EXPORT INTERFACE FUNCTION PROTOTYPES                      

  Note(s): In this section declare all system global function prototypes of your module.
***************************************************************************************************/

/* Called in reset container. */
void CTS_vRteReset(void);	

/* Called in initialization container. */
void CTS_vRteInit(void);		        

/* Called in deinitialization container. */
void CTS_vRteDeinit(void);	 

/* Called in 100ms cyclic scheduling container when ignition on, sequence: Task0->Task1->Task2. */
void CTS_vRte100msTask0(void);
void CTS_vRte100msTask1(void);
void CTS_vRte100msTask2(void);

/* Called in 100ms cyclic scheduling container during active status. */
void CTS_vRteActive(void);

/* This function is used for RTE input process. */
void CTS_vGetRteInput(void);

/* This function is used to write the CTS output into RTE. */
void CTS_vWriteRteOutput(void);


#endif

/***************************************************************************************************
  EOF: CTS_RteInterface.h
***************************************************************************************************/
