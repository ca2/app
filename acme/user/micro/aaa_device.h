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


   virtual void draw_text123(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack, ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font  * pnanofont);
   virtual void _draw_text(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack, ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font  * pnanofont);
   virtual ::size_i32 get_text_extents(const ::string & str, ::nano::graphics::font * pnanofont);
   virtual void rectangle(const ::rectangle_i32 & rectangle, ::nano::graphics::brush * pnanobrush, ::nano::graphics::pen * pnanopen);

   virtual void draw(::nano::graphics::icon * picon, int x, int y, int cx, int cy);

   virtual void _on_cairo_paint(void * p);
   //void set_antialias(bool bAntialiasOn);

};


   } // namespace user


} // namespace nano



