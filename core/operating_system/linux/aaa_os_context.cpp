#include "framework.h"
#include "aura/platform/app_core.h"
#include "_linux.h"
#include "aura/os/linux/gnome_gnome.h"
#include <unistd.h>

i32 daemonize_process(const ::string & _cmd_line, i32 * pprocessId);

#undef USERNAME_LENGTH // mysql one


#include <sys/stat.h>

string empty_get_file_content_type(string)
{

   return "";

}

PFN_GET_FILE_CONTENT_TYPE g_pfnGetFileContentType = &empty_get_file_content_type;

string linux_get_file_content_type(string strPath)
{

   return (*g_pfnGetFileContentType)(strPath);

}

void set_get_file_content_type_function(PFN_GET_FILE_CONTENT_TYPE pfnGetFileContentType)
{

   g_pfnGetFileContentType = pfnGetFileContentType;

}


bool linux_can_exec(const ::string &file)
{

   struct stat st;

   string str(file);

   if(str.case_insensitive_begins_eat("\""))
   {

      auto pFind = str.find("\"");

      if(::is_null(pFind))
      {

         return false;

      }

      str = str(0, pFind);

   }
   else if(str.case_insensitive_begins_eat("\'"))
   {

      auto pFind = str.find("\'");

      if(::is_null(pFind))
      {

         return false;

      }

      str = str(0, pFind);

   }
   else
   {

      auto pFind = str.find(" ");

      if(iFind > 0)
      {

         str = str(0, pFind);

      }


   }

   if(str == "sudo")
   {

      return true;

   }

   zero(st);

   if (stat(str, &st) < 0)
   {

      return false;

   }

   if ((st.st_mode & S_IEXEC) != 0)
   {

      string strContentType = linux_get_file_content_type(str);

      if(strContentType == "application/x-shellscript")
      {

         return true;

      }
      else if(strContentType == "application/x-sharedlib")
      {

         return true;

      }


      return false;

   }

   return false;

}


namespace linux
{


   os_context::os_context()
   {
   }


   os_context::~os_context()
   {
   }


   string os_context::get_command_line()
   {

      return psystem->get_command_line();

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

      throw ::not_implemented();
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
      //      if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE,
      //      SHTDN_REASON_MAJOR_SOFTWARE | SHTDN_REASON_MINOR_INSTALLATION))
      //      {
      //      ::u32 dwLastError = ::get_last_error();
      //      return false;
      //      }
            //reset the previlages
      //      tkp.Privileges[0].Attributes = 0;
      //      AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
      //      return true;
            throw ::not_implemented();
            return false;

         */
      return false;
   }


   void os_context::terminate_processes_by_title(const ::string & lpszName)
   {
      throw ::not_implemented();
      return;

      /*      ::u32 dwPid;
            while(get_pid_by_title(lpszName, dwPid))
            {
               HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                  PROCESS_VM_READ,
                  false, dwPid );
               TerminateProcess(hProcess, (::u32) -1);
               Clos_contexteHandle(hProcess);
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
               Clos_contexteHandle(hProcess);
               return bResult == true;*/

      //  }
   }

   bool os_context::get_pid_by_path(const ::string & lpszName, ::u32 & dwPid)
   {
      u32_array dwa;
      get_all_processes(dwa);
      for(i32 i = 0; i < dwa.get_count(); i++)
      {
         if(get_process_path(dwa[i]).case_insensitive_order(lpszName) == 0)
         {
            dwPid = dwa[i];
            return true;
         }
      }
      return false;
   }


   bool os_context::get_pid_by_title(const ::string & lpszName, ::u32 & dwPid)
   {

      u32_array dwa;

      get_all_processes(dwa);

      for(i32 i = 0; i < dwa.get_count(); i++)
      {

         if(get_process_path(dwa[i]).title().case_insensitive_order(lpszName) == 0)
         {

            dwPid = dwa[i];

            return true;

         }

      }

      return false;

   }


   ::file::path os_context::get_process_path(::u32 dwPid)
   {
      throw ::not_implemented();
      return "";

   }

   void os_context::get_all_processes(u32_array & dwa )
   {

      throw ::not_implemented();
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

//   string os_context::get_module_path(HMODULE hmodule)
//   {
//      throw ::not_implemented();
//      return "";
//      /*
//      string strPath;
//      ::u32 dwSize = 1;
//      while(natural(strPath.length() + 1) == dwSize)
//      {
//         dwSize = ::GetModuleFileName(
//            hmodule,
//            strPath.get_buffer(dwSize + 1024),
//            (dwSize + 1024));
//         strPath.ReleaseBuffer();
//      }
//      return strPath;*/
//   }


   ::payload os_context::connection_settings_get_auto_detect()
   {
      //throw ::not_implemented();
      return false;

      /*
            registry::Key key1;

            key1.OpenKey(HKEY_CURRENT_USER, "Software\\Micros_contextoft\\Windows\\CurrentVersion\\Internet Settings\\Connections", false);

            memory mem;

            key1.QueryValue("DefaultConnectionSettings", mem);

            bool bAutoDetect = (((byte *) mem.get_data())[8] & 0x08) != 0;

            return bAutoDetect;
      */
   }



   ::payload os_context::connection_settings_get_auto_config_url()
   {

      //throw ::not_implemented();
      return "";
      /*
            registry::Key key;

            key.OpenKey(HKEY_CURRENT_USER, "Software\\Micros_contextoft\\Windows\\CurrentVersion\\Internet Settings", false);

            string strUrl;

            key.QueryValue("AutoConfigURL", strUrl);

            return strUrl;
      */
   }

   bool os_context::local_machine_set_run(const ::string & pszKey, const ::string & pszCommand)
   {

//      throw ::not_implemented();
      return false;

      /*
            registry::Key keyKar(HKEY_LOcaL_MACHINE, "SOFTWARE\\Micros_contextoft\\Windows\\CurrentVersion\\Run", true);


            keyKar.SetValue(pszKey, pszCommand);


            return true;
      */
   }


   bool os_context::local_machine_set_run_once(const ::string & pszKey, const ::string & pszCommand)
   {


      throw ::not_implemented();
      return false;
      /*    registry::Key keyKar(HKEY_LOcaL_MACHINE, "SOFTWARE\\Micros_contextoft\\Windows\\CurrentVersion\\RunOnce", true);


            keyKar.SetValue(pszKey, pszCommand);
      */

      return false;

   }

   bool os_context::current_user_set_run(const ::string & pszKey, const ::string & pszCommand)
   {

      throw ::not_implemented();
      return false;

      /*
            registry::Key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Micros_contextoft\\Windows\\CurrentVersion\\Run", true);


            keyKar.SetValue(pszKey, pszCommand);
      */

      return false;

   }

   bool os_context::current_user_set_run_once(const ::string & pszKey, const ::string & pszCommand)
   {

      throw ::not_implemented();
      return false;

      /*
            registry::Key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Micros_contextoft\\Windows\\CurrentVersion\\RunOnce", true);


            keyKar.SetValue(pszKey, pszCommand);

      */
      return false;

   }


   bool os_context::defer_register_ca2_plugin_for_mozilla()
   {
      //  throw ::not_implemented();
      return false;

      /*
            registry::Key keyPlugins;

            if(keyPlugins.OpenKey(HKEY_LOcaL_MACHINE, "SOFTWARE\\MozillaPlugins", true))
            {

               registry::Key keyPlugin;

               if(keyPlugin.OpenKey(keyPlugins, "@ca2.software/npca2", true))
               {

                  keyPlugin.SetValue("Description", "ca2 plugin for NPAPI");
                  keyPlugin.SetValue("Path", psystem->m_strCa2Module("npca2.dll"));
                  keyPlugin.SetValue("ProductName", "ca2 plugin for NPAPI");
                  keyPlugin.SetValue("Vendor", "ca2 Desenvolvimento de Software Ltda.");
                  keyPlugin.SetValue("Version", papp->acmefile()->as_string(pcontext->m_papexcontext->dir()->ca2("appdata/x86/ca2_build.txt")));

                  registry::Key keyApplicationca2;

                  if(keyApplicationca2.OpenKey(keyPlugin, "application/ca2", true))
                  {

                     keyApplicationca2.SetValue("Description", "ca2 Document");

                  }

               }

            }

            return true;
      */
   }

   bool os_context::file_extension_get_open_with_list_keys(string_array & straKey, const ::string & pszExtension)
   {
      throw ::not_implemented();
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


   bool os_context::file_extension_get_open_with_list_commands(string_array & straCommand, const ::string & pszExtension)
   {

      string_array straKey;

      if(!file_extension_get_open_with_list_keys(straKey, pszExtension))
         return false;


      return true;

   }

   bool os_context::file_association_set_default_icon(const ::string & pszExtension, const ::string & pszExtensionNamingClass, const ::string & pszIconPath)
   {

      throw ::not_implemented();
      return false;

      /*
            string strExtensionNamingClass(pszExtensionNamingClass);

            registry::Key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass, true);
            keyLink3.SetValue("DefaultIcon", pszIconPath);


            return false;
      */
   }


   bool os_context::file_association_set_shell_open_command(const ::string & pszExtension, const ::string & pszExtensionNamingClass,  const ::scoped_string & scopedstrCommand, const ::string & pszParam)
   {

      return false;

      throw ::not_implemented();

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

   bool os_context::file_association_get_shell_open_command(const ::string & pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
   {
      throw ::not_implemented();
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

               const ::scoped_string & scopedstr = strFormat;

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

   bool os_context::open_in_ie(const ::string & pcsz)

   {

      throw ::not_implemented();
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

   bool os_context::create_service(::particle * pparticle)
   {

      //throw ::not_implemented();
      return true;

      /*
            if(papp->m_strAppName.is_empty()
            || papp->m_strAppName.case_insensitive_order("bergedge") == 0
            || !papp->is_serviceable())
               return false;

            SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);

            string strcalling = papp->m_strModulePath + " : app=" + papp->m_strAppId + " service usehos_contexttlogin";

            if(hdlSCM == 0)
            {
               //::get_last_error()
               return false;
            }

            SC_HANDLE hdlServ = ::CreateService(
               hdlSCM,                    // SCManager database
               "aura-" + papp->m_strAppName,               // name of service
               "ccwarehouse ca2 account " + papp->m_strAppName,        // service name to display
               STANDARD_RIGHTS_REQUIRED,  // desired access
               SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, // service type
               SERVICE_AUTO_START,      // start type
               SERVICE_ERROR_NORMAL,      // error control type
               strcalling,                   // service's binary Path name
               0,                      // no load ordering group
               0,                      // no tag identifier
               0,                      // no dependencies
               0,                      // LocalSystem account
               0);                     // no password

            if (!hdlServ)
            {
               Clos_contexteServiceHandle(hdlSCM);
               //Ret = ::get_last_error();
               return false;
            }

            Clos_contexteServiceHandle(hdlServ);
            Clos_contexteServiceHandle(hdlSCM);

            return true;
      */

   }


   bool os_context::erase_service(::particle * pparticle)
   {
//      throw ::not_implemented();
      return false;

      /*
            if(papp->m_strAppName.is_empty()
            || papp->m_strAppName.case_insensitive_order("bergedge") == 0
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
               "aura-" + papp->m_strAppName,               // name of service
               DELETE);                     // no password

            if (!hdlServ)
            {
               // Ret = ::get_last_error();
               Clos_contexteServiceHandle(hdlSCM);
               return false;
            }

            ::DeleteService(hdlServ);

            Clos_contexteServiceHandle(hdlServ);

            Clos_contexteServiceHandle(hdlSCM);

            return false;
      */
   }

   bool os_context::start_service(::particle * pparticle)
   {
      //throw ::not_implemented();
      return false;

      /*
            if(papp->m_strAppName.is_empty()
            || papp->m_strAppName.case_insensitive_order("bergedge") == 0
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
               "aura-" + papp->m_strAppName,               // name of service
               SERVICE_START);                     // no password


            if (!hdlServ)
            {
               Clos_contexteServiceHandle(hdlSCM);
               //Ret = ::get_last_error();
               return false;
            }

            bool bOk = StartService(hdlServ, 0, nullptr) != false;

            Clos_contexteServiceHandle(hdlServ);
            Clos_contexteServiceHandle(hdlSCM);

            return bOk != false;
            */
   }

   bool os_context::stop_service(::particle * pparticle)
   {
      throw ::not_implemented();
      return false;

      /*
            if(papp->m_strAppName.is_empty()
            || papp->m_strAppName.case_insensitive_order("bergedge") == 0
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
               "aura-" + papp->m_strAppName,               // name of service
               SERVICE_STOP);                     // no password

            if (!hdlServ)
            {
               // Ret = ::get_last_error();
               Clos_contexteServiceHandle(hdlSCM);
               return false;
            }

            SERVICE_STATUS ss;

            memory_set(&ss, 0, sizeof(ss));

            bool bOk = ::ControlService(hdlServ, SERVICE_CONTROL_STOP, &ss) != false;

            ::DeleteService(hdlServ);

            Clos_contexteServiceHandle(hdlServ);

            Clos_contexteServiceHandle(hdlSCM);

            return bOk != false;
      */
   }


   void os_context::raise_exception( ::u32 dwExceptionCode, ::u32 dwExceptionFlags)
   {

      throw ::not_implemented();
      return;
      /*
            RaiseException( dwExceptionCode, dwExceptionFlags, 0, nullptr );
            */
   }

   bool os_context::is_remote_session()
   {

//      throw ::not_implemented();
      return false;
      /*
            return GetSystemMetrics(SM_REMOTESESSION) != false;
      */
   }


   void os_context::post_to_all_threads(const ::atom & atom, WPARAM wparam, LPARAM lparam)

   {

      return;

   }


   int os_context::get_pid()
   {

      return ::getpid();

   }


   bool os_context::initialize_wallpaper_fileset(::file::set * pfileset, bool bAddSearch)
   {

      if (bAddSearch)
      {

         string strDir;

         strDir = "/usr/share/backgrounds";

         pfileset->add_search(strDir, true);

      }

      return true;

   }


   //#elif defined(LINUX)
   //            }
   //
   //#elif defined(MACos_context)
   //   //string strDir;
   //   //strDir = pcontext->m_papexcontext->dir()->path(getenv("HOME"), "Pictures");
   //   //imagefileset.add_search(strDir);
   //   string strDir;
   //   strDir = "/Library/Desktop Pictures";
   //   imagefileset.add_search(strDir, true);
   //            }
   //
   //#else

   bool os_context::get_default_browser(string & strId, ::file::path & path, string & strParam)
   {

      string str = psystem->process().get_output("/bin/sh -c \"xdg-settings get default-web-browser\"");

      str.trim();

      if(str.case_insensitive_ends(".desktop"))
      {

         ::file::path pathDesktop = "/usr/share/applications";

         pathDesktop /= str;

         if(acmefile()->exists(pathDesktop))
         {

            ::file::path pathTarget;

            resolve_link(pathTarget, pathDesktop, nullptr, &strParam);

            path = pathTarget;

         }

      }

      //string str = psystem->process().get_output("xdg-settings get default-web-browser");

      if(str.case_insensitive_find("chrome") >= 0)
      {

         strId = "chrome";

         if(path.is_empty())
         {

            path = "google-chrome";

         }

      }
      else
      {

         strId = "firefox";


         path = "firefox";

      }

      return true;

   }


   bool os_context::file_open(::file::path strTarget, string strParams, string strFolder)
   {

      strTarget = pcontext->m_papexcontext->defer_process_path(strTarget);

      if(linux_can_exec(strTarget))
      {

         //int iPid;

         //daemonize_process(strTarget, &iPid);

         //::system("cd /; setsid \"" + strTarget + "\" </dev/null &>/dev/null");

         //i32 daemonize_process(const ::string & _cmd_line, i32 * pprocessId)

         // 2018-01-29 call_async("/bin/bash", "-c \"" + strTarget + "\"", strFolder, SW_SHOWDEFAULT, false);

         call_async(strTarget, strParams, strFolder, e_display_default, false);

//         char * pszCommandLine = strdup(strTarget + " " + strParams);

//         pid_t pid = ::fork();
//
//         if(pid == 0)
//         {
//
//            int iExitCode = ::system(pszCommandLine);
//
//            free(pszCommandLine);
//
//            exit(iExitCode);
//
//         }
//         else if(pid < 0)
//         {
//
//            free(pszCommandLine);
//
//            return false;
//
//         }

         return true;

      }
      else
      {

         //call_async("/bin/bash", "-i -c 'xdg-open \"" + strTarget + "\"'", strFolder, SW_SHOWDEFAULT, false);

         //::system("nohup /bin/bash -l -c 'xdg-open \"" + strTarget + "\"' > /dev/null 2>&1&");

         //::system("nohup xdg-open \"" + strTarget + "\" > /dev/null 2>&1&");

         gdk_fork([strTarget]()
         {

            string strUri = strTarget;

            if(!strUri.contains("://"))
            {

               strUri = "file://" + strUri;

            }

            string strError;

            int iBufferSize = 4096;

            char * pszError = strError.get_buffer(iBufferSize);

            int iBool = aaa_gdk_launch_uri(strUri, pszError, iBufferSize);

            strError.release_buffer();

            if(!iBool)
            {

               _S_FORMATTED_TRACE("Error launching file : \"%s\" , %s", strUri.c_str(), strError.c_str());

            }

         });

      }

      return true;

   }


   void os_context::list_process(::file::path_array & patha, u32_array & uaPid)
   {

      ::output_debug_string("linux::os_context::list_process");

      ::file::path_array stra;

      ::dir::ls_dir(stra, "/proc/");

      for(auto & strPid : stra)
      {

         int iPid = atoi(strPid.title());

         if(iPid > 0)
         {

            ::file::path path = module_path_from_pid(iPid);

            if(path.has_char())
            {

               patha.add(path);

               uaPid.add(iPid);

            }

         }

      }

   }


} // namespace linux






