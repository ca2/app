//
//  account_system_storage.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//
#include "framework.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "system_storage.h"


namespace account
{
   
   
   system_storage::system_storage()
   {
      
      
   }
   
   
   system_storage::~system_storage()
   {
      
      
   }
   

   void system_storage::initialize_system_storage(department* pdepartment)
   {

      //auto estatus = 
      
      storage::initialize(pdepartment);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_paccount = pdepartment;

      //return estatus;

   }

   
   ::file::path system_storage::path_prefix(string strToken)
   {
      
      if(strToken.is_empty())
      {
         
         ASSERT(false);
         
         strToken = "(empty)";
         
      }

      auto psystem = m_psystem;

      auto purl = psystem->url();

      string strName = purl->os_fsname(strToken);
      
      return m_paccount->system_storage_default_path_prefix() / strName;
      
   }
   
   
   bool system_storage::get(string strKey, string strToken, string & strValue)
   {
      
      ::file::path path;
      
      path = path_prefix(strToken);

      auto psystem = get_system()->m_papexsystem;
      
      path /= psystem->crypto()->md5(strToken + strKey);

      try
      {

         psystem->crypto()->file_get(path, strValue, strToken, get_app()->m_papplication);

      }
      catch (...)
      {

         return false;

      }

      return true;
      
   }
   
   
   void system_storage::set(string strKey, string strToken, string strValue)
   {
      
      ::file::path path;
      
      path = path_prefix(strToken);
      
      auto psystem = m_psystem->m_papexsystem;

      auto pacmedirectory = psystem->m_pacmedirectory;

      pacmedirectory->create(path);

      path /= psystem->crypto()->md5(strToken + strKey);
      
      psystem->crypto()->file_set(path, strValue, strToken, get_app()->m_papplication);
      
   }
   
   
} // namespace account



