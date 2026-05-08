#include "framework.h"
#include <stdio.h>
#include <stdlib.h>


//#include "acme/node/ansios/ansios.h"
//#include "_linux.h"

//
//namespace linux
//{
//
//   int function()
//   {
//      return 0;
//   }
//
//
////   unsigned int GetTempPath(string & str)
////   {
////      return ::GetTempPathW(MAX_PATH * 8, wstring_adaptor(str, MAX_PATH * 8));
////   }
//
//} // namespace linux
//



//void CLASS_DECL_ACME __lnx_term()
//{
//
//
//
//}
//







// void motif_factory(::factory::factory * pfactory);
//
//
// void linux_factory(::factory::factory * pfactory){motif_factory(pfactory);}




bool debian_is_package_installed(const ::scoped_string & scopedstrPackageName)
{

    ::string strCommand;

    strCommand.format("dpkg-query -W -f='${{Status}}' {} 2>/dev/null", scopedstrPackageName);

    FILE* pipe = popen(strCommand.c_str(), "r");
    if (!pipe)
    {
        return false;
    }

    char buffer[256];
    ::string output;

    while (fgets(buffer, sizeof(buffer), pipe))
    {
        output += buffer;
    }

    int rc = pclose(pipe);
    if (rc != 0)
    {
        return false;
    }

    return output.contains("install ok installed");
}


::string_array_base debian_not_installed_packages(const ::string_array_base & straPackages)
{

    ::string_array_base straNotInstalledPackages;

    for (auto & strPackage : straPackages)
    {

        if (!debian_is_package_installed(strPackage))
        {

            straNotInstalledPackages.add_unique(strPackage);;

        }

    }

    return ::transfer(straNotInstalledPackages);

}


::string debian_install_packages_command_line(const ::string_array_base & straPackageNames)
{

    auto strPackages = straPackageNames.implode(" ");

    ::string strCommandLine;

    strCommandLine.format("sudo apt -y install {}", strPackages);

    return strCommandLine;

}


::string debian_install_package_file_command_line(const ::file::path & pathPackageFile)
{

   ::string strCommandLine;

   strCommandLine.format("sudo apt -y install '{}'", pathPackageFile);

   return strCommandLine;

}


::string_array_base debian_run_operating_system_package_installation_update_command_line_array()
{

   ::string_array_base straCommandLine;

   straCommandLine.add("sudo apt update");

   straCommandLine.add("sudo apt upgrade");

   return straCommandLine;

}




















bool rpm_is_package_installed(const ::scoped_string & scopedstrPackageName)
{

   ::string strCommand;

   strCommand.format("rpm -q {} 2>&1", scopedstrPackageName);

   FILE * pipe = popen(strCommand.c_str(), "r");

   if (!pipe)
   {

      return false;

   }

   char buffer[256];

   ::string output;

   while (fgets(buffer, sizeof(buffer), pipe))
   {

      output += buffer;

   }

   int rc = pclose(pipe);

   if (rc != 0)
   {

      return false;

   }

   // rpm outputs package info if installed,
   // and exits non-zero if not installed.
   return !output.is_empty();

}






bool fedora_is_package_installed(const ::scoped_string & scopedstrPackageName)
{

   return rpm_is_package_installed(scopedstrPackageName);

}


::string_array_base fedora_not_installed_packages(const ::string_array_base & straPackages)
{

   ::string_array_base straNotInstalledPackages;

   for (auto & strPackage : straPackages)
   {

      if (!debian_is_package_installed(strPackage))
      {

         straNotInstalledPackages.add_unique(strPackage);;

      }

   }

   return ::transfer(straNotInstalledPackages);

}


::string fedora_install_packages_command_line(const ::string_array_base & straPackageNames)
{

   auto stra = straPackageNames;

   stra.surround("'", "'");

   auto strPackages = stra.implode(" ");

   ::string strCommandLine;

   strCommandLine.format("sudo dnf -y install {}", strPackages);

   return strCommandLine;

}


::string fedora_install_package_file_command_line(const ::file::path & pathPackageFile)
{

   ::string strCommandLine;

   strCommandLine.format("sudo dnf -y install '{}'", pathPackageFile);

   return strCommandLine;

}



::string_array_base fedora_run_operating_system_package_installation_update_command_line_array()
{

   ::string_array_base straCommandLine;

   straCommandLine.add("sudo dnf update");

   return straCommandLine;

}

































bool opensuse_is_package_installed(const ::scoped_string & scopedstrPackageName)
{

   return rpm_is_package_installed(scopedstrPackageName);

}



::string_array_base opensuse_not_installed_packages(const ::string_array_base & straPackages)
{

   ::string_array_base straNotInstalledPackages;

   for (auto & strPackage : straPackages)
   {

      if (!debian_is_package_installed(strPackage))
      {

         straNotInstalledPackages.add_unique(strPackage);;

      }

   }

   return ::transfer(straNotInstalledPackages);

}



::string opensuse_install_packages_command_line(const ::string_array_base & straPackageNames)
{

   auto stra = straPackageNames;

   stra.surround("'", "'");

   auto strPackages = stra.implode(" ");

   ::string strCommandLine;

   strCommandLine.format("sudo zypper --non-interactive install {}", strPackages);

   return strCommandLine;

}



::string opensuse_install_package_file_command_line(const ::file::path & pathPackageFile)
{

   ::string strCommandLine;

   strCommandLine.format("sudo zypper --non-interactive install '{}'", pathPackageFile);

   return strCommandLine;

}




::string_array_base opensuse_run_operating_system_package_installation_update_command_line_array()
{

   ::string_array_base straCommandLine;

   straCommandLine.add("sudo zypper update");

   return straCommandLine;

}

