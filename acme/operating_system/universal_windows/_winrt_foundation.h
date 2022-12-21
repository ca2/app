// Created by camilo on 2022-09-23 01:15 <3ThomasBorregaardSorensen!!
#pragma once



#include <winrt/Windows.Foundation.h>

inline winrt::hstring __hstring(const ::scoped_string & scopedstr)
{

   wstring wstr(psz);

   return wstr.c_str();

}

inline ::winrt::Windows::Foundation::Rect ScaleRect(::winrt::Windows::Foundation::Rect rectangle, double scale)
{

   rectangle.X = (float)(rectangle.X * scale);
   rectangle.Y = (float)(rectangle.Y * scale);
   rectangle.Width = (float)(rectangle.Width * scale);
   rectangle.Height = (float)(rectangle.Height * scale);

   return rectangle;

}

