#include "framework.h"
#include "document.h"
#include "item.h"
#include "tree_data.h"
#include "core/user/user/tree.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/topic.h"
#include "acme/platform/application.h"
#include "acme/platform/session.h"
#include "acme/platform/timer.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/prototype/data/listener.h"
#include "aura/user/user/interaction.h"
#include "base/user/user/impact.h"
#include "core/user/user/tree_data.h"


namespace userfs
{


   tree_data::tree_data()
   {

      m_iAnimate = 0;

   }


   tree_data::~tree_data()
   {

   }


   void tree_data::destroy()
   {

      ::user::tree_data<::userfs::item>::destroy();
      ::channel::destroy();

   }


   // ::core::application* tree_data::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::core::session* tree_data::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::core::system* tree_data::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }


#ifdef _DEBUG

   long long tree_data::increment_reference_count()
   {

      return ::user::tree_data<::userfs::item>::increment_reference_count();
//      auto c = m_countReference++;
//
//#if REFERENCING_DEBUGGING
//
//      add_ref_history(pReferer, pszObjRefDbg);
//
//#endif
//
//      return c;

   }


   long long tree_data::decrement_reference_count()
   {

//      auto c = m_countReference--;
//
//#if REFERENCING_DEBUGGING
//
//      if (c > 0)
//      {
//
//         dec_ref_history(pReferer, pszObjRefDbg);
//
//      }
//
//#endif

      return ::user::tree_data<::userfs::item>::decrement_reference_count();

   }


   long long tree_data::release()
   {

      long long i = decrement_reference_count();

      if (i == 0)
      {

         delete_this();

      }

      return i;

   }


#endif


//   void tree_data::assert_ok() const
//   {
//
//   }
//
//
//   void tree_data::dump(dump_context &) const
//   {
//   }



   void tree_data::install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(e_message_create, pchannel, this, &tree_data::on_message_create);
      MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &tree_data::on_message_left_button_double_click);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &tree_data::on_message_context_menu);

   }




   void tree_data::on_message_left_button_double_click(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }

   void tree_data::on_message_context_menu(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);
//      ::pointer<::message::context_menu>pcontextmenu(pmessage);
      //   int iItem;
      //   HRESULT hr;
//         auto point = pcontextmenu->GetPoint();
//      ::user::tree_data::screen_to_client(&point);
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
         (::windowing::window *) pframe);
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
         (::windowing::window *) pframe);
         }
         }*/
   }


   void tree_data::on_timer(::timer * ptimer)
   {

      if (ptimer->m_uTimer == 1234567)
      {
         
         m_iAnimate += 2;
         
         if (m_iAnimate >= 11)
         {
            
            m_iAnimate = 0;

            ptimer->m_ptimercallback->erase_timer(ptimer);

         }
         
         ptimer->m_ptimercallback->get_user_interaction()->set_need_redraw();

      }
      else if (ptimer->m_uTimer == 123)
      {
         
         ptimer->m_ptimercallback->get_user_interaction()->set_need_redraw();
         
         m_bTimer123 = false;
         
         ptimer->m_ptimercallback->erase_timer(ptimer);

      }

   }


   void tree_data::StartAnimation(::user::interaction * pinteraction)
   {
      
      m_iAnimate = 1;
      
      pinteraction->set_timer(1234567, 50_ms, nullptr);

   }


   void tree_data::_001OnShellCommand(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   //void tree_data::_017OpenFolder(::pointer<::file::item>pitem, const ::action_context & context)
   //{

   //   m_puserfsdocument->browse(pitem, context);

   //}


   void tree_data::on_message_create(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }




   void tree_data::update_list()
   {

   }


   void tree_data::browse_sync(const ::action_context & context)
   {


   }


   void tree_data::_017EnsureVisible(const ::file::path & path, const ::action_context & context)
   {

   }


   ::data::tree_item<::userfs::item> * tree_data::find_item_by_user_path(const::file::path & pathUser, bool bPathFromItemFromOwnTree, ::data::tree_item<::userfs::item> * pitemStart)
   {

      return find_user_path(pathUser, bPathFromItemFromOwnTree, pitemStart);

   }


   void tree_data::on_insert_columns()
   {

      /*::user::form_control control;

      control.set_type(::user::form_control_type_edit);
      control.m_iKey = FILE_MANAGER_ID_FILE_NAME;
      pinteraction->id() = FILE_MANAGER_ID_FILE_NAME;
      control.set_data_type(::user::form_control_data_type_string);

      int iControl =  _001AddControl(control);

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

   void tree_data::GetSelectedFilePath(string_array & stra)
   {

      ::data::tree_item_ptr_array<::userfs::item> itemptraSelected;

      get_selection(itemptraSelected);

      for (int i = 0; i < itemptraSelected.get_size(); i++)
      {

         stra.add(itemptraSelected[0]->m_pitem.cast < ::userfs::item >()->user_path());

      }

   }


   void tree_data::TakeAnimationSnapshot()
   {
      m_iAnimate = 1;
      //   ::user::tree_data::_001OnDraw(m_gimageuffer.GetBuffer());
   }


   /*   IShellFolder * tree_data::_001GetFolder(EFolder efolder)
   {
   IShellFolder * psf;

   if(m_mapFolder.lookup(efolder, psf))
   {
   return psf;
   }
   else
   {
   int iCSIDL = MapToCSIDL(efolder);

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

   /*   int tree_data::MapToCSIDL(EFolder efolder)
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

   void tree_data::_001OnItemExpand(::data::tree_item_base * ptreeitembase, const ::action_context & context)
   {
      __UNREFERENCED_PARAMETER(ptreeitembase);
      __UNREFERENCED_PARAMETER(context);
   }

   void tree_data::_001OnItemCollapse(::data::tree_item_base * ptreeitembase, const ::action_context & context)
   {
      __UNREFERENCED_PARAMETER(ptreeitembase);
      __UNREFERENCED_PARAMETER(context);
   }

   bool tree_data::_001IsTranslucent()
   {
      return true;
   }

   void tree_data::_001OnOpenItem(::data::tree_item_base * ptreeitembase, const ::action_context & context)
   {

      auto pitem = __allocate ::file::item(*dynamic_cast < ::userfs::item*>(ptreeitembase->_item()));

      m_puserfsdocument->browse(pitem, context);

   }


   ::color::color tree_data::get_background_color()
   {
      
      if (m_puserfsdocument == nullptr)
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

   ::data::tree_item<::userfs::item> * tree_data::find_absolute(const ::file::path & path, bool bPointerFromPathFromItemFromOwnTree, ::data::tree_item<::userfs::item> * pitemStart)
   {

      ::data::tree_item<::userfs::item> * pitem;

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

         if (pitem->m_pitem)
         {

            ::userfs::item * puserfsitem = pitem->m_pitem.cast < ::userfs::item >();

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


   ::data::tree_item<::userfs::item> * tree_data::find_user_path(const ::file::path & pathUser, bool bPointerFromPathFromItemFromOwnTree, ::data::tree_item<::userfs::item> * pitemStart)
   {

      ::data::tree_item<::userfs::item> * pitem;

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

         if (pitem->m_pitem)
         {

            ::userfs::item * puserfsitem = pitem->m_pitem.cast < ::userfs::item >();

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


   void tree_data::arrange(::fs::e_arrange earrange)
   {

      //if (earrange == ::fs::arrange_by_name)
      {
         //sort(item::CompareArrangeByName);
      }

   }


   //::userfs::document * tree_data::get_document()
   //{

   //   return  dynamic_cast < ::userfs::document * > (get_data_container());

   //}



   void tree_data::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ////__update(::update)
      {

         if (ptopic->id() == id_initialize)
         {

         }
         if (ptopic->id() == id_filter)
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



