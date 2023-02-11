﻿// Created by camilo on 2021-11-17 01:29 PM <3ThomasBorregaardSørensen!! & Mummi!!
// Now rebased on api_client_base by camilo on 2023-02-01 09:24 PM <3ThomasBorregaardSørensen!! & Mummi!!
#pragma once


#include "api_client_base.h"


class CLASS_DECL_APEX api_client :
   virtual public ::api_client_base
{
public:


   ::pointer<::api>     m_papi;
   string               m_strImplementation;
   string               m_strBrowserAccount;
   ::file::path         m_pathProfileFolder;


   api_client();
   ~api_client() override;


   virtual void initialize_api_client(const ::scoped_string & scopedstrImplementation, const ::scoped_string & scopedstrBrowserAccount = "", const ::file::path & pathProfileFolder = "");


   virtual void defer_api();


   virtual void api_get(::string & str, const string& strUrl, property_set& set);


   virtual void api_get(::payload & payload, const string& strUrl, property_set& set);


   virtual void api_download(string strGet, const ::file::path& path, property_set& set);



};









