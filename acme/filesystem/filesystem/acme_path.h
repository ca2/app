// Create on 2021-03-21 00:11 <3ThomasBS_
#pragma once


class CLASS_DECL_ACME acme_path :
   virtual public matter
{
public:


   ::PLATFORM_NAMESPACE::acme_path* m_pplatformpath;

   ::file::path      m_pathModule;


   virtual ::file::path app(string strPlatform, string strConfiguration);

   virtual ::file::path app_app_admin(string strPlatform, string strConfiguration);
   
   virtual ::file::path app_app_nest(string strPlatform, string strConfiguration);

   virtual ::file::path app_app(string strPlatform, string strConfiguration);

   virtual ::file::path vcredist(string strPlatform, string strConfiguration);

   virtual ::file::path install_log(string strPlatform, string strConfiguration);

   virtual  string from(string str);

   virtual ::file::path app_module();


};



