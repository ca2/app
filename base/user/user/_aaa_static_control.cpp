#include "framework.h"
//#if !BROAD_PRECOMPILED_HEADER
////#include "base/user/user/_component.h"
//#endif
//#include "aura/graphics/draw2d/graphics.h"
//#include "static_control.h"
//#include "aura/user/user/style.h"
//#include "base/platform/session.h"
//
//
//namespace user
//{
//
//
//   static_control::static_control()
//   {
//
//      m_econtroltype = e_control_type_static;
//
//      m_etype = type_text;
//
//      m_bLButtonDown = false;
//
//      m_bHover = false;
//
//   }
//
//
//   static_control::~static_control()
//   {
//
//      destroy_window();
//
//   }
//
//
//
//   //bool static_control::create_interaction(::user::interaction * puiParent,atom atom)
//   //{
//
//   //   return ::user::interaction::create_interaction(puiParent, atom);
//
//   //}
//
//
//   ::write_text::font_pointer static_control::get_font(style * pstyle, enum_element eelement, ::user::enum_state estate) const
//   {
//
//      if (pstyle)
//      {
//
//         if (pstyle->m_pfontStill)
//         {
//
//            return pstyle->m_pfontStill;
//
//         }
//
//         if (pstyle->m_pfont)
//         {
//
//            return pstyle->m_pfont;
//
//         }
//
//      }
//
//      return nullptr;
//
//   }
//
//
//   void static_control::install_message_routing(::channel * pchannel)
//   {
//
//      ::user::interaction::install_message_routing(pchannel);
//
//      MESSAGE_LINK(e_message_create, pchannel, this, &static_control::on_message_create);
//      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &static_control::on_message_left_button_down);
//      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &static_control::on_message_left_button_up);
//      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &static_control::on_message_mouse_leave);
//      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &static_control::on_message_mouse_move);
//
//   }
//
//   void static_control::on_message_create(::message::message * pmessage)
//   {
//
//      //descriptor().set_control_type(e_control_type_static);
//
//      pmessage->previous();
//
//      if (pmessage->m_bRet)
//         return;
//
//   }
//
//   void static_control::on_message_left_button_down(::message::message * pmessage)
//   {
//
////      auto pmouse = pmessage->m_union.m_pmouse;
//      __UNREFERENCED_PARAMETER(pmessage);
//
//      m_bLButtonDown = true;
//
//   }
//
//
//   void static_control::on_message_left_button_up(::message::message * pmessage)
//   {
//
////      auto pmouse = pmessage->m_union.m_pmouse;
//      __UNREFERENCED_PARAMETER(pmessage);
//
//      if (m_bLButtonDown)
//      {
//
//         m_bLButtonDown = false;
//
//         auto ptopic = create_topic(id_click);
//
//         ptopic->m_puserelement = this;
//         ptopic->m_actioncontext = ::e_source_user;
//
//         route(ptopic);
//
//      }
//
//
//   }
//
//   void static_control::on_message_mouse_move(::message::message * pmessage)
//   {
//
////      auto pmouse = pmessage->m_union.m_pmouse;
//      __UNREFERENCED_PARAMETER(pmessage);
//   }
//
//
//   void static_control::on_message_mouse_leave(::message::message * pmessage)
//   {
//
////      ::pointer<::message::mouse>pleave(pmessage);
//      __UNREFERENCED_PARAMETER(pmessage);
//
//      m_bLButtonDown = false;
//
//   }
//
//   void static_control::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
//   {
//
//
//
//      ::color::color crText = argb(255, 0, 0, 0);
//
//      if(m_bHover)
//      {
//
//         auto pointCursor = get_cursor_position();
//
//         ::int_rectangle rectangleWindow;
//
//         window_rectangle(rectangleWindow);
//
//         if(rectangleWindow.contains(pointCursor))
//         {
//
//            crText = ::rgba(255, 0, 0, 0);
//
//         }
//         else
//         {
//
//            crText = ::rgba(255, 0, 0, 0);
//
//         }
//
//      }
//      else
//      {
//
//         crText = ::rgba(255, 0, 0, 0);
//
//      }
//
//      pgraphics->set_text_color(crText);
//
//      pgraphics->set_font(this, ::e_element_none);
//
//      pgraphics->text_out(0, 0, get_window_text());
//
//   }
//
//
////   bool static_control::OnChildNotify(::user::message * pusermessage)
////   {
////
////#ifdef WINDOWS_DESKTOP
////
////      if (pusermessage->m_atom != WM_DRAWITEM)
////         return ::user::interaction::OnChildNotify(pusermessage);
////
////#ifdef WINDOWS_DESKTOP
////
//////      DrawItem((LPDRAWITEMSTRUCT)pusermessage->m_lparam);
////
////#endif
////
////#endif
////
////      return true;
////
////   }
//
//
//   void static_control::static_set_icon(::image::icon * picon)
//   {
//
//      if(picon == nullptr)
//         return;
//
//      m_etype = type_icon;
//
//      m_picon = picon;
//
//   }
//
//
//   ::image::icon * static_control::static_get_icon()
//   {
//
//      return m_etype == type_icon ? m_picon : nullptr;
//
//   }
//
//
////#ifdef WINDOWS_DESKTOP
////
////
////   HENHMETAFILE static_control::SetEnhMetaFile(HENHMETAFILE hMetaFile)
////   {
////
////      //ASSERT(is_window());
////
////      //return (HENHMETAFILE)send_message( STM_SETIMAGE, IMAGE_ENHMETAFILE, (LPARAM)hMetaFile);
////
////      return nullptr;
////
////   }
////
////
////   HENHMETAFILE static_control::GetEnhMetaFile()
////   {
////
////      //ASSERT(is_window());
////
////      //return (HENHMETAFILE)send_message( STM_GETIMAGE, IMAGE_ENHMETAFILE, 0L);
////
////      return nullptr;
////
////   }
////
////
////#endif
//
//
//   void static_control::static_set_bitmap(::draw2d::bitmap * pbitmap)
//   {
//
//
//      if(pbitmap == nullptr)
//         return;
//
//      m_etype = type_icon;
//
//      m_pbitmap = pbitmap;
//
//
//   }
//
//
//   ::draw2d::bitmap * static_control::static_get_bitmap()
//   {
//
//      return m_etype == type_bitmap ? m_pbitmap : nullptr;
//
//   }
//
//
//   void static_control::static_set_cursor(::image::cursor * pcursor)
//   {
//
//      if(pcursor == nullptr)
//         return;
//
//      m_etype = type_cursor;
//
//      m_pcursor = pcursor;
//
//   }
//
//
//   ::image::cursor *  static_control::static_get_cursor()
//   {
//
//      return m_etype == type_cursor ? m_pcursor : nullptr;
//
//   }
//
//   ::user::static_control::enum_type static_control::get_type()
//   {
//
//      return m_etype;
//
//   }
//
//
//} // namespace user
//
//
//
//
//
//
//
