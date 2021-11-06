//
//  account_storage.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//
#pragma once


namespace account
{
   
   
   class CLASS_DECL_AXIS storage :
      virtual public ::object
   {
   public:
      
      
      virtual ::e_status     get(string strKey, string strToken, string & strValue) = 0;
      
      virtual bool set(string strKey, string strToken, string strValue) = 0;
      
      
   };

   
} // namespace account



