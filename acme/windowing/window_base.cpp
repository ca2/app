//
// Created by camilo on 2023-10-06 <3ThomasBorregaardSorensen!!
//
// nano::user::window_base Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSorensen!!
// Merged into window_base on 2024-04-26 14:52
//
#include "framework.h"
#include "window_base.h"
#include "platform/system.h"
#include "windowing_system/windowing_system.h"
#include "acme/nano/nano.h"
#include "acme/nano/graphics/device.h"
#include "acme/nano/user/display.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/user/user/interaction_base.h"



namespace windowing
{


   window_base::window_base() :
      m_pointCursor2(I32_MINIMUM)
   {

      m_bRepositioningWindowFromCenter = false;
      m_bResizingWindowFromBottomRight = false;

   }


   window_base::~window_base()
   {

      output_debug_string("window_base::~window_base()");

   }


   void window_base::on_initialize_particle()
   {

      ::user::element::on_initialize_particle();

      _synchronous_lock synchronouslock(system()->windowing_system()->synchronization());

      system()->windowing_system()->m_windowbasea.add(this);

   }


   void window_base::destroy()
   {

      ::user::element::destroy();

      _synchronous_lock synchronouslock(system()->windowing_system()->synchronization());

      system()->windowing_system()->m_windowbasea.erase(this);

   }


   bool window_base::is_windowing_popup()
   {

      return false;

   }


   ::point_i32 window_base::windowing_popup_origin()
   {

      return {};

   }


   ::size_i32 window_base::windowing_popup_size()
   {

      return {};

   }


   void window_base::_on_windowing_close_window()
   {


   }


   bool window_base::is_satellite_window()
   {

      return false;

   }


   window_base * window_base::owner_window()
   {

      return nullptr;

   }


   ::string window_base::get_window_text()
   {

      return {};

   }


   // ::pointer < ::operating_system::a_system_menu > window_base::create_system_menu(bool bContextual)
   // {
   //
   //    return ::nano::user::window_base::create_system_menu(bContextual);
   //
   // }


   bool window_base::defer_perform_entire_reposition_process(::user::mouse * pmouse)
   {

      return false;

   }


   bool window_base::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
   {

      return false;

   }



// static thread_local ::pointer_array < window_base > t_nanowindowimplementationa;
//
//
//
// ::pointer_array < window_base > & window_base::nanowindowimplementationa()
// {
//
//    return t_nanowindowimplementationa;
//
// }


// window_base::window_base()
// {
//
//
// }
//
//
// window_base::~window_base()
// {
//
//    output_debug_string("window_base::~window_base()");
//
// }


::nano::user::display * window_base::get_display()
{

   return nullptr;

}


// void window_base::draw(device * pnanodevice)
// {
//
//    m_pinterface->draw(pnanodevice);
//
// }


// bool window_base::get_dark_mode()
// {
//
//    return m_pinterface->get_dark_mode();
//
// }


bool window_base::is_active_window()
{

   //return m_pinterface->is_active();

   return false;

}


// void window_base::nano_window_on_create()
// {
//
//    //node()->fetch_user_color();
//
//    //system()->add_signal_handler({ use_t{}, this }, id_operating_system_user_color_change);
//
//    create_drawing_objects();
//
//    on_create();
//
// }




void window_base::nano_window_on_destroy()
{


}


   void window_base::create_window()
{

}


   void window_base::_create_window()
{


}


void window_base::on_create_window()
{

   m_puserinteractionbase->on_create_window();

}




   void window_base::show_window()
{

}


   void window_base::hide_window()
{


}


   void window_base::message_loop()
   {


   }


   void window_base::set_active_window()
   {


   }



::point_i32 window_base::try_absolute_mouse_position(const ::point_i32 & point)
{

   //return window_interface::try_absolute_mouse_position(point);

      return point;

}


void window_base::handle(::topic * ptopic, ::context * pcontext)
{

   // if(ptopic->m_atom == id_operating_system_user_color_change)
   // {
   //
   //    update_drawing_objects();
   //
   //    redraw();
   //
   // }
   // else if(ptopic->m_atom == id_set_application_dark_mode)
   // {
   //
   //    update_drawing_objects();
   //
   //    redraw();
   //
   // }
   // else if(ptopic->m_atom == id_application_dark_mode_change)
   // {
   //
   //    update_drawing_objects();
   //
   //    redraw();
   //
   // }

}


::size_i32 window_base::get_main_screen_size()
{

   auto pdisplay = get_display();

   if(::is_null(pdisplay))
   {

      return {800, 600};

   }

   return pdisplay->get_main_screen_size();

}


// ::payload window_base::do_synchronously(const class time & timeWait)
// {
//
//    create();
//
//    m_pinterface->show_window();
//
//    message_loop();
//
//    // auto pmanualresetevent = ::place(new manual_reset_event());
//    //
//    // m_pinterface->m_psequencer->then([ pmanualresetevent](auto psequencer)
//    // {
//    //
//    //    pmanualresetevent->SetEvent();
//    //
//    // });
//    //
//    // auto pinterface = m_pinterface;
//    //
//    // if(pinterface->m_payloadResult.is_new())
//    // {
//    //
//    //    pmanualresetevent->wait();
//    //
//    // }
//    //
//    // //   auto pmessagebox = pparticle->__create_new < message_box >();
//    // //
//    // //   atom idResult;
//    // //
//    // //   manual_reset_event event;
//    // //
//    // //   pmessagebox->display(pszMessage, pszTitle, emessagebox, pszDetails);
//    // //
//    // //   pmessagebox->m_functionClose = [&idResult, &event](nano::user::interchange * pwindow)
//    // //   {
//    // //
//    // //      idResult = pwindow->m_atomResult;
//    // //
//    // //      event.SetEvent();
//    // //
//    // //   };
//    // //
//    // //   if(is_single_main_user_thread() && is_main_thread())
//    // //   {
//    // //
//    // //      pmessagebox->_run_modal_loop();
//    // //
//    // //   }
//    // //   else
//    // //   {
//    // //      event.wait();
//    // //
//    // //   }
//    // //
//    // //   //auto idResult = pmessagebox->get_result();
//    // //
//    // //   return idResult;
//
//    return pinterface->m_payloadResult;
//
// }

//::atom message_box::do_synchronously()
//{
//
//   //main_synchronous(1_min, [this]()
//   //{
//
//
//   //main_asynchronous([this]()
//      //{
//
//   create();
//
//   nano::user::interchange::display();
//
//  aaa_message_loop();
//
//   //});
//
//   //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
//
////});
//
//   return m_atomResult;
//
//}


   void window_base::_on_window_simple_action(const char * pszActionName)
   {

      if(!m_puserinteractionbase)
      {

         throw ::exception(error_failed);

      }

      m_puserinteractionbase->_on_window_simple_action(pszActionName);

   }


void window_base::defer_show_system_menu(::user::mouse * pmouse)
{


}

void window_base::implementation_message_loop_step()
{


}


void window_base::on_char(int iChar)
{


}

//::atom message_box::do_synchronously()
//{
//
//   //main_synchronous(1_min, [this]()
//   //{
//
//
//   //main_asynchronous([this]()
//      //{
//
//   create();
//
//   nano::user::interchange::display();
//
//   aaa_message_loop();
//
//   //});
//
//   //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
//
////});
//
//   return m_atomResult;
//
//}


//void message_box::do_asynchronously()
//{
//
//   m_functionClose = [this](nano::user::interchange * pwindow)
//   {
//
//      m_psequence->on_sequence();
//
//   };
//
//   main_asynchronous([this]()
//      {
//
//         create();
//
//         nano::user::interchange::display();
//
//         aaa_message_loop();
//
//      });
//
//   //display(m_strMessage, m_strTitle, m_emessagebox, m_strDetails);
//
////});
//
//   //return m_atomResult;
//
//}
//
//


   void window_base::set_interface_client_size(const ::size_i32 & sizeWindow) // set_size
   {

      m_sizeWindow = sizeWindow;

   }


   void window_base::set_position(const point_i32 &point)
   {

      auto p = point;

      main_post([this, p]()
         {

set_position_unlocked(p);

         });


   }


   void window_base::set_size(const size_i32 &size)
   {

      auto s = size;

      main_post([this, s]()
         {

set_size_unlocked(s);

         });


   }


   void window_base::set_position_unlocked(const point_i32 &point)
   {


   }


   void window_base::set_size_unlocked(const size_i32 &size)
   {


   }


   void window_base::on_a_system_menu_item(::operating_system::a_system_menu_item * psystemmenuitem)
   {

      ::string strActionName(psystemmenuitem->m_strAtom);

      if(strActionName == "minimize")
      {

         window_minimize();

      }
      else if(strActionName == "maximize")
      {

         window_maximize();

      }
      else if(strActionName == "maximize")
      {

         window_maximize();

      }
      else if(strActionName == "about_box")
      {

         application()->show_about_box();

      }
      else if(strActionName == "close")
      {

         window_close();

      }
      else if(strActionName == "")
      {

         print_line("reaching here?!");
         //defer_perform_entire_reposition_process(nullptr);

      }
      else if(strActionName == "")
      {

         print_line("also here");

         //defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, nullptr);

      }


   }


} // namespace windowing




