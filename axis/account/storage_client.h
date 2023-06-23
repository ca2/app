//
//  account_storage_client.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/12/18.
//
#pragma once


// #include "acme/primitive/string/string.h"
//#include "acme/primitive/primitive/matter.h"


namespace account
{
   
   
   class CLASS_DECL_AXIS storage_client :
      virtual public ::matter
   {
   public:
      
      
      storage *         m_pstorage;
      string            m_strToken;
      
      
      storage_client();
      ~storage_client() override;
      
      
      virtual void initialize_account_storage_client(storage * pstorage);

      
      virtual bool get(string strKey, string & strValue);
      virtual void set(string strKey, string strValue);

      
   };
   
   
} // namespace account



