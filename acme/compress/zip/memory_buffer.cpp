#include "framework.h"


void * zip_filefuncdef_malloc();
void zip_filefuncdef_set_file(void * p, ::file::file * pfile);


namespace zip
{


   memory_file::memory_file()
   {

      common_construct();

   }


   memory_file::memory_file(memory_base * pmemory)
   {

      common_construct();

   }


   void memory_file::common_construct()
   {

      m_pvoidFileFuncDef = zip_filefuncdef_malloc();

      zip_filefuncdef_set_file(m_pvoidFileFuncDef, this);


   }


   memory_file::~memory_file()
   {

      free(m_pvoidFileFuncDef);

   }


} // namespace zip



//
//
//voidpf c_zip_memory_buffer_open_file_func (voidpf opaque, const char* filename, i32 mode)
//{
//   __UNREFERENCED_PARAMETER(mode);
//   __UNREFERENCED_PARAMETER(filename);
//   ::zip::memory_file * pfile = (::zip::memory_file *) opaque;
//   return (voidpf) pfile;
//}
//
//uptr  c_zip_memory_buffer_read_file_func (voidpf opaque, voidpf stream, void * buf, uptr size)
//{
//   __UNREFERENCED_PARAMETER(stream);
//   ::zip::memory_file * pfile = (::zip::memory_file *) opaque;
//   return (uptr) pfile->read(buf, size);
//}
//
//uptr  c_zip_memory_buffer_write_file_func (voidpf opaque, voidpf stream, const void * buf, uptr size)
//{
//   __UNREFERENCED_PARAMETER(stream);
//   ::zip::memory_file * pfile = (::zip::memory_file *) opaque;
//
//   pfile->write(buf, size);
//   return size;
//}
//
//long   c_zip_memory_buffer_tell_file_func (voidpf opaque, voidpf stream)
//{
//   __UNREFERENCED_PARAMETER(stream);
//   ::zip::memory_file * pfile = (::zip::memory_file *) opaque;
//   return (long) pfile->get_position();
//}
//
//long   c_zip_memory_buffer_seek_file_func (voidpf opaque, voidpf stream, uptr offset, i32 origin)
//{
//   __UNREFERENCED_PARAMETER(stream);
//   ::zip::memory_file * pfile = (::zip::memory_file *) opaque;
//   if(pfile->seek(offset, (::enum_seek) origin) == 0xffffffff)
//      return -1;
//   else
//      return 0;
//}
//
//i32    c_zip_memory_buffer_close_file_func (voidpf opaque, voidpf stream)
//{
//   __UNREFERENCED_PARAMETER(opaque);
//   __UNREFERENCED_PARAMETER(stream);
////      ::zip::memory_file * pfile = (::zip::memory_file *) opaque;
//   return 1;
//}
//
//i32 c_zip_memory_buffer_testerror_file_func (voidpf opaque, voidpf stream)
//{
//   __UNREFERENCED_PARAMETER(stream);
//   ::zip::memory_file * pfile = (::zip::memory_file *) opaque;
//   return pfile->IsValid() ? 0 : 1;
//}
//
//
