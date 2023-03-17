// From zip::file(or zip::infile) by camilo on 2021-11-10 15:46 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
//#include <zlib.h>
//#include <zutil.h>
#include "ioapi.h"
#include "file_function_definitions.h"
#include "acme/filesystem/file/file.h"


voidpf c_zip_file_open_file_func(voidpf opaque, const char* filename, i32 mode);
uptr  c_zip_file_read_file_func(voidpf opaque, voidpf stream, void* buf, uptr size);
uptr  c_zip_file_write_file_func(voidpf opaque, voidpf stream, const void* buf, uptr size);
long   c_zip_file_tell_file_func(voidpf opaque, voidpf stream);
long   c_zip_file_seek_file_func(voidpf opaque, voidpf stream, uptr offset, i32 origin);
i32    c_zip_file_close_file_func(voidpf opaque, voidpf stream);
i32 c_zip_file_testerror_file_func(voidpf opaque, voidpf stream);
zlib_filefunc_def* zip_filefuncdef_malloc();


void zip_filefuncdef_set_file(zlib_filefunc_def* pParam, ::file::file* pfile);


voidpf c_zip_file_open_file_func(voidpf opaque, const char* filename, i32 mode)
{
   
   __UNREFERENCED_PARAMETER(mode);
   __UNREFERENCED_PARAMETER(filename);
   
   ::file::file* pfile = (::file::file*)opaque;

   return (voidpf)pfile;

}


uptr c_zip_file_read_file_func(voidpf opaque, voidpf stream, void* buf, uptr size)
{

   return (uptr)((::file::file *)stream)->read({ buf, size });

}


uptr c_zip_file_write_file_func(voidpf opaque, voidpf stream, const void* buf, uptr size)
{

   __UNREFERENCED_PARAMETER(stream);

   ::file::file* pfile = (::file::file*)stream;

   pfile->write({ buf, size });

   return size;

}


long c_zip_file_tell_file_func(voidpf opaque, voidpf stream)
{

   __UNREFERENCED_PARAMETER(stream);

   ::file::file* pfile = (::file::file*)stream;

   return (long)pfile->get_position();

}


long   c_zip_file_seek_file_func(voidpf opaque, voidpf stream, uptr offset, i32 origin)
{

   __UNREFERENCED_PARAMETER(stream);

   auto* pfile = (::file::file*)stream;
   try
   {


      pfile->translate(offset, (::enum_seek)origin);

      return 0;

   }
   catch(...)
   {

   }

   return -1;

}


i32 c_zip_file_close_file_func(voidpf opaque, voidpf stream)
{

   __UNREFERENCED_PARAMETER(opaque);
   __UNREFERENCED_PARAMETER(stream);

   //      ::zip::file * pzipfile = (::zip::file *) opaque;
   //      file_pointer  pfile = pzipfile->m_pfile;
   
   return 1;

}


i32 c_zip_file_testerror_file_func(voidpf opaque, voidpf stream)
{

   __UNREFERENCED_PARAMETER(opaque);
   __UNREFERENCED_PARAMETER(stream);
   //      ::zip::file * pzipfile = (::zip::file *) opaque;
   //      file_pointer  pfile = pzipfile->m_pfile;
      //return spfile->IsValid() ? 0 : 1;
   
   return 0;

}





//
//
//
//void* zip_filefuncdef_malloc()
//{
//
//   zlib_filefunc_def_s* p = (zlib_filefunc_def_s*)malloc(sizeof(zlib_filefunc_def_s));
//
//   (zopen_file = &c_zip_file_open_file_func;
//   (zread_file = &c_zip_file_read_file_func;
//   (zwrite_file = &c_zip_file_write_file_func;
//   (ztell_file = &c_zip_file_tell_file_func;
//   (zseek_file = &c_zip_file_seek_file_func;
//   (zclose_file = &c_zip_file_close_file_func;
//   (zerror_file = &c_zip_file_testerror_file_func;
//
//   return p;
//
//}


//
//void zip_filefuncdef_set_file(void* pParam, ::file::file* pfile)
//{
//
//   zlib_filefunc_def_s* p = (zlib_filefunc_def_s*)pParam;
//
//   (opaque = (voidpf)pfile;
//
//}


//
//#ifdef __cplusplus
//extern "C" {
//#endif

namespace folder_zip
{

   file_function_definitions::file_function_definitions() 
   {

      zopen_file = &c_zip_file_open_file_func;
      zread_file = &c_zip_file_read_file_func;
      zwrite_file = &c_zip_file_write_file_func;
      ztell_file = &c_zip_file_tell_file_func;
      zseek_file = &c_zip_file_seek_file_func;
      zclose_file = &c_zip_file_close_file_func;
      zerror_file = &c_zip_file_testerror_file_func;
      opaque = this;

   }


} //namespace folder_zip