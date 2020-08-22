#include "framework.h"
#include <math.h>

#ifdef LINUX

#include <FreeImage.h>

#else

#include "FreeImage/FreeImage.h"

#endif

#include "pimage->h"


void cra_from_quada(colorref_array & cra, RGBQUAD * pquad, int iCount);

bool draw2d_gif_load_frame(::image * pimageCompose, image & imageCompose, image_frame_array * pimagepointera, image_pointer * pointer, int uFrameIndex, u8 * ba, int iScan, colorref_array & cra, int transparentIndex);

bool freeimage_load_imagea_frame(image & imageCompose, image_frame_array * pimagea, int iFrame, FIBITMAP * pfi, ::object * pobject);

bool imaging::load_image(::object * pobject, image_frame_array * pimagepointera, const ::memory & memory)
{

   fimemory mem(memory);


   if(!mem)
   {

      return false;

   }

   FIMULTIBITMAP * m = nullptr;


   ::image_pointer pimageCompose(pobject);

   try
   {

      FREE_IMAGE_FORMAT format = mem.get_image_format();

      if (true)
      {

         m = FreeImage_LoadMultiBitmapFromMemory(format, mem);

         try
         {

            int c = FreeImage_GetPageCount(m);

            for (index i = 0; i < c; i++)
            {

auto point  = __new(image_pointer);

               pimagepointera->add(point);

               point->m_pimpl = pobject->create_image();


               FIBITMAP * pfi = FreeImage_LockPage(m, (int) i);



               if (pfi != nullptr)
               {

                  int w = FreeImage_GetWidth(pfi);

                  int h = FreeImage_GetHeight(pfi);

                  FITAG * ptag;

                  if (i == 0)
                  {

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "LogicalWidth", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                        {

                           pimagepointera->m_size.cx = *((short *)FreeImage_GetTagValue(ptag));

                        }

                     }

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "LogicalHeight", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                        {

                           pimagepointera->m_size.cy = *((short *)FreeImage_GetTagValue(ptag));

                        }

                     }
                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "GlobalPalette", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_PALETTE)
                        {

                           cra_from_quada(pimagepointera->m_colorrefa, (RGBQUAD *)FreeImage_GetTagValue(ptag), FreeImage_GetTagCount(ptag));

                        }

                     }

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "Loop", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_LONG)
                        {

                           pimagepointera->m_countLoop = (unsigned int) *((long *)FreeImage_GetTagValue(ptag));

                        }

                     }

                     imageCompose.create_image({pobject,  pimagepointera->m_size});


                     imageCompose.fill(0);


                  }
                  point->m_rect.left = 0;
                  if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameLeft", &ptag))
                  {

                     if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                     {

                        point->m_rect.left = *((short *)FreeImage_GetTagValue(ptag));

                     }

                  }
                  point->m_rect.right = point.m_rect.left + w;
                  point->m_rect.top = 0;
                  if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameTop", &ptag))
                  {

                     if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                     {

                        point->m_rect.top = *((short *)FreeImage_GetTagValue(ptag));

                     }

                  }
                  point->m_rect.bottom = point.m_rect.top + h;
                  if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "NoLocalPalette", &ptag))
                  {

                     if (FreeImage_GetTagType(ptag) == FIDT_BYTE)
                     {

                        point->m_bLocalPalette = *((u8 *)FreeImage_GetTagValue(ptag)) == 0;

                     }

                  }
                  point->m_edisposal = draw2d::disposal_undefined;
                  if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "DisposalMethod", &ptag))
                  {

                     if (FreeImage_GetTagType(ptag) == FIDT_BYTE)
                     {
                        switch (*((u8 *)FreeImage_GetTagValue(ptag)))
                        {
                        case 0:
                           point->m_edisposal = draw2d::disposal_undefined;
                           break;
                        case 1:
                           point->m_edisposal = draw2d::disposal_none;
                           break;
                        case 2:
                           point->m_edisposal = draw2d::disposal_background;
                           break;
                        case 3:
                           point->m_edisposal = draw2d::disposal_previous;
                           break;
                        default:
                           point->m_edisposal = draw2d::disposal_undefined;
                           break;
                        }


                     }

                  }

                  if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameTime", &ptag))
                  {

                     if (FreeImage_GetTagType(ptag) == FIDT_LONG)
                     {

                        point->m_tick = (u32) *((long *)FreeImage_GetTagValue(ptag));

                     }

                  }

                  //::draw2d::graphics_pointer spgraphics(papp->create_new, this);

                  //spgraphics->CreateCompatibleDC(nullptr);

                  if (!freeimage_load_imagea_frame(imageCompose, pimagepointera, (int) i, pfi, pobject))
                  {

                     output_debug_string("failed to load page image");

                  }

                  pimagepointera->m_tickTotal += point->m_tick;


                  //try
                  //{
                  //   FreeImage_UnlockPage(m, pfi, false);

                  //}
                  //catch (...)
                  //{


                  //}

               }







            }
         }
         catch (...)
         {


         }

         FreeImage_CloseMultiBitmap(m);

      }

   }
   catch (...)
   {
      return false;

   }

   return true;
}


bool freeimage_load_imagea_frame(image & imageCompose, image_frame_array * pimagepointera, int iFrame, FIBITMAP * pfi, ::object * pobject)
{

   if (pfi == nullptr)
   {

      return false;

   }

   if (pobject == nullptr)
   {

      return false;

   }

   image_pointer * point = pimagepointera->element_at(iFrame);

   BITMAPINFO * pbi = nullptr;

   void * pdata = nullptr;

   pbi = FreeImage_GetInfo(pfi);

   pdata = FreeImage_GetBits(pfi);

   int w = FreeImage_GetWidth(pfi);

   int h = FreeImage_GetHeight(pfi);

   point->m_pimpl = pobject->create_image({w,  h});

   if (point->m_pimpl.is_null())
   {

      return false;

   }

   int transparentIndex = FreeImage_GetTransparentIndex(pfi);

   bool bIsTransparent = FreeImage_IsTransparent(pfi) != 0;

   if (!bIsTransparent)
   {

      transparentIndex = -1;

   }

   RGBQUAD quad;

   if (FreeImage_GetBackgroundColor(pfi, &quad))
   {

      output_debug_string("has background color");

   }

   int iScan = FreeImage_GetPitch(pfi);

   if (FreeImage_GetBPP(pfi) == 8)
   {

      if (point->m_bLocalPalette && pbi->bmiHeader.biClrUsed > 0)
      {

         colorref_array cra;

         cra_from_quada(cra, pbi->bmiColors, pbi->bmiHeader.biClrUsed);

         if (!draw2d_gif_load_frame(pobject, imageCompose, pimagepointera, point, iFrame, (u8 *)pdata, iScan, cra, transparentIndex))
         {

            return false;

         }

      }
      else
      {


#if defined(ANDROID) && defined(__arm__)
         COLORREF crQuad = ARGB(255, quad.rgbRed, quad.rgbGreen, quad.rgbBlue);
#else
         //COLORREF crQuad = ARGB(255, quad.rgbBlue, quad.rgbGreen, quad.rgbRed);
#endif

         //if (transparentIndex >= pimagepointera->m_cra.get_size() || crQuad != pimagepointera->m_cra[transparentIndex])
         //{

         //   transparentIndex = -1;

         //}



         if (!draw2d_gif_load_frame(pobject, imageCompose, pimagepointera, point, iFrame, (u8 *)pdata, iScan, pimagepointera->m_colorrefa, transparentIndex))
         {

            return false;

         }

      }

   }
   else if (FreeImage_GetBPP(pfi) == 32)
   {

      ::copy_colorref(
      point->m_pimpl->width(),
      point->m_pimpl->height(),
      point->m_pimpl->colorref(),
      point->m_pimpl->scan_size(),
      (COLORREF*) pdata, iScan);
      return true;
   }
   else
   {

      return false;

   }

   return true;

}




void cra_from_quada(colorref_array & cra, RGBQUAD * pquad, int iCount)
{

   cra.set_size(iCount);

   for (index i = 0; i < iCount; i++)
   {

#if defined(ANDROID) && defined(__arm__)
      cra[i] = ARGB(255, pquad[i].rgbRed, pquad[i].rgbGreen, pquad[i].rgbBlue);
#else
      cra[i] = ARGB(255, pquad[i].rgbBlue, pquad[i].rgbGreen, pquad[i].rgbRed);
#endif

      if (cra[i] == ARGB(255, 255, 255, 255))
      {

         output_debug_string("completely white");

      }

   }

}
