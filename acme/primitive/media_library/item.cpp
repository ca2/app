// Created by camilo on 2022-05-28 02:32 <3ThomasBorregaardSorensen
#include "framework.h"
#include "item.h"
// #include "acme/primitive/string/string.h"
//#include "acme/filesystem/filesystem/path.h"
////#include "acme/exception/exception.h"


namespace media_library
{


   string media_library_protocol(enum_media_library emedialibrary)
   {

      switch (emedialibrary)
      {
      case e_media_library_image:
         return "image://";
      case e_media_library_music:
         return "music://";
      case e_media_library_video:
         return "video://";
      default:
         return "";
      }

   }


   ::file::path item::get_path()
   {

      auto emedialibrary = media_library_type();

      string strMediaLibraryProtocol = media_library_protocol(emedialibrary);

      if (strMediaLibraryProtocol.is_empty())
      {

         throw ::exception(::error_failed, "Unknown media library protocol");

      }

      string strId = get_id();

      ::file::path path;

      path = strMediaLibraryProtocol;

      path /= strId;

      return path;

   }


   ::string item::get_title()
   {

      return "";

   }


   ::string item::get_artist()
   {

      return "";

   }


   ::string item::get_display_name()
   {

      return "";

   }


   ::string item::get_full_path()
   {

      return "";

   }


   ::string item::get_mime_type()
   {

      return "";

   }


} // namespace media_library



