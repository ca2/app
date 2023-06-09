#include "framework.h"
#include "dialog_frame.h"
#include "acme/constant/message.h"
#include "aura/message/user.h"
#include "base/platform/application.h"


namespace userex
{


   dialog_frame::dialog_frame()
   {

      //m_bDefaultCreateToolbar = false;

      m_bTransparentFrameEnable = false;

      window_enable_full_screen();

   }


   dialog_frame::~dialog_frame()
   {

   }


   //void dialog_frame::assert_ok() const
   //{

   //   simple_frame_window::assert_ok();

   //}


   //void dialog_frame::dump(dump_context & dumpcontext) const
   //{

   //   simple_frame_window::dump(dumpcontext);

   //}


   bool dialog_frame::pre_create_window(::user::system * pusersystem)
   {

      if (!simple_frame_window::pre_create_window(pusersystem))
      {

         return false;

      }

      //pusersystem->m_createstruct.style &= ~WS_CHILD;
      //pusersystem->m_createstruct.dwExStyle |= WS_EX_TOOLWINDOW;
      //pusersystem->m_createstruct.dwExStyle |= WS_EX_TOPMOST;

      return true;

   }

   void dialog_frame::install_message_routing(::channel * pchannel)
   {

      ::simple_frame_window::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &dialog_frame::on_message_create);
      //MESSAGE_LINK(e_message_activate, pchannel, this, &list_box::_001OnActivate);
      MESSAGE_LINK(e_message_mouse_activate, pchannel, this, &dialog_frame::_001OnMouseActivate);

   }


   void dialog_frame::_001OnActivate(::message::message * pmessage)
   {

      ::pointer<::message::activate>pactivate(pmessage);

      ::pointer<::user::interaction>pActive = (pactivate->inactive() ? pactivate->m_pWndOther : this);

      if (pactivate->inactive())
      {

         //auto pointCursor = psession->get_cursor_position();

         //m_pcombo->screen_to_client(&pointCursor);

         //if(m_pcombo->hit_test(pointCursor) != e_element_drop_down)
         //{

         //   m_pcombo->_001ShowDropDown(false);

         //}




         //if(pActive != m_puiDeactivateTogether)
         //{

         //   ::experience::WorkSet * pset = m_puiDeactivateTogetherSet;

         //   if(pset != nullptr)
         //   {

         //      pset->SetActiveFlag(false);

         //   }

         //}



      }
      else
      {

         //psession->set_keyboard_focus(this);


      }



      //m_pcombo->_001ShowDropDown(false);

      //}

   }

   void dialog_frame::_001OnMouseActivate(::message::message * pmessage)
   {

      ::pointer<::message::mouse_activate>pactivate(pmessage);

      pactivate->m_lresult = e_mouse_activate_no_activate;

      pactivate->m_bRet = true;


   }


   void dialog_frame::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      auto papp = get_app();

      m_bWindowFrame = !papp->m_bExperienceMainFrame;

      if (papp->has_property("opaque"))
      {

         m_bExplicitTranslucency = true;

         m_etranslucencyFrame = ::user::e_translucency_none;

      }
      else
      {

         m_bExplicitTranslucency = false;

      }

      //ModifyStyleEx(0, WS_EX_TOOLWINDOW, SWP_FRAMECHANGED);

      set_tool_window();

   }


   ::experience::frame * dialog_frame::frame_experience()
   {

      auto pframe = ::simple_frame_window::frame_experience(nullptr, "013", "LightBlue");

      return pframe;

   }


   bool dialog_frame::has_pending_graphical_update()
   {

      return m_bNeedRedraw;

   }


   //bool dialog_frame::get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::interaction * pinteraction)
   //{

   //   if (m_bExplicitTranslucency)
   //   {

   //      etranslucency = m_etranslucency;

   //      return true;

   //   }

   //   //if (userstyle() != nullptr)
   //   //{

   //   //   if (m_puserstyle->_001GetMainFrameTranslucency(etranslucency))
   //   //      return true;

   //   //}
   //   //etranslucency = ::user::e_translucency_present;

   //   ////      etranslucency = ::user::e_translucency_none;

   //   //return true;

   //   return ::user::style::get_translucency(etranslucency, eelement, pinteraction);

   //}


} // namespace userex







