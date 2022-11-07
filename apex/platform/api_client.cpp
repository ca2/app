// Created by camilo on 2021-11-17 01:29 PM <3ThomasBorregaardSørensen!! & Mummi!!
#include "framework.h"
#include "api.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"
#include "apex/platform/system.h"


api_client::api_client()
{


}


api_client::~api_client()
{


}


void api_client::defer_api()
{

   if (!m_papi || !m_papi->m_bAuthenticated)
   {
      
      if(m_papi && m_papi->m_bAuthenticating)
      {
      
         m_papi->m_eventResponse.wait();
      
      }
      else
      {

         create_api();
         
         m_papi->m_bAuthenticating = true;

         ::file::path pathProfile;

         pathProfile = dir()->appdata() / "api" / m_strImplementation / (m_strProfileStore + ".network_payload");

         try
         {
            
            m_papi->initialize_api(this, pathProfile);

         }
         catch (...)
         {

            m_papi.release();

            throw ::exception(error_failed);

         }

         try
         {

            m_papi->api_login(m_strApiClientConfig, m_strBrowserProfile);

         }
         catch (...)
         {

            m_papi.release();

            return;

         }
         
      }

   }

}


void api_client::create_api()
{

   return create_api(m_strImplementation);

}


void api_client::create_api(const ::string& strImplementation)
{

   if (!m_papi)
   {

      auto & pfactory = acmesystem()->factory("api", strImplementation);

      if (!pfactory)
      {

         throw ::exception(error_resource);

      }

      m_papi = pfactory->create < ::api >();

      if (!m_papi)
      {

         throw ::exception(error_resource);

      }

      m_papi->m_papiclient = this;

   }

   //return success;

}


void api_client::api_get(::string & str, const string& strUrl, property_set& set)
{

   defer_api();

   if (!m_papi)
   {

      throw ::exception(error_resource);

   }

   m_papi->api_get(str, strUrl, set);

}


void api_client::api_get(::payload& payload, const string& strUrl, property_set& set)
{

   defer_api();

   if (!m_papi)
   {

      throw ::exception(error_resource);

   }

   m_papi->api_get(payload, strUrl, set);

}


void api_client::api_download(string strGet, const ::file::path& path, property_set& set)
{

   defer_api();

   if (!m_papi)
   {

      throw ::exception(error_resource);

   }

   m_papi->api_download(strGet, path, set);

}



