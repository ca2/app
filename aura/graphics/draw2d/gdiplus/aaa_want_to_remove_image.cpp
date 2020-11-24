#include "framework.h"
#include <wincodec.h>
#ifdef _UWP
#include <ShCore.h>
#endif


bool node_save_image(IStream * pstream, const ::image * pimage, ::save_image * psaveimage);


#ifdef _UWP


CLASS_DECL_AURA bool node_save_image(::Windows::Storage::Streams::InMemoryRandomAccessStream ^ randomAccessStream, const ::image * pimage, ::save_image * psaveimage);


#endif

bool windows_image_from_bitmap_source(::image * pimageFrame, IWICBitmapSource * pbitmapsource, IWICImagingFactory * pimagingfactory)
{

   comptr < IWICBitmap > piBmp;

   HRESULT hr = pimagingfactory->CreateBitmapFromSource(pbitmapsource, WICBitmapCacheOnLoad, &piBmp);

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

   pimageFrame->create({ (int)uiWidth, (int)uiHeight });

   if (pimageFrame->area() <= 0)
   {

      return false;

   }

   pimageFrame->map();

   ::copy_colorref(pimageFrame->get_data(), uiWidth, uiHeight, pimageFrame->scan_size(), (color32_t *)pData, cbStride);

   
   return true;


}


comptr < IWICImagingFactory > wic_get_imaging_factory()
{

   comptr < IWICImagingFactory > pimagingfactory;

   pimagingfactory.CoCreateInstance(CLSID_WICImagingFactory1);

   return pimagingfactory;

}


//bool is_jpeg(IWICBitmapDecoder * pBitmapDecoder)
//{
//   
//   GUID guidFormat = { };
//
//   HRESULT hr = pBitmapDecoder->GetContainerFormat(&guidFormat);
//
//   if (FAILED(hr))
//   {
//
//      return false;
//
//   }
//
//   return IsEqualGUID(guidFormat, GUID_ContainerFormatJpeg);
//
//}
//
//HRESULT get_query_reader(const widechar * wszPath, IWICMetadataQueryReader * pqueryreaderParent, comptr<IWICMetadataQueryReader> & pqueryreader)
//{
//
//   PROPVARIANT value;
//   
//   ::PropVariantInit(&value);
//
//   HRESULT hr = pqueryreaderRoot->GetMetadataByName(wszIFDPath, &value);
//   
//   if (FAILED(hr))
//   {
//
//      return hr;
//
//   }
//   else if (value.vt != VT_UNKNOWN)
//   {
//
//      return E_FAIL;
//
//   }
//
//   return value.punkVal->QueryInterface(IID_IWICMetadataQueryReader, &pqueryreader);
//
//}




#ifdef _UWP


bool node_save_image(::Windows::Storage::Streams::InMemoryRandomAccessStream ^ randomAccessStream,  const ::image * pimage, ::save_image * psaveimage)
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

   Windows::Storage::Streams::InMemoryRandomAccessStream ^ randomAccessStream = ref new Windows::Storage::Streams::InMemoryRandomAccessStream();

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
   xxf_zero(stg);
   pstream->Stat(&stg, STATFLAG_NONAME);
   LARGE_INTEGER l;
   l.QuadPart = 0;
   pstream->Seek(l, STREAM_SEEK_SET, nullptr);


   memory mem;

   mem.set_size(1024 * 1024);

   ULONG ulPos = 0;
   ULONG ulRead;
   ULONG ul;
   do
   {

      ulRead = 0;

      ul = (ULONG) stg.cbSize.QuadPart - ulPos;

      pstream->Read(mem.get_data(), (ULONG)__min(ul, mem.get_size()), &ulRead);

      if (ulRead > 0)
      {

         pfile->write(mem.get_data(), ulRead);

         ulPos += ulRead;

      }

   } while (ulRead > 0 && stg.cbSize.QuadPart - ulPos > 0);

   return true;

}


bool node_save_image(IStream * pstream, const ::image * pimage, ::save_image * psaveimage)
{

   comptr < IWICImagingFactory > pimagingfactory = nullptr;
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
      (LPVOID *)& pimagingfactory);

   if (SUCCEEDED(hr))
   {

      hr = pimagingfactory->CreateStream(&piStream);

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
         hr = pimagingfactory->CreateEncoder(GUID_ContainerFormatBmp, nullptr, &piEncoder);
         break;
      case draw2d::format_gif:
         hr = pimagingfactory->CreateEncoder(GUID_ContainerFormatGif, nullptr, &piEncoder);
         break;
      case draw2d::format_jpeg:
         hr = pimagingfactory->CreateEncoder(GUID_ContainerFormatJpeg, nullptr, &piEncoder);
         break;
      case draw2d::format_png:
         hr = pimagingfactory->CreateEncoder(GUID_ContainerFormatPng, nullptr, &piEncoder);
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
         varValue.fltVal = max(0.f, min(1.f, psaveimage->m_iQuality / 100.0f));

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

   const color32_t * pcr = pimage->get_data();

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

            hr = piBitmapFrame->WritePixels(uiHeight, pimage->scan_size(), uiHeight * pimage->scan_size(), (byte *)pcr);

         }

      }
      else
      {

         comptr <IWICBitmap> pbitmap;

         if (SUCCEEDED(hr))
         {

            hr = pimagingfactory->CreateBitmapFromMemory(
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

            hr = pimagingfactory->CreateFormatConverter(&pconverter);

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



