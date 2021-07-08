#include "framework.h"
#include "core/user/user/_user.h"
#include "aura/update.h"
#include "aura/procedure.h"


namespace user
{


   font_list::font_list()
   {

      user_font_list_common_construct();

   }


   void font_list::user_font_list_common_construct()
   {

      m_econtroltype = ::user::e_control_type_list;

      m_flagNonClient.add(non_client_hover_rect);

      m_bFirstShown = false;
      m_idView = FONTSEL_IMPACT;
      m_scrolldataVertical.m_bScrollEnable = true;
      m_bEnsureVisible = false;

   }


   font_list::~font_list()
   {

   }


   void font_list::install_message_routing(::channel * pchannel)
   {

      ::user::list_box::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &font_list::on_message_create);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &font_list::on_message_left_button_down);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &font_list::on_message_mouse_move);
      MESSAGE_LINK(e_message_close, pchannel, this, &font_list::on_message_close);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &font_list::on_message_show_window);

   }


   void font_list::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

   }


   void font_list::set_font_list_type(::write_text::font_list::enum_type etype)
   {

      auto psession = get_session();

      if (etype == ::write_text::font_list::type_single_column)
      {

         m_pfontlist = psession->get_single_column_font_list();

      }
      else if (etype == ::write_text::font_list::type_wide)
      {

         if (m_pfontlist.is_null() || m_pfontlist->get_font_list_type() != ::write_text::font_list::type_wide)
         {

            m_pfontlist = ::__create_new < ::write_text::font_list >();

            m_pfontlist->initialize_font_list(this);

            m_pfontlist->set_font_list_type(::write_text::font_list::type_wide);

         }

         m_pfontlist->m_puserinteraction = this;

      }
      else
      {

         __throw(todo);

      }

   }


   bool font_list::update_data(bool bSaveAndValidate)
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

      return true;

   }


   void font_list::_001OnTimer(::timer * ptimer)
   {

      ::user::list_box::_001OnTimer(ptimer);

   }


   void font_list::on_message_left_button_down(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      auto item = hit_test(pmouse);

      auto psession = get_session();

      psession->user()->set_mouse_focus_LButtonDown(this);

      if (item.m_iItem != m_pfontlist->m_iSel)
      {

         m_pfontlist->m_iSel = (index) item.m_iItem;

         set_need_redraw();

         auto iItem = item.m_iItem;

         auto pfontenumerationitema = m_pfontlist->m_pfontenumeration->m_pfontenumerationitema;

         if(iItem >= 0 && iItem < pfontenumerationitema->get_count())
         {

            auto pfontenumerationitem = pfontenumerationitema->element_at((::index)iItem);

            m_pfontlist->m_strFontFamily = pfontenumerationitem->m_strName;

         }
         
         if(has_control_event_handler())
         {

            ::user::control_event ev;

            ev.m_puie = this;

            ev.m_eevent = ::user::e_event_after_change_cur_sel;

            ev.m_actioncontext = ::e_source_user;

            ev.m_item = item;

            ev.m_id = m_idView;

            route_control_event(&ev);
            
         }

         pmouse->m_lresult = 0;

         pmouse->m_bRet = true;

      }

   }


   void font_list::on_message_mouse_move(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      auto item = hit_test(pmouse);

      if (m_pfontlist->m_iHover != item.m_iItem)
      {

         m_pfontlist->m_iHover = item.item_index();

         auto iItem = item.m_iItem;

         auto pfontenumerationitema = m_pfontlist->m_pfontenumeration->m_pfontenumerationitema;

         if(pfontenumerationitema->contains_index(iItem))
         {

            auto pfontenumerationitem = pfontenumerationitema->element_at((::index)iItem);

            m_pfontlist->m_strFontFamily = pfontenumerationitem->m_strName;

         }
         
         if(has_control_event_handler())
         {

            ::user::control_event ev;

            ev.m_puie = this;

            ev.m_eevent = ::user::e_event_after_change_cur_hover;

            ev.m_actioncontext = ::e_source_user;

            ev.m_id = m_idView;

            route_control_event(&ev);
               
         }

         set_need_redraw();

      }

   }


   void font_list::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      list_box::on_subject(psubject, pcontext);

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

      if (m_pfontlist->m_strFontFamily.has_char()
         && m_pfontlist->m_iSel < 0 
         &&
         (m_pfontlist->is_updating()
         || m_pfontlist->m_iSelUpdateId != m_pfontlist->m_pfontenumeration->m_iUpdateId))
      {

         if (set_sel_by_name(m_pfontlist->m_strFontFamily))
         {

            ensure_sel_visible();

         }

      }

      if (m_bEnsureVisible)
      {

         __on_draw_ensure_sel_visible();

      }

      synchronous_lock synchronouslock(m_pfontlist->mutex());

      //m_pgraphics = pgraphics;

      if (m_pfontlist->m_strText != m_pfontlist->m_strTextLayout)
      {

         m_pfontlist->m_strTextLayout = m_pfontlist->m_strText;

         on_layout(pgraphics);

      }

      auto rectangleClient = get_client_rect();

      if (m_pfontlist->get_font_list_type() != ::write_text::font_list::type_wide)
      {

         auto pstyle = get_style(pgraphics);

         ::color::color colorBackground = get_color(pstyle, ::user::e_element_background);

         auto rectBackground(rectangleClient);

         rectBackground += m_pointScroll;

         pgraphics->fill_rectangle(rectBackground, colorBackground);

      }

      //auto pstyle = m_pfontlist->m_puserstyle;

      //m_pfontlist->m_puserstyle = this;

      m_pfontlist->_001OnDraw(pgraphics);

      //m_pfontlist->m_puserstyle = pstyle;

   }


   void font_list::query_full_size(::draw2d::graphics_pointer & pgraphics, ::SIZE_I32 * psize)
   {

      *psize = m_pfontlist->m_size;

   }


   void font_list::ensure_sel_visible()
   {

      m_bEnsureVisible = true;

   }


   void font_list::__on_draw_ensure_sel_visible()
   {

      index iSel = m_pfontlist->m_iSel;

      ::rectangle_i32 rectangle;

      if (m_pfontlist->get_box_rect(rectangle, iSel) && rectangle.area() > 0)
      {

         ::rectangle_i32 rectImpact;

         get_client_rect(rectImpact);

         rectImpact.offset(m_pointScroll);

         if (!rectImpact.contains(rectangle))
         {

            m_pointScroll.y = (rectangle.top + rectangle.bottom - rectImpact.height()) / 2;

         }

         m_bEnsureVisible = false;

      }

   }


   void font_list::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectFontList = get_client_rect();

      if(rectFontList.is_empty())
      {

         return;

      }

      if (m_pfontlist.is_null())
      {

         return;

      }

      synchronous_lock synchronouslock(m_pfontlist->mutex());

      auto pstyle = get_style(pgraphics);

      int iScrollBarWidth = get_int(pstyle, e_int_scroll_bar_width);

      if (m_pfontlist->get_font_list_type() != ::write_text::font_list::type_wide)
      {

         rectFontList.right -= iScrollBarWidth;

      }

      rectFontList.bottom -= iScrollBarWidth;

      m_pfontlist->set_client_rectangle(rectFontList);

      m_sizeTotal = m_pfontlist->m_size;

      on_change_view_size(pgraphics);

   }


   string font_list::get_cur_sel_face_name()
   {

      auto item = current_item();

      if (!item.is_set())
      {

         return "";

      }

      synchronous_lock synchronouslock(m_pfontlist->mutex());

      return m_pfontlist->m_pfontlistdata->element_at(item)->m_strFont;

   }


   string font_list::get_cur_hover_face_name()
   {

      auto item = hover_item();

      if (!item.is_set())
      {

         return "";

      }

      synchronous_lock synchronouslock(m_pfontlist->mutex());

      return m_pfontlist->m_pfontlistdata->element_at(item)->m_strFont;

   }


   item font_list::current_item()
   {

      synchronous_lock synchronouslock(m_pfontlist->mutex());

      if (m_pfontlist->m_iSel < 0)
      {

         return -1;

      }

      if (m_pfontlist->m_iSel >= m_pfontlist->m_pfontlistdata->get_count())
      {

         return -1;

      }

      return m_pfontlist->m_iSel;

   }


   item font_list::hover_item()
   {

      synchronous_lock synchronouslock(m_pfontlist->mutex());

      if (m_pfontlist->m_iHover < 0)
      {

         return -1;

      }

      if (m_pfontlist->m_iHover >= m_pfontlist->m_pfontlistdata->get_count())
      {

         return -1;

      }

      return m_pfontlist->m_iHover;

   }


   void font_list::on_hit_test(::user::item & item)
   {

      item = m_pfontlist->hit_test(item.m_pointHitTest);

   }


   bool font_list::set_sel_by_name(string str)
   {

      if (!m_pfontlist)
      {

         return false;

      }

      if (!m_pfontlist->set_sel_by_name(str))
      {

         return false;

      }

      return true;

   }


   void font_list::on_change_combo_sel(index iSel)
   {

      if (m_pfontlist.is_set())
      {

         m_pfontlist->m_iSel = iSel;

      }

   }


   void font_list::on_message_close(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      display(e_display_none);

   }


   void font_list::on_message_show_window(::message::message * pmessage)
   {

      __pointer(::message::show_window) pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

         if (!m_bFirstShown)
         {

            m_bFirstShown = true;

            auto psystem = m_psystem->m_paurasystem;

            psystem->set_modified(id_font_enumeration);

            //fork([this]()
  //             {
//
    //              psession->call(e_routine_font_change);

      //         });

         }

      }
      else
      {

         auto iItem = current_item().m_iItem;

         auto pfontenumerationitema = m_pfontlist->m_pfontenumeration->m_pfontenumerationitema;

         if (pfontenumerationitema->contains_index(iItem))
         {

            auto pfontenumerationitem = pfontenumerationitema->element_at((::index)iItem);

            m_pfontlist->m_strFontFamily = pfontenumerationitem->m_strName;

         }

      }

   }


   void font_list::_001EnsureVisible(index iItem)
   {

      if (m_pfontlist.is_set()
         && iItem >= 0
         && iItem < m_pfontlist->m_pfontlistdata->get_size())
      {

         m_pfontlist->m_iSel = iItem;

         m_pointScroll.y = m_pfontlist->m_pfontlistdata->element_at(iItem)->m_box[0].m_rectangle.top;

      }
      else
      {

         ::user::list_box::_001EnsureVisible(iItem);

      }

   }


} // namespace user



