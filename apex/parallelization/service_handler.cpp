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
   //virtual void start_service();

   //virtual void stop_service();

service* service_handler::get_service()
{

   return m_pservice;

}
   //virtual void install_service();

   void service_handler::defer_service()
   {

      if (m_pservice)
      {

         return ::success;

      }

      __pointer(::application) papplication = get_application();

      auto pservice = papplication->create_service();

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

   
   //void service_handler::enable_service()
   //{

   //   throw ::interface_only_exception();

   //   return error_interface_only;

   //}


   //void service_handler::disable_service()
   //{

   //   throw ::interface_only_exception();

   //   return error_interface_only;

   //}



   void service_handler::start_service()
   {

      throw ::interface_only_exception();

      return error_interface_only;

   }


   void service_handler::stop_service()
   {

      throw ::interface_only_exception();

      return error_interface_only;

   }






