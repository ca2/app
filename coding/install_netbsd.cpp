#include "platform.h"
#include "application.h"
#include "install.h"
#include "acme/platform/node.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"

namespace coding
{
   namespace
   {
      void unsupported_installer()
      {
         throw ::exception(error_not_supported, "This installer is not available on NetBSD.");
      }

      ::string shell_quote(const ::scoped_string & value)
      {
         ::string quoted(value);
         quoted.find_replace("'", "'\"'\"'");
         return "'" + quoted + "'";
      }
   }

   void application::start_install_clion() { unsupported_installer(); }
   void application::__install_jetbrains_clion() { unsupported_installer(); }
   bool application::__is_git_scm_installed() { return node()->has_posix_shell_command("git"); }
   bool install::get_debug_project_enabled() { return true; }
   ::file::path install::get_download_url(::string &) { unsupported_installer(); return {}; }
   ::string install::get_latest_git_credential_manager_download_url() { unsupported_installer(); return {}; }
   void install::install_setup_folders() { unsupported_installer(); }
   void install::install_patch_shell() { unsupported_installer(); }
   void install::install_smart_git() { unsupported_installer(); }
   void install::install_google_chrome() { unsupported_installer(); }
   void install::install_visual_studio_code() { unsupported_installer(); }
   void install::install_git_credential_manager() { unsupported_installer(); }
   void install::install_deps() { unsupported_installer(); }
   void install::defer_install_gnome_extensions() { unsupported_installer(); }
   void install::_install_gnome_extensions() { unsupported_installer(); }
   void install::install_user_fonts_from_font_listing(const ::file::path &) { unsupported_installer(); }

   ::i32 install::synchronous_posix_terminal(const ::scoped_string & command)
   {
      return node()->synchronous_posix_terminal(command, e_posix_shell_system_default,
         [this](auto, auto text, bool) { set_status2(text); });
   }

   bool install::_is_package_installed(const ::scoped_string & name)
   {
      ::string output, error;
      return node()->get_posix_shell_command_output(output, error,
         "/usr/pkg/sbin/pkg_info -e " + shell_quote(name)) == 0;
   }

   void install::_install_packages(const ::string_array_base & names)
   {
      if (names.is_empty()) return;
      ::string command = "sudo /usr/pkg/bin/pkgin -y install";
      for (const auto & name : names) command += " " + shell_quote(name);
      if (synchronous_posix_terminal(command) != 0)
         throw ::exception(error_failed, "NetBSD package installation failed.");
   }

   void install::defer_install_packages(const ::string_array_base & names)
   {
      ::string_array_base missing;
      for (const auto & name : names)
         if (!_is_package_installed(name)) missing.add(name);
      _install_packages(missing);
   }

   void install::_uninstall(const ::scoped_string & name)
   {
      if (synchronous_posix_terminal("sudo /usr/pkg/bin/pkgin -y remove " + shell_quote(name)) != 0)
         throw ::exception(error_failed, "NetBSD package removal failed.");
   }

   void install::install_git_scm()
   {
      defer_install_packages({"git"});
      on_finished();
   }

   bool install::_are_user_packages_installed()
   {
      auto index = directory_system()->home() / ".config/integration/code/___install/index.txt";
      if (!file_system()->exists(index)) return false;
      auto names = file_system()->lines(index);
      names.trim();
      names.erase_empty();
      for (const auto & name : names)
         if (!_is_package_installed(name)) return false;
      return true;
   }

   void install::defer_install_user_packages()
   {
      if (!_are_user_packages_installed()) _install_user_packages();
   }

   void install::_install_user_packages()
   {
      auto index = directory_system()->home() / ".config/integration/code/___install/index.txt";
      if (!file_system()->exists(index))
         throw ::exception(error_not_found, "No NetBSD user package list is configured.");
      auto names = file_system()->lines(index);
      names.trim();
      names.erase_empty();
      defer_install_packages(names);
   }

   void install::_install_pkg()
   {
      if (synchronous_posix_terminal("sudo /usr/pkg/sbin/pkg_add " + shell_quote(m_path)) != 0)
         throw ::exception(error_failed, "NetBSD package installation failed.");
   }

   void install::install_pkg()
   {
      _install_pkg();
      on_finished();
   }
}
