#include "framework.h"
#include "aura/graphics/snippet/close_button.h"

#define STEPPY_DEBUG 0


namespace app_app
{


   main_window::main_window()
   {

      m_bTransparent = true;

      m_rectInitialRateOrSize = { 0.05, 0.05, 0.4, 0.4 };

      m_dBreathPeriod = 60.0;

      m_millisStart.Now();

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


//#ifdef WINDOWS_DESKTOP

  //    ModifyStyle(WS_CAPTION, 0);

//#endif

  //    ModifyStyleEx(0, WS_EX_LAYERED);

      //auto & app = App(this);

      auto papplication = get_application();

      papplication->m_bInterprocessIntercommunication = false;

      ::user::interaction * p = this;

   }


   void main_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      //return;

      m_iCloseButtonDraw = 0;

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      if (rectClient.is_empty())
      {

         return;

      }

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);

      pgraphics->fill_rectangle(rectClient, argb(127, 255, 255, 255));

      //return;

      double dBase = (double) rectClient.minimum_signed_absolute_dimension() / 17.0;

      double x = dBase * 3;

      double y = dBase * 3;

      pgraphics->fill_rectangle(::rectd_dim(x, y, dBase * 5.0, dBase * 5.0), __acolor(127, 40, 150, 235));

      pgraphics->fill_rectangle(::rectd_dim(x + dBase * 6.0, y, dBase * 5.0, dBase * 5.0), __acolor(127, 40, 150, 235));

      pgraphics->fill_rectangle(::rectd_dim(x, y + dBase * 6.0, dBase * 11.0, dBase * 5.0), __acolor(127, 255, 110, 150));

      rectClient.deflate((::i32) dBase);

      for (int i = 0; i < dBase; i++)
      {

         pgraphics->draw_rectangle(rectClient, __acolor(255, 127, 127, 127));

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

         double time = m_millisStart.elapsed().m_i / 1'000.0;

         double dFrequency = 1.0 / m_dBreathPeriod;

         auto pmathematics = ::mathematics::mathematics();

         double omega = 2.0 * pmathematics->get_pi() * dFrequency;

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

         auto psession = get_session();

         auto puser = psession->user();

         auto pmainwindow = puser->windowing();

         auto pointCursor = pmainwindow->get_cursor_position();

         update_hover(pointCursor);

      }

      ::user::interaction::_001OnDraw(pgraphics);

   }


   void main_window::_001DrawItem(::draw2d::graphics_pointer& pgraphics, ::user::item* pitem)
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

            //::output_debug_string("output");

         }

      }

   }


} // namespace app_app



