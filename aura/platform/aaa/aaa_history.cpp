#include "framework.h"


namespace aura
{


   history::history()
   {

      // m_phistory = nullptr;

   }


   //history::history(::particle * pparticle) :
   //   ::object(pparticle)
   //{

   //   m_phistory = nullptr;

   //}


   bool history::hist(const ::string & psz)
   {

      if(m_phistory != nullptr)
      {

         return m_phistory->hist(psz);

      }

      return false;

   }


} // namespace aura


