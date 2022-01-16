#include "framework.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/primitive/mathematics/mathematics.h"
#ifdef WINDOWS_DESKTOP
#include "acme_windows/_.h"
#include "acme_windows/_acme_windows.h"
#endif
#include "acme/filesystem/filesystem/acme_dir.h"


#include <sys/stat.h>

#ifdef LINUX
i32 create_process(const ::string & pszCommandLine, i32 * pprocessId);
#endif

string vs_build(::object * pobject)
{

   ::file::path path;

   auto pacmedir = pobject->m_psystem->m_pacmedir;

   path = pacmedir->config() / "programming/vs_build.txt";

   string strVsBuild = pobject->m_psystem->m_pacmefile->as_string(path);

   strVsBuild.trim();

   return strVsBuild;

}

#if defined(LINUX)
#include <ctype.h>
#endif


//::u32 RunSilent(const ::string & strFunct, const ::string & strstrParams);


namespace introjection
{



   compiler::compiler()
   {

      defer_create_mutex();


   }


   compiler::~compiler()
   {

   }


   void compiler::initialize_introjection_compiler(::object * pobject, const ::string& pszRepos, const ::string& pszApp, const ::string& pszProjectName)
   {

      auto estatus = initialize_programming_compiler(pobject);

      if (!estatus)
      {

         return estatus;

      }

//      auto pcontext = get_context();
//
//#ifdef WINDOWS
//      {
//
//         ::file::path path;
//
//         auto pacmedir = m_psystem->m_pacmedir;
//
//         path = pacmedir->config() / "programming/vs.txt";
//
//         m_strVs = pcontext->m_papexcontext->file().as_string(path);
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
//      m_pathProjectDir = path.folder();
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
//      m_strDynamicSourceStage = "time-" PLATFORM_NAME;
//
//#else
//
//      m_strDynamicSourceConfiguration = "profiler";
//      m_strDynamicSourceStage = "profiler";
//
//#endif
//
//      m_strDynamicSourceStageFolder = pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage;
//

      m_strRepos = pszRepos;

      m_strApp = pszApp;

      m_strProjectName = pszProjectName;

      prepare_compile_and_link_environment();


      return estatus;

   }


   //void compiler::initialize_compiler(const ::string & pszRepos, const ::string & pszApp, const ::string & pszProjectName)
   //{

   //   m_strRepos = pszRepos;

   //   m_strApp = pszApp;

   //   m_strProjectName = pszProjectName;

   //   prepare_compile_and_link_environment();

   //}


//   void compiler::prepare_compile_and_link_environment()
//   {
//
//      //auto papplication = get_application();
//
//      auto pcontext = get_context();
//
//      auto pacmedir = m_psystem->m_pacmedir;
//
//      pcontext->m_papexcontext->dir().create(pacmedir->system() / "introjection\\symbols");
//
//      ::file::path strVars;
//
//#ifndef _UWP
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
//         m_strEnv = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvarsall.bat";
//
//         ::windows::registry::key key;
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
//               m_strEnv = path / "VC/Auxiliary/Build/vcvarsall.bat";
//
//            }
//
//         }
//
//         __pointer(application) papplication = get_application();
//
//         m_strVCVersion = papplication->get_visual_studio_build();
//
//      }
//      else if (m_strVs == "2017")
//      {
//
//         m_strEnv = "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvarsall.bat";
//
//         ::windows::registry::key key;
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
//               m_strEnv = path / "VC/Auxiliary/Build/vcvarsall.bat";
//
//            }
//
//         }
//
//         __pointer(application) papplication = get_application();
//
//         m_strVCVersion = papplication->get_visual_studio_build();
//
//      }
//      else if (m_strVs == "2015")
//      {
//
//         m_strEnv = strVars.up(2);
//         m_strEnv = m_strEnv / "vc\\vcvarsall.bat";
//         //m_strEnv = ".\\vc_vars.bat";
//
//      }
//
//      m_strTime = pcontext->m_papexcontext->dir().install() / "time";
//
//      //m_strEnv = "C:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Bin\\SetEnv.cmd";
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
//      //pcontext->m_papexcontext->file().lines(m_straSync, "C:\\aura\\database\\text\\introjection\\syncer.txt", get_application());
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
//      pcontext->m_papexcontext->dir().create(pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage / "front");
//
//      //#ifdef WINDOWS
//      //      string vars1batSrc;
//      //      string vars2batSrc;
//      //      string vars1batDst;
//      //      string vars2batDst;
//      //      vars1batSrc = pcontext->m_papexcontext->dir().install()/"platform/stage/introjection/vc_vars.bat";
//      //      vars2batSrc = pcontext->m_papexcontext->dir().install()/"platform/stage/introjection/vc_vars_query_registry.bat";
//      //      vars1batDst = pcontext->m_papexcontext->dir().install()/ m_strDynamicSourceStage / "front"/"vc_vars.bat";
//      //      vars2batDst = pcontext->m_papexcontext->dir().install()/m_strDynamicSourceStage /"front"/"vc_vars_query_registry.bat";
//      //      try
//      //      {
//      //         pcontext->m_papexcontext->file().copy(vars1batDst, vars1batSrc, false);
//      //      }
//      //      catch(...)
//      //      {
//      //      }
//      //      try
//      //      {
//      //         pcontext->m_papexcontext->file().copy(vars2batDst, vars2batSrc, false);
//      //      }
//      //      catch(...)
//      //      {
//      //      }
//      //
//      //#endif
//
//      auto psystem = m_psystem->m_paurasystem;
//
//#ifdef _UWP
//
//      __throw(todo);
//
//#elif defined(LINUX)
//
//#else
//
//      //string strCommandLine = "\"" + m_strEnv + "\" " + m_strPlat2 + " "10.0.16299.0";
//
//      string strCommandLine = "\"" + m_strEnv + "\" " + m_strPlat2 + " " + vs_build(this);
//
//      ::payload payload = psystem->process().get_output(strCommandLine);
//
//      FORMATTED_TRACE("%s", payload.string().c_str());
//
//#endif
//
//      string str;
//      string strItem;
//
//      strItem = pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage / m_strStagePlatform;
//      str = str + strItem + ";";
//
//      strItem = pcontext->m_papexcontext->dir().install() / m_strDynamicSourceStage / m_strStagePlatform / "introjection\\library";
//      str = str + strItem + ";";
//
//      //auto psystem = m_psystem;
//
//      auto pnode = psystem->node();
//
//      str += pnode->get_environment_variable("PATH");
//
//      bool bResult = false;
//#ifdef WINDOWS_DESKTOP
//      //bResult = SetEnvironmentVariable("PATH",str) != false;
//#elif defined(_UWP)
//
//      __throw(todo);
//
//#elif defined(LINUX)
//#else
//      bResult = setenv("PATH",str,true);
//#endif
//
//      TRACE("compiler::prepare_compile_and_link_environment SetEnvironmentVariable return bool " << bResult);
//
//
//   }


//   void compiler::prepare1(const ::string & lpcszSource, const ::string & lpcszDest)
//   {
//
//      //auto papplication = get_application();
//
//#ifdef WINDOWS
//      //sleep(15000_ms);
//
//      __pointer(application) papplication = get_application();
//
//      string strBuildCmd = m_strEnv;
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
//         strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + papplication->get_visual_studio_build();
//
//      }
//
//      ::operating_system::process_pointer process(e_create, this);
//
//      ::file::path pathEnvTxt;
//
//      auto pacmedir = m_psystem->m_pacmedir;
//
//      pathEnvTxt = pacmedir->system() / "env.txt";
//
//      m_psystem->m_pacmefile->put_contents(pacmedir->system() / "env1.bat", pacmedir->system() / "env.bat > \"" + pathEnvTxt + "\"");
//
//      m_psystem->m_pacmefile->put_contents(pacmedir->system() / "env.bat","@call " + strBuildCmd + "\r\n@set");
//
//      auto psystem = m_psystem;
//
//      auto pnode = psystem->node();
//
//      pnode->run_silent(pacmedir->system() / "env1.bat","");
//
//      string strLog;
//
//      strLog = m_psystem->m_pacmefile->as_string(pacmedir->system() / "env.txt");
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
//      property_set setEnvironment;
//
//      setEnvironment.parse_environment_variable(stra);
//
//      for (auto & pproperty : setEnvironment)
//      {
//
//         FORMATTED_TRACE("%s : %s", pproperty->m_id.to_string().c_str(), pproperty->string().c_str());
//
//         SetEnvironmentVariableW(wstring(pproperty->m_id), wstring(pproperty->string()));
//
//      }
//
//
//
//#endif
//#endif
//
//      auto pcontext = get_context();
//
//      ::file::path strFolder;
//
//      strFolder = pcontext->m_papexcontext->dir().install();
//      if(!::str::ends(strFolder,"/") && !::str::ends(strFolder,"\\"))
//         strFolder += "/";
//      string strTemplate;
//      string strSource = "platform/time/dynamic_source/";
//      strSource += lpcszSource;
//
//      ::file::path pathN = m_pathProjectDir;
//      pathN -= 3;
//      string strN = pathN;
//      strN.replace("\\", "/");
//      strN += "/";
//
//
//      //#ifdef _DEBUG
//      strTemplate = strFolder / strSource;
//      //#else
//      // strTemplate = strFolder, "app/time/aura/account/app/main/matter/dynamic_source_cl.bat", false);
//      //#endif
//      string str;
//      str = pcontext->m_papexcontext->file().as_string(strTemplate);
//      /*string strVars = getenv("VS100COMNTOOLS");
//      pcontext->m_papexcontext->file().path().eat_end_level(strVars, 2, "/");
//      strVars += "vc/bin/vcvars32.bat";*/
//      str.replace("%VS_VARS%",m_strEnv);
//      str.replace("%VS_VARS_PLAT2%",m_strPlat2);
//
//      string strV(pcontext->m_papexcontext->dir().install());
//      strV.replace("\\","/");
//      if(!::str::ends(strV,"/") && !::str::ends(strV,"\\"))
//         strV += "/";
//      str.replace("%CA2_ROOT%",strV);
//      str.replace("%PROJECT_DIR%", m_pathProjectDir);
//      str.replace("%NETNODE_ROOT%",strN);
//      str.replace("%SDK1%",m_strSdk1);
//      string strDest = m_strDynamicSourceStage / "front" / lpcszDest;
//      ::file::path strCmd;
//      //#ifdef _DEBUG
//      strCmd = strFolder / strDest;
//      //#else
//      // strCmd = strFolder, "app\\time\\aura\\account\\app\\main\\front\\dynamic_source_cl.bat", false);
//      //#endif
//      pcontext->m_papexcontext->dir().create(strCmd.folder());
//      //pcontext->m_papexcontext->file().put_text_utf8(strCmd, str);
//      pcontext->m_papexcontext->file().put_contents(strCmd,str);
//      pcontext->m_papexcontext->dir().create(m_strTime / "dynamic_source");
//
//   }


   ::acme::library * compiler::compile(const ::file::path & pathFile,bool bNew)
   {

      if (m_strApp.is_empty())
      {

         throw ::exception(error_failed, "call compiler::initialize");

      }

      synchronous_lock slCompiler(mutex());

      auto & plibrary = m_lib[pathFile];

      if(!plibrary)
      {

         plibrary = __create_new < library > ();

         plibrary->defer_create_mutex();

      }
      else if(!bNew)
//         if(get_filetime(strFilePath) == lib->m_filetime)
      {

//          bNew = false;

         return plibrary->m_plibrary;

      }

      single_lock synchronouslock(plibrary->mutex());

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

      plibrary->m_filetimeset = get_filetime_set(pathFile);

      ::file::path strName(pathFile);

      plibrary->m_pathScript = strName;

#ifdef WINDOWS

      strName.replace("/","\\");

#endif

      string str;

      ::file::path strClog;

      ::file::path strLlog;

      ::file::path strScript;

      strScript = strName.title();

      ::file::path strTransformName = strName;

      auto pcontext = get_context();

      if(pcontext->m_papexcontext->file().exists(strName))
      {

         strTransformName.replace(":","");

         ::str::ends_eat_ci(strTransformName,".cpp");

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
      strTargetPath =  pcontext->m_papexcontext->dir().module() / "lib" + strSrcName;
      string strDsymPath = (pcontext->m_papexcontext->dir().module().folder(3)) /  "lib" + strSrcName;
      string strDdPath = pcontext->m_papexcontext->dir().module().folder(7);
      string strBuildFolderPath = pcontext->m_papexcontext->dir().module().folder(5);
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

         string str2 = pcontext->m_papexcontext->file().as_string(strLfl+".LinkFileList");
         str2.replace("%TARGET_PATH%", strTargetPath);
         str2.replace("%DSYM_PATH%", strDsymPath);
         str2.replace("%DERIVED_DATA%", strDdPath);
         str2.replace("%FRAMEWORK%", strFramework);
         str2.replace("%BUILD_FOLDER%", strBuildFolderPath);
         str2.replace("%SRC_FOLDER%", strSrcFolder);
         str2.replace("%SRC_NAME%", strSrcName);
         pcontext->m_papexcontext->file().put_text(strLfl + "2.LinkFileList", str2);

      }

               auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->create("/var/tmp/ca2/intermediate");

#else

      string strCmd;

      strCmd = pathFile.folder() / "build_bot";
      string strCmdCompile;
      string strCmdLink;
      strCmdCompile = strCmd + "-win-compile.bat";
      strCmdLink = strCmd + "-win-link.bat";

      //strName.replace("/", "\\");
      //string strFolder;
      //strFolder = pcontext->m_papexcontext->dir().install();
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
      strScript.replace("\\", ",");
      strScript.replace("/", ",");
      strScript = "ca2" + m_pmanager->m_strNamespace + "_script." + strScript;*/

      ::file::path strSourceDir;
      strSourceDir = strName.folder();

      //if(!pcontext->m_papexcontext->file().exists(lib->m_strSourcePath))
      //{
      //   lib->m_memfileError << "<pre>";
      //   str.format("Source File : \"%s\" does not exist",lib->m_strSourcePath);
      //   lib->m_memfileError << str;
      //   lib->m_memfileError << "</pre>";
      //   return;
      //}


      //      string strTime = m_strTime;


      string strCppPath;

      //strCppPath = lib->m_pathScript;



      strClog = plibrary->m_pathScript.folder() / "build_" + plibrary->m_pathScript.title() + "-compile-log.log";
      strLlog = plibrary->m_pathScript.folder() / "build_" + plibrary->m_pathScript.title() + "-link-log.log";
      ::file::path strDynamicSourceScriptFolder = m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration / string("introjection");

      //#ifdef _DEBUG
#ifdef LINUX
      strO = strDynamicSourceScriptFolder / strTransformName.name() / strTransformName + ".bash";
      strObj = strDynamicSourceScriptFolder / strTransformName / strTransformName.name() + ".o";
#else
      //strB = m_strDynamicSourceStageFolder / "front\\introjection\\BuildBat" / strTransformName.name() / strTransformName + ".bat";
      strP = m_strDynamicSourceStageFolder / m_strStagePlatform / "introjection" / strTransformName.sibling(strScript.name()) + ".pdb";
      strL = m_strDynamicSourceStageFolder / m_strStagePlatform / "introjection" / strTransformName.sibling(strScript.name()) + ".lib";
      strE = m_strDynamicSourceStageFolder / m_strStagePlatform / "introjection" / strTransformName.sibling(strScript.name()) + ".exp";
      //strCppPath = m_strDynamicSourceStageFolder / "introjection" / strTransformName.sibling(strScript.name()) + ".cpp";
      strCppPath = strName;

      //strDVI = strDynamicSourceScriptFolder / strTransformName / m_strSdk1 + ".idb";
      strDVP = strDynamicSourceScriptFolder / strTransformName / m_strSdk1 + ".pdb";
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
      // lib->m_strLibraryPath.format(pcontext->m_papexcontext->dir().install(m_strDynamicSourceStage /" Release\\%s.dll"), strName);
      //#endif

      try
      {
         if(pcontext->m_papexcontext->file().exists(strO))
         {
            pcontext->m_papexcontext->file().del(strO);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(pcontext->m_papexcontext->file().exists(strObj))
         {
            pcontext->m_papexcontext->file().del(strObj);
         }
      }
      catch(...)
      {
      }
#ifndef LINUX
      try
      {
         if(pcontext->m_papexcontext->file().exists(strP))
         {
            pcontext->m_papexcontext->file().del(strP);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(pcontext->m_papexcontext->file().exists(strL))
         {
            pcontext->m_papexcontext->file().del(strL);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(pcontext->m_papexcontext->file().exists(strE))
         {
            pcontext->m_papexcontext->file().del(strE);
         }
      }
      catch(...)
      {
      }
      //try
      //{
      //   if(pcontext->m_papexcontext->file().exists(strDPC))
      //   {
      //      pcontext->m_papexcontext->file().del(strDPC);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(pcontext->m_papexcontext->file().exists(strDVP))
      //   {
      //      pcontext->m_papexcontext->file().del(strDVP);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(pcontext->m_papexcontext->file().exists(strDVI))
      //   {
      //      pcontext->m_papexcontext->file().del(strDVI);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(pcontext->m_papexcontext->file().exists(strDO1))
      //   {
      //      pcontext->m_papexcontext->file().del(strDO1);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(pcontext->m_papexcontext->file().exists(strDO2))
      //   {
      //      pcontext->m_papexcontext->file().del(strDO2);
      //   }
      //}
      //catch(...)
      //{
      //}
#endif
      try
      {
         if(pcontext->m_papexcontext->file().exists(strClog))
         {
            pcontext->m_papexcontext->file().del(strClog);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(pcontext->m_papexcontext->file().exists(strLlog))
         {
            pcontext->m_papexcontext->file().del(strLlog);
         }
      }
      catch(...)
      {
      }
      //::DeleteFile(lib->m_strBuildBat);
      //try
      //{
      //   if(pcontext->m_papexcontext->file().exists(lib->m_pathScript + ".old"))
      //   {
      //      pcontext->m_papexcontext->file().del(lib->m_pathScript + ".old");
      //   }
      //}
      //catch(string strError)
      //{
      //   TRACE0(strError + "\n");
      //}
      try
      {
         //if(pcontext->m_papexcontext->file().exists(lib->m_pathScript))
         //{
         //   pcontext->m_papexcontext->file().copy(strCppPath,lib->m_pathScript);
         //}
      }
      catch(string strError)
      {

         FORMATTED_TRACE("%s", (strError + "\n").c_str());

      }
      //try
      //{
      //   if(pcontext->m_papexcontext->file().exists(lib->m_pathScript + ".old"))
      //   {
      //      pcontext->m_papexcontext->file().del(lib->m_pathScript + ".old");
      //   }
      //}
      //catch(string strError)
      //{
      //   TRACE0(strError + "\n");
      //}
#ifndef LINUX

      //      pcontext->m_papexcontext->dir().create(strDVI.folder());
      //      pcontext->m_papexcontext->dir().create(lib->m_strBuildBat.folder());
      //try
      //{
      //   //         pcontext->m_papexcontext->file().copy(strDVI, strSVI, false);
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   pcontext->m_papexcontext->file().copy(strDVP, strSVP, false);
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   pcontext->m_papexcontext->file().copy(strDPC, strSPC, false);
      //}
      //catch(...)
      //{

      //   lib->m_bHasTempOsError = true;

      //   return;

      //}
      //try
      //{
      //   pcontext->m_papexcontext->file().copy(strDO1,strSO1,false);
      //}
      //catch(...)
      //{

      //   lib->m_bHasTempOsError = true;

      //   return;

      //}
      //try
      //{
      //   pcontext->m_papexcontext->file().copy(strDO2,strSO2,false);
      //}
      //catch(...)
      //{

      //   lib->m_bHasTempOsError = true;

      //   return;

      //}




#endif

      pcontext->m_papexcontext->dir().create(plibrary->m_pathScript.folder());
      pcontext->m_papexcontext->dir().create(strL.folder());
      pcontext->m_papexcontext->dir().create(m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration /  m_strRepos / m_strProjectName / strTransformName);

      ::file::path pathN = m_pathProjectDir;

      pathN -= 3;

      string strN = pathN;

      strN.replace("\\", "/");

      strN += "/";

      string strBuildCmd;

#ifdef LINUX
      strBuildCmd = pcontext->m_papexcontext->dir().install() / "archive/platform-linux/stage/_introjection" / m_strApp / (m_strDynamicSourceConfiguration + "_c" + m_strPlat1 + ".bash");
#elif defined(__APPLE__)
      strBuildCmd.format(pcontext->m_papexcontext->dir().install() / "archive/platform-macos/_stage/introjection" / m_strApp / (m_strDynamicSourceConfiguration + "_c" + m_strPlat1 + ".bat"));
#else
      strBuildCmd.format(pcontext->m_papexcontext->dir().install() / "archive/platform-windows/_stage/introjection" / m_strApp / m_strVsTools / (m_strDynamicSourceConfiguration + "_c" + m_strPlat1 + ".bat"));
#endif

      str = pcontext->m_papexcontext->file().as_string(strBuildCmd);
      str.replace("%SOURCE%",::str::replace("\\","/",string(strName)));
      str.replace("%ITEM_NAME%",::str::replace("\\","/",string(strTransformName)));
      str.replace("%ITEM_TITLE%",strTransformName.name());
      str.replace("%ITEM_DIR%",::str::replace("\\","/",string(strTransformName.folder())) + "/");
      str.replace("%LIBS_LIBS%",m_strLibsLibs);
      str.replace("%VS_VARS%",m_strEnv);
      str.replace("%VS_VARS_PLAT2%",m_strPlat2);

      string strElem = pcontext->m_papexcontext->dir().install();

      strElem.replace("\\","/");

      strElem += "/";
      string strHmhLctvWildPdbPath;
      string strRndTitle;

      auto pmathematics = ::mathematics::mathematics();

      pmathematics->gen_rand_alnum(strRndTitle.get_string_buffer(64),64);

      strRndTitle.release_string_buffer();

      auto pacmedir = m_psystem->m_pacmedir;

      strHmhLctvWildPdbPath = ::file::path(pacmedir->system() / "netnodelite\\symbols") / strRndTitle;
      strHmhLctvWildPdbPath.replace("\\","/");
      pcontext->m_papexcontext->dir().create(::file::path(strHmhLctvWildPdbPath).folder());
      str.replace("%HMH_LCTVWILD_PDB_PATH%",strHmhLctvWildPdbPath);

      str.replace("%CA2_ROOT%",strElem);
      str.replace("%PROJECT_DIR%", m_pathProjectDir);
      str.replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
      str.replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
      str.replace("%PLATFORM%",m_strPlatform);
      str.replace("%STAGEPLATFORM%",m_strStagePlatform);

      str.replace("%SDK1%",m_strSdk1);
      string strT2 = plibrary->m_pathScript;
      strT2.replace("\\",".");
      strT2.replace("/",".");
      strT2.replace(":","_");

      ::file::path pathOutputFolder;
      
      pathOutputFolder = 
         (strElem 
            + "time-windows/intermediate/" 
            + m_strPlatform + "/"
            + m_strDynamicSourceConfiguration 
            + "/app-core/app_core_resident_desktop/" 
            + strTransformName);

      m_pcontext->m_papexcontext->dir().create(pathOutputFolder);
      

#ifdef LINUX

      string strTargetPath =  pcontext->m_papexcontext->dir().install() /"time" / m_strPlatform / m_strDynamicSourceConfiguration / plibrary->m_pathScript.title();
      ::str::ends_eat_ci(strTargetPath,".cpp");
      ::str::ends_eat_ci(strTargetPath,".so");

#else

      string strTargetPath = pcontext->m_papexcontext->dir().install() / "time-windows" / m_strPlatform / m_strDynamicSourceConfiguration / strT2 ;
      ::str::ends_eat_ci(strTargetPath, ".cpp");
      ::str::ends_eat_ci(strTargetPath,".dll");

#endif

      strTargetPath += "-"+strRndTitle;

      str.replace("%TARGET_PATH%",strTargetPath);

      ::operating_system::process_pointer process(e_create, this);

#ifdef LINUX

      m_psystem->m_pacmefile->put_contents("/tmp/introj.bash", str);

      chmod("/tmp/introj.bash", S_IRWXU | S_IRWXG | S_IRWXO);

      process->create_child_process("/tmp/introj.bash",true,nullptr,::e_priority_highest);

#else

      str.trim();

      pcontext->m_papexcontext->file().put_text(strCmdCompile, str);

      process->create_child_process(str,true,m_pathProjectDir,::e_priority_highest);

#endif

#endif

      string strLog;

      bool bTimeout = false;

#ifdef MACOS

      {

         ::chdir(strSrcFolder);
         strSrcFolder.trim();
         strSrcFolder.replace(" ", "\\ ");
         strBuildFolderPath.trim();
         strBuildFolderPath.replace(" ", "\\ ");
         strTargetPath.trim();
         strTargetPath.replace(" ", "\\ ");
         string str2 = pcontext->m_papexcontext->file().as_string(strCmd);
         str2.replace("%TARGET_PATH%", strTargetPath);
         str2.replace("%DSYM_PATH%", strDsymPath);
         str2.replace("%DERIVED_DATA%", strDdPath);
         str2.replace("%FRAMEWORK%", strFramework);
         str2.replace("%BUILD_FOLDER%", strBuildFolderPath);
         str2.replace("%SRC_FOLDER%", strSrcFolder);
         str2.replace("%SRC_NAME%", strSrcName);
         str2.replace("%LOG_NAME%", strLogName);
         pcontext->m_papexcontext->file().put_text(strCmd + "2", str2);

         ::system(str2);

      }

      strLog= m_psystem->m_pacmefile->as_string(strClog);

#else
auto tickStart = ::duration::now();

      while(::task_get_run())
      {

         strLog += process->read();

         if (process->has_exited())
         {

            break;

         }

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

#endif




#ifdef LINUX
      if(!bTimeout)
#else
      if(!bTimeout && strLog.has_char())
#endif
      {

#ifdef LINUX

         //sleep(2000_ms);

#endif

         str = strLog;

         str.trim();

         if(str.has_char())
         {
#ifndef MACOS
            pcontext->m_papexcontext->file().put_text_utf8(strClog,strLog);
#endif
            plibrary->m_memfileError << "<pre>";

            plibrary->m_memfileError << "Compiling...\n";
            plibrary->m_memfileError << plibrary->m_pathScript;
            plibrary->m_memfileError << "\n";
            if(bTimeout)
            {
               plibrary->m_memfileError << "error: Timeout during compilation (If there are the compilation or link errors about the file \"" + plibrary->m_pathScript + "\" following this message, they may be out-of-date)";
            }
            str.replace("\r\n","\n");
            plibrary->m_memfileError << str;

         }

         string strBuildCmd;

#ifndef MACOS

#ifdef LINUX
         strBuildCmd.format(pcontext->m_papexcontext->dir().install() / "archive/platform-linux/_stage/introjection" / m_strApp / (m_strDynamicSourceConfiguration + "_l" + m_strPlat1 + ".bash"));
#else
         strBuildCmd.format(pcontext->m_papexcontext->dir().install() / "archive/platform-windows/_stage/introjection" / m_strApp / m_strVsTools / (m_strDynamicSourceConfiguration + "_l" + m_strPlat1 + ".bat"));
#endif

         str = pcontext->m_papexcontext->file().as_string(strBuildCmd);


         str.replace("%ITEM_NAME%",::str::replace("\\","/",string(strTransformName)));
         str.replace("%ITEM_TITLE%",strTransformName.name());
         str.replace("%ITEM_DIR%",::str::replace("\\","/",string(strTransformName.folder())) + "/");
         str.replace("%LIBS_LIBS%",m_strLibsLibs);
         str.replace("%VS_VARS%",m_strEnv);
         str.replace("%VS_VARS_PLAT2%",m_strPlat2);
         str.replace("%HMH_LCTVWILD_PDB_PATH%",strHmhLctvWildPdbPath);

         str.replace("%CA2_ROOT%",strElem);
         str.replace("%PROJECT_DIR%", m_pathProjectDir);
         str.replace("%CONFIGURATION_NAME%",m_strDynamicSourceConfiguration);
         str.replace("%CONFIGURATION%",m_strDynamicSourceConfiguration);
         str.replace("%PLATFORM%",m_strPlatform);
         str.replace("%STAGEPLATFORM%",m_strStagePlatform);
         //      str.replace("%LIBPLATFORM%", m_strLibPlatform);
         str.replace("%SDK1%",m_strSdk1);
         //string strTargetPath = lib->m_pathScript;
         //strTargetPath.replace("\\",".");
         //strTargetPath.replace("/",".");
         //::str::ends_eat_ci(strTargetPath,".cpp");
         //#ifdef LINUX
         //         ::str::ends_eat_ci(strTargetPath,".so");
         //#else
         //         ::str::ends_eat_ci(strTargetPath,".dll");
         //#endif
         //         strTargetPath = pcontext->m_papexcontext->dir().install() /
         str.replace("%TARGET_PATH%",strTargetPath);

         pcontext->m_papexcontext->file().put_text(strCmdLink, str);
         //strBuildCmd = lib->m_strBuildBat;
         //pcontext->m_papexcontext->file().put_text_utf8(strBuildCmd, str);

         //pcontext->m_papexcontext->file().put_contents(strBuildCmd,str);

         //str.replace("\\", "/");

         bTimeout = false;

         ::operating_system::process_pointer process(e_create, this);

         //         set_thread_priority(::e_priority_highest);

#ifdef LINUX

         m_psystem->m_pacmefile->put_contents("/tmp/introl.bash", str);

         chmod("/tmp/introl.bash", S_IRWXU | S_IRWXG | S_IRWXO);

         process->create_child_process("/tmp/introl.bash",true,nullptr,::e_priority_highest);

#else

         process->create_child_process(str,true, m_pathProjectDir,::e_priority_highest);
#endif
#else

         {

            string str2 = pcontext->m_papexcontext->file().as_string(strPreLinkScript);
            str2.replace("%TARGET_PATH%", strTargetPath);
            str2.replace("%DSYM_PATH%", strDsymPath);
            str2.replace("%DERIVED_DATA%", strDdPath);
            str2.replace("%FRAMEWORK%", strFramework);
            str2.replace("%BUILD_FOLDER%", strBuildFolderPath);
            str2.replace("%SRC_FOLDER%", strSrcFolder);
            str2.replace("%SRC_NAME%", strSrcName);
            str2.replace("%LOG_NAME%", strLogName);
            pcontext->m_papexcontext->file().put_text(strPreLinkScript + "2", str2);

            ::chmod(strPreLinkScript + "2", 0755);

            string strFileNameCmd = strPreLinkScript;

            strFileNameCmd.replace(" ", "\\ ");

            ::system(strFileNameCmd + "2 &> " + strFileNameCmd + ".txt");

         }

         {

            string str2 = pcontext->m_papexcontext->file().as_string(strLCmd);
            str2.replace("%TARGET_PATH%", strTargetPath);
            str2.replace("%DSYM_PATH%", strDsymPath);
            str2.replace("%DERIVED_DATA%", strDdPath);
            str2.replace("%FRAMEWORK%", strFramework);
            str2.replace("%BUILD_FOLDER%", strBuildFolderPath);
            str2.replace("%SRC_FOLDER%", strSrcFolder);
            str2.replace("%SRC_NAME%", strSrcName);
            str2.replace("%LOG_NAME%", strLogName);
            pcontext->m_papexcontext->file().put_text(strLCmd + "2", str2);
            //::system(strLCmd + "2");
            ::system(str2);

            if(!::str::begins_ci(pcontext->m_papexcontext->dir().module(), "/Applications/"))
            {
               string str2 = pcontext->m_papexcontext->file().as_string(strDCmd);
               str2.replace("%TARGET_PATH%", strTargetPath);
               str2.replace("%DSYM_PATH%", strDsymPath);
               str2.replace("%DERIVED_DATA%", strDdPath);
               str2.replace("%FRAMEWORK%", strFramework);
               str2.replace("%BUILD_FOLDER%", strBuildFolderPath);
               str2.replace("%SRC_FOLDER%", strSrcFolder);
               str2.replace("%SRC_NAME%", strSrcName);
               str2.replace("%LOG_NAME%", strLogName);
               pcontext->m_papexcontext->file().put_text(strDCmd + "2", str2);
               //              ::system(strDCmd + "2");
               ::system(str2);
            }

         }

#endif

         string strLog;

#ifdef MACOS

         strLog= m_psystem->m_pacmefile->as_string(strLlog);

#else

         while(true)
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

#endif

         if(!bTimeout && strLog.has_char())
         {

#ifdef LINUX

            //sleep(2000_ms);

#endif


            str = strLog;

            str.trim();

            if(str.has_char())
            {

#ifndef MACOS

               pcontext->m_papexcontext->file().put_text_utf8(strLlog,strLog);

#endif

               plibrary->m_memfileError << "Linking...\n";
               str.replace("\r\n","\n");
               plibrary->m_memfileError << str;
               plibrary->m_memfileError << "</pre>";


            }

            plibrary->m_strError = plibrary->m_memfileError;

            plibrary->m_strError.trim();

         }

      }

#ifndef LINUX

#ifndef MACOS

      try
      {

         pcontext->m_papexcontext->file().del(strDVP);

      }
      catch(...)
      {

      }

#endif

#endif

      strTargetPath.replace("\\ ", " ");

      if(!plibrary->m_plibrary->open(strTargetPath))
      {

         output_error_message("Failed to open bot library (1)\n\n" + plibrary->m_plibrary->m_strMessage);

      }

      //if(!plibrary->m_plibrary->open_library(strLibTitle))
      //{

      //   output_error_message("Failed to open bot library (2)\n\n" + plibrary->m_plibrary->m_strMessage);

      //}

      return plibrary->m_plibrary;

   }

}



