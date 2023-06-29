#include "framework.h"
#include "file_context.h"
#include "file_system.h"
#include "dir_context.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/io.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/folder.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/file/status.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/primitive/primitive/url.h"
#include "acme/primitive/primitive/url_domain.h"
#include "acme/parallelization/event.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task_flag.h"
#include "acme/platform/ini.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/system.h"
#include "acme/primitive/datetime/datetime.h"
#include "acme/primitive/primitive/read_only_memory.h"
#include "acme/primitive/string/base64.h"
//#include "acme/primitive/string/hex.h"
#include "acme/primitive/string/str.h"
#include "acme/user/user/conversation.h"
#include "acme/user/nano/nano.h"
#include "apex/crypto/crypto.h"
#include "apex/crypto/hasher.h"
#include "apex/filesystem/filesystem/dir_system.h"
#include "apex/networking/http/context.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"
#include "apex/platform/machine_event.h"
#include "apex/platform/machine_event_central.h"
#include "apex/platform/os_context.h"
#include "apex/platform/session.h"
#include "apex/platform/system.h"

//
//#ifdef WINDOWS_DESKTOP
//
////#include "apex/platform/app_core.h"
//
////#elif defined(UNIVERSAL_WINDOWS)
////#include "acme/_operating_system.h"
//#endif

#include <stdio.h>


#define UTF8_BOM "\xef\xbb\xbf"


////#include "apex/compress/zip/_.h"
#include "acme/constant/id.h"


#ifndef WINDOWS
#include <sys/stat.h>
#endif

//#define astr (*::apex::g_papexstrpool)

//#ifdef RASPBERRYPIOS
//#include <openssl/md5.h>
//#include <openssl/whrlpool.h>
//#include "apex/crypto/crypto_openssl.h"
//#endif


file_context::file_context()
{

}


file_context::~file_context()
{

}


void file_context::initialize(::particle * pparticle)
{

   /*auto estatus = */ ::object::initialize(pparticle);

   defer_create_synchronization();

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


bool file_context::exists(const ::file::path &pathParam)
{

   if (::is_null(m_pcontext))
   {

      throw ::exception(error_null_pointer);

   }

   ::file::path path = m_pcontext->m_papexcontext->defer_process_path(pathParam);

   if (path.flags().is_clear(::file::e_flag_required) && path.is_empty())
   {

      return false;

   }

   auto etype = safe_get_type(path);

   return etype == ::file::e_type_file || etype == ::file::e_type_element;

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


::file::enum_type file_context::get_type(const ::file::path &path, ::payload *pvarQuery)
{

   if (path.begins("http://") || path.begins("https://"))
   {

      property_set set;

      if (path.flags() & ::file::e_flag_required)
      {

         set["required"] = true;

      }

      if (path.flags() & ::file::e_flag_bypass_cache)
      {

         set["nocache"] = true;

      }

      return m_pcontext->m_papexcontext->http().get_type(path, pvarQuery, set);

   }

   if (::task_flag().is_set(e_task_flag_compress_is_dir))
   {

      auto iFind = ::str::find_file_extension("zip:", path);

      if (found(iFind))
      {

         if (!exists(path.substr(0, iFind + 4)))
         {

            return ::file::e_type_doesnt_exist;

         }

         throw todo;

         //compress_context compress(this);

         //::file::path pathZip;

         //string_array straPath;

         //if (!compress.get_patha(pathZip, straPath, path))
         //{

         //   return false;

         //}

         //auto pfile = file()->get_reader(pathZip);

         //zip_context zip(this);

         //return zip.is_file_or_dir(pfile, straPath, petype);

         return ::file::e_type_doesnt_exist;

      }

   }

   return ::file::e_type_unknown;

}


::file::enum_type file_context::safe_get_type(const ::file::path& path, ::payload* pvarQuery)
{

   if (path.begins("http://") || path.begins("https://"))
   {

      property_set set;

      if (path.flags() & ::file::e_flag_required)
      {

         set["required"] = true;

      }

      if (path.flags() & ::file::e_flag_bypass_cache)
      {

         set["nocache"] = true;

      }

      return m_pcontext->m_papexcontext->http().get_type(path, pvarQuery, set);

   }

   if (::task_flag().is_set(e_task_flag_compress_is_dir))
   {

      auto iFind = ::str::find_file_extension("zip:", path);

      if (found(iFind))
      {

         if (!exists(path.substr(0, iFind + 4)))
         {

            return ::file::e_type_doesnt_exist;

         }

         throw todo;

         //compress_context compress(this);

         //::file::path pathZip;

         //string_array straPath;

         //if (!compress.get_patha(pathZip, straPath, path))
         //{

         //   return false;

         //}

         //auto pfile = file()->get_reader(pathZip);

         //zip_context zip(this);

         //return zip.is_file_or_dir(pfile, straPath, petype);

         return ::file::e_type_doesnt_exist;

      }

   }

   return ::file::e_type_unknown;

}


::payload file_context::length(const ::file::path &pszPath)
{

   return length(pszPath, nullptr);

}


::payload file_context::length(const ::file::path &path, ::payload *pvarQuery)
{

   throw ::interface_only();

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
//   if (!GetFileAttributesExW(utf8_to_unicode(path), GetFileExInfoStandard, &data))
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

   auto psystem = acmesystem()->m_papexsystem;

   auto pfilesystem = psystem->m_pfilesystem;

   return pfilesystem->m_pathModule;

}


//::file::path file_context::ca2module()
//{
//
//   auto psystem = acmesystem()->m_papexsystem;
//
//   return psystem->m_pfilesystem->m_pathCa2Module;
//
//}


::file::path file_context::time_square(const string &pszPrefix, const string &pszSuffix)
{

   return time(dir()->time_square(), 25, pszPrefix, pszSuffix);

}


::file::path file_context::time_log(const string &pszId)
{
   return time(dir()->time_log(pszId), 9);
}


::file::path
file_context::time(const ::file::path &psz, i32 iMaxLevel, const string &pszPrefix, const string &pszSuffix,
                   bool bTryDelete)
{

   auto psystem = acmesystem()->m_papexsystem;

   synchronous_lock lockMachineEvent(psystem->synchronization());

   ::file::path str;

   ::file::path path;

   string strPrefix(pszPrefix);

   string strSuffix(pszSuffix);

   restart:

   str.empty();

   str = psz;

   dir()->create(str);

   ::file::listing listing;

   string strFormat;

   int iIncLevel = 0;

   for (i32 i = 1; i <= iMaxLevel;)
   {

      dir()->create(str);

      if (!dir()->is(str))
      {

         throw ::exception(error_path_not_found, "time square dir does not exist");

      }

      listing.set_listing(str);

      dir()->enumerate(listing);

      if (i < iMaxLevel)
      {

         i32 iMax = filterex_time_square("", listing);

         if (iMax == -1)
         {

            str /= "00";

            dir()->create(str);

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

               dir()->create(str);

            }

         }

         i++;

      }
      else // if i == iMaxLevel
      {

         listing.set_listing(str);

         dir()->enumerate(listing);

         i32 iMax = bTryDelete ? 0 : filterex_time_square(pszPrefix, listing);

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


i32 file_context::filterex_time_square(const ::scoped_string & scopedstrPrefix, ::file::path_array &stra)
{

   i32 iMax = -1;

   i32 iIndex;

   for (i32 i = 0; i < stra.size(); i++)
   {

      string str = stra[i].name();

      if (str.case_insensitive_begins_eat(scopedstrPrefix))
      {

         if (str.length() < 2)
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

         iIndex = atoi(str.substr(0, 2));

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

   if (file()->exists(path))
   {

      if (!bTryDelete)
      {

         return false;

      }

      file()->erase(path);

      if (file()->exists(path))
      {

         return false;

      }

   }

   ::pointer<::file::file>pfile;

   __construct(pfile);

   if (!m_estatus)
   {

      return false;

   }

   pfile->open(path, ::file::e_open_create | ::file::e_open_binary | ::file::e_open_no_exception_on_open);

   if (::failed(pfile->m_estatus))
   {

      return false;

   }

   return true;

}


::payload file_context::as_network_payload(const ::payload & payloadFile)
{

   string str = as_string(payloadFile);

   str.trim();

   if (str.is_empty())
   {

      return ::e_type_new;

   }

   const char *pszJson = str;

   ::payload v;

   v.parse_network_payload(pszJson);

   return v;

}


::payload file_context::safe_get_network_payload(const ::payload & payloadFile)
{

   string str = safe_get_string(payloadFile);

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

      information() << e.get_message();

      v = ::e_type_new;

   }
   catch (...)
   {

      information() << "GENERAL Exception parsing network_payload file_context::as_network_payload : \"" << str << "\"";

      v = ::e_type_new;

   }

   return v;

}


string file_context::as_string(const ::payload & payloadFile)
{

   memory memory;

   as_memory(payloadFile, memory);

   return memory.as_utf8();

}


string file_context::safe_get_string(const ::payload & payloadFile, ::e_status * pestatus)
{

   memory memory;

   safe_get_memory(payloadFile, memory, pestatus);

   return memory.as_utf8();

}


void file_context::as_memory(const ::payload &payloadFile, memory_base &mem)
{

   file_pointer pfile;

   //try
   //{

      pfile = get_file(payloadFile, ::file::e_open_share_deny_none | ::file::e_open_read | ::file::e_open_binary);

//      if (!pfile)
//      {
//
//         return false;
//
//      }
//      else if (::failed(pfile->m_estatus))
//      {
//
//         return false;
//
//      }
//
//   }
//   catch (const ::exception & exception)
//   {
//
//      if (bNoExceptionOnFail)
//      {
//
//         return false;
//
//      }
//
//      throw exception;
//
//   }

//   try
  // {

   mem = pfile->full_memory();


//      {
//
//         return false;
//
//      }

     //return true;

  // }
  // catch (...)
  // {

  // }

   //return false;

}


void file_context::safe_get_memory(const ::payload &payloadFile, memory_base &mem, ::e_status * pestatus)
{

   file_pointer pfile;

   try
   {

      pfile = get_file(payloadFile, ::file::e_open_file | ::file::e_open_share_deny_none | ::file::e_open_read | ::file::e_open_binary | ::file::e_open_no_exception_on_open);

      if (!pfile)
      {

         return;

      }
      else if (::failed(pfile->m_estatus))
      {

         return;

      }

   }
   catch (const ::exception & exception)
   {

      auto psequencer = nano()->exception_message_console(exception);

      psequencer->do_asynchronously();

   }

   try
   {

      pfile->full_memory(mem);

   }
   catch (...)
   {

   }

}


::memory file_context::as_memory(const ::payload &payloadFile)
{

   ::memory memory;

   as_memory(payloadFile, memory);

   return ::transfer(memory);

}


::memory file_context::safe_get_memory(const ::payload &payloadFile)
{

   ::memory memory;

   safe_get_memory(payloadFile, memory);

   return ::transfer(memory);

}


memsize file_context::read(const ::payload& payloadFile, void * p, filesize position, memsize size, bool bNoExceptionOnFail)
{

   file_pointer pfile;

   try
   {

      pfile = get_file(payloadFile, ::file::e_open_share_deny_none | ::file::e_open_read | ::file::e_open_binary | (bNoExceptionOnFail ? ::file::e_open_no_exception_on_open : 0));

      if (!pfile)
      {

         return -1;

      }
      else if (::failed(pfile->m_estatus))
      {

         return -1;

      }

   }
   catch (const ::exception& exception)
   {

      if (bNoExceptionOnFail)
      {

         return -1;

      }

      throw exception;

   }

   memsize sizeToRead = (memsize) minimum(size, pfile->size() - position);

   if (position > 0)
   {

      pfile->set_position(position);

   }

   auto sizeRead = pfile->read({ p, sizeToRead });

   return sizeRead;

}


memsize file_context::read_beginning(const ::payload& payloadFile, void* p, memsize size, bool bNoExceptionOnFail)
{

   return read(payloadFile, p, 0, size, bNoExceptionOnFail);

}


memory file_context::beginning(const ::payload& payloadFile, memsize size, bool bNoExceptionOnFail)
{

   memory mem;

   mem.set_size(size);

   auto sizeRead = read(payloadFile, mem.data(), mem.size(), bNoExceptionOnFail);

   mem.set_size(sizeRead);

   return ::transfer(mem);

}


void file_context::put_lines(const ::payload &payloadFile, const string_array &stra, const plain_text_file_options & options)
{

   //try
   //{

      auto pfile = get_file(payloadFile, ::file::e_open_write | ::file::e_open_truncate | ::file::e_open_create | ::file::e_open_defer_create_directory);

      if (!pfile)
      {

         throw ::exception(error_failed);

      }

      if (options.m_bUtf8Bom)
      {

         pfile->write({ UTF8_BOM, STATIC_ASCII_STRING_LENGTH(UTF8_BOM) });

      }

      pfile->put_lines(stra);

      //return success;

   //}
   //catch (...)
   //{

   //}

   //return error_exception;

}


//void file_context::put_lines_utf8(const ::payload &payloadFile, const string_array &stra)
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


void file_context::get_lines(string_array &stra, const ::payload &payloadFile, bool bAddEmpty, bool bNoExceptionIfFailToOpen)
 {

   file_pointer pfile;

   try
   {

      pfile = get_file(payloadFile, ::file::e_open_file |
      ::file::e_open_share_deny_none | ::file::e_open_read | ::file::e_open_binary
      |(bNoExceptionIfFailToOpen ? ::file::e_open_no_exception_on_open : 0));

      if (bNoExceptionIfFailToOpen)
      {

         if (pfile.nok())
         {

            return;

         }

      }

   }
   catch (const ::exception& exception)
   {

      if (bNoExceptionIfFailToOpen)
      {

         return;

      }

      throw exception;

   }

   pfile = create_memory_file_by_reading(pfile);

   string strLine;

   while (pfile->read_string(strLine))
   {

      if (bAddEmpty || !strLine.is_empty())
      {

         stra.add(strLine);

      }

   }

}


void file_context::put_memory(const ::payload &payloadFile, const block & block)
{

   file_pointer pfile;

   pfile = get_file(payloadFile,
                     ::file::e_open_binary
      | ::file::e_open_write
      | ::file::e_open_create
      | ::file::e_open_share_deny_write
      | ::file::e_open_no_truncate
      | ::file::e_open_defer_create_directory);

   if (pfile.nok())
   {

      throw ::exception(error_io);

   }

   pfile->set_size(0);

   if(block.size() > 0)
   {

      pfile->write(block);

   }

   //return true;

}


void file_context::add_contents(const ::payload &payloadFile, const ::scoped_string & scopedstr)
{

   file_pointer pfile;

   //try
   //{

      pfile = get_file(payloadFile,
                        ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_no_truncate |
                        ::file::e_open_share_exclusive | ::file::e_open_defer_create_directory);

   //}
   //catch (...)
   //{

   //   return false;

   //}

   if (!pfile)
   {

      throw ::exception(error_io);

   }

   pfile->seek_to_end();

   pfile->write(scopedstr);

}


void file_context::put_text(const ::payload& payloadFile, const ::scoped_string & scopedstr)
{

   if (scopedstr.data() == nullptr || scopedstr.is_empty())
   {

      return put_memory(payloadFile, nullptr);

   }

   string strContents(scopedstr);

   ::str::fix_eol(strContents);

   return put_memory(payloadFile, strContents);

}


//void file_context::add_contents(const ::payload &payloadFile, const ::scoped_string & scopestrContents)
//{
//
//   return add_contents(payloadFile, scopestrContents.begin(), scopestrContents.size());
//
//}


void file_context::put_memory(const ::payload &payloadFile, ::file::file *pfileSrc)
{

   auto pfile = get_file(payloadFile,
                     ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_share_deny_write |
                     ::file::e_open_defer_create_directory);

   if (!pfile)
   {

      throw ::exception(error_io);

   }

   pfile->set_size(0);

   if (::is_set(pfileSrc))
   {

      memory mem;

      auto remainingByteCount = pfileSrc->get_remaining_byte_count();

      mem.set_size(minimum((memsize) remainingByteCount, (memsize) 8MiB));

      memsize uRead;

      while ((uRead = pfileSrc->read(mem)) > 0)
      {

         pfile->write(mem(0, uRead));

      }

   }

   //return ::success;

}


//bool file_context::put_contents(const ::payload &payloadFile, memory &mem)
//{
//
//   return put_contents(payloadFile, mem.data(), (count) mem.size());
//
//}


void file_context::put_text_utf8(const ::payload &payloadFile, const ::scoped_string & scopedstr)
{

   auto pfile = get_file(payloadFile,
                     ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_share_deny_none |
                     ::file::e_open_defer_create_directory);

   if (!pfile)
   {

      throw ::exception(error_io);

   }

   pfile->write({ UTF8_BOM, STATIC_ASCII_STRING_LENGTH(UTF8_BOM) });

   string strContents(scopedstr);

   ::str::fix_eol(strContents);

   pfile->write(strContents);

   //return true;

}


void file_context::calculate_main_resource_memory()
{


}


::block file_context::get_main_resource_block()
{

   if(subsystem()->m_blockMatter.is_set())
   {

      return subsystem()->m_blockMatter;

   }

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

   try
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto & pfactory = acmesystem()->folder_factory();

      if (m_bFolderResourceCalculated)
      {

         if (!m_pfolderResource)
         {

            information("m_pfolderResource is null? Why?");

         }

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

      acmesystem()->m_pfactoryFolder->__construct(m_pcontext, m_pfolderResource);

      m_pfolderResource->initialize(this);

      m_pfolderResource->open_for_reading(pfile);
      //if (!)
      //{


      //   return nullptr;

      //}

      return m_pfolderResource;

   }
   catch (...)
   {

      return nullptr;

   }

}


::memory_file_pointer file_context::create_resource_file(const ::file::path & path)
{

   ::folder * pfolder = nullptr;

   {

      synchronous_lock synchronouslock(this->synchronization());

      pfolder = resource_folder();

      if (::is_null(pfolder))
      {

         return nullptr;

      }

   }

   synchronous_lock synchronouslock(pfolder->synchronization());

   string strPath(path);

   strPath.replace_with("/", "\\");

   ::information(strPath);

   fflush(stdout);

   if (!pfolder->locate_file(strPath))
   {

      return nullptr;

   }

   auto pfile = pfolder->get_file();

   if (pfile.nok())
   {

      return nullptr;

   }

   auto pfileOutput = create_memory_file();

   transfer(pfileOutput, pfile);

   pfileOutput->seek_to_begin();

   pfileOutput->m_estatus = ::success;

   pfileOutput->set_ok_flag();

   if(strPath.contains("256"))
   {

      information("contains 256");

      fflush(stdout);

      if(pfileOutput.nok())
      {

         information("output file nok");

         fflush(stdout);

      }

   }

   return pfileOutput;

}


::memory file_context::get_resource_memory(const ::file::path & path)
{

   auto pfile = create_resource_file(path);

   if (!pfile)
   {

      return {};

   }

   return ::transfer(*pfile->memory().m_pprimitivememory);

}


::file::enum_type file_context::resource_get_type(const ::file::path & path)
{

   ::folder* pfolder = nullptr;

   {

      synchronous_lock synchronouslock(this->synchronization());

      pfolder = resource_folder();

      if (::is_null(pfolder))
      {

         return ::file::e_type_doesnt_exist;

      }

   }

   synchronous_lock synchronouslock(pfolder->synchronization());

   string strPath(path);

   strPath.replace_with("/", "\\");

   strPath.trim_right("\\/");

   if (pfolder->locate_file(strPath))
   {

      return ::file::e_type_file;

   }

   if (pfolder->locate_folder(strPath))
   {

      return ::file::e_type_folder;

   }

   return ::file::e_type_doesnt_exist;

}


void file_context::copy(::payload varTarget, ::payload varSource, bool bFailIfExists, enum_extract eextract)
{

   if (dir()->is(varSource.as_file_path()) &&
       (eextract == e_extract_first || eextract == e_extract_all || !(string_ends_ci(varSource.as_file_path(), ".zip"))))
   {

      ::file::listing listing;

      listing.set_listing(varSource, e_depth_recursively);

      dir()->enumerate(listing);

      ::file::path strDst;
      ::file::path strSrc;
      ::file::path strDirSrc(varSource.as_file_path());
      ::file::path strDirDst(varTarget.as_file_path());

      if (::task_flag().is_set(e_task_flag_compress_is_dir) && (string_ends(strDirSrc, ".zip")))
      {

         strDirSrc += ":";

      }

      for (i32 i = 0; i < listing.size(); i++)
      {

         strSrc = listing[i];

         strDst = strSrc;

         strDst.case_insensitive_begins_eat(strDirSrc);

         strDst = strDirDst / strDst;

         if (dir()->is(strSrc))
         {

            if ((eextract == e_extract_first || eextract == e_extract_none) &&
                (string_ends_ci(varSource.as_file_path(), ".zip")))
            {
            }
            else
            {
               dir()->create(strDst);
            }
         }
         else
         {
            if (!dir()->is(strDst.folder()))
            {
               dir()->create(strDst.folder());
            }
            copy(strDst, strSrc, bFailIfExists, eextract == e_extract_all ? e_extract_all : e_extract_none);

         }
      }
      return;
   }

   auto preader = varSource.cast < ::file::file >();

   bool bSourceEmpty = varSource.as_file_path().is_empty();

   if(bSourceEmpty && preader.nok())
   {

      throw ::exception(error_bad_argument);

   }

   auto pwriter = varTarget.cast < ::file::file >();

   bool bTargetEmpty = varTarget.as_file_path().is_empty();

   if (bTargetEmpty && pwriter.nok())
   {

      throw ::exception(error_bad_argument);

   }


   if(pwriter.nok())
   {

      if (!dir()->is(varTarget.as_file_path().folder()))
      {

         dir()->create(varTarget.as_file_path().folder());

      }

   }

   auto psystem = acmesystem();

   auto pacmefile = psystem->m_pacmefile;

   ::file::path pathTarget;

   if(pwriter.nok())
   {

      pathTarget = psystem->defer_process_path(varTarget.as_file_path());

   }

   ::file::path pathSource;

   if(preader.nok())
   {

      pathSource = psystem->defer_process_path(varSource.as_file_path());

      if (exists(pathSource))
      {

         pacmefile->copy(pathTarget, pathSource, !bFailIfExists);

         return;

      }

   }

   if (bFailIfExists)
   {

      if (exists(varTarget))
      {

         throw ::exception(error_failed);

      }

   }

   ::payload varNew;

   if (pwriter.nok()&& dir()->is(varTarget) && (varSource.as_file_path().name().has_char() && preader.nok()))
   {

      varNew = ::file::path(varTarget) / varSource.as_file_path().name();

   }
   else
   {

      varNew = varTarget;

   }


   bool bGeneralFailure = false;

   bool bOutputFail = false;
   bool bInputFail = false;

   try
   {

      if(preader.nok())
      {

         preader = get_reader(varSource,
                              ::file::e_open_read | ::file::e_open_binary | ::file::e_open_share_deny_none);

         if (preader.nok())
         {

            string strError;

            strError.format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open input file",
                            varSource.as_file_path().c_str(), varNew.as_file_path().c_str(), bFailIfExists);

            throw ::exception(::error_io, strError);

         }

      }

      if(pwriter.nok())
      {

         pwriter = get_file(varNew,
                            ::file::e_open_write | ::file::e_open_binary | ::file::e_open_create |
                            ::file::e_open_defer_create_directory |
                            ::file::e_open_share_deny_write);

         if (pwriter.nok())
         {

            string strError;

            strError.format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open output file",
                            varSource.as_file_path().c_str(), varNew.as_file_path().c_str(), bFailIfExists);

            throw ::exception(::error_io, strError);

         }

      }

      file()->transfer(pwriter, preader);

      bool bStatusFail = false;

      ::file::file_status st;

      try
      {

         st = preader->get_status();

      }
      catch (...)
      {

         bStatusFail = true;

         {

            auto information = this->information();

            information << "During copy, failed to get status from input file \"";

            information << varSource.as_file_path();

            information << "\" bFailIfExists = ";

            information << (bFailIfExists ? "true" : "false");

         }

      }

      if (!bStatusFail)
      {

         try
         {

            st = preader->get_status();

         }
         catch (...)
         {

            bStatusFail = true;

            information() << "During copy, failed to set status to output file \""
               << varTarget.as_file_path() << "\" bFailIfExists=" << (bFailIfExists ? "true" : "false");

         }

      }

      try
      {

         pwriter->flush();

      }
      catch (...)
      {

      }

      try
      {

         pwriter->close();

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
            varSource.as_file_path().c_str(), varTarget.as_file_path().c_str(), bFailIfExists);
         throw ::exception(::error_io, strError);
      }
      else
      {
         string strError;
         strError.format("During copy, failed to close input file \"%s\" bFailIfExists=%d",
                         varSource.as_file_path().c_str(), bFailIfExists);
         throw ::exception(::error_io, strError);
      }
   }
   else if (bOutputFail)
   {
      string strError;
      strError.format("During copy, failed to close output file \"%s\" bFailIfExists=%d",
                      varTarget.as_file_path().c_str(), bFailIfExists);
      throw ::exception(::error_io, strError);
   }

   //}

   //return ::success;

}


//::extended::status file_context::update_to_newer(::payload varTarget, ::payload varSource)
//{
//
//
//}

void file_context::transfer(const ::file::path &pszNew, const ::file::path &psz)
{

   throw ::interface_only();

   //throw ::interface_only();

//#ifdef WINDOWS_DESKTOP
//
//   if (!::MoveFileW(
//      utf8_to_unicode(psz),
//      utf8_to_unicode(pszNew)))
//   {
//
//      DWORD dwError = ::GetLastError();
//
//      if (dwError == ERROR_ALREADY_EXISTS)
//      {
//
//         if (::CopyFileW(
//            utf8_to_unicode(psz),
//            utf8_to_unicode(pszNew),
//            false))
//         {
//
//            if (!::DeleteFileW(utf8_to_unicode(psz)))
//            {
//
//               dwError = ::GetLastError();
//
//               string strError;
//
//               strError.Format("Failed to delete the file to transfer \"%s\" error=%d", psz, dwError);
//
//               information("%s", strError);
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
//      strError.Format("Failed to transfer file \"%s\" to \"%s\" error=%d", psz, pszNew, dwError);
//
//      throw ::exception(io_exception(::error_io, strError));
//
//   }
//
//#elif defined(UNIVERSAL_WINDOWS)
//
//   ::winrt::Windows::Storage::StorageFile ^ file = get_os_file(psz, 0, 0, nullptr, OPEN_EXISTING, 0, nullptr);
//
//   if (file == nullptr)
//   {
//
//      //information("test");
//
//      throw ::exception(::exception("file::file_context::transfer Could not transfer file, could not open source file"));
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
//      throw ::exception(::exception(strError));
//   }
//#endif
//
//   return ::success;

}


void file_context::erase(const ::file::path & path)
{

   throw ::interface_only();

   //throw ::interface_only();

//#ifdef WINDOWS_DESKTOP
//
//   HANDLE h = ::CreateFileW(utf8_to_unicode(string("\\\\?\\") + psz),
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
//   /*      if(!::DeleteFileW(utf8_to_unicode(string("\\\\?\\") + psz)))
//   {
//   u32 dwError = ::get_last_error();
//   if(dwError == 2) // the file does not exist, so delete "failed"
//   return;
//   string strError;
//   strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);
//   throw ::exception(io_exception(strError));
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
//         throw ::exception(::exception(strError));
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
   if (dir()->is(psz))
   {
      i32 i = 1;
      while (i <= 100)
      {
         strNew.format("%s-%s-%d", psz.c_str(), strCopy.c_str(), i);
         if (!exists(strNew))
         {
            copy(strNew, psz, false, e_extract_all);
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
            copy(strNew, psz, false, e_extract_all);
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

      copy(pathNew, path, false, e_extract_all);

      return pathNew;

   }

}


void file_context::trash_that_is_not_trash(const ::file::path &psz)
{

   ::file::path strDir = dir()->trash_that_is_not_trash(psz);

   dir()->create(strDir);

   transfer(strDir / psz.name(), psz);

}



void file_context::trash_that_is_not_trash(::file::path_array& stra)
{

   if (stra.size() <= 0)
   {

      return;

   }

   ::file::path strDir = dir()->trash_that_is_not_trash(stra[0]);

   dir()->create(strDir);

   for (i32 i = 0; i < stra.size(); i++)
   {

      transfer(strDir / stra[i].name(), stra[i]);

   }

}



void file_context::get_status(::file::file_status & status, const ::file::path &path)
{

   UNREFERENCED_PARAMETER(status);
   UNREFERENCED_PARAMETER(path);

   throw ::interface_only();

   //return false;

}


void file_context::set_status(const ::file::path &path, const ::file::file_status &status)
{

   UNREFERENCED_PARAMETER(path);
   UNREFERENCED_PARAMETER(status);

   throw ::interface_only();

   //return ::success;

}


void file_context::replace_with(const ::file::path & pathContext, const string & strNew, const string & strOld)
{

   ::file::listing listing;

   string strOldName;

   string strNewName;

   listing.set_listing(pathContext);

   dir()->enumerate(listing);

   for (i32 i = 0; i < listing.size(); i++)
   {

      strOldName = listing[i].name();

      strNewName = strOldName;

      strNewName.replace_with(strNew, strOld);

      if (strNewName != strOldName)
      {
         // TODO(camilo) : should there be a way to chain or return multiple exceptions... instead of ::extended::status specifile file smart...
         // why not a super smart chained super hand heroe smarter pointerer that can contain vector of any excepction based on
         // ::exception like (::file::exception) (I supposed ::file::exception is already based on ::exception OMG CAMILO!!!)
         // and may be then replace could do replace for example on HTTP servers and return may io_exception and not tighted
         // to a barely translated io exception into a empty ::file::exception with improper filled members....
         transfer(pathContext / strNewName, pathContext / strOldName);

      }

   }
   //if (strFail.has_char())
   //{
   //   App(papp).message_box(nullptr, strFail, e_message_box_icon_exclamation);
   //}

   //return e;


}


void file_context::transfer(::file::file *pfileOut, ::file::file *pfileIn)
{

   //try
   //{

      pfileOut->write(pfileIn);

   //}
   //catch (...)
   //{

   //   //return false;

   //}

   //return true;

}


bool file_context::is_read_only(const ::file::path &psz)
{

   //throw ::interface_only();

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
//#elif defined(UNIVERSAL_WINDOWS)
//
//   throw ::exception(todo);
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


file_pointer file_context::resource_get_file(const ::file::path & path)
{

   throw ::interface_only();

   return nullptr;

}


::file::path file_context::sys_temp(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension)
{


   string strTempDir = acmedirectory()->sys_temp();

   if (!string_ends(strTempDir, "\\") && !string_ends(strTempDir, "/"))
   {

      strTempDir += "\\";

   }

   string str;

   char buf[30];

   for (i32 i = 0; i < 1000; i++)
   {

      sprintf(buf, "%d", i);

      str = strTempDir;
      str += scopedstrName;
      str += "-";
      str += buf;
      str += ".";
      str += scopedstrExtension;

      if (!exists(str))
      {

         return str;

      }

   }

   return "";

}


::file::path file_context::sys_temp_unique(const ::file::path &lpszName)
{

   return acmedirectory()->sys_temp() / lpszName;

}


file_pointer file_context::time_square_file(const string &pszPrefix, const string &pszSuffix)
{

   return get(time_square(pszPrefix, pszSuffix));

}


file_pointer file_context::get(const ::file::path &name)
{

   dir()->create(name.name());

   file_pointer fileOut = get_file(name, ::file::e_open_create | ::file::e_open_binary | ::file::e_open_write);

//   if (fileOut.is_null())
//   {

//      throw ::file::exception(error_file_not_found, -1L, -1, name);

//   }

   return fileOut;

}


::file_pointer file_context::get_temporary_upload_file(const ::file::path &pathCurrent)
{

   int i = 0;

   //static ::pointer < ::mutex > s_mutex(nullptr);

   //single_lock synchronouslock(&s_mutex, true);

   ::earth::time timeFile = ::earth::time::now();

   ::string strIndex;

   ::string strTime;

   ::string strTempFile;

   while (true)
   {

      strTime = datetime()->format("%Y\\%m\\%d\\%H\\%M\\%S\\", timeFile);

      strIndex.format("%08x\\", i);

      strTempFile = m_pcontext->acmesystem()->m_papexsystem->m_pdirsystem->m_pathUpload / (strTime + strIndex + pathCurrent);

      if (!exists(strTempFile))
      {

         break;

      }

      string strMessage;

      auto psystem = acmesystem()->m_papexsystem;

      auto pdatetime = psystem->datetime();

      strMessage = pdatetime->international().get_date_time() + " " + strTempFile;

      acmefile()->append_wait("C:\\ca2\\toomuchuploads.txt", strMessage);

      i++;

   }

   auto pfileUpload = get_file(strTempFile,
                               ::file::e_open_defer_create_directory
                               | ::file::e_open_binary
                               | ::file::e_open_create
                               | ::file::e_open_write);

   return pfileUpload;

}


::file::path file_context::replace_with_extension(const ::string & strExtension, const ::file::path & path)
{

   ::file::path pathNew(path);

   set_extension(pathNew, strExtension);

   return pathNew;

}


void file_context::set_extension(::file::path & path, const ::scoped_string & scopedstrExtension)
{

   strsize iEnd = path.rear_find_index('.');

   if (iEnd < 0)
   {

      iEnd = path.length();

   }

   path = path.left(iEnd) + ::str::has_char(scopedstrExtension, ".");

}


void file_context::normalize(string &str)
{

   if (str.is_empty())
   {

      return;

   }

   while (str.has_char() &&
          (str.right(1) == "\\" ||
           str.right(1) == "/"))
   {

      str = str.left(str.length() - 1);

   }

}


::std::strong_ordering file_context::cmp(const ::file::path &psz1, const ::file::path &psz2)
{
   string str1(psz1);
   normalize(str1);
   string str2(psz2);
   normalize(str2);
   return str1.case_insensitive_order(str2);
}


void file_context::rename(const ::file::path &pszNew, const ::file::path &psz)
{

   ::file::path strDir = psz.folder();

   ::file::path strDirNew = pszNew.folder();

   if (strDir != strDirNew)
   {

      // rename should work only on files in the same directory/folder

      throw ::exception(::error_failed);

   }

   //if (transfer(pszNew, psz).failed())
   transfer(pszNew, psz);
   //{

   //   return ::error_failed;

   //}

   //return ::success;

}


//void file_context::dtf(const ::file::path & pszFile, const ::file::path & pszDir)
//{
//
//   ::file::listing ls;
//
//   dir()->rls(ls, pszDir);
//
//   dtf(pszFile, ls);
//
//}
//
//
//void file_context::dtf(const ::file::path & pszFile, ::file::path_array & stra)
//{
//
//   file_pointer pfile = get_file(pszFile, ::file::e_open_create | ::file::e_open_write | ::file::e_open_binary);
//
//   if (pfile.is_null())
//   {
//
//      throw ::exception(::exception("failed"));
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
//   ::pointer<::file::file>pfile2;
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
//   for (i32 i = 0; i < stra.size(); i++)
//   {
//      if (string_ends_ci(stra[i], ".zip"))
//      {
//      }
//      else if (dir()->is(stra[i]))
//         continue;
//      write_n_number(pfile, nullptr, 1);
//      iPos = pfile->get_position();
//      write_gen_string(pfile, nullptr, strMd5);
//      MD5_Init(&ctx);
//      string strRelative = stra[i].relative();
//      write_gen_string(pfile, &ctx, strRelative);
//      if (pfile2->open(stra[i], ::file::e_open_read | ::file::e_open_binary).failed())
//         throw ::exception(::exception("failed"));
//      write_n_number(pfile, &ctx, (i32)pfile2->size());
//      while ((uRead = pfile2->read(buf, iBufSize)) > 0)
//      {
//         pfile->write(buf, uRead);
//         MD5_Update(&ctx, buf, (size_t)uRead);
//      }
//      pfile->seek(iPos, ::e_seek_set);
//      strMd5 = as_string(ctx);
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
//      throw ::exception(::exception("failed"));
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
//         dir()->create(strPath.folder());
//         if (pfile2->open(strPath, ::file::e_open_create | ::file::e_open_binary | ::file::e_open_write).failed())
//            throw ::exception(::exception("failed"));
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
//         strMd5New = as_string(ctx);
//         if (strMd5 != strMd5New)
//            throw ::exception(::exception("failed"));
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
//      MD5_Update((MD5_CTX *)pctx, (const char *)str, (i32)str.length());
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
//      throw ::exception(::exception("failed"));
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
//   ::count iLen = str.length();
//   write_n_number(pfile, pctx, iLen);
//   pfile->write((const char *)str);
//   if (pctx != nullptr)
//   {
//      MD5_Update((MD5_CTX *)pctx, (const char *)str, (i32)str.length());
//   }
//}

//void file_context::read_gen_string(::file::file * pfile, void * pctx, string & str)
//{
//   i64 iLen;
//   read_n_number(pfile, pctx, iLen);
//   char * psz = str.get_buffer((strsize)(iLen + 1));
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
//   str.release_buffer();
//}


::pointer < ::file::link > file_context::resolve_link(const ::file::path &path)
{

   return m_pcontext->m_papexcontext->os_context()->resolve_link(path);

}


string file_context::get_hash(const ::payload &payloadFile, enum_hash ehash)
{

   auto pfile = get_file(payloadFile, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_none);

   if (!pfile)
   {

      return "";

   }

   memory mem;

   mem.set_size(1024 * 256);

   auto psystem = acmesystem()->m_papexsystem;

   auto pcrypto = psystem->crypto();

   auto phasher = pcrypto->create_hasher(ehash);

   memsize iRead;

   while ((iRead = (memsize) pfile->read(mem)) > 0)
   {

      phasher->update(mem(0, iRead));

   }

   return ::hex::upper_case_from(phasher->get_hash_and_reset());

}


string file_context::md5(const ::payload &payloadFile)
{

   return get_hash(payloadFile, e_hash_md5);

}


string file_context::nessie(const ::payload &payloadFile)
{

   throw ::exception(todo, "nessie");

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

   //while ((iRead = (memsize)pfile->read(mem.data(), mem.size())) > 0)
   //{

   //   WHIRLPOOL_Update(&ns, mem.data(), (size_t)iRead);

   //}

   //return as_string(ns);

}


void file_context::get_last_write_time(file_time_t *pfile_time, const string &strFilename)
{

   throw ::interface_only();

   //return false;

}


void file_context::init_system()
{

//   auto psystem = acmesystem()->m_papexsystem;
//
//   auto estatus = psystem->m_pfilesystem->update_module_path();
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
   //return ::success;

}


void file_context::init_context()
{

   //return ::success;

}


//bool file_context::prepare_output(::stream & outputstream, path & pathDownloading, const ::stream & os)
//{

//   Sys(pparticle).dir()->mk(pathOut.folder());

//   file_pointer fileOut;

//   i64 iTry = 0;

//   ::application * papp = ::get_app(pparticle);

//   while (true)
//   {

//      pathDownloading = pathOut + ".downloading." + ::str::zero_pad(as_string(iTry), 20);

//      fileOut = papp->file()->get_file(pathDownloading, ::file::e_open_defer_create_directory | ::file::e_open_create | ::file::e_open_binary | ::file::e_open_write);

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

//   file_pointer fileIn = Sess(pparticle).file()->get_file(pathIn, ::file::e_open_binary | ::file::e_open_read);

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


void file_context::post_output(const ::file::path & pathOut, const ::file::path & pathDownloading)
{

   try
   {

      rename(pathOut, pathDownloading);

   }
   catch (...)
   {

      information() << "Failed to rename \"downloading\" file from " << pathDownloading << " to " << pathOut;

      erase(pathDownloading);

      throw ::exception(error_io);

   }

}


file_pointer file_context::file_get_file(::file::path path, ::file::e_open eopen)
{

   file_pointer pfile;

   __construct(pfile);

   pfile->open(path, eopen);

   return pfile;

   //try
   //{

      //auto resultstatus = pfile->open(path, eopen);

      //if (resultstatus)
      //{

      //   return pfile;

      //}
      //else
      //{

      //   return resultstatus;

      //}

   //}
   //catch (const ::exception & e)
   //{

   //   return e.m_estatus;

   //}
   //catch (...)
   //{

   //}

   //return ::error_failed;

}


file_pointer file_context::data_get_file(string strData, ::file::e_open eopen)
{

   ASSERT(strData.case_insensitive_begins("data:"));

   string strSample = strData.left(4096);

   auto iFind = strSample.find_index(";", 5);

   if (iFind > 5)
   {

      strsize iEncoding1 = strSample.find_index(",", iFind + 1);

      strsize iEncoding2 = strSample.find_index(";", iFind + 1);

      strsize iEncoding = minimum_non_negative(iEncoding1, iEncoding2);

      if (iFind > 5 && iEncoding > iFind)
      {

         string strMimeType = strData.substr(5, iFind - 5);

         string strEncoding = strData.substr(iFind + 1, iEncoding - iFind - 1);

         if (strEncoding.case_insensitive_order("base64") == 0)
         {

            ::pointer<memory_file>pmemoryfile = __new(memory_file());

            auto psystem = acmesystem();

            auto pbase64 = psystem->base64();

            if (pbase64->decode(*pmemoryfile->get_primitive_memory(), strData.substr(iEncoding + 1)))
            {

               information() << "::file::file_context::data_get_file Succeeded";

               return pmemoryfile;

            }

         }

      }

   }

   information() << "::file::file_context::data_get_file Failed";

   //throw ::exception(error_failed);
   //return ::error_failed;

   return nullptr;

}


folder_pointer file_context::get_folder(::file::file *pfile, const ::scoped_string & scopedstrImplementation, ::file::e_open eopen)
{

   auto & pfactory = acmesystem()->folder_factory();

   if (!pfactory)
   {

     throw ::exception(::error_failed);

   }

   auto pfolder = pfactory->create < ::folder >();

   if (!pfolder)
   {

      throw ::exception(::error_failed);

   }

   if(eopen & ::file::e_open_read)
   {

      pfolder->open_for_reading(pfile);
      //{

         //information() << "::file::file_context::zip_get_file Succeeded";

         return pfolder;

      //}

   }
   else if (eopen & ::file::e_open_write)
   {

      //if (pfolder->open_for_writing(pfile))
      pfolder->open_for_writing(pfile);
      //{

        // information() << "::file::file_context::zip_get_file Succeeded";

         return pfolder;

      //}

   }

   //information() << "::file::file_context::zip_get_file Failed";

   return nullptr;

}


file_pointer file_context::http_get_file(const ::payload &payloadFile, ::file::e_open eopen)
{

   if (eopen & (::file::e_open_write | ::file::e_open_truncate | ::file::e_open_create))
   {

      return nullptr;

   }

   ::file::path path = payloadFile.as_file_path();

   ::url_domain domain;

   auto psystem = acmesystem();

   auto purl = psystem->url();

   domain.create(purl->get_server(path));

   //bool bSaveCache = domain.m_strRadix != "ca2" || !string_begins(purl->get_object(path), "/matter/");

   bool bSaveCache = !::file::get_no_cache(payloadFile);

   ::file::path pathCache;

   if (bSaveCache)
   {

      pathCache = path;

      if (string_ends(pathCache, "en_us_international.xml"))
      {

         information() << "Debug Here";

      }

      if (string_ends(pathCache, "text_select.xml"))
      {

         information() << "Debug Here";

      }

      if (string_ends(pathCache, "arialuni.ttf"))
      {

         information() << "Debug Here : arialuni.ttf";

      }

#ifdef WINDOWS
      pathCache.replace_with("_\\", "://");
      pathCache.replace_with("_", "?");
      pathCache.replace_with("_", ":");
#else
      pathCache.replace_with("_/", "://");
#endif
      pathCache = dir()->cache() / (pathCache + ".cache");

      if (exists(pathCache))
      {

         auto pfile = get_reader(pathCache);

         if (pfile.ok())
         {

            return pfile;

         }

      }

   }

   while_predicateicate_Sleep(60 * 1000, [&]()
   {

      synchronous_lock synchronouslock(m_pcontext->m_papexcontext->http().m_pmutexDownload);

      return m_pcontext->m_papexcontext->http().m_straDownloading.contains(path) || m_pcontext->m_papexcontext->http().m_straExists.contains(path);

      });/* .failed())
   {

      bSaveCache = false;

   }*/


   {

      synchronous_lock synchronouslock(m_pcontext->m_papexcontext->http().m_pmutexDownload);

      if (path.flags().is_clear(::file::e_flag_bypass_cache) && acmefile()->exists(pathCache))
      {

         synchronouslock.unlock();

         auto pfile = file_get_file(pathCache, eopen);

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

   //if (!m_pcontext->m_papexcontext->http().get(pmemoryfile->get_primitive_memory(), path, set))
   m_pcontext->m_papexcontext->http().get(pmemoryfile->get_primitive_memory(), path, set);
   //{

   //   return ::error_failed;

   //}

   if (bSaveCache)
   {

      synchronous_lock synchronouslock(m_pcontext->m_papexcontext->http().m_pmutexDownload);

      try
      {

         pmemoryfile->seek_to_begin();

         auto pfileOut = file()->get_writer(pathCache);

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

::file_pointer file_context::shared_reader(const ::payload &payloadFile, ::file::e_open eopen)
{

   return get_reader(payloadFile, eopen | ::file::e_open_share_deny_none);

}


::file_pointer file_context::get_reader(const ::payload &payloadFile, ::file::e_open eopen)
{

   ::file_pointer preader;

   if (payloadFile.m_etype == ::e_type_element)
   {

      preader = payloadFile.cast<::file::file>();

   }

   if (!preader)
   {

      preader = get_file(payloadFile, eopen | ::file::e_open_read | ::file::e_open_no_exception_on_open);

   }

   return preader;

}


::file_pointer file_context::get_writer(const ::payload &payloadFile, ::file::e_open eopen)
{

   ::file_pointer pwriter;

   if (payloadFile.m_etype == ::e_type_element)
   {

      pwriter = payloadFile.cast<::file::file>();

   }

   if (!pwriter)
   {

      pwriter = get_file(payloadFile, eopen | ::file::e_open_write | ::file::e_open_create | ::file::e_open_defer_create_directory | ::file::e_open_binary);

   }

   return pwriter;

}


file_pointer file_context::get_file(const ::payload &payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception)
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

   ::file::path path = payloadFile.as_file_path();

   if(path.is_empty())
   {

      if(eopen & ::file::e_open_file)
      {

         if(eopen & ::file::e_open_no_exception_on_open)
         {

            pfile = __new(::file::file);

            pfile->m_estatus = error_not_a_file;

            pfile->set_nok();

            return pfile;

         }
         else
         {

            throw ::exception(error_not_a_file);

         }

      }

   }

   if (path.case_insensitive_begins("data:"))
   {

      return data_get_file(path);

   }

   if (path.contains("yesno.xhtml"))
   {

      information("file_context::get_file yesno.xhtml");

   }

   if (path.flags().is_clear(::file::e_flag_required) &&
         payloadFile.is_property_true("required"))
   {

      path.flags().set(::file::e_flag_required);

   }

   if (path.flags().is_clear(::file::e_flag_bypass_cache)
         && ((eopen & ::file::e_open_no_cache) || payloadFile.is_property_true("nocache")))
   {

      path.flags().set(::file::e_flag_bypass_cache);

   }

   auto pathProcessed = m_pcontext->m_papexcontext->defer_process_path(path);

   if (pathProcessed.is_empty())
   {

      //information() << "::file::file_context::get_file file with empty name!!";

      if(eopen & ::file::e_open_no_exception_on_open)
      {

         __construct_new(pfile);

         pfile->m_estatus = error_file_not_found;

         pfile->set_nok();

         return pfile;

      }
      else
      {

         throw file::exception(::error_file_not_found, errno_error_code(ENOENT), path, ::file::e_open_none, "defer_process_path returns empty path");

      }

      return nullptr;

   }

   path = pathProcessed;

   if (::task_flag().is_set(e_task_flag_compress_is_dir) && (::str::find_file_extension("zip:", path) >= 0))
   {

      //auto pfile = get_reader(path);

      //return zip_get_file(pfile.m_p, eopen);

      throw todo;

      return nullptr;

   }
   else if (path.begins_eat("file:///") || path.begins_eat("file:\\\\\\"))
   {

      return get_file(path, eopen);

   }
   else if (path.begins_eat("resource://") || path.begins_eat("resource:\\\\"))
   {

      return resource_get_file(path);

   }
   else if (string_begins(path, "http://") || string_begins(path, "https://"))
   {

      return http_get_file(payloadFile, eopen);

   }
   else if (path.begins_eat("zipresource://"))
   {

      return create_resource_file(path);

   }
   else if(path.case_insensitive_begins_eat("file://"))
   {

      return create_native_file(path, eopen);

   }
   else
   {

      return create_native_file(path, eopen);

   }

   return pfile;

}


::file_pointer file_context::create_native_file(const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception)
{

   ::file_pointer pfile;

   __construct(pfile);

   pfile->open(path, eopen, pfileexception);

   return pfile;

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
//   while ((uRead = istream.read(memory, memory.size())) > 0)
//   {
//      ostream.write(memory, uRead);
//   }
//   return true;
//}


bool file_context::is_link(const ::file::path & path)
{

   return false;

}


::file::path file_context::dropbox_info_network_payload()
{

   ::file::path pathNetworkPayload;

   pathNetworkPayload = acmedirectory()->home() / ".dropbox/info" NETWORK_PAYLOAD_DEFAULT_EXTENSION;

   return pathNetworkPayload;

}


::file::path file_context::onedrive_global_ini()
{

   ::file::path pathGlobalIni;

   pathGlobalIni = acmedirectory()->ca2roaming() / "OneDrive/settings/Personal/global.ini";

   return pathGlobalIni;

}


::file::path file_context::onedrive_cid_ini()
{

   ::file::path pathGlobalIni = onedrive_global_ini();

   string strIni = acmefile()->as_string(pathGlobalIni);

   if (strIni.is_empty())
   {

      return "";

   }

   ::property_set set;

   set.parse_ini(strIni);

   string strCid;

   strCid = set["cid"];

   ::file::path pathIni = acmedirectory()->ca2roaming() / "OneDrive/Settings/Personal/" + strCid + ".ini";

   return pathIni;

}
//
//::extended::status file_context::copy(::payload varTarget, ::payload varSource, bool bFailIfExists, enum_extract eextract)
//{
//
//   return psystem->m_spfile->copy(varTarget, varSource, bFailIfExists, eextract, get_app());
//
//}

//
//::extended::status file_context::transfer(const ::file::path & pszNew, const ::file::path & pszOld)
//{
//
//   return psystem->m_spfile->transfer(pszNew, pszOld, get_app());
//
//}

//
//::extended::status file_context::del(const ::file::path & psz)
//{
//   return psystem->m_spfile->del(psz, get_app());
//}

//::extended::status file_context::rename(const ::file::path & pszNew, const ::file::path & pszOld)
//{
//   return psystem->m_spfile->rename(pszNew, pszOld, get_app());
//}

//void file_context::trash_that_is_not_trash(const ::file::path & psz)
//{
//   return psystem->m_spfile->trash_that_is_not_trash(psz, get_app());
//}
//
//void file_context::trash_that_is_not_trash(::file::path_array & stra)
//{
//   return psystem->m_spfile->trash_that_is_not_trash(stra, get_app());
//}

//::extended::status file_context::replace(const ::file::path & pszContext, const string & pszFind, const string & pszReplace)
//{
//   return psystem->m_spfile->replace(pszContext, pszFind, pszReplace, get_app());
//}


//bool file_context::exists(const ::file::path & pszPath)
//{
//
//   return psystem->m_spfile->exists(pszPath, get_app());
//
//}


::file::enum_type file_context::get_type(const ::file::path &path)
{

   auto etype = get_type(path, nullptr);

   if(etype != ::file::e_type_unknown)
   {

      return etype;

   }

   return acmepath()->get_type(path);

}


::file::enum_type file_context::safe_get_type(const ::file::path& path)
{

   auto etype = safe_get_type(path, nullptr);

   if (etype != ::file::e_type_unknown)
   {

      return etype;

   }

   return acmepath()->safe_get_type(path);

}


/*  bool file_context::exists(const ::string & strPath)
   {

      return psystem->m_spfile->exists(strPath, get_app());

   }

   bool file_context::exists(const ::payload & payload)
   {

      const ::string & strPath = payload.get_string();


      return psystem->m_spfile->exists(strPath, get_app());

   }*/


//::payload file_context::length(const ::file::path & pszPath)
//{
//
//   return psystem->m_spfile->length(pszPath, get_app());
//
//}


//::payload file_context::length(const ::string & strPath)
//{


//   return psystem->m_spfile->length(strPath, get_app());

//}


//::payload file_context::length(const ::payload & payload)
//{

//   return psystem->m_spfile->length(payload.get_string(), get_app());

//}

//
//::file::path file_context::time(const ::file::path & pszBasePath, i32 iDepth, const string & pszPrefix, const string & pszSuffix)
//{
//
//   return psystem->m_spfile->time(get_app(), pszBasePath, iDepth, pszPrefix, pszSuffix);
//
//}


//::file::path file_context::time_square(const string & pszPrefix, const string & pszSuffix)
//{
//
//   return psystem->m_spfile->time_square(get_app(), pszPrefix, pszSuffix);
//
//}

//::file::path file_context::time_log(const string & pszId)
//{
//   return psystem->m_spfile->time_log(get_app(), pszId);
//}
//
//file_pointer file_context::time_square_file(const ::scoped_string & scopedstrPrefix, const ::scoped_string & scopedstrSuffix)
//{
//   return psystem->m_spfile->time_square_file(get_app(), pszPrefix, pszSuffix);
//}


//file_pointer file_context::get(const ::file::path & name)
//{
//
//   return psystem->m_spfile->get(name, get_app());
//
//}


//::payload file_context::as_network_payload(const ::payload & payloadFile)
//{
//
//   return psystem->m_spfile->as_network_payload(get_app(), payloadFile);
//
//}


//string file_context::as_string(const ::payload & payloadFile)
//{
//
//   return psystem->m_spfile->as_string(get_app(), payloadFile);
//
//}
//
//
//bool file_context::as_memory(const ::payload & payloadFile, memory_base & mem)
//{
//
//   return psystem->m_spfile->as_memory(get_app(), payloadFile, mem);
//
//}

//
//void file_context::lines(string_array & stra, const ::payload & payloadFile)
//{
//
//   return psystem->m_spfile->lines(stra, payloadFile, get_app());
//
//}
//
//
//void file_context::put_lines(const ::payload & payloadFile, const string_array & stra)
//{
//   return psystem->m_spfile->put_lines(payloadFile, stra, get_app());
//}
//
//bool file_context::put_contents(const ::payload & payloadFile, const void * pvoidContents, ::count count)
//{
//   return psystem->m_spfile->put_contents(payloadFile, pvoidContents, count, get_app());
//}
//
//bool file_context::put_contents(const ::payload & payloadFile, const ::scoped_string & scopedstrContents)
//
//{
//   return psystem->m_spfile->put_contents(payloadFile, pcszContents, get_app());
//
//}
//
//
//bool file_context::add_contents(const ::payload & payloadFile, const ::scoped_string & scopedstrContents)
//{
//
//   return psystem->m_spfile->add_contents(payloadFile, pcszContents, get_app());
//
//}


//bool file_context::put_contents(const ::payload & payloadFile, const ::stream & stream)
//{

//   return psystem->m_spfile->put_contents(payloadFile, stream, get_app());

//}


//bool file_context::put_contents(const ::payload & payloadFile, memory & mem)
//{
//
//   return psystem->m_spfile->put_contents(payloadFile, mem, get_app());
//
//}
//
//
//bool file_context::put_text_utf8(const ::payload & payloadFile, const ::scoped_string & scopedstrContents)
//{
//
//   return psystem->m_spfile->put_text_utf8(payloadFile, pcszContents, get_app());
//
//}

//
//string file_context::sys_temp(const char * lpszName, const ::scoped_string & scopedstrExtension)
//{
//   return psystem->m_spfile->sys_temp(lpszName, pszExtension, get_app());
//}


::file_pointer file_context::friendly_get_file(const ::payload &payloadFile, ::file::e_open eopen)
{

   //try
   //{

      return get_file(payloadFile, eopen);

   //}
   //catch (const ::exception & e)
   //{

   //   return e;

   //}
   //catch (...)
   //{

   //   return ::error_failed;

   //}

}


//
//
//::file_pointer file_context::get_file(const ::payload & payloadFile, ::u32 nOpenFlags)
//{
//
//   return file()->get_file(get_app(), payloadFile, nOpenFlags);
//
//}


//
//void file_context::dtf(const ::file::path & pszFile, const ::file::path & pszDir)
//{
//
//   return psystem->m_spfile->dtf(pszFile, pszDir, get_app());
//
//}

//bool file_context::is_read_only(const path & psz)
//{
//
//   return psystem->m_spfile->is_read_only(psz, get_app());
//}


//void file_context::dtf(const ::file::path & pszFile, ::file::path_array & stra, ::file::path_array & straRelative)
//{
//
//   return psystem->m_spfile->dtf(pszFile, stra, get_app());
//
//}
//
//
//void file_context::ftd(const ::file::path & pszDir, const ::file::path & pszFile)
//{
//
//   return psystem->m_spfile->ftd(pszDir, pszFile, get_app());
//
//}


void file_context::crypto_set(const ::payload &payloadFile, const ::scoped_string & scopedstrData, const ::scoped_string & scopedstrSalt)
{

   throw ::interface_only();

   ///return false;

}


void file_context::crypto_get(const ::payload &payloadFile, string &str, const ::scoped_string & scopedstrSalt)
{

   throw ::interface_only();

   ///return false;

}


void file_context::save_lines(const ::payload &payloadFile, string_array &stra)
{

   string str = stra.implode("\n");

   put_text_utf8(payloadFile, str);

   //return true;

}


void file_context::load_lines(string_array &stra, const ::payload &payloadFile)
{

   string str = as_string(payloadFile);

   stra.add_lines(str);

   //return true;

}


//bool file_context::transfer(const path & pathOut, const path & pszSource)

//{

//   return file()->transfer(get_app(), pathOut, pszSource);


//}


//bool file_context::transfer(const path & pathOut, ::file::file * pfileIn)
//{

//   return file()->transfer(get_app(), pathOut, pfileIn);

//}


//bool file_context::transfer(const path & pathOut, ::file::file & reader)
//{

//   return file()->transfer(get_app(), pathOut, reader);

//}


//bool file_context::transfer(::file::file * pfileOut, ::file::file * pfileIn)
//{
//
//   return file()->transfer(get_app(), pfileOut, pfileIn);
//
//}


//bool file_context::transfer(file * pfileOut, ::file::file * pfileIn)
//{

//   return file()->transfer(get_app(), pfileOut, pfileIn);

//}


//bool file_context::transfer(file * pfileOut, ::file::file & is)
//{

//   return file()->transfer(get_app(), *pfileOut, is);

//}


//bool file_context::transfer(::file::file & os, const path & pszSource)
//{

//   return file()->transfer(get_app(), os, pszSource);

//}


//bool file_context::transfer(::file::file & os, ::file::file * pfileIn)
//{

//   return file()->transfer(get_app(), os, pfileIn);

//}


//bool file_context::transfer(::file::file & os, ::file::file & is)
//{

//   return file()->transfer(get_app(), os, is);

//}


void file_context::touch(const ::file::path &path)
{

   if (!exists(path))
   {

      put_memory(path, nullptr);

   }

}


//void file_context::update_module_path()
//{
//
//   auto psystem = acmesystem()->m_papexsystem;
//
//   auto estatus = psystem->m_pfilesystem->update_module_path();
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return estatus;
//
//
//}




void set_bypass_cache_if_empty(::payload & payloadFile)
{

   auto etype = payloadFile.m_etype;

   if(etype != e_type_element)
   {

      if(etype != e_type_property_set)
      {

         auto path = payloadFile.as_file_path();

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


void file_context::set(const ::payload & payloadFile, const ::memory_base & memory)
{

   auto writer = get_writer(payloadFile);

   writer->write(memory);

   //return writer.m_estatus;

}


void file_context::unzip_to_folder(const ::file::path & pathFolder, const ::file::path & pathZip)
{

   auto pfileZip = get_reader(pathZip);

   auto pfolder = acmesystem()->create < ::folder >("folder", "zip");

   pfolder->initialize(m_pcontext);

   pfolder->open_for_reading(pfileZip);

   pfolder->e_extract_all(pathFolder);

}



