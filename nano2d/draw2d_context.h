#pragma once


#include "aura/graphics/draw2d/matrix.h"
#include "aura/graphics/image/drawing.h"
#include "acme/primitive/collection/int_map.h"
#include "context.h"
#include "font_sink.h"


namespace nano2d
{


   void __font_face(::write_text::font * pfont, const char * font);
   void __font_size(::write_text::font * pfont, float size);


   class CLASS_DECL_NANO2D draw2d_context :
      virtual public ::nano2d::context
   {
   public:

      
      ::draw2d::graphics_pointer          m_pgraphics;
      ::pointer<::nano2d::font_sink>      m_pfontsink;
      int                                 m_iPaint = -1;



      class state :
         virtual public ::matter
      {
      public:

         ::draw2d::pen_pointer         m_ppen;

         ::draw2d::brush_pointer       m_pbrush;

         ::draw2d::path_pointer        m_ppath;

         ::i32                         m_iSavedContext;

         string                        m_strFontFace;
         float                         m_fFontSize;

         ::e_align                     m_ealignText;

         ::point_f64                   m_pointCurrent;

         ::draw2d::matrix              m_matrix;

         bool                          m_bHasCurrentPoint;

         state(::draw2d::graphics * pgraphics)
         {

            m_fFontSize = 0.f;

         }

      };


      class paint_image
      {
      public:

         int                           m_iImage;
         ::draw2d::brush_pointer       m_pbrush;
         ::image_pointer               m_pimage;
         ::image_drawing_options       m_imagedrawingoptions;

      };


      pointer_array < state >          m_statea;
      ::pointer<state>                 m_pstate;
      ::i32                            m_iPaintImageSeed;
      i32_map < paint_image >          m_mapPaintImage;


      draw2d_context();
      ~draw2d_context() override;


      void set_graphics(::draw2d::graphics * pgraphics);
      ::draw2d::graphics * get_graphics();


      void set_font_sink(::nano2d::font_sink * pfontsink);
      ::nano2d::font_sink * get_font_sink();
      
      
      virtual ::write_text::font_pointer _get_current_font();


      virtual ::pointer < state > create_new_state();
      virtual paint_image & _create_new_paint_image();


      void save1() override;
      void restore1() override;


      void begin_path() override;
      void path_winding(int dir) override;
      void close_path() override;


      void translate(float x, float y) override;
      void rotate(float angle) override;


      void rounded_rectangle(float x, float y, float w, float h, float r) override;


      void fill() override;
      void stroke() override;


      ::nano2d::paint linear_gradient(float sx, float sy, float ex, float ey, ::color::color icol, ::color::color ocol) override;
      ::nano2d::paint box_gradient(float x, float y, float w, float h, float r, float f, ::color::color icol, ::color::color ocol) override;
      ::nano2d::paint radial_gradient(float cx, float cy, float inr, float outr, ::color::color icol, ::color::color ocol) override;
      ::nano2d::paint image_pattern_from_index(float cx, float cy, float w, float h, float angle, float alpha, int iImage) override;
      ::nano2d::paint image_pattern_from_image(float cx, float cy, float w, float h, float angle, float alpha, ::image * pimage) override;



      void font_face(const ::scoped_string & scopedstr) override;
      void font_size(float size) override;
      void fill_color(::color::color color) override;
      void stroke_width(float width) override;
      void stroke_color(::color::color color) override;
      void text_align(int align) override;


      void fill_paint(::nano2d::paint paint) override;
      void stroke_paint(::nano2d::paint paint) override;


      void scissor(float x, float y, float w, float h) override;
      void intersect_scissor(float x, float y, float w, float h) override;
      void reset_scissor() override;


      float text(float x, float y, const ::scoped_string & scopedstr) override;
      int text_glyph_positions(float x, float y, const ::scoped_string & scopedstr, ::nano2d::glyphPosition * positions, int maxPositions) override;
      float text_bounds(float x, float y, const ::scoped_string & scopedstr, float * bounds) override;


      void move_to(float x, float y) override;
      void line_to(float x, float y) override;


      void rectangle(float x, float y, float w, float h) override;
      void ellipse(float cx, float cy, float rx, float ry) override;
      void arc(float cx, float cy, float r, ::angle_f32 a0, ::angle_f32 a1, int dir) override;


      void frame_pixel_perfect_rectangle(int x, int y, int w, int h, const ::color::color& color, int width) override;

      int create_image(const ::scoped_string & scopedstrFilename, int imageFlags) override;
      int create_image_rgba(int w, int h, int imageFlags, const void * data, int iScan) override;
      void image_size(int image, int * w, int * h) override;


      void update_image(int image, const void * data) override;
      void _draw_image(float x, float y, float w, float h, ::image * pimage) override;


   };


} // namespace nano2d



