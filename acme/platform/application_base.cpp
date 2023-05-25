//
// Created by camilo on 2022-12-01 08:42 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "application_base.h"
#include "acme.h"


namespace acme
{


   application_base::application_base()
   {

      m_acme.acme_initialize();

   }


   application_base::~application_base()
   {

      //::acme::acme::g_pacme->acme_finalize();

      //::acme::acme::g_pacme->~acme();

   }


} // namespace acme



