#include "framework.h"
#include "stdio_file.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/status.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
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


void stdio_file::open(const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception)
{

   string str;

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

         throw_exception("fopen");

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

      throw_exception("fseek != 0");

   }

#else

   int iFseekResult = fseek(m_pfile, offset, nFrom);
   
   if(iFseekResult != 0)
   {

      throw_exception("fseek != 0");

   }

#endif

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


memsize stdio_file::read(void * p, ::memsize s)
{

   auto amountRead = fread(p, 1, s, m_pfile);

   int iEof = feof(m_pfile);

   if (!iEof)
   {

      int iError = ferror(m_pfile);

      if (iError != 0)
      {

         throw_exception("fread: !feof and ferror");

         return 0;
         
      }

   }

   return (::memsize)amountRead;

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

}


void stdio_file::write(const void * p, ::memsize s)
{

   fwrite(p, 1, s, m_pfile);

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

   auto position = get_position();

   ((stdio_file *)this)->seek_to_end();

   auto size = get_position();

   ((stdio_file *)this)->set_position(position);

   return size;

}


::file::path stdio_file::get_file_path() const
{

   return m_path;

}


::file::file_status stdio_file::get_status() const
{

   return {};

}


string stdio_file::get_location() const
{

   return get_file_path();

}


bool stdio_file::is_opened() const
{

   return m_pfile != nullptr;

}


void stdio_file::throw_exception(const ::scoped_string & scopedstr)
{

   auto iErrNo = errno;

   auto estatus = errno_status(iErrNo);

   auto errorcode = errno_error_code(iErrNo);

   throw ::file::exception(estatus, errorcode, m_path, m_eopen, scopedstr);

}



