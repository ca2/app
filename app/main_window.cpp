#include "framework.h"
#include "aura/graphics/user/close_button.h"

#define STEPPY_DEBUG 0


namespace app_app
{


   main_window::main_window()
   {

      m_bTransparent = true;

      m_rectangleInitialRateOrSize = { 0.05, 0.05, 0.4, 0.4 };

      m_dBreathPeriod = 60.0;

      m_durationStart.Now();

      m_dPhaseShift = 0.0;

   }


   main_window::~main_window()
   {


   }


   void main_window::on_create_user_interaction()
   {

      ::user::main_window::on_create_user_interaction();

#if !STEPPY_DEBUG

      set_prodevian();

#endif

      auto papplication = get_application();

      papplication->m_bInterprocessIntercommunication = false;

   }


   void main_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      
      m_iCloseButtonDraw = 0;

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if (rectangleClient.is_empty())
      {

         return;

      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);

      pgraphics->fill_rectangle(rectangleClient, argb(127, 255, 255, 255));

      double dBase = (double) rectangleClient.minimum_signed_absolute_dimension() / 17.0;

      double x = dBase * 3;

      double y = dBase * 3;

      pgraphics->fill_rectangle(::rectangle_f64_dimension(x, y, dBase * 5.0, dBase * 5.0), __acolor(127, 40, 150, 235));

      pgraphics->fill_rectangle(::rectangle_f64_dimension(x + dBase * 6.0, y, dBase * 5.0, dBase * 5.0), __acolor(127, 40, 150, 235));

      pgraphics->fill_rectangle(::rectangle_f64_dimension(x, y + dBase * 6.0, dBase * 11.0, dBase * 5.0), __acolor(127, 255, 110, 150));

      rectangleClient.deflate((::i32) dBase);

      for (int i = 0; i < dBase; i++)
      {

         pgraphics->draw_inset_rectangle(rectangleClient, __acolor(255, 127, 127, 127));

         rectangleClient.deflate(1, 1);

      }

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

      auto pitem = get_user_item(::e_element_close_button);

      if (::is_set(pitem))
      {

         bool bHover = m_itemHover == ::e_element_close_button;

         double dSourcePeriod;
         
         if (bHover)
         {

            dSourcePeriod = 0.5;

         }
         else
         {

            dSourcePeriod = 5.0;

         }

         double time = m_durationStart.elapsed().floating_second().m_d;

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

            //auto pmathematics = ::mathematics::mathematics();

            m_dPhaseShift = fmod(m_dPhaseShift, 2.0 * pmathematics->get_pi());

         }

         int iSize = (int) (::sin(angle) * 20.0 + 64.0);

         get_client_rect(pitem->m_rectangle);

         pitem->m_rectangle.left = pitem->m_rectangle.right - iSize;

         pitem->m_rectangle.bottom = pitem->m_rectangle.top + iSize;

         auto pwindow = window();

         auto pointCursor = pwindow->get_mouse_cursor_position();

         update_hover(pointCursor);

      }

      ::user::interaction::_001OnDraw(pgraphics);

   }


   void main_window::_001DrawItem(::draw2d::graphics_pointer& pgraphics, ::item* pitem)
   {

      if (::is_null(pitem))
      {

         return;

      }

      if (pitem->m_eelement == ::e_element_close_button)
      {

         ::user::draw_close_button(pgraphics, this, pitem);

         m_iCloseButtonDraw++;

         if (m_iCloseButtonDraw > 1)
         {

            //::output_debug_string("output");

         }

         return;

      }
      
      ::user::interaction::_001DrawItem(pgraphics, pitem);

   }


} // namespace app_app



