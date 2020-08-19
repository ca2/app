//
//  account_network_credentials.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//
#pragma once


#include "aura/net/http/status.h"


namespace account
{


   class CLASS_DECL_AURA network_authenticator :
      virtual public authenticator
   {
   public:




      network_authenticator(::object * pobject);
      virtual ~network_authenticator();


      virtual ::estatus  pre_authenticate(credentials * pcredentials) override;

      virtual ::estatus  authenticate(credentials * pcredentials) override;




      virtual ::estatus  network_authentication(credentials * pcredentials);


      //virtual ::estatus  get_server(credentials * pcredentials);


      //virtual ::estatus  _get_server(credentials * pcredentials);
      virtual ::estatus  get_account_server(credentials * pcredentials);
      virtual ::estatus  _get_account_server(credentials * pcredentials);


   };


} // namespace account
