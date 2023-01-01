#include "framework.h"
#include "acme/filesystem/file/file.h"


#include <FreeImage.h>


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

      origin = ::e_seek_set;

   }
   else if (origin == SEEK_CUR)
   {

      origin = ::e_seek_current;

   }
   else if (origin == SEEK_END)
   {

      origin = ::e_seek_from_end;

   }

   try {

      pfile->translate(offset, (::enum_seek) origin);
      return 0;
   }
   catch(...)
   {


   }
   return -1;

}


long _stdcall ___Ex1File__TellProc(fi_handle handle)
{

   file_pointer  pfile = (::file::file *) handle;

   return (long)pfile->get_position();

}




