#include "framework.h"
#include <dirent.h>

i32 get_process_pid(const ::string & procNameParam)
{

   string procName(procNameParam);

   i32 pid = -1;

   // Open the /proc directory
   DIR *dp = opendir("/proc");
   if (dp != nullptr)
   {
      // Enumerate all entries in directory until process found
      struct dirent *dirp;
      while (pid < 0 && (dirp = readdir(dp)))
      {
         // Skip non-numeric entries
         i32 id = atoi(dirp->d_name);
         if (id > 0)
         {
            // Read contents of virtual /proc/{pid}/cmdline file
            string cmdPath = string("/proc/") + dirp->d_name + "/cmdline";
            FILE * cmdFile = fopen(cmdPath, "rb");
            string cmdLine;
            fgets(cmdLine.get_string_buffer(1024 * 256), 1024 * 256, cmdFile);
            cmdLine.release_string_buffer();
            if(cmdLine.has_char())
            {
               // Keep first cmdline item which contains the program path
               strsize pos = cmdLine.find('\0');
               if(pos >= 0)
                  cmdLine = cmdLine.substr(0, pos);
               // Keep program name only, removing the path
               pos = cmdLine.reverse_find('/');
               if (pos >= 0)
                  cmdLine = cmdLine.substr(pos + 1);
               // compare against requested process name
               if (procName == cmdLine)
                  pid = id;
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
   char * pszBuffer = path.get_string_buffer(iSize);
   char * systemPath = nullptr;
   char * candidateDir = nullptr;

   string str;
   str = "/proc/" + __str(iPid) + "/exe";

   /* the easiest case: we are in linux */
   ssize_t s = readlink(pszBuffer,path,iSize);

   if(s == -1)
   {
      return "";
   }

   path.set_at(s, '\0');

   path.release_string_buffer();


   return path;

}



int_array module_path_get_pid(const ::string & pszPath)
{

   int_array ia;

   ::file::patha stra;

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


//id_array app_get_pid(const ::string & psz)
//{
//
//   id_array ia;
//
//   ::file::patha stra;
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
//
//
//
//string_array cmdline_from_pid(unsigned int iPid)
//{
//
//   string_array stra;
//
//   string str;
//
//   str = "/proc/" + __str(iPid) + "/cmdline";
//
//   memory mem = file_as_memory(str);
//
//   string strArg;
//
//   char ch;
//
//   for(int i = 0; i < mem.get_size(); i++)
//   {
//
//      ch = (char)mem.get_data()[i];
//
//      if(ch == '\0')
//      {
//
//         stra.add(strArg);
//
//         strArg.Empty();
//
//      }
//      else
//      {
//
//         strArg += ch;
//
//      }
//
//
//   }
//
//   if(strArg.has_char())
//   {
//
//      stra.add(strArg);
//
//   }
//
//   return stra;
//
//   /* the easiest case: we are in linux */
//   //    ssize_t s = readlink (str, path, iSize);
//
//   //  if(s == -1)
//   //{
//   // return "";
//   //}
//
//   //path[s] = '\0';
//
//   //return path;
//
//}
//
//

