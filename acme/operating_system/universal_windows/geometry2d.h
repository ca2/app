// Created by camilo on 2024-12-29 21:52 <3ThomasBorregaardSørensen!!
#pragma once


inline winrt::Windows::Foundation::Rect as_winrt_windows_foundation_rect(const ::i32_rectangle & rectangle)
{

   winrt::Windows::Foundation::Rect rect;

   rect.X = (::f32) rectangle.left;
   rect.Y = (::f32) rectangle.top;
   rect.Width = (::f32) rectangle.width();
   rect.Height = (::f32) rectangle.height();

   return rect;

}


inline ::i32_rectangle as_int_rectangle(const ::winrt::Windows::Foundation::Rect & rect)
{

   ::i32_rectangle rectangle;

   rectangle.left = (::i32)rect.X;
   rectangle.top = (::i32)rect.Y;
   rectangle.right = (::i32)(rect.X + rect.Width);
   rectangle.bottom = (::i32)(rect.Y + rect.Height);

   return rectangle;

}



