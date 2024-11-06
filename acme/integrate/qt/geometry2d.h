//
// Created by camilo on 2024-09-27 16:52 <3ThomasBorregaardSorensen!!
//
#pragma once


inline ::int_rectangle & copy(::int_rectangle & rectangle, const QRect &qrect)
{

   rectangle.left() = qrect.left();
   rectangle.top() = qrect.top();
   rectangle.right() = qrect.right();
   rectangle.bottom() = qrect.bottom();

   return rectangle;

}



