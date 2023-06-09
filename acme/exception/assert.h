#pragma once


//#include "exception.h"


class CLASS_DECL_ACME assert_exception :
   public ::exception
{
public:


   string m_strFile;
   long m_lLine;


   assert_exception(const ::scoped_string & scopedstrFile, long lLine);
   virtual ~assert_exception();


};



