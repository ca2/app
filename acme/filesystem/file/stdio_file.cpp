#include "framework.h"
#include "stdio_file.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/status.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/platform/system.h"
#include "acme/platform/trace.h"
#include "acme/primitive/primitive/memory.h"


#include <errno.h>


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

   return (::u8) iChar;

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

   return (::u8) iChar;

}


void stdio_file::put_byte_back(::u8 u8)
{

   ::ungetc(u8, m_pfile);

}


void stdio_file::write(const void * p, ::memsize s)
{

   fwrite(p, 1, s, m_pfile);

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



::pointer <stdio_file> stdio_open(::particle * pparticle, const ::file::path & pathParam, const ::scoped_string & scopedstrAttrs, int iShare)
{

    auto pfile = pparticle->m_pcontext->__create_new < ::stdio_file >();

    if (!pfile)
    {

        return pfile;

    }

    auto path = pparticle->acmepath()->defer_process_relative_path(pathParam);

    pfile->open(path, scopedstrAttrs, iShare);

    return pfile;

}



memory acme_file::as_memory(const ::file::path & pathParam, strsize iReadAtMostByteCount, bool bNoExceptionIfNotFound)
{

    auto pfile = m_pcontext->__create_new < stdio_file >();

    if (bNoExceptionIfNotFound)
    {

        pfile->m_eflag |= stdio_file::flag_no_exception_if_not_found;

    }

    auto path = acmepath()->defer_process_relative_path(pathParam);

    pfile->open(path, "rb", _SH_DENYNO);

    if (bNoExceptionIfNotFound)
    {

        if (pfile->m_eflag & stdio_file::flag_file_not_found)
        {

            return {};

        }

    }

    ::memory memory;

    auto uSize = pfile->size();

    if(iReadAtMostByteCount < 0)
    {

        iReadAtMostByteCount = (strsize) uSize;

    }
    else
    {

        iReadAtMostByteCount = minimum(iReadAtMostByteCount, (strsize)uSize);

    }

    memory.set_size(iReadAtMostByteCount);

    auto p = memory.data();

    ::size_t iPos = 0;

    while (iReadAtMostByteCount - iPos > 0)
    {

        auto dwRead = pfile->read({ p + iPos, (size_t)iReadAtMostByteCount - iPos });

        if (dwRead <= 0)
        {

            break;

        }

        iPos += dwRead;

    }

    return memory;

}


memory acme_file::safe_get_memory(const ::file::path & pathParam, strsize iReadAtMostByteCount, bool bNoExceptionIfNotFound)
{

    auto pfile = m_pcontext->__create_new < stdio_file >();

    pfile->m_eflag |= stdio_file::flag_no_exception_if_not_found;

    auto path = acmepath()->defer_process_relative_path(pathParam);

    pfile->open(path, "rb", _SH_DENYNO);

    if (bNoExceptionIfNotFound)
    {

        if (pfile->m_eflag & stdio_file::flag_file_not_found)
        {

            return {};

        }

    }

    auto memory = pfile->right_memory();

    return memory;

}



CLASS_DECL_ACME void destroy_pointer(FILE * p)
{

    if(::is_set(p))
    {

        fclose(p);

    }

}





CLASS_DECL_ACME FILE * trace_level_FILE(enum_trace_level etracelevel, enum_trace_level etracelevelInformation)
{

    return etracelevel <= etracelevelInformation ? stdout : stderr;

}


CLASS_DECL_ACME trace_function std_inline_log(enum_trace_level etracelevelInformation)
{

    auto predicate = [&](auto etracelevel, auto & str)
    {

        ::fprintf(trace_level_FILE(etracelevel, etracelevelInformation), "%c: %s\n", trace_level_letter(etracelevel),
                  ::string(str).c_str());

    };

    return predicate;

}







void __cdecl __clearerr_s(FILE *stream)
{

#ifdef WINDOWS

    C_RUNTIME_ERROR_CHECK(::clearerr_s(stream));

#else

    clearerr(stream);

    C_RUNTIME_ERROR_CHECK(errno);

#endif

}


::e_status fgets_string(string & str, FILE * pfile, memsize iBufferSize)
{

    if(::is_null(pfile))
    {

        return error_null_pointer;

    }

    if(iBufferSize <= 0)
    {

        return error_bad_argument;

    }

    if(feof(pfile))
    {

        return ::success_end_of_file;

    }

    auto pszBuffer = str.get_buffer(iBufferSize);

    if(::is_null(pszBuffer))
    {

        return error_resource;

    }

    auto psz = fgets(pszBuffer, (int) iBufferSize, pfile);

    if(::is_null(psz))
    {

        zero(pszBuffer, iBufferSize);

        str.release_buffer();

        if(feof(pfile))
        {

            throw ::exception(::success_end_of_file);

        }

        int iErrNo = errno;

        auto estatus = failed_errno_status(iErrNo);

        throw ::exception(estatus);

    }

    str.release_buffer();

    return ::success;

}


memsize acme_file::as_memory(const ::file::path & pathParam, void * p, memsize s)
{

    stdio_file file;

    auto path = acmepath()->defer_process_relative_path(pathParam);

    file.open(path, "r", _SH_DENYNO);

    auto iReadAtMostByteCount = s;

    ::u8 * psz = (::u8 *) p;

    ::size_t iPos = 0;

    while (iReadAtMostByteCount - iPos > 0)
    {

        auto dwRead = file.read({ psz + iPos, (size_t)iReadAtMostByteCount - iPos });

        if (dwRead <= 0)
        {

            break;

        }

        iPos += dwRead;

    }

    return iPos;

}


void acme_file::as_memory(memory_base & memory, const ::file::path & pathParam, memsize iReadAtMostByteCount, bool bNoExceptionOnOpen)
{

    memory.set_size(0);

    stdio_file file;

    auto path = acmepath()->defer_process_relative_path(pathParam);

    try
    {

        file.open(path, "r", _SH_DENYNO);

    }
    catch(const ::exception & e)
    {

        if(bNoExceptionOnOpen)
        {

            return;

        }

        throw e;

    }
    catch(...)
    {

        if(bNoExceptionOnOpen)
        {

            return;

        }

        throw ::exception(error_catch_all_exception);

    }

    auto iSize = file.size();

    if (iSize < 0)
    {

        memory.set_size(0);

        return;

    }

    iReadAtMostByteCount = minimum_non_negative(iReadAtMostByteCount, (::strsize)iSize);

    memory.set_size(iReadAtMostByteCount);

    filesize dwReadTotal = 0;

    while (dwReadTotal < iReadAtMostByteCount)
    {

        auto dwRead = file.read(memory(dwReadTotal, (iReadAtMostByteCount - dwReadTotal)));

        if (dwRead <= 0)
        {

            break;

        }

        dwReadTotal += dwRead;

    }

    memory.set_size((memsize) dwReadTotal);

    //return ::success;

}




void acme_file::append_wait(const ::file::path & pathFile, const block & block, const class time & time)
{

    auto pacmedirectory = m_pacmedirectory;

    pacmedirectory->create(::file_path_folder(pathFile));


    if (!pacmedirectory->is(::file_path_folder(pathFile)))
    {

        throw ::exception(error_path_not_found);

    }

    FILE * pfile = nullptr;

    auto millisStart = ::time::now();

    while (true)
    {

#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID) || defined(FREEBSD)

        pfile = fopen(pathFile, "ab");

#else

        wstring wstr(pathFile);

      pfile = _wfopen(wstr, L"ab");

#endif

        if (pfile != nullptr)
        {

            break;

        }

        if (millisStart.elapsed() > time)
        {

            throw ::exception(error_timeout);

        }

        preempt(500_ms);

    }

    fwrite(block.begin(), block.size(), 1, pfile);

    fclose(pfile);

    //return success;

}


//filesize acme_file::get_size(FILE * pfile)
//{
//
//    return get_size_fd(fileno(pfile));
//
//}



string acme_file::line(const ::file::path & pathParam, index iLine)
{

    string str;

    auto path = acmepath()->defer_process_relative_path(pathParam);

#ifdef WINDOWS

    FILE * file = _fsopen(path, "r", _SH_DENYNO);

#else

    FILE * file = fopen(path.c_str(), "r");

#endif

    if (file == nullptr)
    {

        trace_last_error();

        throw ::exception(error_io);

    }

    int iChar;

    string strLine;

    int iLastChar = -1;

    while (iLine >= 0)
    {

        iChar = fgetc(file);

        if (iChar == EOF)
        {

            break;

        }

        if (iChar == '\r')
        {

            iLine--;

        }
        else if (iChar == '\n')
        {

            if (iLastChar != '\r')
            {

                iLine--;

            }

        }
        else if (iLine == 0)
        {

            str += (char)iChar;

        }

        iLastChar = iChar;

    }

    return str;

}


void acme_file::append_wait(const ::string & strFile, const block & block, const class time & time)
{

    m_pacmedirectory->create(::file_path_folder(strFile));

    if (!m_pacmedirectory->is(::file_path_folder(strFile)))
    {

        throw ::exception(::error_not_a_directory);

    }

    wstring wstr(strFile);

    FILE * pfile = nullptr;

    auto millisStart = ::time::now();

    while (true)
    {

#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID) || defined(FREEBSD)

        pfile = fopen(strFile.c_str(), "ab");

#else

        pfile = _wfopen(wstr, L"ab");

#endif

        if (pfile != nullptr)
        {

            break;

        }

        if (millisStart.elapsed() > time)
        {

            throw ::exception(error_timeout);

        }

        preempt(500_ms);

    }

    fwrite(block.data(), block.size(), 1, pfile);

    fclose(pfile);

    //return ::success;

}



