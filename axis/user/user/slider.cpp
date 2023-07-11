#include "framework.h"
#include "slider.h"
#include "acme/constant/message.h"
#include "aura/message/user.h"
#include "aura/graphics/draw2d/graphics.h"


namespace user
{


   slider::slider()
   {


      m_bSlide = false;

   }


   slider::~slider()
   {
   }


   void slider::install_message_routing(::channel * pchannel)
   {
      ::user::interaction::install_message_routing(pchannel);
      MESSAGE_LINK(MESSAGE_CREATE,pchannel,this,&slider::on_message_create);
//      //MESSAGE_LINK(e_message_timer,pchannel,this,&slider::_001OnTimer);
      MESSAGE_LINK(e_message_left_button_down,pchannel,this,&slider::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up,pchannel,this,&slider::on_message_left_button_up);
      MESSAGE_LINK(e_message_mouse_move,pchannel,this,&slider::on_message_mouse_move);
   }

   void slider::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      UNREFERENCED_PARAMETER(pmessage);

   }

   void slider::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);


   }


   void slider::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      //::rectangle_i32 rectangle;

      //get_slider_rect(rectangle);

      //auto point(pmouse->m_point);

      //screen_to_client()(point);

      //if(rectangle.contains(point))
      //{

      set_mouse_capture();

      m_bSlide = true;

      m_scalar.set_rate(get_slide_rate(), e_scalar_slide);

      set_need_redraw();

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

      //   pmouse->m_bRet = true;

      //   pmouse->set_lresult(1);

      //}

   }


   void slider::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if(m_bSlide)
      {

         release_mouse_capture();

         m_bSlide = false;

         m_scalar.set_rate(get_slide_rate(), e_scalar_set);

         set_need_redraw();

         pmouse->m_bRet = true;

         pmouse->m_lresult = 1;

      }

   }


   void slider::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if(m_bSlide)
      {

         m_scalar.set_rate(get_slide_rate(), e_scalar_slide);

         set_need_redraw();

         pmouse->m_bRet = true;

         pmouse->m_lresult = 1;

      }

   }



   double slider::get_slide_rate()
   {

      double dScalar = m_scalar.get_rate();

      auto pointCursor = get_cursor_position();

      screen_to_client(e_layout_design)(pointCursor);

      auto rectangle = client_rectangle();

      if(rectangle.width() != 0)
      {

         dScalar = (double) (pointCursor.x() - rectangle.left) / (double) rectangle.width();

      }

      dScalar = minimum(1.0, maximum(0.0, dScalar));

      return dScalar;

   }


   void slider::set_scalar(const ::scalar & scalar)
   {

      m_scalar = scalar;

   }


   void slider::set_rate(double dRate)
   {

      if(dRate < 0.0)
         dRate = 0.0;
      else if(dRate > 1.0)
         dRate = 1.0;

      m_scalar.set_rate(dRate, e_scalar_set);

      set_need_redraw();

   }


   void slider::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      if(m_bSlide)
      {

         m_dRate = get_slide_rate();

      }
      else
      {

         m_dRate = m_scalar.get_rate();

      }

      auto rectangleClient = client_rectangle();

      ::u8 bAlpha1 = (::u8) (128.0* get_alpha());

      pgraphics->fill_rectangle(rectangleClient, argb(bAlpha1, 250,255,255));

      ::rectangle_i32 rectangle;

      get_slider_rect(rectangle);

      ::u8 bAlpha = (::u8) (220.0* get_alpha());

      pgraphics->draw_inset_3d_rectangle(rectangle,argb(bAlpha / 255,108,100,210),argb(bAlpha,90,70,180), 1.0);
      rectangle.deflate(1,1);
      pgraphics->draw_inset_3d_rectangle(rectangle,argb(bAlpha / 255,150,120,150),argb(bAlpha,60,80,150), 1.0);
      rectangle.deflate(1,1);
      pgraphics->draw_inset_3d_rectangle(rectangle,argb(bAlpha / 255,108,100,210),argb(bAlpha,90,70,180), 1.0);
      rectangle.deflate(1,1);
      pgraphics->fill_rectangle(rectangle,argb(bAlpha1,140,108,120));
      //if(m_bSlide)
      //{
      //   pgraphics->set_current_point(rectangle.center());
      //   auto point = psession->get_cursor_position();
      //   screen_to_client()(point);
      //   pgraphics->line_to(point);
      //}
   }


   void slider::get_slider_rect(::rectangle_i32 & rectangle)
   {

      auto rectangleClient = client_rectangle();

      i32 iWidth = 16;

      rectangle.top = rectangleClient.top;
      rectangle.bottom = rectangleClient.bottom;
      rectangle.left = (::i32)minimum(rectangleClient.right,m_dRate * (rectangleClient.width() - iWidth));
      rectangle.right = (::i32)minimum(rectangleClient.right,m_dRate * ((rectangleClient.width() - iWidth)) + iWidth);


   }


} // namespace user























































