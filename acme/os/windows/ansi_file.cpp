#include "framework.h"
#include <io.h>
#include <fcntl.h>




i32 ansi_open(const char * psz,i32 i)
{
   return _wopen(::str::international::utf8_to_unicode(psz),i);
}

void ansi_get_errno(i32 * perrno)
{
   *perrno = errno;
}


FILE * ansi_fopen(const char * psz,const char * pszMode)
{
   return _wfopen(::str::international::utf8_to_unicode(psz),::str::international::utf8_to_unicode(pszMode));
}



int ansi_file_flag(int iFlag)
{

   int i = 0;

   if(iFlag & ::file::e_open_binary)
   {

      i |= _O_BINARY;

   }

   if(iFlag & ::file::e_open_read)
   {

      if(iFlag & ::file::e_open_write)
      {

         i |= _O_RDWR;

      }
      else
      {

         i |= _O_RDONLY;

      }

   }
   else if(iFlag & ::file::e_open_write)
   {

      i |= _O_WRONLY;

   }

   return i;

}

void ansi_unlink(const char * psz)
{

   _unlink(psz);

}










