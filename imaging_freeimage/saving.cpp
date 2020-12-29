#include "framework.h"


namespace imaging_freeimage
{


   FIBITMAP * freeimage_from_image(const ::image * pimage)
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
      i32 nColors = FreeImage_GetColorsUsed(fi);
      //HDC hdc = ::CreateCompatibleDC(nullptr);

      int iWidth;
      int iHeight;
      color32_t * pcolorref;
      int iStrideDst;

      iWidth = FreeImage_GetWidth(fi);

      iHeight = FreeImage_GetHeight(fi);

      pcolorref = (color32_t *)FreeImage_GetBits(fi);

      if (FreeImage_GetInfo(fi)->bmiHeader.biSizeImage <= 0)
      {

         iStrideDst = iWidth * sizeof(color32_t);

      }
      else
      {

         iStrideDst = FreeImage_GetInfo(fi)->bmiHeader.biSizeImage / iHeight;

      }

      color32_t * pdst = pcolorref;

      const color32_t * psrc = pimage->colorref();

#if  defined(ANDROID)

      int iStrideSrc = pimage->scan_size();

      for (index y = 0; y < pimage->height(); y++)
      {

         u8 * pbDst = ((u8 *)pdst) + ((pimage->height() - y - 1) * iStrideDst);

         u8 * pbSrc = (u8 *)psrc + (y * iStrideSrc);

         for (index x = 0; x < pimage->width(); x++)
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

      u8 * pbDst = (u8 *)pdst;

      u8 * pbSrc = (u8 *)psrc;

      ::count c = (count)pimage->area();

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

      u8 * pbDst;

      u8 * pbSrc;

      for(int i = 0; i < pimage->height(); i++)
      {

      pbDst = &((u8 *) pimage->get_data())[pimage->scan_size() * (pimage->height() - i - 1)];

      pbSrc = &((u8 *) pdata)[pbi->bmiHeader.biWidth * sizeof(color32_t) * i];

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

         ::memcpy_dup(
            &((u8 *)pdst)[iStrideDst * (pimage->height() - i - 1)],
            &((u8 *)psrc)[iStrideSrc * i],
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


   ::e_status context_image::save_image(memory & memory, const ::image * pimage, const ::save_image * psaveimage)
   {

      if (::is_null(pimage))
      {

         return false;

      }

      ::save_image saveimageDefault;

      if (psaveimage == nullptr)
      {

         psaveimage = &saveimageDefault;

      }

      bool bOk = false;

      bool b8 = false;

      bool b24 = false;

      int iFreeImageSave = 0;

      FREE_IMAGE_FORMAT eformat = (FREE_IMAGE_FORMAT)0;

      string strFile;

      switch (psaveimage->m_eformat)
      {
      case ::draw2d::format_png:
         eformat = FreeImage_GetFIFFromFormat("PNG");
         strFile = "foo.png";
         break;
      case ::draw2d::format_bmp:
         eformat = FIF_BMP;
         strFile = "foo.bmp";
         break;
      case ::draw2d::format_gif:
         b8 = true;
         eformat = FIF_GIF;
         strFile = "foo.gif";
         break;
      case ::draw2d::format_jpeg:
         b24 = true;
         eformat = FreeImage_GetFIFFromFormat("JPEG");
         strFile = "foo.jpg";
         if (psaveimage->m_iQuality > 80)
         {
            iFreeImageSave |= JPEG_QUALITYSUPERB;
         }
         else if (psaveimage->m_iQuality > 67)
         {
            iFreeImageSave |= JPEG_QUALITYGOOD;
         }
         else if (psaveimage->m_iQuality > 33)
         {
            iFreeImageSave |= JPEG_QUALITYNORMAL;
         }
         else if (psaveimage->m_iQuality > 15)
         {
            iFreeImageSave |= JPEG_QUALITYAVERAGE;
         }
         else
         {
            iFreeImageSave |= JPEG_QUALITYBAD;
         }
         break;
      default:
         return false;
      }

      eformat = FreeImage_GetFIFFromFilename(strFile);


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

      bOk = FreeImage_SaveToMemory(eformat, pfi8, pfm1, iFreeImageSave) != FALSE;

      byte * pbData = nullptr;
      DWORD dwSize = 0;
      if (bOk)
         bOk = FreeImage_AcquireMemory(pfm1, &pbData, &dwSize) != FALSE;
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



      return bOk != FALSE;

      //#endif

   }


} // namespace imaging_freeimage



