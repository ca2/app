#include "framework.h"
#include "_android.h"
#include "acme/platform/static_start.h"
//#include "acme/xml/_.h"
#include "acme/graphics/draw2d/ttf_util.h"


#undef USERNAME_LENGTH // mysql one




namespace android
{


   os_context::os_context()
   {
   }


   os_context::~os_context()
   {
   }


   bool os_context::shutdown(bool bIfPowerOff)
   {
      /*      bool retval = true;
            HANDLE hToken;
            TOKEN_PRIVILEGES tokenprivileges;
            if (!OpenProcessToken(GetCurrentProcess(),
               TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
               return false;
            LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tokenprivileges.Privileges[0].Luid);
            tokenprivileges.PrivilegeCount = 1;
            tokenprivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
            if (bIfPowerOff)
               retval = ExitWindowsEx(EWX_POWEROFF, 0) != false;
            else
               retval = ExitWindowsEx(EWX_SHUTDOWN, 0) != false;

            //reset the previlages
            tokenprivileges.Privileges[0].Attributes = 0;
            AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
            return retval;*/

      throw ::interface_only();
      return false;

   }

   bool os_context::reboot()
   {
      /*      HANDLE hToken;
            TOKEN_PRIVILEGES tokenprivileges;
            if (!OpenProcessToken(GetCurrentProcess(),
               TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
               return false;
            if(!LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tokenprivileges.Privileges[0].Luid))
            {
               TRACELASTERROR();
               return false;
            }
            tokenprivileges.PrivilegeCount = 1;
            tokenprivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            if(!AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0))
            {
               TRACELASTERROR();
               return false;
            }
            if (get_last_error() == ERROR_NOT_ALL_ASSIGNED)
            {
               return false;
            }
            if(!LookupPrivilegeValue(nullptr, SE_REMOTE_SHUTDOWN_NAME, &tokenprivileges.Privileges[0].Luid))
            {
               TRACELASTERROR();
               return false;
            }
            tokenprivileges.PrivilegeCount = 1;
            tokenprivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            if(!AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0))
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
            /*if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE,
            SHTDN_REASON_MAJOR_SOFTWARE | SHTDN_REASON_MINOR_INSTALLATION))
            {
            ::u32 dwLastError = ::get_last_error();
            return false;
            }*/
      //reset the previlages
      /*    tokenprivileges.Privileges[0].Attributes = 0;
          AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
          return true;*/
      throw ::interface_only();
      return false;

   }

   void os_context::terminate_processes_by_title(const ::scoped_string & scopedstrName)
   {
      throw ::interface_only();
      return;

      /*      ::u32 dwPid;
            while(get_pid_by_title(pszName, dwPid))
            {
               HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                  PROCESS_VM_READ,
                  false, dwPid );
               TerminateProcess(hProcess, (::u32) -1);
               CloseHandle(hProcess);
               /*::EnumWindows((WNDENUMPROC)
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

   bool os_context::get_pid_by_path(const ::scoped_string & scopedstrName, ::u32 & dwPid)
   {
      ::u32_array dwa;
      get_all_processes(dwa);
      for(i32 i = 0; i < dwa.get_count(); i++)
      {
         if(get_process_path(dwa[i]).case_insensitive_order(pszName) == 0)
         {
            dwPid = dwa[i];
            return true;
         }
      }
      return false;
   }

   bool os_context::get_pid_by_title(const ::scoped_string & scopedstrName, ::u32 & dwPid)
   {
      ::u32_array dwa;
      get_all_processes(dwa);
      for(i32 i = 0; i < dwa.get_count(); i++)
      {
         if(get_process_path(dwa[i]).title().case_insensitive_order(pszName) == 0)
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
      throw ::interface_only();
      return "";

   }

   void os_context::get_all_processes(::u32_array & dwa )
   {

      throw ::interface_only();
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



   ::payload os_context::connection_settings_get_auto_detect()
   {
      //throw ::interface_only();
      return false;

      /*
            registry::Key key1;

            key1.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Connections", false);

            memory mem;

            key1.QueryValue("DefaultConnectionSettings", mem);

            bool bAutoDetect = (((LPBYTE) mem.get_data())[8] & 0x08) != 0;

            return bAutoDetect;
      */
   }



   ::payload os_context::connection_settings_get_auto_config_url()
   {

      //throw ::interface_only();
      return "";
      /*
            registry::Key key;

            key.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", false);

            string strUrl;

            key.QueryValue("AutoConfigURL", strUrl);

            return strUrl;
      */
   }

   bool os_context::local_machine_set_run(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand, bool bSet)
   {

//      throw ::interface_only();
      return false;

      /*
            registry::Key keyKar(HKEY_LOcaL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);


            keyKar.SetValue(pszKey, pszCommand);


            return true;
      */
   }


   bool os_context::local_machine_set_run_once(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand, bool bSet)
   {


      throw ::interface_only();
      return false;
      /*    registry::Key keyKar(HKEY_LOcaL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);


            keyKar.SetValue(pszKey, pszCommand);
      */

      return false;

   }

   bool os_context::current_user_set_run(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand, bool bSet)
   {

      throw ::interface_only();
      return false;

      /*
            registry::Key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);


            keyKar.SetValue(pszKey, pszCommand);
      */

      return false;

   }

   bool os_context::current_user_set_run_once(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand, bool bSet)
   {

      throw ::interface_only();
      return false;

      /*
            registry::Key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);


            keyKar.SetValue(pszKey, pszCommand);

      */
      return false;

   }


   bool os_context::defer_register_ca2_plugin_for_mozilla()
   {
      //  throw ::interface_only();
      return false;

      /*
            registry::Key keyPlugins;

            if(keyPlugins.OpenKey(HKEY_LOcaL_MACHINE, "SOFTWARE\\MozillaPlugins", true))
            {

               registry::Key keyPlugin;

               if(keyPlugin.OpenKey(keyPlugins, "@ca2.software/npca2", true))
               {

                  keyPlugin.SetValue("Description", "ca2 plugin for NPAPI");
                  keyPlugin.SetValue("Path", ::acmeacmesystem()->m_strCa2Module("npca2.dll"));
                  keyPlugin.SetValue("ProductName", "ca2 plugin for NPAPI");
                  keyPlugin.SetValue("Vendor", "ca2 Desenvolvimento de Software Ltda.");
                  keyPlugin.SetValue("Version", papp->file_system()->as_string(directory()->ca2("appdata/x86/ca2_build.txt")));

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

   bool os_context::file_extension_get_open_with_list_keys(string_array & straKey, const ::scoped_string & scopedstrExtension)
   {
      throw ::interface_only();
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


   bool os_context::file_extension_get_open_with_list_commands(string_array & straCommand, const ::scoped_string & scopedstrExtension)
   {

      string_array straKey;

      if(!file_extension_get_open_with_list_keys(straKey, pszExtension))
         return false;


      return true;

   }

   bool os_context::file_association_set_default_icon(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass, const ::scoped_string & scopedstrIconPath)
   {

      throw ::interface_only();
      return false;

      /*
            string strExtensionNamingClass(pszExtensionNamingClass);

            registry::Key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass, true);
            keyLink3.SetValue("DefaultIcon", pszIconPath);


            return false;
      */
   }


   bool os_context::file_association_set_shell_open_command(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass,  const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrParam)
   {
      throw ::interface_only();
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
            strFormat.formatf("\"%s\" \"%%L\" %s", pszCommand, pszParam);
            keyLink1.SetValue(nullptr, strFormat);

            return true;
      */
   }

   bool os_context::file_association_get_shell_open_command(const ::scoped_string & scopedstrExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
   {
      throw ::interface_only();
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

   bool os_context::native_modern_web_browser(const char * lpcsz)
   {

      throw ::interface_only();
      return false;
   }


   bool os_context::native_full_web_browser(const char * lpcsz)
   {

      throw ::interface_only();
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
                        strCommand.replace("%1", lpcsz);
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
                              strCommand.replace("%1", lpcsz);
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

   void os_context::create_service()
   {

      //throw ::interface_only();
      return error_failed;


   }


   void os_context::erase_service()
   {
//      throw ::interface_only();
      return error_failed;

   }

   void os_context::start_service()
   {
      //throw ::interface_only();
      return error_failed;

   }

   void os_context::stop_service()
   {
      throw ::interface_only();
      return error_failed;

   }


   //void os_context::raise_exception( ::u32 dwExceptionCode, ::u32 dwExceptionFlags)
   //{

   //   throw ::interface_only();
   //   return;
   //   /*
   //         RaiseException( dwExceptionCode, dwExceptionFlags, 0, nullptr );
   //         */
   //}

   bool os_context::is_remote_session()
   {

//      throw ::interface_only();
      return false;
      /*
            return GetSystemMetrics(SM_REMOTESESSION) != false;
      */
   }


   //void os_context::post_to_all_threads(const ::atom & atom, WPARAM wparam, LPARAM lparam)
   //{

   //   throw ::interface_only();
   //   return;


   //}

   void os_context::enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema)
   {

      cslock synchronouslock(::acme::g_pcsFont);

      ::pointer<::write_text::font_enumeration_item>pitem;

      double dAndroid = 4.4;

      string strSystemFonts = file()->as_string("/system/etc/system_fonts.xml");

            auto psystem = system();

      auto pxml = psystem->xml();

      auto pdoc = pxml->create_document();

      ::pointer<ttf_util>putil;

      ::e_status estatus = __construct_new(putil);

      if (pdoc->load(strSystemFonts))
      {

         ::collection::index iFamilyPos = 0;

         while (auto pfamily = pdoc->root()->get_child("family", iFamilyPos))
         {

            if (iFamilyPos < 0)
            {

               break;

            }

            iFamilyPos++;

            if (pfamily->get_name() == "family")
            {

               ::collection::index iNamesetPos = 0;

               auto pnameset = pfamily->get_child("nameset", iNamesetPos);

               ::collection::index iFilesetPos = 0;

               auto pfileset = pfamily->get_child("fileset", iFilesetPos);

               if (pnameset && pfileset)
               {

                  if (pnameset->get_children_count() >= 1 && pfileset->get_children_count() >= 1)
                  {

                     ::collection::index iNamePos = 0;

                     auto pfirstname = pnameset->get_child("name", iNamePos);

                     ::collection::index iFilePos = 0;

                     auto pfirstfile = pfileset->get_child("file", iFilePos);

                     if (pfirstname && pfirstfile)
                     {

                        string strName = pfirstname->get_value();

                        string strFile = pfirstfile->get_value();

                        ::file::path path = "/system/fonts";

                        path /= strFile;

                        pitem = __allocate ::write_text::font_enumeration_item();

                        if (::file_system()->exists(path))
                        {

                           pitem->m_strFile = path;

                        }
                        else
                        {

                           pitem->m_strFile = strFile;

                        }

                        pitem->m_strName = strName;

                        itema.add(pitem);

                        ::acme::g_pmapFontFaceName->set_at(strName, pitem->m_strFile);

                     }

                  }

               }

            }

         }

      }

      if (dAndroid >= 8.0)
      {

         ::file::path_array patha;

         ::dir::ls(patha, "/system/fonts");

         if(estatus.succeeded())
         {

            for (auto& path : patha)
            {

               pitem = __allocate ::write_text::font_enumeration_item();

               pitem->m_strFile = path;

               string strName = putil->GetFontNameFromFile(path);

               if (strName.is_empty())
               {

                  strName = path.title();

               }

               pitem->m_strName = strName;

               itema.add(pitem);

               ::acme::g_pmapFontFaceName->set_at(strName, path);

            }

         }

      }

      if (itema.isEmpty())
      {


#ifdef pnode->font_name(e_font_mono)

         pitem = __allocate ::write_text::font_enumeration_item();

         pitem->m_strFile = pnode->font_name(e_font_mono);

         pitem->m_strName = pnode->font_name(e_font_mono);

         itema.add(pitem);

#endif


#ifdef pnode->font_name(e_font_sans)

         pitem = __allocate ::write_text::font_enumeration_item();

         pitem->m_strFile = pnode->font_name(e_font_sans);

         pitem->m_strName = pnode->font_name(e_font_sans);

         itema.add(pitem);

#endif


#ifdef pnode->font_name(e_font_serif)

         pitem = __allocate ::write_text::font_enumeration_item();

         pitem->m_strFile = pnode->font_name(e_font_serif);

         pitem->m_strName = pnode->font_name(e_font_serif);

         itema.add(pitem);

#endif


#ifdef pnode->font_name(e_font_sans_ex)

         pitem = __allocate ::write_text::font_enumeration_item();

         pitem->m_strFile = pnode->font_name(e_font_sans_ex);

         pitem->m_strName = pnode->font_name(e_font_sans_ex);

         itema.add(pitem);

#endif


#ifdef pnode->font_name(e_font_serif_ex)

         pitem = __allocate ::write_text::font_enumeration_item();

         pitem->m_strFile = pnode->font_name(e_font_serif_ex);

         pitem->m_strName = pnode->font_name(e_font_serif_ex);

         itema.add(pitem);

#endif


#ifdef pnode->font_name(e_font_sans_fx)

         pitem = __allocate ::write_text::font_enumeration_item();

         pitem->m_strFile = pnode->font_name(e_font_sans_fx);

         pitem->m_strName = pnode->font_name(e_font_sans_fx);

         itema.add(pitem);

#endif


#ifdef pnode->font_name(e_font_serif_fx)

         pitem = __allocate ::write_text::font_enumeration_item();

         pitem->m_strFile = pnode->font_name(e_font_serif_fx);

         pitem->m_strName = pnode->font_name(e_font_serif_fx);

         itema.add(pitem);

#endif


#ifdef FONT_SANS_FX2

         pitem = __allocate ::write_text::font_enumeration_item();

         pitem->m_strFile = FONT_SANS_FX2;

         pitem->m_strName = FONT_SANS_FX2;

         itema.add(pitem);

#endif


      }

   }


} // namespace android






