// Created by camilo on 2023-06-14 01:51 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "mouse.h"


namespace user
{


   ::user::mouse & mouse::operator = (const ::user::mouse & mouse)
   {

      if (this != &mouse)
      {

         ::particle::operator = (mouse);

         m_ebuttonstate          = mouse.m_ebuttonstate;
         m_point                 = mouse.m_point;
         m_pointDesired          = mouse.m_pointDesired;
         m_pcursor               = mouse.m_pcursor;
         m_puserinteractionHit   = mouse.m_puserinteractionHit;

      }

      return *this;

   }


} // namespace user



