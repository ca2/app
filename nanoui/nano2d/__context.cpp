// Created by camilo on 2022/03/18 9:00 AM <3ThomasBorregaardSorensen!! (Thomas Like number 5)
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


   void context::path_winding(::i32 dir)
   {


   }


   void context::close_path()
   {


   }


   void context::translate(::f32 x, ::f32 y)
   {



   }


   void context::rotate(::f32 angle)
   {



   }


   void context::rounded_rect(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::f32 r)
   {



   }


   void context::fill()
   {


   }


   void context::stroke()
   {


   }


   ::nano2d::paint context::linear_gradient(::f32 sx, ::f32 sy, ::f32 ex, ::f32 ey,
      ::nano2d::color icol, ::nano2d::color ocol)
   {

      return {};

   }


   ::nano2d::paint context::box_gradient(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::f32 r, ::f32 f,
      ::nano2d::color icol, ::nano2d::color ocol)
   {

      return {};

   }


   ::nano2d::paint context::radial_gradient(::f32 cx, ::f32 cy, ::f32 inr, ::f32 outr,
      ::nano2d::color icol, ::nano2d::color ocol)
   {

      return {};

   }


   ::nano2d::paint context::image_pattern(::f32 cx, ::f32 cy, ::f32 w, ::f32 h, ::f32 angle,
      ::i32 image, ::f32 alpha)
   {

      return {};

   }



   void context::font_face(const_char_pointer face)
   {


   }


   void context::font_size(::f32 size)
   {



   }


   void context::font_blur(::f32 blur)
   {



   }


//   ::write_text::font_pointer context::create_font(const_char_pointer face, ::f32 size)
//   {
//      
//      return nullptr;
//      
//   }


   void context::fill_color(::nano2d::color color)
   {

   }


   void context::fill_paint(::nano2d::paint paint)
   {

   }


   void context::stroke_paint(::nano2d::paint paint)
   {


   }


   void context::scissor(::f32 x, ::f32 y, ::f32 w, ::f32 h)
   {

   }


   void context::intersect_scissor(::f32 x, ::f32 y, ::f32 w, ::f32 h)
   {


   }


   void context::reset_scissor()
   {


   }


   void context::stroke_color(::nano2d::color color)
   {



   }


   void context::global_alpha(::f32 alpha)
   {

   }


   void context::stroke_width(::f32 width)
   {



   }


   void context::text_align(::i32 align)
   {


   }


   ::f32 context::text(::f32 x, ::f32 y, const_char_pointer string, const_char_pointer end)
   {

      return 0.f;

   }


   ::i32 context::text_glyph_positions(::f32 x, ::f32 y, const_char_pointer string, const_char_pointer end, ::nano2d::glyphPosition * positions, ::i32 maxPositions)
   {

      return 0;

   }


   ::f32 context::text_bounds(::f32 x, ::f32 y, const_char_pointer string, const_char_pointer end, ::f32 * bounds)
   {

      bounds[0] = 0.f;
      bounds[1] = 0.f;
      bounds[2] = 0.f;
      bounds[3] = 0.f;

      return 0.f;

   }


   void context::text_line_height(::f32 lineHeight)
   {


   }


   void context::move_to(::f32 x, ::f32 y)
   {


   }


   void context::line_to(::f32 x, ::f32 y)
   {


   }


   void context::rect(::f32 x, ::f32 y, ::f32 w, ::f32 h)
   {


   }


   void context::f64_ellipse(::f32 cx, ::f32 cy, ::f32 rx, ::f32 ry)
   {


   }


   void context::circle(::f32 cx, ::f32 cy, ::f32 r)
   {

      ellipse(cx, cy, r, r);

   }


   void context::arc(::f32 cx, ::f32 cy, ::f32 r, ::f32 a0, ::f32 a1, ::i32 dir)
   {


   }


   ::i32 context::create_image(const_char_pointer pszFilename, ::i32 imageFlags)
   {

      return -1;

   }


   ::i32 context::create_image_rgba(::i32 w, ::i32 h, ::i32 imageFlags, const void * data, ::i32 iScan)
   {

      return -1;

   }


   void context::image_size(::i32 image, ::i32 * w, ::i32 * h)
   {


   }


   void context::update_image(::i32 image, const void * data)
   {


   }


   void context::_draw_image(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::image::image *pimage)
   {


   }


} // namespace nano2d




