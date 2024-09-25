//
// Created by camilo on 31/01/2022 21:27 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "device.h"
#include "acme/primitive/geometry2d/rectangle.h"
//#include "acme/primitive/collection/string_array.h"
namespace nano
{
   
   namespace user
   {
      

device::device()
{


}


device::~device()
{


}


void device::on_begin_draw()
{


}


void device::on_end_draw()
{


}


void device::draw_text123(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::user::brush * pnanobrushBack, ::nano::user::brush * pnanobrushText, ::nano::user::font * pnanofont)
{

   if(ealign & e_align_bottom_right_bias)
   {

      _draw_text(str, rectangleText, ealign, edrawtext, pnanobrushBack, pnanobrushText, pnanofont);

   }
   else
   {

      string_array straLines;

      straLines.add_lines(str);

      auto r = rectangleText;

      for (auto & strLine: straLines)
      {

         _draw_text(strLine, r, ealign, edrawtext, pnanobrushBack, pnanobrushText, pnanofont);

         auto size = get_text_extents(strLine, pnanofont);

         r.top() += size.cy();

         if (r.top() > rectangleText.bottom())
         {

            break;

         }

      }

   }


}


void device::_draw_text(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::user::brush * pnanobrushBack, ::nano::user::brush * pnanobrushText, ::nano::user::font * pnanofont)
{


}


::size_i32 device::get_text_extents(const ::string & str, ::nano::user::font * pnanofont)
{

   return {};

}



void device::rectangle(const ::rectangle_i32 & rectangle, ::nano::user::brush * pnanobrush, ::nano::user::pen * pnanopen)
{


}

      void device::draw(::nano::user::icon * picon, int x, int y, int cx, int cy)
{


}

   } // namespace user


} // namespace nano


