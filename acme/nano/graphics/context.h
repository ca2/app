//
// Created by camilo on 31/01/2022 14:35 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/operating_system/x11/_.h"
#include "acme/prototype/prototype/particle.h"
#include "acme/prototype/geometry2d/size.h"


namespace nano
{


   namespace graphics
   {


      enum enum_smoothing_mode
      {

         e_smoothing_mode_none,
         e_smoothing_mode_high_quality,

      };

      enum enum_text_rendering_hint
      {

         e_text_rendering_hint_none,
         e_text_rendering_hint_clear_type_grid_fit,

      };


      class CLASS_DECL_ACME context :
         virtual public ::particle
      {
      public:
         
         
         ::i32_size     m_size;


         context();

         ~context() override;


         virtual void set_smoothing_mode(enum_smoothing_mode esmoothingmode);

         virtual void set_text_rendering_hint(enum_text_rendering_hint etextrenderinghint);

         virtual void clear(const ::color::color & color);

#ifdef HAS_X11
         virtual void create_for_x11(const ::x11::handle_t & handle, ::i32 w, ::i32 h);
#endif

         virtual void create(::i32 cx, ::i32 cy);

         virtual void resize(const ::i32_size & size);

         virtual void attach(void * posdata, const ::i32_size & size, ::i32 iType);


         virtual void on_begin_draw();

         virtual void on_end_draw();


         virtual void
         draw_text123(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangleText, const ::e_align & ealign,
                      const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack,
                      ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font * pnanofont);

         virtual void _draw_text(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangleText, const ::e_align & ealign,
                                 const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack,
                                 ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font * pnanofont);

         virtual ::i32_size get_text_extents(const ::scoped_string & scopedstr, ::nano::graphics::font * pnanofont);

         virtual void rectangle(const ::f64_rectangle & rectangle, ::nano::graphics::brush * pnanobrush,
                                ::nano::graphics::pen * pnanopen);

         virtual void draw(::nano::graphics::icon * picon, ::i32 x, ::i32 y, ::i32 cx, ::i32 cy);

         virtual ::pixmap pixmap();
         //void set_antialias(bool bAntialiasOn);
         
         virtual void translate(::f64 x, ::f64 y);

         virtual void fill_path(::nano::graphics::path *ppath, ::nano::graphics::brush *pbrush);

         virtual void draw_path(::nano::graphics::path *ppath, ::nano::graphics::pen *ppen);
         

      };


   } // namespace graphics


} // namespace nano



