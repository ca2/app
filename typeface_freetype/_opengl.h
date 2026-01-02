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


#include "graphics.h"


#define GL2D_GRAPHICS(pgraphics) (dynamic_cast < ::typeface_freetype::graphics * > (pgraphics))
#define GL2D_HDC(pgraphics) (GL2D_GRAPHICS(pgraphics)->m_hdc)


namespace opengl
{


   //inline void vertex2f(const ::double_rectangle & rectangle, float fZ)
   //{

   //   glVertex3f((GLfloat)rectangle.left, (GLfloat)rectangle.top, fZ);
   //   glVertex3f((GLfloat)rectangle.right, (GLfloat)rectangle.top, fZ);
   //   glVertex3f((GLfloat)rectangle.right, (GLfloat)rectangle.bottom, fZ);
   //   glVertex3f((GLfloat)rectangle.left, (GLfloat)rectangle.bottom, fZ);

   //}

  
      //inline void vertex2f(const ::double_polygon& a, float fZ)
      //{
      //   for (auto& p : a)
      //   {

      //      glVertex3f((GLfloat)p.x, (GLfloat)p.y, fZ);

      //   }

      //}

   void resize(const ::int_size & size, bool bYSwap);


   //https://community.khronos.org/t/draw-an-arc-in-opengl/57994/2
   void draw_arc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments);

} // namespace opengl



namespace typeface_freetype
{


   class draw2d;


} // namespace typeface_freetype



