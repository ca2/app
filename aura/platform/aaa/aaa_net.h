#pragma once


CLASS_DECL_AURA string url_encode(const ::string & psz);


CLASS_DECL_AURA string url_decode(const ::string & psz);
CLASS_DECL_AURA string url_decode(const ::string & pszUrl,strsize iLen);



CLASS_DECL_AURA bool url_query_get_param(string & strParam, const ::string & pszKey, const ::string & pszUrl);



#if defined(APPLEOS)

CLASS_DECL_AURA void openURL(const string &url_str);

#endif







