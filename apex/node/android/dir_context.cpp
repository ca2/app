#include "framework.h"
#include "_android.h"
#include "acme/id.h"
//#include "apex/xml/_.h"


namespace android
{


   dir_context::dir_context()
   {

   }


   dir_context::~dir_context()
   {

   }


   ::e_status dir_context::initialize(::object * pobject)
   {

      auto estatus = ::dir_context::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __refer(m_pdirsystem, ::apex::get_system()->m_pdirsystem);

      if (!estatus)
      {

         return estatus;

      }
      
      estatus = __refer(m_pfilesystem, ::apex::get_system()->m_pfilesystem);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   inline bool myspace(char ch)
   {
      return ch == ' ' ||
         ch == '\t' ||
         ch == '\r' ||
         ch == '\n';
   }


   ::file::listing & dir_context::root_ones(::file::listing & listing)
   {

      listing.add("/");

      listing.m_straTitle.add("File ::apex::get_system()");

      return listing;

   }


   ::file::listing & dir_context::ls(::file::listing & listing)
   {

      if (::dir_context::ls( listing))
      {

         return listing;

      }


      if (listing.m_bRecursive)
      {

         index iStart = listing.get_count();

         {

            __restore(listing.m_pathFinal);

            __restore(listing.m_eextract);

            ::file::listing straDir;

            ls_dir(straDir, listing.m_pathFinal);

            for (i32 i = 0; i < straDir.get_count(); i++)
            {

               string strDir = straDir[i];

               if (strDir == listing.m_pathFinal)
                  continue;

               if (listing.m_bDir)
               {

                  listing.add(::file::path(strDir));

                  ::file::path & path = listing.last();

                  path.m_iSize = 0;

                  path.m_iDir = 1;

               }

               listing.m_pathFinal = strDir;

               ls(listing);


            }

         }

         if (listing.m_bFile)
         {

            __restore(listing.m_bRecursive);

            listing.m_bRecursive = false;

            ls_file(listing, listing.m_pathFinal);

         }

         for (index i = iStart; i < listing.get_size(); i++)
         {

            listing[i].m_iRelative = listing.m_pathFinal.get_length() + 1;

         }

      }
      else
      {


         ::file::patha stra;

         ::dir::ls(stra, listing.m_pathFinal);

         for (i32 i = 0; i < stra.get_count(); i++)
         {

            ::file::path strPath = stra[i];

            if (!::str::begins(strPath, listing.m_pathFinal))
               continue;

            bool bIsDir;

            bIsDir = ::dir_context::is(strPath);

            if (!bIsDir && !matches_wildcard_criteria(listing.m_straPattern, strPath.name()))
               continue;

            if ((bIsDir && !listing.m_bDir) || (!bIsDir && !listing.m_bFile))
               continue;

            listing.add(strPath);

            ::file::path & path = listing.last();

            path.m_iDir = bIsDir ? 1 : 0;

            if (bIsDir)
            {

               path.m_iSize = 0;

            }
            else
            {

               path.m_iSize = file_length_dup(strPath);

            }

         }

      }

      return listing;

   }


   //bool dir_context::rls(const char * lpcsz, string_array * pstraPath, string_array * pstraTitle, string_array * pstraRelative, e_extract eextract)
   //{

   //   if(::file::system_dir::rls(papp,lpcsz,pstraPath,pstraTitle,pstraRelative,eextract))
   //   {

   //      return true;

   //   }

   //   return rls_pattern(papp, lpcsz, "*.*", pstraPath, pstraTitle, pstraRelative, nullptr, nullptr, eextract);

   //}


   //bool dir_context::rls_pattern(const char * lpcsz, const char * pszPattern, string_array * pstraPath, string_array * pstraTitle, string_array * pstraRelative, bool_array * pbaIsDir, i64_array * piaSize, e_extract eextract)
   //{


   //   if(::file::system_dir::rls_pattern(papp,lpcsz,pszPattern,pstraPath,pstraTitle,pstraRelative,pbaIsDir,piaSize,eextract))
   //   {

   //      return true;

   //   }

   //   string_array straDir;

   //   ::dir_context::ls_dir(straDir, lpcsz);

   //   for(i32 i = 0; i < straDir.get_count(); i++)
   //   {

   //      string strDir = straDir[i];

   //      if(strDir == lpcsz)
   //         continue;

   //      index iStart = 0;

   //      if(pstraRelative != nullptr)
   //      {
   //         iStart = pstraRelative->get_size();
   //      }

   //      rls_pattern(papp, strDir, pszPattern, pstraPath, pstraTitle, pstraRelative, pbaIsDir, piaSize, eextract == extract_all ? extract_all : extract_none);

   //      if(pstraRelative != nullptr)
   //      {

   //         for(index i = iStart; i < pstraRelative->get_size(); i++)
   //         {

   //            pstraRelative->element_at(i) = get_context()->dir_context().path(pcontext->m_papexcontext->file().name_(strDir), pstraRelative->element_at(i));

   //         }

   //      }

   //   }

   //   string strDir(lpcsz);

   //   if(!::str::ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }

   //   string_array stra;

   //   ::dir_context::ls(stra, lpcsz);

   //   for(i32 i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!::str::begins_eat(strName, strDir))
   //         continue;

   //      if(!matches_wildcard_criteria(pszPattern, strName))
   //         continue;

   //      if(pstraPath != nullptr)
   //      {

   //         pstraPath->add(strPath);

   //      }

   //      if(pstraTitle != nullptr)
   //      {

   //         pstraTitle->add(strName);

   //      }

   //      if(pstraRelative != nullptr)
   //      {

   //         pstraRelative->add(strName);

   //      }

   //      bool bIsDir;

   //      if(pbaIsDir != nullptr || piaSize != nullptr)
   //      {

   //         bIsDir = ::dir_context::is(strPath);

   //      }

   //      if(pbaIsDir != nullptr)
   //      {

   //         pbaIsDir->add(bIsDir);

   //      }

   //      if(piaSize != nullptr)
   //      {

   //         if(bIsDir)
   //         {

   //            piaSize->add(0);

   //         }
   //         else
   //         {

   //            piaSize->add(file_length_dup(strPath));

   //         }

   //      }

   //   }

   //   return true;

   //}


   //bool dir_context::rls_dir(const char * lpcsz, string_array * pstraPath, string_array * pstraTitle, string_array * pstraRelative)
   //{

   //   if(::file::system_dir::rls_dir(papp,lpcsz,pstraPath,pstraTitle,pstraRelative))
   //   {

   //      return true;

   //   }

   //   string_array stra;

   //   ::dir_context::ls(stra, lpcsz);

   //   string strDir(lpcsz);

   //   if(!::str::ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }


   //   for(i32 i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!::str::begins_eat(strName, strDir))
   //         continue;

   //      if(!get_context()->dir_context().is(strPath))
   //         continue;

   //      if(pstraPath != nullptr)
   //      {

   //         pstraPath->add((const char *) stra[i]);

   //      }

   //      if(pstraTitle != nullptr)
   //      {

   //         pstraTitle->add(strName);

   //      }

   //      if(pstraRelative != nullptr)
   //      {

   //         pstraRelative->add(strName);

   //      }

   //      index iStart = 0;

   //      if(pstraRelative != nullptr)
   //      {

   //         iStart = pstraRelative->get_size();

   //      }

   //      rls_dir(papp, strPath, pstraPath, pstraTitle, pstraRelative);

   //      if(pstraRelative != nullptr)
   //      {

   //         for(index i = iStart; i < pstraRelative->get_size(); i++)
   //         {

   //            pstraRelative->element_at(i) = get_context()->dir_context().path(strPath, pstraRelative->element_at(i));

   //         }

   //      }

   //   }

   //   return true;

   //}


   //bool dir_context::ls_dir(const char * lpcsz, string_array * pstraPath, string_array * pstraTitle)
   //{

   //   if(::file::system_dir::ls_dir(papp,lpcsz,pstraPath,pstraTitle))
   //   {

   //      return true;

   //   }

   //   string_array stra;

   //   ::dir_context::ls(stra, lpcsz);

   //   string strDir(lpcsz);

   //   if(!::str::ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }


   //   for(i32 i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!::str::begins_eat(strName, strDir))
   //         continue;

   //      if(!get_context()->dir_context().is(strPath))
   //         continue;

   //      if(pstraPath != nullptr)
   //      {

   //         pstraPath->add((const char *) stra[i]);

   //      }

   //      if(pstraTitle != nullptr)
   //      {

   //         pstraTitle->add(strName);

   //      }

   //   }

   //   return true;

   //}


   //bool dir_context::ls_file(const char * lpcsz, string_array * pstraPath, string_array * pstraTitle)
   //{

   //   if(::file::system_dir::ls_file(papp,lpcsz,pstraPath,pstraTitle))
   //   {

   //      return true;

   //   }

   //   string_array stra;

   //   ::dir_context::ls(stra, lpcsz);

   //   string strDir(lpcsz);

   //   if(!::str::ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }


   //   for(i32 i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!::str::begins_eat(strName, strDir))
   //         continue;

   //      if(get_context()->dir_context().is(strPath))
   //         continue;


   //      if(pstraPath != nullptr)
   //      {

   //         pstraPath->add((const char *) stra[i]);

   //      }

   //      if(pstraTitle != nullptr)
   //      {

   //         pstraTitle->add(strName);

   //      }

   //   }

   //   return true;

   //}


   //bool dir_context::ls(const char * lpcsz, string_array * pstraPath, string_array * pstraTitle, bool_array * pbaIsDir, i64_array * piaSize)
   //{


   //   if(::file::system_dir::ls(papp,lpcsz,pstraPath,pstraTitle,pbaIsDir,piaSize))
   //   {

   //      return true;

   //   }


   //   string_array stra;

   //   ::dir_context::ls(stra, lpcsz);

   //   string strDir(lpcsz);

   //   if(!::str::ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }


   //   for(i32 i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!::str::begins_eat(strName, strDir))
   //         continue;

   //      if(pstraPath != nullptr)
   //      {

   //         pstraPath->add((const char *) stra[i]);

   //      }

   //      if(pstraTitle != nullptr)
   //      {

   //         pstraTitle->add(strName);

   //      }


   //      bool bIsDir;

   //      if(pbaIsDir != nullptr || piaSize != nullptr)
   //      {

   //         bIsDir = get_context()->dir_context().is(strPath);

   //      }

   //      if(pbaIsDir != nullptr)
   //      {

   //         pbaIsDir->add(bIsDir);

   //      }

   //      if(piaSize != nullptr)
   //      {

   //         if(bIsDir)
   //         {

   //            piaSize->add(0);

   //         }
   //         else
   //         {

   //            piaSize->add(file_length_dup(strPath));

   //         }

   //      }


   //   }

   //   return true;

   //}

   bool dir_context::is(const ::file::path & lpcszPath)
   {

      if (::dir_context::is(lpcszPath))
      {

         return true;

      }

      string strPath(lpcszPath);

      if (strPath.get_length() >= MAX_PATH)
      {

         if (::str::begins(strPath, "\\\\"))
         {

            strPath = "\\\\?\\UNC" + strPath.Mid(1);

         }
         else
         {

            strPath = "\\\\?\\" + strPath;

         }

      }

      bool bIsDir = ::dir::_is(strPath);

      return bIsDir;

   }


   //bool dir_context::is(const ::string & strPath)
   //{

   //   if(::file::system_dir::is(strPath))
   //      return true;

   //   bool bIsDir;

   //   ::u32 dwLastError;

   //   if(m_isdirmap.lookup(strPath, bIsDir, dwLastError))
   //   {

   //      if(!bIsDir)
   //      {

   //         set_last_error(dwLastError);

   //      }

   //      return bIsDir;

   //   }


   //   wstring wstrPath;

   //   //strsize iLen = ::str::international::utf8_to_unicode_count(strPath);
   //   //wstrPath.alloc(iLen + 32);
   //   wstrPath = ::str::international::utf8_to_unicode(strPath);
   //   if(wstrPath.get_length() >= MAX_PATH)
   //   {
   //      if(::str::begins(wstrPath, L"\\\\"))
   //      {
   //         ::str::begin(wstrPath, L"\\\\?\\UNC");
   //      }
   //      else
   //      {
   //         ::str::begin(wstrPath, L"\\\\?\\");
   //      }
   //   }

   //   bIsDir = ::dir_context::is(::str::international::unicode_to_utf8(wstrPath));

   //   m_isdirmap.set(strPath, bIsDir, bIsDir ? 0 : ::get_last_error());

   //   return bIsDir;
   //}

   bool dir_context::name_is(const ::file::path & str)
   {
      //output_debug_string(str);
      strsize iLast = str.get_length() - 1;
      while (iLast >= 0)
      {
         if (str[iLast] != '\\' && str[iLast] != '/' && str[iLast] != ':')
            break;
         iLast--;
      }
      while (iLast >= 0)
      {
         if (str[iLast] == '\\' || str[iLast] == '/' || str[iLast] == ':')
            break;
         iLast--;
      }
      if (iLast >= 0)
      {
         while (iLast >= 0)
         {
            if (str[iLast] != '\\' && str[iLast] != '/' && str[iLast] != ':')
            {
               iLast++;
               break;

            }

            iLast--;

         }

      }
      else
      {

         return true; // assume empty string is root_ones directory

      }

      if (task_flag().is_set(e_task_flag_zip_is_dir) && iLast >= 3 && !ansi_count_compare_ci(&((const char *)str)[iLast - 3], ".zip", 4))
      {

         return true;

      }

      wstring wstrPath;

      wstrPath = ::str::international::utf8_to_unicode(str, iLast + 1);

      bool bIsDir = ::dir_context::is(::str::international::unicode_to_utf8(wstrPath));

      return bIsDir;

   }


   ::file::path dir_context::time()
   {

      return m_pdirsystem->m_strTimeFolder;

   }


   ::file::path dir_context::stage()
   {

      return install() / "stage";

   }


   ::file::path dir_context::stageapp()
   {

      return stage() / "basis";

   }


   ::file::path dir_context::netseed()
   {

      return m_pdirsystem->m_strNetSeedFolder;

   }


   // stage in ccwarehouse spalib
   ::file::path dir_context::install()
   {

      single_lock synchronouslock(mutex(), true);

      return m_pdirsystem->m_pathInstall;

   }


   //::file::path dir_context::module()
   //{

   // return ::apex::get_system()->get_module_folder();

   //}


   //::file::path dir_context::ca2module()
   //{
   //
   // return ::apex::get_system()->get_ca2_module_folder();
   //
   //}


   ::file::path dir_context::time_square()
   {

      return time() / "time";

   }


   ::file::path dir_context::time_log(const ::string & strId)
   {

      return appdata() / "log";

   }

   bool dir_context::mk(const ::file::path & lpcsz)
   {

      if (is(lpcsz))
         return true;

      ::file::patha stra;

      lpcsz.ascendants_path(stra);

      for (i32 i = 0; i < stra.get_size(); i++)
      {

         if (!is(stra[i]))
         {

            if (!::dir::_mk(stra[i]))
            {

               auto estatus = ::get_last_status();

               if (estatus == error_already_exists)
               {

                  string str;
                  str = "\\\\?\\" + stra[i];
                  str.trim_right("\\/");
                  try
                  {
                     pcontext->m_papexcontext->file().del(str);
                  }
                  catch (...)
                  {
                  }
                  str = stra[i];
                  str.trim_right("\\/");
                  try
                  {
                     pcontext->m_papexcontext->file().del(str);
                  }
                  catch (...)
                  {
                  }

                  //if(::CreateDirectory(::str::international::utf8_to_unicode("\\\\?\\" + stra[i]), nullptr))
                  if (::dir_context::mk("\\\\?\\" + stra[i]))
                  {

                     goto try1;

                  }
                  else
                  {

                     estatus = ::get_last_status();

                  }

               }

            }

         try1:

            if (!is(stra[i]))
            {

               return false;

            }

         }

      }

      return true;

   }


   bool dir_context::rm(const ::file::path & path, bool bRecursive)
   {
      if (bRecursive)
      {

         ::file::listing straPath;

         straPath.m_pathFinal = path;

         ls(straPath);

         for (i32 i = 0; i < straPath.get_count(); i++)
         {

            if (is(straPath[i]))
            {

               rm(path / straPath[i].name(), true);

            }
            else
            {

               ::unlink(straPath[i]);

            }

         }

      }

      return ::rmdir(path) != false;

   }


   ::e_status dir_context::init_system()
   {

      auto estatus = ::dir_context::init_system();
     
      if (!estatus)
      {

        return estatus;

      }

      //xml::document doc;

      //doc.load(pcontext->m_papexcontext->file().as_string(appdata() / "configuration\\directory.xml"));

      ::file::path pathInstall = ::apex::get_system()->m_pathCacheDirectory;

      m_pdirsystem->m_pathInstall = pathInstall;

      //nodeos_set_home(         auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->system() / "home");

      //nodeos_set_temp(         auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->system() / "temp");

      m_pdirsystem->m_strCommonAppData = pathInstall / "commonappdata";

      mk(m_pdirsystem->m_strCommonAppData);

      if (!is(m_pdirsystem->m_strCommonAppData))
      {

         return false;

      }

      ::file::path pathTimeFolder;

      ::file::path pathNetSeedFolder;

      //if (doc.get_name() == "directory_configuration")
      //{

      //   pathTimeFolder = doc.get_child_value("time");

      //   pathNetSeedFolder = doc.get_child_value("netseed");

      //}

      if (m_pdirsystem->m_strTimeFolder.is_empty())
      {

         pathTimeFolder = appdata() / "time";

      }

      if (m_pdirsystem->m_strNetSeedFolder.is_empty())
      {

         pathNetSeedFolder = install() / "net";

      }

      mk(pathTimeFolder);

      if (!is(pathTimeFolder))
      {

         return error_failed;

      }

      ::file::path pathTimeFolderTime;

      pathTimeFolderTime = pathTimeFolder / "time";

      mk(pathTimeFolderTime);

      if (!is(pathTimeFolderTime))
      {

         return error_failed;

      }

      m_pdirsystem->m_strTimeFolder = pathTimeFolder;

      m_pdirsystem->m_strNetSeedFolder = pathNetSeedFolder;

      return success;

   }


   ::e_status dir_context::init_context()
   {

      auto estatus = ::dir_context::init_context();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::file::path dir_context::trash_that_is_not_trash(const ::file::path & pszParam)
   {

      if (pszParam == nullptr)
         return "";

      ::file::path psz(pszParam);

      if (psz[1] == ':')
      {
         string strDir = psz.folder();
         string str;
         str = strDir.Left(2);
         str += "\\trash_that_is_not_trash\\";
         string strFormat;
         ::datetime::time time;
         time = ::datetime::time::now();
         strFormat.format("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
         str += strFormat;
         if (strDir[2] == '\\')
         {
            str += strDir.Mid(3);
         }
         else
         {
            str += strDir.Mid(2);
         }
         return str;
      }

      return "";
   }


   ::file::path dir_context::appdata()
   {

      string str;

      str =          auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->system() / ".ca2/app/appdata";
      
      string strRelative;

      strRelative = install();

      return str / "ca2";

   }


   ::file::path dir_context::commonappdata()
   {

      return m_pdirsystem->m_strCommonAppData;

   }


   //::file::path dir_context::usersystemappdata(const string & lpcszPrefix)
   //{

   //   

   //   return appdata() / lpcszPrefix;

   //}


   //::file::path dir_context::appdata()
   //{

   //   return userfolder() /  "appdata";

   //}


   //::file::path dir_context::userdata()
   //{

   //   return userfolder() / "data";

   //}


//   ::file::path dir_context::userfolder()
//   {
//
//      string str;
//      /*SHGetSpecialFolderPath(
//         nullptr,
//         str,
//         CSIDL_PROFILE,
//         false);*/
//
//      str = getenv("HOME");
//
//      ::file::path strRelative;
//      strRelative = install();
//      index iFind = strRelative.find(':');
//      if(iFind >= 0)
//      {
//         strsize iFind1 = strRelative.reverse_find("\\", iFind);
//         strsize iFind2 = strRelative.reverse_find("/", iFind);
//         strsize iStart = maximum(iFind1 + 1, iFind2 + 1);
//         strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart, iFind - iStart) + strRelative.Mid(iFind + 1);
//      }
//
//   ::file::path strUserFolderShift;
//
//      if(App(papp).has_property("user_folder_relative_path"))
//      {
//         strUserFolderShift = strRelative / App(papp).m_varTopicQuery["user_folder_relative_path"].get_string();
//      }
//      else
//      {
//         strUserFolderShift = strRelative;
//      }
//
//      return str / "ca2" / strUserFolderShift;
//
////      return path(path(str, "ca2"), lpcsz);
///*      if(&AppUser() == nullptr)
//      {
//         string str;
//         SHGetSpecialFolderPath(
//            nullptr,
//            str,
//            CSIDL_PROFILE,
//            false);
//         return path(path(str, "ca2\\_____default"), lpcsz);
//      }
//      else
//      {
//         return path(AppUser().m_strPath, lpcsz, lpcsz2);
//      }*/
//   }

   //::file::path dir_context::default_os_user_path_prefix()
   //{
   //   /*
   //   unichar buf[MAX_PATH];
   //   ULONG ulSize = sizeof(buf) / sizeof(unichar);
   //   if(!::GetUserNameExW(Namecanonical, buf, &ulSize))
   //   {
   //      if(!::GetUserNameW(buf, &ulSize))
   //      {
   //         __memset(buf, 0, sizeof(buf));
   //      }
   //   }*/
   //   /*return ::str::international::unicode_to_utf8(buf);*/
   //   return ::getlogin();

   //}


   //::file::path dir_context::default_userappdata(const string & lpcszPrefix, const string & lpcszLogin)
   //{

   //   return default_userfolder(papp, lpcszPrefix, lpcszLogin) /  "appdata";

   //}


   //::file::path dir_context::default_userdata(const string & lpcszPrefix, const string & lpcszLogin)
   //{

   //   return default_userfolder(papp, lpcszPrefix, lpcszLogin) / "data";

   //}


   //::file::path dir_context::default_userfolder(::application *  papp, const string & lpcszPrefix, const string & lpcszLogin)
   //{

   //   return userfolder();

   //}


   ::file::path dir_context::userquicklaunch()
   {

      return m_pdirsystem->m_pathInstall / ".ca2/app/Microsoft/Internet Explorer/Quick Launch";

   }


   ::file::path dir_context::bookmark()
   {

      return m_pdirsystem->m_pathInstall / "bookmark";

   }


   ::file::path dir_context::userprograms()
   {

      return m_pdirsystem->m_pathInstall / "userprograms";

   }


   ::file::path dir_context::commonprograms()
   {

      return m_pdirsystem->m_pathInstall / "commonprograms";

   }


   bool dir_context::is_inside_time(const ::file::path & pszPath)
   {

      return is_inside(time(), pszPath);

   }



   bool dir_context::is_inside(const ::file::path & pszDir, const ::file::path & pszPath)
   {

      return ::str::begins_ci(pszDir, pszPath);

   }


   bool dir_context::has_subdir(const ::file::path & pszDir)
   {

      ::file::listing ls;

      ls_dir(ls, pszDir);

      return ls.get_size() > 0;

   }


   ::file::path dir_context::commonappdata_root()
   {

      return m_pdirsystem->m_strCommonAppData;

   }


} // namespace android
