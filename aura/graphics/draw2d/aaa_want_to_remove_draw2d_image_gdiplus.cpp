#include "framework.h"
#include <wincodec.h>
#ifdef _UWP
#include <ShCore.h>
#endif


bool node_save_image(IStream * pstream, const ::image * pimage, ::save_image * psaveimage);


#ifdef _UWP


CLASS_DECL_AURA bool node_save_image(::winrt::Windows::Storage::Streams::InMemoryRandomAccessStream ^ randomAccessStream, ::image * pimage, ::save_image * psaveimage);


#endif

bool windows_image_from_bitmap_source(::image * pimage, IWICBitmapSource * piConverter, IWICImagingFactory * piFactory)
{

   comptr < IWICBitmap > piBmp;

   HRESULT hr = piFactory->CreateBitmapFromSource(piConverter, WICBitmapCacheOnLoad, &piBmp);

   if (hr != S_OK)
   {

      return false;

   }

   ::u32 uWidth;

   ::u32 uHeight;

   hr = piBmp->GetSize(&uiWidth, &uiHeight);

   if (hr != S_OK)
   {

      return false;

   }

   WICRect rc;

   rc.X = 0;
   rc.Y = 0;
   rc.Width = uiWidth;
   rc.Height = uiHeight;

   comptr < IWICBitmapLock > piLock;

   hr = piBmp->Lock(&rc, WICBitmapLockRead, &piLock);

   if (hr != S_OK)
   {

      return false;

   }

   ::u32 cbStride;

   piLock->GetStride(&cbStride);

   if (hr != S_OK)
   {

      return false;

   }

   ::u32 uArea;

   byte * pData;

   hr = piLock->GetDataPointer(&uiArea, &pData);

   if (hr != S_OK)
   {

      return false;

   }

   pimage->create(uiWidth, uiHeight);

   if (pimage->area() <= 0)
   {

      return false;

   }

   pimage->map();

   ::copy_colorref(pimage->get_data(), uiWidth, uiHeight, pimage->scan_size(), (color32_t *)pData, cbStride);

   return true;


}


bool imaging::load_image(::object * pobject, ::image * pimage, const ::memory & mem)
{

   {

      defer_co_initialize_ex(false);

      comptr < IWICImagingFactory > piFactory;

      HRESULT hr = piFactory.CoCreateInstance(CLSID_WICImagingFactory1);

      if (FAILED(hr))
      {

         return false;

      }

      comptr < IWICStream > piStream;

      hr = piFactory->CreateStream(&piStream);

      if (FAILED(hr))
      {

         return false;

      }

      hr = piStream->InitializeFromMemory(mem.get_data(), (::u32) mem.get_size());

      if (FAILED(hr))
      {

         return false;

      }

      comptr < IWICBitmapDecoder > piDecoder;

      hr = piFactory->CreateDecoderFromStream(piStream, 0, WICDecodeMetadataCacheOnLoad, &piDecoder); // jpeg,png:OK, bmp:88982f50のエラーになる, iconもエラー

      if (FAILED(hr))
      {

         return false;

      }

      comptr < IWICBitmapFrameDecode > piBitmapFrame;

      hr = piDecoder->GetFrame(0, &piBitmapFrame);

      if (FAILED(hr))
      {

         return false;

      }

      int iOrientation = -1;

      {

         HRESULT hrExif = hr;

         comptr<IWICMetadataQueryReader> pQueryReader;

         if (SUCCEEDED(hrExif))
         {

            hrExif = piBitmapFrame->GetMetadataQueryReader(&pQueryReader);

         }

         if (SUCCEEDED(hrExif))
         {

            PROPVARIANT value;

            PropVariantInit(&value);

            hrExif = pQueryReader->GetMetadataByName(L"/app1/ifd/{ushort=274}", &value);

            if (FAILED(hrExif))
            {

               PropVariantClear(&value); // Clear value for new query.

               PropVariantInit(&value);

               hrExif = pQueryReader->GetMetadataByName(L"/ifd/{ushort=274}", &value);

            }

            if (SUCCEEDED(hrExif))
            {

               iOrientation = value.uiVal;

            }

            PropVariantClear(&value); // Clear value for new query.

         }

      }

      // Convert the image format to 32bppPBGRA
      // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
      // http://d.hatena.ne.jp/sugarontop/20141015
      comptr < IWICFormatConverter > piConverter;

      hr = piFactory->CreateFormatConverter(&piConverter);

      if (FAILED(hr))
      {

         return false;

      }

      hr = piConverter->Initialize(piBitmapFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);

      if (FAILED(hr))
      {

         return false;

      }

      if (!windows_image_from_bitmap_source(pobject, pimage, piConverter, piFactory))
      {

         return false;

      }

      pimage->m_iExifOrientation = iOrientation;

   }

   return true;

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
/*
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


#ifdef _UWP


bool node_save_image(::winrt::Windows::Storage::Streams::InMemoryRandomAccessStream ^ randomAccessStream, const ::image * pimage, ::save_image * psaveimage)
{

   comptr < IStream > pstream;

   ::CreateStreamOverRandomAccessStream(randomAccessStream, IID_PPV_ARGS(&pstream));

   if (!node_save_image(pstream, pimage, psaveimage))
   {

      return false;

   }

   return true;

}


#endif



bool node_save_image(::file::file * pfile, const ::image * pimage, ::save_image * psaveimage)
{

#ifdef _UWP

   ::winrt::Windows::Storage::Streams::InMemoryRandomAccessStream ^ randomAccessStream = ref new ::winrt::Windows::Storage::Streams::InMemoryRandomAccessStream();

   //::wait(randomAccessStream->WriteAsync(get_os_buffer()));

   comptr < IStream > pstream;

   ::CreateStreamOverRandomAccessStream(randomAccessStream, IID_PPV_ARGS(&pstream));

#else

   comptr < IStream > pstream = LIBCALL(shlwapi, SHCreateMemStream)(nullptr, NULL);

#endif

   if (!node_save_image(pstream, pimage, psaveimage))
   {

      return false;

   }

   STATSTG stg;
   __zero(stg);
   pstream->Stat(&stg, STATFLAG_NONAME);
   LARGE_INTEGER l;
   l.QuadPart = 0;
   pstream->Seek(l, STREAM_SEEK_SET, nullptr);


   memory mem(pobject->get_application());

   mem.set_size(1024 * 1024);

   ULONG ulPos = 0;
   ULONG ulRead;
   ULONGLONG ul;
   do
   {

      ulRead = 0;

      ul = stg.cbSize.QuadPart - ulPos;

      pstream->Read(mem.get_data(), (ULONG)minimum(ul, mem.get_size()), &ulRead);

      if (ulRead > 0)
      {

         pfile->write(mem.get_data(), ulRead);

         ulPos += ulRead;

      }

   }
   while (ulRead > 0 && stg.cbSize.QuadPart - ulPos > 0);

   return true;

}


bool node_save_image(IStream * pstream, const ::image * pimage, ::save_image * psaveimage)
{

   comptr < IWICImagingFactory > piFactory = nullptr;
   comptr < IWICBitmapEncoder > piEncoder = nullptr;
   comptr < IWICBitmapFrameEncode > piBitmapFrame = nullptr;
   comptr < IPropertyBag2 > pPropertybag = nullptr;

   comptr < IWICStream > piStream = nullptr;
   ::u32 uWidth = pimage->width();
   ::u32 uHeight = pimage->height();

   HRESULT hr = CoCreateInstance(
                CLSID_WICImagingFactory,
                nullptr,
                CLSCTX_INPROC_SERVER,
                IID_IWICImagingFactory,
                (LPVOID*)&piFactory);

   if (SUCCEEDED(hr))
   {

      hr = piFactory->CreateStream(&piStream);

   }

   if (SUCCEEDED(hr))
   {

      hr = piStream->InitializeFromIStream(pstream);

   }

   if (SUCCEEDED(hr))
   {

      switch (psaveimage->m_eformat)
      {
      case draw2d::format_bmp:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatBmp, nullptr, &piEncoder);
         break;
      case draw2d::format_gif:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatGif, nullptr, &piEncoder);
         break;
      case draw2d::format_jpeg:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatJpeg, nullptr, &piEncoder);
         break;
      case draw2d::format_png:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatPng, nullptr, &piEncoder);
         break;
      default:
         break;
      }

   }

   if (SUCCEEDED(hr))
   {

      hr = piEncoder->Initialize(piStream, WICBitmapEncoderNoCache);

   }

   if (SUCCEEDED(hr))
   {

      hr = piEncoder->CreateNewFrame(&piBitmapFrame, &pPropertybag);

   }

   if (SUCCEEDED(hr))
   {

      //if(m_bJxr)
      //{
      //   //PROPBAG2 option ={0};
      //   //option.pstrName = L"ImageQuality";
      //   //VARIANT varValue;
      //   //VariantInit(&varValue);
      //   //varValue.vt = VT_R4;
      //   //varValue.fltVal = 0.49f;
      //   PROPBAG2 option ={0};
      //   option.pstrName = L"UseCodecOptions";
      //   VARIANT varValue;
      //   VariantInit(&varValue);
      //   varValue.vt = VT_BOOL;
      //   varValue.boolVal = -1;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //   option.pstrName = L"Quality";
      //   VariantInit(&varValue);
      //   varValue.vt = VT_UI1;
      //   varValue.bVal = 184;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //   option.pstrName = L"Subsampling";
      //   VariantInit(&varValue);
      //   varValue.vt = VT_UI1;
      //   varValue.bVal = 1;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //   option.pstrName = L"Overlap";
      //   VariantInit(&varValue);
      //   varValue.vt = VT_UI1;
      //   varValue.bVal = 2;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //   option.pstrName = L"StreamOnly";
      //   VariantInit(&varValue);
      //   varValue.vt = VT_BOOL;
      //   varValue.boolVal = -1;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //}
      if (psaveimage->m_eformat == draw2d::format_jpeg)
      {

         PROPBAG2 option = { 0 };
         option.pstrName = L"ImageQuality";
         VARIANT varValue;
         VariantInit(&varValue);
         varValue.vt = VT_R4;
         varValue.fltVal = maximum(0.f, minimum(1.f, psaveimage->m_iQuality / 100.0f));

         if (SUCCEEDED(hr))
         {

            hr = pPropertybag->Write(1, &option, &varValue);

         }

      }

      if (SUCCEEDED(hr))
      {

         hr = piBitmapFrame->Initialize(pPropertybag);

      }

   }

   if (SUCCEEDED(hr))
   {

      hr = piBitmapFrame->SetSize(uiWidth, uiHeight);

   }

   WICPixelFormatGUID formatGUID = GUID_WICPixelFormat32bppBGRA;

   if (SUCCEEDED(hr))
   {

      hr = piBitmapFrame->SetPixelFormat(&formatGUID);

   }

   pimage->map();

   color32_t * pcr = pimage->get_data();

//   memory m;
//
//#ifdef _UWP
//
//   m.set_size(uiHeight*pimage->scan_size());
//
//   pcr = (color32_t *)m.get_data();
//
//   ::draw2d::vertical_swap_copy_colorref(pimage->width(), pimage->height(), pcr,
//                                         pimage->scan_size(), pimage->get_data(), pimage->scan_size());
//
//#endif

   if (SUCCEEDED(hr))
   {

      if (IsEqualGUID(formatGUID, GUID_WICPixelFormat32bppBGRA))
      {

         if (SUCCEEDED(hr))
         {

            hr = piBitmapFrame->WritePixels(uiHeight, pimage->scan_size(), uiHeight*pimage->scan_size(), (byte *)pcr);

         }

      }
      else
      {

         comptr <IWICBitmap> pbitmap;

         if (SUCCEEDED(hr))
         {

            hr = piFactory->CreateBitmapFromMemory(
                 pimage->width(),
                 pimage->height(),
                 GUID_WICPixelFormat32bppBGRA,
                 pimage->scan_size(),
                 pimage->scan_size() * pimage->height(),
                 (byte *)pcr,
                 &pbitmap
                 );

         }

         comptr<IWICFormatConverter> pconverter;

         if (SUCCEEDED(hr))
         {

            hr = piFactory->CreateFormatConverter(&pconverter);

         }

         if (SUCCEEDED(hr))
         {

            hr = pconverter->Initialize(pbitmap, formatGUID, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);

         }

         if (SUCCEEDED(hr))
         {

            hr = piBitmapFrame->WriteSource(pconverter, nullptr);

         }

      }

   }

   if (SUCCEEDED(hr))
   {

      hr = piBitmapFrame->Commit();

   }

   if (SUCCEEDED(hr))
   {

      hr = piEncoder->Commit();

   }

   return true;

}



