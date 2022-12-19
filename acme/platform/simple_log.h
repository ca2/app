#pragma once


#include "log.h"


//CLASS_DECL_ACME void __simple_tracev(e_trace_category ecategory, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFile, i32 iLine, const scoped_string & strFormat, va_list args);
//CLASS_DECL_ACME void __simple_tracea(e_trace_category ecategory, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFileName, i32 iLine, const scoped_string & str);
//CLASS_DECL_ACME void __simple_tracev(matter* pmatter, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFile, i32 iLine, const scoped_string & strFormat, va_list args);
//CLASS_DECL_ACME void __simple_tracea(matter* pmatter, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFileName, i32 iLine, const scoped_string & str);


class CLASS_DECL_ACME simple_log :
   virtual public ::log
{
public:

   
   //CreatableFromBase(simple_log, logger);


   bool m_bReallySimple;


   simple_log();
   ~simple_log() override;


   void print(enum_trace_level etracelevel, enum_trace_category etracecategory, const scoped_string & strFunction, const scoped_string & strFile, int iLine, const scoped_string & str) override;


};



