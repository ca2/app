//
//  account_storage_client.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//
#include "framework.h"


namespace account
{
   
   
   storage_client::storage_client()
   {

   }
   
   
   storage_client::~storage_client()
   {
      
   }
   
   
   ::e_status storage_client::initialize_account_storage_client(storage * pstorage)
   {

      auto estatus = ::object::initialize(pstorage);

      if (!estatus)
      {

         return estatus;

      }

      m_pstorage = pstorage;

      return ::success;

   }


   ::e_status     storage_client::get(string strKey, string & strValue)
   {
      
      if(m_strToken.is_empty())
      {
         
         TRACE(trace_category_general, e_trace_level_error, "::account::storage_client::get Token is Empty!");
         
         ASSERT(false);
         
         return error_failed;
         
      }

      return m_pstorage->get(strKey, m_strToken, strValue);
      
   }
   
   
   bool storage_client::set(string strKey, string strValue)
   {
      
      if(m_strToken.is_empty())
      {
         
         
         TRACE(trace_category_general, e_trace_level_error, "::account::storage_client::set Token is Empty!");
         
         //ASSERT(false);
         
         return false;
         
      }
      
      return m_pstorage->set(strKey, m_strToken, strValue);
      
   }

   
} // namespace account



