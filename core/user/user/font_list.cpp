#include "framework.h"
#include "font_list.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/item.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/user/user/content.h"
#include "aura/user/user/scroll_state.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/font_enumeration_item.h"
#include "aura/graphics/write_text/font_list.h"
#include "aura/message/user.h"
#include "aura/user/user/user.h"
#include "aura/platform/session.h"
#include "aura/platform/system.h"
#include "aura/platform/application.h"


namespace user
{


   font_list::font_list()
   {

      user_font_list_common_construct();

   }


   void font_list::user_font_list_common_construct()
   {

      m_econtroltype = ::user::e_control_type_list;

      m_flagNonClient += e_non_client_hover_rect;

      m_flagNonClient -= e_non_client_focus_rect;

      m_bFirstShown = false;
      m_atomImpact = FONTSEL_IMPACT;
      m_pscrolllayoutY->m_scrollstatea[::user::e_layout_sketch].m_bScrollEnable = true;
      m_bEnsureVisible = false;
      m_bDefaultClickHandling = true;
      m_bDefaultMouseHoverHandling = true;
      m_bDefaultParentMouseMessageHandling = false;

   }


   font_list::~font_list()
   {

   }


   void font_list::install_message_routing(::channel * pchannel)
   {

      ::user::list_box::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &font_list::on_message_create);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &font_list::on_message_left_button_down);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &font_list::on_message_mouse_move);
      MESSAGE_LINK(MESSAGE_CLOSE, pchannel, this, &font_list::on_message_close);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &font_list::on_message_show_window);

   }


   void font_list::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

   }


   void font_list::set_font_list_type(::write_text::enum_font_list efontlist)
   {

      auto psession = get_session();

      if (efontlist == ::write_text::e_font_list_single_column)
      {

         m_pfontlist = psession->get_single_column_font_list();

      }
      else if (efontlist == ::write_text::e_font_list_wide)
      {

         if (m_pfontlist.is_null() || m_pfontlist->get_font_list_type() != ::write_text::e_font_list_wide)
         {

            __defer_construct_new(m_pfontlist);

            m_pfontlist->m_puserinteraction = this;

            //m_pfontlist->initialize_font_list(this);

            m_pfontlist->set_font_list_type(::write_text::e_font_list_wide);

         }

      }
      else
      {

         throw ::exception(todo);

      }

   }


   void font_list::set_font_branch(const ::scoped_string & scopedstrFontBranch)
   {

      __defer_construct_new(m_pfontlist);

      m_pfontlist->set_font_branch(scopedstrFontBranch);

   }


   void font_list::update_data(bool bSaveAndValidate)
   {

      if (bSaveAndValidate)
      {

      }
      else
      {

         //if (m_pfontlist.is_set())
         //{

         //   m_pfontlist->layout_sync();

         //}

      }

      //return true;

   }


   void font_list::_001OnTimer(::timer * ptimer)
   {

      ::user::list_box::_001OnTimer(ptimer);

   }


   void font_list::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pitem = hit_test(pmouse, ::user::e_zorder_any);

      auto psession = get_session();

      psession->user()->set_mouse_focus_LButtonDown(this);

      if (!::is_same_item(pitem, main_content().m_pitemCurrent))
      {

         //::index iIndexSel = ::item_index(pitem);

         main_content().m_pitemCurrent = pitem;

         set_need_redraw();

         auto pfontenumerationitema = m_pfontlist->m_pfontenumeration->m_pfontenumerationitema;

         if(::is_item_set(main_content().m_pitemCurrent)
            && main_content().m_pitemCurrent->m_item.m_iItem < pfontenumerationitema->get_count())
         {

            auto pfontenumerationitem = pfontenumerationitema->element_at(main_content().m_pitemCurrent->m_item.m_iItem);

            m_pfontlist->m_strFontFamily = pfontenumerationitem->m_strName;

         }
         
         if(has_handler())
         {

            auto ptopic = create_topic(::id_after_change_cur_sel);

            ptopic->m_puserelement = this;

            ptopic->m_actioncontext = ::e_source_user;

            ptopic->m_pitem = pitem;

            route(ptopic);
            
         }

         pmouse->m_lresult = 0;

         pmouse->m_bRet = true;

      }

   }


   void font_list::on_message_mouse_move(::message::message * pmessage)
   {

      if (!m_pfontlist
         || !m_pfontlist->m_pfontenumeration
         || !m_pfontlist->m_pfontenumeration->m_pfontenumerationitema)
      {

         return;

      }

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pitem = hit_test(pmouse, ::user::e_zorder_any);

      if (!::is_same_item(pitem, m_pitemHover))
      {

         //auto iItemHover = ::item_index(pitem);

         m_pitemHover = pitem;

         auto pfontenumerationitema = m_pfontlist->m_pfontenumeration->m_pfontenumerationitema;

         ::index iItemHover = ::item_index(m_pitemHover);

         if (pfontenumerationitema->contains_index(iItemHover))
         {

            auto pfontenumerationitem = pfontenumerationitema->element_at(iItemHover);

            m_pfontlist->m_strFontFamily = pfontenumerationitem->m_strName;

         }
         else
         {

            m_pfontlist->m_strFontFamily.empty_string();

         }

         if (has_handler())
         {

            auto ptopic = create_topic(::id_after_change_cur_hover);

            ptopic->m_puserelement = this;

            ptopic->m_actioncontext = ::e_source_user;

            ptopic->m_pitem = pitem;

            route(ptopic);

         }

         set_need_redraw();

         post_redraw();

      }

   }


   void font_list::handle(::topic * ptopic, ::context * pcontext)
   {

      list_box::handle(ptopic, pcontext);

      if (ptopic->m_atom == id_font_list_total_size)
      {

         set_need_layout();

         set_need_redraw();

         post_redraw();

      }

   }



   void font_list::_001OnNcClip(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::list_box::_001OnNcClip(pgraphics);

   }


   void font_list::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnNcDraw(pgraphics);

   }


   void font_list::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::list_box::_001OnClip(pgraphics);

   }


   void font_list::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pfontlist == nullptr)
      {

         return;

      }

      synchronous_lock synchronouslock(m_pfontlist->synchronization());

      if (m_bEnsureVisible)
      {

         __on_draw_ensure_sel_visible();

      }

      //m_pgraphics = pgraphics;

      if (m_pfontlist->m_strText != m_pfontlist->m_strTextLayout)
      {

         m_pfontlist->m_strTextLayout = m_pfontlist->m_strText;

         on_layout(pgraphics);

      }

      auto rectangle = this->rectangle();

      if (m_pfontlist->get_font_list_type() != ::write_text::e_font_list_wide)
      {

         auto pstyle = get_style(pgraphics);

         ::color::color colorBackground = get_color(pstyle, ::e_element_background);

         auto rectangleBackground(rectangle);

         //rectangleBackground += m_pointScroll;

         pgraphics->fill_rectangle(rectangleBackground, colorBackground);

      }

      //auto pstyle = m_pfontlist->m_puserstyle;

      //m_pfontlist->m_puserstyle = this;

      //auto rectangle = client_rectangle();

      m_pfontlist->_001OnDraw(pgraphics, this);

      //m_pfontlist->m_puserstyle = pstyle;

   }


   void font_list::query_full_size(::draw2d::graphics_pointer & pgraphics, ::size_i32 * psize)
   {

      *psize = m_pfontlist->m_size;

   }


   void font_list::ensure_sel_visible()
   {

      m_bEnsureVisible = true;

   }


   void font_list::__on_draw_ensure_sel_visible()
   {

      auto pitemCurrent = main_content().m_pitemCurrent;

      ::rectangle_i32 rectangle;

      ::index iCurrent = ::item_index(pitemCurrent);

      if (m_pfontlist->get_box_rect(&rectangle, iCurrent) && rectangle.area() > 0)
      {

         ::rectangle_i32 rectangleImpact;

         rectangleImpact = this->rectangle();

         rectangleImpact.offset(get_context_offset(::user::e_layout_sketch));

         if (!rectangleImpact.contains(rectangle))
         {

            set_context_offset_y((rectangle.top() + rectangle.bottom() - rectangleImpact.height()) / 2);

         }

         m_bEnsureVisible = false;

      }

   }


   void font_list::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleFontList = this->rectangle();

      if(rectangleFontList.is_empty())
      {

         return;

      }

      if (m_pfontlist.is_null())
      {

         return;

      }

      synchronous_lock synchronouslock(m_pfontlist->synchronization());

      auto pstyle = get_style(pgraphics);

      int iScrollBarWidth = get_int(pstyle, e_int_scroll_bar_thickness);

      //if (m_pfontlist->get_font_list_type() != ::write_text::e_font_list_wide)
      //{

         rectangleFontList.right() -= iScrollBarWidth;

      //}

      rectangleFontList.bottom() -= iScrollBarWidth;

      if (m_pfontlist->m_strFontFamily.has_char()
         && !::is_item_set(main_content().m_pitemCurrent)
         &&
         (m_pfontlist->is_updating()
         || m_pfontlist->m_iSelUpdateId != m_pfontlist->m_pfontenumeration->m_iUpdateId))
      {

         if (set_sel_by_name(m_pfontlist->m_strFontFamily))
         {

            ensure_sel_visible();

         }

      }

      m_pfontlist->set_client_rectangle(rectangleFontList);

      set_total_size(m_pfontlist->m_size, ::user::e_layout_design);

      //on_change_sketch_scroll_state();

   }


   string font_list::get_cur_sel_face_name()
   {
      
      if(!m_pfontlist)
      {
         
         return {};
         
      }

      auto iItemSel = ::item_index(main_content().m_pitemCurrent);

      if (iItemSel < 0)
      {

         return "";

      }

      synchronous_lock synchronouslock(m_pfontlist->synchronization());
      
      if(!m_pfontlist->m_pfontlistdata)
      {
         
         return {};
         
      }
      
      if(iItemSel >= m_pfontlist->m_pfontlistdata->item_count())
      {
       
         return {};
         
      }
      
      if(!m_pfontlist->m_pfontlistdata->item_at(iItemSel))
      {
         
         return {};
         
      }

      ::pointer < ::write_text::font_list_item > pfontlistitem = m_pfontlist->m_pfontlistdata->item_at(iItemSel);

      return pfontlistitem->m_strFont;

   }


   string font_list::get_cur_hover_face_name()
   {

      auto iItemHover = ::item_index(m_pitemHover);

      if (iItemHover < 0)
      {

         return "";

      }

      synchronous_lock synchronouslock(m_pfontlist->synchronization());

      ::pointer < ::write_text::font_list_item > pfontlistitem = m_pfontlist->m_pfontlistdata->item_at(iItemHover);

      return pfontlistitem->m_strFont;

   }


   string font_list::get_sel_by_name()
   {

      return get_cur_sel_face_name();

   }


   string font_list::get_hover_by_name()
   {

      return get_cur_hover_face_name();

   }


   ::item_pointer font_list::current_item()
   {

      synchronous_lock synchronouslock(m_pfontlist->synchronization());

      if (!::is_item_set(main_content().m_pitemCurrent))
      {

         return nullptr;

      }

      return main_content().m_pitemCurrent;

   }


   ::item_pointer font_list::hover_item()
   {

      synchronous_lock synchronouslock(m_pfontlist->synchronization());

      if (!::is_item_set(m_pitemHover))
      {

         return nullptr;

      }

      return m_pitemHover;

   }


   ::item_pointer font_list::on_hit_test(const ::point_i32 &point, ::user::e_zorder ezorder)
   {

      return m_pfontlist->hit_test(point, ezorder);

   }


   bool font_list::set_sel_by_name(const ::string & strName)
   {

      if (!m_pfontlist)
      {

         return false;

      }

      if (!m_pfontlist->set_sel_by_name(strName))
      {

         return false;

      }

      return true;

   }


   void font_list::on_change_combo_sel(index iSel)
   {

      if (m_pfontlist.is_set())
      {

         main_content().m_pitemCurrent = m_pfontlist->m_pfontlistdata->item_at(iSel);

      }

   }


   void font_list::on_message_close(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      display(e_display_none);

   }


   void font_list::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

         if (!m_bFirstShown)
         {

            m_bFirstShown = true;

            auto psystem = system()->m_paurasystem;

            psystem->signal(id_font_enumeration);

         }

      }
      else
      {

         auto pitem = current_item();

         if (pitem)
         {

            auto iItem = pitem->m_item.m_iItem;

            auto pfontenumerationitema = m_pfontlist->m_pfontenumeration->m_pfontenumerationitema;

            if (pfontenumerationitema->contains_index(iItem))
            {

               auto pfontenumerationitem = pfontenumerationitema->element_at((::index)iItem);

               m_pfontlist->m_strFontFamily = pfontenumerationitem->m_strName;

            }

         }

      }

   }


   void font_list::ensure_item_visible_by_index(index iItem)
   {

      if (m_pfontlist
         && m_pfontlist->m_pfontlistdata
         && iItem >= 0
         && iItem < m_pfontlist->m_pfontlistdata->item_count())
      {

         main_content().m_pitemCurrent = m_pfontlist->m_pfontlistdata->item_at(iItem);

         ::pointer < ::write_text::font_list_item > pfontlistitem = m_pfontlist->m_pfontlistdata->item_at(iItem);

         set_context_offset_y(pfontlistitem->m_box[0].m_rectangle.top());

      }
      else
      {

         ::user::list_box::ensure_item_visible_by_index(iItem);

      }

   }


} // namespace user



