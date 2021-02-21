#include "framework.h"
#include "base/user/experience/_experience.h"


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

      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &button::on_message_left_button_down);


   }


   void button::on_message_left_button_down(::message::message* pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      if (m_ebutton == e_button_dock)
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

      //return;

      try
      {

         if (string(type_name()).contains_ci("control_box"))
         {

            output_debug_string("control_box");

         }

         ::rectangle_i32 rectClip;

         ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

         ::rectangle_i32 rectClient;

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

            ::rectangle_i32 rectFocus;

            index i = 0;

            while (pinteraction != nullptr)
            {

               pinteraction->get_client_rect(rectFocus);

               pinteraction->_001ClientToHost(rectFocus);

               _001HostToClient(rectFocus);

               m_pshapeaClip->add_item(__new(rectd_shape(rectFocus)));
               
               m_pshapeaClip->add_item(__new(intersect_clip_shape));

               i++;

               pinteraction = pinteraction->get_parent();

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


   bool button::keyboard_focus_is_focusable() const
   {

      return false;

   }


} // namespace experience



