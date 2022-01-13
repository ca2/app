#include "framework.h"
#include "acme/operating_system.h"
#include <stdio.h>
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_file.h"



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

   if ((eopen & ::file::e_open_defer_create_directory) && (eopen & ::file::e_open_write))
   {

      m_psystem->m_pacmedir->create(path.folder());

   }

   if (eopen & ::file::e_open_no_truncate && m_psystem->m_pacmefile->exists(path))
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

   //throw_status(

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

   wstring wstrPath(path);

   wstring wstrAttributes(strAttributes);

   m_pfile = _wfsopen(wstrPath, wstrAttributes, iShare);

#else

   m_pfile = fopen(path, strAttributes);

#endif

   if (!m_pfile)
   {

      int iErrNo = errno;

      auto estatus = errno_to_status(iErrNo);

      if (!estatus)
      {

         if (m_eflag & flag_no_exception_if_not_found && estatus == error_file_not_found)
         {

            m_eflag |= flag_file_not_found;

            return;

         }

         throw_status(estatus, string("Error with file: ") + path);

      }

   }

}


filesize stdio_file::translate(filesize offset, ::enum_seek eseek)
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

      // error;

      throw ::file::exception(error_file, GetLastError(), errno, m_path);

      return -1;

   }


#else

   if(fseek(m_pfile, offset, nFrom))
   {

      // error;

      throw ::file::exception(error_file, 0, errno, m_path);

      return -1;

   }

#endif

   return ftell(m_pfile);

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

      if (iError > 0)
      {

         ::file::throw_status(error_file, iError, m_strFileName);

         return 0;

      }

   }

   return (::memsize) size;

}


int stdio_file::get_character()
{

   int iChar = fgetc(m_pfile);

   return iChar;

}



int stdio_file::peek_character()
{

   int iChar = fgetc(m_pfile);

   ::ungetc(iChar, m_pfile);

   return iChar;

}


int stdio_file::put_character_back(int iChar)
{

   int iCharRet = ::ungetc(iChar, m_pfile);

   return iCharRet;

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


filesize stdio_file::get_size() const
{

   //return m_psystem->m_pacmefile->get_size(m_pfile);

   auto position = get_position();

   auto size = ((stdio_file *)this)->seek_to_end();

   ((stdio_file *)this)->set_position(position);

   return size;

}


void stdio_file::assert_valid() const
{

}


void stdio_file::dump(dump_context & dumpcontext) const
{

   __UNREFERENCED_PARAMETER(dumpcontext);

}


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



