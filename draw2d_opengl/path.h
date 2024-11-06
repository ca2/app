#pragma once


#include "aura/graphics/draw2d/path.h"


namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL path :
      virtual public ::draw2d::path
   {
   public:


      bool                       m_bHasPointInternal;
      ::point_f64                   m_pointLast;


      path();
      virtual ~path();


      virtual bool internal_add_arc(const ::rectangle_i32 & rectangle, double iStart, double iAngle);

      virtual point_f64 internal_last_point();

      virtual point_f64 internal_current_point();


      virtual bool internal_begin_figure(bool bFill, ::draw2d::enum_fill_mode efillmode);
      virtual bool internal_end_figure(bool bClose);

      virtual bool internal_add_line(int x1, int y1, int x2, int y2);
      virtual bool internal_add_rect(int x,int y,int cx,int cy);
      virtual bool internal_add_line(int x, int y);
      virtual bool internal_add_move(int x,int y);

      virtual bool internal_add_rect(double x,double y,double cx,double cy);
      virtual bool internal_add_move(double x,double y);

      virtual void destroy() override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::arc_f64& parc) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::line_f64& pline) override;

      //virtual bool _set(::draw2d::graphics* pgraphics, const ::lined& pline) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::lines_f64& pline) override;

      //virtual bool _set(::draw2d::graphics* pgraphics, const ::linesd& pline) override;

      //virtual bool _set(::draw2d::graphics* pgraphics, const ::rectangle_i32& prectangle) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::rectangle_f64& prectangle) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::polygon_f64& ppolygon) override;

      //virtual bool _set(::draw2d::graphics* pgraphics, const ::polygon_f64& ppolygond) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::write_text::text_out& ptextout) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::write_text::draw_text& pdrawtext) override;


   };


} // namespace draw2d_opengl




