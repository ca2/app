#pragma once

struct simple_http_status
{
public:

   ::u32             m_dwStatusCode;
   const char *      m_pszStatus;

};

CLASS_DECL_APEX bool ms_download_dup(const scoped_string & strUrl, const scoped_string & strFile, bool bProgress, bool bUrlEncode = false, i32 * piStatus = nullptr, void (*callback)(void *, i32, uptr) = nullptr, void * callback_param = nullptr);
CLASS_DECL_APEX string ms_get_dup(const scoped_string & strUrl, bool bCache = false, void (*callback)(void *, i32, dword_ptr) = nullptr, void * callback_param = nullptr, bool bProgressCallback = false);
CLASS_DECL_APEX string defer_ls_get(const scoped_string & strUrl, const scoped_string & strLocale, const scoped_string & strSchema);
//CLASS_DECL_APEX vsstring ms_post_dup(const scoped_string & strUrl, const scoped_string & strPost);
