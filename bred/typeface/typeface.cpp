// Created by camilo on 2026-01-06 21:11 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "typeface.h"


namespace typeface
{


   typeface::typeface() 
   {
      
   }


   typeface::~typeface()
   {
      
      
   }


   ::file::path typeface::get_font_file_path_by_font_name(const ::scoped_string & scopedstr)
   {

      auto path = _get_font_file_path_by_font_name(scopedstr);

      if (path.is_empty())
      {

         path = "matter://font/truetype/Roboto-Regular.ttf";

      }

      return path;


   }


   ::file::path typeface::_get_font_file_path_by_font_name(const ::scoped_string & scopedstr)
   {

      throw ::interface_only();

      return {};

   }


} // namespace typeface



