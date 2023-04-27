//
// Created by camilo on 2022-12-01 08:42 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "application_base.h"
#include "acme.h"


#ifdef WINDOWS


void defer_initialize_system_heap();


#endif


namespace acme
{


   application_base::application_base()
   {

      //if (!::acme::acme::g_p)
      {

#ifdef WINDOWS

         defer_initialize_system_heap();

#endif

//         ::acme::acme::g_p = &m_acme;

         m_acme.acme_initialize();

      }

   }


   application_base::~application_base()
   {

      //::acme::acme::g_p->acme_finalize();

      //::acme::acme::g_p->~acme();

   }


} // namespace acme



