#include "framework.h"
#include "button.h"
#include "control_box.h"
#include "frame_window.h"
#include "dock_manager.h"
#include "acme/constant/message.h"
#include "acme/handler/item.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/message/user.h"
#include "aura/graphics/draw2d/region.h"
#include "aura/graphics/write_text/font.h"


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

      MESSAGE_LINK(e_message_show_window, pchannel, this, &button::on_message_show_window);

      if(m_ebutton == e_button_dock)
      {

         auto pdockmanager = m_pcontrolbox->m_pframewindow->m_pdockmanager.get();

         MESSAGE_LINK(e_message_left_button_down   , pchannel, pdockmanager, &::experience::dock_manager::dock_button_on_message_left_button_down  );
         MESSAGE_LINK(e_message_mouse_move         , pchannel, pdockmanager, &::experience::dock_manager::dock_button_on_message_mouse_move        );
         MESSAGE_LINK(e_message_left_button_up     , pchannel, pdockmanager, &::experience::dock_manager::dock_button_on_message_left_button_up    );

      }

   }


   void button::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshow(pmessage);

      //m_bDrag = false;

      //m_bShowAttempt = false;

      if (pshow->m_bShow)
      {

         //m_timeShow.Now();

      }
      else
      {

         output_debug_string("experience::button");

      }

   }


   void button::UpdateWndRgn()
   {

   }


   void button::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {
      
      return ::user::button::_001OnClip(pgraphics);
//
//
//#ifdef MACOS
//
//      // clip
//      //return;
//
//#endif
//
//      //return;
//
//      try
//      {
//
//         if (__type_name(this).case_insensitive_contains("control_box"))
//         {
//
//            output_debug_string("control_box");
//
//         }
//
//         ::rectangle_i32 rectangleClip;
//
//         ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();
//
//         ::rectangle_i32 rectangleClient;
//
//         bool bFirst = true;
//
//         if (pdrawcontext != nullptr)
//         {
//
//            client_rectangle(rectangleClient);
//
//            rectangleClient.bottom++;
//            rectangleClient.right++;
//
//            rectangleClip = rectangleClient;
//
//            bFirst = false;
//
//         }
//
//         //auto pinteractiondraw2d = get_draw2d();
//
//         if(!m_pshapeaClip)
//         {
//
//            __construct_new(m_pshapeaClip);
//
//            ::user::interaction * pinteraction = this;
//
//            ::rectangle_i32 rectangleFocus;
//
//            index i = 0;
//
//            while (pinteraction != nullptr)
//            {
//
//               pinteraction->client_rectangle(rectangleFocus);
//
//               pinteraction->client_to_host(rectangleFocus);
//
//               host_to_client(rectangleFocus);
//
//               m_pshapeaClip->add_item(__new(rectangle_shape(rectangleFocus)));
//
//               m_pshapeaClip->add_item(__new(intersect_clip_shape));
//
//               i++;
//
//               pinteraction = pinteraction->get_parent();
//
//            }
//
//         }
//
//         pgraphics->reset_clip();
//
//         pgraphics->add_shapes(*m_pshapeaClip);
//
//      }
//      catch (...)
//      {
//
//         throw ::exception(error_failed, "no more a u");
//
//      }

   }


   ::item_pointer button::on_hit_test(const ::point_i32 &point, ::user::e_zorder ezorder)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_pregion.is_null() || !m_pregion->contains(point))
      {

         if(m_bMouseHoverOnCapture)
         {

            if(has_mouse_capture())
            {

               return __new(::item(::e_element_non_client));

            }

         }
         else if(m_ebutton == e_button_dock)
         {

            if(m_pcontrolbox->m_pframewindow->dock_manager()->window_is_docking())
            {

               return __new(::item(::e_element_non_client));

            }

         }

      }

      return ::user::button::on_hit_test(point, ezorder);

   }


   bool button::keyboard_focus_is_focusable()
   {

      return false;

   }


} // namespace experience



