﻿// Created by camilo on 2021-11-05 16:10 PM <3ThomasBorregaardSørensen!!
#pragma once


//#include "acme/filesystem/filesystem/path.h"
#include "acme/parallelization/manual_reset_event.h"
//#include "acme/primitive/primitive/payload.h"
////#include "acme/primitive/primitive/object.h"


class api_client;


class CLASS_DECL_APEX api :
   virtual public ::object
{
protected:

   
   using ::object::initialize;


public:


   ::string                         m_strScope;
   bool                             m_bAuthenticated;
   bool                             m_bAuthenticating;
   //string                         m_strConfig;
   ::string                         m_strImplementation;
   string                           m_strBrowserAccount;
   string                           m_strToken;
   string                           m_strState;
   ::file::path                     m_pathProfile;
   ::payload                        m_payloadProfile;
   bool                             m_bWaitingResponseFromUser;
   ::pointer<::api_client>          m_papiclient;
   ::manual_reset_event             m_eventResponse;
   //;; property_set                m_setConfig;
   property_set                     m_setProfile;
   property_set                     m_setConfiguration;


   api();
   ~api() override;

   
   virtual void initialize_api(::particle * pparticle, const ::file::path & pathProfile, const ::scoped_string & scopedstrBrowserAccount);


   virtual void load_configuration();

   virtual void load_profile();
   virtual void save_profile();
   virtual void clear_profile();


   virtual void on_login_response();


   virtual ::string get_name_for_profile() = 0;

   virtual void switch_profile_folder(const ::file::path & pathFolder);

   //virtual void api_login(const ::string & strConfig, const ::string & strProfile);

   virtual void api_login();


   virtual void _api_get(::string & str, const ::string & strUrl, property_set& set);

   virtual void api_get(::payload & payload, const ::string & strUrl, property_set & set);

   virtual void api_download(string strGet, const ::file::path& path, property_set& set);

   virtual string api_token(bool bForce);


   virtual void on_login_authentication_failed();

   virtual string randomDataBase64url(u32 length);
   virtual memory sha256(string strInput);
   virtual string base64urlencodeNoPadding(memory m);



};


#include "api_client.h"




