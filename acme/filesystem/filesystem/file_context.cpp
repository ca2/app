#include "framework.h"
#include "file_context.h"
#include "file_system.h"
#include "directory_context.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/io.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/folder.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/file/status.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/nano/http/get.h"
#include "acme/platform/http.h"
#include "acme/prototype/prototype/url.h"
#include "acme/prototype/prototype/url_domain.h"
#include "acme/parallelization/happening.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task_flag.h"
//#include "acme/platform/ini.h"
//#include "acme/platform/sequence.h"
#include "acme/platform/system.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/prototype/read_only_memory.h"
#include "acme/prototype/string/base64.h"
//#include "acme/prototype/string/hex.h"
#include "acme/prototype/string/str.h"
//#include "acme/user/user/conversation.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "acme/crypto/crypto.h"
#include "acme/crypto/hasher.h"
#include "acme/filesystem/filesystem/directory_system.h"
//#include "apex/networking/http/context.h"
#include "acme/platform/application.h"
#include "acme/platform/application.h"
//#include "acme/platform/machine_event.h"
//#include "acme/platform/machine_event_central.h"
//#include "acme/platform/os_context.h"
#include "acme/platform/session.h"
#include "acme/platform/system.h"

#include <string.h>
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

   __refdbg_add_referer

      defer_create_synchronization();

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


bool file_context::exists(const ::file::path & pathParam)
{

   if (::is_null(m_papplication))
   {

      throw ::exception(error_null_pointer);

   }

   ::file::path path = m_papplication->defer_process_path(pathParam);

   if (path.flags().is_clear(::file::e_flag_required) && path.is_empty())
   {

      return false;

   }

   auto etype = safe_get_type(path);

   if (!(etype & ::file::e_type_exists))
   {

      return false;

   }

   return etype & ::file::e_type_file2 || etype & ::file::e_type_element2;

}


//bool file_context::is_file_or_dir(const ::file::path & path, ::file::enum_type * petype)
//{
//
//   path = m_papplication->defer_process_matter_path(path, papp, bOptional, bNoCache);
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


::file::enum_type file_context::get_type(const ::file::path & path, ::payload * pvarQuery)
{

   if (path.begins("http://") || path.begins("https://"))
   {

      ::property_set set;

      if (path.flags() & ::file::e_flag_required)
      {

         set["required"] = true;

      }

      if (path.flags() & ::file::e_flag_bypass_cache)
      {

         set["nocache"] = true;

      }

      return http()->get_type(path, pvarQuery, set);

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


::file::enum_type file_context::safe_get_type(const ::file::path & path, ::payload * pvarQuery)
{

   if (path.begins("http://") || path.begins("https://"))
   {

      ::property_set set;

      if (path.flags() & ::file::e_flag_required)
      {

         set["required"] = true;

      }

      if (path.flags() & ::file::e_flag_bypass_cache)
      {

         set["nocache"] = true;

      }

      return http()->get_type(path, pvarQuery, set);

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


::payload file_context::length(const ::file::path & path)
{

   return length(path, nullptr);

}


::payload file_context::length(const ::file::path & path, ::payload * pvarQuery)
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
//      varRet = (((unsigned long long) data.nFileSizeHigh) << 32) | (unsigned long long) data.nFileSizeLow;
//
//      ((::file::path &) path).m_iSize = varRet.m_hi;
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
//      ((::file::path &)path).m_iSize = varRet.m_hi;
//
//   }
//
//#endif

//   return varRet;

}


::file::path file_context::module()
{

   auto psystem = system();

   auto pfilesystem = psystem->file_system();

   return pfilesystem->m_pathModule;

}


//::file::path file_context::ca2module()
//{
//
//   auto psystem = system();
//
//   return psystem->m_pfilesystem->m_pathCa2Module;
//
//}


::file::path file_context::time_square(const ::scoped_string & scopedstrPrefix, const ::scoped_string & scopedstrSuffix)
{

   return time(directory()->time_square(), 25, scopedstrPrefix, scopedstrSuffix);

}


::file::path file_context::time_log(const ::scoped_string & scopedstrId)
{
   return time(directory()->time_log(scopedstrId), 9);
}


::file::path
file_context::time(const ::file::path & pathBase, int iMaxLevel, const ::scoped_string & scopedstrPrefix, const ::scoped_string & scopedstrSuffix,
                   bool bTryDelete)
{

   auto psystem = system();

   _synchronous_lock lockMachineEvent(psystem->synchronization());

   ::file::path str;

   ::file::path path;

   string strPrefix(scopedstrPrefix);

   string strSuffix(scopedstrSuffix);

   int iIncLevel = 0;

restart:

   str.empty();

   str = pathBase;

   directory()->create(str);

   ::file::listing listing;

   string strFormat;

   for (int i = 1; i <= iMaxLevel;)
   {

      directory()->create(str);

      if (!directory()->is(str))
      {

         throw ::exception(error_path_not_found, "time square dir does not exist");

      }

      listing.set_listing(str);

      directory()->enumerate(listing);

      if (i < iMaxLevel)
      {

         int iMax = filterex_time_square("", listing);

         if (iMax == -1)
         {

            str /= "00";

            directory()->create(str);

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

            strFormat.formatf("%02d", iMax);

            str /= strFormat;

            if (i == iIncLevel)
            {

               directory()->create(str);

            }

         }

         i++;

      }
      else // if i == iMaxLevel
      {

         listing.set_listing(str);

         directory()->enumerate(listing);

         int iMax = bTryDelete ? 0 : filterex_time_square(scopedstrPrefix, listing);

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

                  strFormat.formatf("%d", iMax);

               }
               else
               {

                  strFormat.formatf("%02d", iMax);

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


int file_context::filterex_time_square(const ::scoped_string & scopedstrPrefix, ::file::path_array & stra)
{

   int iMax = -1;

   int iIndex;

   for (int i = 0; i < stra.size(); i++)
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

         if (!character_isdigit(str[0]) || !character_isdigit(str[1]))
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
bool file_context::try_create_file(const ::file::path & path, bool bTryDelete)
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

   __øconstruct(pfile);

   if (!m_estatus)
   {

      return false;

   }

   pfile->open(path, ::file::e_open_create | ::file::e_open_binary | ::file::e_open_no_exception_on_open);

   if (pfile->m_estatus.failed())
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

   const_char_pointer pszJson = str;

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

   const_char_pointer pszJson = str;

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


::memory file_context::_005Signature(const ::payload & payloadFile)
{

   auto path = payloadFile.as_file_path();

   ::string all_extensions = path.all_extensions();

   if (all_extensions.is_empty())
   {

      ::string strMessage;

      strMessage = "file_context::_005SignedMemory Cannot open file as _005SignedMemory. It doesn't have file extension.";

      warning() << strMessage;

      throw ::exception(error_failed, strMessage);

   }

   all_extensions.make_lower();

   ::memory signature;

   signature.append("\0\0\0\0\0", 5);
   signature.append("\1\1\1\1\1", 5);

   signature.append(all_extensions);

   signature.append("\1\1\1\1\1", 5);
   signature.append("\0\0\0\0\0", 5);

   return ::transfer(signature);

}


::memory file_context::_005SignedMemory(const ::payload & payloadFile)
{

   auto memory = as_memory(payloadFile);

   auto signature = _005Signature(payloadFile);

   if (!memory.begins_eat(signature))
   {

      ::string strMessage;

      strMessage.formatf("file_context::_005SignedMemory Cannot open file as _005SignedMemory. Start of file doesn't match the _005Signature for all_extensions : %s", ::string(payloadFile.as_file_path().all_extensions()).c_str());

      throw ::exception(error_failed, strMessage);

   }

   return memory;

}


string file_context::_005SignedString(const ::payload & payloadFile)
{

   auto memory = _005SignedMemory(payloadFile);

   return memory.as_utf8();

}


string file_context::as_string(const ::payload & payloadFile)
{

   memory memory;

   as_memory(payloadFile, memory);

   return memory.as_utf8();

}


::string file_context::get_configuration_text(const ::scoped_string & scopedConfigurationFile)
{

   ::string str;

   try
   {

      str = as_string(directory_system()->config() / scopedConfigurationFile);

   }
   catch (...)
   {

      information() << "get_configuration_text failed!! : \"" << scopedConfigurationFile << "\"";

   }

   return str;

}




void file_context::as_memory(const ::payload & payloadFile, memory_base & mem)
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




::memory file_context::as_memory(const ::payload & payloadFile)
{

   ::memory memory;

   as_memory(payloadFile, memory);

   return ::transfer(memory);

}




memsize file_context::read(const ::payload & payloadFile, void * p, filesize position, memsize size, bool bNoExceptionOnFail)
{

   file_pointer pfile;

   try
   {

      pfile = get_file(payloadFile, ::file::e_open_share_deny_none | ::file::e_open_read | ::file::e_open_binary | (bNoExceptionOnFail ? ::file::e_open_no_exception_on_open : 0));

      if (!pfile)
      {

         return -1;

      }
      else if (pfile->m_estatus.failed())
      {

         return -1;

      }

   }
   catch (const ::exception & exception)
   {

      if (bNoExceptionOnFail)
      {

         return -1;

      }

      throw exception;

   }

   memsize sizeToRead = (memsize)minimum(size, pfile->size() - position);

   if (position > 0)
   {

      pfile->set_position(position);

   }

   auto sizeRead = pfile->read({ p, sizeToRead });

   return sizeRead;

}


memsize file_context::read_beginning(const ::payload & payloadFile, void * p, memsize size, bool bNoExceptionOnFail)
{

   return read(payloadFile, p, 0, size, bNoExceptionOnFail);

}


memory file_context::beginning(const ::payload & payloadFile, memsize size, bool bNoExceptionOnFail)
{

   memory mem;

   mem.set_size(size);

   auto sizeRead = read(payloadFile, mem.data(), mem.size(), bNoExceptionOnFail);

   mem.set_size(sizeRead);

   return ::transfer(mem);

}


void file_context::put_lines(const ::payload & payloadFile, const string_array & stra, const plain_text_file_options & options)
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


void file_context::get_lines(string_array & stra, const ::payload & payloadFile, bool bAddEmpty, bool bNoExceptionIfFailToOpen)
{

   file_pointer pfile;

   try
   {

      pfile = get_file(payloadFile, ::file::e_open_file |
      ::file::e_open_share_deny_none | ::file::e_open_read | ::file::e_open_binary
      | (bNoExceptionIfFailToOpen ? ::file::e_open_no_exception_on_open : 0));

      if (bNoExceptionIfFailToOpen)
      {

         if (pfile.nok())
         {

            return;

         }

      }

   }
   catch (const ::exception & exception)
   {

      if (bNoExceptionIfFailToOpen)
      {

         return;

      }

      throw exception;

   }

   auto pmemoryfile = create_memory_file_by_reading(pfile);

   string strLine;

   while (pmemoryfile->::file::file::read_string(strLine))
   {

      if (bAddEmpty || !strLine.is_empty())
      {

         stra.add(strLine);

      }

   }

}


void file_context::put_memory(const ::payload & payloadFile, const block & block)
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

   if (block.size() > 0)
   {

      pfile->write(block);

   }

   //return true;

}



void file_context::_005PutSignedMemory(const ::payload & payloadFile, const block & block)
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

   auto signature = _005Signature(payloadFile);

   pfile->write(signature);

   if (block.size() > 0)
   {

      pfile->write(block);

   }

}



void file_context::add_contents(const ::payload & payloadFile, const ::scoped_string & scopedstr)
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


void file_context::put_text(const ::payload & payloadFile, const ::scoped_string & scopedstr)
{

   if (scopedstr.data() == nullptr || scopedstr.is_empty())
   {

      return put_memory(payloadFile, nullptr);

   }

   string strContents(scopedstr);

   ::str::fix_eol(strContents);

   return put_memory(payloadFile, strContents);

}


void file_context::_005PutSignedText(const ::payload & payloadFile, const ::scoped_string & scopedstr)
{

   return _005PutSignedMemory(payloadFile, scopedstr);

}

//void file_context::add_contents(const ::payload &payloadFile, const ::scoped_string & scopestrContents)
//{
//
//   return add_contents(payloadFile, scopestrContents.begin(), scopestrContents.size());
//
//}


void file_context::put_memory(const ::payload & payloadFile, ::file::file * pfileSrc)
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

      mem.set_size(minimum((memsize)remainingByteCount, (memsize)8_MiB));

      memsize uRead;

      while ((uRead = pfileSrc->read(mem)) > 0)
      {

         pfile->write(mem.data(), uRead);

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


void file_context::put_text_utf8(const ::payload & payloadFile, const ::scoped_string & scopedstr)
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

   if (::system()->m_blockMatter.is_set())
   {

      return ::system()->m_blockMatter;

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


::folder * file_context::resource_folder()
{

   try
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto pfactory = system()->folder_factory();

      if (m_bFolderResourceCalculated)
      {

         if (!m_pfolderResource)
         {

            informationf("m_pfolderResource is null? Why?");

         }

         return m_pfolderResource;

      }

      m_bFolderResourceCalculated = true;

      auto block = get_main_resource_block();

      if (!block)
      {

         return nullptr;

      }

      auto pmemory = __allocate read_only_memory(block);

      auto pfile = __allocate::memory_file(pmemory);

      system()->folder_factory()->__øconstruct(m_papplication, m_pfolderResource);

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

      _synchronous_lock synchronouslock(this->synchronization());

      pfolder = resource_folder();

      if (::is_null(pfolder))
      {

         return nullptr;

      }

   }

   _synchronous_lock synchronouslock(pfolder->synchronization());

   string strPath(path);

   strPath.replace_with("/", "\\");

   debugf("file_context::create_resource_file : %s", strPath.c_str());

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

   if (strPath.contains("256"))
   {

      informationf("contains 256");

      //fflush(stdout);

      if (pfileOutput.nok())
      {

         informationf("output file nok");

         //fflush(stdout);

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

   ::folder * pfolder = nullptr;

   {

      _synchronous_lock synchronouslock(this->synchronization());

      pfolder = resource_folder();

      if (::is_null(pfolder))
      {

         return ::file::e_type_doesnt_exist;

      }

   }

   _synchronous_lock synchronouslock(pfolder->synchronization());

   string strPath(path);

   strPath.replace_with("/", "\\");

   strPath.trim_right("\\/");

   if (pfolder->locate_file(strPath))
   {

      return ::file::e_type_existent_file;

   }

   if (pfolder->locate_folder(strPath))
   {

      return ::file::e_type_existent_folder;

   }

   return ::file::e_type_doesnt_exist;

}


void file_context::copy(::payload varTarget, ::payload varSource, bool bFailIfExists, enum_extract eextract)
{

   auto pdir = directory();

   auto bSourceIsDir = pdir->is(varSource);

   if (bSourceIsDir &&
       (eextract == e_extract_first || eextract == e_extract_all || !(case_insensitive_string_ends(varSource.as_file_path(), ".zip"))))
   {

      ::file::listing listing;

      listing.set_listing(varSource, e_depth_recursively);

      directory()->enumerate(listing);

      ::file::path strDst;
      ::file::path strSrc;
      ::file::path strDirSrc(varSource.as_file_path());
      ::file::path strDirDst(varTarget.as_file_path());

      if (::task_flag().is_set(e_task_flag_compress_is_dir) && (string_ends(strDirSrc, ".zip")))
      {

         strDirSrc += ":";

      }

      for (int i = 0; i < listing.size(); i++)
      {

         strSrc = listing[i];

         strDst = strSrc;

         strDst.case_insensitive_begins_eat(strDirSrc);

         strDst = strDirDst / strDst;

         if (directory()->is(strSrc))
         {

            if ((eextract == e_extract_first || eextract == e_extract_none) &&
                (case_insensitive_string_ends(varSource.as_file_path(), ".zip")))
            {
            }
            else
            {
               directory()->create(strDst);
            }
         }
         else
         {
            if (!directory()->is(strDst.folder()))
            {
               directory()->create(strDst.folder());
            }
            copy(strDst, strSrc, bFailIfExists, eextract == e_extract_all ? e_extract_all : e_extract_none);

         }
      }
      return;
   }

   auto preader = varSource.cast < ::file::file >();

   bool bSourceEmpty = varSource.as_file_path().is_empty();

   if (bSourceEmpty && ::is_nok(preader))
   {

      throw ::exception(error_bad_argument);

   }

   auto pwriter = varTarget.cast < ::file::file >();

   bool bTargetEmpty = varTarget.as_file_path().is_empty();

   if (bTargetEmpty && ::is_nok(pwriter))
   {

      throw ::exception(error_bad_argument);

   }

   if (::is_nok(pwriter))
   {

      if (!directory()->is(varTarget.as_file_path().folder()))
      {

         directory()->create(varTarget.as_file_path().folder());

      }

   }

   auto psystem = system();

   auto pfilesystem = psystem->file_system();

   ::file::path pathTarget;

   if (::is_nok(pwriter))
   {

      pathTarget = application()->defer_process_path(varTarget.as_file_path());

   }

   ::file::path pathSource;

   if (::is_nok(preader))
   {

      pathSource = application()->defer_process_path(varSource.as_file_path());

      if (exists(pathSource))
      {

         pfilesystem->copy(pathTarget, pathSource, !bFailIfExists);

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

   if (::is_nok(pwriter) && directory()->is(varTarget) && (varSource.as_file_path().name().has_character() && ::is_nok(preader)))
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

      information() << "preader : " << (iptr)preader.m_p;

      if (::is_nok(preader))
      {

         preader = get_reader(varSource,
                              ::file::e_open_read | ::file::e_open_binary | ::file::e_open_share_deny_none);

         if (::is_nok(preader))
         {

            string strError;

            strError.formatf("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open input file",
                            varSource.as_file_path().c_str(), varNew.as_file_path().c_str(), bFailIfExists);

            error() << strError;

            throw ::exception(::error_io, strError);

         }

      }

      if (::is_nok(pwriter))
      {

         pwriter = get_file(varNew,
                            ::file::e_open_write | ::file::e_open_binary | ::file::e_open_create |
                            ::file::e_open_defer_create_directory |
                            ::file::e_open_share_deny_write);

         if (::is_nok(pwriter))
         {

            string strError;

            strError.formatf("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open output file",
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

            pwriter->set_modification_time(st.m_timeModification);

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
         strError.formatf(
            "During copy, failed to close both input file \"%s\" and output file \"%s\" bFailIfExists=%d",
            varSource.as_file_path().c_str(), varTarget.as_file_path().c_str(), bFailIfExists);
         throw ::exception(::error_io, strError);
      }
      else
      {
         string strError;
         strError.formatf("During copy, failed to close input file \"%s\" bFailIfExists=%d",
                         varSource.as_file_path().c_str(), bFailIfExists);
         throw ::exception(::error_io, strError);
      }
   }
   else if (bOutputFail)
   {
      string strError;
      strError.formatf("During copy, failed to close output file \"%s\" bFailIfExists=%d",
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

void file_context::transfer(const ::file::path & pathNew, const ::file::path & path)
{

   throw ::interface_only();

   //throw ::interface_only();

//#ifdef WINDOWS_DESKTOP
//
//   if (!::MoveFileW(
//      utf8_to_unicode(scopedstr),
//      utf8_to_unicode(scopedstrNew)))
//   {
//
//      DWORD dwError = ::GetLastError();
//
//      if (dwError == ERROR_ALREADY_EXISTS)
//      {
//
//         if (::CopyFileW(
//            utf8_to_unicode(scopedstr),
//            utf8_to_unicode(scopedstrNew),
//            false))
//         {
//
//            if (!::DeleteFileW(utf8_to_unicode(scopedstr)))
//            {
//
//               dwError = ::GetLastError();
//
//               string strError;
//
//               strError.Format("Failed to delete the file to transfer \"%s\" error=%d", psz, dwError);
//
//               informationf("%s", strError);
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
//   ::winrt::Windows::Storage::StorageFile ^ file = get_os_file(scopedstr, 0, 0, nullptr, OPEN_EXISTING, 0, nullptr);
//
//   if (file == nullptr)
//   {
//
//      //informationf("test");
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
//   if (::rename(scopedstr, pszNew) != 0)
//   {
//      int err = errno;
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
//   unsigned int dwError = ::get_last_error();
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
//   if (unlink(scopedstr) != 0)
//   {
//      int err = errno;
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


::file::path file_context::duplicate(const ::file::path & path)
{
   string strCopy("copy");
   string strNew;
   if (directory()->is(path))
   {
      int i = 1;
      while (i <= 100)
      {
         strNew.formatf("%s-%s-%d", path.c_str(), strCopy.c_str(), i);
         if (!exists(strNew))
         {
            copy(strNew, path, false, e_extract_all);
            return strNew;
         }
         i++;
      }
   }
   else
   {
      string strExt = path.final_extension();
      if (!strExt.is_empty())
      {
         strExt = "-" + strExt;
      }
      int i = 1;
      while (i <= 100)
      {
         strNew.formatf("%s-%s-%d%s", path.c_str(), strCopy.c_str(), i, strExt.c_str());
         if (!exists(strNew))
         {
            copy(strNew, path, false, e_extract_all);
            return strNew;
         }
         i++;
      }
   }
   return "";
}


::file::path file_context::paste(const ::file::path & pathLocation, const ::file::path & path)
{

   ::file::path pathFolder = path.folder();

   ::file::path pathDst = pathLocation;

   ::file::path pathSrc = pathFolder;

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


void file_context::trash_that_is_not_trash(const ::file::path & path)
{

   ::file::path strDir = directory()->trash_that_is_not_trash(path);

   directory()->create(strDir);

   transfer(strDir / path.name(), path);

}



void file_context::trash_that_is_not_trash(::file::path_array & stra)
{

   if (stra.size() <= 0)
   {

      return;

   }

   ::file::path strDir = directory()->trash_that_is_not_trash(stra[0]);

   directory()->create(strDir);

   for (int i = 0; i < stra.size(); i++)
   {

      transfer(strDir / stra[i].name(), stra[i]);

   }

}


::file::path file_context::get_filesystem_file(const ::file::path & path)
{

   if (file_system()->exists(path))
   {

      return path;

   }


   auto pathTemp = this->time_square(path.title(), "." + path.all_extensions());

   copy(pathTemp, path);

   return pathTemp;

}


void file_context::get_status(::file::file_status & status, const ::file::path & path)
{

   __UNREFERENCED_PARAMETER(status);
   __UNREFERENCED_PARAMETER(path);

   throw ::interface_only();

   //return false;

}


void file_context::set_status(const ::file::path & path, const ::file::file_status & status)
{

   __UNREFERENCED_PARAMETER(path);
   __UNREFERENCED_PARAMETER(status);

   throw ::interface_only();

   //return ::success;

}


void file_context::replace_with(const ::file::path & pathContext, const ::scoped_string & scopedstrNew, const ::scoped_string & scopedstrOld)
{

   ::file::listing listing;

   string strOldName;

   string strNewName;

   listing.set_listing(pathContext);

   directory()->enumerate(listing);

   for (int i = 0; i < listing.size(); i++)
   {

      strOldName = listing[i].name();

      strNewName = strOldName;

      strNewName.replace_with(scopedstrNew, scopedstrOld);

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
   //if (strFail.has_character())
   //{
   //   App(papp).message_box(nullptr, strFail, e_message_box_icon_exclamation);
   //}

   //return e;


}


void file_context::transfer(::file::file * pfileOut, ::file::file * pfileIn)
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


bool file_context::is_read_only(const ::file::path & path)
{

   //throw ::interface_only();

   return false;

   //#ifdef WINDOWS_DESKTOP
   //
   //   unsigned int dwAttrib = windows_get_file_attributes(scopedstr);
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
   //   if (stat(scopedstr, &st) != 0)
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


   string strTempDir = directory_system()->sys_temp();

   if (!string_ends(strTempDir, "\\") && !string_ends(strTempDir, "/"))
   {

      strTempDir += "\\";

   }

   string str;

   char buf[30];

   for (int i = 0; i < 1000; i++)
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


::file::path file_context::sys_temp_unique(const ::file::path & lpszName)
{

   return directory_system()->sys_temp() / lpszName;

}


file_pointer file_context::time_square_file(const ::scoped_string & scopedstrPrefix, const ::scoped_string & scopedstrSuffix)
{

   return get(time_square(scopedstrPrefix, scopedstrSuffix));

}


file_pointer file_context::get(const ::file::path & path)
{

   directory()->create(path.folder());

   file_pointer fileOut = get_file(path, ::file::e_open_create | ::file::e_open_binary | ::file::e_open_write);

   //   if (fileOut.is_null())
   //   {

   //      throw ::file::exception(error_file_not_found, -1L, -1, name);

   //   }

   return fileOut;

}


::file_pointer file_context::get_temporary_upload_file(const ::file::path & pathCurrent)
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

      strIndex.formatf("%08x\\", i);

      strTempFile = m_papplication->system()->directory_system()->m_pathUpload / (strTime + strIndex + pathCurrent);

      if (!exists(strTempFile))
      {

         break;

      }

      string strMessage;

      auto psystem = system();

      auto pdatetime = psystem->datetime();

      strMessage = pdatetime->date_time_text() + " " + strTempFile;

      file_system()->append_wait("C:\\ca2\\toomuchuploads.txt", strMessage);

      i++;

   }

   auto pfileUpload = get_file(strTempFile,
                               ::file::e_open_defer_create_directory
                               | ::file::e_open_binary
                               | ::file::e_open_create
                               | ::file::e_open_write);

   return pfileUpload;

}


::file::path file_context::replace_with_extension(const ::scoped_string & scopedstrExtension, const ::file::path & path)
{

   ::file::path pathNew(path);

   set_extension(pathNew, scopedstrExtension);

   return pathNew;

}


void file_context::set_extension(::file::path & path, const ::scoped_string & scopedstrExtension)
{

   character_count iEnd = path.rear_find_index('.');

   if (iEnd < 0)
   {

      iEnd = path.length();

   }

   path = path.left(iEnd) + ::str::has_character(scopedstrExtension, ".");

}


//::file::path file_context::dropbox_client()
//{
//
//   throw ::interface_only();
//
//   return {};
//
//}


void file_context::normalize(string & str)
{

   if (str.is_empty())
   {

      return;

   }

   while (str.has_character() &&
          (str.right(1) == "\\" ||
             str.right(1) == "/"))
   {

      str = str.left(str.length() - 1);

   }

}


::std::strong_ordering file_context::cmp(const ::file::path & path1, const ::file::path & path2)
{
   string str1(path1);
   normalize(str1);
   string str2(path2);
   normalize(str2);
   return str1.case_insensitive_order(str2);
}


void file_context::rename(const ::file::path & pathNew, const ::file::path & path)
{

   ::file::path strDir = path.folder();

   ::file::path strDirNew = pathNew.folder();

   if (strDir != strDirNew)
   {

      // rename should work only on files in the same directory/folder

      throw ::exception(::error_failed);

   }

   //if (transfer(scopedstrNew, psz).failed())
   transfer(pathNew, path);
   //{

   //   return ::error_failed;

   //}

   //return ::success;

}


//void file_context::dtf(const ::file::path & pathFile, const ::file::path & pathFolder)
//{
//
//   ::file::listing ls;
//
//   directory()->rls(ls, pszDir);
//
//   dtf(scopedstrFile, ls);
//
//}
//
//
//void file_context::dtf(const ::file::path & pathFile, ::file::path_array & stra)
//{
//
//   file_pointer pfile = get_file(scopedstrFile, ::file::e_open_create | ::file::e_open_write | ::file::e_open_binary);
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
//   __øconstruct(pfile2);
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
//   unsigned long long iPos;
//
//   for (int i = 0; i < stra.size(); i++)
//   {
//      if (case_insensitive_string_ends(stra[i], ".zip"))
//      {
//      }
//      else if (directory()->is(stra[i]))
//         continue;
//      write_n_number(pfile, nullptr, 1);
//      iPos = pfile->get_position();
//      write_gen_string(pfile, nullptr, strMd5);
//      MD5_Init(&ctx);
//      string strRelative = stra[i].relative();
//      write_gen_string(pfile, &ctx, strRelative);
//      if (pfile2->open(stra[i], ::file::e_open_read | ::file::e_open_binary).failed())
//         throw ::exception(::exception("failed"));
//      write_n_number(pfile, &ctx, (int)pfile2->size());
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
//void file_context::ftd(const ::file::path & pathFolder, const ::file::path & pathFile)
//{
//
//   string strVersion;
//
//   file_pointer pfile = get_file(scopedstrFile, ::file::e_open_read | ::file::e_open_binary);
//
//   if (pfile.is_null())
//      throw ::exception(::exception("failed"));
//
//   read_gen_string(pfile, nullptr, strVersion);
//
//   long long n;
//
//   string strRelative;
//   string strMd5;
//   string strMd5New;
//   int iBufSize = 1024 * 1024;
//   memory buf;
//   buf.set_size(iBufSize);
//   long long iLen;
//   MD5_CTX ctx;
//
//   auto pfile2 = __øcreate < ::file::file >();
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
//         ::file::path strPath = ::file::path(scopedstrDir) / strRelative;
//         directory()->create(strPath.folder());
//         if (pfile2->open(strPath, ::file::e_open_create | ::file::e_open_binary | ::file::e_open_write).failed())
//            throw ::exception(::exception("failed"));
//         read_n_number(pfile, &ctx, iLen);
//         while (iLen > 0)
//         {
//            uRead = pfile->read(buf, (unsigned int)(minimum(iBufSize, iLen)));
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




//void file_context::write_n_number(::file::file * pfile, void * pctx, long long iNumber)
//{
//
//   string str;
//
//   str.Format("%I64dn", iNumber);
//
//   pfile->write((const_char_pointer )str);
//
//   if (pctx != nullptr)
//   {
//
//      MD5_Update((MD5_CTX *)pctx, (const_char_pointer )str, (int)str.length());
//
//   }
//
//}


//void file_context::read_n_number(::file::file * pfile, void * pctx, long long & iNumber)
//{
//
//   unsigned long long uRead;
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
//   iNumber = ::str::to_long_long(str);
//
//}

//void file_context::write_gen_string(::file::file * pfile, void * pctx, string & str)
//{
//   ::collection::count iLen = str.length();
//   write_n_number(pfile, pctx, iLen);
//   pfile->write((const_char_pointer )str);
//   if (pctx != nullptr)
//   {
//      MD5_Update((MD5_CTX *)pctx, (const_char_pointer )str, (int)str.length());
//   }
//}

//void file_context::read_gen_string(::file::file * pfile, void * pctx, string & str)
//{
//   long long iLen;
//   read_n_number(pfile, pctx, iLen);
//   char * psz = str.get_buffer((character_count)(iLen + 1));
//
//   pfile->read(scopedstr, (memsize)iLen);
//
//   if (pctx != nullptr)
//   {
//      long long iProcessed = 0;
//      while (iLen - iProcessed > 0)
//      {
//         int iProcess = (int)minimum(1024 * 1024, iLen - iProcessed);
//         MD5_Update((MD5_CTX *)pctx, &psz[iProcessed], iProcess);
//
//         iProcessed += iProcess;
//      }
//   }
//   psz[iLen] = '\0';
//
//   str.release_buffer();
//}


//::pointer < ::file::link > file_context::resolve_link(const ::file::path &path)
//{
//
//   return node()->resolve_link(path);
//
//}


string file_context::get_hash(const ::payload & payloadFile, enum_hash ehash)
{

   auto pfile = get_file(payloadFile, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_none);

   if (!pfile)
   {

      return "";

   }

   memory mem;

   mem.set_size(1024 * 256);

   auto psystem = system();

   auto pcrypto = psystem->crypto();

   auto phasher = pcrypto->create_hasher(ehash);

   memsize iRead;

   while ((iRead = (memsize)pfile->read(mem)) > 0)
   {

      phasher->update({ mem.data(), iRead });

   }

   return ::hex::upper_case_from(phasher->get_hash_and_reset());

}


string file_context::md5(const ::payload & payloadFile)
{

   return get_hash(payloadFile, e_hash_md5);

}


string file_context::nessie(const ::payload & payloadFile)
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


void file_context::get_last_write_time(file_time_t * pfile_time, const ::scoped_string & scopedstrFilename)
{

   throw ::interface_only();

   //return false;

}


void file_context::init_system()
{

   //   auto psystem = system();
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



void file_context::term_context()
{

   //return ::success;

}


void file_context::term_system()
{

   //   auto psystem = system();
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


void file_context::destroy()
{

   m_pfolderResource.defer_destroy();

   file_context_interface::destroy();

}


//bool file_context::prepare_output(::stream & outputstream, path & pathDownloading, const ::stream & os)
//{

//   Sys(pparticle).directory()->mk(pathOut.folder());

//   file_pointer fileOut;

//   long long iTry = 0;

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

   __øconstruct(pfile);

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


file_pointer file_context::data_get_file(const ::scoped_string & scopedstrData, ::file::e_open eopen)
{

   ::string strData(scopedstrData);

   ASSERT(strData.case_insensitive_begins("data:"));

   string strSample = strData.left(4096);

   auto iFind = strSample.find_index(";", 5);

   if (iFind > 5)
   {

      character_count iEncoding1 = strSample.find_index(",", iFind + 1);

      character_count iEncoding2 = strSample.find_index(";", iFind + 1);

      character_count iEncoding = minimum_non_negative(iEncoding1, iEncoding2);

      if (iFind > 5 && iEncoding > iFind)
      {

         string strMimeType = strData.substr(5, iFind - 5);

         string strEncoding = strData.substr(iFind + 1, iEncoding - iFind - 1);

         if (strEncoding.case_insensitive_order("base64") == 0)
         {

            ::pointer<memory_file>pmemoryfile = __allocate memory_file();

            auto psystem = system();

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


folder_pointer file_context::get_folder(::file::file * pfile, const ::scoped_string & scopedstrImplementation, ::file::e_open eopen)
{

   auto pfactory = system()->folder_factory();

   if (!pfactory)
   {

      throw ::exception(::error_failed);

   }

   auto pfolder = __øcreate < ::folder >(pfactory);

   if (!pfolder)
   {

      throw ::exception(::error_failed);

   }

   if (eopen & ::file::e_open_read)
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


file_pointer file_context::http_get_file(const ::url::url & url, ::file::e_open eopen, ::file::e_flag eflag)
{

   if (eopen & (::file::e_open_write | ::file::e_open_truncate | ::file::e_open_create))
   {

      return nullptr;

   }

   auto pdomain = __create_new < ::url_domain >();

   pdomain->create(url.connect().host());

   //bool bSaveCache = domain.m_strRadix != "ca2" || !string_begins(purl->get_object(path), "/matter/");

   bool bBypassCache = (eopen & ::file::e_open_no_cache) || (eflag & ::file::e_flag_bypass_cache);

   bool bDoCache = !bBypassCache;

   ::file::path pathCache;

   if (bDoCache)
   {

      pathCache = url.as_string();

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
      pathCache = directory()->cache() / (pathCache + ".cache");

      if (exists(pathCache))
      {

         auto pfile = get_reader(pathCache);

         if (pfile.ok() && pfile->size() > 0)
         {

            return pfile;

         }

      }

   }

   while_predicateicate_Sleep(60 * 1000, [&]()
   {

      _synchronous_lock synchronouslock(system()->http_download_mutex());

      return system()->http_download_array()->contains(url.as_string()) || system()->http_exists_array()->contains(url.as_string());

      });/* .failed())
   {

      bSaveCache = false;

   }*/


   {

      _synchronous_lock synchronouslock(system()->http_download_mutex());

      if (bDoCache && file_system()->exists(pathCache))
      {

         synchronouslock.unlock();

         auto pfile = file_get_file(pathCache, eopen);

         if (pfile.ok() && pfile->size() > 0)
         {

            return pfile;

         }

      }

   }

   if (bDoCache)
   {

      _synchronous_lock synchronouslock(system()->http_download_mutex());

      system()->http_download_array()->add(url.as_string());

   }

   auto pget = __øcreate < ::nano::http::get >();

   pget->m_url = url;

   pget->m_timeSyncTimeout = 5_hour;

   auto pmemoryfile = create_memory_file();

   pget->want_memory_response(pmemoryfile->get_memory());

   pget->call();

   const_char_pointer pszData = (const_char_pointer )pmemoryfile->get_memory()->data();

   auto size = static_cast<size_t>(pmemoryfile->get_memory()->size());

   //*pmemoryfile->get_primitive_memory() = ;

  /// ::property_set & set = payloadFile["http_set"].property_set_reference();

   pmemoryfile->payload("http_set") = ::transfer(pget->property_set());
   //{

   //   return ::error_failed;

   //}

   if (bDoCache)
   {

      _synchronous_lock synchronouslock(system()->http_download_mutex());

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

         system()->http_download_array()->erase(url.as_string());

      }
      catch (...)
      {

      }

      pmemoryfile->seek_to_begin();

   }

   return pmemoryfile;

}

::file_pointer file_context::shared_reader(const ::payload & payloadFile, ::file::e_open eopen)
{

   return get_reader(payloadFile, eopen | ::file::e_open_share_deny_none);

}


::file_pointer file_context::get_reader(const ::payload & payloadFile, ::file::e_open eopen)
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


::file_pointer file_context::get_writer(const ::payload & payloadFile, ::file::e_open eopen)
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


file_pointer file_context::get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception)
{

   auto p = _get_file(payloadFile, eopen, pfileexception);

   if (!(eopen & ::file::e_open_no_follow_uniform_resource_locator))
   {

      ::file::path path = payloadFile.as_file_path();

      if (path.case_insensitive_ends(".uniform_resource_locator"))
      {

         ::string strUrl = p->full_string();

         strUrl.trim();

         if (!strUrl.case_insensitive_begins("http://")
            && !strUrl.case_insensitive_begins("http://"))
         {

            throw ::exception(error_wrong_state, "Currently can only handle http and https in uniform_resource_locator files.");

         }

         ::file::path pathUniformResourceLocator = strUrl;

         auto pfile = get_file(pathUniformResourceLocator, eopen, pfileexception);

         return pfile;

      }

   }

   return p;

}


file_pointer file_context::_get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception)
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

         pfile = payloadFile.as_property_set()["file"].cast<::file::file>();

         if (pfile.is_set())
         {

            return pfile;

         }

      }

   }

   ::file::path path = payloadFile.as_file_path();

   if (path.is_empty())
   {

      if (eopen & ::file::e_open_file)
      {

         if (eopen & ::file::e_open_no_exception_on_open)
         {

            pfile = __allocate::file::file();

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

      informationf("file_context::get_file yesno.xhtml");

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

   if (path == "matter://main/icon.png")
   {

      informationf("Ok let's hey hohohou");
      informationf("Ok let's hey hohohou");

      //pathProcessed = "zipresource://_matter/integration/_std/_std/main/icon-256.png";

   }

   auto pathProcessed = m_papplication->defer_process_path(path);

   if (path == "matter://main/icon-256.png")
   {

      informationf("for icon-2456 processed path is : %s", pathProcessed.c_str());
      informationf("for icon-2456 processed path is : %s", pathProcessed.c_str());

      //pathProcessed = "zipresource://_matter/integration/_std/_std/main/icon-256.png";

   }

   if (pathProcessed.is_empty())
   {

      //information() << "::file::file_context::get_file file with empty name!!";

      if (eopen & ::file::e_open_no_exception_on_open)
      {

         __construct_new(pfile);

         pfile->m_estatus = error_file_not_found;

         pfile->set_nok();

         return pfile;

      }
      else
      {

         throw file::exception(::error_file_not_found, {}, pathProcessed, ::file::e_open_none, "defer_process_path returns empty path");

      }

      return nullptr;

   }

   auto strProtocol = ::url::url(pathProcessed).connect().protocol();

   if (strProtocol.has_character())
   {

      auto pfile = defer_get_protocol_file(strProtocol, pathProcessed, eopen, pfileexception);

      if (pfile)
      {

         return pfile;

      }

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

      return http_get_file(path, eopen, path.m_flags);

   }
   else if (path.begins_eat("zipresource://"))
   {

      return create_resource_file(path);

   }
   else if (path.case_insensitive_begins_eat("file://"))
   {

      return create_native_file(path, eopen);

   }
   else
   {

      return create_native_file(path, eopen);

   }

   return pfile;

}


::file_pointer file_context::defer_get_protocol_file(const ::scoped_string & scopedstrProtocol, const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception)
{

   return nullptr;

}


::file_pointer file_context::create_native_file(const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception)
{

   ::file_pointer pfile;

   __øconstruct(pfile);

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

//   return output(scopedstrOutput, this, &file_context::transfer, pfileIn);

//}


//bool file_context::transfer(const path & pszOutput, ::stream & istream)
//{

//   return output(scopedstrOutput, this, &file_context::transfer, istream);

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


//::file::path file_context::dropbox_info_network_payload()
//{
//
//   ::file::path pathNetworkPayload;
//
//   pathNetworkPayload = directory_system()->home() / ".dropbox/info" NETWORK_PAYLOAD_DEFAULT_EXTENSION;
//
//   return pathNetworkPayload;
//
//}


::file::path file_context::onedrive_global_ini()
{

   ::file::path pathGlobalIni;

   pathGlobalIni = directory_system()->ca2roaming() / "OneDrive/settings/Personal/global.ini";

   return pathGlobalIni;

}


::file::path file_context::onedrive_cid_ini()
{

   ::file::path pathGlobalIni = onedrive_global_ini();

   string strIni = file_system()->as_string(pathGlobalIni);

   if (strIni.is_empty())
   {

      return "";

   }

   ::property_set set;

   set.parse_ini(strIni);

   string strCid;

   strCid = set["cid"];

   ::file::path pathIni = directory_system()->ca2roaming() / "OneDrive/Settings/Personal/" + strCid + ".ini";

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
//::extended::status file_context::transfer(const ::file::path & pathNew, const ::file::path & pathOld)
//{
//
//   return psystem->m_spfile->transfer(scopedstrNew, pszOld, get_app());
//
//}

//
//::extended::status file_context::del(const ::file::path & path)
//{
//   return psystem->m_spfile->del(scopedstr, get_app());
//}

//::extended::status file_context::rename(const ::file::path & pathNew, const ::file::path & pathOld)
//{
//   return psystem->m_spfile->rename(scopedstrNew, pszOld, get_app());
//}

//void file_context::trash_that_is_not_trash(const ::file::path & path)
//{
//   return psystem->m_spfile->trash_that_is_not_trash(scopedstr, get_app());
//}
//
//void file_context::trash_that_is_not_trash(::file::path_array & stra)
//{
//   return psystem->m_spfile->trash_that_is_not_trash(stra, get_app());
//}

//::extended::status file_context::replace(const ::file::path & pathContext, const ::scoped_string & scopedstrFind, const ::scoped_string & scopedstrReplace)
//{
//   return psystem->m_spfile->replace(scopedstrContext, pszFind, pszReplace, get_app());
//}


//bool file_context::exists(const ::file::path & path)
//{
//
//   return psystem->m_spfile->exists(scopedstrPath, get_app());
//
//}


::file::enum_type file_context::get_type(const ::file::path & path)
{

   auto etype = get_type(path, nullptr);

   if (etype != ::file::e_type_unknown)
   {

      return etype;

   }

   return path_system()->get_type(path);

}


::file::enum_type file_context::safe_get_type(const ::file::path & path)
{

   auto etype = safe_get_type(path, nullptr);

   if (etype != ::file::e_type_unknown)
   {

      return etype;

   }

   return path_system()->safe_get_type(path);

}


/*  bool file_context::exists(const ::scoped_string & scopedstrPath)
   {

      return psystem->m_spfile->exists(strPath, get_app());

   }

   bool file_context::exists(const ::payload & payload)
   {

      const ::scoped_string & scopedstrPath = payload.get_string();


      return psystem->m_spfile->exists(strPath, get_app());

   }*/


   //::payload file_context::length(const ::file::path & path)
   //{
   //
   //   return psystem->m_spfile->length(scopedstrPath, get_app());
   //
   //}


   //::payload file_context::length(const ::scoped_string & scopedstrPath)
   //{


   //   return psystem->m_spfile->length(strPath, get_app());

   //}


   //::payload file_context::length(const ::payload & payload)
   //{

   //   return psystem->m_spfile->length(payload.get_string(), get_app());

   //}

   //
   //::file::path file_context::time(const ::file::path & pathBasePath, int iDepth, const ::scoped_string & scopedstrPrefix, const ::scoped_string & scopedstrSuffix)
   //{
   //
   //   return psystem->m_spfile->time(get_app(), pszBasePath, iDepth, pszPrefix, pszSuffix);
   //
   //}


   //::file::path file_context::time_square(const ::scoped_string & scopedstrPrefix, const ::scoped_string & scopedstrSuffix)
   //{
   //
   //   return psystem->m_spfile->time_square(get_app(), pszPrefix, pszSuffix);
   //
   //}

   //::file::path file_context::time_log(const ::scoped_string & scopedstrId)
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
   //bool file_context::put_contents(const ::payload & payloadFile, const void * pvoidContents, ::collection::count count)
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
   //string file_context::sys_temp(const_char_pointer lpszName, const ::scoped_string & scopedstrExtension)
   //{
   //   return psystem->m_spfile->sys_temp(lpszName, pszExtension, get_app());
   //}


::file_pointer file_context::friendly_get_file(const ::payload & payloadFile, ::file::e_open eopen)
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
//::file_pointer file_context::get_file(const ::payload & payloadFile, unsigned int nOpenFlags)
//{
//
//   return file()->get_file(get_app(), payloadFile, nOpenFlags);
//
//}


//
//void file_context::dtf(const ::file::path & pathFile, const ::file::path & pathFolder)
//{
//
//   return psystem->m_spfile->dtf(scopedstrFile, pszDir, get_app());
//
//}

//bool file_context::is_read_only(const path & psz)
//{
//
//   return psystem->m_spfile->is_read_only(scopedstr, get_app());
//}


//void file_context::dtf(const ::file::path & pathFile, ::file::path_array & stra, ::file::path_array & straRelative)
//{
//
//   return psystem->m_spfile->dtf(scopedstrFile, stra, get_app());
//
//}
//
//
//void file_context::ftd(const ::file::path & pathFolder, const ::file::path & pathFile)
//{
//
//   return psystem->m_spfile->ftd(scopedstrDir, pszFile, get_app());
//
//}


void file_context::crypto_set(const ::payload & payloadFile, const ::scoped_string & scopedstrData, const ::scoped_string & scopedstrSalt)
{

   throw ::interface_only();

   ///return false;

}


void file_context::crypto_get(const ::payload & payloadFile, string & str, const ::scoped_string & scopedstrSalt)
{

   throw ::interface_only();

   ///return false;

}


void file_context::save_lines(const ::payload & payloadFile, string_array & stra)
{

   string str = stra.implode("\n");

   put_text_utf8(payloadFile, str);

   //return true;

}


void file_context::load_lines(string_array & stra, const ::payload & payloadFile)
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


void file_context::touch(const ::file::path & path)
{

   if (!exists(path))
   {

      put_memory(path, nullptr);

   }

}


//void file_context::update_module_path()
//{
//
//   auto psystem = system();
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

   if (etype != e_type_element)
   {

      if (etype != e_type_property_set)
      {

         auto path = payloadFile.as_file_path();

         payloadFile["url"] = path;

      }

      payloadFile["bypass_cache_if_empty"] = true;

   }

}


bool get_bypass_cache_if_empty(const ::payload & payloadFile)
{

   if (payloadFile.m_etype == e_type_property_set)
   {

      if (payloadFile.is_property_true("bypass_cache_if_empty"))
      {

         return true;

      }

   }

   return false;

}


void set_bypass_cache(::payload & payloadFile)
{

   auto etype = payloadFile.m_etype;

   if (payloadFile.m_etype == e_type_path)
   {

      payloadFile.m_ppath->m_flags += ::file::e_flag_bypass_cache;

   }
   else
   {

      if (etype != e_type_property_set)
      {

         auto path = payloadFile.as_file_path();

         payloadFile["url"] = path;

      }

      payloadFile["nocache"] = true;

   }

}


bool get_bypass_cache(const ::payload & payloadFile)
{

   if (payloadFile.m_etype == e_type_path)
   {

      return payloadFile.m_ppath->m_flags & ::file::e_flag_bypass_cache;

   }
   else if (payloadFile.m_etype == e_type_property_set)
   {

      if (payloadFile.is_property_true("nocache"))
      {

         return true;

      }

   }

   return false;

}

void file_context::set(const ::payload & payloadFile, const ::memory_base & memory)
{

   auto writer = get_writer(payloadFile);

   writer->write(memory);

   //return writer.m_estatus;

}


void file_context::unzip_to_folder(const ::file::path & pathFolder, const ::file::path & pathZip, ::function<bool(const::scoped_string & scopedstr) > functionCallback)
{

   auto pfileZip = get_reader(pathZip);

   auto pfolder = system()->create < ::folder >("folder", "zip");

   pfolder->initialize(m_papplication);

   pfolder->open_for_reading(pfileZip);

   pfolder->e_extract_all(pathFolder, nullptr, nullptr, nullptr, functionCallback);

}


::file::path file_context::unzip_exe(const ::file::path & pathZip)
{

   auto pfileZip = get_reader(pathZip);

   auto pfolder = system()->create < ::folder >("folder", "zip");

   pfolder->initialize(m_papplication);

   pfolder->open_for_reading(pfileZip);

   auto uncompressFolder = pathZip.folder() / pathZip.title();

   return pfolder->e_extract_first_ends(uncompressFolder, ".exe");

}


CLASS_DECL_ACME void * file_as_memory_dup(long & size, const_char_pointer psz)
{

   try
   {

      auto mem = ::system()->application()->file()->as_memory(psz);

      size = (long)mem.size();

      if (size > 0)
      {

         auto p = malloc(size);

         memcpy(p, mem.data(), size);

         return p;

      }
      
   }
   catch (...) 
   {

   }

   return nullptr;

}





::property_set file_context::get_ini(const ::payload& payloadFile)
{

   auto str = this->safe_get_string(payloadFile);

   ::property_set set;

   set.parse_ini(str);

   return ::transfer(set);

}


void file_context::set_ini(const ::payload& payloadFile, const ::property_set & set)
{

   auto str = set.get_ini();

   put_text(payloadFile, str);

}


::property_set file_context::get_standard_configuration(const ::payload& payloadFile)
{


   auto str = as_string(payloadFile);

   ::property_set set;

   set.parse_standard_configuration(str);

   return ::transfer(set);

}
