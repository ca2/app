#pragma once


namespace path
{


   CLASS_DECL_AQUA ::file::path app(string strPlatform, string strConfiguration);
   CLASS_DECL_AQUA ::file::path app_app(string strPlatform, string strConfiguration);
   CLASS_DECL_AQUA ::file::path app_app_admin(string strPlatform, string strConfiguration);
   CLASS_DECL_AQUA ::file::path app_app_nest(string strPlatform, string strConfiguration);
   CLASS_DECL_AQUA ::file::path vcredist(string strPlatform, string strConfiguration);
   CLASS_DECL_AQUA ::file::path module(HMODULE pmoduleosdata = nullptr);
   CLASS_DECL_AQUA ::file::path install_log(string strPlatform, string strConfiguration);
   CLASS_DECL_AQUA string from(string str);


} // namespace path