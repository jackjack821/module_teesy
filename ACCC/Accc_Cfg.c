/************************** DEFAULTS ************************************/
/********************** Automatically Generated File ************************/
/********************* Do not edit this file manually! **********************/
/** Generated On : 2014/11/26  18:22:02                                     */
/**           By : test                                                     */
/**        Using : Accc_Cfg.xls                                             */
/**         From : D:\HVACproject\NewDevelopmentMode\ACCC                   */
/**               (D = )                                                    */
/****************************************************************************/

/*****************************************************************************
* FILE DECLARATION
*****************************************************************************/

#define ACCC_CFG

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/
#include "ACCC_Cfg.h"


/*****************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants and macros to configure your module. These constants are unknown for other
*   modules
*****************************************************************************/


const ACCC_tstLayout ACCC_stRomLayout = 

   {  /*----------------------- GroupACCC ---------------------------------------*/
	10,
	400,
	430,
#if ACCC_nWITH_ECON_MODE
	460,
	500,
#endif
	400,
	430,
#if(ACCC_nUSE_ENGINE_PROHIBITION == True)
	15,
	200,
	200,
	3500,
	0,
#endif
#if(ACCC_nUSE_SI_PROHIBITION == True)
	650,
	630,
#endif
#if(ACCC_nWITH_PRESSURE_SENSOR == True)
	200,
	0,
	3140,
	400,
#endif

#if (ACCC_nWITH_PRESSURE_SWITCH == True)
	307,
#endif
#if((ACCC_nAcType == ACC_u8VariableDisplacAc) || (ACCC_nAcType == ACC_u8ElectricAc))
	430,
	30,
	1,
	20,
	40,
	15,
	30,
	20,
	450,
	-450,
	2,
	{ 0x01AE,0x01D6,0x0226,0x0258 },	/*EED_au16AcccEvapByBlowoutTemp_X*/
	{ 0x01AE,0x01BD,0x01EA,0x0208 },	/*EED_au16AcccEvapByBlowoutTemp_Y*/
#if ACCC_nWITH_EVAP_DELAY_OFFAC
	380,
	600,
#endif
	20,
	{500,600, 700, 750, 800},// InletTemp = 10, 20, 30, 35, 40
	{420, 440, 460, 480, 500},
	{//InletTemp = 10, 20, 30, 35, 40
		{400,   420,   440,   460, 480},// 2
		{400,   420,   440,   460, 480}, // 4
		{400,   420,   440,   460, 480}, // 6
		{400,   420,   440,   460, 480}, // 8
		{400,   420,   440,   460, 480} // 10
	},
	{// InletTemp = 10, 20, 30, 35, 40
		{410,   430,   450,   470, 490},// 2
		{410,   430,   450,   470, 490}, // 4
		{410,   430,   450,   470, 490}, // 6
		{410,   430,   450,   470, 490}, // 8
		{410,   430,   450,   470, 490} // 10
	},
	{// InletTemp = 10, 20, 30, 35, 40
		{420,   440,   460,   480, 500},// 2
		{420,   440,   460,   480, 500}, // 4
		{420,   440,   460,   480, 500}, // 6
		{420,   440,   460,   480, 500}, // 7
		{420,   440,   460,   480, 500} // 10
	},
	{500,600, 700, 750, 800},// InletTemp = 10, 20, 30, 35, 40
	{625, 635,640, 660, 690},//EvapErr
	{//InletTemp = 10, 20, 30, 35, 40
		{30, 30, 30, 	30,	30},//-1.5
		{15, 15, 15, 	15,	15}, // -0.5
		{0, 	0, 	0, 	0,	0}, // 0
		{2, 	2, 	2, 	2,	2}, // 2
		{4, 	4, 	4, 	4,	4}  // 5
	},
	{//InletTemp = 10, 20, 30, 35, 40
		{30, 30, 30, 30,30},//-1.5
		{15, 15, 15, 15,15}, // -0.5
		{0, 	0, 	0,  0,  0}, // 0
		{2, 	2, 	2,  2,  2}, // 2
		{4, 	4, 	4,  4,  4}  // 5
	},
	{//InletTemp = 10, 20, 30, 35, 40
		{30, 30, 30, 30,30},//-1.5
		{15, 15, 15, 15,15}, // -0.5
		{0,    0,  0,   0,  0}, // 0
		{2,    2,  2,   2,  2}, // 2
		{4,    4,  4,   4,  4}  // 5
	},
	{630, 635, 639, 640, 641, 645, 650},
	{625, 630, 635, 640, 650, 655, 660},
	{//DynEvap   -1 ,  -0.5,  -0.1,  0,  0.1,  0.5,   1
		{57, 	52,  49, 	47, 	5, 	 0, 	 0}, // -1.5
		{37, 	34,  32, 	29, 	5, 	 0, 	 0}, // -1
		{24, 	22, 	19, 	17, 	5, 	0, 	 0}, // -0.5
		{ 5, 	       9, 	9, 	9, 	9, 	9, 	 5}, // 0
		{0,	 	0, 	5, 	9, 	10, 	12, 	14}, // 1
		{0, 		0, 	5, 	10, 	12, 	14,  17}, // 1.5
		{0, 		0,	5, 	12, 	14, 	17,  20} 	// 2
	},
	{//DynEvap   -1 ,  -0.5,  -0.1,  0,  0.1,  0.5,   1
		{60, 	55,  52, 	50, 	5, 	 0, 	 0}, // -1.5
		{40, 	37,  34, 	32, 	5, 	 0, 	 0}, // -1
		{24, 	22, 	19, 	17, 	5, 	0, 	 0}, // -0.5
		{ 5, 	       12, 	12, 	12, 	12, 	12, 	 5}, // 0
		{0,	 	0, 	5, 	12, 	14, 	17, 	18}, // 1
		{0, 		0, 	5, 	14, 	17, 	19,  22}, // 1.5
		{0, 		0,	5, 	17, 	19, 	22,  27} 	// 2
	},	
	{//DynEvap   -1 ,  -0.5,  -0.1,  0,  0.1,  0.5,   1
		{68, 	63,  58, 	53, 	5, 	 0, 	 0}, // -1.5
		{45, 	40,  36, 	34, 	5, 	 0, 	 0}, // -1
		{30, 	27, 	25, 	20, 	5, 	0, 	 0}, // -0.5
		{ 5, 	       15, 	15, 	15, 	15, 	15, 	 5}, // 0
		{0,	 	0, 	5, 	15, 	20, 	22, 	25}, // 1
		{0, 		0, 	5, 	18, 	20, 	25,  30}, // 1.5
		{0, 		0, 	5, 	20, 	25, 	30,  35} 	// 2
	},
	20,
	100,
	1000,
	10,
	{100,1000},
	{1000,5000},

#endif

#if(ACCC_nAcType == ACC_u8VariableDisplacAc)	
	1,
	500,
	-500,
	100,
	1000,
	10,
	65,
	250,
#if(ACCC_nUSE_SHORT_GND_PROHIBITION == True)
	70,
	30,
	3,
#endif
#if(ACCC_nWITH_TORQUE_OUTPUT)	
	{23, 35,46,58,69,81,92,104,115,127},
	{800,1000,1200,1400,1600,1800,2000,2200,2500},
	{ 
		{12,		11,	10,	9,	8,	7,	6,	5,	4},
		{26,		24,	22,	21,	19,	16,	13,	9,	6},
		{43,		40,	38,	35,	33,	28,	21,	15,	9},
		{60,		55,	51,	47,	43,	36,	28,	21,	13},
		{80,		72,	66,	59,	53,	44,	34,	27,	19},
		{100,	91,	84,	70,	60,	50,	39,	32,	24},
		{126,	115,	108,	83,	66,	55,	44,	37,	29},
		{149,	136,	127,	95,	74,	62,	50,	43,	34},
		{166,	150,	139,	105,	82,	70,	58,	49,	40},
		{180,	162,	150,	114,	90,	78,	65,	55,	45},
	},
#endif
#endif
#if(ACCC_nAcType == ACC_u8ElectricAc) 	
	100,
#if(ACCC_nHCU_LIMIT_EC_SPEED == True)
	500,
	{499, 500, 550,1050,1550,2000,2460,2929,3100},
	{0, 1000, 1000,2000,3000,4000,5000,6000,6500},
#endif
#if(ACCC_nOUTPUT_SPEED_TO_POWER)
	50,
	500,
#endif
	{0,1000,2000,3000,4000,5000,6000,6500},
	{0,550,1050,1550,2000,2460,2920,3100},

#if(ACCC_nWITH_BATT_MANAGE == True)&&(ACCC_nAcType == ACC_u8ElectricAc) 	

	10,
	50,
	20,
	1000,
	3500,
	10,
	35,
	25,
	15,
	100,
	{500U, 600U, 700U, 800U },
	{80U, 100U, 300U, 350U},
	{550U, 600U, 700U, 800U},
	{1000U, 1400U, 1700U, 2000U},

#endif
#if(ACCC_nWITH_COOLING_VALVE == True)
	150,
#endif
#endif

};


