#include "framework.h"
////#include "acme/exception/exception.h"
#include "application_build_helper.h"
#include "application.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/directory_system.h"
//#include "acme/filesystem/filesystem/file_context.h"
#include "acme/operating_system/process.h"
#include "acme/platform/ini.h"
#include "acme/platform/node.h"
#include "acme/prototype/string/str.h"
#include "acme/platform/system.h"
#ifdef WINDOWS_DESTKOP
#include <direct.h>
#endif
#include "application_build_helper.h"
//#include "acme/platform/system.h"
//#include "acme/prototype/collection/string_array.h"
//#include "_factory.h"

namespace application_build_helper
{


   application_build_helper::application_build_helper(application * papplication) :
      m_papplication(papplication)
   {

      m_iExitCode = 0;

      m_estatus = ::success;

      initialize(papplication);

      m_bTranslateDependency = false;

#ifdef WINDOWS

      m_strOperatingSystem2 = "windows";

      m_strSystemAmbientRelease = "windows";

#elif defined(MACOS)

      m_strOperatingSystem2 = "macos";

      m_strSystemAmbientRelease = "macos";

#elif defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)

      string strOperatingSystem;

      strOperatingSystem = getenv("__SYSTEM_UNDERSCORE_OPERATING_SYSTEM");

      string strSystemAmbientRelease;

      strSystemAmbientRelease = getenv("__SYSTEM_SLASHED_OPERATING_SYSTEM");

      if (strOperatingSystem.is_empty() || strSystemAmbientRelease.is_empty())
      {

         printf("%s", "Did you set __SYSTEM_SLASHED_OPERATING_SYSTEM and __SYSTEM_UNDERSCORE_OPERATING_SYSTEM environment variables?\n");
         printf("%s", "(They can be set \"automatically\" with patch_shell)\n");

         throw ::exception(error_wrong_state);

      }

      m_strOperatingSystem2 = strOperatingSystem;

      m_strSystemAmbientRelease = strSystemAmbientRelease;

      ::file::path pathEtcOsRelease;

      pathEtcOsRelease = "/etc/os-release";

      auto pini = file_system()->get_ini(pathEtcOsRelease);

      string strDistro = (*pini)["ID"];

      strDistro.trim("\'");
      strDistro.trim("\"");
      strDistro.trim();
      strDistro.trim("\'");
      strDistro.trim("\"");
      strDistro.trim();

      ::file::path pathUrl;

      string strDistroRelease = (*pini)["VERSION_ID"];

      strDistroRelease.trim("\'");
      strDistroRelease.trim("\"");
      strDistroRelease.trim();
      strDistroRelease.trim("\'");
      strDistroRelease.trim("\"");
      strDistroRelease.trim();

      m_strInstallerType = "";

      if(strDistro.case_insensitive_order("fedora") == 0)
      {


//         pathUrlBase = "https://fedora.camilothomas.com";

         if (acmesystem()->m_pnode->get_eoperating_ambient() == ::user::e_operating_ambient_kde)
         {

            //pathUrlBase /= "kde";

         }
         else
         {

            //pathUrlBase /= "workstation";

         }

         m_strInstallerType = "rpm";

      }
      else if(strDistro.case_insensitive_order("linuxmint") == 0)
      {


//         pathUrlBase = "https://ubuntu.camilothomas.com";
//
//         if (strDistroRelease == "20" || strDistroRelease.begins("20."))
//         {
//
//            strDistroRelease = "20.04";
//
//         }
         m_strInstallerType = "deb";

      }
      else if(strDistro.case_insensitive_order("debian") == 0)
      {


//         pathUrlBase = "https://debian.camilothomas.com";
//
//         if (acmesystem()->m_pnode->get_eoperating_ambient() & ::user::e_operating_ambient_kde)
//         {
//
//            pathUrlBase /= "kde";
//
//         }
//         else
//         {
//
//            pathUrlBase /= "gnome";
//
//         }

         m_strInstallerType = "deb";

      }
      else
      {

//         if (acmesystem()->m_pnode->get_eoperating_ambient() & ::user::e_operating_ambient_kde)
//         {
//
//            pathUrlBase = "https://kubuntu.camilothomas.com";
//
//         }
//         else
//         {
//
//            pathUrlBase = "https://ubuntu.camilothomas.com";
//
//         }


         m_strInstallerType = "deb";

      }


#endif

      m_strOperatingSystem2.trim();

      m_strSystemAmbientRelease.trim();

   }


   application_build_helper::~application_build_helper()
   {

   }


   bool application_build_helper::set_project_id(const ::scoped_string & scopedstrProjectId)
   {

      auto range = scopedstrProjectId();

      range.trim();

      if (range.is_empty() || range.begins("#"))
      {

         return false;

      }

      {

         ::file::path pathIterator = range;

         m_strItem = pathIterator.name();

         m_strItem.trim();

         pathIterator.ascend();

         m_strRoot = pathIterator.name();

         m_strRoot.trim();

         pathIterator.ascend();

         m_strBase = pathIterator.name();

         m_strBase.trim();

      }

      if (m_strItem.is_empty() || m_strRoot.is_empty())
      {

         return false;

      }

      if (m_strBase.is_empty())
      {

         m_strBase = "source";

      }

      m_strProjectId = m_strRoot + "/" + m_strItem;

      m_strApplication = m_strProjectId;

      m_pathBaseDir = m_papplication->m_pathFolder;

      m_pathFolder = m_pathBaseDir / m_strBase / m_strProjectId;

      m_pathGroup = m_pathFolder - 2;

      m_pathOperatingSystem = m_pathBaseDir / "operating_system";

      m_pathPort = m_pathBaseDir / "port";

      m_pathSource = m_pathBaseDir / "source";

      m_strUnderscoreAppId = m_strProjectId;

      m_strUnderscoreAppId.find_replace("/", "_");

      m_strUnderscoreAppId.find_replace("-", "_");

      return true;

   }


   //
   //
   //void application_build_helper::load_application_list()
   //{
   //
   //   auto pathApplicationMatterList = m_pathBaseDir / "application_list.txt";
   //
   //   string_array straApplications;
   //
   //   file()->get_lines(straApplications, pathApplicationMatterList);
   //
   //   straApplications.trim();
   //
   //   for (string& strPath : straApplications)
   //   {
   //
   //      strPath.case_insensitive_ends_eat("application.txt");
   //
   //      ::file::path path = strPath;
   //
   //      string strItem = path.name();
   //
   //      path.go_up();
   //
   //      string strRoot = path.name();
   //
   //      string strAppId = strRoot + "/" + strItem;
   //
   //      string strUnderscoreAppId(strAppId);
   //
   //      strUnderscoreAppId.replace("/", "_");
   //
   //      strUnderscoreAppId.replace("-", "_");
   //
   //      m_mapAppId.set_at(strAppId, strRoot + "/" + strUnderscoreAppId);
   //
   //   }
   //
   //}


   void application_build_helper::create_package_list()
   {

      auto pathIgnorePackage = m_pathOperatingSystem / ("operating_system-" OPERATING_SYSTEM_NAME) / "ignore_packages.txt";

      m_straIgnorePackage = get_lines(pathIgnorePackage);

      ::file::path pathPackageMap;

      pathPackageMap = m_pathOperatingSystem / ("operating_system-" OPERATING_SYSTEM_NAME) / "operating_system" / m_strSystemAmbientRelease / "package_map.txt";

      try
      {

         m_piniPackageMap = file_system()->get_ini(pathPackageMap);

      }
      catch (const ::exception & e)
      {

         fprintf(stderr, "\n\nFatal! Failed to open package map file: %s\n(Does it exist?)\n\n\n", pathPackageMap.c_str());

         throw e;

      }

      if (::is_null(m_piniPackageMap))
      {

         fprintf(stderr, "\n\nFatal! Failed to open package map file: %s\n(Does it exist?)\n\n\n", pathPackageMap.c_str());

         throw ::exception(error_failed);

      }

      package_reference packagereference;

      packagereference.m_strPackage = m_strProjectId;

      packagereference.m_iLine = -1;

      add_package(packagereference);

      //return ::success;

   }


   void application_build_helper::translate_package_list()
   {

      //::e_status estatus = ::success;

      m_bTranslateDependency = true;

      auto packagereferenceaCopy = m_packagereferencea;

      m_packagereferencea.clear();

      for (auto & packagereference : packagereferenceaCopy)
      {

         //estatus = 

         add_package(packagereference);

         //if(!estatus)
         //{

         //   break;

         //}

      }

      //   return estatus;

   }

   //void application_build_helper::set_base_dir(const ::file::path& pathBaseDir)
   //{

   //   m_pathOperatingSystem = pathBaseDir / "operating_system";

   //   m_pathSource = pathBaseDir / "source";

   //   m_straIgnorePackage = get_lines(m_pathOperatingSystem / ("operating_system-" OPERATING_SYSTEM_NAME) / "ignore_packages.txt");

   //}


   void application_build_helper::add_package(package_reference & packagereference)
   {

      if (m_bTranslateDependency)
      {

         string strTranslate = defer_translate_dependency(packagereference.m_strPackage);

         if (strTranslate.has_character() && strTranslate != packagereference.m_strPackage)
         {

            packagereference.m_strPackage = strTranslate;

         }

         if (packagereference.m_strPackage.case_insensitive_begins("default_"))
         {

            return;

         }

      }

      if (packagereference.m_strPackage.is_empty())
      {

         return;

      }

      if (packagereference.m_strPackage.case_insensitive_ends("node_windows"))
      {

         printf("%s", "");

      }

      if (m_straIgnorePackage.case_insensitive_contains(packagereference.m_strPackage))
      {

         return;

      }

      if (packagereference.m_strPackage.case_insensitive_ends("node_windows"))
      {

         printf("%s", "");

      }

      string_array stra;

      stra.explode("/", packagereference.m_strPackage);

      auto size = stra.get_size();

      if (size == 1 && packagereference.m_strPackage.case_insensitive_order("none") == 0)
      {

         return;

      }

      if (size > 3 && !packagereference.m_strPackage.case_insensitive_begins("default_"))
      {

         //printf("Error in package: \"%s\"\n", strPackage.c_str());

         auto psz =

#ifdef WINDOWS

            "%s(%d,1)"

#else

            "%s:%d:1"

#endif
            ": error: package name must have one or two slashes.\n";

         fprintf(stderr, psz, packagereference.m_pathReference.c_str(), packagereference.m_iLine + 1);

         throw ::exception(error_failed);

      }

      if (m_packagereferencea.is_empty())
      {

         package_reference packagereferenceNew;

         packagereferenceNew.m_strPackage = m_strRoot + "/" + m_strUnderscoreAppId;

         packagereferenceNew.m_pathReference = packagereference.m_pathReference;

         packagereferenceNew.m_iLine = packagereference.m_iLine;

         if (packagereferenceNew.m_strPackage.case_insensitive_ends("veriwell_multimedia"))
         {

            printf("%s", "");

         }

         m_packagereferencea.add(packagereferenceNew);

      }
      else
      {

         package_reference packagereferenceNew;

         packagereferenceNew = packagereference;

         packagereferenceNew.m_strPackage = defer_translate_application_name(packagereferenceNew.m_strPackage);

         packagereferenceNew.m_strPackage = defer_binary_to_project(packagereferenceNew.m_strPackage);

         for (auto & packagereferenceItem : m_packagereferencea)
         {

            if (packagereferenceItem.m_strPackage.trimmed().case_insensitive_order(packagereferenceNew.m_strPackage.trimmed()) == 0)
            {

               return;

            }

         }

         if (packagereference.m_strPackage.case_insensitive_ends("node_windows"))
         {

            //printf("test");

         }

         if (packagereferenceNew.m_strPackage.case_insensitive_ends("veriwell_multimedia"))
         {

            printf("%s", "");

         }

         m_packagereferencea.add(packagereferenceNew);

      }

      add_package_dependencies(packagereference);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void application_build_helper::add_package_dependencies(const package_reference & packagereference)
   {

      //::e_status estatus = ::success;

      auto packagereferencea = get_all_package_dependencies(packagereference.m_strPackage);

      for (auto & packagereferenceItem : packagereferencea)
      {

         //estatus = 

         add_package(packagereferenceItem);

         //if(!estatus)
         //{

         //   break;

         //}

      }

      //return estatus;

   }


   string_array application_build_helper::get_lines(const ::file::path & path, bool bNoExceptionIfNotFound)
   {

      auto strInput = file_system()->as_string(path, -1, bNoExceptionIfNotFound);

      if (strInput.is_empty())
      {

         return {};

      }

      string_array stra;

      stra.add_lines(strInput, true);

      return stra;

   }


   package_reference_array application_build_helper::get_package_list(const ::scoped_string & scopedstrList, const ::scoped_string & scopedstrPackageParam)
   {

      ::file::path path;

      ::string strPackage = strPackageParam;

      if (strPackage.case_insensitive_begins("operating_system-"))
      {

         path = m_pathOperatingSystem;

      }
      else if (strPackage.case_insensitive_begins_eat("port/"))
      {

         if (strPackage.contains("/"))
         {

            path = m_pathPort;

         }
         else
         {

            path = m_pathPort / "package_list";

         }

      }
      else if (strPackage.case_insensitive_begins_eat("third/"))
      {

//         if (strPackage == "swresample")
//         {
//
//            ::output_debug_string("swresample");
//
//         }

         if (strPackage.contains("/"))
         {

            path = m_pathPort;

         }
         else
         {

            path = m_pathPort / "package_list";

         }

      }
      else
      {

         path = m_pathSource;

      }

      path /= strPackage.trimmed();

      path /= (strList.trimmed() + ".txt");

      auto stra = get_lines(path);

      stra.trim();

      stra.erase_empty();

      package_reference_array packagereferencea;

      int iLine = 0;

      for (auto & str : stra)
      {

         packagereferencea.add({ str, path, iLine });

         iLine++;

      }

      return packagereferencea;

   }


   package_reference_array application_build_helper::get_package_references(const ::scoped_string & scopedstrPackage)
   {

      return get_package_list("_references", strPackage);

   }


   package_reference_array application_build_helper::get_package_dependencies(const ::scoped_string & scopedstrPackage)
   {

      return get_package_list("_dependencies", strPackage);

   }


   package_reference_array application_build_helper::get_package_extensions(const ::scoped_string & scopedstrPackage)
   {

      return get_package_list("_extensions", strPackage);

   }


   package_reference_array application_build_helper::get_all_package_dependencies(const ::scoped_string & scopedstrPackage)
   {

      package_reference_array packagereferencea;

      package_reference_array straReferences = get_package_references(strPackage);

      package_reference_array straDependencies = get_package_dependencies(strPackage);

      package_reference_array straExtensions = get_package_extensions(strPackage);

      packagereferencea.append(straReferences);

      packagereferencea.append(straDependencies);

      packagereferencea.append(straExtensions);

      return packagereferencea;

   }


   void application_build_helper::copy_icon_ico()
   {

      ::file::path pathRoot = m_pathFolder - 1;

      ::file::path pathSource = pathRoot / "_matter" / m_strItem / "_std/_std/main";

      ::file::path pathIconSource = pathSource / "icon.ico";

      ::file::path pathIconTarget = m_pathFolder / "icon.ico";

      if (!file_system()->exists(pathIconSource))
      {

         string strMessage;

         strMessage.format("The icon file is missing: \"%s\".\n", pathIconSource.c_str());

         fprintf(stderr, "%s", strMessage.c_str());

         throw ::exception(error_not_found, strMessage);

      }

      file_system()->overwrite_if_different(pathIconTarget, pathIconSource);

   }


   void application_build_helper::generate__main()
   {

      {

         ::file::path pathMain = m_pathFolder / "operating_system" / m_strSystemAmbientRelease / "_main.inl";

         string strMain;

         strMain += "#define APPLICATION " + m_strUnderscoreAppId + "\n";
         strMain += "#define __APP_ID \"" + m_strProjectId + "\"\n";
         //strMain += "#if defined(WINDOWS_DESKTOP) && defined(CUBE)\n";
         strMain += "#include \"_static_factory.inl\"\n";
         //strMain += "#endif\n";
         //strMain += "#include \"_factory.h\"\n";
         strMain += "#include \"acme/application.h\"\n";

         ///estatus =
         //file_system()->set_file_normal(pathMain);

         //if(!estatus)
         //{

         //   return estatus;

         //}

         //estatus =

         file_system()->put_contents(pathMain, strMain);

         //if(!estatus)
         //{

         //   return estatus;

         //}

      }

      {

         ::file::path pathApps = m_pathFolder / "_apps.txt";

         string strApps = file_system()->as_string(pathApps);

         strApps.trim();

         string_array straApps;

         straApps.add_lines(strApps, false);

         straApps.trim();

         straApps.erase_empty();

         straApps.add("");

         //if(strApps.has_character())
         {

            for (::collection::index i = 0; i < straApps.get_count(); i++)
            {

               ::string strAppAddUp = straApps[i];

               strAppAddUp.trim();

               string strAppName = m_strUnderscoreAppId;

               if (strAppAddUp.has_character())
               {

                  strAppName += "_" + strAppAddUp;

               }

               {

                  ::file::path pathApplication =
                     m_pathFolder / "operating_system" / m_strSystemAmbientRelease / ("_" + strAppName + ".cpp");

                  //if (!psystem->m_pfilesystem->exists(pathApplication))
                  {

                     string strApplication;

                     strApplication += "#include \"framework.h\"\n";

                     if (strAppAddUp.has_character())
                     {

                        strAppAddUp.make_upper();

                        strApplication += "#define " + strAppAddUp + "\n";

                     }

                     strApplication += "#include \"_main.inl\"\n";

                     //file_system()->set_file_normal(pathApplication);

                     //if (!estatus)
                     //{

                     //   return estatus;

                     //}

                     ///estatus =

                     file_system()->put_contents(pathApplication, strApplication);

                     /*         if (!estatus)
                              {

                                 return estatus;

                              }*/

                  }

               }

            }

         }

      }

      //return estatus;

   }




   //void command_system(const char* psz)
   //{
   //
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //   string str(scopedstr);
   //
   //   wstring wstr;
   //
   //   wstr = str;
   //
   //   ::OutputDebugStringW(wstr);
   //
   //   ::OutputDebugStringW(L"\n");
   //
   //   STARTUPINFO info = { sizeof(info) };
   //   PROCESS_INFORMATION processInfo;
   //   if (CreateProcessW(nullptr, wstr, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &info, &processInfo))
   //   {
   //      WaitForSingleObject(processInfo.hProcess, INFINITE);
   //      CloseHandle(processInfo.hProcess);
   //      CloseHandle(processInfo.hThread);
   //   }
   //#else
   //
   //   printf("%s\n", psz);
   //   ::system(scopedstr);
   //
   //#endif
   //}
   //

   string application_build_helper::defer_translate_application_name(string strDependency)
   {

      ::file::path pathApplicationMatter = m_pathSource / strDependency / "application.txt";

      auto estatus = file_system()->exists(pathApplicationMatter);

      if (estatus)
      {

         string strPath = pathApplicationMatter;

         strPath.case_insensitive_ends_eat("application.txt");

         ::file::path path = strPath;

         string strItem = path.name();

         path.ascend();

         string strRoot = path.name();

         string strAppId = strRoot + "/" + strItem;

         string strUnderscoreAppId(strAppId);

         strUnderscoreAppId.find_replace("/", "_");

         strUnderscoreAppId.find_replace("-", "_");

         return strRoot + "/" + strUnderscoreAppId;

      }

      return strDependency;

   }


   string application_build_helper::defer_translate_dependency(string strDependency)
   {

      strDependency.trim();

      strDependency.make_lower();

      if (strDependency.begins("port/"))
      {
         
         //::output_debug_string("port/");

      }
      else if (strDependency.begins_eat("third/"))
      {

         strDependency = "port" / strDependency;

      }

      string strTranslatedDependency = (*m_piniPackageMap)[strDependency];

      if (strTranslatedDependency.is_empty())
      {

         if (strDependency.trimmed().case_insensitive_begins("default_"))
         {

            //return success_none;
            return "";

         }

         return strDependency;

      }

      return strTranslatedDependency;

      //   if (strDependency == "default_draw2d")
      //   {
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //      return "draw2d_gdiplus";
      //
      //#else
      //
      //      return "draw2d_cairo";
      //
      //#endif
      //
      //   }
      //   else if (strDependency == "default_node")
      //   {
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //      return "node_windows";
      //
      //#else
      //
      //      return "node_linux";
      //
      //#endif
      //
      //   }
      //   else if (strDependency == "default_windowing")
      //   {
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //      return "windowing_win32";
      //
      //#else
      //
      //      return "";
      //
      //#endif
      //
      //   }
      //   else if (strDependency == "default_imaging")
      //   {
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //      return "imaging_wic";
      //
      //#else
      //
      //      return "imaging_freeimage";
      //
      //#endif
      //
      //   }
      //   else if (strDependency == "default_write_text")
      //   {
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //      return "write_text_win32";
      //
      //#else
      //
      //      return "write_text_pango";
      //
      //#endif
      //
      //   }
      //
      //   return strDependency;

   }


   string application_build_helper::defer_binary_to_project(string strBinary)
   {

      string_array stra;

      stra.explode("/", strBinary);

      if (stra.get_count() != 2)
      {

         return strBinary;

      }

      string strRoot = stra[0];

      string strName = stra[1];

      auto & map = m_mapBinaryToProject[strRoot];

      if (map["(--loaded--)"].is_empty())
      {

         load_map(map, "binary_to_project", strRoot);

      }

      string strRename;

      strRename = map[strBinary];

      if (strRename.is_empty())
      {

         return strBinary;

      }

      return strRename;

   }


   string application_build_helper::defer_project_to_binary(string strProject)
   {

      string_array stra;

      stra.explode("/", strProject);

      if (stra.get_count() != 2)
      {

         return strProject;

      }

      string strRoot = stra[0];

      string strName = stra[1];

      auto & map = m_mapProjectToBinary[strRoot];

      if (map["(--loaded--)"].is_empty())
      {

         load_map(map, "project_to_binary", strRoot);

      }

      string strRename;

      strRename = map[strProject];

      if (strRename.is_empty())
      {

         return strProject;

      }

      return strRename;

   }


   void application_build_helper::load_map(string_to_string & map, string strMap, string strRoot)
   {

      ::file::path pathMapBase;

      if (strRoot.case_insensitive_begins("operating_system-"))
      {

         pathMapBase = m_pathOperatingSystem;

      }
      else
      {

         pathMapBase = m_pathSource;

      }

      pathMapBase /= strRoot;

      ::file::path pathMap;

      pathMap = pathMapBase / (strMap + ".txt");

      string_array straLines;

      straLines = file_system()->lines(pathMap);

      for (auto & strLine : straLines)
      {

         string_array stra;

         stra.explode("=", strLine);

         if (stra.get_size() == 2)
         {

            string strName = stra[0];

            string strRename = stra[1];

            strName.trim();

            strRename.trim();

            map[strName] = strRename;

         }

      }

      map["(--loaded--)"] = "true";

   }


   void application_build_helper::static_factory(const ::scoped_string & scopedstrFileDst, const ::scoped_string & scopedstrFileSrc)
   {

      //auto estatus =

      file_system()->ensure_exists(strFileSrc);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      auto strInput = file_system()->as_string(strFileSrc);

      //if(!strInput)
      //{


      //   return strInput;

      //}

      string_array stra;

      stra.add_lines(strInput, false);

      string strOutput;

      strOutput += "#define DO_FACTORY(do) \\\n";

      //string strFactory;

      //strFactory += "BEGIN_FACTORY("+ m_strUnderscoreAppId +") \n";

      bool bFirst = true;

      for (::collection::index i = 0; i < stra.get_count(); i++)
      {

         auto & strLine = stra[i];

         strLine.trim();

         if (strLine.has_character())
         {

            string strDependency = defer_translate_dependency(strLine);

            if (strDependency.has_character())
            {

               string_array stra;

               stra.explode("/", strDependency);

               if (stra.get_size() == 2)
               {

                  string strPackage = stra[1];

                  if (strPackage.has_character())
                  {

                     if (!bFirst)
                     {

                        strOutput += " \\\n";

                     }

                     strOutput += "do(" + strPackage + ");";

                     //strFactory += "FACTORY_DEPENDENCY(" + strPackage + ") \n";

                     bFirst = false;

                  }

               }

            }

         }

      }

      strOutput += "\n";

      ///strFactory += "FACTORY_DEPENDENCY(" + m_strUnderscoreAppId + ") \n";

      //strFactory += "END_FACTORY() \n";

      //estatus =

      //file_system()->set_file_normal(strFileDst);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //estatus =

      file_system()->put_contents(strFileDst, strOutput);

      //file_system()->put_contents(strFileFactory, strFactory);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void application_build_helper::translate_items(const ::scoped_string & scopedstrFileDst, const ::scoped_string & scopedstrFileSrc)
   {

      //auto estatus =

      file_system()->ensure_exists(strFileSrc);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      auto strInput = file_system()->as_string(strFileSrc);

      //if(!strInput)
      //{

      //   return strInput;

      //}

      string_array stra;

      stra.add_lines(strInput, false);

      string strOutput;

      for (::collection::index i = 0; i < stra.get_count(); i++)
      {

         auto & strLine = stra[i];

         strLine.trim();

         if (strLine.has_character())
         {

            string strDependency = defer_translate_dependency(strLine);

            if (strDependency.has_character())
            {

               strOutput += strDependency;

               strOutput += "\n";

            }

         }

      }

      //estatus =

      //file_system()->set_file_normal(strFileDst);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //estatus =

      file_system()->put_contents(strFileDst, strOutput);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void application_build_helper::defer_matter()
   {

      ::file::path pathMatter = m_pathFolder / "matter.txt";

      //auto estatus =

      file_system()->ensure_exists(pathMatter);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //file_system()->set_file_normal(pathMatter);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      auto strInput = file_system()->as_string(pathMatter);

      //if(!strInput)
      //{

      //   return strInput;

      //}

      strInput.trim();

      if (strInput.has_character())
      {

         return;

      }

      string strOutput;

      strOutput += "app/main\n";

      strOutput += m_strProjectId + "\n";

      file_system()->put_contents(pathMatter, strOutput);

   }


} // namespace application_build_helper



