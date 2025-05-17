#include "framework.h"
#include "_vulkan.h"
#include "image.h"
#include "graphics.h"
#include "bitmap.h"
#include "pen.h"
#include "brush.h"
#include "region.h"
#include "font.h"
#include "path.h"
#include "draw2d.h"


__FACTORY_EXPORT void draw2d_vulkan_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::draw2d_vulkan::image, ::image::image >();
   pfactory->add_factory_item < ::draw2d_vulkan::graphics, ::draw2d::graphics >();
   pfactory->add_factory_item < ::draw2d_vulkan::bitmap, ::draw2d::bitmap >();
   pfactory->add_factory_item < ::draw2d_vulkan::pen, ::draw2d::pen >();
   pfactory->add_factory_item < ::draw2d_vulkan::brush, ::draw2d::brush >();
   pfactory->add_factory_item < ::draw2d_vulkan::region, ::draw2d::region >();
   pfactory->add_factory_item < ::draw2d_vulkan::font, ::write_text::font >();
   pfactory->add_factory_item < ::draw2d_vulkan::path, ::draw2d::path >();


   pfactory->add_factory_item < ::draw2d_vulkan::draw2d, ::draw2d::draw2d >();

}



