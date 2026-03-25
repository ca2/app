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



