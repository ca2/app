// From image32_array.cpp by camilo on 2023-06-13 15:47 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "color_array.h"


//colorref_array::colorref_array()
//{
//
//}


color_array::~color_array()
{

}


void color_array::create_web_palette()
{

   // Do nothing
   const u32 STANDARD_PALETTE[] = {00,51,102,153,204,255};
   const i32 STANDARD_COLOR_SIZE = 6;
//   const ::i32 STANDARD_PALETTE_VAL_DIF = 51;
   allocate(216);
//   u32 dwColorMapTable[216] = {0};
   i32 nColorMapIdx = 0;
   for(i32 nBlueIdx = 0; nBlueIdx < STANDARD_COLOR_SIZE; ++nBlueIdx)
   {
      for(i32 nGreenIdx = 0; nGreenIdx < STANDARD_COLOR_SIZE; ++nGreenIdx)
      {
         for(i32 nRedIdx = 0; nRedIdx < STANDARD_COLOR_SIZE; ++nRedIdx)
         {
            this->element_at(nColorMapIdx) = argb(255, (::u8) STANDARD_PALETTE[nRedIdx],
             (::u8) STANDARD_PALETTE[nGreenIdx],
               (::u8) STANDARD_PALETTE[nBlueIdx]);
            ++nColorMapIdx;

         }

      }

   }

}


namespace draw2d
{



   CLASS_DECL_ACME void colora_from_quada(color_array & colora, WINRGBQUAD * prgbquad, int iCount)
   {

      colora.set_size(iCount);

      for (index i = 0; i < iCount; i++)
      {

//#if defined(ANDROID) && defined(__arm__)
         colora[i] = argb(255, prgbquad[i].rgbRed, prgbquad[i].rgbGreen, prgbquad[i].rgbBlue);
//#else
//         colorrefa[i] = argb(255, prgbquad[i].rgbBlue, prgbquad[i].rgbGreen, prgbquad[i].rgbRed);
//#endif

//         if (colora[i] == argb(255, 255, 255, 255))
//         {
//
//            infomration("colora_from_quada  completely white");
//
//         }

      }

   }


} // namespace draw2d



