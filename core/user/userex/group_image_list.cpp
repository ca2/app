#include "framework.h"
#include "core/user/userex/_userex.h"


namespace userex
{


   group_image_list_view::group_image_list_view()
   {

      m_size.cx = 7;
      m_size.cy = 5;


   }


   group_image_list_view::~group_image_list_view()
   {

   }





   void group_image_list_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void group_image_list_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void group_image_list_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      ::user::impact::on_subject(psubject, pcontext);

   }

   void group_image_list_view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &group_image_list_view::on_message_create);


   }


   ::userex::image_list_view * group_image_list_view::add_group(::id idGroup, string strIcon, string strTitle, ::file::path pathFolder)
   {

      __pointer(group) pgroup = __new(group);

      pgroup->m_iIndex = m_groupa.get_size();

      pgroup->m_idGroup = idGroup;

      pgroup->m_strIcon = strIcon;

      pgroup->m_strTitle = strTitle;

      m_idaHandledCommands.add("menu_item_" + idGroup.to_string());

      m_groupa.add(pgroup);

      auto * plist = get_group_list(idGroup);

      plist->m_iIndex = m_groupa.get_upper_bound();

      if (pathFolder.has_char())
      {

         plist->m_pathFolder = pathFolder;

         plist->update_data(false);

      }

      return plist;

   }


   void group_image_list_view::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      auto pcontext = m_pcontext->m_pauracontext;

      auto pcontextimage = pcontext->context_image();

      m_pimage = pcontextimage->load_image("project->jpg", false);

      pcreate->previous();

      m_idaHandledCommands.add(m_id);

      m_buttonMenu.create_control(this, m_id);

      m_buttonMenu.set_button_style(::user::button::style_image_and_text);

      //m_buttonMenu.create_color(::user::color_button_text, argb(255, 80, 80, 80));
      //m_buttonMenu.create_color(::user::color_button_background, argb(255, 255, 255, 255));
      //m_buttonMenu.create_int(::user::int_button_draw_text_and_image_flags, e_align_left_center | DT_SINGLELINE);

      m_buttonMenu.m_flagNonClient.erase(::user::interaction::non_client_focus_rect);

   }


   group_image_list_view::group * group_image_list_view::get_group(::id idGroup)
   {

      index iFind = m_groupa.predicate_find_first([=](auto & item)
      {

         return item->m_idGroup == idGroup;

      });

      if (iFind < 0)
      {

         return nullptr;

      }

      return m_groupa[iFind];

   }


   string group_image_list_view::get_group_title(group * pgroup)
   {

      ASSERT(pgroup != nullptr);

      if (pgroup->m_strTitle.has_char())
      {

         return pgroup->m_strTitle;

      }

      return pgroup->m_idGroup;


   }


   ::file::path group_image_list_view::get_link_path(string strLink)
   {

      ::file::path path;

      for (auto & group : m_groupa)
      {

         path = group->m_plist->get_link_path(strLink);

         if (path.has_char())
         {

            break;

         }

      }

      return path;

   }


   ::userex::image_list_view * group_image_list_view::get_group_list(::id idGroup)
   {

      __pointer(group) pgroup = get_group(idGroup);

      if (pgroup.is_null())
      {

         return nullptr;

      }

      auto & plist = pgroup->m_plist;

      if (plist.is_null())
      {

         plist = create_view < ::userex::image_list_view >(nullptr, nullptr, idGroup);

         plist->m_ealign = e_align_top_center;

         plist->m_bMultiSel = false;

      }

      return plist;

   }


   ::e_status group_image_list_view::set_current_item(const ::user::item & item, const ::action_context & context)
   {

      auto estatus = ::user::impact::set_current_item(item, context);

      if(estatus != success)
      {

         return estatus;

      }

      auto pgroup = m_groupa[item];

      if (!pgroup)
      {

         return error_not_found;

      }

      show_group(pgroup->m_idGroup);

      //auto * plist = get_group_list(strGroup);

     //::image_pointer pimage = papplication->matter_image(pgroup->m_strIcon);

      //m_buttonMenu.set_window_text(get_group_title(pgroup));

      //m_buttonMenu.LoadBitmaps(pimage);

      //if (pathFolder.has_char())
      //{

      //   plist->m_pathFolder = pathFolder;

      //   plist->update_data(false);

      //}

 /*     m_strGroup = strGroup;

      set_need_layout();

      set_need_redraw();*/

      return ::success;

   }


   bool group_image_list_view::show_group(::id idGroup, ::file::path pathFolder)
   {

      __pointer(group) pgroup = get_group(idGroup);

      if (pgroup.is_null())
      {

         return false;

      }

      auto * plist = get_group_list(idGroup);

      m_itemCurrent = plist->m_iIndex;

      auto pcontext = m_pcontext->m_pauracontext;

      auto pcontextimage = pcontext->context_image();

      ::image_pointer pimage = pcontextimage->matter_image(pgroup->m_strIcon);

      m_buttonMenu.set_window_text(get_group_title(pgroup));

      m_buttonMenu.LoadBitmaps(pimage);

      if (pathFolder.has_char())
      {

         plist->m_pathFolder = pathFolder;

         plist->update_data(false);

      }

      m_idGroup = idGroup;

      set_need_layout();

      set_need_redraw();

      return true;

   }


   void group_image_list_view::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::impact::_001OnNcDraw(pgraphics);

   }


   void group_image_list_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::impact::_001OnDraw(pgraphics);

   }


   void group_image_list_view::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::e_event_item_clicked)
      {


      }
      else if (pevent->m_eevent == ::user::e_event_click)
      {

         if (pevent->m_puserinteraction->m_id == m_id)
         {

            show_menu();

         }

      }

      return ::user::impact::on_control_event(pevent);

   }


   string group_image_list_view::get_menu_xml()
   {

      string str;

      str = "<menubar title = \""+string(m_id)+"\" close_button=\"false\">";

      for (auto & pgroup : m_groupa)
      {

         str += "<item id=\"menu_item_";
         str += pgroup->m_idGroup.to_string();
         str += "\" pimage =\"";
         str += pgroup->m_strIcon;
         str += "\">";
         str += get_group_title(pgroup);
         str += "</item>";

      }

      str += "</menubar>";

      return str;

   }


   void group_image_list_view::show_menu()
   {

      string strXml(get_menu_xml());

      ::user::interaction * pinteraction = &m_buttonMenu;

      ::rectangle_i32 rectWindow;

      pinteraction->get_window_rect(rectWindow);

      auto puser = user();

      m_pmenu = puser->track_popup_xml_menu(this, strXml, 0, rectWindow.bottom_left(), ::size_i32(width(), 0));
      //m_pmenu->create_color(::user::color_button_background, argb(255, 255, 255, 255));
      //m_pmenu->create_color(::user::color_button_text, argb(255, 80, 80, 80));

      index i = 0;

      auto itemCurrent = current_item();

      for (auto & item : *m_pmenu->m_pmenuitem->m_pmenuitema)
      {

         __pointer(::user::menu_button) pbutton = item->m_puserinteraction;

         ::image_pointer pimage;
         
         pimage= pbutton->m_pbitmap->m_pimage->clone();

         pimage->saturation(0.0);

         pbutton->m_pbitmap->m_pimage = pimage;

         if (itemCurrent == i)
         {

            pbutton->_001SetCheck(::check_checked, ::e_source_sync);

         }
         else
         {

            pbutton->_001SetCheck(::check_unchecked, ::e_source_sync);

         }

         i++;

      }


   }


   void group_image_list_view::on_command(::message::command * pcommand)
   {

      string str = pcommand->m_id;

      if (::str::begins_eat_ci(str, "menu_item_"))
      {

         show_group(str);

      }

   }

   ::userex::image_list_view * group_image_list_view::get_current_list()
   {

      auto * pgroup = get_group(m_idGroup);

      if (pgroup == nullptr)
      {

         return nullptr;

      }

      return pgroup->m_plist;

   }


   void group_image_list_view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleClient = get_client_rect();

      if (!rectangleClient)
      {

         return;

      }

      ::rectangle_i32 rectMenu(rectangleClient);

      rectMenu.bottom = rectangleClient.top + 32;

      m_buttonMenu.display_child(rectMenu);

      ::rectangle_i32 rectList(rectangleClient);

      rectList.top = rectangleClient.top + 32;

      auto * plist = get_current_list();

      if (plist != nullptr)
      {

         plist->place(rectList);

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



