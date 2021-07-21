#include "framework.h" 
#include "core/user/simple_ui/_simple_ui.h"

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
//      ::object(this),
//      ::user::interaction(this)
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
//      MESSAGE_LINK(e_message_show_window, pchannel, this, &::user::interaction::on_message_show_window);
//
//   }
//   
//   
//   void interaction::install_simple_ui_default_mouse_handling(::channel * pchannel)
//   {
//      
//      MESSAGE_LINK(e_message_left_button_down  , pchannel, this, &interaction::on_message_left_button_down);
//      MESSAGE_LINK(e_message_left_button_up    , pchannel, this, &interaction::on_message_left_button_up);
//      MESSAGE_LINK(e_message_middle_button_down  , pchannel, this, &interaction::on_message_middle_button_down);
//      MESSAGE_LINK(e_message_middle_button_up    , pchannel, this, &interaction::on_message_middle_button_up);
//      MESSAGE_LINK(e_message_mouse_move    , pchannel, this, &interaction::on_message_mouse_move);
//      MESSAGE_LINK(e_message_mouse_leave   , pchannel, this, &interaction::on_message_mouse_leave);
//
//   }
//
//
//   void interaction::on_message_show_window(::message::message * pmessage)
//   {
//
//      UNREFERENCED_PARAMETER(pmessage);
//      //__pointer(::message::show_window) pshowwindow(pmessage);
//
//
//
//   }
//
//
//   bool interaction::simple_process_system_message(::message::message * pmessage, ::user::enum_event eevent)
//   {
//
//      __pointer(::user::message) pusermessage(pmessage);
//
//      if (eevent == ::user::e_event_button_down)
//      {
//
//         psession->m_puiLastLButtonDown = this;
//
//      }
//
//      ::user::control_event ev;
//
//      ev.m_puserinteraction = this;
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
//         if (pusermessage != nullptr)
//         {
//
//            pusermessage->set_lresult(1);
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
//   void interaction::on_message_left_button_down(::message::message * pmessage)
//   {
//
//      auto pmouse = pmessage->m_pmouse;
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
//         if (!simple_process_system_message(pmessage, ::user::e_event_button_down))
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
//   void interaction::on_message_middle_button_down(::message::message * pmessage)
//   {
//
//      auto pmouse = pmessage->m_pmouse;
//
//      pmessage->previous();
//
//      auto point = screen_to_client(pmouse->m_point);
//
//      if (hit_test(pmouse->)
//      {
//
//         if (!simple_process_system_message(pmessage, ::user::e_event_m_button_down))
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
//   void interaction::on_message_middle_button_up(::message::message * pmessage)
//   {
//
//      auto pmouse = pmessage->m_pmouse;
//
//      pmessage->previous();
//
//      auto point = screen_to_client(pmouse->m_point);
//
//      if (hit_test(pmouse->)
//      {
//
//         if (!simple_process_system_message(pmessage, ::user::e_event_m_button_up))
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
//   void interaction::on_message_left_button_up(::message::message * pmessage)
//   {
//
//      auto pmouse = pmessage->m_pmouse;
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
//            ev.m_puserinteraction = this;
//
//            ev.m_id = m_id;
//
//            ev.m_eevent = ::user::e_event_button_clicked;
//
//            ev.m_pmessage = pmouse->
//
//            ev.m_item = item;
//
//            ev.m_context.add(::e_source_user);
//
//            on_control_event(&ev);
//
//            pmessage->m_bRet = ev.m_bRet;
//
//            if (!pmessage->m_bRet)
//            {
//
//               ::message::command command;
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
//   void interaction::on_message_mouse_move(::message::message * pmessage)
//   {
//
//      auto pmouse = pmessage->m_pmouse;
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
//            ev.m_puserinteraction = this;
//
//            ev.m_eevent = ::user::e_event_mouse_enter;
//
//            on_control_event(&ev);
//
//         }
//         else if (!item)
//         {
//
//            ::user::control_event ev;
//
//            ev.m_puserinteraction = this;
//
//            ev.m_eevent = ::user::e_event_mouse_leave;
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
//   void interaction::on_message_mouse_leave(::message::message * pmessage)
//   {
//
//      __pointer(::user::message) pusermessage(pmessage);
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
//         ev.m_puserinteraction = this;
//
//         ev.m_eevent = ::user::e_event_mouse_leave;
//
//         on_control_event(&ev);
//
//      }
//
//      pusermessage->m_bRet = false;
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
//      auto rectangle = this->rectangle(::user::e_element_client);
//
//      if (!rectangle.contains(point))
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
//   bool interaction::get_rect(::rectangle_i32 & rectangle, const ::user::item& item)
//   {
//
//      if (!item)
//      {
//
//         return false;
//
//      }
//
//      rectangle = get_client_rect();
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
//   void interaction::simple_ui_draw_back_01_old(::rectangle_i32 rectangle, ::draw2d::graphics_pointer & pgraphics)
//   {
//
//      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//      color32_t crOut;
//
//      color32_t crIn;
//
//      /*   if (eschema == ::hotplugin::plugin::schema_darker)
//         {
//
//         crOut = argb(0, 90, 90, 80);
//
//         crIn = argb(133, 90, 90, 80);
//
//         }
//         else*/
//      {
//
//         crOut = argb(0, 255, 255, 233);
//
//         crIn = argb(133, 255, 255, 233);
//
//      }
//
//      i32 iBorderH = minimum(rectangle.height() / 2, 49);
//
//      ::draw2d::brush_pointer br(e_create);
//
//      br->CreateLinearGradientBrush(rectangle.top_left(), point_i32(rectangle.left, rectangle.top + iBorderH), crOut, crIn);
//
//      pgraphics->fill_rectangle(::rectangle_i32(rectangle.left, rectangle.top, (i32)rectangle.width(), iBorderH), br);
//
//      br->create_solid(crIn);
//
//      pgraphics->fill_rectangle(::rectangle_i32(rectangle.left, rectangle.top + iBorderH, (i32)rectangle.width(), (i32)rectangle.height() - (iBorderH * 2)), br);
//
//      br->CreateLinearGradientBrush(point_i32(rectangle.left, rectangle.bottom - iBorderH), rectangle.bottom_left(), crIn, crOut);
//
//      pgraphics->fill_rectangle(::rectangle_i32(rectangle.left, rectangle.bottom - iBorderH, (i32)rectangle.width(), iBorderH), br);
//
//   }
//
//
//   void interaction::simple_ui_draw_back_01_new(::rectangle_i32 rectangle, ::draw2d::graphics_pointer & pgraphics)
//   {
//
//      /*simple_solid_brush br(g, argb(255, 255, 255, 255));
//
//      simple_pen pen;
//
//      pen.create_solid(argb(255, 0, 0, 0));
//
//      pgraphics->select(br);
//
//      pgraphics->select(pen);
//
//      m_rectangle.deflate(0, 0, 1, 1);
//
//      pgraphics->rectangle(m_rectangle);*/
//
//      //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);
//
//      //pgraphics->fill_rectangle(rectangle,argb(0,0,0,0));
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
//      ::rectangle_i32 rectangleClient;
//
//      get_client_rect(rectangleClient);
//
//      rectangleClient.deflate(0,0,1,1);
//
//      ::draw2d::brush_pointer b(e_create);
//
//      b->create_solid(argb(255, 255, 255, 255));
//
//      pgraphics->set(b);
//
//      ::draw2d::pen_pointer point_i32(e_create);
//
//      point_i32->create_solid(1.0, argb(255, 0, 0, 0));
//
//      pgraphics->set(point);
//
//      pgraphics->rectangle(rectangleClient);
//
//   }
//
//
//   void interaction::simple_ui_draw_fuzzy_color_spread(::draw2d::graphics_pointer & pgraphics)
//   {
//      /*
//      ::rectangle_i32 rectWindow;
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
//      point_i32[0] = iR;
//      point_i32[1] = iG;
//      point_i32[2] = iB;
//      point_i32[3] = 84;
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
//      ::rectangle_i32 rectWindow;
//
//      get_client_rect(rectWindow);
//
//      pgraphics->fill_rectangle(rectWindow, argb(90, 127, 127, 127));
//
//   }
//
//
//
//   void interaction::simple_ui_draw_pestana(::draw2d::graphics_pointer & pgraphics)
//   {
//
//      ::rectangle_i32 rectWindow;
//
//      get_client_rect(rectWindow);
//
//      pgraphics->set_alpha_mode(draw2d::e_alpha_mode_blend);
//
//      int iCount = rectWindow.height();
//      ::draw2d::pen_pointer point_i32(e_create);
//      for (int i = 0; i < iCount; i += 2)
//      {
//         double dRate = (double)i / (double)iCount;
//         dRate = 1.0 - dRate;
//         byte a1 = brate(1.0 - dRate, 23, 90);
//         byte r1 = brate(dRate, 23, 127);
//         byte g1 = brate(dRate, 23, 127);
//         byte b1 = brate(dRate, 23, 127);
//         point_i32->create_solid(1.0, argb(a1, r1, g1, b1));
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
//      ::rectangle_i32 rectangle;
//
//      get_client_rect(rectangle);
//
//      pgraphics->set_alpha_mode(draw2d::e_alpha_mode_blend);
//
//      // front
//      point_i32 pa[4];
//      //  0       1
//      //
//      //
//      //  3       2
//
//      // back
//      point_i32 pb[4];
//
//
//      // guards
//      point_i32 pc[4];
//
//
//      pa[0].x = rectangle.left;
//      pa[0].y = rectangle.top;
//      pa[1].x = rectangle.right - rectangle.width() / 10;
//      pa[1].y = rectangle.top + rectangle.height() / 10;
//      pa[2].x = rectangle.right - rectangle.width() / 8;
//      pa[2].y = rectangle.bottom - rectangle.height() / 10;
//      pa[3].x = rectangle.left;
//      pa[3].y = rectangle.bottom;
//
//
//      pb[0].x = rectangle.left + rectangle.width() / 6;
//      pb[0].y = rectangle.top + rectangle.height() / 6;
//      pb[1].x = rectangle.right - rectangle.width() / 6;
//      pb[1].y = rectangle.top + rectangle.height() / 6;
//      pb[2].x = rectangle.right - rectangle.width() / 5;
//      pb[2].y = rectangle.bottom - rectangle.height() / 4;
//      pb[3].x = rectangle.left + rectangle.width() / 5;
//      pb[3].y = rectangle.bottom - rectangle.height() / 4;
//
//      {
//
//         ::draw2d::brush_pointer b(e_create);
//
//         b->create_solid(argb(192, 220, 220, 220));
//
//         pgraphics->set(b);
//
//         pgraphics->fill_polygon(pb, 4);
//
//         ::draw2d::pen_pointer point_i32(e_create);
//
//         point_i32->create_solid(1.0, argb(192, 192, 192, 192));
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
//         b->create_solid(argb(180, 210, 210, 210));
//
//         pgraphics->set(b);
//
//         pgraphics->fill_polygon(pc, 4);
//
//         ::draw2d::pen_pointer point_i32(e_create);
//
//         point_i32->create_solid(1.0, argb(180, 180, 177, 177));
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
//         b->create_solid(argb(123, 120, 120, 123));
//
//         pgraphics->set(b);
//
//         pgraphics->fill_polygon(pc, 4);
//
//         ::draw2d::pen_pointer point_i32(e_create);
//
//         point_i32->create_solid(1.0, argb(123, 90, 90, 90));
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
//         b->create_solid(argb(149, 192, 192, 192));
//
//         pgraphics->set(b);
//
//         pgraphics->fill_polygon(pc, 4);
//
//         ::draw2d::pen_pointer point_i32(e_create);
//
//         point_i32->create_solid(1.0, argb(149, 176, 176, 176));
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
//         b->create_solid(argb(90, 150, 149, 149));
//
//         pgraphics->set(b);
//
//         pgraphics->fill_polygon(pc, 4);
//
//         ::draw2d::pen_pointer point_i32(e_create);
//
//         point_i32->create_solid(1.0, argb(90, 120, 120, 123));
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
//         ::draw2d::pen_pointer point_i32(e_create);
//
//         point_i32->create_solid(1.0, argb(190, 90, 90, 90));
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
//   //   auto rectangleClient = get_client_rect();
//
//   //   if (!rectangleClient.contains(point))
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



