#include "framework.h"
//#include "_internal.h"


//void * zip_filefuncdef_malloc();
//void zip_filefuncdef_set_file(void * p, ::file::file * pfile);
//


namespace folder_zip
{


   file::file()
   {
      //m_bOwnFile                 = false;
      //m_pvoidFileFuncDef = zip_filefuncdef_malloc();
      //m_pfUnzip = nullptr;
      //m_pfZip = nullptr;
   }


   file::~file()
   {
      //if(m_pfUnzip != nullptr)
      //{
      //   unzClose(m_pfUnzip);
      //}
      //if(m_pfZip != nullptr)
      //{
      //   zipClose(m_pfZip, nullptr);
      //}

      //free(m_pvoidFileFuncDef);

   }



   void file::assert_valid() const
   {


   }


   void file::dump(dump_context& dumpcontext) const
   {

      dumpcontext << "with handle " << (uptr)m_pfolder.m_p;
      dumpcontext << " and name \"" << m_strFileName << "\"";
      dumpcontext << "\n";

   }

//   bool file_container::unzip_open(const char * pcwsz)
//
//   {
//
//      m_bOwnFile = true;
//
//      file_pointer spfile(e_create_new);
//
//      __throw(todo("object"));
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


   //bool file::unzip_open(file_pointer pfile, int iBufferLevel)
   //{

   //   if (iBufferLevel >= 2)
   //   {

   //      m_pbuffile1 = __new(::file::buffered_file(pfile, 1024 * 32));

   //      m_pbuffile2 = __new(::file::buffered_file(m_pbuffile1, 1024 * 32));

   //   }
   //   else if (iBufferLevel == 1)
   //   {

   //      m_pbuffile1 = nullptr;

   //      m_pbuffile2 = __new(::file::buffered_file(pfile, 1024 * 32));

   //   }
   //   else
   //   {

   //      // good option if pfile is memory file?
   //      m_pbuffile2 = pfile;

   //   }

   //   m_pbuffile2->seek_to_begin();

   //   m_pfile = m_pbuffile2;

   //   zip_filefuncdef_set_file(m_pvoidFileFuncDef, m_pfile);

   //   m_pfUnzip = api::unzip_open(this);

   //   return true;

   //}


   //bool file_container::zip_open(const char * pcwsz)

   //{

   //   m_bOwnFile = true;

   //   auto pfile = m_psystem->__create < ::file::file > ();

   //   try
   //   {

   //      if(!pfile->open(pcwsz, ::file::e_open_read_write | ::file::e_open_binary | ::file::e_open_create | ::file::e_open_defer_create_directory))
   //      {

   //         return false;

   //      }

   //   }
   //   catch(const ::exception &)
   //   {

   //      return false;

   //   }
   //   catch(...)
   //   {

   //      return false;

   //   }

   //   return zip_open(pfile);

   //}


   //bool file_container::zip_open(file_pointer pfile)
   //{

   //   m_pbuffile1 = __new(::file::buffered_file(pfile, 1024 * 256));

   //   m_pbuffile2 = __new(::file::buffered_file(m_pbuffile1, 1024 * 256));

   //   m_pbuffile2->seek_to_begin();

   //   m_pfile = m_pbuffile2;

   //   zip_filefuncdef_set_file(m_pvoidFileFuncDef, m_pfile);

   //   m_pfZip = api::zip_open(this);

   //   return true;

   //}


memsize file::read(void* pdata, memsize nCount)
{
   //   ASSERT_VALID(this);
   ASSERT(m_pfolder->m_unzfile != nullptr);

   if (nCount == 0)
      return 0;   // avoid Win32 "nullptr-read"

   ASSERT(pdata != nullptr);

   ASSERT(__is_valid_address(pdata, (uptr)nCount));

   auto iRead = unzReadCurrentFile(m_pfolder->m_unzfile, pdata, (u32)nCount);

   m_iPosition += iRead;

   return (::u32)iRead;
}

void file::write(const void* pdata, memsize nCount)

{

   return;
     /* byte buf[1024];
      i32 iRead;
      if(unzOpenCurrentFile(m_pfUnzip) != UNZ_OK)
         return;

      while((iRead = unzReadCurrentFile(m_pfUnzip, buf, sizeof(buf))) > 0)
      {
         pfileOut->write(buf, iRead);
      }
      if(unzCloseCurrentFile(m_pfUnzip) != UNZ_OK)
         return;
   }*/

}

   //void  file::write_to_file(file_pointer  pfileOut, const widechar * pcsz)

   //{

   //   string str;

   //   ::str::international::unicode_to_utf8(str, pcsz);


   //   str.replace("\\", "/");
   //   if(unzLocateFile(m_pfUnzip, str, 1) != UNZ_OK)
   //      return;
   //   byte buf[1024];
   //   i32 iRead;
   //   if(unzOpenCurrentFile(m_pfUnzip) != UNZ_OK)
   //      return;

   //   while((iRead = unzReadCurrentFile(m_pfUnzip, buf, sizeof(buf))) > 0)
   //   {
   //      pfileOut->write(buf, iRead);
   //   }
   //   if(unzCloseCurrentFile(m_pfUnzip) != UNZ_OK)
   //      return;
   //}




   //bool file::is_reading() const
   //{

   //   return m_pfolder->m_unzipfile && !m_pfolder->m_pzipfile;

   //}

   filesize file::get_position() const
   {

      return m_iPosition;

   }


   void file::flush()
   {

   }


   void file::close()
   {

      //m_filea.erase_all();
      //m_infilea.erase_all();
      m_straPath.erase_all();
      m_straPrefix.erase_all();
      m_strFileName.Empty();

   }




   filesize file::translate(filesize offset, ::enum_seek eseek)
   {

      u64 iNewPosition;

      if (eseek == ::e_seek_set)
      {

         iNewPosition = offset;

      }
      else if (eseek == ::e_seek_from_end)
      {

         iNewPosition = m_pfolder->m_unzfileinfo.uncompressed_size - offset;

      }
      else if (eseek == ::e_seek_current)
      {

         iNewPosition = m_iPosition + offset;

      }
      else
      {

         throw ::exception(error_invalid_argument, "zip::folder::seek invalid seek option");

      }

      if (iNewPosition < m_iPosition)
      {

         if (unzCloseCurrentFile(m_pfolder->m_unzfile) != UNZ_OK)
         {

            return -1;

         }

         if (unzOpenCurrentFile(m_pfolder->m_unzfile) != UNZ_OK)
         {

            return -1;

         }

         m_iPosition = 0;

      }

      if (iNewPosition > m_iPosition)
      {

         i64 iRemain = iNewPosition - m_iPosition;

         i64 iGet;

         i32 iRead;

         byte pbBuf[1024];

         while (iRemain > 0)
         {

            iGet = minimum(iRemain, 1024);

            iRead = unzReadCurrentFile(m_pfolder->m_unzfile, pbBuf, (u32)iGet);

            iRemain -= iRead;

            if (iRead < iGet)
            {

               break;

            }

         }

         iNewPosition -= iRemain;

      }

      m_iPosition = iNewPosition;

      return iNewPosition;

   }



   bool file::is_opened() const
   {

      return m_pfolder && m_pfolder->m_unzfile;

   }


   void file::set_size(filesize dwNewLen)
   {

      __throw(error_not_supported);

   }


   filesize file::get_size() const
   {

      return m_pfolder->m_unzfileinfo.uncompressed_size;

   }



} // namespace folder_zip


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


