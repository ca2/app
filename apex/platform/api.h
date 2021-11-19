// Created by camilo on 2021-11-05 16:10 PM <3ThomasBorregaardS�rensen!!
#pragma once


class api_client;


class CLASS_DECL_APEX api :
   virtual public ::object
{
protected:

   
   using ::object::initialize;


public:


   bool                             m_bAuthenticated;
   string                           m_strConfig;
   string                           m_strProfile;
   string                           m_strToken;
   string                           m_strState;
   ::file::path                     m_pathProfile;
   ::payload                        m_payloadProfile;
   bool                             m_bWaitingResponseFromUser;
   __pointer(::api_client)    m_papiclient;
   ::manual_reset_event             m_eventResponse;


   api();
   ~api() override;

   
   virtual ::e_status initialize_api(::object* pobject, const ::file::path & pathProfile);


   virtual ::e_status load_profile();
   virtual ::e_status save_profile();


   virtual void on_login_response();


   virtual ::e_status api_login(const ::string & strConfig, const ::string & strProfile);


   virtual ::e_status api_get(::string & strNetworkPayload, const ::string & strUrl, property_set& set);

   virtual ::e_status api_get(::payload & payload, const ::string & strUrl, property_set & set);


   virtual ::e_status api_download(string strGet, const ::file::path& path, property_set& set);


   virtual string api_token(bool bForce);


   virtual void on_login_authentication_failed();

   virtual string randomDataBase64url(u32 length);
   virtual memory sha256(string strInput);
   virtual string base64urlencodeNoPadding(memory m);



};


#include "api_client.h"




