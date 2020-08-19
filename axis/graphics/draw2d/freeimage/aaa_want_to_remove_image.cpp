#include "framework.h"

#include <stdio.h>

#ifdef LINUX

#include <FreeImage.h>

#else

#include "FreeImage/FreeImage.h"

#endif


FIBITMAP * freeimage_from_image(::image * pimage)
{

   if (::is_null(pimpl))
   {

      return nullptr;

   }

   if (pimpl->area() <= 0)
   {

      return nullptr;

   }

   pimpl->map();

   FIBITMAP * fi;

   //   if(bm.bmBitsPixel == 32)
   {
      fi = FreeImage_AllocateT(FIT_BITMAP, pimpl->width(), pimpl->height(), 32);
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
   COLORREF * pcolorref;
   int iStrideDst;

   iWidth = FreeImage_GetWidth(fi);

   iHeight = FreeImage_GetHeight(fi);

   pcolorref = (COLORREF *)FreeImage_GetBits(fi);

   if (FreeImage_GetInfo(fi)->bmiHeader.biSizeImage <= 0)
   {

      iStrideDst = iWidth * sizeof(COLORREF);

   }
   else
   {

      iStrideDst = FreeImage_GetInfo(fi)->bmiHeader.biSizeImage / iHeight;

   }

   COLORREF * pdst = pcolorref;

   COLORREF * psrc = pimpl->colorref();

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

   pbSrc = &((u8 *) pdata)[pbi->bmiHeader.biWidth * sizeof(COLORREF) * i];

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

   int iStrideSrc = pimpl->scan_size();

   for (int i = 0; i < pimpl->height(); i++)
   {

      ::memcpy_dup(
      &((u8 *)pdst)[iStrideDst * (pimpl->height() - i - 1)],
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


bool image_from_freeimage(::image * pimage, FIBITMAP *pfibitmap)
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

   if (!pimpl->create(w, h))
   {

      return false;

   }

   void * pdata = FreeImage_GetBits(image32);

   int iSrcScan = FreeImage_GetPitch(image32);

   int iLineSize = w * sizeof(COLORREF);

   pimpl->map();

#if defined(ANDROID)

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

   for (int i = 0; i < pimpl->height(); i++)
   {

      ::memcpy_dup(
      &((u8 *)pimpl->get_data())[pimpl->scan_size() * (h - i - 1)],
      &((u8 *)pdata)[iSrcScan * i],
      iLineSize);

   }

#endif

   pimpl->mult_alpha_fast();

   FreeImage_Unload(image32);

   return true;

}


//#include "visual_FreeImageFileProc.h"

/*u32 ___ReadProc    (void *buffer, u32 size, u32 count, fi_handle handle)
{
   u32 dwRead;
   if(ReadFile(handle, buffer, count * size, &dwRead, nullptr))
   {
      return count;
   }
   else
   {
      return --count;
   }

}
u32 ___WriteProc   (void *buffer, u32 size, u32 count, fi_handle handle)
{
   u32 dwWritten;
   if(WriteFile(handle, buffer, count * size, &dwWritten, nullptr))
   {
      return count;
   }
   else
   {
      return --count;
   }
}
i32      ___SeekProc    (fi_handle handle, long offset, i32 origin)
{
   if(origin == SEEK_SET)
      origin = FILE_BEGIN;
   else if(origin == SEEK_CUR)
      origin = FILE_CURRENT;
   else if(origin == SEEK_END)
      origin = FILE_END;
   if(SetFilePointer(handle, offset, nullptr, origin) == 0xFFFFFFFF)
      return -1;
   else
      return 0;
}
long     ___TellProc    (fi_handle handle)
{
   return SetFilePointer(handle, 0, nullptr, SEEK_CUR);
}

u32 __ReadProc (void *buffer, u32 size, u32 count, fi_handle handle)
{
   u32 dwRead;
   if(ReadFile(handle, buffer, count * size, &dwRead, nullptr))
   {
      return count;
   }
   else
   {
      return --count;
   }

}
u32 __WriteProc (void *buffer, u32 size, u32 count, fi_handle handle)
{
   u32 dwWritten;
   if(WriteFile(handle, buffer, count * size, &dwWritten, nullptr))
   {
      return count;
   }
   else
   {
      return --count;
   }
}
i32 __SeekProc (fi_handle handle, long offset, i32 origin)
{
   if(origin == SEEK_SET)
      origin = FILE_BEGIN;
   else if(origin == SEEK_CUR)
      origin = FILE_CURRENT;
   else if(origin == SEEK_END)
      origin = FILE_END;
   if(SetFilePointer(handle, offset, nullptr, origin) == 0xFFFFFFFF)
      return -1;
   else
      return 0;
}
long __TellProc (fi_handle handle)
{
   return SetFilePointer(handle, 0, nullptr, SEEK_CUR);
}*/

//#ifndef WINDOWS
//
//#define DLL_CALLCONV
//
//#endif


unsigned DLL_CALLCONV  __ReadProc2 (void *buffer, unsigned size, unsigned count, fi_handle handle)
{

   memsize dwRead;

   ::file::file *  pfile = (::file::file * ) handle;

   DWORD dwTotal = count * size;

   dwRead = pfile->read(buffer, dwTotal);

   if(dwRead == dwTotal)
   {

      return count;

   }
   else
   {

      return dwRead / size;

   }

}


unsigned DLL_CALLCONV __WriteProc2(void *buffer, unsigned size, unsigned count, fi_handle handle)
{

   ::file::file *  pfile = (::file::file * ) handle;

   try
   {

      pfile->write(buffer, count * size);

   }
   catch(...)
   {

      return 0;

   }

   return count;

}


int DLL_CALLCONV __SeekProc2(fi_handle handle, long offset, int origin)
{

   ::file::file *  pfile = (::file::file * ) handle;

   if (origin == SEEK_SET)
   {

      origin = ::file::seek_begin;

   }
   else if (origin == SEEK_CUR)
   {

      origin = ::file::seek_current;

   }
   else if (origin == SEEK_END)
   {

      origin = ::file::seek_end;

   }

   try
   {

      pfile->seek(offset, (::file::e_seek) origin);

   }
   catch(...)
   {

      return -1;

   }

   return 0;

}


long DLL_CALLCONV __TellProc2(fi_handle handle)
{

   ::file::file *  pfile = (::file::file * ) handle;

   return (long) pfile->get_position();

}



//static u32 _stdcall  __ReadProc3 (void *buffer, u32 size, u32 count, fi_handle handle);
//static u32 _stdcall __WriteProc3 (void *buffer, u32 size, u32 count, fi_handle handle);
//static i32 _stdcall __SeekProc3 (fi_handle handle, long offset, i32 origin);
//static long _stdcall __TellProc3 (fi_handle handle);


u32 _stdcall  ___Ex1File__ReadProc (void *buffer, u32 size, u32 count, fi_handle handle)
{

   memsize dwRead;

   file_pointer  pfile = (::file::file * ) handle;

   if((dwRead = pfile->read(buffer, count * size)))
   {

      return count;

   }
   else
   {

      return --count;

   }

}


u32 _stdcall ___Ex1File__WriteProc(void *buffer, u32 size, u32 count, fi_handle handle)
{

   file_pointer  pfile = (::file::file * ) handle;

   try
   {

      pfile->write(buffer, count * size);

   }
   catch(...)
   {

      return --count;

   }

   return count;

}


i32 _stdcall ___Ex1File__SeekProc(fi_handle handle, long offset, i32 origin)
{

   file_pointer  pfile = (::file::file * ) handle;

   if (origin == SEEK_SET)
   {

      origin = ::file::seek_begin;

   }
   else if (origin == SEEK_CUR)
   {

      origin = ::file::seek_current;

   }
   else if (origin == SEEK_END)
   {

      origin = ::file::seek_end;

   }

   if (pfile->seek(offset, (::file::e_seek) origin) == 0xFFFFFFFF)
   {

      return -1;

   }
   else
   {

      return 0;

   }

}


long _stdcall ___Ex1File__TellProc(fi_handle handle)
{

   file_pointer  pfile = (::file::file * ) handle;

   return (long) pfile->get_position();

}



namespace draw2d
{


   void free_FreeImage(FIBITMAP * pfibitmap)
   {

#ifdef _UWP

      __throw(todo());

#else
      FreeImage_Unload(pfibitmap);
#endif
   }


}


bool imaging::save_image(::object * pobject, memory & memory, ::image * pimage, ::save_image * psaveimage)
{

   if(::is_null(pimpl))
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
   FIBITMAP * pfi7 = freeimage_from_image(pimpl);
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

   BYTE * pbData = nullptr;
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
::exception::throw_not_implemented();

::memory_file file(get_object());

::aura::Resource resource;

if(!resource.ReadResource(*file.get_memory(), (UINT) MAKEINTRESOURCE(pszId), pszType))

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





//bool imaging::load_image(::image * pimage, var varFile, ::aura::application * papp)
//{
//
//   ::memory_file memfile(get_object());
//
//   Context.file().as_memory(varFile, *memfile.get_memory(), papp);
//
//   if (memfile.get_size() <= 0)
//      return false;
//
//   return load_image(pimage, &memfile);
//
//}


//bool imaging::save_png(const char * pcszFile, draw2d::image_pointer & image)

//{
//
//   auto * fi = freeimage_from_image(&image);
//
//   if (fi == nullptr)
//   {
//
//      return false;
//
//   }
//
//   bool bOk = false;
//
//   if (FreeImage_Save(FreeImage_GetFIFFromFormat("PNG"), fi, pcszFile, 0))

//   {
//
//      bOk = true;
//
//   }
//
//   FreeImage_Unload(fi);
//
//   return bOk;
//
//}
//
//
//::draw2d::bitmap_pointer freeimage_to_hbitmap(FIBITMAP * pfibitmap, ::aura::application * papp)
//{
//
//   if (pfibitmap == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   ::image_pointer pimage(papp->create_new, this);
//
//   if (!image_from_freeimage(pimage, pfibitmap))
//   {
//
//      return nullptr;
//
//   }
//
//   return pimage->detach_bitmap();
//
//}


//::draw2d::bitmap_pointer di_bitmap_from_freeimage(::draw2d::graphics_pointer & pgraphics, FIBITMAP * pFreeImage)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   ::draw2d::bitmap_pointer bitmap(pgraphics->get_context_application());
//
//   if (!bitmap->CreateDIBitmap(pgraphics, FreeImage_GetInfoHeader(pFreeImage), CBM_INIT, FreeImage_GetBits(pFreeImage), FreeImage_GetInfo(pFreeImage), DIB_RGB_COLORS))
//   {
//
//      TRACELASTERROR();
//
//      return nullptr;
//
//   }
//
//   return bitmap;
//
//#else
//
//   __throw(todo(pgraphics->get_context_application()));
//
//#endif
//
//   return nullptr;
//
//}


//::draw2d::bitmap_pointer bitmap_from_freeimage(::draw2d::graphics_pointer & pgraphics, FIBITMAP * pfibitmap)
//{
//
//   ::image_pointer pimage(pgraphics->create_new, this);
//
//   image_from_freeimage(pimage, pfibitmap);
//
//   return pimage->detach_bitmap();
//
//}


bool imaging::load_image(::object * pobject, ::image * pimage, const memory & memory)
{

   if (::is_null(pimpl))
   {

      return false;

   }

   if(memory.is_empty())
   {

      return false;

   }


   FIMEMORY * pmem= FreeImage_OpenMemory(memory.get_data(), memory.get_size());

   if(pmem == nullptr)
   {

   return false;

   }


//   FreeImageIO io;
//
//   io.read_proc = __ReadProc2;
//
//   io.seek_proc = __SeekProc2;
//
//   io.tell_proc = __TellProc2;
//
//   io.write_proc = __WriteProc2;

   FIBITMAP * pfibitmap = nullptr;

   try
   {


      FREE_IMAGE_FORMAT format;

      format =  FreeImage_GetFileTypeFromMemory(pmem);

      pfibitmap = FreeImage_LoadFromMemory(format, pmem);

   }
   catch (...)
   {

   }

   if (pfibitmap == nullptr)
   {

      FreeImage_CloseMemory(pmem);

      return false;

   }

   int iExifOrientation = -1;

   bool bOrientation = false;

   FITAG *tag = nullptr;

   FIMETADATA *mdhandle = FreeImage_FindFirstMetadata(FIMD_EXIF_MAIN, pfibitmap, &tag);

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

               iExifOrientation = *((unsigned short*)value);

               pimpl->prop("exif_orientation") = iExifOrientation;

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

   if(!image_from_freeimage(pimpl, pfibitmap))
   {

      FreeImage_Unload(pfibitmap);

      FreeImage_CloseMemory(pmem);

      return false;

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


   return true;


}





// bool os_init_imaging()
// {

//    FreeImage_Initialise(FALSE);

//    return true;
// }


// void os_term_imaging()
// {

//    FreeImage_DeInitialise();


// }

