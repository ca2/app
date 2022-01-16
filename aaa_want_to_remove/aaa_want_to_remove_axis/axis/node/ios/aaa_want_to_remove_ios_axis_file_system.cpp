

#include <sys/stat.h>
#include <ctype.h>


struct PROCESS_INFO_t
{
   string csProcess;
   u32 dwImageListIndex;
};


namespace ios
{


   namespace axis
   {


      file_system::file_system(::object * pobject) :
         ::object(pobject),
         ::file::system(pobject),
         ::file::axis::system(pobject),
         ::ios::file_system(pobject)
      {
      }


//      bool file_system::path::is_equal(const ::string & lpszFilPathA, const ::string & lpszFilPathB)
//      {
//         string stra(lpszFilPathA);
//         string wstrb(lpszFilPathB);
//
//         //   ::str::international::ACPToUnicode(stra, lpszFilPathA);
//         //   ::str::international::ACPToUnicode(wstrb, lpszFilPathB);
//         if(stra == wstrb)
//            return true;
//
//         /*if(_GetShortPathName(stra, lpszFilPathA) == 0)
//          return false;
//          if(_GetShortPathName(wstrb, lpszFilPathB) == 0)
//          return false;*/
//         return stra == wstrb;
//
//      }
//
//
//      bool file_system::path::eat_end_level(string & str, i32 iLevelCount, const ::string & lpSeparator)
//      {
//
//         strsize iLast = str.length() - 1;
//
//         if(iLast < 0)
//            return iLevelCount <= 0;
//
//         while(str[iLast] == '/' || str[iLast] == '\\')
//            iLast--;
//
//         for(i32 i = 0; i < iLevelCount; i++)
//         {
//
//            strsize iFind1 = str.reverse_find('/', iLast);
//
//            strsize iFind2 = str.reverse_find('\\', iLast);
//
//            strsize iFind = maximum(iFind1, iFind2);
//
//            if(iFind >= iLast)
//               return false;
//
//            if(iFind < 0)
//               return false;
//
//            iLast = iFind;
//
//            while(str[iLast] == '/' || str[iLast] == '\\')
//               iLast--;
//
//         }
//
//         str.Truncate(iLast + 1);
//
//         return true;
//
//      }
//
//      bool file_system::path::is_relative(const ::string & psz)
//      {
//         string strPath(psz);
//         if(strPath.find(':') != -1 && strPath.find(':') < 10)
//            return false;
//         if(strPath.find('/') == 0 || strPath.find('\\') == 0)
//            return false;
//         return true;
//      }
//
//      void file_system::get_ascendants_path(const ::string & pcsz, string_array & straParam)
//      {
//         string_array stra;
//         get_ascendants_name(pcsz, stra);
//         string str;
//         bool bUrl = purl->is_url(pcsz);
//#ifdef LINUX
//         bool bLinux = true;
//         str += "/";
//#else
//         bool bLinux = false;
//#endif
//
//         for(i32 i = 0; i < stra.get_size(); i++)
//         {
//            str += stra[i];
//            if(stra[i].find('/') < 0 && stra[i].find('\\') < 0)
//            {
//               str += "\\";
//            }
//            if(bUrl || bLinux)
//            {
//               str.replace("\\", "/");
//            }
//            else
//            {
//               str.replace("/", "\\");
//            }
//            straParam.add(str);
//         }
//      }
//
//      void file_system::get_ascendants_name(const ::string & pcsz, string_array & straParam)
//      {
//         string_array straSeparator;
//         straSeparator.add("/");
//         straSeparator.add("\\");
//         straParam.add_smallest_tokens(pcsz, straSeparator, false);
//         if(straParam.get_count() > 0)
//         {
//            strsize iFind = straParam[0].find(':');
//            if(iFind >= 2)
//            {
//               straParam[0] += "//";
//            }
//            else if(iFind == 1)
//            {
//               straParam[0] += "\\";
//            }
//         }
//      }
//
//      ::payload file_system::length(const ::string & pszPath)
//      {
//
//         ::payload varRet;
//
//#ifdef WINDOWS
//
//         WIN32_FILE_ATTRIBUTE_DATA data;
//
//         if(!GetFileAttributesExW(::str::international::utf8_to_unicode(pszPath), GetFileExInfoStandard, &data))
//         {
//            varRet.set_type(::e_type_null);
//         }
//         else
//         {
//            varRet = (u32) data.nFileSizeLow;
//         }
//
//#else
//
//         struct stat stat;
//
//         if(::stat(pszPath, &stat)  == -1)
//         {
//            varRet.set_type(::e_type_null);
//         }
//         else
//         {
//            varRet = stat.st_size;
//         }
//
//#endif
//
//         return varRet;
//
//      }
//
//
//      string file_system::time_square(::aura::application *  papp, const ::string & pszPrefix, const ::string & pszSuffix)
//      {
//         string str;
//         pcontext->m_papexcontext->dir().time_square(str);
//         return time(papp, str, 25, pszPrefix, pszSuffix);
//      }
//
//      string file_system::time_log(::aura::application *  papp, const ::string & pszId)
//      {
//         return time(papp, pcontext->m_papexcontext->dir().time_log(pszId), 9);
//      }
//
//      string file_system::time(::aura::application *  papp, const ::string & psz, i32 iMaxLevel, const ::string & pszPrefix, const ::string & pszSuffix)
//      {
//         single_lock lockMachineEvent(
//                                      (psystem->machine_event_central() != nullptr) ?
//                                      psystem->machine_event_central().m_machineevent.m_mutex
//                                      : ((::mutex *) nullptr), true);
//         i32 iIncLevel = -1;
//         string str;
//         string strPrefix(pszPrefix);
//         string strSuffix(pszSuffix);
//      restart:
//         str.Empty();
//         str = psz;
//         pcontext->m_papexcontext->dir().create(str, papp);
//         string_array straTitle;
//         string strFormat;
//         for(i32 i = 1; i <= iMaxLevel;)
//         {
//            pcontext->m_papexcontext->dir().create(str, papp);
//            if(!pcontext->m_papexcontext->dir().is(str, papp))
//               __throw(::exception("time square dir does not exist"));
//            straTitle.erase_all();
//            pcontext->m_papexcontext->dir().ls(papp, str, nullptr, &straTitle);
//            if(i < iMaxLevel)
//            {
//               i32 iMax = filterex_time_square("", straTitle);
//               if(iMax == -1)
//               {
//                  str = pcontext->m_papexcontext->dir().path(str, "00");
//                  pcontext->m_papexcontext->dir().create(str, papp);
//               }
//               else if(iMax == 99)
//               {
//                  iIncLevel = i - 1;
//                  goto restart;
//               }
//               else
//               {
//                  if(i == iIncLevel)
//                  {
//                     iMax++;
//                  }
//                  strFormat.format("%02d", iMax);
//                  str = pcontext->m_papexcontext->dir().path(str, strFormat);
//                  if(i == iIncLevel)
//                  {
//                     pcontext->m_papexcontext->dir().create(str, papp);
//                  }
//               }
//               i++;
//            }
//            else // if i == iMaxLevel
//            {
//               pcontext->m_papexcontext->dir().ls(papp, str, nullptr, &straTitle);
//               i32 iMax = filterex_time_square(pszPrefix, straTitle);
//               if(iMax == -1)
//               {
//                  str = pcontext->m_papexcontext->dir().path(str, strPrefix+"00"+strSuffix);
//                  if(file_system::mk_time(str))
//                     break;
//               }
//               else if(iMax == 99)
//               {
//                  iIncLevel = iMaxLevel - 1;
//                  goto restart;
//               }
//               else
//               {
//                  iMax++;
//                  strFormat.format("%02d", iMax);
//                  str = pcontext->m_papexcontext->dir().path(str, strPrefix+strFormat+strSuffix);
//                  if(file_system::mk_time(str))
//                     break;
//               }
//               return "";
//            }
//         }
//         return str;
//      }
//
//      i32 file_system::filterex_time_square(const ::string & pszPrefix, string_array & stra)
//      {
//         i32 iMax = -1;
//         i32 iIndex;
//         for(i32 i = 0; i < stra.get_size(); i++)
//         {
//            string str = stra[i];
//            if(::str::begins_eat_ci(str, pszPrefix))
//            {
//               if(str.get_length() < 2)
//               {
//                  stra.erase_at(i);
//                  i--;
//                  continue;
//               }
//               if(!isdigit((uchar) str[0]) || !isdigit((uchar) str[1]))
//               {
//                  stra.erase_at(i);
//                  i--;
//                  continue;
//               }
//               iIndex = atoi(str.Mid(0, 2));
//               if(iIndex > iMax)
//                  iMax = iIndex;
//            }
//         }
//         return iMax;
//      }
//
//      // fail if exists, create if not exists
//      bool file_system::mk_time(const ::string & lpcszCandidate)
//      {
//         file_pointer spfile(e_create);
//         if(pcontext->m_papexcontext->file().exists(lpcszCandidate, get_application()))
//            return false;
//         try
//         {
//            if(spfile->open(lpcszCandidate, ::file::e_open_create | ::file::e_open_binary).failed())
//               return false;
//         }
//         catch(...)
//         {
//            return false;
//         }
//         return true;
//      }
//
//      string file_system::as_string(::payload payloadFile, ::aura::application *  papp)
//      {
//         ::payload varQuery;
//         return as_string(payloadFile, varQuery, papp);
//      }
//
//      string file_system::as_string(::payload payloadFile, ::payload & varQuery, ::aura::application *  papp)
//      {
//         memory storage;
//         if(payloadFile.cast < ::file::reader > () != nullptr)
//         {
//            storage.transfer_from(*payloadFile.cast < ::file::reader >());
//         }
//         else
//         {
//            string strFilePath(payloadFile);
//            if(papp->m_bZipIsDir && (::str::find_ci(".zip:", strFilePath) >= 0))
//            {
//               ::memory_file memfile(papp, &storage);
//               zip::InFile infile(this);
//               if(!infile.unzip_open(strFilePath, 0))
//                  return "";
//               if(!infile.dump(&memfile))
//                  return "";
//            }
//            else if(::str::begins_eat_ci(strFilePath, "file:///"))
//            {
//               as_memory(strFilePath, storage, papp);
//            }
//            else if(::str::begins_eat_ci(strFilePath, "file:\\\\\\"))
//            {
//               as_memory(strFilePath, storage, papp);
//            }
//            else if(::str::begins_ci(strFilePath, "http://")
//                    || ::str::begins_ci(strFilePath, "https://"))
//            {
//
//               if(varQuery.has_property("in_headers"))
//               {
//
//                  varQuery["headers"] = varQuery["in_headers"].propset();
//
//               }
//
//               varQuery.propset().set_app(pobject);
//
//               if(strFilePath.contains("/matter.ca2.software/") || strFilePath.contains(".matter.ca2.software/"))
//               {
//
//                  try
//                  {
//
//                     storage.transfer_from(*App(papp).file().get_file(strFilePath, ::file::e_open_binary | ::file::e_open_read));
//
//                  }
//                  catch(...)
//                  {
//
//                  }
//
//               }
//               else
//               {
//
//                  App(papp).http().get(strFilePath, storage, varQuery.propset());
//
//               }
//
//               varQuery["out_headers"] = varQuery["get_headers"];
//
//            }
//            else
//            {
//
//               as_memory(strFilePath, storage, papp);
//
//            }
//
//         }
//
//         string strResult;
//
//         if(storage.get_size() >= 2
//            && storage.get_data()[0] == 255
//            && storage.get_data()[1] == 60)
//         {
//            ::str::international::unicode_to_utf8(strResult, (const unichar *) &storage.get_data()[2], (i32)(storage.get_size() - 2));
//         }
//         else if(storage.get_size() >= 3
//                 && storage.get_data()[0] == 0xef
//                 && storage.get_data()[1] == 0xbb
//                 && storage.get_data()[2] == 0xbf)
//         {
//            strResult = string((const ::string &) (const unichar *) &storage.get_data()[3], (i32) (storage.get_size() - 3));
//         }
//         else
//         {
//            strResult = string((const ::string &) storage.get_data(), (i32) storage.get_size());
//         }
//
//         return strResult;
//      }
//
//      void file_system::as_memory(::payload payloadFile, memory_base & mem, ::aura::application *  papp)
//      {
//
//         mem.set_size(0);
//
//         if(payloadFile.get_type() == ::e_type_string)
//         {
//
//            string strPath = payloadFile.get_string();
//
//            if(strPath.is_empty())
//            {
//
//               TRACE("::file::file_system::as_memory payloadFile is a empty file name!!");
//
//               return;
//
//            }
//
//            strPath.trim("\"'");
//
//            if((::str::begins(strPath, "http://") || ::str::begins(strPath, "https://")))
//            {
//
//               property_set set;
//
//               App(papp).http().get(strPath, mem, set);
//
//               return;
//
//            }
//
//         }
//
//         file_pointer spfile;
//
//         try
//         {
//
//            spfile = App(papp).file().get_file(payloadFile, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_none);
//
//            mem.transfer_from(*spfile);
//
//         }
//         catch(...)
//         {
//         }
//
//
//
//      }
//
//      void file_system::lines(string_array & stra, ::payload payloadFile, ::aura::application *  papp)
//      {
//
//         __UNREFERENCED_PARAMETER(pobject);
//
//         ::file::text_buffer_pointer spfile(e_create);
//
//         try
//         {
//            if(spfile->open(payloadFile, ::file::e_open_text | ::file::e_open_read).failed())
//            {
//               return;
//            }
//         }
//         catch(...)
//         {
//            return;
//         }
//         string strLine;
//         while(spfile->read_string(strLine))
//         {
//            stra.add(strLine);
//         }
//
//      }
//
//      bool file_system::put_contents(::payload payloadFile, const void * pvoidContents, count count, ::aura::application *  papp)
//      {
//
//         file_pointer spfile;
//
//         spfile = App(papp).file().get_file(payloadFile, ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_share_deny_none | ::file::e_open_defer_create_directory);
//
//         if(spfile.is_null())
//            return false;
//
//         spfile->write(pvoidContents, count);
//
//         return true;
//
//      }
//
//      bool file_system::put_contents(::payload payloadFile, const ::string & lpcszContents, ::aura::application *  papp)
//      {
//         if(lpcszContents == nullptr)
//         {
//            return put_contents(payloadFile, "", 0, papp);
//         }
//         else
//         {
//            return put_contents(payloadFile, lpcszContents, strlen(lpcszContents), papp);
//         }
//      }
//
//      bool file_system::put_contents(::payload payloadFile, ::file::reader & reader, ::aura::application *  papp)
//      {
//         file_pointer spfile;
//         spfile = App(papp).file().get_file(payloadFile, ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_share_deny_none | ::file::e_open_defer_create_directory);
//         if(spfile.is_null())
//            return false;
//         memory mem;
//         mem.set_size(1024 * 1024 * 8);
//         memsize uRead;
//         while((uRead = reader.read(mem.get_data(), mem.get_size())) > 0)
//         {
//            spfile->write(mem.get_data(), uRead);
//         }
//         return true;
//      }
//
//      bool file_system::put_contents(::payload payloadFile, memory & mem, ::aura::application *  papp)
//      {
//         return put_contents(payloadFile, mem.get_data(), (count) mem.get_size(), papp);
//      }
//
//      bool file_system::put_text_utf8(::payload payloadFile, const ::string & lpcszContents, ::aura::application *  papp)
//      {
//         file_pointer spfile;
//         spfile = App(papp).file().get_file(payloadFile, ::file::e_open_binary | ::file::e_open_write | ::file::e_open_create | ::file::e_open_share_deny_none | ::file::e_open_defer_create_directory);
//         if(spfile.is_null())
//            return false;
//
//         string str("\xef\xbb\xbf");
//         spfile->write(str, str.length());
//
//         spfile->write(lpcszContents, strlen(lpcszContents));
//         return true;
//      }
//
//      void file_system::path::split(string_array & stra, const ::string & lpcszPath)
//      {
//         string_array straSeparator;
//         straSeparator.add("\\");
//         straSeparator.add("/");
//         stra.add_smallest_tokens(lpcszPath, straSeparator, false);
//      }
//
//      class file_system::path & file_system::path()
//      {
//         return m_path;
//      }
//
//
//      string file_system::title_(const ::string & path)
//      {
//
//         string str = name_(path);
//
//         strsize iPos = str.reverse_find('.');
//
//         if(iPos >= 0)
//         {
//            return str.Mid(0, iPos);
//         }
//         else
//         {
//            return str;
//         }
//
//      }
//
//
//      string file_system::name_(const ::string & path)
//      {
//
//         string str(path);
//
//         while(::str::ends_eat(str, "\\"));
//
//         while(::str::ends_eat(str, "/"));
//
//         strsize iPos;
//
//         strsize iPos1 = str.reverse_find('\\');
//
//         strsize iPos2 = str.reverse_find('/');
//
//         if(iPos1 >= 0 && iPos2 >= 0)
//         {
//
//            if(iPos1 > iPos2)
//            {
//
//               iPos = iPos1 + 1;
//
//            }
//            else
//            {
//
//               iPos = iPos2 + 1;
//
//            }
//
//         }
//         else if(iPos1 >= 0)
//         {
//
//            iPos = iPos1 + 1;
//
//         }
//         else if(iPos2 >= 0)
//         {
//
//            iPos = iPos2 + 1;
//
//         }
//         else
//         {
//
//            iPos = 0;
//
//         }
//
//         return str.Mid(iPos);
//
//      }
//
//      string file_system::extension(const ::string & path)
//      {
//
//         string str = name_(path);
//
//         strsize iPos = str.reverse_find('.');
//
//         if(iPos >= 0)
//         {
//
//            return str.Mid(iPos + 1);
//
//         }
//         else
//         {
//
//            return "";
//
//         }
//
//      }
//
//      void file_system::copy(const ::string & pszNew, const ::string & psz, bool bFailIfExists, e_extract eextract, ::aura::application *  papp)
//      {
//         if(bFailIfExists)
//         {
//            if(exists(pszNew, papp))
//               __throw(::exception("Failed to copy file"));
//         }
//         if(pcontext->m_papexcontext->dir().is(psz, papp) && (eextract == extract_first || eextract == extract_all || !(::str::ends_ci(psz, ".zip"))))
//         {
//            string_array straPath;
//            pcontext->m_papexcontext->dir().rls(papp, psz, &straPath);
//            string strDst;
//            string strSrc;
//            string strDirSrc(psz);
//            string strDirDst(pszNew);
//            if(papp->m_bZipIsDir && (::str::ends(strDirSrc, ".zip")))
//            {
//               strDirSrc += ":";
//            }
//            for(i32 i = 0; i < straPath.get_size(); i++)
//            {
//               strSrc = straPath[i];
//               strDst = strSrc;
//               ::str::begins_eat_ci(strDst, strDirSrc);
//               strDst = pcontext->m_papexcontext->dir().path(strDirDst, strDst);
//               if(pcontext->m_papexcontext->dir().is(strSrc, papp))
//               {
//                  if((eextract == extract_first || eextract == extract_none) && (::str::ends_ci(psz, ".zip")))
//                  {
//                  }
//                  else
//                  {
//                     pcontext->m_papexcontext->dir().create(strDst, papp);
//                  }
//               }
//               else
//               {
//                  if(!pcontext->m_papexcontext->dir().is(pcontext->m_papexcontext->dir().name(strDst), papp))
//                  {
//                     pcontext->m_papexcontext->dir().create(pcontext->m_papexcontext->dir().name(strDst), papp);
//                  }
//                  copy(strDst, strSrc, bFailIfExists, eextract == extract_all ? extract_all : extract_none, papp);
//               }
//            }
//         }
//         else
//         {
//
//            string strNew;
//
//            if(pcontext->m_papexcontext->dir().is(pszNew, papp))
//            {
//               strNew = pcontext->m_papexcontext->dir().path(pszNew, name_(psz));
//            }
//            else
//            {
//               strNew = pszNew;
//            }
//
//            file_pointer ofile;
//            ofile = App(papp).file().get_file(strNew, ::file::e_open_write | ::file::e_open_binary | ::file::e_open_create | ::file::e_open_defer_create_directory | ::file::e_open_share_deny_write);
//            if(ofile.is_null())
//            {
//               string strError;
//               strError.format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open output file", psz, pszNew, bFailIfExists);
//               __throw(strError);
//            }
//
//            file_pointer ifile;
//            ifile = App(papp).file().get_file(psz, ::file::e_open_read | ::file::e_open_binary | ::file::e_open_share_deny_none);
//            if(ifile.is_null())
//            {
//               string strError;
//               strError.format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open input file", psz, pszNew, bFailIfExists);
//               __throw(strError);
//            }
//
//            ::file::output_stream ostream(ofile);
//
//            ::file::input_stream istream(ifile);
//
//            psystem->compress().null(ostream, istream);
//
//
//
//            bool bOutputFail = false;
//            bool bInputFail = false;
//            try
//            {
//               ofile->close();
//            }
//            catch(...)
//            {
//               bOutputFail = true;
//            }
//
//            ::file::file_status st;
//
//            ifile->GetStatus(st);
//
//            pcontext->m_papexcontext->os().set_file_status(strNew, st);
//
//            try
//            {
//               ifile->close();
//            }
//            catch(...)
//            {
//               bInputFail = true;
//            }
//            if(bInputFail)
//            {
//               if(bOutputFail)
//               {
//                  string strError;
//                  strError.format("During copy, failed to close both input file \"%s\" and output file \"%s\" bFailIfExists=%d", psz, pszNew, bFailIfExists);
//                  __throw(strError);
//               }
//               else
//               {
//                  string strError;
//                  strError.format("During copy, failed to close input file \"%s\" bFailIfExists=%d", psz, bFailIfExists);
//                  __throw(strError);
//               }
//            }
//            else if(bOutputFail)
//            {
//               string strError;
//               strError.format("During copy, failed to close output file \"%s\" bFailIfExists=%d", pszNew, bFailIfExists);
//               __throw(strError);
//            }
//
//         }
//
//      }
//
//      void file_system::move(const ::string & pszNew, const ::string & psz)
//      {
//#ifdef WINDOWS_DESKTOP
//         if(!::MoveFileW(
//                         ::str::international::utf8_to_unicode(psz),
//                         ::str::international::utf8_to_unicode(pszNew)))
//         {
//            u32 dwError = ::get_last_error();
//            string strError;
//            strError.format("Failed to move file \"%s\" to \"%s\" error=%d", psz, pszNew, dwError);
//            __throw(strError);
//         }
//#elif defined(_UWP)
//
//         ::winrt::Windows::Storage::StorageFile ^ file = get_os_file(psz,  0, 0, nullptr, OPEN_EXISTING, 0, nullptr);
//
//         if(file == nullptr)
//            __throw(::exception("file::file_system::move Could not move file, could not open source file"));
//
//         string strDirOld     = pcontext->m_papexcontext->dir().name(psz);
//         string strDirNew     = pcontext->m_papexcontext->dir().name(pszNew);
//         string strNameOld    = pcontext->m_papexcontext->file().name_(psz);
//         string strNameNew    = pcontext->m_papexcontext->file().name_(pszNew);
//
//         if(strDirOld == strDirNew)
//         {
//            if(strNameOld == strNameNew)
//            {
//               return;
//            }
//            else
//            {
//               ::wait(file->RenameAsync(strNameNew));
//            }
//         }
//         else
//         {
//            ::winrt::Windows::Storage::StorageFolder ^ folder = get_os_folder(strDirNew);
//            if(strNameOld == strNameNew)
//            {
//               ::wait(file->MoveAsync(folder));
//            }
//            else
//            {
//               ::wait(file->MoveAsync(folder, strNameNew));
//            }
//         }
//
//
//#else
//         if(rename(psz, pszNew) != 0)
//         {
//            i32 err = errno;
//            string strError;
//            strError.format("Failed to delete file error=%d", err);
//            __throw(strError);
//         }
//#endif
//      }
//
//      void file_system::del(const ::string & psz)
//      {
//#ifdef WINDOWS
//         if(!::DeleteFileW(
//                           ::str::international::utf8_to_unicode(psz)))
//         {
//            u32 dwError = ::get_last_error();
//            if(dwError == 2) // the file does not exist, so delete "failed"
//               return;
//            string strError;
//            strError.format("Failed to delete file \"%s\" error=%d", psz, dwError);
//            __throw(strError);
//         }
//#else
//         if(erase(psz) != 0)
//         {
//            i32 err = errno;
//            string strError;
//            strError.format("Failed to delete file error=%d", err);
//            __throw(strError);
//         }
//#endif
//
//      }
//
//
//      string file_system::copy(const ::string & psz, ::aura::application *  papp)
//      {
//         string strCopy("copy");
//         string strNew;
//         if(pcontext->m_papexcontext->dir().is(psz, papp))
//         {
//            i32 i = 1;
//            while( i <= 100)
//            {
//               strNew.format("%s-%s-%d", psz, strCopy.c_str(), i);
//               if(!exists(strNew, papp))
//               {
//                  copy(strNew, psz, false, extract_all, papp);
//                  return strNew;
//               }
//               i++;
//            }
//         }
//         else
//         {
//            string strExt = extension(psz);
//            if(!strExt.is_empty())
//            {
//               strExt = "-" + strExt;
//            }
//            i32 i = 1;
//            while( i <= 100)
//            {
//               strNew.format("%s-%s-%d%s", psz, strCopy.c_str(), i, strExt.c_str());
//               if(!exists(strNew, papp))
//               {
//                  copy(strNew, psz, false, extract_all, papp);
//                  return strNew;
//               }
//               i++;
//            }
//         }
//         return "";
//      }
//
//
//      bool file_system::exists(const ::string & pszPath, ::aura::application *  papp)
//      {
//
//         if(::str::begins_ci_iws(pszPath, "uifs://"))
//         {
//            return AppUser(pobject).m_pifs->m_psystem->m_pacmefile->exists(pszPath);
//         }
//         else if(::str::begins_ci_iws(pszPath, "http://") || ::str::begins_ci_iws(pszPath, "https://"))
//         {
//
//            property_set set;
//
//            return App(papp).http().exists(pszPath, set);
//
//         }
//
//         if(papp->m_bZipIsDir)
//         {
//
//            strsize iFind = ::str::find_ci(".zip:", pszPath);
//
//            zip::Util ziputil;
//
//            if(iFind >= 0)
//               return ziputil.exists(papp, pszPath);
//
//            if(!Sys(papp).dir().name_is(pszPath, papp))
//               return false;
//
//         }
//
//#ifdef WINDOWS
//
//
//         return m_psystem->m_pacmefile->exists(pszPath);
//
//         //return ::windows_get_file_attributes(::str::international::utf8_to_unicode(pszPath)) != INVALID_FILE_ATTRIBUTES;
//
//#else
//
//         struct stat st;
//
//         if(stat(pszPath, &st) != 0)
//            return false;
//
//         return S_ISREG(st.st_mode) || S_ISDIR(st.st_mode);
//
//#endif
//
//      }
//
//
//      bool file_system::exists(const ::string & strPath, ::aura::application *  papp)
//      {
//
//         if(::str::begins_ci_iws(strPath, "uifs://"))
//         {
//            return AppUser(pobject).m_pifs->m_psystem->m_pacmefile->exists(strPath);
//         }
//
//         if(::str::begins_ci_iws(strPath, "http://")
//            || ::str::begins_ci_iws(strPath, "https://"))
//         {
//
//            property_set set;
//
//            return App(papp).http().exists(strPath, set);
//
//         }
//
//
//         if(papp->m_bZipIsDir)
//         {
//
//            strsize iFind = ::str::find_ci(".zip:", strPath);
//
//            zip::Util ziputil;
//
//            if(iFind >= 0)
//            {
//
//               if(!exists(strPath.Mid(0, iFind + 4), papp))
//                  return false;
//
//               return ziputil.exists(papp, strPath);
//
//            }
//
//
//         }
//
//         //if(!papp->m_psystem->dir().name_is(strPath, papp))
//         // return false;
//
//#ifdef WINDOWS
//
//
//         return m_psystem->m_pacmefile->exists(strPath);
//         // return true;
//
//         //return App(papp).m_spfsdata->m_psystem->m_pacmefile->exists(strPath);
//         //return ::windows_get_file_attributes(::str::international::utf8_to_unicode(strPath)) != INVALID_FILE_ATTRIBUTES;
//
//#else
//
//         struct stat st;
//
//         if(stat(strPath, &st) != 0)
//            return false;
//
//         return S_ISREG(st.st_mode) || S_ISDIR(st.st_mode);
//
//#endif
//
//      }
//
//      string file_system::paste(const ::string & pszLocation, const ::string & path, ::aura::application *  papp)
//      {
//         string strDir = pcontext->m_papexcontext->dir().name(path);
//         string strDest = pcontext->m_papexcontext->dir().path(pszLocation, "");
//         string strSrc = pcontext->m_papexcontext->dir().path(strDir, "");
//         if(strDest == strSrc)
//         {
//            return copy(path, papp);
//         }
//         else
//         {
//            string strNew = pcontext->m_papexcontext->dir().path(strDest, name_(path));
//            copy(strNew, path, false, extract_all, papp);
//            return strNew;
//         }
//      }
//
//      void file_system::trash_that_is_not_trash(string_array & stra, ::aura::application *  papp)
//      {
//
//         if(stra.get_size() <= 0)
//            return;
//
//         string strDir = pcontext->m_papexcontext->dir().trash_that_is_not_trash(stra[0]);
//
//         pcontext->m_papexcontext->dir().create(strDir, papp);
//
//         for(i32 i = 0; i < stra.get_size(); i++)
//         {
//#ifdef WINDOWS
//            move(pcontext->m_papexcontext->dir().path(strDir, name_(stra[i])), stra[i]);
//#else
//            ::rename(stra[i], pcontext->m_papexcontext->dir().path(strDir, name_(stra[i])));
//#endif
//         }
//
//      }
//
//      void file_system::trash_that_is_not_trash(const ::string & psz, ::aura::application *  papp)
//      {
//
//         string strDir = pcontext->m_papexcontext->dir().trash_that_is_not_trash(psz);
//
//         pcontext->m_papexcontext->dir().create(strDir, papp);
//
//#ifdef WINDOWS
//         //         ::MoveFile(psz, pcontext->m_papexcontext->dir().path(strDir, name_(psz)));
//         move(pcontext->m_papexcontext->dir().path(strDir, name_(psz)), psz);
//#else
//         ::rename(psz, pcontext->m_papexcontext->dir().path(strDir, name_(psz)));
//#endif
//
//      }
//
//      void file_system::replace(const ::string & pszContext, const ::string & pszFind, const ::string & pszReplace, ::aura::application *  papp)
//      {
//         string_array straTitle;
//         pcontext->m_papexcontext->dir().ls(papp, pszContext, nullptr, &straTitle);
//         string strOld;
//         string strNew;
//         for(i32 i = 0; i < straTitle.get_size(); i++)
//         {
//            strOld = straTitle[i];
//            strNew = strOld;
//            strNew.replace(pszFind, pszReplace);
//            if(strNew != strOld)
//            {
//#ifdef WINDOWS
//               //               ::MoveFileW(
//               //                ::str::international::utf8_to_unicode(pcontext->m_papexcontext->dir().path(pszContext, strOld)),
//               //              ::str::international::utf8_to_unicode(pcontext->m_papexcontext->dir().path(pszContext, strNew)));
//               move(pcontext->m_papexcontext->dir().path(pszContext, strNew), pcontext->m_papexcontext->dir().path(pszContext, strOld));
//#else
//               ::rename(
//                        pcontext->m_papexcontext->dir().path(pszContext, strOld),
//                        pcontext->m_papexcontext->dir().path(pszContext, strNew));
//#endif
//            }
//         }
//      }
//
//      bool file_system::is_read_only(const ::string & psz)
//      {
//
//#ifdef WINDOWS_DESKTOP
//
//         u32 dwAttrib = windows_get_file_attributes(::str::international::utf8_to_unicode(psz));
//         if(dwAttrib & FILE_ATTRIBUTE_READONLY)
//            return true;
//         return false;
//
//#elif defined(_UWP)
//
//         __throw(todo);
//
//#else
//
//         struct stat st;
//
//         if(stat(psz, &st) != 0)
//            return true;
//
//         return !(st.st_mode & S_IWUSR);
//
//#endif
//
//      }
//
//      string file_system::sys_temp(const ::string & pszName, const ::string & pszExtension, ::aura::application *  papp)
//      {
//
//         string strTempDir = get_sys_temp_path();
//
//         if(!::str::ends(strTempDir, "\\") && !::str::ends(strTempDir, "/"))
//         {
//
//            strTempDir += "\\";
//
//         }
//
//         string str;
//
//         char buf[30];
//
//         for(i32 i = 0; i < 1000; i++)
//         {
//
//            sprintf(buf, "%d", i);
//
//            str = strTempDir;
//            str += pszName;
//            str += "-";
//            str += buf;
//            str += ".";
//            str += pszExtension;
//            if(!exists(str, papp))
//               return str;
//         }
//
//         return "";
//
//      }
//
//      string file_system::sys_temp_unique(const ::string & pszName)
//      {
//
//         return pcontext->m_papexcontext->dir().path(get_sys_temp_path(), pszName);
//
//      }
//
//      file_pointer file_system::time_square_file(::aura::application *  papp, const ::string & pszPrefix, const ::string & pszSuffix)
//      {
//
//         return get(time_square(papp, pszPrefix, pszSuffix), papp);
//
//      }
//
//      file_pointer file_system::get(const ::string & name, ::aura::application *  papp)
//      {
//
//         pcontext->m_papexcontext->dir().create(pcontext->m_papexcontext->dir().name(name), papp);
//
//         file_pointer fileOut = App(papp).file().get_file(name, ::file::e_open_create | ::file::e_open_binary | ::file::e_open_write);
//
//         if(fileOut.is_null())
//            __throw(::file::exception(-1, ::file::exception::none, name));
//
//         return fileOut;
//
//      }
//
//      string file_system::replace_extension(const ::string & pszFile, const ::string & pszExtension)
//      {
//         string strFile(pszFile);
//         set_extension(strFile, pszExtension);
//         return strFile;
//      }
//
//      void file_system::set_extension(string & strFile, const ::string & pszExtension)
//      {
//         strsize iEnd = strFile.reverse_find('.');
//         if(iEnd < 0)
//            iEnd = strFile.get_length();
//         strFile = strFile.Left(iEnd) + ::str::has_char(pszExtension, ".");
//      }

      file_pointer file_system::get_file(::payload payloadFile,::u32 nOpenFlags,::extended::status * pfesp,::aura::application * papp)
      {

         file_pointer spfile;

         spfile = ::file::axis::system::get_file(payloadFile,nOpenFlags,pfesp,papp);

         if(spfile.is_set())
         {

            return spfile;

         }

         spfile = ::ios::file_system::get_file(payloadFile,nOpenFlags,pfesp,papp);

         if(spfile.is_set())
         {

            return spfile;

         }

         return nullptr;

      }



   } // namespace axis


} // namespace macos










