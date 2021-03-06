// Created by CamiloSTTBS 2020-12-25 14:01 BRT <3ThomasBS_, Mummi and bilbo!!
#include "framework.h"


namespace aura
{

//
//   __pointer(::extended::future < ::conversation >) system::message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox)
//   {
//
//      auto psession = Session;
//
//      auto puser = psession->m_puser;
//
//      auto pmessagebox = __create_new < ::user::message_box >();
//
//      auto pfuture = pmessagebox->::extended::asynchronous<::conversation>::future();
//
//      pmessagebox->show(pszMessage, pszTitle, emessagebox);
//
//      ///__throw(todo);
//
////      auto pwindowing = puser->m_pwindowing;
//
////      auto ret = pwindowing->message_box(pszMessage, pszTitle, emessagebox);
//
////      process(ret);
//
//      return pfuture;
//
//   }


   //::e_status system::message_box_timeout(const char * pszMessage, const char * pszTitle, const ::duration & durationTimeout, const ::e_message_box & emessagebox, const future & process)
   //{

   //   auto psession = Session;

   //   auto puser = psession->m_puser;

   //   auto pwindowing = puser->m_pwindowing;

   //   auto ret = pwindowing->message_box(pszMessage, pszTitle, emessagebox);

   //   process(ret);

   //   return ::success;


   //}


   ::e_status system::start()
   {

      auto estatus = create_os_node();

      if (!estatus)
      {

         return estatus;

      }

      if (m_pnode)
      {

         return m_pnode->start();

      }

      estatus = ::aqua::system::start();

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


} // namespace aura




