// Create by camilo on 2024-09-02 20:12 <3ThomasBorregaardSorensen!!
#include "framework.h"

#if !defined(OPENBSD)
#if defined(OPENBSD)
#include <sys/types.h>
#endif
#include <sys/sysctl.h>
#endif

::file::path deduct_module_path_from_current_directory(const_char_pointer  pszOptionalExecutableRelativePath = nullptr);


//https://stackoverflow.com/questions/1528298/get-path-of-executable
::file::path get_module_path()
{
	
   ::string strName;
	
#if !defined(OPENBSD)

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

#endif

   auto path = deduct_module_path_from_current_directory(strName);
   
   return path;

}

