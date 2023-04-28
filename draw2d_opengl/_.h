#pragma once


#include "aura/_.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#include "gl/glew.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#ifdef LINUX
#include <GL/glx.h>
#endif


#ifdef _DRAW2D_OPENGL_STATIC
#define CLASS_DECL_DRAW2D_OPENGL
#elif defined(_draw2d_opengl_project)
#define CLASS_DECL_DRAW2D_OPENGL  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DRAW2D_OPENGL  CLASS_DECL_IMPORT
#endif


#include "factory_exchange.h"


#include "object.h"
#include "pen.h"
#include "bitmap.h"
#include "brush.h"
#include "font.h"
#include "region.h"
#include "image.h"
#include "path.h"


#include "graphics.h"


#define GL2D_GRAPHICS(pgraphics) (dynamic_cast < ::draw2d_opengl::graphics * > (pgraphics))
#define GL2D_HDC(pgraphics) (GL2D_GRAPHICS(pgraphics)->m_hdc)


namespace opengl
{


   inline void color(byte r, byte g, byte b, byte a)
   {

      //auto fr = (float)r * (float)a / 65355.f;
      //auto fg = (float)g * (float)a / 65355.f;
      //auto fb = (float)b * (float)a / 65355.f;
      auto fr = (float)r / 255.f;
      auto fg = (float)g / 255.f;
      auto fb = (float)b / 255.f;
      auto fa = (float)a / 255.f;

      glColor4f(fr, fg, fb, fa);

   }

   
   inline void color(color32_t color32)
   {

      ::opengl::color(
         colorref_get_r_value(color32),
         colorref_get_g_value(color32),
         colorref_get_b_value(color32),
         colorref_get_a_value(color32));

   }


   inline void color(const ::color::color & color)
   {

      ::opengl::color(color.red, color.green, color.blue, color.alpha);

   }


   inline void vertex2f(const ::rectangle_f64& rectangle)
   {

      glVertex2f(rectangle.left, rectangle.top);
      glVertex2f(rectangle.right, rectangle.top);
      glVertex2f(rectangle.right, rectangle.bottom);
      glVertex2f(rectangle.left, rectangle.bottom);

   }


   void resize(const ::size_i32& size);


   //https://community.khronos.org/t/draw-an-arc-in-opengl/57994/2
   void draw_arc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments);

} // namespace opengl



namespace draw2d_opengl
{


   class draw2d;


} // namespace draw2d_opengl



