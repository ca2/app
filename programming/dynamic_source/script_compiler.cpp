#include "framework.h"
#include "script_compiler.h"
#include "script_manager.h"
#include "ds_script.h"
#include "script_cache.h"
#include "library.h"
#include "script_main.h"
#include "script_instance.h"
////#include "acme/exception/exception.h"
#include "acme/exception/parsing.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/filesystem/file/memory_file.h"
//#include "acme/filesystem/file/text_stream.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/operating_system/process.h"
#include "acme/platform/node.h"
#include "acme/prototype/prototype/url.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/string/str.h"
#include "acme/prototype/string/utf8_character.h"
#include "acme/prototype/text/context.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/crypto/rsa.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/watcher/action.h"
#include "acme/filesystem/watcher/watcher.h"
#include "apex/networking/http/context.h"
#include "aura/platform/application.h"
#include "axis/platform/system.h"


#include "acme/_operating_system.h"
#include <sys/stat.h>

#undef ERROR
#define log_error(...) TRACE_LOG_ERROR(__VA_ARGS__)



#if defined(LINUX)
#include <ctype.h>
#endif

//unsigned int RunSilent(const ::scoped_string & scopedstrFunct, const ::scoped_string & scopedstrstrParams);



namespace dynamic_source
{

   string escape(const ::scoped_string & scopedstr);

   void add_var_id(string& strResult, character_count& iArroba, string_array_base& straId, bool bMakeKeyLower = true);


   script_compiler::script_compiler()
   {

   }


   script_compiler::~script_compiler()
   {

   }


   void script_compiler::initialize_dynamic_source_script_compiler(script_manager* pscriptmanager)
   {

      //auto estatus = 

      initialize_programming_compiler(pscriptmanager, pscriptmanager->m_pathNetnodePath);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pmanager = pscriptmanager;

      //return estatus;

   }


   void script_compiler::init1()
   {

      //node()->integration_factory();

      //øconstruct(m_pintegrationcontext);

      //m_pintegrationcontext->m_strPlatform = "x64";

      prepare_compile_and_link_environment();

      folder_watch();

      run_persistent();

      parse_pstr_set();

      //return ::success;

   }


   void script_compiler::destroy()
   {

      for (auto& plibrary : m_mapLib.payloads())
      {

         plibrary.defer_destroy();

      }

      m_mapLib.clear();

      ::programming::compiler::destroy();

   }


   void script_compiler::prepare_compile_and_link_environment()
   {

      auto pdirectorysystem = directory_system();

      directory()->create(pdirectorysystem->userconfig() / "netnode_desktop/symbols");


      ::programming::compiler::prepare_compile_and_link_environment();

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
      //      ::pointer<::aura::application>papp = get_app();
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //      try
      //      {
      //
      //         if (m_strVs == "2022")
      //         {
      //
      //            m_strContext = "C:/Program Files/Microsoft Visual Studio/2022/Thumbnail/VC/Auxiliary/Build/vcvarsall.bat";
      //
      //            m_strVCVersion = papp->get_visual_studio_build();
      //
      //         }
      //         else if (m_strVs == "2019")
      //         {
      //
      //            m_strContext = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvarsall.bat";
      //
      //            m_strVCVersion = papp->get_visual_studio_build();
      //
      //         }
      //         else if (m_strVs == "2017")
      //         {
      //
      //            m_strContext = "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvarsall.bat";
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
      //            m_strContext = path / "VC/Auxiliary/Build/vcvarsall.bat";
      //
      //            m_strVCVersion = papp->get_visual_studio_build();
      //
      //         }
      //         else if (m_strVs == "2015")
      //         {
      //
      //            m_strContext = strVars.up(2);
      //
      //            m_strContext = m_strContext / "vc\\vcvarsall.bat";
      //
      //         }
      //
      //      }
      //      catch (const ::e_status & estatus)
      //      {
      //
      //         informationf("failed to setup visual studio environment " + as_string((long long)estatus.m_estatus));
      //
      //      }
      //
      //#endif

      m_pathTime = m_pintegrationcontext->m_pathBuildFolder / "time-" OPERATING_SYSTEM_NAME;

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
//      m_strPlat1     = "64";
//      m_strPlatform = "x86";
//      m_strStagePlatform = "x86";
//      m_strLibPlatform = "x86/";
//
//#else
//
//      m_strPlat1     = "64";
//      m_strPlat2 = "x86_amd64";
//      //m_strPlat2 = "amd64";
//      m_strPlatform = "x64";
//      m_strStagePlatform = "x64";
//      m_strLibPlatform = "x64/";
//
//#endif
//#else
//
//      m_strPlat1     = "32";
//      m_strPlat2 = " x86";
//      m_strPlatform = "Win32";
//      m_strStagePlatform = "x86";
//      m_strLibPlatform = "x86/";
//
//#endif
//
//#if defined(LINUX) || defined(MACOS)
//
//      prepare1(m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bash",
//               m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bash");
//      prepare1(m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bash",
//               m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bash");
//      prepare1(m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bash",
//               m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bash");
//
//#else
//
//      prepare1(m_strPlat1,m_strPlat1);
//
//#endif

      directory()->create(m_pintegrationcontext->m_pathBuildFolder / m_strDynamicSourceStage / "front");

      string str;

      string strItem;

      strItem = m_pintegrationcontext->m_pathBuildFolder / m_strDynamicSourceStage / m_pintegrationcontext->m_strStagePlatform;

      str = str + strItem + ";";

      strItem = m_pintegrationcontext->m_pathBuildFolder / m_strDynamicSourceStage / m_pintegrationcontext->m_strStagePlatform / "dynamic_source\\library";

      str = str + strItem + ";";

#ifdef WINDOWS_DESKTOP

      unsigned int dwSize = GetEnvironmentVariableW(L"PATH", nullptr, 0);
      LPWSTR lpsz = øraw_new wchar_t[dwSize + 1];
      dwSize = GetEnvironmentVariableW(L"PATH", lpsz, dwSize + 1);
      str += lpsz;
      delete lpsz;

#endif

   }


   void script_compiler::compile(ds_script* pscript)
   {

      //synchronous_lock synchronouslock(pscript->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      _synchronous_lock slCompiler(&m_pmanager->m_semCompiler);

      information("Compiling script {}", pscript->m_pfilesystemcacheitem->path());

      auto& ostreamError = pscript->m_textstreamError;

      ::file::path strName(pscript->m_pfilesystemcacheitem->path());

      if (strName.case_insensitive_ends("\\auth3.ds"))
      {

         informationf("compile auth3.ds");

      }

      pscript->on_start_build();

      //#ifdef WINDOWS
      //
      //      strName.find_replace("/","\\");
      //
      //#endif

            //strName.replace("/", "\\");
            //string strFolder;
            //strFolder = m_pintegrationcontext->m_pathBuildFolder ;
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

      ::file::path pathClog;
      ::file::path pathLlog;
      ::file::path pathObj;

      /*string strScript(strName);
      strScript.replace("\\", ",");
      strScript.replace("/", ",");
      strScript = "ca2" + m_pmanager->m_strNamespace + "_script." + strScript;*/

      ::file::path strScript;

      strScript = strName.title();

      ::file::path strTransformName = strName;

      if (file()->exists(strName))
      {

         pscript->m_strSourcePath = strName;

         strTransformName.find_replace(":", "");

      }
      else
      {

         pscript->m_strSourcePath.formatf(m_pmanager->m_pathNetnodePath / "net/%s", strName.c_str());

      }

      pscript->m_strSourceDir = pscript->m_strSourcePath.folder();

      auto strSourcePath = pscript->m_strSourcePath;

      if (!file()->exists(strSourcePath))
      {
         ostreamError << "<pre>";
         str.formatf("Source File : \"%s\" does not exist", pscript->m_strSourcePath.c_str());
         ostreamError << str;
         ostreamError << "</pre>";
         return;
      }

      string strRndTitle;

      string strMillis;

      strMillis = ::as_string(::long_long_millisecond() % 1000);

      auto pszBufferMillis = strMillis.get_buffer(3);

      ::ansi_zero_pad(pszBufferMillis, 3);

      strMillis.release_buffer();

      auto psystem = system();

      auto pdatetime = psystem->datetime();

      strRndTitle = "_" + pdatetime->format("%Y-%m-%d_%H-%M-%S") + "_" + strMillis;

      string strTime = m_pathTime;

      pscript->m_strCppPath.formatf(m_pathTime / "dynamic_source/%s.cpp", strTransformName.c_str());

      //auto pathCa2Root = m_pintegrationcontext->m_pathBuildFolder ;

      auto pathProjectDir = m_pintegrationcontext->m_pathBuildFolder;

      //string strCompileLogUnique;

      ::earth::time timeNow = ::earth::time::now();

      string strCompileLogUnique = datetime()->format(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE, timeNow);

      if (!::character_isdigit(strCompileLogUnique[0]))
      {

         string strCompileLogUnique2 = datetime()->format(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE, timeNow);

         informationf("Ops");

      }

      pathClog = string().formatf(m_pathTime / "dynamic_source/%s-compile-log-%s.txt", strTransformName.c_str(), strCompileLogUnique.c_str());
      pathLlog = string().formatf(m_pathTime / "dynamic_source/%s-link-log.txt", strTransformName.c_str());

      string strPathCompiler;
      strPathCompiler.formatf(m_pathTime / "dynamic_source/%s-compiler.txt", strTransformName.c_str());
      ::file::path pathCompiler(strPathCompiler);

      string strPathLinker;
      strPathLinker.formatf(m_pathTime / "dynamic_source/%s-linker.txt", strTransformName.c_str());
      ::file::path pathLinker(strPathLinker);

      //#ifdef _DEBUG
#ifdef LINUX
      //strB = m_pintegrationcontext->m_pathBuildFolder  / m_strDynamicSourceStage / "front\\dynamic_source\\BuildBat" / strTransformName.name() / strTransformName + ".bat";
      strO = ::file::path(m_pathTime) / "intermediate" / m_pintegrationcontext->m_strPlatform / m_pmanager->m_strNamespace + "_dynamic_source_script" / strTransformName / strTransformName.name() + ".o";
#else

      //strB = m_strDynamicSourceStageFolder / "front\\dynamic_source\\BuildBat" / strTransformName.name() / strTransformName + ".bat";

      strP = m_strDynamicSourceStageFolder / m_pintegrationcontext->m_strPlatform / "dynamic_source" / strTransformName.sibling(strScript.name()) + ".pdb";

      strL = m_strDynamicSourceStageFolder / m_pintegrationcontext->m_strPlatform / "dynamic_source" / strTransformName.sibling(strScript.name()) + ".lib";

      strE = m_strDynamicSourceStageFolder / m_pintegrationcontext->m_strPlatform / "dynamic_source" / strTransformName.sibling(strScript.name()) + ".exp";

      ::file::path strDynamicSourceScriptFolder = m_pathTime / "intermediate" / m_pintegrationcontext->m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + "_dynamic_source_script";

      //strDVI = strDynamicSourceScriptFolder / strTransformName / m_strSdk1 + ".idb";

      //::file::path pathSourceDVP = strDynamicSourceScriptFolder / strTransformName / m_strSdk1 + ".pdb";

      ::file::path pathSourceNetnodeDSS = m_pintegrationcontext->m_pathBuildFolder / "time-" OPERATING_SYSTEM_NAME "/intermediate/x64" / m_strDynamicSourceConfiguration / "app-core/netnode_dynamic_source_script";

      ::string strSDK1 = m_pintegrationcontext->payload("sdk1").as_string();

      ::file::path pathSourceDVP = pathSourceNetnodeDSS / (strSDK1 + ".pdb");

      //::file::path pathCompiler;

      {

         ::file::path pathHelper1 = strTransformName.sibling(strScript.name());

         string strHelper1 = pathHelper1 + "-" + m_pintegrationcontext->payload("sdk1").as_string() + ".pdb";

         auto pathDVP0 = m_strDynamicSourceStageFolder / m_pintegrationcontext->m_strPlatform / "dynamic_source" / pathHelper1.folder() / strHelper1;

         string strCompiler = pathHelper1 + "-compiler.txt";

         string strDVP1 = pathDVP0;

         solve_relative(strDVP1);

         strDVP = strDVP1;

         ::file::path pathDVP = strDVP;

         ::file::path pathDVP_Folder = pathDVP.folder();

         directory_system()->create(pathDVP_Folder);

         file()->copy(pathDVP, pathSourceDVP);

      }

      string strDVP_B = strDVP;

      strDVP_B.find_replace("\\", "/");

      //strDPC = strDynamicSourceScriptFolder / strTransformName / m_pmanager->m_strNamespace + "_dynamic_source_script.pch";
      //strDO1 = strDynamicSourceScriptFolder / strTransformName / "framework.obj";
      //strDO2 = strDynamicSourceScriptFolder / strTransformName / m_pmanager->m_strNamespace + "_dynamic_source_script.obj";
      //strSVI = strDynamicSourceScriptFolder / m_strSdk1 + ".idb";
      //strSVP = strDynamicSourceScriptFolder / m_strSdk1 + ".pdb";
      //strSPC = strDynamicSourceScriptFolder / m_pmanager->m_strNamespace + "_dynamic_source_script.pch";
      //strSO1 = strDynamicSourceScriptFolder / "framework.obj";
      //strSO2 = strDynamicSourceScriptFolder / m_pmanager->m_strNamespace + "_dynamic_source_script.obj";

      pathObj = strDynamicSourceScriptFolder / strTransformName / strTransformName.name() + ".obj";

      strO = strDynamicSourceScriptFolder / strTransformName.name() / strTransformName + ".bat";

#endif

      pscript->m_strScriptPath = m_pmanager->netnode_file_path(strName, strRndTitle);

      try
      {

         if (file()->exists(strO))
         {

            file()->erase(strO);

         }

      }
      catch (...)
      {

      }

      try
      {

         if (file()->exists(pathObj))
         {

            file()->erase(pathObj);

         }

      }
      catch (...)
      {

      }

#ifndef LINUX

      try
      {

         if (file()->exists(strP))
         {

            file()->erase(strP);

         }

      }
      catch (...)
      {

      }

      try
      {

         if (file()->exists(strL))
         {

            file()->erase(strL);

         }

      }
      catch (...)
      {

      }

      try
      {
      
         if (file()->exists(strE))
         {

            file()->erase(strE);

         }

      }
      catch (...)
      {

      }

      //try
      //{
      //   if(file()->exists(strDPC))
      //   {
      //      file()->del(strDPC);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(file()->exists(strDVP))
      //   {
      //      file()->del(strDVP);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(file()->exists(strDVI))
      //   {
      //      file()->del(strDVI);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(file()->exists(strDO1))
      //   {
      //      file()->del(strDO1);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(file()->exists(strDO2))
      //   {
      //      file()->del(strDO2);
      //   }
      //}
      //catch(...)
      //{
      //}
#endif

      try
      {

         if (file()->exists(pathClog))
         {

            file()->erase(pathClog);

         }

      }
      catch (...)
      {

      }

      try
      {

         if (file()->exists(pathLlog))
         {

            file()->erase(pathLlog);

         }

      }
      catch (...)
      {

      }

      //::DeleteFile(pscript->m_strBuildBat);

      try
      {

         if (file()->exists(pscript->m_strScriptPath + ".old"))
         {

            file()->erase(pscript->m_strScriptPath + ".old");

         }

      }
      catch (const ::exception&)
      {

         //::exception_pointer esp(pexception);

         //informationf("%s", esp->get_message().c_str());

      }

      try
      {

         if (file()->exists(pscript->m_strScriptPath))
         {

            file()->transfer(pscript->m_strScriptPath + ".old", pscript->m_strScriptPath);

         }

      }
      catch (const ::exception&)
      {

         //::exception_pointer esp(pexception);

         //informationf("%s", esp->get_message().c_str());

      }

      try
      {

         if (file()->exists(pscript->m_strScriptPath + ".old"))
         {

            file()->erase(pscript->m_strScriptPath + ".old");

         }

      }
      catch (const ::exception&)
      {

         //::exception_pointer esp(pexception);

         //informationf("%s", esp->get_message().c_str());

      }


      directory()->create(pscript->m_strScriptPath.folder());
      directory()->create(strL.folder());
      directory()->create(m_pathTime / "intermediate" / m_pintegrationcontext->m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + ::file::path("_dynamic_source_script") / strTransformName);

      cppize(pscript);

      //auto pathCa2Root = m_pintegrationcontext->m_pathBuildFolder ;

      string strV(pathProjectDir);
      strV.find_replace("\\", "/");
      if (!string_ends(strV, "/") && !string_ends(strV, "\\"))
         strV += "/";

      string strN = m_pmanager->m_pathNetnodePath;
      strN.find_replace("\\", "/");
      if (!string_ends(strN, "/") && !string_ends(strN, "\\"))
         strN += "/";

      string strObjFile;

      string strItemName = ::str::find_replace("\\", "/", string(strTransformName));

      string strItemTitle = strTransformName.name();

      ::file::path pathObjFile;


#ifdef WINDOWS

      {

         pathObjFile = strV;
         pathObjFile /= "time-" OPERATING_SYSTEM_NAME"/intermediate";
         pathObjFile /= m_pintegrationcontext->m_strPlatform;
         pathObjFile /= m_strDynamicSourceConfiguration;
         pathObjFile /= "app-core/netnode_dynamic_source_script";
         pathObjFile /= strItemName;
         pathObjFile /= (strItemTitle + ".obj");

         strObjFile = pathObjFile;

      }

      strObjFile.find_replace("\\", "/");

#endif

      string strBuildCmd;

#if defined(LINUX) || defined(MACOS) || defined(FREEBSD) || defined(OPENBSD)
      strBuildCmd = m_pintegrationcontext->m_pathBuildFolder / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_cl_" + m_pintegrationcontext->m_strPlatform + ".bash";
#else
      strBuildCmd = m_pintegrationcontext->m_pathBuildFolder / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "\\_stage\\dynamic_source" / m_pintegrationcontext->payload("vstools").as_string() / m_strDynamicSourceConfiguration + "_c_" + m_pintegrationcontext->m_strPlatform + ".bat";
#endif

      str = file()->as_string(strBuildCmd);
      str.find_replace("%ITEM_NAME%", strItemName);
      str.find_replace("%ITEM_TITLE%", strItemTitle);
      str.find_replace("%ITEM_DIR%", ::str::replace_with("\\", "/", string(strTransformName.folder())) + "/");
      str.find_replace("%LIBS_LIBS%", m_strLibsLibs);


      str.find_replace("%CA2_ROOT%", strV);
      str.find_replace("%NETNODE_ROOT%", strN);
      str.find_replace("%CONFIGURATION_NAME%", m_strDynamicSourceConfiguration);
      str.find_replace("%CONFIGURATION%", m_strDynamicSourceConfiguration);
#ifdef LINUX
      str.find_replace("%DVP%", strDVP);
#else
      str.find_replace("%DVP%", strDVP_B);
#endif
      str.find_replace("%OBJFILE%", strObjFile);

      string strTargetPath = pscript->m_strScriptPath;
#ifdef LINUX
      strTargetPath.case_insensitive_ends_eat(".so");
#else
      strTargetPath.case_insensitive_ends_eat(".dll");
#endif
      str.find_replace("%TARGET_PATH%", strTargetPath);
      //strBuildCmd = pscript->m_strBuildBat;
      //file()->put_text_utf8(strBuildCmd, str);

      ///file()->put_contents(strBuildCmd,str);

      m_pintegrationcontext->prepare_compilation_script(str);

      bool bTimeout = false;

      ::operating_system::process_pointer process(e_create, this);

      ::parallelization::set_priority(::e_priority_highest);

      //process->prop("inherit") = false;

      string strCompiler = str;

      strCompiler.trim();

      file()->put_text_utf8(pathCompiler, strCompiler);

#ifdef WINDOWS
      process->create_child_process(strCompiler, true, m_pintegrationcontext->m_pathBuildFolder / "source/app-core/netnode_dynamic_source_script", ::e_priority_highest);
#else
      process->create_child_process(strCompiler, true, m_pintegrationcontext->m_pathBuildFolder, ::e_priority_highest);
#endif

      //::system(str + " > " + "\"" + strClog + "\"");

      auto tickStart = ::time::now();

      string strLog;

      while (::task_get_run())
      {

         strLog += process->read();

         if (process->has_exited())
            break;

         preempt(100_ms);

         if (tickStart.elapsed() > 890_s) // 14 minutes
         {

            bTimeout = true;

            break;

         }

      }

      strLog += process->read();

      if (bTimeout)
      {

         process->kill();

      }

      if (!bTimeout && strLog.has_character())
      {

#ifdef LINUX

         //sleep(2000_ms);

#endif

         str = strLog;

         str.trim();

         if (str.has_character())
         {

            file()->put_text_utf8(pathClog, strLog);

            ostreamError << "<pre>";

            //ostreamError << "Compiling Command\n";
            //ostreamError << pathCompiler << "\n";
            informationf("Compiling Command File %s", pathCompiler.c_str());
            informationf("Compiling Command %s", strCompiler.c_str());
            ostreamError << "Compiling...\n";
            ostreamError << pscript->m_strCppPath;
            ostreamError << "\n";
            if (bTimeout)
            {
               ostreamError << "error: Timeout during compilation (If there are the compilation or link errors about the file \"" + pscript->m_strCppPath + "\" following this message, they may be out-of-date)";
            }
            str.find_replace("\r\n", "\n");
            ostreamError << str;

         }

         int iObjFileMinimumByteCount = 1024;

         if (process->m_exitstatus.m_iExitCode != 0 || file()->length(pathObjFile) < iObjFileMinimumByteCount)
         {

            informationf("Compilation FAILED: or object file is shorter than %lld bytes...", iObjFileMinimumByteCount);
            informationf("%s", strLog.c_str());

            //string_array_base straLog;
            //straLog.add_lines(strLog);
            //for(auto & strLine : straLog)
            //{
            //   int iColCount = 80;
            //   for (::collection::index i = 0; i < strLine.length(); i += iColCount)
            //   {
            //      if (strLine.length() < i + iColCount + 10)
            //      {
            //         information(strLine.substr(i));
            //         break;
            //      }
            //      else
            //      {
            //         information(strLine.substr(i, iColCount) + "\\...");
            //      }
            //   }

            //}

            pscript->m_strError = ostreamError.m_pfile->full_string();

            return;

         }

         //strBuildCmd;

#if defined(LINUX) || defined(MACOS) || defined(FREEBSD) || defined(OPENBSD)
         strBuildCmd = m_pintegrationcontext->m_pathBuildFolder / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME"\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_cl_" + m_pintegrationcontext->m_strPlatform + ".bash";
#else
         strBuildCmd = m_pintegrationcontext->m_pathBuildFolder / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "\\_stage\\dynamic_source" / m_pintegrationcontext->payload("vstools").as_string() / m_strDynamicSourceConfiguration + "_l_" + m_pintegrationcontext->m_strPlatform + ".bat";
#endif

         str = file()->as_string(strBuildCmd);
         str.find_replace("%ITEM_NAME%", ::str::find_replace("\\", "/", string(strTransformName)));
         str.find_replace("%ITEM_TITLE%", strTransformName.name());
         str.find_replace("%ITEM_DIR%", ::str::find_replace("\\", "/", string(strTransformName.folder())) + "/");
         str.find_replace("%LIBS_LIBS%", m_strLibsLibs);


         str.find_replace("%CA2_ROOT%", strV);
         str.find_replace("%NETNODE_ROOT%", strN);
         str.find_replace("%CONFIGURATION_NAME%", m_strDynamicSourceConfiguration);
         str.find_replace("%CONFIGURATION%", m_strDynamicSourceConfiguration);
#ifdef LINUX
         str.find_replace("%DVP%", strDVP);
#else
         str.find_replace("%DVP%", strDVP_B);
#endif
         str.find_replace("%OBJFILE%", strObjFile);

         m_pintegrationcontext->prepare_linking_script(str);

         string strTargetPath = pscript->m_strScriptPath;
#ifdef LINUX

         strTargetPath.case_insensitive_ends_eat(".so");

#else

         strTargetPath.case_insensitive_ends_eat(".dll");

#endif

         str.find_replace("%TARGET_PATH%", strTargetPath);

         string strHmhLctvWildPdbPath;

         string strSymbolName;

         strSymbolName = ::file::path(strTransformName).title();

         strSymbolName += strRndTitle;

         auto pdirectorysystem = directory_system();

         strHmhLctvWildPdbPath = ::file::path(pdirectorysystem->userconfig() / "netnode_desktop\\symbols") / strSymbolName;

         str.find_replace("%HMH_LCTVWILD_PDB_PATH%", strHmhLctvWildPdbPath);

         //strBuildCmd = pscript->m_strBuildBat;
         //file()->put_text_utf8(strBuildCmd, str);

         //file()->put_contents(strBuildCmd,str);

         //str.find_replace("\\", "/");

         bTimeout = false;

         ::operating_system::process_pointer process(e_create, this);

         ::parallelization::set_priority(::e_priority_highest);

         string strLinker(str);

         strLinker.find_replace("\\", "/");
         strLinker.trim();

         file()->put_text_utf8(pathLinker, strLinker);

         process->create_child_process(strLinker, true, nullptr, ::e_priority_highest);

         auto tickStart = ::time::now();

         string strLog;

         while (::task_get_run())
         {

            strLog += process->read();

            if (process->has_exited())
               break;

            preempt(100_ms);

            if (tickStart.elapsed() > 890_s) // 14 minutes
            {

               bTimeout = true;

               break;

            }

         }

         strLog += process->read();

         if (!bTimeout && strLog.has_character())
         {

#ifdef LINUX

            //sleep(2000_ms);

#endif

            str = strLog;

            str.trim();

            if (str.has_character())
            {

               file()->put_text_utf8(pathLlog, strLog);
               ostreamError << "Linking...\n";
               //ostreamError << "Linker Command File" << "\n";
               //ostreamError << pathLinker << "\n";
               information() << "Linker Command File " << pathLinker.c_str();
               //ostreamError << "Linker Command" << "\n";
               //ostreamError << strLinker << "\n";
               information() << "Linker Command " << strLinker.c_str();
               str.find_replace("\r\n", "\n");
               ostreamError << str;
               ostreamError << "</pre>";


            }

            pscript->m_strError = pscript->m_pfileError->as_string();

            pscript->m_strError.trim();

         }

      }

#ifndef LINUX

      //try
      //{
      //   file()->del(strDVI);
      //}
      //catch(...)
      //{
      //}
      try
      {
         file()->erase(strDVP);
      }
      catch (...)
      {
      }
      //try
      //{
      //   file()->del(strDPC);
      //}
      //catch(...)
      //{
      //}

#endif

   }


   void script_compiler::cppize(ds_script* pscript)
   {

      auto ftDs = get_file_time_set(pscript->m_strSourcePath);

      if (file()->exists(pscript->m_strCppPath))
      {

         if (ftDs == pscript->m_ftDs)
         {

            return; // nothing to do

         }

      }

      directory()->create(pscript->m_strCppPath.folder());

      cppize1(pscript);

      pscript->m_ftDs = ftDs;

   }

   string escape(const ::scoped_string & scopedstr)
   {
      string str(scopedstr);
      str.find_replace("\\", "\\\\");
      str.find_replace("\"", "\\\"");
      str.find_replace("\r\n", "\\r\\n");
      str.find_replace("\r", "\\r\\n");
      str.find_replace("\n", "\\r\\n");
      str.find_replace("\t", "\\t");
      return str;
   }

   void script_compiler::cppize1(ds_script* pscript)
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

      while ((strSource = file()->as_string(pscript->m_strSourcePath)).trimmed().is_empty() && ::task_get_run())
      {

         preempt(100_ms);

         iTry++;

         if (iTry > 256)
         {
            return;
         }

      }
      pscript->m_strClassNamePrefix = pscript->m_strSourcePath;
      pscript->m_strClassNamePrefix.find_replace("/", "_");
      pscript->m_strClassNamePrefix.find_replace("\\", "_");
      pscript->m_strClassNamePrefix.find_replace("-", "_");
      pscript->m_strClassNamePrefix.find_replace(":", "_");
      pscript->m_strClassNamePrefix.find_replace(" ", "_");
      pscript->m_strClassNamePrefix.find_replace("!", "_");
      pscript->m_strClassNamePrefix.find_replace(".", "_");

      pscript->m_strClassName = pscript->m_strClassNamePrefix + "_dynamic_source_script";

      character_count iPosId = -1;
      string_array_base straId;
      string strDest;
      strDest = "";
      strDest += "#include \"netnode_dynamic_source_script_framework.h\"\r\n";
      //strDest += "#include \"11ca2_account.h\"\r\n";
      //for(int i = 0; i < m_straLibIncludePath.get_count(); i++)
      //{
      //   string str;
      //   str = m_straLibIncludePath[i].relative();
      //   str.case_insensitive_ends_eat(".ds");
      //   strDest += "#include \""+str+".h\"\r\n";
      //}
      character_count iStart = 0;
      character_count iPos = 0;
      character_count iLastEnd = 0;
      if (strSource.substr(0, 4) == "<?ss"_ansi)
      {
         iLastEnd = strSource.find_index("?>", iPos);
         if (iLastEnd > 0)
         {
            iLastEnd += 2;
            strDest += cppize2(strSource.substr(iPos + 4, iLastEnd - iPos - 6), false, straId);
            iStart = iLastEnd;
         }
      }
      else if (strSource.substr(0, 7) == "<? //ss")
      {
         iLastEnd = strSource.find_index("?>", iPos);
         if (iLastEnd > 0)
         {
            iLastEnd += 2;
            strDest += cppize2(strSource.substr(iPos + 7, iLastEnd - iPos - 7 - 2), false, straId);
            iStart = iLastEnd;
         }
      }
      string strDs;
      if (strSource.substr(iStart, 4) == "<?ds")
      {
         iStart += 4;
         while (true)
         {
            character_count iMid = strSource.find_index("?>", iStart);
            iLastEnd = strSource.find_index("ds?>", iStart);
            if (iMid > 0 && iMid < iLastEnd)
            {
               strDs += cppize2(strSource.substr(iStart, iMid - iStart), true, straId);
               iStart = iMid + 2;
               iMid = strSource.find_index("<?", iStart);
               if (iMid < iLastEnd)
               {
                  strDs += get_ds_print(strSource.substr(iStart, iMid - iStart));
               }
               iStart = iMid + 2;
               continue;
            }
            if (iLastEnd > 0)
            {
               strDs += cppize2(strSource.substr(iStart, iLastEnd - iStart), true, straId);
               iStart = iLastEnd + 4;
               iLastEnd = iStart;
            }
            break;
         }
      }
      strDest += "\r\n";
      strDest += "\r\n";
      iPosId = strDest.length();
      strDest += "\r\n";
      strDest += "\r\n";
      strDest += "\r\n";
      strDest += "#define _return return";
      strDest += "\r\n";
      strDest += "\r\n";
      strDest += "\r\n";
      strDest += "class " + pscript->m_strClassNamePrefix + "_dynamic_source_script : virtual public ::app_consumer < ::netnode::application, ::" + m_pmanager->m_strNamespace + "::script_instance >\r\n";
      strDest += "{\r\n";
      strDest += "public:\r\n";
      //strDest += "   " + pscript->m_strClassNamePrefix + "_dynamic_source_script(dynamic_source::script * pscript) : ::object(pscript->get_app()), dynamic_source::script_instance(pscript), ::" + pscript->m_strClassNamePrefix + "::script_instance(pscript), ::" + pscript->m_strClassNamePrefix + "::script_impl(pscript) {};  \r\n";
      strDest += "   " + pscript->m_strClassNamePrefix + "_dynamic_source_script() {};\r\n";
      strDest += "   virtual ~" + pscript->m_strClassNamePrefix + "_dynamic_source_script() {};\r\n";
      strDest += "   virtual void     run() { script_run(); };\r\n";
      strDest += "   virtual void script_run();\r\n";
      strDest += "   \r\n\r\n";
      strDest += strDs;
      strDest += "   \r\n\r\n\r\n";
      strDest += "};\r\n";
      strDest += "\r\n";
      strDest += "extern \"C\" __declspec(dllexport) dynamic_source::script_instance * __cdecl create_dynamic_source_script_instance ()\r\n";
      strDest += "{\r\n";
      strDest += "   return øraw_new " + pscript->m_strClassNamePrefix + "_dynamic_source_script ();\r\n";
      strDest += "}\r\n";
      strDest += "\r\n";
      strDest += "void " + pscript->m_strClassNamePrefix + "_dynamic_source_script::script_run()\r\n";
      strDest += "{\r\n";
      strDest += "//Start parsed user script\r\n";
      straId.erase_all();
      while ((iPos = strSource.find_index("<?", iStart)) >= 0)
      {
         if (iPos > iLastEnd)
         {
            strDest += get_ds_print(strSource.substr(iLastEnd, iPos - iLastEnd));
         }
         iLastEnd = strSource.find_index("?>", iPos);
         if (iLastEnd < 0)
            break;
         iLastEnd += 2;
         int iShift = 0;
         if (strSource.substr(iPos, 5).case_insensitive_order("<?php") == 0)
            iShift = 3;
         strDest += cppize2(strSource.substr(iPos + 2 + iShift, iLastEnd - iPos - 4 - iShift), true, straId);
         iStart = iLastEnd;
      }
      strDest += get_ds_print(strSource.substr(iStart));

      strDest += "//End parsed user script\r\n";
      //strDest += "return ::success;\r\n";
      strDest += "}\r\n";

      //string strId;
      //for(int i = 0; i < straId.get_size(); i++)
      //{
      //   strId += "static ::atom lscript_id" + ::as_string(i) + "(\"" + straId[i] + "\");\r\n";
      //}

      //strDest = strDest.left(iPosId) + strId + strDest.substr(iPosId);


      string strCppPath = pscript->m_strCppPath;

      strCppPath.find_replace("\\", "\\\\");

      //      strDest += " \r\n \
      //         extern \"C\" int APIENTRY \r\n \
      //         DllMain(HINSTANCE hInstance,unsigned int dwReason,LPVOID lpReserved) \r\n \
      //      { \r\n \
      //\r\n  \
      // \r\n \r\n \
      //         __UNREFERENCED_PARAMETER(hInstance); \r\n \
      //         __UNREFERENCED_PARAMETER(lpReserved); \r\n \
      // \r\n \
      // \r\n \
      //         if(dwReason == DLL_PROCESS_ATTACH) \r\n \
      //         { \r\n \
      // \r\n \
      // \r\n \
      //             ::information(\"netnode_desktop script initializing : " + strCppPath + "!\\n\"); \r\n \
      // \r\n \
      // \r\n \
      //         } \r\n \
      //         else if(dwReason == DLL_PROCESS_DETACH) \r\n \
      //         { \r\n \
      // \r\n \
      // \r\n \
      //            ::information(\"netnode_desktop script terminating : " + strCppPath + "!\\n\"); \r\n \
      // \r\n \
      // \r\n \
      //         } \r\n \
      // \r\n \
      //         return 1;    \r\n \
      // \r\n \
      //      }\r\n\r\n\r\n\r\n\r\n";

            //file()->put_text_utf8(pscript->m_strCppPath, strDest);
      file()->put_text(pscript->m_strCppPath, strDest);

   }

   void script_compiler::operator()(::file::action* paction)
   {

      synchronous_lock synchronouslock(m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ::file::path path = paction->m_pathFolder / paction->m_pathFile;

      string strTransfer = path;

      // does not transfer
      if (::str::case_insensitive_find("netnode_persistent_ui_str", strTransfer) >= 0)
         return;

      //auto psystem = system();

      if (m_straSync.get_count() > 1)
      {
         for (int i = 1; i < m_straSync.get_count(); i++)
         {

            ::property_set set;

            //auto purl = psystem->url();

            http()->get("http://" + m_straSync[i] + "/synchronization?src=" + m_straSync[0] + "&url=" + ::url::encode(strTransfer) + "&pwd=sym123&authnone=1", set);

         }

      }

      if (string_begins(path, m_pmanager->m_pathNetseedDsCa2Path / "library/include"))
      {

         m_pmanager->m_pcache->set_all_out_of_date();

      }
      else if (string_begins(path, m_pmanager->m_pathNetseedDsCa2Path / "library/source"))
      {

      }
      else if (defer_run_persistent(path))
      {
      }
      else
      {

         m_pmanager->m_pcache->set_out_of_date(path);

      }

   }


   void script_compiler::folder_watch()
   {

      //xxx:folder_watch m_filewatcherid = file_watcher()->add_watch(m_pmanager->m_pathNetseedDsCa2Path, this, true);

   }


   library& script_compiler::lib(const ::scoped_string & scopedstrLibrary)
   {

      single_lock slLibrary(m_pmutexLibrary, true);

      auto p = m_mapLib.find(scopedstrLibrary);

      if (::is_ok(p))
      {
         return *p->element2();
      }

      m_mapLib[scopedstrLibrary] = øallocate library(this);

      library& l = *m_mapLib[scopedstrLibrary];

      auto pathCa2Root = m_pintegrationcontext->m_pathBuildFolder;

      string strV(pathCa2Root);
      strV.find_replace("\\", "/");
      if (!string_ends(strV, "/") && !string_ends(strV, "\\"))
         strV += "/";

      string strN = m_pmanager->m_pathNetnodePath;
      strN.find_replace("\\", "/");
      if (!string_ends(strN, "/") && !string_ends(strN, "\\"))
         strN += "/";


      //unload_library();

      string strLibrary(scopedstrLibrary);

      ::file::path strName = strLibrary;

      m_strLibsLibs = m_pintegrationcontext->m_pathBuildFolder / "time-" OPERATING_SYSTEM_NAME"/library" / m_pintegrationcontext->m_strStagePlatform / "/library/" + strLibrary + ".lib";

      //m_memfileLibError.set_length(0);
      string strFolder;
      strFolder = m_pintegrationcontext->m_pathBuildFolder;

      //auto papp = get_app();

      //l.m_straLibSourcePath.m_pprovider = papp;

      l.m_straLibSourcePath.clear_results();

      //auto pcontext = m_papplication;

      l.m_straLibSourcePath.set_listing(m_pmanager->m_pathNetseedDsCa2Path / "library" / strName, ::e_depth_recursively);

      directory()->enumerate(l.m_straLibSourcePath);

      for (int i = 0; i < l.m_straLibSourcePath.get_size();)
      {
         if (l.m_straLibSourcePath[i].final_extension() != "ds" && l.m_straLibSourcePath[i].final_extension() != "cpp")
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
      for (int i = 0; i < l.m_straLibSourcePath.get_size(); i++)
      {
         string str = l.m_straLibSourcePath[i].relative();
         str.case_insensitive_ends_eat(".ds");
         str.find_replace(":", "");
         l.m_straLibCppPath.add(m_pathTime / strLibRel / str + ".cpp");
      }
      //l.m_straLibIncludePath.m_pprovider = papp;
      l.m_straLibIncludePath.clear_results();
      l.m_straLibIncludePath.set_listing(m_pmanager->m_pathNetseedDsCa2Path / "library" / strName, e_depth_recursively);
      directory()->enumerate(l.m_straLibIncludePath);
      for (int i = 0; i < l.m_straLibIncludePath.get_size();)
      {
         if (l.m_straLibIncludePath[i].final_extension() != "h"
            || ::str::case_insensitive_find(l.m_straLibIncludePath[i], "\\.svn\\") >= 0
            || directory()->is(l.m_straLibIncludePath[i]))
         {
            l.m_straLibIncludePath.erase_at(i);
         }
         else
         {
            i++;
         }
      }
      l.m_straLibHppPath.erase_all();
      for (int i = 0; i < l.m_straLibIncludePath.get_size(); i++)
      {
         string str = l.m_straLibIncludePath[i].relative();
         str.case_insensitive_ends_eat(".ds");
         str.find_replace(":", "");
         l.m_straLibHppPath.add(m_pathTime / strLibRel / str + ".h");
      }

      string strLib(strName.name());


      //#ifdef _DEBUG
#ifdef LINUX
      l.m_strLibraryPath = "/aura/" / m_strDynamicSourceStage / "x86/libnetnodelibrary.so";
#else
      l.m_strLibraryPath = m_pintegrationcontext->m_pathBuildFolder / m_strDynamicSourceStage / m_pintegrationcontext->m_strPlatform / "dynamic_source/" / strName / strLib + ".dll";
#endif
      //#else
      // plib->m_strLibraryPath.formatf(strFolder, "app/_stage/aura/account/app/main/front/Release/%s.dll", false), strName);
      //#endif

      directory()->create(l.m_strLibraryPath.folder());
      directory()->create(m_pathTime / "intermediate" / m_pintegrationcontext->m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + "_dynamic_source_library/library");

      for (int i = 0; i < l.m_straLibIncludePath.get_size(); i++)
      {
         cppize(l.m_straLibIncludePath[i], l.m_straLibHppPath[i], cpptype_include);
      }


      //      string strN = m_pmanager->m_pathNetnodePath;
            //    strN.replace("\\","/");
            //  if(!string_ends(strN,"/") && !string_ends(strN,"\\"))
            //   strN += "/";


#ifdef WINDOWS
      string vars1batSrc;
      string vars2batSrc;
      string vars1batDst;
      string vars2batDst;
      vars1batSrc = m_pintegrationcontext->m_pathBuildFolder / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "/_stage/dynamic_source/vc_vars.bat";
      vars2batSrc = m_pintegrationcontext->m_pathBuildFolder / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "/_stage/dynamic_source/vc_vars_query_registry.bat";
      vars1batDst = m_pintegrationcontext->m_pathBuildFolder / m_strDynamicSourceStage / "front/vc_vars.bat";
      vars2batDst = m_pintegrationcontext->m_pathBuildFolder / m_strDynamicSourceStage / "front/vc_vars_query_registry.bat";
      try
      {
         file()->copy(vars1batDst, vars1batSrc, false);
      }
      catch (...)
      {
      }
      try
      {
         file()->copy(vars2batDst, vars2batSrc, false);
      }
      catch (...)
      {
      }

#endif

      for (int i = 0; i < l.m_straLibSourcePath.get_size(); i++)
      {
         if (l.m_straLibSourcePath[i].final_extension() == "cpp")
         {
            file_system()->copy(l.m_straLibCppPath[i], l.m_straLibSourcePath[i], false);
         }
         else
         {
            cppize(l.m_straLibSourcePath[i], l.m_straLibCppPath[i], cpptype_source);

         }
         string strRel = l.m_straLibSourcePath[i].relative();
         strRel.case_insensitive_ends_eat(".ds");
         strRel.case_insensitive_ends_eat(".cpp");
         strRel.find_replace("\\", "/");
         ::file::path str1;
         str1 = "library/source" / strRel;
         string strCmd;
         //#ifdef _DEBUG
//#ifdef LINUX
//         strCmd = m_pintegrationcontext->m_pathBuildFolder / m_strDynamicSourceStage / "front"/ m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash";
//#else
//         strCmd = m_pintegrationcontext->m_pathBuildFolder  / m_strDynamicSourceStage / "front" / m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bat";
//#endif
#ifdef LINUX
         strCmd = m_pintegrationcontext->m_pathBuildFolder / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_libc_" + m_pintegrationcontext->m_strPlatform + ".bash";
#else
         strCmd = m_pintegrationcontext->m_pathBuildFolder / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + ::file::path("_libc") + m_pintegrationcontext->m_strPlatform + ".bat";
#endif

         //#else
         //    strCmd.formatf(strFolder, "app\\_stage\\aura\\account\\app\\main\\front\\dynamic_source_cl.bat", false));
         //#endif
         string str = file()->as_string(strCmd);


         str.find_replace("%ITEM_NAME%", ::str::find_replace("\\", "/", string(l.m_straLibCppPath[i])));
         str.find_replace("%ITEM_TITLE%", l.m_straLibCppPath[i].name());
         str.find_replace("%ITEM_DIR%", ::str::find_replace("\\", "/", string(l.m_straLibCppPath[i].folder())) + "/");
         str.find_replace("%LIBS_LIBS%", m_strLibsLibs);


         str.find_replace("%CA2_ROOT%", strV);
         str.find_replace("%NETNODE_ROOT%", strN);
         str.find_replace("%CONFIGURATION_NAME%", m_strDynamicSourceConfiguration);
         str.find_replace("%CONFIGURATION%", m_strDynamicSourceConfiguration);
         //str.find_replace("%DVP%", strDVP_B);


         //str.find_replace("%ITEM_NAME%",::str::replace("\\","/",string(str1)));
         //str.find_replace("%ITEM_DIR%",::str::replace("\\", "/", string(str1.folder())) +"/" );
         str.find_replace("%NETNODE_ROOT%", strN);
         str.find_replace("%CONFIGURATION_NAME%", m_strDynamicSourceConfiguration);
         str.find_replace("%CONFIGURATION%", m_strDynamicSourceConfiguration);
         //str.find_replace("%DVP%", strDVP_B);

         directory()->create(m_pathTime / "intermediate" / m_pintegrationcontext->m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + "_dynamic_source_library" / str1.folder());
         directory()->create(m_pathTime / "library" / m_pintegrationcontext->m_strStagePlatform / str1.folder());

         string strFormat = "libc-" + str1;

         strFormat.find_replace("/", "-");
         strFormat.find_replace("\\", "-");

#ifdef LINUX
         strFormat += ".bash";
#else
         strFormat += ".bat";
#endif
         strCmd = m_pintegrationcontext->m_pathBuildFolder / m_strDynamicSourceStage / "front" / strFormat;

         bool bTimeout = false;

         ::operating_system::process_pointer process(e_create, this);

         ::parallelization::set_priority(::e_priority_highest);

         process->create_child_process(str, true, nullptr, ::e_priority_highest);

         auto tickStart = ::time::now();

         //unsigned int dwExitCode;

         string strLog;

         while (::task_get_run())
         {

            strLog += process->read();

            if (process->has_exited())
               break;

            preempt(100_ms);

            if (tickStart.elapsed() > 890_s) // 14 minutes
            {

               bTimeout = true;

               break;

            }

         }

         strLog += process->read();

         if (bTimeout)
         {

            process->kill();

         }

         string strClog;

         strClog = m_pathTime / strLibRel / strRel + "-compile-log.txt";

         ::file::path pathCompiler = m_pathTime / strLibRel / strRel + "-compile-log.txt";

         if (!bTimeout && strLog.has_character())
         {

#ifdef LINUX

            //sleep(2000_ms);

#endif



            str = strLog;

            str.trim();


            if (str.has_character())
            {

               file()->put_text_utf8(strClog, strLog);

               l.m_memfileError << "<pre>";

               l.m_memfileError << "Compiling...\n";
               l.m_memfileError << l.m_straLibCppPath[i];
               l.m_memfileError << "\n";
               if (bTimeout)
               {
                  l.m_memfileError << "error: Timeout during compilation (If there are the compilation or link errors about the file \"" + l.m_straLibCppPath[i] + "\" following this message, they may be out-of-date)";
               }
               str.find_replace("\r\n", "\n");
               l.m_memfileError << str;

            }

            l.m_strError = l.m_memfileError.as_string();

            l.m_strError.trim();

         }


      }

      string strObjs;
      for (int i = 0; i < l.m_straLibSourcePath.get_size(); i++)
      {
         strObjs += " ";
         ::file::path strRel = l.m_straLibSourcePath[i].relative();
         strRel.case_insensitive_ends_eat(".ds");
         strObjs += m_pathTime / "intermediate" / m_pintegrationcontext->m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + "_dynamic_source_library/library" / strName;
         //strObjs += m_pathTime.separator();
         strObjs += "/";
         strObjs += strRel;
#ifdef LINUX
         strObjs += ".o";
#else
         strObjs += ".obj";
#endif
         strObjs += " ";
      }
      ::file::path strCmd;
      //#ifdef _DEBUG
//      strCmd = m_pintegrationcontext->m_pathBuildFolder  / m_strDynamicSourceStage / "front" / m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 +
//#ifdef LINUX
//         ".bash";
//#else
//         ".bat";
//#endif
#ifdef LINUX
      strCmd = m_pintegrationcontext->m_pathBuildFolder / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_libl_" + m_pintegrationcontext->m_strPlatform + ".bash";
#else
      strCmd = m_pintegrationcontext->m_pathBuildFolder / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_libl" + m_pintegrationcontext->m_strPlatform + ".bat";
#endif
      //#else
      // strCmd.formatf(strFolder, "app\\_stage\\aura\\account\\app\\main\\front\\dynamic_source_libl.bat", false));
      //#endif
      string str = file()->as_string(strCmd);
      str.find_replace("%ITEM_NAME%", ::file::path("library") / strName);
      str.find_replace("%ITEM_DIR%", "library");
      str.find_replace("%OBJECTS%", strObjs);
      str.find_replace("%NETNODE_ROOT%", strN);
      str.find_replace("%CONFIGURATION_NAME%", m_strDynamicSourceConfiguration);
      str.find_replace("%CONFIGURATION%", m_strDynamicSourceConfiguration);
      //str.find_replace("%DVP%", strDVP_B);

      string strTargetName = l.m_strLibraryPath;
      strTargetName.case_insensitive_ends_eat(".dll");
      str.find_replace("%TARGET_NAME%", strTargetName);
      directory()->create(m_pintegrationcontext->m_pathBuildFolder / m_strDynamicSourceStage / m_pintegrationcontext->m_strStagePlatform / "library");
      //#ifdef LINUX
      //      //sleep(2000_ms);
      //      strCmd = m_pintegrationcontext->m_pathBuildFolder /m_strDynamicSourceStage/ "front\\libl1.bash";
      //#else
      //      strCmd = m_pintegrationcontext->m_pathBuildFolder / m_strDynamicSourceStage / "front\\libl1.bat";
      //#endif

            //file()->put_text_utf8(strCmd, str);
      bool bTimeout = false;

      ::operating_system::process_pointer process(e_create, this);

      ::parallelization::set_priority(::e_priority_highest);

      process->create_child_process(str, true, nullptr, ::e_priority_highest);
      auto tickStart = ::time::now();

      string strLog;

      while (::task_get_run())
      {

         strLog += process->read();

         if (process->has_exited())
         {

            break;

         }

         preempt(100_ms);

         if (tickStart.elapsed() > 890_s) // 14 minutes
         {

            bTimeout = true;

            break;

         }

      }

      strLog += process->read();

      if (bTimeout)
      {

         process->kill();

      }

      string strLlog;

      strLlog = m_pathTime / strLibRel / "link-log.txt";

      if (!bTimeout && strLog.has_character())
      {

#ifdef LINUX

         //sleep(2000_ms);

#endif

         str = strLog;

         str.trim();

         if (str.has_character())
         {

            file()->put_text_utf8(strLlog, strLog);
            l.m_memfileError << "Linking...\n";
            str.find_replace("\r\n", "\n");
            l.m_memfileError << str;
            l.m_memfileError << "</pre>";

         }

         l.m_strError = l.m_memfileError.as_string();

         l.m_strError.trim();

      }

      l.load_library();

      return l;

   }


   void script_compiler::cppize(const ::file::path& lpcszSource, const ::file::path& lpcszDest, ecpptype enum_type)
   {

      directory()->create(lpcszDest.folder());

      cppize1(lpcszSource, lpcszDest, enum_type);

   }


   void script_compiler::cppize1(const ::file::path& lpcszSource, const ::file::path& lpcszDest, ecpptype enum_type)
   {

      string strSource = file()->as_string(lpcszSource);

      bool bCode = false;

      string strDest;
      strDest = "";
      strDest = "";
      if (enum_type == cpptype_source || enum_type == cpptype_ds)
      {
         strDest += "#include \"netnode_dynamic_source_script.h\"\r\n";
         //strDest += "#include \"11ca2_account.h\"\r\n";
         //for(int i = 0; i < m_straLibIncludePath.get_count(); i++)
         //{
         //   string str;
         //   str = m_straLibIncludePath[i].relative();
         //   str.case_insensitive_ends_eat(".ds");
         //   strDest += "#include \""+str+".h\"\r\n";
         //}
      }

      strDest += "\r\n";
      strDest += "\r\n";
      character_count iPosId = strDest.length();
      strDest += "\r\n";
      strDest += "\r\n";

      character_count iStart = 0;
      character_count iPos = 0;
      character_count iLastEnd = 0;
      string_array_base straId;
      while ((iPos = strSource.find_index("<?", iStart)) >= 0)
      {
         if (iPos > iLastEnd && bCode)
         {
            strDest += get_ds_print(strSource.substr(iLastEnd, iPos - iLastEnd));
         }
         iLastEnd = strSource.find_index("?>", iPos);
         if (iLastEnd < 0)
            break;
         iLastEnd += 2;
         int iShift = 0;
         if (strSource.substr(iPos, 5).case_insensitive_order("<?php") == 0)
            iShift = 3;
         bCode = true;
         strDest += cppize2(strSource.substr(iPos + 2 + iShift, iLastEnd - iPos - 4 - iShift), false, straId);
         iStart = iLastEnd;
      }
      /*   strDest += "   print(\"" ;
      strDest += escape(strSource.substr(iStart));
      strDest += "\");\r\n";
      strDest += "//End parsed user script\r\n";
      strDest += "}\r\n";*/

      //string strId;
      //for(int i = 0; i < straId.get_size(); i++)
      //{
      //   strId += "static ::atom lscript_id" + ::as_string(i) + "(\"" + straId[i] + "\");\r\n";
      //}

      //strDest = strDest.left(iPosId) + strId + strDest.substr(iPosId);

      //file()->put_text_utf8(lpcszDest, strDest);
      file()->put_text(lpcszDest, strDest);


   }


   void add_var_id(string& strResult, character_count& iArroba, string_array_base& straId, bool bMakeKeyLower)
   {
      string strKey = strResult.substr(iArroba);
      if (bMakeKeyLower)
      {
         strKey.make_lower();
      }
      auto iFind = straId.find_first(strKey);
      if (::not_found(iFind))
      {
         straId.add(strKey);
         iFind = straId.get_upper_bound();
      }
      //strResult = strResult.left(iArroba) + " lscript_id" + as_string(iFind);
      strResult = strResult.left(iArroba) + " \"" + strKey + "\"";
      iArroba = -1;
   }

   string script_compiler::cppize2(const ::scoped_string & scopedstr, bool bScript, string_array_base& straId)
   {
      string str(scopedstr);
      str.trim();
      bool bInSimpleQuote = false;
      bool bInDoubleQuote = false;
      character_count iSimpleQuote = 0;
      character_count iArroba = -1;
      bool bInVar = false;
      bool bInSlash = false;
      bool bInRet = false;
      bool bInSpec1 = false;
      bool bInSpec1Close = false;
      bool bInSpec2 = false;
      bool bInSpec2Close = false;
      bool bServer = false;
      character_count iServer = -1;
      character_count iBracket = 0;
      bool bInBrace = false;
      character_count iVar = -1;
      character_count iIdLen = 0;
      ::utf8_character_range ch2(str);
      //::utf8_character_range ch2.next()(str, ch2.m_iNext);
      string strResult;
      character_count iLen = str.length();
      //character_count i2 = 0;
      //character_count iNext2 = 0;
      //character_count iNext3 = 0;
      bool bInitial = true;
      string strSpec1;
      string strSpec1Macro;
      character_count iOpenParen = 1; // open Parenthesis Count
      string_array_base straFunction;
      index_array iaFunctionParen; // index of the parenthesis of the function
      bool bInserted = false;
      bool bNewLine = true;
      bool bLow = false;
      while (ch2.m_i < iLen)
      {
         bInserted = false;
         //iNext2 = i2;
         //iNext3 = iNext2;
         //ch2.next().m_i = ch2.m_iNext;
         //ch2.next().get();
         if (string_begins(str.substr(ch2.m_i), "bk_filter_active1"))
         {
            //debug_break();
         }
         if (bInSpec1)
         {
            if (ch2 == '\r' || ch2 == '\n')
            {
               bNewLine = true;
               ch2++;
            }
            else if (ch2.is_ansi_space())
            {
               ch2++;
               continue;
            }
            else if (ch2 == '(')
            {
               if (strSpec1Macro.has_character())
               {
                  strResult += strSpec1Macro + "(";
               }
               else
               {

                  strResult += strSpec1 + "(";
               }
               bInSpec1 = false;
               ch2++;
               bNewLine = false;
               continue;
            }
            else
            {
               if (strSpec1Macro.has_character())
               {
                  strResult += strSpec1Macro + "(";
               }
               else
               {

                  strResult += strSpec1 + "(";
               }
               bInSpec1Close = true;
               bInSpec1 = false;
            }
         }
         if (bInSpec2)
         {
            if (ch2 == '\r' || ch2 == '\n')
            {
               bNewLine = true;
               ch2++;
            }
            else if (ch2.is_ansi_space())
            {
               ch2++;
               continue;
            }
            else if (ch2 == '=')
            {
               strResult += ".payloada().add(";
               bInSpec2 = false;
               bInSpec2Close = true;
               ch2++;
               bNewLine = false;
               continue;
            }
            else
            {
               ///erro
            }
         }
         if (bServer)
         {
            if (ch2.is_ansi_alpha() || ch2.is_ansi_digit() || ch2 == '.' || ch2 == ',' || ch2 == '-' || ch2 == '_')
            {
               if (iServer < 0)
               {
                  iServer = strResult.length();
               }
            }
            else if (iServer >= 0)
            {
               bool bWaitQuote = true;
               bool bWaitCloseBracket = false;
               bServer = false;
               add_var_id(strResult, iServer, straId);
               strResult += "]";
               while (ch2.m_i < iLen)
               {
                  if (ch2.is_ansi_space())
                     ch2++;
                  else if (bWaitQuote && (ch2 == '\'' || ch2 == '\"'))
                  {
                     bWaitQuote = false;
                     bWaitCloseBracket = true;
                     ch2++;
                  }
                  else if (bWaitCloseBracket && ch2 == ']')
                  {
                     ch2++;
                     break;
                  }
                  else
                  {
                     strResult += ":*<invalid-syntax>*:"; // fatal;
                     break;
                     break;
                     //throw ::exception(::exception("invalid syntax."));
                  }
               }
               continue;
            }
            else
            {
               ch2++;
               continue;
            }
         }
         if (iBracket > 0 && ch2== ']')
         {
            strResult += ch2;
            iBracket--;
         }
         else if (bInSimpleQuote)
         {
            if (bInSlash)
            {
               bInSlash = false;
               strResult += ch2;
            }
            else
            {
               if (ch2 == '\\')
               {
                  bInSlash = true;
                  if (ch2.next() != '{'
                     && ch2.next() != '}'
                     && ch2.next() != '$')
                  {
                     strResult += ch2;
                  }
               }
               else if (ch2 == '\'')
               {
                  bInSimpleQuote = false;
                  //strResult += "\")";
                  strResult += "\"";
               }
               else
               {
                  bInSlash = false;
                  strResult += ch2;
               }
            }
         }
         else if (iArroba >= 0)
         {
            if (bInSlash)
            {
               bInSlash = false;
               strResult += ch2;
            }
            else
            {
               if (ch2 == '\\')
               {
                  bInSlash = true;
                  if (ch2.next() != '{'
                     && ch2.next() != '}'
                     && ch2.next() != '$')
                  {
                     strResult += ch2;
                  }
               }
               else if (ch2 == '@')
               {
                  add_var_id(strResult, iArroba, straId);
               }
               else
               {
                  bInSlash = false;
                  strResult += ch2;
               }
            }
         }
         else if (bInVar)
         {
            if (ch2.is_ansi_digit() || ch2.is_ansi_alpha() || ch2 == '_')
            {
               if (bLow)
               {
                  strResult += (char)ch2.ansi_lower();
               }
               else
               {
                  strResult += ch2;
               }
            }
            else
            {
               bInVar = false;
               bLow = false;
               if (bInDoubleQuote)
               {
                  if (ch2 == '$')
                  {
                     bInVar = true;
                     add_var_id(strResult, iVar, straId);
                     strResult += ") + gstr(";
                     iVar = strResult.length();
                     bLow = true;
                     ch2++;
                     continue;
                  }
                  else
                  {
                     //strResult += "\") + unitext(\"";
                     add_var_id(strResult, iVar, straId);
                     strResult += ") + \"";
                     if (ch2 == '\"')
                     {
                        bInDoubleQuote = false;
                        //strResult += "\")";
                        strResult += "\"";
                        ch2++;
                        continue;
                     }
                     else if (ch2 == '\\')
                     {
                        bInSlash = true;
                     }
                  }
               }
               else
               {
                  while (ch2.is_ansi_space() && ch2.m_i < iLen)
                  {
                     ch2++;
                  }
                  //ch = str[i];
                  //ch2.next() = ch2.next();
                  if (ch2 == '[' && ch2.next() != ']')
                  {
                     iBracket++;
                     add_var_id(strResult, iVar, straId);
                     strResult += ").propset()";
                  }
                  else if (ch2 == '-' && ch2.next() == '>')
                  {
                     ch2.ansi_add(2);
                     while (ch2.is_ansi_space() && ch2.m_i < iLen)
                     {
                        ch2++;
                     }
                     //ch = str[i];
                     string strToken;
                     if (ch2.is_ansi_alpha() || ch2 == '_')
                     {
                        strToken += ch2;
                        ch2++;
                     }
                     else
                     {
                        strResult = "-> error";
                        return strResult;
                     }
                     //ch = str[i];
                     while (ch2.is_ansi_digit() || ch2.is_ansi_alpha() || ch2 == '_')
                     {
                        strToken += ch2;
                        ch2++;
                        //ch = str[i];
                     }
                     //ch = str[i];
                     while (ch2.is_ansi_space())
                     {
                        ch2++;
                        //ch = str[i];
                     }
                     if (ch2 == '(')
                     {
                        ch2++;
                        //ch = str[i];
                        iaFunctionParen.add(iOpenParen);
                        iOpenParen++;
                        straFunction.add(strToken);
                        while (ch2.is_ansi_space())
                        {
                           ch2++;
                           //ch = str[i];
                        }
                        if (ch2 == ')')
                        {
                           add_var_id(strResult, iVar, straId);
                           strResult += ").cast < " + m_pmanager->m_strNamespace + "::object_base >()->call(\"" + strToken + "\" ";
                        }
                        else
                        {
                           add_var_id(strResult, iVar, straId);
                           strResult += ").cast < " + m_pmanager->m_strNamespace + "::object_base >()->call(\"" + strToken + "\", ";
                           continue;
                        }
                     }
                     else
                     {
                        add_var_id(strResult, iVar, straId);
                        strResult += ").cast < " + m_pmanager->m_strNamespace + "::object_base >()->m_propertyset[\"" + strToken + "\"]";
                     }
                  }
                  else
                  {
                     add_var_id(strResult, iVar, straId);
                     strResult += ")";
                  }
               }
               if (ch2 == ';')
                  goto ch_comma;
               else
                  goto ch_else;
               //strResult += ch;
            }
         }
         else if (bInDoubleQuote)
         {
            if (bInSlash)
            {
               bInSlash = false;
               strResult += ch2;
            }
            else
            {
               if (ch2 == '$' && (ch2.next().is_ansi_alpha() || ch2.next() == '_'))
               {
                  bInVar = true;
                  //strResult += "\") + glowstr(\"";
                  strResult += "\" + gstr(";
                  iVar = strResult.length();
                  bLow = true;
               }
               else if (ch2 == '{')
               {
                  bInBrace = true;
                  bInDoubleQuote = false;
                  //strResult += "\") + ";
                  strResult += "\" + ";
               }
               else if (ch2 == '\\')
               {
                  bInSlash = true;
                  if (ch2.next() != '{'
                     && ch2.next() != '}'
                     && ch2.next() != '$')
                  {
                     strResult += ch2;
                  }
               }
               else if (ch2 == '\"')
               {
                  bInDoubleQuote = false;
                  //strResult += "\")";
                  strResult += "\"";
               }
               else
               {
                  bInSlash = false;
                  strResult += ch2;
               }
            }
         }
         else if (ch2 == '\"')
         {
            bInDoubleQuote = true;
            //strResult += "unitext(\"";
            strResult += "\"";
         }
         else if (ch2 == '\'')
         {
            bInSimpleQuote = true;
            //strResult += "unitext(\""; // overloads should cope with the possibility of conversion between string to character
            strResult += "\""; // overloads should cope with the possibility of conversion between string to character
            iSimpleQuote = strResult.length();
         }
         else if (ch2 == '@')
         {
            iArroba = strResult.length();
         }
         else if (ch2 == '_' && ch2.next() == '_' && is_id(&str[ch2.m_i], str.length() - ch2.m_i, "__ch", 4, iIdLen))
         {
            strResult += "'";
            bInVar = false;
            ch2.ansi_add(iIdLen);
            while (ch2 != '(' && ch2.m_i < iLen)
               ch2++;
            ch2++;
            while (ch2 != ')' && ch2.m_i < iLen)
            {
               strResult += ch2;
               ch2++;
            }
            strResult += "'";

         }
         else if (ch2 == '$' && (ch2.next().is_ansi_alpha() || ch2.next() == '_'))
         {
            if (bInVar)
            {
               if (bInDoubleQuote)
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
               if (bInDoubleQuote)
               {
                  //strResult += "\") + glowstr(\"";
                  strResult += "\" + gstr(";
                  iVar = strResult.length();
                  bLow = true;
               }
               else
               {
                  if (is_id(&str[ch2.m_i + 1], str.length() - ch2.m_i - 1, "_GET", 4, iIdLen))
                  {
                     strResult += "geta()[";
                     bInVar = false;
                     bServer = true;
                     ch2.ansi_add(iIdLen + 1);
                  }
                  else if (is_id(&str[ch2.m_i + 1], str.length() - ch2.m_i - 1, "_POST", 5, iIdLen))
                  {
                     strResult += "posta()[";
                     bInVar = false;
                     bServer = true;
                     ch2.ansi_add(iIdLen + 1);
                  }
                  else if (is_id(&str[ch2.m_i + 1], str.length() - ch2.m_i - 1, "_REQUEST", 8, iIdLen))
                  {
                     strResult += "requesta()[";
                     bInVar = false;
                     bServer = true;
                     ch2.ansi_add(iIdLen + 1);
                  }
                  else if (is_id(&str[ch2.m_i + 1], str.length() - ch2.m_i - 1, "_SERVER", 7, iIdLen))
                  {
                     strResult += "inattra()[";
                     bInVar = false;
                     bServer = true;
                     ch2 += iIdLen + 1;
                  }
                  else if (is_id(&str[ch2.m_i + 1], str.length() - ch2.m_i - 1, "_COOKIE", 7, iIdLen))
                  {
                     strResult += "cookies()[";
                     bInVar = false;
                     bServer = true;
                     ch2 += iIdLen + 1;
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
         else if (ch2 == ';')
         {
         ch_comma:
            if (bInRet)
            {
               bInRet = false;
               strResult += ch2;
               strResult += "\r\nreturn;\r\n}\r\n";
            }
            else if (bInSpec1Close)
            {
               bInSpec1Close = false;
               strResult += ")";
               strResult += ch2;
            }
            else if (bInSpec2Close)
            {
               bInSpec2Close = false;
               strResult += ")";
               strResult += ch2;
            }
            else
            {
               strResult += ch2;
            }
            bInitial = true;
         }
         else if (ch2 == '(')
         {
            strResult += ch2;
            iOpenParen++;
         }
         else if (ch2 == ')')
         {
            iOpenParen--;
            //if(iaFunctionParen.pop_match('');
            strResult += ch2;
         }
         else if (ch2 == '#')
         {
            if (bNewLine)
            {
               strResult += ch2;
               ch2++;
               while (ch2.m_i < iLen)
               {
                  //ch = str[i];
                  strResult += ch2;
                  if (ch2 == '\r' || ch2 == '\n')
                     break;
                  ch2++;

               }

            }
         }
         else
         {
         ch_else:
            if (bScript && str[ch2.m_i - 1] != '_' && is_id(&str[ch2.m_i], str.length() - ch2.m_i, "return", 6, iIdLen) && next_nonspace(str.substr(ch2.m_i + iIdLen))[0] != ';')
            {
               bInRet = true;
               strResult += "\r\n{\r\nm_varRet = ";
               ch2.ansi_add(iIdLen - 1);
            }
            else if (is_id(&str[ch2.m_i], str.length() - ch2.m_i, "include", 7, iIdLen))
            {
               bInSpec1 = true;
               strSpec1 = "include";
               strSpec1Macro = "ds_include";
               ch2.ansi_add(iIdLen - 1);
            }
            else if (is_id(&str[ch2.m_i], str.length() - ch2.m_i, "print", 5, iIdLen))
            {
               bInSpec1 = true;
               strSpec1 = "print";
               strSpec1Macro = "";
               ch2.ansi_add(iIdLen - 1);
            }
            else if (is_id(&str[ch2.m_i], str.length() - ch2.m_i, "echo", 4, iIdLen))
            {
               bInSpec1 = true;
               strSpec1 = "echo";
               strSpec1Macro = "";
               ch2.ansi_add(iIdLen - 1);
            }
            else if (str.substr(ch2.m_i, 2) == "[]")
            {
               bInSpec2 = true;
               ch2.ansi_add(2 - 1);
            }
            else if (bInBrace && ch2 == '}')
            {
               bInDoubleQuote = true;
               bInBrace = false;
               //strResult += " + unitext(\"";
               strResult += " + \"";
            }
            else
            {
               if (ch2 == '\r' || ch2 == '\n')
               {
                  bNewLine = true;

               }
               else if (ch2.is_ansi_space())
               {
               }
               else
               {
                  bNewLine = false;
               }
               if (bLow)
               {
                  strResult += (char) ch2.ansi_lower();
               }
               else
               {
                  strResult += ch2;
               }
            }
         }
         ch2++;
      }
      return strResult;

   }


   bool script_compiler::is_id(const ::scoped_string & scopedstr, character_count iLen, const ::scoped_string & scopedstrId, character_count iIdLen, character_count& iIdLenRet)
   {
      if (iLen < iIdLen)
         return false;
      if (iIdLen == iLen)
      {
         if (string_compare(scopedstr, scopedstrId) == 0)
         {
            iIdLenRet = iIdLen;
            return true;
         }
      }
      if (string_begins(scopedstr, scopedstrId)
         && !::character_isdigit(scopedstr[iIdLen])
         && !::character_isalpha(scopedstr[iIdLen])
         && scopedstr[iIdLen] != '_')
      {
         iIdLenRet = iIdLen;
         return true;
      }
      return false;
   }


   const_char_pointer script_compiler::next_nonspace(const ::scoped_string & scopedstrParam)
   {

      const ::ansi_character* psz = scopedstrParam;

      while (*psz && character_isspace(*psz))
      {

         psz++;

      }

      return psz;

   }


   void script_compiler::run_persistent()
   {

      string strPath = m_pmanager->m_pathNetseedDsCa2Path / "core/persistent";

      ::file::listing_base stra;

      //auto papp = get_app();

      //auto pcontext = m_papplication;

      stra.set_listing(strPath, e_depth_recursively);

      directory()->enumerate(stra);

      string strCat;
      strCat = m_pmanager->m_pathNetseedDsCa2Path / "core/netnode_persistent_ui_str.ds";
      string strBody;
      strBody = "<?\r\n";
      strBody += "// ATTENTION!\r\n";
      strBody += "// Do not edit this file\r\n";
      strBody += "// This file is automatically generated as the\r\n";
      strBody += "// concatenation of all .ds files in thisr\r\n";
      strBody += "// folder and subfolders!\r\n";
      strBody += "\r\n";
      strBody += "?>\r\n\r\n\r\n";
      for (int i = 0; i < stra.get_size(); i++)
      {
         string str = stra[i];
         if (case_insensitive_string_begins(str, m_pmanager->m_pathNetseedDsCa2Path / "core/persistent")
            && case_insensitive_string_ends(str, ".ds"))
         {
            strBody += file()->as_string(str);
         }
      }

      file()->put_text(strCat, strBody);

      string strInclude = strCat;

      strInclude.case_insensitive_begins_eat(m_pmanager->m_pathNetseedDsCa2Path);

      strInclude.case_insensitive_ends_eat(".ds");

      auto pfilesystemcacheitem = m_pmanager->netnode_file_path(strInclude);

      ::pointer<script_instance>pinstance = m_pmanager->get(pfilesystemcacheitem);

      if (pinstance)
      {

         auto pmain = øcreate < script_main >();

         pmain->m_pmanager2 = m_pmanager;

         pmain->m_pmain = pmain;

         pmain->init1();

         pinstance->m_pmain = pmain;

         pinstance->initialize(pmain);

         //pinstance->init1();

         string strError;

         //pinstance->initialize_dynamic_source_script_interface(pinstance, nullptr, nullptr, m_pmanager);

         auto pdsscript = pinstance->m_pscript2;

         if (pdsscript)
         {

            try
            {

               pdsscript->m_pfileError->seek_to_begin();

               string strScriptError;

               strScriptError = pdsscript->m_pfileError->as_string();

               m_pmanager->m_strPersistentError += strScriptError;

            }
            catch (...)
            {

            }

         }

         try
         {
            avoid_parsing_exception avoidparsingexception;
            pinstance->run();
         }
         catch (...)
         {
         }

      }
   }


   bool script_compiler::defer_run_persistent(const ::scoped_string & scopedstr)
   {

      string str(scopedstr);

      if (::str::case_insensitive_find("pstr_set", scopedstr) && case_insensitive_string_ends(scopedstr, ".txt"))
      {

         parse_pstr_set();

         //string strCat;
         //strCat = m_pmanager->m_pathNetseedDsCa2Path/ "aura\\netnode_persistent_ui_str.ds";
         //string strInclude = strCat;
         //strInclude.case_insensitive_begins_eat(m_pmanager->m_pathNetseedDsCa2Path);
         //strInclude.case_insensitive_ends_eat(".ds");
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
      else if (str.case_insensitive_begins_eat(m_pmanager->m_pathNetseedDsCa2Path / "aura\\persistent")
         && str.case_insensitive_ends_eat(".ds")
         && str.case_insensitive_order("netnode_persistent_ui_str") != 0)
      {
         run_persistent();
         return true;
      }
      return false;
   }


   //bool script_compiler::library_DoesMatchVersion()
   //{

   //   if(m_timeLastLibraryVersionCheck.elapsed() < (5000))
   //   {
   //      return m_bLastLibraryVersionCheck;
   //   }

   //   single_lock slLibrary(m_pmutexLibrary, true);

   //   for(int i = 0; i < m_straLibSourcePath.get_size(); i++)
   //   {

   //      //FILETIME ftCreation;
   //      //FILETIME ftAccess;
   //      //FILETIME ftModified;
   //      //memory_set(&ftCreation, 0, sizeof(FILETIME));
   //      //memory_set(&ftAccess, 0, sizeof(FILETIME));
   //      //memory_set(&ftModified, 0, sizeof(FILETIME));
   //      //HANDLE h = ::CreateFile(m_straLibSourcePath[i], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
   //      //GetFileTime(h, &ftCreation, &ftAccess, &ftModified);
   //      //::CloseHandle(h);

   //      struct stat st;

   //      stat(m_straLibSourcePath[i], &st);

   //      if(__memcmp(&st.st_ctime, &m_ftaLibCreation[i], sizeof(__time_t)) != 0
   //         || __memcmp(&m_ftaLibModified[i], &st.st_mtime, sizeof(__time_t)) != 0)
   //      {
   //         m_bLastLibraryVersionCheck = false;
   //         m_timeLastLibraryVersionCheck= ::time::now();
   //         return false;

   //      }

   //   }

   //   m_bLastLibraryVersionCheck    = true;
   //   m_timeLastLibraryVersionCheck  = ::time::now();

   //   return true;

   //}
   void library::load_library()
   {

      single_lock slLibrary(m_pmutex, true);

      øconstruct(m_plibraryLib);

      m_plibraryLib->open(m_strLibraryPath);
      // return;

      m_ftaLibCreation.set_size(m_straLibSourcePath.get_size());
      m_ftaLibAccess.set_size(m_straLibSourcePath.get_size());
      m_ftaLibModified.set_size(m_straLibSourcePath.get_size());

      for (int i = 0; i < m_straLibSourcePath.get_size(); i++)
      {

         struct stat st;

         stat(m_straLibSourcePath[i], &st);

         m_ftaLibCreation[i] = st.st_ctime;
         m_ftaLibAccess[i] = st.st_atime;
         m_ftaLibModified[i] = st.st_mtime;

         //HANDLE h = ::CreateFile(m_straLibSourcePath[i], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
         //memory_set(&m_ftaLibCreation[i], 0, sizeof(FILETIME));
         //memory_set(&m_ftaLibAccess[i], 0, sizeof(FILETIME));
         //memory_set(&m_ftaLibModified[i], 0, sizeof(FILETIME));
         //GetFileTime(h , &m_ftaLibCreation[i], &m_ftaLibAccess[i], &m_ftaLibModified[i]);
         //::CloseHandle(h);

      }

   }


   library::library(::particle* pparticle)
   {

      initialize(pparticle);

   }


   library::~library()
   {

   }


   void library::unload_library()
   {
      single_lock slLibrary(m_pmutex, true);
      m_plibraryLib->close();
   }

   string script_compiler::get_ds_print(const ::scoped_string & scopedstr)
   {
      string strSource(scopedstr);
      string strDest;
      while (strSource.length() > 0)
      {
         character_count iLen = minimum(4 * 1024, strSource.length());
         if (strSource.length() > iLen)
         {
            if (strSource[iLen] == '\n')
               iLen++;
         }
         string str = strSource.left(iLen);
         //strDest += "   ds_print(unitext(\"";
         strDest += "\r\n   ds_print(\"";
         strDest += escape(str);
         //strDest += "\"));\r\n";
         strDest += "\");\r\n";
         strSource = strSource.substr(iLen);
      }
      return strDest;
   }


   void script_compiler::parse_pstr_set()
   {

      ::file::listing_base straFile;

      //auto papp = get_app();

      //auto pcontext = m_papplication;

      ::file::path pathPstrSet = m_pmanager->m_pathNetnodePath / "net/aura/pstr_set";

      if (directory()->is(pathPstrSet))
      {

         straFile.set_listing(pathPstrSet, ::e_depth_recursively);

         directory()->enumerate(straFile);

      }

      for (int i = 0; i < straFile.get_count(); i++)
      {
         string strFile = straFile[i];
         if (::str::case_insensitive_find(".svn", strFile) >= 0 || !case_insensitive_string_ends(strFile, ".txt"))
            continue;
         strFile = file()->as_string(strFile);
         string_array_base straLine;
         straLine.explode("\r\n", strFile);
         string strExtra;
         for (int j = 0; j < straLine.get_count(); j++)
         {
            string strLine = straLine[j];
            auto range = strLine();
            try
            {
               range.consume_spaces(0);
               string strId = range.consume_c_quoted_value();
               range.consume_spaces(1);
               string strLocale = range.consume_c_quoted_value();
               range.consume_spaces(1);
               string strSchema = range.consume_c_quoted_value();
               range.consume_spaces(1);
               string strValue = range.consume_c_quoted_value();
               strExtra = "";
               try
               {
                  range.consume_spaces(1);
                  strExtra = range.consume_c_quoted_value();
               }
               catch (...)
               {
               }
               if (strExtra.has_character())
               {
                  pstr_set(strId + "." + strExtra, strLocale, strSchema, strValue);
               }
               else
               {
                  pstr_set(strId, strLocale, strSchema, strValue);
               }

            }
            catch (const ::parsing_exception&)
            {

               informationf("script_compiler::parse_pstr_set");

            }
            catch (const ::exception&)
            {

               informationf("script_compiler::parse_pstr_set");

            }
            catch (...)
            {

            }

         }

      }

   }


   void script_compiler::pstr_set(const ::atom & atomTopic, atom idLocale, atom idSchema, const ::scoped_string & scopedstr)
   {

      synchronous_lock synchronouslock(m_pmanager->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto psystem = system();

      psystem->texttable()->set(atomTopic, idLocale, idSchema, scopedstr);

   }


} // namespace dynamic_source





