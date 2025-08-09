//
// Created by camilo on 2024-10-24 12:45 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "node_apex.h"


namespace platform
{
   // #ifdef _DEBUG
   //
   //
   //       long long increment_reference_count() override{}
   //
   //
   //       long long decrement_reference_count() override{}
   //
   //
   // #endif


   //void apex_node_layer::on_initialize_particle() override{}


   //void apex_node_layer::main(){}


   ::string apex_node_layer::system_options_html()
   {

      return {};


   }


   ::string apex_node_layer::system_options_main_body()
   {

      return {};
   }


   //void apex_node_layer::defer_create_main_menu(const string_array & straParent, const string_array & straMenu, const string_array & straId){}


   //      void apex_node_layer::set_main_menu(application_menu * pmenu, ::apex::application * papp){}


   ::file::path apex_node_layer:: get_desktop_file_path(::apex::application* papp)
   {

      return {};
   }


   //void apex_node_layer::defer_notify_startup_complete(){}


   //void start_node() override{}


   //void application_handle(long long l, void * p) override{}


   // void on_operating_system_user_theme_change() override{}
   //
   //
   // void on_operating_system_user_color_change() override{}
   //
   //
   // void on_operating_system_font_list_change() override{}


   void apex_node_layer::defer_innate_ui()
   {
   }


   void apex_node_layer::shell_create_link(::file::path pathObj, ::file::path pathLnk, const ::scoped_string & scopedstrDesc, ::file::path pathIco,
                                  int iIcon)
   {
   }


   bool apex_node_layer::shell_link_target(::file::path& pathTarget, const ::file::path& pathLnk)
   {
      return false;
   }


   bool apex_node_layer::shell_link_icon(::file::path& pathIcon, int& iIcon, const ::file::path& pathLnk)
   {
      return false;
   }


   //void apex_node_layer::parallelization_initialize(){}
   //void apex_node_layer::parallelization_finalize(){}

   bool apex_node_layer::has_ip4_internet()
   {
      return false;
   }


   bool apex_node_layer::has_ip6_internet()
   {
      return false;
   }


   void apex_node_layer::thread_initialize(::thread* pthread)
   {
   }


   //void apex_node_layer::thread_finalize(::thread* pthread){}

   // void apex_node_layer::node_thread_initialize(::thread* pthread){}
   // void apex_node_layer::node_thread_finalize(::thread* pthread){}

   ::string apex_node_layer::get_version()
   {

      return {};
   }


   void apex_node_layer::_001InitializeShellOpen()
   {
   }


   //using ::platform::node::set_file_extension_mime_type{}
   //void set_file_extension_mime_type(::get_file_extension_mime_type * pgetfileextensionmimetype) override{}

   //void initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch) override{}
   //void shell_open(const ::file::path & path, const ::scoped_string & scopedstrParams, const ::file::path & pathFolder) override{}


   void apex_node_layer::show_wait_cursor(bool bShow)
   {
   }


   void apex_node_layer::get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory)
   {
   }


   void apex_node_layer::on_start_application(::apex::application* papplication)
   {
   }


   //DECLARE_MESSAGE_HANDLER(on_message_clear_application_data){}


   void apex_node_layer::on_create_app_shortcut(::platform::application* papplication)
   {
   }


   void apex_node_layer::defer_create_app_shortcut(::platform::application* papplication)
   {
   }


   ::file::path apex_node_layer:: app_shortcut_path(::platform::application* papplication)
   {
      return {};
   }


   ::string apex_node_layer::get_host_name()
   {
      return {};
   }


   //void load_character_set_default_sample_text() override{}


   ::pointer<::input::input> apex_node_layer::create_input()
   {
      return {};
   }


   bool apex_node_layer::is_key_pressed(bool* pbPressed, ::user::enum_key ekey)
   {
      return false;
   }


   void apex_node_layer::root_ones(::file::listing_base& listing)
   {
   }


   //      bool apex_node_layer::defer_enumerate_protocol(::file::listing_base& listing){}

   //::string http_get_effective_url(const ::scoped_string & scopedstrUrl) override{}

} // namespace platform
