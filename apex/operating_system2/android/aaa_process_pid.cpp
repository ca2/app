#include "framework.h"
#include <dirent.h>

int get_process_pid(const char * procNameParam)
{

   string procName(procNameParam);

   int pid = -1;

   // Open the /proc directory
   DIR *dp = opendir("/proc");
   if (dp != nullptr)
   {
      // Enumerate all entries in directory until process found
      struct dirent *dirp;
      while (pid < 0 && (dirp = readdir(dp)))
      {
         // Skip non-numeric entries
         int atom = atoi(dirp->d_name);
         if (atom > 0)
         {
            // Read contents of virtual /proc/{pid}/cmdline file
            string cmdPath = string("/proc/") + dirp->d_name + "/cmdline";
            FILE * cmdFile = fopen(cmdPath, "rb");

            string cmdLine;

            auto estatus = fgets_string(cmdLine, cmdFile, 1024 * 256);

            if(estatus && cmdLine.has_character())
            {
               // Keep first cmdline item which contains the program path
               character_count pos = cmdLine.find('\0');
               if(pos >= 0)
                  cmdLine = cmdLine.substr(0, pos);
               // Keep program name only, removing the path
               pos = cmdLine.rear_find('/');
               if (pos >= 0)
                  cmdLine = cmdLine.substr(pos + 1);
               // compare against requested process name
               if (procName == cmdLine)
                  pid = atom;
            }
            fclose(cmdFile);
         }
      }
   }

   closedir(dp);

   return pid;

}




string module_path_from_pid(unsigned int iPid)
{

   int iSize = 1024 * 8;

   string path;
   char * pszBuffer = path.get_buffer(iSize);
   char * systemPath = nullptr;
   char * candidateDir = nullptr;

   string str;
   str = "/proc/" + as_string(iPid) + "/exe";

   /* the easiest case: we are in linux */
   ssize_t s = readlink(pszBuffer,path,iSize);

   if(s == -1)
   {
      return "";
   }

   path.set_at(s, '\0');

   path.release_buffer();


   return path;

}



::int_array module_path_get_pid(const ::file::path & path)
{

   ::int_array ia;

   ::file::path_array stra;

   ::dir::ls_dir(stra,"/proc/");

   for(auto & strPid : stra)
   {

      int iPid = atoi(strPid.title());

      if(iPid > 0)
      {

         string strPath =module_path_from_pid(iPid);

         if(strPath == pszPath)
         {

            ia.add(iPid);

         }

      }

   }

   return ia;

}

//
//atom_array app_get_pid(const ::scoped_string & scopedstr)
//{
//
//   atom_array ia;
//
//   ::file::path_array stra;
//
//   ::dir::ls_dir(stra,"/proc/");
//
//   string str(psz);
//
//   str = "app=" + str;
//
//   string strApp(psz);
//
//   strApp.replace("-","_");
//
//   strApp.replace("/","_");
//
//   for(auto & strPid : stra)
//   {
//
//      int iPid = atoi(strPid.title());
//
//      if(iPid > 0)
//      {
//
//         ::file::path path = module_path_from_pid(iPid);
//
//         if(path.title() == strApp)
//         {
//
//            ia.add(iPid);
//
//         }
//         else
//         {
//
//            string_array straCmdLine = cmdline_from_pid(iPid);
//
//            string strCmdLine;
//
//            strCmdLine = straCmdLine.implode(" ");
//
//            if(straCmdLine.find_first(str) > 0)
//            {
//
//               ia.add(iPid);
//
//            }
//
//         }
//
//      }
//
//   }
//
//   return ia;
//
//}



string_array cmdline_from_pid(unsigned int iPid)
{

   string_array stra;

   string str;

   str = "/proc/" + as_string(iPid) + "/cmdline";

   memory mem = file_as_memory(str);

   string strArg;

   char ch;

   for(int i = 0; i < mem.get_size(); i++)
   {

      ch = (char)mem.get_data()[i];

      if(ch == '\0')
      {

         stra.add(strArg);

         strArg.empty();

      }
      else
      {

         strArg += ch;

      }


   }

   if(strArg.has_character())
   {

      stra.add(strArg);

   }

   return stra;

   /* the easiest case: we are in linux */
   //    ssize_t s = readlink (str, path, iSize);

   //  if(s == -1)
   //{
   // return "";
   //}

   //path[s] = '\0';

   //return path;

}



//
