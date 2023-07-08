// From acme/filesystem/file/_.cpp by camilo on 2021-08-09 
// From acme_windows/acme_file.cpp
// 04:38 BRT <3ThomasBorregaardSorensen
#include "framework.h"
#include "acme_file.h"
#include "acme_directory.h"
#include "acme_path.h"
#include "listing.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/io.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/file/memory_map.h"
#include "acme/platform/ini.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/memory.h"
//#include "acme/primitive/collection/string_array.h"
////#include "acme/primitive/datetime/earth_time.h"


CLASS_DECL_ACME void exception_message_box(::particle * pparticle, ::exception & exception, const ::string & strMoreDetails);


void trace_last_error()
{

   information("trace_last_error::todo");

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


file_pointer acme_file::get_file(const ::payload& payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* pfileexception)
{

   if (payloadFile.m_etype == e_type_element)
   {

      auto pfile = payloadFile.cast < ::file::file>();

      if (pfile)
      {

         return pfile;

      }

   }

   auto pfile = m_pcontext->__create < ::file::file >();

   if(!pfile)
   {

      return pfile;

   }

   auto pathFile = payloadFile.as_file_path();

   auto path = acmepath()->defer_process_relative_path(pathFile);

   pfile->open(path, eopen);

   return pfile;

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

   //char * psz = str.get_buffer(iReadAtMostByteCount);

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

   //str.release_buffer();

   return str;

}


string acme_file::safe_get_string(const ::file::path & pathParam, strsize iReadAtMostByteCount, bool bNoExceptionIfNotFound)
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

      return { (const char *)data + 3, size - 3 };

   }
   else
   {

      return { (const char *)data, size };

   }

   return str;

}




string acme_file::get_temporary_file_name(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension)
{

   throw interface_only();

   return {};

}


//void acme_file::write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten)
//{
//
//   throw interface_only();
//
//}




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


void acme_file::find_replace(const ::file::path & path, const ::property_set & set)
{

   auto str = as_string(path);

   for(auto & pproperty : set.propertyptra())
   {

      str.find_replace(pproperty->name(), pproperty->as_string());

   }

   put_contents(path, str);

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


//void acme_file::set_size(FILE * pfile, filesize size)
//{
//
//   throw ::interface_only();
//
//   //return false;
//
//}


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


void acme_file::copy(const ::file::path & pathNew, const ::file::path & pathExisting, bool bOverwrite)
{

   if (acmedirectory()->is(pathExisting))
   {

      if (exists(pathNew))
      {

         throw ::exception(error_not_supported, "currently not supported");

      }

      acmedirectory()->create(pathNew);

      ::file::listing listing;

      listing.set_listing(pathExisting, e_depth_recursively);

      acmedirectory()->enumerate(listing);

      ::file::path strDst;
      ::file::path strSrc;
      ::file::path strDirSrc(pathExisting);
      ::file::path strDirDst(pathNew);

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
   
   auto pathTarget = pathNew;
      
   if (acmedirectory()->is(pathTarget))
   {
      
      pathTarget /= pathExisting.name();
      
   }
      
   _copy(pathTarget, pathExisting, bOverwrite);

}


void acme_file::_copy(const ::file::path & pathDup, const ::file::path & pathSrc, bool bOverwrite)
{
   
   if(!bOverwrite && exists(pathDup))
   {
      
      return;
      
   }
   
   //if(!_memory_map_file_copy(pathDup, pathSrc))
   {
      
      _read_write_file_copy(pathDup, pathSrc, 128_MiB);
      
   }
   
}


bool acme_file::text_is_different(const ::file::path & path1, const ::file::path & path2, ::string * pstr1, ::string * pstr2)
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


bool acme_file::copy_if_text_is_different(const ::file::path & pathTarget, const ::file::path & pathSource, const ::procedure & procedureRunIfFilesAreDifferentAndAfterCopy)
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


bool acme_file::_memory_map_file_copy(const ::file::path & pathTarget, const ::file::path & pathSource)
{

   auto pmemorymapSource = __create < ::file::memory_map >();
   
   auto pmemorymapTarget = __create < ::file::memory_map >();
   
   if(!pmemorymapSource->open_path(pathSource, true, false, false))
   {
      
      return false;
      
   }
      
   if(!pmemorymapTarget->open_path(pathSource, true, true, true, pmemorymapSource->m_size))
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


void acme_file::_read_write_file_copy(const ::file::path & pathTarget, const ::file::path & pathSource, ::memsize sizeBuffer)
{

   auto pfileIn = get_file(pathSource, ::file::e_open_read | ::file::e_open_binary);
   
   auto pfileOut = get_file(pathTarget, ::file::e_open_write | ::file::e_open_binary
                  | ::file::e_open_create | ::file::e_open_truncate);


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




string_array acme_file::lines(const ::file::path & pathParam)
{

   auto path = acmepath()->defer_process_relative_path(pathParam);

   try
   {

      auto pfile = get_file(path, ::file::e_open_read | ::file::e_open_share_deny_none | ::file::e_open_no_exception_on_open);

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


//void acme_file::write(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten)
//{
//
//#if OSBIT > 32
//
//   memsize pos = 0;
//
//   ::u32 dw = 0;
//
//   ::u32 dwWrite;
//
//   memsize uiWrittenTotal = 0;
//
//   while (pos < nCount)
//   {
//
//      dwWrite = (::u32)minimum(nCount - uiWrittenTotal, 0xffffffffu);
//
//      dw = (::u32)(fwrite(&((u8 *)pdata)[pos], 1, dwWrite, file));
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
//   ::u32 dw = 0;
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


void acme_file::append(const ::string & strFile, const block & block)
{

   return append_wait(strFile, block, 0_s);

}




bool acme_file::_exists(const ::file::path & path)
{

   bool bOk = ::safe_file_exists(path.c_str());

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

   auto preader = this->get_file(payloadFile, ::file::e_open_share_deny_none | ::file::e_open_read);

   if (preader.nok())
   {

      throw ::io_exception(error_io);

   }

   string str;

   preader->right_string(str);

   auto pini = __create_new < handle::ini >();

   if (!pini)
   {

      return pini;

   }

   pini->parse_ini(str);

   return ::transfer(pini);

}


::property_set acme_file::parse_standard_configuration(const ::payload & payloadFile)
{


   auto str = as_string(payloadFile);

   ::property_set set;

   set.parse_standard_configuration(str);

   return ::transfer(set);

}


