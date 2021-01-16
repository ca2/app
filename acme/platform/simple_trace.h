#pragma once


CLASS_DECL_ACME void __simple_tracev(e_trace_category ecategory, enum_trace_level elevel, const char* pszFunction, const char* pszFile, i32 iLine, const char* pszFormat, va_list args);
CLASS_DECL_ACME void __simple_tracea(e_trace_category ecategory, enum_trace_level elevel, const char* pszFunction, const char* pszFileName, i32 iLine, const char* psz);
CLASS_DECL_ACME void __simple_tracev(matter* pmatter, enum_trace_level elevel, const char* pszFunction, const char* pszFile, i32 iLine, const char* pszFormat, va_list args);
CLASS_DECL_ACME void __simple_tracea(matter* pmatter, enum_trace_level elevel, const char* pszFunction, const char* pszFileName, i32 iLine, const char* psz);


class CLASS_DECL_ACME simple_trace :
   virtual public ::matter
{
public:


   simple_trace();
   virtual ~simple_trace();


   virtual void __tracea(::matter * pmatter, enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz) override;


};



