//
// Created by camilo on 31/01/2022 16:16 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "window_implementation.h"
#include "device.h"
#include "child.h"
#include "button.h"
#include "nano.h"
#include "acme/handler/topic.h"
#include "acme/user/nano/font.h"
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



nano_window::nano_window()
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


nano_window::~nano_window()
{

   system()->m_pnano->m_nanowindowa.erase_item(this);

}


//::pointer < item_container > nano_window::item_form()
//{
//
//   return item_container(id_user_interface);
//
//}


void nano_window::on_initialize_particle()
{

   ::object::on_initialize_particle();

   __construct(m_pimplementation);

   m_pimplementation->m_pinterface = this;
   
   system()->m_pnano->m_nanowindowa.add(this);

}


void nano_window::draw(nano_device * pnanodevice)
{

   ::pointer<::nano_pen>pnanopenBorder;

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


void nano_window::draw_children(nano_device * pnanodevice)
{

   for (auto & pchild: m_childa)
   {

      pchild->on_draw(pnanodevice);

   }

}


void nano_window::create()
{

   m_pimplementation->create();

}


void nano_window::on_create()
{


}


void nano_window::destroy()
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
   
   system()->m_pnano->m_nanowindowa.erase(this);
   
}


void nano_window::display()
{

   m_pimplementation->display();

}


void nano_window::hide()
{

   m_pimplementation->hide();

}


void nano_window::message_loop()
{

   m_pimplementation->message_loop();

}



void nano_window::on_draw(nano_device * pnanodevice)
{

   m_pimplementation->draw(pnanodevice);

}


void nano_window::on_char(int iChar)
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


bool nano_window::is_active()
{

   return m_bNcActive;

}


void nano_window::set_active()
{

   m_pimplementation->set_active();

}


void nano_window::delete_drawing_objects()
{

   m_pbrushWindow.release();

   m_ppenBorder.release();

   m_ppenBorder.release();

}


bool nano_window::get_dark_mode()
{

   return m_pimplementation->get_dark_mode();

}


void nano_window::create_drawing_objects()
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

   m_pbrushWindow = ::nano::create_solid_brush(this, m_colorWindow);

   m_pbrushText = ::nano::create_solid_brush(this, m_colorText);

   m_pbrushHyperlink = ::nano::create_solid_brush(this, m_colorHyperlink);

   m_pbrushHyperlinkHover = ::nano::create_solid_brush(this, m_colorHyperlinkHover);

   m_ppenBorder = ::nano::create_pen(this, 1, m_colorText);

   m_ppenBorderFocus = ::nano::create_pen(this, 1, m_colorFocus);

}


void nano_window::update_drawing_objects()
{

   delete_drawing_objects();

   create_drawing_objects();

}


bool nano_window::defer_perform_entire_reposition_process()
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



::point_i32 nano_window::try_absolute_mouse_position(const ::point_i32 & point)
{

   return m_pimplementation->try_absolute_mouse_position(point);

}


::point_i32 nano_window::origin()
{

   return m_rectangle.origin();

}


nano_child * nano_window::on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
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


void nano_window::add_child(nano_child * pchild)
{

   pchild->m_pnanowindow = this;

   m_childa.add(pchild);

}


void nano_window::add_button(const ::scoped_string & scopedstrText, enum_dialog_result edialogresult, char chLetter)
{

   auto pbutton = __allocate< nano_button >();

   pbutton->m_strText = scopedstrText;
   pbutton->m_atom = edialogresult;
   pbutton->m_edialogresult1 = edialogresult;
   pbutton->m_chLetter = chLetter;
   //pbutton->m_bDefault = bDefault;

   m_nanobuttona.add(pbutton);

   add_child(pbutton);

}



nano_child * nano_window::get_child_by_id(const ::atom & atom)
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

::atom nano_window::get_result()
{

   return m_payloadResult;

}


void nano_window::on_mouse_move(::user::mouse * pmouse)
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


void nano_window::on_left_button_down(::user::mouse * pmouse)
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

      drag_on_button_down(pitemClient, pmouse);

      return;

   }

   if (::is_set(pchild) && pchild->is_focusable())
   {

      pchild->set_focus();

   }

}


void nano_window::on_left_button_up(::user::mouse * pmouse)
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


void nano_window::on_right_button_down(::user::mouse * pmouse)
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


void nano_window::on_right_button_up(::user::mouse * pmouse)
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


void nano_window::on_click(const ::atom & atom, ::user::mouse * pmouse)
{

   
}


void nano_window::on_right_click(const ::atom & atom, ::user::mouse * pmouse)
{


}


void nano_window::move_to(const ::point_i32 & point)
{

   m_pimplementation->move_to(point);

}



void nano_window::redraw()
{

   m_pimplementation->redraw();

}


void nano_window::get_client_rectangle(::rectangle_i32 & rectangle)
{

   rectangle.left() = 0;
   rectangle.top() = 0;
   rectangle.right() = m_rectangle.width();
   rectangle.bottom() = m_rectangle.height();

}


void nano_window::get_window_rectangle(::rectangle_i32 & rectangle)
{

   rectangle = m_rectangle;

}


void nano_window::set_capture()
{

   if(m_bCapture)
   {

      return;

   }

   m_pimplementation->set_capture();

   m_bCapture = true;

}


void nano_window::set_cursor(enum_cursor ecursor)
{

   m_pimplementation->set_cursor(ecursor);

}


bool nano_window::has_capture() const
{

   return m_pimplementation->has_capture();

}



void nano_window::release_capture()
{

   m_pchildCapture = nullptr;

   if(!m_bCapture)
   {

      return;

   }

   m_bCapture = false;

   m_pimplementation->release_capture();


}


::pointer<nano_device>nano_window::create_device()
{

   throw interface_only();

   return nullptr;

}


void nano_window::display_temporary_file_with_text(const ::string & str)
{

   string strAppId;

   strAppId = application()->m_strAppId;

   ::file::path pathFolder = acmedirectory()->home() / "application" / strAppId / "details";

   auto pathDetails = acmefile()->time_put_contents(pathFolder, "details", "txt", str);

   node()->shell_open(pathDetails, "");

}



void nano_window::_run_modal_loop()
{
   
   m_pimplementation->_run_modal_loop();
   
}


::payload nano_window::do_synchronously(const class time & timeWait)
{
   
   return m_pimplementation->do_synchronously(timeWait);

}


void nano_window::handle(::topic* ptopic, ::context* pcontext)
{
   
   if (ptopic->m_atom == id_set_application_dark_mode)
   {
      
      m_pimplementation->handle(ptopic, pcontext);
      
   }
   
}


//::user::item & nano_window::user_item(const ::item * pitem)
//{
//
//   return m_useritemmap[pitem];
//
//}


void nano_window::do_asynchronously()
{

   m_pimplementation->do_asynchronously();

}



