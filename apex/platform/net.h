#pragma once


CLASS_DECL_APEX string url_encode_dup(const char * psz);


CLASS_DECL_APEX string url_decode_dup(const char * psz);
CLASS_DECL_APEX string url_decode_dup(const char * pszUrl,strsize iLen);



CLASS_DECL_APEX bool url_query_get_param_dup(string & strParam,const char * pszKey,const char * pszUrl);



#if defined(APPLEOS)

CLASS_DECL_APEX void openURL(const string &url_str);

#endif







