// From api_client_base.cpp by camilo on 2023-02-01 09:10 PM <3ThomasBorregaardSørensen!! & Mummi!!
#include "framework.h"
#include "api.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"
#include "apex/platform/system.h"


api_client_base::api_client_base()
{

}


api_client_base::~api_client_base()
{


}


//
//void api_client_base::initialize(::particle * pparticle)
//{
//
//   ::object::initialize(pparticle);
//
//}


::pointer < ::api > api_client_base::create_new_profile(::string & strProfile, const ::scoped_string & scopedstrImplementation, const ::scoped_string & scopedstrBrowserAccount)
{

   if (m_pathFolder.is_empty())
   {

      m_pathFolder = dir()->appdata() / "api" / scopedstrImplementation;

   }

   ::file::path pathProfile;

   int iProfile = 1;

   while (true)
   {

      strProfile.format("new_profile_%d", iProfile);

      pathProfile = m_pathFolder / strProfile;

      if (!acmedirectory()->is(pathProfile))
      {

         break;

      }


   }

   auto papi = api_client_base::create_profile_api(pathProfile, scopedstrImplementation, scopedstrBrowserAccount);

   strProfile = papi->get_name_for_profile();

   if (strProfile.is_empty())
   {

      throw ::exception(error_failed, "Failed to retrieve name for profile using api");

   }

   pathProfile = m_pathFolder / strProfile;

   papi->switch_profile_folder(m_pathFolder);

   return papi;

}


::pointer < ::api > api_client_base::create_profile_api(const ::file::path & pathProfile, const ::scoped_string & scopedstrImplementation, const ::scoped_string & scopedstrBrowserAccount)
{

   if (m_pathFolder.is_empty())
   {

      m_pathFolder = dir()->appdata() / "api" / scopedstrImplementation;

   }


   auto papi = create_api(scopedstrImplementation);
   //if (!m_papi || !m_papi->m_bAuthenticated)
   //{

   //   if (m_papi && m_papi->m_bAuthenticating)
   //   {

   //      m_papi->m_eventResponse.wait();

   //   }
   //   else
   //   {

         //create_api();

   papi->m_bAuthenticating = true;


   try
   {

      papi->initialize_api(this, pathProfile, scopedstrBrowserAccount);

   }
   catch (...)
   {

      papi.release();

      throw ::exception(error_failed);

   }

   try
   {

      //papi->api_login(m_strApiClientConfig, m_strBrowserProfile);
      papi->api_login();

   }
   catch (...)
   {

      papi.release();

      //return;

   }

   return papi;

}


//void api_client_base::create_api()
//{
//
//   return create_api(m_strImplementation);
//
//}


::pointer < ::api > api_client_base::create_api(const ::scoped_string & scopedstrImplementation)
{

   auto & pfactory = acmesystem()->factory("api", scopedstrImplementation);

   if (!pfactory)
   {

      throw ::exception(error_resource);

   }

   auto papi = pfactory->create < ::api >();

   if (!papi)
   {

      throw ::exception(error_resource);

   }

   papi->m_papiclient = this;

   papi->m_strImplementation = scopedstrImplementation;

   return papi;

}




//void api_client_base::api_get(::string & str, const string & strUrl, property_set & set)
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
//      m_papi->api_get(str, strUrl, set);
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
//
//}
//
//
//void api_client_base::api_get(::payload & payload, const string & strUrl, property_set & set)
//{
//
//   defer_api();
//
//   if (!m_papi)
//   {
//
//      throw ::exception(error_resource);
//
//   }
//
//   m_papi->api_get(payload, strUrl, set);
//
//}
//
//
//void api_client_base::api_download(string strGet, const ::file::path & path, property_set & set)
//{
//
//   defer_api();
//
//   if (!m_papi)
//   {
//
//      throw ::exception(error_resource);
//
//   }
//
//   m_papi->api_download(strGet, path, set);
//
//}
//
//
//
