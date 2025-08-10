#pragma once


namespace ios
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

      virtual void terminate_processes_by_title(const ::scoped_string & scopedstrName) override;
      virtual string get_module_path(HMODULE hmodule);
      virtual bool get_pid_by_path(const ::scoped_string & scopedstrName, unsigned int & dwPid) override;
      virtual bool get_pid_by_title(const ::scoped_string & scopedstrName, unsigned int & dwPid) override;
      virtual int get_pid() override;
      virtual void get_all_processes(unsigned_int_array & dwa) override;
      virtual ::file::path get_process_path(unsigned int dwPid) override;

      virtual ::payload connection_settings_get_auto_detect() override;
      virtual ::payload connection_settings_get_auto_config_url() override;


      virtual bool local_machine_set_run(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand);
      virtual bool local_machine_set_run_once(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand);
      virtual bool current_user_set_run(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand);
      virtual bool current_user_set_run_once(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand);
      virtual bool defer_register_ca2_plugin_for_mozilla() override;

      virtual bool file_extension_get_open_with_list_keys(string_array_base & straKey, const ::scoped_string & scopedstrExtension) override;
      virtual bool file_extension_get_open_with_list_commands(string_array_base & straCommand, const ::scoped_string & scopedstrExtension) override;

      virtual bool file_association_set_default_icon(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass, const ::scoped_string & scopedstrIconPath) override;
      virtual bool file_association_set_shell_open_command(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass,  const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrParam) override;
      virtual bool file_association_get_shell_open_command(const ::scoped_string & scopedstrExtension, string & strExtensionNamingClass, string & strCommand, string & strParam) override;


      virtual bool open_in_ie(const ::scoped_string & scopedstr);

      virtual void create_service() override;
      virtual void erase_service() override;

      virtual void start_service() override;
      virtual void stop_service() override;

      void raise_exception( unsigned int dwExceptionCode, unsigned int dwExceptionFlags);

      virtual bool is_remote_session() override;

      virtual void post_to_all_threads(::enum_message emessage, ::wparam wparam, ::lparam lparam);


      virtual bool file_open(const ::file::path & path, string strParams, string strFolder) override;


      virtual bool initialize_wallpaper_fileset(::file::set * pfileset, bool bAddSearch) override;

   };


} // namespace ios



