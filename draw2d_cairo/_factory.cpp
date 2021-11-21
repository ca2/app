#include "framework.h"


__FACTORY_EXPORT void draw2d_cairo_factory(::factory::factory * pfactory)
{

   init_cairo_mutex();

   pfactory->add_factory_item < ::draw2d_cairo::image, ::image >();
   pfactory->add_factory_item < ::draw2d_cairo::graphics, ::draw2d::graphics >();
   pfactory->add_factory_item < ::draw2d_cairo::bitmap, ::draw2d::bitmap >();
   pfactory->add_factory_item < ::draw2d_cairo::pen, ::draw2d::pen >();
   pfactory->add_factory_item < ::draw2d_cairo::brush, ::draw2d::brush >();
   pfactory->add_factory_item < ::draw2d_cairo::palette, ::draw2d::palette >();
   pfactory->add_factory_item < ::draw2d_cairo::region, ::draw2d::region >();
   pfactory->add_factory_item < ::draw2d_cairo::font, ::write_text::font >();
   pfactory->add_factory_item < ::draw2d_cairo::path, ::draw2d::path >();

   pfactory->add_factory_item < ::draw2d_cairo::draw2d, ::draw2d::draw2d >();


}



