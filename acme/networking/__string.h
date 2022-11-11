// Created by camilo on 2022-11-07 22:00 <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACME string url_encode(const char * psz);


CLASS_DECL_ACME string url_decode(const char * psz);
CLASS_DECL_ACME string url_decode(const char * pszUrl, strsize iLen);



CLASS_DECL_ACME bool url_query_get_param(string & strParam, const char * pszKey, const char * pszUrl);



#if defined(__APPLE__)

CLASS_DECL_ACME void openURL(const string & url_str);

#endif



