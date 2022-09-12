//
//  account_storage_client.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
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
      
      ::object::initialize(pstorage);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pstorage = pstorage;

      //return ::success;

   }


   bool storage_client::get(string strKey, string & strValue)
   {
      
      if(m_strToken.is_empty())
      {
         
         ERROR("::account::storage_client::get Token is Empty!");
         
         ASSERT(false);
         
         return false;
         
      }

      return m_pstorage->get(strKey, m_strToken, strValue);
      
   }
   
   
   void storage_client::set(string strKey, string strValue)
   {
      
      if(m_strToken.is_empty())
      {
         
         ERROR("::account::storage_client::set Token is Empty!");
         
         //ASSERT(false);
         
         return;
         
      }
      
      m_pstorage->set(strKey, m_strToken, strValue);
      
   }

   
} // namespace account



