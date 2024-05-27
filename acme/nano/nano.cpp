//
//  nano.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/24.
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "nano.h"
#include "acme/nano/archive/archive.h"
#include "acme/nano/http/http.h"
#include "acme/nano/speech/speech.h"
#include "acme/nano/user/user.h"
#include "acme/platform/system.h"


namespace nano
{


   nano::nano()
   {
      
   }


   nano::~nano()
   {
      
   }


   ::nano::archive::archive*nano::archive()
   {
      return system()->__factory(m_parchive);
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
