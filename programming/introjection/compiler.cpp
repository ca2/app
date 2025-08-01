#include "framework.h"
#include "compiler.h"
#include "library.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/library.h"
#include "acme/platform/system.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "acme/prototype/string/str.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"

#include "acme/_operating_system.h"

#include <sys/stat.h>


#ifdef LINUX
//#include <unistd.h>
int create_process(const ::scoped_string & scopedstrCommandLine, int * pprocessId);
#elif defined(MACOS)
#include <unistd.h>
#endif

string vs_build(::particle * pparticle)
{

   ::file::path path;

   auto pdirectorysystem = pparticle->directory_system();

   path = pdirectorysystem->config() / "programming/vs_build.txt";

   string strVsBuild = pparticle->file_system()->as_string(path);

   strVsBuild.trim();

   return strVsBuild;

}

#if defined(LINUX)
#include <ctype.h>
#endif


//unsigned int RunSilent(const ::scoped_string & scopedstrFunct, const ::scoped_string & scopedstrstrParams);


namespace introjection
{



   compiler::compiler()
   {

      defer_create_synchronization();


   }


   compiler::~compiler()
   {

   }


   void compiler::initialize_introjection_compiler(::particle * pparticle, const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp, const ::scoped_string & scopedstrProjectName, const ::file::path & pathProjectDir)
   {

      //auto estatus =
      
      initialize_programming_compiler(pparticle, pathProjectDir);

      //if (!estatus)
      //{

      //   return estatus;

      //}

//      // auto pcontext = get_context();
//
//#ifdef WINDOWS
//      {
//
//         ::file::path path;
//
//         auto pdirectorysystem = directory_system();
//
//         path = pdirectorysystem->config() / "programming/vs.txt";
//
//         m_strVs = file()->as_string(path);
//
//         m_strVs.trim();
//
//         if (m_strVs == "2015")
//         {
//
//            m_strVsTools = "140";
//
//         }
//         else if (m_strVs == "2017")
//         {
//
//            m_strVsTools = "141";
//
//         }
//         else if (m_strVs == "2019")
//         {
//
//            m_strVsTools = "142";
//
//         }
//         else if (m_strVs == "2022")
//         {
//
//            m_strVsTools = "143";
//
//         }
//         else
//         {
//
//            string strMessage;
//
//            strMessage = "There is a hole here. You should fill it with fullfillment. Missing f**k " + path;
//
//            //message_box(strMessage, strMessage, e_message_box_ok);
//
//         }
//
//      }
//
//#endif
//
//      ::file::path path;
//
//      path = THIS_FILE;
//
//      m_pathProjectFolder = path.folder();
//
//#if MEMDLEAK
//
//      m_strDynamicSourceConfiguration = "basis";
//      m_strDynamicSourceStage = "time";
//
//
//#elif defined(_DEBUG)
//
//      m_strDynamicSourceConfiguration = "basis";
//      m_strDynamicSourceStage = "time-" OPERATING_SYSTEM_NAME;
//
//#else
//
//      m_strDynamicSourceConfiguration = "profiler";
//      m_strDynamicSourceStage = "profiler";
//
//#endif
//
//      m_strDynamicSourceStageFolder = m_pintegrationcontext->m_pathBuildFolder / m_strDynamicSourceStage;
//

      m_strRepos = scopedstrRepos;

      m_strApp = scopedstrApp;

      m_strProjectName = scopedstrProjectName;

      prepare_compile_and_link_environment();


      //return estatus;

   }


   //void compiler::initialize_compiler(const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp, const ::scoped_string & scopedstrProjectName)
   //{

   //   m_strRepos = pszRepos;

   //   m_strApp = pszApp;

   //   m_strProjectName = pszProjectName;

   //   prepare_compile_and_link_environment();

   //}


//   void compiler::prepare_compile_and_link_environment()
//   {
//
//      //auto papp = get_app();
//
//      // auto pcontext = get_context();
//
//      auto pdirectorysystem = directory_system();
//
//      directory()->create(pdirectorysystem->system() / "introjection\\symbols");
//
//      ::file::path strVars;
//
//#ifndef UNIVERSAL_WINDOWS
//#ifdef WINDOWS_DESKTOP
//
//      if (m_strVs == "2015")
//      {
//
//         strVars = getenv("VS140COMNTOOLS");
//
//      }
//#endif
//#endif
//
//#ifdef WINDOWS_DESKTOP
//
//      if (m_strVs == "2019")
//      {
//
//         m_strContext = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvarsall.bat";
//
//         ::acme_windows::registry::key key;
//
//         if (key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\VisualStudio\\SxS\\VS7", false))
//         {
//
//            string strPath;
//
//            if (key._get("16.0", strPath))
//            {
//
//               ::file::path path = strPath;
//
//               m_strContext = path / "VC/Auxiliary/Build/vcvarsall.bat";
//
//            }
//
//         }
//
//         ::pointer<application>papp = get_app();
//
//         m_strVCVersion = papp->get_visual_studio_build();
//
//      }
//      else if (m_strVs == "2017")
//      {
//
//         m_strContext = "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvarsall.bat";
//
//         ::acme_windows::registry::key key;
//
//         if (key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\VisualStudio\\SxS\\VS7", false))
//         {
//
//            string strPath;
//
//            if (key._get("15.0", strPath))
//            {
//
//               ::file::path path = strPath;
//
//               m_strContext = path / "VC/Auxiliary/Build/vcvarsall.bat";
//
//            }
//
//         }
//
//         ::pointer<application>papp = get_app();
//
//         m_strVCVersion = papp->get_visual_studio_build();
//
//      }
//      else if (m_strVs == "2015")
//      {
//
//         m_strContext = strVars.up(2);
//         m_strContext = m_strContext / "vc\\vcvarsall.bat";
//         //m_strContext = ".\\vc_vars.bat";
//
//      }
//
//      m_strTime = m_pintegrationcontext->m_pathBuildFolder / "time";
//
//      //m_strContext = "C:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Bin\\SetEnv.cmd";
//
//      //m_strSdk1 = "windows7.1sdk";
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
//#ifdef LINUX
//      m_strPlat1     = "64";
//      m_strPlatform = "x64";
//      m_strStagePlatform = "x64";
//      m_strLibPlatform = "x64/";
//#else
//      m_strPlat1     = "64";
//      m_strPlat2 = "x86_amd64";
//      //m_strPlat2 = "amd64";
//      m_strPlatform = "x64";
//      m_strStagePlatform = "x64";
//      m_strLibPlatform = "x64/";
//#endif
//#else
//      m_strPlat1     = "32";
//      m_strPlat2 = " x86";
//      m_strPlatform = "Win32";
//      m_strStagePlatform = "x86";
//      m_strLibPlatform = "x86/";
//#endif
//
//      //file()->lines(m_straSync, "C:\\aura\\database\\text\\introjection\\syncer.txt", get_app());
//#if defined(LINUX)
//      prepare1(m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash",
//               m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash");
//      prepare1(m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash",
//               m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash");
//      prepare1(m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 + ".bash",
//               m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 + ".bash");
//#else
//      prepare1(m_strPlat1,m_strPlat1);
//      //prepare1(m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bat",
//      //   m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bat");
//      //prepare1(m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bat",
//      //   m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bat");
//      //prepare1(m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bat",
//      //   m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bat");
//#endif
//
//      directory()->create(m_pintegrationcontext->m_pathBuildFolder / m_strDynamicSourceStage / "front");
//
//      //#ifdef WINDOWS
//      //      string vars1batSrc;
//      //      string vars2batSrc;
//      //      string vars1batDst;
//      //      string vars2batDst;
//      //      vars1batSrc = m_pintegrationcontext->m_pathBuildFolder/"platform/stage/introjection/vc_vars.bat";
//      //      vars2batSrc = m_pintegrationcontext->m_pathBuildFolder/"platform/stage/introjection/vc_vars_query_registry.bat";
//      //      vars1batDst = m_pintegrationcontext->m_pathBuildFolder/ m_strDynamicSourceStage / "front"/"vc_vars.bat";
//      //      vars2batDst = m_pintegrationcontext->m_pathBuildFolder/m_strDynamicSourceStage /"front"/"vc_vars_query_registry.bat";
//      //      try
//      //      {
//      //         file()->copy(vars1batDst, vars1batSrc, false);
//      //      }
//      //      catch(...)
//      //      {
//      //      }
//      //      try
//      //      {
//      //         file()->copy(vars2batDst, vars2batSrc, false);
//      //      }
//      //      catch(...)
//      //      {
//      //      }
//      //
//      //#endif
//
//      auto psystem = system();
//
//#ifdef UNIVERSAL_WINDOWS
//
//      throw ::exception(todo);
//
//#elif defined(LINUX)
//
//#else
//
//      //string strCommandLine = "\"" + m_strContext + "\" " + m_strPlat2 + " "10.0.16299.0";
//
//      string strCommandLine = "\"" + m_strContext + "\" " + m_strPlat2 + " " + vs_build(this);
//
//      ::payload payload = psystem->process().get_output(strCommandLine);
//
//      informationf("%s", payload.string().c_str());
//
//#endif
//
//      string str;
//      string strItem;
//
//      strItem = m_pintegrationcontext->m_pathBuildFolder / m_strDynamicSourceStage / m_strStagePlatform;
//      str = str + strItem + ";";
//
//      strItem = m_pintegrationcontext->m_pathBuildFolder / m_strDynamicSourceStage / m_strStagePlatform / "introjection\\library";
//      str = str + strItem + ";";
//
//      //auto psystem = system();
//
//      auto pnode = psystem->node();
//
//      str += pnode->get_environment_variable("PATH");
//
//      bool bResult = false;
//#ifdef WINDOWS_DESKTOP
//      //bResult = SetEnvironmentVariable("PATH",str) != false;
//#elif defined(UNIVERSAL_WINDOWS)
//
//      throw ::exception(todo);
//
//#elif defined(LINUX)
//#else
//      bResult = setenv("PATH",str,true);
//#endif
//
//      informationf("compiler::prepare_compile_and_link_environment SetEnvironmentVariable return bool " << bResult);
//
//
//   }


//   void compiler::prepare1(const ::scoped_string & scopedstrSource, const ::scoped_string & scopedstrDest)
//   {
//
//      //auto papp = get_app();
//
//#ifdef WINDOWS
//      //sleep(15000_ms);
//
//      ::pointer<application>papp = get_app();
//
//      string strBuildCmd = m_strContext;
//
//      if (m_strVs == "2015")
//      {
//
//         strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2;
//
//      }
//      else if (m_strVs >= "2017")
//      {
//
//         strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + papp->get_visual_studio_build();
//
//      }
//
//      ::operating_system::process_pointer process(e_create, this);
//
//      ::file::path pathEnvTxt;
//
//      auto pdirectorysystem = directory_system();
//
//      pathEnvTxt = pdirectorysystem->system() / "env.txt";
//
//      file_system()->put_contents(pdirectorysystem->system() / "env1.bat", pdirectorysystem->system() / "env.bat > \"" + pathEnvTxt + "\"");
//
//      file_system()->put_contents(pdirectorysystem->system() / "env.bat","@call " + strBuildCmd + "\r\n@set");
//
//      auto psystem = system();
//
//      auto pnode = psystem->node();
//
//      pnode->run_silent(pdirectorysystem->system() / "env1.bat","");
//
//      string strLog;
//
//      strLog = file_system()->as_string(pdirectorysystem->system() / "env.txt");
//
//      string_array stra;
//
//      stra.add_lines(strLog);
//
//      //sleep(10000_ms);
//
//#ifdef WINDOWS_DESKTOP
//
//
//      ::property_set setEnvironment;
//
//      setEnvironment.parse_environment_variable(stra);
//
//      for (auto & pproperty : setEnvironment)
//      {
//
//         informationf("%s : %s", pproperty->id().to_string().c_str(), pproperty->string().c_str());
//
//         SetEnvironmentVariableW(wstring(pproperty->id()), wstring(pproperty->string()));
//
//      }
//
//
//
//#endif
//#endif
//
//      // auto pcontext = get_context();
//
//      ::file::path strFolder;
//
//      strFolder = m_pintegrationcontext->m_pathBuildFolder;
//      if(!string_ends(strFolder,"/") && !string_ends(strFolder,"\\"))
//         strFolder += "/";
//      string strTemplate;
//      string strSource = "platform/time/dynamic_source/";
//      strSource += lpcszSource;
//
//      ::file::path pathN = m_pathProjectFolder;
//      pathN -= 3;
//      string strN = pathN;
//      strN.find_replace("\\", "/");
//      strN += "/";
//
//
//      //#ifdef _DEBUG
//      strTemplate = strFolder / strSource;
//      //#else
//      // strTemplate = strFolder, "app/time/aura/account/app/main/matter/dynamic_source_cl.bat", false);
//      //#endif
//      string str;
//      str = file()->as_string(strTemplate);
//      /*string strVars = getenv("VS100COMNTOOLS");
//      file()->path().eat_end_level(strVars, 2, "/");
//      strVars += "vc/bin/vcvars32.bat";*/
//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//
//      string strV(m_pintegrationcontext->m_pathBuildFolder);
//      strV.find_replace("\\","/");
//      if(!string_ends(strV,"/") && !string_ends(strV,"\\"))
//         strV += "/";
//      str.find_replace("%CA2_ROOT%",strV);
//      str.find_replace("%PROJECT_DIR%", m_pathProjectFolder);
//      str.find_replace("%NETNODE_ROOT%",strN);
//      str.find_replace("%SDK1%",m_strSdk1);
//      string strDest = m_strDynamicSourceStage / "front" / lpcszDest;
//      ::file::path strCmd;
//      //#ifdef _DEBUG
//      strCmd = strFolder / strDest;
//      //#else
//      // strCmd = strFolder, "app\\time\\aura\\account\\app\\main\\front\\dynamic_source_cl.bat", false);
//      //#endif
//      directory()->create(strCmd.folder());
//      //file()->put_text_utf8(strCmd, str);
//      file()->put_contents(strCmd,str);
//      directory()->create(m_strTime / "dynamic_source");
//
//   }


   ::acme::library * compiler::compile(const ::file::path & pathFile,bool bNew)
   {

      if (m_strApp.is_empty())
      {

         throw ::exception(error_failed, "call compiler::initialize");

      }

      synchronous_lock slCompiler(synchronization());

      auto & plibrary = m_lib[pathFile];

      if(!plibrary)
      {

         plibrary = __create_new < library > ();

         plibrary->defer_create_synchronization();

      }
      else if(!bNew)
//         if(get_file_time(strFilePath) == lib->m_filetime)
      {

//          bNew = false;

         return plibrary->m_plibrary;

      }

      single_lock synchronouslock(plibrary->synchronization());

      if (!synchronouslock.lock(0_s))
      {

         synchronouslock.lock();

         if (plibrary->m_plibrary.is_set())
         {

            return plibrary->m_plibrary;

         }

      }

      slCompiler.unlock();

      plibrary->m_plibrary->close();

      bNew = true;

      plibrary->m_filetimeset = get_file_time_set(pathFile);

      ::file::path strName(pathFile);

      plibrary->m_pathScript = strName;

#ifdef WINDOWS

      strName.find_replace("/","\\");

#endif

      string str;

      ::file::path strClog;

      ::file::path strLlog;

      ::file::path strScript;

      strScript = strName.title();

      ::file::path strTransformName = strName;

      if(file()->exists(strName))
      {

         strTransformName.find_replace(":","");

         strTransformName.case_insensitive_ends_eat(".cpp");

      }
      else
      {

         return plibrary->m_plibrary;

      }

      string strLibTitle = plibrary->m_pathScript.title();

#ifdef MACOS

      string strCmd;
      string strLCmd;
      string strDCmd;
      string strPreLinkScript;

      strCmd = ::file::path(pathFile).folder() / "build_bot";

      string strTargetPath;
      string strSrcName = ::file::path(pathFile).title();
      string strLogName = ::file::path(strCmd).title();
      strTargetPath =  directory()->module() / "lib" + strSrcName;
      string strDsymPath = (directory()->module().folder(3)) /  "lib" + strSrcName;
      string strDdPath = directory()->module().folder(7);
      string strBuildFolderPath = directory()->module().folder(5);
      string strSrcFolder = ::file::path(pathFile).folder();
      string strFramework = m_strFramework;
      strClog = strCmd + "-osxc.txt";
      strLlog = strCmd + "-osxl.txt";
      strLCmd = strCmd + "-osxl";
      strPreLinkScript = strCmd + "-osxprelink";
      strDCmd = strCmd + "-osxd";
      string strLfl = strCmd + "-osx";
      strCmd += "-osxc";

      {

         string str2 = file()->as_string(strLfl+".LinkFileList");
         str2.find_replace("%TARGET_PATH%", strTargetPath);
         str2.find_replace("%DSYM_PATH%", strDsymPath);
         str2.find_replace("%DERIVED_DATA%", strDdPath);
         str2.find_replace("%FRAMEWORK%", strFramework);
         str2.find_replace("%BUILD_FOLDER%", strBuildFolderPath);
         str2.find_replace("%SRC_FOLDER%", strSrcFolder);
         str2.find_replace("%SRC_NAME%", strSrcName);
         file()->put_text(strLfl + "2.LinkFileList", str2);

      }

               auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->create("/var/tmp/ca2/intermediate");

#else

      string strCmd;

      strCmd = pathFile.folder() / "build_bot";
      string strCmdCompile;
      string strCmdLink;
      strCmdCompile = strCmd + "-win-compile.bat";
      strCmdLink = strCmd + "-win-link.bat";

      //strName.find_replace("/", "\\");
      //string strFolder;
      //strFolder = m_pintegrationcontext->m_pathBuildFolder;
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
      ::file::path strObj;


      /*string strScript(strName);
      strScript.find_replace("\\", ",");
      strScript.find_replace("/", ",");
      strScript = "ca2" + m_pmanager->m_strNamespace + "_script." + strScript;*/

      ::file::path strSourceDir;
      strSourceDir = strName.folder();

      //if(!file()->exists(lib->m_strSourcePath))
      //{
      //   lib->m_memfileError << "<pre>";
      //   str.formatf("Source File : \"%s\" does not exist",lib->m_strSourcePath);
      //   lib->m_memfileError << str;
      //   lib->m_memfileError << "</pre>";
      //   return;
      //}


      //      string strTime = m_strTime;


      string strCppPath;

      //strCppPath = lib->m_pathScript;



      strClog = plibrary->m_pathScript.folder() / "build_" + plibrary->m_pathScript.title() + "-compile-log.log";
      strLlog = plibrary->m_pathScript.folder() / "build_" + plibrary->m_pathScript.title() + "-link-log.log";
      ::file::path strDynamicSourceScriptFolder = m_strTime / "intermediate" / m_pintegrationcontext->m_strPlatform / m_strDynamicSourceConfiguration / string("introjection");

      //#ifdef _DEBUG
#ifdef LINUX
      strO = strDynamicSourceScriptFolder / strTransformName.name() / strTransformName + ".bash";
      strObj = strDynamicSourceScriptFolder / strTransformName / strTransformName.name() + ".o";
#else
      //strB = m_strDynamicSourceStageFolder / "front\\introjection\\BuildBat" / strTransformName.name() / strTransformName + ".bat";
      strP = m_strDynamicSourceStageFolder / m_pintegrationcontext->m_strPlatform / "introjection" / strTransformName.sibling(strScript.name()) + ".pdb";
      strL = m_strDynamicSourceStageFolder / m_pintegrationcontext->m_strPlatform / "introjection" / strTransformName.sibling(strScript.name()) + ".lib";
      strE = m_strDynamicSourceStageFolder / m_pintegrationcontext->m_strPlatform / "introjection" / strTransformName.sibling(strScript.name()) + ".exp";
      //strCppPath = m_strDynamicSourceStageFolder / "introjection" / strTransformName.sibling(strScript.name()) + ".cpp";
      strCppPath = strName;

      //strDVI = strDynamicSourceScriptFolder / strTransformName / m_strSdk1 + ".idb";
      strDVP = strDynamicSourceScriptFolder / strTransformName / m_pintegrationcontext->payload("sdk1").as_string() + ".pdb";
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
      //lib->m_strBuildBat = strB;
      //m_pathScript = m_pmanager->get_script_path(strName);
      //#else
      // lib->m_strLibraryPath.formatf(directory()->install(m_strDynamicSourceStage /" Release\\%s.dll"), strName);
      //#endif

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
      //::DeleteFile(lib->m_strBuildBat);
      //try
      //{
      //   if(file()->exists(lib->m_pathScript + ".old"))
      //   {
      //      file()->del(lib->m_pathScript + ".old");
      //   }
      //}
      //catch(const ::scoped_string & scopedstrError)
      //{
      //   TRACE0(strError + "\n");
      //}
      try
      {
         //if(file()->exists(lib->m_pathScript))
         //{
         //   file()->copy(strCppPath,lib->m_pathScript);
         //}
      }
      catch(const ::scoped_string & scopedstrError)
      {

         information(scopedstrError + "\n");

      }
      //try
      //{
      //   if(file()->exists(lib->m_pathScript + ".old"))
      //   {
      //      file()->del(lib->m_pathScript + ".old");
      //   }
      //}
      //catch(const ::scoped_string & scopedstrError)
      //{
      //   TRACE0(strError + "\n");
      //}
#ifndef LINUX

      //      directory()->create(strDVI.folder());
      //      directory()->create(lib->m_strBuildBat.folder());
      //try
      //{
      //   //         file()->copy(strDVI, strSVI, false);
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   file()->copy(strDVP, strSVP, false);
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   file()->copy(strDPC, strSPC, false);
      //}
      //catch(...)
      //{

      //   lib->m_bHasTempOsError = true;

      //   return;

      //}
      //try
      //{
      //   file()->copy(strDO1,strSO1,false);
      //}
      //catch(...)
      //{

      //   lib->m_bHasTempOsError = true;

      //   return;

      //}
      //try
      //{
      //   file()->copy(strDO2,strSO2,false);
      //}
      //catch(...)
      //{

      //   lib->m_bHasTempOsError = true;

      //   return;

      //}




#endif

      directory()->create(plibrary->m_pathScript.folder());
      directory()->create(strL.folder());
      directory()->create(m_strTime / "intermediate" / m_pintegrationcontext->m_strPlatform / m_strDynamicSourceConfiguration /  m_strRepos / m_strProjectName / strTransformName);

      ::file::path pathN = m_pintegrationcontext->m_pathProjectFolder;

      pathN -= 3;

      string strN = pathN;

      strN.find_replace("\\", "/");

      strN += "/";

      string strBuildCmd;

#if defined(LINUX) || defined(__BSD__)
      strBuildCmd = m_pintegrationcontext->m_pathBuildFolder / "operating_system/operating_system-linux/stage/_introjection" / m_strApp / (m_strDynamicSourceConfiguration + "_c" + m_pintegrationcontext->m_strPlatform + ".bash");
#elif defined(__APPLE__)
      strBuildCmd.formatf(m_pintegrationcontext->m_pathBuildFolder / "operating_system/operating_system-macos/_stage/introjection" / m_strApp / (m_strDynamicSourceConfiguration + "_c" + m_pintegrationcontext->m_strPlatform + ".bat"));
#else
      strBuildCmd.formatf(m_pintegrationcontext->m_pathBuildFolder / "operating_system/operating_system-windows/_stage/introjection" / m_strApp / m_pintegrationcontext->payload("vstools").as_string() / (m_strDynamicSourceConfiguration + "_c_" + m_pintegrationcontext->m_strPlatform + ".bat"));
#endif

      str = file()->as_string(strBuildCmd);
      str.find_replace("%SOURCE%",::str::find_replace("\\","/",string(strName)));
      str.find_replace("%ITEM_NAME%",::str::find_replace("\\","/",string(strTransformName)));
      str.find_replace("%ITEM_TITLE%",strTransformName.name());
      str.find_replace("%ITEM_DIR%",::str::find_replace("\\","/",string(strTransformName.folder())) + "/");
      str.find_replace("%LIBS_LIBS%",m_strLibsLibs);
      auto pathInstall = m_pintegrationcontext->m_pathBuildFolder;
      str.find_replace("%CA2_ROOT%", ::string(pathInstall) + "/");

      m_pintegrationcontext->prepare_compilation_script(str);

      string strElem = m_pintegrationcontext->m_pathBuildFolder;

      strElem.find_replace("\\","/");

      strElem += "/";
      string strHmhLctvWildPdbPath;
      string strRndTitle;

      auto pmathematics = this->mathematics();

      strRndTitle = pmathematics->random_alphanumeric(64);

      ///strRndTitle.release_buffer();

      auto pdirectorysystem = directory_system();

      strHmhLctvWildPdbPath = ::file::path(pdirectorysystem->userconfig() / "netnode_desktop\\symbols") / strRndTitle;
      strHmhLctvWildPdbPath.find_replace("\\","/");
      directory()->create(::file::path(strHmhLctvWildPdbPath).folder());
      str.find_replace("%HMH_LCTVWILD_PDB_PATH%",strHmhLctvWildPdbPath);

      str.find_replace("%CA2_ROOT%",strElem);
      str.find_replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
      str.find_replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);


      m_pintegrationcontext->prepare_compilation_script(str);

      string strT2 = plibrary->m_pathScript;
      strT2.find_replace("\\",".");
      strT2.find_replace("/",".");
      strT2.find_replace(":","_");

      ::file::path pathOutputFolder;
      
      pathOutputFolder = 
         (strElem 
            + "time-windows/intermediate/" 
            + m_pintegrationcontext->m_strPlatform + "/"
            + m_strDynamicSourceConfiguration 
            + "/app-core/resident_resident_desktop/" 
            + strTransformName);

      directory()->create(pathOutputFolder);


#if defined(LINUX) || defined(__BSD__)

      string strTargetPath =  m_pintegrationcontext->m_pathBuildFolder /"time" / m_pintegrationcontext->m_strPlatform / m_strDynamicSourceConfiguration / plibrary->m_pathScript.title();
      strTargetPath.case_insensitive_ends_eat(".cpp");
      strTargetPath.case_insensitive_ends_eat(".so");

#else

      string strTargetPath = m_pintegrationcontext->m_pathBuildFolder / "time-windows" / m_pintegrationcontext->m_strPlatform / m_strDynamicSourceConfiguration / strT2 ;
      strTargetPath.case_insensitive_ends_eat(".cpp");
      strTargetPath.case_insensitive_ends_eat(".dll");

      ::SetThreadUILanguage((LANGID)65001);


#endif

      strTargetPath += "-"+strRndTitle;

      str.find_replace("%TARGET_PATH%",strTargetPath);

      ::operating_system::process_pointer process(e_create, this);

#ifdef LINUX

      file_system()->put_contents("/tmp/introj.bash", str);

      chmod("/tmp/introj.bash", S_IRWXU | S_IRWXG | S_IRWXO);

      process->create_child_process("/tmp/introj.bash",true,nullptr,::e_priority_highest);

#else

      str.trim();

      file()->put_text(strCmdCompile, str);

      process->create_child_process(str,true,m_pintegrationcontext->m_pathProjectFolder,::e_priority_highest);

#endif

#endif

      string strLog;

      bool bTimeout = false;

#ifdef MACOS

      {

         ::chdir(strSrcFolder);
         strSrcFolder.trim();
         strSrcFolder.find_replace(" ", "\\ ");
         strBuildFolderPath.trim();
         strBuildFolderPath.find_replace(" ", "\\ ");
         strTargetPath.trim();
         strTargetPath.find_replace(" ", "\\ ");
         string str2 = file()->as_string(strCmd);
         str2.find_replace("%TARGET_PATH%", strTargetPath);
         str2.find_replace("%DSYM_PATH%", strDsymPath);
         str2.find_replace("%DERIVED_DATA%", strDdPath);
         str2.find_replace("%FRAMEWORK%", strFramework);
         str2.find_replace("%BUILD_FOLDER%", strBuildFolderPath);
         str2.find_replace("%SRC_FOLDER%", strSrcFolder);
         str2.find_replace("%SRC_NAME%", strSrcName);
         str2.find_replace("%LOG_NAME%", strLogName);
         file()->put_text(strCmd + "2", str2);

         ::system(str2);

      }

      strLog= file_system()->as_string(strClog);

#else
auto tickStart = ::time::now();

      while(::task_get_run())
      {

         strLog += process->read();

         if (process->has_exited())
         {

            break;

         }

         preempt(100_ms);

         if(tickStart.elapsed() > 15_min)
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

#endif




#ifdef LINUX
      if(!bTimeout)
#else
      if(!bTimeout && strLog.has_character())
#endif
      {

#ifdef LINUX

         //sleep(2000_ms);

#endif

         str = strLog;

         str.trim();

         if(str.has_character())
         {
#ifndef MACOS
            file()->put_text_utf8(strClog,strLog);
#endif
            plibrary->m_memfileError << "<pre>";

            plibrary->m_memfileError << "Compiling...\n";
            plibrary->m_memfileError << plibrary->m_pathScript;
            plibrary->m_memfileError << "\n";
            if(bTimeout)
            {
               plibrary->m_memfileError << "error: Timeout during compilation (If there are the compilation or link errors about the file \"" + plibrary->m_pathScript + "\" following this message, they may be out-of-date)";
            }
            str.find_replace("\r\n","\n");
            plibrary->m_memfileError << str;

         }

         string strBuildCmd;

#ifndef MACOS

#if defined(LINUX) || defined(__BSD__)
         strBuildCmd.formatf(m_pintegrationcontext->m_pathBuildFolder / "operating_system/operating_system-linux/_stage/introjection" / m_strApp / (m_strDynamicSourceConfiguration + "_l" + m_pintegrationcontext->m_strPlatform + ".bash"));
#else
         strBuildCmd.formatf(m_pintegrationcontext->m_pathBuildFolder / "operating_system/operating_system-windows/_stage/introjection" / m_strApp / m_pintegrationcontext->payload("vstools").as_string() / (m_strDynamicSourceConfiguration + "_l_" + m_pintegrationcontext->m_strPlatform + ".bat"));
#endif

         str = file()->as_string(strBuildCmd);


         str.find_replace("%ITEM_NAME%",::str::find_replace("\\","/",string(strTransformName)));
         str.find_replace("%ITEM_TITLE%",strTransformName.name());
         str.find_replace("%ITEM_DIR%",::str::find_replace("\\","/",string(strTransformName.folder())) + "/");
         str.find_replace("%LIBS_LIBS%",m_strLibsLibs);
         str.find_replace("%HMH_LCTVWILD_PDB_PATH%",strHmhLctvWildPdbPath);

//         auto pathInstall = m_pintegrationcontext->m_pathBuildFolder;
         str.find_replace("%CA2_ROOT%", ::string(pathInstall) + "/");

         //str.find_replace("%CA2_ROOT%",strElem);
         str.find_replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
         str.find_replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);


         m_pintegrationcontext->prepare_linking_script(str);

         //string strTargetPath = lib->m_pathScript;
         //strTargetPath.find_replace("\\",".");
         //strTargetPath.find_replace("/",".");
         //strTargetPath.case_insensitive_ends_eat(".cpp");
         //#ifdef LINUX
         //         strTargetPath.case_insensitive_ends_eat(".so");
         //#else
         //         strTargetPath.case_insensitive_ends_eat(".dll");
         //#endif
         //         strTargetPath = m_pintegrationcontext->m_pathBuildFolder /
         str.find_replace("%TARGET_PATH%",strTargetPath);

         file()->put_text(strCmdLink, str);
         //strBuildCmd = lib->m_strBuildBat;
         //file()->put_text_utf8(strBuildCmd, str);

         //file()->put_contents(strBuildCmd,str);

         //str.find_replace("\\", "/");

         bTimeout = false;

         ::operating_system::process_pointer process(e_create, this);

         //         set_thread_priority(::e_priority_highest);

#ifdef LINUX

         file_system()->put_contents("/tmp/introl.bash", str);

         chmod("/tmp/introl.bash", S_IRWXU | S_IRWXG | S_IRWXO);

         process->create_child_process("/tmp/introl.bash",true,nullptr,::e_priority_highest);

#else

         process->create_child_process(str,true, m_pintegrationcontext->m_pathProjectFolder,::e_priority_highest);
#endif
#else

         {

            string str2 = file()->as_string(strPreLinkScript);
            str2.find_replace("%TARGET_PATH%", strTargetPath);
            str2.find_replace("%DSYM_PATH%", strDsymPath);
            str2.find_replace("%DERIVED_DATA%", strDdPath);
            str2.find_replace("%FRAMEWORK%", strFramework);
            str2.find_replace("%BUILD_FOLDER%", strBuildFolderPath);
            str2.find_replace("%SRC_FOLDER%", strSrcFolder);
            str2.find_replace("%SRC_NAME%", strSrcName);
            str2.find_replace("%LOG_NAME%", strLogName);
            file()->put_text(strPreLinkScript + "2", str2);

            ::chmod(strPreLinkScript + "2", 0755);

            string strFileNameCmd = strPreLinkScript;

            strFileNameCmd.find_replace(" ", "\\ ");

            ::system(strFileNameCmd + "2 &> " + strFileNameCmd + ".txt");

         }

         {

            string str2 = file()->as_string(strLCmd);
            str2.find_replace("%TARGET_PATH%", strTargetPath);
            str2.find_replace("%DSYM_PATH%", strDsymPath);
            str2.find_replace("%DERIVED_DATA%", strDdPath);
            str2.find_replace("%FRAMEWORK%", strFramework);
            str2.find_replace("%BUILD_FOLDER%", strBuildFolderPath);
            str2.find_replace("%SRC_FOLDER%", strSrcFolder);
            str2.find_replace("%SRC_NAME%", strSrcName);
            str2.find_replace("%LOG_NAME%", strLogName);
            file()->put_text(strLCmd + "2", str2);
            //::system(strLCmd + "2");
            ::system(str2);

            if(!case_insensitive_string_begins(directory()->module(), "/Applications/"))
            {
               string str2 = file()->as_string(strDCmd);
               str2.find_replace("%TARGET_PATH%", strTargetPath);
               str2.find_replace("%DSYM_PATH%", strDsymPath);
               str2.find_replace("%DERIVED_DATA%", strDdPath);
               str2.find_replace("%FRAMEWORK%", strFramework);
               str2.find_replace("%BUILD_FOLDER%", strBuildFolderPath);
               str2.find_replace("%SRC_FOLDER%", strSrcFolder);
               str2.find_replace("%SRC_NAME%", strSrcName);
               str2.find_replace("%LOG_NAME%", strLogName);
               file()->put_text(strDCmd + "2", str2);
               //              ::system(strDCmd + "2");
               ::system(str2);
            }

         }

#endif

         string strLog;

#ifdef MACOS

         strLog= file_system()->as_string(strLlog);

#else

         while(true)
         {

            strLog += process->read();

            if(process->has_exited())
               break;

            preempt(100_ms);

            if(tickStart.elapsed() > 15_min)
            {

               bTimeout = true;

               break;

            }

         }

         strLog += process->read();

#endif

         if(!bTimeout && strLog.has_character())
         {

#ifdef LINUX

            //sleep(2000_ms);

#endif


            str = strLog;

            str.trim();

            if(str.has_character())
            {

#ifndef MACOS

               file()->put_text_utf8(strLlog,strLog);

#endif

               plibrary->m_memfileError << "Linking...\n";
               str.find_replace("\r\n","\n");
               plibrary->m_memfileError << str;
               plibrary->m_memfileError << "</pre>";


            }

            plibrary->m_strError = plibrary->m_memfileError.as_string();

            plibrary->m_strError.trim();

         }

      }

#ifndef LINUX

#ifndef MACOS

      try
      {

         file()->erase(strDVP);

      }
      catch(...)
      {

      }

#endif

#endif

      strTargetPath.find_replace("\\ ", " ");

      plibrary->m_plibrary->open(strTargetPath);

      //if(!plibrary->m_plibrary->open(strTargetPath))
      //{

      //   output_error_message("Failed to open bot library (1)\n\n" + plibrary->m_plibrary->m_strMessage);

      //}

      //if(!plibrary->m_plibrary->open_library(strLibTitle))
      //{

      //   output_error_message("Failed to open bot library (2)\n\n" + plibrary->m_plibrary->m_strMessage);

      //}

      return plibrary->m_plibrary;

   }

}



