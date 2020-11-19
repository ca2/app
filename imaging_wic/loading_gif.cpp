#include "framework.h"
#include <Wincodec.h>


#include <math.h>


#ifdef _UWP
#include <ShCore.h>
#endif


struct FIBITMAP;




namespace imaging_wic
{

   //bool draw2d_gif_load_frame(::image * pimageCanvas, image_frame_array * pframea, image_frame * pframe, int uFrameIndex, u8 * ba, int iScan, colorref_array & colorrefa, int transparentIndex);
   bool windows_image_from_bitmap_source(::image * pimage, IWICBitmapSource * pbitmapsource, IWICImagingFactory * pimagingfactory);
   color32_t windows_image_metadata_get_background_color(IWICMetadataQueryReader * pqueryreader, IWICBitmapDecoder * pbitmapdecoder, IWICImagingFactory * pimagingfactory);


   ::estatus context_image::_load_image(::image * pimageCompose, __pointer(image_frame_array) & pframea, memory_pointer pmemory)
   {

      HRESULT hr = E_FAIL;

      {

         auto pimagingfactory = get_imaging_factory();

         comptr < IWICStream > pwicstream;

         hr = pimagingfactory->CreateStream(&pwicstream);

         if (FAILED(hr))
         {
            return false;

         }

         auto pinputstream = pmemory->create_istream();

         hr = pwicstream->InitializeFromIStream(pinputstream);

         if (FAILED(hr))
         {

            return false;

         }

         comptr < IWICBitmapDecoder > pbitmapdecoder;

         hr = pimagingfactory->CreateDecoderFromStream(pwicstream, 0, WICDecodeMetadataCacheOnLoad, &pbitmapdecoder); // jpeg,png:OK, bmp:88982f50のエラーになる, iconもエラー

         if (FAILED(hr))
         {

            return false;

         }

         ::count cFrame;

         {

            ::u32 uCount = 0;

            hr = pbitmapdecoder->GetFrameCount(&uCount);

            if (FAILED(hr))
            {

               return false;

            }

            cFrame = uCount;

         }

         
         comptr < IWICMetadataQueryReader > pimetadataqueryreader;

         hr = pbitmapdecoder->GetMetadataQueryReader(&pimetadataqueryreader);

         if (FAILED(hr))
         {

            return false;

         }

         PROPVARIANT propValue;

         PropVariantInit(&propValue);

         hr = pimetadataqueryreader->GetMetadataByName(L"/logscrdesc/Width", &propValue);

         if (SUCCEEDED(hr))
         {

            hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);

            if (SUCCEEDED(hr))
            {

               pframea->m_size.cx = propValue.uiVal;

            }

         }

         PropVariantClear(&propValue);

         if (FAILED(hr))
         {

            return false;

         }

         PropVariantInit(&propValue);

         hr = pimetadataqueryreader->GetMetadataByName(L"/logscrdesc/Height", &propValue);

         if (SUCCEEDED(hr))
         {

            hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);

            if (SUCCEEDED(hr))
            {

               pframea->m_size.cy = propValue.uiVal;

            }

         }

         PropVariantClear(&propValue);

         if (FAILED(hr))
         {

            return false;

         }

         pframea->m_crBack = windows_image_metadata_get_background_color(pimetadataqueryreader, pbitmapdecoder, pimagingfactory);

         pframea->set_size(cFrame);

         image_pointer pimageFrame;

         for (index iFrame = 0; iFrame < cFrame; iFrame++)
         {

            auto & pframe = pframea->element_at(iFrame);

            __defer_construct_new(pframe);

            auto estatus = __construct(pframe->m_pimage);

            if (!estatus)
            {

               return false;

            }

            pframe->m_iFrame = iFrame;

            __defer_construct(pimageFrame);

            estatus = pimageFrame->create(pframea->m_size, 0);

            if (!estatus)
            {

               return false;

            }

            // pframe->m_pimage->fill(0);

            pimageFrame->fill(0);

            {

               comptr<IWICFormatConverter> pformatconverter;

               comptr<IWICBitmapFrameDecode> pframedecode;

               comptr<IWICMetadataQueryReader > pqueryreader;

               HRESULT hr = pbitmapdecoder->GetFrame((::u32)iFrame, &pframedecode);

               if (SUCCEEDED(hr))
               {

                  hr = pimagingfactory->CreateFormatConverter(&pformatconverter);

               }

               if (SUCCEEDED(hr))
               {

                  hr = pformatconverter->Initialize(
                     pframedecode,
                     GUID_WICPixelFormat32bppPBGRA,
                     WICBitmapDitherTypeNone,
                     nullptr,
                     0.f,
                     WICBitmapPaletteTypeCustom);
               }

               if (SUCCEEDED(hr))
               {

                  hr = windows_image_from_bitmap_source(pimageFrame, pformatconverter, pimagingfactory) ? S_OK : E_FAIL;

               }

               if (SUCCEEDED(hr))
               {

                  hr = pframedecode->GetMetadataQueryReader(&pqueryreader);

               }

               if (SUCCEEDED(hr))
               {

                  PropVariantInit(&propValue);

                  hr = pqueryreader->GetMetadataByName(L"/imgdesc/Left", &propValue);

                  if (SUCCEEDED(hr))
                  {

                     hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);

                     if (SUCCEEDED(hr))
                     {

                        pframe->m_rect.left = static_cast<::i32>(propValue.uiVal);

                     }

                  }

                  PropVariantClear(&propValue);

               }

               if (SUCCEEDED(hr))
               {

                  PropVariantInit(&propValue);

                  hr = pqueryreader->GetMetadataByName(L"/imgdesc/Top", &propValue);

                  if (SUCCEEDED(hr))
                  {

                     hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);

                     if (SUCCEEDED(hr))
                     {

                        pframe->m_rect.top = static_cast<::i32>(propValue.uiVal);

                     }

                  }

                  PropVariantClear(&propValue);

               }

               if (SUCCEEDED(hr))
               {

                  PropVariantInit(&propValue);

                  hr = pqueryreader->GetMetadataByName(L"/imgdesc/Width", &propValue);

                  if (SUCCEEDED(hr))
                  {

                     hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);

                     if (SUCCEEDED(hr))
                     {

                        pframe->m_rect.right = static_cast<::i32>(propValue.uiVal) + pframe->m_rect.left;

                     }

                  }

                  PropVariantClear(&propValue);

               }

               if (SUCCEEDED(hr))
               {

                  PropVariantInit(&propValue);

                  hr = pqueryreader->GetMetadataByName(L"/imgdesc/Height", &propValue);

                  if (SUCCEEDED(hr))
                  {

                     hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);

                     if (SUCCEEDED(hr))
                     {

                        pframe->m_rect.bottom = static_cast<::i32>(propValue.uiVal) + pframe->m_rect.top;

                     }

                  }

                  PropVariantClear(&propValue);

               }

               if (SUCCEEDED(hr))
               {

                  PropVariantInit(&propValue);

                  // Get delay from the optional Graphic Control Extension
                  if (SUCCEEDED(pqueryreader->GetMetadataByName(L"/grctlext/Delay", &propValue)))
                  {

                     hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);

                     if (SUCCEEDED(hr))
                     {

                        // Convert the delay retrieved in 10 ms units to a delay in 1 ms units
                        ::u32 uDelay;

                        hr = UIntMult(propValue.uiVal, 10, &uDelay);

                        pframe->m_tick = uDelay;

                     }

                  }
                  else
                  {

                     // Failed to get delay from graphic control extension. Possibly a
                     // single frame image (non-animated gif)
                     pframe->m_tick = 0;

                  }

                  if (SUCCEEDED(hr))
                  {

                     // Insert an artificial delay to ensure rendering for gif with very small
                     // or 0 delay.  This delay number is picked to match with most browsers'
                     // gif display speed.
                     //
                     // This will defeat the purpose of using zero delay intermediate frames in
                     // order to preserve compatibility. If this is removed, the zero delay
                     // intermediate frames will not be visible.
                     if (pframe->m_tick < 90)
                     {

                        pframe->m_tick = 90;

                     }

                  }

                  PropVariantClear(&propValue);

               }

               if (SUCCEEDED(hr))
               {

                  PropVariantInit(&propValue);

                  int iDisposal = -1;

                  if (SUCCEEDED(pqueryreader->GetMetadataByName(
                     L"/grctlext/Disposal",
                     &propValue)))
                  {
                     hr = (propValue.vt == VT_UI1) ? S_OK : E_FAIL;
                     if (SUCCEEDED(hr))
                     {
                        iDisposal = propValue.bVal;
                     }
                  }
                  else
                  {
                     // Failed to get the disposal method, use default. Possibly a
                     // non-animated gif.
                     //iDisposal
                  }

                  pframe->gif_set_disposal(iDisposal);

                  PropVariantClear(&propValue);

               }



            }

            ::draw2d::e_disposal edisposal = iFrame <= 0 ? ::draw2d::disposal_none : pframea->element_at(iFrame - 1)->m_edisposal;

            pframe->m_edisposal = edisposal;

            pframe->_001Process(pimageCompose, pimageFrame, pframea);

         }

      }

      return SUCCEEDED(hr);

   }









   //#ifdef WINDOWS

   /******************************************************************
   *                                                                 *
   *  DemoApp::get_background_color()                                  *
   *                                                                 *
   *  Reads and stores the background color for gif.                 *
   *                                                                 *
   ******************************************************************/


   bool windows_load_image_from_frame(
      ::image * pimage,
      comptr< IWICBitmapFrameDecode> & pframe,
      IWICImagingFactory * pimagingfactory,
      IWICBitmapDecoder * pbitmapdecoder,
      int iFrame)
   {

      try
      {

         HRESULT hr = pbitmapdecoder->GetFrame(iFrame, &pframe);

         WICPixelFormatGUID px;
         ·zero(px);
         if (!pframe)
         {
            return false;
         }
         if (FAILED(hr))
         {
            return false;
         }

         hr = pframe->GetPixelFormat(&px);
         if (FAILED(hr))
         {
            return false;
         }


         if (px == GUID_WICPixelFormat32bppRGBA)
         {

            ::u32 width = 0;

            ::u32 height = 0;

            pframe->GetSize(&width, &height);

            pimage->create(width, height);

            pimage->map();

            hr = pframe->CopyPixels(nullptr, pimage->scan_size(), pimage->scan_size() * height, (byte *)pimage->get_data());

   #ifdef _UWP
            //pimage->mult_alpha();
   #endif

         }
         else if (px == GUID_WICPixelFormat32bppBGRA)
         {

            ::u32 width = 0;

            ::u32 height = 0;

            pframe->GetSize(&width, &height);

            pimage->create(::size(width, height));

            pimage->map();

            hr = pframe->CopyPixels(nullptr, pimage->scan_size(), pimage->scan_size() * height, (byte *)pimage->get_data());
   #ifdef _UWP
            //pimage->mult_alpha();
   #endif

         }
         else
         {

            comptr<IWICFormatConverter> pbitmap;

            if (SUCCEEDED(hr))
            {

               hr = pimagingfactory->CreateFormatConverter(&pbitmap);

            }

            px = GUID_WICPixelFormat32bppBGRA;

            if (SUCCEEDED(hr))
            {

               hr = pbitmap->Initialize(pframe, px, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);
            }

            //Step 4: Create render target and D2D bitmap from IWICBitmapSource
            ::u32 width = 0;
            ::u32 height = 0;
            if (SUCCEEDED(hr))
            {
               hr = pbitmap->GetSize(&width, &height);
            }

            pimage->create(width, height);

            pimage->map();

            hr = pbitmap->CopyPixels(nullptr, pimage->scan_size(), pimage->scan_size() * height, (byte *)pimage->get_data());


         }



      }
      catch (...)
      {
         return false;
      }

      return true;

   }



   HRESULT windows_image_get_frame(::image * pimageCompose,
      WICColor * rgColors,
      int iUsed,
      image_frame_array * pframea,
      IWICImagingFactory * pimagingfactory,
      IWICBitmapDecoder * pbitmapdecoder,
      ::u32 uFrameIndex)
   {

      __pointer(image_frame) pframe = pframea->element_at(uFrameIndex);

      comptr < IWICBitmapFrameDecode >    pbitmapframedecode;

      comptr < IWICMetadataQueryReader >  pqueryreader;

      // Retrieve the current frame
      HRESULT hr = pbitmapdecoder->GetFrame(uFrameIndex, &pbitmapframedecode);

      comptr < IWICFormatConverter > pbitmap;

      if (SUCCEEDED(hr))
      {

         hr = pimagingfactory->CreateFormatConverter(&pbitmap);

      }

      if (SUCCEEDED(hr))
      {

         hr = pbitmap->Initialize(
            pbitmapframedecode,
            GUID_WICPixelFormat8bppIndexed,
            WICBitmapDitherTypeNone,
            nullptr,
            0.f,
            WICBitmapPaletteTypeCustom);

      }

      ::u32 width = 0;

      ::u32 height = 0;

      if (SUCCEEDED(hr))
      {

         hr = pbitmap->GetSize(&width, &height);

      }

      pframe->m_pimage->create(width, height);

      pframe->m_pimage->map();

      byte_array ba;

      ba.allocate((memsize)pframe->m_pimage->area());

      hr = pbitmap->CopyPixels(nullptr, pframe->m_pimage->width(), (::u32)ba.get_size(), (byte *)ba.get_data());

      if (FAILED(hr))
      {

         return false;

      }

      hr = pbitmapframedecode->GetMetadataQueryReader(&pqueryreader);

      PROPVARIANT propValue;

      if (SUCCEEDED(hr))
      {

         PropVariantInit(&propValue);

         hr = pqueryreader->GetMetadataByName(L"/imgdesc/Left", &propValue);

         if (SUCCEEDED(hr))
         {

            hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);

            if (SUCCEEDED(hr))
            {

               pframe->m_rect.left = propValue.uiVal;

            }

         }

         PropVariantClear(&propValue);

      }

      if (SUCCEEDED(hr))
      {

         PropVariantInit(&propValue);

         hr = pqueryreader->GetMetadataByName(L"/imgdesc/Top", &propValue);

         if (SUCCEEDED(hr))
         {

            hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);

            if (SUCCEEDED(hr))
            {

               pframe->m_rect.top = propValue.uiVal;

            }

         }

         PropVariantClear(&propValue);

      }

      if (SUCCEEDED(hr))
      {

         PropVariantInit(&propValue);

         hr = pqueryreader->GetMetadataByName(L"/imgdesc/Width", &propValue);

         if (SUCCEEDED(hr))
         {

            hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);

            if (SUCCEEDED(hr))
            {

               pframe->m_rect.right = propValue.uiVal + pframe->m_rect.left;

            }

         }

         PropVariantClear(&propValue);

      }

      if (SUCCEEDED(hr))
      {

         PropVariantInit(&propValue);

         hr = pqueryreader->GetMetadataByName(L"/imgdesc/Height", &propValue);

         if (SUCCEEDED(hr))
         {

            hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);

            if (SUCCEEDED(hr))
            {

               pframe->m_rect.bottom = propValue.uiVal + pframe->m_rect.top;

            }

         }

         PropVariantClear(&propValue);

      }

      if (SUCCEEDED(hr))
      {

         PropVariantInit(&propValue);

         // Get delay from the optional Graphic Control Extension
         if (SUCCEEDED(pqueryreader->GetMetadataByName(
            L"/grctlext/Delay",
            &propValue)))
         {

            hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);

            if (SUCCEEDED(hr))
            {

               ::u32 u;

               // Convert the delay retrieved in 10 ms units to a delay in 1 ms units
               hr = UIntMult(propValue.uiVal, 10, &u);

               pframe->m_tick = u;

            }

         }
         else
         {

            // Failed to get delay from graphic control extension. Possibly a
            // single frame image (non-animated gif)
            pframe->m_tick = 0;

         }

         PropVariantClear(&propValue);

         if (pframe->m_tick <= 0)
         {

            output_debug_string("0 delay");

         }

         if (SUCCEEDED(hr))
         {
            // Insert an artificial delay to ensure rendering for gif with very small
            // or 0 delay.  This delay number is picked to match with most browsers'
            // gif display speed.
            //
            // This will defeat the purpose of using zero delay intermediate frames in
            // order to preserve compatibility. If this is removed, the zero delay
            // intermediate frames will not be visible.
            //if (pframe->m_tick < 90)
            {
               // pframe->m_tick = 90;
            }

         }

      }

      if (SUCCEEDED(hr))
      {

         PropVariantInit(&propValue);

         if (SUCCEEDED(pqueryreader->GetMetadataByName(
            L"/grctlext/Disposal",
            &propValue)))
         {

            hr = (propValue.vt == VT_UI1) ? S_OK : E_FAIL;

            if (SUCCEEDED(hr))
            {

               pframe->m_edisposal = (::draw2d::e_disposal) propValue.bVal;

            }

         }
         else
         {

            // Failed to get the disposal method, use default. Possibly a
            // non-animated gif.
            pframe->m_edisposal = ::draw2d::disposal_undefined;

         }

         PropVariantClear(&propValue);

      }

      int transparentIndex = -1;

      hr = S_OK;

      if (SUCCEEDED(hr))
      {

         PropVariantInit(&propValue);

         hr = pqueryreader->GetMetadataByName(
            L"/grctlext/TransparencyFlag",
            &propValue);

         if (SUCCEEDED(hr))
         {

            hr = (propValue.vt != VT_BOOL) ? E_FAIL : S_OK;

            if (SUCCEEDED(hr))
            {

               pframe->m_bTransparent = propValue.boolVal != FALSE;

            }

         }

         PropVariantClear(&propValue);

      }

      if (pframe->m_bTransparent)
      {

         if (SUCCEEDED(hr))
         {

            PropVariantInit(&propValue);

            hr = pqueryreader->GetMetadataByName(
               L"/grctlext/TransparentColorIndex",
               &propValue);

            if (SUCCEEDED(hr))
            {

               hr = (propValue.vt != VT_UI1) ? E_FAIL : S_OK;

               if (SUCCEEDED(hr))
               {

                  transparentIndex = propValue.bVal;

               }

            }

            PropVariantClear(&propValue);

         }

      }

      if (SUCCEEDED(hr) && pframe->m_bTransparent)
      {

         hr = (transparentIndex >= pframea->m_colorrefa.get_count()) ? E_FAIL : S_OK;

      }

      if (SUCCEEDED(hr))
      {

         pframe->m_crTransparent = pframea->m_colorrefa[transparentIndex];

      }
      else
      {

         pframe->m_crTransparent = ARGB(255, 255, 255, 255);

      }

      colorref_array colorrefa;

      cra_from_quada(colorrefa, (RGBQUAD *)rgColors, iUsed);

      if (uFrameIndex == 0)
      {

         if (transparentIndex >= 0)
         {

            pimageCompose->fill(0);

         }
         else
         {

            pimageCompose->fill(pframea->m_crBack);


         }

      }

      //if (!draw2d_gif_load_frame(pimageCompose, pframea, pframe, uFrameIndex, (u8 *)ba.get_data(), width, colorrefa, transparentIndex))
      //{

      //   return false;

      //}

      return true;

   }







   color32_t windows_image_metadata_get_background_color(IWICMetadataQueryReader * pqueryreader, IWICBitmapDecoder * pbitmapdecoder, IWICImagingFactory * pimagingfactory)
   {

      ::u32 dwBGColor;
      byte backgroundIndex = 0;
      WICColor rgColors[256];
      ::u32 cColorsCopied = 0;
      PROPVARIANT propVariant;
      comptr < IWICPalette > pWicPalette;

      color32_t crBk = 0;

      PropVariantInit(&propVariant);
      // If we have a global palette, get the palette and background color
      HRESULT hr = pqueryreader->GetMetadataByName(L"/logscrdesc/GlobalColorTableFlag", &propVariant);
      if (SUCCEEDED(hr))
      {
         hr = (propVariant.vt != VT_BOOL || !propVariant.boolVal) ? E_FAIL : S_OK;
      }

      PropVariantClear(&propVariant);


      if (SUCCEEDED(hr))
      {
         PropVariantInit(&propVariant);
         // Background color index
         hr = pqueryreader->GetMetadataByName(L"/logscrdesc/BackgroundColorIndex", &propVariant);
         if (SUCCEEDED(hr))
         {
            hr = (propVariant.vt != VT_UI1) ? E_FAIL : S_OK;
            if (SUCCEEDED(hr))
            {
               backgroundIndex = propVariant.bVal;
            }
         }

         PropVariantClear(&propVariant);

      }


      // Get the color from the palette
      if (SUCCEEDED(hr))
      {
         hr = pimagingfactory->CreatePalette(&pWicPalette);
      }

      if (SUCCEEDED(hr))
      {
         // Get the global palette
         hr = pbitmapdecoder->CopyPalette(pWicPalette);
      }

      if (SUCCEEDED(hr))
      {
         hr = pWicPalette->GetColors(
            ARRAYSIZE(rgColors),
            rgColors,
            &cColorsCopied);
      }

      if (SUCCEEDED(hr))
      {
         // Check whether background color is outside range
         hr = (backgroundIndex >= cColorsCopied) ? E_FAIL : S_OK;
      }

      if (SUCCEEDED(hr))
      {
         // Get the color in ARGB format
         dwBGColor = rgColors[backgroundIndex];

         // The background color is in ARGB format, and we want to
         // extract the alpha value and convert it to float
         crBk = dwBGColor;
      }

      return crBk;

   }


} // namespace imaging_wic



