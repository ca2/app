#include "framework.h"
#include "step_slider.h"
#include "acme/constant/message.h"
#include "acme/handler/item.h"
#include "acme/platform/timer.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"
#include "aura/user/user/interaction_impl.h"


namespace user
{


   step_slider::step_slider()
   {

      //m_iHover = 0x80000000;
      //m_pitemHover = false;

   }

   step_slider::~step_slider()
   {
   }


   //bool step_slider::create_window(::user::interaction * puserinteractionParent, atom atom)
   //{

   //   return ::user::interaction::create_window(nullptr, nullptr, WS_CHILD, puserinteractionParent, atom) != false;

   //}


   void step_slider::install_message_routing(::channel * pchannel)
   {
      ::user::interaction::install_message_routing(pchannel);
      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &step_slider::on_message_create);
//      //MESSAGE_LINK(e_message_timer, pchannel, this, &step_slider::_001OnTimer);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &step_slider::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &step_slider::on_message_left_button_up);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &step_slider::on_message_mouse_move);
   }

   void step_slider::on_message_create(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
//      ::pointer<::message::create>pcreate(pmessage);

   }

   void step_slider::_001OnTimer(::timer * ptimer)
   {
      ::user::interaction::_001OnTimer(ptimer);;
//      if(ptimer->m_uEvent == 1)
//      {
//         if(::is_set(m_pitemHover))
//         {
//            update_hover();
//            if(!::is_set(m_pitemHover))
//               KillTimer(1);
//         }
//      }
   }

   void step_slider::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pwindowimpl = get_window_impl();

      pwindowimpl->m_pitemLButtonDown = hit_test(pmouse, ::user::e_zorder_any);

   }


   void step_slider::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pitem = hit_test(pmouse, ::user::e_zorder_any);

      auto pwindowimpl = get_window_impl();

      if(pitem == pwindowimpl->m_pitemLButtonDown)
      {

         m_scalar.set(pitem->m_iItem);

      }

   }


   void step_slider::on_message_mouse_move(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      SetTimer(1, 200_ms, nullptr);

      m_pitemHover = __new(::item(::e_element_client));

      //update_hover();

   }


   void step_slider::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      

      if(m_scalar.is_null())
         return;

      ::rectangle_i32 rectangleClient;
      client_rectangle(rectangleClient);

      byte bAlpha = (byte) (128.0 * get_alpha());

      pgraphics->fill_rectangle(rectangleClient, argb(bAlpha, 150, 200, 255));

      i64 iMin = m_scalar.minimum().get_i64();
      i64 iMax = m_scalar.maximum().get_i64();
      i64 iVal = m_scalar.get().get_i64();

      ::rectangle_i32 rectangle;
      for(i64 i = iMin; i <= iMax; i++)
      {
         GetStepRect(&rectangle, i, iMin, iMax, rectangleClient);
         if(i == iVal)
         {
            
            if(m_pitemHover->item_index() == i)
            {

               pgraphics->fill_rectangle(rectangle, argb(bAlpha, 255, 255, 240));

            }
            else
            {
               
               pgraphics->fill_rectangle(rectangle, argb(bAlpha, 255, 255, 150));
               
            }
            
         }
         else
         {
         
            if(::is_item(m_pitemHover, i))
            {
               
               pgraphics->fill_rectangle(rectangle, argb(bAlpha, 255, 180, 180));
               
            }
            else
            {
               
               pgraphics->fill_rectangle(rectangle, argb(bAlpha, 100, 100, 255));
               
            }
            
         }
         
      }
      
   }


   void step_slider::GetStepHoverRect(::rectangle_i32 * prectangle, i64 iStep, i64 iMin, i64 iMax, const ::rectangle_i32 & rectangleClient)
   {

      if((iMax - iMin) == 0)
         return;

      prectangle->top = rectangleClient.top;

      prectangle->bottom = rectangleClient.bottom;

      double dWidth = ((double)rectangleClient.width()) / (iMax - iMin);

      prectangle->left = (::i32) (dWidth * (iStep - iMin));

      prectangle->right = (::i32) (dWidth * (iStep - iMin + 1));



   }


   void step_slider::GetStepRect(::rectangle_i32 * prectangle, i64 iStep, i64 iMin, i64 iMax, const ::rectangle_i32 & rectangleClient)
   {

      if((iMax - iMin) == 0)
         return;

      GetStepHoverRect(prectangle, iStep, iMin, iMax, rectangleClient);

      i32 halfm = (prectangle->right - prectangle->left - 2) / 2;

      prectangle->left +=  halfm;

      prectangle->right -=  halfm;


   }


   ::item_pointer step_slider::on_hit_test(const ::point_i32 &point, ::user::e_zorder ezorder)
   {

      ::rectangle_i32 rectangleClient;

      client_rectangle(rectangleClient);

      if (rectangleClient.width() == 0)
      {

         auto pitemNone = __new(::item(e_element_none));

         return pitemNone;

      }

      i64 iMin, iMax;

      iMin = m_scalar.minimum().get_i64();

      iMax = m_scalar.maximum().get_i64();

      return __new(::item((index) (iMin + (((point.x() - rectangleClient.left) * (iMax - iMin)) / rectangleClient.width()))));

   }


//   void step_slider::update_hover()
//   {
//
//      auto pwindow = window();
//
//      auto pointCursor = pwindow->get_cursor_position();
//
//      m_pitemHover = hit_test(pointCursor);
//
//      set_need_redraw();
//
//      ::rectangle_i32 rectangleClient;
//
//      client_rectangle(rectangleClient);
//
//      if (rectangleClient.contains(pointCursor))
//      {
//
//         m_pitemHover = __new(::item(e_element_client));
//
//      }
//      else
//      {
//
//         m_pitemHover = nullptr;
//
//      }
//
//   }


} // namespace user
