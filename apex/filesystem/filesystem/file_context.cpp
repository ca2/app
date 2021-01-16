#include "framework.h"
#include "acme/platform/acme_str_pool.h"
#include "apex/platform/machine_event.h"
#include "apex/platform/machine_event_central.h"

#ifdef WINDOWS_DESKTOP

#include "apex/platform/app_core.h"

#elif defined(_UWP)
#include "apex/os/_os.h"
#endif

#include <stdio.h>


#define UTF8_BOM "\xef\xbb\xbf"


#include "apex/compress/zip/_.h"
#include "apex/const/id.h"


#ifndef WINDOWS
#include <sys/stat.h>
#endif

//#define astr (*::apex::g_papexstrpool)

#ifdef RASPBIAN
//#include <openssl/md5.h>
//#include <openssl/whrlpool.h>
#include "apex/crypto/crypto_openssl.h"
#endif


file_context::file_context()
{

}


file_context::~file_context()
{

}


::e_status file_context::initialize(::layered *pobjectContext)
{

   auto estatus = ::object::initialize(pobjectContext);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


bool file_context::exists(const ::file::path &pathParam)
{

   ::file::path path = Context.defer_process_matter_path(pathParam);

   if (!(path & ::file::e_flag_required) && path.is_empty())
   {

      return false;

   }

   ::file::enum_type etype = ::file::e_type_none;

   bool bExists = is_file_or_dir(path, nullptr, &etype);

   return bExists && (etype == ::file::e_type_file || etype == ::file::e_type_element);

}


//bool file_context::is_file_or_dir(const ::file::path & path, ::file::enum_type * petype)
//{
//
//   path = Context.defer_process_matter_path(path, papp, bOptional, bNoCache);
//
//   if (bOptional && path.is_empty())
//   {
//
//      return false;
//
//   }
//
//   return exists(path, papp, petype, bOptional, bNoCache);
//
//}


bool file_context::is_file_or_dir(const ::file::path &path, payload *pvarQuery, ::file::enum_type *petype)
{

   if (::str::begins(path, "http://") || ::str::begins(path, "https://"))
   {

      property_set set;

      if (path & ::file::e_flag_required)
      {

         set["required"] = true;

      }

      if (path & ::file::e_flag_bypass_cache)
      {

         set["nocache"] = true;

      }

      return Context.http().is_file_or_dir(path, pvarQuery, petype, set);

   }

   if (::thread_is_set(id_thread_zip_is_dir))
   {

      strsize iFind = ::str::find_file_extension("zip:", path);

      if (iFind >= 0)
      {

         if (!exists(path.Mid(0, iFind + 4)))
         {

            return false;

         }

         compress_context compress(this);

         ::file::path pathZip;

         string_array straPath;

         if (!compress.get_patha(pathZip, straPath, path))
         {

            return false;

         }

         auto pfile = Context.file().get_reader(pathZip);

         zip_context zip(get_context_object());

         return zip.is_file_or_dir(pfile, straPath, petype);

      }

   }

   return is_file_or_dir_dup(path, petype) != FALSE;

}


payload file_context::length(const ::file::path &pszPath)
{

   return length(pszPath, nullptr);

}


payload file_context::length(const ::file::path &path, payload *pvarQuery)
{

   if (path.m_iSize != -1)
   {

      return max(0, path.m_iSize);

   }

   payload varRet;

#ifdef WINDOWS

   WIN32_FILE_ATTRIBUTE_DATA data;

   if (!GetFileAttributesExW(::str::international::utf8_to_unicode(path), GetFileExInfoStandard, &data))
   {

      varRet.set_type(::e_type_null);

      ((::file::path &) path).m_iSize = -2;

   }
   else
   {

      varRet = (((u64) data.nFileSizeHigh) << 32) | (u64) data.nFileSizeLow;

      ((::file::path &) path).m_iSize = varRet.m_i64;

   }

#else

   struct stat stat;

   if (::stat(path, &stat) == -1)
   {

      varRet.set_type(::e_type_null);

      ((::file::path &) path).m_iSize = -2;

   }
   else
   {

      varRet = (iptr)stat.st_size;

      ((::file::path &)path).m_iSize = varRet.m_i64;

   }

#endif

   return varRet;

}


::file::path file_context::module()
{

   auto pfilesystem = System.m_pfilesystem;

   return pfilesystem->m_pathModule;

}


::file::path file_context::ca2module()
{

   return System.m_pfilesystem->m_pathCa2Module;

}


::file::path file_context::time_square(const string &pszPrefix, const string &pszSuffix)
{

   return time(Context.dir().time_square(), 25, pszPrefix, pszSuffix);

}


::file::path file_context::time_log(const string &pszId)
{
   return time(Context.dir().time_log(pszId), 9);
}


::file::path
file_context::time(const ::file::path &psz, i32 iMaxLevel, const string &pszPrefix, const string &pszSuffix,
                   bool bTryDelete)
{

   sync_lock lockMachineEvent(
      !is_null(&System.machine_event_central()) ? &System.machine_event_central().m_machineevent.m_mutex
                                                : ((::mutex *) nullptr));

   i32 iIncLevel = -1;

   ::file::path str;

   ::file::path path;

   string strPrefix(pszPrefix);

   string strSuffix(pszSuffix);

   restart:

   str.Empty();

   str = psz;

   Context.dir().mk(str);

   ::file::listing ls;

   string strFormat;

   for (i32 i = 1; i <= iMaxLevel;)
   {

      Context.dir().mk(str);

      if (!Context.dir().is(str))
      {

         __throw(::exception::exception("time square dir does not exist"));

      }

      Context.dir().ls(ls, str);

      if (i < iMaxLevel)
      {

         i32 iMax = filterex_time_square("", ls);

         if (iMax == -1)
         {

            str /= "00";

            Context.dir().mk(str);

         }
         else if (iMax == 99)
         {

            iIncLevel = i - 1;

            goto restart;

         }
         else
         {

            if (i == iIncLevel)
            {

               iMax++;

            }

            strFormat.Format("%02d", iMax);

            str /= strFormat;

            if (i == iIncLevel)
            {

               Context.dir().mk(str);

            }

         }

         i++;

      }
      else // if i == iMaxLevel
      {

         Context.dir().ls(ls, str);

         i32 iMax = bTryDelete ? 0 : filterex_time_square(pszPrefix, ls);

         do
         {

            if (iMax == -1)
            {

               path = str / (strPrefix + "00" + strSuffix);

               if (file_context::try_create_file(path, bTryDelete))
               {

                  return path;

               }

            }
            else if (iMax == 99 && iMaxLevel > 1)
            {

               iIncLevel = iMaxLevel - 1;

               goto restart;

            }
            else
            {

               iMax++;

               if (bTryDelete)
               {

                  strFormat.Format("%d", iMax);

               }
               else
               {

                  strFormat.Format("%02d", iMax);

               }

               path = str / (strPrefix + strFormat + strSuffix);

               if (file_context::try_create_file(path, bTryDelete))
               {

                  return path;

               }

            }

         } while (bTryDelete);

         return "";

      }

   }

   return str;

}


i32 file_context::filterex_time_square(const char *pszPrefix, ::file::patha &stra)
{

   i32 iMax = -1;

   i32 iIndex;

   for (i32 i = 0; i < stra.get_size(); i++)
   {

      string str = stra[i].name();

      if (::str::begins_eat_ci(str, pszPrefix))
      {

         if (str.get_length() < 2)
         {

            stra.remove_at(i);

            i--;

            continue;

         }

         if (!isdigit((uchar) str[0]) || !isdigit((uchar) str[1]))
         {

            stra.remove_at(i);

            i--;

            continue;

         }

         iIndex = atoi(str.Mid(0, 2));

         if (iIndex > iMax)
         {

            iMax = iIndex;

         }

      }

   }

   return iMax;

}


// fail if exists, create if not exists
bool file_context::try_create_file(const ::file::path &path, bool bTryDelete)
{

   if (Context.file().exists(path))
   {

      if (!bTryDelete)
      {

         return false;

      }

      Context.file().del(path);

      if (Context.file().exists(path))
      {

         return false;

      }

   }

   __pointer(::file::file) pfile;

   __construct(pfile);

   if (!m_estatus)
   {

      return false;

   }

   try
   {

      if (pfile->open(path, ::file::e_open_create | ::file::e_open_binary).failed())
      {

         return false;

      }

   }
   catch (...)
   {

      return false;

   }

   return true;

}


payload file_context::as_json(const payload &varFile)
{

   string str = as_string(varFile);

   str.trim();

   if (str.is_empty())
   {

      return ::e_type_new;

   }

   const char *pszJson = str;

   payload v;

   try
   {

      v.parse_json(pszJson);

   }
   catch (const ::exception_pointer &pe)
   {

      ::exception_pointer esp(pe);

      TRACE(esp->get_message());

      v = ::e_type_new;

   }
   catch (...)
   {

      TRACE("GENERAL Exception parsing json file_context::as_json : \"" + str + "\"");

      v = ::e_type_new;

   }

   return v;

}


string file_context::as_string(const payload &varFile)
{

   memory memory;

   if (!as_memory(varFile, memory))
   {

      return "";

   }

   return memory.as_utf8();

}


bool file_context::as_memory(const payload &varFile, memory_base &mem)
{

   auto pfile = get_file(varFile, ::file::e_open_share_deny_none | ::file::e_open_read | ::file::e_open_binary);

   if (!pfile)
   {

      return false;

   }

   try
   {

      if (!pfile->full_read(mem))
      {

         return false;

      }

      return true;

   }
   catch (...)
   {

   }

   return false;

}


void file_context::put_lines(const payload &varFile, const string_array &stra)
{

   file_pointer spfile;

   try
   {

      spfile = get_file(varFile, ::file::e_open_write | ::file::e_open_truncate | ::file::e_open_create |
                                 ::file::e_open_defer_create_directory);

   }
   catch (...)
   {

      return;

   }

   _put_lines(spfile, stra);

}


void file_context::put_lines_utf8(const payload &varFile, const string_array &stra)
{

   file_pointer spfile;

   try
   {

      spfile = get_file(varFile, ::file::e_open_text | ::file::e_open_write | ::file::e_open_truncate | ::file::e_open_create |
                                 ::file::e_open_defer_create_directory);

   }
   catch (...)
   {

      return;

   }

   if (spfile.is_null())
   {

      return;

   }

   spfile->write(UTF8_BOM, STATIC_ASCII_STRING_LENGTH(UTF8_BOM));

   _put_lines(spfile, stra);

}


void file_context::_put_lines(::file::file *pfile, const string_array &stra)
{

   if (pfile == nullptr)
   {

      return;

   }

   for (auto &strLine : stra)
   {

      pfile->println(strLine);

   }

}


void file_context::lines(string_array &stra, const payload &varFile)
{


   file_result pfile;

   try
   {

      pfile = get_file(varFile, ::file::e_open_text | ::file::e_open_read);

   }
   catch (...)
   {

      return;

   }

   if (!pfile)
   {

      return;

   }

   string strLine;

   while (pfile->read_string(strLine))
   {

      stra.add(strLine);

   }

}


bool file_context::put_contents(const payload &varFile, const void *pvoidContents, ::count count)
{

   file_result pfile;

   int iTry = 0;

   while (true)
   {

      try
      {

         pfile = get_file(varFile,
                          ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_share_deny_write |
                          ::file::e_open_defer_create_directory);

      }
      catch (::exception_pointer e)
      {

         pfile.add(e);

      }
      catch (...)
      {

         return false;

      }

      if (pfile)
      {

         break;

      }

      auto estatus = pfile.status();

      if (estatus == error_file_sharing_violation)
      {

         sleep(300_ms);

         iTry++;

         if (iTry > 8)
         {

            return false;

         }

      }

   }

   pfile->write(pvoidContents, count);

   return true;

}


bool file_context::add_contents(const payload &varFile, const void *pvoidContents, ::count count)
{

   file_pointer spfile;

   try
   {

      spfile = get_file(varFile,
                        ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_no_truncate |
                        ::file::e_open_share_exclusive | ::file::e_open_defer_create_directory);

   }
   catch (...)
   {

      return false;

   }

   if (spfile.is_null())
      return false;


   spfile->seek_to_end();

   spfile->write(pvoidContents, count);

   return true;

}


bool file_context::put_contents(const payload &varFile, const char *pcszContents)
{

   if (pcszContents == nullptr)
   {

      return put_contents(varFile, "", 0);

   }
   else
   {

      string strContents(pcszContents, strlen(pcszContents));

      ::str::fix_eol(strContents);

      return put_contents(varFile, strContents, strContents.get_length());

   }

}


bool file_context::add_contents(const payload &varFile, const char *pcszContents)
{

   if (pcszContents != nullptr)
   {

      return add_contents(varFile, pcszContents, strlen(pcszContents));


   }

   return false;

}


bool file_context::put_contents(const payload &varFile, ::file::file *pfile)
{

   file_pointer spfile;

   spfile = get_file(varFile,
                     ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_share_deny_write |
                     ::file::e_open_defer_create_directory);

   if (spfile.is_null())
   {

      return false;

   }

   memory mem;

   mem.set_size(1024 * 1024 * 8);

   memsize uRead;

   while ((uRead = pfile->read(mem.get_data(), mem.get_size())) > 0)
   {

      spfile->write(mem.get_data(), uRead);

   }

   return true;

}


bool file_context::put_contents(const payload &varFile, memory &mem)
{

   return put_contents(varFile, mem.get_data(), (count) mem.get_size());

}


bool file_context::put_contents_utf8(const payload &varFile, const char *pcszContents)
{

   file_pointer spfile;

   spfile = get_file(varFile,
                     ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_share_deny_write |
                     ::file::e_open_defer_create_directory);

   if (spfile.is_null())
   {

      return false;

   }

   spfile->write(UTF8_BOM, STATIC_ASCII_STRING_LENGTH(UTF8_BOM));

   string strContents(pcszContents, strlen(pcszContents));

   ::str::fix_eol(strContents);

   spfile->write(strContents);

   return true;

}


::status::result file_context::copy(payload varTarget, payload varSource, bool bFailIfExists, e_extract eextract)
{

   if (Context.dir().is(varSource.get_file_path()) &&
       (eextract == extract_first || eextract == extract_all || !(::str::ends_ci(varSource.get_file_path(), ".zip"))))
   {

      ::file::listing patha;

      Context.dir().rls(patha, varSource);

      ::file::path strDst;
      ::file::path strSrc;
      ::file::path strDirSrc(varSource.get_file_path());
      ::file::path strDirDst(varTarget.get_file_path());

      if (::thread_is_set(id_thread_zip_is_dir) && (::str::ends(strDirSrc, ".zip")))
      {

         strDirSrc += ":";

      }

      for (i32 i = 0; i < patha.get_size(); i++)
      {
         strSrc = patha[i];
         strDst = strSrc;
         ::str::begins_eat_ci(strDst, strDirSrc);
         strDst = strDirDst / strDst;
         if (Context.dir().is(strSrc))
         {
            if ((eextract == extract_first || eextract == extract_none) &&
                (::str::ends_ci(varSource.get_file_path(), ".zip")))
            {
            }
            else
            {
               Context.dir().mk(strDst);
            }
         }
         else
         {
            if (!Context.dir().is(strDst.folder()))
            {
               Context.dir().mk(strDst.folder());
            }
            copy(strDst, strSrc, bFailIfExists, eextract == extract_all ? extract_all : extract_none);
         }
      }
   }
   else
   {

      if (varTarget.get_file_path().has_char() && varSource.get_file_path().has_char())
      {

         if (!Context.dir().is(varTarget.get_file_path().folder()))
         {

            Context.dir().mk(varTarget.get_file_path().folder());

         }

         if (!::file_copy_dup(varTarget, varSource, !bFailIfExists))
         {

            return ::error_failed;

         }

         return ::success;

      }

      if (bFailIfExists)
      {

         if (exists(varTarget))
         {

            return ::error_failed;

         }

      }

      payload varNew;

      if (Context.dir().is(varTarget) && varSource.get_file_path().name().has_char())
      {

         varNew = ::file::path(varTarget) / varSource.get_file_path().name();

      }
      else
      {

         varNew = varTarget;

      }

      file_pointer ofile;

      ofile = get_file(varNew,
                       ::file::e_open_write | ::file::e_open_binary | ::file::e_open_create | ::file::e_open_defer_create_directory |
                       ::file::e_open_share_deny_write);

      if (ofile.is_null())
      {
         string strError;
         strError.Format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open output file",
                         varSource.get_file_path().c_str(), varNew.get_file_path().c_str(), bFailIfExists);
         __throw(io_exception(::error_io, strError));
      }

      bool bGeneralFailure = false;

      bool bOutputFail = false;
      bool bInputFail = false;
      try
      {

         auto ifile = get_reader(varSource, ::file::e_open_read | ::file::e_open_binary | ::file::e_open_share_deny_none);

         if (!ifile)
         {
            string strError;
            strError.Format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open input file",
                            varSource.get_file_path().c_str(), varNew.get_file_path().c_str(), bFailIfExists);
            __throw(io_exception(::error_io, strError));
         }

         binary_stream ostream(ofile);

         //stream istream(ifile, FIRST_VERSION);

         Context.file().transfer(ostream.m_p, ifile);

         ::file_pointer pfileInput = ifile;

         if (pfileInput)
         {

            bool bStatusFail = false;

            ::file::file_status st;

            try
            {

               pfileInput->get_status(st);

            }
            catch (...)
            {

               bStatusFail = true;

               TRACE("During copy, failed to get status from input file \"%s\" bFailIfExists=%d",
                     varSource.get_file_path().c_str(), bFailIfExists);

            }

            if (!bStatusFail)
            {
               try
               {

                  pfileInput->get_status(st);

               }
               catch (...)
               {

                  bStatusFail = true;

                  TRACE("During copy, failed to set status to output file \"%s\" bFailIfExists=%d",
                        varTarget.get_file_path().c_str(), bFailIfExists);

               }

            }

         }

         try
         {
            ofile->flush();
         }
         catch (...)
         {
         }

         try
         {
            ofile->close();
         }
         catch (...)
         {
            bOutputFail = true;
         }

      }
      catch (...)
      {

         bGeneralFailure = true;

      }

      if (bInputFail || bGeneralFailure)
      {
         if (bOutputFail)
         {
            string strError;
            strError.Format(
               "During copy, failed to close both input file \"%s\" and output file \"%s\" bFailIfExists=%d",
               varSource.get_file_path().c_str(), varTarget.get_file_path().c_str(), bFailIfExists);
            __throw(io_exception(::error_io, strError));
         }
         else
         {
            string strError;
            strError.Format("During copy, failed to close input file \"%s\" bFailIfExists=%d",
                            varSource.get_file_path().c_str(), bFailIfExists);
            __throw(io_exception(::error_io, strError));
         }
      }
      else if (bOutputFail)
      {
         string strError;
         strError.Format("During copy, failed to close output file \"%s\" bFailIfExists=%d",
                         varTarget.get_file_path().c_str(), bFailIfExists);
         __throw(io_exception(::error_io, strError));
      }

   }

   return ::success;

}


::status::result file_context::move(const ::file::path &pszNew, const ::file::path &psz)
{

#ifdef WINDOWS_DESKTOP

   if (!::MoveFileW(
      ::str::international::utf8_to_unicode(psz),
      ::str::international::utf8_to_unicode(pszNew)))
   {

      DWORD dwError = ::GetLastError();

      if (dwError == ERROR_ALREADY_EXISTS)
      {

         if (::CopyFileW(
            ::str::international::utf8_to_unicode(psz),
            ::str::international::utf8_to_unicode(pszNew),
            FALSE))
         {

            if (!::DeleteFileW(::str::international::utf8_to_unicode(psz)))
            {

               dwError = ::GetLastError();

               string strError;

               strError.Format("Failed to delete the file to move \"%s\" error=%d", psz, dwError);

               TRACE("%s", strError);

            }

            return ::success;

         }

         dwError = ::GetLastError();

      }

      string strError;

      strError.Format("Failed to move file \"%s\" to \"%s\" error=%d", psz, pszNew, dwError);

      __throw(io_exception(::error_io, strError));

   }

#elif defined(_UWP)

   ::Windows::Storage::StorageFile ^ file = get_os_file(psz, 0, 0, nullptr, OPEN_EXISTING, 0, nullptr);

   if (file == nullptr)
   {

      //output_debug_string("test");

      __throw(::exception::exception("file::file_context::move Could not move file, could not open source file"));

   }

   string strDirOld = psz.folder();
   string strDirNew = pszNew.folder();
   string strNameOld = psz.name();
   string strNameNew = pszNew.name();

   if (strDirOld == strDirNew)
   {
      if (strNameOld == strNameNew)
      {
         return ::success;
      }
      else
      {
         ::wait(file->RenameAsync(strNameNew));
      }
   }
   else
   {
      ::Windows::Storage::StorageFolder ^ folder = get_os_folder(strDirNew);
      if (strNameOld == strNameNew)
      {
         ::wait(file->MoveAsync(folder));
      }
      else
      {
         ::wait(file->MoveAsync(folder, strNameNew));
      }
   }


#else
   if (::rename(psz, pszNew) != 0)
   {
      i32 err = errno;
      string strError;
      strError.Format("Failed to delete file error=%d", err);
      __throw(::exception::exception(strError));
   }
#endif

   return ::success;

}


::status::result file_context::del(const ::file::path &psz)
{


#ifdef WINDOWS_DESKTOP

   HANDLE h = ::CreateFileW(::str::international::utf8_to_unicode(string("\\\\?\\") + psz),
                            GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING,
                            FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_DELETE_ON_CLOSE, nullptr);

   if (h == INVALID_HANDLE_VALUE)
   {

      DWORD dwError = ::GetLastError();

      if (dwError == 2) // the file does not exist, so delete "failed"
      {

         return ::success;

      }

      string strError;

      strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);

      return ::error_failed;

   }
   else
   {
      ::FlushFileBuffers(h);
      ::CloseHandle(h);
   }

   /*      if(!::DeleteFileW(::str::international::utf8_to_unicode(string("\\\\?\\") + psz)))
   {
   u32 dwError = ::get_last_error();
   if(dwError == 2) // the file does not exist, so delete "failed"
   return;
   string strError;
   strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);
   __throw(io_exception(strError));
   }*/


#else

   if (unlink(psz) != 0)
   {
      i32 err = errno;
      if (err != ENOENT) // already does not exist - consider removal successful - does not issue an exception
      {
         string strError;
         strError.Format("Failed to delete file error=%d", err);
         __throw(::exception::exception(strError));
      }
   }
#endif

   return ::success;

}


::file::path file_context::duplicate(const ::file::path &psz)
{
   string strCopy("copy");
   string strNew;
   if (Context.dir().is(psz))
   {
      i32 i = 1;
      while (i <= 100)
      {
         strNew.Format("%s-%s-%d", psz.c_str(), strCopy.c_str(), i);
         if (!exists(strNew))
         {
            copy(strNew, psz, false, extract_all);
            return strNew;
         }
         i++;
      }
   }
   else
   {
      string strExt = psz.ext();
      if (!strExt.is_empty())
      {
         strExt = "-" + strExt;
      }
      i32 i = 1;
      while (i <= 100)
      {
         strNew.Format("%s-%s-%d%s", psz.c_str(), strCopy.c_str(), i, strExt.c_str());
         if (!exists(strNew))
         {
            copy(strNew, psz, false, extract_all);
            return strNew;
         }
         i++;
      }
   }
   return "";
}


::file::path file_context::paste(const ::file::path &pathLocation, const ::file::path &path)
{

   ::file::path pathDir = path.folder();

   ::file::path pathDst = pathLocation;

   ::file::path pathSrc = pathDir;

   if (pathDst == pathSrc)
   {

      return duplicate(path);

   }
   else
   {

      ::file::path pathNew = pathDst / path.name();

      copy(pathNew, path, false, extract_all);

      return pathNew;

   }

}


void file_context::trash_that_is_not_trash(::file::patha &stra)
{

   if (stra.get_size() <= 0)
   {

      return;

   }

   ::file::path strDir = Context.dir().trash_that_is_not_trash(stra[0]);

   Context.dir().mk(strDir);

   for (i32 i = 0; i < stra.get_size(); i++)
   {

      move(strDir / stra[i].name(), stra[i]);

   }

}


void file_context::trash_that_is_not_trash(const ::file::path &psz)
{

   ::file::path strDir = Context.dir().trash_that_is_not_trash(psz);

   Context.dir().mk(strDir);

   move(strDir / psz.name(), psz);

}


bool file_context::get_status(const ::file::path &path, ::file::file_status &status)
{

   UNREFERENCED_PARAMETER(path);
   UNREFERENCED_PARAMETER(status);
   __throw(interface_only_exception());

}


::status::result file_context::set_status(const ::file::path &path, const ::file::file_status &status)
{

   UNREFERENCED_PARAMETER(path);
   UNREFERENCED_PARAMETER(status);
   __throw(interface_only_exception());

}


::status::result file_context::replace(const ::file::path &pszContext, const string &pszFind, const string &pszReplace)
{

   ::status::result e;

   ::file::listing straTitle;
   Context.dir().ls(straTitle, pszContext);
   string strOld;
   string strNew;
   //string strFail;
   ::file::path pathContext = pszContext;
   for (i32 i = 0; i < straTitle.get_size(); i++)
   {
      strOld = straTitle[i].name();
      strNew = strOld;
      strNew.replace(pszFind, pszReplace);
      if (strNew != strOld)
      {
         // TODO(camilo) : should there be a way to chain or return multiple exceptions... instead of ::status::result specifile file smart...
         // why not a super smart chained super hand heroe smarter pointerer that can contain vector of any excepction based on
         // ::exception like (::file::exception) (I supposed ::file::exception is already based on ::exception OMG CAMILO!!!)
         // and may be then replace could do replace for example on HTTP servers and return may io_exception and not tighted
         // to a barely translated io exception into a empty ::file::exception with improper filled members....
         e.add(move(pathContext / strNew, pathContext / strOld));

      }

   }
   //if (strFail.has_char())
   //{
   //   App(papp).message_box(nullptr, strFail, e_message_box_icon_exclamation);
   //}

   return e;


}


bool file_context::transfer(::file::file *pfileOut, ::file::file *pfileIn)
{

   try
   {

      pfileOut->from(pfileIn);

   }
   catch (...)
   {

      return false;

   }

   return true;

}


bool file_context::is_read_only(const ::file::path &psz)
{

#ifdef WINDOWS_DESKTOP

   u32 dwAttrib = windows_get_file_attributes(psz);

   if (dwAttrib & FILE_ATTRIBUTE_READONLY)
   {

      return true;

   }

   return false;

#elif defined(_UWP)

   __throw(todo());

#else

   struct stat st;

   if (stat(psz, &st) != 0)
      return true;

   return !(st.st_mode & S_IWUSR);

#endif

}


::file::path file_context::sys_temp(const ::file::path &lpszName, const char *pszExtension)
{


   string strTempDir = ::dir::sys_temp();

   if (!::str::ends(strTempDir, "\\") && !::str::ends(strTempDir, "/"))
   {

      strTempDir += "\\";

   }

   string str;

   char buf[30];

   for (i32 i = 0; i < 1000; i++)
   {

      sprintf(buf, "%d", i);

      str = strTempDir;
      str += lpszName;
      str += "-";
      str += buf;
      str += ".";
      str += pszExtension;

      if (!exists(str))
      {

         return str;

      }

   }

   return "";

}


::file::path file_context::sys_temp_unique(const ::file::path &lpszName)
{

   return ::dir::sys_temp() / lpszName;

}


file_pointer file_context::time_square_file(const string &pszPrefix, const string &pszSuffix)
{

   return get(time_square(pszPrefix, pszSuffix));

}


file_pointer file_context::get(const ::file::path &name)
{

   Context.dir().mk(name.name());

   file_pointer fileOut = get_file(name, ::file::e_open_create | ::file::e_open_binary | ::file::e_open_write);

   if (fileOut.is_null())
   {

      throw ::file::exception(error_file_not_found, -1L, -1, name);

   }

   return fileOut;

}


::file::path file_context::replace_extension(const ::file::path &pszFile, const char *pszExtension)
{

   ::file::path strFile(pszFile);

   set_extension(strFile, pszExtension);

   return strFile;

}


void file_context::set_extension(::file::path &strFile, const char *pszExtension)
{

   strsize iEnd = strFile.reverse_find('.');

   if (iEnd < 0)
   {

      iEnd = strFile.get_length();

   }

   strFile = strFile.Left(iEnd) + ::str::has_char(pszExtension, ".");

}


void file_context::normalize(string &str)
{
   if (str.is_empty())
   {

      return;

   }

   while (str.has_char() &&
          (str.Right(1) == "\\" ||
           str.Right(1) == "/"))
   {
      str = str.Left(str.get_length() - 1);
   }
}


i32 file_context::cmp(const ::file::path &psz1, const ::file::path &psz2)
{
   string str1(psz1);
   normalize(str1);
   string str2(psz2);
   normalize(str2);
   return str1.compare_ci(str2);
}


::status::result file_context::rename(const ::file::path &pszNew, const ::file::path &psz)
{

   ::file::path strDir = psz.folder();

   ::file::path strDirNew = pszNew.folder();

   if (strDir != strDirNew)
   {

      // rename should work only on files in the same directory/folder

      return ::error_failed;

   }

   if (move(pszNew, psz).failed())
   {

      return ::error_failed;

   }

   return ::success;

}


//void file_context::dtf(const ::file::path & pszFile, const ::file::path & pszDir)
//{
//
//   ::file::listing ls;
//
//   Context.dir().rls(ls, pszDir);
//
//   dtf(pszFile, ls);
//
//}
//
//
//void file_context::dtf(const ::file::path & pszFile, ::file::patha & stra)
//{
//
//   file_pointer spfile = get_file(pszFile, ::file::e_open_create | ::file::e_open_write | ::file::e_open_binary);
//
//   if (spfile.is_null())
//   {
//
//      __throw(::exception::exception("failed"));
//
//   }
//
//   string strVersion;
//
//   strVersion = "fileset v1";
//
//   //MD5_CTX ctx;
//
//   write_gen_string(spfile, nullptr, strVersion);
//
//   __pointer(::file::file) pfile2;
//
//   __construct(pfile2);
//
//   memsize iBufSize = 1024 * 1024;
//
//   memsize uRead;
//
//   memory buf;
//
//   buf.set_size(iBufSize);
//
//   string strMd5 = "01234567012345670123456701234567";
//
//   u64 iPos;
//
//   for (i32 i = 0; i < stra.get_size(); i++)
//   {
//      if (::str::ends_ci(stra[i], ".zip"))
//      {
//      }
//      else if (Context.dir().is(stra[i]))
//         continue;
//      write_n_number(spfile, nullptr, 1);
//      iPos = spfile->get_position();
//      write_gen_string(spfile, nullptr, strMd5);
//      MD5_Init(&ctx);
//      string strRelative = stra[i].relative();
//      write_gen_string(spfile, &ctx, strRelative);
//      if (pfile2->open(stra[i], ::file::e_open_read | ::file::e_open_binary).failed())
//         __throw(::exception::exception("failed"));
//      write_n_number(spfile, &ctx, (i32)pfile2->get_size());
//      while ((uRead = pfile2->read(buf, iBufSize)) > 0)
//      {
//         spfile->write(buf, uRead);
//         MD5_Update(&ctx, buf, (size_t)uRead);
//      }
//      spfile->seek(iPos, ::file::seek_begin);
//      strMd5 = __str(ctx);
//      write_gen_string(spfile, nullptr, strMd5);
//      spfile->seek_to_end();
//
//   }
//
//   write_n_number(spfile, nullptr, 2);
//
//}
//
//
//void file_context::ftd(const ::file::path & pszDir, const ::file::path & pszFile)
//{
//
//   string strVersion;
//
//   file_pointer spfile = get_file(pszFile, ::file::e_open_read | ::file::e_open_binary);
//
//   if (spfile.is_null())
//      __throw(::exception::exception("failed"));
//
//   read_gen_string(spfile, nullptr, strVersion);
//
//   i64 n;
//
//   string strRelative;
//   string strMd5;
//   string strMd5New;
//   i32 iBufSize = 1024 * 1024;
//   memory buf;
//   buf.set_size(iBufSize);
//   i64 iLen;
//   MD5_CTX ctx;
//
//   auto pfile2 = __create < ::file::file >();
//
//   memsize uRead;
//
//   if (strVersion == "fileset v1")
//   {
//      while (true)
//      {
//         read_n_number(spfile, nullptr, n);
//         if (n == 2)
//            break;
//         read_gen_string(spfile, nullptr, strMd5);
//         MD5_Init(&ctx);
//         read_gen_string(spfile, &ctx, strRelative);
//         ::file::path strPath = ::file::path(pszDir) / strRelative;
//         Context.dir().mk(strPath.folder());
//         if (pfile2->open(strPath, ::file::e_open_create | ::file::e_open_binary | ::file::e_open_write).failed())
//            __throw(::exception::exception("failed"));
//         read_n_number(spfile, &ctx, iLen);
//         while (iLen > 0)
//         {
//            uRead = spfile->read(buf, (::u32)(min(iBufSize, iLen)));
//            if (uRead == 0)
//               break;
//            pfile2->write(buf, uRead);
//            MD5_Update(&ctx, buf, (size_t)uRead);
//            iLen -= uRead;
//         }
//         pfile2->close();
//         strMd5New = __str(ctx);
//         if (strMd5 != strMd5New)
//            __throw(::exception::exception("failed"));
//      }
//   }
//
//}




//void file_context::write_n_number(::file::file * pfile, void * pctx, i64 iNumber)
//{
//
//   string str;
//
//   str.Format("%I64dn", iNumber);
//
//   pfile->write((const char *)str);
//
//   if (pctx != nullptr)
//   {
//
//      MD5_Update((MD5_CTX *)pctx, (const char *)str, (i32)str.get_length());
//
//   }
//
//}


//void file_context::read_n_number(::file::file * pfile, void * pctx, i64 & iNumber)
//{
//
//   u64 uRead;
//
//   string str;
//
//   char ch;
//
//   while ((uRead = pfile->read(&ch, 1)) == 1)
//   {
//
//      if (ch >= '0' && ch <= '9')
//         str += ch;
//      else
//         break;
//
//      if (pctx != nullptr)
//      {
//         MD5_Update((MD5_CTX *)pctx, &ch, 1);
//      }
//
//   }
//
//   if (ch != 'n')
//      __throw(::exception::exception("failed"));
//
//   if (pctx != nullptr)
//   {
//      MD5_Update((MD5_CTX *)pctx, &ch, 1);
//   }
//
//   iNumber = ::str::to_i64(str);
//
//}

//void file_context::write_gen_string(::file::file * pfile, void * pctx, string & str)
//{
//   ::count iLen = str.get_length();
//   write_n_number(pfile, pctx, iLen);
//   pfile->write((const char *)str);
//   if (pctx != nullptr)
//   {
//      MD5_Update((MD5_CTX *)pctx, (const char *)str, (i32)str.get_length());
//   }
//}

//void file_context::read_gen_string(::file::file * pfile, void * pctx, string & str)
//{
//   i64 iLen;
//   read_n_number(pfile, pctx, iLen);
//   char * psz = str.get_string_buffer((strsize)(iLen + 1));
//
//   pfile->read(psz, (memsize)iLen);
//
//   if (pctx != nullptr)
//   {
//      i64 iProcessed = 0;
//      while (iLen - iProcessed > 0)
//      {
//         i32 iProcess = (i32)min(1024 * 1024, iLen - iProcessed);
//         MD5_Update((MD5_CTX *)pctx, &psz[iProcessed], iProcess);
//
//         iProcessed += iProcess;
//      }
//   }
//   psz[iLen] = '\0';
//
//   str.release_string_buffer();
//}


bool
file_context::resolve_link(::file::path &pathTarget, const string &strSource, string *pstrDirectory, string *pstrParams)
{

   return Context.os().resolve_link(pathTarget, strSource, pstrDirectory, pstrParams);

}


string file_context::get_hash(const payload &varFile, enum_hash ehash)
{

   auto pfile = get_file(varFile, ::file::e_open_binary | ::file::e_open_read);

   if (!pfile)
   {

      return "";

   }

   memory mem;

   mem.set_size(1024 * 256);

   auto phasher = System.crypto().create_hasher(ehash);

   memsize iRead;

   while ((iRead = (memsize) pfile->read(mem.get_data(), mem.get_size())) > 0)
   {

      phasher->update({mem.get_data(), iRead});

   }

   return ::hex::upper_from(phasher->get_hash_and_reset());

}


string file_context::md5(const payload &varFile)
{

   return get_hash(varFile, e_hash_md5);

}


string file_context::nessie(const payload &varFile)
{

   __throw(todo("nessie"));

   return "";

   //auto pfile = get_file(varFile, ::file::e_open_binary | ::file::e_open_read);

   //if (!pfile)
   //{

   //   return "";

   //}

   //memory mem;

   //mem.set_size(1024 * 256);

   //WHIRLPOOL_CTX ns;

   //WHIRLPOOL_Init(&ns);

   //memsize iRead;

   //while ((iRead = (memsize)pfile->read(mem.get_data(), mem.get_size())) > 0)
   //{

   //   WHIRLPOOL_Update(&ns, mem.get_data(), (size_t)iRead);

   //}

   //return __str(ns);

}


bool file_context::get_last_write_time(filetime_t *pfiletime, const string &strFilename)
{

   __throw(interface_only_exception());

}


::e_status file_context::init_system()
{

   auto estatus = System.m_pfilesystem->update_module_path();

   if (!estatus)
   {

      return estatus;

   }

   return ::success;

}


::e_status file_context::init_context()
{

   return ::success;

}


//bool file_context::prepare_output(::stream & outputstream, path & pathDownloading, const ::stream & os)
//{

//   Sys(pobject).dir().mk(pathOut.folder());

//   file_pointer fileOut;

//   i64 iTry = 0;

//   ::apex::application * papp = ::get_context_application(pobject);

//   while (true)
//   {

//      pathDownloading = pathOut + ".downloading." + ::str::zero_pad(__str(iTry), 20);

//      fileOut = papp->file().get_file(pathDownloading, ::file::e_open_defer_create_directory | ::file::e_open_create | ::file::e_open_binary | ::file::e_open_write);

//      if (fileOut.is_set())
//      {

//         break;

//      }

//      iTry++;

//   }

//   os.m_spfile = fileOut;

//   if (os.m_spfile.is_null())
//   {

//      return false;

//   }

//   return true;

//}

//bool file_context::prepare_input(::stream & is, const path & pathIn)
//{

//   file_pointer fileIn = Sess(pobject).file().get_file(pathIn, ::file::e_open_binary | ::file::e_open_read);

//   if (fileIn.is_null())
//   {

//      return false;

//   }

//   return prepare_input(is, fileIn);

//}

//bool file_context::prepare_input(::stream & is, ::file::file * pfileIn)
//{

//   is.m_spfile = pfileIn;

//   if (is.m_spfile.is_null())
//   {

//      return false;

//   }

//   return prepare_input(is);

//}


//bool file_context::prepare_input(::stream & is)
//{

//   if (is.m_spfile.is_null())
//   {

//      return false;

//   }

//   return true;

//}


bool file_context::post_output(::file::path pathOut, ::file::path pathDownloading)
{

   try
   {

      if (rename(pathOut, pathDownloading))
      {

         TRACE("Failed to rename \"downloading\" file from %s to %s", pathDownloading.c_str(), pathOut.c_str());

         del(pathDownloading);

         return false;

      }

   }
   catch (...)
   {

      return false;

   }

   return true;

}


file_result file_context::file_get_file(::file::path path, const ::file::e_open &eopenFlags)
{

   file_pointer pfile;

   __construct(pfile);

   try
   {

      auto resultstatus = pfile->open(path, eopenFlags);

      if (resultstatus)
      {

         return pfile;

      }
      else
      {

         return resultstatus;

      }

   }
   catch (const ::exception_pointer &pe)
   {

      return pe;

   }
   catch (...)
   {

   }

   return ::error_failed;

}


file_result file_context::data_get_file(string strData, const ::file::e_open &eopenFlags)
{

   ASSERT(strData.begins_ci("data:"));

   string strSample = strData.Left(4096);

   strsize iFind = strSample.find(";", 5);

   if (iFind > 5)
   {

      strsize iEncoding1 = strSample.find(",", iFind + 1);

      strsize iEncoding2 = strSample.find(";", iFind + 1);

      strsize iEncoding = min_non_neg(iEncoding1, iEncoding2);

      if (iFind > 5 && iEncoding > iFind)
      {

         string strMimeType = strData.Mid(5, iFind - 5);

         string strEncoding = strData.Mid(iFind + 1, iEncoding - iFind - 1);

         if (strEncoding.compare_ci("base64") == 0)
         {

            __pointer(memory_file) pmemoryfile = __new(memory_file());

            if (System.base64().decode(*pmemoryfile->get_primitive_memory(), strData.Mid(iEncoding + 1)))
            {

               TRACE("::file::file_context::data_get_file Succeeded");

               return pmemoryfile;

            }

         }

      }

   }

   TRACE("::file::file_context::data_get_file Failed");

   return ::error_failed;

}


file_result file_context::zip_get_file(::file::file *pfile, const ::file::e_open &eopenFlags)
{

   auto pinfile = __new(zip::in_file);

   if (pinfile.is_set())
   {

      if (pinfile->unzip_open(pfile))
      {

         TRACE("::file::file_context::zip_get_file Succeeded");

         return pinfile;

      }

   }

   TRACE("::file::file_context::zip_get_file Failed");

   return nullptr;

}


file_result file_context::http_get_file(const payload &varFile, const ::file::e_open &eopenFlags)
{

   if (eopenFlags & (::file::e_open_write | ::file::e_open_truncate | ::file::e_open_create))
   {

      return ::error_invalid_argument;

   }

   ::file::path path = varFile.get_file_path();

   ::url_domain domain;

   domain.create(System.url().get_server(path));

   bool bSaveCache = domain.m_strRadix != "ca2" || !::str::begins(System.url().get_object(path), astr.MatterUri);

   ::file::path pathCache;

   if (bSaveCache)
   {

      pathCache = path;

      if (::str::ends(pathCache, "en_us_international.xml"))
      {
         TRACE("Debug Here");
      }

      if (::str::ends(pathCache, "text_select.xml"))
      {
         TRACE("Debug Here");
      }

      if (::str::ends(pathCache, "arialuni.ttf"))
      {
         TRACE("Debug Here : arialuni.ttf");
      }

#ifdef WINDOWS
      pathCache.replace("://", "_\\");
      pathCache.replace("?", "_");
      pathCache.replace(":", "_");
#else
      pathCache.replace("://", "_/");
#endif
      pathCache = Context.dir().cache() / pathCache + ".local_copy";

   }

   if (while_pred_Sleep(60 * 1000, [&]()
   {

      sync_lock sl(Context.http().m_pmutexDownload);

      return Context.http().m_straDownloading.contains(path) || Context.http().m_straExists.contains(path);

   }).failed())
   {

      bSaveCache = false;

   }


   {

      sync_lock sl(Context.http().m_pmutexDownload);

      if (!(path & ::file::e_flag_bypass_cache) && ::file_exists(pathCache))
      {

         sl.unlock();

         auto pfile = file_get_file(pathCache, eopenFlags);

         if (pfile)
         {

            return pfile;

         }

      }

   }

   if (bSaveCache)
   {

      sync_lock sl(Context.http().m_pmutexDownload);

      Context.http().m_straDownloading.add(path);

   }

   property_set set = varFile["http_set"].propset();

   auto pmemoryfile = create_memory_file();

   if (!Context.http().get(pmemoryfile->get_primitive_memory(), path, set))
   {

      return ::error_failed;

   }

   if (bSaveCache)
   {

      sync_lock sl(Context.http().m_pmutexDownload);

      try
      {

         pmemoryfile->seek_begin();

         auto pfileOut = Context.file().get_writer(pathCache);

         transfer(pfileOut, pmemoryfile);

      }
      catch (...)
      {

      }

      try
      {

         Context.http().m_straDownloading.remove(path);

      }
      catch (...)
      {

      }

      pmemoryfile->seek_begin();

   }

   return pmemoryfile;

}

::file_result file_context::shared_reader(const payload &varFile, const ::file::e_open &eopenFlags)
{

   return get_reader(varFile, eopenFlags | ::file::e_open_share_deny_none);

}


::file_result file_context::get_reader(const payload &varFile, const ::file::e_open &eopenFlags)
{

   ::file_result preader;

   if (varFile.m_etype == ::e_type_element)
   {

      preader = varFile.cast<::file::file>();

   }

   if (!preader)
   {

      preader = get_file(varFile, eopenFlags | ::file::e_open_read);

   }

   return preader;

}


::file_result file_context::get_writer(const payload &varFile, const ::file::e_open &eopenFlags)
{

   ::file_result pwriter;

   if (varFile.m_etype == ::e_type_element)
   {

      pwriter = varFile.cast<::file::file>();

   }

   if (!pwriter)
   {

      pwriter = get_file(varFile, eopenFlags);

   }

   return pwriter;

}


file_result file_context::get_file(const payload &varFile, const ::file::e_open &eopenFlags)
{

   try
   {

      ::file_pointer pfile;

      if (varFile.get_type() == ::e_type_element)
      {

         pfile = varFile.cast<::file::file>();

         if (pfile.is_set())
         {

            return pfile;

         }

      }
      else if (varFile.get_type() == ::e_type_propset)
      {

         if (varFile.has_property("file"))
         {

            pfile = varFile.propset()["file"].cast<::file::file>();

            if (pfile.is_set())
            {

               return pfile;

            }

         }

      }

      ::file::path path = varFile.get_file_path();

      if (path.begins_ci("data:"))
      {

         return data_get_file(path);

      }

      if (path.contains("yesno.xhtml"))
      {

         output_debug_string("test");

      }

      if (!(path & ::file::e_flag_required) &&
          varFile.is_property_true("required"))
      {

         path |= ::file::e_flag_required;

      }

      if (!(path & ::file::e_flag_bypass_cache)
          && ((eopenFlags & ::file::e_open_no_cache) || varFile.is_property_true("nocache")))
      {

         path |= ::file::e_flag_bypass_cache;

      }

      path = Context.defer_process_path(path);

      if (path.is_empty())
      {

         TRACE("::file::file_context::get_file file with empty name!!");

         return ::error_file_not_found;

      }
      else if (::thread_is_set(id_thread_zip_is_dir) && (::str::find_file_extension("zip:", path) >= 0))
      {

         auto pfile = get_reader(path);

         return zip_get_file(pfile.m_p, eopenFlags);

      }
      else if (::str::begins_eat(path, "file:///") || ::str::begins_eat(path, "file:\\\\\\"))
      {

         return get_file(path, eopenFlags);

      }
      else if (::str::begins_eat(path, "resource://") || ::str::begins_eat(path, "resource:\\\\"))
      {

#ifdef WINDOWS_DESKTOP

         auto pfile = create_memory_file();

         int iId = atoi(path);
         string strExtension = path.final_extension();

         strExtension.make_upper();
         const char *psz = strExtension;
         if (strExtension == "HTML")
         {

            psz = (const char *) RT_HTML;

         }

         if (read_resource_as_memory(*pfile->get_primitive_memory(), System.m_hinstance, iId, psz))
         {

            return pfile;

         }

#else

         throw_todo();

#endif

      }
      else if (::str::begins(path, "http://") || ::str::begins(path, "https://"))
      {

         return http_get_file(varFile, eopenFlags);

      }
      else
      {
         //else if (::str::begins_eat_ci(path, "matter://"))
         //{

         //   __pointer(::apex::application) pappLookup;

         //   string strApp = System.url().get_server("matter://" + strPath);

         //   if (strApp == papp->m_strAppName)
         //   {

         //      strPath = System.url().get_object("matter://" + strPath).Mid(1);

         //      spfile = App(papp).alloc(__type(::file::binary_file));

         //      ::status::result = spfile->open(App(papp).dir().matter(strPath), nOpenFlags);

         //   }
         //   else if (&Session != nullptr && psession->appptra().lookup(strApp, pappLookup))
         //   {

         //      spfile = App(pappLookup).file().get_file("matter://" + strPath, nOpenFlags, &::status::result);

         //   }
         //   else
         //   {

         //      strPath = App(papp).dir().matter(strPath);

         //      strPath = Sys(papp).get_matter_cache_path(strPath);

         //      spfile = get_file(strPath, nOpenFlags, &::status::result);

         //   }

         //}
         //else
         //{

         //   //  return nullptr;




         //   /*            if((nOpenFlags & ::file::e_open_create) == 0 && !exists(strPath))
         //   {
         //   TRACE("::application::file does not exist!! : \"%s\"",strPath);
         //   return spfile;
         //   }
         //   */

         //if (nOpenFlags & ::file::e_open_text)
         //{

         //   pfile = __new(::file::stdio_file(pobject));

         //}
         //else

         if (eopenFlags & ::file::e_open_text)
         {

            pfile = __create_new<::stdio_file>();

         }

         auto eopen = eopenFlags;

         if (!pfile)
         {

            if (eopen & ::file::e_open_text)
            {

               eopen -= ::file::e_open_text;

            }

            if (!(eopen & ::file::e_open_binary))
            {

               eopen += ::file::e_open_binary;

            }

            __construct(pfile);

         }

         auto result = pfile->open(path, eopen);

         if (result)
         {

            return pfile;

         }
         else
         {

            return result;

         }

      }

      return pfile;

   }
   catch (...)
   {

   }

   return ::error_io;

}


//bool file_context::transfer(::file::file * pfileOut, ::file::file * pfileIn)
//{
//
//   return transfer(this, pfileOut, pfileIn);
//
//}


//bool file_context::transfer(const path & pszOutput, ::file::file * pfileIn)
//{

//   return output(pszOutput, this, &file_context::transfer, pfileIn);

//}


//bool file_context::transfer(const path & pszOutput, ::stream & istream)
//{

//   return output(pszOutput, this, &file_context::transfer, istream);

//}


//bool file_context::transfer(file * pfileOut, const path & pszSource)

//{

//   return output(pfileOut, this, &file_context::transfer, pszSource);


//}


//bool file_context::transfer(file * pfileOut, ::file::file * pfileIn)
//{

//   return output(pfileOut, this, &file_context::transfer, pfileIn);

//}


//bool file_context::transfer(file * pfileOut, ::stream & istream)
//{

//   return output(pfileOut, this, &file_context::transfer, istream);

//}


//bool file_context::transfer(::stream & os, const path & pszSource)

//{

//   return output(os, this, &file_context::transfer, pszSource);


//}


//bool file_context::transfer(::stream & os, ::file::file * pfileIn)
//{

//   return output(os, this, &file_context::transfer, pfileIn);

//}


//bool file_context::transfer(::stream & os, ::stream & istream)
//{

//   return output(os, this, &file_context::transfer, istream);

//}

//bool file_context::transfer(::object* ::stream& os, ::file::file & reader)
//{

//   return output(os, this, &file_context::transfer, preader);

//}

//bool file_context::transfer(::stream & ostream, ::stream & istream)
//{
//   class memory memory;
//   memory.set_size(1024 * 256);
//   memsize  uRead;
//   while ((uRead = istream.read(memory, memory.get_size())) > 0)
//   {
//      ostream.write(memory, uRead);
//   }
//   return true;
//}


bool file_context::is_link(string strPath)
{

   return false;

}


::file::path file_context::dropbox_info_json()
{

   ::file::path pathJson;

   pathJson = ::dir::home() / ".dropbox/info.json";

   return pathJson;

}


::file::path file_context::onedrive_global_ini()
{

   ::file::path pathGlobalIni;

   pathGlobalIni = ::dir::roaming() / "OneDrive/settings/Personal/global.ini";

   return pathGlobalIni;

}


::file::path file_context::onedrive_cid_ini()
{

   ::file::path pathGlobalIni = onedrive_global_ini();

   string strIni = file_as_string(pathGlobalIni);

   if (strIni.is_empty())
   {

      return "";

   }

   ::property_set set;

   set.parse_ini(strIni);

   string strCid = set["cid"];

   ::file::path pathIni = ::dir::roaming() / "OneDrive/Settings/Personal/" + strCid + ".ini";

   return pathIni;

}
//
//::status::result file_context::copy(payload varTarget, payload varSource, bool bFailIfExists, e_extract eextract)
//{
//
//   return System.m_spfile->copy(varTarget, varSource, bFailIfExists, eextract, get_context_application());
//
//}

//
//::status::result file_context::move(const ::file::path & pszNew, const ::file::path & pszOld)
//{
//
//   return System.m_spfile->move(pszNew, pszOld, get_context_application());
//
//}

//
//::status::result file_context::del(const ::file::path & psz)
//{
//   return System.m_spfile->del(psz, get_context_application());
//}

//::status::result file_context::rename(const ::file::path & pszNew, const ::file::path & pszOld)
//{
//   return System.m_spfile->rename(pszNew, pszOld, get_context_application());
//}

//void file_context::trash_that_is_not_trash(const ::file::path & psz)
//{
//   return System.m_spfile->trash_that_is_not_trash(psz, get_context_application());
//}
//
//void file_context::trash_that_is_not_trash(::file::patha & stra)
//{
//   return System.m_spfile->trash_that_is_not_trash(stra, get_context_application());
//}

//::status::result file_context::replace(const ::file::path & pszContext, const string & pszFind, const string & pszReplace)
//{
//   return System.m_spfile->replace(pszContext, pszFind, pszReplace, get_context_application());
//}


//bool file_context::exists(const ::file::path & pszPath)
//{
//
//   return System.m_spfile->exists(pszPath, get_context_application());
//
//}


bool file_context::is_file_or_dir(const ::file::path &pszPath, ::file::enum_type *petype)
{

   return is_file_or_dir(pszPath, nullptr, petype);

}


/*  bool file_context::exists(const string & strPath)
   {

      return System.m_spfile->exists(strPath, get_context_application());

   }

   bool file_context::exists(const payload & payload)
   {

      const string & strPath = payload.get_string();


      return System.m_spfile->exists(strPath, get_context_application());

   }*/


//payload file_context::length(const ::file::path & pszPath)
//{
//
//   return System.m_spfile->length(pszPath, get_context_application());
//
//}


//payload file_context::length(const string & strPath)
//{


//   return System.m_spfile->length(strPath, get_context_application());

//}


//payload file_context::length(const payload & payload)
//{

//   return System.m_spfile->length(payload.get_string(), get_context_application());

//}

//
//::file::path file_context::time(const ::file::path & pszBasePath, i32 iDepth, const string & pszPrefix, const string & pszSuffix)
//{
//
//   return System.m_spfile->time(get_context_application(), pszBasePath, iDepth, pszPrefix, pszSuffix);
//
//}


//::file::path file_context::time_square(const string & pszPrefix, const string & pszSuffix)
//{
//
//   return System.m_spfile->time_square(get_context_application(), pszPrefix, pszSuffix);
//
//}

//::file::path file_context::time_log(const string & pszId)
//{
//   return System.m_spfile->time_log(get_context_application(), pszId);
//}
//
//file_pointer file_context::time_square_file(const char * pszPrefix, const char * pszSuffix)
//{
//   return System.m_spfile->time_square_file(get_context_application(), pszPrefix, pszSuffix);
//}


//file_pointer file_context::get(const ::file::path & name)
//{
//
//   return System.m_spfile->get(name, get_context_application());
//
//}


//payload file_context::as_json(const payload & varFile)
//{
//
//   return System.m_spfile->as_json(get_context_application(), varFile);
//
//}


//string file_context::as_string(const payload & varFile)
//{
//
//   return System.m_spfile->as_string(get_context_application(), varFile);
//
//}
//
//
//bool file_context::as_memory(const payload & varFile, memory_base & mem)
//{
//
//   return System.m_spfile->as_memory(get_context_application(), varFile, mem);
//
//}

//
//void file_context::lines(string_array & stra, const payload & varFile)
//{
//
//   return System.m_spfile->lines(stra, varFile, get_context_application());
//
//}
//
//
//void file_context::put_lines(const payload & varFile, const string_array & stra)
//{
//   return System.m_spfile->put_lines(varFile, stra, get_context_application());
//}
//
//bool file_context::put_contents(const payload & varFile, const void * pvoidContents, ::count count)
//{
//   return System.m_spfile->put_contents(varFile, pvoidContents, count, get_context_application());
//}
//
//bool file_context::put_contents(const payload & varFile, const char * pcszContents)
//
//{
//   return System.m_spfile->put_contents(varFile, pcszContents, get_context_application());
//
//}
//
//
//bool file_context::add_contents(const payload & varFile, const char * pcszContents)
//{
//
//   return System.m_spfile->add_contents(varFile, pcszContents, get_context_application());
//
//}


//bool file_context::put_contents(const payload & varFile, const ::stream & stream)
//{

//   return System.m_spfile->put_contents(varFile, stream, get_context_application());

//}


//bool file_context::put_contents(const payload & varFile, memory & mem)
//{
//
//   return System.m_spfile->put_contents(varFile, mem, get_context_application());
//
//}
//
//
//bool file_context::put_contents_utf8(const payload & varFile, const char * pcszContents)
//{
//
//   return System.m_spfile->put_contents_utf8(varFile, pcszContents, get_context_application());
//
//}

//
//string file_context::sys_temp(const char * lpszName, const char * pszExtension)
//{
//   return System.m_spfile->sys_temp(lpszName, pszExtension, get_context_application());
//}


rp(::file::file) file_context::friendly_get_file(const payload &varFile, const ::file::e_open & eopenFlags)
{

   try
   {

      return get_file(varFile, eopenFlags);

   }
   catch (const ::exception_pointer &pe)
   {

      return pe;

   }
   catch (...)
   {

      return ::error_failed;

   }

}


//
//
//::file_result file_context::get_file(const payload & varFile, ::u32 nOpenFlags)
//{
//
//   return Context.file().get_file(get_context_application(), varFile, nOpenFlags);
//
//}


//
//void file_context::dtf(const ::file::path & pszFile, const ::file::path & pszDir)
//{
//
//   return System.m_spfile->dtf(pszFile, pszDir, get_context_application());
//
//}

//bool file_context::is_read_only(const path & psz)
//{
//
//   return System.m_spfile->is_read_only(psz, get_context_application());
//}


//void file_context::dtf(const ::file::path & pszFile, ::file::patha & stra, ::file::patha & straRelative)
//{
//
//   return System.m_spfile->dtf(pszFile, stra, get_context_application());
//
//}
//
//
//void file_context::ftd(const ::file::path & pszDir, const ::file::path & pszFile)
//{
//
//   return System.m_spfile->ftd(pszDir, pszFile, get_context_application());
//
//}


bool file_context::crypto_set(const payload &varFile, const char *pszData, const char *pszSalt)
{

   __throw(interface_only_exception());

   return false;

}


bool file_context::crypto_get(const payload &varFile, string &str, const char *pszSalt)
{

   __throw(interface_only_exception());

   return false;

}


bool file_context::save_lines(const payload &varFile, string_array &stra)
{

   string str = stra.implode("\n");

   put_contents_utf8(varFile, str);

   return true;

}


bool file_context::load_lines(string_array &stra, const payload &varFile)
{

   string str = as_string(varFile);

   stra.add_lines(str);

   return true;

}


//bool file_context::transfer(const path & pathOut, const path & pszSource)

//{

//   return Context.file().transfer(get_context_application(), pathOut, pszSource);


//}


//bool file_context::transfer(const path & pathOut, ::file::file * pfileIn)
//{

//   return Context.file().transfer(get_context_application(), pathOut, pfileIn);

//}


//bool file_context::transfer(const path & pathOut, ::file::file & reader)
//{

//   return Context.file().transfer(get_context_application(), pathOut, reader);

//}


//bool file_context::transfer(::file::file * pfileOut, ::file::file * pfileIn)
//{
//
//   return Context.file().transfer(get_context_application(), pfileOut, pfileIn);
//
//}


//bool file_context::transfer(file * pfileOut, ::file::file * pfileIn)
//{

//   return Context.file().transfer(get_context_application(), pfileOut, pfileIn);

//}


//bool file_context::transfer(file * pfileOut, ::file::file & is)
//{

//   return Context.file().transfer(get_context_application(), *pfileOut, is);

//}


//bool file_context::transfer(::file::file & os, const path & pszSource)
//{

//   return Context.file().transfer(get_context_application(), os, pszSource);

//}


//bool file_context::transfer(::file::file & os, ::file::file * pfileIn)
//{

//   return Context.file().transfer(get_context_application(), os, pfileIn);

//}


//bool file_context::transfer(::file::file & os, ::file::file & is)
//{

//   return Context.file().transfer(get_context_application(), os, is);

//}


bool file_context::touch(const ::file::path &path)
{

   if (!exists(path))
   {

      char ch;

      if (!put_contents(path, &ch, 0))
      {

         return false;

      }

   }

   return true;

}

//string file_context::md5(const payload & varFile)
//{
//   return System.m_spfile->md5(varFile, get_context_application());
//}

//string file_context::nessie(const payload & varFile)
//{
//   return System.m_spfile->nessie(varFile, get_context_application());
//}

//
//::file::path file_context::dropbox_info_json()
//{
//
//   return System.m_spfile->dropbox_info_json(get_context_application());
//
//}

//
//::file::path file_context::onedrive_global_ini()
//{
//
//   return System.m_spfile->onedrive_global_ini(get_context_application());
//
//}

//
//::file::path file_context::onedrive_cid_ini()
//{
//
//   return System.m_spfile->onedrive_cid_ini(get_context_application());
//
//}

//
//} // namespace windows
//
//
//



::e_status file_context::update_module_path()
{


   auto estatus = System.m_pfilesystem->update_module_path();

   if (!estatus)
   {

      return estatus;

   }

   return estatus;


}

