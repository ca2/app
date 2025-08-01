//
//  account_system_storage.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/12/18.
//
#pragma once


#include "storage.h"


namespace account
{
   
   
   class CLASS_DECL_AXIS system_storage :
   virtual public storage
   {
   public:
      
      
      department *      m_paccount;
      
      
      system_storage();
      ~system_storage() override;
      

      virtual void initialize_system_storage(department* pdepartment);
      
      virtual ::file::path path_prefix(const ::scoped_string & scopedstrToken);
      
      
      virtual bool get(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrToken, string & strValue) override;
      virtual void set(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrToken, const ::scoped_string & scopedstrValue) override;
      
      
   };
   

} // namespace account



