// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// Adapted by Camilo for android 2022-01-05 04:36 <3TBS (Thomas likes number 5), Mummi and bilbo!!
#include "framework.h"
#include "windowing.h"
#include "host_interaction.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/platform/system.h"
#include "aura/windowing/sandbox/window.h"
//#include "aura/user/user/interaction_impl.h"
#include "aura/windowing/cursor_manager.h"


namespace sandbox_windowing
{


   windowing::windowing()
   {

      defer_create_synchronization();

      m_psandboxwindowing = this;


   }


   windowing::~windowing()
   {


   }


   bool windowing::is_branch_current() const
   {

      auto itaskCurrent = current_itask();

      return itaskCurrent == m_itask;


   }


::pointer < ::acme::windowing::window > windowing::get_new_window()
{
   
auto      pwindow = ::windowing::windowing::get_new_window();
   
   return pwindow;
   
}
//
//   ::windowing::window* windowing::new_window(::windowing::window* pimpl)
//   {
//
//      ::pointer<::sandbox_windowing::window>pwindow;
//
//      if (::is_null(system()->m_pwindowMain->m_pwindow))
//      {
//
//         pwindow = system()->m_pwindowMain;
//
//      }
//      else
//      {
//
//         pwindow = pimpl->øcreate < ::windowing::window >();
//
//      }
//
//      if (!pwindow)
//      {
//
//         return nullptr;
//
//      }
//
//      pwindow->m_pwindowing = this;
//
//      pwindow->m_pwindow = pimpl;
//
//      pimpl->m_pwindow = pwindow;
//
//      pwindow->create_window(pimpl);
//
//      return pwindow;
//
//   }


   void windowing::erase_window(::windowing::window* pwindow)
   {

      //m_pdisplay->erase_window(pwindow);

   }


   void windowing::initialize(::particle * pparticle)
   {

      //auto estatus =
      //
      ::windowing::windowing::initialize(pparticle);

      //      if(!estatus)
      //      {
      //
      //         return estatus;
      //
      //      }

      initialize_windowing();

      //auto pdisplay = øcreate < ::windowing::display >();

      ////      if(!pdisplay)
      ////      {
      ////
      ////         informationf("----> Failed to øcreate < ::windowing::display > at windowing_x11::windowing::initialize");
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
      ////         informationf("----> Failed to initialize_display at windowing_x11::windowing::initialize");
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


      //_libsnx_start_context();


      //      if(!estatus)
      //      {
      //
      //         informationf("----> Failed to m_pdisplay->open at windowing_x11::windowing::initialize");
      //
      //         return estatus;
      //
      //      }
      //
      //      return ::success;

   }


::particle * windowing::defer_initialize_host_window(const ::int_rectangle* lpcrect)
   {

//      if (::is_set(m_phostinteraction))
//      {
//
//         return;
//
//      }
//
//      //øconstruct_new(m_phostinteraction);
//      
//      øconstruct(m_phostinteraction);
//
//      //m_phostinteraction->place(*lpcrect);
//
//      //m_phostinteraction->create_host(e_parallelization_synchronous);
//      m_phostinteraction->create_host();
//
//      m_phostinteraction->display();
//      
//      m_phostinteraction->m_bNeedPerformLayout = true;
//
//      m_phostinteraction->set_need_layout();
//
//      m_phostinteraction->set_need_redraw();
//
//      m_phostinteraction->post_redraw();

      if(::is_set(m_pwindowApplicationHost))
      {

         auto pacmewindowbridge = m_pwindowApplicationHost->get_acme_window_bridge();

         return pacmewindowbridge;
         
      }
      
      øconstruct(m_phostinteraction);
//      
//      auto pacmewindowingwindow =       m_phostinteraction->acme_windowing_window();
   
   
   
      ::cast < ::sandbox_windowing::host_interaction > phostinteraction = m_phostinteraction;
      
      phostinteraction->create_window();
      
      phostinteraction->add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen);

      if(::is_set(lpcrect) && !lpcrect->is_empty())
      {

         phostinteraction->place(*lpcrect);

      }
      
      phostinteraction->display();
      
      phostinteraction->m_bNeedPerformLayout = true;
      
      phostinteraction->set_need_layout();
      
      phostinteraction->set_need_redraw();
      
      phostinteraction->post_redraw();
      
      m_pwindowApplicationHost = phostinteraction->window();
   
      auto pacmewindowbridge = m_pwindowApplicationHost->get_acme_window_bridge();
   
      return pacmewindowbridge;
      
   }


   ::acme::windowing::window* windowing::get_application_host_window()
   {

      return m_pwindowApplicationHost;

   }

   //   void windowing::start()
   //   {
   //
   //      auto psystem = system();
   //
   //      if (psystem->m_bUser)
   //      {
   //
   //         deferx_initializex_x11();
   //
   //      }
   //
   //      auto pnode = psystem->node();
   //
   //      if(pnode)
   //      {
   //
   //         _libsnx_start_context();
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


   //void windowing::windowing_post(const ::procedure& procedure)
   //{

   //   if (!procedure)
   //   {

   //      throw ::exception(error_null_pointer);

   //   }

   //   synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   //   m_procedurelist.add_tail(procedure);

   //   //return ::success_scheduled;

   //}


   // bool windowing::aaa_x11_runnable_step()
   // {

   //    bool bHandled = false;

   //    //if (m_pdisplay)
   //    //{

   //    //   if (m_pdisplay->m_px11display)
   //    //   {

   //    //      while (m_pdisplay->m_px11display->aaa_x11_posted())
   //    //      {

   //    //         bHandled = true;

   //    //      }

   //    //   }

   //    //}

   //    synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   //    if (m_procedurelist.is_empty())
   //    {

   //       return bHandled;

   //    }

   //    do
   //    {

   //       {

   //          auto routine = m_procedurelist.pick_head();

   //          synchronouslock.unlock();

   //          routine();

   //       }

   //       synchronouslock.lock();

   //    } while (m_procedurelist.has_element());

   //    return true;

   // }


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

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (!m_pcursormanager)
      {

         //auto estatus =
         //
         //
         øconstruct_new(m_pcursormanager);

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

      //synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      windowing_output_debug_string("::x11_GetWindowRect 1");

      //display_lock lock(m_pdisplay->Display());

      //auto cursor = XCreateFontCursor(m_pdisplay->Display(), iCursor);

      //auto pcursorX11 = øcreate < ::windowing_x11::cursor >();

      //pcursor = pcursorX11;

      //pcursorX11->m_cursor = cursor;

      //return pcursor;

      return nullptr;

   }


   ::acme::windowing::window* windowing::window(oswindow oswindow)
   {

      return oswindow;

   }


   void windowing::_message_handler(void* p)
   {

      //XEvent* pevent = (XEvent*)p;

   }


   ::acme::windowing::window * windowing::get_keyboard_focus(::thread*)
   {

      //auto pwindowApplicationHost = get_application_host_window();

      //if (!pwindowApplicationHost->m_pwindow->aaa_m_pacmeuserinteractionKeyboardFocus)
      //{

      //   return nullptr;

      //}

      //return pwindowApplicationHost;

      return m_pwindowKeyboardFocus;

   }


   ::acme::windowing::window* windowing::get_mouse_capture(::thread*)
   {

      //if (!m_pdisplay)
      //{

      //   return nullptr;

      //}

      ////auto pwindow = m_pdisplay->get_mouse_capture();

      ////return pwindow;

      return m_pacmewindowingwindowMouseCapture;

   }


   bool windowing::defer_release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow)
   {

      if (!m_pacmewindowingwindowMouseCapture)
      {

         return false;

      }

      if (m_pacmewindowingwindowMouseCapture != pwindow)
      {

         return false;

      }
      
      ::cast < ::windowing::window > pwindowingwindow = pwindow;

      pwindowingwindow->m_pacmeuserinteractionMouseCapture.release();

      m_pacmewindowingwindowMouseCapture.release();

      return true;

   }

//
//   void windowing::clear_keyboard_focus(::user::element* pelementGainingFocusIfAny)
//   {
//
//      if (!m_pwindowKeyboardFocus)
//      {
//
//         return;
//
//      }
//
//      ::cast < ::windowing::window > pwindow = m_pwindowKeyboardFocus;
//
//      if (pwindow)
//      {
//         
//         pwindow->clear_keyboard_focus();
//
//         //pwindow->on_fin
////         auto puserinteractionKeyboardFocus = pwindow->aaa_m_pacmeuserinteractionKeyboardFocus;
////
////         if (puserinteractionKeyboardFocus)
////         {
////
////            pwindow->m_puserinteractionKeyboardGainingFocusIfAny = pwindowGainingFocusIfAny;
////
////            //pwindow->aaa_m_pacmeuserinteractionKeyboardFocus->post_message(::user::e_message_kill_focus);
////
////            pwindow->aaa_m_pacmeuserinteractionKeyboardFocus.release();
//
//         //}
//            //auto puserinteraction =
//
////         if (puserinteraction)
////         {
////
////            puserinteraction->post_message(::user::e_message_kill_focus);
////
////         }
////
////         //if (pwindow->aaa_m_pacmeuserinteractionKeyboardFocus)
////         //{
////
////         //   pwindow->m_puserinteractionKeyboardGainingFocusIfAny = pwindowGainingFocusIfAny;
////
////         //   pwindow->aaa_m_pacmeuserinteractionKeyboardFocus->post_message(::user::e_message_kill_focus);
////
////         //}
////
////         pwindow->aaa_m_pacmeuserinteractionKeyboardFocus.release();
//
//      //}
//
//      if(!pelementGainingFocusIfAny || pelementGainingFocusIfAny->window() !=
//         m_pwindowKeyboardFocus)
//      {
//      
//         m_pwindowKeyboardFocus.release();
//         
//      }
//
//      //auto estatus =
//      //
//      //m_pdisplay->release_mouse_capture();
//
//      //      if(!estatus)
//      //      {
//      //
//      //         return estatus;
//      //
//      //      }
//      //
//      //      return estatus;
//         
//      }
//
//   }


   ::pointer<::windowing::cursor>windowing::get_cursor(enum_cursor ecursor)
   {

      return nullptr;

   }


} // namespace sandbox_windowing


