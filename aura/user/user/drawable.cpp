#include "framework.h" // previously aqua/user/user.h
#include "drawable.h"
//#include "acme/constant/activate.h"
//#include "aura/message/user.h"


namespace user
{


   drawable::drawable()
   {

   }


   drawable::~drawable()
   {

   }


   void drawable::_001OnDraw(::draw2d::graphics_pointer& pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

   }


   bool drawable::_000OnBeforeDraw(::draw2d::graphics_pointer& pgraphics)
   {

      return true;

   }


   ::item_pointer drawable::hit_test(const ::point_i32& point, e_zorder ezorder)
   {

      __UNREFERENCED_PARAMETER(point);

      return nullptr;

   }


   ::item_pointer drawable::on_hit_test(const ::point_i32 & point, e_zorder ezorder)
   {

      return nullptr;

   }


   void drawable::_000OnDraw(::draw2d::graphics_pointer& pgraphics)
   {

   }


   void drawable::_000CallOnDraw(::draw2d::graphics_pointer& pgraphics)
   {

      _000OnDraw(pgraphics);

   }


   void drawable::_001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer& pgraphics)
   {
   }

   void drawable::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer& pgraphics)
   {
   }




   //bool drawable::_get_client_rect(::rectangle_i64 * prectangle)
   //{

   //   copy(prectangle, get_window_rect64());

   //   screen_to_client(prectangle);

   //   return true;

   //}


   //bool drawable::_get_window_rect(::rectangle_i64 * prectangle)
   //{

   //   copy(prectangle, get_client_rect64());

   //   client_to_screen(prectangle);

   //   return true;

   //}


   ::graphics::graphics* drawable::get_window_graphics()
   {

      return nullptr;

   }


   oswindow drawable::_oswindow() const
   {

      return nullptr;

   }


   bool drawable::is_composite()
   {

      return false;

   }


   item_pointer drawable::hit_test(::user::mouse* pmouse, e_zorder ezorder)
   {

      return nullptr;

      //return hit_test(pmouse->m_point);

   }


   //::item * drawable::hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
   //{

   //   ::item item; hit_test(item, point); return item;

   //}


   //::item * drawable::hit_test(::message::mouse* pmouse)
   //{

   //   return nullptr;

   //   //return hit_test(pmouse->m_point);

   //}


} // namespace user



