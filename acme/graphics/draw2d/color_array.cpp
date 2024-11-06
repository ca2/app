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
   const unsigned int STANDARD_PALETTE[] = {00,51,102,153,204,255};
   const int STANDARD_COLOR_SIZE = 6;
//   const int STANDARD_PALETTE_VAL_DIF = 51;
   set_size(216);
//   unsigned int dwColorMapTable[216] = {0};
   int nColorMapIdx = 0;
   for(int nBlueIdx = 0; nBlueIdx < STANDARD_COLOR_SIZE; ++nBlueIdx)
   {
      for(int nGreenIdx = 0; nGreenIdx < STANDARD_COLOR_SIZE; ++nGreenIdx)
      {
         for(int nRedIdx = 0; nRedIdx < STANDARD_COLOR_SIZE; ++nRedIdx)
         {
            this->element_at(nColorMapIdx) = argb(255, (unsigned char) STANDARD_PALETTE[nRedIdx],
             (unsigned char) STANDARD_PALETTE[nGreenIdx],
               (unsigned char) STANDARD_PALETTE[nBlueIdx]);
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

      for (::collection::index i = 0; i < iCount; i++)
      {

//#if defined(ANDROID) && defined(__arm__)
         colora[i] = argb(255, prgbquad[i].rgbRed, prgbquad[i].rgbGreen, prgbquad[i].rgbBlue);
//#else
//         colorrefa[i] = argb(255, prgbquad[i].rgbBlue, prgbquad[i].rgbGreen, prgbquad[i].rgbRed);
//#endif

//         if (colora[i] == argb(255, 255, 255, 255))
//         {
//
//            informationf("colora_from_quada  completely white");
//
//         }

      }

   }


} // namespace draw2d



