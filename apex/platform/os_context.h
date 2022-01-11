#pragma once


class CLASS_DECL_APEX os_context :
   virtual public object
{
public:


   os_context();
   ~os_context() override;


   virtual string get_command_line();

   virtual bool reboot();
   virtual bool shutdown(bool bPowerOff);

   virtual void terminate_processes_by_title(const ::string & strName);

//#ifdef WINDOWS
//      virtual ::file::path get_module_path(HMODULE hmodule);
//#endif

   virtual bool get_pid_by_path(const ::string & strName, u32 & dwPid);
   virtual bool get_pid_by_title(const ::string & strName, u32 & dwPid);
   virtual void get_all_processes(u32_array & dwa);
   virtual ::file::path get_process_path(u32 dwPid);

   virtual int get_pid();

   virtual ::payload connection_settings_get_auto_detect();
   virtual ::payload connection_settings_get_auto_config_url();

   virtual void link_open(const string & strUrl, const string & strProfile);

   virtual bool local_machine_set_run(const ::string & strKey, const ::string & strCommand, const ::string& strArguments, bool bSet);
   virtual bool local_machine_set_run_once(const ::string & strKey, const ::string & strCommand, const ::string& strArguments, bool bSet);
   virtual bool current_user_set_run(const ::string & strKey, const ::string & strCommand, const ::string & strArguments, bool bSet);
   virtual bool current_user_set_run_once(const ::string & strKey, const ::string & strCommand, const ::string& strArguments, bool bSet);

   virtual bool defer_register_ca2_plugin_for_mozilla();


   virtual bool file_extension_get_open_with_list_keys(string_array & straKey, const ::string & strExtension);
   virtual bool file_extension_get_open_with_list_commands(string_array & straCommand, const ::string & strExtension);

   virtual bool file_association_set_default_icon(const ::string & strExtension, const ::string & strExtensionNamingClass, const ::string & strIconPath);
   virtual bool file_association_set_shell_open_command(const ::string & strExtension, const ::string & strExtensionNamingClass, const ::string & strCommand, const ::string & strParam);
   virtual bool file_association_get_shell_open_command(const ::string & strExtension, string & strExtensionNamingClass, string & strCommand, string & strParam);

   virtual bool native_full_web_browser(const ::string & str);


   virtual bool native_modern_web_browser(const ::string & str);


   virtual void enable_service();

   virtual void disable_service();

   virtual void start_service();

   virtual void stop_service();

   virtual bool enable_service(const ::string & strServiceName, const ::string & strDisplayName, const ::string & strCommand, const ::string & strUser = "", const ::string & strPass = "");

   virtual bool disable_service(const ::string & strServiceName);

   virtual bool start_service(const ::string & strServiceName);

   virtual bool stop_service(const ::string & strServiceName);

//#ifdef WINDOWS
//      virtual DECLSPEC_NO_RETURN void raise_exception(u32 dwExceptionCode, u32 dwExceptionFlags = EXCEPTION_NONCONTINUABLE);
//#endif

   virtual bool is_remote_session();

   virtual void set_file_status(const ::string & strFileName, const ::file::file_status& status);


   virtual bool resolve_link(::file::path & path, const ::string & strSource, string * pstrDirectory = nullptr, string * pstrParams = nullptr);

   virtual bool initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch);

   virtual void set_dark_mode(bool bDarkMode);

   virtual bool file_open(::file::path path, string strParams = "", string strFolder = "");

   virtual string get_default_browser();

   virtual bool get_default_browser(string & strId, ::file::path & path, string & strParam);

   virtual bool set_default_browser();

   virtual bool add_default_program(string_array & straExtension, string_array & straMimeType);

   virtual bool register_user_auto_start(const string & strId, const string & strCommand, const string & strArguments, bool bRegister);

   virtual bool is_user_auto_start(string strId);

   virtual ::file::path get_app_path(const ::string & strApp);

   virtual void on_process_command(::create * pcommand);

   /// set["file_filter_specs"] : string array of file extensions (with dot)
   /// set["file_filter_names"] : string array of the file extensions titles
   /// set["default_file_extension"] : default file extension (with dot)
   /// set["folder"] : folder path
   /// set["file_name"] : in/out file name
   virtual bool browse_file_open(property_set & set);

   /// set["file_filter_specs"] : string array of extensions (with dot)
   /// set["file_filter_names"] : string array of the file extensions titles
   /// set["default_file_extension"] : default file extension (with dot)
   /// set["folder"] : folder path
   /// set["file_name"] : in/out file name
   virtual bool browse_file_save(property_set & set);

   /// set["folder"] : in/out folder path
   virtual bool browse_folder(property_set & set);

   /// set["folder"] : in/out folder path
   virtual bool browse_file_or_folder(property_set & set);


   virtual void list_process(::file::patha & patha, u32_array & uaPid);


   ::file::patha list_process_path();

   //virtual ::icon_transport load_icon(const ::payload & payloadFile);

   //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema);

   virtual void broadcast_environment_variable_change();


};



