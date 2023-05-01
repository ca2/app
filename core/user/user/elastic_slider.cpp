#include "framework.h"
#include "elastic_slider.h"
#include "mesh.h"
#include "acme/constant/message.h"
#include "acme/platform/timer.h"
#include "acme/primitive/mathematics/scalar.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"


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
      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &elastic_slider::on_message_create);
      ////MESSAGE_LINK(e_message_timer, pchannel, this, &elastic_slider::_001OnTimer);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &elastic_slider::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &elastic_slider::on_message_left_button_up);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &elastic_slider::on_message_mouse_move);
   }


   void elastic_slider::on_message_create(::message::message * pmessage)
   {
    
      __UNREFERENCED_PARAMETER(pmessage);
      
      SetTimer(333, 50_ms, nullptr);

   }


   void elastic_slider::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);;

      if(ptimer->m_uEvent == 333)
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


   void elastic_slider::on_message_left_button_down(::message::message * pmessage)
   {
      
      auto pmouse = pmessage->m_union.m_pmouse;
      
      ::rectangle_i32 rectangle;
      
      GetSliderRect(rectangle);
      
      auto point = pmouse->m_point;

      screen_to_client()(point);

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


   void elastic_slider::CalcTension(point_i32 & point)
   {
      ::rectangle_i32 rectangleClient;
      client_rectangle(rectangleClient);
      if (rectangleClient.width() == 0)
      {
         m_dTensionPosition = 1.0;
      }

      else
      {
         m_dTensionPosition = ((double) point.x / (double) rectangleClient.width());
      }
   }

   
   void elastic_slider::CalcTension()
   {
      
      auto pointCursor = get_cursor_position();

      screen_to_client()(pointCursor);

      CalcTension(pointCursor);

   }


   double elastic_slider::GetForce()
   {
      return m_dTensionPosition - m_dPosition;
   }

   double elastic_slider::CalcScalar()
   {
      auto tickNow = ::time::now();
      if(tickNow - m_timeLastTime < 30_ms)
         return m_daScalar.simple_total_mean();
      CalcTension();
      double dScalar;
      if(m_bSlide)
      {
         double dForce = GetForce();
         auto dDeltaTime = (tickNow - m_timeLastTime).floating_millisecond();
         double dFilterLastScalar = m_daScalar.simple_total_mean();
         double dRate = 1.0 / 100.0;
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


   void elastic_slider::SetStreamingVelocityMode(scalar * pscalarVelocity,scalar * pscalarPosition)
   {

      m_escalar = e_scalar_streaming_velocity;

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

      ::rectangle_i32 rectangleClient;
      
      client_rectangle(rectangleClient);

      byte bAlpha = (byte) (128.0 * get_alpha());

      pgraphics->fill_rectangle(rectangleClient, argb(bAlpha, 250, 255, 255));

      ::rectangle_i32 rectangle;
      
      GetSliderRect(rectangle);

      pgraphics->draw_inset_rectangle(rectangle,argb(bAlpha,255,255,255), 1.0);
      
      rectangle.deflate(1, 1);
      
      pgraphics->draw_inset_rectangle(rectangle,argb(bAlpha,255,255,0), 1.0);
      
      rectangle.deflate(1, 1);
      
      pgraphics->draw_inset_rectangle(rectangle,argb(bAlpha,255,255,255), 1.0);

      if(m_bSlide)
      {
         
         pgraphics->set_current_point(rectangle.center());
         
         auto pointCursor = get_cursor_position();

         screen_to_client()(pointCursor);

         pgraphics->line_to(pointCursor);

      }

   }


   void elastic_slider::GetSliderRect(::rectangle_i32 & rectangle)
   {

      ::rectangle_i32 rectangleClient;

      client_rectangle(rectangleClient);

      i32 iWidth = 16;
      
      rectangle.top = rectangleClient.top;
      
      rectangle.bottom = rectangleClient.bottom;
      
      rectangle.left = (::i32) minimum(rectangleClient.right, m_dPosition * (rectangleClient.width() - iWidth));
      
      rectangle.right = (::i32) minimum(rectangleClient.right, m_dPosition * ((rectangleClient.width() - iWidth)) + iWidth);
      
   }


} // namespace user



