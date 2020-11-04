#include "framework.h"
#include <wincodec.h>


namespace imaging_wic
{


   bool windows_image_from_bitmap_source(::image * pimageFrame, IWICBitmapSource * pbitmapsource, IWICImagingFactory * pimagingfactory);


   context_image::context_image()
   {

   }


   context_image::~context_image()
   {

   }


   ::estatus context_image::initialize(::layered * pobjectContext)
   {

      auto estatus = ::context_image::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      __own(this, m_pmanagerImageLoad, __new(handler_manager("imaging_load_image", true)));

      if (!m_pmanagerImageLoad)
      {

         return ::error_failed;

      }

#ifdef WINDOWS

      m_pmanagerImageLoad->m_bUseDedicatedThread = true;

#endif

      return estatus;

   }


   comptr < IWICImagingFactory > get_imaging_factory()
   {

      comptr < IWICImagingFactory > pimagingfactory;

      //defer_co_initialize_ex(false);

      HRESULT hrCreate = pimagingfactory.CoCreateInstance(CLSID_WICImagingFactory1, nullptr, CLSCTX_INPROC_SERVER);

      if (FAILED(hrCreate))
      {

         TRACE("Failed creating WICImagingFactory1 %x", hrCreate);

      }

      return pimagingfactory;

   }


#ifdef _UWP

   // platform implementation may use this context_image-"routing" to manipulate the image/clipboard
   bool context_image::_desk_to_image(::image* pimage)
   {


      bool bOk = true;

      main_sync(__method([&]()
         {

            auto dataPackage = ::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();

            if (dataPackage == nullptr)
            {

               bOk = false;

               return;

            }

            if (!dataPackage->Contains(::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Bitmap))
            {

               bOk = false;

               return;

            }

            auto p = ::wait(dataPackage->GetDataAsync(L"DeviceIndependentBitmap"));

            //::Windows::Storage::Streams::IRandomAccessStream^ stream = (::Windows::Storage::Streams::IRandomAccessStream^)

            //auto ref = ::wait(dataPackage->GetDataAsync(L"DeviceIndependentBitmap"));

            if (p == nullptr)
            {

               p = (::Windows::Storage::Streams::IRandomAccessStream^) ::wait(dataPackage->GetDataAsync(L"DeviceIndependentBitmapV5"));

               if (p == nullptr)
               {
                  
                  p = (::Windows::Storage::Streams::IRandomAccessStream^) ::wait(dataPackage->GetDataAsync(L"DeviceInterchangeFormat"));

                  if (p == nullptr)
                  {

                     bOk = false;

                     return;

                  }

               }

            }

            ::Windows::Storage::Streams::IRandomAccessStream^ stream = (::Windows::Storage::Streams::IRandomAccessStream ^ ) p;

            //::Windows::Storage::Streams::IRandomAccessStreamWithContentType ^ stream = ::wait(ref->OpenReadAsync());

            //if (stream == nullptr)
            //{


            //   bOk = false;

            //   return;

            //}

            memsize s = (memsize)stream->Size;

            Windows::Storage::Streams::Buffer^ buffer = ref new Windows::Storage::Streams::Buffer(s);

            if (buffer == nullptr)
               return;

            ::wait(stream->ReadAsync(buffer, s, ::Windows::Storage::Streams::InputStreamOptions::ReadAhead));

            memory m;

            m.set_os_buffer(buffer);

            BITMAPINFO* _ = (BITMAPINFO*)m.get_data();

            pimage->create({ _->bmiHeader.biWidth,  _->bmiHeader.biHeight });

            pimage->map();

            vertical_swap_copy_colorref(
               pimage->get_data(),
               pimage->width(),
               pimage->height(),
               pimage->scan_size(),
               (COLORREF*)&m.get_data()[_->bmiHeader.biSize],
               _->bmiHeader.biSizeImage / _->bmiHeader.biHeight);


            //memory m;

            //m.

            //if (!windows_load_image_from_file(pimage, stream, get_context_application()))
            //{


            //   bOk = false;

            //   return;

            //}

         }));

      return bOk;

   }
   // platform implementation may use this context_image-"routing" to manipulate the image/clipboard
   bool context_image::_desk_has_image()
   {

      bool bOk = false;

      main_sync(__method([&bOk]()
         {

            auto dataPackage = ::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();

            if (dataPackage == nullptr)
            {

               return;

            }

            if (dataPackage->Contains(::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Bitmap))
            {

               bOk = true;

               return;

            }

         }));

      return bOk;

   }

   // platform implementation may use this context_image-"routing" to manipulate the image/clipboard
   bool context_image::_image_to_desk(const ::image* pimage)
   {

      bool bOk = true;

      auto package = ref new ::Windows::ApplicationModel::DataTransfer::DataPackage;

      if (package == nullptr)
      {

         return false;

      }

      Windows::Storage::Streams::InMemoryRandomAccessStream^ randomAccessStream = ref new Windows::Storage::Streams::InMemoryRandomAccessStream();

      ::save_image saveimage;

      saveimage.m_eformat = ::draw2d::format_png;

      saveimage.m_iQuality = 100;

      if (!node_save_image(randomAccessStream, pimage, &saveimage))
      {

         return false;

      }

      package->RequestedOperation = ::Windows::ApplicationModel::DataTransfer::DataPackageOperation::Copy;

      auto context_object = ::Windows::Storage::Streams::RandomAccessStreamReference::CreateFromStream(randomAccessStream);

      package->SetBitmap(context_object);

      defer_main_thread([&package, this]()
         {

            ::Windows::ApplicationModel::DataTransfer::Clipboard::SetContent(package);

         });

      return true;


   }

#endif


} // namespace imaging_wic




