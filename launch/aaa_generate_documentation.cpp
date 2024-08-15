// Created by camilo on 2023-02-11 12:22 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"


namespace application_build_helper
{


   void application::generate_documentation()
   {

      generate_documentation("source/app/acme");

      //   printf("Preparing to generate documentation...");
      //
      //   auto path = acmedirectory()->get_current();
      //
      //   acmedirectory()->change_current(path / "source/app/acme");
      //
      //   acmedirectory()->change_current(path / "source/app/acme/doxygen.directory");
      //
      //   int iExitCode = 0;
      //
      //   string_array straOutput;
      //
      //   string strCmd;
      //
      //   strCmd = "doxygen doxygen.doxygen";
      //
      //   acmenode()->command_system(straOutput, iExitCode, strCmd, e_command_system_inline_log);
      //
      //   string strLog;
      //
      //   strLog = straOutput.implode("\n");
      //   
      //   acmefile()->put_contents(path / "source/app/acme/doxygen.directory/generation.log", strLog);
      //
      //   
      //
      //
      //   // acmefile()->copy("C:\\documentation-release", "C:\\documentation", true);
      //
      //
      ////   //string strFolder = subsystem()->get_argument1(0);
      ////
      ////   //string strProjectName = subsystem()->get_argument1(1);
      ////
      ////   //set_package_folder(strFolder);
      ////
      ////   auto pathFolder = m_pathFolder;
      ////
      ////   ::file::path pathApplicationTxt;
      ////
      ////   pathApplicationTxt = pathFolder / "application.txt";
      ////
      ////   if (!acmefile()->exists(pathApplicationTxt))
      ////   {
      ////
      ////      return;
      ////
      ////   }
      ////
      ////   if (m_strProjectName.has_char())
      ////   {
      ////
      ////      if (m_strProjectName.case_insensitive_begins("shared_") || m_strProjectName.case_insensitive_begins("static_"))
      ////      {
      ////
      ////         return;
      ////
      ////      }
      ////
      ////   }
      ////
      ////   printf("build_helper \"%s\"\n", pathFolder.c_str());
      ////
      ////   printf("operating system: \"%s\"\n", m_strOperatingSystem2.c_str());
      ////
      ////   create_package_list();
      ////
      ////   string strPackages;
      ////
      ////   for (auto & packagereference : m_packagereferencea)
      ////   {
      ////
      ////      strPackages += packagereference.m_strPackage.trimmed() + "\n";
      ////
      ////   }
      ////
      ////   ::file::path pathInl = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_static_factory.inl";
      ////
      ////   ::file::path pathSourcePackages = pathFolder / "_packages.txt";
      ////
      ////   ::file::path pathTargetPackages = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_packages.txt";
      ////
      ////   acmefile()->put_contents(pathSourcePackages, strPackages);
      ////
      ////   auto strPackagesConfirm = acmefile()->as_string(pathSourcePackages);
      ////
      ////#ifdef WINDOWS
      ////
      ////   strPackagesConfirm.find_replace("\r\n", "\n");
      ////
      ////#endif
      ////
      ////   if (strPackagesConfirm == strPackages)
      ////   {
      ////
      ////      printf("\"_packages.txt\" created successfully.");
      ////
      ////   }
      ////   else
      ////   {
      ////
      ////      printf("\"_packages.txt\" wasn't correctly created.");
      ////
      ////   }
      ////
      ////   ::file::path pathSourceReferences;
      ////
      ////   pathSourceReferences = pathFolder / "_references.txt";
      ////
      ////   ::file::path pathTargetReferences;
      ////
      ////   pathTargetReferences = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_references.txt";
      ////
      ////   ::file::path pathDepsDeprecated;
      ////
      ////   pathDepsDeprecated = pathFolder / "deps.txt";
      ////
      ////   ::file::path pathSourceDependencies;
      ////
      ////   pathSourceDependencies = pathFolder / "_dependencies.txt";
      ////
      ////   ::file::path pathTargetDependencies;
      ////
      ////   pathTargetDependencies = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_dependencies.txt";
      ////
      ////   ::file::path pathSourceExtensions;
      ////
      ////   pathSourceExtensions = pathFolder / "_extensions.txt";
      ////
      ////   ::file::path pathTargetExtensions;
      ////
      ////   pathTargetExtensions = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_extensions.txt";
      ////
      ////   auto lenDepsDeprecated = acmefile()->as_string(pathDepsDeprecated).trimmed().length();
      ////
      ////   auto lenSourceDependencies = acmefile()->as_string(pathSourceDependencies).trimmed().length();
      ////
      ////   if (lenDepsDeprecated > 0 && lenSourceDependencies == 0)
      ////   {
      ////
      ////      acmefile()->set_file_normal(pathSourceDependencies);
      ////
      ////      acmefile()->copy(pathSourceDependencies, pathDepsDeprecated, true);
      ////
      ////   }
      ////
      ////   generate__main();
      ////
      ////   copy_icon_ico();
      ////
      ////   static_factory(pathInl, pathSourceDependencies);
      ////
      ////   translate_items(pathTargetReferences, pathSourceReferences);
      ////
      ////   translate_items(pathTargetDependencies, pathSourceDependencies);
      ////
      ////   translate_items(pathTargetExtensions, pathSourceExtensions);
      ////
      ////   translate_package_list();
      ////
      ////   string strTranslatedPackages;
      ////
      ////   for (auto & packagereference : m_packagereferencea)
      ////   {
      ////
      ////      string strPackage = packagereference.m_strPackage.trimmed();
      ////
      ////      string strTranslatedPackage = defer_project_to_binary(strPackage);
      ////
      ////      strTranslatedPackages += strTranslatedPackage + "\n";
      ////
      ////   }
      ////
      ////   acmefile()->put_contents(pathTargetPackages, strTranslatedPackages);
      ////
      ////   bool bDoMatter = true;
      ////
      ////   ::file::path pathMatterOutput = m_pathFolder / "matter_output.txt";
      ////
      ////   if (m_bSoftBuild)
      ////   {
      ////
      ////      if (file_exists(pathMatterOutput))
      ////      {
      ////
      ////         bDoMatter = false;
      ////
      ////      }
      ////
      ////   }
      ////
      ////   if (bDoMatter)
      ////   {
      ////
      ////      defer_matter();
      ////
      ////      zip_matter();
      ////
      ////      ::file::path pathZip = m_pathFolder / "_matter.zip";
      ////
      ////      if (!acmefile()->exists(pathZip))
      ////      {
      ////
      ////         string strError;
      ////
      ////         strError.format("\"%s\" wasn't created.", pathZip.c_str());
      ////
      ////         throw ::exception(error_failed, strError);
      ////
      ////      }
      ////
      ////      acmefile()->ensure_exists(pathMatterOutput);
      ////
      ////      auto pathSeedAndroid = m_pathOperatingSystem / "seed-android";
      ////
      ////      if (acmedirectory()->is(pathSeedAndroid))
      ////      {
      ////
      ////         auto pathAssetsMatterZip = pathSeedAndroid / m_strPackageAppId / "app/src/main/assets/_matter.zip";
      ////
      ////         acmefile()->copy(pathAssetsMatterZip, pathZip, true);
      ////
      ////      }
      ////
      ////      int iCreateLinuxMatterObject = string(getenv("DISTRO")) == "raspbian";
      ////
      ////#if defined(FREEBSD) || defined(LINUX)
      ////
      ////      iCreateLinuxMatterObject = 1;
      ////
      ////#endif
      ////
      ////      if (iCreateLinuxMatterObject)
      ////      {
      ////
      ////         create_linux_matter_object();
      ////
      ////      }
      ////
      ////   }

   }



   void application::generate_documentation(const ::scoped_string & scopedstrSubPath)
   {

      printf("%s", ("Generating documentation for " + scopedstrSubPath + " ...").c_str());

      auto path = acmedirectory()->get_current();

      acmedirectory()->change_current(path / scopedstrSubPath);

      acmedirectory()->create(path / scopedstrSubPath / "doxygen.directory");

      string_array straOutput;

      string strCmd;

      strCmd = "doxygen doxygen.doxygen";

      auto iExitCode = acmenode()->command_system(strCmd, [&](auto, auto & str){ straOutput.add(str); printf("%s\n", str.c_str()); });

      string strLog;

      strLog = straOutput.implode("\n");
      
      ::string strExitCode;
      
      strExitCode.format("\n\nexit_code = %d\n\n", iExitCode);
      
      strLog += strExitCode;

      acmefile()->put_contents(path / scopedstrSubPath / "doxygen.directory/generation.log", strLog);


      //   //string strFolder = subsystem()->get_argument1(0);
      //
      //   //string strProjectName = subsystem()->get_argument1(1);
      //
      //   //set_package_folder(strFolder);
      //
      //   auto pathFolder = m_pathFolder;
      //
      //   ::file::path pathApplicationTxt;
      //
      //   pathApplicationTxt = pathFolder / "application.txt";
      //
      //   if (!acmefile()->exists(pathApplicationTxt))
      //   {
      //
      //      return;
      //
      //   }
      //
      //   if (m_strProjectName.has_char())
      //   {
      //
      //      if (m_strProjectName.case_insensitive_begins("shared_") || m_strProjectName.case_insensitive_begins("static_"))
      //      {
      //
      //         return;
      //
      //      }
      //
      //   }
      //
      //   printf("build_helper \"%s\"\n", pathFolder.c_str());
      //
      //   printf("operating system: \"%s\"\n", m_strOperatingSystem2.c_str());
      //
      //   create_package_list();
      //
      //   string strPackages;
      //
      //   for (auto & packagereference : m_packagereferencea)
      //   {
      //
      //      strPackages += packagereference.m_strPackage.trimmed() + "\n";
      //
      //   }
      //
      //   ::file::path pathInl = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_static_factory.inl";
      //
      //   ::file::path pathSourcePackages = pathFolder / "_packages.txt";
      //
      //   ::file::path pathTargetPackages = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_packages.txt";
      //
      //   acmefile()->put_contents(pathSourcePackages, strPackages);
      //
      //   auto strPackagesConfirm = acmefile()->as_string(pathSourcePackages);
      //
      //#ifdef WINDOWS
      //
      //   strPackagesConfirm.find_replace("\r\n", "\n");
      //
      //#endif
      //
      //   if (strPackagesConfirm == strPackages)
      //   {
      //
      //      printf("\"_packages.txt\" created successfully.");
      //
      //   }
      //   else
      //   {
      //
      //      printf("\"_packages.txt\" wasn't correctly created.");
      //
      //   }
      //
      //   ::file::path pathSourceReferences;
      //
      //   pathSourceReferences = pathFolder / "_references.txt";
      //
      //   ::file::path pathTargetReferences;
      //
      //   pathTargetReferences = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_references.txt";
      //
      //   ::file::path pathDepsDeprecated;
      //
      //   pathDepsDeprecated = pathFolder / "deps.txt";
      //
      //   ::file::path pathSourceDependencies;
      //
      //   pathSourceDependencies = pathFolder / "_dependencies.txt";
      //
      //   ::file::path pathTargetDependencies;
      //
      //   pathTargetDependencies = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_dependencies.txt";
      //
      //   ::file::path pathSourceExtensions;
      //
      //   pathSourceExtensions = pathFolder / "_extensions.txt";
      //
      //   ::file::path pathTargetExtensions;
      //
      //   pathTargetExtensions = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_extensions.txt";
      //
      //   auto lenDepsDeprecated = acmefile()->as_string(pathDepsDeprecated).trimmed().length();
      //
      //   auto lenSourceDependencies = acmefile()->as_string(pathSourceDependencies).trimmed().length();
      //
      //   if (lenDepsDeprecated > 0 && lenSourceDependencies == 0)
      //   {
      //
      //      acmefile()->set_file_normal(pathSourceDependencies);
      //
      //      acmefile()->copy(pathSourceDependencies, pathDepsDeprecated, true);
      //
      //   }
      //
      //   generate__main();
      //
      //   copy_icon_ico();
      //
      //   static_factory(pathInl, pathSourceDependencies);
      //
      //   translate_items(pathTargetReferences, pathSourceReferences);
      //
      //   translate_items(pathTargetDependencies, pathSourceDependencies);
      //
      //   translate_items(pathTargetExtensions, pathSourceExtensions);
      //
      //   translate_package_list();
      //
      //   string strTranslatedPackages;
      //
      //   for (auto & packagereference : m_packagereferencea)
      //   {
      //
      //      string strPackage = packagereference.m_strPackage.trimmed();
      //
      //      string strTranslatedPackage = defer_project_to_binary(strPackage);
      //
      //      strTranslatedPackages += strTranslatedPackage + "\n";
      //
      //   }
      //
      //   acmefile()->put_contents(pathTargetPackages, strTranslatedPackages);
      //
      //   bool bDoMatter = true;
      //
      //   ::file::path pathMatterOutput = m_pathFolder / "matter_output.txt";
      //
      //   if (m_bSoftBuild)
      //   {
      //
      //      if (file_exists(pathMatterOutput))
      //      {
      //
      //         bDoMatter = false;
      //
      //      }
      //
      //   }
      //
      //   if (bDoMatter)
      //   {
      //
      //      defer_matter();
      //
      //      zip_matter();
      //
      //      ::file::path pathZip = m_pathFolder / "_matter.zip";
      //
      //      if (!acmefile()->exists(pathZip))
      //      {
      //
      //         string strError;
      //
      //         strError.format("\"%s\" wasn't created.", pathZip.c_str());
      //
      //         throw ::exception(error_failed, strError);
      //
      //      }
      //
      //      acmefile()->ensure_exists(pathMatterOutput);
      //
      //      auto pathSeedAndroid = m_pathOperatingSystem / "seed-android";
      //
      //      if (acmedirectory()->is(pathSeedAndroid))
      //      {
      //
      //         auto pathAssetsMatterZip = pathSeedAndroid / m_strPackageAppId / "app/src/main/assets/_matter.zip";
      //
      //         acmefile()->copy(pathAssetsMatterZip, pathZip, true);
      //
      //      }
      //
      //      int iCreateLinuxMatterObject = string(getenv("DISTRO")) == "raspbian";
      //
      //#if defined(FREEBSD) || defined(LINUX)
      //
      //      iCreateLinuxMatterObject = 1;
      //
      //#endif
      //
      //      if (iCreateLinuxMatterObject)
      //      {
      //
      //         create_linux_matter_object();
      //
      //      }
      //
      //   }

   }



} // namespace application_build_helper





