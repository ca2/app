// From acme/filesystem/file/_.cpp by camilo on 2021-08-09 
// From acme_windows/file_system.cpp
// 04:38 BRT <3ThomasBorregaardSorensen
#include "framework.h"
#include "file_system.h"
#include "directory_system.h"
#include "path_system.h"
#include "listing.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/io.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/file/memory_map.h"
//#include "acme/platform/ini.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/platform/session.h"
//#include "acme/prototype/collection/string_array.h"
////#include "acme/prototype/datetime/earth_time.h"


CLASS_DECL_ACME void exception_message_box(::particle* pparticle, ::exception& exception,
                                           const ::scoped_string & scopedstrMoreDetails);


file_system::file_system()
{

}


file_system::~file_system()
{

}


void file_system::ensure_exists(const ::file::path& path)
{

   throw ::interface_only();

   //throw ::interface_only();

}


void file_system::touch(const ::file::path& path)
{

   throw ::interface_only();

   //throw ::interface_only();


}


void file_system::touch_app_cloud(const ::file::path& path, const char* pszContentIdentifier)
{

   touch(path);

   //throw ::interface_only();


}


void file_system::clear_read_only(const ::file::path& path)
{

   throw ::interface_only();

   //throw ::interface_only();

}


void file_system::set_file_normal(const ::file::path& path)
{

   throw ::interface_only();

   //throw ::interface_only();

}


bool file_system::is_equal(const ::file::path& path1, const ::file::path& path2)
{

   auto mem1 = as_memory(path1);

   auto mem2 = as_memory(path2);

   return mem1 == mem2;

}


void file_system::overwrite_if_different(const ::file::path& pathTarget, const ::file::path& pathSource)
{

   if (!exists(pathSource))
   {

      throw ::exception(error_not_found);

   }

   if (exists(pathTarget) && is_equal(pathTarget, pathSource))
   {

      return;

   }

   copy(pathTarget, pathSource, true);

}


::file::path file_system::module()
{

   if (m_pathExecutable.is_empty())
   {

      auto pnode = node();

      auto pathModule = pnode->module_path_source();

      m_pathExecutable = pathModule;

   }

   return m_pathExecutable;

}


file_pointer file_system::get_file(const ::payload& payloadFile, ::file::e_open eopen,
                                   ::pointer<::file::exception>* pfileexception)
{

   if (payloadFile.m_etype == e_type_element)
   {

      auto pfile = payloadFile.cast<::file::file>();

      if (pfile)
      {

         return pfile;

      }

   }

   auto pfile = application()->__øcreate<::file::file>();

   if (!pfile)
   {

      return pfile;

   }

   auto pathFile = payloadFile.as_file_path();

   auto path = path_system()->defer_process_relative_path(pathFile);

   pfile->open(path, eopen);

   return pfile;

}


file_pointer file_system::get_reader(const ::payload& payloadFile, ::file::e_open eopen,
                                     ::pointer<::file::exception>* pfileexception)
{

   return get_file(payloadFile, eopen | ::file::e_open_read, pfileexception);

}


file_pointer file_system::get_writer(const ::payload& payloadFile, ::file::e_open eopen,
                                     ::pointer<::file::exception>* pfileexception)
{

   return get_file(payloadFile, eopen | ::file::e_open_read_write, pfileexception);

}


string file_system::as_string(const ::file::path& pathParam, character_count iReadAtMostByteCount,
                              bool bNoExceptionIfNotFound)
{

   auto memory = as_memory(pathParam, iReadAtMostByteCount);

   ::string str;

   auto data = (char *)memory.data();

   auto size = memory.size();

   if (::is_null(data) || size <= 0)
   {

      return {};

   }
   else if (data[0] == '\xEF' && data[1] == '\xBB' && data[2] == '\xBF') // BOM
   {

      return {(const char *)data + 3, size - 3};

   }
   else
   {

      return {(const char *)data, size};

   }

   //auto pfile = m_papplication->__create_new < stdio_file >();

   //if (bNoExceptionIfNotFound)
   //{

   //   pfile->m_eflag |= stdio_file::flag_no_exception_if_not_found;

   //}

   //auto path = path_system()->defer_process_relative_path(pathParam);

   //pfile->open(path, "r", _SH_DENYNO);

   //if (bNoExceptionIfNotFound)
   //{

   //   if (pfile->m_eflag & stdio_file::flag_file_not_found)
   //   {

   //      return {};

   //   }

   //}

   //string str;

   //auto uSize = pfile->size();
   //
   //if(iReadAtMostByteCount < 0)
   //{
   //
   //   iReadAtMostByteCount = (character_count) uSize;
   //
   //}
   //else
   //{
   //
   //   iReadAtMostByteCount = minimum(iReadAtMostByteCount, (character_count)uSize);
   //
   //}

   //char * psz = str.get_buffer(iReadAtMostByteCount);

   //::size_t iPos = 0;

   //while (iReadAtMostByteCount - iPos > 0)
   //{

   //   auto dwRead = pfile->read(scopedstr + iPos, (size_t)iReadAtMostByteCount - iPos);

   //   if (dwRead <= 0)
   //   {

   //      break;

   //   }

   //   iPos += dwRead;

   //}

   //psz[iPos] = '\0';

   //str.release_buffer();

   return str;

}


string file_system::safe_get_string(const ::file::path& pathParam, character_count iReadAtMostByteCount,
                                    bool bNoExceptionIfNotFound)
{

   auto memory = safe_get_memory(pathParam, iReadAtMostByteCount);

   ::string str;

   auto data = (char *)memory.data();

   auto size = memory.size();

   if (::is_null(data) || size <= 0)
   {

      return {};

   }
   else if (data[0] == '\xEF' && data[1] == '\xBB' && data[2] == '\xBF') // BOM
   {

      return {(const char *)data + 3, size - 3};

   }
   else
   {

      return {(const char *)data, size};

   }

   return str;

}


string file_system::__safe_get_string(const ::file::path& pathParam, character_count iReadAtMostByteCount,
   bool bNoExceptionIfNotFound)
{

   auto memory = __safe_get_memory(pathParam, iReadAtMostByteCount);

   ::string str;

   auto data = (char*)memory.data();

   auto size = memory.size();

   if (::is_null(data) || size <= 0)
   {

      return {};

   }
   else if (data[0] == '\xEF' && data[1] == '\xBB' && data[2] == '\xBF') // BOM
   {

      return { (const char*)data + 3, size - 3 };

   }
   else
   {

      return { (const char*)data, size };

   }

   return str;

}

string file_system::get_temporary_file_name(const ::scoped_string& scopedstrName,
                                            const ::scoped_string& scopedstrExtension)
{

   throw interface_only();

   return {};

}


//void file_system::write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten)
//{
//
//   throw interface_only();
//
//}


void file_system::append(const ::file::path& pathFile, const block& block)
{

   file_system::append_wait(pathFile, block, 0_s);

}


::filesize file_system::size(const ::file::path & pathFile)
{

   auto memory = as_memory(pathFile);

   return memory.size();

}


::memory file_system::slice(const ::file::path & pathFile, memsize start, memsize count)
{

   auto memory = as_memory(pathFile);

   return memory.slice(start, count);

}


::memory file_system::beginning(const ::file::path & pathFile, memsize len)
{

   return slice(pathFile, 0, len);

}


::memory file_system::ending(const ::file::path & pathFile, memsize len)
{

   return slice(pathFile, size(pathFile) - len, len);

}


bool file_system::append_unique_line(const file::path& pathFile, const scoped_string& scopedstrLine)
{

   ::string_array lines;

   if (this->exists(pathFile))
   {

      lines = this->lines(pathFile);

   }

   if (lines.contains(pathFile))
   {

      return false;

   }

   ::string strAppend;

   strAppend = scopedstrLine;

   if (lines.has_element())
   {

      auto ending = this->ending(pathFile, 1);

      if (ending[0] != '\r' && ending[0] != '\n')
      {

         strAppend = "\n" + strAppend;

      }

   }

   strAppend += "\n";

   this->append(pathFile, strAppend);

   return true;

}


::collection::count file_system::find_and_erase(const ::file::path& pathFile, const block& block)
{

   auto memory = as_memory(pathFile);

   ::collection::count c = 0;

   while (true)
   {

      auto start = memory.find_index(block);

      if (start < 0)
      {

         if (c > 0)
         {

            put_block(pathFile, memory);

         }

         return c;

      }

      c++;

      memory.erase(start, block.size());

   }


}


bool file_system::exists(const ::file::path& pathParam)
{

   if (pathParam.is_empty())
   {

      throw ::exception(error_bad_argument);

   }

   auto path = path_system()->defer_process_relative_path(pathParam);

   if (path.case_insensitive_begins("data:"))
   {

      return true;

   }

   auto bExists = _exists(path);

   if (!bExists)
   {

      return false;

   }

   return true;

}


bool file_system::__exists(const ::file::path& path)
{

   if (path.is_empty())
   {

      return false;

   }

   auto bExists = _exists(path);

   if (!bExists)
   {

      return false;

   }

   return true;

}


//void file_system::put_contents(const ::file::path & path, const ::scoped_string & scopedstr)
//{
//
//   throw ::interface_only();
//
//   //throw ::interface_only();
//
//}


void file_system::get_temporary_file_name_template(char* szRet, character_count iBufferSize,
                                                   const ::scoped_string& scopedstrName,
                                                   const ::scoped_string& scopedstrExtension,
                                                   const ::scoped_string& scopedstrTemplate)
{

   throw ::interface_only();

   //throw ::interface_only();

}


filesize file_system::get_size(const ::file::path& path)
{

   throw ::interface_only();

   return 0;

}


filesize file_system::get_size_fd(int iFile)
{

   throw ::interface_only();

   return 0;

}


void file_system::clear_application_data()
{

   throw ::interface_only();

   //return -1;

}


void file_system::find_replace(const ::file::path& path, const ::property_set & set)
{

   auto str = as_string(path);

   for (auto& pproperty: set)
   {

      str.find_replace(pproperty->name(), pproperty->as_string());

   }

   put_contents(path, str);

}


void file_system::put_app_cloud_data(const ::file::path& path, const char* pszContentIdentifier, const ::block& block)
{

   auto pathAppCloud = path_system()->defer_get_icloud_container_path(path, pszContentIdentifier);

   this->put_contents(pathAppCloud, pszContentIdentifier);

}


::memory file_system::get_app_cloud_data(const ::file::path& path, const char* pszContentIdentifier)
{

   auto pathAppCloud = path_system()->defer_get_icloud_container_path(path, pszContentIdentifier);

   return this->as_memory(pathAppCloud);

}


void file_system::put_documents_cloud_data(const ::file::path& path, const ::block& block)
{

   auto pathAppCloud = path_system()->defer_get_icloud_container_path(path, "Documents");

   this->put_contents(pathAppCloud, block);

}


::memory file_system::get_documents_cloud_data(const ::file::path& path)
{

   auto pathAppCloud = path_system()->defer_get_icloud_container_path(path, "Documents");

   return this->as_memory(pathAppCloud);

}


bool file_system::is_true(const ::file::path& path)
{

   throw ::interface_only();

   //throw ::interface_only();

}


void file_system::set_size(const ::file::path& pathName, filesize size)
{

   throw ::interface_only();

   //return success;

}


void file_system::set_size(int iFileDescriptor, filesize size)
{

   throw ::interface_only();

   //return false;

}


//void file_system::set_size(FILE * pfile, filesize size)
//{
//
//   throw ::interface_only();
//
//   //return false;
//
//}


void file_system::transfer(const ::file::path& pathNewName, const ::file::path& pathOldName)
{

   copy(pathNewName, pathOldName, true);

   erase(pathOldName);

}


void file_system::erase(const ::file::path& pathParam)
{

   if (pathParam.is_empty())
   {

      throw ::exception(error_null_pointer);

   }

   auto path = path_system()->defer_process_relative_path(pathParam);

   _erase(path);

   //if(!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void file_system::defer_erase(const ::file::path& path)
{

   if (exists(path))
   {

      erase(path);

   }

}


bool file_system::safe_erase(const ::file::path& path)
{

   try
   {

      defer_erase(path);

      return true;

   }
   catch (...)
   {


   }

   return false;

}


void replace_char(char* sz, char ch1, char ch2)
{

   while (*sz)
   {

      if (*sz == ch1)
      {

         *sz = ch2;

      }

      sz++;

   }

}


void file_system::copy(const ::file::path& pathNew, const ::file::path& pathExisting, bool bOverwrite)
{

   if (directory_system()->is(pathExisting))
   {

      if (exists(pathNew))
      {

         throw ::exception(error_not_supported, "currently not supported");

      }

      directory_system()->create(pathNew);

      ::file::listing listing;

      listing.set_listing(pathExisting, e_depth_recursively);

      directory_system()->enumerate(listing);

      ::file::path strDst;
      ::file::path strSrc;
      ::file::path strDirSrc(pathExisting);
      ::file::path strDirDst(pathNew);

      for (int i = 0; i < listing.size(); i++)
      {

         strSrc = listing[i];

         strDst = strSrc;

         strDst.case_insensitive_begins_eat(strDirSrc);

         strDst = strDirDst / strDst;

         if (directory_system()->is(strSrc))
         {

            directory_system()->create(strDst);

         }
         else
         {

            if (!directory_system()->is(strDst.folder()))
            {

               directory_system()->create(strDst.folder());

            }

            _copy(strDst, strSrc, bOverwrite);

         }

      }

      return;

   }

   auto pathTarget = pathNew;

   if (directory_system()->is(pathTarget))
   {

      pathTarget /= pathExisting.name();

   }

   _copy(pathTarget, pathExisting, bOverwrite);

}


void file_system::_copy(const ::file::path& pathDup, const ::file::path& pathSrc, bool bOverwrite)
{

   if (!bOverwrite && exists(pathDup))
   {

      return;

   }

   //if(!_memory_map_file_copy(pathDup, pathSrc))
   {

      _read_write_file_copy(pathDup, pathSrc, 128_MiB);

   }

}


bool file_system::text_is_different(const ::file::path& path1, const ::file::path& path2, ::string* pstr1,
                                    ::string* pstr2)
{

   ::string str1 = this->safe_get_string(path1);

   ::string str2 = this->safe_get_string(path2);

   if (pstr1)
   {

      *pstr1 = str1;

   }

   if (pstr2)
   {

      *pstr2 = str2;

   }

   bool bIsDifferent = str1 != str2;

   return bIsDifferent;

}


bool file_system::copy_if_text_is_different(const ::file::path& pathTarget, const ::file::path& pathSource,
                                            const ::procedure& procedureRunIfFilesAreDifferentAndAfterCopy)
{

   ::string strSource;

   bool bIsDifferent = text_is_different(pathTarget, pathSource, nullptr, &strSource);

   if (bIsDifferent)
   {

      this->put_contents(pathTarget, strSource);

      if (procedureRunIfFilesAreDifferentAndAfterCopy)
      {

         procedureRunIfFilesAreDifferentAndAfterCopy();

      }

   }

   return bIsDifferent;

}


bool file_system::_memory_map_file_copy(const ::file::path& pathTarget, const ::file::path& pathSource)
{

   auto pmemorymapSource = __øcreate<::file::memory_map>();

   auto pmemorymapTarget = __øcreate<::file::memory_map>();

   if (!pmemorymapSource->open_path(pathSource, true, false, false))
   {

      return false;

   }

   if (!pmemorymapTarget->open_path(pathSource, true, true, true, pmemorymapSource->m_size))
   {

      return false;

   }

   try
   {

      memory_copy(pmemorymapTarget->m_pdata, pmemorymapSource->m_pdata, pmemorymapSource->m_size);

   }
   catch (...)
   {

      return false;

   }

   return true;

}


void file_system::_read_write_file_copy(const ::file::path& pathTarget, const ::file::path& pathSource,
                                        ::memsize sizeBuffer)
{

   if (pathSource.case_insensitive_ends("/store.zip"))
   {


      information() << "copy .../store.zip";

   }

   auto pfileIn = get_file(pathSource, ::file::e_open_read | ::file::e_open_binary);

   auto pfileOut = get_file(pathTarget, ::file::e_open_write | ::file::e_open_binary
                                        | ::file::e_open_create | ::file::e_open_truncate |
                                        ::file::e_open_defer_create_directory);


   //#ifdef WINDOWS
   //
   //   FILE * out = _wfopen(wstring(pathTarget), L"w"); // create the output file for writing
   //
   //#else
   //
   //   FILE * out = fopen(pathTarget.c_str(), "w"); // create the output file for writing
   //
   //#endif

   //   if (out == NULL)
   //   {
   //
   //      throw io_exception(error_io);
   //
   //   }

   memory memory;

   memory.set_size(::maximum(1, sizeBuffer));

   size_t read;

   while ((read = pfileIn->read(memory)) > 0)
   {

      pfileOut->write(memory.data(), read);

   }

   pfileOut->set_modification_time(pfileIn->modification_time());

}


class ::time file_system::modification_time(const ::file::path& path)
{

   throw ::interface_only();

   return {};

}


void file_system::set_modification_time(const ::file::path& path, const class ::time& time)
{

   throw ::interface_only();

}


//
//::time file_system::modification_time(const ::file::path & path)
//{
//
//   throw ::interface_only();
//
//   throw ::interface_only();
//
//}


void file_system::synchronize(const ::file::path& path1, const ::file::path& path2)
{

   auto time1 = modification_time(path1);

   auto time2 = modification_time(path2);

   auto bExists1 = exists(path1);

   auto bExists2 = exists(path2);

   if ((!bExists1 && bExists2) || ((bExists1 && bExists2) && (time1 < time2)))
   {

      copy(path1, path2, true);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = set_modification_time(scopedstr1, time2);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return;

   }
   else if ((!bExists2 && bExists1) || ((bExists1 && bExists2) && (time2 < time1)))
   {

      copy(path2, path1, true);


      return;

      //#if !defined(WINDOWS)
      //
      //estatus = set_modification_time(scopedstr2, time1);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }

   //return ::success_none;

}


void file_system::save_stra(const ::file::path& pathName, const string_array& stra)
{

   throw ::interface_only();

   //return ::success;

}


void file_system::load_stra(const ::file::path& pathName, string_array& stra, bool bAddEmpty)
{

   throw ::interface_only();

   //return ::success;

}


//void file_system::put_contents(const ::file::path& path, const memory_base& memory)
//{
//
//   put_block(path, memory);
//
//}


void file_system::put_contents(const ::file::path& path, const ::block& block)
{


   throw interface_only();

   //put_contents(path, scopedstrContents, scopedstrContents.size());


}


void file_system::put_block(const ::file::path& path, const block& block)
{

   throw interface_only();

   //put_contents(path, (const char *) block.data(), block.size());

}


void file_system::put_now(const ::file::path& path)
{

   auto timeNow = ::earth::time::now();

   put_time(path, timeNow);

}


void file_system::put_time(const ::file::path& path, const ::earth::time& time)
{

   ::string strTime = datetime()->date_time_text(time);

   strTime += " UTC";

   put_block(path, strTime);

}


::earth::time file_system::as_time(const ::file::path& path)
{

   ::string strTime = as_string(path);

   if (strTime.is_empty())
   {

      return {};

   }

   int iPath = 0;

   int iPathCount = 0;

   auto time = datetime()->strtotime(session()->text_context(), strTime, iPath, iPathCount);

   return time;

}


::earth::time file_system::safe_time(const ::file::path& path)
{

   ::string strTime = safe_get_string(path);

   if (strTime.is_empty())
   {

      return {};

   }

   int iPath = 0;

   int iPathCount = 0;

   auto time = datetime()->strtotime(session()->text_context(), strTime, iPath, iPathCount);

   return time;

}


void file_system::as_block(block& block, const ::file::path& path)
{

   auto size = as_memory(path, block.data(), block.size());

   if (size != block.size())
   {

      throw ::exception(error_wrong_type);

   }

}


string file_system::first_line(const ::file::path& path)
{

   return line(path, 0);

}


string_array file_system::lines(const ::file::path& pathParam)
{

   auto path = path_system()->defer_process_relative_path(pathParam);

   try
   {

      auto pfile = get_file(
         path, ::file::e_open_read | ::file::e_open_share_deny_none | ::file::e_open_no_exception_on_open);

      if (pfile.nok())
      {

         return {};

      }

      string_array straLines;

      string strLine;

      while (pfile->read_string(strLine))
      {

         straLines.add(strLine);

      }

      return ::transfer(straLines);

   }
   catch (const ::exception& exception)
   {

      if (exception.m_estatus == error_file_not_found)
      {

         return {};

      }

      throw exception;

   }

}


void file_system::set_line(const ::file::path& pathParam, ::collection::index iLine,
                           const ::scoped_string& scopedstrLine)
{

   if (iLine < 0)
   {

      throw ::exception(error_index_out_of_bounds);

   }

   string str;

   auto path = path_system()->defer_process_relative_path(pathParam);

   m_pdirectorysystem->create(path.folder());

   auto pfile = get_file(path, ::file::e_open_read_write | ::file::e_open_create | ::file::e_open_no_truncate);

   //if (!pfile)
   //{

   //   trace_last_error();

   //   return pfile;

   //}

   int iChar;

   string strLine;

   int iLastChar = -1;

   filesize iPosStart = -1;

   filesize iPosEnd = -1;

   while (iLine >= 0)
   {

      iChar = pfile->getc();

      if (iChar == -1)
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

         if (iPosStart <= 0)
         {

            iPosStart = pfile->get_position();

         }

      }

      iLastChar = iChar;

   }

   if (iLine > 0)
   {

      while (iLine > 0)
      {

         pfile->put('\n');

         iLine--;

      }

      pfile->write(scopedstrLine);

   }
   else
   {

      iPosEnd = pfile->get_position();

      ::file::path pathTime = path;

      pathTime += ".time";

      {

         auto pfile2 =
            get_file(
               pathTime,
               ::file::e_open_write
               | ::file::e_open_share_exclusive
               | ::file::e_open_defer_create_directory
               | ::file::e_open_create);

         //if (!pfile2)
         //{

         //   return pfile2;

         //}

         if (iPosStart > 0)
         {

            memory m;

            pfile->seek_to_begin();

            m.set_size((memsize)iPosStart);

            pfile->read(m);

            pfile2->write(m);

         }

         pfile2->write(scopedstrLine);

         auto iEnd = pfile->size();

         if (iEnd - iPosEnd > 0)
         {

            memory m;

            pfile->set_position(iPosEnd);

            m.set_size((memsize)(iEnd - iPosEnd));

            pfile->read(m);

            pfile2->write(m);

         }

      }

      copy(path, pathTime.c_str(), true);
      //{

      //   return error_failed;

      //}

      erase(pathTime);

   }

   ///   return true;

}


//string file_system::get_temporary_file_name(const ::scope_string & strName, const ::scoped_string & scopedstrExtension)
//{
//
//#ifdef WINDOWS
//
//   WCHAR pPathBuffer[MAX_PATH * 16];
//
//   unsigned int dwRetVal = GetTempPathW(sizeof(pPathBuffer) / sizeof(WCHAR), pPathBuffer);
//
//   if (dwRetVal > sizeof(pPathBuffer) || (dwRetVal == 0))
//   {
//
//      debug_print("GetTempPath failed (%d)\n", ::GetLastError());
//
//      return "";
//
//   }
//
//#else
//
//   char pPathBuffer[MAX_PATH * 16];
//
//   strcpy(pPathBuffer, "/tmp/");
//
//#endif
//
//   ::file::path pathFolder(pPathBuffer);
//
//   for (int i = 0; i < 1000; i++)
//   {
//
//      ::file::path path;
//
//      path = pathFolder;
//
//      path /= lpszName;
//
//      path /= as_string(i);
//
//      path /= (string(lpszName) + "." + string(scopedstrExtension));
//
//      if (exists(path))
//      {
//
//         if (delete_file(path))
//         {
//
//            return ::transfer(path);
//
//         }
//
//      }
//      else
//      {
//
//         return ::transfer(path);
//
//      }
//
//   }
//
//   return "";
//
//}


//void file_system::write(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten)
//{
//
//#if OSBIT > 32
//
//   memsize pos = 0;
//
//   unsigned int dw = 0;
//
//   unsigned int dwWrite;
//
//   memsize uiWrittenTotal = 0;
//
//   while (pos < nCount)
//   {
//
//      dwWrite = (unsigned int)minimum(nCount - uiWrittenTotal, 0xffffffffu);
//
//      dw = (unsigned int)(fwrite(&((unsigned char *)pdata)[pos], 1, dwWrite, file));
//
//      if (dw != dwWrite)
//      {
//
//         uiWrittenTotal += dw;
//
//         if (puiWritten != nullptr)
//         {
//
//            *puiWritten = uiWrittenTotal;
//
//         }
//
//         if (dw < dwWrite)
//         {
//            // is_disk_full?
//            throw ::exception(error_disk_full);
//
//         }
//
//         throw ::exception(error_io);
//         //return false;
//
//      }
//
//      uiWrittenTotal += dw;
//
//      if (dw != dwWrite)
//      {
//
//         break;
//
//      }
//
//      pos += dw;
//
//   }
//
//   if (puiWritten != nullptr)
//   {
//
//      *puiWritten = uiWrittenTotal;
//
//   }
//
//   //return uiWrittenTotal == nCount;
//
//#else
//
//   unsigned int dw = 0;
//
//   dw = ::fwrite(pdata, 1, (size_t)nCount, file);
//
//   int_bool bOk = dw == nCount;
//
//   if (puiWritten != nullptr)
//   {
//
//      *puiWritten = dw;
//
//   }
//
//   if(!bOk)
//   {
//
//      throw io_exception(error_io);
//
//   }
//
//#endif
//
//}


void file_system::append(const ::scoped_string & scopedstrFile, const block& block)
{

   return append_wait(strFile, block, 0_s);

}


bool file_system::_exists(const ::file::path& path)
{

   bool bOk = ::safe_file_exists(path.c_str());

   return bOk;

   //if(!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void file_system::_erase(const ::file::path& path)
{

   throw ::interface_only();

}


::file::path file_system::time_put_contents(const ::file::path& pathFolder, const ::scoped_string & scopedstrPrefix,
                                            const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstr)
{

   ::file::path path;

   int i = 0;

   while (true)
   {

      string strHexadecimal;

      strHexadecimal.formatf("%08x", i);

      path = pathFolder / (strPrefix + "-" + strHexadecimal + "." + strExtension);

      if (exists(path))
      {

         i++;

         continue;

      }

      put_contents(path, str);

      break;

   }

   return path;

}




// file_system::file_system()
// {
//
// }
//
//
// file_system::~file_system()
// {
//
//
// }
//

void file_system::initialize(::particle* pparticle)
{

   /*auto estatus = */
   ::object::initialize(pparticle);

   //if(!estatus)
   //{
   //
   //   return estatus;
   //
   //}

   ::file::path pathModule = this->module();

   m_pathModule = pathModule;

   //return estatus;

}


void file_system::init_system()
{

   //   auto estatus = update_module_path();
   //
   //   if(!estatus)
   //   {
   //
   //      return estatus;
   //
   //   }
   //
   //return estatus;

   //return ::success;

}


//void file_system::update_module_path()
//{
//
//   return ::success;
//
//}
