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

      m_bWindowFrame = !papplication->m_bExperienceMainFrame;

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


   ::experience::frame * frame::frame_experience()
   {

      //auto pframe = papplication->experience()->frame_experience("experience_lite", "001");

      auto pframe = papplication->experience()->frame_experience("experience_lite","013");

      pframe->set_style("LightBlue");

      pschema->m_typeControlBoxButton = __type(MetaButton);

      return pframe;

   }


   bool frame::get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::style_context * pinteraction)
   {

      etranslucency = ::user::e_translucency_present;

      return true;

   }


} // namespace turboc







