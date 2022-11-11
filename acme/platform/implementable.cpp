// Created on 2021-11-01 18:14 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "implementable.h"


namespace acme
{


   bool implementable::defer_implement(::acme::context * pcontext)
   {

      if (!m_pfnImplement)
      {

         return false;
         
      }

      m_pfnImplement(pcontext);

      return true;

   }


} // namespace acme



