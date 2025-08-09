//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "acme/platform/node.h"
#include "apex/message/channel.h"


namespace apex
{


   class CLASS_DECL_APEX node :
      virtual public ::platform::node,
      virtual public ::channel
   {
   public:
      //
      //
      // ::set < ::channel * >         m_setChannelSystemOptionsHtml;
      // //::apex::node*                 m_papexnode;
      // //::aura::node*                 m_pauranode;
      //

      node();
      ~node() override;


#ifdef _DEBUG

      
      long long increment_reference_count() override;
      
      
      long long decrement_reference_count() override;


#endif


      void on_initialize_particle() override;
      
      void destroy() override;
      
      virtual void main();


      virtual ::string system_options_html() override;

      virtual ::string system_options_main_body() override;
      
      
      //virtual void defer_create_main_menu(const string_array & straParent, const string_array & straMenu, const string_array & straId);
      

//      virtual void set_main_menu(application_menu * pmenu, ::apex::application * papp);


      virtual ::file::path get_desktop_file_path(::apex::application * papp) override;


      //virtual void defer_notify_startup_complete();


      void start_node() override;
      
      
      //void application_handle(long long l, void * p) override;


      // void on_operating_system_user_theme_change() override;
      //
      //
      // void on_operating_system_user_color_change() override;
      //
      //
      // void on_operating_system_font_list_change() override;


      virtual void defer_innate_ui() override;


      virtual void shell_create_link(::file::path pathObj, ::file::path pathLnk, const ::scoped_string & scopedstrDesc, ::file::path pathIco = "", int iIcon = -1) override;

      virtual bool shell_link_target(::file::path & pathTarget, const ::file::path & pathLnk) override;
      virtual bool shell_link_icon(::file::path & pathIcon, int & iIcon, const ::file::path& pathLnk) override;


      //virtual void parallelization_initialize();
      //virtual void parallelization_finalize();

      virtual bool has_ip4_internet() override;

      virtual bool has_ip6_internet() override;

      virtual void thread_initialize(::thread* pthread) override;
      //virtual void thread_finalize(::thread* pthread);

      // virtual void node_thread_initialize(::thread* pthread);
      // virtual void node_thread_finalize(::thread* pthread);

      virtual string get_version() override;

      virtual void _001InitializeShellOpen() override;

      using ::platform::node::set_file_extension_mime_type;
      void set_file_extension_mime_type(::get_file_extension_mime_type * pgetfileextensionmimetype) override;

      void initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch) override;
      //void shell_open(const ::file::path & path, const ::scoped_string & scopedstrParams = "", const ::file::path & pathFolder = "") override;


      virtual void show_wait_cursor(bool bShow = true) override;


      virtual void get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory) override;


      virtual void on_start_application(::apex::application * papplication) override;


      //DECLARE_MESSAGE_HANDLER(on_message_clear_application_data);


      virtual void on_create_app_shortcut(::platform::application * papplication) override;

      virtual void defer_create_app_shortcut(::platform::application* papplication) override;

      virtual ::file::path app_shortcut_path(::platform::application* papplication) override;


      virtual ::string get_host_name() override;


      void load_character_set_default_sample_text() override;


      virtual ::pointer < ::input::input > create_input() override;


      virtual bool is_key_pressed(bool * pbPressed, ::user::enum_key ekey) override;


      virtual void root_ones(::file::listing_base & listing) override;
      
//      virtual bool defer_enumerate_protocol(::file::listing_base& listing);

       //::string http_get_effective_url(const ::scoped_string & scopedstrUrl) override;

      
   };


} // namespace apex



