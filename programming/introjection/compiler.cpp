#include "framework.h"
#include "core/programming/_.h"
#ifdef WINDOWS_DESKTOP
#include "aura/node/windows/registry.h"
#endif

#include <sys/stat.h>

#ifdef LINUX
i32 create_process(const char * pszCommandLine, i32 * pprocessId);
#endif

string vs_build()
{

   ::file::path path;

   path = ::dir::config() / "programming/vs_build.txt";

   string strVsBuild = file_as_string(path);

   strVsBuild.trim();

   return strVsBuild;

}

#if defined(LINUX)
#include <ctype.h>
#endif


DWORD RunSilent(const char* strFunct, char* strstrParams);


namespace introjection
{


   library::library(::object * pobject):
      object(pobject),
      m_plibrary(__new(::aura::library()))
   {

      defer_create_mutex();

      xxf_zero(m_filetime);

   }


   library::~library()
   {


   }


   compiler::compiler()
   {

      defer_create_mutex();


   }


   compiler::~compiler()
   {

   }


   ::estatus compiler::initialize(::object* pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

#ifdef WINDOWS
      {

         ::file::path path;

         path = ::dir::config() / "programming/vs.txt";

         m_strVs = Context.file().as_string(path);

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

            os_message_box(nullptr, strMessage, strMessage, MB_OK);

         }

      }

#endif

      ::file::path path;

      path = THIS_FILE;

      m_pathProjectDir = path.folder();

#if MEMDLEAK

      m_strDynamicSourceConfiguration = "basis";
      m_strDynamicSourceStage = "time";


#elif defined(_DEBUG)

      m_strDynamicSourceConfiguration = "basis";
      m_strDynamicSourceStage = "time-" __PLATFORM;

#else

      m_strDynamicSourceConfiguration = "profiler";
      m_strDynamicSourceStage = "profiler";

#endif

      m_strDynamicSourceStageFolder = Context.dir().install() / m_strDynamicSourceStage;


      return estatus;

   }


   void compiler::initialize_compiler(const char * pszRepos, const char * pszApp, const char * pszProjectName)
   {

      m_strRepos = pszRepos;

      m_strApp = pszApp;

      m_strProjectName = pszProjectName;

      prepare_compile_and_link_environment();

   }


   void compiler::prepare_compile_and_link_environment()
   {

      Context.dir().mk(::dir::system() / "introjection\\symbols");

      ::file::path strVars;

#ifndef _UWP
#ifdef WINDOWS_DESKTOP

      if (m_strVs == "2015")
      {

         strVars = getenv("VS140COMNTOOLS");

      }
#endif
#endif


#ifdef WINDOWS_DESKTOP

      if (m_strVs == "2019")
      {

         m_strEnv = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvarsall.bat";

         ::windows::registry::key key;

         if (key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\VisualStudio\\SxS\\VS7", false))
         {

            string strPath;

            if (key._get("16.0", strPath))
            {

               ::file::path path = strPath;

               m_strEnv = path / "VC/Auxiliary/Build/vcvarsall.bat";

            }

         }

         m_strVCVersion = Application.get_visual_studio_build();

      }
      else if (m_strVs == "2017")
      {

         m_strEnv = "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvarsall.bat";

         ::windows::registry::key key;

         if (key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\VisualStudio\\SxS\\VS7", false))
         {

            string strPath;

            if (key._get("15.0", strPath))
            {

               ::file::path path = strPath;

               m_strEnv = path / "VC/Auxiliary/Build/vcvarsall.bat";

            }

         }

         m_strVCVersion = Application.get_visual_studio_build();

      }
      else if (m_strVs == "2015")
      {

         m_strEnv = strVars.up(2);
         m_strEnv = m_strEnv / "vc\\vcvarsall.bat";
         //m_strEnv = ".\\vc_vars.bat";

      }

      m_strTime = Context.dir().install() / "time";

      //m_strEnv = "C:\\Program Files\\Microsoft SDKs\\Windows\\v7.1\\Bin\\SetEnv.cmd";

      //m_strSdk1 = "windows7.1sdk";
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
      m_strPlatform = "x64";
      m_strStagePlatform = "x64";
      m_strLibPlatform = "x64/";
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

      //Context.file().lines(m_straSync, "C:\\aura\\database\\text\\introjection\\syncer.txt", get_context_application());
#if defined(LINUX)
      prepare1(m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash",
               m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash");
      prepare1(m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash",
               m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash");
      prepare1(m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 + ".bash",
               m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 + ".bash");
#else
      prepare1(m_strPlat1,m_strPlat1);
      //prepare1(m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bat",
      //   m_strDynamicSourceConfiguration  + "_cl" + m_strPlat1 + ".bat");
      //prepare1(m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bat",
      //   m_strDynamicSourceConfiguration  + "_libc" + m_strPlat1 + ".bat");
      //prepare1(m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bat",
      //   m_strDynamicSourceConfiguration  + "_libl" + m_strPlat1 + ".bat");
#endif

      Context.dir().mk(Context.dir().install() / m_strDynamicSourceStage / "front");

      //#ifdef WINDOWS
      //      string vars1batSrc;
      //      string vars2batSrc;
      //      string vars1batDst;
      //      string vars2batDst;
      //      vars1batSrc = Context.dir().install()/"platform/stage/introjection/vc_vars.bat";
      //      vars2batSrc = Context.dir().install()/"platform/stage/introjection/vc_vars_query_registry.bat";
      //      vars1batDst = Context.dir().install()/ m_strDynamicSourceStage / "front"/"vc_vars.bat";
      //      vars2batDst = Context.dir().install()/m_strDynamicSourceStage /"front"/"vc_vars_query_registry.bat";
      //      try
      //      {
      //         Context.file().copy(vars1batDst, vars1batSrc, false);
      //      }
      //      catch(...)
      //      {
      //      }
      //      try
      //      {
      //         Context.file().copy(vars2batDst, vars2batSrc, false);
      //      }
      //      catch(...)
      //      {
      //      }
      //
      //#endif


#ifdef _UWP

      __throw(todo());

#elif defined(LINUX)

#else

      //string strCommandLine = "\"" + m_strEnv + "\" " + m_strPlat2 + " "10.0.16299.0";

      string strCommandLine = "\"" + m_strEnv + "\" " + m_strPlat2 + " " + vs_build();

      var var = System.process().get_output(strCommandLine);

      TRACE("%s", var.get_string().c_str());

#endif

      string str;
      string strItem;

      strItem = Context.dir().install() / m_strDynamicSourceStage / m_strStagePlatform;
      str = str + strItem + ";";

      strItem = Context.dir().install() / m_strDynamicSourceStage / m_strStagePlatform / "introjection\\library";
      str = str + strItem + ";";
#ifdef WINDOWS_DESKTOP
      u32 dwSize = GetEnvironmentVariableW(L"PATH",nullptr,0);
      LPTSTR lpsz = new wchar_t[dwSize + 1];
      dwSize = GetEnvironmentVariableW(L"PATH",lpsz,dwSize + 1);
      str += lpsz;
      delete lpsz;
#elif defined(_UWP)

      __throw(todo());

#else
      str += getenv("PATH");
#endif
      bool bResult = FALSE;
#ifdef WINDOWS_DESKTOP
      //bResult = SetEnvironmentVariable("PATH",str) != FALSE;
#elif defined(_UWP)

      __throw(todo());

#elif defined(LINUX)
#else
      bResult = setenv("PATH",str,TRUE);
#endif

      TRACE("compiler::prepare_compile_and_link_environment SetEnvironmentVariable return bool %d",bResult);


   }





   void compiler::prepare1(const char * lpcszSource,const char * lpcszDest)
   {
#ifdef WINDOWS
      //Sleep(15000);

      string strBuildCmd = m_strEnv;

      if (m_strVs == "2015")
      {

         strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2;

      }
      else if (m_strVs >= "2017")
      {

         strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + Application.get_visual_studio_build();

      }

      ::process::process_pointer process(e_create);


      ::file::path pathEnvTxt;

      pathEnvTxt = dir::system() / "env.txt";

      file_put_contents_dup(::dir::system() / "env1.bat",::dir::system() / "env.bat > \"" + pathEnvTxt + "\"");

      file_put_contents_dup(::dir::system() / "env.bat","@call " + strBuildCmd + "\r\n@set");

      RunSilent(::dir::system() / "env1.bat","");

      string strLog;

      strLog = file_as_string(::dir::system() / "env.txt");

      string_array stra;

      stra.add_lines(strLog);

      //Sleep(10000);

#ifdef WINDOWS_DESKTOP


      property_set setEnvironment;

      setEnvironment.parse_environment_variable(stra);

      for (auto & pproperty : setEnvironment)
      {

         TRACE("%s : %s", pproperty->m_id.to_string().c_str(), pproperty->get_string().c_str());

         SetEnvironmentVariableW(wstring(pproperty->m_id), wstring(pproperty->get_string()));

      }



#endif
#endif

      ::file::path strFolder;
      strFolder = Context.dir().install();
      if(!::str::ends(strFolder,"/") && !::str::ends(strFolder,"\\"))
         strFolder += "/";
      string strTemplate;
      string strSource = "platform/time/dynamic_source/";
      strSource += lpcszSource;

      ::file::path pathN = m_pathProjectDir;
      pathN -= 3;
      string strN = pathN;
      strN.replace("\\", "/");
      strN += "/";


      //#ifdef _DEBUG
      strTemplate = strFolder / strSource;
      //#else
      // strTemplate = strFolder, "app/time/aura/account/app/main/matter/dynamic_source_cl.bat", false);
      //#endif
      string str;
      str = Context.file().as_string(strTemplate);
      /*string strVars = getenv("VS100COMNTOOLS");
      Context.file().path().eat_end_level(strVars, 2, "/");
      strVars += "vc/bin/vcvars32.bat";*/
      str.replace("%VS_VARS%",m_strEnv);
      str.replace("%VS_VARS_PLAT2%",m_strPlat2);

      string strV(Context.dir().install());
      strV.replace("\\","/");
      if(!::str::ends(strV,"/") && !::str::ends(strV,"\\"))
         strV += "/";
      str.replace("%CA2_ROOT%",strV);
      str.replace("%PROJECT_DIR%", m_pathProjectDir);
      str.replace("%NETNODE_ROOT%",strN);
      str.replace("%SDK1%",m_strSdk1);
      string strDest = m_strDynamicSourceStage / "front" / lpcszDest;
      ::file::path strCmd;
      //#ifdef _DEBUG
      strCmd = strFolder / strDest;
      //#else
      // strCmd = strFolder, "app\\time\\aura\\account\\app\\main\\front\\dynamic_source_cl.bat", false);
      //#endif
      Context.dir().mk(strCmd.folder());
      //Context.file().put_contents_utf8(strCmd, str);
      Context.file().put_contents(strCmd,str);
      Context.dir().mk(m_strTime / "dynamic_source");

   }





   ::aura::library * compiler::compile(string strFilePath,bool bNew)
   {

      if (m_strApp.is_empty())
      {

         __throw(::exception::exception("call compiler::initialize"));

      }



      sync_lock slCompiler(mutex());

      auto & plibrary = m_lib[strFilePath];

      if(!plibrary)
      {

         plibrary = __new(library(get_context_object()));

      }
      else if(!bNew)
//         if(get_file_time(strFilePath) == lib->m_filetime)
      {

//          bNew = false;

         return plibrary->m_plibrary;

      }

      single_lock sl(plibrary->mutex());

      if (!sl.lock(millis(0)))
      {

         sl.lock();

         if (plibrary->m_plibrary.is_set())
         {

            return plibrary->m_plibrary;

         }

      }

      slCompiler.unlock();

      plibrary->m_plibrary->close();

      bNew = true;

      plibrary->m_filetime = get_file_time(strFilePath);

      ::file::path strName(strFilePath);

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

      if(Context.file().exists(strName))
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

      strCmd = ::file::path(strFilePath).folder() / "build_bot";

      string strTargetPath;
      string strSrcName = ::file::path(strFilePath).title();
      string strLogName = ::file::path(strCmd).title();
      strTargetPath =  Context.dir().module() / "lib" + strSrcName;
      string strDsymPath = (Context.dir().module().folder(3)) /  "lib" + strSrcName;
      string strDdPath = Context.dir().module().folder(7);
      string strBuildFolderPath = Context.dir().module().folder(5);
      string strSrcFolder = ::file::path(strFilePath).folder();
      string strFramework = m_strFramework;
      strClog = strCmd + "-osxc.txt";
      strLlog = strCmd + "-osxl.txt";
      strLCmd = strCmd + "-osxl";
      strPreLinkScript = strCmd + "-osxprelink";
      strDCmd = strCmd + "-osxd";
      string strLfl = strCmd + "-osx";
      strCmd += "-osxc";

      {

         string str2 = Context.file().as_string(strLfl+".LinkFileList");
         str2.replace("%TARGET_PATH%", strTargetPath);
         str2.replace("%DSYM_PATH%", strDsymPath);
         str2.replace("%DERIVED_DATA%", strDdPath);
         str2.replace("%FRAMEWORK%", strFramework);
         str2.replace("%BUILD_FOLDER%", strBuildFolderPath);
         str2.replace("%SRC_FOLDER%", strSrcFolder);
         str2.replace("%SRC_NAME%", strSrcName);
         Context.file().put_contents(strLfl + "2.LinkFileList", str2);

      }

      ::dir::mk("/var/tmp/ca2/intermediate");

#else

      string strCmd;

      strCmd = ::file::path(strFilePath).folder() / "build_bot";
      string strCmdCompile;
      string strCmdLink;
      strCmdCompile = strCmd + "-win-compile.bat";
      strCmdLink = strCmd + "-win-link.bat";

      //strName.replace("/", "\\");
      //string strFolder;
      //strFolder = Context.dir().install();
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

      //if(!Context.file().exists(lib->m_strSourcePath))
      //{
      //   lib->m_memfileError << "<pre>";
      //   str.Format("Source File : \"%s\" does not exist",lib->m_strSourcePath);
      //   lib->m_memfileError << str;
      //   lib->m_memfileError << "</pre>";
      //   return;
      //}


      //      string strTime = m_strTime;


      string strCppPath;

      //strCppPath = lib->m_pathScript;



      strClog = plibrary->m_pathScript.folder() / "build_" + plibrary->m_pathScript.title() + "-compile-log.txt";
      strLlog = plibrary->m_pathScript.folder() / "build_" + plibrary->m_pathScript.title() + "-link-log.txt";
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
      // lib->m_strLibraryPath.Format(Context.dir().install(m_strDynamicSourceStage /" Release\\%s.dll"), strName);
      //#endif

      try
      {
         if(Context.file().exists(strO))
         {
            Context.file().del(strO);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(Context.file().exists(strObj))
         {
            Context.file().del(strObj);
         }
      }
      catch(...)
      {
      }
#ifndef LINUX
      try
      {
         if(Context.file().exists(strP))
         {
            Context.file().del(strP);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(Context.file().exists(strL))
         {
            Context.file().del(strL);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(Context.file().exists(strE))
         {
            Context.file().del(strE);
         }
      }
      catch(...)
      {
      }
      //try
      //{
      //   if(Context.file().exists(strDPC))
      //   {
      //      Context.file().del(strDPC);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(Context.file().exists(strDVP))
      //   {
      //      Context.file().del(strDVP);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(Context.file().exists(strDVI))
      //   {
      //      Context.file().del(strDVI);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(Context.file().exists(strDO1))
      //   {
      //      Context.file().del(strDO1);
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   if(Context.file().exists(strDO2))
      //   {
      //      Context.file().del(strDO2);
      //   }
      //}
      //catch(...)
      //{
      //}
#endif
      try
      {
         if(Context.file().exists(strClog))
         {
            Context.file().del(strClog);
         }
      }
      catch(...)
      {
      }
      try
      {
         if(Context.file().exists(strLlog))
         {
            Context.file().del(strLlog);
         }
      }
      catch(...)
      {
      }
      //::DeleteFile(lib->m_strBuildBat);
      //try
      //{
      //   if(Context.file().exists(lib->m_pathScript + ".old"))
      //   {
      //      Context.file().del(lib->m_pathScript + ".old");
      //   }
      //}
      //catch(string strError)
      //{
      //   TRACE0(strError + "\n");
      //}
      try
      {
         //if(Context.file().exists(lib->m_pathScript))
         //{
         //   Context.file().copy(strCppPath,lib->m_pathScript);
         //}
      }
      catch(string strError)
      {

         TRACE("%s", (strError + "\n").c_str());

      }
      //try
      //{
      //   if(Context.file().exists(lib->m_pathScript + ".old"))
      //   {
      //      Context.file().del(lib->m_pathScript + ".old");
      //   }
      //}
      //catch(string strError)
      //{
      //   TRACE0(strError + "\n");
      //}
#ifndef LINUX

      //      Context.dir().mk(strDVI.folder());
      //      Context.dir().mk(lib->m_strBuildBat.folder());
      //try
      //{
      //   //         Context.file().copy(strDVI, strSVI, false);
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   Context.file().copy(strDVP, strSVP, false);
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   Context.file().copy(strDPC, strSPC, false);
      //}
      //catch(...)
      //{

      //   lib->m_bHasTempOsError = true;

      //   return;

      //}
      //try
      //{
      //   Context.file().copy(strDO1,strSO1,false);
      //}
      //catch(...)
      //{

      //   lib->m_bHasTempOsError = true;

      //   return;

      //}
      //try
      //{
      //   Context.file().copy(strDO2,strSO2,false);
      //}
      //catch(...)
      //{

      //   lib->m_bHasTempOsError = true;

      //   return;

      //}




#endif

      Context.dir().mk(plibrary->m_pathScript.folder());
      Context.dir().mk(strL.folder());
      Context.dir().mk(m_strTime / "intermediate" / m_strPlatform / m_strDynamicSourceConfiguration /  m_strRepos / m_strProjectName / strTransformName);

      ::file::path pathN = m_pathProjectDir;

      pathN -= 3;

      string strN = pathN;

      strN.replace("\\", "/");

      strN += "/";

      string strBuildCmd;

#ifdef LINUX
      strBuildCmd = Context.dir().install() / "platform/stage/introjection" / m_strApp / (m_strDynamicSourceConfiguration + "_c" + m_strPlat1 + ".bash");
#elif defined(__APPLE__)
      strBuildCmd.Format(Context.dir().install() / "platform/stage/introjection" / m_strApp / (m_strDynamicSourceConfiguration + "_c" + m_strPlat1 + ".bat"));
#else
      strBuildCmd.Format(Context.dir().install() / "platform/stage/introjection" / m_strApp / m_strVsTools / (m_strDynamicSourceConfiguration + "_c" + m_strPlat1 + ".bat"));
#endif

      str = Context.file().as_string(strBuildCmd);
      str.replace("%SOURCE%",::str::replace("\\","/",string(strName)));
      str.replace("%ITEM_NAME%",::str::replace("\\","/",string(strTransformName)));
      str.replace("%ITEM_TITLE%",strTransformName.name());
      str.replace("%ITEM_DIR%",::str::replace("\\","/",string(strTransformName.folder())) + "/");
      str.replace("%LIBS_LIBS%",m_strLibsLibs);
      str.replace("%VS_VARS%",m_strEnv);
      str.replace("%VS_VARS_PLAT2%",m_strPlat2);

      string strElem = Context.dir().install();

      strElem.replace("\\","/");

      strElem += "/";
      string strHmhLctvWildPdbPath;
      string strRndTitle;
      System.math().gen_rand_alnum(strRndTitle.get_string_buffer(64),64);

      strRndTitle.release_string_buffer();

      strHmhLctvWildPdbPath = ::file::path(::dir::system() / "netnodelite\\symbols") / strRndTitle;
      strHmhLctvWildPdbPath.replace("\\","/");
      Context.dir().mk(::file::path(strHmhLctvWildPdbPath).folder());
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

#ifdef LINUX

      string strTargetPath =  Context.dir().install() /"time" / m_strPlatform / m_strDynamicSourceConfiguration / plibrary->m_pathScript.title();
      ::str::ends_eat_ci(strTargetPath,".cpp");
      ::str::ends_eat_ci(strTargetPath,".so");

#else

      string strTargetPath = Context.dir().install() / "time" / m_strPlatform / m_strDynamicSourceConfiguration / strT2 ;
      ::str::ends_eat_ci(strTargetPath, ".cpp");
      ::str::ends_eat_ci(strTargetPath,".dll");

#endif

      strTargetPath += "-"+strRndTitle;

      str.replace("%TARGET_PATH%",strTargetPath);

      ::process::process_pointer process(e_create);

#ifdef LINUX

      file_put_contents_dup("/tmp/introj.bash", str);

      chmod("/tmp/introj.bash", S_IRWXU | S_IRWXG | S_IRWXO);

      process->create_child_process("/tmp/introj.bash",true,nullptr,::priority_highest);

#else

      str.trim();

      Context.file().put_contents(strCmdCompile, str);

      process->create_child_process(str,true,m_pathProjectDir,::priority_highest);

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
         string str2 = Context.file().as_string(strCmd);
         str2.replace("%TARGET_PATH%", strTargetPath);
         str2.replace("%DSYM_PATH%", strDsymPath);
         str2.replace("%DERIVED_DATA%", strDdPath);
         str2.replace("%FRAMEWORK%", strFramework);
         str2.replace("%BUILD_FOLDER%", strBuildFolderPath);
         str2.replace("%SRC_FOLDER%", strSrcFolder);
         str2.replace("%SRC_NAME%", strSrcName);
         str2.replace("%LOG_NAME%", strLogName);
         Context.file().put_contents(strCmd + "2", str2);

         ::system(str2);

      }

      strLog= file_as_string(strClog);

#else
auto tickStart = ::tick::now();

      while(::thread_get_run())
      {

         strLog += process->read();

         if (process->has_exited())
         {

            break;

         }

         Sleep(100);

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

         //Sleep(2000);

#endif

         str = strLog;

         str.trim();

         if(str.has_char())
         {
#ifndef MACOS
            Context.file().put_contents_utf8(strClog,strLog);
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
         strBuildCmd.Format(Context.dir().install() / "platform\\stage\\introjection" / m_strApp / (m_strDynamicSourceConfiguration + "_l" + m_strPlat1 + ".bash"));
#else
         strBuildCmd.Format(Context.dir().install() / "platform\\stage\\introjection" / m_strApp / m_strVsTools / (m_strDynamicSourceConfiguration + "_l" + m_strPlat1 + ".bat"));
#endif

         str = Context.file().as_string(strBuildCmd);


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
         //         strTargetPath = Context.dir().install() /
         str.replace("%TARGET_PATH%",strTargetPath);

         Context.file().put_contents(strCmdLink, str);
         //strBuildCmd = lib->m_strBuildBat;
         //Context.file().put_contents_utf8(strBuildCmd, str);

         //Context.file().put_contents(strBuildCmd,str);

         //str.replace("\\", "/");

         bTimeout = false;

         ::process::process_pointer process(e_create);

         //         set_thread_priority(::priority_highest);

#ifdef LINUX

         file_put_contents_dup("/tmp/introl.bash", str);

         chmod("/tmp/introl.bash", S_IRWXU | S_IRWXG | S_IRWXO);

         process->create_child_process("/tmp/introl.bash",true,nullptr,::priority_highest);

#else

         process->create_child_process(str,true,nullptr,::priority_highest);
#endif
#else

         {

            string str2 = Context.file().as_string(strPreLinkScript);
            str2.replace("%TARGET_PATH%", strTargetPath);
            str2.replace("%DSYM_PATH%", strDsymPath);
            str2.replace("%DERIVED_DATA%", strDdPath);
            str2.replace("%FRAMEWORK%", strFramework);
            str2.replace("%BUILD_FOLDER%", strBuildFolderPath);
            str2.replace("%SRC_FOLDER%", strSrcFolder);
            str2.replace("%SRC_NAME%", strSrcName);
            str2.replace("%LOG_NAME%", strLogName);
            Context.file().put_contents(strPreLinkScript + "2", str2);

            ::chmod(strPreLinkScript + "2", 0755);

            string strFileNameCmd = strPreLinkScript;

            strFileNameCmd.replace(" ", "\\ ");

            ::system(strFileNameCmd + "2 &> " + strFileNameCmd + ".txt");

         }

         {

            string str2 = Context.file().as_string(strLCmd);
            str2.replace("%TARGET_PATH%", strTargetPath);
            str2.replace("%DSYM_PATH%", strDsymPath);
            str2.replace("%DERIVED_DATA%", strDdPath);
            str2.replace("%FRAMEWORK%", strFramework);
            str2.replace("%BUILD_FOLDER%", strBuildFolderPath);
            str2.replace("%SRC_FOLDER%", strSrcFolder);
            str2.replace("%SRC_NAME%", strSrcName);
            str2.replace("%LOG_NAME%", strLogName);
            Context.file().put_contents(strLCmd + "2", str2);
            //::system(strLCmd + "2");
            ::system(str2);

            if(!::str::begins_ci(Context.dir().module(), "/Applications/"))
            {
               string str2 = Context.file().as_string(strDCmd);
               str2.replace("%TARGET_PATH%", strTargetPath);
               str2.replace("%DSYM_PATH%", strDsymPath);
               str2.replace("%DERIVED_DATA%", strDdPath);
               str2.replace("%FRAMEWORK%", strFramework);
               str2.replace("%BUILD_FOLDER%", strBuildFolderPath);
               str2.replace("%SRC_FOLDER%", strSrcFolder);
               str2.replace("%SRC_NAME%", strSrcName);
               str2.replace("%LOG_NAME%", strLogName);
               Context.file().put_contents(strDCmd + "2", str2);
               //              ::system(strDCmd + "2");
               ::system(str2);
            }

         }

#endif

         string strLog;

#ifdef MACOS

         strLog= file_as_string(strLlog);

#else

         while(true)
         {

            strLog += process->read();

            if(process->has_exited())
               break;

            Sleep(100);

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

            //Sleep(2000);

#endif


            str = strLog;

            str.trim();

            if(str.has_char())
            {

#ifndef MACOS

               Context.file().put_contents_utf8(strLlog,strLog);

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

         Context.file().del(strDVP);

      }
      catch(...)
      {

      }

#endif

#endif

      strTargetPath.replace("\\ ", " ");

      if(!plibrary->m_plibrary->open(strTargetPath))
      {

         Application.message_box("Failed to open bot library (1)\n\n" + plibrary->m_plibrary->m_strMessage);

      }

      if(!plibrary->m_plibrary->open_ca2_library(strLibTitle))
      {

         Application.message_box("Failed to open bot library (2)\n\n" + plibrary->m_plibrary->m_strMessage);

      }

      return plibrary->m_plibrary;

   }

}


DWORD RunSilent(const char* strFunct, char* strstrParams)
{

#if defined(_UWP)

   throw interface_only_exception();

#elif defined(WINDOWS_DESKTOP)

   STARTUPINFO StartupInfo;

   PROCESS_INFORMATION ProcessInfo;

   char Args[4096];

   char *pEnvCMD = nullptr;

   char *pDefaultCMD = "CMD.EXE";

   ULONG rc;

   __memset(&StartupInfo, 0, sizeof(StartupInfo));

   StartupInfo.cb = sizeof(STARTUPINFO);

   StartupInfo.dwFlags = STARTF_USESHOWWINDOW;

   StartupInfo.wShowWindow = SW_HIDE;

   Args[0] = 0;

   pEnvCMD = getenv("COMSPEC");

   if (pEnvCMD)
   {

      strcpy(Args, pEnvCMD);

   }
   else
   {

      strcpy(Args, pDefaultCMD);

   }

   // "/c" option - Do the command then terminate the command window
   ansi_concatenate(Args, " /c ");
   //the application you would like to run from the command window
   ansi_concatenate(Args, strFunct);
   ansi_concatenate(Args, " ");
   //the parameters passed to the application being run from the command window.
   ansi_concatenate(Args, strstrParams);

   if (!CreateProcessW(nullptr, wstring(Args), nullptr, nullptr, FALSE,
                      CREATE_NEW_CONSOLE,
                      nullptr,
                      nullptr,
                      &StartupInfo,
                      &ProcessInfo))
   {

      return get_last_error();

   }

   WaitForSingleObject(ProcessInfo.hProcess, INFINITE);

   if (!GetExitCodeProcess(ProcessInfo.hProcess, &rc))
   {

      rc = 0;

   }

   CloseHandle(ProcessInfo.hThread);

   CloseHandle(ProcessInfo.hProcess);

   return rc;

#else

   string strCmdLine;

   strCmdLine = strFunct;

   if (ansi_length(strstrParams) > 0)
   {

      strCmdLine += " ";

      strCmdLine += strstrParams;

   }

   i32 processId;

   if (!create_process(strCmdLine, &processId))
   {

      return -1;

   }

   while (true)
   {

      if (kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
      {

         break;

      }

      sleep(millis(23));

   }

   return 0;

#endif

}


