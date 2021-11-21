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

      auto & pfactory = m_psystem->factory("api", strImplementation);

      if (!pfactory)
      {

         return pfactory;

      }

      m_papi = pfactory->create < ::api >();

      if (!m_papi)
      {

         return false;

      }

      m_papi->m_papiclient = this;

   }

   return success;

}