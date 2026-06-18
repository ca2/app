#include "framework.h"
#include "elastic_slider.h"
#include "mesh.h"
#include "acme/constant/user_message.h"
#include "acme/constant/timer.h"
#include "acme/prototype/mathematics/scalar.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"


namespace user
{


   elastic_slider::elastic_slider()
   {

      m_daScalar.set_size(100);
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
      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &elastic_slider::on_message_create);
      ////USER_MESSAGE_LINK(::user::e_message_timer, pchannel, this, &elastic_slider::on_timer);
      USER_MESSAGE_LINK(::user::e_message_left_button_down, pchannel, this, &elastic_slider::on_message_left_button_down);
      USER_MESSAGE_LINK(::user::e_message_left_button_up, pchannel, this, &elastic_slider::on_message_left_button_up);
      USER_MESSAGE_LINK(::user::e_message_mouse_move, pchannel, this, &elastic_slider::on_message_mouse_move);
   }


   void elastic_slider::on_message_create(::message::message * pmessage)
   {
    
      __UNREFERENCED_PARAMETER(pmessage);
      
      set_timer(e_timer_update_slider, 50_ms);

   }


   void elastic_slider::operator()(::timer * ptimer)
   {

      ::user::interaction::operator()(ptimer);;

      if(ptimer->m_etimer == e_timer_update_slider)
      {

         ::f64 dScalar = CalcScalar();

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


   void elastic_slider::on_message_left_button_down(::message::message * pmessage)
   {
      
      auto pmouse = pmessage->m_union.m_pmouse;
      
      ::i32_rectangle rectangle;
      
      GetSliderRect(rectangle);
      
      auto point = pmouse->m_pointHost;

      host_to_client()(point);

      if(rectangle.contains(point))
      {

         CalcTension(point);
         set_mouse_capture();
         m_timeLastTime= ::time::now();
         m_daScalar.set(0.0);
         m_iScalar = 0;
         m_bSlide = true;
         pmouse->m_bRet = true;
         pmouse->m_lresult = 1;
      }
   }

   void elastic_slider::on_message_left_button_up(::message::message * pmessage)
   {
      auto pmouse = pmessage->m_union.m_pmouse;
      if(m_bSlide)
      {

         m_bSlide= false;
         Slide();
         pmouse->m_bRet = true;
         pmouse->m_lresult = 1;
      }
   }

   void elastic_slider::on_message_mouse_move(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
//      auto pmouse = pmessage->m_union.m_pmouse;
   }


   void elastic_slider::Slide()
   {

      UpdatePosition();

      m_pscalarVelocity->set_rate(CalcScalar(), e_scalar_set);

   }


   void elastic_slider::CalcTension(i32_point & point)
   {
      auto rectangleX = this->rectangle();
      if (rectangleX.width() == 0)
      {
         m_dTensionPosition = 1.0;
      }

      else
      {
         m_dTensionPosition = ((::f64) point.x / (::f64) rectangleX.width());
      }
   }

   
   void elastic_slider::CalcTension()
   {
      
      auto pointCursor = host_mouse_cursor_position();

      host_to_client()(pointCursor);

      CalcTension(pointCursor);

   }


   ::f64 elastic_slider::GetForce()
   {
      return m_dTensionPosition - m_dPosition;
   }

   ::f64 elastic_slider::CalcScalar()
   {
      auto tickNow = ::time::now();
      if(tickNow - m_timeLastTime < 30_ms)
         return m_daScalar.simple_total_mean();
      CalcTension();
      ::f64 dScalar;
      if(m_bSlide)
      {
         ::f64 dForce = GetForce();
         auto dDeltaTime = (tickNow - m_timeLastTime).floating_millisecond();
         ::f64 dFilterLastScalar = m_daScalar.simple_total_mean();
         ::f64 dRate = 1.0 / 100.0;
         dScalar = dForce * dDeltaTime * dRate + dFilterLastScalar;
      }
      else
      {
         dScalar = 0.0;
      }
      m_daScalar[m_iScalar] =  dScalar;
      m_iScalar = (m_iScalar + 1) % m_daScalar.get_size();
      m_timeLastTime = tickNow;
      return m_daScalar.simple_total_mean(); // Low Pass Filter

   }


   void elastic_slider::SetStreamingVelocityMode(::number::scalar * pscalarVelocity,::number::scalar * pscalarPosition)
   {

      m_escalar = e_scalar_streaming_velocity;

      m_pscalarVelocity = pscalarVelocity;

      m_pscalarPosition = pscalarPosition;

   }


   void elastic_slider::UpdatePosition()
   {

      SetSliderPos(m_pscalarPosition->get_rate(0.0));

   }


   void elastic_slider::SetSliderPos(::f64 dPos)
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

      auto rectangleX = this->rectangle();

      ::u8 bAlpha = (::u8) (128.0 * get_alpha());

      pgraphics->fill_rectangle(rectangleX, argb(bAlpha, 250, 255, 255));

      ::i32_rectangle rectangle;
      
      GetSliderRect(rectangle);

      pgraphics->draw_inset_rectangle(rectangle,argb(bAlpha,255,255,255), 1.0);
      
      rectangle.deflate(1, 1);
      
      pgraphics->draw_inset_rectangle(rectangle,argb(bAlpha,255,255,0), 1.0);
      
      rectangle.deflate(1, 1);
      
      pgraphics->draw_inset_rectangle(rectangle,argb(bAlpha,255,255,255), 1.0);

      if(m_bSlide)
      {
         
         auto pointCursor = host_mouse_cursor_position();

         host_to_client()(pointCursor);

         pgraphics->line(rectangle.center(),  pointCursor);

      }

   }


   void elastic_slider::GetSliderRect(::i32_rectangle & rectangle)
   {

      auto rectangleX = this->rectangle();

      ::i32 iWidth = 16;
      
      rectangle.top = rectangleX.top;
      
      rectangle.bottom = rectangleX.bottom;
      
      rectangle.left = (::i32) minimum(rectangleX.right, m_dPosition * (rectangleX.width() - iWidth));
      
      rectangle.right = (::i32) minimum(rectangleX.right, m_dPosition * ((rectangleX.width() - iWidth)) + iWidth);
      
   }


} // namespace user



