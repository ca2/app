#include "framework.h"
//#include "_filemanager.h"


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

      IGUI_MSG_LINK(WM_LBUTTONDBLCLK, pchannel, this, &folder_list::_001OnLButtonDblClk);

      IGUI_MSG_LINK(WM_CANCELMODE, pchannel, this, &folder_list::_001OnCancelMode);

   }


   void folder_list::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void folder_list::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }



   void folder_list::_001OnLButtonDblClk(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      index iItem;

      if(_001HitTest_(pmouse->m_point, iItem))
      {

         filemanager_document()->on_file_manager_open_folder(__new(::file::item(
               Context.defer_process_path(m_foldera.GetFolder((::index)iItem).m_strFolderPath),
               m_foldera.GetFolder((::index) iItem).m_strFolderPath)), ::source_user);

      }

   }

   void folder_list::_001OnCancelMode(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      // trans   ::user::impact::OnCancelMode();

      // TODO: add your message handler code here

   }

   bool folder_list::pre_create_window(::user::create_struct& cs)
   {

      cs.style |= WS_CLIPCHILDREN;

      return ::user::impact::pre_create_window(cs);
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

      //      m_foldera.clear(nullptr, nullptr);

      Folder folder;


      ::file::listing patha(get_context());

      patha.ls(strParent);

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
         //      UINT uiFlags;
         if (pcolumn->m_pil == nullptr)
         {
            pcolumn->m_pil = __new(image_list);
         }
         __pointer(image_list) pil = pcolumn->m_pil;
         //if(pil->GetSafeHandle() != nullptr)
         //pil->DeleteImageList();
         //if(pil->create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 1))
#ifdef WINDOWS_DESKTOP
         if (pil->create(16, 16, ILC_COLOR32, 0, 1))
#else
         if (pil->create(16, 16, 0, 0, 1))
#endif
         {

            string str;
            //::draw2d::icon * hicon = nullptr;
            //i32 iIndex;
            for (auto p = m_iconmap.begin(); p; p++)
            {
               delete p->m_element1;
            }
            m_iconmap.remove_all();
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
               &uiFlags);
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
               System.m_hInstance,
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


#ifdef WINDOWS_DESKTOP
   void folder_list::FolderArray::clear(LPITEMIDLIST piidlPreserve1, LPITEMIDLIST piidlPreserve2)

   {
      UNREFERENCED_PARAMETER(piidlPreserve1);

      UNREFERENCED_PARAMETER(piidlPreserve2);

      //Folder folder;


      //for(i32 i = 0; i < this->get_size(); i++)
      //{
      //Folder & folder = this->element_at(i);
      //}
      remove_all();


   }

#endif

   void folder_list::FolderArray::clear()
   {

      remove_all();

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


   COLORREF folder_list::get_background_color()
   {

      if (filemanager_data()->is_topic())
      {

         COLORREF cr = 0;

         if (filemanager_document()->m_emode == ::userfs::mode_saving)
         {

            cr = ARGB(190, 255, 180, 90);

         }
         else if (filemanager_document()->m_emode == ::userfs::mode_import)
         {

            cr = ARGB(190, 90, 177, 255);

         }
         else if (filemanager_document()->m_emode == ::userfs::mode_export)
         {

            cr = ARGB(190, 255, 255, 177);

         }
         else if (filemanager_document()->m_emode == ::userfs::mode_import)
         {

            cr = ARGB(190, 180, 255, 90);

         }

         return cr;

      }
      else
      {

         return RGB(200, 255, 255);

      }

   }



   void folder_list::update(::update * pupdate)
   {

      ::filemanager::impact::update(pupdate);

      if (pupdate->m_id == INITIALIZE_ID)
      {

         if (filemanager_data()->m_bPassBk)
         {

            ::user::list::m_bBackgroundBypass = true;

         }

         _001UpdateColumns();

      }

   }


} // namespace filemanager



