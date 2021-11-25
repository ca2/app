// Created by camilo on 2021-11-17 01:29 PM <3ThomasBorregaardS�rensen!! & Mummi!!
#pragma once


class CLASS_DECL_APEX api_client :
   virtual public ::object
{
public:


   __pointer(::api)     m_papi;
   string               m_strImplementation;
   string               m_strProfileStore;
   string               m_strApiClientConfig;
   string               m_strBrowserProfile;


   api_client();
   ~api_client() override;


   virtual ::e_status defer_api();


   virtual ::e_status create_api();


   virtual ::e_status create_api(const ::string& strImplementation);


   virtual ::e_status api_get(::payload& payload, const string& strUrl, property_set& set);


   virtual ::e_status api_download(string strGet, const ::file::path& path, property_set& set);



};









