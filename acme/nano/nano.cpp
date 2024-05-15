//
//  nano.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/24.
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "nano.h"
#include "http/http.h"
#include "speech/speech.h"
#include "user/user.h"
#include "acme/platform/system.h"


namespace nano
{


   nano::nano()
   {
      
   }


   nano::~nano()
   {
      
   }


   ::nano::http::http*nano::http()
   {
      return system()->__factory(m_phttp);
   }
   ::nano::speech::speech*nano::speech()
   {
      return system()->__factory(m_pspeech);
   }
   ::nano::user::user*nano::user()
   {
      return system()->__factory(m_puser);
   }

}//namespace nano
