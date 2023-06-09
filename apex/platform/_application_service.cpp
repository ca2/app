// Create by camilo on 2021-08-10 14:06 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "os_context.h"
#include "acme/handler/request.h"
#include "apex/parallelization/service.h"
#include "apex/parallelization/service_handler.h"
#include "apex/platform/application.h"
#include "apex/platform/system.h"


namespace apex
{


   void application::enable_service()
   {

      //auto estatus = acmesystem()->m_papexsystem->os_context()->enable_service();

      acmesystem()->m_papexsystem->os_context()->enable_service();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = service_handler()->start_service();

      service_handler()->start_service();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //e_status application::disable_service()
   void application::disable_service()
   {

      //auto estatus = 

      service_handler()->stop_service();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 

      os_context()->disable_service();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void application::on_service_request(::request * prequest)
   {

      if (!is_service())
      {

         return;

      }

      if (prequest->has_property("create_service"))
      {

         enable_service();

      }
      else if (prequest->has_property("start_service"))
      {

         service_handler()->defer_service();

         service_handler()->start_service();

      }
      else if (prequest->has_property("stop_service"))
      {

         service_handler()->stop_service();

      }
      else if (prequest->has_property("erase_service"))
      {

         disable_service();

      }
      else if (prequest->has_property("service"))
      {

         service_handler()->defer_service();

         service_handler()->start_service();

      }
      //else if (has_property("run"))
      else 
      {

         __construct(m_pservicehandler);

         service_handler()->defer_service();

         service_handler()->get_service()->run();

      }

   }


} // namespace apex



