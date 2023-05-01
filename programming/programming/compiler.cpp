// Created by camilo on 2021-11-15 15:39 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "compiler.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/operating_system/process.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "aura/platform/application.h"


#ifdef WINDOWS_DESKTOP


#include "acme_windows/_.h"
#include "acme_windows/registry.h"


#endif


namespace programming
{


   compiler::compiler()
   {

      defer_create_synchronization();

   }


   compiler::~compiler()
   {


   }


   void compiler::initialize_programming_compiler(::particle * pparticle, const ::file::path & pathProjectDir)
   {

      //auto estatus = 
      
      ::object::initialize(pparticle);

      acmenode()->integration_factory();

      __construct(m_pintegrationcontext);

      //if (!estatus)
      //{

      //   return estatus;

      //}


      if(pathProjectDir.has_char())
      {

         m_pintegrationcontext->m_pathProjectDir = pathProjectDir;

      }
      else
      {

         ::file::path path;

         path = __FILE__;

         m_pintegrationcontext->m_pathProjectDir = path.folder();

      }


#if MEMDLEAK

      m_strDynamicSourceConfiguration = "memdleak";
      m_strDynamicSourceStage = "stage";


#elif defined(_DEBUG)

      m_strDynamicSourceConfiguration = "debug";
      m_strDynamicSourceStage = "time-" OPERATING_SYSTEM_NAME;

#else

      m_strDynamicSourceConfiguration = "profiler";
      m_strDynamicSourceStage = "profiler";

#endif

      m_strDynamicSourceStageFolder = dir()->install() / m_strDynamicSourceStage;

      //return estatus;

   }


   void compiler::prepare_compile_and_link_environment()
   {
//
//      auto pacmedirectory = acmedirectory();
//
//      dir()->create(pacmedirectory->system() / "netnode_desktop/symbols");
//
//      ::file::path strVars;
//
//#ifdef WINDOWS_DESKTOP
//
//      if (m_strVs == "2015")
//      {
//
//         strVars = getenv("VS140COMNTOOLS");
//
//      }
//
//#endif
//
//      auto papp1 = get_app();
//
//      ::pointer<::aura::application>papp = papp1;
//
//#ifdef WINDOWS_DESKTOP
//
//      try
//      {
//
//         if (m_strVs == "2022")
//         {
//
//            m_strEnv = "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvarsall.bat";
//
//            m_strVCVersion = papp->get_visual_studio_build();
//
//         }
//         else if (m_strVs == "2019")
//         {
//
//            m_strEnv = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvarsall.bat";
//
//            m_strVCVersion = papp->get_visual_studio_build();
//
//         }
//         else if (m_strVs == "2017")
//         {
//
//            m_strEnv = "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvarsall.bat";
//
//            ::acme_windows::registry::key key;
//
//            key.open(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\VisualStudio\\SxS\\VS7", false);
//
//            string strPath;
//
//            key.get("15.0", strPath);
//
//            ::file::path path = strPath;
//
//            m_strEnv = path / "VC/Auxiliary/Build/vcvarsall.bat";
//
//            m_strVCVersion = papp->get_visual_studio_build();
//
//         }
//         else if (m_strVs == "2015")
//         {
//
//            m_strEnv = strVars.ascend(2);
//
//            m_strEnv = m_strEnv / "vc\\vcvarsall.bat";
//
//         }
//
//      }
//      catch (const ::e_status & estatus)
//      {
//
//         output_debug_string("failed to setup visual studio environment " + as_string(estatus.as_i64()));
//
//      }
//
//#endif
//
//      m_strTime = dir()->install() / ("time-" OPERATING_SYSTEM_NAME);
//
//#ifdef WINDOWS_DESKTOP
//
//      if (m_strVs == "2015")
//      {
//
//         m_strSdk1 = "vc140";
//
//      }
//      else if (m_strVs == "2017")
//      {
//
//         m_strSdk1 = "vc141";
//
//      }
//      else if (m_strVs == "2019")
//      {
//
//         m_strSdk1 = "vc142";
//
//      }
//      else if (m_strVs == "2022")
//      {
//
//         m_strSdk1 = "vc143";
//
//      }
//
//#endif
//
//#ifdef OS64BIT
//
//#ifdef LINUX
//
//      m_strPlat1 = "64";
//      m_strPlatform = "x86";
//      m_strStagePlatform = "x86";
//      m_strLibPlatform = "x86/";
//
//#else
//
//      m_strPlat1 = "64";
//      m_strPlat2 = "x86_amd64";
//      //m_strPlat2 = "amd64";
//      m_strPlatform = "x64";
//      m_strStagePlatform = "x64";
//      m_strLibPlatform = "x64/";
//
//#endif
//#else
//
//      m_strPlat1 = "32";
//      m_strPlat2 = " x86";
//      m_strPlatform = "Win32";
//      m_strStagePlatform = "x86";
//      m_strLibPlatform = "x86/";
//
//#endif
//
//#if defined(LINUX) || defined(MACOS)
//
//      prepare1(m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash",
//         m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash");
//      prepare1(m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash",
//         m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash");
//      prepare1(m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 + ".bash",
//         m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 + ".bash");
//
//#else
//
//      prepare1(m_strPlat1, m_strPlat1);
//
//#endif

      m_pintegrationcontext->prepare_compile_and_link_environment();

      dir()->create(dir()->install() / m_strDynamicSourceStage / "front");

      string str;

      string strItem;

      strItem = dir()->install() / m_strDynamicSourceStage / m_pintegrationcontext->m_strStagePlatform;

      str = str + strItem + ";";

      strItem = dir()->install() / m_strDynamicSourceStage / m_pintegrationcontext->m_strStagePlatform / "dynamic_source\\library";

      str = str + strItem + ";";

#ifdef WINDOWS_DESKTOP

      u32 dwSize = GetEnvironmentVariableW(L"PATH", nullptr, 0);
      LPWSTR lpsz = memory_new wchar_t[dwSize + 1];
      dwSize = GetEnvironmentVariableW(L"PATH", lpsz, dwSize + 1);
      str += lpsz;
      delete lpsz;

#endif

   }


   void compiler::prepare1(const ::string& lpcszSource, const ::string& lpcszDest)
   {

      string_array stra;


      string strLog;


      ::pointer<::apex::application>papp = acmeapplication();


//#ifdef WINDOWS
//      //sleep(15000_ms);
//
//      string strBuildCmd = m_strContext;
//
//      if (m_strVs == "2015")
//      {
//
//         strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2;
//
//      }
//      else if (m_strVs == "2017")
//      {
//
//         strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + papp->get_visual_studio_build();
//
//      }
//      else if (m_strVs == "2019")
//      {
//
//         strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + papp->get_visual_studio_build();
//
//      }
//      else if (m_strVs == "2022")
//      {
//
//         //strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + papp->get_visual_studio_build();
//
//         strBuildCmd = "\"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvars64.bat\"";
//
//      }
//
//      ::operating_system::process_pointer process(e_create, this);
//
//      ::file::path pathEnvTxt;
//
//      auto pacmedirectory = acmedirectory();
//
//      pathEnvTxt = pacmedirectory->system() / "env.txt";
//
//      acmefile()->put_contents(pacmedirectory->system() / "env1.bat", pacmedirectory->system() / "env.bat > \"" + pathEnvTxt + "\"");
//
//      acmefile()->put_contents(pacmedirectory->system() / "env.bat", "@call " + strBuildCmd + "\r\n@set");
//
//      auto psystem = acmesystem();
//
//      auto pnode = psystem->node();
//
//      pnode->run_silent(pacmedirectory->system() / "env1.bat", "");
//
//      strLog = acmefile()->as_string(pacmedirectory->system() / "env.txt");
//
//      stra.add_lines(strLog);
//
//      //sleep(10000_ms);
//
//#ifdef WINDOWS_DESKTOP
//
//      property_set setEnvironment;
//
//      setEnvironment.parse_environment_variable(stra);
//
//      for (auto& pproperty : setEnvironment)
//      {
//
//         SetEnvironmentVariableW(wstring(pproperty->m_atom), wstring(pproperty->as_string()));
//
//      }
//
//
//
//#endif
//#endif

      //   ::file::path strFolder;
      //   strFolder = dir()->install();
      //   if (!string_ends(strFolder, "/") && !string_ends(strFolder, "\\"))
      //      strFolder += "/";
      //   string strTemplate;
      //   string strSource = "platform/time-" OPERATING_SYSTEM_NAME"/dynamic_source/";
      //   strSource += lpcszSource;
      //
      ::file::path pathN = m_pintegrationcontext->m_pathProjectDir;
      pathN -= 3;
      string strN = pathN;
      strN.find_replace("\\", "/");
      strN += "/";
      //
      //
      //   //#ifdef _DEBUG
      //   strTemplate = strFolder / strSource;
      //   //#else
      //   // strTemplate = strFolder, "app/time-" OPERATING_SYSTEM_NAME"/aura/account/app/main/matter/dynamic_source_cl.bat", false);
      //   //#endif
      //   string str;
      //   str = file()->as_string(strTemplate);
      //   /*string strVars = getenv("VS100COMNTOOLS");
      //   file()->path().eat_end_level(strVars, 2, "/");
      //   strVars += "vc/bin/vcvars32.bat";*/
      //   str.replace("%VS_VARS%", m_strEnv);
      //   str.replace("%VS_VARS_PLAT2%", m_strPlat2);
      //
      //   string strV(dir()->install());
      //   strV.replace("\\", "/");
      //   if (!string_ends(strV, "/") && !string_ends(strV, "\\"))
      //      strV += "/";
      //   str.replace("%CA2_ROOT%", strV);
      //   str.replace("%PROJECT_DIR%", m_pathProjectDir);
      //   str.replace("%NETNODE_ROOT%", strN);
      //   str.replace("%SDK1%", m_strSdk1);
      //   string strDest = m_strDynamicSourceStage / "front" / lpcszDest;
      //   ::file::path strCmd;
      //   //#ifdef _DEBUG
      //   strCmd = strFolder / strDest;
      //   //#else
      //   // strCmd = strFolder, "app\\time-" OPERATING_SYSTEM_NAME"\\aura\\account\\app\\main\\front\\dynamic_source_cl.bat", false);
      //   //#endif
      //   dir()->create(strCmd.folder());
      //   //file()->put_text_utf8(strCmd, str);
      //   file()->put_contents(strCmd, str);
      //   dir()->create(m_strTime / "dynamic_source");
      //
      //
      //   string strBuildCmd = m_strEnv;
      //
      //   strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2;
      //
      //   ::process::process_pointer process(e_create);
      //
      //
      //   acmefile()->put_contents(pacmedirectory->system() / "env.bat","@call " + strBuildCmd + " "+m_strVCVersion+"\r\n@set");
      //
      //   set_thread_priority(::e_priority_highest);
      //   process->prop("inherit") = false;
      //
      //   ::file::path pathCommand =          auto psystem = acmesystem();

      //         auto pacmedirectory = psystem->m_pacmedirectory;
      //
      //pacmedirectory->system() / "env.bat";
      //
      //   ::file::path pathFolder = ::file::path(m_strEnv).folder();
      //
      //#ifdef WINDOWS_DESKTOP
      //   {
      //      u32 dwSize = GetEnvironmentVariable("PATH", nullptr, 0);
      //      char * lpsz = memory_new char[dwSize + 1];
      //      dwSize = GetEnvironmentVariable("PATH", lpsz, dwSize + 1);
      //      delete lpsz;
      //   }
      //
      //   #endif
      //
      //   process->create_child_process(pathCommand,true,pathFolder,::e_priority_highest);
      //   string strLog;
      //
      //   //   EnvVarValArray arrEnvVarVal;
      //
      //   //   ::time tickStart= ::time::now();
      //
      //   //   u32 dwExitCode;
      //
      //   //   string strLog;
      //
      //   //   string_array m_strArray;
      //   //   // Open the process for further operations
      //   //   HANDLE hProcess = CProcessEnvReader::OpenProcessToRead(process->m_iPid);
      //   //   if(hProcess)
      //   //   {
      //   //      _ENVSTRING_t stEnvData;
      //   //      // Read the process environment block
      //   //      if(!CProcessEnvReader::ReadEnvironmentBlock(hProcess,stEnvData))
      //   //      {
      //   //         return;
      //   //      }
      //
      //   //      // Parse the retrieved data
      //   //      CProcessEnvReader::ParseEnvironmentStrings(stEnvData.pData,
      //   //         stEnvData.nSize / 2,
      //   //         m_strArray);
      //
      //
      //   //      // Seperate values and variables
      //   //      CProcessEnvReader::SeparateVariablesAndValues(m_strArray,arrEnvVarVal);
      //
      //   //      // UpdateProcessMiscInfo( hProcess, pNMItemActivate->iItem);
      //   //      CProcessEnvReader::ReleaseHandle(hProcess);
      //   //   }
      //   //process->write("\n");
      //   u32 dwExitCode;
      //   ::u32 tickStart= ::time::now();
      //   while(::task_get_run() && task_get_run())
      //   {
      //
      //      strLog += process->read();
      //
      //      if(process->has_exited(&dwExitCode))
      //         break;
      //
      //      sleep(100_ms);
      //
      //      if(tickStart.elapsed() > 840 * 1000) // 14 minutes
      //      {
      //
      //         //            bTimeout = true;
      //
      //         break;
      //
      //      }
      //
      //   }
      //
      //   strLog += process->read();
      //   string_array stra;
      //
      //   stra.add_lines(strLog);
      //
      //   #ifdef WINDOWS_DESKTOP
      //   {
      //      u32 dwSize = GetEnvironmentVariable("PATH", nullptr, 0);
      //      char * lpsz = memory_new char[dwSize + 1];
      //      dwSize = GetEnvironmentVariable("PATH", lpsz, dwSize + 1);
      //      delete lpsz;
      //   }
      //   #endif
      //
      //   //sleep(10000_ms);
      //
      //#if defined(WINDOWS_DESKTOP)
      //   EnvVarValArray arrEnvVarVal;
      //   // Seperate values and variables
      //   CProcessEnvReader::SeparateVariablesAndValues(stra,arrEnvVarVal);
      //
      //   string_to_string map;
      //
      //   for(auto pair : arrEnvVarVal)
      //   {
      //      map[pair.element1()] = pair.element2();
      //      SetEnvironmentVariable(pair.element1(),pair.element2());
      //   }
      //
      //
      //
      //   //SetEnvironmentVariable("INCLUDE",map["INCLUDE"]);
      //   //SetEnvironmentVariable("LIBPATH",map["LIBPATH"]);
      //   //SetEnvironmentVariable("PATH",map["PATH"]);
      //
      //   // UpdateProcessMiscInfo( hProcess, pNMItemActivate->iItem);
      //   //CProcessEnvReader::ReleaseHandle(hProcess);
      //
      //#endif
      //
      stra.add_lines(strLog);

      //string strEnv = acmefile()->as_string(         auto psystem = acmesystem();

   //         auto pacmedirectory = psystem->m_pacmedirectory;
   //
   //pacmedirectory->system() / "env.txt");

      ::file::path strFolder;
      strFolder = dir()->install();
      if (!string_ends(strFolder, "/") && !string_ends(strFolder, "\\"))
         strFolder += "/";
      string strTemplate;
      string strSource = "operating_system/operating_system-" OPERATING_SYSTEM_NAME "/_stage/dynamic_source/";
      strSource += lpcszSource;

      //   string strN = m_pmanager->m_strNetnodePath;
            //strN.replace("\\","/");
            //if(!string_ends(strN,"/") && !string_ends(strN,"\\"))
            // strN += "/";

            //#ifdef _DEBUG
      strTemplate = strFolder / strSource;
      //#else
      // strTemplate = strFolder, "app/_stage/aura/account/app/main/matter/dynamic_source_cl.bat", false);
      //#endif
      string str;
      str = file()->safe_get_string(strTemplate);
      /*string strVars = getenv("VS100COMNTOOLS");
      file()->path().eat_end_level(strVars, 2, "/");
      strVars += "vc/bin/vcvars32.bat";*/

      string strV(dir()->install());
      strV.find_replace("\\", "/");
      if (!string_ends(strV, "/") && !string_ends(strV, "\\"))
         strV += "/";
      str.find_replace("%CA2_ROOT%", strV);
      str.find_replace("%NETNODE_ROOT%", strN);
      //str.replace("%DVP%", strDVP_B);

      m_pintegrationcontext->prepare_compilation_script(str);

      string strDest = m_strDynamicSourceStage / "front" / lpcszDest;
      ::file::path strCmd;
      //#ifdef _DEBUG
      strCmd = strFolder / strDest;
      //#else
      // strCmd = strFolder, "app\\_stage\\aura\\account\\app\\main\\front\\dynamic_source_cl.bat", false);
      //#endif
      dir()->create(strCmd.folder());
      //file()->put_text_utf8(strCmd, str);
      file()->put_text(strCmd, str);
      dir()->create(m_pathTime / "dynamic_source");


   }


} // namespace programming



