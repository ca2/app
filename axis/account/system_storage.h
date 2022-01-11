//
//  account_system_storage.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//
#pragma once


namespace account
{
   
   
   class CLASS_DECL_AXIS system_storage :
   virtual public storage
   {
   public:
      
      
      department *      m_paccount;
      
      
      system_storage();
      virtual ~system_storage();
      

      virtual void initialize_system_storage(department* pdepartment);
      
      virtual ::file::path path_prefix(string strToken);
      
      
      virtual void     get(string strKey, string strToken, string & strValue) override;
      virtual bool set(string strKey, string strToken, string strValue) override;
      
      
   };
   

} // namespace account



