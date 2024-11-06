#include "framework.h"
#include "multiple_option.h"
#include "list_box.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/user_key.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/user/user/_constant.h"
#include "acme/user/user/content.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/windowing/windowing.h"
#include "aura/message/user.h"
#include "aura/platform/session.h"


namespace user
{


   multiple_option::multiple_option()
   {

      user_multiple_option_common_construct();

   }


   void multiple_option::user_multiple_option_common_construct()
   {

      m_econtroltype                         = e_control_type_multiple_option;
      m_bDefaultParentMouseMessageHandling   = true;
      m_bDefaultClickHandling = true;
      m_iIndex                               = -1;

   }


   multiple_option::~multiple_option()
   {



   } bool multiple_option::on_click(::item* pitem)
   {

      if (!::is_item_set(pitem))
      {

         return false;

      }

      m_propertyOption.set_property(pitem->m_atom, ::e_source_user);

      set_need_redraw();

      post_redraw();

      return true;

   }


   ::particle_pointer multiple_option::clone()
   {

      auto pmultipleoptionClone = m_papplication->__create_new < multiple_option >();

      return pmultipleoptionClone;

   }


   void multiple_option::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &multiple_option::on_message_mouse_move);
      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &multiple_option::on_message_mouse_leave);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &multiple_option::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &multiple_option::on_message_left_button_up);
      MESSAGE_LINK(e_message_key_down,pchannel,this,&multiple_option::on_message_key_down);
      MESSAGE_LINK(e_message_key_up,pchannel,this,&multiple_option::on_message_key_up);
      //MESSAGE_LINK(e_message_set_focus,pchannel,this,&multiple_option::on_message_set_focus);
      //MESSAGE_LINK(e_message_kill_focus, pchannel, this, &multiple_option::on_message_kill_focus);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &multiple_option::on_message_show_window);
      MESSAGE_LINK(e_message_reposition, pchannel, this, &multiple_option::on_message_move);

   }




   bool multiple_option::should_show_keyboard_focus()
   {

      return has_keyboard_focus();

   }


   ::write_text::font_pointer multiple_option::get_font(style * pstyle, enum_element eelement, ::user::enum_state estate)
   {


      return ::user::interaction::get_font(pstyle, eelement, estate);

   }



   void multiple_option::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

      ::int_rectangle r = client2_rectangle();

      pgraphics->draw_rectangle(r);

      auto iIndex = selected_index();

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->set_font(this, ::e_element_none);

      for (::collection::index i = 0; i < main_content().item_count(); i++)
      {

         auto pitem = main_content().item_at(i);

         auto puseritem = user_item(pitem);

         auto rItem = puseritem->m_rectangle2;

         if (i == iIndex)
         {

            pgraphics->fill_rectangle(rItem, ::argb(255, 10, 77, 189));

            pgraphics->set_text_color(::color::white);


         }
         else
         {

            pgraphics->fill_rectangle(rItem, ::argb(80, 127, 127, 127));

            pgraphics->set_text_color(::argb(255, 189, 189, 189));

         }

         ::string strName;

         if (i < m_straName.size())
         {

            strName = m_straName[i];

         }

         
         if (strName.has_character())
         {

            pgraphics->draw_text(strName, rItem, e_align_center);

         }

      }
      

   }



   ::collection::index multiple_option::get_option_count() const
   {

      return m_atomaOptions.size();

   }


   bool multiple_option::get_element_rectangle(::int_rectangle & rectangle, enum_element eelement)

   {

      if(eelement == e_element_text)
      {

         eelement = e_element_combo_edit;

      }

      return interaction::get_element_rectangle(rectangle, eelement);

   }


   ::item_pointer multiple_option::on_hit_test(const ::int_point& point, ::user::e_zorder ezorder)
   {

      //::int_rectangle rectangleElement;

      return ::user::interaction::on_hit_test(point, ezorder);

      //if(get_element_rectangle(rectangleElement, e_element_drop_down))
      //{

      //   if (rectangleElement.contains(point))
      //   {

      //      auto pitem = __allocate ::item(e_element_drop_down);

      //      auto puseritem = user_item(pitem);
      //      
      //      puseritem->m_rectangle2 = rectangleElement;

      //      return pitem;

      //   }

      //}

      ///auto rectangleX = this->rectangle();

      //if (rectangleX.contains(point))
      //{

      //   auto pitem = __allocate ::item(e_element_text);

      //   auto puseritem = user_item(pitem);
      //      
      //   puseritem->m_rectangle2 = rectangleElement;

      //   return pitem;

      //}
      //
      //auto pitemNone = __allocate ::item(e_element_none);
      //
      //return pitemNone;

   }


   void multiple_option::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

      if (!pshowwindow->m_bShow)
      {

         //if (m_plistbox.is_set() && m_plistbox->is_window())
         //{

         //   m_plistbox->post_message(e_message_close);

         //}

      }

   }


   void multiple_option::on_message_move(::message::message * pmessage)
   {

      _on_reposition();

   }


   void multiple_option::on_reposition()
   {

      _on_reposition();

   }


   void multiple_option::_on_reposition()
   {

      //if (is_drop_down())
      //{

      //   ::int_rectangle rectangleWindow;

      //   window_rectangle(rectangleWindow, ::user::e_layout_sketch);

      //   m_plistbox->on_drop_down(rectangleWindow, m_sizeFull);

      //}

   }


   void multiple_option::on_message_key_down(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if(pkey->m_ekey == ::user::e_key_down)
      {

         /*if(!is_drop_down())
         {

            _001ShowDropDown();

         }*/

      }

   }


   void multiple_option::on_message_key_up(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void multiple_option::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->previous();

      if (is_window_enabled())
      {

         //if (!m_bEdit || (::is_set(m_pitemHover) && m_pitemHover->m_item.m_eelement == e_element_drop_down))
         //{

         //   auto pwindowing = windowing();

         //   auto pcursor = pwindowing->get_cursor(e_cursor_arrow);

         //   user_mouse_set_cursor(pmouse, pcursor);

         //   pmouse->m_bRet = true;

         //}

      }

   }


   void multiple_option::on_message_mouse_leave(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      m_pitemHover = nullptr;

      set_need_redraw();

   }


   void multiple_option::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (!is_window_enabled())
      {

         return;

      }

      auto pitemHit = hit_test(pmouse, e_zorder_any);

      //if (::is_set(pitemHit) && (!m_bEdit || pitemHit->m_item.m_eelement == e_element_drop_down))
      //{

      //   class ::time timeLastVisibilityChangeElapsed;

      //   if (m_plistbox.is_set())
      //   {

      //      timeLastVisibilityChangeElapsed = m_plistbox->m_timeLastVisibilityChange.elapsed();

      //   }

      //   bool bDropDownListBoxShown = false;

      //   if (m_plistbox.is_null() || timeLastVisibilityChangeElapsed > 300_ms)
      //   {

      //      bDropDownListBoxShown = _001ToggleDropDown();

      //   }
      //   else if (!m_plistbox->const_layout().sketch().is_screen_visible())
      //   {

      //      //informationf("test");

      //   }

      //   if (!bDropDownListBoxShown)
      //   {

      //      set_keyboard_focus();

      //      set_active_window();

      //   }

      //   set_need_redraw();

      //   post_redraw();

      //   pmouse->m_bRet = true;

      //}

   }


   void multiple_option::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (is_window_enabled())
      {

         //auto point = screen_to_client(pmouse->m_point);

         //auto pitemHit = hit_test(pmouse, e_zorder_any);

         //if (::is_set(pitemHit) && (!m_bEdit || pitemHit->m_item.m_eelement == e_element_drop_down))
         //{

         //   pmouse->m_bRet = true;

         //}

      }

   }


   void multiple_option::on_set_keyboard_focus()
   {

      //if(m_bEdit)
      //{

      //   plain_edit::on_set_keyboard_focus();

      //}

   }


   void multiple_option::on_kill_keyboard_focus()
   {

      //if (::is_set(m_plistbox) && m_plistbox->is_window())
      //{

      //   m_plistbox->post_message(e_message_close);

      //}

   }



   void multiple_option::set_current_item(::item * pitem, const ::action_context & actioncontext)
   {

      if (::is_same_item(current_item(), pitem))
      {

         return;

      }

      //if (m_plistbox)
      //{

      //   m_plistbox->main_content().m_pitemCurrent = pitem;

      //}

      ::user::interaction::set_current_item(pitem, actioncontext);

      if (!is_window())
      {

         //return ::success;

         return;

      }

      string strItem;

      //if (::is_set(pitem))
      //{

      //   _001GetListText(pitem->m_item.m_iItem, strItem);

      //}

      set_text(strItem, actioncontext);

      //return ::success;

   }


   void multiple_option::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      //if(m_bEdit)
      //{

      //   ::user::interaction::on_layout(pgraphics);

      //}


      /*      ::write_text::font_pointer fontxyz(e_create);

            auto rectangleX = this->rectangle();

            fontxyz->m_dFontSize = rectangleX.height() * 0.4;
            fontxyz->m_eunitFontSize = ::draw2d::e_unit_pixel;
            fontxyz->m_bUpdated = false;

            SetFont(fontxyz);*/

      ::int_rectangle r = client2_rectangle();

      pgraphics->draw_rectangle(r);

      int iPad = 5;

      r.deflate(iPad);

      int iW = (int) ( r.width() / m_atomaOptions.size()) ;

      int x = iPad;

      auto iIndex = selected_index();

      main_content().clear_items();

      for (::collection::index i = 0; i < m_atomaOptions.size(); i++)
      {

         ::int_rectangle rItem(r);

         rItem.left() = x;
         rItem.right() = rItem.left() + iW;

         if (i == iIndex)
         {

            pgraphics->fill_rectangle(rItem, ::argb(255, 10, 77, 189));

         }
         else
         {

            pgraphics->fill_rectangle(rItem, ::argb(127, 127, 127, 127));

         }
         auto pitem = __create_new<::item>();
         pitem->m_item.m_iItem = i;
         pitem->m_item.m_eelement = e_element_item;
         pitem->m_atom = m_atomaOptions[i];


         main_content().add_item(pitem);

         auto puseritem = user_item(pitem);

         puseritem->m_rectangle2 = rItem;

         //puseritem->m_euseritemflag

         x += iW;


      }


   }


   //void multiple_option::plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & actioncontext)
   //{

   //   if(actioncontext.is_user_source())
   //   {

   //      string str;

   //      //if(m_bEdit)
   //      //{

   //      // ::user::interaction::get_text(str);
   //      str = as_text();

   //      //      }
   //      //      else
   //      //      {
   //      //
   //      //         str = m_strText;
   //      //
   //      //      }

   //      auto itemCurrent = _001FindListText(str);

   //      set_current_item(__allocate ::item(e_element_item, itemCurrent), actioncontext);

   //   }

   //}


   void multiple_option::handle(::topic * ptopic, ::context * pcontext)
   {

      ////if(m_bEdit)
      //{

      //   ::user::interaction::handle(ptopic, pcontext);

      //}

      if (ptopic->m_atom == ::id_after_change_cur_sel)
      {

         auto puserinteraction = ptopic->user_interaction();

         //if (puserinteraction == m_plistbox)
         //{

         //   set_current_item(ptopic->m_pitem, ptopic->m_actioncontext);

         //   _001ShowDropDown(false);

         //   ptopic->Ret();

         //   set_need_redraw();

         //   post_redraw();

         //   keyboard_set_focus_next();

         //   return;

         //}

      }

   }


   //bool multiple_option::create_interaction(::user::interaction * puiParent, const ::atom & atom)
   //{

   //   if (!::user::interaction::create_interaction(puiParent, atom))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


//#ifdef WINDOWS_DESKTOP
//   //Derived class is responsible for implementing these handlers
//   //for owner/self draw controls (except for the optional DeleteItem)
//   void multiple_option::DrawItem(LPDRAWITEMSTRUCT)
//   { ASSERT(false); }
//   void multiple_option::MeasureItem(LPMEASUREITEMSTRUCT)
//   { ASSERT(false); }
//   int multiple_option::CompareItem(LPCOMPAREITEMSTRUCT)
//   { ASSERT(false); return 0; }
//   void multiple_option::DeleteItem(LPDELETEITEMSTRUCT)
//   { /* default to nothing */ }
//#endif

//   bool multiple_option::OnChildNotify(::user::message * pusermessage)
//   {
//
//#ifdef WINDOWS_DESKTOP
//      switch (pusermessage->m_atom)
//      {
//      case WM_DRAWITEM:
//#ifdef WINDOWSEX
//         DrawItem((LPDRAWITEMSTRUCT)pusermessage->m_lparam);
//#else
//         throw ::exception(todo);
//#endif
//         break;
//      case e_message_measure_item:
//#ifdef WINDOWSEX
//         MeasureItem((LPMEASUREITEMSTRUCT)pusermessage->m_lparam);
//#else
//         throw ::exception(todo);
//#endif
//         break;
//      case WM_COMPAREITEM:
//#ifdef WINODWSEX
//         *pResult = CompareItem((LPCOMPAREITEMSTRUCT)pusermessage->m_lparam);
//#else
//         throw ::exception(todo);
//#endif
//         break;
//      case WM_DELETEITEM:
//#ifdef WINODWSEX
//         DeleteItem((LPDELETEITEMSTRUCT)pusermessage->m_lparam);
//#else
//         throw ::exception(todo);
//#endif
//         break;
//      default:
//         return ::user::interaction::OnChildNotify(pusermessage);
//      }
//#endif
//
//      return true;
//   }
//



   ::collection::index multiple_option::erase_item_at(::collection::index nIndex)
   {

      //auto iIndex = m_plistbox->erase_item_at(nIndex);

      //;; return iIndex;
      return - 1;

   }


   ::collection::index multiple_option::insert_item_at(::collection::index nIndex, const ::string & pszString)
   {

      //ASSERT(is_window());

      //return (int)send_message( CB_INSERTSTRING, nIndex, (LPARAM)pszString);

      //auto iIndex= m_plistbox->insert_item_at(nIndex, pszString);
      //return iIndex;
      return -1;

   }


   void multiple_option::reset_content()
   {

      //if (!m_plistbox)
      //{

      //   return;

      //}

      //m_plistbox->reset_content();

   }




   ::collection::index multiple_option::add_item(const ::scoped_string& scopedstr, const ::atom & atom)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto iIndex = m_atomaOptions.add(atom);

      m_straName.add(scopedstr);

      return iIndex;

   }

   //::collection::index multiple_option::add_string(const ::string & pszString,uptr dwItemData)
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   ASSERT(m_edatamode == data_mode_opaque);

   //   if (m_edatamode != data_mode_opaque)
   //   {

   //      return -1;

   //   }

   //   defer_create_list_box();

   //   return m_plistbox->add_item(pszString, dwItemData);

   //}


   //::collection::index multiple_option::add_string(const ::string & pszString, const ::string & strValue)
   //{

   //   ASSERT(m_edatamode == data_mode_string);

   //   if (m_edatamode != data_mode_string)
   //   {

   //      return -1;

   //   }

   //   defer_create_list_box();

   //   auto iIndex = m_plistbox->add_string(pszString, strValue);

   //   return iIndex;

   //}


   bool multiple_option::has_action_hover()
   {

      //return ::is_set(m_pitemHover) || is_drop_down();

      return true;

   }


   ::collection::index multiple_option::selected_index() const
   {

      try
      {

         auto property = m_propertyOption.get_property();

         auto atom = property.as_atom();

         auto iIndex = m_atomaOptions.find_first(atom);

         return iIndex;

      }
      catch (...)
      {

      }

      return -1;

   }


   void multiple_option::set_current_item_by_text(const ::scoped_string & scopedstr, const ::action_context & actioncontext)
   {

      auto iIndex = m_straName.case_insensitive_find_first(scopedstr);

      if (iIndex >= 0)
      {

         set_current_item_by_index(iIndex, actioncontext);

      }

   }


   void multiple_option::set_current_item_by_index(::collection::index iIndex, const ::action_context & action_context)
   {

      m_iIndex = iIndex;

   }


   void multiple_option::set_current_item_by_atom(const ::atom & atom, const ::action_context & actioncontext)
   {

      auto iIndex = m_atomaOptions.find_first(atom);

      if (iIndex >= 0)
      {

         set_current_item_by_index(iIndex, actioncontext);

      }

   }


   string multiple_option::get_current_item_text()
   {

      if (m_iIndex < 0 || m_iIndex >= m_straName.size())
      {

         return {};

      }

      return m_straName[m_iIndex];

   }


   ::atom multiple_option::get_current_item_atom()
   {

      if (m_iIndex < 0 || m_iIndex >= m_atomaOptions.size())
      {

         return {};

      }

      return m_atomaOptions[m_iIndex];

   }



   bool multiple_option::keyboard_focus_is_focusable()
   {

      // return m_bEdit && is_window_enabled() && is_window_visible(e_layout_sketch);
      return is_window_enabled() && is_window_visible(e_layout_sketch);

   }


} // namespace user



