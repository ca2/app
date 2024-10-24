// Created by camilo on 2023-01-15 02:59 <3ThomasBorregaardSørensen!!
#pragma once


//#ifdef CONSOLE_INTEGRATION_NO_AUDIO
//#include "apex/platform/application.h"
//#else
//#include "aqua/platform/application.h"
//#endif

//
//namespace console_integration
//{
//
//
//   //namespace integration
//   //{
//
//
//   class integration :
//      virtual public ::particle
//   {
//   public:
//
//
//      ::file::path m_pathFolder;
//
//
//      integration();

//
//      bool integrate();
//
//      bool safe_integrate();
//
//      ::string m_strMakeOptions;
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
//      //      string strCommand;
//
//      //   strCommand =
//      //      "configure --enable-asm --enable-yasm --arch=" + strArch +
//      //      " --disable-doc " + strShared + strStatic +
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
//      //application::application()
//      //{
//
//      //   m_bNetworking = true;
//
//      //   m_bCrypto = false;
//
//      //   m_bResource = false;
//
//      //   m_strAppId = "console/integration";
//
//      //   m_pathFolder = "C:\\";
//
//
//      //}
//
//
//      //int __implement()
////{
////
////   auto papp = memory_new app_integration::application();
////
////   int iExitCode = papp->__implement();
////
////   return iExitCode;
////
////}
//
//         //namespace console
//         //{
//
//
//         //   namespace integration
//         //   {
//
//
//         //      void application::main() override
//         //      {
//
//         //         auto psystem = acmesystem();
//
//         //         auto psubsystem = psystem->m_psubsystem;
//
//         //         for (int i = 0; i < psubsystem->get_argument_count1(); i++)
//         //         {
//
//         //            string strArgument = psubsystem->get_argument1(i);
//
//         //            if (strArgument.case_insensitive_equals("ffmpeg"))
//         //            {
//
//         //               ffmpeg();
//
//         //            }
//         //            else if (strArgument.case_insensitive_equals("openssl"))
//         //            {
//
//         //               openssl();
//
//         //            }
//
//         //         }
//
//
//         //      }
//
//
//         //   } // namespace integration
//
//
//
//         //} // namespace console
//
//
//
////void main() override;
//      //{
//
//      //   auto psystem = acmesystem();
//
//      //   auto psubsystem = psystem->m_psubsystem;
//
//      //   string strArgument = psubsystem->get_argument1(0);
//
//      //   string strModule = acmefile()->module().title();
//
//      //   if (strArgument.case_insensitive_equals("ffmpeg"))
//      //   {
//
//      //      auto strPlatform = psubsystem->get_argument1(1);
//
//      //      if (!strPlatform.case_insensitive_equals("Win32")
//      //         && !strPlatform.case_insensitive_equals("x64"))
//      //      {
//
//      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg Win32");
//
//      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg x64");
//
//      //         return;
//
//      //      }
//
//      //      auto strConfiguration = psubsystem->get_argument1(2);
//
//      //      if (!strConfiguration.case_insensitive_equals("Debug")
//      //         && !strConfiguration.case_insensitive_equals("Release")
//      //         && !strConfiguration.case_insensitive_equals("StaticDebug")
//      //         && !strConfiguration.case_insensitive_equals("StaticRelease"))
//      //      {
//
//      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " Debug --no-prefix-clean");
//
//      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " Release --no-prefix-clean");
//
//      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " StaticDebug --no-prefix-clean");
//
//      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " StaticRelease --no-prefix-clean");
//
//      //         return;
//
//      //      }
//
//      //      //while (true)
//      //      //{
//
//      //      //   printf("Enter s to start.\n");
//
//      //      //   if (getchar() == 's')
//      //      //   {
//
//      //      //      break;
//
//      //      //   }
//
//      //      //}
//
//      //      auto pffmpeg = __create_new < ffmpeg >();
//
//      //      pffmpeg->m_papplication->m_strPlatform = strPlatform;
//
//      //      pffmpeg->m_papplication->m_strConfiguration = strConfiguration;
//
//      //      pffmpeg->build();
//
//      //      while (true)
//      //      {
//
//      //         printf("Enter q to quit.\n");
//
//      //         if (getchar() == 'q')
//      //         {
//
//      //            break;
//
//      //         }
//
//      //      }
//
//      //   }
//      //   else if (strArgument.case_insensitive_equals("openssl"))
//      //   {
//
//      //      auto popenssl = __create_new < openssl >();
//
//      //      popenssl->m_papplication->m_strPlatform = psubsystem->get_argument1(1);
//
//      //      popenssl->m_papplication->m_strConfiguration = psubsystem->get_argument1(2);
//
//      //      popenssl->build();
//
//      //   }
//      //   else if (strArgument.case_insensitive_equals("x264"))
//      //   {
//
//      //      auto px264 = __create_new < x264 >();
//
//      //      px264->m_papplication->m_strPlatform = psubsystem->get_argument1(1);
//
//      //      px264->m_papplication->m_strConfiguration = psubsystem->get_argument1(2);
//
//      //      px264->m_papplication->m_pathPrefix = psubsystem->get_argument1(3);
//
//      //      px264->build();
//
//      //   }
//      //   else if (strArgument.case_insensitive_equals("x265"))
//      //   {
//
//      //      auto px264 = __create_new < x265 >();
//
//      //      px264->m_papplication->m_strPlatform = psubsystem->get_argument1(1);
//
//      //      px264->m_papplication->m_strConfiguration = psubsystem->get_argument1(2);
//
//      //      px264->m_papplication->m_pathPrefix = psubsystem->get_argument1(3);
//
//      //      px264->build();
//
//      //   }
//
//
//      //}
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
//   };
//
//
//
//
//
//
//
//   //} // namespace integration
//
//
//} // namespace console_integration
//
//
//
