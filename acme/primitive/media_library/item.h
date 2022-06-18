// Created by camilo on 2022-05-28 02:30 <3ThomasBorregaardS�rensen
#pragma once


#include "acme/constant/media_library.h"


namespace media_library
{


   class CLASS_DECL_ACME item :
      virtual public element
   {
   public:


      virtual ::enum_media_library media_library_type() = 0;
      virtual string get_id() = 0;
      virtual ::file::path get_path();


      /// Attributes
      virtual ::string get_title();
      virtual ::string get_artist();


      virtual ::string get_display_name();
      virtual ::string get_full_path();
      virtual ::string get_mime_type();


   };

   using item_array = __pointer_array(item);

   using item_map = ::map < enum_media_library, item_array >;

   CLASS_DECL_ACME string media_library_protocol(enum_media_library emedialibrary);


} // namespace media_library


