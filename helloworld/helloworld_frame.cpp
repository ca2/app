#include "framework.h"


namespace helloworld
{


   frame::frame(::object * pobject) :
      object(pobject),
      simple_frame_window(pobject)
   {

      m_bDefaultCreateToolbar = false;

   }


   frame::~frame()
   {

   }


   void frame::assert_valid() const
   {

      simple_frame_window::assert_valid();

   }


   void frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


   bool frame::get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::style_context * pinteraction)
   {

      etranslucency = ::user::translucency_present;

      return true;

   }


} // namespace helloworld







