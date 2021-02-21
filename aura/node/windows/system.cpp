// Created by CamiloSTTBS 2020-12-25 14:01 BRT <3ThomasBS_, Mummi and bilbo!!
#include "framework.h"


namespace aura
{



   ::e_status system::message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, const promise::process & process)
   {

      auto psession = Session;

      auto puser = psession->m_puser;

      auto pwindowing = puser->m_pwindowing;

      auto ret = pwindowing->message_box(pszMessage, pszTitle, emessagebox);

      process(ret);

      return ::success;

   }


   ::e_status system::message_box_timeout(const char * pszMessage, const char * pszTitle, const ::duration & durationTimeout, const ::e_message_box & emessagebox, const promise::process & process)
   {

      auto psession = Session;

      auto puser = psession->m_puser;

      auto pwindowing = puser->m_pwindowing;

      auto ret = pwindowing->message_box(pszMessage, pszTitle, emessagebox);

      process(ret);

      return ::success;


   }


   ::e_status system::start()
   {

      if (m_pnode)
      {

         return m_pnode->start();

      }

      auto estatus = ::aqua::system::start();

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


} // namespace aura




