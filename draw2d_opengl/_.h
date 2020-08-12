#pragma once


#include "aura/_.h"

#include "gl/glew.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#ifdef LINUX
#include <GL/glx.h>
#endif


#ifdef _DRAW2D_OPENGL_STATIC
#define CLASS_DECL_DRAW2D_OPENGL
#elif defined(_DRAW2D_OPENGL_LIBRARY)
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
//#include "palette.h"
#include "region.h"
#include "image.h"
#include "path.h"

//#include "printer.h"


#include "graphics.h"



#define GL2D_GRAPHICS(pgraphics) (dynamic_cast < ::draw2d_opengl::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))
#define GL2D_HDC(pgraphics) ((dynamic_cast < ::draw2d_opengl::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))->m_hdc)


namespace opengl
{


   inline void color(byte r, byte g, byte b, byte a)
   {

      glColor4f(
         (float) r * (float) a / 65355.f, 
         (float) g * (float) a / 65355.f,
         (float) b * (float) a / 65355.f,
         (float) a / 255.f);

   }

   
   inline void color(COLORREF cr)
   {

      ::opengl::color(
         colorref_get_r_value(cr),
         colorref_get_g_value(cr),
         colorref_get_b_value(cr),
         colorref_get_a_value(cr));

   }


   inline void color(const ::color & color)
   {

      ::opengl::color(color.m_iR, color.m_iG, color.m_iB, color.m_iA);

   }


   inline void vertex2f(const ::rectd& rect)
   {

      glVertex2f(rect.left, rect.top);
      glVertex2f(rect.right, rect.top);
      glVertex2f(rect.right, rect.bottom);
      glVertex2f(rect.left, rect.bottom);

   }


   void resize(const ::size& size);


   //https://community.khronos.org/t/draw-an-arc-in-opengl/57994/2
   void draw_arc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments);

} // namespace opengl



