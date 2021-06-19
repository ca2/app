#include "framework.h"
#include "aura/graphics/snippet/close_button.h"


namespace app_net
{


   window::window()
   {

      m_bGettingUrl = false;

      m_bSimpleUIDefaultMouseHandling = true;

      m_strUrl = "https://ca2.software/time";

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

      __construct(m_pfont);

      m_pfont->create_point_font(pnode->font_name(e_font_sans_ui), 21.0);

   }


   void window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      auto colorText = get_color(pstyle, ::user::e_element_text);

      pgraphics->set_text_color(colorText);

      pgraphics->set(m_pfont);

      if (!m_bGettingUrl)
      {

         string strMessage = "Click at window to start getting url";

         pgraphics->text_out(10, 10, strMessage);

      }

      string strUrl = m_strUrl;

      pgraphics->text_out(10, 50, strUrl);

      string strGet;

      if (m_bGettingUrl)
      {

         string strDots = "...";

         auto elapsed = m_millisStartGettingUrl.elapsed();

         auto millis = duration(elapsed).millis();

         strGet = "Getting Url " + strDots.Left((millis.m_iMilliseconds / 300) % 4);

      }
      else
      {

         strGet = m_strGet;

      }

      pgraphics->text_out(10, 150, strGet);

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

      }

   }


   void window::start_getting_url()
   {

      if (m_bGettingUrl)
      {

         return;

      }

      m_bGettingUrl = true;

      m_millisStartGettingUrl.Now();

      fork([this]()
         {

            property_set set;

            set["raw_http"] = true;

            string strGet = papplication->http().get(m_strUrl, set);

            {

               synchronous_lock synchronouslock(mutex());

               m_strGet = strGet;

            }

            m_bGettingUrl = false;

         });


   }

   
   bool window::on_click(const ::user::item& item)
   {

      start_getting_url();

      return true;

   }


} // namespace app_net



