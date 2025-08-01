#include "framework.h"
#include "group_image_list.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "aura/graphics/image/context.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/user/user/content.h"
#include "aura/message/user.h"
#include "aura/platform/context.h"
#include "base/user/menu/button.h"
#include "base/user/menu/item.h"
#include "base/user/menu/item_ptra.h"
#include "base/user/menu/menu.h"
#include "base/user/user/user.h"


namespace userex
{


   group_image_list_impact::group_image_list_impact()
   {

      m_size.cx() = 7;
      m_size.cy() = 5;


   }


   group_image_list_impact::~group_image_list_impact()
   {

   }





   //void group_image_list_impact::assert_ok() const
   //{

   //   ::user::impact::assert_ok();

   //}


   //void group_image_list_impact::dump(dump_context & dumpcontext) const
   //{

   //   ::user::impact::dump(dumpcontext);

   //}


   void group_image_list_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::impact::handle(ptopic, phandlercontext);

      if (ptopic->id() == ::id_item_clicked)
      {


      }
      else if (ptopic->id() == ::id_click)
      {

         if (ptopic->user_interaction()->id() == id())
         {

            show_menu();

         }

      }

      return ::user::impact::handle(ptopic, phandlercontext);


   }

   void group_image_list_impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &group_image_list_impact::on_message_create);


   }


   ::userex::image_list_impact * group_image_list_impact::add_group(::atom idGroup, const ::scoped_string & scopedstrIcon, const ::scoped_string & scopedstrTitle, ::file::path pathFolder)
   {

      ::pointer<group>pgroup = __allocate group();

      pgroup->m_iIndex = m_groupa.get_size();

      pgroup->m_atomGroup = idGroup;

      pgroup->m_strIcon = scopedstrIcon;

      pgroup->m_strTitle = scopedstrTitle;

      m_atomaHandledCommands.add("menu_item_" + idGroup);

      m_groupa.add(pgroup);

      auto * plist = get_group_list(idGroup);

      plist->m_iIndex = m_groupa.get_upper_bound();

      if (pathFolder.has_character())
      {

         plist->m_pathFolder = pathFolder;

         plist->update_data(false);

      }

      return plist;

   }


   void group_image_list_impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);


      m_pimage = image()->load_image("project.jpg", { .cache = false });

      pcreate->previous();

      m_atomaHandledCommands.add(id());

      __construct_new(m_pbuttonMenu);

      m_pbuttonMenu->create_control(this, id());

      m_pbuttonMenu->set_button_style(::user::button::e_style_image_and_text);

      //m_pbuttonMenu->create_color(::user::color_button_text, argb(255, 80, 80, 80));
      //m_pbuttonMenu->create_color(::user::color_button_background, argb(255, 255, 255, 255));
      //m_pbuttonMenu->create_int(::user::int_button_draw_text_and_image_flags, e_align_left_center | DT_SINGLELINE);

      m_pbuttonMenu->m_flagNonClient.erase(::user::interaction::e_non_client_focus_rect);

   }


   group_image_list_impact::group * group_image_list_impact::get_group(::atom idGroup)
   {

      auto iFind = m_groupa.predicate_find_first([=](auto & item)
      {

         return item->m_atomGroup == idGroup;

      });

      if (::not_found(iFind))
      {

         return nullptr;

      }

      return m_groupa[iFind];

   }


   string group_image_list_impact::get_group_title(group * pgroup)
   {

      ASSERT(pgroup != nullptr);

      if (pgroup->m_strTitle.has_character())
      {

         return pgroup->m_strTitle;

      }

      return pgroup->m_atomGroup;


   }


   ::file::path group_image_list_impact::get_link_path(const ::scoped_string & scopedstrLink)
   {

      ::file::path path;

      for (auto & group : m_groupa)
      {

         path = group->m_plist->get_link_path(scopedstrLink);

         if (path.has_character())
         {

            break;

         }

      }

      return path;

   }


   ::userex::image_list_impact * group_image_list_impact::get_group_list(::atom idGroup)
   {

      ::pointer<group>pgroup = get_group(idGroup);

      if (pgroup.is_null())
      {

         return nullptr;

      }

      auto & plist = pgroup->m_plist;

      if (plist.is_null())
      {

         plist = create_impact < ::userex::image_list_impact >(nullptr, nullptr, idGroup);

         plist->m_ealign = e_align_top_center;

         plist->m_bMultiSel = false;

      }

      return plist;

   }


   void group_image_list_impact::set_current_item(::item * pitem, const ::action_context & context)
   {

      //auto estatus = 
      
      ::user::impact::set_current_item(pitem, context);

      //if(estatus != success)
      //{

      //   return estatus;

      //}

      auto pgroup = m_groupa[pitem->m_item.m_iItem];

      if (!pgroup)
      {

         throw ::exception(error_not_found);

      }

      show_group(pgroup->m_atomGroup);

      //auto * plist = get_group_list(strGroup);

     //::image::image_pointer pimage = papp->matter_image(pgroup->m_strIcon);

      //m_pbuttonMenu->set_window_text(get_group_title(pgroup));

      //m_pbuttonMenu->LoadBitmaps(pimage);

      //if (pathFolder.has_character())
      //{

      //   plist->m_pathFolder = pathFolder;

      //   plist->update_data(false);

      //}

 /*     m_strGroup = strGroup;

      set_need_layout();

      set_need_redraw();*/

      //return ::success;

   }


   bool group_image_list_impact::show_group(::atom idGroup, ::file::path pathFolder)
   {

      ::pointer<group>pgroup = get_group(idGroup);

      if (pgroup.is_null())
      {

         return false;

      }

      auto * plist = get_group_list(idGroup);

      main_content().m_pitemCurrent = main_content().defer_item(::e_element_item, plist->m_iIndex);


      ::image::image_pointer pimage = image()->matter_image(pgroup->m_strIcon);

      m_pbuttonMenu->set_window_text(get_group_title(pgroup));

      m_pbuttonMenu->LoadBitmaps(pimage);

      if (pathFolder.has_character())
      {

         plist->m_pathFolder = pathFolder;

         plist->update_data(false);

      }

      m_atomGroup = idGroup;

      set_need_layout();

      set_need_redraw();

      return true;

   }


   void group_image_list_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::impact::_001OnNcDraw(pgraphics);

   }


   void group_image_list_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::impact::_001OnDraw(pgraphics);

   }


   //void group_image_list_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //   if (ptopic->id() == ::id_item_clicked)
   //   {


   //   }
   //   else if (ptopic->id() == ::id_click)
   //   {

   //      if (ptopic->user_interaction()->id() == id())
   //      {

   //         show_menu();

   //      }

   //   }

   //   return ::user::impact::handle(ptopic, phandlercontext);

   //}


   string group_image_list_impact::get_menu_xml()
   {

      string str;

      str = "<menubar title = \""+string(id())+"\" close_button=\"false\">";

      for (auto & pgroup : m_groupa)
      {

         str += "<item id=\"menu_item_";
         str += pgroup->m_atomGroup;
         str += "\" pimage =\"";
         str += pgroup->m_strIcon;
         str += "\">";
         str += get_group_title(pgroup);
         str += "</item>";

      }

      str += "</menubar>";

      return str;

   }


   void group_image_list_impact::show_menu()
   {

      string strXml(get_menu_xml());

      ::user::interaction * pinteraction = m_pbuttonMenu;

      ::int_rectangle rectangleWindow;

      pinteraction->window_rectangle(rectangleWindow);
      
      auto puser = user();
      
      auto pmenuSource = puser->menu_from_xml(this, strXml);
      
      auto ptrackpopup = ___new ::menu::track_popup(
                                                     pmenuSource,
                                                     this,
                                                     this,
                                                     mouse_cursor_position(),
                                                     rectangleWindow);
      
      ::pointer < ::user::menu > pmenu = ptrackpopup;
      
      pmenu->set_minimum_width(width());
      
      ptrackpopup->track([](){});
      

//      m_pmenu = puser->track_popup_menu(this, strXml, 0, rectangleWindow.bottom_left(), ::int_size(width(), 0));
      //m_pmenu->create_color(::user::color_button_background, argb(255, 255, 255, 255));
      //m_pmenu->create_color(::user::color_button_text, argb(255, 80, 80, 80));

      ::collection::index i = 0;

      auto pitemCurrent = current_item();

      for (auto & item : *m_pmenu->m_pmenuitem->m_pmenuitema)
      {

         ::pointer<::user::menu_button>pbutton = item->m_puserinteraction;

         ::image::image_pointer pimage;
         
         pimage= pbutton->m_pbitmap->m_pimage->clone();

         pimage->saturation(0.0);

         pbutton->m_pbitmap->m_pimage = pimage;

         if (::is_item(pitemCurrent, i))
         {

            pbutton->set_check(::e_check_checked, ::e_source_sync);

         }
         else
         {

            pbutton->set_check(::e_check_unchecked, ::e_source_sync);

         }

         i++;

      }


   }


   void group_image_list_impact::on_command(::message::command * pcommand)
   {

      string str = pcommand->command_id();

      if (str.case_insensitive_begins_eat("menu_item_"))
      {

         show_group(str);

      }

   }

   ::userex::image_list_impact * group_image_list_impact::get_current_list()
   {

      auto * pgroup = get_group(m_atomGroup);

      if (pgroup == nullptr)
      {

         return nullptr;

      }

      return pgroup->m_plist;

   }


   void group_image_list_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      if (!rectangleX)
      {

         return;

      }

      ::int_rectangle rectangleMenu(rectangleX);

      rectangleMenu.bottom() = rectangleX.top() + 32;

      m_pbuttonMenu->display_child(rectangleMenu);

      ::int_rectangle rectangleList(rectangleX);

      rectangleList.top() = rectangleX.top() + 32;

      auto * plist = get_current_list();

      if (plist != nullptr)
      {

         plist->place(rectangleList);

         plist->order_top();

         plist->display();

         plist->set_need_redraw();

      }

      for (auto & pgroup : m_groupa)
      {

         if (pgroup->m_plist.is_set() && pgroup->m_plist != plist)
         {

            pgroup->m_plist->hide();

         }

      }

   }


} // namespace userex



