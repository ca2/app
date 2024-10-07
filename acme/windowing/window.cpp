//
// Created by camilo on 31/01/2022 16:16 <3ThomasBorregaardSorensen!!
//
// renamed window from window by camilo on
//    2024-09-26 15:38 <3ThomasBorregaardSorensen!!
// // Merged from windowing_base to
//     windowing to nano_use by camilo on 2024-10-05 11:12 <3ThomasBorregaardSorensen!!
//                   //
// Created by camilo on 2024-05-26 21:50 <3ThomasBorregaardSorensen!!
// // Merged from windowing_base to
//     windowing by camilo on 2024-10-05 10:36 <3ThomasBorregaardSorensen!!
//

//

   //
// Created by camilo on 2023-10-06 <3ThomasBorregaardSorensen!!
//
// micro::window Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSorensen!!
// Merged into window on 2024-04-26 14:52
//
//
#include "framework.h"
#include "display.h"
#include "window.h"
#include "windowing.h"
#include "acme/nano/graphics/device.h"
//#include "interaction.h"
//#include "button.h"
//#include "user.h"
#include "acme/nano/nano.h"
#include "acme/handler/topic.h"
#include "acme/nano/graphics/font.h"
#include "acme/constant/id.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/nano/user/interaction.h"
#include "acme/nano/user/user.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"



namespace acme
{


   namespace windowing
   {


      window::window() :
         m_pointCursor2(I32_MINIMUM)
      {

         m_bRepositioningWindowFromCenter = false;
         m_bResizingWindowFromBottomRight = false;

         //}
         //{

         m_bTopMost = false;

         m_bNcActive = false;

         m_bStartCentered = false;

         m_bArbitraryPositioning = false;

         m_bCapture = false;

      }


      window::~window()
      {

         output_debug_string("window::~window()");

      }


      //::pointer < item_container > window::item_form()
      //{
      //
      //   return item_container(id_user_interface);
      //
      //}


      void window::on_initialize_particle()
      {

         ::user::element::on_initialize_particle();

         //__construct(m_pnanouserinteraction);

         //m_pnanouserinteraction->m_pnanouserinteraction = this;

         //system()->acme_windowing()->m_interchangea.add(this);

         //::user::element::on_initialize_particle();

         //_synchronous_lock synchronouslock(system()->acme_windowing()->synchronization());

         //system()->acme_windowing()->m_windowbasea.add(this);


      }





      //::rectangle_i32 window::get_window_rectangle()
      //{

      //   return m_rectangle;

      //}




      void window::create_window()
      {

         //m_pnanouserinteraction->create_window();

      }


      void window::on_create_window()
      {

         //update_drawing_objects();

         m_pnanouserinteraction->on_create_window();


      }


      void window::destroy()
      {

         if (m_pnanouserinteraction)
         {

            m_pnanouserinteraction->destroy();

            m_pnanouserinteraction.release();

         }

         if (m_functionClose)
         {

            m_functionClose(m_pnanouserinteraction);

            m_functionClose.clear();

         }


         if (system()->acme_windowing())
         {

            system()->acme_windowing()->m_windowa.erase(this);

         }

         //_synchronous_lock synchronouslock(system()->acme_windowing()->synchronization());

         //system()->acme_windowing()->m_windowbasea.erase(this);




         ::user::element::destroy();

      }


      void window::show_window()
      {

         //m_pnanouserinteraction->show_window();

      }


      void window::hide_window()
      {

         //m_pnanouserinteraction->hide();

      }


      void window::window_message_loop()
      {

         //m_pnanouserinteraction->message_loop();

      }



      //void window::on_draw(::nano::graphics::device * pnanodevice)
      //{

      //   //m_pnanouserinteraction->draw(pnanodevice);

      //}


      //void window::on_char(int iChar)
      //{

      //   if (iChar == '\t' && m_childa.has_element())
      //   {

      //      auto iFind = m_childa.find_first(m_pchildFocus);

      //      iFind++;

      //      m_pchildFocus = m_childa % iFind;

      //      redraw();

      //   }
      //   else if (m_pchildFocus)
      //   {

      //      m_pchildFocus->on_char(iChar);

      //   }

      //}


      bool window::is_active_window()
      {

         return m_bNcActive;

      }


      void window::set_active_window()
      {
         //
           //       m_pnanouserinteraction->set_active_window();

      }





      //bool window::get_dark_mode()
      //{

      //   return system()->dark_mode();


      //}



      bool window::defer_perform_entire_reposition_process(::user::mouse * pmouse)
      {

         if (m_pnanouserinteraction)
         {

            if (m_pnanouserinteraction->defer_perform_entire_reposition_process(pmouse))
            {

               return true;

            }

         }

         return false;

      }



      void window::on_position_window()
      {


      }

      void window::on_size_window()
      {


      }


      bool window::is_window_zoomed()
      {

         return false;

      }


      void window::window_minimize()
      {

      }


      void window::window_maximize()
      {

      }


      void window::window_full_screen()
      {

      }


      void window::window_restore()
      {

      }


      void window::window_close()
      {

      }


      bool window::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
      {

         if (m_pnanouserinteraction)
         {

            if (m_pnanouserinteraction->defer_perform_entire_resizing_process(eframeSizing, pmouse))
            {

               return true;

            }

         }

         return false;

      }


      //::point_i32 window::try_absolute_mouse_position(const ::point_i32 & point)
      //{

      //   return m_pnanouserinteraction->try_absolute_mouse_position(point);

      //}


      ::point_i32 window::origin()
      {

         return m_rectangle.origin();

      }






      //void window::set_position(const ::point_i32 & point)
      //{

      //   m_pnanouserinteraction->set_position(point);

      //}


      void window::redraw()
      {

         m_pnanouserinteraction->redraw();

      }


      void window::set_interaction_rectangle(const ::rectangle_i32 & rectangle)
      {

         m_rectangle = rectangle;

      }


      ::rectangle_i32 window::get_interaction_rectangle()
      {

         return m_rectangle;

      }


      //::rectangle_i32 window::get_window_rectangle()
      //{

      //   //::rectangle_i32 rectangle;

      //   //rectangle.left() = 0;
      //   //rectangle.top() = 0;
      //   //rectangle.right() = m_rectangle.width();
      //   //rectangle.bottom() = m_rectangle.height();

      //   //return rectangle;

      //   return {};

      //}


      // ::rectangle_i32 window::get_window_rectangle()
      // {
      //
      //    return m_rectangle;
      //
      // }


      void window::set_capture()
      {

         if (m_bCapture)
         {

            return;

         }

         m_pnanouserinteraction->set_capture();

         m_bCapture = true;

      }


      void window::set_cursor(enum_cursor ecursor)
      {

         m_pnanouserinteraction->set_cursor(ecursor);

      }


      bool window::has_capture()
      {

         return m_pnanouserinteraction->has_capture();

      }


      void window::release_capture()
      {

         m_pnanouserinteractionCapture = nullptr;

         if (!m_bCapture)
         {

            return;

         }

         m_bCapture = false;

         m_pnanouserinteraction->release_capture();

      }


      ::pointer<::nano::graphics::device>window::create_device()
      {

         throw interface_only();

         return nullptr;

      }





      void window::_run_modal_loop()
      {

         m_pnanouserinteraction->_run_modal_loop();

      }



      // ::atom window::do_synchronously()
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
      //    micro::window::display();
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


      ::payload window::do_synchronously(const class time & timeWait)
      {

         create_window();

         show_window();

         acme_windowing_window()->window_message_loop();

         return m_pnanouserinteraction->m_payloadResult;

      }




      void window::handle(::topic * ptopic, ::context * pcontext)
      {

         if (ptopic->m_atom == id_set_application_dark_mode)
         {

            m_pnanouserinteraction->handle(ptopic, pcontext);

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

         create_window();

         show_window();

      }

      // // Merged from windowing_base to
   //     windowing to nano_use by camilo on 2024-10-05 11:12 <3ThomasBorregaardSorensen!!
   //                   //
   // Created by camilo on 2024-05-26 21:50 <3ThomasBorregaardSorensen!!
   // // Merged from windowing_base to
   //     windowing by camilo on 2024-10-05 10:36 <3ThomasBorregaardSorensen!!
   //

   //

      //
   // Created by camilo on 2023-10-06 <3ThomasBorregaardSorensen!!
   //
   // micro::window Created by camilo on 31/01/2022 23:04 <3ThomasBorregaardSorensen!!
   // Merged into window on 2024-04-26 14:52
   //
   //#include "framework.h"
   //#include "window.h"
   //#include "platform/system.h"
   //#include "acme/nano/nano.h"
   //#include "acme/nano/graphics/device.h"
   //#include "acme/nano/user/display.h"
   //#include "acme/operating_system/a_system_menu.h"
   //#include "acme/parallelization/synchronous_lock.h"
   //#include "acme/platform/application.h"
   //#include "acme/user/user/interaction_base.h"
   //#include "acme/windowing/windowing_base.h"
   //
   //
   //   namespace windowing
   //   {
   //

         //window::window() :
         //   m_pointCursor2(I32_MINIMUM)
         //{

         //   m_bRepositioningWindowFromCenter = false;
         //   m_bResizingWindowFromBottomRight = false;

         //}


         //window::~window()
         //{

         //   output_debug_string("window::~window()");

         //}



      ::acme::user::interaction * window::acme_user_interaction()
      {

         return m_pnanouserinteraction;

      }


      ::acme::windowing::window * window::acme_windowing_window()
      {

         return this;

      }


      //void window::on_initialize_particle()
      //{

      //   ::user::element::on_initialize_particle();

      //   _synchronous_lock synchronouslock(system()->acme_windowing()->synchronization());

      //   system()->acme_windowing()->m_windowbasea.add(this);

      //}


      //void window::destroy()
      //{

      //   ::user::element::destroy();

      //   _synchronous_lock synchronouslock(system()->acme_windowing()->synchronization());

      //   system()->acme_windowing()->m_windowbasea.erase(this);

      //}


      bool window::is_windowing_popup()
      {

         return false;

      }


      ::point_i32 window::windowing_popup_origin()
      {

         return {};

      }


      ::size_i32 window::windowing_popup_size()
      {

         return {};

      }


      void window::_on_windowing_close_window()
      {


      }


      bool window::is_satellite_window()
      {

         return false;

      }


      //window * window::user_interchange()
      //{

      //   return this;

      //}


      ::string window::get_window_text()
      {

         return {};

      }


      // ::pointer < ::operating_system::a_system_menu > window::create_system_menu(bool bContextual)
      // {
      //
      //    return ::micro::window::create_system_menu(bContextual);
      //
      // }


      //bool window::defer_perform_entire_reposition_process(::user::mouse * pmouse)
      //{

      //   return false;

      //}


      //bool window::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
      //{

      //   return false;

      //}



      // static thread_local ::pointer_array < window > t_nanowindowimplementationa;
      //
      //
      //
      // ::pointer_array < window > & window::nanowindowimplementationa()
      // {
      //
      //    return t_nanowindowimplementationa;
      //
      // }


      // window::window()
      // {
      //
      //
      // }
      //
      //
      // window::~window()
      // {
      //
      //    output_debug_string("window::~window()");
      //
      // }


      ::acme::windowing::display * window::get_display()
      {

         return nullptr;

      }


      // void window::draw(device * pnanodevice)
      // {
      //
      //    m_pinterface->draw(pnanodevice);
      //
      // }


      // bool window::get_dark_mode()
      // {
      //
      //    return m_pinterface->get_dark_mode();
      //
      // }


      //bool window::is_active_window()
      //{

      //   //return m_pinterface->is_active();

      //   return false;

      //}


      // void window::nano_window_on_create()
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




      void window::nano_window_on_destroy()
      {


      }


      //void window::create_window()
      //{

      //}


      void window::_create_window()
      {


      }


      //void window::on_create_window()
      //{

      //   m_pnanouserinteraction->on_create_window();

      //}




      //void window::show_window()
      //{

      //}


      //void window::hide_window()
      //{


      //}


      //void window::message_loop()
      //{


      //}


      //void window::set_active_window()
      //{


      //}



      //::point_i32 window::try_absolute_mouse_position(const ::point_i32 & point)
      //{

      //   //return window_interface::try_absolute_mouse_position(point);

      //   return point;

      //}


      //void window::handle(::topic * ptopic, ::context * pcontext)
      //{

      //   // if(ptopic->m_atom == id_operating_system_user_color_change)
      //   // {
      //   //
      //   //    update_drawing_objects();
      //   //
      //   //    redraw();
      //   //
      //   // }
      //   // else if(ptopic->m_atom == id_set_application_dark_mode)
      //   // {
      //   //
      //   //    update_drawing_objects();
      //   //
      //   //    redraw();
      //   //
      //   // }
      //   // else if(ptopic->m_atom == id_application_dark_mode_change)
      //   // {
      //   //
      //   //    update_drawing_objects();
      //   //
      //   //    redraw();
      //   //
      //   // }

      //}


      ::size_i32 window::get_main_screen_size()
      {

         auto pdisplay = get_display();

         if (::is_null(pdisplay))
         {

            return { 800, 600 };
         }

         return pdisplay->get_main_screen_size();

      }


      // ::payload window::do_synchronously(const class time & timeWait)
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
      //    // //   pmessagebox->m_functionClose = [&idResult, &event](micro::window * pwindow)
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
      //   micro::window::display();
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


      void window::_on_window_simple_action(const char * pszActionName)
      {

         if (!m_pnanouserinteraction)
         {

            throw ::exception(error_failed);

         }

         m_pnanouserinteraction->_on_window_simple_action(pszActionName);

      }


      void window::defer_show_system_menu(::user::mouse * pmouse)
      {


      }

      void window::window_message_loop_step()
      {


      }


      //void window::on_char(int iChar)
      //{


      //}

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
      //   micro::window::display();
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
      //   m_functionClose = [this](micro::window * pwindow)
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
      //         micro::window::display();
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


      void window::set_interface_client_size(const ::size_i32 & sizeWindow) // set_size
      {

         m_sizeWindow = sizeWindow;

      }


      void window::set_rectangle(const rectangle_i32 & rectangle)
      {

         auto r = rectangle;

         main_send([this, r]()
                   {

                      set_rectangle_unlocked(r);

                   });

      }


      void window::set_position(const point_i32 & point)
      {

         auto p = point;

         main_post([this, p]()
         {

            set_position_unlocked(p);

         });

      }


      void window::set_size(const size_i32 & size)
      {

         auto s = size;

         main_post([this, s]()
         {

            set_size_unlocked(s);

         });


      }


      void window::set_rectangle_unlocked(const rectangle_i32 & rectangle)
      {

         set_position_unlocked(rectangle.top_left());

         set_size_unlocked(rectangle.size());

      }


      void window::set_position_unlocked(const point_i32 & point)
      {


      }


      void window::set_size_unlocked(const size_i32 & size)
      {


      }


      ::rectangle_i32 window::get_window_rectangle()
      {

         ::rectangle_i32 rectangle;

         main_send([this, &rectangle]()
         {

            rectangle = get_window_rectangle_unlocked();

         });

         return rectangle;

      }


      ::rectangle_i32 window::get_window_rectangle_unlocked()
      {

         return {};

      }


      void window::on_a_system_menu_item(::operating_system::a_system_menu_item * psystemmenuitem)
      {

         ::string strActionName(psystemmenuitem->m_strAtom);

         if (strActionName == "minimize")
         {

            window_minimize();

         }
         else if (strActionName == "maximize")
         {

            window_maximize();

         }
         else if (strActionName == "maximize")
         {

            window_maximize();

         }
         else if (strActionName == "about_box")
         {

            application()->show_about_box();

         }
         else if (strActionName == "close")
         {

            window_close();

         }
         else if (strActionName == "")
         {

            print_line("reaching here?!");
            //defer_perform_entire_reposition_process(nullptr);

         }
         else if (strActionName == "")
         {

            print_line("also here");

            //defer_perform_entire_resizing_process(::experience::e_frame_sizing_top_left, nullptr);

         }



      }


      ::acme::windowing::window * window::owner_window()
      {

         return m_pnanowindowingwindowOwner;

      }


      //void window::window_message_loop()
      //{


      //}

   //} // namespace windowing

   } // namespace user


} //  namespace acme



