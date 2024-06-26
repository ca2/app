// From impact.cpp on 2023-01-15 09:46 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "ffmpeg.h"
#include "x264.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/url.h"
#include "acme/platform/nano_http.h"
#include "acme/platform/integration_context.h"
//#include "apex/platform/node.h"
//#include "apex/platform/os_context.h"


#define Return return
#define If if


namespace console_integration
{


   namespace macos
   {

   
      ffmpeg::ffmpeg()
      {
         
         m_bX264 = true;
         m_bX265 = false;
         m_bFdkAac = true;
         m_bLame = true;
         m_bFreetype = true;
      
      }


      ffmpeg::~ffmpeg()
      {
         
      }


      void ffmpeg::initialize(::particle * pparticle)
      {
         
         ::console_integration::macos::build::initialize(pparticle);

         ::console_integration::ffmpeg::initialize(pparticle);
         
      }


      void ffmpeg::build()
      {
         
         if(m_pcontext->m_strRelease.is_empty())
         {
            
            property_set set;
            
            auto psystem = acmesystem();
            
            auto purl = psystem->url();
            
            purl->defer_raw_http(set);
            
            set["disable_common_name_cert_check"] = true;
            
            ::string strRelease = acmesystem()->http_text("https://raw.githubusercontent.com/FFmpeg/FFmpeg/master/RELEASE", set);
            
            strRelease.trim();
            
            strRelease.case_insensitive_ends_eat(".git");
            
            m_pcontext->m_strRelease = strRelease;
            
         }
         
         if(m_pcontext->m_strPlatform.is_empty())
         {
            
            build_dependencies();
            
            _001MakeInitialize("x86_64", "x86_64-apple-macos10.13", "10.13", "x86_64-apple-darwin");
            
            build();
               
            _001MakeInitialize("arm64", "arm64-apple-macos11.0", "11.0", "arm64-apple-darwin");
            
            build();
            
//            remap_dependencies("avcodec");
//            remap_dependencies("avdevice");
//            remap_dependencies("avfilter");
//            remap_dependencies("avformat");
//            remap_dependencies("avutil");
//            remap_dependencies("swresample");
//            remap_dependencies("swscale");
            
            lipo("avcodec");
            lipo("avdevice");
            lipo("avfilter");
            lipo("avformat");
            lipo("avutil");
            lipo("swresample");
            lipo("swscale");
            
            while (true)
            {
   
               printf("Enter q to quit.\n");
   
               if (getchar() == 'q')
               {
   
                  break;
   
               }
   
            }
            
            return;
            
         }

         prepare();
         
         //acmedirectory()->change_current(m_pcontext->m_pathFolder);
         
         auto pathConfigure = m_pcontext->m_pathSource / "configure";
         
         if(!acmefile()->exists(pathConfigure))
         {
            
            download();
            
            configure();
            
            compile();
            
         }
         
         install();
         
         remap_dependencies("avcodec");
         remap_dependencies("avdevice");
         remap_dependencies("avfilter");
         remap_dependencies("avformat");
         remap_dependencies("avutil");
         remap_dependencies("swresample");
         remap_dependencies("swscale");

         
      }


      void ffmpeg::prepare()
      {
        
         m_pcontext->prepare();
         
         if (m_pcontext->m_strPlatform == "x86_64")
         {
            
            m_strArch = "x86_64";
            
         }
         else if (m_pcontext->m_strPlatform == "arm64")
         {
            
            m_strArch = "aarch64";
            
         }
         else
         {
            
            throw ::exception(error_failed, "Unsupported Platform \"" + m_pcontext->m_strPlatform + "\"?!?");
            
         }
         
         if (m_pcontext->m_strConfiguration.case_insensitive_contains("Debug"))
         {
            
            m_strDebug = "--enable-debug";
            
         }
         else
         {
            
            m_strDebug = "--disable-debug";
            
         }
         
//         if (m_pcontext->m_strConfiguration.case_insensitive_contains("Static"))
//         {
//            
//            m_strShared = "";
//            
//            m_strStatic = "";
//            
//         }
//         else
//         {
//            
//            m_strShared = "--enable-shared";
//            
//            m_strStatic = "--disable-static";
//            
//         }
         
         if(m_pcontext->m_strPlatform.case_insensitive_equals("arm64"))
         {
            
            m_strCrossCompile = "--enable-cross-compile";
            
         }
         else
         {
          
            m_strCrossCompile = "";
            
         }
         
         m_pcontext->m_pathPrefix = m_pcontext->m_pathFolder / m_pcontext->m_pathBase / m_pcontext->m_pathPlatformConfiguration / "build";
         
         m_pcontext->prepare_compile_and_link_environment();
       
         m_pcontext->create_source_directory();
         
      }


      void ffmpeg::build_dependencies()
      {
         
         if(m_bX264 && !acmedirectory()->is(m_pcontext->m_pathSource / "x264"))
         {
            
            build_x264();
            
         }

         if(m_bX265 && !acmedirectory()->is(m_pcontext->m_pathSource / "x265"))
         {
            
            build_x265("StaticRelease");
            
            build_x265("Release");
            
         }
         
         if(m_bFdkAac && !acmedirectory()->is(m_pcontext->m_pathSource / "fdk-aac"))
         {
            
            build_fdk_aac();
            
         }

         if(m_bLame && !acmedirectory()->is(m_pcontext->m_pathSource / "mp3lame"))
         {
            
            build_lame();
            
         }

         if(m_bFreetype && !acmedirectory()->is(m_pcontext->m_pathSource / "freetype"))
         {
            
            build_freetype();
            
         }
         
      }


      void ffmpeg::build_x264()
      {
         
         ::file::path pathDependencyPrefixBase =
         m_pcontext->m_pathFolder /
         m_pcontext->m_strName /
         m_pcontext->m_strRelease;
         
         ::string strParameters;
         
         strParameters = "x264 " + m_pcontext->m_strConfiguration;
         
         strParameters += " \"" + pathDependencyPrefixBase + "\"";
         
         ::string strCommand;
         
         strCommand = acmedirectory()->home() / "bin" / "application_build_helper " + strParameters;
         
         //      auto functionTrace = [&](auto etracelevel, auto& str)
         //      {
         //
         //         m_strax264.append_format("%c: %s\n", trace_level_letter(etracelevel), str.c_str());
         //
         //         std_inline_log()(etracelevel, str);
         //
         //      };
         
         m_pcontext->bash(strCommand);
         
      }


      void ffmpeg::build_x265(const ::scoped_string & scopedstrConfiguration)
      {
        
         ::file::path pathDependencyPrefixBase =
         m_pcontext->m_pathFolder /
         m_pcontext->m_strName /
         m_pcontext->m_strRelease;
         
         int iExitCode = 0;
         
         ::string strParameters;
         
         //strParameters = "x265 " + m_pcontext->m_strPlatform + " " + m_pcontext->m_strConfiguration;
         
         strParameters = "x265 " + scopedstrConfiguration;
         
         strParameters += " \"" + pathDependencyPrefixBase + "\"";
         
         ::string strCommand;
         
         strCommand = acmedirectory()->home() / "bin" / "application_build_helper " + strParameters;
         
      //   auto functionTrace = [&](auto etracelevel, auto& str)
      //   {
      //
      //      m_strax264.append_format("%c: %s\n", trace_level_letter(etracelevel), str.c_str());
      //
      //      std_inline_log()(etracelevel, str);
      //
      //   };
         
         //acmenode()->command_system(strCommand, functionTrace);
         m_pcontext->bash(strCommand);
         
         if (iExitCode == 0)
         {
            
            m_straX265.add("x265 Completed!!");
            
         }
         else
         {
            
            m_straX265.add("x265 Finished with error exit code: " + ::as_string(iExitCode) + "!");
            
         }
         
         //__construct_new(m_px264);
         
         //m_px264->m_pcontext->m_pathPrefix = m_pcontext->m_pathPrefix;
         
         //m_px264->m_pcontext->m_strPlatform = m_pcontext->m_strPlatform;
         
         //m_px264->m_pcontext->m_strConfiguration = m_pcontext->m_strConfiguration;
         
         //m_px264->build();
         
      }

         
      void ffmpeg::build_fdk_aac()
      {
         
         ::file::path pathDependencyPrefixBase =
         m_pcontext->m_pathFolder /
         m_pcontext->m_strName /
         m_pcontext->m_strRelease;
         
         int iExitCode = 0;
         
         ::string strParameters;
         
         strParameters = "fdk_aac " + m_pcontext->m_strConfiguration;
         
         strParameters += " \"" + pathDependencyPrefixBase + "\"";
         
         ::string strCommand;
         
         strCommand = acmedirectory()->home() / "bin" / "application_build_helper " + strParameters;
         
         m_pcontext->bash(strCommand);
         
         if (iExitCode == 0)
         {
            
            m_straFdkAac.add("fdk_aac Completed!!");
            
         }
         else
         {
            
            m_straFdkAac.add("fdk_aac Finished with error exit code: " + ::as_string(iExitCode) + "!");
            
         }
         
         //__construct_new(m_px264);
         
         //m_px264->m_pcontext->m_pathPrefix = m_pcontext->m_pathPrefix;
         
         //m_px264->m_pcontext->m_strPlatform = m_pcontext->m_strPlatform;
         
         //m_px264->m_pcontext->m_strConfiguration = m_pcontext->m_strConfiguration;
         
         //m_px264->build();
         
      }

   
   void ffmpeg::build_lame()
   {
      
      ::file::path pathDependencyPrefixBase =
      m_pcontext->m_pathFolder /
      m_pcontext->m_strName /
      m_pcontext->m_strRelease;
      
      int iExitCode = 0;
      
      ::string strParameters;
      
      strParameters = "lame " + m_pcontext->m_strConfiguration;
      
      strParameters += " \"" + pathDependencyPrefixBase + "\"";
      
      ::string strCommand;
      
      strCommand = acmedirectory()->home() / "bin" / "application_build_helper " + strParameters;
      
      m_pcontext->bash(strCommand);
      
      if (iExitCode == 0)
      {
         
         m_straLame.add("lame Completed!!");
         
      }
      else
      {
         
         m_straLame.add("lame Finished with error exit code: " + ::as_string(iExitCode) + "!");
         
      }
      
   }

   
   void ffmpeg::build_freetype()
   {
      
      ::file::path pathDependencyPrefixBase =
      m_pcontext->m_pathFolder /
      m_pcontext->m_strName /
      m_pcontext->m_strRelease;
      
      int iExitCode = 0;
      
      ::string strParameters;
      
      strParameters = "freetype " + m_pcontext->m_strPlatform + " " + m_pcontext->m_strConfiguration;
      
      strParameters += " \"" + pathDependencyPrefixBase + "\"";
      
      ::string strCommand;
      
      strCommand = acmedirectory()->home() / "bin" / "application_build_helper " + strParameters;
      
      m_pcontext->bash(strCommand);
      
      if (iExitCode == 0)
      {
         
         m_straFreetype.add("freetype Completed!!");
         
      }
      else
      {
         
         m_straFreetype.add("freetype Finished with error exit code: " + ::as_string(iExitCode) + "!");
         
      }
      
   }


      void ffmpeg::clean()
      {
         
         m_pcontext->clean();
         
      }


      void ffmpeg::download()
      {
         
         m_pcontext->change_to_source_directory();
         
         m_pcontext->git_clone();
         
      }


      void ffmpeg::configure()
      {
         
         m_pcontext->change_to_source_directory();
         
         string strPrefix = m_pcontext->prepare_path(m_pcontext->m_pathPrefix);
         
         string strCommand;
         
         ::string strPkgConfigPath;
         
         ::file::path pathPkgConfigPath;
         
         pathPkgConfigPath = strPrefix;
         
         pathPkgConfigPath /= "lib/pkgconfig";
         
         strPkgConfigPath = pathPkgConfigPath;
         
         //acmenode()->set_environment_variable("PKG_CONFIG_PATH", "'" + strPkgConfigPath + "'");
         
         //m_pcontext->bash("set");
         
         //strCommand += "";
         
         //m_pcontext->bash("export -p > environment_variables.txt");
         
         ::string strConfigureCommand;
         
         
         ::string strMoreFlags;
         
         
//         if (m_pcontext->m_strConfiguration.case_insensitive_contains("Static"))
//         {
//
//            if (m_pcontext->m_strConfiguration.case_insensitive_contains("Debug"))
//            {
//
//               strMoreFlags = "-MTd ";
//
//            }
//            else
//            {
//
//               strMoreFlags = "-MT ";
//
//            }
//
//         }
         
         strConfigureCommand = "./configure --enable-asm --arch=" + m_strArch;
//         if(m_pcontext->m_strPlatform == "x86_64")
//         {
//
//            strConfigureCommand = " --enable-x86asm";
//
//         }
         //strConfigureCommand += " --disable-doc " + m_strShared + " " + m_strStatic;
         strConfigureCommand += " --disable-doc";
         strConfigureCommand += " --enable-shared";
         strConfigureCommand += " --enable-static";
         //strConfigureCommand += " --disable-bzlib --disable-libopenjpeg --disable-iconv --disable-zlib";
         strConfigureCommand += " " + m_strCrossCompile;
         strConfigureCommand += " --disable-bzlib --disable-libopenjpeg";
         strConfigureCommand += " --disable-programs";
         strConfigureCommand += " --enable-gpl --enable-nonfree";
         if(m_bX264)
         {
            strConfigureCommand += " --enable-libx264";
         }
         if(m_bX265)
         {
            strConfigureCommand += " --enable-libx265";
         }
         if(m_bFdkAac)
         {
            strConfigureCommand += " --enable-libfdk-aac";
         }
         if(m_bFreetype)
         {
            strConfigureCommand += " --enable-libfreetype";
         }
         if(m_bLame)
         {
            strConfigureCommand += " --enable-libmp3lame";
         }
         strConfigureCommand += " --prefix=" + strPrefix + " " + m_strDebug;
         strConfigureCommand += " --bindir=\"$PREFIX/bin\"";
         strConfigureCommand += " --extra-ldflags=\"-L" + strPrefix + "/lib -target " + m_strTargetting + "\"";
         strConfigureCommand += " --extra-cflags=\""+strMoreFlags+"-I" + strPrefix + "/include -target " + m_strTargetting + "\"";
         
         acmenode()->set_environment_variable("PKG_CONFIG_PATH", strPkgConfigPath);
//         strCommand += "#!/bin/bash\n";
//         strCommand += "\n";
//         strCommand += "\n";
//         strCommand += "do_configure()\n";
//         strCommand += "{\n";
//         strCommand += "\n";
//         strCommand += "   cd \""+ m_pcontext->m_pathSource + "\"\n";
//         strCommand += strConfigureCommand + "\n";
//         strCommand += "   PKG_CONFIG_PATH='" + windows_bash_path(strPkgConfigPath) + "'\n";
//         strCommand += "   export PKG_CONFIG_PATH\n";
//         strCommand += "   set > test1.txt\n";
//         strCommand += "\n";
//         strCommand += "\n";
//         strCommand += "   make\n";
//         strCommand += "\n";
//         strCommand += "}\n";
//         strCommand += "\n";
//         strCommand += "do_configure\n";
         
//         acmefile()->put_contents(m_pcontext->m_pathSource / "configure2.sh",
//                                  strCommand);
//         m_pcontext->bash("chmod +x configure2.sh");
//         ::string s;
//
//         if (m_pcontext->m_strPlatform.contains("64"))
//         {
//            s += "call \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat\"\n";
//         }
//         else
//         {
//            s += "call \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvars32.bat\"\n";
//         }
//         s += "C:\n";
//         s += "cd \""+m_pcontext->m_pathSource.windows_path()+"\"\n";
//         s += "set CHERE_INVOKING=1\n";
//         s += "set MSYSTEM=MSYS\n";
//         s += "set MSYS2_PATH_TYPE=inherit\n";
//         s += "\"C:\\msys64\\usr\\bin\\bash.exe\" --login -i \"" + m_pcontext->m_pathSource + "/configure2.sh\"\n";
//         //s += "\"C:\\msys64\\msys2.exe\" -l \"" + m_pcontext->m_pathSource2 + "/configure2.sh\"\n";
//         //   C:\
         
         
         //acmefile()->put_contents(m_pcontext->m_pathSource / "vs_call.bat", s);
         
         //trace_function tracefunction = [&](auto etracelevel, auto& str)
         //{
         
         //   //m_strax264.append_format("%c: %s\n", trace_level_letter(etracelevel), str.c_str());
         
         //   std_inline_log()(etracelevel, str);
         
         //};
         
         printf("Current Directory: %s\n", acmedirectory()->get_current().c_str());

         m_pcontext->bash(strConfigureCommand);
         
         //tracefunction.m_timeTimeout = 2.5_hour;
         
         //acmenode()->command_system(m_pcontext->m_pathSource2 +"/vs_call.bat", tracefunction);
         
         //printf("%s\n", s.c_str());
         
         //::file::path pathVsCall = m_pcontext->m_pathSource2 + "/vs_call.bat";
         
         //acmenode()->command_system(pathVsCall.windows_path(), 2.5_hour);
         
///         m_pcontext->bash("export PKG_CONFIG_PATH='" + windows_bash_path(strPkgConfigPath) + "'; " + strConfigureCommand);
         
   //      output_debug_string("test");
         
      }


      void ffmpeg::compile()
      {
         
         // make at configure
         
         m_pcontext->change_to_source_directory();
         
         ::pointer < ::application_build_helper::application > papplication = acmeapplication();
         
         m_pcontext->bash("make" + papplication->m_strMakeOptions);
         
      }


      void ffmpeg::install_lib(const ::scoped_string & scopedstrLibrary)
      {
         
         auto pathSource = m_pcontext->m_pathSource;
         
         auto pathOperatingSystemStorageFolder = m_pcontext->m_pathOperatingSystemStorageFolder / m_pcontext->m_strConfiguration;
         
         auto strSource = m_pcontext->prepare_path(pathSource);
         
         auto strStorage = m_pcontext->prepare_path(pathOperatingSystemStorageFolder);
         
         ::string strDylib = "lib" + scopedstrLibrary + ".dylib";

         ::string strDylibOriginal = "lib" + scopedstrLibrary + "-original.dylib";

         auto path = m_pcontext->m_pathPrefix / "lib" / strDylib;

         auto pathOriginal = m_pcontext->m_pathPrefix / "lib" / strDylibOriginal;
         
         ::string strCommand2 ="mv -f " + path + " " + pathOriginal;

         m_pcontext->bash(strCommand2);

         acmefile()->copy(path, pathOriginal, true);
         
         ::string strCommand3 ="install_name_tool -id @executable_path/" + strDylib + " " + path;

         m_pcontext->bash(strCommand3);
         
         m_mappath[scopedstrLibrary][m_pcontext->m_strPlatform] = path;

         //m_pcontext->bash("cp -f " + strSource + "/lib" + scopedstrLibrary + "/* " + strStorage + "/binary/");
         //m_pcontext->bash("cp -f " + strSource + "/lib" + scopedstrLibrary + "/*.pdb //" + strStorage + "/binary/");
         
         
      }


      void ffmpeg::install()
      {
         
         m_pcontext->change_to_source_directory();
         
         m_pcontext->bash("make install");
         
         auto pathOperatingSystemIncludeFolder = acmedirectory()->home() /"workspace/operating_system/operating_system-macos/include";
         ;

         auto pathOperatingSystemStorageFolder = m_pcontext->m_pathOperatingSystemStorageFolder /m_pcontext->m_strConfiguration;
         
         auto strPrefix = m_pcontext->prepare_path(m_pcontext->m_pathPrefix);
         
         ::string strInclude = m_pcontext->prepare_path(pathOperatingSystemIncludeFolder);
         
         ::string strStorage = m_pcontext->prepare_path(pathOperatingSystemStorageFolder);
         
         m_pcontext->bash("cp -Rf " + strPrefix + "/include/* " + strInclude + "/include/");
//         m_pcontext->bash("cp -f " + strPrefix + "/bin/*.exe " + strStorage + "/binary/");
//         m_pcontext->bash("cp -f " + strPrefix + "/bin/*.dll " + strStorage + "/binary/");
//         m_pcontext->bash("cp -f " + strPrefix + "/bin/*.lib " + strStorage + "/library/");
         m_pcontext->bash("cp -f " + strPrefix + "/lib/* " + strStorage + "/library/");
         
         install_lib("avcodec");
         install_lib("avdevice");
         install_lib("avfilter");
         install_lib("avformat");
         install_lib("avutil");
         install_lib("swresample");
         install_lib("swscale");
         
      }
   
   
      void ffmpeg::remap_dependencies(const ::scoped_string & scopedstrLibraryName)
      {
         
         remap_dependency(scopedstrLibraryName, "avcodec");
         remap_dependency(scopedstrLibraryName, "avdevice");
         remap_dependency(scopedstrLibraryName, "avfilter");
         remap_dependency(scopedstrLibraryName, "avformat");
         remap_dependency(scopedstrLibraryName, "avutil");
         remap_dependency(scopedstrLibraryName, "swresample");
         remap_dependency(scopedstrLibraryName, "swscale");
         
      }


   } // namespace macos


} // namespace console_integration



