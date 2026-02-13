//
// // Created from micro::interchange by
// // camilo on 2024-10-05 16:52 <3ThomasBorregaardSorensen!!
// Created by camilo on 31/01/2022 14:32 <3ThomasBorregaardSorensen!!
// renamed interchange from interchange by camilo on
//    2024-09-26 15:37 <3ThomasBorregaardSorensen!!
// 
// // // Merged from (acme)windowing and (acme)windowing_system by
// //   camilo on 2024-10-05 11:07 <3ThomasBorregaardSorensen!!
// //   (acme)windowing_system::windowing_system
// //       ---->windowing::windowing_base
// // //       ---->micro::user
// //   (acme)windowing::window_base
// //       ---->micro::interchange
//
// //// Child merged into main_window on 2024-10-05 05:17 <3ThomasBorregaardSorensen!!
// Created by camilo on 2022-01-21 05:10 PM <3ThomasBorregaardSorensen
//
// // merged from micro::main_window by camilo on 
// 2024-10-05 17:59 Odense Time <3ThomasBorregaardSorensen!!
// Created by camilo on 2024-09-26 22:59 Odense Time <3ThomasBorregaardSorensen!!
//
// micro::main_window Created by camilo on 31/01/2022 22:42 <3ThomasBorregaardSorensen!!
// From micro::main_window merged at ::user::main_window by
//    camilo on 2024-0926 15:04 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "button.h"
#include "main_window.h"
#include "user.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/handler/topic.h"
#include "acme/nano/graphics/device.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/theme.h"
#include "acme/windowing/window.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
//#include "acme/handler/sequence.h"
#include "acme/platform/system.h"
#include "acme/user/user/drag.h"
#include "acme/user/user/mouse.h"
#include "acme/user/user/tool.h"
#include "acme/windowing/window.h"
#include "acme/windowing/windowing.h"


namespace micro
{


   main_window::main_window()
   {

      m_efont = e_font_sans;

      auto pitemClient = stock_item(e_element_client);

      enable_drag(pitemClient, ::user::e_zorder_back);

   }


   main_window::~main_window()
   {


   }


   void main_window::create_window()
   {

      ::micro::elemental::create_window();


   }


   ::shift_int main_window::client_to_host()
   {

      if (system()->acme_windowing()->get_application_host_window())
      {

         return ::micro::elemental::client_to_host();

      }
      else
      {

         return {};

      }

   }


   void main_window::on_before_create_window(acme::windowing::window * pacmewindowingwindow)
   {

      ::micro::elemental::on_before_create_window(pacmewindowingwindow);

      m_bMinimizeBox = true;
      m_bMaximizeBox = true;
      m_bResizeable = true;
      m_bTopMost = false;
      m_bStartCentered = false;
      m_bArbitraryPositioning = false;

      pacmewindowingwindow->m_pacmeuserinteraction = this;

   }


   ::micro::main_window * main_window::micro_main_window()
   {

      return this;

   }



   void main_window::on_initialize_particle()
   {


   }


   void main_window::show()
   {

      if (!m_pacmeuserinteractionParent)
      {

         acme_windowing_window()->show_window();

      }

   }


   void main_window::hide()
   {

      if (!m_pacmeuserinteractionParent)
      {

         acme_windowing_window()->hide_window();

      }

   }


   void main_window::implementation_message_loop_step()
   {


   }


   ::string main_window::get_title()
   {

      return payload("main_window.title").as_string();

   }





   ::int_point main_window::origin()
   {
      auto r = get_window_rectangle();

      return r.top_left();

   }



   void main_window::set_position(const ::int_point & point)
   {

      m_pacmewindowingwindow->set_position(point);

   }


   void main_window::display_temporary_file_with_text(const ::scoped_string & scopedstr)
   {

      string strAppId;

      strAppId = application()->m_strAppId;

      ::file::path pathFolder = directory_system()->home() / "application" / strAppId / "details";

      auto pathDetails = file_system()->time_put_contents(pathFolder, "details", "txt", scopedstr);

      node()->shell_open(pathDetails, "");

   }


   void main_window::destroy()
   {


      ::micro::elemental::destroy();

   }


   void main_window::redraw()
   {

      ::acme::user::interaction::redraw();


   }


   int_rectangle main_window::get_window_rectangle()
   {

      return acme_windowing_window()->get_window_rectangle();

   }

   void main_window::set_cursor(enum_cursor ecursor)
   {


   }


   void main_window::synchronize_composited_micro_window()
   {


   }


   bool main_window::is_popup_window() const
   {

      return false;

   }


   void main_window::_on_window_simple_action(const_char_pointer pszActionName, ::user::activation_token * puseractivationtoken)
   {

      ::string strActionName(pszActionName);

      if (strActionName == "***move")
      {

         print_line("reaching here?!");
         //defer_perform_entire_reposition_process(nullptr);

         m_pacmewindowingwindow->set_mouse_capture();
         m_pacmewindowingwindow->m_bRepositioningWindowFromCenter = true;

      }
      else if (strActionName == "***size")
      {

         print_line("also here");

         m_pacmewindowingwindow->set_mouse_capture();
         m_pacmewindowingwindow->m_bResizingWindowFromBottomRight = true;

         //defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, nullptr);

      }
      else
      {

         ::acme::user::interaction::_on_window_simple_action(pszActionName, puseractivationtoken);

      }

   }


   void main_window::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if (ptopic->id() == id_operating_system_user_color_change)
      {

         redraw();

      }
      else if (ptopic->id() == id_set_application_dark_mode)
      {

         redraw();

      }
      else if (ptopic->id() == id_application_dark_mode_change)
      {

         redraw();

      }

   }


   void main_window::run()
   {

      show();

   }


   ::trace_statement & main_window::raw_trace_statement_prefix(::trace_statement & statement) const
   {

      ::string strType = ::platform::type(this).name();

      statement << strType;

      ::string strAtom = id().as_string();

      if (strAtom.has_character() && strAtom != strType)
      {
         statement << "=" << strAtom;
      }

      statement << "  ";

      return statement;

   }


} // namespace micro
