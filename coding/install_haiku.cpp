#include "platform.h"
#include "application.h"
#include "install.h"
#include "acme/platform/node.h"

namespace coding
{
   // Desktop installers for other operating systems cannot run on Haiku.
   static void unsupported_installer()
   {
      throw ::exception(error_not_supported, "This installer is not available on Haiku.");
   }
   void application::start_install_clion() { unsupported_installer(); }
   void application::__install_jetbrains_clion() { unsupported_installer(); }
   bool application::__is_git_scm_installed() { return node()->has_posix_shell_command("git"); }
   bool install::get_debug_project_enabled() { return true; }
   ::file::path install::get_download_url(::string &) { unsupported_installer(); return {}; }
   ::string install::get_latest_git_credential_manager_download_url() { unsupported_installer(); return {}; }
   void install::install_setup_folders() { unsupported_installer(); }
   void install::install_git_scm() { unsupported_installer(); }
   void install::install_patch_shell() { unsupported_installer(); }
   void install::install_smart_git() { unsupported_installer(); }
   void install::install_google_chrome() { unsupported_installer(); }
   void install::install_user_fonts_from_font_listing(const ::file::path &) { unsupported_installer(); }
   ::i32 install::synchronous_posix_terminal(const ::scoped_string & command)
   {
      return node()->synchronous_posix_terminal(command, e_posix_shell_system_default,
         [this](auto, auto text, bool) { set_status2(text); });
   }
}
