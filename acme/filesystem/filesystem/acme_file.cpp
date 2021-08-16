// From acme/filesystem/file/_.cpp by camilo on 2021-08-09 
// From acme_windows/acme_file.cpp
// 04:38 BRT <3ThomasBorregaardS�rensen
#include "framework.h"
#include "acme/operating_system.h"
#include "acme_dir.h"
#include "acme_file.h"
#include <stdio.h>

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


::file::path acme_file::executable()
{

   if (m_pathExecutable.is_empty())
   {

      auto pnode = m_psystem->node();

      auto pathModule = pnode->module_path_source();

      m_pathExecutable = pathModule;

   }

   return m_pathExecutable;

}



file_transport acme_file::open(const ::file::path & path, const ::file::e_open & eopen)
{

   auto pfile = __create_new < ::file::file >();

   if(!pfile)
   {

      return pfile;

   }

   auto estatus = pfile->open(path, eopen);

   if(!estatus)
   {

      return estatus;

   }

   return pfile;

}


memory acme_file::as_memory(const char * path, strsize iReadAtMostByteCount)
{

   __throw(error_interface_only);

   return ::memory();

}


memsize acme_file::as_memory(const char * path, void * p, memsize s)
{

   __throw(error_interface_only);

   return -1;

}


string acme_file::as_string(const char * path, strsize iReadAtMostByteCount)
{

   __throw(error_interface_only);

   return ::memory();
}





string acme_file::get_temporary_file_name(const char * lpszName, const char * pszExtension)
{

#ifdef WINDOWS

   WCHAR pPathBuffer[MAX_PATH * 16];

   ::u32 dwRetVal = GetTempPathW(sizeof(pPathBuffer) / sizeof(WCHAR), pPathBuffer);

   if (dwRetVal > sizeof(pPathBuffer) || (dwRetVal == 0))
   {

      debug_print("GetTempPath failed (%d)\n", ::GetLastError());

      return "";

   }

#else

   char pPathBuffer[MAX_PATH * 16];

   strcpy(pPathBuffer, "/tmp/");

#endif

   ::file::path pathFolder(pPathBuffer);

   for (int i = 0; i < 1000; i++)
   {

      ::file::path path;

      path = pathFolder;

      path /= lpszName;

      path /= __str(i);

      path /= (string(lpszName) + "." + string(pszExtension));

      if (this->exists(path))
      {

         if (this->delete_file(path))
         {

            return ::move(path);

         }

      }
      else
      {

         return ::move(path);

      }

   }

   return "";

}


bool acme_file::write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten)

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

         return false;

      }

      uiWrittenTotal += dw;

      if (dw != dwWrite)
         break;

      pos += dw;

   }

   if (puiWritten != nullptr)
   {

      *puiWritten = uiWrittenTotal;

   }

   return uiWrittenTotal == nCount;

#else

   ::u32 dw = 0;

   dw = ::fwrite(pdata, 1, (size_t)nCount, file);


   int_bool bOk = dw == nCount;

   if (puiWritten != nullptr)
   {

      *puiWritten = dw;

   }

   return bOk;

#endif

}


bool acme_file::append_wait(const char * strFile, const block & block, const ::duration & duration)
{

   auto pacmedir = m_pacmedir;

pacmedir->create(::file_path_folder(strFile));

   if (!  

pacmedir->is(::file_path_folder(strFile)))
   {

      return false;

   }

   wstring wstr(strFile);

   FILE * pfile = nullptr;

   auto millisStart = ::millis::now();

   while (true)
   {

#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
      pfile = fopen(strFile, "ab");
#else
      pfile = _wfopen(wstr, L"ab");
#endif

      if (pfile != nullptr)
      {

         break;

      }

      if (millisStart.elapsed() > duration)
      {

         return false;

      }

      sleep(500_ms);

   }

   fwrite(block.get_data(), block.get_size(), 1, pfile);

   fclose(pfile);

   return true;

}


//bool acme_file::append_wait(const ::string & strFile, const ::string & str, ::u32 tickTimeout)
//{
//
//   return acme_file::append_wait(strFile, str, str.get_length(), tickTimeout);
//
//}


bool acme_file::append(const char * strFile, const block & block)
{

   return acme_file::append_wait(strFile, block, 0);

}


bool acme_file::exists(const char * path)
{

   __throw(error_interface_only);

   return false;

}


bool acme_file::put_contents(const char * path, const char * contents, strsize len)
{

   __throw(error_interface_only);

   return false;

}


bool acme_file::get_temporary_file_name_template(char * szRet, strsize iBufferSize, const char * lpszName, const char * pszExtension, const char * pszTemplate)
{

   __throw(error_interface_only);

   return false;

}


filesize acme_file::get_size(const char * path)
{

   __throw(error_interface_only);

   return -1;

}


filesize acme_file::get_size(FILE * pfile)
{

   __throw(error_interface_only);

   return -1;

}



filesize acme_file::get_size_fd(int iFile)
{

   __throw(error_interface_only);

   return -1;

}


//FILE * acme_file::FILE_open(const char * path, const char * attrs, int iShare)
//{
//
//#ifdef WINDOWS
//
//   wstring wstrPath(path);
//
//   wstring wstrAttrs(attrs);
//
//   auto pfile = _wfsopen(wstrPath, wstrAttrs, iShare);
//
//#else
//
//   auto pfile = fopen(path, attrs);
//
//#endif
//
//   if (!pfile)
//   {
//
//      return nullptr;
//
//   }
//
//   return pfile;
//
//}
//
//
//i32 acme_file::FILE_printf(FILE * pfile, const char * pformat, ...)
//{
//
//   va_list valist;
//
//   va_start(valist, pformat);
//
//   vfprintf(pfile, pformat, valist);
//
//   va_end(valist);
//
//   return -1;
//
//}
//
//
//i32 acme_file::FILE_close(FILE * pfile)
//{
//
//   return fclose(pfile);
//
//}
//
//
//i32 acme_file::FILE_eof(FILE * pfile)
//{
//
//   return feof(pfile);
//
//}
//
//
//filesize acme_file::FILE_seek(FILE * pfile, filesize offset, i32 origin)
//{
//
//   return fseek(pfile, (long)(offset), origin);
//
//}
//
//
//filesize acme_file::FILE_tell(FILE * pfile)
//{
//
//   return ftell(pfile);
//
//}
//
//
//filesize acme_file::FILE_read(void * buffer, memsize size, memsize count, FILE * pfile)
//{
//
//   return fread(buffer, (size_t)size, (size_t)count, pfile);
//
//}
//
//
//filesize acme_file::FILE_write(const void * buffer, memsize size, memsize count, FILE * pfile)
//{
//
//   return fwrite(buffer, (size_t)size, (size_t)count, pfile);
//
//}
//
//
//char * acme_file::FILE_gets(char * str, strsize n, FILE * pfile)
//{
//
//   return fgets(str, (int)n, pfile);
//
//}
//
//
//i32 acme_file::FILE_getc(FILE * pfile)
//{
//
//   return ::getc(pfile);
//
//}
//
//
//i32 acme_file::FILE_ungetc(i32 c, FILE * pfile)
//{
//
//   return ::ungetc(c, pfile);
//
//}
//
//
//i32 acme_file::FILE_error(FILE * pfile)
//{
//
//   return ferror(pfile);
//
//}
//
//
//i32 acme_file::FILE_flush(FILE * pfile)
//{
//
//   return fflush(pfile);
//
//}
//
//
//filesize acme_file::FILE_get_size(FILE * pfile)
//{
//
//#ifdef WINDOWS
//   auto pos = _ftelli64(pfile);
//#elif (defined(ANDROID) && __ANDROID_API__ < 24) || defined(MACOS)
//   auto pos = ftello(pfile);
//#else
//   auto pos = ftello64(pfile);
//#endif
//
//   fseek(pfile, 0, SEEK_END);
//
//#ifdef WINDOWS
//   auto len = _ftelli64(pfile);
//#elif (defined(ANDROID) && __ANDROID_API__ < 24) || defined(MACOS)
//   auto len = ftello(pfile);
//#else
//   auto len = ftello64(pfile);
//#endif
//
//#ifdef WINDOWS
//   _fseeki64(pfile, (long)(pos), SEEK_SET);
//#elif (defined(ANDROID) && __ANDROID_API__ < 24) || defined(MACOS)
//   fseeko(pfile, (long)(pos), SEEK_SET);
//#else
//   fseeko64(pfile, (long)(pos), SEEK_SET);
//#endif
//
//   return len;
//
//}


bool acme_file::is_true(const char * path)
{

   __throw(error_interface_only);

   return false;

}


bool acme_file::set_size(const char * lpszName, filesize size)
{

   __throw(error_interface_only);

   return false;

}


bool acme_file::set_size(int iFileDescriptor, filesize size)
{

   __throw(error_interface_only);

   return false;

}


bool acme_file::set_size(FILE * pfile, filesize size)
{

   __throw(error_interface_only);

   return false;

}


bool acme_file::move(const char * pszNewName, const char * pszOldName)
{

   auto bOk = copy(pszNewName, pszOldName, true);

   if(!bOk)
   {

      return false;

   }

   bool bOkDelete = delete_file(pszOldName);

   if(!bOk)
   {

      output_debug_string("failed to delete file \"" + string(pszOldName) + "\"");

   }

   return bOk;

}


bool acme_file::delete_file(const char * pszFileName)
{

   __throw(error_interface_only);

   return false;

}


//bool acme_file::set_line(const char * pszPath, index iLine, const char * pszLine)
//{
//
//   if (iLine < 0)
//   {
//
//      return false;
//
//   }
//
//   string str;
//
//   ::file::path path(pszPath);
//
//   auto pacmedir = m_pacmedir;
//
//            auto psystem = m_psystem;

//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->create(path.folder());
//
//   FILE * file = FILE_open(path, "a+", _SH_DENYWR);
//
//   if (file == nullptr)
//   {
//
//      ::e_status estatus = ::get_last_status();
//
//      return false;
//
//   }
//
//   int iChar;
//
//   string strLine;
//
//   int iLastChar = -1;
//
//   index iPosStart = -1;
//
//   index iPosEnd = -1;
//
//   while (iLine >= 0)
//   {
//
//      iChar = fgetc(file);
//
//      if (iChar == EOF)
//      {
//
//         break;
//
//      }
//
//      if (iChar == '\r')
//      {
//
//         iLine--;
//
//      }
//      else if (iChar == '\n')
//      {
//
//         if (iLastChar != '\r')
//         {
//
//            iLine--;
//
//         }
//
//      }
//      else if (iLine == 0)
//      {
//
//         if (iPosStart <= 0)
//         {
//
//            iPosStart = ftell(file);
//
//         }
//
//      }
//
//      iLastChar = iChar;
//
//   }
//
//   if (iLine > 0)
//   {
//
//      fwrite("\n", 1, (size_t)iLine, file);
//
//      fwrite(pszLine, 1, strlen(pszLine), file);
//
//      fclose(file);
//
//   }
//   else
//   {
//
//      iPosEnd = ftell(file);
//
//      ::file::path pathTime = path;
//
//      pathTime += ".time";
//
//      FILE * file2 = FILE_open(pathTime, "w", _SH_DENYWR);
//
//      if (iPosStart > 0)
//      {
//
//         memory m;
//
//         fseek(file, 0, SEEK_SET);
//
//         m.set_size(iPosStart);
//
//         fread(m.get_data(), 1, (size_t)iPosStart, file);
//
//         fwrite(m.get_data(), 1, (size_t)iPosStart, file2);
//
//      }
//
//      fwrite(pszLine, 1, strlen(pszLine), file2);
//
//      index iEnd = fseek(file, 0, SEEK_END);
//
//      if (iEnd - iPosEnd > 0)
//      {
//
//         memory m;
//
//         fseek(file, (long)iPosEnd, SEEK_SET);
//
//         m.set_size(iEnd - iPosEnd);
//
//         fread(m.get_data(), 1, (size_t)m.get_size(), file);
//
//         fwrite(m.get_data(), 1, (size_t)m.get_size(), file2);
//
//      }
//
//      fclose(file2);
//
//      fclose(file);
//
//#if defined(WINDOWS) || defined(APPLE_IOS)
//
//      if (!copy(path, pathTime.c_str(), true))
//      {
//
//         return false;
//
//      }
//
//      delete_file(pathTime);
//
//#else
//
//      ::system("mv -f \"" + string(pathTime) + "\" \"" + string(path) + "\"");
//
//#endif
//
//   }
//
//   return true;
//
//}







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


bool acme_file::copy(const char * pszDup, const char * pszSrc, bool bOverwrite)
{

   __throw(error_interface_only);

   return false;

}


bool acme_file::save_stra(const char * lpszName, const string_array & stra)
{

   __throw(error_interface_only);

   return false;

}


bool acme_file::load_stra(const char * lpszName, string_array & stra, bool bAddEmpty)
{

   __throw(error_interface_only);

   return false;

}


bool acme_file::put_contents(const char * path, const memory_base & memory)
{

   __throw(error_interface_only);

   return false;

}


bool acme_file::put_contents(const char * path, const char * contents)
{

   auto bOk = put_contents(path, contents, ::str::string_safe_length(contents));

   if (!bOk)
   {

      return false;

   }

   return true;

}


bool acme_file::as_memory(memory_base & memory, const char * path, memsize iReadAtMostByteCount)
{

   __throw(error_interface_only);

   return false;

}


bool acme_file::put_block(const char * path, const block & block)
{

   return put_contents(path, (const char *) block.get_data(), block.get_size());

}



bool acme_file::as_block(block & block, const char * path)
{

   return as_memory(path, block.get_data(), block.get_size()) == block.get_size();

}


string acme_file::first_line(const char * path)
{

   return line(path, 0);

}


string acme_file::line(const char * path, index iLine)
{

   string str;

#ifdef WINDOWS

   FILE * file = _fsopen(path, "r", _SH_DENYNO);

#else

   FILE * file = fopen(path, "r");

#endif

   if (file == nullptr)
   {

      trace_last_error();

      return "";

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


string_array acme_file::lines(const char * path)
{

   string_array straLines;

   auto pfile = open(path, ::file::e_open_read);

   if (!pfile)
   {

      return straLines;

   }

   string strLine;

   while (pfile->read_string(strLine))
   {

      straLines.add(strLine);

   }

   return straLines;

}


::e_status acme_file::set_line(const char * pszPath, index iLine, const char * pszLine)
{

   if (iLine < 0)
   {

      return error_index_out_of_bounds;

   }

   string str;

   ::file::path path(pszPath);

   m_pacmedir->create(path.folder());

   auto pfile = open(path, ::file::e_open_read_write);

   if (!pfile)
   {

      trace_last_error();

      return pfile;

   }

   int iChar;

   string strLine;

   int iLastChar = -1;

   index iPosStart = -1;

   index iPosEnd = -1;

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

      pfile->write(pszLine);

   }
   else
   {

      iPosEnd = pfile->get_position();

      ::file::path pathTime = path;

      pathTime += ".time";

      auto pfile2 = open(path, ::file::e_open_write | ::file::e_open_share_exclusive);

      if(!pfile2)
      {

         return pfile2;

      }

      if (iPosStart > 0)
      {

         memory m;

         pfile->seek_to_begin();

         m.set_size(iPosStart);

         pfile->read(m.get_data(), iPosStart);

         pfile2->write(m.get_data(), iPosStart);

      }

      pfile2->write(pszLine);

      index iEnd = pfile->get_size();

      if (iEnd - iPosEnd > 0)
      {

         memory m;

         pfile->set_position(iPosEnd);

         m.set_size(iEnd - iPosEnd);

         pfile->read(m.get_data(), m.get_size());

         pfile2->write(m.get_data(), m.get_size());

      }

      if (!copy(path, pathTime.c_str(), true))
      {

         return error_failed;

      }

      delete_file(pathTime);

   }

   return true;

}


//string acme_file::get_temporary_file_name(const char * lpszName, const char * pszExtension)
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
//      path /= __str(i);
//
//      path /= (string(lpszName) + "." + string(pszExtension));
//
//      if (exists(path))
//      {
//
//         if (delete_file(path))
//         {
//
//            return ::move(path);
//
//         }
//
//      }
//      else
//      {
//
//         return ::move(path);
//
//      }
//
//   }
//
//   return "";
//
//}




bool acme_file::write(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten)
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

         return false;

      }

      uiWrittenTotal += dw;

      if (dw != dwWrite)
         break;

      pos += dw;

   }

   if (puiWritten != nullptr)
   {

      *puiWritten = uiWrittenTotal;

   }

   return uiWrittenTotal == nCount;

#else

   ::u32 dw = 0;

   dw = ::fwrite(pdata, 1, (size_t)nCount, file);


   int_bool bOk = dw == nCount;

   if (puiWritten != nullptr)
   {

      *puiWritten = dw;

   }

   return bOk;

#endif

}



bool acme_file::append(const ::string & strFile, const block & block)
{

   return append_wait(strFile, block, 0);

}



bool acme_file::append_wait(const ::string & strFile, const block & block, const ::duration & duration)
{

   m_pacmedir->create(::file_path_folder(strFile));

   if (!m_pacmedir->is(::file_path_folder(strFile)))
   {

      return false;

   }

   wstring wstr(strFile);

   FILE * pfile = nullptr;

   auto millisStart = ::millis::now();

   while (true)
   {

#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
      pfile = fopen(strFile, "ab");
#else
      pfile = _wfopen(wstr, L"ab");
#endif

      if (pfile != nullptr)
      {

         break;

      }

      if (millisStart.elapsed() > duration)
      {

         return false;

      }

      sleep(500_ms);

   }

   fwrite(block.get_data(), block.get_size(), 1, pfile);

   fclose(pfile);

   return true;

}


//bool file_append_wait(const ::string & strFile, const ::string & str, ::u32 tickTimeout)
//{
//
//   return file_append_wait(strFile, str, str.get_length(), tickTimeout);
//
//}

