#include "framework.h"
#include "aura/platform/app_core.h"


#ifdef CUBE
void draw2d_factory_exchange()
{
   draw2d_opengl::factory_exchange factoryexchange;
}
#else
extern "C"
void draw2d_factory_exchange()
{

   create_factory < ::draw2d_opengl::image, ::image>();
   create_factory < ::draw2d_opengl::graphics, ::draw2d::graphics>();
   create_factory < ::draw2d_opengl::bitmap, ::draw2d::bitmap>();
   create_factory < ::draw2d_opengl::pen, ::draw2d::pen>();
   create_factory < ::draw2d_opengl::brush, ::draw2d::brush>();
   //create_factory < ::draw2d_opengl::palette              , ::draw2d::palette>();
   create_factory < ::draw2d_opengl::region, ::draw2d::region>();
   create_factory < ::draw2d_opengl::font, ::draw2d::font>();
   create_factory < ::draw2d_opengl::path, ::draw2d::path>();
   //create_factory <::draw2d_opengl:: printer              , ::aura::printer>();
   //create_factory < ::draw2d_opengl::window_opengl        , window_graphics>();
}
#endif


