#pragma once

struct simple_http_status
{
public:

   ::u32             m_dwStatusCode;
   const char *      m_pszStatus;

};

CLASS_DECL_AURA bool ms_download_dup(const ::string & pszUrl, const ::string & pszFile, bool bProgress, bool bUrlEncode = false, i32 * piStatus = nullptr, void (*callback)(void *, i32, uptr) = nullptr, void * callback_param = nullptr);
CLASS_DECL_AURA string ms_get_dup(const ::string & pszUrl, bool bCache = false, void (*callback)(void *, i32, dword_ptr) = nullptr, void * callback_param = nullptr, bool bProgressCallback = false);
CLASS_DECL_AURA string defer_ls_get(const ::string & pszUrl, const ::string & pszLocale, const ::string & pszSchema);
//CLASS_DECL_AURA vsstring ms_post_dup(const ::string & pszUrl, const ::string & pszPost);
