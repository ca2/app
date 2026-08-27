// Created by camilo on 2022/03/18 9:00 AM <3ThomasBorregaardSorensen!! (Thomas Like number 5)
#include "platform.h"
#include "draw2d_context.h"
#include "acme/platform/application.h"
#include "acme/prototype/geometry2d/ellipse.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/write_text/font.h"


namespace nano2d
{


   draw2d_context::draw2d_context(::particle * pparticle) 
   {

      m_bHasCurrentPoint = false;

      initialize(pparticle);

      m_iPaintImageSeed = 1;

   }


   draw2d_context::~draw2d_context()
   {


   }


   void draw2d_context::set_graphics(::draw2d::graphics * pdraw2dgraphics)
   {

      if (m_pdraw2dgraphics == pdraw2dgraphics)
      {

         return;

      }

      m_pdraw2dgraphics = pdraw2dgraphics;

      pdraw2dgraphics->set_text_rendering_hint(::write_text::e_rendering_clear_type_grid_fit);
      
      pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      m_pstate = create_new_state();

   }


   ::draw2d::graphics * draw2d_context::get_graphics()
   {

      return m_pdraw2dgraphics;

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


   ::pointer < ::nano2d::state > draw2d_context::create_new_state()
   {

      auto pstate = allocateø draw2d_state(m_pdraw2dgraphics);

      pstate->initialize(m_pdraw2dgraphics);

      m_pdraw2dgraphics->constructø(pstate->m_pdraw2dpen);
      m_pdraw2dgraphics->constructø(pstate->m_pdraw2dbrush);

      pstate->m_pdraw2dpen->m_epen = ::draw2d::e_pen_solid;
      pstate->m_pdraw2dpen->m_dWidth = 1.0;

      pstate->m_pdraw2dbrush->m_ebrush = ::draw2d::e_brush_solid;

      pstate->m_bHasCurrentPoint = false;

      return pstate;

   }


   draw2d_context::paint_image & draw2d_context::_create_new_paint_image()
   {

      auto & paintimage = m_mapPaintImage[m_iPaintImageSeed];

      paintimage.m_iImage = m_iPaintImageSeed;

      m_iPaintImageSeed++;

      return paintimage;

   }


   void draw2d_context::save1()
   {

      ::pointer < draw2d_state > pstateOld = m_pstate;

      pstateOld->m_matrix = m_pdraw2dgraphics->m_matrix;

      m_statea.add(pstateOld);

      ::pointer < draw2d_state > pstateNew = create_new_state();

      *pstateNew->m_pdraw2dpen            = *pstateOld->m_pdraw2dpen;
      *pstateNew->m_pdraw2dbrush          = *pstateOld->m_pdraw2dbrush;

      pstateNew->m_strFontFace      = pstateOld->m_strFontFace;
      pstateNew->m_fFontSize        = pstateOld->m_fFontSize;

      pstateNew->m_pointCurrent     = pstateOld->m_pointCurrent;
      pstateNew->m_bHasCurrentPoint = pstateOld->m_bHasCurrentPoint;
      pstateNew->m_ealignText       = pstateOld->m_ealignText;
      pstateNew->m_iSavedContext    = m_pdraw2dgraphics->save_graphics_context();

      if (pstateOld->m_pdraw2dpath)
      {

         m_pdraw2dgraphics->constructø(pstateNew->m_pdraw2dpath);

         *pstateNew->m_pdraw2dpath = *pstateOld->m_pdraw2dpath;

      }

      m_pstate = pstateNew;

   }


   void draw2d_context::restore1()
   {

      m_pdraw2dgraphics->restore_graphics_context(m_pstate->m_iSavedContext);

      m_pstate = m_statea.pop();

      m_pdraw2dgraphics->set(m_pstate->m_matrix);

   }


   void draw2d_context::begin_path()
   {
      
      ::pointer < draw2d_state > pstate = m_pstate;

      m_pdraw2dgraphics->constructø(pstate->m_pdraw2dpath);
      
      pstate->m_pdraw2dpath->begin_figure();
   
   }


   void draw2d_context::path_winding(::i32 dir)
   {
      
      ::pointer < draw2d_state > pstate = m_pstate;

      if (pstate->m_pdraw2dpath)
      {

         pstate->m_pdraw2dpath->set_fill_mode(
            dir == ::nano2d::e_solidity_solid ?
            ::draw2d::e_fill_mode_winding
            : ::draw2d::e_fill_mode_alternate);

      }
      else
      {

         m_pdraw2dgraphics->set_fill_mode(dir == ::nano2d::e_solidity_solid ?
            ::draw2d::e_fill_mode_winding
            : ::draw2d::e_fill_mode_alternate);

      }

   }


   void draw2d_context::close_path()

{

      ::pointer < draw2d_state > pstate = m_pstate;

      if (pstate->m_pdraw2dpath)
      {

         pstate->m_pdraw2dpath->close_figure();

      }
      else
      {

         m_pdraw2dgraphics->close_figure();

      }

   }


   void draw2d_context::translate(::f32 x, ::f32 y)
   {

      ::geometry2d::matrix matrix;

      matrix.translate(x, y);

      m_pdraw2dgraphics->prepend(matrix);

   }


   void draw2d_context::rotate(::f32 angle)
   {

      if (::std::isinf(angle))
      {

         return;

      }

      ::geometry2d::matrix matrix;

      matrix.rotate(angle);

      m_pdraw2dgraphics->prepend(matrix);

   }
   
   
   void draw2d_context::rounded_rectangle(::f32 xParam, ::f32 yParam, ::f32 wParam, ::f32 hParam, ::f32 rParam)
   {

      ::f64 x = xParam;
      ::f64 y = yParam;
      ::f64 w = wParam;
      ::f64 h = hParam;
      ::f64 r = rParam;

      auto r2 = r * 2.0;

      if (r2 > w || r2 > h)
      {

         return;

      }

      ::pointer < draw2d_state > pstate = m_pstate;

      
      pstate->m_pdraw2dpath->add_round_rectangle({ x, y, x + w, y + h }, r);

   }


   void draw2d_context::fill()
   {

      if (m_iPaint >= 0)
      {

         auto & paintimage = m_mapPaintImage[m_iPaint];

         if (paintimage.m_pdraw2dbrush)
         {

            m_pdraw2dgraphics->set(paintimage.m_pdraw2dbrush);
            
            ::pointer < draw2d_state > pstate = m_pstate;


            m_pdraw2dgraphics->fill(pstate->m_pdraw2dpath);


         }
         else if (paintimage.m_pimage)
         {

            ::draw2d::save_context savecontext(m_pdraw2dgraphics);
            
            ::pointer < draw2d_state > pstate = m_pstate;

            m_pdraw2dgraphics->intersect_clip(pstate->m_pdraw2dpath);
            
            ::f64_rectangle rect;
            
            m_pdraw2dgraphics->get_clip_box(rect);

            ::image::image_source imagesource(paintimage.m_pimage);

            ::image::image_drawing imagedrawing(paintimage.m_imagedrawingoptions, imagesource);

            m_pdraw2dgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            m_pdraw2dgraphics->set_compositing_quality(::draw2d::e_compositing_quality_high_quality);

            m_pdraw2dgraphics->draw(imagedrawing);

         }

         m_iPaint = -1;

      }
      else
      {

         ::pointer < draw2d_state > pstate = m_pstate;

         m_pdraw2dgraphics->set(pstate->m_pdraw2dbrush);
         
         m_pdraw2dgraphics->fill(pstate->m_pdraw2dpath);

      }

   }


   void draw2d_context::stroke()
   {
      
      ::pointer < draw2d_state > pstate = m_pstate;

      m_pdraw2dgraphics->set(pstate->m_pdraw2dpen);

      m_pdraw2dgraphics->draw(pstate->m_pdraw2dpath);

   }


   ::nano2d::paint draw2d_context::linear_gradient(::f32 sx, ::f32 sy, ::f32 ex, ::f32 ey,
      ::color::color icol, ::color::color ocol)
   {

      auto & paintimage = _create_new_paint_image();

      m_pdraw2dgraphics->constructø(paintimage.m_pdraw2dbrush);

      paintimage.m_pdraw2dbrush->CreateLinearGradientBrush(
         ::f64_point(sx, sy),
         ::f64_point(ex, ey),
         icol,
         ocol);
   
      ::nano2d::paint paint{};
      
      paint.image = paintimage.m_iImage;

      return paint;

   }



   ::nano2d::paint draw2d_context::box_gradient(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::f32 r, ::f32 f,
      ::color::color icol, ::color::color ocol)
   {

      auto & paintimage = _create_new_paint_image();

      m_pdraw2dgraphics->constructø(paintimage.m_pdraw2dbrush);

      paintimage.m_pdraw2dbrush->CreateBoxGradientBrush(
         ::f64_point(x, y),
         ::f64_size(w, h),
         r,
         icol,
         ocol);

      ::nano2d::paint paint{};

      paint.image = paintimage.m_iImage;

      return paint;

   }


   ::nano2d::paint draw2d_context::radial_gradient(::f32 cx, ::f32 cy, ::f32 inr, ::f32 outr,
      ::color::color icol, ::color::color ocol)
   {

      auto & paintimage = _create_new_paint_image();

      m_pdraw2dgraphics->constructø(paintimage.m_pdraw2dbrush);

      paintimage.m_pdraw2dbrush->CreateRadialGradientBrush(
         ::f64_point(cx - inr, cy - outr),
         ::f64_size(inr * 2.0f, outr * 2.0f),
         icol,
         ocol);

      ::nano2d::paint paint{};

      paint.image = paintimage.m_iImage;

      return paint;

   }



   ::nano2d::paint draw2d_context::image_pattern_from_index(::f32 cx, ::f32 cy, ::f32 w, ::f32 h, ::f32 angle, ::f32 alpha, ::i32 iImage)
   {

      if (iImage <= 0)
      {

         return {};

      }

      auto pimage = m_pdraw2dgraphics->image()->integer_image(iImage);

      return image_pattern_from_image(cx, cy, w, h, angle, alpha, pimage);

   }


   ::nano2d::paint draw2d_context::image_pattern_from_image(::f32 cx, ::f32 cy, ::f32 w, ::f32 h, ::f32 angle, ::f32 alpha, ::image::image *pimage)
   {

      auto& paintimage = _create_new_paint_image();

      ::f64_rectangle rectangleTarget(::f64_point(cx, cy), ::f64_size(w, h));

      ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

      imagedrawingoptions.opacity(alpha);

      paintimage.m_imagedrawingoptions = imagedrawingoptions;

      paintimage.m_pimage = pimage;

      ::nano2d::paint paint{};

      paint.image = paintimage.m_iImage;

      return paint;

   }


   void draw2d_context::font_face(const ::scoped_string & scopedstrFace)
   {

      m_pstate->m_strFontFace = scopedstrFace;
      
   }

   void draw2d_context::diacritics(bool b)
   {

      m_pstate->m_bDiacritics = b;

   }


   void draw2d_context::font_size(::f32 size)
   {

      m_pstate->m_fFontSize = size;

   }


   void __font_face(::write_text::font * pwritetextfont, const_char_pointer font)
   {

      string strFont(font);

      if (strFont.case_insensitive_order("sans-bold") == 0)
      {

         pwritetextfont->m_pathFontFile = "matter://font/truetype/Roboto-Bold.ttf";

         pwritetextfont->m_fontweight = e_font_weight_bold;

         pwritetextfont->set_modified();

      }
      else if (strFont.case_insensitive_order("sans") == 0)
      {

         pwritetextfont->m_pathFontFile = "matter://font/truetype/Roboto-Regular.ttf";

         pwritetextfont->m_fontweight = e_font_weight_normal;

         pwritetextfont->set_modified();

      }
      else if (strFont.case_insensitive_order("mono") == 0)
      {

         pwritetextfont->m_pathFontFile = "matter://font/truetype/Inconsolata-Regular.ttf";

         pwritetextfont->m_fontweight = e_font_weight_normal;

         pwritetextfont->set_modified();

      }
      else if (strFont.case_insensitive_order("icons") == 0)
      {

         pwritetextfont->m_pathFontFile = "matter://font/truetype/FontAwesome-Solid.ttf";

         pwritetextfont->m_fontweight = e_font_weight_normal;

         pwritetextfont->set_modified();

      }
      else
      {

         pwritetextfont->m_pfontfamily = strFont;

         pwritetextfont->m_fontweight = e_font_weight_normal;

         pwritetextfont->set_modified();

      }

   }


   void __font_size(::write_text::font * pwritetextfont, ::f32 size)
   {

      pwritetextfont->m_fontsize = size * 0.8_px;
      //pwritetextfont->m_eunitFontSize = ::draw2d::e_unit_pixel;
      pwritetextfont->set_modified();

   }


   void draw2d_context::fill_color(::color::color color)
   {

      
      ::pointer < draw2d_state > pstate = m_pstate;

pstate->m_pdraw2dbrush->m_ebrush = ::draw2d::e_brush_solid;

      pstate->m_pdraw2dbrush->m_color = color;

      pstate->m_pdraw2dbrush->set_modified();
      
      m_iPaint = -1;

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

      if (paintimage.m_pdraw2dbrush)
      {

         ::pointer < draw2d_state > pstate = m_pstate;

         pstate->m_pdraw2dpen->m_pdraw2dbrush = paintimage.m_pdraw2dbrush;

         pstate->m_pdraw2dpen->set_modified();

         m_pdraw2dgraphics->draw(pstate->m_pdraw2dpath, pstate->m_pdraw2dpen);


      }
      //else if (paintimage.m_pimage)
      //{

      //   ::draw2d::save_context savecontext(m_pdraw2dgraphics);

      //   m_pdraw2dgraphics->intersect_clip(m_pstate->m_pdraw2dpath);

      //   ::image::image_source imagesource(paintimage.m_pimage);

      //   ::image::image_drawing imagedrawing(paintimage.m_imagedrawingoptions, imagesource);

      //   m_pdraw2dgraphics->draw(imagedrawing);

      //}

   }

   void draw2d_context::scissor(::f32 x, ::f32 y, ::f32 w, ::f32 h)
   {

      auto r = f64_rectangle_dimension(x, y, w, h);

      m_pdraw2dgraphics->reset_clip();

      m_pdraw2dgraphics->intersect_clip(r);

   }


   void draw2d_context::intersect_scissor(::f32 x, ::f32 y, ::f32 w, ::f32 h)
   {

      auto r = f64_rectangle_dimension(x, y, w, h);

      m_pdraw2dgraphics->intersect_clip(r);

   }


   void draw2d_context::reset_scissor()
   {

      m_pdraw2dgraphics->reset_clip();

   }


   void draw2d_context::stroke_color(::color::color color)
   {

      
      ::pointer < draw2d_state > pstate = m_pstate;

pstate->m_pdraw2dpen->m_color = color;

      pstate->m_pdraw2dpen->set_modified();

   }


   void draw2d_context::stroke_width(::f32 width)
   {
      ::pointer < draw2d_state > pstate = m_pstate;


      pstate->m_pdraw2dpen->m_dWidth = width;

      pstate->m_pdraw2dpen->set_modified();


   }


   void draw2d_context::text_align(::i32 align)
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


   ::f32_rectangle draw2d_context::text(::f32 x, ::f32 y, const ::scoped_string& scopedstr)
   {
      
      //::string strText(string, end ? end - string : string_safe_length(string));

      __set_current_font();
      
      ::pointer < draw2d_state > pstate = m_pstate;

      m_pdraw2dgraphics->set(pstate->m_pdraw2dbrush);

      ::f64 offsetx = 0.0;

      ::f64 offsety = 0.0;

      auto size = m_pdraw2dgraphics->get_text_extent(scopedstr);

      size.cx *= 1.01;
      size.cy *= 1.01;

      if (m_pstate->m_ealignText & ::e_align_right)
      {

         offsetx = -size.cx;

      }
      else if (m_pstate->m_ealignText & ::e_align_horizontal_center)
      {

         offsetx = -size.cx / 2.0;

      }

      if (m_pstate->m_ealignText & ::e_align_bottom)
      {

         offsety = -size.cy;

      }
      else if (m_pstate->m_ealignText & ::e_align_vertical_center)
      {

         offsety = -size.cy / 2.0;

      }

      ::f32_rectangle r;

      r.left = (::f32) ((::f64)x + offsetx);
      r.top = (::f32) ((::f64)y + offsety);
      r.set_size(size);

      auto ealignForDrawText = m_pstate->m_ealignText;
      
      m_pdraw2dgraphics->draw_text(scopedstr, r, ealignForDrawText);

      return r; // it used to return r.right

   }


   ::i32 draw2d_context::text_glyph_positions(::f32 x, ::f32 y, const ::scoped_string& scopedstr, ::nano2d::glyphPosition * positions, ::i32 maxPositions)
   {

      f64_array daLeft;
      f64_array daRight;

      __set_current_font();

      auto size = m_pdraw2dgraphics->get_text_extent(scopedstr);

      ::f64 offsetx = 0.0;

      ::f64 offsety = 0.0;

      if (m_pstate->m_ealignText & ::e_align_right)
      {

         offsetx = -size.cx;

      }
      else if (m_pstate->m_ealignText & ::e_align_horizontal_center)
      {

         offsetx = -size.cx / 2.0;

      }

      if (m_pstate->m_ealignText & ::e_align_bottom)
      {

         offsety = -size.cy;

      }
      else if (m_pstate->m_ealignText & ::e_align_vertical_center)
      {

         offsety = -size.cy / 2.0;

      }


      character_metric(daLeft, daRight, scopedstr);

      const_char_pointer pszStart = scopedstr.begin();

      const_char_pointer psz = pszStart;
       
      const_char_pointer pszEnd = scopedstr.end();

      ::i32 iChar = 0;

      while (psz < pszEnd && iChar < maxPositions)
      {

         ::i32 iLen = get_utf8_char_length(psz);
         
         if(iLen < 0)
         {
            
            break;
            
         }
         
         auto & position = positions[iChar];
         
         auto iIndex = psz - pszStart;
         
         auto dLeft = daLeft[iIndex];
         
         auto dRight = daRight[iIndex];

         position.str = psz;

         position.x = (::f32) (x + offsetx + dLeft);

         position.minx = (::f32) (x + offsetx + dLeft);

         position.maxx = (::f32) (x + offsetx + dRight);

         psz += iLen;

         iChar++;

      }

      return iChar;

   }


   ::f32 draw2d_context::text_bounds(::f32 x, ::f32 y, const ::scoped_string & scopedstr, ::f32_rectangle * bounds)
   {

      //::string strText(string, end ? end - string : string_safe_length(scopedstr));
      
      __set_current_font();

      auto size = m_pdraw2dgraphics->get_text_extent(scopedstr);

      //if (!m_pstate->m_bDiacritics)
      //{

      //   auto tm = m_pdraw2dgraphics->get_text_metrics();

      //   size.cy = tm.m_dAscent;

      //}

      ::f64 offsetx = 0.0;

      ::f64 offsety = 0.0;

      if (m_pstate->m_ealignText & ::e_align_right)
      {

         offsetx = -size.cx;

      }
      else if (m_pstate->m_ealignText & ::e_align_horizontal_center)
      {

         offsetx = -size.cx / 2.0;

      }

      if (m_pstate->m_ealignText & ::e_align_bottom)
      {

         offsety = -size.cy;

      }
      else if (m_pstate->m_ealignText & ::e_align_vertical_center)
      {

         offsety = -size.cy / 2.0;

      }

      if (bounds)
      {

         bounds->left = (::f32) (x + offsetx);
         bounds->top = (::f32) (y + offsety);
         bounds->set_size(size);
         
      }

      return (::f32) (x + offsetx + size.cx);

   }


void draw2d_context::text_metrics(::f32 * pfAscender, ::f32 * pfDescender, ::f32 * pfLineHeight)
{
   
   __set_current_font();
   
   auto textmetrics = m_pdraw2dgraphics->get_text_metrics();
   
   if(pfAscender)
   {
      
      *pfAscender = (::f32) textmetrics.m_dAscent;
      
   }
   
   if(pfDescender)
   {
    
      *pfDescender = (::f32) textmetrics.m_dAscent;
      
   }
   
   if(pfLineHeight)
   {
   
      *pfLineHeight = (::f32) textmetrics.get_line_height();
      
   }

}


   void draw2d_context::move_to(::f32 x, ::f32 y)
   {
      
      ::pointer < draw2d_state > pstate = m_pstate;


      if (pstate->m_pdraw2dpath)
      {

         pstate->m_pdraw2dpath->set_current_point(::f64_point(x, y));

      }
      else
      {

         m_point.x = x;

         m_point.y = y;

         m_bHasCurrentPoint = true;

      }

   }


   void draw2d_context::line_to(::f32 x, ::f32 y)
   {
      
      ::pointer < draw2d_state > pstate = m_pstate;

      
      if (pstate->m_pdraw2dpath)
      {

         pstate->m_pdraw2dpath->add_line(::f64_point(x, y));

      }
      else
      {

         if (!m_bHasCurrentPoint)
         {

            throw ::exception(error_wrong_state);

         }

         m_pdraw2dgraphics->line(m_point.x, m_point.y, x, y);

         m_point.x = x;

         m_point.y = y;

      }

   }


   void draw2d_context::rectangle(::f32 x, ::f32 y, ::f32 w, ::f32 h)
   {
      
      ::pointer < draw2d_state > pstate = m_pstate;


      if (pstate->m_pdraw2dpath)
      {

         pstate->m_pdraw2dpath->add_rectangle(f64_rectangle_dimension(x, y, w, h));

      }
      else
      {

         m_pdraw2dgraphics->rectangle(f64_rectangle_dimension(x, y, w, h));

      }

   }


   void draw2d_context::ellipse(::f32 cx, ::f32 cy, ::f32 rx, ::f32 ry)
   {
      
      ::f64_ellipse ellipse;
      
      ellipse.left = cx - rx;
      ellipse.top = cy - ry;
      ellipse.right = cx + rx;
      ellipse.bottom = cy + ry;
      
      
      ::pointer < draw2d_state > pstate = m_pstate;


      if (pstate->m_pdraw2dpath)
      {

         pstate->m_pdraw2dpath->add_ellipse(ellipse);

      }
      else
      {

         m_pdraw2dgraphics->ellipse(ellipse);

      }

   }


   void draw2d_context::arc(::f32 cx, ::f32 cy, ::f32 r, ::f32_angle a0, ::f32_angle a1, ::i32 dir)
   {
      
      ::f64_rectangle rectangle(cx - r, cy - r, cx + r, cy + r);

      ::pointer < draw2d_state > pstate = m_pstate;

      
      if (pstate->m_pdraw2dpath)
      {

         pstate->m_pdraw2dpath->add_arc(rectangle, a0, dir ? a1 - a0 : a0 - a1);

      }
      else
      {

         m_pdraw2dgraphics->arc(rectangle, a0, dir ? a1 - a0 : a0 - a1);

      }

   }


   void draw2d_context::frame_pixel_perfect_rectangle(::i32 x, ::i32 y, ::i32 w, ::i32 h, const ::color::color& color, ::i32 width)
   {

      m_pdraw2dgraphics->frame_pixel_perfect_rectangle(x, y, w, h, color, width);

   }


   ::i32 draw2d_context::create_image(const ::scoped_string& scopedstrFilename, ::i32 imageFlags)
   {

      return m_pdraw2dgraphics->image()->image_integer(scopedstrFilename);

   }


   ::i32 draw2d_context::create_image_rgba(::i32 w, ::i32 h, ::i32 imageFlags, const void * data, ::i32 iScan)
   {

      return m_pdraw2dgraphics->m_papplication->image()->create_image_integer(w, h, (const ::image32_t *)data, iScan);

   }


   void draw2d_context::image_size(::i32 image, ::i32 * w, ::i32 * h)
   {

      if (image <= 0)
      {

         *w = 0;
         *h = 0;

         return;


      }
      
      auto pimage = m_pdraw2dgraphics->image()->integer_image(image);

      if (::is_null(pimage))
      {

         *w = 0;
         *h = 0;

         return;

      }

      *w = pimage->width();

      *h = pimage->height();

   }


   void draw2d_context::update_image(::i32 image, const void * data)
   {

      if (image <= 0)
      {

         return;

      }

      auto pdraw2dgraphics = m_pdraw2dgraphics;

      auto pimage = ::particle::image()->integer_image(image);

      auto ppixmap = pimage->map();

      ppixmap->copy(pimage->size(), (const image32_t *)data, pimage->m_iScan);

   }


   void draw2d_context::_draw_image(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::image::image *pimage)
   {

      ::f64_rectangle rectangleTarget(x, y, x + w, y + h);

      ::image::image_source imagesource(pimage);

      ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      m_pdraw2dgraphics->set_compositing_quality(::draw2d::e_compositing_quality_high_quality);

      m_pdraw2dgraphics->draw(imagedrawing);


   }


   ::collection::count draw2d_context::character_metric(::f64_array& daLeft, ::f64_array& daRight, const ::scoped_string & scopedstr, character_count iStart, character_count iEnd)
   {

      __set_current_font();

      auto c = m_pdraw2dgraphics->get_character_extent(daLeft, daRight, scopedstr, iStart, iEnd);

      return c;

   }


   void draw2d_context::__set_current_font()
   {

      m_pdraw2dgraphics->set(_get_current_font());

      //auto textmetric = m_pdraw2dgraphics->get_text_metrics();

      m_pstate->lineHeight = 1.0f;

   }


} // namespace draw2d



