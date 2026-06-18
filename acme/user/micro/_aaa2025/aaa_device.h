//
// Created by camilo on 31/01/2022 14:35 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/prototype/prototype/particle.h"

namespace nano
{
   
   namespace user
   {
      

class CLASS_DECL_ACME device :
   virtual public ::particle
{
public:


   device();
   ~device() override;


   virtual void on_begin_draw();
   virtual void on_end_draw();


   virtual void draw_text123(const ::scoped_string & scopedstr, const ::i32_rectangle & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack, ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font  * pnanofont);
   virtual void _draw_text(const ::scoped_string & scopedstr, const ::i32_rectangle & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack, ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font  * pnanofont);
   virtual ::i32_size get_text_extents(const ::scoped_string & scopedstr, ::nano::graphics::font * pnanofont);
   virtual void rectangle(const ::i32_rectangle & rectangle, ::nano::graphics::brush * pnanobrush, ::nano::graphics::pen * pnanopen);

   virtual void draw(::nano::graphics::icon * picon, ::i32 x, ::i32 y, ::i32 cx, ::i32 cy);

   virtual void _on_cairo_paint(void * p);
   //void set_antialias(bool bAntialiasOn);

};


   } // namespace user


} // namespace nano



