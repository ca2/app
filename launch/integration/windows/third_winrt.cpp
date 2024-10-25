// From third_winrt.cpp by camilo on 2023-06-22 16:35 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "third_winrt.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/prototype/url.h"
//#include "acme/filesystem/filesystem/file_context.h"
//#include "apex/networking/http/context.h"
#include "acme/platform/integration_context.h"
//#include "aqua/audio/audio.h"
//#include "aqua/audio/speaker.h"
//#include "aqua/platform/system.h"

//void simple_tts(const ::scoped_string& scopestr);


namespace console_integration
{


   third_winrt::third_winrt()
   {

   }


   third_winrt::~third_winrt()
   {

   }


   void third_winrt::initialize(::particle* pparticle)
   {

      ::particle::initialize(pparticle);

      acmenode()->integration_factory();

      __construct(m_papplication);

      m_papplication->m_strName = "third_winrt";

   }


   void third_winrt::build()
   {

      prepare();

      //clean();

      download();

      configure();

      compile();

      install();

      //preempt(10_s);

   }


   void third_winrt::prepare()
   {

      //initialize_tts_speaker();

      m_papplication->prepare_compile_and_link_environment();

   }


   void third_winrt::clean()
   {


   }


   void third_winrt::download()
   {



   }


   void third_winrt::configure()
   {

      
   }


   void third_winrt::speak(::index iIndex, ::index iCount, const ::scoped_string& scopedstrText, int iExitCode)
   {

      ::string strMessage;

      if (iExitCode == 0)
      {

         strMessage.format("%d of %d %s has been built successfully", iIndex, iCount, ::string(scopedstrText).c_str());

      }
      else
      {

         strMessage.format("%d of %d %s has failed to build", iIndex, iCount, ::string(scopedstrText).c_str());

      }

      acmenode()->speak(strMessage);

      if (iExitCode != 0)
      {

         throw ::exception(error_failed);

      }

   }


   void third_winrt::compile()
   {

      int iExitCode;

      try
      {

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"Debug\";Platform=Win32");

         speak(1, 16, "Universal Windows Intel 32-bit Debug", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"Release\";Platform=Win32");

         speak(2, 16, "Universal Windows Intel 32-bit Release", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"StaticDebug\";Platform=Win32");

         speak(3, 16, "Universal Windows Intel 32-bit Static Debug", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"StaticRelease\";Platform=Win32");

         speak(4, 16, "Universal Windows Intel 32-bit Static Release", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"Debug\";Platform=x64");

         speak(5, 16, "Universal Windows Intel 64-bit Debug", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"Release\";Platform=x64");

         speak(6, 16, "Universal Windows Intel 64-bit Release", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"StaticDebug\";Platform=x64");

         speak(7, 16, "Universal Windows Intel 64-bit Static Debug", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"StaticRelease\";Platform=x64");

         speak(8, 16, "Universal Windows Intel 64-bit Static Release", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"Debug\";Platform=ARM");

         speak(9, 16, "Universal Windows ARM 32-bit Debug", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"Release\";Platform=ARM");

         speak(10, 16, "Universal Windows ARM 32-bit Release", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"StaticDebug\";Platform=ARM");

         speak(11, 16, "Universal Windows ARM 32-bit Static Debug", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"StaticRelease\";Platform=ARM");

         speak(12, 16, "Universal Windows ARM 32-bit Static Release", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"Debug\";Platform=ARM64");

         speak(13, 16, "Universal Windows ARM 64-bit Debug", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"Release\";Platform=ARM64");

         speak(14, 16, "Universal Windows ARM 64-bit Release", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"StaticDebug\";Platform=ARM64");

         speak(15, 16, "Universal Windows ARM 64-bit Static Debug", iExitCode);

         iExitCode = m_papplication->command_system("msbuild.exe C:\\main\\solution-universal_windows\\u_third.sln /t:Rebuild /p:Configuration=\"StaticRelease\";Platform=ARM64");

         speak(16, 16, "Universal Windows Intel 64-bit Static Release", iExitCode);

         //auto pfile = file_system()->get_reader("matter://Techno-full-loop.mp3");

         //acmesystem()->audio()->play_audio(pfile, true);

      }
      catch (...)
      {

         //auto pfile = file()->get_reader("matter://twilight.wav");

         //acmesystem()->audio()->play_audio(pfile, true);

      }

   }


   void third_winrt::install()
   {

   }


} // namespace console_integration



