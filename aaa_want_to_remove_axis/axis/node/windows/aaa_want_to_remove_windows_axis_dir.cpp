#include "framework.h"
//#include "windows.h"


//namespace windows
//{
//
//
//   namespace axis
//   {
//
//
//      dir::dir(::object * pobject) :
//         ::object(pobject),
//         ::file::dir::system(pobject),
//         ::file::dir::axis::system(pobject),
//         ::windows::dir(pobject)
//      {
//
//      }
//
//
//      ::file::listing & dir::ls(::object * pobject, ::file::listing & listing)
//      {
//
//         if(::file::dir::axis::system::ls(pobject,listing).succeeded())
//         {
//
//            return listing;
//
//         }
//
//         listing.m_statusresult.clear();
//
//         return ::windows::dir::ls(pobject,listing);
//
//      }
//
//
//      ::file::listing & dir::ls_relative_name(::object * pobject, ::file::listing & listing)
//      {
//
//         if (::file::dir::axis::system::ls_relative_name(pobject, listing).succeeded())
//         {
//
//            return listing;
//
//         }
//
//         return ::windows::dir::ls_relative_name(pobject, listing);
//
//      }
//
//
//      bool dir::is_impl(const ::file::path & path,::object * pobject)
//      {
//
//         if (::file::dir::axis::system::is_impl(path, pobject))
//         {
//
//            return true;
//
//         }
//
//         if (::windows::dir::is_impl(path, pobject))
//         {
//
//            return true;
//
//         }
//
//         return false;
//
//      }
//
//
////      bool dir::name_is(const ::file::path & str,::object * pobject)
////      {
////         //output_debug_string(str);
////         strsize iLast = str.get_length() - 1;
////         while(iLast >= 0)
////         {
////            if(str.m_pdata[iLast] != '\\' && str.m_pdata[iLast] != '/' && str.m_pdata[iLast] != ':')
////               break;
////            iLast--;
////         }
////         while(iLast >= 0)
////         {
////            if(str.m_pdata[iLast] == '\\' || str.m_pdata[iLast] == '/' || str.m_pdata[iLast] == ':')
////               break;
////            iLast--;
////         }
////         if(iLast >= 0)
////         {
////            while(iLast >= 0)
////            {
////               if(str.m_pdata[iLast] != '\\' && str.m_pdata[iLast] != '/' && str.m_pdata[iLast] != ':')
////               {
////                  iLast++;
////                  break;
////               }
////               iLast--;
////            }
////         }
////         else
////         {
////            return true; // assume empty string is root_ones directory
////         }
////
////
////         bool bIsDir;
////
////
////         //u32 uiLastError;
////
////         //if(m_isdirmap.lookup(str, bIsDir, uiLastError, (i32) iLast))
////         //{
////         //   if(!bIsDir)
////         //   {
////         //      ::set_last_error(uiLastError);
////         //   }
////         //   return bIsDir;
////         //}
////
////
////         if(::thread_set(id_thread_zip_is_dir) && iLast >= 3 && !ansi_count_compare_ci(&((const char *)str)[iLast - 3],".zip",4))
////         {
////            //            m_isdirmap.set(str.Left(iLast + 1), true, 0);
////            return true;
////         }
////
////         strsize iFind = ::str::find_file_extension("zip:", str, 0, iLast);
////
////         if(::thread_set(id_thread_zip_is_dir) && iFind >= 0 && iFind < iLast)
////         {
////            bool bHasSubFolder;
////            //if(m_isdirmap.lookup(str, bHasSubFolder, uiLastError))
////            //{
////            //   if(!bHasSubFolder)
////            //   {
////            //      ::set_last_error(uiLastError);
////            //   }
////            //   return bHasSubFolder;
////            //}
////            bHasSubFolder = m_pziputil->has_sub_folder(pobject, str);
//////            m_isdirmap.set(str.Left(iLast + 1), bHasSubFolder, bHasSubFolder ? 0 : ::get_last_error());
////            return bHasSubFolder;
////         }
////
////
////         wstring wstrPath;
////
////         //strsize iLen = ::str::international::utf8_to_unicode_count(str, iLast + 1);
////
////         //wstrPath.alloc(iLen + 32);
////
////         wstrPath = ::str::international::utf8_to_unicode(str, iLast + 1);
////
////         //output_debug_string(wstrPath);
////
////         if(wstrPath.get_length() >= MAX_PATH)
////         {
////            if(::str::begins(wstrPath, L"\\\\"))
////            {
////               ::str::begin(wstrPath, L"\\\\?\\UNC");
////            }
////            else
////            {
////               ::str::begin(wstrPath, L"\\\\?\\");
////            }
////         }
////         DWORD dwAttrib;
////         dwAttrib = windows_get_file_attributes(wstrPath);
////         /*if(dwAttrib == INVALID_FILE_ATTRIBUTES)
////         {
////            dwAttrib = GetFileAttributes(strPath);
////         }*/
////
////         bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
////
//////         m_isdirmap.set(str.Left(iLast + 1), bIsDir, bIsDir ? 0 : ::get_last_error());
////
////         return bIsDir;
////      }
//
//
//      //string dir::time(const char * pcsz, const char * lpcsz2)
//
//      //{
//      //   return path(m_strTimeFolder, pcsz, lpcsz2);
//
//      //}
//
//      //string dir::stage(const char * pcsz, const char * lpcsz2)
//
//      //{
//      //   return path(element("stage"), pcsz, lpcsz2);
//
//      //}
//
//      //string dir::stageapp(const char * pcsz, const char * lpcsz2)
//
//      //{
//      //   return path(stage("basis", pcsz), lpcsz2);
//
//      //}
//
//      //string dir::netseed(const char * pcsz, const char * lpcsz2)
//
//      //{
//      //   return path(m_strNetSeedFolder, pcsz, lpcsz2);
//
//      //}
//
//      //// stage in ca2os spalib
//      //string dir::install(const char * pcsz, const char * lpcsz2)
//
//      //{
//      //
//      //   single_lock sl(&m_mutex, true);
//
//      //   return path(m_strCa2, pcsz, lpcsz2);
//
//
//      //}
//
//      //string dir::install(const string & str, const char * pcsz2)
//
//      //{
//      //
//      //   single_lock sl(&m_mutex, true);
//
//      //   return path(m_strCa2, str, pcsz2);
//
//
//      //}
//
//      //string dir::install(const char * pcsz, const string & str2)
//
//      //{
//      //
//      //   single_lock sl(&m_mutex, true);
//
//      //   return path(m_strCa2, pcsz, str2);
//
//
//      //}
//
//      //string dir::install(const string & str, const string & str2)
//      //{
//      //
//      //   single_lock sl(&m_mutex, true);
//
//      //   return path(m_strCa2, str, str2);
//
//      //}
//
//      //string dir::install(const string & str)
//      //{
//      //
//      //   single_lock sl(&m_mutex, true);
//
//      //   return path(m_strCa2, str);
//
//      //}
//
//      //string dir::install()
//      //{
//      //
//      //   single_lock sl(&m_mutex, true);
//
//      //   return m_strCa2;
//
//      //}
//
//
//      //string dir::module(const char * pcsz, const char * lpcsz2)
//
//      //{
//      //   string str = System.get_module_folder();
//      //   return path(str, pcsz, lpcsz2);
//
//      //}
//
//      //string dir::ca2module(const char * pcsz, const char * lpcsz2)
//
//      //{
//      //   string str = System.get_ca2_module_folder();
//      //   return path(str, pcsz, lpcsz2);
//
//      //}
//
//
//      //void dir::time_square(string &str)
//      //{
//      //   str = time("time");
//      //}
//
//      //string dir::time_log(const char * pszId)
//      //{
//      //   string strLogBaseDir;
//      //   strLogBaseDir = appdata("log");
//      //   return path(strLogBaseDir, pszId);
//      //}
//
//      //bool dir::mk(const char * pcsz, ::object * pobject)
//
//      //{
//
//      //   if(is(pcsz, papp))
//
//      //      return true;
//
//      //   string_array stra;
//      //   Context.file().get_ascendants_path(pcsz, stra);
//
//      //   for(i32 i = 0; i < stra.get_size(); i++)
//      //   {
//      //
//      //      string strDir = stra[i];
//
//      //      if(!is(strDir, papp))
//      //      {
//      //
//      //         if(::CreateDirectoryW(::str::international::utf8_to_unicode("\\\\?\\" + strDir), nullptr))
//      //         {
//
//      //            m_isdirmap.set(strDir, true, 0);
//
//      //         }
//      //         else
//      //         {
//
//      //            DWORD dwError = ::get_last_error();
//
//      //            if (dwError == ERROR_ALREADY_EXISTS)
//      //            {
//
//      //               if (::dir::is(strDir))
//      //               {
//      //                  m_isdirmap.set(strDir, true, 0);
//      //               }
//      //               else
//      //               {
//      //                  string str;
//      //                  str = "\\\\?\\" + strDir;
//      //                  str.trim_right("\\/");
//      //                  try
//      //                  {
//      //                     Context.file().del(str);
//      //                  }
//      //                  catch (...)
//      //                  {
//      //                  }
//      //                  str = stra[i];
//      //                  str.trim_right("\\/");
//      //                  try
//      //                  {
//      //                     Context.file().del(str);
//      //                  }
//      //                  catch (...)
//      //                  {
//      //                  }
//      //                  if (::CreateDirectoryW(::str::international::utf8_to_unicode("\\\\?\\" + stra[i]), nullptr))
//      //                  {
//      //                     m_isdirmap.set(stra[i], true, 0);
//      //                     goto try1;
//      //                  }
//      //                  else
//      //                  {
//      //                     dwError = ::get_last_error();
//      //                  }
//      //               }
//      //               char * pszError;
//      //               FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (LPTSTR)&pszError, 8, nullptr);
//
//      //               //TRACE("dir::mk CreateDirectoryW last error(%d)=%s", dwError, pszError);
//      //               ::LocalFree(pszError);
//      //               //m_isdirmap.set(stra[i], false);
//      //            }
//      //         }
//      //         try1:
//      //
//      //         if(!is(stra[i], papp))
//      //         {
//      //            return false;
//      //         }
//      //
//      //      }
//      //   }
//      //   return true;
//      //}
//
//      //bool dir::rm(::object * pobject, const char * psz, bool bRecursive)
//      //{
//      //   if(bRecursive)
//      //   {
//      //      ::file::patha patha;
//      //      ::file::patha straTitle;
//      //      ls(papp, psz, &patha, &straTitle);
//      //      for(i32 i = 0; i < patha.get_count(); i++)
//      //      {
//      //         if(is(patha[i], papp))
//      //         {
//      //            rm(papp, path(psz, straTitle[i]), true);
//      //         }
//      //         else
//      //         {
//      //            ::DeleteFile(patha[i]);
//      //         }
//      //      }
//      //   }
//      //   return RemoveDirectory(psz) != FALSE;
//      //}
//
//
//      //string dir::name(const char * path1)
//      //{
//      //   const char * psz = path1 + strlen(path1) - 1;
//      //   while(psz >= path1)
//      //   {
//      //      if(*psz != '\\' && *psz != '/' && *psz != ':')
//      //         break;
//      //      psz--;
//      //   }
//      //   while(psz >= path1)
//      //   {
//      //      if(*psz == '\\' || *psz == '/' || *psz == ':')
//      //         break;
//      //      psz--;
//      //   }
//      //   if(psz >= path1) // strChar == "\\" || strChar == "/"
//      //   {
//      //      const char * pszEnd = psz;
//      //      /*while(psz >= path1)
//      //      {
//      //         if(*psz != '\\' && *psz != '/' && *psz != ':')
//      //            break;
//      //         psz--;
//      //      }*/
//      //      return string(path1, pszEnd - path1 + 1);
//      //   }
//      //   else
//      //   {
//      //      return "";
//      //   }
//      //}
//
//      //string dir::name(const string & str)
//      //{
//      //
//      //   strsize iLast = str.get_length() - 1;
//
//      //   while(iLast >= 0)
//      //   {
//      //      if(str.m_pdata[iLast] != '\\' && str.m_pdata[iLast] != '/' && str.m_pdata[iLast] != ':')
//      //         break;
//      //      iLast--;
//      //   }
//      //   while(iLast >= 0)
//      //   {
//      //      if(str.m_pdata[iLast] == '\\' || str.m_pdata[iLast] == '/' || str.m_pdata[iLast] == ':')
//      //         break;
//      //      iLast--;
//      //   }
//      //   if(iLast >= 0)
//      //   {
//      //      while(iLast >= 0)
//      //      {
//      //         if(str.m_pdata[iLast] != '\\' && str.m_pdata[iLast] != '/' && str.m_pdata[iLast] != ':')
//      //            break;
//      //         iLast--;
//      //      }
//      //      return str.Left(iLast + 1);
//      //   }
//      //   else
//      //   {
//      //      return "";
//      //   }
//      //}
//
//
//      //class ::file::path & dir::path()
//      //{
//      //   return m_path;
//      //}
//
//
//      bool dir::initialize()
//      {
//
//         if(!::windows::dir::initialize())
//            return false;
//
//
////         string strCa2Module = ca2module();
////
////         m_strCa2 = strCa2Module;
////
////#ifndef CUBE
////
////         Context.file().path().eat_end_level(m_strCa2, 2, "\\");
////
////#endif
////
////         SHGetSpecialFolderPath(
////            nullptr,
////            m_strCommonAppData,
////            CSIDL_COMMON_APPDATA,
////            FALSE);
////         SHGetSpecialFolderPath(
////            nullptr,
////            m_strProfile,
////            CSIDL_PROFILE,
////            FALSE);
////         SHGetSpecialFolderPath(
////            nullptr,
////            m_strAppData,
////            CSIDL_APPDATA,
////            FALSE);
////         SHGetSpecialFolderPath(
////            nullptr,
////            m_strPrograms,
////            CSIDL_PROGRAMS,
////            FALSE);
////         SHGetSpecialFolderPath(
////            nullptr,
////            m_strCommonPrograms,
////            CSIDL_COMMON_PROGRAMS,
////            FALSE);
////
////      xml::document doc(get_object());
////
////      doc.load(Context.file().as_string(appdata("configuration\\directory.xml"),get_context_application()));
////
////      xxdebug_box("win_dir::initialize (configuration)", "win_dir::initialize", 0);
////      if(doc.get_name() == "directory_configuration")
////      {
////
////         m_strTimeFolder = doc.get_child_value("time");
////
////         m_strNetSeedFolder = doc.get_child_value("netseed");
////
////      }
////      if(m_strTimeFolder.is_empty())
////         m_strTimeFolder = appdata("time");
////
////      if(m_strNetSeedFolder.is_empty())
////         m_strNetSeedFolder = element("net");
////
////      mk(m_strTimeFolder, get_context_application());
////      xxdebug_box("win_dir::initialize (m_strTimeFolder)", "win_dir::initialize", 0);
////
////      if(!is(m_strTimeFolder, get_context_application()))
////         return false;
////
////      mk(path(m_strTimeFolder, "time"), get_context_application());
////      xxdebug_box("win_dir::initialize", "win_dir::initialize", 0);
//         return true;
//
//      }
//
////   string dir::trash_that_is_not_trash(const char * psz)
////   {
////      if(psz == nullptr)
////         return "";
////
////      if(psz[1] == ':')
////      {
////         string strDir = name(psz);
////         string str;
////         str = strDir.Left(2);
////         str += "\\trash_that_is_not_trash\\";
////         string strFormat;
////         ::datetime::time time;
////         time = ::datetime::time::get_current_time();
////         strFormat.Format("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
////         str += strFormat;
////         if(strDir.m_pdata[2] == '\\')
////         {
////            str += strDir.Mid(3);
////         }
////         else
////         {
////            str += strDir.Mid(2);
////         }
////         return str;
////      }
////
////      return "";
////   }
////
////   string dir::appdata(const char * pcsz, const char * lpcsz2)
//
////   {
////      string str;
////      str = m_strAppData;
////
////      string strRelative;
////      strRelative = install();
////      index iFind = strRelative.find(':');
////      if(iFind >= 0)
////      {
////         strsize iFind1 = strRelative.reverse_find("\\", iFind);
////         strsize iFind2 = strRelative.reverse_find("/", iFind);
////         strsize iStart = MAX(iFind1 + 1, iFind2 + 1);
////         strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart, iFind - iStart) + strRelative.Mid(iFind + 1);
////      }
////      return path(path(str, "ca2", strRelative), pcsz, lpcsz2);
//
////   }
////
////
////   string dir::commonappdata(const char * pcsz,const char * lpcsz2)
//
////   {
////
////      string str;
////
////      str = m_strCommonAppData;
////
////      return element_commonappdata(install(), pcsz, lpcsz2);
//
////
////   }
////
////
////   string dir::element_commonappdata(const string & strElement, const char * pcsz,const char * lpcsz2)
//
////   {
////
////      string strRelative;
////
////      strRelative = strElement;
////
////      index iFind = strRelative.find(':');
////
////      if(iFind >= 0)
////      {
////
////         strsize iFind1 = strRelative.reverse_find("\\",iFind);
////
////         strsize iFind2 = strRelative.reverse_find("/",iFind);
////
////         strsize iStart = MAX(iFind1 + 1,iFind2 + 1);
////
////         strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart,iFind - iStart) + strRelative.Mid(iFind + 1);
////
////      }
////
////      return path(path(m_strCommonAppData,"ca2",strRelative),pcsz,lpcsz2);
//
////
////   }
////
////
////   string dir::usersystemappdata(::object * pobject, const char * pcszPrefix, const char * lpcsz, const char * lpcsz2)
//
////   {
////      UNREFERENCED_PARAMETER(pobject);
////      return path(appdata(pcszPrefix), lpcsz, lpcsz2);
//
////   }
////
////   string dir::appdata(::object * pobject, const char * pcsz, const char * lpcsz2)
//
////   {
////      return path(userfolder(papp, "appdata"), pcsz, lpcsz2);
//
////   }
////
////   string dir::userdata(::object * pobject, const char * pcsz, const char * lpcsz2)
//
////   {
////      return path(userfolder(papp, "data"), pcsz, lpcsz2);
//
////   }
////
////   string dir::userfolder(::object * pobject, const char * pcsz, const char * lpcsz2)
//
////   {
////
////      string str;
////      str = m_strProfile;
////
////
////      string strRelative;
////      strRelative = install();
////      index iFind = strRelative.find(':');
////      if(iFind >= 0)
////      {
////         strsize iFind1 = strRelative.reverse_find("\\", iFind);
////         strsize iFind2 = strRelative.reverse_find("/", iFind);
////         strsize iStart = MAX(iFind1 + 1, iFind2 + 1);
////         strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart, iFind - iStart) + strRelative.Mid(iFind + 1);
////      }
////
////      string strUserFolderShift;
////
////      if(App(papp).has_property("user_folder_relative_path"))
////      {
////         strUserFolderShift = path(strRelative, App(papp).m_varTopicQuery["user_folder_relative_path"].get_string());
////      }
////      else
////      {
////         strUserFolderShift = strRelative;
////      }
////
////      return path(path(str, "ca2", strUserFolderShift), pcsz, lpcsz2);
//
////
//////      return path(path(str, "ca2"), pcsz);
//
/////*      if(&AppUser(pobject) == nullptr)
////      {
////         string str;
////         SHGetSpecialFolderPath(
////            nullptr,
////            str,
////            CSIDL_PROFILE,
////            FALSE);
////         return path(path(str, "aura\\_____default"), pcsz);
//
////      }
////      else
////      {
////         return path(AppUser(pobject).m_strPath, pcsz, lpcsz2);
//
////      }*/
////   }
////
////   string dir::default_os_user_path_prefix(::object * pobject)
////   {
////      UNREFERENCED_PARAMETER(pobject);
////      unichar buf[MAX_PATH];
////      ULONG ulSize = sizeof(buf) / sizeof(unichar);
////      if(!::GetUserNameExW(NameCanonical, buf, &ulSize))
////      {
////         if(!::GetUserNameW(buf, &ulSize))
////         {
////            __memset(buf, 0, sizeof(buf));
////         }
////      }
////      return ::str::international::unicode_to_utf8(buf);
////   }
////
////   string dir::default_userappdata(::object * pobject, const char * pcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
//
////   {
////      return path(default_userfolder(papp, pcszPrefix, lpcszLogin, "appdata"), pszRelativePath);
//
////   }
////
////   string dir::default_userdata(::object * pobject, const char * pcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
//
////   {
////      return path(default_userfolder(papp, pcszPrefix, lpcszLogin, "data"), pszRelativePath);
//
////   }
////
////   string dir::default_userfolder(::object * pobject, const char * pcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
//
////   {
////
////      return userfolder(papp, pszRelativePath);
////
/////*      UNREFERENCED_PARAMETER(pobject);
////      string str;
////      SHGetSpecialFolderPath(
////         nullptr,
////         str,
////         CSIDL_APPDATA,
////         FALSE);
////      return path(path(str, "aura\\user", pcszPrefix), lpcszLogin, pszRelativePath);*/
//
////   }
////
////   string dir::userquicklaunch(::object * pobject, const char * pcszRelativePath, const char * lpcsz2)
//
////   {
////      UNREFERENCED_PARAMETER(pobject);
////      string str;
////      str = m_strAppData;
////      str = path(str, "Microsoft\\Internet Explorer\\Quick Launch");
////      return path(str, pcszRelativePath, lpcsz2);
//
////   }
////
////   string dir::userprograms(::object * pobject, const char * pcszRelativePath, const char * lpcsz2)
//
////   {
////      UNREFERENCED_PARAMETER(pobject);
////      string str;
////      str = m_strPrograms;
////      return path(str, pcszRelativePath, lpcsz2);
//
////   }
////
////   string dir::commonprograms(const char * pcszRelativePath, const char * lpcsz2)
//
////   {
////      string str;
////      str = m_strCommonPrograms;
////      return path(str, pcszRelativePath, lpcsz2);
//
////   }
//
//      //bool dir::is_inside_time(const char * pszPath, ::object * pobject)
//      //{
//      //   return is_inside(time(), pszPath, papp);
//      //}
//
//
//      //bool dir::is_inside(const char * pszDir, const char * pszPath, ::object * pobject)
//      //{
//      //
//      //   return ::str::begins_ci(pszDir, pszPath);
//
//      //}
//
//
//      //bool dir::has_subdir(::object * pobject, const char * pszDir)
//      //{
//      //
//      //   return ::windows::dir::has_subdir(papp,pszDir);
//
//      //}
//
//   } // namespace axis
//
//} // namespace windows
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
