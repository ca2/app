#include "framework.h"
#include "_ios.h"


#include <sys/stat.h>


namespace ios
{


   file_context::file_context()
   {

   }


   file_context::~file_context()
   {

   }


   ::estatus file_context::initialize(::matter * pobjectContext)
   {
      
      auto estatus = ::file_context::initialize(pobjectContext);
      
      if(!estatus)
      {
         
         return estatus;
         
      }
      
      m_pdirsystem = System.m_pdirsystem;
      
      m_pfilesystem = System.m_pfilesystem;

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

      m_pfilesystem->m_strUserFolder = str / "ca2" / strUserFolderShift;
      
      return true;

   }


   ::estatus file_context::update_module_path()
   {

      m_pfilesystem->m_pathModule = apple_app_module_path();

      m_pfilesystem->m_pathCa2Module = m_pdirsystem->m_pathModule;

      return ::success;

   }


   ::file_result file_context::get_file(const ::payload & varFile, const ::efileopen & eopen)
   {

      ::file_result pfileresult;

      pfileresult = ::file_context::get_file(varFile, eopen);

      if(!pfileresult)
      {

         return pfileresult;

      }

      return pfileresult;

   }


   payload file_context::length(const ::file::path & path, payload * pvarQuery)
   {

      payload varRet;

      struct stat stat;

      if(::stat(path, &stat)  == -1)
      {
         
         varRet.set_type(::e_type_null);
         
      }
      else
      {
         
         varRet = stat.st_size;
         
      }

      return varRet;

   }


} // namespace ios



