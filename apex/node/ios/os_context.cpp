#include "framework.h"
#include "_ios.h"


bool ns_open_file(const char * );


namespace ios
{


   os_context::os_context()
   {
      
   }


   os_context::~os_context()
   {
      
   }


   string os_context::get_command_line()
   {

      return get_command_line();

   }


   bool os_context::shutdown(bool bIfPowerOff)
   {
      
      /*      bool retval = true;
       HANDLE hToken;
       TOKEN_PRIVILEGES tkp;
       if (!OpenProcessToken(GetCurrentProcess(),
       TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
       return false;
       LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
       tkp.PrivilegeCount = 1;
       tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
       AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
       if (bIfPowerOff)
       retval = ExitWindowsEx(EWX_POWEROFF, 0) != false;
       else
       retval = ExitWindowsEx(EWX_SHUTDOWN, 0) != false;

       //reset the previlages
       tkp.Privileges[0].Attributes = 0;
       AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
       return retval;*/

      //  __throw(error_not_implemented);
      return false;

   }


   bool os_context::reboot()
   {
      /*      HANDLE hToken;
       TOKEN_PRIVILEGES tkp;
       if (!OpenProcessToken(GetCurrentProcess(),
       TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
       return false;
       if(!LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
       {
       TRACELASTERROR();
       return false;
       }
       tkp.PrivilegeCount = 1;
       tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
       if(!AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES) nullptr, 0))
       {
       TRACELASTERROR();
       return false;
       }
       if (get_last_error() == ERROR_NOT_ALL_ASSIGNED)
       {
       return false;
       }
       if(!LookupPrivilegeValue(nullptr, SE_REMOTE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
       {
       TRACELASTERROR();
       return false;
       }
       tkp.PrivilegeCount = 1;
       tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
       if(!AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES) nullptr, 0))
       {
       TRACELASTERROR();
       return false;
       }
       if (get_last_error() == ERROR_NOT_ALL_ASSIGNED)
       {
       return false;
       }


       if(!WTSShutdownSystem(WTS_CURRENT_SERVER_HANDLE, WTS_WSD_REBOOT))
       {
       TRACELASTERROR();
       return false;
       }
       if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE,
       SHTDN_REASON_MAJOR_SOFTWARE | SHTDN_REASON_MINOR_INSTALLATION))
       {
       ::u32 dwLastError = ::get_last_error();
       return false;
       }*/
      //reset the previlages
      /*    tkp.Privileges[0].Attributes = 0;
       AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
       return true;*/
      //    __throw(error_not_implemented);
      return false;

   }


   void os_context::terminate_processes_by_title(const char * pszName)
   {
//      __throw(error_not_implemented);
      return;

      /*      ::u32 dwPid;
       while(get_pid_by_title(pszName, dwPid))
       {
       HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
       PROCESS_VM_READ,
       false, dwPid );
       TerminateProcess(hProcess, (::u32) -1);
       CloseHandle(hProcess);
       ::EnumWindows((WNDENUMPROC)
       CKillProcessHelper::TerminateAppEnum,
       (LPARAM) dwId);
       // Wait on the handle. If it signals, great.

       //If it times out, then you kill it.

       if(WaitForSingleObject(hProcess, 5000)
       !=WAIT_OBJECT_0)
       bResult = TerminateProcess(hProcess,0);
       else
       bResult = true;
       CloseHandle(hProcess);
       return bResult == true;*/

      //  }
   }


   bool os_context::get_pid_by_path(const char * pszName, ::u32 & dwPid)
   {
      u32_array dwa;
      get_all_processes(dwa);
      for(i32 i = 0; i < dwa.get_count(); i++)
      {
         if(get_process_path(dwa[i]).compare_ci(pszName) == 0)
         {
            dwPid = dwa[i];
            return true;
         }
      }
      return false;
   }


   bool os_context::get_pid_by_title(const char * pszName, ::u32 & dwPid)
   {
      u32_array dwa;
      get_all_processes(dwa);
      for(i32 i = 0; i < dwa.get_count(); i++)
      {
         if(get_process_path(dwa[i]).title().compare_ci(pszName) == 0)
         {
            dwPid = dwa[i];
            return true;
         }
      }
      return false;
   }


   int os_context::get_pid()
   {

      return ::getpid();

   }


   ::file::path os_context::get_process_path(::u32 dwPid)
   {
      /*
       string strName = ":<unknown>";
       // get a handle to the process.
       HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
       PROCESS_VM_READ,
       false, dwPid );

       // get the process name.

       if (nullptr != hProcess )
       {
       HMODULE hMod;
       ::u32 cbNeeded;

       if(EnumProcessModules( hProcess, &hMod, sizeof(hMod),
       &cbNeeded) )
       {
       strName = get_module_path(hMod);
       }
       }

       CloseHandle( hProcess );
       return strName;*/
      //    __throw(error_not_implemented);
      return "";

   }


   void os_context::get_all_processes(u32_array & dwa )
   {

      //  __throw(error_not_implemented);
      return;

      /*
       dwa.set_size(0);
       ::u32 cbNeeded = 0;
       while(cbNeeded == natural(dwa.get_count()))
       {
       dwa.set_size(dwa.get_count() + 1024);
       if(!EnumProcesses(
       dwa.get_data(),
       (::u32) (dwa.get_count() * sizeof(::u32)),
       &cbNeeded))
       {
       return;
       }
       dwa.set_size(cbNeeded / sizeof(::u32));
       }*/
   }


   string os_context::get_module_path(HMODULE hmodule)
   {
      //   __throw(error_not_implemented);
      return "";
      /*
       string strPath;
       ::u32 dwSize = 1;
       while(natural(strPath.get_length() + 1) == dwSize)
       {
       dwSize = ::GetModuleFileName(
       hmodule,
       strPath.get_string_buffer(dwSize + 1024),
       (dwSize + 1024));
       strPath.ReleaseBuffer();
       }
       return strPath;*/
   }


   ::payload os_context::connection_settings_get_auto_detect()
   {
//      __throw(error_not_implemented);
      return false;

      /*
       registry::Key key1;

       key1.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Connections", false);

       memory mem;

       key1.QueryValue("DefaultConnectionSettings", mem);

       bool bAutoDetect = (((byte *) mem.get_data())[8] & 0x08) != 0;

       return bAutoDetect;
       */
   }


   ::payload os_context::connection_settings_get_auto_config_url()
   {

//      __throw(error_not_implemented);
      return "";
      /*
       registry::Key key;

       key.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", false);

       string strUrl;

       key.QueryValue("AutoConfigURL", strUrl);

       return strUrl;
       */
   }


   bool os_context::local_machine_set_run(const char * pszKey, const char * pszCommand)
   {

//     __throw(error_not_implemented);
      return false;

      /*
       registry::Key keyKar(HKEY_LOCAL_IOSHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);


       keyKar.SetValue(pszKey, pszCommand);


       return true;
       */
   }


   bool os_context::local_machine_set_run_once(const char * pszKey, const char * pszCommand)
   {


//     __throw(error_not_implemented);
      return false;
      /*    registry::Key keyKar(HKEY_LOCAL_IOSHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);


       keyKar.SetValue(pszKey, pszCommand);
       */

      return false;

   }


   bool os_context::current_user_set_run(const char * pszKey, const char * pszCommand)
   {

      //   __throw(error_not_implemented);
      return false;

      /*
       registry::Key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);


       keyKar.SetValue(pszKey, pszCommand);
       */

      return false;

   }


   bool os_context::current_user_set_run_once(const char * pszKey, const char * pszCommand)
   {

//    __throw(error_not_implemented);
      return false;

      /*
       registry::Key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);


       keyKar.SetValue(pszKey, pszCommand);

       */
      return false;

   }


   bool os_context::defer_register_ca2_plugin_for_mozilla()
   {
      //    __throw(error_not_implemented);
      return false;

      /*
       registry::Key keyPlugins;

       if(keyPlugins.OpenKey(HKEY_LOCAL_IOSHINE, "SOFTWARE\\MozillaPlugins", true))
       {

       registry::Key keyPlugin;

       if(keyPlugin.OpenKey(keyPlugins, "@ca2.software/npca2", true))
       {

       keyPlugin.SetValue("Description", "ca2 plugin for NPAPI");
       keyPlugin.SetValue("Path", ::apex::get_system()->m_strCa2Module("npca2.dll"));
       keyPlugin.SetValue("ProductName", "ca2 plugin for NPAPI");
       keyPlugin.SetValue("Vendor", "ca2 Desenvolvimento de Software Ltda.");
       keyPlugin.SetValue("Version", get_application()->m_psystem->m_pacmefile->as_string(pcontext->m_papexcontext->dir().ca2("appdata/x86/ca2_build.txt")));

       registry::Key keyApplicationCa2;

       if(keyApplicationCa2.OpenKey(keyPlugin, "application/ca2", true))
       {

       keyApplicationCa2.SetValue("Description", "ca2 Document");

       }

       }

       }

       return true;
       */
   }


   bool os_context::file_extension_get_open_with_list_keys(string_array & straKey, const char * pszExtension)
   {
      //   __throw(error_not_implemented);
      return false;

      /*
       string strExt;

       strExt = ".";
       strExt += pszExtension;

       string strOpenWithKey;
       strOpenWithKey = strExt + "\\OpenWithList";

       registry::Key key;

       key.OpenKey(HKEY_CLASSES_ROOT, strOpenWithKey, false);

       key.EnumKey(straKey);

       return true;
       */
   }


   bool os_context::file_extension_get_open_with_list_commands(string_array & straCommand, const char * pszExtension)
   {

      string_array straKey;

      if(!file_extension_get_open_with_list_keys(straKey, pszExtension))
         return false;


      return true;

   }


   bool os_context::file_association_set_default_icon(const char * pszExtension, const char * pszExtensionNamingClass, const char * pszIconPath)
   {

      //    __throw(error_not_implemented);
      return false;

      /*
       string strExtensionNamingClass(pszExtensionNamingClass);

       registry::Key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass, true);
       keyLink3.SetValue("DefaultIcon", pszIconPath);


       return false;
       */
   }


   bool os_context::file_association_set_shell_open_command(const char * pszExtension, const char * pszExtensionNamingClass,  const char * pszCommand, const char * pszParam)
   {
      //   __throw(error_not_implemented);
      return false;

      /*
       string strExt;

       strExt = ".";
       strExt += pszExtension;

       string strExtensionNamingClass(pszExtensionNamingClass);

       registry::Key key(HKEY_CLASSES_ROOT, strExt, true);
       key.SetValue(nullptr, strExtensionNamingClass);

       registry::Key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass + "\\shell", true);
       keyLink3.SetValue(nullptr, "open");

       registry::Key keyLink2(keyLink3, "open", true);
       keyLink2.SetValue(nullptr, "&Abrir");

       registry::Key keyLink1(keyLink2, "command", true);

       string strFormat;
       strFormat.format("\"%s\" \"%%L\" %s", pszCommand, pszParam);
       keyLink1.SetValue(nullptr, strFormat);

       return true;
       */
   }


   bool os_context::file_association_get_shell_open_command(const char * pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
   {
      //    __throw(error_not_implemented);
      return false;

      /*
       string strExt;

       strExt = ".";
       strExt += pszExtension;

       registry::Key key(HKEY_CLASSES_ROOT, strExt, false);
       if(!key.QueryValue(nullptr, strExtensionNamingClass))
       return false;

       registry::Key keyLink(HKEY_CLASSES_ROOT, strExtensionNamingClass + "\\shell\\open\\command", false);

       string strFormat;
       if(keyLink.QueryValue(nullptr, strFormat))
       {

       const char * psz = strFormat;

       try
       {

       strCommand = ::str::consume_quoted_value(psz);
       ::str::consume_spaces(psz);
       ::str::consume(psz, "\"%L\"");
       strParam = psz;

       }
       catch(...)
       {
       }


       }

       return true;
       */
   }


   bool os_context::open_in_ie(const char * pcsz)
   {

      //    __throw(error_not_implemented);
      return false;

      /*    registry reg;
       string str;
       string str2;
       string strCommand;
       registry::Key key;
       if(key.OpenKey(HKEY_CLASSES_ROOT, ".html", false))
       {
       if(reg.RegQueryValue(key.m_hkey, "", str))
       {
       if(key.OpenKey(HKEY_CLASSES_ROOT, ".html\\shell\\opennew\\command", false))
       {
       string str;
       if(reg.RegQueryValue(HKEY_CLASSES_ROOT, str, str2))
       {
       string strCommand(str2);
       strCommand.replace("%1", pcsz);
       WinExec(strCommand,e_display_normal);
       }
       }
       else
       {
       if(key.OpenKey(HKEY_CLASSES_ROOT, str, false))
       {
       str += "\\shell\\opennew\\command";
       if(key.OpenKey(HKEY_CLASSES_ROOT, str, false))
       {
       if(reg.RegQueryValue(key.m_hkey, "", str2))
       {
       string strCommand(str2);
       strCommand.replace("%1", pcsz);
       WinExec(strCommand,e_display_normal);
       }
       }
       }
       }
       }
       }

       return true;
       */

   }


   ::e_status os_context::create_service()
   {

      //    __throw(error_not_implemented);
      return false;

      /*
       if(papp->m_strAppName.is_empty()
       || papp->m_strAppName.compare_ci("bergedge") == 0
       || !papp->is_serviceable())
       return false;

       SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);

       string strCalling = papp->m_strModulePath + " : app=" + papp->m_XstrAppId + " service usehostlogin";

       if(hdlSCM == 0)
       {
       //::get_last_error()
       return false;
       }

       SC_HANDLE hdlServ = ::CreateService(
       hdlSCM,                    // SCManager database
       "apex-" + papp->m_strAppName,               // name of service
       "ccwarehouse ca2 account " + papp->m_strAppName,        // service name to display
       STANDARD_RIGHTS_REQUIRED,  // desired access
       SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, // service type
       SERVICE_AUTO_START,      // start type
       SERVICE_ERROR_NORMAL,      // error control type
       strCalling,                   // service's binary Path name
       0,                      // no load ordering group
       0,                      // no tag identifier
       0,                      // no dependencies
       0,                      // LocalSystem account
       0);                     // no password

       if (!hdlServ)
       {
       CloseServiceHandle(hdlSCM);
       //Ret = ::get_last_error();
       return false;
       }

       CloseServiceHandle(hdlServ);
       CloseServiceHandle(hdlSCM);

       return true;
       */

   }


   ::e_status os_context::erase_service()
   {

      return false;

      /*
       if(papp->m_strAppName.is_empty()
       || papp->m_strAppName.compare_ci("bergedge") == 0
       || !papp->is_serviceable())
       return false;

       SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

       if(hdlSCM == 0)
       {
       //::get_last_error();
       return false;
       }

       SC_HANDLE hdlServ = ::OpenService(
       hdlSCM,                    // SCManager database
       "apex-" + papp->m_strAppName,               // name of service
       DELETE);                     // no password

       if (!hdlServ)
       {
       // Ret = ::get_last_error();
       CloseServiceHandle(hdlSCM);
       return false;
       }

       ::DeleteService(hdlServ);

       CloseServiceHandle(hdlServ);

       CloseServiceHandle(hdlSCM);

       return false;
       */
   }


   ::e_status os_context::start_service()
   {
      //  __throw(error_not_implemented);
      return false;

      /*
       if(papp->m_strAppName.is_empty()
       || papp->m_strAppName.compare_ci("bergedge") == 0
       || !papp->is_serviceable())
       return false;

       SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

       if(hdlSCM == 0)
       {
       //::get_last_error();
       return false;
       }

       SC_HANDLE hdlServ = ::OpenService(
       hdlSCM,                    // SCManager database
       "apex-" + papp->m_strAppName,               // name of service
       SERVICE_START);                     // no password


       if (!hdlServ)
       {
       CloseServiceHandle(hdlSCM);
       //Ret = ::get_last_error();
       return false;
       }

       bool bOk = StartService(hdlServ, 0, nullptr) != false;

       CloseServiceHandle(hdlServ);
       CloseServiceHandle(hdlSCM);

       return bOk != false;
       */
   }


   ::e_status os_context::stop_service()
   {
      //    __throw(error_not_implemented);
      return false;

      /*
       if(papp->m_strAppName.is_empty()
       || papp->m_strAppName.compare_ci("bergedge") == 0
       || !papp->is_serviceable())
       return false;

       SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

       if(hdlSCM == 0)
       {
       //::get_last_error();
       return false;
       }

       SC_HANDLE hdlServ = ::OpenService(
       hdlSCM,                    // SCManager database
       "apex-" + papp->m_strAppName,               // name of service
       SERVICE_STOP);                     // no password

       if (!hdlServ)
       {
       // Ret = ::get_last_error();
       CloseServiceHandle(hdlSCM);
       return false;
       }

       SERVICE_STATUS ss;

       __memset(&ss, 0, sizeof(ss));

       bool bOk = ::ControlService(hdlServ, SERVICE_CONTROL_STOP, &ss) != false;

       ::DeleteService(hdlServ);

       CloseServiceHandle(hdlServ);

       CloseServiceHandle(hdlSCM);

       return bOk != false;
       */
   }


   void os_context::raise_exception( ::u32 dwExceptionCode, ::u32 dwExceptionFlags)
   {

      __throw(error_not_implemented);
      return;
      /*
       RaiseException( dwExceptionCode, dwExceptionFlags, 0, nullptr );
       */
   }


   bool os_context::is_remote_session()
   {

//      __throw(error_not_implemented);
      return false;
      /*
       return GetSystemMetrics(SM_REMOTESESSION) != false;
       */
   }


   void os_context::post_to_all_threads(const ::id & id, wparam wparam, lparam lparam)
   {

//      __throw(error_not_implemented);
      return;


   }


   bool os_context::initialize_wallpaper_fileset(::file::set * pfileset, bool bAddSearch)
   {

      if (bAddSearch)
      {

         //string strDir;
         //strDir = pcontext->m_papexcontext->dir().path(getenv("HOME"), "Pictures");
         //imagefileset.add_search(strDir);
         string strDir;
         strDir = "/Library/Wallpaper";
         pfileset->add_search(strDir, true);

         strDir = "/Library/Desktop Pictures";
         pfileset->add_search(strDir, true);

      }

      return true;

   }


   bool os_context::file_open(::file::path path, string strParams, string strFolder)
   {

      path = get_context()->defer_process_path(path);

      ns_main_async(^
      {

         ns_open_file(path.c_str());

      });

      return true;

   }


} // namespace ios









//
//  macos_os.cpp
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//


CLASS_DECL_APEX bool _istlead(i32 ch)
{

   return false;

}








int_bool GetCursorPos(POINT_I32 * lppointCursor)
{

   /*   HIPoint point_i32;

   HICoordinateSpace space = kHICoordSpaceScreenPixel;

   HIGetMousePosition(space, nullptr, &point);


   lppointCursor->x = point.x;
   lppointCursor->y = point.y;
   */

   return true;

}



