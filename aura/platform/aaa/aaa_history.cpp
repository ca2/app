#include "framework.h"


namespace aura
{


   history::history()
   {

      // m_phistory = nullptr;

   }


   //history::history(::object * pobject) :
   //   ::object(pobject)
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


