// Created by camilo on 2021-11-17 01:29 PM <3ThomasBorregaardSørensen!! & Mummi!!
#include "framework.h"
#include "api.h"
#include "apex/filesystem/filesystem/dir_context.h"
////#include "acme/exception/exception.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"
#include "apex/platform/system.h"


api_client::api_client()
{


}


api_client::~api_client()
{


}



void api_client::initialize_api_client(const ::scoped_string & scopedstrImplementation, const ::scoped_string & scopedstrBrowserAccount, const ::file::path & pathProfileFolder)
{

   m_strImplementation = scopedstrImplementation;
   m_strBrowserAccount = scopedstrBrowserAccount;
   m_pathProfileFolder = pathProfileFolder;

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

         if(!m_papi)
         {

            m_papi = create_api(m_strImplementation);

         }
         
         m_papi->m_bAuthenticating = true;

         //::file::path pathProfile;

         //pathProfile = dir()->appdata() / "api" / scopedstrImplementation / (m_strProfileStore + ".network_payload");

         if (m_pathProfileFolder.is_empty())
         {

            auto pathAppData = dir()->appdata();

            m_pathProfileFolder = pathAppData / "api" / m_strImplementation;

         }

         try
         {
            
            m_papi->initialize_api(this, m_pathProfileFolder, m_strBrowserAccount);

         }
         catch (...)
         {

            m_papi.release();

            throw ::exception(error_failed);

         }


         if (!m_papi->m_bAuthenticated)
         {

            try
            {

               //m_papi->api_login(m_strApiClientConfig, m_strBrowserProfile);

               m_papi->api_login();

            }
            catch (...)
            {

               m_papi.release();

               return;

            }

         }
         
      }

   }

}


//::pointer < ::api > api_client::create_api()
//{
//
//   return create_api(m_strImplementation);
//
//}



void api_client::api_get(::string & str, const string& strUrl, property_set& set)
{

   int iTryCount = 3;

   for (int iTry = 0; iTry < iTryCount; iTry++)
   {

      defer_api();

      if (!m_papi)
      {

         throw ::exception(error_resource);

      }

      m_papi->_api_get(str, strUrl, set);

      int iHttpStatusCode = set["http_status_code"];

      ::string strStatus = set["http_status"];

      if (iHttpStatusCode == 200 || iHttpStatusCode == 400)
      {

         break;

      }

      m_papi->clear_profile();

   }


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



