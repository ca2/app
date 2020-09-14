#include "framework.h"
#include "apex/os/windows_common/file_c.h"
#include "apex/machine_event2.h"
#include "apex/machine_event_central2.h"
#include <stdio.h>

#define UTF8_BOM "\xef\xbb\xbf"

#include "apex/compress/zip/zip.h"
#include "apex/const/id.h"



//#ifndef _UWP
//#include <openssl/ssl.h>
//#endif
//
//#include <openssl/md5.h>
//#include <openssl/whrlpool.h>
//
#ifndef WINDOWS
#include <sys/stat.h>
//#include <ctype.h>
#endif

//CLASS_DECL_APEX void NESSIEinit(struct NESSIEstruct * const structpointer);
//CLASS_DECL_APEX void NESSIEadd(const uchar * const source, uptr sourceBits, struct NESSIEstruct * const structpointer);
//CLASS_DECL_APEX void NESSIEfinalize(struct NESSIEstruct * const structpointer, uchar * const result);




//#ifndef _UWP
//#include <openssl/ssl.h>
//#endif


#include "apex/crypto/crypto_openssl.h"


#ifndef WINDOWS
#include <sys/stat.h>
//#include <ctype.h>
#endif


namespace file
{


   system_file::system_file()
   {
      //m_path.m_p = this;

   }


   system_file::~system_file()
   {

   }


   bool system_file::exists(::file::path path, ::object * pobject)
   {

      ::apex::application * papp = ::get_context_application(pobject);

      path = Sys(papp).defer_process_matter_path(path, papp);

      if (!(path & ::file::flag_required) && path.is_empty())
      {

         return false;

      }

      ::file::e_type etype = ::file::type_none;

      bool bExists = is_file_or_dir(path, nullptr, &etype, pobject);

      return bExists && (etype == ::file::type_file || etype == ::file::type_element);

   }


   //bool system_file::is_file_or_dir(::file::path path, ::object * pobject, ::file::e_type * petype)
   //{

   //   path = Sys(papp).defer_process_matter_path(path, papp, bOptional, bNoCache);

   //   if (bOptional && path.is_empty())
   //   {

   //      return false;

   //   }

   //   return exists(path, nullptr, papp, petype, bOptional, bNoCache);

   //}


   bool system_file::is_file_or_dir(::file::path path, var * pvarQuery, ::file::e_type * petype, ::object * pobject)
   {

      if (::str::begins(path, astr.HttpProtocol) || ::str::begins(path, astr.HttpsProtocol))
      {

         property_set set;

         if (path & ::file::flag_required)
         {

            set["required"] = true;

         }

         if (path & ::file::flag_bypass_cache)
         {

            set["nocache"] = true;

         }

         return App(pobject).http().is_file_or_dir(path, pvarQuery, petype, set);

      }

      if (::thread_is_set(id_thread_zip_is_dir))
      {

         strsize iFind = ::str::find_file_extension("zip:", path);

         ::zip::util ziputil;

         if (iFind >= 0)
         {

            if (!exists(path.Mid(0, iFind + 4), pobject))
            {

               return false;

            }

            return ziputil.is_file_or_dir(pobject, path, petype);

         }

      }

      return is_file_or_dir_dup(path, petype) != FALSE;

   }


   var system_file::length(const ::file::path & pszPath,::object * pobject)
   {

      return length(pszPath, nullptr, pobject);

   }


   var system_file::length(const ::file::path & path,var * pvarQuery,::object * pobject)
   {

      if (path.m_iSize != -1)
      {

         return MAX(0, path.m_iSize);

      }

      var varRet;

#ifdef WINDOWS

      WIN32_FILE_ATTRIBUTE_DATA data;

      if(!GetFileAttributesExW(::str::international::utf8_to_unicode(path), GetFileExInfoStandard, &data))
      {

         varRet.set_type(::type_null);

         ((::file::path &) path).m_iSize = -2;

      }
      else
      {

         varRet = (((u64)data.nFileSizeHigh) << 32) | (u64) data.nFileSizeLow;

         ((::file::path &)path).m_iSize = varRet.m_i64;

      }

#else

      struct stat stat;

      if(::stat(path, &stat)  == -1)
      {

         varRet.set_type(::type_null);

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


   ::file::path system_file::module()
   {

      return m_pathModule;

   }


   ::file::path system_file::ca2module()
   {

      return m_pathCa2Module;

   }


   ::file::path system_file::time_square(::object * pobject,const string & pszPrefix,const string & pszSuffix)
   {

      return time(pobject, Context.dir().time_square(pobject), 25, pszPrefix, pszSuffix);

   }


   ::file::path system_file::time_log(::object * pobject,const string & pszId)
   {
      return time(pobject, Context.dir().time_log(pszId), 9);
   }


   ::file::path system_file::time(::object * pobject,const ::file::path & psz,i32 iMaxLevel,const string & pszPrefix,const string & pszSuffix, bool bTryDelete)
   {

      sync_lock lockMachineEvent(!is_null(&System.machine_event_central()) ? &System.machine_event_central().m_machineevent.m_mutex : ((::mutex *) nullptr));

      i32 iIncLevel = -1;

      ::file::path str;

      ::file::path path;

      string strPrefix(pszPrefix);

      string strSuffix(pszSuffix);

restart:

      str.Empty();

      str = psz;

      Context.dir().mk(str, pobject);

      listing ls(::get_context_application(pobject));

      string strFormat;

      for(i32 i = 1; i <= iMaxLevel;)
      {

         Context.dir().mk(str, pobject);

         if (!Context.dir().is(str, pobject))
         {

            __throw(::exception::exception("time square dir does not exist"));

         }

         ls.ls(str);

         if(i < iMaxLevel)
         {

            i32 iMax = filterex_time_square("", ls);

            if(iMax == -1)
            {

               str /= "00";

               Context.dir().mk(str, pobject);

            }
            else if(iMax == 99)
            {

               iIncLevel = i - 1;

               goto restart;

            }
            else
            {

               if(i == iIncLevel)
               {

                  iMax++;

               }

               strFormat.Format("%02d", iMax);

               str /= strFormat;

               if(i == iIncLevel)
               {

                  Context.dir().mk(str, pobject);

               }

            }

            i++;

         }
         else // if i == iMaxLevel
         {

            ls.ls(str);

            i32 iMax = bTryDelete ? 0 : filterex_time_square(pszPrefix, ls);

            do
            {

               if (iMax == -1)
               {

                  path = str / (strPrefix + "00" + strSuffix);

                  if (system_file::try_create_file(path, bTryDelete))
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

                  if (system_file::try_create_file(path, bTryDelete))
                  {

                     return path;

                  }

               }

            }
            while (bTryDelete);

            return "";

         }

      }

      return str;

   }


   i32 system_file::filterex_time_square(const char * pszPrefix, ::file::patha & stra)
   {

      i32 iMax = -1;

      i32 iIndex;

      for(i32 i = 0; i < stra.get_size(); i++)
      {

         string str = stra[i].name();

         if(::str::begins_eat_ci(str, pszPrefix))
         {

            if(str.get_length() < 2)
            {

               stra.remove_at(i);

               i--;

               continue;

            }

            if(!isdigit((uchar) str[0]) || !isdigit((uchar) str[1]))
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
   bool system_file::try_create_file(const ::file::path & path, bool bTryDelete)
   {

      if (Context.file().exists(path, get_context_application()))
      {

         if (!bTryDelete)
         {

            return false;

         }

         Context.file().del(path, get_context_application());

         if (Context.file().exists(path, get_context_application()))
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

         if (pfile->open(path, ::file::mode_create | ::file::type_binary).failed())
         {

            return false;

         }

      }
      catch(...)
      {

         return false;

      }

      return true;

   }


   var system_file::as_json(::object * pobject, const var & varFile)
   {

      string str = as_string(pobject, varFile);

      if (str.is_empty())
      {

         return ::type_new;

      }

      const char * pszJson = str;

      var v;

      try
      {

         v.parse_json(pszJson);

      }
      catch (const ::exception_pointer & pe)
      {

         ::exception_pointer esp(pe);

         TRACE(esp->get_message());

         v = ::type_new;

      }
      catch (...)
      {

         TRACE("GENERAL Exception parsing json system_file::as_json : \"" + str + "\"");

         v = ::type_new;

      }

      return v;

   }


   string system_file::as_string(::object * pobject, const var & varFile)
   {

      memory memory;

      if (!as_memory(pobject, varFile, memory))
      {

         return "";

      }

      return memory.as_utf8();

   }


   bool system_file::as_memory(::object * pobject, const var & varFile, memory_base & mem)
   {

      auto pfile = get_file(pobject, varFile, ::file::share_deny_none | ::file::mode_read | ::file::type_binary);

      if (!pfile)
      {

         return false;

      }

      try
      {

         ::binary_stream reader(pfile);

         reader >> mem;

         return true;

      }
      catch(...)
      {

      }

      return false;

   }


   void system_file::put_lines(const var & varFile, const string_array & stra, ::object * pobject)
   {

      UNREFERENCED_PARAMETER(pobject);

      file_pointer spfile;

      try
      {

         spfile = App(pobject).file().get_file(varFile,::file::mode_write | ::file::mode_truncate | ::file::mode_create | ::file::defer_create_directory);

      }
      catch(...)
      {

         return;

      }

      _put_lines(spfile, stra);

   }


   void system_file::put_lines_utf8(const var & varFile, const string_array & stra, ::object * pobject)
   {

      file_pointer spfile;

      try
      {

         spfile = App(pobject).file().get_file(varFile,::file::type_text | ::file::mode_write | ::file::mode_truncate | ::file::mode_create | ::file::defer_create_directory);

      }
      catch(...)
      {

         return;

      }

      if(spfile.is_null())
      {

         return;

      }

      spfile->write(UTF8_BOM, STATIC_ASCII_STRING_LENGTH(UTF8_BOM));

      _put_lines(spfile, stra);

   }


   void system_file::_put_lines(::file::file * pfile, const string_array & stra)
   {

      if(pfile == nullptr)
      {

         return;

      }

      for(auto & strLine : stra)
      {

         pfile->write_string(strLine);

      }

   }


   void system_file::lines(string_array & stra, const var & varFile, ::object * pobject)
   {

      UNREFERENCED_PARAMETER(pobject);

      file_result pfile;

      try
      {

         pfile = App(pobject).file().get_file(varFile,::file::type_text | ::file::mode_read);

      }
      catch(...)
      {

         return;

      }

      if(!pfile)
      {

         return;

      }

      string strLine;

      while(pfile->read_string(strLine))
      {

         stra.add(strLine);

      }

   }


   bool system_file::put_contents(const var & varFile, const void * pvoidContents, ::count count, ::object * pobject)
   {

      file_result pfile;

      int iTry = 0;

retry_get_file:

      try
      {

         pfile = App(pobject).file().get_file(varFile, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::share_deny_write | ::file::defer_create_directory);

      }
      catch (::exception_pointer e)
      {

         pfile.add(e);

      }
      catch(...)
      {

         return false;

      }

      if (!pfile)
      {

         auto estatus = pfile.status();

         if (estatus == error_file_sharing_violation)
         {

            Sleep(300);

            iTry++;

            if (iTry <= 8)
            {

               goto retry_get_file;

            }

         }

         return false;

      }

      pfile->write(pvoidContents, count);

      return true;

   }


   bool system_file::add_contents(const var & varFile,const void * pvoidContents,::count count,::object * pobject)
   {

      file_pointer spfile;

      try
      {

         spfile = App(pobject).file().get_file(varFile,::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::mode_no_truncate | ::file::share_exclusive | ::file::defer_create_directory);

      }
      catch(...)
      {

         return false;

      }

      if(spfile.is_null())
         return false;


      spfile->seek_to_end();

      spfile->write(pvoidContents,count);

      return true;

   }


   bool system_file::put_contents(const var & varFile, const char * pcszContents, ::object * pobject)

   {

      if(pcszContents == nullptr)

      {

         return put_contents(varFile, "", 0, pobject);

      }
      else
      {

         string strContents(pcszContents, strlen(pcszContents));

         ::str::fix_eol(strContents);

         return put_contents(varFile, strContents, strContents.get_length(), pobject);

      }

   }


   bool system_file::add_contents(const var & varFile,const char * pcszContents,::object * pobject)

   {

      if(pcszContents != nullptr)

      {

         return add_contents(varFile,pcszContents,strlen(pcszContents), pobject);


      }

      return false;

   }


   bool system_file::put_contents(const var & varFile, ::file::file * pfile, ::object * pobject)
   {

      file_pointer spfile;

      spfile = App(pobject).file().get_file(varFile, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::share_deny_write | ::file::defer_create_directory);

      if (spfile.is_null())
      {

         return false;

      }

      memory mem;

      mem.set_size(1024 * 1024 * 8);

      memsize uiRead;

      while((uiRead = pfile->read(mem.get_data(), mem.get_size())) > 0)
      {

         spfile->write(mem.get_data(), uiRead);

      }

      return true;

   }


   bool system_file::put_contents(const var & varFile, memory & mem, ::object * pobject)
   {

      return put_contents(varFile, mem.get_data(), (count) mem.get_size(), pobject);

   }


   bool system_file::put_contents_utf8(const var & varFile, const char * pcszContents, ::object * pobject)
   {

      file_pointer spfile;

      spfile = App(pobject).file().get_file(varFile, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::share_deny_write | ::file::defer_create_directory);

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


   ::status::result system_file::copy(var varTarget, var varSource,bool bFailIfExists,e_extract eextract,::object * pobject)
   {

      ::apex::application * papp = ::get_context_application(pobject);

      if (Context.dir().is(varSource.get_file_path(), pobject) && (eextract == extract_first || eextract == extract_all || !(::str::ends_ci(varSource.get_file_path(), ".zip"))))
      {
         ::file::listing patha(papp);
         patha.rls(varSource);
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
            if (Context.dir().is(strSrc, pobject))
            {
               if ((eextract == extract_first || eextract == extract_none) && (::str::ends_ci(varSource.get_file_path(), ".zip")))
               {
               }
               else
               {
                  Context.dir().mk(strDst, pobject);
               }
            }
            else
            {
               if (!Context.dir().is(strDst.folder(), pobject))
               {
                  Context.dir().mk(strDst.folder(), pobject);
               }
               copy(strDst, strSrc, bFailIfExists, eextract == extract_all ? extract_all : extract_none, papp);
            }
         }
      }
      else
      {

         if (varTarget.get_file_path().m_epath == ::file::path_file && varSource.get_file_path().m_epath == ::file::path_file)
         {

            if (!papp->m_spdir->is(varTarget.get_file_path().folder()))
            {

               papp->m_spdir->mk(varTarget.get_file_path().folder());

            }

            if (!::file_copy_dup(varTarget, varSource, !bFailIfExists))
            {

               return ::error_failed;

            }

            return ::success;

         }

         if (bFailIfExists)
         {

            if (exists(varTarget, papp))
            {

               return ::error_failed;

            }

         }

         var varNew;

         if (Context.dir().is(varTarget, papp) && varSource.get_file_path().name().has_char())
         {

            varNew = ::file::path(varTarget) / varSource.get_file_path().name();

         }
         else
         {

            varNew = varTarget;

         }

         file_pointer ofile;
         
         ofile = App(papp).file().get_file(varNew, ::file::mode_write | ::file::type_binary | ::file::mode_create | ::file::defer_create_directory | ::file::share_deny_write);

         if (ofile.is_null())
         {
            string strError;
            strError.Format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open output file", varSource.get_file_path().c_str(), varNew.get_file_path().c_str(), bFailIfExists);
            __throw(io_exception(strError));
         }

         bool bGeneralFailure = false;

         bool bOutputFail = false;
         bool bInputFail = false;
         try
         {

            auto ifile = App(papp).file().get_reader(varSource, ::file::mode_read | ::file::type_binary | ::file::share_deny_none);

            if (!ifile)
            {
               string strError;
               strError.Format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open input file", varSource.get_file_path().c_str(), varNew.get_file_path().c_str(), bFailIfExists);
               __throw(io_exception(strError));
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

                  pfileInput->GetStatus(st);

               }
               catch (...)
               {

                  bStatusFail = true;

                  TRACE("During copy, failed to get status from input file \"%s\" bFailIfExists=%d", varSource.get_file_path().c_str(), bFailIfExists);

               }

               if (!bStatusFail)
               {
                  try
                  {

                     pfileInput->GetStatus(st);

                  }
                  catch (...)
                  {

                     bStatusFail = true;

                     TRACE("During copy, failed to set status to output file \"%s\" bFailIfExists=%d", varTarget.get_file_path().c_str(), bFailIfExists);

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
               strError.Format("During copy, failed to close both input file \"%s\" and output file \"%s\" bFailIfExists=%d", varSource.get_file_path().c_str(), varTarget.get_file_path().c_str(), bFailIfExists);
               __throw(io_exception(strError));
            }
            else
            {
               string strError;
               strError.Format("During copy, failed to close input file \"%s\" bFailIfExists=%d", varSource.get_file_path().c_str(), bFailIfExists);
               __throw(io_exception(strError));
            }
         }
         else if (bOutputFail)
         {
            string strError;
            strError.Format("During copy, failed to close output file \"%s\" bFailIfExists=%d", varTarget.get_file_path().c_str(), bFailIfExists);
            __throw(io_exception(strError));
         }

      }

      return ::success;

   }











   ::status::result system_file::move(const ::file::path & pszNew,const ::file::path & psz,::object * pobject)
   {

#ifdef WINDOWS_DESKTOP

      if (!::MoveFileW(
            ::str::international::utf8_to_unicode(psz),
            ::str::international::utf8_to_unicode(pszNew)))
      {

         u32 dwError = ::get_last_error();

         if (dwError == ERROR_ALREADY_EXISTS)
         {

            if (::CopyFileW(
                  ::str::international::utf8_to_unicode(psz),
                  ::str::international::utf8_to_unicode(pszNew),
                  FALSE))
            {

               if (!::DeleteFileW(::str::international::utf8_to_unicode(psz)))
               {

                  dwError = ::get_last_error();

                  string strError;

                  strError.Format("Failed to delete the file to move \"%s\" error=%d", psz, dwError);

                  TRACE("%s", strError);

               }

               return ::success;

            }

            dwError = ::get_last_error();

         }

         string strError;

         strError.Format("Failed to move file \"%s\" to \"%s\" error=%d", psz, pszNew, dwError);

         __throw(io_exception(strError));

      }

#elif defined(_UWP)

      ::Windows::Storage::StorageFile ^ file = get_os_file(psz,  0, 0, nullptr, OPEN_EXISTING, 0, nullptr);

      if (file == nullptr)
      {

         output_debug_string("test");

         __throw(::exception::exception("file::system_file::move Could not move file, could not open source file"));

      }

      string strDirOld     = psz.folder();
      string strDirNew     = pszNew.folder();
      string strNameOld    = psz.name();
      string strNameNew    = pszNew.name();

      if(strDirOld == strDirNew)
      {
         if(strNameOld == strNameNew)
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
         if(strNameOld == strNameNew)
         {
            ::wait(file->MoveAsync(folder));
         }
         else
         {
            ::wait(file->MoveAsync(folder, strNameNew));
         }
      }


#else
      if(::rename(psz, pszNew) != 0)
      {
         i32 err = errno;
         string strError;
         strError.Format("Failed to delete file error=%d", err);
         __throw(::exception::exception(strError));
      }
#endif

      return ::success;

   }










   ::status::result system_file::del(const ::file::path & psz,::object * pobject)
   {


#ifdef WINDOWS_DESKTOP

      HANDLE h = ::CreateFileW(::str::international::utf8_to_unicode(string("\\\\?\\") + psz), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_DELETE_ON_CLOSE, nullptr);

      if (h == INVALID_HANDLE_VALUE)
      {
         u32 dwError = ::get_last_error();
         if (dwError == 2) // the file does not exist, so delete "failed"
            return ::success;
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

      if (remove(psz) != 0)
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


   ::file::path system_file::duplicate(const ::file::path & psz,::object * pobject)
   {
      string strCopy("copy");
      string strNew;
      if(Context.dir().is(psz, pobject))
      {
         i32 i = 1;
         while( i <= 100)
         {
            strNew.Format("%s-%s-%d", psz.c_str(), strCopy.c_str(), i);
            if(!exists(strNew, pobject))
            {
               copy(strNew, psz, false, extract_all, pobject);
               return strNew;
            }
            i++;
         }
      }
      else
      {
         string strExt = psz.ext();
         if(!strExt.is_empty())
         {
            strExt = "-" + strExt;
         }
         i32 i = 1;
         while( i <= 100)
         {
            strNew.Format("%s-%s-%d%s", psz.c_str(), strCopy.c_str(), i, strExt.c_str());
            if(!exists(strNew, pobject))
            {
               copy(strNew, psz, false, extract_all, pobject);
               return strNew;
            }
            i++;
         }
      }
      return "";
   }



   ::file::path system_file::paste(const ::file::path & pathLocation,const ::file::path & path,::object * pobject)
   {

      ::file::path pathDir = path.folder();

      ::file::path pathDst = pathLocation;

      ::file::path pathSrc = pathDir;

      if (pathDst == pathSrc)
      {

         return duplicate(path, pobject);

      }
      else
      {

         ::file::path pathNew = pathDst / path.name();

         copy(pathNew, path, false, extract_all, pobject);

         return pathNew;

      }

   }



   void system_file::trash_that_is_not_trash(::file::patha & stra, ::object * pobject)
   {

      if (stra.get_size() <= 0)
      {

         return;

      }

      ::file::path strDir = Context.dir().trash_that_is_not_trash(stra[0]);

      Context.dir().mk(strDir, pobject);

      for (i32 i = 0; i < stra.get_size(); i++)
      {

         move(strDir / stra[i].name(), stra[i], pobject);

      }

   }




   void system_file::trash_that_is_not_trash(const ::file::path & psz,::object * pobject)
   {

      ::file::path strDir = Context.dir().trash_that_is_not_trash(psz);

      Context.dir().mk(strDir, pobject);

      move(strDir / psz.name(), psz, pobject);

   }




   bool system_file::get_status(const ::file::path & path, ::file::file_status & status, ::object * pobject)
   {

      UNREFERENCED_PARAMETER(path);
      UNREFERENCED_PARAMETER(status);
      __throw(interface_only_exception());

   }


   ::status::result system_file::set_status(const ::file::path & path, const ::file::file_status & status, ::object * pobject)
   {

      UNREFERENCED_PARAMETER(path);
      UNREFERENCED_PARAMETER(status);
      __throw(interface_only_exception());

   }


   ::status::result system_file::replace(const ::file::path & pszContext,const string & pszFind,const string & pszReplace,::object * pobject)
   {

      ::status::result e;

      ::file::listing straTitle(::get_context_application(pobject));
      straTitle.ls(pszContext);
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
            e.add(move(pathContext / strNew, pathContext / strOld, pobject));

         }

      }
      //if (strFail.has_char())
      //{
      //   App(papp).message_box(nullptr, strFail, MB_ICONEXCLAMATION);
      //}

      return e;


   }


   bool system_file::transfer(::object* pobject, ::file::file* pfileOut, ::file::file* pfileIn)
   {

      try
      {

         pfileOut->transfer_from(pfileIn);

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   bool system_file::is_read_only(const ::file::path & psz, ::object * pobject)
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

      if(stat(psz, &st) != 0)
         return true;

      return !(st.st_mode & S_IWUSR);

#endif

   }


   ::file::path system_file::sys_temp(const ::file::path & lpszName, const char * pszExtension, ::object * pobject)
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

         if (!exists(str, pobject))
         {

            return str;

         }

      }

      return "";

   }


   ::file::path system_file::sys_temp_unique(const ::file::path & lpszName)
   {

      return ::dir::sys_temp() / lpszName;

   }


   file_pointer system_file::time_square_file(::object * pobject, const string & pszPrefix, const string & pszSuffix)
   {

      return get(time_square(pobject, pszPrefix, pszSuffix), pobject);

   }


   file_pointer system_file::get(const ::file::path & name,::object * pobject)
   {

      Context.dir().mk(name.name(), pobject);

      file_pointer fileOut = App(pobject).file().get_file(name, ::file::mode_create | ::file::type_binary | ::file::mode_write);

      if (fileOut.is_null())
      {

         __throw(::file::exception(error_file_not_found, -1L, name));

      }

      return fileOut;

   }


   ::file::path system_file::replace_extension(const ::file::path & pszFile, const char * pszExtension)
   {

      ::file::path strFile(pszFile);

      set_extension(strFile, pszExtension);

      return strFile;

   }


   void system_file::set_extension(::file::path & strFile, const char * pszExtension)
   {

      strsize iEnd = strFile.reverse_find('.');

      if(iEnd < 0)
      {

         iEnd = strFile.get_length();

      }

      strFile = strFile.Left(iEnd) + ::str::has_char(pszExtension, ".");

   }


   void system_file::normalize(string & str)
   {
      if (str.is_empty())
      {

         return;

      }

      while(str.has_char() &&
            (str.Right(1) == "\\" ||
             str.Right(1) == "/"))
      {
         str = str.Left(str.get_length() - 1);
      }
   }


   i32 system_file::cmp(const ::file::path & psz1, const ::file::path & psz2)
   {
      string str1(psz1);
      normalize(str1);
      string str2(psz2);
      normalize(str2);
      return str1.compare_ci(str2);
   }



   ::status::result system_file::rename(const ::file::path & pszNew,const ::file::path & psz,::object * pobject)
   {

      ::file::path strDir = psz.folder();

      ::file::path strDirNew = pszNew.folder();

      if(strDir != strDirNew)
      {

         // rename should work only on files in the same directory/folder

         return ::error_failed;

      }

      if(move(pszNew, psz, pobject).failed())
      {

         return ::error_failed;

      }

      return ::success;

   }




   void system_file::dtf(const ::file::path  & pszFile,const ::file::path & pszDir,::object * pobject)
   {
      listing ls(::get_context_application(pobject));
      ls.rls( pszDir);
      dtf(pszFile, ls, pobject);
   }

   
   void system_file::dtf(const ::file::path & pszFile,::file::patha & stra,::object * pobject)
   {

      file_pointer spfile = App(pobject).file().get_file(pszFile, ::file::mode_create | ::file::mode_write | ::file::type_binary);

      if (spfile.is_null())
         __throw(::exception::exception("failed"));

      string strVersion;

      strVersion = "fileset v1";

      MD5_CTX ctx;

      write_gen_string(spfile, nullptr, strVersion);

      __pointer(::file::file) pfile2;

      __construct(pfile2);

      memsize iBufSize = 1024 * 1024;

      memsize uiRead;

      memory buf;

      buf.set_size(iBufSize);

      string strMd5 = "01234567012345670123456701234567";

      u64 iPos;

      for (i32 i = 0; i < stra.get_size(); i++)
      {
         if (::str::ends_ci(stra[i], ".zip"))
         {
         }
         else if (Context.dir().is(stra[i], pobject))
            continue;
         write_n_number(spfile, nullptr, 1);
         iPos = spfile->get_position();
         write_gen_string(spfile, nullptr, strMd5);
         MD5_Init(&ctx);
         string strRelative = stra[i].relative();
         write_gen_string(spfile, &ctx, strRelative);
         if (pfile2->open(stra[i], ::file::mode_read | ::file::type_binary).failed())
            __throw(::exception::exception("failed"));
         write_n_number(spfile, &ctx, (i32)pfile2->get_length());
         while ((uiRead = pfile2->read(buf, iBufSize)) > 0)
         {
            spfile->write(buf, uiRead);
            MD5_Update(&ctx, buf, (size_t) uiRead);
         }
         spfile->seek(iPos, ::file::seek_begin);
         strMd5 = __str(ctx);
         write_gen_string(spfile, nullptr, strMd5);
         spfile->seek_to_end();

      }

      write_n_number(spfile, nullptr, 2);


   }

   void system_file::ftd(const ::file::path & pszDir,const ::file::path & pszFile,::object * pobject)
   {

      string strVersion;

      file_pointer spfile = App(pobject).file().get_file(pszFile, ::file::mode_read | ::file::type_binary);

      if (spfile.is_null())
         __throw(::exception::exception("failed"));

      read_gen_string(spfile, nullptr, strVersion);

      i64 n;

      string strRelative;
      string strMd5;
      string strMd5New;
      i32 iBufSize = 1024 * 1024;
      memory buf;
      buf.set_size(iBufSize);
      i64 iLen;
      MD5_CTX ctx;
      
      auto pfile2 = __create < ::file::file > ();

      memsize uiRead;

      if (strVersion == "fileset v1")
      {
         while (true)
         {
            read_n_number(spfile, nullptr, n);
            if (n == 2)
               break;
            read_gen_string(spfile, nullptr, strMd5);
            MD5_Init(&ctx);
            read_gen_string(spfile, &ctx, strRelative);
            ::file::path strPath = ::file::path(pszDir) / strRelative;
            App(pobject).dir().mk(strPath.folder());
            if (pfile2->open(strPath, ::file::mode_create | ::file::type_binary | ::file::mode_write).failed())
               __throw(::exception::exception("failed"));
            read_n_number(spfile, &ctx, iLen);
            while (iLen > 0)
            {
               uiRead = spfile->read(buf, (UINT)(MIN(iBufSize, iLen)));
               if (uiRead == 0)
                  break;
               pfile2->write(buf, uiRead);
               MD5_Update(&ctx, buf, (size_t)uiRead);
               iLen -= uiRead;
            }
            pfile2->close();
            strMd5New = __str(ctx);
            if (strMd5 != strMd5New)
               __throw(::exception::exception("failed"));
         }
      }

   }




   void system_file::write_n_number(::file::file *  pfile, void * pctx, i64 iNumber)
   {

      string str;

      str.Format("%I64dn", iNumber);

      pfile->write((const char *)str, str.get_length());

      if (pctx != nullptr)
      {

         MD5_Update((MD5_CTX *)pctx, (const char *)str, (i32)str.get_length());

      }

   }

   void system_file::read_n_number(::file::file *  pfile, void * pctx, i64 & iNumber)
   {

      u64 uiRead;

      string str;

      char ch;

      while ((uiRead = pfile->read(&ch, 1)) == 1)
      {

         if (ch >= '0' && ch <= '9')
            str += ch;
         else
            break;

         if (pctx != nullptr)
         {
            MD5_Update((MD5_CTX *)pctx, &ch, 1);
         }

      }

      if (ch != 'n')
         __throw(::exception::exception("failed"));

      if (pctx != nullptr)
      {
         MD5_Update((MD5_CTX *)pctx, &ch, 1);
      }

      iNumber = ::str::to_i64(str);

   }

   void system_file::write_gen_string(::file::file *  pfile, void * pctx, string & str)
   {
      ::count iLen = str.get_length();
      write_n_number(pfile, pctx, iLen);
      pfile->write((const char *)str, str.get_length());
      if (pctx != nullptr)
      {
         MD5_Update((MD5_CTX *)pctx, (const char *)str, (i32)str.get_length());
      }
   }

   void system_file::read_gen_string(::file::file * pfile, void * pctx, string & str)
   {
      i64 iLen;
      read_n_number(pfile, pctx, iLen);
      LPSTR psz = str.get_string_buffer((strsize)(iLen + 1));

      pfile->read(psz, (memsize)iLen);

      if (pctx != nullptr)
      {
         i64 iProcessed = 0;
         while (iLen - iProcessed > 0)
         {
            i32 iProcess = (i32)MIN(1024 * 1024, iLen - iProcessed);
            MD5_Update((MD5_CTX *)pctx, &psz[iProcessed], iProcess);

            iProcessed += iProcess;
         }
      }
      psz[iLen] = '\0';

      str.release_string_buffer();
   }


   bool system_file::resolve_link(::object * pobject, ::file::path & pathTarget, const string & strSource, string * pstrDirectory, string * pstrParams, ::user::primitive * puiMessageParentOptional)
   {

      return Context.os().resolve_link(pobject, pathTarget, strSource, pstrDirectory, pstrParams, puiMessageParentOptional);

   }


   string system_file::md5(const var & varFile, ::object * pobject)
   {

      auto pfile = App(pobject).file().get_file(varFile, ::file::type_binary | ::file::mode_read);

      return md5(pfile);

   }


   string system_file::md5(file * pfile)
   {

      if (::is_null(pfile))
      {

         return "";

      }

      memory mem;

      mem.set_size(1024 * 256);

      MD5_CTX ctx;

      MD5_Init(&ctx);

      memsize iRead;

      while ((iRead = (memsize)pfile->read(mem.get_data(), mem.get_size())) > 0)
      {

         MD5_Update(&ctx, mem.get_data(), (size_t)iRead);

      }

      return __str(ctx);

   }


   string system_file::nessie(const var & varFile, ::object * pobject)
   {

      auto pfile = App(pobject).file().get_file(varFile, ::file::type_binary | ::file::mode_read);

      return nessie(pfile);

   }


   string system_file::nessie(file * pfile)
   {

      if (::is_null(pfile))
      {

         return "";

      }

      memory mem;

      mem.set_size(1024 * 256);

      WHIRLPOOL_CTX ns;

      WHIRLPOOL_Init(&ns);

      memsize iRead;

      while ((iRead = (memsize)pfile->read(mem.get_data(), mem.get_size())) > 0)
      {

         WHIRLPOOL_Update(&ns, mem.get_data(), (size_t)iRead);

      }

      return __str(ns);

   }


   bool system_file::get_last_write_time(FILETIME * pfiletime,const string & strFilename)
   {

      __throw(interface_only_exception());

   }


   bool system_file::update_module_path()
   {

      m_pathModule = "";
      m_pathCa2Module = "";


      return true;

   }


   ::estatus system_file::initialize(::layered * pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }

   //bool system_file::prepare_output(::object * pobject, ::stream & outputstream, path & pathDownloading, const ::stream & os)
   //{

   //   Sys(pobject).dir().mk(pathOut.folder(), pobject);

   //   file_pointer fileOut;

   //   i64 iTry = 0;

   //   ::apex::application * papp = ::get_context_application(pobject);

   //   while (true)
   //   {

   //      pathDownloading = pathOut + ".downloading." + ::str::zero_pad(__str(iTry), 20);

   //      fileOut = papp->file().get_file(pathDownloading, ::file::defer_create_directory | ::file::mode_create | ::file::type_binary | ::file::mode_write);

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

   //bool system_file::prepare_input(::object * pobject, ::stream & is, const path & pathIn)
   //{

   //   file_pointer fileIn = Sess(pobject).file().get_file(pathIn, ::file::type_binary | ::file::mode_read);

   //   if (fileIn.is_null())
   //   {

   //      return false;

   //   }

   //   return prepare_input(pobject, is, fileIn);

   //}

   //bool system_file::prepare_input(::object * pobject, ::stream & is, ::file::file * pfileIn)
   //{

   //   is.m_spfile = pfileIn;

   //   if (is.m_spfile.is_null())
   //   {

   //      return false;

   //   }

   //   return prepare_input(pobject, is);

   //}


   //bool system_file::prepare_input(::object * pobject, ::stream & is)
   //{

   //   if (is.m_spfile.is_null())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   bool system_file::post_output(::object * pobject, ::file::path pathOut, ::file::path pathDownloading)
   {

      try
      {

         if (rename(pathOut, pathDownloading, pobject))
         {

            TRACE("Failed to rename \"downloading\" file from %s to %s", pathDownloading.c_str(), pathOut.c_str());

            del(pathDownloading, pobject);

            return false;

         }

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   file_result system_file::file_get_file(::object * pobject, ::file::path path, const efileopen & eopenFlags)
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
      catch (const ::exception_pointer & pe)
      {

         return pe;

      }
      catch (...)
      {

      }

      return ::error_failed;

   }


   file_result system_file::data_get_file(::object * pobject, string strData, const efileopen & eopenFlags)
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

                  TRACE("::file::system_file::data_get_file Succeeded");

                  return pmemoryfile;

               }

            }

         }

      }

      TRACE("::file::system_file::data_get_file Failed");

      return ::error_failed;

   }


   file_result system_file::zip_get_file(::object * pobject, ::file::path path, const efileopen & eopenFlags)
   {

      if (eopenFlags & (::file::mode_write | ::file::mode_truncate | ::file::mode_create))
      {

         TRACE("Error: randomly writing to file inside zip compressed file not supported");

         return ::error_invalid_argument;

      }

      auto pinfile = __new(zip::in_file);

      if (pinfile.is_set())
      {

         if (pinfile->unzip_open(path, 0))
         {

            TRACE("::file::system_file::zip_get_file Succeeded");

            return pinfile;

         }

      }

      TRACE("::file::system_file::zip_get_file Failed");

      return nullptr;

   }


   file_result system_file::http_get_file(::object * pobject, const var & varFile, const efileopen & eopenFlags)
   {

      if (eopenFlags & (::file::mode_write | ::file::mode_truncate | ::file::mode_create))
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

         if (!(path & ::file::flag_bypass_cache) && ::file_exists(pathCache))
         {

            sl.unlock();

            auto pfile = file_get_file(pobject, pathCache, eopenFlags);

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

      __pointer(memory_file) pmemoryfile = __new(::memory_file());

      if (!Context.http().get(*pmemoryfile->get_primitive_memory(), path, set))
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

            App(pobject).file().transfer(pfileOut, pmemoryfile);

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


   ::file_result system_file::get_reader(::object* pobject, const var& varFile, const efileopen & eopenFlags)
   {

      ::file_result preader;

      if (varFile.m_etype == ::type_element)
      {

         preader = varFile.cast < ::file::file >();

         if (!preader)
         {

            preader = get_file(pobject, varFile, eopenFlags);

         }

      }

      return preader;

   }



   ::file_result system_file::get_writer(::object* pobject, const var& varFile, const efileopen & eopenFlags)
   {

      ::file_result preader;

      if (varFile.m_etype == ::type_element)
      {

         preader = varFile.cast < ::file::file >();

         if (!preader)
         {

            preader = get_file(pobject, varFile, eopenFlags);

         }

      }

      return preader;

   }


   file_result system_file::get_file(::object * pobject, const var & varFile, const efileopen & eopenFlags)
   {

      try
      {

         ::file_pointer pfile;

         if (varFile.get_type() == ::type_element)
         {

            pfile = varFile.cast < ::file::file >();

            if (pfile.is_set())
            {

               return pfile;

            }

         }
         else if (varFile.get_type() == ::type_propset)
         {

            if (varFile.has_property("file"))
            {

               pfile = varFile.propset()["file"].cast < ::file::file >();

               if (pfile.is_set())
               {

                  return pfile;

               }

            }

         }

         ::file::path path = varFile.get_file_path();

         if (path.begins_ci("data:"))
         {

            return data_get_file(pobject, path);

         }

         if (!(path & ::file::flag_required) &&
               varFile.is_property_true("required"))
         {

            path |= ::file::flag_required;

         }

         if(!(path & ::file::flag_bypass_cache)
               && ((eopenFlags & ::file::no_cache) || varFile.is_property_true("nocache")))
         {

            path |= ::file::flag_bypass_cache;

         }

         path = Context.defer_process_path(path, pobject);

         if (path.is_empty())
         {

            TRACE("::file::system_file::get_file file with empty name!!");

            return ::error_file_not_found;

         }
         else if (::thread_is_set(id_thread_zip_is_dir) && (::str::find_file_extension("zip:", path) >= 0))
         {

            return zip_get_file(pobject, path, eopenFlags);

         }
         else if (::str::begins_eat(path, "file:///") || ::str::begins_eat(path, "file:\\\\\\"))
         {

            return get_file(pobject, path, eopenFlags);

         }
         else if (::str::begins(path, astr.HttpProtocol) || ::str::begins(path, astr.HttpsProtocol))
         {

            return http_get_file(pobject, varFile, eopenFlags);

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
            //   else if (&Session != nullptr && Session.appptra().lookup(strApp, pappLookup))
            //   {

            //      spfile = App(pappLookup).file().get_file("matter://" + strPath, nOpenFlags, &::status::result);

            //   }
            //   else
            //   {

            //      strPath = App(papp).dir().matter(strPath);

            //      strPath = Sys(papp).get_matter_cache_path(strPath);

            //      spfile = get_file(strPath, nOpenFlags, &::status::result, papp);

            //   }

            //}
            //else
            //{

            //   //  return nullptr;




            //   /*            if((nOpenFlags & ::file::mode_create) == 0 && !exists(strPath))
            //   {
            //   TRACE("::application::file does not exist!! : \"%s\"",strPath);
            //   return spfile;
            //   }
            //   */

            //if (nOpenFlags & ::file::type_text)
            //{

            //   pfile = __new(::file::stdio_file(pobject));

            //}
            //else
            {

               __construct(pfile);

            }

            auto result = pfile->open(path, eopenFlags);

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


   bool system_file::transfer(::file::file * pfileOut, ::file::file * pfileIn)
   {

      return transfer(this, pfileOut, pfileIn);

   }


   //bool system_file::transfer(::object * pobject, const path & pszOutput, ::file::file * pfileIn)
   //{

   //   return output(pobject, pszOutput, this, &system_file::transfer, pfileIn);

   //}


   //bool system_file::transfer(::object * pobject, const path & pszOutput, ::stream & istream)
   //{

   //   return output(pobject, pszOutput, this, &system_file::transfer, istream);

   //}


   //bool system_file::transfer(::object * pobject, file * pfileOut, const path & pszSource)

   //{

   //   return output(pobject, pfileOut, this, &system_file::transfer, pszSource);


   //}


   //bool system_file::transfer(::object * pobject, file * pfileOut, ::file::file * pfileIn)
   //{

   //   return output(pobject, pfileOut, this, &system_file::transfer, pfileIn);

   //}


   //bool system_file::transfer(::object * pobject, file * pfileOut, ::stream & istream)
   //{

   //   return output(pobject, pfileOut, this, &system_file::transfer, istream);

   //}


   //bool system_file::transfer(::object * pobject, ::stream & os, const path & pszSource)

   //{

   //   return output(pobject, os, this, &system_file::transfer, pszSource);


   //}


   //bool system_file::transfer(::object * pobject, ::stream & os, ::file::file * pfileIn)
   //{

   //   return output(pobject, os, this, &system_file::transfer, pfileIn);

   //}


   //bool system_file::transfer(::object * pobject, ::stream & os, ::stream & istream)
   //{

   //   return output(pobject, os, this, &system_file::transfer, istream);

   //}

   //bool system_file::transfer(::object* pobject, ::stream& os, ::file::file & reader)
   //{

   //   return output(pobject, os, this, &system_file::transfer, preader);

   //}

   //bool system_file::transfer(::stream & ostream, ::stream & istream)
   //{
   //   class memory memory;
   //   memory.set_size(1024 * 256);
   //   memsize  uiRead;
   //   while ((uiRead = istream.read(memory, memory.get_size())) > 0)
   //   {
   //      ostream.write(memory, uiRead);
   //   }
   //   return true;
   //}


   bool system_file::is_link(string strPath)
   {

      return false;

   }


   ::file::path system_file::dropbox_info_json(::layered * pobjectContext)
   {

      ::file::path pathJson;

      pathJson = ::dir::home() / ".dropbox/info.json";

      return pathJson;

   }

   
   ::file::path system_file::onedrive_global_ini(::layered * pobjectContext)
   {
      
      ::file::path pathGlobalIni;
      
      pathGlobalIni = ::dir::roaming() / "OneDrive/settings/Personal/global.ini";
      
      return pathGlobalIni;
      
   }

   
   ::file::path system_file::onedrive_cid_ini(::layered * pobjectContext)
   {
      
      ::file::path pathGlobalIni = onedrive_global_ini(pobject);
      
      string strIni = file_as_string(pathGlobalIni);
      
      if(strIni.is_empty())
      {
       
         return "";
         
      }
      
      ::property_set set;
      
      set.parse_ini(strIni);
      
      string strCid = set["cid"];
      
      ::file::path pathIni = ::dir::roaming() / "OneDrive/Settings/Personal/" + strCid + ".ini";
      
      return pathIni;
      
   }


} // namespace file



