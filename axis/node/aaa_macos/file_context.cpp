//
//  file_context.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 28/02/20.
//

#include "framework.h"
//#include "macos.h"
#include "aura/os/_.h"
#include "aura/os/_os.h"


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


   file_context::file_context()
   {

   }


   file_context::~file_context()
   {

   }

   ::payload file_context::length(const ::file::path & pszPath)
   {

      ::payload varRet;


      struct stat stat;

      if(::stat(pszPath, &stat)  == -1)
      {
         varRet.set_type(::e_type_null);
      }
      else
      {
         varRet = stat.st_size;
      }

      return varRet;

   }


   ::e_status file_context::initialize(::context_object * pcontextobject)
   {
      
      auto estatus = ::file_context::initialize(pcontextobject);
      
      if(!estatus)
      {
         
         return estatus;
         
      }

      estatus = __refer(m_pdirsystem, psystem->m_pdirsystem);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      estatus = __refer(m_pfilesystem, psystem->m_pfilesystem);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      
//      string str = getenv("HOME");
//
//      ::file::path strRelative = ::dir::install();
//
//      string strUserFolderShift;
//
//      if(papplication->has_property("user_folder_relative_path"))
//      {
//
//         strUserFolderShift = strRelative / papplication->command_value("user_folder_relative_path").get_string();
//
//      }
//      else
//      {
//
//         strUserFolderShift = strRelative;
//
//      }
//
//      m_strUserFolder = str / "ca2" / strUserFolderShift;

      return estatus;

   }




   ::e_status file_context::update_module_path()
   {


//      m_pathModule = apple_app_module_path();
//
//      m_pathCa2Module = ca2_module_dup();

      return true;

   }


   file_result file_context::get_file(const ::payload & varFile, const ::file::e_open & eopenFlags)
   {

      return ::file_context::get_file(varFile, eopenFlags);

   }



} // namespace macos



