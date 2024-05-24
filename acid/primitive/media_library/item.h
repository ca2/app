// Created by camilo on 2022-05-28 02:30 <3ThomasBorregaardSorensen
#pragma once


#include "acid/constant/media_library.h"
//#include "acid/primitive/collection/array.h"
////#include "acid/primitive/collection/pointer_array.h"
//#include "acid/primitive/primitive/element.h"


namespace media_library
{




   class CLASS_DECL_ACID item :
      virtual public ::particle
   {
   public:


      virtual ::enum_media_library media_library_type() = 0;
      virtual string get_id() = 0;
      virtual ::file::path get_path();


      virtual ::string get_title();
      virtual ::string get_artist();


      virtual ::string get_display_name();
      virtual ::string get_full_path();
      virtual ::string get_mime_type();


   };

   using item_array = pointer_array < item >;

   using item_map = ::map < enum_media_library, item_array >;

   CLASS_DECL_ACID string media_library_protocol(enum_media_library emedialibrary);


} // namespace media_library



