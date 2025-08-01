//
//  account_storage_client.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/12/18.
//
#include "framework.h"
#include "storage_client.h"
#include "storage.h"


namespace account
{
   
   
   storage_client::storage_client()
   {

   }
   
   
   storage_client::~storage_client()
   {
      
   }
   
   
   void storage_client::initialize_account_storage_client(storage * pstorage)
   {

      //auto estatus = 
      
      ::particle::initialize(pstorage);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pstorage = pstorage;

      //return ::success;

   }


   bool storage_client::get(const ::scoped_string & scopedstrKey, string & strValue)
   {
      
      if(m_strToken.is_empty())
      {
         
         error() <<"::account::storage_client::get Token is Empty!";
         
         ASSERT(false);
         
         return false;
         
      }

      return m_pstorage->get(scopedstrKey, m_strToken, strValue);
      
   }
   
   
   void storage_client::set(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrValue)
   {
      
      if(m_strToken.is_empty())
      {
         
         error() <<"::account::storage_client::set Token is Empty!";
         
         //ASSERT(false);
         
         return;
         
      }
      
      m_pstorage->set(scopedstrKey, m_strToken, scopedstrValue);
      
   }

   
} // namespace account



