// Created by camilo on 2021-11-17 01:29 PM <3ThomasBorregaardS�rensen!! & Mummi!!
#include "framework.h"
#include "api.h"


api_client::api_client()
{


}


api_client::~api_client()
{


}


::e_status api_client::create_api(const ::string& strImplementation)
{

   if (!m_papi)
   {

      auto plibrary = m_psystem->do_containerized_factory_exchange("api", strImplementation);

      if (!plibrary)
      {

         return error_failed;

      }

      m_papi = plibrary->create < ::api >();

      if (!m_papi)
      {

         return false;

      }

      m_papi->m_papiclient = this;

   }

   return success;

}