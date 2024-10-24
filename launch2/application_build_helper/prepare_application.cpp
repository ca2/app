// From implement.cpp by camilo on 2022-09-23 20:08 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application_build_helper.h"
#include "acme/platform/scoped_restore.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/system.h"


namespace application_build_helper
{


   void application_build_helper::prepare_application()
   {

      auto pathFolder = m_pathFolder;

      ::file::path pathApplicationTxt;

      pathApplicationTxt = pathFolder / "application.txt";

      if (!file_system()->exists(pathApplicationTxt))
      {

         return;

      }

      if (m_strProjectName.has_char())
      {

         if (m_strProjectName.case_insensitive_begins("shared_") || m_strProjectName.case_insensitive_begins("static_"))
         {

            return;

         }

      }

      //printf("prepare_application: %s", m_strApplication.c_str());

      printf("%s", m_strApplication.c_str());

      at_end_of_scope
      {

         printf("\n");

      };

      //printf("build_helper \"%s\"\n", pathFolder.c_str());

      //printf("operating system: \"%s\"\n", m_strOperatingSystem2.c_str());

      create_package_list();

      string strPackages;

      for (auto & packagereference : m_packagereferencea)
      {

         strPackages += packagereference.m_strPackage.trimmed() + "\n";

      }

      ::file::path pathInl = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_static_factory.inl";

      ::file::path pathSourcePackages = pathFolder / "_packages.txt";

      ::file::path pathTargetPackages = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_packages.txt";

      file_system()->put_contents(pathSourcePackages, strPackages);

      auto strPackagesConfirm = file_system()->as_string(pathSourcePackages);

#ifdef WINDOWS

      strPackagesConfirm.find_replace("\r\n", "\n");

#endif

      if (strPackagesConfirm == strPackages)
      {

         //printf("\"_packages.txt\" created successfully.\n\n");

      }
      else
      {

         printf("\"_packages.txt\" wasn't correctly created.\n");
         printf("contents(%s) wrong.\n", pathSourcePackages.c_str());

      }

      ::file::path pathSourceReferences;

      pathSourceReferences = pathFolder / "_references.txt";

      ::file::path pathTargetReferences;

      pathTargetReferences = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_references.txt";

      ::file::path pathDepsDeprecated;

      pathDepsDeprecated = pathFolder / "deps.txt";

      ::file::path pathSourceDependencies;

      pathSourceDependencies = pathFolder / "_dependencies.txt";

      ::file::path pathTargetDependencies;

      pathTargetDependencies = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_dependencies.txt";

      ::file::path pathSourceExtensions;

      pathSourceExtensions = pathFolder / "_extensions.txt";

      ::file::path pathTargetExtensions;

      pathTargetExtensions = pathFolder / "operating_system" / m_strSlashedOperatingSystem / "_extensions.txt";

      auto lenDepsDeprecated = file_system()->as_string(pathDepsDeprecated).trimmed().length();

      auto lenSourceDependencies = file_system()->as_string(pathSourceDependencies).trimmed().length();

      if (lenDepsDeprecated > 0 && lenSourceDependencies == 0)
      {

         file_system()->set_file_normal(pathSourceDependencies);

         file_system()->copy(pathSourceDependencies, pathDepsDeprecated, true);

      }

      generate__main();
      
#ifdef WINDOWS_DESKTOP

      copy_icon_ico();
      
#endif

      static_factory(pathInl, pathSourceDependencies);

      translate_items(pathTargetReferences, pathSourceReferences);

      translate_items(pathTargetDependencies, pathSourceDependencies);

      translate_items(pathTargetExtensions, pathSourceExtensions);

      translate_package_list();

      string strTranslatedPackages;

      for (auto & packagereference : m_packagereferencea)
      {

         string strPackage = packagereference.m_strPackage.trimmed();

         string strTranslatedPackage = defer_project_to_binary(strPackage);

         strTranslatedPackages += strTranslatedPackage + "\n";

      }

      file_system()->put_contents(pathTargetPackages, strTranslatedPackages);

      bool bDoMatter = true;

      ///::file::path pathMatterOutput = m_pathFolder / "matter_output.txt";

      ::file::path pathZip = m_pathFolder / "_matter.zip";

      if (m_bSoftBuild)
      {

         //if (file_exists(pathMatterOutput))
         if(file_exists(pathZip))
         {

            bDoMatter = false;

         }

      }

      if (bDoMatter)
      {

         defer_matter();

         zip_matter();

         if (!file_system()->exists(pathZip))
         {

            string strError;

            strError.format("\"%s\" wasn't created.", pathZip.c_str());

            throw ::exception(error_failed, strError);

         }

         //sacmefile()->ensure_exists(pathMatterOutput);

         auto pathSeedAndroid = m_pathOperatingSystem / "seed-android";

         if (directory_system()->is(pathSeedAndroid))
         {

            auto pathAssetsMatterZip = pathSeedAndroid / m_strProjectId / "app/src/main/assets/_matter.zip";

            file_system()->copy(pathAssetsMatterZip, pathZip, true);

         }

#if defined(FREEBSD) || defined(OPENBSD)|| defined(LINUX)

//         int iCreateLinuxMatterObject = string(getenv("DISTRO")) == "raspbian";

  //       iCreateLinuxMatterObject = 1;

    //     if (iCreateLinuxMatterObject)
      //   {

            posix_create_matter_object();

        // }

#endif

      }

   }


} // namespace application_build_helper



