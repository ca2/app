#include "framework.h"
#include <wincodec.h>
#include <shcore.h>


namespace imaging_wic
{


   bool windows_image_from_bitmap_source(::image * pimageFrame, IWICBitmapSource * pbitmapsource, IWICImagingFactory * pimagingfactory);


   ::e_status context_image::_load_image(::image * pimageParam, const payload & varFile, bool bSync, bool bCreateHelperMaps)
   {

      auto ploadimage = __new(load_image(this));

      auto estatus = ploadimage->initialize(this);

      if (!estatus)
      {

         return estatus;

      }

      ploadimage->m_pimage = pimageParam;

      ploadimage->m_varFile = varFile;

      pimageParam->m_bCreateHelperMaps = bCreateHelperMaps;

      m_pmanagerImageLoad->handle(ploadimage, bSync);

      return ploadimage->m_estatus;

   }


   context_image::load_image::load_image(context_image * pcontextimage) :
      m_pcontextimage(pcontextimage)
   {


   }

   
   context_image::load_image::~load_image()
   {


   }



   ::e_status context_image::load_image::run()
   {

      //defer_co_initialize_ex(false);

      ::image * pimage = m_pimage;

      pimage->m_estatus = error_failed;

      try
      {
         
         ::payload payload = m_varFile;

         ::file::path path = payload.get_file_path();

         bool bCache = true;

         while (true)
         {

            auto pmemory = create_memory();

            if (!bCache)
            {

               ::file::set_no_cache(payload);

            }

            Context.file().as_memory(payload, *pmemory);

            const char* psz = (const char*)pmemory->get_data();

            auto size = pmemory->get_size();

            if (::is_null(psz))
            {

               if (bCache)
               {

                  bCache = false;

                  continue;

               }

               return pimage->m_estatus;

            }

            auto estatus = Application.image().load_svg(pimage, pmemory);

            if (::succeeded(estatus))
            {

               pimage->on_load_image();

               pimage->set_ok();

               pimage->m_estatus = ::success;

               return pimage->m_estatus;

            }

            if (pmemory->get_size() > 3 && strnicmp(psz, "gif", 3) == 0)
            {

               if (!m_pcontextimage->_load_multi_frame_image(pimage, pmemory))
               {

                  pimage->set_nok();

                  if (bCache)
                  {

                     bCache = false;

                     continue;

                  }

                  return pimage->m_estatus;

               }

               pimage->on_load_image();

               pimage->set_ok();

               pimage->m_estatus = ::success;

               return pimage->m_estatus;

            }

            on_os_load_image(pmemory);

            if (pimage->is_ok())
            {

               break;

            }
            else
            {

               if (bCache)
               {

                  bCache = false;

                  continue;

               }
               else
               {

                  break;

               }

            }

         }

      }
      catch (...)
      {

      }

      return pimage->m_estatus;

   }


   void context_image::load_image::on_os_load_image(memory_pointer pmemory)
   {

      ::image * pimage = m_pimage;

      pimage->m_estatus = ::error_failed;

      pimage->set_nok();

      comptr < IWICImagingFactory > pimagingfactory;

      pimagingfactory = get_imaging_factory();

      comptr < IWICStream > piStream;

      HRESULT hr = pimagingfactory->CreateStream(&piStream);

      if (FAILED(hr))
      {

         return;

      }

      hr = piStream->InitializeFromMemory(pmemory->get_data(), (::u32)pmemory->get_size());

      if (FAILED(hr))
      {

         return;

      }

      comptr < IWICBitmapDecoder > piDecoder;

      hr = pimagingfactory->CreateDecoderFromStream(piStream, 0, WICDecodeMetadataCacheOnLoad, &piDecoder); // jpeg,png:OK, bmp:88982f50のエラーになる, iconもエラー

      if (FAILED(hr))
      {

         return;

      }

      comptr < IWICBitmapFrameDecode > pframedecode;

      hr = piDecoder->GetFrame(0, &pframedecode);

      if (FAILED(hr))
      {

         return;

      }

      int iOrientation = -1;

      {

         HRESULT hrExif = hr;

         comptr<IWICMetadataQueryReader> pqueryreader;

         if (SUCCEEDED(hrExif))
         {

            hrExif = pframedecode->GetMetadataQueryReader(&pqueryreader);

         }

         PROPVARIANT value;

         if (SUCCEEDED(hrExif))
         {

            PropVariantInit(&value);

            bstring bstr("/app1/ifd/{ushort=274}");

            hrExif = pqueryreader->GetMetadataByName(bstr.c_str(), &value);

            if (FAILED(hrExif))
            {

               PropVariantClear(&value);

               PropVariantInit(&value);

               bstring bstr("/ifd/{ushort=274}");

               hrExif = pqueryreader->GetMetadataByName(bstr.c_str(), &value);

            }

            string strOrientation;

            if (SUCCEEDED(hrExif))
            {

               iOrientation = value.uiVal;

            }

            PropVariantClear(&value);

         }

      }

      // Convert the image format to 32bppPBGRA
      // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
      // http://d.hatena.ne.jp/sugarontop/20141015
      comptr < IWICFormatConverter > pbitmapsource;

      hr = pimagingfactory->CreateFormatConverter(&pbitmapsource);

      if (FAILED(hr))
      {

         return;

      }

      hr = pbitmapsource->Initialize(pframedecode, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);

      if (FAILED(hr))
      {

         return;

      }

      if (!windows_image_from_bitmap_source(pimage, pbitmapsource, pimagingfactory))
      {

         return;

      }

      pimage->m_iExifOrientation = iOrientation;

      pimage->on_load_image();

      pimage->set_ok();

      //pimage->notify(OK);

      pimage->m_estatus = ::success;




   }

#include "framework.h"
#include <wincodec.h>
#ifdef _UWP
#include <ShCore.h>
#endif


   bool node_save_image(IStream * pstream, const ::image * pimage, ::save_image * psaveimage);


#ifdef _UWP


   CLASS_DECL_IMAGING_WIC bool node_save_image(::Windows::Storage::Streams::InMemoryRandomAccessStream ^ randomAccessStream, const ::image * pimage, ::save_image * psaveimage);


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

      hr = piBmp->GetSize(&uWidth, &uHeight);

      if (hr != S_OK)
      {

         return false;

      }

      WICRect rc;

      rc.X = 0;
      rc.Y = 0;
      rc.Width = uWidth;
      rc.Height = uHeight;

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

      hr = piLock->GetDataPointer(&uArea, &pData);

      if (hr != S_OK)
      {

         return false;

      }

      pimageFrame->create({ (int)uWidth, (int)uHeight });

      if (pimageFrame->area() <= 0)
      {

         return false;

      }

      pimageFrame->map();

      ::copy_colorref(pimageFrame->get_data(), uWidth, uHeight, pimageFrame->scan_size(), (color32_t *)pData, cbStride);


      return true;


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


   bool node_save_image(::Windows::Storage::Streams::InMemoryRandomAccessStream ^ randomAccessStream, const ::image * pimage, const ::save_image * psaveimage)
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



   bool node_save_image(::file::file * pfile, const ::image * pimage, const ::save_image * psaveimage)
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

         ul = (ULONG)stg.cbSize.QuadPart - ulPos;

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
         (LPVOID *)&pimagingfactory);

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
            option.pstrName = (LPOLESTR) L"ImageQuality";
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

         hr = piBitmapFrame->SetSize(uWidth, uHeight);

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

               hr = piBitmapFrame->WritePixels(uHeight, pimage->scan_size(), uHeight * pimage->scan_size(), (byte *)pcr);

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


} // namespace imaging_wic



