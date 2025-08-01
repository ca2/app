//
// Created by camilo on 2024-10-24 22:12 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace platform
{


   struct CLASS_DECL_ACME apex_node_layer_t
   {


      ::set < ::channel * >         m_setChannelSystemOptionsHtml;
      //::apex::node*                 m_papexnode;
      //::aura::node*                 m_pauranode;


   };


   class CLASS_DECL_ACME apex_node_layer
   {
   public:

// #ifdef _DEBUG
//
//
//       long long increment_reference_count() override;
//
//
//       long long decrement_reference_count() override;
//
//
// #endif


      //virtual void on_initialize_particle() override;


      //virtual void main();


      virtual ::string system_options_html();

      virtual ::string system_options_main_body();


      //virtual void defer_create_main_menu(const string_array & straParent, const string_array & straMenu, const string_array & straId);


//      virtual void set_main_menu(application_menu * pmenu, ::apex::application * papp);


      virtual ::file::path get_desktop_file_path(::apex::application * papp);


      //virtual void defer_notify_startup_complete();


      //void start_node() override;


      //void application_handle(long long l, void * p) override;


      // void on_operating_system_user_theme_change() override;
      //
      //
      // void on_operating_system_user_color_change() override;
      //
      //
      // void on_operating_system_font_list_change() override;


      virtual void defer_innate_ui();


      virtual void shell_create_link(::file::path pathObj, ::file::path pathLnk, const ::scoped_string & scopedstrDesc, ::file::path pathIco = "", int iIcon = -1);

      virtual bool shell_link_target(::file::path & pathTarget, const ::file::path & pathLnk);
      virtual bool shell_link_icon(::file::path & pathIcon, int & iIcon, const ::file::path& pathLnk);


      //virtual void parallelization_initialize();
      //virtual void parallelization_finalize();

      virtual bool has_ip4_internet();

      virtual bool has_ip6_internet();

      virtual void thread_initialize(::thread* pthread);
      //virtual void thread_finalize(::thread* pthread);

      // virtual void node_thread_initialize(::thread* pthread);
      // virtual void node_thread_finalize(::thread* pthread);

      virtual string get_version();

      virtual void _001InitializeShellOpen();

      //using ::platform::node::set_file_extension_mime_type;
      //void set_file_extension_mime_type(::get_file_extension_mime_type * pgetfileextensionmimetype) override;

      //void initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch) override;
      //void shell_open(const ::file::path & path, const ::scoped_string & scopedstrParams = "", const ::file::path & pathFolder = "") override;


      virtual void show_wait_cursor(bool bShow = true);


      virtual void get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory);


      virtual void on_start_application(::apex::application * papplication);


      //DECLARE_MESSAGE_HANDLER(on_message_clear_application_data);


      virtual void on_create_app_shortcut(::platform::application * papplication);

      virtual void defer_create_app_shortcut(::platform::application* papplication);

      virtual ::file::path app_shortcut_path(::platform::application* papplication);


      virtual ::string get_host_name();


      //void load_character_set_default_sample_text() override;


      virtual ::pointer < ::input::input > create_input();


      virtual bool is_key_pressed(bool * pbPressed, ::user::enum_key ekey);


      virtual void root_ones(::file::listing & listing);

//      virtual bool defer_enumerate_protocol(::file::listing& listing);

       //::string http_get_effective_url(const ::scoped_string & scopedstrUrl) override;

   };


} // namespace platform





