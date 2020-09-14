#pragma once


CLASS_DECL_AURA string url_encode(const char * psz);


CLASS_DECL_AURA string url_decode(const char * psz);
CLASS_DECL_AURA string url_decode(const char * pszUrl,strsize iLen);



CLASS_DECL_AURA bool url_query_get_param(string & strParam,const char * pszKey,const char * pszUrl);



#if defined(APPLEOS)

CLASS_DECL_AURA void openURL(const string &url_str);

#endif







