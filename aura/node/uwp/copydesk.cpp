#include "framework.h"
#include "aura/graphics/draw2d/common.h"
#include "_uwp.h"
#include <shlobj.h>


CLASS_DECL_AURA bool node_save_image(Windows::Storage::Streams::IRandomAccessStream^ stream, ::image* pimage, ::save_image* psaveimage);

bool node_save_image(::image * pimage, Windows::Storage::Streams::IRandomAccessStream ^stream, ::aura::application * papp);


CLASS_DECL_AURA bool node_save_image(Windows::Storage::Streams::IRandomAccessStream ^ randomAccessStream, const ::image * pimage, ::save_image * psaveimage);


namespace uwp
{


   copydesk::copydesk()
   {
      
      m_bHasFile = false;

      m_bHasPlainText = false;

      m_eventsink = ref new event_sink;

      m_eventsink->m_pcopydesk = this;

   }


   copydesk::~copydesk()
   {

   }


   bool copydesk::_has_filea()
   {

      return m_bHasFile;

   }


   bool copydesk::_get_filea(::file::patha & patha, e_op & eop)
   {

      defer_main_thread([&patha, this]()
      {

         ::Windows::ApplicationModel::DataTransfer::DataPackageView ^ view = ::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();

         if (view != nullptr)
         {

            if (view->Contains(::Windows::ApplicationModel::DataTransfer::StandardDataFormats::ApplicationLink))
            {

               m_bHasFile = true;

            }
            else if (view->Contains(::Windows::ApplicationModel::DataTransfer::StandardDataFormats::StorageItems))
            {

               ::Windows::Foundation::Collections::IVectorView < ::Windows::Storage::IStorageItem ^ > ^ items = ::wait(view->GetStorageItemsAsync());

               for (uptr u = 0; u < items->Size; u++)
               {

                  patha.add(items->GetAt(u)->Path->Begin());

               }

               m_bHasFile = true;

            }

         }

      });

      return m_bHasFile;

   }


   bool copydesk::_set_filea(const ::file::patha & patha, e_op eop)
   {

      __throw(todo());

      return false;

   }

   void copydesk::event_sink::ContentChanged(Platform::Object ^ ,Platform::Object ^)
   {

      m_pcopydesk->on_content_changed();

   }

   ::estatus copydesk::initialize(::layered * pobjectContext)
   {

      auto estatus = ::user::copydesk::initialize(pobjectContext);

      if(!estatus)
      {

         return estatus;

      }

      System.main_user_async(__procedure([this]()
         {

            on_content_changed();

            ::Windows::ApplicationModel::DataTransfer::Clipboard::ContentChanged += ref new ::Windows::Foundation::EventHandler <::Platform::Object ^>(m_eventsink, &event_sink::ContentChanged);

         }));

      return true;

   }


   void copydesk::finalize()
   {

      ::user::copydesk::finalize();

   }


   bool copydesk::_set_plain_text(const string & str)
   {

      auto package = ref new ::Windows::ApplicationModel::DataTransfer::DataPackage;

      if (package == nullptr)
      {

         return false;

      }

      package->RequestedOperation = ::Windows::ApplicationModel::DataTransfer::DataPackageOperation::Copy;

      package->SetText(str);

      defer_main_thread([&package, this]()
      {

         ::Windows::ApplicationModel::DataTransfer::Clipboard::SetContent(package);

      });

      return true;

   }


   bool copydesk::_get_plain_text(string & str)
   {

      bool bOk = false;

      defer_main_thread([&str, &bOk, this]()
      {

         auto dataPackage = ::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();

         if (dataPackage != nullptr && dataPackage->Contains(::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Text))
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

      auto dataPackageView = ::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();

      if (dataPackageView == nullptr)
      {

         return;

      }

      auto pformats = dataPackageView->AvailableFormats;

      m_bHasImage = ::papaya::array::contains_item(pformats, ::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Bitmap);

      if (::papaya::array::contains_item(pformats, ::Windows::ApplicationModel::DataTransfer::StandardDataFormats::ApplicationLink))
      {

         m_bHasFile = true;

      }
      else if (::papaya::array::contains_item(pformats, ::Windows::ApplicationModel::DataTransfer::StandardDataFormats::StorageItems))
      {

         m_bHasFile = true;

      }
      else
      {

         m_bHasFile = false;

      }

      m_bHasPlainText = ::papaya::array::contains_item(pformats, ::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Text);

   }


   bool copydesk::_has_image()
   {

      return Application.image()._desk_has_image();

   }


   bool copydesk::_desk_to_image(::image * pimage)
   {

      return Application.image()._desk_to_image(pimage);

   }


   bool copydesk::_image_to_desk(const ::image * pimage)
   {

      return Application.image()._image_to_desk(pimage);

   }


} // namespace uwp




