#pragma once

struct simple_http_status
{
public:

   unsigned int             m_dwStatusCode;
   const char *      m_pszStatus;

};

CLASS_DECL_APEX bool ms_download_dup(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrFile, bool bProgress, bool bUrlEncode = false, int * piStatus = nullptr, void (*callback)(void *, int, uptr) = nullptr, void * callback_param = nullptr);
CLASS_DECL_APEX string ms_get_dup(const ::scoped_string & scopedstrUrl, bool bCache = false, void (*callback)(void *, int, dword_ptr) = nullptr, void * callback_param = nullptr, bool bProgressCallback = false);
CLASS_DECL_APEX string defer_ls_get(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
//CLASS_DECL_APEX vsstring ms_post_dup(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrPost);
