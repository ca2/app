#include "framework.h"
#include "file_application.h"
#include "audio/audio.h"
#include "acme/parallelization/event.h"
#include "acme/prototype/string/str.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aqua/platform/system.h"


namespace multimedia
{


   file_application::file_application()
   {

   }


   file_application::~file_application()
   {

   }


   file_pointer file_application::get_file(::payload payloadFile, ::file::e_open eopen)
   {

      file_pointer spfile;

      string strPath;

      if (payloadFile.get_type() == ::e_type_string)
      {
         
         strPath = payloadFile;

         strPath.trim("\"'");

      }


#ifndef UNIVERSAL_WINDOWS

      if (strPath.case_insensitive_begins("rtp://") || strPath.case_insensitive_begins("rtprx://"))
      {

         auto psystem = system();

         return psystem->audio()->get_rtp_file(strPath);

      }

#endif

      //// auto pcontext = get_context();

      return file()->get_file(payloadFile, eopen);

   }


} // namespace multimedia



