//
// Created by camilo on 2024-09-27 16:52 <3ThomasBorregaardSorensen!!
//
#pragma once


inline ::i32_rectangle & copy(::i32_rectangle & rectangle, const QRect &qrect)
{

   rectangle.left = qrect.left();
   rectangle.top = qrect.top();
   rectangle.right = qrect.right();
   rectangle.bottom = qrect.bottom();

   return rectangle;

}



