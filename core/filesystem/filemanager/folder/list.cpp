#include "framework.h"
////#include "data.h"
#include "list.h"
#include "acme/constant/message.h"
#include "acme/filesystem/file/item.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/handler/topic.h"
#include "apex/platform/context.h"
#include "aura/graphics/image/list.h"
#include "aura/message/user.h"
#include "core/filesystem/filemanager/data.h"
#include "core/filesystem/filemanager/document.h"
#include "core/user/user/list_column.h"
#include "core/user/user/list_column_array.h"
#include "core/user/user/mesh_item.h"


namespace filemanager
{


   folder_list::folder_list()
   {


   }


   folder_list::~folder_list()
   {

   }


   void folder_list::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &folder_list::on_message_left_button_double_click);

//#ifdef WINDOWS_DESKTOP
//      MESSAGE_LINK(WM_CANCELMODE, pchannel, this, &folder_list::_001OnCancelMode);
//#endif

   }


//   void folder_list::assert_ok() const
//   {
//
//      ::user::impact::assert_ok();
//
//   }
//
//
//   void folder_list::dump(dump_context & dumpcontext) const
//   {
//
//      ::user::impact::dump(dumpcontext);
//
//   }



   void folder_list::on_message_left_button_double_click(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      index iItem;

      auto point = pmouse->m_pointHost;

      host_to_client()(point);

      if(_001HitTest_(point, iItem))
      {

         ::file::path filepathFinal = m_foldera.GetFolder((::index)iItem).m_strFolderPath;

         auto pcontext = get_context();

         ::file::path filepathUser = pcontext->m_papexcontext->defer_process_path(filepathFinal);

         auto pfileitem = __allocate< ::file::item >(filepathUser, filepathFinal);

         filemanager_document()->on_file_manager_open_folder(pfileitem, ::e_source_user);

      }

   }


   void folder_list::_001OnCancelMode(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      // trans   ::user::impact::OnCancelMode();

      // TODO: add your message handler code here

   }

   bool folder_list::pre_create_window(::user::system * pusersystem)
   {

#ifdef WINDOWS_DESKTOP

#endif

      return ::user::impact::pre_create_window(pusersystem);

   }


   void folder_list::on_insert_columns()
   {

      auto pcolumn = new_list_column();

      pcolumn->m_iWidth = 200;
      pcolumn->m_iSubItem = 1;
      pcolumn->m_bIcon = true;
      pcolumn->m_sizeIcon.cx() = 16;
      pcolumn->m_sizeIcon.cy() = 16;


   }


   void folder_list::_001GetSubItemText(::user::mesh_subitem * psubitem)
   {

      psubitem->m_strText = m_foldera.GetFolder((::index)psubitem->m_pitem->m_iItem).m_strName;

      psubitem->m_bOk = true;

   }


   void folder_list::browse_sync(const ::action_context & context)
   {

      string strParent = filemanager_item()->user_path();

      m_foldera.clear();

      Folder folder;

      ::file::listing listing;

      auto pcontext = m_pcontext;

      listing.set_listing(strParent);

      dir()->enumerate(listing);

      for (i32 i = 0; i < listing.get_count(); i++)
      {

         folder.m_strFolderPath = listing[i];

         folder.m_strName = listing[i].title();

         m_foldera.AddFolder(folder);

      }

      update_impact();

      auto pcolumn = m_pcolumna->get_by_subitem(1);

      _001CreateImageList(pcolumn);

   }


   void folder_list::_001CreateImageList(::user::list_column * pcolumn)
   {
      //   HRESULT hr;
      if (pcolumn->m_iSubItem == 1)
      {
         //      char szPath[MAX_PATH * 4];
         //      ::u32 uFlags;
         if (pcolumn->m_pimagelist == nullptr)
         {
            pcolumn->m_pimagelist = __allocate< ::image_list >();
         }
         ::pointer<::image_list>pil = pcolumn->m_pimagelist;
         //if(pil->GetSafeHandle() != nullptr)
         //pil->DeleteImageList();
         //if(pil->create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 1))
//#ifdef WINDOWS_DESKTOP
//         if (pil->create(16, 16, ILC_COLOR32, 0, 1))
//#else
         if (pil->create(16, 16, 0, 0, 1))
//#endif
         {

            string str;
            //::draw2d::icon * hicon = nullptr;
            //i32 iIndex;
            for (auto p = m_iconmap.begin(); p; p++)
            {
               delete p->m_element1;
            }
            m_iconmap.erase_all();
            //         i32 iIcon;
            //         i32 iImage;
            //         IExtractIcon * piextracticon;

            for (i32 i = 0; i < m_foldera.GetFolderCount(); i++)
            {
               /*            Folder & folder = m_foldera.GetFolder(i);
               if(FAILED(m_spshellfolder->GetUIObjectOf(
               GetSafeoswindow_(),
               1,
               (const ITEMIDLIST **) &folder.m_lpiidlRelative,
               IID_IExtractIcon,
               nullptr,
               (void **) &piextracticon)))

               {
               continue;
               }
               hr = piextracticon->GetIconLocation(

               0,
               szPath,
               sizeof(szPath),
               &iIcon,
               &uFlags);
               if(hr == S_OK)
               {
               HICON hicon = nullptr;
               HICON hiconLarge = nullptr;
               hr = piextracticon->Extract(

               szPath,
               iIcon,
               &hiconLarge,
               &hicon,
               0x00100000);
               if(hr == NOERROR)
               {
               if(!m_iconmap.lookup(hicon, iImage))
               {
               iImage = pil->add(hicon);
               m_iconmap.set_at(hicon, iImage);
               pil->add(hicon);
               }
               folder.m_iImage = iImage;
               }
               else if(hr == S_FALSE)
               {
               HICON hicon = ExtractIcon(
               psystem->m_hInstance,
               szPath,
               iIcon);*/
               /*HINSTANCE hinstance = (HINSTANCE) ::LoadLibrary(
               szPath);
               HICON hicon = (HICON) ::LoadImage(
               hinstance,
               MAKEINTRESOURCE(iIcon),
               IMAGE_ICON,
               16, 16,
               LR_CREATEDIBSECTION);
               if(!m_iconmap.lookup(hicon, iImage))
               {
               iImage = pil->add(hicon);
               m_iconmap.set_at(hicon, iImage);
               pil->add(hicon);
               }
               folder.m_iImage = iImage;
               }
               }
               else if(hr == S_FALSE)
               {
               // a default icon should be used
               }
               piextracticon->Release();*/

            }
         }
      }
      else
      {
         ::user::list::_001CreateImageList(pcolumn);
      }
   }


//#ifdef WINDOWS_DESKTOP
//   void folder_list::FolderArray::clear(LPITEMIDLIST piidlPreserve1, LPITEMIDLIST piidlPreserve2)
//
//   {
//      UNREFERENCED_PARAMETER(piidlPreserve1);
//
//      UNREFERENCED_PARAMETER(piidlPreserve2);
//
//      //Folder folder;
//
//
//      //for(i32 i = 0; i < this->get_size(); i++)
//      //{
//      //Folder & folder = this->element_at(i);
//      //}
//      erase_all();
//
//
//   }
//
//#endif

   void folder_list::FolderArray::clear()
   {

      erase_all();

   }

   folder_list::Folder &
   folder_list::FolderArray::GetFolder(index i)
   {
      return this->element_at(i);
   }

   ::count folder_list::FolderArray::GetFolderCount()
   {
      return this->get_size();
   }

   
   void folder_list::FolderArray::AddFolder(Folder &folder)
   {
      
      add(folder);

   }


   void folder_list::_001GetSubItemImage(::user::mesh_subitem * psubitem)
   {

      if (psubitem->m_iSubItem == 1)
      {

         psubitem->m_iImage = m_foldera.GetFolder((::index)psubitem->m_pitem->m_iItem).m_iImage;

         psubitem->m_bOk = true;

      }
      else
      {

         ::user::list::_001GetSubItemImage(psubitem);

      }

   }


   ::file::item * folder_list::filemanager_item()
   {

      return filemanager_document()->filemanager_item();

   }


   ::count folder_list::_001GetItemCount()
   {

      return m_foldera.GetFolderCount();

   }


   ::color::color folder_list::get_background_color()
   {

      if (filemanager_data()->is_topic())
      {

         ::color32_t color32 = ::color::transparent;

         if (filemanager_data()->m_emode == ::userfs::e_mode_saving)
         {

            color32 = argb(190, 255, 180, 90);

         }
         else if (filemanager_data()->m_emode == ::userfs::e_mode_import)
         {

            color32 = argb(190, 90, 177, 255);

         }
         else if (filemanager_data()->m_emode == ::userfs::e_mode_export)
         {

            color32 = argb(190, 255, 255, 177);

         }
         else if (filemanager_data()->m_emode == ::userfs::e_mode_import)
         {

            color32 = argb(190, 180, 255, 90);

         }

         return color32;

      }
      else
      {

         return rgb(200, 255, 255);

      }

   }



   void folder_list::handle(::topic * ptopic, ::context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, pcontext);

      if (ptopic->m_atom == ID_INITIALIZE)
      {

         if (filemanager_data()->m_bPassBk)
         {

            ::user::list::m_bBackgroundBypass = true;

         }

         set_pending_column_update();

      }

   }


} // namespace filemanager



