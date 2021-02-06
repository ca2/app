#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/user/_user.h"
#endif


namespace user
{


   elastic_slider::elastic_slider()
   {

      m_daScalar.allocate(100);
      m_daScalar.set(0.0);

      m_bSlide = false;
      m_iScalar = 0;

   }

   elastic_slider::~elastic_slider()
   {
   }


   void elastic_slider::install_message_routing(::channel * pchannel)
   {
      ::user::interaction::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &elastic_slider::_001OnCreate);
      ////MESSAGE_LINK(e_message_timer, pchannel, this, &elastic_slider::_001OnTimer);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &elastic_slider::_001OnLButtonDown);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &elastic_slider::_001OnLButtonUp);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &elastic_slider::_001OnMouseMove);
   }

   void elastic_slider::_001OnCreate(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      SetTimer(84 +77 +51 +33 + 23 + 49, 50, nullptr);
   }

   void elastic_slider::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);;

      if(ptimer->m_uEvent == 84 + 77 + 51 + 33 + 23 + 49)
      {
         double dScalar = CalcScalar();

         if(m_bSlide || dScalar > 0.001)
         {

            Slide();

         }
         else
         {
            UpdatePosition();
         }
      }

   }


   void elastic_slider::_001OnLButtonDown(::message::message * pmessage)
   {
      
      __pointer(::message::mouse) pmouse(pmessage);
      
      ::rectangle_i32 rectangle;
      
      GetSliderRect(rectangle);
      
      auto point = pmouse->m_point;

      _001ScreenToClient(point);

      if(rectangle.contains(point))
      {

         CalcTension(point);
         SetCapture();
         m_millisLastTime= ::millis::now();
         m_daScalar.set(0.0);
         m_iScalar = 0;
         m_bSlide = true;
         pmouse->m_bRet = true;
         pmouse->m_lresult = 1;
      }
   }

   void elastic_slider::_001OnLButtonUp(::message::message * pmessage)
   {
      __pointer(::message::mouse) pmouse(pmessage);
      if(m_bSlide)
      {

         m_bSlide= false;
         Slide();
         pmouse->m_bRet = true;
         pmouse->m_lresult = 1;
      }
   }

   void elastic_slider::_001OnMouseMove(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
//      __pointer(::message::mouse) pmouse(pmessage);
   }

   void elastic_slider::Slide()
   {

      UpdatePosition();

      m_pscalarVelocity->set_rate(CalcScalar(),scalar_set);

   }


   void elastic_slider::CalcTension(point_i32 & point)
   {
      ::rectangle_i32 rectClient;
      get_client_rect(rectClient);
      if (rectClient.width() == 0)
      {
         m_dTensionPosition = 1.0;
      }

      else
      {
         m_dTensionPosition = ((double) point.x / (double) rectClient.width());
      }
   }

   
   void elastic_slider::CalcTension()
   {
      
      auto psession = Session;

      auto point = psession->get_cursor_pos();

      _001ScreenToClient(point);

      CalcTension(point);

   }


   double elastic_slider::GetForce()
   {
      return m_dTensionPosition - m_dPosition;
   }

   double elastic_slider::CalcScalar()
   {
      auto tickNow = ::millis::now();
      if(tickNow - m_millisLastTime < 30)
         return m_daScalar.GetMean();
      CalcTension();
      double dScalar;
      if(m_bSlide)
      {
         double dForce = GetForce();
         auto dDeltaTime = tickNow - m_millisLastTime;
         double dFilterLastScalar = m_daScalar.GetMean();
         double dRate = 1.0 / 100.0;
         dScalar = dForce * __double(dDeltaTime) * dRate + dFilterLastScalar;
      }
      else
      {
         dScalar = 0.0;
      }
      m_daScalar[m_iScalar] =  dScalar;
      m_iScalar = (m_iScalar + 1) % m_daScalar.get_size();
      m_millisLastTime = tickNow;
      return m_daScalar.GetMean(); // Low Pass Filter
   }

   void elastic_slider::SetStreamingVelocityMode(scalar_base * pscalarVelocity,scalar_base * pscalarPosition)
   {

      m_escalar = scalar_streaming_velocity;

      m_pscalarVelocity = pscalarVelocity;

      m_pscalarPosition = pscalarPosition;

   }

   void elastic_slider::UpdatePosition()
   {

      SetSliderPos(m_pscalarPosition->get_rate(0.0));

   }


   void elastic_slider::SetSliderPos(double dPos)
   {
      if(dPos < 0.0)
         dPos = 0.0;
      else if(dPos > 1.0)
         dPos = 1.0;
      m_dPosition = dPos;
      set_need_redraw();
   }


   void elastic_slider::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      ::rectangle_i32 rectClient;
      get_client_rect(rectClient);

      class imaging & imaging = System.imaging();

      byte bAlpha = (byte) (128.0 * get_alpha());

      imaging.color_blend(
      pgraphics,
      rectClient,
      rgb(250, 255, 255),
      bAlpha);

      ::rectangle_i32 rectangle;
      GetSliderRect(rectangle);

      pgraphics->draw_rect(rectangle,argb(bAlpha,255,255,255));
      rectangle.deflate(1, 1);
      pgraphics->draw_rect(rectangle,argb(bAlpha,255,255,0));
      rectangle.deflate(1, 1);
      pgraphics->draw_rect(rectangle,argb(bAlpha,255,255,255));

      if(m_bSlide)
      {
         
         pgraphics->move_to(rectangle.center());
         
         auto psession = Session;

         auto point = psession->get_cursor_pos();

         _001ScreenToClient(point);

         pgraphics->line_to(point);

      }

   }


   void elastic_slider::GetSliderRect(::rectangle_i32 & rectangle)
   {

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      i32 iWidth = 16;
      rectangle.top = rectClient.top;
      rectangle.bottom = rectClient.bottom;
      rectangle.left = (::i32) min(rectClient.right, m_dPosition * (rectClient.width() - iWidth));
      rectangle.right = (::i32) min(rectClient.right, m_dPosition * ((rectClient.width() - iWidth)) + iWidth);
   }

} // namespace user
