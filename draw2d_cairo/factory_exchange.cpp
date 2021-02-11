#include "framework.h"


extern "C"
void draw2d_cairo_factory_exchange()
{

   init_cairo_mutex();

   create_factory < ::draw2d_cairo::image, ::image >();
   create_factory < ::draw2d_cairo::graphics, ::draw2d::graphics >();
   create_factory < ::draw2d_cairo::bitmap, ::draw2d::bitmap >();
   create_factory < ::draw2d_cairo::pen, ::draw2d::pen >();
   create_factory < ::draw2d_cairo::brush, ::draw2d::brush >();
   create_factory < ::draw2d_cairo::palette, ::draw2d::palette >();
   create_factory < ::draw2d_cairo::region, ::draw2d::region >();
   create_factory < ::draw2d_cairo::font, ::write_text::font >();
   create_factory < ::draw2d_cairo::path, ::draw2d::path >();
}



