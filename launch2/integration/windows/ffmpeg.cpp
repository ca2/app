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


   namespace windows
   {


      ffmpeg::ffmpeg()
      {

      }


      ffmpeg::~ffmpeg()
      {

      }


      void ffmpeg::initialize(::particle* pparticle)
      {

         ::particle::initialize(pparticle);

         acmenode()->integration_factory();

         __construct(m_pcontext);

         m_pcontext->m_bMsys = true;

         m_pcontext->m_strName = "ffmpeg";

      }


      void ffmpeg::build()
      {

         prepare();

         //clean();

         //If(0)
         if (m_pcontext->m_bBuildDependencies)
         {

            build_dependencies();

         }

         if (!m_pcontext->m_bOnlyInstall)
         {

            //Return;

            download();

            configure();

            compile();

         }

         install();

      }


      void ffmpeg::prepare()
      {

         //property_set set;

         //acmesystem()->url()->defer_raw_http(set);

         //set["disable_common_name_cert_check"] = true;

         ::string strRelease = acmesystem()->http_text("https://raw.githubusercontent.com/FFmpeg/FFmpeg/master/RELEASE");

         strRelease.trim();

         strRelease.case_insensitive_ends_eat(".git");

         m_pcontext->m_strRelease = strRelease;

         m_pcontext->m_pathDownloadURL = "https://git.ffmpeg.org/ffmpeg.git";

         m_pcontext->prepare();

         if (m_pcontext->m_strPlatform == "Win32")
         {

            m_strArch = "i386";

         }
         else if (m_pcontext->m_strPlatform == "x64")
         {

            m_strArch = "x86_64";

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

         if (m_pcontext->m_strConfiguration.case_insensitive_contains("Static"))
         {

            m_strShared = "";

            m_strStatic = "";

         }
         else
         {

            m_strShared = "--enable-shared";

            m_strStatic = "--disable-static";

         }

         m_pcontext->m_pathPrefix = m_pcontext->m_pathFolder / m_pcontext->m_pathBase / m_pcontext->m_pathPlatformConfiguration / "build";

         m_pcontext->prepare_compile_and_link_environment();

      }


      void ffmpeg::build_dependencies()
      {

         //If(0)
         {

            build_x264();

         }

         //Return;

         build_x265();

      }


      void ffmpeg::build_x264()
      {

         ::file::path pathDependencyPrefixBase =
            m_pcontext->m_pathFolder /
            m_pcontext->m_strName /
            m_pcontext->m_strRelease;

         //int iExitCode = 0;

         ::string strParameters;

         strParameters = "x264 " + m_pcontext->m_strPlatform + " " + m_pcontext->m_strConfiguration;

         strParameters += " \"" + pathDependencyPrefixBase + "\"";

         ::string strCommand;

         strCommand = "application_build_helper " + strParameters;

         auto functionTrace = [&](auto etracelevel, auto& str)
            {

               m_strax264.append_format("%c: %s\n", trace_level_letter(etracelevel), str.c_str());

               std_inline_log()(etracelevel, str);

            };

         //acmenode()->command_system(strCommand);

         m_pcontext->bash(strCommand);

         //if (iExitCode == 0)
         //{

         //   m_strax264.add("x264 Completed!!");

         //}
         //else
         //{

         //   m_strax264.add("x264 Finished with error exit code: " + ::as_string(iExitCode) + "!");

         //}

         //__construct_new(m_px264);

         //m_px264->m_pcontext->m_pathPrefix = m_pcontext->m_pathPrefix;

         //m_px264->m_pcontext->m_strPlatform = m_pcontext->m_strPlatform;

         //m_px264->m_pcontext->m_strConfiguration = m_pcontext->m_strConfiguration;

         //m_px264->build();

      }


      void ffmpeg::build_x265()
      {

         ::file::path pathDependencyPrefixBase =
            m_pcontext->m_pathFolder /
            m_pcontext->m_strName /
            m_pcontext->m_strRelease;


         int iExitCode = 0;

         ::string strParameters;

         strParameters = "x265 " + m_pcontext->m_strPlatform + " " + m_pcontext->m_strConfiguration;

         strParameters += " \"" + pathDependencyPrefixBase + "\"";

         ::string strCommand;

         strCommand = "application_build_helper " + strParameters;

         auto functionTrace = [&](auto etracelevel, auto& str)
            {

               m_strax264.append_format("%c: %s\n", trace_level_letter(etracelevel), str.c_str());

               std_inline_log()(etracelevel, str);

            };

         //acmenode()->command_system(strCommand, functionTrace);
         m_pcontext->bash(strCommand);

         if (iExitCode == 0)
         {

            m_strax264.add("x265 Completed!!");

         }
         else
         {

            m_strax264.add("x265 Finished with error exit code: " + ::as_string(iExitCode) + "!");

         }

         //__construct_new(m_px264);

         //m_px264->m_pcontext->m_pathPrefix = m_pcontext->m_pathPrefix;

         //m_px264->m_pcontext->m_strPlatform = m_pcontext->m_strPlatform;

         //m_px264->m_pcontext->m_strConfiguration = m_pcontext->m_strConfiguration;

         //m_px264->build();

      }


      void ffmpeg::clean()
      {

         m_pcontext->clean();

      }


      void ffmpeg::download()
      {

         m_pcontext->create_source_directory();

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


         if (m_pcontext->m_strConfiguration.case_insensitive_contains("Static"))
         {

            if (m_pcontext->m_strConfiguration.case_insensitive_contains("Debug"))
            {

               strMoreFlags = "-MTd ";

            }
            else
            {

               strMoreFlags = "-MT ";

            }

         }

         strConfigureCommand = "./configure --enable-asm --enable-x86asm --arch=" + m_strArch;
         strConfigureCommand += " --disable-doc " + m_strShared + " " + m_strStatic;
         strConfigureCommand += " --disable-bzlib --disable-libopenjpeg --disable-iconv --disable-zlib";
         strConfigureCommand += " --disable-programs";
         strConfigureCommand += " --enable-libx264 --enable-libx265 --enable-gpl";
         strConfigureCommand += " --prefix=" + strPrefix + "/ --toolchain=msvc " + m_strDebug;
         strConfigureCommand += " --extra-ldflags=-LIBPATH:" + strPrefix + "/lib/";
         strConfigureCommand += " --extra-cflags=\"" + strMoreFlags + "-I" + strPrefix + "/include/\"";


         strCommand += "#!/bin/bash\n";
         strCommand += "\n";
         strCommand += "\n";
         strCommand += "do_configure()\n";
         strCommand += "{\n";
         strCommand += "\n";
         strCommand += "   cd \"" + m_pcontext->m_pathSource + "\"\n";
         strCommand += strConfigureCommand + "\n";
         strCommand += "   PKG_CONFIG_PATH='" + windows_bash_path(strPkgConfigPath) + "'\n";
         strCommand += "   export PKG_CONFIG_PATH\n";
         strCommand += "   set > test1.txt\n";
         strCommand += "\n";
         strCommand += "\n";
         strCommand += "   make\n";
         strCommand += "\n";
         strCommand += "}\n";
         strCommand += "\n";
         strCommand += "do_configure\n";

         acmefile()->put_contents(m_pcontext->m_pathSource / "configure2.sh",
            strCommand);
         m_pcontext->bash("chmod +x configure2.sh");
         ::string s;

         if (m_pcontext->m_strPlatform.contains("64"))
         {
            s += "call \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat\"\n";
         }
         else
         {
            s += "call \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvars32.bat\"\n";
         }
         s += "C:\n";
         s += "cd \"" + m_pcontext->m_pathSource.windows_path() + "\"\n";
         s += "set CHERE_INVOKING=1\n";
         s += "set MSYSTEM=MSYS\n";
         s += "set MSYS2_PATH_TYPE=inherit\n";
         s += "\"C:\\msys64\\usr\\bin\\bash.exe\" --login -i \"" + m_pcontext->m_pathSource + "/configure2.sh\"\n";
         //s += "\"C:\\msys64\\msys2.exe\" -l \"" + m_pcontext->m_pathSource + "/configure2.sh\"\n";
   //   C:\


         acmefile()->put_contents(m_pcontext->m_pathSource / "vs_call.bat", s);

         //trace_function tracefunction = [&](auto etracelevel, auto& str)
         //{

         //   //m_strax264.append_format("%c: %s\n", trace_level_letter(etracelevel), str.c_str());

         //   std_inline_log()(etracelevel, str);

         //};

         //tracefunction.m_timeTimeout = 2.5_hour;

         //acmenode()->command_system(m_pcontext->m_pathSource +"/vs_call.bat", tracefunction);

         printf("Current Directory: %s\n", acmedirectory()->get_current().c_str());
         printf("%s\n", s.c_str());

         //::file::path pathVsCall = m_pcontext->m_pathSource + "/vs_call.bat";

         //acmenode()->command_system(pathVsCall.windows_path(), 2.5_hour);

         m_pcontext->bash("export PKG_CONFIG_PATH='" + windows_bash_path(strPkgConfigPath) + "'; " + strConfigureCommand);

         output_debug_string("test");

      }


      void ffmpeg::compile()
      {

         // make at configure

         m_pcontext->change_to_source_directory();

         ::pointer < ::application_build_helper::application > papplication = acmeapplication();

         m_pcontext->bash("make" + papplication->m_strMakeOptions);

      }


      void ffmpeg::install_lib(const ::scoped_string& scopedstrLibrary)
      {

         auto pathSource = m_pcontext->m_pathSource;

         auto pathOperatingSystemStorageFolder = m_pcontext->m_pathOperatingSystemStorageFolder / m_pcontext->m_strPlatform / m_pcontext->m_strConfiguration;

         auto strSource = m_pcontext->prepare_path(pathSource);

         auto strStorage = m_pcontext->prepare_path(pathOperatingSystemStorageFolder);

         if (!m_pcontext->m_strConfiguration.case_insensitive_contains("static"))
         {
          
            //m_pcontext->bash("cp -f " + strSource + "/lib" + scopedstrLibrary + "/*.dll " + strStorage + "/binary/");
            m_pcontext->bash("cp -f " + strSource + "/lib" + scopedstrLibrary + "/*.pdb " + strStorage + "/binary/");

         }

      }


      void ffmpeg::install()
      {

         m_pcontext->change_to_source_directory();

         m_pcontext->bash("make install");

         auto pathOperatingSystemIncludeFolder = m_pcontext->m_pathOperatingSystemIncludeFolder;

         auto pathOperatingSystemStorageFolder = m_pcontext->m_pathOperatingSystemStorageFolder / m_pcontext->m_strPlatform / m_pcontext->m_strConfiguration;

         auto strPrefix = m_pcontext->prepare_path(m_pcontext->m_pathPrefix);

         auto strInclude = m_pcontext->prepare_path(pathOperatingSystemIncludeFolder);

         auto strStorage = m_pcontext->prepare_path(pathOperatingSystemStorageFolder);

         m_pcontext->bash("cp -Rf " + strPrefix + "/include/* " + strInclude + "/include/");
         m_pcontext->bash("cp -f " + strPrefix + "/bin/*.exe " + strStorage + "/binary/");
         
         if (!m_pcontext->m_strConfiguration.case_insensitive_contains("static"))
         {
          
            m_pcontext->bash("cp -f " + strPrefix + "/bin/*.dll " + strStorage + "/binary/");
            m_pcontext->bash("cp -f " + strPrefix + "/bin/*.lib " + strStorage + "/library/");

         }

         m_pcontext->bash("cp -Rf " + strPrefix + "/lib/* " + strStorage + "/library/");

         install_lib("avcodec");
         install_lib("avdevice");
         install_lib("avfilter");
         install_lib("avformat");
         install_lib("avutil");
         install_lib("swresample");
         install_lib("swscale");

      }


   } // namespace windows


} // namespace console_integration



