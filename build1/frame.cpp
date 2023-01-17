#include "framework.h"


namespace app_core_build
{


   frame::frame()
   {

      m_bDefaultCreateToolbar = false;

   }


   frame::~frame()
   {

   }


   void frame::assert_ok() const
   {

      simple_frame_window::assert_ok();

   }


   void frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


   void frame::on_layout(::draw2d::graphics_pointer& pgraphics)
   {

      simple_frame_window::on_layout(pgraphics);

   }


//   bool frame::get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::style_context * pinteraction)
//   {
//
//      etranslucency = ::user::e_translucency_present;
//
//      return true;
//
//   }


} // namespace app_core_build



