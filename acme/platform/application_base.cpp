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


   extern ::pointer < ::acme::acme > g_p;


   application_base::application_base()
   {

      if (!::acme::g_p)
      {

#ifdef WINDOWS

         defer_initialize_system_heap();

#endif

         __raw_construct_new(::acme::g_p);

      }

   }


   application_base::~application_base()
   {

      ::acme::g_p.global_release();

   }



} // namespace acme


