#include "framework.h"


namespace aqua
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


   bool history::hist(const char * psz)
   {

      if(m_phistory != nullptr)
      {

         return m_phistory->hist(psz);

      }

      return false;

   }


} // namespace aqua


