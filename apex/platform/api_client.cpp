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

   if (!m_papi)
   {

      auto estatus = create_api();

      if (!estatus)
      {

         return estatus;

      }

      ::file::path pathProfile;

      pathProfile = m_pcontext->m_papexcontext->dir().appdata() / "api" / m_strImplementation / (m_strProfileStore + ".network_payload");

      estatus = m_papi->initialize_api(this, pathProfile);

      if (!estatus)
      {

         m_papi.release();

         return false;

      }

      estatus = m_papi->api_login(m_strApiClientConfig, m_strBrowserProfile);

      if (!estatus && estatus != success_scheduled)
      {

         m_papi.release();

         return false;

      }

   }

   return true;

}


::e_status api_client::create_api()
{

   return create_api(m_strImplementation);

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


::e_status api_client::api_get(::string & str, const string& strUrl, property_set& set)
{

   auto estatus = defer_api();

   if (!estatus || !m_papi)
   {

      return estatus;

   }

   estatus = m_papi->api_get(str, strUrl, set);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

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


::e_status api_client::api_download(string strGet, const ::file::path& path, property_set& set)
{

   auto estatus = defer_api();

   if (!estatus || !m_papi)
   {

      return estatus;

   }

   estatus = m_papi->api_download(strGet, path, set);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}



