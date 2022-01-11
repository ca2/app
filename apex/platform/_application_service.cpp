// Create by camilo on 2021-08-10 14:06 BRT <3ThomasBorregaardS�rensen!!
#include "framework.h"
#include "apex/parallelization/service.h"
#include "apex/parallelization/service_handler.h"


e_status application::enable_service()
{

   auto estatus = m_psystem->m_papexsystem->os_context()->enable_service();

   if (!estatus)
   {

      return estatus;

   }

   estatus = service_handler()->start_service();

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


e_status application::disable_service()
{

   auto estatus = service_handler()->stop_service();

   if (!estatus)
   {

      return estatus;

   }

   estatus = os_context()->disable_service();

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}



void application::on_service_request(::create * pcreate)
{

   if (!is_service())
   {

      return;

   }

   if (pcreate->m_pcommandline->m_varQuery.has_property("create_service"))
   {

      enable_service();

   }
   else if (pcreate->m_pcommandline->m_varQuery.has_property("start_service"))
   {

      service_handler()->defer_service();

      service_handler()->start_service();

   }
   else if (pcreate->m_pcommandline->m_varQuery.has_property("stop_service"))
   {

      service_handler()->stop_service();

   }
   else if (pcreate->m_pcommandline->m_varQuery.has_property("erase_service"))
   {

      disable_service();

   }
   else if (has_property("service"))
   {

      service_handler()->defer_service();

      service_handler()->start_service();

   }
   else if (has_property("run"))
   {

      __compose(m_pservicehanlder)
         ;

      service_handler()->defer_service();

      service_handler()->get_service()->run();

   }

}



