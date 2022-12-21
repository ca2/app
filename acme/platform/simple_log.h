#pragma once


#include "log.h"


//CLASS_DECL_ACME void __simple_tracev(e_trace_category ecategory, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, i32 iLine, const ::scoped_string & scopedstrFormat, va_list args);
//CLASS_DECL_ACME void __simple_tracea(e_trace_category ecategory, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::file::path & path, i32 iLine, const ::scoped_string & scopedstr);
//CLASS_DECL_ACME void __simple_tracev(matter* pmatter, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, i32 iLine, const ::scoped_string & scopedstrFormat, va_list args);
//CLASS_DECL_ACME void __simple_tracea(matter* pmatter, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::file::path & path, i32 iLine, const ::scoped_string & scopedstr);


class CLASS_DECL_ACME simple_log :
   virtual public ::log
{
public:

   
   //CreatableFromBase(simple_log, logger);


   bool m_bReallySimple;


   simple_log();
   ~simple_log() override;


   void print(enum_trace_level etracelevel, enum_trace_category etracecategory, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstr) override;


};



