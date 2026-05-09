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

   strCommandLine.format("sudo dnf -y --best --allow-erasing install {}", strPackages);

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


//
// #include <cstdlib>
// #include <cstdio>
// #include <string>
//
// enum MsgBoxResult {
//    e_dialog_result_ok,
//    MSGBOX_CANCEL,
//    e_dialog_result_yes,
//    e_dialog_result_no,
//    MSGBOX_ERROR
// };

CLASS_DECL_ACME enum_dialog_result simple_ui_message_box(
   const ::user_interaction_sink& userinteractionsink,
   const ::scoped_string& scopedstrMessage,
   const ::scoped_string& scopedstrCaption,
   const ::user::e_message_box& emessagebox)
{

   ::string strCommand;

   ::string strTitle(scopedstrCaption);

   ::string strMessage(scopedstrMessage);

    int ret;

    // -------------------------
    // ZENITY
    // -------------------------
    if ((emessagebox & ::user::e_message_box_button_mask) == ::user::e_message_box_yes_no)
    {
        strCommand =
            "zenity --question "
            "--strTitle=\"" + strTitle +
            "\" --text=\"" + strMessage + "\"";

        ret = system(strCommand.c_str());

        if (WIFEXITED(ret))
        {
            int code = WEXITSTATUS(ret);

            if (code == 0)
                return e_dialog_result_yes;

            if (code == 1)
                return e_dialog_result_no;
        }
    }
   else //if ((emessagebox & ::user::e_message_box_button_mask) == ::user::e_message_box_ok)
   {
      strCommand =
          "zenity --info "
          "--title=\"" + strTitle +
          "\" --text=\"" + strMessage + "\"";

      ret = system(strCommand.c_str());

      if (WIFEXITED(ret) && WEXITSTATUS(ret) == 0)
         return e_dialog_result_ok;
   }

    // -------------------------
    // KDIALOG
    // -------------------------
   if ((emessagebox & ::user::e_message_box_button_mask) == ::user::e_message_box_yes_no)
    {
        strCommand =
            "kdialog --yesno \"" + strMessage +
            "\" --strTitle \"" + strTitle + "\"";

        ret = system(strCommand.c_str());

        if (WIFEXITED(ret))
        {
            int code = WEXITSTATUS(ret);

            if (code == 0)
                return e_dialog_result_yes;

            if (code == 1)
                return e_dialog_result_no;
        }
    }
   else //if (buttons == MSGBOX_BUTTON_OK)
   {
      strCommand =
          "kdialog --msgbox \"" + strMessage +
          "\" --strTitle \"" + strTitle + "\"";

      ret = system(strCommand.c_str());

      if (WIFEXITED(ret) && WEXITSTATUS(ret) == 0)
         return e_dialog_result_ok;
   }

    // -------------------------
    // TERMINAL FALLBACK
    // -------------------------
    printf("\n=== %s ===\n%s\n",
           strTitle.c_str(),
           strMessage.c_str());

   if ((emessagebox & ::user::e_message_box_button_mask) == ::user::e_message_box_yes_no)
    {
        printf("[y/n]: ");

        char c;
        scanf(" %c", &c);

        return (c == 'y' || c == 'Y')
            ? e_dialog_result_yes
            : e_dialog_result_no;
    }
   else  //if (buttons == MSGBOX_BUTTON_OK)
   {
      printf("[Press ENTER to continue]");
      getchar();
      return e_dialog_result_ok;
   }
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

