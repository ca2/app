#include "framework.h"
#include "aura/graphics/user/close_button.h"

#define STEPPY_DEBUG 0


namespace app_message_box
{


   window::window()
   {

      m_bTransparent = true;

      m_rectInitialRateOrSize = { 0.05, 0.05, 0.4, 0.4 };

      m_dBreathPeriod = 60.0;

      m_millisStart.Now();

      m_dPhaseShift = 0.0;

   }


   window::~window()
   {


   }


   void window::on_create_user_interaction()
   {

      main_window::on_create_user_interaction();

      __construct(m_pbuttonShowMessageBox);

      m_pbuttonShowMessageBox->create_child(this);

      m_pbuttonShowMessageBox->set_window_text("Show message box");

      m_pbuttonShowMessageBox->add_control_event_handler(this);

#if !STEPPY_DEBUG

      set_prodevian();

#endif


//#ifdef WINDOWS_DESKTOP

  //    ModifyStyle(WS_CAPTION, 0);

//#endif

  //    ModifyStyleEx(0, WS_EX_LAYERED);

      auto papplication = get_application();

      papplication->m_bInterprocessIntercommunication = false;

      //::user::interaction * p = this;

   }


   void window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
      //return;

      m_iCloseButtonDraw = 0;

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if (rectangleClient.is_empty())
      {

         return;

      }

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);

      pgraphics->fill_rectangle(rectangleClient, argb(127, 255, 255, 255));

      //return;

      double dBase = (double) rectangleClient.minimum_signed_absolute_dimension() / 17.0;

      double x = dBase * 3;

      double y = dBase * 3;

      pgraphics->fill_rectangle(::rectangle_f64_dimension(x, y, dBase * 5.0, dBase * 5.0), __acolor(127, 40, 150, 235));

      pgraphics->fill_rectangle(::rectangle_f64_dimension(x + dBase * 6.0, y, dBase * 5.0, dBase * 5.0), __acolor(127, 40, 150, 235));

      pgraphics->fill_rectangle(::rectangle_f64_dimension(x, y + dBase * 6.0, dBase * 11.0, dBase * 5.0), __acolor(127, 255, 110, 150));

      rectangleClient.deflate((::i32) dBase);

      for (int i = 0; i < dBase; i++)
      {

         pgraphics->draw_rectangle(rectangleClient, __acolor(255, 127, 127, 127));

         rectangleClient.deflate(1, 1);

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

         auto pwindowing = puser->windowing();

         auto pointCursor = pwindowing->get_cursor_position();

         update_hover(pointCursor);

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

            //::output_debug_string("output");

         }

      }

   }


   void window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      m_pbuttonShowMessageBox->display();

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      double dBase = (double)rectangleClient.minimum_signed_absolute_dimension() / 17.0;

      double x = dBase * 3;

      double y = dBase * 3;

      ::rectangle_i32 rectangleButton(rectangleClient);

      rectangleButton.right -= (int) x;

      rectangleButton.bottom -= (int) y;

      rectangleButton.left = (int) (rectangleButton.right - x * 3.5);

      rectangleButton.top = (int) (rectangleButton.bottom - y * 1.65);

      m_pbuttonShowMessageBox->place(rectangleButton);


   }


   void window::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::e_event_button_clicked)
      {

         if (pevent->m_puserinteraction == m_pbuttonShowMessageBox
            && pevent->m_actioncontext.is_user_source())
         {

            try
            {

               show_message_box();

               pevent->m_bRet = true;

               return;

            }
            catch (...)
            {

            }

         }

      }

   }


   void window::show_message_box()
   {

      auto pprocess = message_box("Showing a message box as requested.\n\nIs it ok?", nullptr, e_message_box_yes_no_cancel);

      pprocess->then([this](auto future)
         {

            if (future->m_edialogresult == e_dialog_result_yes)
            {

               auto papplication = get_application();

               papplication->_001TryCloseApplication();

            }
            else
            {

               show_message_box();

            }

         });

   }


} // namespace app_message_box



