//
//  account_storage_client.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/12/18.
//
#pragma once



//#include "acme/prototype/prototype/matter.h"


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

      
      virtual bool get(const ::scoped_string & scopedstrKey, string & strValue);
      virtual void set(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrValue);

      
   };
   
   
} // namespace account



