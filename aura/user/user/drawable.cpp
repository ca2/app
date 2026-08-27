#include "platform.h" // previously aqua/user/user.h
#include "drawable.h"
#include "acme/exception/interface_only.h"
//#include "aura/message/user.h"


namespace user
{


   drawable::drawable()
   {

   }


   drawable::~drawable()
   {

   }


   void drawable::destroy()
   {

      //::draw2d::host::destroy();

      ::user::acme_container::destroy();


   }


   void drawable::_000DrawImpl(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      __UNREFERENCED_PARAMETER(pdraw2dgraphics);

   }


   void drawable::_001OnDraw(::draw2d::graphics_pointer& pdraw2dgraphics)
   {

      __UNREFERENCED_PARAMETER(pdraw2dgraphics);

   }


   bool drawable::_000OnBeforeDraw(::draw2d::graphics_pointer& pdraw2dgraphics)
   {

      return true;

   }


   ::item_pointer drawable::parent_client_hit_test(const ::i32_point& point, e_zorder ezorder)
   {

      __UNREFERENCED_PARAMETER(point);

      return nullptr;

   }


   ::item_pointer drawable::parent_client_on_hit_test(const ::i32_point & point, e_zorder ezorder)
   {

      return nullptr;

   }


   void drawable::_000OnDraw(::draw2d::graphics_pointer& pdraw2dgraphics)
   {

   }


   void drawable::_000CallOnDraw(::draw2d::graphics_pointer& pdraw2dgraphics)
   {

      _000OnDraw(pdraw2dgraphics);

   }


   void drawable::_001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer& pdraw2dgraphics)
   {
   }

   void drawable::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer& pdraw2dgraphics)
   {
   }




   //bool drawable::_get_client_rect(::i64_rectangle * prectangle)
   //{

   //   copy(prectangle, get_window_rect64());

   //   screen_to_client(prectangle);

   //   return true;

   //}


   //bool drawable::_get_window_rect(::i64_rectangle * prectangle)
   //{

   //   copy(prectangle, get_client_rect64());

   //   client_to_screen(prectangle);

   //   return true;

   //}


   ::graphics::graphics* drawable::get_window_graphics()
   {

      return nullptr;

   }


   // oswindow drawable::_oswindow() const
   // {
   //
   //    return nullptr;
   //
   // }


   bool drawable::is_composite()
   {

      return false;

   }


 /*  ::item_pointer drawable::hit_test(::user::mouse* pmouse, e_zorder ezorder)
   {

      throw ::interface_only();

      return nullptr;

   }*/


   //::item * drawable::hit_test(const ::i32_point & point, ::user::e_zorder ezorder)
   //{

   //   ::item item; hit_test(item, point); return item;

   //}


   //::item * drawable::hit_test(::message::mouse* pmouse)
   //{

   //   return nullptr;

   //   //return hit_test(pmouse->m_point);

   //}

   ::acme::windowing::window * drawable::acme_windowing_window()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::operating_system::window drawable::operating_system_window()
{

   throw ::interface_only();

   return {};

}



} // namespace user



