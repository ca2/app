#pragma once


#include "acme/prototype/geometry2d/matrix.h"
#include "aura/graphics/image/drawing.h"
#include "acme/prototype/collection/integer_map.h"
#include "context.h"
#include "font_sink.h"


namespace nano2d
{


   void __font_face(::write_text::font * pfont, const_char_pointer font);
   void __font_size(::write_text::font * pfont, ::f32 size);


   class CLASS_DECL_NANO2D draw2d_context :
      virtual public ::nano2d::context 
   {
   public:

      
      ::draw2d::graphics_pointer          m_pgraphics;
      ::pointer<::nano2d::font_sink>      m_pfontsink;
      ::i32                                 m_iPaint = -1;
      bool                                m_bHasCurrentPoint;
      ::f32_point                       m_point;


      class draw2d_state :
         virtual public state
      {
      public:

         ::draw2d::pen_pointer         m_ppen;

         ::draw2d::brush_pointer       m_pbrush;

         ::draw2d::path_pointer        m_ppath;

         draw2d_state(::draw2d::graphics * pgraphics)
         {

            

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


      ::i32                            m_iPaintImageSeed;
      i32_map < paint_image >          m_mapPaintImage;


      draw2d_context(::particle * pparticle);
      ~draw2d_context() override;


      void set_graphics(::draw2d::graphics * pgraphics);
      ::draw2d::graphics * get_graphics();


      void set_font_sink(::nano2d::font_sink * pfontsink);
      ::nano2d::font_sink * get_font_sink();
      
      
      virtual ::write_text::font_pointer _get_current_font();


      virtual ::pointer < ::nano2d::state > create_new_state();
      virtual paint_image & _create_new_paint_image();


      void save1() override;
      void restore1() override;


      void begin_path() override;
      void path_winding(::i32 dir) override;
      void close_path() override;


      void translate(::f32 x, ::f32 y) override;
      void rotate(::f32 angle) override;


      void rounded_rectangle(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::f32 r) override;


      void fill() override;
      void stroke() override;


      ::nano2d::paint linear_gradient(::f32 sx, ::f32 sy, ::f32 ex, ::f32 ey, ::color::color icol, ::color::color ocol) override;
      ::nano2d::paint box_gradient(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::f32 r, ::f32 f, ::color::color icol, ::color::color ocol) override;
      ::nano2d::paint radial_gradient(::f32 cx, ::f32 cy, ::f32 inr, ::f32 outr, ::color::color icol, ::color::color ocol) override;
      ::nano2d::paint image_pattern_from_index(::f32 cx, ::f32 cy, ::f32 w, ::f32 h, ::f32 angle, ::f32 alpha, ::i32 iImage) override;
      ::nano2d::paint image_pattern_from_image(::f32 cx, ::f32 cy, ::f32 w, ::f32 h, ::f32 angle, ::f32 alpha, ::image::image *pimage) override;



      void font_face(const ::scoped_string & scopedstr) override;
      void font_size(::f32 size) override;
      void fill_color(::color::color color) override;
      void stroke_width(::f32 width) override;
      void stroke_color(::color::color color) override;
      void text_align(::i32 align) override;


      void diacritics(bool b) override;


      void fill_paint(::nano2d::paint paint) override;
      void stroke_paint(::nano2d::paint paint) override;


      void scissor(::f32 x, ::f32 y, ::f32 w, ::f32 h) override;
      void intersect_scissor(::f32 x, ::f32 y, ::f32 w, ::f32 h) override;
      void reset_scissor() override;


      ::f32_rectangle text(::f32 x, ::f32 y, const ::scoped_string & scopedstr) override;
      ::i32 text_glyph_positions(::f32 x, ::f32 y, const ::scoped_string & scopedstr, ::nano2d::glyphPosition * positions, ::i32 maxPositions) override;
      ::collection::count character_metric(::f64_array& daLeft, ::f64_array& daRight, const ::scoped_string & scopedstr, character_count iStart = 0, character_count iEnd = -1) override;
      ::f32 text_bounds(::f32 x, ::f32 y, const ::scoped_string & scopedstr, ::f32_rectangle * prectangle) override;
      void text_metrics(::f32 * ascender, ::f32 * descender, ::f32 * lineh) override;

      using ::nano2d::context ::move_to;
      void move_to(::f32 x, ::f32 y) override;
      using ::nano2d::context ::line_to;
      void line_to(::f32 x, ::f32 y) override;




      void rectangle(::f32 x, ::f32 y, ::f32 w, ::f32 h) override;
      void ellipse(::f32 cx, ::f32 cy, ::f32 rx, ::f32 ry) override;
      void arc(::f32 cx, ::f32 cy, ::f32 r, ::f32_angle a0, ::f32_angle a1, ::i32 dir) override;


      void frame_pixel_perfect_rectangle(::i32 x, ::i32 y, ::i32 w, ::i32 h, const ::color::color& color, ::i32 width) override;

      ::i32 create_image(const ::scoped_string & scopedstrFilename, ::i32 imageFlags) override;
      ::i32 create_image_rgba(::i32 w, ::i32 h, ::i32 imageFlags, const void * data, ::i32 iScan) override;
      void image_size(::i32 image, ::i32 * w, ::i32 * h) override;


      void update_image(::i32 image, const void * data) override;
      void _draw_image(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::image::image *pimage) override;


      virtual void __set_current_font();

   };


} // namespace nano2d



