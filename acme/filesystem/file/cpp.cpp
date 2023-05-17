#include "framework.h"
//// #include "acme/primitive/string/string.h"
//////#include "acme/exception/exception.h"


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

      return error_bad_argument;

   }

   if(feof(pfile))
   {

      return ::success_end_of_file;

   }

   auto pszBuffer = str.get_buffer(iBufferSize);

   if(::is_null(pszBuffer))
   {

      return error_resource;

   }

   auto psz = fgets(pszBuffer, (int) iBufferSize, pfile);

   if(::is_null(psz))
   {

      zero(pszBuffer, iBufferSize);

      str.release_buffer();

      if(feof(pfile))
      {

         throw ::exception(::success_end_of_file);

      }

      int iErrNo = errno;

      auto estatus = failed_errno_status(iErrNo);

      throw ::exception(estatus);

   }

   str.release_buffer();

   return ::success;

}


CLASS_DECL_ACME string file_friendly_transform(string str, bool bTransformSlashes)
{

   str.replace_with("_", ":");
   str.replace_with("_", "\\");
   str.replace_with("_", "/");
   str.replace_with("_", "<");
   str.replace_with("_", ">");
   str.replace_with("_", "\"");
   str.replace_with("_", "\'");
   str.replace_with("_", "|");
   str.replace_with("_", "?");
   str.replace_with("_", "*");

   for (index i = 0; i < str.length(); i++)
   {

      if (str[i] <= 31)
      {

         str.set_at(i, '_');

      }

   }

   return str;

}



