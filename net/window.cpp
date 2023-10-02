#include "framework.h"
//#include "aura/graphics/draw2d/_component.h"
#include "aura/graphics/user/control_box_button.h"


namespace app_net
{


   window::window() 
   {

      m_bGettingUrl = false;

      //m_bSimpleUIDefaultMouseHandling = true;

      m_strUrl = "https://ca2.software/time";

      m_dBreathPeriod = 60.0;

      m_timeStart.Now();

      m_dPhaseShift = 0.0;

   }



   void window::on_create_user_interaction()
   {

      main_window::on_create_user_interaction();

      set_auto_refresh();

#ifdef WINDOWS_DESKTOP

      ModifyStyle(WS_CAPTION, 0);

#endif

      //ModifyStyleEx(0, WS_EX_LAYERED);

      auto papp = get_app();

      papp->m_bInterprocessCommunication = false;

      ::user::interaction * p = this;

      __construct(m_pfont);

      auto psystem = acmesystem()->m_paurasystem;

      auto pnode = psystem->node();

      m_pfont->create_point_font(pnode->font_name(e_font_sans_ui), 21.0);

   }


   void window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      auto colorText = get_color(pstyle, ::e_element_text);

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

         auto elapsed = m_timeStartGettingUrl.elapsed();

         strGet = "Getting Url " + strDots.left((elapsed.integral_millisecond().m_i / 300) % 4);

      }
      else
      {

         strGet = m_strGet;

      }

      pgraphics->text_out(10, 150, strGet);

   }


   void window::_001DrawItem(::draw2d::graphics_pointer& pgraphics, ::item* pitem, const ::user::e_state & estate)
   {

      if (::is_null(pitem))
      {

         return;

      }

      if (pitem->m_item.m_eelement == ::e_element_close_button)
      {

         ::user::draw_close_button(pgraphics, this, pitem, estate);

      }

   }


   void window::start_getting_url()
   {

      if (m_bGettingUrl)
      {

         return;

      }

      m_bGettingUrl = true;

      m_timeStartGettingUrl.Now();

      fork([this]()
         {

            property_set set;

            set["raw_http"] = true;

            auto papp = get_app();

            string strGet = papp->http().get(m_strUrl, set);

            {

               synchronous_lock synchronouslock(this->synchronization());

               m_strGet = strGet;

            }

            m_bGettingUrl = false;

         });


   }

   
   bool window::on_click(::item * pitem)
   {

      start_getting_url();

      return true;

   }


} // namespace app_net



