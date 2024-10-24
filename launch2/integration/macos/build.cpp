//
//  build_helper.cpp
//  integration_console_integration
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 17:55
//
#include "framework.h"
#include "build.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/link.h"
#include "acme/platform/integration_context.h"
#include "acme/platform/node.h"


namespace console_integration
{


   namespace macos
   {


      build::build()
      {

      }


      build::~build()
      {

      }


      void build::initialize(::particle* pparticle)
      {

         ::console_integration::build::initialize(pparticle);


         m_papplication->m_pathOperatingSystemStorageFolder = directory_system()->home() / "workspace/operating_system/storage-macos";

      }


      void build::initialize_macos_build(const ::scoped_string& scopedstrPlatform)
      {

         m_papplication->m_strPlatform = scopedstrPlatform;
         m_papplication->m_pathPrefix = m_pathPrefixBase /
            m_papplication->m_strPlatform / m_papplication->m_strConfiguration / "build";

         if (m_papplication->m_strConfiguration.case_insensitive_contains("static"))
         {

            m_papplication->m_pathStaticPrefix = m_papplication->m_pathPrefix;

         }
         else
         {

            m_papplication->m_pathStaticPrefix = m_pathPrefixBase /
               m_papplication->m_strPlatform / ("Static" + m_papplication->m_strConfiguration) / "build";

         }

      }


      void build::_001MakeInitialize(
         const ::scoped_string& scopedstrArch,
         const ::scoped_string& scopedstrTargetting,
         const ::scoped_string& scopedstrTarget,
         const ::scoped_string& scopedstrHost)
      {

         initialize_macos_build(scopedstrArch);

         m_strArch = scopedstrArch;
         m_strTargetting = scopedstrTargetting;
         m_strTarget = scopedstrTarget;
         m_strHost = scopedstrHost;

      }


      ::file::path build::calculate_prefix_path(const ::scoped_string& scopedstrPlatform, const ::scoped_string& scopedstrConfiguration)
      {

         return m_pathPrefixBase / scopedstrPlatform / m_papplication->m_strConfiguration / "build";


      }


      void build::_001MakeConfigure(bool bAutogen, const ::scoped_string& scopedstrExtra)
      {

         acmenode()->unset_environment_variable("OS_ACTIVITY_DT_MODE");

         if (m_strTarget.has_char())
         {

            acmenode()->set_environment_variable("MACOSX_DEPLOYMENT_TARGET", m_strTarget);

         }

         //         auto iExitCode0 = m_papplication->bash("set > ~/a-set.txt");
         //
         //         throw ::exception(error_failed);

                  //::string str = "#!/bin/bash\n";

         if (bAutogen)
         {

            ::string strCommand1;

            strCommand1 = "./autogen.sh";

            //            str += strCommand1 + "\n";

            auto iExitCode1 = m_papplication->bash(strCommand1);

            if (iExitCode1 != 0)
            {

               throw ::exception(error_failed);

            }

            m_papplication->bash("set > ~/set-autogen.txt");

         }

         ::string strCommand2;

         strCommand2 = "./configure --prefix=\"" + m_papplication->m_pathPrefix + "\" --host=\"" + m_strHost + "\" --enable-shared " + scopedstrExtra + " CC=\"cc -target " + m_strTargetting + "\" CXX=\"c++ -target " + m_strTargetting + "\"";
         //str += strCommand2 + "\n";
//            ./autogen.sh
//            ./configure --prefix=$PREFIX --enable-shared --host=$HOST CC="cc -target $TARGETTING" CXX="c++ -target $TARGETTING"

         auto iExitCode2 = m_papplication->bash(strCommand2);

         if (iExitCode2 != 0)
         {

            throw ::exception(error_failed);

         }

         m_papplication->bash("set > ~/set-configure.txt");

         //         str+="make -j\n";
         //
         //         file_system()->put_contents(m_papplication->m_pathSource /"build", str);
         //         m_papplication->bash("chmod +x build");
         //         m_papplication->bash("./build");
      }


      void build::_001MakeInstall(const ::scoped_string& scopedstrLibraryModifier)
      {

         m_papplication->change_to_source_directory();

         m_papplication->command_system("make install");

         auto pathOperatingSystemStorageFolderPlatform = m_papplication->m_pathOperatingSystemStorageFolder / m_papplication->m_strPlatform;

         //         make -j 8
         //         make install
         //         unlink $PREFIX/lib/libfdk-aac.dylib
         //         mv $PREFIX/lib/libfdk-aac.2.dylib $PREFIX/lib/libfdk-aac.dylib
         //         install_name_tool -id @executable_path/libfdk-aac.dylib $PREFIX/lib/libfdk-aac.dylib

         directory_system()->create(pathOperatingSystemStorageFolderPlatform / "library");
         directory_system()->create(m_papplication->m_pathStaticPrefix / "library");

         //         ::string strCommand1 ="cp -f " + (m_papplication->m_pathPrefix / "lib/*.a") + " " + (pathOperatingSystemStorageFolder / "library") ;
         //
         //         m_papplication->bash(strCommand1);

         ::string strDylib = "lib" + m_papplication->m_strName + ".dylib";

         ::string strDylib2 = "lib" + m_papplication->m_strName + scopedstrLibraryModifier + ".dylib";

         auto path = m_papplication->m_pathPrefix / "lib" / strDylib;

         auto path2 = m_papplication->m_pathPrefix / "lib" / strDylib2;

         ::string strCommand1 = "unlink " + path;

         m_papplication->bash(strCommand1);

         ::string strCommand2 = "mv " + path2 + " " + path;

         m_papplication->bash(strCommand2);

         ::string strCommand3 = "install_name_tool -id @executable_path/" + strDylib + " " + path;

         m_papplication->bash(strCommand3);

         m_mappath[m_papplication->m_strName][m_papplication->m_strPlatform] = path;

         ::string strA = "lib" + m_papplication->m_strName + ".a";

         auto pathA = m_papplication->m_pathPrefix / "lib" / strA;

         auto pathStorageA = pathOperatingSystemStorageFolderPlatform / "library" / strA;

         file_system()->copy(pathStorageA, pathA, true);

         auto pathB = m_papplication->m_pathStaticPrefix / "lib" / strA;

         ::string strCommand4 = "mv " + pathA + " " + pathB;

         m_papplication->bash(strCommand4);

      }


      void build::lipo(const ::scoped_string& scopedstrLibraryName)
      {

         ::string strLibraryName(scopedstrLibraryName);

         if (strLibraryName.is_empty())
         {

            strLibraryName = m_papplication->m_strName;

         }

         //   ARM_PATH=$BASE_PREFIX/arm64/lib/lib$LIBNAME.dylib
         //   X86_PATH=$BASE_PREFIX/x86_64/lib/lib$LIBNAME.dylib

         ::string strDylib = "lib" + strLibraryName + ".dylib";

         auto pathOutput = directory_system()->home() / "workspace/operating_system/storage-macos/library" / strDylib;

         auto pathFolder = pathOutput.folder();

         directory_system()->create(pathFolder);

         auto pathArm = m_mappath[strLibraryName]["arm64"];

         auto pathX64 = m_mappath[strLibraryName]["x86_64"];

         ::string strCommand = "lipo -create -arch arm64 \"" + pathArm + "\" -arch x86_64 \"" + pathX64 + "\" -output \"" + pathOutput + "\"";

         m_papplication->bash(strCommand);

         //   auto pathOperatingSystemStorageFolder = m_papplication->m_pathOperatingSystemStorageFolder / m_papplication->m_strPlatform / m_papplication->m_strConfiguration;
         //
         //   directory_system()->create(pathOperatingSystemIncludeFolder / "include");
         //
         //   directory_system()->create(pathOperatingSystemStorageFolder / "binary");
         //
         //   directory_system()->create(pathOperatingSystemStorageFolder / "library");


      }


      void build::remap_dependencies(const ::scoped_string& scopedstrLibraryName)
      {


      }


      void build::remap_dependency(const ::scoped_string& scopedstrLibraryName,
         const ::scoped_string& scopedstrLibraryDependency)
      {
         auto pathDependency = library_source_path(scopedstrLibraryDependency);

         if (pathDependency.has_char())
         {
            ::string str = "lib" + scopedstrLibraryName + ".dylib";

            ::file::path path = m_papplication->m_pathPrefix / "lib" / ("lib" + scopedstrLibraryName + ".dylib");

            ::string strDependency = "lib" + scopedstrLibraryDependency + ".dylib";

            {

               ::string strCommand = "install_name_tool -change " + pathDependency + " @executable_path/" + strDependency + " " + path;

               m_papplication->bash(strCommand);

            }

            ::file::path pathName = pathDependency.name();

            auto pathFolder = pathDependency.folder();

            ::string strExtension = pathDependency.final_extension();

            pathName.ends_eat("." + strExtension);

            while (true)
            {

               ::string strExtension1 = pathName.final_extension();

               if (strExtension1.is_empty())
               {

                  break;

               }

               pathName.ends_eat("." + strExtension1);

               auto pathDependency = pathFolder / (pathName + "." + strExtension);

               ::string strCommand = "install_name_tool -change " + pathDependency + " @executable_path/" + strDependency + " " + path;

               m_papplication->bash(strCommand);

            }


         }

      }


      ::file::path build::library_source_path(const ::scoped_string& scopedstrLibraryName)
      {

         ::file::path path;

         path = m_papplication->m_pathPrefix / "lib" / ("lib" + scopedstrLibraryName + "-original.dylib");

         auto plink = path_system()->resolve_link(path);

         if (plink)
         {

            return plink->m_pathTarget;

         }

         return {};

      }


   } // namespace macos


} // namespace console_integration





