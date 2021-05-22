// Created on 2021-03-17 by camilo 13:12 BRT <3ThomasBS_!!
#include "framework.h"
#include "service_handler.h"
#include "service.h"



service_handler::service_handler()
{

}
service_handler:: ~service_handler()
{
}
   //virtual ::e_status start_service();

   //virtual ::e_status stop_service();

service* service_handler::get_service()
{

   return m_pservice;

}
   //virtual ::e_status install_service();

   ::e_status service_handler::defer_service()
   {

      if (m_pservice)
      {

         return ::success;

      }

      __pointer(::application) papplication = get_application();

      auto pservice = papplication->new_service();

      if (!pservice)
      {

         return error_failed;

      }

      auto estatus = pservice->initialize(papplication);

      if (!estatus)
      {

         return estatus;

      }

      m_pservice = pservice;

      if (!m_pservice)
      {

         return false;

      }

      //psystem->m_serviceptra.add(m_pservice);

      return estatus;

   }

   
   //::e_status service_handler::enable_service()
   //{

   //   __throw(error_interface_only);

   //   return error_interface_only;

   //}


   //::e_status service_handler::disable_service()
   //{

   //   __throw(error_interface_only);

   //   return error_interface_only;

   //}



   ::e_status service_handler::start_service()
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   ::e_status service_handler::stop_service()
   {

      __throw(error_interface_only);

      return error_interface_only;

   }






