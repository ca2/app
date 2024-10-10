//
// Created by camilo on 2024-09-27 16:52 <3ThomasBorregaardSorensen!!
//
#pragma once


inline ::rectangle_i32 & copy(::rectangle_i32 & rectangle, const QRect &qrect)
{

   rectangle.left() = qrect.left();
   rectangle.top() = qrect.top();
   rectangle.right() = qrect.right();
   rectangle.bottom() = qrect.bottom();

   return rectangle;

}



