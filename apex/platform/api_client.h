// Created by camilo on 2021-11-17 01:29 PM <3ThomasBorregaardSørensen!! & Mummi!!
#pragma once


class CLASS_DECL_APEX api_client :
   virtual public ::object
{
public:


   ::pointer<::api>    m_papi;
   string               m_strImplementation;
   string               m_strProfileStore;
   string               m_strApiClientConfig;
   string               m_strBrowserProfile;


   api_client();
   ~api_client() override;


   virtual void defer_api();


   virtual void create_api();


   virtual void create_api(const ::string& strImplementation);


   virtual void api_get(::string & str, const string& strUrl, property_set& set);


   virtual void api_get(::payload & payload, const string& strUrl, property_set& set);


   virtual void api_download(string strGet, const ::file::path& path, property_set& set);



};









