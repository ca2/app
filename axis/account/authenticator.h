//
//  account_credentials.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/12/18.
//
#pragma once


//#include "acme/primitive/primitive/matter.h"


namespace account
{

   
   class CLASS_DECL_AXIS authenticator :
      virtual public ::matter
   {
   public:
      
      
      authenticator();
      ~authenticator() override;
      
      
      virtual void pre_authenticate(credentials * pcredentials);
      
      virtual void authenticate(credentials * pcredentials);
      

   };


} // namespace account



