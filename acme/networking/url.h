// Created by camilo on 2022-11-07 22:00 <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACME bool is_url(const char * pszCandidate,const char ** ppszRequest = nullptr);

CLASS_DECL_ACME bool is_like_url_protocol(const char* psz);


namespace url
{


   CLASS_DECL_ACME string encode(const ::block& block);


   CLASS_DECL_ACME string decode(const ::block& block);


   CLASS_DECL_ACME bool query_get_param(string& strParam, const char* pszKey, const char* pszUrl);


} // namespace url


#if defined(__APPLE__)

CLASS_DECL_ACME void openURL(const string& url_str);

#endif



