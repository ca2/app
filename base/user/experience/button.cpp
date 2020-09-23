#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/experience/_experience.h"
#endif


namespace experience
{


   button::button()
   {

   }


   button::~button()
   {

   }


   void button::install_message_routing(::channel* pchannel)
   {

      ::user::button::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &button::_001OnLButtonDown);


   }


   void button::_001OnLButtonDown(::message::message* pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      if (m_ebutton == button_dock)
      {

         auto item = hit_test(pmouse);

         if (item.is_set())
         {

            m_pcontrolbox->m_pframewindow->experience_on_start_dock(pmouse);

         }

      }

   }


   void button::UpdateWndRgn()
   {

   }


   void button::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {
      
#ifdef MACOS

      // clip
      return;

#endif

      try
      {

         if (string(type_name()).contains_ci("control_box"))
         {

            output_debug_string("control_box");

         }

         ::rect rectClip;

         ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

         ::rect rectClient;

         bool bFirst = true;

         if (pdrawcontext != nullptr)
         {

            rectClient = pdrawcontext->m_rectWindow;

            _001ScreenToClient(rectClient);

            rectClient.bottom++;
            rectClient.right++;

            rectClip = rectClient;

            bFirst = false;

         }

         ::user::interaction * pframewindow = this;

         ::rect rectFocus;

         ::rect rectIntersect;

         index i = 0;

         while (pframewindow != nullptr)
         {

            pframewindow->get_window_rect(rectClient);

            if (::is_set(m_pcontrolbox) && pframewindow == m_pcontrolbox->m_pframewindow)
            {

               m_pcontrolbox->m_pframewindow->m_pframe->GetFrameRect(&rectFocus);

            }
            else
            {

               pframewindow->get_client_rect(rectFocus);

            }


            rectFocus.offset(rectClient.top_left());

            _001ScreenToClient(rectFocus);

            //rectFocus.bottom;
            //rectFocus.right;

            if (i == 0)
            {

               rectIntersect = rectFocus;

            }
            else
            {

               rectIntersect.intersect(rectFocus);

            }

            i++;

            pframewindow = pframewindow->GetParent();

         }

         pgraphics->IntersectClipRect(rectIntersect);

      }
      catch (...)
      {

         __throw(::exception::exception("no more a ui"));

      }

   }


   bool button::keyboard_focus_is_focusable()
   {

      return false;

   }


} // namespace experience



