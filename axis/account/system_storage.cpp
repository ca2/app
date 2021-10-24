//
//  account_system_storage.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//
#include "framework.h"
#include "system_storage.h"


namespace account
{
   
   
   system_storage::system_storage()
   {
      
      
   }
   
   
   system_storage::~system_storage()
   {
      
      
   }
   

   ::e_status system_storage::initialize_system_storage(department* pdepartment)
   {

      auto estatus = storage::initialize(pdepartment);

      if (!estatus)
      {

         return estatus;

      }

      m_paccount = pdepartment;

      return estatus;

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
   
   
   ::e_status     system_storage::get(string strKey, string strToken, string & strValue)
   {
      
      ::file::path path;
      
      path = path_prefix(strToken);

      auto psystem = get_system()->m_papexsystem;
      
      path /= psystem->crypto()->md5(strToken + strKey);
      
      return psystem->crypto()->file_get(path, strValue, strToken, get_application());
      
   }
   
   
   bool system_storage::set(string strKey, string strToken, string strValue)
   {
      
      ::file::path path;
      
      path = path_prefix(strToken);
      
               auto psystem = m_psystem->m_papexsystem;

         auto pacmedir = psystem->m_pacmedir;

      pacmedir->create(path);

      path /= psystem->crypto()->md5(strToken + strKey);
      
      return psystem->crypto()->file_set(path, strValue, strToken, get_application());
      
   }
   
   
} // namespace account



