#include "framework.h"
#include "freetype.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/integration_context.h"
#include "acme/platform/node.h"


namespace console_integration
{


   namespace macos
   {

   
      freetype::freetype()
      {
         
      }


      freetype::~freetype()
      {
         
      }


      void freetype::initialize(::particle * pparticle)
      {
         
         ::console_integration::macos::build::initialize(pparticle);
         ::console_integration::freetype::initialize(pparticle);
         
      }

//
//      void freetype::initialize_freetype(
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
//

      void freetype::build()
      {
         
        if(m_pcontext->m_strPlatform.is_empty())
         {
            
            _001MakeInitialize("x86_64", "x86_64-apple-macos10.13", "10.13", "x86_64-apple-darwin");
            
            build();
            
            _001MakeInitialize("arm64", "arm64-apple-macos11.0", "11.0", "arm64-apple-darwin");
            
            build();
            
            lipo();
            
            auto pathOperatingSystemIncludeFolder = acmedirectory()->home() /"workspace/operating_system/operating_system-macos/include";
            ;
            
            auto strPrefix = m_pcontext->prepare_path(m_pcontext->m_pathPrefix);
            
            auto pathInclude = m_pcontext->prepare_path(pathOperatingSystemIncludeFolder);
            
            acmedirectory()->create(pathInclude /"freetype2");
            //auto strStorage = m_pcontext->prepare_path(pathOperatingSystemStorageFolder);
            
            m_pcontext->bash("cp -Rf " + strPrefix + "/include/freetype2/* " + pathInclude + "/freetype2/");

            
            return;
            
         }
            
         prepare();
         
         //clean();
         
         download();
         
         configure();
         
         compile();

         install();
         
      }


      void freetype::clean()
      {
         
         m_pcontext->clean();
         
      }


      void freetype::prepare()
      {
         
         m_pcontext->prepare();
         
         if(m_pcontext->m_pathPrefix.is_empty())
         {
            
            m_pcontext->m_pathPrefix = calculate_prefix_path(m_pcontext->m_strPlatform, m_pcontext->m_strConfiguration);
            
         }
         
         m_pcontext->prepare_compile_and_link_environment();
         
         m_pcontext->create_source_directory();
         
      }


      void freetype::download()
      {
         
         m_pcontext->create_source_directory();
         
         m_pcontext->change_to_source_directory();
         
         m_pcontext->git_clone();
         
      }


      void freetype::configure()
      {
         
         m_pcontext->change_to_source_directory();
         
         string strPrefix = m_pcontext->prepare_path(m_pcontext->m_pathPrefix);
         
//         ::string strCommand;
//
//         strCommand = "./configure --prefix="+m_pcontext->m_pathPrefix+" --host="+m_strHost+" --enable-pic --enable-shared --enable-static --extra-cflags=\"-target " + m_strTargetting + "\"";
//
//         auto iExitCode = m_pcontext->bash(strCommand);
//
//         if(iExitCode != 0)
//         {
//
//            throw ::exception(error_failed);
//
//         }
         
         _001MakeConfigure(true, "-enable-pic");
         
      }


      void freetype::compile()
      {
         
         m_pcontext->change_to_source_directory();
         
         m_pcontext->bash("make -j");
         
      }


      void freetype::install()
      {
         
         _001MakeInstall(".6");
         
//         m_pcontext->change_to_source_directory();
//
//         m_pcontext->command_system("make install");
//
//         auto pathOperatingSystemStorageFolder = m_pcontext->m_pathOperatingSystemStorageFolder / m_pcontext->m_strPlatform ;
//
//         acmedirectory()->create(pathOperatingSystemStorageFolder / "library");
//
//         ::string strCommand1 ="cp -f " + (m_pcontext->m_pathPrefix / "lib/*.a") + " " + (pathOperatingSystemStorageFolder / "library") ;
//
//         m_pcontext->bash(strCommand1);
//
//         ::string strDylib = "lib" + m_pcontext->m_strName + ".dylib";
//
//         ::string strDylibOriginal = "lib" + m_pcontext->m_strName + "-origianl.dylib";
//
//         auto path = m_pcontext->m_pathPrefix / "lib" / strDylib;
//
//         auto pathOriginal = m_pcontext->m_pathPrefix / "lib" / strDylibOriginal;
//
//         ::string strCommand2 ="mv -f " + path + " " + pathOriginal;
//
//         m_pcontext->bash(strCommand2);
//
//         acmefile()->copy(path, pathOriginal, true);
//
//         m_mappath[m_pcontext->m_strPlatform] = path;

      }


   } // namespace macos


} // namespace console_integration



