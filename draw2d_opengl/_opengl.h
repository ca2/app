// Created by camilo on 2023-04-27 17:06 <3ThomasBorregaardSorensen!!
#pragma once


#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#define GLAD_GLAPI_EXPORT
#include "glad.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#ifdef LINUX
#include <GL/glx.h>
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


#define GL2D_GRAPHICS(pgraphics) (dynamic_cast < ::draw2d_opengl::graphics * > (pgraphics))
#define GL2D_HDC(pgraphics) (GL2D_GRAPHICS(pgraphics)->m_hdc)


namespace opengl
{


   inline void vertex2f(const ::rectangle_f64 & rectangle)
   {

      glVertex2f((GLfloat)rectangle.left, (GLfloat)rectangle.top);
      glVertex2f((GLfloat)rectangle.right, (GLfloat)rectangle.top);
      glVertex2f((GLfloat)rectangle.right, (GLfloat)rectangle.bottom);
      glVertex2f((GLfloat)rectangle.left, (GLfloat)rectangle.bottom);

   }


   void resize(const ::size_i32 & size);


   //https://community.khronos.org/t/draw-an-arc-in-opengl/57994/2
   void draw_arc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments);

} // namespace opengl



namespace draw2d_opengl
{


   class draw2d;


} // namespace draw2d_opengl



