#include "framework.h"


namespace file
{




} // namespace file


::e_status fgets_string(string & str, FILE * pfile, memsize iBufferSize)
{

   if(::is_null(pfile))
   {

      return error_null_pointer;

   }

   if(iBufferSize <= 0)
   {

      return error_invalid_argument;

   }

   if(feof(pfile))
   {

      return ::success_end_of_file;

   }

   auto pszBuffer = str.get_string_buffer(iBufferSize);

   if(::is_null(pszBuffer))
   {

      return error_resource;

   }

   auto psz = fgets(pszBuffer, (int) iBufferSize, pfile);

   if(::is_null(psz))
   {

      zero(pszBuffer, iBufferSize);

      str.release_string_buffer();

      if(feof(pfile))
      {

         throw_status(::success_end_of_file);

      }

      int iErrNo = errno;

      auto estatus = failed_errno_to_status(iErrNo);

      throw_status(estatus);

   }

   str.release_string_buffer();

   return ::success;

}



