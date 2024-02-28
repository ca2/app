#pragma once

struct simple_http_status
{
public:

   ::u32             m_dwStatusCode;
   const char *      m_pszStatus;

};

CLASS_DECL_ACME bool ms_download_dup(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrFile, bool bProgress, bool bUrlEncode = false, i32 * piStatus = nullptr, void (*callback)(void *, i32, uptr) = nullptr, void * callback_param = nullptr);
CLASS_DECL_ACME string ms_get_dup(const ::scoped_string & scopedstrUrl, bool bCache = false, void (*callback)(void *, i32, dword_ptr) = nullptr, void * callback_param = nullptr, bool bProgressCallback = false);
CLASS_DECL_ACME string defer_ls_get(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
//CLASS_DECL_ACME vsstring ms_post_dup(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrPost);
