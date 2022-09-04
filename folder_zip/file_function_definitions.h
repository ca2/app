// From zip::file(or zip::infile) by camilo on 2021-11-10 15:47 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include <zlib.h>
#include <zutil.h>
#include "ioapi.h"


namespace folder_zip
{


   class CLASS_DECL_FOLDER_ZIP file_function_definitions :
      public zlib_filefunc_def
   {

   public:


      file_function_definitions();

   };


} // namespace folder_zip




