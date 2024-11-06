#include "framework.h"
#include "acme/filesystem/file/file.h"


#include <FreeImage.h>


unsigned DLL_CALLCONV __ReadProc2(void * buffer, unsigned size, unsigned count, fi_handle handle)
{

   memsize dwRead;

   ::file::file * pfile = (::file::file *) handle;

   unsigned int dwTotal = count * size;

   dwRead = pfile->read({ buffer, dwTotal });

   if (dwRead == dwTotal)
   {

      return count;

   }
   else
   {

      return (unsigned int)dwRead / (unsigned int)size;

   }

}


unsigned DLL_CALLCONV __WriteProc2(void * buffer, unsigned size, unsigned count, fi_handle handle)
{

   ::file::file * pfile = (::file::file *) handle;

   try
   {

      pfile->write({ buffer, count * size });

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

   try
   {

      pfile->translate(offset, (::enum_seek) origin);

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



//static unsigned int _stdcall  __ReadProc3 (void *buffer, unsigned int size, unsigned int count, fi_handle handle);
//static unsigned int _stdcall __WriteProc3 (void *buffer, unsigned int size, unsigned int count, fi_handle handle);
//static int _stdcall __SeekProc3 (fi_handle handle, long offset, int origin);
//static long _stdcall __TellProc3 (fi_handle handle);


unsigned int _stdcall  ___Ex1File__ReadProc(void * buffer, unsigned int size, unsigned int count, fi_handle handle)
{

   memsize dwRead;

   file_pointer  pfile = (::file::file *) handle;

   if ((dwRead = pfile->read({ buffer, count * size })))
   {

      return count;

   }
   else
   {

      return --count;

   }

}



