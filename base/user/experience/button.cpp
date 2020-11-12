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

      MESSAGE_LINK(e_message_lbutton_down, pchannel, this, &button::_001OnLButtonDown);


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
      //return;

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
         
         if(!m_pshapeaClip)
         {

            __construct_new(m_pshapeaClip);
            
            ::user::interaction * pinteraction = this;

            ::rect rectFocus;

            index i = 0;

            while (pinteraction != nullptr)
            {

               pinteraction->get_window_rect(rectFocus);

               rectFocus.offset(rectClient.top_left());

               _001ScreenToClient(rectFocus);

               m_pshapeaClip->add_item(__new(rect_shape(rectFocus)));
               
               m_pshapeaClip->add_item(__new(intersect_clip_shape));

               i++;

               pinteraction = pinteraction->GetParent();

            }
            
         }
         
         pgraphics->reset_clip();
         
         pgraphics->add_shapes(*m_pshapeaClip);

      }
      catch (...)
      {

         __throw(::exception::exception("no more a u"));

      }

   }


   bool button::keyboard_focus_is_focusable()
   {

      return false;

   }


} // namespace experience



