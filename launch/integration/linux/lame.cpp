#include "framework.h"
#include "lame.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/integration_context.h"
#include "acme/platform/node.h"


namespace console_integration
{


   namespace linux
   {

   
      lame::lame()
      {
         
      }


      lame::~lame()
      {
         
      }


      void lame::initialize(::particle * pparticle)
      {
         
         ::console_integration::linux::build::initialize(pparticle);
         ::console_integration::lame::initialize(pparticle);
         
      }

//
//      void lame::initialize_lame(
//                                 const ::scoped_string & scopedstrArch,
//                                 const ::scoped_string & scopedstrTargetting,
//                                 const ::scoped_string & scopedstrTarget,
//                                 const ::scoped_string & scopedstrHost)
//      {
//         
//         initialize_macos_build(scopedstrArch);
//         
//         m_strArch = scopedstrArch;
//         m_strTargetting = scopedstrTargetting;
//         m_strTarget = scopedstrTarget;
//         m_strHost = scopedstrHost;
//         
//      }


      void lame::build()
      {
         
        if(m_papplication->m_strPlatform.is_empty())
         {
            
            _001MakeInitialize("x86_64", "x86_64-apple-macos10.13", "10.13", "x86_64-apple-darwin");
            
            build();
            
            _001MakeInitialize("arm64", "arm64-apple-macos11.0", "11.0", "aarch64-apple-darwin");
            
            build();
            
            lipo();
            
            auto pathOperatingSystemIncludeFolder = directory_system()->home() /"workspace/operating_system/operating_system-linux/include";
            ;
            
            auto strPrefix = m_papplication->prepare_path(m_papplication->m_pathPrefix);
            
            auto pathInclude = m_papplication->prepare_path(pathOperatingSystemIncludeFolder);
            
            directory_system()->create(pathInclude /"lame");
            //auto strStorage = m_papplication->prepare_path(pathOperatingSystemStorageFolder);
            
            m_papplication->bash("cp -Rf " + strPrefix + "/include/lame/* " + pathInclude + "/lame/");
            
            return;
            
         }
            
         prepare();
         
         //clean();
         
         download();
         
         configure();
         
         compile();

         install();
         
      }


      void lame::clean()
      {
         
         m_papplication->clean();
         
      }


      void lame::prepare()
      {
         
         m_papplication->prepare();
         
         if(m_papplication->m_pathPrefix.is_empty())
         {
            
            m_papplication->m_pathPrefix = calculate_prefix_path(m_papplication->m_strPlatform, m_papplication->m_strConfiguration);
            
         }
         
         m_papplication->prepare_compile_and_link_environment();
         
         m_papplication->create_source_directory();
         
      }


      void lame::download()
      {
         
         m_papplication->create_source_directory();
         
         m_papplication->change_to_source_directory();
         
         m_papplication->git_clone();
         
      }


      void lame::configure()
      {
         
         m_papplication->change_to_source_directory();
         
         string strPrefix = m_papplication->prepare_path(m_papplication->m_pathPrefix);
         
//         ::string strCommand;
//
////            ./configure --prefix=$PREFIX --enable-shared --host=$HOST CC="cc -target $TARGETTING" CXX="c++ -target $TARGETTING"
//
//         strCommand = "./configure --prefix="+m_papplication->m_pathPrefix+" --host="+m_strHost+" --enable-pic --enable-shared --enable-static --extra-cflags=\"-target " + m_strTargetting + "\"";
//
//         auto iExitCode = m_papplication->bash(strCommand);
//
//         if(iExitCode != 0)
//         {
//
//            throw ::exception(error_failed);
//
//         }
         
         _001MakeConfigure(false, "");
         
      }


      void lame::compile()
      {
         
         m_papplication->change_to_source_directory();
         
         m_papplication->bash("make -j");
         
      }


      void lame::install()
      {
         
         _001MakeInstall(".0");
         
//         m_papplication->change_to_source_directory();
//
//         m_papplication->command_system("make install");
//
//         auto pathOperatingSystemStorageFolder = m_papplication->m_pathOperatingSystemStorageFolder / m_papplication->m_strPlatform ;
//
//         directory_system()->create(pathOperatingSystemStorageFolder / "library");
//
//         ::string strCommand1 ="cp -f " + (m_papplication->m_pathPrefix / "lib/*.a") + " " + (pathOperatingSystemStorageFolder / "library") ;
//
//         m_papplication->bash(strCommand1);
//
//         ::string strDylib = "lib" + m_papplication->m_strName + ".dylib";
//
//         ::string strDylibOriginal = "lib" + m_papplication->m_strName + "-origianl.dylib";
//
//         auto path = m_papplication->m_pathPrefix / "lib" / strDylib;
//
//         auto pathOriginal = m_papplication->m_pathPrefix / "lib" / strDylibOriginal;
//
//         ::string strCommand2 ="mv -f " + path + " " + pathOriginal;
//
//         m_papplication->bash(strCommand2);
//
//         file_system()->copy(path, pathOriginal, true);
//
//         m_mappath[m_papplication->m_strPlatform] = path;

      }


   } // namespace linux


} // namespace console_integration



