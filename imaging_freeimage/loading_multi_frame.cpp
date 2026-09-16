#include "platform.h"
#include "image_context.h"
#include "fimemory.h"
#include "acme/platform/scoped_restore.h"
////#include "acme/exception/exception.h"
#include "acme/prototype/time/_text_stream.h"
#include "acme/graphics/image/frame.h"
#include "acme/graphics/image/frame_array.h"


#if defined(USE_PORT_FREEIMAGE)
#include <port_freeimage/FreeImage.h>
#else
#include <FreeImage.h>
#endif


CLASS_DECL_ACME ::string as_string(::draw2d::enum_disposal edisposal);
CLASS_DECL_ACME void set_first_multi_frame_loaded();


struct FIBITMAP;


namespace imaging_freeimage
{


   bool freeimage_load_imagea_frame(::pixmap *ppixmapImageCompose, ::image::image_frame_array * pimagea, ::collection::index iFrame, FIBITMAP * pfi);


   void image_context::_load_image(::pixmap *ppixmapImageCompose, ::pointer<::image::image_frame_array>& pframea, memory & memory)
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

            if (!multibitmap)
            {

               throw ::exception(error_failed, "GIF: could not open frame data");

            }

            try
            {

               ::collection::count cFrame = FreeImage_GetPageCount(multibitmap);

               for (::collection::index iFrame = 0; iFrame < cFrame; iFrame++)
               {

                  auto pframe = allocateø ::image::image_frame();

                  pframea->add(pframe);

                  construct_newø(pframe->m_ppixmap);

                  pframe->m_iFrame = iFrame;

                  FIBITMAP * pfi = FreeImage_LockPage(multibitmap, (::i32)iFrame);

                  if (!pfi)
                  {

                     throw ::exception(error_failed, "GIF: could not lock frame");

                  }

                  at_end_of_scope
                  {

                     FreeImage_UnlockPage(multibitmap, pfi, FALSE);

                  };

                  if (pfi != nullptr)
                  {

                     ::i32 w = FreeImage_GetWidth(pfi);

                     ::i32 h = FreeImage_GetHeight(pfi);

                     FITAG * ptag;

                     if (iFrame <= 0)
                     {

                        pframea->m_size = {w, h};

                        if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "LogicalWidth", &ptag))
                        {

                           if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                           {

                              pframea->m_size.cx = *((::i16 *)FreeImage_GetTagValue(ptag));

                           }

                        }

                        if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "LogicalHeight", &ptag))
                        {

                           if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                           {

                              pframea->m_size.cy = *((::i16 *)FreeImage_GetTagValue(ptag));

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

                              pframea->m_countLoop = (::u32)*((::u32 *)FreeImage_GetTagValue(ptag));

                           }

                        }

                        ppixmapImageCompose->create_as_descriptor(pframea->m_size);

                        // A descriptor has dimensions but no allocated pixels yet.
                        auto ppixmapCompose = ppixmapImageCompose->map();
                        ppixmapCompose->clear(::color::transparent);

                     }

                     pframe->m_rectangle.left = 0;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameLeft", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                        {

                           pframe->m_rectangle.left = *((::i16 *)FreeImage_GetTagValue(ptag));

                        }

                     }

                     pframe->m_rectangle.right = pframe->m_rectangle.left + w;

                     pframe->m_rectangle.top = 0;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameTop", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                        {

                           pframe->m_rectangle.top = *((::i16 *)FreeImage_GetTagValue(ptag));

                        }

                     }

                     pframe->m_rectangle.bottom = pframe->m_rectangle.top + h;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "NoLocalPalette", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_BYTE)
                        {

                           pframe->m_bLocalPalette = *((::u8 *)FreeImage_GetTagValue(ptag)) == 0;

                        }

                     }

                     pframe->m_edisposal = draw2d::e_disposal_undefined;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "DisposalMethod", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_BYTE)
                        {

                           auto iDisposal = *((::u8 *)FreeImage_GetTagValue(ptag));

                           pframe->gif_set_disposal(iDisposal);

                        }

                     }

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameTime", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_LONG)
                        {

                           ::u32 uMillisecond = *(::u32 *)FreeImage_GetTagValue(ptag);

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

                     auto edisposal = pframe->m_edisposal;

                     auto strDisposal = ::as_string(edisposal);

                     if (iFrame == 3)
                     {

                        information("frame {} disposal {}", iFrame, strDisposal);

                     }
                     else if (iFrame == 29)
                     {

                        information("frame {} disposal {}", iFrame, strDisposal);

                     }
                     else if (iFrame == 30)
                     {

                        information("frame {} disposal {}", iFrame, strDisposal);

                     }
                     else
                     {

                        information("frame {} disposal {}", iFrame, strDisposal);

                     }

                     if (!freeimage_load_imagea_frame(ppixmapImageCompose, pframea, iFrame, pfi))
                     {

                        throw ::exception(error_failed, "GIF: failed to decode frame pixels");

                     }

                  }

               }

            }
            catch (...)
            {

               FreeImage_CloseMultiBitmap(multibitmap);
               throw;

            }

            FreeImage_CloseMultiBitmap(multibitmap);

         }

      }
      catch (...)
      {
         //return false;

         throw;

      }

      set_first_multi_frame_loaded();
      //return true;

   }


   bool freeimage_load_imagea_frame(::pixmap *ppixmapImageCompose, ::image::image_frame_array * pframea, ::collection::index iFrame, FIBITMAP * pfi)
   {

      if (pfi == nullptr)
      {

         throw ::exception(error_failed, "GIF: failed to decode frame pixels");

         return false;

      }

      ::image::image_frame * pframe = pframea->element_at(iFrame);

      //BITMAPINFO * pbi = nullptr;

      //void * pdata = nullptr;

      //pbi = FreeImage_GetInfo(pfi);

      //pdata = FreeImage_GetBits(pfi);

      //::i32 w = FreeImage_GetWidth(pfi);

      //::i32 h = FreeImage_GetHeight(pfi);

      ::pixmap_pointer ppixmapImageFrame;

      //auto estatus = 
      
      ppixmapImageCompose->construct_newø(ppixmapImageFrame);

      //if (!estatus || !pimageFrame)
      if (!ppixmapImageFrame)
      {

         throw ::exception(error_failed, "GIF: failed to decode frame pixels");

         return false;

      }

      if (!pixmap_from_freeimage(ppixmapImageFrame, pfi))
      {

         throw ::exception(error_failed, "GIF: failed to decode frame pixels");

         return false;

      }

      ::draw2d::enum_disposal edisposal = iFrame <= 0 ? ::draw2d::e_disposal_none : pframea->element_at(iFrame)->m_edisposal;

      pframe->m_edisposal = edisposal;

      pframe->_001Process(ppixmapImageCompose, ppixmapImageFrame, pframea);

      // Each animation frame needs its own snapshot of the composed canvas.
      pframe->create_frame(pframe, ppixmapImageCompose, pframea);

      auto diagnosticsFrame = _001_image32_diagnostics_t(ppixmapImageFrame);

      ::string strDisposal = ::as_string(edisposal);

      ::string strDiagnosticFrame = diagnosticsFrame.as_string();

      if (diagnosticsFrame.transparentCount > 100)
      {

         information("frame {} edisposal {} diagnostics: {}", iFrame, strDisposal, strDiagnosticFrame);

      }
      else
      {

         information("frame {} edisposal {} diagnostics: {}", iFrame, strDisposal, strDiagnosticFrame);

      }

      auto diagnosticsCompose = _001_image32_diagnostics_t(ppixmapImageCompose);

      ::string strDiagnosticCompose = diagnosticsCompose.as_string();

      if (diagnosticsCompose.transparentCount > 0)
      {

         information("composed frame {} diagnostics: {}", iFrame, strDiagnosticCompose);

      }
      else if (diagnosticsCompose.translucentCount > 0)
      {

         information("composed frame {} diagnostics: {}", iFrame, strDiagnosticCompose);

      }
      else
      {

         information("composed frame {} diagnostics: {}", iFrame, strDisposal, strDiagnosticCompose);

      }




//      ::i32 transparentIndex = FreeImage_GetTransparentIndex(pfi);
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
//      ::i32 iScan = FreeImage_GetPitch(pfi);
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
//            /*if (!draw2d_gif_load_frame(pimageCompose, pframea, pframe, iFrame, (::u8 *)pdata, iScan, cra, transparentIndex))
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
//            //if (!draw2d_gif_load_frame(pimageCompose, pframea, pframe, iFrame, (::u8 *)pdata, iScan, pframea->m_colorrefa, transparentIndex))
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

