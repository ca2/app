#include "framework.h"
#include "core/user/user/_user.h"


namespace user
{


   step_slider::step_slider()
   {

      //m_iHover = 0x80000000;
      //m_itemHover = false;

   }

   step_slider::~step_slider()
   {
   }


   //bool step_slider::create_window(::user::interaction * pwndParent, id id)
   //{

   //   return ::user::interaction::create_window(nullptr, nullptr, WS_CHILD, pwndParent, id) != false;

   //}


   void step_slider::install_message_routing(::channel * pchannel)
   {
      ::user::interaction::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &step_slider::on_message_create);
//      //MESSAGE_LINK(e_message_timer, pchannel, this, &step_slider::_001OnTimer);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &step_slider::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &step_slider::on_message_left_button_up);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &step_slider::_001OnMouseMove);
   }

   void step_slider::on_message_create(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
//      __pointer(::message::create) pcreate(pmessage);

   }

   void step_slider::_001OnTimer(::timer * ptimer)
   {
      ::user::interaction::_001OnTimer(ptimer);;
      if(ptimer->m_uEvent == 1)
      {
         if(m_itemHover.is_set())
         {
            update_hover();
            if(!m_itemHover.is_set())
               KillTimer(1);
         }
      }
   }

   void step_slider::on_message_left_button_down(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      m_itemLButtonDown = hit_test(pmouse);

   }


   void step_slider::on_message_left_button_up(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      auto item = hit_test(pmouse);

      if(item == m_itemLButtonDown)
      {

         m_scalar.set(item);

      }

   }


   void step_slider::_001OnMouseMove(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
//      __pointer(::message::mouse) pmouse(pmessage);
      SetTimer(1, 200, nullptr);
      m_itemHover = true;
      update_hover();
   }


   void step_slider::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      

      if(m_scalar.is_null())
         return;

      ::rectangle_i32 rectClient;
      get_client_rect(rectClient);
      class imaging & imaging = System.imaging();

      byte bAlpha = (byte) (128.0 * get_alpha());

      imaging.color_blend(
         pgraphics,
         rectClient,
         rgb(150, 200, 255),
         bAlpha);

      i64 iMin = m_scalar.minimum();
      i64 iMax = m_scalar.maximum();
      i64 iVal = m_scalar;

      ::rectangle_i32 rectangle;
      for(i64 i = iMin; i <= iMax; i++)
      {
         GetStepRect(rectangle, i, iMin, iMax, rectClient);
         if(i == iVal)
         {
            if(m_itemHover.item_index() == i)
            {
               imaging.color_blend(
                  pgraphics,
                  rectangle,
                  rgb(255, 255, 240),
                  bAlpha);
            }
            else
            {
               imaging.color_blend(
                  pgraphics,
                  rectangle,
                  rgb(255, 255, 150),
                  bAlpha);
            }
         }
         else
         {
            if(m_itemHover.item_index() == i)
            {
               imaging.color_blend(
                  pgraphics,
                  rectangle,
                  rgb(255, 180, 180),
                  bAlpha);
            }
            else
            {
               imaging.color_blend(
                  pgraphics,
                  rectangle,
                  rgb(100, 100, 255),
                  bAlpha);
            }
         }
      }
   }


   void step_slider::GetStepHoverRect(RECTANGLE_I32 * prectangle, i64 iStep, i64 iMin, i64 iMax, const ::rectangle_i32 & rectClient)
   {

      if((iMax - iMin) == 0)
         return;

      prectangle->top = rectClient.top;

      prectangle->bottom = rectClient.bottom;

      double dWidth = ((double)rectClient.width()) / (iMax - iMin);

      prectangle->left = (::i32) (dWidth * (iStep - iMin));

      prectangle->right = (::i32) (dWidth * (iStep - iMin + 1));



   }


   void step_slider::GetStepRect(RECTANGLE_I32 * prectangle, i64 iStep, i64 iMin, i64 iMax, const ::rectangle_i32 & rectClient)
   {

      if((iMax - iMin) == 0)
         return;

      GetStepHoverRect(prectangle, iStep, iMin, iMax, rectClient);

      i32 halfm = (prectangle->right - prectangle->left - 2) / 2;

      prectangle->left +=  halfm;

      prectangle->right -=  halfm;


   }


   void step_slider::on_hit_test(::user::item & item)
   {

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      if (rectClient.width() == 0)
      {

         item = ::user::e_element_none;

         return;

      }

      i64 iMin, iMax;

      iMin = m_scalar.minimum();

      iMax = m_scalar.maximum();

      item = (index) (iMin + (((item.m_pointHitTest.x - rectClient.left) * (iMax - iMin)) / rectClient.width()));

   }


   void step_slider::update_hover()
   {

      auto psession = Session;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pointCursor = pwindowing->get_cursor_position();

      m_itemHover = hit_test(pointCursor);

      set_need_redraw();

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      m_itemHover = rectClient.contains(pointCursor) != false;

   }


} // namespace user
