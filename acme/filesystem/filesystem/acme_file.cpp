// From acme/filesystem/file/_.cpp by camilo on 2021-08-09 
// From acme_windows/acme_file.cpp
// 04:38 BRT <3ThomasBorregaardSørensen
#include "framework.h"
#include "acme_file.h"
#include "acme_directory.h"
#include "acme_path.h"
#include "listing.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/io.h"
#include "acme/filesystem/file/stdio_file.h"
#include "acme/platform/ini.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/memory.h"
//#include "acme/primitive/collection/string_array.h"
////#include "acme/primitive/datetime/earth_time.h"


CLASS_DECL_ACME void exception_message_box(::particle * pparticle, ::exception & exception, const ::string & strMoreDetails);

void trace_last_error()
{

   output_debug_string("trace_last_error::todo");

}
acme_file::acme_file()
{

}


acme_file::~acme_file()
{

}


void acme_file::ensure_exists(const ::file::path & path)
{

   throw ::interface_only();

   //throw ::interface_only();

}


void acme_file::touch(const ::file::path & path)
{

   throw ::interface_only();

   //throw ::interface_only();


}


void acme_file::clear_read_only(const ::file::path & path)
{

   throw ::interface_only();

   //throw ::interface_only();

}


void acme_file::set_file_normal(const ::file::path & path)
{

   throw ::interface_only();

   //throw ::interface_only();

}


bool acme_file::is_equal(const ::file::path & path1, const ::file::path & path2)
{

   auto mem1 = as_memory(path1);

   auto mem2 = as_memory(path2);

   return mem1 == mem2;

}


void acme_file::overwrite_if_different(const ::file::path & pathTarget, const ::file::path & pathSource)
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



::file::path acme_file::module()
{

   if (m_pathExecutable.is_empty())
   {

      auto pnode = acmenode();

      auto pathModule = pnode->module_path_source();

      m_pathExecutable = pathModule;

   }

   return m_pathExecutable;

}



file_pointer acme_file::open(const ::file::path & pathParam, const ::file::e_open & eopen)
{

   auto pfile = m_pcontext->__create < ::file::file >();

   if(!pfile)
   {

      return pfile;

   }

   auto path = acmepath()->defer_process_relative_path(pathParam);

   pfile->open(path, eopen);

   return pfile;

}


file_pointer acme_file::stdio_open(const ::file::path & pathParam, const ::scoped_string & scopedstrAttrs, int iShare)
{

   auto pfile = m_pcontext->__create_new < ::stdio_file >();

   if (!pfile)
   {

      return pfile;

   }

   auto path = acmepath()->defer_process_relative_path(pathParam);

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


string acme_file::as_string(const ::file::path & pathParam, strsize iReadAtMostByteCount, bool bNoExceptionIfNotFound)
{
   
   auto memory = as_memory(pathParam, iReadAtMostByteCount);

   ::string str;

   auto data = (char *) memory.data();

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

   //auto pfile = m_pcontext->__create_new < stdio_file >();

   //if (bNoExceptionIfNotFound)
   //{

   //   pfile->m_eflag |= stdio_file::flag_no_exception_if_not_found;

   //}

   //auto path = acmepath()->defer_process_relative_path(pathParam);

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
   //   iReadAtMostByteCount = (strsize) uSize;
   //   
   //}
   //else
   //{
   //   
   //   iReadAtMostByteCount = minimum(iReadAtMostByteCount, (strsize)uSize);
   //   
   //}

   //char * psz = str.get_string_buffer(iReadAtMostByteCount);

   //::size_t iPos = 0;

   //while (iReadAtMostByteCount - iPos > 0)
   //{

   //   auto dwRead = pfile->read(psz + iPos, (size_t)iReadAtMostByteCount - iPos);

   //   if (dwRead <= 0)
   //   {

   //      break;

   //   }

   //   iPos += dwRead;

   //}

   //psz[iPos] = '\0';

   //str.release_string_buffer();

   return str;

}


memsize acme_file::as_memory(const ::file::path & pathParam, void * p, memsize s)
{

   stdio_file file;

   auto path = acmepath()->defer_process_relative_path(pathParam);

   file.open(path, "r", _SH_DENYNO);

   auto iReadAtMostByteCount = s;

   byte * psz = (byte *) p;

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


string acme_file::get_temporary_file_name(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension)
{

   throw interface_only();

   return {};

}


void acme_file::write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten)
{

   throw interface_only();
   
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


void acme_file::append(const ::file::path & pathFile, const block & block)
{

   acme_file::append_wait(pathFile, block, 0_s);

}


bool acme_file::exists(const ::file::path & pathParam)
{

   if(pathParam.is_empty())
   {

      throw ::exception(error_bad_argument);

   }

   auto path = acmepath()->defer_process_relative_path(pathParam);

   auto bExists = _exists(path);

   if(!bExists)
   {

      return false;

   }

   return true;

}


//void acme_file::put_contents(const ::file::path & path, const ::scoped_string & scopedstr)
//{
//
//   throw ::interface_only();
//
//   //throw ::interface_only();
//
//}


void acme_file::get_temporary_file_name_template(char * szRet, strsize iBufferSize, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrTemplate)
{

   throw ::interface_only();

   //throw ::interface_only();

}


filesize acme_file::get_size(const ::file::path & path)
{

   throw ::interface_only();

   return 0;

}


filesize acme_file::get_size(FILE * pfile)
{

   return get_size_fd(fileno(pfile));

}


filesize acme_file::get_size_fd(int iFile)
{

   throw ::interface_only();

   return 0;

}


void acme_file::clear_application_data()
{

   throw ::interface_only();

   //return -1;

}


bool acme_file::is_true(const ::file::path & path)
{

   throw ::interface_only();

   //throw ::interface_only();

}


void acme_file::set_size(const ::file::path & pathName, filesize size)
{

   throw ::interface_only();

   //return success;

}


void acme_file::set_size(int iFileDescriptor, filesize size)
{

   throw ::interface_only();

   //return false;

}


void acme_file::set_size(FILE * pfile, filesize size)
{

   throw ::interface_only();

   //return false;

}


void acme_file::transfer(const ::file::path & pathNewName, const ::file::path & pathOldName)
{

   copy(pathNewName, pathOldName, true);

   erase(pathOldName);

}


void acme_file::erase(const ::file::path & pathParam)
{

   if(pathParam.is_empty())
   {

      throw ::exception(error_null_pointer);

   }

   auto path = acmepath()->defer_process_relative_path(pathParam);

    _erase(path);

   //if(!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void replace_char(char * sz, char ch1, char ch2)
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


void acme_file::copy(const ::file::path & pathTarget, const ::file::path & pathSource, bool bOverwrite)
{

   if (acmedirectory()->is(pathSource))
   {

      if (exists(pathTarget))
      {

         throw ::exception(error_failed);

      }

      acmedirectory()->create(pathTarget);

      ::file::listing listing;

      listing.set_listing(pathSource, e_depth_recursively);

      acmedirectory()->enumerate(listing);

      ::file::path strDst;
      ::file::path strSrc;
      ::file::path strDirSrc(pathSource);
      ::file::path strDirDst(pathTarget);

      for (i32 i = 0; i < listing.size(); i++)
      {

         strSrc = listing[i];

         strDst = strSrc;

         strDst.case_insensitive_begins_eat(strDirSrc);

         strDst = strDirDst / strDst;

         if (acmedirectory()->is(strSrc))
         {

            acmedirectory()->create(strDst);

         }
         else
         {

            if (!acmedirectory()->is(strDst.folder()))
            {

               acmedirectory()->create(strDst.folder());

            }

            _copy(strDst, strSrc, bOverwrite);

         }

      }

      return;

   }
   else
   {

      _copy(pathTarget, pathSource, bOverwrite);

   }

}


void acme_file::_copy(const ::file::path & pathTarget, const ::file::path & pathSource, bool bOverwrite)
{

#ifdef WINDOWS

   FILE * in = _wfopen(wstring(pathSource), L"r"); //create the input file for reading

#else

   FILE * in = fopen(pathSource.c_str(), "r"); //create the input file for reading

#endif

   if (in == NULL)
      throw io_exception(error_io);

#ifdef WINDOWS

   FILE * out = _wfopen(wstring(pathTarget), L"w"); // create the output file for writing

#else

   FILE * out = fopen(pathTarget.c_str(), "w"); // create the output file for writing

#endif

   if (out == NULL)
      throw io_exception(error_io);

   memory memory;

   memory.set_size(1024);

   size_t read;

   while ((read = fread(memory.data(), 1, memory.size(), in)) > 0)
   {

      fwrite(memory.data(), 1, read, out); // write the input file to the output file

   }

}


class ::time acme_file::modification_time(const ::file::path & path)
{

   throw ::interface_only();

   return {};

}


void acme_file::set_modification_time(const ::file::path & path, const class ::time& time)
{

   throw ::interface_only();

}


//
//::time acme_file::modification_time(const ::file::path & path)
//{
//
//   throw ::interface_only();
//
//   throw ::interface_only();
//
//}


void acme_file::synchronize(const ::file::path & path1, const ::file::path & path2)
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

      //estatus = set_modification_time(psz1, time2);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return ;

   }
   else if ((!bExists2 && bExists1) || ((bExists1 && bExists2) && (time2 < time1)))
   {

       copy(path2, path1, true);


      return;

//#if !defined(WINDOWS)
//
      //estatus = set_modification_time(psz2, time1);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }

   //return ::success_none;

}


void acme_file::save_stra(const ::file::path & pathName, const string_array & stra)
{

   throw ::interface_only();

   //return ::success;

}


void acme_file::load_stra(const ::file::path & pathName, string_array & stra, bool bAddEmpty)
{

   throw ::interface_only();

   //return ::success;

}


void acme_file::put_contents(const ::file::path & path, const memory_base & memory)
{

   put_block(path, memory);

}


void acme_file::put_contents(const ::file::path & path, const ::scoped_string & scopedstrContents)
{


   throw interface_only();

   //put_contents(path, scopedstrContents, scopedstrContents.size());

  
}


void acme_file::put_lines(const ::file::path& path, const ::string_array& straLines)
{

#ifdef WINDOWS_DESKTOP

   put_block(path, straLines.implode("\r\n") + "\r\n");

#else

   put_block(path, straLines.implode("\n") + "\n");

#endif

}


void acme_file::put_block(const ::file::path & path, const block & block)
{

   throw interface_only();

   //put_contents(path, (const char *) block.data(), block.size());

}



void acme_file::as_block(block & block, const ::file::path & path)
{

   auto size = as_memory(path, block.data(), block.size());

   if(size != block.size())
   {

      throw ::exception(error_wrong_type);

   }

}


string acme_file::first_line(const ::file::path & path)
{

   return line(path, 0);

}


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


string_array acme_file::lines(const ::file::path & pathParam)
{

   auto path = acmepath()->defer_process_relative_path(pathParam);

   try
   {

      auto pfile = open(path, ::file::e_open_read | ::file::e_open_share_deny_none
      | ::file::e_open_no_exception_on_open);

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
   catch (const ::exception & exception)
   {

      if (exception.m_estatus == error_file_not_found)
      {

         return {};

      }

      throw exception;

   }

}


void acme_file::set_line(const ::file::path & pathParam, index iLine, const ::scoped_string & scopedstrLine)
{

   if (iLine < 0)
   {

      throw ::exception(error_index_out_of_bounds);

   }

   string str;

   auto path = acmepath()->defer_process_relative_path(pathParam);

   m_pacmedirectory->create(path.folder());

   auto pfile = open(path, ::file::e_open_read_write | ::file::e_open_create | ::file::e_open_no_truncate);

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

         if (iPosStart <= 0)
         {

            iPosStart = pfile->get_position();

         }

      }

      iLastChar = iChar;

   }

   if (iLine > 0)
   {

      while(iLine > 0)
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
            open(
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


//string acme_file::get_temporary_file_name(const ::scope_string & strName, const ::scoped_string & scopedstrExtension)
//{
//
//#ifdef WINDOWS
//
//   WCHAR pPathBuffer[MAX_PATH * 16];
//
//   ::u32 dwRetVal = GetTempPathW(sizeof(pPathBuffer) / sizeof(WCHAR), pPathBuffer);
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
//      path /= (string(lpszName) + "." + string(pszExtension));
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


void acme_file::write(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten)
{

#if OSBIT > 32

   memsize pos = 0;

   ::u32 dw = 0;

   ::u32 dwWrite;

   memsize uiWrittenTotal = 0;

   while (pos < nCount)
   {

      dwWrite = (::u32)minimum(nCount - uiWrittenTotal, 0xffffffffu);

      dw = (::u32)(fwrite(&((u8 *)pdata)[pos], 1, dwWrite, file));

      if (dw != dwWrite)
      {

         uiWrittenTotal += dw;

         if (puiWritten != nullptr)
         {

            *puiWritten = uiWrittenTotal;

         }

         if (dw < dwWrite)
         {
            // is_disk_full?
            throw ::exception(error_disk_full);

         }

         throw ::exception(error_io);
         //return false;

      }

      uiWrittenTotal += dw;

      if (dw != dwWrite)
      {

         break;

      }

      pos += dw;

   }

   if (puiWritten != nullptr)
   {

      *puiWritten = uiWrittenTotal;

   }

   //return uiWrittenTotal == nCount;

#else

   ::u32 dw = 0;

   dw = ::fwrite(pdata, 1, (size_t)nCount, file);

   int_bool bOk = dw == nCount;

   if (puiWritten != nullptr)
   {

      *puiWritten = dw;

   }

   if(!bOk)
   {

      throw io_exception(error_io);

   }

#endif

}


void acme_file::append(const ::string & strFile, const block & block)
{

   return append_wait(strFile, block, 0_s);

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


bool acme_file::_exists(const ::file::path & path)
{

   bool bOk = ::file_exists(path.c_str());

   return bOk;

   //if(!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void acme_file::_erase(const ::file::path & path)
{

    throw ::interface_only();

}


::file::path acme_file::time_put_contents(const ::file::path& pathFolder, const ::string& strPrefix, const ::string& strExtension, const ::string& str)
{

   ::file::path path;

   int i = 0;

   while (true)
   {

      string strHexadecimal;

      strHexadecimal.format("%08x", i);

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


::pointer<::handle::ini>acme_file::get_ini(const ::payload & payloadFile)
{

   auto preader = this->open(payloadFile, ::file::e_open_share_deny_none | ::file::e_open_read);

   if (preader.nok())
   {

      throw ::io_exception(error_io);

   }

   string str;

   preader->as(str);

   auto pini = __create_new < handle::ini >();

   if (!pini)
   {

      return pini;

   }

   pini->parse_ini(str);

   return ::transfer(pini);

}





