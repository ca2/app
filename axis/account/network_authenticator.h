//
//  account_network_credentials.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//
#pragma once


#include "apex/networking/http/status.h"


namespace account
{


   class CLASS_DECL_AXIS network_authenticator :
      virtual public authenticator
   {
   public:




      network_authenticator();
      virtual ~network_authenticator();


      virtual ::e_status  pre_authenticate(credentials * pcredentials) override;

      virtual ::e_status  authenticate(credentials * pcredentials) override;




      virtual ::e_status  network_authentication(credentials * pcredentials);


      //virtual ::e_status  get_server(credentials * pcredentials);


      //virtual ::e_status  _get_server(credentials * pcredentials);
      virtual ::e_status  get_account_server(credentials * pcredentials);
      virtual ::e_status  _get_account_server(credentials * pcredentials);


   };


} // namespace account
