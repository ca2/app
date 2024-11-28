// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// Adapted by Camilo for android 2022-01-05 04:36 <3TBS (Thomas likes number 5), Mummi and bilbo!!
// as acme::sandbox_windowing on 2024-11-25 23:23 by
// camilo <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "windowing.h"
#include "host_interaction.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"
#include "acme/windowing/sandbox/window.h"
//#include "aura/user/user/interaction_impl.h"
//#include "aura/windowing/cursor_manager.h"


namespace acme
{

namespace sandbox_windowing
{


windowing::windowing()
{
   
   defer_create_synchronization();
   
   //m_psandboxwindowing = this;
   
   
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
   
   auto      pwindow = ::acme::windowing::windowing::get_new_window();
   
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
//         pwindow = pimpl->__øcreate < ::windowing::window >();
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


void windowing::erase_window(::acme::windowing::window* pwindow)
{
   
   //m_pdisplay->erase_window(pwindow);
   
}


void windowing::initialize(::particle * pparticle)
{
   
   //auto estatus =
   //
   ::acme::windowing::windowing::initialize(pparticle);
   
   //      if(!estatus)
   //      {
   //
   //         return estatus;
   //
   //      }
   
   initialize_windowing();
   
   //auto pdisplay = __øcreate < ::windowing::display >();
   
   ////      if(!pdisplay)
   ////      {
   ////
   ////         informationf("\nFailed to __øcreate < ::windowing::display > at windowing_x11::windowing::initialize");
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
   ////         informationf("\nFailed to initialize_display at windowing_x11::windowing::initialize");
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
   //         informationf("\nFailed to m_pdisplay->open at windowing_x11::windowing::initialize");
   //
   //         return estatus;
   //
   //      }
   //
   //      return ::success;
   
}


void windowing::defer_initialize_host_window(const ::int_rectangle* lpcrect)
{
   
   //      if (::is_set(m_phostinteraction))
   //      {
   //
   //         return;
   //
   //      }
   //
   //      //__construct_new(m_phostinteraction);
   //
   //      __øconstruct(m_phostinteraction);
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
      
      return;
      
   }
   
   __øconstruct(m_phostinteraction);
   
   m_phostinteraction->create_window();
   
//   m_phostinteraction->add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen);
   
   m_phostinteraction->display();
   
//   m_phostinteraction->m_bNeedPerformLayout = true;
   
  // m_phostinteraction->set_need_layout();
   
   m_phostinteraction->set_need_redraw();
   
   m_phostinteraction->post_redraw();
   
   m_pwindowApplicationHost = m_phostinteraction->acme_windowing_window();
   
}


void windowing::_will_finish_launching()
{
   
   //defer_initialize_host_window(nullptr);
//
//   ::acme::windowing::windowing::_will_finish_launching();
   
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

//   synchronous_lock synchronouslock(this->synchronization());

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

//    synchronous_lock synchronouslock(this->synchronization());

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


//::pointer<::windowing::cursor>windowing::load_default_cursor(enum_cursor ecursor)
//{
//   
//   synchronous_lock synchronouslock(this->synchronization());
//   
//   if (!m_pcursormanager)
//   {
//      
//      //auto estatus =
//      //
//      //
//      __construct_new(m_pcursormanager);
//      
//      //         if (!estatus)
//      //         {
//      //
//      //            return nullptr;
//      //
//      //         }
//      
//   }
//   
//   //auto & pcursor = m_pcursormanager->m_cursormap[ecursor];
//   
//   //if (pcursor)
//   //{
//   
//   //   return pcursor;
//   
//   //}
//   
//   //int iCursor = 0;
//   
//   //if (ecursor == e_cursor_size_top_left)
//   //{
//   
//   //   iCursor = XC_top_left_corner;
//   
//   //}
//   //else if (ecursor == e_cursor_size_top_right)
//   //{
//   
//   //   iCursor = XC_top_right_corner;
//   
//   //}
//   //else if (ecursor == e_cursor_size_top)
//   //{
//   
//   //   iCursor = XC_top_side;
//   
//   //}
//   //else if (ecursor == e_cursor_size_right)
//   //{
//   
//   //   iCursor = XC_right_side;
//   
//   //}
//   //else if (ecursor == e_cursor_size_left)
//   //{
//   
//   //   iCursor = XC_left_side;
//   
//   //}
//   //else if (ecursor == e_cursor_size_bottom)
//   //{
//   
//   //   iCursor = XC_bottom_side;
//   
//   //}
//   //else if (ecursor == e_cursor_size_bottom_left)
//   //{
//   
//   //   iCursor = XC_bottom_left_corner;
//   
//   //}
//   //else if (ecursor == e_cursor_size_bottom_right)
//   //{
//   
//   //   iCursor = XC_bottom_right_corner;
//   
//   //}
//   //else if (ecursor == e_cursor_arrow)
//   //{
//   
//   //   iCursor = XC_arrow;
//   
//   //}
//   
//   //if (iCursor == 0)
//   //{
//   
//   //   return nullptr;
//   
//   //}
//   
//   //synchronous_lock sl(user_synchronization());
//   
//   windowing_output_debug_string("::x11_GetWindowRect 1");
//   
//   //display_lock lock(m_pdisplay->Display());
//   
//   //auto cursor = XCreateFontCursor(m_pdisplay->Display(), iCursor);
//   
//   //auto pcursorX11 = __øcreate < ::windowing_x11::cursor >();
//   
//   //pcursor = pcursorX11;
//   
//   //pcursorX11->m_cursor = cursor;
//   
//   //return pcursor;
//   
//   return nullptr;
//   
//}


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
   
   //if (!pwindowApplicationHost->m_pwindow->m_puserinteractionKeyboardFocus)
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
   
   return m_pwindowMouseCapture;
   
}


bool windowing::defer_release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow)
{
   
   if (!m_pwindowMouseCapture)
   {
      
      return false;
      
   }
   
   if (m_pwindowMouseCapture != pwindow)
   {
      
      return false;
      
   }
   
   pwindow->m_pacmeuserinteractionCapture.release();
   
   m_pwindowMouseCapture.release();
   
   return true;
   
}


void windowing::clear_keyboard_focus(::user::element* pelementGainingFocusIfAny)
{
   
   if (!m_pwindowKeyboardFocus)
   {
      
      return;
      
   }
   
   auto pwindow = m_pwindowKeyboardFocus;
   
   if (pwindow)
   {
      
      pwindow->clear_keyboard_focus();
      
      //pwindow->on_fin
      //         auto puserinteractionKeyboardFocus = pwindow->m_puserinteractionKeyboardFocus;
      //
      //         if (puserinteractionKeyboardFocus)
      //         {
      //
      //            pwindow->m_puserinteractionKeyboardGainingFocusIfAny = pwindowGainingFocusIfAny;
      //
      //            //pwindow->m_puserinteractionKeyboardFocus->post_message(e_message_kill_focus);
      //
      //            pwindow->m_puserinteractionKeyboardFocus.release();
      
      //}
      //auto puserinteraction =
      
      //         if (puserinteraction)
      //         {
      //
      //            puserinteraction->post_message(e_message_kill_focus);
      //
      //         }
      //
      //         //if (pwindow->m_puserinteractionKeyboardFocus)
      //         //{
      //
      //         //   pwindow->m_puserinteractionKeyboardGainingFocusIfAny = pwindowGainingFocusIfAny;
      //
      //         //   pwindow->m_puserinteractionKeyboardFocus->post_message(e_message_kill_focus);
      //
      //         //}
      //
      //         pwindow->m_puserinteractionKeyboardFocus.release();
      
      //}
      
      if(!pelementGainingFocusIfAny || pelementGainingFocusIfAny->acme_windowing_window() !=
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

//
//::pointer<::windowing::cursor>windowing::get_cursor(enum_cursor ecursor)
//{
//   
//   return nullptr;
//   
//}


} // namespace sandbox_windowing


} // namespace acme



