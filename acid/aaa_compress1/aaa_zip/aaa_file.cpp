#include "framework.h"
#include "_internal.h"


void * zip_filefuncdef_malloc();
void zip_filefuncdef_set_file(void * p, ::file::file * pfile);



namespace zip
{


   file::file()
   {
      m_bOwnFile                 = false;
      m_pvoidFileFuncDef = zip_filefuncdef_malloc();
      m_pfUnzip = nullptr;
      m_pfZip = nullptr;
   }

   file::~file()
   {
      if(m_pfUnzip != nullptr)
      {
         unzClose(m_pfUnzip);
      }
      if(m_pfZip != nullptr)
      {
         zipClose(m_pfZip, nullptr);
      }

      free(m_pvoidFileFuncDef);

   }

//   bool file::unzip_open(const char * pcwsz)
//
//   {
//
//      m_bOwnFile = true;
//
//      file_pointer spfile(e_create_new);
//
//      throw ::exception(todo("object"));
//      //spfile->initialize(this);
//
//      try
//      {
//
//         if(!spfile->open(pcwsz, ::file::e_open_read | ::file::e_open_binary))
//
//         {
//
//            return false;
//
//         }
//
//      }
//      catch(const ::exception & e)
//      {
//
//         return false;
//
//      }
//      catch(...)
//      {
//
//         return false;
//
//      }
//
//      return unzip_open(spfile);
//
//   }


   bool file::unzip_open(file_pointer pfile, int iBufferLevel)
   {

      if (iBufferLevel >= 2)
      {

         m_pbuffile1 = __allocate< ::file::buffered_file >(pfile, 1024 * 32);

         m_pbuffile2 = __allocate< ::file::buffered_file >(m_pbuffile1, 1024 * 32);

      }
      else if (iBufferLevel == 1)
      {

         m_pbuffile1 = nullptr;

         m_pbuffile2 = __allocate< ::file::buffered_file >(pfile, 1024 * 32);

      }
      else
      {

         // good option if pfile is memory file?
         m_pbuffile2 = pfile;

      }

      m_pbuffile2->seek_to_begin();

      m_pfile = m_pbuffile2;

      zip_filefuncdef_set_file(m_pvoidFileFuncDef, m_pfile);

      m_pfUnzip = api::unzip_open(this);

      return true;

   }


   bool file::zip_open(const char * pcwsz)

   {

      m_bOwnFile = true;

      auto pfile = system()->__create < ::file::file > ();

      try
      {

         if(!pfile->open(pcwsz, ::file::e_open_read_write | ::file::e_open_binary | ::file::e_open_create | ::file::e_open_defer_create_directory))
         {

            return false;

         }

      }
      catch(const ::exception &)
      {

         return false;

      }
      catch(...)
      {

         return false;

      }

      return zip_open(pfile);

   }


   bool file::zip_open(file_pointer pfile)
   {

      m_pbuffile1 = __allocate< ::file::buffered_file >(pfile, 1024 * 256);

      m_pbuffile2 = __allocate< ::file::buffered_file >(m_pbuffile1, 1024 * 256);

      m_pbuffile2->seek_to_begin();

      m_pfile = m_pbuffile2;

      zip_filefuncdef_set_file(m_pvoidFileFuncDef, m_pfile);

      m_pfZip = api::zip_open(this);

      return true;

   }


   void  file::write_to_file(file_pointer  pfileOut, const ::wide_character * pcsz)

   {

      string str;

      unicode_to_utf8(str, pcsz);


      str.replace("\\", "/");
      if(unzLocateFile(m_pfUnzip, str, 1) != UNZ_OK)
         return;
      ::u8 buf[1024];
      i32 iRead;
      if(unzOpenCurrentFile(m_pfUnzip) != UNZ_OK)
         return;

      while((iRead = unzReadCurrentFile(m_pfUnzip, buf, sizeof(buf))) > 0)
      {
         pfileOut->write(buf, iRead);
      }
      if(unzCloseCurrentFile(m_pfUnzip) != UNZ_OK)
         return;
   }


} // namespace zip


//
//
//
//voidpf fileopen_file_func (voidpf opaque, const char* filename, i32 mode)
//{
//   __UNREFERENCED_PARAMETER(mode);
//   __UNREFERENCED_PARAMETER(filename);
//   ::zip::file * pzipfile = (::zip::file *) opaque;
//   file_pointer  pfile = pzipfile->m_pfile;
//   return (voidpf) pfile;
//}
//uptr  fileread_file_func (voidpf opaque, voidpf stream, void * buf, uptr size)
//{
//   return (uptr)((::zip::file *) opaque)->m_pfile.m_p->read(buf, size);
//}
//uptr  filewrite_file_func (voidpf opaque, voidpf stream, const void * buf, uptr size)
//{
//   __UNREFERENCED_PARAMETER(stream);
//   ::zip::file * pzipfile = (::zip::file *) opaque;
//   file_pointer  pfile = pzipfile->m_pfile;
//   pfile->write(buf, size);
//   return size;
//}
//long   filetell_file_func (voidpf opaque, voidpf stream)
//{
//   __UNREFERENCED_PARAMETER(stream);
//   ::zip::file * pzipfile = (::zip::file *) opaque;
//   file_pointer  pfile = pzipfile->m_pfile;
//   return (long) pfile->get_position();
//}
//
//long   fileseek_file_func (voidpf opaque, voidpf stream, uptr offset, i32 origin)
//{
//   __UNREFERENCED_PARAMETER(stream);
//   ::zip::file * pzipfile = (::zip::file *) opaque;
//   file_pointer  pfile = pzipfile->m_pfile;
//   if(pfile->seek(offset, (::enum_seek) origin) == 0xffffffff)
//      return -1;
//   else
//      return 0;
//
//}
//
//i32    fileclose_file_func (voidpf opaque, voidpf stream)
//{
//   __UNREFERENCED_PARAMETER(opaque);
//   __UNREFERENCED_PARAMETER(stream);
////      ::zip::file * pzipfile = (::zip::file *) opaque;
////      file_pointer  pfile = pzipfile->m_pfile;
//   return 1;
//}
//
//i32 c_zip_file_testerror_file_func (voidpf opaque, voidpf stream)
//{
//   __UNREFERENCED_PARAMETER(opaque);
//   __UNREFERENCED_PARAMETER(stream);
////      ::zip::file * pzipfile = (::zip::file *) opaque;
////      file_pointer  pfile = pzipfile->m_pfile;
//   //return spfile->IsValid() ? 0 : 1;
//   return 0;
//}
//
//
//








voidpf c_zip_file_open_file_func (voidpf opaque, const char* filename, i32 mode)
{
   __UNREFERENCED_PARAMETER(mode);
   __UNREFERENCED_PARAMETER(filename);
   ::file::file * pfile = (::file::file *) opaque;
   return (voidpf) pfile;
}
uptr  c_zip_file_read_file_func (voidpf opaque, voidpf stream, void * buf, uptr size)
{
   return (uptr)((::file::file *) opaque)->read(buf, size);
}
uptr  c_zip_file_write_file_func (voidpf opaque, voidpf stream, const void * buf, uptr size)
{
   __UNREFERENCED_PARAMETER(stream);
   ::file::file * pfile = (::file::file *) opaque;
   pfile->write(buf, size);
   return size;
}
long   c_zip_file_tell_file_func (voidpf opaque, voidpf stream)
{
   __UNREFERENCED_PARAMETER(stream);
   ::file::file * pfile = (::file::file *) opaque;
   return (long) pfile->get_position();
}

long   c_zip_file_seek_file_func (voidpf opaque, voidpf stream, uptr offset, i32 origin)
{
   __UNREFERENCED_PARAMETER(stream);
   auto * pfile = (::file::file *) opaque;
   if(pfile->translate(offset, (::enum_seek) origin) == 0xffffffff)
      return -1;
   else
      return 0;

}

i32    c_zip_file_close_file_func (voidpf opaque, voidpf stream)
{
   __UNREFERENCED_PARAMETER(opaque);
   __UNREFERENCED_PARAMETER(stream);
//      ::zip::file * pzipfile = (::zip::file *) opaque;
//      file_pointer  pfile = pzipfile->m_pfile;
   return 1;
}

i32 c_zip_file_testerror_file_func (voidpf opaque, voidpf stream)
{
   __UNREFERENCED_PARAMETER(opaque);
   __UNREFERENCED_PARAMETER(stream);
//      ::zip::file * pzipfile = (::zip::file *) opaque;
//      file_pointer  pfile = pzipfile->m_pfile;
   //return spfile->IsValid() ? 0 : 1;
   return 0;
}








void * zip_filefuncdef_malloc()
{

   zlib_filefunc_def_s * p = (zlib_filefunc_def_s *)malloc(sizeof(zlib_filefunc_def_s));

   p->zopen_file = &c_zip_file_open_file_func;
   p->zread_file = &c_zip_file_read_file_func;
   p->zwrite_file = &c_zip_file_write_file_func;
   p->ztell_file = &c_zip_file_tell_file_func;
   p->zseek_file = &c_zip_file_seek_file_func;
   p->zclose_file = &c_zip_file_close_file_func;
   p->zerror_file = &c_zip_file_testerror_file_func;

   return p;

}



void zip_filefuncdef_set_file(void * pParam, ::file::file * pfile)
{

   zlib_filefunc_def_s * p = (zlib_filefunc_def_s *)pParam;

   p->opaque = (voidpf)pfile;

}


