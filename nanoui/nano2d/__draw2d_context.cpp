// Created by camilo on 2022/03/18 9:00 AM <3ThomasBorregaardSorensen!! (Thomas Like number 5)
#include "framework.h"
#include "draw2d_context.h"
#include "acme/platform/context.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/context_image.h"
#include "aura/graphics/write_text/font.h"


namespace nano2d
{


   draw2d_context::draw2d_context() 
   {

      m_iPaintImageSeed = 1;

   }


   draw2d_context::~draw2d_context()
   {


   }


   void draw2d_context::set_graphics(::draw2d::graphics * pgraphics)
   {

      if (m_pgraphics == pgraphics)
      {

         return;

      }

      m_pgraphics = pgraphics;

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_clear_type_grid_fit);

      _create_new_state();

   }


   ::draw2d::graphics * draw2d_context::get_graphics()
   {

      return m_pgraphics;

   }


   void draw2d_context::set_font_sink(::nano2d::font_sink * pfontsink)
   {
      
      m_pfontsink = pfontsink;
      
   }


   ::nano2d::font_sink * draw2d_context::get_font_sink()
   {
      
      return m_pfontsink;
      
   }


   ::write_text::font_pointer draw2d_context::_get_current_font()
   {

      return m_pfontsink->get_shared_font(m_pstate->m_strFontFace, m_pstate->m_fFontSize);
                                          
   }


   void draw2d_context::_create_new_state()
   {

      m_pstate = __allocate< state >(m_pgraphics);

      m_pstate->initialize(m_pgraphics);

      m_pgraphics->__construct(m_pstate->m_ppen);
      m_pgraphics->__construct(m_pstate->m_pbrush);

      m_pstate->m_ppen->m_epen = ::draw2d::e_pen_solid;
      m_pstate->m_ppen->m_dWidth = 1.0;

      m_pstate->m_pbrush->m_ebrush = ::draw2d::e_brush_solid;

      m_pstate->m_bHasCurrentPoint = false;

   }


   draw2d_context::paint_image & draw2d_context::_create_new_paint_image()
   {

      auto & paintimage = m_mapPaintImage[m_iPaintImageSeed];

      paintimage.m_iImage = m_iPaintImageSeed;

      m_iPaintImageSeed++;

      return paintimage;

   }


   void draw2d_context::save()
   {

      m_pstate->m_matrix = m_pgraphics->m_matrix;


      m_statea.add(m_pstate);

      _create_new_state();

      auto & stateNew = *m_pstate;

      auto & stateOld = *m_statea.last();

      *stateNew.m_ppen = *stateOld.m_ppen;
      *stateNew.m_pbrush = *stateOld.m_pbrush;
      stateNew.m_strFontFace = stateOld.m_strFontFace;
      stateNew.m_fFontSize = stateOld.m_fFontSize;

      stateNew.m_pointCurrent = stateOld.m_pointCurrent;
      stateNew.m_bHasCurrentPoint = stateOld.m_bHasCurrentPoint;
      stateNew.m_ealignText = stateOld.m_ealignText;


      if (stateOld.m_ppath)
      {

         m_pgraphics->__construct(stateNew.m_ppath);

         *stateNew.m_ppath = *stateOld.m_ppath;

      }

      

   }


   void draw2d_context::restore()
   {

      m_pstate = m_statea.pop();

      //m_pgraphics->reset_clip();

      m_pgraphics->set(m_pstate->m_matrix);

   }


   void draw2d_context::begin_path()
   {

      m_pgraphics->__construct(m_pstate->m_ppath);

      m_pstate->m_ppath->begin_figure();
   
   }


   void draw2d_context::path_winding(int dir)
   {

      if (m_pstate->m_ppath)
      {

         m_pstate->m_ppath->set_fill_mode(
            dir == ::nano2d::e_solidity_solid ?
            ::draw2d::e_fill_mode_winding
            : ::draw2d::e_fill_mode_alternate);

      }
      else
      {

         m_pgraphics->set_fill_mode(dir == ::nano2d::e_solidity_solid ?
            ::draw2d::e_fill_mode_winding
            : ::draw2d::e_fill_mode_alternate);

      }

   }


   void draw2d_context::close_path()
   {

      if (m_pstate->m_ppath)
      {

         m_pstate->m_ppath->close_figure();

      }
      else
      {

         m_pgraphics->close_figure();

      }

   }


   void draw2d_context::translate(float x, float y)
   {

      ::geometry2d::matrix matrix;

      matrix.translate(x, y);

      m_pgraphics->prepend(matrix);

   }


   void draw2d_context::rotate(float angle)
   {

      ::geometry2d::matrix matrix;

      matrix.rotate(angle);

      m_pgraphics->prepend(matrix);

   }
   
   
   void draw2d_context::rounded_rect(float xParam, float yParam, float wParam, float hParam, float rParam)
   {

      double x = xParam;
      double y = yParam;
      double w = wParam;
      double h = hParam;
      double r = rParam;

      auto r2 = r * 2.0;

      if (r2 > w || r2 > h)
      {

         return;

      }

      m_pstate->m_ppath->add_round_rectangle({ x, y, x + w, y + h }, r);

   }


   void draw2d_context::fill()
   {

      if (m_iPaint >= 0)
      {

         auto & paintimage = m_mapPaintImage[m_iPaint];

         if (paintimage.m_pbrush)
         {

            m_pgraphics->set(paintimage.m_pbrush);

            m_pgraphics->fill(m_pstate->m_ppath);


         }
         else if (paintimage.m_pimage)
         {

            ::draw2d::save_context savecontext(m_pgraphics);

            m_pgraphics->intersect_clip(m_pstate->m_ppath);

            image_source imagesource(paintimage.m_pimage);

            image_drawing imagedrawing(paintimage.m_imagedrawingoptions, imagesource);

            m_pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            m_pgraphics->set_compositing_quality(::draw2d::e_compositing_quality_high_quality);

            m_pgraphics->draw(imagedrawing);

         }

         m_iPaint = -1;

      }
      else
      {

         m_pgraphics->set(m_pstate->m_pbrush);

         m_pgraphics->fill(m_pstate->m_ppath);

      }

   }


   void draw2d_context::stroke()
   {

      m_pgraphics->set(m_pstate->m_ppen);

      m_pgraphics->draw(m_pstate->m_ppath);

   }


   ::nano2d::paint draw2d_context::linear_gradient(float sx, float sy, float ex, float ey,
      ::nano2d::color icol, ::nano2d::color ocol)
   {

      auto & paintimage = _create_new_paint_image();

      m_pgraphics->__construct(paintimage.m_pbrush);

      paintimage.m_pbrush->CreateLinearGradientBrush(
         ::point_f64(sx, sy),
         ::point_f64(ex, ey),
         __color(icol),
         __color(ocol));
   
      ::nano2d::paint paint{};
      
      paint.image = paintimage.m_iImage;

      return paint;

   }



   ::nano2d::paint draw2d_context::box_gradient(float x, float y, float w, float h, float r, float f,
      ::nano2d::color icol, ::nano2d::color ocol)
   {

      auto & paintimage = _create_new_paint_image();

      m_pgraphics->__construct(paintimage.m_pbrush);

      paintimage.m_pbrush->CreateBoxGradientBrush(
         ::point_f64(x, y),
         ::point_f64(w, h),
         r,
         __color(icol),
         __color(ocol));

      ::nano2d::paint paint{};

      paint.image = paintimage.m_iImage;

      return paint;

   }


   ::nano2d::paint draw2d_context::radial_gradient(float cx, float cy, float inr, float outr,
      ::nano2d::color icol, ::nano2d::color ocol)
   {

      auto & paintimage = _create_new_paint_image();

      m_pgraphics->__construct(paintimage.m_pbrush);

      paintimage.m_pbrush->CreateRadialGradientBrush(
         ::point_f64(cx - inr, cy - outr),
         ::size_f64(inr * 2.0f, outr * 2.0f),
         __color(icol),
         __color(ocol));

      ::nano2d::paint paint{};

      paint.image = paintimage.m_iImage;

      return paint;

   }



   ::nano2d::paint draw2d_context::image_pattern(float cx, float cy, float w, float h, float angle,
      int image, float alpha)

   {

      if (image <= 0)
      {

         return {};

      }

      auto pimage = m_pgraphics->m_pcontext->context_image()->integer_image(image);

      auto & paintimage = _create_new_paint_image();

      //m_pgraphics->__construct(paintimage.m_pbrush);

      //paintimage.m_pbrush->CreatePatternBrush(
      //   pimage,
      //   ::size_f64(w, h));

      

      ::rectangle_f64 rectangleTarget(::point_f64(cx, cy), ::size_f64(w, h));

      ::image_drawing_options imagedrawingoptions(rectangleTarget);

      imagedrawingoptions.opacity(alpha);

      paintimage.m_imagedrawingoptions = imagedrawingoptions;

      paintimage.m_pimage = pimage;

      ::nano2d::paint paint{};

      paint.image = paintimage.m_iImage;

      return paint;

   }


   void draw2d_context::font_face(const char * face)
   {

      m_pstate->m_strFontFace = face;
      
   }


   void draw2d_context::font_size(float size)
   {

      m_pstate->m_fFontSize = size;

   }


   void __font_face(::write_text::font * pfont, const char * font)
   {

      string strFont(font);

      if (strFont.case_insensitive_order("sans-bold") == 0)
      {

         pfont->m_path = "matter://font/truetype/Roboto-Bold.ttf";

         pfont->m_iFontWeight = 800;

         pfont->set_modified();

      }
      else if (strFont.case_insensitive_order("sans") == 0)
      {

         pfont->m_path = "matter://font/truetype/Roboto-Regular.ttf";

         pfont->m_iFontWeight = 400;

         pfont->set_modified();

      }
      else if (strFont.case_insensitive_order("mono") == 0)
      {

         pfont->m_path = "matter://font/truetype/Inconsolata-Regular.ttf";

         pfont->m_iFontWeight = 400;

         pfont->set_modified();

      }
      else if (strFont.case_insensitive_order("icons") == 0)
      {

         pfont->m_path = "matter://font/truetype/FontAwesome-Solid.ttf";

         pfont->m_iFontWeight = 400;

         pfont->set_modified();

      }
      else
      {

         pfont->m_strFontFamilyName = strFont;

         pfont->m_iFontWeight = 400;

         pfont->set_modified();

      }

   }


   void __font_size(::write_text::font * pfont, float size)
   {

      pfont->m_dFontSize = size * 0.8;
      pfont->m_eunitFontSize = ::draw2d::e_unit_pixel;
      pfont->set_modified();

   }


   void draw2d_context::fill_color(::nano2d::color color)
   {

      m_pstate->m_pbrush->m_ebrush = ::draw2d::e_brush_solid;

      m_pstate->m_pbrush->m_color = __color(color);

      m_pstate->m_pbrush->set_modified();

   }


   void draw2d_context::fill_paint(::nano2d::paint paint)
   {

      if (paint.image <= 0 || paint.image >= m_iPaintImageSeed)
      {

         return;

      }

      ASSERT(paint.image >= 0 && paint.image < m_iPaintImageSeed);

      m_iPaint = paint.image;


   }


   void draw2d_context::stroke_paint(::nano2d::paint paint)
   {

      ASSERT(paint.image >= 0 && paint.image < m_iPaintImageSeed);

      auto & paintimage = m_mapPaintImage[paint.image];

      if (paintimage.m_pbrush)
      {

         m_pstate->m_ppen->m_pbrush = paintimage.m_pbrush;

         m_pstate->m_ppen->set_modified();

         m_pgraphics->draw(m_pstate->m_ppath, m_pstate->m_ppen);


      }
      //else if (paintimage.m_pimage)
      //{

      //   ::draw2d::save_context savecontext(m_pgraphics);

      //   m_pgraphics->intersect_clip(m_pstate->m_ppath);

      //   image_source imagesource(paintimage.m_pimage);

      //   image_drawing imagedrawing(paintimage.m_imagedrawingoptions, imagesource);

      //   m_pgraphics->draw(imagedrawing);

      //}

   }

   void draw2d_context::scissor(float x, float y, float w, float h)
   {

      auto r = rectangle_f64_dimension(x, y, w, h);

      m_pgraphics->reset_clip();

      m_pgraphics->intersect_clip(r);

   }


   void draw2d_context::intersect_scissor(float x, float y, float w, float h)
   {

      auto r = rectangle_f64_dimension(x, y, w, h);

      m_pgraphics->intersect_clip(r);

   }


   void draw2d_context::reset_scissor()
   {

      m_pgraphics->reset_clip();

   }


   void draw2d_context::stroke_color(::nano2d::color color)
   {

      m_pstate->m_ppen->m_color = __color(color);

      m_pstate->m_ppen->set_modified();

   }


   void draw2d_context::stroke_width(float width)
   {
  

      m_pstate->m_ppen->m_dWidth = width;

      m_pstate->m_ppen->set_modified();


   }


   void draw2d_context::text_align(int align)
   {

      m_pstate->m_ealignText = e_align_none;

      if (align & ::nano2d::e_align_center)
      {

         m_pstate->m_ealignText |= ::e_align_horizontal_center;


      }
      else if (align & ::nano2d::e_align_right)
      {

         m_pstate->m_ealignText |=::e_align_right;

      }
      else
      {

         m_pstate->m_ealignText |= ::e_align_left;

      }

      if (align & ::nano2d::e_align_middle)
      {

         m_pstate->m_ealignText |= ::e_align_vertical_center;


      }
      else if (align & ::nano2d::e_align_top)
      {

         m_pstate->m_ealignText |= ::e_align_top;

      }
      else
      {

         m_pstate->m_ealignText |= ::e_align_bottom;

      }

   }


   float draw2d_context::text(float x, float y, const char * string, const char * end)
   {
      
      ::string strText(string, end ? end - string : string_safe_length(string));

      m_pgraphics->set(_get_current_font());

      m_pgraphics->set(m_pstate->m_pbrush);

      double offsetx = 0.0;

      double offsety = 0.0;

      auto size = m_pgraphics->get_text_extent(strText);

      if (m_pstate->m_ealignText & ::e_align_right)
      {

         offsetx = -size.cx();

      }
      else if (m_pstate->m_ealignText & ::e_align_horizontal_center)
      {

         offsetx = -size.cx() / 2.0;

      }

      if (m_pstate->m_ealignText & ::e_align_bottom)
      {

         offsety = -size.cy();

      }
      else if (m_pstate->m_ealignText & ::e_align_vertical_center)
      {

         offsety = -size.cy() / 2.0;

      }
      
      m_pgraphics->text_out({ (double)x + offsetx, (double)y + offsety }, strText);

      return (float) (x + offsetx + size.cx());

   }


   int draw2d_context::text_glyph_positions(float x, float y, const char * stringParam, const char * end, ::nano2d::glyphPosition * positions, int maxPositions)
   {

      f64_array daLeft;
      f64_array daRight;

      ::string strText(stringParam, end ? end - stringParam : string_safe_length(stringParam));

      m_pgraphics->set(_get_current_font());

      auto size = m_pgraphics->get_text_extent(strText);
      double offsetx = 0.0;

      double offsety = 0.0;

      if (m_pstate->m_ealignText & ::e_align_right)
      {

         offsetx = -size.cx();

      }
      else if (m_pstate->m_ealignText & ::e_align_horizontal_center)
      {

         offsetx = -size.cx() / 2.0;

      }

      if (m_pstate->m_ealignText & ::e_align_bottom)
      {

         offsety = -size.cy();

      }
      else if (m_pstate->m_ealignText & ::e_align_vertical_center)
      {

         offsety = -size.cy() / 2.0;

      }


      m_pgraphics->get_character_extent(daLeft, daRight, strText);

      auto pszStart = strText.c_str();

      auto psz = pszStart;

      int iChar = 0;

      while (*psz && iChar < maxPositions)
      {

         int iLen = get_utf8_char_length(psz);

         positions[iChar].str = psz;

         positions[iChar].x() = (float) (x+ offsetx+daLeft[psz - pszStart]);

         positions[iChar].minx = (float) (x + offsetx + daLeft[psz - pszStart]);

         positions[iChar].maxx = (float) (x + offsetx + daRight[psz - pszStart]);

         psz += iLen;

         iChar++;

      }

      return iChar;

   }



   float draw2d_context::text_bounds(float x, float y, const char * string, const char * end, float * bounds)
   {

      ::string strText(string, end ? end - string : string_safe_length(string));
      
      auto pfont = _get_current_font();

      m_pgraphics->set(pfont);

      auto size = m_pgraphics->get_text_extent(strText);
      double offsetx = 0.0;

      double offsety = 0.0;

      if (m_pstate->m_ealignText & ::e_align_right)
      {

         offsetx = -size.cx();

      }
      else if (m_pstate->m_ealignText & ::e_align_horizontal_center)
      {

         offsetx = -size.cx() / 2.0;

      }

      if (m_pstate->m_ealignText & ::e_align_bottom)
      {

         offsety = -size.cy();

      }
      else if (m_pstate->m_ealignText & ::e_align_vertical_center)
      {

         offsety = -size.cy() / 2.0;

      }

      if (bounds)
      {

         bounds[0] = (float) (x + offsetx);
         bounds[1] = (float) (y + offsety);
         bounds[2] = (float) (x + offsetx + size.cx());
         bounds[3] = (float) (y + offsety + size.cy());

      }

      return (float) (x + offsetx + size.cx());

   }


   void draw2d_context::move_to(float x, float y)
   {

      if (m_pstate->m_ppath)
      {

         m_pstate->m_ppath->set_current_point(::point_f64(x, y));

      }
      else
      {

         m_pgraphics->set_current_point(::point_f64(x, y));

      }

   }


   void draw2d_context::line_to(float x, float y)
   {
      
      if (m_pstate->m_ppath)
      {

         m_pstate->m_ppath->add_line(::point_f64(x, y));

      }
      else
      {

         m_pgraphics->line_to(::point_f64(x, y));

      }

   }


   void draw2d_context::rect(float x, float y, float w, float h)
   {

      if (m_pstate->m_ppath)
      {

         m_pstate->m_ppath->add_rectangle(rectangle_f64_dimension(x, y, w, h));

      }
      else
      {

         m_pgraphics->rectangle(rectangle_f64_dimension(x, y, w, h));

      }

   }


   void draw2d_context::ellipse_f64(float cx, float cy, float rx, float ry)
   {

      if (m_pstate->m_ppath)
      {

         m_pstate->m_ppath->add_ellipse(rectangle_f64_dimension(cx - rx, cy - ry, rx *2.0, ry*2.0));

      }
      else
      {

         m_pgraphics->ellipse(rectangle_f64_dimension(cx - rx, cy - ry, rx * 2.0, ry * 2.0));

      }

   }


   void draw2d_context::arc(float cx, float cy, float r, float a0, float a1, int dir)
   {

      if (m_pstate->m_ppath)
      {

         m_pstate->m_ppath->add_arc(rectangle_f64_dimension(cx - r, cy - r, r * 2.0, r * 2.0), a0, dir ? a1 - a0 : a0 - a1);

      }
      else
      {

         m_pgraphics->arc(rectangle_f64_dimension(cx - r, cy - r, r * 2.0, r * 2.0), a0, dir ? a1 - a0 : a0 - a1);

      }

   }


   int draw2d_context::create_image(const char * filename, int imageFlags)
   {

      return m_pgraphics->m_pcontext->context_image()->image_integer(filename);

   }


   int draw2d_context::create_image_rgba(int w, int h, int imageFlags, const void * data, int iScan)
   {

      return m_pgraphics->m_pcontext->context_image()->create_image_integer(w, h, (const ::color32_t *)data, iScan);

   }


   void draw2d_context::image_size(int image, int * w, int * h)
   {

      if (image <= 0)
      {

         *w = 0;
         *h = 0;

         return;


      }
      
      auto pimage = m_pgraphics->m_pcontext->context_image()->integer_image(image);

      if (::is_null(pimage))
      {

         *w = 0;
         *h = 0;

         return;

      }

      *w = pimage->width();

      *h = pimage->height();

   }


   void draw2d_context::update_image(int image, const void * data)
   {

      if (image <= 0)
      {

         return;

      }

      auto pgraphics = m_pgraphics;

      auto pcontext = pgraphics->m_pcontext;

      auto pcontextimage = pcontext->context_image();

      auto pimage = pcontextimage->integer_image(image);

      pimage->map();

      copy_image32(pimage->get_data(), pimage->width(), pimage->height(), pimage->m_iScan, (const color32_t *)data);

   }


   void draw2d_context::_draw_image(float x, float y, float w, float h, ::image * pimage)
   {

      ::rectangle_f64 rectangleTarget(x, y, x + w, y + h);

      image_source imagesource(pimage);

      image_drawing_options imagedrawingoptions(rectangleTarget);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      m_pgraphics->set_compositing_quality(::draw2d::e_compositing_quality_high_quality);

      m_pgraphics->draw(imagedrawing);


   }


} // namespace draw2d



