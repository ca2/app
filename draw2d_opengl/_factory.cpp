#include "framework.h"
#include "image.h"
#include "graphics.h"
#include "bitmap.h"
#include "pen.h"
#include "brush.h"
#include "region.h"
#include "font.h"
#include "path.h"


__FACTORY_EXPORT void draw2d_opengl_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::draw2d_opengl::image, ::image >();
   pfactory->add_factory_item < ::draw2d_opengl::graphics, ::draw2d::graphics >();
   pfactory->add_factory_item < ::draw2d_opengl::bitmap, ::draw2d::bitmap >();
   pfactory->add_factory_item < ::draw2d_opengl::pen, ::draw2d::pen >();
   pfactory->add_factory_item < ::draw2d_opengl::brush, ::draw2d::brush >();
   pfactory->add_factory_item < ::draw2d_opengl::region, ::draw2d::region >();
   pfactory->add_factory_item < ::draw2d_opengl::font, ::write_text::font >();
   pfactory->add_factory_item < ::draw2d_opengl::path, ::draw2d::path >();

}



