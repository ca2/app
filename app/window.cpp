#include "framework.h"
#include "aura/graphics/snippet/close_button.h"


namespace app_app
{


   window::window()
   {

      m_rectInitialRateOrSize = { 0.05, 0.05, 0.4, 0.4 };

      m_dBreathPeriod = 60.0;

      m_dStartTime = ::get_secs();

      m_dPhaseShift = 0.0;

   }


   void window::on_create_user_interaction()
   {

      main_window::on_create_user_interaction();

      set_prodevian();

#ifdef WINDOWS_DESKTOP

      ModifyStyle(WS_CAPTION, 0);

#endif

      ModifyStyleEx(0, WS_EX_LAYERED);

      auto & app = App(this);

      app.m_bInterprocessIntercommunication = false;

      ::user::interaction * p = this;

   }


   void window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      m_iCloseButtonDraw = 0;

      ::rect rectClient;

      get_client_rect(rectClient);

      if (rectClient.is_empty())
      {

         return;

      }

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);

      pgraphics->fill_rect(rectClient, ARGB(127, 255, 255, 255));

      double dBase = (double) rectClient.minimum_signed_absolute_dimension() / 17.0;

      double x = dBase * 3;

      double y = dBase * 3;

      pgraphics->fill_solid_rect_dim(x, y, dBase * 5.0, dBase * 5.0, ARGB(127, 40, 150, 235));

      pgraphics->fill_solid_rect_dim(x + dBase * 6.0, y, dBase * 5.0, dBase * 5.0, ARGB(127, 40, 150, 235));

      pgraphics->fill_solid_rect_dim(x, y + dBase * 6.0, dBase * 11.0, dBase * 5.0, ARGB(127, 255, 110, 150));

      rectClient.deflate((::i32) dBase);

      for (int i = 0; i < dBase; i++)
      {

         pgraphics->draw_rect(rectClient, __acolor(255, 127, 127, 127));

         rectClient.deflate(1, 1);

      }

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

      auto pitem = get_user_item(::user::e_element_close_button);

      if (::is_set(pitem))
      {

         bool bHover = m_itemHover == ::user::e_element_close_button;

         double dSourcePeriod;
         
         if (bHover)
         {

            dSourcePeriod = 0.5;

         }
         else
         {

            dSourcePeriod = 5.0;

         }

         double time = get_secs() - m_dStartTime;

         double dFrequency = 1.0 / m_dBreathPeriod;

         double omega = 2.0 * System.math().GetPi() * dFrequency;

         double angle = omega * time;

         angle += m_dPhaseShift;

         double dNewPeriod = m_dBreathPeriod;

         if (dSourcePeriod < dNewPeriod)
         {

            dNewPeriod -= dNewPeriod * 0.1;

         }
         else if (dSourcePeriod > dNewPeriod)
         {

            dNewPeriod += dNewPeriod * 0.1;

         }

         if (dNewPeriod != m_dBreathPeriod)
         {

            m_dBreathPeriod = dNewPeriod;

            dFrequency = 1.0 / m_dBreathPeriod;

            omega = 2.0 * System.math().GetPi() * dFrequency;

            double angleNew = omega * time;

            m_dPhaseShift = angle - angleNew;

            m_dPhaseShift = fmod(m_dPhaseShift, 2.0 * System.math().GetPi());

         }

         int iSize = (int) (::sin(angle) * 20.0 + 64.0);

         get_client_rect(pitem->m_rect);

         pitem->m_rect.left = pitem->m_rect.right - iSize;

         pitem->m_rect.bottom = pitem->m_rect.top + iSize;

         auto psession = Session;

         update_hover(get_cursor_pos());

      }

      ::user::interaction::_001OnDraw(pgraphics);

   }


   void window::_001DrawItem(::draw2d::graphics_pointer& pgraphics, ::user::item* pitem)
   {

      if (::is_null(pitem))
      {

         return;

      }

      if (pitem->m_eelement == ::user::e_element_close_button)
      {

         ::user::draw_close_button(pgraphics, this, pitem);

         m_iCloseButtonDraw++;

         if (m_iCloseButtonDraw > 1)
         {

            ::output_debug_string("output");

         }

      }

   }


} // namespace app_app



