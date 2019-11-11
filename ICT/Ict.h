/*---------------------------------------------------------------------------
 *  Project : Generic Product
 *  Filename: Ict.h
 *  Version : 1.1
 *  AUTHOR [Ouyang Bihuan]
*-----------------------------------------------------------------------------

 Version Date        Author                       Change
 -----------------------------------------------------------------------------
 Rev 1.1 2015-7-2    Ouyang Bihuan        	Create the module base on ICT of GAC A28.

****************************** .FILE_HEADER_END ******************************/

/*****************************************************************************
* FILE DECLARATION
******************************************************************************/
#ifndef ICT_H
#define ICT_H

#ifndef ext
#define ext extern 
#else
#define ext
#endif

#define _USE_NATS_

/*****************************************************************************
* LOCATION-DEFINES -only when the location assignment is needed.
******************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
******************************************************************************/
/* System-headerfiles */
#include "General.h"
#include "Ict_Cfg.h"

/* Foreign headerfiles */



/* Own headerfiles */



/*define the Num. of uint16 variable that will be used by other modules.*/
typedef enum ICT_enu16VarNum
{
		ICT_nu16Value=0,/*the predict incar value*/
		ICT_nu16SensorAdValue,	
        ICT_nu16SensorValue,/* Sensor value. */    
		ICT_nu16UndampedValue,/*the PTA incar value*/
		ICT_nu16LinearLimitValue,/*the incar value after line limit*/		
		ICT_nu16DynOffset,/*the filter diff between Set and PtaIncar*/
		ICT_nu16DynMax,/*the diff between Set and PtaIncar*/
		ICT_nu16MaxDiff,
		ICT_nu16StaticOffset,
		ICT_nu16TempOffset,/*for CCP,140807*/
		ICT_nu16FactorSi,/*for CCP,140807*/
		ICT_nu16IdleStaticOffset,/*for CCP,140904*/
		ICT_nu16ErrorState,
		ICT_nu16SwVersion,
		ICT_nu16Max
}ICT_tenu16VarNum;

typedef enum ICT_enu8VarNum
{
		ICT_nu8Valid=0,/*all the Incar value is valid*/
		ICT_nu8Max
}ICT_tenu8VarNum;



ext void ICT_vReset (void);		    /* Reset Container */
ext void ICT_vInit (void);		          /* StandbyActive Container */
ext void ICT_vDeinit(void);	             /* ActiveStandby Container */
ext void ICT_vMain           (void);		                     /* On Container */
ext void ICT_vActive         (void);
ext void ICT_vStartup        (void);
ext uint8 ICT_u8GetValue( ICT_tenu8VarNum Num );
ext uint16 ICT_u16GetValue( ICT_tenu16VarNum Num );

#undef ext 
//#undef ICT_H

#endif                            


