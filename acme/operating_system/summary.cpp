//
// Created by camilo on 07/04/23.
//
#include "framework.h"
#include "summary.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/node.h"


namespace operating_system
{


summary::summary()
{
   
   m_iMajorRelease = 0;
   
   m_iMinorRelease = 0;
   
}


summary::~summary()
{
   
   
}


::string summary::get_summary() const
{
   
   ::string strSummary;
   
   strSummary.append_format("__SYSTEM_DISTRO is %s", m_strDistro.c_str());
   strSummary.append_format("__SYSTEM_DISTRO_FAMILY is %s", m_strDistroFamily.c_str());
   strSummary.append_format("__SYSTEM_DISTRO_BRANCH is %s", m_strDistroBranch.c_str());
   strSummary.append_format("__SYSTEM_DISTRO_RELEASE is %s", m_strDistroRelease.c_str());
   strSummary.append_format("__SYSTEM_DESKTOP_ENVIRONMENT is %s", m_strDesktopEnvironment.c_str());
   strSummary.append_format("__SYSTEM_SLASHED_OPERATING_SYSTEM is %s", m_strSlashedOperatingSystem.c_str());
   strSummary.append_format("__SYSTEM_UNDERSCORE_OPERATING_SYSTEM is %s", m_strUnderscoreOperatingSystem.c_str());
   strSummary.append_format("__SYSTEM_SUDO_INSTALL is %s", m_strSudoInstall.c_str());
   strSummary.append_format("__SYSTEM_STANDARD_PACKAGE_FILE_EXTENSION is %s", m_strStandardPackageFileExtension.c_str());
   
   return strSummary;
   
}


//   ::pointer <::operating_system::summary > node::operating_system_summary()
//   {
//
//      throw ::interface_only();
//
//      return nullptr;
//
//   }
//
//void distro__release_and_desktop_environment::initialize(::particle *pparticle)
//{
//
//   ::particle::initialize(pparticle);
//
//   ::string strOs;
//   ::string strVer;
//   //}
//
//   // freedesktop.org and systemd
//   if (acmefile()->exists("/etc/os-release"))
//   {
//
//      auto set = acmefile()->parse_standard_configuration("/etc/os-release");
//
//      m_strDistro = set["ID"];
//      m_strDistroBranch = set["VARIANT_ID"];
//      m_strDesktopEnvironment = m_strDistroBranch;
//      m_strDistroRelease = set["VERSION_ID"];
//      m_strDistroFamily = set["ID_LIKE"];
//
//      m_strDistro.make_lower();
//      m_strDistroBranch.make_lower();
//      m_strDesktopEnvironment.make_lower();
//      m_strDistroRelease.make_lower();
//      m_strDistroFamily.make_lower();
//
//      if (m_strDistroFamily.case_insensitive_equals("arch"))
//      {
//
//         auto setArch = acmefile()->parse_standard_configuration("/etc/os-release");
//
//         m_strDistroRelease = setArch["DISTRIB_RELEASE"];
//         m_strDistroRelease.make_lower();
//
//      }
//
//   }
//   else if (acmenode()->has_unix_shell_command("lsb_release"))
//   {
//
//      //         }
//      //      elif
//      //      type lsb_release >/dev / null
//      //      2 > &1;
//      //      then
//
//      //# linuxbase.org
//
//      strOs = acmenode()->unix_shell_command_string("lsb_release -si");
//      strVer = acmenode()->unix_shell_command_string("lsb_release -sr");
//
//      strOs.make_lower();
//      strVer.make_lower();
//
//   }
//   else if (acmefile()->exists("/etc/lsb-release"))
//   {
//
//      //# For some versions of Debian/Ubuntu without lsb_release command
//      auto set = acmefile()->parse_standard_configuration("/etc/lsb-release");
//      //./ etc / lsb - release
//
//      strOs = set["DISTRIB_ID"];
//      strVer = set["DISTRIB_RELEASE"];
//      strOs.make_lower();
//      strVer.make_lower();
//
//
//   }
//   else if (acmefile()->exists("/etc/debian_version"))
//   {
//
//      //      elif[-f / etc / debian_version];
//      //      then
//      //
//      //# Older Debian/Ubuntu/etc.
//
//      strOs = "Debian";
//      strVer = acmefile()->as_string("/etc/debian_version");
//      strOs.make_lower();
//      strVer.make_lower();
//
//
//   }
//   else if (acmefile()->exists("/etc/SuSe-release"))
//   {
//      //      elif[-f / etc / SuSe - release];
//      //      then
//      //
//      //# Older SuSE/etc.
//      //
//      //              ...
//   }
//
//   else if (acmefile()->exists("/etc/redhat-release"))
//   {
//
//
//      //      }              elif[-f / etc / redhat - release];
//      //      then
//      //
//      //# Older Red Hat, CentOS, etc.
//      //
//      //              ...
//
//   }
//   else
//   {
//
//      // # Fall back to uname, e.g. "Linux <version>", also works for BSD, etc.
//
//      strOs = acmenode()->unix_shell_command_string("uname -s");
//      strVer = acmenode()->unix_shell_command_string("uname -r");
//
//   }
//
//   if (m_strDistroFamily.is_empty())
//   {
//
//      m_strDistroFamily = m_strDistro;
//
//   }
//
//   if (m_strDistro.case_insensitive_equals("ubuntu"))
//   {
//
//      m_strDistroFamily = "debian";
//
//   }
//   else if (m_strDistro.case_insensitive_equals("debian"))
//   {
//
//      m_strDistroFamily = "debian";
//
//   }
//   else if (m_strDistro.case_insensitive_equals("opensuse-tumbleweed"))
//   {
//
//      m_strDistroFamily = "zypper";
//
//   }
//   else if (m_strDistro.case_insensitive_equals("opensuse-leap"))
//   {
//
//      m_strDistroFamily = "zypper";
//
//   }
//
//   if (m_strDistro.case_insensitive_equals("fedora"))
//   {
//
//      if (m_strDistroBranch.case_insensitive_equals("workstation"))
//      {
//
//         m_strDesktopEnvironment = "gnome";
//
//      }
//
//   }
//
//   //::string strLowerCaseCurrentDesktop;
//
//   if (m_strDesktopEnvironment.is_empty())
//   {
//      ///# echo "DESKTOP_ENVIRONMENT is empty here"
//
//      if (m_strDistroFamily.case_insensitive_equals("debian")
//          || m_strDistroFamily.case_insensitive_equals("zypper")
//          || m_strDistroFamily.case_insensitive_equals("arch"))
//      {
//         //      if [ "$__SYSTEM_DISTRO_FAMILY" = "debian" ] || [ "$__SYSTEM_DISTRO_FAMILY" = "zypper" ] || [ "$__SYSTEM_DISTRO_FAMILY" = "arch" ];
//         //      then
//
//         //# echo "DISTRO_FAMILY is debian, zypper or arch"
//
//         auto strLowerCaseCurrentDesktop = acmenode()->get_environment_variable("XDG_CURRENT_DESKTOP").lowered();
//
//         //# echo "lower case xdg_current_desktop is $__SYSTEM_LOWER_CASE_CURRENT_DESKTOP"
//         if (strLowerCaseCurrentDesktop.equals("gnome"))
//         {
//            //      if contains
//            //      $__SYSTEM_LOWER_CASE_CURRENT_DESKTOP
//            //      "gnome";
//            //      then
//            //
//            //# echo "lower case xdg_current_desktop contains gnome"
//
//            m_strDesktopEnvironment = "gnome";
//
//         }
//         else if (strLowerCaseCurrentDesktop.equals("kde"))
//         {
//            //      elif
//            //      contains
//            //      $__SYSTEM_LOWER_CASE_CURRENT_DESKTOP
//            //      "kde";
//            //      then
//            //
//            //# echo "lower case xdg_current_desktop contains gnome"
//
//            m_strDesktopEnvironment = "kde";
//
//         }
//         else if (strLowerCaseCurrentDesktop.equals("lxde"))
//         {
//            //      elif
//            //      contains
//            //      $__SYSTEM_LOWER_CASE_CURRENT_DESKTOP
//            //      "lxde";
//            //      then
//            //
//            //# echo "lower case xdg_current_desktop contains lxde"
//
//            m_strDesktopEnvironment = "lxde";
//
//         }
//
//         if (m_strDistroFamily.case_insensitive_equals("debian"))
//         {
//
//            m_strDistroBranch = m_strDesktopEnvironment;
//
//         }
//         else if (m_strDistroFamily.case_insensitive_equals("zypper"))
//         {
//
//            m_strDistroBranch = m_strDesktopEnvironment;
//
//         }
//         else if (m_strDistroFamily.case_insensitive_equals("arch"))
//         {
//
//            m_strDistroBranch = m_strDesktopEnvironment;
//
//         }
//
//      }
//
//      if (m_strDistro.case_insensitive_equals("ubuntu"))
//      {
//
//         if (m_strDesktopEnvironment.case_insensitive_equals("kde"))
//         {
//
//            m_strSlashedOperatingSystem = "kubuntu/" + m_strDistroRelease;
//
//         }
//         else
//         {
//
//            m_strSlashedOperatingSystem = m_strDistro + "/" + m_strDistroRelease;
//         }
//
//      }
//      else
//      {
//
//         m_strSlashedOperatingSystem = m_strDistro + "/" + m_strDistroBranch + "/" + m_strDistroRelease;
//
//      }
//
//
//      if (m_strDistroFamily == "debian")
//      {
//
//         m_strSudoInstall = "sudo apt -y install";
//         m_strStandardPackageFileExtension = "deb";
//         m_strPackagePlatform = "amd64";
//
//      }
//      else if (m_strDistroFamily == "fedora")
//      {
//
//         m_strSudoInstall = "sudo dnf -y install";
//         m_strStandardPackageFileExtension = "rpm";
//         m_strPackagePlatform = "x86_64";
//
//      }
//      else if (m_strDistroFamily == "zypper")
//      {
//
//         m_strSudoInstall = "sudo zypper --non-interactive install";
//         m_strStandardPackageFileExtension = "rpm";
//         m_strPackagePlatform = "x86_64";
//
//      }
//
//      if (m_strDesktopEnvironment == "kde")
//      {
//
//         m_strTerminal = "konsole";
//
//      }
//      else
//      {
//
//         m_strTerminal = "gnome-terminal";
//
//      }
//
//      m_strUnderscoreOperatingSystem = m_strSlashedOperatingSystem;
//
//      m_strUnderscoreOperatingSystem.find_replace("/", "_");
//
//      acmenode()->set_environment_variable("__SYSTEM_DISTRO", m_strDistro);
//      acmenode()->set_environment_variable("__SYSTEM_DISTRO_FAMILY", m_strDistroFamily);
//      acmenode()->set_environment_variable("__SYSTEM_DISTRO_BRANCH", m_strDistroBranch);
//      acmenode()->set_environment_variable("__SYSTEM_DISTRO_RELEASE", m_strDistroRelease);
//      acmenode()->set_environment_variable("__SYSTEM_DESKTOP_ENVIRONMENT", m_strDesktopEnvironment);
//      acmenode()->set_environment_variable("__SYSTEM_SLASHED_OPERATING_SYSTEM", m_strSlashedOperatingSystem);
//      acmenode()->set_environment_variable("__SYSTEM_UNDERSCORE_OPERATING_SYSTEM", m_strUnderscoreOperatingSystem);
//      acmenode()->set_environment_variable("__SYSTEM_SUDO_INSTALL", m_strSudoInstall);
//      acmenode()->set_environment_variable("__SYSTEM_TERMINAL", m_strTerminal);
//
//   }
//
//
//}


} // namespace operating_system



