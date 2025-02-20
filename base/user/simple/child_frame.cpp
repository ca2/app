#include "framework.h"
#include "base/user/simple/child_frame.h"
#include "base/user/user/user.h"


simple_child_frame::simple_child_frame()
{
   
   m_ewindowflag += e_window_flag_satellite_window_if_child;
   m_ewindowflag += e_window_flag_embedded_graphics_thread_if_child;

   //m_bWindowFrame       = false;
   //m_bAutoWindowFrame = false;

}

simple_child_frame::~simple_child_frame()
{

}


bool simple_child_frame::pre_create_window(::user::system * pusersystem)
{

//   pusersystem->m_createstruct.style |= WS_CHILD;
//
//#ifdef WINDOWS_DESKTOP
//
//
//   pusersystem->m_createstruct.style &= ~WS_BORDER;
//   pusersystem->m_createstruct.style &= ~WS_THICKFRAME;
//
//#endif

   if (!simple_frame_window::pre_create_window(pusersystem))
   {

      return false;

   }
//
//#ifdef WINDOWS_DESKTOP
//
//   if(pusersystem->m_createstruct.hwndParent == nullptr)
//   {
//
//      auto puserinteractionMain = papp->m_pacmeuserinteractionMain;
//
//      if(puserinteractionMain != nullptr)
//      {
//
//         auto pui = __user_interaction(papp->m_pacmeuserinteractionMain);
//
//         pusersystem->m_createstruct.hwndParent = as_hwnd(pui->get_oswindow());
//
//      }
//
//   }
//
//#endif

   ///pusersystem->m_createstruct.style &= ~WS_OVERLAPPEDWINDOW;

   return true;

}


void simple_child_frame::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
{

   simple_frame_window::route_command(pcommand, bRouteToKeyDescendant);

}


void simple_child_frame::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   __UNREFERENCED_PARAMETER(pgraphics);


}


//bool simple_child_frame::get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::style_context * pinteraction)
//{
//
//   // etranslucency = ::user::e_translucency_present for children that may ask the translucency guideline for this as parent,
//   // but simple_child_frame, at the moment of this remark writing, itself draw transparently.
//
//   etranslucency = ::user::e_translucency_present;
//
//   return true;
//
//}


namespace base
{


   ::type_atom user::get_simple_child_frame_type_info()
   {

      
      return ::type < simple_child_frame >();

      
   }


} // namespace core



