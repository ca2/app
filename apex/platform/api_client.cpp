// Created by camilo on 2021-11-17 01:29 PM <3ThomasBorregaardSørensen!! & Mummi!!
#include "framework.h"
#include "api.h"
#include "apex/filesystem/filesystem/dir_context.h"
///#include "acme/exception/exception.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"
#include "apex/platform/system.h"
#include "acme/primitive/primitive/memory.h"


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
            
            m_papi->initialize_api(m_pparticleContext, m_pathProfileFolder, m_strBrowserAccount);

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



//void api_client::_api_get(::string & str, const ::scoped_string & scopedstrUrl, ::property_set & set)
//{
//
//   int iTryCount = 3;
//
//   for (int iTry = 0; iTry < iTryCount; iTry++)
//   {
//
//      defer_api();
//
//      if (!m_papi)
//      {
//
//         throw ::exception(error_resource);
//
//      }
//
//      m_papi->_api_get(str, strUrl, set);
//
//      int iHttpStatusCode = set["http_status_code"];
//
//      ::string strStatus = set["http_status"];
//
//      if (iHttpStatusCode == 200 || iHttpStatusCode == 400)
//      {
//
//         break;
//
//      }
//
//      m_papi->clear_profile();
//
//   }
//
//}


::payload api_client::api_get(const ::scoped_string & scopedstrUrl, ::property_set & set)
{

   defer_api();

   if (!m_papi)
   {

      throw ::exception(error_resource);

   }

   return m_papi->api_get(scopedstrUrl, set);

}


::memory api_client::api_memory(const ::scoped_string & scopedstrUrl, ::property_set & set)
{

   defer_api();

   if (!m_papi)
   {

      throw ::exception(error_resource);

   }

   return m_papi->api_memory(scopedstrUrl, set);

}



