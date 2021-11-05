// Created on 2021-11-01 18:14 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"


namespace acme
{


   bool implementable::defer_implement(class ::system * psystem)
   {

      if (!m_pfnImplement)
      {

         return false;
         
      }

      m_pfnImplement(psystem);

      return true;

   }


} // namespace acme



