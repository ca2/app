#include "framework.h"
#include "tree.h"
#include "document.h"
#include "item.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/platform/application.h"
#include "acme/platform/session.h"
#include "acme/platform/timer.h"
#include "acme/platform/context.h"
#include "acme/platform/system.h"
#include "acme/primitive/data/listener.h"
#include "aura/user/user/interaction.h"
#include "base/user/user/impact.h"
#include "core/user/user/tree.h"


namespace userfs
{


   tree::tree()
   {

      m_iAnimate = 0;

   }


   tree::~tree()
   {

   }


   ::core::application* tree::get_app()
   {

      auto pacmeapplication = acmeapplication();

      return ::is_set(pacmeapplication) ? pacmeapplication->m_pcoreapplication : nullptr;

   }


   ::core::session* tree::get_session()
   {

      auto pacmesession = acmesession();

      return ::is_set(pacmesession) ? pacmesession->m_pcoresession : nullptr;

   }


   ::core::system* tree::get_system()
   {

      auto pacmesystem = acmesystem();

      return ::is_set(pacmesystem) ? pacmesystem->m_pcoresystem : nullptr;

   }


#ifdef _DEBUG

   i64 tree::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      auto c = m_countReference++;

#if OBJECT_REFERENCE_COUNT_DEBUG

      add_ref_history(pReferer, pszObjRefDbg);

#endif

      return c;

   }


   i64 tree::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      auto c = m_countReference--;

#if OBJECT_REFERENCE_COUNT_DEBUG

      if (c > 0)
      {

         dec_ref_history(pReferer, pszObjRefDbg);

      }

#endif

      return c;

   }


   i64 tree::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      i64 i = decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      if (i == 0)
      {

         delete_this();

      }

      return i;

   }


#endif


//   void tree::assert_ok() const
//   {
//
//   }
//
//
//   void tree::dump(dump_context &) const
//   {
//   }



   void tree::install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &tree::on_message_create);
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &tree::on_message_left_button_double_click);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &tree::on_message_context_menu);

   }




   void tree::on_message_left_button_double_click(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }

   void tree::on_message_context_menu(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);
//      ::pointer<::message::context_menu>pcontextmenu(pmessage);
      //   i32 iItem;
      //   HRESULT hr;
//         auto point = pcontextmenu->GetPoint();
//      ::user::tree::screen_to_client(&point);
      /*     if(_001HitTest_(point, iItem))
         {
         CSimpleMenu menu(CBaseMenuCentral::GetMenuCentral());
         if (menu.LoadMenu(get_filemanager_template()->get_filemanager_template()->m_uiFilePopup))
         {
         CSimpleMenu* pPopup = (CSimpleMenu *) menu.GetSubMenu(0);
         ASSERT(pPopup != nullptr);
         ::pointer<::user::frame_window>pframe = top_level_frame();

         pframe->set_active_impact(this);

         //IContextMenu * pcontextmenu;

         hr = m_spshellfolder->GetUIObjectOf(
         nullptr,
         1,
         (LPCITEMIDLIST *) &m_itema.get_item(iItem).m_lpiidlRelative,
         IID_IContextMenu,
         nullptr,
         (void **) &m_contextmenu.m_pcontextmenu);


         if(SUCCEEDED(hr))
         {
         hr = m_contextmenu.m_pcontextmenu->QueryContextMenu(
         pPopup->GetSafeHmenu(),
         0,
         SHELL_COMMAND_FIRST,
         SHELL_COMMAND_LAST,
         CMF_NORMAL);

         }


         pPopup->track_popup_menu(
         point.x(), point.y(),
         (::user::interaction_impl *) pframe);
         }
         }
         else
         {
         ::user::menu menu;
         if (menu.LoadMenu(get_filemanager_template()->get_filemanager_template()->m_uiPopup))
         {
         ::user::menu* pPopup = menu.GetSubMenu(0);
         ASSERT(pPopup != nullptr);
         ::pointer<::user::frame_window>pframe = top_level_frame();
         pPopup->track_popup_menu(
         point.x(), point.y(),
         (::user::interaction_impl *) pframe);
         }
         }*/
   }


   void tree::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_uEvent == 1234567)
      {
         
         m_iAnimate += 2;
         
         if (m_iAnimate >= 11)
         {
            
            m_iAnimate = 0;

            ptimer->m_ptimercallback->erase_timer(ptimer);

         }
         
         ptimer->m_ptimercallback->get_user_interaction()->set_need_redraw();

      }
      else if (ptimer->m_uEvent == 123)
      {
         
         ptimer->m_ptimercallback->get_user_interaction()->set_need_redraw();
         
         m_bTimer123 = false;
         
         ptimer->m_ptimercallback->erase_timer(ptimer);

      }

   }


   void tree::StartAnimation(::user::interaction * pinteraction)
   {
      
      m_iAnimate = 1;
      
      pinteraction->SetTimer(1234567, 50_ms, nullptr);

   }


   void tree::_001OnShellCommand(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void tree::_017OpenFolder(::pointer<::file::item>pitem, const ::action_context & context)
   {

      get_document()->browse(pitem, context);

   }


   void tree::on_message_create(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }




   void tree::update_list()
   {

   }


   void tree::browse_sync(const ::action_context & context)
   {


   }


   void tree::_017EnsureVisible(const ::file::path & path, const ::action_context & context)
   {

   }


   ::data::tree_item * tree::find_item_by_user_path(const::file::path & pathUser, bool bPathFromItemFromOwnTree, ::data::tree_item * pitemStart)
   {

      return find_user_path(pathUser, bPathFromItemFromOwnTree, pitemStart);

   }


   void tree::on_insert_columns()
   {

      /*::user::form_control control;

      control.set_type(::user::form_control_type_edit);
      control.m_iKey = FILE_MANAGER_ID_FILE_NAME;
      pinteraction->m_atom = FILE_MANAGER_ID_FILE_NAME;
      control.set_data_type(::user::form_control_data_type_string);

      i32 iControl =  _001AddControl(control);

      CColumn column;

      pcolumn->m_iWidth               = 500;
      pcolumn->m_iSubItem             = 1;
      pcolumn->m_bIcon                = true;
      pcolumn->m_sizeIcon.cx()          = 16;
      pcolumn->m_sizeIcon.cy()          = 16;
      pcolumn->m_iControl             = iControl;
      pcolumn->m_iConfigId            = FILE_MANAGER_ID_FILE_NAME;
      pcolumn->m_bEditOnSecondClick   = true;
      */

   }

   void tree::GetSelectedFilePath(string_array & stra)
   {

      ::data::tree_item_ptr_array itemptraSelected;

      get_selection(itemptraSelected);

      for (i32 i = 0; i < itemptraSelected.get_size(); i++)
      {

         stra.add(itemptraSelected[0]->m_pdataitem.cast < ::userfs::item >()->user_path());

      }

   }


   void tree::TakeAnimationSnapshot()
   {
      m_iAnimate = 1;
      //   ::user::tree::_001OnDraw(m_gimageuffer.GetBuffer());
   }


   /*   IShellFolder * tree::_001GetFolder(EFolder efolder)
   {
   IShellFolder * psf;

   if(m_mapFolder.lookup(efolder, psf))
   {
   return psf;
   }
   else
   {
   i32 iCSIDL = MapToCSIDL(efolder);

   ASSERT(iCSIDL >= 0);

   if(iCSIDL < 0)
   return nullptr;

   IShellFolder * psfDesktop = nullptr;
   HRESULT hr = SHGetDesktopFolder(&psfDesktop);
   LPITEMIDLIST pidl;


   hr = SHGetSpecialFolderLocation(
   nullptr,
   iCSIDL,
   &pidl);


   if(FAILED(hr))
   return nullptr;

   hr = psfDesktop->BindToObject(
   pidl,

   nullptr,
   IID_IShellFolder,
   (void **) &psf);

   if(FAILED(hr))
   return nullptr;

   m_mapFolder.set_at(efolder, psf);

   psf->AddRef();
   psfDesktop->Release();
   return psf;
   }
   }*/

   /*   i32 tree::MapToCSIDL(EFolder efolder)
   {
   switch(efolder)
   {
   case FolderMyComputer:
   return CSIDL_DRIVES;
   default:
   return -1;
   }
   }
   */

   void tree::_001OnItemExpand(::data::tree_item * pitem, const ::action_context & context)
   {
   }

   void tree::_001OnItemCollapse(::data::tree_item * pitem, const ::action_context & context)
   {
      UNREFERENCED_PARAMETER(pitem);
   }

   bool tree::_001IsTranslucent()
   {
      return true;
   }

   void tree::_001OnOpenItem(::data::tree_item * pitem, const ::action_context & context)
   {

      _017OpenFolder(__new(::file::item(*pitem->m_pdataitem.cast < ::userfs::item >())), context);

   }





   ::color::color tree::get_background_color()
   {
      if (get_document() == nullptr)
      {
         return rgb(200, 255, 255);
      }
      /*      else if(get_filemanager_template()->get_filemanager_data()->is_saving())
      {
      return rgb(255, 180, 90);
      }*/
      else
      {
         return rgb(200, 255, 255);
      }
   }

   ::data::tree_item * tree::find_absolute(const ::file::path & path, bool bPointerFromPathFromItemFromOwnTree, ::data::tree_item * pitemStart)
   {

      ::data::tree_item * pitem;

      if (pitemStart == nullptr)
      {

         pitem = get_base_item();

      }
      else
      {

         pitem = pitemStart;

      }

      if (path.is_empty())
      {

         return nullptr;

      }

      while (pitem != nullptr)
      {

         if (pitem->m_pdataitem)
         {

            ::userfs::item * puserfsitem = pitem->m_pdataitem.cast < ::userfs::item >();

            if (puserfsitem != nullptr)
            {

               auto & pathTreeItem = puserfsitem->final_path();

               if (bPointerFromPathFromItemFromOwnTree)
               {

                  if (&pathTreeItem == &path)
                  {

                     return pitem;

                  }

               }
               else
               {

                  if (pathTreeItem == path)
                  {

                     return pitem;

                  }

               }

            }

         }

         pitem = pitem->get_child_next_or_parent();

         if (pitem == pitemStart)
         {

            break;

         }

      }

      return nullptr;

   }


   ::data::tree_item * tree::find_user_path(const ::file::path & pathUser, bool bPointerFromPathFromItemFromOwnTree, ::data::tree_item * pitemStart)
   {

      ::data::tree_item * pitem;

      if (pitemStart == nullptr)
      {

         pitem = get_base_item();

      }
      else
      {

         pitem = pitemStart;

      }

      if (pathUser.is_empty())
      {

         return nullptr;

      }

      while (pitem != nullptr)
      {

         if (pitem->m_pdataitem)
         {

            ::userfs::item * puserfsitem = pitem->m_pdataitem.cast < ::userfs::item >();

            if (puserfsitem != nullptr)
            {

               auto & pathTreeItem = puserfsitem->user_path();

               if (bPointerFromPathFromItemFromOwnTree)
               {

                  if (&pathTreeItem == &pathUser)
                  {

                     return pitem;

                  }

               }
               else
               {

                  if (pathTreeItem == pathUser)
                  {

                     return pitem;

                  }
                  else if(pathTreeItem.case_insensitive_ends("://")
                     && pathUser.length() <= pathTreeItem.length()
                     && pathUser.begins(pathTreeItem(0, pathTreeItem.length() - 3)))
                  {

                     return pitem;

                  }

               }

            }

         }

         pitem = pitem->get_child_next_or_parent();

         if (pitem == pitemStart)
         {

            break;

         }

      }

      return nullptr;

   }


   void tree::arrange(::fs::e_arrange earrange)
   {

      //if (earrange == ::fs::arrange_by_name)
      {
         //sort(item::CompareArrangeByName);
      }

   }


   ::userfs::document * tree::get_document()
   {

      return  dynamic_cast < ::userfs::document * > (get_data_container());

   }



   void tree::handle(::topic * ptopic, ::context * pcontext)
   {

      ////__update(::update)
      {

         if (ptopic->m_atom == id_initialize)
         {

         }
         if (ptopic->m_atom == id_filter)
         {

            if (ptopic->payload(id_filter).is_empty())
            {
               //               FilterClose();
            }
            else
            {
               //             FilterBegin();
               //           Filter1(ptopic->payload(id_filter));
               //         FilterApply();
            }

         }

      }

   }




} // namespace userfs



