#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/user/_user.h"
#endif


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


   bool step_slider::create_window(::user::interaction * pwndParent, id id)
   {

      return ::user::interaction::create_window(nullptr, nullptr, WS_CHILD, pwndParent, id) != FALSE;

   }


   void step_slider::install_message_routing(::channel * pchannel)
   {
      ::user::interaction::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &step_slider::_001OnCreate);
//      //MESSAGE_LINK(e_message_timer, pchannel, this, &step_slider::_001OnTimer);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &step_slider::_001OnLButtonDown);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &step_slider::_001OnLButtonUp);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &step_slider::_001OnMouseMove);
   }

   void step_slider::_001OnCreate(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
//      SCAST_PTR(::message::create, pcreate, pmessage);

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

   void step_slider::_001OnLButtonDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      m_itemLButtonDown = hit_test(pmouse);

   }


   void step_slider::_001OnLButtonUp(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      auto item = hit_test(pmouse);

      if(item == m_itemLButtonDown)
      {

         m_scalar.set(item);

      }

   }


   void step_slider::_001OnMouseMove(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
//      SCAST_PTR(::message::mouse, pmouse, pmessage);
      SetTimer(1, 200, nullptr);
      m_itemHover = true;
      update_hover();
   }


   void step_slider::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      

      if(m_scalar.is_null())
         return;

      ::rect rectClient;
      get_client_rect(rectClient);
      class imaging & imaging = System.imaging();

      byte bAlpha = (byte) (128.0 * get_alpha());

      imaging.color_blend(
         pgraphics,
         rectClient,
         RGB(150, 200, 255),
         bAlpha);

      i64 iMin = m_scalar.minimum();
      i64 iMax = m_scalar.maximum();
      i64 iVal = m_scalar;

      ::rect rect;
      for(i64 i = iMin; i <= iMax; i++)
      {
         GetStepRect(rect, i, iMin, iMax, rectClient);
         if(i == iVal)
         {
            if(m_itemHover.item_index() == i)
            {
               imaging.color_blend(
                  pgraphics,
                  rect,
                  RGB(255, 255, 240),
                  bAlpha);
            }
            else
            {
               imaging.color_blend(
                  pgraphics,
                  rect,
                  RGB(255, 255, 150),
                  bAlpha);
            }
         }
         else
         {
            if(m_itemHover.item_index() == i)
            {
               imaging.color_blend(
                  pgraphics,
                  rect,
                  RGB(255, 180, 180),
                  bAlpha);
            }
            else
            {
               imaging.color_blend(
                  pgraphics,
                  rect,
                  RGB(100, 100, 255),
                  bAlpha);
            }
         }
      }
   }


   void step_slider::GetStepHoverRect(RECT32 * prect, i64 iStep, i64 iMin, i64 iMax, const ::rect & rectClient)
   {

      if((iMax - iMin) == 0)
         return;

      prect->top = rectClient.top;

      prect->bottom = rectClient.bottom;

      double dWidth = ((double)rectClient.width()) / (iMax - iMin);

      prect->left = (::i32) (dWidth * (iStep - iMin));

      prect->right = (::i32) (dWidth * (iStep - iMin + 1));



   }


   void step_slider::GetStepRect(RECT32 * prect, i64 iStep, i64 iMin, i64 iMax, const ::rect & rectClient)
   {

      if((iMax - iMin) == 0)
         return;

      GetStepHoverRect(prect, iStep, iMin, iMax, rectClient);

      i32 halfm = (prect->right - prect->left - 2) / 2;

      prect->left +=  halfm;

      prect->right -=  halfm;


   }


   void step_slider::on_hit_test(::user::item & item)
   {

      ::rect rectClient;

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

      auto point = psession->get_cursor_pos();
      
      m_itemHover = hit_test(point);

      set_need_redraw();

      ::rect rectClient;

      get_client_rect(rectClient);

      m_itemHover = rectClient.contains(point) != FALSE;

   }


} // namespace user
