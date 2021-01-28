//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/id.h"


namespace acme
{

   node::node()
   {

      m_papexnode = nullptr;
      m_pauranode = nullptr;
      m_edesktop = ::user::e_desktop_none;

   }


   node::~node()
   {


   }


   int node::node_init_check(int *pi, char *** ppz)
   {

      return -1;

   }


   void node::os_application_system_run()
   {


   }


   bool node::_calc_dark_mode()
   {

      return false;

   }


   void node::os_calc_user_dark_mode()
   {

      bool bDarkMode = _calc_dark_mode();

      if(is_different(::user::is_app_dark_mode(), bDarkMode)
      || is_different(::user::is_system_dark_mode(), bDarkMode))
      {

         ::user::set_app_dark_mode(bDarkMode);

         ::user::set_system_dark_mode(bDarkMode);

         System.deliver(id_os_dark_mode);

         on_os_dark_mode_change();

      }

   }


   void node::on_os_dark_mode_change()
   {


   }


   string node::os_get_user_theme()
   {

      return "";

   }


   bool node::os_set_user_theme(const ::string & strUserTheme)
   {

      return false;

   }


   void node::os_process_user_theme(string strTheme)
   {



   }


   bool node::set_wallpaper(index iScreen, string strLocalImagePath)
   {

      auto pnode = Node;

      if(::is_null(pnode))
      {

         return false;

      }

      return pnode->set_wallpaper(iScreen, strLocalImagePath);

   }


   string node::get_wallpaper(index iScreen)
   {

      return "";

   }


   string node::get_file_icon_path(const char * pszPath, int iSize)
   {

      return "";

   }


   string node::get_file_content_type(const char * pszPath)
   {

      return "";

   }


   int node::os_launch_uri(const char * pszUri, char * pszError, int iBufferSize)
   {

      return -1;

   }


   void node::enable_wallpaper_change_notification()
   {


   }


   void node::node_fork(const ::promise::routine & routine)
   {

   }


   void node::node_sync(const ::duration & durationTimeout, const ::promise::routine & routine)
   {

      auto proutine = __sync_routine(routine);

      node_fork(proutine);

      proutine->sync_wait(durationTimeout);

   }


   void node::user_fork(const ::promise::routine & routine)
   {


   }


   void node::user_sync(const ::duration & durationTimeout, const ::promise::routine & routine)
   {

      auto proutine = __sync_routine(routine);

      user_fork(proutine);

      proutine->sync_wait(durationTimeout);

   }


   void node::node_post_quit()
   {


   }


   void node::enum_display_monitors(::aura::session * psession)
   {


   }


   void node::os_post_quit()
   {

   }


  bool node::should_launch_on_node(::promise::subject * psubject)
  {

      return false;

  }


  bool node::defer_launch_on_node(::promise::subject * psubject)
  {

      bool bShouldLaunchOnNode = should_launch_on_node(psubject);

      if(!bShouldLaunchOnNode)
      {

         return false;

      }

      bool bLaunchedOnNode = launch_on_node(psubject);

      if(!bLaunchedOnNode)
      {

         return false;

      }

      return true;

  }


  bool node::launch_on_node(::promise::subject * psubject)
  {

      return false;

  }


} // namespace acme



