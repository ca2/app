//
//  account_system_storage.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/12/18.
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
      
      virtual ::file::path path_prefix(string strToken);
      
      
      virtual bool get(string strKey, string strToken, string & strValue) override;
      virtual void set(string strKey, string strToken, string strValue) override;
      
      
   };
   

} // namespace account



