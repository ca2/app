#pragma once


#include "aura/graphics/draw2d/path.h"


namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL path :
      virtual public ::draw2d::path
   {
   public:


      bool                       m_bHasPointInternal;
      ::f64_point                   m_pointLast;


      path();
      virtual ~path();


      virtual bool internal_add_arc(const ::i32_rectangle & rectangle, double iStart, double iAngle);

      virtual f64_point internal_last_point();

      virtual f64_point internal_current_point();


      virtual bool internal_begin_figure(bool bFill, ::draw2d::enum_fill_mode efillmode);
      virtual bool internal_end_figure(bool bClose);

      virtual bool internal_add_line(int x1, int y1, int x2, int y2);
      virtual bool internal_add_rect(int x,int y,int cx,int cy);
      virtual bool internal_add_line(int x, int y);
      virtual bool internal_add_move(int x,int y);

      virtual bool internal_add_rect(double x,double y,double cx,double cy);
      virtual bool internal_add_move(double x,double y);

      virtual void destroy() override;

      virtual bool _set(::draw2d::graphics * pdraw2dgraphics, const ::f64_arc& parc) override;

      virtual bool _set(::draw2d::graphics * pdraw2dgraphics, const ::f64_line& pline) override;

      //virtual bool _set(::draw2d::graphics * pdraw2dgraphics, const ::lined& pline) override;

      virtual bool _set(::draw2d::graphics * pdraw2dgraphics, const ::f64_lines& pline) override;

      //virtual bool _set(::draw2d::graphics * pdraw2dgraphics, const ::linesd& pline) override;

      //virtual bool _set(::draw2d::graphics * pdraw2dgraphics, const ::i32_rectangle& prectangle) override;

      virtual bool _set(::draw2d::graphics * pdraw2dgraphics, const ::f64_rectangle& prectangle) override;

      virtual bool _set(::draw2d::graphics * pdraw2dgraphics, const ::f64_polygon& ppolygon) override;

      //virtual bool _set(::draw2d::graphics * pdraw2dgraphics, const ::f64_polygon& ppolygond) override;

      virtual bool _set(::draw2d::graphics * pdraw2dgraphics, const ::write_text::text_out& ptextout) override;

      virtual bool _set(::draw2d::graphics * pdraw2dgraphics, const ::write_text::draw_text& pdrawtext) override;


   };


} // namespace draw2d_opengl




