// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// Adapted by Camilo for android 2022-01-05 04:36 <3TBS (Thomas likes number 5), Mummi and bilbo!!
#include "framework.h"
#include "windowing.h"
#include "host_interaction.h"
#include "aura/platform/system.h"
#include "aura/windowing/sandbox/window.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/windowing/cursor_manager.h"


namespace sandbox_windowing
{


   windowing::windowing()
   {

      defer_create_mutex();

      m_psandboxwindowing = this;


   }


   windowing::~windowing()
   {


   }


   bool windowing::is_branch_current() const
   {

      auto itaskCurrent = get_current_itask();

      return itaskCurrent == m_itask;


   }


   ::windowing::window* windowing::new_window(::user::interaction_impl* pimpl)
   {

      ::pointer<::sandbox_windowing::window>pwindow;

      if (::is_null(m_psystem->m_paurasystem->m_pwindowMain->m_puserinteractionimpl))
      {

         pwindow = m_psystem->m_paurasystem->m_pwindowMain;

      }
      else
      {

         pwindow = pimpl->__create < ::windowing::window >();

      }

      if (!pwindow)
      {

         return nullptr;

      }

      pwindow->m_pwindowing = this;

      pwindow->m_puserinteractionimpl = pimpl;

      pimpl->m_pwindow = pwindow;

      pwindow->create_window(pimpl);

      return pwindow;

   }


   void windowing::erase_window(::windowing::window* pwindow)
   {

      //m_pdisplay->erase_window(pwindow);

   }


   void windowing::initialize(::object* pobject)
   {

      //auto estatus =
      //
      ::windowing::windowing::initialize(pobject);

      //      if(!estatus)
      //      {
      //
      //         return estatus;
      //
      //      }

      initialize_windowing();

      //auto pdisplay = __create < ::windowing::display >();

      ////      if(!pdisplay)
      ////      {
      ////
      ////         output_debug_string("\nFailed to __create < ::windowing::display > at windowing_x11::windowing::initialize");
      ////
      ////         return ::error_no_factory;
      ////
      ////      }

      //      //estatus =
      //      //
      //pdisplay->initialize_display(this);

      ////      if(!estatus)
      ////      {
      ////
      ////         output_debug_string("\nFailed to initialize_display at windowing_x11::windowing::initialize");
      ////
      ////         return estatus;
      ////
      ////      }

      //m_pdisplay = pdisplay;

      //if (!pdisplay)
      //{

      //   throw ::exception(error_no_interface, "Failed to cast pdisplay to m_pdisplay at windowing_x11::windowing::initialize");

      //}

      //m_pdisplay->open();


      //_libsn_start_context();


      //      if(!estatus)
      //      {
      //
      //         output_debug_string("\nFailed to m_pdisplay->open at windowing_x11::windowing::initialize");
      //
      //         return estatus;
      //
      //      }
      //
      //      return ::success;

   }


   void windowing::defer_initialize_host_window(const RECTANGLE_I32* lpcrect)
   {

      if (::is_set(m_phostinteraction))
      {

         return;

      }

      __construct_new(m_phostinteraction);

      m_phostinteraction->place(*lpcrect);

      m_phostinteraction->create_host();

      m_phostinteraction->display();

      m_phostinteraction->set_need_layout();

      m_phostinteraction->set_need_redraw();

      m_phostinteraction->post_redraw();

   }


   ::windowing::window* windowing::get_application_host_window()
   {

      return m_pwindowApplicationHost;

   }

   //   void windowing::start()
   //   {
   //
   //      auto psystem = m_psystem->m_papexsystem;
   //
   //      if (psystem->m_bUser)
   //      {
   //
   //         defer_initialize_x11();
   //
   //      }
   //
   //      auto pnode = psystem->node();
   //
   //      if(pnode)
   //      {
   //
   //         _libsn_start_context();
   //
   //         branch_element(pnode);
   //
   //      }
   //      else
   //      {
   //
   //         x11_main();
   //
   //      }
   //
   //      //return ::success;
   //
   //   }


   void windowing::windowing_post(const ::procedure& procedure)
   {

      if (!procedure)
      {

         throw ::exception(error_null_pointer);

      }

      synchronous_lock synchronouslock(mutex());

      m_procedurelist.add_tail(procedure);

      //return ::success_scheduled;

   }


   bool windowing::x11_runnable_step()
   {

      bool bHandled = false;

      //if (m_pdisplay)
      //{

      //   if (m_pdisplay->m_px11display)
      //   {

      //      while (m_pdisplay->m_px11display->x11_posted())
      //      {

      //         bHandled = true;

      //      }

      //   }

      //}

      synchronous_lock synchronouslock(mutex());

      if (m_procedurelist.is_empty())
      {

         return bHandled;

      }

      do
      {

         {

            auto routine = m_procedurelist.pick_head();

            synchronouslock.unlock();

            routine();

         }

         synchronouslock.lock();

      } while (m_procedurelist.has_element());

      return true;

   }


   //::windowing::display* windowing::display()
   //{

   //   return m_pdisplay;

   //}


   //::windowing_x11::window * windowing::_window(Window window)
   //{

   //   if (!m_pdisplay)
   //   {

   //      return nullptr;

   //   }

   //   auto pwindow = m_pdisplay->_window(window);

   //   return pwindow;

   //}


   ::pointer<::windowing::cursor>windowing::load_default_cursor(enum_cursor ecursor)
   {

      synchronous_lock synchronouslock(mutex());

      if (!m_pcursormanager)
      {

         //auto estatus =
         //
         //
         __construct_new(m_pcursormanager);

         //         if (!estatus)
         //         {
         //
         //            return nullptr;
         //
         //         }

      }

      //auto & pcursor = m_pcursormanager->m_cursormap[ecursor];

      //if (pcursor)
      //{

      //   return pcursor;

      //}

      //int iCursor = 0;

      //if (ecursor == e_cursor_size_top_left)
      //{

      //   iCursor = XC_top_left_corner;

      //}
      //else if (ecursor == e_cursor_size_top_right)
      //{

      //   iCursor = XC_top_right_corner;

      //}
      //else if (ecursor == e_cursor_size_top)
      //{

      //   iCursor = XC_top_side;

      //}
      //else if (ecursor == e_cursor_size_right)
      //{

      //   iCursor = XC_right_side;

      //}
      //else if (ecursor == e_cursor_size_left)
      //{

      //   iCursor = XC_left_side;

      //}
      //else if (ecursor == e_cursor_size_bottom)
      //{

      //   iCursor = XC_bottom_side;

      //}
      //else if (ecursor == e_cursor_size_bottom_left)
      //{

      //   iCursor = XC_bottom_left_corner;

      //}
      //else if (ecursor == e_cursor_size_bottom_right)
      //{

      //   iCursor = XC_bottom_right_corner;

      //}
      //else if (ecursor == e_cursor_arrow)
      //{

      //   iCursor = XC_arrow;

      //}

      //if (iCursor == 0)
      //{

      //   return nullptr;

      //}

      //synchronous_lock sl(user_mutex());

      windowing_output_debug_string("\n::x11_GetWindowRect 1");

      //display_lock lock(m_pdisplay->Display());

      //auto cursor = XCreateFontCursor(m_pdisplay->Display(), iCursor);

      //auto pcursorX11 = __create < ::windowing_x11::cursor >();

      //pcursor = pcursorX11;

      //pcursorX11->m_cursor = cursor;

      //return pcursor;

      return nullptr;

   }


   ::windowing::window* windowing::window(oswindow oswindow)
   {

      return oswindow;

   }


   void windowing::_message_handler(void* p)
   {

      //XEvent* pevent = (XEvent*)p;

   }


   ::windowing::window* windowing::get_keyboard_focus(::thread*)
   {

      //auto pwindowApplicationHost = get_application_host_window();

      //if (!pwindowApplicationHost->m_puserinteractionimpl->m_puserinteractionKeyboardFocus)
      //{

      //   return nullptr;

      //}

      //return pwindowApplicationHost;

      return m_pwindowKeyboardFocus;

   }


   ::windowing::window* windowing::get_mouse_capture(::thread*)
   {

      //if (!m_pdisplay)
      //{

      //   return nullptr;

      //}

      ////auto pwindow = m_pdisplay->get_mouse_capture();

      ////return pwindow;

      return m_pwindowMouseCapture;

   }


   void windowing::release_mouse_capture()
   {

      if (!m_pwindowMouseCapture)
      {

         return;

      }

      auto puserinteractionimpl = m_pwindowMouseCapture->m_puserinteractionimpl;

      if (puserinteractionimpl)
      {

         puserinteractionimpl->m_puserinteractionMouseCapture.release();

      }

      m_pwindowMouseCapture.release();

   }


   void windowing::clear_keyboard_focus(::user::element* pelementGainingFocusIfAny)
   {

      if (!m_pwindowKeyboardFocus)
      {

         return;

      }

      auto puserinteractionimpl = m_pwindowKeyboardFocus->m_puserinteractionimpl;

      if (puserinteractionimpl)
      {
         
         puserinteractionimpl->clear_keyboard_focus();

         //puserinteractionimpl->on_fin
//         auto puserinteractionKeyboardFocus = puserinteractionimpl->m_puserinteractionKeyboardFocus;
//
//         if (puserinteractionKeyboardFocus)
//         {
//
//            puserinteractionimpl->m_puserinteractionKeyboardGainingFocusIfAny = pwindowGainingFocusIfAny;
//
//            //puserinteractionimpl->m_puserinteractionKeyboardFocus->post_message(e_message_kill_focus);
//
//            puserinteractionimpl->m_puserinteractionKeyboardFocus.release();

         //}
            //auto puserinteraction =

//         if (puserinteraction)
//         {
//
//            puserinteraction->post_message(e_message_kill_focus);
//
//         }
//
//         //if (puserinteractionimpl->m_puserinteractionKeyboardFocus)
//         //{
//
//         //   puserinteractionimpl->m_puserinteractionKeyboardGainingFocusIfAny = pwindowGainingFocusIfAny;
//
//         //   puserinteractionimpl->m_puserinteractionKeyboardFocus->post_message(e_message_kill_focus);
//
//         //}
//
//         puserinteractionimpl->m_puserinteractionKeyboardFocus.release();

      //}

      if(!pelementGainingFocusIfAny || pelementGainingFocusIfAny->m_puserinteraction->window() !=
         m_pwindowKeyboardFocus)
      {
      
         m_pwindowKeyboardFocus.release();
         
      }

      //auto estatus =
      //
      //m_pdisplay->release_mouse_capture();

      //      if(!estatus)
      //      {
      //
      //         return estatus;
      //
      //      }
      //
      //      return estatus;
         
      }

   }


   ::pointer<::windowing::cursor>windowing::get_cursor(enum_cursor ecursor)
   {

      return nullptr;

   }


} // namespace sandbox_windowing


