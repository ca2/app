//
// Created by camilo on 2024-05-09 03:16 <3ThomasBorregaardSørensen!!.
//
#include "framework.h"
#include "application.h"
#include "install.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/nano/nano.h"
#include "acme/nano/archive/archive.h"
#include "acme/platform/http.h"
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



   string application::__jetbrains_clion_download_url()
   {

      auto pathUrl = fetch_download_link("linux/clion");

      print_line("JetBrains CLion download url : " + pathUrl);

      return pathUrl;

   }


   void application::__download_jetbrains_clion()
   {

      ::file::path pathSource = __jetbrains_clion_download_url();

      ::file::path pathTarget = directory()->home() / "Downloads/Code!!" / pathSource.name();

      ::property_set set;

      print_line("Downloading \"" + pathSource+"\" to \""+pathTarget + "\".");

      http()->download(pathTarget, pathSource, set);

      m_pathJetBrainsTarGz = pathTarget;

   }


   void application::__install_jetbrains_clion()
   {

      __download_jetbrains_clion();

      print_line("Uncompressing JetBrains CLion...");

      auto pathClion = directory_system()->home() / "application_opt/clion";

      directory_system()->create(pathClion);

      node()->posix_shell_command("tar -xzvf \""+ m_pathJetBrainsTarGz + "\" -C \"" + pathClion + "\" --strip-components=1",
         e_posix_shell_system_default,
   [this](auto etracelevel, auto & str, bool bCarriage)
      {

         print_line(str);

      });

      print_line("Launching JetBrains CLion...");

      node()->posix_shell_command(pathClion / "bin/clion");

      //node()->detached_command("/bin/bash -c " + (pathSyntevo / "smartgit/bin/smartgit.sh"), {});

   }


   // bool application::is_clion_installed()
   // {
   //
   //    return node()->has_posix_shell_command("clion");
   //
   // }


} // namespace coding


