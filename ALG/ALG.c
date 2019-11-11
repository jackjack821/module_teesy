/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE  [  ALG                                     ]
*-----------------------------------------------------------------------------
  .FILE   [  ALG.C                                                        ]
  .AUTHOR [  Li Jiaye				                                     ]
*-----------------------------------------------------------------------------

 Version Date        Author                       Change                      
 -----------------------------------------------------------------------------
 Rev 1.0 2015-3-22    Li Jiaye        module template update.     
 
****************************** .FILE_HEADER_END ******************************/

#define ALG                         /* name of the module                */


/*****************************************************************************
* Template name:     SWMOD2C1.C
* Template revision: 1.3
*-----------------------------------------------------------------------------
* CASE-Tool:
*****************************************************************************/

/*****************************************************************************
* HEADER-FILES (Only those that are needed in this file)
*****************************************************************************/

/* System-headerfiles */
#include "General.h"

#include "ALG.h"



/* ======================================================================== */

/* Function :     ALG_u8FirstOrderFilter                                    */
/* Description :  This function impliments a first order low pass filter    */
/*                   with guaranteed no loss of resolution.                 */
/* Inputs :       u8Input  -  The 8 bit unsigned input value to be filtered */
/*                u8K      -  The filter constant used (1-8).               */
/*                pu16Saved-  A pointer to where the higher resolution value*/
/*                            is stored (necessary to guarantee resolution).*/
/*                            This needs to point to a 16-bit ram location  */
/* Returns :      The 8-bit output if the filter                            */
/* ======================================================================== */
uint8 ALG_u8FirstOrderFilter(uint16 pu16_1[], uint8 u8Input, uint8 u8K)
{
	uint8 u8NewK;
	uint16 u16NewValue;
	u8K &= 0x0FU;                               /* mask in the lower nibble  */
	if ( u8K > 0x08u ) 
    {
      u8K = 0x08u;/* limit k value to maximum 8 */
    }                  
	u8NewK = (uint8)8u - u8K;
	u16NewValue =  pu16_1[0];
	u16NewValue -= (u16NewValue >> u8K);
	u16NewValue += (uint16)(((uint16)u8Input) << u8NewK);
	*pu16_1  = u16NewValue;

	return (uint8)(u16NewValue>>8);
}

/* ======================================================================== */
/* Function :     ALG_u8SecondOrderFilter                                   */
/* Description :  This function impliments a second order low pass filter   */
/*                   with guaranteed no loss of resolution.                 */
/* Inputs :       u8Input  -  The 8 bit unsigned input value to be filtered */
/*                u8K      -  The filter constant used (1-8).               */
/*                         -> u8K:0-3 = Stage 1 K (1-8)                     */
/*                         -> u8K:4-7 = Stage 2 K (1-8)                     */
/*                pau16Saved- A pointer to where the higher resolution value*/
/*                            is stored (necessary to guarantee resolution).*/
/*                            This needs top point to 2 consecutive 16-bit  */
/*                            ram locations.                                */
/* Returns :      The 8-bit output if the filter                            */
/* ======================================================================== */
uint8 ALG_u8SecondOrderFilter(uint16 pu16_1[], uint8 u8Input, uint8 u8K)
{
	uint16 u16NewValue;
	(void)ALG_u8FirstOrderFilter(&pu16_1[0],u8Input,u8K);
	u8K   >>=   4;
	u8K   &=    0x0FU;                          /* mask in the lower nibble  */
	if ( u8K > 8u ) { u8K = 8u;}                 /* limit k value to maximum 8 */

	u16NewValue =  pu16_1[1];
	u16NewValue -= (u16NewValue >> u8K);
	u16NewValue += (pu16_1[0] >> u8K);
	pu16_1[1]   =  u16NewValue;
	return (uint8)(u16NewValue>>8) ;
}
/* ======================================================================== */
/* Function :     ALG_u16FirstOrderFilter                                   */
/* Description :  This function impliments a first order low pass filter    */
/*                   with guaranteed no loss of resolution.                 */
/* Inputs :       u16Input -  The 16 bit unsigned input value to be filtered*/
/*                u8K      -  The filter constant used (1-8).               */
/*                pu32Saved-  A pointer to where the higher resolution value*/
/*                            is stored (necessary to guarantee resolution).*/
/*                            This needs to point to a 32-bit ram location  */
/* Returns :      The 16-bit output if the filter                           */
/* ======================================================================== */
uint16 ALG_u16FirstOrderFilter(uint32 pu32_1[], uint16 u16Input, uint8 u8K)
{
	uint8 u8NewK;
	uint32 u32NewValue;
	u8K &= 0x0FU;                               /* mask in the lower nibble  */
	if ( u8K > 8u ) {u8K = 8u;}                  /* limit k value to maximum 8 */
	u8NewK = (uint8)16u - u8K;

	u32NewValue =  pu32_1[0];
	u32NewValue -= (u32NewValue >> u8K);
	u32NewValue += (((uint32)u16Input) << u8NewK );
	pu32_1[0]  = u32NewValue;
	return (uint16)(u32NewValue>>16);
}
/* ======================================================================== */
/* Function :     ALG_u16SecondOrderFilter                                  */
/* Description :  This function impliments a second order low pass filter   */
/*                   with guaranteed no loss of resolution.                 */
/* Inputs :       u16Input -  The 16 bit unsigned input value to be filtered*/
/*                u8K      -  The filter constant used (1-8).               */
/*                         -> u8K:0-3 = Stage 1 K (1-8)                     */
/*                         -> u8K:4-7 = Stage 2 K (1-8)                     */
/*                pau32Saved- A pointer to where the higher resolution value*/
/*                            is stored (necessary to guarantee resolution).*/
/*                            This needs top point to 2 consecutive 32-bit  */
/*                            ram locations.                                */
/* Returns :      The 16-bit output if the filter                           */
/* ======================================================================== */
uint16 ALG_u16SecondOrderFilter(uint32 pu32_1[], uint16 u16Input, uint8 u8K)
{
	uint32 u32NewValue;
	(void)ALG_u16FirstOrderFilter(&pu32_1[0],u16Input,u8K);
	u8K   >>=   4;
	u8K   &=    0x0Fu;                           /* mask in the lower nibble  */
	if ( u8K>8u ) { u8K = 8u;}                   /* limit k value to maximum 8 */

	u32NewValue = pu32_1[1];
	u32NewValue -= (u32NewValue >> u8K);
	u32NewValue += (pu32_1[0] >> u8K);
	pu32_1[1]  = u32NewValue;
	return  (uint16)(u32NewValue>>16);
}
/* ======================================================================== */
/* Function :     ALG_u8Hysteresis                                          */
/* Description :  This function impliments hysteresis in an 8-bit signal.   */
/* Inputs :       u8Input  -  The 8 bit unsigned input value to be filtered.*/
/*                u8Hysteresis - Hysteresis to be applied (0-255).          */
/*                pu8Saved-  A pointer to an 8-bit location where the       */
/*                            previous value is stored.                     */
/* ======================================================================== */
void    ALG_vHysteresis_8(uint8 pu8_1[], const uint8 u8Input, const uint8 u8Hysteresis)
{
	uint8 u8Diff;
	u8Diff = pu8_1[0];
	if(u8Input >= u8Diff) 
	{
		u8Diff = u8Input - u8Diff;
	}
	else
	{
		u8Diff = u8Diff - u8Input;
	}
	if ( u8Diff > u8Hysteresis )
	{
	  	pu8_1[0] = u8Input;
	}
}
/* ======================================================================== */
/* Function :     ALG_u16Hysteresis                                          */
/* Description :  This function impliments hysteresis in an 16-bit signal.   */
/* Inputs :       u16Input  -  The 16 bit unsigned input value to be filtered.*/
/*                u16Hysteresis - Hysteresis to be applied (0-65535).          */
/*                pu16Saved-  A pointer to an 16-bit location where the       */
/*                            previous value is stored.                     */
/* ======================================================================== */
void    ALG_vHysteresis_16(uint16 pu16_1[], const uint16 u16Input, const uint16 u16Hysteresis)

{
	uint16 u16Diff;
	u16Diff = pu16_1[0];
	if(u16Input >= u16Diff) /* get the u16Input and *pu16_1 abs value, add by lxd @2013-4-3*/
	{
		u16Diff = u16Input - u16Diff;
	}
	else
	{
		u16Diff = u16Diff - u16Input;
	}	
	if ( u16Diff > u16Hysteresis )
	{
	  	pu16_1[0] = u16Input;
	}
}
/* ======================================================================== */
/* Function :     ALG_u8CurveLookup_8_8_Limit                               */
/* Description :  This function impliments an 8-bit curve lookup.           */
/*                The input value is converted , using the characteristic   */
/*                curve. If the input is outside the range of x-values the  */
/*                last y-value is returned, hence the "limit".              */
/* Inputs :       u8Input  - The 8 bit unsigned input value.                */
/*                pau8XCurve - A pointer to an array of 8-bit values. This  */
/*                   array must be monotonically increasing.                */
/*                pau8YCurve - A pointer to an array of 8-bit values. This  */
/*                   array can be any function whatsoever. The values are   */
/*                   linearly interpolated between. The size of this array  */
/*                   must be the same as the x-value array.                 */
/*                u8Size    - The amount of points in the curves   .        */
/*            Y                                                             */
/*            ^                                   X******                   */
/*            |                                  *                          */
/*            |                                 *                           */
/*    returns<|           X*****X              *                            */
/*            |          *       *            *                             */
/*            |      X**X         *          *                              */
/*            |*****X              X********X                               */
/*            |                                                             */
/*            |                                                             */
/*            +------------------------------------------>X                 */
/*                           ^                                              */
/*                           u8Input                                        */
/*                                                                          */
/* Returns :      The 8-bit output if the interpolation                     */
/* ======================================================================== */
uint8 ALG_u8CurveLookup_8_8_Limit(uint8 pu8_1[], uint8 pu8_2[], const uint8 u8Input, const uint8 u8Size )
{
	uint8 u8Index;
	uint8 u8x1;
	uint8 u8y1;
	int16 i16xdiff;
	int16 i16ydiff;
        int16 i16ReturnValue;
        uint8 u8ReturnValue;
	u8Index = u8Size-(uint8)1u;
	if ( u8Input >= pu8_1[u8Index]) /* past the last point */
	{
		u8ReturnValue=pu8_2[(u8Size-1u)];        /* return the last y data point */
	}
	else
	{
		if (u8Input <= pu8_1[0]) /* we are between 0 and the 1st point */
		{
			u8ReturnValue=pu8_2[0];
		}
		else /* normal range interpolation */
		{
			//for ( u8Index=u8Size-(uint8)1u;u8Index>0u;u8Index--)
			for ( u8Index=u8Size-(uint8)1u;u8Index--;)
			{
				if (u8Input > pu8_1[u8Index])
				{
					u8x1 = pu8_1 [u8Index];
					u8y1 = pu8_2 [u8Index];
					i16ydiff = (int16)pu8_2[u8Index+1u] - (int16)u8y1;
					i16xdiff = (int16)pu8_1[u8Index+1u] - (int16)u8x1;
					if ( (i16xdiff ==0L)||(i16ydiff==0L) ) 
                                        {
                                          u8ReturnValue=u8y1;
                                          break;
                                        }

					u8Index = 0u;
				}
			}
			i16ReturnValue=((int16)u8y1 + (i16ydiff *((int16)u8Input - (int16)u8x1) / i16xdiff));
                        u8ReturnValue=(uint8)i16ReturnValue;
		}                
	}
        return u8ReturnValue;
}

/* ======================================================================== */
/* Function :     ALG_u8CurveLookup_8_8_Limit                               */
/* Description :  This function impliments an 8-bit curve lookup.           */
/*                The input value is converted , using the characteristic   */
/*                curve. If the input is outside the range of x-values the  */
/*                last y-value is returned, hence the "limit".              */
/* Inputs :       u8Input  - The 8 bit unsigned input value.                */
/*                pau8XCurve - A pointer to an array of 8-bit values. This  */
/*                   array must be monotonically increasing.                */
/*                pau8YCurve - A pointer to an array of 8-bit values. This  */
/*                   array can be any function whatsoever. The values are   */
/*                   linearly interpolated between. The size of this array  */
/*                   must be the same as the x-value array.                 */
/*                u8Size    - The amount of points in the curves   .        */
/*            Y                                                             */
/*            ^                                   X******                   */
/*            |                                  *                          */
/*            |                                 *                           */
/*    returns<|           X*****X              *                            */
/*            |          *       *            *                             */
/*            |      X**X         *          *                              */
/*            |*****X              X********X                               */
/*            |                                                             */
/*            |                                                             */
/*            +------------------------------------------>X                 */
/*                           ^                                              */
/*                           u8Input                                        */
/*                                                                          */
/* Returns :      The 8-bit output if the interpolation                     */
/* ======================================================================== */
uint8 ALG_cu8CurveLookup_8_8_Limit(const uint8 pu8_1[],const uint8 pu8_2[], const uint8 u8Input, const uint8 u8Size )
{
	uint8 u8Index;
	uint8 u8x1;
	uint8 u8y1;
	int16 i16xdiff;
	int16 i16ydiff;
        int16 i16ReturnValue;
        uint8 u8ReturnValue;
	u8Index = u8Size-(uint8)1u;
	if ( u8Input >= pu8_1[u8Index]) /* past the last point */
	{
		u8ReturnValue=pu8_2[(u8Size-1u)];        /* return the last y data point */
	}
	else
	{
		if (u8Input <= pu8_1[0]) /* we are between 0 and the 1st point */
		{
			u8ReturnValue=pu8_2[0];
		}
		else /* normal range interpolation */
		{
			//for ( u8Index=u8Size-(uint8)1u;u8Index>0u;u8Index--)	
			for ( u8Index=u8Size-(uint8)1u;u8Index--;)
			{
				if (u8Input > pu8_1[u8Index])
				{
					u8x1 = pu8_1 [u8Index];
					u8y1 = pu8_2 [u8Index];
					i16ydiff = (int16)pu8_2[u8Index+1u] - (int16)u8y1;
					i16xdiff = (int16)pu8_1[u8Index+1u] - (int16)u8x1;
					if ( (i16xdiff ==0L)||(i16ydiff==0L) ) 
                                        {
                                          u8ReturnValue=u8y1;
                                          break;
                                        }

					u8Index = 0u;
				}
			}
			i16ReturnValue=((int16)u8y1 + (i16ydiff *((int16)u8Input - (int16)u8x1) / i16xdiff));
                        u8ReturnValue=(uint8)i16ReturnValue;
		}                
	}
        return u8ReturnValue;
}

/* ======================================================================== */
/* ======================================================================== */
/* This function takes a pointer to an array,along with the size of the     */
/*   array and finds the entry that is closest to the input value.          */
/* If there are two entries in the array that are equidistant from the      */
/*   input, the higher index is returned.                                   */
/*                                                                          */
/* Inputs:  uint8 * au8DataTable       pointer to an array of uint8's       */
/*          uint8 u8Size               size of the array                    */
/*          uint8 u8Input              value that will be compared          */
/* Returns: as uint8 the index pointing to the closest entry in the array   */
/* ======================================================================== */
uint8 ALG_u8GetClosestEntry(uint8 pu8_1[], uint8 u8Size, uint8 u8Input)
{
	uint8 u8Index;
	uint8 u8Diff;
	uint8 u8MinimumDiff;
	uint8 u8NewValue;

	u8MinimumDiff  =(uint8) 0xFFu;            /* Seed the successive difference */
	u8NewValue     = u8Size-(uint8)1u;             /* tracker with 255. Even if all  */
	                                      /* of the data in array is zero,  */
	                                      /* the result will be the highest */
	                                      /* index.                         */

	for ( u8Index = u8Size; u8Index-- ; )  /* Scan through array looking for */
	{                                      /* a closer value, starting at the*/
	                                      /* last data point.               */
		u8Diff =(uint8)abs((int16)u8Input-(int16)(pu8_1[u8Index]));/* Calc absolute difference.  */
		if (u8Diff < u8MinimumDiff)
		{                                   /* This data point is closest so  */
			u8MinimumDiff = u8Diff;          /* far. Save it as the closest.   */
			u8NewValue = u8Index;
		}
	}
	return u8NewValue;
}

/* ======================================================================== */
/* ======================================================================== */
/* This function takes a pointer to an array,along with the size of the     */
/*   array and finds the entry that is closest to the input value.          */
/* If there are two entries in the array that are equidistant from the      */
/*   input, the higher index is returned.                                   */
/*                                                                          */
/* Inputs:  uint8 * au8DataTable       pointer to an array of uint8's       */
/*          uint8 u8Size               size of the array                    */
/*          uint8 u8Input              value that will be compared          */
/* Returns: as uint8 the index pointing to the closest entry in the array   */
/* ======================================================================== */
uint8 ALG_cu8GetClosestEntry(const uint8 pu8_1[], uint8 u8Size, uint8 u8Input)
{
	uint8 u8Index;
	uint8 u8Diff;
	uint8 u8MinimumDiff;
	uint8 u8NewValue;

	u8MinimumDiff  =(uint8) 0xFFu;            /* Seed the successive difference */
	u8NewValue     = u8Size-(uint8)1u;             /* tracker with 255. Even if all  */
	                                      /* of the data in array is zero,  */
	                                      /* the result will be the highest */
	                                      /* index.                         */

	for ( u8Index = u8Size; u8Index--;)  /* Scan through array looking for */
	{                                      /* a closer value, starting at the*/
	                                      /* last data point.               */
		u8Diff =(uint8)abs((int16)u8Input-(int16)(pu8_1[u8Index]));/* Calc absolute difference.  */
		if (u8Diff < u8MinimumDiff)
		{                                   /* This data point is closest so  */
			u8MinimumDiff = u8Diff;          /* far. Save it as the closest.   */
			u8NewValue = u8Index;
		}
	}
	return u8NewValue;
}

/* ======================================================================== */
/* This function takes a pointer to an array,along with the size of the     */
/*   array and finds the entry that is closest to the input value.          */
/* If there are two entries in the array that are equidistant from the      */
/*   input, the higher index is returned.                                   */
/*                                                                          */
/* Inputs:  uint16 * au16DataTable       pointer to an array of uint8's       */
/*          uint8 u8Size               size of the array                    */
/*          uint16 u8Input              value that will be compared          */
/* Returns: as uint16 the index pointing to the closest entry in the array   */
/* ======================================================================== */
uint16 ALG_u16GetClosestEntry(uint16 pu16_1[], uint8 u8Size, uint16 u16Input)
{	

	uint8 u8Index;
	uint16 u16Diff;
	uint16 u16MinimumDiff;
	uint8 u8NewValue;
	
	u16MinimumDiff  = (uint16)0xFFFFu;            /* Seed the successive difference */
	u8NewValue     = u8Size-(uint8)1u;             /* tracker with 255. Even if all  */
	                                      /* of the data in array is zero,  */
	                                      /* the result will be the highest */
	                                      /* index.                         */

	//for ( u8Index = u8Size-(uint8)1u;u8Index>0u;u8Index--)  /* Scan through array looking for */
	for ( u8Index = u8Size;u8Index--;) 
	{                                      /* a closer value, starting at the*/
	                                      /* last data point.               */
		if(u16Input > (pu16_1[u8Index])) /* Calc absolute difference.  */
		{
			u16Diff = (u16Input-(pu16_1[u8Index]) );
		} else
		{
			u16Diff = ((pu16_1[u8Index]) - u16Input );
		}
		
		if (u16Diff < u16MinimumDiff)
		{                                   /* This data point is closest so  */
			u16MinimumDiff = u16Diff;          /* far. Save it as the closest.   */
			u8NewValue = u8Index;
		}
	}
	return (uint16)u8NewValue;
}
/* ======================================================================== */
/* This function takes a pointer to an array,along with the size of the     */
/*   array and finds the entry that is closest to the input value.          */
/* If there are two entries in the array that are equidistant from the      */
/*   input, the higher index is returned.                                   */
/*                                                                          */
/* Inputs:  uint16 * au16DataTable       pointer to an array of uint8's       */
/*          uint8 u8Size               size of the array                    */
/*          uint16 u8Input              value that will be compared          */
/* Returns: as uint16 the index pointing to the closest entry in the array   */
/* ======================================================================== */
uint16 ALG_cu16GetClosestEntry(const uint16 pu16_1[], uint8 u8Size, uint16 u16Input)
{
	uint8 u8Index;
	uint16 u16Diff;
	uint16 u16MinimumDiff;
	uint8 u8NewValue;

	u16MinimumDiff  = (uint16)0xFFFFu;            /* Seed the successive difference */
	u8NewValue     = u8Size-(uint8)1u;             /* tracker with 255. Even if all  */
	                                      /* of the data in array is zero,  */
	                                      /* the result will be the highest */
	                                      /* index.                         */

	for ( u8Index = u8Size-(uint8)1u;u8Index--;)  /* Scan through array looking for */
	{                                      /* a closer value, starting at the*/
	                                      /* last data point.               */
		if(u16Input > (pu16_1[u8Index])) /* Calc absolute difference.  */
		{
			u16Diff = (u16Input-(pu16_1[u8Index]) );
		} else
		{
			u16Diff = ((pu16_1[u8Index]) - u16Input );
		}
		
		if (u16Diff < u16MinimumDiff)
		{                                   /* This data point is closest so  */
			u16MinimumDiff = u16Diff;          /* far. Save it as the closest.   */
			u8NewValue = u8Index;
		}
	}
	return (uint16)u8NewValue;
}

/* ======================================================================== */
/* ======================================================================== */	

/* Function :     PTA_u16CurveLookup_16_16_Limit                               */
/* Description :  This function impliments an 16-bit curve lookup.           */
/*                The input value is converted , using the characteristic   */
/*                curve. If the input is outside the range of x-values the  */
/*                last y-value is returned, hence the "limit".              */
/* Inputs :       u16Input  - The 16 bit unsigned input value.                */
/*                pau16XCurve - A pointer to an array of 16-bit values. This  */
/*                   array must be monotonically increasing.                */
/*                pau16YCurve - A pointer to an array of 16-bit values. This  */
/*                   array can be any function whatsoever. The values are   */
/*                   linearly interpolated between. The size of this array  */
/*                   must be the same as the x-value array.                 */
/*                u8Size    - The amount of points in the curves   .        */
/*            Y                                                             */
/*            ^                                   X******                   */
/*            |                                  *                          */
/*            |                                 *                           */
/*    returns<|           X*****X              *                            */
/*            |          *       *            *                             */
/*            |      X**X         *          *                              */
/*            |*****X              X********X                               */
/*            |                                                             */
/*            |                                                             */
/*            +------------------------------------------>X                 */
/*                           ^                                              */
/*                           u16Input                                        */
/*                                                                          */
/* Returns :      The 16-bit output if the interpolation                     */
/* ======================================================================== */	
uint16 ALG_u16CurveLookup_16_16_Limit( uint16 pu16_1[], uint16 pu16_2[], const uint16 u16Input, const uint8 u8Size )
{
   uint8 u8Index;
   uint16  u16x1;          
   uint16  u16y1; 
   uint16 u16ReturnValue;
   int32  i32xdiff;       
   int32  i32ydiff;
   int32 i32ReturnValue;
   
   u8Index = u8Size-(uint8)1u;
   if ( u16Input >= pu16_1[u8Index]) /* past the last point */
   {
      u16ReturnValue=pu16_2[(u8Size-1u)];        /* return the last y data point */
   }
   else
   {
      if (u16Input <= pu16_1[0]) /* we are between 0 and the 1st point */
      {
         u16ReturnValue=pu16_2[0];
      }
      else /* normal range interpolation */
      {
         //for ( u8Index=u8Size-(uint8)1u;u8Index>(uint8)0u;u8Index--)
	  for ( u8Index=u8Size-(uint8)1u;u8Index--;)
         {
            if (u16Input > pu16_1[u8Index])
            {
               u16x1 = pu16_1 [u8Index];
               u16y1 = pu16_2 [u8Index];
               i32ydiff = (int32)pu16_2 [u8Index+1u] - (int32)u16y1;
               i32xdiff = (int32)pu16_1 [u8Index+1u] - (int32)u16x1;
               if ( (i32xdiff ==0L)||(i32ydiff==0L)) 
               {
                 u16ReturnValue=u16y1;
               }
               u8Index =0u;
            }
         }
         i32ReturnValue=((int32)u16y1 + (i32ydiff *((int32)u16Input - (int32)u16x1) / i32xdiff));
         u16ReturnValue=(uint16)i32ReturnValue;
      }
   }
   return u16ReturnValue;
}
/* ======================================================================== */
/* ======================================================================== */	

/* Function :     PTA_u16CurveLookup_16_16_Limit                               */
/* Description :  This function impliments an 16-bit curve lookup.           */
/*                The input value is converted , using the characteristic   */
/*                curve. If the input is outside the range of x-values the  */
/*                last y-value is returned, hence the "limit".              */
/* Inputs :       u16Input  - The 16 bit unsigned input value.                */
/*                pau16XCurve - A pointer to an array of 16-bit values. This  */
/*                   array must be monotonically increasing.                */
/*                pau16YCurve - A pointer to an array of 16-bit values. This  */
/*                   array can be any function whatsoever. The values are   */
/*                   linearly interpolated between. The size of this array  */
/*                   must be the same as the x-value array.                 */
/*                u8Size    - The amount of points in the curves   .        */
/*            Y                                                             */
/*            ^                                   X******                   */
/*            |                                  *                          */
/*            |                                 *                           */
/*    returns<|           X*****X              *                            */
/*            |          *       *            *                             */
/*            |      X**X         *          *                              */
/*            |*****X              X********X                               */
/*            |                                                             */
/*            |                                                             */
/*            +------------------------------------------>X                 */
/*                           ^                                              */
/*                           u16Input                                        */
/*                                                                          */
/* Returns :      The 16-bit output if the interpolation                     */
/* ======================================================================== */	
uint16 ALG_cu16CurveLookup_16_16_Limit( const uint16 pu16_1[],const uint16 pu16_2[], const uint16 u16Input, const uint8 u8Size )
{
   uint8 u8Index;
   uint16  u16x1;          
   uint16  u16y1; 
   uint16 u16ReturnValue;
   int32  i32xdiff;       
   int32  i32ydiff;
   int32 i32ReturnValue;
   
   u8Index = u8Size-(uint8)1u;
   if ( u16Input >= pu16_1[u8Index]) /* past the last point */
   {
      u16ReturnValue=pu16_2[(u8Size-1u)];        /* return the last y data point */
   }
   else
   {
      if (u16Input <= pu16_1[0]) /* we are between 0 and the 1st point */
      {
         u16ReturnValue=pu16_2[0];
      }
      else /* normal range interpolation */
      {
         //for ( u8Index=u8Size-(uint8)1u;u8Index>(uint8)0u;u8Index--)
	  for ( u8Index=u8Size-(uint8)1u;u8Index--;)
         {
            if (u16Input > pu16_1[u8Index])
            {
               u16x1 = pu16_1 [u8Index];
               u16y1 = pu16_2 [u8Index];
               i32ydiff = (int32)pu16_2 [u8Index+1u] - (int32)u16y1;
               i32xdiff = (int32)pu16_1 [u8Index+1u] - (int32)u16x1;
               if ( (i32xdiff ==0L)||(i32ydiff==0L)) 
               {
                 u16ReturnValue=u16y1;
               }
               u8Index =0u;
            }
         }
         i32ReturnValue=((int32)u16y1 + (i32ydiff *((int32)u16Input - (int32)u16x1) / i32xdiff));
         u16ReturnValue=(uint16)i32ReturnValue;
      }
   }
   return u16ReturnValue;
}



uint16 ALG_u16InputProcessChannel(ALG_tstInputAttributes *pAtr, uint16 u16In, uint8 *pu8InputUsable)
{
    uint8  u8InputUsable = 1U;   /*- u8InputUsable stand for if this input is usable now. -*/
    uint16 u16ErrMask;      /*- u16ErrMask is to report the current input error status. -*/
    uint16 u16New;          /*- u16New is to stored input to be used. -*/
    /*- Input is invalid(FF) or out of range.-*/
    if((u16In == pAtr->nInit)\
        ||(u16In < pAtr->nMinVal)\
            ||(u16In > pAtr->nMaxVal))
    {
        /*- As time nErrWaitTime is run over after IG ON, default value nDefault would be used. -*/
        if(pAtr->u8ErrCounter < pAtr->nErrWaitTime)
        {
            pAtr->u8ErrCounter++;
            u16New = pAtr->nInit;
            u8InputUsable = 0U;
        }
        else
        {
        	if(pAtr->nInputType == nUint8InputType)
        	{
	        	/*- Default value nDefault would be used. -*/
	            if(*(pAtr->pu8Addr) == pAtr->nInit)
	            {
	                u16New = pAtr->nDefault;
	            }
	            /*- The lastest value would be used. -*/
	            else 
	            {
	                /*- Keep the lastest valid value. -*/
	                u16New = *(pAtr->pu8Addr);
	            }
            }
			else if(pAtr->nInputType == nUint16InputType)
            {
    	        	/*- Default value nDefault would be used. -*/
	            if(*(pAtr->pu16Addr) == pAtr->nInit)
	            {
	                u16New = pAtr->nDefault;
	            }
	            /*- The lastest value would be used. -*/
	            else 
	            {
	                /*- Keep the lastest valid value. -*/
	                u16New = *(pAtr->pu16Addr);
	            }        	
            }
			else
			{
				/*nothing to do*/
			}
			
        }

        u16ErrMask = pAtr->nErrMask;
    }
    else 
    {
        /* The input is valid, u16In is uesd.*/
        pAtr->u8ErrCounter = pAtr->nErrWaitTime;
        u16New = u16In;
        u16ErrMask = 0U;
    }

    if(pAtr->nInputType == nUint8InputType)
    {
        *(pAtr->pu8Addr) = (uint8)u16New;
    }
    else if(pAtr->nInputType == nUint16InputType)
    {
        *(pAtr->pu16Addr) = u16New;
    }
    else
    {

    }
    /*- Write the input usable flag. -*/
    *pu8InputUsable = u8InputUsable;
    /*- Return error status of this channel. -*/
    return(u16ErrMask);
}


void ALG_vInputSigleChannelInit(ALG_tstInputAttributes *pAtr)
{
    pAtr->u8ErrCounter = 0U;
    
    if(pAtr->nInputType == nUint8InputType)
    {
        *(pAtr->pu8Addr) = (uint8)((*pAtr).nInit);
    }
    else if(pAtr->nInputType == nUint16InputType)
    {
        *(pAtr->pu16Addr) = pAtr->nInit;
    }
    else
    {
        
    }
}


#if 1
/* ======================================================================== */
/* ======================================================================== */
uint8 ALG_u8SensorFilter(const tstSensorFilterConstantType SensorPar[], tstSensorFilterVariableType SensorVar[])
/* Function :     ALG_u8SensorFilter                               */
/* Description :  This function filter the sensor disturbance.           */
/* Inputs :       SensorPar  - Input the constant parameters.                */
/*                   SensorVar - The patameters will be changed  */
/* Returns :      0 - OK                     */
/*                    1 - Over Range                     */
/*                    2 - SensorPar[0].au16Raw[] from large to small                     */
{
	uint16 u16SensorAD;
	uint16 u16CurrentSensorValue;
	uint8 u8ErrorType=0u;

	u16SensorAD = SensorVar[0].u16SensorAD;
	if ( (u16SensorAD < SensorPar[0].u16MinLimitValue) || (u16SensorAD > SensorPar[0].u16MaxLimitValue) )
	{
		if ( SensorVar[0].u8ErrorCount < 0xFFu )
		{
			SensorVar[0].u8ErrorCount++;
		}

		if ( SensorVar[0].u8ErrorCount > SensorPar[0].u8ErrorCountTimeout )
		{
			SensorVar[0].u8SensorErrorFlag = True;
			SensorVar[0].u16SensorValue = SensorPar[0].u16SensorDefaultValue;
		}

		u8ErrorType = 1u;
	}
	else
	{
		SensorVar[0].u8ErrorCount = 0u;
		u16CurrentSensorValue = ALG_u16CurveLookup_16_16_Limit( SensorPar[0].au16Raw, SensorPar[0].au16Result, 
																u16SensorAD, SensorPar[0].u8Length );

		if ( (SensorVar[0].u8SensorErrorFlag) || (SensorVar[0].u8InitFlag == ColdBoot) )
		{
			SensorVar[0].u8SensorErrorFlag = False;
			SensorVar[0].u8InitFlag = HotBoot;
			SensorVar[0].u16SensorValue = u16CurrentSensorValue;
			SensorVar[0].u32InterimValue = (uint32)u16CurrentSensorValue<<16;
		}
		else
		{
			SensorVar[0].u16SensorValue = ALG_u16FirstOrderFilter(&(SensorVar[0].u32InterimValue), u16CurrentSensorValue, 
																SensorPar[0].u8FilterParameter); 
		}
																
		if ( SensorPar[0].au16Raw[0] > SensorPar[0].au16Raw[SensorPar[0].u8Length-1u] )
		{
			u8ErrorType = 2u;
		}
	}

	return u8ErrorType;
}
#endif
/*****************************************************************************
* EOF: Alg.c
*****************************************************************************/



