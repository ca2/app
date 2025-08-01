#include "framework.h"
#include "stdio_file.h"
#include "acme/exception/runtime_check.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/status.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/operating_system/shared_posix/c_error_number.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/platform/trace.h"
#include "acme/prototype/prototype/memory.h"


#include <errno.h>


stdio_file::stdio_file()
{

   m_pfile = nullptr;

}


stdio_file::~stdio_file()
{

   if (m_pfile != nullptr)
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

   if (eopen & ::file::e_open_binary)
   {

      str += "b";

   }
   else if (eopen & ::file::e_open_text)
   {

   }

   if (eopen & ::file::e_open_write && eopen & ::file::e_open_read)
   {

      str += "+";

   }

   int iShare = _SH_DENYNO;

   m_eopen = eopen;

//   if(eopen & ::file::e_open_no_exception_on_open)
//   {
//
//      m_eflag |= e_flag_no_exception_if_not_found;
//
//   }

   open(path, str, iShare);

}


void stdio_file::open(const ::file::path & path, const ::scoped_string & scopedstrAttributes, int iShare)
{

   m_path = path;

#ifdef WINDOWS

   bool bTriedSetFileNormal = false;

try_again:

   wstring wstrPath(path);

   wstring wstrAttributes(scopedstrAttributes);

   m_pfile = _wfsopen(wstrPath, wstrAttributes, iShare);

#else

   m_pfile = fopen(path, strAttributes);

#endif

   if (!m_pfile)
   {

      auto cerrornumber = ::c_error_number();

      auto estatus = cerrornumber.estatus();

      m_estatus = estatus;

      set_nok();

      if (!estatus)
      {

         if (m_eopen & ::file::e_open_no_exception_on_open)
         {

            return;

         }
         else if (m_eopen & ::file::e_open_no_exception_if_not_found
         && (m_estatus == error_file_not_found
         || m_estatus == error_bad_path))
         {

            return;

         }

#ifdef WINDOWS

         if (estatus == error_file_access_denied)
         {

            if (file_system()->exists(path))
            {

               if (!bTriedSetFileNormal)
               {

                  file_system()->set_file_normal(path);

                  file_system()->clear_read_only(path);

                  bTriedSetFileNormal = true;

                  goto try_again;

               }

            }

         }

#endif

         throw_exception("fopen");

      }

   }
   else
   {

      m_estatus = ::success;

      set_ok_flag();

   }

}


void stdio_file::translate(filesize offset, ::enum_seek eseek)
{

   int nFrom = SEEK_SET;

   switch (eseek)
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

   if (iFseekResult != 0)
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


int stdio_file::get_unsigned_char()
{

   int iChar = fgetc(m_pfile);

   if (iChar == EOF)
   {

      set_end_of_file();

      return 0;

   }

   return (unsigned char)iChar;

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

   return (unsigned char)iChar;

}


void stdio_file::put_byte_back(unsigned char uch)
{

   ::ungetc(uch, m_pfile);

}


void stdio_file::write(const void * p, ::memsize s)
{

   fwrite(p, 1, s, m_pfile);

}


void stdio_file::lock(filesize dwPos, filesize dwCount)
{

   __UNREFERENCED_PARAMETER(dwPos);
   __UNREFERENCED_PARAMETER(dwCount);

}


void stdio_file::unlock(filesize dwPos, filesize dwCount)
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


class c_error_number stdio_file::c_error_number() const
{

   if(m_pfile == nullptr)
   {

      return {};

   }

   return {c_error_number_t{}, ferror(m_pfile)};

}


void stdio_file::throw_exception(const ::scoped_string & scopedstr)
{

   auto cerrornumber = c_error_number();

   auto estatus = cerrornumber.estatus();

   auto errorcode = cerrornumber.error_code();

   throw ::file::exception(estatus, errorcode, m_path, m_eopen, scopedstr);

}



::pointer <stdio_file> stdio_open(::particle * pparticle, const ::file::path & pathParam, const ::scoped_string & scopedstrAttrs, int iShare)
{

   auto pfile = pparticle->application()->__create_new < ::stdio_file >();

   if (!pfile)
   {

      return pfile;

   }

   auto path = pparticle->path_system()->defer_process_relative_path(pathParam);

   pfile->open(path, scopedstrAttrs, iShare);

   return pfile;

}



memory file_system::as_memory(const ::file::path & pathParam, character_count iReadAtMostByteCount, bool bNoExceptionIfNotFound)
{

   auto pfile = m_papplication->__create_new < stdio_file >();

   if (bNoExceptionIfNotFound)
   {

      pfile->m_eopen |= file::e_open_no_exception_if_not_found;

   }

   auto path = path_system()->defer_process_relative_path(pathParam);

   pfile->open(path, "rb", _SH_DENYNO);

   if (pfile.nok())
   {

      return {};

   }

   ::memory memory;

   auto uSize = pfile->size();

   if (iReadAtMostByteCount < 0)
   {

      iReadAtMostByteCount = (character_count)uSize;

   }
   else
   {

      iReadAtMostByteCount = minimum(iReadAtMostByteCount, (character_count)uSize);

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


memory file_system::safe_get_memory(const ::file::path & pathParam, character_count iReadAtMostByteCount, bool bNoExceptionIfNotFound)
{

   auto pfile = m_papplication->__create_new < stdio_file >();

   pfile->m_eopen |= ::file::e_open_no_exception_if_not_found;

   auto path = path_system()->defer_process_relative_path(pathParam);

   pfile->open(path, "rb", _SH_DENYNO);

   if (bNoExceptionIfNotFound)
   {

      if (pfile.nok())
      {

         return {};

      }

   }

   auto memory = pfile->right_memory();

   return memory;

}


memory file_system::__safe_get_memory(const ::file::path& pathParam, character_count iReadAtMostByteCount, bool bNoExceptionIfNotFound)
{

   FILE* file = fopen(pathParam, "r");
   if (file == NULL) {
      //fprintf(stderr, "Could not open file\n");
      return {};
   }

   fseek(file, 0, SEEK_END);
   long size = ftell(file);
   fseek(file, 0, SEEK_SET);
   ::string str;
   memory m;
   m.set_size(size);
   auto data = m.data();
   if (data == NULL) {
//      fprintf(stderr, "Memory allocation failed\n");
      fclose(file);
      return {};
   }

   fread(data, 1, size, file);
   //str.release_buffer(size);

   fclose(file);

   //printf("File content:\n%s\n", buffer);

   //free(buffer);

   return ::transfer(m);

}

#define BUFFER_SIZE 4096

memsize file_system::__safe_find_string(const ::file::path& path, const_char_pointer psz)
{
   
   int targetLength = strlen(psz);

   if (targetLength >= BUFFER_SIZE)
   {
      return -3;
   }
   FILE* file = fopen(path, "r");
   if (file == NULL) {
      //perror("Error opening file");
      return -2;
   }

   char buffer[BUFFER_SIZE * 2];
   char* found;
   size_t bytesRead;
   int offset = 0;
   memsize pos=0;
   int amountToRead = BUFFER_SIZE;
   int whereToRead = 0;
   while ((bytesRead = fread(buffer + whereToRead, 1, amountToRead, file)) > 0) 
   {
      (buffer + whereToRead)[bytesRead] = '\0';
      found = strstr(buffer, psz);
      if (found != NULL) {
         fclose(file);
         return pos + (found-buffer)-whereToRead; // String found
      }
      if (bytesRead == BUFFER_SIZE) 
      {
         offset = BUFFER_SIZE - targetLength + 1;
         memmove(buffer, buffer + offset, targetLength - 1);
         amountToRead = offset;
         whereToRead = targetLength - 1;
         //fseek(file, -offset, SEEK_CUR);
      }
      pos += bytesRead;
   }
   fclose(file);
   return -1; // String not found
}



CLASS_DECL_ACME void destroy_pointer(FILE * p)
{

   if (::is_set(p))
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

   auto predicate = [etracelevelInformation](auto etracelevel, auto & str, bool bCarriage)
   {

      //::fprintf(trace_level_FILE(etracelevel, etracelevelInformation), "%c: %s\n", trace_level_letter(etracelevel),
      //          ::string(str).c_str());
      ::fprintf(trace_level_FILE(etracelevel, etracelevelInformation), "%s%c", ::string(str).c_str(), bCarriage ? '\r': '\n');

      ::fflush(trace_level_FILE(etracelevel, etracelevelInformation));

   };

   return predicate;

}


CLASS_DECL_ACME trace_function std_get_output(::string * pstrOutput)
{

   auto predicate = [pstrOutput](auto etracelevel, auto& str, bool bCarriage)
      {

         ::string strLine;
         
         strLine.formatf("%c: %s%c", trace_level_letter(etracelevel), ::string(str).c_str(), bCarriage ? '\r' : '\n');

         (*pstrOutput) += strLine;

      };

   return predicate;

}


void __cdecl __clearerr_s(FILE * stream)
{

   c_error_number cerrornumber;

#ifdef WINDOWS

   cerrornumber.m_iErrorNumber = ::clearerr_s(stream);

#else

   clearerr(stream);

   cerrornumber.m_iErrorNumber = errno;

#endif

   if (cerrornumber.m_iErrorNumber)
   {

      throw ::runtime_check_exception(error_runtime_check, { cerrornumber }, "__clearerr_s");

   }

}


::e_status fgets_string(string & str, FILE * pfile, memsize iBufferSize)
{

   if (::is_null(pfile))
   {

      return error_null_pointer;

   }

   if (iBufferSize <= 0)
   {

      return error_bad_argument;

   }

   if (feof(pfile))
   {

      return ::success_end_of_file;

   }

   auto pszBuffer = str.get_buffer(iBufferSize);

   if (::is_null(pszBuffer))
   {

      return error_resource;

   }

   auto psz = fgets(pszBuffer, (int)iBufferSize, pfile);

   if (::is_null(psz))
   {

      zero(pszBuffer, iBufferSize);

      str.release_buffer();

      if (feof(pfile))
      {

         throw ::exception(::success_end_of_file);

      }

      auto cerrornumber = c_error_number();

      auto estatus = cerrornumber.failed_estatus();

      throw ::exception(estatus);

   }

   str.release_buffer();

   return ::success;

}


memsize file_system::as_memory(const ::file::path & pathParam, void * p, memsize s)
{

   stdio_file file;

   auto path = path_system()->defer_process_relative_path(pathParam);

   file.open(path, "r", _SH_DENYNO);

   auto iReadAtMostByteCount = s;

   unsigned char * psz = (unsigned char *)p;

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


void file_system::as_memory(memory_base & memory, const ::file::path & pathParam, memsize iReadAtMostByteCount, bool bNoExceptionOnOpen)
{

   memory.set_size(0);

   stdio_file file;

   auto path = path_system()->defer_process_relative_path(pathParam);

   try
   {

      file.open(path, "r", _SH_DENYNO);

   }
   catch (const ::exception & e)
   {

      if (bNoExceptionOnOpen)
      {

         return;

      }

      throw e;

   }
   catch (...)
   {

      if (bNoExceptionOnOpen)
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

   iReadAtMostByteCount = minimum_non_negative(iReadAtMostByteCount, (::character_count)iSize);

   memory.set_size(iReadAtMostByteCount);

   filesize dwReadTotal = 0;

   while (dwReadTotal < iReadAtMostByteCount)
   {

      auto dwRead = file.read(memory.data() + dwReadTotal, (iReadAtMostByteCount - dwReadTotal));

      if (dwRead <= 0)
      {

         break;

      }

      dwReadTotal += dwRead;

   }

   memory.set_size((memsize)dwReadTotal);

   //return ::success;

}




void file_system::append_wait(const ::file::path & pathFile, const block & block, const class time & time)
{

   auto pdirectorysystem = m_pdirectorysystem;

   pdirectorysystem->create(::file_path_folder(pathFile));


   if (!pdirectorysystem->is(::file_path_folder(pathFile)))
   {

      throw ::exception(error_path_not_found);

   }

   FILE * pfile = nullptr;

   auto millisStart = ::time::now();

   while (true)
   {

#if defined(__APPLE__) || defined(LINUX) || defined(__ANDROID__) || defined(__BSD__)

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


//filesize file_system::get_size(FILE * pfile)
//{
//
//    return get_size_fd(fileno(pfile));
//
//}



string file_system::line(const ::file::path & pathParam, ::collection::index iLine)
{

   string str;

   auto path = path_system()->defer_process_relative_path(pathParam);

#ifdef WINDOWS

   FILE * file = _fsopen(path, "r", _SH_DENYNO);

#else

   FILE * file = fopen(path.c_str(), "r");

#endif

   if (file == nullptr)
   {

      auto cerrornumber = c_error_number();

      auto estatus = cerrornumber.estatus();

      auto error_code = cerrornumber.error_code();

      throw ::file::exception(estatus, error_code, path);

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


void file_system::append_wait(const ::scoped_string & scopedstrFile, const block & block, const class time & time)
{

   m_pdirectorysystem->create(::file_path_folder(scopedstrFile));

   if (!m_pdirectorysystem->is(::file_path_folder(scopedstrFile)))
   {

      throw ::exception(::error_not_a_directory);

   }

   wstring wstr(scopedstrFile);

   FILE * pfile = nullptr;

   auto millisStart = ::time::now();

   while (true)
   {

#if defined(__APPLE__) || defined(LINUX) || defined(__ANDROID__) || defined(__BSD__)

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


//CLASS_DECL_ACME void __cdecl __clearerr_s(FILE * stream)
//{
//#ifdef WINDOWS
//   C_RUNTIME_ERROR_CHECK(::clearerr_s(stream));
//#else
//   ::clearerr(stream);
//   C_RUNTIME_ERROR_CHECK(errno);
//#endif
//}



