//
// Created by camilo on 2024-05-09 03:16 <3ThomasBorregaardSørensen!!.
//
#include "framework.h"
#include "application.h"
#include "install.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/nano/nano.h"
#include "acme/nano/archive/archive.h"
#include "acme/platform/node.h"


namespace coding
{




   void application::start_install_clion()
   {


   }


   bool install::get_debug_project_enabled()
   {

      return true;

   }


   // ::file::path install::get_download_url(::string& strName)
   // {
   //
   //    return {};
   //
   // }
//   int application::unix_shell_command(const ::scoped_string& scopedstrCommand)
   //   {
   //
   //      try
   //      {
   //
   //         ::string strUnixShell;
   //
   //         strUnixShell = "/bin/bash";
   //
   //         ::string strCommand;
   //
   //         ::string strCommandInner;
   //
   //         strCommandInner = scopedstrCommand.c_str();
   //
   //         strCommandInner.find_replace("\"", "\\\"");
   //
   //         strCommand.format("\"%s\" -c \"%s\"", strUnixShell.c_str(), strCommandInner.c_str());
   //
   //         auto iExitCode = acmenode()->command_system(strCommand);
   //
   //         return iExitCode;
   //
   //      }
   //      catch (...)
   //      {
   //
   //      }
   //
   //      return -1;
   //
   //   }


   //   bool application::has_unix_shell_command(const ::scoped_string& scopedstrCommand)
   //   {
   //
   //      try
   //      {
   //
   //         ::string strUnixShell;
   //
   //         strUnixShell = "/bin/bash";
   //
   //         ::string strCommand;
   //
   //         strCommand.format("\"%s\" -c command -v %s", strGitBash.c_str(), scopedstrCommand.c_str());
   //
   //         auto iExitCode = acmenode()->command_system(strCommand);
   //
   //         return iExitCode == 0;
   //
   //      }
   //      catch (...)
   //      {
   //
   //      }
   //
   //      return false;
   //
   //   }


   void application::install_clion()
   {


   }


   bool application::is_clion_installed()
   {

      return node()->has_posix_shell_command("clion");

   }


} // namespace coding


