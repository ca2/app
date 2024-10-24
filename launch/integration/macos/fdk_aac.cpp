#include "framework.h"
#include "fdk_aac.h"
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

   
      fdk_aac::fdk_aac()
      {
         
      }


      fdk_aac::~fdk_aac()
      {
         
      }


      void fdk_aac::initialize(::particle * pparticle)
      {
         
         ::console_integration::macos::build::initialize(pparticle);
         ::console_integration::fdk_aac::initialize(pparticle);
         
      }


//      void fdk_aac::initialize_fdk_aac(
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


      void fdk_aac::build()
      {
         
//         m_papplication->zsh("_build_fdk_aac_shared");
//         
//         return;
         
        if(m_papplication->m_strPlatform.is_empty())
         {

            _001MakeInitialize("x86_64", "x86_64-apple-macos10.13", "10.13", "x86_64-apple-darwin");
            
            build();
            
            _001MakeInitialize("arm64", "arm64-apple-macos11.0", "11.0", "arm64-apple-darwin");
            
            build();
            
            lipo();
            
            auto pathOperatingSystemIncludeFolder = acmedirectory()->home() /"workspace/operating_system/operating_system-macos/include";
            ;
            
            auto strPrefix = m_papplication->prepare_path(m_papplication->m_pathPrefix);
            
            auto pathInclude = m_papplication->prepare_path(pathOperatingSystemIncludeFolder);
            
            acmedirectory()->create(pathInclude /"fdk-aac");
            //auto strStorage = m_papplication->prepare_path(pathOperatingSystemStorageFolder);
            
            m_papplication->bash("cp -Rf " + strPrefix + "/include/fdk-aac/* " + pathInclude + "/fdk-aac/");
            
            return;
            
         }
            
         prepare();
         
         //clean();
         
         download();
         
//         ::string strScript;
//
//         strScript += "#!/bin/zsh\n";
//         strScript += "\n";
//         strScript += "\n";
//
//         {
//                     ::string strCommand1;
//
//                     strCommand1 = "./autogen.sh";
//
//                     strScript += strCommand1 + "\n";
//
////                     auto iExitCode1 = m_papplication->zsh(strCommand1);
////
////                     if(iExitCode1 != 0)
////                     {
////
////                        throw ::exception(error_failed);
////
////                     }
//
//                  }
//
//         {
//
//            ::string strCommand;
//
//            strCommand = "./configure --prefix="+m_papplication->m_pathPrefix+" --host="+m_strHost+" --enable-shared " + " CC=\"cc -target " + m_strTargetting + "\" CXX=\"c++ -target " + m_strTargetting + "\"";
//            strScript += strCommand + "\n";
//
//         }
//         //            ./autogen.sh
//         //            ./configure --prefix=$PREFIX --enable-shared --host=$HOST CC="cc -target $TARGETTING" CXX="c++ -target $TARGETTING"
//
////                  auto iExitCode2 = m_papplication->zsh(strCommand2);
////
////                  if(iExitCode2 != 0)
////                  {
////
////                     throw ::exception(error_failed);
////
////                  }
//
//         strScript +="make -j\n";
//         strScript +="make install\n";
//         strScript +="\n";
//         strScript +="\n";
//         strScript +="\n";
//         strScript +="\n";
//         //
//         acmefile()->put_contents(m_papplication->m_pathSource /"build", strScript);
//         m_papplication->zsh("chmod +x build");
//         m_papplication->zsh("./build");

         configure();
         
         compile();

         install();
         
      }


      void fdk_aac::clean()
      {
         
         m_papplication->clean();
         
      }


      void fdk_aac::prepare()
      {
         
         m_papplication->prepare();
         
         if(m_papplication->m_pathPrefix.is_empty())
         {
            
            m_papplication->m_pathPrefix = calculate_prefix_path(m_papplication->m_strPlatform, m_papplication->m_strConfiguration);
            
         }
         
         m_papplication->prepare_compile_and_link_environment();
         
         m_papplication->create_source_directory();
         
      }


      void fdk_aac::download()
      {
         
         m_papplication->create_source_directory();
         
         m_papplication->change_to_source_directory();
         
         m_papplication->git_clone();
         
      }


      void fdk_aac::configure()
      {
         
         m_papplication->change_to_source_directory();
         
         string strPrefix = m_papplication->prepare_path(m_papplication->m_pathPrefix);
         
//         m_papplication->zsh("glibtoolize");
//         
//         m_papplication->zsh("autoreconf -fiv");
         
         _001MakeConfigure(true, "");
         
      }


      void fdk_aac::compile()
      {
         
         m_papplication->change_to_source_directory();
         
         //m_papplication->zsh("set > ~/set-compile.txt");
         
         //throw ::exception(error_failed);
         
         m_papplication->bash("make -j");
         
//         ::string strScript;
//
//         strScript += "#!/bin/bash\n";
//         //strScript += "make clean\n";
//         strScript += "which ./libtool\n";
//         strScript += "make -j\n";
//         strScript += "which ./libtool\n";
//
//         acmefile()->put_contents(m_papplication->m_pathSource /"call_make", strScript);
//         m_papplication->bash("chmod +x call_make");
//         m_papplication->bash("./call_make");

         
      }


      void fdk_aac::install()
      {
        
         _001MakeInstall(".2");
        
      }


   } // namespace macos


} // namespace console_integration



