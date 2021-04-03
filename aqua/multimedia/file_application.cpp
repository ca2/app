#include "framework.h"


namespace multimedia
{


   file_application::file_application()
   {

   }


   file_application::~file_application()
   {

   }


   file_pointer file_application::get_file(::payload varFile, const ::file::e_open & eopen)
   {

      file_pointer spfile;

      string strPath;

      if (varFile.get_type() == ::e_type_string)
      {
         
         strPath = varFile;

         strPath.trim("\"'");

      }


#ifndef _UWP

      if (::str::begins_ci(strPath, "rtp://") || ::str::begins_ci(strPath, "rtprx://"))
      {

         __pointer(::aqua::system) psystem = get_system();

         return psystem->audio()->get_rtp_file(strPath);

      }

#endif

      auto pcontext = get_context();

      return pcontext->m_papexcontext->file().get_file(varFile, eopen);

   }


} // namespace multimedia



