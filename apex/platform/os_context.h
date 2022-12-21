#pragma once


////#include "acme/primitive/primitive/object.h"
//#include "acme/filesystem/filesystem/path.h"


class CLASS_DECL_APEX os_context :
   virtual public object
{
public:


   os_context();
   ~os_context() override;


   virtual string get_command_line();

   virtual void reboot();
   virtual void shutdown(bool bPowerOff);

   virtual void terminate_processes_by_title(const ::string & strName);

//#ifdef WINDOWS
//      virtual ::file::path get_module_path(HMODULE hmodule);
//#endif

   virtual bool path_pid(u32& dwPid, const ::string & strName);
   virtual bool title_pid(u32& dwPid, const ::string & strName);
   virtual void get_all_processes(u32_array & dwa);
   virtual ::file::path get_process_path(u32 dwPid);


   virtual int get_pid();

   virtual ::payload connection_settings_get_auto_detect();
   virtual ::payload connection_settings_get_auto_config_url();

   virtual void link_open(const string & strUrl, const string & strProfile);

   virtual void local_machine_set_run(const ::string & strKey, const ::string & strCommand, const ::string& strArguments, bool bSet);
   virtual void local_machine_set_run_once(const ::string & strKey, const ::string & strCommand, const ::string& strArguments, bool bSet);
   virtual void current_user_set_run(const ::string & strKey, const ::string & strCommand, const ::string & strArguments, bool bSet);
   virtual void current_user_set_run_once(const ::string & strKey, const ::string & strCommand, const ::string& strArguments, bool bSet);

   virtual void defer_register_ca2_plugin_for_mozilla();


   virtual void file_extension_get_open_with_list_keys(string_array & straKey, const ::string & strExtension);
   virtual void file_extension_get_open_with_list_commands(string_array & straCommand, const ::string & strExtension);

   virtual void file_association_set_default_icon(const ::string & strExtension, const ::string & strExtensionNamingClass, const ::string & strIconPath);
   virtual void file_association_set_shell_open_command(const ::string & strExtension, const ::string & strExtensionNamingClass, const ::string & strCommand, const ::string & strParam);
   virtual void file_association_get_shell_open_command(const ::string & strExtension, string & strExtensionNamingClass, string & strCommand, string & strParam);

   virtual void native_full_web_browser(const ::string & str);


   virtual void native_modern_web_browser(const ::string & str);


   virtual void enable_service();

   virtual void disable_service();

   virtual void start_service();

   virtual void stop_service();

   virtual void enable_service(const ::string & strServiceName, const ::string & strDisplayName, const ::string & strCommand, const ::string & strUser = "", const ::string & strPass = "");

   virtual void disable_service(const ::string & strServiceName);

   virtual void start_service(const ::string & strServiceName);

   virtual void stop_service(const ::string & strServiceName);

//#ifdef WINDOWS
//      virtual DECLSPEC_NO_RETURN void raise_exception(u32 dwExceptionCode, u32 dwExceptionFlags = EXCEPTION_NONCONTINUABLE);
//#endif

   virtual bool is_remote_session();

   virtual void set_file_status(const ::string & strFileName, const ::file::file_status& status);

   virtual void edit_link_target(const ::file::path & path, const ::file::path & pathLink);
   virtual void edit_link_folder(const ::file::path & path, const ::file::path & pathLink);
   virtual void edit_link_icon(const ::file::path& path, int iIcon, const ::file::path& pathLink);
   virtual bool resolve_link(::file::path & path, const ::string & strSource, string * pstrDirectory = nullptr, string * pstrParams = nullptr, string * pstrIcon = nullptr, int * piIcon = nullptr);
   virtual bool has_alias_in_path(const ::scoped_string & scopedstr, bool bNoUI = false, bool bNoMount = false);
   virtual bool is_alias(const ::scoped_string & scopedstr);

   virtual void initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch);

   virtual void set_dark_mode(bool bDarkMode);

   virtual void file_open(const ::file::path & path, const ::string & strParams = "", const ::file::path & pathFolder = "");
   virtual void hidden_start(const ::file::path& path, const ::string& strParams = "", const ::file::path& pathFolder = "");
   virtual void hidden_run(const class time & timeWait, const ::file::path& path, const ::string& strParams = "", const ::file::path& pathFolder = "");

   virtual string get_default_browser();

   virtual void get_default_browser(string & strId, ::file::path & path, string & strParam);

   virtual void set_default_browser();

   virtual void add_default_program(string_array & straExtension, string_array & straMimeType);

   virtual void register_user_auto_start(const string & strAppId, const string & strCommand, const string & strArguments, bool bRegister);

   virtual bool is_user_auto_start(const string & strAppId);

   virtual ::file::path get_app_path(const ::string & strApp);

   virtual void on_process_request(::request * prequest);

   /// set["file_filter_specs"] : string array of file extensions (with dot)
   /// set["file_filter_names"] : string array of the file extensions titles
   /// set["default_file_extension"] : default file extension (with dot)
   /// set["folder"] : folder path
   /// set["file_name"] : in/out file name
   virtual void browse_file_open(property_set & set);

   /// set["file_filter_specs"] : string array of extensions (with dot)
   /// set["file_filter_names"] : string array of the file extensions titles
   /// set["default_file_extension"] : default file extension (with dot)
   /// set["folder"] : folder path
   /// set["file_name"] : in/out file name
   virtual void browse_file_save(property_set & set);

   /// set["folder"] : in/out folder path
   virtual void browse_folder(property_set & set);

   /// set["folder"] : in/out folder path
   virtual void browse_file_or_folder(property_set & set);


   virtual void list_process(::file::path_array & patha, u32_array & uaPid);


   ::file::path_array list_process_path();

   //virtual ::icon_pointer load_icon(const ::payload & payloadFile);

   //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema);

   virtual void broadcast_environment_variable_change();


   virtual void set_this_application_as_default_for_file_extension(const ::string& strExtension);


};



