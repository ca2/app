// Created by camilo on 2021-12-17 21:01 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application_build_helper.h"
#include "acme/platform/scoped_restore.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/operating_system/process.h"
#include "acme/platform/node.h"


namespace application_build_helper
{


   void application_build_helper::build_rpm()
   {

      ::string strReleaseNumberSrc = "0.4";

      ::earth::time earthtime;

      earthtime.Now();

      ::string strReleaseNumberDst;

      strReleaseNumberDst.format("%d.%d", earthtime.year() - 2000, earthtime.month());

      ::string strPackageNameSrc = "store-" + strReleaseNumberSrc;

      ::string strPackageNameDst = "store-" + strReleaseNumberDst;

      ::file::path pathHome = directory_system()->home();

      ::file::path pathRpmbuild = pathHome / "rpmbuild";

      string strCommand = "rm -Rf " + pathRpmbuild;

      printf("%s\n", strCommand.c_str());

      acmenode()->command_system("bash -c \"" + strCommand + "\"", std_inline_log());

      ::string pathTool = path_system()->tool_folder_path();

      strCommand = "cp -Rf " + pathTool + "/tool-linux/build_rpm/rpmbuild " + pathRpmbuild;

      printf("%s\n", strCommand.c_str());

      acmenode()->command_system("bash -c \"" + strCommand + "\"", std_inline_log());

      ::file::path pathSOURCES;

      pathSOURCES = pathRpmbuild / "SOURCES";

      ::file::path pathPackageSrc;

      pathPackageSrc = pathSOURCES / strPackageNameSrc;

      ::file::path pathPackageDst;

      pathPackageDst = pathSOURCES / strPackageNameDst;

      acmenode()->command_system("mv \"" + pathPackageSrc + "\" \"" + pathPackageDst+ "\"", std_inline_log());

      ::file::path pathStoreFolder;

      pathStoreFolder = directory_system()->home() / "store";

      pathStoreFolder /= m_strSystemAmbientRelease;

      ::file::path pathStoreZip;

      pathStoreZip = pathStoreFolder;

      pathStoreZip /= "app-core/store.zip";

      ::file::path pathBin;

      pathBin = pathPackageDst / "/opt/store/bin";

      directory_system()->create(pathBin);

      strCommand = "unzip -o " + pathStoreZip + " -d " + pathBin + "/";

      printf("%s\n", strCommand.c_str());

      acmenode()->command_system("bash -c \"" + strCommand + "\"", std_inline_log());

      ::file::path pathSPECS;

      pathSPECS = pathRpmbuild / "SPECS";

      ::file::path pathSpec;

      pathSpec = pathSPECS / "store.spec";

      ::property_set set;

      set["%RELEASE_NUMBER%"] = strReleaseNumberDst;

      file_system()->find_replace(pathSpec, set);

      directory_system()->change_current(pathSOURCES);

      strCommand = "tar -czvf " + strPackageNameDst + ".tar.gz " + strPackageNameDst;

      printf("%s\n", strCommand.c_str());

      acmenode()->command_system("bash -c \"" + strCommand + "\"", std_inline_log());

      directory_system()->change_current(pathSPECS);

      strCommand = "rpmbuild -ba store.spec";

      printf("%s\n", strCommand.c_str());

      acmenode()->command_system("bash -c \"" + strCommand + "\"", std_inline_log());

      ::file::path pathRPMS;

      pathRPMS = pathRpmbuild / "RPMS";

      ::file::listing listing;

      listing.set_pattern_file_listing(pathRPMS/"x86_64", {"*.rpm"});

      directory_system()->enumerate(listing);

      if(listing.size() != 1)
      {

         fprintf(stderr, "There should be only one rpm file and it must exist!!");

         m_iExitCode = -1;

      }
      else
      {

         strCommand = "cp " + listing.first() + " " + pathStoreFolder + "/store_x86_64.rpm";

         printf("%s\n", strCommand.c_str());

         m_iExitCode = acmenode()->command_system("bash -c \"" + strCommand + "\"", std_inline_log());

      }

   }


} // namespace application_build_helper



