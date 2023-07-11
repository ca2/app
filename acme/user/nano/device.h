//
// Created by camilo on 31/01/2022 14:35 <3ThomasBorregaardSorensen!!
//
#pragma once


//#include "acme/primitive/geometry2d/_geometry2d.h"



class CLASS_DECL_ACME nano_device :
   virtual public ::particle
{
public:


   nano_device();
   ~nano_device() override;


   virtual void on_begin_draw();
   virtual void on_end_draw();


   virtual void draw_text123(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano_brush * pnanobrushBack, ::nano_brush * pnanobrushText, ::nano_font  * pnanofont);
   virtual void _draw_text(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano_brush * pnanobrushBack, ::nano_brush * pnanobrushText, ::nano_font  * pnanofont);
   virtual ::size_i32 get_text_extents(const ::string & str, ::nano_font * pnanofont);
   virtual void rectangle(const ::rectangle_i32 & rectangle, ::nano_brush * pnanobrush, ::nano_pen * pnanopen);


   //void set_antialias(bool bAntialiasOn);

};




