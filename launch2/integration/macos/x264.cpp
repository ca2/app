#include "framework.h"
#include "x264.h"
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

   
      x264::x264()
      {
         
      }


      x264::~x264()
      {
         
      }


      void x264::initialize(::particle * pparticle)
      {
         
         ::console_integration::macos::build::initialize(pparticle);
         ::console_integration::x264::initialize(pparticle);
         
      }


      void x264::initialize_x264(
                                 const ::scoped_string & scopedstrArch,
                                 const ::scoped_string & scopedstrTargetting,
                                 const ::scoped_string & scopedstrTarget,
                                 const ::scoped_string & scopedstrHost)
      {
         
         initialize_macos_build(scopedstrArch);
         
         m_strArch = scopedstrArch;
         m_strTargetting = scopedstrTargetting;
         m_strTarget = scopedstrTarget;
         m_strHost = scopedstrHost;
         
      }


      void x264::build()
      {
         
        if(m_papplication->m_strPlatform.is_empty())
         {
            
            initialize_x264("x86_64", "x86_64-apple-macos10.13", "10.13", "x86_64-apple-darwin");
            
            build();
            
            initialize_x264("arm64", "arm64-apple-macos11.0", "11.0", "arm64-apple-darwin");
            
            build();
            
            lipo();
           
            auto pathPrefixInclude = m_papplication->m_pathPrefix / "include";

            auto pathOperatingSystemIncludeFolder = acmedirectory()->home() /"workspace/operating_system/operating_system-macos/include";
            
            m_papplication->bash("cp -f " + pathPrefixInclude + "/* " + pathOperatingSystemIncludeFolder + "/");
            
            return;
            
         }
            
         prepare();
         
         //clean();

         if (!m_papplication->m_bOnlyInstall)
         {

            download();

            configure();

            compile();

         }

         install();
         
      }


      void x264::clean()
      {
         
         m_papplication->clean();
         
      }


      void x264::prepare()
      {
         
         m_papplication->prepare();
         
         if(m_papplication->m_pathPrefix.is_empty())
         {
            
            m_papplication->m_pathPrefix = calculate_prefix_path(m_papplication->m_strPlatform, m_papplication->m_strConfiguration);
            
         }
         
         m_papplication->prepare_compile_and_link_environment();
         
         m_papplication->create_source_directory();
         
      }


      void x264::download()
      {
         
         m_papplication->create_source_directory();
         
         m_papplication->change_to_source_directory();
         
         m_papplication->git_clone();
         
      }


      void x264::configure()
      {
         
         m_papplication->change_to_source_directory();
         
         string strPrefix = m_papplication->prepare_path(m_papplication->m_pathPrefix);
         
         ::string strCommand;
         
         strCommand = "./configure --prefix="+m_papplication->m_pathPrefix+" --host="+m_strHost+" --enable-pic --enable-shared --enable-static --extra-cflags=\"-target " + m_strTargetting + "\"";
         
         auto iExitCode = m_papplication->bash(strCommand);
         
         if(iExitCode != 0)
         {
          
            throw ::exception(error_failed);
            
         }
         
      }


      void x264::compile()
      {
         
         m_papplication->change_to_source_directory();
         
         m_papplication->bash("make -j");
         
      }


      void x264::install()
      {
         
         m_papplication->change_to_source_directory();
         
         m_papplication->command_system("make install");
         
         auto pathOperatingSystemStorageFolder = m_papplication->m_pathOperatingSystemStorageFolder / m_papplication->m_strPlatform ;

         acmedirectory()->create(pathOperatingSystemStorageFolder / "library");

         ::string strCommand1 ="cp -f " + (m_papplication->m_pathPrefix / "lib/*.a") + " " + (pathOperatingSystemStorageFolder / "library") ;
         
         m_papplication->bash(strCommand1);
         
         ::string strDylib = "lib" + m_papplication->m_strName + ".dylib";

         ::string strDylibOriginal = "lib" + m_papplication->m_strName + "-original.dylib";

         auto path = m_papplication->m_pathPrefix / "lib" / strDylib;

         auto pathOriginal = m_papplication->m_pathPrefix / "lib" / strDylibOriginal;
         
         ::string strCommand2 ="mv -f " + path + " " + pathOriginal;

         m_papplication->bash(strCommand2);

         acmefile()->copy(path, pathOriginal, true);
         
         ::string strCommand3 ="install_name_tool -id @executable_path/" + strDylib + " " + path;

         m_papplication->bash(strCommand3);

         m_mappath[m_papplication->m_strName][m_papplication->m_strPlatform] = path;

      }


   } // namespace macos


} // namespace console_integration



