// Create by camilo on 2024-09-02 20:12 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include <sys/sysctl.h>


//https://stackoverflow.com/questions/1528298/get-path-of-executable
::file::path get_module_path()
{

   int mib[4]{0};
   
   size_t size;
  
   mib[0] = CTL_KERN;
   
   mib[1] = KERN_PROC;
   
   mib[2] = KERN_PROC_PATHNAME;
   
   mib[3] = -1;
   
   int result = sysctl(mib, 4, nullptr, &size, nullptr, 0);
   
   if (-1 == result)
   {
   
      return {};
   
   }
  
   ::string strName;

   auto p = strName.get_range_buffer(size);
   
   result = sysctl(mib, 4, p, &size, nullptr, 0);

   strName.release_buffer(size);

   if (-1 == result)
   {

      return {};
   
   }
  
   auto pathCurrentFolder = get_current_directory_name();
   
   auto path = pathCurrentFolder / strName;
   
   if(!file_exists(path))
   {

      return {};

   }
   
   return path;

}