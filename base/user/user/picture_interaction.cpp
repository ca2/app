#include "framework.h"
//#include "base/user/user/_user.h"


namespace user
{

   picture_interaction::picture_interaction()
   {

   }


   picture_interaction::~picture_interaction()
   {

   }


   ::item_pointer picture_interaction::hit_test(const ::point_i32 & point)
   {

      if (is_picture_enabled())
      {

         //item.m_pointScreen = point;

         //auto pointClient = get_parent()->_001ScreenToClient(item.m_pointScreen);

         //item.m_pointClient = drag_rtransform(pointClient);

         //item.m_pointClient += m_ppictureimpl->m_rectangle.size() / 2;

         //item.m_pointHitTest = item.m_pointClient + m_pointScroll;

         return on_hit_test(point);

      }
      else
      {

         return ::user::interaction::hit_test(point);

      }

   }


   ::item_pointer picture_interaction::on_hit_test(const ::point_i32 &point)
   {

      if (is_picture_enabled())
      {

         return ::user::picture::on_hit_test(point);

      }
      else
      {

         return ::user::interaction::on_hit_test(point);

      }

   }


   ::size_f64 picture_interaction::get_request_size()
   {

      return layout().sketch().size();

   }


} // namespace user



