// From application_build_helper to implement.cpp by camilo on 2021-12-17 21:04 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/nano/nano.h"
#include "acme/nano/http/http.h"
#include "acme/operating_system/summary.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/primitive/datetime/datetime.h"


namespace launch
{


application::application()
{

m_iExitCode = 0;

}


application::~application()
{

}

void application::calculate_distro__branch_and_release()
{

   if(m_strDistro.has_char())
   {

return;

   }


   auto psummary = node()->operating_system_summary();


   m_strDistro = psummary->m_strDistro;

   m_strDistro.make_lower();

   ::string strBranch = psummary->m_strDistroBranch;

   strBranch.make_lower();

   if (m_strDistro == "ubuntu")
   {
      if (strBranch == "kde")
      {
         m_strDistro = "kubuntu";
         print_line("This is Kubuntu System...");
      }
      else if(strBranch == "xfce")
      {
         m_strDistro = "xubuntu";
         print_line("This is Xubuntu System...");
      }
      else
      {
         print_line("This is Ubuntu System (Unity)...");
      }
   }
   else if (m_strDistro == "fedora")
   {

      print_line("This is Fedora Linux System...\n");

      m_strBranch = strBranch;

   }
   else if (m_strDistro == "freebsd")
   {

      print_line("This is FreeBSD System...");

      m_strBranch = strBranch;

   }
   else if (m_strDistro == "opensuse-tumbleweed")
   {

      print_line("This is openSUSE Tumbleweed System...\n");

      m_strBranch = strBranch;

   }

   m_strRelease = psummary->m_strStoreRelease;


   }


   // void application::log_system(const char * pszCommand)
   // {
   //
   // printf("%s\n", pszCommand);
   // ::system(pszCommand);
   //
   // }

void application::install_dependencies()
{


   printf("Going to install dependencies:\n");

   auto lines = acmefile()->lines("operating_system_packages.txt");

   if(lines.is_empty())
   {

      print_line("no dependencies to install");

      return;

   }

   ::string strPackages;

   strPackages = lines.implode(" ");

   ::string strCommand;

   if(m_strDistro == "ubuntu" || m_strDistro == "kubuntu" || m_strDistro == "xubuntu")
   {

      strCommand.formatf("sudo apt -y install %s", strPackages.c_str());

 //     log_system("sudo apt -y install libfreeimage3 libstartup-notification0 libunac1 libxm4");

   }
   else if(m_strDistro ==  "fedora")
   {

      strCommand.formatf("sudo dnf --assumeyes install %s",strPackages.c_str());

  //    log_system("sudo dnf --assumeyes install freeimage libidn motif libappindicator-gtk3");

      //log_system(pszCommand);

   }
   else if(m_strDistro == "freebsd")
   {

      strCommand.formatf("sudo pkg install %s", strPackages.c_str());

   }
   else
   {

      printf_line("Don't know how to install dependencies for this system. (%s)", strPackages.c_str());

   }

   if(strCommand.has_char())
   {

      //log_system(strCommand);

      print_line(strCommand);

      ::system(strCommand);


   }

}


// bool application::check_http_ok(const char * pszUrl)
// {
//
// bool bOk = false;
//
// if (!strcasecmp(m_pszDistro, "freebsd"))
// {
//
// bOk = curl_check_http_ok(pszUrl);
//
// }
// else
// {
//
// bOk = wget_check_http_ok(pszUrl);
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
//
// }


void application::parse_app_root_and_app_name()
{

   if(m_strLaunchAppId.is_empty())
   {

      if(m_argc <= 1)
      {

         throw "Wrong number of arguments";

      }

      m_strLaunchAppId = m_argv[1];
;
   }

   auto iSlash = m_strLaunchAppId.find_index('/');

   if(iSlash < 0 || iSlash == 0 || iSlash >= m_strLaunchAppId.last_index())
   {

      throw "App Id must contain one slash and only one slash separating app_root and app_name";

   }

   m_strAppRoot = m_strLaunchAppId(0, iSlash);

   m_pszAppName = m_strLaunchAppId(iSlash + 1);

}


   void application::run()
   {

      print_line("Calculating Download URL...");

      parse_app_root_and_app_name();

      auto strDownloadUrl = get_download_url(m_strAppRoot, m_strAppName);

      if (strDownloadUrl.is_empty())
      {

         m_iExitCode = -1;

         err_line("Couldn't determine Download URL");

         return;

      }

         print_line("Checking if version exists at server...");

      if (!nano()->http()->check_url_ok(strDownloadUrl))
         {

      m_iExitCode = -1;

         ::string strErr;

         strErr.formatf("Server seems not to have build for this release %s %s", m_strDistro.c_str(), m_strRelease.c_str());

         if(m_strBranch.has_char())
         {

            strErr += " " + m_strBranch;

         }

         err_line(strErr);

      return;

   }

      printf_line("Launching %s/%s...", m_strAppRoot.c_str(), m_strAppName.c_str());

   auto pathStore = acmedirectory()->home() / "application" / m_strAppRoot / m_strAppName;

   acmedirectory()->create(pathStore);

   auto pathInstallingWithLaunchStore =  pathStore / "installing_with_launch_store";

   acmefile()->touch(pathInstallingWithLaunchStore);

   auto pathLogFolder =  pathStore / "log";

   acmedirectory()->create(pathLogFolder);

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

   auto pathX64 = pathStore / "x64";
// char szX64[4096];
//
// strcpy(szX64, szStore);
//
// strcat(szX64, "/x64");
//
// mkdir(szX64, 0777);
//
// chdir(szX64);

   acmedirectory()->create(pathX64);

   acmedirectory()->change_current(pathX64);

#ifdef LINUX

   ::string strExecutable = "_" + m_strAppRoot + "_" + m_strAppName;

#else

   ::string strExecutable = "shared_" + m_strAppRoot + "_" m_strAppName + ".exe";

#endif

//    char szAppExeName[1024];
//    sprintf(szAppExeName, "_%s_%s", m_pszAppRoot, m_pszAppName);
//
//    for(int i = 0; i < strlen(szAppExeName); i++)
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


   ::string strZipName;

   strZipName = "_" + strExecutable + ".zip";
   // char szZipName[1024];
   // sprintf(szZipName, "_%s.zip", szAppExeName);
   // char szDownloadCommand[2048];

   auto pathZipName = pathX64 / strZipName;

   system()->http_download(pathZipName,strDownloadUrl );
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



//system(szDownloadCommand);

   nano()->compress()->unzip(pathX64, pathZipName);

   //char szUnzipCommand[2048];

   //sprintf(szUnzipCommand, "unzip -o %s -d .", szZipName);

//system(szUnzipCommand);


   install_dependencies();


   nano()->shell()->launch_no_hup(pathExeName, pathLogFile);

//    char szCommand[4096];
//    strcpy(szCommand, "sh -c \"nohup ./");
// strcat(szCommand, szAppExeName);
// strcat(szCommand, " > \\\"");
// strcat(szCommand, szLogPath);
// strcat(szCommand, "\\\"\"");
//
// system(szCommand);

}


::string application::get_download_url(const char * pszRoot, const char * pszName)
{

   calculate_distro__branch_and_release();

   if (m_strDistro.is_empty() || m_strRelease.is_empty())
   {

      return {};

   }

if (!strcasecmp(m_pszDistro, "opensuse-tumbleweed") && strlen(m_pszVersion) > 4)
{

printf("This is a openSUSE Tumbleweed System...\n");
printf("Gonna tweak a bit the version :-)...\n");
m_pszVersion[4] = '\0';
printf("There it is new version : %s\n", m_pszVersion);

}

char szUrl[4096];

if (m_pszBranch)
{

sprintf(szUrl, "https://%s.ca2.store/%s/%s/%s/%s.zip", m_pszDistro, m_pszBranch, m_pszVersion, pszRoot, pszName);

}
else
{

sprintf(szUrl, "https://%s.ca2.store/%s/%s/%s.zip", m_pszDistro, m_pszVersion, pszRoot, pszName);

}

return strdup(szUrl);

}


   // void application::log_system(const char * pszCommand)
   // {
   //
   // printf("%s\n", pszCommand);
   // ::system(pszCommand);
   //
   // }

void application::install_dependencies()
{


   printf("Going to install dependencies:\n");

   auto psz = as_string("operating_system_packages.txt");

   if(!psz)
   {

      return;

   }

   auto pszCommand = (char*) ::malloc(strlen(psz) + 1024);

   auto len = strlen(pszCommand);

   for(int i = 0; i < len; i++)
   {

      if(pszCommand[i] == '\n' || pszCommand[i] == '\r')
      {

         pszCommand[i] = ' ';

      }

   }

   if(!strcmp(m_pszDistro, "ubuntu") || !strcmp(m_pszDistro, "kubuntu"))
   {

      sprintf(pszCommand, "sudo apt -y install %s", psz);

      log_system(pszCommand);

 //     log_system("sudo apt -y install libfreeimage3 libstartup-notification0 libunac1 libxm4");

   }
   else if(!strcmp(m_pszDistro, "fedora"))
   {

      sprintf(pszCommand, "sudo dnf --assumeyes install %s", psz);

  //    log_system("sudo dnf --assumeyes install freeimage libidn motif libappindicator-gtk3");

      log_system(pszCommand);

   }
   else if(!strcmp(m_pszDistro, "freebsd"))
   {

    //  log_system("sudo pkg install freeimage open-motif openssl libappindicator");

   }
   else
   {

      printf("No known dependencies to install\n");

   }


}


bool application::check_http_ok(const char * pszUrl)
{

bool bOk = false;

if (!strcasecmp(m_pszDistro, "freebsd"))
{

bOk = curl_check_http_ok(pszUrl);

}
else
{

bOk = wget_check_http_ok(pszUrl);

}

if (bOk)
{

printf("File at \"%s\" seems OK!\n", pszUrl);

}
else
{

printf("Resource at \"%s\" doesn't exist!\n", pszUrl);

}

return bOk;

}

} // namespace launch



int main(int argc, char * argv[])
{


      ::launch::application application(argc, argv);

   try
   {
      application.run();
   }
   catch(const char * psz)
   {

   fprintf(stderr, psz, 1, strlen(psz));
   }

      return application.m_iExitCode;

}



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
//         bool wget_check_http_ok(const char * pszUrl)
//         {
//
//
//         char szCommand[4096];
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
//         bool wget_check_http_ok(const char * pszUrl)
//         {
//
//
//         char szCommand[4096];
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
//      auto pszNewLine = get_line(psz, psz);
//
//      if(!pszNewLine)
//      {
//
//      return false;
//
//      }
//
//
//      if(pszNewLine[0] == ' '
//      && pszNewLine[1] == ' '
//      && pszNewLine[2] == 'H'
//      && pszNewLine[3] == 'T'
//      && pszNewLine[4] == 'T'
//      && pszNewLine[5] == 'P'
//      && pszNewLine[6] == '/')
//      {
//
//      auto pszSpace = strchr(pszNewLine + 6, ' ');
//
//      if(!pszSpace)
//      {
//
//      return false;
//
//      }
//
//      auto nonSpace = strspn(pszSpace, " \t");
//
//      auto pszNonSpace = pszSpace + nonSpace;
//
//      auto pszNewLine = strpbrk(pszNonSpace, "\r\n");
//
//      if(!pszNewLine)
//      {
//
//      return false;
//
//      }
//
//      if(!strncmp(pszNonSpace, "200", pszNewLine - pszNonSpace))
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
//      auto pszNewLine = get_line(psz, psz);
//
//      if(!pszNewLine)
//      {
//
//      return false;
//
//      }
//
//
//      if(pszNewLine[0] == ' '
//      && pszNewLine[1] == ' '
//      && pszNewLine[2] == 'H'
//      && pszNewLine[3] == 'T'
//      && pszNewLine[4] == 'T'
//      && pszNewLine[5] == 'P'
//      && pszNewLine[6] == '/')
//      {
//
//      auto pszSpace = strchr(pszNewLine + 6, ' ');
//
//      if(!pszSpace)
//      {
//
//      return false;
//
//      }
//
//      auto nonSpace = strspn(pszSpace, " \t");
//
//      auto pszNonSpace = pszSpace + nonSpace;
//
//      auto pszNewLine = strpbrk(pszNonSpace, "\r\n");
//
//      if(!pszNewLine)
//      {
//
//      return false;
//
//      }
//
//      if(!strncmp(pszNonSpace, "200", pszNewLine - pszNonSpace))
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

char * start_temporary_file_name()
{

   char sz[8192];
   char szCurDir[1024];
   getcwd(szCurDir, sizeof(szCurDir));
   auto ptmpname = tempnam(szCurDir, "tmpfl");
   return ptmpname;

}


void end_temporary_file_name(char * ptmpname)
{

   remove(ptmpname);

   free(ptmpname);

}


char * end_temporary_file_name_as_string(char * ptmpname)
{

   auto p = as_string(ptmpname);

   end_temporary_file_name(ptmpname);

   return p;

}


char * get_command_output(const char * pszCommand)
{

   auto ptmpname = start_temporary_file_name();

   char sz[8129];

   sprintf(sz, "%s &> %s", pszCommand, ptmpname);

   printf("%s\n", sz);

   system(sz);

   auto p = end_temporary_file_name_as_string(ptmpname);

   return p;

}




