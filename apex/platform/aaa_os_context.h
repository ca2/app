#pragma once

//
//////#include "acme/prototype/prototype/object.h"
////#include "acme/filesystem/filesystem/path.h"
//
//
//class get_file_extension_mime_type;
//
//
//class CLASS_DECL_APEX os_context :
//   virtual public object
//{
//public:
//
//
//   os_context();
//   ~os_context() override;
//
//
//   void finalize() override;
//
//   virtual string get_command_line();
//
//   virtual void reboot();
//   virtual void shutdown(bool bPowerOff);
//
//   virtual void terminate_processes_by_title(const ::scoped_string & scopedstrName);
//
////#ifdef WINDOWS
////      virtual ::file::path get_module_path(HMODULE hmodule);
////#endif
//
//   virtual ::process_identifier_array module_path_processes_identifiers(const ::scoped_string & scopedstrName);
//   virtual ::process_identifier_array title_processes_identifiers(const ::scoped_string & scopedstrName);
//   virtual ::process_identifier_array processes_identifiers();
//   virtual ::file::path process_identifier_module_path(::process_identifier dwPid);
//
//
//   virtual ::process_identifier current_process_identifier();
//
//   virtual ::payload connection_settings_get_auto_detect();
//   virtual ::payload connection_settings_get_auto_config_url();
//
//   virtual void link_open(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile);
//
//   virtual void local_machine_set_run(const ::scoped_string & scopedstrKey, const ::file::path & pathExecutable, const ::scoped_string & scopedstrArguments, bool bSet);
//   virtual void local_machine_set_run_once(const ::scoped_string & scopedstrKey, const ::file::path & pathExecutable, const ::scoped_string & scopedstrArguments, bool bSet);
//   virtual void current_user_set_run(const ::scoped_string & scopedstrKey, const ::file::path & pathExecutable, const ::scoped_string & scopedstrArguments, bool bSet);
//   virtual void current_user_set_run_once(const ::scoped_string & scopedstrKey, const ::file::path & pathExecutable, const ::scoped_string & scopedstrArguments, bool bSet);
//
//   virtual void defer_register_ca2_plugin_for_mozilla();
//
//
//   virtual void file_extension_get_open_with_list_keys(string_array_base & straKey, const ::scoped_string & scopedstrExtension);
//   virtual void file_extension_get_open_with_list_commands(string_array_base & straCommand, const ::scoped_string & scopedstrExtension);
//
//   virtual void file_association_set_default_icon(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass, const ::scoped_string & scopedstrIconPath);
//   virtual void file_association_set_shell_open_command(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass, const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrParam);
//   virtual void file_association_get_shell_open_command(const ::scoped_string & scopedstrExtension, string & strExtensionNamingClass, string & strCommand, string & strParam);
//
//   virtual void native_full_web_browser(const ::scoped_string & scopedstr);
//
//
//   virtual void native_modern_web_browser(const ::scoped_string & scopedstr);
//
//
//   virtual void enable_service();
//
//   virtual void disable_service();
//
//   virtual void start_service();
//
//   virtual void stop_service();
//
//   virtual void enable_service(const ::scoped_string & scopedstrServiceName, const ::scoped_string & scopedstrDisplayName, const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrUser = "", const ::scoped_string & scopedstrPass = "");
//
//   virtual void disable_service(const ::scoped_string & scopedstrServiceName);
//
//   virtual void start_service(const ::scoped_string & scopedstrServiceName);
//
//   virtual void stop_service(const ::scoped_string & scopedstrServiceName);
//
////#ifdef WINDOWS
////      virtual DECLSPEC_NO_RETURN void raise_exception(unsigned int dwExceptionCode, unsigned int dwExceptionFlags = EXCEPTION_NONCONTINUABLE);
////#endif
//
//   virtual bool is_remote_session();
//
//   virtual void set_file_status(const ::file::path & path, const ::file::file_status& status);
//
//   //virtual void edit_link_target(const ::file::path & path, const ::file::path & pathLink);
//   //virtual void edit_link_folder(const ::file::path & path, const ::file::path & pathLink);
//   //virtual void edit_link_icon(const ::file::path& path, int iIcon, const ::file::path& pathLink);
////   virtual ::pointer < ::file::link > resolve_link(const ::file::path & path, ::file::e_link elink = ::file::e_link_all);
//   virtual bool has_alias_in_path(const ::scoped_string & scopedstr, bool bNoUI = false, bool bNoMount = false);
//   virtual bool is_alias(const ::file::path & path);
//
//   virtual void initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch);
//
//   virtual void set_dark_mode(bool bDarkMode);
//
//   virtual void file_open(const ::file::path & path, const ::scoped_string & scopedstrParams = "", const ::file::path & pathFolder = "");
//   virtual void hidden_start(const ::file::path& path, const ::scoped_string & scopedstrParams = "", const ::file::path& pathFolder = "");
//   virtual void hidden_run(const class time & timeWait, const ::file::path& path, const ::scoped_string & scopedstrParams = "", const ::file::path& pathFolder = "");
//
//   virtual string get_default_browser();
//
//   virtual void get_default_browser(string & strId, ::file::path & path, string & strParam);
//
//   virtual void set_default_browser();
//
//   virtual void set_file_extension_mime_type(::get_file_extension_mime_type * pgetfileextensionmimetype);
//
//   virtual void set_file_extension_mime_type(string_array_base & straExtension, string_array_base & straMimeType);
//
//   virtual void register_user_auto_start(const ::scoped_string & scopedstrAppId, const ::file::path & pathExecutable, const ::scoped_string & scopedstrArguments, bool bRegister);
//
//   virtual bool is_user_auto_start(const ::scoped_string & scopedstrAppId);
//
//   virtual ::file::path get_app_path(const ::scoped_string & scopedstrApp);
//
//   virtual void on_process_request(::request * prequest);
//
//   /// set["file_filter_specs"] : string array of file extensions (with dot)
//   /// set["file_filter_names"] : string array of the file extensions titles
//   /// set["default_file_extension"] : default file extension (with dot)
//   /// set["folder"] : folder path
//   /// set["file_name"] : in/out file name
//   //virtual void browse_file_open(::property_set & set);
//
//   /// set["file_filter_specs"] : string array of extensions (with dot)
//   /// set["file_filter_names"] : string array of the file extensions titles
//   /// set["default_file_extension"] : default file extension (with dot)
//   /// set["folder"] : folder path
//   /// set["file_name"] : in/out file name
//   //virtual void browse_file_save(::property_set & set);
//
//   /// set["folder"] : in/out folder path
//   //virtual void browse_folder(::property_set & set);
//
//   /// set["folder"] : in/out folder path
//   //virtual void browse_file_or_folder(::property_set & set);
//
//
//   virtual void list_process(::file::path_array & patha, ::process_identifier_array& uaPid);
//
//
//   ::file::path_array list_process_path();
//
//   //virtual ::icon_pointer load_icon(const ::payload & payloadFile);
//
//   //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema);
//
//   virtual void broadcast_environment_variable_change();
//
//
//   virtual void set_this_application_as_default_for_file_extension(const ::scoped_string & scopedstrExtension);
//
//
//   string get_file_extension_mime_type(const ::scoped_string & scopedstrExtension);
//
//
//};
//


