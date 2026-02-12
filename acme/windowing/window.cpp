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
//   //
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
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/user/micro/elemental.h"
#include "acme/user/micro/user.h"
#include "acme/user/user/frame_interaction.h"
#include "acme/user/user/interaction.h"
#include "acme/user/user/mouse.h"
#include "acme/constant/windowing2.h"


namespace acme
{


   namespace windowing
   {


      window::window() :
         m_pointCursor2(I32_MINIMUM)
      {
         m_bMouseOn = false;
         m_bPerformingEntireRepositionProcess = false;
         m_bPerformingEntireResizingProcess = false;
         //m_ebias = e_bias_unknown;
         m_bRepositioningWindowFromCenter = false;
         m_bResizingWindowFromBottomRight = false;

         //}
         //{

         //m_bTopMost = false;

         //m_bNcActive = false;

         //m_bStartCentered = false;

         //m_bArbitraryPositioning = false;

         //m_bCapture = false;

         //m_uAcmeWindowingWindowFlags = 0;

         m_lX11NativeVisualId = -1;

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


      void window::initialize_window(::acme::user::interaction* pacmeuserinteraction)
      {

         if (::is_null(pacmeuserinteraction))
         {

            throw ::exception(error_wrong_state);

         }

         m_pacmeuserinteraction = pacmeuserinteraction;

      }


      // ::oswindow window::oswindow()
      // {
      //
      //
      //    return nullptr;
      //
      // }


      long window::__x11_Window()
      {

         return 0;

      }


      void * window::__x11_Display()
      {

         return nullptr;

      }


      void * window::__win32_HWND()
      {

         return nullptr;

      }




      ::windowing::enum_bias window::windowing_bias() const
      {

         auto psystem = system();

         if (::is_null(psystem))
         {

            return ::windowing::e_bias_unknown;

         }

         auto pacmewindowing = psystem->acme_windowing();

         if (::is_null(pacmewindowing))
         {

            return ::windowing::e_bias_unknown;

         }

         return pacmewindowing->windowing_bias();

      }


      void window::on_initialize_particle()
      {

         ::user::element::on_initialize_particle();

         //m_ebias = calculate_bias();

         //øconstruct(m_pacmeuserinteraction);

         //m_pacmeuserinteraction->m_pacmeuserinteraction = this;

         //system()->acme_windowing()->m_interchangea.add(this);

         //::user::element::on_initialize_particle();

         //_synchronous_lock synchronouslock(system()->acme_windowing()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         //system()->acme_windowing()->m_windowbasea.add(this);


      }





      //::int_rectangle window::get_window_rectangle()
      //{

      //   return m_rectangle;

      //}




      void window::create_window()
      {

         //m_pacmeuserinteraction->create_window();

      }


      void window::on_create_window()
      {

         //update_drawing_objects();

         m_pacmeuserinteraction->on_create_window();


      }


      void window::destroy()
      {

         __check_refdbg


         m_pacmeuserinteraction.release();

         __check_refdbg
         m_psystemmenu.release();
         __check_refdbg

         //m_pacmeuserinteraction.release();
         m_pacmeuserinteractionKeyboardFocus.release();
         __check_refdbg
         m_pacmeuserinteractionHover.release();
         __check_refdbg
         m_pacmeuserinteractionMouseCapture.release();
         //__check_refdbg
         //m_pacmeuserinteractionOwner.release();
         __check_refdbg

         m_pacmewindowingdisplayWindow.release();
         __check_refdbg




         //if (m_functionClose)
         //{

         //   m_functionClose(m_pacmeuserinteraction);

         //   m_functionClose.clear();

         //}

         auto psystem = system();

         if(psystem)
         {

            auto pacmewindowing = psystem->acme_windowing();
         
            if (pacmewindowing)
            {
               __check_refdbg

               pacmewindowing->m_windowa.erase(this);
               __check_refdbg

            }

         }

         //_synchronous_lock synchronouslock(system()->acme_windowing()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         //system()->acme_windowing()->m_windowbasea.erase(this);



         __check_refdbg

         ::user::element::destroy();
         __check_refdbg

      }


      void window::show_window()
      {

         //m_pacmeuserinteraction->show_window();

      }


      void window::hide_window()
      {

         //m_pacmeuserinteraction->hide();

      }


      void window::window_message_loop()
      {

         //m_pacmeuserinteraction->message_loop();

      }



      //void window::on_draw(::nano::graphics::device * pnanodevice)
      //{

      //   //m_pacmeuserinteraction->draw(pnanodevice);

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

         ::cast < ::acme::user::frame_interaction > pframeinteraction = m_pacmeuserinteraction;

         if (!pframeinteraction)
         {

            return true;

         }

         return pframeinteraction->m_bNcActive;

      }


      void window::set_active_window()
      {
         //
           //       m_pacmeuserinteraction->set_active_window();

      }

   
   void window::exit_iconify()
   {
      
      
   }
   
   
   void window::full_screen(const ::int_rectangle & rect)
   {
      
      
   }
   
   
   void window::exit_full_screen()
   {
      
      
   }
   
   
   void window::exit_zoomed()
   {
      
      
   }
 
   
   void window::set_parent(::acme::windowing::window* pwindowNewParent)
   {
      
   }
   //virtual ::e_status set_parent(::windowing::window * pwindowNewParent) override;
   //virtual long get_state();
   bool window::is_iconic()
   {
      
      return false;
      
   }
   //virtual bool is_window_visible() override;
//   bool window::_configure_window_unlocked(const class ::zorder & zorder, const ::user::e_activation & useractivation, bool bNoZorder, ::e_display edisplay)
//   {
//      
//      return true;
//   
//   }
   //virtual iptr get_window_long_ptr(int nIndex);
   //virtual iptr set_window_long_ptr(int nIndex, iptr l);
   bool window::client_to_screen(::int_point* ppoint)
   {
      
      
      return true;
      
   }
   
   bool window::screen_to_client(::int_point* ppoint)
   {
      
      return true;
      
   
   }
   
   
   //virtual bool set_window_pos(class::zorder zorder, int x, int y, int cx, int cy,unsigned int nFlags);
   //virtual bool _set_window_pos(class::zorder zorder, int x, int y, int cx, int cy,unsigned int nFlags);
   
   
   bool window::is_destroying()
   {
      
      return false;
      
   }
   
   
   //virtual bool bamf_set_icon();
   
   
   //virtual bool set_icon(::image::image* pimage);
   
   //virtual int x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements);
   
   void window::set_mouse_cursor(::windowing::cursor* pcursor)
   {
      
      
   }

   
      //bool window::get_dark_mode()
      //{

      //   return system()->dark_mode();


      //}


      void window::set_user_interaction(::acme::user::interaction * pacmeuserinteraction)
      {

         m_pacmeuserinteraction = pacmeuserinteraction;

         m_pacmeuserinteraction->m_pacmewindowingwindow = this;

      }


      void window::set_user_thread(::user::thread* puserthread)
      {


      }


      void window::set_user_graphics_thread(::user::graphics_thread * pusergraphicsthread)
      {


      }


      bool window::defer_perform_entire_reposition_process(::user::mouse * pmouse)
      {

         if (m_pacmeuserinteraction)
         {

            if (m_pacmeuserinteraction->defer_perform_entire_reposition_process(pmouse))
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


      void window::_on_reposition(int x, int y)
      {


      }


      void window::_on_size(int cx, int cy)
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


      void window::on_window_deiconified()
      {


      }


      void window::on_window_activated()
      {


      }


      void window::on_window_iconified()
      {


      }


      void window::on_window_deactivated()
      {


      }


      void window::on_window_shown()
      {


      }


      void window::on_window_hidden()
      {


      }


      bool window::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse)
      {

         if (m_pacmeuserinteraction)
         {

            if (m_pacmeuserinteraction->defer_perform_entire_resizing_process(eframeSizing, pmouse))
            {

               return true;

            }

         }

         return false;

      }


      //::int_point window::try_absolute_mouse_position(const ::int_point & point)
      //{

      //   return m_pacmeuserinteraction->try_absolute_mouse_position(point);

      //}


      ::int_point window::origin()
      {

         return m_rectangle.origin();

      }






      //void window::set_position(const ::int_point & point)
      //{

      //   m_pacmeuserinteraction->set_position(point);

      //}


      void window::redraw()
      {

         m_pacmeuserinteraction->redraw();

      }


      void window::set_interaction_rectangle(const ::int_rectangle & rectangle)
      {

         m_rectangle = rectangle;

      }


      ::int_rectangle window::get_rectangle()
      {

         return m_rectangle;

      }


      //::int_rectangle window::get_window_rectangle()
      //{

      //   //::int_rectangle rectangle;

      //   //rectangle.left = 0;
      //   //rectangle.top = 0;
      //   //rectangle.right = m_rectangle.width();
      //   //rectangle.bottom = m_rectangle.height();

      //   //return rectangle;

      //   return {};

      //}


      // ::int_rectangle window::get_window_rectangle()
      // {
      //
      //    return m_rectangle;
      //
      // }


      void window::set_mouse_capture()
      {

         ::cast < ::acme::user::frame_interaction > pframeinteraction = m_pacmeuserinteraction;

         if (pframeinteraction && pframeinteraction->m_bCapture)
         {

            return;

         }

         m_pacmeuserinteraction->set_mouse_capture();

         if (pframeinteraction)
         {

            pframeinteraction->m_bCapture = true;

         }

      }


      void window::set_cursor(enum_cursor ecursor)
      {

         m_pacmeuserinteraction->set_cursor(ecursor);

      }


      bool window::_is_window()
      {

         return false;

      }
   
   
   
   void window::set_foreground_window(::user::activation_token * puseractivationtoken)
   {
      
      
   }
   
   
    bool window::has_keyboard_focus()
   {
       
       return false;
       
   
    }


    void window::set_keyboard_focus(::acme::user::interaction * pacmeuserinteractionFocus)
    {

       m_pacmeuserinteractionKeyboardFocus = pacmeuserinteractionFocus;

         if (!has_keyboard_focus())
         {

            set_keyboard_focus();

         }

    }


   void window::set_keyboard_focus()
   {

   }

    //void window::erase_keyboard_focus(::acme::user::interaction * pacmeuserinteractionFocus)
    //{

    //   _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

    //   if (pacmeuserinteractionFocus == m_pacmeuserinteractionKeyboardFocus)
    //   {

    //      set_keyboard_focus(nullptr);

    //   }

    //}

    bool window::is_window()
   {
       return _is_window();
       
    
    }
   //virtual int_bool is_window( windowing_android_WINDOW_MEMBER );
   
   
   void window::set_window_text(const ::scoped_string & scopedstrString)
   {
      

   }


      bool window::has_mouse_capture()
      {

         //return m_pacmeuserinteraction->has_mouse_capture();

         auto pacmewindowing = system()->acme_windowing();

         if(::is_null(pacmewindowing))
         {

            return false;

         }

         auto pacmewindowingwindowMouseCapture = pacmewindowing->get_mouse_capture(nullptr);

         if(::is_null(pacmewindowingwindowMouseCapture))
         {

            return false;

         }

         if(pacmewindowingwindowMouseCapture != this)
         {

            return false;

         }

         return true;

      }


      void window::release_mouse_capture()
      {

         m_pacmeuserinteractionMouseCapture = nullptr;

         ::cast < ::acme::user::frame_interaction > pframeinteraction = m_pacmeuserinteraction;

         if (!pframeinteraction || !pframeinteraction->m_bCapture)
         {

            return;

         }

         if (pframeinteraction)
         {

            pframeinteraction->m_bCapture = false;

         }

         m_pacmeuserinteraction->release_mouse_capture();

      }


      ::pointer<::nano::graphics::device>window::create_device()
      {

         throw interface_only();

         return nullptr;

      }


      void window::on_mouse_enter()
      {


      }


      void window::fore_on_mouse_move(::user::mouse * pmouse)
      {
         
         if (m_pacmeuserinteractionMouseCapture
   && m_pacmeuserinteractionMouseCapture != this)
         {

            ::pointer<::micro::elemental> pelemental;

            pelemental = m_pacmeuserinteractionMouseCapture;

            if (pelemental)
            {

               pelemental->fore_on_mouse_move(pmouse);

               if (pmouse->m_bRet)
               {

                  return;

               }

            }

         }

         auto pchild = m_pacmeuserinteraction->acme_hit_test(pmouse, ::user::e_zorder_front);

         if (pchild)
         {

            if (acme_windowing_window()->m_pacmeuserinteractionHover != pchild)
            {

               if (acme_windowing_window()->m_pacmeuserinteractionHover)
               {

                  acme_windowing_window()->m_pacmeuserinteractionHover->on_mouse_leave();

               }

               acme_windowing_window()->m_pacmeuserinteractionHover = pchild;

               acme_windowing_window()->m_pacmeuserinteractionHover->on_mouse_enter();

            }

            pchild->fore_on_mouse_move(pmouse);

            if (pmouse->m_bRet)
            {

               return;

            }

         }

      }


      void window::back_on_mouse_move(::user::mouse * pmouse)
      {
         if (m_pacmeuserinteractionMouseCapture
&& m_pacmeuserinteractionMouseCapture != this)
         {

            ::pointer<::micro::elemental> pelemental;

            pelemental = m_pacmeuserinteractionMouseCapture;

            if (pelemental)
            {

               pelemental->back_on_mouse_move(pmouse);

               if (pmouse->m_bRet)
               {

                  return;

               }

            }

         }

         auto pchild = m_pacmeuserinteraction->acme_hit_test(pmouse, ::user::e_zorder_back);

         if (pchild)
         {

            //if (acme_windowing_window()->m_pacmeuserinteractionHover != pchild)
            //{

            //   if (acme_windowing_window()->m_pacmeuserinteractionHover)
            //   {

            //      acme_windowing_window()->m_pacmeuserinteractionHover->on_mouse_leave();

            //   }

            //   acme_windowing_window()->m_pacmeuserinteractionHover = pchild;

            //   acme_windowing_window()->m_pacmeuserinteractionHover->on_mouse_enter();

            //}

            pchild->fore_on_mouse_move(pmouse);

            if (pmouse->m_bRet)
            {

               return;

            }

         }


      }


      void window::on_mouse_leave()
      {

         if (m_pacmeuserinteractionHover)
         {
            
            m_pacmeuserinteractionHover->on_mouse_leave();

            m_pacmeuserinteractionHover = nullptr;

         }

      }


      ::pointer < ::user::activation_token> window::get_initial_frame_display_activation_token()
      {

         return nullptr;

      }



      //void window::_run_modal_loop()
      //{

      //   m_pacmeuserinteraction->_run_modal_loop();

      //}



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


      //::payload window::do_synchronously(const class time & timeWait)
      //{

      //   create_window();

      //   show_window();

      //   acme_windowing_window()->window_message_loop();

      //   return m_pacmeuserinteraction->m_payloadResult;

      //}





      void window::handle(::topic * ptopic, ::handler_context * phandlercontext)
      {

         if (ptopic->id() == id_set_application_dark_mode)
         {

            m_pacmeuserinteraction->handle(ptopic, phandlercontext);

         }

      }


      //::user::item & window::user_item(const ::item * pitem)
      //{
      //
      //   return m_useritemmap[pitem];
      //
      //}


      //void window::do_asynchronously()
      //{

      //   create_window();

      //   show_window();

      //}

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
   //#include "acme/user/micro/display.h"
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

         return m_pacmeuserinteraction;

      }


      ::acme::windowing::window * window::acme_windowing_window()
      {

         return this;

      }


      //void window::on_initialize_particle()
      //{

      //   ::user::element::on_initialize_particle();

      //   _synchronous_lock synchronouslock(system()->acme_windowing()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //   system()->acme_windowing()->m_windowbasea.add(this);

      //}


      //void window::destroy()
      //{

      //   ::user::element::destroy();

      //   _synchronous_lock synchronouslock(system()->acme_windowing()->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //   system()->acme_windowing()->m_windowbasea.erase(this);

      //}


      bool window::is_windowing_popup()
      {

         return false;

      }


      ::int_point window::windowing_popup_origin()
      {

         return {};

      }


      ::int_size window::windowing_popup_size()
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


      ::itask window::get_itask() const
      {

         return system()->acme_windowing()->m_itask;

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


   
   ::particle * window::get_acme_window_bridge()
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


      void window::on_window_close()
      {

         m_pacmeuserinteraction->on_window_close();

      }


      //void window::create_window()
      //{

      //}


      void window::_create_window()
      {


      }


      //void window::on_create_window()
      //{

      //   m_pacmeuserinteraction->on_create_window();

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



      //::int_point window::try_absolute_mouse_position(const ::int_point & point)
      //{

      //   //return window_interface::try_absolute_mouse_position(point);

      //   return point;

      //}


      //void window::handle(::topic * ptopic, ::handler_context * phandlercontext)
      //{

      //   // if(ptopic->id() == id_operating_system_user_color_change)
      //   // {
      //   //
      //   //    update_drawing_objects();
      //   //
      //   //    redraw();
      //   //
      //   // }
      //   // else if(ptopic->id() == id_set_application_dark_mode)
      //   // {
      //   //
      //   //    update_drawing_objects();
      //   //
      //   //    redraw();
      //   //
      //   // }
      //   // else if(ptopic->id() == id_application_dark_mode_change)
      //   // {
      //   //
      //   //    update_drawing_objects();
      //   //
      //   //    redraw();
      //   //
      //   // }

      //}


      // ::int_size window::get_main_screen_size()
      // {
      //
      //    auto pdisplay = get_display();
      //
      //    if (::is_null(pdisplay))
      //    {
      //
      //       return { 800, 600 };
      //    }
      //
      //    return pdisplay->get_main_screen_size();
      //
      // }


      // ::payload window::do_synchronously(const class time & timeWait)
      // {
      //
      //    create();
      //
      //    m_pinterface->show_window();
      //
      //    message_loop();
      //
      //    // auto pmanualresethappening = øallocate manual_reset_happening();
      //    //
      //    // m_pinterface->m_psequencer->then([ pmanualresethappening](auto psequencer)
      //    // {
      //    //
      //    //    pmanualresethappening->set_happening();
      //    //
      //    // });
      //    //
      //    // auto pinterface = m_pinterface;
      //    //
      //    // if(pinterface->m_payloadResult.is_new())
      //    // {
      //    //
      //    //    pmanualresethappening->wait();
      //    //
      //    // }
      //    //
      //    // //   auto pmessagebox = pparticle->øcreate_new < message_box >();
      //    // //
      //    // //   atom idResult;
      //    // //
      //    // //   manual_reset_happening happening;
      //    // //
      //    // //   pmessagebox->display(scopedstrMessage, pszTitle, emessagebox, pszDetails);
      //    // //
      //    // //   pmessagebox->m_functionClose = [&idResult, &happening](micro::window * pwindow)
      //    // //   {
      //    // //
      //    // //      idResult = pwindow->m_atomResult;
      //    // //
      //    // //      happening.set_happening();
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
      //    // //      happening.wait();
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


      void window::_on_window_simple_action(const_char_pointer pszActionName, ::user::activation_token * puseractivationtoken)
      {

         if (!m_pacmeuserinteraction)
         {

            throw ::exception(error_failed);

         }

         m_pacmeuserinteraction->_on_window_simple_action(pszActionName, puseractivationtoken);

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


      void window::set_interface_client_size(const ::int_size & sizeWindow) // set_size
      {

         m_sizeWindow = sizeWindow;

      }


      void window::set_rectangle(const int_rectangle & rectangle)
      {

         auto r = rectangle;

         main_send([this, r]()
                   {

                      set_rectangle_unlocked(r);

                   });

      }


      void window::set_position(const int_point & point)
      {

         auto p = point;

         main_post([this, p]()
         {

            set_position_unlocked(p);

         });

      }


      void window::set_size(const int_size & size)
      {

         auto s = size;

         main_post([this, s]()
         {

            set_size_unlocked(s);

         });


      }


      void window::set_rectangle_unlocked(const int_rectangle & rectangle)
      {

         set_size_unlocked(rectangle.size());

         set_position_unlocked(rectangle.top_left());

      }


      void window::set_position_unlocked(const int_point & point)
      {


      }


      void window::set_size_unlocked(const int_size & size)
      {


      }


      ::int_rectangle window::get_window_rectangle()
      {

         ::int_rectangle rectangle;

         main_send([this, &rectangle]()
         {

            rectangle = get_window_rectangle_unlocked();

         });

         return rectangle;

      }


      ::int_rectangle window::get_window_rectangle_unlocked()
      {

         return {};

      }


      void window::on_a_system_menu_item(::operating_system::a_system_menu_item * psystemmenuitem, ::user::activation_token * puseractivationtoken)
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

            application()->show_about_box(puseractivationtoken);

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

      ::windowing::window * window::windowing_window()
      {

         return nullptr;

      }


      ::acme::user::interaction * window::owner_interaction()
      {

         auto puserinteraction = m_pacmeuserinteraction.get();

         if (::is_null(puserinteraction))
         {

            return nullptr;

         }

         auto puserinteractionOwner = puserinteraction->m_pacmeuserinteractionOwner.get();

         if (::is_null(puserinteractionOwner))
         {

            return nullptr;

         }

         return puserinteractionOwner;

      }


      ::acme::windowing::window * window::owner_window()
      {

         auto puserinteractionOwner = owner_interaction();

         if(::is_null(puserinteractionOwner))
         {

            return nullptr;

         }

         return puserinteractionOwner->acme_windowing_window();

      }
   int window::control_box_right_when_at_left() const
   {
      
      
      return -1;
   }
   
   
   bool window::should_use_desktop_ambient_like_control_box() const
   {
      
      auto pacmeuserinteraction = m_pacmeuserinteraction.m_p;
      
      if(::is_null(pacmeuserinteraction))
      {
         
         return false;
         
      }

      return pacmeuserinteraction->should_use_desktop_ambient_like_control_box();

   }
   
   
void window::on_control_box_close()
{
 
   auto pacmeuserinteraction = m_pacmeuserinteraction.m_p;
   
   if(::is_set(pacmeuserinteraction))
   {
      
      pacmeuserinteraction->on_control_box_close();
      
   }
 
}


void window::on_control_box_minimize()
{
 
   auto pacmeuserinteraction = m_pacmeuserinteraction.m_p;
   
   if(::is_set(pacmeuserinteraction))
   {
      
      pacmeuserinteraction->on_control_box_minimize();
      
   }

}


void window::on_control_box_zoom()
{
 
   auto pacmeuserinteraction = m_pacmeuserinteraction.m_p;
   
   if(::is_set(pacmeuserinteraction))
   {
      
      pacmeuserinteraction->on_control_box_zoom();
      
   }

}




      //void window::window_message_loop()
      //{


      //}

   //} // namespace windowing
   
      void window::get_os_window_handle(void *p, int iSize) 
      {
         
         throw ::interface_only();
      
      }


   void window::on_gpu_context_render_frame(int w, int h)
   
   {
      
      if(::is_null(m_pgpucontextrenderframe))
      {
         
         return;
         
         //throw ::exception(error_wrong_state);
         
      }
      
      m_pgpucontextrenderframe->on_gpu_context_render_frame(w, h);

   }

   
   void window::_lock_window_gpu_context()
   {
      
      
   }
   
   
    void  window::_unlock_window_gpu_context()
   {
       
    
    }

   

   } // namespace windowing


} //  namespace acme




CLASS_DECL_ACME void * HWND_from_acme_windowing_window(::acme::windowing::window * pacmewindowingwindow)
{

   if (::is_null(pacmewindowingwindow))
   {

      return nullptr;

   }

   auto pHWND = pacmewindowingwindow->__win32_HWND();

   return pHWND;

}