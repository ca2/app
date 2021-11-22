#include "framework.h"
#include "apex/operating_system.h"
#include "acme/platform/acme_str_pool.h"
#include "apex/platform/machine_event.h"
#include "apex/platform/machine_event_central.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"


#ifdef WINDOWS_DESKTOP

#include "apex/platform/app_core.h"

#elif defined(_UWP)
#include "apex/node/operating_system/_operating_system.h"
#endif

#include <stdio.h>


#define UTF8_BOM "\xef\xbb\xbf"


//#include "apex/compress/zip/_.h"
#include "acme/id.h"


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

   defer_create_mutex();

}


file_context::~file_context()
{

}


::e_status file_context::initialize(::object * pobject)
{

   auto estatus = ::object::initialize(pobject);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


bool file_context::exists(const ::file::path &pathParam)
{

   if (::is_null(m_pcontext))
   {

      return false;

   }

   ::file::path path = m_pcontext->m_papexcontext->defer_process_matter_path(pathParam);

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
//   path = m_pcontext->m_papexcontext->defer_process_matter_path(path, papp, bOptional, bNoCache);
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


bool file_context::is_file_or_dir(const ::file::path &path, ::payload *pvarQuery, ::file::enum_type *petype)
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

      return m_pcontext->m_papexcontext->http().is_file_or_dir(path, pvarQuery, petype, set);

   }

   if (::task_flag().is_set(e_task_flag_compress_is_dir))
   {

      strsize iFind = ::str::find_file_extension("zip:", path);

      if (iFind >= 0)
      {

         if (!exists(path.Mid(0, iFind + 4)))
         {

            return false;

         }

         throw todo;

         //compress_context compress(this);

         //::file::path pathZip;

         //string_array straPath;

         //if (!compress.get_patha(pathZip, straPath, path))
         //{

         //   return false;

         //}

         //auto pfile = m_pcontext->m_papexcontext->file().get_reader(pathZip);

         //zip_context zip(this);

         //return zip.is_file_or_dir(pfile, straPath, petype);

         return false;

      }

   }

   return m_psystem->m_pacmepath->is_file_or_dir(path, petype) != false;

}


::payload file_context::length(const ::file::path &pszPath)
{

   return length(pszPath, nullptr);

}


::payload file_context::length(const ::file::path &path, ::payload *pvarQuery)
{

   throw ::interface_only_exception();

   return false;

   //if (path.m_iSize != -1)
   //{

   //   return maximum(0, path.m_iSize);

   //}

   //::payload varRet;

//#ifdef WINDOWS
//
//   WIN32_FILE_ATTRIBUTE_DATA data;
//
//   if (!GetFileAttributesExW(::str::international::utf8_to_unicode(path), GetFileExInfoStandard, &data))
//   {
//
//      varRet.set_type(::e_type_null);
//
//      ((::file::path &) path).m_iSize = -2;
//
//   }
//   else
//   {
//
//      varRet = (((u64) data.nFileSizeHigh) << 32) | (u64) data.nFileSizeLow;
//
//      ((::file::path &) path).m_iSize = varRet.m_i64;
//
//   }
//
//#else
//
//   struct stat stat;
//
//   if (::stat(path, &stat) == -1)
//   {
//
//      varRet.set_type(::e_type_null);
//
//      ((::file::path &) path).m_iSize = -2;
//
//   }
//   else
//   {
//
//      varRet = (iptr)stat.st_size;
//
//      ((::file::path &)path).m_iSize = varRet.m_i64;
//
//   }
//
//#endif

//   return varRet;

}


::file::path file_context::module()
{

   auto psystem = get_system()->m_papexsystem;

   auto pfilesystem = psystem->m_pfilesystem;

   return pfilesystem->m_pathModule;

}


::file::path file_context::ca2module()
{

   auto psystem = get_system()->m_papexsystem;

   return psystem->m_pfilesystem->m_pathCa2Module;

}


::file::path file_context::time_square(const string &pszPrefix, const string &pszSuffix)
{

   return time(m_pcontext->m_papexcontext->dir().time_square(), 25, pszPrefix, pszSuffix);

}


::file::path file_context::time_log(const string &pszId)
{
   return time(m_pcontext->m_papexcontext->dir().time_log(pszId), 9);
}


::file::path
file_context::time(const ::file::path &psz, i32 iMaxLevel, const string &pszPrefix, const string &pszSuffix,
                   bool bTryDelete)
{

   auto psystem = get_system()->m_papexsystem;

   synchronous_lock lockMachineEvent(psystem->mutex());

   ::file::path str;

   ::file::path path;

   string strPrefix(pszPrefix);

   string strSuffix(pszSuffix);

   restart:

   str.Empty();

   str = psz;

   m_pcontext->m_papexcontext->dir().mk(str);

   ::file::listing ls;

   string strFormat;

   int iIncLevel = 0;

   for (i32 i = 1; i <= iMaxLevel;)
   {

      m_pcontext->m_papexcontext->dir().mk(str);

      if (!m_pcontext->m_papexcontext->dir().is(str))
      {

         __throw(error_path_not_found, "time square dir does not exist");

      }

      m_pcontext->m_papexcontext->dir().ls(ls, str);

      if (i < iMaxLevel)
      {

         i32 iMax = filterex_time_square("", ls);

         if (iMax == -1)
         {

            str /= "00";

            m_pcontext->m_papexcontext->dir().mk(str);

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

            strFormat.format("%02d", iMax);

            str /= strFormat;

            if (i == iIncLevel)
            {

               m_pcontext->m_papexcontext->dir().mk(str);

            }

         }

         i++;

      }
      else // if i == iMaxLevel
      {

         m_pcontext->m_papexcontext->dir().ls(ls, str);

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

                  strFormat.format("%d", iMax);

               }
               else
               {

                  strFormat.format("%02d", iMax);

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

            stra.erase_at(i);

            i--;

            continue;

         }

         if (!isdigit((uchar) str[0]) || !isdigit((uchar) str[1]))
         {

            stra.erase_at(i);

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

   if (m_pcontext->m_papexcontext->file().exists(path))
   {

      if (!bTryDelete)
      {

         return false;

      }

      m_pcontext->m_papexcontext->file().del(path);

      if (m_pcontext->m_papexcontext->file().exists(path))
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


::payload file_context::as_network_payload(const ::payload &payloadFile)
{

   string str = as_string(payloadFile);

   str.trim();

   if (str.is_empty())
   {

      return ::e_type_new;

   }

   const char *pszJson = str;

   ::payload v;

   try
   {

      v.parse_network_payload(pszJson);

   }
   catch (const ::exception & e)
   {

      INFORMATION(e.get_message());

      v = ::e_type_new;

   }
   catch (...)
   {

      INFORMATION("GENERAL Exception parsing network_payload file_context::as_network_payload : \"" << str << "\"");

      v = ::e_type_new;

   }

   return v;

}


string file_context::as_string(const ::payload &payloadFile)
{

   memory memory;

   if (!as_memory(payloadFile, memory))
   {

      return "";

   }

   return memory.as_utf8();

}


bool file_context::as_memory(const ::payload &payloadFile, memory_base &mem)
{

   auto pfile = get_file(payloadFile, ::file::e_open_share_deny_none | ::file::e_open_read | ::file::e_open_binary);

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


::e_status file_context::put_lines(const ::payload &payloadFile, const string_array &stra, const plain_text_file_options & options)
{

   try
   {

      auto pfile = get_file(payloadFile, ::file::e_open_write | ::file::e_open_truncate | ::file::e_open_create | ::file::e_open_defer_create_directory);

      if (!pfile)
      {

         return pfile;

      }

      if (options.m_bUtf8Bom)
      {

         pfile->write(UTF8_BOM, STATIC_ASCII_STRING_LENGTH(UTF8_BOM));

      }

      pfile->put_lines(stra);

      return success;

   }
   catch (...)
   {

   }

   return error_exception;

}


//::e_status file_context::put_lines_utf8(const ::payload &payloadFile, const string_array &stra)
//{
//
//   try
//   {
//
//      auto pfile = get_file(payloadFile, ::file::e_open_write | ::file::e_open_truncate | ::file::e_open_create | ::file::e_open_defer_create_directory);
//
//      if (!pfile)
//      {
//
//         return pfile;
//
//      }
//
//      pfile->write(UTF8_BOM, STATIC_ASCII_STRING_LENGTH(UTF8_BOM));
//
//      pfile->put_lines(stra);
//
//      return success;
//
//   }
//   catch (...)
//   {
//
//   }
//
//   return error_exception;
//
//}


//void file_context::_put_lines(::file::file *pfile, const string_array &stra)
//{
//
//   if (pfile == nullptr)
//   {
//
//      return;
//
//   }
//
//   for (auto &strLine : stra)
//   {
//
//      pfile->println(strLine);
//
//   }
//
//}


::e_status file_context::get_lines(string_array &stra, const ::payload &payloadFile, bool bAddEmpty)
{

   try
   {

      auto pfile = get_file(payloadFile, ::file::e_open_text | ::file::e_open_read);

      if (!pfile)
      {

         return pfile;

      }

      string strLine;

      while (pfile->read_string(strLine))
      {

         if (bAddEmpty || !strLine.is_empty())
         {

            stra.add(strLine);

         }

      }

      return ::success;

   }
   catch (...)
   {

   }

   return error_exception;

}


::e_status file_context::put_memory(const ::payload &payloadFile, const block & block)
{

   file_transport pfile;

   int iTry = 0;

   try
   {

      pfile = get_file(payloadFile,
                        ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_share_deny_write |
                        ::file::e_open_defer_create_directory);

   }
   catch(const ::exception &)
   {

      return false;

   }
   catch (...)
   {

      return false;

   }

   if (!pfile)
   {

      return false;

   }

   pfile->set_size(0);

   if(block.size() > 0)
   {

      pfile->write(block.get_data(), block.get_size());

   }

   return true;

}


::e_status file_context::add_contents(const ::payload &payloadFile, const void *pvoidContents, ::count count)
{

   file_pointer pfile;

   try
   {

      pfile = get_file(payloadFile,
                        ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_no_truncate |
                        ::file::e_open_share_exclusive | ::file::e_open_defer_create_directory);

   }
   catch (...)
   {

      return false;

   }

   if (pfile.is_null())
   {

      return false;

   }

   pfile->seek_to_end();

   pfile->write(pvoidContents, count);

   return true;

}


::e_status file_context::put_text(const ::payload& payloadFile, const ::block & block)
{

   if (block.get_data() == nullptr || block.get_size() <= 0)
   {

      return put_memory(payloadFile, { "", 0 });

   }
   else
   {

      string strContents((const char *) block.get_data(), block.get_size());

      ::str::fix_eol(strContents);

      return put(payloadFile, strContents);

   }

}


::e_status file_context::add_contents(const ::payload &payloadFile, const char *pcszContents)
{

   if (pcszContents != nullptr)
   {

      return add_contents(payloadFile, pcszContents, strlen(pcszContents));


   }

   return false;

}


::e_status file_context::put_memory(const ::payload &payloadFile, ::file::file *pfileSrc)
{

   file_pointer pfile;

   pfile = get_file(payloadFile,
                     ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_share_deny_write |
                     ::file::e_open_defer_create_directory);

   if (pfile.is_null())
   {

      return false;

   }

   memory mem;

   mem.set_size(1024 * 1024 * 8);

   memsize uRead;

   while ((uRead = pfileSrc->read(mem.get_data(), mem.get_size())) > 0)
   {

      pfile->write(mem.get_data(), uRead);

   }

   return true;

}


//bool file_context::put_contents(const ::payload &payloadFile, memory &mem)
//{
//
//   return put_contents(payloadFile, mem.get_data(), (count) mem.get_size());
//
//}


::e_status file_context::put_utf8_text(const ::payload &payloadFile, const ::block & block)
{

   auto pfile = get_file(payloadFile,
                     ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_share_deny_write |
                     ::file::e_open_defer_create_directory);

   if (!pfile)
   {

      return pfile;

   }

   pfile->write(UTF8_BOM, STATIC_ASCII_STRING_LENGTH(UTF8_BOM));

   string strContents((const char *) block.get_data(), block.get_size());

   ::str::fix_eol(strContents);

   pfile->write(strContents);

   return true;

}


void file_context::calculate_main_resource_memory()
{


}


::block file_context::get_main_resource_block()
{

#ifdef LINUX

   if(m_psystem->_binary__matter_zip_start && m_psystem->_binary__matter_zip_end)
   {

      return {
         m_psystem->_binary__matter_zip_start,
         m_psystem->_binary__matter_zip_end - m_psystem->_binary__matter_zip_start
      };

   }


#endif

   if (!m_bMainResourceMemoryCalculated)
   {

      m_bMainResourceMemoryCalculated = true;

      calculate_main_resource_memory();

   }

   if (m_memoryMainResource.is_empty())
   {

      return {};

   }

   return m_memoryMainResource;

}


::folder* file_context::resource_folder()
{

   synchronous_lock synchronouslock(mutex());

   auto & pfactory = m_psystem->folder_factory();

   if (!pfactory)
   {

      return nullptr;

   }

   if (m_bFolderResourceCalculated)
   {

      return m_pfolderResource;

   }

   m_bFolderResourceCalculated = true;

   auto block = get_main_resource_block();

   if (!block)
   {

      return nullptr;

   }

   auto pmemory = __new(read_only_memory(block));

   auto pfile = __new(::memory_file(pmemory));

   m_psystem->m_pfactoryFolder->__construct(m_pfolderResource);

   m_pfolderResource->initialize(this);

   if (!m_pfolderResource->open_for_reading(pfile))
   {


      return nullptr;

   }

   return m_pfolderResource;

}


::memory_file_transport file_context::create_resource_file(const char* path)
{

   ::folder* pfolder = nullptr;

   {

      synchronous_lock synchronouslock(mutex());

      pfolder = resource_folder();

      if (is_null(pfolder))
      {

         return nullptr;

      }

   }

   synchronous_lock synchronouslock(pfolder->mutex());

   string strPath(path);

   strPath.replace("\\", "/");

   if (!pfolder->locate(strPath))
   {

      return nullptr;

   }

   auto pfile = pfolder->get_file();

   if (!pfile)
   {

      return nullptr;

   }

   char buffer[1024];

   auto pfileOutput = create_memory_file();

   memsize read;

   while ((read = pfile->read(buffer, sizeof(buffer))) > 0)
   {

      pfileOutput->write(buffer, read);

   }

   pfileOutput->seek_to_begin();

   return pfileOutput;

}


::memory file_context::get_resource_memory(const char* path)
{

   auto pfile = create_resource_file(path);
   
   if (!pfile)
   {

      return {};

   }

   return ::move(*pfile->memory().m_memory.m_pprimitivememory);

}


bool file_context::resource_is_file_or_dir(const char* path)
{

   ::folder* pfolder = nullptr;

   {

      synchronous_lock synchronouslock(mutex());

      pfolder = resource_folder();

      if (is_null(pfolder))
      {

         return false;

      }

   }

   synchronous_lock synchronouslock(pfolder->mutex());

   string strPath(path);

   strPath.replace("\\", "/");

   if (!pfolder->locate(strPath))
   {

      return false;

   }

   return true;

}


::extended::status file_context::copy(::payload varTarget, ::payload varSource, bool bFailIfExists, e_extract eextract)
{

   if (m_pcontext->m_papexcontext->dir().is(varSource.get_file_path()) &&
       (eextract == extract_first || eextract == extract_all || !(::str::ends_ci(varSource.get_file_path(), ".zip"))))
   {

      ::file::listing patha;

      m_pcontext->m_papexcontext->dir().rls(patha, varSource);

      ::file::path strDst;
      ::file::path strSrc;
      ::file::path strDirSrc(varSource.get_file_path());
      ::file::path strDirDst(varTarget.get_file_path());

      if (::task_flag().is_set(e_task_flag_compress_is_dir) && (::str::ends(strDirSrc, ".zip")))
      {

         strDirSrc += ":";

      }

      for (i32 i = 0; i < patha.get_size(); i++)
      {
         strSrc = patha[i];
         strDst = strSrc;
         ::str::begins_eat_ci(strDst, strDirSrc);
         strDst = strDirDst / strDst;
         if (m_pcontext->m_papexcontext->dir().is(strSrc))
         {
            if ((eextract == extract_first || eextract == extract_none) &&
                (::str::ends_ci(varSource.get_file_path(), ".zip")))
            {
            }
            else
            {
               m_pcontext->m_papexcontext->dir().mk(strDst);
            }
         }
         else
         {
            if (!m_pcontext->m_papexcontext->dir().is(strDst.folder()))
            {
               m_pcontext->m_papexcontext->dir().mk(strDst.folder());
            }
            copy(strDst, strSrc, bFailIfExists, eextract == extract_all ? extract_all : extract_none);
         }
      }
   }
   else
   {

      if (varTarget.get_file_path().has_char() && varSource.get_file_path().has_char())
      {

         if (!m_pcontext->m_papexcontext->dir().is(varTarget.get_file_path().folder()))
         {

            m_pcontext->m_papexcontext->dir().mk(varTarget.get_file_path().folder());

         }

         auto psystem = m_psystem;

         auto pacmefile = psystem->m_pacmefile;

         if (!pacmefile->copy(varTarget.get_file_path(), varSource.get_file_path(), !bFailIfExists))
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

      ::payload varNew;

      if (m_pcontext->m_papexcontext->dir().is(varTarget) && varSource.get_file_path().name().has_char())
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
         strError.format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open output file",
                         varSource.get_file_path().c_str(), varNew.get_file_path().c_str(), bFailIfExists);
         throw ::exception(::error_io, strError);
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
            strError.format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open input file",
                            varSource.get_file_path().c_str(), varNew.get_file_path().c_str(), bFailIfExists);
            __throw(::error_io, strError);
         }

         binary_stream ostream(ofile);

         //stream istream(ifile, FIRST_VERSION);

         m_pcontext->m_papexcontext->file().transfer(ostream.m_p, ifile);

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

               INFORMATION("During copy, failed to get status from input file \"" << 
                     varSource.get_file_path() << "\" bFailIfExists = " <<  (bFailIfExists ? "true" : "false"));

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

                  INFORMATION("During copy, failed to set status to output file \""
                     << varTarget.get_file_path() << "\" bFailIfExists=" << (bFailIfExists ? "true" : "false"));

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
            strError.format(
               "During copy, failed to close both input file \"%s\" and output file \"%s\" bFailIfExists=%d",
               varSource.get_file_path().c_str(), varTarget.get_file_path().c_str(), bFailIfExists);
            __throw(::error_io, strError);
         }
         else
         {
            string strError;
            strError.format("During copy, failed to close input file \"%s\" bFailIfExists=%d",
                            varSource.get_file_path().c_str(), bFailIfExists);
            __throw(::error_io, strError);
         }
      }
      else if (bOutputFail)
      {
         string strError;
         strError.format("During copy, failed to close output file \"%s\" bFailIfExists=%d",
                         varTarget.get_file_path().c_str(), bFailIfExists);
         __throw(::error_io, strError);
      }

   }

   return ::success;

}


::extended::status file_context::move(const ::file::path &pszNew, const ::file::path &psz)
{

   throw ::interface_only_exception();

   return error_interface_only;

//#ifdef WINDOWS_DESKTOP
//
//   if (!::MoveFileW(
//      ::str::international::utf8_to_unicode(psz),
//      ::str::international::utf8_to_unicode(pszNew)))
//   {
//
//      DWORD dwError = ::GetLastError();
//
//      if (dwError == ERROR_ALREADY_EXISTS)
//      {
//
//         if (::CopyFileW(
//            ::str::international::utf8_to_unicode(psz),
//            ::str::international::utf8_to_unicode(pszNew),
//            false))
//         {
//
//            if (!::DeleteFileW(::str::international::utf8_to_unicode(psz)))
//            {
//
//               dwError = ::GetLastError();
//
//               string strError;
//
//               strError.Format("Failed to delete the file to move \"%s\" error=%d", psz, dwError);
//
//               TRACE("%s", strError);
//
//            }
//
//            return ::success;
//
//         }
//
//         dwError = ::GetLastError();
//
//      }
//
//      string strError;
//
//      strError.Format("Failed to move file \"%s\" to \"%s\" error=%d", psz, pszNew, dwError);
//
//      __throw(io_exception(::error_io, strError));
//
//   }
//
//#elif defined(_UWP)
//
//   ::winrt::Windows::Storage::StorageFile ^ file = get_os_file(psz, 0, 0, nullptr, OPEN_EXISTING, 0, nullptr);
//
//   if (file == nullptr)
//   {
//
//      //output_debug_string("test");
//
//      __throw(::exception("file::file_context::move Could not move file, could not open source file"));
//
//   }
//
//   string strDirOld = psz.folder();
//   string strDirNew = pszNew.folder();
//   string strNameOld = psz.name();
//   string strNameNew = pszNew.name();
//
//   if (strDirOld == strDirNew)
//   {
//      if (strNameOld == strNameNew)
//      {
//         return ::success;
//      }
//      else
//      {
//         ::wait(file->RenameAsync(strNameNew));
//      }
//   }
//   else
//   {
//      ::winrt::Windows::Storage::StorageFolder ^ folder = get_os_folder(strDirNew);
//      if (strNameOld == strNameNew)
//      {
//         ::wait(file->MoveAsync(folder));
//      }
//      else
//      {
//         ::wait(file->MoveAsync(folder, strNameNew));
//      }
//   }
//
//
//#else
//   if (::rename(psz, pszNew) != 0)
//   {
//      i32 err = errno;
//      string strError;
//      strError.Format("Failed to delete file error=%d", err);
//      __throw(::exception(strError));
//   }
//#endif
//
//   return ::success;

}


::extended::status file_context::del(const ::file::path & path)
{

   throw ::interface_only_exception();

   return error_interface_only;

//#ifdef WINDOWS_DESKTOP
//
//   HANDLE h = ::CreateFileW(::str::international::utf8_to_unicode(string("\\\\?\\") + psz),
//                            GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING,
//                            FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_DELETE_ON_CLOSE, nullptr);
//
//   if (h == INVALID_HANDLE_VALUE)
//   {
//
//      DWORD dwError = ::GetLastError();
//
//      if (dwError == 2) // the file does not exist, so delete "failed"
//      {
//
//         return ::success;
//
//      }
//
//      string strError;
//
//      strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);
//
//      return ::error_failed;
//
//   }
//   else
//   {
//      ::FlushFileBuffers(h);
//      ::CloseHandle(h);
//   }
//
//   /*      if(!::DeleteFileW(::str::international::utf8_to_unicode(string("\\\\?\\") + psz)))
//   {
//   u32 dwError = ::get_last_error();
//   if(dwError == 2) // the file does not exist, so delete "failed"
//   return;
//   string strError;
//   strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);
//   __throw(io_exception(strError));
//   }*/
//
//
//#else
//
//   if (unlink(psz) != 0)
//   {
//      i32 err = errno;
//      if (err != ENOENT) // already does not exist - consider removal successful - does not issue an exception
//      {
//         string strError;
//         strError.Format("Failed to delete file error=%d", err);
//         __throw(::exception(strError));
//      }
//   }
//#endif
//
//   return ::success;

}


::file::path file_context::duplicate(const ::file::path &psz)
{
   string strCopy("copy");
   string strNew;
   if (m_pcontext->m_papexcontext->dir().is(psz))
   {
      i32 i = 1;
      while (i <= 100)
      {
         strNew.format("%s-%s-%d", psz.c_str(), strCopy.c_str(), i);
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
      string strExt = psz.final_extension();
      if (!strExt.is_empty())
      {
         strExt = "-" + strExt;
      }
      i32 i = 1;
      while (i <= 100)
      {
         strNew.format("%s-%s-%d%s", psz.c_str(), strCopy.c_str(), i, strExt.c_str());
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

   ::file::path strDir = m_pcontext->m_papexcontext->dir().trash_that_is_not_trash(stra[0]);

   m_pcontext->m_papexcontext->dir().mk(strDir);

   for (i32 i = 0; i < stra.get_size(); i++)
   {

      move(strDir / stra[i].name(), stra[i]);

   }

}


void file_context::trash_that_is_not_trash(const ::file::path &psz)
{

   ::file::path strDir = m_pcontext->m_papexcontext->dir().trash_that_is_not_trash(psz);

   m_pcontext->m_papexcontext->dir().mk(strDir);

   move(strDir / psz.name(), psz);

}


bool file_context::get_status(const ::file::path &path, ::file::file_status &status)
{

   __UNREFERENCED_PARAMETER(path);
   __UNREFERENCED_PARAMETER(status);

   throw ::interface_only_exception();

   return false;

}


::extended::status file_context::set_status(const ::file::path &path, const ::file::file_status &status)
{

   __UNREFERENCED_PARAMETER(path);
   __UNREFERENCED_PARAMETER(status);

   throw ::interface_only_exception();

   return ::success;

}


::extended::status file_context::replace(const ::file::path &pszContext, const string &pszFind, const string &pszReplace)
{

   ::extended::status e;

   ::file::listing straTitle;
   m_pcontext->m_papexcontext->dir().ls(straTitle, pszContext);
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
         // TODO(camilo) : should there be a way to chain or return multiple exceptions... instead of ::extended::status specifile file smart...
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

   //throw ::interface_only_exception();

   return false;

//#ifdef WINDOWS_DESKTOP
//
//   u32 dwAttrib = windows_get_file_attributes(psz);
//
//   if (dwAttrib & FILE_ATTRIBUTE_READONLY)
//   {
//
//      return true;
//
//   }
//
//   return false;
//
//#elif defined(_UWP)
//
//   __throw(todo);
//
//#else
//
//   struct stat st;
//
//   if (stat(psz, &st) != 0)
//      return true;
//
//   return !(st.st_mode & S_IWUSR);
//
//#endif

}


::extended::transport < ::file::file > file_context::resource_get_file(const ::file::path & path)
{

   throw ::interface_only_exception();

   return nullptr;

}


::file::path file_context::sys_temp(const ::file::path &lpszName, const char *pszExtension)
{


   string strTempDir = m_psystem->m_pacmedir->sys_temp();

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

   return m_psystem->m_pacmedir->sys_temp() / lpszName;

}


file_pointer file_context::time_square_file(const string &pszPrefix, const string &pszSuffix)
{

   return get(time_square(pszPrefix, pszSuffix));

}


file_pointer file_context::get(const ::file::path &name)
{

   m_pcontext->m_papexcontext->dir().mk(name.name());

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


::extended::status file_context::rename(const ::file::path &pszNew, const ::file::path &psz)
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
//   m_pcontext->m_papexcontext->dir().rls(ls, pszDir);
//
//   dtf(pszFile, ls);
//
//}
//
//
//void file_context::dtf(const ::file::path & pszFile, ::file::patha & stra)
//{
//
//   file_pointer pfile = get_file(pszFile, ::file::e_open_create | ::file::e_open_write | ::file::e_open_binary);
//
//   if (pfile.is_null())
//   {
//
//      __throw(::exception("failed"));
//
//   }
//
//   string strVersion;
//
//   strVersion = "fileset v1";
//
//   //MD5_CTX ctx;
//
//   write_gen_string(pfile, nullptr, strVersion);
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
//      else if (m_pcontext->m_papexcontext->dir().is(stra[i]))
//         continue;
//      write_n_number(pfile, nullptr, 1);
//      iPos = pfile->get_position();
//      write_gen_string(pfile, nullptr, strMd5);
//      MD5_Init(&ctx);
//      string strRelative = stra[i].relative();
//      write_gen_string(pfile, &ctx, strRelative);
//      if (pfile2->open(stra[i], ::file::e_open_read | ::file::e_open_binary).failed())
//         __throw(::exception("failed"));
//      write_n_number(pfile, &ctx, (i32)pfile2->get_size());
//      while ((uRead = pfile2->read(buf, iBufSize)) > 0)
//      {
//         pfile->write(buf, uRead);
//         MD5_Update(&ctx, buf, (size_t)uRead);
//      }
//      pfile->seek(iPos, ::e_seek_set);
//      strMd5 = __string(ctx);
//      write_gen_string(pfile, nullptr, strMd5);
//      pfile->seek_to_end();
//
//   }
//
//   write_n_number(pfile, nullptr, 2);
//
//}
//
//
//void file_context::ftd(const ::file::path & pszDir, const ::file::path & pszFile)
//{
//
//   string strVersion;
//
//   file_pointer pfile = get_file(pszFile, ::file::e_open_read | ::file::e_open_binary);
//
//   if (pfile.is_null())
//      __throw(::exception("failed"));
//
//   read_gen_string(pfile, nullptr, strVersion);
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
//         read_n_number(pfile, nullptr, n);
//         if (n == 2)
//            break;
//         read_gen_string(pfile, nullptr, strMd5);
//         MD5_Init(&ctx);
//         read_gen_string(pfile, &ctx, strRelative);
//         ::file::path strPath = ::file::path(pszDir) / strRelative;
//         m_pcontext->m_papexcontext->dir().mk(strPath.folder());
//         if (pfile2->open(strPath, ::file::e_open_create | ::file::e_open_binary | ::file::e_open_write).failed())
//            __throw(::exception("failed"));
//         read_n_number(pfile, &ctx, iLen);
//         while (iLen > 0)
//         {
//            uRead = pfile->read(buf, (::u32)(minimum(iBufSize, iLen)));
//            if (uRead == 0)
//               break;
//            pfile2->write(buf, uRead);
//            MD5_Update(&ctx, buf, (size_t)uRead);
//            iLen -= uRead;
//         }
//         pfile2->close();
//         strMd5New = __string(ctx);
//         if (strMd5 != strMd5New)
//            __throw(::exception("failed"));
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
//      __throw(::exception("failed"));
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
//         i32 iProcess = (i32)minimum(1024 * 1024, iLen - iProcessed);
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

   return m_pcontext->m_papexcontext->os_context()->resolve_link(pathTarget, strSource, pstrDirectory, pstrParams);

}


string file_context::get_hash(const ::payload &payloadFile, enum_hash ehash)
{

   auto pfile = get_file(payloadFile, ::file::e_open_binary | ::file::e_open_read);

   if (!pfile)
   {

      return "";

   }

   memory mem;

   mem.set_size(1024 * 256);

   auto psystem = get_system()->m_papexsystem;

   auto pcrypto = psystem->crypto();

   auto phasher = pcrypto->create_hasher(ehash);

   memsize iRead;

   while ((iRead = (memsize) pfile->read(mem.get_data(), mem.get_size())) > 0)
   {

      phasher->update({mem.get_data(), iRead});

   }

   return ::hex::upper_from(phasher->get_hash_and_reset());

}


string file_context::md5(const ::payload &payloadFile)
{

   return get_hash(payloadFile, e_hash_md5);

}


string file_context::nessie(const ::payload &payloadFile)
{

   __throw(todo, "nessie");

   return "";

   //auto pfile = get_file(payloadFile, ::file::e_open_binary | ::file::e_open_read);

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

   //return __string(ns);

}


bool file_context::get_last_write_time(filetime_t *pfiletime, const string &strFilename)
{

   throw ::interface_only_exception();

   return false;

}


::e_status file_context::init_system()
{

   auto psystem = get_system()->m_papexsystem;

   auto estatus = psystem->m_pfilesystem->update_module_path();

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

//   ::application * papp = ::get_application(pobject);

//   while (true)
//   {

//      pathDownloading = pathOut + ".downloading." + ::str::zero_pad(__string(iTry), 20);

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

         INFORMATION("Failed to rename \"downloading\" file from " << pathDownloading << " to " << pathOut);

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


file_transport file_context::file_get_file(::file::path path, const ::file::e_open &eopenFlags)
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
   catch (const ::exception & e)
   {

      return e.m_estatus;

   }
   catch (...)
   {

   }

   return ::error_failed;

}


file_transport file_context::data_get_file(string strData, const ::file::e_open &eopenFlags)
{

   ASSERT(strData.begins_ci("data:"));

   string strSample = strData.Left(4096);

   strsize iFind = strSample.find(";", 5);

   if (iFind > 5)
   {

      strsize iEncoding1 = strSample.find(",", iFind + 1);

      strsize iEncoding2 = strSample.find(";", iFind + 1);

      strsize iEncoding = minimum_non_negative(iEncoding1, iEncoding2);

      if (iFind > 5 && iEncoding > iFind)
      {

         string strMimeType = strData.Mid(5, iFind - 5);

         string strEncoding = strData.Mid(iFind + 1, iEncoding - iFind - 1);

         if (strEncoding.compare_ci("base64") == 0)
         {

            __pointer(memory_file) pmemoryfile = __new(memory_file());

            auto psystem = m_psystem;

            auto pbase64 = psystem->base64();

            if (pbase64->decode(*pmemoryfile->get_primitive_memory(), strData.Mid(iEncoding + 1)))
            {

               INFORMATION("::file::file_context::data_get_file Succeeded");

               return pmemoryfile;

            }

         }

      }

   }

   INFORMATION("::file::file_context::data_get_file Failed");

   return ::error_failed;

}


folder_transport file_context::get_folder(::file::file *pfile, const char * pszImplementation, const ::file::e_open &eopen)
{

   auto & pfactory = m_psystem->folder_factory();

   if (!pfactory)
   {

     return ::error_failed;

   }

   auto pfolder = pfactory->create < ::folder >();

   if (!pfolder)
   {

      return ::error_failed;

   }

   if(eopen & ::file::e_open_read)
   {

      if (pfolder->open_for_reading(pfile))
      {

         INFORMATION("::file::file_context::zip_get_file Succeeded");

         return pfolder;

      }

   }
   else if (eopen & ::file::e_open_write)
   {

      if (pfolder->open_for_writing(pfile))
      {

         INFORMATION("::file::file_context::zip_get_file Succeeded");

         return pfolder;

      }

   }

   INFORMATION("::file::file_context::zip_get_file Failed");

   return nullptr;

}


file_transport file_context::http_get_file(const ::payload &payloadFile, const ::file::e_open &eopenFlags)
{

   if (eopenFlags & (::file::e_open_write | ::file::e_open_truncate | ::file::e_open_create))
   {

      return ::error_invalid_argument;

   }

   ::file::path path = payloadFile.get_file_path();

   ::url_domain domain;

   auto psystem = m_psystem;

   auto purl = psystem->url();

   domain.create(purl->get_server(path));

   bool bSaveCache = domain.m_strRadix != "ca2" || !::str::begins(purl->get_object(path), astr.MatterUri);

   ::file::path pathCache;

   if (bSaveCache)
   {

      pathCache = path;

      if (::str::ends(pathCache, "en_us_international.xml"))
      {
         
         INFORMATION("Debug Here");

      }

      if (::str::ends(pathCache, "text_select.xml"))
      {

         INFORMATION("Debug Here");

      }

      if (::str::ends(pathCache, "arialuni.ttf"))
      {

         INFORMATION("Debug Here : arialuni.ttf");

      }

#ifdef WINDOWS
      pathCache.replace("://", "_\\");
      pathCache.replace("?", "_");
      pathCache.replace(":", "_");
#else
      pathCache.replace("://", "_/");
#endif
      pathCache = m_pcontext->m_papexcontext->dir().cache() / pathCache;

   }

   if (while_predicateicate_Sleep(60 * 1000, [&]()
   {

      synchronous_lock synchronouslock(m_pcontext->m_papexcontext->http().m_pmutexDownload);

      return m_pcontext->m_papexcontext->http().m_straDownloading.contains(path) || m_pcontext->m_papexcontext->http().m_straExists.contains(path);

   }).failed())
   {

      bSaveCache = false;

   }


   {

      synchronous_lock synchronouslock(m_pcontext->m_papexcontext->http().m_pmutexDownload);

      if (!(path & ::file::e_flag_bypass_cache) && m_psystem->m_pacmefile->exists(pathCache))
      {

         synchronouslock.unlock();

         auto pfile = file_get_file(pathCache, eopenFlags);

         bool bBypassCacheIfEmpty = get_bypass_cache_if_empty(payloadFile);

         bool bBypassCache = !bBypassCacheIfEmpty || pfile->is_empty();

         if (pfile && !bBypassCache)
         {

            return pfile;

         }

      }

   }

   if (bSaveCache)
   {

      synchronous_lock synchronouslock(m_pcontext->m_papexcontext->http().m_pmutexDownload);

      m_pcontext->m_papexcontext->http().m_straDownloading.add(path);

   }

   property_set set = payloadFile["http_set"].propset();

   auto pmemoryfile = create_memory_file();

   if (!m_pcontext->m_papexcontext->http().get(pmemoryfile->get_primitive_memory(), path, set))
   {

      return ::error_failed;

   }

   if (bSaveCache)
   {

      synchronous_lock synchronouslock(m_pcontext->m_papexcontext->http().m_pmutexDownload);

      try
      {

         pmemoryfile->seek_to_begin();

         auto pfileOut = m_pcontext->m_papexcontext->file().get_writer(pathCache);

         transfer(pfileOut, pmemoryfile);

      }
      catch (...)
      {

      }

      try
      {

         m_pcontext->m_papexcontext->http().m_straDownloading.erase(path);

      }
      catch (...)
      {

      }

      pmemoryfile->seek_to_begin();

   }

   return pmemoryfile;

}

::file_transport file_context::shared_reader(const ::payload &payloadFile, const ::file::e_open &eopenFlags)
{

   return get_reader(payloadFile, eopenFlags | ::file::e_open_share_deny_none);

}


::file_transport file_context::get_reader(const ::payload &payloadFile, const ::file::e_open &eopenFlags)
{

   ::file_transport preader;

   if (payloadFile.m_etype == ::e_type_element)
   {

      preader = payloadFile.cast<::file::file>();

   }

   if (!preader)
   {

      preader = get_file(payloadFile, eopenFlags | ::file::e_open_read);

   }

   return preader;

}


::file_transport file_context::get_writer(const ::payload &payloadFile, const ::file::e_open &eopenFlags)
{

   ::file_transport pwriter;

   if (payloadFile.m_etype == ::e_type_element)
   {

      pwriter = payloadFile.cast<::file::file>();

   }

   if (!pwriter)
   {

      pwriter = get_file(payloadFile, eopenFlags);

   }

   return pwriter;

}


file_transport file_context::get_file(const ::payload &payloadFile, const ::file::e_open &eopenFlags)
{

   try
   {

      ::file_pointer pfile;

      if (payloadFile.get_type() == ::e_type_element)
      {

         pfile = payloadFile.cast<::file::file>();

         if (pfile.is_set())
         {

            return pfile;

         }

      }
      else if (payloadFile.get_type() == ::e_type_property_set)
      {

         if (payloadFile.has_property("file"))
         {

            pfile = payloadFile.propset()["file"].cast<::file::file>();

            if (pfile.is_set())
            {

               return pfile;

            }

         }

      }

      ::file::path path = payloadFile.get_file_path();

      if (path.begins_ci("data:"))
      {

         return data_get_file(path);

      }

      if (path.contains("yesno.xhtml"))
      {

         output_debug_string("test");

      }

      if (!(path & ::file::e_flag_required) &&
          payloadFile.is_property_true("required"))
      {

         path |= ::file::e_flag_required;

      }

      if (!(path & ::file::e_flag_bypass_cache)
          && ((eopenFlags & ::file::e_open_no_cache) || payloadFile.is_property_true("nocache")))
      {

         path |= ::file::e_flag_bypass_cache;

      }

      path = m_pcontext->m_papexcontext->defer_process_path(path);

      if (path.is_empty())
      {

         INFORMATION("::file::file_context::get_file file with empty name!!");

         return ::error_file_not_found;

      }
      else if (::task_flag().is_set(e_task_flag_compress_is_dir) && (::str::find_file_extension("zip:", path) >= 0))
      {

         //auto pfile = get_reader(path);

         //return zip_get_file(pfile.m_p, eopenFlags);

         throw todo;

         return nullptr;

      }
      else if (::str::begins_eat(path, "file:///") || ::str::begins_eat(path, "file:\\\\\\"))
      {

         return get_file(path, eopenFlags);

      }
      else if (::str::begins_eat(path, "resource://") || ::str::begins_eat(path, "resource:\\\\"))
      {

         return resource_get_file(path);

      }
      else if (::str::begins(path, "http://") || ::str::begins(path, "https://"))
      {

         return http_get_file(payloadFile, eopenFlags);

      }
      else if (::str::begins_eat(path, "zipresource://"))
      {

         return create_resource_file(path);

      }
      else
      {
         //else if (::str::begins_eat_ci(path, "matter://"))
         //{

         //   __pointer(::application) pappLookup;

         //   string strApp = purl->get_server("matter://" + strPath);

         //   if (strApp == papp->m_strAppName)
         //   {

         //      strPath = purl->get_object("matter://" + strPath).Mid(1);

         //      pfile = App(papp).alloc(__type(::file::binary_file));

         //      ::extended::status = pfile->open(App(papp).dir().matter(strPath), nOpenFlags);

         //   }
         //   else if (&get_session() != nullptr && psession->appptra().lookup(strApp, pappLookup))
         //   {

         //      pfile = App(pappLookup).file().get_file("matter://" + strPath, nOpenFlags, &::extended::status);

         //   }
         //   else
         //   {

         //      strPath = App(papp).dir().matter(strPath);

         //      strPath = Sys(papp).get_matter_cache_path(strPath);

         //      pfile = get_file(strPath, nOpenFlags, &::extended::status);

         //   }

         //}
         //else
         //{

         //   //  return nullptr;




         //   /*            if((nOpenFlags & ::file::e_open_create) == 0 && !exists(strPath))
         //   {
         //   TRACE("::application::file does not exist!! : \"%s\"",strPath);
         //   return pfile;
         //   }
         //   */

         //if (nOpenFlags & ::file::e_open_text)
         //{

         //   pfile = __new(::file::stdio_file(pobject));

         //}
         //else

         if (eopenFlags & ::file::e_open_text)
         {

            //pfile = __create_new<::stdio_file>();

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


::file::path file_context::dropbox_info_network_payload()
{

   ::file::path pathNetworkPayload;

   pathNetworkPayload = m_psystem->m_pacmedir->home() / ".dropbox/info" NETWORK_PAYLOAD_DEFAULT_EXTENSION;

   return pathNetworkPayload;

}


::file::path file_context::onedrive_global_ini()
{

   ::file::path pathGlobalIni;

   pathGlobalIni = m_psystem->m_pacmedir->ca2roaming() / "OneDrive/settings/Personal/global.ini";

   return pathGlobalIni;

}


::file::path file_context::onedrive_cid_ini()
{

   ::file::path pathGlobalIni = onedrive_global_ini();

   string strIni = m_psystem->m_pacmefile->as_string(pathGlobalIni);

   if (strIni.is_empty())
   {

      return "";

   }

   ::property_set set;

   set.parse_ini(strIni);

   string strCid;
   
   strCid = set["cid"];

   ::file::path pathIni = m_psystem->m_pacmedir->ca2roaming() / "OneDrive/Settings/Personal/" + strCid + ".ini";

   return pathIni;

}
//
//::extended::status file_context::copy(::payload varTarget, ::payload varSource, bool bFailIfExists, e_extract eextract)
//{
//
//   return psystem->m_spfile->copy(varTarget, varSource, bFailIfExists, eextract, get_application());
//
//}

//
//::extended::status file_context::move(const ::file::path & pszNew, const ::file::path & pszOld)
//{
//
//   return psystem->m_spfile->move(pszNew, pszOld, get_application());
//
//}

//
//::extended::status file_context::del(const ::file::path & psz)
//{
//   return psystem->m_spfile->del(psz, get_application());
//}

//::extended::status file_context::rename(const ::file::path & pszNew, const ::file::path & pszOld)
//{
//   return psystem->m_spfile->rename(pszNew, pszOld, get_application());
//}

//void file_context::trash_that_is_not_trash(const ::file::path & psz)
//{
//   return psystem->m_spfile->trash_that_is_not_trash(psz, get_application());
//}
//
//void file_context::trash_that_is_not_trash(::file::patha & stra)
//{
//   return psystem->m_spfile->trash_that_is_not_trash(stra, get_application());
//}

//::extended::status file_context::replace(const ::file::path & pszContext, const string & pszFind, const string & pszReplace)
//{
//   return psystem->m_spfile->replace(pszContext, pszFind, pszReplace, get_application());
//}


//bool file_context::exists(const ::file::path & pszPath)
//{
//
//   return psystem->m_spfile->exists(pszPath, get_application());
//
//}


bool file_context::is_file_or_dir(const ::file::path &pszPath, ::file::enum_type *petype)
{

   return is_file_or_dir(pszPath, nullptr, petype);

}


/*  bool file_context::exists(const ::string & strPath)
   {

      return psystem->m_spfile->exists(strPath, get_application());

   }

   bool file_context::exists(const ::payload & payload)
   {

      const ::string & strPath = payload.get_string();


      return psystem->m_spfile->exists(strPath, get_application());

   }*/


//::payload file_context::length(const ::file::path & pszPath)
//{
//
//   return psystem->m_spfile->length(pszPath, get_application());
//
//}


//::payload file_context::length(const ::string & strPath)
//{


//   return psystem->m_spfile->length(strPath, get_application());

//}


//::payload file_context::length(const ::payload & payload)
//{

//   return psystem->m_spfile->length(payload.get_string(), get_application());

//}

//
//::file::path file_context::time(const ::file::path & pszBasePath, i32 iDepth, const string & pszPrefix, const string & pszSuffix)
//{
//
//   return psystem->m_spfile->time(get_application(), pszBasePath, iDepth, pszPrefix, pszSuffix);
//
//}


//::file::path file_context::time_square(const string & pszPrefix, const string & pszSuffix)
//{
//
//   return psystem->m_spfile->time_square(get_application(), pszPrefix, pszSuffix);
//
//}

//::file::path file_context::time_log(const string & pszId)
//{
//   return psystem->m_spfile->time_log(get_application(), pszId);
//}
//
//file_pointer file_context::time_square_file(const char * pszPrefix, const char * pszSuffix)
//{
//   return psystem->m_spfile->time_square_file(get_application(), pszPrefix, pszSuffix);
//}


//file_pointer file_context::get(const ::file::path & name)
//{
//
//   return psystem->m_spfile->get(name, get_application());
//
//}


//::payload file_context::as_network_payload(const ::payload & payloadFile)
//{
//
//   return psystem->m_spfile->as_network_payload(get_application(), payloadFile);
//
//}


//string file_context::as_string(const ::payload & payloadFile)
//{
//
//   return psystem->m_spfile->as_string(get_application(), payloadFile);
//
//}
//
//
//bool file_context::as_memory(const ::payload & payloadFile, memory_base & mem)
//{
//
//   return psystem->m_spfile->as_memory(get_application(), payloadFile, mem);
//
//}

//
//void file_context::lines(string_array & stra, const ::payload & payloadFile)
//{
//
//   return psystem->m_spfile->lines(stra, payloadFile, get_application());
//
//}
//
//
//void file_context::put_lines(const ::payload & payloadFile, const string_array & stra)
//{
//   return psystem->m_spfile->put_lines(payloadFile, stra, get_application());
//}
//
//bool file_context::put_contents(const ::payload & payloadFile, const void * pvoidContents, ::count count)
//{
//   return psystem->m_spfile->put_contents(payloadFile, pvoidContents, count, get_application());
//}
//
//bool file_context::put_contents(const ::payload & payloadFile, const char * pcszContents)
//
//{
//   return psystem->m_spfile->put_contents(payloadFile, pcszContents, get_application());
//
//}
//
//
//bool file_context::add_contents(const ::payload & payloadFile, const char * pcszContents)
//{
//
//   return psystem->m_spfile->add_contents(payloadFile, pcszContents, get_application());
//
//}


//bool file_context::put_contents(const ::payload & payloadFile, const ::stream & stream)
//{

//   return psystem->m_spfile->put_contents(payloadFile, stream, get_application());

//}


//bool file_context::put_contents(const ::payload & payloadFile, memory & mem)
//{
//
//   return psystem->m_spfile->put_contents(payloadFile, mem, get_application());
//
//}
//
//
//bool file_context::put_contents_utf8(const ::payload & payloadFile, const char * pcszContents)
//{
//
//   return psystem->m_spfile->put_contents_utf8(payloadFile, pcszContents, get_application());
//
//}

//
//string file_context::sys_temp(const char * lpszName, const char * pszExtension)
//{
//   return psystem->m_spfile->sys_temp(lpszName, pszExtension, get_application());
//}


::extended::transport < ::file::file > file_context::friendly_get_file(const ::payload &payloadFile, const ::file::e_open & eopenFlags)
{

   try
   {

      return get_file(payloadFile, eopenFlags);

   }
   catch (const ::exception & e)
   {

      return e;

   }
   catch (...)
   {

      return ::error_failed;

   }

}


//
//
//::file_transport file_context::get_file(const ::payload & payloadFile, ::u32 nOpenFlags)
//{
//
//   return m_pcontext->m_papexcontext->file().get_file(get_application(), payloadFile, nOpenFlags);
//
//}


//
//void file_context::dtf(const ::file::path & pszFile, const ::file::path & pszDir)
//{
//
//   return psystem->m_spfile->dtf(pszFile, pszDir, get_application());
//
//}

//bool file_context::is_read_only(const path & psz)
//{
//
//   return psystem->m_spfile->is_read_only(psz, get_application());
//}


//void file_context::dtf(const ::file::path & pszFile, ::file::patha & stra, ::file::patha & straRelative)
//{
//
//   return psystem->m_spfile->dtf(pszFile, stra, get_application());
//
//}
//
//
//void file_context::ftd(const ::file::path & pszDir, const ::file::path & pszFile)
//{
//
//   return psystem->m_spfile->ftd(pszDir, pszFile, get_application());
//
//}


bool file_context::crypto_set(const ::payload &payloadFile, const char *pszData, const char *pszSalt)
{

   throw ::interface_only_exception();

   return false;

}


bool file_context::crypto_get(const ::payload &payloadFile, string &str, const char *pszSalt)
{

   throw ::interface_only_exception();

   return false;

}


bool file_context::save_lines(const ::payload &payloadFile, string_array &stra)
{

   string str = stra.implode("\n");

   put_utf8_text(payloadFile, str);

   return true;

}


bool file_context::load_lines(string_array &stra, const ::payload &payloadFile)
{

   string str = as_string(payloadFile);

   stra.add_lines(str);

   return true;

}


//bool file_context::transfer(const path & pathOut, const path & pszSource)

//{

//   return m_pcontext->m_papexcontext->file().transfer(get_application(), pathOut, pszSource);


//}


//bool file_context::transfer(const path & pathOut, ::file::file * pfileIn)
//{

//   return m_pcontext->m_papexcontext->file().transfer(get_application(), pathOut, pfileIn);

//}


//bool file_context::transfer(const path & pathOut, ::file::file & reader)
//{

//   return m_pcontext->m_papexcontext->file().transfer(get_application(), pathOut, reader);

//}


//bool file_context::transfer(::file::file * pfileOut, ::file::file * pfileIn)
//{
//
//   return m_pcontext->m_papexcontext->file().transfer(get_application(), pfileOut, pfileIn);
//
//}


//bool file_context::transfer(file * pfileOut, ::file::file * pfileIn)
//{

//   return m_pcontext->m_papexcontext->file().transfer(get_application(), pfileOut, pfileIn);

//}


//bool file_context::transfer(file * pfileOut, ::file::file & is)
//{

//   return m_pcontext->m_papexcontext->file().transfer(get_application(), *pfileOut, is);

//}


//bool file_context::transfer(::file::file & os, const path & pszSource)
//{

//   return m_pcontext->m_papexcontext->file().transfer(get_application(), os, pszSource);

//}


//bool file_context::transfer(::file::file & os, ::file::file * pfileIn)
//{

//   return m_pcontext->m_papexcontext->file().transfer(get_application(), os, pfileIn);

//}


//bool file_context::transfer(::file::file & os, ::file::file & is)
//{

//   return m_pcontext->m_papexcontext->file().transfer(get_application(), os, is);

//}


bool file_context::touch(const ::file::path &path)
{

   if (!exists(path))
   {

      if (!put_memory(path, nullptr))
      {

         return false;

      }

   }

   return true;

}


::e_status file_context::update_module_path()
{

   auto psystem = get_system()->m_papexsystem;

   auto estatus = psystem->m_pfilesystem->update_module_path();

   if (!estatus)
   {

      return estatus;

   }

   return estatus;


}




void set_bypass_cache_if_empty(::payload & payloadFile)
{

   auto etype = payloadFile.m_etype;

   if(etype != e_type_element)
   {

      if(etype != e_type_property_set)
      {

         ::file::path path = payloadFile.get_file_path();

         payloadFile["url"] = path;

      }

      payloadFile["bypass_cache_if_empty"] = true;

   }

}


bool get_bypass_cache_if_empty(const ::payload & payloadFile)
{

   if(payloadFile.m_etype == e_type_property_set)
   {

      if(payloadFile.is_true("bypass_cache_if_empty"))
      {

         return true;

      }

   }

   return true;

}


