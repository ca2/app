// Created by camilo on 2026-01-06 21:27 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "allocator.h"
#include "typeface_fontconfig.h"
#include "face.h"


namespace typeface_freetype
{


   allocator::allocator() {}


   allocator ::~allocator() {}


   ::pointer<::typeface::typeface> allocator ::create_typeface(const ::scoped_string &scopedstrName)
   {

      if (scopedstrName == "fontconfig" || scopedstrName.is_empty())
      {

         return ::øcreate_new<::typeface_fontconfig::typeface>();

      }
      else
      {

         throw ::exception(error_wrong_state, "not know typeface");

      }

      return {};

   }


   ::pointer<::typeface::face> typeface_factory ::create_face(const ::scoped_string &scopedstrName)
   {

      if (scopedstrName == "freetype" || scopedstrName.is_empty())
      {

         return ::øcreate_new<::typeface_freetype::face>();
      }
      else
      {

         throw ::exception(error_wrong_state, "not know face");
      }


      throw ::interface_only();

      return {};

   }


} // namespace typeface_freetype



