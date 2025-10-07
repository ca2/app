#pragma once


CLASS_DECL_AURA string url_encode(const ::scoped_string & scopedstr);


CLASS_DECL_AURA string url_decode(const ::scoped_string & scopedstr);
CLASS_DECL_AURA string url_decode(const ::scoped_string & scopedstrUrl,character_count iLen);



CLASS_DECL_AURA bool url_query_get_param(string & strParam, const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrUrl);



#if defined(APPLEOS)

CLASS_DECL_AURA void openURL(const string &url_str);

#endif







