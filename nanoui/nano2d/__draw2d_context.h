#pragma once


#include "aura/graphics/image/drawing.h"
#include "acme/prototype/collection/integer_map.h"
#include "context.h"
#include "font_sink.h"


namespace nano2d
{


   void __font_face(::write_text::font * pfont, const_char_pointer font);
   void __font_size(::write_text::font * pfont, ::f32 size);


   class CLASS_DECL_NANOUI draw2d_context :
      virtual public ::nano2d::context 
   {
   protected:

      
      ::draw2d::graphics_pointer       m_pgraphics;
      ::pointer<::nano2d::font_sink>  m_pfontsink;
      ::i32                              m_iPaint = -1;

      
   public:


      class state :
         virtual public ::matter,
         public ::draw2d::savedc
      {
      public:

         ::draw2d::pen_pointer         m_ppen;

         ::draw2d::brush_pointer       m_pbrush;

         ::draw2d::path_pointer        m_ppath;

         string                        m_strFontFace;
         ::f32                         m_fFontSize;

         ::e_align                     m_ealignText;

         ::f64_point                   m_pointCurrent;

         ::geometry2d::matrix              m_matrix;

         bool                          m_bHasCurrentPoint;

         state(::draw2d::graphics * pgraphics) :
            savedc(pgraphics)
         {

            m_fFontSize = 0.f;

         }

      };


      class paint_image
      {
      public:

         ::i32                           m_iImage;
         ::draw2d::brush_pointer       m_pbrush;
         ::image::image_pointer               m_pimage;
         ::image::image_drawing_options       m_imagedrawingoptions;

      };


      pointer_array < state >           m_statea;
      ::pointer<state>                m_pstate;
      ::i32                            m_iPaintImageSeed;
      i32_map < paint_image >          m_mapPaintImage;


      draw2d_context();
      ~draw2d_context() override;


      void set_graphics(::draw2d::graphics * pgraphics);
      ::draw2d::graphics * get_graphics();


      void set_font_sink(::nano2d::font_sink * pfontsink);
      ::nano2d::font_sink * get_font_sink();
      
      
      virtual ::write_text::font_pointer _get_current_font();


      virtual void _create_new_state();
      virtual paint_image & _create_new_paint_image();


      void save() override;
      void restore() override;


      void begin_path() override;
      void path_winding(::i32 dir) override;
      void close_path() override;


      void translate(::f32 x, ::f32 y) override;
      void rotate(::f32 angle) override;


      void rounded_rect(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::f32 r) override;


      void fill() override;
      void stroke() override;


      ::nano2d::paint linear_gradient(::f32 sx, ::f32 sy, ::f32 ex, ::f32 ey,
         ::nano2d::color icol, ::nano2d::color ocol) override;
      ::nano2d::paint box_gradient(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::f32 r, ::f32 f,
         ::nano2d::color icol, ::nano2d::color ocol) override;
      ::nano2d::paint radial_gradient(::f32 cx, ::f32 cy, ::f32 inr, ::f32 outr,
         ::nano2d::color icol, ::nano2d::color ocol) override;
      ::nano2d::paint image_pattern(::f32 cx, ::f32 cy, ::f32 w, ::f32 h, ::f32 angle,
         ::i32 image, ::f32 alpha) override;



      void font_face(const_char_pointer font) override;
      void font_size(::f32 size) override;
      void fill_color(::nano2d::color color) override;
      void stroke_width(::f32 width) override;
      void stroke_color(::nano2d::color color) override;
      void text_align(::i32 align) override;


      void fill_paint(::nano2d::paint paint) override;
      void stroke_paint(::nano2d::paint paint) override;


      void scissor(::f32 x, ::f32 y, ::f32 w, ::f32 h) override;
      void intersect_scissor(::f32 x, ::f32 y, ::f32 w, ::f32 h) override;
      void reset_scissor() override;


      ::f32 text(::f32 x, ::f32 y, const_char_pointer string, const_char_pointer end) override;
      ::i32 text_glyph_positions(::f32 x, ::f32 y, const_char_pointer string, const_char_pointer end, ::nano2d::glyphPosition * positions, ::i32 maxPositions) override;
      ::f32 text_bounds(::f32 x, ::f32 y, const_char_pointer string, const_char_pointer end, ::f32 * bounds) override;


      void move_to(::f32 x, ::f32 y) override;
      void line_to(::f32 x, ::f32 y) override;


      void rect(::f32 x, ::f32 y, ::f32 w, ::f32 h) override;
      void ellipse(::f32 cx, ::f32 cy, ::f32 rx, ::f32 ry) override;
      void arc(::f32 cx, ::f32 cy, ::f32 r, ::f32 a0, ::f32 a1, ::i32 dir) override;


      ::i32 create_image(const_char_pointer pszFilename, ::i32 imageFlags) override;
      ::i32 create_image_rgba(::i32 w, ::i32 h, ::i32 imageFlags, const void * data, ::i32 iScan) override;
      void image_size(::i32 image, ::i32 * w, ::i32 * h) override;


      void update_image(::i32 image, const void * data) override;
      void _draw_image(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::image::image *pimage) override;


   };


} // namespace nano2d



