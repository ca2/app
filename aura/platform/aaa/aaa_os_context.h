#pragma once
//#ifndef AXIS_AXIS_CORE_OS_H
//#define AXIS_AXIS_CORE_OS_H


//namespace aura
//{


   class CLASS_DECL_AURA os_context :
      virtual public object
   {
   public:
      

      os_context();
      virtual ~os_context();


      virtual string get_command_line();

      virtual bool reboot();
      virtual bool shutdown(bool bPowerOff);

      virtual void terminate_processes_by_title(const char * lpszName);

#ifdef WINDOWS
      virtual ::file::path get_module_path(HMODULE hmodule);
#endif

      virtual bool get_pid_by_path(const char * lpszName, u32 & dwPid);
      virtual bool get_pid_by_title(const char * lpszName, u32 & dwPid);
      virtual void get_all_processes(u32_array & dwa);
      virtual ::file::path get_process_path(u32 dwPid);

      virtual int get_pid();

      virtual ::payload connection_settings_get_auto_detect();
      virtual ::payload connection_settings_get_auto_config_url();

      virtual ::e_status     link_open(string strUrl);

      virtual bool local_machine_set_run(const char * pszKey, const char * pszCommand, bool bSet);
      virtual bool local_machine_set_run_once(const char * pszKey, const char * pszCommand, bool bSet);
      virtual bool current_user_set_run(const char * pszKey, const char * pszCommand, bool bSet);
      virtual bool current_user_set_run_once(const char * pszKey, const char * pszCommand, bool bSet);

      virtual bool defer_register_ca2_plugin_for_mozilla();


      virtual bool file_extension_get_open_with_list_keys(string_array & straKey, const char * pszExtension);
      virtual bool file_extension_get_open_with_list_commands(string_array & straCommand, const char * pszExtension);

      virtual bool file_association_set_default_icon(const char * pszExtension, const char * pszExtensionNamingClass, const char * pszIconPath);
      virtual bool file_association_set_shell_open_command(const char * pszExtension, const char * pszExtensionNamingClass, const char * pszCommand, const char * pszParam);
      virtual bool file_association_get_shell_open_command(const char * pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam);

      virtual bool native_full_web_browser(const char * pcsz);


      virtual bool native_modern_web_browser(const char * pcsz);


      virtual ::e_status create_service();

      virtual ::e_status erase_service();

      virtual ::e_status start_service();

      virtual ::e_status stop_service();

      virtual bool create_service(const string & strServiceName, const string & strDisplayName, const string & strCommand, const string & strUser = "", const string & strPass = "");

      virtual bool erase_service(const string & strServiceName);

      virtual bool start_service(const string & strServiceName);

      virtual bool stop_service(const string & strServiceName);

#ifdef WINDOWS
      virtual DECLSPEC_NO_RETURN void raise_exception(u32 dwExceptionCode, u32 dwExceptionFlags = EXCEPTION_NONCONTINUABLE);
#endif

      virtual bool is_remote_session();

      virtual void set_file_status(const char * pszFileName, const ::file::file_status& status);


      virtual bool resolve_link(::file::path & path, const string & strSource, string * pstrDirectory = nullptr, string * pstrParams = nullptr, ::user::primitive * puiMessageParentOptional = nullptr);

      virtual bool initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch);

      virtual bool file_open(::file::path path, string strParams = "", string strFolder = "");

      virtual string get_default_browser();

      virtual bool get_default_browser(string & strId, ::file::path & path, string & strParam);

      virtual bool set_default_browser();

      virtual bool add_default_program(string_array & straExtension, string_array & straMimeType);

      virtual bool register_user_auto_start(string strId, string strCommand, bool bRegister);

      virtual bool is_user_auto_start(string strId);

      virtual ::file::path get_app_path(const string & strApp);

      virtual void on_process_command(::create * pcommand);

      /// set["file_filter_specs"] : string array of file extensions (with dot)
      /// set["file_filter_names"] : string array of the file extensions titles
      /// set["default_file_extension"] : default file extension (with dot)
      /// set["folder"] : folder path
      /// set["file_name"] : in/out file name
      virtual bool browse_file_open(::user::interaction* pinteraction, property_set & set);

      /// set["file_filter_specs"] : string array of extensions (with dot)
      /// set["file_filter_names"] : string array of the file extensions titles
      /// set["default_file_extension"] : default file extension (with dot)
      /// set["folder"] : folder path
      /// set["file_name"] : in/out file name
      virtual bool browse_file_save(::user::interaction* pinteraction, property_set & set);

      /// set["folder"] : in/out folder path
      virtual bool browse_folder(::user::interaction* pinteraction, property_set & set);

      /// set["folder"] : in/out folder path
      virtual bool browse_file_or_folder(::user::interaction* pinteraction, property_set & set);


      virtual void list_process(::file::patha & patha, u32_array & uaPid);


      ::file::patha list_process_path();

      virtual ::icon_result load_icon(const ::payload & varFile);

      virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema);


   };

   //typedef pointer < os > os_pointer;


//} // namespace aura
//
//
//#endif // AXIS_AXIS_CORE_OS_H
//
//








