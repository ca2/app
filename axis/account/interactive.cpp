//
//  account_interactive.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/12/18.
//
#include "framework.h"
#include "interactive.h"
#include "credentials.h"
#include "axis/platform/application.h"
#include "user.h"


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

            ::pointer<::axis::application>papp = get_app();

            papp->interactive_credentials(pcredentials);

         }

      }
      else
      {

         pcredentials->m_puser->m_estatusAuthentication = error_credentials_non_interactive;

      }

   }


} // namespace user



