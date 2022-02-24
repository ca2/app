#include "framework.h"


namespace hellobase
{


   main_frame::main_frame(::object * pobject) :
      object(pobject)
   {

      WfiEnableFullScreen();

      m_bWindowFrame = !papp->m_bExperienceMainFrame;



      if (papp->has_property("opaque"))
      {

         m_bExplicitTranslucency = true;

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

      ::user::frame_window::assert_ok();

   }


   void main_frame::dump(dump_context & dumpcontext) const
   {

      ::user::frame_window::dump(dumpcontext);

   }



   bool main_frame::has_pending_graphical_update()
   {

      return true;

   }


   bool main_frame::get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::interaction * pinteraction)
   {

      if (m_bExplicitTranslucency)
      {

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


} // namespace hellobase







