#include "framework.h"


__FACTORY_EXPORT void draw2d_opengl_factory(::factory::factory * pfactory)
{

   add_factory_item < ::draw2d_opengl::image, ::image >();
   add_factory_item < ::draw2d_opengl::graphics, ::draw2d::graphics >();
   add_factory_item < ::draw2d_opengl::bitmap, ::draw2d::bitmap >();
   add_factory_item < ::draw2d_opengl::pen, ::draw2d::pen >();
   add_factory_item < ::draw2d_opengl::brush, ::draw2d::brush >();
   add_factory_item < ::draw2d_opengl::region, ::draw2d::region >();
   add_factory_item < ::draw2d_opengl::font, ::write_text::font >();
   add_factory_item < ::draw2d_opengl::path, ::draw2d::path >();

}



