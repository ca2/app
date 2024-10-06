//
//  nano.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/24.
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved.
//
// Added compress and shell on 2024-05-27 02:16 <3ThomasBorregaardSorensen!!
// Added idn by camilo on 2024-06-02 16:59 <3ThomasBorregaardSorensen!!
// Added account and dynamic library and shell on 2024-06-02 19:11 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "nano.h"
#include "acme/nano/account/account.h"
#include "acme/nano/archive/archive.h"
#include "acme/nano/compress/compress.h"
#include "acme/nano/dynamic_library/dynamic_library.h"
#include "acme/nano/graphics/graphics.h"
#include "acme/nano/http/http.h"
#include "acme/nano/idn/idn.h"
#include "acme/nano/shell/shell.h"
#include "acme/nano/speech/speech.h"
#include "acme/nano/user/user.h"
#include "acme/nano/windowing/windowing.h"
#include "acme/platform/system.h"
#include "acme/platform/system_factory.h"


namespace nano
{


   nano::nano()
   {
      
   }


   nano::~nano()
   {
      
   }

   ::nano::account::account*nano::account()
   {
      return system()->system_factory()->__factory(m_paccount);
   }

   ::nano::archive::archive*nano::archive()
   {
      return system()->system_factory()->__factory(m_parchive);
   }
   ::nano::compress::compress*nano::compress()
   {
      return system()->system_factory()->__factory(m_pcompress);
   }
   ::nano::dynamic_library::dynamic_library*nano::dynamic_library()
   {
      return system()->system_factory()->__factory(m_pdynamiclibrary);
   }
   ::nano::graphics::graphics*nano::graphics()
   {
      return system()->system_factory()->__factory(m_pgraphics);
   }
   ::nano::http::http*nano::http()
   {
      return system()->system_factory()->__factory(m_phttp);
   }
   ::nano::idn::idn*nano::idn()
   {
      return system()->system_factory()->__factory(m_pidn);
   }
   ::nano::shell::shell*nano::shell()
   {
      return system()->system_factory()->__factory(m_pshell);
   }
   ::nano::speech::speech*nano::speech()
   {
      return system()->system_factory()->__factory(m_pspeech);
   }
   ::nano::user::user*nano::user()
   {
      return system()->system_factory()->__factory(m_puser);
   }
   ::nano::windowing::windowing * nano::windowing()
   {
      return system()->system_factory()->__factory(m_pwindowing);
   }

}//namespace nano
