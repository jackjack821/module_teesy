/***************************************************************************************************
                           CLIMATE THERMODYNAMICS SYSTEM EXPORT INTERFACE                           

  .File Name  : CTS_Export.c
  
  .Description: This file is used to provide the export interface of climate thermodynamics system.
  
  --------------------------------------------------------------------------------------------------
    Version     Date        Author          Change
  --------------------------------------------------------------------------------------------------
    V001        2016-01-13  Chen Xiongzhi   - Creat this module.
    V002        2016-01-19  Chen Xiongzhi   - Add error processing status.
    V003        2016-01-20  Chen Xiongzhi   - Rename to CTS_Export.
***************************************************************************************************/

#ifndef CTS_Export_H
#define CTS_Export_H


/***************************************************************************************************
                                            HEADER FILES                                            
***************************************************************************************************/

/* System header files */
#include "CTS_StdDef.h"

 
/***************************************************************************************************
                                EXPORT INTERFACE FUNCTION PROTOTYPES                      

  Note(s): In this section declare all export interface function prototypes of your module.
***************************************************************************************************/

/* Called in reset container. */
void CTS_vReset(void);	

/* Called in initialization container. */
void CTS_vInit(void);		        

/* Called in deinitialization container. */
void CTS_vDeinit(void);	 

/* Called in 100ms cyclic scheduling container when ignition on, sequence: Task0->Task1->Task2. */
void CTS_v100msTask0(void);
void CTS_v100msTask1(void);
void CTS_v100msTask2(void);

/* Called in 100ms cyclic scheduling container during active status. */
void CTS_vActive(void);

/* Active status flag for CTS */
cbool CTS_boGetActiveFlag(void);

/* Get the export value through the API below. */
CTS_tenValidSta CTS_enGetSensorIctExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetPcbTempExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetAirdModeExport(cuint8 *pu8Output);
CTS_tenValidSta CTS_enGetEvapTempExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetHctExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetTgtBlowTempLExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetTgtBlowTempRExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetTgtBlowTempReExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetBlowTempLExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetBlowTempRExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetBlowTempReExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetBlowSpdExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetSunExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetHeadZoneTempLExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetHeadZoneTempRExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetHeadZoneTempReExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetBodyShellTempExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetCabinTempExport(cuint16 *pu16Output);

CTS_tenValidSta CTS_enGetSunLoadHeatExport(cuint16 *pu16Output);/*160926*/
CTS_tenValidSta CTS_enGetVelLoadHeatExport(cuint16 *pu16Output);
CTS_tenValidSta CTS_enGetPcbTempAdExport(cuint16 *pu16Output);

#endif

/***************************************************************************************************
  EOF: CTS_Export.h
***************************************************************************************************/
