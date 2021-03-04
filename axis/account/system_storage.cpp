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
   
   
   system_storage::system_storage(department * paccount) :
      ::object(paccount),
      m_paccount(paccount)
   {
      
      
   }
   
   
   system_storage::~system_storage()
   {
      
      
   }
   
   
   ::file::path system_storage::path_prefix(string strToken)
   {
      
      if(strToken.is_empty())
      {
         
         ASSERT(false);
         
         strToken = "(empty)";
         
      }
      
      string strName = System->url().os_fsname(strToken);
      
      return m_paccount->system_storage_default_path_prefix() / strName;
      
   }
   
   
   ::e_status     system_storage::get(string strKey, string strToken, string & strValue)
   {
      
      ::file::path path;
      
      path = path_prefix(strToken);
      
      path /= System->crypto().md5(strToken + strKey);
      
      return System->crypto().file_get(path, strValue, strToken, get_context_application());
      
   }
   
   
   bool system_storage::set(string strKey, string strToken, string strValue)
   {
      
      ::file::path path;
      
      path = path_prefix(strToken);
      
      dir::mk(path);
      
      path /= System->crypto().md5(strToken + strKey);
      
      return System->crypto().file_set(path, strValue, strToken, get_context_application());
      
   }
   
   
} // namespace account



