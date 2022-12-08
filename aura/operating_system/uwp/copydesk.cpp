#include "framework.h"
#include "aura/graphics/draw2d/common.h"
#include "aura/os/windows_common/draw2d_direct2d_global.h"
#include "_uwp.h"
#include <shlobj.h>


CLASS_DECL_AURA bool node_save_image(::winrt::Windows::Storage::Streams::IRandomAccessStream^ stream, ::image* pimage, ::save_image* psaveimage);

bool node_save_image(::image * pimage, ::winrt::Windows::Storage::Streams::IRandomAccessStream ^stream, ::aura::application * papp);


CLASS_DECL_AURA bool node_save_image(::winrt::Windows::Storage::Streams::IRandomAccessStream ^ randomAccessStream, const ::image * pimage, ::save_image * psaveimage);


namespace universal_windows
{


   copydesk::copydesk()
   {
      
      m_bHasFile = false;

      m_bHasPlainText = false;

      m_eventsink = ref memory_new event_sink;

      m_eventsink->m_pcopydesk = this;

   }


   copydesk::~copydesk()
   {

   }


   bool copydesk::_has_filea()
   {

      return m_bHasFile;

   }


   bool copydesk::_get_filea(::file::path_array & patha, e_op & eop)
   {

      defer_main_thread([&patha, this]()
      {

         ::winrt::Windows::ApplicationModel::DataTransfer::DataPackageView ^ impact = ::winrt::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();

         if (impact != nullptr)
         {

            if (impact->Contains(::winrt::Windows::ApplicationModel::DataTransfer::StandardDataFormats::ApplicationLink))
            {

               m_bHasFile = true;

            }
            else if (impact->Contains(::winrt::Windows::ApplicationModel::DataTransfer::StandardDataFormats::StorageItems))
            {

               ::winrt::Windows::Foundation::Collections::IVectorView < ::winrt::Windows::Storage::IStorageItem ^ > ^ items = ::wait(impact->GetStorageItemsAsync());

               if (items)
               {

                  for (uptr u = 0; u < items->Size; u++)
                  {

                     patha.add(items->GetAt(u)->Path->Begin());

                  }

                  m_bHasFile = true;

               }

            }

         }

      });

      return m_bHasFile;

   }


   bool copydesk::_set_filea(const ::file::path_array & patha, e_op eop)
   {

      throw ::exception(todo);

      return false;

   }

   void copydesk::event_sink::ContentChanged(Platform::Object ^ ,Platform::Object ^)
   {

      m_pcopydesk->on_content_changed();

   }

   void copydesk::initialize(::particle * pparticle)
   {

      auto estatus = ::user::copydesk::initialize(pparticle);

      if(!estatus)
      {

         return estatus;

      }

      ::auraacmesystem()->main_user_sync(__routine([this]()
         {

            on_content_changed();

            ::winrt::Windows::ApplicationModel::DataTransfer::Clipboard::ContentChanged += ref memory_new ::winrt::Windows::Foundation::EventHandler <::Platform::Object ^>(m_eventsink, &event_sink::ContentChanged);

         }));

      return true;

   }


   void copydesk::destroy()
   {

      ::user::copydesk::destroy();

   }


   bool copydesk::_set_plain_text(const ::string & str)
   {

      auto package = ref memory_new ::winrt::Windows::ApplicationModel::DataTransfer::DataPackage;

      if (package == nullptr)
      {

         return false;

      }

      package->RequestedOperation = ::winrt::Windows::ApplicationModel::DataTransfer::DataPackageOperation::Copy;

      package->SetText(str);

      defer_main_thread([&package, this]()
      {

         ::winrt::Windows::ApplicationModel::DataTransfer::Clipboard::SetContent(package);

      });

      return true;

   }


   bool copydesk::_get_plain_text(string & str)
   {

      bool bOk = false;

      defer_main_thread([&str, &bOk, this]()
      {

         auto dataPackage = ::winrt::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();

         if (dataPackage != nullptr && dataPackage->Contains(::winrt::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Text))
         {

            str = ::wait(dataPackage->GetTextAsync())->Begin();

            bOk = true;

         }

         
      });

      return bOk;

   }


   bool copydesk::_has_plain_text()
   {

      return m_bHasPlainText;

   }


   void copydesk::on_content_changed()
   {

      auto dataPackageView = ::winrt::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();

      if (dataPackageView == nullptr)
      {

         return;

      }

      auto pformats = dataPackageView->AvailableFormats;

      m_bHasImage = ::papaya::array::contains_item(pformats, ::winrt::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Bitmap);

      if (::papaya::array::contains_item(pformats, ::winrt::Windows::ApplicationModel::DataTransfer::StandardDataFormats::ApplicationLink))
      {

         m_bHasFile = true;

      }
      else if (::papaya::array::contains_item(pformats, ::winrt::Windows::ApplicationModel::DataTransfer::StandardDataFormats::StorageItems))
      {

         m_bHasFile = true;

      }
      else
      {

         m_bHasFile = false;

      }

      m_bHasPlainText = ::papaya::array::contains_item(pformats, ::winrt::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Text);

   }


   bool copydesk::_has_image()
   {

      return m_bHasImage;

   }


   bool copydesk::_desk_to_image(::image * pimage)
   {

      return pcontextimage->_desk_to_image(pimage);

   }


   bool copydesk::_image_to_desk(const ::image * pimage)
   {

      return pcontextimage->_image_to_desk(pimage);

   }


} // namespace universal_windows




