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
      virtual public ::acme::node,
      virtual public ::channel
   {
   public:


      ::set < ::channel * >         m_setChannelSystemOptionsHtml;
      //::apex::node*                 m_papexnode;
      //::aura::node*                 m_pauranode;


      node();
      ~node() override;


#ifdef _DEBUG

      
      i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      
      
      i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#endif


      virtual void on_initialize_particle() override;
      
      
      virtual void main();


      virtual ::string system_options_html();

      virtual ::string system_options_main_body();
      
      
      //virtual void defer_create_main_menu(const string_array & straParent, const string_array & straMenu, const string_array & straId);
      

      virtual void set_application_menu(application_menu * pmenu, ::apex::application * papp);


      virtual ::file::path get_desktop_file_path(::apex::application * papp);


      virtual void defer_notify_startup_complete();


      virtual void start_node() override;


      void on_operating_system_user_theme_change() override;


      void on_operating_system_user_color_change() override;


      void on_operating_system_font_list_change() override;


      virtual void shell_create_link(::file::path pathObj, ::file::path pathLnk, string strDesc, ::file::path pathIco = "", int iIcon = -1);

      virtual bool shell_link_target(::file::path & pathTarget, const ::file::path & pathLnk);
      virtual bool shell_link_icon(::file::path & pathIcon, int & iIcon, const ::file::path& pathLnk);


      //virtual void parallelization_initialize();
      //virtual void parallelization_finalize();

      virtual void thread_initialize(::thread* pthread);
      //virtual void thread_finalize(::thread* pthread);

      // virtual void node_thread_initialize(::thread* pthread);
      // virtual void node_thread_finalize(::thread* pthread);

      virtual string get_version();

      virtual void _001InitializeShellOpen();


      //void shell_open(const ::file::path & path, const ::string & strParams = "", const ::file::path & pathFolder = "") override;


      virtual void show_wait_cursor(bool bShow = true);


      virtual void get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory);


      virtual void on_start_application(::apex::application * papplication);


      //DECLARE_MESSAGE_HANDLER(on_message_clear_application_data);


      virtual void on_create_app_shortcut(::acme::application * papp);


   };


} // namespace apex



