// Created by camilo on 2023-05-15 10:35 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/node.h"


namespace application_build_helper
{


   void application::generate_assimp_project_files()
   {
      
      ::file::path pathAssimpProjectFiles;
      
#ifdef WINDOWS
      
      pathAssimpProjectFiles = "C:\\third";
      
#else
      
      pathAssimpProjectFiles = acmedirectory()->home() /
      "third";
      
#endif
      
      pathAssimpProjectFiles /= "assimp_project_files";

      if (!acmedirectory()->is(pathAssimpProjectFiles))
      {

         acmedirectory()->create(pathAssimpProjectFiles);

      }

      acmedirectory()->change_current(pathAssimpProjectFiles);

      if (!acmedirectory()->is(pathAssimpProjectFiles / "assimp_assimp"))
      {

         acmenode()->command_system("git clone https://github.com/assimp/assimp assimp_assimp", 1_hour);

      }

      acmedirectory()->change_current(pathAssimpProjectFiles);

      if (!acmefile()->exists(pathAssimpProjectFiles / "Assimp.sln"))
      {

         acmenode()->command_system("cmake -S" + (pathAssimpProjectFiles / "assimp_assimp") + " -B " +  pathAssimpProjectFiles, 2_hour);

      }

   }


} // namespace application_build_helper
