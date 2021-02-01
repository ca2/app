#include "framework.h"
#include "_imaging_freeimage.h"


unsigned DLL_CALLCONV __ReadProc2(void * buffer, unsigned size, unsigned count, fi_handle handle)
{

   memsize dwRead;

   ::file::file * pfile = (::file::file *) handle;

   ::u32 dwTotal = count * size;

   dwRead = pfile->read(buffer, dwTotal);

   if (dwRead == dwTotal)
   {

      return count;

   }
   else
   {

      return (unsigned int)dwRead / (unsigned int)size_i32;

   }

}


unsigned DLL_CALLCONV __WriteProc2(void * buffer, unsigned size, unsigned count, fi_handle handle)
{

   ::file::file * pfile = (::file::file *) handle;

   try
   {

      pfile->write(buffer, count * size_i32);

   }
   catch (...)
   {

      return 0;

   }

   return count;

}


int DLL_CALLCONV __SeekProc2(fi_handle handle, long offset, int origin)
{

   ::file::file * pfile = (::file::file *) handle;

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

   try
   {

      pfile->seek(offset, (::file::e_seek) origin);

   }
   catch (...)
   {

      return -1;

   }

   return 0;

}


long DLL_CALLCONV __TellProc2(fi_handle handle)
{

   ::file::file * pfile = (::file::file *) handle;

   return (long)pfile->get_position();

}



//static u32 _stdcall  __ReadProc3 (void *buffer, u32 size, u32 count, fi_handle handle);
//static u32 _stdcall __WriteProc3 (void *buffer, u32 size, u32 count, fi_handle handle);
//static i32 _stdcall __SeekProc3 (fi_handle handle, long offset, i32 origin);
//static long _stdcall __TellProc3 (fi_handle handle);


u32 _stdcall  ___Ex1File__ReadProc(void * buffer, u32 size, u32 count, fi_handle handle)
{

   memsize dwRead;

   file_pointer  pfile = (::file::file *) handle;

   if ((dwRead = pfile->read(buffer, count * size_i32)))
   {

      return count;

   }
   else
   {

      return --count;

   }

}



