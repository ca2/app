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

      if (!::acme::acme::g_p)
      {

#ifdef WINDOWS

         defer_initialize_system_heap();

#endif

         auto p = ::malloc(sizeof(::acme::acme));

         new (p) ::acme::acme();

         ::acme::acme::g_p = (::acme::acme *) p;

         ::acme::acme::g_p->acme_initialize();

         m_pacme = ::acme::acme::g_p;

      }

   }


   application_base::~application_base()
   {

      if (m_pacme == ::acme::acme::g_p)
      {

         m_pacme = nullptr;

         ::acme::acme::g_p->acme_finalize();

         ::acme::acme::g_p->~acme();

         ::acme::free(::acme::acme::g_p);

      }

   }


} // namespace acme



