//
//  account_network_credentials.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//
#pragma once


#include "apex/networking/http/status.h"
#include "authenticator.h"


namespace account
{


   class CLASS_DECL_AXIS network_authenticator :
      virtual public authenticator
   {
   public:


      network_authenticator();
      ~network_authenticator() override;


      void pre_authenticate(credentials * pcredentials) override;

      void authenticate(credentials * pcredentials) override;

      virtual void network_authentication(credentials * pcredentials);


      virtual void get_account_server(credentials * pcredentials);
      virtual void _get_account_server(credentials * pcredentials);


   };


} // namespace account
