#include "framework.h"
#include "aura/graphics/image/list.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif


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


   void folder_list::assert_ok() const
   {

      ::user::impact::assert_ok();

   }


   void folder_list::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }



   void folder_list::on_message_left_button_double_click(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      index iItem;

      if(_001HitTest_(pmouse->m_point, iItem))
      {

         ::file::path filepathFinal = m_foldera.GetFolder((::index)iItem).m_strFolderPath;

         auto pcontext = get_context();

         ::file::path filepathUser = pcontext->m_papexcontext->defer_process_path(filepathFinal);

         auto pfileitem = __new(::file::item(filepathUser, filepathFinal));

         filemanager_document()->on_file_manager_open_folder(pfileitem, ::e_source_user);

      }

   }

   void folder_list::_001OnCancelMode(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      // trans   ::user::impact::OnCancelMode();

      // TODO: add your message handler code here

   }

   bool folder_list::pre_create_window(::user::system * pusersystem)
   {

#ifdef WINDOWS_DESKTOP

#endif

      return ::user::impact::pre_create_window(pusersystem);

   }


   void folder_list::_001InsertColumns()
   {

      auto pcolumn = new_list_column();

      pcolumn->m_iWidth = 200;
      pcolumn->m_iSubItem = 1;
      pcolumn->m_bIcon = true;
      pcolumn->m_sizeIcon.cx = 16;
      pcolumn->m_sizeIcon.cy = 16;


   }


   void folder_list::_001GetItemText(::user::mesh_item * pitem)
   {

      pitem->m_strText = m_foldera.GetFolder((::index) pitem->m_iItem).m_strName;

      pitem->m_bOk = true;

   }


   void folder_list::browse_sync(const ::action_context & context)
   {

      string strParent = filemanager_item()->m_filepathUser;

      m_foldera.clear();

      Folder folder;

      ::file::listing patha;

      auto pcontext = m_pcontext;

      pcontext->m_papexcontext->dir().ls(patha, strParent);

      for (i32 i = 0; i < patha.get_count(); i++)
      {

         folder.m_strFolderPath = patha[i];

         folder.m_strName = patha[i].title();

         m_foldera.AddFolder(folder);

      }

      _001OnUpdateItemCount();

      ::user::list_column * pcolumn = m_columna.get_by_subitem(1);

      _001CreateImageList(pcolumn);

   }


   void folder_list::_001CreateImageList(::user::list_column * pcolumn)
   {
      //   HRESULT hr;
      if (pcolumn->m_iSubItem == 1)
      {
         //      char szPath[MAX_PATH * 4];
         //      ::u32 uFlags;
         if (pcolumn->m_pil == nullptr)
         {
            pcolumn->m_pil = __new(::image_list);
         }
         __pointer(::image_list) pil = pcolumn->m_pil;
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
//      __UNREFERENCED_PARAMETER(piidlPreserve1);
//
//      __UNREFERENCED_PARAMETER(piidlPreserve2);
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

   void folder_list::_001GetItemImage(::user::mesh_item * pitem)
   {
      if (pitem->m_iSubItem == 1)
      {
         pitem->m_iImage = m_foldera.GetFolder((::index) pitem->m_iItem).m_iImage;
         pitem->m_bOk = true;
      }
      else
      {
         ::user::list::_001GetItemImage(pitem);
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

         ::color32_t color32 = 0;

         if (filemanager_document()->m_emode == ::userfs::mode_saving)
         {

            color32 = argb(190, 255, 180, 90);

         }
         else if (filemanager_document()->m_emode == ::userfs::mode_import)
         {

            color32 = argb(190, 90, 177, 255);

         }
         else if (filemanager_document()->m_emode == ::userfs::mode_export)
         {

            color32 = argb(190, 255, 255, 177);

         }
         else if (filemanager_document()->m_emode == ::userfs::mode_import)
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

      if (ptopic->m_atom == INITIALIZE_ID)
      {

         if (filemanager_data()->m_bPassBk)
         {

            ::user::list::m_bBackgroundBypass = true;

         }

         _001UpdateColumns();

      }

   }


} // namespace filemanager



