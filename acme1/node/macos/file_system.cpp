#include "framework.h"
//#include "macos.h"
#include "acme/os/_.h"
#include "acme/os/_os.h"


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


   ::estatus file_system::initialize(::generic * pobjectContext)
   {
      
      auto estatus = ::file_system::initialize(pobjectContext);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      string str = getenv("HOME");

      ::file::path strRelative = ::dir::install();

      string strUserFolderShift;

      if(System.has_property("user_folder_relative_path"))
      {

         strUserFolderShift = strRelative / Application.value("user_folder_relative_path").get_string();

      }
      else
      {

         strUserFolderShift = strRelative;

      }

      m_strUserFolder = str / "ca2" / strUserFolderShift;

      return true;

   }


   ::estatus file_system::update_module_path()
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



