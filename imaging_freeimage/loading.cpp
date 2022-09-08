#include "framework.h"
//#include "_imaging_freeimage.h"
#include "acme/filesystem/filesystem/acme_file.h"


CLASS_DECL_APEX void set_bypass_cache_if_empty(::payload & payloadFile);


namespace imaging_freeimage
{


   bool image_from_freeimage(::image * pimage, FIBITMAP * pfibitmap)
   {

      if (pfibitmap == nullptr)
      {

         return false;

      }

      FIBITMAP * image32 = FreeImage_ConvertTo32Bits(pfibitmap);

      if (image32 == nullptr)
      {

         return false;

      }

      int w = FreeImage_GetWidth(image32);

      int h = FreeImage_GetHeight(image32);

      pimage->create({ w, h });

      ////if (!pimage->create({ w, h}))
      //{

      //   return false;

      //}

      void * pdata = FreeImage_GetBits(image32);

      int iSrcScan = FreeImage_GetPitch(image32);

      int iLineSize = w * sizeof(color32_t);

      pimage->map();

#if defined(ANDROID) && defined(ARM)

      for (index y = 0; y < pimage->height(); y++)
      {

         u8 * pbDst = ((u8 *)pimage->get_data()) + ((pimage->height() - y - 1) * pimage->scan_size());

         u8 * pbSrc = (u8 *)pdata + (y * iSrcScan);

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

      u8 * pbDst = (u8 *)pimage->get_data();

      u8 * pbSrc = (u8 *)pdata;

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


#else

      for (int i = 0; i < pimage->height(); i++)
      {

         ::memcpy_dup(
            &((u8 *)pimage->get_data())[pimage->scan_size() * (h - i - 1)],
            &((u8 *)pdata)[iSrcScan * i],
            iLineSize);

      }

#endif

      pimage->mult_alpha_fast();

      FreeImage_Unload(image32);

      return true;

   }





   namespace draw2d
   {


      void free_FreeImage(FIBITMAP * pfibitmap)
      {

#ifdef _UWP

         throw ::exception(todo);

#else
         FreeImage_Unload(pfibitmap);
#endif
      }


   }



   /*FIBITMAP * imaging::LoadImageFile(CArchive & ar)
   {
   ASSERT(!ar.IsStoring());

   return LoadImageFile(ar.GetFile());

   }
   */
   /*HBITMAP imaging::LoadBitmap(
   const char * pszType,

   const char * pszId)

   {
   throw ::interface_only();

   ::memory_file file(this);

   ::aura::Resource resource;

   if(!resource.ReadResource(*file.get_memory(), (::u32) MAKEINTRESOURCE(pszId), pszType))

   return false;

   file.seek_to_begin();

   file_pointer  pfile = &file;

   FreeImageIO io;
   io.read_proc   = ___Ex1File__ReadProc;
   io.seek_proc   = ___Ex1File__SeekProc;
   io.tell_proc   = ___Ex1File__TellProc;
   io.write_proc  = ___Ex1File__WriteProc;

   FREE_IMAGE_FORMAT format;
   format = FreeImage_GetFileTypeFromHandle(&io, pfile ,16);
   FIBITMAP *pfi = nullptr;
   if(true)
   {
   pfi = FreeImage_LoadFromHandle(format, &io, pfile);
   }

   if(pfi == nullptr)
   return nullptr;

   BITMAPINFO * pbi = FreeImage_GetInfo(pfi);
   void * pData = FreeImage_GetBits(pfi);


   HDC hdcSource = CreateDC(
   "DISPLAY",
   nullptr,
   nullptr,
   nullptr);

   HBITMAP hBitmapSource = ::CreateCompatibleBitmap(
   hdcSource,
   pbi->bmiHeader.biWidth,
   pbi->bmiHeader.biHeight);

   if(pbi->bmiHeader.biHeight != SetDIBits(
   hdcSource,
   hBitmapSource,
   0,
   pbi->bmiHeader.biHeight,
   pData,
   pbi,
   DIB_RGB_COLORS))
   {
   FreeImage_Unload(pfi);
   DeleteDC(hdcSource);
   delete_object(hBitmapSource);
   return nullptr;
   }

   FreeImage_Unload(pfi);
   DeleteDC(hdcSource);

   return hBitmapSource;
   */
   //}
   //*/


   //#endif // WINDOWS_DESKTOP


   void context_image::_load_image(::image * pimage, const ::payload & varFileParam, const ::image::load_options & loadoptions)
   {

      memory memory;

      ::payload payloadFile;

      payloadFile = varFileParam;

      {

         auto tmp = payloadFile.get_file_path();

         if (tmp.ends_ci(".gif"))
         {

            output_debug_string("GIF!!");

         }

      }

      set_bypass_cache_if_empty(payloadFile);

      ::file::path path = payloadFile.get_file_path();

      ::file::path pathProcess = m_pcontext->m_papexcontext->defer_process_path(path);

      auto bOk = m_pcontext->m_papexcontext->file().as_memory(payloadFile, memory);

      auto p1 = memory.get_data();

      auto s1 = memory.get_size();

      if(!bOk)
      {

         return;

      }


      //m_pcontext->m_papexcontext->file().non_empty_memory(payloadFile, *pmemory);

      const char * psz = (const char *)memory.get_data();

      if (::is_null(psz))
      {

         //return pimage->m_estatus;

         return;

      }

      if (::is_null(pimage))
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      if (memory.is_empty())
      {

         //return false;

         throw ::exception(error_failed);

      }

      auto pcontext = m_pcontext->m_pauracontext;

      auto pcontextimage = pcontext->context_image();

      auto pszData = memory.get_data();

      auto size = memory.get_size();

      char  pszPngSignature []= {(char)137, 80, 78 ,71, 13 ,10, 26 ,10};

      bool bPng = size > sizeof(pszPngSignature)
      && strncmp((const char *) pszData, pszPngSignature, sizeof(pszPngSignature)) == 0;

      bool bJpegBegins = memory.begins("\x0FF\x0D8", 2);

      bool bJpegEnds = memory.ends("\x0FF\x0D9", 2);

      bool bGif87a = memory.begins("GIF87a", 6);

      bool bGif89a = memory.begins("GIF89a", 6);

      bool bJpeg =  bJpegBegins && bJpegEnds;

      bool bJfif = memory.begins("JFIF", 4);

      bool bExif = memory.begins("Exif", 4);

      bool bGif = bGif87a || bGif89a;

      bool bBinary = *pszData == '\0';

      if(!bPng
      && !bBinary
      && !bJpeg
      && !bJfif
      && !bExif
      && !bGif
      )
      {

         //estatus = 
         
         pcontextimage->load_svg(pimage, memory);

         if (::is_ok(pimage))
         {

            return;

         }

      }
   else if (bGif)
      {

      //m_psystem->m_pacmefile->put_contents("/home/camilo/a.gif", memory);

         _load_multi_frame_image(pimage, memory);

         //if (!)
 /*        {

            pimage->set_nok();

            return pimage->m_estatus;

         }*/

         pimage->on_load_image();

         pimage->set_ok();

         pimage->m_estatus = ::success;

         return;

         // return pimage->m_estatus;

      }

      FIMEMORY * pmem = FreeImage_OpenMemory(memory.get_data(), (::u32) memory.get_size());

      if (pmem == nullptr)
      {

         throw ::exception(error_failed);

      }

      FIBITMAP * pfibitmap = nullptr;

      try
      {


         FREE_IMAGE_FORMAT format;

         format = FreeImage_GetFileTypeFromMemory(pmem);

         pfibitmap = FreeImage_LoadFromMemory(format, pmem);

      }
      catch (...)
      {

      }

      if (pfibitmap == nullptr)
      {

         FreeImage_CloseMemory(pmem);

         pimage->m_estatus = error_failed;

         pimage->set_nok();

         return;

      }

      int iExifOrientation = -1;

      bool bOrientation = false;

      FITAG * tag = nullptr;

      FIMETADATA * mdhandle = FreeImage_FindFirstMetadata(FIMD_EXIF_MAIN, pfibitmap, &tag);

      if (mdhandle)
      {

         do
         {

            if (!_stricmp(FreeImage_GetTagKey(tag), "orientation"))
            {

               bOrientation = true;

               auto type = FreeImage_GetTagType(tag);

               if (type == FIDT_SHORT)
               {

                  auto value = FreeImage_GetTagValue(tag);

                  iExifOrientation = *((unsigned short *)value);

                  pimage->m_iExifOrientation = iExifOrientation;

               }

            }

            if (bOrientation)
            {

               break;

            }

         }

         while (FreeImage_FindNextMetadata(mdhandle, &tag));

         FreeImage_FindCloseMetadata(mdhandle);

      }

      if (!image_from_freeimage(pimage, pfibitmap))
      {

         FreeImage_Unload(pfibitmap);

         FreeImage_CloseMemory(pmem);

         throw ::exception(error_failed);

      }

      FreeImage_Unload(pfibitmap);

      FreeImage_CloseMemory(pmem);


      //   if (iExifOrientation >= 0)
      //   {
      //
      //      ::image_pointer pimage2;
      //
      //      //double dPiQuarter = ::atan(1.0);
      //
      //      //double dPi = dPiQuarter * 4.0;
      //
      //      // http://sylvana.net/jpegcrop/exif_orientation.html
      //      //1) transform = "";;
      //      //2) transform = "-flip horizontal";;
      //      //3) transform = "-rotate 180";;
      //      //4) transform = "-flip vertical";;
      //      //5) transform = "-transpose";;
      //      //6) transform = "-rotate 90";;
      //      //7) transform = "-transverse";;
      //      //8) transform = "-rotate 270";;
      //      //*) transform = "";;
      //      switch (iExifOrientation)
      //      {
      //      case 2:
      //         pimage2->flip_horizontal(pimage);
      //         pimage->from(pimage2);
      //         break;
      //      case 3:
      //         pimage2->rotate(pimage, 180.0);
      //         pimage->from(pimage2);
      //         break;
      //      case 4:
      //         pimage2->flip_vertical(pimage);
      //         pimage->from(pimage2);
      //         break;
      //      case 5:
      //         pimage2->flip_horizontal(pimage);
      //         pimage->rotate(pimage2, -270.0);
      //         break;
      //      case 6:
      //         pimage2->rotate(pimage, -90.0);
      //         pimage->from(pimage2);
      //         break;
      //      case 7:
      //         pimage2->flip_horizontal(pimage);
      //         pimage->rotate(pimage2, -90.0);
      //         break;
      //      case 8:
      //         pimage2->rotate(pimage, -270.0);
      //         pimage->from(pimage2);
      //         break;
      //      case 1:
      //      default:
      //         break;
      //
      //      }
      //
      //   }

      pimage->on_load_image();

      pimage->set_ok();

      pimage->m_estatus = ::success;

      if(loadoptions.functionLoaded)
      {

         loadoptions.functionLoaded(pimage);

      }
//      return pimage->m_estatus;

   }


} // namespace imaging_freeimage





   //bool os_init_imaging()
   //{

   //   FreeImage_Initialise(false);

   //   return true;
   //}


   //void os_term_imaging()
   //{

   //   FreeImage_DeInitialise();


   //}
