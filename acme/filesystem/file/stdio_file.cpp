#include "framework.h"
#include <stdio.h>



stdio_file::stdio_file()
{

   m_pfile = nullptr;

}



stdio_file::~stdio_file()
{

   if(m_pfile != nullptr)
   {

      fclose_dup(m_pfile);

   }

}


::status::result stdio_file::open(const ::file::path & pszFileName, const efileopen & eopen)
{

   string str;

   if ((eopen & ::file::defer_create_directory) && (eopen & ::file::mode_write))
   {

      ::dir::mk(::file::path(pszFileName).folder());

   }

   if (eopen & ::file::mode_no_truncate && file_exists(pszFileName))
   {

      str += "r";

   }
   else if (eopen & ::file::mode_create)
   {

      str += "w";

   }
   else
   {

      str += "r";

   }



   //if (eopen & ::file::mode_write)
   //{

   //   str += "w";

   //}
   //else if(eopen & ::file::mode_read)
   //{

   //   

   //}

   if(eopen & ::file::type_binary)
   {

      str += "b";

   }
   else if(eopen & ::file::type_text)
   {

   }

   if (eopen & ::file::mode_write && eopen & ::file::mode_read)
   {

      str += "+";

   }

   m_pfile = fopen_dup(pszFileName, str, _SH_DENYNO);

   if (m_pfile == nullptr)
   {

      return ::error_io;

   }

   return ::success;

}


filesize stdio_file::seek(filesize lOff,::file::e_seek eseek)
{

   int nFrom = SEEK_SET;

   switch(eseek)
   {
   case ::file::seek_current:
      nFrom = SEEK_CUR;
      break;

   case ::file::seek_end:
      nFrom = SEEK_END;
      break;

   default:
      break;

   }

   return fseek_dup(m_pfile,lOff,nFrom);

}


filesize stdio_file::get_position() const
{

   return ftell_dup(m_pfile);

}


void stdio_file::flush()
{

   fflush_dup(m_pfile);

}


void stdio_file::close()
{

   fclose_dup(m_pfile);

}


memsize stdio_file::read(void * pdata, memsize nCount)
{

   auto size = fread_dup(pdata, 1, nCount, m_pfile);

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



void stdio_file::write(const void * pdata,memsize nCount)

{
   fwrite_dup(pdata,nCount, 1, m_pfile);

}


void stdio_file::lock(filesize dwPos,filesize dwCount)
{
   UNREFERENCED_PARAMETER(dwPos);
   UNREFERENCED_PARAMETER(dwCount);
}

void stdio_file::unlock(filesize dwPos,filesize dwCount)
{
   UNREFERENCED_PARAMETER(dwPos);
   UNREFERENCED_PARAMETER(dwCount);
}


void stdio_file::set_size(filesize dwNewLen)
{

   UNREFERENCED_PARAMETER(dwNewLen);

}


filesize stdio_file::get_size() const
{

   return flen_dup(m_pfile);

}


void stdio_file::assert_valid() const
{

}


void stdio_file::dump(dump_context & dumpcontext) const
{
   
   UNREFERENCED_PARAMETER(dumpcontext);

}


::file::path stdio_file::get_file_path() const
{

   return "";

}


bool stdio_file::get_status(::file::file_status & rStatus) const
{

   UNREFERENCED_PARAMETER(rStatus);

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



