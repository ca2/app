#pragma once


////#include "acme/prototype/prototype/object.h"


namespace multimedia
{


   class CLASS_DECL_AQUA file_application :
      virtual public ::object
   {
   public:


      file_application();
      virtual ~file_application();


      virtual file_pointer get_file(::payload payloadFile, ::file::e_open eopen);


   };


} // namespace multimedia




