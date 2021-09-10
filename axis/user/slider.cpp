#include "framework.h"
#include "axis/user/_user.h"


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
      MESSAGE_LINK(e_message_create,pchannel,this,&slider::on_message_create);
//      //MESSAGE_LINK(e_message_timer,pchannel,this,&slider::_001OnTimer);
      MESSAGE_LINK(e_message_left_button_down,pchannel,this,&slider::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up,pchannel,this,&slider::on_message_left_button_up);
      MESSAGE_LINK(e_message_mouse_move,pchannel,this,&slider::on_message_mouse_move);
   }

   void slider::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      __UNREFERENCED_PARAMETER(pmessage);

   }

   void slider::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);


   }


   void slider::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      //::rectangle_i32 rectangle;

      //get_slider_rect(rectangle);

      //auto point(pmouse->m_point);

      //screen_to_client(point);

      //if(rectangle.contains(point))
      //{

      set_mouse_capture();

      m_bSlide = true;

      m_pscalar->set_rate(get_slide_rate(), scalar_slide);

      set_need_redraw();

      pmouse->m_bRet = true;

      pmouse->m_lresult = 1;

      //   pmouse->m_bRet = true;

      //   pmouse->set_lresult(1);

      //}

   }

   void slider::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      if(m_bSlide)
      {

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         pwindowing->release_mouse_capture();

         m_bSlide = false;

         m_pscalar->set_rate(get_slide_rate(), scalar_set);

         set_need_redraw();

         pmouse->m_bRet = true;

         pmouse->m_lresult = 1;

      }

   }


   void slider::on_message_mouse_move(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_pmouse;

      if(m_bSlide)
      {

         m_pscalar->set_rate(get_slide_rate(), scalar_slide);

         set_need_redraw();

         pmouse->m_bRet = true;

         pmouse->m_lresult = 1;

      }

   }



   double slider::get_slide_rate()
   {

      double dScalar = m_pscalar->get_rate();

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto point = pwindowing->get_cursor_position();

      screen_to_client(point, e_layout_design);

      ::rectangle_i32 rectangle;

      get_client_rect(rectangle);

      if(rectangle.width() != 0)
      {

         dScalar = (double) (point.x - rectangle.left) / (double) rectangle.width();

      }

      dScalar = minimum(1.0, maximum(0.0, dScalar));

      return dScalar;

   }


   void slider::set_scalar(scalar_base * pscalar)
   {

      m_pscalar = pscalar;

   }


   void slider::set_rate(double dRate)
   {

      if(dRate < 0.0)
         dRate = 0.0;
      else if(dRate > 1.0)
         dRate = 1.0;

      m_pscalar->set_rate(dRate, scalar_set);

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

         m_dRate = m_pscalar->get_rate();

      }

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      byte bAlpha1 = (byte) (128.0* get_alpha());

      pgraphics->fill_rectangle(rectangleClient, argb(bAlpha1, 250,255,255));

      ::rectangle_i32 rectangle;

      get_slider_rect(rectangle);

      byte bAlpha = (byte) (220.0* get_alpha());

      pgraphics->draw_inset_3drect(rectangle,argb(bAlpha / 255,108,100,210),argb(bAlpha,90,70,180));
      rectangle.deflate(1,1);
      pgraphics->draw_inset_3drect(rectangle,argb(bAlpha / 255,150,120,150),argb(bAlpha,60,80,150));
      rectangle.deflate(1,1);
      pgraphics->draw_inset_3drect(rectangle,argb(bAlpha / 255,108,100,210),argb(bAlpha,90,70,180));
      rectangle.deflate(1,1);
      pgraphics->fill_rectangle(rectangle,argb(bAlpha1,140,108,120));
      //if(m_bSlide)
      //{
      //   pgraphics->move_to(rectangle.center());
      //   auto point = psession->get_cursor_position();
      //   screen_to_client(point);
      //   pgraphics->line_to(point);
      //}
   }


   void slider::get_slider_rect(::rectangle_i32 & rectangle)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      i32 iWidth = 16;

      rectangle.top = rectangleClient.top;
      rectangle.bottom = rectangleClient.bottom;
      rectangle.left = (::i32)minimum(rectangleClient.right,m_dRate * (rectangleClient.width() - iWidth));
      rectangle.right = (::i32)minimum(rectangleClient.right,m_dRate * ((rectangleClient.width() - iWidth)) + iWidth);


   }


} // namespace user























































