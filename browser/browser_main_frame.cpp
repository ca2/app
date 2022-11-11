#include "framework.h"


namespace browser
{


   main_frame::main_frame(::particle * pparticle) :
      object(pparticle),
      simple_frame_window(pparticle),
      simple_main_frame(pparticle)
   {

      //m_ewindowflag += e_window_flag_disable_window_placement_snapping;

      m_bDefaultCreateToolbar = false;

      window_enable_full_screen();

      m_bWindowFrame = !papp->m_bExperienceMainFrame;

      set_translucent();

      if (papp->has_property("opaque"))
      {

         m_bExplicitTranslucency = true;

         m_etranslucency = ::user::e_translucency_none;

      }
      else
      {

         m_bExplicitTranslucency = false;

      }



   }


   main_frame::~main_frame()
   {

   }


   void main_frame::assert_ok() const
   {

      simple_frame_window::assert_ok();

   }


   void main_frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


   ::experience::frame * main_frame::frame_experience()
   {

      auto pframe = papp->experience()->frame_experience(nullptr, "013");

      pframe->set_style("LightBlue");

      return pframe;

   }


   bool main_frame::has_pending_graphical_update()
   {

      return is_window_visible();

   }


   bool main_frame::get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::style_context * pcontext)
   {

      if (m_bExplicitTranslucency)
      {

         etranslucency = m_etranslucency;

         return true;

      }

      return ::user::style::get_translucency(etranslucency, eelement, pcontext);

   }


} // namespace browser



