#include "framework.h"
#include "step_slider.h"
#include "acme/constant/user_message.h"
#include "acme/handler/item.h"
#include "acme/platform/timer.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"
#include "aura/windowing/window.h"


namespace user
{


   step_slider::step_slider()
   {

      //m_iHover = I32_MINIMUM;
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
      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &step_slider::on_message_create);
//      //USER_MESSAGE_LINK(::user::e_message_timer, pchannel, this, &step_slider::on_timer);
      USER_MESSAGE_LINK(::user::e_message_left_button_down, pchannel, this, &step_slider::on_message_left_button_down);
      USER_MESSAGE_LINK(::user::e_message_left_button_up, pchannel, this, &step_slider::on_message_left_button_up);
      USER_MESSAGE_LINK(::user::e_message_mouse_move, pchannel, this, &step_slider::on_message_mouse_move);
   }

   void step_slider::on_message_create(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
//      ::pointer<::message::create>pcreate(pmessage);

   }

   void step_slider::on_timer(::timer * ptimer)
   {
      ::user::interaction::on_timer(ptimer);;
//      if(ptimer->m_uTimer == 1)
//      {
//         if(::is_set(m_pitemHover))
//         {
//            update_hover();
//            if(!::is_set(m_pitemHover))
//               kill_timer(1);
//         }
//      }
   }

   void step_slider::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pwindowimpl = windowing_window();

      pwindowimpl->m_pitemLButtonDown = hit_test(pmouse, ::user::e_zorder_any);

   }


   void step_slider::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pitem = hit_test(pmouse, ::user::e_zorder_any);

      auto pwindowimpl = windowing_window();

      if(pitem == pwindowimpl->m_pitemLButtonDown)
      {

         m_scalar.set(pitem->m_item.m_iItem);

      }

   }


   void step_slider::on_message_mouse_move(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      set_timer(1, 200_ms, nullptr);

      m_pitemHover = øallocate ::item(::e_element_client);

      //update_hover();

   }


   void step_slider::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      

      if(m_scalar.is_null())
         return;

      auto rectangleX = this->rectangle();

      unsigned char bAlpha = (unsigned char) (128.0 * get_alpha());

      pgraphics->fill_rectangle(rectangleX, argb(bAlpha, 150, 200, 255));

      long long iMin = m_scalar.minimum().get_long_long();
      long long iMax = m_scalar.maximum().get_long_long();
      long long iVal = m_scalar.get().get_long_long();

      ::int_rectangle rectangle;
      for(long long i = iMin; i <= iMax; i++)
      {
         GetStepRect(&rectangle, i, iMin, iMax, rectangleX);
         if(i == iVal)
         {
            
            if(m_pitemHover->m_item.m_iItem == i)
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


   void step_slider::GetStepHoverRect(::int_rectangle * prectangle, long long iStep, long long iMin, long long iMax, const ::int_rectangle & rectangleX)
   {

      if((iMax - iMin) == 0)
         return;

      prectangle->top = rectangleX.top;

      prectangle->bottom = rectangleX.bottom;

      double dWidth = ((double)rectangleX.width()) / (iMax - iMin);

      prectangle->left = (int) (dWidth * (iStep - iMin));

      prectangle->right = (int) (dWidth * (iStep - iMin + 1));



   }


   void step_slider::GetStepRect(::int_rectangle * prectangle, long long iStep, long long iMin, long long iMax, const ::int_rectangle & rectangleX)
   {

      if((iMax - iMin) == 0)
         return;

      GetStepHoverRect(prectangle, iStep, iMin, iMax, rectangleX);

      int halfm = (prectangle->right - prectangle->left - 2) / 2;

      prectangle->left +=  halfm;

      prectangle->right -=  halfm;


   }


   ::item_pointer step_slider::on_hit_test(const ::int_point &point, ::user::e_zorder ezorder)
   {

      auto rectangleX = this->rectangle();

      if (rectangleX.width() == 0)
      {

         auto pitemNone = øallocate ::item(e_element_none);

         return pitemNone;

      }

      long long iMin, iMax;

      iMin = m_scalar.minimum().get_long_long();

      iMax = m_scalar.maximum().get_long_long();

      return øallocate ::item(e_element_item, (::collection::index) (iMin + (((point.x - rectangleX.left) * (iMax - iMin)) / rectangleX.width())));

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
//      ::int_rectangle rectangleX;
//
//      this->rectangle(rectangleX);
//
//      if (rectangleX.contains(pointCursor))
//      {
//
//         m_pitemHover = øallocate ::item(e_element_client);
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
