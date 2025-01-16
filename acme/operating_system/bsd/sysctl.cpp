// Create by camilo on 2024-09-02 20:12 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include <sys/sysctl.h>



string get_current_directory_name();


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

   informationf("get_module_path: exe:%s", strName.c_str());

   if(strName.begins("/"))
   {

      return strName;

   }
   
   if(strName.is_empty())
   {
      
      strName = ::system()->m_args[0];
      
   }
  
   auto pathCurrentFolder = get_current_directory_name();
   
   auto path = pathCurrentFolder / strName;
   
   informationf("get_module_path (2): %s", path.c_str());
   
   if(!file_exists(path))
   {

      return {};

   }
   
   informationf("get_module_path (3): OK!!: %s", path.c_str());
   
   return path;

}
