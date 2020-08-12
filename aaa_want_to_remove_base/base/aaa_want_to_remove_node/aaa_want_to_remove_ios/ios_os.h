#pragma once


namespace ios
{
   
   
   class CLASS_DECL_AURA os :
   public ::aura::os
   {
   public:
      
      
      os(::object * pobject);
      virtual ~os();
      
      
      virtual bool reboot();
      virtual bool shutdown(bool bPowerOff);
      
      virtual void terminate_processes_by_title(const char * pszName);
      virtual string get_module_path(HMODULE hmodule);
      virtual bool get_pid_by_path(const char * pszName, DWORD & dwPid);
      virtual bool get_pid_by_title(const char * pszName, DWORD & dwPid);
      virtual void get_all_processes(u32_array & dwa);
      virtual string get_process_path(DWORD dwPid);
      
      virtual bool connection_settings_get_auto_detect();
      virtual string connection_settings_get_auto_config_url();
      
      
      virtual bool local_machine_set_run(const char * pszKey, const char * pszCommand);
      virtual bool local_machine_set_run_once(const char * pszKey, const char * pszCommand);
      virtual bool current_user_set_run(const char * pszKey, const char * pszCommand);
      virtual bool current_user_set_run_once(const char * pszKey, const char * pszCommand);
      virtual bool defer_register_ca2_plugin_for_mozilla();
      
      virtual bool file_extension_get_open_with_list_keys(string_array & straKey, const char * pszExtension);
      virtual bool file_extension_get_open_with_list_commands(string_array & straCommand, const char * pszExtension);
      
      virtual bool file_association_set_default_icon(const char * pszExtension, const char * pszExtensionNamingClass, const char * pszIconPath);
      virtual bool file_association_set_shell_open_command(const char * pszExtension, const char * pszExtensionNamingClass,  const char * pszCommand, const char * pszParam);
      virtual bool file_association_get_shell_open_command(const char * pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam);
      
      
      virtual bool open_in_ie(const char * pcsz);
      
      virtual bool create_service(::object * pobject);
      virtual bool remove_service(::object * pobject);
      
      virtual bool start_service(::object * pobject);
      virtual bool stop_service(::object * pobject);
      
      virtual bool resolve_link(string & strTarget, string & strFolder, string & strParams, const string & pszSource, ::user::interaction * puiMessageParentOptional = nullptr);
      
      void raise_exception( DWORD dwExceptionCode, DWORD dwExceptionFlags);
      
      virtual bool is_remote_session();
      
      virtual void post_to_all_threads(UINT message, WPARAM wParam, LPARAM lParam);
      
      
   };
   
   
   
} // namespace ios




