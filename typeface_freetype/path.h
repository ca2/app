#pragma once


#include "aura/graphics/draw2d/path.h"


namespace typeface_freetype
{


   class CLASS_DECL_TYPEFACE_FREETYPE path :
      virtual public ::draw2d::path
   {
   public:


      bool                       m_bHasPointInternal;
      ::f64_point                   m_pointLast;


      path();
      virtual ~path();


      virtual bool internal_add_arc(const ::i32_rectangle & rectangle, ::f64 iStart, ::f64 iAngle);

      virtual ::f64_point internal_last_point();

      virtual ::f64_point internal_current_point();


      virtual bool internal_begin_figure(bool bFill, ::draw2d::enum_fill_mode efillmode);
      virtual bool internal_end_figure(bool bClose);

      virtual bool internal_add_line(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2);
      virtual bool internal_add_rect(::i32 x,::i32 y,::i32 cx,::i32 cy);
      virtual bool internal_add_line(::i32 x, ::i32 y);
      virtual bool internal_add_move(::i32 x,::i32 y);

      virtual bool internal_add_rect(::f64 x,::f64 y,::f64 cx,::f64 cy);
      virtual bool internal_add_move(::f64 x,::f64 y);

      virtual void destroy() override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::f64_arc& parc) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::f64_line& pline) override;

      //virtual bool _set(::draw2d::graphics* pgraphics, const ::lined& pline) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::f64_lines& pline) override;

      //virtual bool _set(::draw2d::graphics* pgraphics, const ::linesd& pline) override;

      //virtual bool _set(::draw2d::graphics* pgraphics, const ::i32_rectangle& prectangle) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::f64_rectangle& prectangle) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::f64_polygon& ppolygon) override;

      //virtual bool _set(::draw2d::graphics* pgraphics, const ::f64_polygon& ppolygond) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::write_text::text_out& ptextout) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::write_text::draw_text& pdrawtext) override;


   };


} // namespace typeface_freetype




