#include "framework.h"


namespace multimedia
{


   file_application::file_application()
   {

   }


   file_application::~file_application()
   {

   }


   file_pointer file_application::get_file(payload varFile, u32 nOpenFlags)
   {

      file_pointer spfile;

      string strPath;

      if (varFile.get_type() == ::type_string)
      {
         strPath = varFile;
         strPath.trim("\"'");
      }


#ifndef _UWP

      if (::str::begins_ci(strPath, "rtp://") || ::str::begins_ci(strPath, "rtprx://"))
      {

         return Audio.get_rtp_file(strPath);

      }

#endif

      return Context.file().get_file(varFile, nOpenFlags);

   }

} // namespace multimedia



