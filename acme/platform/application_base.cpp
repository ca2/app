//
// Created by camilo on 2022-12-01 08:42 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "application_base.h"
#include "acme.h"


#ifdef WINDOWS


void defer_initialize_system_heap();


#endif


namespace acme
{


   extern ::acme::acme * g_p;


   application_base::application_base()
   {

      if (!::acme::g_p)
      {

#ifdef WINDOWS

         defer_initialize_system_heap();

#endif

         ::acme::g_p = memory_new ::acme::acme;

         m_pacme = ::acme::g_p;

      }

   }


   application_base::~application_base()
   {

      if (m_pacme == ::acme::g_p)
      {

         m_pacme = nullptr;

         ::acme::del(::acme::g_p);

      }

   }



} // namespace acme


