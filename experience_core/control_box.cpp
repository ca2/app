#include "framework.h"


namespace experience
{


   namespace aura
   {


      control_box::control_box()
      {


      }


      control_box::~control_box()
      {

      }


      void control_box::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
      {


      }

      void control_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         if((GetTopLevel()->frame_is_transparent() && !GetTopLevel()->is_active()) || !GetTopLevelFrame()->m_bShowControlBox)
         {

            return;

         }

         auto rectClient = get_client_rect();

         if (rectClient.is_empty())
         {

            return;

         }

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         color32_t crBackground;

         if(GetTopLevel()->frame_is_transparent())
         {

            crBackground = ARGB(90,colorref_get_r_value(m_crBackground),colorref_get_g_value(m_crBackground),colorref_get_b_value(m_crBackground));

         }
         else
         {

            crBackground = m_crBackground;

         }

         //crBackground = ARGB(80, 255, 200, 160);

         pgraphics->fill_rect(rectClient, crBackground);

      }


      void control_box::_001OnShowWindow(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);

      }

      void control_box::_001OnLButtonDown(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);

      }

      void control_box::_001OnLButtonUp(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);

      }



      void control_box::_001OnTimer(::timer * ptimer)
      {

         ::experience::control_box::_001OnTimer(ptimer);

      }


      void control_box::install_message_routing(::channel *pframewindow)
      {

         ::experience::control_box::install_message_routing(pframewindow);

         MESSAGE_LINK(e_message_show_window, pframewindow, this, &control_box::_001OnShowWindow);
         MESSAGE_LINK(e_message_left_button_down, pframewindow, this, &control_box::_001OnLButtonDown);
         MESSAGE_LINK(e_message_left_button_up, pframewindow, this, &control_box::_001OnLButtonUp);
         //MESSAGE_LINK(e_message_size, pframewindow, this, &control_box::_001OnSize);
      //   //MESSAGE_LINK(e_message_timer, pframewindow, this, &control_box::_001OnTimer);

      }


   } // namespace aura


} // namespace experience



