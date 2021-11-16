// Created by camilo on 2021-11-05 16:12 PM <3ThomasBorregaardS�rensen!!
#include "framework.h"
#include "api.h"


api::api()
{

   m_bAuthenticated = false;

}


api::~api()
{


}


::e_status api::initialize_api(::object* pobject, const ::file::path & pathProfile)
{

   auto estatus = ::object::initialize(pobject);

   if (!estatus)
   {

      return estatus;

   }

   m_pathProfile = pathProfile;

   load_profile();

   return estatus;

}


::e_status api::load_profile()
{

   auto strNetworkPayload = m_pcontext->m_papexcontext->file().as_string(m_pathProfile);

   ::payload payload;

   payload.parse_network_payload(strNetworkPayload);

   m_strToken = payload["token"];

   if (m_strToken.has_char())
   {

      m_bAuthenticated = true;

   }

   return ::success;

}


::e_status api::save_profile()
{

   ::payload payload;

   payload["token"] = m_strToken;

   auto strNetworkPayload = payload.get_network_payload();

   m_pcontext->m_papexcontext->file().put_contents(m_pathProfile, strNetworkPayload);

   return ::success;

}



::e_status api::api_login(const ::string & strConfig, const ::string & strProfile)
{

   m_strConfig = strConfig;

   m_strProfile = strProfile;

   auto estatus = save_profile();

   m_bAuthenticated = true;

   return ::success;

}


::e_status api::api_get(string& strNetworkPayload, const string& strUrl, property_set& set)
{

   throw interface_only_exception();

   return error_interface_only;

}


::e_status api::api_get(::payload& payload, const string & strUrl, property_set& set)
{

   string strNetworkPayload;

   auto estatus = api_get(strNetworkPayload, strUrl, set);

   if(!estatus)
   {

      return estatus;

   }

   payload.parse_network_payload(strNetworkPayload);

   return estatus;

}


::e_status api::api_download(string strGet, const ::file::path& path, property_set& set)
{

   throw interface_only_exception();

   return ::error_interface_only;

}


string api::api_token(bool bForce)
{

   throw interface_only_exception();

   return "";

}


void api::on_login_authentication_failed()
{

   m_strToken.Empty();

   save_profile();

   api_login(m_strConfig, m_strProfile);

}
