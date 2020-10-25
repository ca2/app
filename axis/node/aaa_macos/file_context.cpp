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

   var file_context::length(const ::file::path & pszPath)
   {

      var varRet;


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


   ::estatus file_context::initialize(::layered * pobjectContext)
   {
      
      auto estatus = ::file_context::initialize(pobjectContext);
      
      if(!estatus)
      {
         
         return estatus;
         
      }

      estatus = __refer(m_pdirsystem, System.m_pdirsystem);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      estatus = __refer(m_pfilesystem, System.m_pfilesystem);
      
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
//      if(Application.has_property("user_folder_relative_path"))
//      {
//
//         strUserFolderShift = strRelative / Application.command_value("user_folder_relative_path").get_string();
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




   ::estatus file_context::update_module_path()
   {


//      m_pathModule = apple_app_module_path();
//
//      m_pathCa2Module = ca2_module_dup();

      return true;

   }


   file_result file_context::get_file(const var & varFile, const efileopen & eopenFlags)
   {

      return ::file_context::get_file(varFile, eopenFlags);

   }



} // namespace macos



