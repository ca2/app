#include "framework.h"
//#include "_opengl.h"
#include "image.h"
#include "graphics.h"
#include "bitmap.h"
#include "pen.h"
#include "brush.h"
#include "region.h"
#include "font.h"
#include "path.h"
#include "draw2d.h"
//#ifdef WINDOWS_DESKTOP
//#include "face_gdiplus.h"
//#else
//#include "face_freetype.h"
//#endif

__FACTORY_EXPORT void draw2d_gpu_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::draw2d_gpu::image, ::image::image >();
   pfactory->add_factory_item < ::draw2d_gpu::graphics, ::draw2d::graphics >();
   pfactory->add_factory_item < ::draw2d_gpu::bitmap, ::draw2d::bitmap >();
   pfactory->add_factory_item < ::draw2d_gpu::pen, ::draw2d::pen >();
   pfactory->add_factory_item < ::draw2d_gpu::brush, ::draw2d::brush >();
   pfactory->add_factory_item < ::draw2d_gpu::region, ::draw2d::region >();
   pfactory->add_factory_item < ::draw2d_gpu::font, ::write_text::font >();
   pfactory->add_factory_item < ::draw2d_gpu::path, ::draw2d::path >();

//#ifdef WINDOWS_DESKTOP
//   pfactory->add_factory_item < ::draw2d_gpu::face_gdiplus, ::draw2d_gpu::face >();
//#else
//   pfactory->add_factory_item < ::draw2d_gpu::face_freetype, ::draw2d_gpu::face >();
//#endif


   pfactory->add_factory_item < ::draw2d_gpu::draw2d, ::draw2d::draw2d >();

}



