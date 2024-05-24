//
//  session.cpp
//  acid
//
//  Created by camilo on 2022-12-01 11:30 BRT <3TBS_!!
//
#include "framework.h"
#include "session.h"
#include "acid/exception/interface_only.h"


namespace acid
{


   session::session()
   {

      m_pacesession = this;
      m_papexsession = nullptr;
      m_paquasession = nullptr;
      m_paurasession = nullptr;
      m_paxissession = nullptr;
      m_pbasesession = nullptr;
      m_pbredsession = nullptr;
      m_pcoresession = nullptr;


   }
      
   
   session::~session()
   {


   }


   ::user::user * session::user()
   {

      throw ::interface_only("imaging requires aura layer or upper layer");

      return nullptr;

   }


} // namespace apex



