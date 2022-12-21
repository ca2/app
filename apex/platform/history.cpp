#include "framework.h"
#include "history.h"


namespace apex
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


   bool history::hist(const ::scoped_string & scopedstr)
   {

      if(m_phistory != nullptr)
      {

         return m_phistory->hist(psz);

      }

      return false;

   }


} // namespace apex


