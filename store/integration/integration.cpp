#include "framework.h"
#include "integration.h"
#include <stdio.h>
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/url.h"
#include "acme/platform/integration_context.h"
//#include "apex/networking/http/context.h"


namespace application_build_helper
{


   //class application :
   //   virtual public ::apex::application
   //{
   //public:


   //   ::file::path m_pathFolder;


//      application::application()
//      {
//
//         m_bNetworking = true;
//
//         m_bCrypto = false;
//
//         //m_bResource = false;
//
//         m_bAudio = true;
//
//         m_strAppId = "integration/console_integration";
//
//         m_pathFolder = "C:\\";
//
//
//      }
//
      
      //int __implement()
//{
//
//   auto papp = memory_new app_integration::application();
//
//   int iExitCode = papp->__implement();
//
//   return iExitCode;
//
//}

         //namespace console
         //{


         //   namespace integration
         //   {


         //      void application::main() override
         //      {

         //         auto psystem = acmesystem();

         //         auto psubsystem = psystem->m_psubsystem;

         //         for (int i = 0; i < psubsystem->get_argument_count1(); i++)
         //         {

         //            string strArgument = psubsystem->get_argument1(i);

         //            if (strArgument.case_insensitive_equals("ffmpeg"))
         //            {

         //               ffmpeg();

         //            }
         //            else if (strArgument.case_insensitive_equals("openssl"))
         //            {

         //               openssl();

         //            }

         //         }


         //      }


         //   } // namespace integration



         //} // namespace console


//
//      void application::main()
//      {
//
//         auto psystem = acmesystem();
//
//         auto psubsystem = psystem->m_psubsystem;
//
//         string strArgument = psubsystem->get_argument1(0);
//
//         string strModule = file_system()->module().title();
//
//         if (this->has_property("j"))
//         {
//
//            m_strMakeOptions = " -j" + this->payload("j");
//
//         }
//
//         if (strArgument.case_insensitive_equals("ffmpeg"))
//         {
//
//            auto strPlatform = psubsystem->get_argument1(1);
//
//            if (strPlatform.case_insensitive_equals("Static"))
//            {
//
//               ::string strExtraParameters;
//
//               if (this->has_property("j"))
//               {
//
//                  strExtraParameters = " --j=" + this->payload("j");
//
//               }
//
//
//               acmenode()->open_terminal_and_run(strModule + " ffmpeg Win32 StaticDebug" + strExtraParameters);
//
//               acmenode()->open_terminal_and_run(strModule + " ffmpeg Win32 StaticRelease" + strExtraParameters);
//
//               acmenode()->open_terminal_and_run(strModule + " ffmpeg x64 StaticDebug" + strExtraParameters);
//
//               acmenode()->open_terminal_and_run(strModule + " ffmpeg x64 StaticRelease" + strExtraParameters);
//
//               return;
//
//            }
//
//
//            if (!strPlatform.case_insensitive_equals("Win32")
//               && !strPlatform.case_insensitive_equals("x64"))
//            {
//
//               acmenode()->open_terminal_and_run(strModule + " ffmpeg Win32");
//                        
//               acmenode()->open_terminal_and_run(strModule + " ffmpeg x64");
//                        
//               return;
//
//            }
//
//            auto strConfiguration = psubsystem->get_argument1(2);
//
//            if (!strConfiguration.case_insensitive_equals("Debug")
//               && !strConfiguration.case_insensitive_equals("Release")
//               && !strConfiguration.case_insensitive_equals("StaticDebug")
//               && !strConfiguration.case_insensitive_equals("StaticRelease"))
//            {
//
//               acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " Debug --no-prefix-clean");
//
//               acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " Release --no-prefix-clean");
//               
//               acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " StaticDebug --no-prefix-clean");
//
//               acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " StaticRelease --no-prefix-clean");
//
//               return;
//
//            }
//
//            //while (true)
//            //{
//
//            //   printf("Enter s to start.\n");
//
//            //   if (getchar() == 's')
//            //   {
//
//            //      break;
//
//            //   }
//
//            //}
//
//            auto pffmpeg = øcreate_new < macos::ffmpeg >();
//
//            pffmpeg->m_papplication->m_strPlatform = strPlatform;
//
//            pffmpeg->m_papplication->m_strConfiguration = strConfiguration;
//
//            pffmpeg->build();
//
//            while (true)
//            {
//
//               printf("Enter q to quit.\n");
//
//               if (getchar() == 'q')
//               {
//
//                  break;
//
//               }
//
//            }
//
//         }
//         else if (strArgument.case_insensitive_equals("openssl"))
//         {
//
//            auto popenssl = øcreate_new < openssl >();
//
//            popenssl->m_papplication->m_strPlatform = psubsystem->get_argument1(1);
//
//            popenssl->m_papplication->m_strConfiguration = psubsystem->get_argument1(2);
//
//            popenssl->build();
//
//         }
//         else if (strArgument.case_insensitive_equals("x264"))
//         {
//
//            auto px264 = øcreate_new < x264 >();
//
//            px264->m_papplication->m_strPlatform = psubsystem->get_argument1(1);
//
//            px264->m_papplication->m_strConfiguration = psubsystem->get_argument1(2);
//
//            px264->m_papplication->m_pathPrefix = psubsystem->get_argument1(3);
//
//            px264->build();
//
//         }
//         else if (strArgument.case_insensitive_equals("x265"))
//         {
//
//            auto px264 = øcreate_new < x265 >();
//
//            px264->m_papplication->m_strPlatform = psubsystem->get_argument1(1);
//
//            px264->m_papplication->m_strConfiguration = psubsystem->get_argument1(2);
//
//            px264->m_papplication->m_pathPrefix = psubsystem->get_argument1(3);
//
//            px264->build();
//
//         }
//         else if (strArgument.case_insensitive_equals("third_winrt"))
//         {
//
//            auto pthirdwinrt = øcreate_new < third_winrt >();
//
//            pthirdwinrt->build();
//
//         }
//         else if (strArgument.case_insensitive_equals("third"))
//         {
//
//            auto pthirdwinrt = øcreate_new < third >();
//
//            pthirdwinrt->build();
//
//         }
//
//
//      }
//
//
//      //void ffmpeg()
//      //{
//
//      //   ffmpeg("Win32", "Debug");
//      //   ffmpeg("Win32", "Release");
//      //   ffmpeg("Win32", "StaticDebug");
//      //   ffmpeg("Win32", "StaticRelease");
//
//      //   ffmpeg("x64", "Debug");
//      //   ffmpeg("x64", "Release");
//      //   ffmpeg("x64", "StaticDebug");
//      //   ffmpeg("x64", "StaticRelease");
//
//
//      //}
//
//
//      //void ffmpeg(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration)
//      //{
//
//      //   printf("Building ffmpeg");
//
//      //   ::file::path path;
//
//      //   path = "ffmpeg" / strVersion / scopedstrPlatform / scopedstrConfiguration;
//
//      //   ::file::path pathPrefix = m_pathFolder / path / "build"
//
//      //   string strCommand;
//      //   
//      //   strCommand = 
//      //      "configure --enable-asm --enable-yasm --arch=" + strArch + 
//      //      " --disable-doc "+ strShared + strStatic + 
//      //      " --disable-bzlib --disable-libopenjpeg --disable-iconv --disable-zlib" +
//      //      " --prefix=" + strBaseDir + "/" + strPath + "/build$BASE_DIR / $PATH / build --toolchain = msvc $DEBUG
//
//
//      //}
//
//      //void openssl()
//      //{
//
//      //   printf("Building openssl");
//
//
//      //}
//
//
//   //};

} // namespace console_integration

//
//::console_integration::application g_console_http_get_application;
//


