#pragma once


namespace path
{


   CLASS_DECL_ACME ::file::path app(string strPlatform, string strConfiguration);
   CLASS_DECL_ACME ::file::path app_app(string strPlatform, string strConfiguration);
   CLASS_DECL_ACME ::file::path app_app_admin(string strPlatform, string strConfiguration);
   CLASS_DECL_ACME ::file::path app_app_nest(string strPlatform, string strConfiguration);
   CLASS_DECL_ACME ::file::path vcredist(string strPlatform, string strConfiguration);
#ifdef WINDOWS
   CLASS_DECL_ACME ::file::path module(HMODULE pmoduleosdata = nullptr);
#else
   CLASS_DECL_ACME ::file::path module(void * pmoduleosdata = nullptr);
#endif
   CLASS_DECL_ACME ::file::path install_log(string strPlatform, string strConfiguration);
   CLASS_DECL_ACME string from(string str);


} // namespace path