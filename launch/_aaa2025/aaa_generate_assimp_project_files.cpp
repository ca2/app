// Created by camilo on 2023-05-15 10:35 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/node.h"


namespace application_build_helper
{


   void application::generate_assimp_project_files()
   {
      
      ::file::path pathAssimpProjectFiles;
      
#ifdef WINDOWS
      
      pathAssimpProjectFiles = "C:\\third";
      
#else
      
      pathAssimpProjectFiles = directory_system()->home() /
      "third";
      
#endif
      
      pathAssimpProjectFiles /= "assimp_project_files";

      if (!directory_system()->is(pathAssimpProjectFiles))
      {

         directory_system()->create(pathAssimpProjectFiles);

      }

      directory_system()->change_current(pathAssimpProjectFiles);

      if (!directory_system()->is(pathAssimpProjectFiles / "assimp_assimp"))
      {

         acmenode()->command_system("git clone https://github.com/assimp/assimp assimp_assimp", 1_hour);

      }

      directory_system()->change_current(pathAssimpProjectFiles);

      if (!file_system()->exists(pathAssimpProjectFiles / "Assimp.sln"))
      {

         acmenode()->command_system("cmake -S" + (pathAssimpProjectFiles / "assimp_assimp") + " -B " +  pathAssimpProjectFiles, 2_hour);

      }

   }


} // namespace application_build_helper
