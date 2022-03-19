#pragma once


namespace draw2d
{


   class NVGcontext :
      virtual public ::NVGcontext
   {
   public:


      ::draw2d::graphics_pointer & m_pgraphics;


      ::draw2d::brush_pointer m_pbrush;
      ::write_text::font_pointer m_pfont;

      ::e_align  m_ealignText;


      NVGcontext(::draw2d::graphics_pointer & pgraphics);
      virtual ~NVGcontext();


      void font_face(const char * font) override;
      void font_size(float size) override;
      void fill_color(NVGcolor color) override;
      void text_align(int align) override;
      float text(float x, float y, const char * string, const char * end) override;
      float text_bounds(float x, float y, const char * string, const char * end, float * bounds) override;


   };


} // namespace draw2d



