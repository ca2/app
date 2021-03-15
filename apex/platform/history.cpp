#include "framework.h"


namespace apex
{


   history::history()
   {

      // m_phistory = nullptr;

   }


   //history::history(::context_object * pcontextobject) :
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


} // namespace apex


