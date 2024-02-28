// From api_client.h by camilo on 2023-02-01 19:08 PM <3ThomasBorregaardSorensen!! & Mummi!!
#pragma once


#include "acme/primitive/collection/string_map.h"


class CLASS_DECL_APEX api_client_base :
   virtual public ::object
{
public:


   string_map < ::pointer < ::api > >     m_mapapi;
   //string                                 m_strImplementation; 
   //string                               m_strProfileStore;
   //string                               m_strApiClientConfig;
   //string                               m_strBrowserProfile;
   ::file::path                           m_pathFolder;

   
   api_client_base();
   ~api_client_base() override;


   //void initialize(::particle * pparticle) override;


   virtual ::pointer < ::api > create_new_profile(::string & strProfile, const ::scoped_string & scopedstrImplementation, const ::scoped_string & scopedstrService, const ::scoped_string & scopedstrBrowserAccount);


   virtual ::pointer < ::api > create_profile_api(const ::file::path & pathProfile, const ::scoped_string & scopedstrImplementation, const ::scoped_string & scopedstrService, const ::scoped_string & scopedstrBrowserAccount);


   virtual ::pointer < ::api > create_api(const ::scoped_string & scopedstrImplementation, const ::scoped_string & scopedstrService);

   
   //virtual ::pointer < ::api > create_api(const ::scoped_string & strImplementation);


   //virtual void api_get(::string & str, const string & strUrl, property_set & set);


   //virtual void api_get(::payload & payload, const string & strUrl, property_set & set);


   //virtual void api_download(string strGet, const ::file::path & path, property_set & set);


};



