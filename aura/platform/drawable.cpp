#include "framework.h" // previously aqua/user/user.h
#include "acme/constant/activate.h"
#include "aura/message/user.h"

namespace aura
{


   drawable::drawable()
   {

   }


   drawable::~drawable()
   {

   }


   void drawable::_001OnDraw(::draw2d::graphics_pointer& pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }


   bool drawable::_000OnBeforeDraw(::draw2d::graphics_pointer& pgraphics)
   {

      return true;

   }


   void drawable::hit_test(::user::item& item, const ::point_i32& point)
   {

      UNREFERENCED_PARAMETER(item);
      UNREFERENCED_PARAMETER(point);

   }


   void drawable::on_hit_test(::user::item& item)
   {

      UNREFERENCED_PARAMETER(item);

   }


   //drawable::drawable()
   //{

   //}


   //drawable::~drawable()
   //{

   //}


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




   //bool drawable::_get_client_rect(RECTANGLE_I64 * prectangle)
   //{

   //   __copy(prectangle, get_window_rect64());

   //   screen_to_client(prectangle);

   //   return true;

   //}


   //bool drawable::_get_window_rect(RECTANGLE_I64 * prectangle)
   //{

   //   __copy(prectangle, get_client_rect64());

   //   client_to_screen(prectangle);

   //   return true;

   //}


   ::graphics::graphics* drawable::get_window_graphics()
   {

      return nullptr;

   }


   oswindow drawable::get_oswindow() const
   {

      return nullptr;

   }


   bool drawable::is_composite()
   {
      return false;
   }


   void drawable::hit_test(::user::item& item, ::message::mouse* pmouse)
   {

      hit_test(item, pmouse->m_point);

   }


   ::user::item drawable::hit_test(const ::point_i32& point)
   {

      ::user::item item; hit_test(item, point); return item;

   }


   ::user::item drawable::hit_test(::message::mouse* pmouse)
   {

      return hit_test(pmouse->m_point);

   }


} // namespace aura



