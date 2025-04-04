//
// Created by camilo on 31/01/2022 16:16 <3ThomasBorregaardSorensen!!
//
// renamed interchange from interchange by camilo on
//    2024-09-26 15:38 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "interchange.h"
#include "window_implementation.h"
#include "device.h"
#include "child.h"
#include "button.h"
#include "user.h"
#include "acme/nano/nano.h"
#include "acme/handler/topic.h"
#include "acme/user/micro/font.h"
#include "acme/constant/id.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
//#include "acme/handler/sequence.h"
#include "acme/platform/system.h"
#include "acme/user/user/drag.h"
#include "acme/user/user/mouse.h"
#include "acme/user/user/tool.h"
#include "acme/windowing/window_base.h"


namespace nano
{


namespace user
{


interchange::interchange()
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


interchange::~interchange()
{
   
   system()->acme_windowing()->m_interchangea.erase_item(this);
   
}


//::pointer < item_container > interchange::item_form()
//{
//
//   return item_container(id_user_interface);
//
//}


void interchange::on_initialize_particle()
{
   
   ::object::on_initialize_particle();
   
   __øconstruct(m_pwindowbase);
   
   m_pwindowbase->m_puserinteractionbase = this;
   
   system()->m_pnano->user()->m_interchangea.add(this);
   
}


void interchange::draw(::nano::graphics::device * pnanodevice)
{
   
   ::pointer<::nano::graphics::pen>pnanopenBorder;
   
   if (is_active())
   {
      
      pnanopenBorder = m_ppenBorderFocus;
      
   }
   else
   {
      
      pnanopenBorder = m_ppenBorder;
      
   }
   
   ::int_rectangle rectangleX;
   
   get_client_rectangle(rectangleX);
   
   pnanodevice->rectangle(rectangleX, m_pbrushWindow, pnanopenBorder);
   
   on_draw(pnanodevice);
   
   draw_children(pnanodevice);
   
}

   ::int_rectangle interchange::get_window_rectangle()
{

return m_rectangle;

}


void interchange::draw_children(::nano::graphics::device * pnanodevice)
{
   
   for (auto & pchild: m_childa)
   {
      
      pchild->on_draw(pnanodevice);
      
   }
   
}


void interchange::create()
{
   
   m_pwindowbase->create_window();
   
}


void interchange::on_create_window()
{

   update_drawing_objects();
   
}


void interchange::destroy()
{
   
   if (m_pwindowbase)
   {
      
      m_pwindowbase->destroy();
      
      m_pwindowbase.release();
      
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

   if(system()->acme_windowing())
   {

      system()->acme_windowing()->m_interchangea.erase(this);

   }
   
}


void interchange::show_window()
{
   
   m_pwindowbase->show_window();
   
}


void interchange::hide()
{
   
   m_pwindowbase->hide();
   
}


void interchange::message_loop()
{
   
   m_pwindowbase->message_loop();
   
}



void interchange::on_draw(::nano::graphics::device * pnanodevice)
{
   
   //m_pwindowbase->draw(pnanodevice);
   
}


void interchange::on_char(int iChar)
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


bool interchange::is_active()
{
   
   return m_bNcActive;
   
}


void interchange::set_active()
{
   
   m_pwindowbase->set_active_window();
   
}


void interchange::delete_drawing_objects()
{
   
   m_pbrushWindow.release();
   
   m_ppenBorder.release();
   
   m_ppenBorder.release();
   
}


bool interchange::get_dark_mode()
{
   
   return system()->dark_mode();
   
}


void interchange::create_drawing_objects()
{
   
   if (!m_pfont)
   {
      
#if REFERENCING_DEBUGGING
      
      ::allocator::add_referer({this, __FUNCTION_FILE_LINE__});
      
#endif
      
      __øconstruct(m_pfont, nullptr);
      
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
   
   m_pbrushWindow = ::nano::graphics::create_solid_brush(this, m_colorWindow);
   
   m_pbrushText = ::nano::graphics::create_solid_brush(this, m_colorText);
   
   m_pbrushHyperlink = ::nano::graphics::create_solid_brush(this, m_colorHyperlink);
   
   m_pbrushHyperlinkHover = ::nano::graphics::create_solid_brush(this, m_colorHyperlinkHover);
   
   m_ppenBorder = ::nano::graphics::create_pen(this, 1, m_colorText);
   
   m_ppenBorderFocus = ::nano::graphics::create_pen(this, 1, m_colorFocus);
   
}


void interchange::update_drawing_objects()
{
   
   delete_drawing_objects();
   
   create_drawing_objects();
   
}


bool interchange::defer_perform_entire_reposition_process(::user::mouse * pmouse)
{
   
   if(m_pwindowbase)
   {
      
      if(m_pwindowbase->defer_perform_entire_reposition_process(pmouse))
      {
         
         return true;
         
      }
      
   }
   
   return false;
   
}


   bool interchange::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
   {

      if(m_pwindowbase)
      {

         if(m_pwindowbase->defer_perform_entire_resizing_process(eframeSizing, pmouse))
         {

            return true;

         }

      }

      return false;

   }


::int_point interchange::try_absolute_mouse_position(const ::int_point & point)
{
   
   return m_pwindowbase->try_absolute_mouse_position(point);
   
}


::int_point interchange::origin()
{
   
   return m_rectangle.origin();
   
}


::micro::child * interchange::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
{

   auto point = pmouse->m_pointHost;

   host_to_client()(point);

   return on_hit_test(point, ezorder);

}



::micro::child * interchange::on_hit_test(const ::int_point & point, ::user::e_zorder ezorder)
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


void interchange::add_child(::micro::child * pchild)
{
   
   pchild->m_pinterchange = this;
   
   m_childa.add(pchild);
   
}


void interchange::add_button(const ::scoped_string & scopedstrText, enum_dialog_result edialogresult, char chLetter)
{
   
   auto pbutton = __allocate ::micro::button();
   
   pbutton->m_strText = scopedstrText;
   pbutton->id() = edialogresult;
   pbutton->m_edialogresult1 = edialogresult;
   pbutton->m_chLetter = chLetter;
   //pbutton->m_bDefault = bDefault;
   
   m_nanobuttona.add(pbutton);
   
   add_child(pbutton);
   
}



::micro::child * interchange::get_child_by_id(const ::atom & atom)
{
   
   for (auto & pchild : m_childa)
   {
      
      if (pchild->id() == atom)
      {
         
         return pchild;
         
      }
      
   }
   
   return nullptr;
   
}


::payload interchange::get_result()
{
   
   return m_payloadResult;
   
}


void interchange::on_mouse_move(::user::mouse * pmouse)
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


void interchange::on_left_button_down(::user::mouse * pmouse)
{
   
   auto pchild = hit_test(pmouse, ::user::e_zorder_any);
   
   if (pchild)
   {
      
      m_atomLeftButtonDown = pchild->id();
      
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


void interchange::on_left_button_up(::user::mouse * pmouse)
{
   
   release_capture();
   
   if (drag_on_button_up(pmouse))
   {
      
      return;
      
   }
   
   auto pchild = hit_test(pmouse, ::user::e_zorder_any);
   
   if (pchild)
   {
      
      m_atomLeftButtonUp = pchild->id();
      
   }
   else
   {
      
      m_atomLeftButtonUp = e_dialog_result_none;
      
   }
   
   if (m_atomLeftButtonUp == m_atomLeftButtonDown && m_atomLeftButtonUp != e_dialog_result_none)
   {
      
      m_payloadResult = m_atomLeftButtonUp;
      
      on_click(m_payloadResult, pmouse);
      
   }
   
   if (drag_on_button_up(pmouse))
   {
      
      return;
      
   }
   
}


void interchange::on_right_button_down(::user::mouse * pmouse)
{
   
   auto pchild = hit_test(pmouse, ::user::e_zorder_any);
   
   if (pchild)
   {
      
      m_atomRightButtonDown = pchild->id();
      
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


void interchange::on_right_button_up(::user::mouse * pmouse)
{
   
   release_capture();
   
   auto pchild = hit_test(pmouse, ::user::e_zorder_any);
   
   if (pchild)
   {
      
      m_atomRightButtonUp = pchild->id();
      
   }
   else
   {
      
      m_atomRightButtonUp = e_dialog_result_none;
      
   }
   
   if (m_atomRightButtonUp == m_atomRightButtonDown)
   {
      
      on_right_click(m_atomLeftButtonUp, pmouse);
      
   }
   
}


void interchange::on_click(const ::payload& payload, ::user::mouse * pmouse)
{
   
   
}


void interchange::on_right_click(const ::payload& payload, ::user::mouse * pmouse)
{
   
   
}


void interchange::set_position(const ::int_point & point)
{
   
   m_pwindowbase->set_position(point);
   
}


void interchange::redraw()
{
   
   m_pwindowbase->redraw();
   
}


void interchange::get_client_rectangle(::int_rectangle & rectangle)
{
   
   rectangle.left() = 0;
   rectangle.top() = 0;
   rectangle.right() = m_rectangle.width();
   rectangle.bottom() = m_rectangle.height();
   
}


// ::int_rectangle interchange::get_window_rectangle()
// {
//
//    return m_rectangle;
//
// }


void interchange::set_capture()
{
   
   if(m_bCapture)
   {
      
      return;
      
   }
   
   m_pwindowbase->set_capture();
   
   m_bCapture = true;
   
}


void interchange::set_cursor(enum_cursor ecursor)
{
   
   m_pwindowbase->set_cursor(ecursor);
   
}


bool interchange::has_capture()
{
   
   return m_pwindowbase->has_capture();
   
}


void interchange::release_capture()
{
   
   m_pchildCapture = nullptr;
   
   if(!m_bCapture)
   {
      
      return;
      
   }
   
   m_bCapture = false;
   
   m_pwindowbase->release_capture();

}


::pointer<::nano::graphics::device>interchange::create_device()
{
   
   throw interface_only();
   
   return nullptr;
   
}


void interchange::display_temporary_file_with_text(const ::string & str)
{
   
   string strAppId;
   
   strAppId = application()->m_strAppId;
   
   ::file::path pathFolder = directory_system()->home() / "application" / strAppId / "details";
   
   auto pathDetails = file_system()->time_put_contents(pathFolder, "details", "txt", str);
   
   node()->shell_open(pathDetails, "");
   
}



void interchange::_run_modal_loop()
{
   
   m_pwindowbase->_run_modal_loop();
   
}


    ::payload interchange::do_synchronously(const class time & timeWait)
    {


       create();

       show_window();

       message_loop();

       auto pmanualresethappening = __allocate manual_reset_happening();

       m_psequencer->then([ pmanualresethappening](auto psequencer)
       {

           pmanualresethappening->set_happening();

       });

      if(m_payloadResult.is_new())
      {

         pmanualresethappening->wait();

      }

       // //   auto pmessagebox = pparticle->__create_new < message_box >();
       // //
       // //   atom idResult;
       // //
       // //   manual_reset_happening happening;
       // //
       // //   pmessagebox->display(pszMessage, pszTitle, emessagebox, pszDetails);
       // //
       // //   pmessagebox->m_functionClose = [&idResult, &happening](micro::interchange * pwindow)
       // //   {
       // //
       // //      idResult = pwindow->m_atomResult;
       // //
       // //      happening.set_happening();
       // //
       // //   };
       // //
       // //   if(is_single_main_user_thread() && is_main_thread())
       // //   {
       // //
       // //      pmessagebox->_run_modal_loop();
       // //
       // //   }
       // //   else
       // //   {
       // //      happening.wait();
       // //
       // //   }
       // //
       // //   //auto idResult = pmessagebox->get_result();
       // //
       // //   return idResult;

       return m_payloadResult;

    }

   // ::atom interchange::do_synchronously()
   // {
   //
   //    //main_synchronous(1_min, [this]()
   //    //{
   //
   //
   //    //main_asynchronous([this]()
   //       //{
   //
   //    create();
   //
   //    micro::interchange::display();
   //
   //   aaa_message_loop();
   //
   //    //});
   //
   //    //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
   //
   // //});
   //
   //    return m_atomResult;
   //
   // }



void interchange::handle(::topic * ptopic, ::handler_context * pcontext)
{
   
   if (ptopic->id() == id_set_application_dark_mode)
   {
      
      m_pwindowbase->handle(ptopic, phandlercontext);
      
   }
   
}


//::user::item & interchange::user_item(const ::item * pitem)
//{
//
//   return m_useritemmap[pitem];
//
//}


void interchange::do_asynchronously()
{
   
   //m_pwindowbase->do_asynchronously();
   
}


} // namespace user


} //  namespace nano

   

