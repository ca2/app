// From application_build_helper to implement.cpp by camilo on 2021-12-17 21:04 BRT <3ThomasBorregaardSørensen!!
// From launch/application.cpp by camilo on 2026-06-01 23:30 BRT <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "application.h"
#include "launch.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/nano/nano.h"
#include "acme/nano/http/http.h"
#include "acme/nano/compress/compress.h"
#include "acme/nano/shell/shell.h"
#include "acme/operating_system/summary.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/datetime/datetime.h"



namespace launch
{


   launch::launch()
   {

      m_iExitCode = 0;

   }


   launch::~launch()
   {

   }


   void launch::calculate_distro__branch_and_release()
   {

      if (m_poperatingsystemsummary)
      {

         return;

      }

      m_poperatingsystemsummary = node()->operating_system_summary();

      m_strSystem = m_poperatingsystemsummary->m_strSystem;

      m_strSystem.make_lower();

      m_strSystemFamily = m_poperatingsystemsummary->m_strSystemFamily;

      m_strSystemFamily.make_lower();

      ::string strBranch = m_poperatingsystemsummary->m_strSystemBranch;

      strBranch.make_lower();

      ::string strRelease;

      strRelease = m_poperatingsystemsummary->m_strSystemRelease;

      if (m_strSystemFamily.has_character())
      {

         print_line("System family is \"" + m_strSystemFamily + "\"...");

      }

      if (m_strSystem == "ubuntu")
      {
         if (strBranch == "kde")
         {
            m_strSystem = "kubuntu";
            print_line("This is Kubuntu System...");
         }
         else if (strBranch == "xfce")
         {
            m_strSystem = "xubuntu";
            print_line("This is Xubuntu System...");
         }
         else if (strBranch == "lxde")
         {
            m_strSystem = "lubuntu";
            print_line("This is Lubuntu System (LXDE)...");
         }
         else if (strBranch == "lxqt")
         {
            m_strSystem = "lubuntu";
            print_line("This is Xubuntu System (LXQt)...");
         }
         else
         {
            print_line("This is Ubuntu System (Unity)...");
         }
      }
      else if (m_strSystem == "fedora")
      {

         print_line("This is Fedora Linux System...\n");

         m_strBranch = strBranch;

      }
      else if (m_strSystem == "debian")
      {

         print_line("This is Debian Linux System...\n");

         m_strBranch = strBranch;

      }
      else if (m_strSystem == "freebsd")
      {

         print_line("This is FreeBSD System...");

         m_strBranch = strBranch;

         //if(strBranch == "kde")
         //{

         //m_strBranch = "gnome";

         //}


      }
      else if (m_strSystem == "openbsd")
      {

         print_line("This is OpenBSD System...");

         m_strBranch = strBranch;

         printf_line("Branch is \"%s\"", m_strBranch.c_str());

      }
      else if (m_strSystem == "netbsd")
      {

         print_line("This is NetBSD System...");

         m_strBranch = strBranch;

      }
      else if (m_strSystem == "linuxmint")
      {

         m_strSystem = "ubuntu";

         if (strRelease == "21")
         {

            print_line("This is Linux Mint 21 System...");

            print_line("Going to use Ubuntu 22.04 binaries...");

            strRelease = "22.04";

            m_strBranch = "";

         }
         else if (strRelease == "22")
         {

            print_line("This is Linux Mint 22 System...");

            print_line("Going to use Ubuntu 24.04 binaries...");

            strRelease = "24.04";

            m_strBranch = "";

         }
         else
         {

            printf_line("This is Linux Mint %s System...", strRelease.c_str());

            //print_line("Currently not known how to handle. Fallback to Ubuntu 24.04 binaries...");

            m_strBranch = strBranch;

         }

      }
      else if (m_strSystem == "opensuse-tumbleweed")
      {

         print_line("This is openSUSE Tumbleweed System...\n");

         m_strBranch = strBranch;

      }
      else if (m_strSystem == "opensuse-leap")
      {

         print_line("This is openSUSE Leap System...\n");

         m_strBranch = strBranch;

      }
      else if (m_poperatingsystemsummary->m_strSystemFamily == "arch")
      {

         print_line("This is Arch based system...\n");

         m_strBranch = strBranch;

      }

      m_strRelease = strRelease;

      printf_line("Release is \"%s\"", m_strRelease.c_str());

      m_strArchitecture = m_poperatingsystemsummary->m_strSystemArchitecture;

      printf_line("Architecture is \"%s\"", m_strArchitecture.c_str());

   }


   void launch::install_dependencies()
   {

      print_line("Going to install dependencies: ");

      auto straDependencies = file_system()->lines(m_pathBinaryFolder / "operating_system_packages.txt");

      if (straDependencies.is_empty())
      {

         print_line("no dependencies to install");

         return;

      }

      auto straNotInstalled = system()->not_installed_operating_system_packages(straDependencies);

      auto lines = straNotInstalled;

      if (lines.is_empty())
      {

         print_line("dependencies already installed");

         return;

      }

      ::string strPackages;

      strPackages = lines.implode(" ");

      ::string strCommand;

      if (m_strSystemFamily == "debian")
      {

         strCommand.formatf("sudo apt -y install %s", strPackages.c_str());

         //     log_system("sudo apt -y install libfreeimage3 libstartup-notification0 libunac1 libxm4");

      }
      else if (m_strSystem == "fedora")
      {

         strCommand.formatf("sudo dnf --assumeyes install %s", strPackages.c_str());

         //    log_system("sudo dnf --assumeyes install freeimage libidn motif libappindicator-gtk3");

         //log_system(scopedstrCommand);

      }
      else if (m_strSystem == "freebsd")
      {

         strCommand.formatf("sudo pkg install %s", strPackages.c_str());

      }
      else if (m_strSystem == "opensuse"
         || m_strSystem == "opensuse-tumbleweed"
         || m_strSystem == "opensuse-leap")
      {

         strCommand.formatf("sudo zypper install %s", strPackages.c_str());

      }
      else
      {

         printf_line("Don't know how to install dependencies for this system. (%s)", strPackages.c_str());

      }

      if (strCommand.has_character())
      {

         //log_system(strCommand);

         print_line(strCommand);

         ::i32 iError = ::system(strCommand);

         if (iError)
         {

            printf_line("\"%s\" Command failed with error code %d", strCommand.c_str(), iError);

         }

      }

   }


   void launch::parse_app_root_and_app_name()
   {

      if (m_strLaunchAppId.is_empty())
      {

         if (::system()->m_argc <= 1)
         {

            throw "Wrong number of arguments";

         }

         m_strLaunchAppId = ::system()->m_args[1];

      }

      auto iSlash = m_strLaunchAppId.find_index('/');

      if (iSlash < 0 || iSlash == 0 || iSlash >= m_strLaunchAppId.last_index())
      {

         throw "App Id must contain one slash and only one slash separating app_root and app_name";

      }

      m_strAppRoot = m_strLaunchAppId(0, iSlash);

      debugf("app_root: %s", m_strAppRoot.c_str());

      m_strAppName = m_strLaunchAppId(iSlash + 1);

      debugf("app_name: %s", m_strAppName.c_str());

   }


   void launch::on_main_status(const ::scoped_string& scopedstr)
   {

      m_plaunchapplication->on_launch_main_status(scopedstr);

   }


   void launch::on_detail_status(const ::scoped_string& scopedstr)
   {

      m_plaunchapplication->on_launch_detail_status(scopedstr);

   }


   void launch::on_error_status(const ::scoped_string& scopedstr)
   {

      m_plaunchapplication->on_launch_error_status(scopedstr);

   }  


   void launch::do_launch()
   {

      on_main_status("Starting app/launch for \"" + m_strLaunchAppId + "\".");

      on_detail_status("Build time: " __DATE__ " " __TIME__);

      on_detail_status("Calculating Download URL...");

      parse_app_root_and_app_name();

      auto strDownloadUrl = calculate_download_url();

      if (strDownloadUrl.is_empty())
      {

         m_iExitCode = -1;

         on_error_status("Couldn't determine Download URL");

         return;

      }

      ::string strMessage;

      strMessage.formatf("Checking if version exists at server... (%s)", strDownloadUrl.c_str());

      on_main_status(strMessage);

      ::property_set setCheckUrlOkDownload;

      m_papplication->get_http_user_agent(setCheckUrlOkDownload);

      if (!nano()->http()->check_url_ok(strDownloadUrl, setCheckUrlOkDownload))
      {

         m_iExitCode = -1;

         ::string strErr;

         strErr.formatf("Server seems not to have build of \"%s/%s\" for this operating-system release \"%s\" (%s, %s)",
            m_strAppRoot.c_str(),
            m_strAppName.c_str(),
            m_poperatingsystemsummary->m_strName.c_str(),
            m_poperatingsystemsummary->m_strSystemReleaseName.c_str(),
            m_poperatingsystemsummary->m_strSystemArchitecture.c_str());

         if (m_strBranch.has_character())
         {

            strErr.append_formatf(" \"%s\".", m_poperatingsystemsummary->m_strSystemBranchName.c_str());

         }
         else
         {

            strErr += ".";

         }

         on_error_status(strErr);

         return;

      }

      strMessage.formatf("Downloading %s/%s...", m_strAppRoot.c_str(), m_strAppName.c_str());

      on_main_status(strMessage);

      auto pathStore = directory_system()->home() / "application" / m_strAppRoot / m_strAppName;

      directory_system()->create(pathStore);

      auto pathInstallingWithLaunchStore = pathStore / "installing_with_launch_store";

      file_system()->ensure_exists(pathInstallingWithLaunchStore);

      auto pathLogFolder = pathStore / "log";

      directory_system()->create(pathLogFolder);

      auto strDateTimeName = datetime()->date_time_text_for_file_with_no_spaces();

      strDateTimeName += ".txt";

      //
      // sprintf(szLogFilename,
      // "%04d-%02d-%02d_%02d-%02d-%02d.txt",
      // ptm->tm_year,
      // ptm->tm_mon,
      // ptm->tm_mday,
      // ptm->tm_hour,
      // ptm->tm_min,
      // ptm->tm_sec);

      m_pathLog = pathLogFolder / strDateTimeName;

      m_pathBinaryFolder = pathStore / "binary";
      // ::i8 szX64[4096];
      //
      // strcpy(szX64, szStore);
      //
      // strcat(szX64, "/x64");
      //
      // mkdir(szX64, 0777);
      //
      // chdir(szX64);

      directory_system()->create(m_pathBinaryFolder);

      directory_system()->change_current(m_pathBinaryFolder);

#if defined(WINDOWS)

      ::string strExecutable = "shared_" + m_strAppRoot + "_" + m_strAppName + ".exe";

#else

      ::string strExecutable = "_" + m_strAppRoot + "_" + m_strAppName;

#endif

      //    ::i8 szAppExeName[1024];
      //    sprintf(szAppExeName, "_%s_%s", m_pszAppRoot, m_pszAppName);
      //
      //    for(::i32 i = 0; i < strlen(szAppExeName); i++)
      //    {
      //
      // if(szAppExeName[i] =='-')
      // {
      // szAppExeName[i] = '_';
      //
      // }
      //
      //    }
      strExecutable.find_replace("-", "_");

      auto pathExecutable = m_pathBinaryFolder / strExecutable;

      ::string strZipName;

      strZipName = "_" + strExecutable + ".zip";
      // ::i8 szZipName[1024];
      // sprintf(szZipName, "_%s.zip", szAppExeName);
      // ::i8 szDownloadCommand[2048];

      auto pathZipName = m_pathBinaryFolder / strZipName;

      ::property_set set;

      m_papplication->get_http_user_agent(set);

      nano()->http()->download(pathZipName, strDownloadUrl, set);
      // if (!strcasecmp(m_pszDistro, "freebsd")) {
      //
      // strcpy(szDownloadCommand, "curl ");
      // strcat(szDownloadCommand, szDownloadUrl);
      // strcat(szDownloadCommand, " > ");
      // strcat(szDownloadCommand, szZipName);
      //
      // }
      // else
      // {
      // strcpy(szDownloadCommand, "wget ");
      // strcat(szDownloadCommand, szDownloadUrl);
      // strcat(szDownloadCommand, " -O ");
      // strcat(szDownloadCommand, szZipName);
      //
      // }


      strMessage.formatf("Uncompressing %s/%s...", m_strAppRoot.c_str(), m_strAppName.c_str());

      on_main_status(strMessage);

      //system(szDownloadCommand);

      nano()->compress()->unzip(m_pathBinaryFolder, pathZipName);

      //::i8 szUnzipCommand[2048];

      //sprintf(szUnzipCommand, "unzip -o %s -d .", szZipName);

      //system(szUnzipCommand);

      strMessage.formatf("Installing dependencies for %s/%s...", m_strAppRoot.c_str(), m_strAppName.c_str());

      on_main_status(strMessage);

      install_dependencies();

      if (::system()->has_argument("--install-only")
         || ::system()->has_argument("--only-install"))
      {

         print_line("Installed \"" + m_strAppRoot + "/" + m_strAppName + "\".");

         return;

      }

      m_plaunchapplication->on_going_to_launch();

      strMessage.formatf("Launching %s/%s...", m_strAppRoot.c_str(), m_strAppName.c_str());

      on_main_status(strMessage);

      ::string strCommand;

      strCommand = pathExecutable;

      auto strTraceLevel = ::system()->get_argument_begins_eat("--trace-level=");

      if (strTraceLevel.has_character())
      {

         strCommand += " --trace-level=" + strTraceLevel;

      }

      node()->detached_command(strCommand, m_pathLog);

      m_plaunchapplication->on_launched();


      //    ::i8 szCommand[4096];
      //    strcpy(szCommand, "sh -c \"nohup ./");
      // strcat(szCommand, szAppExeName);
      // strcat(szCommand, " > \\\"");
      // strcat(szCommand, szLogPath);
      // strcat(szCommand, "\\\"\"");
      //
      // system(szCommand);

   }


   ::string launch::calculate_download_url()
   {

      calculate_distro__branch_and_release();

      if (m_strSystem.is_empty() || m_strRelease.is_empty())
      {

         return {};

      }

      // if (!strcasecmp(m_pszDistro, "opensuse-tumbleweed") && strlen(m_pszVersion) > 4)
      // {
      //
      // printf("This is a openSUSE Tumbleweed System...\n");
      // printf("Gonna tweak a bit the version :-)...\n");
      // m_pszVersion[4] = '\0';
      // printf("There it is ___new version : %s\n", m_pszVersion);
      //
      // }
      //
      // ::i8 szUrl[4096];

      ::string strUrl;

      if (m_strBranch.has_character())
      {

         strUrl.formatf("https://%s.ca2.site/%s/%s/%s/%s/%s.zip",
            m_strSystem.c_str(),
            m_strBranch.c_str(),
            m_strRelease.c_str(),
            m_strArchitecture.c_str(),
            m_strAppRoot.c_str(),
            m_strAppName.c_str());

      }
      else
      {

#ifdef WINDOWS

         strUrl.formatf("https://%s.ca2.site/%s/%s/%s.zip",
            m_strSystem.c_str(),
            m_strArchitecture.c_str(),
            m_strAppRoot.c_str(),
            m_strAppName.c_str());

#else

         strUrl.formatf("https://%s.ca2.site/%s/%s/%s/%s.zip",
            m_strSystem.c_str(),
            m_strRelease.c_str(),
            m_strArchitecture.c_str(),
            m_strAppRoot.c_str(),
            m_strAppName.c_str());

#endif


      }

      return strUrl;

   }


} // namespace launch


//    // void launch::log_system(const_char_pointer pszCommand)
//    // {
//    //
//    // printf("%s\n", pszCommand);
//    // ::system(scopedstrCommand);
//    //
//    // }
//
// void launch::install_dependencies()
// {
//
//
//    printf("Going to install dependencies:\n");
//
//    auto line = file_system()->as_string("operating_system_packages.txt");
//
//    if(!psz)
//    {
//
//       return;
//
//    }
//
//    auto pszCommand = (char_pointer ) ::malloc(strlen(scopedstr) + 1024);
//
//    auto len = strlen(scopedstrCommand);
//
//    for(::i32 i = 0; i < len; i++)
//    {
//
//       if(scopedstrCommand[i] == '\n' || pszCommand[i] == '\r')
//       {
//
//          pszCommand[i] = ' ';
//
//       }
//
//    }
//
//    if(!strcmp(m_pszDistro, "ubuntu") || !strcmp(m_pszDistro, "kubuntu"))
//    {
//
//       sprintf(scopedstrCommand, "sudo apt -y install %s", psz);
//
//       log_system(scopedstrCommand);
//
//  //     log_system("sudo apt -y install libfreeimage3 libstartup-notification0 libunac1 libxm4");
//
//    }
//    else if(!strcmp(m_pszDistro, "fedora"))
//    {
//
//       sprintf(scopedstrCommand, "sudo dnf --assumeyes install %s", psz);
//
//   //    log_system("sudo dnf --assumeyes install freeimage libidn motif libappindicator-gtk3");
//
//       log_system(scopedstrCommand);
//
//    }
//    else if(!strcmp(m_pszDistro, "freebsd"))
//    {
//
//     //  log_system("sudo pkg install freeimage open-motif openssl libappindicator");
//
//    }
//    else
//    {
//
//       printf("No known dependencies to install\n");
//
//    }
//
//
// }


// bool launch::check_http_ok(const_char_pointer pszUrl)
// {
//
// bool bOk = false;
//
// if (!strcasecmp(m_pszDistro, "freebsd"))
// {
//
// bOk = curl_check_http_ok(scopedstrUrl);
//
// }
// else
// {
//
// bOk = wget_check_http_ok(scopedstrUrl);
//
// }
//
// if (bOk)
// {
//
// printf("File at \"%s\" seems OK!\n", pszUrl);
//
// }
// else
// {
//
// printf("Resource at \"%s\" doesn't exist!\n", pszUrl);
//
// }
//
// return bOk;
//
// }
//
// } // namespace launch
//
//
//
// ::i32 main(::i32 argc, char_pointer argv[])
// {
//
//
//       ::launch::application application(argc, argv);
//
//    try
//    {
//       application.run();
//    }
//    catch(const_char_pointer psz)
//    {
//
//    fprintf(stderr, psz, 1, strlen(scopedstr));
//    }
//
//       return application.m_iExitCode;
//
// }
//


//
//
//#include "application.h"
//#include <stdio.h>
//#include <sys/stat.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <time.h>
//#include <memory.h>
//
//
//         bool wget_check_http_ok(const_char_pointer pszUrl)
//         {
//
//
//         ::i8 szCommand[4096];
//
//      strcpy(szCommand, "wget -S --spider ");
//      strcat(szCommand, pszUrl);
//      strcat(szCommand, " > wget_url_exists.txt");
//
//      system(szCommand);
//
//      auto psz = as_string("wget_url_exists.txt");
//
//      if(!psz)
//      {
//
//      return false;
//
//      }
//
//      while(true)//
//
//#include "application.h"
//#include <stdio.h>
//#include <sys/stat.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <time.h>
//#include <memory.h>
//
//
//         bool wget_check_http_ok(const_char_pointer pszUrl)
//         {
//
//
//         ::i8 szCommand[4096];
//
//      strcpy(szCommand, "wget -S --spider ");
//      strcat(szCommand, pszUrl);
//      strcat(szCommand, " > wget_url_exists.txt");
//
//      system(szCommand);
//
//      auto psz = as_string("wget_url_exists.txt");
//
//      if(!psz)
//      {
//
//      return false;
//
//      }
//
//      while(true)
//      {
//
//      auto pszNewLine = get_line(scopedstr, psz);
//
//      if(!pszNewLine)
//      {
//
//      return false;
//
//      }
//
//
//      if(scopedstrNewLine[0] == ' '
//      && pszNewLine[1] == ' '
//      && pszNewLine[2] == 'H'
//      && pszNewLine[3] == 'T'
//      && pszNewLine[4] == 'T'
//      && pszNewLine[5] == 'P'
//      && pszNewLine[6] == '/')
//      {
//
//      auto pszSpace = strchr(scopedstrNewLine + 6, ' ');
//
//      if(!pszSpace)
//      {
//
//      return false;
//
//      }
//
//      auto nonSpace = strspn(scopedstrSpace, " \t");
//
//      auto pszNonSpace = pszSpace + nonSpace;
//
//      auto pszNewLine = strpbrk(scopedstrNonSpace, "\r\n");
//
//      if(!pszNewLine)
//      {
//
//      return false;
//
//      }
//
//      if(!strncmp(scopedstrNonSpace, "200", pszNewLine - pszNonSpace))
//      {
//
//      return true;
//
//      }
//
//      return false;
//
//      }
//
//      }
//
//      }
//

//      {
//
//      auto pszNewLine = get_line(scopedstr, psz);
//
//      if(!pszNewLine)
//      {
//
//      return false;
//
//      }
//
//
//      if(scopedstrNewLine[0] == ' '
//      && pszNewLine[1] == ' '
//      && pszNewLine[2] == 'H'
//      && pszNewLine[3] == 'T'
//      && pszNewLine[4] == 'T'
//      && pszNewLine[5] == 'P'
//      && pszNewLine[6] == '/')
//      {
//
//      auto pszSpace = strchr(scopedstrNewLine + 6, ' ');
//
//      if(!pszSpace)
//      {
//
//      return false;
//
//      }
//
//      auto nonSpace = strspn(scopedstrSpace, " \t");
//
//      auto pszNonSpace = pszSpace + nonSpace;
//
//      auto pszNewLine = strpbrk(scopedstrNonSpace, "\r\n");
//
//      if(!pszNewLine)
//      {
//
//      return false;
//
//      }
//
//      if(!strncmp(scopedstrNonSpace, "200", pszNewLine - pszNonSpace))
//      {
//
//      return true;
//
//      }
//
//      return false;
//
//      }
//
//      }
//
//      }
//
//
// char_pointer start_temporary_file_name()
// {
//
//    ::i8 sz[8192];
//    ::i8 szCurDir[1024];
//    getcwd(szCurDir, sizeof(szCurDir));
//    auto ptmpname = tempnam(szCurDir, "tmpfl");
//    return ptmpname;
//
// }
//
//
// void end_temporary_file_name(char_pointer ptmpname)
// {
//
//    remove(ptmpname);
//
//    free(ptmpname);
//
// }
//
//
// char_pointer end_temporary_file_name_as_string(char_pointer ptmpname)
// {
//
//    auto p = as_string(ptmpname);
//
//    end_temporary_file_name(ptmpname);
//
//    return p;
//
// }


// char_pointer get_command_output(const_char_pointer pszCommand)
// {
//
//    auto ptmpname = start_temporary_file_name();
//
//    ::i8 sz[8129];
//
//    sprintf(sz, "%s &> %s", pszCommand, ptmpname);
//
//    printf("%s\n", sz);
//
//    system(sz);
//
//    auto p = end_temporary_file_name_as_string(ptmpname);
//
//    return p;
//
// }




