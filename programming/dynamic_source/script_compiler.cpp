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
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/operating_system/process.h"
#include "acme/platform/node.h"
#include "acme/primitive/primitive/url.h"
#include "acme/primitive/datetime/datetime.h"
#include "acme/primitive/string/str.h"
#include "acme/primitive/text/context.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "apex/crypto/rsa.h"
#include "apex/filesystem/file/action.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/filesystem/file/watcher.h"
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

//::u32 RunSilent(const ::string & strFunct, const ::string & strstrParams);



namespace dynamic_source
{

   string escape(const ::string & pcsz);

   void add_var_id(string & strResult, strsize & iArroba, string_array & straId, bool bMakeKeyLower = true);


   script_compiler::script_compiler()
   {

   }


   script_compiler::~script_compiler()
   {

   }

   
   void script_compiler::initialize_dynamic_source_script_compiler(script_manager* pscriptmanager)
   {

      //auto estatus = 
      
      initialize_programming_compiler(pscriptmanager);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pmanager = pscriptmanager;

      //return estatus;

   }


   void script_compiler::init1()
   {

      acmenode()->integration_factory();

      __construct(m_pintegrationcontext);

      m_pintegrationcontext->m_strPlatform = "x64";

      prepare_compile_and_link_environment();

      folder_watch();

      run_persistent();

      parse_pstr_set();

      //return ::success;

   }


   void script_compiler::prepare_compile_and_link_environment()
   {

      auto pacmedirectory = acmedirectory();

      dir()->create(pacmedirectory->system() / "netnode_desktop/symbols");


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
//         infomration("failed to setup visual studio environment " + as_string((::i64)estatus.m_estatus));
//
//      }
//
//#endif

      m_pathTime = dir()->install() / "time-" OPERATING_SYSTEM_NAME;

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

      dir()->create(dir()->install()/m_strDynamicSourceStage / "front");

      string str;

      string strItem;

      strItem = dir()->install() / m_strDynamicSourceStage / m_pintegrationcontext->m_strStagePlatform;

      str = str + strItem + ";";

      strItem = dir()->install()/ m_strDynamicSourceStage / m_pintegrationcontext->m_strStagePlatform / "dynamic_source\\library";

      str = str + strItem + ";";

#ifdef WINDOWS_DESKTOP

      u32 dwSize = GetEnvironmentVariableW(L"PATH", nullptr, 0);
      LPWSTR lpsz = memory_new wchar_t[dwSize + 1];
      dwSize = GetEnvironmentVariableW(L"PATH", lpsz, dwSize + 1);
      str += lpsz;
      delete lpsz;

#endif

   }


   void script_compiler::compile(ds_script * pscript)
   {

      synchronous_lock synchronouslock(pscript->synchronization());

      information("Compiling script %s", pscript->m_strName.c_str());

      auto & ostreamError = pscript->m_streamError;

      ::file::path strName(pscript->m_strName);

      if (strName.case_insensitive_ends("\\auth3.ds"))
      {

         ::infomration("compile auth3.ds");

      }

      pscript->on_start_build();

#ifdef WINDOWS

      strName.find_replace("/","\\");

#endif

      //strName.replace("/", "\\");
      //string strFolder;
      //strFolder = dir()->install();
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
      if(file()->exists(strName))
      {
         pscript->m_strSourcePath = strName;
         strTransformName.find_replace(":","");
      }
      else
      {
         pscript->m_strSourcePath.format(m_pmanager->m_strNetnodePath / "net\\%s",strName.c_str());
      }
      pscript->m_strSourceDir = pscript->m_strSourcePath.folder();

      if(!file()->exists(pscript->m_strSourcePath))
      {
         ostreamError << "<pre>";
         str.format("Source File : \"%s\" does not exist",pscript->m_strSourcePath.c_str());
         ostreamError << str;
         ostreamError << "</pre>";
         return;
      }

      string strRndTitle;

      string strMillis;

      strMillis = ::as_string(::i64_millisecond() % 1000);

      auto pszBufferMillis = strMillis.get_buffer(3);

      ::ansi_zero_pad(pszBufferMillis, 3);

      strMillis.release_buffer();

      auto psystem = acmesystem()->m_paurasystem;

      auto pdatetime = psystem->datetime();

      strRndTitle = "_" + pdatetime->international().get_date_time("%Y-%m-%d_%H-%M-%S") + "_" + strMillis;

      string strTime = m_pathTime;

      pscript->m_strCppPath.format(m_pathTime / "dynamic_source\\%s.cpp",strTransformName.c_str());

      auto pathCa2Root = dir()->install();

      //string strCompileLogUnique;

      ::earth::time timeNow = ::earth::time::now();

      string strCompileLogUnique = datetime()->format(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE, timeNow);

      if (!::isdigit(strCompileLogUnique[0]))
      {

         string strCompileLogUnique2 = datetime()->format(INTERNATIONAL_DATE_TIME_FORMAT_FOR_FILE, timeNow);

         ::infomration("Ops");

      }

      strClog.format(m_pathTime / "dynamic_source/%s-compile-log-%s.txt",strTransformName.c_str(), strCompileLogUnique.c_str());
      strLlog.format(m_pathTime / "dynamic_source/%s-link-log.txt",strTransformName.c_str());

      string strPathCompiler;
      strPathCompiler.format(m_pathTime / "dynamic_source/%s-compiler.txt", strTransformName.c_str());
      ::file::path pathCompiler(strPathCompiler);

      string strPathLinker;
      strPathLinker.format(m_pathTime / "dynamic_source/%s-linker.txt", strTransformName.c_str());
      ::file::path pathLinker(strPathLinker);

      //#ifdef _DEBUG
#ifdef LINUX
      //strB = dir()->install() / m_strDynamicSourceStage / "front\\dynamic_source\\BuildBat" / strTransformName.name() / strTransformName + ".bat";
      strO = ::file::path(m_pathTime) / "intermediate" / m_pintegrationcontext->m_strPlatform / m_pmanager->m_strNamespace + "_dynamic_source_script" / strTransformName / strTransformName.name() + ".o";
#else

      //strB = m_strDynamicSourceStageFolder / "front\\dynamic_source\\BuildBat" / strTransformName.name() / strTransformName + ".bat";

      strP = m_strDynamicSourceStageFolder / m_pintegrationcontext->m_strPlatform / "dynamic_source" / strTransformName.sibling(strScript.name()) + ".pdb";

      strL = m_strDynamicSourceStageFolder / m_pintegrationcontext->m_strPlatform / "dynamic_source" / strTransformName.sibling(strScript.name()) + ".lib";

      strE = m_strDynamicSourceStageFolder / m_pintegrationcontext->m_strPlatform / "dynamic_source" / strTransformName.sibling(strScript.name()) + ".exp";

      ::file::path strDynamicSourceScriptFolder = m_pathTime / "intermediate" / m_pintegrationcontext->m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + "_dynamic_source_script";

      //strDVI = strDynamicSourceScriptFolder / strTransformName / m_strSdk1 + ".idb";

      //::file::path pathSourceDVP = strDynamicSourceScriptFolder / strTransformName / m_strSdk1 + ".pdb";
      
      ::file::path pathSourceNetnodeDSS = pathCa2Root / "time-" OPERATING_SYSTEM_NAME "/intermediate/x64" / m_strDynamicSourceConfiguration / "app-core/netnode_dynamic_source_script";

      ::file::path pathSourceDVP = pathSourceNetnodeDSS / (m_pintegrationcontext->payload("sdk1").as_string() + ".pdb");

      //::file::path pathCompiler;

      {

         ::file::path pathHelper1 = strTransformName.sibling(strScript.name());

         string strHelper1 = pathHelper1.name() + "-" + m_pintegrationcontext->payload("sdk1").as_string() + ".pdb";

         auto pathDVP0 = m_strDynamicSourceStageFolder / m_pintegrationcontext->m_strPlatform / "dynamic_source" / pathHelper1.folder() / strHelper1;

         string strCompiler = pathHelper1.name() + "-compiler.txt";

         string strDVP1 = pathDVP0;

         solve_relative(strDVP1);

         strDVP = strDVP1;

         ::file::path pathDVP = strDVP;

         ::file::path pathDVP_Folder = pathDVP.folder();

         acmedirectory()->create(pathDVP_Folder);

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

      strObj = strDynamicSourceScriptFolder / strTransformName / strTransformName.name() + ".obj";

      strO = strDynamicSourceScriptFolder / strTransformName.name() / strTransformName + ".bat";

#endif

      pscript->m_strScriptPath = m_pmanager->get_script_path(strName, strRndTitle);

      try
      {
         if(file()->exists(strO))
         {
            file()->erase(strO);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(file()->exists(strObj))
         {
            file()->erase(strObj);
         }
      }
      catch(...)
      {
      }
#ifndef LINUX
      try
      {
         if(file()->exists(strP))
         {
            file()->erase(strP);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(file()->exists(strL))
         {
            file()->erase(strL);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(file()->exists(strE))
         {
            file()->erase(strE);
         }
      }
      catch(...)
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

         if(file()->exists(strClog))
         {

            file()->erase(strClog);

         }

      }
      catch(...)
      {

      }

      try
      {

         if(file()->exists(strLlog))
         {

            file()->erase(strLlog);

         }

      }
      catch(...)
      {

      }

      //::DeleteFile(pscript->m_strBuildBat);

      try
      {

         if(file()->exists(pscript->m_strScriptPath + ".old"))
         {

            file()->erase(pscript->m_strScriptPath + ".old");

         }

      }
      catch (const ::exception &)
      {

         //::exception_pointer esp(pexception);

         //information("%s", esp->get_message().c_str());

      }

      try
      {

         if(file()->exists(pscript->m_strScriptPath))
         {

            file()->transfer(pscript->m_strScriptPath + ".old",pscript->m_strScriptPath);

         }

      }
      catch (const ::exception &)
      {

         //::exception_pointer esp(pexception);

         //information("%s", esp->get_message().c_str());

      }

      try
      {

         if(file()->exists(pscript->m_strScriptPath + ".old"))
         {

            file()->erase(pscript->m_strScriptPath + ".old");

         }

      }
      catch (const ::exception &)
      {

         //::exception_pointer esp(pexception);

         //information("%s", esp->get_message().c_str());

      }


      dir()->create(pscript->m_strScriptPath.folder());
      dir()->create(strL.folder());
      dir()->create(m_pathTime / "intermediate" / m_pintegrationcontext->m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + ::file::path("_dynamic_source_script") / strTransformName);

      cppize(pscript);

      //auto pathCa2Root = dir()->install();

      string strV(pathCa2Root);
      strV.find_replace("\\","/");
      if(!string_ends(strV,"/") && !string_ends(strV,"\\"))
         strV += "/";

      string strN = m_pmanager->m_strNetnodePath;
      strN.find_replace("\\","/");
      if(!string_ends(strN,"/") && !string_ends(strN,"\\"))
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

#if defined(LINUX) || defined(MACOS) || defined(FREEBSD)
      strBuildCmd.format(dir()->install() / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_cl_" + m_pintegrationcontext->m_strPlatform + ".bash");
#else
      strBuildCmd.format(dir()->install() / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "\\_stage\\dynamic_source" / m_pintegrationcontext->payload("vstools").as_string() / m_strDynamicSourceConfiguration + "_c_" + m_pintegrationcontext->m_strPlatform + ".bat");
#endif

      str = file()->as_string(strBuildCmd);
      str.find_replace("%ITEM_NAME%",strItemName);
      str.find_replace("%ITEM_TITLE%",strItemTitle);
      str.find_replace("%ITEM_DIR%",::str::replace_with("\\","/",string(strTransformName.folder())) + "/");
      str.find_replace("%LIBS_LIBS%",m_strLibsLibs);


      str.find_replace("%CA2_ROOT%",strV);
      str.find_replace("%NETNODE_ROOT%",strN);
      str.find_replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
      str.find_replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
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
      str.find_replace("%TARGET_PATH%",strTargetPath);
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
      process->create_child_process(strCompiler,true, pathCa2Root/ "source/app-core/netnode_dynamic_source_script",::e_priority_highest);
#else
      process->create_child_process(strCompiler,true,m_pintegrationcontext->m_pathProjectDir,::e_priority_highest);
#endif

      //::system(str + " > " + "\"" + strClog + "\"");

      auto tickStart = ::time::now();

      string strLog;

      while(::task_get_run())
      {

         strLog += process->read();

         if(process->has_exited())
            break;

         preempt(100_ms);

         if(tickStart.elapsed() > 890_s) // 14 minutes
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

            file()->put_text_utf8(strClog, strLog);

            ostreamError << "<pre>";

            //ostreamError << "Compiling Command\n";
            //ostreamError << pathCompiler << "\n";
            information("Compiling Command File %s", pathCompiler.c_str());
            information("Compiling Command %s", strCompiler.c_str());
            ostreamError << "Compiling...\n";
            ostreamError << pscript->m_strCppPath;
            ostreamError << "\n";
            if(bTimeout)
            {
               ostreamError << "error: Timeout during compilation (If there are the compilation or link errors about the file \"" + pscript->m_strCppPath + "\" following this message, they may be out-of-date)";
            }
            str.find_replace("\r\n","\n");
            ostreamError << str;

         }

         int iObjFileMinimumByteCount = 1024;

         if (process->m_exitstatus.m_iExitCode != 0 || file()->length(pathObjFile) < iObjFileMinimumByteCount)
         {

            information("Compilation FAILED: or object file is shorter than %lld bytes...", iObjFileMinimumByteCount);
            information("%s", strLog.c_str());

            //string_array straLog;
            //straLog.add_lines(strLog);
            //for(auto & strLine : straLog)
            //{
            //   int iColCount = 80;
            //   for (index i = 0; i < strLine.length(); i += iColCount)
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

#if defined(LINUX) || defined(MACOS) || defined(FREEBSD)
         strBuildCmd.format(dir()->install() / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME"\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_cl_" + m_pintegrationcontext->m_strPlatform + ".bash");
#else
         strBuildCmd.format(dir()->install() / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "\\_stage\\dynamic_source" /m_pintegrationcontext->payload("vstools").as_string() / m_strDynamicSourceConfiguration + "_l_" + m_pintegrationcontext->m_strPlatform + ".bat");
#endif

         str = file()->as_string(strBuildCmd);
         str.find_replace("%ITEM_NAME%",::str::find_replace("\\","/",string(strTransformName)));
         str.find_replace("%ITEM_TITLE%",strTransformName.name());
         str.find_replace("%ITEM_DIR%",::str::find_replace("\\","/",string(strTransformName.folder())) + "/");
         str.find_replace("%LIBS_LIBS%",m_strLibsLibs);


         str.find_replace("%CA2_ROOT%",strV);
         str.find_replace("%NETNODE_ROOT%",strN);
         str.find_replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
         str.find_replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
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
         
         str.find_replace("%TARGET_PATH%",strTargetPath);

         string strHmhLctvWildPdbPath;

         string strSymbolName;

         strSymbolName = ::file::path(strTransformName).title();

         strSymbolName += strRndTitle;

         auto pacmedirectory = acmedirectory();

         strHmhLctvWildPdbPath = ::file::path(pacmedirectory->system() / "netnode_desktop\\symbols") / strSymbolName;

         str.find_replace("%HMH_LCTVWILD_PDB_PATH%",strHmhLctvWildPdbPath);

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

         process->create_child_process(strLinker,true,nullptr,::e_priority_highest);

         auto tickStart = ::time::now();

         string strLog;

         while(::task_get_run())
         {

            strLog += process->read();

            if(process->has_exited())
               break;

            preempt(100_ms);

            if(tickStart.elapsed() > 890_s) // 14 minutes
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

               file()->put_text_utf8(strLlog,strLog);
               ostreamError << "Linking...\n";
               //ostreamError << "Linker Command File" << "\n";
               //ostreamError << pathLinker << "\n";
               information() << "Linker Command File " << pathLinker.c_str();
               //ostreamError << "Linker Command" << "\n";
               //ostreamError << strLinker << "\n";
               information() << "Linker Command " << strLinker.c_str();
               str.find_replace("\r\n","\n");
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
      catch(...)
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

   void script_compiler::cppize(ds_script * pscript)
   {

      auto ftDs = get_file_time_set(pscript->m_strSourcePath);

      if(file()->exists(pscript->m_strCppPath))
      {

         if(ftDs == pscript->m_ftDs)
         {

            return; // nothing to do

         }

      }

      dir()->create(pscript->m_strCppPath.folder());

      cppize1(pscript);

      pscript->m_ftDs = ftDs;

   }

   string escape(const ::string & pcsz)
   {
      string str(pcsz);
      str.find_replace("\\", "\\\\");
      str.find_replace("\"", "\\\"");
      str.find_replace("\r\n", "\\r\\n");
      str.find_replace("\r", "\\r\\n");
      str.find_replace("\n", "\\r\\n");
      str.find_replace("\t", "\\t");
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

      while ((strSource = file()->as_string(pscript->m_strSourcePath)).trimmed().is_empty() && ::task_get_run())
      {

         preempt(100_ms);

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
      //   str.case_insensitive_ends_eat(".ds");
      //   strDest += "#include \""+str+".h\"\r\n";
      //}
      strsize iStart = 0;
      strsize iPos = 0;
      strsize iLastEnd = 0;
      if(strSource.substr(0, 4) == "<?ss")
      {
         iLastEnd = strSource.find_index("?>", iPos);
         if(iLastEnd > 0)
         {
            iLastEnd += 2;
            strDest += cppize2(strSource.substr(iPos + 4, iLastEnd - iPos - 6), false, straId);
            iStart = iLastEnd;
         }
      }
      else if(strSource.substr(0, 7) == "<? //ss")
      {
         iLastEnd = strSource.find_index("?>", iPos);
         if(iLastEnd > 0)
         {
            iLastEnd += 2;
            strDest += cppize2(strSource.substr(iPos + 7, iLastEnd - iPos - 7 - 2), false, straId);
            iStart = iLastEnd;
         }
      }
      string strDs;
      if(strSource.substr(iStart, 4) == "<?ds")
      {
         iStart +=4;
         while(true)
         {
            strsize iMid = strSource.find_index("?>", iStart);
            iLastEnd = strSource.find_index("ds?>", iStart);
            if(iMid > 0 && iMid < iLastEnd)
            {
               strDs += cppize2(strSource.substr(iStart, iMid - iStart), true, straId);
               iStart = iMid + 2;
               iMid = strSource.find_index("<?", iStart);
               if(iMid < iLastEnd)
               {
                  strDs += get_ds_print(strSource.substr(iStart, iMid - iStart));
               }
               iStart = iMid + 2;
               continue;
            }
            if(iLastEnd > 0)
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
      strDest += "class " + m_pmanager->m_strNamespace + "_dynamic_source_script : virtual public ::app_consumer < ::netnode::application, ::" + m_pmanager->m_strNamespace + "::script_instance >\r\n";
      strDest += "{\r\n";
      strDest += "public:\r\n";
      //strDest += "   " + m_pmanager->m_strNamespace + "_dynamic_source_script(dynamic_source::script * pscript) : ::object(pscript->get_app()), dynamic_source::script_instance(pscript), ::" + m_pmanager->m_strNamespace + "::script_instance(pscript), ::" + m_pmanager->m_strNamespace + "::script_impl(pscript) {};  \r\n";
      strDest += "   " + m_pmanager->m_strNamespace + "_dynamic_source_script() {};\r\n";
      strDest += "   virtual ~" + m_pmanager->m_strNamespace + "_dynamic_source_script() {};\r\n";
      strDest += "   virtual void     run() { script_run(); };\r\n";
      strDest += "   virtual void script_run();\r\n";
      strDest += "   \r\n\r\n";
      strDest += strDs;
      strDest += "   \r\n\r\n\r\n";
      strDest += "};\r\n";
      strDest += "\r\n";
      strDest += "extern \"C\" __declspec(dllexport) dynamic_source::script_instance * __cdecl create_dynamic_source_script_instance ()\r\n";
      strDest += "{\r\n";
      strDest += "   return memory_new " + m_pmanager->m_strNamespace + "_dynamic_source_script();\r\n";
      strDest += "}\r\n";
      strDest += "\r\n";
      strDest += "void " + m_pmanager->m_strNamespace + "_dynamic_source_script::script_run()\r\n";
      strDest += "{\r\n";
      strDest += "//Start parsed user script\r\n";
      straId.erase_all();
      while((iPos = strSource.find_index("<?", iStart)) >= 0)
      {
         if(iPos > iLastEnd)
         {
            strDest += get_ds_print(strSource.substr(iLastEnd, iPos - iLastEnd));
         }
         iLastEnd = strSource.find_index("?>", iPos);
         if(iLastEnd < 0)
            break;
         iLastEnd += 2;
         i32 iShift = 0;
         if(strSource.substr(iPos, 5).case_insensitive_order("<?php") == 0)
            iShift = 3;
         strDest += cppize2(strSource.substr(iPos + 2 + iShift, iLastEnd - iPos - 4 - iShift), true, straId);
         iStart = iLastEnd;
      }
      strDest += get_ds_print(strSource.substr(iStart));

      strDest += "//End parsed user script\r\n";
      //strDest += "return ::success;\r\n";
      strDest += "}\r\n";

      string strId;
      for(i32 i = 0; i < straId.get_size(); i++)
      {
         strId += "static ::atom lscript_id" + ::as_string(i) + "(\"" + straId[i] + "\");\r\n";
      }

      strDest = strDest.left(iPosId) + strId + strDest.substr(iPosId);


      string strCppPath =  pscript->m_strCppPath;

      strCppPath.find_replace("\\","\\\\");

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
//             ::infomration(\"netnode_desktop script initializing : " + strCppPath + "!\\n\"); \r\n \
// \r\n \
// \r\n \
//         } \r\n \
//         else if(dwReason == DLL_PROCESS_DETACH) \r\n \
//         { \r\n \
// \r\n \
// \r\n \
//            ::infomration(\"netnode_desktop script terminating : " + strCppPath + "!\\n\"); \r\n \
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

   void script_compiler::operator()(::file::action * paction)
   {

      synchronous_lock synchronouslock(m_pmutex);

      ::file::path path = paction->m_pathFolder / paction->m_pathFile;

      string strTransfer = path;

      // does not transfer
      if(::str::case_insensitive_find("netnode_persistent_ui_str", strTransfer) >= 0)
         return;

      //auto psystem = acmesystem()->m_paurasystem;

      if(m_straSync.get_count() > 1)
      {
         for(i32 i = 1; i < m_straSync.get_count(); i++)
         {

            property_set set;

            //auto purl = psystem->url();

            m_pcontext->m_papexcontext->http().get("http://" + m_straSync[i] + "/synchronization?src=" +m_straSync[0] + "&url=" + ::url::encode(strTransfer) + "&pwd=sym123&authnone=1", set);

         }

      }

      if(string_begins(path, m_pmanager->m_strNetseedDsCa2Path/ "library/include"))
      {

         m_pmanager->m_pcache->set_all_out_of_date();

      }
      else if(string_begins(path, m_pmanager->m_strNetseedDsCa2Path / "library/source"))
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

      m_filewatcherid = dir()->watcher().add_watch(m_pmanager->m_strNetseedDsCa2Path, this, true);

   }


   library & script_compiler::lib(const ::string & pszLibrary)
   {

      single_lock slLibrary(m_pmutexLibrary,true);

      auto p = m_mapLib.plookup(pszLibrary);

      if(::is_ok(p))
      {
         return *p->element2();
      }

      m_mapLib[pszLibrary] = __new(library(this));

      library & l = *m_mapLib[pszLibrary];

      auto pathCa2Root = dir()->install();

      string strV(pathCa2Root);
      strV.find_replace("\\","/");
      if(!string_ends(strV,"/") && !string_ends(strV,"\\"))
         strV += "/";

      string strN = m_pmanager->m_strNetnodePath;
      strN.find_replace("\\","/");
      if(!string_ends(strN,"/") && !string_ends(strN,"\\"))
         strN += "/";


      //unload_library();

      string strLibrary(pszLibrary);

      ::file::path strName = strLibrary;

      m_strLibsLibs = dir()->install() / "time-" OPERATING_SYSTEM_NAME"/library" / m_pintegrationcontext->m_strStagePlatform / "/library/"+strLibrary+".lib";

      //m_memfileLibError.set_length(0);
      string strFolder;
      strFolder = dir()->install();

      //auto papp = get_app();

      //l.m_straLibSourcePath.m_pprovider = papp->m_papexapplication;

      l.m_straLibSourcePath.clear_results();

      //auto pcontext = m_pcontext;

      l.m_straLibSourcePath.set_listing(m_pmanager->m_strNetseedDsCa2Path / "library" / strName, ::e_depth_recursively);

      dir()->enumerate(l.m_straLibSourcePath);

      for(i32 i = 0; i < l.m_straLibSourcePath.get_size();)
      {
         if(l.m_straLibSourcePath[i].final_extension() != "ds" && l.m_straLibSourcePath[i].final_extension() != "cpp")
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
         str.case_insensitive_ends_eat(".ds");
         str.find_replace(":","");
         l.m_straLibCppPath.add(m_pathTime / strLibRel / str + ".cpp");
      }
      //l.m_straLibIncludePath.m_pprovider = papp->m_papexapplication;
      l.m_straLibIncludePath.clear_results();
      l.m_straLibIncludePath.set_listing(m_pmanager->m_strNetseedDsCa2Path / "library" / strName, e_depth_recursively);
      dir()->enumerate(l.m_straLibIncludePath);
      for(i32 i = 0; i < l.m_straLibIncludePath.get_size();)
      {
         if(l.m_straLibIncludePath[i].final_extension() != "h"
               || ::str::case_insensitive_find(l.m_straLibIncludePath[i],"\\.svn\\") >= 0
               || dir()->is(l.m_straLibIncludePath[i]))
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
         str.case_insensitive_ends_eat(".ds");
         str.find_replace(":","");
         l.m_straLibHppPath.add(m_pathTime / strLibRel / str + ".h");
      }

      string strLib(strName.name());


      //#ifdef _DEBUG
#ifdef LINUX
      l.m_strLibraryPath = "/aura/" / m_strDynamicSourceStage / "x86/libnetnodelibrary.so";
#else
      l.m_strLibraryPath = dir()->install() / m_strDynamicSourceStage / m_pintegrationcontext->m_strPlatform / "dynamic_source/" / strName / strLib + ".dll";
#endif
      //#else
      // plib->m_strLibraryPath.format(strFolder, "app/_stage/aura/account/app/main/front/Release/%s.dll", false), strName);
      //#endif

      dir()->create(l.m_strLibraryPath.folder());
      dir()->create(m_pathTime / "intermediate" / m_pintegrationcontext->m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + "_dynamic_source_library/library");

      for(i32 i = 0; i < l.m_straLibIncludePath.get_size(); i++)
      {
         cppize(l.m_straLibIncludePath[i],l.m_straLibHppPath[i],cpptype_include);
      }


//      string strN = m_pmanager->m_strNetnodePath;
      //    strN.replace("\\","/");
      //  if(!string_ends(strN,"/") && !string_ends(strN,"\\"))
      //   strN += "/";


#ifdef WINDOWS
      string vars1batSrc;
      string vars2batSrc;
      string vars1batDst;
      string vars2batDst;
      vars1batSrc = dir()->install() / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "/_stage/dynamic_source/vc_vars.bat";
      vars2batSrc = dir()->install() / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "/_stage/dynamic_source/vc_vars_query_registry.bat";
      vars1batDst = dir()->install() / m_strDynamicSourceStage / "front/vc_vars.bat";
      vars2batDst = dir()->install() / m_strDynamicSourceStage / "front/vc_vars_query_registry.bat";
      try
      {
         file()->copy(vars1batDst,vars1batSrc,false);
      }
      catch(...)
      {
      }
      try
      {
         file()->copy(vars2batDst,vars2batSrc,false);
      }
      catch(...)
      {
      }

#endif

      for(i32 i = 0; i < l.m_straLibSourcePath.get_size(); i++)
      {
         if(l.m_straLibSourcePath[i].final_extension() == "cpp")
         {
            acmefile()->copy(l.m_straLibCppPath[i], l.m_straLibSourcePath[i], false);
         }
         else
         {
            cppize(l.m_straLibSourcePath[i],l.m_straLibCppPath[i],cpptype_source);

         }
         string strRel = l.m_straLibSourcePath[i].relative();
         strRel.case_insensitive_ends_eat(".ds");
         strRel.case_insensitive_ends_eat(".cpp");
         strRel.find_replace("\\","/");
         ::file::path str1;
         str1 = "library/source" / strRel;
         string strCmd;
         //#ifdef _DEBUG
//#ifdef LINUX
//         strCmd = dir()->install()/ m_strDynamicSourceStage / "front"/ m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash";
//#else
//         strCmd = dir()->install() / m_strDynamicSourceStage / "front" / m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bat";
//#endif
#ifdef LINUX
         strCmd.format(dir()->install() / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_libc_" + m_pintegrationcontext->m_strPlatform + ".bash");
#else
         strCmd.format(dir()->install() / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + ::file::path("_libc") + m_pintegrationcontext->m_strPlatform + ".bat");
#endif

         //#else
         //    strCmd.format(strFolder, "app\\_stage\\aura\\account\\app\\main\\front\\dynamic_source_cl.bat", false));
         //#endif
         string str = file()->as_string(strCmd);


         str.find_replace("%ITEM_NAME%",::str::find_replace("\\","/",string(l.m_straLibCppPath[i])));
         str.find_replace("%ITEM_TITLE%",l.m_straLibCppPath[i].name());
         str.find_replace("%ITEM_DIR%",::str::find_replace("\\","/",string(l.m_straLibCppPath[i].folder())) + "/");
         str.find_replace("%LIBS_LIBS%",m_strLibsLibs);


         str.find_replace("%CA2_ROOT%",strV);
         str.find_replace("%NETNODE_ROOT%",strN);
         str.find_replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
         str.find_replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
         //str.find_replace("%DVP%", strDVP_B);


         //str.find_replace("%ITEM_NAME%",::str::replace("\\","/",string(str1)));
         //str.find_replace("%ITEM_DIR%",::str::replace("\\", "/", string(str1.folder())) +"/" );
         str.find_replace("%NETNODE_ROOT%",strN);
         str.find_replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
         str.find_replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
         //str.find_replace("%DVP%", strDVP_B);

         dir()->create(m_pathTime / "intermediate" / m_pintegrationcontext->m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + "_dynamic_source_library" / str1.folder());
         dir()->create(m_pathTime / "library" / m_pintegrationcontext->m_strStagePlatform / str1.folder());

         string strFormat = "libc-" + str1;

         strFormat.find_replace("/","-");
         strFormat.find_replace("\\","-");

#ifdef LINUX
         strFormat += ".bash";
#else
         strFormat += ".bat";
#endif
         strCmd = dir()->install() / m_strDynamicSourceStage / "front" / strFormat;

         bool bTimeout = false;

         ::operating_system::process_pointer process(e_create, this);

         ::parallelization::set_priority(::e_priority_highest);

         process->create_child_process(str,true,nullptr,::e_priority_highest);

         auto tickStart = ::time::now();

         //u32 dwExitCode;

         string strLog;

         while(::task_get_run())
         {

            strLog += process->read();

            if(process->has_exited())
               break;

            preempt(100_ms);

            if(tickStart.elapsed() > 890_s) // 14 minutes
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
         strClog = m_pathTime / strLibRel / strRel +"-compile-log.txt";

         ::file::path pathCompiler = m_pathTime / strLibRel / strRel + "-compile-log.txt";


         if(!bTimeout && strLog.has_char())
         {

#ifdef LINUX

            //sleep(2000_ms);

#endif



            str = strLog;

            str.trim();


            if(str.has_char())
            {

               file()->put_text_utf8(strClog,strLog);

               l.m_memfileError << "<pre>";

               l.m_memfileError << "Compiling...\n";
               l.m_memfileError << l.m_straLibCppPath[i];
               l.m_memfileError << "\n";
               if(bTimeout)
               {
                  l.m_memfileError << "error: Timeout during compilation (If there are the compilation or link errors about the file \"" + l.m_straLibCppPath[i] + "\" following this message, they may be out-of-date)";
               }
               str.find_replace("\r\n","\n");
               l.m_memfileError << str;

            }

            l.m_strError = l.m_memfileError.as_string();

            l.m_strError.trim();

         }


      }

      string strObjs;
      for(i32 i = 0; i < l.m_straLibSourcePath.get_size(); i++)
      {
         strObjs += " ";
         ::file::path strRel = l.m_straLibSourcePath[i].relative();
         strRel.case_insensitive_ends_eat(".ds");
         strObjs += m_pathTime / "intermediate" / m_pintegrationcontext->m_strPlatform / m_strDynamicSourceConfiguration / m_pmanager->m_strRepos / m_pmanager->m_strNamespace + "_dynamic_source_library/library" / strName;
         //strObjs += m_pathTime.separator();
         strObjs += "/";
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
//      strCmd = dir()->install() / m_strDynamicSourceStage / "front" / m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 +
//#ifdef LINUX
//         ".bash";
//#else
//         ".bat";
//#endif
#ifdef LINUX
      strCmd.format(dir()->install() / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_libl_" + m_pintegrationcontext->m_strPlatform + ".bash");
#else
      strCmd.format(dir()->install() / "operating_system" / "operating_system-" OPERATING_SYSTEM_NAME "\\_stage\\dynamic_source" / m_strDynamicSourceConfiguration + "_libl" + m_pintegrationcontext->m_strPlatform + ".bat");
#endif
      //#else
      // strCmd.format(strFolder, "app\\_stage\\aura\\account\\app\\main\\front\\dynamic_source_libl.bat", false));
      //#endif
      string str = file()->as_string(strCmd);
      str.find_replace("%ITEM_NAME%",::file::path("library")/strName);
      str.find_replace("%ITEM_DIR%","library");
      str.find_replace("%OBJECTS%",strObjs);
      str.find_replace("%NETNODE_ROOT%",strN);
      str.find_replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
      str.find_replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
      //str.find_replace("%DVP%", strDVP_B);

      string strTargetName = l.m_strLibraryPath;
      strTargetName.case_insensitive_ends_eat(".dll");
      str.find_replace("%TARGET_NAME%", strTargetName);
      dir()->create(dir()->install()/ m_strDynamicSourceStage / m_pintegrationcontext->m_strStagePlatform /"library");
//#ifdef LINUX
//      //sleep(2000_ms);
//      strCmd = dir()->install()/m_strDynamicSourceStage/ "front\\libl1.bash";
//#else
//      strCmd = dir()->install()/ m_strDynamicSourceStage / "front\\libl1.bat";
//#endif

      //file()->put_text_utf8(strCmd, str);
      bool bTimeout = false;

      ::operating_system::process_pointer process(e_create, this);

      ::parallelization::set_priority(::e_priority_highest);

      process->create_child_process(str,true,nullptr,::e_priority_highest);
auto tickStart = ::time::now();

      string strLog;

      while(::task_get_run())
      {

         strLog += process->read();

         if (process->has_exited())
         {

            break;

         }

         preempt(100_ms);

         if(tickStart.elapsed() > 890_s) // 14 minutes
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

      strLlog = m_pathTime / strLibRel / "link-log.txt";

      if(!bTimeout && strLog.has_char())
      {

#ifdef LINUX

         //sleep(2000_ms);

#endif

         str = strLog;

         str.trim();

         if(str.has_char())
         {

            file()->put_text_utf8(strLlog,strLog);
            l.m_memfileError << "Linking...\n";
            str.find_replace("\r\n","\n");
            l.m_memfileError << str;
            l.m_memfileError << "</pre>";

         }

         l.m_strError = l.m_memfileError.as_string();

         l.m_strError.trim();

      }

      l.load_library();

      return l;

   }


   void script_compiler::cppize(const ::file::path & lpcszSource,const ::file::path & lpcszDest,ecpptype enum_type)
   {

      dir()->create(lpcszDest.folder());

      cppize1(lpcszSource, lpcszDest, enum_type);

   }


   void script_compiler::cppize1(const ::file::path & lpcszSource,const ::file::path & lpcszDest,ecpptype enum_type)
   {

      string strSource = file()->as_string(lpcszSource);

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
         //   str.case_insensitive_ends_eat(".ds");
         //   strDest += "#include \""+str+".h\"\r\n";
         //}
      }

      strDest += "\r\n";
      strDest += "\r\n";
      strsize iPosId = strDest.length();
      strDest += "\r\n";
      strDest += "\r\n";

      strsize iStart = 0;
      strsize iPos = 0;
      strsize iLastEnd = 0;
      string_array straId;
      while((iPos = strSource.find_index("<?", iStart)) >= 0)
      {
         if(iPos > iLastEnd && bCode)
         {
            strDest += get_ds_print(strSource.substr(iLastEnd, iPos - iLastEnd));
         }
         iLastEnd = strSource.find_index("?>", iPos);
         if(iLastEnd < 0)
            break;
         iLastEnd += 2;
         i32 iShift = 0;
         if(strSource.substr(iPos, 5).case_insensitive_order("<?php") == 0)
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

      string strId;
      for(i32 i = 0; i < straId.get_size(); i++)
      {
         strId += "static ::atom lscript_id" + ::as_string(i) + "(\"" + straId[i] + "\");\r\n";
      }

      strDest = strDest.left(iPosId) + strId + strDest.substr(iPosId);

      //file()->put_text_utf8(lpcszDest, strDest);
      file()->put_text(lpcszDest, strDest);


   }


   void add_var_id(string & strResult, strsize & iArroba, string_array & straId, bool bMakeKeyLower)
   {
      string strKey = strResult.substr(iArroba);
      if(bMakeKeyLower)
      {
         strKey.make_lower();
      }
      auto iFind = straId.find_first(strKey);
      if(::not_found(iFind))
      {
         straId.add(strKey);
         iFind = straId.get_upper_bound();
      }
      strResult = strResult.left(iArroba) + " lscript_id" + as_string(iFind);
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
      strsize iLen = str.length();
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
         if(string_begins(str.substr(i), "bk_filter_active1"))
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
            else if(character_isspace(ch))
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
            else if(character_isspace(ch))
            {
               i++;
               continue;
            }
            else if(ch == '=')
            {
               strResult += ".payloada().add(";
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
                  iServer = strResult.length();
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
                  if(character_isspace(ch))
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
                     //throw ::exception(::exception("invalid syntax."));
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
            if(ansi_char_isdigit(ch) || ansi_char_isalpha(ch) || ch == '_')
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
                  while(ansi_char_isspace(str[i]) && i < iLen)
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
                     while(ansi_char_isspace(str[i]) && i < iLen)
                     {
                        i++;
                     }
                     ch = str[i];
                     string strToken;
                     if(ansi_char_isalpha(ch) || ch == '_')
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
                     while(ansi_char_isdigit(ch) || ansi_char_isalpha(ch) || ch == '_')
                     {
                        strToken += ch;
                        i++;
                        ch = str[i];
                     }
                     ch = str[i];
                     while(ansi_char_isspace(ch))
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
                        while(ansi_char_isspace(ch))
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
               if(ch == '$' && (ansi_char_isalpha(chNext) || chNext == '_'))
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
            iSimpleQuote = strResult.length();
         }
         else if(ch == '@')
         {
            iArroba = strResult.length();
         }
         else if(ch == '_' && chNext == '_' && is_id(&str[i], str.length() - i,  "__ch", 4, iIdLen))
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
         else if(ch == '$' && (ansi_char_isalpha(chNext) || chNext == '_'))
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
                  if(is_id(&str[i + 1], str.length() - i - 1, "_GET", 4,  iIdLen))
                  {
                     strResult += "geta()[";
                     bInVar = false;
                     bServer = true;
                     i += iIdLen + 1;
                  }
                  else if(is_id(&str[i + 1], str.length() - i - 1, "_POST", 5,  iIdLen))
                  {
                     strResult += "posta()[";
                     bInVar = false;
                     bServer = true;
                     i += iIdLen + 1;
                  }
                  else if(is_id(&str[i + 1], str.length() - i - 1, "_REQUEST", 8, iIdLen))
                  {
                     strResult += "requesta()[";
                     bInVar = false;
                     bServer = true;
                     i += iIdLen + 1;
                  }
                  else if(is_id(&str[i + 1], str.length() - i - 1, "_SERVER", 7, iIdLen))
                  {
                     strResult += "inattra()[";
                     bInVar = false;
                     bServer = true;
                     i += iIdLen + 1;
                  }
                  else if(is_id(&str[i + 1], str.length() - i - 1, "_COOKIE", 7, iIdLen))
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
            if(bScript &&str[i-1] != '_' && is_id(&str[i], str.length() - i,  "return", 6,  iIdLen) && next_nonspace(str.substr(i + iIdLen))[0] != ';')
            {
               bInRet = true;
               strResult += "\r\n{\r\nm_varRet = ";
               i += iIdLen - 1;
            }
            else if(is_id(&str[i], str.length() - i,  "include", 7, iIdLen))
            {
               bInSpec1 = true;
               strSpec1 = "include";
               i += iIdLen - 1;
            }
            else if(is_id(&str[i], str.length() - i,   "print", 5,  iIdLen))
            {
               bInSpec1 = true;
               strSpec1 = "print";
               i += iIdLen - 1;
            }
            else if(is_id(&str[i], str.length() - i,  "echo", 4, iIdLen))
            {
               bInSpec1 = true;
               strSpec1 = "echo";
               i += iIdLen - 1;
            }
            else if(str.substr(i, 2) == "[]")
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
               else if(character_isspace(ch))
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


   bool script_compiler::is_id(const ::string & psz, strsize iLen, const ::string & pszId, strsize iIdLen, strsize & iIdLenRet)
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
      if(string_begins(psz, pszId)
            && !isdigit(psz[iIdLen]) && !isalpha(psz[iIdLen]) && psz[iIdLen] != '_')
      {
         iIdLenRet = iIdLen;
         return true;
      }
      return false;
   }


   const char * script_compiler::next_nonspace(const ::string & strParam)
   {

      const ::ansi_character * psz = strParam;

      while(*psz && character_isspace(*psz))
      {

         psz++;

      }

      return psz;

   }


   void script_compiler::run_persistent()
   {

      string strPath = m_pmanager->m_strNetseedDsCa2Path/ "core/persistent";

      ::file::listing stra;

      //auto papp = get_app();

      //auto pcontext = m_pcontext;

      stra.set_listing(strPath, e_depth_recursively);

      dir()->enumerate(stra);

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
         if(string_begins_ci(str, m_pmanager->m_strNetseedDsCa2Path/ "core/persistent")
               && string_ends_ci(str, ".ds"))
         {
            strBody += file()->as_string(str);
         }
      }

      file()->put_text(strCat, strBody);

      string strInclude = strCat;
      
      strInclude.case_insensitive_begins_eat(m_pmanager->m_strNetseedDsCa2Path);
      
      strInclude.case_insensitive_ends_eat(".ds");
      
      ::pointer<script_instance>pinstance = m_pmanager->get(strInclude);

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

               pdsscript->m_pfileError->seek_to_begin();

               string strScriptError;

               strScriptError = pdsscript->m_pfileError->as_string();

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


   bool script_compiler::defer_run_persistent(const ::string &psz)
   {
      string str(psz);

      if(::str::case_insensitive_find("pstr_set", psz) && string_ends_ci(psz, ".txt"))
      {

         parse_pstr_set();

         //string strCat;
         //strCat = m_pmanager->m_strNetseedDsCa2Path/ "aura\\netnode_persistent_ui_str.ds";
         //string strInclude = strCat;
         //strInclude.case_insensitive_begins_eat(m_pmanager->m_strNetseedDsCa2Path);
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
      else if(str.case_insensitive_begins_eat(m_pmanager->m_strNetseedDsCa2Path/ "aura\\persistent")
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

//   for(i32 i = 0; i < m_straLibSourcePath.get_size(); i++)
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

      m_plibraryLib.create(this);

      m_plibraryLib->open(m_strLibraryPath);
      // return;

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
         //memory_set(&m_ftaLibCreation[i], 0, sizeof(FILETIME));
         //memory_set(&m_ftaLibAccess[i], 0, sizeof(FILETIME));
         //memory_set(&m_ftaLibModified[i], 0, sizeof(FILETIME));
         //GetFileTime(h , &m_ftaLibCreation[i], &m_ftaLibAccess[i], &m_ftaLibModified[i]);
         //::CloseHandle(h);

      }

   }


   library::library(::particle * pparticle)
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

   string script_compiler::get_ds_print(const ::string &psz)
   {
      string strSource(psz);
      string strDest;
      while(strSource.length() > 0)
      {
         strsize iLen = minimum(4 * 1024, strSource.length());
         if(strSource.length() > iLen)
         {
            if(strSource[iLen] == '\n')
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

      ::file::listing straFile;

      //auto papp = get_app();

      //auto pcontext = m_pcontext;

      ::file::path pathPstrSet = m_pmanager->m_strNetnodePath / "net/aura/pstr_set";

      if (dir()->is(pathPstrSet))
      {

         straFile.set_listing(pathPstrSet, ::e_depth_recursively);

         dir()->enumerate(straFile);

      }

      for(int i = 0; i < straFile.get_count(); i++)
      {
         string strFile = straFile[i];
         if(::str::case_insensitive_find(".svn",strFile) >= 0 || !string_ends_ci(strFile,".txt"))
            continue;
         strFile = file()->as_string(strFile);
         string_array straLine;
         straLine.explode("\r\n",strFile);
         string strExtra;
         for(int j = 0; j < straLine.get_count(); j++)
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

               infomration("script_compiler::parse_pstr_set");

            }
            catch (const ::exception & )
            {

               infomration("script_compiler::parse_pstr_set");

            }
            catch(...)
            {

            }

         }

      }

   }


   void script_compiler::pstr_set(atom pszTopic,atom idLocale,atom idSchema, const ::string & psz)
   {

      synchronous_lock synchronouslock(m_pmanager->synchronization());

      auto psystem = acmesystem()->m_paurasystem;

      psystem->texttable()->set(pszTopic,idLocale,idSchema,psz);

   }


} // namespace dynamic_source





