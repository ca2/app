#include "framework.h"
#include "file_application.h"
#include "audio/audio.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "aqua/platform/system.h"


namespace multimedia
{


   file_application::file_application()
   {

   }


   file_application::~file_application()
   {

   }


   file_pointer file_application::get_file(::payload payloadFile, const ::file::e_open & eopen)
   {

      file_pointer spfile;

      string strPath;

      if (payloadFile.get_type() == ::e_type_string)
      {
         
         strPath = payloadFile;

         strPath.trim("\"'");

      }


#ifndef _UWP

      if (::str().begins_ci(strPath, "rtp://") || ::str().begins_ci(strPath, "rtprx://"))
      {

         auto psystem = get_system()->m_paquasystem;

         return psystem->audio()->get_rtp_file(strPath);

      }

#endif

      auto pcontext = get_context();

      return pcontext->m_papexcontext->file()->get_file(payloadFile, eopen);

   }


} // namespace multimedia



