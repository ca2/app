// Created by camilo on 2022-09-23 01:15 <3ThomasBorregaardSorensen!!
#pragma once



#include <winrt/Windows.Foundation.h>

inline winrt::hstring as_hstring(const ::scoped_string & scopedstr)
{

   wstring wstr(scopedstr);

   return wstr.c_str();

}


inline ::winrt::Windows::Foundation::Rect ScaleRect(::winrt::Windows::Foundation::Rect rectangle, ::f64 scale)
{

   rectangle.X = (::f32)(rectangle.X * scale);
   rectangle.Y = (::f32)(rectangle.Y * scale);
   rectangle.Width = (::f32)(rectangle.Width * scale);
   rectangle.Height = (::f32)(rectangle.Height * scale);

   return rectangle;

}

