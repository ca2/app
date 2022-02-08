// Created by camilo on 2021-11-15 15:39 BRT <3ThomasBorregaardS�rensen!!
#include "framework.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#ifdef WINDOWS_DESKTOP
#include "acme_windows/_.h"
#include "acme_windows/_acme_windows.h"
#endif


namespace programming
{


   compiler::compiler()
   {

      defer_create_mutex();

   }


   compiler::~compiler()
   {


   }


   void compiler::initialize_programming_compiler(::object* pobject)
   {

      //auto estatus = 
      
      ::object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

#ifdef WINDOWS_DESKTOP

      {

         auto pacmedir = m_psystem->m_pacmedir;

         ::file::path path;

         path = pacmedir->config() / "programming/vs.txt";

         auto pcontext = get_context();

         m_strVs = m_pcontext->m_papexcontext->file().as_string(path);

         m_strVs.trim();

         if (m_strVs == "2015")
         {

            m_strVsTools = "140";

         }
         else if (m_strVs == "2017")
         {

            m_strVsTools = "141";

         }
         else if (m_strVs == "2019")
         {

            m_strVsTools = "142";

         }
         else if (m_strVs == "2022")
         {

            m_strVsTools = "143";

         }
         else
         {

            string strMessage;

            strMessage = "There is a hole here. You should fill it with fullfillment. Missing f**k " + path;

            FATAL(strMessage);

         }

      }

#endif

      ::file::path path;

      path = THIS_FILE;

      m_pathProjectDir = path.folder();


#if MEMDLEAK

      m_strDynamicSourceConfiguration = "memdleak";
      m_strDynamicSourceStage = "stage";


#elif defined(_DEBUG)

      m_strDynamicSourceConfiguration = "basis";
      m_strDynamicSourceStage = "time-" OPERATING_SYSTEM_NAME;

#else

      m_strDynamicSourceConfiguration = "profiler";
      m_strDynamicSourceStage = "profiler";

#endif

      m_strDynamicSourceStageFolder = m_pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage;

      //return estatus;

   }


   void compiler::prepare_compile_and_link_environment()
   {

      auto pacmedir = m_psystem->m_pacmedir;

      m_pcontext->m_papexcontext->dir().create(pacmedir->system() / "netnodelite/symbols");

      ::file::path strVars;

#ifdef WINDOWS_DESKTOP

      if (m_strVs == "2015")
      {

         strVars = getenv("VS140COMNTOOLS");

      }

#endif

      __pointer(::aura::application) papplication = get_application();

#ifdef WINDOWS_DESKTOP

      try
      {

         if (m_strVs == "2022")
         {

            m_strEnv = "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvarsall.bat";

            m_strVCVersion = papplication->get_visual_studio_build();

         }
         else if (m_strVs == "2019")
         {

            m_strEnv = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvarsall.bat";

            m_strVCVersion = papplication->get_visual_studio_build();

         }
         else if (m_strVs == "2017")
         {

            m_strEnv = "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvarsall.bat";

            ::windows::registry::key key;

            key.open(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\VisualStudio\\SxS\\VS7", false);

            string strPath;

            key.get("15.0", strPath);

            ::file::path path = strPath;

            m_strEnv = path / "VC/Auxiliary/Build/vcvarsall.bat";

            m_strVCVersion = papplication->get_visual_studio_build();

         }
         else if (m_strVs == "2015")
         {

            m_strEnv = strVars.up(2);

            m_strEnv = m_strEnv / "vc\\vcvarsall.bat";

         }

      }
      catch (const ::e_status & estatus)
      {

         output_debug_string("failed to setup visual studio environment " + __string((::i64)estatus.m_estatus));

      }

#endif

      m_strTime = m_pcontext->m_papexcontext->dir().install() / ("time-" OPERATING_SYSTEM_NAME);

#ifdef WINDOWS_DESKTOP

      if (m_strVs == "2015")
      {

         m_strSdk1 = "vc140";

      }
      else if (m_strVs == "2017")
      {

         m_strSdk1 = "vc141";

      }
      else if (m_strVs == "2019")
      {

         m_strSdk1 = "vc142";

      }
      else if (m_strVs == "2022")
      {

         m_strSdk1 = "vc143";

      }

#endif

#ifdef OS64BIT

#ifdef LINUX

      m_strPlat1 = "64";
      m_strPlatform = "x86";
      m_strStagePlatform = "x86";
      m_strLibPlatform = "x86/";

#else

      m_strPlat1 = "64";
      m_strPlat2 = "x86_amd64";
      //m_strPlat2 = "amd64";
      m_strPlatform = "x64";
      m_strStagePlatform = "x64";
      m_strLibPlatform = "x64/";

#endif
#else

      m_strPlat1 = "32";
      m_strPlat2 = " x86";
      m_strPlatform = "Win32";
      m_strStagePlatform = "x86";
      m_strLibPlatform = "x86/";

#endif

#if defined(LINUX) || defined(MACOS)

      prepare1(m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash",
         m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash");
      prepare1(m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash",
         m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash");
      prepare1(m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 + ".bash",
         m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 + ".bash");

#else

      prepare1(m_strPlat1, m_strPlat1);

#endif

      m_pcontext->m_papexcontext->dir().create(m_pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage / "front");

      string str;

      string strItem;

      strItem = m_pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage / m_strStagePlatform;

      str = str + strItem + ";";

      strItem = m_pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage / m_strStagePlatform / "dynamic_source\\library";

      str = str + strItem + ";";

#ifdef WINDOWS_DESKTOP

      u32 dwSize = GetEnvironmentVariableW(L"PATH", nullptr, 0);
      LPWSTR lpsz = new wchar_t[dwSize + 1];
      dwSize = GetEnvironmentVariableW(L"PATH", lpsz, dwSize + 1);
      str += lpsz;
      delete lpsz;

#endif

   }


   void compiler::prepare1(const ::string& lpcszSource, const ::string& lpcszDest)
   {

      string_array stra;


      string strLog;


      __pointer(::application) papplication = get_application();


#ifdef WINDOWS
      //sleep(15000_ms);

      string strBuildCmd = m_strEnv;

      if (m_strVs == "2015")
      {

         strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2;

      }
      else if (m_strVs == "2017")
      {

         strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + papplication->get_visual_studio_build();

      }
      else if (m_strVs == "2019")
      {

         strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + papplication->get_visual_studio_build();

      }
      else if (m_strVs == "2022")
      {

         //strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + papplication->get_visual_studio_build();

         strBuildCmd = "\"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvars64.bat\"";

      }

      ::operating_system::process_pointer process(e_create, this);

      ::file::path pathEnvTxt;

      auto pacmedir = m_psystem->m_pacmedir;

      pathEnvTxt = pacmedir->system() / "env.txt";

      m_psystem->m_pacmefile->put_contents(pacmedir->system() / "env1.bat", pacmedir->system() / "env.bat > \"" + pathEnvTxt + "\"");

      m_psystem->m_pacmefile->put_contents(pacmedir->system() / "env.bat", "@call " + strBuildCmd + "\r\n@set");

      auto psystem = m_psystem;

      auto pnode = psystem->node();

      pnode->run_silent(pacmedir->system() / "env1.bat", "");

      strLog = m_psystem->m_pacmefile->as_string(pacmedir->system() / "env.txt");

      stra.add_lines(strLog);

      //sleep(10000_ms);

#ifdef WINDOWS_DESKTOP

      property_set setEnvironment;

      setEnvironment.parse_environment_variable(stra);

      for (auto& pproperty : setEnvironment)
      {

         SetEnvironmentVariableW(wstring(pproperty->m_atom), wstring(pproperty->string()));

      }



#endif
#endif

      //   ::file::path strFolder;
      //   strFolder = m_pcontext->m_papexcontext->dir().install();
      //   if (!::str::ends(strFolder, "/") && !::str::ends(strFolder, "\\"))
      //      strFolder += "/";
      //   string strTemplate;
      //   string strSource = "platform/time-" OPERATING_SYSTEM_NAME"/dynamic_source/";
      //   strSource += lpcszSource;
      //
      ::file::path pathN = m_pathProjectDir;
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
      //   str = m_pcontext->m_papexcontext->file().as_string(strTemplate);
      //   /*string strVars = getenv("VS100COMNTOOLS");
      //   m_pcontext->m_papexcontext->file().path().eat_end_level(strVars, 2, "/");
      //   strVars += "vc/bin/vcvars32.bat";*/
      //   str.replace("%VS_VARS%", m_strEnv);
      //   str.replace("%VS_VARS_PLAT2%", m_strPlat2);
      //
      //   string strV(m_pcontext->m_papexcontext->dir().install());
      //   strV.replace("\\", "/");
      //   if (!::str::ends(strV, "/") && !::str::ends(strV, "\\"))
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
      //   m_pcontext->m_papexcontext->dir().create(strCmd.folder());
      //   //m_pcontext->m_papexcontext->file().put_text_utf8(strCmd, str);
      //   m_pcontext->m_papexcontext->file().put_contents(strCmd, str);
      //   m_pcontext->m_papexcontext->dir().create(m_strTime / "dynamic_source");
      //
      //
      //   string strBuildCmd = m_strEnv;
      //
      //   strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2;
      //
      //   ::process::process_pointer process(e_create);
      //
      //
      //   m_psystem->m_pacmefile->put_contents(pacmedir->system() / "env.bat","@call " + strBuildCmd + " "+m_strVCVersion+"\r\n@set");
      //
      //   set_thread_priority(::e_priority_highest);
      //   process->prop("inherit") = false;
      //
      //   ::file::path pathCommand =          auto psystem = m_psystem;

      //         auto pacmedir = psystem->m_pacmedir;
      //
      //pacmedir->system() / "env.bat";
      //
      //   ::file::path pathFolder = ::file::path(m_strEnv).folder();
      //
      //#ifdef WINDOWS_DESKTOP
      //   {
      //      u32 dwSize = GetEnvironmentVariable("PATH", nullptr, 0);
      //      char * lpsz = new char[dwSize + 1];
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
      //   //   ::duration tickStart= ::duration::now();
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
      //   ::u32 tickStart= ::duration::now();
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
      //      char * lpsz = new char[dwSize + 1];
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

      //string strEnv = m_psystem->m_pacmefile->as_string(         auto psystem = m_psystem;

   //         auto pacmedir = psystem->m_pacmedir;
   //
   //pacmedir->system() / "env.txt");

      ::file::path strFolder;
      strFolder = m_pcontext->m_papexcontext->dir().install();
      if (!::str::ends(strFolder, "/") && !::str::ends(strFolder, "\\"))
         strFolder += "/";
      string strTemplate;
      string strSource = "operating-system/operating-system-" OPERATING_SYSTEM_NAME "/_stage/dynamic_source/";
      strSource += lpcszSource;

      //   string strN = m_pmanager->m_strNetnodePath;
            //strN.replace("\\","/");
            //if(!::str::ends(strN,"/") && !::str::ends(strN,"\\"))
            // strN += "/";

            //#ifdef _DEBUG
      strTemplate = strFolder / strSource;
      //#else
      // strTemplate = strFolder, "app/_stage/aura/account/app/main/matter/dynamic_source_cl.bat", false);
      //#endif
      string str;
      str = m_pcontext->m_papexcontext->file().as_string(strTemplate);
      /*string strVars = getenv("VS100COMNTOOLS");
      m_pcontext->m_papexcontext->file().path().eat_end_level(strVars, 2, "/");
      strVars += "vc/bin/vcvars32.bat";*/
      str.find_replace("%VS_VARS%", m_strEnv);
      str.find_replace("%VS_VARS_PLAT2%", m_strPlat2);

      string strV(m_pcontext->m_papexcontext->dir().install());
      strV.find_replace("\\", "/");
      if (!::str::ends(strV, "/") && !::str::ends(strV, "\\"))
         strV += "/";
      str.find_replace("%CA2_ROOT%", strV);
      str.find_replace("%PROJECT_DIR%", m_pathProjectDir);
      str.find_replace("%NETNODE_ROOT%", strN);
      str.find_replace("%SDK1%", m_strSdk1);
      //str.replace("%DVP%", strDVP_B);

      string strDest = m_strDynamicSourceStage / "front" / lpcszDest;
      ::file::path strCmd;
      //#ifdef _DEBUG
      strCmd = strFolder / strDest;
      //#else
      // strCmd = strFolder, "app\\_stage\\aura\\account\\app\\main\\front\\dynamic_source_cl.bat", false);
      //#endif
      m_pcontext->m_papexcontext->dir().create(strCmd.folder());
      //m_pcontext->m_papexcontext->file().put_text_utf8(strCmd, str);
      m_pcontext->m_papexcontext->file().put_text(strCmd, str);
      m_pcontext->m_papexcontext->dir().create(m_strTime / "dynamic_source");
   }


} // namespace programming



