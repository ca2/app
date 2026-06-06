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




      class CLASS_DECL_ACME context :
         virtual public ::particle
      {
      public:
         
         
         ::i32_size     m_size;
         

         context();

         ~context() override;

         
         virtual void set_pen(::nano::graphics::pen * ppen);
         virtual void set_brush(::nano::graphics::brush * pbrush);
         virtual void set_font(::nano::graphics::font * pfont);

         virtual void set_blend_mode(enum_blend_mode eblendmode);
         
         virtual void set_smoothing_mode(enum_smoothing_mode esmoothingmode);

         virtual void set_text_rendering_hint(enum_text_rendering_hint etextrenderinghint);

         virtual void clear(const ::color::color & color);

#ifdef HAS_X11
         virtual void create_for_x11(const ::x11::handle_t & handle, ::i32 w, ::i32 h);
#endif

         virtual void create(const ::i32_size & size);

         virtual void resize(const ::i32_size & size);

         virtual void attach(void * posdata, const ::i32_size & size, ::i32 iType);


         virtual void on_begin_draw();

         virtual void on_end_draw();


         virtual void draw_text123(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext);

         virtual void _draw_text(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext);

         virtual ::f64_size get_text_extents(const ::scoped_string & scopedstr);
         
   
         virtual void rectangle(const ::f64_rectangle & rectangle);
         virtual void ellipse(const ::f64_rectangle &rectangle);
         virtual void line(const ::f64_point &point1, const ::f64_point &point2);

         virtual void draw_icon(::nano::graphics::icon * picon, ::i32 x, ::i32 y, ::i32 cx, ::i32 cy);

         virtual void draw_image(::nano::graphics::image * pimage,const ::f64_rectangle &rectangle);

         virtual void draw_image(::nano::graphics::image * pimage, const ::f64_point & point, const ::f64_rectangle &rectangle);

         virtual ::pixmap pixmap();
         //void set_antialias(bool bAntialiasOn);
         
         virtual void translate(::f64 x, ::f64 y);

         virtual void do_path(::nano::graphics::path *ppath);

//         virtual void draw_path(::nano::graphics::path *ppath, ::nano::graphics::pen *ppen);
         

      };


   } // namespace graphics


} // namespace nano



