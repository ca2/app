#include "framework.h"
#include "stdio_file.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/system.h"


stdio_file::stdio_file()
{

   m_pfile = nullptr;

}



stdio_file::~stdio_file()
{

   if(m_pfile != nullptr)
   {

      fclose(m_pfile);

   }

}


void stdio_file::open(const ::file::path & path, const ::file::e_open & eopen)
{

   string str;

//   if ((eopen & ::file::e_open_defer_create_directory) && (eopen & ::file::e_open_write))
//   {
//
//      acmedirectory()->create(path.folder());
//
//   }

   //if (eopen & ::file::e_open_no_truncate && acmefile()->exists(path))
   if (eopen & ::file::e_open_no_truncate)
   {

      str += "r";

   }
   else if (eopen & ::file::e_open_create)
   {

      str += "w";

   }
   else
   {

      str += "r";

   }

   if(eopen & ::file::e_open_binary)
   {

      str += "b";

   }
   else if(eopen & ::file::e_open_text)
   {

   }

   if (eopen & ::file::e_open_write && eopen & ::file::e_open_read)
   {

      str += "+";

   }

   int iShare = _SH_DENYNO;

   open(path, str, iShare);

   //throw ::exception(

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return ::success;

}


void stdio_file::open(const ::file::path & path, const ::string & strAttributes, int iShare)
{

   m_path = path;

#ifdef WINDOWS

   bool bTriedSetFileNormal = false;

   try_again:

   wstring wstrPath(path);

   wstring wstrAttributes(strAttributes);

   m_pfile = _wfsopen(wstrPath, wstrAttributes, iShare);

#else

   m_pfile = fopen(path, strAttributes);

#endif

   if (!m_pfile)
   {

      int iErrNo = errno;

      auto estatus = errno_status(iErrNo);

      if (!estatus)
      {

         if (m_eflag & flag_no_exception_if_not_found && estatus == error_file_not_found)
         {

            m_eflag |= flag_file_not_found;

            return;

         }

#ifdef WINDOWS

         if (estatus == error_file_access_denied)
         {

            if (acmefile()->exists(path))
            {

               if (!bTriedSetFileNormal)
               {

                  acmefile()->set_file_normal(path);

                  acmefile()->clear_read_only(path);

                  bTriedSetFileNormal = true;

                  goto try_again;

               }

            }

         }

#endif

         throw ::exception(estatus, string("Error with file: ") + path);

      }

   }

}


void stdio_file::translate(filesize offset, ::enum_seek eseek)
{

   int nFrom = SEEK_SET;

   switch(eseek)
   {
   case ::e_seek_current:
      nFrom = SEEK_CUR;
      break;

   case ::e_seek_from_end:
      nFrom = SEEK_END;
      break;

   default:
      break;

   }

#ifdef WINDOWS

   if (fseek(m_pfile, (long)offset, nFrom))
   {

      auto iErrNo = errno;

      auto estatus = errno_status(iErrNo);

      auto errorcode = errno_error_code(iErrNo);

      throw ::file::exception(estatus, errorcode, m_path, "fseek != 0", m_eopen);

   }

#else

   int iFseekResult = fseek(m_pfile, offset, nFrom);
   
   if(iFseekResult != 0)
   {

      i32 iErrNo = errno;
      
      auto errorcode = errno_error_code(iErrNo);
      
      auto estatus = errno_status(iErrNo);
      
      throw ::file::exception(estatus, errorcode, m_path, "fseek != 0");

      //return -1;

   }

#endif

   //return ftell(m_pfile);

}


filesize stdio_file::get_position() const
{

   return ftell(m_pfile);

}


void stdio_file::flush()
{

   fflush(m_pfile);

}


void stdio_file::close()
{

   fclose(m_pfile);

}


memsize stdio_file::read(void * pdata, memsize nCount)
{

   auto size = fread(pdata, 1, nCount, m_pfile);

   int iEof = feof(m_pfile);

   if (!iEof)
   {

      int iError = ferror(m_pfile);

      if (iError != 0)
      {

         i32 iErrNo = errno;
         
         auto errorcode = errno_error_code(iErrNo);
         
         auto estatus = errno_status(iErrNo);
         
         throw ::file::exception(estatus, errorcode, m_path, "fread: !feof and ferror");

         return 0;

      }

   }

   return (::memsize) size;

}


int stdio_file::get_u8()
{

   int iChar = fgetc(m_pfile);

   if (iChar == EOF)
   {

      set_end_of_file();

      return 0;

   }

   return (::byte) iChar;

}


int stdio_file::peek_byte()
{

   int iChar = fgetc(m_pfile);

   if (iChar == EOF)
   {

      set_end_of_file();

      return 0;

   }

   ::ungetc(iChar, m_pfile);

   return (::byte) iChar;

}


void stdio_file::put_byte_back(::byte byte)
{

   ::ungetc(byte, m_pfile);

   //UNUSED_RETURN_VALUEreturn iCharRet;

}


void stdio_file::write(const void * pdata,memsize nCount)
{

   fwrite(pdata,nCount, 1, m_pfile);

}


void stdio_file::lock(filesize dwPos,filesize dwCount)
{

   __UNREFERENCED_PARAMETER(dwPos);
   __UNREFERENCED_PARAMETER(dwCount);

}


void stdio_file::unlock(filesize dwPos,filesize dwCount)
{

   __UNREFERENCED_PARAMETER(dwPos);
   __UNREFERENCED_PARAMETER(dwCount);

}


void stdio_file::set_size(filesize dwNewLen)
{

   __UNREFERENCED_PARAMETER(dwNewLen);

}


filesize stdio_file::size() const
{

   //return acmefile()->get_size(m_pfile);

   auto position = get_position();

   ((stdio_file *)this)->seek_to_end();

   auto size = get_position();

   ((stdio_file *)this)->set_position(position);

   return size;

}


//void stdio_file::assert_ok() const
//{
//
//}
//
//
//void stdio_file::dump(dump_context & dumpcontext) const
//{
//
//   __UNREFERENCED_PARAMETER(dumpcontext);
//
//}


::file::path stdio_file::get_file_path() const
{

   return "";

}


bool stdio_file::get_status(::file::file_status & rStatus) const
{

   __UNREFERENCED_PARAMETER(rStatus);

   return false;

}


bool stdio_file::is_opened() const
{

   return m_pfile != nullptr;

}


string stdio_file::get_location() const
{

   return get_file_path();

}


//CLASS_DECL_ACME file_pointer create_stdio_file(const ::file::path & path, const ::string & strAttributes, int iShare)
//{
//
//   auto pfile = __new(stdio_file);
//
//   auto estatus = pfile->open(path, strAttributes, iShare);
//
//   if(!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return pfile;
//
//}



