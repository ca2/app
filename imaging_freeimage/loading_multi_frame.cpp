#include "framework.h"
#include "image_context.h"
#include "fimemory.h"
////#include "acme/exception/exception.h"
#include "acme/prototype/time/_text_stream.h"
#include "aura/graphics/image/frame.h"
#include "aura/graphics/image/frame_array.h"


#include <FreeImage.h>


struct FIBITMAP;


namespace imaging_freeimage
{


   bool freeimage_load_imagea_frame(::image::image *pimageCompose, ::image::image_frame_array * pimagea, ::collection::index iFrame, FIBITMAP * pfi);


   void image_context::_load_image(::image::image *pimageCompose, ::pointer<::image::image_frame_array>& pframea, memory & memory)
   {

      fimemory mem(memory);

      if (!mem)
      {

         throw ::exception(error_failed);

      }

      FIMULTIBITMAP * multibitmap = nullptr;

      try
      {

         FREE_IMAGE_FORMAT format = mem.get_image_format();

         //if (true)
         {

            multibitmap = FreeImage_LoadMultiBitmapFromMemory(format, mem);

            try
            {

               ::collection::count cFrame = FreeImage_GetPageCount(multibitmap);

               for (::collection::index iFrame = 0; iFrame < cFrame; iFrame++)
               {

                  auto pframe = __allocate ::image::image_frame();

                  pframea->add(pframe);

                  __øconstruct(pframe->m_pimage);

                  pframe->m_iFrame = iFrame;

                  FIBITMAP * pfi = FreeImage_LockPage(multibitmap, (int)iFrame);

                  if (pfi != nullptr)
                  {

                     int w = FreeImage_GetWidth(pfi);

                     int h = FreeImage_GetHeight(pfi);

                     FITAG * ptag;

                     if (iFrame <= 0)
                     {

                        if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "LogicalWidth", &ptag))
                        {

                           if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                           {

                              pframea->m_size.cx() = *((short *)FreeImage_GetTagValue(ptag));

                           }

                        }

                        if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "LogicalHeight", &ptag))
                        {

                           if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                           {

                              pframea->m_size.cy() = *((short *)FreeImage_GetTagValue(ptag));

                           }

                        }

                        if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "GlobalPalette", &ptag))
                        {

                           if (FreeImage_GetTagType(ptag) == FIDT_PALETTE)
                           {

                              ::draw2d::colora_from_quada(pframea->m_colora, (WINRGBQUAD *)FreeImage_GetTagValue(ptag), FreeImage_GetTagCount(ptag));

                           }

                        }

                        if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "Loop", &ptag))
                        {

                           if (FreeImage_GetTagType(ptag) == FIDT_LONG)
                           {

                              pframea->m_countLoop = (unsigned int)*((unsigned int *)FreeImage_GetTagValue(ptag));

                           }

                        }

                        pimageCompose->create(pframea->m_size);

                        pimageCompose->clear(::color::transparent);

                     }

                     pframe->m_rectangle.left() = 0;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameLeft", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                        {

                           pframe->m_rectangle.left() = *((short *)FreeImage_GetTagValue(ptag));

                        }

                     }

                     pframe->m_rectangle.right() = pframe->m_rectangle.left() + w;

                     pframe->m_rectangle.top() = 0;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameTop", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                        {

                           pframe->m_rectangle.top() = *((short *)FreeImage_GetTagValue(ptag));

                        }

                     }

                     pframe->m_rectangle.bottom() = pframe->m_rectangle.top() + h;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "NoLocalPalette", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_BYTE)
                        {

                           pframe->m_bLocalPalette = *((unsigned char *)FreeImage_GetTagValue(ptag)) == 0;

                        }

                     }

                     pframe->m_edisposal = draw2d::e_disposal_undefined;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "DisposalMethod", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_BYTE)
                        {

                           auto iDisposal = *((unsigned char *)FreeImage_GetTagValue(ptag));

                           pframe->gif_set_disposal(iDisposal);

                        }

                     }

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameTime", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_LONG)
                        {

                           unsigned int uMillisecond = *(unsigned int *)FreeImage_GetTagValue(ptag);

                           pframe->m_time = millisecond_time(uMillisecond);

                        }

                     }

                     if(pframe->m_time < 1_ms)
                     {

                        pframe->m_time = 1_ms;

                     }
                     else if(pframe->m_time > 1_s)
                     {

                        information() << "Long frame time " << pframe->m_time.integral_second();

                     }

                     if (!freeimage_load_imagea_frame(pimageCompose, pframea, iFrame, pfi))
                     {

                        informationf("failed to load page image");

                     }

                  }

               }

            }
            catch (...)
            {

            }

            FreeImage_CloseMultiBitmap(multibitmap);

         }

      }
      catch (...)
      {
         //return false;

         throw ::exception(error_failed);

      }

      //return true;

   }


   bool freeimage_load_imagea_frame(::image::image *pimageCompose, ::image::image_frame_array * pframea, ::collection::index iFrame, FIBITMAP * pfi)
   {

      if (pfi == nullptr)
      {

         return false;

      }

      ::image::image_frame * pframe = pframea->element_at(iFrame);

      //BITMAPINFO * pbi = nullptr;

      //void * pdata = nullptr;

      //pbi = FreeImage_GetInfo(pfi);

      //pdata = FreeImage_GetBits(pfi);

      //int w = FreeImage_GetWidth(pfi);

      //int h = FreeImage_GetHeight(pfi);

      ::image::image_pointer pimageFrame;

      //auto estatus = 
      
      pimageCompose->__øconstruct(pimageFrame);

      //if (!estatus || !pimageFrame)
      if (!pimageFrame)
      {

         return false;

      }

      image_from_freeimage(pimageFrame, pfi);

      ::draw2d::enum_disposal edisposal = iFrame <= 0 ? ::draw2d::e_disposal_none : pframea->element_at(iFrame)->m_edisposal;

      pframe->m_edisposal = edisposal;

      pframe->_001Process(pimageCompose, pimageFrame, pframea);


//      int transparentIndex = FreeImage_GetTransparentIndex(pfi);
//
//      bool bIsTransparent = FreeImage_IsTransparent(pfi) != 0;
//
//      if (!bIsTransparent)
//      {
//
//         transparentIndex = -1;
//
//      }
//
//      RGBQUAD quad;
//
//      if (FreeImage_GetBackgroundColor(pfi, &quad))
//      {
//
//         informationf("has background color");
//
//      }
//
//      int iScan = FreeImage_GetPitch(pfi);
//
//      if (FreeImage_GetBPP(pfi) == 8)
//      {
//
//         if (pframe->m_bLocalPalette && pbi->bmiHeader.biClrUsed > 0)
//         {
//
//            colorref_array cra;
//
//            cra_from_quada(cra, pbi->bmiColors, pbi->bmiHeader.biClrUsed);
//
//            /*if (!draw2d_gif_load_frame(pimageCompose, pframea, pframe, iFrame, (unsigned char *)pdata, iScan, cra, transparentIndex))
//            {
//
//               return false;
//
//            }*/
//
//         }
//         else
//         {
//
//#if defined(__ANDROID__) && defined(__arm__)
//
//            color32_t crQuad = argb(255, quad.rgbRed, quad.rgbGreen, quad.rgbBlue);
//
//#else
//
//            //color32_t crQuad = argb(255, quad.rgbBlue, quad.rgbGreen, quad.rgbRed);
//
//#endif
//
//            //if (!draw2d_gif_load_frame(pimageCompose, pframea, pframe, iFrame, (unsigned char *)pdata, iScan, pframea->m_colorrefa, transparentIndex))
//            //{
//
//            //   return false;
//
//            //}
//
//         }
//
//      }
//      else if (FreeImage_GetBPP(pfi) == 32)
//      {
//
//         ::copy_image32(pframe->m_pimage->image32(), pframe->m_pimage->width(), pframe->m_pimage->height(), pframe->m_pimage->scan_size(), (color32_t *)pdata, iScan);
//
//         return true;
//
//      }
//      else
//      {
//
//         return false;
//
//      }

      return true;

   }


} // namespace imaging_freeimage



