#include "framework.h"
//#if defined(LINUX)
////#include "base/os/linux/linux_window_xlib.h"
//#elif defined(ANDROID)
////#include "base/os/android/android_window_anative.h"
//#endif

//namespace draw2d_cairo
//{
//
//
//   factory_exchange::factory_exchange()
//   {
//
//      init_cairo_mutex();
//
//      create_factory < image, ::image >();
//      create_factory < pgraphics, ::draw2d::graphics >();
//      create_factory < bitmap, ::draw2d::bitmap >();
//      create_factory < pen, ::draw2d::pen >();
//      create_factory < brush, ::draw2d::brush >();
//      create_factory < palette, ::draw2d::palette >();
//      create_factory < region, ::draw2d::region >();
//      create_factory < font, ::draw2d::font >();
//      create_factory < path, ::draw2d::path >();
//
//      //    #ifdef WINDOWS_DESKTOP
//
////      create_factory < window_gdi      , window_graphics >();
//
//
//   }
//
//
//   factory_exchange::~factory_exchange()
//   {
//
//   }
//
//
//} // namespace win


extern "C"
void factory_exchange()
{
   //draw2d_cairo::factory_exchange factoryexchange;

   init_cairo_mutex();

   create_factory < ::draw2d_cairo::image, ::image >();
   create_factory < ::draw2d_cairo::graphics, ::draw2d::graphics >();
   create_factory < ::draw2d_cairo::bitmap, ::draw2d::bitmap >();
   create_factory < ::draw2d_cairo::pen, ::draw2d::pen >();
   create_factory < ::draw2d_cairo::brush, ::draw2d::brush >();
   create_factory < ::draw2d_cairo::palette, ::draw2d::palette >();
   create_factory < ::draw2d_cairo::region, ::draw2d::region >();
   create_factory < ::draw2d_cairo::font, ::draw2d::font >();
   create_factory < ::draw2d_cairo::path, ::draw2d::path >();
}

extern "C"
void draw2d_factory_exchange()
{

   //draw2d_cairo::factory_exchange factoryexchange;
   factory_exchange();

}




