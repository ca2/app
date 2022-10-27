//
// Created by camilo on 31/01/2022 21:27 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "device.h"
#include "acme/primitive/collection/string_array.h"


nano_device::nano_device()
{


}


nano_device::~nano_device()
{


}


void nano_device::on_begin_draw()
{


}


void nano_device::on_end_draw()
{


}


void nano_device::draw_text123(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano_brush * pnanobrushBack, ::nano_brush * pnanobrushText, ::nano_font * pnanofont)
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

         r.top += size.cy;

         if (r.top > rectangleText.bottom)
         {

            break;

         }

      }

   }


}


void nano_device::_draw_text(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano_brush * pnanobrushBack, ::nano_brush * pnanobrushText, ::nano_font * pnanofont)
{


}


::size_i32 nano_device::get_text_extents(const ::string & str, ::nano_font * pnanofont)
{

   return {};

}



void nano_device::rectangle(const ::rectangle_i32 & rectangle, ::nano_brush * pnanobrush, ::nano_pen * pnanopen)
{


}

