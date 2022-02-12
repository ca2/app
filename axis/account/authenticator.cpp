//
//  account_credentials.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//
#include "framework.h"


namespace account
{


   authenticator::authenticator()
   {

   }


   authenticator::~authenticator()
   {

   }


   void authenticator::pre_authenticate(credentials * pcredentials)
   {

      throw ::exception(error_pre_authentication);
      
   }


   void authenticator::authenticate(credentials * pcredentials)
   {

      throw ::exception(error_authentication_none);

   }


} // namespace account



