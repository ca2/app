#include "framework.h"
#include "aura/graphics/user/control_box_button.h"
//#include "aura/graphics/draw2d/_component.h"
#include "acme/prototype/mathematics/mathematics.h"


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

         set_fps_interest();

      }

#endif

      auto papp = get_app();

      papp->m_bInterprocessCommunication = false;

   }


   void main_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      
      m_iCloseButtonDraw = 0;

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;

      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

      pgraphics->fill_rectangle(rectangleX, argb(255, 255, 255, 255));
      
      auto dMinimumDimension = (double) rectangleX.minimum_signed_absolute_dimension();

      double dBase = dMinimumDimension / 17.0;

      double x = dBase * 3;

      double y = dBase * 3;

      pgraphics->fill_rectangle(::double_rectangle_dimension(x, y, dBase * 5.0, dBase * 5.0), ::rgba(127, 40, 150, 235));

      pgraphics->fill_rectangle(::double_rectangle_dimension(x + dBase * 6.0, y, dBase * 5.0, dBase * 5.0), ::rgba(127, 40, 150, 235));

      pgraphics->fill_rectangle(::double_rectangle_dimension(x, y + dBase * 6.0, dBase * 11.0, dBase * 5.0), ::rgba(127, 255, 110, 150));
      
      rectangleX.deflate((int) dBase);

      ::color::color colorInset;

      if (node()->background_color().get_luminance() < 0.5)
      {

         colorInset = ::rgba(255, 89, 89, 89);

      }
      else
      {

         colorInset = ::rgba(255, 127, 127, 127);

      }

      for (int i = 0; i < dBase; i++)
      {

         pgraphics->draw_inset_rectangle(rectangleX, colorInset);

         rectangleX.deflate(1, 1);

      }

      pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_high);

      auto pitemClose = get_user_item(::e_element_close_button);
      auto pitemZoom = get_user_item(::e_element_maximize_button);
      auto pitemIcon = get_user_item(::e_element_minimize_button);

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

         double time = m_timeStart.elapsed().floating_second().m_d;

         double dFrequency = 1.0 / m_dBreathPeriod;

         auto pmathematics = ::mathematics::mathematics();

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

            auto pmathematics = ::mathematics::mathematics();

            omega = 2.0 * π * dFrequency;

            double angleNew = omega * time;

            m_dPhaseShift = angle - angleNew;

            //auto pmathematics = ::mathematics::mathematics();

            m_dPhaseShift = fmod(m_dPhaseShift, 2.0 * π);

         }

         int iSize = (int) (::sin(angle) * 20.0 + 64.0);

         this->rectangle(pitemClose->m_rectangle);

         pitemClose->m_rectangle.left() = pitemClose->m_rectangle.right() - iSize;

         pitemClose->m_rectangle.bottom() = pitemClose->m_rectangle.top() + iSize;

         auto pwindow = window();

         auto pointCursor = pwindow->get_mouse_cursor_position();

         auto pmouse = __create_new < ::user::mouse >();

         pmouse->m_point = pointCursor;

         update_hover(pmouse);

         if (::is_set(pitemZoom))
         {

            this->rectangle(pitemZoom->m_rectangle);

            pitemZoom->m_rectangle.right() = pitemClose->m_rectangle.left();

            pitemZoom->m_rectangle.bottom() = pitemClose->m_rectangle.bottom();

            pitemZoom->m_rectangle.left() = pitemZoom->m_rectangle.right() - iSize;


            if (::is_set(pitemIcon))
            {

               this->rectangle(pitemIcon->m_rectangle);

               pitemIcon->m_rectangle.right() = pitemZoom->m_rectangle.left();

               pitemIcon->m_rectangle.bottom() = pitemClose->m_rectangle.bottom();

               pitemIcon->m_rectangle.left() = pitemIcon->m_rectangle.right() - iSize;


            }

         }



      }


      ::user::interaction::_001OnDraw(pgraphics);

   }


   void main_window::_001DrawItem(::draw2d::graphics_pointer& pgraphics, ::item* pitem, const ::user::e_state & estate)
   {

      if (::is_null(pitem))
      {

         return;

      }

      if (pitem->m_item.m_eelement == ::e_element_close_button)
      {

         ::user::draw_close_button(pgraphics, this, pitem, estate);

         m_iCloseButtonDraw++;

         if (m_iCloseButtonDraw > 1)
         {

            //informationf("output");

         }

         return;

      }
      
      ::user::interaction::_001DrawItem(pgraphics, pitem, estate);

   }


} // namespace app_app



