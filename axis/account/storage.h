//
//  account_storage.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/12/18.
//
#pragma once


//#include "acme/prototype/prototype/matter.h"


namespace account
{
   
   
   class CLASS_DECL_AXIS storage :
      virtual public ::matter
   {
   public:
      
      
      virtual bool get(string strKey, string strToken, string & strValue) = 0;
      
      virtual void set(string strKey, string strToken, string strValue) = 0;
      
      
   };

   
} // namespace account



