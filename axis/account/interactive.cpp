//
//  account_interactive.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//
#include "framework.h"


namespace account
{


   void interactive::interactive_credentials(credentials * pcredentials)
   {

      if (pcredentials->m_bInteractive)
      {

         if (pcredentials->m_pinteractive != nullptr)
         {

            pcredentials->m_pinteractive->interactive_credentials(pcredentials);

         }
         else
         {

            __pointer(::axis::application) papplication = get_application();

            papplication->interactive_credentials(pcredentials);

         }

      }
      else
      {

         pcredentials->m_puser->m_estatusAuthentication = error_credentials_non_interactive;

      }

   }


} // namespace user



