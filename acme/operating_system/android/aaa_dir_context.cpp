#include "framework.h"
#include "_android.h"
#include "acme/constant/id.h"
//#include "acme/xml/_.h"


namespace android
{


   directory_context::directory_context()
   {

   }


   directory_context::~directory_context()
   {

   }


   void directory_context::initialize(::particle * pparticle)
   {

      auto estatus = ::directory_context::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __refer(m_pdirectorysystem, ::acmeacmesystem()->m_pdirectorysystem);

      if (!estatus)
      {

         return estatus;

      }
      
      estatus = __refer(m_pfilesystem, ::acmeacmesystem()->m_pfilesystem);

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


   ::file::listing & directory_context::root_ones(::file::listing & listing)
   {

      listing.add("/");

      listing.m_straTitle.add("File ::acmeacmesystem()");

      return listing;

   }


   ::file::listing & directory_context::ls(::file::listing & listing)
   {

      if (::directory_context::ls( listing))
      {

         return listing;

      }


      if (listing.m_bRecursive)
      {

         ::collection::index iStart = listing.get_count();

         {

            scoped_restore(listing.m_pathFinal);

            scoped_restore(listing.m_eextract);

            ::file::listing straDir(get_context());

            straDir.ls_dir(listing.m_pathFinal);

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

               listing.ls();


            }

         }

         if (listing.m_bFile)
         {

            scoped_restore(listing.m_bRecursive);

            listing.m_bRecursive = false;

            listing.ls_file(listing.m_pathFinal);

         }

         for (::collection::index i = iStart; i < listing.get_size(); i++)
         {

            listing[i].m_iRelative = listing.m_pathFinal.get_length() + 1;

         }

      }
      else
      {


         ::file::path_array stra;

         ::dir::ls(stra, listing.m_pathFinal);

         for (i32 i = 0; i < stra.get_count(); i++)
         {

            ::file::path strPath = stra[i];

            if (!string_begins(strPath, listing.m_pathFinal))
               continue;

            bool bIsDir;

            bIsDir = ::directory_context::is(strPath);

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


   //bool directory_context::rls(const char * lpcsz, string_array * pstraPath, string_array * pstraTitle, string_array * pstraRelative, enum_extract eextract)
   //{

   //   if(::file::system_dir::rls(papp,lpcsz,pstraPath,pstraTitle,pstraRelative,eextract))
   //   {

   //      return true;

   //   }

   //   return rls_pattern(papp, lpcsz, "*.*", pstraPath, pstraTitle, pstraRelative, nullptr, nullptr, eextract);

   //}


   //bool directory_context::rls_pattern(const char * lpcsz, const ::scoped_string & scopedstrPattern, string_array * pstraPath, string_array * pstraTitle, string_array * pstraRelative, bool_array * pbaIsDir, i64_array * piaSize, enum_extract eextract)
   //{


   //   if(::file::system_dir::rls_pattern(papp,lpcsz,pszPattern,pstraPath,pstraTitle,pstraRelative,pbaIsDir,piaSize,eextract))
   //   {

   //      return true;

   //   }

   //   string_array straDir;

   //   ::directory_context::ls_dir(straDir, lpcsz);

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

   //      rls_pattern(papp, strDir, pszPattern, pstraPath, pstraTitle, pstraRelative, pbaIsDir, piaSize, eextract == e_extract_all ? e_extract_all : e_extract_none);

   //      if(pstraRelative != nullptr)
   //      {

   //         for(::collection::index i = iStart; i < pstraRelative->get_size(); i++)
   //         {

   //            pstraRelative->element_at(i) = get_context()->directory_context().path(file()->name_(strDir), pstraRelative->element_at(i));

   //         }

   //      }

   //   }

   //   string strDir(lpcsz);

   //   if(!string_ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }

   //   string_array stra;

   //   ::directory_context::ls(stra, lpcsz);

   //   for(i32 i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!strName.begins_eat(strDir))
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

   //         bIsDir = ::directory_context::is(strPath);

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


   //bool directory_context::rls_dir(const char * lpcsz, string_array * pstraPath, string_array * pstraTitle, string_array * pstraRelative)
   //{

   //   if(::file::system_dir::rls_dir(papp,lpcsz,pstraPath,pstraTitle,pstraRelative))
   //   {

   //      return true;

   //   }

   //   string_array stra;

   //   ::directory_context::ls(stra, lpcsz);

   //   string strDir(lpcsz);

   //   if(!string_ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }


   //   for(i32 i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!strName.begins_eat(strDir))
   //         continue;

   //      if(!get_context()->directory_context().is(strPath))
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

   //         for(::collection::index i = iStart; i < pstraRelative->get_size(); i++)
   //         {

   //            pstraRelative->element_at(i) = get_context()->directory_context().path(strPath, pstraRelative->element_at(i));

   //         }

   //      }

   //   }

   //   return true;

   //}


   //bool directory_context::ls_dir(const char * lpcsz, string_array * pstraPath, string_array * pstraTitle)
   //{

   //   if(::file::system_dir::ls_dir(papp,lpcsz,pstraPath,pstraTitle))
   //   {

   //      return true;

   //   }

   //   string_array stra;

   //   ::directory_context::ls(stra, lpcsz);

   //   string strDir(lpcsz);

   //   if(!string_ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }


   //   for(i32 i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!strName.begins_eat(strDir))
   //         continue;

   //      if(!get_context()->directory_context().is(strPath))
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


   //bool directory_context::ls_file(const char * lpcsz, string_array * pstraPath, string_array * pstraTitle)
   //{

   //   if(::file::system_dir::ls_file(papp,lpcsz,pstraPath,pstraTitle))
   //   {

   //      return true;

   //   }

   //   string_array stra;

   //   ::directory_context::ls(stra, lpcsz);

   //   string strDir(lpcsz);

   //   if(!string_ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }


   //   for(i32 i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!strName.begins_eat(strDir))
   //         continue;

   //      if(get_context()->directory_context().is(strPath))
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


   //bool directory_context::ls(const char * lpcsz, string_array * pstraPath, string_array * pstraTitle, bool_array * pbaIsDir, i64_array * piaSize)
   //{


   //   if(::file::system_dir::ls(papp,lpcsz,pstraPath,pstraTitle,pbaIsDir,piaSize))
   //   {

   //      return true;

   //   }


   //   string_array stra;

   //   ::directory_context::ls(stra, lpcsz);

   //   string strDir(lpcsz);

   //   if(!string_ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }


   //   for(i32 i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!strName.begins_eat(strDir))
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

   //         bIsDir = get_context()->directory_context().is(strPath);

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

   bool directory_context::is(const ::file::path & lpcszPath)
   {

      if (::directory_context::is(lpcszPath))
      {

         return true;

      }

      string strPath(lpcszPath);

      if (strPath.length() >= MAX_PATH)
      {

         if (string_begins(strPath, "\\\\"))
         {

            strPath = "\\\\?\\UNC" + strPath.substr(1);

         }
         else
         {

            strPath = "\\\\?\\" + strPath;

         }

      }

      bool bIsDir = ::dir::_is(strPath);

      return bIsDir;

   }


   //bool directory_context::is(const ::string & strPath)
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

   //   //strsize iLen = utf8_to_unicode_count(strPath);
   //   //wstrPath.alloc(iLen + 32);
   //   wstrPath = utf8_to_unicode(strPath);
   //   if(wstrPath.get_length() >= MAX_PATH)
   //   {
   //      if(string_begins(wstrPath, L"\\\\"))
   //      {
   //         ::str::begin(wstrPath, L"\\\\?\\UNC");
   //      }
   //      else
   //      {
   //         ::str::begin(wstrPath, L"\\\\?\\");
   //      }
   //   }

   //   bIsDir = ::directory_context::is(unicode_to_utf8(wstrPath));

   //   m_isdirmap.set(strPath, bIsDir, bIsDir ? 0 : ::get_last_error());

   //   return bIsDir;
   //}

   bool directory_context::name_is(const ::file::path & str)
   {
      //information(str);
      strsize iLast = str.length() - 1;
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

      if (task_flag().is_set(e_task_flag_compress_is_dir) && iLast >= 3 && !case_insensitive_ansi_count_compare(&((const char *)str)[iLast - 3], ".zip", 4))
      {

         return true;

      }

      wstring wstrPath;

      wstrPath = utf8_to_unicode(str, iLast + 1);

      bool bIsDir = ::directory_context::is(unicode_to_utf8(wstrPath));

      return bIsDir;

   }


   ::file::path directory_context::time()
   {

      return m_pdirectorysystem->m_strTimeFolder;

   }


   ::file::path directory_context::stage()
   {

      return install() / "stage";

   }


   ::file::path directory_context::stageapp()
   {

      return stage() / "basis";

   }


   ::file::path directory_context::netseed()
   {

      return m_pdirectorysystem->m_strNetSeedFolder;

   }


   // stage in ccwarehouse spalib
   ::file::path directory_context::install()
   {

      single_lock synchronouslock(mutex(), true);

      return m_pdirectorysystem->m_pathInstall;

   }


   //::file::path directory_context::module()
   //{

   // return ::acmeacmesystem()->get_module_folder();

   //}


   //::file::path directory_context::ca2module()
   //{
   //
   // return ::acmeacmesystem()->get_ca2_module_folder();
   //
   //}


   ::file::path directory_context::time_square()
   {

      return time() / "time";

   }


   ::file::path directory_context::time_log(const ::string & strId)
   {

      return appdata() / "log";

   }

   bool directory_context::mk(const ::file::path & lpcsz)
   {

      if (is(lpcsz))
         return true;

      ::file::path_array stra;

      lpcsz.ascendants_path(stra);

      for (i32 i = 0; i < stra.get_size(); i++)
      {

         if (!is(stra[i]))
         {

            if (!::dir::_mk(stra[i]))
            {
               ::u32 dwError = ::get_last_error();
               if (dwError == ERROR_ALREADY_EXISTS)
               {
                  string str;
                  str = "\\\\?\\" + stra[i];
                  str.trim_right("\\/");
                  try
                  {
                     file()->del(str);
                  }
                  catch (...)
                  {
                  }
                  str = stra[i];
                  str.trim_right("\\/");
                  try
                  {
                     file()->del(str);
                  }
                  catch (...)
                  {
                  }

                  //if(::CreateDirectory(utf8_to_unicode("\\\\?\\" + stra[i]), nullptr))
                  if (::directory_context::mk("\\\\?\\" + stra[i]))
                  {

                     goto try1;

                  }
                  else
                  {

                     dwError = ::get_last_error();

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


   bool directory_context::rm(const ::file::path & psz, bool bRecursive)
   {
      if (bRecursive)
      {

         ::file::listing straPath(get_context());

         straPath.ls(psz);

         for (i32 i = 0; i < straPath.get_count(); i++)
         {

            if (is(straPath[i]))
            {

               rm(psz / straPath[i].name(), true);

            }
            else
            {

               ::unlink(straPath[i]);

            }

         }

      }

      return ::rmdir(psz) != false;

   }


   void directory_context::init_system()
   {

      auto estatus = ::directory_context::init_system();
     
      if (!estatus)
      {

        return estatus;

      }

      xml::document doc;

      doc.load(file()->as_string(appdata() / "configuration\\directory.xml"));

      ::file::path pathInstall = ::acmeacmesystem()->m_pathCacheDir;

      m_pdirectorysystem->m_pathInstall = pathInstall;

      //nodeos_set_home(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "home");

      //nodeos_set_temp(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "temp");

      m_pdirectorysystem->m_strCommonAppData = pathInstall / "commonappdata";

      mk(m_pdirectorysystem->m_strCommonAppData);

      if (!is(m_pdirectorysystem->m_strCommonAppData))
         return false;


      if (doc.get_name() == "directory_configuration")
      {

         m_pdirectorysystem->m_strTimeFolder = doc.get_child_value("time");

         m_pdirectorysystem->m_strNetSeedFolder = doc.get_child_value("netseed");

      }

      if (m_pdirectorysystem->m_strTimeFolder.is_empty())
         m_pdirectorysystem->m_strTimeFolder = appdata() / "time";

      if (m_pdirectorysystem->m_strNetSeedFolder.is_empty())
         m_pdirectorysystem->m_strNetSeedFolder = install() / "net";

      mk(m_pdirectorysystem->m_strTimeFolder);

      if (!is(m_pdirectorysystem->m_strTimeFolder))
         return false;

      mk(m_pdirectorysystem->m_strTimeFolder / "time");

      return true;

   }


   void directory_context::init_context()
   {

      auto estatus = ::directory_context::init_context();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::file::path directory_context::trash_that_is_not_trash(const ::file::path & pszParam)
   {

      if (pszParam == nullptr)
         return "";

      ::file::path psz(pszParam);

      if (psz[1] == ':')
      {
         string strDir = psz.folder();
         string str;
         str = strDir.left(2);
         str += "\\trash_that_is_not_trash\\";
         string strFormat;
         ::earth::time time;
         time = ::earth::time::now();
         strFormat.formatf("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
         str += strFormat;
         if (strDir[2] == '\\')
         {
            str += strDir.substr(3);
         }
         else
         {
            str += strDir.substr(2);
         }
         return str;
      }

      return "";
   }

   ::file::path directory_context::appdata()
   {
      string str;
      /*SHGetSpecialFolderPath(
         nullptr,
         str,
         CSIDL_COMMON_APPDATA,
         false);*/

      str =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / ".ca2/app/appdata";
      string strRelative;
      strRelative = install();
      //auto pFind = strRelative.find(':');
      //if(::is_set(pFind))
      {
         // strsize iFind1 = strRelative(pFind).rear_find("\\");
         //strsize iFind2 = strRelative(pFind).rear_find("/");
         //strsize iStart = maximum(iFind1 + 1, iFind2 + 1);

         //strRelative = strRelative.left(iFind - 1) + "_" + strRelative.substr(iStart, iFind - iStart) + strRelative(pFind + 1);
      }
      return str / "ca2";
   }

   ::file::path directory_context::commonappdata()
   {

      return m_pdirectorysystem->m_strCommonAppData;

   }


   //::file::path directory_context::usersystemappdata(const string & lpcszPrefix)
   //{

   //   

   //   return appdata() / lpcszPrefix;

   //}


   //::file::path directory_context::appdata()
   //{

   //   return userfolder() /  "appdata";

   //}


   //::file::path directory_context::userdata()
   //{

   //   return userfolder() / "data";

   //}


//   ::file::path directory_context::userfolder()
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
//      auto pFind = strRelative.find(':');
//      if(::is_set(pFind))
//      {
//         strsize iFind1 = strRelative(pFind).rear_find("\\");
//         strsize iFind2 = strRelative(pFind).rear_find("/");
//         strsize iStart = maximum(iFind1 + 1, iFind2 + 1);
//         strRelative = strRelative.left(iFind - 1) + "_" + strRelative.substr(iStart, iFind - iStart) + strRelative(pFind + 1);
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

   //::file::path directory_context::default_os_user_path_prefix()
   //{
   //   /*
   //   unichar buf[MAX_PATH];
   //   ULONG ulSize = sizeof(buf) / sizeof(unichar);
   //   if(!::GetUserNameExW(Namecanonical, buf, &ulSize))
   //   {
   //      if(!::GetUserNameW(buf, &ulSize))
   //      {
   //         memory_set(buf, 0, sizeof(buf));
   //      }
   //   }*/
   //   /*return unicode_to_utf8(buf);*/
   //   return ::getlogin();

   //}


   //::file::path directory_context::default_userappdata(const string & lpcszPrefix, const string & lpcszLogin)
   //{

   //   return default_userfolder(papp, lpcszPrefix, lpcszLogin) /  "appdata";

   //}


   //::file::path directory_context::default_userdata(const string & lpcszPrefix, const string & lpcszLogin)
   //{

   //   return default_userfolder(papp, lpcszPrefix, lpcszLogin) / "data";

   //}


   //::file::path directory_context::default_userfolder(::platform::application *  papp, const string & lpcszPrefix, const string & lpcszLogin)
   //{

   //   return userfolder();

   //}


   ::file::path directory_context::userquicklaunch()
   {

      return m_pdirectorysystem->m_pathInstall / ".ca2/app/Microsoft/Internet Explorer/Quick Launch";

   }


   ::file::path directory_context::bookmark()
   {

      return m_pdirectorysystem->m_pathInstall / "bookmark";

   }


   ::file::path directory_context::userprograms()
   {

      return m_pdirectorysystem->m_pathInstall / "userprograms";

   }


   ::file::path directory_context::commonprograms()
   {

      return m_pdirectorysystem->m_pathInstall / "commonprograms";

   }


   bool directory_context::is_inside_time(const ::file::path & pszPath)
   {

      return is_inside(time(), pszPath);

   }



   bool directory_context::is_inside(const ::file::path & pszDir, const ::file::path & pszPath)
   {

      return case_insensitive_string_begins(pszDir, pszPath);

   }


   bool directory_context::has_subdir(const ::file::path & pszDir)
   {

      ::file::listing ls(get_context());

      ls.ls_dir(pszDir);

      return ls.get_size() > 0;

   }


   ::file::path directory_context::commonappdata_root()
   {

      return m_pdirectorysystem->m_strCommonAppData;

   }


} // namespace android
