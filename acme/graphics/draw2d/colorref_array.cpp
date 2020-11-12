#include "framework.h"


colorref_array::colorref_array()
{

}


colorref_array::~colorref_array()
{

}


void colorref_array::create_web_palette()
{

   // Do nothing
   const u32 STANDARD_PALETTE[] = {00,51,102,153,204,255};
   const INT STANDARD_COLOR_SIZE = 6;
//   const INT STANDARD_PALETTE_VAL_DIF = 51;
   allocate(216);
//   u32 dwColorMapTable[216] = {0};
   i32 nColorMapIdx = 0;
   for(i32 nBlueIdx = 0; nBlueIdx < STANDARD_COLOR_SIZE; ++nBlueIdx)
   {
      for(i32 nGreenIdx = 0; nGreenIdx < STANDARD_COLOR_SIZE; ++nGreenIdx)
      {
         for(i32 nRedIdx = 0; nRedIdx < STANDARD_COLOR_SIZE; ++nRedIdx)
         {
            this->element_at(nColorMapIdx) = ARGB(255, (byte) STANDARD_PALETTE[nRedIdx],
             (byte) STANDARD_PALETTE[nGreenIdx],
               (byte) STANDARD_PALETTE[nBlueIdx]);
            ++nColorMapIdx;
         }
      }
   }
}
