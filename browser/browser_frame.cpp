#include "framework.h"


namespace browser
{


   frame::frame(::particle * pparticle) :
      object(pparticle),
      simple_frame_window(pparticle)
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


   bool frame::get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::style_context * pinteraction)
   {

      etranslucency = ::user::e_translucency_present;

      return true;

   }


} // namespace browser



