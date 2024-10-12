#include "framework.h"
#include "main_window.h"
#include "acme/constant/message.h"
#include "acme/handler/item.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/user/user/tool.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/user/control_box_button.h"
#include "aura/message/user.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "aura/platform/application.h"


#define STEPPY_DEBUG 0


namespace app_app
{


   main_window::main_window()
   {

      m_bTransparent = true;

      m_rectangleInitialRateOrSize = { 0.05, 0.05, 0.4, 0.4 };

      m_dBreathPeriod = 60.0;

      m_timeStart.Now();

      m_dPhaseShift = 0.0;

      m_bNeedFullRedrawOnResize = true;

   }


   main_window::~main_window()
   {


   }


   void main_window::install_message_routing(::channel * pchannel)
   {

      ::user::main_window::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &main_window::on_message_create);

   }


   void main_window::on_message_create(::message::message * pmessage)
   {

#if !STEPPY_DEBUG

      if (is_sandboxed())
      {

         add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen);

      }
      else
      {

         //set_fps_interest();

         add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen_fps);

      }

#endif

   }


   void main_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      m_iCloseButtonDraw = 0;

      m_dDrawOnlyMainRectangles = false;

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;

      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      if (system()->background_color().get_luminance() < 0.5)
      {

         pgraphics->fill_rectangle(rectangleX, argb(255, 127, 127, 127));

      }
      else
      {

         pgraphics->fill_rectangle(rectangleX, argb(255, 255, 255, 255));

      }

      auto dMinimumDimension = (double)rectangleX.minimum_signed_absolute_dimension();

      double dBase = dMinimumDimension / 17.0;

      double x = dBase * 3;

      double y = dBase * 3;

      pgraphics->fill_rectangle(::rectangle_f64_dimension(x, y, dBase * 5.0, dBase * 5.0), ::argb(127, 40, 150, 235));

      pgraphics->fill_rectangle(::rectangle_f64_dimension(x + dBase * 6.0, y, dBase * 5.0, dBase * 5.0), ::argb(127, 40, 150, 235));

      pgraphics->fill_rectangle(::rectangle_f64_dimension(x, y + dBase * 6.0, dBase * 11.0, dBase * 5.0), ::argb(127, 255, 110, 150));

      if (m_dDrawOnlyMainRectangles)
      {

         return;

      }

      rectangleX.deflate((::i32)dBase);

      ::color::color colorInset;

      if (system()->background_color().get_luminance() < 0.5)
      {

         colorInset = argb(255, 89, 89, 89);

      }
      else
      {

         colorInset = argb(255, 127, 127, 127);

      }

      pgraphics->draw_inset_rectangle(rectangleX, colorInset, dBase);

      //m_dDrawControlBox = true;

      if (should_show_platform_control_box())
      {

         pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

         auto pitemClose = user_item(tool().item(::e_element_close_button));

         auto pitemZoom = user_item(tool().item(::e_element_maximize_button));

         auto pitemIcon = user_item(tool().item(::e_element_minimize_button));

         if (::is_set(pitemClose))
         {

            bool bHover = ::is_element(m_pitemHover, ::e_element_close_button);

            double dSourcePeriod;

            if (bHover)
            {

               dSourcePeriod = 0.5;

            }
            else
            {

               dSourcePeriod = 5.0;

            }

            double time = m_timeStart.elapsed().floating_second();

            double dFrequency = 1.0 / m_dBreathPeriod;

            auto pmathematics = mathematics();

            double omega = 2.0 * π * dFrequency;

            double angle = omega * time;

            angle += m_dPhaseShift;

            double dNewPeriod = m_dBreathPeriod;

            if (dSourcePeriod < dNewPeriod)
            {

               dNewPeriod -= dNewPeriod * 0.01;

            }
            else if (dSourcePeriod > dNewPeriod)
            {

               dNewPeriod += dNewPeriod * 0.01;

            }

            if (dNewPeriod != m_dBreathPeriod)
            {

               m_dBreathPeriod = dNewPeriod;

               dFrequency = 1.0 / m_dBreathPeriod;

               auto pmathematics = mathematics();

               omega = 2.0 * π * dFrequency;

               double angleNew = omega * time;

               m_dPhaseShift = angle - angleNew;

               m_dPhaseShift = fmod(m_dPhaseShift, 2.0 * π);

            }

            int iSize = (int)(::sin(angle) * 25.0 + 64.0);

            pitemClose->m_rectangle2 = this->rectangle();

            pitemClose->m_rectangle2.left() = pitemClose->m_rectangle2.right() - iSize;

            pitemClose->m_rectangle2.bottom() = pitemClose->m_rectangle2.top() + iSize;

//            auto pmouse = __create_new < ::message::mouse >();
//
//            pmouse->m_pointHost = host_mouse_cursor_position();
//
//            pmouse->m_pointAbsolute = absolute_mouse_cursor_position();
//
            update_hover_according_to_last_hover_update(::user::e_zorder_any);

            if (::is_set(pitemZoom))
            {

               pitemZoom->m_rectangle2 = this->rectangle();

               pitemZoom->m_rectangle2.right() = pitemClose->m_rectangle2.left();

               pitemZoom->m_rectangle2.bottom() = pitemClose->m_rectangle2.bottom();

               pitemZoom->m_rectangle2.left() = pitemZoom->m_rectangle2.right() - iSize;

               if (::is_set(pitemIcon))
               {

                  pitemIcon->m_rectangle2 = this->rectangle();

                  pitemIcon->m_rectangle2.right() = pitemZoom->m_rectangle2.left();

                  pitemIcon->m_rectangle2.bottom() = pitemClose->m_rectangle2.bottom();

                  pitemIcon->m_rectangle2.left() = pitemIcon->m_rectangle2.right() - iSize;

               }

            }

         }

      }

      ::user::interaction::_001OnDraw(pgraphics);

   }


   void main_window::_001DrawItem(::draw2d::graphics_pointer & pgraphics, ::user::item & useritem, const ::user::e_state & estate)
   {

      auto pitem = useritem.m_pitem;

      if (::is_null(useritem.m_pitem))
      {

         return;

      }

      if (pitem->m_item.m_eelement == ::e_element_close_button)
      {

         ::user::draw_close_button(pgraphics, this, useritem, estate);

         m_iCloseButtonDraw++;

         if (m_iCloseButtonDraw > 1)
         {

            //informationf("output");

         }

         return;

      }

      ::user::interaction::_001DrawItem(pgraphics, useritem, estate);

   }


} // namespace app_app



