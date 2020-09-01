#include "framework.h"
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

      m_bFirstShown = false;
      m_idView = FONTSEL_IMPACT;
      //m_puserstyle = this;
      //m_econtroltype = control_type_list;
      m_scrolldataVert.m_bScrollEnable = true;
      m_bEnsureVisible = false;

   }


   font_list::~font_list()
   {

   }


   void font_list::install_message_routing(::channel * pchannel)
   {

      ::user::combo_list::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &font_list::_001OnCreate);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &font_list::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_MOUSEMOVE, pchannel, this, &font_list::_001OnMouseMove);
      IGUI_MSG_LINK(WM_CLOSE, pchannel, this, &font_list::_001OnClose);
      IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &font_list::_001OnShowWindow);

   }


   void font_list::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      descriptor().set_control_type(::user::control_type_list);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      User.will_use_view_hint(FONTSEL_IMPACT);

      Session.add(e_procedure_font_change, [this]()
      {

         on_font_change();

      });

   }


   void font_list::on_font_change()
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      if (rectClient.area() > 0)
      {

         m_pfontlist->m_rectClient = rectClient;

         m_pfontlist->update();

      }

      TRACE("pane_tab_view::on_change_cur_sel font_check_need_update thread finished!!");

   }


   void font_list::set_font_list_type(::draw2d::font_list::e_type etype)
   {

      if (etype == ::draw2d::font_list::type_single_column)
      {

         m_pfontlist = Session.get_single_column_font_list();

      }
      else if (etype == ::draw2d::font_list::type_wide)
      {

         if (m_pfontlist.is_null() || m_pfontlist->m_etype != ::draw2d::font_list::type_wide)
         {

            m_pfontlist = __create_new < ::draw2d::font_list >();

            m_pfontlist->m_etype = ::draw2d::font_list::type_wide;

         }

         m_pfontlist->m_puserinteraction = this;

      }
      else
      {

         __throw(todo());

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

      ::user::combo_list::_001OnTimer(ptimer);

   }


   void font_list::_001OnLButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      auto item = hit_test(pmouse);

      Session.user()->set_mouse_focus_LButtonDown(this);

      if (item.m_iItem != m_pfontlist->m_iSel)
      {

         m_pfontlist->m_iSel = (index) item.m_iItem;

         set_need_redraw();

         auto iItem = item.m_iItem;

         if(iItem >= 0 && iItem < m_pfontlist->m_pfontenumeration->m_pitema->get_count())
         {

            m_pfontlist->m_strFontFamily = m_pfontlist->m_pfontenumeration->m_pitema->element_at((::index) iItem)->m_strName;

         }

         ::user::control_event ev;

         ev.m_puie = this;

         ev.m_eevent = ::user::event_after_change_cur_sel;

         ev.m_actioncontext = ::source_user;

         ev.m_item = item;

         ev.m_id = m_idView;

         route_control_event(&ev);

         pmouse->m_lresult = 0;

         pmouse->m_bRet = true;

      }

   }


   void font_list::_001OnMouseMove(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      auto item = hit_test(pmouse);

      if (m_pfontlist->m_iHover != item.m_iItem)
      {

         m_pfontlist->m_iHover = item.item_index();

         auto iItem = item.m_iItem;

         if(iItem >= 0 && iItem < m_pfontlist->m_pfontenumeration->m_pitema->get_count())
         {

            m_pfontlist->m_strFontFamily = m_pfontlist->m_pfontenumeration->m_pitema->element_at((::index) iItem)->m_strName;

         }

         ::user::control_event ev;

         ev.m_puie = this;

         ev.m_eevent = ::user::event_after_change_cur_hover;

         ev.m_actioncontext = ::source_user;

         ev.m_id = m_idView;

         route_control_event(&ev);

         set_need_redraw();

      }

   }


   void font_list::update(::update * pupdate)
   {

      combo_list::update(pupdate);

   }


   void font_list::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnNcDraw(pgraphics);

   }


   void font_list::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {


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

      sync_lock sl(m_pfontlist->mutex());

      //m_pgraphics = pgraphics;

      if (m_pfontlist->m_strText != m_pfontlist->m_strTextLayout)
      {

         m_pfontlist->m_strTextLayout = m_pfontlist->m_strText;

         on_layout(pgraphics);

      }

      auto rectClient = get_client_rect();

      if (m_pfontlist->m_etype != ::draw2d::font_list::type_wide)
      {

         auto pstyle = get_style(pgraphics);

         color colorBackground = get_color(pstyle, ::user::element_background);

         auto rectBackground(rectClient);

         rectBackground += m_pointScroll;

         pgraphics->fill_rect(rectBackground, colorBackground);

      }

      //auto pstyle = m_pfontlist->m_puserstyle;

      //m_pfontlist->m_puserstyle = this;

      m_pfontlist->_001OnDraw(pgraphics);

      //m_pfontlist->m_puserstyle = pstyle;

   }


   void font_list::query_full_size(::draw2d::graphics_pointer & pgraphics, LPSIZE psize)
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

      ::rect rect;

      if (m_pfontlist->get_box_rect(rect, iSel) && rect.area() > 0)
      {

         ::rect rectImpact;

         get_client_rect(rectImpact);

         rectImpact.offset(m_pointScroll);

         if (!rectImpact.contains(rect))
         {

            m_pointScroll.y = (rect.top + rect.bottom - rectImpact.height()) / 2;

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

      sync_lock sl(m_pfontlist->mutex());

      if (m_pfontlist->m_etype != ::draw2d::font_list::type_wide)
      {

         rectFontList.right -= GetSystemMetrics(SM_CXVSCROLL);

      }

      rectFontList.bottom -= GetSystemMetrics(SM_CYHSCROLL);

      m_pfontlist->m_rectClient = rectFontList;

      m_pfontlist->layout();

      m_sizeTotal = m_pfontlist->m_size;

      on_change_view_size();

      ::user::interaction::on_layout(pgraphics);

   }


   string font_list::get_cur_sel_face_name()
   {

      auto item = current_item();

      if (!item.is_set())
      {

         return "";

      }

      sync_lock sl(m_pfontlist->mutex());

      return m_pfontlist->m_plistdata->element_at(item)->m_strFont;

   }


   string font_list::get_cur_hover_face_name()
   {

      auto item = hover_item();

      if (!item.is_set())
      {

         return "";

      }

      sync_lock sl(m_pfontlist->mutex());

      return m_pfontlist->m_plistdata->element_at(item)->m_strFont;

   }


   item font_list::current_item()
   {

      sync_lock sl(m_pfontlist->mutex());

      if (m_pfontlist->m_iSel < 0)
      {

         return -1;

      }

      if (m_pfontlist->m_iSel >= m_pfontlist->m_plistdata->get_count())
      {

         return -1;

      }

      return m_pfontlist->m_iSel;

   }


   item font_list::hover_item()
   {

      sync_lock sl(m_pfontlist->mutex());

      if (m_pfontlist->m_iHover < 0)
      {

         return -1;

      }

      if (m_pfontlist->m_iHover >= m_pfontlist->m_plistdata->get_count())
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


   void font_list::_001OnClose(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      display(display_none);

   }


   void font_list::_001OnShowWindow(::message::message * pmessage)
   {

      SCAST_PTR(::message::show_window, pshowwindow, pmessage);

      if (pshowwindow->m_bShow)
      {

         if (!m_bFirstShown)
         {

            m_bFirstShown = true;

            fork([this]()
               {

                  Session.runall(e_procedure_font_change);

               });

         }

      }
      else
      {

         auto iItem = current_item().m_iItem;

         if(iItem >= 0 && iItem < m_pfontlist->m_pfontenumeration->m_pitema->get_count())
         {

            m_pfontlist->m_strFontFamily = m_pfontlist->m_pfontenumeration->m_pitema->element_at((::index) iItem)->m_strName;

         }

      }

   }


   void font_list::_001EnsureVisible(index iItem)
   {

      if (m_pfontlist.is_set()
         && iItem >= 0
         && iItem < m_pfontlist->m_plistdata->get_size())
      {

         m_pfontlist->m_iSel = iItem;

         m_pointScroll.y = m_pfontlist->m_plistdata->element_at(iItem)->m_box[0].m_rect.top;

      }
      else
      {

         ::user::combo_list::_001EnsureVisible(iItem);

      }

   }


} // namespace user



