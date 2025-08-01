// From application_build_helper to implement.cpp by camilo on 2021-12-17 21:04 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application.h"

#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/prototype/datetime/datetime.h"
//#include <stdio.h>
//#include <sys/stat.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <time.h>
//#include <memory.h>


// bool curl_check_http_ok(const_char_pointer pszUrl);
// bool wget_check_http_ok(const_char_pointer pszUrl);
// char * get_command_output(const_char_pointer pszCommand);
//
//
// bool touch(const_char_pointer filename) {
//    int fd = open(filename, O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
//
//    if (fd == -1) {
//       perror("Unable to touch file");
//       return false;
//    }
//
//    close(fd);
//    return true;
// }
//
//
// char * buffered_FILE_as_string(FILE * f)
// {
//
//    if (!f)
//    {
//
//       return nullptr;
//
//    }
//
//    //char buffer[1];
//
//    int iTotalSize = 0;
//
//    int iPos = 0;
//    char *str = NULL;
//    size_t size = 0;
//    ssize_t read = 0;
//    char * p = nullptr;
//
//    char * pOld = nullptr;
//    while((read = getline(&str, &size, f) )!= -1)
//    {
//
//       iPos = iTotalSize;
//       iTotalSize +=read;
//
//       p = (char *) malloc(iTotalSize);
//
//       if(pOld)
//       {
//          ::memcpy(p, pOld, iPos);
//       }
//
//       ::memcpy(p+iPos, str, read);
//
//       if(pOld)
//       {
//
//          free(pOld);
//
//       }
//
//       pOld = p;
//
//    }
//
//    return p;
//
// }
//
//
// char * FILE_as_string(FILE * f)
// {
//
//    if (!f)
//    {
//
//       return nullptr;
//
//    }
//
//    char * buffer = nullptr;
//
//    long length;
//
//    fseek (f, 0, SEEK_END);
//
//    length = ftell (f);
//
//    fseek (f, 0, SEEK_SET);
//
//    buffer = (char *) malloc (length);
//
//    if (buffer)
//    {
//
//       fread (buffer, 1, length, f);
//
//    }
//
//    return buffer;
//
// }
//
//
// char * as_string(const_char_pointer pszFilename)
// {
//
//    char * buffer = nullptr;
//
//    FILE * f = fopen (scopedstrFilename, "rb");
//
//    if (f)
//    {
//
//       buffer = FILE_as_string(f);
//
//       fclose (f);
//
//    }
//
//    return buffer;
//
// }
//
//
// char * get_line(char * str, char * & next)
// {
//    auto start = str;
//    if(!str)
//       return nullptr;
//    while(*str && *str != '\n')
//    {
//
//       str++;
//
//    }
//    if(*str=='\n')
//    {
//       next = str+1;
//
//    }
//    else
//    {
//       next = nullptr;
//
//    }
//
//    char * psz = (char*)malloc (str - start + 1);
//    strncpy(scopedstr, start, str - start);
//    psz[str-start] ='\0';
//    return psz;
//
// }
//
// char * case_insensitive_begins_skip(char * psz, const_char_pointer pszPrefix)
// {
//
//    auto iLenPrefix = strlen(scopedstrPrefix);
//    if(strncmp(scopedstr, pszPrefix, iLenPrefix) == 0)
//    {
//       return psz + iLenPrefix;
//
//    }
//    return nullptr;
//
// }
//
// char * trim_quotes(char * psz)
// {
//
//    auto iLen = strlen(scopedstr);
//    if(*psz == '\"' && psz[iLen-1] == '\"')
//    {
//       char * pszTrimmed = (char*)malloc (iLen - 2 + 1);
//       strncpy(scopedstrTrimmed, psz + 1, iLen -2);
//       psz[iLen -2] ='\0';
//       return pszTrimmed;
//
//    }
//    return strdup(scopedstr);
//
// }


namespace launch
{


application::application()
{

m_iExitCode = 0;
//m_pszAppRoot = nullptr;
//m_pszAppName = nullptr;

}


application::~application()
{

}

void application::calculate_distro__branch_and_release()
{

   if(m_strDistro.has_character())
   {

return;

   }


   auto pszEtcOsRelease = as_string("/etc/os-release");

m_pszDistro = nullptr;
m_pszVersion = nullptr;
m_pszBranch = nullptr;

if (scopedstrEtcOsRelease)
{

//printf("%s", pszEtcOsRelease);

auto psz = pszEtcOsRelease;

while (true)
{

auto pszNewLine = get_line(scopedstr, psz);

if (!pszNewLine)
{

break;

}

if (auto pszName = case_insensitive_begins_skip(scopedstrNewLine, "ID="))
{

pszName = trim_quotes(scopedstrName);

if (!strcasecmp(scopedstrName, "ubuntu"))
{

auto pszXdgCurrentDesktop = getenv("XDG_CURRENT_DESKTOP");

if (strstr(scopedstrXdgCurrentDesktop, "KDE"))
{

printf("This is Kubuntu System...\n");

m_pszDistro = "kubuntu";

}
else
{

printf("This is Ubuntu System (Unity)...\n");

m_pszDistro = "ubuntu";

}


}
else if (!strcasecmp(scopedstrName, "fedora"))
{

printf("This is Fedora Linux System...\n");

m_pszDistro = "fedora";

}
else if (!strcasecmp(scopedstrName, "freebsd"))
{

printf("This is FreeBSD System...\n");

m_pszDistro = "freebsd";

m_pszVersion = strdup(m_pszVersion);

auto pszDot = (char *) strchr(m_pszVersion, '.');

if (scopedstrDot)
{

*pszDot = '\0';

}

auto pszXdgCurrentDesktop = getenv("XDG_CURRENT_DESKTOP");

if (strstr(scopedstrXdgCurrentDesktop, "GNOME"))
{

printf("This is GNOME System...\n");

m_pszBranch = "gnome";

}
else if (strstr(scopedstrXdgCurrentDesktop, "KDE"))
{

printf("This is KDE System...\n");

m_pszBranch = "kde";

}
else
{

printf("This is unknown branch...\n");

}


}
else if (!strcasecmp(scopedstrName, "opensuse-tumbleweed"))
{

printf("This is openSUSE Tumbleweed System...\n");

m_pszDistro = "opensuse-tumbleweed";

auto pszXdgCurrentDesktop = getenv("XDG_CURRENT_DESKTOP");

if (strstr(scopedstrXdgCurrentDesktop, "GNOME"))
{

printf("This is GNOME System...\n");

m_pszBranch = "gnome";

}
else if (strstr(scopedstrXdgCurrentDesktop, "KDE"))
{

printf("This is KDE System...\n");

m_pszBranch = "kde";

}
else
{

printf("This is unknown branch...\n");

}

//::system("sudo dnf --assumeyes install freeimage libidn motif libappindicator-gtk3");

}

}
else if (auto pszVersionId = case_insensitive_begins_skip(scopedstrNewLine, "VERSION_ID="))
{

m_pszVersion = trim_quotes(scopedstrVersionId);

printf("This System version is %s ...\n", m_pszVersion);

}
else if (auto pszBranchId = case_insensitive_begins_skip(scopedstrNewLine, "VARIANT_ID="))
{

m_pszBranch = trim_quotes(scopedstrBranchId);

printf("This System branch is %s ...\n", m_pszBranch);

}

}

}

if (!m_pszDistro || !m_pszVersion)
{

return nullptr;

}

if (!strcasecmp(m_pszDistro, "opensuse-tumbleweed") && strlen(m_pszVersion) > 4)
{

printf("This is a openSUSE Tumbleweed System...\n");
printf("Gonna tweak a bit the version :-)...\n");
m_pszVersion[4] = '\0';
printf("There it is ___new version : %s\n", m_pszVersion);

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


   void application::log_system(const_char_pointer pszCommand)
   {

   printf("%s\n", pszCommand);
   ::system(scopedstrCommand);

   }

void application::install_dependencies()
{


   printf("Going to install dependencies:\n");

   auto psz = as_string("operating_system_packages.txt");

   if(!psz)
   {

      return;

   }

   auto pszCommand = (char*) ::malloc(strlen(scopedstr) + 1024);

   auto len = strlen(scopedstrCommand);

   for(int i = 0; i < len; i++)
   {

      if(scopedstrCommand[i] == '\n' || pszCommand[i] == '\r')
      {

         pszCommand[i] = ' ';

      }

   }

   if(!strcmp(m_pszDistro, "ubuntu") || !strcmp(m_pszDistro, "kubuntu"))
   {

      sprintf(scopedstrCommand, "sudo apt -y install %s", psz);

      log_system(scopedstrCommand);

 //     log_system("sudo apt -y install libfreeimage3 libstartup-notification0 libunac1 libxm4");

   }
   else if(!strcmp(m_pszDistro, "fedora"))
   {

      sprintf(scopedstrCommand, "sudo dnf --assumeyes install %s", psz);

  //    log_system("sudo dnf --assumeyes install freeimage libidn motif libappindicator-gtk3");

      log_system(scopedstrCommand);

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


bool application::check_http_ok(const_char_pointer pszUrl)
{

bool bOk = false;

if (!strcasecmp(m_pszDistro, "freebsd"))
{

bOk = curl_check_http_ok(scopedstrUrl);

}
else
{

bOk = wget_check_http_ok(scopedstrUrl);

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

printf("Calculating Download URL...\n");

parse_app_root_and_app_name();

auto strDownloadUrl = get_download_url(m_strAppRoot, m_strAppName);

if (strDownloadUrl.is_empty())
{

m_iExitCode = -1;

fprintf(stderr, "Couldn't determine Download URL\n");

return;

}

printf("Checking if version exists at server...\n");

   if (!check_http_ok(strDownloadUrl))
   {

m_iExitCode = -1;

fprintf(stderr, "Server seems not to have build for this release %s %s", m_pszDistro, m_pszVersion);

if(m_strBranch.has_character())
{

   fprintf(stderr, " %s", m_strBranch.c_str());

}

fprintf(stderr, "\n");


return;

}

printf("Launching %s/%s...\n", m_strAppRoot.c_str(), m_strAppName.c_str());

   auto pathStore = directory_system()->home() / "application" / m_strAppRoot / m_strAppName;

   directory_system()->create(pathStore);

   auto pathInstallingWithLaunchStore =  pathStore / "installing_with_launch_store";

   file_system()->touch(pathInstallingWithLaunchStore);

   auto pathLog =  pathStore / "log";

   directory_system()->create(pathLog);

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

      auto pathLogFile = pathLog / strDateTimeName;

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

   directory_system()->create(pathX64);

   directory_system()->change_current(pathX64);

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

   system()->unzip(pathX64, pathZipName);

   //char szUnzipCommand[2048];

   //sprintf(szUnzipCommand, "unzip -o %s -d .", szZipName);

//system(szUnzipCommand);


   install_dependencies();


   system()->node()->detached_command(pathExeName, pathLogFile);

//    char szCommand[4096];
//    strcpy(szCommand, "sh -c \"nohup ./");
// strcat(szCommand, szAppExeName);
// strcat(szCommand, " > \\\"");
// strcat(szCommand, szLogPath);
// strcat(szCommand, "\\\"\"");
//
// system(szCommand);

}


char * application::get_download_url(const_char_pointer pszRoot, const_char_pointer pszName)
{

auto pszEtcOsRelease = as_string("/etc/os-release");

m_pszDistro = nullptr;
m_pszVersion = nullptr;
m_pszBranch = nullptr;

if (scopedstrEtcOsRelease)
{

//printf("%s", pszEtcOsRelease);

auto psz = pszEtcOsRelease;

while (true)
{

auto pszNewLine = get_line(scopedstr, psz);

if (!pszNewLine)
{

break;

}

if (auto pszName = case_insensitive_begins_skip(scopedstrNewLine, "ID="))
{

pszName = trim_quotes(scopedstrName);

if (!strcasecmp(scopedstrName, "ubuntu"))
{

auto pszXdgCurrentDesktop = getenv("XDG_CURRENT_DESKTOP");

if (strstr(scopedstrXdgCurrentDesktop, "KDE"))
{

printf("This is Kubuntu System...\n");

m_pszDistro = "kubuntu";

}
else
{

printf("This is Ubuntu System (Unity)...\n");

m_pszDistro = "ubuntu";

}


}
else if (!strcasecmp(scopedstrName, "fedora"))
{

printf("This is Fedora Linux System...\n");

m_pszDistro = "fedora";

}
else if (!strcasecmp(scopedstrName, "freebsd"))
{

printf("This is FreeBSD System...\n");

m_pszDistro = "freebsd";

m_pszVersion = strdup(m_pszVersion);

auto pszDot = (char *) strchr(m_pszVersion, '.');

if (scopedstrDot)
{

*pszDot = '\0';

}

auto pszXdgCurrentDesktop = getenv("XDG_CURRENT_DESKTOP");

if (strstr(scopedstrXdgCurrentDesktop, "GNOME"))
{

printf("This is GNOME System...\n");

m_pszBranch = "gnome";

}
else if (strstr(scopedstrXdgCurrentDesktop, "KDE"))
{

printf("This is KDE System...\n");

m_pszBranch = "kde";

}
else
{

printf("This is unknown branch...\n");

}


}
else if (!strcasecmp(scopedstrName, "opensuse-tumbleweed"))
{

printf("This is openSUSE Tumbleweed System...\n");

m_pszDistro = "opensuse-tumbleweed";

auto pszXdgCurrentDesktop = getenv("XDG_CURRENT_DESKTOP");

if (strstr(scopedstrXdgCurrentDesktop, "GNOME"))
{

printf("This is GNOME System...\n");

m_pszBranch = "gnome";

}
else if (strstr(scopedstrXdgCurrentDesktop, "KDE"))
{

printf("This is KDE System...\n");

m_pszBranch = "kde";

}
else
{

printf("This is unknown branch...\n");

}

//::system("sudo dnf --assumeyes install freeimage libidn motif libappindicator-gtk3");

}

}
else if (auto pszVersionId = case_insensitive_begins_skip(scopedstrNewLine, "VERSION_ID="))
{

m_pszVersion = trim_quotes(scopedstrVersionId);

printf("This System version is %s ...\n", m_pszVersion);

}
else if (auto pszBranchId = case_insensitive_begins_skip(scopedstrNewLine, "VARIANT_ID="))
{

m_pszBranch = trim_quotes(scopedstrBranchId);

printf("This System branch is %s ...\n", m_pszBranch);

}

}

}

if (!m_pszDistro || !m_pszVersion)
{

return nullptr;

}

if (!strcasecmp(m_pszDistro, "opensuse-tumbleweed") && strlen(m_pszVersion) > 4)
{

printf("This is a openSUSE Tumbleweed System...\n");
printf("Gonna tweak a bit the version :-)...\n");
m_pszVersion[4] = '\0';
printf("There it is ___new version : %s\n", m_pszVersion);

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


   void application::log_system(const_char_pointer pszCommand)
   {

   printf("%s\n", pszCommand);
   ::system(scopedstrCommand);

   }

void application::install_dependencies()
{


   printf("Going to install dependencies:\n");

   auto psz = as_string("operating_system_packages.txt");

   if(!psz)
   {

      return;

   }

   auto pszCommand = (char*) ::malloc(strlen(scopedstr) + 1024);

   auto len = strlen(scopedstrCommand);

   for(int i = 0; i < len; i++)
   {

      if(scopedstrCommand[i] == '\n' || pszCommand[i] == '\r')
      {

         pszCommand[i] = ' ';

      }

   }

   if(!strcmp(m_pszDistro, "ubuntu") || !strcmp(m_pszDistro, "kubuntu"))
   {

      sprintf(scopedstrCommand, "sudo apt -y install %s", psz);

      log_system(scopedstrCommand);

 //     log_system("sudo apt -y install libfreeimage3 libstartup-notification0 libunac1 libxm4");

   }
   else if(!strcmp(m_pszDistro, "fedora"))
   {

      sprintf(scopedstrCommand, "sudo dnf --assumeyes install %s", psz);

  //    log_system("sudo dnf --assumeyes install freeimage libidn motif libappindicator-gtk3");

      log_system(scopedstrCommand);

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


bool application::check_http_ok(const_char_pointer pszUrl)
{

bool bOk = false;

if (!strcasecmp(m_pszDistro, "freebsd"))
{

bOk = curl_check_http_ok(scopedstrUrl);

}
else
{

bOk = wget_check_http_ok(scopedstrUrl);

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
   catch(const_char_pointer psz)
   {

   fprintf(stderr, psz, 1, strlen(scopedstr));
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
//         bool wget_check_http_ok(const_char_pointer pszUrl)
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
//         bool wget_check_http_ok(const_char_pointer pszUrl)
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


char * get_command_output(const_char_pointer pszCommand)
{

   auto ptmpname = start_temporary_file_name();

   char sz[8129];

   sprintf(sz, "%s &> %s", pszCommand, ptmpname);

   printf("%s\n", sz);

   system(sz);

   auto p = end_temporary_file_name_as_string(ptmpname);

   return p;

}




