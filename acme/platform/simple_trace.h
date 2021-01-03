#pragma once


CLASS_DECL_APEX void __simple_tracev(e_trace_category ecategory, enum_trace_level elevel, const char* pszFunction, const char* pszFile, i32 iLine, const char* pszFormat, va_list args);
CLASS_DECL_APEX void __simple_tracea(e_trace_category ecategory, enum_trace_level elevel, const char* pszFunction, const char* pszFileName, i32 iLine, const char* psz);
CLASS_DECL_APEX void __simple_tracev(matter* pobject, enum_trace_level elevel, const char* pszFunction, const char* pszFile, i32 iLine, const char* pszFormat, va_list args);
CLASS_DECL_APEX void __simple_tracea(matter* pobject, enum_trace_level elevel, const char* pszFunction, const char* pszFileName, i32 iLine, const char* psz);



