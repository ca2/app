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
      m_atomImpact = FONTSEL_IMPACT;
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

            __defer_construct_new(m_pfontlist);

            m_pfontlist->m_puserinteraction = this;

            //m_pfontlist->initialize_font_list(this);

            m_pfontlist->set_font_list_type(::write_text::font_list::type_wide);

         }

      }
      else
      {

         throw ::exception(todo);

      }

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

      auto pitem = hit_test(pmouse);

      auto psession = get_session();

      psession->user()->set_mouse_focus_LButtonDown(this);

      if (!::is_item(pitem, m_pfontlist->m_iSel))
      {

         ::index iIndexSel = ::item_index(pitem);

         m_pfontlist->m_iSel = iIndexSel;

         set_need_redraw();

         auto pfontenumerationitema = m_pfontlist->m_pfontenumeration->m_pfontenumerationitema;

         if(iIndexSel >= 0 && iIndexSel < pfontenumerationitema->get_count())
         {

            auto pfontenumerationitem = pfontenumerationitema->element_at(iIndexSel);

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

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pitem = hit_test(pmouse);

      if (!::is_item(pitem, m_pfontlist->m_iHover))
      {

         auto iItemHover = ::item_index(pitem);

         m_pfontlist->m_iHover = iItemHover;

         if (m_pfontlist && m_pfontlist->m_pfontenumeration && m_pfontlist->m_pfontenumeration->m_pfontenumerationitema)
         {

            auto pfontenumerationitema = m_pfontlist->m_pfontenumeration->m_pfontenumerationitema;

            if (pfontenumerationitema->contains_index(iItemHover))
            {

               auto pfontenumerationitem = pfontenumerationitema->element_at(iItemHover);

               m_pfontlist->m_strFontFamily = pfontenumerationitem->m_strName;

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

         }

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

         ::color::color colorBackground = get_color(pstyle, ::e_element_background);

         auto rectangleBackground(rectangleClient);

         rectangleBackground += m_pointScroll;

         pgraphics->fill_rectangle(rectangleBackground, colorBackground);

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

         ::rectangle_i32 rectangleImpact;

         get_client_rect(rectangleImpact);

         rectangleImpact.offset(m_pointScroll);

         if (!rectangleImpact.contains(rectangle))
         {

            m_pointScroll.y = (rectangle.top + rectangle.bottom - rectangleImpact.height()) / 2;

         }

         m_bEnsureVisible = false;

      }

   }


   void font_list::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleFontList = get_client_rect();

      if(rectangleFontList.is_empty())
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

         rectangleFontList.right -= iScrollBarWidth;

      }

      rectangleFontList.bottom -= iScrollBarWidth;

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

      m_pfontlist->set_client_rectangle(rectangleFontList);

      m_sizeTotal = m_pfontlist->m_size;

      on_change_view_size(pgraphics);

   }


   string font_list::get_cur_sel_face_name()
   {

      auto iItemSel = m_pfontlist->m_iSel;

      if (iItemSel < 0)
      {

         return "";

      }

      synchronous_lock synchronouslock(m_pfontlist->mutex());

      return m_pfontlist->m_pfontlistdata->element_at(iItemSel)->m_strFont;

   }


   string font_list::get_cur_hover_face_name()
   {

      auto iItemHover = m_pfontlist->m_iHover;

      if (iItemHover < 0)
      {

         return "";

      }

      synchronous_lock synchronouslock(m_pfontlist->mutex());

      return m_pfontlist->m_pfontlistdata->element_at(iItemHover)->m_strFont;

   }


   item_pointer font_list::current_item()
   {

      synchronous_lock synchronouslock(m_pfontlist->mutex());

      if (m_pfontlist->m_iSel < 0)
      {

         return nullptr;

      }

      if (m_pfontlist->m_iSel >= m_pfontlist->m_pfontlistdata->get_count())
      {

         return nullptr;

      }

      return __new(::item(e_element_item, m_pfontlist->m_iSel));

   }


   item_pointer font_list::hover_item()
   {

      synchronous_lock synchronouslock(m_pfontlist->mutex());

      if (m_pfontlist->m_iHover < 0)
      {

         return nullptr;

      }

      if (m_pfontlist->m_iHover >= m_pfontlist->m_pfontlistdata->get_count())
      {

         return nullptr;

      }

      return __new(::item(::e_element_item, m_pfontlist->m_iHover));

   }


   ::item_pointer font_list::on_hit_test(const ::point_i32 &point)
   {

      return m_pfontlist->hit_test(point + m_pointScroll);

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

            psystem->signal(id_font_enumeration);

         }

      }
      else
      {

         auto iItem = current_item()->m_iItem;

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



