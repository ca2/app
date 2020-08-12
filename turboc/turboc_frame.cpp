#include "framework.h"
#include <math.h>


namespace turboc
{


   frame::frame(::object * pobject) :
      ::object(pobject),
      simple_frame_window(pobject)
   {

      m_dataid = "::aura::turboc::frame";

      window_enable_full_screen();

      m_bWindowFrame = !Application.has_property("client_only");

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


   ::experience::frame * frame::experience_get_frame()
   {

      //auto pframe = Application.experience()->experience_get_frame("experience_core", "001");

      auto pframe = Application.experience()->experience_get_frame("experience_core","013");

      pframe->set_style("LightBlue");

      pschema->m_typeControlBoxButton = __type(MetaButton);

      return pframe;

   }


   bool frame::get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::style_context * pinteraction)
   {

      etranslucency = ::user::translucency_present;

      return true;

   }


} // namespace turboc







