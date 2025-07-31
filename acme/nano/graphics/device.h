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


      class CLASS_DECL_ACME device :
         virtual public ::particle
      {
      public:
         
         
         ::int_size     m_size;


         device();

         ~device() override;

#ifdef HAS_X11
         virtual void create_for_x11(const ::x11::handle_t & handle, int w, int h);
#endif

         virtual void create(int cx, int cy);

         virtual void resize(const ::int_size & size);

         virtual void attach(void * posdata, const ::int_size & size);


         virtual void on_begin_draw();

         virtual void on_end_draw();


         virtual void
         draw_text123(const ::scoped_string & scopedstr, const ::int_rectangle & rectangleText, const ::e_align & ealign,
                      const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack,
                      ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font * pnanofont);

         virtual void _draw_text(const ::scoped_string & scopedstr, const ::int_rectangle & rectangleText, const ::e_align & ealign,
                                 const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack,
                                 ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font * pnanofont);

         virtual ::int_size get_text_extents(const ::scoped_string & scopedstr, ::nano::graphics::font * pnanofont);

         virtual void rectangle(const ::int_rectangle & rectangle, ::nano::graphics::brush * pnanobrush,
                                ::nano::graphics::pen * pnanopen);

         virtual void draw(::nano::graphics::icon * picon, int x, int y, int cx, int cy);

         virtual ::pixmap pixmap();
         //void set_antialias(bool bAntialiasOn);
         
         virtual void translate(int x, int y);
         

      };


   } // namespace graphics


} // namespace nano



