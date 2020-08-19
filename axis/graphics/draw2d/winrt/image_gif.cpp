#ifdef _UWP


CLASS_DECL_AURA bool windows_load_image_from_file(::image * pimage, Windows::Storage::Streams::IRandomAccessStream ^stream, ::aura::application * papp)
{

   if (!defer_co_initialize_ex(true))
      return false;

   try
   {

      comptr < IStream > pstream;

      ::CreateStreamOverRandomAccessStream(stream, IID_PPV_ARGS(&pstream));

      comptr < IWICImagingFactory > piFactory = nullptr;

      comptr< IWICBitmapDecoder > decoder;
      HRESULT hr = CoCreateInstance(
                   CLSID_WICImagingFactory,
                   nullptr,
                   CLSCTX_INPROC_SERVER,
                   IID_IWICImagingFactory,
                   (LPVOID*)&piFactory);

      if (SUCCEEDED(hr))
      {

         hr = piFactory->CreateDecoderFromStream(pstream, nullptr, WICDecodeMetadataCacheOnLoad, &decoder);
      }

      //if(SUCCEEDED(hr))
      //{

      //   hr = decoder->Initialize(pstream,WICDecodeMetadataCacheOnDemand);

      //}

      comptr< IWICBitmapFrameDecode> pframe;

      if (!windows_load_image_from_frame(pframe, pimage, piFactory, decoder, 0))
      {

         return false;

      }

   }
   catch (...)
   {
      return false;
   }
   //DWORD dw2 =::get_tick();
   //TRACE("InPath %d ms\n",dw2 - dw1);
   //dwLast = dw2;

   //memfile.Truncate(0);

   //}
   return true;

}


CLASS_DECL_AURA bool node_save_image(const ::image * pimage, Windows::Storage::Streams::IRandomAccessStream ^stream, ::aura::application * papp)
{

   if (!defer_co_initialize_ex(true))
      return false;

   try
   {

      comptr < IStream > pstream;

      ::CreateStreamOverRandomAccessStream(stream, IID_PPV_ARGS(&pstream));

      comptr < IWICImagingFactory > piFactory = nullptr;

      comptr< IWICBitmapDecoder > decoder;
      HRESULT hr = CoCreateInstance(
                   CLSID_WICImagingFactory,
                   nullptr,
                   CLSCTX_INPROC_SERVER,
                   IID_IWICImagingFactory,
                   (LPVOID*)&piFactory);

      if (SUCCEEDED(hr))
      {

         hr = piFactory->CreateDecoderFromStream(pstream, nullptr, WICDecodeMetadataCacheOnDemand, &decoder);
      }

      //if(SUCCEEDED(hr))
      //{

      //   hr = decoder->Initialize(pstream,WICDecodeMetadataCacheOnDemand);

      //}

      comptr< IWICBitmapFrameDecode> pframe;

      if (!windows_load_image_from_frame(pframe, pimage, piFactory, decoder, 0))
      {

         return false;

      }

   }
   catch (...)
   {
      return false;
   }
   //DWORD dw2 =::get_tick();
   //TRACE("InPath %d ms\n",dw2 - dw1);
   //dwLast = dw2;

   //memfile.Truncate(0);

   //}
   return true;

}


#endif



