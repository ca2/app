#pragma once


#include "aura/graphics/image/drawing.h"


namespace nano2d
{


   class draw2d_context :
      virtual public ::nano2d::context
   {
   public:


      class state :
         virtual public ::matter,
         public ::draw2d::savedc
      {
      public:

         ::draw2d::pen_pointer         m_ppen;

         ::draw2d::brush_pointer       m_pbrush;

         ::draw2d::path_pointer        m_ppath;

         ::write_text::font_pointer    m_pfont;

         ::e_align                     m_ealignText;

         ::point_f64                   m_pointCurrent;

         ::draw2d::matrix              m_matrix;

         bool                          m_bHasCurrentPoint;

         state(::draw2d::graphics * pgraphics) :
            savedc(pgraphics)
         {


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


      ::draw2d::graphics_pointer &     m_pgraphics;
      __pointer_array(state)           m_statea;
      __pointer(state)                 m_pstate;
      ::i32                            m_iPaintImageSeed;
      i32_map < paint_image >          m_mapPaintImage;


      draw2d_context(::draw2d::graphics_pointer & pgraphics);
      ~draw2d_context() override;


      virtual void _create_new_state();
      virtual paint_image & _create_new_paint_image();


      void save() override;
      void restore() override;


      void begin_path() override;
      void path_winding(int dir) override;
      void close_path() override;


      void translate(float x, float y) override;
      void rotate(float angle) override;


      void rounded_rect(float x, float y, float w, float h, float r) override;


      void fill() override;
      void stroke() override;


      NANO2D_PAINT linear_gradient(float sx, float sy, float ex, float ey,
         NANO2D_COLOR icol, NANO2D_COLOR ocol) override;
      NANO2D_PAINT box_gradient(float x, float y, float w, float h, float r, float f,
         NANO2D_COLOR icol, NANO2D_COLOR ocol) override;
      NANO2D_PAINT radial_gradient(float cx, float cy, float inr, float outr,
         NANO2D_COLOR icol, NANO2D_COLOR ocol);
      NANO2D_PAINT image_pattern(float cx, float cy, float w, float h, float angle,
         int image, float alpha) override;



      void font_face(const char * font) override;
      void font_size(float size) override;
      void fill_color(NANO2D_COLOR color) override;
      void stroke_width(float width) override;
      void stroke_color(NANO2D_COLOR color) override;
      void text_align(int align) override;


      void fill_paint(NANO2D_PAINT paint) override;
      void stroke_paint(NANO2D_PAINT paint) override;


      void scissor(float x, float y, float w, float h) override;
      void intersect_scissor(float x, float y, float w, float h) override;
      void reset_scissor() override;


      float text(float x, float y, const char * string, const char * end) override;
      float text_bounds(float x, float y, const char * string, const char * end, float * bounds) override;


      void move_to(float x, float y) override;
      void line_to(float x, float y) override;


      void rect(float x, float y, float w, float h) override;
      void ellipse(float cx, float cy, float rx, float ry) override;
      void arc(float cx, float cy, float r, float a0, float a1, int dir) override;


      int create_image(const char * filename, int imageFlags) override;
      void image_size(int image, int * w, int * h) override;


      virtual void _draw_image(float x, float y, float w, float h, ::image * pimage);


   };


} // namespace nano2d



