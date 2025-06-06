#include "framework.h"
#include "image_context.h"
////#include "acme/exception/exception.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/encoding_options.h"


#include <FreeImage.h>


namespace imaging_freeimage
{


   FIBITMAP * freeimage_from_image(const ::image::image *pimage)
   {

      if (::is_null(pimage))
      {

         return nullptr;

      }

      if (pimage->area() <= 0)
      {

         return nullptr;

      }

      pimage->map();

      FIBITMAP * fi;

      //   if(bm.bmBitsPixel == 32)
      {
         fi = FreeImage_AllocateT(FIT_BITMAP, pimage->width(), pimage->height(), 32);
      }
      // else
      {
         //  fi = FreeImage_Allocate(bm.bmWidth,bm.bmHeight,bm.bmBitsPixel);
      }
      // The GetDIBits function clears the biClrUsed and biClrImportant BITMAPINFO members (dont't know why)
      // So we save these infos below. This is needed for palettized images only.
      int nColors = FreeImage_GetColorsUsed(fi);
      //HDC hdc = ::CreateCompatibleDC(nullptr);

      int iWidth;
      int iHeight;
      color32_t * pimage32;
      int iStrideDst;

      iWidth = FreeImage_GetWidth(fi);

      iHeight = FreeImage_GetHeight(fi);

      pimage32 = (color32_t *)FreeImage_GetBits(fi);

      if (FreeImage_GetInfo(fi)->bmiHeader.biSizeImage <= 0)
      {

         iStrideDst = iWidth * sizeof(color32_t);

      }
      else
      {

         iStrideDst = FreeImage_GetInfo(fi)->bmiHeader.biSizeImage / iHeight;

      }

      color32_t * pdst = pimage32;

      auto psrc = pimage->image32();

#if  defined(__ANDROID__)

      int iStrideSrc = pimage->scan_size();

      for (::collection::index y = 0; y < pimage->height(); y++)
      {

         unsigned char * pbDst = ((unsigned char *)pdst) + ((pimage->height() - y - 1) * iStrideDst);

         unsigned char * pbSrc = (unsigned char *)psrc + (y * iStrideSrc);

         for (::collection::index x = 0; x < pimage->width(); x++)
         {

            pbDst[0] = pbSrc[2];

            pbDst[1] = pbSrc[1];

            pbDst[2] = pbSrc[0];

            pbDst[3] = pbSrc[3];

            pbDst += 4;

            pbSrc += 4;

         }

      }

#elif defined(APPLEOS)

      unsigned char * pbDst = (unsigned char *)pdst;

      unsigned char * pbSrc = (unsigned char *)psrc;

      ::collection::count c = (count)pimage->area();

      while (c-- > 0)
      {

         pbDst[0] = pbSrc[2];

         pbDst[1] = pbSrc[1];

         pbDst[2] = pbSrc[0];

         pbDst[3] = pbSrc[3];

         pbDst += 4;

         pbSrc += 4;

      }

      /*

      unsigned char * pbDst;

      unsigned char * pbSrc;

      for(int i = 0; i < pimage->height(); i++)
      {

      pbDst = &((unsigned char *) pimage->get_data())[pimage->scan_size() * (pimage->height() - i - 1)];

      pbSrc = &((unsigned char *) pdata)[pbi->bmiHeader.biWidth * sizeof(color32_t) * i];

      for(int j = 0; j < pimage->width(); j++)
      {

      pbDst[0] = pbSrc[2];

      pbDst[1] = pbSrc[1];

      pbDst[2] = pbSrc[0];

      pbDst[3] = pbSrc[3];

      pbDst += 4;

      pbSrc += 4;

      }

      }*/

#else

      int iStrideSrc = pimage->scan_size();

      for (int i = 0; i < pimage->height(); i++)
      {

         ::memory_copy(
            &((unsigned char *)pdst)[iStrideDst * (pimage->height() - i - 1)],
            &((unsigned char *)psrc)[iStrideSrc * i],
            iStrideDst);

      }
#endif

      //GetDIBits(hdc,(HBITMAP)hbitmap,0,FreeImage_GetHeight(fi),FreeImage_GetBits(fi),FreeImage_GetInfo(fi),DIB_RGB_COLORS);

      //::DeleteDC(hdc);

      //pbitmap->ReleaseHBITMAP(hbitmap);

      // restore BITMAPINFO members
      FreeImage_GetInfoHeader(fi)->biClrUsed = nColors;
      FreeImage_GetInfoHeader(fi)->biClrImportant = nColors;
      return fi;


   }


   void image_context::save_image(memory & memory, ::image::image *pimage, const ::image::encoding_options & encodingoptions)
   {

      if (::is_null(pimage))
      {

         throw ::exception(error_invalid_empty_argument);

      }

      auto eformat = encodingoptions.m_eformat;

      if (eformat == ::image::e_format_none)
      {

         eformat = ::image::e_format_png;

      }

      bool bOk = false;

      bool b8 = false;

      bool b24 = false;

      int iFreeImageSave = 0;

      FREE_IMAGE_FORMAT efreeimageformat = (FREE_IMAGE_FORMAT)0;

      string strFile;

      switch (eformat)
      {
      case ::image::e_format_png:
         efreeimageformat = FreeImage_GetFIFFromFormat("PNG");
         strFile = "foo.png";
         break;
      case ::image::e_format_bmp:
         efreeimageformat = FIF_BMP;
         strFile = "foo.bmp";
         break;
      case ::image::e_format_gif:
         b8 = true;
         efreeimageformat = FIF_GIF;
         strFile = "foo.gif";
         break;
      case ::image::e_format_jpeg:
         b24 = true;
         efreeimageformat = FreeImage_GetFIFFromFormat("JPEG");
         strFile = "foo.jpg";
         if (encodingoptions.m_iQuality > 80)
         {
            iFreeImageSave |= JPEG_QUALITYSUPERB;
         }
         else if (encodingoptions.m_iQuality > 67)
         {
            iFreeImageSave |= JPEG_QUALITYGOOD;
         }
         else if (encodingoptions.m_iQuality > 33)
         {
            iFreeImageSave |= JPEG_QUALITYNORMAL;
         }
         else if (encodingoptions.m_iQuality > 15)
         {
            iFreeImageSave |= JPEG_QUALITYAVERAGE;
         }
         else
         {
            iFreeImageSave |= JPEG_QUALITYBAD;
         }
         break;
      default:
         throw ::exception(error_bad_argument);
      }

      efreeimageformat = FreeImage_GetFIFFromFilename(strFile);


      FIMEMORY * pfm1 = FreeImage_OpenMemory();
      FIBITMAP * pfi7 = freeimage_from_image(pimage);
      FIBITMAP * pfi8 = nullptr;
      bool bConv;
      if (b8)
      {
         pfi8 = FreeImage_ConvertTo8Bits(pfi7);
         bConv = true;
      }
      else if (b24)
      {
         pfi8 = FreeImage_ConvertTo24Bits(pfi7);
         bConv = true;
      }
      else
      {
         //FreeImage_SetTransparent(pfi8,true);
         pfi8 = pfi7;
         bConv = false;
      }

      bOk = FreeImage_SaveToMemory(efreeimageformat, pfi8, pfm1, iFreeImageSave) != false;

      unsigned char * pbData = nullptr;
      DWORD dwSize = 0;
      if (bOk)
         bOk = FreeImage_AcquireMemory(pfm1, &pbData, &dwSize) != false;
      if (bOk)
      {
         try
         {

            memory.assign(pbData, dwSize);
         }
         catch (...)
         {
            bOk = false;
         }
      }

      FreeImage_CloseMemory(pfm1);
      if (bConv)
      {
         FreeImage_Unload(pfi8);
      }
      FreeImage_Unload(pfi7);



      //return bOk != false;

      //#endif

   }


} // namespace imaging_freeimage



