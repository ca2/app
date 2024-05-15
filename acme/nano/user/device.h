//
// Created by camilo on 31/01/2022 14:35 <3ThomasBorregaardSorensen!!
//
#pragma once


//#include "acme/primitive/geometry2d/_geometry2d.h"

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


   virtual void draw_text123(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::user::brush * pnanobrushBack, ::nano::user::brush * pnanobrushText, ::nano::user::font  * pnanofont);
   virtual void _draw_text(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::user::brush * pnanobrushBack, ::nano::user::brush * pnanobrushText, ::nano::user::font  * pnanofont);
   virtual ::size_i32 get_text_extents(const ::string & str, ::nano::user::font * pnanofont);
   virtual void rectangle(const ::rectangle_i32 & rectangle, ::nano::user::brush * pnanobrush, ::nano::user::pen * pnanopen);


   //void set_antialias(bool bAntialiasOn);

};


   } // namespace user


} // namespace nano



