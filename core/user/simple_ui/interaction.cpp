#include "framework.h" 
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple_ui/_simple_ui.h"
#endif


namespace simple_ui
{


//   byte brate(double dRate, double dMin, double dMax)
//   {
//
//      return (byte)(dRate * (dMax - dMin) + dMin);
//
//   }
//
//
//   interaction::interaction():
//      ::object(get_object()),
//      ::user::interaction(get_object())
//
//   {
//
//      m_iIndex = -1;
//      //m_eelementHover = ::user::e_element_none;
//
//   }
//
//
//   interaction::~interaction()
//   {
//   }
//
//
//   void interaction::install_message_routing(::channel * pchannel)
//   {
//
//      ::user::interaction::install_message_routing(pchannel);
//
//      MESSAGE_LINK(e_message_show_window, pchannel, this, &::user::interaction::_001OnShowWindow);
//
//   }
//   
//   
//   void interaction::install_simple_ui_default_mouse_handling(::channel * pchannel)
//   {
//      
//      MESSAGE_LINK(e_message_left_button_down  , pchannel, this, &interaction::_001OnLButtonDown);
//      MESSAGE_LINK(e_message_left_button_up    , pchannel, this, &interaction::_001OnLButtonUp);
//      MESSAGE_LINK(e_message_middle_button_down  , pchannel, this, &interaction::_001OnMButtonDown);
//      MESSAGE_LINK(e_message_middle_button_up    , pchannel, this, &interaction::_001OnMButtonUp);
//      MESSAGE_LINK(e_message_mouse_move    , pchannel, this, &interaction::_001OnMouseMove);
//      MESSAGE_LINK(e_message_mouse_leave   , pchannel, this, &interaction::_001OnMouseLeave);
//
//   }
//
//
//   void interaction::_001OnShowWindow(::message::message * pmessage)
//   {
//
//      UNREFERENCED_PARAMETER(pmessage);
//      //SCAST_PTR(::message::show_window, pshowwindow, pmessage);
//
//
//
//   }
//
//
//   bool interaction::simple_process_system_message(::message::message * pmessage, ::user::enum_event eevent)
//   {
//
//      SCAST_PTR(::message::base, pbase, pmessage);
//
//      if (eevent == ::user::event_button_down)
//      {
//
//         psession->m_puiLastLButtonDown = this;
//
//      }
//
//      ::user::control_event ev;
//
//      ev.m_puie = this;
//
//      ev.m_eevent = eevent;
//
//      ev.m_pmessage = pmessage;
//
//      on_control_event(&ev);
//
//      pmessage->m_bRet = ev.m_bRet;
//
//      if (pmessage->m_bRet)
//      {
//
//         if (pbase != nullptr)
//         {
//
//            pbase->set_lresult(1);
//
//         }
//
//      }
//
//      return ev.m_bRet;
//
//   }
//
//
//   void interaction::_001OnLButtonDown(::message::message * pmessage)
//   {
//
//      SCAST_PTR(::message::mouse, pmouse, pmessage);
//
//      if (!is_window_enabled())
//      {
//
//         return;
//
//      }
//
//      auto point = screen_to_client(pmouse->m_point);
//
//      m_itemLButtonDown = hit_test(pmouse);
//
//      if (m_itemLButtonDown)
//      {
//
//         psession->m_puiLastLButtonDown = this;
//
//         pmouse->m_bRet = true;
//
//      }
//      else
//      {
//
//         if (pmessage->previous())
//         {
//
//            return;
//
//         }
//
//         if (!simple_process_system_message(pmessage, ::user::event_button_down))
//         {
//
//            pmouse->m_bRet = true;
//
//         }
//
//      }
//
//   }
//
//
//   void interaction::_001OnMButtonDown(::message::message * pmessage)
//   {
//
//      SCAST_PTR(::message::mouse, pmouse, pmessage);
//
//      pmessage->previous();
//
//      auto point = screen_to_client(pmouse->m_point);
//
//      if (hit_test(pmouse->)
//      {
//
//         if (!simple_process_system_message(pmessage, ::user::event_m_button_down))
//         {
//
//            pmouse->m_bRet = true;
//
//         }
//
//      }
//
//   }
//
//
//   void interaction::_001OnMButtonUp(::message::message * pmessage)
//   {
//
//      SCAST_PTR(::message::mouse, pmouse, pmessage);
//
//      pmessage->previous();
//
//      auto point = screen_to_client(pmouse->m_point);
//
//      if (hit_test(pmouse->)
//      {
//
//         if (!simple_process_system_message(pmessage, ::user::event_m_button_up))
//         {
//
//            pmouse->m_bRet = true;
//
//         }
//
//      }
//
//   }
//
//
//   void interaction::_001OnLButtonUp(::message::message * pmessage)
//   {
//
//      SCAST_PTR(::message::mouse, pmouse, pmessage);
//
//      if (!is_window_enabled())
//      {
//
//         return;
//
//      }
//
//      auto point = screen_to_client(pmouse->m_point);
//
//      auto item = hit_test(pmouse);
//      
//      //int iSize = sizeof(::user::ITEM);
//      
//      //int iCmp = memcmp(&m_itemLButtonDown, &item, iSize);
//
//      if (m_itemLButtonDown == item)
//      {
//
//         psession->m_puiLastLButtonDown = nullptr;
//
//         pmessage->m_bRet = on_click(item);
//
//         if (pmessage->m_bRet)
//         {
//
//            pmouse->set_lresult(1);
//
//         }
//         else
//         {
//
//            ::user::control_event ev;
//
//            ev.m_puie = this;
//
//            ev.m_id = m_id;
//
//            ev.m_eevent = ::user::event_button_clicked;
//
//            ev.m_pmessage = pmouse->
//
//            ev.m_item = item;
//
//            ev.m_context.add(::source_user);
//
//            on_control_event(&ev);
//
//            pmessage->m_bRet = ev.m_bRet;
//
//            if (!pmessage->m_bRet)
//            {
//
//               ::user::command command;
//
//               command.m_id = m_id;
//
//               command.m_puiOther = this;
//
//               route_command_message(&command);
//
//               pmessage->m_bRet = command.m_bRet;
//
//            }
//
//            if (pmessage->m_bRet)
//            {
//
//               pmouse->set_lresult(1);
//
//            }
//
//         }
//
//      }
//
//   }
//
//
//   void interaction::_001OnMouseMove(::message::message * pmessage)
//   {
//
//      SCAST_PTR(::message::mouse, pmouse, pmessage);
//
//      if (!is_window_enabled())
//      {
//
//         return;
//
//      }
//
//      auto point = screen_to_client(pmouse->m_point);
//
//      auto item = hit_test(pmouse);
//
//      if (item != m_itemHover)
//      {
//
//         auto itemOldHover = m_itemHover;
//
//         m_itemHover = item;
//
//         set_need_redraw();
//
//         if (item)
//         {
//
//            track_mouse_hover();
//
//         }
//
//         if (!itemOldHover)
//         {
//
//            ::user::control_event ev;
//
//            ev.m_puie = this;
//
//            ev.m_eevent = ::user::event_mouse_enter;
//
//            on_control_event(&ev);
//
//         }
//         else if (!item)
//         {
//
//            ::user::control_event ev;
//
//            ev.m_puie = this;
//
//            ev.m_eevent = ::user::event_mouse_leave;
//
//            on_control_event(&ev);
//
//         }
//
//      }
//
//      pmessage->m_bRet = false;
//
//   }
//
//
//   void interaction::_001OnMouseLeave(::message::message * pmessage)
//   {
//
//      SCAST_PTR(::message::base, pbase, pmessage);
//
//      auto itemOldHover = m_itemHover;
//
//      m_itemHover = ::user::e_element_none;
//
//      if (itemOldHover)
//      {
//
//         set_need_redraw();
//
//         ::user::control_event ev;
//
//         ev.m_puie = this;
//
//         ev.m_eevent = ::user::event_mouse_leave;
//
//         on_control_event(&ev);
//
//      }
//
//      pbase->m_bRet = false;
//
//   }
//
//
//   ::user::item interaction::hit_test(::message::mouse* pmouse->
//   {
//
//      auto point = pmouse->m_point;
//
//      screen_to_client(point);
//
//      point += m_ptScroll;
//
//
//   }
//
//   void interaction::on_hit_test(::user::item & item)
//   {
//
//      auto rect = this->rect(::user::e_element_client);
//
//      if (!rect.contains(point))
//      {
//
//         return ::user::e_element_none;
//
//      }
//
//      return ::user::e_element_client;
//
//   }
//
//
//   bool interaction::get_rect(::rect & rect, const ::user::item& item)
//   {
//
//      if (!item)
//      {
//
//         return false;
//
//      }
//
//      rect = get_client_rect();
//
//      return true;
//
//   }
//
//
//   bool interaction::on_action(const char * pszId)
//   {
//
//      ::user::interaction * pinteraction = GetTypedParent < ::user::interaction >();
//
//      if (pinteraction != nullptr)
//      {
//
//         if(pinteraction->on_action(pszId))
//            return true;
//
//      }
//
//      return false;
//
//   }
//
//
//
//   bool interaction::keyboard_focus_is_focusable()
//   {
//
//      return false;
//
//   }
//
//
////   ::user::style * interaction::get_user_style()
////   {
////
////      if (m_puserstyle != nullptr)
////         return m_puserstyle;
////
////      if (GetTypedParent < ::user::interaction >() == nullptr)
////         return nullptr;
////
////      return GetTypedParent < ::user::interaction >()->get_style();
////
////   }
//
//
//   void interaction::simple_ui_draw_back_01_old(::rect rect, ::draw2d::graphics_pointer & pgraphics)
//   {
//
//      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//      color32_t crOut;
//
//      color32_t crIn;
//
//      /*   if (eschema == ::hotplugin::plugin::schema_darker)
//         {
//
//         crOut = ARGB(0, 90, 90, 80);
//
//         crIn = ARGB(133, 90, 90, 80);
//
//         }
//         else*/
//      {
//
//         crOut = ARGB(0, 255, 255, 233);
//
//         crIn = ARGB(133, 255, 255, 233);
//
//      }
//
//      i32 iBorderH = min(rect.height() / 2, 49);
//
//      ::draw2d::brush_pointer br(e_create);
//
//      br->CreateLinearGradientBrush(rect.top_left(), point(rect.left, rect.top + iBorderH), crOut, crIn);
//
//      pgraphics->fill_rect(::rect(rect.left, rect.top, (i32)rect.width(), iBorderH), br);
//
//      br->create_solid(crIn);
//
//      pgraphics->fill_rect(::rect(rect.left, rect.top + iBorderH, (i32)rect.width(), (i32)rect.height() - (iBorderH * 2)), br);
//
//      br->CreateLinearGradientBrush(point(rect.left, rect.bottom - iBorderH), rect.bottom_left(), crIn, crOut);
//
//      pgraphics->fill_rect(::rect(rect.left, rect.bottom - iBorderH, (i32)rect.width(), iBorderH), br);
//
//   }
//
//
//   void interaction::simple_ui_draw_back_01_new(::rect rect, ::draw2d::graphics_pointer & pgraphics)
//   {
//
//      /*simple_solid_brush br(g, ARGB(255, 255, 255, 255));
//
//      simple_pen pen;
//
//      pen.create_solid(ARGB(255, 0, 0, 0));
//
//      pgraphics->select(br);
//
//      pgraphics->select(pen);
//
//      m_rect.deflate(0, 0, 1, 1);
//
//      pgraphics->rectangle(m_rect);*/
//
//      //pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);
//
//      //pgraphics->fill_rect(rect,ARGB(0,0,0,0));
//
//   }
//
//
//   void interaction::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      ::user::interaction::_001OnNcDraw(pgraphics);
//
//      if(m_flagNonClient.has(non_client_focus_rect) && keyboard_focus_is_focusable())
//      {
//
//         simple_ui_draw_focus_rect(pgraphics);
//
//      }
//
//   }
//
//
//   void interaction::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      ::user::interaction::_001OnDraw(pgraphics);
//
//   }
//
//
//   bool interaction::has_text_input()
//   {
//
//      return false;
//
//   }
//
//
//   color32_t interaction::get_action_hover_border_color()
//   {
//
//      return _001GetColor(::user::color_action_hover_border_color);
//
//   }
//
//
//   void interaction::simple_ui_draw_focus_rect(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      userstyle()->simple_ui_draw_focus_rect(this,graphics);
//
//   }
//
//
//   void interaction::simple_ui_draw_frame_window_rect(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      ::rect rectClient;
//
//      get_client_rect(rectClient);
//
//      rectClient.deflate(0,0,1,1);
//
//      ::draw2d::brush_pointer b(e_create);
//
//      b->create_solid(ARGB(255, 255, 255, 255));
//
//      pgraphics->set(b);
//
//      ::draw2d::pen_pointer point(e_create);
//
//      point->create_solid(1.0, ARGB(255, 0, 0, 0));
//
//      pgraphics->set(point);
//
//      pgraphics->rectangle(rectClient);
//
//   }
//
//
//   void interaction::simple_ui_draw_fuzzy_color_spread(::draw2d::graphics_pointer & pgraphics)
//   {
//      /*
//      ::rect rectWindow;
//
//      get_window_rect(rectWindow);
//
//      int i = 0;
//      int j = 0;
//      int iCount = rectWindow.width();
//      int jCount = rectWindow.height();
//
//      byte * point = (byte *)m_pimage->get_data();
//
//      for (i = 0; i < iCount; i++)
//      {
//      for (j = 0; j < jCount; j++)
//      {
//      double dPhase = fmod((((double) ::get_tick() * 360 * 0.5984 / 1000.0) + (i * 360.0 / (double)iCount) + (j * 360.0 / (double)jCount) + ((double)(sin(((double) ::get_tick() * 3.1415 * 2.0  *0.0484 / 1000.0) + i * 3.1415 * 2.0 * 2.0 / (double)(iCount)) * sin(((double) ::get_tick() * 3.1415 * 2.0  * 0.0484 / 1000.0) + j * 3.1415 * 2.0 * 2.0 / (double)(jCount)) * 360))), 360.0);
//      i32 iR;
//      i32 iG;
//      i32 iB;
//      double dRate = fmod(dPhase, 60.0) / 60.0;
//      i32 iColor = (i32)(dRate * 155.0);
//      if (dPhase < 60)
//      {
//      // purple to blue
//      iR = 255 - iColor;
//      iG = 100;
//      iB = 255;
//      }
//      else if (dPhase < (120))
//      {
//      // blue to cyan
//      iR = 100;
//      iG = 100 + iColor;
//      iB = 255;
//      }
//      else if (dPhase < (180))
//      {
//      // cyan to green
//      iR = 100;
//      iG = 255;
//      iB = 255 - iColor;
//      }
//      else if (dPhase < (240))
//      {
//      // green to yellow
//      iR = 100 + iColor;
//      iG = 255;
//      iB = 100;
//      }
//      else if (dPhase < (300))
//      {
//      // yellow to red
//      iR = 255;
//      iG = 255 - iColor;
//      iB = 100;
//      }
//      else
//      {
//      // red to purple
//      iR = 255;
//      iG = 100;
//      iB = 100 + iColor;
//      }
//
//      point[0] = iR;
//      point[1] = iG;
//      point[2] = iB;
//      point[3] = 84;
//      point += 4;
//
//      }
//      }
//      */
//
//
//   }
//
//
//   void interaction::simple_ui_draw_dark_glass(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      ::rect rectWindow;
//
//      get_client_rect(rectWindow);
//
//      pgraphics->fill_rect(rectWindow, ARGB(90, 127, 127, 127));
//
//   }
//
//
//
//   void interaction::simple_ui_draw_pestana(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      ::rect rectWindow;
//
//      get_client_rect(rectWindow);
//
//      pgraphics->set_alpha_mode(draw2d::alpha_mode_blend);
//
//      int iCount = rectWindow.height();
//      ::draw2d::pen_pointer point(e_create);
//      for (int i = 0; i < iCount; i += 2)
//      {
//         double dRate = (double)i / (double)iCount;
//         dRate = 1.0 - dRate;
//         byte a1 = brate(1.0 - dRate, 23, 90);
//         byte r1 = brate(dRate, 23, 127);
//         byte g1 = brate(dRate, 23, 127);
//         byte b1 = brate(dRate, 23, 127);
//         point->create_solid(1.0, ARGB(a1, r1, g1, b1));
//         pgraphics->set(point);
//         pgraphics->draw_line(rectWindow.left, i, rectWindow.right, i);
//
//      }
//
//
//   }
//
//
//
//   void interaction::simple_ui_draw_auth_box(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      ::rect rect;
//
//      get_client_rect(rect);
//
//      pgraphics->set_alpha_mode(draw2d::alpha_mode_blend);
//
//      // front
//      point pa[4];
//      //  0       1
//      //
//      //
//      //  3       2
//
//      // back
//      point pb[4];
//
//
//      // guards
//      point pc[4];
//
//
//      pa[0].x = rect.left;
//      pa[0].y = rect.top;
//      pa[1].x = rect.right - rect.width() / 10;
//      pa[1].y = rect.top + rect.height() / 10;
//      pa[2].x = rect.right - rect.width() / 8;
//      pa[2].y = rect.bottom - rect.height() / 10;
//      pa[3].x = rect.left;
//      pa[3].y = rect.bottom;
//
//
//      pb[0].x = rect.left + rect.width() / 6;
//      pb[0].y = rect.top + rect.height() / 6;
//      pb[1].x = rect.right - rect.width() / 6;
//      pb[1].y = rect.top + rect.height() / 6;
//      pb[2].x = rect.right - rect.width() / 5;
//      pb[2].y = rect.bottom - rect.height() / 4;
//      pb[3].x = rect.left + rect.width() / 5;
//      pb[3].y = rect.bottom - rect.height() / 4;
//
//      {
//
//         ::draw2d::brush_pointer b(e_create);
//
//         b->create_solid(ARGB(192, 220, 220, 220));
//
//         pgraphics->set(b);
//
//         pgraphics->fill_polygon(pb, 4);
//
//         ::draw2d::pen_pointer point(e_create);
//
//         point->create_solid(1.0, ARGB(192, 192, 192, 192));
//
//         pgraphics->set(point);
//
//         pgraphics->draw_polygon(pb, 4);
//
//
//      }
//
//
//
//
//
//
//
//
//
//
//
//
//
//      // top
//      ::memcpy_dup(pc, pa, sizeof(pb));
//      pc[2].x = pb[1].x;
//      pc[2].y = pb[1].y;
//      pc[3].x = pb[0].x;
//      pc[3].y = pb[0].y;
//
//      {
//
//         ::draw2d::brush_pointer b(e_create);
//
//         b->create_solid(ARGB(180, 210, 210, 210));
//
//         pgraphics->set(b);
//
//         pgraphics->fill_polygon(pc, 4);
//
//         ::draw2d::pen_pointer point(e_create);
//
//         point->create_solid(1.0, ARGB(180, 180, 177, 177));
//
//         pgraphics->set(point);
//
//         pgraphics->draw_polygon(pc, 4);
//
//
//      }
//      // left
//      ::memcpy_dup(pc, pa, sizeof(pb));
//      pc[1].x = pb[0].x;
//      pc[1].y = pb[0].y;
//      pc[2].x = pb[3].x;
//      pc[2].y = pb[3].y;
//      {
//
//         ::draw2d::brush_pointer b(e_create);
//
//         b->create_solid(ARGB(123, 120, 120, 123));
//
//         pgraphics->set(b);
//
//         pgraphics->fill_polygon(pc, 4);
//
//         ::draw2d::pen_pointer point(e_create);
//
//         point->create_solid(1.0, ARGB(123, 90, 90, 90));
//
//         pgraphics->set(point);
//
//         pgraphics->draw_polygon(pc, 4);
//
//
//      }
//      // bottom
//      ::memcpy_dup(pc, pa, sizeof(pb));
//      pc[0].x = pb[3].x;
//      pc[0].y = pb[3].y;
//      pc[1].x = pb[2].x;
//      pc[1].y = pb[2].y;
//      {
//
//         ::draw2d::brush_pointer b(e_create);
//
//         b->create_solid(ARGB(149, 192, 192, 192));
//
//         pgraphics->set(b);
//
//         pgraphics->fill_polygon(pc, 4);
//
//         ::draw2d::pen_pointer point(e_create);
//
//         point->create_solid(1.0, ARGB(149, 176, 176, 176));
//
//         pgraphics->set(point);
//
//         pgraphics->draw_polygon(pc, 4);
//
//
//      }
//      // right
//      ::memcpy_dup(pc, pa, sizeof(pb));
//      pc[0].x = pb[1].x;
//      pc[0].y = pb[1].y;
//      pc[3].x = pb[2].x;
//      pc[3].y = pb[2].y;
//      {
//
//         ::draw2d::brush_pointer b(e_create);
//
//         b->create_solid(ARGB(90, 150, 149, 149));
//
//         pgraphics->set(b);
//
//         pgraphics->fill_polygon(pc, 4);
//
//         ::draw2d::pen_pointer point(e_create);
//
//         point->create_solid(1.0, ARGB(90, 120, 120, 123));
//
//         pgraphics->set(point);
//
//         pgraphics->draw_polygon(pc, 4);
//
//
//      }
//
//
//
//
//
//      {
//
//         ::draw2d::pen_pointer point(e_create);
//
//         point->create_solid(1.0, ARGB(190, 90, 90, 90));
//
//         pgraphics->set(point);
//
//         pgraphics->draw_polygon(pa, 4);
//
//      }
//
//
//   }
//
//
//   //void interaction::on_hit_test(::user::item & item)
//   //{
//
//   //   auto rectClient = get_client_rect();
//
//   //   if (!rectClient.contains(point))
//   //   {
//
//   //      return ::user::e_element_none;
//
//   //   }
//
//   //   return ::user::e_element_client;
//
//   //}
//

} // namespace simple_ui



