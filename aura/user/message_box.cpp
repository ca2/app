//
// Created by camilo on 29/01/2021.  02:05 BRT <3ThomasBS_!!
//
#include "framework.h"
#include "message_box.h"


namespace user
{


   message_box::message_box(const string &strText, const string &strTitle, const ::e_message_box &emessagebox) :
      m_strText(strText),
      m_strTitle(strTitle),
      m_emessagebox(emessagebox)
   {

   }


   message_box::~message_box()
   {

   }


   ::payload message_box::realize()
   {

      auto pwindowing = System.windowing();

      int iResult = pwindowing->message_box(m_strText, m_strTitle, m_emessagebox);

      return iResult;

   }


} // namespace user


#ifdef _UWP


::e_status os_message_box(const char * pszText, const char * pszTitle, const ::e_message_box & emessagebox, const ::promise::process & process)
{

   return _os_message_box(pszText, pszTitle, emessagebox, process);

}


#else


//::e_status os_message_box(const char * pszText, const char * pszTitle, const ::e_message_box & emessagebox, const ::promise::process & process)
//{
//
//   auto posmessagebox = __new(::acme::os_message_box(pszText, pszTitle, emessagebox));
//
//   return __realize(posmessagebox, process);
//
//}
//

#endif



CLASS_DECL_AURA ::e_status os_message_box(const char * pszMessage, const char * pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const promise::process & process = ::promise::process())
{

   string strMessage(pszMessage);

   string strTitle(pszTitle);

   System.fork([strMessage, strTitle, emessagebox, process]()
               {

                  auto pwindowing = System.windowing();

                  auto result = pwindowing->message_box(strMessage, strTitle, emessagebox);

                  process(result);

               });

   return ::success;

}