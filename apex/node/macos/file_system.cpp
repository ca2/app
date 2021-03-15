#include "framework.h"
//#include "macos.h"
#include "apex/os/_.h"
#include "apex/os/_os.h"


#include <sys/stat.h>
#include <ctype.h>
#include <mach-o/dyld.h>

struct PROCESS_INFO_t
{
   string csProcess;
   u32 dwImageListIndex;
};


namespace macos
{


   file_system::file_system()
   {

   }


   file_system::~file_system()
   {

   }


   ::e_status file_system::initialize(::context_object * pcontextobject)
   {
      
      auto estatus = ::file_system::initialize(pcontextobject);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      string str = getenv("HOME");

      ::file::path strRelative = ::dir::install();

      string strUserFolderShift;

      if(::apex::get_system()->has_property("user_folder_relative_path"))
      {

         strUserFolderShift = strRelative / get_application()->payload("user_folder_relative_path").get_string();

      }
      else
      {

         strUserFolderShift = strRelative;

      }

      m_strUserFolder = str / "ca2" / strUserFolderShift;

      return true;

   }


   ::e_status file_system::update_module_path()
   {
      
      auto estatus = ::file_system::update_module_path();
      
      if(!estatus)
      {
         
         return estatus;
         
      }

      m_pathModule = apple_app_module_path();

      m_pathCa2Module = apple_app_module_path();

      return estatus;

   }


} // namespace macos



