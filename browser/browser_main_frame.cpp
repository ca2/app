#include "framework.h"


namespace browser
{


   main_frame::main_frame(::object * pobject) :
      object(pobject),
      simple_frame_window(pobject),
      simple_main_frame(pobject)
   {

      //m_ewindowflag += e_window_flag_disable_window_placement_snapping;

      m_bDefaultCreateToolbar = false;

      window_enable_full_screen();

      m_bWindowFrame = !papplication->m_bExperienceMainFrame;

      set_translucent();

      if (papplication->has_property("opaque"))
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


   void main_frame::assert_valid() const
   {

      simple_frame_window::assert_valid();

   }


   void main_frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


   ::experience::frame * main_frame::frame_experience()
   {

      auto pframe = papplication->experience()->frame_experience(nullptr, "013");

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



