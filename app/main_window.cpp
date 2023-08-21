#include "framework.h"
#include "main_window.h"
#include "acme/handler/item.h"
#include "acme/platform/node.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/user/control_box_button.h"
#include "aura/message/user.h"
#include "acme/primitive/mathematics/mathematics.h"
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

   }


   main_window::~main_window()
   {


   }


   void main_window::on_create_user_interaction()
   {

      ::user::main_window::on_create_user_interaction();

#if !STEPPY_DEBUG

      if (!is_sandboxed())
      {

         set_auto_refresh();

      }

#endif

   }


   void main_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      m_iCloseButtonDraw = 0;

      m_dDrawOnlyMainRectangles = false;

      auto rectangleClient = client_rectangle();

      if (rectangleClient.is_empty())
      {

         return;

      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      if (acmenode()->background_color().get_luminance() < 0.5)
      {

         pgraphics->fill_rectangle(rectangleClient, argb(255, 127, 127, 127));

      }
      else
      {

         pgraphics->fill_rectangle(rectangleClient, argb(255, 255, 255, 255));

      }

      auto dMinimumDimension = (double)rectangleClient.minimum_signed_absolute_dimension();

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

      rectangleClient.deflate((::i32)dBase);

      ::color::color colorInset;

      if (acmenode()->background_color().get_luminance() < 0.5)
      {

         colorInset = argb(255, 89, 89, 89);

      }
      else
      {

         colorInset = argb(255, 127, 127, 127);

      }

      pgraphics->draw_inset_rectangle(rectangleClient, colorInset, dBase);

      m_dDrawControlBox = true;

      if (m_dDrawControlBox)
      {

         pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

         auto pitemClose = user_item(::e_element_close_button);

         auto pitemZoom = user_item(::e_element_maximize_button);

         auto pitemIcon = user_item(::e_element_minimize_button);

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

            auto pmathematics = ::mathematics::mathematics();

            double omega = 2.0 * pmathematics->get_pi() * dFrequency;

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

               auto pmathematics = ::mathematics::mathematics();

               omega = 2.0 * pmathematics->get_pi() * dFrequency;

               double angleNew = omega * time;

               m_dPhaseShift = angle - angleNew;

               m_dPhaseShift = fmod(m_dPhaseShift, 2.0 * pmathematics->get_pi());

            }

            int iSize = (int)(::sin(angle) * 25.0 + 64.0);

            pitemClose->m_rectangle = client_rectangle();

            pitemClose->m_rectangle.left = pitemClose->m_rectangle.right - iSize;

            pitemClose->m_rectangle.bottom = pitemClose->m_rectangle.top + iSize;

            auto pointCursor = get_cursor_position();

            auto pmouse = __create_new < ::message::mouse >();

            pmouse->m_point = pointCursor;

            update_hover(pmouse, ::user::e_zorder_any);

            if (::is_set(pitemZoom))
            {

               pitemZoom->m_rectangle = client_rectangle();

               pitemZoom->m_rectangle.right = pitemClose->m_rectangle.left;

               pitemZoom->m_rectangle.bottom = pitemClose->m_rectangle.bottom;

               pitemZoom->m_rectangle.left = pitemZoom->m_rectangle.right - iSize;

               if (::is_set(pitemIcon))
               {

                  pitemIcon->m_rectangle = client_rectangle();

                  pitemIcon->m_rectangle.right = pitemZoom->m_rectangle.left;

                  pitemIcon->m_rectangle.bottom = pitemClose->m_rectangle.bottom;

                  pitemIcon->m_rectangle.left = pitemIcon->m_rectangle.right - iSize;

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

            //::information("output");

         }

         return;

      }

      ::user::interaction::_001DrawItem(pgraphics, useritem, estate);

   }


} // namespace app_app



