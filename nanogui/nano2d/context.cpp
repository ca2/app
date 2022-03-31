// Created by camilo on 2022/03/18 9:00 AM <3ThomasBorregaardSørensen!! (Thomas Like number 5)
#include "framework.h"
#include "context.h"


namespace nano2d
{


   context::context()
   {

      p = this;

   }


   context:: ~context()
   {


   }



   void context::save()
   {


   }


   void context::restore()
   {


   }


   void context::begin_path()
   {


   }


   void context::path_winding(int dir)
   {


   }


   void context::close_path()
   {


   }


   void context::translate(float x, float y)
   {



   }


   void context::rotate(float angle)
   {



   }


   void context::rounded_rect(float x, float y, float w, float h, float r)
   {



   }


   void context::fill()
   {


   }


   void context::stroke()
   {


   }


   NANO2D_PAINT context::linear_gradient(float sx, float sy, float ex, float ey,
      NANO2D_COLOR icol, NANO2D_COLOR ocol)
   {

      return {};

   }


   NANO2D_PAINT context::box_gradient(float x, float y, float w, float h, float r, float f,
      NANO2D_COLOR icol, NANO2D_COLOR ocol)
   {

      return {};

   }


   NANO2D_PAINT context::radial_gradient(float cx, float cy, float inr, float outr,
      NANO2D_COLOR icol, NANO2D_COLOR ocol)
   {

      return {};

   }


   NANO2D_PAINT context::image_pattern(float cx, float cy, float w, float h, float angle,
      int image, float alpha)
   {

      return {};

   }



   void context::font_face(const char * face)
   {


   }


   void context::font_size(float size)
   {



   }


   void context::fill_color(NANO2D_COLOR color)
   {



   }



   void context::fill_paint(NANO2D_PAINT paint)
   {




   }


   void context::stroke_paint(NANO2D_PAINT paint)
   {


   }


   void context::scissor(float x, float y, float w, float h)
   {

   }


   void context::intersect_scissor(float x, float y, float w, float h)
   {


   }


   void context::reset_scissor()
   {


   }


   void context::stroke_color(NANO2D_COLOR color)
   {



   }


   void context::stroke_width(float width)
   {



   }


   void context::text_align(int align)
   {


   }


   float context::text(float x, float y, const char * string, const char * end)
   {

      return 0.f;

   }


   int context::text_glyph_positions(float x, float y, const char * string, const char * end, NVGglyphPosition * positions, int maxPositions)
   {

      return 0;

   }


   float context::text_bounds(float x, float y, const char * string, const char * end, float * bounds)
   {

      bounds[0] = 0.f;
      bounds[1] = 0.f;
      bounds[2] = 0.f;
      bounds[3] = 0.f;

      return 0.f;

   }


   void context::move_to(float x, float y)
   {


   }


   void context::line_to(float x, float y)
   {


   }


   void context::rect(float x, float y, float w, float h)
   {


   }


   void context::ellipse(float cx, float cy, float rx, float ry)
   {


   }


   void context::circle(float cx, float cy, float r)
   {

      ellipse(cx, cy, r, r);

   }


   void context::arc(float cx, float cy, float r, float a0, float a1, int dir)
   {


   }


   int context::create_image(const char * filename, int imageFlags)
   {

      return -1;

   }


   int context::create_image_rgba(int w, int h, int imageFlags, const void * data, int iScan)
   {

      return -1;

   }


   void context::image_size(int image, int * w, int * h)
   {


   }


   void context::update_image(int image, const void * data)
   {


   }


   void context::_draw_image(float x, float y, float w, float h, ::image * pimage)
   {


   }


} // namespace nano2d




