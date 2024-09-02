//
// Created by camilo on 31/01/2022 16:16 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "window_implementation.h"
#include "device.h"
#include "child.h"
#include "button.h"
#include "user.h"
#include "acme/nano/nano.h"
#include "acme/handler/topic.h"
#include "acme/nano/user/font.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/user/user/drag.h"
#include "acme/user/user/tool.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/system.h"
#include "acme/exception/interface_only.h"


namespace nano
{


namespace user
{


window::window()
{
   
   m_bTopMost = false;
   
   m_iFontSize = 14;
   
   m_efont = e_font_sans;
   
   auto pitemClient = tool().defer_item(e_element_client);
   
   enable_drag(pitemClient, ::user::e_zorder_back);
   
   m_bNcActive = false;
   
   m_bStartCentered = false;
   
   m_bArbitraryPositioning = false;
   
   m_bCapture = false;
   
}


window::~window()
{
   
   nano()->user()->m_nanowindowa.erase_item(this);
   
}


//::pointer < item_container > window::item_form()
//{
//
//   return item_container(id_user_interface);
//
//}


void window::on_initialize_particle()
{
   
   ::object::on_initialize_particle();
   
   __construct(m_pimplementation);
   
   m_pimplementation->m_pinterface = this;
   
   system()->m_pnano->user()->m_nanowindowa.add(this);
   
}


void window::draw(::nano::user::device * pnanodevice)
{
   
   ::pointer<::nano::user::pen>pnanopenBorder;
   
   if (is_active())
   {
      
      pnanopenBorder = m_ppenBorderFocus;
      
   }
   else
   {
      
      pnanopenBorder = m_ppenBorder;
      
   }
   
   ::rectangle_i32 rectangleX;
   
   get_client_rectangle(rectangleX);
   
   pnanodevice->rectangle(rectangleX, m_pbrushWindow, pnanopenBorder);
   
   on_draw(pnanodevice);
   
   draw_children(pnanodevice);
   
}


void window::draw_children(::nano::user::device * pnanodevice)
{
   
   for (auto & pchild: m_childa)
   {
      
      pchild->on_draw(pnanodevice);
      
   }
   
}


void window::create()
{
   
   m_pimplementation->create();
   
}


void window::on_create()
{
   
   
}


void window::destroy()
{
   
   if (m_pimplementation)
   {
      
      m_pimplementation->destroy();
      
      m_pimplementation.release();
      
   }
   
   if(m_functionClose)
   {
      
      m_functionClose(this);
      
   }
   
   if (m_psequencer)
   {
      
      m_psequencer->on_sequence();
      
      m_psequencer.release();
      
   }

   if(system()->m_pnano->m_puser)
   {

      system()->m_pnano->m_puser->m_nanowindowa.erase(this);

   }
   
}


void window::display()
{
   
   m_pimplementation->display();
   
}


void window::hide()
{
   
   m_pimplementation->hide();
   
}


void window::message_loop()
{
   
   m_pimplementation->message_loop();
   
}



void window::on_draw(::nano::user::device * pnanodevice)
{
   
   m_pimplementation->draw(pnanodevice);
   
}


void window::on_char(int iChar)
{
   
   if (iChar == '\t' && m_childa.has_element())
   {
      
      auto iFind = m_childa.find_first(m_pchildFocus);
      
      iFind++;
      
      m_pchildFocus = m_childa % iFind;
      
      redraw();
      
   }
   else if (m_pchildFocus)
   {
      
      m_pchildFocus->on_char(iChar);
      
   }
   
}


bool window::is_active()
{
   
   return m_bNcActive;
   
}


void window::set_active()
{
   
   m_pimplementation->set_active();
   
}


void window::delete_drawing_objects()
{
   
   m_pbrushWindow.release();
   
   m_ppenBorder.release();
   
   m_ppenBorder.release();
   
}


bool window::get_dark_mode()
{
   
   return m_pimplementation->get_dark_mode();
   
}


void window::create_drawing_objects()
{
   
   if (!m_pfont)
   {
      
#if REFERENCING_DEBUGGING
      
      ::allocator::add_referer({this, __FUNCTION_FILE_LINE__});
      
#endif
      
      __construct(m_pfont, nullptr);
      
      m_pfont->m_iFontSize = m_iFontSize;
      
      m_pfont->m_strFontName = node()->font_name(m_efont);
      
   }
   
   bool bDarkMode = get_dark_mode();
   
   if (bDarkMode)
   {
      
      m_colorWindow = argb(255, 0, 0, 0);
      m_colorText = argb(255, 255, 255, 255);
      m_colorHyperlink = argb(255, 40, 90, 245);
      m_colorHyperlinkHover = argb(255, 70, 180, 255);
      m_colorFocus = argb(255, 2, 128, 255);
      
   }
   else
   {
      
      m_colorWindow = argb(255, 255, 255, 255);
      m_colorText = argb(255, 0, 0, 0);
      m_colorHyperlink = argb(255, 50, 100, 185);
      m_colorHyperlinkHover = argb(255, 100, 180, 225);
      m_colorFocus = argb(255, 2, 58, 235);
      
   }
   
   m_pbrushWindow = ::nano::user::create_solid_brush(this, m_colorWindow);
   
   m_pbrushText = ::nano::user::create_solid_brush(this, m_colorText);
   
   m_pbrushHyperlink = ::nano::user::create_solid_brush(this, m_colorHyperlink);
   
   m_pbrushHyperlinkHover = ::nano::user::create_solid_brush(this, m_colorHyperlinkHover);
   
   m_ppenBorder = ::nano::user::create_pen(this, 1, m_colorText);
   
   m_ppenBorderFocus = ::nano::user::create_pen(this, 1, m_colorFocus);
   
}


void window::update_drawing_objects()
{
   
   delete_drawing_objects();
   
   create_drawing_objects();
   
}


bool window::defer_perform_entire_reposition_process()
{
   
   if(m_pimplementation)
   {
      
      if(m_pimplementation->defer_perform_entire_reposition_process())
      {
         
         return true;
         
      }
      
   }
   
   return false;
   
}



::point_i32 window::try_absolute_mouse_position(const ::point_i32 & point)
{
   
   return m_pimplementation->try_absolute_mouse_position(point);
   
}


::point_i32 window::origin()
{
   
   return m_rectangle.origin();
   
}


::nano::user::child * window::on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
{
   
   for (auto & pchild: m_childa)
   {
      
      if (pchild->m_rectangle.contains(point))
      {
         
         return pchild;
         
      }
      
   }
   
   return nullptr;
   
}


void window::add_child(::nano::user::child * pchild)
{
   
   pchild->m_pnanowindow = this;
   
   m_childa.add(pchild);
   
}


void window::add_button(const ::scoped_string & scopedstrText, enum_dialog_result edialogresult, char chLetter)
{
   
   auto pbutton = ::place(new ::nano::user::button());
   
   pbutton->m_strText = scopedstrText;
   pbutton->m_atom = edialogresult;
   pbutton->m_edialogresult1 = edialogresult;
   pbutton->m_chLetter = chLetter;
   //pbutton->m_bDefault = bDefault;
   
   m_nanobuttona.add(pbutton);
   
   add_child(pbutton);
   
}



::nano::user::child * window::get_child_by_id(const ::atom & atom)
{
   
   for (auto & pchild : m_childa)
   {
      
      if (pchild->m_atom == atom)
      {
         
         return pchild;
         
      }
      
   }
   
   return nullptr;
   
}


::payload window::get_result()
{
   
   return m_payloadResult;
   
}


void window::on_mouse_move(::user::mouse * pmouse)
{
   
   if(m_pchildHover)
   {
      
      m_pchildHover->on_mouse_move(pmouse);
      
      return;
      
   }
   
   if (m_pchildCapture)
   {
      
      m_pchildCapture->on_mouse_move(pmouse);
      
      return;
      
   }
   
   if (drag_on_mouse_move(pmouse))
   {
      
      return;
      
   }
   
   auto pchild = hit_test(pmouse, ::user::e_zorder_any);
   
   if (pchild)
   {
      
      pchild->on_mouse_move(pmouse);
      
   }
   
}


void window::on_left_button_down(::user::mouse * pmouse)
{
   
   auto pchild = hit_test(pmouse, ::user::e_zorder_any);
   
   if (pchild)
   {
      
      m_atomLeftButtonDown = pchild->m_atom;
      
   }
   else
   {
      
      m_atomLeftButtonDown = e_dialog_result_none;
      
   }
   
   auto pitemClient = tool().defer_item(e_element_client);
   
   auto pdragClient = drag(pitemClient);
   
   if (pdragClient && !pchild)
   {
      
      if(drag_on_button_down(pitemClient, pmouse))
      {
         
         return;
         
      }
      
   }
   
   if (::is_set(pchild) && pchild->is_focusable())
   {
      
      pchild->set_focus();
      
   }
   
}


void window::on_left_button_up(::user::mouse * pmouse)
{
   
   release_capture();
   
   if (drag_on_button_up(pmouse))
   {
      
      return;
      
   }
   
   auto pchild = hit_test(pmouse, ::user::e_zorder_any);
   
   if (pchild)
   {
      
      m_atomLeftButtonUp = pchild->m_atom;
      
   }
   else
   {
      
      m_atomLeftButtonUp = e_dialog_result_none;
      
   }
   
   if (m_atomLeftButtonUp == m_atomLeftButtonDown && m_atomLeftButtonUp != e_dialog_result_none)
   {
      
      m_payloadResult = m_atomLeftButtonUp;
      
      m_pimplementation->on_click(m_payloadResult, pmouse);
      
   }
   
   if (drag_on_button_up(pmouse))
   {
      
      return;
      
   }
   
}


void window::on_right_button_down(::user::mouse * pmouse)
{
   
   auto pchild = hit_test(pmouse, ::user::e_zorder_any);
   
   if (pchild)
   {
      
      m_atomRightButtonDown = pchild->m_atom;
      
   }
   else
   {
      
      m_atomRightButtonDown = e_dialog_result_none;
      
   }
   
   
   if (::is_set(pchild) && pchild->is_focusable())
   {
      
      pchild->set_focus();
      
   }
   
}


void window::on_right_button_up(::user::mouse * pmouse)
{
   
   release_capture();
   
   auto pchild = hit_test(pmouse, ::user::e_zorder_any);
   
   if (pchild)
   {
      
      m_atomRightButtonUp = pchild->m_atom;
      
   }
   else
   {
      
      m_atomRightButtonUp = e_dialog_result_none;
      
   }
   
   if (m_atomRightButtonUp == m_atomRightButtonDown)
   {
      
      m_pimplementation->on_right_click(m_atomLeftButtonUp, pmouse);
      
   }
   
}


void window::on_click(const ::payload& payload, ::user::mouse * pmouse)
{
   
   
}


void window::on_right_click(const ::payload& payload, ::user::mouse * pmouse)
{
   
   
}


void window::move_to(const ::point_i32 & point)
{
   
   m_pimplementation->move_to(point);
   
}



void window::redraw()
{
   
   m_pimplementation->redraw();
   
}


void window::get_client_rectangle(::rectangle_i32 & rectangle)
{
   
   rectangle.left() = 0;
   rectangle.top() = 0;
   rectangle.right() = m_rectangle.width();
   rectangle.bottom() = m_rectangle.height();
   
}


void window::get_window_rectangle(::rectangle_i32 & rectangle)
{
   
   rectangle = m_rectangle;
   
}


void window::set_capture()
{
   
   if(m_bCapture)
   {
      
      return;
      
   }
   
   m_pimplementation->set_capture();
   
   m_bCapture = true;
   
}


void window::set_cursor(enum_cursor ecursor)
{
   
   m_pimplementation->set_cursor(ecursor);
   
}


bool window::has_capture() const
{
   
   return m_pimplementation->has_capture();
   
}



void window::release_capture()
{
   
   m_pchildCapture = nullptr;
   
   if(!m_bCapture)
   {
      
      return;
      
   }
   
   m_bCapture = false;
   
   m_pimplementation->release_capture();
   
   
}


::pointer<::nano::user::device>window::create_device()
{
   
   throw interface_only();
   
   return nullptr;
   
}


void window::display_temporary_file_with_text(const ::string & str)
{
   
   string strAppId;
   
   strAppId = application()->m_strAppId;
   
   ::file::path pathFolder = acmedirectory()->home() / "application" / strAppId / "details";
   
   auto pathDetails = acmefile()->time_put_contents(pathFolder, "details", "txt", str);
   
   node()->shell_open(pathDetails, "");
   
}



void window::_run_modal_loop()
{
   
   m_pimplementation->_run_modal_loop();
   
}


::payload window::do_synchronously(const class time & timeWait)
{
   
   return m_pimplementation->do_synchronously(timeWait);
   
}


void window::handle(::topic* ptopic, ::context* pcontext)
{
   
   if (ptopic->m_atom == id_set_application_dark_mode)
   {
      
      m_pimplementation->handle(ptopic, pcontext);
      
   }
   
}


//::user::item & window::user_item(const ::item * pitem)
//{
//
//   return m_useritemmap[pitem];
//
//}


void window::do_asynchronously()
{
   
   m_pimplementation->do_asynchronously();
   
}


} // namespace user


} //  namespace nano

   

