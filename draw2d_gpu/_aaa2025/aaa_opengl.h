// Created by camilo on 2023-04-27 17:06 <3ThomasBorregaardSorensen!!
#pragma once


#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"

#ifdef WINDOWS_DESKTOP
#define GLAD_GLAPI_EXPORT
#include "glad.h"
#else
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glext.h>
#ifdef LINUX
#include <GL/glx.h>
#endif

#endif

//#include "factory_exchange.h"
//
//
//#include "object.h"
//#include "pen.h"
//#include "bitmap.h"
//#include "brush.h"
//#include "font.h"
//#include "region.h"
//#include "image.h"
//#include "path.h"


#include "../graphics.h"


#define GL2D_GRAPHICS(pgraphics) (dynamic_cast < ::draw2d_gpu::graphics * > (pgraphics))
#define GL2D_HDC(pgraphics) (GL2D_GRAPHICS(pgraphics)->m_hdc)


namespace opengl
{


   //inline void vertex2f(const ::f64_rectangle & rectangle, ::f32 fZ)
   //{

   //   glVertex3f((GLf32)rectangle.left, (GLf32)rectangle.top, fZ);
   //   glVertex3f((GLf32)rectangle.right, (GLf32)rectangle.top, fZ);
   //   glVertex3f((GLf32)rectangle.right, (GLf32)rectangle.bottom, fZ);
   //   glVertex3f((GLf32)rectangle.left, (GLf32)rectangle.bottom, fZ);

   //}

  
      //inline void vertex2f(const ::f64_polygon& a, ::f32 fZ)
      //{
      //   for (auto& p : a)
      //   {

      //      glVertex3f((GLf32)p.x, (GLf32)p.y, fZ);

      //   }

      //}

   void resize(const ::i32_size & size, bool bYSwap);


   //https://community.khronos.org/t/draw-an-arc-in-opengl/57994/2
   void draw_arc(::f32 cx, ::f32 cy, ::f32 r, ::f32 start_angle, ::f32 arc_angle, ::i32 num_segments);

} // namespace opengl



namespace draw2d_gpu
{


   class draw2d;


} // namespace draw2d_gpu



