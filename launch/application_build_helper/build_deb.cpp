// Created by camilo on 2021-12-17 21:01 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application_build_helper.h"
#include "acme/platform/scoped_restore.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/operating_system/process.h"
#include "acme/platform/node.h"


namespace application_build_helper
{


   void application_build_helper::release_store_installer()
   {

      if(m_strInstallerType == "deb")
      {

         build_deb();

      }
      else if(m_strInstallerType == "rpm")
      {

         build_rpm();

      }
      else
      {

         fprintf(stderr, "Unknown (\"%s\") installer type!!", m_strInstallerType.c_str());

         m_iExitCode = -1;

      }


   }


   void application_build_helper::build_deb()
   {

      ::file::path pathHome = acmedirectory()->home();

      ::file::path pathStore = pathHome / "store_0.4_amd64";

      string strCommand = "rm -Rf " + pathStore;

      printf("%s\n", strCommand.c_str());

      acmenode()->command_system("bash -c \"" + strCommand + "\"", std_inline_log());

      strCommand = "cp -Rf " + pathHome + "/cmake/operating_system/tool-linux/build_deb/store_0.4_amd64 " + pathStore;

      printf("%s\n", strCommand.c_str());

      acmenode()->command_system("bash -c \"" + strCommand + "\"", std_inline_log());

      ::file::path pathStoreFolder;

      pathStoreFolder = acmedirectory()->home() / "store";

      pathStoreFolder /= m_strSlashedOperatingSystem;

      ::file::path pathStoreZip;

      pathStoreZip = pathStoreFolder;

      pathStoreZip /= "app-core/store.zip";

      ::file::path pathBin;

      pathBin = pathStore / "opt/store/bin/";

      acmedirectory()->create(pathBin);

      strCommand = "unzip -o " + pathStoreZip + " -d " + pathBin + "/";

      printf("%s\n", strCommand.c_str());

      acmenode()->command_system("bash -c \"" + strCommand + "\"", std_inline_log());

      acmedirectory()->change_current(pathHome);

      strCommand = "dpkg-deb --build --root-owner-group store_0.4_amd64";

      printf("%s\n", strCommand.c_str());

      acmenode()->command_system("bash -c \"" + strCommand + "\"", std_inline_log());

      strCommand = "cp store_0.4_amd64.deb " + pathStoreFolder + "/store_amd64.deb";

      printf("%s\n", strCommand.c_str());

      acmenode()->command_system("bash -c \"" + strCommand + "\"", std_inline_log());

   }


} // namespace application_build_helper



