#pragma once


namespace linux
{


   class CLASS_DECL_ACME os_context :
      public ::os_context
   {
   public:


      os_context();
      virtual ~os_context();


      virtual string get_command_line() override;


      virtual bool reboot() override;
      virtual bool shutdown(bool bPowerOff) override;

      virtual void terminate_processes_by_title(const char * lpszName) override;


      //virtual ::file::path get_module_path(HMODULE hmodule) override;


      virtual bool get_pid_by_path(const char * lpszName, ::u32 & dwPid) override;
      virtual bool get_pid_by_title(const char * lpszName, ::u32 & dwPid) override;
      virtual void get_all_processes(u32_array & dwa) override;
      virtual ::file::path get_process_path(::u32 dwPid) override;
      virtual int get_pid() override;

      virtual ::payload connection_settings_get_auto_detect() override;
      virtual ::payload connection_settings_get_auto_config_url() override;


      virtual bool local_machine_set_run(const scoped_string & strKey, const scoped_string & strCommand);
      virtual bool local_machine_set_run_once(const scoped_string & strKey, const scoped_string & strCommand);
      virtual bool current_user_set_run(const scoped_string & strKey, const scoped_string & strCommand);
      virtual bool current_user_set_run_once(const scoped_string & strKey, const scoped_string & strCommand);
      virtual bool defer_register_ca2_plugin_for_mozilla() override;

      virtual bool file_extension_get_open_with_list_keys(string_array & straKey, const scoped_string & strExtension) override;
      virtual bool file_extension_get_open_with_list_commands(string_array & straCommand, const scoped_string & strExtension) override;

      virtual bool file_association_set_default_icon(const scoped_string & strExtension, const scoped_string & strExtensionNamingClass, const scoped_string & strIconPath) override;
      virtual bool file_association_set_shell_open_command(const scoped_string & strExtension, const scoped_string & strExtensionNamingClass,  const scoped_string & strCommand, const scoped_string & strParam) override;
      virtual bool file_association_get_shell_open_command(const scoped_string & strExtension, string & strExtensionNamingClass, string & strCommand, string & strParam) override;


      virtual bool open_in_ie(const char * pcsz);


      virtual bool create_service(::particle * pparticle);
      virtual bool erase_service(::particle * pparticle);

      virtual bool start_service(::particle * pparticle);
      virtual bool stop_service(::particle * pparticle);

      void raise_exception( ::u32 dwExceptionCode, ::u32 dwExceptionFlags);

      virtual bool is_remote_session() override;

      virtual void post_to_all_threads(const ::atom & atom, WPARAM wParam, LPARAM lParam);


      virtual bool initialize_wallpaper_fileset(::file::set * pfileset, bool bAddSearch) override;

      virtual bool get_default_browser(string & strId, ::file::path & path, string & strParam) override;

      virtual bool file_open(::file::path strSrc, string strParams, string strFolder) override;

      virtual void list_process(::file::path_array & patha, u32_array & iaPid) override;


   };


} // namespace linux



typedef string GET_FILE_CONTENT_TYPE(string strPath);

typedef GET_FILE_CONTENT_TYPE * PFN_GET_FILE_CONTENT_TYPE;

void set_get_file_content_type_function(PFN_GET_FILE_CONTENT_TYPE pfnGetFileContentType);

