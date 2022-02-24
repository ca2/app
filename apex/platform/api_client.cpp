// Created by camilo on 2021-11-17 01:29 PM <3ThomasBorregaardS�rensen!! & Mummi!!
#include "framework.h"
#include "api.h"


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

      //auto estatus = 
      
      create_api();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      ::file::path pathProfile;

      pathProfile = m_pcontext->m_papexcontext->dir().appdata() / "api" / m_strImplementation / (m_strProfileStore + ".network_payload");

      //estatus = 

      try
      {
         m_papi->initialize_api(this, pathProfile);

      }
      catch (...)
      {

         m_papi.release();

         throw ::exception(error_failed);

      }

      //if (!estatus)
      //{

      //   m_papi.release();

      //   return false;

      //}

      //estatus = m_papi->api_login(m_strApiClientConfig, m_strBrowserProfile);

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

   //return true;

}


void api_client::create_api()
{

   return create_api(m_strImplementation);

}


void api_client::create_api(const ::string& strImplementation)
{

   if (!m_papi)
   {

      auto & pfactory = m_psystem->factory("api", strImplementation);

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

   //auto estatus = 
      defer_api();

   if (!m_papi)
   {

      throw ::exception(error_resource);

   }

   //estatus = 
   
   m_papi->api_get(str, strUrl, set);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void api_client::api_get(::payload& payload, const string& strUrl, property_set& set)
{

   //auto estatus =
   defer_api();

   if (!m_papi)
   {

      throw ::exception(error_resource);

   }

   m_papi->api_get(payload, strUrl, set);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void api_client::api_download(string strGet, const ::file::path& path, property_set& set)
{

   //auto estatus =
   
   defer_api();

   if (!m_papi)
   {

      throw ::exception(error_resource);

   }

   //estatus = 
   m_papi->api_download(strGet, path, set);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}



