#include "framework.h"


namespace helloworld
{


   main_frame::main_frame(::object * pobject) :
      object(pobject),
      simple_frame_window(pobject)
   {

      m_bDefaultCreateToolbar = false;

      window_enable_full_screen();

      m_bWindowFrame = !papplication->m_bExperienceMainFrame;



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


   ::experience::frame * main_frame::experience_get_frame()
   {



      //__pointer(::user::experience::main_frame::main_frame) pschema = papplication->experience()->experience_get_frame("experience_lite", "001");

      auto pframe = papplication->experience()->experience_get_frame(nullptr, "013");

      pframe->set_style("LightBlue");

      //       // pschema->m_typeControlBoxButton = __type(MetaButton);

      return pframe;

   }

   bool main_frame::has_pending_graphical_update()
   {

      return true;

   }


   bool main_frame::get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::interaction * pinteraction)
   {

      if (m_bExplicitTranslucency)
      {

         etranslucency = m_etranslucency;

         return true;

      }

      //if (userstyle() != nullptr)
      //{

      //   if (m_puserstyle->_001GetMainFrameTranslucency(etranslucency))
      //      return true;

      //}
      //etranslucency = ::user::e_translucency_present;

      ////      etranslucency = ::user::e_translucency_none;

      //return true;

      return ::user::style::get_translucency(etranslucency, eelement, pinteraction);

   }


} // namespace helloworld







