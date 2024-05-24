// Created on 2021-11-01 18:14 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "implementable.h"


namespace acid
{


   bool implementable::defer_implement(::acid::context * pcontext)
   {

      if (!m_pfnImplement)
      {

         return false;
         
      }

      m_pfnImplement(pcontext);

      return true;

   }


} // namespace acid



