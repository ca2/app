#include "framework.h"


namespace helloworld
{


   main_frame::main_frame(::layered * pobjectContext) :
      object(pobject),
      simple_frame_window(pobject)
   {

      m_bDefaultCreateToolbar = false;

      window_enable_full_screen();

      m_bWindowFrame = !Application.has_property("client_only");



      if (Application.has_property("opaque"))
      {

         m_bExplicitTranslucency = true;

         m_etranslucency = ::user::translucency_none;

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



      //__pointer(::user::experience::main_frame::main_frame) pschema = Application.experience()->experience_get_frame("experience_core", "001");

      auto pframe = Application.experience()->experience_get_frame(nullptr, "013");

      pframe->set_style("LightBlue");

      //       // pschema->m_typeControlBoxButton = __type(MetaButton);

      return pframe;

   }

   bool main_frame::has_pending_graphical_update()
   {

      return true;

   }


   bool main_frame::get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::interaction * pinteraction)
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
      //etranslucency = ::user::translucency_present;

      ////      etranslucency = ::user::translucency_none;

      //return true;

      return ::user::style::get_translucency(etranslucency, eelement, pinteraction);

   }


} // namespace helloworld







