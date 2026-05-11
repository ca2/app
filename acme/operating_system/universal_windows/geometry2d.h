// Created by camilo on 2024-12-29 21:52 <3ThomasBorregaardSørensen!!
#pragma once


inline winrt::Windows::Foundation::Rect as_winrt_windows_foundation_rect(const ::i32_rectangle & rectangle)
{

   winrt::Windows::Foundation::Rect rect;

   rect.X = (float) rectangle.left;
   rect.Y = (float) rectangle.top;
   rect.Width = (float) rectangle.width();
   rect.Height = (float) rectangle.height();

   return rect;

}


inline ::i32_rectangle as_int_rectangle(const ::winrt::Windows::Foundation::Rect & rect)
{

   ::i32_rectangle rectangle;

   rectangle.left = (int)rect.X;
   rectangle.top = (int)rect.Y;
   rectangle.right = (int)(rect.X + rect.Width);
   rectangle.bottom = (int)(rect.Y + rect.Height);

   return rectangle;

}



