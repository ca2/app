#include "framework.h"
//#include "apex/graphics/draw2d/common.h"
#include "_uwp.h"
#include <shlobj.h>


CLASS_DECL_APEX bool node_save_image(Windows::Storage::Streams::IRandomAccessStream^ stream, ::image* pimage, ::save_image* psaveimage);

bool node_save_image(::image * pimage, Windows::Storage::Streams::IRandomAccessStream ^stream, ::application * papp);


CLASS_DECL_APEX bool node_save_image(Windows::Storage::Streams::IRandomAccessStream ^ randomAccessStream, const ::image * pimage, ::save_image * psaveimage);


namespace uwp
{


   copydesk::copydesk()
   {
   }

   copydesk::~copydesk()
   {
   }


   bool copydesk::_has_filea()
   {

      bool bHasFile = false;

      defer_main_thread([&bHasFile, this]()
      {

         ::Windows::ApplicationModel::DataTransfer::DataPackageView ^ view = ::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();

         if(view == nullptr)
         {

            //iFileCount = 0;
            return;

         }

         if(view->Contains(::Windows::ApplicationModel::DataTransfer::StandardDataFormats::ApplicationLink))
         {

            bHasFile = true;

         }
         //else if(view->Contains("FileDrop"))
         //{

         //   HGLOBAL hglobal;

         //   ::Windows::Storage::Streams::IInputStream ^ stream = (::Windows::Storage::Streams::IInputStream ^):: wait(view->GetDataAsync("FileDrop"));

         //   ::Windows::Storage::Streams::IBuffer ^ buffer = ref new ::Windows::Storage::Streams::Buffer(sizeof(HGLOBAL));

         //   stream->ReadAsync(buffer, sizeof(HGLOBAL), ::Windows::Storage::Streams::InputStreamOptions::None);

         //   memory memory;

         //   memory.set_os_buffer(buffer);

         //   ::memcpy_dup(&hglobal, memory.get_data(), sizeof(HGLOBAL));

         //   //iCount = ::DragQueryFile(hglobal , 0xFFFFFFFF, nullptr, 0);

         //   //__throw(todo);
         //   // assumes true

         //   bHasFile = true;

         //}
         else if(view->Contains(::Windows::ApplicationModel::DataTransfer::StandardDataFormats::StorageItems))
         {

            ::Windows::Foundation::Collections::IVectorView < ::Windows::Storage::IStorageItem ^ > ^ items = ::wait(view->GetStorageItemsAsync());

            bHasFile = true;

         }

      });

      return bHasFile;


   }


   bool copydesk::_get_filea(::file::patha & patha, e_op & eop)
   {

      bool bHasFile = false;

      defer_main_thread([&bHasFile, &patha, this]()
      {

         ::Windows::ApplicationModel::DataTransfer::DataPackageView ^ view = ::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();

         if (view == nullptr)
         {

            return;

         }

         if (view->Contains(::Windows::ApplicationModel::DataTransfer::StandardDataFormats::ApplicationLink))
         {

            bHasFile = true;

         }
         else if (view->Contains(::Windows::ApplicationModel::DataTransfer::StandardDataFormats::StorageItems))
         {

            ::Windows::Foundation::Collections::IVectorView < ::Windows::Storage::IStorageItem ^ > ^ items = ::wait(view->GetStorageItemsAsync());

            for (int i = 0; i < items->Size; i++)
            {

               patha.add(items->GetAt(i)->Path->Begin());

            }

            bHasFile = true;

         }

      });

      return bHasFile;

   }


   bool copydesk::_set_filea(const ::file::patha & patha, e_op eop)
   {

#ifdef WINDOWS_DESKTOP

      ASSERT(m_p->is_window());

      strsize iLen = 0;

      for(int i = 0; i < stra.get_size(); i++)
      {
         iLen += ::str::international::utf8_to_unicode_count(stra[i]) + 1;
      }


      HGLOBAL hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(DROPFILES) + (iLen + 1) * sizeof(WCHAR));
      LPDROPFILES pDropFiles = (LPDROPFILES) ::GlobalLock(hglbCopy);
      pDropFiles->pFiles = sizeof(DROPFILES);
      pDropFiles->point.x = pDropFiles->point.y = 0;
      pDropFiles->fNC = true;
      pDropFiles->fWide = true; // ANSI charset

      ASSERT(m_p->is_window());
      char * lptstrCopy = (char *) pDropFiles;
      lptstrCopy += pDropFiles->pFiles;
      unichar * lpwstrCopy = (unichar *) lptstrCopy;
      for(int i = 0; i < stra.get_size(); i++)
      {
         ASSERT(m_p->is_window());
         ::str::international::utf8_to_unicode(lpwstrCopy, ::str::international::utf8_to_unicode_count(stra[i]) + 1, stra[i]);
         ASSERT(m_p->is_window());
         lpwstrCopy += (stra[i].get_length() + 1);
      }
      ASSERT(m_p->is_window());
      *lpwstrCopy = '\0';    // nullptr character
      ASSERT(m_p->is_window());
      ::GlobalUnlock(hglbCopy);
      ASSERT(m_p->is_window());
      if(!m_p->OpenClipboard())
      {
         ::GlobalFree(hglbCopy);
         return;
      }
      EmptyClipboard();
      SetClipboardData(CF_HDROP, hglbCopy);
      VERIFY(::CloseClipboard());

#else

      __throw(todo);

#endif

      return false;

   }


   ::e_status copydesk::initialize(::object * pobject)
   {

      auto estatus = ::user::copydesk::initialize(pobject);

      if(!estatus)
      {

         return estatus;

      }

      return true;

   }


   ::e_status copydesk::finalize()
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

         if (dataPackage == nullptr)
         {

            return;

         }

         if (!dataPackage->Contains(::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Text))
         {

            return;

         }

         str = ::wait(dataPackage->GetTextAsync())->Begin();

         bOk = true;

      });

      return bOk;

   }


   bool copydesk::_has_plain_text()
   {

      bool bOk = false;

      defer_main_thread([&bOk, this]()
      {

         auto dataPackage = ::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();

         if (dataPackage == nullptr)
         {

            return;

         }

         if (!dataPackage->Contains(::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Text))
         {

            return;

         }

         bOk = true;

      });

      return bOk;

   }


   bool copydesk::_has_image()
   {

      return ::apex::get_system()->imaging()._desk_has_image();

   }


   bool copydesk::_desk_to_image(::image * pimage)
   {

      return ::apex::get_system()->imaging()._desk_to_image(pimage);

   }


   bool copydesk::_image_to_desk(const ::image * pimage)
   {

      return ::apex::get_system()->imaging()._image_to_desk(pimage);

   }


} // namespace uwp




