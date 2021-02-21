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
      MESSAGE_LINK(e_message_mouse_move,pchannel,this,&slider::_001OnMouseMove);
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

      __pointer(::message::mouse) pmouse(pmessage);

      //::rect rect;

      //get_slider_rect(rect);

      //auto point(pmouse->m_point);

      //_001ScreenToClient(point);

      //if(rect.contains(point))
      //{

      SetCapture();

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

      __pointer(::message::mouse) pmouse(pmessage);

      if(m_bSlide)
      {

         ReleaseCapture();

         m_bSlide = false;

         m_pscalar->set_rate(get_slide_rate(), scalar_set);

         set_need_redraw();

         pmouse->m_bRet = true;

         pmouse->m_lresult = 1;

      }

   }


   void slider::_001OnMouseMove(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

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

      auto point = psession->get_cursor_pos();

      _001ScreenToClient(point, e_layout_design);

      ::rect rect;

      get_client_rect(rect);

      if(rect.width() != 0)
      {

         dScalar = (double) (point.x - rect.left) / (double) rect.width();

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

      ::rect rectClient;

      get_client_rect(rectClient);

      class imaging & imaging = System.imaging();

      byte bAlpha1 = (byte) (128.0* get_alpha());

      imaging.color_blend(pgraphics, rectClient, rgb(250,255,255), bAlpha1);

      ::rect rect;

      get_slider_rect(rect);

      byte bAlpha = (byte) (220.0* get_alpha());

      pgraphics->draw_3drect(rect,argb(bAlpha / 255,108,100,210),argb(bAlpha,90,70,180));
      rect.deflate(1,1);
      pgraphics->draw_3drect(rect,argb(bAlpha / 255,150,120,150),argb(bAlpha,60,80,150));
      rect.deflate(1,1);
      pgraphics->draw_3drect(rect,argb(bAlpha / 255,108,100,210),argb(bAlpha,90,70,180));
      rect.deflate(1,1);
      pgraphics->fill_rectangle(rect,argb(bAlpha1,140,108,120));
      //if(m_bSlide)
      //{
      //   pgraphics->move_to(rect.center());
      //   auto point = psession->get_cursor_pos();
      //   _001ScreenToClient(point);
      //   pgraphics->line_to(point);
      //}
   }


   void slider::get_slider_rect(::rect & rect)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      i32 iWidth = 16;

      rect.top = rectClient.top;
      rect.bottom = rectClient.bottom;
      rect.left = (::i32)minimum(rectClient.right,m_dRate * (rectClient.width() - iWidth));
      rect.right = (::i32)minimum(rectClient.right,m_dRate * ((rectClient.width() - iWidth)) + iWidth);


   }


} // namespace user























































