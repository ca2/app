#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


namespace user
{

   picture_interaction::picture_interaction()
   {

   }


   picture_interaction::~picture_interaction()
   {

   }


   void picture_interaction::hit_test(::user::item & item, const ::point_i32 & point)
   {

      if (is_picture_enabled())
      {

         item.m_pointScreen = point;

         auto pointClient = get_parent()->screen_to_client(item.m_pointScreen);

         item.m_pointClient = drag_rtransform(pointClient);

         item.m_pointClient += m_ppictureimpl->m_rectangle.size() / 2;

         item.m_pointHitTest = item.m_pointClient + m_pointScroll;

         on_hit_test(item);

      }
      else
      {

         return ::user::interaction::hit_test(item, point);

      }

   }


   void picture_interaction::on_hit_test(::user::item & item)
   {

      if (is_picture_enabled())
      {

         ::user::picture::on_hit_test(item);

      }
      else
      {

         ::user::interaction::on_hit_test(item);

      }

   }


   ::size_f64 picture_interaction::get_request_size()
   {

      return layout().sketch().size();

   }


} // namespace user



