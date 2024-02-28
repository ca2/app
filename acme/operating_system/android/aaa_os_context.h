#pragma once


namespace android
{


   class CLASS_DECL_ACME os_context :
      public ::os_context
   {
   public:


      os_context();
      virtual ~os_context();


      virtual bool reboot() override;
      virtual bool shutdown(bool bPowerOff) override;

      virtual void terminate_processes_by_title(const ::scoped_string & scopedstrName) override;
      virtual bool get_pid_by_path(const ::scoped_string & scopedstrName, ::u32 & dwPid) override;
      virtual bool get_pid_by_title(const ::scoped_string & scopedstrName, ::u32 & dwPid) override;
      virtual int get_pid() override;
      virtual void get_all_processes(::u32_array & dwa) override;
      virtual ::file::path get_process_path(::u32 dwPid) override;

      virtual ::payload connection_settings_get_auto_detect() override;
      virtual ::payload connection_settings_get_auto_config_url() override;


      virtual bool local_machine_set_run(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand, bool bSet) override;
      virtual bool local_machine_set_run_once(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand, bool bSet) override;
      virtual bool current_user_set_run(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand, bool bSet) override;
      virtual bool current_user_set_run_once(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand, bool bSet) override;
      virtual bool defer_register_ca2_plugin_for_mozilla() override;

      virtual bool file_extension_get_open_with_list_keys(string_array & straKey, const ::scoped_string & scopedstrExtension) override;
      virtual bool file_extension_get_open_with_list_commands(string_array & straCommand, const ::scoped_string & scopedstrExtension) override;

      virtual bool file_association_set_default_icon(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass, const ::scoped_string & scopedstrIconPath) override;
      virtual bool file_association_set_shell_open_command(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass,  const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrParam) override;
      virtual bool file_association_get_shell_open_command(const ::scoped_string & scopedstrExtension, string & strExtensionNamingClass, string & strCommand, string & strParam) override;


      virtual bool native_full_web_browser(const ::scoped_string & scopedstr) override;
      virtual bool native_modern_web_browser(const ::scoped_string & scopedstr) override;

      virtual void create_service() override;
      virtual void erase_service() override;

      virtual void start_service() override;
      virtual void stop_service() override;


      virtual bool is_remote_session() override;

      virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema) override;

      //virtual void post_to_all_threads(const ::atom & atom, WPARAM wParam, LPARAM lParam) override;

   };


} // namespace android




