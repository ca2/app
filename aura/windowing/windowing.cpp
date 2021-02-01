// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "_windowing.h"

#if !BROAD_PRECOMPILED_HEADER

#include "aura/user/_user.h"

#endif


namespace windowing
{


   windowing::windowing()
   {


   }


   windowing::~windowing()
   {

   }


   hcursor windowing::load_default_cursor(e_cursor ecursor)
   {


      return 0;


   }


   int_bool windowing::window_set_mouse_cursor(window *pwindow, hcursor hcursor)
   {

      return FALSE;


   }


   bool windowing::sn_start_context()
   {


      return false;

   }


   bool windowing::set_window_icon(window *pwindow, const ::file::path &path)
   {


      return false;

   }


   int windowing::message_box(const char *pszMessage, const char *pszTitle, const ::e_message_box &emessagebox)
   {

      return -1;

   }


   int windowing::message_box_timeout(const char *pszMessage, const char *pszTitle, const ::duration &duration,
                                      const ::e_message_box &emessagebox)
   {

      return -1;

   }


   window *windowing::new_message_window(::user::interaction_impl *pimpl)
   {

      __throw(interface_only_exception);

      return nullptr;

   }


   window *windowing::new_window(::user::interaction_impl *pimpl)
   {

      __throw(interface_only_exception);

      return nullptr;

   }


   ::e_status windowing::remove_window(::user::interaction_impl *pimpl)
   {

      __throw(interface_only_exception);

      return error_interface_only;

   }


//   ::e_status windowing::hook(class hook *phook)
//   {
//
//      __throw(interface_only_exception);
//
//      return
//         error_interface_only;
//
//   }
//
//
//   ::e_status windowing::unhook(class hook * phook)
//   {
//
//      __throw(interface_only_exception);
//
//      return
//         error_interface_only;
//
//   }



   bool windowing::route_message(::message::base * pmessagebase)
   {

      pmessagebase->m_oswindow->m_pimpl->message_handler(pmessagebase);

      return true;

   }


   void windowing::on_idle(display *pdisplay)
   {


   }


} // namespace windowing




