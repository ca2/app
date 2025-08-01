//
//  account_system_storage.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/12/18.
//
#include "framework.h"
#include "system_storage.h"
#include "department.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/prototype/prototype/url.h"
#include "acme/platform/system.h"
#include "acme/crypto/crypto.h"
#include "apex/platform/application.h"
#include "apex/platform/system.h"


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

   
   ::file::path system_storage::path_prefix(const ::scoped_string & scopedstrToken)
   {

      ::string strToken(scopedstrToken);
      
      if(strToken.is_empty())
      {
         
         ASSERT(false);
         
         strToken = "(empty)";
         
      }

      // string strName = purl->os_fsname(strToken);
      
      return m_paccount->system_storage_default_path_prefix() / strToken;
      
   }
   
   
   bool system_storage::get(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrToken, string & strValue)
   {
      
      ::file::path path;

      ::string strToken(scopedstrToken);
      
      path = path_prefix(strToken);

      auto psystem = system();
      
      path /= psystem->crypto()->md5(::string(strToken + scopedstrKey));

      try
      {

         psystem->crypto()->file_get(path, strValue, strToken, get_app());

      }
      catch (...)
      {

         return false;

      }

      return true;
      
   }
   
   
   void system_storage::set(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrToken, const ::scoped_string & scopedstrValue)
   {
      
      ::file::path path;

      ::string strToken(scopedstrToken);
      
      path = path_prefix(strToken);
      
      auto psystem = system();

      auto pdirectorysystem = psystem->m_pdirectorysystem;

      pdirectorysystem->create(path);

      path /= psystem->crypto()->md5(::string(strToken + scopedstrKey));
      
      psystem->crypto()->file_set(path, scopedstrValue, strToken, get_app());
      
   }
   
   
} // namespace account



