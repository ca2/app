#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple/_simple.h"
#endif


simple_child_frame::simple_child_frame()
{
   
   m_ewindowflag += window_flag_satellite_window;
   m_ewindowflag += window_flag_embedded_prodevian;

   m_bWindowFrame       = false;
   m_bAutoWindowFrame = false;

}

simple_child_frame::~simple_child_frame()
{

}


bool simple_child_frame::pre_create_window(::user::create_struct& cs)
{

   cs.style |= WS_CHILD;

#ifdef WINDOWS_DESKTOP


   cs.style &= ~WS_BORDER;
   cs.style &= ~WS_THICKFRAME;

#endif

   if (!simple_frame_window::pre_create_window(cs))
   {

      return FALSE;

   }

#ifdef WINDOWS_DESKTOP

   if(cs.hwndParent == nullptr)
   {

      auto puiMain1 = Application.m_puiMain1;

      if(puiMain1 != nullptr)
      {

         auto pui = __user_interaction(Application.m_puiMain1);

         cs.hwndParent = pui->get_handle();

      }

   }

#endif

   cs.style &= ~WS_OVERLAPPEDWINDOW;

   return TRUE;

}


void simple_child_frame::route_command_message(::user::command * pcommand)
{

   simple_frame_window::route_command_message(pcommand);

}


void simple_child_frame::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   UNREFERENCED_PARAMETER(pgraphics);


}


//bool simple_child_frame::get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::style_context * pinteraction)
//{
//
//   // etranslucency = ::user::translucency_present for children that may ask the translucency guideline for this as parent,
//   // but simple_child_frame, at the moment of this remark writing, itself draw transparently.
//
//   etranslucency = ::user::translucency_present;
//
//   return true;
//
//}


namespace core
{


   ::type user::get_simple_child_frame_type_info()
   {

      
      return __type(simple_child_frame);

      
   }


} // namespace core



