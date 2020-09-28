#include "framework.h"


namespace acme
{


   history::history()
   {

      // m_phistory = nullptr;

   }


   //history::history(::elemental * pobject) :
   //   ::elemental(pobject)
   //{

   //   m_phistory = nullptr;

   //}


   bool history::hist(const char * psz)
   {

      if(m_phistory != nullptr)
      {

         return m_phistory->hist(psz);

      }

      return false;

   }


} // namespace acme


