// Created by camilo on 2022/03/18 9:00 AM <3ThomasBorregaardSorensen!! (Thomas Like number 5)
#include "framework.h"
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


   void draw2d_context::set_graphics(::draw2d::graphics * pgraphics)
   {

      if (m_pgraphics == pgraphics)
      {

         return;

      }

      m_pgraphics = pgraphics;

      pgraphics->set_text_rendering_hint(::write_text::e_rendering_clear_type_grid_fit);
      
      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      m_pstate = create_new_state();

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


   ::pointer < ::nano2d::state > draw2d_context::create_new_state()
   {

      auto pstate = øallocate draw2d_state(m_pgraphics);

      pstate->initialize(m_pgraphics);

      m_pgraphics->øconstruct(pstate->m_ppen);
      m_pgraphics->øconstruct(pstate->m_pbrush);

      pstate->m_ppen->m_epen = ::draw2d::e_pen_solid;
      pstate->m_ppen->m_dWidth = 1.0;

      pstate->m_pbrush->m_ebrush = ::draw2d::e_brush_solid;

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

      pstateOld->m_matrix = m_pgraphics->m_matrix;

      m_statea.add(pstateOld);

      ::pointer < draw2d_state > pstateNew = create_new_state();

      *pstateNew->m_ppen            = *pstateOld->m_ppen;
      *pstateNew->m_pbrush          = *pstateOld->m_pbrush;

      pstateNew->m_strFontFace      = pstateOld->m_strFontFace;
      pstateNew->m_fFontSize        = pstateOld->m_fFontSize;

      pstateNew->m_pointCurrent     = pstateOld->m_pointCurrent;
      pstateNew->m_bHasCurrentPoint = pstateOld->m_bHasCurrentPoint;
      pstateNew->m_ealignText       = pstateOld->m_ealignText;
      pstateNew->m_iSavedContext    = m_pgraphics->save_graphics_context();

      if (pstateOld->m_ppath)
      {

         m_pgraphics->øconstruct(pstateNew->m_ppath);

         *pstateNew->m_ppath = *pstateOld->m_ppath;

      }

      m_pstate = pstateNew;

   }


   void draw2d_context::restore1()
   {

      m_pgraphics->restore_graphics_context(m_pstate->m_iSavedContext);

      m_pstate = m_statea.pop();

      m_pgraphics->set(m_pstate->m_matrix);

   }


   void draw2d_context::begin_path()
   {
      
      ::pointer < draw2d_state > pstate = m_pstate;

      m_pgraphics->øconstruct(pstate->m_ppath);
      
      pstate->m_ppath->begin_figure();
   
   }


   void draw2d_context::path_winding(int dir)
   {
      
      ::pointer < draw2d_state > pstate = m_pstate;

      if (pstate->m_ppath)
      {

         pstate->m_ppath->set_fill_mode(
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

      ::pointer < draw2d_state > pstate = m_pstate;

      if (pstate->m_ppath)
      {

         pstate->m_ppath->close_figure();

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
   
   
   void draw2d_context::rounded_rectangle(float xParam, float yParam, float wParam, float hParam, float rParam)
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

      ::pointer < draw2d_state > pstate = m_pstate;

      
      pstate->m_ppath->add_round_rectangle({ x, y, x + w, y + h }, r);

   }


   void draw2d_context::fill()
   {

      if (m_iPaint >= 0)
      {

         auto & paintimage = m_mapPaintImage[m_iPaint];

         if (paintimage.m_pbrush)
         {

            m_pgraphics->set(paintimage.m_pbrush);
            
            ::pointer < draw2d_state > pstate = m_pstate;


            m_pgraphics->fill(pstate->m_ppath);


         }
         else if (paintimage.m_pimage)
         {

            ::draw2d::save_context savecontext(m_pgraphics);
            
            ::pointer < draw2d_state > pstate = m_pstate;

            m_pgraphics->intersect_clip(pstate->m_ppath);
            
            ::double_rectangle rect;
            
            m_pgraphics->get_clip_box(rect);

            ::image::image_source imagesource(paintimage.m_pimage);

            ::image::image_drawing imagedrawing(paintimage.m_imagedrawingoptions, imagesource);

            m_pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            m_pgraphics->set_compositing_quality(::draw2d::e_compositing_quality_high_quality);

            m_pgraphics->draw(imagedrawing);

         }

         m_iPaint = -1;

      }
      else
      {

         ::pointer < draw2d_state > pstate = m_pstate;

         m_pgraphics->set(pstate->m_pbrush);
         
         m_pgraphics->fill(pstate->m_ppath);

      }

   }


   void draw2d_context::stroke()
   {
      
      ::pointer < draw2d_state > pstate = m_pstate;

      m_pgraphics->set(pstate->m_ppen);

      m_pgraphics->draw(pstate->m_ppath);

   }


   ::nano2d::paint draw2d_context::linear_gradient(float sx, float sy, float ex, float ey,
      ::color::color icol, ::color::color ocol)
   {

      auto & paintimage = _create_new_paint_image();

      m_pgraphics->øconstruct(paintimage.m_pbrush);

      paintimage.m_pbrush->CreateLinearGradientBrush(
         ::double_point(sx, sy),
         ::double_point(ex, ey),
         icol,
         ocol);
   
      ::nano2d::paint paint{};
      
      paint.image = paintimage.m_iImage;

      return paint;

   }



   ::nano2d::paint draw2d_context::box_gradient(float x, float y, float w, float h, float r, float f,
      ::color::color icol, ::color::color ocol)
   {

      auto & paintimage = _create_new_paint_image();

      m_pgraphics->øconstruct(paintimage.m_pbrush);

      paintimage.m_pbrush->CreateBoxGradientBrush(
         ::double_point(x, y),
         ::double_size(w, h),
         r,
         icol,
         ocol);

      ::nano2d::paint paint{};

      paint.image = paintimage.m_iImage;

      return paint;

   }


   ::nano2d::paint draw2d_context::radial_gradient(float cx, float cy, float inr, float outr,
      ::color::color icol, ::color::color ocol)
   {

      auto & paintimage = _create_new_paint_image();

      m_pgraphics->øconstruct(paintimage.m_pbrush);

      paintimage.m_pbrush->CreateRadialGradientBrush(
         ::double_point(cx - inr, cy - outr),
         ::double_size(inr * 2.0f, outr * 2.0f),
         icol,
         ocol);

      ::nano2d::paint paint{};

      paint.image = paintimage.m_iImage;

      return paint;

   }



   ::nano2d::paint draw2d_context::image_pattern_from_index(float cx, float cy, float w, float h, float angle, float alpha, int iImage)
   {

      if (iImage <= 0)
      {

         return {};

      }

      auto pimage = m_pgraphics->image()->integer_image(iImage);

      return image_pattern_from_image(cx, cy, w, h, angle, alpha, pimage);

   }


   ::nano2d::paint draw2d_context::image_pattern_from_image(float cx, float cy, float w, float h, float angle, float alpha, ::image::image *pimage)
   {

      auto& paintimage = _create_new_paint_image();

      ::double_rectangle rectangleTarget(::double_point(cx, cy), ::double_size(w, h));

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


   void draw2d_context::font_size(float size)
   {

      m_pstate->m_fFontSize = size;

   }


   void __font_face(::write_text::font * pfont, const_char_pointer font)
   {

      string strFont(font);

      if (strFont.case_insensitive_order("sans-bold") == 0)
      {

         pfont->m_path = "matter://font/truetype/Roboto-Bold.ttf";

         pfont->m_fontweight = e_font_weight_bold;

         pfont->set_modified();

      }
      else if (strFont.case_insensitive_order("sans") == 0)
      {

         pfont->m_path = "matter://font/truetype/Roboto-Regular.ttf";

         pfont->m_fontweight = e_font_weight_normal;

         pfont->set_modified();

      }
      else if (strFont.case_insensitive_order("mono") == 0)
      {

         pfont->m_path = "matter://font/truetype/Inconsolata-Regular.ttf";

         pfont->m_fontweight = e_font_weight_normal;

         pfont->set_modified();

      }
      else if (strFont.case_insensitive_order("icons") == 0)
      {

         pfont->m_path = "matter://font/truetype/FontAwesome-Solid.ttf";

         pfont->m_fontweight = e_font_weight_normal;

         pfont->set_modified();

      }
      else
      {

         pfont->m_pfontfamily = strFont;

         pfont->m_fontweight = e_font_weight_normal;

         pfont->set_modified();

      }

   }


   void __font_size(::write_text::font * pfont, float size)
   {

      pfont->m_fontsize = size * 0.8_px;
      //pfont->m_eunitFontSize = ::draw2d::e_unit_pixel;
      pfont->set_modified();

   }


   void draw2d_context::fill_color(::color::color color)
   {

      
      ::pointer < draw2d_state > pstate = m_pstate;

pstate->m_pbrush->m_ebrush = ::draw2d::e_brush_solid;

      pstate->m_pbrush->m_color = color;

      pstate->m_pbrush->set_modified();
      
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

      if (paintimage.m_pbrush)
      {

         ::pointer < draw2d_state > pstate = m_pstate;

         pstate->m_ppen->m_pbrush = paintimage.m_pbrush;

         pstate->m_ppen->set_modified();

         m_pgraphics->draw(pstate->m_ppath, pstate->m_ppen);


      }
      //else if (paintimage.m_pimage)
      //{

      //   ::draw2d::save_context savecontext(m_pgraphics);

      //   m_pgraphics->intersect_clip(m_pstate->m_ppath);

      //   ::image::image_source imagesource(paintimage.m_pimage);

      //   ::image::image_drawing imagedrawing(paintimage.m_imagedrawingoptions, imagesource);

      //   m_pgraphics->draw(imagedrawing);

      //}

   }

   void draw2d_context::scissor(float x, float y, float w, float h)
   {

      auto r = double_rectangle_dimension(x, y, w, h);

      m_pgraphics->reset_clip();

      m_pgraphics->intersect_clip(r);

   }


   void draw2d_context::intersect_scissor(float x, float y, float w, float h)
   {

      auto r = double_rectangle_dimension(x, y, w, h);

      m_pgraphics->intersect_clip(r);

   }


   void draw2d_context::reset_scissor()
   {

      m_pgraphics->reset_clip();

   }


   void draw2d_context::stroke_color(::color::color color)
   {

      
      ::pointer < draw2d_state > pstate = m_pstate;

pstate->m_ppen->m_color = color;

      pstate->m_ppen->set_modified();

   }


   void draw2d_context::stroke_width(float width)
   {
      ::pointer < draw2d_state > pstate = m_pstate;


      pstate->m_ppen->m_dWidth = width;

      pstate->m_ppen->set_modified();


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


   ::float_rectangle draw2d_context::text(float x, float y, const ::scoped_string& scopedstr)
   {
      
      //::string strText(string, end ? end - string : string_safe_length(string));

      __set_current_font();
      
      ::pointer < draw2d_state > pstate = m_pstate;

      m_pgraphics->set(pstate->m_pbrush);

      double offsetx = 0.0;

      double offsety = 0.0;

      auto size = m_pgraphics->get_text_extent(scopedstr);

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

      ::float_rectangle r;

      r.left = (float) ((double)x + offsetx);
      r.top = (float) ((double)y + offsety);
      r.set_size(size);

      auto ealignForDrawText = m_pstate->m_ealignText;
      
      m_pgraphics->draw_text(scopedstr, r, ealignForDrawText);

      return r; // it used to return r.right

   }


   int draw2d_context::text_glyph_positions(float x, float y, const ::scoped_string& scopedstr, ::nano2d::glyphPosition * positions, int maxPositions)
   {

      double_array daLeft;
      double_array daRight;

      __set_current_font();

      auto size = m_pgraphics->get_text_extent(scopedstr);

      double offsetx = 0.0;

      double offsety = 0.0;

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

      const char * pszStart = scopedstr.begin();

      const char * psz = pszStart;
       
      const char * pszEnd = scopedstr.end();

      int iChar = 0;

      while (psz < pszEnd && iChar < maxPositions)
      {

         int iLen = get_utf8_char_length(psz);
         
         if(iLen < 0)
         {
            
            break;
            
         }
         
         auto & position = positions[iChar];
         
         auto iIndex = psz - pszStart;
         
         auto dLeft = daLeft[iIndex];
         
         auto dRight = daRight[iIndex];

         position.str = psz;

         position.x = (float) (x + offsetx + dLeft);

         position.minx = (float) (x + offsetx + dLeft);

         position.maxx = (float) (x + offsetx + dRight);

         psz += iLen;

         iChar++;

      }

      return iChar;

   }


   float draw2d_context::text_bounds(float x, float y, const ::scoped_string & scopedstr, ::float_rectangle * bounds)
   {

      //::string strText(string, end ? end - string : string_safe_length(scopedstr));
      
      __set_current_font();

      auto size = m_pgraphics->get_text_extent(scopedstr);

      //if (!m_pstate->m_bDiacritics)
      //{

      //   auto tm = m_pgraphics->get_text_metrics();

      //   size.cy = tm.m_dAscent;

      //}

      double offsetx = 0.0;

      double offsety = 0.0;

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

         bounds->left = (float) (x + offsetx);
         bounds->top = (float) (y + offsety);
         bounds->set_size(size);
         
      }

      return (float) (x + offsetx + size.cx);

   }


void draw2d_context::text_metrics(float * pfAscender, float * pfDescender, float * pfLineHeight)
{
   
   __set_current_font();
   
   auto textmetrics = m_pgraphics->get_text_metrics();
   
   if(pfAscender)
   {
      
      *pfAscender = (float) textmetrics.m_dAscent;
      
   }
   
   if(pfDescender)
   {
    
      *pfDescender = (float) textmetrics.m_dAscent;
      
   }
   
   if(pfLineHeight)
   {
   
      *pfLineHeight = (float) textmetrics.get_line_height();
      
   }

}


   void draw2d_context::move_to(float x, float y)
   {
      
      ::pointer < draw2d_state > pstate = m_pstate;


      if (pstate->m_ppath)
      {

         pstate->m_ppath->set_current_point(::double_point(x, y));

      }
      else
      {

         m_point.x = x;

         m_point.y = y;

         m_bHasCurrentPoint = true;

      }

   }


   void draw2d_context::line_to(float x, float y)
   {
      
      ::pointer < draw2d_state > pstate = m_pstate;

      
      if (pstate->m_ppath)
      {

         pstate->m_ppath->add_line(::double_point(x, y));

      }
      else
      {

         if (!m_bHasCurrentPoint)
         {

            throw ::exception(error_wrong_state);

         }

         m_pgraphics->line(m_point.x, m_point.y, x, y);

         m_point.x = x;

         m_point.y = y;

      }

   }


   void draw2d_context::rectangle(float x, float y, float w, float h)
   {
      
      ::pointer < draw2d_state > pstate = m_pstate;


      if (pstate->m_ppath)
      {

         pstate->m_ppath->add_rectangle(double_rectangle_dimension(x, y, w, h));

      }
      else
      {

         m_pgraphics->rectangle(double_rectangle_dimension(x, y, w, h));

      }

   }


   void draw2d_context::ellipse(float cx, float cy, float rx, float ry)
   {
      
      ::double_ellipse ellipse;
      
      ellipse.left = cx - rx;
      ellipse.top = cy - ry;
      ellipse.right = cx + rx;
      ellipse.bottom = cy + ry;
      
      
      ::pointer < draw2d_state > pstate = m_pstate;


      if (pstate->m_ppath)
      {

         pstate->m_ppath->add_ellipse(ellipse);

      }
      else
      {

         m_pgraphics->ellipse(ellipse);

      }

   }


   void draw2d_context::arc(float cx, float cy, float r, ::float_angle a0, ::float_angle a1, int dir)
   {
      
      ::double_rectangle rectangle(cx - r, cy - r, cx + r, cy + r);

      ::pointer < draw2d_state > pstate = m_pstate;

      
      if (pstate->m_ppath)
      {

         pstate->m_ppath->add_arc(rectangle, a0, dir ? a1 - a0 : a0 - a1);

      }
      else
      {

         m_pgraphics->arc(rectangle, a0, dir ? a1 - a0 : a0 - a1);

      }

   }


   void draw2d_context::frame_pixel_perfect_rectangle(int x, int y, int w, int h, const ::color::color& color, int width)
   {

      m_pgraphics->frame_pixel_perfect_rectangle(x, y, w, h, color, width);

   }


   int draw2d_context::create_image(const ::scoped_string& scopedstrFilename, int imageFlags)
   {

      return m_pgraphics->image()->image_integer(scopedstrFilename);

   }


   int draw2d_context::create_image_rgba(int w, int h, int imageFlags, const void * data, int iScan)
   {

      return m_pgraphics->m_papplication->image()->create_image_integer(w, h, (const ::image32_t *)data, iScan);

   }


   void draw2d_context::image_size(int image, int * w, int * h)
   {

      if (image <= 0)
      {

         *w = 0;
         *h = 0;

         return;


      }
      
      auto pimage = m_pgraphics->image()->integer_image(image);

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

      auto pimage = ::particle::image()->integer_image(image);

      pimage->map();

      pimage->get_data()->copy(pimage->size(), pimage->m_iScan, (const image32_t *)data);

   }


   void draw2d_context::_draw_image(float x, float y, float w, float h, ::image::image *pimage)
   {

      ::double_rectangle rectangleTarget(x, y, x + w, y + h);

      ::image::image_source imagesource(pimage);

      ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      m_pgraphics->set_compositing_quality(::draw2d::e_compositing_quality_high_quality);

      m_pgraphics->draw(imagedrawing);


   }


   ::collection::count draw2d_context::character_metric(::double_array& daLeft, ::double_array& daRight, const ::scoped_string & scopedstr, character_count iStart, character_count iEnd)
   {

      __set_current_font();

      auto c = m_pgraphics->get_character_extent(daLeft, daRight, scopedstr, iStart, iEnd);

      return c;

   }


   void draw2d_context::__set_current_font()
   {

      m_pgraphics->set(_get_current_font());

      //auto textmetric = m_pgraphics->get_text_metrics();

      m_pstate->lineHeight = 1.0f;

   }


} // namespace draw2d



