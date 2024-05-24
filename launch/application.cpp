// From application_build_helper to implement.cpp by camilo on 2021-12-17 21:04 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application.h"
#include "ace/filesystem/filesystem/filesystem.h"
#include "ace/primitive/string/string.h"
#include "ace/platform/application.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



namespace launch
{


   application::application()
   {
      //
      // m_iExitCode = 0;
      // m_pszAppRoot = nullptr;
      // m_pszAppName = nullptr;
   }


   application::~application()
   {
   }


   void application::parse_app_root_and_app_name()
   {
      if (m_argc <= 1)
      {
         throw "Wrong number of arguments";
      }

      auto p = strchr(m_args[1], '/');

      if (!p || p == m_args[1] || (p - m_args[1]) >= (strlen(m_args[1]) - 1))
      {
         throw "App Id must contain one slash and only one slash separating app_root and app_name";
      }

      m_strAppRoot.assign(m_args[1], p - m_args[1]);

      //   m_pszAppRoot[p -m_argv[1]] = '\0';

      m_strAppName = p + 1;
   }


   void application::run()
   {

      information_log("Calculating Download URL...");

      parse_app_root_and_app_name();

      ::ace::string strDownloadUrl = get_download_url(m_strAppRoot, m_strAppName);

      if (strDownloadUrl.is_empty())
      {
         m_iExitCode = -1;

         error_log("Couldn't determine Download URL");

         return;
      }

      ::ace::information_log("Checking if version exists at server...");

      if (!check_http_ok(strDownloadUrl))
      {

         m_iExitCode = -1;

         errorf_log("Server seems not to have build for this release %s %s", m_strDistro.c_str(),
                                 m_strVersion.c_str());

         if (m_strBranch)
         {

            errorf_log(" %s", m_strBranch.c_str());

         }

         error_log("\n");

         return;

      }

      informationf_log("Launching %s/%s...", m_strAppRoot.c_str(), m_strAppName.c_str());

      ::ace::string strHome(getenv("HOME"));

      ::ace::string strApplication(strHome);

      strApplication /= "application";

      ::ace::create_directory(strApplication, 0777);

      ::ace::string strAppCore(strApplication);

      strAppCore /= m_strAppRoot;

      ::ace::create_directory(strAppCore);

      ::ace::string strStore;

      strStore += strAppCore;

      strStore /= m_strAppName;

      ::ace::create_directory(strStore);

      ::ace::string strInstallingWithLaunchStore(strStore);

      strInstallingWithLaunchStore /= "installing_with_launch_store";

      ::ace::touch_file(strInstallingWithLaunchStore);

      ::ace::string strLog(strStore);

      strLog /= "log";

      ::ace::create_directory(strLog);

      auto t = ::time(nullptr);

      auto ptm = localtime(&t);

      ::ace::string strLogFilename;

      strLogFilename.formatf(
         "%04d-%02d-%02d_%02d-%02d-%02d.txt",
         ptm->tm_year,
         ptm->tm_mon,
         ptm->tm_mday,
         ptm->tm_hour,
         ptm->tm_min,
         ptm->tm_sec);

      ::ace::string strLogPath(strLog);

      strLogPath /= strLogFilename;

      ::ace::string strX64(strStore);

      strStore /= "x64";

      ::ace::create_directory(strX64);

      ::ace::change_directory(strX64);

   ::ace::string strAppExeName;
   strAppExeName.formatf("_%s_%s", m_strAppRoot, m_strAppName);

   strAppExeName.find_replace_character('-', '_');

   ::ace::string strZipName;
   strZipName.formatf("_%s.zip", strAppExeName.c_str());
   ::ace::string strDownloadCommand;
if (m_strDistro.case_insensitive_equals("freebsd"))
   {

strDownloadCommand = "curl ";
strDownloadCommand += strDownloadUrl;
strDownloadCommand += " > ";
strDownloadCommand += strZipName;

}
else
{
strDownloadCommand = "wget ";
strDownloadCommand += strDownloadUrl;
strDownloadCommand += " -O ";
strDownloadCommand += strZipName;

}



system(strDownloadCommand);

   char szUnzipCommand[2048];

   sprintf(szUnzipCommand, "unzip -o %s -d .", strZipName.c_str());

system(szUnzipCommand);


install_dependencies();


::ace::string strCommand;


strCommand = "sh -c \"nohup ./";
strCommand += strAppExeName;
strCommand += " > \\\"";
strCommand += strLogPath;
strCommand += "\\\"\"";


system(strCommand);


}


::ace::string application::get_download_url(const char * pszRoot, const char * pszName)
{


::ace::string strUrl;

if (m_strBranch)
{

   strUrl.formatf("https://%s.ca2.store/%s/%s/%s/%s.zip", m_strDistro.c_str(), m_strBranch.c_str(), m_strVersion.c_str(), pszRoot, pszName);

}
else
{

   strUrl.formatf("https://%s.ca2.store/%s/%s/%s.zip", m_strDistro.c_str(), m_strVersion.c_str(), pszRoot, pszName);

}

return strUrl;

}


   void application::log_system(const char * pszCommand)
   {

      ::ace::information_log(pszCommand);

      ::system(pszCommand);

   }


void application::install_dependencies()
{


   printf("Going to install dependencies:\n");

   auto str = ::ace::file_as_string("operating_system_packages.txt");

   if(!str)
   {

      return;

   }

   auto strPackages = str;

   strPackages.find_replace_character('\n', ' ');
   strPackages.find_replace_character('\r', ' ');

   if(!m_strDistro.case_insensitive_equals("ubuntu") || !m_strDistro.case_insensitive_equals("kubuntu"))
   {

      ::ace::string strCommand;

      strCommand.append_formatf("sudo apt -y install %s", strPackages.c_str());

      log_system(strCommand);

 //     log_system("sudo apt -y install libfreeimage3 libstartup-notification0 libunac1 libxm4");

   }
   else if(!m_strDistro.case_insensitive_equals("fedora"))
   {

      ::ace::string strCommand;

      strCommand.append_formatf("sudo dnf --assumeyes install %s", strPackages.c_str());

  //    log_system("sudo dnf --assumeyes install freeimage libidn motif libappindicator-gtk3");

      log_system(strCommand);

   }
   else if(!m_strDistro.case_insensitive_equals("freebsd"))
   {

    //  log_system("sudo pkg install freeimage open-motif openssl libappindicator");

   }
   else
   {

      printf("No known dependencies to install\n");

   }


}



} // namespace launch



int main(int argc, const char * args[])
{

   return ::ace::main < ::launch::application >(argc, args);

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




// void end_temporary_file_name(const char * ptmpname)
// {
//
//    remove(ptmpname);
//
//    free((void*) ptmpname);
//
// }


// ::ace::string end_temporary_file_name_as_string(const char * ptmpname)
// {
//
//    auto p = ::ace::file_as_string(ptmpname);
//
//    end_temporary_file_name(ptmpname);
//
//    return p;
//
// }


