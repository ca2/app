#include "framework.h"
#include "_.h"
#ifdef WINDOWS_DESKTOP
#include "acme_windows/_.h"
#include "acme_windows/_acme_windows.h"
#include "acme/os/windows/environment_variable.h"
#endif
#include "acme/filesystem/filesystem/acme_dir.h"





#include <sys/stat.h>


#if defined(LINUX)
#include <ctype.h>
#endif

::u32 RunSilent(const char* strFunct, const char* strstrParams);



namespace dynamic_source
{

   string escape(const char * pcsz);

   void add_var_id(string & strResult, strsize & iArroba, string_array & straId, bool bMakeKeyLower = true);


   script_compiler::script_compiler()
   {

   }


   script_compiler::~script_compiler()
   {

   }

   
   ::e_status script_compiler::initialize_dynamic_source_script_compiler(script_manager* pscriptmanager)
   {

      auto estatus = ::object::initialize(pscriptmanager);

      if (!estatus)
      {

         return estatus;

      }

      m_pmanager = pscriptmanager;

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
         else
         {

            string strMessage;

            strMessage = "There is a hole here. You should fill it with fullfillment. Missing f**k " + path;

            message_box(strMessage, strMessage, e_message_box_ok);

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
      m_strDynamicSourceStage = "time-" PLATFORM_NAME;

#else

      m_strDynamicSourceConfiguration = "profiler";
      m_strDynamicSourceStage = "profiler";

#endif

      m_strDynamicSourceStageFolder = m_pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage;

      return estatus;


   }


   ::e_status script_compiler::init1()
   {

      prepare_compile_and_link_environment();

      folder_watch();

      run_persistent();

      parse_pstr_set();

      return ::success;

   }


   void script_compiler::prepare_compile_and_link_environment()
   {

      auto pacmedir = m_psystem->m_pacmedir;

      m_pcontext->m_papexcontext->dir().mk(pacmedir->system() / "netnodelite/symbols");

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

         if (m_strVs == "2019")
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

         output_debug_string("failed to setup visual studio environment " + __str((::i64)estatus.m_estatus));

      }

#endif

      m_strTime = m_pcontext->m_papexcontext->dir().install() / "time-" PLATFORM_NAME;

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

#endif

#ifdef OS64BIT

#ifdef LINUX

      m_strPlat1     = "64";
      m_strPlatform = "x86";
      m_strStagePlatform = "x86";
      m_strLibPlatform = "x86/";

#else

      m_strPlat1     = "64";
      m_strPlat2 = "x86_amd64";
      //m_strPlat2 = "amd64";
      m_strPlatform = "x64";
      m_strStagePlatform = "x64";
      m_strLibPlatform = "x64/";

#endif
#else

      m_strPlat1     = "32";
      m_strPlat2 = " x86";
      m_strPlatform = "Win32";
      m_strStagePlatform = "x86";
      m_strLibPlatform = "x86/";

#endif

#if defined(LINUX) || defined(MACOS)

      prepare1(m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bash",
               m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bash");
      prepare1(m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bash",
               m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bash");
      prepare1(m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bash",
               m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bash");

#else

      prepare1(m_strPlat1,m_strPlat1);

#endif

      m_pcontext->m_papexcontext->dir().mk(m_pcontext->m_papexcontext->dir().install()/m_strDynamicSourceStage / "front");

      string str;

      string strItem;

      strItem = m_pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage /m_strStagePlatform;

      str = str + strItem + ";";

      strItem = m_pcontext->m_papexcontext->dir().install()/ m_strDynamicSourceStage /  m_strStagePlatform / "dynamic_source\\library";

      str = str + strItem + ";";

#ifdef WINDOWS_DESKTOP

      u32 dwSize = GetEnvironmentVariableW(L"PATH", nullptr, 0);
      LPWSTR lpsz = new wchar_t[dwSize + 1];
      dwSize = GetEnvironmentVariableW(L"PATH", lpsz, dwSize + 1);
      str += lpsz;
      delete lpsz;

#endif

   }


   void script_compiler::compile(ds_script * pscript)
   {

      synchronous_lock synchronouslock(pscript->mutex());

      TRACE("Compiling script \"%s\"\n",pscript->m_strName.c_str());

      ::text_stream & ostreamError = pscript->m_streamError;

      ::file::path strName(pscript->m_strName);

      if (strName.ends_ci("\\auth3.ds"))
      {

         ::output_debug_string("compile auth3.ds");

      }

      pscript->on_start_build();

#ifdef WINDOWS

      strName.replace("/","\\");

#endif

      //strName.replace("/", "\\");
      //string strFolder;
      //strFolder = m_pcontext->m_papexcontext->dir().install();
      string str;
      //::file::path strB;
      ::file::path strO;
      ::file::path strP;
      ::file::path strL;
      ::file::path strE;
      //::file::path strSVI;
      //::file::path strSVP;
      //::file::path strSPC;
      //::file::path strDVI;
      ::file::path strDVP;
      //::file::path strDPC;
      //::file::path strSO1;
      //::file::path strSO2;
      //::file::path strDO1;
      //::file::path strDO2;
      ::file::path strClog;
      ::file::path strLlog;
      ::file::path strObj;


      /*string strScript(strName);
      strScript.replace("\\", ",");
      strScript.replace("/", ",");
      strScript = "ca2" + m_pmanager->m_strNamespace + "_script." + strScript;*/
      ::file::path strScript;
      strScript = strName.title();
      ::file::path strTransformName = strName;
      if(m_pcontext->m_papexcontext->file().exists(strName))
      {
         pscript->m_strSourcePath = strName;
         strTransformName.replace(":","");
      }
      else
      {
         pscript->m_strSourcePath.Format(m_pmanager->m_strNetnodePath / "net\\%s",strName.c_str());
      }
      pscript->m_strSourceDir = pscript->m_strSourcePath.folder();

      if(!m_pcontext->m_papexcontext->file().exists(pscript->m_strSourcePath))
      {
         ostreamError << "<pre>";
         str.Format("Source File : \"%s\" does not exist",pscript->m_strSourcePath.c_str());
         ostreamError << str;
         ostreamError << "</pre>";
         return;
      }

      string strRndTitle;

      string strMillis;

      strMillis = __str(::get_millis() % 1000);

      ::ansi_zero_pad(strMillis, 3);

      auto psystem = m_psystem->m_paurasystem;

      auto pdatetime = psystem->datetime();

      strRndTitle = "_" + pdatetime->international().get_gmt_date_time("%Y-%m-%d_%H-%M-%S") + "_" + strMillis;

      string strTime = m_strTime;

      pscript->m_strCppPath.Format(m_strTime / "dynamic_source\\%s.cpp",strTransformName.c_str());

      //string strCompileLogUnique;

      ::datetime::time timeNow = ::datetime::time::get_current_time();

      string strCompileLogUnique = timeNow.Format(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE);

      strClog.Format(m_strTime / "dynamic_source/%s-compile-log-%s.txt",strTransformName.c_str(), strCompileLogUnique.c_str());
      strLlog.Format(m_strTime / "dynamic_source/%s-link-log.txt",strTransformName.c_str());

      string strPathCompiler;
      strPathCompiler.Format(m_strTime / "dynamic_source/%s-compiler.txt", strTransformName.c_str());
      ::file::path pathCompiler(strPathCompiler);

      string strPathLinker;
      strPathLinker.Format(m_strTime / "dynamic_source/%s-linker.txt", strTransformName.c_str());
      ::file::path pathLinker(strPathLinker);

      //#ifdef _DEBUG
#ifdef LINUX
      //strB = m_pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage / "front\\dynamic_source\\BuildBat" / strTransformName.name() / strTransformName + ".bat";
      strO = ::file::path(m_strTime) / "intermediate" / m_strPlatform / m_pmanager->m_strNamespace + "_dynamic_source_script" / strTransformName / strTransformName.name() + ".o";
#else
      //strB = m_strDynamicSourceStageFolder / "front\\dynamic_source\\BuildBat" / strTransformName.name() / strTransformName + ".bat";
      strP = m_strDynamicSourceStageFolder / m_strStagePlatform / "dynamic_source" / strTransformName.sibling(strScript.name()) + ".pdb";
      strL = m_strDynamicSourceStageFolder / m_strStagePlatform / "dynamic_source" / strTransformName.sibling(strScript.name()) + ".lib";
      strE = m_strDynamicSourceStageFolder / m_strStagePlatform / "dynamic_source" / strTransformName.sibling(strScript.name()) + ".exp";


      ::file::path strDynamicSourceScriptFolder = m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + "_dynamic_source_script";
      //strDVI = strDynamicSourceScriptFolder / strTransformName / m_strSdk1 + ".idb";



      //::file::path pathSourceDVP = strDynamicSourceScriptFolder / strTransformName / m_strSdk1 + ".pdb";
      ::file::path pathSourceNetnodeDSS = "C:\\netnode\\time-" PLATFORM_NAME "\\intermediate\\x64\\basis\\app-core\\netnode_dynamic_source_script";
      ::file::path pathSourceDVP = pathSourceNetnodeDSS / m_strSdk1 + ".pdb";

      //::file::path pathCompiler;

      {

         ::file::path pathHelper1 = strTransformName.sibling(strScript.name());

         string strHelper1 = pathHelper1.name() + "-" + m_strSdk1 + ".pdb";

         auto pathDVP0 = m_strDynamicSourceStageFolder / m_strStagePlatform / "dynamic_source" / pathHelper1.folder() / strHelper1;

         string strCompiler = pathHelper1.name() + "-compiler.txt";

         string strDVP1 = pathDVP0;

         solve_relative(strDVP1);

         strDVP = strDVP1;

         ::file::path pathDVP = strDVP;

         ::file::path pathDVP_Folder = pathDVP.folder();

         ::dir::mk(pathDVP_Folder);

         m_pcontext->m_papexcontext->file().copy(pathDVP, pathSourceDVP);


      }
      string strDVP_B = strDVP;
      strDVP_B.replace("\\", "/");




      //strDPC = strDynamicSourceScriptFolder / strTransformName / m_pmanager->m_strNamespace + "_dynamic_source_script.pch";
      //strDO1 = strDynamicSourceScriptFolder / strTransformName / "framework.obj";
      //strDO2 = strDynamicSourceScriptFolder / strTransformName / m_pmanager->m_strNamespace + "_dynamic_source_script.obj";
      //strSVI = strDynamicSourceScriptFolder / m_strSdk1 + ".idb";
      //strSVP = strDynamicSourceScriptFolder / m_strSdk1 + ".pdb";
      //strSPC = strDynamicSourceScriptFolder / m_pmanager->m_strNamespace + "_dynamic_source_script.pch";
      //strSO1 = strDynamicSourceScriptFolder / "framework.obj";
      //strSO2 = strDynamicSourceScriptFolder / m_pmanager->m_strNamespace + "_dynamic_source_script.obj";

      strObj = strDynamicSourceScriptFolder / strTransformName / strTransformName.name() + ".obj";

      strO = strDynamicSourceScriptFolder / strTransformName.name() / strTransformName + ".bat";

#endif

      pscript->m_strScriptPath = m_pmanager->get_script_path(strName, strRndTitle);

      try
      {
         if(m_pcontext->m_papexcontext->file().exists(strO))
         {
            m_pcontext->m_papexcontext->file().del(strO);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(m_pcontext->m_papexcontext->file().exists(strObj))
         {
            m_pcontext->m_papexcontext->file().del(strObj);
         }
      }
      catch(...)
      {
      }
#ifndef LINUX
      try
      {
         if(m_pcontext->m_papexcontext->file().exists(strP))
         {
            m_pcontext->m_papexcontext->file().del(strP);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(m_pcontext->m_papexcontext->file().exists(strL))
         {
            m_pcontext->m_papexcontext->file().del(strL);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(m_pcontext->m_papexcontext->file().exists(strE))
         {
            m_pcontext->m_papexcontext->file().del(strE);
         }
      }
      catch(...)
      {
      }
      //try
      //{
      //   if(m_pcontext->m_papexcontext->file().exists(strDPC))
      //   {
      //      m_pcontext->m_papexcontext->file().del(strDPC);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(m_pcontext->m_papexcontext->file().exists(strDVP))
      //   {
      //      m_pcontext->m_papexcontext->file().del(strDVP);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(m_pcontext->m_papexcontext->file().exists(strDVI))
      //   {
      //      m_pcontext->m_papexcontext->file().del(strDVI);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(m_pcontext->m_papexcontext->file().exists(strDO1))
      //   {
      //      m_pcontext->m_papexcontext->file().del(strDO1);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(m_pcontext->m_papexcontext->file().exists(strDO2))
      //   {
      //      m_pcontext->m_papexcontext->file().del(strDO2);
      //   }
      //}
      //catch(...)
      //{
      //}
#endif

      try
      {

         if(m_pcontext->m_papexcontext->file().exists(strClog))
         {

            m_pcontext->m_papexcontext->file().del(strClog);

         }

      }
      catch(...)
      {

      }

      try
      {

         if(m_pcontext->m_papexcontext->file().exists(strLlog))
         {

            m_pcontext->m_papexcontext->file().del(strLlog);

         }

      }
      catch(...)
      {

      }

      //::DeleteFile(pscript->m_strBuildBat);

      try
      {

         if(m_pcontext->m_papexcontext->file().exists(pscript->m_strScriptPath + ".old"))
         {

            m_pcontext->m_papexcontext->file().del(pscript->m_strScriptPath + ".old");

         }

      }
      catch (const ::exception::exception &)
      {

         //::exception_pointer esp(pexception);

         //TRACE("%s", esp->get_message().c_str());

      }

      try
      {

         if(m_pcontext->m_papexcontext->file().exists(pscript->m_strScriptPath))
         {

            m_pcontext->m_papexcontext->file().move(pscript->m_strScriptPath + ".old",pscript->m_strScriptPath);

         }

      }
      catch (const ::exception::exception &)
      {

         //::exception_pointer esp(pexception);

         //TRACE("%s", esp->get_message().c_str());

      }

      try
      {

         if(m_pcontext->m_papexcontext->file().exists(pscript->m_strScriptPath + ".old"))
         {

            m_pcontext->m_papexcontext->file().del(pscript->m_strScriptPath + ".old");

         }

      }
      catch (const ::exception::exception &)
      {

         //::exception_pointer esp(pexception);

         //TRACE("%s", esp->get_message().c_str());

      }


      m_pcontext->m_papexcontext->dir().mk(pscript->m_strScriptPath.folder());
      m_pcontext->m_papexcontext->dir().mk(strL.folder());
      m_pcontext->m_papexcontext->dir().mk(m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + ::file::path("_dynamic_source_script") / strTransformName);

      cppize(pscript);

      string strV(m_pcontext->m_papexcontext->dir().install());
      strV.replace("\\","/");
      if(!::str::ends(strV,"/") && !::str::ends(strV,"\\"))
         strV += "/";

      string strN = m_pmanager->m_strNetnodePath;
      strN.replace("\\","/");
      if(!::str::ends(strN,"/") && !::str::ends(strN,"\\"))
         strN += "/";

      string strObjFile;

      string strItemName = ::str::replace("\\", "/", string(strTransformName));

      string strItemTitle = strTransformName.name();

      ::file::path pathObjFile;


#ifdef WINDOWS

      {

         pathObjFile = strV;
         pathObjFile /= "time-" PLATFORM_NAME"/intermediate";
         pathObjFile /= m_strPlatform;
         pathObjFile /= m_strDynamicSourceConfiguration;
         pathObjFile /= "app-core/netnode_dynamic_source_script";
         pathObjFile /= strItemName;
         pathObjFile /= (strItemTitle + ".obj");

         strObjFile = pathObjFile;

      }

      strObjFile.replace("\\", "/");

#endif

      string strBuildCmd;

#if defined(LINUX) || defined(MACOS)
      strBuildCmd.Format(m_pcontext->m_papexcontext->dir().install() / "archive" / "platform-" PLATFORM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash");
#else
      strBuildCmd.Format(m_pcontext->m_papexcontext->dir().install() / "archive" / ("platform-" PLATFORM_NAME "\\_stage\\dynamic_source_" + m_strVsTools) / m_strDynamicSourceConfiguration + ::file::path("_c") + m_strPlat1 + ".bat");
#endif

      str = m_pcontext->m_papexcontext->file().as_string(strBuildCmd);
      str.replace("%ITEM_NAME%",strItemName);
      str.replace("%ITEM_TITLE%",strItemTitle);
      str.replace("%ITEM_DIR%",::str::replace("\\","/",string(strTransformName.folder())) + "/");
      str.replace("%LIBS_LIBS%",m_strLibsLibs);
      str.replace("%VS_VARS%",m_strEnv);
      str.replace("%VS_VARS_PLAT2%",m_strPlat2);


      str.replace("%CA2_ROOT%",strV);
      str.replace("%NETNODE_ROOT%",strN);
      str.replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
      str.replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
      str.replace("%PLATFORM%",m_strPlatform);
      str.replace("%STAGEPLATFORM%",m_strStagePlatform);
      //      str.replace("%LIBPLATFORM%", m_strLibPlatform);
      str.replace("%SDK1%",m_strSdk1);
      #ifdef LINUX
      str.replace("%DVP%", strDVP);
      #else
      str.replace("%DVP%", strDVP_B);
      #endif
      str.replace("%OBJFILE%", strObjFile);

      string strTargetPath = pscript->m_strScriptPath;
#ifdef LINUX
      ::str::ends_eat_ci(strTargetPath,".so");
#else
      ::str::ends_eat_ci(strTargetPath,".dll");
#endif
      str.replace("%TARGET_PATH%",strTargetPath);
      //strBuildCmd = pscript->m_strBuildBat;
      //m_pcontext->m_papexcontext->file().put_contents_utf8(strBuildCmd, str);

      ///m_pcontext->m_papexcontext->file().put_contents(strBuildCmd,str);

      bool bTimeout = false;

      ::process::process_pointer process(e_create);

      ::parallelization::set_priority(::priority_highest);

      //process->prop("inherit") = false;

      string strCompiler = str;

      m_pcontext->m_papexcontext->file().put_contents_utf8(pathCompiler, strCompiler);

#ifdef WINDOWS
      process->create_child_process(strCompiler,true,"C:\\netnode\\source\\app-core\\netnode_dynamic_source_script",::priority_highest);
#else
      process->create_child_process(strCompiler,true,m_pathProjectDir,::priority_highest);
#endif

      //::system(str + " > " + "\"" + strClog + "\"");

      auto tickStart = ::millis::now();

      string strLog;

      while(::task_get_run())
      {

         strLog += process->read();

         if(process->has_exited())
            break;

         sleep(100_ms);

         if(tickStart.elapsed() > 840 * 1000) // 14 minutes
         {

            bTimeout = true;

            break;

         }

      }

      strLog += process->read();

      if(bTimeout)
      {

         process->kill();

      }

      if(!bTimeout && strLog.has_char())
      {

#ifdef LINUX

         //sleep(2000_ms);

#endif

         str = strLog;

         str.trim();

         if(str.has_char())
         {

            m_pcontext->m_papexcontext->file().put_contents_utf8(strClog, strLog);

            ostreamError << "<pre>";

            //ostreamError << "Compiling Command\n";
            //ostreamError << pathCompiler << "\n";
            TRACE("Compiling Command File");
            TRACE(pathCompiler);
            //ostreamError << strCompiler << "\n";
            TRACE("Compiling Command");
            TRACE(strCompiler);
            ostreamError << "Compiling...\n";
            ostreamError << pscript->m_strCppPath;
            ostreamError << "\n";
            if(bTimeout)
            {
               ostreamError << "error: Timeout during compilation (If there are the compilation or link errors about the file \"" + pscript->m_strCppPath + "\" following this message, they may be out-of-date)";
            }
            str.replace("\r\n","\n");
            ostreamError << str;

         }

         int iObjFileMinimumByteCount = 1024;

         if (process->m_exitstatus.m_iExitCode != 0 || m_pcontext->m_papexcontext->file().length(pathObjFile) < iObjFileMinimumByteCount)
         {

            TRACE("Compilation FAILED: or object file is shorter than %d bytes...", iObjFileMinimumByteCount);

            string_array straLog;
            straLog.add_lines(strLog);
            for(auto & strLine : straLog)
            {
               int iColCount = 80;
               for (index i = 0; i < strLine.get_length(); i += iColCount)
               {
                  if (strLine.get_length() < i + iColCount + 10)
                  {
                     TRACE(strLine.Mid(i));
                     break;
                  }
                  else
                  {
                     TRACE(strLine.Mid(i, iColCount) + "\\...");
                  }
               }

            }

            ostreamError.to_string(pscript->m_strError);

            return;

         }

         //strBuildCmd;

#if defined(LINUX) || defined(MACOS)
         strBuildCmd.Format(m_pcontext->m_papexcontext->dir().install() / "archive" / "platform-" PLATFORM_NAME"\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash");
#else
         strBuildCmd.Format(m_pcontext->m_papexcontext->dir().install() / "archive" / ("platform-" PLATFORM_NAME "\\_stage\\dynamic_source_" + m_strVsTools) / m_strDynamicSourceConfiguration + ::file::path("_l") + m_strPlat1 + ".bat");
#endif

         str = m_pcontext->m_papexcontext->file().as_string(strBuildCmd);
         str.replace("%ITEM_NAME%",::str::replace("\\","/",string(strTransformName)));
         str.replace("%ITEM_TITLE%",strTransformName.name());
         str.replace("%ITEM_DIR%",::str::replace("\\","/",string(strTransformName.folder())) + "/");
         str.replace("%LIBS_LIBS%",m_strLibsLibs);
         str.replace("%VS_VARS%",m_strEnv);
         str.replace("%VS_VARS_PLAT2%",m_strPlat2);


         str.replace("%CA2_ROOT%",strV);
         str.replace("%NETNODE_ROOT%",strN);
         str.replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
         str.replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
         str.replace("%PLATFORM%",m_strPlatform);
         str.replace("%STAGEPLATFORM%",m_strStagePlatform);
         //      str.replace("%LIBPLATFORM%", m_strLibPlatform);
         str.replace("%SDK1%",m_strSdk1);
         #ifdef LINUX
         str.replace("%DVP%", strDVP);
         #else
         str.replace("%DVP%", strDVP_B);
         #endif
         str.replace("%OBJFILE%", strObjFile);

         string strTargetPath = pscript->m_strScriptPath;
#ifdef LINUX
         ::str::ends_eat_ci(strTargetPath,".so");
#else
         ::str::ends_eat_ci(strTargetPath,".dll");
#endif
         str.replace("%TARGET_PATH%",strTargetPath);
         string strHmhLctvWildPdbPath;

         string strSymbolName;

         strSymbolName = ::file::path(strTransformName).title();

         strSymbolName += strRndTitle;

         auto pacmedir = m_psystem->m_pacmedir;

         strHmhLctvWildPdbPath = ::file::path(pacmedir->system() / "netnodelite\\symbols") / strSymbolName;

         str.replace("%HMH_LCTVWILD_PDB_PATH%",strHmhLctvWildPdbPath);

         //strBuildCmd = pscript->m_strBuildBat;
         //m_pcontext->m_papexcontext->file().put_contents_utf8(strBuildCmd, str);

         //m_pcontext->m_papexcontext->file().put_contents(strBuildCmd,str);

         //str.replace("\\", "/");

         bTimeout = false;

         ::process::process_pointer process(e_create);

         ::parallelization::set_priority(::priority_highest);

         string strLinker(str);

         strLinker.replace("\\", "/");
         strLinker.trim();

         m_pcontext->m_papexcontext->file().put_contents_utf8(pathLinker, strLinker);

         process->create_child_process(strLinker,true,nullptr,::priority_highest);

         auto tickStart = ::millis::now();

         string strLog;

         while(::task_get_run())
         {

            strLog += process->read();

            if(process->has_exited())
               break;

            sleep(100_ms);

            if(tickStart.elapsed() > 840 * 1000) // 14 minutes
            {

               bTimeout = true;

               break;

            }

         }

         strLog += process->read();



         if(!bTimeout && strLog.has_char())
         {

#ifdef LINUX

            //sleep(2000_ms);

#endif



            str = strLog;

            str.trim();

            if(str.has_char())
            {

               m_pcontext->m_papexcontext->file().put_contents_utf8(strLlog,strLog);
               ostreamError << "Linking...\n";
               //ostreamError << "Linker Command File" << "\n";
               //ostreamError << pathLinker << "\n";
               INFO("Linker Command File %s", pathLinker.c_str());
               //ostreamError << "Linker Command" << "\n";
               //ostreamError << strLinker << "\n";
               INFO("Linker Command %s", strLinker.c_str());
               str.replace("\r\n","\n");
               ostreamError << str;
               ostreamError << "</pre>";


            }

            pscript->m_fileError.to_string(pscript->m_strError);

            pscript->m_strError.trim();

         }

      }

#ifndef LINUX

      //try
      //{
      //   m_pcontext->m_papexcontext->file().del(strDVI);
      //}
      //catch(...)
      //{
      //}
      try
      {
         m_pcontext->m_papexcontext->file().del(strDVP);
      }
      catch(...)
      {
      }
      //try
      //{
      //   m_pcontext->m_papexcontext->file().del(strDPC);
      //}
      //catch(...)
      //{
      //}

#endif

   }

   void script_compiler::cppize(ds_script * pscript)
   {

      auto ftDs = get_filetime_set(pscript->m_strSourcePath);

      if(m_pcontext->m_papexcontext->file().exists(pscript->m_strCppPath))
      {

         if(ftDs == pscript->m_ftDs)
         {

            return; // nothing to do

         }

      }

      m_pcontext->m_papexcontext->dir().mk(pscript->m_strCppPath.folder());

      cppize1(pscript);

      pscript->m_ftDs = ftDs;

   }

   string escape(const char * pcsz)
   {
      string str(pcsz);
      str.replace("\\", "\\\\");
      str.replace("\"", "\\\"");
      str.replace("\r\n", "\\r\\n");
      str.replace("\r", "\\r\\n");
      str.replace("\n", "\\r\\n");
      str.replace("\t", "\\t");
      return str;
   }

   void script_compiler::cppize1(ds_script * pscript)
   {
      /*file_pointer spfile(e_create);
      if(spfile->open(pscript->m_strSourcePath, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_none).failed())
      return;

      memory memstorage;
      memstorage.set_size(spfile->get_length() + 1);
      memstorage.get_data()[memstorage.get_size() - 1] = '\0';
      memstorage.read(file);*/

      string strSource;

      int iTry = 0;

      while ((strSource = m_pcontext->m_papexcontext->file().as_string(pscript->m_strSourcePath)).trimmed().is_empty() && ::task_get_run())
      {

         sleep(100_ms);

         iTry++;

         if (iTry > 256)
         {
            return;
         }

      }


      strsize iPosId = -1;
      string_array straId;
      string strDest;
      strDest = "";
      strDest += "#include \"netnode_dynamic_source_script_framework.h\"\r\n";
      //strDest += "#include \"11ca2_account.h\"\r\n";
      //for(i32 i = 0; i < m_straLibIncludePath.get_count(); i++)
      //{
      //   string str;
      //   str = m_straLibIncludePath[i].relative();
      //   ::str::ends_eat_ci(str, ".ds");
      //   strDest += "#include \""+str+".h\"\r\n";
      //}
      strsize iStart = 0;
      strsize iPos = 0;
      strsize iLastEnd = 0;
      if(strSource.Mid(0, 4) == "<?ss")
      {
         iLastEnd = strSource.find("?>", iPos);
         if(iLastEnd > 0)
         {
            iLastEnd += 2;
            strDest += cppize2(strSource.Mid(iPos + 4, iLastEnd - iPos - 6), false, straId);
            iStart = iLastEnd;
         }
      }
      else if(strSource.Mid(0, 7) == "<? //ss")
      {
         iLastEnd = strSource.find("?>", iPos);
         if(iLastEnd > 0)
         {
            iLastEnd += 2;
            strDest += cppize2(strSource.Mid(iPos + 7, iLastEnd - iPos - 7 - 2), false, straId);
            iStart = iLastEnd;
         }
      }
      string strDs;
      if(strSource.Mid(iStart, 4) == "<?ds")
      {
         iStart +=4;
         while(true)
         {
            strsize iMid = strSource.find("?>", iStart);
            iLastEnd = strSource.find("ds?>", iStart);
            if(iMid > 0 && iMid < iLastEnd)
            {
               strDs += cppize2(strSource.Mid(iStart, iMid - iStart), true, straId);
               iStart = iMid + 2;
               iMid = strSource.find("<?", iStart);
               if(iMid < iLastEnd)
               {
                  strDs += get_ds_print(strSource.Mid(iStart, iMid - iStart));
               }
               iStart = iMid + 2;
               continue;
            }
            if(iLastEnd > 0)
            {
               strDs += cppize2(strSource.Mid(iStart, iLastEnd - iStart), true, straId);
               iStart = iLastEnd + 4;
               iLastEnd = iStart;
            }
            break;
         }
      }
      strDest += "\r\n";
      strDest += "\r\n";
      iPosId = strDest.get_length();
      strDest += "\r\n";
      strDest += "\r\n";
      strDest += "\r\n";
      strDest += "#define _return return";
      strDest += "\r\n";
      strDest += "\r\n";
      strDest += "\r\n";
      strDest += "class " + m_pmanager->m_strNamespace + "_dynamic_source_script : virtual public ::application_consumer < ::netnode::application, ::" + m_pmanager->m_strNamespace + "::script_instance >\r\n";
      strDest += "{\r\n";
      strDest += "public:\r\n";
      //strDest += "   " + m_pmanager->m_strNamespace + "_dynamic_source_script(dynamic_source::script * pscript) : ::object(pscript->get_application()), dynamic_source::script_instance(pscript), ::" + m_pmanager->m_strNamespace + "::script_instance(pscript), ::" + m_pmanager->m_strNamespace + "::script_impl(pscript) {};  \r\n";
      strDest += "   " + m_pmanager->m_strNamespace + "_dynamic_source_script() {};\r\n";
      strDest += "   virtual ~" + m_pmanager->m_strNamespace + "_dynamic_source_script() {};\r\n";
      strDest += "   virtual ::e_status     run() {script_run(); return ::success; };\r\n";
      strDest += "   virtual void script_run();\r\n";
      strDest += "   \r\n\r\n";
      strDest += strDs;
      strDest += "   \r\n\r\n\r\n";
      strDest += "};\r\n";
      strDest += "\r\n";
      strDest += "extern \"C\" __declspec(dllexport) dynamic_source::script_instance * __cdecl create_dynamic_source_script_instance ()\r\n";
      strDest += "{\r\n";
      strDest += "   return new " + m_pmanager->m_strNamespace + "_dynamic_source_script();\r\n";
      strDest += "}\r\n";
      strDest += "\r\n";
      strDest += "void " + m_pmanager->m_strNamespace + "_dynamic_source_script::script_run()\r\n";
      strDest += "{\r\n";
      strDest += "//Start parsed user script\r\n";
      straId.erase_all();
      while((iPos = strSource.find("<?", iStart)) >= 0)
      {
         if(iPos > iLastEnd)
         {
            strDest += get_ds_print(strSource.Mid(iLastEnd, iPos - iLastEnd));
         }
         iLastEnd = strSource.find("?>", iPos);
         if(iLastEnd < 0)
            break;
         iLastEnd += 2;
         i32 iShift = 0;
         if(strSource.Mid(iPos, 5).compare_ci("<?php") == 0)
            iShift = 3;
         strDest += cppize2(strSource.Mid(iPos + 2 + iShift, iLastEnd - iPos - 4 - iShift), true, straId);
         iStart = iLastEnd;
      }
      strDest += get_ds_print(strSource.Mid(iStart));

      strDest += "//End parsed user script\r\n";
      //strDest += "return ::success;\r\n";
      strDest += "}\r\n";

      string strId;
      for(i32 i = 0; i < straId.get_size(); i++)
      {
         strId += "static ::id lscript_id" + __str(i) + "(\"" + straId[i] + "\");\r\n";
      }

      strDest = strDest.Left(iPosId) + strId + strDest.Mid(iPosId);


      string strCppPath =  pscript->m_strCppPath;

      strCppPath.replace("\\","\\\\");

//      strDest += " \r\n \
//         extern \"C\" i32 APIENTRY \r\n \
//         DllMain(HINSTANCE hInstance,u32 dwReason,LPVOID lpReserved) \r\n \
//      { \r\n \
//\r\n  \
// \r\n \r\n \
//         UNREFERENCED_PARAMETER(hInstance); \r\n \
//         UNREFERENCED_PARAMETER(lpReserved); \r\n \
// \r\n \
// \r\n \
//         if(dwReason == DLL_PROCESS_ATTACH) \r\n \
//         { \r\n \
// \r\n \
// \r\n \
//             ::output_debug_string(\"netnodelite script initializing : " + strCppPath + "!\\n\"); \r\n \
// \r\n \
// \r\n \
//         } \r\n \
//         else if(dwReason == DLL_PROCESS_DETACH) \r\n \
//         { \r\n \
// \r\n \
// \r\n \
//            ::output_debug_string(\"netnodelite script terminating : " + strCppPath + "!\\n\"); \r\n \
// \r\n \
// \r\n \
//         } \r\n \
// \r\n \
//         return 1;    \r\n \
// \r\n \
//      }\r\n\r\n\r\n\r\n\r\n";

      //m_pcontext->m_papexcontext->file().put_contents_utf8(pscript->m_strCppPath, strDest);
      m_pcontext->m_papexcontext->file().put_contents(pscript->m_strCppPath, strDest);

   }

   void script_compiler::prepare1(const char * lpcszSource, const char * lpcszDest)
   {

      string_array stra;


      string strLog;


      __pointer(::apex::application) papplication = get_application();


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
      ::process::process_pointer process(e_create);


      ::file::path pathEnvTxt;

      auto pacmedir = m_psystem->m_pacmedir;

      pathEnvTxt = pacmedir->system() / "env.txt";

      file_put_contents(pacmedir->system() / "env1.bat", pacmedir->system() / "env.bat > \"" + pathEnvTxt + "\"");

      file_put_contents(pacmedir->system() / "env.bat", "@call " + strBuildCmd + "\r\n@set");

      RunSilent(pacmedir->system() / "env1.bat", "");

      strLog = file_as_string(pacmedir->system() / "env.txt");

      stra.add_lines(strLog);

      //sleep(10000_ms);

#ifdef WINDOWS_DESKTOP

      property_set setEnvironment;

      setEnvironment.parse_environment_variable(stra);

      for (auto & pproperty : setEnvironment)
      {

         SetEnvironmentVariableW(wstring(pproperty->m_id), wstring(pproperty->get_string()));

      }



#endif
#endif

//   ::file::path strFolder;
//   strFolder = m_pcontext->m_papexcontext->dir().install();
//   if (!::str::ends(strFolder, "/") && !::str::ends(strFolder, "\\"))
//      strFolder += "/";
//   string strTemplate;
//   string strSource = "platform/time-" PLATFORM_NAME"/dynamic_source/";
//   strSource += lpcszSource;
//
      ::file::path pathN = m_pathProjectDir;
      pathN -= 3;
      string strN = pathN;
      strN.replace("\\", "/");
      strN += "/";
//
//
//   //#ifdef _DEBUG
//   strTemplate = strFolder / strSource;
//   //#else
//   // strTemplate = strFolder, "app/time-" PLATFORM_NAME"/aura/account/app/main/matter/dynamic_source_cl.bat", false);
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
//   // strCmd = strFolder, "app\\time-" PLATFORM_NAME"\\aura\\account\\app\\main\\front\\dynamic_source_cl.bat", false);
//   //#endif
//   m_pcontext->m_papexcontext->dir().mk(strCmd.folder());
//   //m_pcontext->m_papexcontext->file().put_contents_utf8(strCmd, str);
//   m_pcontext->m_papexcontext->file().put_contents(strCmd, str);
//   m_pcontext->m_papexcontext->dir().mk(m_strTime / "dynamic_source");
//
//
//   string strBuildCmd = m_strEnv;
//
//   strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2;
//
//   ::process::process_pointer process(e_create);
//
//
//   file_put_contents(pacmedir->system() / "env.bat","@call " + strBuildCmd + " "+m_strVCVersion+"\r\n@set");
//
//   set_thread_priority(::priority_highest);
//   process->prop("inherit") = false;
//
//   ::file::path pathCommand = pacmedir->system() / "env.bat";
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
//   process->create_child_process(pathCommand,true,pathFolder,::priority_highest);
//   string strLog;
//
//   //   EnvVarValArray arrEnvVarVal;
//
//   //   millis tickStart= ::millis::now();
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
//   ::u32 tickStart= ::millis::now();
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

      //string strEnv = file_as_string(pacmedir->system() / "env.txt");

      ::file::path strFolder;
      strFolder = m_pcontext->m_papexcontext->dir().install();
      if(!::str::ends(strFolder, "/") && !::str::ends(strFolder, "\\"))
         strFolder += "/";
      string strTemplate;
      string strSource = "archive/platform-" PLATFORM_NAME "/_stage/dynamic_source/";
      strSource += lpcszSource;

//   string strN = m_pmanager->m_strNetnodePath;
      //strN.replace("\\","/");
      //if(!::str::ends(strN,"/") && !::str::ends(strN,"\\"))
      // strN += "/";

      //#ifdef _DEBUG
      strTemplate = strFolder/ strSource;
      //#else
      // strTemplate = strFolder, "app/_stage/aura/account/app/main/matter/dynamic_source_cl.bat", false);
      //#endif
      string str;
      str = m_pcontext->m_papexcontext->file().as_string(strTemplate);
      /*string strVars = getenv("VS100COMNTOOLS");
      m_pcontext->m_papexcontext->file().path().eat_end_level(strVars, 2, "/");
      strVars += "vc/bin/vcvars32.bat";*/
      str.replace("%VS_VARS%", m_strEnv);
      str.replace("%VS_VARS_PLAT2%", m_strPlat2);

      string strV(m_pcontext->m_papexcontext->dir().install());
      strV.replace("\\","/");
      if(!::str::ends(strV,"/") && !::str::ends(strV,"\\"))
         strV += "/";
      str.replace("%CA2_ROOT%",strV);
      str.replace("%PROJECT_DIR%", m_pathProjectDir);
      str.replace("%NETNODE_ROOT%", strN);
      str.replace("%SDK1%", m_strSdk1);
      //str.replace("%DVP%", strDVP_B);

      string strDest = m_strDynamicSourceStage / "front"  / lpcszDest;
      ::file::path strCmd;
      //#ifdef _DEBUG
      strCmd = strFolder/ strDest;
      //#else
      // strCmd = strFolder, "app\\_stage\\aura\\account\\app\\main\\front\\dynamic_source_cl.bat", false);
      //#endif
      m_pcontext->m_papexcontext->dir().mk(strCmd.folder());
      //m_pcontext->m_papexcontext->file().put_contents_utf8(strCmd, str);
      m_pcontext->m_papexcontext->file().put_contents(strCmd, str);
      m_pcontext->m_papexcontext->dir().mk(m_strTime/ "dynamic_source");
   }


   void script_compiler::handle_file_action(::file::action * paction)
   {

      synchronous_lock synchronouslock(&m_mutex);

      ::file::path path = paction->m_pathFolder / paction->m_pathFile;

      string strTransfer = path;

      // does not transfer
      if(::str::find_ci("netnode_persistent_ui_str", strTransfer) >= 0)
         return;

      auto psystem = m_psystem->m_paurasystem;

      if(m_straSync.get_count() > 1)
      {
         for(i32 i = 1; i < m_straSync.get_count(); i++)
         {

            property_set set;

            auto purl = psystem->url();

            m_pcontext->m_papexcontext->http().get("http://" + m_straSync[i] + "/synchronization_object?src=" +m_straSync[0] + "&url=" + purl->url_encode(strTransfer) + "&pwd=sym123&authnone=1", set);

         }

      }

      if(::str::begins(path, m_pmanager->m_strNetseedDsCa2Path/ "library/include"))
      {

         m_pmanager->m_pcache->set_all_out_of_date();

      }
      else if(::str::begins(path, m_pmanager->m_strNetseedDsCa2Path / "library/source"))
      {

      }
      else if(defer_run_persistent(path))
      {
      }
      else
      {

         m_pmanager->m_pcache->set_out_of_date(path);

      }

   }


   void script_compiler::folder_watch()
   {

      m_filewatcherid  = m_pcontext->m_papexcontext->dir().watcher().add_watch(m_pmanager->m_strNetseedDsCa2Path, this, true);

   }


   library & script_compiler::lib(const char * pszLibrary)
   {

      single_lock slLibrary(&m_mutexLibrary,true);

      auto p = m_mapLib.plookup(pszLibrary);

      if(p != nullptr)
      {
         return *p->element2();
      }

      m_mapLib[pszLibrary] = __new(library(this));

      library & l = *m_mapLib[pszLibrary];


      string strV(m_pcontext->m_papexcontext->dir().install());
      strV.replace("\\","/");
      if(!::str::ends(strV,"/") && !::str::ends(strV,"\\"))
         strV += "/";

      string strN = m_pmanager->m_strNetnodePath;
      strN.replace("\\","/");
      if(!::str::ends(strN,"/") && !::str::ends(strN,"\\"))
         strN += "/";


      //unload_library();

      string strLibrary(pszLibrary);

      ::file::path strName = strLibrary;

      m_strLibsLibs = m_pcontext->m_papexcontext->dir().install() / "time-" PLATFORM_NAME"/library" / m_strStagePlatform / "/library/"+strLibrary+".lib";

      //m_memfileLibError.set_length(0);
      string strFolder;
      strFolder = m_pcontext->m_papexcontext->dir().install();


      auto papplication = get_application();

      l.m_straLibSourcePath.m_pprovider = papplication;

      l.m_straLibSourcePath.clear_results();

      auto pcontext = m_pcontext;

      pcontext->m_papexcontext->dir().rls(l.m_straLibSourcePath, m_pmanager->m_strNetseedDsCa2Path / "library" / strName);

      for(i32 i = 0; i < l.m_straLibSourcePath.get_size();)
      {
         if(l.m_straLibSourcePath[i].ext() != "ds" && l.m_straLibSourcePath[i].ext() != "cpp")
         {
            l.m_straLibSourcePath.erase_at(i);
         }
         else
         {
            i++;
         }
      }
      l.m_straLibCppPath.erase_all();
      ::file::path strLibRel = ::file::path("dynamic_source/library") / strName;
      for(i32 i = 0; i < l.m_straLibSourcePath.get_size(); i++)
      {
         string str = l.m_straLibSourcePath[i].relative();
         ::str::ends_eat_ci(str,".ds");
         str.replace(":","");
         l.m_straLibCppPath.add(m_strTime / strLibRel / str + ".cpp");
      }
      l.m_straLibIncludePath.m_pprovider = papplication;
      l.m_straLibIncludePath.clear_results();
      pcontext->m_papexcontext->dir().rls(l.m_straLibIncludePath, m_pmanager->m_strNetseedDsCa2Path / "library" / strName);
      for(i32 i = 0; i < l.m_straLibIncludePath.get_size();)
      {
         if(l.m_straLibIncludePath[i].ext() != "h"
               || ::str::find_ci(l.m_straLibIncludePath[i],"\\.svn\\") >= 0
               || m_pcontext->m_papexcontext->dir().is(l.m_straLibIncludePath[i]))
         {
            l.m_straLibIncludePath.erase_at(i);
         }
         else
         {
            i++;
         }
      }
      l.m_straLibHppPath.erase_all();
      for(i32 i = 0; i < l.m_straLibIncludePath.get_size(); i++)
      {
         string str = l.m_straLibIncludePath[i].relative();
         ::str::ends_eat_ci(str,".ds");
         str.replace(":","");
         l.m_straLibHppPath.add(m_strTime / strLibRel / str + ".h");
      }

      string strLib(strName.name());


      //#ifdef _DEBUG
#ifdef LINUX
      l.m_strLibraryPath = "/aura/" / m_strDynamicSourceStage / "x86/libnetnodelibrary.so";
#else
      l.m_strLibraryPath = m_pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage / m_strStagePlatform / "dynamic_source/" / strName / strLib + ".dll";
#endif
      //#else
      // plib->m_strLibraryPath.Format(strFolder, "app/_stage/aura/account/app/main/front/Release/%s.dll", false), strName);
      //#endif

      m_pcontext->m_papexcontext->dir().mk(l.m_strLibraryPath.folder());
      m_pcontext->m_papexcontext->dir().mk(m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + "_dynamic_source_library/library");

      for(i32 i = 0; i < l.m_straLibIncludePath.get_size(); i++)
      {
         cppize(l.m_straLibIncludePath[i],l.m_straLibHppPath[i],cpptype_include);
      }


//      string strN = m_pmanager->m_strNetnodePath;
      //    strN.replace("\\","/");
      //  if(!::str::ends(strN,"/") && !::str::ends(strN,"\\"))
      //   strN += "/";


#ifdef WINDOWS
      string vars1batSrc;
      string vars2batSrc;
      string vars1batDst;
      string vars2batDst;
      vars1batSrc = m_pcontext->m_papexcontext->dir().install() / "archive" / "platform-" PLATFORM_NAME "/_stage/dynamic_source/vc_vars.bat";
      vars2batSrc = m_pcontext->m_papexcontext->dir().install() / "archive" / "platform-" PLATFORM_NAME "/_stage/dynamic_source/vc_vars_query_registry.bat";
      vars1batDst = m_pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage / "front/vc_vars.bat";
      vars2batDst = m_pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage / "front/vc_vars_query_registry.bat";
      try
      {
         m_pcontext->m_papexcontext->file().copy(vars1batDst,vars1batSrc,false);
      }
      catch(...)
      {
      }
      try
      {
         m_pcontext->m_papexcontext->file().copy(vars2batDst,vars2batSrc,false);
      }
      catch(...)
      {
      }

#endif

      for(i32 i = 0; i < l.m_straLibSourcePath.get_size(); i++)
      {
         if(l.m_straLibSourcePath[i].ext() == "cpp")
         {
            file_copy_dup(l.m_straLibCppPath[i], l.m_straLibSourcePath[i], false);
         }
         else
         {
            cppize(l.m_straLibSourcePath[i],l.m_straLibCppPath[i],cpptype_source);

         }
         string strRel = l.m_straLibSourcePath[i].relative();
         ::str::ends_eat_ci(strRel,".ds");
         ::str::ends_eat_ci(strRel,".cpp");
         strRel.replace("\\","/");
         ::file::path str1;
         str1 = "library/source" / strRel;
         string strCmd;
         //#ifdef _DEBUG
//#ifdef LINUX
//         strCmd = m_pcontext->m_papexcontext->dir().install()/ m_strDynamicSourceStage / "front"/ m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash";
//#else
//         strCmd = m_pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage / "front" / m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bat";
//#endif
#ifdef LINUX
         strCmd.Format(m_pcontext->m_papexcontext->dir().install() / "archive" / "platform-" PLATFORM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash");
#else
         strCmd.Format(m_pcontext->m_papexcontext->dir().install() / "archive" / "platform-" PLATFORM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + ::file::path("_libc") + m_strPlat1 + ".bat");
#endif

         //#else
         //    strCmd.Format(strFolder, "app\\_stage\\aura\\account\\app\\main\\front\\dynamic_source_cl.bat", false));
         //#endif
         string str = m_pcontext->m_papexcontext->file().as_string(strCmd);


         str.replace("%ITEM_NAME%",::str::replace("\\","/",string(l.m_straLibCppPath[i])));
         str.replace("%ITEM_TITLE%",l.m_straLibCppPath[i].name());
         str.replace("%ITEM_DIR%",::str::replace("\\","/",string(l.m_straLibCppPath[i].folder())) + "/");
         str.replace("%LIBS_LIBS%",m_strLibsLibs);
         str.replace("%VS_VARS%",m_strEnv);
         str.replace("%VS_VARS_PLAT2%",m_strPlat2);


         str.replace("%CA2_ROOT%",strV);
         str.replace("%NETNODE_ROOT%",strN);
         str.replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
         str.replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
         str.replace("%PLATFORM%",m_strPlatform);
         str.replace("%STAGEPLATFORM%",m_strStagePlatform);
         //      str.replace("%LIBPLATFORM%", m_strLibPlatform);
         str.replace("%SDK1%",m_strSdk1);
         //str.replace("%DVP%", strDVP_B);


         //str.replace("%ITEM_NAME%",::str::replace("\\","/",string(str1)));
         //str.replace("%ITEM_DIR%",::str::replace("\\", "/", string(str1.folder())) +"/" );
         str.replace("%PLATFORM%",m_strPlatform);
         str.replace("%STAGEPLATFORM%",m_strStagePlatform);
         str.replace("%NETNODE_ROOT%",strN);
         str.replace("%LIBPLATFORM%",m_strLibPlatform);
         str.replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
         str.replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
         str.replace("%SDK1%",m_strSdk1);
         //str.replace("%DVP%", strDVP_B);

         m_pcontext->m_papexcontext->dir().mk(m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + "_dynamic_source_library" / str1.folder());
         m_pcontext->m_papexcontext->dir().mk(m_strTime / "library" / m_strStagePlatform / str1.folder());

         string strFormat = "libc-" + str1;

         strFormat.replace("/","-");
         strFormat.replace("\\","-");

#ifdef LINUX
         strFormat += ".bash";
#else
         strFormat += ".bat";
#endif
         strCmd = m_pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage / "front" / strFormat;

         bool bTimeout = false;

         ::process::process_pointer process(e_create);

         ::parallelization::set_priority(::priority_highest);

         process->create_child_process(str,true,nullptr,::priority_highest);
auto tickStart = ::millis::now();

         //u32 dwExitCode;

         string strLog;

         while(::task_get_run())
         {

            strLog += process->read();

            if(process->has_exited())
               break;

            sleep(100_ms);

            if(tickStart.elapsed() > 840 * 1000) // 14 minutes
            {

               bTimeout = true;

               break;

            }

         }

         strLog += process->read();

         if(bTimeout)
         {

            process->kill();

         }
         string strClog;
         strClog = m_strTime / strLibRel / strRel +"-compile-log.txt";

         ::file::path pathCompiler = m_strTime / strLibRel / strRel + "-compile-log.txt";


         if(!bTimeout && strLog.has_char())
         {

#ifdef LINUX

            //sleep(2000_ms);

#endif



            str = strLog;

            str.trim();


            if(str.has_char())
            {

               m_pcontext->m_papexcontext->file().put_contents_utf8(strClog,strLog);

               l.m_memfileError << "<pre>";

               l.m_memfileError << "Compiling...\n";
               l.m_memfileError << l.m_straLibCppPath[i];
               l.m_memfileError << "\n";
               if(bTimeout)
               {
                  l.m_memfileError << "error: Timeout during compilation (If there are the compilation or link errors about the file \"" + l.m_straLibCppPath[i] + "\" following this message, they may be out-of-date)";
               }
               str.replace("\r\n","\n");
               l.m_memfileError << str;

            }

            l.m_strError = l.m_memfileError;

            l.m_strError.trim();

         }


      }

      string strObjs;
      for(i32 i = 0; i < l.m_straLibSourcePath.get_size(); i++)
      {
         strObjs += " ";
         ::file::path strRel = l.m_straLibSourcePath[i].relative();
         ::str::ends_eat_ci(strRel,".ds");
         strObjs += m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + "_dynamic_source_library/library" / strName;
         strObjs += m_strTime.sep();
         strObjs += strRel;
#ifdef LINUX
         strObjs+=".o";
#else
         strObjs+=".obj";
#endif
         strObjs += " ";
      }
      ::file::path strCmd;
      //#ifdef _DEBUG
//      strCmd = m_pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage / "front" / m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 +
//#ifdef LINUX
//         ".bash";
//#else
//         ".bat";
//#endif
#ifdef LINUX
      strCmd.Format(m_pcontext->m_papexcontext->dir().install() / "archive" / "platform-" PLATFORM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 + ".bash");
#else
      strCmd.Format(m_pcontext->m_papexcontext->dir().install() / "archive" / "platform-" PLATFORM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + ::file::path("_libl") + m_strPlat1 + ".bat");
#endif
      //#else
      // strCmd.Format(strFolder, "app\\_stage\\aura\\account\\app\\main\\front\\dynamic_source_libl.bat", false));
      //#endif
      string str = m_pcontext->m_papexcontext->file().as_string(strCmd);
      str.replace("%ITEM_NAME%",::file::path("library")/strName);
      str.replace("%ITEM_DIR%","library");
      str.replace("%OBJECTS%",strObjs);
      str.replace("%PLATFORM%",m_strPlatform);
      str.replace("%STAGEPLATFORM%",m_strStagePlatform);
      str.replace("%NETNODE_ROOT%",strN);
      str.replace("%LIBPLATFORM%",m_strLibPlatform);
      str.replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
      str.replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
      str.replace("%SDK1%",m_strSdk1);
      //str.replace("%DVP%", strDVP_B);

      string strTargetName = l.m_strLibraryPath;
      ::str::ends_eat_ci(strTargetName,".dll");
      str.replace("%TARGET_NAME%", strTargetName);
      m_pcontext->m_papexcontext->dir().mk(m_pcontext->m_papexcontext->dir().install()/ m_strDynamicSourceStage / m_strStagePlatform /"library");
//#ifdef LINUX
//      //sleep(2000_ms);
//      strCmd = m_pcontext->m_papexcontext->dir().install()/m_strDynamicSourceStage/ "front\\libl1.bash";
//#else
//      strCmd = m_pcontext->m_papexcontext->dir().install()/ m_strDynamicSourceStage / "front\\libl1.bat";
//#endif

      //m_pcontext->m_papexcontext->file().put_contents_utf8(strCmd, str);
      bool bTimeout = false;

      ::process::process_pointer process(e_create);

      ::parallelization::set_priority(::priority_highest);

      process->create_child_process(str,true,nullptr,::priority_highest);
auto tickStart = ::millis::now();

      string strLog;

      while(::task_get_run())
      {

         strLog += process->read();

         if(process->has_exited())
            break;

         sleep(100_ms);

         if(tickStart.elapsed() > 840 * 1000) // 14 minutes
         {

            bTimeout = true;

            break;

         }

      }

      strLog += process->read();

      if(bTimeout)
      {

         process->kill();

      }

      string strLlog;

      strLlog = m_strTime / strLibRel / "link-log.txt";

      if(!bTimeout && strLog.has_char())
      {

#ifdef LINUX

         //sleep(2000_ms);

#endif

         str = strLog;

         str.trim();

         if(str.has_char())
         {

            m_pcontext->m_papexcontext->file().put_contents_utf8(strLlog,strLog);
            l.m_memfileError << "Linking...\n";
            str.replace("\r\n","\n");
            l.m_memfileError << str;
            l.m_memfileError << "</pre>";

         }

         l.m_strError = l.m_memfileError;

         l.m_strError.trim();

      }

      l.load_library();

      return l;

   }


   void script_compiler::cppize(const ::file::path & lpcszSource,const ::file::path & lpcszDest,ecpptype enum_type)
   {

      m_pcontext->m_papexcontext->dir().mk(lpcszDest.folder());

      cppize1(lpcszSource, lpcszDest, enum_type);

   }


   void script_compiler::cppize1(const ::file::path & lpcszSource,const ::file::path & lpcszDest,ecpptype enum_type)
   {

      string strSource = m_pcontext->m_papexcontext->file().as_string(lpcszSource);

      bool bCode = false;

      string strDest;
      strDest = "";
      strDest = "";
      if(enum_type == cpptype_source || enum_type == cpptype_ds)
      {
         strDest += "#include \"netnode_dynamic_source_script.h\"\r\n";
         //strDest += "#include \"11ca2_account.h\"\r\n";
         //for(i32 i = 0; i < m_straLibIncludePath.get_count(); i++)
         //{
         //   string str;
         //   str = m_straLibIncludePath[i].relative();
         //   ::str::ends_eat_ci(str, ".ds");
         //   strDest += "#include \""+str+".h\"\r\n";
         //}
      }

      strDest += "\r\n";
      strDest += "\r\n";
      strsize iPosId = strDest.get_length();
      strDest += "\r\n";
      strDest += "\r\n";

      strsize iStart = 0;
      strsize iPos = 0;
      strsize iLastEnd = 0;
      string_array straId;
      while((iPos = strSource.find("<?", iStart)) >= 0)
      {
         if(iPos > iLastEnd && bCode)
         {
            strDest += get_ds_print(strSource.Mid(iLastEnd, iPos - iLastEnd));
         }
         iLastEnd = strSource.find("?>", iPos);
         if(iLastEnd < 0)
            break;
         iLastEnd += 2;
         i32 iShift = 0;
         if(strSource.Mid(iPos, 5).compare_ci("<?php") == 0)
            iShift = 3;
         bCode = true;
         strDest += cppize2(strSource.Mid(iPos + 2 + iShift, iLastEnd - iPos - 4 - iShift), false, straId);
         iStart = iLastEnd;
      }
      /*   strDest += "   print(\"" ;
      strDest += escape(strSource.Mid(iStart));
      strDest += "\");\r\n";
      strDest += "//End parsed user script\r\n";
      strDest += "}\r\n";*/

      string strId;
      for(i32 i = 0; i < straId.get_size(); i++)
      {
         strId += "static ::id lscript_id" + __str(i) + "(\"" + straId[i] + "\");\r\n";
      }

      strDest = strDest.Left(iPosId) + strId + strDest.Mid(iPosId);

      //m_pcontext->m_papexcontext->file().put_contents_utf8(lpcszDest, strDest);
      m_pcontext->m_papexcontext->file().put_contents(lpcszDest, strDest);


   }


   void add_var_id(string & strResult, strsize & iArroba, string_array & straId, bool bMakeKeyLower)
   {
      string strKey = strResult.Mid(iArroba);
      if(bMakeKeyLower)
      {
         strKey.make_lower();
      }
      strsize iFind = straId.find_first(strKey);
      if(iFind <= 0)
      {
         straId.add(strKey);
         iFind = straId.get_upper_bound();
      }
      strResult = strResult.Left(iArroba) + " lscript_id" + __str(iFind);
      iArroba = -1;
   }

   string script_compiler::cppize2(const string & psz,bool bScript,string_array & straId)
   {
      string str(psz);
      str.trim();
      bool bInSimpleQuote = false;
      bool bInDoubleQuote = false;
      strsize iSimpleQuote = 0;
      strsize iArroba = -1;
      bool bInVar = false;
      bool bInSlash = false;
      bool bInRet = false;
      bool bInSpec1 = false;
      bool bInSpec1Close = false;
      bool bInSpec2 = false;
      bool bInSpec2Close = false;
      bool bServer = false;
      strsize iServer = -1;
      strsize iBracket = 0;
      bool bInBrace = false;
      strsize iVar = -1;
      strsize iIdLen = 0;
      char ch;
      char chNext;
      string strResult;
      strsize iLen = str.get_length();
      strsize i = 0;
      bool bInitial = true;
      string strSpec1;
      strsize iOpenParen = 1; // open Parenthesis Count
      string_array straFunction;
      index_array iaFunctionParen; // index of the parenthesis of the function
      bool bInserted = false;
      bool bNewLine = true;
      bool bLow = false;
      while(i < iLen)
      {
         bInserted = false;
         ch = str[i];
         chNext = str[i + 1];
         if(::str::begins(str.Mid(i), "bk_filter_active1"))
         {
            //debug_break();
         }
         if(bInSpec1)
         {
            if(ch == '\r' || ch == '\n')
            {
               bNewLine = true;
               i++;
            }
            else if(isspace(ch))
            {
               i++;
               continue;
            }
            else if(ch == '(')
            {
               strResult += strSpec1 + "(";
               bInSpec1 = false;
               i++;
               bNewLine = false;
               continue;
            }
            else
            {
               strResult += strSpec1 + "(";
               bInSpec1Close = true;
               bInSpec1 = false;
            }
         }
         if(bInSpec2)
         {
            if(ch == '\r' || ch == '\n')
            {
               bNewLine = true;
               i++;
            }
            else if(isspace(ch))
            {
               i++;
               continue;
            }
            else if(ch == '=')
            {
               strResult += ".vara().add(";
               bInSpec2 = false;
               bInSpec2Close = true;
               i++;
               bNewLine = false;
               continue;
            }
            else
            {
               ///erro
            }
         }
         if(bServer)
         {
            if(isalpha(ch) || isdigit(ch) || ch == '.' || ch == ',' || ch == '-' || ch == '_')
            {
               if(iServer < 0)
               {
                  iServer = strResult.get_length();
               }
            }
            else if(iServer >= 0)
            {
               bool bWaitQuote = true;
               bool bWaitCloseBracket = false;
               bServer = false;
               add_var_id(strResult, iServer, straId);
               strResult += "]";
               while(i < iLen)
               {
                  ch = str[i];
                  if(isspace(ch))
                     i++;
                  else if(bWaitQuote && (ch == '\'' || ch=='\"'))
                  {
                     bWaitQuote = false;
                     bWaitCloseBracket = true;
                     i++;
                  }
                  else if(bWaitCloseBracket && ch == ']')
                  {
                     i++;
                     break;
                  }
                  else
                  {
                     strResult += ":*<invalid-syntax>*:"; // fatal;
                     break;
                     break;
                     //__throw(::exception::exception("invalid syntax."));
                  }
               }
               continue;
            }
            else
            {
               i++;
               continue;
            }
         }
         if(iBracket > 0 && ch == ']')
         {
            strResult += ch;
            iBracket--;
         }
         else if(bInSimpleQuote)
         {
            if(bInSlash)
            {
               bInSlash = false;
               strResult += ch;
            }
            else
            {
               if(ch == '\\')
               {
                  bInSlash = true;
                  if(chNext != '{'
                        && chNext != '}'
                        && chNext != '$')
                  {
                     strResult += ch;
                  }
               }
               else if(ch == '\'')
               {
                  bInSimpleQuote = false;
                  //strResult += "\")";
                  strResult += "\"";
               }
               else
               {
                  bInSlash = false;
                  strResult += ch;
               }
            }
         }
         else if(iArroba >= 0)
         {
            if(bInSlash)
            {
               bInSlash = false;
               strResult += ch;
            }
            else
            {
               if(ch == '\\')
               {
                  bInSlash = true;
                  if(chNext != '{'
                        && chNext != '}'
                        && chNext != '$')
                  {
                     strResult += ch;
                  }
               }
               else if(ch == '@')
               {
                  add_var_id(strResult, iArroba, straId);
               }
               else
               {
                  bInSlash = false;
                  strResult += ch;
               }
            }
         }
         else if(bInVar)
         {
            if(ansi_char_is_digit(ch) || ansi_char_is_alphabetic(ch) || ch == '_')
            {
               if(bLow)
               {
                  strResult += (char) tolower(ch);
               }
               else
               {
                  strResult += ch;
               }
            }
            else
            {
               bInVar = false;
               bLow = false;
               if(bInDoubleQuote)
               {
                  if(ch == '$')
                  {
                     bInVar = true;
                     add_var_id(strResult, iVar, straId);
                     strResult += ") + gstr(";
                     iVar = strResult.length();
                     bLow = true;
                     i++;
                     continue;
                  }
                  else
                  {
                     //strResult += "\") + unitext(\"";
                     add_var_id(strResult, iVar, straId);
                     strResult += ") + \"";
                     if(ch == '\"')
                     {
                        bInDoubleQuote = false;
                        //strResult += "\")";
                        strResult += "\"";
                        i++;
                        continue;
                     }
                     else if(ch == '\\')
                     {
                        bInSlash = true;
                     }
                  }
               }
               else
               {
                  while(ansi_char_is_space(str[i]) && i < iLen)
                  {
                     i++;
                  }
                  ch = str[i];
                  if(ch == '[' && chNext != ']')
                  {
                     iBracket++;
                     add_var_id(strResult, iVar, straId);
                     strResult += ").propset()";
                  }
                  else if(ch == '-' && chNext == '>')
                  {
                     i+=2;
                     while(ansi_char_is_space(str[i]) && i < iLen)
                     {
                        i++;
                     }
                     ch = str[i];
                     string strToken;
                     if(ansi_char_is_alphabetic(ch) || ch == '_')
                     {
                        strToken += ch;
                        i++;
                     }
                     else
                     {
                        strResult = "-> error";
                        return strResult;
                     }
                     ch = str[i];
                     while(ansi_char_is_digit(ch) || ansi_char_is_alphabetic(ch) || ch == '_')
                     {
                        strToken += ch;
                        i++;
                        ch = str[i];
                     }
                     ch = str[i];
                     while(ansi_char_is_space(ch))
                     {
                        i++;
                        ch = str[i];
                     }
                     if(ch == '(')
                     {
                        i++;
                        ch = str[i];
                        iaFunctionParen.add(iOpenParen);
                        iOpenParen++;
                        straFunction.add(strToken);
                        while(ansi_char_is_space(ch))
                        {
                           i++;
                           ch = str[i];
                        }
                        if(ch == ')')
                        {
                           add_var_id(strResult, iVar, straId);
                           strResult += ").cast < " + m_pmanager->m_strNamespace + "::object_base >()->call(\""+ strToken + "\" ";
                        }
                        else
                        {
                           add_var_id(strResult, iVar, straId);
                           strResult += ").cast < " + m_pmanager->m_strNamespace + "::object_base >()->call(\""+ strToken + "\", ";
                           continue;
                        }
                     }
                     else
                     {
                        add_var_id(strResult, iVar, straId);
                        strResult += ").cast < " + m_pmanager->m_strNamespace + "::object_base >()->m_propertyset[\""+ strToken + "\"]";
                     }
                  }
                  else
                  {
                     add_var_id(strResult, iVar, straId);
                     strResult += ")";
                  }
               }
               if(ch == ';')
                  goto ch_comma;
               else
                  goto ch_else;
               //strResult += ch;
            }
         }
         else if(bInDoubleQuote)
         {
            if(bInSlash)
            {
               bInSlash = false;
               strResult += ch;
            }
            else
            {
               if(ch == '$' && (ansi_char_is_alphabetic(chNext) || chNext == '_'))
               {
                  bInVar = true;
                  //strResult += "\") + glowstr(\"";
                  strResult += "\" + gstr(";
                  iVar = strResult.length();
                  bLow = true;
               }
               else if(ch == '{')
               {
                  bInBrace = true;
                  bInDoubleQuote = false;
                  //strResult += "\") + ";
                  strResult += "\" + ";
               }
               else if(ch == '\\')
               {
                  bInSlash = true;
                  if(chNext != '{'
                        && chNext != '}'
                        && chNext != '$')
                  {
                     strResult += ch;
                  }
               }
               else if(ch == '\"')
               {
                  bInDoubleQuote = false;
                  //strResult += "\")";
                  strResult += "\"";
               }
               else
               {
                  bInSlash = false;
                  strResult += ch;
               }
            }
         }
         else if(ch == '\"')
         {
            bInDoubleQuote = true;
            //strResult += "unitext(\"";
            strResult += "\"";
         }
         else if(ch == '\'')
         {
            bInSimpleQuote = true;
            //strResult += "unitext(\""; // overloads should cope with the possibility of conversion between string to character
            strResult += "\""; // overloads should cope with the possibility of conversion between string to character
            iSimpleQuote = strResult.get_length();
         }
         else if(ch == '@')
         {
            iArroba = strResult.get_length();
         }
         else if(ch == '_' && chNext == '_' && is_id(&str[i], str.get_length() - i,  "__ch", 4, iIdLen))
         {
            strResult += "'";
            bInVar = false;
            i += iIdLen;
            while(str[i] != '(' && i < iLen)
               i++;
            i++;
            while(str[i] != ')' && i < iLen)
            {
               strResult += str[i];
               i++;
            }
            strResult += "'";

         }
         else if(ch == '$' && (ansi_char_is_alphabetic(chNext) || chNext == '_'))
         {
            if(bInVar)
            {
               if(bInDoubleQuote)
               {
                  add_var_id(strResult, iVar, straId);
                  strResult += ") + gstr(";
                  iVar = strResult.length();
                  bLow = true;
               }
               else
               {
                  add_var_id(strResult, iVar, straId);
                  strResult += ")"; // probably will generate compile error, leave to ca++ compiler
               }
            }
            else
            {
               bInVar = true;
               if(bInDoubleQuote)
               {
                  //strResult += "\") + glowstr(\"";
                  strResult += "\" + gstr(";
                  iVar = strResult.length();
                  bLow = true;
               }
               else
               {
                  if(is_id(&str[i + 1], str.get_length() - i - 1, "_GET", 4,  iIdLen))
                  {
                     strResult += "geta()[";
                     bInVar = false;
                     bServer = true;
                     i += iIdLen + 1;
                  }
                  else if(is_id(&str[i + 1], str.get_length() - i - 1, "_POST", 5,  iIdLen))
                  {
                     strResult += "posta()[";
                     bInVar = false;
                     bServer = true;
                     i += iIdLen + 1;
                  }
                  else if(is_id(&str[i + 1], str.get_length() - i - 1, "_REQUEST", 8, iIdLen))
                  {
                     strResult += "requesta()[";
                     bInVar = false;
                     bServer = true;
                     i += iIdLen + 1;
                  }
                  else if(is_id(&str[i + 1], str.get_length() - i - 1, "_SERVER", 7, iIdLen))
                  {
                     strResult += "inattra()[";
                     bInVar = false;
                     bServer = true;
                     i += iIdLen + 1;
                  }
                  else if(is_id(&str[i + 1], str.get_length() - i - 1, "_COOKIE", 7, iIdLen))
                  {
                     strResult += "cookies()[";
                     bInVar = false;
                     bServer = true;
                     i += iIdLen + 1;
                  }
                  else
                  {
                     strResult += "gprop(";
                     iVar = strResult.length();
                     bLow = true;
                  }
               }
            }
         }
         else if(ch == ';')
         {
ch_comma:
            if(bInRet)
            {
               bInRet = false;
               strResult += ch;
               strResult += "\r\nreturn;\r\n}\r\n";
            }
            else if(bInSpec1Close)
            {
               bInSpec1Close = false;
               strResult += ")";
               strResult += ch;
            }
            else if(bInSpec2Close)
            {
               bInSpec2Close = false;
               strResult += ")";
               strResult += ch;
            }
            else
            {
               strResult += ch;
            }
            bInitial = true;
         }
         else if(ch == '(')
         {
            strResult += ch;
            iOpenParen++;
         }
         else if(ch == ')')
         {
            iOpenParen--;
            //if(iaFunctionParen.pop_match('');
            strResult += ch;
         }
         else if(ch == '#')
         {
            if(bNewLine)
            {
               strResult += ch;
               i++;
               while(i < iLen)
               {
                  ch = str[i];
                  strResult += ch;
                  if(ch == '\r' || ch == '\n')
                     break;
                  i++;

               }

            }
         }
         else
         {
ch_else:
            if(bScript &&str[i-1] != '_' && is_id(&str[i], str.get_length() - i,  "return", 6,  iIdLen) && next_nonspace(str.Mid(i + iIdLen))[0] != ';')
            {
               bInRet = true;
               strResult += "\r\n{\r\nm_varRet = ";
               i += iIdLen - 1;
            }
            else if(is_id(&str[i], str.get_length() - i,  "include", 7, iIdLen))
            {
               bInSpec1 = true;
               strSpec1 = "include";
               i += iIdLen - 1;
            }
            else if(is_id(&str[i], str.get_length() - i,   "print", 5,  iIdLen))
            {
               bInSpec1 = true;
               strSpec1 = "print";
               i += iIdLen - 1;
            }
            else if(is_id(&str[i], str.get_length() - i,  "echo", 4, iIdLen))
            {
               bInSpec1 = true;
               strSpec1 = "echo";
               i += iIdLen - 1;
            }
            else if(str.Mid(i, 2) == "[]")
            {
               bInSpec2 = true;
               i += 2 - 1;
            }
            else if(bInBrace && ch == '}')
            {
               bInDoubleQuote = true;
               bInBrace = false;
               //strResult += " + unitext(\"";
               strResult += " + \"";
            }
            else
            {
               if(ch == '\r' || ch == '\n')
               {
                  bNewLine = true;

               }
               else if(isspace((int) (unsigned char) ch))
               {
               }
               else
               {
                  bNewLine = false;
               }
               if(bLow)
               {
                  strResult += (char) tolower(ch);
               }
               else
               {
                  strResult += ch;
               }
            }
         }
         i++;
      }
      return strResult;

   }


   bool script_compiler::is_id(const char * psz, strsize iLen, const char * pszId, strsize iIdLen, strsize & iIdLenRet)
   {
      if(iLen < iIdLen)
         return false;
      if(iIdLen == iLen)
      {
         if(!strcmp(psz, pszId))
         {
            iIdLenRet = iIdLen;
            return true;
         }
      }
      if(::str::begins(psz, pszId)
            && !isdigit(psz[iIdLen]) && !isalpha(psz[iIdLen]) && psz[iIdLen] != '_')
      {
         iIdLenRet = iIdLen;
         return true;
      }
      return false;
   }

   const char * script_compiler::next_nonspace(const char * psz)
   {
      while(*psz != '\0' && isspace(*psz))
      {
         psz++;
      }
      return psz;
   }


   void script_compiler::run_persistent()
   {

      string strPath = m_pmanager->m_strNetseedDsCa2Path/ "core/persistent";

      ::file::listing stra;

      auto papplication = get_application();

      auto pcontext = m_pcontext;

      pcontext->m_papexcontext->dir().rls(stra, strPath);

      string strCat;
      strCat = m_pmanager->m_strNetseedDsCa2Path/ "core/netnode_persistent_ui_str.ds";
      string strBody;
      strBody = "<?\r\n";
      strBody += "// ATTENTION!\r\n";
      strBody += "// Do not edit this file\r\n";
      strBody += "// This file is automatically generated as the\r\n";
      strBody += "// concatenation of all .ds files in thisr\r\n";
      strBody += "// folder and subfolders!\r\n";
      strBody += "\r\n";
      strBody += "?>\r\n\r\n\r\n";
      for(i32 i = 0; i < stra.get_size(); i++)
      {
         string str = stra[i];
         if(::str::begins_ci(str, m_pmanager->m_strNetseedDsCa2Path/ "core/persistent")
               && ::str::ends_ci(str, ".ds"))
         {
            strBody += m_pcontext->m_papexcontext->file().as_string(str);
         }
      }

      m_pcontext->m_papexcontext->file().put_contents(strCat, strBody);

      string strInclude = strCat;
      
      ::str::begins_eat_ci(strInclude, m_pmanager->m_strNetseedDsCa2Path);
      
      ::str::ends_eat_ci(strInclude, ".ds");
      
      __pointer(script_instance) pinstance = m_pmanager->get(strInclude);

      if(pinstance)
      {

         auto pmain = __create < script_main >();

         pmain->m_pmanager2 = m_pmanager;

         pmain->init1();

         pinstance->initialize(pmain);

         pinstance->init1();
         
         string strError;
         
         //pinstance->initialize_dynamic_source_script_interface(pinstance, nullptr, nullptr, m_pmanager);
         
         auto pdsscript = pinstance->m_pscript2;

         if(pdsscript)
         {

            try
            {

               pdsscript->m_fileError.seek_to_begin();

               string strScriptError;

               pdsscript->m_fileError.to_string(strScriptError);

               m_pmanager->m_strPersistentError += strScriptError;

            }
            catch(...)
            {

            }

         }

         try
         {
            avoid_parsing_exception avoidparsingexception;
            pinstance->run();
         }
         catch(...)
         {
         }

      }
   }


   bool script_compiler::defer_run_persistent(const char *psz)
   {
      string str(psz);

      if(::str::find_ci("pstr_set", psz) && ::str::ends_ci(psz, ".txt"))
      {

         parse_pstr_set();

         //string strCat;
         //strCat = m_pmanager->m_strNetseedDsCa2Path/ "aura\\netnode_persistent_ui_str.ds";
         //string strInclude = strCat;
         //::str::begins_eat_ci(strInclude, m_pmanager->m_strNetseedDsCa2Path);
         //::str::ends_eat_ci(strInclude, ".ds");
         //script_instance * pinstance = m_pmanager->get(strInclude);
         //if(pinstance != nullptr)
         //{
         //   string strError;
         //   pinstance->initialize(pinstance, nullptr, nullptr, m_pmanager);
         //   ::dynamic_source::ds_script * pdsscript = dynamic_cast < ds_script * > (pinstance->m_pscript);
         //   if(pdsscript != nullptr)
         //   {
         //      try
         //      {
         //         pdsscript->m_memfileError.seek_to_begin();
         //         m_pmanager->m_strPersistentError += pdsscript->m_memfileError.to_string();
         //      }
         //      catch(...)
         //      {
         //      }
         //   }
         //   try
         //   {
         //      avoid_parsing_exception avoidparsingexception;
         //      pinstance->run();
         //   }
         //   catch(...)
         //   {
         //   }
         //   try
         //   {
         //      pinstance->destroy();
         //   }
         //   catch(...)
         //   {
         //   }
         //}
      }
      else if(::str::begins_eat_ci(str,m_pmanager->m_strNetseedDsCa2Path/ "aura\\persistent")
              && ::str::ends_eat_ci(str, ".ds")
              && str.compare_ci("netnode_persistent_ui_str") != 0)
      {
         run_persistent();
         return true;
      }
      return false;
   }


//bool script_compiler::library_DoesMatchVersion()
//{

//   if(m_millisLastLibraryVersionCheck.elapsed() < (5000))
//   {
//      return m_bLastLibraryVersionCheck;
//   }

//   single_lock slLibrary(&m_mutexLibrary, true);

//   for(i32 i = 0; i < m_straLibSourcePath.get_size(); i++)
//   {

//      //FILETIME ftCreation;
//      //FILETIME ftAccess;
//      //FILETIME ftModified;
//      //__memset(&ftCreation, 0, sizeof(FILETIME));
//      //__memset(&ftAccess, 0, sizeof(FILETIME));
//      //__memset(&ftModified, 0, sizeof(FILETIME));
//      //HANDLE h = ::CreateFile(m_straLibSourcePath[i], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
//      //GetFileTime(h, &ftCreation, &ftAccess, &ftModified);
//      //::CloseHandle(h);

//      struct stat st;

//      stat(m_straLibSourcePath[i], &st);

//      if(__memcmp(&st.st_ctime, &m_ftaLibCreation[i], sizeof(__time_t)) != 0
//         || __memcmp(&m_ftaLibModified[i], &st.st_mtime, sizeof(__time_t)) != 0)
//      {
//         m_bLastLibraryVersionCheck = false;
//         m_millisLastLibraryVersionCheck= ::millis::now();
//         return false;

//      }

//   }

//   m_bLastLibraryVersionCheck    = true;
//   m_millisLastLibraryVersionCheck  = ::millis::now();

//   return true;

//}
   void library::load_library()
   {

      single_lock slLibrary(&m_mutex, true);

      m_plibraryLib.create(this);

      if(!m_plibraryLib->open(m_strLibraryPath))
         return;

      m_ftaLibCreation.allocate(m_straLibSourcePath.get_size());
      m_ftaLibAccess.allocate(m_straLibSourcePath.get_size());
      m_ftaLibModified.allocate(m_straLibSourcePath.get_size());

      for(i32 i = 0; i < m_straLibSourcePath.get_size(); i++)
      {

         struct stat st;

         stat(m_straLibSourcePath[i], &st);

         m_ftaLibCreation[i]  = st.st_ctime;
         m_ftaLibAccess[i]    = st.st_atime;
         m_ftaLibModified[i]  = st.st_mtime;

         //HANDLE h = ::CreateFile(m_straLibSourcePath[i], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
         //__memset(&m_ftaLibCreation[i], 0, sizeof(FILETIME));
         //__memset(&m_ftaLibAccess[i], 0, sizeof(FILETIME));
         //__memset(&m_ftaLibModified[i], 0, sizeof(FILETIME));
         //GetFileTime(h , &m_ftaLibCreation[i], &m_ftaLibAccess[i], &m_ftaLibModified[i]);
         //::CloseHandle(h);

      }

   }


   library::library(::object * pobject)
   {

      initialize(pobject);

   }


   library::~library()
   {

   }


   void library::unload_library()
   {
      single_lock slLibrary(&m_mutex, true);
      m_plibraryLib->close();
   }

   string script_compiler::get_ds_print(const char *psz)
   {
      string strSource(psz);
      string strDest;
      while(strSource.get_length() > 0)
      {
         strsize iLen = minimum(4 * 1024, strSource.get_length());
         if(strSource.get_length() > iLen)
         {
            if(strSource[iLen] == '\n')
               iLen++;
         }
         string str = strSource.Left(iLen);
         //strDest += "   ds_print(unitext(\"";
         strDest += "\r\n   ds_print(\"";
         strDest += escape(str);
         //strDest += "\"));\r\n";
         strDest += "\");\r\n";
         strSource = strSource.Mid(iLen);
      }
      return strDest;
   }


   void script_compiler::parse_pstr_set()
   {

      ::file::listing straFile;

      auto papplication = get_application();

      auto pcontext = m_pcontext;

      pcontext->m_papexcontext->dir().rls(straFile, m_pmanager->m_strNetnodePath / "net/aura/pstr_set");

      for(int i = 0; i < straFile.get_count(); i++)
      {
         string strFile = straFile[i];
         if(::str::find_ci(".svn",strFile) >= 0 || !::str::ends_ci(strFile,".txt"))
            continue;
         strFile = m_pcontext->m_papexcontext->file().as_string(strFile);
         string_array straLine;
         straLine.explode("\r\n",strFile);
         string strExtra;
         for(int j = 0; j < straLine.get_count(); j++)
         {
            string strLine = straLine[j];
            const char * psz = strLine;
            try
            {
               ::str::consume_spaces(psz,0);
               string strId = ::str::consume_c_quoted_value(psz);
               ::str::consume_spaces(psz,1);
               string strLocale = ::str::consume_c_quoted_value(psz);
               ::str::consume_spaces(psz,1);
               string strSchema = ::str::consume_c_quoted_value(psz);
               ::str::consume_spaces(psz,1);
               string strValue = ::str::consume_c_quoted_value(psz);
               strExtra = "";
               try
               {
                  ::str::consume_spaces(psz,1);
                  strExtra = ::str::consume_c_quoted_value(psz);
               }
               catch(...)
               {
               }
               if(strExtra.has_char())
               {
                  pstr_set(strId + "." + strExtra,strLocale,strSchema,strValue);
               }
               else
               {
                  pstr_set(strId,strLocale,strSchema,strValue);
               }

            }
            catch (const ::parsing_exception & )
            {

               output_debug_string("script_compiler::parse_pstr_set");

            }
            catch (const ::exception::exception & )
            {

               output_debug_string("script_compiler::parse_pstr_set");

            }
            catch(...)
            {

            }

         }

      }

   }


   void script_compiler::pstr_set(id pszTopic,id idLocale,id idSchema,const char * psz)
   {

      synchronous_lock synchronouslock(m_pmanager->mutex());

      auto psystem = m_psystem->m_paurasystem;

      psystem->texttable()->set(pszTopic,idLocale,idSchema,psz);

   }


} // namespace dynamic_source





