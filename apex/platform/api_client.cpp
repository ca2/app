// Created by camilo on 2021-11-17 01:29 PM <3ThomasBorregaardS�rensen!! & Mummi!!
#include "framework.h"
#include "api.h"


api_client::api_client()
{


}


api_client::~api_client()
{


}


::e_status api_client::defer_api()
{

   throw interface_only_exception();

   return error_interface_only;

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


::e_status api_client::api_get(::payload& payload, const string& strUrl, property_set& set)
{

   auto estatus = defer_api();

   if (!estatus || !m_papi)
   {

      return estatus;

   }

   estatus = m_papi->api_get(payload, strUrl, set);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}