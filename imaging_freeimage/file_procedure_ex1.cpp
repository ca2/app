#include "framework.h"


u32 _stdcall ___Ex1File__WriteProc(void * buffer, u32 size, u32 count, fi_handle handle)
{

   file_pointer  pfile = (::file::file *) handle;

   try
   {

      pfile->write(buffer, count * size);

   }
   catch (...)
   {

      return --count;

   }

   return count;

}


i32 _stdcall ___Ex1File__SeekProc(fi_handle handle, long offset, i32 origin)
{

   file_pointer  pfile = (::file::file *) handle;

   if (origin == SEEK_SET)
   {

      origin = ::file::seek_begin;

   }
   else if (origin == SEEK_CUR)
   {

      origin = ::file::seek_current;

   }
   else if (origin == SEEK_END)
   {

      origin = ::file::seek_end;

   }

   if (pfile->seek(offset, (::file::e_seek) origin) == 0xFFFFFFFF)
   {

      return -1;

   }
   else
   {

      return 0;

   }

}


long _stdcall ___Ex1File__TellProc(fi_handle handle)
{

   file_pointer  pfile = (::file::file *) handle;

   return (long)pfile->get_position();

}




